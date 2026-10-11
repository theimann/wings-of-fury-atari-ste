#!/usr/bin/env bash
# Every target carries manual/README.TXT beside the program (the floppy: in its root).
# Build the release targets of the current source into builds/release-<version+commit>/ (WOF_BUILDS, tools/env.sh):
#   hatari/      unpacked disk folder (a GEMDOS drive for Hatari; AUTO/WOF.PRG starts at boot).
#                The same files are what game/deploy_ste.sh uploads to a SidecarTridge cartridge.
#   floppy/      wof.st: one 720 KB disk image: AUTO/WOF.PRG (packed with UPX), WOF.DAT (the packed assets of
#                tools/pack_disk.py in one archive), README.TXT; boots from the AUTO folder (Gotek, emulators, or
#                written to a real disk)
#   harddisk/    WOF/ folder: WOF.PRG, WOF.DAT (the unpacked files in one archive: nothing to unpack, quickest to
#                load), README.TXT; and a zip of it
# The game makes its SAVE folder itself. The archives (tools/make_archive.py) come out byte for byte the same as
# long as the assets do not change: their sums are kept in tools/archive.sums, and a release whose archive differs
# stops unless --new-data is given (which writes the new sums; commit the file).
# Usage: tools/make_release.sh [--no-upx] [--new-data]
set -e
. "$(dirname "$0")/env.sh"
T="$WOF_ROOT"; PY="$PYTHON"
cd "$T/game"
DISK=disk1; REL=disk_rel; SUF=""; UPX=1; NEWDATA=0
for a in "$@"; do case "$a" in --no-upx) UPX=0 ;; --new-data) NEWDATA=1 ;; esac; done
make > build.log 2>&1 || { tail -20 build.log; exit 1; }
ID=$(sed 's/#define WOF_VERSION "\([^ ]*\) .*/\1/' version.h)
OUT="$WOF_BUILDS/release-$ID$SUF"
rm -rf "$OUT"; mkdir -p "$OUT/hatari/AUTO" "$OUT/floppy" "$OUT/harddisk" "$OUT/stage/AUTO"

copy_data() {   # disk folder, destination: everything but programs and test files
  for f in "$1"/*; do
    [ -f "$f" ] || continue
    case "$(basename "$f")" in *.PRG|*.prg|map.txt|MAP.TXT|replay.txt|REPLAY.TXT|HISCORE.DAT|README.TXT|SAVE?.WOF) ;; *) cp -p "$f" "$2/" ;; esac
  done
}

# unpacked
copy_data $DISK "$OUT/hatari"
cp -p $DISK/auto/wof.prg "$OUT/hatari/AUTO/WOF.PRG"
../tools/readme.sh "$OUT/hatari/README.TXT"       # (README.TXT is part of every target)

# packed
"$PY" ../tools/pack_disk.py $DISK $REL 8 | tail -1
PRG="$OUT/stage/WOF.PRG"
cp $REL/auto/wof.prg "$PRG"
if [ "$UPX" = 1 ] && command -v upx > /dev/null; then upx -q --best "$PRG" > /dev/null; fi
mkdir -p "$OUT/data_f" "$OUT/data_h"
copy_data $REL "$OUT/data_f"
"$PY" ../tools/make_archive.py "$OUT/data_f" "$OUT/stage/WOF.DAT"
cp "$PRG" "$OUT/stage/AUTO/WOF.PRG"; rm "$PRG"
../tools/readme.sh "$OUT/stage/README.TXT"
"$PY" ../tools/make_st.py "$OUT/stage" "$OUT/floppy/wof.st"
mkdir -p "$OUT/harddisk/WOF"
copy_data $DISK "$OUT/data_h"
"$PY" ../tools/make_archive.py "$OUT/data_h" "$OUT/harddisk/WOF/WOF.DAT"
cp -p $DISK/auto/wof.prg "$OUT/harddisk/WOF/WOF.PRG"
../tools/readme.sh "$OUT/harddisk/WOF/README.TXT"
# the archives against the recorded ones
SUMS=../tools/archive.sums
NOW="harddisk $(shasum -a 256 "$OUT/harddisk/WOF/WOF.DAT" | cut -d' ' -f1)
floppy $(shasum -a 256 "$OUT/stage/WOF.DAT" | cut -d' ' -f1)"
if [ "$NEWDATA" = 1 ]; then echo "$NOW" > $SUMS; echo "data archives: NEW (tools/archive.sums written)"
elif [ "$NOW" = "$(cat $SUMS 2>/dev/null)" ]; then echo "data archives: same as recorded"
else echo "data archives differ from tools/archive.sums:"; echo "$NOW"; echo "(assets changed? then run again with --new-data)"; rm -rf "$OUT"; exit 1; fi
find "$OUT/harddisk/WOF" -exec touch -t 202210041200 {} +       # (the zip: the same bytes for the same files)
(cd "$OUT/harddisk" && zip -q -X -r "wof-$ID$SUF-hd.zip" WOF)
rm -rf "$OUT/stage" "$OUT/data_f" "$OUT/data_h"
if [ -z "$SUF" ]; then
ln -sfn "$OUT" "$WOF_BUILDS/release-current"
ln -sfn "$OUT/hatari" "$WOF_BUILDS/current"                  # the last release as a drive folder for Hatari
fi
echo "release $ID$SUF -> $OUT"
du -sk "$OUT/hatari" "$OUT/harddisk/WOF" | awk '{print "  " $1 " KB  " $2}'
ls -l "$OUT/floppy/wof.st" "$OUT/harddisk/"*.zip | awk '{print "  " int($5/1024) " KB  " $9}'
