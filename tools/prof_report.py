#!/usr/bin/env python3
"""Cycles per function from a Hatari CPU profile (tools/hatari_run.py --profile).

Usage: prof_report.py <outdir of hatari_run.py> [--build game/build_runs] [--top N] [--callers NAME]
       prof_report.py --symfile <file> [--build ...] [--text ADDR]: a symbol file for Hatari's debugger (`symbols`)
Hatari 2.6.1 writes the profile's disassembly lines to its standard output (hatari.txt), the header with
PROGRAM_TEXT to profile.txt. Symbols: the link map gives each object's .text address, nm gives the functions in it
(static ones too); a link address plus PROGRAM_TEXT (the program's TEXT start in RAM) is the address in RAM.
"""
import os, re, subprocess, sys, bisect, collections

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
NM = os.path.expanduser('~/cross-mint/bin/m68k-atari-mint-nm')
CXXFILT = os.path.expanduser('~/cross-mint/bin/m68k-atari-mint-c++filt')


def symbols(build):
    mp = open(os.path.join(build, 'wof.map')).read().splitlines()
    syms, first = [], None
    for l in mp:
        m = re.match(r'^ \.text\s+0x([0-9a-f]+)\s+0x([0-9a-f]+)\s+(\S+)$', l)
        if not m:
            continue
        base, size, obj = int(m.group(1), 16), int(m.group(2), 16), m.group(3)
        if first is None:
            first = base
        mm = re.match(r'(.*)\((.*)\)$', obj)
        path, member = (mm.group(1), mm.group(2)) if mm else (obj, None)
        path = os.path.join(os.path.dirname(build), path) if not os.path.isabs(path) else path
        if not os.path.exists(path):
            syms.append((base, os.path.basename(obj)))
            continue
        out = subprocess.run([NM, '-n', path], capture_output=True, text=True).stdout
        cur, got = None, False
        for ln in out.splitlines():
            if ln.endswith(':'):
                cur = ln[:-1]; continue
            if member and cur != member:
                continue
            p = ln.split()
            # (C objects: static functions too; assembler objects: only the global labels, their local ones
            # would split a routine)
            if len(p) == 3 and p[1] in ('tT' if obj.endswith('wof.o') else 'T') and not p[2].startswith('.'):
                a = int(p[0], 16)
                if a < size:
                    syms.append((base + a, p[2])); got = True
        if not got:
            syms.append((base, os.path.basename(obj)))
    syms.sort()
    names = sorted(set(n for _, n in syms))
    dem = subprocess.run([CXXFILT], input='\n'.join(n[1:] if n.startswith('__Z') else n for n in names),
                         capture_output=True, text=True).stdout.splitlines()
    nice = dict(zip(names, dem)) if len(dem) == len(names) else {}
    return [a for a, _ in syms], [nice.get(n, n) for _, n in syms], first


def main():
    a = sys.argv[1:]
    build, top = os.path.join(ROOT, 'game', 'build_runs'), 40
    if '--build' in a:
        i = a.index('--build'); build = os.path.abspath(a[i + 1]); del a[i:i + 2]
    if '--symfile' in a:		# (runtime addresses: TEXT is 0xceba in tools/hatari_run.py's set-up)
        i = a.index('--symfile'); f = a[i + 1]; del a[i:i + 2]
        text = 0xceba
        if '--text' in a:
            i = a.index('--text'); text = int(a[i + 1], 0); del a[i:i + 2]
        addrs, names, _ = symbols(build)
        open(f, 'w').write(''.join('%08x T %s\n' % (x + text, re.sub(r'[^A-Za-z0-9_.:]', '_', n)[:60])
                                   for x, n in zip(addrs, names)))
        return
    callers = None
    if '--callers' in a:
        i = a.index('--callers'); callers = a[i + 1]; del a[i:i + 2]
    if '--top' in a:
        i = a.index('--top'); top = int(a[i + 1]); del a[i:i + 2]
    out = a[0]
    text = None
    for l in open(os.path.join(out, 'profile.txt'), errors='replace'):
        m = re.match(r'PROGRAM_TEXT:\s+0x([0-9a-f]+)', l)
        if m:
            text = int(m.group(1), 16)
    addrs, names, first = symbols(build)
    rel = text
    per = collections.Counter()
    total = 0
    rx = re.compile(r'^([0-9a-f]{8}) .*% \((\d+), (\d+), \d+, \d+\)$')
    for l in open(os.path.join(out, 'hatari.txt'), errors='replace'):
        m = rx.match(l.rstrip())
        if not m:
            continue
        pc, cyc = int(m.group(1), 16), int(m.group(3))
        total += cyc
        if pc >= 0xe00000:
            per['(TOS ROM)'] += cyc; continue
        la = pc - rel
        if pc < text or la > addrs[-1] + 0x10000:
            per['(outside the program)'] += cyc; continue
        i = bisect.bisect_right(addrs, la) - 1
        per[names[i] if i >= 0 else '?'] += cyc
    print('total %.1f s of CPU (8 MHz), program TEXT at %06x' % (total / 8021247, text))
    if callers:		# Hatari's call lines (with symbols loaded): "<callee>: <caller> = <calls> <types> ..., <name>"
        for l in open(os.path.join(out, 'hatari.txt'), errors='replace'):
            if l.startswith('0x') and l.rstrip().endswith(callers):
                print(l.rstrip()[:400])
    for n, c in per.most_common(top):
        print('%6.2f%%  %8.2f s  %s' % (100.0 * c / total, c / 8021247, n[:110]))


if __name__ == '__main__':
    main()
