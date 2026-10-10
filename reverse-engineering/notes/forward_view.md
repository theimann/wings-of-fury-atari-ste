# Dashboard 3-D forward view (FUN_1417e) – implementation spec

Sources: `scratch/ann.s` 0x1417e–0x146c4 (hand-written asm), tables read from `reverse-engineering/wings.bin`
(`img[addr-0x10000]`), shapes decoded with `tools/rpck.py` + `tools/ppkc.py`.
Confidence: [H] read directly from code/bytes, [M] inferred, [?] open (see §8).

All coordinates are **dashboard bitmap pixels: hires, 640×37** (pixel aspect 1:2, i.e. half as wide as a
playfield pixel). All shapes below are hires art. Colours are **dashboard palette indices** (`iff-dash` CMAP,
render_sound.md 3.6): 1 = 07e sea, 2 = 0bf sky, 5 = da7 sand.

## 0. Inputs

| name | meaning |
|---|---|
| `px` = G_26dac | plane world x (render copy of G_24fca), px |
| `alt` = G_26db0 | plane altitude (render copy of G_24fc8) |
| `dir` = **G_24fdc** | plane direction −1 / +1, read **live** from the logic struct (not the render copy G_26eca) |
| `zoom` = G_24e86 | 8 = normal view, 1 = 1/8 view (set by the logic when alt > 186) |
| `map[]` = G_24578 | u16 cells; `surf = c & 3` (0 sea, 1 ship deck, 2 island), `type = (c >> 2) & 511` |
| `mapw` = G_24580 | map width in px (= cells*8); last cell pointer G_2457c |
| `H` = G_25336 | horizon row = `(alt >> 4) + 24` (asr; computed in render_world 0x13802 every frame) |
| enemy slots G_2517a | 4 × 52 bytes: +0 state, +38 altitude, +46 `(x >> 3) * 2`, +48 sprite index 0..55 |
| ship records | FUN_14a52(off): first match of destroyer G_253b0 (if G_252ca), battleship G_253ce (G_252c7), transport G_253ec (G_252cb), J-carrier G_2540a (G_252c8), own carrier G_25428 (always); match = `rec.x0 <= off <= rec.x1` (map byte offsets = cell*2). +18 = sink bonus (0 own carrier, 6000 J-carrier), +28 = 3-D frame base (0 own carrier and J-carrier, 184 transport, 208 destroyer, 248 battleship) |
| `noLanding` = G_2764c | byte, initial 0, persists across frames (§5) |

Cell distances below are in map cells (8 px) from the plane cell `xc = px >> 3` (asr), measured in flight
direction: `cell(d) = xc + dir * d`.

## 1. When, window, background [H]

Called once per rendered frame from render_frame (0x10300), unconditionally, after the dashboard rastport is
selected; draws into the back buffer, so the whole window is repainted every frame (no incremental state except
`noLanding`).

```
forward_view():                                   # FUN_1417e
    clip = x 256..399, y 7..31                    # FUN_1525c: top 7, bottom 32 (exclusive), left 256, right 400 (excl.)
    fill_rect(258, 7, 380, 31, colour 2)          # sky   (code passes y1 = 32, clipped to 31; both ends inclusive)
    fill_rect(258, H, 380, 31, colour 1)          # sea   (nothing if H > 31, i.e. alt >= 128)
    if zoom == 1: return                          # 1/8 view: only sky + sea, no objects, no reticle
    bands()                                       # §2  FUN_14206 (ends with the landing view §5)
    reticle()                                     # §6  FUN_141b4
```
The window is 123×25 px (x 258..380, y 7..31), centre column **319**. Shapes are clipped to x 256..399 /
y 7..31, not to the 258..380 rectangle (all shapes used are narrow enough or have transparent margins).
No test of player state: it is drawn while landed, crashing, dead etc.

Every shape is drawn with `draw_shape` FUN_20ce2 (mask = OR of the stored planes, see render_sound.md 5.1) at
```
left = 319 - hot_x          top = Y - hot_y          (Y = the reference row given below)
```
so the hot spot is the anchor: its column goes to x 319 and its row to Y.

## 2. Depth bands [H]

### 2.1 Tables (bytes/words read from the binary)

`T` = 12 words at **0x245f0** (the code addresses it as G_24606 backwards; G_245f2 is `T[1]`):
```
T = 6, 13, 21, 30, 40, 51, 63, 76, 90, 105, 130, 160
```
Per band `k` (loop counter d7, **10 = farthest, drawn first … 0 = nearest, drawn last**):

| k | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 |
|---|---|---|---|---|---|---|---|---|---|---|---|
| row Y = H + 10 − k | H+10 | H+9 | H+8 | H+7 | H+6 | H+5 | H+4 | H+3 | H+2 | H+1 | H |
| near = T[k] | 6 | 13 | 21 | 30 | 40 | 51 | 63 | 76 | 90 | 105 | 130 |
| far = T[k+1] | 13 | 21 | 30 | 40 | 51 | 63 | 76 | 90 | 105 | 130 | 160 |
| enemy planes: distance | 6–13 | 13–21 | 21–30 | 30–40 | 40–51 | 51–63 | 63–76 | 76–90 | 90–105 | 105–130 | 130–160 |
| terrain cells scanned: distance far … 2·far−near | 13–20 | 21–29 | 30–39 | 40–50 | 51–62 | 63–75 | 76–89 | 90–104 | 105–120 | 130–155 | 160–190 |
| ship lookup distance (2·far−near+1) | 21 | 30 | 40 | 51 | 63 | 76 | 90 | 105 | 121 | 156 | 191 |
| `S1[k]` G_24608 (island objects) | 6 | 6 | 5 | 5 | 4 | 4 | 3 | 3 | 2 | 2 | 1 |
| `S2[k]` G_24614 (ships) | 7 | 7 | 6 | 6 | 5 | 4 | 3 | 2 | 1 | 0 | 0 |
| `OFF[k]` G_245e2 (enemy planes) | 0 | 0 | 0 | 28 | 28 | 28 | 56 | 56 | 56 | 84 | 84 |

Note the asymmetry: terrain of band k is taken from the cells **beyond** `far` (far … far+(far−near), so cells
121–129 and 156–159 are never scanned), enemy planes from **near … far**.

Landing-view tables (§5): G_2461f = 102 bytes, `value[n] = min(n / 6, 15)` (6× each of 0..14, then 12× 15);
G_24685 = `0,0,0,0,0,0,0,0,1,2,3,4,5,6,7,8`; G_24695 = `2,3,4,…,17`; G_246a5 = `0,0,1,1,2,2,3,3,3,3,3,3,3,3,3,3`.

### 2.2 Loop

```
bands():                                               # FUN_14206
    hide = 4                                           # G_273aa: surface value hidden from the scan (4 = none)
    if 0 <= px < mapw and (map[xc] & 3) == 1:          # plane is above a ship deck
        rec = ship_at(xc*2)                            # FUN_14a52; no match -> own carrier record
        if rec.bonus(+18) == 0 or rec.bonus == 6000:   # own carrier or J-carrier
            hide = 1                                   # its cells are not drawn as band objects

    Y = H
    for k = 10 downto 0:
        near = T[k]; far = T[k+1]; count = far - near

        # (a) enemy planes, slots 0..3 in order                                    (§4)
        lo = xc + dir*near;  hi = xc + dir*far;  if lo > hi: swap
        for each slot e with e.state != 0 and 2*lo <= e.celloff(+46) <= 2*hi:      # both ends inclusive
            f = e.sprite(+48);  if dir >= 0: f = (f + 28) mod 56
            draw(G_273ac[f + OFF[k]],  Y = Y - 4 - (e.alt(+38) >> 2))              # asr

        # (b) scan count+1 cells, from distance far outward
        obj = -1; trees = -1; sand = false; last_surf = (stale value of G_255dd)
        for i = 0 .. count:
            c = xc + dir*(far + i)
            if c < 0 or c > last_cell: continue        # off-map cells are skipped entirely
            surf = map[c] & 3;  type = (map[c] >> 2) & 511
            last_surf = surf                           # G_255dd: surface of the LAST valid cell scanned
            if surf == hide: type = 0
            if type != 0:
                if 6 <= type <= 8: trees = type        # G_2532a
                elif obj != 34 and obj != 246: obj = type     # G_25328: last type wins, but 34/246 stick
            if surf == 2: sand = true
        after = (xc + dir*(far + count + 1)) * 2       # d6 after the loop: byte offset one cell past the scan

        # (c) draw, in this order
        if sand:        fill_rect(258, Y, 380, Y, colour 5)        # 1-px sand line (clipped: nothing if Y > 31)
        if trees >= 0:  i = shape_index(trees, last_surf, k, after)   # always the dash bank
                        if i >= 0: draw(DASH[i], Y)
        if obj >= 0:    (bank, i) = shape_index(obj, last_surf, k, after)
                        if i >= 0: draw(bank[i], Y)
        Y += 1

    if not noLanding: landing_view()                   # §5 (the clrb after it is a no-op)
```
`last_surf` is a global byte that is only written for valid cells: if every cell of a band is off-map it keeps
the value from the previous band/frame (irrelevant in practice, obj/trees are −1 then).

Consequences worth knowing when implementing (all [H], straight from the code):
* One object shape per band at most (plus the tree strip plus the sand line). The object is the type of the
  **farthest** non-zero, non-tree cell of the band, including types without a 3-D shape (beach 1/2, `bumb` 9,
  `cama` 11, …) – those make the band's object disappear.
* All shapes are centred on x 319: there is **no lateral position** in this view at all.
* Non-anchor cells count (every cell of a hut carries type 4).
* A band reaching past the far end of a ship (last cell = sea) draws nothing for that ship, because `last_surf`
  is then 0.

### 2.3 Cell type → shape (FUN_145a6) [H]

`DASH[i]` = frame number i of the dash name list (§3). Tests in this order:

| condition | shape index | frames (far → near) |
|---|---|---|
| type 6..8 (trees `tre1-3`) | `14 + S1[k]` | 3dl5, 3dl6, 3dl7, 3dl8, 3dl9, **dug0** (k = 0,1) [?] |
| type 4 (hut `huta`) | `27 + S1[k]` | hut1 … hut6 |
| type 5 (destroyed hut `hutb`) | `34 + S1[k]` | hutb … hutg |
| type 3 (bunker `dugo`) | `20 + S1[k]` | dug1 … dug6 |
| `last_surf == 1` (ship) | see below | |
| type 15 (pillbox `pila`) | `41 + S1[k]` | pil1 … pil6 |
| type 16..30 (`pilb..pilp`) | `48 + S1[k]` | pilb … pilg |
| anything else | none (−1) | |

Ship branch (`last_surf == 1`), with `D = (dir < 0) ? 10 : 0`:
```
if type == 34 or type == 246:              # carrier island/tower cell (own 'towr', J-carrier 'jrmt')
    return DASH[77 + D + S2[k]]
rec = ship_at(after)                       # 'after' from the scan loop, NOT the cell that set obj
if no record contains it or after < 0: return none          # noLanding unchanged
if rec.base(+28) != 0:                     # transport 184, destroyer 208, battleship 248
    noLanding = true                       # G_2764c = 0xff
    return CELLTAB[rec.base + D + S2[k]]   # G_26ea4, the world per-cell-type frame table
else:                                      # own carrier or J-carrier
    noLanding = false
    return DASH[60 + D + S2[k]]
```
`CELLTAB` entries 184.. are the ship banks' own frame lists, so the index resolves to (far → near, S2 = 0..7):

| ship | dir ≥ 0 | dir < 0 |
|---|---|---|
| transport (cruiseship.shp) | cl1 … cl8 | cr1 … cr8 |
| destroyer (destroyer.shp) | db1 … db8 | ds1 … ds8 |
| battleship (battleship.shp) | bb1 … bb8 | bs1 … bs8 |
| own carrier / J-carrier (dash) | 60..67 = 3dca … 3dch | 70..77 = 3dck, 3dcl, 3dcm, 3dcn, 3dco, 3dcp, 3dta, 3dtb [?] |
| tower cell 34/246 (dash) | 77..84 = 3dtb … 3dth, 3dti [?] | 87..94 = 3dtl, 3dtm, 3dtn, 3dto, 3dtp, ndl1, ndl2, ndl3 [?] |

(The `+10` fits the ship banks, which hold 10 sizes per direction; the dash list has only 8 per direction, so for
the carriers the dir < 0 indices land on the wrong frames – this is what the code does, see §8.)
Types 16..30 and 5 do not occur in the map files; 5 is written at run time when a hut is destroyed (0x14790).

## 3. Shape inventory

### 3.1 Bank and index [H]
* Dash bank: `shapes/dash.shp` (day) or `shapes/nightdash.shp` (night), chosen by G_252e0 (0x16540); loaded with
  the name list at **0x24118** (117 names) into the pointer table G_26da2. Shape index = position in that list:

```
  0 misl bomb torp olof olon targ bnum wnum ltar rtar
 10 3dl0 3dl1 3dl2 3dl3 3dl4 3dl5 3dl6 3dl7 3dl8 3dl9
 20 dug0 dug1 dug2 dug3 dug4 dug5 dug6
 27 hut0 hut1 hut2 hut3 hut4 hut5 hut6
 34 huta hutb hutc hutd hute hutf hutg
 41 pil0 pil1 pil2 pil3 pil4 pil5 pil6
 48 pila pilb pilc pild pile pilf pilg
 55 towr
 56 dec0 dec1 dec2 dec3
 60 3dca 3dcb 3dcc 3dcd 3dce 3dcf 3dcg 3dch   68 3dci 3dcj 3dck 3dcl 3dcm 3dcn 3dco 3dcp
 76 3dta 3dtb 3dtc 3dtd 3dte 3dtf 3dtg 3dth   84 3dti 3dtj 3dtk 3dtl 3dtm 3dtn 3dto 3dtp
 92 ndl1 … ndln (23 gauge needles), 115 gaug, 116 zero
```
* Frame header: +0 width in bytes, +2 height, +4 hot_x, +6 hot_y (signed).
* **Never drawn by this routine**: `towr` (55), 3dl0–3dl4, hut0, huta, pil0, pila, 3dci, 3dcj, 3dtj, 3dtk,
  `carr`, `hut7`, `ltar`, `rtar`, and the `zr4*` plane set (present in the file, never looked up).
* Ship frames come from the ship banks (4 stored planes → colours 0..15, used as **dashboard** palette indices
  because they are blitted into the dashboard bitmap).

### 3.2 Frames: `name w×h hot_x,hot_y` (day bank; `[night …]` = differing header in nightdash.shp)

Reticle: targ 32×9 15,4

Trees/land strip (14+S1): 3dl5 128×5 65,4 · 3dl6 128×6 65,5 · 3dl7 128×6 65,5 · 3dl8 128×7 65,6 · 3dl9 128×7 65,6 · dug0 16×1 7,0
(3dl*: canopy texture in colours 4,5,6,7 with a solid colour-5 bottom row; visible columns 5..126 → x 259..380)

Bunker (20+S1): dug1 16×1 8,0 · dug2 16×1 9,0 · dug3 32×2 11,1 · dug4 32×2 13,1 · dug5 32×3 12,2 · dug6 32×3 12,2

Hut (27+S1): hut1 32×4 23,3 · hut2 48×4 24,3 · hut3 48×5 23,4 · hut4 48×6 23,5 · hut5 48×7 23,6 · hut6 48×8 23,7

Destroyed hut (34+S1): hutb 32×3 23,2 · hutc 32×3 16,2 · hutd 48×4 24,3 · hute 48×4 27,3 · hutf 48×4 27,3 · hutg 48×5 26,4

Pillbox (41+S1): pil1 32×3 15,3 · pil2 32×4 14,3 · pil3 32×4 14,3 · pil4 32×5 15,4 · pil5 32×6 14,5 · pil6 48×7 29,6

Pillbox types 16..30 (48+S1): pilb 32×3 20,2 · pilc 32×3 22,2 · pild 48×4 23,3 · pile 48×4 24,3 · pilf 48×5 26,4 · pilg 48×5 28,4

Carrier hull, 60..67: 3dca 16×2 6,1 · 3dcb 32×4 15,3 [night 16,3] · 3dcc 32×4 15,3 [night 16,3] · 3dcd 48×5 24,4 [night 25,4] · 3dce 48×6 22,5 [night 23,5] · 3dcf 64×7 35,6 · 3dcg 80×8 34,7 · 3dch 80×9 34,8

Carrier hull, 70..75: 3dck 48×4 23,3 · 3dcl 48×5 23,4 · 3dcm 48×5 24,4 · 3dcn 64×6 31,5 · 3dco 64×7 32,6 · 3dcp 80×8 40,7

Tower, 76..84: 3dta 16×2 6,2 · 3dtb 16×3 15,5 [night 9,5] · 3dtc 16×4 15,6 [night 16,6] · 3dtd 16×5 24,8 [night 25,8] · 3dte 16×7 22,11 [night 23,11] · 3dtf 16×10 26,15 · 3dtg 16×11 31,17 [night 32×11 34,17] · 3dth 16×14 34,21 · 3dti 16×2 7,2

Tower, 87..91: 3dtl 16×5 −9,8 [night −9,9] · 3dtm 16×7 −8,10 · 3dtn 16×10 −11,14 [night −12,14] · 3dto 16×11 −14,16 [night −16,16] · 3dtp 16×14 −19,20

Needles reached by the tower index overflow (92..94): ndl1 32×10 24,2 · ndl2 32×8 25,2 · ndl3 32×6 26,2

Landing deck: dec0 64×4 33,10 [night 33,11] · dec1 64×5 33,11 [night 33,12] · dec2 64×6 33,12 [night 33,13] · dec3 64×8 33,14 [night 33,15]

Transport, cruiseship.shp: cl1 64×4 36,3 · cl2 64×7 34,5 · cl3 80×7 50,5 · cl4 80×9 46,6 · cl5 96×12 57,9 · cl6 96×15 54,11 · cl7 96×16 52,11 · cl8 96×18 49,13
 / cr1 64×4 31,3 · cr2 64×7 31,5 · cr3 80×7 36,5 · cr4 80×9 37,6 · cr5 96×12 44,9 · cr6 96×15 42,11 · cr7 96×16 45,11 · cr8 96×18 44,13

Destroyer, destroyer.shp: db1 32×7 19,4 · db2 32×10 13,7 · db3 32×15 20,12 · db4 48×18 23,14 · db5 48×19 21,15 · db6 32×20 16,15 · db7 64×23 32,17 · db8 48×27 25,19
 / ds1 16×8 8,5 · ds2 32×12 18,8 · ds3 32×16 18,10 · ds4 48×19 25,13 · ds5 48×21 19,15 · ds6 64×23 30,16 · ds7 64×25 26,18 · ds8 64×27 26,18

Battleship, battleship.shp: bb1 32×8 12,6 · bb2 48×10 25,8 · bb3 32×13 20,10 · bb4 48×17 24,13 · bb5 48×22 24,16 · bb6 48×25 24,18 · bb7 64×26 36,19 · bb8 64×29 28,20
 / bs1 48×8 24,6 · bs2 48×12 22,9 · bs3 48×14 22,9 · bs4 48×16 28,10 · bs5 48×19 21,13 · bs6 64×22 31,15 · bs7 64×24 35,16 · bs8 64×26 27,16

Enemy planes (dash bank, 63 frames, all 32 px wide), `name h hot_x,hot_y`:
```
size 1: zr10 4 17,2  zr11 3 17,1  zr12 4 17,1  zr13..zr19 7 17,3  zr1a 4 17,1  zr1b 4 17,2
        zr1d 4 15,2  zr1e 3 15,1  zr1f 4 15,1  zr1g..zr1m 7 15,3  zr1n 4 15,1  zr1o 4 15,2  zr1p 4 15,2
size 2: zr20 3 17,1  zr21 3 17,1  zr22 4 17,1  zr23..zr29 5 17,2  zr2a 4 17,1  zr2b 3 17,1
        zr2d 3 15,1  zr2e 3 15,1  zr2f 4 15,1  zr2g..zr2m 5 15,2  zr2n 4 15,1  zr2o 3 15,1  zr2p 3 15,1
size 3: zr30 2 17,1  zr31 2 17,0  zr32..zr36 3 17,0  zr3k..zr3n 3 15,0  zr3o 2 15,0  zr3p 2 15,1
```
Totals for everything reachable: **183 distinct frames** (135 dash + 48 ship), bounding boxes 72 304 px
(dash 27 008, of which planes 9 024; ships 45 296), 29 500 non-transparent px. Largest: 128 px wide (3dl*),
29 px high (bb8). The opaque-blit rule (width_bytes × h > 1040) never applies.

## 4. Enemy planes [H]

Condition and position: §2.2 (a). Any non-zero slot state counts (flying, falling, burning wreck).
`e.celloff = (e.x >> 3) * 2` is refreshed in the render snapshot (0x10ff2). A plane exactly on a band boundary
(distance 13, 21, …, 130) is drawn in both bands. Reference row `Y_band − 4 − (alt_enemy >> 2)`: absolute enemy
altitude, not relative to the player; x always 319 − hot_x. Planes are drawn **before** the band's sand line,
trees and object, so those overdraw them.

Frame table G_273ac, 168 pointers, built at 0x1d1ea (name with 3rd char = '1'+j looked up in the dash bank):
```
G_273ac[j*56 + i]      = "zr" + ('1'+j) + A[i]        j = 0..2 (size 1 = largest), i = 0..27
G_273ac[j*56 + 28 + i] = "zr" + ('1'+j) + B[i]
A (0x26068) = 0 1 1 1 2 2 2 3 3 4 4 5 5 6 k k l l m m n n n o o o p p
B (0x260d8) = d e e e f f f f g h h i i j 7 7 8 8 9 9 a a a b b b 0 0
```
`e.sprite` (+48) = manoeuvre frame 0..27, +28 when the enemy's dir != −1 (enemies.md §7).
Index used: `f + OFF[k]` with `f = sprite` (player dir < 0) or `(sprite + 28) mod 56` (player dir ≥ 0).
Because OFF steps by 28 while the table's size stride is 56, the result is:

| bands k | f = 0..27 | f = 28..55 |
|---|---|---|
| 0–2 | size 1, A[f] | size 1, B[f−28] |
| 3–5 | size 1, B[f] | size 2, A[f−28] |
| 6–8 | size 2, A[f] | size 2, B[f−28] |
| 9–10 | size 2, B[f] | size 3, A[f−28] |

## 5. Carrier deck / landing view (FUN_14430) [H]

Called at the end of `bands()` when `noLanding == 0`.
`noLanding` is set when a band resolves a transport/destroyer/battleship (base ≠ 0) and cleared only when a band
resolves the own carrier or J-carrier; nothing else resets it (4 references in the whole program: 0x1441a,
0x14426, 0x1464e, 0x14656), so it carries over between frames.

```
landing_view():
    if not (0 <= px < mapw) or (map[xc] & 3) != 1: return       # only above a deck cell (any ship)
    step = (dir >= 0) ? -1 : +1                                  # scan BACKWARDS (against flight direction)
    n = 0
    while ((map[xc + step*n] >> 2) & 511) != 0: n += 1           # cells to the first type-0 cell behind; no bounds check
    idx  = G_2461f[n]                 # = min(n / 6, 15)
    yb   = H + 9 + idx                # H + G_24695[idx] + 7
    v    = G_246a5[idx]               # 0,0,1,1,2,2,3,3,3,…

    clip top = H + G_24685[idx]       # = H + max(0, idx - 7)   (instead of 7)
    draw(DASH[56 + v], Y = yb + 1)                     # dec0..dec3: striped deck, tapering towards the horizon
    draw(DASH[dir >= 0 ? 65 : 73], Y = yb)             # 3dcf / 3dcn: near part of the deck
    clip top = 7 (restored)
    draw(DASH[dir >= 0 ? 81 : 89], Y = yb)             # 3dtf / 3dtn: island/tower, left of centre / right of centre
```
* The only inputs are `n` (how far along the deck the plane is, counted from the deck end behind it), `dir`,
  and the altitude through `H`. **No lateral data, no speed, no relative altitude** besides the horizon shift.
* As the plane advances along the deck the picture moves down 1 row per 6 cells (48 px) and the far deck piece
  grows dec0 → dec3 during the first 36 cells; from idx 8 on the top of the deck is cut off 1 row more per step.
* Own carrier: 95 deck cells (x0 = anchor−160, x1 = x0+192 byte offsets), so n ≤ 95, idx ≤ 15.
* Rows with the day hot spots: dec top = `yb + 1 − hy` (hy 10/11/12/14), 3dcf rows `yb−6 … yb`,
  3dtf rows `yb−15 … yb−6` at x 293..308, 3dtn rows `yb−14 … yb−5` at x 330..345.
* While above the own carrier or the J-carrier, `hide = 1` removes all deck cells from the band scan (§2.2), so
  the ship is shown only by this view. Above a destroyer/battleship/transport deck the ship is still drawn in the
  bands **and** this view is drawn too unless `noLanding` is set.

## 6. Target reticle (FUN_141b4) [H]

Drawn last, in every frame of the normal view (not in the 1/8 view), no other condition:
```
ry = (alt >= 81) ? 13 : 13 + ((81 - alt) >> 2)        # signed compare, logical shift; alt 0 -> 33, alt 80 -> 13
draw(DASH[5] 'targ', Y = ry)                          # left = 304, rows ry-4 .. ry+4, clipped to y 7..31
```
So above altitude 80 the reticle sits at row 13 (rows 9..17); below it sinks 1 row per 4 px of altitude and
is cut by the window bottom (centre on row 31 at alt 6..9; ry = 33 at alt 0..1, so rows 29..31 of it still show).

## 7. Draw order summary

sky rect → sea rect → for k = 10..0: [enemy planes slot 0..3 → sand line → tree strip → object/ship] →
landing view (dec, 3dcf/n, 3dtf/n) → reticle.

## 8. Unclear / to verify

1. **Carriers when flying left** (0x14610–0x14674): `D = 10` gives DASH[70..77] = 3dck…3dcp, 3dta, 3dtb instead
   of the 8-frame set 3dci…3dcp at 68..75. Looks like an original bug (the +10 is right for the ship banks only).
   The spec above is what the code does; worth one look in the emulator (own carrier ahead while flying left:
   far band shows the 48×4 `3dck`, nearest bands a tiny tower piece).
2. **Tower cells 34/246** (0x1462c): base 77 (not 76) → dir ≥ 0 uses 3dtb…3dti, dir < 0 runs into the gauge
   needles ndl1..ndl3 for bands 0–4. Same class of off-by-N; code is unambiguous, intent is not.
3. **Trees base 14** (0x1467e): `14 + S1` = 3dl5…3dl9 and then `dug0` (16×1) for bands 0 and 1. Unreferenced code
   at 0x14694 computes `10 + S1[k]` (3dl1…3dl6), probably the older/intended variant. Nothing branches to it.
4. **Enemy plane OFF table** 0x245e2 (0,28,56,84) vs. table stride 56 (0x1d2da `mulsw #56`): mixes orientation
   and size as tabulated in §4; `zr4*` frames are never loaded (loop limit 3 at 0x1d33e). Probably unintended.
5. **`noLanding` stickiness** (G_2764c): after any enemy ship other than the J-carrier was shown, the landing view
   stays off until a band resolves a carrier again. Initial value 0 in the data hunk; I found no reset at level
   start – confirm there is none outside the four references (search was on ann.s annotations only).
6. `ship_at(after)` uses the cell one past the band's scan (distance row in §2.1), and `last_surf` the last valid
   cell: a ship is therefore drawn only in bands whose scan ends on a deck cell. Read from the code, not observed.
7. `dir` is read from the live logic variable G_24fdc while x/alt are render copies; assumed to be only ±1
   (0 would scan the same cell repeatedly).
8. Not examined: whether the dashboard art around x 256..257 / 381..399 can be overdrawn by a wide shape
   (clip is 256..399, background rect 258..380). All frames listed fit for the day bank; night `3dtg` is 32 wide.
9. Fill colours: `fill_rect` d4 = 2 / 1 / 5 taken as colour index (render_sound.md 5.1); 3-D shapes use dashboard
   colours 2..15, mostly 12..15 (greys) and 3..7 (island).
