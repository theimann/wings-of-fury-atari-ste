# Wings of Fury (Amiga) – frame timing, display, rendering, interrupts, sound & music

Area owner: render/sound agent. Addresses are absolute (A4 = 0x2af4e; `G_xxxxx` = global at that address).
Confidence: **[H]** high (read in asm), **[M]** medium (inferred from code + data), **[L]** guess.
Scratch files used: `notes/scratch/ann.s` (raw asm annotated with jump-table targets and absolute globals),
`notes/scratch/jt.json` (jump table A4 offset → target), `songplay.s`, `wofsongs_data.bin`.

---------------------------------------------------------------------------------------------------
## 1. Frame structure and timing

### 1.1 Two clocks
The game runs **two independent rates**:

| what | rate | driven by |
|---|---|---|
| **Logic tick** `FUN_00011386` | **12.5 Hz** (every 4th PAL VBL = 80 ms) **[H]** | VBL server queues one input word every 4 VBLs; the main loop runs one tick per queued word |
| **Render frame** `FUN_00010228` | variable: 50/n Hz, n = VBLs the render takes (≥1) **[H]** | waits for "VBL happened since last flip" flag |

Every behaviour coded in the logic tick is therefore *per 80 ms*, independent of the drawing speed.
Things updated inside the render path are *per drawn frame* (frame-rate dependent!) – see 1.5.

### 1.2 Main loop (FUN_00010006, gameplay part) [H]
```
loop:
  FUN_0001ccf6()            keyboard events (console.device): ESC pause, 's' sound, 'f' invert up/down, 'r' quit…, cheat "colin" codes
  if mission_over(G_25312) -> end-of-mission path
  if paused(G_254a6): wait_next_vbl (FUN_1aa32); continue
  if (G_252b4 && G_2530c) -> next-mission path (stop sounds, load next map, rebuild display) [M: meaning of flags]
  FUN_00010228()            RENDER one frame (waits for VBL first, flips at end)
  FUN_000114d8()            run all queued LOGIC ticks:
        while demo_budget(G_26c94)!=0: wait_next_vbl        (demo record/playback only)
        if paused<0 return
        while input_queue_count(G_272a4) > 0: FUN_00011386()  (each call pops one input word)
        G_26c94 = (demo_mode? 2 : 0)
```

### 1.3 VBL interrupt server FUN_00011754 [H]
Installed by `FUN_00012910`: exec `AddIntServer(INTB_VERTB=5, is)` with `ln_Pri = -10`, name "Interrupt_Server",
`is_Data = &G_2531a`, `is_Code = FUN_00011754`. Per VBL:
1. `G_2550e = 0xff` (render sync flag – "a VBL happened").
2. if `paused (G_254a6)` → return (nothing else counts while paused).
3. `G_2531a++` (32-bit VBL counter via is_Data; used e.g. for blinking `(G_2531a>>4)&0x1f`).
4. `FUN_0001c9ca()` – **every VBL**: fire-button timing. `G_26be2++`; on press store press time; if released
   within 10 VBLs → `G_27d4c=1` ("tap"); if still held ≥10 VBLs → `G_27d4a=1` ("held").
5. `if (--G_272b2 <= 0) { G_272b2 = 4; …}` → **every 4th VBL** build the input word:
   - normal: `FUN_0001ca32()` → `G_272b6` low byte: `1`=up `2`=down `4`=right `8`=left `0x10`=fire held `0x20`=fire tap
     (joystick read `FUN_0001520e`: JOY1DAT → table `G_255f6`; `'f'` key (G_25446) swaps up/down).
   - demo playback (`G_26c9c==1`): byte from demo buffer `G_26c9e[G_26ca2++]`, only while `G_26ca4 && G_26c94>0`
     (`G_26c94--`); 0xff or pos>4997 → `G_25312 = 0xff` (end demo).
   - push into queue `G_272a6[6]` (count `G_272a4`); if full (6) the oldest is dropped (`FUN_00011714`).
   - demo record (`G_26c9c==2`): write byte to buffer (5000 bytes) under the same budget.
6. if `G_2459e == 0` (in game, not in a menu):
   - `G_25360++` (game VBL timer, reset/used by player logic – interface to flight agent).
   - **message ticker** (see 3.7): shift the ticker bitmap 1 hires pixel left, start next glyph when due.

Second VBL server: the sound driver's `FUN_0001ec64` (pri **30**, so it runs before the game server) – see 6.

### 1.4 Render frame FUN_00010228 (per drawn frame) [H]
```
wait_vbl_flag()                         FUN_1aa3e: spin until G_2550e, clear it
G_252f6 = (G_252f6+1) % 11              frame counter (only reset elsewhere)
clip = playfield (0,0)-(320,162); set_rastport(back playfield)
FUN_00010f88()                          snapshot logic state -> render copies (under Forbid/Permit):
     G_26dac=G_24fca (plane/camera x), G_26db0=G_24fc8 (plane altitude), G_26eca=G_24fdc (dir),
     G_26ec8=G_2535e, G_26ecc=G_26db2, G_26da6=G_252fe (bob), G_24e86=G_25300 (zoom),
     copies of projectile/enemy/object positions; wave frame: every 2nd frame G_252de-- (11..0 wrap)
camera (see 4):  G_24e84 = zoom?3:0;  G_24e80 = G_26dac - (160<<G_24e84)
                 G_24e82 = G_252f0 = zoom? (1208,151) : 151 + max(0, G_26db0-131)
update_waterline_split(min(G_252f0,162))     FUN_1876e – moves the copper palette split (3.4)
[G_24e74 → FUN_135d8]
FUN_00013772  render_world        (sky, map objects, player, enemies, waves …, see 5.4)
FUN_00010ee0  debris particles     (moves AND draws, 40 slots)
FUN_00013eee  soldiers (guy*)      (moves AND draws)
FUN_000152f8  splashes/ricochets   (20 slots, counts down)
FUN_000106be  projectiles          (15 slots G_24bfe + G_254e4)
FUN_00010344  weapon-select box 'selt' + icon (only when G_252b4)
FUN_0001557c  victory balloons (G_252ad)
FUN_000110c2  "gmov" game-over shape (G_252b2), countdown G_25512 → G_25312
FUN_0001f2dc  clip = dashboard (0,0)-(640,37)
set_rastport(back dash viewport)
FUN_0001417e  3-D forward view window
FUN_0001ee16  dashboard gauges / counters / score (incremental)
G_26d8c = 0xff
sky colour patch: front copper list word +0x92 (= COLOR01 value of the playfield) = sky colour,
                  or G_25368 on odd counts of G_25366-- (sky flash: 0xfff white / 0xf00 red, 5 frames)
FUN_000150b0  present: flip views (COP1LC := back view's copper list), clear G_2550e
```
Because the flip clears `G_2550e`, the next frame starts at the first VBL **after** the flip → proper
double buffering, max 50 fps, otherwise 25/16.7/12.5 … fps. **No fixed frame rate.** **[H]**

### 1.5 Logic tick FUN_00011386 (12.5 Hz) – contents relevant to timing [H]
```
if paused return
if G_24fd4 == 0 (flying):  every 0x50 ticks (6.4 s): G_24fda-- (unless ==0x80)
                           every G_270b8 ticks:      G_24fd6--   (fuel – other agents)
G_27296 ^= 1                              (half-rate toggle, 6.25 Hz)
bob: if --G_252fc < 0 { G_252fc = G_25338; G_246ba = (G_246ba+1)&7; G_252fe = table_24b94[G_246ba]+1 }
     table_24b94 = {1,2,3,2,1,2,3,2}  → bob offset 2,3,4,3,2,3,4,3 (ship/sea bobbing, render copy G_26da6)
G_26c92 = input_queue_pop()               the input word for this tick
if (G_26c8e==0 || --G_26c8e==0) { FUN_112b0(); FUN_11460(); }
FUN_1c660 (player), FUN_1e7d6 (enemy planes), FUN_12132 (continuous sound params), FUN_1b682,
FUN_12066 (sound channel arbitration), FUN_11274, FUN_11bfc, FUN_10a72, FUN_119bc,
G_27298 = max(0, G_27298-1), FUN_11622, FUN_11510, FUN_11cae, FUN_11de4, FUN_11c5e
```
**Interface warning for other agents:** several *render-path* functions also mutate game state per drawn
frame: `FUN_13eee` soldiers walk ±3 px/frame and die/score, `FUN_10ee0` debris move, `FUN_13d78/13de8/14c3e`
(AA/flak timers, call `FUN_15460`), `FUN_1557c` balloons, `FUN_152f8` splash counters, wave frame, dashboard
needle animation, `FUN_10da6` muzzle-flash counters, `G_25318` (render frame counter 0..99) which the logic tick
also reads. On the STE, render at a fixed 25 Hz (2 frames per logic tick) or 12.5 Hz to stay close.

### 1.6 Demo record/playback [M]
`G_26c9c`: 0 none, 1 playback ("wofdemo" file loaded by FUN_18262), 2 record (when the exe gets a CLI arg,
`G_26ed6 != 0`; 5000-byte buffer). Byte 0 = rank, then one input byte per logic tick. During demo modes each
drawn frame consumes exactly 2 ticks (budget G_26c94=2).

---------------------------------------------------------------------------------------------------
## 2. Display hardware use, copper lists, double buffering

### 2.1 Own copper-list system [H]
The game builds its own copper lists (not Intuition screens). Copper list = `{u16 max, u16 count, (u16 reg,u16 val)…}`,
terminated with 0xfffffffe and loaded by writing `COP1LC` directly (`FUN_1aa0e`).
Helpers: `FUN_199bc` MOVE, `FUN_19a08` MOVE.L (two MOVEs), `FUN_19a9c` WAIT(x,y): `y += 0x2c`, clamp y 0..0x106,
x = (x/4)*2 clamp 0..0xe2, if y>255 first insert WAIT(line 255) (PAL wrap), entry `((y<<8)|(x&0xfe)|1, 0xfffe)`.

"View" struct (0x27948 = view A, 0x27956 = view B):
`+0 u16 dash-cache offset (0 / 0x14)`, `+2 copper list (1000 bytes)`, `+6 first viewport`, `+10 screen memory`.
Screen memory 0x159a0 bytes allocated once (`G_27ba8`, B = +0xacd0).
"Viewport" struct (0xb0 bytes; 0x27698/0x277f0 view A, 0x27744/0x2789c view B, 0x271e6 ticker shared):
```
+0x00 next              +0x04 BitMap (BytesPerRow,Rows,Flags,Depth@+9,pad,Planes[]@+0xc)
+0x2c RastPort          +0x90 split x (0)      +0x92 split line (relative y)   +0x94 split enabled
+0x98 palette[32] ptr   +0x9c split palette[32] ptr
+0xa0 display bytes/row (>0x3c → HIRES)   +0xa2 display height   +0xa4 x   +0xa6 y   +0xa8 bitmap width px  +0xaa bitmap height
```
`FUN_1a0d4` builds a view's copper list: `BPLCON0=0x0200`; 8 sprites parked (SPRxPOS=0x0300, CTL=0x0406, pointers);
then per viewport: [WAIT(y-1), BPLCON0=0x0200 (blank line) for all but the first] → WAIT(y-1) + COLORxx
(1<<depth colours) → BPLCON1=(x&15)*0x11, DIWSTRT, DIWSTOP, DDFSTRT, DDFSTOP, BPL1MOD, BPL2MOD, BPLxPT →
WAIT(y) BPLCON0 = (depth | hires<<3)<<12 | 0x200 → optional split: WAIT(+0x92) + only the colours that
differ between palette and split palette (index saved in `G_27bbc`) → (WAIT end, BPLCON0 0x200).
`FUN_187ba` then appends the ticker colour gradient.

### 2.2 In-game screen layout (FUN_16c38 / FUN_16bd8) [H]
| viewport | y (rel.) | PAL line | size | depth | mode | palette |
|---|---|---|---|---|---|---|
| playfield | 0 | 0x2c–0xcd | **320 × 162** (bitmap = display, 40 B/row, no scroll margin) | **5 (32 col)** | lowres, BPLCON0 0x5200, DIW 0x2c81/0xcec1, DDF 0x38/0xd0 | `wingspalette` (day) / `night.p`; split to `ocean.palette` / `nightocean.p` |
| (blank) | 162 | 0xce | 1 line | – | BPLCON0 0x0200; dash colours loaded here | |
| dashboard | 163 | 0xcf–0xf3 | **640 × 37** | 4 (16 col) | hires, BPLCON0 0xc200, DDF 0x3c/0xd4 | `iff-dash` CMAP / `nightdash` |
| (blank) | 200 | 0xf4 | 1 line | | | |
| message ticker | 201 | 0xf5–0x101 | 640 visible of a **672 × 13** 1-plane bitmap (modulo 4) | 1 | hires 0x9200 | col0 = 0 (black), col1 = per-line copper gradient |

Total 214 lines from line 0x2c (needs the PAL >255 wait). Playfield bitmap 40×162×5 = 32400 B + dash 80×37×4 = 11840 B
= 0xacd0 per buffer. Ticker bitmap (0x444 = 13×84 B, `G_27bb0`) is **single-buffered**, shared by both views and written by the VBL.
Ticker gradient (FUN_187ba): COLOR01 at relative lines 201..210 = `0777 0999 0bbb 0ddd 0fff 0ddd 0bbb 0999 0777 0555`
(ticker colour 1 base = 0x777, set in FUN_18806).
Menus use `FUN_169a4`: one 320×200 4-plane viewport.

### 2.3 Double buffering [H]
`G_26d7c` = back view (being drawn), `G_26d80` = front view. `G_26d70` = back playfield viewport, `G_26d6c` = its
RastPort, `G_26d84` its BitMap. `FUN_16f20(view)`: COP1LC = view copper, front = view, back = other view.
Dashboard drawing is per buffer with a 20-byte cache per view (`G_27e80`/`G_27e94`, offset = view+0) so unchanged
instruments are not redrawn.

### 2.4 Other chip registers [H]
`0xbfe001 bit1` set at start (audio low-pass filter OFF / LED), cleared on exit. `VHPOSR` read for random seed (`FUN_15d5a`).
No sprites, no dual playfield, no hardware scrolling (BPLCON1 = 0 in game): **every frame is redrawn from scratch.**

---------------------------------------------------------------------------------------------------
## 3. Palettes, waterline split, night, colour effects

### 3.1 Files / tables
Pointer tables indexed by `night (G_252e0)`: `0x25840 {wingspalette, night.p}`, `0x25848 {iff-dash, nightdash}`,
`0x25850 {ocean.palette, nightocean.p}`, `0x25858 {dash.shp, nightdash.shp}`. (`palette`, `ocean.p` are not used in game.)
CMAP files: `'CMAP'+id+32 RGB triples` → 12-bit (`FUN_16dd6`). IFF: BMHD, BODY (ByteRun1), CMAP, and a private
**`CMP2`** chunk (`u32 line, 32 RGB` → split palette) (`FUN_1a452`). **CRNG chunks are ignored – there is no colour
cycling anywhere.** [H]

### 3.2 Night [H]
`FUN_000111fc` (each mission): `map = table_233af[rank*4+mission]`; if `map > 6` (maps h..o) then
`night = bit15 of the 4th random()` (50 %), else day.

### 3.3 Playfield palette (day)
`wingspalette`: 0 000, **1 0af (sky)**, 2 e62, 3 d30, 4 b10, 5 03d, 6 112, 7 393, 8 171, 9 050, 10 fe6, 11 fa2, 12 640,
13 730, 14 941, 15 a62, 16 c74, 17 d96, 18 fb8, 19 025, 20 147, 21 47a, 22 7ac, 23 bde, 24 0af, 25 334, 26 445, 27 667,
28 889, 29 aab, 30 ccd, 31 fff.
`ocean.palette` differs only in **2..15** (water blues a ef, 8de, 6ce, 5bd, 3ad, 19c, 08c, 07b, 06a, 059, 048, 037, 026, 015)
and **24** (112). Night files analogous.

### 3.4 Waterline palette split [H]
The playfield viewport has a split: at playfield line **L** the copper reloads colours 2..15 and 24 from the
ocean palette. `L` is rewritten every frame by `FUN_1876e` in the back copper list:
```
L = min(162, G_252f0),  G_252f0 = 151 + max(0, plane_alt - 131)   (normal view)
                        G_252f0 = 151                              (1/8 zoom view)
```
(initial value 0x96=150 from FUN_16c38). So everything drawn below the sea surface line (wave strip, hull
bottoms, island bases) uses the water colours for indices 2–15/24. When the plane is high (L ≥ 162) no water is visible.

### 3.5 Sky flash [H]
`G_25366` = frames, `G_25368` = colour; on odd counts the playfield COLOR01 (sky) shows the flash colour
(set to 5 frames with 0xfff or 0xf00 in FUN_146dc/149a6 – island destroyed / hits, other agents).

### 3.6 Dashboard palette
`iff-dash` CMAP: 000 07e 0bf 700 c60 da7 4a4 484 f77 f55 f00 000 334 667 99a dde (night: `nightdash`).
3-D view: colour 2 = sky, colour 1 = sea.

### 3.7 Message ticker (VBL-driven) [H]
Font `newarmyfont` (FUN_12794): `u16 height(12), u8 first(0x20), u8 last(0x7e), u8 width[n] (padded even), glyphs`
each glyph `((w+15)>>4)` words × height rows; offsets table `G_26ca6`, data `G_26d66`.
Message start: `FUN_1555a` (only if no message active, `G_25706==0`), usually via `FUN_15624` = sprintf + start.
Each VBL (in game): if `G_25518>0`: shift the whole 13×84-byte bitmap left by 1 px, `G_25518--`; if
`G_25530` char delay still running → done. Next char: `G_25518 = 672`; width `w`: if `w==0` (space) delay 10 VBLs,
else copy glyph to byte column 80 (x = 640, just right of the visible area) rows 0..h-1, delay `w+1` VBLs.
End of string → `G_25706 = 0`. **Scroll speed 50 hires px/s = 1 px/VBL.**

---------------------------------------------------------------------------------------------------
## 4. Camera, world → screen mapping

Units: world x in pixels (1 map cell = 8 px), world altitude y up-positive. Screen y down-positive.

**Normal view (`G_24e86 = 8` cell step, `G_24e84 = 0`)** [H]
```
camX        = G_24e80 = plane_x - 160           (plane always at screen x 160)
refY        = G_24e82 = 151 + max(0, plane_alt - 131)
screen_x    = world_x - camX
screen_y    = refY + 11 - world_alt             (FUN_15174 draw_world_object)
```
So the plane rises on screen until alt 131 (screen y = 31 for its reference point), then the camera follows
1:1 upward and the sea line drops (`refY` > 162 → no sea visible). No horizontal look-ahead in this code
(look-ahead, if any, would be inside the logic's G_24fca – flight agent).
Objects are culled if `screen_x < -128 || screen_x > 448` (before hot-spot); the blitter clips to the window.

**1/8 "high altitude" view (`G_24e86 = 1`, `G_24e84 = 3`)** [H] – selected each logic tick at the end of the
player logic `FUN_1c660`: `G_25300 = (plane_alt G_24fc8 > 186) ? 1 : 8` (`G_27d3c` points to `G_24fc8`):
```
camX = plane_x - 1280;   refY = 1208
screen_x = (world_x - camX) >> 3;   screen_y = (1208 + 11 - world_alt) >> 3
```
uses `8thscale.shp` frames, waterline fixed at 151, the sea is a flat colour-10 rectangle (0,151)-(319,162),
map objects at y = 151, map x snapped to 8 px.

---------------------------------------------------------------------------------------------------
## 5. Rendering

### 5.1 Blitter primitives (hand-written asm, 0x209bc–0x2155c) [H]
All take registers: `a0` frame, `a1` mask (0 = none), `d0,d1` = top-left x,y in bitmap pixels (callers subtract
the frame hot spot), `a6` = 0xdff000. Blitter is owned via graphics `OwnBlitter` (`FUN_212ce`) /
`WaitBlit+DisownBlitter` (`FUN_212d4`). Current target: `set_rastport FUN_2124a` (RastPort `G_26e6a`, BitMap
`G_2709e`, plane write mask = (1<<depth)-1). Clip rect `G_268ac` top, `G_268ae` bottom(excl), `G_268b0` left,
`G_268b2` right (x rounded to 16), set by `FUN_2129c`.

* `FUN_20b0c blit_shape` – cookie-cut blit, 3 passes for frame header bytes:
  - byte **12 = CLEAR mask**: for each dest plane bit (∧ rastport mask) BLTCON0 `USEA|USEC|USED, LF=0xCA` with
    BLTBDAT=0 → D = mask ? 0 : D
  - byte **13 = SET mask**: same with BLTBDAT=0xffff → D = mask ? 1 : D
  - then for each stored plane k (plane_map list at +14, 0-terminated, ≤6) and each dest plane in plane_map[k]:
    `USEA|USEB|USEC|USED, LF=0xCA` → **D = mask ? src_k : D** (replace, not OR; later stored planes win if dest planes overlap).
  Without mask (`a1=0`): A = 0xffff constant → the whole frame rectangle is written (opaque).
  Dest planes not named in clear/set/plane_map keep the background even inside the mask.
* `FUN_20ce2 draw_shape` (normal entry, a1=0): builds the mask on the fly into a 0x410-byte buffer (`G_27386`):
  1 stored plane → mask = that plane; ≥2 → OR of all stored planes; then calls blit_shape.
  **If width_bytes×height > 0x410 (1040) the frame is blitted WITHOUT mask = opaque rectangle.** This is why the big
  frames contain solid sky colour 1: `batb/batf/batm`, `dstb/dstm`, `crus`, `jrmt`, carrier `fcar/mcar/rcar`, `rank`.
* `FUN_20e24` XOR draw (`LF=0x6A`, D = D ^ src; set-mask planes are inverted) – muzzle flashes.
* `FUN_21010 fill_rect(x0,y0,x1,y1,colour)` per plane LF 0x0c (clear) / 0xfc (set), clipped.
* `FUN_21318` Cohen–Sutherland clipped line (used once for the arresting hook line when G_24fd4==7).
* `FUN_20f54` raw A/B/C→D blit setup (unused in game drawing).

**Corrections to ../README.md / tools/ppkc.py:** frame byte 12 is a *clear* mask (not "set"), byte 13 is the *set*
mask; transparency = all stored planes 0 (not "colour 0" of the composed pixel) except for frames >1040 B/plane,
which are opaque. E.g. ship hull frames (`b12=16`, map 1,2,4,8) produce colours 0–15 (plane 4 cleared), not 16–31.
Pixel formula inside mask: `dst = (dst & ~clr | set)` then for k in order: `dst = dst & ~map[k] | (bit_k ? map[k] : 0)`.

### 5.2 Shape banks (pointer tables of frame addresses) [H]
`FUN_15bc6(file, namelist)` → table. world.shp → `G_26d9a` (bank G_24582), hellcat.shp → `G_26dd2`, Torpedo.shp →
`G_26e60` (hc01-hc40 + bom/rc/rk/ro/tor weapons), japplane.shp → `G_24596`, 8thscale.shp → `G_26dc6`,
dash.shp/nightdash.shp → `G_26da2` (bank G_2458a), per-cell-type tables (incl. ships) `G_26ea4` (normal) /
`G_26ed2` (1/8), Japanese plane frames by heading `G_26ede` (56) / `G_26fbe`, 3-D view plane sizes `G_273ac`.

### 5.3 Screen clear / sea [H]
No buffer clear: `render_world` first fills (0,0)-(319, min(161, refY+1)) with **colour 1 (sky)**.
The sea is the **wave strip** (`FUN_13e6c`, drawn *after* the map objects): frame `wava..wavl` index
`0x4e + G_252de` (96×11, hot 16,10), 5 copies at x = `63-(plane_x&63)-80-16 + 96*i`, top y = waterline.
Wave frame `G_252de` steps 11→0 once every 2 drawn frames. With the camera at its normal height the strip
covers lines 151..161 exactly; nothing else is drawn below it. 1/8 view: colour-10 rect (0,151)-(319,162).

### 5.4 Draw order in a frame (painter's algorithm) [H]
`render_world FUN_13772`:
1. sky rect (colour 1)
2. **map cells**, left→right from cell `(plane_x-288)/8` (1/8: `(plane_x-2304)/8`), screen x starting
   `-128-(plane_x&7)` (+8 per cell; 1/8: +1 per cell) until x ≥ 464. Only anchor cells (bit15) with a frame:
   x = cell_x - hot_x, y = `G_252f0 + jitter*4 - hot_y` (jitter = bits 13..11; 1/8: y = 151). Carrier-deck cells
   (surface==1) go through `FUN_14eac` first. Per cell (any) `FUN_13b1c`: extras for type 5, 0x22 tower
   (flag animation every 2nd frame), 0x9f, 0x113 (island flag).
3. `FUN_1409c` carrier elevator 'elev' clipped to the deck
4. `FUN_103a6` **player plane** (clip bottom 161 / carrier deck via FUN_1526e; 1/8 view uses 8thscale frames),
   hook line, XOR muzzle flash while firing (pattern `table_24b58[n&3]`)
5. `FUN_10da6` list `G_2512a` (japplane frame 27/55 at waterline-4) and the 4 **enemy planes** `G_2517a`
   (+ XOR muzzle flash on alternate frames)
6. `FUN_13d78, 13de8, 14c3e, 13a18, 1391e` other world objects (AA flak, soldiers' guns, parked planes… other agents)
7. `FUN_13e6c` **wave strip** (covers hull bottoms)  8. `FUN_140e8` beach/edge pieces + fill
Then in render_frame: debris → soldiers → splashes → projectiles → weapon-select box → balloons → "gmov" →
dashboard (3-D view, instruments). Ticker: VBL.

### 5.5 Dashboard (hires 640×37, coordinates = d0/d1 passed before hot-spot subtraction, dash pixels) [H for positions, M for meaning]
Static background = `iff-dash` picture copied into both buffers at level start. Per frame (`FUN_1ee16`, only redrawn
when the value changed for that buffer):
* gauge A needle at (208,18)/(202,10) – value from `G_24fda` (`(v-0x60)*2 &~3`, ±4 per frame animation, blinking
  warning when < 0x74, period 10)  [M: engine/damage]
* gauge B needle at (431,18)/(424,10) – value `min(0x58, G_24fd6/2)&~3` (fuel), warning blink < 0x41, period 8
* weapon icon (16,11) = `G_252f4` (0 rockets 'misl', 1 bombs, 2 torpedo)
* 2-digit rolling counter (42,28)/(66,28), clip y 19–28, value `G_252bd` (0xff = blank) – ammo of selected weapon
  (`bnum` strip 91 px high, 8 px per digit, rolls 1 px/frame)
* 1-digit rolling counter (125,19) = `G_252ac` (planes left)
* score `G_2529c` "%07ld" at x=512, y=11, 14 px per digit (digit frames from table `G_24b4c` via blit_shape, clip y 11–18) [M]
* `G_252cf` (0..99) two digits (508/522,21) + 7-step bars at (534,19),(534,25)  [M: kills?]
* warning light (320,10) frame 32/36 if any enemy plane state&7 == 4 (`FUN_1f21a`)
* **3-D forward view** `FUN_1417e` (clip x 256..400, y 7..32): sky rect colour 2 (258,7)-(380,32), sea rect colour 1 from
  horizon `G_25336 = (plane_alt>>4)+24`; 11 depth bands (`G_245f2..G_24606` distances) scanning map cells ahead
  in flight direction, drawing scaled 3-D sprites (dug*/hut*/pil*/towr/dec*/3dt*) centred at x=319 plus enemy
  planes (`G_273ac`) and the carrier deck/landing view (`3dc*`, `dec0-3`, FUN_14430) when over the carrier; target
  reticle 'targ' at y = 13 + (81-alt)/4 (alt<81) (`FUN_141b4`). Not drawn in the 1/8 view. Exact band tables not
  dumped (structure only) [M].

### 5.6 Misc
'selt' (96×72) weapon-select box at screen (250,60) with icon `rock/bomb/torp` – drawn opaque (blit_shape, no mask).
'gmov' at (160,81) by name lookup (`FUN_20560`).

---------------------------------------------------------------------------------------------------
## 6. Sound effects (gameplay)

### 6.1 Driver (FUN_1e8b8 … 0x1ed78) [H]
Init `FUN_1e8b8` (from FUN_12570): clear 4 channel structs; INTENA off AUD0-3, DMACON off 0x000f, ADKCON 0x00ff;
**level-4 autovector 0x70 replaced** by `FUN_1ebaa`; INTENA 0x8780; AddIntServer(VERTB, pri 30, code `FUN_1ec64`).
Channel struct `G_27dbe + 30*ch`:
`+0 sample ptr (0=idle) +4 timestamp +8 start pending +10 len words +12 period +14 vol (16.16) +18 repeats +20 repeat
counter +22 target vol (16.16, -1=none) +26 vol slide step`.
* `FUN_1ea28 start(a0=data,d0=bytes,d1=chan,d2=period,d3=vol,d4=repeats)`: stops a busy channel, clears/enables its
  audio IRQ, fills the struct, sets pending.
* VBL `FUN_1ec64` (50 Hz): `G_27dba++`; pending channels that were stopped ≥2 VBLs ago get AUDxLC/LEN/PER/VOL and their
  DMA bit; volume slides toward target; DMACON |= started bits.
* audio IRQ `FUN_1ebaa`: per finished block: repeats<0 → loop forever; else `--counter < 0` → stop (DMA off, vol 0, free).
  repeats = 1 → play once.
* `FUN_1eb4c(ch,period,vol)` live update (negative = keep). `FUN_1eac0` stop channel. `FUN_1e94c` shutdown.
* `FUN_1e992` plays a {u32 len,u16 rate(Hz or kHz if ≤100),data} struct with period 3579545/rate – unused.

### 6.2 Samples (`FUN_13368`, raw signed 8-bit, length = file size) [H]
`Engine G_26da8 · splash G_26e04 · screech G_26df8 · scream G_26dfc · metal.clang.1 G_26d92 · boom G_26d8e ·
Grind.1 G_26dca · machinegun G_26de6` (sizes in G_254ca, 254ce, 254da, 254d2, 254d6, 254c6, 254de, 254c2).
Periods are Amiga periods (PAL clock 3546895 Hz → rate = 3546895/period).

### 6.3 Request slots and channel arbitration [H]
8 slots × 24 bytes at `G_272b8` (2 per channel): `+0 want(u16) +2 ptr +6 bytes +10 period +12 volume +14 repeats(-1 loop)`;
channel state at slot0 +16 (current ptr) / +20 (current period/vol).
`FUN_12066` (every logic tick): per channel use slot0 if wanted, else slot1, else stop; same sample → only update
period/volume; different → restart. All silent while paused or `'s'` sound-off (`G_25447`).

| ch | slot 0 (priority) | slot 1 |
|---|---|---|
| 0 | player machine gun: period 200, vol 64, loop; want = `G_252ba` (firing) | player **engine**: loop, period/vol dynamic |
| 1 | enemy machine gun: period 160, vol 57, loop; want = OR of enemy firing flags (+18) | enemy engine: period 330, loop, vol = f(distance to nearest enemy plane) |
| 2 | **boom**: period 500, once, vol = dist | **splash**: period 350 once (vol = dist); or period 800 vol 34 loop while G_252e4==1 |
| 3 | AA gun fire: machinegun period 320 loop, want/vol = `G_270b4/G_270b6` (vol = 64 - min(64, nearest_gun_dist/8)) | one-shots: metal.clang (450, once), screech (350, once), scream (380, once, vol = manual/2); Grind.1 (450, loop) while G_252e4 is 2 or 3 |

Continuous parameters `FUN_12132` (per tick):
* engine volume `G_2537c` → target `G_25378` (40 engine on, 0 off): +1/tick up, −2/tick down.
* engine period `G_2537e` → target `(G_25352>>7) + G_2537a(=808) + (altitude G_24fc8>>4)`: +20/tick up, −10/tick down
  (lower period = higher pitch; G_25352 is the speed-like value from the flight model, ≥ −3100).
* enemy engine vol from Manhattan distance d (`FUN_122ce`): `d>>=4; d>44 → 0; d≤5 → 64-4d; else 64-(d+20)`.
* distance volume for one-shots (`FUN_12306/122f6`): `d = |x-plane_x| + |20-plane_alt|; d>>=5; d>64 → 0 else 64-d`.

Triggers: boom/splash `FUN_10aa6` (projectile impact, splash on water), metal.clang `FUN_11460` (crash sequence,
after stopping all), screech `FUN_1ba80` (deck touch-down / hook), scream `FUN_11a8c` (soldier hit). Stop all `FUN_11f4e`.

---------------------------------------------------------------------------------------------------
## 7. Music (menus only)

### 7.1 Loading/playing (FUN_123dc play_song(name="wofsongs", n), FUN_12470 stop) [H]
`songplay` and `wofsongs` are separate hunk files loaded with dos `LoadSeg`; no music during gameplay.
`songplay` entry (first code) is a dispatcher `jsr (entry)` with `d0` = command:
`0 OpenTimerInt, 1 ReadInstruments(d1=song,d2=song table), 2 PlaySong, 3 StopSong, 4 CloseTimerInt, 5 GetSongStat,
6 FadeSong(d1=speed), 7 PlaySfx, 8 StopSfx, 9 SfxStat, 10 Pause, 11 Restart, 12 AdjustSfx` (symbols present in the hunk).
`wofsongs` first code returns `a0` = its DATA hunk (song table). play_song: if a song is loaded → Fade(2), wait
GetSongStat==0, else LoadSeg both + Open; then ReadInstruments(n) + PlaySong. stop: Fade(2), wait, Close, UnLoadSeg.
Songs used: **2** during intro `FUN_17e80`, **1** Broderbund/title/credits (FUN_18022), **4** rank selection
(FUN_18262), **0** high-score screen (FUN_19856); stopped when the mission starts.

### 7.2 Driver (songplay) [H]
Timer: CIA-B timer A via `ciab.resource` AddICRVector, continuous; tempo from song commands (TAHI 0x3c / 0x38,
TALO not set by the songs → [M] 0) ⇒ ≈46.2 / 49.5 ticks/s (709379 Hz E-clock). Own level-4 audio IRQ (saves/restores
vector 0x70). Period = `K[note] / (samplesPerHiCycle << octave)`, `K = 3579545/f`, note 27 = middle C (261.6 Hz).

### 7.3 wofsongs data format [H]
DATA hunk (39020 B, symbols): `songs[5] = {song1, song2, song3, song2, song4}`. Song = 4 track pointers + inline
instrument pointer list (`voices1` = voice0..6, 0-terminated). Voice (0x2e B): `+0 VHDR ptr, +4 BODY ptr, +8 83/ctOctave,
+10 8SVX file ptr, +18..+30 vibrato params, +34 arpeggio flag (0 in all voices), +36 arpeggio offsets {4,7,0,12}`.
Instruments (IFF 8SVX, 1 octave each): 1 SyntheBass (8363 Hz, sphc 8), 2 Omlead (sphc 16), 3 RoomBrass (sphc 8),
4 BassDrum3, 5 SnareDrum1, 6 Mech1 (sphc 32).
Track = list of 6-byte entries `{u32 pattern ptr, s16 transpose}`; pattern = 2-byte events:
`n<0xd9`: note `(n&0x7f)+transpose`, bit7 = tie/legato, arg = duration index into table (len,gate) pairs:
`96/86 48/43 32/28 64/58 24/21 72/64 12/10 84/75 60/54 36/32 6/5 90/81 78/70 66/59 54/48 42/38 30/27 18/16 8/7 16/14`
(ticks; note cut at `len-gate` remaining unless sustain);
`0xd9` next list entry, `0xda` end track, `0xdb` loop track, `0xdc i` instrument, `0xdd v` CIA TAHI, `0xde v` TALO,
`0xdf v` volume, `0xe0 v` sustain mode. Song loop lengths: song1 1536 ticks, song2 1152, song3 2688, song4 1344
(all 4 tracks agree). A converter to a tracker/YM format is straightforward from this.

---------------------------------------------------------------------------------------------------
## 8. Notes for the STE re-implementation
* Keep logic at 12.5 Hz (one tick = 4 VBL @50 Hz); render at 25 Hz (2 frames/tick) and move the per-frame
  state changes listed in 1.5 to fixed rates.
* Playfield 320×162 ×32 colours with a raster split at the waterline (only colours 2–15, 24 change): on the STE use a
  Timer-B/HBL palette change at line L; 5→4 planes needs a palette remap (sky=1, water colours 2–15).
* Sea = 11-line wave strip only; sky = flat colour 1; everything redrawn each frame.
* Dashboard is hires 640×37 4 colours-planes: needs a medium-res split or a 320-wide redraw.
* Sound: 4 channels, one/two requests each with fixed priority; engine pitch per formula; STE DMA sound can mix.

## 9. Open questions
* Exact meaning of G_24fda (gauge A) and G_252cf (dash counter) – flight/missions agents.
* What sets `G_24fca` (render x) – if the logic adds look-ahead the plane isn't always at screen centre.
* 3-D view band tables (G_245e2, G_245f2-G_24606, G_2461f, G_24685/95/a5) not dumped.
* Whether the wave strip shows a seam (frames are not 64-px periodic but scroll phase wraps every 64 px).
* CIA TALO initial value for music tempo.
