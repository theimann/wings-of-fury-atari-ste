import re,bisect,collections
R={0x000:'BLTDDAT',0x002:'DMACONR',0x004:'VPOSR',0x006:'VHPOSR',0x00a:'JOY0DAT',0x00c:'JOY1DAT',0x010:'ADKCONR',0x016:'POTGOR',0x01c:'INTENAR',0x01e:'INTREQR',
0x040:'BLTCON0',0x042:'BLTCON1',0x044:'BLTAFWM',0x046:'BLTALWM',0x048:'BLTCPTH',0x04a:'BLTCPTL',0x04c:'BLTBPTH',0x04e:'BLTBPTL',0x050:'BLTAPTH',0x052:'BLTAPTL',0x054:'BLTDPTH',0x056:'BLTDPTL',0x058:'BLTSIZE',
0x060:'BLTCMOD',0x062:'BLTBMOD',0x064:'BLTAMOD',0x066:'BLTDMOD',0x070:'BLTCDAT',0x072:'BLTBDAT',0x074:'BLTADAT',0x080:'COP1LC',0x088:'COPJMP1',0x096:'DMACON',0x09a:'INTENA',0x09c:'INTREQ',0x09e:'ADKCON',0x034:'POTGO',
0x100:'BPLCON0',0x102:'BPLCON1',0x104:'BPLCON2',0x180:'COLOR00'}
for ch in range(4):
    b=0xa0+ch*16
    for o,n in [(0,'LCH'),(2,'LCL'),(4,'LEN'),(6,'PER'),(8,'VOL'),(10,'DAT')]: R[b+o]=f'AUD{ch}{n}'
funcs=sorted(int(m,16) for m in re.findall(r'==== FUN_([0-9a-f]+) @',open('wings_decomp.c').read()))
use=collections.defaultdict(set)
lines=open('wings_raw.s').read().splitlines()
active=False
for l in lines:
    m=re.match(r'\s*([0-9a-f]+):\s+(?:[0-9a-f]{4} ?)+\s+(.*)',l)
    if not m: continue
    a=int(m.group(1),16); ins=m.group(2)
    f=funcs[bisect.bisect_right(funcs,a)-1]
    if re.search(r'(%a4@\(-18118\)|#14675968|0xdff000),%fp',ins): active=f
    if active==f:
        for o in re.findall(r'%fp@\((-?\d+)\)',ins):
            o=int(o); use[f].add(R.get(o,hex(o)))
        if re.search(r'%fp@[^(]',ins) or ins.endswith('%fp@'): use[f].add('BLTDDAT?(fp@)')
    if ins.startswith('rts'): active=False
for f in sorted(use): print(hex(f),sorted(use[f]))
