# Player aircraft (F6F Hellcat) and carrier interaction

Agent: player/carrier. Sources: wings_decomp.c, wings_raw.s, wings.bin. Every address is absolute (A4 = 0x2af4e).
Confidence tags: **[sure]** = read from code and checked against the asm; **[likely]** = strong inference; **[?]** = guess.

---------------------------------------------------------------------------------------------------
## 0. The briefing's frame structure is wrong in one important way

- `FUN_00010228` is the **render-side** frame: it snapshots state, positions the camera and draws. It does no physics.
- **The game logic runs at a fixed rate in `FUN_00011386` (the "logic tick").** The main loop calls `FUN_000114d8`,
  which calls `FUN_00011386` once for each queued joystick sample. **[sure]**
- The VBL server `FUN_00011754` samples the joystick on **every 4th VBL** (`DAT_000272b2` reloads with 4) and pushes one
  input word into the queue `DAT_000272a6[6]` (count `DAT_000272a4`, max 6; when it overflows, the oldest entry is
  dropped by `FUN_00011714`). **The logic therefore runs at 12.5 Hz on PAL (one tick = 80 ms).** Every per-tick constant below
  is per 80 ms. **[sure]**
- Demo record/playback lives in the same VBL code: `DAT_00026c9c` = 1 plays back and 2 records bytes into `DAT_00026c9e`,
  up to index 0x1385. **[sure]**
- `FUN_00010f88` (the "116 globals" function) only copies logic state into render copies inside Disable()/Enable()
  (exec -0x84/-0x8a): 26dac = x, 26db0 = y, 26eca = dir, 26ec8 = turn frame, 26ecc = vspeed, 26da6 = wave bob,
  24e86 = zoom. **[sure]**

Logic tick `FUN_00011386` (skipped while paused, `DAT_000254a6`):
```
if P.state==0 (flying):
    if oil != 0x80 and --oil_timer(272a0, reload 0x50) hits 0: oil--          // a damaged engine leaks
    if --fuel_timer(2729e, reload 270b8=28) hits 0: fuel--
27296 ^= 1                                   // even/odd tick toggle (smoke)
if --252fc < 0: 252fc = 20; i=(i+1)&7; wave_bob(252fe) = {1,2,3,2,1,2,3,2}[i] + 1
input(26c92) = pop_input_queue()
if (26c8e == 0 || --26c8e == 0): carrier_menu_input (FUN_000112b0); carrier_phase_tick (FUN_00011460)
player_update (FUN_0001c660)    <-- all of the flight model
enemy_planes_update (FUN_0001e7d6)   [other agent]
sound_params (FUN_00012132), gun_hits_on_planes (FUN_0001b682), FUN_00012066, render_snapshot2 (FUN_00011274),
oil_smoke (FUN_00011bfc), FUN_00010a72 (projectiles), drop_test (FUN_000119bc), 11622/11510 (AA/ships), 11cae (ship sinking), ...
```

---------------------------------------------------------------------------------------------------
## 1. Input

### 1.1 Joystick read
`FUN_0001520e` reads JOY1DAT (0xdff00c) and builds idx = b0 | b1<<1 | b8>>6 | b9>>6 (bits 0,1,8,9). It then looks idx up in the
16-byte table at 0x255f6:
```
[0,2,10,8, 1,0,0,9, 5,0,0,0, 4,6,0,0]    -> raw bits: 1=up(forward) 2=down(back) 4=left 8=right
```
When `DAT_00025446` is set (toggled with **Ctrl-F**), up and down are swapped (eor 3 when either is set). **[sure]**
Fire button: `FUN_0002046a` reads CIA-A 0xbfe001 bit 7 (active low). **[sure]**

### 1.2 Input word as the logic sees it (`DAT_00026c92`, low byte at 26c93) — built by `FUN_0001ca32` **[sure]**
| bit  | meaning |
|------|---------|
| 0x01 | stick UP (forward) |
| 0x02 | stick DOWN (back) |
| 0x04 | stick RIGHT (note: swapped from raw) |
| 0x08 | stick LEFT |
| 0x10 | fire **held** — still down 10+ VBLs after the press (`FUN_0001c9ca`, VBL counter 26be2) → machine gun |
| 0x20 | fire **tapped** — released less than 10 VBLs after the press → drop ordnance |

Code tests the horizontal direction this way: `stick = (in&8) ? -1 : +1` ("pushing toward the nose" means `stick == P.dir`).

### 1.3 Keyboard (`FUN_0001ccf6`)
- Ctrl-F swaps up/down. Ctrl-S toggles sound (25447). Esc pauses (254a6).
- Cheat mode: type `c o l i n`, which takes 25e68 to 5. Then: i/k change the pitch rate 25e66 by ±50, `f` sets fuel to 0x80,
  `d` sets oil=0x80, state=0 and toggles invulnerability 26ec2, `p` adds a life (252ac++), `q` ends the mission, and so on. **[sure]**
- Carrier menu (phase 1): raw keys 0x4c and 0x4d (cursor up/down) cycle the weapon. 0x44 and 0x43 (Return/Enter) act like fire.

### 1.4 Hook into weapons (`FUN_0001b5b0`, run every tick before the state machine)
- `(in & 0x30) == 0`: gun flag 252ba = 0.
- In state 0 (flying):
  - **tap (0x20)**: if `turn < 6 || turn > 16`, call `FUN_0001107c` → `FUN_000107f2` to drop or launch the selected ordnance.
    The selected type is 252f4 (0..2) and the count is 252bd (-1 means unlimited).
  - **hold (0x10)**: `gun_on(252ba) = (turn==0 && gun_ammo(25e64) > 0)`. Hits on enemy planes are handled in `FUN_0001b682`:
    |dx|<0xa0, |dy|<0x14 and the pitch angle must be exactly 0.
- In state 1 (on deck): fire is the "re-arm" request (§6.5).
- `FUN_0001bc02` (enemy-spawn timer, enemies agent): any fire input raises 24fe4 to at least 0x2ee. Otherwise 24fe4 counts
  down from 0x546. When it reaches 0 and `|0x7fff - x| > 0x1a00`, an enemy plane is spawned at x±0x1800 (`FUN_0001e4d0`).

---------------------------------------------------------------------------------------------------
## 2. Player state

### 2.1 Player struct `P` at 0x24fc8 (pointer `DAT_00027d3c`), all words **[sure unless marked]**
| addr  | off | name | meaning |
|-------|-----|------|---------|
| 24fc8 | +0  | y | altitude, world px, **up is positive**. 0 is roughly the sea surface. Range -4..1100 when flying |
| 24fca | +2  | x | world x in px (1 map cell = 8 px; cell ptr = map + (x/8)*2, see `FUN_0001c982`) |
| 24fcc | +4  | shape_ptr (long) | shape found by name in the normal set (2458e) |
| 24fd0 | +8  | shape_name (long) | 4-char name, e.g. 'hc05' |
| 24fd4 | +12 | state | state machine, see §5 |
| 24fd6 | +14 | fuel | starts at 0xc0; −1 every 28 ticks while flying; flak hits take rand&3. Below 0 → engine dies |
| 24fd8 | +16 | flak_counter | set to rand%4+6. Each flak "hit" decrements it; at 0: oil−1, fuel−=rand&3, reload rand&7+6 (`FUN_00014f5c`) |
| 24fda | +18 | oil (engine health) | starts at 0x80 (perfect). Once below 0x80 it leaks 1 per 80 ticks. Below 0x60 → engine dies |
| 24fdc | +20 | dir | −1 = facing/moving left (−x), +1 = right. Starts at −1 on respawn |
| 24fde | +22 | hspeed | px per tick (unsigned magnitude; x += hspeed*dir) |
| 24fe0 | +24 | vspeed | px per tick, + is up |
| 24fe2 | +26 | ? | cleared on crash. No other user found |
| 24fe4 | +28 | idle_spawn_timer | see §1.4 |

### 2.2 Other player globals
| addr | name | meaning |
|------|------|---------|
| 25364 | airspeed | 0..1400 (0x578). 1000 = cruise; 100 units = 1 px/tick |
| 27d3a | throttle_accel | added to airspeed per tick while thrusting: +1 per tick up to 8. When idle it decays to a minimum of 4 |
| 25352 | pitch_cmd | commanded pitch in **centidegrees**. + is nose up. Range −4500..+3000 (1100-ceiling bounce can mirror it) |
| 259f2 | pitch_smooth | flight-path angle: `+= (target − smooth)/4` each tick |
| 25358 | pitch_bias | extra angle added to the smoothed one; = −pitch_cmd while auto-levelling (0<pitch≤500) |
| 259fa | landing_attitude | 1 while the stick is held UP only (no horizontal) and the plane faces left (dir −1) |
| 25e66 | pitch_rate | 600 (centideg/tick). Cheat i/k adjusts it |
| 2535e | turn_frame | 0 = normal; 1..25 = half-loop/reversal animation index (§4) |
| 259f0 | turn_step_timer | the turn frame advances every 2 ticks |
| 254e2 | attitude_frame_no | 1..10 (hc01..hc0a), 4 on deck, 0 while turning; selects wheel clearance |
| 2535a | gear_target | 5 = gear down, 0 = up |
| 2529a | gear_anim | moves by 1 per render frame toward gear_target (`FUN_000103a6`) |
| 259ec | deck_tail_up | on deck: speed > 600 and stick not UP → frame 'hc05' (tail up) |
| 27d36 | deck_frame_no | 25c50[idx] (33..27, 64) [?] |
| 27d38 | engine_boost | 1 while thrust or dive input (sound) |
| 25378/2537a | engine sound target volume/period. 2537c/2537e current values, slewed in `FUN_00012132` [sound agent] |
| 252ac | lives | 3 at mission start (`FUN_00013562`) |
| 252b2 | last_plane / game_over display flag |
| 259f4, 259f6, 259f8 | crash timers: sink sub-counter, ticks since crash, next explosion tick |
| 25360 | ? | set to 100 every tick, 9 at takeoff, 0 during turns, incremented in VBL. Possibly an engine-sound helper [?] |
| 25300 → 24e86 | zoom | 8 = normal, 1 = zoomed out (1/8 scale) when y > 0xba (186) |
| 252ba | gun_firing |
| 252f4 | weapon type 0..2 (default 1 after re-arm) | 252bd = ordnance count (from table 24b49[type]) |
| 25e64 | gun ammo (0x600 after re-arm) |

---------------------------------------------------------------------------------------------------
## 3. Flight model (state 0 = flying), per tick

Order inside `FUN_0001c660` case 0:
```
if oil < 0x60 || fuel < 0:   state=4; airspeed = hspeed*100; crash_update(); return    // engine dead -> falls
if y < -6:                   state=6 (sinking); reset crash timers; return
controls()        FUN_0001bff4
physics()         FUN_0001bdfa
ground_check()    FUN_0001ba80
deck_crew_signal(): 252af = (y<0x51) ? 2 : 3, then FUN_0001bcce
```

### 3.1 controls() — `FUN_0001bff4` **[sure, from asm]**
```
k = pitch_rate (600);  stick = (in&8)?-1:+1;  landing_attitude=0;  pitch_bias=0
if (in & 0xF) == 0:                                 // no stick input
    if turn: (turn<7 ? turn-- : turn_step(0)); 25360=0
             pitch -= k/4; if pitch < -2250: pitch=-2250
             if 0<pitch<=500: pitch_bias = -pitch
    else if pitch > 0: pitch -= k; if pitch<0: pitch=0; if pitch<=500: pitch_bias=-pitch   // auto-level, climbs only
    throttle_accel--, min 4
    if airspeed > 1000: airspeed -= throttle_accel, min 1000           // drift back to cruise
elif (in & 0xC) == 0:                               // vertical only
    if in&2 (DOWN):  pitch -= 2k, min -4500 (engine boost sound)
    elif in&1 (UP):
        if dir == -1:                               // facing left: landing attitude
            if pitch==0 || pitch<600: pitch += k, max 600  else pitch -= k, min 600
            landing_attitude = 1
        else:                                       // facing right: UP alone lowers the nose
            pitch -= k; if pitch < -600: pitch -= (pitch+600)/2
            landing_attitude = 0
    if turn: (turn<7 ? turn-- : turn_step(0)); 25360=0
else:                                               // horizontal input (+ maybe vertical)
    if dir == stick:                                // push toward the nose = throttle
        if turn: (turn<=6 ? turn-- : turn_step(1))
        throttle_accel++, max 8;  airspeed += throttle_accel, max 1400
    else:
        turn_step(0)                                // push against the nose = start/continue the reversal
    if (in&3)==0:  same "no vertical" pitch handling as above (with turn → -k/4 to -2250)
    elif in&2 (DOWN): pitch -= (turn ? k/2 : k), min -4500
    else (UP):     if airspeed > 1000: pitch += k, max 3000
                   else pitch += (dir>0 ? k/4 : k/8), max 3000
```
Notes: with no input the nose relaxes only from positive pitch. A dive persists until the player pulls up.
UP alone does not climb. Climbing needs UP plus a horizontal push, or UP alone while facing left (which only reaches 6°).
**The asymmetry between left and right is real code. Carrier approaches are always made facing left.**

### 3.2 physics() — `FUN_0001bdfa` (Motorola FFP via mathffp.library) **[sure]**
LVOs used: SPFix −30, SPFlt −36, SPNeg −60, SPAdd −66, SPMul −78, SPDiv −84 (`FUN_00021cc4/21ce2/21cb0/21c9c/21cec/21cd8`).
```
target = (landing_attitude && pitch == 600) ? -800 : pitch
pitch_smooth += (target - pitch_smooth) / 4                       // C '/' truncation, 16-bit
a  = pitch_smooth + pitch_bias;  t = |a|
s  = SIN[t/100]            ; c = SIN[(9000 - t)/100]               // table 0x25ac4 (FFP), see §8
if pitch_smooth < 0 || pitch_bias < 0: s = -s
throttle_accel -= SPFix(s)                                          // effectively 0 (|s|<1 except at 90°)
if dir > 0 && airspeed < 1000: throttle_accel -= throttle_accel/10
hspeed = SPFix( (TURNCOS[turn] * airspeed * c + 50.0) / 100.0 )   // rounded; TURNCOS = 0x25a5c
x     += hspeed * dir
vspeed = SPFix( airspeed * s / 100.0 )                             // truncated
if airspeed < 1000 && state == 0:                                  // STALL
    if !(in & 1): pitch -= k/2, min -4500                          // nose drops unless UP is held
    vspeed -= (1000 - airspeed) / 100
y += vspeed
if y > 1100: y = 1100; pitch = -pitch; vspeed = -(vspeed/2)        // ceiling bounce
elif y < -4: y = -4
```
Integer port: SIN*1.0 can be replaced by a 16.16 table. SPFix truncates toward zero **[likely; check against mathffp]**.
Speed meaning: airspeed 1000 → 10 px/tick → 125 px/s. Max 1400 → 14 px/tick. Climbing or diving does not change airspeed (no energy model).
Airspeed only drops below 1000 after a takeoff (it starts at 0 on deck). It can be below 1000 only until throttle brings it up.

### 3.3 ground_check() — `FUN_0001ba80` **[sure]**
```
cell = map[x/8];  H = obj_height(cell) (FUN_00015710);  clr = wheel_clearance() (FUN_0001aaea)
over_deck = deck_x0 <= x <= deck_x1 && turn==0 && y >= H + clr - 4 && carrier_alive(2542c)
touching  = (y - clr < H) || (y - clr < 1)                          // FUN_0001b8c4
if clr < 0x37 && state==0 && touching:
    if over_deck:
        if dir == -1 && landing_attitude:  state = 1 (LANDED); y = H + clr; gear/sfx (FUN_00012380)
        else: vspeed = -vspeed; pitch = -pitch; y += 6; sfx          // bounce off the deck
    else:                                                            // CRASH
        state = 4; airspeed = hspeed*100
        if cell is not sea and (not carrier or y > 0x13): explosion(cell) + hit ground object FUN_000146c6(cell)
        crash_update()
```
**Landing rule:** you must face left, hold UP with no horizontal input, and touch down over the deck between deck_x0 and deck_x1.
On the touch-down tick y must still be at least H+clr−4, so the plane may sink at most about 4 px into the deck in one tick.
In practice vspeed must be roughly ≥ −4..−5 px/tick, and the steady −8° landing glide (≈ −1.4 px/tick at 1000) meets this. **No airspeed check.**

### 3.4 Wheel clearance `FUN_0001aaea` (height of the plane origin above its wheels) **[sure]**
```
if turn==0 || state==1 || state==0xb:  clr = CLR[attitude_frame_no] (+ GEAR[attitude_frame_no] if gear_target != 0)
elif turn < 6:  clr = TURNCLR[turn];  elif turn > 19: clr = TURNCLR[25-turn];  else clr = 11
CLR    @0x259fc = [2,12,10,6,4,2,5,7,9,12,14,5]
GEAR   @0x25a12 = [5,4,3,3,3,5,3,2,1,0,0,10]
TURNCLR@0x25a50 = [2,2,4,6,10,11]
```

### 3.5 Gear (`FUN_0001b45a`) **[sure]**
- States 1, 7, 0xb: gear_target = gear_anim = 5.
- State 0: gear_target = 5 when `|x − carrier_home| < 1280` (25e52) and the carrier is alive. Otherwise 0.
- The gear is lowered automatically near the carrier. There is no gear control.

---------------------------------------------------------------------------------------------------
## 4. Direction reversal (half loop / Immelmann) — turn_frame 2535e

`turn_step(p)` = `FUN_0001ab80` **[sure]**:
```
if turn_allowed() (FUN_0001aa6e) && --turn_step_timer == 0:
    turn_step_timer = 2                                  // one animation step per 2 ticks
    n = turn + 1
    if n >= 26: turn = 0
    else:
        if n > 19 && p == 0: n = 25 - turn               // with no "push toward new nose", frame 20 jumps back to 6
        turn = n
        if turn == 14: dir = -dir                        // the reversal happens here
```
- `turn_allowed()` is 0 only when P.state==0 and one of the 4 enemy planes (2517a, stride 0x34) has [0]==2, [1]==1, [2]==3
  and [0xb]==13. **[? meaning: some enemy manoeuvre blocks your loop]**
- Pushing against the nose calls turn_step(0) every tick, so frames run 1→13, dir flips at 14, then 14→19.
  After that, keeping the same push (which now points against the new nose) gives frame 6 again, which is a **continuous loop**.
  Pushing toward the new nose calls turn_step(1), which runs 20..25 and then 0 (finish).
  With no horizontal input: frames ≤6 decrement back to 0 (abort), frames ≥7 continue with p=0.
- While turning, hspeed is scaled by TURNCOS[turn] (0.0 at 14). Pitch drifts by −k/4 down to −22.5° (the plane loses height).
  Bombs cannot be dropped for turn frames 6..16. Guns only fire at turn 0.
- Turn frames during a crash (`FUN_0001afba`): frames below 14 unwind by −2 per tick; frames ≥14 run on by +2 to 26 → 0.

---------------------------------------------------------------------------------------------------
## 5. State machine (P.state, `FUN_0001c660`) **[sure]**

The machine is skipped while the carrier menu is up (`252b4 != 0`); then airspeed = throttle_accel = 0.
| state | meaning | per tick |
|------:|---------|----------|
| 0 | flying | §3 |
| 1 | on deck, rolling or taxiing | deck_throttle (`1c4e8`), deck_move (`1bdba`: hspeed=(airspeed+50)/100; x+=hspeed*dir), deck_height_or_takeoff (`1c5f4`), wire_check (`1b92e`), crew signal (`1bcce`) |
| 4 | crashing (hit ground or engine died) | `FUN_0001afba` slide/fall; engine sound 0x19/0x3c0 |
| 6 | sinking in the sea | every 3 ticks y−−; pitch −=250 (min −4500); `1aed8` debris; `1af7c` respawn timer |
| 7 | caught by arrester wire | y = deck; pitch=0; airspeed −= 110/tick → at <0: airspeed 0, state 1; deck_move |
| 8 | burning wreck on land or deck | name 'hcr5' (dir +1) / 'hcrf' (dir −1); y = ground/deck; smoke every 4 ticks (`1cae0(6,y+11)`); `1aed8`; `1af7c` |
| 9 | nothing (frozen) [?] | — |
| 0xb (default) | on the elevator (launch/recover) | y = deck height; when phase 252e4 becomes 0 → state 1 |

At the end of every tick: `gear (1b45a)`, `select_frame (1c378)`, then `zoom = (y > 0xba) ? 1 : 8`.

### 5.1 crash_update `FUN_0001afba` (state 4)
```
clr=wheel_clearance(); cell=map[x/8]; kind = sea?2 : carrier?3 : 1(land)
land:    if y-clr<1 && turn==0: landed (pitch,smooth,attitude=0; y=clr; explosion) else falling
sea:     if y<=clr: landed (pitch,smooth,attitude=0 here too; y=clr; splash FUN_000152ac(x+5))
carrier: h=H+clr; if y<=h: if map cell 5 cells behind (cell - dir*10 bytes) is not sea: landed (pitch,smooth,attitude=0; y=H+clr)
                           else: x -= (airspeed/100*dir + 4); airspeed=0; screen flash FUN_0001cab4(7,0xf00); explosion
turn unwinds ±2 (see §4)
if turn==0 || y > h:
    if landed: x += (airspeed/100)*dir; airspeed -= 85 (→0 below 100); splash or explosion; on land also hit object + FUN_00011a84(8) (kills troops within 8 px)
    else:      pitch -= 600 (min -3100); falling
else: y = H + TURNCLR...; x += (airspeed/100)*dir
if falling: vspeed -= 1 (min -10); y += vspeed; if y-clr<1: y=clr, explosion; x += (airspeed/100)*dir
if airspeed==0 && turn==0 && y<=h:
    state = (not sea && (not carrier || y > 0x13)) ? 8 : 6;  oil=0; P[+26]=0; crash timers=0
```
In short: a crash slides along the ground and decelerates by 85 per tick, then becomes a wreck (8) or sinks (6).
An engine failure in the air gives gravity −1 px/tick² (terminal −10) and the nose goes down.

### 5.2 Death → respawn
- `FUN_0001af7c` (states 6/8): 259f6++ each tick. When it reaches **150 ticks (12 s)**, or is above 30 with fire pressed,
  → `FUN_000135ce`. It also sets 252b2=1 when lives ≤ 1.
- `FUN_000135ce`: lives(252ac)−−; x = carrier_home(252e2); turn=0; dir=−1; clears the 40-entry particle list 26ea8.
  If lives < 1 or carrier HP (25434) < 1: game over (252b2=0xff, mission_over 25312=0xff).
  Otherwise call `FUN_00013684` (re-arm/reset, see §6.5) and wait 20 frames with WaitTOF. (`FUN_000135d8` is the same without lives−−,
  used at mission start.)

---------------------------------------------------------------------------------------------------
## 6. Carrier

### 6.1 Carrier geometry
- Map parser `FUN_00012d5a`: the **first anchor cell of type 0x21 ('rcar', carrier rear)** at map byte offset `o` defines:
  - 25428 = o − 0xa0, 2542a = o + 0x20. These are map byte offsets; world x = offset*4.
  - 2542c = 0xffff (carrier alive), 25434 = 4 (carrier HP; ship struct base 25428, HP at +0xc), 25436 = 0x21 (deck base height 33),
    2543c = sink offset, 2543e = 0x14.
- Deck x range (`FUN_0001b7bc`): **deck_x0 (2534c) = 25428*4 + 16, deck_x1 (2534e) = 2542a*4 − 16** (≈ rcar_x−624 .. rcar_x+112).
- **carrier_home / elevator x (252e2) = (2nd longword of the map file header, 26e44)*4 − 8** (`FUN_00012adc`).
  Struct pointer `DAT_00027d44` = &252e2; +2 = phase (252e4).
- Deck / object height `FUN_00015710(cell)` for carrier cell types 0x1f–0x27 and 0x9f:
  `H = 0x21 − sink(2543c) − wave_bob(252fe: 2..4) − elevator(252e6)`. So the deck top is ≈ 29..31 px. The elevator offset applies to
  every carrier cell.
- Wave bob 252fe: `{1,2,3,2,1,2,3,2}[i]+1`, i advances every 21 ticks (25338=20).

### 6.2 Carrier phases (252e4, counter 252e6) — `FUN_00011460`, `FUN_000112b0`
| phase | meaning |
|-------|---------|
| 1 | plane below deck on the elevator; weapon menu active (252b4=0xff, 252e6=0x20). UP/DOWN (or keys) cycle weapon 252f4; FIRE → state 0xb, phase 2, 252b4=0 |
| 2 | elevator rising: 252e6−− once per new render frame (25318 changed); at 0 → phase 0, engine start (`1b9cc`), sfx |
| 0 | normal play |
| 3 | elevator going down after a landing: 252e6++; at 0x20 → `FUN_00013684` (re-arm) → phase 1 |
`FUN_00011cd8` (ship sinking, enemies/ships agent): if the carrier sinks during phase 1 the launch is forced (state 0xb, phase 2).
If the player is still on the deck (state 1) at sink step 0x21: state 6, y=0, lives=0.

### 6.3 Take-off
State 1 starts on the elevator facing left (dir −1).
- Deck throttle `FUN_0001c4e8` **[sure]**:
  ```
  gun off
  no horizontal input:  airspeed -= 8 (friction/brake), throttle_accel = 0
  push toward the nose: if turn==0: throttle_accel++ (max 8)   else turn--   ;  airspeed += throttle_accel
  push against it:      throttle_accel=0; if airspeed==0: turn++, if turn>6: dir=-dir, turn=5   ;  airspeed -= 8
  deck_tail_up(259ec) = airspeed > 600 && !(in & UP)
  clamp airspeed 0..1400
  ```
  (Turning round on deck works only when stopped: 7 steps, flip, then 5 steps unwinding.)
- `FUN_0001c5f4`: if x < deck_x0 or x > deck_x1 → **state 0 (airborne)**, 252af=2, 252b7=0, 25360=9.
  Otherwise y = H + clr (sitting on the deck).
- A normal takeoff leaves the deck end with airspeed < 1000, so the stall rule (§3.2) applies until throttle brings airspeed to 1000.
  Hold UP to stop the nose dropping.

### 6.4 Landing and arrester wires
1. Approach facing left, UP held (attitude +6°, flight path −8°), over [deck_x0, deck_x1] → state 1 (§3.3). Airspeed is kept.
2. `FUN_0001b92e` each tick in state 1: if **airspeed ≥ 600 and deck_tail_up==0 (UP still held, i.e. hook down)**:
   hook_x = x + 0x18 (dir −1) or x − 0x18 (dir +1). Wires are at **wire_k = home + 0x46 + k*0x38, k=0..3** (home+70, 126, 182, 238).
   If |hook_x − wire_k| ≤ 8: state 7 (arrested), 252af=4, 26c8a = wire_k (x of the caught wire, so the renderer can draw it stretched,
   which matches world cell 'hook' 0x27 [likely]).
3. State 7: airspeed −110/tick → stop → state 1.
4. Below 600 there is no wire catch; the plane only brakes at −8/tick. Rolling off the deck end makes it airborne again (state 0) at low speed.

### 6.5 Refuel / re-arm
`FUN_0001b5b0`: in state 1, phase 0, carrier HP>0, **plane fully on the elevator** (`FUN_0001b4de`), airspeed==0, fire pressed
→ phase 3, state 0xb, y = deck. Elevator goes down, then `FUN_00013684`.

"On the elevator" (`FUN_0001b4de`, state 1 only): plane extents left = x − L[turn], right = x + R[turn]
(dir −1: L=0x25d80, R=0x25d8e; dir +1: swapped). The plane is on it when left ≥ home−0x17 and right ≤ home+0x21. Otherwise 252af = 1
(too far left) or 0 (too far right).
```
0x25d80 = [19,18,17,18,20,20,23]   0x25d8e = [22,21,20,20,22,23,23]   (index = deck turn frame 0..6)
```
`FUN_00013684` (re-arm and new plane): menu delay 26c8e=15, clear projectiles, weapon 252f4=1, ordnance 252bd = 24b49[type],
gun ammo 25e64=0x600, phase 1, 252e6=0x20, menu on, then `FUN_0001b7ec` player reset:
`y=0, hspeed=vspeed=0, state=1, flak_counter=rand%4+6, oil=0x80, fuel=0xc0, pitch=0, airspeed=0, idle_spawn=0x546,
gear=5/5, tail_up=0, fuel interval 270b8=28`. x and dir are **not** reset here; only the respawn path (§5.2) sets x=home, dir=−1.

### 6.6 Deck crew / landing-signal hint 252af (consumed by world cell 0x9f animation in `FUN_00013b1c`) **[likely]**
0 = go right, 1 = go left, 2 = flying low (y<0x51), 3 = idle/high, 4 = "cut"/stop (in braking distance of the elevator, or wire caught),
5 = on the elevator. The braking-distance test is in `FUN_0001bcce`: d=airspeed/4, stop=d*d*2/100, dist=|x−home|−16; signal 4 when
dist<stop and the plane is moving toward home. Before the first takeoff (252b7≠0): 1 if x−deck_x0 < 0x136 and airspeed<400, else 0.
Arm-pose tables are at 0x255ac (render agent).

---------------------------------------------------------------------------------------------------
## 7. Animation frame selection (`FUN_0001c378` → `FUN_0001abde(state, dir, idx)`) **[sure]**

- Pitch bucket: `pidx = (pitch_cmd + 5000)/500` (state ∉ {1,0xb} and turn==0). Otherwise pidx=0 when turning, and 9 by default in
  states 1/0xb (their idx is the turn frame). `idx = turn + pidx`.
- `FUN_0001abde`:
  - state 0/4 (and 6/7 by default), turn==0: name = PITCH[idx] (0x25d30) **mirrored by the engine for dir** (shape flag
    `+8 = dir+1`, flip done by `FUN_00015b58`). attitude_frame_no = 0x25a28[idx].
  - state 0/4, turn≠0: name = (dir==−1 ? LOOP_L[turn] (0x25c60) : LOOP_R[turn] (0x25cc8)). Not mirrored. attitude_frame_no = 0.
  - state 1/0xb: deck_tail_up ? 'hc05' : DECK[turn] (0x25c30), mirrored. attitude_frame_no = 4. 27d36 = 0x25c50[idx].
  - state 8: 'hcr5'/'hcrf' set directly; no lookup.
- Wheels overlay (gear), state 0/7/4 or tail_up, turn==0: name = (dir==−1 ? WHL[pidx] (0x25da2) : WHR[pidx] (0x25df2)).
  The wheel frame index is 25376 = pidx (+10 for dir −1); its shape pointer is 2536a.
- Both the normal set (2458e, ptr → P+4) and the 1/8 zoom set (24592, ptr → 2536e) are looked up by the same name.

```
PITCH  @25d30 idx0..19: hc0a hc0a hc09 hc09 hc08 hc08 hc07 hc07 hc06 hc05 hc05 hc04 hc04 hc03 hc03 hc02 hc02 hc01 hc01 hc01
         (hc0a = steepest dive, hc05 level, hc01 steepest climb; pitch −4500 → idx1, 0 → idx10, +3000 → idx16)
FRAMENO@25a28: 10 10 9 9 8 8 7 7 6 5 5 4 4 3 3 2 2 1 1 1
LOOP_L @25c60 turn0..25: hc0f hc28 hc29 hc2a hc2b hc2c hc2d hc2e hc2f hc30 hc31 hc32 hc32 hc32 hc3b hc3b hc3c hc3d hc3e hc3f hc2d hc2c hc2b hc2a hc29 hc28
LOOP_R @25cc8 turn0..25: hc05 hc22 hc23 hc24 hc25 hc26 hc27 hc37 hc38 hc39 hc3a hc3b hc3b hc3b hc32 hc32 hc33 hc34 hc35 hc36 hc27 hc26 hc25 hc24 hc23 hc22
DECK   @25c30 turn0..7: hc21 hc20 hc1f hc1e hc1d hc1c hc1b hc40       DECKNO @25c50: 33 32 31 30 29 28 27 64
WHL    @25da2 pidx0..19: wh14 wh14 wh13 wh13 wh12 wh12 wh11 wh11 wh10 wh0f wh0f wh0e wh0e wh0d wh0d wh0c wh0c wh0b wh0b wh0b
WHR    @25df2 pidx0..19: wh0a wh0a wh09 wh09 wh08 wh08 wh07 wh07 wh06 wh05 wh05 wh04 wh04 wh03 wh03 wh02 wh02 wh01 wh01 wh01
```
(hc0f at LOOP_L[0] is never used and does not exist in hellcat_shp. hc0b–hc1a are listed in DATA but absent from the gfx too.)

Zoomed-out view (24e86==1): `FUN_000103a6` draws from the 8th-scale table 26dc6[n]:
turn==0: `n = 0x2a + max(-vspeed>>2, -2) + (dir>=0 ? 6 : 0)`.
turn 9..17: `n = turn + (sgn>=0 ? 0x38 : 0x2f)`, where sgn = dir (negated when turn>13).
other turns: `u = turn<=8 ? turn : 26-turn; n = 0x34 + ((u-1)>>2) + (dir>=0 ? 2 : 0)`. **[sure; render agent owns the table]**

---------------------------------------------------------------------------------------------------
## 8. Tables (dumped from wings.bin)

```
SIN @0x25ac4, FFP longs, index = degrees 0..91 (note idx1-4 clamp to sin4°, idx91 = 0):
0.0 .0698 .0698 .0698 .0698 .0872 .1045 .1219 .1392 .1564 .1736 .1908 .2079 .2250 .2419 .2588 .2756 .2924 .3090 .3256
.3420 .3584 .3746 .3907 .4067 .4226 .4384 .4540 .4695 .4848 .5000 .5150 .5299 .5446 .5592 .5736 .5878 .6018 .6157 .6293
.6428 .6561 .6691 .6820 .6947 .7071 .7193 .7314 .7431 .7547 .7660 .7771 .7880 .7986 .8090 .8191 .8290 .8387 .8480 .8572
.8660 .8746 .8830 .8910 .8988 .9063 .9136 .9205 .9272 .9336 .9397 .9455 .9511 .9563 .9613 .9659 .9703 .9744 .9782 .9816
.9848 .9877 .9903 .9926 .9945 .9962 .9976 .9986 .9994 .9998 1.0 0.0
TURNCOS @0x25a5c (FFP, index turn 0..26):
1.0 .98 .95 .91 .86 .81 .75 .70 .60 .50 .40 .30 .23 .20 0.0 .05 .25 .45 .60 .70 .75 .81 .86 .91 .95 .98 0.0
FFP decode: mant = v>>8 (24 bit), sign = bit7, exp = (v&0x7f)-64; value = ±mant/2^24 * 2^exp.  0xC8000046 = 50.0, 0xC8000047 = 100.0
Constants @0x25e52: carrier gear radius 1280; 25e54 = 9; 25e64 = 30000 (initial gun ammo before first re-arm [?]); 25e66 = 600 pitch rate.
Object heights @0x25712 (tre1,tre2,tre3,cama,dugo,huta): 36 35 35 9 13 12 (minus cell y-jitter bits13-11).
```

---------------------------------------------------------------------------------------------------
## 9. Camera (`FUN_00010228`, render side) **[sure for formulas, likely for meaning]**
```
zoom_shift (24e84) = (zoom==1) ? 3 : 0
cam_left (24e80)  = player_x - (160 << zoom_shift)      // plane is kept at screen x = 160
normal:  252f0 = 0x97; if player_y > 0x83: 252f0 = player_y + 0x14;  24e82 = 252f0   // vertical scroll once higher than 131
zoomed:  252f0 = 0x97; 24e82 = 0x4b8
```
(Screen y is probably `24e82 − y`, so the horizon sits at line 151 until the plane climbs above 131. After that the plane stays about
20 px from the top. Above y=186 the view switches to the 1/8-scale view. **[?] — confirm with the rendering agent.**)

---------------------------------------------------------------------------------------------------
## 10. Interfaces with other subsystems
- Weapons: `FUN_0001107c`/`FUN_000107f2` (drop: uses render copies 26db2/26db6 = vspeed/hspeed as 16.16, 26dba x, 26db0 y+0xb,
  25354 = pitch_smooth*1024/18000 (binary angle, 2048 per turn), airspeed). Gun hits are in `FUN_0001b682`. Drop test is in `FUN_000119bc`.
- Damage to the player: flak `FUN_00014f5c` (skipped if invulnerable 26ec2) → flak_counter/oil/fuel. Oil-leak smoke `FUN_00011bfc`.
  Gauges are drawn in `FUN_0001ee16` (oil gauge = oil−0x60, warning <0x74; fuel warning <0x41).
- Ground hit by the crashing plane: `FUN_000146c6(cell)` (destroys huts/bunkers/pillboxes, score 2529c). Explosions `FUN_00010820(cell,h)`,
  splash `FUN_000152ac`, smoke `FUN_0001cae0`, screen flash `FUN_0001cab4(count,colour)` → 25366/25368.
- Enemies read player x/y/airspeed/turn_frame (functions 1d562, 1d9c6, 1dccc, 1dea4).
- Mission flow: lives 252ac, mission_over 25312, game-over display 252b2/25512, carrier HP 25434.
- Sound: 25378/2537a targets and 27d38, slewed in `FUN_00012132`: period = (y>>4) + 2537a + (pitch>>7).

## 11. Open questions
- Exact meaning of state 9 and of 25360 (VBL-incremented, set to 9 at takeoff).
- `FUN_0001aa6e`: which enemy state (obj[0xb]==13) blocks the player's loop.
- Screen-y mapping (§9), and the use of 26c8a (caught-wire x) by the renderer.
- Initial gun ammo before the first re-arm: `FUN_00013684` always sets 0x600, so 25e64's static 30000 is probably overwritten.
