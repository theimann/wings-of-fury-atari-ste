"""Help-screen font sheet for the STE prototype: ASCII 32..95 (64 glyphs) in 16x10 cells (IMSPR), white with a dark
outline (palette index 0 is the sprite key, so the outline uses the darkest other colour of the level palette).
Usage: make_font.py <level png (palette)> <out png>"""
import sys
from PIL import Image, ImageDraw, ImageFont

CW, CH, COLS = 16, 10, 8

def main(level, out):
    pal = Image.open(level).getpalette()[:48]
    cols = [tuple(pal[i * 3:i * 3 + 3]) for i in range(16)]
    white = max(range(1, 16), key=lambda i: sum(cols[i]))
    dark = min(range(1, 16), key=lambda i: sum(cols[i]))
    font = ImageFont.load_default_imagefont() if hasattr(ImageFont, 'load_default_imagefont') else ImageFont.load_default()
    img = Image.new('P', (CW * COLS, CH * 8), 0)
    img.putpalette(pal + [0] * (768 - 48))
    for n in range(64):
        ch = chr(32 + n)
        g = Image.new('L', (CW, CH + 4), 0)
        ImageDraw.Draw(g).text((1, 0), ch, fill=255, font=font)
        gp = g.point(lambda v: 255 if v > 100 else 0).load()
        ox, oy = (n % COLS) * CW, (n // COLS) * CH
        on = {(x, y) for y in range(CH) for x in range(8) if gp[x, y + 1]}
        for (x, y) in on:                      # outline first, then the glyph
            for dx in (-1, 0, 1):
                for dy in (-1, 0, 1):
                    xx, yy = x + dx, y + dy
                    if 0 <= xx < 9 and 0 <= yy < CH and (xx, yy) not in on:
                        img.putpixel((ox + xx, oy + yy), dark)
        for (x, y) in on:
            img.putpixel((ox + x, oy + y), white)
    img.save(out)
    print('font sheet', img.size, 'white', white, 'dark', dark)

if __name__ == '__main__':
    main(*sys.argv[1:3])
