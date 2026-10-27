# What the atw-snoop debug screen found in Wings of Fury

The debug build (`make atw` / `make atwrun`; the library and its documentation: github.com/theimann/atw-snoop) shows a live frame profile on the ATW800/2
card's output while the game runs on the Mega STE's own screen. This file keeps track of what it showed and what
changed in the game because of it, measured with the same scripted run (run 1, `deploy_ste.sh --run=1 --atw`) on
the Mega STE at 8 MHz. Changes to the debug code itself are listed apart: they make the measurement cheaper, not
the game faster.

## The game

| Build | What the screen showed | Change in the game | Slow frames, run 1 |
|---|---|---|---|
| 1.1.0+3627284 | busy ~21 ms of the 60 ms pacing (3 VBLs) in the opening; bgrestore the largest section (13 ms average, 23 ms worst); single sections jump to 16-23 ms in the frames that run over (each time another one) | none yet | 124 of 3699 (debug build) |
| 1.1.0+2fdae3c (plain) | baseline without the debug screen | none | 80 of 3713 |
| 1.1.0+6af8b47 | **The sound mixer drives the late frames in flight.** Per second (PROF lines) mixing is 0.47 ms a frame (median), but 8-20 ms a frame while guns fire, shells hit and the plane crashes (VBL 5595, 8862, 9120, 11285-11442 of run 1). VBL samples of the late frames (LPC lines): `snd_mix_side` 15 % of the samples outside the pacing wait, against ~2 % of the time on average. Arithmetic: the two-voice loop is ~94 cycles a sample, both sides at 12517 Hz: four voices cost ~6 ms per VBL of sound, ~18 ms of a 3-VBL frame; a 4-VBL frame needs 4 VBLs of sound, so a late frame makes the next mix larger (the scene stays late). Also over-represented in late frames: `panel_restore` (5 % against 1.5 %), `fpv_draw` (6 % against 3 %). | none yet: the cheap levers change the sound (open) | 122 of 3698 (debug build) |

## The debug code

| Change | Its own cost a frame |
|---|---|
| first hardware run (1.1.0+c8d4dda) | 2.2-8 ms shown; the clock went back up to 5 ms at times (timer C ran out with its interrupt not yet taken): wrapped figures of 176 million us |
| snoop_clock adds the pending tick; a negative section shows 0 | 2.2 ms |
| per section one subtraction and two stores; raw counts, scaled by the card's T425 (atw-snoop: scaled decimal slots); numbers every 4th frame | ~0.8 ms (780-1200 us; 4 ms in the frame that also does the once-a-second work) |
| the run build logs LATE (sections of every late frame), PROF (each second's averages) and LPC (the PCs at the last six VBLs of a late frame, from a stub ahead of the frame interrupt); `tools/atw_late.py LOG MAP OBJ` sums them up | (log only) |
