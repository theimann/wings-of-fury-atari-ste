"""Pack a built disk directory for release: tools/pack_disk.py <disk dir> <out dir> [jobs]

Tiles (.cct), sprites (.spr, .emx), map data (.dat) and pictures (.pic) become AGT 'wrapped' assets packed with ZX0 (AGT unpacks them on load).
Maps (.ccm) keep their 8-byte header, followed by the wrapped, packed map entries (local AGT patch in
worldmap::load_ccm: the map is unpacked straight into its final memory). PACK.INF holds the largest packed size (the
game allocates its unpack scratch buffer from it) and the unpacked sizes of the level files. Everything else is copied. ZX0 packing is slow (minutes per level
file), so results are cached by content hash in <out dir>/../.pack_cache.
"""
import hashlib, os, shutil, struct, subprocess, sys, tempfile
from concurrent.futures import ThreadPoolExecutor

AGT = os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', '..', 'agtools')
SKIP = {'panelspr.emx'}                       # stale files of earlier builds
MODE = 'zx0'


def pack(data, cache):
    key = os.path.join(cache, hashlib.md5(data).hexdigest() + '.' + MODE)
    if os.path.exists(key):
        return open(key, 'rb').read()
    with tempfile.TemporaryDirectory() as td:
        p = os.path.join(td, 'a.bin')
        open(p, 'wb').write(data)
        subprocess.run([os.path.join(AGT, 'scripts', 'pack.sh'), p, MODE], check=True, stdout=subprocess.DEVNULL,
                       stderr=subprocess.DEVNULL)
        out = open(p, 'rb').read()
    assert out[:4] == b'wrap' and struct.unpack('>I', out[12:16])[0] == len(data), 'packing failed'
    open(key, 'wb').write(out)
    return out


def main(src, dst, jobs=8):
    cache = os.path.join(os.path.dirname(os.path.abspath(dst)), '.pack_cache')
    os.makedirs(cache, exist_ok=True)
    shutil.rmtree(dst, ignore_errors=True)
    os.makedirs(os.path.join(dst, 'auto'))
    shutil.copy(os.path.join(src, 'auto', 'wof.prg'), os.path.join(dst, 'auto', 'wof.prg'))
    todo = []
    for name in sorted(os.listdir(src)):
        path = os.path.join(src, name)
        ext = name.rsplit('.', 1)[-1].lower()
        if not os.path.isfile(path) or name in SKIP or ext in ('prg', 'txt', 'inf', 'bin') or name.upper() == 'HISCORE.DAT':
            continue
        todo.append((name, ext, open(path, 'rb').read()))

    def one(item):
        name, ext, data = item
        if ext in ('cct', 'spr', 'emx', 'dat', 'pic'):
            out = pack(data, cache)
            psize = struct.unpack('>I', out[8:12])[0]
        elif ext == 'ccm':
            body = pack(data[8:], cache)
            out, psize = data[:8] + body, struct.unpack('>I', body[8:12])[0]
        else:
            out, psize = data, 0
        return name, len(data), len(out), psize, out

    with ThreadPoolExecutor(int(jobs)) as ex:
        res = list(ex.map(one, todo))
    # bundles: the files of one loading phase in one file (the game reads it in one go: opening and reading files one
    # by one costs seconds each from a floppy). START.BIN = everything the start-up loads; LVL_x.BIN = one mission
    packed = {r[0].lower(): r[4] for r in res}
    def bundle(fname, names):
        names = [n for n in names if n in packed]
        if not names: return
        head = 2 + 20 * len(names)
        blob, off = struct.pack('>H', len(names)), head
        body = b''
        for n in names:
            d = packed[n] + b'\0' * (len(packed[n]) & 1)
            blob += n.upper().encode('ascii').ljust(12, b'\0') + struct.pack('>II', off, len(packed[n]))
            body += d; off += len(d)
        open(os.path.join(dst, fname), 'wb').write(blob + body)
    start = [n for n in packed if n.endswith(('.spr', '.emx'))] + ['panel.cct', 'panel.ccm', 'music.dat', 'intro.dat',
             'broder.pic', 'title.pic', 'credits.pic', 'level_a.cct', 'level_a.ccm', 'map_a.dat']
    bundle('START.BIN', start)
    in_bundle = set(start)
    for l in 'abcdefghijklmno':
        names = ['level_%s.cct' % l, 'level_%s.ccm' % l, 'map_%s.dat' % l]
        bundle('LVL_%s.BIN' % l.upper(), names)
        in_bundle.update(names)
    for n, d in packed.items():                           # the rest stays a file of its own
        if n not in in_bundle: open(os.path.join(dst, n), 'wb').write(d)

    # PACK.INF: largest packed size, then the unpacked sizes of level_a..o (.cct, .ccm; 0 = no such level), so the
    # game sizes its level memory without opening 30 files (that took 20 s from a floppy)
    size = {r[0].lower(): r[1] for r in res}
    inf = struct.pack('>I', max(r[3] for r in res))
    for l in 'abcdefghijklmno':
        inf += struct.pack('>II', size.get('level_%s.cct' % l, 0), size.get('level_%s.ccm' % l, 0))
    open(os.path.join(dst, 'PACK.INF'), 'wb').write(inf)
    prg = os.path.getsize(os.path.join(dst, 'auto', 'wof.prg'))
    disk = sum(os.path.getsize(os.path.join(dst, f)) for f in os.listdir(dst) if os.path.isfile(os.path.join(dst, f)))
    cats = (('tiles', ('cct',)), ('maps', ('ccm',)), ('sprites', ('spr', 'emx')), ('map data', ('dat',)), ('pictures', ('pic',)))
    print('footprint (KB)      unpacked   packed')
    tin = tout = 0
    for label, exts in cats:
        a = sum(r[1] for r in res if r[0].rsplit('.', 1)[-1].lower() in exts)
        b = sum(r[2] for r in res if r[0].rsplit('.', 1)[-1].lower() in exts)
        tin += a; tout += b
        print('  %-16s %8.0f %8.0f' % (label, a / 1024, b / 1024))
    print('  %-16s %8.0f %8.0f' % ('program', prg / 1024, prg / 1024))
    print('  %-16s %8.0f %8.0f   (largest packed file %d bytes)'
          % ('total', (tin + prg) / 1024, (tout + prg) / 1024, max(r[3] for r in res)))
    print('  disk files (bundles + loose, without the program): %d KB' % (disk / 1024))


if __name__ == '__main__':
    main(*sys.argv[1:4])
