"""Build the STE cockpit panel (320x37 low-res) from the Amiga hires dashboard 'iff-dash' (640x37).

Outputs: <out>/panel.png (320x48, 8-bit indexed, dash palette, tile source)
         <out>/panelspr.png (digit + icon sprites in the dash palette)
         preview: <out>/../build/panel_preview.png
The art is downscaled 2:1 keeping the darker pixel of each pair (preserves 1-px lines); the OIL/FUEL labels and all
digits are redrawn with a hand-made low-res pixel font, because 2:1 downscaled hires text is unreadable.
"""
import os, sys
from PIL import Image
sys.path.insert(0, os.path.dirname(__file__))
import iff, ppkc, rpck

ROOT = os.path.join(os.path.dirname(__file__), '..')
SHAPES = os.path.join(ROOT, 'amiga-original/shapes')

# 4x7 digits (hand-made, in the spirit of the dashboard's LCD style)
DIGITS = [
    ['.##.', '#..#', '#..#', '#..#', '#..#', '#..#', '.##.'],
    ['..#.', '.##.', '..#.', '..#.', '..#.', '..#.', '.###'],
    ['.##.', '#..#', '...#', '..#.', '.#..', '#...', '####'],
    ['.##.', '#..#', '...#', '..#.', '...#', '#..#', '.##.'],
    ['...#', '..##', '.#.#', '#..#', '####', '...#', '...#'],
    ['####', '#...', '###.', '...#', '...#', '#..#', '.##.'],
    ['.##.', '#...', '###.', '#..#', '#..#', '#..#', '.##.'],
    ['####', '...#', '..#.', '..#.', '.#..', '.#..', '.#..'],
    ['.##.', '#..#', '#..#', '.##.', '#..#', '#..#', '.##.'],
    ['.##.', '#..#', '#..#', '.###', '...#', '...#', '.##.'],
]
# 3x5 capitals for the gauge labels
LETTERS = {
    'O': ['###', '#.#', '#.#', '#.#', '###'], 'I': ['###', '.#.', '.#.', '.#.', '###'], 'L': ['#..', '#..', '#..', '#..', '###'],
    'F': ['###', '#..', '##.', '#..', '#..'], 'U': ['#.#', '#.#', '#.#', '#.#', '###'], 'E': ['###', '#..', '##.', '#..', '###'],
}
WHITE, LGREY, DGREY = 15, 14, 12          # dash palette indices (d0d0e0, 9090a0, 303040)
BOXBLACK = 11                              # counter box background
NEEDLE_AX, NEEDLE_AY = 16, 12              # gauge needle pivot inside its 32x24 sprite cell


def wnum_digits(dash):
    """White score/counter digits from the Amiga 'wnum' strip (hires, 8 rows per digit, glyph rows 2-8 of each cell),
    halved horizontally keeping a pixel if either of the pair is set: bold 6x7 glyphs like the original."""
    w = dash['wnum']
    out = []
    for d in range(10):
        rows = []
        for y in range(2 + 8 * d, 9 + 8 * d):
            r = ''
            for x in range(2, 14, 2):
                a, b = y * w.w + x, y * w.w + x + 1
                r += '#' if (w.mask[a] or w.mask[b]) else '.'
            rows.append(r)
        out.append(rows)
    return out


def glyph(img, g, x, y, col):
    for j, row in enumerate(g):
        for i, ch in enumerate(row):
            if ch == '#':
                img.putpixel((x + i, y + j), col)


def glyph_rgb(img, g, x, y, rgb):
    for j, row in enumerate(g):
        for i, ch in enumerate(row):
            if ch == '#':
                img.putpixel((x + i, y + j), tuple(rgb))


def text(img, s, x, y, col):
    for ch in s:
        glyph(img, LETTERS[ch], x, y, col)
        x += 4


def main(out):
    d = rpck.load(os.path.join(SHAPES, 'iff-dash'))
    w, h, planes, pixels, pal = iff.read_ilbm(d)
    flat = [v for c in pal for v in c] + [0] * (768 - 3 * len(pal))
    lum = [sum(c) for c in pal]
    panel = Image.new('P', (320, 48), 0)
    panel.putpalette(flat)
    for y in range(h):
        for x in range(320):
            p, q = pixels[y * w + 2 * x], pixels[y * w + 2 * x + 1]
            panel.putpixel((x, y), p if lum[p] <= lum[q] else q)
    # labels: clear the downscaled lettering (gauge faces are black) and redraw
    for (x0, x1, label, lx) in [(96, 116, 'OIL', 100), (205, 230, 'FUEL', 210)]:
        for y in range(28, 35):
            for x in range(x0, x1):
                if panel.getpixel((x, y)) in (WHITE, LGREY):
                    panel.putpixel((x, y), 0)
        text(panel, label, lx, 29, WHITE)
    # the planes-shot-down counter (G_252cf) is live: erase the baked "00" from its black box (x 249-266, y 20-28)
    for y in range(20, 29):
        for x in range(249, 267):
            if panel.getpixel((x, y)) in (WHITE, LGREY):
                panel.putpixel((x, y), BOXBLACK)
    # the scrolling playfield shows its window from map x 16: pad 16 px both sides (panel x 0 = map x 16)
    padded = Image.new('P', (352, 48), 0)
    padded.putpalette(flat)
    padded.paste(panel, (16, 0))
    padded.save(os.path.join(out, 'panel.png'))

    # sprites (32x24 cells, 10 per row): 0-9 dark digits, 10-19 white digits, 20 bomb, 21 rocket, 22 torpedo icon,
    # 23-45 gauge needles ndl1..ndln (hotspot at NEEDLE_AX/AY in the cell), 46 lit warning lamp 'olon' (top-left), 47 kill tally 'zero'
    dash = {f.name: f for f in ppkc.parse(rpck.load(os.path.join(SHAPES, 'dash.shp')))}
    spr = Image.new('P', (32 * 10, 24 * 5), 0)
    spr.putpalette(flat)
    wdig = wnum_digits(dash)
    for n in range(10):
        glyph(spr, DIGITS[n], n * 32, 0, DGREY)
        glyph(spr, wdig[n], n * 32, 24, WHITE)
    for k, name in enumerate(['bomb', 'misl', 'torp']):
        f = dash[name]
        for yy in range(f.h):
            for xx in range(0, f.w, 2):
                a, b = (yy * f.w + xx), (yy * f.w + xx + 1)
                cand = [c for c, m in ((f.pixels[a], f.mask[a]), (f.pixels[b], f.mask[b])) if m and c and c not in (6, 7)]
                if cand and xx // 2 < 32:
                    spr.putpixel((k * 32 + xx // 2, 48 + yy), max(cand, key=lambda c: lum[c]))   # light icon on black
    def half(f, cx, cy):          # hires frame halved horizontally (brighter pixel of each pair), top-left at cx, cy
        for yy in range(f.h):
            for xx in range(0, f.w, 2):
                a, b = (yy * f.w + xx), (yy * f.w + xx + 1)
                cand = [c for c, m in ((f.pixels[a], f.mask[a]), (f.pixels[b], f.mask[b])) if m and c]
                if cand:
                    spr.putpixel((cx + xx // 2, cy + yy), max(cand, key=lambda c: lum[c]))
    for i in range(23):           # dashboard gauge needles (draw_dashboard 1ee16: frame 92 + value/4)
        nm = 'ndl' + '123456789abcdefghijklmn'[i]
        f = dash[nm]
        n = 23 + i
        half(f, (n % 10) * 32 + NEEDLE_AX - f.hx // 2, (n // 10) * 24 + NEEDLE_AY - f.hy)
    half(dash['olon'], (46 % 10) * 32, (46 // 10) * 24)
    half(dash['zero'], (47 % 10) * 32, (47 // 10) * 24)      # 47: kill tally, the small Zero (hud_draw_kill_tally 1f200)
    half(dash['ltar'], (48 % 10) * 32, (48 // 10) * 24)      # 48 / 49: enemy-plane warning arrows (FUN_1f21a), 16x5
    half(dash['rtar'], (49 % 10) * 32, (49 // 10) * 24)
    spr.save(os.path.join(out, 'panelspr.png'))

    make_fpv(out, dash, flat, lum)

    # preview with sample values: bombs 30, planes 3, score 0001234
    prev = panel.convert('RGB').crop((0, 0, 320, 37))
    def put_digit(n, x, y, white):
        for j, row in enumerate(DIGITS[n]):
            for i, ch in enumerate(row):
                if ch == '#':
                    prev.putpixel((x + i, y + j), pal[WHITE if white else DGREY])
    for i, dgt in enumerate([3, 0]):
        put_digit(dgt, PANEL_POS['ammo'][i][0], PANEL_POS['ammo'][i][1], False)
    put_digit(3, *PANEL_POS['lives'], False)
    ic = spr.crop((0, 48, 32, 56)).convert('RGB'); icm = spr.crop((0, 48, 32, 56))
    for yy in range(8):
        for xx in range(32):
            if icm.getpixel((xx, yy)):
                prev.putpixel((PANEL_POS['icon'][0] + xx, PANEL_POS['icon'][1] + yy), ic.getpixel((xx, yy)))
    for i, dgt in enumerate([0, 0, 0, 1, 2, 3, 4]):
        glyph_rgb(prev, wdig[dgt], PANEL_POS['score'][0] + i * PANEL_POS['score_pitch'], PANEL_POS['score'][1], pal[WHITE])
    for i, dgt in enumerate([0, 7]):
        glyph_rgb(prev, wdig[dgt], PANEL_POS['kills'][i][0], PANEL_POS['kills'][i][1], pal[WHITE])
    os.makedirs(os.path.join(out, '..', 'build'), exist_ok=True)
    prev.resize((1280, 148), Image.NEAREST).save(os.path.join(out, '..', 'build', 'panel_preview.png'))


# ---------------------------------------------------------------------------------------------------------------------
# 3-D forward view (FUN_1417e, reverse-engineering/notes/forward_view.md): every shape is centred on hires x 319, so the frames are
# halved horizontally and pre-clipped to the window here. Window: hires x 258..380 = panel x 130..189 (60 px),
# rows 7..31.
FPV_X0 = 259
DASH_NAMES = ('misl bomb torp olof olon targ bnum wnum ltar rtar 3dl0 3dl1 3dl2 3dl3 3dl4 3dl5 3dl6 3dl7 3dl8 3dl9 '
              'dug0 dug1 dug2 dug3 dug4 dug5 dug6 hut0 hut1 hut2 hut3 hut4 hut5 hut6 huta hutb hutc hutd hute hutf hutg '
              'pil0 pil1 pil2 pil3 pil4 pil5 pil6 pila pilb pilc pild pile pilf pilg towr dec0 dec1 dec2 dec3 '
              '3dca 3dcb 3dcc 3dcd 3dce 3dcf 3dcg 3dch 3dci 3dcj 3dck 3dcl 3dcm 3dcn 3dco 3dcp '
              '3dta 3dtb 3dtc 3dtd 3dte 3dtf 3dtg 3dth 3dti 3dtj 3dtk 3dtl 3dtm 3dtn 3dto 3dtp ndl1 ndl2 ndl3').split()
FPV_DASH_USED = [5] + list(range(15, 27)) + list(range(28, 34)) + list(range(35, 41)) + list(range(42, 48)) + \
    list(range(49, 55)) + list(range(56, 95))
ZR_A, ZR_B = '0111222334455 6kkllmmnnnooopp'.replace(' ', ''), 'deeeffffghhiij77889 9aaabbb00'.replace(' ', '')


def make_fpv(out, dash, flat, lum):
    frames = []                                   # (frame, mode) in sheet order

    def add(f):
        frames.append(f)
        return len(frames) - 1
    c_dash = [255] * 95
    for i in FPV_DASH_USED:
        c_dash[i] = add(dash[DASH_NAMES[i]])
    c_ship = []
    for bank, l, r in (('cruiseship.shp', 'cl', 'cr'), ('destroyer.shp', 'db', 'ds'), ('battleship.shp', 'bb', 'bs')):
        b = {f.name: f for f in ppkc.parse(rpck.load(os.path.join(SHAPES, bank)))}
        for pre in (l, r):                        # dir >= 0, then dir < 0; sizes 1..8 (S2 0..7)
            for n in range(1, 9):
                c_ship.append(add(b[pre + str(n)]))
    c_arrow = [add(dash['ltar']), add(dash['rtar'])]   # enemy-plane warning (FUN_1f21a), drawn at (320,10): 1 px off here
    assert len(ZR_A) == 28 and len(ZR_B) == 28
    zr, c_zr = {}, []
    for j in range(3):                            # G_273ac[j*56 + i] = zr<1+j><A[i]>, [j*56 + 28 + i] = zr<1+j><B[i]>
        for tab in (ZR_A, ZR_B):
            for ch in tab:
                nm = 'zr%d%s' % (j + 1, ch)
                if nm not in zr:
                    zr[nm] = add(dash[nm])
                c_zr.append(zr[nm])
    # The game composes the view itself and copies it to the screen: per shape the rows that hold pixels, as the
    # 16-px screen words c0..c0+nc-1 of the 64 px around the 60-px window (panel x 128..191), each word as mask
    # (1 = opaque) + 4 bitplanes. top = first row relative to the reference row Y.
    hdr, bits = [], []
    for f in frames:
        left = 319 - f.hx
        grid = {}
        for yy in range(f.h):
            for lx in range(60):                  # panel pixel lx = hires FPV_X0 + 2*lx, +1
                cand = []
                for xh in (FPV_X0 + 2 * lx, FPV_X0 + 2 * lx + 1):
                    xx = xh - left
                    if 0 <= xx < f.w and f.mask[yy * f.w + xx]:
                        cand.append((f.pixels[yy * f.w + xx] & 15) or BOXBLACK)   # opaque colour 0 = black (11)
                if cand:
                    grid[(lx + 2, yy - f.hy)] = max(cand, key=lambda c: lum[c])   # (+2: the window starts 2 px into a screen word)
        if not grid:
            hdr.append((0, 0, 0, 0, 0, 0))
            continue
        ys = [y for _, y in grid]; cs = [x >> 4 for x, _ in grid]
        y0, y1, c0, c1 = min(ys), max(ys), min(cs), max(cs)
        assert -128 <= y0 and len(bits) < 65536
        solid = y1 - y0 + 1                       # first row from which all rows cover the whole window (px 2..61)
        while solid > 0 and all((x, y0 + solid - 1) in grid for x in range(2, 62)):
            solid -= 1
        hdr.append((y0, y1 - y0 + 1, c0, c1 - c0 + 1, solid, len(bits)))
        for y in range(y0, y1 + 1):
            for c in range(c0, c1 + 1):
                w = [0] * 5
                for b in range(16):
                    v = grid.get((c * 16 + b, y))
                    if v is not None:
                        w[0] |= 0x8000 >> b
                        for pl in range(4):
                            if v >> pl & 1:
                                w[1 + pl] |= 0x8000 >> b
                bits += w
    with open(os.path.join(out, '..', 'fpv_data.h'), 'w') as fp:
        fp.write('// generated by tools/make_panel.py: forward view shapes (halved, clipped to the 60-px window)\n')
        fp.write('#define FPV_SHAPES %d\n' % len(frames))
        for nm, t in (('c_fpv_dash', c_dash), ('c_fpv_ship', c_ship), ('c_fpv_zr', c_zr), ('c_fpv_arrow', c_arrow)):
            fp.write('static const u8 %s[%d] = { %s };\n' % (nm, len(t), ', '.join(str(v) for v in t)))
        nd = iff.read_ilbm(rpck.load(os.path.join(SHAPES, 'nightdash')))[4]
        def ste_word(rgb):
            w = 0
            for c in rgb:
                v = c >> 4
                w = (w << 4) | (v >> 1) | ((v & 1) << 3)
            return w
        fp.write('// the panel palette at night (nightdash CMAP, same indices as the day palette), STE colour words\n')
        fp.write('static const u16 c_night_dash[16] = { %s };\n' % ', '.join('0x%03x' % ste_word(c) for c in nd[:16]))
        fp.write('struct fpv_shape_t { s8 top; u8 rows, c0, nc, solid; u16 ofs; };\n')
        fp.write('static const fpv_shape_t c_fpv_hdr[%d] = {\n%s };\n' % (len(hdr), ',\n'.join(
            ' '.join('{ %d, %d, %d, %d, %d, %d },' % h for h in hdr[i:i + 6]).rstrip(',') for i in range(0, len(hdr), 6))))
        fp.write('static const u16 c_fpv_bits[%d] = {\n%s };\n' % (len(bits), ',\n'.join(
            ', '.join('0x%04x' % v for v in bits[i:i + 20]) for i in range(0, len(bits), 20))))
    print('fpv:', len(frames), 'shapes,', len(bits) * 2, 'bytes')


# top-left positions of the dynamic digits in panel pixels (from the Amiga coordinates / 2, tuned by eye)
PANEL_POS = {
    'ammo': [(19, 20), (31, 20)],          # white boxes x 16-25 / 28-37, rows 19-27
    'lives': (61, 20),                     # white box x 58-66
    'icon': (12, 11),                      # black bar x 14-39, rows 10-16 (icon's own left columns are empty)
    'score': (253, 11),                    # Amiga: x=512 - hot 8 + 2, y=11, 14 hires px per digit
    'score_pitch': 7,
    'kills': [(251, 21), (258, 21)],       # Amiga: x=508/522 - 6, y=21 (planes shot down, G_252cf)
}

if __name__ == '__main__':
    main(sys.argv[1])
