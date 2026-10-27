#!/usr/bin/env python3
"""atw_late.py RUNn.LOG [wof.map [wof.o]] : the frame profile of a debug run (make atwrun; deploy_ste.sh --run=<n> --atw).
PROF lines (once a second: frames, each section's average) give each section's mean over the run; LATE lines (each
frame over the pacing: its VBLs, every section) show which section ran over, against that second's average, and by how
much. Counts are dbg_clock's: 26.04 us. With the build's map (game/build_atwrun/wof.map of the same build): LPC lines
(the PCs at the last six VBLs of each late frame) named by function, counted over all late frames; with the object
file too, the game's static functions (not in the map) by name as well."""
import re, sys, statistics
NAMES = ["input, pages", "logic ticks", "sound mix", "effects advance", "fx_build", "carrier bob, camera",
         "hud, panel build", "entity tick", "pre-draw", "view set-up", "bgrestore", "hybrid_fill", "overlays",
         "sprites", "panel restore", "fpv_draw", "panel items, swap", "pacing wait (idle)"]
US = 26.0417
prof, late, lpc = [], [], []
last = None
entry = None
for l in open(sys.argv[1], errors='replace'):
    f = l.split()
    if len(f) > 3 and f[2] == 'PROF':
        last = [int(x, 16) for x in f[4:4 + 18]]
        prof.append((int(f[3], 16), last))
    elif len(f) > 2 and f[2].startswith('entry') and 'at=' in l:
        entry = int(l.split('at=')[1].split()[0], 16)
    elif len(f) > 3 and f[2] == 'LPC':
        lpc.append([int(x, 16) for x in f[3:]])
    elif len(f) > 3 and f[2] == 'LATE':
        late.append((int(f[0], 16), int(f[3], 16), [int(x, 16) for x in f[4:4 + 18]], last))
if not prof:
    sys.exit('no PROF lines (not a debug run build?)')
w = sum(n for n, _ in prof)
print('%d seconds, %d frames; %d late frames' % (len(prof), w, len(late)))
print('\nsection               mean us   share of busy')
mean = [sum(n * a[k] for n, a in prof) / w for k in range(18)]
busy = sum(mean[:17])
for k in range(18):
    print('%-20s %8.0f   %5.1f %%' % (NAMES[k], mean[k] * US, 100 * mean[k] / busy if k < 17 else 0))
print('busy %.0f us a frame on average' % (busy * US))
if late:
    blame, over = {}, []
    for vbl, v, d, a in late:
        if a is None:
            continue
        ex = [(d[k] - a[k], k) for k in range(17)]
        e, k = max(ex)
        blame.setdefault(k, []).append(e)
        over.append((e * US, vbl, v, NAMES[k]))
    print('\nlate frames: the section furthest over its second\'s average')
    for k, es in sorted(blame.items(), key=lambda x: -len(x[1])):
        print('%-20s %3d times, over by %6.0f us median (%6.0f .. %6.0f)' % (NAMES[k], len(es), statistics.median(es) * US,
              min(es) * US, max(es) * US))
    print('\nby VBLs: ' + ', '.join('%d: %d' % (v, sum(1 for x in late if x[1] == v)) for v in sorted({x[1] for x in late})))
    print('\nthe 10 largest:')
    for e, vbl, v, n in sorted(over, reverse=True)[:10]:
        print('  at VBL %6d, %2d VBLs: %s +%.0f us' % (vbl, v, n, e))

if lpc and len(sys.argv) > 2 and entry is not None:
    import bisect, collections
    syms = []
    for l in open(sys.argv[2]):
        m = re.match(r'\s+0x([0-9a-f]+)\s+(_\S+)\s*$', l)
        if m:
            syms.append((int(m.group(1), 16), m.group(2)))
    if len(sys.argv) > 3:                       # the object's own symbols (static functions), at its .text in the map
        import subprocess, os
        obj = sys.argv[3]
        tb = None
        for l in open(sys.argv[2]):
            m = re.match(r'\s*\.text\s+0x([0-9a-f]+)\s+0x[0-9a-f]+\s+\S*/wof\.o\s*$', l)
            if m:
                tb = int(m.group(1), 16)
        od = os.path.expanduser('~/cross-mint/bin/m68k-atari-mint-objdump')
        for l in subprocess.run([od, '-t', obj], capture_output=True, text=True).stdout.splitlines():
            f = l.split()
            if tb is not None and len(f) >= 4 and '.text' in f and f[-1].startswith('_'):
                syms.append((tb + int(f[0], 16), f[-1]))
    syms.sort()
    base = dict((n, a) for a, n in syms).get('_AGT_EntryPoint')
    off = entry - base
    addrs = [a for a, _ in syms]
    def name(pc):
        i = bisect.bisect_right(addrs, pc - off) - 1
        return syms[i][1] if i >= 0 else '?'
    c = collections.Counter(name(pc) for row in lpc for pc in row)
    print('\nwhere the 68000 was at the VBLs of late frames (%d frames, %d samples):' % (len(lpc), sum(c.values())))
    for n, k in c.most_common(25):
        print('  %4d  %s' % (k, n))
