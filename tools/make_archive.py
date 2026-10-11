"""Build the game's data archive: tools/make_archive.py <folder> <out file>

Every file of the folder goes into one file, in the order of the names, without dates: the same input gives the
same bytes. The game reads its files from it (dirs_init / arch_open in game/wof.cpp, the disk archive in AGT's
zerolibc); a file that is not in it is looked for on the disk.

Layout (big-endian): 'WOFD', u32 length of the archive, u32 sum of its 32-bit words from offset 16 on, u16 format
(1), u16 number of files, then per file char name[12] (upper case, NUL padded), u32 offset from the start of the
archive, u32 size; then the files, each padded to 4 bytes.
"""
import hashlib, os, struct, sys

SKIP_EXT = ('prg', 'txt', 'wof')
SKIP = ('HISCORE.DAT',)


def main(src, dst):
    names = sorted(n for n in os.listdir(src) if os.path.isfile(os.path.join(src, n))
                   and n.rsplit('.', 1)[-1].lower() not in SKIP_EXT and n.upper() not in SKIP and not n.startswith('.'))
    assert names and all(len(n) <= 12 for n in names), 'no files, or a name longer than 8.3'
    names.sort(key=str.upper)
    off = 16 + 20 * len(names)
    head, body = b'', b''
    for n in names:
        d = open(os.path.join(src, n), 'rb').read()
        head += n.upper().encode('ascii').ljust(12, b'\0') + struct.pack('>II', off, len(d))
        d += b'\0' * (-len(d) & 3)
        body += d; off += len(d)
    rest = struct.pack('>HH', 1, len(names))[2:] + head + body      # (from offset 14: the count, directory, files)
    summed = rest[2:]                                               # (from offset 16)
    total = sum(struct.unpack('>%dI' % (len(summed) // 4), summed)) & 0xffffffff
    out = b'WOFD' + struct.pack('>IIH', 14 + len(rest), total, 1) + rest
    assert len(out) == off
    open(dst, 'wb').write(out)
    print('%s: %d files, %d bytes, sha256 %s' % (os.path.basename(dst), len(names), len(out), hashlib.sha256(out).hexdigest()))


if __name__ == '__main__':
    main(sys.argv[1], sys.argv[2])
