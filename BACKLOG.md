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
- **The floppy image on a real drive or Gotek** with 0.9.x or later (0.8.0 ran on an STE with a Gotek).
- **New in 0.9.3**: ships and the own carrier sink 1 px per stage, with the ship's row showing at the waterline
  between the wave crests; pillbox damage in the 1/8 view; the Zero's muzzle flash in the colours of the Amiga's
  exclusive-or; Ctrl+S, F, C, V. Checked in Hatari only.

## Known issues

- **Sound clicks on real hardware**. Sporadic clicks while the DMA sound plays, on the STE and the
  Mega STE about equally, not in Hatari. They occur over a silent buffer too, stop only with the DMA off, and the
  plain-screen build without the split-screen code clicks as well. Most likely the known hardware behaviour (Shifter ground
  bounce into the sound DAC latches, atari-forum t=41328); no software workaround is documented. Not tried: a
  25 kHz DMA rate, cold against warm machine, other DMA-sound software on the same machines. A YM2149 fallback
  would be the way out if it stays a problem.

- **Flicker during take-off in Steem** (P2, reported): the game runs in Steem but "flickers some during takeoff",
  with a PAL and with an NTSC TOS 1.62. Not reproduced: Steem has not been run here (no macOS version), and Hatari
  and the real machines do not show it. That report was for a build before 1.0.0, whose display code was different; to be
  checked again with the current build. Low priority as long as it is Steem only.

- **Freeze after Ctrl+Q** (P2, seen on a Mega STE with 1.0.0, started from the cartridge): after quitting with
  Ctrl+Q the screen is white with some garbled letters and the machine hangs. Open: whether it is the display code of this build (the exit path may leave Timer B or the split-screen list
  running), the cartridge's program runner, or the desktop's resolution; whether "Exit Game" in the load dialog does
  the same. Not reproduced in Hatari: started from the desktop under HDDRIVER (TOS 2.06), from a subfolder and from the
  floppy's AUTO folder (TOS 1.62), Ctrl+Q in a mission returns to a working desktop each time.

- **Own carrier sinking: parts stay behind** (P3, seen on a Mega STE): the ship sinks as it should, but some
  objects on it stay where they were, the flag mast for one, maybe others. To do: list what is drawn as sprites of
  their own on the carrier (mast, flag, parked planes, guns) and move or hide them with the sinking stage.

- **Black playfield after Ctrl+R** (P3, seen once on a Mega STE, started from the cartridge with unpacked files): a
  mission was played for a while, Ctrl+R went back to the rank selection, CAPTAIN was chosen; the screen was black
  for a moment, then the panel came up but the playfield stayed black. Not reproduced in Hatari with the same steps
  (`tests/rank_restart.txt`, `rank_restart2.txt`). Seen with an earlier build; open whether the current one does it.

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

- **Throttle feel:** pushing toward the nose raises the airspeed from 1000 to 1400 as in the original code, but
  acceleration feels "missing" on the STE. What is expected (sound, movement on screen) is not clear.
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
