#!/usr/bin/env bash
# Usage: tools/run_hatari.sh <folder to mount as drive C:> [more Hatari options]
# Starts an STE (4 MB, colour monitor) in Hatari with the folder as GEMDOS drive C:; a program in its AUTO folder
# starts at boot. WOF_TOS must name a TOS image (1.62 or 2.06).
#   HATARI_FIFO   control fifo (default: hatari.fifo in tools/hplay_out), e.g. echo "hatari-shortcut screenshot" > fifo
#   HATARI_SHOTS  folder for screenshots;  HATARI_CFG  a configuration file to use
. "$(dirname "$0")/env.sh"
DIR="${1:-.}"; shift
[ -f "${WOF_TOS:-}" ] || { echo "run_hatari.sh: set WOF_TOS to a TOS image (TOS 1.62 or 2.06 for the STE)" >&2; exit 1; }
W="$WOF_ROOT/tools/hplay_out"
FIFO="${HATARI_FIFO:-$W/hatari.fifo}"; SHOTS="${HATARI_SHOTS:-$W/screenshots}"
mkdir -p "$SHOTS" "$(dirname "$FIFO")"; rm -f "$FIFO"
CFG=(); [ -n "${HATARI_CFG:-}" ] && CFG=(-c "$HATARI_CFG")   # (a configuration file must come first)
exec "$HATARI" "${CFG[@]}" --machine ste --monitor rgb \
  --tos "$WOF_TOS" --memsize 4 --harddrive "$DIR" \
  --fast-boot on --confirm-quit no --natfeats on \
  --screenshot-dir "$SHOTS" --screenshot-format png \
  --cmd-fifo "$FIFO" "$@"
