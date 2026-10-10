# Wings of Fury: front end (everything outside the in-level gameplay)

Sources: `scratch/ann.s` (preferred), `wings_named.c`, `wings.bin` (img[addr-0x10000]), game files in `shapes/`.
Marks: **[H]** read from code/bytes, **[M]** inferred, **[?]** open.
"Frame" = one `WaitTOF` (graphics -270, thunk `22eee`) = 1/50 s PAL. Colours are 12-bit Amiga RGB (`RGB` hex).
Related notes: `weapons_missions.md` §7-§11 (mission logic, main loop), `render_sound.md` §3.7 (font, ticker), §7 (music),
`enemies.md` §1 (per-mission tables).

## 0. Shared helpers [H]

| addr | name | behaviour |
|---|---|---|
| `2044c` | fire() | 1 if joystick fire (CIA `bfe001` bit 7 low) **or left mouse button** (bit 6 low, read via mirror `bfe0ff`) |
| `20454` | stick() | 0 = centre, 1 = up, 2 = up-right, 3 = right, 4 = down-right, 5 = down, 6, 7 = left, 8 (table `0x204b0` = `00 05 04 03 01 00 00 02 08 00 00 00 07 06 00 00`, index from JOY1DAT) [H table, M compass naming] |
| `207d8` / `207e4` | key_pending() / get_key() | key queue; get_key returns `qualifier<<16 | rawkey` |
| `20700` | to_ascii(raw) | RawKeyConvert; Ctrl = qualifier bit 3 |
| `16eee` | wait(n) | `WaitTOF; for (i=1;i<n;i++){ if fire() break; WaitTOF; } return fire();` → up to n frames, ends early on fire |
| `17422` | load_pic(name, pal_out) | load ILBM into the **back** view, copy its 32 palette words to `pal_out`, set the view palette to black |
| `16fc4` | flip_wait(view) | show view, wait 1 VBL |
| `17084` | fade_to(pal, 1) | 16 steps s=0..15; each colour component `cur + (target-cur)*s/15` from the palette at entry (s=15 → exact target); rebuild copper + show after each step. **No VBL wait inside** → speed is CPU-bound [H]; about 1 frame/step on an A500 [?] |
| `173b0` | fade_out(1) | `fade_to(all 0)` |
| `171f2` / `173e6` | fade_to2 / fade_out2 | same for a view with two viewports (both palettes) |
| `1a9ca` | copy_view(front, back) | copy bitmaps + palettes |
| `123dc` | play_song("wofsongs", n) | if a song runs: FadeSong(2), wait until silent; then start song n. `songs[5] = {song1, song2, song3, song2, song4}` |
| `12470` | stop_song() | FadeSong(2), wait, unload |
| `18570` | text(str) | draw with `newarmyfont` (12 px high, proportional) at the rastport cursor = **top-left** of the glyph box, via BltTemplate with the rastport pens/drawmode |
| `18194` | menu_input(timeout_flag) | see §2 |
| `18228` | debounce() | see §2 |

Every view set-up (`16a60/16a98/16ad8/16b04/169a4/16d7a`) re-runs InitRastPort → FgPen = 0xFF (= highest colour of the view),
BgPen 0, JAM2, until changed [H 167f2/168b8].

Screen modes used:

| setup | mode | used by |
|---|---|---|
| `16a60` | hires 640x200, 1 plane, bitmap 230 rows (`DAT_2773a = 0xe6`) | intro scroller |
| `16ad8` | lores 320x200, 5 planes (32 colours) | broderbund, title, credits, rank select |
| `16b04` | hires 640x147, 3 planes (8 colours) | mission briefing |
| `169a4` | lores 320x200, 4 planes (16 colours) | name entry, save/load dialog |
| `16d7a` | top viewport lores 320x75 5 planes + bottom viewport hires 640x145 4 planes at y offset 76 | high score table |

## 1. Start-up `FUN_18022` (runs once per program start) [H]

```
main 10006: LED/filter bit set; init; if argc > 1: G_26ed6 = "wofdemo" (demo RECORD mode); FUN_18022(); goto NEW_GAME (§4)

FUN_18022:
  play_song(2)                         // song3
  intro_scroller()                     // FUN_17e80, §1.1
  play_song(1)                         // fades song3 out, waits, starts song2; keeps playing until rank select
  set lores 320x200x5 (16ad8), black
  P = load_pic("shapes/broderbund")    // back view, palette black
  flip_wait(back)
  fade_to(PAL_A @0x2589c)              // logo only: colours 9..15 stay black
  if wait(60) goto END
  fade_to(P)                           // greys 9..15 appear (cross-fade to the file palette)
  P = load_pic("shapes/wingstitle")    // into the hidden view
  if wait(120) goto END
  fade_out; flip_wait(back); fade_to(P)          // title
  P = load_pic("shapes/creditscreen")
  if wait(300) goto END
  fade_out; flip_wait(back); fade_to(P)          // credits
  wait(600)
END:
  fade_out
```
- Skip: **fire only** (joystick button or left mouse button). Keys do nothing here. Fire during any wait jumps to END
  (one fade-out, then rank select). The intro scroller is skipped separately (fire ends the scroller, then the pictures start).
- No text is drawn on the three pictures.
- Durations (frames, plus fades): broderbund 60 with PAL_A + 120 with file palette, title 300, credits 600.
- Quirk [M]: fire still held when rank select opens selects the highlighted rank at once (fire is polled right after its fade-in).

Pictures (all plain IFF ILBM, not Rpck; none has a CAMG chunk):

| file | size | planes / CMAP | colours used | mode |
|---|---|---|---|---|
| `shapes/broderbund` | 320x200 | 4 / 16 | 14 | lores |
| `shapes/wingstitle` | 320x200 | 5 / 32 | 31 | lores |
| `shapes/creditscreen` | 320x200 | 5 / 32 | 26 | lores |

```
broderbund CMAP : 000 ECA 730 026 038 02B 03D 07E 05F 555 666 777 888 999 AAA CCC
PAL_A 0x2589c   : 000 ECA 730 026 038 02B 03D 07E 05F 000 000 000 000 000 000 000
                  1FB 6FE 6CE 00F 61F 06D 61F C1F F1F FAC DB9 C80 A87 CCC 999 666   (16..31 unused by the picture)
wingstitle CMAP : 000 00B 400 500 600 700 800 900 B00 333 444 555 666 777 999 BBB
                  221 320 420 531 640 750 960 B70 D90 FB0 FC5 FD4 FD7 FE9 DDB EEE
creditscreen    : 000 00F 00E 00D 00C 00B 00A 009 008 007 006 005 004 0CE 0FF 09B
                  08A 068 046 000 000 000 000 000 F80 E70 D60 C50 B40 A30 920 820
```

### 1.1 Intro text scroller `FUN_17e80` [H]

Hires 640x200, 1 bitplane, colour 0 black, text colour 1 through a copper gradient. Font `newarmyfont`, x = 0.
The bitmap is a **ring of 210 rows**: the display starts at row `c`, and a copper move reloads BPL1PT to row 0 at display
line `210-c`. Text scrolls up 1 px per step; one step = `wait(2)` twice = **4 frames** (12.5 px/s).

```
c = 0; lines = 0; ptr = *(0x258dc) = 0x17494
loop:
  if c % 14 == 0:
      y = ring row (c + 196) % 210          // code: 196 if c == 0 else -14 relative to the moved plane pointer
      clear rows y..y+11 (pen 0)
      if lines < 53:
          str = ptr; ptr += strlen(str) + 1
          width = (next string is empty) ? 0 : 615      // 0x267: full justification unless last line of a paragraph
          draw_text_justified(str, x=0, y, width); left = 210
      lines++
  wait(2); build copper(16, 210-c); show; wait(2)
  left--; c++; if c == 210: c = 0
  if left < 0 or fire(): break
for n = 16 down to 1: build copper(n, 210-c); show; wait(2)      // fade out, 2 frames per step
```
- Line pitch 14 px, glyph height 12. 53 strings (blank strings give blank lines). Total about 939 steps = 75 s if not skipped.
- Copper gradient `FUN_17d4e(n, wrap)`: display line L = 0..n-1 sets COLOR01 = `L * 0x111`; the last value stays for the middle;
  display lines 181..196 set COLOR01 = `(196-L) * 0x111` (only i < n entries; black below). With n = 16 the text is white (FFF) in the
  middle, fades in over the bottom 16 lines and out over the top 16. New lines are drawn at display line 196 (black) and rise.
  Copper waits are at `L+5` [H]; the mapping of copper line to display line is [M].
- Justification `FUN_15956` [H]: advance per character = glyph width + 1 (width-0 glyphs, i.e. space, advance 10 + 1).
  If `width > natural`: extra = width - natural; every character gets `extra / (len-1)` more, the first `extra % (len-1)` get 1 more.

Strings (address, text; quoted exactly, 0x17494..0x17cfb):
```
 0 0x17494 "                 A Time of Fury"
 1 0x174b4 ""
 2 0x174b5 ""
 3 0x174b6 "    It  is 1944 and the world is at war.  Europe"
 4 0x174e7 "is  ablaze with a conflict that engulfs her like"
 5 0x17518 "the   flames   of   hell,   leaving  a  path  of"
 6 0x17549 "destruction  wherever  it  burns.  The Far East,"
 7 0x1757a "too, is being consumed by a furious struggle for"
 8 0x175ab "dominance.   In  the Pacific theater, the allies"
 9 0x175dc "face  an  enemy  possessed of  great skill and a"
10 0x1760d "relentless determination.  As the tide begins to"
11 0x1763e "turn in favor of the allies, the enemy struggles"
12 0x1766f "ever  more desperately to maintain the footholds"
13 0x176a0 "it had gained earlier in the war."
14 0x176c2 ""
15 0x176c3 "    However, both on the sea and in the air, the"
16 0x176f4 "U.S.   Navy  proves  to be more than a match for"
17 0x17725 "it's  opponents.   One  reason  for  this is the"
18 0x17756 "incredible  striking  power  of  the  Navy's Air"
19 0x17787 "Force.   It  is  instrumental  in  defeating the"
20 0x177b8 "enemy in battle after battle.  Within the Navy's"
21 0x177e9 "air  command,  one plane seems to be leading the"
22 0x1781a "fight  for  an  allied  victory:  the mighty F6F"
23 0x1784b "Hellcat!"
24 0x17854 ""
25 0x17855 ""
26 0x17856 "     The  Hellcat  is  incredibly  powerful  and"
27 0x17887 "durable,  a  real  work horse capable of bearing"
28 0x178b8 "bombs,   rockets   and   torpedoes.    Able   to"
29 0x178e9 "outmaneuver the enemy's best fighter planes, the"
30 0x1791a "Hellcat   has   established   one  of  the  best"
31 0x1794b "kill-to-loss ratios in the war."
32 0x1796b ""
33 0x1796c "    Now  you  have  the  opportunity to fly your"
34 0x1799d "very own Hellcat.  You'll be assigned to provide"
35 0x179ce "air  support  for  the  USS Wasp.  This aircraft"
36 0x179ff "carrier  has  been heavily damaged and must make"
37 0x17a30 "its   way safely back to port.  On this perilous"
38 0x17a61 "journey,  you  must  defend  the carrier against"
39 0x17a92 "torpedo  bombers,  rout  the  enemy  from  their"
40 0x17ac3 "island  strongholds, sink enemy vessels that lie"
41 0x17af4 "en  route  to  home port and protect yourself by"
42 0x17b25 "shooting down enemy planes."
43 0x17b41 ""
44 0x17b42 "    Strapping  yourself  into  the  cockpit, you"
45 0x17b73 "face  a  tremendous responsibility.  The fate of"
46 0x17ba4 "the  carrier  and  every  man  onboard  has been"
47 0x17bd5 "placed in your experienced hands.  As the signal"
48 0x17c06 "officer gives you the go, you give your Cat full"
49 0x17c37 "throttle  and  take  off  into the unknown skies"
50 0x17c68 "before  you.   Just  minutes  off  the deck, you"
51 0x17c99 "sight  the  first  sign  of  trouble:  a pair of"
52 0x17cca "enemy fighters bearing down on you from above..."
```

## 2. Rank select `FUN_18262` [H]

Assets:

| file | size | planes / colours | mode | use |
|---|---|---|---|---|
| `shapes/selectrank` | 320x200 | 5 / 32 (26 used) | lores | background with all 8 menu lines already drawn |
| `shapes/selectrank.shp` | PPkc bank, 8 frames `rnk0..rnk7`, each 192x9 | | lores | highlight bars, XOR-blitted |

```
selectrank CMAP: 000 ECA 730 840 950 A60 C72 D83 D95 EA5 EB7 FD8 FE9 000 000 03C
                 06E 08F 000 000 333 444 555 666 777 888 999 AAA CCC DDD EEE FFF
```
Layout: metal frame, "Wings of Fury" emblem, "SELECT RANK" (blue), then 8 text lines, 10 px apart. Frame `rnkN` is blitted at
its own header position `(src_x, src_y)` = **(64, 91 + 10*N)**, size 192x9, with `FUN_20e0a` = XOR blit (minterm 0x6A per plane map).

| N | picture text | text colours | bar colours (rnkN) |
|---|---|---|---|
| 0 | MIDSHIPMAN | 9, 11 (orange) | 15, 16, 17 (blue) |
| 1 | ENSIGN | 9, 11 | 15, 16, 17 |
| 2 | LT. JUNIOR GRADE | 9, 11 | 15, 16, 17 |
| 3 | LIEUTENANT | 9, 11 | 15, 16, 17 |
| 4 | LT. COMMANDER | 9, 11 | 15, 16, 17 |
| 5 | COMMANDER | 9, 11 | 15, 16, 17 |
| 6 | CAPTAIN | 9, 11 | 15, 16, 17 |
| 7 | RETURN FROM R&R (= load saved game) | 15, 16, 17 (blue) | 7, 8, 9, 11 (orange) |

The bar pixels are non-zero only where the picture is 0 (checked for all 8 frames), so XOR = paint a filled bar behind the text,
and a second XOR restores the picture. On the STE: keep the 192x9 background strip and blit the bar as an opaque pre-merged strip. [H]

```
sel = G_26bb4 = 0                         // always starts on MIDSHIPMAN
play_song(4)                              // song4; fades out whatever was playing
lores 320x200x5 black; G_26c90 = 0 (loaded-from-save flag)
P = load_pic("shapes/selectrank"); bank = load "shapes/selectrank.shp"
xor rnk[sel]; flip_wait; fade_to(P); copy_view(front -> back)
LOOP:
  r = menu_input(1)
  if r == 1000: G_26c9c = 1 (demo playback); goto DONE        // 36 s without input
  if r == 0: goto DONE
  sel = (sel + r) wrapped to 0..7
  if sel changed: xor rnk[old]; xor rnk[sel]; flip_wait; copy_view; debounce()
  goto LOOP
DONE:
  if sel == 7:
      if load_save_dialog(0) == 0: G_26c90 = 1; free bank; fade_out; goto END   // rank/mission come from the save
      else: redraw the menu view; goto LOOP                                      // cancelled
  free bank; fade_out
  if G_26c9c == 0 and G_26ed6 != 0: G_26c9e = alloc(5000); G_26c9c = 2          // record
  if G_26c9c == 1: G_26c9e = load file "wofdemo"
  G_26ca2 = 0; if G_26c9e == 0: G_26c9c = 0
  if G_26c9c != 0: seed RNG (203da(15d5a()))
  G_254a8 = sel; G_2530e = sel
  if G_26c9c == 1: G_2530e = demo[G_26ca2++]          // demo byte 0 = rank
  if G_26c9c == 2: demo[G_26ca2++] = (byte)G_2530e
  G_25310 = 1
END:
  stop_song()
  return 0x235a0[G_254a8]                 // map name pointer; the caller ignores it
```

`menu_input(flag)` `FUN_18194`, polled once per frame, counter restarts on every call:
```
key pending: raw 0x4C (cursor up) -> -1; raw 0x4D (cursor down) -> +1; raw 0x44 (Return) or 0x43 (Enter) -> 0; other keys ignored
stick() == 1 (up) -> -1;  stick() == 5 (down) -> +1;  fire() -> 0
WaitTOF; if flag and ++n > 1800 -> 1000
```
`debounce()` `FUN_18228`: wait up to 8 frames while fire or any stick direction is held and no key is pending; returns at once on
release or key → auto-repeat about every 9-10 frames with the stick held.

What a rank choice sets:

| variable | value | used by |
|---|---|---|
| `G_2530e` rank | 0..6 | map index (`12adc`, `0x233af` lookups in `111fc`, `1252c`, `12c84`, `15ae8`), briefing name, advance `15694`, high-score entry |
| `G_25310` mission in rank | 1 | same |
| `G_254a8` | sel | only the return value below |
| `G_26bb4` | sel (menu cursor) | this function only |

Nothing else. Lives, carrier hits, gravity etc. come from `13562` and are the same for every rank (§4). There is **no difficulty
parameter per rank**; difficulty comes from the map and the per-mission tables (§8). [H]

Tables:
```
0x235a0 first map per rank (pointers): maps/a.map d.map g.map i.map k.map l.map m.map   (0x236a6 0x236c7 0x236e8 0x236fe 0x23714 0x2371f 0x2372a)
0x25498 missions per rank (u16[7]): 3 3 2 2 1 1 3
0x233af mission index byte[rank*4 + mission]: r0: 0 1 2 | r1: 3 4 5 | r2: 6 7 | r3: 8 9 | r4: 10 | r5: 11 | r6: 12 13 14
0x2545c map names (15 pointers): maps/a.map .. maps/o.map
0x25860 rank names (7 pointers -> 0x164f8..): "Midshipman" "Ensign" "Lt. Jr. Gr." "Lieutenant" "Lt.Commd" "Commander" "Captain"
```
The menu picture spells the ranks differently (see table above); the strings at `0x25860` are used in the briefing and the high-score table.

Demo: no `wofdemo` file exists on the disk [H listing], so after the 36 s timeout the load fails, `G_26c9c` returns to 0 and a
**normal game starts at the highlighted rank** (or the load dialog opens if line 7 was highlighted) [H code path, M effect].

### 2.1 Save/load dialog `FUN_18b96(mode)` (0 = load, 1 = save) [H, summary]

Lores 320x200, 16 colours, ROM font (8 px) [M]. Palette `0x25960`: `000 28F 05E 00C F80 0F0 CCC F26 FF0 BF0 8E0 0F0 2C0 0B1 FFF 999`.
Text pen 15, JAM1: "Load"/"Save" at (85,19), "Game" (127,19), "Exit Game" (63,193), "Cancel" (222,194) (baseline positions, table `0x258f8`).
Outline boxes (table `0x25918`): 6 slots `(43, 59+16i)-(282, 69+16i)`, buttons `(43,183)-(147,199)` and `(205,183)-(285,199)`.
Slot names = files `wof.<name>` in the current directory (first 6 found, name ≤ 28 chars), drawn at x = 45.
Cursor 0..5 = slots, 6 = Exit Game, 7 = Cancel; highlight = COMPLEMENT RectFill; moved with `menu_input(0)`; load mode skips empty slots
and starts on Cancel when no save exists; save mode edits the slot name with the text field of §5.
Result: 0 = done ("Loading game..."/"Saving game..." at (10,10)), -1 = cancelled. "Exit Game" quits the program.
In game: Ctrl+G (save, only in player state 1), Ctrl+L (load).

## 3. Mission briefing `FUN_18590` [H]

Shown before **every** mission (first mission after rank select, each next mission, and after loading a save).
Returns 1 if Ctrl+R was pressed (→ NEW_GAME), else 0.

- Mode: hires 640x147, 3 planes. Palette `0x2587c` (first 8 used): `000 0AF D30 03D 444 666 888 AAA` (rest `0B6 0DD 0AF 07C 00F 70F C0E C08`).
- Panel: frame **`rank` of `shapes/world.shp`** (256x95 hires px, 3 planes, opaque, labels "RANK: / MISSION: / MISSION OBJECTIVES: /
  ISLANDS: / SHIPS:" are part of the graphic). Drawn at x = 320 - width/2 = **192**, y = 101 - (95>>1) = **54** (bottom 2 rows fall
  outside the 147-line view [M]). `shapes/rank.iff` (640x200, 3 planes, 8 colours, hires, same palette) is the same panel as a picture
  and is **not loaded** by this code [M].
- Texts, `newarmyfont`, cursor = top-left, hires coordinates. Pen = InitRastPort default → colour 7 (`AAA`), JAM2 on colour 0 [M]:

| x, y | content |
|---|---|
| 296, 61 | rank name `0x25860[G_2530e]` |
| 340, 73 | `"%d"` (0x18764) of `G_25310` (mission in rank, 1-based) |
| 340, 119 | `"%d"` of `G_252d2` (islands with enemy forces) |
| 340, 131 | `"%d"` of `G_252c0` (ships present) |

```
draw panel + texts on the back view; flip_wait; fade_to(pal)
WaitTOF
for n = 1; n < 240 and not fire(); n++:
    WaitTOF
    if key pending: k = get_key(); if Ctrl held and to_ascii(k) == 'r': fade_out; return 1
fade_out; return 0
```
Shows about 4.8 s; fire skips. No music (stopped at the end of rank select). The map must already be parsed (`12adc`) because the counts come from it.

The string "Island has %d soldiers and %d pillboxes." (`0x25e6a`) is **not** a briefing text. It is a cheat/debug ticker message (§7).
Mission-end ticker messages (in game, `15694`): `0x238ee` ". . . Good work ! You are ordered to return to carrier to receive your next mission ! . . ."
and `0x239aa` ". . . Congratulations! You have completed your mission!! You are instructed to return to carrier for victory ceremony!! . . .".

## 4. Campaign flow `FUN_10006` [H]

```
start-up (§1)
NEW_GAME:                                                    // 0x10066
  cleanup 11234
  G_25447 = 0 (sound on); G_25510 = 0; G_26c9c = 0 (demo); G_26c94 = 0; G_254f0 = 0; G_25504 = 0
  new_game_init 13562:
      G_25434 = 4        carrier hits
      G_2529c = 0        score (long)
      G_2530c = 0        mission-complete flag;  G_25312 = 0 session over;  G_252ae = 0xFF
      G_252ac = 3        lives
      G_252a0 = 0x6000   gravity;  G_252a4 = 0x400;  G_252a8 = 85;  G_252aa = 160   (flight constants, see player.md)
      1edea (lives drum), 1e608 (clear enemy planes), 135a8
  G_252b2 = 0 (game-over picture); G_25312 = 0; G_25511 = 0; G_252cf = 0 (planes shot down)
  rank_select (§2)                                           // sets rank, mission = 1 (or loads a save: G_26c90 = 1)
  load dash 1653c (day/night by G_252e0, not reset here)
  if G_26c90 == 0: load + parse map 12adc
  if briefing() != 0 goto NEW_GAME
  1edaa; 18806 (level display + palettes); 13252 (ship shapes); 1535a; 13368 (sounds)
  if G_26c90 == 0:
MISSION:                                                     // 0x100d2
      135a8: G_252ad = 0 (ceremony off); clear enemy planes G_2517a/251ae/251e2/25216; G_25126 = G_25128 = 0; unpause; respawn 135d8
      13684 start sortie; G_26c90 = 0; G_254a6 = 0; G_26c8c = 0; G_26c92 = 0
  G_2459e = 0; G_26c90 = 0; 11386; 1174a; if demo: G_26c94 = 2; G_26ca4 = 0xFF
FRAME:                                                       // 0x1010e
  keyboard 1ccf6 (§7)
  if G_25312 goto GAME_OVER
  if G_254a6 (paused): wait VBL (1aa32); goto FRAME
  if G_252b4 and G_2530c:                                    // parked below deck after mission complete
      G_2530c = 0; G_252b4 = 0; stop sounds; ticker off; fade_out2; cleanup 11234
      if G_252ad: G_252ac++                                  // promotion: +1 life (byte, no cap in code)
      111fc: G_252e0 = (mission index > 6) ? random bit : 0  // night, maps h..o only
      1edaa; 12adc (map index = sum(0x25498[0..rank-1]) + mission - 1)
      if briefing() != 0 goto NEW_GAME
      1653c; 18806; 13252; 1535a; 13368; goto MISSION
  frame update 10228; logic ticks 114d8
  if G_25510 (Ctrl+R) goto NEW_GAME                          // no high scores
  if G_26c9c == 1 and fire(): goto GAME_OVER                 // any fire aborts demo playback
  if not G_25312 goto FRAME
GAME_OVER:                                                   // 0x101c6
  stop sounds; clear ticker; fade_out2; G_26ca4 = 0
  G_26edc = (G_26c9c == 1); finish demo 1852a (writes "wofdemo" when recording)
  if G_26ed0 (cheat q / Exit Game): exit program
  G_2459e = 0xFF; ticker off
  if not G_26edc: cleanup 11234; high_score_screen (§5)
  goto NEW_GAME                                              // back to RANK SELECT, not to the title pictures
```

Mission complete `FUN_15694` (called in game when ships-to-sink and islands-to-clear both reach 0):
```
mission++                                   // G_25310
if mission > 0x25498[rank]:
    mission = 1; rank = min(rank + 1, 6); G_252ad = 0xFF     // promoted -> ceremony (§6), +1 life at the next mission load
    ticker += 0x239aa "Congratulations..."
else ticker += 0x238ee "Good work..."
G_25706 = message; G_2530c = -1
```
- Sequence: a b c | d e f | g h | i j | k | l | m n o. Promotion after c, f, h, j, k, l, o.
- **After the last rank**: after map o the rank stays 6 (Captain), mission = 1, promotion flag set → ceremony, +1 life, then
  m n o again, forever. There is no ending screen. [H]
- Session over (`G_25312`) is set by: no lives left or carrier lost (`135d8`, `110c2` countdown), Ctrl+R, demo end, cheat q.
- No mission failure other than game over.
- Carrier hits `G_25434 = 4` are written only in `13562` [H]; whether the map parser re-creates them per mission: see enemies.md [?].

## 5. High scores [H]

Storage: file **`highscore`** in the game directory, 360 bytes = 10 entries of 36 bytes, big-endian:
`+0 long score, +4 word rank (0..6), +6 char name[30]`. Read by `193cc` into a stack buffer (`G_27d2a`) each time the screen runs.
**No defaults in the binary**: if the file is missing, all 10 entries are score 0, rank 0, name = 12 spaces (`0x19464`), and entries
with score 0 are not drawn → the table is empty. The disk image has no `highscore` file [H listing].
Ctrl+C in game deletes the file (§7).

```
high_score_screen 19856:
  play_song(0)                                        // song1; keeps playing until rank select fades it
  entry 19472:
      load table; bubble sort descending by score (19320: swap when entry[i].score < entry[i+1].score, signed)
      if score (G_2529c) > entry[9].score:            // strictly greater
          name entry screen (below) -> name
          entry[9] = { score, rank = G_2530e, name (strncpy 17) }
          fade_out; sort; save 360 bytes (19288)
  table screen:
      set two-viewport view (16d7a)
      P2 = load_pic("shapes/hiscoreslab") into the hires viewport; draw table text on it (1967e)
      P1 = load_pic("shapes/hiscore.iff") into the top viewport
      flip_wait; fade_to2(P1, P2); wait(1800); fade_out2      // 36 s or fire
```

| file | size | planes / colours | mode | position |
|---|---|---|---|---|
| `shapes/hiscore.iff` | 320x75 | 5 / 32 (30 used) | lores | top viewport, lines 0..74 ("HONOR / Wings of Fury / VALOR / ACES" banner) |
| `shapes/hiscoreslab` | 640x200 (marble in rows 0..~130) | 4 / 16 (14 used) | hires | bottom viewport from line 76, 145 lines visible |

```
hiscore.iff CMAP: 000 0AF 730 840 950 A60 C72 D83 D95 EA5 EB7 FD8 FE9 900 B00 F00
                  03B 06E 08F 000 333 444 555 666 777 888 999 AAA CCC DDD EEE FFF
hiscoreslab CMAP: 000 06C 001 223 334 445 556 667 778 889 99A AAB BBC CCD DDE EEF
```
Table text `1967e`: `newarmyfont`, JAM1, hires coordinates inside the slab viewport, cursor = top-left. Three passes for a shadow:
pens `0x259a0 = {0, 0, 15}`, offsets `0x259a6 = {-1, +1, 0}` (same offset on x and y). For row r = 0..9 with score != 0:

| x | y | format | value |
|---|---|---|---|
| 13 + off | 6 + 12*r + off | `"%d"` (0x19846) | r + 1 |
| 53 + off | same | `"%-6ld"` (0x19849) | score |
| 163 + off | same | `"%-12s"` (0x1984f) | rank name `0x25860[entry.rank]` |
| 313 + off | same | raw string | name |

Colour 15 = `EEF` on two black copies. No header line; the titles are in the banner picture.

Name entry screen (`19472`): lores 320x200, 4 planes, palette `0x259ac` =
`000 ECA E00 A00 D80 FE0 8F0 080 0B6 0DD 0AF 07C 00F 70F C0E C08` (words 16..31: `620 E52 A52 FCA 333 444 555 666 777 888 999 AAA CCC DDD EEE FFF`).
Drawn with the system `Text()` call = rastport default font, 8 px wide (the cursor code assumes 8) [M topaz 8]:
- pen 8 (`0B6`), JAM1: "Your name is to be entered" (0x1964e) at (52, 83), "in the hall of fame." (0x19669) at (91, 92) (baseline).
- pen 2 (`E00`): box outline (80,100)-(225,100)-(225,113)-(80,113).
- flip_wait; fade_to(pal); then `text_input(buf, max = 16, x = 82, y = 102)` (`FUN_16086`); buffer starts empty.

Text field `FUN_16086` [H]: pen 6 (`8F0`), BgPen 0, JAM2, 8 px per character, text top at y (baseline y + font baseline).
Cursor = 8x8 COMPLEMENT block at `(x + 8*pos, y)`. Keyboard only for characters:
- printable key (RawKeyConvert result != 0): insert at the cursor if pos < max; cursor right (stops at max).
- Backspace (raw 0x41): delete left. Del (0x46): delete at cursor. Cursor left 0x4F / right 0x4E (with Shift: to start / end).
- Right-Amiga + x [M qualifier bit 7]: clear the field.
- **End of input**: Return (0x44), Enter (0x43), fire, cursor up (0x4C) / down (0x4D), stick up / down.
- Max length **16 characters**. An empty name is accepted. Fire held from the game-over screen ends the entry at once [M].

## 6. Victory ceremony `FUN_1557c` (draw) + `FUN_11c5e` (move) [H]

Active while `G_252ad != 0`: from the mission-complete event of the **last mission of a rank** (set in `15694`) until the next
mission is initialised (`135a8` clears it). It runs during normal play while the player flies back and lands; there is no separate
screen. Coloured balloons rise from the carrier.

Pool `G_26eb6`: **20** records of 18 bytes: `+0 x (16.16, integer word first), +4 y altitude (16.16), +8 dx (long 16.16),
+12 dy (long 16.16), +16 colour byte 0..2, +17 active flag`.

```
draw 1557c (once per rendered frame, only in the normal view G_24e86 == 8; nothing in the 1/8 view):
  for each of the 20 records:
      if not active:                                   // respawn immediately, so all 20 are always alive
          x = carrier_x (G_252e2) - 116;  y = 56       // world px, altitude up-positive
          r = (rol16(rand(), 4)) & 3;  if r == 0: r = 2;  colour = r - 1       // 0: 25 %, 1: 50 %, 2: 25 %
          dx = 0x10000 + 2*(rand() & 0xFFFF)           // +1.0 .. +3.0 px per logic tick (to the right)
          dy = 0x10000 + 2*(rand() & 0xFFFF)           // +1.0 .. +3.0 px per logic tick (upward)
          active = 0xFF
      draw world object type 12 + colour at (x, y) via 15174      // frame table G_26ea4

move 11c5e (once per logic tick, 12.5 Hz):
  for each active record: x += dx; y += dy; if (word)y >= 170: active = 0
```
Shapes (`shapes/world.shp`, world type list `0x23e34` entries 12..14), each 16x5 px, hot spot (6,1), lores playfield:

| colour | frame | playfield colours |
|---|---|---|
| 0 | `balb` | 5, 23 (blue) |
| 1 | `balr` | 3, 11 (red) |
| 2 | `balw` | 23, 31 (white) |

A balloon lives 38..114 ticks (3..9 s) and rises 114 px. Spawning happens in the draw routine, so nothing spawns while the 1/8 view is
shown; records keep moving. No sound, no music. The pool is not cleared at start, so the first frame may show stale records [M].

## 7. Keys `FUN_1ccf6` (called once per frame from the main loop, in game only) [H]

| key | effect |
|---|---|
| Esc | toggle pause `G_254a6` (stop all sounds on pause). While paused the main loop only polls keys; no picture change, no "PAUSE" text |
| Ctrl+R | ticker off, fade out, `G_25510 = G_25312 = 0xFF` → back to rank select without high scores. Also works in the briefing |
| Ctrl+S | toggle sound `G_25447` (stops sounds when switched off; also stops menu music from starting) |
| Ctrl+F | toggle `G_25446` = swap stick up/down (see player.md) |
| Ctrl+G | save-game dialog, only in player state 1 (on deck) |
| Ctrl+L | load-game dialog, not during a demo |
| Ctrl+C | `DeleteFile("highscore")` (dos -72, string 0x1ce46) = clear the high scores |
| Ctrl+V | ticker "Version %d.%d" (0x25e93) with `G_27d32 = 1`, `G_27d34 = 0` → "Version 1.0" |
| Ctrl+B | `illegal` instruction (debug trap). Do not port |

Cheat mode: type **c o l i n** (state `G_25e68` 0→5; a wrong letter among c/o/l/n/i resets to 0). With state 5:

| key | effect |
|---|---|
| m | toggle infinite ordnance (`G_252bd = -1`, or reload from `0x24b49[weapon]`) |
| c | next weapon type `G_252f4` (0..2) |
| r | clear projectiles |
| f | fuel `G_24fd6 = 128` |
| d | oil `G_24fda = 128`, player state 0, toggle invulnerability `G_26ec2` |
| p | lives + 1 |
| 8 / 2 | gravity `G_252a0` ± 0x1000 |
| 6 / 4 | gravity ± 0x100 |
| i / k | pitch rate `G_25e66` ± 50 |
| q | `G_26ed0 = G_25312 = 0xFF` → quit the program (no high scores) |
| Space | ticker with four AvailMem values (format 0x23a8a) |
| F10 (raw 0x59) | clear the ticker message |
| Help (raw 0x5F) | ticker "Island has %d soldiers and %d pillboxes." (0x25e6a) for the island under the plane, from `G_253a0` |

There is no quit key without the cheat (only "Exit Game" in the save/load dialog).

Demo / attract mode `G_26c9c`: 0 none, 1 playback, 2 record.
- Record: start the program with any argument → every game is recorded to `wofdemo` (5000 bytes: byte 0 = rank, then one input byte
  per logic tick, 0xFF terminator), written at game over.
- Playback: starts when rank select times out (1800 frames) and `wofdemo` loads. RNG is re-seeded for record and playback. Two logic
  ticks per frame (`G_26c94 = 2`). Ends on fire or at the end of the data ("demo end" sets `G_25312`); then straight back to rank
  select, no high-score screen (`G_26edc`).
- The shipped disk has no `wofdemo`, so there is no attract mode in practice (§2). [H listing, M]

## 8. Difficulty scaling [H]

No rank multiplier exists. `G_2530e`/`G_25310` are read only to form the **mission index m = `0x233af[rank*4 + mission]`** (0..14 = map a..o).
AA accuracy, enemy plane speed and fire probability are constants (enemies.md). What changes per mission:

1. The map itself (islands, guns, pillboxes, ships).
2. Per-mission tables indexed by m (dumped from `wings.bin`; pairs are `planes, max airborne`):

| m | map | airfields `0x23444` (2 pairs) | destroyer `0x23480` | battleship `0x2349e` | transport `0x234bc` | J-carrier `0x234da` | island bonus `0x233cc` (u16[4]) |
|---|---|---|---|---|---|---|---|
| 0 | a | 0,0 0,0 | 4,3 | 5,3 | 3,3 | 0,0 | 450 0 0 0 |
| 1 | b | 0,0 0,0 | 0,0 | 0,0 | 0,0 | 0,0 | 500 700 0 0 |
| 2 | c | 0,0 0,0 | 0,0 | 0,0 | 0,0 | 0,0 | 1000 600 750 0 |
| 3 | d | 2,1 0,0 | 0,0 | 0,0 | 0,0 | 0,0 | 1500 1100 0 0 |
| 4 | e | 3,1 0,0 | 0,0 | 0,0 | 0,0 | 0,0 | 1000 900 1500 0 |
| 5 | f | 0,0 0,0 | 0,0 | 0,0 | 2,1 | 0,0 | 900 900 0 0 |
| 6 | g | 0,0 0,0 | 3,2 | 0,0 | 3,1 | 0,0 | 900 1200 1200 0 |
| 7 | h | 3,1 0,0 | 3,1 | 0,0 | 0,0 | 0,0 | 900 1600 1000 0 |
| 8 | i | 2,1 0,0 | 4,1 | 0,0 | 2,1 | 0,0 | 1500 1300 1300 0 |
| 9 | j | 0,0 0,0 | 4,2 | 6,2 | 0,0 | 0,0 | 0 0 0 0 |
| 10 | k | 3,1 0,0 | 0,0 | 5,2 | 0,0 | 0,0 | 1600 1500 2000 0 |
| 11 | l | 3,2 3,2 | 3,2 | 4,2 | 0,0 | 0,0 | 2400 0 2500 0 |
| 12 | m | 3,2 3,1 | 0,0 | 5,2 | 0,0 | 6,3 | 3000 2000 2200 2800 |
| 13 | n | 4,1 0,0 | 4,2 | 5,3 | 0,0 | 0,0 | 2500 3000 3200 0 |
| 14 | o | 4,2 0,0 | 4,2 | 5,2 | 0,0 | 7,3 | 3000 3000 3500 0 |

   A ship row only matters if the map contains that ship class (row a has values but map a has no such ships [M]).
3. Night: `G_252e0` = random bit for m > 6 when **advancing** to the mission (not for the first mission of a session). Palettes and
   dashboard files only (`0x25840..0x2585c`: `shapes/wingspalette`/`night.p`, `iff-dash`/`nightdash`, `ocean.palette`/`nightocean.p`,
   `dash.shp`/`nightdash.shp`); no logic change.
4. Lives: 3 at start, +1 per promotion. Score and lives carry over between missions; a new game resets them.

## 9. Notes for the STE port [M]

- 32-colour lores pictures (`wingstitle`, `creditscreen`, `selectrank`, `hiscore.iff`) need a 16-colour reduction or STE palette
  splits; `broderbund` is already 16 colours (two palette states: PAL_A, then the file palette).
- Hires screens (intro text, briefing panel 256x95, high-score slab + text) use 640-px coordinates. In ST low resolution halve x
  (panel at x = 96, texts at x = 148 / 170; table columns 6 / 26 / 81 / 156) and use a half-width font, or switch to medium resolution.
- Intro: 1-plane ring buffer + 16-line top/bottom grey ramps = a per-line palette change of one colour (HBL/Timer B).
- Fades are 16 linear steps on 4-bit components; with the STE 4-bit palette they map 1:1.
- High scores: keep the 36-byte entry layout if a file is wanted; the original starts with an empty table.

## 10. Open questions [?]

1. Real duration of one fade (16 steps without VBL wait): 1 frame per step assumed.
2. Briefing text colour: colour 7 (`AAA`) from the InitRastPort default pen is inferred, not seen on screen; same for the ROM font used
   by the name entry and the save dialog (topaz 8 assumed).
3. Vertical placement of the 147-line briefing view and of the copper ramps of the intro relative to the display top.
4. Whether carrier hits (`G_25434 = 4`) persist across missions or are rebuilt by the map parser.
5. Meaning of `G_252ae = 0xFF`, `G_252a4 = 0x400`, `G_252a8 = 85`, `G_252aa = 160` set at new game (flight constants, see player.md).
6. Stale balloon records on the first ceremony frame (pool not cleared) not verified.
