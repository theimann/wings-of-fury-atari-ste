"""Message line font for the STE prototype: ASCII 32..95 (64 glyphs, classic 5x7) in 16x8 cells (EMX), drawn over the
black separator strip, which is shown with the panel palette: index 15 = its light grey (the palette is copied from
sepbar.png, the indices are kept by the cutter).
Usage: make_tfont.py <sepbar png (palette)> <out png>"""
import sys
from PIL import Image

CW, CH, COLS, INK = 16, 8, 8, 15

# columns left to right, bit 0 = top row
GLYPHS = """
00 00 00 00 00|00 00 5F 00 00|00 07 00 07 00|14 7F 14 7F 14|24 2A 7F 2A 12|23 13 08 64 62|36 49 55 22 50|00 05 03 00 00
00 1C 22 41 00|00 41 22 1C 00|14 08 3E 08 14|08 08 3E 08 08|00 50 30 00 00|08 08 08 08 08|00 60 60 00 00|20 10 08 04 02
3E 51 49 45 3E|00 42 7F 40 00|42 61 51 49 46|21 41 45 4B 31|18 14 12 7F 10|27 45 45 45 39|3C 4A 49 49 30|01 71 09 05 03
36 49 49 49 36|06 49 49 29 1E|00 36 36 00 00|00 56 36 00 00|08 14 22 41 00|14 14 14 14 14|00 41 22 14 08|02 01 51 09 06
32 49 79 41 3E|7E 11 11 11 7E|7F 49 49 49 36|3E 41 41 41 22|7F 41 41 22 1C|7F 49 49 49 41|7F 09 09 09 01|3E 41 49 49 7A
7F 08 08 08 7F|00 41 7F 41 00|20 40 41 3F 01|7F 08 14 22 41|7F 40 40 40 40|7F 02 0C 02 7F|7F 04 08 10 7F|3E 41 41 41 3E
7F 09 09 09 06|3E 41 51 21 5E|7F 09 19 29 46|46 49 49 49 31|01 01 7F 01 01|3F 40 40 40 3F|1F 20 40 20 1F|3F 40 38 40 3F
63 14 08 14 63|07 08 70 08 07|61 51 49 45 43|00 7F 41 41 00|02 04 08 10 20|00 41 41 7F 00|04 02 01 02 04|40 40 40 40 40
"""

def main(palsrc, out):
    glyphs = [[int(c, 16) for c in g.split()] for line in GLYPHS.strip().splitlines() for g in line.split('|')]
    assert len(glyphs) == 64
    img = Image.new('P', (CW * COLS, CH * 8), 0)
    img.putpalette(Image.open(palsrc).getpalette())
    for n, g in enumerate(glyphs):
        ox, oy = (n % COLS) * CW, (n // COLS) * CH
        for x, col in enumerate(g):
            for y in range(7):
                if col >> y & 1:
                    img.putpixel((ox + x, oy + y), INK)
    img.save(out)
    print('ticker font sheet', img.size)

if __name__ == '__main__':
    main(*sys.argv[1:3])
