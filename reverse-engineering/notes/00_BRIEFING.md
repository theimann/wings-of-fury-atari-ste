# Wings of Fury (Amiga, Broderbund 1990) – reverse-engineering briefing

Goal: understand the game logic well enough to re-implement it in C on the Atari STE (AGT engine).
We need exact behaviour (constants, formulas, state machines, timings), not just a vague description.

## Files (all under `reverse-engineering/`)
- `wings.bin` – relocated flat image of the exe: CODE 0x10000-0x22f4b, DATA 0x22f50-0x27f3f.
- `wings_raw.s` – objdump disassembly of CODE (m68k syntax, `%a4@(-N)` = small-data global).
- `wings_decomp.c` – Ghidra decompile of all 743 functions, headed `// ==== FUN_xxxxxxxx @ xxxxxxxx ====`.
  Globals appear as `DAT_000xxxxx` (absolute address = A4 + offset).
- `calls.json` – call graph {caller: [callees]} with jump-table calls resolved (Ghidra's own graph misses these).
- `callgraph.jsonl` – per function: size, strings, globals referenced (r/w).
- `../amiga-original/` – game files; `../amiga-graphics/` decoded graphics; `../README.md` file formats.
- Useful: `awk '/==== FUN_000XXXXX @/{p=1} /==== FUN_/{if(p&&!/XXXXX/)exit} p' wings_decomp.c` to print one function,
  `grep -n 'DAT_00025312' wings_decomp.c` to find all users of a global.

## Compiler facts
- Aztec/Manx C, small data model: **A4 = 0x2af4e**. `%a4@(-N)` → address 0x2af4e-N.
- Calls via 185-entry jump table at 0x22f50 (`jsr %a4@(-N)` → `jmp abs` → real target). Ghidra shows these as `(*_thunk_FUN_xxx)()`.
- Many functions take args in registers (a0/a1/d0/d1) — Ghidra shows `in_A0`, `extraout_D0` etc.; check `wings_raw.s` when unclear.
- AmigaOS calls: `(**(code **)(base + -0x1e))()` = library vector offsets (e.g. dos Open -30, Read -42, Close -36).

## Known facts so far
- main = FUN_00010006. Per-frame loop: FUN_0001ccf6 (bookkeeping), FUN_00010228 (game update), FUN_000114d8→FUN_00011386 (render).
- VBL interrupt server = FUN_00011754 (installed by FUN_00012910). Sound FX interrupt handler near 0x1e8b8 ("SoundFX_IntHandler").
- Map/level: loader FUN_00012adc, parser FUN_00012d5a; map buffer ptr DAT_00024578, end DAT_0002457c, size DAT_00025316.
  Cells u16, 1 cell = 8 world px: bit15 anchor, bits13-11 y-jitter, bits10-2 type (index into world shape-name list at 0x23e34:
  0 barf,1 bchl,2 bchr,3 dugo(bunker),4 huta(hut),5 hutb,6-8 tre1-3,9 bumb,10 LIVE,11 cama, 0x0f-0x1e pila..pilp (pillbox/AA),
  0x1f fcar,0x20 mcar,0x21 rcar,0x22 towr,0x23 fgun,0x24 rgun,0x25 elev,0x26 Cpln,0x27 hook ...), bits1-0 surface (0 sea,1 carrier,2 island).
  Ships: 0xCC transport(1000HP) 0xE4-E7 destroyer(2500) 0x10C-110 battleship(4500) 0xF1-F6 J-carrier(6000). 0x113 one per island, 0x114/0x115 zone pairs.
- Rank/mission: DAT_0002530e rank?, DAT_00025310 mission-in-rank?; map table at 0x2545c (15 maps), rank start table 0x235a0 (a,d,g,i,k,l,m). Ranks: Midshipman..Captain.
- Object height fn FUN_00015710 (table at 0x25712).
- Shape name lists in DATA (0x23b60.. 0x24270): hellcat frames (hc01.. etc.), world list, 3D/dash list. Frames: see ../amiga-graphics/frames/*/_frames.json.
- Strings: "Island has %d soldiers and %d pillboxes", "All enemy forces on island have been destroyed", "%s sunk . . . BONUS %ld points",
  ranks list, "Crashed in the main task".

## Deliverables (per subsystem agent)
1. `notes/<area>.md` – precise spec: state variables (address → meaning, units), per-frame algorithm, constants, tables (dump them
   from wings.bin with python if needed), state machines, inputs, interactions with other subsystems. Note confidence levels.
2. `names/<area>.json` – {"functions": {"0x10f88": "player_update_physics", ...}, "globals": {"0x25312": "mission_over_flag", ...}}
   Only names you are reasonably confident about; lowercase_snake_case.
Do NOT modify any other files. Work read-only on the sources. Python is available as `python3`.
