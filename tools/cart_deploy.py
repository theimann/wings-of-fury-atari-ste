#!/usr/bin/env python3
"""cart_deploy.py: deployments to a SidecarTridge (md-devops GEMDRIVE) that send only what the card lacks and keep
what they replace.

  cart_deploy.py deploy   --remote /WOF --build <id> (--dir <folder> | --file <local>=<remote path> ...)
                          [--skip <top folder> ...] [--keep <top folder> ...] [--first <remote path> ...] [--run <program>]
  cart_deploy.py list     --remote /WOF
  cart_deploy.py activate --remote /WOF <number or build id> [--run <program>]
  cart_deploy.py run      --remote /WOF <program>

Host: $SIDECART_HOST (name or address). $SIDECART_ALIASES (name=address,...) maps names to addresses, so that a
cartridge keeps its state file whichever way it is named. md-devops' command
line tool: $SIDECART_CLI, or sidecart.py on the PATH.

How it works. The tool remembers, per cartridge and folder, the content (md5) of every file it has put there
(state: $CART_STATE or ~/.cart_state, <host>_<folder>.json). A deployment compares the new build with that:
  - a file the card holds already is left alone;
  - a file that is to be replaced is first renamed on the card into the store /OLD/<folder>/<number> (a rename costs
    no transfer), unless the store has that content already;
  - the new content comes out of the store by renaming if it is there (an earlier deployment had it), otherwise it
    is uploaded;
  - a file of the last deployment that the new one does not have goes to the store as well.
Every deployment is recorded with its build id, time, source folder and file list. "activate" makes an earlier one
current again by the same steps: renames where the store has the files, uploads from the recorded source folder
(the builds kept on the Mac) for the rest.
--keep: folders whose files are sent only when the card has none of them (save games: never replaced, not part
of a deployment's file list). --skip: top folders not sent at all.

The state is what this tool did. Files changed on the card by other means are not known to it; a rename that
fails falls back to an upload. First use on a folder filled by the old deploy scripts: their hash files
(<project>/.deploy_cache/<host>_<folder>/) are read once (--seed <that folder>)."""
import sys, os, json, hashlib, subprocess, time, argparse

SC = os.environ.get('SIDECART_CLI') or 'sidecart.py'      # md-devops' command line tool
STATE = os.environ.get('CART_STATE') or os.path.expanduser('~/.cart_state')
ALIAS = dict(a.split('=', 1) for a in os.environ.get('SIDECART_ALIASES', '').split(',') if '=' in a)


def sc(*args, tries=4, quiet=True):
    for t in range(tries):
        r = subprocess.run(([sys.executable, SC] if SC.endswith('.py') and os.path.exists(SC) else [SC]) + list(args), capture_output=True, text=True)
        if r.returncode == 0: return r.stdout
        if t + 1 < tries: time.sleep(4)
    if not quiet: sys.stderr.write(r.stdout + r.stderr)
    return None


def md5(path):
    h = hashlib.md5()
    with open(path, 'rb') as f:
        for b in iter(lambda: f.read(1 << 20), b''): h.update(b)
    return h.hexdigest()


class Card:
    def __init__(self, remote):
        self.host = os.environ.get('SIDECART_HOST', 'sidecart2.local'); self.remote = remote.rstrip('/')
        os.makedirs(STATE, exist_ok=True)
        self.path = os.path.join(STATE, '%s_%s.json' % (ALIAS.get(self.host, self.host), self.remote.strip('/').replace('/', '_')))
        self.s = json.load(open(self.path)) if os.path.exists(self.path) else {'current': {}, 'deployments': [], 'store': {}, 'next': 1, 'dirs': []}
        self.store_dir = '/OLD/' + self.remote.strip('/').replace('/', '_')

    def save(self):
        json.dump(self.s, open(self.path + '.new', 'w'), indent=1); os.replace(self.path + '.new', self.path)

    def mkdirs(self, rpath):
        parts = rpath.strip('/').split('/')[:-1]
        for i in range(1, len(parts) + 1):
            d = '/' + '/'.join(parts[:i])
            if d not in self.s['dirs']:
                sc('gemdrive', 'mkdir', d, tries=1); self.s['dirs'].append(d)

    def to_store(self, rel, h):
        """the file at rel (content h) leaves the folder: into the store, unless its content is there already"""
        full = self.remote + '/' + rel
        if h in self.s['store']:
            sc('gemdrive', 'rm', full, tries=2); return 'dropped (in the store)'
        name = '%s/%08d' % (self.store_dir, self.s['next'])
        self.mkdirs(name)
        if sc('gemdrive', 'mv', full, name, tries=2) is None: return 'not kept (rename failed)'
        self.s['store'][h] = name; self.s['next'] += 1
        return 'kept'

    def apply(self, want, run=None, label=''):
        """want: {rel: (md5, local path or None)}. Makes the folder hold exactly these (kept folders aside)."""
        cur = self.s['current']; sent = renamed = kept = failed = 0; t0 = time.time()
        for rel in [r for r in cur if r not in want]:              # files of the last deployment that this one lacks
            self.to_store(rel, cur[rel]); del cur[rel]; kept += 1; self.save()
        for rel, (h, local) in want.items():
            if cur.get(rel) == h: continue
            full = self.remote + '/' + rel; self.mkdirs(full)
            if rel in cur:
                if self.to_store(rel, cur[rel]) == 'kept': kept += 1
                del cur[rel]; self.save()
            if h in self.s['store'] and sc('gemdrive', 'mv', self.s['store'][h], full, tries=2) is not None:
                del self.s['store'][h]; cur[rel] = h; renamed += 1; self.save(); print('back  %s' % rel, flush=True); continue
            self.s['store'].pop(h, None)
            if local and os.path.exists(local) and sc('gemdrive', 'put', local, full, '-f') is not None:
                cur[rel] = h; sent += 1; self.save(); print('sent  %s' % rel, flush=True); continue
            failed += 1; print('FAILED %s%s' % (rel, '' if local and os.path.exists(local) else ' (not in the store, and its source file is gone)'), flush=True)
        print('%s: %d sent, %d taken from the store, %d kept in the store, %d failed, %d s' % (label, sent, renamed, kept, failed, time.time() - t0))
        return failed

    def run(self, prg):
        sc('runner', 'cd', self.remote, quiet=False)
        for _ in range(10):
            st = sc('runner', 'status') or ''
            if 'busy' in st and ': no' in st.split('busy')[1].split('\n')[0]: break
            time.sleep(1)
        sc('runner', 'run', prg, quiet=False); print((sc('runner', 'status') or '').strip())


def main():
    ap = argparse.ArgumentParser(); ap.add_argument('cmd', choices=['deploy', 'list', 'activate', 'run']); ap.add_argument('what', nargs='?')
    ap.add_argument('--remote', required=True); ap.add_argument('--build'); ap.add_argument('--dir'); ap.add_argument('--file', action='append', default=[])
    ap.add_argument('--skip', action='append', default=[]); ap.add_argument('--keep', action='append', default=[]); ap.add_argument('--first', action='append', default=[])
    ap.add_argument('--run'); ap.add_argument('--seed')
    a = ap.parse_args(); c = Card(a.remote)
    if a.cmd == 'list':
        for d in c.s['deployments']:
            print('%3d  %-28s %s  %d files%s' % (d['n'], d['build'], d['when'], len(d['files']), '   <- on the card now' if d['files'] == c.s['current'] else ''))
        print('store: %d files in %s' % (len(c.s['store']), c.store_dir)); return 0
    if a.cmd == 'run': c.run(a.what); return 0
    if sc('ping') is None: print('cartridge %s does not answer' % c.host); return 1
    if a.cmd == 'deploy':
        files = {}
        if a.dir:
            for root, _, names in os.walk(a.dir):
                for n in names:
                    if n.startswith('.'): continue
                    rel = os.path.relpath(os.path.join(root, n), a.dir).replace(os.sep, '/')
                    files[rel] = os.path.join(root, n)
        for f in a.file:
            local, rel = f.split('=', 1); files[rel.strip('/')] = local
        files = {r: p for r, p in files.items() if r.split('/')[0] not in a.skip}
        order = [r for r in a.first if r in files] + sorted(r for r in files if r not in a.first)
        keep = {r: files[r] for r in order if r.split('/')[0] in a.keep}
        want = {r: (md5(files[r]), os.path.abspath(files[r])) for r in order if r not in keep}
        if a.seed and not c.s['current'] and os.path.isdir(a.seed):          # the old scripts' hash files, once
            for r in want:
                p = os.path.join(a.seed, r.replace('/', '_') + '.md5')
                if os.path.exists(p): c.s['current'][r] = open(p).read().strip()
            print('state seeded from %s: %d files known' % (a.seed, len(c.s['current'])))
        for top in a.keep:                                                  # kept folders: only when the card has none
            listing = sc('gemdrive', 'ls', c.remote + '/' + top, tries=1) or ''
            mine = {r: p for r, p in keep.items() if r.split('/')[0] == top}
            if any(os.path.basename(r) in listing for r in mine): print('%s on the card kept (not sent)' % top); continue
            for r, p in mine.items():
                c.mkdirs(c.remote + '/' + r); print(('sent  ' if sc('gemdrive', 'put', p, c.remote + '/' + r, '-f') is not None else 'FAILED ') + r)
        failed = c.apply(want, label='deployment %s' % a.build)
        last = c.s['deployments'][-1] if c.s['deployments'] else None
        if not failed and not (last and last['build'] == (a.build or '?') and last['files'] == {r: w[0] for r, w in want.items()}):      # (the same build again: no new entry)
            n = (c.s['deployments'][-1]['n'] + 1) if c.s['deployments'] else 1
            c.s['deployments'].append({'n': n, 'build': a.build or '?', 'when': time.strftime('%Y-%m-%d %H:%M'), 'src': {r: w[1] for r, w in want.items()}, 'files': {r: w[0] for r, w in want.items()}})
            c.save()
    else:
        ds = [d for d in c.s['deployments'] if str(d['n']) == a.what or d['build'] == a.what or d['build'].endswith('+' + (a.what or '')) or (a.what or '-').upper() in d['build'].upper().replace('+', '.')]
        if not ds: print('no deployment "%s" (see list)' % a.what); return 1
        d = ds[-1]; print('making deployment %d (%s, %s) current' % (d['n'], d['build'], d['when']))
        failed = c.apply({r: (h, d['src'].get(r)) for r, h in d['files'].items()}, label='deployment %s again' % d['build'])
    if failed: return 1
    if a.run: c.run(a.run)
    return 0


if __name__ == '__main__':
    sys.exit(main())
