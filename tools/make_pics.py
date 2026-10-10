"""Start-up pictures for the STE build: the Amiga's 320x200 pictures (broderbund 16 colours, wingstitle and
creditscreen 32 colours) reduced to 16 STE colours, as raw screens: 16 palette words (STE format) + 32000 bytes of
ST low-res screen memory (4 interleaved bitplanes).
Usage: make_pics.py <graphics dir> <out dir>      writes broder.pic, title.pic, credits.pic and the menu pictures
(rank.pic, brief.pic, hiscore.pic: see make_menu_pics)"""
import os, sys
from PIL import Image

PICS = (('broderbund.png', 'broder.pic'), ('wingstitle.png', 'title.pic'), ('creditscreen.png', 'credits.pic'))


def ste_word(rgb):
    w = 0
    for c in rgb:
        v = c >> 4                                  # 4 bits per gun; the STE keeps the lowest bit in bit 3
        w = (w << 4) | (v >> 1) | ((v & 1) << 3)
    return w


def convert(src, dst):
    im = Image.open(src).convert('RGB')
    assert im.size == (320, 200), im.size
    im = im.point(lambda v: (v >> 4) * 17)          # the Amiga's (and the STE's) 4 bits per gun
    q = im.quantize(colors=16, method=Image.MEDIANCUT, dither=Image.NONE)
    pal = q.getpalette()[:48]
    cols = [tuple(pal[i * 3:i * 3 + 3]) for i in range(16)]
    px = list(q.getdata())
    # colour 0 = the border colour: make it the darkest colour
    dark = min(range(16), key=lambda i: sum(cols[i]))
    if dark != 0:
        cols[0], cols[dark] = cols[dark], cols[0]
        px = [dark if p == 0 else 0 if p == dark else p for p in px]
    out = bytearray()
    for c in cols:
        out += ste_word(c).to_bytes(2, 'big')
    for y in range(200):
        for x0 in range(0, 320, 16):
            planes = [0, 0, 0, 0]
            for b in range(16):
                p = px[y * 320 + x0 + b]
                for pl in range(4):
                    if p >> pl & 1:
                        planes[pl] |= 0x8000 >> b
            for w in planes:
                out += w.to_bytes(2, 'big')
    assert len(out) == 32032
    open(dst, 'wb').write(out)
    used = len(set(px))
    print(os.path.basename(dst), 'colours', used)
    return q, cols, px


# ---------------------------------------------------------------------------------------------------------------------
# Menu pictures shown inside the game (reverse-engineering/notes/frontend.md 2, 3, 5). Each file is a 32032-byte screen followed by
# extra strips in screen format (16-px word groups of 4 plane words, row by row):
#   rank.pic   'selectrank' without its "RETURN FROM R&R" line (no saved games); extras: for each of the 7 ranks the
#              192x9 strip at (64, 91 + 10 N) highlighted (bar 'rnkN' behind the text), then the 7 plain strips
#   brief.pic  the briefing panel (world.shp 'rank', 256x95 hires, halved by averaging) at (96, 54); extras: the 7
#              rank names (0x25860) as 80x12 strips for x 144 (text at x 148), then the digits 0..9 as 32x12 strips
#              for x 160 (text at x 170), both in 'newarmyfont' halved by averaging, colour AAA
#   hiscore.pic  'hiscore.iff' (320x75) above 'hiscoreslab' (640x200 hires, halved by averaging; its first 124 rows
#              from row 76)
import struct
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import iff, ppkc, rpck

ROOT = os.path.join(os.path.dirname(os.path.abspath(__file__)), '..')
GAME = os.path.join(ROOT, 'amiga-original')
RANK_NAMES = ['Midshipman', 'Ensign', 'Lt. Jr. Gr.', 'Lieutenant', 'Lt.Commd', 'Commander', 'Captain']   # 0x25860
BRIEF_PAL = [(0, 0, 0), (0, 0xa0, 0xf0), (0xd0, 0x30, 0), (0, 0x30, 0xd0), (0x40, 0x40, 0x40), (0x60, 0x60, 0x60),
             (0x80, 0x80, 0x80), (0xa0, 0xa0, 0xa0)]          # 0x2587c


def quant16(im):
    """RGB image -> (palette of 16 rgb, index list); index 0 = the darkest colour"""
    im = im.point(lambda v: min(255, ((v + 8) >> 4) * 17))
    q = im.quantize(colors=16, method=Image.MEDIANCUT, dither=Image.NONE)
    pal = q.getpalette()[:48]
    cols = [tuple(pal[i * 3:i * 3 + 3]) for i in range(16)]
    px = list(q.getdata())
    dark = min(range(16), key=lambda i: sum(cols[i]))
    if dark != 0:
        cols[0], cols[dark] = cols[dark], cols[0]
        px = [dark if p == 0 else 0 if p == dark else p for p in px]
    return cols, px


def planar(px, w, x0, y0, cw, ch):
    """cw x ch pixels at (x0, y0) of the index list (row length w) -> screen-format bytes; cw a multiple of 16"""
    out = bytearray()
    for y in range(y0, y0 + ch):
        for xg in range(x0, x0 + cw, 16):
            planes = [0, 0, 0, 0]
            for b in range(16):
                p = px[y * w + xg + b]
                for pl in range(4):
                    if p >> pl & 1:
                        planes[pl] |= 0x8000 >> b
            for v in planes:
                out += v.to_bytes(2, 'big')
    return out


def pic_file(cols, px, w, extras):
    out = bytearray()
    for c in cols:
        out += ste_word(c).to_bytes(2, 'big')
    out += planar(px, w, 0, 0, 320, 200)
    assert len(out) == 32032
    for (x0, y0, cw, ch) in extras:
        out += planar(px, w, x0, y0, cw, ch)
    return out


def ilbm_rgb(name):
    w, h, planes, pixels, pal = iff.read_ilbm(rpck.load(os.path.join(GAME, 'shapes', name)))
    im = Image.new('RGB', (w, h))
    im.putdata([tuple(pal[p]) for p in pixels])
    return im, pixels, pal


def font_text(text, colour):
    """the string in 'newarmyfont' (hires): RGB image, cursor at (0, 0)"""
    d = rpck.load(os.path.join(GAME, 'newarmyfont'))
    h, first, last = struct.unpack('>HBB', d[:4])
    n = last - first + 1
    ws = list(d[4:4 + n])
    off = 4 + n + (n & 1)
    im = Image.new('RGB', (sum((ws[ord(c) - first] or 10) + 1 for c in text) + 2, h))
    x = 0
    for c in text:
        i = ord(c) - first
        w = ws[i]
        if w:
            o = off + sum(((v + 15) >> 4) * 2 * h for v in ws[:i])
            gw = (w + 15) >> 4
            for r in range(h):
                bits = int.from_bytes(d[o + r * gw * 2:o + (r + 1) * gw * 2], 'big')
                for b in range(w):
                    if bits >> (gw * 16 - 1 - b) & 1:
                        im.putpixel((x + b, r), colour)
        x += (w or 10) + 1
    return im


def halve(im):
    return im.resize((im.size[0] // 2, im.size[1]), Image.BOX)


def make_menu_pics(outdir):
    # rank select
    base, pixels, pal = ilbm_rgb('selectrank')
    bars = {f.name: f for f in ppkc.parse(rpck.load(os.path.join(GAME, 'shapes', 'selectrank.shp')))}
    tall = Image.new('RGB', (320, 200 + 8 * 9))
    tall.paste(base, (0, 0))
    for n in range(8):                                     # (line 7 = RETURN FROM R&R) the bar is XORed in: it has pixels only where the picture is 0
        f = bars['rnk%d' % n]
        strip = base.crop((64, 91 + 10 * n, 256, 100 + 10 * n))
        for yy in range(9):
            for xx in range(192):
                b = f.pixels[yy * f.w + xx]
                if b:
                    strip.putpixel((xx, yy), tuple(pal[pixels[(91 + 10 * n + yy) * 320 + 64 + xx] ^ b]))
        tall.paste(strip, (64, 200 + 9 * n))
    cols, px = quant16(tall)
    extras = [(64, 200 + 9 * n, 192, 9) for n in range(8)] + [(64, 91 + 10 * n, 192, 9) for n in range(8)]
    open(os.path.join(outdir, 'rank.pic'), 'wb').write(pic_file(cols, px, 320, extras))

    # briefing
    world = {f.name: f for f in ppkc.parse(rpck.load(os.path.join(GAME, 'shapes', 'world.shp')))}
    r = world['rank']
    panel = Image.new('RGB', (r.w, r.h))
    panel.putdata([BRIEF_PAL[p & 7] for p in r.pixels])
    tall = Image.new('RGB', (320, 200 + 7 * 12 + 12))
    tall.paste(halve(panel), (96, 54))
    for n, name in enumerate(RANK_NAMES):                  # names for x 144..223 (text starts at hires 296 = lores 148)
        t = Image.new('RGB', (160, 12))
        t.paste(font_text(name, BRIEF_PAL[7]), (8, 0))
        strip = tall.crop((144, 61, 224, 73))              # over the panel as it is there (its right border ends in this strip)
        ht = halve(t)
        strip.paste(ht, (0, 0), ht.convert('L').point(lambda v: 255 if v else 0))
        tall.paste(strip, (144, 200 + 12 * n))
    for dg in range(10):                                   # digits for x 160..191 (text at hires 340 = lores 170)
        t = Image.new('RGB', (64, 12))
        t.paste(font_text(str(dg), BRIEF_PAL[7]), (20, 0))
        tall.paste(halve(t), (dg * 32, 200 + 84))
    cols, px = quant16(tall)
    extras = [(144, 200 + 12 * n, 80, 12) for n in range(7)] + [(dg * 32, 284, 32, 12) for dg in range(10)]
    open(os.path.join(outdir, 'brief.pic'), 'wb').write(pic_file(cols, px, 320, extras))

    # hall of fame
    banner, _, _ = ilbm_rgb('hiscore.iff')
    slab, _, _ = ilbm_rgb('hiscoreslab')
    page = Image.new('RGB', (320, 200))
    page.paste(banner, (0, 0))
    page.paste(halve(slab).crop((0, 0, 320, 124)), (0, 76))
    # 16 colours for both parts: 10 from the banner (with black) and 6 from the marble, so the marble keeps its own
    # grey ramp (quantised together its light veins came out in the banner's gold)
    def some(im, n):
        q = im.point(lambda v: min(255, ((v + 8) >> 4) * 17)).quantize(colors=n, method=Image.MEDIANCUT, dither=Image.NONE)
        pal = q.getpalette()[:n * 3]
        return [tuple(pal[i * 3:i * 3 + 3]) for i in range(n)]
    cols = [(0, 0, 0)]
    for c in some(banner, 10) + some(halve(slab).crop((0, 0, 320, 124)), 6):
        if c not in cols and len(cols) < 16:
            cols.append(c)
    while len(cols) < 16:
        cols.append((0, 0, 0))
    def near(c, cand):
        return min(cand, key=lambda k: sum((a - b) ** 2 for a, b in zip(c, cols[k])))
    greys = [k for k in range(16) if max(cols[k]) - min(cols[k]) <= 0x44]
    px = []
    for y in range(200):
        for x in range(320):
            px.append(near(page.getpixel((x, y)), greys if y >= 76 else range(16)))
    open(os.path.join(outdir, 'hiscore.pic'), 'wb').write(pic_file(cols, px, 320, []))
    return tall


if __name__ == '__main__':
    gfx, outdir = sys.argv[1:3]
    os.makedirs(outdir, exist_ok=True)
    prev = Image.new('RGB', (960, 200))
    for i, (s, d) in enumerate(PICS):
        q, cols, px = convert(os.path.join(gfx, s), os.path.join(outdir, d))
        im = Image.new('RGB', (320, 200))
        im.putdata([cols[p] for p in px])
        prev.paste(im, (i * 320, 0))
    make_menu_pics(outdir)
    if len(sys.argv) > 3:
        prev.save(sys.argv[3])
