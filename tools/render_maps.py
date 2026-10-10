"""Render Wings of Fury level maps to PNG previews.

Map format (big-endian): u32 file size, u32 home (carrier) byte offset, then u16 cells.
One cell = 8 world pixels. Cell bits:
  15     object anchor (draw/spawn an object here)
  13..11 height offset (0-7)
  10..2  type: index into the world shape-name list (>= 184: ships / special markers)
  1..0   surface: 0 = open sea, 1 = carrier deck, 2 = island
Usage: render_maps.py <maps dir> <exe image wings.bin> <world frames dir> <out dir>
"""
import json, os, struct, sys
from PIL import Image, ImageDraw

CELL = 8
SEA_Y = 150          # preview baseline (not the game's real screen coordinate)
SKY = (0x60, 0xb0, 0xf0)
SEA = (0x00, 0x60, 0xd0)
SAND = (0xd0, 0x90, 0x60)
DECK = (0x60, 0x60, 0x70)

# world-list entries with no sprite: gameplay markers
INVISIBLE = {'barf', 'bumb', 'LIVE'}
# ship / special object IDs above the world list (identified from part counts and hit points)
SHIPS = {0xcc: 'transport', 0xe4: 'destroyer', 0xe5: 'dest.2', 0xe6: 'dest.3', 0xe7: 'dest.4',
         0xf1: 'J-carrier', 0xf2: 'jcar.2', 0xf3: 'jcar.3', 0xf6: 'jcar.4',
         0x10c: 'battleship', 0x10d: 'bship.2', 0x10e: 'bship.3', 0x10f: 'bship.4', 0x110: 'bship.5'}

def world_names(img):
    names, i = [], 0x23e34 - 0x10000
    while img[i:i + 4] != b'\0\0\0\0':
        names.append(img[i:i + 4].decode('latin1')); i += 4
    return names

def load_map(path):
    m = open(path, 'rb').read()
    size, home = struct.unpack('>II', m[:8])
    cells = struct.unpack('>%dH' % ((len(m) - 8) // 2), m[8:8 + (len(m) - 8) // 2 * 2])
    return home, cells

def render(cells, home, names, frames, fdir):
    W = len(cells) * CELL
    im = Image.new('RGBA', (W, 220), SKY + (255,))
    dr = ImageDraw.Draw(im)
    dr.rectangle([0, SEA_Y, W, 220], fill=SEA)
    for i, v in enumerate(cells):
        x = i * CELL
        surf = v & 3
        if surf == 2:
            dr.rectangle([x, SEA_Y - 4, x + CELL - 1, SEA_Y + 6], fill=SAND)
        elif surf == 1:
            dr.rectangle([x, SEA_Y - 2, x + CELL - 1, SEA_Y + 2], fill=DECK)
    objs = []
    for i, v in enumerate(cells):
        if not v & 0x8000:
            continue
        t = (v >> 2) & 0x1ff
        h = (v >> 11) & 7
        x = i * CELL
        name = names[t] if t < len(names) else None
        f = frames.get(name)
        if f:
            spr = Image.open(os.path.join(fdir, name + '.png'))
            im.alpha_composite(spr, (max(0, x - f['hot_x']), max(0, SEA_Y - f['hot_y'] - h)))
            objs.append(name)
        elif name in INVISIBLE:
            objs.append(name)
        else:
            label = SHIPS.get(t) or name or ('ID%03x' % t)
            dr.rectangle([x - 20, SEA_Y - 30, x + 20, SEA_Y], outline=(255, 0, 0), width=2)
            dr.text((x - 18, SEA_Y - 26), label, fill=(255, 255, 255))
            objs.append(label)
    hx = home // 2 * CELL
    dr.line([hx, 0, hx, 20], fill=(255, 255, 0), width=3)
    dr.text((hx + 4, 4), 'home', fill=(255, 255, 0))
    return im, objs

def main(mapdir, exe, fdir, out):
    os.makedirs(out, exist_ok=True)
    img = open(exe, 'rb').read()
    names = world_names(img)
    frames = {f['name']: f for f in json.load(open(os.path.join(fdir, '_frames.json')))}
    summary = {}
    for fn in sorted(os.listdir(mapdir)):
        home, cells = load_map(os.path.join(mapdir, fn))
        im, objs = render(cells, home, names, frames, fdir)
        # wrap long strip into rows for viewing
        rowlen = 2400
        rows = (im.width + rowlen - 1) // rowlen
        sheet = Image.new('RGBA', (rowlen, rows * im.height), (0, 0, 0, 255))
        for r in range(rows):
            sheet.paste(im.crop((r * rowlen, 0, (r + 1) * rowlen, im.height)), (0, r * im.height))
        base = fn.replace('.map', '')
        sheet.save(os.path.join(out, base + '.png'))
        from collections import Counter
        summary[fn] = dict(cells=len(cells), width_px=len(cells) * CELL, home_cell=home // 2,
                           objects=dict(Counter(objs)))
        print(fn, len(cells) * CELL, 'px', dict(Counter(objs)))
    json.dump(summary, open(os.path.join(out, 'maps.json'), 'w'), indent=1)

if __name__ == '__main__':
    main(*sys.argv[1:5])
