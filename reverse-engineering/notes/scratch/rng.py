import sys,re,os
lo=int(sys.argv[1],16); hi=int(sys.argv[2],16)
for l in open(os.path.join(os.path.dirname(os.path.abspath(__file__)), 'ann.s')):
    m=re.match(r'\s*([0-9a-f]+):',l)
    if m and lo<=int(m.group(1),16)<hi: print(l.rstrip())
