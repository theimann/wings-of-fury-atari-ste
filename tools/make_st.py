"""Atari ST floppy image (.st: raw sectors) from a disk folder, for emulators, Gotek drives and real disks.
720 KB double-sided (80 tracks, 2 sides, 9 sectors), FAT12 as TOS formats it; files are stored contiguously.
One level of folders (AUTO). Usage: make_st.py <disk folder> <out.st> [--label NAME]"""
import os, struct, sys

BPS, SPC, RES, NFATS, ROOT, SPT, HEADS, TRACKS = 512, 2, 1, 2, 112, 9, 2, 80
TOTAL = SPT * HEADS * TRACKS
SPF = 5                                       # TOS's own format uses 5 sectors per FAT
ROOT_SECS = ROOT * 32 // BPS
DATA0 = RES + NFATS * SPF + ROOT_SECS
CLUSTERS = (TOTAL - DATA0) // SPC


def name83(n):
    n = n.upper()
    base, _, ext = n.partition('.')
    assert 0 < len(base) <= 8 and len(ext) <= 3, n
    return (base.ljust(8) + ext.ljust(3)).encode('ascii')


def entry(name, attr, cluster, size):
    return name + bytes([attr]) + bytes(10) + struct.pack('<HHHI', 0x6000, 0x5544, cluster, size)   # 12:00, 1990-10-04


def main(src, out, label):
    fat = [0xff9, 0xfff] + [0] * CLUSTERS
    data = bytearray(CLUSTERS * SPC * BPS)
    nxt = [2]

    def store(blob):                          # -> first cluster (0 for an empty file)
        n = (len(blob) + SPC * BPS - 1) // (SPC * BPS)
        if n == 0: return 0
        c0 = nxt[0]
        if c0 + n > CLUSTERS + 2: raise SystemExit('disk full: %d KB do not fit' % (sum(len(b) for b in [blob]) // 1024))
        for c in range(c0, c0 + n): fat[c] = c + 1 if c < c0 + n - 1 else 0xfff
        data[(c0 - 2) * SPC * BPS:(c0 - 2) * SPC * BPS + len(blob)] = blob
        nxt[0] += n
        return c0

    root = bytearray()
    if label: root += entry(label.upper().ljust(11)[:11].encode('ascii'), 0x08, 0, 0)
    names = sorted(os.listdir(src), key=lambda n: (not os.path.isdir(os.path.join(src, n)), n.upper()))
    used = 0
    for n in names:
        p = os.path.join(src, n)
        if n.startswith('.'): continue
        if os.path.isdir(p):
            sub = [f for f in sorted(os.listdir(p)) if not f.startswith('.')]
            dirblob = bytearray(SPC * BPS)
            c = store(bytes(dirblob))          # the folder's own cluster first, its files after it
            ents = entry(b'.          ', 0x10, c, 0) + entry(b'..         ', 0x10, 0, 0)
            for f in sub:
                blob = open(os.path.join(p, f), 'rb').read(); used += len(blob)
                ents += entry(name83(f), 0x20, store(blob), len(blob))
            assert len(ents) <= SPC * BPS, 'folder too large'
            data[(c - 2) * SPC * BPS:(c - 2) * SPC * BPS + len(ents)] = ents
            root += entry(name83(n), 0x10, c, 0)
        else:
            blob = open(p, 'rb').read(); used += len(blob)
            root += entry(name83(n), 0x20, store(blob), len(blob))
    assert len(root) <= ROOT * 32, 'too many files in the root folder'

    boot = bytearray(BPS)
    boot[0:2] = b'\x60\x38'                    # (bra.s: not executable, the checksum is not $1234)
    boot[2:8] = b'Loader'
    boot[8:11] = b'\x57\x4f\x46'               # serial number
    boot[11:30] = struct.pack('<HBHBHHBHHHH', BPS, SPC, RES, NFATS, ROOT, TOTAL, 0xf9, SPF, SPT, HEADS, 0)
    fatb = bytearray(SPF * BPS)
    for i in range(0, len(fat) - 1, 2):
        a, b = fat[i], fat[i + 1]
        fatb[i * 3 // 2:i * 3 // 2 + 3] = bytes((a & 0xff, (a >> 8) | ((b & 0xf) << 4), b >> 4))
    img = bytes(boot) + bytes(fatb[:SPF * BPS]) * NFATS + bytes(root).ljust(ROOT_SECS * BPS, b'\0') + bytes(data)
    assert len(img) == TOTAL * BPS
    open(out, 'wb').write(img)
    free = (CLUSTERS + 2 - nxt[0]) * SPC * BPS
    print('%s: %d files, %d KB data, %d KB free of %d' % (os.path.basename(out), len(root) // 32, used // 1024, free // 1024, CLUSTERS * SPC * BPS // 1024))


if __name__ == '__main__':
    label = sys.argv[sys.argv.index('--label') + 1] if '--label' in sys.argv else 'WOF'
    main(sys.argv[1], sys.argv[2], label)
