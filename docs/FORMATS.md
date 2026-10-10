# The Amiga version's files

`amiga-original/` holds the game's files as they are on the Amiga disk. The decoders are in
`tools/` (`rpck.py`, `ppkc.py`, `iff.py`, `hunk.py`).

## Graphics

- **Rpck**: `'Rpck'`, u32 unpacked size, then PackBits with the sense inverted (c >= 0x80: copy 256-c literal
  bytes; else repeat the next byte c+1 times). Most files in `shapes/` are packed this way.
- **PPkc** shape bank: `'PPkc'`, u16 count, 4-character names, u32 offsets. Frame header (20 bytes): width in
  bytes, height, hot spot x and y, source x and y (u16/s16), `clear_planes` (u8), `set_planes` (u8), `plane_map[6]`
  (0-terminated). The stored planes follow one after the other and *replace* the destination plane bits named by
  `plane_map` (0x18 = planes 3 and 4) under the mask, which is the OR of the stored planes; `clear_planes` and
  `set_planes` force destination planes to 0 or 1 under the mask. Frames with width_bytes x height > 1040 are
  drawn opaque, which is why the large ship frames contain sky.
- **CMAP files** (`*.p`, `wingspalette`): `'CMAP'`, a 4-byte id, 32 RGB triples (12-bit Amiga colours, the same
  depth as the STE's).
- **IFF ILBM**: standard (ByteRun1). `iff-dash`, `hiscoreslab` and `rank.iff` are 640 pixels wide (hires).

`tools/convert_gfx.py` writes everything to `amiga-graphics/`: previews, contact sheets, `palettes.json`, and
`frames/<bank>/*.png` with `_frames.json`.

## Maps (`maps/a.map` to `o.map`)

Header: u32 file size, u32 byte offset of the carrier's home cell (cell = offset / 2). Then u16 cells to the end
of the file; **one cell is 8 world pixels**.

Cell bits: 15 object anchor, 13..11 vertical jitter 0-7, 10..2 type, 1..0 surface (0 sea, 1 carrier deck,
2 island).

The type is an index into the list of world shape names in the program (at 0x23e34: barf, bchl, bchr, dugo, huta,
hutb, tre1-3, bumb, LIVE, cama, ..., pila-pilp = 0x0F-0x1E, fcar ... hook = 0x1F-0x27). Markers without a
picture: barf, bumb, LIVE, 0x111/0x112 (carrier ends), 0x113 (one per island), 0x114/0x115 (zone pairs). Ships:
0xCC transport (1000 hit points), 0xE4-E7 destroyer (2500), 0x10C-110 battleship (4500), 0xF1-F6 Japanese carrier
(6000).

The first map of each rank comes from a table in the program: a d g i k l m. Previews of all maps are in
`amiga-graphics/maps/` (`tools/render_maps.py`).

## Sound

- `sounds/`: raw signed 8-bit samples without header.
- `wofsongs`, `songplay`: the menu music, four songs with six 8SVX instruments, and its player. See
  `reverse-engineering/notes/music.md`.

## The program

`wings` is an AmigaDOS hunk executable. `tools/hunk.py` loads it to a flat relocated image, `reverse-engineering/wings.bin` (code
at 0x10000, data at 0x22f50). It was compiled with an Aztec/Manx-style C compiler: small data with base register
A4 = 0x2af4e, calls through a table of 185 `jmp` entries at 0x22f50.

`reverse-engineering/` holds the disassembly (`wings_raw.s`), the Ghidra decompilation of all 743 functions (`wings_decomp.c`, with
names applied: `wings_named.c`), the call graph, the names (`names/`), the Ghidra scripts, and the notes that
specify each subsystem (`reverse-engineering/notes/`): player and flight, enemies, weapons and missions, rendering and sound, front
end, forward view, music. Addresses in the game's source comments (`FUN_1d796`, `[25366]`) refer to this image.
