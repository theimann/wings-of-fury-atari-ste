#!/bin/bash
# usage: fa.sh hexaddr  -> raw asm of function
cd "$(dirname "$0")/../.."
python3 - "$1" <<'P'
import sys,re,bisect
a=int(sys.argv[1],16)
funcs=sorted(int(m,16) for m in re.findall(r'==== FUN_([0-9a-f]+) @',open('wings_decomp.c').read()))
i=bisect.bisect_right(funcs,a)
end=funcs[i] if i<len(funcs) else 0x30000
for l in open('wings_raw.s'):
    m=re.match(r'\s*([0-9a-f]+):',l)
    if m:
        x=int(m.group(1),16)
        if a<=x<end: print(l.rstrip())
P
