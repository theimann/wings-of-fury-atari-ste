"""Intro text scroller data for the STE build (FUN_17e80, reverse-engineering/notes/frontend.md 1.1): the Amiga's 'newarmyfont' and the
53 text lines from the game binary (0x17494..), in one file:
  u16 font bytes, font (as the Amiga file: u16 height, u8 first, u8 last, u8 width[n] padded even, glyph rows as
  16-bit words), u16 line count, the lines (NUL terminated), padded even.
Usage: make_intro.py <out file>"""
import os, struct, sys
sys.path.insert(0, os.path.dirname(__file__))
import rpck

ROOT = os.path.join(os.path.dirname(__file__), '..')
GAME = os.path.join(ROOT, 'amiga-original')
TEXT0, LINES = 0x17494, 53

if __name__ == '__main__':
    font = rpck.load(os.path.join(GAME, 'newarmyfont'))
    img = open(os.path.join(ROOT, 'reverse-engineering/wings.bin'), 'rb').read()
    p, lines = TEXT0 - 0x10000, []
    for _ in range(LINES):
        e = img.index(b'\0', p)
        lines.append(img[p:e])
        p = e + 1
    assert lines[0].strip() == b'A Time of Fury' and lines[-1].endswith(b'above...')
    out = struct.pack('>H', len(font)) + font + struct.pack('>H', len(lines)) + b''.join(l + b'\0' for l in lines)
    out += b'\0' * (len(out) & 1)
    open(sys.argv[1], 'wb').write(out)
    print('intro.dat', len(out), 'bytes,', len(lines), 'lines')
