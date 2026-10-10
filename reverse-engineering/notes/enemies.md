# Enemies and world objects (Wings of Fury, Amiga)

Scope: the island garrisons (huts, bunkers, pillboxes, soldiers, island flag), airfields, enemy ships (guns, planes on deck, torpedo hits, sinking), and enemy aircraft (Zeros and the carrier bomber).
Addresses are absolute (A4 = 0x2af4e). `G_xxxxx` means global 0x2xxxx. Confidence: **[H]** high (read in asm), **[M]** medium, **[L]** guess.

## 0. Frame structure: which code runs when

This changes what the briefing said:
- **Logic tick** `FUN_00011386`. `FUN_000114d8` runs it `G_272a4` times per displayed frame (catch-up loop). Order of calls in one tick:
  `1c660` player → **`1e7d6` enemy planes** → `12132` sound mixer → **`1b682` player gun vs enemy planes** → `12066` → `11274` camera copy → `11bfc` →
  `10a72` weapons (bombs, rockets, torpedoes, enemy bomb) → `119bc` player bullets → `G_27298--` (launch cooldown, floor 0) →
  **`11622` airfields** → **`11510` ship plane launch** → **`11cae` ship sinking** → **`11de4` soldiers leaving buildings** → `11c5e`.
- **Render frame** `FUN_00010228`. It is not render-only: some game logic runs here once per displayed frame.
  `10f88` copies logic state into render copies (inside Forbid/Permit). Then `13772` draws the world.
  **`13d78` bunker guns and `13de8` pillbox guns aim, fire, damage the player and burn here.** So does **`14c3e` ship guns**.
  `13eee` moves, animates and kills soldiers, and checks whether an island is cleared.
  For an exact port, keep this split: AA hit rolls and soldier movement are per displayed frame, not per logic tick. **[H]**
- Render copies made in `10f88`:
  - zone `+16/+18` ← `+6/+8`
  - ship `+26` ← `+20` (sink stage)
  - `G_24e88[5][64]` ← `G_24fe6[5][64]` (ship plane blocks)
  - each enemy plane: `+46 = (x>>3)*2` (map cell byte offset)

Random numbers: `FUN_000203be` returns a random number in d0. `FUN_0001cac8(n)` returns `rand % n`. `G_2531a` is also used as a cheap random source.

## 1. Mission indexing and per-mission tables

- `G_2530e` = rank (0..6). `G_25310` = mission within the rank, **1-based**.
- `G_25498` u16[7] = missions per rank: `3,3,2,2,1,1,3`. Used by `15694` (advance mission) and `12adc` (map index = sum of earlier ranks + mission - 1). **[H]**
- `G_233af` byte[rank*4 + mission] = global mission index **m (0..14)**, which equals the map letter a..o:
  rank0: 0,1,2 · rank1: 3,4,5 · rank2: 6,7 · rank3: 8,9 · rank4: 10 · rank5: 11 · rank6: 12,13,14. **[H]**
- Every difficulty value is per mission m, not a separate rank multiplier. I found no other rank scaling in enemy code. AI speeds and fire probabilities are constants.

| table | address | layout (index m) | meaning |
|---|---|---|---|
| airfields | 0x23444 | 4 bytes: (planes, maxAir) × 2 airfields | see §4 |
| destroyer planes | 0x23480 | 2 bytes (n, maxAir) | planes carried on the ship |
| battleship planes | 0x2349e | 2 bytes | |
| transport planes | 0x234bc | 2 bytes | |
| J-carrier planes | 0x234da | 2 bytes | |
| island bonus | 0x233cc | u16[4] per m (8 bytes) | bonus when island i is cleared |
| night flag | `FUN_000111fc` | | `G_252e0 = (m>6) ? random 0/1 : 0`. Probably the night palette **[M]** |

Values dumped from wings.bin (m: value):
- Airfields: 3:[2,1] 4:[3,1] 7:[3,1] 8:[2,1] 10:[3,1] 11:[3,2],[3,2] 12:[3,2],[3,1] 13:[4,1] 14:[4,2] (others 0).
- Destroyer: 0:[4,3] 6:[3,2] 7:[3,1] 8:[4,1] 9:[4,2] 11:[3,2] 13:[4,2] 14:[4,2]
- Battleship: 0:[5,3] 9:[6,2] 10:[5,2] 11:[4,2] 12:[5,2] 13:[5,3] 14:[5,2]
- Transport: 0:[3,3] 5:[2,1] 6:[3,1] 8:[2,1]
- J-carrier: 12:[6,3] 14:[7,3]
- Island bonus (islands 0..3):
  - m0: 450
  - m1: 500, 700
  - m2: 1000, 600, 750
  - m3: 1500, 1100
  - m4: 1000, 900, 1500
  - m5: 900, 900
  - m6: 900, 1200, 1200
  - m7: 900, 1600, 1000
  - m8: 1500, 1300, 1300
  - m9: (no islands)
  - m10: 1600, 1500, 2000
  - m11: 2400, 0, 2500
  - m12: 3000, 2000, 2200, 2800
  - m13: 2500, 3000, 3200
  - m14: 3000, 3000, 3500

Quirk: battleship m9 has n=6 but the position table has only 5 entries. The 6th entry is read from the next table (transport header at 0x23548). Reproduce or clamp.

## 2. Map parsing: `FUN_00012d5a` (+ `FUN_00012c84`, `FUN_0001252c`, `FUN_0001350e`)

Cell format: see the briefing. In the code, a cell position is usually a **byte offset `off` into the map = cell*2**. World x in px = `off*4`. Only cells with **bit 15 (anchor)** count.

**Pass 1** (`12d5a`). Scan all anchor cells:
- type 4 hut → `G_252d7++` (huts). Type 3 bunker → `G_252d6++`. Type 0x0f pila → `G_252d5++` (pillboxes). Each of these sets `G_25550 = -1` (current island has enemies).
- type 2 `bchr` (right beach = end of an island) → `G_252d4++` (islands). If `G_25550` was set: `G_252d2++`, `G_252d3++` (enemy islands, and enemy islands remaining), then clear `G_25550`.
- type 0x21 rcar → own carrier record `G_25428`, only the first one:
  - `+4=-1`, `+12=4` (torpedo hits to sink), `+14=33`, `+18=0`, `+22=20`
  - `x0 = off-160`, `x1 = x0+192`
  - also clears `G_25312`
- Ships, only the first of each kind. For each: `G_252c0++`, `G_252c1++` (ships present / ships remaining), then fill the 30-byte ship record (§6) and call `1252c` (plane block):

| type | record | flag | +10 guns | +12 torp hits | +14 gun base y | +18 sink bonus | x0 / x1 (byte offsets) | plane block | gun-x table |
|---|---|---|---|---|---|---|---|---|---|
| 0xE4 destroyer | G_253b0 | G_252ca | 8 | 1 | 27 | 2500 | off-32 / x0+160 | G_24fe6 | G_25552 |
| 0x10D battleship | G_253ce | G_252c7 | 14 | 2 | 27 | 4500 | off-32 / x0+192 | G_25066 | G_25562 |
| 0xCC transport | G_253ec | G_252cb | 4 | 1 | 28 | 1000 | off-16 / x0+32 | G_250a6 | G_2559c |
| 0xF2 J-carrier | G_2540a | G_252c8 | 15 | 3 | 21 | 6000 | off-32 / x0+156 | G_250e6 | G_2557e |

Note: the anchor types are 0xE4, **0x10D** and **0xF2** (only the anchor cell matters). +22 = 20 is set for all records except the battleship. The battleship's +22 is not set by the parser **[H]**.

The value called "HP" in the briefing (1000/2500/4500/6000) is **not hit points**. It is the **score bonus for sinking** (+18). Ships sink only from torpedo hits (+12).

**Allocations.** `FUN_000158ec(bytes)` is malloc:
- `G_25448` = huts × 16 bytes
- `G_2544c` = bunkers × 16 bytes
- `G_25314` = (huts+bunkers) × 5 = soldier count; `G_25450` = `G_25314` × 8 bytes
- `G_25454` = pillboxes × 14 bytes

**Pass 2.**
- Fill hut, bunker and pillbox records (`13216`, `131c8`, `13236`).
- Type 1 `bchl` offsets go to list `G_25380[]`. Type 2 `bchr` offsets go to `G_25388[]`. Island index `i` starts at 0 and increments after each `bchr`.
- Island counters `G_253a0[i]` (4 bytes each): `+0` soldiers alive, `+2` pillboxes alive. Each hut or bunker adds 5 soldiers; each pillbox adds 1.
- `G_25390[i]` (4 bytes): `+0` offset of the island's first bunker, `+2` offset of its last bunker.

**Ship shapes** (`FUN_00013252`, at load):
- Loads battleship.shp, destroyer.shp, cruiseship.shp (transport) and japcarrier.shp.
- Sets ship `+28` = 248 (battleship), 208 (destroyer), 184 (transport), 0 (J-carrier). Meaning unknown; probably drawing related **[L]**.
- `1350e` allocates the gun array (`+6` ptr, `+10` × 14 bytes). Gun x = table[k] + x0*4.
- Transport guns 1 and 2 get `+6 = 5` (y offset).

**Zones** `FUN_00012c84`. Airfields are made from cells of type 0x114 / 0x115, which must come in pairs:
- The first cell of a pair gives `x_start` (px = cell*8). The second gives `x_end` and the direction: 0x114 → -1, 0x115 → +1.
- Up to 4 records at `G_2524a`, 20 bytes each. Two bytes are consumed per airfield from the per-mission table: first byte → `+6` planes, second → `+4` max airborne.

Rows from `maps/*.map` (anchor counts):

| map | huts | bunkers | pillboxes | islands | airfields | ships |
|---|---|---|---|---|---|---|
| a | 2 | 2 | 0 | 1 | | |
| c | 7 | 7 | 4 | 3 | | |
| d | 6 | 6 | 4 | 2 | 1 | |
| f | | | | | | transport |
| h | | | | | | destroyer |
| j | | | | 0 | | destroyer + battleship |
| m | 14 | 13 | 24 | 4 | 2 | battleship + J-carrier |
| o | 11 | 9 | 30 | 3 | | J-carrier + battleship + destroyer |

## 3. Island garrison

### Records

**Hut** (`G_25448`, 16 bytes) and **bunker** (`G_2544c`, 16 bytes). **[H]**

| off | size | meaning |
|---|---|---|
| +0 | long | anchor byte offset (high word 0). Lookup key in `14b54`. |
| +4 | w | left exit x px. Hut: x. Bunker: x-44. |
| +6 | w | right exit x px. Hut: x. Bunker: x+16. |
| +8 | b | soldiers inside. Init 5. |
| +9 | b | island index |
| +10 | b | soldiers queued to run out |
| +11 | b | countdown to next soldier leaving |
| +12 | w | hut: smoke puffs left (50 after destruction). Bunker: guns-silent delay (360 after re-manning). |
| +14 | w | hut: smoke puff delay. Bunker: re-man timer (200). |

**Pillbox** (`G_25454`, 14 bytes). Ship guns use the same layout, with +4 = x px. **[H]**

| off | meaning |
|---|---|
| +0 | anchor byte offset |
| +4 | x px. Ship guns only; pillboxes compute x from +0. |
| +6 | island index. On ship guns this is the y offset. |
| +8 | w: 0 = alive, -1 = destroyed |
| +10 | smoke puffs left (50) |
| +12 | puff delay |

**Soldier** (`G_25450`, 8 bytes, `G_25314` slots). **[H]**

| off | meaning |
|---|---|
| +0 | x px |
| +2 | byte: sign = direction (negative = left) |
| +3 | animation frame |
| +4 | death animation delay |
| +5 | island index |
| +6 | w state: 0 free, 1 running, 2 dying, 3 dead |

**Island counters** `G_253a0[i]` = {soldiers alive, pillboxes alive}.

### Objects occupy 4 cells

Huts, bunkers and pillboxes span 4 cells (32 px). The cell with bit 15 is the anchor.

`FUN_00014ae4(x)` searches the cells at x-8 .. x+16 for the anchor A. It returns a0..a3 = A-2 .. A+1 (byte offsets A-4 .. A+2). `FUN_00014b54(x)` turns that into the record pointer (a0) or d0 = -1.

### Bomb or rocket impact on an island: `FUN_000146dc` (called by the weapons code; weapon type = obj+34)

- **Hut** (cell type 4):
  - All 4 cells are rewritten to type 5 `hutb` (destroyed hut); bit 15 is kept.
  - Hut `+12=50`, `+14=1`, **score += 150** (`G_2529c`).
  - `14b40`: `+10 += +8`, `+8 = 0`, `+11 = 60`. The soldiers inside will run out.
- **Bunker** (type 3): the bunker is indestructible. If it has soldiers inside (`+8 != 0`): `+14=200`, **score += 200**, and `14b40` empties it as for the hut.
- **Pillbox** (types 0x0f..0x1d), **rockets only** (weapon type 0 = rockets; see weapons_missions.md. corrected 2026-10-02 and confirmed in play):
  - Damage bit = `1 << (4 - ((x/4 - off)/2 + 3))`. It is ORed into `(type - 0x0f)`, which is a 4-bit damage mask, and all 4 cells become `pila + mask`. The 16 sprites pila..pilp show progressively wrecked states.
  - If the pillbox is not already destroyed: `+8=-1`, `+10=50`, `+12=1`, **score += 200**, island pillbox count `-1`. **One rocket destroys it.**
- Explosion parameters: `G_25366 = 5`, `G_25368 = 4095` or `3840` when something was hit. These belong to the weapons/rendering agents.
- Afterwards the weapon kills soldiers within ±16 px: `11a8c(x, 16)`.

### Island cleared

This check is in `146dc` (last pillbox destroyed) and `13eee` (last soldier dead). **[H]**

When `soldiers == 0 && pillboxes == 0` for island i:
- `bonus = table_0x233cc[m][i]`, and score += bonus.
- `G_252d3--` (enemy islands remaining).
- If `G_252d3 <= 0` and `G_252c1 == 0` (no ships left): show message `G_2394a` ("All enemy forces on island have been destroyed . . . Bonus %ld points") and call `FUN_00015694` (mission complete: next mission or rank).
- Otherwise: queue the same message (`15624` → `G_25706`).

### Soldiers

- **Leaving a building** (`FUN_00011de4`, per logic tick, bunkers first, then huts): if `+11 != 0`, decrement it. When it reaches 0:
  - `FUN_00011e82` spawns one soldier, then `+10--`.
  - If more are queued: `+11 = (G_2531a>>4)&31`, or 3 if that is 0.
- **Spawn** `FUN_00011e82(d0 kind 1=hut / 2=bunker, d1 dir, a0 building)`:
  - Bunker: dir = +1 if it is the island's first bunker, -1 if it is the last, else 0. With probability about 1/32 the direction is negated.
  - Takes the first free slot: `+6=1`, `+5=island`.
  - If dir == 0, use a random byte (G_2531a). `+2` = dir byte.
  - x = `+4` (exit left) if the byte is negative, else `+6`. Then `+3 = byte&3` and `x += (byte&7)*4`.
- **Update and draw** (`FUN_00013eee`, per render frame, all slots):
  - State 1, running: `+3 = (+3+1)`, wrapping >4 → 0 (frames 0..4). Step = ±3 px. If the cell at x+step is sea (surface 0), reverse direction (negate +2 and the step). Then `x += step`. The soldier runs back and forth across the island.
  - State 1 entering a bunker: if the cell under the soldier is type 3 (bunker), find the bunker. If `+12 == 0 && +8 == 0`, set `+12 = 360`. Then `+8++` and free the soldier. **Soldiers run into bunkers and re-man them.**
  - State 2, dying: `+4` counts 2..0. Each time it wraps, `+3++`. When `+3 > 7` (frames 5, 6, 7): state 3, **score += 25**, `G_26c8c++` (kills), island soldiers `-1`, then the island-cleared check.
  - Sprite: world frame `0x6f + frame` (`guy0..guy7`), `+9` when facing left (`guy9..gy10`), drawn at y = 12. Dead soldiers (state 3) are not drawn in the normal view. In the 1/8-scale view a different index is used: `(frame&1)+1+0x6e`.
- **Kill** `FUN_00011a8c(x, r)`: all running soldiers with |sx - x| <= r get state 2, `+3=5`, `+4=2`, and sound `123ac`.
  - Callers: bombs and rockets (r=16), player bullets (`119bc`, r=16).
  - Then `11ae2(x, r)` destroys player torpedoes and the enemy bomb within r.
- **Bunker re-manning** (`FUN_00013d78`, render frame): an **empty** bunker counts `+14` down. At 0: `+14 = 200`, and `FUN_00014fee` sends one soldier from the nearest hut with at least 2 soldiers inside. The search starts at the bunker's island and continues through later islands. The soldier runs toward the bunker.
- **Soldiers never shoot** (no fire code found) **[M]**.

### Island flag

Map cell type 0x113 is drawn in `13b1c`. The island is found from `player_x/4` against the `bchr` list `G_25388`.
- If the island still has soldiers or pillboxes: Japanese flag animation, world frames 0xb0..0xb2 (`flg0..2`), stepping every 3 frames (`G_252d0`).
- Otherwise: frame 0xb3 `POST` (bare pole).
- Drawn only in the normal view.

There is **no surrender or flag-raising animation**. The `fgy*` sprites (0x8f..0x9e, `fgyx` = 0x9f) are the **carrier deck crew / landing signal officer** (cell type 0x9f). They are driven by `G_252af` / `G_255xx` in `13b1c` and `1bcce`, which is the player/carrier area. `flg3..6` are the US flag on the carrier.

### Destroyed hut smoke (`14e18`, via 13b1c for type 5 anchors)

While `+12 > 0`: every `+14` frames, `+12--`, `+14 = 50 - +12`. Each step spawns smoke `15460(x+16, 17, 5)`. The puffs come faster as they run out. Pillboxes and ship guns use the same scheme (`x+8`).

## 4. Airfields (zones): `G_2524a`, 4 × 20 bytes

| off | meaning |
|---|---|
| +0 | x_start px |
| +2 | x_end px |
| +4 | max enemy planes airborne |
| +6 | planes still parked |
| +8 | x of the plane rolling for take-off (0 = none) |
| +12 | take-off speed (0..56) |
| +14 | dir (-1 / +1) |
| +16 / +18 | render copies of +6 / +8 |

`FUN_00011622`, per logic tick:
1. **Roll.** If `+8 != 0`: `+12 = min(+12+1, 56)`, `x += dir * (+12>>3)`.
   - Past `x_end` (dir +1) or before `x_start` (dir -1): `FUN_0001e4d0(0, x, 0, dir)` (spawn an airborne Zero at altitude 0) and `+8 = 0`.
   - Any active roll ends the function for this tick.
2. **Launch.** Only if the cooldown `G_27298 == 0`. For each airfield, check:
   - `x_start - 480 <= player_x <= x_end + 480` (`G_26dba`)
   - `G_25126 < +4` (Zeros airborne)
   - `+6 > 0`

   If all hold:
   - `+6--`
   - `G_27298 = 100`
   - start x = `x_end - 32 - 64*+6` (dir -1) or `x_start + 32 + 64*+6` (dir +1)
   - `+12 = 0`
- **Drawing** (`13a18`): +16 parked planes at `x_end-32, -64, ...` (dir -1) or `x_start+32, +64, ...` (dir +1). japplane frame `jp21` (index 20, dir -1) or `jp22`. The rolling plane is drawn at +18. In the 1/8 view: 8thscale `zpn0` / `zpnn`.

## 5. AA guns: pillboxes, bunkers and ship guns (render frame)

**Bunkers** (`13d78`, `y = 20`). These are manned bunkers with `+12` (silent delay) expired.
- If `+12 != 0`, decrement it. Fire only on the frame it reaches 0, or when it was already 0.

**Pillboxes** (`13de8`, `y = 22`): every intact pillbox. Destroyed ones emit smoke (§3).

**Aim** `FUN_00014d50(x)` → frame or -1:
- -1 if the player state `G_24fd4 != 0` (only a flying player is shot at).
- In the 1/8 view: 50% → frame 90, else -1.
- Otherwise `FUN_00014db8(gx, px = G_26dac, alt = G_26db0)`:
  - `dx = px - gx`. If |dx| > 512, return -1.
  - `idx = ((alt>>5) - 1)*8 + dx/40 + 3` (signed, `divs`, truncates toward 0).
  - `v = G_24b6c[idx]` (signed byte).
  - Then `14d50`: if v < 0, return -1. Else `frame = 0x81 + v` (`gun0..gun6` barrel angle), and with probability 6/16 `frame += 7` (`gnf0..6` muzzle flash).
- The table is a flat array. Out-of-range rows and columns spill into neighbouring bytes, so reproduce it as a flat 1-D array starting at 0x24b6c, including bytes before it. Rows 0..9 from 0x24b6c:

```
alt 32-63   : 0 0 0 3 3 6 6 6
alt 64-95   : 0 1 1 3 3 5 5 6
alt 96-127  : 1 1 2 3 3 4 5 5
alt128-159  : 1 2 2 3 3 4 4 5
alt160-191  : 2 2 3 3 3 3 4 4
alt192-223  : 1 2 3 2 1 2 3 2      (looks like other data -> effectively random)
alt224-255  : 1 3 2 1 0 -112 -112 -112
alt256-287  : all -112 (no fire)
```

Columns are dx = -120..-81, -80..-41, -40..-1 (and 0..39, because of truncation), 40..79, 80..119, 120..159, 160..199, 200..239.
Example: at alt 40 and dx 0 the frame is gun3 (vertical). Hits are possible whenever the gun gets a frame.

**Hit roll** `FUN_00014f5c(gx)`. This runs every frame the gun got a frame, not only on muzzle-flash frames.
- `d = |gx - px|`. If d > 448, nothing.
- Track the minimum: `G_273a6 = min(d)`, and `G_273a4 = -1`. These drive the AA sound volume: `13772` sets `G_270b6 = 64 - min(G_273a6/8, 64)`.
- `r = max(d, alt) + min(d, alt)/4` (approximate distance).
- If `G_26ec2 == 0` (not invulnerable), `(rand & 511) >= r` and `(rand & 2047) <= 409` (≈20%), the player is hit:
  - effect/sound `154e0(6)`
  - `G_24fd8--` (hit sub-counter). When it reaches <= 0:
    - `G_24fda--` (player damage level, 128 = intact)
    - `G_24fd6 -= rand&3` (fuel? player area)
    - `G_24fd8 = 6 + (rand&7)`

**Ship guns** (`FUN_00014c3e`) run only if the player state `G_24fd4 == 0`. They cover every ship in `G_254aa` except the own carrier (0x25428) that is alive (`+4`) and not sinking (`+12 > 0`). For each gun with `+8 == 0`:
- `14efc(gx)`: if `(rand&511) > |gx - G_24fca|`, set `G_26c9a = -1` (sound). Then, if the player altitude `G_24fc8 <= 200` and `(rand&15) < 6`, spawn a splash `152b0` at `player_x + (rand&63) - 32` and destroy player torpedoes within 10 px of it (`11ae2(x, 10)`). **Ships shoot down incoming torpedoes.**
- Aim with `14db8` as above. y = `ship+14 - ship+26(sink) - G_26da6(wave bob) + gun+6 + 13`.
- frame = `0x81 + v`. With 50% probability (not 6/16) use the `gnf` firing frame.
- Draw, then the same hit roll `14f5c`.
- A destroyed gun smokes (`+10` / `+12` scheme) at y = `ship+14 - ship+26 + 13`.

**Rocket hit on a ship** (`146dc`, the impact surface is sea or carrier; weapon type 0 = rocket):
- Rocket (type 0): the first gun within 16 px with `+8 == 0` gets `+8 = -1`, `+10 = 50`, `+12 = 1`, **score += 200**.
- Rockets (type 1): no effect on ships.
- Torpedo (type 2) in its running state (`obj+30 == 10`): if ship `+12 > 0`, then `+12--`. When it reaches 0, set `+24 = 20` and the ship starts sinking.

## 6. Ships

`G_254aa` = pointer list {destroyer 0x253b0, own carrier 0x25428, battleship 0x253ce, transport 0x253ec, J-carrier 0x2540a, -1}. **[H]**

**Ship record**, 30 bytes:

| off | meaning |
|---|---|
| +0 | x0 (map byte offset) |
| +2 | x1 (map byte offset) |
| +4 | present / alive |
| +6 | ptr to gun array |
| +10 | gun count |
| +12 | torpedo hits left (<=0: sinking; -1: gone) |
| +14 | gun / plane base y |
| +18 | sink bonus (0 = own carrier) |
| +20 | sink stage (= y sink offset in px) |
| +22 | step timer |
| +24 | step reload, decrements |
| +26 | render copy of +20 |
| +28 | shape value (§2) |

Ship lookups:
- `FUN_00014a52(off)` → ship record whose [x0, x1] contains off, else -1.
- `FUN_00015898` and `FUN_0001cbf2` → ship index from a map pointer (carrier-deck cells only).

**Sinking** (`FUN_00011cae` → `FUN_00011cd8`, per logic tick, ships with `+4 && +12 == 0`):
- `+22--`. When it reaches <= 0: `+20++`, `+22 = +24`, and `+24--` while it is nonzero. Steps take 20, 20, 19, 18, … ticks, then one every tick.
- Stage 1, own carrier only: if `G_252e4 == 1`, set `G_24fd4 = 11`, `G_252e4 = 2`, `G_252b4 = 0`, `G_2535e = 0`.
- Stage 10, enemy ships:
  - score += bonus (`+18`)
  - message `15640`: "%s sunk . . . BONUS %ld points". Name from `G_23af8`, chosen by bonus: 4500 Battleship, 6000 carrier, 2500 destroyer, else transport.
  - `G_252c1--`. If it is <= 0 and `G_252d3 == 0` (no enemy islands left): mission complete (`15694`). Otherwise the message is queued.
- Own carrier, stage 33: if the player state `G_24fd4 == 1` (on deck), the player goes down with it (`G_24fd4 = 6`, `G_24fc8 = 0`, …, `G_25512 = 100`).
- Stage 120:
  - Enemy ship: `G_252c0--`, `+12 = -1`, and all map cells x0..x1 are cleared to 0 (sea). The ship disappears.
  - Own carrier: `+4 = 0`, `G_25511 = -1` (game over / carrier lost; mission-flow agent).
- Ship graphics move down by the sink stage. Ships also bob with the waves `G_26da6` (`G_252fe`, from table `G_24b94` cycled every `G_25338` ticks in `11386`).

**Ship plane blocks** (64 bytes; `G_24fe6` destroyer, `G_25026` own carrier (unused, all zero), `G_25066` battleship, `G_250a6` transport, `G_250e6` J-carrier):
- Header: `+0` n planes left, `+2` max airborne, `+4` xa = shipx_px - 200 (J-carrier -250), `+6` xb = shipx_px + 620 (transport +320, J-carrier +20). Here shipx_px = x0*4.
- Then n entries of 8 bytes: `{flag 0x8000 (parked; 1 = rolling), x px (= tbl + shipx_px), y, dir}`.
- Entry tables:

| ship | x | y | dir |
|---|---|---|---|
| destroyer | 194 | 51 | +1 |
| | 525 | 40 | -1 |
| | 484 | 40 | +1 |
| | 234 | 51 | -1 |
| battleship | 233 | 56 | -1 |
| | 507 | 47 | +1 |
| | 746 | 32 | +1 |
| | 194 | 56 | +1 |
| | 546 | 47 | -1 |
| transport | 29 | 62 | +1 |
| | 115 | 69 | -1 |
| | 76 | 69 | +1 |
| J-carrier (all y 16, dir -1) | 604, 571, 538, 505, 472, 439, 459 | 16 | -1 |

- The first n entries are drawn parked on deck with `jp21` / `jp22` (`1391e`, y = entry y - sink stage).
- **Launch** (`FUN_00011510`, per logic tick):
  1. J-carrier take-off roll (only if a plane is rolling, i.e. entry[n-1].flag > 0):
     - `v = G_2729a`; `v += 8 - v/16` (tends to 128); `x -= v/16`.
     - When `x < x0*4`: `n--` and `FUN_0001e4d0(0, x, y, -1)`.
  2. If `G_27298 == 0`, for each block in the order destroyer, own carrier, battleship, transport, J-carrier, check:
     - ship alive, bonus `!= 0` (excludes the own carrier), `+12 > 0`
     - `xa <= player_x <= xb`
     - `G_25126 < max` and `n > 0`

     Then:
     - Destroyer, battleship, transport: `n--`, the plane is spawned **immediately** at entry (x, y) with dir -1, `G_27298 = 100`.
     - J-carrier: the last entry starts rolling (`flag = 1`, `x = shipx_px + 380`, `y = 33`), `G_2729a = 0`, `G_27298 = 100`.

## 7. Enemy aircraft: `G_2517a`, 4 slots × 52 bytes

This is C-compiled code (link a5, mathffp library). Ghidra's decompile of `1d35a`..`1e7d6` is usable; I checked call arguments in the asm. The player struct is at `G_24fc8`; `G_27d3c` points to it:
- word[0] altitude
- [1] x
- [6] state (0 = flying)
- [7] fuel? (`G_24fd6`)
- [8] hit sub-counter
- [9] damage level (`G_24fda`)
- [10] dir
- [11] speed

Other player globals used by the AI: `G_25364` = player speed (same units as `+28`), `G_2535e` = player loop/turn frame (0 = level; 14 = direction flip; up to 25).

### Struct (offsets in bytes) **[H for layout / M for semantics]**

| off | meaning |
|---|---|
| +0 | state: 0 free, 1 (no-op), 2 flying (AI), 4 shot down / falling, 8 (unused), 0x10 burning wreck on an island |
| +2 | AI mode (low bits): 1 chase, 2 attack, 4 carrier bomber, 0x10 escape; bit 3 (8) = "start manoeuvre" request; 9 = chase + manoeuvre |
| +4 | relation to player (`1d3b4`): same dir → 1, or 3 if the plane is ahead of the player (`(px-ex)^pdir < 0`, i.e. in the gun line) and then `+16 ||= 550`; opposite dir → 2 if ex >= px, else 4 |
| +6 | "was hit" flag, set by `1b682` |
| +8 | health, 240 at spawn; < 128 → smoke trail; < 96 → shot down |
| +10 | hit sub-counter (init rand(3)+5, reload rand(4)+6) |
| +12 | queue position among mode-1 / rel-1 chasers (`1d476`, 1 = first) |
| +16 | pursuit timer (550 = 0x226) |
| +18 | firing flag (muzzle flash and gun sound) |
| +20 | dir (-1 / +1) |
| +22 | manoeuvre frame 0..27 (index into attitude tables) |
| +24 | delay before next manoeuvre |
| +26 | manoeuvre repeats |
| +28 | speed |
| +30 | target speed |
| +32 | x px |
| +34 | fall velocity |
| +36 | target altitude |
| +38 | altitude |
| +40 | \|x - player_x\| |
| +44 | muzzle animation counter |
| +46 | cell offset (render) |
| +48 | sprite index (`1d35a`): `+22`, or 26 for a bomber in level flight; +28 when dir != -1 |
| +50 | manoeuvre step delay (3 ticks per frame) |

Globals:
- `G_25126` = Zeros airborne. Bombers and escapers are not counted.
- `G_25128` / `G_2512a[]` = wreck list: x * dir, drawn by `10da6` with frame 27 or 55.
- `G_252cf` = enemy planes destroyed.
- Speed limits: `G_25ea2 = 900`, `G_25ea4 = 2600`.

### Spawn `FUN_0001e4d0(bomber, x, alt, dir)`

- Needs a free slot. A bomber is refused if another plane with mode bit 4 exists.
- Sets `+0 = 2`, `+20 = dir`, `+32 = x`, `+36 = 50`, `+28 = +30 = 900`, `+8 = 240`, `+10 = rand(3)+5`, and clears the other fields.
- Bomber: `+2 = 4`, `+38 = 50`.
- Zero: `G_25126++`, `+2 = 1`, `+38 = alt`.
- Callers:
  - airfields: alt 0
  - ship decks: entry y, or 33 for the J-carrier
  - bomber `FUN_0001bc02`

**Bomber timer** `G_24fe4`: 1350 at mission start, 500 after each bomb drop, at least 750 while `G_26c92 & 0x30` (player input bits).
- It only counts down while the own carrier exists and has torpedo hits left (`G_2542c`, `G_25434`).
- When it reaches 0 and `|32767 - player_x| > 6656`, a bomber spawns 6144 px away:
  - **behind** the player (x - 6144, dir +1) if player_x < carrier start `G_2534c`, or (player over the carrier and 50%)
  - else at x + 6144, dir -1

### Per tick (`FUN_0001e7d6`, slots 0..3)

`1d3b4` relation → `1d476` queue → state handler → `1e64e` speed → (state != 0x10) `1d796` move → `1d35a` sprite.

- **`1e64e` speed** (state 2): clamp target to [900, 2600].
  - If speed < target: `speed += (target - speed)/2 + 5`, capped at 2600.
  - If speed > target: `speed -= (speed - target)/2 - 5`, floored at 900.
- **`1d796` move:**
  - If the player state is 4, 6 or 8 (state & 0x14 clear), target speed = 1700.
  - `x += SPFix( SPFlt((speed/100)*dir) * COS[+22] )`, where COS = FFP table 0x25a5c:
    1.0, .98, .95, .91, .86, .81, .75, .70, .60, .50, .40, .30, .23, .20, 0, .05, .25, .45, .60, .70, .75, .81, .86, .91, .95, .98, 0, .07.
    So the speed unit is 1/100 px per tick.
  - Non-bomber in flight: target altitude is at least 33, and 70 if the player state is 1 (player on carrier).
  - Altitude moves toward the target by `rand(2) + T[min(|d|, 100)/20]`, with T = {1, 2, 2, 3, 4, 5} (`G_26148`).
  - Falling (state & 4): if the target is below, `alt += fallv/100` and `fallv -= 10` (accelerating dive).
  - Then, if `+24 > 0`, decrement it; when it reaches <1, set the manoeuvre bit (+2 |= 8).
  - If bit 8 is set and state == 2: `1d562`.
- **`1d562` manoeuvre** (a half loop or Immelmann turn):
  - Each step: `+16 = 0`; every 3 ticks `+22++`.
  - At frame 14 the direction is reversed.
  - At frame 20 (mode chase/attack, player state 0), if `+26 < 3`: depending on the relation, recompute `+24` (frames until the next manoeuvre; rel 1: `|dx|*100/speed`, rel 4: `|dx|*100/(player speed + speed)`). It may also jump back to frame `26 - frame` and repeat (`+26++`; S-turns to re-engage).
  - At frame >= 26 the manoeuvre ends (+22 = 0, bit 8 cleared).
  - The manoeuvre is cut short (frame = 0) when all of these hold: the player is level and flying, the frame is >= 19, rel is 1 or 3, and mode is 1 or 2.
- **`1e728` (state 2):** smoke chance `(rand&63) < 128 - health`. Then by mode:
  - **Mode 1 chase** (`1d9c6`):
    - rel 1 (behind the player, same dir):
      - If |dx| < 160 and the plane is first in the queue: switch to attack (mode 2).
      - Otherwise trail: target alt = player alt, target speed = player speed - 70*queue.
      - If the player is looping, set the next-manoeuvre delay instead.
      - If |dx| >= 160: target speed = player speed ± 80*queue + |dx|.
    - rel 2: target speed = 900 if the player is turning (frame 1..10), else manoeuvre.
    - rel 3 (ahead of the player, in the gun line): evade.
      - Pursuit timer `+16--`; manoeuvre when it runs out or the player is turning.
      - When hit (`+6`), set `+24 = rand(2)+8` and `+16 = 550`.
      - Otherwise target speed = player speed - |dx|/4 + 70*k (k = order among the evaders) and random altitude `rand(7)*10 + 35`.
      - If |dx| >= 1536: manoeuvre.
    - rel 4: speed 900, target alt = player alt ± 32, `+24 = |dx|*100/(player speed + speed)`, manoeuvre.
  - **Mode 2 attack** (`1dccc`), rel 1 only (otherwise back to mode 1):
    - If the player is level: target speed = player speed ± 50 to hold |dx| at 130..131.
    - If the player turns: mode = 9 (manoeuvre).
    - Target alt = player alt.
    - **Firing:** `+18 = 1` when all hold: player level and in state 0, |alt diff| < 8, frame 0, |dx| < 160, same dir as the player, and the Zero is behind the player.
    - **Damage:** only if `G_26ec2 == 0`, altitude exactly equal, and every 2nd tick (`G_27296`):
      - `player[8]--` (hit sub-counter). When it reaches <1:
        - `player[9] -= 8` (damage, 8× flak)
        - `player[7] -= rand(32)`
        - `player[8] = rand(5) + 6`
  - **Mode 4 bomber** (`1dea4`), attacks the own carrier (carrier x range `G_2534c..G_2534e`):
    - If rel 3: evade as above (`+16 = 0x113` (275); random altitudes).
    - Outside the carrier ±500 px on its approach side: manoeuvre.
    - Within 1000 px before the carrier: target alt 20.
    - When over or past the carrier, altitude == 20 and level, it **drops a bomb** into the 16th weapon slot `G_254e4`:
      - type `G_25506 = 2`
      - x = plane x, y = alt + 15
      - vx = ±speed*655
    - It then turns into an escaper: `+0 = 2`, target speed = 1300, target alt = 60, mode 0x10. `G_24fe4 = 500`.
    - While not over the carrier, `+16` counts down to a manoeuvre.
  - **Mode 0x10 escape** (`1e17a`): despawn when more than 2600 px from the player (`1d18c`, `0xa28`). Otherwise evade with random altitudes `rand(7)*10 + 25`, and on hit `+24 = rand(6)+8`.
- **State 4, falling** (`1e244`): smoke. When altitude reaches the target (-3), look at the map cell under x:
  - Over sea with speed < 300: every 2nd time `target--`, and speed += 24. Speed -= 35 per tick.
  - Speed > 500: impact effect `146c6`. Splash `152ac(alt+3)` every tick.
  - Speed < 100: `G_252cf++`.
    - Over an island: state 0x10, `+30 = 6`, `+28 = 30`.
    - Else: freed (and `G_25126--` for a Zero).
- **State 0x10, wreck burning on an island** (`1e3e8`): sprite 27 or 55. Count `+28` down; each time it runs out, `+30--` and `+28 = +30*5`. Smoke every 4 ticks. When `+30 < 2`: append `x*dir` to the wreck list and free the slot.

### Player shooting Zeros: `FUN_0001b682`, per tick while the gun fires (`G_252ba`)

- A target needs rel == 3 (in front, same dir), |dx| < 160, |dalt| < 20 and `G_25352 == 0`.
- On a target: `+6 = 1`, `+10--`. When `+10` reaches <1:
  - smoke puff
  - `health -= 8`
  - if health < 96: **score += 350**, state 4, target alt -3, frame 0, bit 8 cleared
  - `+10 = rand(4) + 6`

So a kill takes 19 decrements: about 5..7 + 18 × 6..9 ≈ 115..170 ticks on target.

Rendering, for the other agents:
- `10da6` draws wrecks and planes from the frame table `G_26ede[56]`, built in `1d1ea` from name tables `G_25ea8` (dir -1) / `G_25f18`. The 1/8 view uses `G_26fbe` (zpn*).
- Muzzle flash: japplane `fc10/fd10/fc1a/fd1a` (indices 16..19), every other 2 ticks while `+18` is set.
- `14206` draws the planes in the 3D/rear-view panel.
- `12132` sets the engine volume from the nearest |dx|+|dalt|.

## 8. Unresolved / open

- `barf`, `bumb`, `LIVE`, `cama`, `balb/balr/balw`, `tre1-3`, `rock`: no gameplay code found referencing these types. They look decorative, or they are used by object height `FUN_00015710` (not analysed) **[L]**.
- Ship `+28` (248/208/184/0) and the battleship's missing `+22` init.
- Exact semantics of player fields `G_24fd6` / `G_24fda` / `G_24fd8` (fuel? damage?) belong to the player agent. Here they are named from how they are used.
- Enemy state 1 / state 8 handlers are empty (`1e4c8` returns immediately).
- The difference between rel 2 and rel 4 (head-on vs receding) depends on the player dir sign convention, which I did not verify.
- Units: altitude is assumed to be px above sea (`G_24fc8`).
