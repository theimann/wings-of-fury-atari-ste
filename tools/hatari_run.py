#!/usr/bin/env python3
"""Try a scripted run of the run build (make runs -> disk1/WOFRUN.PRG) in Hatari, without a window.

Usage: hatari_run.py <run script> <outdir> [--timeout S] [--avi] [--real] [--after S]
  - stages game/disk1 (the loose files) with WOFRUN.PRG in AUTO and the script as RUNS/RUN1.TXT, the way the
    cartridge runs it (docs/BUILDING.md, "Scripted runs on real machines")
  - fast forward unless --real; --avi records <outdir>/video.avi (normal speed)
  - --after S: S seconds after the end a screenshot <outdir>/after.png (the desktop the program went back to)
  - waits for the run's END line in RUNS/RUN1.LOG, copies the log to <outdir>/run.log and stops its own Hatari
"""
import os, shutil, subprocess, sys, time

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
DISK = os.path.join(ROOT, 'game', 'disk1')
INST = os.environ.get('WOF_INST') or str(os.getpid())
WORK = os.path.join(ROOT, 'tools', 'hplay_out')
STAGE = os.path.join(WORK, 'run_' + INST)
FIFO = os.path.join(WORK, 'run_' + INST + '.fifo')


def main():
    a = sys.argv[1:]
    timeout, after = 900.0, 0.0
    if '--after' in a:
        i = a.index('--after'); after = float(a[i + 1]); del a[i:i + 2]
    if '--timeout' in a:
        i = a.index('--timeout'); timeout = float(a[i + 1]); del a[i:i + 2]
    avi, real = '--avi' in a, '--real' in a
    a = [x for x in a if not x.startswith('--')]
    script, outdir = os.path.abspath(a[0]), os.path.abspath(a[1])
    os.makedirs(outdir, exist_ok=True)
    shutil.rmtree(STAGE, ignore_errors=True)
    os.makedirs(os.path.join(STAGE, 'AUTO'))
    os.makedirs(os.path.join(STAGE, 'RUNS'))
    for f in os.listdir(DISK):
        p = os.path.join(DISK, f)
        if os.path.isfile(p) and not f.upper().endswith('.PRG') and f.upper() not in ('REPLAY.TXT', 'HISCORE.DAT'):
            shutil.copy(p, STAGE)
    shutil.copy(os.path.join(DISK, 'WOFRUN.PRG'), os.path.join(STAGE, 'AUTO', 'WOFRUN.PRG'))
    shutil.copy(script, os.path.join(STAGE, 'RUNS', 'RUN1.TXT'))
    log = os.path.join(STAGE, 'RUNS', 'RUN1.LOG')
    env = dict(os.environ, HATARI_FIFO=FIFO, HATARI_SHOTS=os.path.join(STAGE, 'shots'), SDL_VIDEODRIVER='dummy',
               SDL_AUDIODRIVER='dummy')
    extra = ['--memsize', os.environ.get('WOF_MEMSIZE', '2')]
    if not real:
        extra += ['--fast-forward', 'on']
    if avi:
        extra += ['--avirecord', '--avi-vcodec', 'png', '--png-level', '1', '--avi-fps', '50',
                  '--avi-file', os.path.join(outdir, 'video.avi')]
    out = open(os.path.join(outdir, 'hatari.txt'), 'w')
    proc = subprocess.Popen([os.path.join(ROOT, 'tools', 'run_hatari.sh'), STAGE] + extra, stdout=out,
                            stderr=subprocess.STDOUT, env=env)
    t0, result = time.time(), 'timeout'
    try:
        while time.time() - t0 < timeout:
            if proc.poll() is not None:
                result = 'hatari exited'; break
            time.sleep(1)
            if os.path.exists(log):
                txt = open(log, errors='replace').read()
                if ' END frames ' in txt:
                    result = 'end'
                    if after:
                        time.sleep(after)
                        shots = os.path.join(STAGE, 'shots')
                        with open(FIFO, 'w') as f:
                            f.write('hatari-shortcut screenshot\n')
                        for _ in range(50):
                            time.sleep(0.1)
                            got = [x for x in os.listdir(shots) if x.endswith('.png')] if os.path.isdir(shots) else []
                            if got:
                                time.sleep(0.3); shutil.copy(os.path.join(shots, got[0]), os.path.join(outdir, 'after.png')); break
                    break
            crash = open(os.path.join(outdir, 'hatari.txt'), errors='replace').read()
            if 'Address Error' in crash or 'Bus Error' in crash or 'Illegal' in crash:
                result = 'crash'; time.sleep(1); break
    finally:
        if os.path.exists(log):
            shutil.copy(log, os.path.join(outdir, 'run.log'))
        proc.terminate()
        try:
            proc.wait(timeout=5)
        except subprocess.TimeoutExpired:
            proc.kill()
        shutil.rmtree(STAGE, ignore_errors=True)
        if os.path.exists(FIFO):
            os.remove(FIFO)
    print('result:', result, '(%.0f s)' % (time.time() - t0))
    return 0 if result == 'end' else 1


if __name__ == '__main__':
    sys.exit(main())
