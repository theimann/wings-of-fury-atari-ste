#!/usr/bin/env python3
"""Make the scripted runs for the real machines (game/runs/RUN1.TXT ...) from the replay scripts in tests/.

Each run is a chain of test scripts. A script that does not pick its own map starts after "MAP a" (a fresh
mission 1, also the way to reset everything between two scripts); END lines are dropped, one END closes the run.
SNAP lines stay: in the run build they are markers in the log (with frame and tick), no pause.
docs/BUILDING.md, "Scripted runs on real machines".
"""
import os

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
TESTS = os.path.join(ROOT, 'tests')
OUT = os.path.join(ROOT, 'game', 'runs')

# a flight over each map: load, take off, fly level for about 20 s
def map_flight(letter):
    return ['# --- map %s: load, take off, fly' % letter, 'MAP %s' % letter, '4 -', 'SNAP map_%s' % letter,
            '1 T', 'WAITDECK', '1 -', '100 L', '30 UL', '4 L', 'SNAP map_%s_air' % letter, '250 L']

RUNS = [
    ('sortie', 'take-off, landing and elevator, bombs, save and load, soldiers, hut smoke, rockets, torpedo',
     ['takeoff_fire', 'landing_elevator', 'savegame', 'soldiers', 'hut_smoke', 'rockets', 'torpedo', 'torpedo_roll']),
    ('views', 'high altitude view, dives, waves, past the map ends, night, help page, gun, oil, speed, deck bob',
     ['high_alt', 'dive_scroll', 'jump_dive', 'waves', 'map_wrap', 'map_wrap_high', 'night', 'help', 'gun_flash',
      'oil_turn', 'accel', 'carrier_far', 'bob_video', 'lamps', 'flags_deck']),
    ('combat', 'Zeros, AA guns, carrier bomber, pillboxes, ship sinking, enemy ship guns, kill tally',
     ['zeros', 'aa_guns', 'bomber', 'pillbox', 'pillbox_mini', 'ship_sink', 'far_out_guns', 'zero_left',
      'kill_tally']),
    ('crashes', 'crashes into sea, island and carrier, the own carrier sinking, promotion, front end pages',
     ['crash_sea', 'crash_sea_near', 'crash_island', 'crash_carrier', 'crash_carrier_edge', 'carrier_sink_smooth',
      'carrier_gone', 'ceremony', 'rank_restart2', 'frontend']),
    ('maps', 'every map loaded and flown over, b to o and a again', None),
    ('soak', 'six minutes on the deck, then four bombing sorties', ['idle_deck', 'bomb_hut_mini', 'bomb_hut_mini',
     'bomb_hut_mini', 'bomb_hut_mini']),
]


def script_lines(name):
    lines = []
    for l in open(os.path.join(TESTS, name + '.txt')).read().splitlines():
        if l.strip().upper() == 'END':
            continue
        lines.append(l)
    return lines


def picks_map(lines):
    for l in lines:
        s = l.split('#')[0].strip()
        if not s:
            continue
        return s.startswith('MAP') or s.startswith('NEWGAME')
    return False


def main():
    os.makedirs(OUT, exist_ok=True)
    index = ['Scripted runs (tools/make_runs.py; docs/BUILDING.md, "Scripted runs on real machines")', '']
    for n, (name, what, parts) in enumerate(RUNS, 1):
        out = ['# run %d: %s - %s' % (n, name, what)]
        if parts is None:
            for letter in 'bcdefghijklmnoa':
                out += map_flight(letter)
        else:
            for p in parts:
                lines = script_lines(p)
                out.append('# --- %s' % p)
                if not picks_map(lines):
                    out += ['MAP a', '4 -']
                out += lines
        out.append('END')
        ticks = 0
        for l in out:
            s = l.split('#')[0].split()
            if s and s[0].isdigit():
                ticks += int(s[0])
        open(os.path.join(OUT, 'RUN%d.TXT' % n), 'w', newline='\r\n').write('\n'.join(out) + '\n')
        index.append('RUN%d  %-8s %4d s of play  %s' % (n, name, ticks * 4 // 50, what))
    open(os.path.join(OUT, 'INDEX.TXT'), 'w', newline='\r\n').write('\n'.join(index) + '\n')
    print('\n'.join(index))


if __name__ == '__main__':
    main()
