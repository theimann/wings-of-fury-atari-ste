#!/bin/sh
# readme.sh <destination file>: manual/README.TXT with the build's identification under the title (the line "@BUILD@"),
# e.g. "Version 0.9.0+9634964  2026-10-08", centred in the 38 columns. The id is the built program's (game/version.h).
D="$(cd "$(dirname "$0")/.." && pwd)"
ID=$(sed -n 's/#define WOF_VERSION "\(.*\)"/\1/p' "$D/game/version.h")
L="Version $(echo "$ID" | sed 's/ /  /')"
P=$(( (38 - ${#L}) / 2 )); [ $P -lt 0 ] && P=0
LINE="$(printf '%*s%s' $P '' "$L")"
grep -q '^@BUILD@' "$D/manual/README.TXT" || { echo "readme.sh: no @BUILD@ line in manual/README.TXT" >&2; exit 1; }
sed "s|^@BUILD@|$LINE|" "$D/manual/README.TXT" > "$1"
