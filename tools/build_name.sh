#!/usr/bin/env bash
# build_name.sh <build id> : the build id as a folder name TOS can hold (8.3, capitals): the commit as the name,
# the version's digits as the extension. 0.1.0+d5b820b -> D5B820B.010 (for build folders on the
# Ataris' own disks, to keep track of versions there). A build from uncommitted sources
# (.dirty) gets an X in front of the commit, cut to 8: 0.1.0+d5b820b.dirty -> XD5B820B.010
id="$1"; ver="${id%%+*}"; rest="${id#*+}"; c="${rest%%.*}"
[ "$rest" != "${rest%.dirty}" ] && c="X$c"
printf '%s.%s\n' "$(printf '%s' "$c" | tr a-z A-Z | cut -c1-8)" "$(printf '%s' "$ver" | tr -d . | cut -c1-3)"
