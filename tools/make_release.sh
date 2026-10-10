#!/usr/bin/env bash
# Every target carries manual/README.TXT beside the program (the floppy: in its root).
# Build the release targets of the current source into builds/release-<version+commit>/ (WOF_BUILDS, tools/env.sh):
#   hatari/      unpacked disk folder (a GEMDOS drive for Hatari; AUTO/WOF.PRG starts at boot).
#                The same files are what game/deploy_ste.sh uploads to a SidecarTridge cartridge.
#   floppy/      wof.st: one 720 KB disk image, assets packed (tools/pack_disk.py), program packed with UPX;
#                boots from the AUTO folder (Gotek, emulators, or written to a real disk). Same layout as the hard
#                disk version: the files in DATA/, an empty SAVE/ (the program has to be in AUTO/ to start by itself)
#   harddisk/    WOF/ folder: WOF.PRG, the unpacked files in DATA/ (nothing to unpack: quickest to load), an empty
#                SAVE/ for saved games and high scores; and a zip of it
# Usage: tools/make_release.sh [--no-upx]
set -e
. "$(dirname "$0")/env.sh"
T="$WOF_ROOT"; PY="$PYTHON"
cd "$T/game"
DISK=disk1; REL=disk_rel; SUF=""; UPX=1
for a in "$@"; do case "$a" in --no-upx) UPX=0 ;; esac; done
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
mkdir -p "$OUT/stage/DATA" "$OUT/stage/SAVE"
copy_data $REL "$OUT/stage/DATA"
cp "$PRG" "$OUT/stage/AUTO/WOF.PRG"; rm "$PRG"
../tools/readme.sh "$OUT/stage/README.TXT"
"$PY" ../tools/make_st.py "$OUT/stage" "$OUT/floppy/wof.st"
mkdir -p "$OUT/harddisk/WOF/DATA" "$OUT/harddisk/WOF/SAVE"
copy_data $DISK "$OUT/harddisk/WOF/DATA"
cp -p $DISK/auto/wof.prg "$OUT/harddisk/WOF/WOF.PRG"
../tools/readme.sh "$OUT/harddisk/WOF/README.TXT"
(cd "$OUT/harddisk" && zip -q -r "wof-$ID$SUF-hd.zip" WOF)
rm -rf "$OUT/stage"
if [ -z "$SUF" ]; then
ln -sfn "$OUT" "$WOF_BUILDS/release-current"
ln -sfn "$OUT/hatari" "$WOF_BUILDS/current"                  # the last release as a drive folder for Hatari
fi
echo "release $ID$SUF -> $OUT"
du -sk "$OUT/hatari" "$OUT/harddisk/WOF" | awk '{print "  " $1 " KB  " $2}'
ls -l "$OUT/floppy/wof.st" "$OUT/harddisk/"*.zip | awk '{print "  " int($5/1024) " KB  " $9}'
