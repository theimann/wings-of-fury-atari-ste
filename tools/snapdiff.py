"""Compare the screenshots of two regression-suite runs (tools/suite.sh output folders).
Usage: snapdiff.py <base dir> <new dir>   -> per test and snapshot: number of differing pixels
"""
import os, sys
from PIL import Image

base, new = sys.argv[1:3]
total = 0
for t in sorted(os.listdir(base)):
    bd, nd = os.path.join(base, t), os.path.join(new, t)
    if not os.path.isdir(bd) or not os.path.isdir(nd):
        continue
    for f in sorted(os.listdir(bd)):
        if not f.endswith('.png') or not os.path.exists(os.path.join(nd, f)):
            continue
        a = Image.open(os.path.join(bd, f)).convert('RGB')
        b = Image.open(os.path.join(nd, f)).convert('RGB')
        if a.size != b.size:
            print(t, f, 'size', a.size, b.size)
            continue
        pa, pb = a.tobytes(), b.tobytes()
        n = sum(1 for i in range(0, len(pa), 3) if pa[i:i + 3] != pb[i:i + 3])
        total += n
        print('%-16s %-28s %s' % (t, f, n if n else 'same'))
print('total differing pixels:', total)
