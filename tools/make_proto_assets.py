"""Build STE prototype source assets (8-bit indexed PNGs, 16 colours used) for AGT's agtcut, plus flight_data.h.

Outputs into <out>:
  level_<x>.png - per map: level strip incl. sky up to the flight ceiling (EXTRA rows above the 240-line base view)
                  and the source band below (1/8 view, bob, waves, wrecked huts); shared palette
  map_<x>.dat  - per map: runtime data (geometry, map cells, building/flag/wave tables), big-endian words
  hellcat.png  - plane frames in fixed cells; the original hotspot sits at the cell anchor (PL_AX, PL_AY)
  wheels.png   - landing gear overlay frames, same scheme (WH_AX, WH_AY)
  info.txt     - summary
  <hdr>        - C header: geometry, flight tables (16.16), frame index tables, map cells
Usage: make_proto_assets.py <maps dir> <out dir> <header path> [map letters, default a]

Coordinates (see reverse-engineering/notes/render_sound.md 4, 5.3, 5.4 and player.md 9):
  world y is up-positive. The player plane origin is drawn at row WATER_ROW - y (Amiga FUN_103a6: refY - y);
  other world objects (explosions etc.) at BASE_ROW - y with BASE_ROW = WATER_ROW + 11 (FUN_15174: refY + 11 - y).
  map object hotspots at row EXTRA + 200 + jitter*4 (Amiga: 151 + jitter*4), wave strip top at EXTRA + 200.
  image x = world x + MARGIN.
"""
import json, os, struct, sys
from PIL import Image
sys.path.insert(0, os.path.dirname(__file__))
import iff, ppkc, rpck
from render_maps import load_map, world_names, INVISIBLE

ROOT = os.path.join(os.path.dirname(__file__), '..')
SHAPES = os.path.join(ROOT, 'amiga-original/shapes')
VIEW_H = 240
# playfield lines above the 37-line cockpit panel (the last SEP_H show black under the panel palette).
# Default 163 -> 200 lines in all (the Amiga playfield is 162 lines).
PF_H = int(os.environ.get('WOF_PF_H', '163'))
SEP_H = 8                   # separator rows: palette index 0 = sky in the playfield palette, black in the panel palette
EXTRA = 88                  # sky above the base view: the normal view never goes above altitude 186 (1/8 view above)
WATER_ROW = EXTRA + 200     # Amiga waterline row 151
BASE_ROW = WATER_ROW + 11   # row of world y = 0
OBJ_WEIGHT = 200              # palette weight per pixel of each distinct map object frame
MARGIN = 1024              # open sea beyond both map ends (the original lets you fly on indefinitely)

PITCH = "hc0a hc0a hc09 hc09 hc08 hc08 hc07 hc07 hc06 hc05 hc05 hc04 hc04 hc03 hc03 hc02 hc02 hc01 hc01 hc01".split()
LOOP_L = "hc0f hc28 hc29 hc2a hc2b hc2c hc2d hc2e hc2f hc30 hc31 hc32 hc32 hc32 hc3b hc3b hc3c hc3d hc3e hc3f hc2d hc2c hc2b hc2a hc29 hc28".split()
LOOP_R = "hc05 hc22 hc23 hc24 hc25 hc26 hc27 hc37 hc38 hc39 hc3a hc3b hc3b hc3b hc32 hc32 hc33 hc34 hc35 hc36 hc27 hc26 hc25 hc24 hc23 hc22".split()
DECK = "hc21 hc20 hc1f hc1e hc1d hc1c hc1b hc40".split()
WHL = "wh14 wh14 wh13 wh13 wh12 wh12 wh11 wh11 wh10 wh0f wh0f wh0e wh0e wh0d wh0d wh0c wh0c wh0b wh0b wh0b".split()
WHR = "wh0a wh0a wh09 wh09 wh08 wh08 wh07 wh07 wh06 wh05 wh05 wh04 wh04 wh03 wh03 wh02 wh02 wh01 wh01 wh01".split()
FRAMENO = [10, 10, 9, 9, 8, 8, 7, 7, 6, 5, 5, 4, 4, 3, 3, 2, 2, 1, 1, 1]
CLR = [2, 12, 10, 6, 4, 2, 5, 7, 9, 12, 14, 5]
GEAR = [5, 4, 3, 3, 3, 5, 3, 2, 1, 0, 0, 10]
TURNCLR = [2, 2, 4, 6, 10, 11]

PL_CW, PL_CH, PL_AX, PL_AY = 128, 48, 64, 24
# AGT draws the entities of a layer by descending x: the anchors give the original order torpedo, gear, plane
# (PL_AX 64 > WH_AX 62 > TP_AX 60)
WH_CW, WH_CH, WH_AX, WH_AY = 96, 32, 62, 12
TP_AX = 60
EL_AX, EL_AY = 28, 0     # elevator sheet anchor
FX_CW, FX_CH, FX_AX, FX_AY = 48, 32, 20, 22
WP_CW, WP_CH, WP_AX, WP_AY = 112, 80, 48, 40     # weapons sheet (IMSPR): rockets, torpedo, weapon-select menu
GN_CW, GN_CH, GN_AX, GN_AY = 64, 32, 32, 24      # AA guns gun0..6 / gnf0..6 (world 0x81..0x8e), hotspot (32,24)
ZP_CW, ZP_CH, ZP_AX, ZP_AY = 112, 48, 56, 24     # enemy planes (japplane.shp, IMSPR): hotspots range -7..41 x, -3..15 y
AA_TAB_ADDR, AA_TAB_PRE, AA_TAB_LEN = 0x24b6c, 24, 320   # FUN_14db8 aim table, flat incl. spill-over bytes
SO_CW, SO_CH, SO_AX, SO_AY = 48, 16, 24, 10      # soldiers guy0..7 (right) / guy9..gy10 (left), hotspot (24,10)
CR_CW, CR_CH, CR_AX, CR_AY = 32, 16, 17, 45     # deck crew poses fgy0..fgyf (hotspot ~41-45 px above the frame)
HUD_CW, HUD_CH = 16, 8                          # digits, rope segments, bomb icon (top-left anchored)
FX_NAMES = ['bom%x' % i for i in range(12)] + ['exp%d' % i for i in range(6)] + ['spl%d' % i for i in range(7)] + ['ric0'] + ['smk%d' % i for i in range(6)] + \
    ['balb', 'balr', 'balw']             # victory ceremony balloons (FUN_1557c)
WRECK_ROW0, WRECK_ROWS = (EXTRA + 200 - 16) // 16, 4    # tile rows covering huts (hotspot at waterline + jitter*4)
# 1/8 high-altitude view (render_sound.md 4): pre-rendered miniature world in extra rows below the level
MINI_H = (PF_H + 15) // 16 * 16     # one playfield of rows; the camera never scrolls vertically here
MINI_SEA = PF_H - SEP_H - 11        # top of the flat sea band = the normal view's wave-strip top (Amiga line 151)
MINI_X0 = 208                       # mini image x of world x = -MARGIN: with the 128 px of sea margin, 336 px of
                                    # open sea left of the map, a full screen for a camera that stays >= 16
MI_CW, MI_CH, MI_AX, MI_AY = 32, 16, 16, 8      # mini plane sheet cells, hotspot
MINI_PLANE_N0, MINI_PLANE_N1 = 0x28, 0x48       # 8thscale indices used by draw_player_plane (lpn*)
assert WATER_ROW % 16 == 0, "waves/bob tile animation needs a tile-aligned waterline"
WAVE_ROW0, WAVE_PHASES = WATER_ROW // 16, 12    # wave strip tile row (waterline is tile-aligned), frames
MINI_WRECK_ROW0, MINI_WRECK_ROWS = (MINI_SEA - 16) // 16, 2      # mini tile rows covering huts (wrecked copy appended)
BAND_ROWS = max(MINI_H // 16 + MINI_WRECK_ROWS, 15)   # source band below the live area (15: bob 8 + carrier 7, pillbox masks)
ALL_MAPS = 'abcdefghijklmno'
# enemy ship records (FUN_12d5a): anchor type -> (x0 in px relative to the anchor cell x, width in px):
# x0 = anchor byte offset - 32 (transport - 16), x1 = x0 + 160 / 192 / 32 / 156 byte offsets (4 px each)
SHIP_X = {0xe4: (-128, 640), 0x10d: (-128, 768), 0xcc: (-64, 128), 0xf2: (-128, 624)}
PILL_ROW, PILL_COLS = WATER_ROW // 16 - 1, 3    # pillboxes (12 px, jitter 0 in every map) sit in this tile row
BOB_COLS = 49                                  # carrier bob block width (48 or 49 by tile alignment)
WAVE_PERIOD = 96 // 16                         # open-sea wave strip repeats every 96 px
WAVE_SEA_LEN = 25 + WAVE_PERIOD   # waves_apply copies <= 25 columns


def bank(name):
    return {f.name: f for f in ppkc.parse(rpck.load(os.path.join(SHAPES, name)))}


def put(canvas, f, x, y, pal):
    W, H = len(canvas[0]), len(canvas)
    for j in range(f.h):
        yy = y + j
        if not 0 <= yy < H:
            continue
        row = canvas[yy]
        for i in range(f.w):
            k = j * f.w + i
            if f.mask[k]:
                xx = x + i
                if 0 <= xx < W:
                    row[xx] = pal[f.pixels[k]]


# enemy ship banks (FUN_13252 + the cell-type table built after it): the cell types after the world list's 184 entries
# index these banks in this order, each with its name list from the exe (A4-relative)
SHIP_BANKS = [(0xb8, 'cruiseship.shp', -29486), (0xd0, 'destroyer.shp', -29598), (0xeb, 'japcarrier.shp', -29654),
              (0xf8, 'battleship.shp', -29758)]
_ship_frames = None
_ship_names = {}


def ship_name(t):
    ship_frame(t)
    return _ship_names.get(t)


def ship_frame(t):
    """frame of an enemy ship cell type (>= 0xb8), or None"""
    global _ship_frames
    if _ship_frames is None:
        img = open(os.path.join(ROOT, 'reverse-engineering/wings.bin'), 'rb').read()
        _ship_frames = {}
        for base, fname, off in SHIP_BANKS:
            b = bank(fname)
            i = 0x2af4e + off - 0x10000
            k = 0
            while img[i:i + 4] != b'\0\0\0\0':
                nm = img[i:i + 4].decode('latin1').strip()
                _ship_names[base + k] = nm
                if nm in b:
                    _ship_frames[base + k] = b[nm]
                i += 4
                k += 1
    return _ship_frames.get(t)


def carrier_cells(cells):
    """cell range of the player's carrier (the carrier-surface run around 'rcar'); other runs are enemy ships"""
    r = next(i for i, v in enumerate(cells) if v & 0x8000 and (v >> 2) & 0x1ff == 0x21)
    lo, hi = r, r
    while lo > 0 and cells[lo - 1] & 3 == 1: lo -= 1
    while hi < len(cells) - 1 and cells[hi + 1] & 3 == 1: hi += 1
    return lo, hi


def build_level(cells, world, names, pal, ocean, wreck_huts=False, wave_frame=0, bob=3, pill_mask=0, no_ships=False,
                no_carrier=False):
    W = (len(cells) * 8 + 2 * MARGIN + 15) // 16 * 16
    H = (EXTRA + VIEW_H + 15) // 16 * 16     # whole tile rows (bands are appended below)
    SKY, SEA, SAND = pal[1], pal[5], pal[17]
    # (sky also behind the wave strip: its crests are transparent and show the sky colour on the Amiga)
    canvas = [[SKY] * W if y < WATER_ROW + 11 else [SEA] * W for y in range(H)]
    lo, hi = carrier_cells(cells)
    for i, v in enumerate(cells):                 # 1) map objects at waterline + jitter*4 (render_sound 5.4)
        if not v & 0x8000:
            continue
        t = (v >> 2) & 0x1ff
        if wreck_huts and t == 4:
            t = 5                                 # 'hutb' (wrecked hut)
        if pill_mask and t == 0x0f:
            t = 0x0f + pill_mask                  # pillbox damage state 'pila' + mask (146dc)
        name = names[t] if t < len(names) else None
        f = world.get(name) if t < 0xb8 else (None if no_ships else ship_frame(t))
        if no_carrier and lo - 8 <= i <= hi + 8:
            f = None                              # the own carrier (after it sank)
        if f and (t >= 0xb8 or name not in INVISIBLE):
            cbob = (bob if lo <= i <= hi else 3) if v & 3 == 1 else 0   # carrier: + wave bob (2..4) via FUN_14eac;
                                                                      # enemy ships: fixed at 3 for now
            # render_world: x = cell_x - hot_x in world terms. The asm (1389e) has subq #8,d0; sub hot_x, but its
            # screen x counter starts at 8 - (cam & 7) - 128 for the cell at cam - 288 (137bc..137f8), and the
            # camera is plane_x - 160 (10260): the two 8s cancel. Measured in vAmiga too (shots/elev: the plane
            # and the elevator stand in the middle of the shaft).
            put(canvas, f, MARGIN + i * 8 - f.hx, WATER_ROW + ((v >> 11) & 7) * 4 + cbob - f.hy, pal)
    waves = [world['wav' + c] for c in 'abcdefghijkl']
    x = 0
    while x < W:                                  # 2) wave strip over object bottoms, top = waterline (5.3):
        f = waves[wave_frame]                     #    one frame repeated every 96 px (world-fixed), animated at runtime
        put(canvas, f, x, WATER_ROW, ocean)
        x += f.w
    # 3) beaches (FUN_140e8, after the waves): per island the end pieces 'bchl'/'bchr' (world frames 1/2) at
    #    world alt 11 (= waterline) and a colour-17 sand fill between them, 5 lines from the waterline (measured
    #    in vAmiga: sand on lines 151..155). Island extents = bchl / bchr anchor cells.
    lefts = [MARGIN + i * 8 for i, v in enumerate(cells) if v & 0x8000 and (v >> 2) & 0x1ff == 1]
    rights = [MARGIN + i * 8 for i, v in enumerate(cells) if v & 0x8000 and (v >> 2) & 0x1ff == 2]
    for lx, rx in zip(lefts, rights):
        for y in range(WATER_ROW, WATER_ROW + 5):
            for xx in range(lx, rx + 1):
                canvas[y][xx] = SAND
        for nm, ax in (('bchl', lx), ('bchr', rx)):
            f = world[nm]
            put(canvas, f, ax - f.hx, WATER_ROW - f.hy, pal)
    for y in range(WATER_ROW + 11, H):            # 4) the Amiga playfield ends here; our taller view shows plain sea
        canvas[y] = [SEA] * W
    for y in range(WATER_ROW + 11, WATER_ROW + 11 + SEP_H):   # 5) separator: drawn after the panel palette burst
        canvas[y] = [SKY] * W
    return canvas


def build_mini(cells, eighth, names, pal, W, sea_rgb, wreck_huts=False, no_ships=False, no_carrier=False):
    """1/8 view: sky, map objects (8thscale frame of the same name, hotspot on the waterline, 1 px per cell),
    then the flat colour-10 sea rectangle over the object bottoms (render_sound.md 4 and 5.3). Those lines run
    under the copper's ocean palette: the band measures (0,72,141) in vAmiga = ocean.palette[11]."""
    SKY, SEA10 = pal[1], sea_rgb
    canvas = [[SKY] * W for _ in range(MINI_H)]
    clo, chi = carrier_cells(cells)
    for i, v in enumerate(cells):
        if not v & 0x8000:
            continue
        t = (v >> 2) & 0x1ff
        if wreck_huts and t == 4:
            t = 5                                 # 'hutb'
        name = (names[t] if t < len(names) else None) if t < 0xb8 else (None if no_ships else ship_name(t))
        if no_carrier and clo - 8 <= i <= chi + 8:
            name = None
        f = eighth.get(name)
        if f and name not in INVISIBLE:
            put(canvas, f, MINI_X0 + MARGIN // 8 + i - f.hx, MINI_SEA - f.hy, pal)
    for y in range(MINI_SEA, MINI_SEA + 11):
        canvas[y] = [SEA10] * W
    # beaches (FUN_140e8 in the 1/8 view): one colour-17 sand line on the top row of the sea band between the island
    # ends (measured in vAmiga, tools/vamiga/shots/island_high), plus the 8thscale bchl/bchr pieces
    mx = lambda wx: MINI_X0 + (MARGIN + wx) // 8
    lefts = [i * 8 for i, v in enumerate(cells) if v & 0x8000 and (v >> 2) & 0x1ff == 1]
    rights = [i * 8 for i, v in enumerate(cells) if v & 0x8000 and (v >> 2) & 0x1ff == 2]
    for lx, rx in zip(lefts, rights):
        for xx in range(mx(lx), mx(rx) + 1):
            canvas[MINI_SEA][xx] = pal[17]
        for nm, ax in (('bchl', mx(lx)), ('bchr', mx(rx))):
            f = eighth[nm]
            put(canvas, f, ax - f.hx, MINI_SEA - f.hy, pal)
    return canvas


def d2(a, b):
    return sum((x - y) ** 2 for x, y in zip(a, b))


def choose_palette(weights, n=16, forced=()):
    used = list(weights)
    chosen = list(forced)
    while len(chosen) < n and len(chosen) < len(used):
        best, besterr = None, None
        for c in used:
            if c in chosen:
                continue
            cand = chosen + [c]
            err = sum(w * min(d2(u, k) for k in cand) for u, w in weights.items())
            if besterr is None or err < besterr:
                best, besterr = c, err
        chosen.append(best)
    return chosen


def sheet(frames, mirror_flags, cw, ch, ax, ay, rgbmap, pal, cols=10, xor_frames=()):
    """frames: list of Frame; mirror_flags: same length. Hotspot is placed at (ax, ay) in each cell.
    Frames whose name is in xor_frames are baked with the colour an Amiga XOR blit produces over the sky
    (palette[1 ^ pixel]), e.g. the muzzle flashes (blit_shape_xor)."""
    rows = (len(frames) + cols - 1) // cols
    img = Image.new('P', (cw * cols, ch * rows), 0)
    for n, (f, m) in enumerate(zip(frames, mirror_flags)):
        fr = Image.new('P', (f.w, f.h), 0)
        data = []
        for p, msk in zip(f.pixels, f.mask):
            if not msk:
                data.append(0)
            else:
                src = pal[1 ^ p] if f.name in xor_frames else pal[p]
                c = rgbmap[src] if src in rgbmap else min(range(16), key=lambda k: 0)
                data.append(c if c != 0 else 1)   # index 0 is the transparency key
        fr.putdata(data)
        hx = f.hx
        if m:
            fr = fr.transpose(Image.FLIP_LEFT_RIGHT)
            hx = f.w - 1 - f.hx
        ox, oy = ax - hx, ay - f.hy
        assert 0 <= ox and ox + f.w <= cw and 0 <= oy and oy + f.h <= ch, (f.name, ox, oy)
        img.paste(fr, ((n % cols) * cw + ox, (n // cols) * ch + oy))
    return img, cols, rows


def ffp(v):
    mant = v >> 8; sign = -1 if v & 0x80 else 1; exp = (v & 0x7f) - 64
    return sign * mant / (1 << 24) * (2.0 ** exp) if mant else 0.0


def carr(name, ctype, vals, per_line=16):
    lines = []
    for i in range(0, len(vals), per_line):
        lines.append('\t' + ', '.join(str(v) for v in vals[i:i + per_line]) + ',')
    return f'static const {ctype} {name}[{len(vals)}] =\n{{\n' + '\n'.join(lines) + '\n};\n'


def main(mapdir, out, hdr, letters='a'):
    os.makedirs(out, exist_ok=True)
    # the in-game day palette is 'wingspalette' (FUN_18806; 'palette' is a different file: its colours 6, 10, 11 and
    # the sky do not match the game. Verified against vAmiga: weapon menu yellow f0e060 / shadow 101020, sky 00a0f0)
    amiga_pal = list(iff.read_palette(rpck.load(os.path.join(SHAPES, 'wingspalette'))))
    ocean = iff.read_palette(rpck.load(os.path.join(SHAPES, 'ocean.palette')))
    img = open(os.path.join(ROOT, 'reverse-engineering/wings.bin'), 'rb').read()
    names = world_names(img)
    world, hell = bank('world.shp'), bank('hellcat.shp')
    # the palette always comes from all 15 maps, so builds with any subset of maps share it
    allmaps = []
    for letter in ALL_MAPS:
        mapfile = os.path.join(mapdir, letter + '.map')
        m = open(mapfile, 'rb').read()
        mp = {'letter': letter, 'home_hdr': struct.unpack('>I', m[4:8])[0]}
        _, mp['cells'] = load_map(mapfile)
        mp['canvas'] = build_level(mp['cells'], world, names, amiga_pal, ocean)
        mp['wreck'] = build_level(mp['cells'], world, names, amiga_pal, ocean, wreck_huts=True)
        allmaps.append(mp)
    maps = [mp for mp in allmaps if mp['letter'] in letters]
    live_h = len(maps[0]['canvas'])

    # ---- plane frame set (order defines the sprite frame numbers) ----
    plane = []                       # (name, mirrored)
    def pf(name, mir):
        key = (name, mir)
        if key not in plane:
            plane.append(key)
        return plane.index(key)
    pitch_l = [pf(n, True) for n in PITCH]      # dir -1: engine mirrors the right-facing pitch frames
    pitch_r = [pf(n, False) for n in PITCH]
    loop_l = [pf(n, False) if n in hell else pf('hc28', False) for n in LOOP_L]
    loop_r = [pf(n, False) for n in LOOP_R]
    deck_l = [pf(n, True) for n in DECK]
    deck_r = [pf(n, False) for n in DECK]
    crash_l, crash_r = pf('hcrf', False), pf('hcr5', False)
    # muzzle flash (draw_player_plane): hellcat list index attitude-5 + 67 ('fa') / 87 ('fb'), +10 facing left
    flash_a_r = [pf('fa%02x' % a, False) for a in range(1, 11)]
    flash_a_l = [pf('fa%02x' % (a + 10), False) for a in range(1, 11)]
    flash_b_r = [pf('fb%02x' % a, False) for a in range(1, 11)]
    flash_b_l = [pf('fb%02x' % (a + 10), False) for a in range(1, 11)]
    wheels = []
    def wf(name):
        if name not in wheels:
            wheels.append(name)
        return wheels.index(name)
    whl = [wf(n) for n in WHL]
    whr = [wf(n) for n in WHR]

    # ---- palette: level pixels + heavily weighted plane/wheel pixels ----
    weights = {}
    for mp in allmaps:
        for row in mp['canvas'] + mp['wreck'][WRECK_ROW0 * 16:(WRECK_ROW0 + WRECK_ROWS) * 16]:
            for p in row:
                weights[p] = weights.get(p, 0) + 1.0 / len(allmaps)
    for n, _ in plane:
        for p, mk in zip(hell[n].pixels, hell[n].mask):
            if mk:
                rgb = amiga_pal[p]; weights[rgb] = weights.get(rgb, 0) + 400
    for n in wheels:
        for p, mk in zip(hell[n].pixels, hell[n].mask):
            if mk:
                rgb = amiga_pal[p]; weights[rgb] = weights.get(rgb, 0) + 400
    # index 0 = black: the ST border shows colour 0. It is also the sprite key, so no art maps to it (15 art colours).
    # map objects: each distinct frame counts with a fixed weight per pixel, so small but common objects (palms,
    # huts, bunkers) keep their colours against the large carrier / sky / sea areas
    seen = set()
    for v in [v for mp in allmaps for v in mp['cells']]:
        t = (v >> 2) & 0x1ff
        nm = names[t] if v & 0x8000 and t < len(names) else None
        if nm in world and nm not in seen and nm not in INVISIBLE:
            seen.add(nm)
            f = world[nm]
            for p, mk in zip(f.pixels, f.mask):
                if mk:
                    rgb = amiga_pal[p]; weights[rgb] = weights.get(rgb, 0) + OBJ_WEIGHT
    # index 1 = sky. Forced: menu / explosion yellow (10) and orange-red (2), palm green (7): small but important areas
    # ... and a dark brown (0x904010): without it the log bunkers ('dugo', three browns) and the huts collapse into
    # the orange and lose their detail. It costs the least used of the automatically chosen colours.
    chosen = [(0, 0, 0)] + choose_palette(weights, 15, forced=[amiga_pal[1], amiga_pal[10], amiga_pal[2], amiga_pal[7],
                                                              (0x90, 0x40, 0x10)])
    def grey(c):
        return max(c) - min(c) <= 0x20
    def warm(c):
        return c[0] >= c[2] + 0x40 and c[0] >= c[1]
    def nearest(rgb):
        # keep the character of the colour: a (near) grey goes to a grey (dark hull greys used to land on the dark
        # blues), a brown / orange to a warm colour; everything else to the nearest
        cand = range(1, len(chosen))
        if grey(rgb):
            g = [k for k in cand if grey(chosen[k])]
            cand = g or cand
        elif warm(rgb):
            g = [k for k in cand if warm(chosen[k])]
            cand = g or cand
        return min(cand, key=lambda k: d2(rgb, chosen[k]))
    rgbmap = {rgb: nearest(rgb) for rgb in set(weights) | set(amiga_pal)}
    flatpal = [v for rgb in chosen for v in rgb]
    flatpal += [0] * (768 - len(flatpal))       # 8-bit PNG: agtcut misreads 4-bit packed PNGs
    # night (missions h..o, a random bit per mission: FUN_111fc): 'night.p' / 'nightocean.p' replace the day palettes.
    # Each of our 16 colours takes the night value of the Amiga colour it is (or, for the forced brown, is nearest to)
    night_pal = list(iff.read_palette(rpck.load(os.path.join(SHAPES, 'night.p'))))
    night_ocean = list(iff.read_palette(rpck.load(os.path.join(SHAPES, 'nightocean.p'))))
    day_night = [(amiga_pal[i], night_pal[i]) for i in range(32)] + [(tuple(ocean[i]), night_ocean[i]) for i in range(32)]
    def ste_word(rgb):
        w = 0
        for c in rgb:
            v = c >> 4
            w = (w << 4) | (v >> 1) | ((v & 1) << 3)
        return w
    night16 = [0] + [ste_word(min(day_night, key=lambda dn: d2(c, dn[0]))[1]) for c in chosen[1:]]

    eighth = bank('8thscale.shp')

    # ---- per map: level image (live area + source band) and runtime data file map_<x>.dat ----
    def map_assets(mp):
        cells, canvas, wreck = mp['cells'], [list(r) for r in mp['canvas']], mp['wreck']
        W = len(canvas[0])
        WC = W // 16
        huts = [i for i, v in enumerate(cells) if v & 0x8000 and (v >> 2) & 0x1ff == 4]
        # ---- source band below the live area (BAND_ROWS tile rows): everything the runtime copies into the live area
        # (multimod_copy) or shows instead of it, packed side by side so the map stays small for the wide maps ----
        band0 = live_h // 16
        band = [[canvas[0][0]] * W for _ in range(BAND_ROWS * 16)]
        def blit(src, sy, sx, h, w, dy, dx):
            for y in range(h):
                band[dy + y][dx:dx + w] = src[sy + y][sx:sx + w]
        # 1) the 1/8 view (camera region, columns 0..mini_w) with its wrecked-hut rows below it in the same columns
        mini_sea = ocean[11]
        rgbmap.setdefault(mini_sea, nearest(mini_sea))
        mini = build_mini(cells, eighth, names, amiga_pal, W, mini_sea)
        mwreck = build_mini(cells, eighth, names, amiga_pal, W, mini_sea, wreck_huts=True, no_ships=True,
                            no_carrier=True)   # (also the source when a sunk ship or the own carrier leaves the 1/8 view)
        mini_w = (MINI_X0 + W // 8 + 208 + 15) // 16 * 16     # camera right edge (+ guard) for the rightmost plane x
        blit(mini, 0, 0, MINI_H, mini_w, 0, 0)
        blit(mwreck, MINI_WRECK_ROW0 * 16, 0, MINI_WRECK_ROWS * 16, mini_w, MINI_H, 0)
        col = mini_w // 16
        # 2) carrier wave bob (FUN_14eac; 252fe = {1,2,3,2,1,2,3,2}[i] + 1, i advances every 21 ticks): the tile rows
        # above the strip that change with the bob, rendered for bob 2, 3, 4 side by side
        var = {b: build_level(cells, world, names, amiga_pal, ocean, bob=b) for b in (2, 3, 4)}
        def tile(cv, tx, ty):
            return [cv[ty * 16 + y][tx * 16:tx * 16 + 16] for y in range(16)]
        changed = [(tx, ty) for ty in range(WAVE_ROW0) for tx in range(WC)
                   if tile(var[2], tx, ty) != tile(var[3], tx, ty) or tile(var[4], tx, ty) != tile(var[3], tx, ty)]
        bob_c0, bob_c1 = min(c for c, r in changed), max(c for c, r in changed)
        bob_r0 = min(r for c, r in changed)
        bob_rows, bob_cols = WAVE_ROW0 - bob_r0, BOB_COLS
        assert bob_c1 - bob_c0 + 1 <= BOB_COLS
        bob_src_col = col
        for v, b in enumerate((2, 3, 4)):
            blit(var[b], bob_r0 * 16, bob_c0 * 16, bob_rows * 16, bob_cols * 16, 0, (col + v * bob_cols) * 16)
        col += 3 * bob_cols
        # 3) wave animation (FUN_13e6c: frame 0x4e+n, n steps 11..0 every 2nd drawn frame). The waterline is tile-aligned,
        # so the strip is tile row WAVE_ROW0 only. Open sea repeats every 96 px (6 columns, world-fixed): the band holds
        # WAVE_SEA_LEN sea columns (any visible run of open sea is one copy from column x % 6) plus every column where
        # objects, hull or beaches show in the strip (c_wave_src, 0xffff = open sea); one band row per phase
        phases = [build_level(cells, world, names, amiga_pal, ocean, wave_frame=k) for k in range(WAVE_PHASES)]
        def stack(x):
            return tuple(tuple(ph[WAVE_ROW0 * 16 + y][x * 16:x * 16 + 16]) for ph in phases for y in range(16))
        stacks = [stack(x) for x in range(WC)]
        bad = [x for x in range(MARGIN // 16 - 4) if stacks[x] != stacks[x % WAVE_PERIOD]]
        assert not bad, "open sea strip not periodic: columns %s" % bad[:8]
        wave_sea_col = col
        for j in range(WAVE_SEA_LEN):
            for k, ph in enumerate(phases):
                blit(ph, WAVE_ROW0 * 16, (j % WAVE_PERIOD) * 16, 16, 16, k * 16, (col + j) * 16)
        col += WAVE_SEA_LEN
        wave_src = []
        for x in range(WC):
            if stacks[x] == stacks[x % WAVE_PERIOD]:
                wave_src.append(0xffff)
            else:
                for k, ph in enumerate(phases):
                    blit(ph, WAVE_ROW0 * 16, x * 16, 16, 16, k * 16, col * 16)
                wave_src.append(col)
                col += 1
        # 4) wrecked huts: per hut anchor the 3 x WRECK_ROWS tiles around 'hutb' (drawn at cell_x - hot_x 16)
        wreck_src = []
        for ci in huts:
            c0 = (MARGIN + ci * 8 - 16) >> 4
            blit(wreck, WRECK_ROW0 * 16, c0 * 16, WRECK_ROWS * 16, 48, 0, col * 16)
            wreck_src.append(col)
            col += 3
        # 5) pillbox damage (146dc: the cells become 'pila' + 4-bit damage mask): per pillbox the PILL_COLS tiles of
        # tile row PILL_ROW for masks 1..15, one band row each
        pills = [i for i, v in enumerate(cells) if v & 0x8000 and 0x0f <= (v >> 2) & 0x1ff <= 0x1e]
        pill_src = []
        if pills:
            pv = {m: build_level(cells, world, names, amiga_pal, ocean, pill_mask=m) for m in range(1, 16)}
            for ci in pills:
                c0 = (MARGIN + ci * 8 - 15) >> 4
                # (band rows 0..BAND_ROWS-1, then the next PILL_COLS columns: the band has < 15 rows in the 200-line build)
                for m in range(1, 16):
                    blit(pv[m], PILL_ROW * 16, c0 * 16, 16, PILL_COLS * 16, ((m - 1) % BAND_ROWS) * 16,
                         (col + PILL_COLS * ((m - 1) // BAND_ROWS)) * 16)
                pill_src.append(col)
                col += PILL_COLS * ((14 // BAND_ROWS) + 1)
        # 6) sunk enemy ships (stage 120 clears their cells): per ship the changed tiles above the strip without the
        # ship, its wave strip columns (open sea afterwards) and its 1/8-view columns (the mini wreck rows have no ships)
        ship_rm = []
        sh = []
        for i, v in enumerate(cells):
            t = (v >> 2) & 0x1ff
            if v & 0x8000 and t in SHIP_X and t not in [x[0] for x in sh]:
                sh.append((t, i))
        if sh:
            noship = build_level(cells, world, names, amiga_pal, ocean, no_ships=True)
            mnoship = build_mini(cells, eighth, names, amiga_pal, W, mini_sea, no_ships=True)
            for t, ci in sh:
                x0 = MARGIN + ci * 8 + SHIP_X[t][0]
                x1 = x0 + SHIP_X[t][1]
                ca, cb = max(0, (x0 - 64) // 16), min(WC - 1, (x1 + 64) // 16)
                ch = [(tx, ty) for ty in range(WAVE_ROW0) for tx in range(ca, cb + 1)
                      if tile(canvas, tx, ty) != tile(noship, tx, ty)]
                c0, c1 = min(c for c, r in ch), max(c for c, r in ch)
                r0 = min(r for c, r in ch)
                nrows, ncols = WAVE_ROW0 - r0, c1 - c0 + 1
                assert nrows <= BAND_ROWS
                blit(noship, r0 * 16, c0 * 16, nrows * 16, ncols * 16, 0, col * 16)
                wc = [tx for tx in range(ca, cb + 1) if tile(canvas, tx, WAVE_ROW0) != tile(noship, tx, WAVE_ROW0)]
                mx0, mx1 = (MINI_X0 + x0 // 8 - 16) // 16, (MINI_X0 + x1 // 8 + 16) // 16
                mc = [tx for tx in range(mx0, mx1 + 1)
                      if any(mini[y][tx * 16:tx * 16 + 16] != mnoship[y][tx * 16:tx * 16 + 16]
                             for y in range(MINI_WRECK_ROW0 * 16, (MINI_WRECK_ROW0 + MINI_WRECK_ROWS) * 16))]
                ship_rm += [col, c0, ncols, r0, nrows, min(wc) if wc else 0, max(wc) if wc else -1,
                            min(mc) if mc else 0, (max(mc) - min(mc) + 1) if mc else 0]
                col += ncols
        # 7) the own carrier sunk (stage 120): its ship-less tiles go below the bob variants (band rows 8..14)
        rcar_i = next(i for i, v in enumerate(cells) if v & 0x8000 and (v >> 2) & 0x1ff == 0x21)
        nocar = build_level(cells, world, names, amiga_pal, ocean, no_carrier=True)
        mnocar = build_mini(cells, eighth, names, amiga_pal, W, mini_sea, no_carrier=True)
        x0 = MARGIN + rcar_i * 8 - 640
        x1 = x0 + 768
        ca, cb = max(0, (x0 - 64) // 16), min(WC - 1, (x1 + 64) // 16)
        ch = [(tx, ty) for ty in range(WAVE_ROW0) for tx in range(ca, cb + 1) if tile(canvas, tx, ty) != tile(nocar, tx, ty)]
        c0, c1 = min(c for c, r in ch), max(c for c, r in ch)
        r0 = min(r for c, r in ch)
        nrows, ncols = WAVE_ROW0 - r0, c1 - c0 + 1
        if nrows <= BAND_ROWS - bob_rows and ncols <= 3 * bob_cols:
            car_col, car_row = bob_src_col, bob_rows
        else:                                     # (200-line build: the band is too low, own columns instead)
            assert nrows <= BAND_ROWS
            car_col, car_row = col, 0
            col += ncols
        blit(nocar, r0 * 16, c0 * 16, nrows * 16, ncols * 16, car_row * 16, car_col * 16)
        wc = [tx for tx in range(ca, cb + 1) if tile(canvas, tx, WAVE_ROW0) != tile(nocar, tx, WAVE_ROW0)]
        mx0, mx1 = (MINI_X0 + x0 // 8 - 16) // 16, (MINI_X0 + x1 // 8 + 16) // 16
        mc = [tx for tx in range(mx0, mx1 + 1)
              if any(mini[y][tx * 16:tx * 16 + 16] != mnocar[y][tx * 16:tx * 16 + 16]
                     for y in range(MINI_WRECK_ROW0 * 16, (MINI_WRECK_ROW0 + MINI_WRECK_ROWS) * 16))]
        carrier_rm = [car_col, c0, ncols, r0, nrows, min(wc) if wc else 0, max(wc) if wc else -1,
                      min(mc) if mc else 0, (max(mc) - min(mc) + 1) if mc else 0, car_row]
        assert col <= WC, "source band wider than the level (%d > %d columns)" % (col, WC)
        for row in band:
            for px in row:
                if px not in rgbmap:
                    rgbmap[px] = nearest(px)
        mini_row = len(canvas)
        canvas += band
        lvl = Image.new('P', (W, len(canvas))); lvl.putpalette(flatpal)
        lvl.putdata([rgbmap[p] for row in canvas for p in row])
        lvl.save(os.path.join(out, 'level_%s.png' % mp['letter']))
        flags = []                                    # (top-left image x, y, kind 0 = US tower, 1 = island)
        for i, v in enumerate(cells):
            t = (v >> 2) & 0x1ff
            if t == 0x22:
                f = world['flg3']
                bob = 3 if v & 3 == 1 else 0
                flags.append((MARGIN + i * 8 - f.hx, WATER_ROW + ((v >> 11) & 7) * 4 + bob - f.hy, 0))
            elif t == 0x113:
                f = world['flg0']
                flags.append((MARGIN + i * 8 - f.hx, WATER_ROW - f.hy, 1))

        # ---- carrier geometry (player.md 6.1) ----
        rcar = next(i for i, v in enumerate(cells) if v & 0x8000 and (v >> 2) & 0x1ff == 0x21)
        o = rcar * 2
        deck_x0, deck_x1 = (o - 0xa0) * 4 + 16, (o + 0x20) * 4 - 16
        home = mp['home_hdr'] * 4 - 8

        bunkers = [i for i, v in enumerate(cells) if v & 0x8000 and (v >> 2) & 0x1ff == 3]
        lso = [i for i, v in enumerate(cells) if (v >> 2) & 0x1ff == 0x9f]   # FUN_13b1c runs for every cell (no anchor bit)
        assert len(canvas) == live_h + BAND_ROWS * 16
        # islands (FUN_12d5a pass 2): island i ends at the i-th 'bchr' anchor; a building belongs to the island whose
        # right beach is the first one after it. Bonus per island: word table 0x233cc[m * 4 + i]
        bchr = [i for i, v in enumerate(cells) if v & 0x8000 and (v >> 2) & 0x1ff == 2]
        assert len(bchr) <= 4
        isl = lambda c: sum(1 for r in bchr if r < c)
        m_idx = ord(mp['letter']) - ord('a')
        bonus = list(struct.unpack('>4H', img[0x233cc - 0x10000 + m_idx * 8:0x233cc - 0x10000 + m_idx * 8 + 8]))
        # enemy ships (only the first of each kind): anchor type, cell
        ships, seen_t = [], set()
        for i, v in enumerate(cells):
            t = (v >> 2) & 0x1ff
            if v & 0x8000 and t in (0xe4, 0x10d, 0xcc, 0xf2) and t not in seen_t:
                seen_t.add(t); ships += [t, i]
        # map_<x>.dat (big-endian words): header, then c_map, c_wave_src, huts, bunkers, wreck_src, flags, lso, pillboxes,
        # island ends (bchr cells), island bonus[4], hut / bunker / pillbox island index, ships (type, cell)
        # airfields (FUN_12c84): cells 0x114 / 0x115 in pairs, the second one gives x_end and the direction
        # (0x114 -1, 0x115 +1); planes / max airborne per airfield from the mission table 0x23444 (2 bytes each)
        zc = [(i, (v >> 2) & 0x1ff) for i, v in enumerate(cells) if (v >> 2) & 0x1ff in (0x114, 0x115)]
        aft = img[0x23444 - 0x10000 + m_idx * 4:0x23444 - 0x10000 + m_idx * 4 + 4]
        airf = []
        for k in range(0, len(zc) // 2 * 2, 2):
            if k // 2 >= 2:
                break
            planes, mx_air = aft[k], aft[k + 1]
            airf += [zc[k][0] * 8, zc[k + 1][0] * 8, mx_air, planes, -1 if zc[k + 1][1] == 0x114 else 1]
        # ship plane blocks (FUN_1252c): planes / max airborne per ship kind from the mission tables (2 bytes each)
        sp_tab = {0xe4: 0x23480, 0x10d: 0x2349e, 0xcc: 0x234bc, 0xf2: 0x234da}
        ship_planes = []
        for k in range(0, len(ships), 2):
            a2 = sp_tab[ships[k]] - 0x10000 + m_idx * 2
            ship_planes += [img[a2], img[a2 + 1]]
        hdrw = [0x574d, 6, W, len(cells), deck_x0, deck_x1, home, bob_c0, bob_src_col, wave_sea_col,
                len(huts), len(bunkers), len(pills), len(flags), len(lso), len(bchr), m_idx, len(ships) // 2, 0, 0]
        data = hdrw + list(cells) + wave_src + huts + bunkers + wreck_src + [v for fl in flags for v in fl] + lso + pills
        data += bchr + bonus + [isl(c) for c in huts] + [isl(c) for c in bunkers] + [isl(c) for c in pills] + ships
        data += pill_src + ship_rm + [len(airf) // 5] + airf + ship_planes + carrier_rm
        assert len(ship_rm) == 9 * len(ships) // 2
        with open(os.path.join(out, 'map_%s.dat' % mp['letter']), 'wb') as fp:
            fp.write(struct.pack('>%dH' % len(data), *[v & 0xffff for v in data]))
        return dict(letter=mp['letter'], W=W, cells=len(cells), huts=len(huts), bunkers=len(bunkers), pills=len(pills),
                    islands=len(bchr), ships=len(ships) // 2, bonus=bonus,
                    flags=len(flags), lso=len(lso), home=home, deck=(deck_x0, deck_x1), band_cols=col,
                    bob=(bob_r0, bob_rows, bob_cols), wave_sea_col=wave_sea_col, mini_row=mini_row)
    infos = [map_assets(mp) for mp in maps]
    for k in ('bob', 'mini_row'):
        assert all(i[k] == infos[0][k] for i in infos), (k, [(i['letter'], i[k]) for i in infos])
    bob_r0, bob_rows, bob_cols = infos[0]['bob']
    mini_row = infos[0]['mini_row']

    flash_names = set('fa%02x' % i for i in range(1, 0x15)) | set('fb%02x' % i for i in range(1, 0x15))
    for n in flash_names:                                   # make sure XOR colours are mappable
        for p, mk in zip(hell[n].pixels, hell[n].mask):
            rgb = amiga_pal[1 ^ p]
            if mk and rgb not in rgbmap:
                rgbmap[rgb] = nearest(rgb)
    pimg, pcols, prows = sheet([hell[n] for n, _ in plane], [mi for _, mi in plane],
                               PL_CW, PL_CH, PL_AX, PL_AY, rgbmap, amiga_pal, xor_frames=flash_names)
    pimg.putpalette(flatpal); pimg.save(os.path.join(out, 'hellcat.png'))
    wimg, wcols, wrows = sheet([hell[n] for n in wheels], [False] * len(wheels),
                               WH_CW, WH_CH, WH_AX, WH_AY, rgbmap, amiga_pal)
    wimg.putpalette(flatpal); wimg.save(os.path.join(out, 'wheels.png'))

    # torpedo slung under the plane (draw_player_plane 103a6, G_2536e): Torpedo.shp holds one overlay per Hellcat frame
    # name, drawn at the plane's position with its own hot-spot. Same cells / anchor as the plane sheet.
    tbank = bank('torpedo.shp')
    tsl, tfr = [], []                # sheet entries (name, mirrored); per plane frame: sheet index or 255
    for name, mir in plane:
        if name in tbank:
            if (name, mir) not in tsl:
                tsl.append((name, mir))
            tfr.append(tsl.index((name, mir)))
        else:
            tfr.append(255)
    for n, _ in tsl:
        for px, mk in zip(tbank[n].pixels, tbank[n].mask):
            if mk and amiga_pal[px] not in rgbmap:
                rgbmap[amiga_pal[px]] = nearest(amiga_pal[px])
    timg, tcols, trows = sheet([tbank[n] for n, _ in tsl], [mi for _, mi in tsl],
                               PL_CW, PL_CH, TP_AX, PL_AY, rgbmap, amiga_pal)
    timg.putpalette(flatpal); timg.save(os.path.join(out, 'torp.png'))

    # carrier elevator platform 'elev' (draw_carrier_elevator 1409c): one 64x13 frame, hot-spot (28,-1), drawn at the
    # elevator x with its hot-spot at the deck height
    ef = world['elev']
    for px, mk in zip(ef.pixels, ef.mask):
        if mk and amiga_pal[px] not in rgbmap:
            rgbmap[amiga_pal[px]] = nearest(amiga_pal[px])
    eimg, _, _ = sheet([ef], [False], 64, 16, EL_AX, EL_AY, rgbmap, amiga_pal, cols=1)
    eimg.putpalette(flatpal); eimg.save(os.path.join(out, 'elev.png'))

    # 'gmov' game-over sign (FUN_110c2): 192x22, hot-spot (99,11), drawn at screen (160,81); 208x24 cell, anchor (100,12)
    gf = world['gmov']
    for px, mk in zip(gf.pixels, gf.mask):
        if mk and amiga_pal[px] not in rgbmap:
            rgbmap[amiga_pal[px]] = nearest(amiga_pal[px])
    gimg, _, _ = sheet([gf], [False], 208, 24, 100, 12, rgbmap, amiga_pal, cols=1)
    gimg.putpalette(flatpal); gimg.save(os.path.join(out, 'gmov.png'))

    # flags (draw_special_map_cell 13b1c, not drawn in the 1/8 view): carrier tower 0x22 -> flg3..6 (also turns the
    # radar; opaque 32x42 incl. sky), island 0x113 -> flg0..2 while garrisoned, else 'POST'. Same anchor as the cell
    # frame: x = cell_x - hot_x; tower y = waterline + jitter*4 + bob - hot_y, island y = waterline - hot_y.
    FLAG_NAMES = ['flg3', 'flg4', 'flg5', 'flg6', 'flg0', 'flg1', 'flg2', 'POST']
    flagimg = Image.new('P', (32 * 8, 48), 0)
    for n, nm in enumerate(FLAG_NAMES):
        f = world[nm]
        for j in range(f.h):
            for i in range(f.w):
                k = j * f.w + i
                if f.mask[k]:
                    c = rgbmap[amiga_pal[f.pixels[k]]]
                    flagimg.putpixel((n * 32 + i, j), c if c else 1)
    flagimg.putpalette(flatpal); flagimg.save(os.path.join(out, 'flags.png'))
    # 1/8 view player frames: draw_player_plane picks 8thscale index 0x28..0x47 (names list = world names)
    mini_names, mini_idx = [], []
    for n in range(MINI_PLANE_N0, MINI_PLANE_N1):
        nm = names[n]
        if nm not in mini_names:
            mini_names.append(nm)
        mini_idx.append(mini_names.index(nm))
    # 1/8 view effects: FUN_15174 draws the 8thscale frame of the same name; bombs use 'bumb' (8thscale shape 9).
    # Frames without a 1/8 version (spl4-6, ric0) are not drawn there.
    mini_fx = []
    for nm in FX_NAMES:
        mn = 'bumb' if nm.startswith('bom') else nm
        if mn in eighth:
            if mn not in mini_names:
                mini_names.append(mn)
            mini_fx.append(mini_names.index(mn))
        else:
            mini_fx.append(255)
    mini_sold = []
    for nm in ('guy0', 'guy1'):                     # 1/8 view: (frame & 1) + 1 + 0x6e -> guy0 / guy1
        if nm not in mini_names:
            mini_names.append(nm)
        mini_sold.append(mini_names.index(nm))
    # (the 1/8-view AA gun frame 'expl' lives in the gun sheet: a 41st mini frame crashed the EMX draw)
    mimg, mcols, mrows = sheet([eighth[n] for n in mini_names], [False] * len(mini_names),
                               MI_CW, MI_CH, MI_AX, MI_AY, rgbmap, amiga_pal)
    mimg.putpalette(flatpal); mimg.save(os.path.join(out, 'mini.png'))

    torp = bank('torpedo.shp')
    fxf = [torp[n] if n in torp else world[n] for n in FX_NAMES]
    for f in fxf:
        for p, mk in zip(f.pixels, f.mask):
            if mk and amiga_pal[p] not in rgbmap:
                rgbmap[amiga_pal[p]] = nearest(amiga_pal[p])
    ximg, xcols, xrows = sheet(fxf, [False] * len(fxf), FX_CW, FX_CH, FX_AX, FX_AY, rgbmap, amiga_pal)
    ximg.putpalette(flatpal); ximg.save(os.path.join(out, 'fx.png'))

    crew = [world['fgy%x' % i] for i in range(16)]
    cimg, ccols, crows = sheet(crew, [False] * 16, CR_CW, CR_CH, CR_AX, CR_AY, rgbmap, amiga_pal, cols=8)
    cimg.putpalette(flatpal); cimg.save(os.path.join(out, 'crew.png'))

    # island soldiers (FUN_13eee): world frame 0x6f + frame (guy0..guy7), +9 facing left (guy9..gy10)
    sold = [world[names[0x6f + k]] for k in range(8)] + [world[names[0x78 + k]] for k in range(8)]
    simg, scols, srows = sheet(sold, [False] * 16, SO_CW, SO_CH, SO_AX, SO_AY, rgbmap, amiga_pal, cols=8)
    simg.putpalette(flatpal); simg.save(os.path.join(out, 'soldiers.png'))

    # weapons (2.3 drawing): rockets rc01..rc14 (Torpedo.shp 0x4c+frame), drop phase ro01..ro14 (0x74+frame),
    # torpedo tor2 / tor7 (facing left); weapon-select menu 'selt' + highlighted rows rock/bomb/torp (world 0x4a..0x4d)
    tnames = []
    i = 0x242f0 - 0x10000
    while img[i:i + 4] != b'\0\0\0\0':
        tnames.append(img[i:i + 4].decode('latin1')); i += 4
    wfr = [torp[tnames[0x4c + k]] for k in range(20)] + [torp[tnames[0x74 + k]] for k in range(20)] + \
          [torp['tor2'], torp['tor7']] + [world[names[0x4d]]] + [world[names[0x4a + k]] for k in range(3)]
    for f in wfr:
        for p, mk in zip(f.pixels, f.mask):
            if mk and amiga_pal[p] not in rgbmap:
                rgbmap[amiga_pal[p]] = nearest(amiga_pal[p])
    # the menu is drawn as one sprite per selection (box + highlighted row composed), frames 43..45
    selt = world[names[0x4d]]
    class _F: pass
    for k in range(3):
        row = world[names[0x4a + k]]
        f = _F(); f.name = 'menu%d' % k; f.w, f.h, f.hx, f.hy = selt.w, selt.h, selt.hx, selt.hy
        f.pixels = list(selt.pixels); f.mask = [True] * (selt.w * selt.h)      # 'selt' is blitted without a mask
        oy = selt.hy - row.hy; ox = selt.hx - row.hx
        for y in range(row.h):
            for x in range(row.w):
                if row.mask[y * row.w + x] and 0 <= x + ox < f.w and 0 <= y + oy < f.h:
                    f.pixels[(y + oy) * f.w + x + ox] = row.pixels[y * row.w + x]
        wfr[0x2b + k] = f
    wimg2, _, wrows2 = sheet(wfr, [False] * len(wfr), WP_CW, WP_CH, WP_AX, WP_AY, rgbmap, amiga_pal, cols=8)
    wimg2.putpalette(flatpal); wimg2.save(os.path.join(out, 'weapons.png'))

    # enemy planes (10da6 / 1d1ea): sprite index 0..27 (dir -1) / 28..55 (dir +1) -> japplane name tables 0x25ea8 /
    # 0x25f18; 1/8 view zpn* tables 0x25f88 / 0x25ff8. Plus muzzle flashes fc10/fd10/fc1a/fd1a and parked jp21/jp22.
    japp = bank('japplane.shp')
    def ntab(a, n):
        i = a - 0x10000
        return [img[i + k * 4:i + k * 4 + 4].decode('latin1').strip() for k in range(n)]
    zp_names = []
    def zf(nm):
        if nm not in zp_names:
            zp_names.append(nm)
        return zp_names.index(nm)
    zp_idx = [zf(n) for n in ntab(0x25ea8, 28) + ntab(0x25f18, 28)]
    zp_fx = [zf(n) for n in ('fc10', 'fd10', 'fc1a', 'fd1a', 'jp21', 'jp22')]
    # The Zero's muzzle flash is drawn with exclusive-or ON the plane's nose (0x10e88, blit_shape_xor; checked in
    # vAmiga 2026-10-08): its blues and browns over the light grey cowling give yellow, orange and white. The flag is
    # only set in level flight, so the plane under it is always jp1a (flying left) or jp10 (right): the four flash
    # frames are stored as the colours that result, pixel by pixel (the sky, colour 1, where the plane is not).
    import copy
    zfr = {n: japp[n] for n in zp_names}
    for fn, pn in (('fc1a', 'jp1a'), ('fd1a', 'jp1a'), ('fc10', 'jp10'), ('fd10', 'jp10')):
        f, pl = japp[fn], japp[pn]
        g = copy.copy(f)
        px = []
        for i, (p, mk) in enumerate(zip(f.pixels, f.mask)):
            x, y = i % f.w - f.hx + pl.hx, i // f.w - f.hy + pl.hy
            under = 1
            if 0 <= x < pl.w and 0 <= y < pl.h and pl.mask[y * pl.w + x]:
                under = pl.pixels[y * pl.w + x]
            c = under ^ p
            px.append(c)
            if mk and amiga_pal[c] not in rgbmap:
                rgbmap[amiga_pal[c]] = nearest(amiga_pal[c])
        g.pixels = px
        zfr[fn] = g
    zimg, _, zrows = sheet([zfr[n] for n in zp_names], [False] * len(zp_names), ZP_CW, ZP_CH, ZP_AX, ZP_AY,
                           rgbmap, amiga_pal, cols=8)
    zimg.putpalette(flatpal); zimg.save(os.path.join(out, 'zeros.png'))
    zm_names = []
    def zmf(nm):
        if nm not in zm_names:
            zm_names.append(nm)
        return zm_names.index(nm)
    zm_idx = [zmf(n) for n in ntab(0x25f88, 28) + ntab(0x25ff8, 28)]
    zmimg, _, zmrows = sheet([eighth[n] for n in zm_names], [False] * len(zm_names), MI_CW, MI_CH, MI_AX, MI_AY,
                             rgbmap, amiga_pal, cols=8)
    zmimg.putpalette(flatpal); zmimg.save(os.path.join(out, 'zmini.png'))

    # AA guns (13d78 bunkers / 13de8 pillboxes): barrel frames gun0..6, firing frames gnf0..6
    guns = [world[names[0x81 + k]] for k in range(14)] + [eighth[names[90]]]   # + frame 14: 1/8 view (90 'expl')
    gimg, gcols, grows = sheet(guns, [False] * 15, GN_CW, GN_CH, GN_AX, GN_AY, rgbmap, amiga_pal, cols=8)
    gimg.putpalette(flatpal); gimg.save(os.path.join(out, 'guns.png'))

    # HUD: digits 0-9 from dash 'wnum' (8 px per digit), rope segments 1..16 px (Amiga colour 3), bomb icon
    dash = bank('dash.shp')
    dpal = iff.read_palette(rpck.load(os.path.join(SHAPES, 'iff-dash')))
    hud = Image.new('P', (HUD_CW * 10, HUD_CH * 3), 0)
    wn = dash['wnum']
    white = rgbmap.get((0xf0, 0xf0, 0xf0), nearest((0xf0, 0xf0, 0xf0)))
    for dgt in range(10):
        for y in range(8):
            for x in range(wn.w):
                k = (2 + dgt * 8 + y) * wn.w + x          # digits are 7 rows at pitch 8, starting at row 2
                if k < len(wn.mask) and wn.mask[k] and x < HUD_CW:
                    hud.putpixel((dgt * HUD_CW + x, y), white)
    rope_c = nearest(amiga_pal[3]) or 1
    for w in range(1, 17):
        n = 10 + (w - 1)
        for x in range(w):
            hud.putpixel(((n % 10) * HUD_CW + x, (n // 10) * HUD_CH), rope_c)
    bomb_icon = torp['bom9']
    n = 26
    for y in range(bomb_icon.h):
        for x in range(bomb_icon.w):
            k = y * bomb_icon.w + x
            if bomb_icon.mask[k]:
                c = rgbmap[amiga_pal[bomb_icon.pixels[k]]] or 1
                hud.putpixel(((n % 10) * HUD_CW + x, (n // 10) * HUD_CH + y), c)
    hud.putpalette(flatpal); hud.save(os.path.join(out, 'hud.png'))

    # ---- tables from the exe ----
    def longs(addr, n):
        a = addr - 0x10000
        return struct.unpack('>%dI' % n, img[a:a + 4 * n])
    sin16 = [round(ffp(v) * 65536) for v in longs(0x25ac4, 92)]
    turncos16 = [round(ffp(v) * 65536) for v in longs(0x25a5c, 28)]   # 28: enemy planes use index 27
    objh = list(struct.unpack('>6h', img[0x25712 - 0x10000:0x25712 - 0x10000 + 12]))
    tantab = list(struct.unpack('>256h', img[0x246bc - 0x10000:0x246bc - 0x10000 + 512]))   # gun ray, 1024 units/turn

    with open(hdr, 'w') as fp:
        fp.write('// generated by wof/tools/make_proto_assets.py - do not edit\n#pragma once\n\n')
        mx = lambda k: max(i[k] for i in infos)
        fp.write(f'// per-map values (LEVEL_W, MAP_CELLS, HOME_X, DECK_X0/1, c_map, ...) come from map_<x>.dat at run time\n')
        fp.write(f'#define MAX_LEVEL_W {mx("W")}\n#define MAX_MAP_CELLS {mx("cells")}\n#define MAX_HUTS {max(1, mx("huts"))}\n#define MAX_BUNKERS {max(1, mx("bunkers"))}\n#define MAX_PILLBOXES {max(1, mx("pills"))}\n#define MAX_FLAGS {max(1, mx("flags"))}\n#define MAX_LSO {max(1, mx("lso"))}\n')
        fp.write(f'#define MAP_LETTERS "{letters}"\n#define LEVEL_H {live_h + BAND_ROWS * 16}\n#define VIEW_H {VIEW_H}\n#define PF_H {PF_H}\n#define SEP_H {SEP_H}\n')
        fp.write(f'#define BASE_ROW {BASE_ROW}\t\t// image row of world y = 0\n#define WATER_ROW {WATER_ROW}\n#define MARGIN {MARGIN}\n')
        fp.write(f'#define PL_AX {PL_AX}\n#define PL_AY {PL_AY}\n#define WH_AX {WH_AX}\n#define WH_AY {WH_AY}\n')
        fp.write(f'#define LIVE_H {live_h}\t\t// camera limit; rows below hold the wrecked-hut tiles\n')
        fp.write(f'#define BAND_ROW {live_h // 16}\t\t// source band (BAND_ROWS tile rows): 1/8 view, bob, waves, wrecked huts\n#define BAND_ROWS {BAND_ROWS}\n')
        fp.write(f'#define WRECK_DST_ROW {WRECK_ROW0}\n#define WRECK_SRC_ROW {live_h // 16}\n#define WRECK_ROWS {WRECK_ROWS}\n')
        fp.write(f'#define MINI_ROW {mini_row}\t\t// image row of the 1/8 view (MINI_H rows)\n#define MINI_H {MINI_H}\n#define MINI_SEA {MINI_SEA}\n#define MINI_X0 {MINI_X0}\n')
        fp.write(f'#define MI_AX {MI_AX}\n#define MI_AY {MI_AY}\n#define MINI_FRAMES {len(mini_names)}\n#define MINI_SHEET_ROWS {mrows}\n#define MINI_PLANE_N0 {MINI_PLANE_N0}\n')
        fp.write(f'#define MINI_WRECK_DST_ROW {mini_row // 16 + MINI_WRECK_ROW0}\n#define MINI_WRECK_SRC_ROW {live_h // 16 + MINI_H // 16}\n#define MINI_WRECK_ROWS {MINI_WRECK_ROWS}\n')
        fp.write(carr('c_fr_mini', 'u8', mini_idx, 16))
        fp.write(carr('c_fr_minifx', 'u8', mini_fx, 26))
        fp.write(carr('c_night_pal', 'u16', night16, 16))   # the playfield palette at night (STE colour words)
        fp.write(f'#define WAVE_DST_ROW {WAVE_ROW0}\n#define WAVE_SRC_ROW {live_h // 16}\n#define WAVE_PHASES {WAVE_PHASES}\n#define WAVE_PERIOD {WAVE_PERIOD}\n')
        fp.write(f'#define PILL_ROW {PILL_ROW}\n#define PILL_COLS {PILL_COLS}\n')
        fp.write(f'#define BOB_DST_ROW {bob_r0}\n#define BOB_ROWS {bob_rows}\n#define BOB_COLS {bob_cols}\n#define BOB_SRC_ROW {live_h // 16}\n')
        fp.write(f'#define SO_AX {SO_AX}\n#define SO_AY {SO_AY}\n')
        fp.write(carr('c_fr_minisold', 'u8', mini_sold))
        fp.write(f'#define WP_AX {WP_AX}\n#define WP_AY {WP_AY}\n#define WP_FR_RC 0\n#define WP_FR_RO 20\n#define WP_FR_TOR 40\n#define WP_FR_SELT 42\n#define WP_FR_ROW 43\n#define WP_FRAMES {len(wfr)}\n#define WP_ROWS {wrows2}\n')
        fp.write(f'#define ZP_AX {ZP_AX}\n#define ZP_AY {ZP_AY}\n#define ZP_FRAMES {len(zp_names)}\n#define ZP_ROWS {zrows}\n#define ZM_FRAMES {len(zm_names)}\n#define ZM_ROWS {zmrows}\n')
        fp.write(carr('c_fr_zero', 'u8', zp_idx, 28))
        fp.write(carr('c_fr_zmini', 'u8', zm_idx, 28))
        fp.write(f'#define ZP_FR_FC10 {zp_fx[0]}\n#define ZP_FR_FD10 {zp_fx[1]}\n#define ZP_FR_FC1A {zp_fx[2]}\n#define ZP_FR_FD1A {zp_fx[3]}\n#define ZP_FR_PARK1 {zp_fx[4]}\n#define ZP_FR_PARK2 {zp_fx[5]}\n')
        fp.write(f'#define GUN_FR_MINI 14\n#define GN_AX {GN_AX}\n#define GN_AY {GN_AY}\n#define AA_TAB_PRE {AA_TAB_PRE}\n#define AA_TAB_LEN {AA_TAB_LEN}\n')
        a = AA_TAB_ADDR - 0x10000 - AA_TAB_PRE
        fp.write(carr('c_aa_tab', 's8', [b - 256 if b > 127 else b for b in img[a:a + AA_TAB_LEN]], 24))
        fp.write(f'#define FX_AX {FX_AX}\n#define FX_AY {FX_AY}\n#define FX_BOMB0 0\n#define FX_EXP0 12\n#define FX_SPL0 18\n#define FX_RIC0 25\n#define FX_SMK0 26\n#define FX_BAL0 32\n#define FX_FRAMES {len(FX_NAMES)}\n\n')
        fp.write(carr('c_sin16', 's32', sin16, 8))
        fp.write(carr('c_turncos16', 's32', turncos16, 9))
        fp.write(carr('c_objh', 's16', objh))
        fp.write(carr('c_tantab', 's16', tantab))
        fp.write(carr('c_frameno', 'u8', FRAMENO, 20))
        fp.write(carr('c_clr', 's16', CLR, 12))
        fp.write(carr('c_gear', 's16', GEAR, 12))
        fp.write(carr('c_turnclr', 's16', TURNCLR, 6))
        for nm, arr in [('c_fr_pitch_l', pitch_l), ('c_fr_pitch_r', pitch_r), ('c_fr_loop_l', loop_l),
                        ('c_fr_loop_r', loop_r), ('c_fr_deck_l', deck_l), ('c_fr_deck_r', deck_r),
                        ('c_fr_wheel_l', whl), ('c_fr_wheel_r', whr)]:
            fp.write(carr(nm, 'u8', arr, 26))
        fp.write(f'#define FR_CRASH_L {crash_l}\n#define FR_CRASH_R {crash_r}\n')
        fp.write(carr('c_fr_torp', 'u8', tfr, 26))     # plane frame -> slung torpedo frame (255 = none)
        fp.write(f'#define TORP_FRAMES {len(tsl)}\n#define TORP_SHEET_ROWS {trows}\n#define TP_AX {TP_AX}\n#define EL_AX {EL_AX}\n#define EL_AY {EL_AY}\n')
        for nm, arr in [('c_fr_flash_a_l', flash_a_l), ('c_fr_flash_a_r', flash_a_r),
                        ('c_fr_flash_b_l', flash_b_l), ('c_fr_flash_b_r', flash_b_r)]:
            fp.write(carr(nm, 'u8', [0] + arr, 26))      # index = attitude frame 1..10
        fp.write(f'#define CR_AX {CR_AX}\n#define CR_AY {CR_AY}\n#define HUD_DIGIT0 0\n#define HUD_ROPE1 10\n#define HUD_BOMB 26\n')
        fp.write(f'#define PLANE_FRAMES {len(plane)}\n#define WHEEL_FRAMES {len(wheels)}\n')
        fp.write(f'#define PLANE_SHEET_COLS {pcols}\n#define PLANE_SHEET_ROWS {prows}\n')
        fp.write(f'#define WHEEL_SHEET_COLS {wcols}\n#define WHEEL_SHEET_ROWS {wrows}\n\n')

    with open(os.path.join(out, 'info.txt'), 'w') as fp:
        for i in infos:
            fp.write(f"map {i['letter']}: level {i['W']}x{live_h + BAND_ROWS * 16} home={i['home']} deck={i['deck'][0]}..{i['deck'][1]} "
                     f"huts={i['huts']} bunkers={i['bunkers']} pillboxes={i['pills']} islands={i['islands']} {i['bonus']} ships={i['ships']} "
                     f"band={i['band_cols']}/{i['W'] // 16} columns\n")
        fp.write(f'base_row={BASE_ROW} water_row={WATER_ROW}\n')
        fp.write(f'plane frames {len(plane)} ({pcols}x{prows} cells of {PL_CW}x{PL_CH}), wheels {len(wheels)}\n')
        fp.write('palette=' + ' '.join('%02x%02x%02x' % tuple(c) for c in chosen) + '\n')
    print(open(os.path.join(out, 'info.txt')).read())


if __name__ == '__main__':
    main(*sys.argv[1:5])
