#!/bin/bash
cd "$(dirname "$0")/../.."
for x in "$@"; do awk -v a="==== FUN_000$x @" 'index($0,a){p=1;print;next} /==== FUN_/{if(p)exit} p' wings_decomp.c; done
