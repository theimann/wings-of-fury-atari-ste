# Wings of Fury (Amiga) – menu music: formats, replay model, inventory, STE port options

**Status 2026-10-04: implemented as option (a)** – `tools/make_music.py` -> `music.dat` (38 KB, 30 KB packed), player
`game/music.h` on the mixer of `game/snd.h`; the mix runs in the VBL while a song plays. Differences from the Amiga:
voices at twice the level (the mixer halves volumes), tick lengths rounded to whole output samples (253 / 271), PAL
pitch, output at 12.5 kHz (brass notes above that rate alias). Not listened to against the Amiga yet.

Sources: `amiga-original/{songplay,wofsongs}`, `reverse-engineering/notes/scratch/songplay.s` (songplay relocated:
CODE at 0, DATA at 0xa90), `reverse-engineering/notes/scratch/ann.s` (wings), `game/snd.h` (STE mixer). Earlier summary: `render_sound.md` §7.
Marks: **[H]** read from code/bytes, **[M]** inferred, **[?]** open. Numbers in §3/§4 come from the script in §6.

Correction to `render_sound.md` §7.2: the timer is **CIA-A** timer A (`ciaa.resource`, registers `bfe401/bfe501/bfee01`),
not CIA-B [H].

---------------------------------------------------------------------------------------------------
## 1. Files

### 1.1 `songplay` (5148 B) – the player [H]
| hunk | type | size | content |
|---|---|---|---|
| 0 | CODE | 2696 (0xa88) | dispatcher + player, 138 relocs, symbols present |
| 1 | DATA | 988 (0x3dc) | resource name, interrupt struct, period table, duration table, state, 4 track structs |
| 2 | BSS | 4 | unused |

Entry = first code byte, `jsr (seg+4)` with `d0` = command (symbol names from the hunk):

| d0 | symbol (code offset) | args | action |
|---|---|---|---|
| 0 | `_OpenTimerInt` 9bc | – | OpenResource("ciaa.resource"); AddICRVector(bit 0 = timer A, is_Code = `SongInt`, name "Music TimerInt"); CRA = 1 (start, continuous); save vector 0x70 and install own level-4 audio handler `SongIntHandler`; INTENA 0x8780 |
| 1 | `_ReadInstruments` 946 | d1 = song index, d2 = song table | `SongAddr = table[d1]`; voice table = song+16; for each voice (from index 1, until 0) with an 8SVX pointer: search "VHDR" / "BODY" (word steps), store pointers, `+8 = 83 / ctOctave` |
| 2 | `_PlaySong` 92a | – | if PlayState == 0: PlayState = 1 (start at next tick) |
| 3 | `_StopSong` 64 | – | DMA off, PlayState = 3 (cleared at next tick) |
| 4 | `_CloseTimerInt` a50 | – | RemICRVector, audio IRQs off, DMA off, restore vector 0x70 |
| 5 | `_GetSongStat` 29e | – | d0 = PlayState (0 stopped, 1 start pending, 2 playing, 3 stop pending, 4 fading) |
| 6 | `_FadeSong` 84 | d1 = speed | FadeCount = FadeSpeed = d1, PlayState = 4 |
| 7–9, 12 | `_PlaySfx`, `_StopSfx`, `_SfxStat`, `_AdjustSfx` | a0 = {len, …, rate}, d1 = channel, d2 = vol, d3 = repeats, d4 = music volume scale | one 8SVX-style effect on a music channel (channel flag `+70` mutes the track's register writes; music volume × d4/256 while an effect runs) – **never called by `wings`** |
| 10 / 11 | `_PauseMusic` / `_RestartMusic` | – | Paused flag, DMA off / resume – not called by `wings` |

`wings` only issues commands 0, 1, 2, 4, 5, 6 [H: all calls go through `G_2553e` in `123dc`/`12470`].

### 1.2 How `wings` uses it [H]
```
play_song(name="wofsongs", n)  @123dc
    G_25542 = n
    if (G_27378 /*song seg loaded*/) {
        songplay(6, d1=2)                         // FadeSong(2)
        if (!sound_off /*G_25447*/) while (songplay(5)) ;   // busy wait until PlayState == 0  (~2 s, §2.5)
    } else {
        G_27378 = LoadSeg(name);   G_2737c = ((seg<<2)+4)()      // wofsongs code returns a0 = DATA hunk = song table
        G_2553a = LoadSeg("songplay"); G_2553e = (seg<<2)+4
        songplay(0)                               // OpenTimerInt
    }
    songplay(1, d1=n, d2=G_2737c)                 // ReadInstruments
    if (!sound_off) { songplay(2, ...); G_27380 = true }       // PlaySong
stop_song()  @12470 : FadeSong(2); wait (unless sound off); songplay(4); UnLoadSeg both; clear pointers
```
Callers: `play_song(2)` + `play_song(1)` in start-up `18022`, `play_song(4)` rank select `18272`, `play_song(0)` high
score `19868`; `stop_song` at `10216`, `184d6`, `19146` (before a mission / demo). Music and the game's own effect driver
(`1e8b8…`) are never active together: both replace the level-4 vector and own all 4 Paula channels [H] → **music only on
screens without effects; all 4 channels belong to the music.**

### 1.3 `wofsongs` (41328 B) [H]
| hunk | type | size | content |
|---|---|---|---|
| 0 | CODE | 276 | `lea data,a0; rts` + a compiler `segload` stub (unused) |
| 1 | DATA, **MEMF_CHIP** | 39020 (0x986c) | everything below; 349 relocs, all into this hunk; symbols present |
| 2 | BSS | 4 | – |
(+ an empty HUNK_OVERLAY 0x3f5 trailer; `tools/hunk.py` stops there with an error – the script in §6 handles it.)

DATA hunk map (offsets in the hunk):
| offset | symbol | content |
|---|---|---|
| 0000 | `songs` | 5 pointers: `song1, song2, song3, song2, song4` (index = play_song argument) |
| 0014, 0040, 006c, 009c | `song1..4` | song header |
| 00cc..020d | `voice0..6` | 7 voice structs × 0x2e |
| 020e..0c17 | – | track lists and patterns of the 4 songs (2570 B in total) |
| 0c18 | `BassDrum3Data` | IFF 8SVX file, 3504 B |
| 19c8 | `SnareDrum1Data` | 1746 B |
| 209a | `RoomBrassData` | 8420 B |
| 417e | `SyntheBassData` | 8132 B |
| 6142 | `OmleadData` | 6580 B |
| 7af6 | `Mech1Data` | 7542 B (ends 0x986c) |

```
song header:   u32 track_list[4];            // track t plays on Paula channel t (AUD0..3)
               u32 voice[];                  // instrument table, 0-terminated; index = argument of command 0xdc
                                             //   song1/2: voice0..5, song3/4: voice0..6  (voice0 = no sample = rest)
track list:    { u32 pattern; s16 transpose; } [];   // 6 bytes per entry, no terminator (patterns end the list)
pattern:       2-byte events, see §2.2
voice (0x2e):  +0 u32 VHDR data ptr (set by ReadInstruments)   +4 u32 BODY data ptr (ditto)
               +8 u16 83/ctOctave (ditto)   +10 u32 8SVX file ptr (0 = rest voice)
               +18 u16 vibrato limit up, +20 limit down, +22 s16 step, +24 speed, +26 delay, +28 counter, +30 enable
               +34 u16 arpeggio enable, +36 s16 arpeggio offsets[4], +44 u16 arpeggio phase
```
All vibrato fields and both enable words are **0 in all 7 voices** (arpeggio offsets `{4,7,0,12}` are filled in but
switched off) [H].

Instruments (8SVX VHDR; all 1 octave, uncompressed, signed 8-bit, volume 0x10000) [H]:
| voice | NAME | role | oneShot | repeat (loop) | bytes | samplesPerHiCycle | VHDR rate |
|---|---|---|---|---|---|---|---|
| 1 | SyntheBass.iff | bass, tonal | 7644 | 384 | 8028 | 8 | 8363 |
| 2 | omlead.iff | drone / pad, tonal | 3434 | 3042 | 6476 | 16 | 4181 |
| 3 | RoomBrass2.iff | brass lead, tonal | 1768 | 6548 | 8316 | 8 | 8363 |
| 4 | BassDrum3 | kick, percussion | 3400 | 0 | 3400 | 32 | 8363 |
| 5 | sdrum1.iff | snare, percussion | 1642 | 0 | 1642 | 32 | 8363 |
| 6 | Mechanic1.iff | effect ("mechanical"), played once | 7374 | 64 | 7438 | 32 | 8363 |
Sample data total **35300 B**. The VHDR rate is not used by the player; pitch comes from `samplesPerHiCycle` (§2.3) [H].
"tonal / percussion / effect" is from names, loop lengths and use in the songs; not listened to [M].

---------------------------------------------------------------------------------------------------
## 2. Replay model

### 2.1 Timing [H]
* Tick = CIA-A timer A interrupt (level 2 via `ciaa.resource`), continuous mode. Period = `TAHI<<8 | TALO` E-clock cycles.
* Songs set only TAHI (command 0xdd): **60** in song1, **56** in song2/3/4; TALO (0xde) is never written by a song or
  by the player → low byte = whatever the latch held [?].
* Tick rate (PAL E-clock 709379 Hz): TAHI 60 → 45.4–46.2 Hz, TAHI 56 → 48.6–49.5 Hz (NTSC 715909 Hz: +0.9 %).
  Used below: **46.2 Hz** (song1), **49.5 Hz** (others), i.e. TALO = 0 [M].
* Whole note = 96 ticks → quarter = 24 ticks → about 115 BPM (song1) / 124 BPM (others) [M].
* Audio (level 4) interrupt per channel handles one-shot end and the switch to the loop part.

### 2.2 Pattern events (2 bytes: command, argument) [H]
| byte 0 | meaning |
|---|---|
| `< 0xd9` | note: `n = (b0 & 0x7f) + transpose` (transpose from the track-list entry); **bit 7 = tie**; b1 = duration index |
| `0xd9` | next track-list entry (pattern end) |
| `0xda` | end of track (track inactive) |
| `0xdb` | loop track from list entry 0 |
| `0xdc i` | instrument = song voice table[i] (0 = rest voice) |
| `0xdd v` / `0xde v` | CIA-A TAHI / TALO = v, then force-load + start (tempo) |
| `0xdf v` | track volume 0..64 (ignored while fading); written to AUDxVOL at once |
| `0xe0 v` | sustain mode (1 = no note-off at gate end) – not used by any song |
| other ≥ 0xe1 | skipped |

Duration table (songplay DATA+0x254), index → length/gate in ticks:
`0 96/86 · 1 48/43 · 2 32/28 · 3 64/58 · 4 24/21 · 5 72/64 · 6 12/10 · 7 84/75 · 8 60/54 · 9 36/32 · 10 6/5 · 11 90/81 ·
12 78/70 · 13 66/59 · 14 54/48 · 15 42/38 · 16 30/27 · 17 18/16 · 18 8/7 · 19 16/14`

### 2.3 Per-tick logic per track (`0x4f4`) [H]
```
if (!active) return
if (count != 0) {                       // note running
    count--
    if (count == gate_off) {            // 'gate' ticks after the note start
        if (sustain != 1 && tie == 0) { DMA off for the channel; AUDxVOL = 0; AUDxPER = 124; irq_state = -1 }
    } else if (voice.arpeggio) period(note + arp[phase++ & 3])       // unused
    else if (voice.vibrato)  triangle on the period between the limits     // unused
    return
}
loop: read event
    command      -> execute, next event
    note         -> tie: bit7 set: if (tie == 0) tie = 2;   bit7 clear: tie = 0
                    count = len-1; gate_off = len-1-gate
                    if (voice has no sample) return                       // rest
                    if (tie == 1) return                                  // tied continuation: nothing changes, not even pitch
                    if (tie == 2) tie = 1
                    octave o = max(0, ctOctave - note/(83/ctOctave) - 1)  // = 0 here (all instruments 1 octave)
                    AUDxPER = K[note] / (samplesPerHiCycle << o)          // K[n] = 3579545 / f(n), n = 27 -> 261.6 Hz (C4);
                                                                          //   table covers n = -33..98
                    AUDxLC  = start of octave o;  AUDxLEN = (oneShot + repeat)/2
                    loop_ptr = start + oneShot;   loop_len = repeat/2;  irq_state = 1
                    AUDxVOL = track volume (default 32; × SfxMusicVol/256 while a songplay effect runs)
                    ADKCON 0x00ff cleared; DMA on; audio IRQ on
audio IRQ:  irq_state 1: loop_len != 0 -> AUDxLC/LEN = loop part, state -1 (loops until note-off)
                         loop_len == 0 -> state 0;  state 0 at the next IRQ: DMA off, volume 0 (one-shot finished)
```
* A note sounds `gate` ticks of its `len`; looped instruments are cut hard at gate end (no release) [H].
* Tie: the first tied note triggers and suppresses its note-off; following tied notes only extend it. A track whose
  notes are all tied triggers **once** and then holds its looped sample forever (the drones of song3/4) [H].
* No ADSR, no volume slides, no portamento; vibrato/arpeggio code exists but is disabled by the data [H].
* The player uses the NTSC constant 3579545; on a PAL Amiga every pitch is 0.9 % lower (3546895) [H/M].
* Stereo by Paula: tracks 0 and 3 left, 1 and 2 right [H by the register pointers in the track structs].

### 2.4 Start / end [H]
PlayState 1 → at the next tick all 4 tracks: active, list entry 0, **volume 32**, DMA off, state 2. A song ends
(PlayState 0, all off) when no track set its bit in `TrackState` – all 4 songs loop with `0xdb`, so never.

### 2.5 Fade [H]
`FadeSong(s)`: every `s+1` ticks each track volume −1; when all are 0 → stop. The faded volume reaches AUDxVOL **only at
the next note trigger**, so held notes (the drones) do not fade, they stop. With s = 2 and volume 32: 33×3 ≈ 99 ticks
≈ **2.0 s**, during which `play_song` busy-waits.

---------------------------------------------------------------------------------------------------
## 3. Inventory (songs by play_song index)

Ticks/events [H] by the script; seconds [M] (tick rate, §2.1); duty = share of the loop a track's channel is sounding
(gate time, one-shots limited by their sample length) [M].

| index | song | screen (frontend.md) | TAHI | loop: ticks / bars / s | tracks 0-3: instrument, note events, duty | samples needed |
|---|---|---|---|---|---|---|
| 0 | song1 | high-score table | 60 | 1536 / 16 / **33.3** | brass 58 (0.79) · brass 22 (0.93) · bass 128 (0.88) · snare 52 + kick 28, vol 30 (0.62) | bass, brass, kick, snare = **21386 B** |
| 1, 3 | song2 | Broderbund logo / title / credits (index 3 unused by the game) | 56 | 1152 / 12 / **23.3** | brass 44 (0.88) · brass 28 (0.89) · bass 96 (0.88) · snare 44 + kick 18, vol 30 (0.64) | same **21386 B** |
| 2 | song3 | intro scroller | 56 | 2688 / 28 / **54.3** | omlead C5 drone (1.00) · omlead C4 drone (1.00) · omlead C3 drone + Mech once + snare at 1761 Hz once (0.97) · brass 20 notes (0.27) | omlead, brass, snare, Mech = **23872 B** |
| 4 | song4 | rank selection | 56 | 1344 / 14 / **27.2** | omlead C5 (1.00) · omlead C4 (1.00) · omlead C3 (1.00) · snare 120 hits (0.63) | omlead, snare = **8118 B** |

Mean simultaneously sounding voices: song1 3.2, song2 3.3, song3 3.2, song4 3.6; peak 4 [M].
Note data of all songs: 2570 B [H]. Pattern structure: 17 / 13 / 29 / 15 track-list entries per track, 2–9 distinct patterns.

Playback rates the samples are stepped at (= 3579545 / period) [H]:
| instrument | notes used | rate range |
|---|---|---|
| SyntheBass | F5..D#6 (written; sounding pitch depends on the waveform) | 5.6–10.0 kHz |
| omlead | C3, C4, C5 only | 2.1 / 4.2 / 8.4 kHz |
| RoomBrass | G5..G6 (song1), A5..**G7** (song2), C6..C7 (song3) | 6.3–12.6 kHz; song2 up to **25.2 kHz**; song3 up to 16.8 kHz |
| kick, snare | C4 | 8.4 kHz (snare once at 1.8 kHz in song3) |
| Mech | C3 once | 4.2 kHz |

---------------------------------------------------------------------------------------------------
## 4. Port options for the STE

Given: mixer `game/snd.h` = 4 voices, 12517 Hz, stereo ring, ~56 cycles per output sample and voice ≈ **0.25 VBL per
continuously playing voice per 3-VBL frame** (= 8.3 % of the CPU per voice); mix is called from the main loop once per frame.

### (a) Original samples through the DMA mixer
| item | value | |
|---|---|---|
| voices | 4 tracks → 4 mixer voices, same L/R split as now (0+3 left, 1+2 right) | [H] |
| CPU | mean 3.2–3.6 voices → **0.80–0.91 VBL per 3-VBL frame = 27–30 % of the CPU**; peak 4 voices 1.0 VBL (33 %) | [M] |
| CPU at 6258 Hz | half: 13–15 %; but the brass runs at 6–25 kHz source rate → audible aliasing/dullness | [M] |
| memory | samples 35.3 KB (per song 8–24 KB) + note data 2.6 KB + sequencer code; the DATA hunk could be shipped as is (39 KB) | [H] |
| sequencer | port of §2.3: ~150 lines C; run it in the sample domain inside the mix call (1 tick = 12517/49.5 = 253 samples, 271 for song1) – no extra timer, exact tempo | [M] |
| mixer changes | loop start/length per voice (now a loop restarts at 0); tie/hold; volume 30/32 fits the table (vol>>1); samples < 32 K ok; step up to 2.0 (brass G7) ok | [H from snd.h] |
| fidelity | all notes, timbres and stereo as on the Amiga; brass above ~12.5 kHz source rate aliases slightly (song2, bars with A6..G7) | [M] |
| risk | the mix runs in the main loop: every blocking phase (disk load of a picture, CPU-bound fades, the busy fade-wait) starves the ring after ≤ 14 VBLs → stutter, unless the menu code calls the mix in those loops or the mix moves into the VBL for menus. The intro scroller's own frame cost is not measured | [M] [?] |

### (b) Convert the note data to YM2149 chip music
| item | value | |
|---|---|---|
| conversion | straightforward: events → (period = 125000 / f, duration, gate); note range C3..G7 = YM periods 956..40, in range | [M] |
| size / CPU | ~3 KB data, player in the VBL, < 1 % CPU; plays through disk loads | [M] |
| voices | 4 tracks on 3 tone channels: song1/2 need brass + brass + bass + drums → drums as noise bursts stealing a channel (or the bass); song3 needs 3 drone octaves + brass → one drone dropped while the brass plays; song4 3 drones + snare → snare as noise on a drone channel | [M] |
| lost | all sample timbres (brass with a 6548-sample evolving loop, synth-bass attack, the "om" drone), real drums, the Mech effect, stereo (YM is mono), the 4th voice | [M] |
| tonal vs noise | tonal: SyntheBass, omlead, RoomBrass; noise/percussion: BassDrum3, sdrum1; effect: Mechanic1 (1 use) | [M] |
| tempo | 50 Hz VBL instead of 46.2 / 49.5 Hz → song1 8 % fast, others 1 % fast, unless a timer or tick skipping is used | [M] |

### (b') Hybrid: YM tones + DMA drums
Tracks 0–2 on YM A/B/C, track 3 on one mixer voice. Fits song1, 2, 4 exactly (track 3 = drums only, duty 0.62–0.64 →
≈ 0.16 VBL per 3-VBL frame ≈ 5 % CPU, 5 KB samples). Song3: track 3 is the brass melody (duty 0.27) → play it as a sample
too (+8.3 KB) or as a 4th tone by dropping a drone octave. Loses the tonal timbres, keeps drums and all notes [M].

### (c) Pre-rendered streams (one loop per song, DMA plays it directly, ~0 % CPU)
| song | seconds | 6258 Hz mono | 12517 Hz mono |
|---|---|---|---|
| song1 | 33.3 | **203 KB** | 407 KB |
| song2 | 23.3 | **142 KB** | 285 KB |
| song3 | 54.3 | **332 KB** | 664 KB |
| song4 | 27.2 | **166 KB** | 332 KB |
| total | 138 | **843 KB** | 1.69 MB |
Stereo doubles it. Free RAM after load is ~268 KB in Hatari (less on a real STE, notes in the port status) → song3 does
not fit, the set does not fit a 720 KB disk beside the game, and 6258 Hz loses everything above 3 kHz [M].

### Comparison
| | CPU | RAM | disk | fidelity |
|---|---|---|---|---|
| (a) mixer | 27–30 % (33 % peak) | ~38 KB | 39 KB | original, 4 voices, stereo |
| (b) YM | < 1 % | ~3 KB | ~3 KB | notes only, 3 voices, mono |
| (b') hybrid | ~5 % | ~8–16 KB | same | notes + real drums |
| (c) stream 6.25 kHz | ~0 % | 142–332 KB per song | 843 KB | original but dull, mono |

Recommendation [M]: **(a)**. The music only plays on menu screens without effects, the mixer and its 4 voices are
free there, the data is 39 KB and the result is the Amiga original. Open before committing: the frame cost of the intro
scroller and how the mix is kept fed during disk loads and fades (call it from those loops, or a VBL-driven mix in menus).
If that budget is not there, (b') is the fallback; (c) is ruled out by size.

---------------------------------------------------------------------------------------------------
## 5. Certain / inferred / open
* [H] formats, commands, duration table, period formula, instrument headers, song lengths in ticks, channel assignment,
  no vibrato/arpeggio/ADSR, fade behaviour, CIA-A timer A, music never together with effects, songplay effect API unused.
* [M] seconds and BPM (TALO taken as 0), duty and voice means, CPU and size estimates, instrument roles.
* [?] TALO latch value at run time (tempo ±1.7 %); how the songs sound (nothing was rendered or listened to; a
  Paula-accurate render from §2.3 would settle the aliasing question for 12.5 kHz); intro scroller frame budget on the STE.

---------------------------------------------------------------------------------------------------
## 6. Dump script
`python3 dump_wofsongs.py "amiga-original/wofsongs" [-v]`
(standard library only; `-v` lists every event). Prints the song table, per track: list entries, patterns, events,
ticks, instruments, note range, commands; then periods/rates per instrument and the 8SVX headers.

```python
#!/usr/bin/env python3
"""Dump songs / tracks / patterns / voices of Wings of Fury (Amiga) 'wofsongs'.
usage: dump_wofsongs.py <wofsongs> [-v]     (-v: print every pattern event)"""
import struct, sys
from collections import Counter

DUR = [(96,86),(48,43),(32,28),(64,58),(24,21),(72,64),(12,10),(84,75),(60,54),(36,32),
       (6,5),(90,81),(78,70),(66,59),(54,48),(42,38),(30,27),(18,16),(8,7),(16,14)]   # songplay DATA+0x254
NOTE = ['C','C#','D','D#','E','F','F#','G','G#','A','A#','B']
def nname(n): return '%s%d' % (NOTE[(n - 27) % 12], 4 + (n - 27) // 12)   # 27 = middle C (261.6 Hz)

def load(path):
    d = open(path, 'rb').read()
    u = lambda p: struct.unpack('>I', d[p:p+4])[0]
    assert u(0) == 0x3f3
    p, hunks, cur = 0x14 + 4 * (u(0x10) - u(0x0c) + 1), [], None
    while p < len(d):
        t = u(p) & 0x3fffffff; p += 4
        if t in (0x3e9, 0x3ea):
            n = u(p) * 4; p += 4
            cur = dict(data=bytearray(d[p:p+n]), rel=[], sym={}); hunks.append(cur); p += n
        elif t == 0x3eb:
            p += 4; cur = dict(data=bytearray(), rel=[], sym={}); hunks.append(cur)
        elif t == 0x3ec:
            while u(p):
                n, tg = u(p), u(p+4); p += 8
                cur['rel'] += [(u(p + 4*i), tg) for i in range(n)]; p += 4 * n
            p += 4
        elif t == 0x3f0:
            while u(p):
                n = u(p); p += 4
                cur['sym'][u(p + 4*n)] = d[p:p+4*n].rstrip(b'\0').decode(); p += 4*n + 4
            p += 4
        elif t == 0x3f2: pass
        else: break                       # 0x3f5 HUNK_OVERLAY trailer (empty)
    h = hunks[1]                          # DATA hunk; all its relocs point into itself -> base 0
    relocs = {o for o, tg in h['rel'] if tg == 1}
    return bytes(h['data']), relocs, h['sym']

def main():
    D, REL, SYM = load(sys.argv[1]); verbose = '-v' in sys.argv
    w = lambda p: struct.unpack('>H', D[p:p+2])[0]
    sw = lambda p: struct.unpack('>h', D[p:p+2])[0]
    l = lambda p: struct.unpack('>I', D[p:p+4])[0]
    name = lambda a: SYM.get(a, '%05x' % a)
    songs = [l(p) for p in range(0, l(0), 4)]
    print('songs[] =', [name(s) for s in songs])

    voices = {}; allnotes = {}
    def voice(a):
        if a in voices or a == 0: return
        f = l(a + 10); v = dict(addr=a, file=f)
        if f:
            q = f + 12; v['name'] = ''
            while q < f + 8 + l(f + 4):
                cid, n = D[q:q+4], l(q + 4)
                if cid == b'VHDR':
                    v.update(zip(('oneShot','repeat','sphc','rate','oct','comp','vol'),
                                 struct.unpack('>IIIHBBI', D[q+8:q+28])))
                elif cid == b'NAME': v['name'] = D[q+8:q+8+n].rstrip(b'\0').decode('latin1')
                elif cid == b'BODY': v['body'] = q + 8; v['bodylen'] = n
                q += 8 + n + (n & 1)
            v['filelen'] = 8 + l(f + 4)
        v['vib'] = [sw(a + o) for o in (18, 20, 22, 24, 26, 30)]
        v['arp'] = (w(a + 34), [sw(a + 36 + 2*i) for i in range(4)])
        voices[a] = v

    for si, s in enumerate(songs):
        if s in songs[:si]:
            print('\nsong index %d = %s (same as index %d)' % (si, name(s), songs.index(s))); continue
        vt = []; q = s + 16
        while True:                               # voice list: [0]=0 (rest), then pointers, 0-terminated
            a = l(q); vt.append(a); q += 4
            if a == 0 and len(vt) > 1: break
            voice(a)
        print('\nsong index %d = %s  voices: %s' % (si, name(s), [name(a) for a in vt[:-1]]))
        for t in range(4):
            tl = l(s + 4*t); e = 0; ticks = 0; used = Counter(); notes = Counter(); ins = 0
            cmds = Counter(); tempo = []; nev = 0; lo, hi = 999, -999; end = '?'; pats = []; vols = set()
            pat = l(tl); q = pat; pats.append((pat, sw(tl + 4)))
            while True:
                c, a = D[q], D[q+1]; q += 2
                if c < 0xd9:
                    n = (c & 0x7f) + sw(tl + e + 4); ln, gate = DUR[a]
                    ticks += ln; nev += 1
                    if l(vt[ins] + 10):
                        used[ins] += 1; lo, hi = min(lo, n), max(hi, n); allnotes.setdefault((si, vt[ins]), Counter())[n] += 1
                    if verbose: print('   %05x %s%-4s len %2d gate %2d %s' % (q-2, 'tie ' if c & 0x80 else '', nname(n), ln, gate, name(vt[ins]) if l(vt[ins] + 10) else 'rest'))
                elif c == 0xd9:
                    e += 6; pat = l(tl + e); q = pat; pats.append((pat, sw(tl + e + 4)))
                elif c == 0xda: end = 'end'; break
                elif c == 0xdb: end = 'loop'; break
                else:
                    cmds[c] += 1
                    if c == 0xdc: ins = a
                    if c == 0xdf: vols.add(a)
                    if c in (0xdd, 0xde): tempo.append((ticks, c, a))
                    if verbose: print('   %05x cmd %02x %d' % (q-2, c, a))
            print('  track %d list %05x: %d list entries, %d distinct patterns, %d events, %d ticks, %s; '
                  'instr use %s; note range %s..%s; cmds %s; vol %s; tempo %s' %
                  (t, tl, len(pats), len({a for a, _ in pats}), nev, ticks, end,
                   {name(vt[i]): n for i, n in used.items()},
                   nname(lo) if nev and lo < 999 else '-', nname(hi) if hi > -999 else '-',
                   {'%02x' % k: v for k, v in cmds.items()}, sorted(vols), sorted({('%02x' % c, a) for tk, c, a in tempo})))
    print('\nnotes per instrument (note xcount -> Paula period, Hz):')
    K = lambda n: round(3579545 / (261.6256 * 2 ** ((n - 27) / 12)))      # = songplay period table
    for a, v in sorted(voices.items()):
        if not v['file']: continue
        for (si, vi), cnt in sorted(allnotes.items()):
            if vi != a: continue
            out = []
            for n, c in sorted(cnt.items()):
                o = max(0, v['oct'] - n // (83 // v['oct']) - 1); per = K(n) // (v['sphc'] << o)
                out.append('%s x%d -> %d %.0f Hz' % (nname(n), c, per, 3579545 / per))
            print('  %-7s %-14s song%d: %s' % (name(a), v['name'], si + 1 if si < 3 else si, '; '.join(out)))
    print('\nvoices:')
    for a, v in sorted(voices.items()):
        if v['file']:
            tot = (v['oneShot'] + v['repeat']) * ((1 << v['oct']) - 1)
            print('  %-7s %-12s oneShot %5d repeat %5d sphc %2d rate %5d oct %d comp %d vol %5x body %5d (expect %d) file %5d  vib(up,down,step,speed,delay,on)=%s arp=%s'
                  % (name(a), v['name'], v['oneShot'], v['repeat'], v['sphc'], v['rate'], v['oct'], v['comp'], v['vol'], v['bodylen'], tot, v['filelen'], v['vib'], v['arp']))
        else: print('  %-7s (no sample)' % name(a))

main()
```
