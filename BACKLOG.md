# Wings of Fury STE: open points

What is still open. Things that are done are not listed.

## To confirm on real hardware (fixed in code, checked in Hatari)

- **HDDRIVER black screen** (fixed in 0.9.0, see `docs/AGT_CHANGES.md`, "The 200 Hz clock"): confirmed in Hatari
  with the HDDRIVER 13.01 demo, not on a real machine with HDDRIVER.
- **Quit: the desktop's own resolution and palette** (0.9.0). To test on the STE and the Mega STE: start from a low
  and from a medium resolution desktop, quit with Ctrl+Q and with "Exit Game" in the load dialog; check resolution,
  colours and mouse pointer. The medium case has not run anywhere.
- **Floppy program started by hand** (0.9.0): on a machine that boots from a hard disk the floppy's AUTO folder is
  not run; started from the desktop the program looks for DATA one folder up. Checked in Hatari with the same
  folder layout on a hard disk folder, not from a floppy.
- **Memory check** (0.9.1): "Not enough free memory. Free: n KB, needed: n KB". Needed at the game's entry:
  1164 KB with the files as they are, 1258 KB with the packed floppy files (the check adds 16 KB for larger level
  bundles: an estimate, only mission 1 was run at the limit). A plain 2 MB STE has 1547 KB there (TOS 2.06:
  1538 KB), a 1 MB one 499 KB.
- **New in 0.9.3**: ships and the own carrier sink 1 px per stage, with the ship's row showing at the waterline
  between the wave crests; pillbox damage in the 1/8 view; the Zero's muzzle flash in the colours of the Amiga's
  exclusive-or; Ctrl+S, F, C, V. Checked in Hatari only.

## Known issues

- **A chasing enemy plane does not attack** (P1, seen in Hatari with 1.0.0+f248896): a plane
  that chases the player gets right behind it but does not fire; it turns round, then follows again, and repeats
  that cycle. Looked at so far: a Zero from an airfield (map d) behind a plane flying straight and level holds 131 px
  and fires until the player goes down, so the fighter's attack works. Missions a, b and c have no airfield and no
  ship: the only enemy planes there are the carrier bombers, which never fire at the player in the original either
  (`zero_bomber`, FUN_1dea4): they go for the carrier, turn round when they are past it or when their timer runs
  out, and slow down when the player is behind them. Open: which mission it was. If it was a bomber, this is the
  original's behaviour; if it was a fighter in a later mission, the case has to be found (turning player, two
  planes and the attack queue, a plane coming head-on).

- **Garbled desktop after Ctrl+Q** (P2, seen on a Mega STE with 1.0.0+395b65c, booted from the floppy image on a
  Gotek): after Ctrl+Q the desktop comes back with a pink tint and a doubled picture (menu text and icons appear
  twice, shifted sideways); the mouse pointer still moves. An earlier report from the same machine, started from
  the cartridge, was a white screen with garbled letters and a hang. Not reproduced in Hatari: floppy with TOS 1.62
  and TOS 2.06, a subfolder, and from the desktop under HDDRIVER all return to a clean desktop. To look at: what the
  exit leaves in the STE's video registers on the real machine (horizontal scroll `$ff8265`, line width `$ff820f`,
  the palette, the resolution against the one TOS assumes), the order and the moment of those writes (in the
  vertical blank or not), and whether a timer of the display code can still fire after the vectors are restored.

## Differences from the Amiga still open

- **Enemy ships don't bob** on the waves. The original (measured in vAmiga, map g's ship): the whole
  picture, its guns and parked planes move 1 px up and down with the wave bob (2, 3, 4, 3: a step every 21 ticks; a
  larger value is lower), the wave strip in front stays still, and a sinking ship keeps bobbing. Here only the own
  carrier bobs (three stored copies), and it stops when it sinks. The sinking mechanism could do it (shift = stage +
  bob - 3), but then every ship in view needs its block of own tiles (about 40 KB each) and a redraw every 1.7 s.
- **Ctrl keys:** all of the original's are in (Ctrl+V shows this build's version where the original says
  "Version 1.0"). Ctrl+S, F, C, V have not been run yet. Ctrl+B (a debug trap) is left out on purpose.
- **Sea crash near the carrier:** the orange explosion uses the Amiga's position values but sits some pixels higher
  on the plane in the pictures (`tests/crash_sea_near.txt`); cause
  not found.
- **Sky flash:** stepped every 3 VBLs here, per drawn frame on the Amiga (4 VBLs during a crash).
- **Rocket homing:** matches the Amiga at a pillbox; the ship gun path was only read. Our atan
  is a table search (can differ by 0.35 degrees), sin1024 truncates to degrees, the slip during the delay uses the
  direction at launch.
- **Game-over countdown** runs per tick (per drawn frame in the original).
- **Original quirks not reproduced:** the gun can hit falling planes and wrecks again (each hit scores +350 and
  counts as a kill, FUN_1b682 has no state test); a burning wreck on an island keeps the intact plane picture until
  it moves to the wreck list.
- **Front end:** the hires parts (briefing panel, marble slab) are halved to low resolution; table and name entry
  use the 5x7 message font in upper case; the night panel uses the night palette only (the Amiga's night dashboard
  picture differs in about 900 pixels).
- **World ends:** ours wraps at the tile map's sea margins, 200 px before either end; the original has a 16-bit x
  that wraps after about 65000 px of open sea.
- **Palette:** 16 colours for 32; a dark brown is forced in so that bunkers and huts keep their detail.
- **Ours only:** H (help page), Esc (pause page), Ctrl+Q (quit), a loading screen before every load, the title
  picture stays until the game is loaded.

## Not compared with the Amiga

- **Forward view** (ported from the code, `reverse-engineering/notes/forward_view.md`): the carrier shapes when flying left, the
  tree strip using `dug0` in the two nearest bands, the enemy-plane size table, the sticky "no landing view" flag
  after an enemy ship was shown. One capture with the own carrier ahead while flying left settles the first three.
  The window is 60 px wide here (61.5 on the Amiga).
- The J-carrier's take-off roll (ported, no test flight), the Zero's x-step helper in FUN_1d796, the launch routines
  11622 / 11510, the player's 1/8 frames.
- Saved games: the exact dialog texts, what else the original's file holds, the demo recording.

## Undecided

- **Frame pacing:** 3 VBLs per frame (16.7 fps, the Amiga's own rate) is the default.
- **Keys of ours** (H, Esc pause page, Ctrl+Q): keep per target or not.

## Enhancements (beyond the original, for a later edition)

- **Falcon030:** AGT's timer-driven display shows a black screen on the Videl; it would need a display path of its
  own. The game says "needs an STE or Mega STE" on Falcon and TT (the TT has no blitter).
- **1 MB machines:** about 665 KB too much today (1164 KB needed, 499 KB free). The level in memory (the map has
  4 bytes per cell), the screen buffers, sprites and sound would all have to shrink; an exact memory map of a
  running mission would be the first step.
- **Panel digits** as dark digits in white boxes (score, planes shot down), easier to read.
- **Propeller animation** (static in the original).

## Reference

**Builds** (`tools/make_release.sh` -> `builds/release-<id>/`): `hatari/` (unpacked, files beside the
program), `floppy/wof.st` (packed, one 720 KB disk, program in
AUTO, DATA and SAVE folders), `harddisk/WOF/` (unpacked, DATA and SAVE folders). README.TXT with the build's
version line is in every target. Before publishing: run the floppy image on 2 MB, the files-beside-the-program
layout from a subfolder, and the hard disk version under HDDRIVER (an ACSI disk image with the HDDRIVER demo).

**Saved games:** `SAVE1.WOF` .. `SAVE6.WOF`, header + state blocks + the tile map entries that differ from the
mission's map (about 13 KB). Tied to the build: a change of a saved struct makes old files "not a saved game";
`SAVE_VERSION` must be raised when the meaning of a field changes.

**Footprint:** unpacked 5.7 MB (tiles 2.0, maps 2.7); packed floppy 720 KB image with about 95 KB free. The Amiga
original is 631 KB on its 880 KB disk.

**Speed:** 3 VBLs per frame in flight. A sinking ship costs 0.2 VBL per frame on average, about 1 VBL in its last
seconds. The forward view costs up to about 8 % low over an island (compiled C; an assembly blitter would free it).

**AGT:** the changes are in `agt-patch/agtools-local.patch` and described in `docs/AGT_CHANGES.md`. Known AGT fault to report some day: an IMSPR entity
in the same draw layer as EMX entities, or drawn last in a pass, makes the following EMX drawing crash (our
workaround: IMSPR only in layer 1, the EMX separator bar always last).

**Tests:** `tools/suite.sh <names>` replays `tests/*.txt` in Hatari (`WOF_MEMSIZE=2` for a
2 MB check). The Amiga side was run in a headless vAmiga with snapshots and scripted input (not part of this
repository).
