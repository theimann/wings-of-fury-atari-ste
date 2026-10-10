#!/usr/bin/env bash
# Build the game and run it on a real STE via SidecarTridge Multi-device + md-devops (Runner mode).
# SIDECART_CLI names md-devops' command line tool (default: sidecart.py on the PATH).
# Usage: ./deploy_ste.sh [--no-run] [--packed] [--from=<build folder>]      host: $SIDECART_HOST (default sidecart.local)
#   uploads the build (./disk1) to /WOF
set -e
. "$(dirname "$0")/../tools/env.sh"
cd "$(dirname "$0")"
SC="${SIDECART_CLI:-sidecart.py}"

DISK=disk1; REMOTE=/WOF; RUN=1; SND=0
for a in "$@"; do
  case "$a" in
    --no-run) RUN=0 ;;
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
[ -f $DISK/WOFDIAG.PRG ] && ARGS+=(--file "$DISK/WOFDIAG.PRG=WOFDIAG.PRG")
for f in $(cd $DISK && ls); do     # every data file of the disk folder (unpacked: assets; packed: bundles)
  [ -f "$DISK/$f" ] || continue
  case "$f" in *.PRG|*.prg|map.txt|MAP.TXT|replay.txt|REPLAY.TXT|HISCORE.DAT) continue ;; esac
  ARGS+=(--file "$DISK/$f=$(echo $f | tr a-z A-Z)")
done
HOSTA="${SIDECART_HOST:-sidecart.local}"
export SIDECART_CLI="${SC#python3 }"   # (cart_deploy.py takes the script path alone)
python3 ../tools/cart_deploy.py deploy --remote $REMOTE --build "$ID" "${ARGS[@]}" --first WOF.PRG --seed ".deploy_cache/${HOSTA}$(echo $REMOTE | tr '/' '_')"
$SC gemdrive ls $REMOTE | tail -3
[ "$RUN" = 0 ] && exit 0
$SC runner cd $REMOTE
$SC runner run WOF.PRG
$SC runner status
