#!/usr/bin/env python3
"""ladiff.py A.BIN B.BIN : compare two LADUMP.PRG dumps (ladump.c): line-A words by offset (EmuTOS names where known),
system variables $44a..$461, video registers, palette."""
import sys
NAMES = {-602: 'GCURX', -600: 'GCURY', -598: 'HIDE_CNT', -596: 'MOUSE_BT', -464: 'CUR_WORK.hi', -462: 'CUR_WORK.lo',
         -460: 'def_font.hi', -458: 'def_font.lo', -906: 'CUR_FONT.hi', -904: 'CUR_FONT.lo', -348: 'cur_ms_stat',
         -346: 'disab_cnt', -344: 'newx', -342: 'newy', -340: 'draw_flag/mouse_flag', -338: 'sav_cur_x',
         -336: 'sav_cur_y', -330: 'save_len', -328: 'save_addr.hi', -326: 'save_addr.lo', -324: 'save_stat',
         -46: 'v_cel_ht', -44: 'v_cel_mx', -42: 'v_cel_my', -40: 'v_cel_wr', -38: 'v_col_bg', -36: 'v_col_fg',
         -34: 'v_cur_ad.hi', -32: 'v_cur_ad.lo', -30: 'v_cur_of', -28: 'v_cur_cx', -26: 'v_cur_cy', -24: 'v_period/tim',
         -22: 'v_fnt_ad.hi', -20: 'v_fnt_ad.lo', -18: 'v_fnt_nd', -16: 'v_fnt_st', -14: 'v_fnt_wr', -12: 'V_REZ_HZ',
         -10: 'v_off_ad.hi', -8: 'v_off_ad.lo', -6: 'v_stat_0', -4: 'V_REZ_VT', -2: 'BYTES_LIN', 0: 'v_planes',
         2: 'v_lin_wr'}
for o in range(-852, -846, 2): NAMES.setdefault(o, 'mouse cdb')
for o in range(-692, -602, 2): NAMES[o] = 'DEV_TAB[%d] (v_opnwk)' % ((o + 692) // 2)
for o in range(-782, -692, 2): NAMES[o] = 'INQ_TAB[%d] (vq_extnd)' % ((o + 782) // 2)
SYS = {0x44a: 'palmode?', 0x44c: 'sshiftmd', 0x44e: '_v_bas_ad', 0x452: 'vblsem', 0x454: 'nvbls', 0x456: '_vblqueue',
       0x45a: 'colorptr', 0x45e: 'screenpt'}
REGS = ['8201', '8203', '8205', '8207', '8209', '820a', '820d', '820f', '8260', '8265']
a, b = (open(f, 'rb').read() for f in sys.argv[1:3])
print('line-A (offset from the base), word: A -> B')
for i in range(0, 0x400, 2):
    if a[i:i + 2] != b[i:i + 2]:
        o = i - 0x3a0
        print('  %5d (%s%03x)  %04x -> %04x  %s' % (o, '-' if o < 0 else '+', abs(o), int.from_bytes(a[i:i + 2], 'big'),
              int.from_bytes(b[i:i + 2], 'big'), NAMES.get(o, '')))
print('system variables, byte:')
for k in range(0x18):
    if a[0x400 + k] != b[0x400 + k]:
        ad = 0x44a + k
        nm = next((v for s, v in sorted(SYS.items()) if s <= ad), '')
        print('  $%03x  %02x -> %02x  (%s)' % (ad, a[0x400 + k], b[0x400 + k], nm))
print('video registers:')
for k, r in enumerate(REGS):
    x, y = a[0x418 + k], b[0x418 + k]
    print('  $ffff%s  %02x -> %02x%s' % (r, x, y, '' if x == y else '   <-'))
print('palette:', ' '.join('%04x' % int.from_bytes(a[0x424 + 2 * k:0x426 + 2 * k], 'big') for k in range(16)))
print('     ->  ', ' '.join('%04x' % int.from_bytes(b[0x424 + 2 * k:0x426 + 2 * k], 'big') for k in range(16)))
