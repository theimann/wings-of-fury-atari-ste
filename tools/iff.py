"""Minimal IFF ILBM / bare CMAP reader for Amiga images and palettes."""
import struct

def _chunks(d, start=12):
    i = start
    while i + 8 <= len(d):
        cid = d[i:i + 4].decode('latin1')
        size = struct.unpack('>I', d[i + 4:i + 8])[0]
        yield cid, d[i + 8:i + 8 + size]
        i += 8 + size + (size & 1)

def read_palette(d):
    """Return a list of (r,g,b) from an ILBM's CMAP or a bare 'CMAP'+id+rgb file."""
    if d[:4] == b'CMAP':
        rgb = d[8:]
    else:
        rgb = dict(_chunks(d))['CMAP']
    return [tuple(rgb[i:i + 3]) for i in range(0, len(rgb) - 2, 3)]

def _byterun1(src, n):
    out = bytearray()
    i = 0
    while len(out) < n:
        c = src[i]; i += 1
        if c < 128:
            out += src[i:i + c + 1]; i += c + 1
        elif c > 128:
            out += bytes([src[i]]) * (257 - c); i += 1
    return bytes(out[:n])

def read_ilbm(d):
    """Return (width, height, planes, pixel index list, palette)."""
    assert d[:4] == b'FORM' and d[8:12] == b'ILBM', 'not an ILBM'
    ch = dict(_chunks(d))
    w, h, _, _, planes, masking, comp = struct.unpack('>HHhhBBB', ch['BMHD'][:11])
    rowbytes = ((w + 15) // 16) * 2
    nplanes = planes + (1 if masking == 1 else 0)
    body = ch['BODY']
    total = rowbytes * nplanes * h
    raw = _byterun1(body, total) if comp == 1 else body[:total]
    pixels = [0] * (w * h)
    for y in range(h):
        for p in range(planes):
            row = (y * nplanes + p) * rowbytes
            for x in range(w):
                if raw[row + (x >> 3)] & (0x80 >> (x & 7)):
                    pixels[y * w + x] |= 1 << p
    return w, h, planes, pixels, read_palette(d)
