
re/notes/scratch/songplay.bin:     file format binary


Disassembly of section .data:

00000000 <.data>:
   0:	b07c 0000      	cmpw #0,%d0
   4:	6700 09b6      	beqw 0x9bc
   8:	b07c 0001      	cmpw #1,%d0
   c:	6700 0938      	beqw 0x946
  10:	b07c 0002      	cmpw #2,%d0
  14:	6700 0914      	beqw 0x92a
  18:	b07c 0003      	cmpw #3,%d0
  1c:	6746           	beqs 0x64
  1e:	b07c 0004      	cmpw #4,%d0
  22:	6700 0a2c      	beqw 0xa50
  26:	b07c 0005      	cmpw #5,%d0
  2a:	6700 0272      	beqw 0x29e
  2e:	b07c 0006      	cmpw #6,%d0
  32:	6750           	beqs 0x84
  34:	b07c 0007      	cmpw #7,%d0
  38:	6770           	beqs 0xaa
  3a:	b07c 0008      	cmpw #8,%d0
  3e:	6700 0168      	beqw 0x1a8
  42:	b07c 0009      	cmpw #9,%d0
  46:	6700 01a2      	beqw 0x1ea
  4a:	b07c 000a      	cmpw #10,%d0
  4e:	6700 01aa      	beqw 0x1fa
  52:	b07c 000b      	cmpw #11,%d0
  56:	6700 01e8      	beqw 0x240
  5a:	b07c 000c      	cmpw #12,%d0
  5e:	6700 01f2      	beqw 0x252
  62:	4e75           	rts
  64:	4a79 0000 0d0c 	tstw 0xd0c
  6a:	6716           	beqs 0x82
  6c:	4279 0000 0d1e 	clrw 0xd1e
  72:	33fc 000f 00df 	movew #15,0xdff096
  78:	f096 
  7a:	33fc 0003 0000 	movew #3,0xd0c
  80:	0d0c 
  82:	4e75           	rts
  84:	4a79 0000 0d1e 	tstw 0xd1e
  8a:	66d8           	bnes 0x64
  8c:	4a79 0000 0d0c 	tstw 0xd0c
  92:	6714           	beqs 0xa8
  94:	33c1 0000 0d1a 	movew %d1,0xd1a
  9a:	33c1 0000 0d1c 	movew %d1,0xd1c
  a0:	33fc 0004 0000 	movew #4,0xd0c
  a6:	0d0c 
  a8:	4e75           	rts
  aa:	48e7 ffff      	moveml %d0-%sp,%sp@-
  ae:	b1fc 0000 0000 	cmpal #0,%a0
  b4:	6748           	beqs 0xfe
  b6:	33c1 0000 0d24 	movew %d1,0xd24
  bc:	33c2 0000 0d26 	movew %d2,0xd26
  c2:	33c3 0000 0d28 	movew %d3,0xd28
  c8:	33c4 0000 0d14 	movew %d4,0xd14
  ce:	03f9 0000 0d12 	bset %d1,0xd12
  d4:	4247           	clrw %d7
  d6:	03c7           	bset %d1,%d7
  d8:	43f9 0000 0d2a 	lea 0xd2a,%a1
  de:	e549           	lslw #2,%d1
  e0:	2271 1000      	moveal %a1@(0000000000000000,%d1:w),%a1
  e4:	23c8 0000 0d20 	movel %a0,0xd20
  ea:	2469 0028      	moveal %a1@(40),%a2
  ee:	4252           	clrw %a2@
  f0:	2469 002c      	moveal %a1@(44),%a2
  f4:	34bc 007c      	movew #124,%a2@
  f8:	33c7 00df f096 	movew %d7,0xdff096
  fe:	4cdf ffff      	moveml %sp@+,%d0-%sp
 102:	4e75           	rts
 104:	3239 0000 0d24 	movew 0xd24,%d1
 10a:	3439 0000 0d26 	movew 0xd26,%d2
 110:	3639 0000 0d28 	movew 0xd28,%d3
 116:	2079 0000 0d20 	moveal 0xd20,%a0
 11c:	03f9 0000 0d12 	bset %d1,0xd12
 122:	4247           	clrw %d7
 124:	03c7           	bset %d1,%d7
 126:	33c7 0000 0a92 	movew %d7,0xa92
 12c:	8e7c 8000      	orw #-32768,%d7
 130:	33c7 0000 0a90 	movew %d7,0xa90
 136:	ef4f           	lslw #7,%d7
 138:	8e7c 8000      	orw #-32768,%d7
 13c:	33c7 0000 0a94 	movew %d7,0xa94
 142:	43f9 0000 0d2a 	lea 0xd2a,%a1
 148:	e549           	lslw #2,%d1
 14a:	2271 1000      	moveal %a1@(0000000000000000,%d1:w),%a1
 14e:	337c ffff 0046 	movew #-1,%a1@(70)
 154:	2448           	moveal %a0,%a2
 156:	4eba 0844      	jsr %pc@(0x99c)
 15a:	264a           	moveal %a2,%a3
 15c:	4eba 084e      	jsr %pc@(0x9ac)
 160:	2c69 0028      	moveal %a1@(40),%fp
 164:	3c82           	movew %d2,%fp@
 166:	3343 0048      	movew %d3,%a1@(72)
 16a:	2c69 0030      	moveal %a1@(48),%fp
 16e:	2c8a           	movel %a2,%fp@
 170:	2c69 0034      	moveal %a1@(52),%fp
 174:	2413           	movel %a3@,%d2
 176:	e24a           	lsrw #1,%d2
 178:	3c82           	movew %d2,%fp@
 17a:	2c69 002c      	moveal %a1@(44),%fp
 17e:	342b 000c      	movew %a3@(12),%d2
 182:	263c 0036 9e99 	movel #3579545,%d3
 188:	86c2           	divuw %d2,%d3
 18a:	3c83           	movew %d3,%fp@
 18c:	33f9 0000 0a90 	movew 0xa90,0xdff096
 192:	00df f096 
 196:	33f9 0000 0a94 	movew 0xa94,0xdff09a
 19c:	00df f09a 
 1a0:	42b9 0000 0d20 	clrl 0xd20
 1a6:	4e75           	rts
 1a8:	48e7 60c0      	moveml %d1-%d2/%a0-%a1,%sp@-
 1ac:	4242           	clrw %d2
 1ae:	03c2           	bset %d1,%d2
 1b0:	03b9 0000 0d12 	bclr %d1,0xd12
 1b6:	41f9 0000 0d2a 	lea 0xd2a,%a0
 1bc:	e549           	lslw #2,%d1
 1be:	2070 1000      	moveal %a0@(0000000000000000,%d1:w),%a0
 1c2:	2268 0028      	moveal %a0@(40),%a1
 1c6:	4251           	clrw %a1@
 1c8:	2268 002c      	moveal %a0@(44),%a1
 1cc:	32bc 007c      	movew #124,%a1@
 1d0:	33c2 00df f096 	movew %d2,0xdff096
 1d6:	317c ffff 0012 	movew #-1,%a0@(18)
 1dc:	4268 0048      	clrw %a0@(72)
 1e0:	4268 0046      	clrw %a0@(70)
 1e4:	4cdf 0306      	moveml %sp@+,%d1-%d2/%a0-%a1
 1e8:	4e75           	rts
 1ea:	4240           	clrw %d0
 1ec:	0339 0000 0d12 	btst %d1,0xd12
 1f2:	6704           	beqs 0x1f8
 1f4:	303c ffff      	movew #-1,%d0
 1f8:	4e75           	rts
 1fa:	33fc ffff 0000 	movew #-1,0xd1e
 200:	0d1e 
 202:	41f9 0000 0d3a 	lea 0xd3a,%a0
 208:	6122           	bsrs 0x22c
 20a:	41f9 0000 0d84 	lea 0xd84,%a0
 210:	611a           	bsrs 0x22c
 212:	41f9 0000 0dce 	lea 0xdce,%a0
 218:	6112           	bsrs 0x22c
 21a:	41f9 0000 0e18 	lea 0xe18,%a0
 220:	610a           	bsrs 0x22c
 222:	33fc 000f 00df 	movew #15,0xdff096
 228:	f096 
 22a:	4e75           	rts
 22c:	2268 0002      	moveal %a0@(2),%a1
 230:	2028 000a      	movel %a0@(10),%d0
 234:	2171 0000 0006 	movel %a1@(0000000000000000,%d0:w),%a0@(6)
 23a:	4268 000e      	clrw %a0@(14)
 23e:	4e75           	rts
 240:	4a79 0000 0d0c 	tstw 0xd0c
 246:	6700 06e2      	beqw 0x92a
 24a:	4279 0000 0d1e 	clrw 0xd1e
 250:	4e75           	rts
 252:	0339 0000 0d12 	btst %d1,0xd12
 258:	6720           	beqs 0x27a
 25a:	41f9 0000 0d2a 	lea 0xd2a,%a0
 260:	e549           	lslw #2,%d1
 262:	2070 1000      	moveal %a0@(0000000000000000,%d1:w),%a0
 266:	2c68 0028      	moveal %a0@(40),%fp
 26a:	3c83           	movew %d3,%fp@
 26c:	2c68 002c      	moveal %a0@(44),%fp
 270:	263c 0036 9e99 	movel #3579545,%d3
 276:	86c2           	divuw %d2,%d3
 278:	3c83           	movew %d3,%fp@
 27a:	4e75           	rts
 27c:	48e7 e0e0      	moveml %d0-%d2/%a0-%a2,%sp@-
 280:	b1fc 0000 0000 	cmpal #0,%a0
 286:	6b10           	bmis 0x298
 288:	670e           	beqs 0x298
 28a:	23c8 0000 0d16 	movel %a0,0xd16
 290:	33fc 0001 0000 	movew #1,0xd0c
 296:	0d0c 
 298:	4cdf 0707      	moveml %sp@+,%d0-%d2/%a0-%a2
 29c:	4e75           	rts
 29e:	3039 0000 0d0c 	movew 0xd0c,%d0
 2a4:	4e75           	rts
 2a6:	48e7 ffff      	moveml %d0-%sp,%sp@-
 2aa:	287c 0000 8a8e 	moveal #35470,%a4
 2b0:	4ab9 0000 0d20 	tstl 0xd20
 2b6:	6704           	beqs 0x2bc
 2b8:	4eba fe4a      	jsr %pc@(0x104)
 2bc:	4a79 0000 0d1e 	tstw 0xd1e
 2c2:	6634           	bnes 0x2f8
 2c4:	4a79 0000 0d0c 	tstw 0xd0c
 2ca:	672c           	beqs 0x2f8
 2cc:	0c79 0001 0000 	cmpiw #1,0xd0c
 2d2:	0d0c 
 2d4:	6700 0084      	beqw 0x35a
 2d8:	0c79 0002 0000 	cmpiw #2,0xd0c
 2de:	0d0c 
 2e0:	6700 013c      	beqw 0x41e
 2e4:	0c79 0003 0000 	cmpiw #3,0xd0c
 2ea:	0d0c 
 2ec:	6710           	beqs 0x2fe
 2ee:	0c79 0004 0000 	cmpiw #4,0xd0c
 2f4:	0d0c 
 2f6:	6712           	beqs 0x30a
 2f8:	4cdf ffff      	moveml %sp@+,%d0-%sp
 2fc:	4e75           	rts
 2fe:	4279 0000 0d0c 	clrw 0xd0c
 304:	4eba 01d4      	jsr %pc@(0x4da)
 308:	60ee           	bras 0x2f8
 30a:	5379 0000 0d1a 	subqw #1,0xd1a
 310:	6c00 010c      	bgew 0x41e
 314:	33f9 0000 0d1c 	movew 0xd1c,0xd1a
 31a:	0000 0d1a 
 31e:	4247           	clrw %d7
 320:	41f9 0000 0d3a 	lea 0xd3a,%a0
 326:	6120           	bsrs 0x348
 328:	41f9 0000 0d84 	lea 0xd84,%a0
 32e:	6118           	bsrs 0x348
 330:	41f9 0000 0dce 	lea 0xdce,%a0
 336:	6110           	bsrs 0x348
 338:	41f9 0000 0e18 	lea 0xe18,%a0
 33e:	6108           	bsrs 0x348
 340:	4a47           	tstw %d7
 342:	6600 00da      	bnew 0x41e
 346:	60b6           	bras 0x2fe
 348:	3028 001e      	movew %a0@(30),%d0
 34c:	4a40           	tstw %d0
 34e:	6708           	beqs 0x358
 350:	5368 001e      	subqw #1,%a0@(30)
 354:	3e3c ffff      	movew #-1,%d7
 358:	4e75           	rts
 35a:	2079 0000 0d16 	moveal 0xd16,%a0
 360:	33fc ffff 0000 	movew #-1,0xd3a
 366:	0d3a 
 368:	2250           	moveal %a0@,%a1
 36a:	23c9 0000 0d3c 	movel %a1,0xd3c
 370:	23d1 0000 0d40 	movel %a1@,0xd40
 376:	42b9 0000 0d44 	clrl 0xd44
 37c:	4279 0000 0d48 	clrw 0xd48
 382:	33fc 0020 0000 	movew #32,0xd58
 388:	0d58 
 38a:	33fc ffff 0000 	movew #-1,0xd84
 390:	0d84 
 392:	2268 0004      	moveal %a0@(4),%a1
 396:	23c9 0000 0d86 	movel %a1,0xd86
 39c:	23d1 0000 0d8a 	movel %a1@,0xd8a
 3a2:	42b9 0000 0d8e 	clrl 0xd8e
 3a8:	4279 0000 0d92 	clrw 0xd92
 3ae:	33fc 0020 0000 	movew #32,0xda2
 3b4:	0da2 
 3b6:	33fc ffff 0000 	movew #-1,0xdce
 3bc:	0dce 
 3be:	2268 0008      	moveal %a0@(8),%a1
 3c2:	23c9 0000 0dd0 	movel %a1,0xdd0
 3c8:	23d1 0000 0dd4 	movel %a1@,0xdd4
 3ce:	42b9 0000 0dd8 	clrl 0xdd8
 3d4:	4279 0000 0ddc 	clrw 0xddc
 3da:	33fc 0020 0000 	movew #32,0xdec
 3e0:	0dec 
 3e2:	33fc ffff 0000 	movew #-1,0xe18
 3e8:	0e18 
 3ea:	2268 000c      	moveal %a0@(12),%a1
 3ee:	23c9 0000 0e1a 	movel %a1,0xe1a
 3f4:	23d1 0000 0e1e 	movel %a1@,0xe1e
 3fa:	42b9 0000 0e22 	clrl 0xe22
 400:	4279 0000 0e26 	clrw 0xe26
 406:	33fc 0020 0000 	movew #32,0xe36
 40c:	0e36 
 40e:	33fc 0002 0000 	movew #2,0xd0c
 414:	0d0c 
 416:	33fc 000f 00df 	movew #15,0xdff096
 41c:	f096 
 41e:	47f9 0000 0d3a 	lea 0xd3a,%a3
 424:	33fc 8001 0000 	movew #-32767,0xa90
 42a:	0a90 
 42c:	33fc 0001 0000 	movew #1,0xa92
 432:	0a92 
 434:	33fc 8080 0000 	movew #-32640,0xa94
 43a:	0a94 
 43c:	33fc 0000 0000 	movew #0,0xa96
 442:	0a96 
 444:	4eba 00ae      	jsr %pc@(0x4f4)
 448:	47f9 0000 0d84 	lea 0xd84,%a3
 44e:	33fc 8002 0000 	movew #-32766,0xa90
 454:	0a90 
 456:	33fc 0002 0000 	movew #2,0xa92
 45c:	0a92 
 45e:	33fc 8100 0000 	movew #-32512,0xa94
 464:	0a94 
 466:	33fc 0001 0000 	movew #1,0xa96
 46c:	0a96 
 46e:	4eba 0084      	jsr %pc@(0x4f4)
 472:	47f9 0000 0dce 	lea 0xdce,%a3
 478:	33fc 8004 0000 	movew #-32764,0xa90
 47e:	0a90 
 480:	33fc 0004 0000 	movew #4,0xa92
 486:	0a92 
 488:	33fc 8200 0000 	movew #-32256,0xa94
 48e:	0a94 
 490:	33fc 0002 0000 	movew #2,0xa96
 496:	0a96 
 498:	615a           	bsrs 0x4f4
 49a:	47f9 0000 0e18 	lea 0xe18,%a3
 4a0:	33fc 8008 0000 	movew #-32760,0xa90
 4a6:	0a90 
 4a8:	33fc 0008 0000 	movew #8,0xa92
 4ae:	0a92 
 4b0:	33fc 8400 0000 	movew #-31744,0xa94
 4b6:	0a94 
 4b8:	33fc 0003 0000 	movew #3,0xa96
 4be:	0a96 
 4c0:	6132           	bsrs 0x4f4
 4c2:	4ab9 0000 0d0e 	tstl 0xd0e
 4c8:	6600 fe2e      	bnew 0x2f8
 4cc:	33fc 0000 0000 	movew #0,0xd0c
 4d2:	0d0c 
 4d4:	6104           	bsrs 0x4da
 4d6:	6000 fe20      	braw 0x2f8
 4da:	33fc 0780 00df 	movew #1920,0xdff09a
 4e0:	f09a 
 4e2:	33fc 0780 00df 	movew #1920,0xdff01e
 4e8:	f01e 
 4ea:	33fc 000f 00df 	movew #15,0xdff096
 4f0:	f096 
 4f2:	4e75           	rts
 4f4:	4a53           	tstw %a3@
 4f6:	6700 02f0      	beqw 0x7e8
 4fa:	4243           	clrw %d3
 4fc:	4a6b 000e      	tstw %a3@(14)
 500:	6700 00d0      	beqw 0x5d2
 504:	206b 003c      	moveal %a3@(60),%a0
 508:	4a68 0022      	tstw %a0@(34)
 50c:	6712           	beqs 0x520
 50e:	3028 002c      	movew %a0@(44),%d0
 512:	5268 002c      	addqw #1,%a0@(44)
 516:	c07c 0003      	andw #3,%d0
 51a:	e348           	lslw #1,%d0
 51c:	3630 0024      	movew %a0@(0000000000000024,%d0:w),%d3
 520:	536b 000e      	subqw #1,%a3@(14)
 524:	302b 000e      	movew %a3@(14),%d0
 528:	b06b 0010      	cmpw %a3@(16),%d0
 52c:	676a           	beqs 0x598
 52e:	206b 003c      	moveal %a3@(60),%a0
 532:	4a68 0022      	tstw %a0@(34)
 536:	670e           	beqs 0x546
 538:	322b 0040      	movew %a3@(64),%d1
 53c:	d243           	addw %d3,%d1
 53e:	4eba 02aa      	jsr %pc@(0x7ea)
 542:	6000 02a4      	braw 0x7e8
 546:	4a68 001e      	tstw %a0@(30)
 54a:	6700 029c      	beqw 0x7e8
 54e:	5368 001c      	subqw #1,%a0@(28)
 552:	6e00 0294      	bgtw 0x7e8
 556:	3168 0018 001c 	movew %a0@(24),%a0@(28)
 55c:	322b 0020      	movew %a3@(32),%d1
 560:	302b 0042      	movew %a3@(66),%d0
 564:	3400           	movew %d0,%d2
 566:	9041           	subw %d1,%d0
 568:	4a6b 0044      	tstw %a3@(68)
 56c:	6d22           	blts 0x590
 56e:	b068 0012      	cmpw %a0@(18),%d0
 572:	6304           	blss 0x578
 574:	446b 0044      	negw %a3@(68)
 578:	d46b 0044      	addw %a3@(68),%d2
 57c:	4a6b 0046      	tstw %a3@(70)
 580:	6606           	bnes 0x588
 582:	2c6b 002c      	moveal %a3@(44),%fp
 586:	3c82           	movew %d2,%fp@
 588:	3742 0042      	movew %d2,%a3@(66)
 58c:	6000 025a      	braw 0x7e8
 590:	b068 0014      	cmpw %a0@(20),%d0
 594:	62e2           	bhis 0x578
 596:	60dc           	bras 0x574
 598:	0c6b 0001 0038 	cmpiw #1,%a3@(56)
 59e:	6700 0248      	beqw 0x7e8
 5a2:	4a6b 003a      	tstw %a3@(58)
 5a6:	6600 0240      	bnew 0x7e8
 5aa:	4a6b 0046      	tstw %a3@(70)
 5ae:	6618           	bnes 0x5c8
 5b0:	33f9 0000 0a92 	movew 0xa92,0xdff096
 5b6:	00df f096 
 5ba:	2c6b 0028      	moveal %a3@(40),%fp
 5be:	4256           	clrw %fp@
 5c0:	2c6b 002c      	moveal %a3@(44),%fp
 5c4:	3cbc 007c      	movew #124,%fp@
 5c8:	377c ffff 0012 	movew #-1,%a3@(18)
 5ce:	6000 0218      	braw 0x7e8
 5d2:	206b 0002      	moveal %a3@(2),%a0
 5d6:	226b 0006      	moveal %a3@(6),%a1
 5da:	202b 000a      	movel %a3@(10),%d0
 5de:	4241           	clrw %d1
 5e0:	1211           	moveb %a1@,%d1
 5e2:	4242           	clrw %d2
 5e4:	1429 0001      	moveb %a1@(1),%d2
 5e8:	b27c 00d9      	cmpw #217,%d1
 5ec:	6c2a           	bges 0x618
 5ee:	0801 0007      	btst #7,%d1
 5f2:	670e           	beqs 0x602
 5f4:	4a6b 003a      	tstw %a3@(58)
 5f8:	660c           	bnes 0x606
 5fa:	377c 0002 003a 	movew #2,%a3@(58)
 600:	6004           	bras 0x606
 602:	426b 003a      	clrw %a3@(58)
 606:	c27c 007f      	andw #127,%d1
 60a:	d270 0004      	addw %a0@(0000000000000004,%d0:w),%d1
 60e:	3741 0040      	movew %d1,%a3@(64)
 612:	d243           	addw %d3,%d1
 614:	6000 00ee      	braw 0x704
 618:	b27c 00d9      	cmpw #217,%d1
 61c:	6738           	beqs 0x656
 61e:	b27c 00db      	cmpw #219,%d1
 622:	6746           	beqs 0x66a
 624:	b27c 00da      	cmpw #218,%d1
 628:	6758           	beqs 0x682
 62a:	b27c 00dc      	cmpw #220,%d1
 62e:	6758           	beqs 0x688
 630:	b27c 00dd      	cmpw #221,%d1
 634:	6774           	beqs 0x6aa
 636:	b27c 00de      	cmpw #222,%d1
 63a:	6700 0086      	beqw 0x6c2
 63e:	b27c 00df      	cmpw #223,%d1
 642:	6700 0098      	beqw 0x6dc
 646:	b27c 00e0      	cmpw #224,%d1
 64a:	6700 00b0      	beqw 0x6fc
 64e:	54ab 0006      	addql #2,%a3@(6)
 652:	5489           	addql #2,%a1
 654:	6088           	bras 0x5de
 656:	5cab 000a      	addql #6,%a3@(10)
 65a:	5c80           	addql #6,%d0
 65c:	2770 0000 0006 	movel %a0@(0000000000000000,%d0:w),%a3@(6)
 662:	226b 0006      	moveal %a3@(6),%a1
 666:	6000 ff76      	braw 0x5de
 66a:	42ab 000a      	clrl %a3@(10)
 66e:	206b 0002      	moveal %a3@(2),%a0
 672:	2750 0006      	movel %a0@,%a3@(6)
 676:	226b 0006      	moveal %a3@(6),%a1
 67a:	202b 000a      	movel %a3@(10),%d0
 67e:	6000 ff5e      	braw 0x5de
 682:	4253           	clrw %a3@
 684:	6000 0162      	braw 0x7e8
 688:	e54a           	lslw #2,%d2
 68a:	2479 0000 0e66 	moveal 0xe66,%a2
 690:	2472 2000      	moveal %a2@(0000000000000000,%d2:w),%a2
 694:	274a 003c      	movel %a2,%a3@(60)
 698:	2752 0014      	movel %a2@,%a3@(20)
 69c:	276a 0004 0018 	movel %a2@(4),%a3@(24)
 6a2:	376a 0008 001c 	movew %a2@(8),%a3@(28)
 6a8:	60a4           	bras 0x64e
 6aa:	13c2 00bf e501 	moveb %d2,0xbfe501
 6b0:	13fc 0010 00bf 	moveb #16,0xbfee01
 6b6:	ee01 
 6b8:	13fc 0001 00bf 	moveb #1,0xbfee01
 6be:	ee01 
 6c0:	608c           	bras 0x64e
 6c2:	13c2 00bf e401 	moveb %d2,0xbfe401
 6c8:	13fc 0010 00bf 	moveb #16,0xbfee01
 6ce:	ee01 
 6d0:	13fc 0001 00bf 	moveb #1,0xbfee01
 6d6:	ee01 
 6d8:	6000 ff74      	braw 0x64e
 6dc:	0c79 0004 0000 	cmpiw #4,0xd0c
 6e2:	0d0c 
 6e4:	6700 ff68      	beqw 0x64e
 6e8:	4a6b 0046      	tstw %a3@(70)
 6ec:	6606           	bnes 0x6f4
 6ee:	2c6b 0028      	moveal %a3@(40),%fp
 6f2:	3c82           	movew %d2,%fp@
 6f4:	3742 001e      	movew %d2,%a3@(30)
 6f8:	6000 ff54      	braw 0x64e
 6fc:	3742 0038      	movew %d2,%a3@(56)
 700:	6000 ff4c      	braw 0x64e
 704:	54ab 0006      	addql #2,%a3@(6)
 708:	43f9 0000 0ce4 	lea 0xce4,%a1
 70e:	4243           	clrw %d3
 710:	e34a           	lslw #1,%d2
 712:	1631 2000      	moveb %a1@(0000000000000000,%d2:w),%d3
 716:	5343           	subqw #1,%d3
 718:	3743 000e      	movew %d3,%a3@(14)
 71c:	9631 2001      	subb %a1@(0000000000000001,%d2:w),%d3
 720:	3743 0010      	movew %d3,%a3@(16)
 724:	4aab 0014      	tstl %a3@(20)
 728:	6700 00b2      	beqw 0x7dc
 72c:	4a6b 003a      	tstw %a3@(58)
 730:	670e           	beqs 0x740
 732:	0c6b 0001 003a 	cmpiw #1,%a3@(58)
 738:	6700 00a2      	beqw 0x7dc
 73c:	536b 003a      	subqw #1,%a3@(58)
 740:	4eba 00a8      	jsr %pc@(0x7ea)
 744:	4a43           	tstw %d3
 746:	6710           	beqs 0x758
 748:	2412           	movel %a2@,%d2
 74a:	d4aa 0004      	addl %a2@(4),%d2
 74e:	3803           	movew %d3,%d4
 750:	d1c2           	addal %d2,%a0
 752:	e38a           	lsll #1,%d2
 754:	5344           	subqw #1,%d4
 756:	66f8           	bnes 0x750
 758:	4a6b 0046      	tstw %a3@(70)
 75c:	6606           	bnes 0x764
 75e:	2c6b 0030      	moveal %a3@(48),%fp
 762:	2c88           	movel %a0,%fp@
 764:	2412           	movel %a2@,%d2
 766:	e7aa           	lsll %d3,%d2
 768:	d1c2           	addal %d2,%a0
 76a:	2748 0024      	movel %a0,%a3@(36)
 76e:	377c 0001 0012 	movew #1,%a3@(18)
 774:	2412           	movel %a2@,%d2
 776:	d4aa 0004      	addl %a2@(4),%d2
 77a:	e7aa           	lsll %d3,%d2
 77c:	e28a           	lsrl #1,%d2
 77e:	4a6b 0046      	tstw %a3@(70)
 782:	6606           	bnes 0x78a
 784:	2c6b 0034      	moveal %a3@(52),%fp
 788:	3c82           	movew %d2,%fp@
 78a:	242a 0004      	movel %a2@(4),%d2
 78e:	e7aa           	lsll %d3,%d2
 790:	e28a           	lsrl #1,%d2
 792:	3742 0022      	movew %d2,%a3@(34)
 796:	4a6b 0046      	tstw %a3@(70)
 79a:	6624           	bnes 0x7c0
 79c:	2c6b 0028      	moveal %a3@(40),%fp
 7a0:	302b 001e      	movew %a3@(30),%d0
 7a4:	4a79 0000 0d12 	tstw 0xd12
 7aa:	6604           	bnes 0x7b0
 7ac:	3c80           	movew %d0,%fp@
 7ae:	6010           	bras 0x7c0
 7b0:	e148           	lslw #8,%d0
 7b2:	3239 0000 0d14 	movew 0xd14,%d1
 7b8:	c0c1           	muluw %d1,%d0
 7ba:	e088           	lsrl #8,%d0
 7bc:	e088           	lsrl #8,%d0
 7be:	3c80           	movew %d0,%fp@
 7c0:	33fc 00ff 00df 	movew #255,0xdff09e
 7c6:	f09e 
 7c8:	33f9 0000 0a90 	movew 0xa90,0xdff096
 7ce:	00df f096 
 7d2:	33f9 0000 0a94 	movew 0xa94,0xdff09a
 7d8:	00df f09a 
 7dc:	3039 0000 0a96 	movew 0xa96,%d0
 7e2:	01f9 0000 0d0e 	bset %d0,0xd0e
 7e8:	4e75           	rts
 7ea:	206b 0018      	moveal %a3@(24),%a0
 7ee:	246b 0014      	moveal %a3@(20),%a2
 7f2:	4282           	clrl %d2
 7f4:	3401           	movew %d1,%d2
 7f6:	84eb 001c      	divuw %a3@(28),%d2
 7fa:	4243           	clrw %d3
 7fc:	162a 000e      	moveb %a2@(14),%d3
 800:	9642           	subw %d2,%d3
 802:	5343           	subqw #1,%d3
 804:	4a43           	tstw %d3
 806:	6c02           	bges 0x80a
 808:	4243           	clrw %d3
 80a:	927c 001b      	subw #27,%d1
 80e:	e549           	lslw #2,%d1
 810:	43f9 0000 0bc4 	lea 0xbc4,%a1
 816:	2231 1000      	movel %a1@(0000000000000000,%d1:w),%d1
 81a:	242a 0008      	movel %a2@(8),%d2
 81e:	e7aa           	lsll %d3,%d2
 820:	82c2           	divuw %d2,%d1
 822:	4a6b 0046      	tstw %a3@(70)
 826:	6606           	bnes 0x82e
 828:	2c6b 002c      	moveal %a3@(44),%fp
 82c:	3c81           	movew %d1,%fp@
 82e:	3741 0020      	movew %d1,%a3@(32)
 832:	3741 0042      	movew %d1,%a3@(66)
 836:	2c6b 003c      	moveal %a3@(60),%fp
 83a:	3d6e 001a 001c 	movew %fp@(26),%fp@(28)
 840:	376e 0016 0044 	movew %fp@(22),%a3@(68)
 846:	4e75           	rts
 848:	48e7 ffff      	moveml %d0-%sp,%sp@-
 84c:	287c 0000 8a8e 	moveal #35470,%a4
 852:	3039 00df f01e 	movew 0xdff01e,%d0
 858:	41f9 0000 0d3a 	lea 0xd3a,%a0
 85e:	323c 0007      	movew #7,%d1
 862:	343c 0001      	movew #1,%d2
 866:	363c 0080      	movew #128,%d3
 86a:	6142           	bsrs 0x8ae
 86c:	41f9 0000 0d84 	lea 0xd84,%a0
 872:	323c 0008      	movew #8,%d1
 876:	343c 0002      	movew #2,%d2
 87a:	363c 0100      	movew #256,%d3
 87e:	612e           	bsrs 0x8ae
 880:	41f9 0000 0dce 	lea 0xdce,%a0
 886:	323c 0009      	movew #9,%d1
 88a:	343c 0004      	movew #4,%d2
 88e:	363c 0200      	movew #512,%d3
 892:	611a           	bsrs 0x8ae
 894:	41f9 0000 0e18 	lea 0xe18,%a0
 89a:	323c 000a      	movew #10,%d1
 89e:	343c 0008      	movew #8,%d2
 8a2:	363c 0400      	movew #1024,%d3
 8a6:	6106           	bsrs 0x8ae
 8a8:	4cdf ffff      	moveml %sp@+,%d0-%sp
 8ac:	4e73           	rte
 8ae:	0300           	btst %d1,%d0
 8b0:	675c           	beqs 0x90e
 8b2:	4a68 0046      	tstw %a0@(70)
 8b6:	665e           	bnes 0x916
 8b8:	4a68 0012      	tstw %a0@(18)
 8bc:	6d50           	blts 0x90e
 8be:	670c           	beqs 0x8cc
 8c0:	4a68 0022      	tstw %a0@(34)
 8c4:	6632           	bnes 0x8f8
 8c6:	4268 0012      	clrw %a0@(18)
 8ca:	6042           	bras 0x90e
 8cc:	5f41           	subqw #7,%d1
 8ce:	03b9 0000 0d12 	bclr %d1,0xd12
 8d4:	2268 0028      	moveal %a0@(40),%a1
 8d8:	4251           	clrw %a1@
 8da:	2268 002c      	moveal %a0@(44),%a1
 8de:	32bc 007c      	movew #124,%a1@
 8e2:	33c2 00df f096 	movew %d2,0xdff096
 8e8:	317c ffff 0012 	movew #-1,%a0@(18)
 8ee:	4268 0048      	clrw %a0@(72)
 8f2:	4268 0046      	clrw %a0@(70)
 8f6:	6016           	bras 0x90e
 8f8:	2268 0034      	moveal %a0@(52),%a1
 8fc:	32a8 0022      	movew %a0@(34),%a1@
 900:	2268 0030      	moveal %a0@(48),%a1
 904:	22a8 0024      	movel %a0@(36),%a1@
 908:	317c ffff 0012 	movew #-1,%a0@(18)
 90e:	33c3 00df f09c 	movew %d3,0xdff09c
 914:	4e75           	rts
 916:	0c68 ffff 0048 	cmpiw #-1,%a0@(72)
 91c:	67f0           	beqs 0x90e
 91e:	4a68 0048      	tstw %a0@(72)
 922:	67a8           	beqs 0x8cc
 924:	5368 0048      	subqw #1,%a0@(72)
 928:	60e4           	bras 0x90e
 92a:	48e7 ffff      	moveml %d0-%sp,%sp@-
 92e:	2079 0000 0e62 	moveal 0xe62,%a0
 934:	4eba f968      	jsr %pc@(0x29e)
 938:	4a40           	tstw %d0
 93a:	6604           	bnes 0x940
 93c:	4eba f93e      	jsr %pc@(0x27c)
 940:	4cdf ffff      	moveml %sp@+,%d0-%sp
 944:	4e75           	rts
 946:	48e7 ffff      	moveml %d0-%sp,%sp@-
 94a:	2042           	moveal %d2,%a0
 94c:	e541           	aslw #2,%d1
 94e:	2070 1000      	moveal %a0@(0000000000000000,%d1:w),%a0
 952:	23c8 0000 0e62 	movel %a0,0xe62
 958:	d1fc 0000 0010 	addal #16,%a0
 95e:	23c8 0000 0e66 	movel %a0,0xe66
 964:	5888           	addql #4,%a0
 966:	2250           	moveal %a0@,%a1
 968:	b3fc 0000 0000 	cmpal #0,%a1
 96e:	6726           	beqs 0x996
 970:	2469 000a      	moveal %a1@(10),%a2
 974:	b5fc 0000 0000 	cmpal #0,%a2
 97a:	67e8           	beqs 0x964
 97c:	611e           	bsrs 0x99c
 97e:	228a           	movel %a2,%a1@
 980:	4240           	clrw %d0
 982:	102a 000e      	moveb %a2@(14),%d0
 986:	7253           	moveq #83,%d1
 988:	82c0           	divuw %d0,%d1
 98a:	3341 0008      	movew %d1,%a1@(8)
 98e:	611c           	bsrs 0x9ac
 990:	234a 0004      	movel %a2,%a1@(4)
 994:	60ce           	bras 0x964
 996:	4cdf ffff      	moveml %sp@+,%d0-%sp
 99a:	4e75           	rts
 99c:	0c92 5648 4452 	cmpil #1447576658,%a2@
 9a2:	6704           	beqs 0x9a8
 9a4:	548a           	addql #2,%a2
 9a6:	60f4           	bras 0x99c
 9a8:	508a           	addql #8,%a2
 9aa:	4e75           	rts
 9ac:	0c92 424f 4459 	cmpil #1112491097,%a2@
 9b2:	6704           	beqs 0x9b8
 9b4:	548a           	addql #2,%a2
 9b6:	60f4           	bras 0x9ac
 9b8:	508a           	addql #8,%a2
 9ba:	4e75           	rts
 9bc:	2f0e           	movel %fp,%sp@-
 9be:	4279 0000 0d0c 	clrw 0xd0c
 9c4:	42b9 0000 0d0e 	clrl 0xd0e
 9ca:	43f9 0000 0a9c 	lea 0xa9c,%a1
 9d0:	2c78 0004      	moveal 0x4,%fp
 9d4:	4eae fe0e      	jsr %fp@(-498)
 9d8:	23c0 0000 0a98 	movel %d0,0xa98
 9de:	41f9 0000 0aaa 	lea 0xaaa,%a0
 9e4:	117c 0002 0008 	moveb #2,%a0@(8)
 9ea:	117c 0000 0009 	moveb #0,%a0@(9)
 9f0:	43f9 0000 0ac0 	lea 0xac0,%a1
 9f6:	2149 000a      	movel %a1,%a0@(10)
 9fa:	217c 0000 0000 	movel #0,%a0@(14)
 a00:	000e 
 a02:	43fa f8a2      	lea %pc@(0x2a6),%a1
 a06:	2149 0012      	movel %a1,%a0@(18)
 a0a:	2c79 0000 0a98 	moveal 0xa98,%fp
 a10:	7000           	moveq #0,%d0
 a12:	43f9 0000 0aaa 	lea 0xaaa,%a1
 a18:	4eae fffa      	jsr %fp@(-6)
 a1c:	13fc 0001 00bf 	moveb #1,0xbfee01
 a22:	ee01 
 a24:	33fc 0780 00df 	movew #1920,0xdff09a
 a2a:	f09a 
 a2c:	23f8 0070 0000 	movel 0x70,0xad0
 a32:	0ad0 
 a34:	43fa fe12      	lea %pc@(0x848),%a1
 a38:	21c9 0070      	movel %a1,0x70
 a3c:	33fc 0780 00df 	movew #1920,0xdff01e
 a42:	f01e 
 a44:	33fc 8780 00df 	movew #-30848,0xdff09a
 a4a:	f09a 
 a4c:	2c5f           	moveal %sp@+,%fp
 a4e:	4e75           	rts
 a50:	2f0e           	movel %fp,%sp@-
 a52:	2c79 0000 0a98 	moveal 0xa98,%fp
 a58:	7000           	moveq #0,%d0
 a5a:	43f9 0000 0aaa 	lea 0xaaa,%a1
 a60:	4eae fff4      	jsr %fp@(-12)
 a64:	33fc 0780 00df 	movew #1920,0xdff09a
 a6a:	f09a 
 a6c:	33fc 0780 00df 	movew #1920,0xdff01e
 a72:	f01e 
 a74:	33fc 000f 00df 	movew #15,0xdff096
 a7a:	f096 
 a7c:	21f9 0000 0ad0 	movel 0xad0,0x70
 a82:	0070 
 a84:	2c5f           	moveal %sp@+,%fp
 a86:	4e75           	rts
	...
 a9c:	6369           	blss 0xb07
 a9e:	6161           	bsrs 0xb01
 aa0:	2e72 6573 6f75 	moveal %a2@(000000006f757263)@(0000000065000000),%sp
 aa6:	7263 6500 0000 
	...
 ac0:	4d75           	.short 0x4d75
 ac2:	7369           	.short 0x7369
 ac4:	6320           	blss 0xae6
 ac6:	5469 6d65      	addqw #2,%a1@(28005)
 aca:	7249           	moveq #73,%d1
 acc:	6e74           	bgts 0xb42
 ace:	0000 0000      	orib #0,%d0
 ad2:	0000 0006      	orib #6,%d0
 ad6:	ae40           	.short 0xae40
 ad8:	0006 4e40      	orib #64,%d6
 adc:	0005 f3a8      	orib #-88,%d5
 ae0:	0005 9e24      	orib #36,%d5
 ae4:	0005 4d6c      	orib #108,%d5
 ae8:	0005 013c      	orib #60,%d5
 aec:	0004 b954      	orib #84,%d4
 af0:	0004 7574      	orib #116,%d4
 af4:	0004 3564      	orib #100,%d4
 af8:	0003 f8ec      	orib #-20,%d3
 afc:	0003 bfd8      	orib #-40,%d3
 b00:	0003 89f8      	orib #-8,%d3
 b04:	0003 5720      	orib #32,%d3
 b08:	0003 2720      	orib #32,%d3
 b0c:	0002 f9d4      	orib #-44,%d2
 b10:	0002 cf12      	orib #18,%d2
 b14:	0002 a6b6      	orib #-74,%d2
 b18:	0002 809e      	orib #-98,%d2
 b1c:	0002 5caa      	orib #-86,%d2
 b20:	0002 3aba      	orib #-70,%d2
 b24:	0002 1ab2      	orib #-78,%d2
 b28:	0001 fc76      	orib #118,%d1
 b2c:	0001 dfec      	orib #-20,%d1
 b30:	0001 c4fc      	orib #-4,%d1
 b34:	0001 ab90      	orib #-112,%d1
 b38:	0001 9390      	orib #-112,%d1
 b3c:	0001 7cea      	orib #-22,%d1
 b40:	0001 6789      	orib #-119,%d1
 b44:	0001 535b      	orib #91,%d1
 b48:	0001 404f      	orib #79,%d1
 b4c:	0001 2e55      	orib #85,%d1
 b50:	0001 1d5d      	orib #93,%d1
 b54:	0001 0d59      	orib #89,%d1
 b58:	0000 fe3b      	orib #59,%d0
 b5c:	0000 eff6      	orib #-10,%d0
 b60:	0000 e27e      	orib #126,%d0
 b64:	0000 d5c8      	orib #-56,%d0
 b68:	0000 c9c8      	orib #-56,%d0
 b6c:	0000 be75      	orib #117,%d0
 b70:	0000 b3c4      	orib #-60,%d0
 b74:	0000 a9ad      	orib #-83,%d0
 b78:	0000 a027      	orib #39,%d0
 b7c:	0000 972a      	orib #42,%d0
 b80:	0000 8eae      	orib #-82,%d0
 b84:	0000 86ac      	orib #-84,%d0
 b88:	0000 7f1d      	orib #29,%d0
 b8c:	0000 77fb      	orib #-5,%d0
 b90:	0000 713f      	orib #63,%d0
 b94:	0000 6ae4      	orib #-28,%d0
 b98:	0000 64e4      	orib #-28,%d0
 b9c:	0000 5f3a      	orib #58,%d0
 ba0:	0000 59e2      	orib #-30,%d0
 ba4:	0000 54d7      	orib #-41,%d0
 ba8:	0000 5014      	orib #20,%d0
 bac:	0000 4b95      	orib #-107,%d0
 bb0:	0000 4757      	orib #87,%d0
 bb4:	0000 4356      	orib #86,%d0
 bb8:	0000 3f8f      	orib #-113,%d0
 bbc:	0000 3bfd      	orib #-3,%d0
 bc0:	0000 38a0      	orib #-96,%d0
 bc4:	0000 3572      	orib #114,%d0
 bc8:	0000 3272      	orib #114,%d0
 bcc:	0000 2f9d      	orib #-99,%d0
 bd0:	0000 2cf1      	orib #-15,%d0
 bd4:	0000 2a6b      	orib #107,%d0
 bd8:	0000 280a      	orib #10,%d0
 bdc:	0000 25cb      	orib #-53,%d0
 be0:	0000 23ac      	orib #-84,%d0
 be4:	0000 21ab      	orib #-85,%d0
 be8:	0000 1fc7      	orib #-57,%d0
 bec:	0000 1dff      	orib #-1,%d0
 bf0:	0000 1c50      	orib #80,%d0
 bf4:	0000 1ab9      	orib #-71,%d0
 bf8:	0000 1939      	orib #57,%d0
 bfc:	0000 17cf      	orib #-49,%d0
 c00:	0000 1679      	orib #121,%d0
 c04:	0000 1536      	orib #54,%d0
 c08:	0000 1405      	orib #5,%d0
 c0c:	0000 12e5      	orib #-27,%d0
 c10:	0000 11d6      	orib #-42,%d0
 c14:	0000 10d6      	orib #-42,%d0
 c18:	0000 0fe4      	orib #-28,%d0
 c1c:	0000 0eff      	orib #-1,%d0
 c20:	0000 0e28      	orib #40,%d0
 c24:	0000 0d5c      	orib #92,%d0
 c28:	0000 0c9d      	orib #-99,%d0
 c2c:	0000 0be7      	orib #-25,%d0
 c30:	0000 0b3c      	orib #60,%d0
 c34:	0000 0a9b      	orib #-101,%d0
 c38:	0000 0a02      	orib #2,%d0
 c3c:	0000 0973      	orib #115,%d0
 c40:	0000 08eb      	orib #-21,%d0
 c44:	0000 086b      	orib #107,%d0
 c48:	0000 07f2      	orib #-14,%d0
 c4c:	0000 0780      	orib #-128,%d0
 c50:	0000 0714      	orib #20,%d0
 c54:	0000 06ae      	orib #-82,%d0
 c58:	0000 064e      	orib #78,%d0
 c5c:	0000 05f4      	orib #-12,%d0
 c60:	0000 059e      	orib #-98,%d0
 c64:	0000 054d      	orib #77,%d0
 c68:	0000 0501      	orib #1,%d0
 c6c:	0000 04b9      	orib #-71,%d0
 c70:	0000 0475      	orib #117,%d0
 c74:	0000 0435      	orib #53,%d0
 c78:	0000 03f9      	orib #-7,%d0
 c7c:	0000 03c0      	orib #-64,%d0
 c80:	0000 038a      	orib #-118,%d0
 c84:	0000 0357      	orib #87,%d0
 c88:	0000 0327      	orib #39,%d0
 c8c:	0000 02fa      	orib #-6,%d0
 c90:	0000 02cf      	orib #-49,%d0
 c94:	0000 02a7      	orib #-89,%d0
 c98:	0000 0281      	orib #-127,%d0
 c9c:	0000 025d      	orib #93,%d0
 ca0:	0000 023b      	orib #59,%d0
 ca4:	0000 021b      	orib #27,%d0
 ca8:	0000 01fc      	orib #-4,%d0
 cac:	0000 01e0      	orib #-32,%d0
 cb0:	0000 01c5      	orib #-59,%d0
 cb4:	0000 01ab      	orib #-85,%d0
 cb8:	0000 0193      	orib #-109,%d0
 cbc:	0000 017d      	orib #125,%d0
 cc0:	0000 0167      	orib #103,%d0
 cc4:	0000 0153      	orib #83,%d0
 cc8:	0000 0140      	orib #64,%d0
 ccc:	0000 012e      	orib #46,%d0
 cd0:	0000 011d      	orib #29,%d0
 cd4:	0000 010d      	orib #13,%d0
 cd8:	0000 00fe      	orib #-2,%d0
 cdc:	0000 00f0      	orib #-16,%d0
 ce0:	0000 00e2      	orib #-30,%d0
 ce4:	6056           	bras 0xd3c
 ce6:	302b 201c      	movew %a3@(8220),%d0
 cea:	403a           	.short 0x403a
 cec:	1815           	moveb %a5@,%d4
 cee:	4840           	swap %d0
 cf0:	0c0a           	.short 0x0c0a
 cf2:	544b           	addqw #2,%a3
 cf4:	3c36 2420      	movew %fp@(0000000000000020,%d2:w:4),%d6
 cf8:	0605 5a51      	addib #81,%d5
 cfc:	4e46           	trap #6
 cfe:	423b           	.short 0x423b
 d00:	3630 2a26      	movew %a0@(0000000000000026,%d2:l:2),%d3
 d04:	1e1b           	moveb %a3@+,%d7
 d06:	1210           	moveb %a0@,%d1
 d08:	0807 100e      	btst #14,%d7
	...
 d2c:	0d3a 0000      	btst %d6,%pc@(0xd2e)
 d30:	0d84           	bclr %d6,%d4
 d32:	0000 0dce      	orib #-50,%d0
 d36:	0000 0e18      	orib #24,%d0
	...
 d56:	0000 0020      	orib #32,%d0
 d5a:	007c 0000      	oriw #0,%sr
 d5e:	0000 0000      	orib #0,%d0
 d62:	00df           	.short 0x00df
 d64:	f0a8           	.short 0xf0a8
 d66:	00df           	.short 0x00df
 d68:	f0a6           	.short 0xf0a6
 d6a:	00df           	.short 0x00df
 d6c:	f0a0           	.short 0xf0a0
 d6e:	00df           	.short 0x00df
 d70:	f0a4           	.short 0xf0a4
	...
 da2:	0020 007c      	orib #124,%a0@-
 da6:	0000 0000      	orib #0,%d0
 daa:	0000 00df      	orib #-33,%d0
 dae:	f0b8           	.short 0xf0b8
 db0:	00df           	.short 0x00df
 db2:	f0b6           	.short 0xf0b6
 db4:	00df           	.short 0x00df
 db6:	f0b0           	.short 0xf0b0
 db8:	00df           	.short 0x00df
 dba:	f0b4           	.short 0xf0b4
	...
 dec:	0020 007c      	orib #124,%a0@-
 df0:	0000 0000      	orib #0,%d0
 df4:	0000 00df      	orib #-33,%d0
 df8:	f0c8 00df f0c6 	pbws 0xdffec0
 dfe:	00df           	.short 0x00df
 e00:	f0c0 00df f0c4 	pbbs 0xdffec6
	...
 e36:	0020 007c      	orib #124,%a0@-
 e3a:	0000 0000      	orib #0,%d0
 e3e:	0000 00df      	orib #-33,%d0
 e42:	f0d8           	.short 0xf0d8
 e44:	00df           	.short 0x00df
 e46:	f0d6           	.short 0xf0d6
 e48:	00df           	.short 0x00df
 e4a:	f0d0           	.short 0xf0d0
 e4c:	00df           	.short 0x00df
 e4e:	f0d4           	.short 0xf0d4
	...
