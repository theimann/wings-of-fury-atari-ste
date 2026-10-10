"""PPkc shape-bank decoder (Broderbund Wings of Fury, Amiga).

Layout (big-endian):
  'PPkc' u16 count, count x 4-char names, count x u32 offsets (relative to end of table)
Frame:
  u16 width_bytes, u16 height, s16 hot_x, s16 hot_y, u16 src_x, u16 src_y,
  u8 clear_planes - destination planes forced to 0 under the mask
  u8 set_planes   - destination planes forced to 1 under the mask
  u8 plane_map[6] - destination plane mask for each stored plane, 0-terminated
  then stored planes, plane-sequential, each height * width_bytes
Blit semantics (from the game's blitter code, see reverse-engineering/notes/render_sound.md 5.x):
  mask = OR of all stored planes; stored planes *replace* their destination plane bits under the mask;
  frames with width_bytes*height > 1040 are blitted without mask (opaque rectangle);
  destination planes not named in clear/set/plane_map keep the background (decoded here against background 0).
"""
OPAQUE_LIMIT = 1040
import struct

class Frame:
    __slots__ = ('name', 'wb', 'w', 'h', 'hx', 'hy', 'sx', 'sy', 'clear_planes', 'set_planes', 'opaque',
                 'plane_map', 'pixels', 'mask')

def _parse_frame(name, d, o, interleaved=False):
    f = Frame()
    f.name = name
    f.wb, f.h, f.hx, f.hy, f.sx, f.sy = struct.unpack('>HHhhHH', d[o:o + 12])
    f.w = f.wb * 8
    f.clear_planes = d[o + 12]
    f.set_planes = d[o + 13]
    f.plane_map = []
    for b in d[o + 14:o + 20]:
        if b == 0:
            break
        f.plane_map.append(b)
    data = o + 20
    psize = f.wb * f.h
    pixels = [0] * (f.w * f.h)
    mask = [False] * (f.w * f.h)
    for p, dst in enumerate(f.plane_map):
        for y in range(f.h):
            if interleaved:
                row = data + (y * len(f.plane_map) + p) * f.wb
            else:
                row = data + p * psize + y * f.wb
            for xb in range(f.wb):
                byte = d[row + xb]
                if not byte:
                    continue
                for bit in range(8):
                    if byte & (0x80 >> bit):
                        i = y * f.w + xb * 8 + bit
                        pixels[i] |= dst
                        mask[i] = True
    f.opaque = psize > OPAQUE_LIMIT
    if f.opaque:
        mask = [True] * len(mask)
    if f.set_planes:
        for i in range(len(pixels)):
            if mask[i]:
                pixels[i] |= f.set_planes
    f.pixels, f.mask = pixels, mask
    return f

def parse(d, interleaved=False):
    assert d[:4] == b'PPkc', 'not a PPkc bank'
    n = struct.unpack('>H', d[4:6])[0]
    names = [d[6 + i * 4:10 + i * 4].decode('latin1').rstrip() for i in range(n)]
    ot = 6 + 4 * n
    offs = struct.unpack('>%dI' % n, d[ot:ot + 4 * n])
    base = ot + 4 * n
    return [_parse_frame(names[i], d, base + offs[i], interleaved) for i in range(n)]
