#!/usr/bin/env bash
# make_debug.sh : the debug folder for a Mega STE with an ATW800/2 card (docs/ATW_SCREEN_PLAN.md), from a clean
# commit, staged in game/dbg_stage/<build name>/ (tools/build_name.sh: 1.1.0+3536910 -> 3536910.110):
#   WOF.PRG       the game with the frame profile on the card (make atw)
#   SCRIPTED.PRG  every scripted run, one after another, no keys (make wofruns)
#   README.TXT  (game/README_DBG.TXT)
#   WOF.DAT     all data in one archive, as in the hard disk release (make_release.sh)
#   RUNS\         the run scripts and RUN.PRG, the run build SCRIPTED starts for each (make atwrun); the runs
#                 write their logs and saves here
set -e
cd "$(dirname "$0")/../game"
. ../tools/env.sh > /dev/null 2>&1; unset AGTROOT
[ -z "$(git status --porcelain --untracked-files=no)" ] || { echo "uncommitted changes: commit first (a clean build id)"; exit 1; }
PY="${PYTHON:-python3}"
rm -rf build_atw build_atwrun
(make && make atw && make runs && "$PY" ../tools/make_runs.py && make atwrun && make wofruns) > build_dbg.log 2>&1 || { tail -20 build_dbg.log; exit 1; }
ID="$(sed 's/#define WOF_VERSION "\([^ ]*\) .*/\1/' version.h)"
NAME="$(../tools/build_name.sh "$ID")"
S="dbg_stage/$NAME"; rm -rf dbg_stage; mkdir -p "$S/RUNS" dbg_stage/data
for f in disk1/*; do
  [ -f "$f" ] || continue
  case "$(basename "$f")" in *.PRG|*.prg|map.txt|MAP.TXT|replay.txt|REPLAY.TXT|HISCORE.DAT|README.TXT|SAVE?.WOF) ;; *) cp -p "$f" dbg_stage/data/ ;; esac
done
"$PY" ../tools/make_archive.py dbg_stage/data "$S/WOF.DAT" > /dev/null
rm -rf dbg_stage/data
cp disk1/WOFATW.PRG "$S/WOF.PRG"; cp disk1/SCRIPTED.PRG "$S/SCRIPTED.PRG"; cp disk1/WOFATWR.PRG "$S/RUNS/RUN.PRG"
cp README_DBG.TXT "$S/README.TXT"; cp runs/RUN*.TXT "$S/RUNS/"
echo "$ID $S"
