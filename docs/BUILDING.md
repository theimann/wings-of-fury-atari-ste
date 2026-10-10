# Building

The build runs on macOS and Linux. It was developed on a Mac (Apple Silicon; AGT's tools for macOS are x86_64 and
run under Rosetta).

## What you need

| | |
|---|---|
| AGT | [bitbucket.org/d_m_l/agtools](https://bitbucket.org/d_m_l/agtools), `master` at commit `a155d41`, with this repository's patch applied |
| Compiler | m68k-atari-mint GCC 4.6.4 with binutils, mintbin, MiNTLib and fdlibm, for example from [Thorsten Otto's cross tools](https://tho-otto.de/crossmint.php) |
| Python | Python 3 with Pillow |
| GNU make, bash | |
| Optional | `upx` (packs the floppy version's program), `zip`, [Hatari](https://www.hatari-emu.org/) 2.5 or newer and a TOS image (1.62 or 2.06) to run and test |

AGT's cutter, assembler (rmac) and packers come prebuilt in `agtools/bin/` for macOS, Linux and Windows.

## Set up

Put AGT beside this repository and apply the patch:

    git clone https://bitbucket.org/d_m_l/agtools.git
    cd agtools
    git checkout a155d41
    git apply --whitespace=nowarn ../wings-of-fury-atari-ste/agt-patch/agtools-local.patch
    cd ../wings-of-fury-atari-ste

The patch only changes files in `agtsys/`; [AGT_CHANGES.md](AGT_CHANGES.md) explains each change. AGT's files have
DOS line endings and so has the patch: apply it with `git apply`, not with a tool that converts line endings.

Python:

    python3 -m venv .venv
    .venv/bin/pip install -r requirements.txt

Where things are, if not in the default places (as environment variables, or in a file `local.env` in the
repository's root, which git ignores):

| Variable | Default | |
|---|---|---|
| `AGTROOT` | `../agtools` | the patched AGT |
| `CROSS_MINT` | `$HOME/cross-mint` if it exists, else AGT's `/opt/cross-mint` | the folder with `bin/m68k-atari-mint-gcc` |
| `PYTHON` | `.venv/bin/python`, else `python3` | |
| `WOF_BUILDS` | `builds/` | where releases are put |
| `HATARI` | `hatari` on the path, else the macOS application | |
| `WOF_TOS` | none | the TOS image for Hatari |

## Build

    cd game
    make

This cuts the graphics with AGT's `agtcut` (`assets_com.sh`, about a minute the first time), compiles AGT and the
game, and writes a disk folder `game/disk1/`: `AUTO/WOF.PRG` and the data files beside it. Run it in Hatari with
the folder as hard disk:

    WOF_TOS=/path/to/tos206.img tools/run_hatari.sh game/disk1

Other targets of the Makefile:

| | |
|---|---|
| `make play` | `disk1/WOFPLAY.PRG`, the build that replays a script of joystick input (for the tests) |
| `make diag` | `disk1/WOFDIAG.PRG`, a build with checks and debug output for real machines |
| `make hdiag` | the same for Hatari, output in Hatari's log |
| `make plain` | a build with a plain 200-line screen, without the split-screen code |
| `make MAPS="a b"` | only some of the 15 maps |

After a change of preprocessor defines or of `assets_com.sh`, remove `game/build*` and `game/cache` (make does
not track them).

## Releases

    tools/make_release.sh

builds `builds/release-<version>+<commit>/` with three targets:

| | |
|---|---|
| `floppy/wof.st` | a 720 KB disk image that boots into the game: data packed with ZX0, program packed with UPX |
| `harddisk/WOF/` | `WOF.PRG`, `DATA/`, `SAVE/`, unpacked, and a zip of it |
| `hatari/` | a drive folder with `AUTO/WOF.PRG` and the files beside it |

`README.TXT` (from `manual/README.TXT`, with the build's version line) is part of each. The first run packs all
level files, which takes about half an hour; the results are cached in `game/.pack_cache/`.

The version is `VERSION` plus the git commit (`tools/version.sh`); it is compiled into the program and shown by
Ctrl+V and on the pause page.

## Tests

The tests are scripts of joystick input (`tests/*.txt`) that a replay build plays in Hatari. A script can take
screenshots and state what must come out (the sequence of player states, the score).

    cd game && make play && cd ..
    WOF_TOS=/path/to/tos206.img tools/suite.sh takeoff_fire bomb_hut_mini     # some tests
    WOF_TOS=/path/to/tos206.img tools/suite.sh                               # the regression set, takes a while

Screenshots and logs go to `tools/hplay_out/suite/<test>/`. `tools/hatari_play.py` runs one script and has options
for sound and video recording; `tools/snapdiff.py` compares the screenshots of two runs. `WOF_MEMSIZE=2` runs with
2 MB. The script format is described at `WOF_REPLAY` in `game/wof.cpp`.

## The assets

Everything the build reads is in the repository, so the steps below are only needed after changing a tool.

    tools/regen_assets.sh

| From | Tool | To |
|---|---|---|
| `amiga-original/shapes/` | `tools/convert_gfx.py` | `amiga-graphics/`: every sprite frame as PNG, with hot spots and palettes |
| `amiga-original/wings` | `tools/hunk.py` | `reverse-engineering/wings.bin`: the program as a flat image, for the tables the tools read from it |
| maps, `amiga-graphics/`, `reverse-engineering/wings.bin` | `tools/make_proto_assets.py` | `game/source_assets/`: level pictures, map data, sprite sheets in the 16 colours; `game/flight_data.h` |
| `iff-dash`, `nightdash` | `tools/make_panel.py` | panel tiles and sprites, `game/fpv_data.h` |
| | `tools/make_font.py`, `make_tfont.py` | the help page and message line fonts |
| `amiga-original/sounds/` | `tools/make_sounds.py` | `game/snd_data.h` |
| pictures, font, songs | `tools/make_pics.py`, `make_intro.py`, `make_music.py` | start-up pictures, intro text and music (run by `assets_com.sh` at build time) |

`amiga-original/` holds the game's own files from the Amiga disk. The file formats are described in
[FORMATS.md](FORMATS.md).

## Real machines

`game/deploy_ste.sh` uploads a build to a [SidecarTridge Multi-device](https://sidecartridge.com/) cartridge
running md-devops and starts it (`SIDECART_HOST`, `SIDECART_CLI`). The cartridge's drive emulation rejects file
seeks; see [AGT_CHANGES.md](AGT_CHANGES.md) and [sidecartridge/](sidecartridge/).
