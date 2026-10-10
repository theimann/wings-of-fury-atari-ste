#!/usr/bin/env python3
"""Play the STE prototype in Hatari from a replay script (see WOF_REPLAY in game/wof.cpp) and collect screenshots.

Usage: hatari_play.py <replay.txt> <outdir> [--ff] [--timeout S] [--tos IMG] [--wav] [--avi] [--exact]
  --wav: record Hatari's audio output from 'REPLAY loaded' to the end into <outdir>/sound.wav
  - builds nothing: run `make play` in game first (disk1/WOFPLAY.PRG)
  - stages game/disk1 + REPLAY.TXT into tools/hplay_out/ with WOFPLAY.PRG in AUTO
  - boots Hatari (tools/run_hatari.sh: STE, 4 MB, the TOS image named by WOF_TOS; WOF_MEMSIZE=2 for 2 MB), answers each "SNAP <name>" with a screenshot
    <outdir>/<name>.png, then presses Space to resume; stops at "REPLAY END", a crash or the timeout
  - the game's NatFeats log ends up in <outdir>/log.txt
  - "# EXPECT states 1 0 1" in the replay checks the sequence of player states seen in the log (consecutive
    duplicates collapsed); "# EXPECT score 96" checks the final score (hex),
    "# EXPECT score >= c8" a minimum. A mismatch fails the run.
"""
import os, shutil, subprocess, sys, time, glob

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
PROTO = os.environ.get('WOF_PROTO') or os.path.join(ROOT, 'game')
# every run has its own stage folder, control fifo and screenshot folder (WOF_INST, default: the pid), so several
# runs (a regression suite, a single test, another Hatari) can go on side by side
INST = os.environ.get('WOF_INST') or str(os.getpid())
WORK = os.path.join(ROOT, 'tools', 'hplay_out')
STAGE = os.path.join(WORK, 'stage_' + INST)
FIFO = os.path.join(WORK, 'hplay_' + INST + '.fifo')
SHOTS = os.path.join(WORK, 'shots_' + INST)

def send(cmd):
    with open(FIFO, 'w') as f:
        f.write(cmd + '\n')


def main():
    args = [a for a in sys.argv[1:] if not a.startswith('--')]
    ff = '--ff' in sys.argv
    timeout = 300
    if '--timeout' in sys.argv:
        timeout = float(sys.argv[sys.argv.index('--timeout') + 1])
        args = [a for a in args if a != sys.argv[sys.argv.index('--timeout') + 1]]
    tos = None
    if '--tos' in sys.argv:
        tos = os.path.abspath(os.path.expanduser(sys.argv[sys.argv.index('--tos') + 1]))
        args = [a for a in args if os.path.abspath(os.path.expanduser(a)) != tos]
    wav = '--wav' in sys.argv
    replay, outdir = os.path.abspath(args[0]), os.path.abspath(args[1])
    os.makedirs(outdir, exist_ok=True)

    # stage the disk (fresh AUTO folder so only WOFPLAY.PRG runs)
    if os.path.isdir(STAGE):
        shutil.rmtree(STAGE)
    os.makedirs(os.path.join(STAGE, 'AUTO'))
    for f in os.listdir(os.path.join(PROTO, os.environ.get('WOF_DISK', 'disk1'))):
        src = os.path.join(PROTO, os.environ.get('WOF_DISK', 'disk1'), f)
        if os.path.isfile(src) and not f.upper().endswith('.PRG'):
            shutil.copy(src, STAGE)
    shutil.copy(os.path.join(PROTO, os.environ.get('WOF_DISK', 'disk1'), 'WOFPLAY.PRG'), os.path.join(STAGE, 'AUTO', 'WOFPLAY.PRG'))
    shutil.copy(replay, os.path.join(STAGE, 'REPLAY.TXT'))

    os.makedirs(SHOTS, exist_ok=True)
    if os.path.exists(FIFO):
        os.remove(FIFO)
    os.makedirs(WORK, exist_ok=True)
    os.environ['HATARI_FIFO'] = FIFO           # run_hatari.sh: own control fifo and screenshot folder
    os.environ['HATARI_SHOTS'] = SHOTS
    logpath = os.path.join(outdir, 'log.txt')
    log = open(logpath, 'w')
    extra = ['--memsize', os.environ.get('WOF_MEMSIZE', '4')]      # (WOF_MEMSIZE=2: tight-memory test)
    if ff:
        extra += ['--fast-forward', 'on']
    if tos:
        extra += ['--tos', tos]
    if wav:
        # Hatari records to szYMCaptureFileName: use a copy of the configuration that names our file
        src_cfg = os.path.expanduser('~/Library/Application Support/Hatari/hatari.cfg')
        cfg = os.path.join(outdir, 'hatari_rec.cfg')
        lines = open(src_cfg).read().splitlines() if os.path.exists(src_cfg) else ['[Sound]']
        lines = [l for l in lines if not l.startswith('szYMCaptureFileName')]
        i = lines.index('[Sound]') + 1 if '[Sound]' in lines else len(lines)
        lines.insert(i, 'szYMCaptureFileName = ' + os.path.join(outdir, 'sound.wav'))
        open(cfg, 'w').write('\n'.join(lines) + '\n')
        os.environ['HATARI_CFG'] = cfg
    # other machines / options: WOF_HATARI_ARGS="--machine megaste --cpuclock 16" (appended, so they override)
    extra += os.environ.get('WOF_HATARI_ARGS', '').split()
    if '--exact' in sys.argv:
        extra += ['--cpu-exact', 'true', '--compatible', 'true']
    if '--avi' in sys.argv:
        extra += ['--avirecord', '--avi-vcodec', 'png', '--png-level', '1', '--avi-fps', '50', '--avi-file', os.path.join(outdir, 'video.avi')]
    proc = subprocess.Popen([os.path.join(ROOT, 'tools', 'run_hatari.sh'), STAGE] + extra,
                            stdout=log, stderr=subprocess.STDOUT)
    t0 = time.time()
    pos = 0
    result = 'timeout'
    try:
        while time.time() - t0 < timeout:
            if proc.poll() is not None:
                result = 'hatari exited'
                break
            time.sleep(0.1)
            with open(logpath, errors='replace') as f:
                f.seek(pos)
                chunk = f.read()
            # only consume complete lines
            cut = chunk.rfind('\n') + 1
            pos += len(chunk[:cut].encode('utf-8', errors='replace'))
            for line in chunk[:cut].splitlines():
                if wav and line.startswith('REPLAY loaded'):
                    send('hatari-shortcut recsound')
                    print('recording sound', flush=True)
                if line.startswith('SNAP '):
                    name = line[5:].strip() or 'snap'
                    before = set(glob.glob(os.path.join(SHOTS, '*.png')))
                    send('hatari-shortcut screenshot')
                    for _ in range(50):
                        time.sleep(0.1)
                        new = set(glob.glob(os.path.join(SHOTS, '*.png'))) - before
                        if new:
                            break
                    if new:
                        time.sleep(0.2)
                        shutil.move(new.pop(), os.path.join(outdir, name + '.png'))
                        print('snap', name, flush=True)
                    else:
                        print('snap', name, 'FAILED', flush=True)
                    send('hatari-event keydown 57')
                    time.sleep(0.15)
                    send('hatari-event keyup 57')
                elif line.startswith('REPLAY END'):
                    result = 'end'
                    if wav:
                        send('hatari-shortcut recsound')
                        time.sleep(1.0)
                elif 'Address Error' in line or 'Bus Error' in line or 'Illegal' in line:
                    print('CRASH:', line, flush=True)
                    result = 'crash'
            if result in ('end', 'crash'):
                if result == 'crash':
                    time.sleep(0.5)
                    before = set(glob.glob(os.path.join(SHOTS, '*.png')))
                    send('hatari-shortcut screenshot')
                    time.sleep(1)
                    new = set(glob.glob(os.path.join(SHOTS, '*.png'))) - before
                    if new:
                        shutil.move(new.pop(), os.path.join(outdir, 'crash.png'))
                break
    finally:
        proc.terminate()
        try:
            proc.wait(timeout=5)
        except subprocess.TimeoutExpired:
            proc.kill()
        shutil.rmtree(STAGE, ignore_errors=True)
        shutil.rmtree(SHOTS, ignore_errors=True)
        if os.path.exists(FIFO):
            os.remove(FIFO)
    if wav:
        for cand in (os.path.join(outdir, 'sound.wav'), os.path.join(os.getcwd(), 'hatari.wav'), os.path.join(ROOT, 'hatari.wav')):
            if os.path.exists(cand):
                if cand != os.path.join(outdir, 'sound.wav'):
                    shutil.move(cand, os.path.join(outdir, 'sound.wav'))
                print('sound ->', os.path.join(outdir, 'sound.wav'))
                break
        else:
            print('sound: no hatari.wav found')
    # expectations from the replay script
    import re
    exp_states = exp_score = None
    exp_min = False
    for line in open(replay):
        m = re.match(r'#\s*EXPECT\s+states\s+(.*)', line)
        if m: exp_states = m.group(1).split()
        m = re.match(r'#\s*EXPECT\s+score\s+(>=)?\s*(\w+)', line)
        if m: exp_score, exp_min = int(m.group(2), 16), bool(m.group(1))
    states, score = [], None
    for line in open(logpath, errors='replace'):
        m = re.match(r'st=([0-9A-F]{8}).*?score=([0-9A-F]{8})', line)
        if m:
            st = str(int(m.group(1), 16))
            if not states or states[-1] != st: states.append(st)
            score = int(m.group(2), 16)
    if result == 'end' and exp_states is not None and states != exp_states:
        print('EXPECT states', ' '.join(exp_states), 'got', ' '.join(states)); result = 'fail'
    if result == 'end' and exp_score is not None and (score is None or (score < exp_score if exp_min else score != exp_score)):
        print('EXPECT score %s%x got %s' % ('>= ' if exp_min else '', exp_score, score)); result = 'fail'
    print('result:', result, '(%.1fs)' % (time.time() - t0))
    return 0 if result == 'end' else 1


if __name__ == '__main__':
    sys.exit(main())
