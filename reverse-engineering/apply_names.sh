#!/usr/bin/env bash
# Merge names/*.json, apply to the Ghidra project and re-export decompile + call graph.
set -e
cd "$(dirname "$0")"
python3 - <<'PY'
import json, glob
merged = {"functions": {}, "globals": {}}
for fn in sorted(glob.glob('names/*.json')):
    d = json.load(open(fn))
    for sec in merged:
        for k, v in d.get(sec, {}).items():
            k = hex(int(k, 16))
            if k in merged[sec] and merged[sec][k] != v:
                print(f'conflict {sec} {k}: {merged[sec][k]} vs {v} ({fn}) - keeping first')
                continue
            merged[sec][k] = v
json.dump(merged, open('names_merged.json', 'w'), indent=1)
print(len(merged['functions']), 'functions,', len(merged['globals']), 'globals')
PY
# GHIDRA_HOME: the Ghidra installation (12.1 was used); JAVA_HOME: a JDK 21
G=${GHIDRA_HOME:?set GHIDRA_HOME to the Ghidra folder}
$G/support/analyzeHeadless "$PWD/ghidra_proj" wings -process wings.bin -noanalysis -scriptPath "$PWD/ghidra_scripts" \
  -postScript ApplyNames.java "$PWD/names_merged.json" \
  -postScript ExportDecomp.java "$PWD/wings_named.c" > ghidra_names.log 2>&1
grep -E 'applied|ERROR' ghidra_names.log || true
