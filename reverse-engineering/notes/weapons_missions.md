# Wings of Fury: weapons, collisions and damage, scoring, mission and campaign flow

Scope: player ordnance (rockets, bombs, torpedo, machine gun), projectile physics, impact resolution against
ground objects, ships and planes, player damage model (oil and fuel), scoring, mission objectives, rank and map
progression, briefing, rank-select, game over, high scores, day/night.

Confidence tags: **[sure]** read directly from the asm. **[likely]** strong inference. **[?]** guess.
Notation: `G_xxxxx` = absolute address of a small-data global (A4 = 0x2af4e). Offsets like `+34` are byte offsets.
Positions are world pixels. x grows to the right. **y grows upward**: sea or ground level is about y = 12.
Map byte offset = (x >> 3) * 2 (one cell = 8 px). Ship and pillbox x fields are stored in "x/4" units, which equal map byte offsets.

## 0. Timing (important for every constant below)

- The **logic tick** `FUN_00011386` runs once per joystick sample. The VBL samples the joystick every 4th VBL
  (`G_272b2` = 4), so the tick is **12.5 Hz on PAL (80 ms)**. Projectile physics (`FUN_00010a72`), gun fire, oil and
  fuel drain, ship sinking and gun-vs-plane all run per tick. **[sure]** (This matches player.md.)
- `FUN_00010228` (the "frame update") runs once per displayed frame. It waits for the VBL flag `G_2550e` in
  `FUN_0001aa3e`, so it runs at most at 50 Hz and is CPU-bound. The following run **per displayed frame, not per tick**:
  soldier animation and soldier scoring (`FUN_00013eee`), AA fire and its damage rolls (`FUN_00013772` → `13d78`/`13de8`/`14c3e`),
  explosion and splash animation counters (`106be`, `152f8`), smoke particles (`10ee0`) and the HUD. **[sure]** The real
  frame rate on an A500 is unknown **[?]**. For the STE port, use 25 Hz for these, or tie them to the tick and re-tune.

## 1. Weapon selection and ammo

| addr | meaning |
|---|---|
| `G_252f4` (word) | selected weapon: **0 = rockets, 1 = bombs, 2 = torpedo** **[sure]** (select screen draws world shape 0x4a+w = rock/bomb/torp; dash icon index w = misl/bomb/torp; projectile frames confirm it) |
| `G_252bd` (byte) | ordnance left for the current weapon. 0xFF = infinite (cheat 'm'), never decremented |
| `0x24b49` (3 bytes) | ammo per weapon: **rockets 15, bombs 30, torpedo 1** **[sure]** |
| `G_25e64` (word) | machine-gun ammo. Set to 1536 in `13684` and **never decremented**, so the gun is unlimited **[sure]** |
| `G_252b4` (byte) | "plane parked below deck, weapon menu active". Set by `13684`, cleared when the player presses fire in the menu |
| `G_252be` | menu key debounce (2 ticks) |

- **Rearm.** `FUN_00013684` (start of sortie) runs after a respawn and after every landing: weapon = 1 (bombs),
  `G_252bd = 0x24b49[weapon]`, oil = 128, fuel = 192 (via `1b7ec`). Landing on the carrier is therefore a full
  rearm, refuel and repair. **[sure]**
- **Menu** `FUN_000112b0`, logic tick, only while `252b4 && !2530c`. Input is joystick bits 1/2 or raw keys 0x4C/0x4D
  (cursor up/down), which cycle the weapon 0..2 with wrap-around. Changing the weapon **reloads** the ammo from
  the table. Fire, or raw keys 0x44/0x43 (Return/Enter), takes off: `252b4 = 0`, player state = 11, `G_252e4 = 2`.
  `FUN_00010344` draws the menu: world shape `selt` (0x4d) and shape 0x4a+weapon at (250,60). **[sure]**
- **Release** `FUN_0001b5b0` (tick, player state 0 only). Input bit 0x20 ("tap") calls `FUN_0001107c` → `FUN_000107f2`,
  unless the plane is in its reversal animation (`G_2535e` in 6..16). Bit 0x10 ("hold") sets `G_252ba` (gun firing) =
  1 if `G_2535e == 0 && G_25e64 > 0`. **[sure]**

## 2. Projectile pool and physics

Pool: **15 slots × 42 bytes at `0x24bfe`**, plus one extra slot at **`0x254e4`** that is used only for the
enemy torpedo-bomber's torpedo (`FUN_0001e244` at 1e08c). The extra slot uses the same struct and update code. **[sure]**

| off | size | meaning |
|---|---|---|
| +0 | long 16.16 | x (px) |
| +4 | long 16.16 | y (px, up) |
| +8,+10,+12 | word | render snapshot of x, y and +32, copied each frame by `FUN_00010f88` (drawing and gun-hit tests use these) |
| +14 | long 16.16 | dx |
| +18 | long 16.16 | dy (for a running torpedo: remaining life in ticks) |
| +22 | long 16.16 | ddx (rocket thrust) |
| +26 | long 16.16 | ddy (rocket thrust). Overwritten with the tick counter `G_25318` on impact |
| +30 | byte | anim frame. Bomb 0..11; rocket 0..19; torpedo: **10 = running in water** |
| +31 | byte | torpedo: facing sign (from `G_24fdd`). After impact: surface that was hit (0 sea, 1 ship deck, 2 island) |
| +32 | byte | state: 0 = free, 0xFF = flying, **8 = exploding** |
| +33 | byte | explosion frame counter 1..7 (0 after) |
| +34 | word | type 0 = rocket, 1 = bomb, 2 = torpedo |
| +36 | word | rocket: ignition delay (ticks) |
| +38 | word | rocket: launch angle = `G_25354 >> 1` |
| +40 | word | rocket: speed = `G_25364` (airspeed) |

### 2.1 Launch `FUN_000107f2` **[sure]**
```
G_26eda = 20                                  // [?] unknown, maybe a sound or flash timer
if ammo(252bd) == 0: return
slot = first slot with +32 == 0 (15 slots), else return
if ammo != 0xFF: ammo--
p.type = weapon; p.dy = G_26db2 (plane vspeed, 16.16); p.dx = G_26db6 (plane hspeed, 16.16), negated if facing left (G_24fdc<0)
p.y = plane_y(G_26db0) + 11;  p.x = G_26dba (plane x 16.16)
p.frame = (dx<0) ? 3 : 9
bomb:     state = 0xFF
torpedo:  p.+31 = low byte of facing; state = 0xFF
rocket:   a = G_25354>>1; p.+38 = a; p.+40 = G_25364
          p.ddy = sin(a)*16>>3 ; p.ddx = cos(a)*16>>3, sign of dx   // sin table 0x248bc: 1024 units/turn, amplitude 32767,
                                                                     // so |thrust| ≈ 1.0 px/tick²
          p.delay = (rnd4 rol 1)&12, or 8 if that is 0                // values 4, 8, 12 (8 twice as likely)
          p.frame = clamp(4 - (G_25354>>5), 0, 9) + (dx<0 ? 10 : 0)
          state = 0xFF
```
Angle units: player.md says `G_25354` is a binary angle with 2048 units per turn. The code feeds `G_25354>>1` to sin/cos,
which use 1024 units per turn, so the rocket thrust direction matches the plane's pitch. **[likely]**

### 2.2 Per-tick update `FUN_00010aa6` (called for each active slot by `FUN_00010a72`) **[sure]**
```
if state == 8: return
if type == 0 (rocket):
    if delay:                                   // drop-away phase
        if --delay == 0: rocket_ignite(p) (FUN_0001099a), then fall through to thrust
        else: x.int -= sign(facing); y.int -= 1; goto MOVE      // falls 1 px/tick, slips back 1 px/tick, still adds dx
    dy += ddy; dx += ddx
  MOVE: x += dx
    if |player_x - x|.int - 640 > 640 (normal view) [or > 640+4480 in the 1/8 map view]: state = 0; return
    ny = (y + dy + ddy).int                      // note: ddy is counted twice in the prediction
else (bomb or torpedo):
    if type==2 && frame==10: goto TORPEDO_RUN
    dx -= (dx.int / 10) << 16                   // drag removes whole pixels only. No drag once |dx| < 10 px/tick
    x += dx
    dy -= G_252a0 (gravity, 0x6000 = 0.375 px/tick²);  ny = (y + dy).int
zone = FUN_00011126(x)                           // airfield record in G_2524a with x in [+0,+2] (see enemies.md)
if zone:
    if ny > 30: y = ny
    elif rocket: state = 0                       // rocket vanishes
    else: y=30; dy = -dy; dy.int >>= 1 (clamped ≤ 9); if dy.int==0 → state=0; dx.int >>= 1; if dx.int==0 → state=0  // bounce
    goto ANIM
y = ny
s = surface(x) (FUN_000150c8: 0 sea, 1 ship/carrier deck, 2 island; off-map → 0)
ground = 12                                      // sea and island
if s == 1: ground = object_height(cell at x) + 11 (FUN_00015714)   // ship decks
// (A test for bunker/hut height on islands is dead code: it compares the surface value with types 3 and 4, so islands always use 12.)
if ny <= ground:
    y = ground; p.+31 = s
    sound: s==0 → splash (FUN_0001233e), else boom (FUN_00012324). Volume = 64 - (|x-px| + |20-py|)>>5
    p.+26 = G_25318
    if type == 2 and s == 0:                     // torpedo enters the water
        if dy.int < -5: goto EXPLODE             // too steep: it explodes on the water
        dx = ±0x45000 (4.27 px/tick, keeps its sign); frame = 10; life(+18) = 200
        splash effect (FUN_000152b0)
      TORPEDO_RUN:
        if --life <= 0: state = 0, +33 = 0; return
        x += dx
        if surface(x) != 0: impact(p) (FUN_000146dc); state = 8; +33 = 1; boom; splash; return
        add a splash at x (FUN_000152b0) every tick           // the visible wake
        return
  EXPLODE:
    impact(p) (FUN_000146dc); state = 8; +33 = 1
    kill_soldiers_near(x, 16) (FUN_00011a8c)                // also detonates torpedoes nearby (see 4.2)
ANIM: if bomb && G_26d8c && (G_25318 & 1): frame = (frame+1) mod 12   // tumbling bomb
```
Notes:
- Bombs and torpedoes are never culled by distance. A bomb is freed when it hits ground or sea. **[sure]**
- A **running torpedo** lives 200 ticks (16 s) and covers about 853 px. It hits anything whose cell has a non-sea surface,
  so it hits ship decks (surface 1, including the player's own carrier) and island cells. **[sure]**
- `FUN_0001099a` rocket_ignite (end of the delay). If the rocket points downward (`(+38>>1) < 0`), it computes the ground
  impact x of the **player's** line of sight for angles a, a+20 and a−20 (`FUN_00011a46`). It then looks between those x values
  for an intact ship gun (`FUN_000111a6`) or, failing that, an intact pillbox (`FUN_0001115c`). If it finds one, it re-aims:
  `ang = -|atan2(|tx - x|, y)|` (`FUN_00015ca6`), `dx = cos(ang)*(speed/100)` (keeping the sign of dx), `dy = sin(ang)*(speed/100)`
  (16.16; 32767 ≈ 0.5 px per unit). Then it sets state = 0xFF. **So rockets fired in a dive home in on guns and pillboxes.** **[sure on the code; the angle-unit mix (>>1 twice) is odd]**

### 2.3 Drawing (`FUN_000106be` / `FUN_00010702`, per frame) **[sure]**
Shape bank `G_26e60` = Torpedo.shp list `0x242f0`; the 1/8 map view uses shape 9 of 8thscale.
Bomb frames are `bom0..bomb` (0x40+frame). Torpedo is `tor2` (0x88), or `tor7` (0x89) if facing left. A running torpedo (frame 10)
**is not drawn** (only its splash wake shows). Rocket frames are `rc01..` (0x4C+frame); during the drop delay they are `ro01..` (0x74+frame).
**Explosion** (+12 == 8): world shapes 0x59+n (n = 1..7: `exp0..exp5`) if it hit land or a deck, or 0x65+n (`spl0..spl6`) if it hit the sea.
+33 advances once per drawn frame, and the slot is freed when +33 reaches 8.
The torpedo slung under the plane (`G_2536e`) is drawn in `103a6` while weapon == 2 and ammo > 0.

## 3. Impact resolution `FUN_000146dc` (a0 = projectile; reads x = +0 and type = +34) **[sure]**

`FUN_000146c6(cellptr)` is the same routine for non-projectiles. It builds a fake projectile at `G_27650` with
x = (cellptr - map)*4 and type 0. Planes crashing on the ground use it (player `1afba`/`1ba80`, enemy `1e244`).
**A crashing plane therefore acts like a rocket hit.**

Screen flash: `G_25366 = 5`, `G_25368 = colour`. `FUN_00010228` writes `G_25368` into the sky colour of the copper list
on the frames where the counter is odd (3 flashes). The colour is 0x0FFF (white) for an impact and 0x0F00 (red) for a kill.

Let `s, t = surface and type of the cell at x`:

**Sea or deck (s = 0 or 1)**. Find the ship whose extent contains `(x>>3)*2` (`FUN_00014a4e`). Only enemy ships whose
presence flag is set are checked (destroyer, battleship, cruiser, J-carrier in that order), then always the player carrier `0x25428`.
- No ship → nothing.
- **type 1 (bomb) → nothing. Bombs cannot hurt ships.**
- type 2 (torpedo): white flash. If it was running (+30 == 10): red flash, and if `ship.hits(+12) > 0` then `--hits`.
  When hits reach 0, `ship.+24 = 20` (start the sinking sequence). A torpedo that is not running falls through to the gun case below.
- type 0 (rocket, crash) or a non-running torpedo: white flash. Walk the ship's gun list (`ship+6` ptr, `ship+10` = count−1,
  14-byte entries). The first intact gun (`+8 == 0`) with `|x - gun.x(+4)| < 16` is destroyed: `+8 = -1`,
  `+10 = 50` (smoke puffs), `+12 = 1`, **score +200**, red flash.

**Island (s = 2)** (type 0 also gives a white flash first):
- t = 0x113 (island marker): nothing.
- **t = 3 bunker (`dugo`)**, any weapon: find the bunker record. If soldiers are inside (`+8 != 0`): `+14 = 200`,
  **score +200**, release all of them (`FUN_00014b40`: `+10 += +8; +8 = 0; +11 = 60`). The bunker graphic is not destroyed.
  A red flash happens only for type 0.
- **t = 4 hut (`huta`)**, any weapon: the 4 cells of the hut are rewritten to type 5 `hutb` (wrecked, anchor bit kept).
  The hut record gets `+12 = 50`, `+14 = 1` (burning smoke via `14e18`). **Score +150.**
- **t = 15..29 pillbox (`pila..piln`), rockets and crashes only (type 0)**: red flash. The cell type becomes
  `15 + (oldmask | bit)` with `bit = 1 << (4 - (((x>>2) - pill.x) >> 1) - 3)`. The 4-bit mask records which quarter was hit and
  selects the damage graphics `pilb..pilp`. If `pill.+8 >= 0` (still alive): `+8 = -1` (dead, stops firing), `+10 = 50`, `+12 = 1`,
  **score +200**, and that island's pillbox count drops by one (`G_253a0[island*4+2]`). If the island now has 0 pillboxes and
  0 soldiers, the **island is cleared** (§6.2).
- Other types: nothing.

**Which weapon does what** (from the code above, consistent with the manual):

| target | rockets | bombs | torpedo | gun |
|---|---|---|---|---|
| soldiers in the open | yes (blast ±16 px) | yes (blast ±16 px) | yes, if it explodes on land | yes (ground ray ±16 px) |
| hut | destroy +150 | destroy +150 | destroy +150 | no |
| bunker with soldiers | flush them out +200 | same | same | no |
| pillbox / AA gun | destroy +200 | **no** | no | no |
| ship deck gun | destroy +200 (±16 px) | **no** | only if dropped directly on the deck | no |
| ship hull | no | no | **running torpedo = 1 hit** | no |
| enemy plane | no | no | no | yes (§4.3) |
| enemy torpedo in water | no | blast window (§4.2) | blast window | yes |

**Ship hits needed** (`+12` set by the map parser `12d5a`): battleship 2, J-carrier 3, destroyer 1, cruiser (transport) 1,
player carrier 4 (enemy torpedoes). Since the player carries only 1 torpedo, a battleship needs 2 sorties and a carrier 3.
**Own running torpedoes also damage the player's carrier.** **[sure]**

### 3.1 Object height `FUN_00015710` (stack arg) / `FUN_00015714` (a0 = cell ptr) **[sure]**
Returns the object top height above the sea for a cell. Table `0x25712` (words) is indexed by group:

| group | types | value |
|---|---|---|
| 0 | 6 tre1 | 36 |
| 1 | 7 tre2 | 35 |
| 2 | 8 tre3, 11 cama | 35 |
| 3 | 3 dugo | 9 |
| 4 | 4 huta | 13 |
| 5 | 15..30 pillboxes | 12 |

Result = table − cell y-jitter (bits 13..11).
Ships return `ship.+14 - ship.+20 - G_252fe` (wave bob). The player carrier also subtracts `G_252e6`.
Ship types: cruiser 204 → `0x253ec`; J-carrier 241/242/243/246 → `0x2540a`; battleship 268-272 → `0x253ce`;
destroyer 228-231 → `0x253b0`; player carrier 31-39 and 159 → `0x25428`. Anything else → 0.

## 4. Machine gun **[sure]**

### 4.1 Ground strafing `FUN_000119bc` (tick)
Conditions: `G_252ba` (fire held), plane descending (`G_26db2 < 0`), plane y < 160, `G_259fa == 0` (not in landing attitude).
```
x_hit = FUN_00011a46(G_25354):   if angle >= 0 → 0 (no hit)
          dist = (G_26dbe >> 8) / tantab[(-angle)&255]     // tantab 0x246bc ≈ 256*tan(i*360/1024); G_26dbe = altitude 16.16
          x_hit = player_x + (facing>=0 ? +dist : -dist)
kill_soldiers_near(x_hit, 16); add impact x_hit to the 20-entry impact list G_26e80 (+0 x, +2 timer, +3 surface)
```
The gun fires one "ray" per tick with no travel time.
Impacts (`FUN_000152b0`): timer 4 on an island, otherwise 6. Drawn per frame by `FUN_000152f8`: on an island, `ric0` (0x6e) at y = 9;
otherwise `spl0+timer` (0x67+t) at y = 13. The same list holds the torpedo wake and the flak splashes.
**Angle units [?]**: `11a46` assumes 1024 units per turn, but `G_25354` is 2048 per turn according to player.md, so the gun
would aim at twice the real dive angle (the impact lands closer under the plane). Verify in game.

### 4.2 `FUN_00011a8c` kill_soldiers_near(d0 = x, d1 = r)
Every soldier in state 1 (walking) with `x-r <= sx <= x+r` gets state 2 (dying), frame 5, timer 2, and plays the scream sample.
It then calls `FUN_00011ae2(x-r, 2r)`, which sets state 8 (explode) on any torpedo in the 15-slot pool or in the enemy torpedo slot
`0x254e4` with `|t.x - (x-r)| <= 2r`. This is an asymmetric window `[x-3r, x+r]` and looks like a bug.
Flak near-misses (`FUN_00014efc`) call `FUN_00011ae2(x, 10)` directly.

### 4.3 Gun vs enemy planes `FUN_0001b682` (tick)
For each enemy plane slot (`0x2517a`, 4 × 52 bytes) with `+4 == 3`:
if `|player_x - plane.x(+32)| < 160` and `|player_y - plane.y(+38)| < 20` and `G_25352 == 0` (pitch command 0? **[?]**)
— **no facing check**:
```
plane.+6 = 1; if --plane.+10 <= 0:
    hit spark (FUN_0001cae0(0, 6, x-16, y+10)); plane.health(+8) -= 8
    if health < 96: score += 350; plane.+0 = 4 (falling); +36 = -3; +22 = 0; clear bit 3 of +3; FUN_0001d35a(plane)
    plane.+10 = rnd(4) + 6
```
Planes spawn with health 240 (enemies.md), so a kill needs 19 damage steps, each needing 6..9 ticks in the cone.
A kill increments `G_252cf` (planes shot down, shown on the HUD) in `FUN_0001e244` **[likely]**.

## 5. Player damage model **[sure]**

Player struct at `0x24fc8` (player.md): +0 y, +2 x, +12 state, **+14 fuel (`G_24fd6`)**, **+16 hit counter (`G_24fd8`)**, **+18 oil (`G_24fda`)**, +20 dir.

- Start of sortie: oil = 128, fuel = 192, hit counter = rnd(4)+6.
- Per tick while flying (state 0, `FUN_00011386`): **fuel −1 every 28 ticks** (`G_270b8`), about 7.2 min.
  **If oil != 128, oil −1 every 80 ticks** (a damaged engine keeps leaking).
- **AA / pillbox / bunker / ship-gun fire** `FUN_00014f5c(gun_x)`, called **per frame per gun**. A gun takes part only when the plane is
  flying, `|gun_x - px| <= 448`, and the aim table `14db8` returns ≥ 0 (|dx| ≤ 512).
  ```
  d = max(dx, alt) + min(dx, alt)/4                      // approximate distance
  G_273a6 = min(G_273a6, dx); G_273a4 = 0xFF              // nearest threat, used by sound?
  if invulnerable(G_26ec2): no damage
  if (rnd&511) >= d and (rnd&2047) <= 409:               // P = (512-d)/512 * 410/2048
      smoke puff at the plane (FUN_000154e0(6))
      if --hitcount <= 0: oil -= 1; fuel -= rnd&3; hitcount = 6 + (rnd&7)
  ```
  So AA alone takes 6..13 hits to cost 1 oil. Bunkers fire only while soldiers are inside; pillboxes and ship guns fire until destroyed.
- **Enemy plane fire** (`FUN_0001dccc`, enemy lane, around 1de2c): needs `plane.y == player.y` exactly, opposite facings, range < 160,
  and an odd tick. Then `--hitcount <= 0` → **oil −8**, fuel −= rnd(32), hitcount = rnd(5)+6.
- **Smoke trail** `FUN_00011bfc` (every other tick). If damaged (`128 - oil != 0`): when damage < 20, emit only where the bit table
  `0x2551a` allows; when damage ≥ 20, always. Calls `FUN_000154e0`, which spawns a smoke particle at the plane (x ± 10 px by
  facing, y + 13, roll-dependent offset from `0x24b40`).
- **Death conditions** (player state machine `FUN_0001c660`, state 0): **oil < 96 or fuel < 0 → state 4 (engine dead, glides down)**.
  Also y <= −7 → state 6 (in the sea). Ground and object collisions are covered in player.md.
  So the oil gauge's "empty" mark is 96: 32 points of damage kill the engine. That is 4 enemy-plane bursts, or about 32 × 6..13 AA hits.
- If the carrier sinks while the plane is on deck, the plane goes to state 6 and lives become 0 (§7).

Smoke particles (`FUN_00015460`): 40 slots × 20 bytes at `*G_26ea8`. Fields: +0 x 16.16, +4 y 16.16 (min 16.0),
+8/+12 velocity 1.0..2.0 px/tick (random, always +x, +y), +16 frame n, +18 = 6. Drawn by `10ee0` as world shape 0x60+n
(n=6 → `smk5` … n=1 → `smk0`). n decreases every 7 frames; the particle dies at 0. Callers pass n=6 (player hit), n=5 (burning hut, pillbox, gun) or n=3.

## 6. Scoring **[sure]**

Score `G_2529c` (long), cleared in `FUN_00013562` (new game). All score sources:

| event | points | where |
|---|---|---|
| soldier killed (death anim finished) | 25 | `13eee` (13f40) |
| hut destroyed | 150 | `146dc` |
| bunker hit with soldiers inside | 200 | `146dc` |
| pillbox destroyed | 200 | `146dc` |
| ship deck gun destroyed | 200 | `146dc` |
| enemy plane shot down by gun | 350 | `1b682` |
| ship sunk (sink stage 10) | ship.+18: battleship 4500, J-carrier 6000, destroyer 2500, cruiser 1000 | `11cd8` |
| island cleared | per-map table below | `13eee`, `146dc` |

**Island bonus** `FUN_00015ae8(island)` = word table `0x233cc[map*4 + island]`:

| map | a | b | c | d | e | f | g | h | i | j | k | l | m | n | o |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| isl0 | 450 | 500 | 1000 | 1500 | 1000 | 900 | 900 | 900 | 1500 | 0 | 1600 | 2400 | 3000 | 2500 | 3000 |
| isl1 | 0 | 700 | 600 | 1100 | 900 | 900 | 1200 | 1600 | 1300 | 0 | 1500 | 0 | 2000 | 3000 | 3000 |
| isl2 | 0 | 0 | 750 | 0 | 1500 | 0 | 1200 | 1000 | 1300 | 0 | 2000 | 2500 | 2200 | 3200 | 3500 |
| isl3 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 2800 | 0 | 0 |

The island index counts island segments left to right. It increments at each type-2 (`bchr`) cell (map parser `130f2`).

**Messages** (scroll line pointer `G_25706`, buffer `G_270ba`, formatted with exec RawDoFmt via `FUN_00015078`):
- Island cleared: `"All enemy forces on island have been destroyed . . . Bonus %ld points . . ."` (0x2394a)
- Ship sunk: `". . . %s sunk . . . BONUS %ld points . . ."` (0x23a28). The name comes from the points value
  (`FUN_00015640`): 4500 "Battleship", 6000 "Carrier", 2500 "Destroyer", otherwise "Cruiser".
- If the event finishes the mission, `FUN_00015694` **appends** its text to the same buffer (it overwrites the last character).
  Otherwise `FUN_0001555a` shows the buffer only if no message is currently scrolling (`G_25706 == 0`). If a message is already
  showing, the new one is dropped.
- `0x23996 "Bonus %ld points..."` and `0x23a53 "How about a nice game of thermonuclear war?"` have no code reference found **[?]**.

**HUD** `FUN_0001ee16` (per frame, dash.shp table `G_26da2`, list 0x24118):
- Score `"%07ld"` (`FUN_0001f26a`): 7 digits at x=512, 14 px apart, y=11, shape `wnum`. The digit is chosen by a y offset from `0x24b4c` = 88 − 8·digit.
- Oil gauge at (208,18): needle `ndl1+` index = `((max(oil-96,0)*2) & ~3)/4`, +6 steps when on deck with `G_27d38`. The needle eases 4 per frame.
  Warning lamp `olon`/`olof` blinks with period 10 when oil < 116.
- Fuel gauge at (431,18): needle = `min(fuel/2, 88) & ~3`. It jitters randomly at 0. The lamp blinks with period 8 when fuel ≤ 64.
- Weapon icon at (16,11): `misl`/`bomb`/`torp`. Ammo shows as 2 rolling digits (`bnum`, x = 42 tens and 66 units). Infinite ammo shows a blank drum (100).
- Lives (`G_252ac`, 0..9) as a rolling digit at x=125.
- Planes shot down `G_252cf` (0..99): two digits at x = 508/522, plus up to 7+7 tally marks (`zero` shape) at x=534, y = 19/25.
- Enemy-plane warning: `ltar`/`rtar` at (320,10) toward any enemy plane whose `(+2 & 7) == 4` (`FUN_0001f21a`).

## 7. Mission objectives, success and failure **[sure]**

Counters (set by the map parser `FUN_00012d5a`):

| addr | meaning |
|---|---|
| `G_252c0` | ships present (briefing "SHIPS:"). Decremented when a wreck is removed |
| `G_252c1` | **ships still to sink** |
| `G_252d4` | islands total (number of `bchr` = type 2 cells) |
| `G_252d2` | islands with forces (briefing "ISLANDS:"). An island has forces if it contains an anchor of type 3 (dugo), 4 (huta) or 15 (pila) |
| `G_252d3` | **islands still to clear** |
| `G_253a0` | per island (4 max): word soldiers, word pillboxes. Each hut and bunker adds 5 soldiers, each `pila` adds 1 pillbox |

At most one ship of each class per map: battleship `0x253ce`, J-carrier `0x2540a`, destroyer `0x253b0`, cruiser `0x253ec`.
Flags `252c7/c8/ca/cb` limit each class to one. The player's carrier record `0x25428` is created from type 0x21 `rcar`.

**Island cleared**: when soldiers == 0 and pillboxes == 0 for that island, checked when a soldier finishes dying or a pillbox
is destroyed. Huts and bunkers do not need to be destroyed, but each one's 5 soldiers must die. Soldiers inside a bunker still count.

**Ship sinking** (`FUN_00011cae` → `FUN_00011cd8`, tick). A ship with `+4 != 0` and `hits(+12) == 0` advances a stage
counter `+20`. The step delay starts at `+24` (20 after the fatal torpedo) and shrinks by 1 each step, so sinking accelerates.
- Stage 10 (enemy ship): score += points, show the sunk message, `--G_252c1`. If that leaves `G_252c1 <= 0` and `G_252d3 == 0`,
  call `mission_complete`.
- Stage 120: the ship's map cells are zeroed, `G_252c0--`, `+12 = -1`.
- **Player carrier** (points 0). At the first step, if `G_252e4 == 1` (plane on the elevator) → player state 11, phase 2.
  At stage 33, if player state == 1 (on deck) → state 6, lives = 0, `G_25512 = 100` (game-over countdown).
  At stage 120 → removed, `G_25511 = 0xFF`. A respawn with carrier hits ≤ 0 is game over (§8).

**Mission complete** `FUN_00015694` is called when both counters reach zero, from whichever event finishes the last one:
```
mission++ (G_25310)
if mission > missions_per_rank[rank] (table 0x25498 = 3,3,2,2,1,1,3):
    mission = 1; rank = min(rank+1, 6); G_252ad = 0xFF (promoted)
    message += ". . . Congratulations! You have completed your mission!! You are instructed to return to carrier for victory ceremony!! . . ."
else
    message += ". . . Good work ! You are ordered to return to carrier to receive your next mission ! . . ."
G_25706 = G_270ba (show it); G_2530c = -1 (mission complete, waiting for landing)
```
While `G_2530c` is set, the weapon menu is suppressed. After the next landing, `13684` sets `252b4`. The main loop sees
`252b4 && 2530c` and loads the next mission (§9). While `252ad` is set, `FUN_0001557c` animates 20 confetti particles
(`0x26eb6`, 18 bytes each; spawned at carrier x − 116, y = 56; moved by `11c5e` until y > 169) as the "victory ceremony",
in the normal-scale view only.

**Promotion bonus**: on the mission change, if `G_252ad` is set, lives++ (`G_252ac`).

There is **no failure condition for missions**. The only loss is the game over (§8).

## 8. Lives, crash and game over **[sure]**

- `G_252ac` = lives (planes). Set to 3 by `13562` at a new game. +1 per promotion; cheat 'p' also adds 1.
- After a crash, `FUN_0001af7c` (per tick in the crash states): if lives ≤ 1, set `G_252b2 = 1` (draw the `gmov` "game over"
  shape at (160,81) via `110c2`). `G_259f6++`. After 150 ticks, or after 30 ticks if fire is pressed, call `FUN_000135ce`:
  `G_273a2 = 20` (blank-screen frames), `lives--`, then `FUN_000135d8`.
- `FUN_000135d8` respawn: plane x = carrier x (`G_252e2`), facing left, clear particles.
  **If lives ≤ 0 or carrier hits ≤ 0 → `G_252b2 = 0xFF`, `G_25312 = 0xFF` (session over), lives = 0.**
  Otherwise `FUN_00013684` starts a new sortie on the elevator. The screen stays blank for 20 frames.
- `FUN_000110c2`: while `G_252b2`, draw `gmov`. If `G_25512` is set (carrier lost with the player on deck), count it down
  once per frame and set `G_25312` at 0.

## 9. Main loop and campaign flow (`FUN_00010006`) **[sure]**

```
init; title screens FUN_00018022 (broderbund, wingstitle, creditscreen; wofsongs music)
NEW_GAME:
  cleanup 11234; clear 25447,25510,26c9c,26c94,254f0,25504
  13562 new_game_init (score 0, lives 3, gravity 0x6000, ...); 252b2=0; 25312=0; 25511=0; 252cf=0
  18262 rank_select_screen → rank, mission=1, returns map name 0x235a0[rank]
  1653c load dash (day/night by G_252e0); if not loaded from savegame: 12adc load+parse map
  repeat if 18590 mission_briefing returns 1 (Ctrl+R) → back to NEW_GAME
  1edaa, 18806 (palettes for G_252e0), 13252 (ship shapes), 1535a, 13368 (sounds)
MISSION:
  135a8 new_mission_init (252ad=0, enemy planes cleared, unpause, respawn 135d8); 13684 start sortie
  254a6=0; 26c8c=0; 26c92=0
  FRAME: 1ccf6 keyboard
    if 25312: game over → 1852a (finish demo), if 26ed0 quit program;
              else if not demo playback (26edc==0): 19856 high_score_screen; goto NEW_GAME
    if 254a6 (pause): wait VBL, loop
    if 252b4 && 2530c:                       // landed after mission complete
        2530c=0; 252b4=0; if 252ad: lives++
        111fc choose_day_night; 12adc load map (index = sum(0x25498[0..rank-1]) + mission - 1 → 0x2545c); 18590 briefing (Ctrl+R → NEW_GAME)
        1653c, 18806, 13252, 1535a, 13368; goto MISSION
    10228 frame update; 114d8 run logic ticks
    if 25510 (Ctrl+R in game): goto NEW_GAME
    if (demo playback && input) or 25312: game over path
```
**Map sequence.** Map index = `0x233af[rank*4 + mission]` (mission is 1-based). Map names come from `0x2545c[index]`
(`maps/a.map`..`o.map`). The loader `12adc` computes the same index as `sum(missions_per_rank[0..rank-1]) + mission - 1`.

| rank | name (`0x25860`) | missions | maps |
|---|---|---|---|
| 0 | Midshipman | 3 | a b c |
| 1 | Ensign | 3 | d e f |
| 2 | Lt. Jr. Gr. | 2 | g h |
| 3 | Lieutenant | 2 | i j |
| 4 | Lt.Commd | 1 | k |
| 5 | Commander | 1 | l |
| 6 | Captain | 3 | m n o |

The rank-select screen offers ranks 0..6 plus option 7 (load a saved game). It starts at the first map of the chosen rank
(`0x235a0`: a d g i k l m). After Captain's 3rd mission (map o), the rank stays 6 and the mission resets to 1, so the
game **loops m → n → o forever**. Each loop prints the "Congratulations" text again and gives +1 life. **[sure]**

**Briefing** `FUN_00018590`: background `rank` (from rank.iff), rank name at (296,61). The `%d` values are drawn at x = 340:
MISSION = `G_25310` (y=73), ISLANDS = `G_252d2` (y=119), SHIPS = `G_252c0` (y=131). It shows for 239 frames or until the
demo is aborted. Ctrl+R returns 1 (restart).

**Day/night** `FUN_000111fc` runs **only when advancing to the next mission**. If the next map index > 6 (maps h..o), then
`G_252e0 = random bit` (50 % night); otherwise 0 (day). `G_252e0` selects these pairs:
`wingspalette`/`night.p` (0x25840), `iff-dash`/`nightdash` (0x25848), `ocean.palette`/`nightocean.p` (0x25850),
`dash.shp`/`nightdash.shp` (0x25858). It changes nothing else in the game logic.
Quirk: a new game from rank select does not reset `G_252e0`. The first mission therefore inherits the last value, which is day
on the first game after boot. **[sure]**

## 10. High scores, save/load, keys

- High scores: file `highscore`, 360 bytes = 10 × 36-byte entries {long score, word rank, char name[30]}, held at `G_27d2a`.
  `19472`: if score > entry[9], the player types a name (`FUN_00016086` text input, "Your name is to be entered / in the hall of fame."),
  it goes into slot 9, the table is bubble-sorted (`19320`) and saved (`19288`).
  The table is drawn by `1967e` with formats `"%d"`, `"%-6ld"`, `"%-12s"`, with rank names, in 3 passes (shadow).
- Save/load game: `FUN_00018b96(mode)` (0 = load, 1 = save). Dialog "Game"/"Exit Game"/"Cancel", 6 named slots,
  "Loading game..."/"Saving game...". Save writes the game state blocks (`15e8a`), load reads them (`15e1a`).
  Opened in game with **Ctrl+G** (save, only in player state 1) and **Ctrl+L** (load), or from rank-select option 7.
- Keys (`FUN_0001ccf6`, raw key plus qualifier). Ctrl+R: abort to rank select. Ctrl+S: sound toggle (`25447`).
  Ctrl+F: toggle `25446`. Esc: pause (`254a6`).
  Cheat: type **c o l i n** (`G_25e68` reaches 5). Then: m = infinite ammo toggle, r = clear projectiles, c = cycle weapon,
  f = fuel 128, d = oil 128 + state 0 + toggle invulnerability `G_26ec2`, p = lives+1, 8/2/4/6 = gravity ±0x1000/±0x100,
  i/k = pitch rate ±50, q = quit, space = memory info, '_' = "Island has %d soldiers and %d pillboxes." for the current island.
- Demo: `G_26c9c` 1 = playback (file `wofdemo`, one input byte per tick), 2 = recording (command-line argument). `G_26edc` skips the high-score screen after a demo.

## 11. Main-loop exit flags (summary)

| flag | set by | effect |
|---|---|---|
| `G_25312` | 135d8 (no lives or carrier sunk), 110c2 countdown, Ctrl+R, demo end, cheat q | ends the session → high scores → rank select |
| `G_25510` | Ctrl+R | jump straight back to NEW_GAME (no high score) |
| `G_254a6` | Esc | pause |
| `G_252b4` | 13684 (plane parked below deck) | weapon menu, and the mission-advance check |
| `G_2530c` | 15694 | mission complete, waiting to land |
| `G_26c9c` | rank select / demo | demo mode |
| `G_26ed0` | cheat q / Exit Game | quit the program after the session ends |

## 12. Interfaces to other subsystems

- From the player: `G_26dac`/`G_26dba` x, `G_26db0` y, `G_26db2`/`G_26db6` vspeed/hspeed (16.16), `G_24fdc` facing,
  `G_25354` angle, `G_25364` airspeed, `G_2535e` reversal frame, player state `G_24fd4`, input word `G_26c92` (0x10 gun, 0x20 release).
- Enemy lane: soldier list `G_25450` (count `G_25314`, 8 bytes: x, dir, frame, timer, island, state 0..3), huts `G_25448`
  (count `252d7`), bunkers `G_2544c` (`252d6`), pillboxes `G_25454` (`252d5`; 14 bytes: +0 x/4, +6 island, +8 dead,
  +10/+12 smoke), ship records (30 bytes: +0/+2 extent, +4 present, +6 gun list, +10 gun count−1, +12 hits, +14 height,
  +18 points, +20 sink stage, +22 step timer, +24 step delay), enemy planes `0x2517a`.
- Rendering: shapes via `FUN_00015174` (world coordinates relative to `G_24e80`/`G_24e82`; the 1/8 view when `G_24e84`=3).
  The dashboard forward view (`FUN_0001417e` → `14206`/`14430`, dash `3d*`/`dug*`/`hut*`/`pil*`/`3dc*` frames) is a **cockpit
  perspective view of the terrain ahead**, not a torpedo-run mode **[likely]**. It is left to rendering.
- Sound: `12324` boom, `1233e` splash, `123ac` scream, `12354` metal clang, `12380` screech.

## Open questions
1. The angle-unit mix in the gun ray (`G_25354` used directly) and in rocket homing (`>>1` twice). Is the effective angle really doubled or halved?
2. The real displayed frame rate. It decides how fast AA damage, soldier death and explosion animations run.
3. The meaning of `G_26eda` (=20 on fire) and of `G_25352 == 0` as a requirement for gun-vs-plane hits.
4. Why projectiles bounce at y ≤ 30 inside airfield zones. It may be a runway or hangar roof; check against enemies.md.
5. Unused strings 0x23996 and 0x23a53.
