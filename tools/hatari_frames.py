#!/usr/bin/env python3
"""Time every drawn frame of a scripted run, section by section, in Hatari (cycle-exact, 8 MHz STE).

Usage: hatari_frames.py <run script> <outdir> [--text ADDR] [--frames]
  make prof first (disk1/WOFPROF.PRG: the run build with PMARK(n) section markers in the main loop, game/wof.cpp).
  Every marker gets a tracing breakpoint that prints its number, the VBL and the cycle within the frame; a frame goes
  from marker 0 (after the pacing wait) to the next marker 0. Report (<outdir>/frames.txt): the sections' average
  cost in frames on time and in late frames (longer than 3 VBLs), and the 40 most expensive frames.
  --text: the program's TEXT start in Hatari's RAM (default 0xceba: 2 MB STE, TOS 2.06, GEMDOS drive);
  --frames: also every frame, one line each.
"""
import os, re, subprocess, sys, collections

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
BUILD = os.path.join(ROOT, 'game', 'build_prof')
NM = os.path.expanduser('~/cross-mint/bin/m68k-atari-mint-nm')
VBL_CYC = 512 * 313		# STE, 50 Hz
SECTIONS = {			# section n runs from marker n to the next marker (game/wof.cpp, main loop)
    0: 'input, pages, map switch', 1: 'logic ticks, scroll wrap', 2: 'sound mix', 3: 'fx tick', 4: 'fx build',
    5: 'carrier bob, camera', 6: 'hud/panel/vis build, pools', 7: 'EntityTickAll + links', 8: 'waves, blank, rebuild',
    9: 'playfield select', 10: 'bgrestore', 11: 'hybrid_fill', 12: 'direct sprites, pages',
    13: 'playfield sprites, message', 15: 'panel restore, fill', 17: 'forward view', 16: 'panel sprites, swap', 14: 'pacing wait'}


def marks():
    base = None
    for l in open(os.path.join(BUILD, 'wof.map')):
        m = re.match(r'^ \.text\s+0x([0-9a-f]+)\s+0x[0-9a-f]+\s+build_prof/wof\.o$', l)
        if m:
            base = int(m.group(1), 16)
    out = {}
    for l in subprocess.run([NM, os.path.join(BUILD, 'wof.o')], capture_output=True, text=True).stdout.splitlines():
        m = re.match(r'^([0-9a-f]+) t __Z5pmarkILi(\d+)EEvv$', l)
        if m:
            out[int(m.group(2))] = base + int(m.group(1), 16)
    return out


def main():
    a = sys.argv[1:]
    text = 0xceba
    if '--text' in a:
        i = a.index('--text'); text = int(a[i + 1], 0); del a[i:i + 2]
    every = '--frames' in a
    a = [x for x in a if x != '--frames']
    script, out = a[0], os.path.abspath(a[1])
    os.makedirs(out, exist_ok=True)
    ini = os.path.join(out, 'marks.ini')
    lines = []
    for n, addr in sorted(marks().items()):
        f = os.path.join(out, 'm%d.ini' % n)
        open(f, 'w').write('e %d\ne VBL\ne FrameCycles\n' % (1000 + n))
        lines.append('b pc = $%x :trace :quiet :file %s' % (text + addr, f))
    open(ini, 'w').write('\n'.join(lines) + '\n')
    r = subprocess.run([sys.executable, os.path.join(ROOT, 'tools', 'hatari_run.py'), script, out, '--prg', 'WOFPROF.PRG',
                        '--parse', ini])
    vals = [int(m.group(1)) for m in re.finditer(r'#(-?\d+) \(dec\)', open(os.path.join(out, 'hatari.txt'), errors='replace').read())]
    ev = []
    for i in range(0, len(vals) - 2, 3):
        if 1000 <= vals[i] < 1100:
            ev.append((vals[i] - 1000, vals[i + 1] * VBL_CYC + vals[i + 2]))
    if not ev:
        print('no marker hits: wrong --text?'); return 1
    frames = []				# (start, length, {section: cycles})
    cur = None
    for k, (n, t) in enumerate(ev):
        if n == 0:
            if cur:
                frames.append((cur[0], t - cur[0], cur[1]))
            cur = (t, collections.Counter())
        if cur and k + 1 < len(ev):
            cur[1][n] += ev[k + 1][1] - t
    rep = []
    late = [f for f in frames if f[1] > 3 * VBL_CYC + 2000]
    ok = [f for f in frames if f[1] <= 3 * VBL_CYC + 2000]
    rep.append('%d frames, %d late (more than 3 VBLs); cycles per VBL %d' % (len(frames), len(late), VBL_CYC))
    order = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 15, 17, 16, 14]
    rep.append('%-30s %10s %10s %10s' % ('section (VBLs)', 'on time', 'late', 'late max'))
    for n in order:
        name = SECTIONS.get(n, str(n))
        av = lambda fs: sum(f[2][n] for f in fs) / max(1, len(fs)) / VBL_CYC
        mx = max((f[2][n] for f in late), default=0) / VBL_CYC
        rep.append('%-30s %10.3f %10.3f %10.3f' % (name, av(ok), av(late), mx))
    work = lambda f: (f[1] - f[2][14]) / VBL_CYC
    rep.append('%-30s %10.3f %10.3f' % ('work (all but the wait)', sum(work(f) for f in ok) / max(1, len(ok)),
                                        sum(work(f) for f in late) / max(1, len(late))))
    rep.append('')
    rep.append('most expensive frames (work in VBLs; sections over 0.3 VBL):')
    for f in sorted(frames, key=lambda f: -work(f))[:40]:
        big = ', '.join('%s %.2f' % (SECTIONS.get(n, str(n)), c / VBL_CYC)
                        for n, c in sorted(f[2].items(), key=lambda x: -x[1]) if c > 0.3 * VBL_CYC and n != 14)
        rep.append('  VBL %6d  frame %.2f  work %.2f  %s' % (f[0] // VBL_CYC, f[1] / VBL_CYC, work(f), big))
    if every:
        rep.append('')
        for f in frames:
            rep.append('%6d %.2f %s' % (f[0] // VBL_CYC, f[1] / VBL_CYC,
                                       ' '.join('%d:%.2f' % (n, f[2][n] / VBL_CYC) for n in order)))
    open(os.path.join(out, 'frames.txt'), 'w').write('\n'.join(rep) + '\n')
    print('\n'.join(rep[:60]))
    return r.returncode


if __name__ == '__main__':
    sys.exit(main())
