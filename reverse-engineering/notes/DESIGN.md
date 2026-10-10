# Wings of Fury STE: design from the reverse-engineered Amiga game

Synthesis of the four subsystem specs (player.md, enemies.md, weapons_missions.md, render_sound.md).
Named decompile: `../wings_named.c` (272 functions, 241 globals named; regenerate with `../apply_names.sh`).
Confidence tags in the specs: [H] high, [M] medium, [L] low.

## 1. Architecture of the original

| part | where | rate |
|---|---|---|
| VBL server: joystick sample, input queue, ticker scroll, timers | `vbl_server` 0x11754 | 50 Hz |
| **Logic tick**: player, weapons, enemies, ships, collisions, scoring | `logic_tick` 0x11386 | **12.5 Hz fixed** (one queued input word per 4 VBL) |
| Render frame: draws the world, dashboard and 3D forward view, plus some per-frame state (soldier walk, AA rolls, debris, waves, gauges) | `frame_update_and_render` 0x10228 | as fast as it can (50/n Hz), double-buffered |
| Keyboard commands (pause, sound, invert, quit, cheat "colin") | `keyboard_commands` 0x1ccf6 | per loop |
| Sound FX driver (4 ch, 2 request slots each, priorities) | 0x1e8b8.. | level-4 interrupt + VBL |
| Music (`songplay` + `wofsongs`, menus only) | separate LoadSeg'd driver | CIA-B timer |

Logic state is snapshotted for the renderer (`snapshot_logic_state_for_render` 0x10f88) with interrupts off.

## 2. STE architecture (AGT)

- **Logic tick:** keep it at 12.5 Hz (every 4th VBL) and port it as faithfully as possible. All speeds, timers and AI were tuned for 80 ms ticks.
- **Rendering:** target 25 Hz (2 frames per tick). For smoothness, interpolate the camera and sprite positions between ticks; the original only snaps.
- **Per-drawn-frame behaviour:** the soldier walk, AA damage rolls, explosions and waves run once per *drawn* frame on the Amiga, so their speed depends on its frame rate. Give them fixed rates; the Amiga's typical rate needs measuring in an emulator (WinUAE) or from your play memory.
- **Playfield:**
  - The Amiga uses 320×162 in 32 colours. The STE can show more (the prototype uses 320×240), so decide how much extra sky/sea to show.
  - The sky stays a flat colour, the sea is an 11-px animated wave strip, and everything is redrawn per frame. AGT's tile playfield and restore system fits better than full redraws.
- **Colours:**
  - The Amiga's 32 colours = sky/objects (0–31) plus a **waterline split** at line `L = min(162, 151 + max(0, alt-131))`. Below it, colours 2–15 and 24 switch to the ocean palette.
  - On the STE: one 16-colour palette above the waterline plus a Timer-B raster palette change at L. That gives two 16-colour sets, which is close to the original.
  - Night: the night.p / nightocean.p palettes.
- **Camera:** the plane sits at screen x = 160, and the camera follows its altitude above 131. Above altitude 186 the view switches to a **1/8-scale overview** using 8thscale.shp, which needs a second render mode.
- **Dashboard:** 640×37 hires in 16 colours on the Amiga. STE medium res only has 4 colours, so redraw it as **320×37 low-res**, either with its own palette via a raster split or sharing the main palette. It holds the gauges (oil, fuel), the score, weapon/ammo, the enemy-plane warning arrow and the 3D forward view (cockpit perspective of the terrain ahead, dash.shp `3d*`).
- **Message ticker:** a 13-line, 1-plane strip that scrolls 1 px/VBL with a copper colour gradient. On the STE use a small strip with a raster gradient, or a simplified version.
- **Sound:** the 8 raw samples go through STE DMA sound (mono, mixed in software or 1–2 voices); engine pitch = `808 + (airspeed>>7) + alt/16` (Amiga period).
- **Music:** menus only. Convert the `wofsongs` event format (decoded in render_sound.md §7) to a tracker module or a custom player.

## 3. Game rules summary (details in the specs)

- **Flight:**
  - Pitch runs −45°..+30° in 6° steps.
  - Speed is 0..1400 (1000 = cruise = 10 px/tick). Below 1000 the plane stalls and sinks.
  - Pushing against the nose starts a half-loop (frames 1–25, direction flips at frame 14).
  - There is a ceiling bounce at y 1100.
  - The maths uses FFP floats plus a sine table at 0x25ac4 and a loop table at 0x25a5c; port it to fixed point. *(player.md)*
- **Carrier:**
  - Land facing left with Up held.
  - The hook catches one of 4 wires (home+70+k·56) at speed ≥ 600.
  - Stop on the elevator and press fire to rearm, refuel and repair; the weapon resets to bombs.
- **Damage and lives:** oil starts at 128, fuel at 192; the engine dies at oil < 96 or fuel < 0. Damaged engines leak oil. 3 lives, +1 per promotion, respawn after a crash.
- **Weapons:**
  - 15 rockets / 30 bombs / 1 torpedo (selected on the carrier). The machine gun has unlimited ammo.
  - **Rockets** destroy pillboxes and ship guns (confirmed in play).
  - **Bombs** destroy huts and bunkers' occupants.
  - **Torpedoes** sink ships (destroyer/transport 1, battleship 2, Japanese carrier 3); they must enter the water shallowly.
- **Islands:** huts and bunkers hold 5 soldiers each. Bunkers and pillboxes are the AA guns. Soldiers don't shoot. The flag becomes a bare pole when the island is cleared.
- **Enemy planes:** up to 4 at once. Zeros launch from airfields (0x114/0x115 cell pairs) and ships; a periodic bomber attacks the carrier. A Zero takes 19 hits.
- **Scoring:** soldier 25, hut 150, bunker/pillbox/ship gun 200, Zero 350, ships 1000/2500/4500/6000, plus island bonuses.
- **Campaign:**
  - The `0x233af[rank*4+mission]` table gives the map. Missions per rank are 3,3,2,2,1,1,3; after Captain, maps m–o loop.
  - Night (50% chance) only on maps h–o.
  - A mission is won by clearing all islands, sinking all ships and landing back on the carrier.

## 4. Port plan (suggested order)

1. **Core loop:** add the 12.5 Hz tick scheduler to the prototype, plus the camera rule and screen-y mapping.
2. **Player:** port player_update (0x1c660) state machine and flight model to fixed point. Hellcat frame selection tables, left/right mirroring (mirror at asset build time), carrier take-off/landing/wires/elevator.
3. **World objects:** huts, bunkers, pillboxes, flags as dynamic tiles or sprites; soldiers; AA fire.
4. **Weapons:** gun, bombs, rockets, torpedo, impacts and explosions; scoring.
5. **Enemy planes and ships:** AI modes, airfields, ship guns, sinking.
6. **Display:** dashboard and gauges; waterline raster split; night palettes; 1/8 overview; message ticker.
7. **Sound effects;** then music and menus (title, rank select, mission briefing, high scores).

## 5. Open questions (consolidated)

Answered by test flights in the headless vAmiga rig (tools/vamiga, 2026-10-02):
- **Frame rate:** a new frame every 3 VBLs (16.7 fps) in cruise over open sea, steady. Logic is every 4 VBLs, so motion judders in the original.
- **Camera:** the plane stays horizontally centred (±5 px) flying left, flying right and during the turn-around. There is no look-ahead; the camera follows only vertically. Above altitude 186 the 1/8 overview appears (seen in flight).
- **Turning:** never refused, only paused. `no_enemy_on_tail` 0x1aa6e skips the turn step while a chasing Zero in your gun line is at frame 13 of its own loop (max 3 ticks ≈ 0.24 s). This is from the code; not reproduced in flight.
- **Take-off:** you must keep holding Up after leaving the deck until cruise speed (~4-5 s), or the plane stalls into the sea. The loop loses height.

Code-level (to resolve during porting):
- Player state 9, `G_25360`. Gauge A `G_24fda`, dash counter `G_252cf`. Ship field +28, the battleship's sink timer.
- Angle units in the gun ray and rocket homing (doubled or halved?).
- Projectile bounce at y ≤ 30 in airfield zones (runway/hangar?).
- 3D forward-view band tables not dumped yet. CIA TALO tempo for the music.
- Cell types with no gameplay code found: barf, bumb, LIVE, cama, bal*, tre*. Probably decorative or height-only.
