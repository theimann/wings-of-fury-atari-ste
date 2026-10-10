"""Convert Wings of Fury Amiga graphics to PNG + JSON for inspection and the STE asset pipeline.

Usage: convert_gfx.py <shapes dir> <output dir>
"""
import json, os, sys
from PIL import Image, ImageDraw
sys.path.insert(0, os.path.dirname(__file__))
import iff, ppkc, rpck

# palette to preview each bank with (index 0 rendered transparent)
BANK_PALETTE = {
    'nightdash.shp': 'night.p',
}
DEFAULT_PALETTE = 'palette'

def flat(pal):
    out = []
    for c in pal:
        out += c
    return out + [0] * (768 - len(out))

def frame_image(f, pal):
    im = Image.new('RGBA', (f.w, f.h))
    im.putdata([pal[p] + (255,) if m else (0, 0, 0, 0) for p, m in zip(f.pixels, f.mask)])
    return im

def contact_sheet(frames, pal, scale=2, maxw=1100):
    pad, label = 6, 12
    cells = []
    for f in frames:
        cells.append((f, max(f.w * scale, 40), f.h * scale + label))
    rows, row, x = [], [], 0
    for c in cells:
        if row and x + c[1] + pad > maxw:
            rows.append(row); row, x = [], 0
        row.append(c); x += c[1] + pad
    rows.append(row)
    H = sum(max(c[2] for c in r) + pad for r in rows) + pad
    W = max(sum(c[1] + pad for c in r) for r in rows) + pad
    sheet = Image.new('RGBA', (W, H), (255, 0, 255, 255))
    draw = ImageDraw.Draw(sheet)
    y = pad
    for r in rows:
        x = pad
        for f, cw, ch in r:
            draw.text((x, y), f.name, fill=(255, 255, 255, 255))
            im = frame_image(f, pal).resize((f.w * scale, f.h * scale), Image.NEAREST)
            sheet.alpha_composite(im, (x, y + label))
            x += cw + pad
        y += max(c[2] for c in r) + pad
    return sheet

def main(src, out):
    os.makedirs(out, exist_ok=True)
    palettes = {}
    for name in os.listdir(src):
        d = rpck.load(os.path.join(src, name))
        if d[:4] == b'CMAP' or (d[:4] == b'FORM' and b'CMAP' in d[:200]):
            palettes[name] = iff.read_palette(d)
    with open(os.path.join(out, 'palettes.json'), 'w') as fp:
        json.dump({k: ['%02x%02x%02x' % c for c in v] for k, v in palettes.items()}, fp, indent=1)

    summary = []
    for name in sorted(os.listdir(src)):
        d = rpck.load(os.path.join(src, name))
        base = name.replace('.', '_')
        if d[:4] == b'PPkc':
            pal = palettes[BANK_PALETTE.get(name, DEFAULT_PALETTE)]
            frames = ppkc.parse(d)
            fdir = os.path.join(out, 'frames', base)
            os.makedirs(fdir, exist_ok=True)
            meta = []
            for f in frames:
                frame_image(f, pal).save(os.path.join(fdir, f.name.replace(' ', '_') + '.png'))
                meta.append(dict(name=f.name, w=f.w, h=f.h, hot_x=f.hx, hot_y=f.hy,
                                 src_x=f.sx, src_y=f.sy, clear_planes=f.clear_planes, set_planes=f.set_planes, opaque=f.opaque,
                                 plane_map=f.plane_map,
                                 colours=sorted(set(p for p, m in zip(f.pixels, f.mask) if m))))
            with open(os.path.join(fdir, '_frames.json'), 'w') as fp:
                json.dump(meta, fp, indent=1)
            contact_sheet(frames, pal).save(os.path.join(out, base + '_sheet.png'))
            summary.append(f'{name}: {len(frames)} frames')
        elif d[:4] == b'FORM' and d[8:12] == b'ILBM':
            w, h, planes, pixels, pal = iff.read_ilbm(d)
            if w < 8:
                continue  # palette carrier, not an image
            im = Image.new('P', (w, h)); im.putpalette(flat(pal)); im.putdata(pixels)
            if w == 640:  # hires: show at correct aspect
                im = im.resize((w, h * 2), Image.NEAREST)
            im.save(os.path.join(out, base + '.png'))
            summary.append(f'{name}: ILBM {w}x{h} {planes} planes')
    print('\n'.join(summary))

if __name__ == '__main__':
    main(*sys.argv[1:3])
