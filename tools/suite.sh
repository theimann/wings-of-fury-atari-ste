#!/usr/bin/env bash
# Regression suite: run replay tests against a snapshot of the current build, so the working build can be rebuilt
# (and other Hatari sessions used) while it runs.
# Usage: tools/suite.sh [-o results.txt] [test names...]     (default: every tests/*.txt marked below)
#   WOF_PROTO=<game dir> selects the branch's build (default: this checkout's game)
#   WOF_SUITE_DISK=<folder> tests another disk folder of it, WOF_SUITE_OUT=<name> puts the
#   results into tools/hplay_out/<name>/ instead of suite/
set -u
T="$(cd "$(dirname "$0")/.." && pwd)"
PROTO="${WOF_PROTO:-$T/game}"
OUT=""
if [ "${1:-}" = "-o" ]; then OUT="$2"; shift 2; fi
TESTS="$*"
[ -n "$TESTS" ] || TESTS="takeoff_fire high_alt bomb_hut_mini waves flags_deck bob_deck crash_sea crash_island crash_carrier crash_carrier_edge calib_cruise soldiers aa_guns gun_flash rockets rocket_path torpedo torpedo_roll help accel oil_turn elevator landing_elevator pillbox zeros ship_sink bomber carrier_sink carrier_gone maps_tour kill_tally map_wrap zero_left ceremony lamps frontend savegame"
SNAP="$T/tools/hplay_out/suite_disk_$$"
rm -rf "$SNAP"; mkdir -p "$SNAP"; cp -R "$PROTO/${WOF_SUITE_DISK:-disk1}/." "$SNAP/"
RES="${WOF_SUITE_OUT:-suite}"
pass=0; fail=0
for t in $TESTS; do
  r=$(WOF_PROTO="$PROTO" WOF_DISK="$SNAP" python3 "$T/tools/hatari_play.py" "$T/tests/$t.txt" "$T/tools/hplay_out/$RES/$t" --timeout 400 2>&1 | grep -E "EXPECT|result:" | tr '\n' ' ')
  line="$t: $r"; echo "$line"; [ -n "$OUT" ] && echo "$line" >> "$OUT"
  case "$r" in *"result: end"*) pass=$((pass+1));; *) fail=$((fail+1));; esac
done
rm -rf "$SNAP"
line="suite: $pass passed, $fail failed"; echo "$line"; [ -n "$OUT" ] && echo "$line" >> "$OUT"
[ "$fail" = 0 ]
