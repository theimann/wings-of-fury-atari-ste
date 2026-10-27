#!/usr/bin/env bash
# Build the game and run it on a real STE via SidecarTridge Multi-device + md-devops (Runner mode).
# SIDECART_CLI names md-devops' command line tool (default: sidecart.py on the PATH).
# Usage: ./deploy_ste.sh [--no-run] [--packed] [--from=<build folder>]      host: $SIDECART_HOST (default sidecart.local)
#   uploads the build (./disk1) to /WOF
#   ./deploy_ste.sh --run=<n>   the run build (make runs) with the scripted runs (game/runs) in /WOFRUN, run n started
#   --atw: the debug builds with the frame profile on an ATW800/2 card (make atw / atwrun): WOFATW.PRG beside the
#   game in /WOF and started; with --run=<n> the run build's ATW variant as /WOFRUN/WOFRUN.PRG
#   ./deploy_ste.sh --quit      ends the program running there (remote quit); --log=<n>: run n's log to stdout
set -e
. "$(dirname "$0")/../tools/env.sh"
cd "$(dirname "$0")"
SC="${SIDECART_CLI:-sidecart.py}"

DISK=disk1; REMOTE=/WOF; RUN=1; SND=0; RUNNR=""
API="http://${SIDECART_HOST:-sidecart.local}/api/v1"
busy() { curl -s --max-time 5 "$API/runner" | grep -q '"busy": *true'; }
quit_running() {       # the cartridge's remote quit (SIDECARTRIDGE.md; the runner says "not busy" right after the request)
  busy || return 0
  local path; path="$(curl -s --max-time 5 "$API/runner" | sed -n 's/.*"last_path": *"\([^"]*\)".*/\1/p')"
  case "$path" in /WOF/*|/WOFRUN/*) ;; *) echo "another program runs there ($path): not touching it"; exit 1 ;; esac
  echo "$path runs there: remote quit"
  curl -s --max-time 5 -X POST "$API/runner/adv/meminfo" > /dev/null || true
  sleep 3
  for i in $(seq 1 30); do busy || { echo "it has ended"; return 0; }; sleep 1; done
  echo "still running after 30 s (a build without the remote quit, or it hangs): quit it by hand"; exit 1
}
for a in "$@"; do
  case "$a" in
    --quit) quit_running; exit 0 ;;   # end the program running there (its run log is written as at the end)
    --run=*) RUNNR="${a#--run=}"; REMOTE=/WOFRUN ;;   # scripted run n (make runs, tools/make_runs.py) in /WOFRUN
    --log=*) exec curl -s --max-time 30 "$API/gemdrive/files/WOFRUN/RUNS/RUN${a#--log=}.LOG" ;;   # that run's log
    --no-run) RUN=0 ;;
    --atw) ATW=1 ;;                   # the ATW800/2 debug builds (make atw / make atwrun)
    --sound) SND=1 ;;                 # the sound build (make sound) is uploaded as WOF.PRG
    --from=*) DISK="${a#--from=}"; NOBUILD=1 ;;   # a built disk folder (builds/...): no rebuild
    --packed) DISK=disk_rel ;;        # the packed release disk (tools/pack_disk.py): 0.7 MB instead of 5.4
    --list) LIST=1 ;;                 # the deployments made to this cartridge and folder
    --back=*) BACK="${a#--back=}" ;;  # make an earlier deployment current again (and start it)
  esac
done
if [ -n "$LIST" ]; then SIDECART_CLI="$SC" exec python3 ../tools/cart_deploy.py list --remote $REMOTE; fi
if [ -n "$BACK" ]; then SIDECART_CLI="$SC" exec python3 ../tools/cart_deploy.py activate --remote $REMOTE "$BACK" $([ "$RUN" = 1 ] && echo "--run WOF.PRG"); fi
if [ -z "$NOBUILD" ]; then
  make > build.log 2>&1 || { tail -20 build.log; exit 1; }
fi
if [ -n "$RUNNR" ]; then
  make runs > build_runs.log 2>&1 || { tail -20 build_runs.log; exit 1; }
  python3 ../tools/make_runs.py > /dev/null
fi
if [ -n "$ATW" ]; then
  make $([ -n "$RUNNR" ] && echo atwrun || echo atw) > build_atw.log 2>&1 || { tail -20 build_atw.log; exit 1; }
fi
[ -d "$DISK" ] || { echo "$DISK missing"; exit 1; }
# The work is done by tools/cart_deploy.py: only files the card lacks are
# sent; files that are replaced go to the store /OLD/<folder> on the card by renaming, and an earlier deployment
# comes back from there without an upload (./deploy_ste.sh --list, --back=<n or build>). HISCORE.DAT on the card
# is never touched (it is not part of a deployment).
PRG=$DISK/auto/wof.prg
ID="$(sed 's/#define WOF_VERSION "\([^ ]*\) .*/\1/' version.h 2>/dev/null)"   # (the build id: version+commit)
[ -n "$NOBUILD" ] && ID="$(basename "$(cd "$DISK" && pwd -P)")"
[ "$SND" = 1 ] && ID="$ID sound"
ARGS=(--file "$PRG=WOF.PRG")
if [ -n "$RUNNR" ]; then
  ID="$ID runs"
  ARGS=(--file "$DISK/$([ -n "$ATW" ] && echo WOFATWR.PRG || echo WOFRUN.PRG)=WOFRUN.PRG")
  [ -n "$ATW" ] && ID="$ID atw"
  for f in runs/*.TXT; do ARGS+=(--file "$f=RUNS/$(basename "$f")"); done
fi
[ -f $DISK/WOFDIAG.PRG ] && [ -z "$RUNNR" ] && ARGS+=(--file "$DISK/WOFDIAG.PRG=WOFDIAG.PRG")
[ -n "$ATW" ] && [ -z "$RUNNR" ] && ARGS+=(--file "$DISK/WOFATW.PRG=WOFATW.PRG")
for f in $(cd $DISK && ls); do     # every data file of the disk folder (unpacked: assets; packed: bundles)
  [ -f "$DISK/$f" ] || continue
  case "$f" in *.PRG|*.prg|map.txt|MAP.TXT|replay.txt|REPLAY.TXT|HISCORE.DAT) continue ;; esac
  ARGS+=(--file "$DISK/$f=$(echo $f | tr a-z A-Z)")
done
HOSTA="${SIDECART_HOST:-sidecart.local}"
export SIDECART_CLI="${SC#python3 }"   # (cart_deploy.py takes the script path alone)
quit_running
python3 ../tools/cart_deploy.py deploy --remote $REMOTE --build "$ID" "${ARGS[@]}" --first $([ -n "$RUNNR" ] && echo WOFRUN.PRG || echo WOF.PRG) --seed ".deploy_cache/${HOSTA}$(echo $REMOTE | tr '/' '_')"
$SC gemdrive ls $REMOTE | tail -3
[ "$RUN" = 0 ] && exit 0
$SC runner cd $REMOTE
if [ -n "$RUNNR" ]; then
  curl -s --max-time 10 -X DELETE "$API/gemdrive/files/WOFRUN/RUNS/RUN$RUNNR.LOG" > /dev/null || true   # (no old log mistaken for the new one)
  $SC runner run WOFRUN.PRG RUN$RUNNR
else
  $SC runner run $([ -n "$ATW" ] && echo WOFATW.PRG || echo WOF.PRG)
fi
$SC runner status
