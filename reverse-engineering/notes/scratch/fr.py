import sys,re,os
# print decomp of functions in [lo,hi)
lo,hi=int(sys.argv[1],16),int(sys.argv[2],16)
txt=open(os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', '..', 'wings_decomp.c')).read()
parts=re.split(r'(?=// ==== FUN_)',txt)
for p in parts:
    m=re.match(r'// ==== FUN_([0-9a-f]+)',p)
    if m and lo<=int(m.group(1),16)<hi: print(p.replace('/* WARNING: Globals starting with \'_\' overlap smaller symbols at the same address */\n',''))
