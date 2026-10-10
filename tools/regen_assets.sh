#!/usr/bin/env bash
# Rebuild everything that is derived from the Amiga files in amiga-original/: the decoded graphics (amiga-graphics/), the flat
# image of the program (reverse-engineering/wings.bin), the sprite sheets, level pictures and map data AGT's cutter reads
# (game/source_assets/) and the generated headers in game/. All of it is in git, so this is only needed after a
# change to a tool; `git status` afterwards shows what the change did.
# Usage: tools/regen_assets.sh [--unpacked]     (--unpacked also writes the shape files without their Rpck packing
#                                                to unpacked/, for inspection)
set -e
. "$(dirname "$0")/env.sh"
cd "$WOF_ROOT"
G="amiga-original"
PY="$PYTHON"
if [ "$1" = "--unpacked" ]; then
  mkdir -p unpacked
  for f in "$G"/shapes/*; do "$PY" tools/rpck.py "$f" "unpacked/$(basename "$f")"; done
fi
"$PY" tools/convert_gfx.py "$G/shapes" amiga-graphics > /dev/null
"$PY" tools/hunk.py "$G/wings" reverse-engineering/wings.bin > /dev/null
"$PY" tools/render_maps.py "$G/maps" reverse-engineering/wings.bin amiga-graphics/frames/world_shp amiga-graphics/maps > /dev/null
"$PY" tools/make_proto_assets.py "$G/maps" game/source_assets game/flight_data.h abcdefghijklmno > /dev/null
"$PY" tools/make_panel.py game/source_assets > /dev/null
"$PY" tools/make_font.py game/source_assets/level_a.png game/source_assets/font.png > /dev/null
"$PY" tools/make_tfont.py game/source_assets/sepbar.png game/source_assets/tfont.png > /dev/null
"$PY" tools/make_flash_sheet.py game > /dev/null
"$PY" tools/make_sounds.py game > /dev/null
echo "regenerated: amiga-graphics/, reverse-engineering/wings.bin, game/source_assets/, game/*_data.h (cut and build with: cd game && make)"
