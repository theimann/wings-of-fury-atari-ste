"""Amiga hunk executable loader: parse hunks and build a relocated flat image.

Usage: hunk.py <exe> <out.bin> [base]   (writes image + prints hunk map)
"""
import struct, sys

HUNK_NAMES = {0x3e7: 'UNIT', 0x3e8: 'NAME', 0x3e9: 'CODE', 0x3ea: 'DATA', 0x3eb: 'BSS',
              0x3ec: 'RELOC32', 0x3f0: 'SYMBOL', 0x3f1: 'DEBUG', 0x3f2: 'END',
              0x3f3: 'HEADER', 0x3f7: 'DREL32', 0x3fc: 'RELOC32SHORT'}

def parse(data):
    pos = 0
    def u32():
        nonlocal pos
        v = struct.unpack('>I', data[pos:pos + 4])[0]; pos += 4; return v
    assert u32() == 0x3f3
    while u32():  # resident library names
        pass
    table_size, first, last = u32(), u32(), u32()
    sizes = [(u32() & 0x3fffffff) * 4 for _ in range(last - first + 1)]
    hunks = []
    cur = None
    while pos < len(data):
        t = u32() & 0x3fffffff
        if t in (0x3e9, 0x3ea):
            n = u32() * 4
            cur = dict(type=HUNK_NAMES[t], size=sizes[len(hunks)], data=data[pos:pos + n],
                       relocs=[], symbols=[])
            hunks.append(cur); pos += n
        elif t == 0x3eb:
            u32()
            cur = dict(type='BSS', size=sizes[len(hunks)], data=b'', relocs=[], symbols=[])
            hunks.append(cur)
        elif t == 0x3ec:
            while True:
                n = u32()
                if not n:
                    break
                target = u32()
                for _ in range(n):
                    cur['relocs'].append((u32(), target))
        elif t == 0x3fc or t == 0x3f7:
            while True:
                n = struct.unpack('>H', data[pos:pos + 2])[0]; pos += 2
                if not n:
                    break
                target = struct.unpack('>H', data[pos:pos + 2])[0]; pos += 2
                for _ in range(n):
                    cur['relocs'].append((struct.unpack('>H', data[pos:pos + 2])[0], target)); pos += 2
            if pos & 2:
                pos += 2
        elif t == 0x3f0:
            while True:
                n = u32()
                if not n:
                    break
                name = data[pos:pos + n * 4].rstrip(b'\0').decode('latin1'); pos += n * 4
                cur['symbols'].append((name, u32()))
        elif t == 0x3f1:
            n = u32(); pos += n * 4
        elif t == 0x3f2:
            pass
        else:
            raise ValueError(f'unknown hunk type {t:#x} at {pos - 4:#x}')
    return hunks

def layout(hunks, base=0x10000, align=0x10):
    addrs, a = [], base
    for h in hunks:
        addrs.append(a)
        a += (h['size'] + align - 1) // align * align
    img = bytearray(a - base)
    for h, ha in zip(hunks, addrs):
        img[ha - base:ha - base + len(h['data'])] = h['data']
    for h, ha in zip(hunks, addrs):
        for off, target in h['relocs']:
            p = ha - base + off
            v = struct.unpack('>I', img[p:p + 4])[0] + addrs[target]
            img[p:p + 4] = struct.pack('>I', v & 0xffffffff)
    return bytes(img), addrs

if __name__ == '__main__':
    exe, out = sys.argv[1:3]
    base = int(sys.argv[3], 0) if len(sys.argv) > 3 else 0x10000
    hunks = parse(open(exe, 'rb').read())
    img, addrs = layout(hunks, base)
    open(out, 'wb').write(img)
    for i, (h, a) in enumerate(zip(hunks, addrs)):
        print(f"hunk {i}: {h['type']:5} @ {a:#08x} size {h['size']:#07x} relocs {len(h['relocs'])} symbols {len(h['symbols'])}")
