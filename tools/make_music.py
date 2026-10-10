"""Menu music for the STE build (reverse-engineering/notes/music.md): the Amiga's 'wofsongs' (4 songs, 6 8SVX instruments) and the
period / duration tables of 'songplay' in one file for the player in game/music.h. Big-endian, offsets from the
file start:
  u16 'WM'; u16 song[5]; u16 instruments; u16 period table; u8 duration[20][2] (length, gate in ticks)
  song:        u16 track list[4]; u8 voice[8] (instrument per argument of command 0xdc; 0 = rest)
  track list:  { u16 pattern; s16 transpose } ...   (patterns end the list: 0xd9 next entry, 0xdb back to entry 0)
  pattern:     the Amiga's 2-byte events, unchanged
  instrument:  u16 sample, u16 one-shot bytes, u16 repeat bytes, u16 shift (samplesPerHiCycle = 1 << shift); 7 entries
  period table: u32[132], notes -33..98 (Paula period of a note = table / samplesPerHiCycle)
  samples:     signed 8-bit, one-shot part followed by the repeat part
Usage: make_music.py <out file>"""
import os, struct, sys

ROOT = os.path.join(os.path.dirname(__file__), '..')
GAME = os.path.join(ROOT, 'amiga-original')
KTAB, DUR = 0xad4, 0xa90 + 0x254          # in the relocated songplay image (reverse-engineering/notes/scratch/songplay.bin)


def load_data_hunk(path):
    d = open(path, 'rb').read()
    u = lambda p: struct.unpack('>I', d[p:p+4])[0]
    assert u(0) == 0x3f3
    p, hunks = 0x14 + 4 * (u(0x10) - u(0x0c) + 1), []
    while p < len(d):
        t = u(p) & 0x3fffffff; p += 4
        if t in (0x3e9, 0x3ea):
            n = u(p) * 4; p += 4
            hunks.append(d[p:p+n]); p += n
        elif t == 0x3eb:
            p += 4; hunks.append(b'')
        elif t == 0x3ec:
            while u(p): p += 8 + 4 * u(p)
            p += 4
        elif t == 0x3f0:
            while u(p): p += 8 + 4 * u(p)
            p += 4
        elif t == 0x3f2: pass
        else: break
    return hunks[1]                       # all relocations point into the hunk itself: base 0


def main(out_path):
    D = load_data_hunk(os.path.join(GAME, 'wofsongs'))
    P = open(os.path.join(ROOT, 'reverse-engineering/notes/scratch/songplay.bin'), 'rb').read()
    l = lambda p: struct.unpack('>I', D[p:p+4])[0]
    sw = lambda p: struct.unpack('>h', D[p:p+2])[0]

    out = bytearray(16 + 40)
    def put16(at, v): out[at:at+2] = struct.pack('>H', v)
    def here():
        if len(out) & 1: out.append(0)
        return len(out)
    out[0:2] = b'WM'
    out[16:56] = P[DUR:DUR + 40]
    assert out[16:20] == bytes((96, 86, 48, 43)), out[16:20].hex()

    voices = [0xcc + 0x2e * i for i in range(7)]          # voice0..6; voice0 has no sample
    patterns, songs_done = {}, {}

    def pattern(a):                                       # copy a pattern up to its end command
        if a in patterns: return patterns[a]
        q = a
        while D[q] not in (0xd9, 0xda, 0xdb): q += 2
        o = here(); out.extend(D[a:q+2]); patterns[a] = o
        return o

    def track_list(tl):                                   # entries until a pattern ends with 0xda / 0xdb
        ents, e = [], 0
        while True:
            pa = l(tl + e); ents.append((pa, sw(tl + e + 4)))
            q = pa
            while D[q] not in (0xd9, 0xda, 0xdb): q += 2
            if D[q] != 0xd9: break
            e += 6
        refs = [(pattern(pa), tr) for pa, tr in ents]
        o = here()
        for po, tr in refs: out.extend(struct.pack('>Hh', po, tr))
        return o

    for si in range(5):
        s = l(4 * si)
        if s not in songs_done:
            vt, q = [], s + 16
            while True:
                a = l(q); q += 4
                if a == 0 and vt: break
                vt.append(voices.index(a) if a else 0)
            lists = [track_list(l(s + 4 * t)) for t in range(4)]
            o = here()
            out.extend(struct.pack('>4H', *lists) + bytes((vt + [0] * 8)[:8]))
            songs_done[s] = o
        put16(2 + 2 * si, songs_done[s])

    inst = []
    for a in voices:
        f = l(a + 10)
        if not f: inst.append((0, 0, 0, 0)); continue
        q, vh, body = f + 12, None, None
        while q < f + 8 + l(f + 4):
            cid, n = D[q:q+4], l(q + 4)
            if cid == b'VHDR': vh = struct.unpack('>IIIHBBI', D[q+8:q+28])
            if cid == b'BODY': body = D[q+8:q+8+n]
            q += 8 + n + (n & 1)
        one, rep, sphc, _, octs, comp, _ = vh
        assert octs == 1 and comp == 0 and sphc in (8, 16, 32) and len(body) >= one + rep
        o = here(); out.extend(body[:one + rep])
        inst.append((o, one, rep, sphc.bit_length() - 1))
    put16(12, here())
    for i in inst: out.extend(struct.pack('>4H', *i))
    put16(14, here())
    out.extend(P[KTAB:KTAB + 132 * 4])
    assert struct.unpack('>I', P[KTAB + 4 * 60:KTAB + 4 * 61])[0] == 13682     # note 27 = middle C
    assert len(out) < 65536
    open(out_path, 'wb').write(out)
    print('music.dat', len(out), 'bytes,', len(patterns), 'patterns, samples', sum(i[1] + i[2] for i in inst))


if __name__ == '__main__':
    main(sys.argv[1])
