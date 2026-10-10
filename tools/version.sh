#!/bin/sh
# Build identification: <VERSION>+<git short hash>[.dirty] <build date>, e.g. "0.3.0+3d78c39 2026-10-03".
#   VERSION (repo root) = semantic version: bump the minor for a feature milestone, the patch for fixes, and tag the
#   release commit vX.Y.Z. The hash names the exact source; ".dirty" = built from uncommitted changes.
D="$(cd "$(dirname "$0")/.." && pwd)"
V=$(cat "$D/VERSION" 2>/dev/null || echo 0.0.0)
H=$(git -C "$D" rev-parse --short=7 HEAD 2>/dev/null || echo nogit)
# (generated build inputs like flight_data.h change with the 200/240 variant: only source files count as dirty)
[ "$H" = nogit ] || git -C "$D" diff --quiet HEAD -- game/wof.cpp game/snd.h game/Makefile tools VERSION 2>/dev/null || H="$H.dirty"
echo "$V+$H $(date +%Y-%m-%d)"
