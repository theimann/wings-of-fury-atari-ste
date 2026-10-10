# Changes to AGT

The game is built on [AGT](https://bitbucket.org/d_m_l/agtools) (Atari Game Tools) by dml. AGT is used almost as it
comes; the port needed the changes below. They are in `agt-patch/agtools-local.patch`, a diff against AGT's
`master` at commit `a155d41` (10 August 2026). It touches only `agtsys/`. How to apply it is in
[BUILDING.md](BUILDING.md).

Most of the changes were found on real machines (a 1040 STE and a Mega STE), where the display and sound hardware
behaved differently from Hatari. In the sources the changes are marked `[wof]` or `local patch`.

## Display (STE)

### Split screen on the standard display
`m68k/ste/dispxs.s`, `AGT_CONFIG_NICKEL_NOTOP`.

AGT's split-screen mode is made for a taller picture and starts an upper timer in every frame, also for a picture
of 200 lines. With this define that timer is never started and the 50/60 Hz register is not written: the display
is the machine's standard one. The first port then has to be on screen from the first display line, earlier than
any Timer B event can come, so the VBL sets it (screen address, scroll and line width, the same registers in the
same order as AGT's plain 200-line mode) and steps to the next port. The event list starts with a port at line 0
and ends with `NE_End` at line 200 (`NE_Stop` waits for display lines that do not come after the last one).

### Timer C is masked while the display runs
`m68k/ste/display.s`: `mask_timerc = 1`.

Timer C drives the 200 Hz system clock. Its interrupt would delay the Timer B events that time the split, so it is
masked while the display service is installed, and the clock is counted from the vertical blank instead. AGT has
both pieces already, tied to another switch; they now have a switch of their own. See "The 200 Hz clock" below.

### The 200 Hz clock keeps counting while files load
`m68k/ste/display.s`: macro `hz200_from_vbl`, used in `displayservice_ste_vbi_dmasafe`.

With Timer C masked, AGT's VBL routines add 4 to `_hz_200` (`$4ba`) per frame. The routine that runs while files
are loaded (`displayservice_ste_vbi_dmasafe`, selected while the DMA flag is set) did not, so the clock stood still
exactly during disk access. Hard disk drivers that time their waits with this clock never returned from the next
read: HDDRIVER does so on every access, and the game showed a black screen at the first load. The disk-safe routine
now counts the clock like the others.

### A plain screen while files load
`m68k/ste/display.s`: `g_dmasafe_screen`.

The disk-safe VBL routine runs no raster splits. A game with a split screen (playfield above, panel below) then
shows its playfield buffer over the whole screen, with stale rows below the playfield. In Hatari
with a GEMDOS drive this lasts one frame per file; from a floppy it lasts seconds. If `g_dmasafe_screen` is not
zero, the disk-safe routine shows that plain 320x200 screen instead. The game points it at its loading screen.

### The colours of a compiled colour burst can be changed
`shifter_ste.cpp`: `g_nickel_last_burst`.

The panel's palette is set by a Nickel `NE_ColourBurst`. Rebuilding the Nickel list at run time
(`load_nickel`) costs a frame with a broken split. The patch exposes the colour words of the last compiled burst
(pairs of opcode, colour, colour), so the game can change them in place (day and night panel, fades).

### The start resolution and palette are recorded
`os.c`: `g_agt_start_rez`, `g_agt_start_pal`.

`AGT_EntryPointPre` switches to medium resolution and changes colours before the program's own entry point runs,
so the program cannot find out how it was started. The patch records the resolution and the 16 palette words
first. On exit the game restores them; without this, quitting a game started from a low resolution desktop
returned to a medium resolution desktop with wrong colours.

## Memory

### A zone for level data
`ealloc.cpp`, `ealloc.h`: `ealloc_zone(base, size)`.

The game has 15 maps and loads one at a time into a 2 MB machine. Allocating and freeing each level's tiles, map
and tables with GEMDOS `Malloc` fragments the heap until a later level no longer fits. While a zone is set,
`ealloc()` takes memory from it by bump allocation; `efree()` ignores such blocks; the owner frees everything by
setting the zone again. The game allocates one block for level data at start-up and resets it before each load.

### Maps can be switched after start-up
`arena.h`: `arena::remap(map)`; `playfield.h`: `remap()` of a field; `worldmap.h`, `tileset.h`: `purge()` public.

AGT sets a playfield's map in `init()`, which also allocates the display buffers. `remap()` takes over a new
map's pointers and re-sizes the per-map dirty and occlusion tables without touching the buffers. `purge()` is made
public so that the old map and tiles can be freed first.

### Tables are reused
`playfield.h`: the occlusion map, the dirty masks and the map context's multiplication and modulo tables keep
their allocation when a later `allocate()` or `prepare()` needs the same size or less. Without this every map
switch freed and allocated them again around the level data.

### Less padding below the map
`worldmap.cpp`: `AGT_CONFIG_WORLDMAP_POSTPAD=n`.

For a vertically scrolling map AGT appends a full viewport of rows below the map (19 rows here). The game never
scrolls past the map's last row and sets the padding to 2 rows, which saves 4 bytes per cell of 17 rows on maps
several thousand cells wide.

## Files

### Seeking is emulated where the drive rejects it
`libcxx/zerolibc.cpp`.

The SidecarTridge Multi-device's drive emulation (GEMDRIVE of md-devops 1.1.0) fails every `Fseek()` with -37.
AGT's loaders read a header, seek to the end for the size and seek back; on that drive every asset then loaded
shifted. `FILE*` is now a small record (handle, path, position, size) instead of the bare GEMDOS handle. When
`Fseek()` fails, the size comes from `Fsfirst()` and a reposition is done by reopening the file and reading
forward. On drives where `Fseek()` works nothing changes. The fault is described in
[sidecartridge/fseek-issue.md](sidecartridge/fseek-issue.md), with a test program.

### A set of files read as one block
`libcxx/zerolibc.cpp`: `g_zl_bundle`.

From a floppy each open and read of a small file costs 3 to 4 seconds. If `g_zl_bundle` points to a block in
memory (a count, then name, offset and size per entry, then the data), `fopen()` for reading looks there first and
`fread()` copies from memory. The packed floppy version reads its small files as `START.BIN` and one `LVL_x.BIN`
per map (`tools/pack_disk.py` builds them).

### Packed maps are unpacked in place
`worldmap.cpp`: `load_ccm`; `compress.cpp`, `compress.h`: `unwrap_data()`.

AGT can load packed ("wrapped") assets, but a map would be unpacked into a second block and copied. After the
8-byte `.ccm` header the file may now hold a wrapped body; it is read into scratch memory and unpacked straight
into the map. Maps pack about 50:1 with ZX0.

## Not in the patch

- `makedefs.mintgcc` names `/opt/cross-mint` as the compiler's place. The game's `Makefile` overrides this from
  `CROSS_MINT` instead of changing AGT.
- A fault that is worked around in the game, not fixed in AGT: an IMSPR sprite entity in the same draw layer as
  EMX entities, or drawn last in a pass, makes the following EMX drawing crash. The game keeps all IMSPR entities
  in layer 1 and always draws an EMX entity (the separator bar) last.
