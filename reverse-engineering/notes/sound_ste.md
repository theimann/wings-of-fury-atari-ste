# Sound on the STE: research (2026-10-02)

## What the Amiga game plays (render_sound.md 6 and 7)

- **In game: no music.** Only 8 raw signed 8-bit samples (about 52 KB together) on Paula's 4 channels, driven by a VBL routine.
  Each channel has a 2-slot priority scheme that is re-evaluated every logic tick (12.5 Hz):

| ch | priority 0 | priority 1 |
|---|---|---|
| 0 | player machine gun (loop, ~17.7 kHz) | player **engine** (loop, pitch and volume follow speed/altitude, ~4.4 kHz) |
| 1 | enemy machine gun (loop, ~22 kHz) | enemy engine (loop, volume by distance) |
| 2 | boom (once) | splash (once) / loop |
| 3 | AA gun fire (loop) | clang, screech, scream (once), grind (loop) |

- The engine pitch is continuous (Amiga period = f(speed, altitude), slewed per tick). That is the one sound the STE's 4 fixed DMA rates can't do without software resampling.
- Distance-based volumes (0..64) for one-shots, the enemy engine and the AA guns.
- **Menus only: music.** A small 4-voice note driver (`songplay` + `wofsongs`, 8SVX instruments: bass, lead, brass, kick, snare, "Mech"), songs 0-4. The format is fully documented in render_sound.md 7.3 and could be converted.

Samples: engine 13919 B, splash 6752, screech 6746, scream 6572, metal.clang.1 5703, boom 5466, grind.1 4788, machinegun 1886.

## STE DMA sound (hardware facts)

- 8-bit signed PCM, mono or stereo (stereo = interleaved L/R bytes), at **6258 / 12517 / 25033 / 50066 Hz** only.
- Registers: `$FF8901` control (bit 0 play, bit 1 loop), frame start `$FF8903/05/07`, frame end `$FF890F/11/13`, current address (read) `$FF8909/0B/0D`, mode `$FF8921` (bit 7 mono, bits 0-1 rate).
- **Loop mode latches the next start/end at the frame end.** This gives a gap-free double-buffered or ring-buffered stream. The end of each frame toggles MFP GPIP7 / Timer A input, so it can trigger an interrupt or count frames.
- DMA fetches use the blanking slots, so they cost the CPU almost nothing.
- **One stream only:** there is no hardware mixing. Several simultaneous sounds need a software mixer.
- The Microwire LMC1992 (`$FF8922/24`) sets master/left/right volume and bass/treble, and mixes the YM in or out.
- Hatari emulates all of this well; we can develop and profile there first.

## What AGT has (agtools/agtsys/sound)

- A YM music system (BMM/MIDI-like, channel multiplexing; demos h-shmup and bosscore) plus a **single DMA "percussion" channel**: start/end a sample, one at a time, by priority. There's no mixer.
- `sound.h` still contains parts of an older DMA software mixer (resampling, pitch bend, volume states), flagged in the source as "a giant mess... due for deletion". Not something to build on.
- So for multi-voice DMA we'd write our own small mixer. AGT's YM side stays available if we ever want it.

## Options

**A. Software mixer, 4 voices, mirroring the Amiga channels (recommended)**
- Mono at 12517 Hz into a DMA ring buffer in loop mode; mix about 250 bytes per VBL (or per 2 VBLs) in the VBL/Timer-A interrupt.
- Port the original's channel and priority logic (`FUN_12066`/`12132`) 1:1: same triggers, same volumes, same arbitration.
- Fixed-pitch samples are resampled offline to 12517 Hz (step 1, cheapest inner loop). Only the two engines get a 16.16 fractional step computed from the Amiga period (rate = 3546895/period).
- Volume 0..64: a 65×256-byte scale table (16 KB), or 16 steps (4 KB). Headroom: each voice pre-scaled to 1/4, or a sum/clip table.
- CPU estimate (68000 @ 8 MHz, ~160k cycles/VBL): roughly 12-30 cycles per output byte per active voice.
  - Typically 1-2 voices are active (engine plus occasional effect): about 4-8%.
  - Worst case, 4 voices: about 15-18%.
  - At 6258 Hz the cost halves, with some loss of brightness (the gun is ~17-22 kHz on the Amiga).
- Memory: the samples resampled to 12.5 kHz come to about 50-60 KB (the engine stays at its native ~4.4 kHz, stepped). The current free RAM after load is ~268 KB in Hatari, less on the STE, so it fits but is noticeable. Pre-converting to 6.2 kHz would halve it.

**B. DMA one-shots plus YM engine (cheapest)**
- AGT-style single DMA channel for the effects (zero CPU, one at a time by priority, the gun loop included); the engine drone on the YM (tone + noise, continuous pitch, zero CPU).
- It sounds noticeably less like the original: overlapping sounds cut each other off, and the engine is synthesized.

**C. Two-voice mixer (engine + one effect)**
- Half the cost of A. The original's channel priorities collapse to "engine + highest-priority effect".

## Recommendation / next steps

1. Measure the frame budget first: how many VBLs a drawn frame takes now (Hatari and the real STE), to see what a mixer can take.
2. Build option A as an isolated module (`snd.s` mixer + `snd.cpp` channel logic), 12517 Hz mono, with a compile switch for 6258 Hz and a voice limit.
3. Convert the samples offline (tools: resample to the output rate, keep the engine native) and load them as one bank file.
4. Port the trigger and priority logic from render_sound.md 6.3, then compare against vAmiga recordings (the rig can record audio with REC).
5. Menu music later: convert `wofsongs` (documented format) to the same mixer (menus aren't CPU-bound), or to AGT's YM player.
