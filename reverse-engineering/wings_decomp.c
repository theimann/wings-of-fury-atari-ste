// ==== entry @ 00010000 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void entry(void)

{
  int iVar1;
  undefined4 uVar2;
  short sVar3;
  undefined4 extraout_A0;
  undefined4 *puVar4;
  
  uVar2 = FUN_00021fa0();
  sVar3 = 0x4e3;
  puVar4 = &DAT_00026bb0;
  do {
    *puVar4 = 0;
    iVar1 = _DAT_00000004;
    sVar3 = sVar3 + -1;
    puVar4 = puVar4 + 1;
  } while (sVar3 != -1);
  DAT_00026ec4 = _DAT_00000004;
  DAT_00027f02 = (undefined1 *)register0x0000003c;
  if ((*(byte *)(_DAT_00000004 + 0x129) & 0x10) != 0) {
    (**(code **)(_DAT_00000004 + -0x1e))(uVar2,extraout_A0);
  }
  DAT_00026e6e = (**(code **)(iVar1 + -0x198))();
  if (DAT_00026e6e == 0) {
    (**(code **)(iVar1 + -0x6c))();
  }
  else {
    FUN_00021fa8();
  }
  return;
}


// ==== FUN_00010006 @ 00010006 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00010006(undefined4 param_1)

{
  short sVar1;
  char cVar2;
  
  DAT_00bfe001 = DAT_00bfe001 | 2;
  (*_thunk_FUN_0001aa50)();
  FUN_00012570();
  (**(code **)(DAT_00026e76 + -0x4e))();
  DAT_0002459e = 0xff;
  FUN_00012910();
  DAT_00024bfc = 0xffff;
  if (1 < param_1._0_2_) {
    DAT_00026ed6 = &DAT_000233a8;
  }
  (*_thunk_FUN_0001ccb6)();
  FUN_00016670();
  DAT_00026dd6 = (undefined1 *)register0x0000003c;
  FUN_000134bc();
  (*_thunk_FUN_00018022)();
LAB_00010066:
  do {
    FUN_00011234();
    DAT_00025447 = 0;
    DAT_00025510 = '\0';
    DAT_00026c9c = 0;
    DAT_00026c94 = 0;
    DAT_000254f0._0_1_ = 0;
    DAT_00025504._0_1_ = 0;
    FUN_00013562();
    DAT_000252b2 = 0;
    _DAT_00025312 = 0;
    DAT_00025511 = 0;
    DAT_000252cf = 0;
    (*_thunk_FUN_00018262)();
    FUN_0001653c();
    if (DAT_00026c90 == 0) {
      (*_thunk_FUN_00012adc)();
    }
    sVar1 = (*_thunk_FUN_00018590)();
  } while (sVar1 != 0);
  (*_thunk_FUN_0001edaa)();
  (*_thunk_FUN_00018806)();
  (*_thunk_FUN_00013252)();
  FUN_0001535a();
  (*_thunk_FUN_00013368)();
  if (DAT_00026c90 != 0) goto LAB_000100ea;
  do {
    FUN_000135a8();
    FUN_00013684();
    DAT_000254a6 = '\0';
    DAT_00026c8c = 0;
    DAT_00026c92 = 0;
LAB_000100ea:
    DAT_0002459e = 0;
    DAT_00026c90 = 0;
    (*_thunk_FUN_00011386)();
    (*_thunk_FUN_0001174a)();
    if (DAT_00026c9c != 0) {
      DAT_00026c94 = 2;
    }
    DAT_00026ca4 = CONCAT11(0xff,(undefined1)DAT_00026ca4);
LAB_0001010e:
    (*_thunk_FUN_0001ccf6)();
    if (DAT_00025312 != '\0') {
LAB_000101c6:
      (*_thunk_FUN_00011f4e)();
      FUN_00016bbc();
      FUN_000173e6();
      DAT_00026ca4 = 0;
      DAT_00026edc = -(DAT_00026c9c == 1);
      (*_thunk_FUN_0001852a)();
      if (_DAT_00026ed0 != 0) {
        DAT_00bfe001 = DAT_00bfe001 & 0xfd;
        FUN_00012470();
        FUN_00011234();
        FUN_000134d8();
        return;
      }
      DAT_0002459e = 0xff;
      DAT_00025706 = 0;
      if (DAT_00026edc == '\0') {
        FUN_00011234();
        (*_thunk_FUN_00019856)();
      }
      goto LAB_00010066;
    }
    if (DAT_000254a6 != '\0') {
      (*_thunk_FUN_0001aa32)();
      goto LAB_0001010e;
    }
    if ((DAT_000252b4 == '\0') || (DAT_0002530c == 0)) {
      FUN_00010228();
      FUN_000114d8();
      if (DAT_00025510 != '\0') goto LAB_00010066;
      if (((DAT_00026c9c == 1) && (sVar1 = (*_thunk_FUN_0002044c)(), sVar1 != 0)) ||
         (DAT_00025312 != '\0')) goto LAB_000101c6;
      goto LAB_0001010e;
    }
    DAT_0002530c = 0;
    DAT_000252b4 = '\0';
    (*_thunk_FUN_00011f4e)();
    DAT_00025706 = 0;
    FUN_00016bbc();
    FUN_000173e6();
    FUN_00011234();
    if (DAT_000252ad != '\0') {
      DAT_000252ac = DAT_000252ac + '\x01';
    }
    FUN_000111fc();
    (*_thunk_FUN_0001edaa)();
    (*_thunk_FUN_00012adc)();
    cVar2 = (*_thunk_FUN_00018590)();
    if (cVar2 != '\0') goto LAB_00010066;
    FUN_0001653c();
    (*_thunk_FUN_00018806)();
    (*_thunk_FUN_00013252)();
    FUN_0001535a();
    (*_thunk_FUN_00013368)();
  } while( true );
}


// ==== FUN_0001020e @ 0001020e ====

void FUN_0001020e(void)

{
  DAT_00bfe001 = DAT_00bfe001 & 0xfd;
  FUN_00012470();
  FUN_00011234();
  FUN_000134d8();
  return;
}


// ==== FUN_00010228 @ 00010228 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00010228(void)

{
  ushort uVar1;
  ushort uVar2;
  undefined2 uVar3;
  
  (*_thunk_FUN_0001aa3e)();
  DAT_000252f6 = DAT_000252f6 + 1;
  if (10 < DAT_000252f6) {
    DAT_000252f6 = 0;
  }
  (*_thunk_FUN_0001524a)();
  (*_thunk_FUN_0002124a)();
  FUN_00010f88();
  DAT_00024e84 = 0;
  if (DAT_00024e86 == 1) {
    DAT_00024e84 = 3;
  }
  DAT_00024e80 = DAT_00026dac + (-0xa0 << DAT_00024e84);
  if (DAT_00024e86 == 1) {
    DAT_000252f0 = 0x97;
    DAT_00024e82 = 0x4b8;
  }
  else {
    DAT_000252f0 = 0x97;
    DAT_00024e82 = DAT_000252f0;
    if (0x83 < DAT_00026db0) {
      DAT_000252f0 = DAT_00026db0 + 0x14;
      DAT_00024e82 = DAT_000252f0;
    }
  }
  (*_thunk_FUN_0001876e)();
  if (DAT_00024e74 != '\0') {
    DAT_0002542c = 0xffff;
    FUN_000135d8();
    DAT_00024e74 = '\0';
  }
  (*_thunk_FUN_00013772)();
  FUN_00010ee0();
  (*_thunk_FUN_00013eee)();
  (*_thunk_FUN_000152f8)();
  FUN_000106be();
  FUN_00010344();
  (*_thunk_FUN_0001557c)();
  FUN_000110c2();
  (*_thunk_FUN_0001f2dc)();
  (*_thunk_FUN_0002124a)();
  (*_thunk_FUN_0001417e)();
  (*_thunk_FUN_0001ee16)();
  DAT_00026d8c = 0xff;
  uVar3 = *(undefined2 *)(*(int *)(DAT_00026d70 + 0x98) + 2);
  if ((DAT_00025366 != 0) &&
     (uVar1 = DAT_00025366 - 1, uVar2 = DAT_00025366 & 1, DAT_00025366 = uVar1, uVar2 != 0)) {
    uVar3 = DAT_00025368;
  }
  *(undefined2 *)(*(int *)(DAT_00026d7c + 2) + 0x92) = uVar3;
  (*_thunk_FUN_000150b0)();
  return;
}


// ==== FUN_0001030c @ 0001030c ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0001030c(void)

{
  ushort uVar1;
  ushort uVar2;
  undefined2 uVar3;
  
  uVar3 = *(undefined2 *)(*(int *)(DAT_00026d70 + 0x98) + 2);
  if ((DAT_00025366 != 0) &&
     (uVar1 = DAT_00025366 - 1, uVar2 = DAT_00025366 & 1, DAT_00025366 = uVar1, uVar2 != 0)) {
    uVar3 = DAT_00025368;
  }
  *(undefined2 *)(*(int *)(DAT_00026d7c + 2) + 0x92) = uVar3;
  (*_thunk_FUN_000150b0)();
  return;
}


// ==== FUN_00010344 @ 00010344 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00010344(void)

{
  if ((DAT_000252b4 != '\0') && (DAT_0002530c == 0)) {
    (*_thunk_FUN_000212ce)();
    (*_thunk_FUN_00020b0c)();
    (*_thunk_FUN_00020b0c)();
    (*_thunk_FUN_000212d4)();
  }
  return;
}


// ==== FUN_000103a6 @ 000103a6 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_000103a6(void)

{
  byte bVar1;
  undefined2 uVar2;
  undefined4 uVar3;
  short sVar4;
  undefined2 extraout_D1w;
  ushort uVar5;
  short sVar6;
  ushort *puVar7;
  
  uVar2 = DAT_000268ae;
  if ((((DAT_00024fd4 == 1) || (DAT_00024fd4 == 7)) || (DAT_00024fd4 == 0xb)) || (DAT_00024fd4 == 8)
     ) {
LAB_0001045c:
    DAT_00026db0 = DAT_00024fc8;
  }
  else {
    if (DAT_000252e4 == 1) {
      return;
    }
    if ((DAT_00024e84 != 0) || ((short)DAT_00026dac < 0)) goto LAB_0001045c;
    puVar7 = (ushort *)((short)((DAT_00026dac >> 3) * 2) + DAT_00024578);
    if ((puVar7 < DAT_0002457c) && ((*puVar7 & 3) == 1)) {
      (*_thunk_FUN_0001cbf2)(puVar7);
    }
  }
  DAT_000268ae = 0xa1;
  uVar3 = DAT_00024fcc;
  if (DAT_00024e86 != 1) goto LAB_000104f6;
  if (DAT_00026ec8 == 0) {
    sVar6 = -DAT_00026ecc >> 2;
    if (sVar6 < -2) {
      sVar6 = -2;
    }
    if (-1 < DAT_00026eca) {
      sVar6 = sVar6 + 6;
    }
    sVar6 = sVar6 + 0x2a;
  }
  else {
    uVar5 = DAT_00026ec8;
    if (8 < DAT_00026ec8) {
      if (DAT_00026ec8 < 0x12) {
        sVar4 = DAT_00026eca;
        if (0xd < DAT_00026ec8) {
          sVar4 = -DAT_00026eca;
        }
        sVar6 = DAT_00026ec8 + 0x2f;
        if (-1 < sVar4) {
          sVar6 = DAT_00026ec8 + 0x38;
        }
        goto LAB_000104e2;
      }
      uVar5 = 0x1a - DAT_00026ec8;
    }
    sVar4 = (short)(uVar5 - 1) >> 2;
    sVar6 = sVar4 + 0x34;
    if (-1 < DAT_00026eca) {
      sVar6 = sVar4 + 0x36;
    }
  }
LAB_000104e2:
  uVar3 = *(undefined4 *)(DAT_00026dc6 + (short)(sVar6 << 2));
LAB_000104f6:
  (*_thunk_FUN_0001526e)(uVar3);
  if ((((DAT_00026ec8 == 0) && (DAT_000252f4 == 2)) && (DAT_000252bd != '\0')) &&
     (DAT_00024e84 == 0)) {
    (*_thunk_FUN_00020ce2)();
  }
  if (((DAT_00026ec8 == 0) && (DAT_00024e84 == 0)) &&
     ((DAT_00024fd4 == 0 || ((DAT_00024fd4 == 7 || (DAT_000259ec != 0)))))) {
    if (DAT_0002529a != DAT_0002535a) {
      if (DAT_0002529a < DAT_0002535a) {
        DAT_0002529a = DAT_0002529a + 2;
      }
      DAT_0002529a = DAT_0002529a + -1;
    }
    (*_thunk_FUN_00020ce2)();
  }
  (*_thunk_FUN_00020ce2)();
  if (DAT_00024fd4 == 7) {
    (*_thunk_FUN_00021318)(extraout_D1w);
  }
  if ((((DAT_00026ec8 != 0) && (DAT_000252f4 == 2)) && (DAT_000252bd != '\0')) &&
     (DAT_00024e84 == 0)) {
    (*_thunk_FUN_00020ce2)();
  }
  uVar3 = (*_thunk_FUN_0001524a)();
  if (((DAT_000252ba != 0) && (DAT_00026ec8 == 0)) &&
     ((DAT_00024e86 != 1 &&
      (bVar1 = DAT_000252d8 + 1, DAT_000252d8 = bVar1 & 3,
      (&DAT_00024b58)[(short)((ushort)CONCAT31((int3)((uint)uVar3 >> 8),bVar1) & 0xff03)] != '\0')))
     ) {
    (*_thunk_FUN_00020e24)();
  }
  DAT_000268ae = uVar2;
  return;
}


// ==== FUN_000106be @ 000106be ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_000106be(void)

{
  short sVar1;
  undefined2 *puVar2;
  
  (*_thunk_FUN_000212ce)();
  if (DAT_000252bc != '\0') {
    DAT_000252bc = '\0';
  }
  puVar2 = &DAT_00024bfe;
  sVar1 = 0xe;
  do {
    if (*(char *)(puVar2 + 6) != '\0') {
      FUN_00010702();
    }
    puVar2 = puVar2 + 0x15;
    sVar1 = sVar1 + -1;
  } while (sVar1 != -1);
  if (DAT_000254f0._0_1_ != '\0') {
    FUN_00010702();
  }
  (*_thunk_FUN_000212d4)();
  return;
}


// ==== FUN_00010702 @ 00010702 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00010702(void)

{
  char cVar1;
  int unaff_A2;
  
  if (((*(short *)(unaff_A2 + 0x22) == 1) || (*(short *)(unaff_A2 + 0x22) != 2)) ||
     (*(char *)(unaff_A2 + 0x1e) != '\n')) {
    if (*(char *)(unaff_A2 + 0xc) == '\b') {
      cVar1 = *(char *)(unaff_A2 + 0x21) + '\x01';
      if (cVar1 == '\b') {
        *(undefined1 *)(unaff_A2 + 0x20) = 0;
        *(undefined1 *)(unaff_A2 + 0x21) = 0;
        return;
      }
      *(char *)(unaff_A2 + 0x21) = cVar1;
    }
    (*_thunk_FUN_00015174)();
  }
  return;
}


// ==== FUN_000107f2 @ 000107f2 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_000107f2(void)

{
  short sVar2;
  undefined1 uVar4;
  int iVar1;
  ushort uVar3;
  char cVar5;
  undefined4 *puVar6;
  int extraout_A0;
  int extraout_A0_00;
  
  DAT_00026eda = 0x14;
  if (DAT_000252bd != '\0') {
    puVar6 = (undefined4 *)&DAT_00024bfe;
    sVar2 = 0xe;
    do {
      if (*(char *)(puVar6 + 8) == '\0') {
        if (DAT_000252bd != -1) {
          DAT_000252bd = DAT_000252bd + -1;
        }
        *(undefined2 *)((int)puVar6 + 0x22) = DAT_000252f4;
        *(undefined4 *)((int)puVar6 + 0x12) = DAT_00026db2;
        *(undefined4 *)((int)puVar6 + 0xe) = DAT_00026db6;
        if (DAT_00024fdc < 0) {
          *(int *)((int)puVar6 + 0xe) = -*(int *)((int)puVar6 + 0xe);
        }
        *(undefined2 *)(puVar6 + 1) = DAT_00026db0;
        *(short *)(puVar6 + 1) = *(short *)(puVar6 + 1) + 0xb;
        *puVar6 = DAT_00026dba;
        uVar4 = 3;
        if (-1 < *(char *)((int)puVar6 + 0xe)) {
          uVar4 = 9;
        }
        *(undefined1 *)((int)puVar6 + 0x1e) = uVar4;
        if (*(short *)((int)puVar6 + 0x22) != 1) {
          if (*(short *)((int)puVar6 + 0x22) != 2) {
            *(short *)((int)puVar6 + 0x26) = DAT_00025354 >> 1;
            *(undefined2 *)(puVar6 + 10) = DAT_00025364;
            sVar2 = (*_thunk_FUN_00015108)();
            *(int *)(extraout_A0 + 0x1a) = sVar2 * 0x10 >> 3;
            sVar2 = (*_thunk_FUN_00015104)();
            iVar1 = sVar2 * 0x10 >> 3;
            if (*(short *)(extraout_A0_00 + 0xe) < 0) {
              iVar1 = -iVar1;
            }
            *(int *)(extraout_A0_00 + 0x16) = iVar1;
            (*_thunk_FUN_000203be)();
            (*_thunk_FUN_000203be)();
            (*_thunk_FUN_000203be)();
            uVar3 = (*_thunk_FUN_000203be)();
            sVar2 = (uVar3 & 6) << 1;
            if ((uVar3 & 6) == 0) {
              sVar2 = 8;
            }
            *(short *)(extraout_A0_00 + 0x24) = sVar2;
            sVar2 = 4 - (DAT_00025354 >> 5);
            if (4 < DAT_00025354 >> 5) {
              sVar2 = 0;
            }
            if (9 < sVar2) {
              sVar2 = 9;
            }
            cVar5 = (char)sVar2;
            if (*(char *)(extraout_A0_00 + 0xe) < '\0') {
              cVar5 = cVar5 + '\n';
            }
            *(char *)(extraout_A0_00 + 0x1e) = cVar5;
            *(undefined1 *)(extraout_A0_00 + 0x20) = 0xff;
            return;
          }
          *(undefined1 *)((int)puVar6 + 0x1f) = (undefined1)DAT_00024fdc;
        }
        *(undefined1 *)(puVar6 + 8) = 0xff;
        return;
      }
      puVar6 = (undefined4 *)((int)puVar6 + 0x2a);
      sVar2 = sVar2 + -1;
    } while (sVar2 != -1);
  }
  return;
}


// ==== FUN_00010820 @ 00010820 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00010820(short param_1,undefined4 param_2)

{
  short sVar1;
  short sVar2;
  short *psVar3;
  
  sVar1 = (short)DAT_00024578;
  psVar3 = &DAT_00024bfe;
  sVar2 = 0xe;
  while (*(char *)(psVar3 + 0x10) != '\0') {
    psVar3 = psVar3 + 0x15;
    sVar2 = sVar2 + -1;
    if (sVar2 == -1) {
      return;
    }
  }
  psVar3[9] = 0;
  psVar3[10] = 0;
  psVar3[7] = 0;
  psVar3[8] = 0;
  *psVar3 = (param_1 - sVar1) * 4;
  psVar3[2] = param_2._0_2_ + 0xc;
  psVar3[0xf] = 0;
  *(undefined1 *)(psVar3 + 0x10) = 8;
  *(undefined1 *)((int)psVar3 + 0x21) = 1;
  psVar3[0x11] = 1;
  *(undefined1 *)((int)psVar3 + 0x1f) = 0;
  if (param_2._2_2_ != 0) {
    return;
  }
  *(undefined1 *)((int)psVar3 + 0x1f) = 2;
                    /* WARNING: Could not recover jumptable at 0x00010888. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*_thunk_FUN_00012324)();
  return;
}


// ==== FUN_0001099a @ 0001099a ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0001099a(void)

{
  int iVar1;
  short sVar2;
  ushort uVar3;
  int in_A0;
  
  if ((((*(short *)(in_A0 + 0x26) >> 1 < 0) && (sVar2 = FUN_00011a46(), sVar2 != 0)) &&
      (sVar2 = FUN_00011a46(), sVar2 != 0)) &&
     ((sVar2 = FUN_00011a46(), sVar2 != 0 &&
      (((sVar2 = FUN_000111a6(), sVar2 != 0 || (sVar2 = FUN_000111a6(), sVar2 != 0)) ||
       ((sVar2 = FUN_0001115c(), sVar2 != 0 || (sVar2 = FUN_0001115c(), sVar2 != 0)))))))) {
    FUN_00015ca6();
    uVar3 = *(ushort *)(in_A0 + 0x28) / 100;
    sVar2 = (*_thunk_FUN_00015104)();
    iVar1 = *(int *)(in_A0 + 0xe);
    *(int *)(in_A0 + 0xe) = (int)sVar2 * (int)(short)uVar3;
    if (iVar1 < 0) {
      *(int *)(in_A0 + 0xe) = -*(int *)(in_A0 + 0xe);
    }
    sVar2 = (*_thunk_FUN_00015108)();
    *(int *)(in_A0 + 0x12) = (int)sVar2 * (int)(short)uVar3;
  }
  *(undefined1 *)(in_A0 + 0x20) = 0xff;
  return;
}


// ==== FUN_00010a72 @ 00010a72 ====

void FUN_00010a72(void)

{
  short sVar1;
  undefined2 *extraout_A0;
  undefined2 *puVar2;
  
  puVar2 = &DAT_00024bfe;
  sVar1 = 0xe;
  do {
    if (*(char *)(puVar2 + 0x10) != '\0') {
      FUN_00010aa6();
      puVar2 = extraout_A0;
    }
    puVar2 = puVar2 + 0x15;
    sVar1 = sVar1 + -1;
  } while (sVar1 != -1);
  DAT_00026d8c = 0;
  if (DAT_00025504._0_1_ != '\0') {
    FUN_00010aa6();
  }
  return;
}


// ==== FUN_00010aa6 @ 00010aa6 ====

/* WARNING: Removing unreachable block (ram,0x00010c36) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00010aa6(void)

{
  int iVar1;
  short sVar4;
  int iVar2;
  short sVar5;
  short sVar6;
  undefined4 uVar3;
  char cVar7;
  int *in_A0;
  undefined4 extraout_A0;
  
  if (*(char *)(in_A0 + 8) == '\b') {
    return;
  }
  if (*(short *)((int)in_A0 + 0x22) == 0) {
    if (*(short *)(in_A0 + 9) == 0) {
LAB_00010aec:
      *(int *)((int)in_A0 + 0x12) = *(int *)((int)in_A0 + 0x1a) + *(int *)((int)in_A0 + 0x12);
      *(int *)((int)in_A0 + 0xe) = *(int *)((int)in_A0 + 0x16) + *(int *)((int)in_A0 + 0xe);
    }
    else {
      sVar4 = *(short *)(in_A0 + 9) + -1;
      *(short *)(in_A0 + 9) = sVar4;
      if (sVar4 == 0) {
        FUN_0001099a();
        goto LAB_00010aec;
      }
      sVar4 = 1;
      if (DAT_00024fdc < 0) {
        sVar4 = -1;
      }
      *(short *)in_A0 = *(short *)in_A0 - sVar4;
      *(short *)(in_A0 + 1) = *(short *)(in_A0 + 1) + -1;
    }
    iVar2 = *in_A0 + *(int *)((int)in_A0 + 0xe);
    *in_A0 = iVar2;
    iVar2 = _DAT_00026dac - iVar2;
    if (iVar2 < 0) {
      iVar2 = -iVar2;
    }
    sVar5 = (short)((uint)iVar2 >> 0x10);
    sVar4 = sVar5 + -0x280;
    if (DAT_00024e84 != 0) {
      sVar4 = sVar5 + -0x1400;
    }
    if (0x280 < sVar4) {
      *(undefined1 *)(in_A0 + 8) = 0;
      return;
    }
    sVar4 = (short)((uint)(in_A0[1] + *(int *)((int)in_A0 + 0x1a) + *(int *)((int)in_A0 + 0x12)) >>
                   0x10);
  }
  else {
    if ((*(short *)((int)in_A0 + 0x22) == 2) && (*(char *)((int)in_A0 + 0x1e) == '\n'))
    goto LAB_00010d50;
    iVar2 = *(int *)((int)in_A0 + 0xe) +
            ((int)(short)((uint)*(int *)((int)in_A0 + 0xe) >> 0x10) / 10) * -0x10000;
    *(int *)((int)in_A0 + 0xe) = iVar2;
    *in_A0 = iVar2 + *in_A0;
    iVar2 = *(int *)((int)in_A0 + 0x12) - DAT_000252a0;
    *(int *)((int)in_A0 + 0x12) = iVar2;
    sVar4 = (short)((uint)(in_A0[1] + iVar2) >> 0x10);
  }
  iVar2 = FUN_00011126();
  if (iVar2 == 0) {
    *(short *)(in_A0 + 1) = sVar4;
    sVar5 = (*_thunk_FUN_000150c8)();
    if (sVar5 == 0) {
      sVar6 = 0xc;
    }
    else if (sVar5 == 2) {
      sVar6 = 0xc;
    }
    else if (sVar5 == 1) {
      sVar6 = FUN_00015714(extraout_A0);
      sVar6 = sVar6 + 0xb;
    }
    else {
      sVar6 = 0xc;
    }
    if (sVar4 <= sVar6) {
      *(short *)(in_A0 + 1) = sVar6;
      cVar7 = (char)sVar5;
      *(char *)((int)in_A0 + 0x1f) = cVar7;
      if ((cVar7 == '\x02') || (cVar7 != '\0')) {
        (*_thunk_FUN_00012324)();
      }
      else {
        (*_thunk_FUN_0001233e)();
      }
      *(ushort *)((int)in_A0 + 0x1a) = DAT_00025318;
      if ((*(short *)((int)in_A0 + 0x22) == 2) && (cVar7 == '\0')) {
        if (*(char *)((int)in_A0 + 0x1e) != '\n') {
          if (*(short *)((int)in_A0 + 0x12) < -5) goto LAB_00010cae;
          uVar3 = 0x45000;
          if (*(short *)((int)in_A0 + 0xe) < 0) {
            uVar3 = 0xfffbb000;
          }
          *(undefined4 *)((int)in_A0 + 0xe) = uVar3;
          *(undefined1 *)((int)in_A0 + 0x1e) = 10;
          *(undefined4 *)((int)in_A0 + 0x12) = 200;
          if (DAT_00025318 != *(ushort *)((int)in_A0 + 0x1a)) {
            *(ushort *)((int)in_A0 + 0x1a) = DAT_00025318;
            (*_thunk_FUN_000152b0)();
          }
        }
LAB_00010d50:
        iVar2 = *(int *)((int)in_A0 + 0x12);
        iVar1 = iVar2 + -1;
        *(int *)((int)in_A0 + 0x12) = iVar1;
        if (iVar1 == 0 || iVar2 < 1) {
          *(undefined1 *)(in_A0 + 8) = 0;
          *(undefined1 *)((int)in_A0 + 0x21) = 0;
        }
        else {
          *in_A0 = *in_A0 + *(int *)((int)in_A0 + 0xe);
          cVar7 = (*_thunk_FUN_000150c8)();
          if (cVar7 != '\0') {
            (*_thunk_FUN_000146dc)();
            *(undefined1 *)(in_A0 + 8) = 8;
            *(undefined1 *)((int)in_A0 + 0x21) = 1;
            (*_thunk_FUN_00012324)();
            (*_thunk_FUN_0001233e)();
            return;
          }
        }
        (*_thunk_FUN_000152b0)();
        return;
      }
LAB_00010cae:
      (*_thunk_FUN_000146dc)();
      *(undefined1 *)(in_A0 + 8) = 8;
      *(undefined1 *)((int)in_A0 + 0x21) = 1;
      FUN_00011a8c();
      return;
    }
  }
  else if (sVar4 < 0x1f) {
    if (*(short *)((int)in_A0 + 0x22) != 0) {
      *(undefined2 *)(in_A0 + 1) = 0x1e;
      *(int *)((int)in_A0 + 0x12) = -*(int *)((int)in_A0 + 0x12);
      *(short *)((int)in_A0 + 0x12) = *(short *)((int)in_A0 + 0x12) >> 1;
      if (*(short *)((int)in_A0 + 0x12) < 9) {
        if (*(short *)((int)in_A0 + 0x12) == 0) {
          *(undefined1 *)(in_A0 + 8) = 0;
          goto LAB_00010cca;
        }
      }
      else {
        *(undefined2 *)((int)in_A0 + 0x12) = 9;
      }
      sVar4 = *(short *)((int)in_A0 + 0xe) >> 1;
      *(short *)((int)in_A0 + 0xe) = sVar4;
      if (sVar4 != 0) goto LAB_00010cca;
    }
    *(undefined1 *)(in_A0 + 8) = 0;
  }
  else {
    *(short *)(in_A0 + 1) = sVar4;
  }
LAB_00010cca:
  if ((((*(short *)((int)in_A0 + 0x22) == 1) && (DAT_00026d8c != '\0')) && ((DAT_00025318 & 1) != 0)
      ) && (*(char *)((int)in_A0 + 0x1e) = *(char *)((int)in_A0 + 0x1e) + '\x01',
           0xb < *(byte *)((int)in_A0 + 0x1e))) {
    *(undefined1 *)((int)in_A0 + 0x1e) = 0;
  }
  return;
}


// ==== FUN_00010da6 @ 00010da6 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 FUN_00010da6(void)

{
  undefined4 in_D0;
  short sVar1;
  undefined4 in_D1;
  short sVar2;
  short *psVar3;
  short *psVar4;
  
  psVar4 = &DAT_0002512a;
  sVar2 = DAT_00025128;
  while (sVar2 = sVar2 + -1, sVar2 != -1) {
    psVar3 = psVar4 + 1;
    sVar1 = *psVar4;
    if (sVar1 < 0) {
      sVar1 = -sVar1;
    }
    sVar1 = sVar1 - DAT_00024e80;
    if (DAT_00024e84 != 0) {
      sVar1 = sVar1 >> 3;
    }
    psVar4 = psVar3;
    if ((-0x81 < sVar1) && (sVar1 < 0x1c1)) {
      (*_thunk_FUN_00020ce2)();
    }
  }
  sVar2 = 3;
  psVar4 = &DAT_0002517a;
  do {
    if (*psVar4 != 0) {
      sVar1 = psVar4[0x10] - DAT_00024e80;
      if (DAT_00024e84 != 0) {
        sVar1 = sVar1 >> 3;
      }
      if ((((-0x81 < sVar1) && (sVar1 < 0x1c1)) && ((*_thunk_FUN_00020ce2)(), psVar4[9] != 0)) &&
         ((DAT_00024e84 == 0 && (psVar4[0x16] = psVar4[0x16] + 1, (psVar4[0x16] & 1U) != 0)))) {
        (*_thunk_FUN_00020e24)();
      }
    }
    psVar4 = psVar4 + 0x1a;
    sVar2 = sVar2 + -1;
  } while (sVar2 != -1);
  return CONCAT44(in_D0,in_D1);
}


// ==== FUN_00010ee0 @ 00010ee0 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 FUN_00010ee0(void)

{
  short sVar1;
  short sVar2;
  undefined4 in_D0;
  undefined4 in_D1;
  short sVar3;
  int *extraout_A1;
  int *piVar4;
  
  (*_thunk_FUN_000212ce)();
  sVar2 = DAT_000268ae;
  if (DAT_000252e4 != 0) {
    DAT_000268ae = DAT_00025442 + DAT_00026da6 + 0x84;
  }
  sVar3 = 0x27;
  piVar4 = DAT_00026ea8;
  do {
    if (*(short *)(piVar4 + 4) != 0) {
      (*_thunk_FUN_00015174)();
      *extraout_A1 = extraout_A1[2] + *extraout_A1;
      extraout_A1[1] = extraout_A1[3] + extraout_A1[1];
      sVar1 = *(short *)((int)extraout_A1 + 0x12) + -1;
      *(short *)((int)extraout_A1 + 0x12) = sVar1;
      piVar4 = extraout_A1;
      if (sVar1 < 0) {
        *(undefined2 *)((int)extraout_A1 + 0x12) = 6;
        *(short *)(extraout_A1 + 4) = *(short *)(extraout_A1 + 4) + -1;
      }
    }
    sVar3 = sVar3 + -1;
    piVar4 = piVar4 + 5;
  } while (sVar3 != -1);
  DAT_000268ae = sVar2;
  (*_thunk_FUN_000212d4)();
  return CONCAT44(in_D0,in_D1);
}


// ==== FUN_00010f88 @ 00010f88 ====

void FUN_00010f88(void)

{
  int iVar1;
  short sVar2;
  undefined2 *puVar3;
  undefined **ppuVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  
  iVar1 = DAT_00026ec4;
  (**(code **)(DAT_00026ec4 + -0x84))();
  DAT_00026dac = DAT_00024fca;
  DAT_00026db0 = DAT_00024fc8;
  DAT_00026eca = DAT_00024fdc;
  DAT_00026ec8 = DAT_0002535e;
  DAT_00026ecc = DAT_00026db2._0_2_;
  DAT_00026da6 = DAT_000252fe;
  DAT_00024e86 = DAT_00025300;
  puVar3 = &DAT_00024bfe;
  sVar2 = 0xe;
  do {
    puVar3[4] = *puVar3;
    puVar3[5] = puVar3[2];
    puVar3[6] = puVar3[0x10];
    puVar3 = puVar3 + 0x15;
    sVar2 = sVar2 + -1;
  } while (sVar2 != -1);
  DAT_000254ec = DAT_000254e4;
  DAT_000254ee = DAT_000254e8;
  DAT_000254f0 = DAT_00025504;
  puVar3 = &DAT_0002517a;
  sVar2 = 3;
  do {
    puVar3[0x17] = ((short)puVar3[0x10] >> 3) * 2;
    puVar3 = puVar3 + 0x1a;
    sVar2 = sVar2 + -1;
  } while (sVar2 != -1);
  sVar2 = 3;
  puVar3 = &DAT_0002524a;
  do {
    *(undefined4 *)(puVar3 + 8) = *(undefined4 *)(puVar3 + 3);
    puVar3 = puVar3 + 10;
    sVar2 = sVar2 + -1;
  } while (sVar2 != -1);
  sVar2 = 4;
  ppuVar4 = &PTR_DAT_000254aa;
  do {
    *(undefined2 *)(*ppuVar4 + 0x1a) = *(undefined2 *)(*ppuVar4 + 0x14);
    sVar2 = sVar2 + -1;
    ppuVar4 = ppuVar4 + 1;
  } while (sVar2 != -1);
  puVar5 = &DAT_00024fe6;
  puVar7 = &DAT_00024e88;
  sVar2 = 4;
  do {
    *puVar7 = *puVar5;
    puVar7[1] = puVar5[1];
    puVar7[2] = puVar5[2];
    puVar7[3] = puVar5[3];
    puVar7[4] = puVar5[4];
    puVar7[5] = puVar5[5];
    puVar7[6] = puVar5[6];
    puVar7[7] = puVar5[7];
    puVar7[8] = puVar5[8];
    puVar7[9] = puVar5[9];
    puVar7[10] = puVar5[10];
    puVar7[0xb] = puVar5[0xb];
    puVar7[0xc] = puVar5[0xc];
    puVar7[0xd] = puVar5[0xd];
    puVar6 = puVar5 + 0xf;
    puVar8 = puVar7 + 0xf;
    puVar7[0xe] = puVar5[0xe];
    puVar5 = puVar5 + 0x10;
    puVar7 = puVar7 + 0x10;
    *puVar8 = *puVar6;
    sVar2 = sVar2 + -1;
  } while (sVar2 != -1);
  (**(code **)(iVar1 + -0x8a))();
  DAT_000252b8 = DAT_000252b8 + -1;
  if (DAT_000252b8 < '\0') {
    DAT_000252de = DAT_000252de + -1;
    if (DAT_000252de < '\0') {
      DAT_000252de = '\v';
    }
    DAT_000252b8 = '\x01';
  }
  return;
}


// ==== FUN_0001107c @ 0001107c ====

undefined8 FUN_0001107c(void)

{
  undefined4 in_D0;
  undefined4 in_D1;
  
  DAT_000252bc = 0xff;
  FUN_000107f2();
  DAT_00026d8d = 0;
  return CONCAT44(in_D0,in_D1);
}


// ==== FUN_00011092 @ 00011092 ====

undefined8 FUN_00011092(void)

{
  uint in_D0;
  uint in_D1;
  uint uVar1;
  int iVar2;
  
  uVar1 = (in_D1 & 0xffff) * (in_D0 & 0xffff);
  iVar2 = (int)(short)in_D1 * (int)(short)(in_D0 >> 0x10);
  if (((short)uVar1 < 0) && (uVar1 = uVar1 + 0x10000, uVar1 == 0)) {
    iVar2 = iVar2 + 1;
  }
  return CONCAT44((uVar1 >> 0x10) + iVar2,in_D1);
}


// ==== FUN_000110c2 @ 000110c2 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_000110c2(void)

{
  int iVar1;
  bool bVar2;
  
  if (DAT_000252b2 != '\0') {
    (*_thunk_FUN_000212ce)();
    (*_thunk_FUN_0001524a)();
    (*_thunk_FUN_0002124a)();
    iVar1 = (*_thunk_FUN_00020560)();
    if (iVar1 != 0) {
      (*_thunk_FUN_00020ce2)();
    }
    (*_thunk_FUN_000212d4)();
    if (DAT_00025512 != 0) {
      bVar2 = SBORROW1(DAT_00025512,'\x01');
      DAT_00025512 = DAT_00025512 - 1;
      if (DAT_00025512 == 0 || bVar2 != (short)((ushort)DAT_00025512 << 8) < 0) {
        DAT_00025312 = 0xff;
      }
    }
  }
  return;
}


// ==== FUN_00011126 @ 00011126 ====

short * FUN_00011126(void)

{
  short in_D0w;
  short sVar1;
  short *psVar2;
  
  psVar2 = &DAT_0002524a;
  sVar1 = 3;
  do {
    if (*psVar2 == 0) {
      return (short *)0x0;
    }
    if (in_D0w < *psVar2) {
      return (short *)0x0;
    }
    if (in_D0w <= psVar2[1]) {
      return psVar2;
    }
    psVar2 = psVar2 + 10;
    sVar1 = sVar1 + -1;
  } while (sVar1 != -1);
  return (short *)0x0;
}


// ==== FUN_0001115c @ 0001115c ====

undefined8 FUN_0001115c(void)

{
  undefined4 in_D0;
  undefined4 in_D1;
  ushort uVar1;
  short sVar2;
  short sVar3;
  short sVar4;
  short *psVar5;
  
  sVar2 = (short)in_D0;
  sVar4 = (short)in_D1;
  sVar3 = sVar2;
  if (sVar4 < sVar2) {
    sVar3 = sVar4;
    sVar4 = sVar2;
  }
  uVar1 = (ushort)DAT_000252d5;
  psVar5 = DAT_00025454;
  while (uVar1 = uVar1 - 1, uVar1 != 0xffff) {
    if (*(char *)(psVar5 + 4) == '\0') {
      sVar2 = *psVar5;
      in_D0 = CONCAT22((short)((uint)in_D0 >> 0x10),sVar2);
      if ((sVar3 <= sVar2) && (sVar2 < sVar4)) goto LAB_000111a0;
    }
    psVar5 = psVar5 + 7;
  }
  in_D0 = 0;
LAB_000111a0:
  return CONCAT44(in_D0,in_D1);
}


// ==== FUN_000111a6 @ 000111a6 ====

undefined * FUN_000111a6(void)

{
  short sVar1;
  short in_D0w;
  undefined *puVar2;
  short in_D1w;
  short sVar3;
  short sVar4;
  int iVar5;
  undefined **ppuVar6;
  undefined **ppuVar7;
  
  sVar4 = in_D0w;
  if (in_D1w < in_D0w) {
    sVar4 = in_D1w;
    in_D1w = in_D0w;
  }
  ppuVar6 = &PTR_DAT_000254aa;
  do {
    do {
      ppuVar7 = ppuVar6 + 1;
      puVar2 = *ppuVar6;
      if ((int)puVar2 < 0) {
        return (undefined *)0x0;
      }
      ppuVar6 = ppuVar7;
    } while ((*(int *)(puVar2 + 0x12) == 0) || (puVar2[4] == '\0'));
    iVar5 = *(int *)(puVar2 + 6);
    sVar3 = *(short *)(puVar2 + 10);
    while (sVar3 = sVar3 + -1, sVar3 != -1) {
      sVar1 = *(short *)(iVar5 + 4);
      puVar2 = (undefined *)CONCAT22((short)((uint)puVar2 >> 0x10),sVar1);
      if ((sVar4 <= sVar1) && (sVar1 <= in_D1w)) {
        return puVar2;
      }
      iVar5 = iVar5 + 0xe;
    }
  } while( true );
}


// ==== FUN_000111fc @ 000111fc ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_000111fc(void)

{
  ushort uVar1;
  
  uVar1 = 0;
  if ('\x06' < (char)(&DAT_000233af)[(short)(DAT_00025310 + DAT_0002530e * 4)]) {
    (*_thunk_FUN_000203be)();
    (*_thunk_FUN_000203be)();
    (*_thunk_FUN_000203be)();
    uVar1 = (*_thunk_FUN_000203be)();
    uVar1 = uVar1 >> 0xf;
  }
  DAT_000252e0 = uVar1;
  return;
}


// ==== FUN_00011234 @ 00011234 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00011234(void)

{
  (**(code **)(DAT_00026ec4 + -0xc6))();
  (*_thunk_FUN_000134ae)();
  (*_thunk_FUN_0001346c)();
  (*_thunk_FUN_00012bbe)();
  FUN_000124e0();
  return;
}


// ==== FUN_00011256 @ 00011256 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00011256(void)

{
  (**(code **)(DAT_00026ec4 + -0xc6))();
  (*_thunk_FUN_000134ae)();
  (*_thunk_FUN_0001346c)();
  FUN_000124e0();
  return;
}


// ==== FUN_00011274 @ 00011274 ====

void FUN_00011274(void)

{
  DAT_00026db2._0_2_ = DAT_00024fe0;
  DAT_00026db2._2_2_ = 0;
  DAT_00026db6._0_2_ = DAT_00024fde;
  DAT_00026db6._2_2_ = 0;
  DAT_00026dba._0_2_ = DAT_00024fca;
  DAT_00026dba._2_2_ = 0;
  DAT_00026dbe = DAT_00024fc8;
  DAT_00026dc0 = 0;
  DAT_00025354 = (short)(((short)(DAT_000259f2 * 2) * 0x200) / 18000);
  return;
}


// ==== FUN_000112b0 @ 000112b0 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_000112b0(void)

{
  ushort uVar1;
  
  if ((DAT_000252b4 != '\0') && (DAT_0002530c == 0)) {
    uVar1 = DAT_00026c92;
    if (DAT_00026c92 == 0) {
      if (_DAT_00026eae == 0x4d) {
        uVar1 = 2;
      }
      if (_DAT_00026eae == 0x4c) {
        uVar1 = 1;
      }
      if (_DAT_00026eae == 0x44) {
        uVar1 = 0x10;
      }
      if (_DAT_00026eae == 0x43) {
        uVar1 = 0x10;
      }
    }
    if (uVar1 != 0) {
      if ((uVar1 & 0x30) != 0) {
        DAT_000252b4 = 0;
        DAT_00024fd4 = 0xb;
        DAT_000252e4 = 2;
        return;
      }
      if (DAT_000252be < '\x01') {
        if ((uVar1 & 3) != 0) {
          DAT_000252be = '\x02';
          if ((uVar1 & 1) == 0) {
            DAT_000252f4 = DAT_000252f4 + 1;
            if (DAT_000252f4 == 3) {
              DAT_000252f4 = 0;
            }
          }
          else {
            DAT_000252f4 = DAT_000252f4 + -1;
            if (DAT_000252f4 == -1) {
              DAT_000252f4 = 2;
            }
          }
          if (DAT_000252bd != -1) {
            DAT_000252bd = (&DAT_00024b49)[DAT_000252f4];
          }
          (*_thunk_FUN_0001edbc)();
        }
      }
      else {
        DAT_000252be = DAT_000252be + -1;
      }
    }
  }
  return;
}


// ==== FUN_00011386 @ 00011386 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00011386(void)

{
  bool bVar1;
  short sVar2;
  
  if (DAT_000254a6 == '\0') {
    if (DAT_00024fd4 == 0) {
      if ((DAT_00024fda != 0x80) &&
         (sVar2 = DAT_000272a0 + -1, bVar1 = DAT_000272a0 < 1, DAT_000272a0 = sVar2,
         sVar2 == 0 || bVar1)) {
        DAT_000272a0 = 0x50;
        DAT_00024fda = DAT_00024fda + -1;
      }
      sVar2 = DAT_0002729e + -1;
      bVar1 = DAT_0002729e < 1;
      DAT_0002729e = sVar2;
      if (sVar2 == 0 || bVar1) {
        DAT_00024fd6 = DAT_00024fd6 + -1;
        DAT_0002729e = DAT_000270b8;
      }
    }
    DAT_00027296 = DAT_00027296 + 1 & 1;
    DAT_000252fc = DAT_000252fc + -1;
    if (DAT_000252fc < 0) {
      DAT_000252fc = DAT_00025338;
      DAT_000246ba = DAT_000246ba + 1 & 7;
      DAT_000252fe = (byte)(&DAT_00024b94)[(short)DAT_000246ba] + 1;
    }
    DAT_00026c92 = FUN_00011714();
    if ((DAT_00026c8e == 0) ||
       (sVar2 = DAT_00026c8e + -1, bVar1 = DAT_00026c8e < 1, DAT_00026c8e = sVar2,
       sVar2 == 0 || bVar1)) {
      FUN_000112b0();
      FUN_00011460();
    }
    (*_thunk_FUN_0001c660)();
    (*_thunk_FUN_0001e7d6)();
    FUN_00012132();
    (*_thunk_FUN_0001b682)();
    FUN_00012066();
    FUN_00011274();
    FUN_00011bfc();
    (*_thunk_FUN_00010a72)();
    FUN_000119bc();
    bVar1 = DAT_00027298 < 1;
    DAT_00027298 = DAT_00027298 + -1;
    if (bVar1) {
      DAT_00027298 = 0;
    }
    FUN_00011622();
    FUN_00011510();
    FUN_00011cae();
    FUN_00011de4();
    FUN_00011c5e();
  }
  return;
}


// ==== FUN_00011460 @ 00011460 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00011460(void)

{
  if ((DAT_00025318 != DAT_000272a2) && (DAT_000272a2 = DAT_00025318, DAT_000252e4 != 0)) {
    if (DAT_000252e4 == 2) {
      DAT_000252e6 = DAT_000252e6 + -1;
      if (DAT_000252e6 == 0) {
        DAT_000252e4 = 0;
        (*_thunk_FUN_00011f4e)(DAT_00025318);
        (*_thunk_FUN_00012354)();
        (*_thunk_FUN_0001b9cc)();
      }
    }
    else if ((DAT_000252e4 == 3) && (DAT_000252e6 = DAT_000252e6 + 1, DAT_000252e6 == 0x20)) {
      (*_thunk_FUN_00011f4e)(DAT_00025318);
      (*_thunk_FUN_00012354)();
      FUN_00013684();
    }
  }
  return;
}


// ==== FUN_000114d8 @ 000114d8 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_000114d8(void)

{
  while (DAT_00026c94 != 0) {
    (*_thunk_FUN_0001aa32)();
  }
  if (DAT_000254a6 < '\0') {
    return;
  }
  while (0 < DAT_000272a4) {
    FUN_00011386();
  }
  DAT_00026c94 = 0;
  if (DAT_00026c9c != 0) {
    DAT_00026c94 = 2;
  }
  return;
}


// ==== FUN_00011510 @ 00011510 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00011510(void)

{
  undefined2 *puVar1;
  short *psVar2;
  short sVar3;
  short sVar4;
  short *psVar5;
  undefined **ppuVar6;
  
  if ((DAT_000250e6 != 0) &&
     (sVar4 = (DAT_000250e6 + -1) * 8, 0 < *(short *)(&DAT_000250ee + sVar4))) {
    DAT_0002729a = (DAT_0002729a + 8) - (DAT_0002729a >> 4);
    sVar3 = *(short *)(&DAT_000250f0 + sVar4) - (DAT_0002729a >> 4);
    *(short *)(&DAT_000250f0 + sVar4) = sVar3;
    if (sVar3 < (short)(DAT_0002540a << 2)) {
      DAT_000250e6 = DAT_000250e6 + -1;
      (*_thunk_FUN_0001e4d0)(*(undefined2 *)(&DAT_000250f0 + sVar4),0xffff);
    }
  }
  if (DAT_00027298 == 0) {
    sVar4 = 4;
    psVar5 = (short *)&DAT_00024fe6;
    ppuVar6 = &PTR_DAT_000254aa;
    do {
      psVar2 = (short *)*ppuVar6;
      if ((((psVar2[2] != 0) && (psVar2[9] != 0)) && (0 < psVar2[6])) &&
         (((psVar5[2] <= DAT_00026dba._0_2_ && (DAT_00026dba._0_2_ <= psVar5[3])) &&
          ((DAT_00025126 < psVar5[1] && (*psVar5 != 0)))))) {
        if (sVar4 == 0) {
          puVar1 = (undefined2 *)((int)psVar5 + (short)((*psVar5 + -1) * 8) + 8);
          *puVar1 = 1;
          DAT_0002729a = 0;
          puVar1[1] = *psVar2 * 4 + 0x17c;
          puVar1[2] = 0x21;
          DAT_00027298 = 100;
          return;
        }
        *psVar5 = *psVar5 + -1;
        (*_thunk_FUN_0001e4d0)(*(undefined2 *)((int)psVar5 + (short)(*psVar5 * 8) + 10),0xffff);
        DAT_00027298 = 100;
      }
      psVar5 = psVar5 + 0x20;
      sVar4 = sVar4 + -1;
      ppuVar6 = ppuVar6 + 1;
    } while (sVar4 != -1);
    return;
  }
  return;
}


// ==== FUN_00011622 @ 00011622 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00011622(void)

{
  ushort uVar1;
  short sVar2;
  short sVar3;
  short *psVar4;
  
  sVar2 = 3;
  psVar4 = &DAT_0002524a;
  do {
    if (psVar4[4] != 0) {
      uVar1 = psVar4[6] + 1;
      if (0x38 < (short)uVar1) {
        uVar1 = 0x38;
      }
      psVar4[6] = uVar1;
      if (psVar4[7] == -1) {
        psVar4[4] = psVar4[4] - (uVar1 >> 3);
        sVar2 = psVar4[4];
        if (*psVar4 <= sVar2) {
          return;
        }
      }
      else {
        psVar4[4] = (uVar1 >> 3) + psVar4[4];
        sVar2 = psVar4[4];
        if (sVar2 <= psVar4[1]) {
          return;
        }
      }
      (*_thunk_FUN_0001e4d0)(sVar2,psVar4[7]);
      psVar4[4] = 0;
      return;
    }
    psVar4 = psVar4 + 10;
    sVar2 = sVar2 + -1;
  } while (sVar2 != -1);
  if (DAT_00027298 == 0) {
    sVar3 = 3;
    psVar4 = &DAT_0002524a;
    sVar2 = DAT_00026dba._0_2_;
    do {
      if (((short)(*psVar4 + -0x1e0) <= sVar2) && (sVar2 <= (short)(psVar4[1] + 0x1e0))) {
        if (psVar4[2] <= DAT_00025126) {
          return;
        }
        if (psVar4[3] < 1) {
          return;
        }
        psVar4[3] = psVar4[3] + -1;
        DAT_00027298 = 100;
        sVar2 = psVar4[1] + -0x20 + psVar4[3] * -0x40;
        if (psVar4[7] != -1) {
          sVar2 = psVar4[3] * 0x40 + *psVar4 + 0x20;
        }
        psVar4[4] = sVar2;
        psVar4[6] = 0;
        sVar2 = DAT_00026dba._0_2_;
      }
      psVar4 = psVar4 + 10;
      sVar3 = sVar3 + -1;
    } while (sVar3 != -1);
  }
  return;
}


// ==== FUN_00011714 @ 00011714 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00011714(void)

{
  bool bVar1;
  short sVar2;
  undefined2 *puVar3;
  
  (*_thunk_FUN_00022d48)();
  puVar3 = &DAT_000272a6;
  sVar2 = DAT_000272a4 + -1;
  bVar1 = DAT_000272a4 < 1;
  DAT_000272a4 = sVar2;
  if (bVar1) {
    sVar2 = 0;
    DAT_000272a4 = sVar2;
  }
  while (sVar2 = sVar2 + -1, sVar2 != -1) {
    *puVar3 = puVar3[1];
    puVar3 = puVar3 + 1;
  }
  (*_thunk_FUN_00022d66)();
  return;
}


// ==== FUN_0001174a @ 0001174a ====

void FUN_0001174a(void)

{
  DAT_000272a4 = 0;
  DAT_000272a6 = 0;
  return;
}


// ==== FUN_00011754 @ 00011754 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00011754(void)

{
  ushort uVar1;
  byte bVar2;
  bool bVar3;
  short sVar4;
  ushort uVar5;
  short sVar6;
  undefined4 in_D1;
  ushort extraout_D1w;
  short sVar7;
  undefined2 *extraout_A0;
  ushort *puVar8;
  undefined2 *puVar9;
  undefined2 *puVar10;
  int *in_A1;
  undefined2 *puVar11;
  undefined2 *puVar12;
  
  DAT_0002550e = 0xff;
  if (DAT_000254a6 != '\0') {
    DAT_0002550e = 0xff;
    return in_D1;
  }
  *in_A1 = *in_A1 + 1;
  if (DAT_000272b4 == 0) {
    (*_thunk_FUN_0001c9ca)();
    sVar6 = DAT_000272b2 + -1;
    bVar3 = DAT_000272b2 < 1;
    DAT_000272b2 = sVar6;
    if (sVar6 == 0 || bVar3) {
      DAT_000272b2 = 4;
      if (DAT_00026c9c == 1) {
        if ((DAT_00026ca4 == 0) || (DAT_00026c94 == 0)) goto LAB_00011842;
        DAT_00026c94 = DAT_00026c94 + -1;
        bVar2 = *(byte *)(DAT_00026c9e + (short)DAT_00026ca2);
        uVar5 = (ushort)bVar2;
        if ((bVar2 == 0xff) || (DAT_00026ca2 = DAT_00026ca2 + 1, 0x1385 < DAT_00026ca2)) {
          DAT_00025312 = 0xff;
        }
        DAT_000272b6 = (ushort)bVar2;
      }
      else {
        uVar5 = (*_thunk_FUN_0001ca32)();
      }
      puVar11 = &DAT_000272a6;
      if (DAT_000272a4 < 6) {
        DAT_000272a4 = DAT_000272a4 + 1;
      }
      else {
        uVar5 = FUN_00011714();
        puVar11 = extraout_A0;
        DAT_000272a4 = extraout_D1w;
      }
      *(ushort *)((int)puVar11 + (int)(short)((DAT_000272a4 - 1) * 2)) = DAT_000272b6;
      if (((DAT_00026c9c == 2) && (DAT_00026ca4 != 0)) && (DAT_00026c94 != 0)) {
        DAT_00026c94 = DAT_00026c94 + -1;
        *(undefined1 *)(DAT_00026c9e + (short)DAT_00026ca2) = (undefined1)DAT_000272b6;
        DAT_00026ca2 = DAT_00026ca2 + 1;
        DAT_000272b6 = uVar5;
        if (0x1385 < DAT_00026ca2) {
          DAT_00025312 = 0xff;
        }
      }
    }
  }
LAB_00011842:
  if (DAT_0002459e == '\0') {
    DAT_00025360 = DAT_00025360 + 1;
    if (DAT_00025518 != 0) {
      puVar8 = (ushort *)(DAT_000271f2 + 0x444);
      sVar6 = 0xc;
      DAT_00025518 = DAT_00025518 + -1;
      do {
        uVar5 = puVar8[-1];
        puVar8[-1] = uVar5 << 1;
        uVar1 = puVar8[-2];
        puVar8[-2] = uVar1 << 1 | (ushort)((uVar5 & 0x8000) != 0);
        uVar5 = puVar8[-3];
        puVar8[-3] = uVar5 << 1 | (ushort)((uVar1 & 0x8000) != 0);
        uVar1 = puVar8[-4];
        puVar8[-4] = uVar1 << 1 | (ushort)((uVar5 & 0x8000) != 0);
        uVar5 = puVar8[-5];
        puVar8[-5] = uVar5 << 1 | (ushort)((uVar1 & 0x8000) != 0);
        uVar1 = puVar8[-6];
        puVar8[-6] = uVar1 << 1 | (ushort)((uVar5 & 0x8000) != 0);
        uVar5 = puVar8[-7];
        puVar8[-7] = uVar5 << 1 | (ushort)((uVar1 & 0x8000) != 0);
        uVar1 = puVar8[-8];
        puVar8[-8] = uVar1 << 1 | (ushort)((uVar5 & 0x8000) != 0);
        uVar5 = puVar8[-9];
        puVar8[-9] = uVar5 << 1 | (ushort)((uVar1 & 0x8000) != 0);
        uVar1 = puVar8[-10];
        puVar8[-10] = uVar1 << 1 | (ushort)((uVar5 & 0x8000) != 0);
        uVar5 = puVar8[-0xb];
        puVar8[-0xb] = uVar5 << 1 | (ushort)((uVar1 & 0x8000) != 0);
        uVar1 = puVar8[-0xc];
        puVar8[-0xc] = uVar1 << 1 | (ushort)((uVar5 & 0x8000) != 0);
        uVar5 = puVar8[-0xd];
        puVar8[-0xd] = uVar5 << 1 | (ushort)((uVar1 & 0x8000) != 0);
        uVar1 = puVar8[-0xe];
        puVar8[-0xe] = uVar1 << 1 | (ushort)((uVar5 & 0x8000) != 0);
        uVar5 = puVar8[-0xf];
        puVar8[-0xf] = uVar5 << 1 | (ushort)((uVar1 & 0x8000) != 0);
        uVar1 = puVar8[-0x10];
        puVar8[-0x10] = uVar1 << 1 | (ushort)((uVar5 & 0x8000) != 0);
        uVar5 = puVar8[-0x11];
        puVar8[-0x11] = uVar5 << 1 | (ushort)((uVar1 & 0x8000) != 0);
        uVar1 = puVar8[-0x12];
        puVar8[-0x12] = uVar1 << 1 | (ushort)((uVar5 & 0x8000) != 0);
        uVar5 = puVar8[-0x13];
        puVar8[-0x13] = uVar5 << 1 | (ushort)((uVar1 & 0x8000) != 0);
        uVar1 = puVar8[-0x14];
        puVar8[-0x14] = uVar1 << 1 | (ushort)((uVar5 & 0x8000) != 0);
        uVar5 = puVar8[-0x15];
        puVar8[-0x15] = uVar5 << 1 | (ushort)((uVar1 & 0x8000) != 0);
        uVar1 = puVar8[-0x16];
        puVar8[-0x16] = uVar1 << 1 | (ushort)((uVar5 & 0x8000) != 0);
        uVar5 = puVar8[-0x17];
        puVar8[-0x17] = uVar5 << 1 | (ushort)((uVar1 & 0x8000) != 0);
        uVar1 = puVar8[-0x18];
        puVar8[-0x18] = uVar1 << 1 | (ushort)((uVar5 & 0x8000) != 0);
        uVar5 = puVar8[-0x19];
        puVar8[-0x19] = uVar5 << 1 | (ushort)((uVar1 & 0x8000) != 0);
        uVar1 = puVar8[-0x1a];
        puVar8[-0x1a] = uVar1 << 1 | (ushort)((uVar5 & 0x8000) != 0);
        uVar5 = puVar8[-0x1b];
        puVar8[-0x1b] = uVar5 << 1 | (ushort)((uVar1 & 0x8000) != 0);
        uVar1 = puVar8[-0x1c];
        puVar8[-0x1c] = uVar1 << 1 | (ushort)((uVar5 & 0x8000) != 0);
        uVar5 = puVar8[-0x1d];
        puVar8[-0x1d] = uVar5 << 1 | (ushort)((uVar1 & 0x8000) != 0);
        uVar1 = puVar8[-0x1e];
        puVar8[-0x1e] = uVar1 << 1 | (ushort)((uVar5 & 0x8000) != 0);
        uVar5 = puVar8[-0x1f];
        puVar8[-0x1f] = uVar5 << 1 | (ushort)((uVar1 & 0x8000) != 0);
        uVar1 = puVar8[-0x20];
        puVar8[-0x20] = uVar1 << 1 | (ushort)((uVar5 & 0x8000) != 0);
        uVar5 = puVar8[-0x21];
        puVar8[-0x21] = uVar5 << 1 | (ushort)((uVar1 & 0x8000) != 0);
        uVar1 = puVar8[-0x22];
        puVar8[-0x22] = uVar1 << 1 | (ushort)((uVar5 & 0x8000) != 0);
        uVar5 = puVar8[-0x23];
        puVar8[-0x23] = uVar5 << 1 | (ushort)((uVar1 & 0x8000) != 0);
        uVar1 = puVar8[-0x24];
        puVar8[-0x24] = uVar1 << 1 | (ushort)((uVar5 & 0x8000) != 0);
        uVar5 = puVar8[-0x25];
        puVar8[-0x25] = uVar5 << 1 | (ushort)((uVar1 & 0x8000) != 0);
        uVar1 = puVar8[-0x26];
        puVar8[-0x26] = uVar1 << 1 | (ushort)((uVar5 & 0x8000) != 0);
        uVar5 = puVar8[-0x27];
        puVar8[-0x27] = uVar5 << 1 | (ushort)((uVar1 & 0x8000) != 0);
        uVar1 = puVar8[-0x28];
        puVar8[-0x28] = uVar1 << 1 | (ushort)((uVar5 & 0x8000) != 0);
        uVar5 = puVar8[-0x29];
        puVar8[-0x29] = uVar5 << 1 | (ushort)((uVar1 & 0x8000) != 0);
        puVar8 = puVar8 + -0x2a;
        *puVar8 = *puVar8 << 1 | (ushort)((uVar5 & 0x8000) != 0);
        sVar6 = sVar6 + -1;
      } while (sVar6 != -1);
      if ((DAT_00025530 != 0) && (DAT_00025530 = DAT_00025530 + -1, DAT_00025530 != 0)) {
        return in_D1;
      }
    }
    if (DAT_00025706 != (char *)0x0) {
      if (*DAT_00025706 == '\0') {
        DAT_00025706 = (char *)0x0;
        DAT_00025530 = 0;
      }
      else {
        DAT_00025518 = 0x2a0;
        uVar5 = (ushort)(byte)(*DAT_00025706 - DAT_00026ebe);
        bVar2 = *(byte *)(DAT_00026eba + 4 + (int)(short)uVar5);
        if (bVar2 == 0) {
          DAT_00025530 = 10;
          DAT_00025706 = DAT_00025706 + 1;
        }
        else {
          DAT_00025530 = bVar2 + 1;
          puVar9 = (undefined2 *)
                   (*(short *)((int)&DAT_00026ca6 + (int)(short)(uVar5 * 2)) + DAT_00026d66);
          puVar11 = (undefined2 *)(DAT_000271f2 + 0x50);
          sVar6 = DAT_00026ec0;
          DAT_00025706 = DAT_00025706 + 1;
          while (sVar6 = sVar6 + -1, sVar6 != -1) {
            sVar4 = ((ushort)(bVar2 + 0xf) >> 4) - 1;
            puVar10 = puVar9;
            sVar7 = sVar4;
            do {
              puVar12 = puVar11;
              puVar9 = puVar10 + 1;
              *puVar12 = *puVar10;
              sVar7 = sVar7 + -1;
              puVar10 = puVar9;
              puVar11 = puVar12 + 1;
            } while (sVar7 != -1);
            puVar11 = (undefined2 *)((int)puVar12 + (0x54 - (short)(sVar4 * 2)));
          }
        }
      }
    }
  }
  return in_D1;
}


// ==== FUN_000119bc @ 000119bc ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_000119bc(void)

{
  undefined2 uVar1;
  undefined1 uVar2;
  short sVar3;
  undefined2 *extraout_A0;
  int extraout_A0_00;
  int iVar4;
  
  if ((((DAT_000252ba != 0) && (DAT_00026db2._0_2_ < 0)) && (DAT_00024fc8 < 0xa0)) &&
     (sVar3 = 0x13, iVar4 = DAT_00026e80, DAT_000259fa == 0)) {
    do {
      if (*(char *)(iVar4 + 2) == '\0') {
        FUN_00011a46();
        uVar1 = FUN_00011a8c();
        *extraout_A0 = uVar1;
        (*_thunk_FUN_000152b0)();
        uVar2 = (*_thunk_FUN_000150c8)();
        *(undefined1 *)(extraout_A0_00 + 3) = uVar2;
        return;
      }
      iVar4 = iVar4 + 4;
      sVar3 = sVar3 + -1;
    } while (sVar3 != -1);
  }
  return;
}


// ==== FUN_00011a14 @ 00011a14 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00011a14(void)

{
  undefined2 uVar1;
  short in_D0w;
  undefined1 uVar2;
  short sVar3;
  short *psVar4;
  undefined2 *extraout_A0;
  int extraout_A0_00;
  int extraout_A0_01;
  
  psVar4 = DAT_00026df4;
  if ((*(char *)(DAT_00026df4 + 1) == '\0') && (*DAT_00026df4 = in_D0w, in_D0w != 0)) {
    uVar2 = (*_thunk_FUN_000150c8)();
    *(undefined1 *)(extraout_A0_01 + 3) = uVar2;
    *(undefined1 *)(extraout_A0_01 + 2) = 4;
    return;
  }
  sVar3 = 0x12;
  do {
    if (*(char *)(psVar4 + 3) == '\0') {
      FUN_00011a46();
      uVar1 = FUN_00011a8c();
      *extraout_A0 = uVar1;
      (*_thunk_FUN_000152b0)();
      uVar2 = (*_thunk_FUN_000150c8)();
      *(undefined1 *)(extraout_A0_00 + 3) = uVar2;
      return;
    }
    sVar3 = sVar3 + -1;
    psVar4 = psVar4 + 2;
  } while (sVar3 != -1);
  return;
}


// ==== FUN_00011a42 @ 00011a42 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 FUN_00011a42(short param_1)

{
  undefined4 uVar1;
  undefined4 in_D1;
  short sVar2;
  undefined8 uVar3;
  
  if (param_1 < 0) {
    uVar3 = (*_thunk_FUN_0001514c)();
    sVar2 = (short)((uint)uVar3 / ((uint)((ulonglong)uVar3 >> 0x20) & 0xffff));
    if (-1 < DAT_00024fdc) {
      sVar2 = -sVar2;
    }
    uVar1 = CONCAT22((short)((ulonglong)uVar3 >> 0x30),DAT_00026dac - sVar2);
  }
  else {
    uVar1 = 0;
  }
  return CONCAT44(uVar1,in_D1);
}


// ==== FUN_00011a46 @ 00011a46 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 FUN_00011a46(void)

{
  short in_D0w;
  undefined4 uVar1;
  undefined4 in_D1;
  short sVar2;
  undefined8 uVar3;
  
  if (in_D0w < 0) {
    uVar3 = (*_thunk_FUN_0001514c)();
    sVar2 = (short)((uint)uVar3 / ((uint)((ulonglong)uVar3 >> 0x20) & 0xffff));
    if (-1 < DAT_00024fdc) {
      sVar2 = -sVar2;
    }
    uVar1 = CONCAT22((short)((ulonglong)uVar3 >> 0x30),DAT_00026dac - sVar2);
  }
  else {
    uVar1 = 0;
  }
  return CONCAT44(uVar1,in_D1);
}


// ==== FUN_00011a84 @ 00011a84 ====

undefined8 FUN_00011a84(undefined4 param_1)

{
  undefined4 in_D0;
  undefined4 in_D1;
  short sVar1;
  short *extraout_A0;
  short *psVar2;
  ulonglong uVar3;
  
  uVar3 = (ulonglong)CONCAT24(param_1._0_2_ - param_1._2_2_,(uint)(ushort)(param_1._2_2_ * 2));
  psVar2 = DAT_00025450;
  sVar1 = DAT_00025314;
  while (sVar1 = sVar1 + -1, sVar1 != -1) {
    if ((psVar2[3] == 1) && ((ushort)(*psVar2 - (short)(uVar3 >> 0x20)) <= (ushort)uVar3)) {
      psVar2[3] = 2;
      *(undefined1 *)((int)psVar2 + 3) = 5;
      *(undefined1 *)(psVar2 + 2) = 2;
      uVar3 = FUN_000123ac();
      psVar2 = extraout_A0;
    }
    psVar2 = psVar2 + 4;
  }
  FUN_00011ae2();
  return CONCAT44(CONCAT22((short)((uint)in_D0 >> 0x10),param_1._0_2_),
                  CONCAT22((short)((uint)in_D1 >> 0x10),param_1._2_2_));
}


// ==== FUN_00011a8c @ 00011a8c ====

undefined8 FUN_00011a8c(void)

{
  undefined4 in_D0;
  undefined4 in_D1;
  short sVar1;
  short *extraout_A0;
  short *psVar2;
  ulonglong uVar3;
  
  uVar3 = (ulonglong)CONCAT24((short)in_D0 - (short)in_D1,(uint)(ushort)((short)in_D1 * 2));
  psVar2 = DAT_00025450;
  sVar1 = DAT_00025314;
  while (sVar1 = sVar1 + -1, sVar1 != -1) {
    if ((psVar2[3] == 1) && ((ushort)(*psVar2 - (short)(uVar3 >> 0x20)) <= (ushort)uVar3)) {
      psVar2[3] = 2;
      *(undefined1 *)((int)psVar2 + 3) = 5;
      *(undefined1 *)(psVar2 + 2) = 2;
      uVar3 = FUN_000123ac();
      psVar2 = extraout_A0;
    }
    psVar2 = psVar2 + 4;
  }
  FUN_00011ae2();
  return CONCAT44(in_D0,in_D1);
}


// ==== FUN_00011ae2 @ 00011ae2 ====

undefined8 FUN_00011ae2(void)

{
  undefined4 in_D0;
  undefined4 in_D1;
  ushort uVar1;
  short sVar2;
  undefined2 *puVar3;
  
  puVar3 = &DAT_00024bfe;
  sVar2 = 0xe;
  do {
    if ((*(char *)(puVar3 + 6) != '\0') && (puVar3[0x11] == 2)) {
      uVar1 = puVar3[4] - (short)in_D0;
      if ((short)uVar1 < 0) {
        uVar1 = -uVar1;
      }
      if (uVar1 <= (ushort)in_D1) {
        *(undefined1 *)(puVar3 + 0x10) = 8;
        *(undefined1 *)((int)puVar3 + 0x21) = 1;
      }
    }
    puVar3 = puVar3 + 0x15;
    sVar2 = sVar2 + -1;
  } while (sVar2 != -1);
  if (DAT_000254f0._0_1_ != '\0') {
    uVar1 = DAT_000254ec - (short)in_D0;
    if ((short)uVar1 < 0) {
      uVar1 = -uVar1;
    }
    if (uVar1 <= (ushort)in_D1) {
      DAT_00025504._0_1_ = 8;
      DAT_00025504._1_1_ = 1;
    }
  }
  return CONCAT44(in_D0,in_D1);
}


// ==== FUN_00011bfc @ 00011bfc ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00011bfc(void)

{
  ushort uVar1;
  ushort uVar2;
  ushort in_D1w;
  
  if ((((DAT_00027296 != 0) && (DAT_00024fd4 != 6)) && (DAT_00024fd4 != 8)) &&
     (uVar2 = 0x80 - DAT_00024fda, uVar2 != 0)) {
    if (uVar2 < 0x14) {
      uVar2 = uVar2 * 8 & 0xf0;
      uVar1 = (*_thunk_FUN_000203be)();
      in_D1w = uVar2 + (uVar1 & 0xf);
      uVar2 = in_D1w >> 3;
      if (((&DAT_0002551a)[(short)uVar2] & '\x01' << (in_D1w & 7)) == 0) {
        return;
      }
    }
    FUN_000154e0(uVar2,in_D1w);
  }
  return;
}


// ==== FUN_00011c5e @ 00011c5e ====

void FUN_00011c5e(void)

{
  int *piVar1;
  int *piVar2;
  
  if (DAT_000252ad != '\0') {
    piVar1 = DAT_00026eb6 + 0x5a;
    piVar2 = DAT_00026eb6;
    do {
      if (*(char *)((int)piVar2 + 0x11) != '\0') {
        *piVar2 = piVar2[2] + *piVar2;
        piVar2[1] = piVar2[3] + piVar2[1];
        if (0xa9 < *(short *)(piVar2 + 1)) {
          *(undefined1 *)((int)piVar2 + 0x11) = 0;
        }
      }
      piVar2 = (int *)((int)piVar2 + 0x12);
    } while ((int)piVar2 < (int)piVar1);
  }
  return;
}


// ==== FUN_00011cae @ 00011cae ====

undefined4 FUN_00011cae(void)

{
  undefined4 in_D0;
  short sVar1;
  undefined **ppuVar2;
  undefined **extraout_A0;
  undefined **ppuVar3;
  
  sVar1 = 4;
  ppuVar2 = &PTR_DAT_000254aa;
  do {
    ppuVar3 = ppuVar2 + 1;
    if ((*(short *)(*ppuVar2 + 4) != 0) && (*(short *)(*ppuVar2 + 0xc) == 0)) {
      sVar1 = FUN_00011cd8();
      ppuVar3 = extraout_A0;
    }
    sVar1 = sVar1 + -1;
    ppuVar2 = ppuVar3;
  } while (sVar1 != -1);
  return in_D0;
}


// ==== FUN_00011cd8 @ 00011cd8 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 FUN_00011cd8(void)

{
  short sVar1;
  short sVar2;
  undefined4 in_D0;
  undefined4 in_D1;
  ushort uVar3;
  short *in_A1;
  undefined2 *puVar4;
  bool bVar5;
  
  sVar1 = in_A1[0xb];
  sVar2 = sVar1 + -1;
  in_A1[0xb] = sVar2;
  if (sVar2 != 0 && 0 < sVar1) goto LAB_00011dde;
  in_A1[10] = in_A1[10] + 1;
  in_A1[0xb] = in_A1[0xc];
  if (in_A1[0xc] != 0) {
    in_A1[0xc] = in_A1[0xc] + -1;
  }
  if (in_A1[9] == 0) {
    if (DAT_000252e4 == 1) {
      DAT_00024fd4 = 0xb;
      DAT_000252e4 = 2;
      DAT_000252b4 = 0;
      DAT_0002535e = 0;
    }
  }
  else if (in_A1[10] == 10) {
    DAT_0002529c = in_A1[9] + DAT_0002529c;
    FUN_00015640();
    bVar5 = SBORROW1(DAT_000252c1,'\x01');
    DAT_000252c1 = DAT_000252c1 - 1;
    if ((DAT_000252c1 == 0 || bVar5 != (short)((ushort)DAT_000252c1 << 8) < 0) &&
       (DAT_000252d3 == '\0')) {
      (*_thunk_FUN_00015694)();
    }
    else {
      (*_thunk_FUN_0001555a)();
    }
    goto LAB_00011dde;
  }
  if (in_A1[9] == 0) {
    if (in_A1[10] < 0x21) goto LAB_00011dde;
    if ((in_A1[10] < 0x22) && (DAT_00024fd4 == 1)) {
      DAT_00024fd4 = 6;
      DAT_00024fc8 = 0;
      DAT_000252ac = 0;
      DAT_000252b4 = 0;
      DAT_00025512 = 100;
    }
    if (in_A1[10] < 0x78) goto LAB_00011dde;
    in_A1[2] = 0;
    DAT_00025511 = 0xff;
  }
  else {
    if (in_A1[10] < 0x78) goto LAB_00011dde;
    DAT_000252c0 = DAT_000252c0 + -1;
    in_A1[6] = -1;
  }
  uVar3 = (ushort)-(*in_A1 - in_A1[1]) >> 1;
  puVar4 = (undefined2 *)(DAT_00024578 + *in_A1);
  do {
    *puVar4 = 0;
    uVar3 = uVar3 - 1;
    puVar4 = puVar4 + 1;
  } while (uVar3 != 0xffff);
LAB_00011dde:
  return CONCAT44(in_D0,in_D1);
}


// ==== FUN_00011de4 @ 00011de4 ====

undefined8 FUN_00011de4(void)

{
  char cVar1;
  undefined4 in_D0;
  byte bVar2;
  undefined4 in_D1;
  ushort uVar3;
  int extraout_A0;
  int extraout_A0_00;
  int iVar4;
  
  uVar3 = (ushort)DAT_000252d6;
  iVar4 = DAT_0002544c;
  while (uVar3 = uVar3 - 1, uVar3 != 0xffff) {
    if ((*(char *)(iVar4 + 0xb) != '\0') &&
       (cVar1 = *(char *)(iVar4 + 0xb) + -1, *(char *)(iVar4 + 0xb) = cVar1, cVar1 == '\0')) {
      FUN_00011e82();
      cVar1 = *(char *)(extraout_A0 + 10) + -1;
      *(char *)(extraout_A0 + 10) = cVar1;
      iVar4 = extraout_A0;
      if (cVar1 != '\0') {
        bVar2 = (byte)(DAT_0002531a >> 4) & 0x1f;
        if ((DAT_0002531a >> 4 & 0x1f) == 0) {
          bVar2 = 3;
        }
        *(byte *)(extraout_A0 + 0xb) = bVar2;
      }
    }
    iVar4 = iVar4 + 0x10;
  }
  uVar3 = (ushort)DAT_000252d7;
  iVar4 = DAT_00025448;
  while (uVar3 = uVar3 - 1, uVar3 != 0xffff) {
    if ((*(char *)(iVar4 + 0xb) != '\0') &&
       (cVar1 = *(char *)(iVar4 + 0xb) + -1, *(char *)(iVar4 + 0xb) = cVar1, cVar1 == '\0')) {
      FUN_00011e82();
      cVar1 = *(char *)(extraout_A0_00 + 10) + -1;
      *(char *)(extraout_A0_00 + 10) = cVar1;
      iVar4 = extraout_A0_00;
      if (cVar1 != '\0') {
        bVar2 = (byte)(DAT_0002531a >> 4) & 0x1f;
        if ((DAT_0002531a >> 4 & 0x1f) == 0) {
          bVar2 = 3;
        }
        *(byte *)(extraout_A0_00 + 0xb) = bVar2;
      }
    }
    iVar4 = iVar4 + 0x10;
  }
  return CONCAT44(in_D0,in_D1);
}


// ==== FUN_00011e82 @ 00011e82 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 FUN_00011e82(void)

{
  undefined4 in_D0;
  ushort uVar1;
  undefined4 in_D1;
  byte bVar2;
  short sVar3;
  undefined4 *in_A0;
  short *psVar4;
  
  bVar2 = (byte)in_D1;
  if ((char)in_D0 != '\x01') {
    if ((char)in_D0 != '\x02') goto LAB_00011f48;
    sVar3 = (ushort)*(byte *)((int)in_A0 + 9) << 2;
    bVar2 = 1;
    if (((short)*in_A0 != *(short *)((int)&DAT_00025390 + (int)sVar3)) &&
       (bVar2 = 0xff, (short)*in_A0 != *(short *)((int)&DAT_00025390 + sVar3 + 2))) {
      bVar2 = 0;
    }
    (*_thunk_FUN_000203be)();
    (*_thunk_FUN_000203be)();
    (*_thunk_FUN_000203be)();
    uVar1 = (*_thunk_FUN_000203be)();
    if ((uVar1 & 0xf) == 0 && -1 < (short)uVar1) {
      bVar2 = -bVar2;
    }
  }
  psVar4 = DAT_00025450;
  if (DAT_00025314 != 0) {
    for (; psVar4[3] != 0; psVar4 = psVar4 + 4) {
    }
    psVar4[3] = 1;
    sVar3 = *(short *)(in_A0 + 1);
    *(undefined1 *)((int)psVar4 + 5) = *(undefined1 *)((int)in_A0 + 9);
    if (bVar2 == 0) {
      bVar2 = (byte)DAT_0002531a;
    }
    *(byte *)(psVar4 + 1) = bVar2;
    if (-1 < (char)bVar2) {
      sVar3 = *(short *)((int)in_A0 + 6);
    }
    *psVar4 = sVar3;
    *(byte *)((int)psVar4 + 3) = bVar2 & 7;
    *(byte *)((int)psVar4 + 3) = *(byte *)((int)psVar4 + 3) & 3;
    *psVar4 = (ushort)(bVar2 & 7) * 4 + *psVar4;
  }
LAB_00011f48:
  return CONCAT44(in_D0,in_D1);
}


// ==== FUN_00011f4e @ 00011f4e ====

void FUN_00011f4e(void)

{
  short sVar1;
  undefined2 *puVar2;
  
  puVar2 = &DAT_000272b8;
  sVar1 = 7;
  do {
    *puVar2 = 0;
    puVar2 = puVar2 + 0xc;
    sVar1 = sVar1 + -1;
  } while (sVar1 != -1);
  FUN_00012066();
  return;
}


// ==== FUN_00011f76 @ 00011f76 ====

void FUN_00011f76(void)

{
  DAT_000272ba = DAT_00026de6;
  DAT_000272be = DAT_000254c2;
  DAT_000272c2 = 200;
  DAT_000272c4 = 0x40;
  DAT_000272c6 = 0xffff;
  DAT_000272b8 = 0;
  DAT_000272d2 = DAT_00026da8;
  DAT_000272d6 = DAT_000254ca;
  DAT_000272da = 0x17c;
  DAT_000272dc = 0x3e;
  DAT_000272de = 0xffff;
  DAT_000272d0 = 0;
  DAT_000272ea = DAT_00026de6;
  DAT_000272ee = DAT_000254c2;
  DAT_000272f2 = 0xa0;
  DAT_000272f4 = 0x39;
  DAT_000272f6 = 0xffff;
  DAT_000272e8 = 0;
  DAT_00027302 = DAT_00026da8;
  DAT_00027306 = DAT_000254ca;
  DAT_0002730a = 0x14a;
  DAT_0002730c = 0x40;
  DAT_0002730e = 0xffff;
  DAT_00027300 = 0;
  DAT_0002731a = DAT_00026d8e;
  DAT_0002731e = DAT_000254c6;
  DAT_00027322 = 500;
  DAT_00027324 = 0x40;
  DAT_00027326 = 1;
  DAT_00027318 = 0;
  DAT_00027332 = DAT_00026e04;
  DAT_00027336 = DAT_000254ce;
  DAT_0002733a = 0x15e;
  DAT_0002733c = 0x40;
  DAT_0002733e = 1;
  DAT_00027330 = 0;
  DAT_0002734a = DAT_00026de6;
  DAT_0002734e = DAT_000254c2;
  DAT_00027352 = 0x140;
  DAT_00027354 = 0x40;
  DAT_00027356 = 0xffff;
  DAT_00027348 = 0;
  return;
}


// ==== FUN_00012066 @ 00012066 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00012066(void)

{
  undefined4 uVar1;
  undefined4 uVar2;
  short sVar3;
  short sVar4;
  short sVar5;
  short sVar6;
  short sVar7;
  short *psVar8;
  short *psVar9;
  
  sVar6 = 3;
  sVar7 = 0;
  psVar8 = &DAT_000272b8;
  do {
    if (((DAT_000254a6 == '\0') && (DAT_00025447 == '\0')) &&
       (((*(int *)(psVar8 + 1) != 0 && (psVar9 = psVar8, *psVar8 != 0)) ||
        ((psVar9 = psVar8 + 0xc, *(int *)(psVar8 + 0xd) != 0 && (*psVar9 != 0)))))) {
      if (*(int *)(psVar9 + 1) == *(int *)(psVar8 + 8)) {
        if (*(int *)(psVar9 + 5) != *(int *)(psVar8 + 10)) {
          *(int *)(psVar8 + 10) = *(int *)(psVar9 + 5);
          (*_thunk_FUN_0001eb4c)();
        }
      }
      else {
        uVar1 = *(undefined4 *)(psVar9 + 1);
        uVar2 = *(undefined4 *)(psVar9 + 3);
        sVar3 = psVar9[5];
        sVar4 = psVar9[6];
        sVar5 = psVar9[7];
        *(undefined4 *)(psVar8 + 8) = uVar1;
        *(undefined4 *)(psVar8 + 10) = *(undefined4 *)(psVar9 + 5);
        (*_thunk_FUN_0001ea28)(uVar2,sVar7,(int)sVar3,(int)sVar4,(int)sVar5,uVar1);
        (*_thunk_FUN_0001ea28)();
        (*_thunk_FUN_0001ea28)();
      }
    }
    else if (*(int *)(psVar8 + 8) != 0) {
      (*_thunk_FUN_0001eac0)();
      (*_thunk_FUN_0001eac0)();
      (*_thunk_FUN_0001eac0)();
      psVar8[8] = 0;
      psVar8[9] = 0;
    }
    sVar7 = sVar7 + 1;
    psVar8 = psVar8 + 0x18;
    sVar6 = sVar6 + -1;
  } while (sVar6 != -1);
  return;
}


// ==== FUN_00012132 @ 00012132 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00012132(void)

{
  short sVar1;
  undefined2 uVar2;
  short sVar3;
  short sVar4;
  ushort uVar5;
  ushort uVar6;
  short *psVar7;
  bool bVar8;
  
  if (DAT_000254a6 != '\0') {
    return;
  }
  if (DAT_00025447 != '\0') {
    return;
  }
  DAT_000272d0 = 0;
  if (DAT_00025378 != DAT_0002537c) {
    if (DAT_00025378 < DAT_0002537c) {
      DAT_0002537c = DAT_0002537c - 2;
      if (DAT_0002537c < DAT_00025378) {
        DAT_0002537c = DAT_00025378;
      }
    }
    else {
      DAT_0002537c = DAT_0002537c + 1;
    }
  }
  if (DAT_0002537c != 0) {
    DAT_000272d0 = 0xff00;
    uVar5 = (DAT_00024fc8 >> 4) + DAT_0002537a + (DAT_00025352 >> 7);
    DAT_000272da = DAT_0002537e;
    if (uVar5 != DAT_0002537e) {
      if (uVar5 < DAT_0002537e) {
        DAT_0002537e = DAT_0002537e - 10;
        DAT_000272da = DAT_0002537e;
        if (DAT_0002537e < uVar5) {
          DAT_0002537e = uVar5;
          DAT_000272da = uVar5;
        }
      }
      else {
        DAT_0002537e = DAT_0002537e + 0x14;
        DAT_000272da = DAT_0002537e;
        if (uVar5 <= DAT_0002537e) {
          DAT_0002537e = uVar5;
          DAT_000272da = uVar5;
        }
      }
    }
  }
  DAT_000272b8 = DAT_000252ba;
  psVar7 = &DAT_0002517a;
  sVar1 = 3;
  uVar6 = 0xffff;
  uVar5 = 0;
  do {
    if ((*psVar7 != 0) && (*psVar7 < 3)) {
      sVar3 = psVar7[0x10] - DAT_00024fca;
      if (sVar3 < 0) {
        sVar3 = -sVar3;
      }
      sVar4 = psVar7[0x13] - DAT_00024fc8;
      if (sVar4 < 0) {
        sVar4 = -sVar4;
      }
      if ((ushort)(sVar4 + sVar3) < uVar6) {
        uVar6 = sVar4 + sVar3;
      }
      uVar5 = psVar7[9] | uVar5;
    }
    psVar7 = psVar7 + 0x1a;
    sVar1 = sVar1 + -1;
  } while (sVar1 != -1);
  DAT_00027300 = 0;
  bVar8 = true;
  DAT_000272dc = DAT_0002537c;
  uVar2 = FUN_000122ce();
  if (!bVar8) {
    DAT_00027300 = CONCAT11(0xff,(undefined1)DAT_00027300);
    DAT_0002730c = uVar2;
  }
  if ((DAT_000252e4 == 2) || (DAT_000252e4 == 3)) {
    DAT_00027362 = DAT_00026dca;
    DAT_00027366 = DAT_000254de;
    DAT_0002736a = 0x1c2;
    DAT_0002736c = 0x40;
    DAT_0002736e = 0xffff;
    _DAT_00027360 = CONCAT11(0xff,DAT_00027360_1);
    DAT_00027330 = 0;
  }
  else if (DAT_000252e4 == 1) {
    DAT_0002733a = 800;
    DAT_0002733c = 0x22;
    DAT_0002733e = 0xffff;
    DAT_00027330 = CONCAT11(0xff,(undefined1)DAT_00027330);
    goto LAB_000122b4;
  }
  DAT_0002733a = 0x15e;
  DAT_0002733e = 1;
LAB_000122b4:
  if (_DAT_000270b4 != 0) {
    _DAT_00027360 = 0;
  }
  DAT_00027354 = DAT_000270b6;
  DAT_00027348 = _DAT_000270b4;
  DAT_00027336 = DAT_000254ce;
  DAT_00027332 = DAT_00026e04;
  DAT_000272e8 = uVar5;
  return;
}


// ==== FUN_000122ce @ 000122ce ====

short FUN_000122ce(void)

{
  ushort in_D0w;
  ushort uVar1;
  short sVar2;
  
  uVar1 = in_D0w >> 4;
  if (uVar1 < 0x2d) {
    if (uVar1 < 6) {
      sVar2 = uVar1 << 2;
    }
    else {
      sVar2 = uVar1 + 0x14;
    }
    return 0x40 - sVar2;
  }
  return 0;
}


// ==== FUN_000122f6 @ 000122f6 ====

short FUN_000122f6(void)

{
  ushort in_D0w;
  
  if (in_D0w >> 5 < 0x41) {
    return 0x40 - (in_D0w >> 5);
  }
  return 0;
}


// ==== FUN_00012306 @ 00012306 ====

void FUN_00012306(void)

{
  FUN_000122f6();
  return;
}


// ==== FUN_00012324 @ 00012324 ====

void FUN_00012324(void)

{
  if (DAT_00026d8e != 0) {
    DAT_00027318._0_1_ = 0xff;
    DAT_00027328 = 0;
    DAT_00027324 = FUN_00012306();
  }
  return;
}


// ==== FUN_0001233e @ 0001233e ====

void FUN_0001233e(void)

{
  DAT_00027318 = 0;
  DAT_00027330._0_1_ = 0xff;
  DAT_00027328 = 0;
  DAT_0002733c = FUN_00012306();
  return;
}


// ==== FUN_00012354 @ 00012354 ====

void FUN_00012354(void)

{
  DAT_00027362 = DAT_00026d92;
  DAT_00027366._2_2_ = 0x1646;
  DAT_0002736a = 0x1c2;
  DAT_0002736c = 0x40;
  DAT_0002736e = 1;
  DAT_00027348 = 0;
  DAT_00027360 = 0xff;
  DAT_00027358 = 0;
  return;
}


// ==== FUN_00012380 @ 00012380 ====

void FUN_00012380(void)

{
  DAT_00027362 = DAT_00026df8;
  DAT_00027366._2_2_ = 0x1a5a;
  DAT_0002736a = 0x15e;
  DAT_0002736c = 0x40;
  DAT_0002736e = 1;
  DAT_00027348 = 0;
  DAT_00027360 = 0xff;
  DAT_00027358 = 0;
  return;
}


// ==== FUN_000123ac @ 000123ac ====

void FUN_000123ac(void)

{
  ushort uVar1;
  
  DAT_00027362 = DAT_00026dfc;
  DAT_00027366._2_2_ = 0x19ac;
  DAT_0002736a = 0x17c;
  uVar1 = FUN_00012306();
  DAT_0002736c = uVar1 >> 1;
  DAT_0002736e = 1;
  DAT_00027348 = 0;
  DAT_00027360 = 0xff;
  DAT_00027358 = 0;
  return;
}


// ==== FUN_000123dc @ 000123dc ====

void FUN_000123dc(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  short sVar3;
  code *pcVar2;
  undefined4 extraout_A0;
  
  pcVar2 = DAT_0002553e;
  DAT_00025542 = param_2;
  if ((DAT_00027378 == 0) || ((*DAT_0002553e)(), DAT_00025447 != '\0')) {
    iVar1 = DAT_00026e6e;
    DAT_00027378 = (**(code **)(DAT_00026e6e + -0x96))();
    if (DAT_00027378 == 0) {
      return;
    }
    (*(code *)CONCAT22((short)((uint)(DAT_00027378 << 2) >> 0x10),(short)(DAT_00027378 << 2) + 4))()
    ;
    DAT_0002737c = extraout_A0;
    DAT_0002553a = (**(code **)(iVar1 + -0x96))();
    pcVar2 = (code *)CONCAT22((short)((uint)(DAT_0002553a << 2) >> 0x10),
                              (short)(DAT_0002553a << 2) + 4);
    DAT_0002553e = pcVar2;
    (*pcVar2)();
  }
  else {
    do {
      sVar3 = (*pcVar2)();
    } while (sVar3 != 0);
  }
  (*pcVar2)();
  if (DAT_00025447 == '\0') {
    (*pcVar2)();
    DAT_00027380._0_1_ = 0xff;
  }
  return;
}


// ==== FUN_00012470 @ 00012470 ====

void FUN_00012470(void)

{
  code *pcVar1;
  int iVar2;
  short sVar3;
  
  pcVar1 = DAT_0002553e;
  if (DAT_00027378 != 0) {
    (*DAT_0002553e)();
    DAT_00027380 = 0;
    if (DAT_00025447 == '\0') {
      do {
        sVar3 = (*pcVar1)();
      } while (sVar3 != 0);
    }
    (*pcVar1)();
    iVar2 = DAT_00026e6e;
    (**(code **)(DAT_00026e6e + -0x9c))();
    (**(code **)(iVar2 + -0x9c))();
    DAT_00027378 = 0;
    DAT_0002737c = 0;
    DAT_0002553a = 0;
    DAT_0002553e = (code *)0x0;
  }
  return;
}


// ==== FUN_000124d8 @ 000124d8 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_000124d8(void)

{
                    /* WARNING: Could not recover jumptable at 0x000124d8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*_thunk_FUN_0001020e)();
  return;
}


// ==== FUN_000124dc @ 000124dc ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 FUN_000124dc(int *param_1)

{
  undefined4 in_D0;
  undefined4 in_D1;
  
  if ((param_1 != (int *)0x0) && (*param_1 != 0)) {
    (*_thunk_FUN_0002090a)(*param_1);
  }
  *param_1 = 0;
  return CONCAT44(in_D0,in_D1);
}


// ==== FUN_000124e0 @ 000124e0 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 FUN_000124e0(void)

{
  undefined4 in_D0;
  undefined4 in_D1;
  int *in_A0;
  
  if ((in_A0 != (int *)0x0) && (*in_A0 != 0)) {
    (*_thunk_FUN_0002090a)(*in_A0);
  }
  *in_A0 = 0;
  return CONCAT44(in_D0,in_D1);
}


// ==== FUN_00012502 @ 00012502 ====

void FUN_00012502(void)

{
  int in_A0;
  int in_A1;
  int extraout_A1;
  
  if (in_A0 != 0) {
    FUN_000124e0();
    in_A1 = extraout_A1;
  }
  if (in_A1 != 0) {
    FUN_000124e0();
  }
  return;
}


// ==== FUN_0001252c @ 0001252c ====

undefined8 FUN_0001252c(void)

{
  byte bVar1;
  undefined1 uVar2;
  undefined4 in_D0;
  short sVar3;
  undefined4 in_D1;
  short sVar4;
  int in_A0;
  ushort *in_A1;
  ushort *unaff_A2;
  ushort *puVar5;
  ushort *puVar6;
  
  sVar4 = DAT_00025310 + DAT_0002530e * 4;
  sVar4 = CONCAT11((char)((ushort)sVar4 >> 8),(&DAT_000233af)[sVar4]) * 2;
  bVar1 = *(byte *)(in_A0 + sVar4);
  uVar2 = *(undefined1 *)(in_A0 + 1 + (int)sVar4);
  sVar3 = (short)in_D0 * 4;
  *unaff_A2 = (ushort)bVar1;
  puVar5 = unaff_A2 + 2;
  unaff_A2[1] = CONCAT11((char)((ushort)sVar4 >> 8),uVar2);
  *puVar5 = *in_A1;
  puVar6 = unaff_A2 + 3;
  *puVar5 = sVar3 + *puVar5;
  *puVar6 = in_A1[1];
  *puVar6 = sVar3 + *puVar6;
  sVar4 = bVar1 - 1;
  do {
    puVar5 = in_A1 + 3;
    puVar6 = unaff_A2 + 5;
    unaff_A2[4] = in_A1[2];
    in_A1 = in_A1 + 4;
    *puVar6 = *puVar5;
    *puVar6 = sVar3 + *puVar6;
    *(undefined4 *)(unaff_A2 + 6) = *(undefined4 *)in_A1;
    sVar4 = sVar4 + -1;
    unaff_A2 = unaff_A2 + 4;
  } while (sVar4 != -1);
  return CONCAT44(in_D0,in_D1);
}


// ==== FUN_00012570 @ 00012570 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00012570(void)

{
  int iVar1;
  
  iVar1 = DAT_00026ec4;
  DAT_00026e76 = (**(code **)(DAT_00026ec4 + -0x228))();
  if (DAT_00026e76 != 0) {
    DAT_00026e72 = (**(code **)(iVar1 + -0x228))();
    if (DAT_00026e72 != 0) {
      (*_thunk_FUN_0001e8b8)();
      return;
    }
  }
                    /* WARNING: Could not recover jumptable at 0x000124d8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*_thunk_FUN_0001020e)();
  return;
}


// ==== FUN_0001259e @ 0001259e ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0001259e(void)

{
  int iVar1;
  
  iVar1 = DAT_00026ec4;
  if (DAT_00026e72 != 0) {
    (**(code **)(DAT_00026ec4 + -0x19e))();
  }
  if (DAT_00026e76 != 0) {
    (**(code **)(iVar1 + -0x19e))();
  }
  (*_thunk_FUN_0001e94c)();
  return;
}


// ==== FUN_000125c6 @ 000125c6 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_000125c6(void)

{
  int iVar1;
  
  iVar1 = (**(code **)(_DAT_00000004 + -0x126))();
  DAT_0002739c = *(undefined4 *)(iVar1 + 0xb8);
  DAT_00027390 = iVar1;
  *(undefined4 *)(iVar1 + 0xb8) = 0xffffffff;
  DAT_00027394 = *(int **)(iVar1 + 0x32);
  DAT_00027398 = *(undefined4 *)(iVar1 + 0x2e);
  DAT_0002738e = (**(code **)(DAT_00026ec4 + -300))();
  DAT_00026888 = 0xdff000;
  DAT_000273a0 = 0;
  DAT_00026eb0 = 0;
  if (*DAT_00027394 == 0x48e7fffe) {
    *(undefined **)(DAT_00027390 + 0x32) = &DAT_00012640;
  }
  else {
    DAT_000270b2 = 0x10;
    DAT_000273a0 = 1;
    DAT_00026eb0 = 1;
  }
  return;
}


// ==== FUN_0001276c @ 0001276c ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_0001276c(void)

{
  int iVar1;
  
  iVar1 = DAT_00027390;
  *(undefined4 *)(DAT_00027390 + 0xb8) = DAT_0002739c;
  *(undefined4 *)(iVar1 + 0x32) = DAT_00027394;
  *(undefined4 *)(iVar1 + 0x2e) = DAT_00027398;
  (**(code **)(_DAT_00000004 + -300))();
  return 0;
}


// ==== FUN_00012794 @ 00012794 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 FUN_00012794(void)

{
  undefined4 in_D0;
  short sVar1;
  undefined4 in_D1;
  short sVar2;
  byte *pbVar3;
  short *psVar4;
  undefined8 uVar5;
  
  DAT_00026eba = (short *)(*_thunk_FUN_0001feb4)(s_newarmyfont_000235fc);
  if (DAT_00026eba != (short *)0x0) {
    DAT_00026ec0 = *DAT_00026eba;
    DAT_00026ebe = *(char *)(DAT_00026eba + 1);
    DAT_00026ebf = *(char *)((int)DAT_00026eba + 3);
    DAT_00026d66 = (byte *)((int)(DAT_00026eba + 2) +
                           (int)(short)((byte)((DAT_00026ebf + '\x01') - DAT_00026ebe) + 1 & 0xfffe)
                           );
    sVar1 = 0x5f;
    sVar2 = 0;
    pbVar3 = (byte *)(DAT_00026eba + 2);
    psVar4 = &DAT_00026ca6;
    do {
      *psVar4 = sVar2;
      sVar2 = ((ushort)(*pbVar3 + 0xf) >> 4) * 2 * DAT_00026ec0 + sVar2;
      sVar1 = sVar1 + -1;
      pbVar3 = pbVar3 + 1;
      psVar4 = psVar4 + 1;
    } while (sVar1 != -1);
    return CONCAT44(in_D0,in_D1);
  }
                    /* WARNING: Could not recover jumptable at 0x000124d8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  uVar5 = (*_thunk_FUN_0001020e)();
  return uVar5;
}


// ==== FUN_000127f6 @ 000127f6 ====

void FUN_000127f6(void)

{
  FUN_000124e0();
  return;
}


// ==== FUN_0001283e @ 0001283e ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0001283e(void)

{
  DAT_00026df4 = FUN_000158ec();
  if (DAT_00026df4 != 0) {
    DAT_00026e80 = FUN_000158ec();
    if (DAT_00026e80 != 0) {
      DAT_00026ea8 = FUN_000158ec();
      if (DAT_00026ea8 != 0) {
        DAT_00026eb6 = FUN_000158ec();
        if (DAT_00026eb6 != 0) {
          DAT_0002738a = 0x410;
          DAT_00027386 = FUN_000158fe();
          if (DAT_00027386 != 0) {
            DAT_00026ea4 = FUN_000158ec();
            if (DAT_00026ea4 != 0) {
              DAT_00026ed2 = FUN_000158ec();
              if (DAT_00026ed2 != 0) {
                return;
              }
            }
          }
        }
      }
    }
  }
                    /* WARNING: Could not recover jumptable at 0x000124d4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*_thunk_FUN_0001020e)();
  return;
}


// ==== FUN_000128d6 @ 000128d6 ====

void FUN_000128d6(void)

{
  FUN_000124e0();
  FUN_000124e0();
  FUN_000124e0();
  FUN_000124e0();
  FUN_000124e0();
  FUN_000124e0();
  FUN_000124e0();
  return;
}


// ==== FUN_00012910 @ 00012910 ====

void FUN_00012910(void)

{
  int iVar1;
  int unaff_A6;
  
  iVar1 = FUN_000158ec();
  DAT_00026dda = iVar1;
  if (iVar1 != 0) {
    *(undefined1 *)(iVar1 + 8) = 2;
    *(char **)(iVar1 + 10) = s_Interrupt_Server_00023616;
    *(undefined1 *)(iVar1 + 9) = 0xf6;
    *(undefined4 **)(iVar1 + 0xe) = &DAT_0002531a;
    *(code **)(iVar1 + 0x12) = FUN_00011754;
    (**(code **)(unaff_A6 + -0xa8))();
    return;
  }
  FUN_000124d8();
  return;
}


// ==== FUN_0001295a @ 0001295a ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_0001295a(void)

{
  undefined4 uVar1;
  
  if (DAT_00026dda == 0) {
    (*_thunk_FUN_0001556e)(s_No_Interrupt_handler_detected__0001297e);
    uVar1 = 0;
  }
  else {
    (**(code **)(DAT_00026ec4 + -0xae))();
    uVar1 = FUN_000124e0();
  }
  return uVar1;
}


// ==== FUN_000129c8 @ 000129c8 ====

undefined8 FUN_000129c8(void)

{
  undefined4 in_D0;
  undefined4 in_D1;
  
  FUN_000165c4(s_In_init_asm_000129ba);
  return CONCAT44(in_D0,in_D1);
}


// ==== FUN_000129dc @ 000129dc ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_000129dc(void)

{
  undefined4 uVar1;
  int iVar2;
  short sVar3;
  int extraout_A0;
  uint extraout_A0_00;
  uint extraout_A0_01;
  uint uVar4;
  int extraout_A0_02;
  int extraout_A0_03;
  ushort uVar5;
  
  uVar1 = (*_thunk_FUN_00015bc6)();
  DAT_00024582 = extraout_A0;
  if ((extraout_A0 != 0) &&
     (DAT_00026d9a = uVar1, uVar1 = (*_thunk_FUN_00015bc6)(), DAT_0002458e = extraout_A0_00,
     extraout_A0_00 != 0)) {
    sVar3 = *(short *)(extraout_A0_00 + 4) + -1;
    uVar4 = extraout_A0_00;
    DAT_00026dd2 = uVar1;
    do {
      uVar5 = (ushort)uVar4;
      iVar2 = (*_thunk_FUN_0002050e)(uVar5);
      *(undefined2 *)(iVar2 + 8) = 2;
      uVar4 = (uint)uVar5;
      sVar3 = sVar3 + -1;
    } while (sVar3 != -1);
    uVar1 = (*_thunk_FUN_00015bc6)();
    DAT_00024592 = extraout_A0_01;
    if (extraout_A0_01 != 0) {
      sVar3 = *(short *)(extraout_A0_01 + 4) + -1;
      uVar4 = extraout_A0_01;
      DAT_00026e60 = uVar1;
      do {
        uVar5 = (ushort)uVar4;
        iVar2 = (*_thunk_FUN_0002050e)(uVar5);
        *(undefined2 *)(iVar2 + 8) = 2;
        uVar4 = (uint)uVar5;
        sVar3 = sVar3 + -1;
      } while (sVar3 != -1);
      uVar1 = (*_thunk_FUN_00015bc6)();
      DAT_0002459a = extraout_A0_02;
      if (extraout_A0_02 != 0) {
        DAT_00024596 = uVar1;
        uVar1 = (*_thunk_FUN_00015bc6)();
        DAT_00024586 = extraout_A0_03;
        if (extraout_A0_03 != 0) {
          DAT_00026dc6 = uVar1;
          return;
        }
      }
    }
  }
                    /* WARNING: Could not recover jumptable at 0x000124d8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*_thunk_FUN_0001020e)();
  return;
}


// ==== FUN_00012a92 @ 00012a92 ====

void FUN_00012a92(void)

{
  FUN_00012502();
  FUN_00012502();
  FUN_00012502();
  FUN_00012502();
  FUN_00012502();
  FUN_00012502();
  return;
}


// ==== FUN_00012adc @ 00012adc ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00012adc(void)

{
  int iVar1;
  int iVar2;
  undefined4 in_D0;
  short sVar4;
  undefined4 uVar3;
  short sVar5;
  short *psVar6;
  
  FUN_00013554();
  _DAT_00025312 = 0;
  DAT_000252c0 = 0;
  DAT_000252c1 = 0;
  DAT_000252d4 = 0;
  DAT_000252d2 = 0;
  DAT_000252d3 = 0;
  sVar4 = 0;
  psVar6 = &DAT_00025498;
  sVar5 = DAT_0002530e;
  while (sVar5 = sVar5 + -1, sVar5 != -1) {
    sVar4 = *psVar6 + sVar4;
    psVar6 = psVar6 + 1;
  }
  DAT_0002457c = 0;
  (**(code **)(DAT_00026e6e + -0x1e))
            (*(undefined4 *)
              ((int)&PTR_s_maps_a_map_0002545c + (int)(short)((DAT_00025310 + sVar4 + -1) * 4)));
  iVar2 = DAT_00026e6e;
  (**(code **)(DAT_00026e6e + -0x2a))();
  iVar1 = DAT_00026e44;
  (**(code **)(iVar2 + -0x2a))();
  DAT_000252e2 = (short)DAT_00026e44 * 4 + -8;
  DAT_00024578 = FUN_000158ec();
  iVar2 = DAT_00026e6e;
  if (DAT_00024578 != 0) {
    (**(code **)(DAT_00026e6e + -0x2a))();
    (**(code **)(iVar2 + -0x24))();
    DAT_00025316 = (short)iVar1;
    DAT_00024580 = DAT_00025316 << 2;
    iVar1 = DAT_00024578 + iVar1;
    DAT_0002457c = CONCAT22((short)((uint)iVar1 >> 0x10),(short)iVar1 + -2);
    FUN_00012d5a();
    return in_D0;
  }
  uVar3 = FUN_000124d8();
  return uVar3;
}


// ==== FUN_00012bbe @ 00012bbe ====

undefined8 FUN_00012bbe(void)

{
  undefined4 in_D0;
  undefined4 in_D1;
  
  FUN_000124e0();
  FUN_000124e0();
  FUN_000124e0();
  FUN_000124e0();
  FUN_000124e0();
  if (DAT_000253b4._0_1_ != '\0') {
    DAT_000253b4._0_1_ = '\0';
    FUN_000124e0();
    FUN_00012502();
  }
  if (DAT_000253d2._0_1_ != '\0') {
    DAT_000253d2._0_1_ = '\0';
    FUN_000124e0();
    FUN_00012502();
  }
  if (DAT_000253f0._0_1_ != '\0') {
    DAT_000253f0._0_1_ = '\0';
    FUN_000124e0();
    FUN_00012502();
  }
  if (DAT_0002540e._0_1_ != '\0') {
    DAT_0002540e._0_1_ = '\0';
    FUN_000124e0();
    FUN_00012502();
  }
  DAT_000252c9 = 0;
  return CONCAT44(in_D0,in_D1);
}


// ==== FUN_00012c84 @ 00012c84 ====

undefined8 FUN_00012c84(void)

{
  ushort uVar1;
  bool bVar2;
  undefined4 in_D0;
  undefined4 in_D1;
  short sVar3;
  short sVar4;
  ushort *puVar5;
  short *psVar6;
  undefined *puVar7;
  undefined *puVar8;
  
  sVar3 = DAT_00025310 + DAT_0002530e * 4;
  puVar7 = &DAT_00023444 + (short)(CONCAT11((char)((ushort)sVar3 >> 8),(&DAT_000233af)[sVar3]) << 2)
  ;
  sVar4 = ((ushort)((uint)(DAT_0002457c - (int)DAT_00024578) >> 1) & 0x7fff) - 1;
  psVar6 = &DAT_0002524a;
  DAT_0002524a = 0;
  DAT_0002524c = 0;
  DAT_0002525e = 0;
  DAT_00025260 = 0;
  DAT_00025272 = 0;
  DAT_00025274 = 0;
  DAT_00025286 = 0;
  DAT_00025288 = 0;
  bVar2 = false;
  sVar3 = 0;
  puVar5 = DAT_00024578;
  do {
    uVar1 = *puVar5 >> 2 & 0x1ff;
    if (uVar1 == 0x114) {
      bVar2 = (bool)(bVar2 ^ 1);
      if (bVar2) {
        *psVar6 = sVar3;
      }
      else {
        psVar6[1] = sVar3;
        psVar6[7] = -1;
        psVar6[3] = 0;
        puVar8 = puVar7 + 1;
        *(undefined *)((int)psVar6 + 7) = *puVar7;
        psVar6[2] = 0;
        puVar7 = puVar7 + 2;
        *(undefined *)((int)psVar6 + 5) = *puVar8;
        psVar6 = psVar6 + 10;
      }
    }
    else if (uVar1 == 0x115) {
      bVar2 = (bool)(bVar2 ^ 1);
      if (bVar2) {
        *psVar6 = sVar3;
      }
      else {
        psVar6[1] = sVar3;
        psVar6[7] = 1;
        psVar6[3] = 0;
        puVar8 = puVar7 + 1;
        *(undefined *)((int)psVar6 + 7) = *puVar7;
        psVar6[2] = 0;
        puVar7 = puVar7 + 2;
        *(undefined *)((int)psVar6 + 5) = *puVar8;
        psVar6 = psVar6 + 10;
      }
    }
    sVar3 = sVar3 + 8;
    sVar4 = sVar4 + -1;
    puVar5 = puVar5 + 1;
  } while (sVar4 != -1);
  return CONCAT44(in_D0,in_D1);
}


// ==== FUN_00012d5a @ 00012d5a ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00012d5a(void)

{
  ushort uVar1;
  undefined4 in_D0;
  undefined4 uVar2;
  short sVar3;
  ushort uVar4;
  short *psVar5;
  short *psVar6;
  short *psVar7;
  int extraout_A0;
  int extraout_A0_00;
  int extraout_A0_01;
  int iVar8;
  undefined4 extraout_A1;
  undefined4 extraout_A1_00;
  undefined4 extraout_A1_01;
  undefined4 extraout_A1_02;
  undefined4 *unaff_A2;
  
  DAT_00025390 = 0;
  DAT_00025394 = 0;
  DAT_00025398 = 0;
  DAT_0002539c = 0;
  FUN_000129c8();
  FUN_00012c84();
  DAT_000253d2 = 0;
  DAT_000253e2 = 0;
  DAT_000253e8 = 0;
  DAT_000252c7 = '\0';
  DAT_0002550f = 0;
  DAT_0002540e = 0;
  DAT_000252c8 = '\0';
  DAT_0002541e = 0;
  DAT_00025424 = 0;
  DAT_0002542c = 0xffff;
  DAT_0002543c = 0;
  DAT_00025442 = 0;
  DAT_000253b4 = 0;
  DAT_000252ca = '\0';
  DAT_000253c4 = 0;
  DAT_000253ca = 0;
  DAT_000253f0 = 0;
  DAT_000252cb = '\0';
  DAT_00025400 = 0;
  DAT_00025406 = 0;
  DAT_000252d7 = '\0';
  DAT_000252d5 = '\0';
  DAT_000252d6 = '\0';
  DAT_00025550 = '\0';
  uVar4 = 0;
  iVar8 = DAT_00024578;
  uVar2 = extraout_A1;
  do {
    if ((*(ushort *)(iVar8 + (short)uVar4) & 0x8000) != 0) {
      uVar1 = (ushort)((*(ushort *)(iVar8 + (short)uVar4) & 0xffff7fff) >> 2) & 0x1ff;
      if (uVar1 == 4) {
        DAT_00025550 = -1;
        DAT_000252d7 = DAT_000252d7 + '\x01';
      }
      else if (uVar1 == 3) {
        DAT_00025550 = -1;
        DAT_000252d6 = DAT_000252d6 + '\x01';
      }
      else if (uVar1 == 0xf) {
        DAT_00025550 = -1;
        DAT_000252d5 = DAT_000252d5 + '\x01';
      }
      else if (uVar1 == 0x21) {
        if (DAT_000252c9 == '\0') {
          DAT_000252c9 = -1;
          DAT_0002542c = 0xffff;
          _DAT_00025312 = 0;
          DAT_00025436 = 0x21;
          DAT_00025434 = 4;
          DAT_0002543a = 0;
          DAT_0002542e = 0;
          DAT_00025432 = 0;
          DAT_0002543e = 0x14;
          DAT_00025428 = uVar4 - 0xa0;
          DAT_0002542a = uVar4 + 0x20;
        }
      }
      else if (uVar1 == 0x10d) {
        if (DAT_000252c7 == '\0') {
          DAT_000252c7 = -1;
          DAT_000252c0 = DAT_000252c0 + '\x01';
          DAT_000252c1 = DAT_000252c1 + '\x01';
          DAT_000253d2 = 0xffff;
          DAT_000253d8 = 0xe;
          DAT_000253dc = 0x1b;
          DAT_000253e0 = 0x1194;
          DAT_000253da = 2;
          DAT_000253ce = uVar4 - 0x20;
          DAT_000253d0 = uVar4 + 0xa0;
          unaff_A2 = (undefined4 *)&DAT_00025066;
          FUN_0001252c(0x10d);
          uVar2 = extraout_A1_00;
        }
      }
      else if (uVar1 == 0xf2) {
        if (DAT_000252c8 == '\0') {
          DAT_000252c8 = -1;
          DAT_000252c0 = DAT_000252c0 + '\x01';
          DAT_000252c1 = DAT_000252c1 + '\x01';
          DAT_0002540e = 0xffff;
          DAT_00025414 = 0xf;
          DAT_00025418 = 0x15;
          DAT_0002541c = 6000;
          DAT_00025416 = 3;
          DAT_00025420 = 0x14;
          DAT_0002540a = uVar4 - 0x20;
          DAT_0002540c = uVar4 + 0x7c;
          unaff_A2 = (undefined4 *)&DAT_000250e6;
          FUN_0001252c(0xf2);
          uVar2 = extraout_A1_01;
        }
      }
      else if (uVar1 == 0xe4) {
        if (DAT_000252ca == '\0') {
          DAT_000252ca = -1;
          DAT_000252c0 = DAT_000252c0 + '\x01';
          DAT_000252c1 = DAT_000252c1 + '\x01';
          DAT_000253b4 = 0xffff;
          DAT_000253ba = 8;
          DAT_000253be = 0x1b;
          DAT_000253c2 = 0x9c4;
          DAT_000253bc = 1;
          DAT_000253c6 = 0x14;
          DAT_000253b0 = uVar4 - 0x20;
          DAT_000253b2 = uVar4 + 0x80;
          unaff_A2 = &DAT_00024fe6;
          FUN_0001252c(0xe4);
          uVar2 = extraout_A1_02;
        }
      }
      else if (uVar1 == 0xcc) {
        if (DAT_000252cb == '\0') {
          DAT_000252cb = -1;
          DAT_000252c0 = DAT_000252c0 + '\x01';
          DAT_000252c1 = DAT_000252c1 + '\x01';
          DAT_000253f0 = 0xffff;
          DAT_000253fa = 0x1c;
          DAT_000253f6 = 4;
          DAT_000253fe = 1000;
          DAT_000253f8 = 1;
          DAT_00025402 = 0x14;
          DAT_000253ec = uVar4 - 0x10;
          DAT_000253ee = uVar4 + 0x10;
          FUN_0001252c(0xcc,iVar8,uVar2,unaff_A2);
        }
      }
      else if ((uVar1 == 2) && (DAT_000252d4 = DAT_000252d4 + '\x01', DAT_00025550 != '\0')) {
        DAT_00025550 = '\0';
        DAT_000252d2 = DAT_000252d2 + '\x01';
        DAT_000252d3 = DAT_000252d3 + '\x01';
      }
    }
    uVar4 = uVar4 + 2;
  } while (uVar4 < DAT_00025316);
  if ((DAT_000252d7 != '\0') && (DAT_00025448 = FUN_000158ec(), DAT_00025448 == 0)) {
    uVar2 = FUN_000124d8();
    return uVar2;
  }
  if ((((DAT_000252d6 == '\0') || (DAT_0002544c = FUN_000158ec(), DAT_0002544c != 0)) &&
      ((DAT_00025314 = (ushort)(byte)(DAT_000252d6 + DAT_000252d7) * 5, DAT_00025314 == 0 ||
       (DAT_00025450 = FUN_000158ec(), DAT_00025450 != 0)))) &&
     ((DAT_000252d5 == '\0' || (DAT_00025454 = FUN_000158ec(), DAT_00025454 != 0)))) {
    sVar3 = 0;
    psVar5 = &DAT_00025380;
    DAT_000253a0 = 0;
    DAT_000253a4 = 0;
    DAT_000253a8 = 0;
    DAT_000253ac = 0;
    psVar6 = &DAT_00025388;
    iVar8 = DAT_00024578;
    uVar4 = DAT_00025316;
    do {
      psVar7 = psVar6;
      if ((*(ushort *)(iVar8 + sVar3) & 0x8000) != 0) {
        uVar1 = (*(ushort *)(iVar8 + sVar3) & 0x7fff) >> 2 & 0x1ff;
        if (uVar1 == 4) {
          FUN_00013216();
          iVar8 = extraout_A0;
        }
        else if (uVar1 == 3) {
          FUN_000131c8();
          iVar8 = extraout_A0_00;
        }
        else if (uVar1 == 0xf) {
          FUN_00013236();
          iVar8 = extraout_A0_01;
        }
        else if (uVar1 == 1) {
          *psVar5 = sVar3;
          psVar5 = psVar5 + 1;
        }
        else if (uVar1 == 2) {
          psVar7 = psVar6 + 1;
          *psVar6 = sVar3;
        }
      }
      sVar3 = sVar3 + 2;
    } while ((-1 < (short)(uVar4 - 1)) && (uVar4 = uVar4 - 2, psVar6 = psVar7, uVar4 != 0xffff));
    return in_D0;
  }
                    /* WARNING: Could not recover jumptable at 0x000124d8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  uVar2 = (*_thunk_FUN_0001020e)();
  return uVar2;
}


// ==== FUN_000131c8 @ 000131c8 ====

void FUN_000131c8(void)

{
  short sVar1;
  undefined4 unaff_D2;
  short sVar2;
  short unaff_D7w;
  undefined4 *in_A1;
  short *unaff_A5;
  
  sVar1 = unaff_D7w * 4;
  sVar2 = (short)unaff_D2;
  if (*(short *)((int)&DAT_00025390 + (int)sVar1) == 0) {
    *(short *)((int)&DAT_00025390 + (int)sVar1) = sVar2;
  }
  *(short *)((int)&DAT_00025390 + sVar1 + 2) = sVar2;
  *(short *)(in_A1 + 1) = sVar2 << 2;
  *(short *)(in_A1 + 1) = *(short *)(in_A1 + 1) + -0x2c;
  *(short *)((int)in_A1 + 6) = sVar2 << 2;
  *(short *)((int)in_A1 + 6) = *(short *)((int)in_A1 + 6) + 0x10;
  *in_A1 = unaff_D2;
  *(char *)((int)in_A1 + 9) = (char)unaff_D7w;
  *(undefined1 *)(in_A1 + 2) = 5;
  *unaff_A5 = *unaff_A5 + 5;
  return;
}


// ==== FUN_00013216 @ 00013216 ====

void FUN_00013216(void)

{
  short sVar1;
  undefined4 unaff_D2;
  undefined1 unaff_D7b;
  undefined4 *unaff_A2;
  short *unaff_A5;
  
  sVar1 = (short)unaff_D2 << 2;
  *(short *)(unaff_A2 + 1) = sVar1;
  *(short *)((int)unaff_A2 + 6) = sVar1;
  *unaff_A2 = unaff_D2;
  *(undefined1 *)((int)unaff_A2 + 9) = unaff_D7b;
  *(undefined1 *)(unaff_A2 + 2) = 5;
  *unaff_A5 = *unaff_A5 + 5;
  return;
}


// ==== FUN_00013236 @ 00013236 ====

void FUN_00013236(void)

{
  undefined2 unaff_D2w;
  undefined2 *unaff_D6;
  undefined2 unaff_D7w;
  int unaff_A5;
  
  *unaff_D6 = unaff_D2w;
  unaff_D6[3] = unaff_D7w;
  *(short *)(unaff_A5 + 2) = *(short *)(unaff_A5 + 2) + 1;
  unaff_D6[2] = 0;
  return;
}


// ==== FUN_00013252 @ 00013252 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00013252(void)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 extraout_A0;
  int extraout_A0_00;
  int extraout_A0_01;
  int extraout_A0_02;
  int extraout_A0_03;
  
  DAT_00025444 = 0;
  if (DAT_000252c7 != '\0') {
    DAT_00026e88 = (*_thunk_FUN_00015bc6)();
    if (DAT_00026e88 == 0) {
      DAT_0002550f = 0xff;
      DAT_000252c7 = '\0';
    }
    DAT_000253ea = 0xf8;
    DAT_00026e84 = extraout_A0;
    FUN_0001350e();
  }
  if (DAT_000252ca != '\0') {
    uVar2 = (*_thunk_FUN_00015bc6)();
    DAT_000253cc = 0xd0;
    DAT_00026e94 = extraout_A0_00;
    if (extraout_A0_00 == 0) {
      FUN_000124d8();
      return;
    }
    DAT_00026e98 = uVar2;
    FUN_0001350e();
  }
  if (DAT_000252cb != '\0') {
    uVar2 = (*_thunk_FUN_00015bc6)();
    DAT_00025408 = 0xb8;
    DAT_00026e9c = extraout_A0_01;
    if (extraout_A0_01 == 0) {
      FUN_000124d8();
      return;
    }
    DAT_00026ea0 = uVar2;
    FUN_0001350e();
    iVar1 = *(int *)(extraout_A0_02 + 6);
    *(undefined2 *)(iVar1 + 0x14) = 5;
    *(undefined2 *)(iVar1 + 0x22) = 5;
  }
  if (DAT_000252c8 != '\0') {
    uVar2 = (*_thunk_FUN_00015bc6)();
    DAT_00026e8c = extraout_A0_03;
    if (extraout_A0_03 == 0) {
      FUN_000124d8();
      return;
    }
    DAT_00025426 = 0;
    DAT_00026e90 = uVar2;
    FUN_0001350e();
  }
  return;
}


// ==== FUN_00013368 @ 00013368 ====

void FUN_00013368(void)

{
  if (DAT_00026da8 == 0) {
    DAT_000254ca = FUN_00015b1a();
    DAT_00026da8 = FUN_00015d50();
  }
  if (DAT_00026e04 == 0) {
    DAT_000254ce = FUN_00015b1a();
    DAT_00026e04 = FUN_00015d50();
  }
  if (DAT_00026df8 == 0) {
    DAT_000254da = FUN_00015b1a();
    DAT_00026df8 = FUN_00015d50();
  }
  if (DAT_00026dfc == 0) {
    DAT_000254d2 = FUN_00015b1a();
    DAT_00026dfc = FUN_00015d50();
  }
  if (DAT_00026d92 == 0) {
    DAT_000254d6 = FUN_00015b1a();
    DAT_00026d92 = FUN_00015d50();
  }
  if (DAT_00026d8e == 0) {
    DAT_000254c6 = FUN_00015b1a();
    DAT_00026d8e = FUN_00015d50();
  }
  if (DAT_00026dca == 0) {
    DAT_000254de = FUN_00015b1a();
    DAT_00026dca = FUN_00015d50();
  }
  if (DAT_00026de6 == 0) {
    DAT_000254c2 = FUN_00015b1a();
    DAT_00026de6 = FUN_00015d50();
  }
  FUN_00011f76();
  return;
}


// ==== FUN_0001344e @ 0001344e ====

void FUN_0001344e(void)

{
  if (DAT_00026da8 == 0) {
    DAT_000254ca = FUN_00015b1a();
    DAT_00026da8 = FUN_00015d50();
  }
  return;
}


// ==== FUN_0001346c @ 0001346c ====

void FUN_0001346c(void)

{
  FUN_000124e0();
  FUN_000124e0();
  FUN_000124e0();
  FUN_000124e0();
  FUN_000124e0();
  FUN_000124e0();
  FUN_000124e0();
  FUN_000124e0();
  return;
}


// ==== FUN_000134a4 @ 000134a4 ====

void FUN_000134a4(void)

{
  FUN_000124e0();
  return;
}


// ==== FUN_000134ae @ 000134ae ====

void FUN_000134ae(void)

{
  FUN_00012502();
  return;
}


// ==== FUN_000134bc @ 000134bc ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_000134bc(void)

{
  FUN_000125c6();
  (*_thunk_FUN_000205cc)();
  FUN_00012794();
  FUN_0001283e();
  FUN_000129dc();
  return;
}


// ==== FUN_000134d8 @ 000134d8 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_000134d8(void)

{
  FUN_00012a92();
  FUN_0001295a();
  FUN_000128d6();
  FUN_000127f6();
  (*_thunk_FUN_0002067c)();
  FUN_0001276c();
  FUN_0001660e();
  (*_thunk_FUN_0002090a)(0xffffffff);
  (**(code **)(DAT_00026e76 + -0xd2))();
  FUN_0001259e();
  return;
}


// ==== FUN_0001350e @ 0001350e ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 FUN_0001350e(void)

{
  short sVar1;
  undefined4 in_D0;
  int iVar2;
  short sVar3;
  undefined4 in_D1;
  short *extraout_A0;
  undefined2 *extraout_A1;
  undefined2 *puVar4;
  undefined8 uVar5;
  
  if (DAT_00026c90 != 0) {
    return CONCAT44(in_D0,in_D1);
  }
  iVar2 = FUN_000158ec();
  *(int *)(extraout_A0 + 3) = iVar2;
  if (iVar2 == 0) {
                    /* WARNING: Could not recover jumptable at 0x000124d8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar5 = (*_thunk_FUN_0001020e)();
    return uVar5;
  }
  sVar1 = *extraout_A0;
  sVar3 = extraout_A0[5];
  puVar4 = extraout_A1;
  while (sVar3 = sVar3 + -1, sVar3 != -1) {
    *(undefined2 *)(iVar2 + 4) = *puVar4;
    *(short *)(iVar2 + 4) = sVar1 * 4 + *(short *)(iVar2 + 4);
    iVar2 = iVar2 + 0xe;
    puVar4 = puVar4 + 1;
  }
  return CONCAT44(in_D0,in_D1);
}


// ==== FUN_00013554 @ 00013554 ====

void FUN_00013554(void)

{
  short sVar1;
  undefined2 *puVar2;
  
  sVar1 = 0x4f;
  puVar2 = &DAT_0002524a;
  do {
    *(undefined1 *)puVar2 = 0;
    sVar1 = sVar1 + -1;
    puVar2 = (undefined2 *)((int)puVar2 + 1);
  } while (sVar1 != -1);
  return;
}


// ==== FUN_00013562 @ 00013562 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00013562(void)

{
  DAT_00025434 = 4;
  DAT_0002529c = 0;
  DAT_0002530c = 0;
  _DAT_00025312 = 0;
  DAT_000252ae = 0xff;
  DAT_000252ac = 3;
  DAT_000252a0 = 0x6000;
  DAT_000252a4 = 0x400;
  DAT_000252a8 = 0x55;
  DAT_000252aa = 0xa0;
  (*_thunk_FUN_0001edea)();
  (*_thunk_FUN_0001e608)();
  FUN_000135a8();
  return;
}


// ==== FUN_000135a8 @ 000135a8 ====

void FUN_000135a8(void)

{
  DAT_000252ad = 0;
  DAT_0002517a = 0;
  DAT_000251ae = 0;
  DAT_000251e2 = 0;
  DAT_00025216 = 0;
  DAT_00025126 = 0;
  DAT_00025128 = 0;
  DAT_000254a6 = 0;
  FUN_000135d8();
  return;
}


// ==== FUN_000135ce @ 000135ce ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 FUN_000135ce(void)

{
  undefined4 in_D0;
  short sVar1;
  undefined4 in_D1;
  int iVar2;
  
  DAT_000273a2 = 0x14;
  DAT_000252ac = DAT_000252ac + -1;
  DAT_00024fca = DAT_000252e2;
  DAT_0002535e = 0;
  DAT_00024fdc = 0xffff;
  sVar1 = 0x27;
  iVar2 = DAT_00026ea8;
  do {
    *(undefined2 *)(iVar2 + 0x10) = 0;
    iVar2 = iVar2 + 0x14;
    sVar1 = sVar1 + -1;
  } while (sVar1 != -1);
  if ((DAT_000252ac < '\x01') || (DAT_00025434 < 1)) {
    DAT_000252b2 = 0xff;
    DAT_00025312 = 0xff;
    DAT_000252ac = '\0';
  }
  else {
    DAT_000252af = 3;
    DAT_000252b0 = 0;
    FUN_00013684();
    if (DAT_000273a2 != 0) {
      (*_thunk_FUN_0001524a)();
      (*_thunk_FUN_0002124a)();
      (*_thunk_FUN_000212ce)();
      (*_thunk_FUN_00021010)();
      (*_thunk_FUN_000212d4)();
      FUN_0001030c();
      do {
        (*_thunk_FUN_00022eee)();
        DAT_000273a2 = DAT_000273a2 + -1;
      } while (DAT_000273a2 != 0);
      do {
        (*_thunk_FUN_00022eee)();
      } while (DAT_000273a2 != 0);
    }
  }
  DAT_000273a2 = 0;
  return CONCAT44(in_D0,in_D1);
}


// ==== FUN_000135d8 @ 000135d8 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 FUN_000135d8(void)

{
  undefined4 in_D0;
  short sVar1;
  undefined4 in_D1;
  int iVar2;
  
  DAT_00024fca = DAT_000252e2;
  DAT_0002535e = 0;
  DAT_00024fdc = 0xffff;
  sVar1 = 0x27;
  iVar2 = DAT_00026ea8;
  do {
    *(undefined2 *)(iVar2 + 0x10) = 0;
    iVar2 = iVar2 + 0x14;
    sVar1 = sVar1 + -1;
  } while (sVar1 != -1);
  if ((DAT_000252ac < '\x01') || (DAT_00025434 < 1)) {
    DAT_000252b2 = 0xff;
    DAT_00025312 = 0xff;
    DAT_000252ac = '\0';
  }
  else {
    DAT_000252af = 3;
    DAT_000252b0 = 0;
    FUN_00013684();
    if (DAT_000273a2 != 0) {
      (*_thunk_FUN_0001524a)();
      (*_thunk_FUN_0002124a)();
      (*_thunk_FUN_000212ce)();
      (*_thunk_FUN_00021010)();
      (*_thunk_FUN_000212d4)();
      FUN_0001030c();
      do {
        (*_thunk_FUN_00022eee)();
        DAT_000273a2 = DAT_000273a2 + -1;
      } while (DAT_000273a2 != 0);
      do {
        (*_thunk_FUN_00022eee)();
      } while (DAT_000273a2 != 0);
    }
  }
  DAT_000273a2 = 0;
  return CONCAT44(in_D0,in_D1);
}


// ==== FUN_00013684 @ 00013684 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 FUN_00013684(void)

{
  undefined4 in_D0;
  undefined4 in_D1;
  
  DAT_00026c8e = 0xf;
  (*_thunk_FUN_00013756)();
  DAT_000252f4 = 1;
  DAT_00025366 = 0;
  DAT_00025364 = 0;
  DAT_000252af = 3;
  DAT_000255dc = 0;
  (*_thunk_FUN_0001b9bc)();
  DAT_00025e64 = 0x600;
  DAT_000252e4 = 1;
  DAT_000252e6 = 0x20;
  DAT_000252f0 = 0x97;
  DAT_000252b4 = 0xff;
  DAT_000252b6 = 0x20;
  DAT_000252b7 = 0xff;
  DAT_000252b8 = 1;
  DAT_000252b9 = 5;
  DAT_000252f2 = DAT_00025318;
  DAT_000252ba = 0;
  DAT_000252f6 = 0;
  DAT_000252bc = 0;
  if (DAT_000252bd != -1) {
    DAT_000252bd = (&DAT_00024b49)[DAT_000252f4];
  }
  (*_thunk_FUN_0001edbc)();
  DAT_000252f8 = 2;
  DAT_000252fc = 0xffff;
  DAT_00025300 = 8;
  DAT_00025302 = 1;
  DAT_00025304 = 3;
  DAT_00025306 = 3;
  DAT_00025308 = 1;
  DAT_0002530a = 0x16;
  DAT_000252be = 1;
  DAT_000252bf = 1;
  (*_thunk_FUN_0001b7ec)();
  return CONCAT44(in_D0,in_D1);
}


// ==== FUN_00013756 @ 00013756 ====

void FUN_00013756(void)

{
  short sVar1;
  undefined2 *puVar2;
  
  puVar2 = &DAT_00024bfe;
  sVar1 = 0xe;
  do {
    *(undefined1 *)(puVar2 + 0x10) = 0;
    puVar2 = puVar2 + 0x15;
    sVar1 = sVar1 + -1;
  } while (sVar1 != -1);
  DAT_00025504._0_1_ = 0;
  return;
}


// ==== FUN_00013772 @ 00013772 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00013772(void)

{
  ushort uVar1;
  short sVar2;
  int iVar3;
  ushort *puVar4;
  
  DAT_000273a8 = 0;
  DAT_000273a4 = 0;
  DAT_000273a6 = 10000;
  (*_thunk_FUN_000212ce)();
  (*_thunk_FUN_00021010)();
  DAT_00025318 = DAT_00025318 + 1;
  if (DAT_00025318 == 100) {
    DAT_00025318 = 0;
  }
  uVar1 = DAT_00026dac;
  if (DAT_00024e86 == 1) {
    uVar1 = DAT_00026dac & 0xfff8;
  }
  sVar2 = 0x120;
  if (DAT_00024e86 != 8) {
    sVar2 = 0x900;
  }
  puVar4 = (ushort *)((int)(short)((short)(uVar1 - sVar2) >> 2 & 0xfffe) + (int)DAT_00024578);
  sVar2 = -0x78 - (uVar1 & 7);
  DAT_00025336 = (DAT_00026db0 >> 4) + 0x18;
  iVar3 = DAT_00026ea4;
  if (DAT_00024e86 == 1) {
    iVar3 = DAT_00026ed2;
  }
  do {
    if (DAT_00024578 <= puVar4) goto LAB_00013842;
    puVar4 = puVar4 + 1;
    sVar2 = DAT_00024e86 + sVar2;
  } while (sVar2 < 0x1d0);
  goto LAB_000138ba;
  while( true ) {
    uVar1 = *puVar4 >> 2;
    if (((uVar1 & 0x2000) != 0) && (*(int *)(iVar3 + (short)((uVar1 & 0x1ff) << 2)) != 0)) {
      if ((*puVar4 & 3) == 1) {
        FUN_00014eac();
      }
      (*_thunk_FUN_00020ce2)();
    }
    FUN_00013b1c();
    sVar2 = DAT_00024e86 + sVar2;
    puVar4 = puVar4 + 1;
    if (0x1cf < sVar2) break;
LAB_00013842:
    if (DAT_0002457c < puVar4 + 1) break;
  }
LAB_000138ba:
  FUN_00013abc();
  FUN_0001409c();
  (*_thunk_FUN_000103a6)();
  (*_thunk_FUN_00010da6)();
  FUN_00013d78();
  FUN_00013de8();
  FUN_00014c3e();
  FUN_00013a18();
  FUN_0001391e();
  FUN_00013e6c();
  FUN_000140e8();
  (*_thunk_FUN_000212d4)();
  if (DAT_000273a4 == 0) {
    _DAT_000270b4 = 0;
  }
  else {
    uVar1 = DAT_000273a6 >> 3;
    if (0x40 < uVar1) {
      uVar1 = 0x40;
    }
    DAT_000270b6 = 0x40 - uVar1;
    _DAT_000270b4 = CONCAT11(0xff,DAT_000270b4_1);
  }
  DAT_000273a8 = 0;
  return;
}


// ==== FUN_0001391e @ 0001391e ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0001391e(void)

{
  short sVar1;
  short *psVar2;
  undefined **ppuVar3;
  short sVar4;
  short sVar5;
  short *psVar6;
  short *unaff_A3;
  undefined **ppuVar7;
  
  sVar1 = DAT_000268ae;
  sVar5 = 4;
  psVar2 = (short *)&DAT_00024e88;
  ppuVar3 = &PTR_DAT_000254aa;
  do {
    ppuVar7 = ppuVar3;
    psVar6 = psVar2;
    sVar4 = 0;
    if (*(short *)(*ppuVar7 + 4) != 0) {
      if (DAT_00024e84 == 0) {
        if ((sVar5 < 1) &&
           (sVar4 = DAT_00026da6 + *(short *)(*ppuVar7 + 0x1a) + 0x8e, sVar4 < DAT_000268ae)) {
          DAT_000268ae = sVar4;
        }
      }
      else {
        DAT_000268ae = 0x96;
      }
      unaff_A3 = psVar6 + 4;
      sVar4 = *psVar6;
    }
    while (sVar4 = sVar4 + -1, sVar4 != -1) {
      if (*unaff_A3 != 0) {
        (*_thunk_FUN_00015174)();
      }
      unaff_A3 = unaff_A3 + 4;
    }
    sVar5 = sVar5 + -1;
    psVar2 = psVar6 + 0x20;
    ppuVar3 = ppuVar7 + 1;
  } while (sVar5 != -1);
  if ((((0 < *psVar6) && (DAT_00024e84 == 0)) &&
      (sVar5 = (*(short *)*ppuVar7 * 4 + 0x199) - DAT_00024e80, -0x81 < sVar5)) && (sVar5 < 0x1c1))
  {
    DAT_000268ae = sVar1;
    (*_thunk_FUN_00020ce2)();
  }
  DAT_000268ae = sVar1;
  return;
}


// ==== FUN_00013a18 @ 00013a18 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined2 FUN_00013a18(void)

{
  undefined2 uVar1;
  short sVar2;
  short sVar3;
  undefined2 *puVar4;
  
  sVar3 = 3;
  puVar4 = &DAT_0002524a;
  do {
    sVar2 = puVar4[8];
    uVar1 = 0;
    if (puVar4[1] != 0) {
      while (sVar2 = sVar2 + -1, sVar2 != -1) {
        (*_thunk_FUN_00020ce2)();
      }
      uVar1 = 0;
      if (puVar4[9] != 0) {
        uVar1 = (*_thunk_FUN_00020ce2)();
      }
    }
    puVar4 = puVar4 + 10;
    sVar3 = sVar3 + -1;
  } while (sVar3 != -1);
  return uVar1;
}


// ==== FUN_00013abc @ 00013abc ====

/* WARNING: Removing unreachable block (ram,0x00013ae2) */
/* WARNING: Removing unreachable block (ram,0x00013afe) */
/* WARNING: Removing unreachable block (ram,0x00013b02) */
/* WARNING: Removing unreachable block (ram,0x00013b12) */
/* WARNING: Removing unreachable block (ram,0x00013b0a) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00013abc(void)

{
  return;
}


// ==== FUN_00013b1c @ 00013b1c ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 FUN_00013b1c(void)

{
  short sVar1;
  undefined2 uVar2;
  undefined4 in_D0;
  short sVar4;
  uint uVar3;
  undefined4 in_D1;
  ushort unaff_D3w;
  ushort uVar5;
  short unaff_D4w;
  ushort *puVar6;
  int *piVar7;
  
  uVar5 = unaff_D3w & 0xdfff;
  uVar2 = (undefined2)((uint)in_D0 >> 0x10);
  if (((unaff_D3w & 0x2000) != 0) && (uVar5 == 5)) {
    if (DAT_00024e86 == 1) {
      uVar5 = (unaff_D4w * 8 + (DAT_00026dac & 0xfff8)) - 0x538;
    }
    else {
      uVar5 = unaff_D4w + (DAT_00026dac - 0xa0);
      uVar2 = 0;
    }
    uVar3 = CONCAT22(uVar2,uVar5 >> 2) & 0xfffffffe;
    for (piVar7 = DAT_00025448; CONCAT22((short)(uVar3 >> 0x10),(short)uVar3 + -2) != *piVar7;
        piVar7 = piVar7 + 4) {
    }
    if (((*(short *)(piVar7 + 3) != 0) &&
        (sVar4 = *(short *)((int)piVar7 + 0xe), sVar1 = sVar4 + -1,
        *(short *)((int)piVar7 + 0xe) = sVar1, sVar1 == 0 || sVar4 < 1)) &&
       (sVar4 = *(short *)(piVar7 + 3) + -1, *(short *)(piVar7 + 3) = sVar4, sVar4 != 0)) {
      *(short *)((int)piVar7 + 0xe) = 0x32 - *(short *)(piVar7 + 3);
      (*_thunk_FUN_00015460)();
    }
    return CONCAT44(in_D0,in_D1);
  }
  if (DAT_00024e86 == 1) {
    return CONCAT44(in_D0,in_D1);
  }
  if (uVar5 == 0x22) {
    if (((DAT_00025318 & 1) != 0) &&
       (DAT_000252dd = DAT_000252dd - 1, (short)((ushort)DAT_000252dd << 8) < 0)) {
      DAT_000252dd = 3;
    }
    (*_thunk_FUN_00020ce2)();
    return CONCAT44(in_D0,in_D1);
  }
  if (uVar5 == 0x9f) {
    if (DAT_000273a8 == '\0') {
      DAT_000273a8 = -1;
      if (DAT_000252af != DAT_000255dc) {
        DAT_000255dc = DAT_000252af;
        DAT_000255a4 = *(short *)(&DAT_000255ae + (short)((ushort)DAT_000252af << 2));
        DAT_000255a8 = *(short *)(&DAT_000255c6 + (short)((ushort)DAT_000252af << 2));
      }
      sVar4 = 1;
      if (DAT_000255a6 == DAT_000255a4) {
        if ((DAT_000255dc != 2) || (DAT_000255a6 == DAT_000255aa)) {
          DAT_000255a4 = *(short *)(&DAT_000255ac + (short)((ushort)DAT_000255dc << 2));
          if (DAT_000255a4 == DAT_000255a6) {
            DAT_000255a4 = *(short *)(&DAT_000255ae + (short)((ushort)DAT_000255dc << 2));
          }
        }
      }
      else {
        if (DAT_000255a4 <= DAT_000255a6) {
          sVar4 = -1;
        }
        DAT_000255a6 = sVar4 + DAT_000255a6;
      }
      sVar4 = 1;
      if (DAT_000255aa == DAT_000255a8) {
        DAT_000255a8 = *(short *)(&DAT_000255c4 + (short)((ushort)DAT_000255dc << 2));
        if (DAT_000255a8 == DAT_000255aa) {
          DAT_000255a8 = *(short *)(&DAT_000255c6 + (short)((ushort)DAT_000255dc << 2));
        }
      }
      else {
        if (DAT_000255a8 <= DAT_000255aa) {
          sVar4 = -1;
        }
        DAT_000255aa = sVar4 + DAT_000255aa;
      }
    }
    (*_thunk_FUN_00020ce2)();
    (*_thunk_FUN_00020ce2)();
    return CONCAT44(in_D0,in_D1);
  }
  if (uVar5 == 0x113) {
    sVar4 = 0;
    puVar6 = &DAT_00025388;
    while (*puVar6 <= DAT_00026dac >> 2) {
      sVar4 = sVar4 + 1;
      puVar6 = puVar6 + 1;
    }
    if (((*(short *)((int)&DAT_000253a0 + (int)(short)(sVar4 * 4)) != 0) ||
        (*(short *)((int)&DAT_000253a0 + (short)(sVar4 * 4) + 2) != 0)) &&
       (DAT_000252d0 = DAT_000252d0 - 1, (short)((ushort)DAT_000252d0 << 8) < 0)) {
      DAT_000252d0 = 2;
    }
    (*_thunk_FUN_00020ce2)();
    return CONCAT44(in_D0,in_D1);
  }
  return CONCAT44(in_D0,in_D1);
}


// ==== FUN_00013d78 @ 00013d78 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00013d78(void)

{
  short sVar1;
  short sVar2;
  ushort uVar3;
  int *piVar4;
  bool bVar5;
  
  uVar3 = (ushort)DAT_000252d6;
  piVar4 = DAT_0002544c;
  while (uVar3 = uVar3 - 1, uVar3 != 0xffff) {
    if (*(char *)(piVar4 + 2) == '\0') {
      sVar1 = *(short *)((int)piVar4 + 0xe);
      sVar2 = sVar1 + -1;
      *(short *)((int)piVar4 + 0xe) = sVar2;
      if (sVar2 == 0 || sVar1 < 1) {
        *(undefined2 *)((int)piVar4 + 0xe) = 200;
        FUN_00014fee();
      }
    }
    else if ((*(short *)(piVar4 + 3) == 0) ||
            (sVar1 = *(short *)(piVar4 + 3) + -1, *(short *)(piVar4 + 3) = sVar1, sVar1 == 0)) {
      bVar5 = *piVar4 < 0;
      FUN_00014d50();
      if (!bVar5) {
        (*_thunk_FUN_00015174)();
        FUN_00014f5c();
      }
    }
    piVar4 = piVar4 + 4;
  }
  return;
}


// ==== FUN_00013de8 @ 00013de8 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00013de8(void)

{
  short sVar1;
  short sVar2;
  int in_D0;
  int iVar3;
  ushort uVar4;
  short *psVar5;
  bool bVar6;
  
  uVar4 = (ushort)DAT_000252d5;
  psVar5 = DAT_00025454;
  while (uVar4 = uVar4 - 1, uVar4 != 0xffff) {
    if (*(char *)(psVar5 + 4) == '\0') {
      iVar3 = CONCAT22((short)((uint)in_D0 >> 0x10),*psVar5 * 4);
      bVar6 = in_D0 < 0;
      FUN_00014d50();
      if (!bVar6) {
        (*_thunk_FUN_00015174)();
        iVar3 = FUN_00014f5c();
      }
    }
    else {
      iVar3 = in_D0;
      if (((psVar5[5] != 0) &&
          (sVar1 = psVar5[6], sVar2 = sVar1 + -1, psVar5[6] = sVar2, sVar2 == 0 || sVar1 < 1)) &&
         (sVar1 = psVar5[5] + -1, psVar5[5] = sVar1, sVar1 != 0)) {
        psVar5[6] = 0x32 - psVar5[5];
        iVar3 = (*_thunk_FUN_00015460)();
      }
    }
    psVar5 = psVar5 + 7;
    in_D0 = iVar3;
  }
  return;
}


// ==== FUN_00013e6c @ 00013e6c ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00013e6c(void)

{
  if (DAT_00024e86 != 8) {
    (*_thunk_FUN_00021010)();
    return;
  }
  (*_thunk_FUN_00020ce2)();
  (*_thunk_FUN_00020ce2)();
  (*_thunk_FUN_00020ce2)();
  (*_thunk_FUN_00020ce2)();
  (*_thunk_FUN_00020ce2)();
  return;
}


// ==== FUN_00013eee @ 00013eee ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00013eee(void)

{
  short *psVar1;
  byte bVar2;
  short sVar3;
  ushort uVar4;
  short sVar5;
  char cVar6;
  short extraout_D1w;
  short sVar7;
  uint uVar8;
  int extraout_A0;
  short *psVar9;
  bool bVar10;
  
  (*_thunk_FUN_000212ce)();
  psVar9 = DAT_00025450;
  sVar7 = DAT_00025314;
  do {
    sVar7 = sVar7 + -1;
    if (sVar7 == -1) {
LAB_00014092:
      (*_thunk_FUN_000212d4)();
      return;
    }
    if (psVar9[3] != 0) {
      if (psVar9[3] != 3) {
        if (psVar9[3] == 2) {
          bVar2 = *(byte *)(psVar9 + 2) - 1;
          *(byte *)(psVar9 + 2) = bVar2;
          if ((short)((ushort)bVar2 << 8) < 0) {
            *(undefined1 *)(psVar9 + 2) = 2;
            *(char *)((int)psVar9 + 3) = *(char *)((int)psVar9 + 3) + '\x01';
            if (7 < *(byte *)((int)psVar9 + 3)) {
              psVar9[3] = 3;
              DAT_0002529c = DAT_0002529c + 0x19;
              DAT_00026c8c = DAT_00026c8c + 1;
              sVar3 = (ushort)*(byte *)((int)psVar9 + 5) * 4;
              psVar1 = (short *)((int)&DAT_000253a0 + (int)sVar3);
              sVar5 = *psVar1 + -1;
              *psVar1 = sVar5;
              if ((sVar5 == 0) && (*(short *)((int)&DAT_000253a0 + sVar3 + 2) == 0)) {
                uVar4 = FUN_00015ae8();
                uVar8 = (uint)uVar4;
                DAT_0002529c = uVar8 + DAT_0002529c;
                bVar10 = SBORROW1(DAT_000252d3,'\x01');
                DAT_000252d3 = DAT_000252d3 - 1;
                if ((DAT_000252d3 == 0 || bVar10 != (short)((ushort)DAT_000252d3 << 8) < 0) &&
                   (DAT_000252c1 == '\0')) {
                  (*_thunk_FUN_00015078)();
                  (*_thunk_FUN_00015694)(uVar8);
                  goto LAB_00014092;
                }
                (*_thunk_FUN_00015624)(uVar8);
              }
            }
          }
        }
        else {
          *(char *)((int)psVar9 + 3) = *(char *)((int)psVar9 + 3) + '\x01';
          if (4 < *(byte *)((int)psVar9 + 3)) {
            *(undefined1 *)((int)psVar9 + 3) = 0;
          }
          sVar5 = 3;
          if (*(char *)(psVar9 + 1) < '\0') {
            sVar5 = -3;
          }
          cVar6 = (*_thunk_FUN_000150c8)();
          if (cVar6 == '\0') {
            sVar5 = -sVar5;
            *(char *)(psVar9 + 1) = -*(char *)(psVar9 + 1);
          }
          *psVar9 = sVar5 + *psVar9;
        }
      }
      if (((((DAT_00024e86 == 8) || (psVar9[3] != 3)) && ((*_thunk_FUN_00015174)(), psVar9[3] == 1))
          && (((*_thunk_FUN_000150c8)(), extraout_D1w == 3 && (-1 < *psVar9)))) &&
         (cVar6 = FUN_00014b54(), -1 < cVar6)) {
        if ((*(short *)(extraout_A0 + 0xc) == 0) && (*(char *)(extraout_A0 + 8) == '\0')) {
          *(undefined2 *)(extraout_A0 + 0xc) = 0x168;
        }
        *(char *)(extraout_A0 + 8) = *(char *)(extraout_A0 + 8) + '\x01';
        psVar9[3] = 0;
      }
    }
    psVar9 = psVar9 + 4;
  } while( true );
}


// ==== FUN_0001409c @ 0001409c ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0001409c(void)

{
  if (DAT_00024e86 == 8) {
    if (DAT_000252e4 != 1) {
      (*_thunk_FUN_0001526e)();
      (*_thunk_FUN_00015174)();
    }
    (*_thunk_FUN_0001524a)();
  }
  return;
}


// ==== FUN_000140e8 @ 000140e8 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 FUN_000140e8(void)

{
  undefined4 in_D0;
  undefined4 in_D1;
  ushort uVar1;
  
  uVar1 = (ushort)DAT_000252d4;
  while (uVar1 = uVar1 - 1, uVar1 != 0xffff) {
    (*_thunk_FUN_00015174)();
    (*_thunk_FUN_00015174)();
    (*_thunk_FUN_00021010)();
  }
  return CONCAT44(in_D0,in_D1);
}


// ==== FUN_0001417e @ 0001417e ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 FUN_0001417e(void)

{
  undefined4 in_D0;
  undefined4 in_D1;
  
  (*_thunk_FUN_000212ce)();
  (*_thunk_FUN_0001525c)();
  DAT_00025332 = DAT_00025336;
  FUN_00014564();
  if (DAT_00024e86 != 1) {
    FUN_00014206();
    FUN_000141b4();
  }
  (*_thunk_FUN_000212d4)();
  return CONCAT44(in_D0,in_D1);
}


// ==== FUN_000141b4 @ 000141b4 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_000141b4(void)

{
  if (DAT_00026db0 < 0x51) {
    DAT_0002530a = ((ushort)(0x51U - DAT_00026db0) >> 2) + 0xd;
  }
  else {
    DAT_0002530a = 0xd;
  }
  (*_thunk_FUN_00020ce2)();
  return;
}


// ==== FUN_00014206 @ 00014206 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 FUN_00014206(void)

{
  ushort uVar1;
  short sVar2;
  int iVar3;
  undefined4 in_D0;
  short sVar4;
  undefined4 in_D1;
  ushort extraout_D1w;
  ushort uVar5;
  short sVar6;
  short sVar7;
  short sVar8;
  short sVar9;
  short sVar10;
  int extraout_A0;
  short *psVar11;
  short *psVar12;
  
  iVar3 = DAT_00024578;
  DAT_000273aa = 4;
  if ((((-1 < (short)DAT_00026dac) && (DAT_00026dac < DAT_00024580)) &&
      ((*(ushort *)(DAT_00024578 + (short)((DAT_00026dac >> 3) * 2)) & 3) == 1)) &&
     ((FUN_00014a52(), *(short *)(extraout_A0 + 0x12) == 0 ||
      (*(short *)(extraout_A0 + 0x12) == 6000)))) {
    DAT_000273aa = extraout_D1w;
  }
  psVar12 = &DAT_00024606;
  sVar10 = 10;
  do {
    sVar4 = *psVar12;
    psVar12 = psVar12 + -1;
    DAT_00025328 = 0xffff;
    DAT_0002532a = 0xffff;
    sVar7 = sVar4 - *psVar12;
    if (DAT_00024fdc < 0) {
      sVar4 = -sVar4;
    }
    sVar2 = DAT_00024fdc * 2;
    sVar9 = (((short)DAT_00026dac >> 3) + sVar4) * 2;
    sVar4 = sVar7 * 2;
    if (-1 < sVar2) {
      sVar4 = sVar7 * -2;
    }
    sVar4 = sVar9 + sVar4;
    sVar6 = sVar9;
    if (sVar9 < sVar4) {
      sVar6 = sVar4;
      sVar4 = sVar9;
    }
    sVar8 = 3;
    psVar11 = &DAT_0002517a;
    do {
      if (((*psVar11 != 0) && (sVar4 <= psVar11[0x17])) && (psVar11[0x17] <= sVar6)) {
        (*_thunk_FUN_00020ce2)();
      }
      psVar11 = psVar11 + 0x1a;
      sVar8 = sVar8 + -1;
    } while (sVar8 != -1);
    sVar4 = 0;
    do {
      if ((-1 < sVar9) && ((ushort *)(iVar3 + sVar9) <= DAT_0002457c)) {
        uVar5 = *(ushort *)(iVar3 + sVar9);
        uVar1 = uVar5 & 3;
        uVar5 = uVar5 & 0x7fc;
        DAT_000255dd = (char)uVar1;
        if (uVar1 == DAT_000273aa) {
          uVar5 = 0;
        }
        uVar5 = uVar5 >> 2;
        uVar1 = DAT_0002532a;
        if (((uVar5 != 0) &&
            (((uVar5 < 6 || (uVar1 = uVar5, 8 < uVar5)) &&
             (uVar1 = DAT_0002532a, DAT_00025328 != 0x22)))) && (DAT_00025328 != 0xf6)) {
          DAT_00025328 = uVar5;
        }
        DAT_0002532a = uVar1;
        if (DAT_000255dd == '\x02') {
          sVar4 = -1;
        }
      }
      sVar9 = sVar2 + sVar9;
      sVar7 = sVar7 + -1;
    } while (sVar7 != -1);
    if (sVar4 != 0) {
      (*_thunk_FUN_00021010)();
    }
    if ((-1 < (short)DAT_0002532a) && (sVar4 = FUN_000145a6(), -1 < sVar4)) {
      (*_thunk_FUN_00020ce2)();
    }
    if ((-1 < (short)DAT_00025328) && (sVar4 = FUN_000145a6(), -1 < sVar4)) {
      (*_thunk_FUN_00020ce2)();
    }
    DAT_00025332 = DAT_00025332 + 1;
    sVar10 = sVar10 + -1;
  } while (sVar10 != -1);
  if (DAT_0002764c == '\0') {
    FUN_00014430();
    DAT_0002764c = '\0';
  }
  return CONCAT44(in_D0,in_D1);
}


// ==== FUN_00014430 @ 00014430 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 FUN_00014430(void)

{
  short sVar1;
  undefined4 in_D0;
  short sVar2;
  undefined4 in_D1;
  short sVar3;
  
  DAT_0002764e = DAT_000268ac;
  if (((-1 < (short)DAT_00026dac) && (DAT_00026dac < DAT_00024580)) &&
     (sVar1 = (DAT_00026dac >> 3) * 2, (*(ushort *)(DAT_00024578 + sVar1) & 3) == 1)) {
    sVar3 = 0;
    DAT_00025334 = 0x49;
    sVar2 = 2;
    if (-1 < DAT_00024fdc) {
      DAT_00025334 = 0x41;
      sVar2 = -2;
    }
    while ((*(ushort *)(sVar1 + DAT_00024578 + (int)sVar3) >> 2 & 0x1ff) != 0) {
      sVar3 = sVar2 + sVar3;
    }
    sVar3 = sVar3 >> 1;
    if (sVar3 < 0) {
      sVar3 = -sVar3;
    }
    DAT_000268ac = DAT_00025336 +
                   (ushort)(byte)(&DAT_00024685)[(short)(ushort)(byte)(&DAT_0002461f)[sVar3]];
    (*_thunk_FUN_00020ce2)();
    (*_thunk_FUN_00020ce2)();
    DAT_000268ac = DAT_0002764e;
    (*_thunk_FUN_00020ce2)();
  }
  return CONCAT44(in_D0,in_D1);
}


// ==== FUN_00014564 @ 00014564 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 FUN_00014564(void)

{
  undefined4 in_D0;
  undefined4 in_D1;
  
  (*_thunk_FUN_0002124a)();
  (*_thunk_FUN_00021010)();
  (*_thunk_FUN_00021010)();
  return CONCAT44(in_D0,in_D1);
}


// ==== FUN_000145a6 @ 000145a6 ====

undefined8 FUN_000145a6(void)

{
  undefined4 in_D0;
  short sVar2;
  undefined4 uVar1;
  undefined4 in_D1;
  short sVar3;
  short extraout_D1w;
  short unaff_D7w;
  int extraout_A0;
  
  sVar2 = (short)in_D0;
  if ((5 < sVar2) && (sVar2 < 9)) {
    sVar3 = 0xe;
LAB_000146ae:
    return CONCAT44(CONCAT22((short)((uint)in_D0 >> 0x10),
                             ((ushort)(byte)(&DAT_00024608)[unaff_D7w] + sVar3) * 4),in_D1);
  }
  if ((sVar2 == 4) || (sVar2 == 5)) {
    sVar3 = 0x1b;
    if (sVar2 != 4) {
      sVar3 = 0x22;
    }
    goto LAB_000146ae;
  }
  if (sVar2 == 3) {
    sVar3 = 0x14;
    goto LAB_000146ae;
  }
  if ((char)in_D1 != '\x01') {
    if ((sVar2 < 0xf) || (0x1e < sVar2)) {
      return CONCAT44(0xffffffff,in_D1);
    }
    if (sVar2 == 0xf) {
      sVar3 = 0x29;
    }
    else {
      sVar3 = 0x30;
    }
    goto LAB_000146ae;
  }
  sVar3 = 10;
  if (-1 < DAT_00024fdc) {
    sVar3 = 0;
  }
  if ((sVar2 == 0x22) || (sVar2 == 0xf6)) {
    sVar3 = sVar3 + 0x4d;
  }
  else {
    uVar1 = FUN_00014a52();
    if ((short)uVar1 < 0) goto LAB_00014678;
    sVar3 = *(short *)(extraout_A0 + 0x1c);
    in_D0 = CONCAT22((short)((uint)uVar1 >> 0x10),sVar3);
    if (sVar3 == 0) {
      DAT_0002764c = 0;
      sVar3 = extraout_D1w + 0x3c;
    }
    else {
      sVar3 = sVar3 + extraout_D1w;
      DAT_0002764c = 0xff;
    }
  }
  uVar1 = CONCAT22((short)((uint)in_D0 >> 0x10),
                   ((ushort)(byte)(&DAT_00024614)[unaff_D7w] + sVar3) * 4);
LAB_00014678:
  return CONCAT44(uVar1,in_D1);
}


// ==== FUN_000146c6 @ 000146c6 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 FUN_000146c6(int param_1)

{
  short *psVar1;
  ushort uVar2;
  short sVar3;
  short sVar5;
  char cVar7;
  int iVar4;
  ushort uVar6;
  undefined4 in_D1;
  ushort extraout_D1w;
  short sVar8;
  uint uVar9;
  int extraout_A0;
  short extraout_A0w;
  int extraout_A0_00;
  short *extraout_A0_01;
  short extraout_A0w_00;
  int extraout_A0_02;
  short extraout_A1w;
  short extraout_A1w_00;
  short unaff_A2w;
  short unaff_A3w;
  bool bVar10;
  
  param_1 = param_1 - DAT_00024578;
  uVar6 = (ushort)param_1;
  sVar5 = uVar6 * 4;
  DAT_00027672 = 0;
  DAT_00027650 = sVar5;
  cVar7 = (*_thunk_FUN_000150c8)();
  if ((cVar7 == '\0') || (uVar2 = extraout_D1w & 0x1fff, cVar7 == '\x01')) {
    iVar4 = FUN_00014a4e();
    if ((-1 < iVar4) && (DAT_00027672 != 1)) {
      if ((DAT_00027672 == 2) && (DAT_00025366 = 5, cRam0002766e == '\n')) {
        DAT_00025368 = 0xf00;
        if ((0 < *(short *)(extraout_A0_02 + 0xc)) &&
           (sVar8 = *(short *)(extraout_A0_02 + 0xc) + -1, *(short *)(extraout_A0_02 + 0xc) = sVar8,
           sVar8 == 0)) {
          *(undefined2 *)(extraout_A0_02 + 0x18) = 0x14;
        }
      }
      else {
        DAT_00025366 = 5;
        DAT_00025368 = 0xfff;
        iVar4 = *(int *)(extraout_A0_02 + 6);
        if (iVar4 != 0) {
          sVar8 = *(short *)(extraout_A0_02 + 10);
          while (sVar8 = sVar8 + -1, sVar8 != -1) {
            if (*(short *)(iVar4 + 8) == 0) {
              uVar6 = sVar5 - *(short *)(iVar4 + 4);
              if ((int)((uint)uVar6 << 0x10) < 0) {
                uVar6 = -uVar6;
              }
              if ((short)uVar6 < 0x10) {
                *(undefined2 *)(iVar4 + 8) = 0xffff;
                *(undefined2 *)(iVar4 + 10) = 0x32;
                *(undefined2 *)(iVar4 + 0xc) = 1;
                DAT_0002529c = DAT_0002529c + 200;
                DAT_00025368 = 0xf00;
                break;
              }
            }
            iVar4 = iVar4 + 0xe;
          }
        }
      }
    }
  }
  else {
    if (DAT_00027672 == 0) {
      DAT_00025366 = 5;
      DAT_00025368 = 0xfff;
    }
    if (uVar2 != 0x113) {
      if (uVar2 == 3) {
        cVar7 = FUN_00014b54();
        if (-1 < cVar7) {
          if (DAT_00027672 == 0) {
            DAT_00025368 = 0xf00;
          }
          if (*(char *)(extraout_A0 + 8) != '\0') {
            *(undefined2 *)(extraout_A0 + 0xe) = 200;
            DAT_0002529c = DAT_0002529c + 200;
            FUN_00014b40();
          }
        }
      }
      else if (uVar2 == 4) {
        FUN_00014ae4();
        iVar4 = DAT_00024578;
        uVar6 = *(ushort *)(DAT_00024578 + extraout_A0w);
        *(undefined2 *)(DAT_00024578 + extraout_A0w) = 0x16;
        *(ushort *)(iVar4 + extraout_A0w) = uVar6 & 0x8000 | *(ushort *)(iVar4 + extraout_A0w);
        uVar6 = *(ushort *)(iVar4 + extraout_A1w);
        *(undefined2 *)(iVar4 + extraout_A1w) = 0x16;
        *(ushort *)(iVar4 + extraout_A1w) = uVar6 & 0x8000 | *(ushort *)(iVar4 + extraout_A1w);
        uVar6 = *(ushort *)(iVar4 + unaff_A2w);
        *(undefined2 *)(iVar4 + unaff_A2w) = 0x16;
        *(ushort *)(iVar4 + unaff_A2w) = uVar6 & 0x8000 | *(ushort *)(iVar4 + unaff_A2w);
        uVar6 = *(ushort *)(iVar4 + unaff_A3w);
        *(undefined2 *)(iVar4 + unaff_A3w) = 0x16;
        *(ushort *)(iVar4 + unaff_A3w) = uVar6 & 0x8000 | *(ushort *)(iVar4 + unaff_A3w);
        iVar4 = FUN_00014b54();
        if (-1 < iVar4) {
          if (DAT_00027672 == 0) {
            DAT_00025368 = 0xf00;
          }
          *(undefined2 *)(extraout_A0_00 + 0xc) = 0x32;
          *(undefined2 *)(extraout_A0_00 + 0xe) = 1;
          DAT_0002529c = DAT_0002529c + 0x96;
          FUN_00014b40();
        }
      }
      else if ((((0xe < uVar2) && (uVar2 < 0x1e)) && (DAT_00027672 == 0)) &&
              (cVar7 = FUN_00014b54(), -1 < cVar7)) {
        DAT_00025368 = 0xf00;
        sVar8 = *extraout_A0_01;
        FUN_00014ae4();
        iVar4 = DAT_00024578;
        sVar8 = (1 << (4U - (((short)((uVar6 & 0x3fff) - sVar8) >> 1) + 3) & 0x3f) | uVar2 - 0xf) +
                0xf;
        *(ushort *)(DAT_00024578 + extraout_A0w_00) =
             *(ushort *)(DAT_00024578 + extraout_A0w_00) & 0x8000 | sVar8 * 4 | 2U;
        *(ushort *)(iVar4 + extraout_A1w_00) =
             *(ushort *)(iVar4 + extraout_A1w_00) & 0x8000 | sVar8 * 4 | 2U;
        *(ushort *)(iVar4 + unaff_A2w) = *(ushort *)(iVar4 + unaff_A2w) & 0x8000 | sVar8 * 4 | 2U;
        *(ushort *)(iVar4 + unaff_A3w) = *(ushort *)(iVar4 + unaff_A3w) & 0x8000 | sVar8 * 4 | 2U;
        if (-1 < extraout_A0_01[4]) {
          sVar8 = extraout_A0_01[3];
          extraout_A0_01[4] = -1;
          extraout_A0_01[5] = 0x32;
          extraout_A0_01[6] = 1;
          DAT_0002529c = DAT_0002529c + 200;
          psVar1 = (short *)((int)&DAT_000253a0 + (short)(sVar8 * 4) + 2);
          sVar3 = *psVar1 + -1;
          *psVar1 = sVar3;
          if ((sVar3 == 0) && (*(short *)((int)&DAT_000253a0 + (int)(short)(sVar8 * 4)) == 0)) {
            uVar6 = FUN_00015ae8();
            uVar9 = (uint)uVar6;
            DAT_0002529c = uVar9 + DAT_0002529c;
            bVar10 = SBORROW1(DAT_000252d3,'\x01');
            DAT_000252d3 = DAT_000252d3 - 1;
            if ((DAT_000252d3 == 0 || bVar10 != (int)((uint)DAT_000252d3 << 0x18) < 0) &&
               (DAT_000252c1 == '\0')) {
              (*_thunk_FUN_00015078)();
              (*_thunk_FUN_00015694)(uVar9);
            }
            else {
              (*_thunk_FUN_00015624)(uVar9);
            }
          }
        }
      }
    }
  }
  return CONCAT44(CONCAT22((short)((uint)param_1 >> 0x10),sVar5),in_D1);
}


// ==== FUN_000146dc @ 000146dc ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 FUN_000146dc(void)

{
  short *psVar1;
  short sVar2;
  undefined4 in_D0;
  char cVar5;
  int iVar3;
  ushort uVar4;
  undefined4 in_D1;
  ushort extraout_D1w;
  short sVar6;
  ushort uVar7;
  uint uVar8;
  ushort *in_A0;
  int extraout_A0;
  short extraout_A0w;
  int extraout_A0_00;
  short *extraout_A0_01;
  short extraout_A0w_00;
  int extraout_A0_02;
  short extraout_A1w;
  short extraout_A1w_00;
  short unaff_A2w;
  short unaff_A3w;
  bool bVar9;
  
  uVar4 = *in_A0;
  cVar5 = (*_thunk_FUN_000150c8)();
  if ((cVar5 == '\0') || (uVar7 = extraout_D1w & 0x1fff, cVar5 == '\x01')) {
    iVar3 = FUN_00014a4e();
    if ((-1 < iVar3) && (in_A0[0x11] != 1)) {
      if ((in_A0[0x11] == 2) && (DAT_00025366 = 5, *(char *)(in_A0 + 0xf) == '\n')) {
        DAT_00025368 = 0xf00;
        if ((0 < *(short *)(extraout_A0_02 + 0xc)) &&
           (sVar6 = *(short *)(extraout_A0_02 + 0xc) + -1, *(short *)(extraout_A0_02 + 0xc) = sVar6,
           sVar6 == 0)) {
          *(undefined2 *)(extraout_A0_02 + 0x18) = 0x14;
        }
      }
      else {
        DAT_00025366 = 5;
        DAT_00025368 = 0xfff;
        iVar3 = *(int *)(extraout_A0_02 + 6);
        if (iVar3 != 0) {
          sVar6 = *(short *)(extraout_A0_02 + 10);
          while (sVar6 = sVar6 + -1, sVar6 != -1) {
            if (*(short *)(iVar3 + 8) == 0) {
              uVar7 = uVar4 - *(short *)(iVar3 + 4);
              if ((int)((uint)uVar7 << 0x10) < 0) {
                uVar7 = -uVar7;
              }
              if ((short)uVar7 < 0x10) {
                *(undefined2 *)(iVar3 + 8) = 0xffff;
                *(undefined2 *)(iVar3 + 10) = 0x32;
                *(undefined2 *)(iVar3 + 0xc) = 1;
                DAT_0002529c = DAT_0002529c + 200;
                DAT_00025368 = 0xf00;
                break;
              }
            }
            iVar3 = iVar3 + 0xe;
          }
        }
      }
    }
  }
  else {
    if (in_A0[0x11] == 0) {
      DAT_00025366 = 5;
      DAT_00025368 = 0xfff;
    }
    if (uVar7 != 0x113) {
      if (uVar7 == 3) {
        cVar5 = FUN_00014b54();
        if (-1 < cVar5) {
          if (in_A0[0x11] == 0) {
            DAT_00025368 = 0xf00;
          }
          if (*(char *)(extraout_A0 + 8) != '\0') {
            *(undefined2 *)(extraout_A0 + 0xe) = 200;
            DAT_0002529c = DAT_0002529c + 200;
            FUN_00014b40();
          }
        }
      }
      else if (uVar7 == 4) {
        FUN_00014ae4();
        iVar3 = DAT_00024578;
        uVar4 = *(ushort *)(DAT_00024578 + extraout_A0w);
        *(undefined2 *)(DAT_00024578 + extraout_A0w) = 0x16;
        *(ushort *)(iVar3 + extraout_A0w) = uVar4 & 0x8000 | *(ushort *)(iVar3 + extraout_A0w);
        uVar4 = *(ushort *)(iVar3 + extraout_A1w);
        *(undefined2 *)(iVar3 + extraout_A1w) = 0x16;
        *(ushort *)(iVar3 + extraout_A1w) = uVar4 & 0x8000 | *(ushort *)(iVar3 + extraout_A1w);
        uVar4 = *(ushort *)(iVar3 + unaff_A2w);
        *(undefined2 *)(iVar3 + unaff_A2w) = 0x16;
        *(ushort *)(iVar3 + unaff_A2w) = uVar4 & 0x8000 | *(ushort *)(iVar3 + unaff_A2w);
        uVar4 = *(ushort *)(iVar3 + unaff_A3w);
        *(undefined2 *)(iVar3 + unaff_A3w) = 0x16;
        *(ushort *)(iVar3 + unaff_A3w) = uVar4 & 0x8000 | *(ushort *)(iVar3 + unaff_A3w);
        iVar3 = FUN_00014b54();
        if (-1 < iVar3) {
          if (in_A0[0x11] == 0) {
            DAT_00025368 = 0xf00;
          }
          *(undefined2 *)(extraout_A0_00 + 0xc) = 0x32;
          *(undefined2 *)(extraout_A0_00 + 0xe) = 1;
          DAT_0002529c = DAT_0002529c + 0x96;
          FUN_00014b40();
        }
      }
      else if ((((0xe < uVar7) && (uVar7 < 0x1e)) && (in_A0[0x11] == 0)) &&
              (cVar5 = FUN_00014b54(), -1 < cVar5)) {
        DAT_00025368 = 0xf00;
        sVar6 = *extraout_A0_01;
        FUN_00014ae4();
        iVar3 = DAT_00024578;
        sVar6 = (1 << (4U - (((short)((uVar4 >> 2) - sVar6) >> 1) + 3) & 0x3f) | uVar7 - 0xf) + 0xf;
        *(ushort *)(DAT_00024578 + extraout_A0w_00) =
             *(ushort *)(DAT_00024578 + extraout_A0w_00) & 0x8000 | sVar6 * 4 | 2U;
        *(ushort *)(iVar3 + extraout_A1w_00) =
             *(ushort *)(iVar3 + extraout_A1w_00) & 0x8000 | sVar6 * 4 | 2U;
        *(ushort *)(iVar3 + unaff_A2w) = *(ushort *)(iVar3 + unaff_A2w) & 0x8000 | sVar6 * 4 | 2U;
        *(ushort *)(iVar3 + unaff_A3w) = *(ushort *)(iVar3 + unaff_A3w) & 0x8000 | sVar6 * 4 | 2U;
        if (-1 < extraout_A0_01[4]) {
          sVar6 = extraout_A0_01[3];
          extraout_A0_01[4] = -1;
          extraout_A0_01[5] = 0x32;
          extraout_A0_01[6] = 1;
          DAT_0002529c = DAT_0002529c + 200;
          psVar1 = (short *)((int)&DAT_000253a0 + (short)(sVar6 * 4) + 2);
          sVar2 = *psVar1 + -1;
          *psVar1 = sVar2;
          if ((sVar2 == 0) && (*(short *)((int)&DAT_000253a0 + (int)(short)(sVar6 * 4)) == 0)) {
            uVar4 = FUN_00015ae8();
            uVar8 = (uint)uVar4;
            DAT_0002529c = uVar8 + DAT_0002529c;
            bVar9 = SBORROW1(DAT_000252d3,'\x01');
            DAT_000252d3 = DAT_000252d3 - 1;
            if ((DAT_000252d3 == 0 || bVar9 != (int)((uint)DAT_000252d3 << 0x18) < 0) &&
               (DAT_000252c1 == '\0')) {
              (*_thunk_FUN_00015078)();
              (*_thunk_FUN_00015694)(uVar8);
            }
            else {
              (*_thunk_FUN_00015624)(uVar8);
            }
          }
        }
      }
    }
  }
  return CONCAT44(in_D0,in_D1);
}


// ==== FUN_00014a4e @ 00014a4e ====

short FUN_00014a4e(void)

{
  ushort in_D0w;
  short sVar1;
  
  sVar1 = (in_D0w >> 3) * 2;
  if (((((DAT_000252ca == '\0') || (sVar1 < DAT_000253b0)) || (DAT_000253b2 < sVar1)) &&
      ((((DAT_000252c7 == '\0' || (sVar1 < DAT_000253ce)) || (DAT_000253d0 < sVar1)) &&
       (((DAT_000252cb == '\0' || (sVar1 < DAT_000253ec)) || (DAT_000253ee < sVar1)))))) &&
     ((((DAT_000252c8 == '\0' || (sVar1 < DAT_0002540a)) || (DAT_0002540c < sVar1)) &&
      ((sVar1 < DAT_00025428 || (DAT_0002542a < sVar1)))))) {
    sVar1 = -1;
  }
  return sVar1;
}


// ==== FUN_00014a52 @ 00014a52 ====

/* WARNING: Type propagation algorithm not settling */

void FUN_00014a52(void)

{
  return;
}


// ==== FUN_00014ae4 @ 00014ae4 ====

undefined8 FUN_00014ae4(void)

{
  undefined4 in_D0;
  undefined4 in_D1;
  
  return CONCAT44(in_D0,in_D1);
}


// ==== FUN_00014b40 @ 00014b40 ====

void FUN_00014b40(void)

{
  int in_A0;
  
  *(char *)(in_A0 + 10) = *(char *)(in_A0 + 8) + *(char *)(in_A0 + 10);
  *(undefined1 *)(in_A0 + 8) = 0;
  *(undefined1 *)(in_A0 + 0xb) = 0x3c;
  return;
}


// ==== FUN_00014b54 @ 00014b54 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 FUN_00014b54(void)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 in_D1;
  ushort extraout_D1w;
  ushort uVar3;
  int extraout_A0;
  int extraout_A1;
  int *piVar4;
  short *psVar5;
  int unaff_A2;
  int unaff_A3;
  
  FUN_00014ae4();
  iVar2 = extraout_A0;
  if (((((*(byte *)(DAT_00024578 + (short)extraout_A0) & 0x80) == 0) &&
       (iVar2 = extraout_A1, (*(byte *)(DAT_00024578 + (short)extraout_A1) & 0x80) == 0)) &&
      (iVar2 = unaff_A2, (*(byte *)(DAT_00024578 + (short)unaff_A2) & 0x80) == 0)) &&
     (iVar2 = unaff_A3, (*(byte *)(DAT_00024578 + (short)unaff_A3) & 0x80) == 0)) {
    uVar1 = 0xffffffff;
  }
  else {
    (*_thunk_FUN_000150c8)();
    uVar3 = extraout_D1w & 0x1fff;
    if (uVar3 == 5) {
      uVar1 = 0;
      uVar3 = (ushort)DAT_000252d7;
      piVar4 = DAT_00025448;
      do {
        if (iVar2 == *piVar4) goto LAB_00014c34;
        piVar4 = piVar4 + 4;
        uVar3 = uVar3 - 1;
      } while (uVar3 != 0xffff);
      uVar1 = 0xffffffff;
    }
    else if (uVar3 == 3) {
      uVar1 = 0;
      uVar3 = (ushort)DAT_000252d6;
      piVar4 = DAT_0002544c;
      do {
        if (iVar2 == *piVar4) goto LAB_00014c34;
        piVar4 = piVar4 + 4;
        uVar3 = uVar3 - 1;
      } while (uVar3 != 0xffff);
      uVar1 = 0xffffffff;
    }
    else if ((uVar3 < 0xf) || ('\x1e' < (char)uVar3)) {
      uVar1 = 0xffffffff;
    }
    else {
      uVar1 = 0;
      uVar3 = (ushort)DAT_000252d5;
      psVar5 = DAT_00025454;
      do {
        if ((short)iVar2 == *psVar5) goto LAB_00014c34;
        psVar5 = psVar5 + 7;
        uVar3 = uVar3 - 1;
      } while (uVar3 != 0xffff);
      uVar1 = 0xffffffff;
    }
  }
LAB_00014c34:
  return CONCAT44(uVar1,in_D1);
}


// ==== FUN_00014c3e @ 00014c3e ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 FUN_00014c3e(void)

{
  undefined2 *puVar1;
  short sVar2;
  undefined4 in_D0;
  short sVar4;
  uint uVar3;
  undefined4 in_D1;
  short sVar5;
  int extraout_A1;
  int extraout_A1_00;
  int extraout_A1_01;
  int iVar6;
  undefined **ppuVar7;
  undefined **ppuVar8;
  
  if (DAT_00024fd4 == 0) {
    ppuVar7 = &PTR_DAT_000254aa;
    while( true ) {
      ppuVar8 = ppuVar7 + 1;
      puVar1 = (undefined2 *)*ppuVar7;
      if ((int)puVar1 < 0) break;
      ppuVar7 = ppuVar8;
      if (((puVar1 != &DAT_00025428) && (puVar1[2] != 0)) && (0 < (short)puVar1[6])) {
        sVar5 = puVar1[5];
        iVar6 = *(int *)(puVar1 + 3);
        while (sVar5 = sVar5 + -1, sVar5 != -1) {
          if (*(short *)(iVar6 + 8) == 0) {
            FUN_00014efc();
            sVar4 = FUN_00014db8();
            iVar6 = extraout_A1;
            if (-1 < sVar4) {
              (*_thunk_FUN_000203be)();
              if ((DAT_00024e86 != 1) || (uVar3 = (*_thunk_FUN_000203be)(), (uVar3 & 0x8000) == 0))
              {
                (*_thunk_FUN_00015174)();
              }
              FUN_00014f5c();
              iVar6 = extraout_A1_00;
            }
          }
          else if (((*(short *)(iVar6 + 10) != 0) &&
                   (sVar4 = *(short *)(iVar6 + 0xc), sVar2 = sVar4 + -1,
                   *(short *)(iVar6 + 0xc) = sVar2, sVar2 == 0 || sVar4 < 1)) &&
                  (sVar4 = *(short *)(iVar6 + 10) + -1, *(short *)(iVar6 + 10) = sVar4, sVar4 != 0))
          {
            *(short *)(iVar6 + 0xc) = 0x32 - *(short *)(iVar6 + 10);
            (*_thunk_FUN_00015460)();
            iVar6 = extraout_A1_01;
          }
          iVar6 = iVar6 + 0xe;
        }
      }
    }
  }
  return CONCAT44(in_D0,in_D1);
}


// ==== FUN_00014d50 @ 00014d50 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 FUN_00014d50(void)

{
  undefined2 uVar1;
  undefined4 in_D0;
  uint uVar2;
  undefined4 uVar3;
  short sVar4;
  undefined4 in_D1;
  short sVar5;
  
  uVar1 = (undefined2)((uint)in_D0 >> 0x10);
  sVar5 = -1;
  if (DAT_00024fd4 == 0) {
    if (DAT_00024e84 != 0) {
      uVar2 = (*_thunk_FUN_000203be)();
      if ((uVar2 & 0x8000) == 0) {
        uVar3 = 0xffffffff;
      }
      else {
        uVar3 = CONCAT22((short)(uVar2 >> 0x10),0x5a);
      }
      goto LAB_00014db2;
    }
    uVar3 = FUN_00014db8();
    sVar4 = (short)uVar3;
    if (sVar4 < 0) goto LAB_00014db2;
    sVar5 = sVar4 + 0x81;
    uVar3 = (*_thunk_FUN_000203be)();
    uVar1 = (undefined2)((uint)uVar3 >> 0x10);
    if ((ushort)((ushort)uVar3 >> 0xc) < 6) {
      sVar5 = sVar4 + 0x88;
    }
  }
  uVar3 = CONCAT22(uVar1,sVar5);
LAB_00014db2:
  return CONCAT44(uVar3,in_D1);
}


// ==== FUN_00014db8 @ 00014db8 ====

void FUN_00014db8(void)

{
  return;
}


// ==== FUN_00014eac @ 00014eac ====

undefined4 FUN_00014eac(void)

{
  undefined4 in_D0;
  
  FUN_00014a4e();
  return in_D0;
}


// ==== FUN_00014efc @ 00014efc ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 FUN_00014efc(void)

{
  undefined4 in_D0;
  ushort uVar1;
  ushort uVar2;
  undefined4 in_D1;
  
  uVar2 = (short)in_D0 - DAT_00024fca;
  if ((short)uVar2 < 0) {
    uVar2 = -uVar2;
  }
  uVar1 = (*_thunk_FUN_000203be)();
  if ((uVar2 < (uVar1 & 0x1ff)) && (DAT_00026c9a = 0xff, DAT_00024fc8 < 0xc9)) {
    uVar2 = (*_thunk_FUN_000203be)();
    if ((short)((uVar2 & 0xf) - 6) < 0) {
      (*_thunk_FUN_000203be)();
      (*_thunk_FUN_000152b0)();
      FUN_00011ae2();
    }
  }
  return CONCAT44(in_D0,in_D1);
}


// ==== FUN_00014f5c @ 00014f5c ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 FUN_00014f5c(void)

{
  bool bVar1;
  short sVar2;
  undefined4 in_D0;
  ushort uVar3;
  ushort uVar4;
  undefined4 in_D1;
  ushort uVar5;
  
  uVar4 = (short)in_D0 - DAT_00026dac;
  if ((short)uVar4 < 0) {
    uVar4 = -uVar4;
  }
  if ((short)uVar4 < 0x1c1) {
    if ((short)uVar4 <= (short)DAT_000273a6) {
      DAT_000273a6 = uVar4;
    }
    uVar5 = DAT_00024fc8;
    if ((short)uVar4 <= (short)DAT_00024fc8) {
      uVar5 = uVar4;
      uVar4 = DAT_00024fc8;
    }
    DAT_000273a4._0_1_ = 0xff;
    if (DAT_00026ec2 == 0) {
      uVar3 = (*_thunk_FUN_000203be)();
      if ((short)((uVar5 >> 2) + uVar4) <= (short)(uVar3 & 0x1ff)) {
        uVar4 = (*_thunk_FUN_000203be)();
        if ((uVar4 & 0x7ff) < 0x19a) {
          FUN_000154e0();
          sVar2 = DAT_00024fd8 + -1;
          bVar1 = DAT_00024fd8 < 1;
          DAT_00024fd8 = sVar2;
          if (sVar2 == 0 || bVar1) {
            DAT_00024fda = DAT_00024fda + -1;
            uVar4 = (*_thunk_FUN_000203be)();
            DAT_00024fd6 = DAT_00024fd6 - (uVar4 & 3);
            uVar4 = (*_thunk_FUN_000203be)();
            DAT_00024fd8 = (uVar4 & 7) + 6;
          }
        }
      }
    }
  }
  return CONCAT44(in_D0,in_D1);
}


// ==== FUN_00014fee @ 00014fee ====

/* WARNING: Removing unreachable block (ram,0x00015010) */
/* WARNING: Removing unreachable block (ram,0x0001501e) */
/* WARNING: Removing unreachable block (ram,0x00015020) */

undefined4 FUN_00014fee(void)

{
  undefined4 in_D0;
  
  FUN_00015034();
  return in_D0;
}


// ==== FUN_00015034 @ 00015034 ====

void FUN_00015034(void)

{
  short sVar1;
  short unaff_D2w;
  short unaff_D7w;
  short sVar2;
  int in_A0;
  int in_A1;
  
  sVar2 = unaff_D7w + -1;
  do {
    if (*(char *)(in_A0 + 9) < *(char *)(in_A1 + 9)) {
      return;
    }
    if ((*(char *)(in_A0 + 9) == *(char *)(in_A1 + 9)) && ('\x01' < *(char *)(in_A1 + 8))) {
      sVar1 = *(short *)(in_A0 + 4) - *(short *)(in_A1 + 4);
      if (sVar1 != 0) {
        if (sVar1 < 0) {
          sVar1 = -sVar1;
        }
        if (sVar1 <= unaff_D2w) {
          unaff_D2w = sVar1;
        }
      }
    }
    in_A1 = in_A1 + 0x10;
    sVar2 = sVar2 + -1;
  } while (sVar2 != -1);
  return;
}


// ==== FUN_00015076 @ 00015076 ====

void FUN_00015076(void)

{
  return;
}


// ==== FUN_00015078 @ 00015078 ====

undefined4 FUN_00015078(void)

{
  undefined4 in_D0;
  
  (**(code **)(DAT_00026ec4 + -0x20a))();
  return in_D0;
}


// ==== FUN_00015094 @ 00015094 ====

undefined4 FUN_00015094(void)

{
  undefined4 in_D0;
  
  (**(code **)(DAT_00026ec4 + -0x20a))();
  return in_D0;
}


// ==== FUN_000150b0 @ 000150b0 ====

undefined8 FUN_000150b0(void)

{
  undefined4 in_D0;
  undefined4 in_D1;
  
  FUN_00016f20(DAT_00026d7c);
  FUN_0001520c();
  return CONCAT44(in_D0,in_D1);
}


// ==== FUN_000150c8 @ 000150c8 ====

ulonglong FUN_000150c8(void)

{
  undefined4 in_D0;
  ushort uVar1;
  undefined4 in_D1;
  
  uVar1 = (ushort)in_D0;
  if ((-1 < (short)uVar1) && (uVar1 < DAT_00024580)) {
    uVar1 = *(ushort *)(DAT_00024578 + (short)((uVar1 >> 3) * 2));
    return CONCAT44(CONCAT22((short)((uint)in_D0 >> 0x10),uVar1),
                    CONCAT22((short)((uint)in_D1 >> 0x10),uVar1 >> 2)) & 0xffff0003ffff01ff;
  }
  return 0;
}


// ==== FUN_00015102 @ 00015102 ====

void FUN_00015102(void)

{
  return;
}


// ==== FUN_00015104 @ 00015104 ====

short FUN_00015104(void)

{
  short in_D0w;
  ushort uVar1;
  ushort uVar2;
  
  uVar2 = in_D0w + 0x100U & 0x3ff;
  if (0xff < uVar2) {
    uVar1 = uVar2 - 0x200;
    if (0x1ff < uVar2) {
      if (0xff < uVar1) {
        uVar1 = -(uVar2 - 0x400);
      }
      return -*(short *)(&DAT_000248bc + (short)(uVar1 * 2));
    }
    uVar2 = -uVar1;
  }
  return *(short *)(&DAT_000248bc + (short)(uVar2 * 2));
}


// ==== FUN_00015108 @ 00015108 ====

short FUN_00015108(void)

{
  ushort in_D0w;
  ushort uVar1;
  ushort uVar2;
  
  uVar2 = in_D0w & 0x3ff;
  if (0xff < uVar2) {
    uVar1 = uVar2 - 0x200;
    if (0x1ff < uVar2) {
      if (0xff < uVar1) {
        uVar1 = -(uVar2 - 0x400);
      }
      return -*(short *)(&DAT_000248bc + (short)(uVar1 * 2));
    }
    uVar2 = -uVar1;
  }
  return *(short *)(&DAT_000248bc + (short)(uVar2 * 2));
}


// ==== FUN_0001514c @ 0001514c ====

undefined6 FUN_0001514c(void)

{
  ushort in_D0w;
  ushort uVar1;
  short sVar2;
  undefined4 in_D1;
  
  uVar1 = in_D0w;
  if ((short)in_D0w < 0) {
    uVar1 = -in_D0w;
  }
  sVar2 = *(short *)(&DAT_000246bc + (short)((uVar1 & 0xff) * 2));
  if ((short)in_D0w < 0) {
    sVar2 = -sVar2;
  }
  return CONCAT24(sVar2,in_D1);
}


// ==== FUN_00015174 @ 00015174 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 FUN_00015174(void)

{
  undefined4 in_D0;
  short sVar1;
  undefined4 in_D1;
  
  sVar1 = (short)in_D0 - DAT_00024e80;
  if (DAT_00024e84 != 0) {
    sVar1 = sVar1 >> 3;
  }
  if ((-0x81 < sVar1) && (sVar1 < 0x1c1)) {
    (*_thunk_FUN_00020ce2)();
  }
  return CONCAT44(in_D0,in_D1);
}


// ==== FUN_000151c2 @ 000151c2 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 FUN_000151c2(void)

{
  undefined4 in_D0;
  short sVar1;
  undefined4 in_D1;
  
  sVar1 = (short)in_D0 - DAT_00024e80;
  if (DAT_00024e84 != 0) {
    sVar1 = sVar1 >> 3;
  }
  if ((-0x81 < sVar1) && (sVar1 < 0x1c1)) {
    (*_thunk_FUN_00020e24)();
    return CONCAT44(in_D0,in_D1);
  }
  return CONCAT44(in_D0,in_D1);
}


// ==== FUN_0001520c @ 0001520c ====

void FUN_0001520c(void)

{
  return;
}


// ==== FUN_0001520e @ 0001520e ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined6 FUN_0001520e(void)

{
  ushort uVar1;
  undefined4 in_D1;
  
  uVar1 = (ushort)(byte)(&DAT_000255f6)[(short)(_DAT_00dff00c >> 6 & 0xc | _DAT_00dff00c & 3)];
  if ((((&DAT_000255f6)[(short)(_DAT_00dff00c >> 6 & 0xc | _DAT_00dff00c & 3)] & 3) != 0) &&
     (DAT_00025446 != '\0')) {
    uVar1 = uVar1 ^ 3;
  }
  return CONCAT24(uVar1,in_D1);
}


// ==== FUN_0001524a @ 0001524a ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0001524a(void)

{
  (*_thunk_FUN_0002129c)();
  return;
}


// ==== FUN_0001525c @ 0001525c ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0001525c(void)

{
  (*_thunk_FUN_0002129c)();
  return;
}


// ==== FUN_0001526e @ 0001526e ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 FUN_0001526e(void)

{
  undefined4 in_D0;
  undefined4 in_D1;
  
  (*_thunk_FUN_0002129c)();
  return CONCAT44(in_D0,in_D1);
}


// ==== FUN_000152ac @ 000152ac ====

undefined2 FUN_000152ac(undefined4 param_1)

{
  char cVar1;
  short sVar2;
  int extraout_A1;
  undefined2 *puVar3;
  
  sVar2 = 0x14;
  puVar3 = DAT_00026e80;
  while( true ) {
    sVar2 = sVar2 + -1;
    if (sVar2 == -1) {
      return param_1._0_2_;
    }
    if (*(char *)(puVar3 + 1) == '\0') break;
    puVar3 = puVar3 + 2;
  }
  *puVar3 = param_1._0_2_;
  cVar1 = FUN_000150c8();
  *(char *)(extraout_A1 + 3) = cVar1;
  if (cVar1 == '\x02') {
    *(undefined1 *)(extraout_A1 + 2) = 4;
    return param_1._0_2_;
  }
  *(undefined1 *)(extraout_A1 + 2) = 6;
  return param_1._0_2_;
}


// ==== FUN_000152b0 @ 000152b0 ====

undefined4 FUN_000152b0(void)

{
  undefined4 in_D0;
  char cVar1;
  short sVar2;
  int extraout_A1;
  undefined2 *puVar3;
  
  sVar2 = 0x14;
  puVar3 = DAT_00026e80;
  while( true ) {
    sVar2 = sVar2 + -1;
    if (sVar2 == -1) {
      return in_D0;
    }
    if (*(char *)(puVar3 + 1) == '\0') break;
    puVar3 = puVar3 + 2;
  }
  *puVar3 = (short)in_D0;
  cVar1 = FUN_000150c8();
  *(char *)(extraout_A1 + 3) = cVar1;
  if (cVar1 == '\x02') {
    *(undefined1 *)(extraout_A1 + 2) = 4;
    return in_D0;
  }
  *(undefined1 *)(extraout_A1 + 2) = 6;
  return in_D0;
}


// ==== FUN_000152f8 @ 000152f8 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 FUN_000152f8(void)

{
  undefined4 in_D0;
  undefined4 in_D1;
  short sVar1;
  int extraout_A1;
  int iVar2;
  
  (*_thunk_FUN_000212ce)();
  sVar1 = 0x14;
  iVar2 = DAT_00026e80;
  while (sVar1 = sVar1 + -1, sVar1 != -1) {
    if (*(char *)(iVar2 + 2) != '\0') {
      FUN_00015174();
      *(char *)(extraout_A1 + 2) = *(char *)(extraout_A1 + 2) + -1;
      iVar2 = extraout_A1;
    }
    iVar2 = iVar2 + 4;
  }
  (*_thunk_FUN_000212d4)();
  return CONCAT44(in_D0,in_D1);
}


// ==== FUN_0001535a @ 0001535a ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 FUN_0001535a(void)

{
  undefined4 in_D0;
  short sVar2;
  undefined4 uVar1;
  undefined4 in_D1;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  
  sVar2 = 0xb7;
  puVar3 = DAT_00026d9a;
  puVar5 = DAT_00026ed2;
  puVar7 = DAT_00026dc6;
  puVar6 = DAT_00026ea4;
  do {
    puVar8 = puVar6;
    puVar4 = puVar5;
    puVar6 = puVar8 + 1;
    *puVar8 = *puVar3;
    puVar5 = puVar4 + 1;
    *puVar4 = *puVar7;
    sVar2 = sVar2 + -1;
    puVar3 = puVar3 + 1;
    puVar7 = puVar7 + 1;
  } while (sVar2 != -1);
  sVar2 = 0x17;
  puVar3 = DAT_00026ea0;
  if (DAT_00026ea0 == (undefined4 *)0x0) {
    puVar8 = puVar8 + 2;
    *puVar6 = 0;
    puVar4 = puVar4 + 2;
    *puVar5 = 0;
  }
  else {
    do {
      puVar8 = puVar6 + 1;
      *puVar6 = *puVar3;
      uVar1 = (*_thunk_FUN_00020560)();
      puVar4 = puVar5 + 1;
      *puVar5 = uVar1;
      sVar2 = sVar2 + -1;
      puVar3 = puVar3 + 1;
      puVar5 = puVar4;
      puVar6 = puVar8;
    } while (sVar2 != -1);
  }
  sVar2 = 0x1a;
  puVar3 = DAT_00026e98;
  if (DAT_00026e98 == (undefined4 *)0x0) {
    puVar7 = puVar8 + 1;
    *puVar8 = 0;
    puVar5 = puVar4 + 1;
    *puVar4 = 0;
  }
  else {
    do {
      puVar7 = puVar8 + 1;
      *puVar8 = *puVar3;
      uVar1 = (*_thunk_FUN_00020560)();
      puVar5 = puVar4 + 1;
      *puVar4 = uVar1;
      sVar2 = sVar2 + -1;
      puVar3 = puVar3 + 1;
      puVar4 = puVar5;
      puVar8 = puVar7;
    } while (sVar2 != -1);
  }
  sVar2 = 0xc;
  puVar3 = DAT_00026e90;
  if (DAT_000252c8 == '\0') {
    puVar4 = puVar7 + 1;
    *puVar7 = 0;
    puVar6 = puVar5 + 1;
    *puVar5 = 0;
  }
  else {
    do {
      puVar4 = puVar7 + 1;
      *puVar7 = *puVar3;
      uVar1 = (*_thunk_FUN_00020560)();
      puVar6 = puVar5 + 1;
      *puVar5 = uVar1;
      sVar2 = sVar2 + -1;
      puVar3 = puVar3 + 1;
      puVar5 = puVar6;
      puVar7 = puVar4;
    } while (sVar2 != -1);
  }
  sVar2 = 0x18;
  puVar3 = DAT_00026e88;
  if (DAT_00026e88 == (undefined4 *)0x0) {
    *puVar4 = 0;
    *puVar6 = 0;
  }
  else {
    do {
      *puVar4 = *puVar3;
      uVar1 = (*_thunk_FUN_00020560)();
      *puVar6 = uVar1;
      sVar2 = sVar2 + -1;
      puVar3 = puVar3 + 1;
      puVar6 = puVar6 + 1;
      puVar4 = puVar4 + 1;
    } while (sVar2 != -1);
  }
  return CONCAT44(in_D0,in_D1);
}


// ==== FUN_00015460 @ 00015460 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00015460(void)

{
  undefined4 in_D0;
  uint uVar1;
  int in_D1;
  undefined2 unaff_D2w;
  short sVar2;
  undefined4 *puVar3;
  int extraout_A0;
  int extraout_A0_00;
  
  sVar2 = 0x27;
  puVar3 = DAT_00026ea8;
  do {
    if (*(short *)(puVar3 + 4) == 0) {
      *puVar3 = in_D0;
      if (in_D1 < 0x100000) {
        in_D1 = 0x100000;
      }
      puVar3[1] = in_D1;
      *(undefined2 *)(puVar3 + 4) = unaff_D2w;
      *(undefined2 *)((int)puVar3 + 0x12) = 6;
      uVar1 = (*_thunk_FUN_000203be)();
      *(uint *)(extraout_A0 + 8) = (uVar1 & 0xffff) + 0x10000;
      uVar1 = (*_thunk_FUN_000203be)();
      *(uint *)(extraout_A0_00 + 0xc) = (uVar1 & 0xffff) + 0x10000;
      return;
    }
    puVar3 = puVar3 + 5;
    sVar2 = sVar2 + -1;
  } while (sVar2 != -1);
  return;
}


// ==== FUN_000154cc @ 000154cc ====

void FUN_000154cc(void)

{
  FUN_00015460();
  return;
}


// ==== FUN_000154e0 @ 000154e0 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 FUN_000154e0(void)

{
  undefined4 in_D0;
  undefined4 in_D1;
  
  FUN_00015460();
  return CONCAT44(in_D0,in_D1);
}


// ==== FUN_0001555a @ 0001555a ====

undefined4 FUN_0001555a(void)

{
  undefined4 in_A0;
  
  if (DAT_00025706 == 0) {
    DAT_00025706 = in_A0;
    return 0;
  }
  return 0xffffffff;
}


// ==== FUN_0001556e @ 0001556e ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0001556e(void)

{
  if (DAT_00024bfc != 0) {
                    /* WARNING: Could not recover jumptable at 0x00015576. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (*_thunk_FUN_00021dce)();
    return;
  }
  return;
}


// ==== FUN_0001557c @ 0001557c ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0001557c(void)

{
  ushort uVar2;
  char cVar3;
  uint uVar1;
  char cVar4;
  short *psVar5;
  
  psVar5 = DAT_00026eb6;
  if ((DAT_000252ad != '\0') && (DAT_00024e86 == 8)) {
    cVar4 = '\0';
    (*_thunk_FUN_000212ce)();
    do {
      if (*(char *)((int)psVar5 + 0x11) == '\0') {
        *psVar5 = DAT_000252e2;
        *psVar5 = *psVar5 + -0x74;
        psVar5[2] = 0x38;
        uVar2 = (*_thunk_FUN_000203be)();
        uVar2 = uVar2 >> 0xc & 3;
        cVar3 = (char)uVar2;
        if (uVar2 == 0) {
          cVar3 = '\x02';
        }
        *(char *)(psVar5 + 8) = cVar3 + -1;
        uVar1 = (*_thunk_FUN_000203be)();
        *(uint *)(psVar5 + 4) = (uVar1 & 0xffff) * 2 + 0x10000;
        uVar1 = (*_thunk_FUN_000203be)();
        *(uint *)(psVar5 + 6) = (uVar1 & 0xffff) * 2 + 0x10000;
        *(undefined1 *)((int)psVar5 + 0x11) = 0xff;
      }
      FUN_00015174();
      psVar5 = psVar5 + 9;
      cVar4 = cVar4 + '\x01';
    } while (cVar4 != '\x14');
    (*_thunk_FUN_000212d4)();
  }
  return;
}


// ==== FUN_00015624 @ 00015624 ====

void FUN_00015624(void)

{
  FUN_00015078();
  FUN_0001555a();
  return;
}


// ==== FUN_00015640 @ 00015640 ====

void FUN_00015640(void)

{
  undefined **ppuVar1;
  int in_A1;
  
  if (*(short *)(in_A1 + 0x12) != 0) {
    ppuVar1 = &PTR_s_Battleship_00023af8;
    if (((*(short *)(in_A1 + 0x12) != 0x1194) &&
        (ppuVar1 = &PTR_s_Carrier_00023afc, *(short *)(in_A1 + 0x12) != 6000)) &&
       (ppuVar1 = &PTR_s_Destroyer_00023b00, *(short *)(in_A1 + 0x12) != 0x9c4)) {
      ppuVar1 = &PTR_s_Cruiser_00023b04;
    }
    FUN_00015078(*ppuVar1,(int)*(short *)(in_A1 + 0x12));
  }
  return;
}


// ==== FUN_00015694 @ 00015694 ====

undefined4 FUN_00015694(void)

{
  char cVar1;
  undefined4 in_D0;
  char *pcVar2;
  
  DAT_00025310 = DAT_00025310 + 1;
  if (*(short *)((int)&DAT_00025498 + (int)(short)(DAT_0002530e * 2)) < DAT_00025310) {
    DAT_00025310 = 1;
    DAT_0002530e = DAT_0002530e + 1;
    if (6 < DAT_0002530e) {
      DAT_0002530e = 6;
    }
    DAT_000252ad = 0xff;
    pcVar2 = &DAT_000270ba;
    do {
      cVar1 = *pcVar2;
      pcVar2 = pcVar2 + 1;
    } while (cVar1 != '\0');
    FUN_00015078();
  }
  else {
    pcVar2 = &DAT_000270ba;
    do {
      cVar1 = *pcVar2;
      pcVar2 = pcVar2 + 1;
    } while (cVar1 != '\0');
    FUN_00015078();
  }
  DAT_00025706 = &DAT_000270ba;
  DAT_0002530c = 0xffff;
  return in_D0;
}


// ==== FUN_00015710 @ 00015710 ====

short FUN_00015710(ushort *param_1)

{
  ushort uVar1;
  short sVar2;
  undefined2 *puVar3;
  
  uVar1 = *param_1 >> 2 & 0x1ff;
  sVar2 = 0;
  if (((((uVar1 == 6) || (sVar2 = 1, uVar1 == 7)) || (sVar2 = 2, uVar1 == 8)) ||
      ((uVar1 == 0xb || (sVar2 = 3, uVar1 == 3)))) || (sVar2 = 4, uVar1 == 4)) {
LAB_00015878:
    sVar2 = *(short *)((int)&DAT_00025712 + (int)(short)(sVar2 * 2)) - (*param_1 >> 0xb & 7);
  }
  else {
    sVar2 = 5;
    if (0xe < uVar1) {
      if (uVar1 < 0x1f) goto LAB_00015878;
      puVar3 = &DAT_000253ec;
      if ((((((uVar1 == 0xcc) || (puVar3 = &DAT_0002540a, uVar1 == 0xf1)) ||
            ((uVar1 == 0xf3 ||
             (((uVar1 == 0xf2 || (uVar1 == 0xf6)) || (puVar3 = &DAT_000253ce, uVar1 == 0x10c))))))
           || ((uVar1 == 0x10e || (uVar1 == 0x10d)))) || (uVar1 == 0x10f)) ||
         (((uVar1 == 0x110 || (puVar3 = &DAT_000253b0, uVar1 == 0xe5)) ||
          ((uVar1 == 0xe6 || ((uVar1 == 0xe4 || (uVar1 == 0xe7)))))))) {
        return (puVar3[7] - puVar3[10]) - DAT_000252fe;
      }
      if (((((uVar1 == 0x20) || (uVar1 == 0x1f)) || (uVar1 == 0x21)) ||
          ((uVar1 == 0x26 || (uVar1 == 0x23)))) ||
         (((uVar1 == 0x22 || ((uVar1 == 0x24 || (uVar1 == 0x25)))) ||
          ((uVar1 == 0x9f || (uVar1 == 0x27)))))) {
        return ((DAT_00025436 - DAT_0002543c) - DAT_000252fe) - DAT_000252e6;
      }
    }
    sVar2 = 0;
  }
  return sVar2;
}


// ==== FUN_00015714 @ 00015714 ====

short FUN_00015714(void)

{
  ushort uVar1;
  short sVar2;
  ushort *in_A0;
  undefined2 *puVar3;
  
  uVar1 = *in_A0 >> 2 & 0x1ff;
  sVar2 = 0;
  if (((((uVar1 == 6) || (sVar2 = 1, uVar1 == 7)) || (sVar2 = 2, uVar1 == 8)) ||
      ((uVar1 == 0xb || (sVar2 = 3, uVar1 == 3)))) || (sVar2 = 4, uVar1 == 4)) {
LAB_00015878:
    sVar2 = *(short *)((int)&DAT_00025712 + (int)(short)(sVar2 * 2)) - (*in_A0 >> 0xb & 7);
  }
  else {
    sVar2 = 5;
    if (0xe < uVar1) {
      if (uVar1 < 0x1f) goto LAB_00015878;
      puVar3 = &DAT_000253ec;
      if ((((((uVar1 == 0xcc) || (puVar3 = &DAT_0002540a, uVar1 == 0xf1)) ||
            ((uVar1 == 0xf3 ||
             (((uVar1 == 0xf2 || (uVar1 == 0xf6)) || (puVar3 = &DAT_000253ce, uVar1 == 0x10c))))))
           || ((uVar1 == 0x10e || (uVar1 == 0x10d)))) || (uVar1 == 0x10f)) ||
         (((uVar1 == 0x110 || (puVar3 = &DAT_000253b0, uVar1 == 0xe5)) ||
          ((uVar1 == 0xe6 || ((uVar1 == 0xe4 || (uVar1 == 0xe7)))))))) {
        return (puVar3[7] - puVar3[10]) - DAT_000252fe;
      }
      if (((((uVar1 == 0x20) || (uVar1 == 0x1f)) || (uVar1 == 0x21)) ||
          ((uVar1 == 0x26 || (uVar1 == 0x23)))) ||
         (((uVar1 == 0x22 || ((uVar1 == 0x24 || (uVar1 == 0x25)))) ||
          ((uVar1 == 0x9f || (uVar1 == 0x27)))))) {
        return ((DAT_00025436 - DAT_0002543c) - DAT_000252fe) - DAT_000252e6;
      }
    }
    sVar2 = 0;
  }
  return sVar2;
}


// ==== FUN_00015898 @ 00015898 ====

uint FUN_00015898(short param_1)

{
  short *psVar1;
  uint uVar2;
  ushort uVar3;
  
  uVar3 = *(ushort *)(DAT_00024578 + (short)(param_1 - (short)DAT_00024578)) & 0xff03;
  if ((char)uVar3 == '\x01') {
    uVar2 = 0;
    while( true ) {
      psVar1 = *(short **)((int)&PTR_DAT_000254aa + (int)(short)uVar2);
      if (psVar1 == (short *)0xffffffff) break;
      if (((psVar1[2] != 0) && (*psVar1 <= (short)uVar3)) && ((short)uVar3 <= psVar1[1])) {
        return uVar2;
      }
      uVar2 = (uint)(ushort)((short)uVar2 + 4);
    }
  }
  return 0xffffffff;
}


// ==== FUN_000158ec @ 000158ec ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_000158ec(void)

{
  (*_thunk_FUN_00020848)();
  return;
}


// ==== FUN_000158fe @ 000158fe ====

void FUN_000158fe(void)

{
  FUN_000165cc();
  return;
}


// ==== FUN_00015910 @ 00015910 ====

longlong FUN_00015910(undefined4 param_1,uint param_2)

{
  short sVar1;
  
  sVar1 = FUN_00015956();
  if (sVar1 != 0) {
    (**(code **)(DAT_00026e72 + -0x24))();
  }
  return (ulonglong)param_2 << 0x20;
}


// ==== FUN_0001591e @ 0001591e ====

undefined6 FUN_0001591e(void)

{
  byte bVar1;
  short in_D0w;
  undefined4 in_D1;
  ushort uVar2;
  short sVar3;
  byte *in_A0;
  
  sVar3 = 0;
  do {
    bVar1 = *in_A0;
    if ((bVar1 <= DAT_00026ebf) && (DAT_00026ebe <= bVar1)) {
      bVar1 = *(byte *)(DAT_00026eba + 4 + (int)(short)(ushort)(byte)(bVar1 - DAT_00026ebe));
      uVar2 = (ushort)bVar1;
      if (bVar1 == 0) {
        uVar2 = 10;
      }
      sVar3 = uVar2 + sVar3 + 1;
    }
    in_D0w = in_D0w + -1;
    in_A0 = in_A0 + 1;
  } while (in_D0w != -1);
  return CONCAT24(sVar3,in_D1);
}


// ==== FUN_00015956 @ 00015956 ====

/* WARNING: Restarted to delay deadcode elimination for space: ram */

undefined8 FUN_00015956(void)

{
  byte bVar1;
  byte bVar2;
  bool bVar3;
  int iVar4;
  int iVar5;
  undefined4 in_D0;
  ushort uVar6;
  undefined4 in_D1;
  ushort extraout_D1w;
  short unaff_D2w;
  ushort uVar7;
  short unaff_D3w;
  ushort unaff_D4w;
  ushort unaff_D5w;
  short sVar8;
  short sVar9;
  byte *extraout_A0;
  byte *pbVar10;
  undefined2 *extraout_A1;
  ushort *puVar11;
  undefined2 *puVar12;
  uint *puVar13;
  ushort local_3e;
  
  DAT_00027690 = 0;
  local_3e = (short)in_D0 - 1;
  if (0 < (short)in_D0) {
    uVar6 = FUN_0001591e();
    if (DAT_0002768a < uVar6) {
      DAT_0002768a = uVar6;
    }
    if ((uVar6 <= unaff_D4w) && (unaff_D5w <= DAT_00026ec0)) {
      DAT_00027686 = 0;
      DAT_00027688 = 0;
      sVar9 = unaff_D3w - uVar6;
      DAT_00027690 = uVar6;
      if (sVar9 != 0 && (short)uVar6 <= unaff_D3w) {
        DAT_00027690 = sVar9 + uVar6;
        DAT_00027686 = (short)((uint)(int)sVar9 / (uint)local_3e);
        DAT_00027688 = (short)((uint)(int)sVar9 % (uint)local_3e);
      }
      DAT_00027680 = ((ushort)(unaff_D4w + 0xf) >> 4) * 2;
      uVar6 = extraout_D1w & 0xf;
      sVar9 = unaff_D2w * DAT_00027680 + ((short)extraout_D1w >> 4) * 2;
      sVar8 = ((ushort)(unaff_D5w * DAT_00027680) >> 1) - 1;
      puVar12 = extraout_A1;
      do {
        *puVar12 = 0;
        iVar5 = DAT_00026eba;
        iVar4 = DAT_00026d66;
        sVar8 = sVar8 + -1;
        pbVar10 = extraout_A0;
        puVar12 = puVar12 + 1;
        DAT_0002768c = extraout_A1;
      } while (sVar8 != -1);
      do {
        bVar1 = *pbVar10;
        if ((bVar1 <= DAT_00026ebf) && (DAT_00026ebe <= bVar1)) {
          DAT_00027682 = 10;
          bVar2 = *(byte *)(iVar5 + 4 + (int)(short)(ushort)(byte)(bVar1 - DAT_00026ebe));
          if (bVar2 != 0) {
            DAT_00027682 = (ushort)bVar2;
            DAT_00027684 = (ushort)(DAT_00027682 + 0xf) >> 4;
            DAT_0002767e = DAT_00027680 + DAT_00027684 * -2;
            puVar11 = (ushort *)
                      (*(short *)((int)&DAT_00026ca6 +
                                 (int)(short)((ushort)(byte)(bVar1 - DAT_00026ebe) * 2)) + iVar4);
            puVar13 = (uint *)((int)sVar9 + (int)DAT_0002768c);
            sVar8 = DAT_00026ec0 - 1;
            uVar7 = DAT_00027684;
            do {
              while ((ushort)(uVar7 - 1) != 0xffff) {
                *puVar13 = ((uint)*puVar11 << 0x10) >> uVar6 | *puVar13;
                puVar13 = (uint *)((int)puVar13 + 2);
                puVar11 = puVar11 + 1;
                uVar7 = uVar7 - 1;
              }
              puVar13 = (uint *)((int)DAT_0002767e + (int)puVar13);
              sVar8 = sVar8 + -1;
              uVar7 = DAT_00027684;
            } while (sVar8 != -1);
          }
          uVar7 = DAT_00027686 + DAT_00027682 + uVar6 + 1;
          if (0 < DAT_00027688) {
            uVar7 = uVar7 + 1;
          }
          uVar6 = uVar7 & 0xf;
          sVar9 = (uVar7 >> 4) * 2 + sVar9;
          DAT_00027688 = DAT_00027688 + -1;
        }
        bVar3 = 0 < (short)local_3e;
        pbVar10 = pbVar10 + 1;
        local_3e = local_3e - 1;
      } while (bVar3);
    }
  }
  return CONCAT44(CONCAT22((short)((uint)in_D0 >> 0x10),DAT_00027690),in_D1);
}


// ==== FUN_00015a8c @ 00015a8c ====

undefined8 FUN_00015a8c(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  short sVar1;
  
  sVar1 = FUN_00015956();
  if (sVar1 != 0) {
    (**(code **)(DAT_00026e72 + -0x24))();
  }
  return CONCAT44(param_2,param_3);
}


// ==== FUN_00015ae8 @ 00015ae8 ====

undefined6 FUN_00015ae8(void)

{
  short in_D0w;
  undefined4 in_D1;
  
  return CONCAT24(*(undefined2 *)
                   (&DAT_000233cc +
                   (short)(in_D0w * 2 +
                          (ushort)(byte)(&DAT_000233af)[(short)(DAT_00025310 + DAT_0002530e * 4)] *
                          8)),in_D1);
}


// ==== FUN_00015b16 @ 00015b16 ====

undefined8 FUN_00015b16(void)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 in_D1;
  
  iVar1 = DAT_00026e6e;
  iVar2 = (**(code **)(DAT_00026e6e + -0x1e))();
  uVar3 = 0;
  if (iVar2 != 0) {
    (**(code **)(iVar1 + -0x42))();
    uVar3 = (**(code **)(iVar1 + -0x42))();
    (**(code **)(iVar1 + -0x24))();
  }
  return CONCAT44(uVar3,in_D1);
}


// ==== FUN_00015b1a @ 00015b1a ====

undefined8 FUN_00015b1a(void)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 in_D1;
  
  iVar1 = DAT_00026e6e;
  iVar2 = (**(code **)(DAT_00026e6e + -0x1e))();
  uVar3 = 0;
  if (iVar2 != 0) {
    (**(code **)(iVar1 + -0x42))();
    uVar3 = (**(code **)(iVar1 + -0x42))();
    (**(code **)(iVar1 + -0x24))();
  }
  return CONCAT44(uVar3,in_D1);
}


// ==== FUN_00015b58 @ 00015b58 ====

byte FUN_00015b58(ushort *param_1)

{
  ushort uVar1;
  ushort uVar2;
  char cVar3;
  byte bVar4;
  byte bVar5;
  ushort uVar6;
  short sVar7;
  short sVar8;
  ushort *puVar9;
  ushort *puVar10;
  byte *pbVar11;
  
  bVar5 = 0;
  if (param_1 != (ushort *)0x0) {
    uVar1 = *param_1;
    param_1[2] = (uVar1 * 8 + -1) - param_1[2];
    puVar10 = param_1 + 10;
    pbVar11 = (byte *)((int)param_1 + (short)uVar1 + 0x14);
    uVar6 = uVar1 >> 1;
    uVar2 = param_1[1];
    bVar5 = 0;
    param_1 = param_1 + 7;
    cVar3 = *(char *)param_1;
    while (cVar3 != '\0') {
      param_1 = (ushort *)((int)param_1 + 1);
      sVar8 = uVar6 - 1;
      sVar7 = uVar2 - 1;
      do {
        do {
          bVar5 = *(byte *)puVar10;
          pbVar11 = pbVar11 + -1;
          bVar4 = *pbVar11;
          *pbVar11 = (&DAT_00025606)[(short)(ushort)bVar5];
          puVar9 = (ushort *)((int)puVar10 + 1);
          *(undefined *)puVar10 = (&DAT_00025606)[(short)(ushort)bVar4];
          sVar8 = sVar8 + -1;
          puVar10 = puVar9;
        } while (sVar8 != -1);
        pbVar11 = pbVar11 + (short)(uVar6 + uVar1);
        puVar10 = (ushort *)((int)(short)uVar6 + (int)puVar9);
        sVar7 = sVar7 + -1;
        sVar8 = uVar6 - 1;
      } while (sVar7 != -1);
      cVar3 = *(char *)param_1;
    }
  }
  return bVar5;
}


// ==== FUN_00015bc6 @ 00015bc6 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

ulonglong FUN_00015bc6(void)

{
  int iVar1;
  undefined4 uVar2;
  undefined2 unaff_D5w;
  undefined4 *puVar3;
  undefined4 in_A0;
  int *in_A1;
  int *piVar4;
  undefined4 *puVar5;
  undefined8 uVar6;
  ulonglong uVar7;
  undefined8 uVar8;
  
  piVar4 = in_A1;
  do {
    iVar1 = *piVar4;
    piVar4 = piVar4 + 1;
  } while (iVar1 != 0);
  DAT_000255f2 = in_A0;
  uVar6 = FUN_00015d50();
  uVar2 = (undefined4)uVar6;
  if ((int)((ulonglong)uVar6 >> 0x20) != 0) {
    puVar3 = (undefined4 *)0x0;
    if (in_A1 != (int *)0x0) {
      uVar6 = FUN_000158ec(unaff_D5w);
      puVar3 = (undefined4 *)((ulonglong)uVar6 >> 0x20);
      uVar2 = (undefined4)uVar6;
      if (puVar3 != (undefined4 *)0x0) {
        *puVar3 = 0;
        while( true ) {
          puVar5 = (undefined4 *)((ulonglong)uVar6 >> 0x20);
          uVar2 = (undefined4)uVar6;
          if (*in_A1 == 0) break;
          uVar8 = (*_thunk_FUN_00020560)();
          uVar6 = CONCAT44(puVar5 + 1,(int)uVar8);
          *puVar5 = (int)((ulonglong)uVar8 >> 0x20);
          in_A1 = in_A1 + 1;
        }
      }
    }
    return CONCAT44(puVar3,uVar2);
  }
  uVar7 = (**(code **)(DAT_00026e6e + -0x84))();
  (**(code **)(_DAT_00000004 + -0x20a))((int)(uVar7 >> 0x20));
  return uVar7 & 0xffffffff;
}


// ==== FUN_00015c5c @ 00015c5c ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 * FUN_00015c5c(void)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  int *in_A1;
  undefined4 *puVar3;
  
  puVar2 = (undefined4 *)0x0;
  if ((in_A1 != (int *)0x0) && (puVar2 = (undefined4 *)FUN_000158ec(), puVar2 != (undefined4 *)0x0))
  {
    *puVar2 = 0;
    puVar3 = puVar2;
    while (*in_A1 != 0) {
      uVar1 = (*_thunk_FUN_00020560)();
      *puVar3 = uVar1;
      puVar3 = puVar3 + 1;
      in_A1 = in_A1 + 1;
    }
  }
  return puVar2;
}


// ==== FUN_00015ca6 @ 00015ca6 ====

uint6 FUN_00015ca6(void)

{
  short in_D0w;
  uint in_D1;
  short sVar1;
  ushort uVar2;
  uint6 uVar3;
  
  sVar1 = (short)in_D1;
  uVar2 = 0;
  if (in_D0w < 0) {
    uVar2 = 0x10;
    in_D0w = -in_D0w;
  }
  if (sVar1 < 0) {
    uVar2 = uVar2 | 8;
    sVar1 = -sVar1;
  }
  if (sVar1 <= in_D0w) {
    if (in_D0w == sVar1) {
      if (in_D0w != 0) {
                    /* WARNING: Could not recover jumptable at 0x00015d0a. Too many branches */
                    /* WARNING: Treating indirect jump as call */
        uVar3 = (**(code **)(&DAT_0002571e + (short)uVar2))();
        return uVar3;
      }
      return (uint6)in_D1;
    }
    uVar2 = uVar2 | 4;
  }
                    /* WARNING: Could not recover jumptable at 0x00015cf6. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  uVar3 = (**(code **)(&DAT_0002571e + (short)uVar2))();
  return uVar3;
}


// ==== FUN_00015d3e @ 00015d3e ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00015d3e(undefined4 param_1)

{
  (*_thunk_FUN_0001feb4)(param_1);
  return;
}


// ==== FUN_00015d4c @ 00015d4c ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00015d4c(undefined4 param_1)

{
  (*_thunk_FUN_0001feca)(param_1);
  return;
}


// ==== FUN_00015d50 @ 00015d50 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00015d50(void)

{
  (*_thunk_FUN_0001feca)();
  return;
}


// ==== FUN_00015d5a @ 00015d5a ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined2 FUN_00015d5a(void)

{
  return _DAT_00dff006;
}


// ==== FUN_00015d62 @ 00015d62 ====

void FUN_00015d62(void)

{
  return;
}


// ==== FUN_00015e1a @ 00015e1a ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00015e1a(undefined4 param_1)

{
  undefined4 uVar1;
  
  DAT_00026bb0 = (*_thunk_FUN_00022b30)(param_1,0x3ed);
  if (DAT_00026bb0 == 0) {
    uVar1 = (*_thunk_FUN_00022b06)();
    (*_thunk_FUN_00021dce)(s_Couldn_t_OPEN_file__error___ld_00015e6a,uVar1);
    uVar1 = FUN_00016e96(0);
  }
  else {
    FUN_00015ec2(&LAB_00015d7c,DAT_00026bb0);
    (*_thunk_FUN_00022ab2)(DAT_00026bb0);
    uVar1 = 1;
  }
  return uVar1;
}


// ==== FUN_00015e8a @ 00015e8a ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

bool FUN_00015e8a(undefined4 param_1)

{
  bool bVar1;
  
  DAT_00026bb0 = (*_thunk_FUN_00022b30)(param_1,0x3ee);
  bVar1 = DAT_00026bb0 != 0;
  if (bVar1) {
    FUN_00015ec2(&LAB_00015dde,DAT_00026bb0);
    (*_thunk_FUN_00022ab2)(DAT_00026bb0);
  }
  return bVar1;
}


// ==== FUN_00015ec2 @ 00015ec2 ====

void FUN_00015ec2(code *param_1,undefined4 param_2)

{
  undefined2 *local_e;
  short local_a;
  
  (*param_1)(param_2,&DAT_00024bfe,0x84a);
  (*param_1)(param_2,&DAT_00025316,2);
  (*param_1)(param_2,&DAT_00024578,DAT_00025316);
  DAT_00024580 = DAT_00025316 << 2;
  DAT_0002457c = DAT_00024578 + DAT_00025316;
  local_e = &DAT_000253b0;
  local_a = 0;
  do {
    if ((local_e[2] != 0) && (local_e[9] != 0)) {
      (*param_1)(param_2,local_e + 3,local_e[5] * 0xe);
    }
    local_e = local_e + 0xf;
    local_a = local_a + 1;
  } while (local_a < 5);
  FUN_00015d62();
  (*param_1)(param_2,&DAT_00025454,DAT_000252d5 * 0xe);
  (*param_1)(param_2,&DAT_00025450,DAT_00025314 << 3);
  (*param_1)(param_2,&DAT_0002544c,(short)DAT_000252d6 << 4);
  (*param_1)(param_2,&DAT_00025448,(short)DAT_000252d7 << 4);
  return;
}


// ==== FUN_00016032 @ 00016032 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00016032(undefined4 param_1)

{
  (*_thunk_FUN_00022ec4)(DAT_00026e6a,2);
  (*_thunk_FUN_00022e92)
            (DAT_00026e6a,(int)param_1._0_2_,(int)param_1._2_2_,param_1._0_2_ + 7,param_1._2_2_ + 7)
  ;
  (*_thunk_FUN_00022ec4)(DAT_00026e6a,1);
  return;
}


// ==== FUN_00016086 @ 00016086 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined2 FUN_00016086(undefined1 *param_1,undefined4 param_2,undefined4 param_3)

{
  undefined2 uVar2;
  short sVar3;
  short sVar4;
  uint uVar1;
  ushort uVar5;
  undefined2 uVar6;
  undefined2 local_68;
  short local_5e;
  undefined1 uStack_5b;
  short local_5a;
  short local_58;
  short local_56;
  undefined1 auStack_54 [80];
  
  local_68 = 0;
  (*_thunk_FUN_00022ea4)((short)DAT_00026e6a,6);
  (*_thunk_FUN_00022eb4)((short)DAT_00026e6a,0);
  (*_thunk_FUN_00022ec4)((short)DAT_00026e6a,1);
  local_5a = 0;
  do {
    auStack_54[local_5a] = 0x20;
    local_5a = local_5a + 1;
  } while (local_5a < 0x50);
  local_58 = -1;
  local_56 = 0;
  while( true ) {
    while( true ) {
      while( true ) {
        if (((local_56 != local_58) && (local_5e == 0)) && (-1 < local_58)) {
          FUN_00016032(param_3._0_2_);
        }
        uVar6 = SUB42(param_1,0);
        if (local_5e != 0) {
          (*_thunk_FUN_00022e78)
                    ((short)DAT_00026e6a,param_2._2_2_,
                     param_3._0_2_ + *(short *)(DAT_00026e6a + 0x3e));
          uVar2 = (*_thunk_FUN_00021e12)(uVar6);
          (*_thunk_FUN_00022ed4)((short)DAT_00026e6a,uVar6,uVar2);
          sVar3 = (*_thunk_FUN_00021e12)(uVar6);
          if (sVar3 <= param_2._0_2_) {
            sVar3 = param_2._0_2_ + 1;
            sVar4 = (*_thunk_FUN_00021e12)(uVar6);
            auStack_54[(short)(sVar3 - sVar4)] = 0;
            sVar3 = (*_thunk_FUN_00021e12)(uVar6,param_3._0_2_ + *(short *)(DAT_00026e6a + 0x3e));
            (*_thunk_FUN_00022e78)((short)DAT_00026e6a,param_2._2_2_ + sVar3 * 8);
            uVar2 = (*_thunk_FUN_00021e12)((short)auStack_54);
            (*_thunk_FUN_00022ed4)((short)DAT_00026e6a,(short)auStack_54,uVar2);
            sVar3 = param_2._0_2_ + 1;
            sVar4 = (*_thunk_FUN_00021e12)(uVar6);
            auStack_54[(short)(sVar3 - sVar4)] = 0x20;
          }
        }
        if ((local_5e != 0) || (local_56 != local_58)) {
          FUN_00016032(param_3._0_2_);
        }
        local_58 = local_56;
        local_5e = 0;
        while (sVar3 = (*_thunk_FUN_000207d8)(), sVar3 == 0) {
          (*_thunk_FUN_00022eee)();
          sVar3 = (*_thunk_FUN_0002044c)();
          if (sVar3 != 0) goto LAB_00016444;
          sVar3 = (*_thunk_FUN_00020454)();
          if (sVar3 != 0) {
            if (DAT_00027692 == 1) {
              FUN_00018228();
              local_68 = 0xffff;
              goto LAB_00016444;
            }
            if (DAT_00027692 == 5) {
              FUN_00018228();
              local_68 = 1;
              goto LAB_00016444;
            }
          }
        }
        uVar1 = (*_thunk_FUN_000207e4)();
        uVar5 = (ushort)uVar1 & 0xff;
        sVar3 = (*_thunk_FUN_00020700)((ushort)uVar1);
        if ((uVar5 == 0x44) || (uVar5 == 0x43)) goto LAB_00016444;
        if (uVar5 != 0x4f) break;
        local_56 = local_56 + -1;
        if ((local_56 < 0) || ((uVar1 & 0x30000) != 0)) {
          local_56 = 0;
        }
      }
      if (uVar5 != 0x4e) break;
      local_56 = local_56 + 1;
      sVar3 = (*_thunk_FUN_00021e12)(uVar6);
      if ((sVar3 < local_56) || ((uVar1 & 0x30000) != 0)) {
        local_56 = (*_thunk_FUN_00021e12)(uVar6);
      }
    }
    if (uVar5 == 0x4c) break;
    if (uVar5 == 0x4d) {
      local_68 = 1;
LAB_00016444:
      FUN_00016032(param_3._0_2_);
      return local_68;
    }
    if (uVar5 == 0x46) {
LAB_00016340:
      if (param_1[local_56] != '\0') {
        local_5a = local_56;
        do {
          param_1[local_5a] = param_1[(short)(local_5a + 1)];
          local_5a = local_5a + 1;
          local_5e = 1;
        } while (param_1[local_5a] != '\0');
      }
    }
    else if (uVar5 == 0x41) {
      if (local_56 != 0) {
        local_56 = local_56 + -1;
        goto LAB_00016340;
      }
    }
    else {
      sVar4 = (*_thunk_FUN_00020700)(uVar5);
      if ((sVar4 == 0x78) && ((uVar1 & 0x800000) != 0)) {
        local_56 = 0;
        *param_1 = 0;
        local_5e = 1;
      }
      else if ((sVar3 != 0) && (local_56 < param_2._0_2_)) {
        for (local_5a = param_2._0_2_; local_56 < local_5a; local_5a = local_5a + -1) {
          param_1[local_5a] = param_1[(short)(local_5a + -1)];
        }
        param_1[param_2._0_2_] = 0;
        uStack_5b = (undefined1)sVar3;
        param_1[local_56] = uStack_5b;
        local_56 = local_56 + 1;
        if (param_2._0_2_ < local_56) {
          local_56 = param_2._0_2_;
        }
        local_5e = 1;
      }
    }
  }
  local_68 = 0xffff;
  goto LAB_00016444;
}


// ==== FUN_0001653c @ 0001653c ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Restarted to delay deadcode elimination for space: ram */

void FUN_0001653c(void)

{
  undefined4 uVar1;
  int extraout_A0;
  
  DAT_00027bb8 = (&PTR_s_shapes_dash_shp_00025858)[DAT_000252e0];
  uVar1 = (*_thunk_FUN_00015bc6)(DAT_000252e0 * 4);
  DAT_0002458a = extraout_A0;
  if (extraout_A0 == 0) {
                    /* WARNING: Could not recover jumptable at 0x00016568. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (*_thunk_FUN_0001020e)();
    return;
  }
  DAT_00026da2 = uVar1;
  DAT_00027694 = FUN_00015d3e((&PTR_s_shapes_iff_dash_00025848)[DAT_000252e0]);
  return;
}


// ==== FUN_00016592 @ 00016592 ====

void FUN_00016592(char *param_1)

{
  for (; *param_1 != '\0'; param_1 = param_1 + 1) {
    if ((*param_1 == ':') || (*param_1 == '/')) {
      *param_1 = ' ';
    }
  }
  return;
}


// ==== FUN_000165c4 @ 000165c4 ====

void FUN_000165c4(void)

{
  return;
}


// ==== FUN_000165cc @ 000165cc ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_000165cc(undefined4 param_1)

{
  (*_thunk_FUN_0002085e)(param_1);
  return;
}


// ==== FUN_0001660e @ 0001660e ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0001660e(void)

{
  DAT_00027bc2 = 0;
  _DAT_00dff080 = *(undefined4 *)(DAT_00026e72 + 0x26);
  (*_thunk_FUN_00022eee)();
  FUN_000124dc(&DAT_00026c96);
  FUN_000124dc(&DAT_00027964);
  FUN_000124dc(&DAT_00027ba8);
  FUN_000124dc(&DAT_0002794a);
  FUN_000124dc(&DAT_00027958);
  FUN_000124dc(&DAT_00027bb4);
  FUN_000124dc(&DAT_00027bb0);
  return;
}


// ==== FUN_00016670 @ 00016670 ====

void FUN_00016670(void)

{
  DAT_00026c96 = FUN_000165cc(0x90);
  DAT_00027964 = FUN_000165cc(0x10);
  FUN_00019968(DAT_00026c96,0x90);
  FUN_000199bc(DAT_00026c96,0x1000200);
  FUN_000199bc(DAT_00026c96,0x1800000);
  FUN_0001a06c(DAT_00026c96);
  DAT_00027ba8 = FUN_000165cc(0x159a0);
  if (DAT_00027ba8 == 0) {
    FUN_00016e72();
  }
  DAT_00027bac = DAT_00027ba8 + 0xacd0;
  DAT_0002794a = FUN_000165cc(1000);
  if (DAT_0002794a == 0) {
    FUN_00016e72();
  }
  DAT_00027958 = FUN_000165cc(1000);
  if (DAT_00027958 == 0) {
    FUN_00016e72();
  }
  DAT_00027bb4 = FUN_000165cc(1000);
  if (DAT_00027bb4 == 0) {
    FUN_00016e72();
  }
  DAT_00027bb0 = FUN_000165cc(0x444);
  if (DAT_00027bb0 == 0) {
    FUN_00016e72();
  }
  FUN_00019968(DAT_0002794a,1000);
  FUN_00019968(DAT_00027958,1000);
  FUN_00019968(DAT_00027bb4,1000);
  DAT_00027730 = &DAT_00027968;
  DAT_000277dc = &DAT_000279a8;
  DAT_00027888 = &DAT_000279e8;
  DAT_00027934 = &DAT_00027a28;
  DAT_0002727e = &DAT_00027a68;
  DAT_00027734 = &DAT_00027aa8;
  DAT_000277e0 = &DAT_00027ae8;
  DAT_00027948 = 0;
  DAT_00027956 = 0x14;
  DAT_0002794e = &DAT_00027698;
  DAT_0002795c = &DAT_00027744;
  DAT_00027952 = DAT_00027ba8;
  DAT_00027960 = DAT_00027bac;
  FUN_0001a9fc(DAT_00026c96);
  DAT_00027bbe = DAT_00026c96 + 4;
  DAT_00027bc2 = *(undefined4 *)(DAT_00026e72 + 0x26);
  DAT_00027bc6 = DAT_00026c96 + 4;
  return;
}


// ==== FUN_000167f2 @ 000167f2 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_000167f2(int param_1,int *param_2,undefined4 param_3,undefined4 param_4)

{
  short sVar1;
  short local_a;
  short local_8;
  
  *(undefined2 *)(param_1 + 0xa6) = 0;
  *(undefined2 *)(param_1 + 0xa4) = 0;
  *(short *)(param_1 + 0xa8) = param_3._0_2_;
  *(short *)(param_1 + 0xaa) = param_3._2_2_;
  *(undefined2 *)(param_1 + 0x94) = 0;
  *(short *)(param_1 + 0xa2) = param_3._2_2_;
  *(ushort *)(param_1 + 0xa0) = (param_3._0_2_ + 0xfU & 0xfff0) >> 3;
  sVar1 = *(short *)(param_1 + 0xa0);
  for (local_8 = 0; local_8 < param_4._0_2_; local_8 = local_8 + 1) {
    *(int *)(param_1 + local_8 * 4 + 0xc) = *param_2;
    *param_2 = (int)(short)(sVar1 * param_3._2_2_) + *param_2;
  }
  (*_thunk_FUN_00022e5a)(param_1 + 4,(int)param_4._0_2_,(int)param_3._0_2_,(int)param_3._2_2_);
  (*_thunk_FUN_00022e6c)(param_1 + 0x2c);
  *(int *)(param_1 + 0x30) = param_1 + 4;
  if (*(int *)(param_1 + 0x98) != 0) {
    local_a = 0;
    do {
      *(undefined2 *)(*(int *)(param_1 + 0x98) + local_a * 2) = 0;
      local_a = local_a + 1;
    } while (local_a < 0x20);
  }
  if (*(int *)(param_1 + 0x9c) != 0) {
    local_a = 0;
    do {
      *(undefined2 *)(*(int *)(param_1 + 0x9c) + local_a * 2) = 0;
      local_a = local_a + 1;
    } while (local_a < 0x20);
  }
  return;
}


// ==== FUN_0001692c @ 0001692c ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0001692c(int param_1)

{
  undefined4 local_c;
  undefined4 *local_8;
  
  local_c = *(undefined4 *)(param_1 + 10);
  (*_thunk_FUN_00022e2e)((short)local_c,0xacd0,1);
  for (local_8 = *(undefined4 **)(param_1 + 6); local_8 != (undefined4 *)0x0;
      local_8 = (undefined4 *)*local_8) {
    FUN_000167f2((short)local_8,(short)&local_c);
  }
  FUN_0001a0d4(param_1);
  return;
}


// ==== FUN_000169a4 @ 000169a4 ====

void FUN_000169a4(void)

{
  FUN_0001a9fc(DAT_00026c96);
  *DAT_00026d70 = 0;
  *(undefined2 *)(DAT_00026d70 + 0x2a) = 0x140;
  *(undefined2 *)((int)DAT_00026d70 + 0xaa) = 200;
  *(undefined1 *)((int)DAT_00026d70 + 9) = 4;
  FUN_0001692c(DAT_00026d7c);
  return;
}


// ==== FUN_00016a16 @ 00016a16 ====

void FUN_00016a16(int param_1)

{
  undefined4 *puVar1;
  
  puVar1 = *(undefined4 **)(param_1 + 6);
  *puVar1 = 0;
  *(undefined2 *)(puVar1 + 0x2a) = 0x280;
  *(undefined2 *)((int)puVar1 + 0xaa) = 200;
  *(undefined1 *)((int)puVar1 + 9) = 1;
  FUN_0001692c(param_1);
  *(undefined2 *)((int)puVar1 + 0xa6) = 5;
  return;
}


// ==== FUN_00016a60 @ 00016a60 ====

void FUN_00016a60(void)

{
  FUN_0001a9fc(DAT_00026c96);
  FUN_00016a16(&DAT_00027948);
  FUN_00016a16(&DAT_00027956);
  DAT_0002773a = 0xe6;
  DAT_000277e6 = 0xe6;
  FUN_00016fc4(&DAT_00027948);
  return;
}


// ==== FUN_00016a98 @ 00016a98 ====

void FUN_00016a98(int param_1)

{
  undefined4 *puVar1;
  
  puVar1 = *(undefined4 **)(param_1 + 6);
  *puVar1 = 0;
  *(undefined2 *)(puVar1 + 0x2a) = 0x140;
  *(undefined2 *)((int)puVar1 + 0xaa) = 200;
  *(undefined1 *)((int)puVar1 + 9) = 5;
  FUN_0001692c(param_1);
  return;
}


// ==== FUN_00016ad8 @ 00016ad8 ====

void FUN_00016ad8(void)

{
  FUN_0001a9fc(DAT_00026c96);
  FUN_00016a98(&DAT_00027948);
  FUN_00016a98(&DAT_00027956);
  FUN_00016fc4(&DAT_00027948);
  return;
}


// ==== FUN_00016b04 @ 00016b04 ====

void FUN_00016b04(void)

{
  FUN_0001a9fc(DAT_00026c96);
  DAT_00027698 = 0;
  DAT_00027740 = 0x280;
  DAT_00027742 = 0x93;
  DAT_000276a1 = 3;
  FUN_0001692c(&DAT_00027948);
  DAT_00027744 = 0;
  DAT_000277ec = 0x280;
  DAT_000277ee = 0x93;
  DAT_0002774d = 3;
  FUN_0001692c(&DAT_00027956);
  FUN_00016fc4(&DAT_00027948);
  return;
}


// ==== FUN_00016b60 @ 00016b60 ====

void FUN_00016b60(void)

{
  FUN_0001a9fc(DAT_00026c96);
  DAT_00027698 = 0;
  DAT_00027740 = 0x280;
  DAT_00027742 = 200;
  DAT_000276a1 = 2;
  FUN_0001692c(&DAT_00027948);
  DAT_00027744 = 0;
  DAT_000277ec = 0x280;
  DAT_000277ee = 200;
  DAT_0002774d = 2;
  FUN_0001692c(&DAT_00027956);
  FUN_00016fc4(&DAT_00027948);
  return;
}


// ==== FUN_00016bbc @ 00016bbc ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00016bbc(void)

{
  (*_thunk_FUN_00022e2e)(DAT_00027bb0,0x444,1);
  return;
}


// ==== FUN_00016bd8 @ 00016bd8 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00016bd8(void)

{
  DAT_000271e6 = 0;
  DAT_0002728e = 0x2a0;
  DAT_00027290 = 0xd;
  DAT_00027286 = 0x50;
  DAT_00027288 = 0xd;
  DAT_0002728c = 0xc9;
  DAT_000271ef = 1;
  DAT_000271f2 = DAT_00027bb0;
  (*_thunk_FUN_00022e5a)(&DAT_000271ea,1,0x2a0,0xd);
  (*_thunk_FUN_00022e6c)(&DAT_00027212);
  DAT_00027216 = &DAT_000271ea;
  return;
}


// ==== FUN_00016c38 @ 00016c38 ====

void FUN_00016c38(int param_1)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  
  puVar2 = *(undefined4 **)(param_1 + 6);
  puVar1 = (undefined4 *)*puVar2;
  *(undefined2 *)(puVar2 + 0x2a) = 0x140;
  *(undefined2 *)((int)puVar2 + 0xaa) = 0xa2;
  *(undefined1 *)((int)puVar2 + 9) = 5;
  *(undefined2 *)((int)puVar2 + 0x92) = 0x96;
  *puVar1 = 0;
  *(undefined2 *)(puVar1 + 0x2a) = 0x280;
  *(undefined2 *)((int)puVar1 + 0xaa) = 0x25;
  *(undefined1 *)((int)puVar1 + 9) = 4;
  FUN_0001692c(param_1);
  *puVar1 = &DAT_000271e6;
  *(undefined2 *)((int)puVar1 + 0xa6) = 0xa3;
  *(undefined2 *)(puVar2 + 0x25) = 1;
  return;
}


// ==== FUN_00016cc6 @ 00016cc6 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00016cc6(void)

{
  (*_thunk_FUN_00022e2e)(DAT_00027bb0,0x444,1);
  FUN_00016bd8();
  DAT_00027698 = &DAT_000277f0;
  DAT_00027744 = &DAT_0002789c;
  DAT_000277f0 = &DAT_000271e6;
  DAT_0002789c = &DAT_000271e6;
  DAT_000271e6 = 0;
  FUN_00016c38(&DAT_00027948);
  FUN_00016c38(&DAT_00027956);
  FUN_0001a0d4(&DAT_00027948);
  FUN_0001a0d4(&DAT_00027956);
  return;
}


// ==== FUN_00016d32 @ 00016d32 ====

void FUN_00016d32(void)

{
  DAT_00027698 = &DAT_000277f0;
  DAT_00027744 = &DAT_0002789c;
  FUN_00016c38(DAT_00026d7c);
  FUN_0001a9ca(DAT_00026d80,DAT_00026d7c);
  FUN_0001a0d4(DAT_00026d7c);
  FUN_000187ba(*(undefined4 *)(DAT_00026d7c + 2));
  return;
}


// ==== FUN_00016d7a @ 00016d7a ====

void FUN_00016d7a(void)

{
  FUN_0001a9fc(DAT_00026c96);
  DAT_00027698 = &DAT_000277f0;
  DAT_00027740 = 0x140;
  DAT_00027742 = 0x4b;
  DAT_000276a1 = 5;
  DAT_000277f0 = 0;
  DAT_00027898 = 0x280;
  DAT_0002789a = 0x91;
  DAT_000277f9 = 4;
  FUN_0001692c(&DAT_00027948);
  DAT_00027896 = 0x4c;
  FUN_0001a0d4(&DAT_00027948);
  return;
}


// ==== FUN_00016dd6 @ 00016dd6 ====

void FUN_00016dd6(int *param_1,int param_2)

{
  byte bVar1;
  byte *pbVar2;
  byte *pbVar3;
  int *piVar4;
  int *piVar5;
  short local_e;
  byte *local_c;
  
  piVar4 = param_1;
  piVar5 = param_1;
  if (param_1 != (int *)0x0) {
    do {
      param_1 = piVar5;
      if (*param_1 == 0x434d4150) break;
      piVar5 = param_1 + 1;
    } while (param_1 + 1 < piVar4 + 1000);
    local_c = (byte *)(param_1 + 2);
    local_e = 0;
    do {
      pbVar2 = local_c + 1;
      bVar1 = *local_c;
      pbVar3 = local_c + 2;
      local_c = local_c + 3;
      *(ushort *)(param_2 + local_e * 2) =
           (ushort)(*pbVar3 >> 4) | (ushort)*pbVar2 | (ushort)bVar1 << 4;
      local_e = local_e + 1;
    } while (local_e < 0x20);
  }
  return;
}


// ==== FUN_00016e72 @ 00016e72 ====

void FUN_00016e72(void)

{
  FUN_00016e96(s_Not_enough_memory__00016e82);
  return;
}


// ==== FUN_00016e96 @ 00016e96 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00016e96(int param_1)

{
  if (param_1 != 0) {
    (*_thunk_FUN_00021ef4)(param_1);
  }
  (*_thunk_FUN_0001020e)();
  return;
}


// ==== FUN_00016eb2 @ 00016eb2 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00016eb2(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  
  iVar1 = FUN_00015d3e(param_1);
  if (iVar1 != 0) {
    FUN_0001a548(iVar1,param_3);
    (*_thunk_FUN_0002090a)(iVar1);
    FUN_0001a0d4(param_2);
  }
  return;
}


// ==== FUN_00016eee @ 00016eee ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00016eee(undefined4 param_1)

{
  short sVar1;
  short local_6;
  
  (*_thunk_FUN_00022eee)();
  for (local_6 = 1; local_6 < param_1._0_2_; local_6 = local_6 + 1) {
    sVar1 = (*_thunk_FUN_0002044c)();
    if (sVar1 != 0) break;
    (*_thunk_FUN_00022eee)();
  }
  (*_thunk_FUN_0002044c)();
  return;
}


// ==== FUN_00016f20 @ 00016f20 ====

void FUN_00016f20(undefined2 *param_1)

{
  FUN_0001aa0e(*(undefined4 *)(param_1 + 1));
  DAT_00026d80 = param_1;
  if (param_1 == &DAT_00027948) {
    DAT_00026d7c = &DAT_00027956;
  }
  else {
    DAT_00026d7c = &DAT_00027948;
  }
  DAT_00026d78 = *(int *)(param_1 + 3);
  DAT_00026d74 = DAT_00026d78 + 0x2c;
  DAT_00026d88 = DAT_00026d78 + 4;
  DAT_00026d70 = *(int *)(DAT_00026d7c + 3);
  DAT_00026d6c = DAT_00026d70 + 0x2c;
  DAT_00026d84 = DAT_00026d70 + 4;
  DAT_00027bbe = *(int *)(param_1 + 1) + 4;
  DAT_00027bc2 = *(undefined4 *)(DAT_00026e72 + 0x26);
  DAT_00027bc6 = *(int *)(DAT_00026d7c + 1) + 4;
  return;
}


// ==== FUN_00016fc4 @ 00016fc4 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00016fc4(undefined4 param_1)

{
  FUN_00016f20(param_1);
  (*_thunk_FUN_0001aa3e)();
  return;
}


// ==== FUN_00016ff6 @ 00016ff6 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

ushort FUN_00016ff6(undefined4 param_1,undefined4 param_2)

{
  ushort uVar1;
  
  if (param_1._0_2_ != 0xf) {
    uVar1 = (*_thunk_FUN_000223cc)();
    param_2._0_2_ =
         (uVar1 & 0xf00) +
         ((short)(((param_2._0_2_ & 0xf0) - (param_1._2_2_ & 0xf0)) * param_1._0_2_) / 0xf & 0xf0U)
         + ((short)(((param_2._0_2_ & 0xf) - (param_1._2_2_ & 0xf)) * param_1._0_2_) / 0xf & 0xfU) +
           param_1._2_2_;
  }
  return param_2._0_2_;
}


// ==== FUN_00017084 @ 00017084 ====

void FUN_00017084(void)

{
  undefined4 uVar1;
  undefined2 uVar2;
  undefined2 auStackY_1008a [32];
  undefined2 auStackY_1004a [32732];
  undefined2 auStack_8a [32];
  undefined2 auStack_4a [32];
  short local_a;
  short local_8;
  short local_6;
  
  local_8 = 1 << (*(byte *)(DAT_00026d78 + 9) & 0x3f);
  for (local_6 = 0; local_6 < local_8; local_6 = local_6 + 1) {
    auStack_4a[local_6] = *(undefined2 *)(*(int *)(DAT_00026d78 + 0x98) + local_6 * 2);
  }
  if (*(int *)(DAT_00026d78 + 0x9c) != 0) {
    for (local_6 = 0; local_6 < local_8; local_6 = local_6 + 1) {
      auStack_8a[local_6] = *(undefined2 *)(*(int *)(DAT_00026d78 + 0x9c) + local_6 * 2);
    }
  }
  local_a = 0;
  do {
    for (local_6 = 0; local_6 < local_8; local_6 = local_6 + 1) {
      uVar2 = FUN_00016ff6();
      *(undefined2 *)(*(int *)(DAT_00026d78 + 0x98) + local_6 * 2) = uVar2;
      if (*(int *)(DAT_00026d78 + 0x9c) != 0) {
        uVar2 = FUN_00016ff6();
        *(undefined2 *)(*(int *)(DAT_00026d78 + 0x9c) + local_6 * 2) = uVar2;
      }
    }
    uVar1 = *(undefined4 *)(DAT_00026d80 + 2);
    *(undefined4 *)(DAT_00026d80 + 2) = DAT_00027bb4;
    DAT_00027bb4 = uVar1;
    FUN_0001a0d4(DAT_00026d80);
    FUN_00016f20(DAT_00026d80);
    local_a = local_a + 1;
  } while (local_a < 0x10);
  return;
}


// ==== FUN_000171f2 @ 000171f2 ====

void FUN_000171f2(void)

{
  undefined4 uVar1;
  undefined2 uVar2;
  undefined2 auStackY_100ca [32];
  undefined2 auStackY_1008a [32];
  undefined2 auStackY_1004a [32700];
  undefined2 auStack_ca [32];
  undefined2 auStack_8a [32];
  undefined2 auStack_4a [32];
  short local_a;
  short local_8;
  short local_6;
  
  local_8 = 1 << (*(byte *)((int)DAT_00026d78 + 9) & 0x3f);
  for (local_6 = 0; local_6 < local_8; local_6 = local_6 + 1) {
    auStack_4a[local_6] = *(undefined2 *)(DAT_00026d78[0x26] + local_6 * 2);
    auStack_8a[local_6] = *(undefined2 *)(*(int *)(*DAT_00026d78 + 0x98) + local_6 * 2);
    if (DAT_00026d78[0x27] != 0) {
      auStack_ca[local_6] = *(undefined2 *)(DAT_00026d78[0x27] + local_6 * 2);
    }
  }
  local_a = 0;
  do {
    for (local_6 = 0; local_6 < local_8; local_6 = local_6 + 1) {
      uVar2 = FUN_00016ff6();
      *(undefined2 *)(DAT_00026d78[0x26] + local_6 * 2) = uVar2;
      uVar2 = FUN_00016ff6();
      *(undefined2 *)(*(int *)(*DAT_00026d78 + 0x98) + local_6 * 2) = uVar2;
      if (DAT_00026d78[0x27] != 0) {
        uVar2 = FUN_00016ff6();
        *(undefined2 *)(DAT_00026d78[0x27] + local_6 * 2) = uVar2;
      }
    }
    uVar1 = *(undefined4 *)(DAT_00026d80 + 2);
    *(undefined4 *)(DAT_00026d80 + 2) = DAT_00027bb4;
    DAT_00027bb4 = uVar1;
    FUN_0001a0d4(DAT_00026d80);
    FUN_00016f20(DAT_00026d80);
    local_a = local_a + 1;
  } while (local_a < 0x10);
  return;
}


// ==== FUN_000173b0 @ 000173b0 ====

void FUN_000173b0(void)

{
  undefined2 auStack_46 [32];
  short local_6;
  
  local_6 = 0;
  do {
    auStack_46[local_6] = 0;
    local_6 = local_6 + 1;
  } while (local_6 < 0x20);
  FUN_00017084(auStack_46);
  return;
}


// ==== FUN_000173e6 @ 000173e6 ====

void FUN_000173e6(void)

{
  undefined2 auStack_46 [32];
  short local_6;
  
  local_6 = 0;
  do {
    auStack_46[local_6] = 0;
    local_6 = local_6 + 1;
  } while (local_6 < 0x20);
  FUN_000171f2(auStack_46,auStack_46);
  return;
}


// ==== FUN_00017422 @ 00017422 ====

void FUN_00017422(undefined4 param_1,int param_2)

{
  undefined2 local_6;
  
  FUN_00016eb2(param_1,DAT_00026d7c,DAT_00026d70);
  local_6 = 0;
  do {
    if (param_2 != 0) {
      *(undefined2 *)(param_2 + local_6 * 2) =
           *(undefined2 *)(*(int *)(DAT_00026d70 + 0x98) + local_6 * 2);
    }
    *(undefined2 *)(*(int *)(DAT_00026d70 + 0x98) + local_6 * 2) = 0;
    local_6 = local_6 + 1;
  } while (local_6 < 0x20);
  FUN_0001a0d4(DAT_00026d7c);
  return;
}


// ==== FUN_00017d4e @ 00017d4e ====

void FUN_00017d4e(undefined4 param_1)

{
  undefined4 uVar1;
  short local_6;
  
  uVar1 = *(undefined4 *)(DAT_00026d80 + 2);
  *(undefined4 *)(DAT_00026d80 + 2) = DAT_00027bb4;
  DAT_00027bb4 = uVar1;
  FUN_0001a0d4(&DAT_00027948);
  for (local_6 = 0; local_6 < param_1._0_2_; local_6 = local_6 + 1) {
    FUN_00019a9c((short)DAT_0002794a,local_6 + 5);
    FUN_000199bc((short)DAT_0002794a,CONCAT22(0x182,local_6 * 0x111));
    if (local_6 == param_1._2_2_) {
      FUN_00019a08((short)DAT_0002794a);
    }
  }
  if ((param_1._0_2_ <= param_1._2_2_) && (param_1._2_2_ <= (short)(0xc4 - param_1._0_2_))) {
    FUN_00019a9c((short)DAT_0002794a,param_1._2_2_ + 5);
    FUN_00019a08((short)DAT_0002794a);
  }
  while (local_6 = param_1._0_2_ + -1, -1 < local_6) {
    FUN_00019a9c((short)DAT_0002794a,0xc9 - local_6);
    FUN_000199bc((short)DAT_0002794a,CONCAT22(0x182,local_6 * 0x111));
    param_1._0_2_ = local_6;
    if ((short)(0xc4 - local_6) == param_1._2_2_) {
      FUN_00019a08((short)DAT_0002794a);
    }
  }
  return;
}


// ==== FUN_00017e80 @ 00017e80 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00017e80(void)

{
  short sVar1;
  short unaff_D4w;
  short sVar2;
  short local_14;
  short local_c;
  short local_a;
  undefined *local_8;
  
  FUN_00016a60();
  (*_thunk_FUN_00021246)((short)DAT_00026d74);
  sVar2 = 0xd2;
  local_8 = PTR_s_A_Time_of_Fury_000258dc;
  local_a = 0;
  local_c = 0;
  do {
    if (local_c % 0xe == 0) {
      sVar1 = 0xc4;
      if (local_c != 0) {
        sVar1 = -0xe;
      }
      (*_thunk_FUN_00022ea4)((short)DAT_00026d74,0);
      (*_thunk_FUN_00022e92)(DAT_00026d74,0,(int)sVar1,0x27f,sVar1 + 0xb);
      (*_thunk_FUN_00022ea4)((short)DAT_00026d74,1);
      if (local_a < 0x35) {
        (*_thunk_FUN_00022e78)(DAT_00026d74,0,sVar1);
        sVar1 = (*_thunk_FUN_00021e12)((short)local_8);
        if (local_8[(short)(sVar1 + 1)] == '\0') {
          FUN_00015a8c(local_8,sVar1,0);
        }
        else {
          FUN_00015a8c(local_8,sVar1,0x267);
        }
        sVar1 = (*_thunk_FUN_00021e12)((short)local_8);
        local_8 = local_8 + (short)(sVar1 + 1);
        unaff_D4w = 0xd2;
      }
      local_a = local_a + 1;
    }
    FUN_00016eee();
    FUN_00017d4e(sVar2);
    FUN_00016f20(0x7948);
    FUN_00016eee();
    unaff_D4w = unaff_D4w + -1;
    local_c = local_c + 1;
    *(int *)(DAT_00026d88 + 8) = *(int *)(DAT_00026d88 + 8) + 0x50;
    sVar2 = sVar2 + -1;
    if (sVar2 < 1) {
      sVar2 = 0xd2;
      *(undefined4 *)(DAT_00026d88 + 8) = DAT_00027ba8;
      local_c = 0;
    }
    if (unaff_D4w < 0) break;
    sVar1 = (*_thunk_FUN_0002044c)();
  } while (sVar1 == 0);
  local_14 = 0x10;
  do {
    FUN_00017d4e(sVar2);
    FUN_00016f20(0x7948);
    FUN_00016eee();
    local_14 = local_14 + -1;
  } while (0 < local_14);
  return;
}


// ==== FUN_00018022 @ 00018022 ====

void FUN_00018022(void)

{
  short sVar1;
  undefined1 auStack_44 [64];
  
  FUN_000123dc(0x8122,2);
  FUN_00017e80();
  FUN_000123dc(0x812b,1);
  FUN_00016ad8();
  FUN_00017422(0x8134,(short)auStack_44);
  FUN_00016fc4((short)DAT_00026d7c);
  FUN_00017084(0x589c);
  sVar1 = FUN_00016eee();
  if (sVar1 == 0) {
    FUN_00017084((short)auStack_44);
    FUN_00017422(0x8146,(short)auStack_44);
    sVar1 = FUN_00016eee();
    if (sVar1 == 0) {
      FUN_000173b0();
      FUN_00016fc4((short)DAT_00026d7c);
      FUN_00017084((short)auStack_44);
      FUN_00017422(0x8158,(short)auStack_44);
      sVar1 = FUN_00016eee();
      if (sVar1 == 0) {
        FUN_000173b0();
        FUN_00016fc4((short)DAT_00026d7c);
        FUN_00017084((short)auStack_44);
        FUN_00016eee();
      }
    }
  }
  FUN_000173b0();
  return;
}


// ==== FUN_0001816c @ 0001816c ====

void FUN_0001816c(void)

{
  FUN_00016e96(s_User_requested_abort__0001817e);
  return;
}


// ==== FUN_00018194 @ 00018194 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00018194(undefined4 param_1)

{
  short sVar1;
  short local_a;
  
  local_a = 0;
  while( true ) {
    sVar1 = (*_thunk_FUN_000207d8)();
    if (sVar1 != 0) {
      sVar1 = (*_thunk_FUN_000207e4)();
      if (sVar1 == 0x4c) {
        return 0xffffffff;
      }
      if (sVar1 == 0x4d) {
        return 1;
      }
      if ((sVar1 == 0x44) || (sVar1 == 0x43)) {
        return 0;
      }
    }
    sVar1 = (*_thunk_FUN_00020454)();
    if (sVar1 == 1) {
      return 0xffffffff;
    }
    if (sVar1 == 5) break;
    sVar1 = (*_thunk_FUN_0002044c)();
    if (sVar1 != 0) {
      return 0;
    }
    (*_thunk_FUN_00022eee)();
    local_a = local_a + 1;
    if ((param_1._0_2_ != 0) && (0x708 < local_a)) {
      return 1000;
    }
  }
  return 1;
}


// ==== FUN_00018228 @ 00018228 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00018228(void)

{
  short sVar1;
  undefined2 local_6;
  
  local_6 = 0;
  do {
    (*_thunk_FUN_00022eee)();
    sVar1 = (*_thunk_FUN_000207d8)();
    if (sVar1 == 0) {
      sVar1 = (*_thunk_FUN_0002044c)();
      if (sVar1 == 0) {
        sVar1 = (*_thunk_FUN_00020454)();
        if (sVar1 == 0) goto LAB_0001824c;
      }
    }
    else {
LAB_0001824c:
      local_6 = 1000;
    }
    local_6 = local_6 + 1;
    if (8 < local_6) {
      return;
    }
  } while( true );
}


// ==== FUN_00018262 @ 00018262 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined * FUN_00018262(void)

{
  int iVar1;
  short sVar2;
  int local_50;
  short local_4a;
  undefined1 auStack_48 [64];
  undefined4 local_8;
  
  DAT_00026bb4._0_2_ = 0;
  FUN_000123dc(0x84f0,4);
  FUN_00016ad8();
  DAT_00026c90 = 0;
  FUN_00017422(0x84f9,(short)auStack_48);
  local_8 = FUN_00015d4c(0x850b);
  local_4a = DAT_00026bb4._0_2_;
  (*_thunk_FUN_00021246)((short)DAT_00026d6c);
  (*_thunk_FUN_00021280)();
  local_50 = (*_thunk_FUN_0002050e)((short)local_8);
  (*_thunk_FUN_00020e0a)((short)local_50,*(undefined2 *)(local_50 + 10));
  FUN_00016fc4((short)DAT_00026d7c);
  FUN_00017084((short)auStack_48);
  FUN_0001a9ca((short)DAT_00026d80,(short)DAT_00026d7c);
LAB_00018302:
  do {
    sVar2 = FUN_00018194();
    if (sVar2 != 0) {
      if (sVar2 != 1000) {
        DAT_00026bb4._0_2_ = sVar2 + DAT_00026bb4._0_2_;
        if (DAT_00026bb4._0_2_ < 0) {
          DAT_00026bb4._0_2_ = 7;
        }
        if (7 < DAT_00026bb4._0_2_) {
          DAT_00026bb4._0_2_ = 0;
        }
        if (DAT_00026bb4._0_2_ != local_4a) {
          (*_thunk_FUN_00021246)((short)DAT_00026d6c);
          (*_thunk_FUN_00020e0a)((short)local_50,*(undefined2 *)(local_50 + 10));
          local_50 = (*_thunk_FUN_0002050e)((short)local_8);
          (*_thunk_FUN_00020e0a)((short)local_50,*(undefined2 *)(local_50 + 10));
          FUN_00016fc4((short)DAT_00026d7c);
          FUN_0001a9ca((short)DAT_00026d80,(short)DAT_00026d7c);
          local_4a = DAT_00026bb4._0_2_;
          FUN_00018228();
        }
        goto LAB_00018302;
      }
      DAT_00026c9c = 1;
    }
    if (DAT_00026bb4._0_2_ != 7) {
      (*_thunk_FUN_0002090a)((short)local_8);
      FUN_000173b0();
      if ((DAT_00026c9c == 0) && (DAT_00026ed6 != 0)) {
        DAT_00026c9e = (*_thunk_FUN_00020848)(5000);
        DAT_00026c9c = 2;
      }
      if (DAT_00026c9c == 1) {
        DAT_00026c9e = FUN_00015d3e(0x8521);
      }
      DAT_00026ca2 = 0;
      if (DAT_00026c9e == 0) {
        DAT_00026c9c = 0;
      }
      if (DAT_00026c9c != 0) {
        (*_thunk_FUN_00015d5a)();
        (*_thunk_FUN_000203da)();
      }
      DAT_000254a8 = DAT_00026bb4._0_2_;
      DAT_0002530e = DAT_00026bb4._0_2_;
      if (DAT_00026c9c == 1) {
        DAT_0002530e = (short)*(char *)(DAT_00026c9e + DAT_00026ca2);
        DAT_00026ca2 = DAT_00026ca2 + 1;
      }
      if (DAT_00026c9c == 2) {
        iVar1 = (int)DAT_00026ca2;
        DAT_00026ca2 = DAT_00026ca2 + 1;
        *(undefined1 *)(DAT_00026c9e + iVar1) = (undefined1)DAT_0002530e;
      }
      DAT_00025310 = 1;
      goto LAB_000184d6;
    }
    sVar2 = FUN_00018b96();
    if (sVar2 == 0) {
      DAT_00026c90 = 1;
      (*_thunk_FUN_0002090a)((short)local_8);
      FUN_000173b0();
LAB_000184d6:
      FUN_00012470();
      return (&PTR_s_maps_a_map_000235a0)[DAT_000254a8];
    }
    FUN_00016a98((short)DAT_00026d7c);
    FUN_0001a9ca((short)DAT_00026d80,(short)DAT_00026d7c);
    FUN_0001a0d4((short)DAT_00026d7c);
  } while( true );
}


// ==== FUN_0001852a @ 0001852a ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0001852a(void)

{
  if ((DAT_00026c9c == 2) && (DAT_00026ed6 != 0)) {
    *(undefined1 *)(DAT_00026c9e + DAT_00026ca2) = 0xff;
    (*_thunk_FUN_0001fe50)(DAT_00026ed6,DAT_00026c9e,5000);
  }
  FUN_000124dc(&DAT_00026c9e);
  DAT_00026c9c = 0;
  return;
}


// ==== FUN_00018570 @ 00018570 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00018570(undefined4 param_1)

{
  short sVar1;
  
  sVar1 = (*_thunk_FUN_00021e12)(param_1);
  FUN_00015910(param_1,(int)sVar1);
  return;
}


// ==== FUN_00018590 @ 00018590 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00018590(void)

{
  int iVar1;
  uint uVar2;
  char cVar4;
  short sVar3;
  undefined2 uVar5;
  short local_84;
  undefined1 auStack_76 [50];
  undefined1 auStack_44 [64];
  
  FUN_00016b04();
  iVar1 = (*_thunk_FUN_000204f4)((short)DAT_00024582,0x6e6b);
  uVar5 = (undefined2)DAT_00026d6c;
  (*_thunk_FUN_00021246)(uVar5);
  (*_thunk_FUN_00021280)();
  (*_thunk_FUN_00021eca)(0x587c,(short)auStack_44);
  (*_thunk_FUN_00020cc4)((short)iVar1,0,0x65 - (*(ushort *)(iVar1 + 2) >> 1));
  (*_thunk_FUN_00022e78)(uVar5,0x128,0x3d);
  FUN_00018570((short)(&PTR_s_Midshipman_00025860)[DAT_0002530e]);
  (*_thunk_FUN_00022e78)(uVar5,0x154,0x49);
  (*_thunk_FUN_000215d8)((short)auStack_76,0x8764);
  FUN_00018570((short)auStack_76);
  (*_thunk_FUN_00022e78)(uVar5,0x154,0x77);
  (*_thunk_FUN_000215d8)((short)auStack_76,0x8767);
  FUN_00018570((short)auStack_76);
  (*_thunk_FUN_00022e78)(uVar5,0x154,0x83);
  (*_thunk_FUN_000215d8)((short)auStack_76,0x876a);
  FUN_00018570((short)auStack_76);
  FUN_00016fc4((short)DAT_00026d7c);
  FUN_00017084((short)auStack_44);
  (*_thunk_FUN_00022eee)();
  local_84 = 1;
  do {
    if ((0xef < local_84) || (sVar3 = (*_thunk_FUN_0002044c)(), sVar3 != 0)) {
      FUN_000173b0();
      return 0;
    }
    (*_thunk_FUN_00022eee)();
    sVar3 = (*_thunk_FUN_000207d8)();
    if (sVar3 != 0) {
      uVar2 = (*_thunk_FUN_000207e4)();
      if (((uVar2 & 0x80000) != 0) && (cVar4 = (*_thunk_FUN_00020700)((short)uVar2), cVar4 == 'r'))
      {
        FUN_000173b0();
        return 1;
      }
    }
    local_84 = local_84 + 1;
  } while( true );
}


// ==== FUN_0001876e @ 0001876e ====

void FUN_0001876e(void)

{
  undefined2 uVar1;
  
  uVar1 = *(undefined2 *)(*(int *)(DAT_00026d7c + 2) + 2);
  *(undefined2 *)(*(int *)(DAT_00026d7c + 2) + 2) = DAT_00027bbc;
  FUN_00019a9c(*(undefined4 *)(DAT_00026d7c + 2));
  *(undefined2 *)(*(int *)(DAT_00026d7c + 2) + 2) = uVar1;
  return;
}


// ==== FUN_000187ba @ 000187ba ====

void FUN_000187ba(undefined4 param_1)

{
  short local_6;
  
  local_6 = 0;
  do {
    FUN_00019a9c(param_1,local_6 + 0xc9);
    FUN_000199bc(param_1,*(undefined2 *)(&DAT_000258e4 + local_6 * 2));
    local_6 = local_6 + 1;
  } while (local_6 < 10);
  return;
}


// ==== FUN_00018806 @ 00018806 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00018806(void)

{
  short local_6;
  
  FUN_0001a9fc(DAT_00026c96);
  FUN_00016cc6();
  FUN_0001a548(DAT_00027694,*DAT_00026d70);
  (*_thunk_FUN_0002090a)(DAT_00027694);
  local_6 = 0;
  do {
    *(undefined2 *)(&DAT_000279e8 + local_6 * 2) =
         *(undefined2 *)(*(int *)(*DAT_00026d70 + 0x98) + local_6 * 2);
    *(undefined2 *)(&DAT_00027a28 + local_6 * 2) =
         *(undefined2 *)(*(int *)(*DAT_00026d70 + 0x98) + local_6 * 2);
    local_6 = local_6 + 1;
  } while (local_6 < 0x20);
  DAT_00025706 = 0;
  DAT_00025518 = 0;
  FUN_00015d3e((&PTR_s_shapes_wingspalette_00025840)[DAT_000252e0]);
  FUN_00016dd6(DAT_00027bca,DAT_00026d70[0x26]);
  (*_thunk_FUN_0002090a)(DAT_00027bca);
  FUN_00015d3e((&PTR_s_shapes_ocean_palette_00025850)[DAT_000252e0]);
  FUN_00016dd6(DAT_00027bca,DAT_00026d70[0x27]);
  (*_thunk_FUN_0002090a)(DAT_00027bca);
  *(undefined2 *)(*(int *)(*(int *)*DAT_00026d70 + 0x98) + 2) = 0x777;
  FUN_0001a9fc(DAT_00026c96);
  FUN_0001a9ca(DAT_00026d7c,DAT_00026d80);
  FUN_0001a0d4(DAT_00026d7c);
  FUN_0001a0d4(DAT_00026d80);
  FUN_000187ba(*(undefined4 *)(DAT_00026d7c + 2));
  FUN_000187ba(*(undefined4 *)(DAT_00026d80 + 2));
  FUN_0001d1ea();
  return;
}


// ==== FUN_00018958 @ 00018958 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00018958(void)

{
  short sVar1;
  short local_6;
  
  local_6 = 0;
  do {
    (*_thunk_FUN_00022ec4)(DAT_00026d74,0);
    sVar1 = (*_thunk_FUN_00021e12)(&DAT_00027bce + local_6 * 0x1d);
    (*_thunk_FUN_00022e78)
              (DAT_00026d74,0x2d,(ushort)(*(short *)(DAT_00026d74 + 0x3e) + local_6 * 0x10) + 0x3d);
    (*_thunk_FUN_00022ed4)(DAT_00026d74,&DAT_00027bce + local_6 * 0x1d,(int)sVar1);
    if (sVar1 < 0x1c) {
      (*_thunk_FUN_00022ed4)(DAT_00026d74,PTR_s__000258e0,(int)(short)(0x1c - sVar1));
    }
    local_6 = local_6 + 1;
  } while (local_6 < 6);
  return;
}


// ==== FUN_00018a06 @ 00018a06 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00018a06(void)

{
  undefined2 extraout_D0u;
  undefined2 extraout_D0u_00;
  undefined2 uVar1;
  int iVar2;
  undefined4 uVar3;
  short sVar4;
  int local_c;
  short local_6;
  
  local_c = 0;
  local_6 = 0;
  do {
    (&DAT_00027bce)[local_6 * 0x1d] = 0;
    local_6 = local_6 + 1;
  } while (local_6 < 6);
  FUN_00018958(0);
  iVar2 = (*_thunk_FUN_00020848)(0x104);
  if (iVar2 == 0) {
    uVar3 = 0;
  }
  else {
    local_c = (*_thunk_FUN_00022b1e)(0,0xfffe);
    if (local_c == 0) {
      uVar3 = 0;
    }
    else {
      uVar3 = (*_thunk_FUN_00022ade)((short)local_c,(short)iVar2);
      if ((short)uVar3 != 0) {
        local_6 = 0;
        while ((local_6 < 6 &&
               (sVar4 = (*_thunk_FUN_00022aec)((short)local_c,(short)iVar2), sVar4 != 0))) {
          sVar4 = (*_thunk_FUN_00021e82)();
          if (((sVar4 == 0x77) &&
              (((sVar4 = (*_thunk_FUN_00021e82)(), sVar4 == 0x6f &&
                (sVar4 = (*_thunk_FUN_00021e82)(), sVar4 == 0x66)) &&
               (*(char *)(iVar2 + 0xb) == '.')))) && (*(char *)(iVar2 + 0xc) != '\0')) {
            (*_thunk_FUN_000222d2)(local_6 * 0x1d + 0x7bce,(short)iVar2 + 0xc);
            (*_thunk_FUN_00021e02)(local_6 * 0x1d + 0x7c7c,local_6 * 0x1d + 0x7bce);
            local_6 = local_6 + 1;
          }
        }
        uVar3 = FUN_00018958();
      }
    }
  }
  uVar1 = (undefined2)((uint)uVar3 >> 0x10);
  if (local_c != 0) {
    (*_thunk_FUN_00022b54)((short)local_c);
    uVar1 = extraout_D0u;
  }
  if (iVar2 != 0) {
    (*_thunk_FUN_0002090a)((short)iVar2);
    uVar1 = extraout_D0u_00;
  }
  return CONCAT22(uVar1,local_6);
}


// ==== FUN_00018b96 @ 00018b96 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined2 FUN_00018b96(undefined4 param_1)

{
  undefined2 uVar1;
  short sVar2;
  short local_10c;
  undefined1 local_108 [50];
  undefined2 local_d6;
  undefined4 local_d4;
  undefined4 local_d0;
  short *local_ca;
  undefined **local_c6;
  short local_c2;
  short asStack_c0 [29];
  short asStack_86 [29];
  short local_4c;
  short local_4a;
  short local_48;
  short local_46;
  undefined1 auStack_44 [64];
  
  FUN_000169a4();
  local_c6 = &PTR_DAT_000258f8;
  local_ca = &DAT_00025918;
  local_d0 = DAT_00026d6c;
  local_d4 = DAT_00026d7c;
  (*_thunk_FUN_00021246)((short)DAT_00026d6c);
  (*_thunk_FUN_00021280)();
  (*_thunk_FUN_00022ea4)((short)local_d0,0x28f);
  (*_thunk_FUN_00022ec4)((short)local_d0,0);
  for (; *local_c6 != (undefined *)0x0; local_c6 = local_c6 + 2) {
    (*_thunk_FUN_00022e78)
              ((short)local_d0,*(undefined2 *)(local_c6 + 1),*(undefined2 *)((int)local_c6 + 6));
    uVar1 = (*_thunk_FUN_00021e12)((short)*local_c6);
    (*_thunk_FUN_00022ed4)((short)local_d0,(short)*local_c6,uVar1);
  }
  (*_thunk_FUN_00022e78)((short)local_d0,0x55,0x13);
  if (param_1._0_2_ == 0) {
    (*_thunk_FUN_00022ed4)((short)local_d0,0x9254,4);
  }
  else {
    (*_thunk_FUN_00022ed4)((short)local_d0,0x9259,4);
  }
  for (; (*local_ca != 0 && (local_ca[3] != 0)); local_ca = local_ca + 4) {
    (*_thunk_FUN_00022e78)((short)local_d0,*local_ca,local_ca[1]);
    (*_thunk_FUN_00022e48)((short)local_d0,local_ca[2],local_ca[1]);
    (*_thunk_FUN_00022e48)((short)local_d0,local_ca[2],local_ca[3]);
    (*_thunk_FUN_00022e48)((short)local_d0,*local_ca,local_ca[3]);
    (*_thunk_FUN_00022e48)((short)local_d0,*local_ca,local_ca[1]);
  }
  (*_thunk_FUN_00021eca)(0x5960,(short)auStack_44);
  FUN_00016fc4((short)local_d4);
  FUN_00017084((short)auStack_44);
  local_4c = 0;
  do {
    (&DAT_00027bce)[local_4c * 0x1d] = 0;
    local_4c = local_4c + 1;
  } while (local_4c < 6);
  local_48 = 0;
  do {
    asStack_86[local_48] = 0x2c;
    asStack_c0[local_48] = local_48 * 0x10 + 0x3d;
    local_48 = local_48 + 1;
  } while (local_48 < 6);
  local_48 = 0;
  local_46 = 0;
  (*_thunk_FUN_00021246)((short)DAT_00026d74);
  (*_thunk_FUN_00021280)();
  FUN_000134a4();
  local_c2 = FUN_00018a06();
  if ((local_c2 == 0) && (param_1._0_2_ == 0)) {
    local_48 = 7;
  }
  do {
    uVar1 = (undefined2)DAT_00026d74;
    if (local_48 < 6) {
      if (param_1._0_2_ == 0) {
        (*_thunk_FUN_00022ec4)(uVar1,2);
        (*_thunk_FUN_00022e92)
                  (DAT_00026d74,asStack_86[local_48],asStack_c0[local_48] + -1,
                   asStack_86[local_48] + 0xed,asStack_c0[local_48] + 7);
        (*_thunk_FUN_00022ec4)((short)DAT_00026d74,1);
        local_4a = FUN_00018194();
        FUN_00018228();
      }
      else {
        (*_thunk_FUN_00022ec4)(uVar1,0);
        (*_thunk_FUN_00022ea4)((short)DAT_00026d74,0x28f);
        local_4a = (*_thunk_FUN_00016086)(local_48 * 0x1d + 0x7bce,asStack_86[local_48],1);
      }
    }
    else {
      (*_thunk_FUN_00022ec4)(uVar1,2);
      if (local_48 == 6) {
        (*_thunk_FUN_00022e92)(DAT_00026d74,0x2d,0xb9,0x91,0xc5);
      }
      else if (local_48 == 7) {
        (*_thunk_FUN_00022e92)(DAT_00026d74,0xcf,0xb9,0x11b,0xc5);
      }
      (*_thunk_FUN_00022ec4)((short)DAT_00026d74,1);
      local_4a = FUN_00018194();
      FUN_00018228();
    }
    sVar2 = local_48;
    local_46 = local_48;
    do {
      local_48 = local_4a + local_48;
      if (local_48 < 0) {
        local_48 = 7;
      }
      if (7 < local_48) {
        local_48 = 0;
      }
    } while (((param_1._0_2_ == 0) && (local_48 < 6)) && ((&DAT_00027bce)[local_48 * 0x1d] == '\0'))
    ;
    if (local_48 != sVar2) {
      (*_thunk_FUN_00022ec4)((short)DAT_00026d74,2);
      if (local_46 < 6) {
        if (param_1._0_2_ == 0) {
          (*_thunk_FUN_00022e92)
                    (DAT_00026d74,asStack_86[local_46],asStack_c0[local_46] + -1,
                     asStack_86[local_46] + 0xed,asStack_c0[local_46] + 7);
        }
      }
      else if (local_46 == 6) {
        (*_thunk_FUN_00022e92)(DAT_00026d74,0x2d,0xb9,0x91,0xc5);
      }
      else {
        (*_thunk_FUN_00022e92)(DAT_00026d74,0xcf,0xb9,0x11b,0xc5);
      }
      (*_thunk_FUN_00022ec4)((short)DAT_00026d74,1);
    }
  } while (local_4a != 0);
  FUN_00016592(local_48 * 0x1d + 0x7bce);
  if ((local_48 < 6) && ((&DAT_00027bce)[local_48 * 0x1d] != '\0')) {
    (*_thunk_FUN_00022ea4)((short)DAT_00026d74,1);
    local_108[0] = 0;
    (*_thunk_FUN_000222a8)((short)local_108,0x925e);
    (*_thunk_FUN_000222a8)((short)local_108,local_48 * 0x1d + 0x7bce);
    (*_thunk_FUN_00022e78)((short)DAT_00026d74,10,10);
    if (param_1._0_2_ == 0) {
      (*_thunk_FUN_00022ed4)((short)DAT_00026d74,0x9263,0xf);
      FUN_00012470();
      FUN_00012bbe();
      FUN_00015e1a((short)local_108);
    }
    else {
      (*_thunk_FUN_00022ed4)((short)DAT_00026d74,0x9273,0xe);
      FUN_00015e8a((short)local_108);
      for (local_10c = 0; local_10c < local_c2; local_10c = local_10c + 1) {
        if (((&DAT_00027c7c)[local_10c * 0x1d] != '\0') &&
           (sVar2 = (*_thunk_FUN_00021e9a)(local_10c * 0x1d + 0x7bce,local_10c * 0x1d + 0x7c7c),
           sVar2 != 0)) {
          local_108[0] = 0;
          (*_thunk_FUN_000222a8)((short)local_108,0x9282);
          (*_thunk_FUN_000222a8)((short)local_108,local_10c * 0x1d + 0x7c7c);
          (*_thunk_FUN_00022ace)((short)local_108);
          break;
        }
      }
      FUN_000173b0();
      FUN_00016fc4((short)DAT_00026d7c);
    }
    local_d6 = 0;
  }
  else {
    FUN_000173b0();
    if (local_48 == 6) {
      FUN_00016e96(0);
    }
    FUN_00016fc4((short)DAT_00026d7c);
    local_d6 = 0xffff;
  }
  FUN_0001344e();
  return local_d6;
}


// ==== FUN_00019288 @ 00019288 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00019288(void)

{
  (*_thunk_FUN_0001fe50)(s_highscore_000192a4,DAT_00027d2a,0x168);
  return;
}


// ==== FUN_00019320 @ 00019320 ====

void FUN_00019320(void)

{
  short sVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 auStack_2c [9];
  short local_8;
  short local_6;
  
  do {
    local_6 = 0;
    local_8 = 0;
    do {
      if (*(int *)(DAT_00027d2a + local_8 * 0x24) <
          *(int *)(DAT_00027d2a + (short)(local_8 + 1) * 0x24)) {
        sVar1 = 8;
        puVar2 = auStack_2c;
        puVar3 = (undefined4 *)(DAT_00027d2a + local_8 * 0x24);
        do {
          *puVar2 = *puVar3;
          sVar1 = sVar1 + -1;
          puVar2 = puVar2 + 1;
          puVar3 = puVar3 + 1;
        } while (sVar1 != -1);
        sVar1 = 8;
        puVar2 = (undefined4 *)(DAT_00027d2a + local_8 * 0x24);
        puVar3 = (undefined4 *)(DAT_00027d2a + (short)(local_8 + 1) * 0x24);
        do {
          *puVar2 = *puVar3;
          sVar1 = sVar1 + -1;
          puVar2 = puVar2 + 1;
          puVar3 = puVar3 + 1;
        } while (sVar1 != -1);
        sVar1 = 8;
        puVar2 = (undefined4 *)(DAT_00027d2a + (short)(local_8 + 1) * 0x24);
        puVar3 = auStack_2c;
        do {
          *puVar2 = *puVar3;
          sVar1 = sVar1 + -1;
          puVar2 = puVar2 + 1;
          puVar3 = puVar3 + 1;
        } while (sVar1 != -1);
        local_6 = 1;
      }
      local_8 = local_8 + 1;
    } while (local_8 < 9);
  } while (local_6 != 0);
  return;
}


// ==== FUN_000193cc @ 000193cc ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_000193cc(void)

{
  int iVar1;
  undefined2 local_6;
  
  iVar1 = (*_thunk_FUN_00022b30)(0x945a,0x3ed);
  if (iVar1 == 0) {
    local_6 = 0;
    do {
      *(undefined4 *)(DAT_00027d2a + local_6 * 0x24) = 0;
      *(undefined2 *)(DAT_00027d2a + local_6 * 0x24 + 4) = 0;
      (*_thunk_FUN_000222d2)((short)DAT_00027d2a + local_6 * 0x24 + 6,0x9464);
      local_6 = local_6 + 1;
    } while (local_6 < 10);
  }
  else {
    (*_thunk_FUN_00022b42)((short)iVar1,(short)DAT_00027d2a,0x168);
    (*_thunk_FUN_00022ab2)((short)iVar1);
  }
  return;
}


// ==== FUN_00019472 @ 00019472 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00019472(void)

{
  undefined2 uVar1;
  undefined2 uVar2;
  undefined2 uVar3;
  undefined2 uVar4;
  ushort local_58;
  undefined1 auStack_55 [17];
  undefined1 auStack_44 [64];
  
  for (local_58 = 0; local_58 < 0x11; local_58 = local_58 + 1) {
    auStack_55[(short)local_58] = 0;
  }
  FUN_000193cc();
  FUN_00019320();
  if (*(int *)(DAT_00027d2a + 0x144) < DAT_0002529c) {
    FUN_000169a4();
    uVar2 = (undefined2)DAT_00026d6c;
    (*_thunk_FUN_00021246)(uVar2);
    (*_thunk_FUN_00021280)();
    (*_thunk_FUN_00022ea4)(uVar2,8);
    (*_thunk_FUN_00022ec4)(uVar2,0);
    uVar4 = 0x964e;
    uVar3 = 0x9669;
    (*_thunk_FUN_00022e78)
              (uVar2,0x34,0x53,s_in_the_hall_of_fame__00019669,s_Your_name_is_to_be_entered_0001964e
              );
    uVar1 = (*_thunk_FUN_00021e12)(uVar4);
    (*_thunk_FUN_00022ed4)(uVar2,uVar4,uVar1);
    (*_thunk_FUN_00022e78)(uVar2,0x5b,0x5c);
    uVar1 = (*_thunk_FUN_00021e12)(uVar3);
    (*_thunk_FUN_00022ed4)(uVar2,uVar3,uVar1);
    (*_thunk_FUN_00022ea4)(uVar2,2);
    (*_thunk_FUN_00022e78)(uVar2,0x50,100);
    (*_thunk_FUN_00022e48)(uVar2,0xe1,100);
    (*_thunk_FUN_00022e48)(uVar2,0xe1,0x71);
    (*_thunk_FUN_00022e48)(uVar2,0x50,0x71);
    (*_thunk_FUN_00022e48)(uVar2,0x50,100);
    (*_thunk_FUN_00021eca)(0x59ac,(short)auStack_44);
    FUN_00016fc4((short)DAT_00026d7c);
    FUN_00017084((short)auStack_44);
    (*_thunk_FUN_00016086)((short)auStack_55,0x52,10000);
    *(int *)(DAT_00027d2a + 0x144) = DAT_0002529c;
    (*_thunk_FUN_000222d2)((short)(DAT_00027d2a + 0x14a),(short)auStack_55);
    *(undefined2 *)(DAT_00027d2a + 0x148) = DAT_0002530e;
    FUN_000173b0();
    FUN_00019320();
    FUN_00019288();
  }
  return;
}


// ==== FUN_0001967e @ 0001967e ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0001967e(void)

{
  undefined1 auStack_74 [100];
  undefined4 local_10;
  short local_c;
  short local_a;
  short local_8;
  short local_6;
  
  local_10 = DAT_00026d6c;
  (*_thunk_FUN_00021246)((short)DAT_00026d6c);
  local_6 = 0;
  do {
    local_8 = 0;
    do {
      if (*(int *)(DAT_00027d2a + local_8 * 0x24) != 0) {
        local_a = *(short *)(&DAT_000259a6 + local_6 * 2) + 0xd;
        local_c = local_8 * 0xc + *(short *)(&DAT_000259a6 + local_6 * 2) + 6;
        (*_thunk_FUN_00022ea4)((short)local_10,*(undefined2 *)(&DAT_000259a0 + local_6 * 2));
        (*_thunk_FUN_00022ec4)((short)local_10,0);
        (*_thunk_FUN_00022e78)((short)local_10,local_a,local_c);
        (*_thunk_FUN_000215d8)((short)auStack_74,0x9846);
        FUN_00018570((short)auStack_74);
        (*_thunk_FUN_00022e78)((short)local_10,local_a + 0x28,local_c);
        (*_thunk_FUN_000215d8)
                  ((short)auStack_74,0x9849,(short)*(undefined4 *)(DAT_00027d2a + local_8 * 0x24));
        FUN_00018570((short)auStack_74);
        (*_thunk_FUN_00022e78)((short)local_10,local_a + 0x96,local_c);
        (*_thunk_FUN_000215d8)
                  ((short)auStack_74,0x984f,
                   (short)(&PTR_s_Midshipman_00025860)
                          [*(short *)(DAT_00027d2a + local_8 * 0x24 + 4)]);
        FUN_00018570((short)auStack_74);
        (*_thunk_FUN_00022e78)((short)local_10,local_a + 300,local_c);
        FUN_00018570((short)DAT_00027d2a + local_8 * 0x24 + 6);
      }
      local_8 = local_8 + 1;
    } while (local_8 < 10);
    local_6 = local_6 + 1;
  } while (local_6 < 3);
  return;
}


// ==== FUN_00019856 @ 00019856 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00019856(void)

{
  undefined1 auStack_21e [410];
  undefined1 auStack_84 [64];
  undefined1 auStack_44 [64];
  
  DAT_00027d2a = auStack_21e;
  FUN_000123dc(0x9928,0);
  FUN_00019472();
  FUN_00016d7a();
  DAT_00026d7c = &DAT_00027948;
  DAT_00026d70 = *DAT_0002794e;
  DAT_00026d6c = DAT_00026d70 + 0x2c;
  DAT_00026d84 = DAT_00026d70 + 4;
  FUN_00017422(0x9931,(short)auStack_84);
  (*_thunk_FUN_00021246)((short)DAT_00026d6c);
  (*_thunk_FUN_00021280)();
  FUN_0001967e();
  DAT_00026d70 = *(int *)(DAT_00026d7c + 3);
  DAT_00026d6c = DAT_00026d70 + 0x2c;
  DAT_00026d84 = DAT_00026d70 + 4;
  FUN_00017422(0x9944,(short)auStack_44);
  FUN_00016fc4((short)DAT_00026d7c);
  FUN_000171f2((short)auStack_44,(short)auStack_84);
  FUN_00016eee();
  FUN_000173e6();
  return;
}


// ==== FUN_00019958 @ 00019958 ====

void FUN_00019958(int param_1)

{
  *(undefined2 *)(param_1 + 2) = 0;
  return;
}


// ==== FUN_00019968 @ 00019968 ====

void FUN_00019968(short *param_1,int param_2)

{
  *param_1 = (short)(param_2 - 4U >> 2) + -1;
  FUN_00019958(param_1);
  return;
}


// ==== FUN_000199bc @ 000199bc ====

void FUN_000199bc(short *param_1,undefined4 param_2)

{
  short sVar1;
  
  if (param_1[1] < *param_1) {
    param_1[param_1[1] * 2 + 2] = param_2._0_2_;
    sVar1 = param_1[1];
    param_1[1] = param_1[1] + 1;
    param_1[sVar1 * 2 + 3] = param_2._2_2_;
  }
  return;
}


// ==== FUN_00019a08 @ 00019a08 ====
// decompile failed: 
Low-level Error: Cannot properly adjust input varnodes
// ==== FUN_00019a9c @ 00019a9c ====

void FUN_00019a9c(short *param_1,undefined4 param_2)

{
  short sVar1;
  
  param_2._0_2_ = (short)param_2._0_2_ / 4 << 1;
  param_2._2_2_ = param_2._2_2_ + 0x2c;
  if ((short)param_2._0_2_ < 0) {
    param_2._0_2_ = 0;
  }
  if (0xe2 < (short)param_2._0_2_) {
    param_2._0_2_ = 0xe2;
  }
  if (param_2._2_2_ < 0) {
    param_2._2_2_ = 0;
  }
  if (0x106 < param_2._2_2_) {
    param_2._2_2_ = 0x106;
  }
  if (0xff < param_2._2_2_) {
    FUN_00019a9c(param_1,0xd3);
  }
  if (param_1[1] < *param_1) {
    param_1[param_1[1] * 2 + 2] = (param_2._0_2_ & 0xfe) + param_2._2_2_ * 0x100 + 1;
    sVar1 = param_1[1];
    param_1[1] = param_1[1] + 1;
    param_1[sVar1 * 2 + 3] = -2;
  }
  return;
}


// ==== FUN_00019b5a @ 00019b5a ====

void FUN_00019b5a(short *param_1,short *param_2,undefined4 param_3,undefined4 param_4)

{
  short *psVar1;
  ushort local_6;
  
  if ((param_3._0_2_ != 0) || (param_3._2_2_ != 0)) {
    FUN_00019a9c(param_1,param_3._2_2_);
  }
  if ((short)(*param_1 - param_1[1]) < (short)param_4._0_2_) {
    param_4._0_2_ = *param_1 - param_1[1];
  }
  if (0 < (short)param_4._0_2_) {
    psVar1 = param_1 + param_1[1] * 2;
    for (local_6 = 0; local_6 < param_4._0_2_; local_6 = local_6 + 1) {
      psVar1[2] = local_6 * 2 + 0x180;
      psVar1[3] = *param_2;
      param_2 = param_2 + 1;
      psVar1 = psVar1 + 2;
    }
    param_1[1] = param_4._0_2_ + param_1[1];
  }
  return;
}


// ==== FUN_00019c0a @ 00019c0a ====

void FUN_00019c0a(undefined4 param_1,int param_2)

{
  FUN_00019b5a(param_1,*(undefined4 *)(param_2 + 0x98),*(short *)(param_2 + 0xa6) + -1);
  return;
}


// ==== FUN_00019c80 @ 00019c80 ====

void FUN_00019c80(undefined4 param_1,int param_2)

{
  undefined2 local_6;
  
  FUN_00019a9c(param_1,*(undefined2 *)(param_2 + 0x92));
  for (local_6 = 0; local_6 < (ushort)(1 << (*(byte *)(param_2 + 9) & 0x3f)); local_6 = local_6 + 1)
  {
    if (*(short *)(*(int *)(param_2 + 0x9c) + (short)local_6 * 2) !=
        *(short *)(*(int *)(param_2 + 0x98) + (short)local_6 * 2)) {
      FUN_000199bc(param_1,*(undefined2 *)(*(int *)(param_2 + 0x9c) + (short)local_6 * 2));
    }
  }
  return;
}


// ==== FUN_00019d18 @ 00019d18 ====

void FUN_00019d18(undefined2 param_1,int param_2,undefined4 param_3)

{
  bool bVar1;
  short sVar2;
  short sVar3;
  short sVar4;
  short sVar5;
  short local_1c;
  short sVar6;
  short local_18;
  ushort local_e;
  ushort local_c;
  ushort local_8;
  
  FUN_00019a9c(param_1,CONCAT22(param_3._0_2_,param_3._2_2_ + -1));
  FUN_000199bc(param_1,0x1000200);
  bVar1 = 0x3c < *(ushort *)(param_2 + 0xa0);
  if (bVar1) {
    param_3._0_2_ = (short)param_3._0_2_ >> 1;
  }
  local_18 = 0;
  sVar6 = 0;
  sVar5 = 0;
  local_1c = 0;
  if (param_3._2_2_ < -0x2a) {
    local_1c = -0x2a - param_3._2_2_;
  }
  if (0x118 < (ushort)(param_3._2_2_ + *(short *)(param_2 + 0xa2))) {
    sVar5 = 0x118 - (param_3._2_2_ + *(short *)(param_2 + 0xa2));
  }
  if (((-0x150 < (short)param_3._0_2_) && ((short)param_3._0_2_ < 0x13f)) &&
     ((ushort)(sVar5 + local_1c) < *(ushort *)(param_2 + 0xa2))) {
    sVar4 = (short)(param_3._0_2_ & 0xfff0) / 8;
    FUN_000199bc(param_1,CONCAT22(0x102,(param_3._0_2_ & 0xf) * 0x11),sVar5,0);
    if (2 < sVar4) {
      sVar6 = sVar4 + -2;
    }
    if ((short)param_3._0_2_ < -0x3f) {
      local_18 = -6 - sVar4;
    }
    sVar4 = param_3._0_2_ + local_18 * 8;
    sVar2 = local_1c + param_3._2_2_ + 0x2c;
    sVar3 = sVar6 * -8;
    sVar5 = (sVar2 + *(short *)(param_2 + 0xa2)) - (sVar5 + local_1c);
    if (bVar1) {
      local_18 = local_18 * 2;
      sVar6 = sVar6 * 2;
      local_c = (short)(sVar4 + 0x78) >> 1 & 0xfc;
      local_e = local_c + (*(short *)(param_2 + 0xa0) - (local_18 + sVar6 + 4)) * 2;
    }
    else {
      local_c = (short)(sVar4 + 0x70) >> 1 & 0xf8;
      local_e = local_c + (*(short *)(param_2 + 0xa0) - (local_18 + sVar6 + 2)) * 4;
    }
    local_e = local_e & 0xff;
    FUN_000199bc(param_1,CONCAT22(0x8e,(sVar4 + 0x81U & 0xff) + sVar2 * 0x100));
    FUN_000199bc(param_1,CONCAT22(0x90,param_3._0_2_ + 0xc1 + sVar3 + sVar5 * 0x100));
    FUN_000199bc(param_1,CONCAT22(0x92,local_c));
    FUN_000199bc(param_1,CONCAT22(0x94,local_e));
    FUN_000199bc(param_1,CONCAT22(0x108,local_18 +
                                        sVar6 + (*(short *)(param_2 + 4) -
                                                *(short *)(param_2 + 0xa0))));
    FUN_000199bc(param_1,CONCAT22(0x10a,local_18 +
                                        sVar6 + (*(short *)(param_2 + 4) -
                                                *(short *)(param_2 + 0xa0))));
    for (local_8 = 0; local_8 < *(byte *)(param_2 + 9); local_8 = local_8 + 1) {
      FUN_00019a08(param_1);
    }
    FUN_00019a9c(param_1,CONCAT22(param_3._0_2_,param_3._2_2_));
    FUN_000199bc(param_1,CONCAT22(0x100,((ushort)bVar1 * 8 + (ushort)*(byte *)(param_2 + 9)) *
                                        0x1000 + 0x200));
    if (sVar5 < 0x80) {
      FUN_00019a9c(param_1,sVar5 + -0x2c);
      FUN_000199bc(param_1,0x1000200);
    }
  }
  return;
}


// ==== FUN_0001a06c @ 0001a06c ====

void FUN_0001a06c(undefined2 param_1)

{
  undefined2 local_6;
  
  local_6 = 0;
  do {
    FUN_000199bc(param_1,CONCAT22(local_6 * 4 + 0x140,0x300));
    FUN_000199bc(param_1,CONCAT22(local_6 * 4 + 0x142,0x406));
    FUN_00019a08(param_1);
    local_6 = local_6 + 1;
  } while (local_6 < 8);
  return;
}


// ==== FUN_0001a0d4 @ 0001a0d4 ====

void FUN_0001a0d4(int param_1)

{
  int *local_8;
  
  FUN_00019958(*(undefined4 *)(param_1 + 2));
  FUN_000199bc(*(undefined4 *)(param_1 + 2),0x1000200);
  FUN_0001a06c(*(undefined4 *)(param_1 + 2));
  for (local_8 = *(int **)(param_1 + 6); local_8 != (int *)0x0; local_8 = (int *)*local_8) {
    if (*(int **)(param_1 + 6) != local_8) {
      FUN_00019a9c(*(undefined4 *)(param_1 + 2),*(short *)((int)local_8 + 0xa6) + -1);
      FUN_000199bc(*(undefined4 *)(param_1 + 2),0x1000200);
    }
    if ((*local_8 == 0) ||
       (*(short *)((int)local_8 + 0xa6) < (short)(*(short *)(*local_8 + 0xa6) + -1))) {
      FUN_00019c0a(*(undefined4 *)(param_1 + 2),local_8);
      FUN_00019d18(*(undefined4 *)(param_1 + 2),local_8,local_8[0x29]);
      if ((*(short *)(local_8 + 0x25) != 0) && (local_8[0x27] != 0)) {
        DAT_00027bbc = *(undefined2 *)(*(int *)(param_1 + 2) + 2);
        FUN_00019c80(*(undefined4 *)(param_1 + 2),local_8);
      }
    }
  }
  return;
}


// ==== FUN_0001a1f6 @ 0001a1f6 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0001a1f6(int param_1,int param_2)

{
  byte bVar1;
  short sVar2;
  short sVar3;
  byte *pbVar4;
  byte *pbVar5;
  byte *pbVar6;
  
  pbVar4 = (byte *)(param_1 + 8);
  sVar2 = (*_thunk_FUN_000223cc)();
  if (0x20 < sVar2) {
    sVar2 = 0x20;
  }
  for (sVar3 = 0; sVar3 < sVar2; sVar3 = sVar3 + 1) {
    pbVar5 = pbVar4 + 1;
    bVar1 = *pbVar4;
    pbVar6 = pbVar4 + 2;
    pbVar4 = pbVar4 + 3;
    *(ushort *)(*(int *)(param_2 + 0x98) + sVar3 * 2) =
         *pbVar5 & 0xf0 | (short)(ushort)*pbVar6 >> 4 | (bVar1 & 0xf0) << 4;
  }
  return;
}


// ==== FUN_0001a284 @ 0001a284 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0001a284(int param_1,int param_2)

{
  byte bVar1;
  short sVar2;
  short sVar3;
  byte *pbVar4;
  byte *pbVar5;
  byte *pbVar6;
  
  sVar2 = (*_thunk_FUN_000223cc)();
  if (0x20 < sVar2) {
    sVar2 = 0x20;
  }
  *(undefined2 *)(param_2 + 0x92) = *(undefined2 *)(param_1 + 8);
  *(undefined2 *)(param_2 + 0x90) = 0;
  *(undefined2 *)(param_2 + 0x94) = 1;
  pbVar4 = (byte *)(param_1 + 0xc);
  for (sVar3 = 0; sVar3 < sVar2; sVar3 = sVar3 + 1) {
    pbVar5 = pbVar4 + 1;
    bVar1 = *pbVar4;
    pbVar6 = pbVar4 + 2;
    pbVar4 = pbVar4 + 3;
    *(ushort *)(*(int *)(param_2 + 0x9c) + sVar3 * 2) =
         *pbVar5 & 0xf0 | (short)(ushort)*pbVar6 >> 4 | (bVar1 & 0xf0) << 4;
  }
  return;
}


// ==== FUN_0001a336 @ 0001a336 ====

void FUN_0001a336(int param_1,uint *param_2)

{
  *param_2 = *param_2 + *(int *)(param_1 + *param_2 + 4) + 9 & 0xfffffffe;
  return;
}


// ==== FUN_0001a362 @ 0001a362 ====

void FUN_0001a362(short *param_1,undefined4 param_2,int param_3)

{
  byte bVar1;
  undefined4 auStackY_20028 [32766];
  undefined4 auStack_28 [6];
  ushort local_10;
  short local_e;
  short local_c;
  ushort local_a;
  short local_8;
  short local_6;
  
  local_a = (ushort)(*param_1 + 7U) >> 3;
  if ((ushort)param_1[1] < *(ushort *)(param_3 + 0xaa)) {
    local_e = param_1[1];
  }
  else {
    local_e = *(short *)(param_3 + 0xaa);
  }
  if (*(byte *)(param_1 + 4) < *(byte *)(param_3 + 9)) {
    bVar1 = *(byte *)(param_1 + 4);
  }
  else {
    bVar1 = *(byte *)(param_3 + 9);
  }
  local_10 = (ushort)bVar1;
  for (local_c = 0; local_c < (short)local_10; local_c = local_c + 1) {
    auStack_28[local_c] = *(undefined4 *)(param_3 + local_c * 4 + 0xc);
  }
  FUN_0001a74c((short)param_3);
  for (local_6 = 0; local_6 < local_e; local_6 = local_6 + 1) {
    for (local_8 = 0; local_8 < (short)local_10; local_8 = local_8 + 1) {
      FUN_000203e8((short)&param_2,(short)auStack_28 + local_8 * 4);
    }
  }
  return;
}


// ==== FUN_0001a452 @ 0001a452 ====

void FUN_0001a452(int param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  int local_18;
  int local_c;
  int local_8;
  
  local_8 = 0;
  local_18 = 0;
  local_c = 0xc;
  iVar1 = *(int *)(param_1 + 4);
  while (local_c < iVar1 + 8) {
    iVar2 = *(int *)(param_1 + local_c);
    if (iVar2 == 0x424d4844) {
      local_8 = local_c + param_1 + 8;
    }
    else if (iVar2 == 0x424f4459) {
      local_18 = local_c + param_1 + 8;
    }
    else if (iVar2 == 0x434d4150) {
      FUN_0001a1f6(local_c + param_1,param_2);
    }
    else if (iVar2 == 0x434d5032) {
      FUN_0001a284(local_c + param_1,param_2);
    }
    FUN_0001a336(param_1,&local_c);
    if ((39999 < local_c) || (local_c < 1)) break;
  }
  if ((local_8 != 0) && (local_18 != 0)) {
    FUN_0001a362(local_8,local_18,param_2);
  }
  return;
}


// ==== FUN_0001a548 @ 0001a548 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0001a548(int *param_1,int param_2)

{
  if ((param_1 == (int *)0x0) || (param_2 == 0)) {
    (*_thunk_FUN_00021dce)(s_____Error___null_pointer_passed_t_0001a5b0);
  }
  else if ((*param_1 == 0x464f524d) && (param_1[2] == 0x494c424d)) {
    FUN_0001a452(param_1,param_2);
  }
  return;
}


// ==== FUN_0001a60e @ 0001a60e ====

void FUN_0001a60e(short *param_1,int param_2,int param_3,undefined4 param_4)

{
  short *psVar1;
  short local_e;
  short local_c;
  short local_a;
  short *local_8;
  
  for (local_a = 0; local_a < param_4._0_2_; local_a = local_a + 1) {
    local_c = 0;
    psVar1 = param_1;
    for (local_e = 0; local_8 = psVar1 + 2, local_e < param_1[1]; local_e = local_e + 1) {
      if ((short)(local_a * 2 + 0x180) == *local_8) {
        if (local_c == 0) {
          psVar1[3] = *(short *)(param_3 + local_a * 2);
        }
        local_c = local_c + 1;
      }
      psVar1 = local_8;
    }
    *(undefined2 *)(*(int *)(param_2 + 0x98) + local_a * 2) = *(undefined2 *)(param_3 + local_a * 2)
    ;
  }
  return;
}


// ==== FUN_0001a6ac @ 0001a6ac ====

void FUN_0001a6ac(short *param_1,int param_2,int param_3,undefined4 param_4)

{
  short *psVar1;
  short local_e;
  short local_c;
  short local_a;
  short *local_8;
  
  for (local_a = 0; local_a < param_4._0_2_; local_a = local_a + 1) {
    local_c = 0;
    psVar1 = param_1;
    for (local_e = 0; local_8 = psVar1 + 2, local_e < param_1[1]; local_e = local_e + 1) {
      if ((short)(local_a * 2 + 0x180) == *local_8) {
        if (local_c == 1) {
          psVar1[3] = *(short *)(param_3 + local_a * 2);
        }
        local_c = local_c + 1;
      }
      psVar1 = local_8;
    }
    *(undefined2 *)(*(int *)(param_2 + 0x9c) + local_a * 2) = *(undefined2 *)(param_3 + local_a * 2)
    ;
  }
  return;
}


// ==== FUN_0001a74c @ 0001a74c ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0001a74c(int param_1)

{
  ushort local_a;
  
  for (local_a = 0; local_a < *(byte *)(param_1 + 9); local_a = local_a + 1) {
    (*_thunk_FUN_00022e2e)
              (*(undefined4 *)((short *)(param_1 + 4) + (short)local_a * 2 + 4),
               *(short *)(param_1 + 6) * *(short *)(param_1 + 4),1);
  }
  return;
}


// ==== FUN_0001a834 @ 0001a834 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0001a834(int param_1,int param_2)

{
  undefined4 *local_c;
  undefined4 *local_8;
  
  if ((param_1 != 0) && (param_2 != 0)) {
    local_8 = *(undefined4 **)(param_1 + 6);
    for (local_c = *(undefined4 **)(param_2 + 6);
        (local_8 != (undefined4 *)0x0 && (local_c != (undefined4 *)0x0));
        local_c = (undefined4 *)*local_c) {
      (*_thunk_FUN_00022e0c)
                (local_8 + 1,0,0,local_c + 1,0,0,(uint)*(ushort *)(local_8 + 1) << 3,
                 *(undefined2 *)((int)local_8 + 6),0xcc,0xffffffff,0);
      local_8 = (undefined4 *)*local_8;
    }
  }
  return;
}


// ==== FUN_0001a8c4 @ 0001a8c4 ====

void FUN_0001a8c4(int param_1,int param_2)

{
  undefined4 *local_c;
  undefined4 *local_8;
  
  if ((param_1 != 0) && (param_2 != 0)) {
    local_8 = *(undefined4 **)(param_1 + 6);
    for (local_c = *(undefined4 **)(param_2 + 6);
        (local_8 != (undefined4 *)0x0 && (local_c != (undefined4 *)0x0));
        local_c = (undefined4 *)*local_c) {
      *(undefined2 *)(local_c + 0x24) = *(undefined2 *)(local_8 + 0x24);
      *(undefined2 *)((int)local_c + 0x92) = *(undefined2 *)((int)local_8 + 0x92);
      *(undefined2 *)(local_c + 0x25) = *(undefined2 *)(local_8 + 0x25);
      *(undefined2 *)((int)local_c + 0x96) = *(undefined2 *)((int)local_8 + 0x96);
      if ((local_8[0x26] != 0) && (local_c[0x26] != 0)) {
        FUN_0001a60e(*(undefined4 *)(param_2 + 2),local_c,local_8[0x26]);
      }
      if ((local_8[0x27] != 0) && (local_c[0x27] != 0)) {
        FUN_0001a6ac(*(undefined4 *)(param_2 + 2),local_c,local_8[0x27]);
      }
      local_8 = (undefined4 *)*local_8;
    }
  }
  return;
}


// ==== FUN_0001a9ca @ 0001a9ca ====

void FUN_0001a9ca(int param_1,int param_2)

{
  if ((param_1 != 0) && (param_2 != 0)) {
    FUN_0001a834(param_1,param_2);
    FUN_0001a8c4(param_1,param_2);
  }
  return;
}


// ==== FUN_0001a9fc @ 0001a9fc ====

void FUN_0001a9fc(undefined4 param_1)

{
  FUN_0001aa0e(param_1);
  FUN_0001aa3e();
  return;
}


// ==== FUN_0001aa0e @ 0001aa0e ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0001aa0e(int param_1)

{
  DAT_00027d2e = param_1;
  *(undefined4 *)(param_1 + 4 + (int)(short)(*(short *)(param_1 + 2) << 2)) = 0xfffffffe;
  _DAT_00dff080 = param_1 + 4;
  DAT_0002550e = 0;
  return;
}


// ==== FUN_0001aa32 @ 0001aa32 ====

/* WARNING: Removing unreachable block (ram,0x0001aa3c) */

void FUN_0001aa32(void)

{
                    /* WARNING: Do nothing block with infinite loop */
  do {
  } while( true );
}


// ==== FUN_0001aa3e @ 0001aa3e ====

void FUN_0001aa3e(void)

{
  do {
  } while (DAT_0002550e == '\0');
  DAT_0002550e = 0;
  return;
}


// ==== FUN_0001aa50 @ 0001aa50 ====

void FUN_0001aa50(void)

{
  DAT_00027d32 = 1;
  DAT_00027d34 = 0;
  return;
}


// ==== FUN_0001aa6e @ 0001aa6e ====

undefined2 FUN_0001aa6e(void)

{
  short local_8;
  undefined2 local_6;
  
  local_6 = 1;
  if (*(short *)(DAT_00027d3c + 0xc) == 0) {
    DAT_00027d40 = &DAT_0002517a;
    for (local_8 = 0; local_8 < 4; local_8 = local_8 + 1) {
      if ((((*DAT_00027d40 == 2) && (DAT_00027d40[1] == 1)) && (DAT_00027d40[2] == 3)) &&
         ((0xc < DAT_00027d40[0xb] && (DAT_00027d40[0xb] < 0xe)))) {
        local_6 = 0;
      }
      DAT_00027d40 = DAT_00027d40 + 0x1a;
    }
  }
  return local_6;
}


// ==== FUN_0001aaea @ 0001aaea ====

short FUN_0001aaea(void)

{
  short local_6;
  
  local_6 = 0xb;
  if (((DAT_0002535e == 0) || (*(short *)(DAT_00027d3c + 0xc) == 1)) ||
     (*(short *)(DAT_00027d3c + 0xc) == 0xb)) {
    local_6 = *(short *)(&DAT_000259fc + (uint)DAT_000254e2 * 2);
    if (DAT_0002535a != 0) {
      local_6 = *(short *)(&DAT_00025a12 + (uint)DAT_000254e2 * 2) + local_6;
    }
  }
  else if (DAT_0002535e < 6) {
    local_6 = (&DAT_00025a50)[DAT_0002535e];
  }
  else if (0x13 < DAT_0002535e) {
    local_6 = (&DAT_00025a50)[(short)(0x19 - DAT_0002535e)];
  }
  return local_6;
}


// ==== FUN_0001ab80 @ 0001ab80 ====

void FUN_0001ab80(int param_1)

{
  short sVar1;
  
  sVar1 = FUN_0001aa6e();
  if ((sVar1 != 0) && (DAT_000259f0 = DAT_000259f0 + -1, DAT_000259f0 == 0)) {
    DAT_000259f0 = 2;
    sVar1 = DAT_0002535e + 1;
    if (sVar1 < 0x1a) {
      if ((0x13 < sVar1) && (param_1 == 0)) {
        sVar1 = sVar1 + (DAT_0002535e + -0xc) * -2;
      }
      DAT_0002535e = sVar1;
      if (DAT_0002535e == 0xe) {
        *(short *)(DAT_00027d3c + 0x14) = -*(short *)(DAT_00027d3c + 0x14);
      }
    }
    else {
      DAT_0002535e = 0;
    }
  }
  return;
}


// ==== FUN_0001abde @ 0001abde ====

undefined4 FUN_0001abde(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  int local_10;
  int local_c;
  undefined4 local_8;
  
  if (param_1._0_2_ == 0) {
LAB_0001abec:
    if (DAT_0002535e == 0) {
      iVar1 = FUN_0001cb30(DAT_0002458e,*(undefined4 *)(&DAT_00025d30 + param_2._0_2_ * 4));
      iVar2 = FUN_0001cb30(DAT_00024592,*(undefined4 *)(&DAT_00025d30 + param_2._0_2_ * 4));
      if (*(short *)(iVar1 + 8) != (short)(param_1._2_2_ + 1)) {
        *(short *)(iVar1 + 8) = param_1._2_2_ + 1;
        FUN_00015b58(iVar1);
      }
      if (*(short *)(iVar2 + 8) != (short)(param_1._2_2_ + 1)) {
        *(short *)(iVar2 + 8) = param_1._2_2_ + 1;
        FUN_00015b58(iVar2);
      }
      local_8 = *(undefined4 *)(&DAT_00025d30 + param_2._0_2_ * 4);
      DAT_000254e2 = *(undefined2 *)(&DAT_00025a28 + param_2._0_2_ * 2);
    }
    else {
      DAT_000254e2 = 0;
      if (*(short *)(DAT_00027d3c + 0x14) == -1) {
        local_8 = *(undefined4 *)(&DAT_00025c60 + param_2._0_2_ * 4);
      }
      else {
        local_8 = *(undefined4 *)(&DAT_00025cc8 + param_2._0_2_ * 4);
      }
    }
  }
  else {
    if (param_1._0_2_ != 1) {
      if (param_1._0_2_ == 4) goto LAB_0001abec;
      if (param_1._0_2_ != 0xb) {
        iVar1 = FUN_0001cb30(DAT_0002458e,*(undefined4 *)(&DAT_00025d30 + param_2._0_2_ * 4));
        iVar2 = FUN_0001cb30(DAT_00024592,*(undefined4 *)(&DAT_00025d30 + param_2._0_2_ * 4));
        if (*(short *)(iVar1 + 8) != (short)(param_1._2_2_ + 1)) {
          FUN_00015b58(iVar1);
          *(short *)(iVar1 + 8) = param_1._2_2_ + 1;
        }
        if (*(short *)(iVar2 + 8) != (short)(param_1._2_2_ + 1)) {
          FUN_00015b58(iVar2);
          *(short *)(iVar2 + 8) = param_1._2_2_ + 1;
        }
        DAT_000254e2 = *(undefined2 *)(&DAT_00025a28 + param_2._0_2_ * 2);
        return *(undefined4 *)(&DAT_00025d30 + param_2._0_2_ * 4);
      }
    }
    if (DAT_000259ec == 0) {
      local_c = FUN_0001cb30(DAT_0002458e,*(undefined4 *)(&DAT_00025c30 + param_2._0_2_ * 4));
      local_10 = FUN_0001cb30(DAT_00024592,*(undefined4 *)(&DAT_00025c30 + param_2._0_2_ * 4));
      local_8 = *(undefined4 *)(&DAT_00025c30 + param_2._0_2_ * 4);
    }
    else {
      param_2._0_2_ = 9;
      local_c = FUN_0001cb30(DAT_0002458e,DAT_00025d54);
      local_10 = FUN_0001cb30(DAT_00024592,DAT_00025d54);
      local_8 = DAT_00025d54;
    }
    if (*(short *)(local_c + 8) != (short)(param_1._2_2_ + 1)) {
      FUN_00015b58(local_c);
      *(short *)(local_c + 8) = param_1._2_2_ + 1;
    }
    if (*(short *)(local_10 + 8) != (short)(param_1._2_2_ + 1)) {
      FUN_00015b58(local_10);
      *(short *)(local_10 + 8) = param_1._2_2_ + 1;
    }
    DAT_00027d36 = *(undefined2 *)(&DAT_00025c50 + param_2._0_2_ * 2);
    DAT_000254e2 = 4;
  }
  return local_8;
}


// ==== FUN_0001aed8 @ 0001aed8 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0001aed8(void)

{
  undefined4 uVar1;
  ushort uVar2;
  undefined2 uVar3;
  bool bVar4;
  undefined2 uVar5;
  short local_8;
  
  uVar1 = FUN_0001c982();
  uVar3 = (undefined2)((uint)DAT_00027d3c >> 0x10);
  uVar5 = (undefined2)DAT_00027d3c;
  local_8 = FUN_0001aaea();
  local_8 = *(short *)CONCAT22(uVar3,uVar5) - local_8;
  bVar4 = *(short *)(DAT_00027d3c + 0xc) == 6;
  if (bVar4) {
    local_8 = 0;
  }
  DAT_00025378 = 0;
  if ((DAT_000259f6 < 0x4b) && (DAT_000259f8 <= DAT_000259f6)) {
    uVar2 = FUN_00021e24();
    uVar2 = uVar2 & 0xc;
    DAT_000259f8 = uVar2 + DAT_000259f6;
    FUN_00021e24(bVar4);
    uVar3 = FUN_0001c982(local_8,uVar2,uVar1);
    (*_thunk_FUN_00010820)(uVar3);
  }
  return;
}


// ==== FUN_0001af7c @ 0001af7c ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0001af7c(void)

{
  if ((DAT_000252ac == '\x01') || (DAT_000252ac == '\0')) {
    DAT_000252b2 = 1;
  }
  DAT_000259f6 = DAT_000259f6 + 1;
  if ((DAT_000259f6 == 0x96) || ((0x1e < DAT_000259f6 && ((DAT_00026c92 & 0x30) != 0)))) {
    (*_thunk_FUN_000135ce)();
  }
  return;
}


// ==== FUN_0001afba @ 0001afba ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0001afba(void)

{
  bool bVar1;
  bool bVar2;
  short *psVar3;
  short sVar4;
  short sVar5;
  short sVar6;
  short sVar7;
  undefined2 uVar8;
  undefined2 uVar9;
  short local_14;
  short local_12;
  short local_6;
  
  local_6 = 1;
  bVar2 = false;
  bVar1 = false;
  local_14 = FUN_0001aaea();
  sVar4 = FUN_0001c982();
  sVar5 = FUN_0001cb74(sVar4);
  if (sVar5 == 0) {
    sVar5 = FUN_0001cb34(sVar4);
    if (sVar5 != 0) {
      local_6 = 3;
    }
  }
  else {
    local_6 = 2;
  }
  uVar9 = SUB42(DAT_00027d3c,0);
  uVar8 = (undefined2)((uint)DAT_00027d3c >> 0x10);
  if (local_6 == 1) {
    sVar5 = FUN_0001aaea();
    if (((short)(*(short *)CONCAT22(uVar8,uVar9) - sVar5) < 1) && (DAT_0002535e == 0)) {
      DAT_000254e2 = 0;
      DAT_000259f2 = 0;
      DAT_00025352 = 0;
      sVar5 = FUN_0001aaea();
      *DAT_00027d3c = sVar5;
      FUN_0001abde(DAT_00027d3c[10]);
      bVar1 = true;
      (*_thunk_FUN_00010820)(sVar4,0);
    }
    else {
      bVar2 = true;
    }
  }
  else if (local_6 == 2) {
    sVar5 = FUN_0001aaea();
    bVar1 = *(short *)CONCAT22(uVar8,uVar9) <= sVar5;
    if (bVar1) {
      DAT_000254e2 = 0;
      DAT_000259f2 = 0;
      DAT_00025352 = 0;
      sVar5 = FUN_0001aaea();
      *DAT_00027d3c = sVar5;
      (*_thunk_FUN_000152ac)(*DAT_00027d3c + 5);
    }
  }
  else if (local_6 == 3) {
    sVar6 = DAT_00025364 / 100;
    sVar5 = DAT_00027d3c[10];
    sVar7 = FUN_00015710(sVar4);
    local_14 = sVar7 + local_14;
    if (*DAT_00027d3c <= local_14) {
      sVar7 = FUN_0001cb74(sVar4 + DAT_00027d3c[10] * -10);
      if (sVar7 == 0) {
        bVar1 = true;
        DAT_000254e2 = 0;
        DAT_000259f2 = 0;
        DAT_00025352 = 0;
        uVar8 = (undefined2)((uint)DAT_00027d3c >> 0x10);
        uVar9 = SUB42(DAT_00027d3c,0);
        sVar5 = FUN_0001aaea();
        sVar6 = FUN_00015710(sVar4);
        *(short *)CONCAT22(uVar8,uVar9) = sVar6 + sVar5;
      }
      else {
        DAT_00027d3c[1] = DAT_00027d3c[1] - (sVar6 * sVar5 + 4);
        DAT_00025364 = 0;
        FUN_0001cab4(0xf00);
        local_14 = 2;
        (*_thunk_FUN_00010820)(sVar4,0);
      }
    }
  }
  if (DAT_0002535e < 0xe) {
    DAT_0002535e = DAT_0002535e + -2;
    if (DAT_0002535e < 0) {
      DAT_0002535e = 0;
    }
  }
  else {
    if (DAT_0002535e == 0xe) {
      DAT_00027d3c[10] = -DAT_00027d3c[10];
    }
    DAT_0002535e = DAT_0002535e + 2;
    if (0x19 < DAT_0002535e) {
      DAT_0002535e = 0;
    }
  }
  if ((DAT_0002535e == 0) || (local_14 < *DAT_00027d3c)) {
    if (bVar1) {
      DAT_00027d3c[1] = (DAT_00025364 / 100) * DAT_00027d3c[10] + DAT_00027d3c[1];
      DAT_00025364 = DAT_00025364 + -0x55;
      if (DAT_00025364 < 100) {
        DAT_00025364 = 0;
      }
      if (local_6 == 2) {
        (*_thunk_FUN_000152ac)(*DAT_00027d3c + 5);
      }
      else {
        (*_thunk_FUN_00010820)(*DAT_00027d3c,0);
        if (local_6 == 1) {
          (*_thunk_FUN_000146c6)(sVar4);
          (*_thunk_FUN_00011a84)(8);
        }
      }
    }
    else {
      DAT_00025352 = DAT_00025352 - DAT_00025e66;
      if (DAT_00025352 < -0xc1c) {
        DAT_00025352 = -0xc1c;
      }
      bVar2 = true;
    }
  }
  else {
    local_12 = 0xb;
    if (DAT_0002535e < 6) {
      local_12 = (&DAT_00025a50)[DAT_0002535e];
    }
    else if (0x13 < DAT_0002535e) {
      local_12 = (&DAT_00025a50)[(short)(0x19 - DAT_0002535e)];
    }
    sVar5 = FUN_0001cb34(sVar4);
    if ((sVar5 != 0) || (sVar5 = FUN_0001cb74(sVar4), sVar5 != 0)) {
      uVar8 = (undefined2)((uint)DAT_00027d3c >> 0x10);
      uVar9 = SUB42(DAT_00027d3c,0);
      sVar5 = FUN_00015710(sVar4);
      *(short *)CONCAT22(uVar8,uVar9) = local_12 + sVar5;
    }
    DAT_00027d3c[1] = (DAT_00025364 / 100) * DAT_00027d3c[10] + DAT_00027d3c[1];
    DAT_00025360 = 0;
  }
  psVar3 = DAT_00027d3c;
  if (bVar2) {
    DAT_00027d3c[0xc] = DAT_00027d3c[0xc] + -1;
    if (psVar3[0xc] < -10) {
      DAT_00027d3c[0xc] = -10;
    }
    *DAT_00027d3c = DAT_00027d3c[0xc] + *DAT_00027d3c;
    uVar8 = (undefined2)((uint)DAT_00027d3c >> 0x10);
    uVar9 = SUB42(DAT_00027d3c,0);
    sVar5 = FUN_0001aaea();
    if ((short)(*(short *)CONCAT22(uVar8,uVar9) - sVar5) < 1) {
      sVar5 = FUN_0001aaea();
      *DAT_00027d3c = sVar5;
      (*_thunk_FUN_00010820)(sVar4,0);
    }
    DAT_00027d3c[1] = (DAT_00025364 / 100) * DAT_00027d3c[10] + DAT_00027d3c[1];
  }
  if (((DAT_00025364 == 0) && (DAT_0002535e == 0)) && (*DAT_00027d3c <= local_14)) {
    sVar5 = FUN_0001cb74(sVar4);
    if ((sVar5 == 0) && ((sVar4 = FUN_0001cb34(sVar4), sVar4 == 0 || (0x13 < *DAT_00027d3c)))) {
      DAT_00027d3c[6] = 8;
    }
    else {
      DAT_00027d3c[6] = 6;
    }
    DAT_00027d3c[9] = 0;
    DAT_00027d3c[0xd] = 0;
    DAT_000259f8 = 0;
    DAT_000259f6 = 0;
    DAT_000259f4 = 0;
  }
  return;
}


// ==== FUN_0001b45a @ 0001b45a ====

int FUN_0001b45a(void)

{
  short sVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = (int)*(short *)(DAT_00027d3c + 0xc);
  if (iVar2 == 0) {
    sVar1 = *(short *)(DAT_00027d3c + 0xc) >> 0xf;
    iVar3 = CONCAT22(sVar1,*DAT_00027d44 - DAT_00025e52);
    if (((short)(*DAT_00027d44 - DAT_00025e52) < *(short *)(DAT_00027d3c + 2)) &&
       (iVar3 = CONCAT22(sVar1,DAT_00025e52 + *DAT_00027d44),
       *(short *)(DAT_00027d3c + 2) < (short)(DAT_00025e52 + *DAT_00027d44))) {
      if (DAT_0002542c == 0) {
        DAT_0002535a = 0;
      }
      else {
        DAT_0002535a = 5;
      }
    }
    else {
      DAT_0002535a = 0;
    }
  }
  else {
    iVar3 = 0;
    if (((iVar2 == 1) || (iVar3 = 0, iVar2 == 7)) || (iVar3 = iVar2 + -0xb, iVar3 == 0)) {
      DAT_0002535a = 5;
      DAT_0002529a = 5;
    }
    else {
      DAT_0002535a = 0;
    }
  }
  return iVar3;
}


// ==== FUN_0001b4de @ 0001b4de ====

undefined2 FUN_0001b4de(void)

{
  undefined2 local_a;
  short local_8;
  short local_6;
  
  local_a = 0;
  if (*(short *)(DAT_00027d3c + 0xc) == 1) {
    if (*(short *)(DAT_00027d3c + 0x14) < 0) {
      local_6 = *(short *)(DAT_00027d3c + 2) - *(short *)(&DAT_00025d80 + DAT_0002535e * 2);
      local_8 = *(short *)(DAT_00027d3c + 2) + *(short *)(&DAT_00025d8e + DAT_0002535e * 2);
    }
    else {
      local_6 = *(short *)(DAT_00027d3c + 2) - *(short *)(&DAT_00025d8e + DAT_0002535e * 2);
      local_8 = *(short *)(DAT_00027d3c + 2) + *(short *)(&DAT_00025d80 + DAT_0002535e * 2);
    }
    if (local_6 < (short)(*DAT_00027d44 + -0x17)) {
      DAT_000252af = 1;
    }
    else if ((short)(*DAT_00027d44 + 0x21) < local_8) {
      DAT_000252af = 0;
    }
    else {
      local_a = 1;
    }
  }
  return local_a;
}


// ==== FUN_0001b5b0 @ 0001b5b0 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

ushort FUN_0001b5b0(void)

{
  short *psVar1;
  ushort uVar2;
  short sVar3;
  undefined2 uVar4;
  
  uVar2 = DAT_00026c92 & 0x30;
  if ((DAT_00026c92 & 0x30) == 0) {
    DAT_000252ba = 0;
  }
  else if (DAT_00027d3c[6] == 0) {
    if ((DAT_00026c92 & 0x20) == 0) {
      if ((DAT_0002535e == 0) && (0 < DAT_00025e64)) {
        DAT_000252ba = 1;
      }
      else {
        DAT_000252ba = 0;
      }
    }
    else if ((DAT_0002535e < 6) || (0x10 < DAT_0002535e)) {
      uVar2 = (*_thunk_FUN_0001107c)();
    }
  }
  else if ((((DAT_00027d3c[6] == 1) && (*(short *)(DAT_00027d44 + 2) == 0)) && (DAT_00025434 != 0))
          && ((uVar2 = FUN_0001b4de(), uVar2 != 0 && (DAT_00025364 == 0)))) {
    DAT_000252af = 3;
    *(undefined2 *)(DAT_00027d44 + 2) = 3;
    DAT_00027d3c[6] = 0xb;
    psVar1 = DAT_00027d3c;
    DAT_00025378 = 0;
    sVar3 = FUN_0001aaea();
    uVar4 = FUN_0001c982();
    uVar2 = FUN_00015710(uVar4);
    *psVar1 = uVar2 + sVar3;
  }
  return uVar2;
}


// ==== FUN_0001b682 @ 0001b682 ====

void FUN_0001b682(void)

{
  short sVar1;
  undefined2 *puVar2;
  short local_10;
  short local_e;
  
  if (DAT_000252ba != 0) {
    DAT_00027d40 = &DAT_0002517a;
    for (local_e = 0; local_e < 4; local_e = local_e + 1) {
      if (DAT_00027d40[2] == 3) {
        local_10 = DAT_00027d3c[1] - DAT_00027d40[0x10];
        if (local_10 < 0) {
          local_10 = -local_10;
        }
        sVar1 = *DAT_00027d3c - DAT_00027d40[0x13];
        if (sVar1 < 0) {
          sVar1 = -sVar1;
        }
        if (((local_10 < 0xa0) && (sVar1 < 0x14)) && (DAT_00025352 == 0)) {
          DAT_00027d40[3] = 1;
          puVar2 = DAT_00027d40;
          DAT_00027d40[5] = DAT_00027d40[5] + -1;
          if ((short)puVar2[5] < 1) {
            FUN_0001cae0(6,CONCAT22(DAT_00027d40[0x10] + -0x10,DAT_00027d40[0x13] + 10));
            DAT_00027d40[4] = DAT_00027d40[4] + -8;
            if ((short)DAT_00027d40[4] < 0x60) {
              DAT_0002529c = DAT_0002529c + 0x15e;
              *DAT_00027d40 = 4;
              DAT_00027d40[0x12] = 0xfffd;
              DAT_00027d40[0xb] = 0;
              *(byte *)((int)DAT_00027d40 + 3) = *(byte *)((int)DAT_00027d40 + 3) & 0xf7;
              FUN_0001d35a(DAT_00027d40);
            }
            puVar2 = DAT_00027d40;
            sVar1 = FUN_0001cac8();
            puVar2[5] = sVar1 + 6;
          }
        }
      }
      DAT_00027d40 = DAT_00027d40 + 0x1a;
    }
  }
  return;
}


// ==== FUN_0001b7bc @ 0001b7bc ====

void FUN_0001b7bc(void)

{
  DAT_00027d44 = &DAT_000252e2;
  DAT_0002534c = DAT_00025428 * 4 + 0x10;
  DAT_0002534e = DAT_0002542a * 4 + -0x10;
  return;
}


// ==== FUN_0001b7ec @ 0001b7ec ====

void FUN_0001b7ec(void)

{
  short sVar2;
  undefined4 uVar1;
  undefined2 *puVar3;
  
  DAT_00027d3c = &DAT_00024fc8;
  FUN_0001b7bc();
  *DAT_00027d3c = 0;
  DAT_00027d3c[0xb] = 0;
  DAT_00027d3c[0xc] = 0;
  DAT_00027d3c[6] = 1;
  puVar3 = DAT_00027d3c;
  sVar2 = FUN_0001cac8();
  puVar3[8] = sVar2 + 6;
  DAT_00027d3c[9] = 0x80;
  DAT_00027d3c[7] = 0xc0;
  uVar1 = FUN_0001abde();
  *(undefined4 *)(DAT_00027d3c + 4) = uVar1;
  uVar1 = FUN_0001cb30((short)DAT_0002458e,*(undefined4 *)(DAT_00027d3c + 4));
  *(undefined4 *)(DAT_00027d3c + 2) = uVar1;
  DAT_0002536e = FUN_0001cb30((short)DAT_00024592,*(undefined4 *)(DAT_00027d3c + 4));
  DAT_00025352 = 0;
  DAT_00024fe4 = 0x546;
  DAT_00025364 = 0;
  DAT_0002535a = 5;
  DAT_0002529a = 5;
  DAT_000259ec = 0;
  DAT_000270b8 = 0x1c;
  DAT_0002729e = 0x1c;
  return;
}


// ==== FUN_0001b8c4 @ 0001b8c4 ====

undefined2 FUN_0001b8c4(void)

{
  short sVar1;
  undefined2 uVar2;
  short sVar3;
  undefined2 local_16;
  undefined2 local_6;
  
  local_6 = 0;
  local_16 = (undefined2)((uint)DAT_00027d3c >> 0x10);
  uVar2 = (undefined2)DAT_00027d3c;
  sVar1 = FUN_0001aaea();
  sVar1 = *(short *)CONCAT22(local_16,uVar2) - sVar1;
  uVar2 = FUN_0001c982();
  sVar3 = FUN_00015710(uVar2);
  if ((sVar1 < sVar3) || (sVar1 < 1)) {
    local_6 = 1;
  }
  return local_6;
}


// ==== FUN_0001b92e @ 0001b92e ====

void FUN_0001b92e(void)

{
  short sVar1;
  short sVar2;
  
  if ((599 < DAT_00025364) && (DAT_000259ec == 0)) {
    if (*(short *)(DAT_00027d3c + 0x14) == -1) {
      sVar2 = *(short *)(DAT_00027d3c + 2) + 0x18;
    }
    else {
      sVar2 = *(short *)(DAT_00027d3c + 2) + -0x18;
    }
    DAT_0002535c = *DAT_00027d44 + 0x46;
    for (sVar1 = 0; sVar1 < 4; sVar1 = sVar1 + 1) {
      if (((short)(DAT_0002535c + -8) <= sVar2) && (sVar2 <= (short)(DAT_0002535c + 8))) {
        *(undefined2 *)(DAT_00027d3c + 0xc) = 7;
        DAT_000252af = 4;
        DAT_000259ee = 0xffff;
        DAT_00026c8a = DAT_0002535c;
        return;
      }
      DAT_0002535c = DAT_0002535c + 0x38;
    }
  }
  return;
}


// ==== FUN_0001b9bc @ 0001b9bc ====

void FUN_0001b9bc(void)

{
  DAT_0002537c = 0;
  DAT_00025378 = 0;
  return;
}


// ==== FUN_0001b9cc @ 0001b9cc ====

void FUN_0001b9cc(void)

{
  DAT_0002537c = 0x28;
  DAT_00025378 = 0x28;
  DAT_0002537e = 0x328;
  DAT_0002537a = 0x328;
  DAT_00027d38 = 0;
  return;
}


// ==== FUN_0001b9f0 @ 0001b9f0 ====

void FUN_0001b9f0(void)

{
  return;
}


// ==== FUN_0001ba80 @ 0001ba80 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0001ba80(void)

{
  bool bVar1;
  undefined2 uVar2;
  short sVar3;
  short sVar4;
  undefined2 uVar5;
  undefined2 uVar6;
  
  sVar3 = DAT_00027d3c[1];
  uVar2 = FUN_0001c982();
  if (((DAT_0002534c <= sVar3) && (sVar3 <= DAT_0002534e)) && (DAT_0002535e == 0)) {
    uVar5 = (undefined2)((uint)DAT_00027d3c >> 0x10);
    uVar6 = SUB42(DAT_00027d3c,0);
    sVar3 = FUN_00015710(uVar2);
    sVar4 = FUN_0001aaea();
    if (((short)(sVar4 + sVar3 + -4) <= *(short *)CONCAT22(uVar5,uVar6)) && (DAT_0002542c != 0)) {
      bVar1 = true;
      goto LAB_0001baf0;
    }
  }
  bVar1 = false;
LAB_0001baf0:
  sVar3 = FUN_0001aaea();
  if (((sVar3 < 0x37) && (DAT_00027d3c[6] == 0)) && (sVar3 = FUN_0001b8c4(), sVar3 != 0)) {
    if (bVar1) {
      if ((DAT_00027d3c[10] == -1) && (DAT_000259fa != 0)) {
        DAT_00027d3c[6] = 1;
        DAT_000259ee = 0xffff;
        (*_thunk_FUN_00012380)();
        uVar5 = (undefined2)((uint)DAT_00027d3c >> 0x10);
        uVar6 = SUB42(DAT_00027d3c,0);
        sVar3 = FUN_0001aaea();
        sVar4 = FUN_00015710(uVar2);
        *(short *)CONCAT22(uVar5,uVar6) = sVar4 + sVar3;
      }
      else {
        DAT_00027d3c[0xc] = -DAT_00027d3c[0xc];
        DAT_00025352 = -DAT_00025352;
        *DAT_00027d3c = *DAT_00027d3c + 6;
        (*_thunk_FUN_00012380)();
      }
    }
    else {
      DAT_00027d3c[6] = 4;
      DAT_00025364 = DAT_00027d3c[0xb] * 100;
      sVar3 = FUN_0001cb74(uVar2);
      if ((sVar3 == 0) && ((sVar3 = FUN_0001cb34(uVar2), sVar3 == 0 || (0x13 < *DAT_00027d3c)))) {
        uVar6 = 0;
        uVar5 = FUN_0001c982(*DAT_00027d3c,0);
        (*_thunk_FUN_00010820)(uVar5,uVar6);
        (*_thunk_FUN_000146c6)(uVar2);
      }
      FUN_0001afba();
    }
  }
  return;
}


// ==== FUN_0001bc02 @ 0001bc02 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

ushort FUN_0001bc02(void)

{
  uint uVar1;
  ushort uVar2;
  short local_6;
  
  local_6 = 0x7fff - *(short *)(DAT_00027d3c + 2);
  if (local_6 < 0) {
    local_6 = -local_6;
  }
  uVar2 = DAT_00026c92 & 0x30;
  if ((DAT_00026c92 & 0x30) == 0) {
    if ((((DAT_00024fe4 != 0) && (DAT_0002542c != 0)) && (DAT_00025434 != 0)) &&
       ((DAT_00024fe4 = DAT_00024fe4 + -1, DAT_00024fe4 == 0 && (0x1a00 < local_6)))) {
      if ((*(short *)(DAT_00027d3c + 2) < DAT_0002534c) ||
         ((*(short *)(DAT_00027d3c + 2) <= DAT_0002534e &&
          (uVar1 = (*_thunk_FUN_000203be)(), (uVar1 & 0x8000) != 0)))) {
        uVar2 = (*_thunk_FUN_0001e4d0)(*(short *)(DAT_00027d3c + 2) + -0x1800,1);
      }
      else {
        uVar2 = (*_thunk_FUN_0001e4d0)(*(short *)(DAT_00027d3c + 2) + 0x1800,0xffff);
      }
    }
  }
  else if ((DAT_00024fe4 != 0) && (DAT_00024fe4 < 0x2ee)) {
    DAT_00024fe4 = 0x2ee;
  }
  return uVar2;
}


// ==== FUN_0001bcce @ 0001bcce ====

void FUN_0001bcce(void)

{
  short sVar1;
  
  if (DAT_000252b7 == '\0') {
    sVar1 = FUN_0001b4de();
    if (sVar1 == 0) {
      DAT_00025d9c = DAT_00025364 / 4;
      DAT_00025d9e = (short)(DAT_00025d9c * DAT_00025d9c * 2) / 100;
      DAT_00025da0 = *(short *)(DAT_00027d3c + 2) - *DAT_00027d44;
      if (DAT_00025da0 < 0) {
        DAT_00025da0 = -DAT_00025da0;
      }
      DAT_00025da0 = DAT_00025da0 + -0x10;
      if (*(short *)(DAT_00027d3c + 2) < *DAT_00027d44) {
        if (((DAT_00025da0 < DAT_00025d9e) && (*(short *)(DAT_00027d3c + 0x14) == 1)) &&
           (0 < DAT_00025364)) {
          DAT_000252af = 4;
        }
      }
      else if (((DAT_00025da0 < DAT_00025d9e) && (*(short *)(DAT_00027d3c + 0x14) == -1)) &&
              (0 < DAT_00025364)) {
        DAT_000252af = 4;
      }
    }
    else {
      DAT_000252af = 5;
    }
  }
  else if (((short)(*(short *)(DAT_00027d3c + 2) - DAT_0002534c) < 0x136) && (DAT_00025364 < 400)) {
    DAT_000252af = 1;
  }
  else {
    DAT_000252af = 0;
  }
  return;
}


// ==== FUN_0001bdba @ 0001bdba ====

void FUN_0001bdba(void)

{
  if (*(short *)(DAT_00027d3c + 0xc) != 0) {
    *(short *)(DAT_00027d3c + 0x16) = (short)(DAT_00025364 + 0x32) / 100;
    *(short *)(DAT_00027d3c + 2) =
         *(short *)(DAT_00027d3c + 0x16) * *(short *)(DAT_00027d3c + 0x14) +
         *(short *)(DAT_00027d3c + 2);
  }
  return;
}


// ==== FUN_0001bdfa @ 0001bdfa ====

void FUN_0001bdfa(void)

{
  short sVar1;
  
  if ((DAT_000259fa == 0) || (DAT_00025352 != 600)) {
    sVar1 = DAT_00025352 - DAT_000259f2;
  }
  else {
    sVar1 = -800 - DAT_000259f2;
  }
  DAT_000259f2 = sVar1 / 4 + DAT_000259f2;
  if ((DAT_000259f2 < 0) || (DAT_00025358 < 0)) {
    FUN_00021cb0();
  }
  sVar1 = FUN_00021cc4();
  DAT_00027d3a = DAT_00027d3a - sVar1;
  if ((0 < DAT_00027d3c[10]) && (DAT_00025364 < 1000)) {
    DAT_00027d3a = DAT_00027d3a - DAT_00027d3a / 10;
  }
  FUN_00021ce2(*(undefined4 *)(&DAT_00025a5c + DAT_0002535e * 4));
  FUN_00021cec();
  FUN_00021cec();
  FUN_00021c9c();
  FUN_00021cd8();
  sVar1 = FUN_00021cc4();
  DAT_00027d3c[0xb] = sVar1;
  DAT_00027d3c[1] = DAT_00027d3c[0xb] * DAT_00027d3c[10] + DAT_00027d3c[1];
  FUN_00021ce2();
  FUN_00021cec();
  FUN_00021cd8();
  sVar1 = FUN_00021cc4();
  DAT_00027d3c[0xc] = sVar1;
  if ((DAT_00025364 < 1000) && (DAT_00027d3c[6] == 0)) {
    if ((((byte)DAT_00026c92 & 1) == 0) &&
       (DAT_00025352 = DAT_00025352 - DAT_00025e66 / 2, DAT_00025352 < -0x1194)) {
      DAT_00025352 = -0x1194;
    }
    DAT_00027d3c[0xc] = DAT_00027d3c[0xc] - (short)(1000 - DAT_00025364) / 100;
  }
  *DAT_00027d3c = DAT_00027d3c[0xc] + *DAT_00027d3c;
  if (*DAT_00027d3c < 0x44d) {
    if (*DAT_00027d3c < -4) {
      *DAT_00027d3c = -4;
    }
  }
  else {
    *DAT_00027d3c = 0x44c;
    DAT_00025352 = -DAT_00025352;
    DAT_00027d3c[0xc] = -(DAT_00027d3c[0xc] / 2);
  }
  return;
}


// ==== FUN_0001bff4 @ 0001bff4 ====

uint FUN_0001bff4(void)

{
  uint uVar1;
  uint uVar2;
  short sVar3;
  
  DAT_000259fa = 0;
  if ((DAT_00026c92 & 8) == 0) {
    sVar3 = 1;
  }
  else {
    sVar3 = -1;
  }
  DAT_00025358 = 0;
  uVar2 = DAT_00026c92 & 0xffff000f;
  if ((DAT_00026c92 & 0xf) == 0) {
    if (DAT_0002535e == 0) {
      if (0 < DAT_00025352) {
        uVar2 = (uint)DAT_00025e66;
        DAT_00025352 = DAT_00025352 - DAT_00025e66;
        if (DAT_00025352 < 0) {
          DAT_00025352 = 0;
        }
        if (DAT_00025352 < 0x1f5) {
          DAT_00025358 = -DAT_00025352;
          uVar2 = (uint)DAT_00025358;
        }
      }
    }
    else {
      if (DAT_0002535e < 7) {
        DAT_0002535e = DAT_0002535e + -1;
      }
      else {
        FUN_0001ab80(0);
      }
      DAT_00025360 = 0;
      uVar2 = (int)(short)DAT_00025e66 / 4 & 0xffff;
      DAT_00025352 = DAT_00025352 - (short)((int)(short)DAT_00025e66 / 4);
      if (DAT_00025352 < -0x8ca) {
        DAT_00025352 = -0x8ca;
      }
      if ((0 < DAT_00025352) && (DAT_00025352 < 0x1f5)) {
        DAT_00025358 = -DAT_00025352;
        uVar2 = (uint)DAT_00025358;
      }
    }
    DAT_00027d3a = DAT_00027d3a - 1;
    if ((short)DAT_00027d3a < 4) {
      DAT_00027d3a = 4;
    }
    if (1000 < DAT_00025364) {
      uVar2 = (uint)DAT_00027d3a;
      DAT_00025364 = DAT_00025364 - DAT_00027d3a;
      if (DAT_00025364 < 1000) {
        DAT_00025364 = 1000;
      }
    }
    DAT_00025378 = 0x31;
    DAT_0002537a = 0x181;
    DAT_00027d38 = 0;
  }
  else {
    uVar2 = DAT_00026c92 & 0xffff000c;
    if ((DAT_00026c92 & 0xc) == 0) {
      DAT_00025378 = 0x31;
      DAT_0002537a = 0x181;
      DAT_00027d38 = 0;
      if ((DAT_00026c92 & 2) == 0) {
        if ((DAT_00026c92 & 1) != 0) {
          if (*(short *)(DAT_00027d3c + 0x14) == -1) {
            if ((DAT_00025352 == 0) || (DAT_00025352 < 600)) {
              DAT_00025352 = DAT_00025e66 + DAT_00025352;
              if (600 < DAT_00025352) {
                DAT_00025352 = 600;
              }
            }
            else {
              DAT_00025352 = DAT_00025352 - DAT_00025e66;
              if (DAT_00025352 < 600) {
                DAT_00025352 = 600;
              }
            }
            uVar2 = (uint)DAT_00025e66;
            DAT_000259fa = 1;
          }
          else {
            uVar2 = (uint)DAT_00025e66;
            DAT_00025352 = DAT_00025352 - DAT_00025e66;
            if (DAT_00025352 < -600) {
              uVar1 = (int)(short)(DAT_00025352 + 600) / 2;
              uVar2 = uVar1 & 0xffff;
              DAT_00025352 = DAT_00025352 - (short)uVar1;
            }
            DAT_000259fa = 0;
          }
        }
      }
      else {
        DAT_00025378 = 0x40;
        DAT_0002537a = 0x14f;
        DAT_00027d38 = 1;
        uVar2 = (uint)(ushort)(DAT_00025e66 * 2);
        DAT_00025352 = DAT_00025352 + DAT_00025e66 * -2;
        if (DAT_00025352 < -0x1194) {
          DAT_00025352 = -0x1194;
        }
      }
      DAT_00025358 = 0;
      if (DAT_0002535e != 0) {
        if (DAT_0002535e < 7) {
          DAT_0002535e = DAT_0002535e + -1;
        }
        else {
          uVar2 = FUN_0001ab80(0);
        }
        DAT_00025360 = 0;
      }
    }
    else {
      if (*(short *)(DAT_00027d3c + 0x14) == sVar3) {
        DAT_00027d38 = 1;
        if (DAT_0002535e != 0) {
          if (DAT_0002535e < 7) {
            DAT_0002535e = DAT_0002535e + -1;
          }
          else {
            FUN_0001ab80(1);
          }
        }
        DAT_00027d3a = DAT_00027d3a + 1;
        if (8 < (short)DAT_00027d3a) {
          DAT_00027d3a = 8;
        }
        DAT_00025378 = 0x40;
        DAT_0002537a = 0x14f;
        DAT_00027d38 = 1;
        DAT_00025364 = DAT_00027d3a + DAT_00025364;
        if (0x578 < DAT_00025364) {
          DAT_00025364 = 0x578;
        }
      }
      else {
        FUN_0001ab80(0);
      }
      uVar2 = DAT_00026c92 & 0xffff0003;
      if ((DAT_00026c92 & 3) == 0) {
        if (DAT_0002535e == 0) {
          if (0 < DAT_00025352) {
            uVar2 = (uint)DAT_00025e66;
            DAT_00025352 = DAT_00025352 - DAT_00025e66;
            if (DAT_00025352 < 0) {
              DAT_00025352 = 0;
            }
            if (DAT_00025352 < 0x1f5) {
              DAT_00025358 = -DAT_00025352;
              uVar2 = (uint)DAT_00025358;
            }
          }
        }
        else {
          uVar2 = (int)(short)DAT_00025e66 / 4 & 0xffff;
          DAT_00025352 = DAT_00025352 - (short)((int)(short)DAT_00025e66 / 4);
          if (DAT_00025352 < -0x8ca) {
            DAT_00025352 = -0x8ca;
          }
          if ((0 < DAT_00025352) && (DAT_00025352 < 0x1f5)) {
            DAT_00025358 = -DAT_00025352;
            uVar2 = (uint)DAT_00025358;
          }
        }
      }
      else if ((DAT_00026c92 & 2) == 0) {
        if (DAT_00025364 < 0x3e9) {
          if (*(short *)(DAT_00027d3c + 0x14) < 1) {
            uVar2 = (int)(short)DAT_00025e66 / 8;
            sVar3 = (short)uVar2;
          }
          else {
            uVar2 = (int)(short)DAT_00025e66 / 4;
            sVar3 = (short)uVar2;
          }
          DAT_00025352 = sVar3 + DAT_00025352;
          uVar2 = uVar2 & 0xffff;
          if (3000 < DAT_00025352) {
            DAT_00025352 = 3000;
          }
        }
        else {
          uVar2 = (uint)DAT_00025e66;
          DAT_00025352 = DAT_00025e66 + DAT_00025352;
          if (3000 < DAT_00025352) {
            DAT_00025352 = 3000;
          }
        }
      }
      else if (DAT_0002535e == 0) {
        uVar2 = (uint)DAT_00025e66;
        DAT_00025352 = DAT_00025352 - DAT_00025e66;
        if (DAT_00025352 < -0x1194) {
          DAT_00025352 = -0x1194;
        }
      }
      else {
        uVar2 = (int)(short)DAT_00025e66 / 2 & 0xffff;
        DAT_00025352 = DAT_00025352 - (short)((int)(short)DAT_00025e66 / 2);
        if (DAT_00025352 < -0x1194) {
          DAT_00025352 = -0x1194;
        }
      }
    }
  }
  return uVar2;
}


// ==== FUN_0001c378 @ 0001c378 ====

void FUN_0001c378(void)

{
  undefined4 uVar1;
  short local_a;
  undefined2 uVar2;
  short local_6;
  
  local_6 = 0;
  uVar2 = 1;
  local_a = 9;
  DAT_00025372 = 0;
  if (((*(short *)(DAT_00027d3c + 0xc) != 1) && (*(short *)(DAT_00027d3c + 0xc) != 0xb)) &&
     (DAT_0002535e == 0)) {
    local_a = (short)(DAT_00025352 + 5000) / 500;
    local_6 = local_a;
  }
  if (((*(short *)(DAT_00027d3c + 0xc) == 0) || (*(short *)(DAT_00027d3c + 0xc) == 7)) ||
     ((*(short *)(DAT_00027d3c + 0xc) == 4 || (DAT_000259ec == 1)))) {
    if (DAT_0002535e == 0) {
      if (*(short *)(DAT_00027d3c + 0x14) == -1) {
        DAT_00025372 = *(undefined4 *)(&DAT_00025da2 + local_a * 4);
        DAT_00025376 = local_6 + 10;
      }
      else {
        DAT_00025372 = *(undefined4 *)(s_wh0awh0awh09wh09wh08wh08wh07wh07_00025df2 + local_a * 4);
        DAT_00025376 = local_6;
      }
      DAT_0002536a = FUN_0001cb30((short)DAT_0002458e,DAT_00025372,1);
    }
    else {
      uVar1 = FUN_0001abde();
      *(undefined4 *)(DAT_00027d3c + 8) = uVar1;
      DAT_000259ee = 0xffff;
    }
  }
  if (*(short *)(DAT_00027d3c + 0xc) != 8) {
    uVar1 = FUN_0001abde();
    *(undefined4 *)(DAT_00027d3c + 8) = uVar1;
  }
  uVar1 = FUN_0001cb30((short)DAT_0002458e,*(undefined4 *)(DAT_00027d3c + 8),uVar2);
  *(undefined4 *)(DAT_00027d3c + 4) = uVar1;
  FUN_000204ec();
  DAT_0002536e = FUN_0001cb30((short)DAT_00024592,*(undefined4 *)(DAT_00027d3c + 8));
  FUN_000204e4();
  return;
}


// ==== FUN_0001c4e8 @ 0001c4e8 ====

short FUN_0001c4e8(void)

{
  short sVar1;
  short sVar2;
  
  DAT_000252ba = 0;
  if ((DAT_00026c92 & 0xc) == 0) {
    DAT_00025378 = 0x28;
    DAT_0002537a = 0x328;
    DAT_00027d38 = 0;
    DAT_00027d3a = 0;
    DAT_00025364 = DAT_00025364 + -8;
    sVar1 = 0;
  }
  else {
    if ((DAT_00026c92 & 8) == 0) {
      sVar2 = 1;
    }
    else {
      sVar2 = -1;
    }
    sVar1 = *(short *)(DAT_00027d3c + 0x14);
    if (sVar1 == sVar2) {
      DAT_00027d38 = 1;
      if (DAT_0002535e == 0) {
        DAT_00025378 = 0x40;
        DAT_0002537a = 0x14f;
        DAT_00027d3a = DAT_00027d3a + 1;
        if (8 < DAT_00027d3a) {
          DAT_00027d3a = 8;
        }
      }
      else {
        DAT_00025378 = 0x28;
        DAT_0002537a = 0x328;
        DAT_0002535e = DAT_0002535e + -1;
      }
      DAT_00025364 = DAT_00027d3a + DAT_00025364;
      sVar1 = DAT_00027d3a;
    }
    else {
      DAT_00027d38 = 0;
      DAT_00025378 = 0x28;
      DAT_0002537a = 0x328;
      DAT_00027d3a = 0;
      if ((DAT_00025364 == 0) && (DAT_0002535e = DAT_0002535e + 1, 6 < DAT_0002535e)) {
        *(short *)(DAT_00027d3c + 0x14) = -*(short *)(DAT_00027d3c + 0x14);
        DAT_0002535e = 5;
      }
      DAT_00025364 = DAT_00025364 + -8;
    }
  }
  DAT_000259ec = 0;
  if ((600 < DAT_00025364) && ((DAT_00026c92 & 1) == 0)) {
    DAT_000259ec = 1;
  }
  if (DAT_00025364 < 0) {
    DAT_00025364 = 0;
  }
  else if (0x578 < DAT_00025364) {
    DAT_00025364 = 0x578;
  }
  return sVar1;
}


// ==== FUN_0001c5f4 @ 0001c5f4 ====

void FUN_0001c5f4(void)

{
  short *psVar1;
  short sVar2;
  undefined2 uVar3;
  short sVar4;
  
  psVar1 = DAT_00027d3c;
  if ((DAT_00027d3c[1] < DAT_0002534c) || (DAT_0002534e < DAT_00027d3c[1])) {
    DAT_000252af = 2;
    DAT_000252b7 = 0;
    DAT_00027d3c[6] = 0;
    DAT_00025360 = DAT_00025e54;
  }
  else {
    sVar2 = FUN_0001aaea();
    uVar3 = FUN_0001c982();
    sVar4 = FUN_00015710(uVar3);
    *psVar1 = sVar4 + sVar2;
  }
  return;
}


// ==== FUN_0001c660 @ 0001c660 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0001c660(void)

{
  short *psVar1;
  undefined2 uVar2;
  short sVar3;
  undefined2 uVar4;
  short sVar5;
  undefined2 uStack_1a;
  
  DAT_00025360 = 100;
  FUN_0001b5b0();
  FUN_0001bc02();
  if (_DAT_000252b4 == 0) {
    if (DAT_00025364 == 0) {
      DAT_00026bda = 0;
    }
    uVar2 = SUB42(DAT_00027d3c,0);
    uStack_1a = (undefined2)((uint)DAT_00027d3c >> 0x10);
    switch(DAT_00027d3c[6]) {
    case 0:
      if ((DAT_00027d3c[9] < 0x60) || (DAT_00027d3c[7] < 0)) {
        DAT_000252af = 3;
        DAT_00027d3c[6] = 4;
        DAT_00025364 = DAT_00027d3c[0xb] * 100;
        FUN_0001afba();
      }
      else if (*DAT_00027d3c < -6) {
        DAT_00027d3c[6] = 6;
        DAT_000259f8 = 0;
        DAT_000259f6 = 0;
        DAT_000259f4 = 0;
        DAT_000252af = 3;
      }
      else {
        FUN_0001bff4();
        FUN_0001b9f0();
        FUN_0001bdfa();
        FUN_0001ba80();
        if (*DAT_00027d3c < 0x51) {
          DAT_000252af = 2;
        }
        else {
          DAT_000252af = 3;
        }
        FUN_0001bcce();
      }
      break;
    case 1:
      FUN_0001c4e8();
      FUN_0001bdba();
      FUN_0001c5f4();
      FUN_0001b92e();
      FUN_0001bcce();
      break;
    default:
      sVar3 = FUN_0001aaea();
      uVar4 = FUN_0001c982();
      sVar5 = FUN_00015710(uVar4);
      *(short *)CONCAT22(uStack_1a,uVar2) = sVar5 + sVar3;
      if (*(short *)(DAT_00027d44 + 2) == 0) {
        DAT_00027d3c[6] = 1;
      }
      break;
    case 4:
      DAT_00025378 = 0x19;
      DAT_0002537a = 0x3c0;
      DAT_00027d38 = 0;
      DAT_000252ba = 0;
      DAT_00025358 = 0;
      FUN_0001c982();
      DAT_000252af = 3;
      DAT_000259ee = 0xffff;
      FUN_0001afba();
      break;
    case 6:
      DAT_00025378 = 0;
      DAT_000259f4 = DAT_000259f4 + 1;
      if (2 < DAT_000259f4) {
        DAT_000259f4 = 0;
        *DAT_00027d3c = *DAT_00027d3c + -1;
      }
      DAT_00025352 = DAT_00025352 + -0xfa;
      if (DAT_00025352 < -0x1194) {
        DAT_00025352 = -0x1194;
      }
      FUN_0001aed8();
      FUN_0001af7c();
      break;
    case 7:
      DAT_00025378 = 0x28;
      DAT_0002537a = 0x328;
      sVar3 = FUN_0001aaea();
      uVar4 = FUN_0001c982();
      sVar5 = FUN_00015710(uVar4);
      *(short *)CONCAT22(uStack_1a,uVar2) = sVar5 + sVar3;
      DAT_00025352 = 0;
      DAT_00025358 = 0;
      DAT_00026bda = 0;
      DAT_00025364 = DAT_00025364 + -0x6e;
      if (DAT_00025364 < 0) {
        DAT_00025364 = 0;
        DAT_00027d3c[6] = 1;
        DAT_000259ee = 0xffff;
      }
      FUN_0001bdba();
      break;
    case 8:
      psVar1 = DAT_00027d3c;
      psVar1[4] = 0x6863;
      psVar1[5] = 0x7235;
      if (DAT_00027d3c[10] == -1) {
        psVar1 = DAT_00027d3c;
        psVar1[4] = 0x6863;
        psVar1[5] = 0x7266;
      }
      DAT_000254e2 = 0;
      uVar2 = FUN_0001c982();
      sVar3 = FUN_0001cb34(uVar2);
      if (sVar3 == 0) {
        sVar3 = FUN_0001aaea();
        *DAT_00027d3c = sVar3;
      }
      else {
        uStack_1a = (undefined2)((uint)DAT_00027d3c >> 0x10);
        uVar4 = SUB42(DAT_00027d3c,0);
        sVar3 = FUN_0001aaea();
        sVar5 = FUN_00015710(uVar2);
        *(short *)CONCAT22(uStack_1a,uVar4) = sVar5 + sVar3;
      }
      DAT_00026bd4 = DAT_00026bd4 + 1;
      if ((DAT_00026bd4 & 3) == 0) {
        FUN_0001cae0(6,*DAT_00027d3c + 0xb);
      }
      FUN_0001aed8();
      FUN_0001af7c();
      break;
    case 9:
    }
    FUN_0001b45a();
    FUN_0001c378();
  }
  else {
    DAT_00027d3a = 0;
    DAT_00025364 = 0;
  }
  DAT_00025300 = 8;
  if (0xba < *DAT_00027d3c) {
    DAT_00025300 = 1;
  }
  return;
}


// ==== FUN_0001c982 @ 0001c982 ====

uint FUN_0001c982(int param_1)

{
  uint local_8;
  
  if (param_1 < 0) {
    param_1._0_2_ = 0;
  }
  local_8 = DAT_00024578 + (short)(param_1._0_2_ / 8 << 1);
  if (DAT_0002457c <= local_8) {
    local_8 = DAT_0002457c - 2;
  }
  return local_8;
}


// ==== FUN_0001c9ca @ 0001c9ca ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0001c9ca(void)

{
  short sVar1;
  
  DAT_00026be2 = DAT_00026be2 + 1;
  sVar1 = (*_thunk_FUN_0002044c)();
  if ((sVar1 != 0) && (DAT_00026bdc == 0)) {
    DAT_00026bde = DAT_00026be2;
  }
  if (DAT_00026be2 < DAT_00026bde + 10) {
    if ((sVar1 == 0) && (DAT_00026bdc != 0)) {
      DAT_00027d4c = 1;
    }
  }
  else if (sVar1 != 0) {
    DAT_00027d4a = 1;
  }
  if (sVar1 == 0) {
    DAT_00026bde = 0;
  }
  DAT_00026bdc = sVar1;
  return;
}


// ==== FUN_0001ca32 @ 0001ca32 ====

void FUN_0001ca32(void)

{
  ushort uVar1;
  
  uVar1 = FUN_0001cb20();
  DAT_000272b6._1_1_ = 0;
  if (DAT_00027d4c != 0) {
    DAT_000272b6._1_1_ = 0x20;
    DAT_00027d4c = 0;
    DAT_00027d4a = 0;
  }
  if (DAT_00027d4a != 0) {
    DAT_000272b6._1_1_ = (byte)DAT_000272b6 | 0x10;
    DAT_00027d4a = 0;
  }
  if ((uVar1 & 1) != 0) {
    DAT_000272b6._1_1_ = (byte)DAT_000272b6 | 1;
  }
  if ((uVar1 & 2) != 0) {
    DAT_000272b6._1_1_ = (byte)DAT_000272b6 | 2;
  }
  if ((uVar1 & 4) != 0) {
    DAT_000272b6._1_1_ = (byte)DAT_000272b6 | 8;
  }
  if ((uVar1 & 8) != 0) {
    DAT_000272b6._1_1_ = (byte)DAT_000272b6 | 4;
  }
  DAT_000272b6._0_1_ = 0;
  return;
}


// ==== FUN_0001cab4 @ 0001cab4 ====

void FUN_0001cab4(undefined4 param_1)

{
  DAT_00025366 = param_1._0_2_;
  DAT_00025368 = param_1._2_2_;
  return;
}


// ==== FUN_0001cac8 @ 0001cac8 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint FUN_0001cac8(uint param_1)

{
  uint uVar1;
  
  uVar1 = (*_thunk_FUN_000203be)();
  return (uVar1 & 0xffff) / (param_1 >> 0x10) << 0x10 | (uVar1 & 0xffff) % (param_1 >> 0x10);
}


// ==== FUN_0001cae0 @ 0001cae0 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0001cae0(undefined4 param_1,undefined4 param_2)

{
  ushort uVar1;
  
  uVar1 = (*_thunk_FUN_000203be)();
  FUN_000154cc((int)(short)((uVar1 & 7) + param_2._0_2_) << 0x10,0);
  return;
}


// ==== FUN_0001cb20 @ 0001cb20 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0001cb20(void)

{
                    /* WARNING: Could not recover jumptable at 0x0001cb20. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*_thunk_FUN_0001520e)();
  return;
}


// ==== FUN_0001cb30 @ 0001cb30 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0001cb30(void)

{
                    /* WARNING: Could not recover jumptable at 0x0001cb30. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*_thunk_FUN_000204f4)();
  return;
}


// ==== FUN_0001cb34 @ 0001cb34 ====

bool FUN_0001cb34(ushort *param_1)

{
  bool bVar1;
  
  if ((DAT_00024578 < param_1) && (param_1 < (ushort *)(DAT_0002457c + -2))) {
    bVar1 = (*param_1 & 3) == 1;
  }
  else {
    bVar1 = false;
  }
  return bVar1;
}


// ==== FUN_0001cb74 @ 0001cb74 ====

bool FUN_0001cb74(ushort *param_1)

{
  bool bVar1;
  
  if ((DAT_00024578 < param_1) && (param_1 < (ushort *)(DAT_0002457c + -2))) {
    bVar1 = (*param_1 & 3) == 0;
  }
  else {
    bVar1 = true;
  }
  return bVar1;
}


// ==== FUN_0001cbb2 @ 0001cbb2 ====

bool FUN_0001cbb2(ushort *param_1)

{
  bool bVar1;
  
  if ((DAT_00024578 < param_1) && (param_1 < (ushort *)(DAT_0002457c + -2))) {
    bVar1 = (*param_1 & 3) == 2;
  }
  else {
    bVar1 = false;
  }
  return bVar1;
}


// ==== FUN_0001cbf2 @ 0001cbf2 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_0001cbf2(undefined4 param_1)

{
  short sVar1;
  short local_8;
  
  sVar1 = FUN_0001cb34(param_1);
  if (sVar1 == 0) {
    (*_thunk_FUN_00021dce)(s_Not_over_a_ship_in_ShipNum__0001cc76);
  }
  else {
    sVar1 = (short)param_1 - (short)DAT_00024578;
    local_8 = 0;
    do {
      if ((*(short *)(&PTR_DAT_000254aa)[local_8] <= sVar1) &&
         (sVar1 <= *(short *)((&PTR_DAT_000254aa)[local_8] + 2))) {
        return CONCAT22((short)((uint)(local_8 * 4) >> 0x10),local_8);
      }
      local_8 = local_8 + 1;
    } while (local_8 < 5);
    (*_thunk_FUN_00021dce)(s_COULDN_T_FIND_A_SHIP_in_ShipNum__0001cc93);
  }
  return 1;
}


// ==== FUN_0001ccb6 @ 0001ccb6 ====

void FUN_0001ccb6(undefined4 param_1)

{
  int iVar1;
  
  iVar1 = FUN_00022b7c(0);
  if (((iVar1 < 400000) && (param_1._0_2_ != 0)) && (*(int *)(DAT_00026e76 + 0x34) != 0)) {
    DAT_00026d6a = 1;
    FUN_00022f1c(*(undefined4 *)(DAT_00026e76 + 0x34));
  }
  FUN_00022f28();
  return;
}


// ==== FUN_0001ccf6 @ 0001ccf6 ====

/* WARNING: Control flow encountered unimplemented instructions */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0001ccf6(void)

{
  uint uVar1;
  char cVar6;
  short sVar4;
  undefined2 uVar5;
  undefined4 uVar2;
  int iVar3;
  ushort *puVar7;
  undefined1 uVar8;
  
  _DAT_00026eac = 0;
  uVar8 = 1;
LAB_0001ccfa:
  while( true ) {
    (*_thunk_FUN_000207d8)();
    if ((bool)uVar8) {
      return;
    }
    uVar1 = (*_thunk_FUN_000207e4)();
    _DAT_00026eac = uVar1 & 0x7fffffff;
    cVar6 = (*_thunk_FUN_00020700)((short)uVar1);
    iVar3 = DAT_00026ec4;
    if ((_DAT_00026eac & 0x80000) == 0) break;
    if (cVar6 == 'r') {
      DAT_00025706 = 0;
      FUN_00016bbc();
      uVar8 = 0;
      FUN_000173e6();
      DAT_00025510 = 0xff;
      DAT_00025312 = 0xff;
    }
    else if (cVar6 == 's') {
      DAT_00025447 = ~DAT_00025447;
      uVar8 = DAT_00025447 == 0;
      if (!(bool)uVar8) {
        (*_thunk_FUN_00011f4e)();
      }
    }
    else if (cVar6 == 'f') {
      DAT_00025446 = ~DAT_00025446;
      uVar8 = DAT_00025446 == 0;
    }
    else if (cVar6 == 'g') {
      uVar8 = 0;
      if (DAT_00024fd4 == 1) {
        (*_thunk_FUN_00011f4e)();
        uVar8 = 0;
        FUN_00018b96();
        FUN_00016d32();
        (*_thunk_FUN_0001174a)();
      }
    }
    else if (cVar6 == 'l') {
      uVar8 = 0;
      if (DAT_00026c9c == 0) {
        (*_thunk_FUN_00011f4e)();
        (*_thunk_FUN_000134ae)();
        (*_thunk_FUN_0001346c)();
        (*_thunk_FUN_00011256)();
        DAT_00026c90 = 0;
        sVar4 = FUN_00018b96();
        uVar8 = sVar4 == 0;
        if ((bool)uVar8) {
          DAT_00026c90 = 1;
          FUN_0001653c();
          (*_thunk_FUN_00018590)();
          (*_thunk_FUN_0001edaa)();
          (*_thunk_FUN_00018806)();
          (*_thunk_FUN_00013252)();
          FUN_0001535a();
          (*_thunk_FUN_00013368)();
          DAT_0002459e = 0;
          DAT_00026c90 = 0;
          uVar8 = 1;
          (*_thunk_FUN_00011386)();
          (*_thunk_FUN_0001174a)();
        }
        else {
          FUN_0001653c();
          (*_thunk_FUN_00013368)();
          FUN_00016d32();
          (*_thunk_FUN_0001174a)();
        }
      }
    }
    else {
      if (cVar6 == 'b') {
                    /* WARNING: Unimplemented instruction - Truncating control flow here */
        halt_unimplemented();
      }
      if (cVar6 == 'c') {
        uVar8 = 0;
        (**(code **)(DAT_00026e6e + -0x48))();
      }
      else {
        if (cVar6 != 'v') break;
        uVar8 = DAT_00027d32 == 0;
        (*_thunk_FUN_00015078)(DAT_00027d34);
        (*_thunk_FUN_0001555a)();
      }
    }
  }
  if (cVar6 == '\x1b') {
    DAT_000254a6 = ~DAT_000254a6;
    uVar8 = DAT_000254a6 == 0;
    if (!(bool)uVar8) {
      (*_thunk_FUN_00011f4e)();
    }
    goto LAB_0001ccfa;
  }
  if (cVar6 == 'o') {
    if (DAT_00025e68 == 1) {
      DAT_00025e68 = 2;
      uVar8 = 0;
      goto LAB_0001ccfa;
    }
  }
  else if (cVar6 == 'l') {
    if (DAT_00025e68 == 2) {
      DAT_00025e68 = 3;
      uVar8 = 0;
      goto LAB_0001ccfa;
    }
  }
  else {
    if (cVar6 != 'n') {
      if (cVar6 == 'i') {
        uVar8 = 1;
        if (DAT_00025e68 == 0) goto LAB_0001ccfa;
        if (DAT_00025e68 == 5) {
          DAT_00025e66 = DAT_00025e66 + 0x32;
          uVar8 = DAT_00025e66 == 0;
          goto LAB_0001ccfa;
        }
        if (DAT_00025e68 == 3) {
          DAT_00025e68 = 4;
          uVar8 = 0;
          goto LAB_0001ccfa;
        }
        DAT_00025e68 = 0;
      }
      if (cVar6 == 'k') {
        uVar8 = 0;
        if (DAT_00025e68 == 5) {
          DAT_00025e66 = DAT_00025e66 + -0x32;
          uVar8 = DAT_00025e66 == 0;
        }
      }
      else if (cVar6 == 'f') {
        uVar8 = 0;
        if (DAT_00025e68 == 5) {
          DAT_00024fd6 = 0x80;
          uVar8 = 0;
        }
      }
      else if (cVar6 == 'p') {
        uVar8 = 0;
        if (DAT_00025e68 == 5) {
          DAT_000252ac = DAT_000252ac + '\x01';
          uVar8 = DAT_000252ac == '\0';
        }
      }
      else if (DAT_00026eaf == 'Y') {
        uVar8 = 0;
        if (DAT_00025e68 == 5) {
          DAT_00025706 = 0;
          uVar8 = 1;
        }
      }
      else if (cVar6 == ' ') {
        uVar8 = 0;
        if (DAT_00025e68 == 5) {
          uVar5 = (**(code **)(DAT_00026ec4 + -0xd8))();
          uVar5 = (**(code **)(iVar3 + -0xd8))(uVar5);
          uVar2 = (**(code **)(iVar3 + -0xd8))(uVar5);
          iVar3 = (**(code **)(iVar3 + -0xd8))(uVar2);
          uVar8 = iVar3 == 0;
          (*_thunk_FUN_00015078)(iVar3);
          (*_thunk_FUN_0001555a)();
        }
      }
      else if (DAT_00026eaf == '_') {
        uVar8 = 0;
        if (DAT_00025e68 == 5) {
          sVar4 = 0;
          puVar7 = &DAT_00025388;
          while (*puVar7 <= DAT_00026dac >> 2) {
            sVar4 = sVar4 + 1;
            puVar7 = puVar7 + 1;
          }
          uVar8 = sVar4 == 0;
          (*_thunk_FUN_00015078)();
          (*_thunk_FUN_0001555a)();
        }
      }
      else if (cVar6 == 'q') {
        uVar8 = DAT_00025e68 == 5;
        if ((bool)uVar8) {
          DAT_00026ed0 = 0xff;
          DAT_00025312 = 0xff;
        }
      }
      else if (cVar6 == 'm') {
        uVar8 = 0;
        if (DAT_00025e68 == 5) {
          if (DAT_000252bd == -1) {
            DAT_000252bd = (&DAT_00024b49)[DAT_000252f4];
            uVar8 = DAT_000252bd == '\0';
            (*_thunk_FUN_0001edbc)();
          }
          else {
            DAT_000252bd = -1;
            uVar8 = 0;
          }
        }
      }
      else if (cVar6 == 'r') {
        uVar8 = DAT_00025e68 == 5;
        if ((bool)uVar8) {
          (*_thunk_FUN_00013756)();
        }
      }
      else {
        if (cVar6 != 'c') {
          if (cVar6 == '8') {
            uVar8 = DAT_00025e68 == 5;
            if (!(bool)uVar8) goto LAB_0001ccfa;
            DAT_000252a0 = DAT_000252a0 + 0x1000;
          }
          else if (cVar6 == '2') {
            uVar8 = DAT_00025e68 == 5;
            if (!(bool)uVar8) goto LAB_0001ccfa;
            DAT_000252a0 = DAT_000252a0 + -0x1000;
          }
          else if (cVar6 == '4') {
            uVar8 = DAT_00025e68 == 5;
            if (!(bool)uVar8) goto LAB_0001ccfa;
            DAT_000252a0 = DAT_000252a0 + -0x100;
          }
          else if (cVar6 == '6') {
            uVar8 = DAT_00025e68 == 5;
            if (!(bool)uVar8) goto LAB_0001ccfa;
            DAT_000252a0 = DAT_000252a0 + 0x100;
          }
          uVar8 = 0;
          if ((cVar6 == 'd') && (uVar8 = 0, DAT_00025e68 == 5)) {
            DAT_00024fda = 0x80;
            DAT_00024fd4 = 0;
            DAT_00026ec2 = ~DAT_00026ec2;
            uVar8 = DAT_00026ec2 == 0;
          }
          goto LAB_0001ccfa;
        }
        if (DAT_00025e68 == 0) {
          DAT_00025e68 = 1;
          uVar8 = 0;
        }
        else {
          uVar8 = 0;
          if (DAT_00025e68 == 5) {
            DAT_000252f4 = DAT_000252f4 + 1;
            uVar8 = 0;
            if (DAT_000252f4 == 3) {
              DAT_000252f4 = 0;
              uVar8 = 1;
            }
          }
        }
      }
      goto LAB_0001ccfa;
    }
    if (DAT_00025e68 == 4) {
      DAT_00025e68 = 5;
      uVar8 = 0;
      goto LAB_0001ccfa;
    }
  }
  DAT_00025e68 = 0;
  uVar8 = 1;
  goto LAB_0001ccfa;
}


// ==== FUN_0001d18c @ 0001d18c ====

undefined2 FUN_0001d18c(undefined2 *param_1)

{
  short local_8;
  undefined2 local_6;
  
  local_6 = 0;
  if ((*(byte *)((int)param_1 + 3) & 0x10) != 0) {
    local_8 = *(short *)(DAT_00027d3c + 2) - param_1[0x10];
    if (local_8 < 0) {
      local_8 = -local_8;
    }
    if (0xa28 < local_8) {
      *param_1 = 0;
      param_1[1] = 0;
      local_6 = 1;
    }
  }
  return local_6;
}


// ==== FUN_0001d1ea @ 0001d1ea ====

void FUN_0001d1ea(void)

{
  undefined4 uVar1;
  short local_8;
  short local_6;
  
  local_6 = 0;
  do {
    uVar1 = FUN_0001cb30(DAT_0002459a,*(undefined4 *)(&DAT_00025ea8 + local_6 * 4));
    *(undefined4 *)(&DAT_00026ede + local_6 * 4) = uVar1;
    uVar1 = FUN_0001cb30(DAT_0002459a,*(undefined4 *)(&DAT_00025f18 + local_6 * 4));
    *(undefined4 *)(&DAT_00026ede + (short)(local_6 + 0x1c) * 4) = uVar1;
    uVar1 = FUN_0001cb30(DAT_00024586,*(undefined4 *)(&DAT_00025f88 + local_6 * 4));
    *(undefined4 *)(&DAT_00026fbe + local_6 * 4) = uVar1;
    uVar1 = FUN_0001cb30(DAT_00024586,*(undefined4 *)(&DAT_00025ff8 + local_6 * 4));
    *(undefined4 *)(&DAT_00026fbe + (short)(local_6 + 0x1c) * 4) = uVar1;
    local_8 = 0;
    do {
      uVar1 = FUN_0001cb30(DAT_0002458a,
                           (int)(short)((local_8 + 0x31) * 0x100) +
                           (*(uint *)(&DAT_00026068 + local_6 * 4) & 0xffff00ff));
      *(undefined4 *)(&DAT_000273ac + (short)(local_6 + local_8 * 0x38) * 4) = uVar1;
      uVar1 = FUN_0001cb30(DAT_0002458a,
                           (int)(short)((local_8 + 0x31) * 0x100) +
                           (*(uint *)(&DAT_000260d8 + local_6 * 4) & 0xffff00ff));
      *(undefined4 *)(&DAT_000273ac + (short)(local_6 + local_8 * 0x38 + 0x1c) * 4) = uVar1;
      local_8 = local_8 + 1;
    } while (local_8 < 3);
    local_6 = local_6 + 1;
  } while (local_6 < 0x1c);
  return;
}


// ==== FUN_0001d35a @ 0001d35a ====

void FUN_0001d35a(int param_1)

{
  undefined2 local_6;
  
  local_6 = *(short *)(param_1 + 0x16);
  if (((*(byte *)(param_1 + 3) & 4) != 0) && (*(short *)(param_1 + 0x16) == 0)) {
    local_6 = 0x1a;
  }
  if (*(short *)(param_1 + 0x14) == -1) {
    *(short *)(param_1 + 0x30) = local_6;
  }
  else {
    *(short *)(param_1 + 0x30) = local_6 + 0x1c;
  }
  return;
}


// ==== FUN_0001d3b4 @ 0001d3b4 ====

void FUN_0001d3b4(int param_1)

{
  ushort uVar1;
  short sVar2;
  
  uVar1 = *(short *)(param_1 + 0x20) - *(short *)(DAT_00027d3c + 2);
  if (*(short *)(DAT_00027d3c + 0x14) == *(short *)(param_1 + 0x14)) {
    *(undefined2 *)(param_1 + 4) = 1;
    if ((-1 < (short)(uVar1 ^ *(ushort *)(DAT_00027d3c + 0x14))) &&
       (*(undefined2 *)(param_1 + 4) = 3, *(short *)(param_1 + 0x10) == 0)) {
      *(undefined2 *)(param_1 + 0x10) = 0x226;
    }
  }
  else {
    *(undefined2 *)(param_1 + 4) = 2;
    if ((short)uVar1 < 0) {
      *(undefined2 *)(param_1 + 4) = 4;
    }
  }
  sVar2 = *(short *)(param_1 + 0x20) - *(short *)(DAT_00027d3c + 2);
  *(short *)(param_1 + 0x28) = sVar2;
  if (sVar2 < 0) {
    *(short *)(param_1 + 0x28) = -*(short *)(param_1 + 0x28);
  }
  return;
}


// ==== FUN_0001d476 @ 0001d476 ====

void FUN_0001d476(void)

{
  short local_a;
  short local_8;
  short local_6;
  
  local_6 = 0;
  do {
    local_8 = 1;
    if (((&DAT_0002517c)[local_6 * 0x1a] != 0) && ((&DAT_0002517e)[local_6 * 0x1a] == 1)) {
      for (local_a = 0; local_a < local_6; local_a = local_a + 1) {
        if ((&DAT_0002517e)[local_a * 0x1a] == 1) {
          if (*(short *)(&DAT_000251a2 + local_a * 0x34) <
              *(short *)(&DAT_000251a2 + local_6 * 0x34)) {
            local_8 = local_8 + 1;
          }
          else {
            (&DAT_00025186)[local_a * 0x1a] = (&DAT_00025186)[local_a * 0x1a] + 1;
          }
        }
      }
      (&DAT_00025186)[local_6 * 0x1a] = local_8;
    }
    local_6 = local_6 + 1;
  } while (local_6 < 4);
  return;
}


// ==== FUN_0001d530 @ 0001d530 ====

void FUN_0001d530(int param_1)

{
  short sVar1;
  
  *(undefined2 *)(param_1 + 0x10) = 0;
  sVar1 = *(short *)(param_1 + 0x32);
  *(short *)(param_1 + 0x32) = *(short *)(param_1 + 0x32) + -1;
  if (sVar1 < 1) {
    *(undefined2 *)(param_1 + 0x32) = 2;
    *(short *)(param_1 + 0x16) = *(short *)(param_1 + 0x16) + 1;
  }
  return;
}


// ==== FUN_0001d562 @ 0001d562 ====

uint FUN_0001d562(int param_1)

{
  short sVar1;
  bool bVar2;
  undefined4 in_D0;
  uint uVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  
  bVar2 = false;
  sVar1 = DAT_00027d3c[6];
  if ((DAT_00027d3c[6] == 0) && ((*(ushort *)(param_1 + 2) & 3) != 0)) {
    *(undefined2 *)(param_1 + 0x24) = *DAT_00027d3c;
  }
  if (((((DAT_0002535e != 0) || (sVar1 == 1)) || (DAT_00027d3c[6] != 0)) ||
      ((*(short *)(param_1 + 0x16) < 0x13 ||
       ((*(short *)(param_1 + 4) != 1 && (*(short *)(param_1 + 4) != 3)))))) ||
     (uVar3 = CONCAT22((short)((uint)in_D0 >> 0x10),*(ushort *)(param_1 + 2)) & 0xffff0003,
     (*(ushort *)(param_1 + 2) & 3) == 0)) {
    uVar3 = FUN_0001d530(param_1);
    if (*(short *)(param_1 + 0x16) < 0x1a) {
      if (*(short *)(param_1 + 0x16) == 0xe) {
        *(short *)(param_1 + 0x14) = -*(short *)(param_1 + 0x14);
        *(short *)(param_1 + 0x16) = *(short *)(param_1 + 0x16) + 1;
      }
      else if (((*(short *)(param_1 + 0x16) == 0x14) &&
               (uVar3 = CONCAT22((short)(uVar3 >> 0x10),*(ushort *)(param_1 + 2)) & 0xffff0003,
               (*(ushort *)(param_1 + 2) & 3) != 0)) && (DAT_00027d3c[6] == 0)) {
        if (*(short *)(param_1 + 0x1a) < 3) {
          uVar4 = (uint)*(short *)(param_1 + 4);
          uVar3 = uVar4;
          if (uVar4 < 5) {
            uVar3 = CONCAT22((short)((uVar4 << 1) >> 0x10),
                             *(undefined2 *)
                              ((int)&switchD_0001d75a::switchdataD_0001d742 +
                              (int)(short)(uVar4 << 1)));
            switch(uVar4) {
            case 1:
              if (((0 < DAT_0002535e) && (DAT_0002535e < 6)) && (*(short *)(param_1 + 0x10) == 0)) {
                iVar5 = (int)(short)(*(short *)(param_1 + 0x28) * 100);
                uVar4 = iVar5 / (int)*(short *)(param_1 + 0x1c);
                uVar3 = iVar5 % (int)*(short *)(param_1 + 0x1c) << 0x10 | uVar4 & 0xffff;
                *(short *)(param_1 + 0x18) = (short)uVar4;
              }
              bVar2 = true;
              break;
            case 2:
              if ((0 < DAT_0002535e) && (DAT_0002535e < 6)) {
                bVar2 = true;
              }
              break;
            case 3:
              bVar2 = true;
              break;
            case 4:
              if (*(short *)(param_1 + 0x10) == 0) {
                iVar6 = (int)(short)(*(short *)(param_1 + 0x28) * 100);
                iVar5 = (int)(short)(DAT_00025364 + *(short *)(param_1 + 0x1c));
                uVar4 = iVar6 / iVar5;
                uVar3 = iVar6 % iVar5 << 0x10 | uVar4 & 0xffff;
                *(short *)(param_1 + 0x18) = (short)uVar4;
              }
              bVar2 = true;
            }
          }
          if (((bVar2) && (sVar1 != 1)) && (*(short *)(param_1 + 0x10) == 0)) {
            sVar1 = *(short *)(param_1 + 0x16) + -0xd;
            uVar3 = CONCAT22((short)(uVar3 >> 0x10),sVar1 * 2);
            *(short *)(param_1 + 0x16) = *(short *)(param_1 + 0x16) + sVar1 * -2;
            *(short *)(param_1 + 0x1a) = *(short *)(param_1 + 0x1a) + 1;
          }
        }
        else {
          *(undefined2 *)(param_1 + 0x1a) = 0;
          *(undefined2 *)(param_1 + 0x10) = 0x226;
        }
      }
    }
    else {
      *(undefined2 *)(param_1 + 0x16) = 0;
      *(byte *)(param_1 + 3) = *(byte *)(param_1 + 3) & 0xf7;
    }
  }
  else {
    *(undefined2 *)(param_1 + 0x16) = 0;
    *(byte *)(param_1 + 3) = *(byte *)(param_1 + 3) & 0xf7;
  }
  return uVar3;
}


// ==== FUN_0001d796 @ 0001d796 ====

uint FUN_0001d796(ushort *param_1)

{
  short sVar2;
  short sVar3;
  uint uVar1;
  int extraout_A0;
  ushort *puVar4;
  
  if (((*param_1 & 0x14) == 0) &&
     (((*(short *)(DAT_00027d3c + 0xc) == 4 || (*(short *)(DAT_00027d3c + 0xc) == 8)) ||
      (*(short *)(DAT_00027d3c + 0xc) == 6)))) {
    param_1[0xf] = 0x6a4;
  }
  FUN_00021ce2(*(undefined4 *)(&DAT_00025a5c + (short)param_1[0xb] * 4));
  FUN_00021cec();
  sVar2 = FUN_00021cc4();
  *(short *)(extraout_A0 + 0x20) = sVar2 + *(short *)(extraout_A0 + 0x20);
  if (((*param_1 & 0x14) == 0) && ((*(byte *)((int)param_1 + 3) & 4) == 0)) {
    if (*(short *)(DAT_00027d3c + 0xc) == 1) {
      param_1[0x12] = 0x46;
    }
    if ((short)param_1[0x12] < 0x21) {
      param_1[0x12] = 0x21;
    }
  }
  sVar2 = param_1[0x12] - param_1[0x13];
  if (sVar2 < 0) {
    sVar2 = -sVar2;
  }
  if (100 < sVar2) {
    sVar2 = 100;
  }
  if ((*param_1 & 4) != 0) {
    if ((short)param_1[0x12] < (short)param_1[0x13]) {
      param_1[0x13] = (short)param_1[0x11] / 100 + param_1[0x13];
      param_1[0x11] = param_1[0x11] - 10;
    }
    else if ((short)param_1[0x13] < (short)param_1[0x12]) {
      param_1[0x13] = param_1[0x12];
    }
  }
  if ((short)param_1[0x12] < (short)param_1[0x13]) {
    puVar4 = param_1;
    sVar3 = FUN_0001cac8();
    puVar4[0x13] = puVar4[0x13] - (sVar3 + *(short *)(&DAT_00026148 + (sVar2 / 0x14) * 2));
  }
  else if ((short)param_1[0x13] < (short)param_1[0x12]) {
    puVar4 = param_1;
    sVar3 = FUN_0001cac8();
    puVar4[0x13] = sVar3 + *(short *)(&DAT_00026148 + (sVar2 / 0x14) * 2) + puVar4[0x13];
  }
  uVar1 = *param_1 & 0xffff0014;
  if ((((*param_1 & 0x14) == 0) && (param_1[0xc] != 0)) &&
     (param_1[0xc] = param_1[0xc] - 1, (short)param_1[0xc] < 1)) {
    *(byte *)((int)param_1 + 3) = *(byte *)((int)param_1 + 3) | 8;
    param_1[0xc] = 0;
  }
  if (((*(byte *)((int)param_1 + 3) & 8) != 0) && (*param_1 == 2)) {
    uVar1 = FUN_0001d562(param_1);
  }
  return uVar1;
}


// ==== FUN_0001d9c6 @ 0001d9c6 ====

void FUN_0001d9c6(int param_1)

{
  short sVar1;
  
  switch(*(undefined2 *)(param_1 + 4)) {
  case 1:
    if (*(short *)(param_1 + 0x28) < 0xa0) {
      if (((DAT_0002535e < 1) || (5 < DAT_0002535e)) ||
         ((DAT_00027d3c[6] == 1 || (*(short *)(param_1 + 0x18) != 0)))) {
        if (((*(short *)(param_1 + 0x28) < 0xa0) && (*(short *)(param_1 + 0x18) == 0)) &&
           (*(short *)(param_1 + 0xc) == 1)) {
          *(ushort *)(param_1 + 2) = *(ushort *)(param_1 + 2) & 8 | 2;
        }
        else {
          *(undefined2 *)(param_1 + 0x12) = 0;
          *(short *)(param_1 + 0x24) = *DAT_00027d3c;
          *(short *)(param_1 + 0x1e) = DAT_00025364 + *(short *)(param_1 + 0xc) * -0x46;
        }
      }
      else {
        *(short *)(param_1 + 0x18) =
             *(short *)(param_1 + 0xc) * 2 +
             (short)(*(short *)(param_1 + 0x28) * 100) / *(short *)(param_1 + 0x1c);
      }
    }
    else if (*(short *)(param_1 + 0x16) == 0) {
      *(short *)(param_1 + 0x1e) = DAT_00025364 + *(short *)(param_1 + 0x28);
      if (*(short *)(param_1 + 0xc) == 1) {
        *(short *)(param_1 + 0x1e) = *(short *)(param_1 + 0xc) * 0x50 + *(short *)(param_1 + 0x1e);
      }
      else {
        *(short *)(param_1 + 0x1e) = *(short *)(param_1 + 0x1e) + *(short *)(param_1 + 0xc) * -0x50;
      }
    }
    break;
  case 2:
    if (((DAT_00027d3c[6] == 0) && (0 < DAT_0002535e)) && (DAT_0002535e < 0xb)) {
      *(undefined2 *)(param_1 + 0x1e) = DAT_00025ea2;
    }
    else {
      *(byte *)(param_1 + 3) = *(byte *)(param_1 + 3) | 8;
    }
    break;
  case 3:
    if (*(short *)(param_1 + 0x28) < 0x600) {
      *(short *)(param_1 + 0x10) = *(short *)(param_1 + 0x10) + -1;
      if ((*(short *)(param_1 + 0x10) < 1) ||
         (((0 < DAT_0002535e && (DAT_0002535e < 6)) || (DAT_00027d3c[6] == 1)))) {
        *(byte *)(param_1 + 3) = *(byte *)(param_1 + 3) | 8;
        *(undefined2 *)(param_1 + 0x10) = 0;
      }
      else if (*(short *)(param_1 + 6) == 1) {
        *(undefined2 *)(param_1 + 6) = 0;
        if (*(short *)(param_1 + 0x18) == 0) {
          sVar1 = FUN_0001cac8();
          *(short *)(param_1 + 0x18) = sVar1 + 8;
        }
        *(undefined2 *)(param_1 + 0x10) = 0x226;
      }
      else {
        *(short *)(param_1 + 0x1e) = DAT_00025364 - *(short *)(param_1 + 0x28) / 4;
        sVar1 = DAT_00027db6 * 0x46;
        DAT_00027db6 = DAT_00027db6 + 1;
        *(short *)(param_1 + 0x1e) = sVar1 + *(short *)(param_1 + 0x1e);
        if (*(short *)(param_1 + 0x26) == *(short *)(param_1 + 0x24)) {
          sVar1 = FUN_0001cac8();
          *(short *)(param_1 + 0x24) = sVar1 * 10 + 0x23;
        }
      }
    }
    else {
      *(byte *)(param_1 + 3) = *(byte *)(param_1 + 3) | 8;
    }
    break;
  case 4:
    if (DAT_00027d3c[6] == 0) {
      *(undefined2 *)(param_1 + 0x1e) = DAT_00025ea2;
      if (*(short *)(param_1 + 0x26) < *DAT_00027d3c) {
        *(short *)(param_1 + 0x24) = *DAT_00027d3c + -0x20;
      }
      else {
        *(short *)(param_1 + 0x24) = *DAT_00027d3c + 0x20;
      }
      *(short *)(param_1 + 0x18) =
           (short)(*(short *)(param_1 + 0x28) * 100) /
           (short)(DAT_00027d3c[0xb] + *(short *)(param_1 + 0x1c));
      *(byte *)(param_1 + 3) = *(byte *)(param_1 + 3) | 8;
    }
  }
  return;
}


// ==== FUN_0001dccc @ 0001dccc ====

void FUN_0001dccc(int param_1)

{
  bool bVar1;
  short *psVar2;
  short sVar3;
  short local_6;
  
  if (*(short *)(param_1 + 4) == 1) {
    if ((DAT_0002535e == 0) && (DAT_00027d3c[6] != 1)) {
      if (*(short *)(param_1 + 0x28) < 0x83) {
        if (*(short *)(param_1 + 0x28) < 0x82) {
          *(short *)(param_1 + 0x1e) = DAT_00025364 + -0x32;
        }
      }
      else {
        *(short *)(param_1 + 0x1e) = DAT_00025364 + 0x32;
      }
    }
    else {
      *(undefined2 *)(param_1 + 2) = 9;
      *(short *)(param_1 + 0x18) = *(short *)(param_1 + 0x28) / (*(short *)(param_1 + 0x1c) / 100);
    }
    *(short *)(param_1 + 0x24) = *DAT_00027d3c;
    local_6 = *DAT_00027d3c - *(short *)(param_1 + 0x26);
    if (local_6 < 0) {
      local_6 = -local_6;
    }
    if ((DAT_00027d3c[6] == 0) && (*(short *)(param_1 + 2) == 2)) {
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
    if (((((bVar1) && (*(short *)(param_1 + 0xc) == 1)) && (local_6 < 8)) &&
        ((*(short *)(param_1 + 0x16) == 0 && (*(short *)(param_1 + 0x28) < 0xa0)))) &&
       ((DAT_00027d3c[10] == *(short *)(param_1 + 0x14) &&
        ((short)(*(short *)(param_1 + 0x20) - DAT_00027d3c[1] ^ DAT_00027d3c[10]) < 0)))) {
      *(undefined2 *)(param_1 + 0x12) = 1;
      psVar2 = DAT_00027d3c;
      if (((DAT_00026ec2 == 0) && (*(short *)(param_1 + 0x26) == *DAT_00027d3c)) &&
         ((DAT_00027296 != 0 && (DAT_00027d3c[8] = DAT_00027d3c[8] + -1, psVar2[8] < 1)))) {
        DAT_00027d3c[9] = DAT_00027d3c[9] + -8;
        psVar2 = DAT_00027d3c;
        sVar3 = FUN_0001cac8();
        psVar2[7] = psVar2[7] - sVar3;
        psVar2 = DAT_00027d3c;
        sVar3 = FUN_0001cac8();
        psVar2[8] = sVar3 + 6;
      }
    }
    else {
      *(undefined2 *)(param_1 + 0x12) = 0;
    }
  }
  else {
    *(undefined2 *)(param_1 + 2) = 1;
  }
  return;
}


// ==== FUN_0001dea4 @ 0001dea4 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0001dea4(undefined2 *param_1)

{
  bool bVar1;
  short sVar2;
  
  bVar1 = false;
  if (param_1[2] == 3) {
    if (param_1[3] == 1) {
      param_1[3] = 0;
      if (param_1[0xc] == 0) {
        sVar2 = FUN_0001cac8();
        param_1[0xc] = sVar2 + 8;
      }
      param_1[8] = 0x113;
    }
    if (0x96 < (short)param_1[0x14]) {
      param_1[0x14] = 0xf0;
    }
    if (((short)param_1[0x14] < 0x96) &&
       (param_1[0x14] = param_1[0x14] + -0x96, param_1[0x13] == param_1[0x12])) {
      sVar2 = FUN_0001cac8();
      param_1[0x12] = sVar2 * 10 + 0x23;
    }
    param_1[0xf] = DAT_00025364 - param_1[0x14];
  }
  else if ((param_1[10] == -1) && ((short)param_1[0x10] < (short)(DAT_0002534c + -500))) {
    *(byte *)((int)param_1 + 3) = *(byte *)((int)param_1 + 3) | 8;
  }
  else if ((param_1[10] == 1) && ((short)(DAT_0002534e + 500) < (short)param_1[0x10])) {
    *(byte *)((int)param_1 + 3) = *(byte *)((int)param_1 + 3) | 8;
  }
  if (((param_1[10] == -1) && (DAT_0002534e < (short)param_1[0x10])) &&
     ((short)(param_1[0x10] - DAT_0002534e) < 1000)) {
    param_1[0x12] = 0x14;
  }
  else if (((param_1[10] == 1) && ((short)param_1[0x10] < DAT_0002534c)) &&
          ((short)(DAT_0002534c - param_1[0x10]) < 1000)) {
    param_1[0x12] = 0x14;
  }
  if (((param_1[10] == -1) && (DAT_0002534e < (short)param_1[0x10])) ||
     ((param_1[10] == 1 && ((short)param_1[0x10] < DAT_0002534c)))) {
    bVar1 = true;
  }
  if (bVar1) {
    if ((param_1[0x13] == 0x14) && (param_1[0xb] == 0)) {
      DAT_00025506 = 2;
      DAT_000254f6 = 0;
      DAT_000254f2 = (short)param_1[0xe] * 0x28f;
      _DAT_000254e8 = (int)(short)(param_1[0x13] + 0xf) << 0x10;
      _DAT_000254e4 = (int)(short)param_1[0x10] << 0x10;
      DAT_00025503 = *(char *)((int)param_1 + 0x15);
      if (DAT_00025503 == -1) {
        DAT_000254f2 = (short)param_1[0xe] * -0x28f;
      }
      DAT_00025504._0_1_ = 0xff;
      DAT_00025502 = 0;
      *param_1 = 2;
      param_1[0xf] = DAT_00025ea4 / 2;
      param_1[0x12] = 0x3c;
      param_1[1] = 0x10;
      DAT_00024fe4 = 500;
    }
  }
  else {
    param_1[8] = param_1[8] + -1;
    if ((short)param_1[8] < 1) {
      *(byte *)((int)param_1 + 3) = *(byte *)((int)param_1 + 3) | 8;
      param_1[8] = 0;
    }
  }
  return;
}


// ==== FUN_0001e17a @ 0001e17a ====

void FUN_0001e17a(int param_1)

{
  short sVar1;
  int iVar2;
  
  sVar1 = FUN_0001d18c(param_1);
  if ((sVar1 == 0) && (*(short *)(param_1 + 0x16) == 0)) {
    if (*(short *)(param_1 + 4) == 3) {
      if (*(short *)(param_1 + 6) == 1) {
        *(undefined2 *)(param_1 + 6) = 0;
        if (*(short *)(param_1 + 0x18) == 0) {
          iVar2 = param_1;
          sVar1 = FUN_0001cac8();
          *(short *)(iVar2 + 0x18) = sVar1 + 8;
        }
        *(undefined2 *)(param_1 + 0x10) = 0x226;
      }
      else if ((*(short *)(param_1 + 0x26) == *(short *)(param_1 + 0x24)) &&
              (*(short *)(param_1 + 0x28) < 0xa0)) {
        sVar1 = FUN_0001cac8();
        *(short *)(param_1 + 0x24) = sVar1 * 10 + 0x19;
      }
    }
    else if (*(short *)(param_1 + 4) == 1) {
      *(byte *)(param_1 + 3) = *(byte *)(param_1 + 3) | 8;
    }
  }
  return;
}


// ==== FUN_0001e244 @ 0001e244 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0001e244(undefined2 *param_1)

{
  ushort uVar2;
  uint uVar1;
  short sVar3;
  undefined2 uVar4;
  
  sVar3 = 0x80 - param_1[4];
  uVar2 = (*_thunk_FUN_000203be)();
  if ((short)(uVar2 & 0x3f) < sVar3) {
    FUN_0001cae0(((short)(0x80 - param_1[4]) >> 3) + 1,param_1[0x13] + 10);
  }
  if (param_1[0x13] == param_1[0x12]) {
    uVar1 = FUN_0001c982();
    uVar4 = (undefined2)uVar1;
    sVar3 = FUN_0001cb74(uVar4);
    if ((sVar3 != 0) && ((short)param_1[0xe] < 300)) {
      DAT_00026be6 = DAT_00026be6 + 1;
      if (1 < DAT_00026be6) {
        DAT_00026be6 = 0;
        param_1[0x12] = param_1[0x12] + -1;
      }
      param_1[0xe] = param_1[0xe] + 0x18;
    }
    param_1[0xe] = param_1[0xe] + -0x23;
    (*_thunk_FUN_00011a84)(0x14);
    if (500 < (short)param_1[0xe]) {
      (*_thunk_FUN_000146c6)(uVar4);
    }
    (*_thunk_FUN_000152ac)(param_1[0x13] + 3);
    if ((short)param_1[0xe] < 100) {
      DAT_000252cf = DAT_000252cf + '\x01';
      sVar3 = FUN_0001cbb2(uVar4);
      if (((sVar3 == 0) || (uVar1 < DAT_00024578)) || (DAT_0002457c <= uVar1)) {
        if ((param_1[1] != 4) && (param_1[1] != 0x10)) {
          DAT_00025126 = DAT_00025126 + -1;
        }
        *param_1 = 0;
        param_1[1] = 0;
      }
      else {
        *param_1 = 0x10;
        param_1[0xf] = 6;
        param_1[0xe] = 0x1e;
        param_1[1] = 0;
      }
    }
  }
  return;
}


// ==== FUN_0001e3e8 @ 0001e3e8 ====

uint FUN_0001e3e8(undefined2 *param_1)

{
  uint uVar1;
  int iVar2;
  
  if (param_1[10] == -1) {
    param_1[0x18] = 0x1b;
  }
  else {
    param_1[0x18] = 0x37;
  }
  param_1[0xe] = param_1[0xe] + -1;
  if (param_1[0xe] == 0) {
    param_1[0xf] = param_1[0xf] + -1;
    param_1[0xe] = param_1[0xf] * 5;
  }
  if ((short)param_1[0xf] < 2) {
    iVar2 = (int)DAT_00025128;
    uVar1 = iVar2 * 2;
    DAT_00025128 = DAT_00025128 + 1;
    (&DAT_0002512a)[iVar2] = param_1[10] * param_1[0x10];
    if ((param_1[1] != 4) && (param_1[1] != 0x10)) {
      DAT_00025126 = DAT_00025126 + -1;
    }
    *param_1 = 0;
    param_1[1] = 0;
  }
  else {
    uVar1 = (ushort)param_1[0xe] & 0xffff0003;
    if ((param_1[0xe] & 3) == 0) {
      uVar1 = FUN_0001cae0(param_1[0xf],6);
    }
  }
  return uVar1;
}


// ==== FUN_0001e4c8 @ 0001e4c8 ====

void FUN_0001e4c8(void)

{
  return;
}


// ==== FUN_0001e4d0 @ 0001e4d0 ====

void FUN_0001e4d0(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  bool bVar2;
  short sVar3;
  short sVar4;
  
  sVar4 = -1;
  bVar2 = false;
  for (sVar3 = 0; sVar3 < 4; sVar3 = sVar3 + 1) {
    if ((&DAT_0002517a)[sVar3 * 0x1a] == 0) {
      sVar4 = sVar3;
    }
    if (((*(byte *)((int)&DAT_0002517c + sVar3 * 0x34 + 1) & 4) != 0) &&
       ((&DAT_0002517a)[sVar3 * 0x1a] != 0)) {
      bVar2 = true;
    }
  }
  if ((sVar4 != -1) && (((param_1._0_2_ != 0 && (!bVar2)) || (param_1._0_2_ == 0)))) {
    iVar1 = (int)sVar4;
    (&DAT_0002517a)[iVar1 * 0x1a] = 2;
    (&DAT_0002518e)[iVar1 * 0x1a] = param_2._2_2_;
    (&DAT_0002519a)[iVar1 * 0x1a] = param_1._2_2_;
    (&DAT_0002519e)[iVar1 * 0x1a] = 0x32;
    (&DAT_00025198)[iVar1 * 0x1a] = DAT_00025ea2;
    (&DAT_00025196)[iVar1 * 0x1a] = DAT_00025ea2;
    (&DAT_00025182)[iVar1 * 0x1a] = 0xf0;
    sVar3 = FUN_0001cac8();
    (&DAT_00025184)[iVar1 * 0x1a] = sVar3 + 5;
    (&DAT_00025180)[iVar1 * 0x1a] = 0;
    (&DAT_0002517e)[iVar1 * 0x1a] = 0;
    (&DAT_00025192)[iVar1 * 0x1a] = 0;
    (&DAT_00025190)[iVar1 * 0x1a] = 0;
    (&DAT_00025186)[iVar1 * 0x1a] = 0;
    if (param_1._0_2_ == 0) {
      DAT_00025126 = DAT_00025126 + 1;
      (&DAT_0002517c)[iVar1 * 0x1a] = 1;
      (&DAT_000251a0)[iVar1 * 0x1a] = param_2._0_2_;
    }
    else {
      (&DAT_0002517c)[iVar1 * 0x1a] = 4;
      (&DAT_000251a0)[iVar1 * 0x1a] = 0x32;
    }
  }
  return;
}


// ==== FUN_0001e608 @ 0001e608 ====

void FUN_0001e608(void)

{
  undefined2 *local_10;
  ushort local_8;
  short local_6;
  
  local_6 = 0;
  do {
    local_10 = &DAT_0002517a + local_6 * 0x1a;
    for (local_8 = 0; local_8 < 0x34; local_8 = local_8 + 1) {
      *(undefined1 *)local_10 = 0;
      local_10 = (undefined2 *)((int)local_10 + 1);
    }
    local_6 = local_6 + 1;
  } while (local_6 < 4);
  return;
}


// ==== FUN_0001e64e @ 0001e64e ====

void FUN_0001e64e(short *param_1)

{
  if (*param_1 == 2) {
    if (param_1[0xf] < DAT_00025ea2) {
      param_1[0xf] = DAT_00025ea2;
    }
    if (DAT_00025ea4 < param_1[0xf]) {
      param_1[0xf] = DAT_00025ea4;
    }
    if (param_1[0xe] < param_1[0xf]) {
      param_1[0xe] = (short)(param_1[0xf] - param_1[0xe]) / 2 + 5 + param_1[0xe];
      if (DAT_00025ea4 < param_1[0xe]) {
        param_1[0xe] = DAT_00025ea4;
      }
    }
    else if ((param_1[0xf] < param_1[0xe]) &&
            (param_1[0xe] = param_1[0xe] - ((short)(param_1[0xe] - param_1[0xf]) / 2 + -5),
            param_1[0xe] < DAT_00025ea2)) {
      param_1[0xe] = DAT_00025ea2;
    }
  }
  return;
}


// ==== FUN_0001e728 @ 0001e728 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_0001e728(int param_1)

{
  ushort uVar2;
  int iVar1;
  short sVar3;
  undefined2 uVar4;
  
  sVar3 = 0x80 - *(short *)(param_1 + 8);
  uVar2 = (*_thunk_FUN_000203be)();
  if ((short)(uVar2 & 0x3f) < sVar3) {
    FUN_0001cae0(((short)(0x80 - *(short *)(param_1 + 8)) >> 3) + 1,*(short *)(param_1 + 0x26) + 0xb
                );
  }
  iVar1 = (int)(short)(*(ushort *)(param_1 + 2) & 0xfff7);
  uVar4 = (undefined2)param_1;
  if (iVar1 == 1) {
    iVar1 = FUN_0001d9c6(uVar4);
  }
  else if (iVar1 == 2) {
    iVar1 = FUN_0001dccc(uVar4);
  }
  else if (iVar1 == 4) {
    iVar1 = FUN_0001dea4(uVar4);
  }
  else {
    iVar1 = iVar1 + -0x10;
    if (iVar1 == 0) {
      iVar1 = FUN_0001e17a(uVar4);
    }
  }
  return iVar1;
}


// ==== FUN_0001e7d6 @ 0001e7d6 ====

void FUN_0001e7d6(void)

{
  short sVar1;
  short *psVar2;
  int iVar3;
  short sVar4;
  
  DAT_00027db6 = 0;
  sVar4 = 0;
  do {
    iVar3 = (int)sVar4;
    psVar2 = &DAT_0002517a + iVar3 * 0x1a;
    if (*psVar2 != 0) {
      FUN_0001d3b4(psVar2);
      FUN_0001d476();
      sVar1 = *psVar2;
      if (sVar1 == 1) {
        FUN_0001e4c8(psVar2);
      }
      else if (sVar1 == 2) {
        FUN_0001e728(psVar2);
        if (((*(byte *)((int)&DAT_0002517c + iVar3 * 0x34 + 1) & 4) == 0) &&
           ((short)(&DAT_0002519e)[iVar3 * 0x1a] < 0x21)) {
          (&DAT_0002519e)[iVar3 * 0x1a] = 0x21;
        }
      }
      else if (sVar1 == 4) {
        FUN_0001e244(psVar2);
      }
      else if ((sVar1 != 8) && (sVar1 == 0x10)) {
        FUN_0001e3e8(psVar2);
      }
      FUN_0001e64e(psVar2);
      if (*psVar2 != 0x10) {
        FUN_0001d796(psVar2);
      }
      FUN_0001d35a(psVar2);
    }
    sVar4 = sVar4 + 1;
  } while (sVar4 < 4);
  return;
}


// ==== FUN_0001e8b8 @ 0001e8b8 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_0001e8b8(void)

{
  short sVar1;
  undefined4 *puVar2;
  
  if (DAT_00027db8 == 0) {
    DAT_00027dba = 0;
    sVar1 = 3;
    puVar2 = &DAT_00027dbe;
    do {
      *puVar2 = 0;
      *(undefined2 *)(puVar2 + 2) = 0;
      *(undefined4 *)((int)puVar2 + 0x16) = 0xffffffff;
      puVar2[1] = 0;
      puVar2 = (undefined4 *)((int)puVar2 + 0x1e);
      sVar1 = sVar1 + -1;
    } while (sVar1 != -1);
    _DAT_00dff096 = 0xf;
    _DAT_00dff09e = 0xff;
    DAT_00027e36 = _DAT_00000070;
    _DAT_00000070 = FUN_0001ebaa;
    _DAT_00dff09c = 0x780;
    _DAT_00dff09a = 0x8780;
    DAT_00027e42 = 2;
    DAT_00027e43 = 0x1e;
    DAT_00027e44 = s_SoundFX_IntHandler_00026154;
    DAT_00027e4c = &LAB_0001ec64;
    (**(code **)(DAT_00026ec4 + -0xa8))();
    DAT_00027db8 = 1;
  }
  return 0;
}


// ==== FUN_0001e94c @ 0001e94c ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_0001e94c(void)

{
  if (DAT_00027db8 != 0) {
    (*_thunk_FUN_0001eab4)();
    (**(code **)(DAT_00026e6e + -0xc6))();
    (**(code **)(DAT_00026ec4 + -0xae))();
    _DAT_00dff09a = 0x780;
    _DAT_00dff096 = 0xf;
    _DAT_00000070 = DAT_00027e36;
    DAT_00027db8 = 0;
  }
  return 0;
}


// ==== FUN_0001e992 @ 0001e992 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_0001e992(void)

{
  undefined4 uVar1;
  int in_A0;
  
  if (in_A0 == 0) {
    uVar1 = 0xffffffff;
  }
  else {
    (*_thunk_FUN_0001ea28)();
    uVar1 = 0;
  }
  return uVar1;
}


// ==== FUN_0001e9de @ 0001e9de ====

undefined4 FUN_0001e9de(void)

{
  undefined4 in_D0;
  
  do {
    if (DAT_00027e64 < '\0') {
      return in_D0;
    }
  } while (DAT_00bfe0ff < '\0');
  return in_D0;
}


// ==== FUN_0001e9f4 @ 0001e9f4 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 FUN_0001e9f4(void)

{
  undefined4 in_D0;
  undefined4 in_D1;
  
  DAT_00027e64 = 0;
  DAT_00027e65 = 0xff;
  (*_thunk_FUN_0001eac0)();
  (**(code **)(DAT_00026e6e + -0xc6))();
  DAT_00027e66 = 0;
  return CONCAT44(in_D0,in_D1);
}


// ==== FUN_0001ea18 @ 0001ea18 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0001ea18(void)

{
  (*_thunk_FUN_0001eac0)();
  DAT_00027e65 = 0;
  DAT_00027e66 = 0;
  return;
}


// ==== FUN_0001ea28 @ 0001ea28 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_0001ea28(void)

{
  int iVar1;
  uint in_D0;
  short sVar2;
  undefined4 in_D1;
  short extraout_D1w;
  short extraout_D1w_00;
  short sVar3;
  undefined2 unaff_D2w;
  undefined2 unaff_D3w;
  undefined2 unaff_D4w;
  int in_A0;
  undefined4 extraout_A0;
  undefined4 extraout_A0_00;
  undefined4 uVar4;
  
  if (in_A0 != 0) {
    if ((short)in_D1 == 6) {
      FUN_0001e9f4();
    }
    sVar2 = (*_thunk_FUN_0001eb2e)();
    uVar4 = extraout_A0;
    sVar3 = extraout_D1w;
    if (sVar2 != 0) {
      (*_thunk_FUN_0001eac0)();
      uVar4 = extraout_A0_00;
      sVar3 = extraout_D1w_00;
    }
    _DAT_00dff09c = (ushort)(1 << ((ushort)(sVar3 + 7) & 0x1f));
    _DAT_00dff09a = _DAT_00dff09c | 0x8000;
    iVar1 = (int)(short)(sVar3 * 0x1e);
    *(short *)((int)&DAT_00027dc8 + iVar1) = (short)(in_D0 >> 1);
    *(undefined2 *)((int)&DAT_00027dca + iVar1) = unaff_D2w;
    *(undefined2 *)((int)&DAT_00027dcc + iVar1) = unaff_D3w;
    *(undefined2 *)((int)&DAT_00027dcc + iVar1 + 2) = 0;
    *(undefined2 *)((int)&DAT_00027dd0 + iVar1) = unaff_D4w;
    *(undefined4 *)((int)&DAT_00027dbe + iVar1) = uVar4;
    *(undefined4 *)((int)&DAT_00027dd4 + iVar1) = 0xffffffff;
    *(undefined2 *)((int)&DAT_00027dc6 + iVar1) = 1;
  }
  return in_D1;
}


// ==== FUN_0001eab4 @ 0001eab4 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0001eab4(void)

{
  short sVar1;
  
  do {
    sVar1 = (*_thunk_FUN_0001eac0)();
  } while (sVar1 != 0);
  return;
}


// ==== FUN_0001eac0 @ 0001eac0 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 FUN_0001eac0(void)

{
  int iVar1;
  short sVar2;
  uint in_D0;
  undefined4 in_D1;
  
  sVar2 = (short)in_D0;
  iVar1 = (int)(short)(sVar2 * 0x1e);
  _DAT_00dff09a = 0x80 << (in_D0 & 0x3f);
  *(undefined2 *)((int)&DAT_00027dc6 + iVar1) = 0;
  _DAT_00dff096 = 1 << (in_D0 & 0x3f);
  *(undefined4 *)((int)&DAT_00027dbe + iVar1) = 0;
  *(undefined2 *)((int)&DAT_00027dd2 + iVar1) = 0xffff;
  *(undefined4 *)((int)&DAT_00027dd4 + iVar1) = 0xffffffff;
  *(undefined2 *)(&DAT_00dff0a8 + (short)(sVar2 << 4)) = 0;
  *(undefined4 *)((int)&DAT_00027dc2 + iVar1) = DAT_00027dba;
  *(undefined2 *)(&DAT_00dff0a6 + (short)(sVar2 << 4)) = 0x7c;
  if (sVar2 == 2) {
    DAT_00027e66 = 0;
  }
  return CONCAT44(in_D0,in_D1);
}


// ==== FUN_0001eb2e @ 0001eb2e ====

undefined8 FUN_0001eb2e(void)

{
  undefined4 uVar1;
  undefined4 in_D1;
  
  uVar1 = 0;
  if (*(int *)((int)&DAT_00027dbe + (int)(short)((short)in_D1 * 0x1e)) != 0) {
    uVar1 = 0xffffffff;
  }
  return CONCAT44(uVar1,in_D1);
}


// ==== FUN_0001eb4c @ 0001eb4c ====

void FUN_0001eb4c(void)

{
  int iVar1;
  short in_D0w;
  short in_D1w;
  short unaff_D2w;
  
  iVar1 = (int)(short)(in_D0w * 0x1e);
  if (-1 < in_D1w) {
    *(short *)(&DAT_00dff0a6 + (short)(in_D0w << 4)) = in_D1w;
  }
  if (-1 < unaff_D2w) {
    *(undefined4 *)((int)&DAT_00027dd4 + iVar1) = 0xffffffff;
    *(short *)((int)&DAT_00027dcc + iVar1) = unaff_D2w;
    *(undefined2 *)((int)&DAT_00027dcc + iVar1 + 2) = 0;
    *(short *)(&DAT_00dff0a8 + (short)(in_D0w << 4)) = unaff_D2w;
  }
  return;
}


// ==== FUN_0001ebaa @ 0001ebaa ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 FUN_0001ebaa(void)

{
  short sVar1;
  ushort uVar2;
  undefined4 in_D0;
  undefined4 in_D1;
  uint uVar3;
  short sVar4;
  short sVar5;
  uint uVar6;
  int *piVar7;
  undefined1 *puVar8;
  
  *(undefined4 *)(&DAT_00026168 + (short)(DAT_00027e68 * 4)) = DAT_00027e6a;
  piVar7 = &DAT_00027dbe;
  puVar8 = &DAT_00dff0a0;
  uVar2 = _DAT_00dff01c & _DAT_00dff01e;
  uVar3 = 7;
  sVar4 = 1;
  sVar5 = 3;
  uVar6 = 0;
  do {
    if ((CONCAT22((short)((uint)in_D0 >> 0x10),uVar2) & 0xffff0780 & 1 << (uVar3 & 0x1f)) != 0) {
      if ((*piVar7 == 0) ||
         ((-1 < *(short *)(piVar7 + 5) &&
          (sVar1 = *(short *)(piVar7 + 5), *(short *)(piVar7 + 5) = sVar1 + -1, sVar1 < 1)))) {
        if (sVar5 == 1) {
          DAT_00027e66 = 0;
        }
        uVar6 = uVar6 | 1 << (uVar3 & 0x1f);
        _DAT_00dff096 = sVar4;
        *(undefined4 *)((int)piVar7 + 0x16) = 0xffffffff;
        *(undefined2 *)(puVar8 + 8) = 0;
        *(undefined4 *)((int)piVar7 + 0xe) = 0;
        piVar7[1] = DAT_00027dba;
        *piVar7 = 0;
      }
      uVar6 = uVar6 | 1 << (uVar3 & 0x1f);
    }
    uVar3 = (uint)(ushort)((short)uVar3 + 1);
    sVar4 = sVar4 << 1;
    piVar7 = (int *)((int)piVar7 + 0x1e);
    puVar8 = puVar8 + 0x10;
    sVar5 = sVar5 + -1;
  } while (sVar5 != -1);
  if ((short)uVar6 != 0) {
    _DAT_00dff09c = (short)uVar6;
  }
  _DAT_00dff09a = 0xc000;
  return CONCAT44(in_D0,in_D1);
}


// ==== FUN_0001ed7a @ 0001ed7a ====

void FUN_0001ed7a(void)

{
  undefined1 *in_A0;
  
  *in_A0 = 0xff;
  in_A0[2] = 0xff;
  in_A0[4] = 0xff;
  in_A0[6] = 0xff;
  in_A0[8] = 0xff;
  in_A0[10] = 0xff;
  in_A0[0xc] = 0xff;
  in_A0[0xe] = 0xff;
  in_A0[0x10] = 0xff;
  DAT_00027ea8 = 0x3c;
  DAT_00027eaa = 0x54;
  return;
}


// ==== FUN_0001edaa @ 0001edaa ====

void FUN_0001edaa(void)

{
  FUN_0001ed7a();
  FUN_0001ed7a();
  return;
}


// ==== FUN_0001edbc @ 0001edbc ====

void FUN_0001edbc(void)

{
  DAT_00027e7a = (DAT_000252bd / 10) * -8 + 0x50;
  DAT_00027e7c = ((ushort)DAT_000252bd % 10) * -8 + 0x50;
  DAT_00027e8a = 0xff;
  DAT_00027e9e = 0xff;
  return;
}


// ==== FUN_0001edea @ 0001edea ====

void FUN_0001edea(void)

{
  ushort uVar1;
  byte bVar2;
  
  bVar2 = DAT_000252ac;
  if ((char)DAT_000252ac < '\0') {
    bVar2 = 0;
  }
  uVar1 = (ushort)bVar2;
  if (9 < bVar2) {
    uVar1 = 9;
  }
  DAT_00027e7e = uVar1 * -8 + 0x59;
  DAT_00027e8c = 0xff;
  DAT_00027ea0 = 0xff;
  return;
}


// ==== FUN_0001ee16 @ 0001ee16 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_0001ee16(void)

{
  short sVar1;
  bool bVar2;
  short sVar3;
  ushort uVar4;
  byte bVar5;
  short sVar6;
  ushort uVar7;
  
  sVar1 = *DAT_00026d7c;
  (*_thunk_FUN_000212ce)();
  (*_thunk_FUN_0001f2dc)();
  DAT_00027eac = CONCAT11(0xff,(undefined1)DAT_00027eac);
  if (((DAT_00024fd4 != 0) && (DAT_00024fd4 != 1)) && (DAT_00024fd4 != 7)) {
    DAT_00027eac = 0;
  }
  FUN_0001f21a();
  sVar6 = DAT_00024fda - 0x60;
  if ((short)DAT_00024fda < 0x60) {
    sVar6 = 0;
  }
  uVar7 = sVar6 * 2 & 0xfffc;
  if ((DAT_00024fd4 < 2) && (DAT_00027d38 != 0)) {
    uVar7 = uVar7 + 0x18;
  }
  if (uVar7 != DAT_00027ea8) {
    if ((short)uVar7 < (short)DAT_00027ea8) {
      DAT_00027ea8 = DAT_00027ea8 - 4;
    }
    else {
      DAT_00027ea8 = DAT_00027ea8 + 4;
    }
  }
  uVar7 = DAT_00027ea8;
  sVar6 = 0xc;
  if ((DAT_00027eac != 0) && (DAT_00024fda < 0x74)) {
    sVar6 = 0x10;
    sVar3 = DAT_00027eae + -1;
    bVar2 = DAT_00027eae < 1;
    DAT_00027eae = sVar3;
    if ((sVar3 == 0 || bVar2) && (sVar6 = 0xc, sVar3 != 0)) {
      DAT_00027eae = 10;
    }
  }
  if ((sVar6 != *(short *)(&DAT_00027e80 + sVar1)) ||
     (DAT_00027ea8 != *(ushort *)(&DAT_00027e82 + sVar1))) {
    *(short *)(&DAT_00027e80 + sVar1) = sVar6;
    *(ushort *)(&DAT_00027e82 + sVar1) = uVar7;
    (*_thunk_FUN_00020ce2)();
    (*_thunk_FUN_00020ce2)();
    (*_thunk_FUN_00020ce2)();
  }
  uVar7 = DAT_00024fd6;
  if ((short)DAT_00024fd6 < 0) {
    uVar7 = 0;
  }
  uVar7 = uVar7 >> 1;
  if (0x58 < uVar7) {
    uVar7 = 0x58;
  }
  uVar7 = uVar7 & 0xfffc;
  if ((uVar7 == 0) && (DAT_00027eac != 0)) {
    uVar7 = (*_thunk_FUN_000203be)();
    uVar7 = uVar7 >> 0xd & 4;
  }
  if (uVar7 != DAT_00027eaa) {
    if ((short)uVar7 < (short)DAT_00027eaa) {
      DAT_00027eaa = DAT_00027eaa - 4;
    }
    else {
      DAT_00027eaa = DAT_00027eaa + 4;
    }
  }
  uVar7 = DAT_00027eaa;
  sVar6 = 0xc;
  if ((DAT_00027eac != 0) && ((short)DAT_00024fd6 < 0x41)) {
    sVar6 = 0x10;
    sVar3 = DAT_00027eb0 + -1;
    bVar2 = DAT_00027eb0 < 1;
    DAT_00027eb0 = sVar3;
    if ((sVar3 == 0 || bVar2) && (sVar6 = 0xc, sVar3 != 0)) {
      DAT_00027eb0 = 8;
    }
  }
  if ((sVar6 != *(short *)(&DAT_00027e84 + sVar1)) ||
     (DAT_00027eaa != *(ushort *)(&DAT_00027e86 + sVar1))) {
    *(short *)(&DAT_00027e84 + sVar1) = sVar6;
    *(ushort *)(&DAT_00027e86 + sVar1) = uVar7;
    (*_thunk_FUN_00020ce2)();
    (*_thunk_FUN_00020ce2)();
    (*_thunk_FUN_00020ce2)();
  }
  if (DAT_000252f4 != *(short *)(&DAT_00027e88 + sVar1)) {
    *(short *)(&DAT_00027e88 + sVar1) = DAT_000252f4;
    (*_thunk_FUN_00020b0c)();
  }
  if ((DAT_000252bd == 0xff) || ((ushort)DAT_000252bd != *(ushort *)(&DAT_00027e8a + sVar1))) {
    sVar6 = -1;
    uVar7 = (ushort)DAT_000252bd;
    do {
      uVar4 = uVar7;
      sVar6 = sVar6 + 1;
      uVar7 = uVar4 - 10;
    } while (9 < uVar4);
    uVar7 = uVar4 * -8 + 0x50;
    uVar4 = sVar6 * -8 + 0x50;
    if (DAT_000252bd == 0xff) {
      uVar7 = 100;
      uVar4 = 100;
    }
    if ((DAT_00027e7a == uVar4) && (DAT_00027e7c == uVar7)) {
      *(ushort *)(&DAT_00027e8a + sVar1) = (ushort)DAT_000252bd;
    }
    else {
      DAT_00027e7c = DAT_00027e7c + 1;
      if (0x50 < DAT_00027e7c) {
        DAT_00027e7c = 1;
      }
      if (((DAT_00027e7a != uVar4) && (DAT_00027e7c < 9)) &&
         (DAT_00027e7a = DAT_00027e7a + 1, 0x50 < DAT_00027e7a)) {
        DAT_00027e7a = 1;
      }
    }
    DAT_000268ac = 0x13;
    DAT_000268ae = 0x1c;
    (*_thunk_FUN_00020ce2)();
    (*_thunk_FUN_00020ce2)();
  }
  bVar5 = DAT_000252ac;
  if ((char)DAT_000252ac < '\0') {
    bVar5 = 0;
  }
  uVar7 = (ushort)bVar5;
  if (9 < bVar5) {
    uVar7 = 9;
  }
  if (uVar7 != *(ushort *)(&DAT_00027e8c + sVar1)) {
    sVar6 = uVar7 * -8 + 0x59;
    if (sVar6 == DAT_00027e7e) {
      *(ushort *)(&DAT_00027e8c + sVar1) = uVar7;
    }
    else if (sVar6 < DAT_00027e7e) {
      DAT_00027e7e = DAT_00027e7e + -1;
    }
    else {
      DAT_00027e7e = DAT_00027e7e + 1;
    }
    DAT_000268ac = 0x13;
    DAT_000268ae = 0x1c;
    (*_thunk_FUN_00020ce2)();
  }
  if (DAT_0002529c != *(int *)(&DAT_00027e90 + sVar1)) {
    *(int *)(&DAT_00027e90 + sVar1) = DAT_0002529c;
    FUN_0001f26a();
  }
  uVar7 = (ushort)DAT_000252cf;
  if (99 < uVar7) {
    uVar7 = 99;
  }
  if (uVar7 != *(ushort *)(&DAT_00027e8e + sVar1)) {
    *(ushort *)(&DAT_00027e8e + sVar1) = uVar7;
    DAT_000268ac = 0x14;
    DAT_000268ae = 0x1c;
    FUN_0001f2b0();
    FUN_0001f2b0();
    DAT_000268ac = 0x13;
    DAT_000268ae = 0x1f;
    FUN_0001f200();
    FUN_0001f200();
  }
  (*_thunk_FUN_000212d4)();
  return 0;
}


// ==== FUN_0001f200 @ 0001f200 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0001f200(void)

{
  short unaff_D2w;
  
  for (; 0 < unaff_D2w; unaff_D2w = unaff_D2w + -1) {
    (*_thunk_FUN_00020ce2)();
  }
  return;
}


// ==== FUN_0001f21a @ 0001f21a ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0001f21a(void)

{
  short sVar1;
  short *psVar2;
  
  psVar2 = &DAT_0002517a;
  sVar1 = 3;
  while ((*psVar2 == 0 || ((psVar2[1] & 7U) != 4))) {
    psVar2 = psVar2 + 0x1a;
    sVar1 = sVar1 + -1;
    if (sVar1 == -1) {
      return;
    }
  }
  (*_thunk_FUN_00020ce2)();
  return;
}


// ==== FUN_0001f26a @ 0001f26a ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 FUN_0001f26a(void)

{
  undefined4 in_D0;
  undefined4 in_D1;
  char *pcVar1;
  
  DAT_000268ac = 0xb;
  DAT_000268ae = 0x12;
  (*_thunk_FUN_00015078)();
  pcVar1 = &DAT_00027e72;
  while (*pcVar1 != '\0') {
    FUN_0001f2b0();
    pcVar1 = pcVar1 + 1;
  }
  return CONCAT44(in_D0,in_D1);
}


// ==== FUN_0001f2b0 @ 0001f2b0 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 FUN_0001f2b0(void)

{
  undefined4 in_D0;
  undefined4 in_D1;
  
  (*_thunk_FUN_00020b0c)();
  return CONCAT44(in_D0,in_D1);
}


// ==== FUN_0001f2dc @ 0001f2dc ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0001f2dc(void)

{
  (*_thunk_FUN_0002129c)();
  return;
}


// ==== FUN_0001f2ec @ 0001f2ec ====

byte * FUN_0001f2ec(byte *param_1)

{
  byte *pbVar1;
  byte local_f [11];
  
  pbVar1 = local_f;
  for (; (*param_1 != 0 && (*param_1 != 0x20)); param_1 = param_1 + 1) {
    *pbVar1 = (byte)DAT_0002683e ^ *param_1 & 0x5f;
    pbVar1 = pbVar1 + 1;
  }
  *pbVar1 = 0;
  return local_f;
}


// ==== FUN_0001f332 @ 0001f332 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0001f332(undefined4 param_1,undefined4 param_2)

{
  undefined1 auStack_36 [50];
  
  (*_thunk_FUN_00022e78)(DAT_00026d6c,(int)param_1._0_2_,(int)param_1._2_2_);
  (*_thunk_FUN_000215d8)(auStack_36,param_2,&stack0x0000000c);
  FUN_00018570(auStack_36);
  return;
}


// ==== FUN_0001f374 @ 0001f374 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0001f374(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  (*_thunk_FUN_00022ea4)(DAT_00026d6c,(int)param_3._0_2_);
  (*_thunk_FUN_00022e78)(DAT_00026d6c,(int)param_1._0_2_,(int)param_1._2_2_);
  (*_thunk_FUN_00022e48)(DAT_00026d6c,(int)param_2._0_2_,(int)param_1._2_2_);
  (*_thunk_FUN_00022e48)(DAT_00026d6c,(int)param_2._0_2_,(int)param_2._2_2_);
  (*_thunk_FUN_00022e48)(DAT_00026d6c,(int)param_1._0_2_,(int)param_2._2_2_);
  (*_thunk_FUN_00022e48)(DAT_00026d6c,(int)param_1._0_2_,(int)param_1._2_2_);
  return;
}


// ==== FUN_0001f41a @ 0001f41a ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined2 FUN_0001f41a(void)

{
  int iVar1;
  ushort uVar2;
  short sVar3;
  undefined2 uVar4;
  undefined1 auStack_90 [50];
  undefined2 local_5e;
  undefined2 local_5c;
  undefined2 local_5a;
  short local_58;
  undefined2 local_56;
  undefined4 local_54;
  undefined1 auStack_50 [65];
  undefined1 local_f [11];
  
  local_56 = 0;
  (*_thunk_FUN_00021eca)(0x6840,(short)auStack_50);
  (*_thunk_FUN_00016b60)();
  local_54 = DAT_00026d6c;
  (*_thunk_FUN_00021246)((short)DAT_00026d6c);
  (*_thunk_FUN_00021280)();
  (*_thunk_FUN_000203be)();
  (*_thunk_FUN_000203be)();
  (*_thunk_FUN_000203be)();
  (*_thunk_FUN_000203be)();
  uVar2 = (*_thunk_FUN_000203be)();
  uVar2 = uVar2 & 0xff;
  while (uVar2 != 0) {
    (*_thunk_FUN_000203be)();
    uVar2 = uVar2 - 1;
  }
  local_58 = (*_thunk_FUN_00015d5a)();
  iVar1 = (local_58 % 0x21) * 0x10;
  FUN_0001f374(0x2b,0xa4);
  (*_thunk_FUN_00022ea4)((short)local_54,1);
  local_5a = *(undefined2 *)(&DAT_0002661e + iVar1);
  local_5c = *(undefined2 *)(&DAT_00026620 + iVar1);
  local_5e = *(undefined2 *)(&DAT_00026622 + iVar1);
  FUN_0001f332(0x30,0xf658);
  FUN_0001f332(0x3d,0xf677);
  FUN_0001f332(0x4a,0xf696);
  FUN_0001f332(0x57,0xf6a7);
  FUN_0001f332(100,0xf6c6);
  FUN_0001f332(0x71,0xf6e5);
  FUN_0001f332(0x82,0xf6f2);
  (*_thunk_FUN_00022ea4)((short)local_54,2);
  (*_thunk_FUN_00022e78)((short)DAT_00026d6c,0x70,0x8c);
  (*_thunk_FUN_000215d8)((short)auStack_90,0xf70d,local_5c);
  FUN_00018570((short)auStack_90);
  (*_thunk_FUN_00022ea4)((short)local_54);
  (*_thunk_FUN_00016fc4)((short)DAT_00026d7c);
  (*_thunk_FUN_00017084)((short)auStack_50);
  local_f[0] = 0;
  (*_thunk_FUN_00022ea4)((short)local_54,5);
  FUN_0001f374(0x91,0x99);
  (*_thunk_FUN_00016086)((short)local_f,200,0);
  sVar3 = (*_thunk_FUN_00021e9a)((short)local_f,0xf727);
  if (sVar3 == 0) {
    local_56 = 1;
  }
  uVar4 = FUN_0001f2ec((short)local_f,(short)(iVar1 + 0x26624));
  sVar3 = (*_thunk_FUN_00021e9a)(uVar4);
  if (sVar3 == 0) {
    local_56 = 1;
  }
  (*_thunk_FUN_000173b0)();
  return local_56;
}


// ==== FUN_0001f79c @ 0001f79c ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_0001f79c(ushort param_1,ushort param_2,short param_3,undefined4 param_4,undefined4 param_5)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int *piVar4;
  
  iVar1 = (*_thunk_FUN_00020848)(0x2c,param_4,param_5);
  iVar3 = DAT_00026e72;
  (**(code **)(DAT_00026e72 + -0xcc))();
  *(ushort *)(iVar1 + 0x1a) = param_2;
  *(ushort *)(iVar1 + 0x18) = param_1;
  uVar2 = (**(code **)(iVar3 + -0x23a))();
  *(undefined4 *)(iVar1 + 4) = uVar2;
  uVar2 = (*_thunk_FUN_00020848)(100);
  *(undefined4 *)(iVar1 + 0x28) = uVar2;
  (**(code **)(DAT_00026e72 + -0xc6))();
  uVar2 = (*_thunk_FUN_00020848)(0xc);
  *(undefined4 *)(iVar1 + 0x24) = uVar2;
  uVar2 = (*_thunk_FUN_00020848)(0x28);
  *(undefined4 *)(*(int *)(iVar1 + 0x24) + 4) = uVar2;
  *(undefined4 *)(*(int *)(iVar1 + 0x28) + 4) = uVar2;
  (**(code **)(DAT_00026e72 + -0x186))();
  piVar4 = (int *)(*(int *)(*(int *)(iVar1 + 0x24) + 4) + 8);
  do {
    param_3 = param_3 + -1;
    if (param_3 == -1) {
      *(short *)(iVar1 + 0x1c) = (short)param_4;
      *(short *)(iVar1 + 0x1e) = (short)param_5;
      return iVar1;
    }
    iVar3 = (*_thunk_FUN_0002085e)((uint)(param_1 >> 3) * (uint)param_2);
    *piVar4 = iVar3;
    piVar4 = piVar4 + 1;
  } while (iVar3 != 0);
  FUN_0001f8a2();
  return 0;
}


// ==== FUN_0001f89e @ 0001f89e ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_0001f89e(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  ushort uVar3;
  undefined4 *puVar4;
  
  (**(code **)(DAT_00026e72 + -0x21c))();
  iVar2 = *(int *)(*(int *)(param_1 + 0x24) + 4);
  if (iVar2 != 0) {
    uVar3 = (ushort)*(byte *)(iVar2 + 5);
    puVar4 = (undefined4 *)(iVar2 + 8);
    while (uVar3 = uVar3 - 1, uVar3 != 0xffff) {
      uVar1 = *puVar4;
      puVar4 = puVar4 + 1;
      (*_thunk_FUN_0002090a)(uVar1);
    }
    (*_thunk_FUN_0002090a)(*(undefined4 *)(*(int *)(param_1 + 0x24) + 4));
  }
  (*_thunk_FUN_0002090a)(*(undefined4 *)(param_1 + 0x24));
  (*_thunk_FUN_0002090a)(*(undefined4 *)(param_1 + 0x28));
  if (*(int *)(param_1 + 4) != 0) {
    (**(code **)(DAT_00026e72 + -0x240))();
  }
  (*_thunk_FUN_0002090a)(param_1);
  return 0;
}


// ==== FUN_0001f8a2 @ 0001f8a2 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_0001f8a2(void)

{
  undefined4 uVar1;
  int iVar2;
  ushort uVar3;
  int in_A0;
  undefined4 *puVar4;
  
  (**(code **)(DAT_00026e72 + -0x21c))();
  iVar2 = *(int *)(*(int *)(in_A0 + 0x24) + 4);
  if (iVar2 != 0) {
    uVar3 = (ushort)*(byte *)(iVar2 + 5);
    puVar4 = (undefined4 *)(iVar2 + 8);
    while (uVar3 = uVar3 - 1, uVar3 != 0xffff) {
      uVar1 = *puVar4;
      puVar4 = puVar4 + 1;
      (*_thunk_FUN_0002090a)(uVar1);
    }
    (*_thunk_FUN_0002090a)(*(undefined4 *)(*(int *)(in_A0 + 0x24) + 4));
  }
  (*_thunk_FUN_0002090a)(*(undefined4 *)(in_A0 + 0x24));
  (*_thunk_FUN_0002090a)(*(undefined4 *)(in_A0 + 0x28));
  if (*(int *)(in_A0 + 4) != 0) {
    (**(code **)(DAT_00026e72 + -0x240))();
  }
  (*_thunk_FUN_0002090a)();
  return 0;
}


// ==== FUN_0001f946 @ 0001f946 ====

undefined4 FUN_0001f946(void)

{
  byte bVar1;
  bool bVar2;
  short in_D0w;
  ushort uVar3;
  ushort uVar4;
  undefined4 in_D1;
  ushort uVar5;
  ushort uVar6;
  ushort unaff_D2w;
  short sVar7;
  ushort uVar8;
  short sVar9;
  short sVar10;
  char unaff_D6b;
  byte *in_A0;
  byte *pbVar11;
  int *in_A1;
  int *piVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  
  sVar10 = (short)in_D1 + -1;
  uVar3 = ((ushort)(in_D0w + 0xfU) >> 4) << 1;
  iVar15 = 0;
  do {
    iVar13 = *in_A1;
    pbVar11 = in_A0;
    piVar12 = in_A1 + 1;
    iVar14 = iVar15;
    uVar4 = uVar3;
    sVar9 = (unaff_D2w & 0xff) - 1;
LAB_0001f97e:
    do {
      sVar7 = 0;
      bVar1 = *pbVar11;
      uVar5 = (ushort)bVar1;
      in_A0 = pbVar11;
      uVar6 = uVar3;
      uVar8 = uVar3;
      if (unaff_D6b == '\0') {
        while (uVar5 = uVar6 - 1, uVar5 != 0xffff) {
LAB_0001f99c:
          *(byte *)(iVar13 + iVar14) = *in_A0;
          iVar14 = iVar14 + 1;
          in_A0 = in_A0 + 1;
          uVar6 = uVar5;
        }
LAB_0001f9c2:
        sVar7 = uVar8 + 1;
      }
      else {
        in_A0 = pbVar11 + 1;
        if (-1 < (char)bVar1) {
          uVar8 = (ushort)bVar1;
          goto LAB_0001f99c;
        }
        if (bVar1 != 0x80) {
          uVar6 = (ushort)(byte)-bVar1;
          uVar8 = (ushort)(byte)-bVar1;
          do {
            *(byte *)(iVar13 + iVar14) = *in_A0;
            iVar14 = iVar14 + 1;
            uVar6 = uVar6 - 1;
          } while (uVar6 != 0xffff);
          in_A0 = pbVar11 + 2;
          goto LAB_0001f9c2;
        }
      }
      uVar6 = uVar4 - sVar7;
      bVar2 = sVar7 <= (short)uVar4;
      pbVar11 = in_A0;
      uVar4 = uVar6;
    } while (uVar6 != 0 && bVar2);
    sVar9 = sVar9 + -1;
    if (sVar9 != -1) {
      iVar13 = *piVar12;
      piVar12 = piVar12 + 1;
      iVar14 = iVar15;
      uVar4 = uVar3;
      goto LAB_0001f97e;
    }
    sVar10 = sVar10 + -1;
    iVar15 = iVar14;
    if (sVar10 == -1) {
      return in_D1;
    }
  } while( true );
}


// ==== FUN_0001f9dc @ 0001f9dc ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined1 * FUN_0001f9dc(void)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  undefined1 *puVar4;
  int iVar5;
  uint uVar6;
  int *piVar8;
  undefined1 *puVar9;
  int *in_A1;
  undefined1 *puVar10;
  bool bVar11;
  undefined8 uVar12;
  ushort uVar7;
  
  bVar11 = false;
  (**(code **)(DAT_00026e6e + -0x54))();
  if (!bVar11) {
    iVar2 = (*_thunk_FUN_00020848)(0x104);
    iVar5 = DAT_00026e6e;
    if (iVar2 == 0) {
      (**(code **)(DAT_00026e6e + -0x5a))();
    }
    else {
      (**(code **)(DAT_00026e6e + -0x66))();
      (**(code **)(iVar5 + -0x5a))();
      uVar1 = *(undefined4 *)(iVar2 + 0x7c);
      (*_thunk_FUN_0002090a)(iVar2);
      iVar5 = DAT_00026e6e;
      iVar3 = (**(code **)(DAT_00026e6e + -0x1e))();
      if (iVar3 != 0) {
        uVar12 = (*_thunk_FUN_00020848)(uVar1);
        iVar3 = DAT_00026e6e;
        puVar4 = (undefined1 *)((ulonglong)uVar12 >> 0x20);
        if (puVar4 == (undefined1 *)0x0) {
          (**(code **)(_DAT_00000004 + -0x20a))(0,(int)uVar12,0x3ed,iVar2);
          (**(code **)(iVar5 + -0x24))();
        }
        else {
          iVar5 = (**(code **)(DAT_00026e6e + -0x2a))();
          if (iVar5 == 0) {
            (**(code **)(iVar3 + -0x24))();
          }
          else {
            (**(code **)(iVar3 + -0x24))();
            if (in_A1 == (int *)0x0) {
              return puVar4;
            }
            iVar5 = *(int *)(puVar4 + 0x10);
            iVar2 = iVar5 + 0x14;
            for (piVar8 = (int *)(iVar5 + 4 + (int)(puVar4 + 0x10)); *piVar8 != 0x424f4459;
                piVar8 = (int *)(piVar8[1] + 8 + (int)piVar8)) {
              iVar2 = piVar8[1] + 8 + iVar2;
            }
            uVar6 = iVar2 + 4;
            uVar12 = (*_thunk_FUN_00020848)(uVar6);
            iVar5 = (int)((ulonglong)uVar12 >> 0x20);
            *in_A1 = iVar5;
            if (iVar5 != 0) {
              FUN_0001f946();
              puVar9 = puVar4;
              puVar10 = (undefined1 *)*in_A1;
              while (uVar7 = (short)uVar6 - 1, uVar6 = (uint)uVar7, uVar7 != 0xffff) {
                *puVar10 = *puVar9;
                puVar9 = puVar9 + 1;
                puVar10 = puVar10 + 1;
              }
              (*_thunk_FUN_0002090a)(puVar4);
              (*_thunk_FUN_0002090a)(*in_A1);
              return (undefined1 *)0x0;
            }
            (**(code **)(_DAT_00000004 + -0x20a))(0,(int)uVar12,puVar4,piVar8 + 2);
          }
        }
      }
    }
  }
  return (undefined1 *)0xffffffff;
}


// ==== FUN_0001fc2a @ 0001fc2a ====

/* WARNING: Removing unreachable block (ram,0x0001fce0) */
/* WARNING: Removing unreachable block (ram,0x0001fd06) */
/* WARNING: Removing unreachable block (ram,0x0001fd02) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_0001fc2a(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = DAT_00026e6e;
  iVar1 = (**(code **)(DAT_00026e6e + -0x1e))();
  if (iVar1 != 0) {
    iVar3 = 0;
    iVar1 = (**(code **)(iVar2 + -0x2a))();
    iVar2 = DAT_00026e6e;
    if ((0 < iVar1) && (iVar3 == 0x464f524d)) {
      (**(code **)(DAT_00026e6e + -0x42))();
      iVar2 = (**(code **)(iVar2 + -0x2a))();
      if (iVar2 == 0) {
        return 0;
      }
      do {
        iVar2 = DAT_00026e6e;
        (**(code **)(DAT_00026e6e + -0x42))();
        iVar2 = (**(code **)(iVar2 + -0x2a))();
      } while (iVar2 != 0);
    }
    (**(code **)(DAT_00026e6e + -0x24))();
  }
  return 0;
}


// ==== FUN_0001fd2e @ 0001fd2e ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0001fd2e(void)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  
  iVar1 = FUN_0001fc2a();
  if (iVar1 != 0) {
    for (iVar2 = *(int *)(iVar1 + 0x10) + iVar1 + 0x10; piVar3 = (int *)(iVar2 + 4),
        *piVar3 != 0x434d4150; iVar2 = *(int *)(iVar2 + 8) + (int)piVar3) {
      if (*piVar3 == 0x424f4459) {
        return;
      }
    }
    FUN_0001fdb4();
    (*_thunk_FUN_0002090a)(iVar1);
  }
  return;
}


// ==== FUN_0001fdb4 @ 0001fdb4 ====

void FUN_0001fdb4(void)

{
  byte bVar1;
  bool bVar2;
  short sVar3;
  short in_D0w;
  byte *in_A0;
  byte *pbVar4;
  byte *pbVar5;
  ushort *in_A1;
  
  do {
    pbVar4 = in_A0 + 1;
    bVar1 = *in_A0;
    pbVar5 = in_A0 + 2;
    in_A0 = in_A0 + 3;
    *in_A1 = (ushort)(*pbVar5 >> 4) | (ushort)*pbVar4 | (ushort)bVar1 << 4;
    sVar3 = in_D0w + -3;
    bVar2 = 2 < in_D0w;
    in_D0w = sVar3;
    in_A1 = in_A1 + 1;
  } while (sVar3 != 0 && bVar2);
  return;
}


// ==== FUN_0001fdd6 @ 0001fdd6 ====

undefined4 FUN_0001fdd6(int param_1,int param_2)

{
  undefined4 in_D0;
  short sVar1;
  undefined2 *puVar2;
  undefined2 *puVar3;
  
  sVar1 = *(short *)(param_1 + 2);
  puVar2 = *(undefined2 **)(param_1 + 4);
  puVar3 = *(undefined2 **)(param_2 + 4);
  while (sVar1 = sVar1 + -1, sVar1 != -1) {
    *puVar3 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  }
  return in_D0;
}


// ==== FUN_0001fdfe @ 0001fdfe ====

undefined8 FUN_0001fdfe(void)

{
  undefined4 in_D0;
  undefined4 in_D1;
  
  (**(code **)(DAT_00026e72 + -0x1e))();
  return CONCAT44(in_D0,in_D1);
}


// ==== FUN_0001fe36 @ 0001fe36 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0001fe36(undefined4 param_1,undefined4 param_2)

{
  (*_thunk_FUN_0002090a)(param_1,param_2);
  (*_thunk_FUN_0002090a)();
  return;
}


// ==== FUN_0001fe50 @ 0001fe50 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined2 FUN_0001fe50(undefined4 param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  int iVar2;
  undefined2 local_6;
  
  local_6 = 0;
  iVar1 = (*_thunk_FUN_00022b30)(param_1,0x3ee);
  if (iVar1 == 0) {
    local_6 = (*_thunk_FUN_00022b06)();
  }
  else {
    iVar2 = (*_thunk_FUN_00021d6e)(iVar1,param_2,param_3);
    (*_thunk_FUN_00022ab2)(iVar1);
    if (iVar2 != param_3) {
      local_6 = (*_thunk_FUN_00022b06)();
    }
  }
  return local_6;
}


// ==== FUN_0001feb4 @ 0001feb4 ====

void FUN_0001feb4(undefined4 param_1)

{
  FUN_0001ff16(param_1,0x10001);
  return;
}


// ==== FUN_0001feca @ 0001feca ====

void FUN_0001feca(undefined4 param_1)

{
  FUN_0001ff16(param_1,0x10003);
  return;
}


// ==== FUN_0001fee0 @ 0001fee0 ====

void FUN_0001fee0(byte *param_1,int param_2,byte *param_3)

{
  byte bVar1;
  ushort uVar2;
  short sVar3;
  byte *pbVar4;
  byte *pbVar5;
  byte *pbVar6;
  
  pbVar6 = param_1 + param_2;
  while (param_1 < pbVar6) {
    pbVar4 = param_1 + 1;
    bVar1 = *param_1;
    uVar2 = (ushort)bVar1;
    if ((char)bVar1 < '\0') {
      sVar3 = (byte)-bVar1 - 1;
      pbVar5 = param_3;
      do {
        param_1 = pbVar4 + 1;
        param_3 = pbVar5 + 1;
        *pbVar5 = *pbVar4;
        sVar3 = sVar3 + -1;
        pbVar4 = param_1;
        pbVar5 = param_3;
      } while (sVar3 != -1);
    }
    else {
      param_1 = param_1 + 2;
      bVar1 = *pbVar4;
      pbVar4 = param_3;
      do {
        param_3 = pbVar4 + 1;
        *pbVar4 = bVar1;
        uVar2 = uVar2 - 1;
        pbVar4 = param_3;
      } while (uVar2 != 0xffff);
    }
  }
  return;
}


// ==== FUN_0001ff16 @ 0001ff16 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_0001ff16(undefined4 param_1,undefined4 param_2)

{
  short sVar3;
  int iVar1;
  undefined4 *puVar2;
  int local_34;
  int local_30;
  int local_2c;
  int local_28;
  int local_24 [4];
  int local_14;
  undefined4 local_10;
  int local_c;
  int local_8;
  
  local_8 = 0;
  local_28 = 0;
  local_2c = 0;
  local_30 = 0;
  local_34 = 0;
  DAT_00027eb2 = 0;
  local_8 = (*_thunk_FUN_00022b1e)(param_1,0xfffffffe);
  if (local_8 != 0) {
    local_28 = (*_thunk_FUN_00020848)(0x104);
    if (local_28 == 0) {
      DAT_00027eb2 = 1000000;
    }
    else {
      sVar3 = (*_thunk_FUN_00022ade)(local_8,local_28);
      if (sVar3 != 0) {
        (*_thunk_FUN_00022b54)(local_8);
        local_8 = 0;
        local_14 = *(int *)(local_28 + 0x7c);
        (*_thunk_FUN_0002090a)(local_28);
        local_28 = 0;
        if (0 < local_14) {
          if (local_14 < 0x10) {
            iVar1 = FUN_00020390(param_1,param_2);
            return iVar1;
          }
          local_2c = (*_thunk_FUN_00022b30)(param_1,0x3ed);
          if (((local_2c != 0) &&
              (local_c = (*_thunk_FUN_00022b42)(local_2c,local_24,0x10), local_c == 0x10)) &&
             (local_24[0] != 0x50636b64)) {
            if (local_24[0] == 0x5270636b) {
              local_10 = local_24[1];
              local_30 = FUN_00020874(local_24[1],param_2);
              if (local_30 == 0) {
                DAT_00027eb2 = 1000000;
              }
              else {
                puVar2 = (undefined4 *)(*_thunk_FUN_00020848)(local_14 + -8);
                if (puVar2 == (undefined4 *)0x0) {
                  DAT_00027eb2 = 1000000;
                  local_34 = 0;
                }
                else {
                  local_c = (*_thunk_FUN_00022b42)(local_2c,puVar2 + 2,local_14 + -0x10);
                  (*_thunk_FUN_00022ab2)(local_2c);
                  local_2c = 0;
                  if (local_14 + -0x10 == local_c) {
                    *puVar2 = local_24[2];
                    puVar2[1] = local_24[3];
                    FUN_0001fee0(puVar2,local_14 + -8,local_30,local_10);
                    (*_thunk_FUN_0002090a)(puVar2);
                    DAT_0002767a = local_10;
                    DAT_00027bca = local_30;
                    return local_30;
                  }
                  local_34 = 0;
                }
              }
            }
            else {
              local_34 = FUN_00020874(local_14,param_2);
              if (local_34 == 0) {
                DAT_00027eb2 = 1000000;
              }
              else {
                sVar3 = 0;
                do {
                  *(int *)(local_34 + sVar3 * 4) = local_24[sVar3];
                  sVar3 = sVar3 + 1;
                } while (sVar3 < 4);
                local_c = (*_thunk_FUN_00022b42)(local_2c,local_34 + 0x10,local_14 + -0x10);
                (*_thunk_FUN_00022ab2)(local_2c);
                local_2c = 0;
                if (local_14 + -0x10 == local_c) {
                  DAT_0002767a = local_14;
                  DAT_00027bca = local_34;
                  return local_34;
                }
              }
            }
          }
        }
      }
    }
  }
  if (DAT_00027eb2 == 0) {
    DAT_00027eb2 = (*_thunk_FUN_00022b06)();
  }
  if (local_34 != 0) {
    (*_thunk_FUN_0002090a)(local_34);
  }
  if (local_30 != 0) {
    (*_thunk_FUN_0002090a)(local_30);
  }
  if (local_2c != 0) {
    (*_thunk_FUN_00022ab2)(local_2c);
  }
  if (local_28 != 0) {
    (*_thunk_FUN_0002090a)(local_28);
  }
  if (local_8 != 0) {
    (*_thunk_FUN_00022b54)(local_8);
  }
  DAT_00027bca = 0;
  DAT_0002767a = 0;
  return 0;
}


// ==== FUN_00020220 @ 00020220 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int FUN_00020220(undefined4 param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  bool bVar2;
  short sVar4;
  int iVar3;
  int local_c;
  int local_8;
  
  local_8 = 0;
  DAT_00027bca = 0;
  bVar2 = true;
  DAT_00027eb2 = 0;
  local_c = thunk_FUN_00022d3a(0x104,0);
  if (local_c == 0) {
    DAT_00027eb2 = 1000000;
  }
  else {
    local_8 = (*_thunk_FUN_00022b1e)(param_1,0xfffffffe);
    if ((local_8 != 0) && (sVar4 = (*_thunk_FUN_00022ade)(local_8,local_c), sVar4 != 0)) {
      (*_thunk_FUN_00022b54)(local_8);
      local_8 = 0;
      iVar1 = *(int *)(local_c + 0x7c);
      thunk_FUN_00022d8a(local_c,0x104);
      local_c = 0;
      if (param_2 == 0) {
        DAT_00027bca = FUN_00020874(iVar1,param_3);
        if (DAT_00027bca == 0) {
          DAT_00027eb2 = 1000000;
          goto LAB_0002031e;
        }
      }
      else {
        DAT_00027bca = param_2;
      }
      iVar3 = (*_thunk_FUN_00022b30)(param_1,0x3ed);
      if (iVar3 != 0) {
        DAT_0002767a = (*_thunk_FUN_00022b42)(iVar3,DAT_00027bca,iVar1);
        (*_thunk_FUN_00022ab2)(iVar3);
        if (DAT_0002767a == iVar1) {
          bVar2 = false;
        }
      }
    }
  }
LAB_0002031e:
  if (bVar2) {
    if (DAT_00027eb2 == 0) {
      DAT_00027eb2 = (*_thunk_FUN_00022b06)();
    }
    if (param_2 == 0) {
      (*_thunk_FUN_0002090a)(DAT_00027bca);
    }
    DAT_00027bca = 0;
    DAT_0002767a = 0;
  }
  if (local_8 != 0) {
    (*_thunk_FUN_00022b54)(local_8);
  }
  if (local_c != 0) {
    thunk_FUN_00022d8a(local_c,0x104);
  }
  return DAT_00027bca;
}


// ==== FUN_00020390 @ 00020390 ====

void FUN_00020390(undefined4 param_1,undefined4 param_2)

{
  FUN_00020220(param_1,0,param_2);
  return;
}


// ==== FUN_000203be @ 000203be ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_000203be(void)

{
  DAT_00026860 = _DAT_00dff006 ^ DAT_00026862 * 0x1afb - 0x333U;
  return;
}


// ==== FUN_000203da @ 000203da ====

void FUN_000203da(undefined4 param_1)

{
  DAT_00026860 = param_1._0_2_;
  DAT_00026862 = param_1._0_2_;
  return;
}


// ==== FUN_000203e8 @ 000203e8 ====

void FUN_000203e8(undefined4 *param_1,undefined4 *param_2,undefined4 param_3)

{
  byte bVar1;
  ushort uVar2;
  byte *pbVar3;
  byte *pbVar4;
  byte *pbVar5;
  byte *pbVar6;
  
  pbVar6 = (byte *)*param_2;
  pbVar3 = (byte *)*param_1;
  do {
    while( true ) {
      pbVar4 = pbVar3 + 1;
      bVar1 = *pbVar3;
      uVar2 = (ushort)bVar1;
      if (-1 < (char)bVar1) break;
      pbVar5 = pbVar4;
      if (bVar1 != 0x80) {
        uVar2 = (ushort)(byte)-bVar1;
        param_3._0_2_ = (param_3._0_2_ - uVar2) + -1;
        pbVar5 = pbVar3 + 2;
        bVar1 = *pbVar4;
        pbVar3 = pbVar6;
        do {
          pbVar6 = pbVar3 + 1;
          *pbVar3 = bVar1;
          uVar2 = uVar2 - 1;
          pbVar3 = pbVar6;
        } while (uVar2 != 0xffff);
      }
      pbVar3 = pbVar5;
      if (param_3._0_2_ < 1) goto LAB_0002042a;
    }
    param_3._0_2_ = (param_3._0_2_ - uVar2) + -1;
    pbVar3 = pbVar6;
    do {
      pbVar5 = pbVar4 + 1;
      pbVar6 = pbVar3 + 1;
      *pbVar3 = *pbVar4;
      uVar2 = uVar2 - 1;
      pbVar4 = pbVar5;
      pbVar3 = pbVar6;
    } while (uVar2 != 0xffff);
    pbVar3 = pbVar5;
  } while (0 < param_3._0_2_);
LAB_0002042a:
  *param_1 = pbVar5;
  *param_2 = pbVar6;
  return;
}


// ==== FUN_0002044c @ 0002044c ====

void FUN_0002044c(void)

{
  DAT_00027eb6 = FUN_0002046a();
  return;
}


// ==== FUN_00020454 @ 00020454 ====

void FUN_00020454(void)

{
  DAT_00027692 = FUN_00020488();
  return;
}


// ==== FUN_0002046a @ 0002046a ====

undefined4 FUN_0002046a(void)

{
  if ((DAT_00bfe0ff & 0x40) == 0) {
    return 1;
  }
  if ((DAT_00bfe001 & 0x80) == 0) {
    return 1;
  }
  return 0;
}


// ==== FUN_00020488 @ 00020488 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

ulonglong FUN_00020488(void)

{
  undefined4 in_D1;
  
  return (ulonglong)
         CONCAT14((&LAB_000204b0)[(short)(_DAT_00dff00c >> 6 & 0xc | _DAT_00dff00c & 3)],in_D1);
}


// ==== FUN_000204e4 @ 000204e4 ====

void FUN_000204e4(void)

{
  return;
}


// ==== FUN_000204ec @ 000204ec ====

void FUN_000204ec(void)

{
  return;
}


// ==== FUN_000204f4 @ 000204f4 ====

undefined4 FUN_000204f4(void)

{
  undefined4 extraout_A0;
  
  FUN_00020560();
  return extraout_A0;
}


// ==== FUN_0002050e @ 0002050e ====

int FUN_0002050e(int param_1,undefined4 param_2)

{
  return param_1 + (uint)(ushort)(*(short *)(param_1 + 4) << 3) +
                   *(int *)(param_1 + (uint)(ushort)(param_2._0_2_ + *(short *)(param_1 + 4)) * 4 +
                           6) + 6;
}


// ==== FUN_00020560 @ 00020560 ====

undefined8 FUN_00020560(void)

{
  int *piVar1;
  int in_D0;
  int iVar2;
  undefined4 in_D1;
  short sVar3;
  int in_A0;
  int *piVar4;
  
  sVar3 = *(short *)(in_A0 + 4);
  if (0 < sVar3) {
    piVar1 = (int *)(in_A0 + 6);
    do {
      piVar4 = piVar1;
      if (in_D0 <= *piVar4) break;
      sVar3 = sVar3 + -1;
      piVar1 = piVar4 + 1;
    } while (sVar3 != -1);
    if (in_D0 == *piVar4) {
      iVar2 = *(short *)(in_A0 + 4) * 8 +
              in_A0 + *(int *)((short)((uint)((int)piVar4 + (-6 - in_A0)) >> 2) * 4 +
                               *(short *)(in_A0 + 4) * 4 + in_A0 + 6) + 6;
      goto LAB_000205ac;
    }
  }
  iVar2 = 0;
LAB_000205ac:
  return CONCAT44(iVar2,in_D1);
}


// ==== FUN_000205cc @ 000205cc ====

void FUN_000205cc(undefined4 param_1)

{
  DAT_00026c80 = param_1._0_2_;
  DAT_00026c08 = 10;
  DAT_00026c06 = 0;
  DAT_00026c0a = FUN_00022ba4(0,0);
  DAT_00026c12 = FUN_00022c8e(DAT_00026c0a);
  DAT_00026c24 = &DAT_00026c2c;
  DAT_00026c28 = FUN_0002075a;
  DAT_00026c1f = 0x7f;
  FUN_00022dc4(s_input_device_00026866,0,DAT_00026c12,0);
  *(undefined2 *)(DAT_00026c12 + 0x1c) = 9;
  *(undefined **)(DAT_00026c12 + 0x28) = &DAT_00026c16;
  FUN_00022d50(DAT_00026c12);
  DAT_00026c0e = FUN_00022ba4(0,0);
  DAT_00026c7c = FUN_00022cb6(DAT_00026c0e,0x20);
  FUN_00022dc4(s_console_device_00026873,0xffffffff,DAT_00026c7c,0);
  DAT_00027eba = *(undefined4 *)(DAT_00026c7c + 0x14);
  return;
}


// ==== FUN_0002067c @ 0002067c ====

void FUN_0002067c(void)

{
  if (DAT_00026c7c != 0) {
    FUN_00022b88(DAT_00026c7c);
    FUN_00022cfa(DAT_00026c7c);
    DAT_00026c7c = 0;
    FUN_00022c30(DAT_00026c0e);
    DAT_00026c0e = 0;
    *(undefined2 *)(DAT_00026c12 + 0x1c) = 10;
    *(undefined **)(DAT_00026c12 + 0x28) = &DAT_00026c16;
    FUN_00022d50(DAT_00026c12);
    FUN_00022b88(DAT_00026c12);
    FUN_00022ca4(DAT_00026c12);
    DAT_00026c12 = 0;
    FUN_00022c30(DAT_00026c0a);
    DAT_00026c0a = 0;
  }
  return;
}


// ==== FUN_000206ee @ 000206ee ====

void FUN_000206ee(void)

{
  undefined4 uVar1;
  
  uVar1 = FUN_000207e4();
  FUN_00020700(uVar1);
  return;
}


// ==== FUN_00020700 @ 00020700 ====

ushort FUN_00020700(undefined4 param_1)

{
  short sVar1;
  byte local_20 [2];
  undefined4 local_1e;
  undefined1 local_1a;
  undefined1 local_19;
  undefined2 local_18;
  undefined2 local_16;
  ushort local_6;
  
  local_6 = 0;
  local_1e = 0;
  local_1a = 1;
  local_19 = 0;
  local_18 = param_1._2_2_;
  local_16 = (undefined2)((uint)param_1 >> 0x10);
  sVar1 = FUN_00022f30(&local_1e,local_20,1,0);
  if (sVar1 == 1) {
    local_6 = (ushort)local_20[0];
  }
  return local_6;
}


// ==== FUN_0002075a @ 0002075a ====

void FUN_0002075a(void)

{
  ushort uVar1;
  ushort uVar2;
  short sVar3;
  int *in_A0;
  
  do {
    sVar3 = DAT_00026c06;
    uVar1 = *(ushort *)((int)in_A0 + 6);
    uVar2 = *(ushort *)(in_A0 + 2);
    if (*(char *)(in_A0 + 1) == '\x02') {
      if (uVar1 == 0x69) {
        DAT_00027ebe = CONCAT11(0xff,(undefined1)DAT_00027ebe);
      }
      if (uVar1 == 0xe9) {
        DAT_00027ebe = 0;
        goto LAB_0002078c;
      }
    }
    else {
LAB_0002078c:
      if (((*(char *)(in_A0 + 1) == '\x01') && ((uVar1 & 0x80) == 0)) &&
         ((DAT_00026c80 == 0 || ((DAT_00026c80 & uVar2) != 0)))) {
        if (DAT_00026c06 < DAT_00026c08) {
          (&DAT_00026be8)[DAT_00026c06] = (char)uVar1;
          *(ushort *)((int)&DAT_00026bf2 + (int)(short)(sVar3 * 2)) = uVar2;
          DAT_00026c06 = DAT_00026c06 + 1;
        }
        *(undefined2 *)(in_A0 + 1) = 0;
      }
    }
    in_A0 = (int *)*in_A0;
    if (in_A0 == (int *)0x0) {
      return;
    }
  } while( true );
}


// ==== FUN_000207d8 @ 000207d8 ====

undefined4 FUN_000207d8(void)

{
  undefined4 uVar1;
  
  uVar1 = 0;
  if (DAT_00026c06 != 0) {
    uVar1 = 0xffffffff;
  }
  return uVar1;
}


// ==== FUN_000207e4 @ 000207e4 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 FUN_000207e4(void)

{
  byte bVar1;
  ushort uVar2;
  uint uVar3;
  undefined4 in_D1;
  short sVar4;
  short sVar5;
  undefined1 in_ZF;
  
  while( true ) {
    FUN_000207d8();
    if (!(bool)in_ZF) break;
    (*_thunk_FUN_00022eee)();
  }
  (*_thunk_FUN_00022d48)();
  uVar2 = DAT_00026bf2;
  bVar1 = DAT_00026be8;
  uVar3 = CONCAT31((int3)(((uint)DAT_00026bf2 << 0x10) >> 8),DAT_00026be8);
  DAT_00026c06 = DAT_00026c06 + -1;
  sVar4 = 0;
  sVar5 = 0;
  do {
    (&DAT_00026be8)[sVar4] = (&DAT_00026be9)[sVar4];
    *(undefined2 *)((int)&DAT_00026bf2 + (int)sVar5) =
         *(undefined2 *)((int)&DAT_00026bf4 + (int)sVar5);
    sVar4 = sVar4 + 1;
    sVar5 = sVar5 + 2;
  } while (sVar4 <= DAT_00026c06);
  (*_thunk_FUN_00022d66)();
  if (DAT_00026c80 != 0) {
    uVar3 = (uint)(~DAT_00026c80 & uVar2) << 0x10 | (uint)bVar1;
  }
  return CONCAT44(uVar3,in_D1);
}


// ==== FUN_00020848 @ 00020848 ====

void FUN_00020848(undefined4 param_1)

{
  FUN_00020874(param_1,0x10001);
  return;
}


// ==== FUN_0002085e @ 0002085e ====

void FUN_0002085e(undefined4 param_1)

{
  FUN_00020874(param_1,0x10003);
  return;
}


// ==== FUN_00020874 @ 00020874 ====

int * FUN_00020874(int param_1,uint param_2)

{
  int *piVar1;
  
  piVar1 = (int *)thunk_FUN_00022d3a(param_1 + 0xc,param_2 | 0x10000);
  if (piVar1 == (int *)0x0) {
    piVar1 = (int *)0x0;
  }
  else {
    *piVar1 = param_1 + 0xc;
    if (DAT_00026882 == (int *)0x0) {
      DAT_00026882 = piVar1;
      piVar1[1] = (int)piVar1;
      piVar1[2] = (int)piVar1;
    }
    else {
      piVar1[1] = (int)DAT_00026882;
      piVar1[2] = DAT_00026882[2];
      *(int **)(DAT_00026882[2] + 4) = piVar1;
      DAT_00026882[2] = (int)piVar1;
    }
    piVar1 = piVar1 + 3;
  }
  return piVar1;
}


// ==== FUN_0002090a @ 0002090a ====

undefined4 FUN_0002090a(int param_1)

{
  undefined4 *puVar1;
  
  if (param_1 != 0) {
    if (param_1 == -1) {
      while (DAT_00026882 != (undefined4 *)0x0) {
        FUN_0002090a(DAT_00026882 + 3);
      }
    }
    else {
      puVar1 = (undefined4 *)(param_1 + -0xc);
      if (puVar1 == DAT_00026882) {
        DAT_00026882 = *(undefined4 **)(param_1 + -8);
      }
      if (puVar1 == *(undefined4 **)(param_1 + -8)) {
        DAT_00026882 = (undefined4 *)0x0;
      }
      *(undefined4 *)(*(int *)(param_1 + -8) + 8) = *(undefined4 *)(param_1 + -4);
      *(undefined4 *)(*(int *)(param_1 + -4) + 4) = *(undefined4 *)(param_1 + -8);
      thunk_FUN_00022d8a(puVar1,*puVar1);
    }
  }
  return 0;
}


// ==== FUN_000209bc @ 000209bc ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_000209bc(void)

{
  short sVar1;
  ushort uVar2;
  short sVar3;
  ushort in_D0w;
  short in_D1w;
  ushort uVar4;
  ushort uVar5;
  ushort *in_A0;
  int in_A1;
  bool bVar6;
  
  if (in_A0 == (ushort *)0x0) {
    return;
  }
  DAT_00027ee8 = *in_A0 * in_A0[1];
  DAT_00027ed6 = in_A0 + 10;
  uVar4 = in_A0[1];
  DAT_00027eda = in_A1;
  if (in_D1w < DAT_000268ac) {
    sVar1 = in_D1w - DAT_000268ac;
    bVar6 = SCARRY2(sVar1,uVar4);
    uVar4 = sVar1 + uVar4;
    if (uVar4 == 0 || bVar6 != (int)((uint)uVar4 << 0x10) < 0) {
      return;
    }
    DAT_00027ed6 = (ushort *)((uint)(ushort)-sVar1 * (uint)*in_A0 + (int)DAT_00027ed6);
    DAT_00027eda = (uint)(ushort)-sVar1 * (uint)*in_A0 + in_A1;
    in_D1w = DAT_000268ac;
  }
  uVar5 = (uVar4 + in_D1w) - DAT_000268ae;
  if ((uVar5 != 0 && SBORROW2(uVar4 + in_D1w,DAT_000268ae) == (int)((uint)uVar5 << 0x10) < 0) &&
     (bVar6 = SBORROW2(uVar4,uVar5), uVar4 = uVar4 - uVar5,
     uVar4 == 0 || bVar6 != (int)((uint)uVar4 << 0x10) < 0)) {
    return;
  }
  DAT_00027ef0 = 0xffff;
  uVar5 = *in_A0;
  DAT_00027eee = in_D0w & 0xf;
  if (DAT_00027eee == 0) {
    DAT_00027ef2 = 0xffff;
    _DAT_00027ee4 = 0;
  }
  else {
    uVar5 = uVar5 + 2;
    DAT_00027ef2 = 0;
    _DAT_00027ee4 = 0xfffefffe;
  }
  if ((short)in_D0w < (short)DAT_000268b0) {
    sVar1 = (short)((in_D0w - DAT_000268b0) + 0xf) >> 4;
    sVar3 = sVar1 * 2;
    if (sVar3 != 0) {
      bVar6 = SCARRY2(sVar3,uVar5);
      uVar5 = sVar3 + uVar5;
      if (uVar5 == 0 || bVar6 != (int)((uint)uVar5 << 0x10) < 0) {
        DAT_00027ef0 = 0xffff;
        return;
      }
      _DAT_00027ee4 = CONCAT22(DAT_00027ee4 + sVar1 * -2,DAT_00027ee6 + sVar1 * -2);
      DAT_00027ed6 = (ushort *)((int)DAT_00027ed6 - (int)sVar3);
      DAT_00027eda = DAT_00027eda - sVar3;
    }
    DAT_00027ef0 = *(undefined2 *)(&DAT_000268b8 + (short)((-(in_D0w - DAT_000268b0) & 0xf) * 2));
    in_D0w = DAT_000268b0;
    if (DAT_00027eee != 0) {
      in_D0w = DAT_000268b0 - 0x10;
    }
  }
  sVar1 = (in_D0w & 0xfff0) + uVar5 * 8;
  if (SCARRY2(in_D0w & 0xfff0,uVar5 * 8)) {
    return;
  }
  uVar2 = sVar1 - DAT_000268b2;
  if (uVar2 != 0 && SBORROW2(sVar1,DAT_000268b2) == (int)((uint)uVar2 << 0x10) < 0) {
    sVar1 = (short)uVar2 >> 3;
    bVar6 = SBORROW2(uVar5,sVar1);
    uVar5 = uVar5 - sVar1;
    if (uVar5 == 0 || bVar6 != (int)((uint)uVar5 << 0x10) < 0) {
      return;
    }
    _DAT_00027ee4 = CONCAT22(sVar1 + DAT_00027ee4,sVar1 + DAT_00027ee6);
    DAT_00027ef2 = *(undefined2 *)(&DAT_000268da + (short)((0x10 - DAT_00027eee) * 2));
  }
  DAT_00027ee2 = *DAT_0002709e - uVar5;
  DAT_00027ee0 = uVar5 >> 1 | uVar4 << 6;
  DAT_00027ede = in_D1w * *DAT_0002709e + ((short)in_D0w >> 4) * 2;
  if (in_A1 == 0) {
    DAT_00027eda = 0;
  }
  return;
}


// ==== FUN_00020aee @ 00020aee ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00020aee(void)

{
  (*_thunk_FUN_000212ce)();
  FUN_00020b0c();
                    /* WARNING: Could not recover jumptable at 0x00020b08. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*_thunk_FUN_000212d4)();
  return;
}


// ==== FUN_00020b0c @ 00020b0c ====

undefined8 FUN_00020b0c(void)

{
  int iVar1;
  byte bVar2;
  byte bVar3;
  int iVar4;
  short sVar5;
  undefined2 uVar6;
  short sVar7;
  undefined4 in_D0;
  undefined4 in_D1;
  ushort uVar8;
  ushort uVar9;
  byte bVar10;
  int in_A0;
  int iVar11;
  int *piVar12;
  byte *pbVar13;
  int unaff_A6;
  undefined1 in_CF;
  
  FUN_000209bc();
  sVar7 = DAT_00027ee8;
  uVar6 = DAT_00027ee0;
  sVar5 = DAT_00027ede;
  iVar4 = DAT_00027eda;
  iVar11 = DAT_00027ed6;
  if (!(bool)in_CF) {
    bVar2 = *(byte *)(DAT_00026e6a + 0x18);
    uVar8 = DAT_00027eee << 0xc | DAT_00027eee >> 4;
    bVar10 = *(byte *)(unaff_A6 + 2);
    while ((bVar10 & 0x40) != 0) {
      bVar10 = *(byte *)(unaff_A6 + 2);
    }
    *(undefined2 *)(unaff_A6 + 0x44) = DAT_00027ef0;
    *(undefined2 *)(unaff_A6 + 0x46) = DAT_00027ef2;
    *(undefined2 *)(unaff_A6 + 0x42) = 0;
    uVar9 = 0xbca;
    if (iVar4 == 0) {
      uVar9 = 0x3ca;
      *(undefined2 *)(unaff_A6 + 0x74) = 0xffff;
      if (uVar8 == 0) {
        uVar9 = 0x1ca;
        *(undefined2 *)(unaff_A6 + 0x70) = 0xffff;
      }
    }
    uVar9 = uVar9 | uVar8;
    *(undefined2 *)(unaff_A6 + 100) = DAT_00027ee6;
    *(undefined2 *)(unaff_A6 + 0x62) = DAT_00027ee4;
    *(undefined2 *)(unaff_A6 + 0x60) = DAT_00027ee2;
    *(undefined2 *)(unaff_A6 + 0x66) = DAT_00027ee2;
    bVar10 = bVar2 & *(byte *)(in_A0 + 0xc);
    if (bVar10 != 0) {
      piVar12 = (int *)(DAT_0002709e + 8);
      *(ushort *)(unaff_A6 + 0x40) = uVar9;
      *(undefined2 *)(unaff_A6 + 0x72) = 0;
      do {
        bVar3 = bVar10 & 1;
        bVar10 = bVar10 >> 1;
        if (bVar3 != 0) {
          iVar1 = *piVar12;
          *(int *)(unaff_A6 + 0x50) = iVar4;
          *(int *)(unaff_A6 + 0x48) = sVar5 + iVar1;
          *(int *)(unaff_A6 + 0x54) = sVar5 + iVar1;
          *(undefined2 *)(unaff_A6 + 0x58) = uVar6;
          bVar3 = *(byte *)(unaff_A6 + 2);
          while ((bVar3 & 0x40) != 0) {
            bVar3 = *(byte *)(unaff_A6 + 2);
          }
        }
        piVar12 = piVar12 + 1;
      } while (bVar10 != 0);
    }
    bVar10 = bVar2 & *(byte *)(in_A0 + 0xd);
    if (bVar10 != 0) {
      piVar12 = (int *)(DAT_0002709e + 8);
      *(ushort *)(unaff_A6 + 0x40) = uVar9;
      *(undefined2 *)(unaff_A6 + 0x72) = 0xffff;
      do {
        bVar3 = bVar10 & 1;
        bVar10 = bVar10 >> 1;
        if (bVar3 != 0) {
          iVar1 = *piVar12;
          *(int *)(unaff_A6 + 0x50) = iVar4;
          *(int *)(unaff_A6 + 0x48) = sVar5 + iVar1;
          *(int *)(unaff_A6 + 0x54) = sVar5 + iVar1;
          *(undefined2 *)(unaff_A6 + 0x58) = uVar6;
          bVar3 = *(byte *)(unaff_A6 + 2);
          while ((bVar3 & 0x40) != 0) {
            bVar3 = *(byte *)(unaff_A6 + 2);
          }
        }
        piVar12 = piVar12 + 1;
      } while (bVar10 != 0);
    }
    *(ushort *)(unaff_A6 + 0x42) = uVar8;
    *(ushort *)(unaff_A6 + 0x40) = uVar9 | 0x400;
    pbVar13 = (byte *)(in_A0 + 0xe);
    while( true ) {
      if (*pbVar13 == 0) break;
      bVar10 = bVar2 & *pbVar13;
      if (bVar10 != 0) {
        piVar12 = (int *)(DAT_0002709e + 8);
        do {
          bVar3 = bVar10 & 1;
          bVar10 = bVar10 >> 1;
          if (bVar3 != 0) {
            iVar1 = *piVar12;
            *(int *)(unaff_A6 + 0x50) = iVar4;
            *(int *)(unaff_A6 + 0x4c) = iVar11;
            *(int *)(unaff_A6 + 0x48) = sVar5 + iVar1;
            *(int *)(unaff_A6 + 0x54) = sVar5 + iVar1;
            *(undefined2 *)(unaff_A6 + 0x58) = uVar6;
            bVar3 = *(byte *)(unaff_A6 + 2);
            while ((bVar3 & 0x40) != 0) {
              bVar3 = *(byte *)(unaff_A6 + 2);
            }
          }
          piVar12 = piVar12 + 1;
        } while (bVar10 != 0);
      }
      iVar11 = sVar7 + iVar11;
      pbVar13 = pbVar13 + 1;
    }
  }
  return CONCAT44(in_D0,in_D1);
}


// ==== FUN_00020ca8 @ 00020ca8 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00020ca8(undefined4 param_1)

{
  DAT_0002738a = param_1;
  DAT_00027386 = (*_thunk_FUN_0002085e)(param_1);
  if (DAT_00027386 == 0) {
    DAT_0002738a = 0;
  }
  return;
}


// ==== FUN_00020cc4 @ 00020cc4 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00020cc4(void)

{
  (*_thunk_FUN_000212ce)();
  FUN_00020ce2();
                    /* WARNING: Could not recover jumptable at 0x00020cde. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*_thunk_FUN_000212d4)();
  return;
}


// ==== FUN_00020ce2 @ 00020ce2 ====

undefined4 FUN_00020ce2(void)

{
  int iVar1;
  char cVar2;
  byte bVar3;
  byte bVar4;
  int iVar5;
  undefined2 uVar6;
  short sVar7;
  undefined4 in_D0;
  uint uVar8;
  undefined4 uVar9;
  ushort uVar10;
  ushort uVar11;
  short sVar12;
  byte bVar13;
  int iVar14;
  ushort *in_A0;
  uint *puVar15;
  int in_A1;
  ushort *puVar16;
  uint *puVar17;
  uint *puVar18;
  uint *puVar19;
  uint *puVar20;
  uint *puVar21;
  int *piVar22;
  int unaff_A6;
  bool bVar23;
  
  bVar23 = false;
  if (in_A1 != 0) {
    FUN_000209bc();
    sVar12 = DAT_00027ee8;
    uVar6 = DAT_00027ee0;
    sVar7 = DAT_00027ede;
    iVar5 = DAT_00027eda;
    iVar14 = DAT_00027ed6;
    if (!bVar23) {
      bVar3 = *(byte *)(DAT_00026e6a + 0x18);
      uVar10 = DAT_00027eee << 0xc | DAT_00027eee >> 4;
      bVar13 = *(byte *)(unaff_A6 + 2);
      while ((bVar13 & 0x40) != 0) {
        bVar13 = *(byte *)(unaff_A6 + 2);
      }
      *(undefined2 *)(unaff_A6 + 0x44) = DAT_00027ef0;
      *(undefined2 *)(unaff_A6 + 0x46) = DAT_00027ef2;
      *(undefined2 *)(unaff_A6 + 0x42) = 0;
      uVar11 = 0xbca;
      if (iVar5 == 0) {
        uVar11 = 0x3ca;
        *(undefined2 *)(unaff_A6 + 0x74) = 0xffff;
        if (uVar10 == 0) {
          uVar11 = 0x1ca;
          *(undefined2 *)(unaff_A6 + 0x70) = 0xffff;
        }
      }
      uVar11 = uVar11 | uVar10;
      *(undefined2 *)(unaff_A6 + 100) = DAT_00027ee6;
      *(undefined2 *)(unaff_A6 + 0x62) = DAT_00027ee4;
      *(undefined2 *)(unaff_A6 + 0x60) = DAT_00027ee2;
      *(undefined2 *)(unaff_A6 + 0x66) = DAT_00027ee2;
      bVar13 = bVar3 & *(byte *)(in_A0 + 6);
      if (bVar13 != 0) {
        piVar22 = (int *)(DAT_0002709e + 8);
        *(ushort *)(unaff_A6 + 0x40) = uVar11;
        *(undefined2 *)(unaff_A6 + 0x72) = 0;
        do {
          bVar4 = bVar13 & 1;
          bVar13 = bVar13 >> 1;
          if (bVar4 != 0) {
            iVar1 = *piVar22;
            *(int *)(unaff_A6 + 0x50) = iVar5;
            *(int *)(unaff_A6 + 0x48) = sVar7 + iVar1;
            *(int *)(unaff_A6 + 0x54) = sVar7 + iVar1;
            *(undefined2 *)(unaff_A6 + 0x58) = uVar6;
            bVar4 = *(byte *)(unaff_A6 + 2);
            while ((bVar4 & 0x40) != 0) {
              bVar4 = *(byte *)(unaff_A6 + 2);
            }
          }
          piVar22 = piVar22 + 1;
        } while (bVar13 != 0);
      }
      bVar13 = bVar3 & *(byte *)((int)in_A0 + 0xd);
      if (bVar13 != 0) {
        piVar22 = (int *)(DAT_0002709e + 8);
        *(ushort *)(unaff_A6 + 0x40) = uVar11;
        *(undefined2 *)(unaff_A6 + 0x72) = 0xffff;
        do {
          bVar4 = bVar13 & 1;
          bVar13 = bVar13 >> 1;
          if (bVar4 != 0) {
            iVar1 = *piVar22;
            *(int *)(unaff_A6 + 0x50) = iVar5;
            *(int *)(unaff_A6 + 0x48) = sVar7 + iVar1;
            *(int *)(unaff_A6 + 0x54) = sVar7 + iVar1;
            *(undefined2 *)(unaff_A6 + 0x58) = uVar6;
            bVar4 = *(byte *)(unaff_A6 + 2);
            while ((bVar4 & 0x40) != 0) {
              bVar4 = *(byte *)(unaff_A6 + 2);
            }
          }
          piVar22 = piVar22 + 1;
        } while (bVar13 != 0);
      }
      *(ushort *)(unaff_A6 + 0x42) = uVar10;
      *(ushort *)(unaff_A6 + 0x40) = uVar11 | 0x400;
      puVar16 = in_A0 + 7;
      while( true ) {
        if (*(byte *)puVar16 == 0) break;
        bVar13 = bVar3 & *(byte *)puVar16;
        if (bVar13 != 0) {
          piVar22 = (int *)(DAT_0002709e + 8);
          do {
            bVar4 = bVar13 & 1;
            bVar13 = bVar13 >> 1;
            if (bVar4 != 0) {
              iVar1 = *piVar22;
              *(int *)(unaff_A6 + 0x50) = iVar5;
              *(int *)(unaff_A6 + 0x4c) = iVar14;
              *(int *)(unaff_A6 + 0x48) = sVar7 + iVar1;
              *(int *)(unaff_A6 + 0x54) = sVar7 + iVar1;
              *(undefined2 *)(unaff_A6 + 0x58) = uVar6;
              bVar4 = *(byte *)(unaff_A6 + 2);
              while ((bVar4 & 0x40) != 0) {
                bVar4 = *(byte *)(unaff_A6 + 2);
              }
            }
            piVar22 = piVar22 + 1;
          } while (bVar13 != 0);
        }
        iVar14 = sVar12 + iVar14;
        puVar16 = (ushort *)((int)puVar16 + 1);
      }
    }
    return in_D0;
  }
  uVar8 = (uint)*in_A0 * (uint)in_A0[1];
  if (DAT_0002738a <= uVar8 && uVar8 - DAT_0002738a != 0) {
    uVar9 = FUN_00020b0c();
    return uVar9;
  }
  puVar16 = in_A0 + 7;
  sVar7 = -1;
  do {
    sVar12 = sVar7;
    cVar2 = *(char *)puVar16;
    puVar16 = (ushort *)((int)puVar16 + 1);
    sVar7 = sVar12 + 1;
  } while (cVar2 != '\0');
  if ((short)(sVar12 + 1) != 0 && sVar12 != 0) {
    puVar15 = (uint *)(in_A0 + 10);
    uVar11 = (ushort)uVar8;
    puVar21 = (uint *)((int)puVar15 + (int)(short)uVar11);
    puVar17 = (uint *)((int)puVar21 + (int)(short)uVar11);
    puVar18 = (uint *)((int)puVar17 + (int)(short)uVar11);
    puVar19 = (uint *)((int)puVar18 + (int)(short)uVar11);
    uVar10 = uVar11 >> 1;
    if (sVar12 == 1) {
      uVar11 = uVar11 >> 2;
      puVar17 = DAT_00027386;
      if ((uVar10 & 1) != 0) {
        puVar17 = (uint *)((int)DAT_00027386 + 2);
        *(ushort *)DAT_00027386 = *(ushort *)puVar21 | *(ushort *)puVar15;
        puVar15 = (uint *)(in_A0 + 0xb);
        puVar21 = (uint *)((int)puVar21 + 2);
      }
      while (uVar11 = uVar11 - 1, uVar11 != 0xffff) {
        *puVar17 = *puVar21 | *puVar15;
        puVar15 = puVar15 + 1;
        puVar17 = puVar17 + 1;
        puVar21 = puVar21 + 1;
      }
    }
    else if (sVar12 == 2) {
      uVar11 = uVar11 >> 2;
      puVar18 = DAT_00027386;
      if ((uVar10 & 1) != 0) {
        puVar18 = (uint *)((int)DAT_00027386 + 2);
        *(ushort *)DAT_00027386 = *(ushort *)puVar17 | *(ushort *)puVar21 | *(ushort *)puVar15;
        puVar15 = (uint *)(in_A0 + 0xb);
        puVar21 = (uint *)((int)puVar21 + 2);
        puVar17 = (uint *)((int)puVar17 + 2);
      }
      while (uVar11 = uVar11 - 1, uVar11 != 0xffff) {
        *puVar18 = *puVar17 | *puVar21 | *puVar15;
        puVar15 = puVar15 + 1;
        puVar18 = puVar18 + 1;
        puVar21 = puVar21 + 1;
        puVar17 = puVar17 + 1;
      }
    }
    else if (sVar12 == 3) {
      uVar11 = uVar11 >> 2;
      puVar19 = DAT_00027386;
      if ((uVar10 & 1) != 0) {
        puVar19 = (uint *)((int)DAT_00027386 + 2);
        *(ushort *)DAT_00027386 =
             *(ushort *)puVar18 | *(ushort *)puVar17 | *(ushort *)puVar21 | *(ushort *)puVar15;
        puVar15 = (uint *)(in_A0 + 0xb);
        puVar21 = (uint *)((int)puVar21 + 2);
        puVar17 = (uint *)((int)puVar17 + 2);
        puVar18 = (uint *)((int)puVar18 + 2);
      }
      while (uVar11 = uVar11 - 1, uVar11 != 0xffff) {
        *puVar19 = *puVar18 | *puVar17 | *puVar21 | *puVar15;
        puVar15 = puVar15 + 1;
        puVar19 = puVar19 + 1;
        puVar21 = puVar21 + 1;
        puVar17 = puVar17 + 1;
        puVar18 = puVar18 + 1;
      }
    }
    else {
      uVar11 = uVar11 >> 2;
      puVar20 = DAT_00027386;
      if ((uVar10 & 1) != 0) {
        puVar20 = (uint *)((int)DAT_00027386 + 2);
        *(ushort *)DAT_00027386 =
             *(ushort *)puVar19 |
             *(ushort *)puVar18 | *(ushort *)puVar17 | *(ushort *)puVar21 | *(ushort *)puVar15;
        puVar15 = (uint *)(in_A0 + 0xb);
        puVar21 = (uint *)((int)puVar21 + 2);
        puVar17 = (uint *)((int)puVar17 + 2);
        puVar18 = (uint *)((int)puVar18 + 2);
        puVar19 = (uint *)((int)puVar19 + 2);
      }
      while (uVar11 = uVar11 - 1, uVar11 != 0xffff) {
        *puVar20 = *puVar19 | *puVar18 | *puVar17 | *puVar21 | *puVar15;
        puVar15 = puVar15 + 1;
        puVar20 = puVar20 + 1;
        puVar21 = puVar21 + 1;
        puVar17 = puVar17 + 1;
        puVar18 = puVar18 + 1;
        puVar19 = puVar19 + 1;
      }
    }
  }
  uVar9 = FUN_00020b0c();
  return uVar9;
}


// ==== FUN_00020e0a @ 00020e0a ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00020e0a(void)

{
  (*_thunk_FUN_000212ce)();
  FUN_00020e24();
                    /* WARNING: Could not recover jumptable at 0x00020e20. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*_thunk_FUN_000212d4)();
  return;
}


// ==== FUN_00020e24 @ 00020e24 ====

undefined8 FUN_00020e24(void)

{
  byte bVar1;
  byte bVar2;
  short sVar3;
  undefined2 uVar4;
  short sVar5;
  short sVar6;
  undefined4 in_D0;
  undefined4 in_D1;
  ushort uVar7;
  byte bVar8;
  int in_A0;
  int iVar9;
  int iVar10;
  int *piVar11;
  byte *pbVar12;
  int unaff_A6;
  undefined1 in_CF;
  
  FUN_000209bc();
  sVar5 = DAT_00027ee8;
  uVar4 = DAT_00027ee0;
  sVar3 = DAT_00027ede;
  iVar9 = DAT_00027ed6;
  if (!(bool)in_CF) {
    bVar1 = *(byte *)(DAT_00026e6a + 0x18);
    uVar7 = DAT_00027eee << 0xc | DAT_00027eee >> 4;
    bVar8 = *(byte *)(unaff_A6 + 2);
    while ((bVar8 & 0x40) != 0) {
      bVar8 = *(byte *)(unaff_A6 + 2);
    }
    *(undefined2 *)(unaff_A6 + 0x44) = DAT_00027ef0;
    sVar6 = DAT_00027ef4;
    *(short *)(unaff_A6 + 0x46) = DAT_00027ef4;
    if (sVar6 == 0) {
      *(undefined2 *)(unaff_A6 + 0x46) = DAT_00027ef2;
    }
    *(undefined2 *)(unaff_A6 + 0x42) = 0;
    *(undefined2 *)(unaff_A6 + 0x74) = 0xffff;
    *(undefined2 *)(unaff_A6 + 0x62) = DAT_00027ee4;
    *(undefined2 *)(unaff_A6 + 0x60) = DAT_00027ee2;
    *(undefined2 *)(unaff_A6 + 0x66) = DAT_00027ee2;
    *(int *)(unaff_A6 + 0x4c) = iVar9;
    bVar8 = bVar1 & *(byte *)(in_A0 + 0xd);
    if (bVar8 != 0) {
      piVar11 = (int *)(DAT_0002709e + 8);
      *(ushort *)(unaff_A6 + 0x40) = uVar7 | 0x36a;
      *(undefined2 *)(unaff_A6 + 0x72) = 0xffff;
      do {
        bVar2 = bVar8 & 1;
        bVar8 = bVar8 >> 1;
        if (bVar2 != 0) {
          iVar10 = (int)sVar3 + *piVar11;
          *(int *)(unaff_A6 + 0x48) = iVar10;
          *(int *)(unaff_A6 + 0x54) = iVar10;
          *(undefined2 *)(unaff_A6 + 0x58) = uVar4;
          bVar2 = *(byte *)(unaff_A6 + 2);
          while ((bVar2 & 0x40) != 0) {
            bVar2 = *(byte *)(unaff_A6 + 2);
          }
        }
        piVar11 = piVar11 + 1;
      } while (bVar8 != 0);
    }
    *(ushort *)(unaff_A6 + 0x42) = uVar7;
    *(ushort *)(unaff_A6 + 0x40) = uVar7 | 0x76a;
    pbVar12 = (byte *)(in_A0 + 0xe);
    while( true ) {
      if (*pbVar12 == 0) break;
      bVar8 = bVar1 & *pbVar12;
      if (bVar8 != 0) {
        piVar11 = (int *)(DAT_0002709e + 8);
        do {
          bVar2 = bVar8 & 1;
          bVar8 = bVar8 >> 1;
          if (bVar2 != 0) {
            iVar10 = (int)sVar3 + *piVar11;
            *(int *)(unaff_A6 + 0x4c) = iVar9;
            *(int *)(unaff_A6 + 0x48) = iVar10;
            *(int *)(unaff_A6 + 0x54) = iVar10;
            *(undefined2 *)(unaff_A6 + 0x58) = uVar4;
            bVar2 = *(byte *)(unaff_A6 + 2);
            while ((bVar2 & 0x40) != 0) {
              bVar2 = *(byte *)(unaff_A6 + 2);
            }
          }
          piVar11 = piVar11 + 1;
        } while (bVar8 != 0);
      }
      iVar9 = sVar5 + iVar9;
      pbVar12 = pbVar12 + 1;
    }
  }
  return CONCAT44(in_D0,in_D1);
}


// ==== FUN_00020f54 @ 00020f54 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00020f54(void)

{
  (*_thunk_FUN_000212ce)();
  FUN_00020f7c();
  (*_thunk_FUN_000212d4)();
  return;
}


// ==== FUN_00020f7c @ 00020f7c ====

void FUN_00020f7c(void)

{
  byte bVar1;
  ushort in_D0w;
  short in_D1w;
  int in_A0;
  undefined4 in_A1;
  int unaff_A2;
  int unaff_A6;
  
  bVar1 = *(byte *)(unaff_A6 + 2);
  while ((bVar1 & 0x40) != 0) {
    bVar1 = *(byte *)(unaff_A6 + 2);
  }
  *(undefined2 *)(unaff_A6 + 0x44) = 0xffff;
  *(undefined2 *)(unaff_A6 + 0x46) = 0xffff;
  *(undefined2 *)(unaff_A6 + 100) = 0;
  *(undefined2 *)(unaff_A6 + 0x62) = 0;
  *(undefined2 *)(unaff_A6 + 0x60) = 0;
  *(undefined2 *)(unaff_A6 + 0x66) = 0;
  *(int *)(unaff_A6 + 0x50) = unaff_A2;
  *(int *)(unaff_A6 + 0x4c) = in_A0;
  *(undefined4 *)(unaff_A6 + 0x48) = in_A1;
  *(undefined4 *)(unaff_A6 + 0x54) = in_A1;
  *(undefined2 *)(unaff_A6 + 0x42) = 0;
  *(undefined2 *)(unaff_A6 + 0x40) = 0xfca;
  if ((in_A0 == 0) && (*(undefined2 *)(unaff_A6 + 0x40) = 0xb0a, unaff_A2 == 0)) {
    return;
  }
  if (unaff_A2 == 0) {
    *(undefined2 *)(unaff_A6 + 0x40) = 0x5cc;
  }
  *(ushort *)(unaff_A6 + 0x58) = in_D1w << 6 | in_D0w >> 1;
  return;
}


// ==== FUN_00020ff2 @ 00020ff2 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00020ff2(void)

{
  (*_thunk_FUN_000212ce)();
  FUN_00021010();
  (*_thunk_FUN_000212d4)();
  return;
}


// ==== FUN_00021010 @ 00021010 ====

undefined8 FUN_00021010(void)

{
  short sVar1;
  byte bVar2;
  short sVar3;
  short sVar4;
  short sVar5;
  short *psVar6;
  uint in_D0;
  uint uVar7;
  ushort uVar8;
  uint in_D1;
  uint uVar9;
  short sVar10;
  ushort unaff_D2w;
  undefined2 uVar11;
  short unaff_D3w;
  uint unaff_D4;
  ushort uVar12;
  ushort uVar13;
  undefined3 uVar14;
  undefined4 unaff_D7;
  int iVar15;
  int *piVar16;
  int *piVar17;
  int unaff_A6;
  
  psVar6 = DAT_0002709e;
  uVar7 = in_D0;
  if ((short)in_D0 < (short)DAT_000268b0) {
    uVar7 = (uint)DAT_000268b0;
  }
  if (DAT_000268b2 <= (short)unaff_D2w) {
    unaff_D2w = DAT_000268b2 - 1;
  }
  uVar9 = in_D1;
  if ((short)in_D1 < (short)DAT_000268ac) {
    uVar9 = (uint)DAT_000268ac;
  }
  if (DAT_000268ae <= unaff_D3w) {
    unaff_D3w = DAT_000268ae + -1;
  }
  uVar8 = (ushort)uVar7;
  sVar10 = (short)uVar9;
  uVar14 = (undefined3)((uint)unaff_D7 >> 8);
  if (((uVar8 | unaff_D2w + 1) & 0xf) != 0) {
    sVar3 = (unaff_D3w - sVar10) + 1;
    if (sVar3 != 0 && -2 < (short)(unaff_D3w - sVar10)) {
      sVar1 = *DAT_0002709e;
      uVar13 = (short)uVar8 >> 3 & 0xfffe;
      sVar4 = ((short)unaff_D2w >> 3 & 0xfffeU) + 2;
      bVar2 = *(byte *)(unaff_A6 + 2);
      while ((bVar2 & 0x40) != 0) {
        bVar2 = *(byte *)(unaff_A6 + 2);
      }
      *(undefined2 *)(unaff_A6 + 0x44) = *(undefined2 *)(&DAT_000268b8 + (short)((uVar8 & 0xf) * 2))
      ;
      *(undefined2 *)(unaff_A6 + 0x46) =
           *(undefined2 *)(&DAT_000268dc + (short)((unaff_D2w & 0xf) * 2));
      uVar8 = sVar4 - uVar13;
      if (uVar8 != 0 && (short)uVar13 <= sVar4) {
        sVar4 = *psVar6;
        *(ushort *)(unaff_A6 + 0x62) = sVar4 - uVar8;
        *(ushort *)(unaff_A6 + 0x66) = sVar4 - uVar8;
        *(undefined2 *)(unaff_A6 + 0x74) = 0xffff;
        *(undefined2 *)(unaff_A6 + 0x42) = 0;
        uVar12 = (ushort)*(byte *)((int)psVar6 + 5);
        uVar7 = CONCAT31(uVar14,*(undefined1 *)(DAT_00026e6a + 0x18));
        piVar17 = (int *)(psVar6 + 4);
        while (uVar12 = uVar12 - 1, uVar12 != 0xffff) {
          piVar16 = piVar17 + 1;
          iVar15 = *piVar17;
          uVar11 = 0x50c;
          uVar9 = unaff_D4 & 1;
          unaff_D4 = unaff_D4 >> 1 & 0x7fff;
          if (uVar9 != 0) {
            uVar11 = 0x5fc;
          }
          uVar9 = uVar7 & 1;
          uVar7 = uVar7 >> 1 & 0x7fff;
          piVar17 = piVar16;
          if (uVar9 != 0) {
            iVar15 = (short)(uVar13 + sVar10 * sVar1) + iVar15;
            bVar2 = *(byte *)(unaff_A6 + 2);
            while ((bVar2 & 0x40) != 0) {
              bVar2 = *(byte *)(unaff_A6 + 2);
            }
            *(int *)(unaff_A6 + 0x4c) = iVar15;
            *(int *)(unaff_A6 + 0x54) = iVar15;
            *(undefined2 *)(unaff_A6 + 0x40) = uVar11;
            *(ushort *)(unaff_A6 + 0x58) = uVar8 >> 1 | sVar3 * 0x40;
          }
        }
      }
    }
    return CONCAT44(in_D0,in_D1);
  }
  sVar3 = (unaff_D3w - sVar10) + 1;
  if (sVar3 != 0 && -2 < (short)(unaff_D3w - sVar10)) {
    sVar1 = *DAT_0002709e;
    sVar4 = (short)(uVar8 + 0xf & 0xfff0) >> 3;
    sVar5 = (short)(unaff_D2w + 1 & 0xfff0) >> 3;
    bVar2 = *(byte *)(unaff_A6 + 2);
    while ((bVar2 & 0x40) != 0) {
      bVar2 = *(byte *)(unaff_A6 + 2);
    }
    uVar8 = sVar5 - sVar4;
    if (uVar8 != 0 && sVar4 <= sVar5) {
      *(ushort *)(unaff_A6 + 0x66) = *DAT_0002709e - uVar8;
      *(undefined2 *)(unaff_A6 + 0x42) = 0;
      uVar13 = (ushort)*(byte *)((int)psVar6 + 5);
      uVar7 = CONCAT31(uVar14,*(undefined1 *)(DAT_00026e6a + 0x18));
      piVar17 = (int *)(psVar6 + 4);
      while (uVar13 = uVar13 - 1, uVar13 != 0xffff) {
        piVar16 = piVar17 + 1;
        iVar15 = *piVar17;
        uVar11 = 0x100;
        uVar9 = unaff_D4 & 1;
        unaff_D4 = unaff_D4 >> 1 & 0x7fff;
        if (uVar9 != 0) {
          uVar11 = 0x1ff;
        }
        uVar9 = uVar7 & 1;
        uVar7 = uVar7 >> 1 & 0x7fff;
        piVar17 = piVar16;
        if (uVar9 != 0) {
          bVar2 = *(byte *)(unaff_A6 + 2);
          while ((bVar2 & 0x40) != 0) {
            bVar2 = *(byte *)(unaff_A6 + 2);
          }
          *(int *)(unaff_A6 + 0x54) = (short)(sVar4 + sVar10 * sVar1) + iVar15;
          *(undefined2 *)(unaff_A6 + 0x40) = uVar11;
          *(ushort *)(unaff_A6 + 0x58) = uVar8 >> 1 | sVar3 * 0x40;
        }
      }
    }
  }
  return CONCAT44(in_D0,in_D1);
}


// ==== FUN_00021120 @ 00021120 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 FUN_00021120(void)

{
  undefined4 in_D0;
  undefined4 in_D1;
  
  (*_thunk_FUN_000212ce)();
  FUN_0002113e();
  (*_thunk_FUN_000212d4)();
  return CONCAT44(in_D0,in_D1);
}


// ==== FUN_0002113e @ 0002113e ====

undefined8 FUN_0002113e(void)

{
  int iVar1;
  byte bVar2;
  short sVar3;
  short sVar4;
  ushort uVar5;
  short sVar6;
  short sVar7;
  uint uVar8;
  short *psVar9;
  uint in_D0;
  uint uVar10;
  uint in_D1;
  uint uVar11;
  short unaff_D2w;
  undefined2 uVar12;
  short unaff_D3w;
  uint unaff_D4;
  ushort uVar13;
  undefined4 unaff_D7;
  int *piVar14;
  int *piVar15;
  int unaff_A6;
  
  psVar9 = DAT_0002709e;
  uVar10 = in_D0;
  if ((short)in_D0 < (short)DAT_000268b0) {
    uVar10 = (uint)DAT_000268b0;
  }
  if (DAT_000268b2 <= unaff_D2w) {
    unaff_D2w = DAT_000268b2 + -1;
  }
  uVar11 = in_D1;
  if ((short)in_D1 < (short)DAT_000268ac) {
    uVar11 = (uint)DAT_000268ac;
  }
  if (DAT_000268ae <= unaff_D3w) {
    unaff_D3w = DAT_000268ae + -1;
  }
  sVar4 = unaff_D3w - (short)uVar11;
  sVar3 = sVar4 + 1;
  if (sVar3 != 0 && -2 < sVar4) {
    sVar4 = *DAT_0002709e;
    sVar6 = (short)((short)uVar10 + 0xfU & 0xfff0) >> 3;
    sVar7 = (short)(unaff_D2w + 1U & 0xfff0) >> 3;
    bVar2 = *(byte *)(unaff_A6 + 2);
    while ((bVar2 & 0x40) != 0) {
      bVar2 = *(byte *)(unaff_A6 + 2);
    }
    uVar5 = sVar7 - sVar6;
    if (uVar5 != 0 && sVar6 <= sVar7) {
      *(ushort *)(unaff_A6 + 0x66) = *DAT_0002709e - uVar5;
      *(undefined2 *)(unaff_A6 + 0x42) = 0;
      uVar13 = (ushort)*(byte *)((int)psVar9 + 5);
      uVar10 = CONCAT31((int3)((uint)unaff_D7 >> 8),*(undefined1 *)(DAT_00026e6a + 0x18));
      piVar15 = (int *)(psVar9 + 4);
      while (uVar13 = uVar13 - 1, uVar13 != 0xffff) {
        piVar14 = piVar15 + 1;
        iVar1 = *piVar15;
        uVar12 = 0x100;
        uVar8 = unaff_D4 & 1;
        unaff_D4 = unaff_D4 >> 1 & 0x7fff;
        if (uVar8 != 0) {
          uVar12 = 0x1ff;
        }
        uVar8 = uVar10 & 1;
        uVar10 = uVar10 >> 1 & 0x7fff;
        piVar15 = piVar14;
        if (uVar8 != 0) {
          bVar2 = *(byte *)(unaff_A6 + 2);
          while ((bVar2 & 0x40) != 0) {
            bVar2 = *(byte *)(unaff_A6 + 2);
          }
          *(int *)(unaff_A6 + 0x54) = (short)(sVar6 + (short)uVar11 * sVar4) + iVar1;
          *(undefined2 *)(unaff_A6 + 0x40) = uVar12;
          *(ushort *)(unaff_A6 + 0x58) = uVar5 >> 1 | sVar3 * 0x40;
        }
      }
    }
  }
  return CONCAT44(in_D0,in_D1);
}


// ==== FUN_00021246 @ 00021246 ====

undefined4 FUN_00021246(int param_1)

{
  int iVar1;
  undefined4 in_D0;
  ushort uVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  DAT_00026e6a = param_1;
  iVar1 = *(int *)(param_1 + 4);
  DAT_0002709e = iVar1;
  *(byte *)(param_1 + 0x18) = 0xff >> ((byte)(8 - *(char *)(iVar1 + 5)) & 0x3f);
  uVar2 = (ushort)*(byte *)(iVar1 + 5);
  puVar3 = &DAT_0002688c;
  puVar4 = (undefined4 *)(iVar1 + 8);
  while (uVar2 = uVar2 - 1, uVar2 != 0xffff) {
    *puVar3 = *puVar4;
    puVar3 = puVar3 + 1;
    puVar4 = puVar4 + 1;
  }
  return in_D0;
}


// ==== FUN_0002124a @ 0002124a ====

undefined4 FUN_0002124a(void)

{
  int iVar1;
  undefined4 in_D0;
  ushort uVar2;
  int in_A0;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  iVar1 = *(int *)(in_A0 + 4);
  DAT_00026e6a = in_A0;
  DAT_0002709e = iVar1;
  *(byte *)(in_A0 + 0x18) = 0xff >> ((byte)(8 - *(char *)(iVar1 + 5)) & 0x3f);
  uVar2 = (ushort)*(byte *)(iVar1 + 5);
  puVar3 = &DAT_0002688c;
  puVar4 = (undefined4 *)(iVar1 + 8);
  while (uVar2 = uVar2 - 1, uVar2 != 0xffff) {
    *puVar3 = *puVar4;
    puVar3 = puVar3 + 1;
    puVar4 = puVar4 + 1;
  }
  return in_D0;
}


// ==== FUN_00021280 @ 00021280 ====

undefined8 FUN_00021280(void)

{
  undefined4 in_D0;
  undefined4 in_D1;
  
  FUN_0002129c();
  return CONCAT44(in_D0,in_D1);
}


// ==== FUN_0002129c @ 0002129c ====

void FUN_0002129c(void)

{
  undefined2 in_D0w;
  short in_D1w;
  ushort unaff_D2w;
  ushort unaff_D3w;
  
  DAT_000268ac = in_D0w;
  DAT_000268ae = in_D1w;
  DAT_000268b0 = unaff_D2w & 0xfff0;
  DAT_000268b2 = unaff_D3w & 0xfff0;
  DAT_000268b6 = (unaff_D3w & 0xfff0) - 1;
  DAT_000268b4 = in_D1w + -1;
  return;
}


// ==== FUN_000212ce @ 000212ce ====

void FUN_000212ce(void)

{
  FUN_00022e8a();
  return;
}


// ==== FUN_000212d4 @ 000212d4 ====

void FUN_000212d4(void)

{
  do {
  } while ((DAT_00dff002 & 0x40) != 0);
  FUN_00022e40();
  return;
}


// ==== FUN_000212fa @ 000212fa ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_000212fa(void)

{
  (*_thunk_FUN_000212ce)();
  FUN_00021318();
  (*_thunk_FUN_000212d4)();
  return;
}


// ==== FUN_00021318 @ 00021318 ====

undefined8 FUN_00021318(void)

{
  byte bVar1;
  byte bVar2;
  short sVar3;
  short sVar4;
  ushort uVar5;
  ushort uVar6;
  ushort *puVar7;
  uint in_D0;
  uint uVar8;
  uint in_D1;
  uint uVar9;
  ushort unaff_D2w;
  ushort uVar10;
  ushort unaff_D3w;
  uint unaff_D4;
  ushort uVar12;
  int iVar11;
  ushort uVar13;
  ushort uVar14;
  uint uVar15;
  ushort *puVar16;
  ushort *puVar17;
  int iVar18;
  int unaff_A6;
  undefined4 local_34;
  
  puVar7 = DAT_0002709e;
  DAT_000268b4 = DAT_000268ae - 1;
  DAT_000268b6 = DAT_000268b2 - 1;
  uVar15 = unaff_D4 & 0xffff;
  uVar12 = 10;
  if (((short)DAT_000268b0 <= (short)unaff_D2w) &&
     (uVar12 = 2, (short)DAT_000268b6 < (short)unaff_D2w)) {
    uVar12 = 6;
  }
  if (((short)DAT_000268ac <= (short)unaff_D3w) &&
     (uVar12 = uVar12 & 0xfffd, (short)DAT_000268b4 < (short)unaff_D3w)) {
    uVar12 = uVar12 | 1;
  }
  uVar14 = 10;
  if (((short)DAT_000268b0 <= (short)in_D0) && (uVar14 = 2, (short)DAT_000268b6 < (short)in_D0)) {
    uVar14 = 6;
  }
  if (((short)DAT_000268ac <= (short)in_D1) &&
     (uVar14 = uVar14 & 0xfffd, (short)DAT_000268b4 < (short)in_D1)) {
    uVar14 = uVar14 | 1;
  }
  local_34 = CONCAT22(uVar14,uVar12);
  uVar8 = in_D0;
  uVar9 = in_D1;
  while( true ) {
    uVar12 = (ushort)uVar8;
    uVar14 = (ushort)uVar9;
    if (local_34._2_2_ == 0 && local_34._0_2_ == 0) {
      DAT_00027efc = CONCAT11(DAT_00027efc._0_1_,*(undefined1 *)(DAT_00026e6a + 0x18));
      iVar11 = (uint)*DAT_0002709e * (uVar9 & 0xffff);
      uVar13 = unaff_D3w - uVar14;
      if ((short)uVar13 < 0) {
        uVar13 = -uVar13;
      }
      uVar5 = unaff_D2w - uVar12;
      if ((short)uVar5 < 0) {
        uVar5 = -uVar5;
      }
      uVar10 = uVar5;
      uVar6 = uVar13;
      if ((short)uVar13 < (short)uVar5) {
        uVar10 = uVar13;
        uVar6 = uVar5;
      }
      bVar1 = (&DAT_000268fc)
              [(short)(ushort)(byte)(((unaff_D3w < uVar14) * '\x02' + (unaff_D2w < uVar12)) * '\x02'
                                    + (uVar13 < uVar5))];
      sVar3 = uVar10 * 2;
      uVar14 = (ushort)*(byte *)((int)DAT_0002709e + 5);
      puVar17 = DAT_0002709e + 4;
      while (uVar14 = uVar14 - 1, uVar14 != 0xffff) {
        bVar2 = *(byte *)(unaff_A6 + 2);
        while ((bVar2 & 0x40) != 0) {
          bVar2 = *(byte *)(unaff_A6 + 2);
        }
        puVar16 = puVar17 + 2;
        iVar18 = *(int *)puVar17;
        *(undefined2 *)(unaff_A6 + 0x72) = 0xffff;
        *(undefined2 *)(unaff_A6 + 0x44) = 0xffff;
        *(ushort *)(unaff_A6 + 0x40) = uVar12 << 0xc | 0xbca;
        *(undefined2 *)(unaff_A6 + 0x74) = 0x8000;
        uVar8 = uVar15 & 1;
        uVar15 = uVar15 >> 1;
        if (uVar8 == 0) {
          *(undefined2 *)(unaff_A6 + 0x72) = 0;
        }
        uVar13 = DAT_00027efc & 1;
        DAT_00027efc = DAT_00027efc >> 1;
        puVar17 = puVar16;
        if (uVar13 != 0) {
          *(short *)(unaff_A6 + 0x62) = sVar3;
          uVar13 = (ushort)bVar1;
          if (sVar3 < (short)uVar6) {
            uVar13 = bVar1 | 0x40;
          }
          *(ushort *)(unaff_A6 + 0x52) = sVar3 - uVar6;
          *(ushort *)(unaff_A6 + 100) = (sVar3 - uVar6) - uVar6;
          *(ushort *)(unaff_A6 + 0x42) = uVar13;
          iVar18 = CONCAT22((short)((uint)iVar11 >> 0x10),(uVar12 >> 4) * 2 + (short)iVar11) +
                   iVar18;
          *(int *)(unaff_A6 + 0x48) = iVar18;
          *(int *)(unaff_A6 + 0x54) = iVar18;
          *(ushort *)(unaff_A6 + 0x60) = *puVar7;
          *(ushort *)(unaff_A6 + 0x66) = *puVar7;
          *(ushort *)(unaff_A6 + 0x58) = (uVar6 + 1) * 0x40 + 2;
        }
      }
      return CONCAT44(in_D0,in_D1);
    }
    if ((local_34._2_2_ & local_34._0_2_) != 0) break;
    sVar3 = unaff_D2w - uVar12;
    sVar4 = unaff_D3w - uVar14;
    if (local_34._0_2_ == 0) {
      uVar12 = unaff_D3w;
      if ((local_34 & 8) == 0) {
        if ((local_34 & 4) == 0) {
          uVar14 = unaff_D2w;
          if ((local_34 & 2) == 0) {
            if (((local_34 & 1) != 0) && (uVar12 = DAT_000268b4, sVar3 != 0)) {
              uVar14 = (short)(((int)(short)(DAT_000268b4 - unaff_D3w) * (int)sVar3) / (int)sVar4) +
                       unaff_D2w;
              uVar12 = DAT_000268b4;
            }
          }
          else {
            uVar12 = DAT_000268ac;
            if (sVar3 != 0) {
              uVar14 = (short)(((int)(short)(DAT_000268ac - unaff_D3w) * (int)sVar3) / (int)sVar4) +
                       unaff_D2w;
              uVar12 = DAT_000268ac;
            }
          }
        }
        else {
          uVar14 = DAT_000268b6;
          if (sVar4 != 0) {
            uVar14 = DAT_000268b6;
            uVar12 = (short)(((int)(short)(DAT_000268b6 - unaff_D2w) * (int)sVar4) / (int)sVar3) +
                     unaff_D3w;
          }
        }
      }
      else {
        uVar14 = DAT_000268b0;
        if (sVar4 != 0) {
          uVar14 = DAT_000268b0;
          uVar12 = (short)(((int)(short)(DAT_000268b0 - unaff_D2w) * (int)sVar4) / (int)sVar3) +
                   unaff_D3w;
        }
      }
      unaff_D3w = uVar12;
      unaff_D2w = uVar14;
      uVar12 = 10;
      if (((short)DAT_000268b0 <= (short)unaff_D2w) &&
         (uVar12 = 2, (short)DAT_000268b6 < (short)unaff_D2w)) {
        uVar12 = 6;
      }
      if (((short)DAT_000268ac <= (short)unaff_D3w) &&
         (uVar12 = uVar12 & 0xfffd, (short)DAT_000268b4 < (short)unaff_D3w)) {
        uVar12 = uVar12 | 1;
      }
      local_34 = (uint)uVar12;
    }
    else {
      if ((local_34 & 0x80000) == 0) {
        if ((local_34 & 0x40000) == 0) {
          if ((local_34 & 0x20000) == 0) {
            if ((local_34 & 0x10000) != 0) {
              if (sVar3 != 0) {
                uVar8 = (uint)(ushort)((short)(((int)(short)(DAT_000268b4 - uVar14) * (int)sVar3) /
                                              (int)sVar4) + uVar12);
              }
              uVar9 = (uint)DAT_000268b4;
            }
          }
          else {
            if (sVar3 != 0) {
              uVar8 = (uint)(ushort)((short)(((int)(short)(DAT_000268ac - uVar14) * (int)sVar3) /
                                            (int)sVar4) + uVar12);
            }
            uVar9 = (uint)DAT_000268ac;
          }
        }
        else {
          if (sVar4 != 0) {
            uVar9 = (uint)(ushort)((short)(((int)(short)(DAT_000268b6 - uVar12) * (int)sVar4) /
                                          (int)sVar3) + uVar14);
          }
          uVar8 = (uint)DAT_000268b6;
        }
      }
      else {
        if (sVar4 != 0) {
          uVar9 = (uint)(ushort)((short)(((int)(short)(DAT_000268b0 - uVar12) * (int)sVar4) /
                                        (int)sVar3) + uVar14);
        }
        uVar8 = (uint)DAT_000268b0;
      }
      uVar12 = 10;
      if (((short)DAT_000268b0 <= (short)uVar8) && (uVar12 = 2, (short)DAT_000268b6 < (short)uVar8))
      {
        uVar12 = 6;
      }
      if (((short)DAT_000268ac <= (short)uVar9) &&
         (uVar12 = uVar12 & 0xfffd, (short)DAT_000268b4 < (short)uVar9)) {
        uVar12 = uVar12 | 1;
      }
      local_34 = CONCAT22(uVar12,local_34._2_2_);
    }
  }
  return CONCAT44(in_D0,in_D1);
}


// ==== FUN_000215d8 @ 000215d8 ====

undefined2 FUN_000215d8(undefined1 *param_1,undefined4 param_2)

{
  undefined2 uVar1;
  
  DAT_00026c82 = param_1;
  uVar1 = FUN_000216b2(&LAB_00021608,param_2,&stack0x0000000c);
  *DAT_00026c82 = 0;
  return uVar1;
}


// ==== FUN_00021624 @ 00021624 ====
// decompile failed: 
Low-level Error: Cannot properly adjust input varnodes
// ==== FUN_000216b2 @ 000216b2 ====

short FUN_000216b2(code *param_1,char *param_2,short *param_3)

{
  undefined4 uVar1;
  char cVar2;
  short sVar3;
  char *pcVar4;
  char *pcVar5;
  bool bVar6;
  char acStack_e2 [13];
  char local_d5 [187];
  char *local_1a;
  short local_16;
  short local_14;
  short local_12;
  short local_10;
  short local_e;
  ushort local_c;
  short local_a;
  short *local_8;
  
  local_a = 0;
  local_8 = param_3;
  do {
    while( true ) {
      if (*param_2 == '\0') {
        return local_a;
      }
      if (*param_2 == '%') break;
      sVar3 = (*param_1)();
      if (sVar3 == -1) {
        return -1;
      }
      local_a = local_a + 1;
      param_2 = param_2 + 1;
    }
    local_d5[1] = 0;
    local_e = 0x20;
    local_10 = 10000;
    sVar3 = (short)param_2[1];
    bVar6 = sVar3 == 0x2d;
    pcVar4 = param_2 + 2;
    if (bVar6) {
      pcVar4 = param_2 + 3;
      sVar3 = (short)param_2[2];
    }
    local_c = (ushort)!bVar6;
    pcVar5 = pcVar4;
    if (sVar3 == 0x30) {
      local_e = 0x30;
      pcVar5 = pcVar4 + 1;
      sVar3 = (short)*pcVar4;
    }
    if (sVar3 == 0x2a) {
      local_12 = *local_8;
      pcVar4 = pcVar5 + 1;
      sVar3 = (short)*pcVar5;
      local_8 = local_8 + 1;
    }
    else {
      local_12 = 0;
      pcVar4 = pcVar5;
      while (((&DAT_0002696a)[(short)(sVar3 + 1)] & 4) != 0) {
        local_12 = sVar3 + local_12 * 10 + -0x30;
        sVar3 = (short)*pcVar4;
        pcVar4 = pcVar4 + 1;
      }
    }
    if (sVar3 == 0x2e) {
      pcVar5 = pcVar4 + 1;
      sVar3 = (short)*pcVar4;
      if (sVar3 == 0x2a) {
        local_10 = *local_8;
        pcVar4 = pcVar4 + 2;
        sVar3 = (short)*pcVar5;
        local_8 = local_8 + 1;
      }
      else {
        local_10 = 0;
        pcVar4 = pcVar5;
        while (((&DAT_0002696a)[(short)(sVar3 + 1)] & 4) != 0) {
          local_10 = sVar3 + local_10 * 10 + -0x30;
          sVar3 = (short)*pcVar4;
          pcVar4 = pcVar4 + 1;
        }
      }
    }
    local_14 = 2;
    if (sVar3 == 0x6c) {
      sVar3 = (short)*pcVar4;
      local_14 = 4;
      param_2 = pcVar4 + 1;
    }
    else {
      param_2 = pcVar4;
      if (sVar3 == 0x68) {
        param_2 = pcVar4 + 1;
        sVar3 = (short)*pcVar4;
      }
    }
    switch(sVar3) {
    case 99:
      sVar3 = *local_8;
      local_8 = local_8 + 1;
    default:
      local_1a = local_d5;
      local_d5[0] = (char)sVar3;
      goto LAB_00021924;
    case 100:
      local_16 = -10;
      break;
    case 0x65:
    case 0x66:
    case 0x67:
      uVar1 = *(undefined4 *)local_8;
      local_8 = local_8 + 4;
      FUN_00021a40(uVar1,0,(short)acStack_e2,sVar3 + -0x65);
      local_1a = acStack_e2;
      pcVar4 = acStack_e2;
      do {
        pcVar5 = pcVar4 + 1;
        cVar2 = *pcVar4;
        pcVar4 = pcVar5;
      } while (cVar2 != '\0');
      local_14 = ((short)pcVar5 - (short)acStack_e2) + -1;
      local_10 = 200;
      goto LAB_00021930;
    case 0x6f:
      local_16 = 8;
      break;
    case 0x73:
      local_1a = *(char **)local_8;
      pcVar4 = local_1a;
      do {
        pcVar5 = pcVar4 + 1;
        cVar2 = *pcVar4;
        pcVar4 = pcVar5;
      } while (cVar2 != '\0');
      local_14 = ((short)pcVar5 - (short)local_1a) + -1;
      local_8 = local_8 + 2;
      goto LAB_00021930;
    case 0x75:
      local_16 = 10;
      break;
    case 0x78:
      local_16 = 0x10;
    }
    local_1a = (char *)FUN_00021624(local_8,(short)((uint)(local_d5 + 1) >> 0x10),local_14);
    local_8 = (short *)((int)local_14 + (int)local_8);
LAB_00021924:
    local_14 = ((short)local_d5 + 1) - (short)local_1a;
LAB_00021930:
    if (local_10 < local_14) {
      local_14 = local_10;
    }
    if (local_c != 0) {
      if (((*local_1a == '-') || (*local_1a == '+')) && (local_e == 0x30)) {
        local_12 = local_12 + -1;
        local_1a = local_1a + 1;
        sVar3 = (*param_1)();
        if (sVar3 == -1) {
          return -1;
        }
      }
      while (sVar3 = local_12 + -1, bVar6 = local_14 < local_12, local_12 = sVar3, bVar6) {
        sVar3 = (*param_1)();
        if (sVar3 == -1) {
          return -1;
        }
        local_a = local_a + 1;
      }
    }
    for (local_16 = 0; (*local_1a != '\0' && (local_16 < local_10)); local_16 = local_16 + 1) {
      local_1a = local_1a + 1;
      sVar3 = (*param_1)();
      if (sVar3 == -1) {
        return -1;
      }
    }
    local_a = local_16 + local_a;
    if (local_c == 0) {
      while (sVar3 = local_12 + -1, bVar6 = local_14 < local_12, local_12 = sVar3, bVar6) {
        sVar3 = (*param_1)();
        if (sVar3 == -1) {
          return -1;
        }
        local_a = local_a + 1;
      }
    }
  } while( true );
}


// ==== FUN_00021a40 @ 00021a40 ====

void FUN_00021a40(int param_1,undefined4 param_2,char *param_3,undefined4 param_4)

{
  short sVar1;
  char *pcVar2;
  char *pcVar3;
  char *pcVar4;
  char cVar5;
  bool bVar6;
  char cVar7;
  short local_c;
  short local_a;
  short local_6;
  
  local_c = param_4._0_2_ + 1;
  local_6 = 0;
  cVar5 = param_1 < 0;
  cVar7 = '\0';
  FUN_00021cba();
  pcVar2 = param_3;
  if (cVar7 != cVar5) {
    param_1 = FUN_00021cb0();
    pcVar2 = param_3 + 1;
    *param_3 = '-';
  }
  cVar5 = param_1 < 0;
  bVar6 = param_1 == 0;
  cVar7 = '\0';
  FUN_00021cba();
  if (!bVar6 && cVar7 == cVar5) {
    while( true ) {
      cVar5 = param_1 < 0;
      cVar7 = '\0';
      FUN_00021ca6();
      if (cVar7 == cVar5) break;
      param_1 = FUN_00021cec();
      local_6 = local_6 + -1;
    }
    while( true ) {
      cVar5 = param_1 < 0;
      cVar7 = '\0';
      FUN_00021ca6();
      if (cVar7 != cVar5) break;
      param_1 = FUN_00021cd8();
      local_6 = local_6 + 1;
    }
  }
  if (param_4._2_2_ == 2) {
    local_c = param_4._0_2_;
    if ((local_6 < -4) || (param_4._0_2_ < local_6)) {
      param_4._2_2_ = 0;
    }
  }
  else if (param_4._2_2_ == 1) {
    local_c = local_6 + local_c;
  }
  if (-1 < local_c) {
    FUN_00021c9c();
    cVar5 = DAT_0002691e < 0;
    cVar7 = '\0';
    FUN_00021ca6();
    if ((cVar7 == cVar5) && (local_6 = local_6 + 1, param_4._2_2_ != 0)) {
      local_c = local_c + 1;
    }
  }
  if (param_4._2_2_ == 0) {
    local_a = 1;
  }
  else if (local_6 < 0) {
    *pcVar2 = '0';
    pcVar3 = pcVar2 + 2;
    pcVar2[1] = '.';
    pcVar2 = pcVar3;
    sVar1 = -1 - local_6;
    if (local_c < 1) {
      sVar1 = param_4._0_2_;
    }
    while (sVar1 != 0) {
      *pcVar2 = '0';
      pcVar2 = pcVar2 + 1;
      sVar1 = sVar1 + -1;
    }
    local_a = 0;
  }
  else {
    local_a = local_6 + 1;
  }
  if (0 < local_c) {
    sVar1 = 0;
    pcVar3 = pcVar2;
    while( true ) {
      if (sVar1 < 0x10) {
        cVar5 = FUN_00021cc4();
        *pcVar3 = cVar5 + '0';
        FUN_00021ce2();
        FUN_00021cce();
        FUN_00021cec();
      }
      else {
        *pcVar3 = '0';
      }
      pcVar2 = pcVar3 + 1;
      local_c = local_c + -1;
      if (local_c == 0) break;
      pcVar4 = pcVar2;
      if ((local_a != 0) && (local_a = local_a + -1, local_a == 0)) {
        pcVar4 = pcVar3 + 2;
        *pcVar2 = '.';
      }
      sVar1 = sVar1 + 1;
      pcVar3 = pcVar4;
    }
  }
  if (param_4._2_2_ == 0) {
    *pcVar2 = 'e';
    if (local_6 < 0) {
      local_6 = -local_6;
      pcVar2[1] = '-';
    }
    else {
      pcVar2[1] = '+';
    }
    pcVar3 = pcVar2 + 2;
    if (99 < local_6) {
      pcVar3 = pcVar2 + 3;
      pcVar2[2] = (char)((int)local_6 / 100) + '0';
      local_6 = local_6 % 100;
    }
    *pcVar3 = (char)((int)local_6 / 10) + '0';
    pcVar2 = pcVar3 + 2;
    pcVar3[1] = (char)((int)local_6 % 10) + '0';
  }
  *pcVar2 = '\0';
  return;
}


// ==== FUN_00021c9c @ 00021c9c ====

void FUN_00021c9c(void)

{
  FUN_00021cf6();
  return;
}


// ==== FUN_00021ca6 @ 00021ca6 ====

void FUN_00021ca6(void)

{
  FUN_00021cf6();
  return;
}


// ==== FUN_00021cb0 @ 00021cb0 ====

void FUN_00021cb0(void)

{
  FUN_00021cf6();
  return;
}


// ==== FUN_00021cba @ 00021cba ====

void FUN_00021cba(void)

{
  FUN_00021cf6();
  return;
}


// ==== FUN_00021cc4 @ 00021cc4 ====

void FUN_00021cc4(void)

{
  FUN_00021cf6();
  return;
}


// ==== FUN_00021cce @ 00021cce ====

void FUN_00021cce(void)

{
  FUN_00021cf6();
  return;
}


// ==== FUN_00021cd8 @ 00021cd8 ====

void FUN_00021cd8(void)

{
  FUN_00021cf6();
  return;
}


// ==== FUN_00021ce2 @ 00021ce2 ====

void FUN_00021ce2(void)

{
  FUN_00021cf6();
  return;
}


// ==== FUN_00021cec @ 00021cec ====

void FUN_00021cec(void)

{
  FUN_00021cf6();
  return;
}


// ==== FUN_00021cf6 @ 00021cf6 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00021cf6(void)

{
  int iVar1;
  undefined4 in_A0;
  undefined4 unaff_A6;
  undefined4 *puVar2;
  undefined4 local_1c;
  char *pcStack_18;
  undefined4 local_14;
  undefined1 local_10 [16];
  
  if (DAT_00027efe == 0) {
    local_14 = 0;
    pcStack_18 = s_mathffp_library_00021d46;
    local_1c = 0x21d0a;
    DAT_00027efe = FUN_00021d7c();
    puVar2 = (undefined4 *)local_10;
    if (DAT_00027efe == 0) {
      local_14 = 0x10;
      pcStack_18 = &DAT_00021d56;
      local_1c = 0x21d20;
      local_1c = FUN_00021d66();
      puVar2 = &local_1c;
      FUN_00021d6e();
      (*_thunk_FUN_0001816c)();
    }
    in_A0 = *(undefined4 *)((int)puVar2 + 8);
    register0x0000003c = (BADSPACEBASE *)((int)puVar2 + 0x10);
  }
  *(undefined4 *)((int)register0x0000003c + -4) = in_A0;
  iVar1 = *(int *)register0x0000003c;
  *(undefined4 *)register0x0000003c = unaff_A6;
  *(undefined4 *)((int)register0x0000003c + -8) = 0x21d40;
  (*(code *)(DAT_00027efe + iVar1))();
  return;
}


// ==== FUN_00021d66 @ 00021d66 ====

void FUN_00021d66(void)

{
                    /* WARNING: Could not recover jumptable at 0x00021d6a. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026e6e + -0x3c))();
  return;
}


// ==== FUN_00021d6e @ 00021d6e ====

void FUN_00021d6e(void)

{
                    /* WARNING: Could not recover jumptable at 0x00021d78. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026e6e + -0x30))();
  return;
}


// ==== FUN_00021d7c @ 00021d7c ====

void FUN_00021d7c(void)

{
                    /* WARNING: Could not recover jumptable at 0x00021d88. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026ec4 + -0x228))();
  return;
}


// ==== FUN_00021d92 @ 00021d92 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00021d92(void)

{
  undefined4 in_D0;
  
  (**(code **)(_DAT_00000004 + -0x204))();
  return in_D0;
}


// ==== FUN_00021da4 @ 00021da4 ====

undefined1 FUN_00021da4(char *param_1)

{
  char *extraout_A0;
  
  while (*param_1 != '\0') {
    FUN_00021d92();
    param_1 = extraout_A0;
  }
  return 0;
}


// ==== FUN_00021dc8 @ 00021dc8 ====

void FUN_00021dc8(void)

{
  FUN_00021de2();
  return;
}


// ==== FUN_00021dce @ 00021dce ====

void FUN_00021dce(void)

{
  FUN_00021de2();
  return;
}


// ==== FUN_00021de2 @ 00021de2 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00021de2(void)

{
  (**(code **)(_DAT_00000004 + -0x20a))();
  return;
}


// ==== FUN_00021df0 @ 00021df0 ====

void FUN_00021df0(void)

{
  FUN_00021de2();
  return;
}


// ==== FUN_00021e02 @ 00021e02 ====

char * FUN_00021e02(char *param_1,char *param_2)

{
  char cVar1;
  char *pcVar2;
  
  pcVar2 = param_1;
  do {
    cVar1 = *param_2;
    *pcVar2 = cVar1;
    pcVar2 = pcVar2 + 1;
    param_2 = param_2 + 1;
  } while (cVar1 != '\0');
  return param_1;
}


// ==== FUN_00021e12 @ 00021e12 ====

char * FUN_00021e12(char *param_1)

{
  char cVar1;
  char *pcVar2;
  char *pcVar3;
  
  pcVar3 = param_1;
  do {
    pcVar2 = pcVar3 + 1;
    cVar1 = *pcVar3;
    pcVar3 = pcVar2;
  } while (cVar1 != '\0');
  return pcVar2 + (-1 - (int)param_1);
}


// ==== FUN_00021e24 @ 00021e24 ====

ushort FUN_00021e24(void)

{
  int iVar1;
  
  iVar1 = FUN_000222f4();
  DAT_00026966 = iVar1 + 0x3039;
  return (ushort)((uint)(iVar1 + 0x3039) >> 0x10) & 0x7fff;
}


// ==== FUN_00021e82 @ 00021e82 ====

byte FUN_00021e82(undefined4 param_1)

{
  if ((0x40 < param_1._1_1_) && (param_1._1_1_ < 0x5b)) {
    param_1._1_1_ = param_1._1_1_ + 0x20;
  }
  return param_1._1_1_;
}


// ==== FUN_00021e9a @ 00021e9a ====

undefined4 FUN_00021e9a(byte *param_1,byte *param_2)

{
  byte bVar1;
  short sVar2;
  
  sVar2 = 0x7ffe;
  do {
    bVar1 = *param_2;
    param_2 = param_2 + 1;
    if (*param_1 != bVar1) {
      if (*param_1 <= bVar1) {
        return 0xffffffff;
      }
      return 1;
    }
  } while ((*param_1 != 0) && (sVar2 = sVar2 + -1, param_1 = param_1 + 1, sVar2 != -1));
  return 0;
}


// ==== FUN_00021eca @ 00021eca ====

void FUN_00021eca(undefined1 *param_1,undefined1 *param_2,undefined4 param_3)

{
  if (param_2 == param_1) {
    return;
  }
  if (param_2 <= param_1) {
    while (param_3._0_2_ = param_3._0_2_ + -1, param_3._0_2_ != -1) {
      *param_2 = *param_1;
      param_1 = param_1 + 1;
      param_2 = param_2 + 1;
    }
    return;
  }
  param_1 = param_1 + param_3._0_2_;
  param_2 = param_2 + param_3._0_2_;
  while (param_3._0_2_ = param_3._0_2_ + -1, param_3._0_2_ != -1) {
    param_1 = param_1 + -1;
    param_2 = param_2 + -1;
    *param_2 = *param_1;
  }
  return;
}


// ==== FUN_00021ef4 @ 00021ef4 ====

undefined4 FUN_00021ef4(char *param_1)

{
  short sVar2;
  undefined4 uVar1;
  
  do {
    if (*param_1 == '\0') {
      uVar1 = FUN_00022474();
      return uVar1;
    }
    param_1 = param_1 + 1;
    sVar2 = FUN_00022474();
  } while (sVar2 != -1);
  return 0xffffffff;
}


// ==== FUN_00021f2e @ 00021f2e ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00021f2e(void)

{
  int iVar1;
  undefined4 uVar2;
  short sVar3;
  undefined4 extraout_A0;
  undefined4 *puVar4;
  
  uVar2 = FUN_00021fa0();
  sVar3 = 0x4e3;
  puVar4 = &DAT_00026bb0;
  do {
    *puVar4 = 0;
    iVar1 = _DAT_00000004;
    sVar3 = sVar3 + -1;
    puVar4 = puVar4 + 1;
  } while (sVar3 != -1);
  DAT_00026ec4 = _DAT_00000004;
  DAT_00027f02 = (undefined1 *)register0x0000003c;
  if ((*(byte *)(_DAT_00000004 + 0x129) & 0x10) != 0) {
    (**(code **)(_DAT_00000004 + -0x1e))(uVar2,extraout_A0);
  }
  DAT_00026e6e = (**(code **)(iVar1 + -0x198))();
  if (DAT_00026e6e == 0) {
    (**(code **)(iVar1 + -0x6c))();
  }
  else {
    FUN_00021fa8();
  }
  return;
}


// ==== FUN_00021fa0 @ 00021fa0 ====

void FUN_00021fa0(void)

{
  return;
}


// ==== FUN_00021fa8 @ 00021fa8 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00021fa8(undefined2 param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  short sVar3;
  undefined2 uVar4;
  
  DAT_00027f06 = (undefined4 *)FUN_00022d3a(DAT_00026ba4 * 6,0x10000);
  if (DAT_00027f06 == (undefined4 *)0x0) {
    FUN_00022b64(0,0);
    return;
  }
  *(undefined2 *)(DAT_00027f06 + 1) = 0;
  *(undefined2 *)(DAT_00027f06 + 4) = 1;
  *(undefined2 *)((int)DAT_00027f06 + 10) = 1;
  DAT_00027f0a = (undefined4 *)((DAT_00027f02 - *(int *)(DAT_00027f02 + 4)) + 8);
  *DAT_00027f0a = 0x4d414e58;
  iVar1 = FUN_00022d72(0);
  sVar3 = (short)iVar1;
  if (*(int *)(iVar1 + 0xac) == 0) {
    FUN_00022e00(iVar1 + 0x5c);
    DAT_00027f0e = FUN_00022da6(sVar3 + 0x5c);
    if (*(int *)(DAT_00027f0e + 0x24) != 0) {
      FUN_00022abe(**(undefined4 **)(DAT_00027f0e + 0x24));
    }
    FUN_00022318(sVar3,DAT_00027f0e);
    DAT_00027f12 = DAT_00027f0e;
  }
  else {
    FUN_000220e0(sVar3,param_1,param_2);
    DAT_00027eb8 = 1;
    *(ushort *)(DAT_00027f06 + 1) = *(ushort *)(DAT_00027f06 + 1) | 0x8000;
    *(ushort *)((int)DAT_00027f06 + 10) = *(ushort *)((int)DAT_00027f06 + 10) | 0x8000;
  }
  uVar2 = FUN_00022afa();
  *DAT_00027f06 = uVar2;
  iVar1 = FUN_00021d66();
  *(int *)((int)DAT_00027f06 + 6) = iVar1;
  if (iVar1 != 0) {
    uVar2 = FUN_00022b30(0x20de,0x3ed);
    DAT_00027f06[3] = uVar2;
  }
  uVar4 = DAT_00027f16;
  iVar1 = DAT_00027f12;
  (*_thunk_FUN_00010006)();
  FUN_00022928(uVar4,iVar1);
  return;
}


// ==== FUN_000220e0 @ 000220e0 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_000220e0(int param_1,short param_2,undefined2 param_3)

{
  short sVar1;
  char cVar3;
  short sVar2;
  char *pcVar4;
  char *pcVar5;
  char *pcVar6;
  char *pcVar7;
  undefined2 uVar8;
  
  pcVar4 = DAT_00026ba6;
  if (*(int *)(param_1 + 0xac) != 0) {
    pcVar4 = (char *)(*(int *)(*(int *)(param_1 + 0xac) * 4 + 0x10) << 2);
  }
  DAT_00027f18 = param_2 + *pcVar4 + 2;
  DAT_00027f1a = (char *)FUN_00022d3a(DAT_00027f18,0);
  if (DAT_00027f1a != (char *)0x0) {
    sVar1 = (short)*pcVar4;
    pcVar4 = pcVar4 + 1;
    uVar8 = (undefined2)((uint)DAT_00027f1a >> 0x10);
    sVar2 = sVar1;
    (*_thunk_FUN_000222d2)((short)DAT_00027f1a,(short)pcVar4);
    pcVar6 = DAT_00027f1a + sVar1;
    pcVar5 = &DAT_000222a6;
    do {
      cVar3 = *pcVar5;
      *pcVar6 = cVar3;
      pcVar6 = pcVar6 + 1;
      pcVar5 = pcVar5 + 1;
    } while (cVar3 != '\0');
    FUN_000222ae(DAT_00027f1a,param_3,uVar8,(short)((uint)pcVar4 >> 0x10),sVar2);
    DAT_00027f1a[sVar1] = '\0';
    DAT_00027f16 = 1;
    pcVar4 = DAT_00027f1a + sVar1 + 1;
    pcVar6 = pcVar4;
    while( true ) {
      for (; (((cVar3 = *pcVar6, cVar3 == ' ' || (cVar3 == '\t')) || (cVar3 == '\f')) ||
             ((cVar3 == '\r' || (cVar3 == '\n')))); pcVar6 = pcVar6 + 1) {
      }
      if (*pcVar6 < ' ') break;
      pcVar5 = pcVar6;
      if (*pcVar6 == '\"') {
        pcVar6 = pcVar6 + 1;
        while( true ) {
          pcVar7 = pcVar6;
          pcVar5 = pcVar4;
          pcVar6 = pcVar7 + 1;
          cVar3 = *pcVar7;
          pcVar4 = pcVar5;
          if (cVar3 == '\0') break;
          pcVar4 = pcVar5 + 1;
          *pcVar5 = cVar3;
          if (cVar3 == '\"') {
            if (*pcVar6 != '\"') {
              *pcVar5 = '\0';
              break;
            }
            pcVar6 = pcVar7 + 2;
          }
        }
      }
      else {
        while( true ) {
          pcVar6 = pcVar5 + 1;
          cVar3 = *pcVar5;
          if (((cVar3 == '\0') || (cVar3 == ' ')) ||
             ((cVar3 == '\t' || (((cVar3 == '\f' || (cVar3 == '\r')) || (cVar3 == '\n')))))) break;
          *pcVar4 = cVar3;
          pcVar4 = pcVar4 + 1;
          pcVar5 = pcVar6;
        }
        *pcVar4 = '\0';
        pcVar4 = pcVar4 + 1;
      }
      if (cVar3 == '\0') {
        pcVar6 = pcVar6 + -1;
      }
      DAT_00027f16 = DAT_00027f16 + 1;
    }
    *pcVar4 = '\0';
    DAT_00027f12 = FUN_00022d3a((DAT_00027f16 + 1) * 4,0);
    if (DAT_00027f12 == 0) {
      DAT_00027f16 = 0;
    }
    else {
      pcVar4 = DAT_00027f1a;
      for (sVar2 = 0; sVar2 < DAT_00027f16; sVar2 = sVar2 + 1) {
        *(char **)(DAT_00027f12 + sVar2 * 4) = pcVar4;
        pcVar6 = pcVar4;
        do {
          pcVar5 = pcVar6 + 1;
          cVar3 = *pcVar6;
          pcVar6 = pcVar5;
        } while (cVar3 != '\0');
        pcVar4 = pcVar4 + (short)((short)pcVar5 - (short)pcVar4);
      }
      *(undefined4 *)(DAT_00027f12 + sVar2 * 4) = 0;
    }
  }
  return;
}


// ==== FUN_000222a8 @ 000222a8 ====

char * FUN_000222a8(char *param_1,char *param_2)

{
  char cVar1;
  short sVar2;
  char *pcVar3;
  char *pcVar4;
  
  pcVar3 = param_1;
  do {
    pcVar4 = pcVar3;
    pcVar3 = pcVar4 + 1;
  } while (*pcVar4 != '\0');
  sVar2 = 0x7ffe;
  do {
    cVar1 = *param_2;
    pcVar3 = pcVar4 + 1;
    *pcVar4 = cVar1;
    if (cVar1 == '\0') break;
    sVar2 = sVar2 + -1;
    pcVar4 = pcVar3;
    param_2 = param_2 + 1;
  } while (sVar2 != -1);
  if (cVar1 != '\0') {
    *pcVar3 = '\0';
  }
  return param_1;
}


// ==== FUN_000222ae @ 000222ae ====

char * FUN_000222ae(char *param_1,char *param_2,undefined4 param_3)

{
  char cVar1;
  char *pcVar2;
  char *pcVar3;
  
  pcVar2 = param_1;
  do {
    pcVar3 = pcVar2;
    pcVar2 = pcVar3 + 1;
  } while (*pcVar3 != '\0');
  param_3._0_2_ = param_3._0_2_ + -1;
  do {
    cVar1 = *param_2;
    pcVar2 = pcVar3 + 1;
    *pcVar3 = cVar1;
    if (cVar1 == '\0') break;
    param_3._0_2_ = param_3._0_2_ + -1;
    pcVar3 = pcVar2;
    param_2 = param_2 + 1;
  } while (param_3._0_2_ != -1);
  if (cVar1 != '\0') {
    *pcVar2 = '\0';
  }
  return param_1;
}


// ==== FUN_000222d2 @ 000222d2 ====

char * FUN_000222d2(char *param_1,char *param_2,undefined4 param_3)

{
  char cVar1;
  char *pcVar2;
  bool bVar3;
  
  bVar3 = param_3._0_2_ == 0;
  pcVar2 = param_1;
  while ((!bVar3 && (param_3._0_2_ = param_3._0_2_ + -1, param_3._0_2_ != -1))) {
    cVar1 = *param_2;
    *pcVar2 = cVar1;
    bVar3 = cVar1 == '\0';
    pcVar2 = pcVar2 + 1;
    param_2 = param_2 + 1;
  }
  if (!bVar3) {
    param_3._0_2_ = param_3._0_2_ + 1;
  }
  while (param_3._0_2_ = param_3._0_2_ + -1, param_3._0_2_ != -1) {
    *pcVar2 = '\0';
    pcVar2 = pcVar2 + 1;
  }
  return param_1;
}


// ==== FUN_000222f4 @ 000222f4 ====

undefined8 FUN_000222f4(void)

{
  uint in_D0;
  uint in_D1;
  
  return CONCAT44((in_D1 >> 0x10) * (in_D0 & 0xffff) * 0x10000 + (in_D1 & 0xffff) * (in_D0 & 0xffff)
                  + (in_D0 >> 0x10) * (in_D1 & 0xffff) * 0x10000,in_D1);
}


// ==== FUN_00022318 @ 00022318 ====

void FUN_00022318(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  
  DAT_00027f1e = FUN_00021d7c(s_icon_library_000223b6,0);
  if (DAT_00027f1e != 0) {
    iVar1 = FUN_00022f10(*(undefined4 *)(*(int *)(param_2 + 0x24) + 4));
    if (iVar1 != 0) {
      iVar2 = FUN_00022ef6(*(undefined4 *)(iVar1 + 0x36),s_WINDOW_000223c3);
      if (iVar2 != 0) {
        iVar2 = FUN_00022b30(iVar2,0x3ed);
        if (iVar2 != 0) {
          *(undefined4 *)(param_1 + 0xa4) = *(undefined4 *)(iVar2 * 4 + 8);
          *(int *)(param_1 + 0x9c) = iVar2;
          uVar3 = FUN_00022b30(&DAT_000223ca,0x3ed);
          *(undefined4 *)(param_1 + 0xa0) = uVar3;
        }
      }
      FUN_00022f04(iVar1);
    }
    thunk_FUN_00022b98(DAT_00027f1e);
    DAT_00027f1e = 0;
  }
  return;
}


// ==== FUN_000223cc @ 000223cc ====

undefined8 FUN_000223cc(void)

{
  int in_D0;
  int iVar1;
  int in_D1;
  bool bVar2;
  
  bVar2 = in_D0 < 0;
  if (in_D1 < 0) {
    bVar2 = !bVar2;
  }
  iVar1 = FUN_00022424();
  if (bVar2) {
    iVar1 = -iVar1;
  }
  return CONCAT44(iVar1,in_D1);
}


// ==== FUN_000223f4 @ 000223f4 ====

undefined8 FUN_000223f4(void)

{
  int iVar1;
  int in_D0;
  undefined4 in_D1;
  int extraout_D1;
  
  FUN_00022424();
  iVar1 = extraout_D1;
  if (in_D0 < 0) {
    iVar1 = -extraout_D1;
  }
  return CONCAT44(iVar1,in_D1);
}


// ==== FUN_0002240e @ 0002240e ====

undefined8 FUN_0002240e(void)

{
  undefined4 in_D1;
  undefined4 extraout_D1;
  
  FUN_00022424();
  return CONCAT44(extraout_D1,in_D1);
}


// ==== FUN_0002241a @ 0002241a ====

void FUN_0002241a(void)

{
  FUN_00022424();
  return;
}


// ==== FUN_00022424 @ 00022424 ====

undefined8 FUN_00022424(void)

{
  uint in_D0;
  uint uVar1;
  uint in_D1;
  uint uVar2;
  short sVar3;
  bool bVar4;
  
  if ((short)(in_D1 >> 0x10) != 0) {
    uVar2 = in_D0 >> 0x10;
    uVar1 = in_D0 << 0x10;
    sVar3 = 0xf;
    do {
      bVar4 = CARRY4(uVar1,uVar1);
      uVar1 = uVar1 * 2;
      uVar2 = uVar2 * 2 + (uint)bVar4;
      if (in_D1 <= uVar2) {
        uVar2 = uVar2 - in_D1;
        uVar1 = CONCAT22((short)(uVar1 >> 0x10),(short)uVar1 + 1);
      }
      sVar3 = sVar3 + -1;
    } while (sVar3 != -1);
    return CONCAT44(uVar1,uVar2);
  }
  uVar1 = in_D1 & 0xffff;
  uVar2 = CONCAT22((short)((in_D0 >> 0x10) % uVar1),(short)in_D0);
  return CONCAT44(CONCAT22((short)((in_D0 >> 0x10) / uVar1),(short)(uVar2 / uVar1)),uVar2 % uVar1);
}


// ==== FUN_00022474 @ 00022474 ====

void FUN_00022474(void)

{
  FUN_0002248a();
  return;
}


// ==== FUN_0002248a @ 0002248a ====
// decompile failed: 
Low-level Error: Cannot properly adjust input varnodes
// ==== FUN_000224cc @ 000224cc ====
// decompile failed: 
Low-level Error: Cannot properly adjust input varnodes
// ==== FUN_00022530 @ 00022530 ====

ushort FUN_00022530(undefined4 *param_1)

{
  ushort uVar1;
  ushort uVar2;
  
  uVar1 = 0;
  if (param_1 == (undefined4 *)0x0) {
    uVar1 = 0xffff;
  }
  else {
    if (*(char *)(param_1 + 3) != '\0') {
      if ((*(byte *)(param_1 + 3) & 4) != 0) {
        uVar1 = FUN_000225b4((short)param_1);
      }
      uVar2 = FUN_00022a62();
      uVar1 = uVar2 | uVar1;
      if ((*(byte *)(param_1 + 3) & 2) != 0) {
        FUN_000227b2((short)param_1[2]);
      }
      if ((*(byte *)(param_1 + 3) & 0x20) != 0) {
        FUN_00022856((short)*(undefined4 *)((int)param_1 + 0x12));
        FUN_000227b2((short)*(undefined4 *)((int)param_1 + 0x12));
      }
    }
    *param_1 = 0;
    param_1[1] = 0;
    param_1[2] = 0;
    *(undefined1 *)(param_1 + 3) = 0;
  }
  return uVar1;
}


// ==== FUN_000225b4 @ 000225b4 ====

ushort FUN_000225b4(int *param_1,undefined4 param_2)

{
  byte *pbVar1;
  ushort uVar2;
  short sVar3;
  short sVar4;
  byte local_5;
  
  uVar2 = param_2._0_2_;
  DAT_00027f22 = &LAB_00022508;
  if ((*(byte *)(param_1 + 3) & 0x10) != 0) {
    DAT_00027f22 = &LAB_00022508;
    return 0xffff;
  }
  if (((*(byte *)(param_1 + 3) & 4) == 0) ||
     (sVar4 = (short)*param_1 - (short)param_1[2],
     sVar3 = FUN_0002287a((short)((uint)param_1[2] >> 0x10),sVar4), sVar3 == sVar4)) {
    if (param_2._0_2_ == 0xffff) {
      *(byte *)(param_1 + 3) = *(byte *)(param_1 + 3) & 0xfb;
      *param_1 = 0;
      param_1[1] = 0;
      return 0;
    }
    if (param_1[2] == 0) {
      FUN_000226ce((short)param_1);
    }
    if (*(short *)(param_1 + 4) != 1) {
      *param_1 = param_1[2];
      param_1[1] = param_1[2] + (int)*(short *)(param_1 + 4);
      *(byte *)(param_1 + 3) = *(byte *)(param_1 + 3) | 4;
      pbVar1 = (byte *)*param_1;
      *param_1 = *param_1 + 1;
      *pbVar1 = param_2._1_1_;
      return (ushort)param_2._1_1_;
    }
    local_5 = param_2._1_1_;
    sVar4 = FUN_0002287a((short)((uint)&local_5 >> 0x10),1);
    if (sVar4 == 1) {
      return uVar2;
    }
  }
  *(byte *)(param_1 + 3) = *(byte *)(param_1 + 3) | 0x10;
  *param_1 = 0;
  param_1[1] = 0;
  return 0xffff;
}


// ==== FUN_000226ce @ 000226ce ====

void FUN_000226ce(int param_1)

{
  int iVar1;
  short sVar2;
  
  iVar1 = FUN_0002279e();
  if (iVar1 == 0) {
    *(undefined2 *)(param_1 + 0x10) = 1;
    *(int *)(param_1 + 8) = param_1 + 0xe;
  }
  else {
    *(undefined2 *)(param_1 + 0x10) = 0x400;
    *(byte *)(param_1 + 0xc) = *(byte *)(param_1 + 0xc) | 2;
    *(int *)(param_1 + 8) = iVar1;
    sVar2 = FUN_000227fe();
    if (sVar2 != 0) {
      *(byte *)(param_1 + 0xc) = *(byte *)(param_1 + 0xc) | 0x80;
    }
  }
  return;
}


// ==== FUN_0002275e @ 0002275e ====

undefined4 * FUN_0002275e(int param_1)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  
  DAT_00027f26 = &LAB_0002272c;
  puVar1 = (undefined4 *)FUN_00022d3a(param_1 + 8,0);
  if (puVar1 == (undefined4 *)0x0) {
    puVar2 = (undefined4 *)0x0;
  }
  else {
    *puVar1 = DAT_00026c86;
    puVar1[1] = param_1;
    puVar2 = puVar1 + 2;
    DAT_00026c86 = puVar1;
  }
  return puVar2;
}


// ==== FUN_0002279e @ 0002279e ====

void FUN_0002279e(undefined4 param_1)

{
  FUN_0002275e(param_1._0_2_);
  return;
}


// ==== FUN_000227b2 @ 000227b2 ====

undefined4 FUN_000227b2(int param_1)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  
  puVar1 = DAT_00026c86;
  puVar3 = (undefined4 *)0x0;
  while( true ) {
    puVar2 = puVar1;
    if (puVar2 == (undefined4 *)0x0) {
      return 0xffffffff;
    }
    if ((undefined4 *)(param_1 + -8) == puVar2) break;
    puVar1 = (undefined4 *)*puVar2;
    puVar3 = puVar2;
  }
  if (puVar3 == (undefined4 *)0x0) {
    DAT_00026c86 = (undefined4 *)*puVar2;
  }
  else {
    *puVar3 = *puVar2;
  }
  FUN_00022d8a(puVar2,puVar2[1] + 8);
  return 0;
}


// ==== FUN_000227fe @ 000227fe ====

uint FUN_000227fe(int param_1)

{
  uint uVar1;
  int iVar2;
  
  if (((param_1 < 0) || (DAT_00026ba4 <= param_1._0_2_)) ||
     (*(int *)(DAT_00027f06 + param_1._0_2_ * 6) == 0)) {
    DAT_00027f2a = 2;
    uVar1 = 0xffffffff;
  }
  else {
    iVar2 = FUN_00022b0e(*(undefined4 *)(DAT_00027f06 + param_1._0_2_ * 6));
    uVar1 = (uint)(iVar2 != 0);
  }
  return uVar1;
}


// ==== FUN_00022856 @ 00022856 ====

undefined4 FUN_00022856(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_00022ace(param_1);
  if (iVar1 == 0) {
    DAT_00027f2a = FUN_00022b06();
    uVar2 = 0xffffffff;
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}


// ==== FUN_0002287a @ 0002287a ====
// decompile failed: 
Low-level Error: Cannot properly adjust input varnodes
// ==== FUN_000228f8 @ 000228f8 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint FUN_000228f8(void)

{
  uint uVar1;
  
  uVar1 = FUN_00022df2(0,0x1000);
  if ((uVar1 & 0x1000) != 0) {
    if (DAT_00027eb8 == 0) {
      return uVar1;
    }
    (*_thunk_FUN_0001816c)();
  }
  return 0;
}


// ==== FUN_00022928 @ 00022928 ====

void FUN_00022928(void)

{
  if (DAT_00027f22 != (code *)0x0) {
    (*DAT_00027f22)();
  }
  FUN_00022946();
  return;
}


// ==== FUN_00022946 @ 00022946 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00022946(void)

{
  short sVar1;
  undefined1 *puVar2;
  undefined2 local_10;
  undefined2 uVar3;
  
  puVar2 = &stack0xfffffffc;
  if (DAT_00027f06 != 0) {
    for (sVar1 = 0; sVar1 < DAT_00026ba4; sVar1 = sVar1 + 1) {
      FUN_00022a62();
    }
    FUN_00022d8a((short)DAT_00027f06,DAT_00026ba4 * 6);
  }
  if (DAT_00027f26 != (code *)0x0) {
    (*DAT_00027f26)();
  }
  if (DAT_00026baa != 0) {
    (*_thunk_FUN_00022b54)((short)DAT_00026baa);
  }
  if (DAT_00027f2c != (undefined4 *)0x0) {
    *DAT_00027f2c = DAT_00027f30;
  }
  if (DAT_00027f34 != 0) {
    FUN_00022b98((short)DAT_00027f34);
  }
  if (DAT_00027efe != 0) {
    FUN_00022b98((short)DAT_00027efe);
  }
  if (DAT_00027f38 != 0) {
    FUN_00022b98((short)DAT_00027f38);
  }
  if (DAT_00027f3c != 0) {
    FUN_00022b98((short)DAT_00027f3c);
  }
  if ((*(byte *)(_DAT_00000004 + 0x129) & 0x10) != 0) {
    local_10 = (undefined2)((uint)&stack0xfffffffc >> 0x10);
    uVar3 = SUB42(&stack0xfffffffc,0);
    (**(code **)(_DAT_00000004 + -0x1e))();
    puVar2 = (undefined1 *)CONCAT22(local_10,uVar3);
  }
  if (DAT_00027f0e == 0) {
    if (DAT_00027f1a != 0) {
      FUN_00022d8a((short)DAT_00027f1a,DAT_00027f18);
      FUN_00022d8a(DAT_00027f12,(int)(short)(DAT_00027f16 + 1) << 2);
    }
  }
  else {
    FUN_00022d7e();
    FUN_00022de6((short)DAT_00027f0e);
  }
  return *(undefined4 *)(puVar2 + -4);
}


// ==== FUN_00022a62 @ 00022a62 ====

undefined4 FUN_00022a62(int param_1)

{
  undefined4 uVar1;
  int *piVar2;
  
  piVar2 = (int *)(DAT_00027f06 + param_1._0_2_ * 6);
  if (((param_1 < 0) || (DAT_00026ba4 <= param_1._0_2_)) || (*piVar2 == 0)) {
    DAT_00027f2a = 2;
    uVar1 = 0xffffffff;
  }
  else {
    if ((*(byte *)(piVar2 + 1) & 0x80) == 0) {
      FUN_00022ab2(*piVar2);
    }
    *piVar2 = 0;
    uVar1 = 0;
  }
  return uVar1;
}


// ==== thunk_FUN_00022ab2 @ 00022aae ====

void thunk_FUN_00022ab2(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022aba. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026e6e + -0x24))();
  return;
}


// ==== FUN_00022ab2 @ 00022ab2 ====

void FUN_00022ab2(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022aba. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026e6e + -0x24))();
  return;
}


// ==== FUN_00022abe @ 00022abe ====

void FUN_00022abe(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022ac6. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026e6e + -0x7e))();
  return;
}


// ==== thunk_FUN_00022ace @ 00022aca ====

void thunk_FUN_00022ace(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022ad6. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026e6e + -0x48))();
  return;
}


// ==== FUN_00022ace @ 00022ace ====

void FUN_00022ace(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022ad6. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026e6e + -0x48))();
  return;
}


// ==== thunk_FUN_00022ade @ 00022ada ====

void thunk_FUN_00022ade(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022ae8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026e6e + -0x66))();
  return;
}


// ==== FUN_00022ade @ 00022ade ====

void FUN_00022ade(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022ae8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026e6e + -0x66))();
  return;
}


// ==== FUN_00022aec @ 00022aec ====

void FUN_00022aec(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022af6. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026e6e + -0x6c))();
  return;
}


// ==== FUN_00022afa @ 00022afa ====

void FUN_00022afa(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022afe. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026e6e + -0x36))();
  return;
}


// ==== thunk_FUN_00022b06 @ 00022b02 ====

void thunk_FUN_00022b06(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022b0a. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026e6e + -0x84))();
  return;
}


// ==== FUN_00022b06 @ 00022b06 ====

void FUN_00022b06(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022b0a. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026e6e + -0x84))();
  return;
}


// ==== FUN_00022b0e @ 00022b0e ====

void FUN_00022b0e(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022b16. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026e6e + -0xd8))();
  return;
}


// ==== thunk_FUN_00022b1e @ 00022b1a ====

void thunk_FUN_00022b1e(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022b28. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026e6e + -0x54))();
  return;
}


// ==== FUN_00022b1e @ 00022b1e ====

void FUN_00022b1e(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022b28. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026e6e + -0x54))();
  return;
}


// ==== thunk_FUN_00022b30 @ 00022b2c ====

void thunk_FUN_00022b30(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022b3a. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026e6e + -0x1e))();
  return;
}


// ==== FUN_00022b30 @ 00022b30 ====

void FUN_00022b30(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022b3a. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026e6e + -0x1e))();
  return;
}


// ==== thunk_FUN_00022b42 @ 00022b3e ====

void thunk_FUN_00022b42(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022b4c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026e6e + -0x2a))();
  return;
}


// ==== FUN_00022b42 @ 00022b42 ====

void FUN_00022b42(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022b4c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026e6e + -0x2a))();
  return;
}


// ==== thunk_FUN_00022b54 @ 00022b50 ====

void thunk_FUN_00022b54(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022b5c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026e6e + -0x5a))();
  return;
}


// ==== FUN_00022b54 @ 00022b54 ====

void FUN_00022b54(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022b5c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026e6e + -0x5a))();
  return;
}


// ==== thunk_FUN_00021d6e @ 00022b60 ====

void thunk_FUN_00021d6e(void)

{
                    /* WARNING: Could not recover jumptable at 0x00021d78. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026e6e + -0x30))();
  return;
}


// ==== FUN_00022b64 @ 00022b64 ====

void FUN_00022b64(void)

{
  (**(code **)(DAT_00026ec4 + -0x6c))();
  return;
}


// ==== FUN_00022b7c @ 00022b7c ====

void FUN_00022b7c(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022b84. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026ec4 + -0xd8))();
  return;
}


// ==== FUN_00022b88 @ 00022b88 ====

void FUN_00022b88(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022b90. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026ec4 + -0x1c2))();
  return;
}


// ==== thunk_FUN_00022b98 @ 00022b94 ====

void thunk_FUN_00022b98(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022ba0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026ec4 + -0x19e))();
  return;
}


// ==== FUN_00022b98 @ 00022b98 ====

void FUN_00022b98(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022ba0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026ec4 + -0x19e))();
  return;
}


// ==== FUN_00022ba4 @ 00022ba4 ====

int FUN_00022ba4(int param_1,undefined1 param_2)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  
  iVar1 = FUN_00022c82(0xffffffff);
  if (iVar1 == -1) {
    iVar2 = 0;
  }
  else {
    iVar2 = thunk_FUN_00022d3a(0x22,0x10001);
    if (iVar2 == 0) {
      FUN_00022d9a(iVar1);
      iVar2 = 0;
    }
    else {
      *(int *)(iVar2 + 10) = param_1;
      *(undefined1 *)(iVar2 + 9) = param_2;
      *(undefined1 *)(iVar2 + 8) = 4;
      *(undefined1 *)(iVar2 + 0xe) = 0;
      *(char *)(iVar2 + 0xf) = (char)iVar1;
      uVar3 = thunk_FUN_00022d72(0);
      *(undefined4 *)(iVar2 + 0x10) = uVar3;
      if (param_1 == 0) {
        FUN_00022db2(iVar2 + 0x14);
      }
      else {
        FUN_00022c76(iVar2);
      }
    }
  }
  return iVar2;
}


// ==== FUN_00022c30 @ 00022c30 ====

void FUN_00022c30(int param_1)

{
  if (*(int *)(param_1 + 10) != 0) {
    FUN_00022dda(param_1);
  }
  *(undefined1 *)(param_1 + 8) = 0xff;
  *(undefined4 *)(param_1 + 0x14) = 0xffffffff;
  FUN_00022d9a(*(undefined1 *)(param_1 + 0xf));
  thunk_FUN_00022d8a(param_1,0x22);
  return;
}


// ==== FUN_00022c76 @ 00022c76 ====

void FUN_00022c76(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022c7e. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026ec4 + -0x162))();
  return;
}


// ==== FUN_00022c82 @ 00022c82 ====

void FUN_00022c82(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022c8a. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026ec4 + -0x14a))();
  return;
}


// ==== FUN_00022c8e @ 00022c8e ====

void FUN_00022c8e(undefined4 param_1)

{
  FUN_00022cb6(param_1,0x30);
  return;
}


// ==== FUN_00022ca4 @ 00022ca4 ====

void FUN_00022ca4(undefined4 param_1)

{
  FUN_00022cfa(param_1);
  return;
}


// ==== FUN_00022cb6 @ 00022cb6 ====

int FUN_00022cb6(int param_1,undefined4 param_2)

{
  int iVar1;
  
  if (param_1 == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = thunk_FUN_00022d3a(param_2,0x10001);
    if (iVar1 == 0) {
      iVar1 = 0;
    }
    else {
      *(undefined1 *)(iVar1 + 8) = 5;
      *(undefined2 *)(iVar1 + 0x12) = param_2._2_2_;
      *(int *)(iVar1 + 0xe) = param_1;
    }
  }
  return iVar1;
}


// ==== FUN_00022cfa @ 00022cfa ====

undefined4 FUN_00022cfa(int param_1)

{
  undefined4 uVar1;
  
  uVar1 = 0;
  if (param_1 != 0) {
    *(undefined1 *)(param_1 + 8) = 0xff;
    *(undefined4 *)(param_1 + 0x14) = 0xffffffff;
    *(undefined4 *)(param_1 + 0x18) = 0xffffffff;
    uVar1 = thunk_FUN_00022d8a(param_1,*(undefined2 *)(param_1 + 0x12));
  }
  return uVar1;
}


// ==== thunk_FUN_00022d3a @ 00022d36 ====

void thunk_FUN_00022d3a(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022d44. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026ec4 + -0xc6))();
  return;
}


// ==== FUN_00022d3a @ 00022d3a ====

void FUN_00022d3a(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022d44. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026ec4 + -0xc6))();
  return;
}


// ==== FUN_00022d48 @ 00022d48 ====

void FUN_00022d48(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022d4c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026ec4 + -0x78))();
  return;
}


// ==== FUN_00022d50 @ 00022d50 ====

void FUN_00022d50(void)

{
  (**(code **)(DAT_00026ec4 + -0x1c8))();
  return;
}


// ==== FUN_00022d66 @ 00022d66 ====

void FUN_00022d66(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022d6a. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026ec4 + -0x7e))();
  return;
}


// ==== thunk_FUN_00022d72 @ 00022d6e ====

void thunk_FUN_00022d72(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022d7a. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026ec4 + -0x126))();
  return;
}


// ==== FUN_00022d72 @ 00022d72 ====

void FUN_00022d72(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022d7a. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026ec4 + -0x126))();
  return;
}


// ==== FUN_00022d7e @ 00022d7e ====

void FUN_00022d7e(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022d82. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026ec4 + -0x84))();
  return;
}


// ==== thunk_FUN_00022d8a @ 00022d86 ====

void thunk_FUN_00022d8a(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022d96. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026ec4 + -0xd2))();
  return;
}


// ==== FUN_00022d8a @ 00022d8a ====

void FUN_00022d8a(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022d96. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026ec4 + -0xd2))();
  return;
}


// ==== FUN_00022d9a @ 00022d9a ====

void FUN_00022d9a(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022da2. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026ec4 + -0x150))();
  return;
}


// ==== FUN_00022da6 @ 00022da6 ====

void FUN_00022da6(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022dae. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026ec4 + -0x174))();
  return;
}


// ==== FUN_00022db2 @ 00022db2 ====

void FUN_00022db2(int *param_1)

{
  *param_1 = (int)param_1;
  *param_1 = *param_1 + 4;
  param_1[1] = 0;
  param_1[2] = (int)param_1;
  return;
}


// ==== FUN_00022dc4 @ 00022dc4 ====

void FUN_00022dc4(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022dd6. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026ec4 + -0x1bc))();
  return;
}


// ==== FUN_00022dda @ 00022dda ====

void FUN_00022dda(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022de2. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026ec4 + -0x168))();
  return;
}


// ==== FUN_00022de6 @ 00022de6 ====

void FUN_00022de6(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022dee. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026ec4 + -0x17a))();
  return;
}


// ==== FUN_00022df2 @ 00022df2 ====

void FUN_00022df2(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022dfc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026ec4 + -0x132))();
  return;
}


// ==== FUN_00022e00 @ 00022e00 ====

void FUN_00022e00(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022e08. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026ec4 + -0x180))();
  return;
}


// ==== FUN_00022e0c @ 00022e0c ====

void FUN_00022e0c(void)

{
  (**(code **)(DAT_00026e72 + -0x1e))();
  return;
}


// ==== FUN_00022e2e @ 00022e2e ====

void FUN_00022e2e(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022e3c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026e72 + -300))();
  return;
}


// ==== FUN_00022e40 @ 00022e40 ====

void FUN_00022e40(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022e44. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026e72 + -0x1ce))();
  return;
}


// ==== FUN_00022e48 @ 00022e48 ====

void FUN_00022e48(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022e56. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026e72 + -0xf6))();
  return;
}


// ==== FUN_00022e5a @ 00022e5a ====

void FUN_00022e5a(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022e68. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026e72 + -0x186))();
  return;
}


// ==== FUN_00022e6c @ 00022e6c ====

void FUN_00022e6c(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022e74. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026e72 + -0xc6))();
  return;
}


// ==== FUN_00022e78 @ 00022e78 ====

void FUN_00022e78(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022e86. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026e72 + -0xf0))();
  return;
}


// ==== FUN_00022e8a @ 00022e8a ====

void FUN_00022e8a(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022e8e. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026e72 + -0x1c8))();
  return;
}


// ==== FUN_00022e92 @ 00022e92 ====

void FUN_00022e92(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022ea0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026e72 + -0x132))();
  return;
}


// ==== FUN_00022ea4 @ 00022ea4 ====

void FUN_00022ea4(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022eb0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026e72 + -0x156))();
  return;
}


// ==== FUN_00022eb4 @ 00022eb4 ====

void FUN_00022eb4(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022ec0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026e72 + -0x15c))();
  return;
}


// ==== FUN_00022ec4 @ 00022ec4 ====

void FUN_00022ec4(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022ed0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026e72 + -0x162))();
  return;
}


// ==== FUN_00022ed4 @ 00022ed4 ====

void FUN_00022ed4(void)

{
  (**(code **)(DAT_00026e72 + -0x3c))();
  return;
}


// ==== FUN_00022eee @ 00022eee ====

void FUN_00022eee(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022ef2. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026e72 + -0x10e))();
  return;
}


// ==== FUN_00022ef6 @ 00022ef6 ====

void FUN_00022ef6(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022f00. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00027f1e + -0x60))();
  return;
}


// ==== FUN_00022f04 @ 00022f04 ====

void FUN_00022f04(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022f0c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00027f1e + -0x5a))();
  return;
}


// ==== FUN_00022f10 @ 00022f10 ====

void FUN_00022f10(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022f18. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00027f1e + -0x4e))();
  return;
}


// ==== FUN_00022f1c @ 00022f1c ====

void FUN_00022f1c(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022f24. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026e76 + -0x48))();
  return;
}


// ==== FUN_00022f28 @ 00022f28 ====

void FUN_00022f28(void)

{
                    /* WARNING: Could not recover jumptable at 0x00022f2c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_00026e76 + -0x4e))();
  return;
}


// ==== FUN_00022f30 @ 00022f30 ====

void FUN_00022f30(void)

{
  (**(code **)(DAT_00027eba + -0x30))();
  return;
}


// ==== entry @ 00022f50 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void entry(void)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  short sVar4;
  undefined4 extraout_A0;
  undefined4 *puVar5;
  int unaff_A4;
  
  uVar2 = FUN_00021fa0();
  sVar4 = 0x4e3;
  puVar5 = (undefined4 *)(unaff_A4 + -0x439e);
  do {
    *puVar5 = 0;
    sVar4 = sVar4 + -1;
    puVar5 = puVar5 + 1;
  } while (sVar4 != -1);
  *(BADSPACEBASE **)(unaff_A4 + -0x304c) = register0x0000003c;
  iVar1 = _DAT_00000004;
  *(int *)(unaff_A4 + -0x408a) = _DAT_00000004;
  if ((*(byte *)(iVar1 + 0x129) & 0x10) != 0) {
    (**(code **)(iVar1 + -0x1e))(uVar2,extraout_A0);
  }
  iVar3 = (**(code **)(iVar1 + -0x198))();
  *(int *)(unaff_A4 + -0x40e0) = iVar3;
  if (iVar3 == 0) {
    (**(code **)(iVar1 + -0x6c))();
  }
  else {
    FUN_00021fa8();
  }
  return;
}


// ==== thunk_FUN_00010006 @ 00022f56 ====

void thunk_FUN_00010006(undefined4 param_1)

{
  short sVar1;
  char cVar2;
  int unaff_A4;
  
  DAT_00bfe001 = DAT_00bfe001 | 2;
  (**(code **)(unaff_A4 + -0x7e1e))();
  FUN_00012570();
  (**(code **)(*(int *)(unaff_A4 + -0x40d8) + -0x4e))();
  *(undefined1 *)(unaff_A4 + -0x69b0) = 0xff;
  FUN_00012910();
  *(undefined2 *)(unaff_A4 + -0x6352) = 0xffff;
  if (1 < param_1._0_2_) {
    *(undefined **)(unaff_A4 + -0x4078) = &DAT_000233a8;
  }
  (**(code **)(unaff_A4 + -0x7de8))();
  FUN_00016670();
  *(BADSPACEBASE **)(unaff_A4 + -0x4178) = register0x0000003c;
  FUN_000134bc();
  (**(code **)(unaff_A4 + -0x7e5a))();
LAB_00010066:
  do {
    FUN_00011234();
    *(undefined1 *)(unaff_A4 + -0x5b07) = 0;
    *(undefined1 *)(unaff_A4 + -0x5a3e) = 0;
    *(undefined2 *)(unaff_A4 + -0x42b2) = 0;
    *(undefined2 *)(unaff_A4 + -0x42ba) = 0;
    *(undefined1 *)(unaff_A4 + -0x5a5e) = 0;
    *(undefined1 *)(unaff_A4 + -0x5a4a) = 0;
    FUN_00013562();
    *(undefined1 *)(unaff_A4 + -0x5c9c) = 0;
    *(undefined2 *)(unaff_A4 + -0x5c3c) = 0;
    *(undefined1 *)(unaff_A4 + -0x5a3d) = 0;
    *(undefined1 *)(unaff_A4 + -0x5c7f) = 0;
    (**(code **)(unaff_A4 + -0x7e4e))();
    FUN_0001653c();
    if (*(short *)(unaff_A4 + -0x42be) == 0) {
      (**(code **)(unaff_A4 + -0x7f74))();
    }
    sVar1 = (**(code **)(unaff_A4 + -0x7e42))();
  } while (sVar1 != 0);
  (**(code **)(unaff_A4 + -0x7d8e))();
  (**(code **)(unaff_A4 + -0x7e36))();
  (**(code **)(unaff_A4 + -0x7f68))();
  FUN_0001535a();
  (**(code **)(unaff_A4 + -0x7f62))();
  if (*(short *)(unaff_A4 + -0x42be) != 0) goto LAB_000100ea;
  do {
    FUN_000135a8();
    FUN_00013684();
    *(undefined2 *)(unaff_A4 + -0x42be) = 0;
    *(undefined1 *)(unaff_A4 + -0x5aa8) = 0;
    *(undefined2 *)(unaff_A4 + -0x42c2) = 0;
    *(undefined2 *)(unaff_A4 + -0x42bc) = 0;
LAB_000100ea:
    *(undefined1 *)(unaff_A4 + -0x69b0) = 0;
    *(undefined2 *)(unaff_A4 + -0x42be) = 0;
    (**(code **)(unaff_A4 + -0x7fbc))();
    (**(code **)(unaff_A4 + -0x7fb6))();
    if (*(short *)(unaff_A4 + -0x42b2) != 0) {
      *(undefined2 *)(unaff_A4 + -0x42ba) = 2;
    }
    *(undefined1 *)(unaff_A4 + -0x42aa) = 0xff;
LAB_0001010e:
    (**(code **)(unaff_A4 + -0x7de2))();
    if (*(char *)(unaff_A4 + -0x5c3c) != '\0') {
LAB_000101c6:
      (**(code **)(unaff_A4 + -0x7f9e))();
      FUN_00016bbc();
      FUN_000173e6();
      *(undefined2 *)(unaff_A4 + -0x42aa) = 0;
      *(char *)(unaff_A4 + -0x4072) = -(*(short *)(unaff_A4 + -0x42b2) == 1);
      (**(code **)(unaff_A4 + -0x7e48))();
      if (*(short *)(unaff_A4 + -0x407e) != 0) {
        DAT_00bfe001 = DAT_00bfe001 & 0xfd;
        FUN_00012470();
        FUN_00011234();
        FUN_000134d8();
        return;
      }
      *(undefined1 *)(unaff_A4 + -0x69b0) = 0xff;
      *(undefined4 *)(unaff_A4 + -0x5848) = 0;
      if (*(char *)(unaff_A4 + -0x4072) == '\0') {
        FUN_00011234();
        (**(code **)(unaff_A4 + -0x7e30))();
      }
      goto LAB_00010066;
    }
    if (*(char *)(unaff_A4 + -0x5aa8) != '\0') {
      (**(code **)(unaff_A4 + -0x7e2a))();
      goto LAB_0001010e;
    }
    if ((*(char *)(unaff_A4 + -0x5c9a) == '\0') || (*(short *)(unaff_A4 + -0x5c42) == 0)) {
      FUN_00010228();
      FUN_000114d8();
      if (*(char *)(unaff_A4 + -0x5a3e) != '\0') goto LAB_00010066;
      if (((*(short *)(unaff_A4 + -0x42b2) == 1) &&
          (sVar1 = (**(code **)(unaff_A4 + -0x7d40))(), sVar1 != 0)) ||
         (*(char *)(unaff_A4 + -0x5c3c) != '\0')) goto LAB_000101c6;
      goto LAB_0001010e;
    }
    *(undefined2 *)(unaff_A4 + -0x5c42) = 0;
    *(undefined1 *)(unaff_A4 + -0x5c9a) = 0;
    (**(code **)(unaff_A4 + -0x7f9e))();
    *(undefined4 *)(unaff_A4 + -0x5848) = 0;
    FUN_00016bbc();
    FUN_000173e6();
    FUN_00011234();
    if (*(char *)(unaff_A4 + -0x5ca1) != '\0') {
      *(char *)(unaff_A4 + -0x5ca2) = *(char *)(unaff_A4 + -0x5ca2) + '\x01';
    }
    FUN_000111fc();
    (**(code **)(unaff_A4 + -0x7d8e))();
    (**(code **)(unaff_A4 + -0x7f74))();
    cVar2 = (**(code **)(unaff_A4 + -0x7e42))();
    if (cVar2 != '\0') goto LAB_00010066;
    FUN_0001653c();
    (**(code **)(unaff_A4 + -0x7e36))();
    (**(code **)(unaff_A4 + -0x7f68))();
    FUN_0001535a();
    (**(code **)(unaff_A4 + -0x7f62))();
  } while( true );
}


// ==== thunk_FUN_0001020e @ 00022f5c ====

void thunk_FUN_0001020e(void)

{
  DAT_00bfe001 = DAT_00bfe001 & 0xfd;
  FUN_00012470();
  FUN_00011234();
  FUN_000134d8();
  return;
}


// ==== thunk_FUN_0001020e @ 00022f62 ====

void thunk_FUN_0001020e(void)

{
  DAT_00bfe001 = DAT_00bfe001 & 0xfd;
  FUN_00012470();
  FUN_00011234();
  FUN_000134d8();
  return;
}


// ==== thunk_FUN_000103a6 @ 00022f68 ====

void thunk_FUN_000103a6(void)

{
  undefined2 uVar1;
  byte bVar2;
  short sVar3;
  undefined4 uVar4;
  short sVar5;
  undefined2 extraout_D1w;
  ushort uVar6;
  short sVar7;
  ushort *puVar8;
  int unaff_A4;
  
  uVar1 = *(undefined2 *)(unaff_A4 + -0x46a0);
  if ((((*(short *)(unaff_A4 + -0x5f7a) == 1) || (*(short *)(unaff_A4 + -0x5f7a) == 7)) ||
      (*(short *)(unaff_A4 + -0x5f7a) == 0xb)) || (*(short *)(unaff_A4 + -0x5f7a) == 8)) {
LAB_0001045c:
    *(undefined2 *)(unaff_A4 + -0x419e) = *(undefined2 *)(unaff_A4 + -0x5f86);
  }
  else {
    if (*(short *)(unaff_A4 + -0x5c6a) == 1) goto LAB_000106b4;
    if ((*(short *)(unaff_A4 + -0x60ca) != 0) || ((short)*(ushort *)(unaff_A4 + -0x41a2) < 0))
    goto LAB_0001045c;
    puVar8 = (ushort *)
             ((int)(short)((*(ushort *)(unaff_A4 + -0x41a2) >> 3) * 2) +
             *(int *)(unaff_A4 + -0x69d6));
    if ((puVar8 < *(ushort **)(unaff_A4 + -0x69d2)) && ((*puVar8 & 3) == 1)) {
      (**(code **)(unaff_A4 + -0x7dee))(puVar8);
      *(undefined2 *)(unaff_A4 + -0x46a0) = 0xa1;
    }
  }
  *(undefined2 *)(unaff_A4 + -0x46a0) = 0xa1;
  if (*(short *)(unaff_A4 + -0x60c8) == 1) {
    sVar5 = *(short *)(unaff_A4 + -0x4084);
    uVar6 = *(ushort *)(unaff_A4 + -0x4086);
    if (uVar6 == 0) {
      sVar7 = -*(short *)(unaff_A4 + -0x4082) >> 2;
      if (sVar7 < -2) {
        sVar7 = -2;
      }
      if (-1 < sVar5) {
        sVar7 = sVar7 + 6;
      }
      sVar7 = sVar7 + 0x2a;
    }
    else {
      if (8 < uVar6) {
        if (uVar6 < 0x12) {
          if (0xd < uVar6) {
            sVar5 = -sVar5;
          }
          sVar7 = uVar6 + 0x2f;
          if (-1 < sVar5) {
            sVar7 = uVar6 + 0x38;
          }
          goto LAB_000104e2;
        }
        uVar6 = 0x1a - uVar6;
      }
      sVar3 = (short)(uVar6 - 1) >> 2;
      sVar7 = sVar3 + 0x34;
      if (-1 < sVar5) {
        sVar7 = sVar3 + 0x36;
      }
    }
LAB_000104e2:
    uVar4 = *(undefined4 *)(*(int *)(unaff_A4 + -0x4188) + (int)(short)(sVar7 << 2));
  }
  else {
    uVar4 = *(undefined4 *)(unaff_A4 + -0x5f82);
  }
  (**(code **)(unaff_A4 + -0x7ecc))(uVar4);
  if ((((*(short *)(unaff_A4 + -0x4086) == 0) && (*(short *)(unaff_A4 + -0x5c5a) == 2)) &&
      (*(char *)(unaff_A4 + -0x5c91) != '\0')) && (*(short *)(unaff_A4 + -0x60ca) == 0)) {
    (**(code **)(unaff_A4 + -0x7cd4))();
  }
  if (((*(short *)(unaff_A4 + -0x4086) == 0) && (*(short *)(unaff_A4 + -0x60ca) == 0)) &&
     ((*(short *)(unaff_A4 + -0x5f7a) == 0 ||
      ((*(short *)(unaff_A4 + -0x5f7a) == 7 || (*(short *)(unaff_A4 + -0x5562) != 0)))))) {
    sVar5 = *(short *)(unaff_A4 + -0x5cb4);
    if (sVar5 != *(short *)(unaff_A4 + -0x5bf4)) {
      if (sVar5 < *(short *)(unaff_A4 + -0x5bf4)) {
        sVar5 = sVar5 + 2;
      }
      *(short *)(unaff_A4 + -0x5cb4) = sVar5 + -1;
    }
    (**(code **)(unaff_A4 + -0x7cd4))();
  }
  (**(code **)(unaff_A4 + -0x7cd4))();
  if (*(short *)(unaff_A4 + -0x5f7a) == 7) {
    (**(code **)(unaff_A4 + -0x7c86))(extraout_D1w);
  }
  if ((((*(short *)(unaff_A4 + -0x4086) != 0) && (*(short *)(unaff_A4 + -0x5c5a) == 2)) &&
      (*(char *)(unaff_A4 + -0x5c91) != '\0')) && (*(short *)(unaff_A4 + -0x60ca) == 0)) {
    (**(code **)(unaff_A4 + -0x7cd4))();
  }
  uVar4 = (**(code **)(unaff_A4 + -0x7ed8))();
  if (((*(short *)(unaff_A4 + -0x5c94) != 0) && (*(short *)(unaff_A4 + -0x4086) == 0)) &&
     ((*(short *)(unaff_A4 + -0x60c8) != 1 &&
      (bVar2 = *(char *)(unaff_A4 + -0x5c76) + 1, *(byte *)(unaff_A4 + -0x5c76) = bVar2 & 3,
      *(char *)(unaff_A4 + -0x63f6 +
               (int)(short)((ushort)CONCAT31((int3)((uint)uVar4 >> 8),bVar2) & 0xff03)) != '\0'))))
  {
    (**(code **)(unaff_A4 + -0x7cc8))();
  }
LAB_000106b4:
  *(undefined2 *)(unaff_A4 + -0x46a0) = uVar1;
  return;
}


// ==== thunk_FUN_00010820 @ 00022f6e ====

void thunk_FUN_00010820(short param_1,undefined4 param_2)

{
  undefined4 uVar1;
  short sVar2;
  short *psVar3;
  int unaff_A4;
  
  uVar1 = *(undefined4 *)(unaff_A4 + -0x69d6);
  psVar3 = (short *)(unaff_A4 + -0x6350);
  sVar2 = 0xe;
  while (*(char *)(psVar3 + 0x10) != '\0') {
    psVar3 = psVar3 + 0x15;
    sVar2 = sVar2 + -1;
    if (sVar2 == -1) {
      return;
    }
  }
  psVar3[9] = 0;
  psVar3[10] = 0;
  psVar3[7] = 0;
  psVar3[8] = 0;
  *psVar3 = (param_1 - (short)uVar1) * 4;
  psVar3[2] = param_2._0_2_ + 0xc;
  psVar3[0xf] = 0;
  *(undefined1 *)(psVar3 + 0x10) = 8;
  *(undefined1 *)((int)psVar3 + 0x21) = 1;
  psVar3[0x11] = 1;
  *(undefined1 *)((int)psVar3 + 0x1f) = 0;
  if (param_2._2_2_ != 0) {
    return;
  }
  *(undefined1 *)((int)psVar3 + 0x1f) = 2;
                    /* WARNING: Could not recover jumptable at 0x00010888. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(unaff_A4 + -0x7f92))();
  return;
}


// ==== thunk_FUN_00010a72 @ 00022f74 ====

void thunk_FUN_00010a72(void)

{
  short sVar1;
  int extraout_A0;
  int iVar2;
  int unaff_A4;
  
  iVar2 = unaff_A4 + -0x6350;
  sVar1 = 0xe;
  do {
    if (*(char *)(iVar2 + 0x20) != '\0') {
      FUN_00010aa6();
      iVar2 = extraout_A0;
    }
    iVar2 = iVar2 + 0x2a;
    sVar1 = sVar1 + -1;
  } while (sVar1 != -1);
  *(undefined1 *)(unaff_A4 + -0x41c2) = 0;
  if (*(char *)(unaff_A4 + -0x5a4a) != '\0') {
    FUN_00010aa6();
  }
  return;
}


// ==== thunk_FUN_00010da6 @ 00022f7a ====

undefined8 thunk_FUN_00010da6(void)

{
  short sVar1;
  undefined4 in_D0;
  undefined4 in_D1;
  short sVar2;
  int unaff_A4;
  short *psVar3;
  short *psVar4;
  
  sVar2 = *(short *)(unaff_A4 + -0x5e26);
  psVar4 = (short *)(unaff_A4 + -0x5e24);
  while (sVar2 = sVar2 + -1, sVar2 != -1) {
    psVar3 = psVar4 + 1;
    sVar1 = *psVar4;
    if (sVar1 < 0) {
      sVar1 = -sVar1;
    }
    sVar1 = sVar1 - *(short *)(unaff_A4 + -0x60ce);
    if (*(short *)(unaff_A4 + -0x60ca) != 0) {
      sVar1 = sVar1 >> 3;
    }
    psVar4 = psVar3;
    if ((-0x81 < sVar1) && (sVar1 < 0x1c1)) {
      (**(code **)(unaff_A4 + -0x7cd4))();
    }
  }
  sVar2 = 3;
  psVar4 = (short *)(unaff_A4 + -0x5dd4);
  do {
    if (*psVar4 != 0) {
      sVar1 = psVar4[0x10] - *(short *)(unaff_A4 + -0x60ce);
      if (*(short *)(unaff_A4 + -0x60ca) != 0) {
        sVar1 = sVar1 >> 3;
      }
      if ((((-0x81 < sVar1) && (sVar1 < 0x1c1)) &&
          ((**(code **)(unaff_A4 + -0x7cd4))(), psVar4[9] != 0)) &&
         ((*(short *)(unaff_A4 + -0x60ca) == 0 &&
          (psVar4[0x16] = psVar4[0x16] + 1, (psVar4[0x16] & 1U) != 0)))) {
        (**(code **)(unaff_A4 + -0x7cc8))();
      }
    }
    psVar4 = psVar4 + 0x1a;
    sVar2 = sVar2 + -1;
  } while (sVar2 != -1);
  return CONCAT44(in_D0,in_D1);
}


// ==== thunk_FUN_0001107c @ 00022f80 ====

undefined8 thunk_FUN_0001107c(void)

{
  undefined4 in_D0;
  undefined4 in_D1;
  int unaff_A4;
  
  *(undefined1 *)(unaff_A4 + -0x5c92) = 0xff;
  FUN_000107f2();
  *(undefined1 *)(unaff_A4 + -0x41c1) = 0;
  return CONCAT44(in_D0,in_D1);
}


// ==== thunk_FUN_00011092 @ 00022f86 ====

undefined8 thunk_FUN_00011092(void)

{
  uint in_D0;
  uint in_D1;
  uint uVar1;
  int iVar2;
  
  uVar1 = (in_D1 & 0xffff) * (in_D0 & 0xffff);
  iVar2 = (int)(short)in_D1 * (int)(short)(in_D0 >> 0x10);
  if (((short)uVar1 < 0) && (uVar1 = uVar1 + 0x10000, uVar1 == 0)) {
    iVar2 = iVar2 + 1;
  }
  return CONCAT44((uVar1 >> 0x10) + iVar2,in_D1);
}


// ==== thunk_FUN_00011256 @ 00022f8c ====

void thunk_FUN_00011256(void)

{
  int unaff_A4;
  
  (**(code **)(*(int *)(unaff_A4 + -0x408a) + -0xc6))();
  (**(code **)(unaff_A4 + -0x7f56))();
  (**(code **)(unaff_A4 + -0x7f5c))();
  FUN_000124e0();
  return;
}


// ==== thunk_FUN_00011386 @ 00022f92 ====

void thunk_FUN_00011386(void)

{
  short sVar1;
  ushort uVar2;
  short sVar3;
  undefined2 uVar4;
  int unaff_A4;
  
  if (*(char *)(unaff_A4 + -0x5aa8) == '\0') {
    if (*(short *)(unaff_A4 + -0x5f7a) == 0) {
      if ((*(short *)(unaff_A4 + -0x5f74) != 0x80) &&
         (sVar1 = *(short *)(unaff_A4 + -0x3cae), sVar3 = sVar1 + -1,
         *(short *)(unaff_A4 + -0x3cae) = sVar3, sVar3 == 0 || sVar1 < 1)) {
        *(undefined2 *)(unaff_A4 + -0x3cae) = 0x50;
        *(short *)(unaff_A4 + -0x5f74) = *(short *)(unaff_A4 + -0x5f74) + -1;
      }
      sVar1 = *(short *)(unaff_A4 + -0x3cb0);
      sVar3 = sVar1 + -1;
      *(short *)(unaff_A4 + -0x3cb0) = sVar3;
      if (sVar3 == 0 || sVar1 < 1) {
        *(short *)(unaff_A4 + -0x5f78) = *(short *)(unaff_A4 + -0x5f78) + -1;
        *(undefined2 *)(unaff_A4 + -0x3cb0) = *(undefined2 *)(unaff_A4 + -0x3e96);
      }
    }
    *(short *)(unaff_A4 + -0x3cb8) = *(short *)(unaff_A4 + -0x3cb8) + 1;
    *(ushort *)(unaff_A4 + -0x3cb8) = *(ushort *)(unaff_A4 + -0x3cb8) & 1;
    sVar1 = *(short *)(unaff_A4 + -0x5c52) + -1;
    *(short *)(unaff_A4 + -0x5c52) = sVar1;
    if (sVar1 < 0) {
      *(undefined2 *)(unaff_A4 + -0x5c52) = *(undefined2 *)(unaff_A4 + -0x5c16);
      uVar2 = *(short *)(unaff_A4 + -0x6894) + 1U & 7;
      *(ushort *)(unaff_A4 + -0x6894) = uVar2;
      *(ushort *)(unaff_A4 + -0x5c50) = *(byte *)(unaff_A4 + -0x63ba + (int)(short)uVar2) + 1;
    }
    uVar4 = FUN_00011714();
    *(undefined2 *)(unaff_A4 + -0x42bc) = uVar4;
    if ((*(short *)(unaff_A4 + -0x42c0) == 0) ||
       (sVar1 = *(short *)(unaff_A4 + -0x42c0), sVar3 = sVar1 + -1,
       *(short *)(unaff_A4 + -0x42c0) = sVar3, sVar3 == 0 || sVar1 < 1)) {
      FUN_000112b0();
      FUN_00011460();
    }
    (**(code **)(unaff_A4 + -0x7e00))();
    (**(code **)(unaff_A4 + -0x7dd0))();
    FUN_00012132();
    (**(code **)(unaff_A4 + -0x7e18))();
    FUN_00012066();
    FUN_00011274();
    FUN_00011bfc();
    (**(code **)(unaff_A4 + -0x7fda))();
    FUN_000119bc();
    sVar1 = *(short *)(unaff_A4 + -0x3cb6);
    *(short *)(unaff_A4 + -0x3cb6) = sVar1 + -1;
    if (sVar1 < 1) {
      *(undefined2 *)(unaff_A4 + -0x3cb6) = 0;
    }
    FUN_00011622();
    FUN_00011510();
    FUN_00011cae();
    FUN_00011de4();
    FUN_00011c5e();
  }
  return;
}


// ==== thunk_FUN_0001174a @ 00022f98 ====

void thunk_FUN_0001174a(void)

{
  int unaff_A4;
  
  *(undefined2 *)(unaff_A4 + -0x3caa) = 0;
  *(undefined2 *)(unaff_A4 + -0x3ca8) = 0;
  return;
}


// ==== thunk_FUN_00011754 @ 00022f9e ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 thunk_FUN_00011754(void)

{
  ushort uVar1;
  byte bVar2;
  bool bVar3;
  short sVar4;
  ushort uVar5;
  short sVar6;
  ushort extraout_D1w;
  undefined4 in_D1;
  short sVar7;
  undefined2 *extraout_A0;
  ushort *puVar8;
  undefined2 *puVar9;
  undefined2 *puVar10;
  undefined2 *puVar11;
  undefined2 *puVar12;
  int *in_A1;
  
  DAT_0002550e = 0xff;
  if (DAT_000254a6 != '\0') {
    DAT_0002550e = 0xff;
    return in_D1;
  }
  *in_A1 = *in_A1 + 1;
  if (DAT_000272b4 == 0) {
    (*_thunk_FUN_0001c9ca)();
    sVar6 = DAT_000272b2 + -1;
    bVar3 = DAT_000272b2 < 1;
    DAT_000272b2 = sVar6;
    if (sVar6 == 0 || bVar3) {
      DAT_000272b2 = 4;
      if (DAT_00026c9c == 1) {
        if ((DAT_00026ca4 == 0) || (DAT_00026c94 == 0)) goto LAB_00011842;
        DAT_00026c94 = DAT_00026c94 + -1;
        bVar2 = *(byte *)(DAT_00026c9e + (short)DAT_00026ca2);
        uVar5 = (ushort)bVar2;
        if ((bVar2 == 0xff) || (DAT_00026ca2 = DAT_00026ca2 + 1, 0x1385 < DAT_00026ca2)) {
          DAT_00025312 = 0xff;
        }
        DAT_000272b6 = (ushort)bVar2;
      }
      else {
        uVar5 = (*_thunk_FUN_0001ca32)();
      }
      puVar11 = &DAT_000272a6;
      if (DAT_000272a4 < 6) {
        DAT_000272a4 = DAT_000272a4 + 1;
      }
      else {
        uVar5 = FUN_00011714();
        puVar11 = extraout_A0;
        DAT_000272a4 = extraout_D1w;
      }
      *(ushort *)((int)puVar11 + (int)(short)((DAT_000272a4 - 1) * 2)) = DAT_000272b6;
      if (((DAT_00026c9c == 2) && (DAT_00026ca4 != 0)) && (DAT_00026c94 != 0)) {
        DAT_00026c94 = DAT_00026c94 + -1;
        *(undefined1 *)(DAT_00026c9e + (short)DAT_00026ca2) = (undefined1)DAT_000272b6;
        DAT_00026ca2 = DAT_00026ca2 + 1;
        DAT_000272b6 = uVar5;
        if (0x1385 < DAT_00026ca2) {
          DAT_00025312 = 0xff;
        }
      }
    }
  }
LAB_00011842:
  if (DAT_0002459e == '\0') {
    DAT_00025360 = DAT_00025360 + 1;
    if (DAT_00025518 != 0) {
      puVar8 = (ushort *)(DAT_000271f2 + 0x444);
      sVar6 = 0xc;
      DAT_00025518 = DAT_00025518 + -1;
      do {
        uVar5 = puVar8[-1];
        puVar8[-1] = uVar5 << 1;
        uVar1 = puVar8[-2];
        puVar8[-2] = uVar1 << 1 | (ushort)((uVar5 & 0x8000) != 0);
        uVar5 = puVar8[-3];
        puVar8[-3] = uVar5 << 1 | (ushort)((uVar1 & 0x8000) != 0);
        uVar1 = puVar8[-4];
        puVar8[-4] = uVar1 << 1 | (ushort)((uVar5 & 0x8000) != 0);
        uVar5 = puVar8[-5];
        puVar8[-5] = uVar5 << 1 | (ushort)((uVar1 & 0x8000) != 0);
        uVar1 = puVar8[-6];
        puVar8[-6] = uVar1 << 1 | (ushort)((uVar5 & 0x8000) != 0);
        uVar5 = puVar8[-7];
        puVar8[-7] = uVar5 << 1 | (ushort)((uVar1 & 0x8000) != 0);
        uVar1 = puVar8[-8];
        puVar8[-8] = uVar1 << 1 | (ushort)((uVar5 & 0x8000) != 0);
        uVar5 = puVar8[-9];
        puVar8[-9] = uVar5 << 1 | (ushort)((uVar1 & 0x8000) != 0);
        uVar1 = puVar8[-10];
        puVar8[-10] = uVar1 << 1 | (ushort)((uVar5 & 0x8000) != 0);
        uVar5 = puVar8[-0xb];
        puVar8[-0xb] = uVar5 << 1 | (ushort)((uVar1 & 0x8000) != 0);
        uVar1 = puVar8[-0xc];
        puVar8[-0xc] = uVar1 << 1 | (ushort)((uVar5 & 0x8000) != 0);
        uVar5 = puVar8[-0xd];
        puVar8[-0xd] = uVar5 << 1 | (ushort)((uVar1 & 0x8000) != 0);
        uVar1 = puVar8[-0xe];
        puVar8[-0xe] = uVar1 << 1 | (ushort)((uVar5 & 0x8000) != 0);
        uVar5 = puVar8[-0xf];
        puVar8[-0xf] = uVar5 << 1 | (ushort)((uVar1 & 0x8000) != 0);
        uVar1 = puVar8[-0x10];
        puVar8[-0x10] = uVar1 << 1 | (ushort)((uVar5 & 0x8000) != 0);
        uVar5 = puVar8[-0x11];
        puVar8[-0x11] = uVar5 << 1 | (ushort)((uVar1 & 0x8000) != 0);
        uVar1 = puVar8[-0x12];
        puVar8[-0x12] = uVar1 << 1 | (ushort)((uVar5 & 0x8000) != 0);
        uVar5 = puVar8[-0x13];
        puVar8[-0x13] = uVar5 << 1 | (ushort)((uVar1 & 0x8000) != 0);
        uVar1 = puVar8[-0x14];
        puVar8[-0x14] = uVar1 << 1 | (ushort)((uVar5 & 0x8000) != 0);
        uVar5 = puVar8[-0x15];
        puVar8[-0x15] = uVar5 << 1 | (ushort)((uVar1 & 0x8000) != 0);
        uVar1 = puVar8[-0x16];
        puVar8[-0x16] = uVar1 << 1 | (ushort)((uVar5 & 0x8000) != 0);
        uVar5 = puVar8[-0x17];
        puVar8[-0x17] = uVar5 << 1 | (ushort)((uVar1 & 0x8000) != 0);
        uVar1 = puVar8[-0x18];
        puVar8[-0x18] = uVar1 << 1 | (ushort)((uVar5 & 0x8000) != 0);
        uVar5 = puVar8[-0x19];
        puVar8[-0x19] = uVar5 << 1 | (ushort)((uVar1 & 0x8000) != 0);
        uVar1 = puVar8[-0x1a];
        puVar8[-0x1a] = uVar1 << 1 | (ushort)((uVar5 & 0x8000) != 0);
        uVar5 = puVar8[-0x1b];
        puVar8[-0x1b] = uVar5 << 1 | (ushort)((uVar1 & 0x8000) != 0);
        uVar1 = puVar8[-0x1c];
        puVar8[-0x1c] = uVar1 << 1 | (ushort)((uVar5 & 0x8000) != 0);
        uVar5 = puVar8[-0x1d];
        puVar8[-0x1d] = uVar5 << 1 | (ushort)((uVar1 & 0x8000) != 0);
        uVar1 = puVar8[-0x1e];
        puVar8[-0x1e] = uVar1 << 1 | (ushort)((uVar5 & 0x8000) != 0);
        uVar5 = puVar8[-0x1f];
        puVar8[-0x1f] = uVar5 << 1 | (ushort)((uVar1 & 0x8000) != 0);
        uVar1 = puVar8[-0x20];
        puVar8[-0x20] = uVar1 << 1 | (ushort)((uVar5 & 0x8000) != 0);
        uVar5 = puVar8[-0x21];
        puVar8[-0x21] = uVar5 << 1 | (ushort)((uVar1 & 0x8000) != 0);
        uVar1 = puVar8[-0x22];
        puVar8[-0x22] = uVar1 << 1 | (ushort)((uVar5 & 0x8000) != 0);
        uVar5 = puVar8[-0x23];
        puVar8[-0x23] = uVar5 << 1 | (ushort)((uVar1 & 0x8000) != 0);
        uVar1 = puVar8[-0x24];
        puVar8[-0x24] = uVar1 << 1 | (ushort)((uVar5 & 0x8000) != 0);
        uVar5 = puVar8[-0x25];
        puVar8[-0x25] = uVar5 << 1 | (ushort)((uVar1 & 0x8000) != 0);
        uVar1 = puVar8[-0x26];
        puVar8[-0x26] = uVar1 << 1 | (ushort)((uVar5 & 0x8000) != 0);
        uVar5 = puVar8[-0x27];
        puVar8[-0x27] = uVar5 << 1 | (ushort)((uVar1 & 0x8000) != 0);
        uVar1 = puVar8[-0x28];
        puVar8[-0x28] = uVar1 << 1 | (ushort)((uVar5 & 0x8000) != 0);
        uVar5 = puVar8[-0x29];
        puVar8[-0x29] = uVar5 << 1 | (ushort)((uVar1 & 0x8000) != 0);
        puVar8 = puVar8 + -0x2a;
        *puVar8 = *puVar8 << 1 | (ushort)((uVar5 & 0x8000) != 0);
        sVar6 = sVar6 + -1;
      } while (sVar6 != -1);
      if ((DAT_00025530 != 0) && (DAT_00025530 = DAT_00025530 + -1, DAT_00025530 != 0)) {
        return in_D1;
      }
    }
    if (DAT_00025706 != (char *)0x0) {
      if (*DAT_00025706 == '\0') {
        DAT_00025706 = (char *)0x0;
        DAT_00025530 = 0;
      }
      else {
        DAT_00025518 = 0x2a0;
        uVar5 = (ushort)(byte)(*DAT_00025706 - DAT_00026ebe);
        bVar2 = *(byte *)(DAT_00026eba + 4 + (int)(short)uVar5);
        if (bVar2 == 0) {
          DAT_00025530 = 10;
          DAT_00025706 = DAT_00025706 + 1;
        }
        else {
          DAT_00025530 = bVar2 + 1;
          puVar9 = (undefined2 *)
                   (*(short *)((int)&DAT_00026ca6 + (int)(short)(uVar5 * 2)) + DAT_00026d66);
          puVar11 = (undefined2 *)(DAT_000271f2 + 0x50);
          sVar6 = DAT_00026ec0;
          DAT_00025706 = DAT_00025706 + 1;
          while (sVar6 = sVar6 + -1, sVar6 != -1) {
            sVar4 = ((ushort)(bVar2 + 0xf) >> 4) - 1;
            puVar10 = puVar9;
            sVar7 = sVar4;
            do {
              puVar12 = puVar11;
              puVar9 = puVar10 + 1;
              *puVar12 = *puVar10;
              sVar7 = sVar7 + -1;
              puVar10 = puVar9;
              puVar11 = puVar12 + 1;
            } while (sVar7 != -1);
            puVar11 = (undefined2 *)((int)puVar12 + (0x54 - (short)(sVar4 * 2)));
          }
        }
      }
    }
  }
  return in_D1;
}


// ==== thunk_FUN_00011a14 @ 00022fa4 ====

void thunk_FUN_00011a14(void)

{
  undefined2 uVar1;
  undefined1 uVar2;
  short in_D0w;
  short sVar3;
  short *psVar4;
  undefined2 *extraout_A0;
  int extraout_A0_00;
  int extraout_A0_01;
  int unaff_A4;
  
  psVar4 = *(short **)(unaff_A4 + -0x415a);
  if ((*(char *)(psVar4 + 1) == '\0') && (*psVar4 = in_D0w, in_D0w != 0)) {
    uVar2 = (**(code **)(unaff_A4 + -0x7f08))();
    *(undefined1 *)(extraout_A0_01 + 3) = uVar2;
    *(undefined1 *)(extraout_A0_01 + 2) = 4;
    return;
  }
  sVar3 = 0x12;
  do {
    if (*(char *)(psVar4 + 3) == '\0') {
      FUN_00011a46();
      uVar1 = FUN_00011a8c();
      *extraout_A0 = uVar1;
      (**(code **)(unaff_A4 + -0x7ec0))();
      uVar2 = (**(code **)(unaff_A4 + -0x7f08))();
      *(undefined1 *)(extraout_A0_00 + 3) = uVar2;
      return;
    }
    sVar3 = sVar3 + -1;
    psVar4 = psVar4 + 2;
  } while (sVar3 != -1);
  return;
}


// ==== thunk_FUN_00011a84 @ 00022faa ====

undefined8 thunk_FUN_00011a84(undefined4 param_1)

{
  undefined4 in_D0;
  undefined4 in_D1;
  short sVar1;
  short *extraout_A0;
  short *psVar2;
  int unaff_A4;
  ulonglong uVar3;
  
  uVar3 = (ulonglong)CONCAT24(param_1._0_2_ - param_1._2_2_,(uint)(ushort)(param_1._2_2_ * 2));
  psVar2 = *(short **)(unaff_A4 + -0x5afe);
  sVar1 = *(short *)(unaff_A4 + -0x5c3a);
  while (sVar1 = sVar1 + -1, sVar1 != -1) {
    if ((psVar2[3] == 1) && ((ushort)(*psVar2 - (short)(uVar3 >> 0x20)) <= (ushort)uVar3)) {
      psVar2[3] = 2;
      *(undefined1 *)((int)psVar2 + 3) = 5;
      *(undefined1 *)(psVar2 + 2) = 2;
      uVar3 = FUN_000123ac();
      psVar2 = extraout_A0;
    }
    psVar2 = psVar2 + 4;
  }
  FUN_00011ae2();
  return CONCAT44(CONCAT22((short)((uint)in_D0 >> 0x10),param_1._0_2_),
                  CONCAT22((short)((uint)in_D1 >> 0x10),param_1._2_2_));
}


// ==== thunk_FUN_00011f4e @ 00022fb0 ====

void thunk_FUN_00011f4e(void)

{
  short sVar1;
  undefined2 *puVar2;
  int unaff_A4;
  
  puVar2 = (undefined2 *)(unaff_A4 + -0x3c96);
  sVar1 = 7;
  do {
    *puVar2 = 0;
    puVar2 = puVar2 + 0xc;
    sVar1 = sVar1 + -1;
  } while (sVar1 != -1);
  FUN_00012066();
  return;
}


// ==== thunk_FUN_00012324 @ 00022fb6 ====

void thunk_FUN_00012324(void)

{
  undefined2 uVar1;
  int unaff_A4;
  
  if (*(int *)(unaff_A4 + -0x41c0) != 0) {
    *(undefined1 *)(unaff_A4 + -0x3c36) = 0xff;
    *(undefined4 *)(unaff_A4 + -0x3c26) = 0;
    uVar1 = FUN_00012306();
    *(undefined2 *)(unaff_A4 + -0x3c2a) = uVar1;
  }
  return;
}


// ==== thunk_FUN_00012324 @ 00022fbc ====

void thunk_FUN_00012324(void)

{
  undefined2 uVar1;
  int unaff_A4;
  
  if (*(int *)(unaff_A4 + -0x41c0) != 0) {
    *(undefined1 *)(unaff_A4 + -0x3c36) = 0xff;
    *(undefined4 *)(unaff_A4 + -0x3c26) = 0;
    uVar1 = FUN_00012306();
    *(undefined2 *)(unaff_A4 + -0x3c2a) = uVar1;
  }
  return;
}


// ==== thunk_FUN_0001233e @ 00022fc2 ====

void thunk_FUN_0001233e(void)

{
  undefined2 uVar1;
  int unaff_A4;
  
  *(undefined2 *)(unaff_A4 + -0x3c36) = 0;
  *(undefined1 *)(unaff_A4 + -0x3c1e) = 0xff;
  *(undefined4 *)(unaff_A4 + -0x3c26) = 0;
  uVar1 = FUN_00012306();
  *(undefined2 *)(unaff_A4 + -0x3c12) = uVar1;
  return;
}


// ==== thunk_FUN_00012354 @ 00022fc8 ====

void thunk_FUN_00012354(void)

{
  int unaff_A4;
  
  *(undefined4 *)(unaff_A4 + -0x3bec) = *(undefined4 *)(unaff_A4 + -0x41bc);
  *(undefined2 *)(unaff_A4 + -0x3be6) = 0x1646;
  *(undefined2 *)(unaff_A4 + -0x3be4) = 0x1c2;
  *(undefined2 *)(unaff_A4 + -0x3be2) = 0x40;
  *(undefined2 *)(unaff_A4 + -0x3be0) = 1;
  *(undefined2 *)(unaff_A4 + -0x3c06) = 0;
  *(undefined1 *)(unaff_A4 + -0x3bee) = 0xff;
  *(undefined4 *)(unaff_A4 + -0x3bf6) = 0;
  return;
}


// ==== thunk_FUN_00012380 @ 00022fce ====

void thunk_FUN_00012380(void)

{
  int unaff_A4;
  
  *(undefined4 *)(unaff_A4 + -0x3bec) = *(undefined4 *)(unaff_A4 + -0x4156);
  *(undefined2 *)(unaff_A4 + -0x3be6) = 0x1a5a;
  *(undefined2 *)(unaff_A4 + -0x3be4) = 0x15e;
  *(undefined2 *)(unaff_A4 + -0x3be2) = 0x40;
  *(undefined2 *)(unaff_A4 + -0x3be0) = 1;
  *(undefined2 *)(unaff_A4 + -0x3c06) = 0;
  *(undefined1 *)(unaff_A4 + -0x3bee) = 0xff;
  *(undefined4 *)(unaff_A4 + -0x3bf6) = 0;
  return;
}


// ==== thunk_FUN_00012380 @ 00022fd4 ====

void thunk_FUN_00012380(void)

{
  int unaff_A4;
  
  *(undefined4 *)(unaff_A4 + -0x3bec) = *(undefined4 *)(unaff_A4 + -0x4156);
  *(undefined2 *)(unaff_A4 + -0x3be6) = 0x1a5a;
  *(undefined2 *)(unaff_A4 + -0x3be4) = 0x15e;
  *(undefined2 *)(unaff_A4 + -0x3be2) = 0x40;
  *(undefined2 *)(unaff_A4 + -0x3be0) = 1;
  *(undefined2 *)(unaff_A4 + -0x3c06) = 0;
  *(undefined1 *)(unaff_A4 + -0x3bee) = 0xff;
  *(undefined4 *)(unaff_A4 + -0x3bf6) = 0;
  return;
}


// ==== thunk_FUN_00012adc @ 00022fda ====

undefined4 thunk_FUN_00012adc(void)

{
  int iVar1;
  short sVar4;
  int iVar2;
  undefined4 uVar3;
  undefined4 in_D0;
  short sVar5;
  short *psVar6;
  int unaff_A4;
  
  FUN_00013554();
  *(undefined2 *)(unaff_A4 + -0x5c3c) = 0;
  *(undefined1 *)(unaff_A4 + -0x5c8e) = 0;
  *(undefined1 *)(unaff_A4 + -0x5c8d) = 0;
  *(undefined1 *)(unaff_A4 + -0x5c7a) = 0;
  *(undefined1 *)(unaff_A4 + -0x5c7c) = 0;
  *(undefined1 *)(unaff_A4 + -0x5c7b) = 0;
  sVar5 = *(short *)(unaff_A4 + -0x5c40);
  sVar4 = 0;
  psVar6 = (short *)(unaff_A4 + -0x5ab6);
  while (sVar5 = sVar5 + -1, sVar5 != -1) {
    sVar4 = *psVar6 + sVar4;
    psVar6 = psVar6 + 1;
  }
  uVar3 = *(undefined4 *)
           (unaff_A4 + -0x5af2 + (int)(short)((*(short *)(unaff_A4 + -0x5c3e) + sVar4 + -1) * 4));
  *(undefined4 *)(unaff_A4 + -0x69d2) = 0;
  (**(code **)(*(int *)(unaff_A4 + -0x40e0) + -0x1e))(uVar3);
  iVar2 = *(int *)(unaff_A4 + -0x40e0);
  (**(code **)(iVar2 + -0x2a))();
  iVar1 = *(int *)(unaff_A4 + -0x410a);
  (**(code **)(iVar2 + -0x2a))();
  *(short *)(unaff_A4 + -0x5c6c) = (short)*(undefined4 *)(unaff_A4 + -0x410a) * 4 + -8;
  iVar2 = FUN_000158ec();
  *(int *)(unaff_A4 + -0x69d6) = iVar2;
  if (iVar2 != 0) {
    iVar2 = *(int *)(unaff_A4 + -0x40e0);
    (**(code **)(iVar2 + -0x2a))();
    (**(code **)(iVar2 + -0x24))();
    sVar5 = (short)iVar1;
    *(short *)(unaff_A4 + -0x5c38) = sVar5;
    *(short *)(unaff_A4 + -0x69ce) = sVar5 << 2;
    iVar1 = *(int *)(unaff_A4 + -0x69d6) + iVar1;
    *(uint *)(unaff_A4 + -0x69d2) = CONCAT22((short)((uint)iVar1 >> 0x10),(short)iVar1 + -2);
    FUN_00012d5a();
    return in_D0;
  }
  uVar3 = FUN_000124d8();
  return uVar3;
}


// ==== thunk_FUN_00012bbe @ 00022fe0 ====

undefined8 thunk_FUN_00012bbe(void)

{
  undefined4 in_D0;
  undefined4 in_D1;
  int unaff_A4;
  
  FUN_000124e0();
  FUN_000124e0();
  FUN_000124e0();
  FUN_000124e0();
  FUN_000124e0();
  if (*(char *)(unaff_A4 + -0x5b9a) != '\0') {
    *(undefined1 *)(unaff_A4 + -0x5b9a) = 0;
    FUN_000124e0();
    FUN_00012502();
  }
  if (*(char *)(unaff_A4 + -0x5b7c) != '\0') {
    *(undefined1 *)(unaff_A4 + -0x5b7c) = 0;
    FUN_000124e0();
    FUN_00012502();
  }
  if (*(char *)(unaff_A4 + -0x5b5e) != '\0') {
    *(undefined1 *)(unaff_A4 + -0x5b5e) = 0;
    FUN_000124e0();
    FUN_00012502();
  }
  if (*(char *)(unaff_A4 + -0x5b40) != '\0') {
    *(undefined1 *)(unaff_A4 + -0x5b40) = 0;
    FUN_000124e0();
    FUN_00012502();
  }
  *(undefined1 *)(unaff_A4 + -0x5c85) = 0;
  return CONCAT44(in_D0,in_D1);
}


// ==== thunk_FUN_00013252 @ 00022fe6 ====

void thunk_FUN_00013252(void)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 extraout_A0;
  int extraout_A0_00;
  int extraout_A0_01;
  int extraout_A0_02;
  int extraout_A0_03;
  int unaff_A4;
  
  *(undefined2 *)(unaff_A4 + -0x5b0a) = 0;
  if (*(char *)(unaff_A4 + -0x5c87) != '\0') {
    iVar1 = (**(code **)(unaff_A4 + -0x7e8a))();
    *(undefined4 *)(unaff_A4 + -0x40ca) = extraout_A0;
    if (iVar1 == 0) {
      *(undefined1 *)(unaff_A4 + -0x5a3f) = 0xff;
      *(undefined1 *)(unaff_A4 + -0x5c87) = 0;
    }
    *(undefined2 *)(unaff_A4 + -0x5b64) = 0xf8;
    *(int *)(unaff_A4 + -0x40c6) = iVar1;
    FUN_0001350e();
  }
  if (*(char *)(unaff_A4 + -0x5c84) != '\0') {
    uVar2 = (**(code **)(unaff_A4 + -0x7e8a))();
    *(undefined2 *)(unaff_A4 + -0x5b82) = 0xd0;
    *(int *)(unaff_A4 + -0x40ba) = extraout_A0_00;
    if (extraout_A0_00 == 0) {
      FUN_000124d8();
      return;
    }
    *(undefined4 *)(unaff_A4 + -0x40b6) = uVar2;
    FUN_0001350e();
  }
  if (*(char *)(unaff_A4 + -0x5c83) != '\0') {
    uVar2 = (**(code **)(unaff_A4 + -0x7e8a))();
    *(undefined2 *)(unaff_A4 + -0x5b46) = 0xb8;
    *(int *)(unaff_A4 + -0x40b2) = extraout_A0_01;
    if (extraout_A0_01 == 0) {
      FUN_000124d8();
      return;
    }
    *(undefined4 *)(unaff_A4 + -0x40ae) = uVar2;
    FUN_0001350e();
    iVar1 = *(int *)(extraout_A0_02 + 6);
    *(undefined2 *)(iVar1 + 0x14) = 5;
    *(undefined2 *)(iVar1 + 0x22) = 5;
  }
  if (*(char *)(unaff_A4 + -0x5c86) != '\0') {
    uVar2 = (**(code **)(unaff_A4 + -0x7e8a))();
    *(int *)(unaff_A4 + -0x40c2) = extraout_A0_03;
    if (extraout_A0_03 == 0) {
      FUN_000124d8();
      return;
    }
    *(undefined2 *)(unaff_A4 + -0x5b28) = 0;
    *(undefined4 *)(unaff_A4 + -0x40be) = uVar2;
    FUN_0001350e();
  }
  return;
}


// ==== thunk_FUN_00013368 @ 00022fec ====

void thunk_FUN_00013368(void)

{
  undefined4 uVar1;
  int unaff_A4;
  
  if (*(int *)(unaff_A4 + -0x41a6) == 0) {
    uVar1 = FUN_00015b1a();
    *(undefined4 *)(unaff_A4 + -0x5a84) = uVar1;
    uVar1 = FUN_00015d50();
    *(undefined4 *)(unaff_A4 + -0x41a6) = uVar1;
  }
  if (*(int *)(unaff_A4 + -0x414a) == 0) {
    uVar1 = FUN_00015b1a();
    *(undefined4 *)(unaff_A4 + -0x5a80) = uVar1;
    uVar1 = FUN_00015d50();
    *(undefined4 *)(unaff_A4 + -0x414a) = uVar1;
  }
  if (*(int *)(unaff_A4 + -0x4156) == 0) {
    uVar1 = FUN_00015b1a();
    *(undefined4 *)(unaff_A4 + -0x5a74) = uVar1;
    uVar1 = FUN_00015d50();
    *(undefined4 *)(unaff_A4 + -0x4156) = uVar1;
  }
  if (*(int *)(unaff_A4 + -0x4152) == 0) {
    uVar1 = FUN_00015b1a();
    *(undefined4 *)(unaff_A4 + -0x5a7c) = uVar1;
    uVar1 = FUN_00015d50();
    *(undefined4 *)(unaff_A4 + -0x4152) = uVar1;
  }
  if (*(int *)(unaff_A4 + -0x41bc) == 0) {
    uVar1 = FUN_00015b1a();
    *(undefined4 *)(unaff_A4 + -0x5a78) = uVar1;
    uVar1 = FUN_00015d50();
    *(undefined4 *)(unaff_A4 + -0x41bc) = uVar1;
  }
  if (*(int *)(unaff_A4 + -0x41c0) == 0) {
    uVar1 = FUN_00015b1a();
    *(undefined4 *)(unaff_A4 + -0x5a88) = uVar1;
    uVar1 = FUN_00015d50();
    *(undefined4 *)(unaff_A4 + -0x41c0) = uVar1;
  }
  if (*(int *)(unaff_A4 + -0x4184) == 0) {
    uVar1 = FUN_00015b1a();
    *(undefined4 *)(unaff_A4 + -0x5a70) = uVar1;
    uVar1 = FUN_00015d50();
    *(undefined4 *)(unaff_A4 + -0x4184) = uVar1;
  }
  if (*(int *)(unaff_A4 + -0x4168) == 0) {
    uVar1 = FUN_00015b1a();
    *(undefined4 *)(unaff_A4 + -0x5a8c) = uVar1;
    uVar1 = FUN_00015d50();
    *(undefined4 *)(unaff_A4 + -0x4168) = uVar1;
  }
  FUN_00011f76();
  return;
}


// ==== thunk_FUN_0001346c @ 00022ff2 ====

void thunk_FUN_0001346c(void)

{
  FUN_000124e0();
  FUN_000124e0();
  FUN_000124e0();
  FUN_000124e0();
  FUN_000124e0();
  FUN_000124e0();
  FUN_000124e0();
  FUN_000124e0();
  return;
}


// ==== thunk_FUN_000134ae @ 00022ff8 ====

void thunk_FUN_000134ae(void)

{
  FUN_00012502();
  return;
}


// ==== thunk_FUN_000135ce @ 00022ffe ====

undefined8 thunk_FUN_000135ce(void)

{
  short sVar1;
  undefined4 in_D0;
  undefined4 in_D1;
  int iVar2;
  int unaff_A4;
  
  *(undefined2 *)(unaff_A4 + -0x3bac) = 0x14;
  *(char *)(unaff_A4 + -0x5ca2) = *(char *)(unaff_A4 + -0x5ca2) + -1;
  *(undefined2 *)(unaff_A4 + -0x5f84) = *(undefined2 *)(unaff_A4 + -0x5c6c);
  *(undefined2 *)(unaff_A4 + -0x5bf0) = 0;
  *(undefined2 *)(unaff_A4 + -0x5f72) = 0xffff;
  iVar2 = *(int *)(unaff_A4 + -0x40a6);
  sVar1 = 0x27;
  do {
    *(undefined2 *)(iVar2 + 0x10) = 0;
    iVar2 = iVar2 + 0x14;
    sVar1 = sVar1 + -1;
  } while (sVar1 != -1);
  if ((*(char *)(unaff_A4 + -0x5ca2) < '\x01') || (*(short *)(unaff_A4 + -0x5b1a) < 1)) {
    *(undefined1 *)(unaff_A4 + -0x5c9c) = 0xff;
    *(undefined1 *)(unaff_A4 + -0x5c3c) = 0xff;
    *(undefined1 *)(unaff_A4 + -0x5ca2) = 0;
  }
  else {
    *(undefined1 *)(unaff_A4 + -0x5c9f) = 3;
    *(undefined1 *)(unaff_A4 + -0x5c9e) = 0;
    FUN_00013684();
    if (*(short *)(unaff_A4 + -0x3bac) != 0) {
      (**(code **)(unaff_A4 + -0x7ed8))();
      (**(code **)(unaff_A4 + -0x7ca4))();
      (**(code **)(unaff_A4 + -0x7c92))();
      (**(code **)(unaff_A4 + -0x7cbc))();
      (**(code **)(unaff_A4 + -0x7c8c))();
      FUN_0001030c();
      do {
        (**(code **)(unaff_A4 + -0x7bae))();
        sVar1 = *(short *)(unaff_A4 + -0x3bac) + -1;
        *(short *)(unaff_A4 + -0x3bac) = sVar1;
      } while (sVar1 != 0);
      do {
        (**(code **)(unaff_A4 + -0x7bae))();
      } while (*(short *)(unaff_A4 + -0x3bac) != 0);
    }
  }
  *(undefined2 *)(unaff_A4 + -0x3bac) = 0;
  return CONCAT44(in_D0,in_D1);
}


// ==== thunk_FUN_00013756 @ 00023004 ====

void thunk_FUN_00013756(void)

{
  short sVar1;
  int iVar2;
  int unaff_A4;
  
  iVar2 = unaff_A4 + -0x6350;
  sVar1 = 0xe;
  do {
    *(undefined1 *)(iVar2 + 0x20) = 0;
    iVar2 = iVar2 + 0x2a;
    sVar1 = sVar1 + -1;
  } while (sVar1 != -1);
  *(undefined1 *)(unaff_A4 + -0x5a4a) = 0;
  return;
}


// ==== thunk_FUN_00013772 @ 0002300a ====

void thunk_FUN_00013772(void)

{
  ushort uVar1;
  short sVar2;
  int iVar3;
  int unaff_A4;
  ushort *puVar4;
  
  *(undefined1 *)(unaff_A4 + -0x3ba6) = 0;
  *(undefined2 *)(unaff_A4 + -0x3baa) = 0;
  *(undefined2 *)(unaff_A4 + -0x3ba8) = 10000;
  (**(code **)(unaff_A4 + -0x7c92))();
  (**(code **)(unaff_A4 + -0x7cbc))();
  sVar2 = *(short *)(unaff_A4 + -0x5c36) + 1;
  if (sVar2 == 100) {
    sVar2 = 0;
  }
  *(short *)(unaff_A4 + -0x5c36) = sVar2;
  uVar1 = *(ushort *)(unaff_A4 + -0x41a2);
  if (*(short *)(unaff_A4 + -0x60c8) == 1) {
    uVar1 = uVar1 & 0xfff8;
  }
  sVar2 = 0x120;
  if (*(short *)(unaff_A4 + -0x60c8) != 8) {
    sVar2 = 0x900;
  }
  puVar4 = (ushort *)
           ((int)(short)((short)(uVar1 - sVar2) >> 2 & 0xfffe) + *(int *)(unaff_A4 + -0x69d6));
  sVar2 = -0x78 - (uVar1 & 7);
  *(short *)(unaff_A4 + -0x5c18) = (*(short *)(unaff_A4 + -0x419e) >> 4) + 0x18;
  if (*(short *)(unaff_A4 + -0x60c8) == 1) {
    iVar3 = *(int *)(unaff_A4 + -0x407c);
  }
  else {
    iVar3 = *(int *)(unaff_A4 + -0x40aa);
  }
  do {
    if (*(ushort **)(unaff_A4 + -0x69d6) <= puVar4) goto LAB_00013842;
    puVar4 = puVar4 + 1;
    sVar2 = *(short *)(unaff_A4 + -0x60c8) + sVar2;
  } while (sVar2 < 0x1d0);
  goto LAB_000138ba;
  while( true ) {
    uVar1 = *puVar4 >> 2;
    if (((uVar1 & 0x2000) != 0) && (*(int *)(iVar3 + (short)((uVar1 & 0x1ff) << 2)) != 0)) {
      if ((*puVar4 & 3) == 1) {
        FUN_00014eac();
      }
      (**(code **)(unaff_A4 + -0x7cd4))();
    }
    FUN_00013b1c();
    sVar2 = *(short *)(unaff_A4 + -0x60c8) + sVar2;
    puVar4 = puVar4 + 1;
    if (0x1cf < sVar2) break;
LAB_00013842:
    if (*(ushort **)(unaff_A4 + -0x69d2) < puVar4 + 1) break;
  }
LAB_000138ba:
  FUN_00013abc();
  FUN_0001409c();
  (**(code **)(unaff_A4 + -0x7fe6))();
  (**(code **)(unaff_A4 + -0x7fd4))();
  FUN_00013d78();
  FUN_00013de8();
  FUN_00014c3e();
  FUN_00013a18();
  FUN_0001391e();
  FUN_00013e6c();
  FUN_000140e8();
  (**(code **)(unaff_A4 + -0x7c8c))();
  if (*(short *)(unaff_A4 + -0x3baa) == 0) {
    *(undefined2 *)(unaff_A4 + -0x3e9a) = 0;
  }
  else {
    uVar1 = *(ushort *)(unaff_A4 + -0x3ba8) >> 3;
    if (0x40 < uVar1) {
      uVar1 = 0x40;
    }
    *(ushort *)(unaff_A4 + -0x3e98) = 0x40 - uVar1;
    *(undefined1 *)(unaff_A4 + -0x3e9a) = 0xff;
  }
  *(undefined1 *)(unaff_A4 + -0x3ba6) = 0;
  return;
}


// ==== thunk_FUN_00013eee @ 00023010 ====

void thunk_FUN_00013eee(void)

{
  short *psVar1;
  byte bVar2;
  byte bVar3;
  short sVar4;
  ushort uVar5;
  short sVar6;
  char cVar7;
  short extraout_D1w;
  short sVar8;
  uint uVar9;
  int extraout_A0;
  short *psVar10;
  int unaff_A4;
  
  (**(code **)(unaff_A4 + -0x7c92))();
  sVar8 = *(short *)(unaff_A4 + -0x5c3a);
  psVar10 = *(short **)(unaff_A4 + -0x5afe);
  do {
    sVar8 = sVar8 + -1;
    if (sVar8 == -1) {
LAB_00014092:
      (**(code **)(unaff_A4 + -0x7c8c))();
      return;
    }
    if (psVar10[3] != 0) {
      if (psVar10[3] != 3) {
        if (psVar10[3] == 2) {
          bVar2 = *(byte *)(psVar10 + 2) - 1;
          *(byte *)(psVar10 + 2) = bVar2;
          if ((short)((ushort)bVar2 << 8) < 0) {
            *(undefined1 *)(psVar10 + 2) = 2;
            *(char *)((int)psVar10 + 3) = *(char *)((int)psVar10 + 3) + '\x01';
            if (7 < *(byte *)((int)psVar10 + 3)) {
              psVar10[3] = 3;
              *(int *)(unaff_A4 + -0x5cb2) = *(int *)(unaff_A4 + -0x5cb2) + 0x19;
              *(short *)(unaff_A4 + -0x42c2) = *(short *)(unaff_A4 + -0x42c2) + 1;
              sVar4 = (ushort)*(byte *)((int)psVar10 + 5) * 4;
              psVar1 = (short *)(unaff_A4 + -0x5bae + (int)sVar4);
              sVar6 = *psVar1 + -1;
              *psVar1 = sVar6;
              if ((sVar6 == 0) && (*(short *)(unaff_A4 + -0x5bac + (int)sVar4) == 0)) {
                uVar5 = FUN_00015ae8();
                uVar9 = (uint)uVar5;
                *(int *)(unaff_A4 + -0x5cb2) = uVar9 + *(int *)(unaff_A4 + -0x5cb2);
                bVar2 = *(byte *)(unaff_A4 + -0x5c7b);
                bVar3 = bVar2 - 1;
                *(byte *)(unaff_A4 + -0x5c7b) = bVar3;
                if ((bVar3 == 0 || SBORROW1(bVar2,'\x01') != (short)((ushort)bVar3 << 8) < 0) &&
                   (*(char *)(unaff_A4 + -0x5c8d) == '\0')) {
                  (**(code **)(unaff_A4 + -0x7f1a))();
                  (**(code **)(unaff_A4 + -0x7e90))(uVar9);
                  goto LAB_00014092;
                }
                (**(code **)(unaff_A4 + -0x7e96))(uVar9);
              }
            }
          }
        }
        else {
          *(char *)((int)psVar10 + 3) = *(char *)((int)psVar10 + 3) + '\x01';
          if (4 < *(byte *)((int)psVar10 + 3)) {
            *(undefined1 *)((int)psVar10 + 3) = 0;
          }
          sVar6 = 3;
          if (*(char *)(psVar10 + 1) < '\0') {
            sVar6 = -3;
          }
          cVar7 = (**(code **)(unaff_A4 + -0x7f08))();
          if (cVar7 == '\0') {
            sVar6 = -sVar6;
            *(char *)(psVar10 + 1) = -*(char *)(psVar10 + 1);
          }
          *psVar10 = sVar6 + *psVar10;
        }
      }
      if (((((*(short *)(unaff_A4 + -0x60c8) == 8) || (psVar10[3] != 3)) &&
           ((**(code **)(unaff_A4 + -0x7eea))(), psVar10[3] == 1)) &&
          (((**(code **)(unaff_A4 + -0x7f08))(), extraout_D1w == 3 && (-1 < *psVar10)))) &&
         (cVar7 = FUN_00014b54(), -1 < cVar7)) {
        if ((*(short *)(extraout_A0 + 0xc) == 0) && (*(char *)(extraout_A0 + 8) == '\0')) {
          *(undefined2 *)(extraout_A0 + 0xc) = 0x168;
        }
        *(char *)(extraout_A0 + 8) = *(char *)(extraout_A0 + 8) + '\x01';
        psVar10[3] = 0;
      }
    }
    psVar10 = psVar10 + 4;
  } while( true );
}


// ==== thunk_FUN_0001417e @ 00023016 ====

undefined8 thunk_FUN_0001417e(void)

{
  undefined4 in_D0;
  undefined4 in_D1;
  int unaff_A4;
  
  (**(code **)(unaff_A4 + -0x7c92))();
  (**(code **)(unaff_A4 + -0x7ed2))();
  *(undefined2 *)(unaff_A4 + -0x5c1c) = *(undefined2 *)(unaff_A4 + -0x5c18);
  FUN_00014564();
  if (*(short *)(unaff_A4 + -0x60c8) != 1) {
    FUN_00014206();
    FUN_000141b4();
  }
  (**(code **)(unaff_A4 + -0x7c8c))();
  return CONCAT44(in_D0,in_D1);
}


// ==== thunk_FUN_000146c6 @ 0002301c ====

undefined8 thunk_FUN_000146c6(int param_1)

{
  short *psVar1;
  byte bVar2;
  byte bVar3;
  short sVar4;
  ushort uVar6;
  char cVar8;
  int iVar5;
  ushort uVar7;
  ushort extraout_D1w;
  short sVar9;
  undefined4 in_D1;
  ushort uVar10;
  uint uVar11;
  int extraout_A0;
  short extraout_A0w;
  int extraout_A0_00;
  short *extraout_A0_01;
  short extraout_A0w_00;
  int extraout_A0_02;
  short extraout_A1w;
  short extraout_A1w_00;
  short unaff_A2w;
  short unaff_A3w;
  int unaff_A4;
  
  param_1 = param_1 - *(int *)(unaff_A4 + -0x69d6);
  uVar6 = (short)param_1 << 2;
  *(ushort *)(unaff_A4 + -0x38fe) = uVar6;
  *(undefined2 *)(unaff_A4 + -0x38dc) = 0;
  uVar7 = *(ushort *)(unaff_A4 + -0x38fe);
  cVar8 = (**(code **)(unaff_A4 + -0x7f08))();
  if ((cVar8 == '\0') || (uVar10 = extraout_D1w & 0x1fff, cVar8 == '\x01')) {
    iVar5 = FUN_00014a4e();
    if ((-1 < iVar5) && (*(short *)(unaff_A4 + -0x38dc) != 1)) {
      if (*(short *)(unaff_A4 + -0x38dc) == 2) {
        *(undefined2 *)(unaff_A4 + -0x5be8) = 5;
        *(undefined2 *)(unaff_A4 + -0x5be6) = 0xfff;
        if (*(char *)(unaff_A4 + -0x38e0) == '\n') {
          *(undefined2 *)(unaff_A4 + -0x5be6) = 0xf00;
          if ((0 < *(short *)(extraout_A0_02 + 0xc)) &&
             (sVar9 = *(short *)(extraout_A0_02 + 0xc) + -1,
             *(short *)(extraout_A0_02 + 0xc) = sVar9, sVar9 == 0)) {
            *(undefined2 *)(extraout_A0_02 + 0x18) = 0x14;
          }
          goto LAB_00014a48;
        }
      }
      *(undefined2 *)(unaff_A4 + -0x5be8) = 5;
      *(undefined2 *)(unaff_A4 + -0x5be6) = 0xfff;
      iVar5 = *(int *)(extraout_A0_02 + 6);
      if (iVar5 != 0) {
        sVar9 = *(short *)(extraout_A0_02 + 10);
        while (sVar9 = sVar9 + -1, sVar9 != -1) {
          if (*(short *)(iVar5 + 8) == 0) {
            uVar10 = uVar7 - *(short *)(iVar5 + 4);
            if ((int)((uint)uVar10 << 0x10) < 0) {
              uVar10 = -uVar10;
            }
            if ((short)uVar10 < 0x10) {
              *(undefined2 *)(iVar5 + 8) = 0xffff;
              *(undefined2 *)(iVar5 + 10) = 0x32;
              *(undefined2 *)(iVar5 + 0xc) = 1;
              *(int *)(unaff_A4 + -0x5cb2) = *(int *)(unaff_A4 + -0x5cb2) + 200;
              *(undefined2 *)(unaff_A4 + -0x5be6) = 0xf00;
              break;
            }
          }
          iVar5 = iVar5 + 0xe;
        }
      }
    }
  }
  else {
    if (*(short *)(unaff_A4 + -0x38dc) == 0) {
      *(undefined2 *)(unaff_A4 + -0x5be8) = 5;
      *(undefined2 *)(unaff_A4 + -0x5be6) = 0xfff;
    }
    if (uVar10 != 0x113) {
      if (uVar10 == 3) {
        cVar8 = FUN_00014b54();
        if (-1 < cVar8) {
          if (*(short *)(unaff_A4 + -0x38dc) == 0) {
            *(undefined2 *)(unaff_A4 + -0x5be6) = 0xf00;
          }
          if (*(char *)(extraout_A0 + 8) != '\0') {
            *(undefined2 *)(extraout_A0 + 0xe) = 200;
            *(int *)(unaff_A4 + -0x5cb2) = *(int *)(unaff_A4 + -0x5cb2) + 200;
            FUN_00014b40();
          }
        }
      }
      else if (uVar10 == 4) {
        FUN_00014ae4();
        iVar5 = *(int *)(unaff_A4 + -0x69d6);
        uVar7 = *(ushort *)(iVar5 + extraout_A0w);
        *(undefined2 *)(iVar5 + extraout_A0w) = 0x16;
        *(ushort *)(iVar5 + extraout_A0w) = uVar7 & 0x8000 | *(ushort *)(iVar5 + extraout_A0w);
        uVar7 = *(ushort *)(iVar5 + extraout_A1w);
        *(undefined2 *)(iVar5 + extraout_A1w) = 0x16;
        *(ushort *)(iVar5 + extraout_A1w) = uVar7 & 0x8000 | *(ushort *)(iVar5 + extraout_A1w);
        uVar7 = *(ushort *)(iVar5 + unaff_A2w);
        *(undefined2 *)(iVar5 + unaff_A2w) = 0x16;
        *(ushort *)(iVar5 + unaff_A2w) = uVar7 & 0x8000 | *(ushort *)(iVar5 + unaff_A2w);
        uVar7 = *(ushort *)(iVar5 + unaff_A3w);
        *(undefined2 *)(iVar5 + unaff_A3w) = 0x16;
        *(ushort *)(iVar5 + unaff_A3w) = uVar7 & 0x8000 | *(ushort *)(iVar5 + unaff_A3w);
        iVar5 = FUN_00014b54();
        if (-1 < iVar5) {
          if (*(short *)(unaff_A4 + -0x38dc) == 0) {
            *(undefined2 *)(unaff_A4 + -0x5be6) = 0xf00;
          }
          *(undefined2 *)(extraout_A0_00 + 0xc) = 0x32;
          *(undefined2 *)(extraout_A0_00 + 0xe) = 1;
          *(int *)(unaff_A4 + -0x5cb2) = *(int *)(unaff_A4 + -0x5cb2) + 0x96;
          FUN_00014b40();
        }
      }
      else if ((((0xe < uVar10) && (uVar10 < 0x1e)) && (*(short *)(unaff_A4 + -0x38dc) == 0)) &&
              (cVar8 = FUN_00014b54(), -1 < cVar8)) {
        *(undefined2 *)(unaff_A4 + -0x5be6) = 0xf00;
        sVar9 = *extraout_A0_01;
        FUN_00014ae4();
        sVar9 = (1 << (4U - (((short)((uVar7 >> 2) - sVar9) >> 1) + 3) & 0x3f) | uVar10 - 0xf) + 0xf
        ;
        iVar5 = *(int *)(unaff_A4 + -0x69d6);
        *(ushort *)(iVar5 + extraout_A0w_00) =
             *(ushort *)(iVar5 + extraout_A0w_00) & 0x8000 | sVar9 * 4 | 2U;
        *(ushort *)(iVar5 + extraout_A1w_00) =
             *(ushort *)(iVar5 + extraout_A1w_00) & 0x8000 | sVar9 * 4 | 2U;
        *(ushort *)(iVar5 + unaff_A2w) = *(ushort *)(iVar5 + unaff_A2w) & 0x8000 | sVar9 * 4 | 2U;
        *(ushort *)(iVar5 + unaff_A3w) = *(ushort *)(iVar5 + unaff_A3w) & 0x8000 | sVar9 * 4 | 2U;
        if (-1 < extraout_A0_01[4]) {
          sVar9 = extraout_A0_01[3];
          extraout_A0_01[4] = -1;
          extraout_A0_01[5] = 0x32;
          extraout_A0_01[6] = 1;
          *(int *)(unaff_A4 + -0x5cb2) = *(int *)(unaff_A4 + -0x5cb2) + 200;
          psVar1 = (short *)(unaff_A4 + -0x5bac + (int)(short)(sVar9 * 4));
          sVar4 = *psVar1 + -1;
          *psVar1 = sVar4;
          if ((sVar4 == 0) && (*(short *)(unaff_A4 + -0x5bae + (int)(short)(sVar9 * 4)) == 0)) {
            uVar7 = FUN_00015ae8();
            uVar11 = (uint)uVar7;
            *(int *)(unaff_A4 + -0x5cb2) = uVar11 + *(int *)(unaff_A4 + -0x5cb2);
            bVar2 = *(byte *)(unaff_A4 + -0x5c7b);
            bVar3 = bVar2 - 1;
            *(byte *)(unaff_A4 + -0x5c7b) = bVar3;
            if ((bVar3 == 0 || SBORROW1(bVar2,'\x01') != (int)((uint)bVar3 << 0x18) < 0) &&
               (*(char *)(unaff_A4 + -0x5c8d) == '\0')) {
              (**(code **)(unaff_A4 + -0x7f1a))();
              (**(code **)(unaff_A4 + -0x7e90))(uVar11);
            }
            else {
              (**(code **)(unaff_A4 + -0x7e96))(uVar11);
            }
          }
        }
      }
    }
  }
LAB_00014a48:
  return CONCAT44(CONCAT22((short)((uint)param_1 >> 0x10),uVar6),in_D1);
}


// ==== thunk_FUN_000146c6 @ 00023022 ====

undefined8 thunk_FUN_000146c6(int param_1)

{
  short *psVar1;
  byte bVar2;
  byte bVar3;
  short sVar4;
  ushort uVar6;
  char cVar8;
  int iVar5;
  ushort uVar7;
  ushort extraout_D1w;
  short sVar9;
  undefined4 in_D1;
  ushort uVar10;
  uint uVar11;
  int extraout_A0;
  short extraout_A0w;
  int extraout_A0_00;
  short *extraout_A0_01;
  short extraout_A0w_00;
  int extraout_A0_02;
  short extraout_A1w;
  short extraout_A1w_00;
  short unaff_A2w;
  short unaff_A3w;
  int unaff_A4;
  
  param_1 = param_1 - *(int *)(unaff_A4 + -0x69d6);
  uVar6 = (short)param_1 << 2;
  *(ushort *)(unaff_A4 + -0x38fe) = uVar6;
  *(undefined2 *)(unaff_A4 + -0x38dc) = 0;
  uVar7 = *(ushort *)(unaff_A4 + -0x38fe);
  cVar8 = (**(code **)(unaff_A4 + -0x7f08))();
  if ((cVar8 == '\0') || (uVar10 = extraout_D1w & 0x1fff, cVar8 == '\x01')) {
    iVar5 = FUN_00014a4e();
    if ((-1 < iVar5) && (*(short *)(unaff_A4 + -0x38dc) != 1)) {
      if (*(short *)(unaff_A4 + -0x38dc) == 2) {
        *(undefined2 *)(unaff_A4 + -0x5be8) = 5;
        *(undefined2 *)(unaff_A4 + -0x5be6) = 0xfff;
        if (*(char *)(unaff_A4 + -0x38e0) == '\n') {
          *(undefined2 *)(unaff_A4 + -0x5be6) = 0xf00;
          if ((0 < *(short *)(extraout_A0_02 + 0xc)) &&
             (sVar9 = *(short *)(extraout_A0_02 + 0xc) + -1,
             *(short *)(extraout_A0_02 + 0xc) = sVar9, sVar9 == 0)) {
            *(undefined2 *)(extraout_A0_02 + 0x18) = 0x14;
          }
          goto LAB_00014a48;
        }
      }
      *(undefined2 *)(unaff_A4 + -0x5be8) = 5;
      *(undefined2 *)(unaff_A4 + -0x5be6) = 0xfff;
      iVar5 = *(int *)(extraout_A0_02 + 6);
      if (iVar5 != 0) {
        sVar9 = *(short *)(extraout_A0_02 + 10);
        while (sVar9 = sVar9 + -1, sVar9 != -1) {
          if (*(short *)(iVar5 + 8) == 0) {
            uVar10 = uVar7 - *(short *)(iVar5 + 4);
            if ((int)((uint)uVar10 << 0x10) < 0) {
              uVar10 = -uVar10;
            }
            if ((short)uVar10 < 0x10) {
              *(undefined2 *)(iVar5 + 8) = 0xffff;
              *(undefined2 *)(iVar5 + 10) = 0x32;
              *(undefined2 *)(iVar5 + 0xc) = 1;
              *(int *)(unaff_A4 + -0x5cb2) = *(int *)(unaff_A4 + -0x5cb2) + 200;
              *(undefined2 *)(unaff_A4 + -0x5be6) = 0xf00;
              break;
            }
          }
          iVar5 = iVar5 + 0xe;
        }
      }
    }
  }
  else {
    if (*(short *)(unaff_A4 + -0x38dc) == 0) {
      *(undefined2 *)(unaff_A4 + -0x5be8) = 5;
      *(undefined2 *)(unaff_A4 + -0x5be6) = 0xfff;
    }
    if (uVar10 != 0x113) {
      if (uVar10 == 3) {
        cVar8 = FUN_00014b54();
        if (-1 < cVar8) {
          if (*(short *)(unaff_A4 + -0x38dc) == 0) {
            *(undefined2 *)(unaff_A4 + -0x5be6) = 0xf00;
          }
          if (*(char *)(extraout_A0 + 8) != '\0') {
            *(undefined2 *)(extraout_A0 + 0xe) = 200;
            *(int *)(unaff_A4 + -0x5cb2) = *(int *)(unaff_A4 + -0x5cb2) + 200;
            FUN_00014b40();
          }
        }
      }
      else if (uVar10 == 4) {
        FUN_00014ae4();
        iVar5 = *(int *)(unaff_A4 + -0x69d6);
        uVar7 = *(ushort *)(iVar5 + extraout_A0w);
        *(undefined2 *)(iVar5 + extraout_A0w) = 0x16;
        *(ushort *)(iVar5 + extraout_A0w) = uVar7 & 0x8000 | *(ushort *)(iVar5 + extraout_A0w);
        uVar7 = *(ushort *)(iVar5 + extraout_A1w);
        *(undefined2 *)(iVar5 + extraout_A1w) = 0x16;
        *(ushort *)(iVar5 + extraout_A1w) = uVar7 & 0x8000 | *(ushort *)(iVar5 + extraout_A1w);
        uVar7 = *(ushort *)(iVar5 + unaff_A2w);
        *(undefined2 *)(iVar5 + unaff_A2w) = 0x16;
        *(ushort *)(iVar5 + unaff_A2w) = uVar7 & 0x8000 | *(ushort *)(iVar5 + unaff_A2w);
        uVar7 = *(ushort *)(iVar5 + unaff_A3w);
        *(undefined2 *)(iVar5 + unaff_A3w) = 0x16;
        *(ushort *)(iVar5 + unaff_A3w) = uVar7 & 0x8000 | *(ushort *)(iVar5 + unaff_A3w);
        iVar5 = FUN_00014b54();
        if (-1 < iVar5) {
          if (*(short *)(unaff_A4 + -0x38dc) == 0) {
            *(undefined2 *)(unaff_A4 + -0x5be6) = 0xf00;
          }
          *(undefined2 *)(extraout_A0_00 + 0xc) = 0x32;
          *(undefined2 *)(extraout_A0_00 + 0xe) = 1;
          *(int *)(unaff_A4 + -0x5cb2) = *(int *)(unaff_A4 + -0x5cb2) + 0x96;
          FUN_00014b40();
        }
      }
      else if ((((0xe < uVar10) && (uVar10 < 0x1e)) && (*(short *)(unaff_A4 + -0x38dc) == 0)) &&
              (cVar8 = FUN_00014b54(), -1 < cVar8)) {
        *(undefined2 *)(unaff_A4 + -0x5be6) = 0xf00;
        sVar9 = *extraout_A0_01;
        FUN_00014ae4();
        sVar9 = (1 << (4U - (((short)((uVar7 >> 2) - sVar9) >> 1) + 3) & 0x3f) | uVar10 - 0xf) + 0xf
        ;
        iVar5 = *(int *)(unaff_A4 + -0x69d6);
        *(ushort *)(iVar5 + extraout_A0w_00) =
             *(ushort *)(iVar5 + extraout_A0w_00) & 0x8000 | sVar9 * 4 | 2U;
        *(ushort *)(iVar5 + extraout_A1w_00) =
             *(ushort *)(iVar5 + extraout_A1w_00) & 0x8000 | sVar9 * 4 | 2U;
        *(ushort *)(iVar5 + unaff_A2w) = *(ushort *)(iVar5 + unaff_A2w) & 0x8000 | sVar9 * 4 | 2U;
        *(ushort *)(iVar5 + unaff_A3w) = *(ushort *)(iVar5 + unaff_A3w) & 0x8000 | sVar9 * 4 | 2U;
        if (-1 < extraout_A0_01[4]) {
          sVar9 = extraout_A0_01[3];
          extraout_A0_01[4] = -1;
          extraout_A0_01[5] = 0x32;
          extraout_A0_01[6] = 1;
          *(int *)(unaff_A4 + -0x5cb2) = *(int *)(unaff_A4 + -0x5cb2) + 200;
          psVar1 = (short *)(unaff_A4 + -0x5bac + (int)(short)(sVar9 * 4));
          sVar4 = *psVar1 + -1;
          *psVar1 = sVar4;
          if ((sVar4 == 0) && (*(short *)(unaff_A4 + -0x5bae + (int)(short)(sVar9 * 4)) == 0)) {
            uVar7 = FUN_00015ae8();
            uVar11 = (uint)uVar7;
            *(int *)(unaff_A4 + -0x5cb2) = uVar11 + *(int *)(unaff_A4 + -0x5cb2);
            bVar2 = *(byte *)(unaff_A4 + -0x5c7b);
            bVar3 = bVar2 - 1;
            *(byte *)(unaff_A4 + -0x5c7b) = bVar3;
            if ((bVar3 == 0 || SBORROW1(bVar2,'\x01') != (int)((uint)bVar3 << 0x18) < 0) &&
               (*(char *)(unaff_A4 + -0x5c8d) == '\0')) {
              (**(code **)(unaff_A4 + -0x7f1a))();
              (**(code **)(unaff_A4 + -0x7e90))(uVar11);
            }
            else {
              (**(code **)(unaff_A4 + -0x7e96))(uVar11);
            }
          }
        }
      }
    }
  }
LAB_00014a48:
  return CONCAT44(CONCAT22((short)((uint)param_1 >> 0x10),uVar6),in_D1);
}


// ==== thunk_FUN_000146dc @ 00023028 ====

undefined8 thunk_FUN_000146dc(void)

{
  short *psVar1;
  byte bVar2;
  byte bVar3;
  short sVar4;
  char cVar7;
  int iVar5;
  ushort uVar6;
  undefined4 in_D0;
  ushort extraout_D1w;
  short sVar8;
  undefined4 in_D1;
  ushort uVar9;
  uint uVar10;
  int extraout_A0;
  short extraout_A0w;
  int extraout_A0_00;
  short *extraout_A0_01;
  short extraout_A0w_00;
  int extraout_A0_02;
  ushort *in_A0;
  short extraout_A1w;
  short extraout_A1w_00;
  short unaff_A2w;
  short unaff_A3w;
  int unaff_A4;
  
  uVar6 = *in_A0;
  cVar7 = (**(code **)(unaff_A4 + -0x7f08))();
  if ((cVar7 == '\0') || (uVar9 = extraout_D1w & 0x1fff, cVar7 == '\x01')) {
    iVar5 = FUN_00014a4e();
    if ((-1 < iVar5) && (in_A0[0x11] != 1)) {
      if (in_A0[0x11] == 2) {
        *(undefined2 *)(unaff_A4 + -0x5be8) = 5;
        *(undefined2 *)(unaff_A4 + -0x5be6) = 0xfff;
        if (*(char *)(in_A0 + 0xf) == '\n') {
          *(undefined2 *)(unaff_A4 + -0x5be6) = 0xf00;
          if ((0 < *(short *)(extraout_A0_02 + 0xc)) &&
             (sVar8 = *(short *)(extraout_A0_02 + 0xc) + -1,
             *(short *)(extraout_A0_02 + 0xc) = sVar8, sVar8 == 0)) {
            *(undefined2 *)(extraout_A0_02 + 0x18) = 0x14;
          }
          goto LAB_00014a48;
        }
      }
      *(undefined2 *)(unaff_A4 + -0x5be8) = 5;
      *(undefined2 *)(unaff_A4 + -0x5be6) = 0xfff;
      iVar5 = *(int *)(extraout_A0_02 + 6);
      if (iVar5 != 0) {
        sVar8 = *(short *)(extraout_A0_02 + 10);
        while (sVar8 = sVar8 + -1, sVar8 != -1) {
          if (*(short *)(iVar5 + 8) == 0) {
            uVar9 = uVar6 - *(short *)(iVar5 + 4);
            if ((int)((uint)uVar9 << 0x10) < 0) {
              uVar9 = -uVar9;
            }
            if ((short)uVar9 < 0x10) {
              *(undefined2 *)(iVar5 + 8) = 0xffff;
              *(undefined2 *)(iVar5 + 10) = 0x32;
              *(undefined2 *)(iVar5 + 0xc) = 1;
              *(int *)(unaff_A4 + -0x5cb2) = *(int *)(unaff_A4 + -0x5cb2) + 200;
              *(undefined2 *)(unaff_A4 + -0x5be6) = 0xf00;
              break;
            }
          }
          iVar5 = iVar5 + 0xe;
        }
      }
    }
  }
  else {
    if (in_A0[0x11] == 0) {
      *(undefined2 *)(unaff_A4 + -0x5be8) = 5;
      *(undefined2 *)(unaff_A4 + -0x5be6) = 0xfff;
    }
    if (uVar9 != 0x113) {
      if (uVar9 == 3) {
        cVar7 = FUN_00014b54();
        if (-1 < cVar7) {
          if (in_A0[0x11] == 0) {
            *(undefined2 *)(unaff_A4 + -0x5be6) = 0xf00;
          }
          if (*(char *)(extraout_A0 + 8) != '\0') {
            *(undefined2 *)(extraout_A0 + 0xe) = 200;
            *(int *)(unaff_A4 + -0x5cb2) = *(int *)(unaff_A4 + -0x5cb2) + 200;
            FUN_00014b40();
          }
        }
      }
      else if (uVar9 == 4) {
        FUN_00014ae4();
        iVar5 = *(int *)(unaff_A4 + -0x69d6);
        uVar6 = *(ushort *)(iVar5 + extraout_A0w);
        *(undefined2 *)(iVar5 + extraout_A0w) = 0x16;
        *(ushort *)(iVar5 + extraout_A0w) = uVar6 & 0x8000 | *(ushort *)(iVar5 + extraout_A0w);
        uVar6 = *(ushort *)(iVar5 + extraout_A1w);
        *(undefined2 *)(iVar5 + extraout_A1w) = 0x16;
        *(ushort *)(iVar5 + extraout_A1w) = uVar6 & 0x8000 | *(ushort *)(iVar5 + extraout_A1w);
        uVar6 = *(ushort *)(iVar5 + unaff_A2w);
        *(undefined2 *)(iVar5 + unaff_A2w) = 0x16;
        *(ushort *)(iVar5 + unaff_A2w) = uVar6 & 0x8000 | *(ushort *)(iVar5 + unaff_A2w);
        uVar6 = *(ushort *)(iVar5 + unaff_A3w);
        *(undefined2 *)(iVar5 + unaff_A3w) = 0x16;
        *(ushort *)(iVar5 + unaff_A3w) = uVar6 & 0x8000 | *(ushort *)(iVar5 + unaff_A3w);
        iVar5 = FUN_00014b54();
        if (-1 < iVar5) {
          if (in_A0[0x11] == 0) {
            *(undefined2 *)(unaff_A4 + -0x5be6) = 0xf00;
          }
          *(undefined2 *)(extraout_A0_00 + 0xc) = 0x32;
          *(undefined2 *)(extraout_A0_00 + 0xe) = 1;
          *(int *)(unaff_A4 + -0x5cb2) = *(int *)(unaff_A4 + -0x5cb2) + 0x96;
          FUN_00014b40();
        }
      }
      else if ((((0xe < uVar9) && (uVar9 < 0x1e)) && (in_A0[0x11] == 0)) &&
              (cVar7 = FUN_00014b54(), -1 < cVar7)) {
        *(undefined2 *)(unaff_A4 + -0x5be6) = 0xf00;
        sVar8 = *extraout_A0_01;
        FUN_00014ae4();
        sVar8 = (1 << (4U - (((short)((uVar6 >> 2) - sVar8) >> 1) + 3) & 0x3f) | uVar9 - 0xf) + 0xf;
        iVar5 = *(int *)(unaff_A4 + -0x69d6);
        *(ushort *)(iVar5 + extraout_A0w_00) =
             *(ushort *)(iVar5 + extraout_A0w_00) & 0x8000 | sVar8 * 4 | 2U;
        *(ushort *)(iVar5 + extraout_A1w_00) =
             *(ushort *)(iVar5 + extraout_A1w_00) & 0x8000 | sVar8 * 4 | 2U;
        *(ushort *)(iVar5 + unaff_A2w) = *(ushort *)(iVar5 + unaff_A2w) & 0x8000 | sVar8 * 4 | 2U;
        *(ushort *)(iVar5 + unaff_A3w) = *(ushort *)(iVar5 + unaff_A3w) & 0x8000 | sVar8 * 4 | 2U;
        if (-1 < extraout_A0_01[4]) {
          sVar8 = extraout_A0_01[3];
          extraout_A0_01[4] = -1;
          extraout_A0_01[5] = 0x32;
          extraout_A0_01[6] = 1;
          *(int *)(unaff_A4 + -0x5cb2) = *(int *)(unaff_A4 + -0x5cb2) + 200;
          psVar1 = (short *)(unaff_A4 + -0x5bac + (int)(short)(sVar8 * 4));
          sVar4 = *psVar1 + -1;
          *psVar1 = sVar4;
          if ((sVar4 == 0) && (*(short *)(unaff_A4 + -0x5bae + (int)(short)(sVar8 * 4)) == 0)) {
            uVar6 = FUN_00015ae8();
            uVar10 = (uint)uVar6;
            *(int *)(unaff_A4 + -0x5cb2) = uVar10 + *(int *)(unaff_A4 + -0x5cb2);
            bVar2 = *(byte *)(unaff_A4 + -0x5c7b);
            bVar3 = bVar2 - 1;
            *(byte *)(unaff_A4 + -0x5c7b) = bVar3;
            if ((bVar3 == 0 || SBORROW1(bVar2,'\x01') != (int)((uint)bVar3 << 0x18) < 0) &&
               (*(char *)(unaff_A4 + -0x5c8d) == '\0')) {
              (**(code **)(unaff_A4 + -0x7f1a))();
              (**(code **)(unaff_A4 + -0x7e90))(uVar10);
            }
            else {
              (**(code **)(unaff_A4 + -0x7e96))(uVar10);
            }
          }
        }
      }
    }
  }
LAB_00014a48:
  return CONCAT44(in_D0,in_D1);
}


// ==== thunk_FUN_00015076 @ 0002302e ====

void thunk_FUN_00015076(void)

{
  return;
}


// ==== thunk_FUN_00015078 @ 00023034 ====

undefined4 thunk_FUN_00015078(void)

{
  undefined4 in_D0;
  int unaff_A4;
  
  (**(code **)(*(int *)(unaff_A4 + -0x408a) + -0x20a))();
  return in_D0;
}


// ==== thunk_FUN_00015094 @ 0002303a ====

undefined4 thunk_FUN_00015094(void)

{
  undefined4 in_D0;
  int unaff_A4;
  
  (**(code **)(*(int *)(unaff_A4 + -0x408a) + -0x20a))();
  return in_D0;
}


// ==== thunk_FUN_000150b0 @ 00023040 ====

undefined8 thunk_FUN_000150b0(void)

{
  undefined4 in_D0;
  undefined4 in_D1;
  int unaff_A4;
  
  FUN_00016f20(*(undefined4 *)(unaff_A4 + -0x41d2));
  FUN_0001520c();
  return CONCAT44(in_D0,in_D1);
}


// ==== thunk_FUN_000150c8 @ 00023046 ====

ulonglong thunk_FUN_000150c8(void)

{
  ushort uVar1;
  undefined4 in_D0;
  undefined4 in_D1;
  int unaff_A4;
  
  uVar1 = (ushort)in_D0;
  if ((-1 < (short)uVar1) && (uVar1 < *(ushort *)(unaff_A4 + -0x69ce))) {
    uVar1 = *(ushort *)(*(int *)(unaff_A4 + -0x69d6) + (int)(short)((uVar1 >> 3) * 2));
    return CONCAT44(CONCAT22((short)((uint)in_D0 >> 0x10),uVar1),
                    CONCAT22((short)((uint)in_D1 >> 0x10),uVar1 >> 2)) & 0xffff0003ffff01ff;
  }
  return 0;
}


// ==== thunk_FUN_00015102 @ 0002304c ====

void thunk_FUN_00015102(void)

{
  return;
}


// ==== thunk_FUN_00015104 @ 00023052 ====

short thunk_FUN_00015104(void)

{
  ushort uVar1;
  ushort uVar2;
  short in_D0w;
  int unaff_A4;
  
  uVar2 = in_D0w + 0x100U & 0x3ff;
  if (0xff < uVar2) {
    uVar1 = uVar2 - 0x200;
    if (0x1ff < uVar2) {
      if (0xff < uVar1) {
        uVar1 = -(uVar2 - 0x400);
      }
      return -*(short *)(unaff_A4 + -0x6692 + (int)(short)(uVar1 * 2));
    }
    uVar2 = -uVar1;
  }
  return *(short *)(unaff_A4 + -0x6692 + (int)(short)(uVar2 * 2));
}


// ==== thunk_FUN_00015108 @ 00023058 ====

short thunk_FUN_00015108(void)

{
  ushort uVar1;
  ushort uVar2;
  ushort in_D0w;
  int unaff_A4;
  
  uVar2 = in_D0w & 0x3ff;
  if (0xff < uVar2) {
    uVar1 = uVar2 - 0x200;
    if (0x1ff < uVar2) {
      if (0xff < uVar1) {
        uVar1 = -(uVar2 - 0x400);
      }
      return -*(short *)(unaff_A4 + -0x6692 + (int)(short)(uVar1 * 2));
    }
    uVar2 = -uVar1;
  }
  return *(short *)(unaff_A4 + -0x6692 + (int)(short)(uVar2 * 2));
}


// ==== thunk_FUN_0001514c @ 0002305e ====

undefined6 thunk_FUN_0001514c(void)

{
  ushort uVar1;
  short sVar2;
  ushort in_D0w;
  undefined4 in_D1;
  int unaff_A4;
  
  uVar1 = in_D0w;
  if ((short)in_D0w < 0) {
    uVar1 = -in_D0w;
  }
  sVar2 = *(short *)(unaff_A4 + -0x6892 + (int)(short)((uVar1 & 0xff) * 2));
  if ((short)in_D0w < 0) {
    sVar2 = -sVar2;
  }
  return CONCAT24(sVar2,in_D1);
}


// ==== thunk_FUN_00015174 @ 00023064 ====

undefined8 thunk_FUN_00015174(void)

{
  short sVar1;
  undefined4 in_D0;
  undefined4 in_D1;
  int unaff_A4;
  
  sVar1 = (short)in_D0 - *(short *)(unaff_A4 + -0x60ce);
  if (*(short *)(unaff_A4 + -0x60ca) != 0) {
    sVar1 = sVar1 >> 3;
  }
  if ((-0x81 < sVar1) && (sVar1 < 0x1c1)) {
    (**(code **)(unaff_A4 + -0x7cd4))();
  }
  return CONCAT44(in_D0,in_D1);
}


// ==== thunk_FUN_000151c2 @ 0002306a ====

undefined8 thunk_FUN_000151c2(void)

{
  short sVar1;
  undefined4 in_D0;
  undefined4 in_D1;
  int unaff_A4;
  
  sVar1 = (short)in_D0 - *(short *)(unaff_A4 + -0x60ce);
  if (*(short *)(unaff_A4 + -0x60ca) != 0) {
    sVar1 = sVar1 >> 3;
  }
  if ((-0x81 < sVar1) && (sVar1 < 0x1c1)) {
    (**(code **)(unaff_A4 + -0x7cc8))();
    return CONCAT44(in_D0,in_D1);
  }
  return CONCAT44(in_D0,in_D1);
}


// ==== thunk_FUN_0001520e @ 00023070 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined6 thunk_FUN_0001520e(void)

{
  byte bVar1;
  ushort uVar2;
  undefined4 in_D1;
  int unaff_A4;
  
  bVar1 = *(byte *)(unaff_A4 + -0x5958 + (int)(short)(_DAT_00dff00c >> 6 & 0xc | _DAT_00dff00c & 3))
  ;
  uVar2 = (ushort)bVar1;
  if (((bVar1 & 3) != 0) && (*(char *)(unaff_A4 + -0x5b08) != '\0')) {
    uVar2 = uVar2 ^ 3;
  }
  return CONCAT24(uVar2,in_D1);
}


// ==== thunk_FUN_0001524a @ 00023076 ====

void thunk_FUN_0001524a(void)

{
  int unaff_A4;
  
  (**(code **)(unaff_A4 + -0x7c98))();
  return;
}


// ==== thunk_FUN_0001525c @ 0002307c ====

void thunk_FUN_0001525c(void)

{
  int unaff_A4;
  
  (**(code **)(unaff_A4 + -0x7c98))();
  return;
}


// ==== thunk_FUN_0001526e @ 00023082 ====

undefined8 thunk_FUN_0001526e(void)

{
  undefined4 in_D0;
  undefined4 in_D1;
  int unaff_A4;
  
  (**(code **)(unaff_A4 + -0x7c98))();
  return CONCAT44(in_D0,in_D1);
}


// ==== thunk_FUN_000152ac @ 00023088 ====

undefined2 thunk_FUN_000152ac(undefined4 param_1)

{
  char cVar1;
  short sVar2;
  int extraout_A1;
  undefined2 *puVar3;
  int unaff_A4;
  
  puVar3 = *(undefined2 **)(unaff_A4 + -0x40ce);
  sVar2 = 0x14;
  while( true ) {
    sVar2 = sVar2 + -1;
    if (sVar2 == -1) {
      return param_1._0_2_;
    }
    if (*(char *)(puVar3 + 1) == '\0') break;
    puVar3 = puVar3 + 2;
  }
  *puVar3 = param_1._0_2_;
  cVar1 = FUN_000150c8();
  *(char *)(extraout_A1 + 3) = cVar1;
  if (cVar1 == '\x02') {
    *(undefined1 *)(extraout_A1 + 2) = 4;
    return param_1._0_2_;
  }
  *(undefined1 *)(extraout_A1 + 2) = 6;
  return param_1._0_2_;
}


// ==== thunk_FUN_000152b0 @ 0002308e ====

undefined4 thunk_FUN_000152b0(void)

{
  char cVar1;
  undefined4 in_D0;
  short sVar2;
  int extraout_A1;
  undefined2 *puVar3;
  int unaff_A4;
  
  puVar3 = *(undefined2 **)(unaff_A4 + -0x40ce);
  sVar2 = 0x14;
  while( true ) {
    sVar2 = sVar2 + -1;
    if (sVar2 == -1) {
      return in_D0;
    }
    if (*(char *)(puVar3 + 1) == '\0') break;
    puVar3 = puVar3 + 2;
  }
  *puVar3 = (short)in_D0;
  cVar1 = FUN_000150c8();
  *(char *)(extraout_A1 + 3) = cVar1;
  if (cVar1 == '\x02') {
    *(undefined1 *)(extraout_A1 + 2) = 4;
    return in_D0;
  }
  *(undefined1 *)(extraout_A1 + 2) = 6;
  return in_D0;
}


// ==== thunk_FUN_000152f8 @ 00023094 ====

undefined8 thunk_FUN_000152f8(void)

{
  undefined4 in_D0;
  undefined4 in_D1;
  short sVar1;
  int extraout_A1;
  int iVar2;
  int unaff_A4;
  
  (**(code **)(unaff_A4 + -0x7c92))();
  iVar2 = *(int *)(unaff_A4 + -0x40ce);
  sVar1 = 0x14;
  while (sVar1 = sVar1 + -1, sVar1 != -1) {
    if (*(char *)(iVar2 + 2) != '\0') {
      FUN_00015174();
      *(char *)(extraout_A1 + 2) = *(char *)(extraout_A1 + 2) + -1;
      iVar2 = extraout_A1;
    }
    iVar2 = iVar2 + 4;
  }
  (**(code **)(unaff_A4 + -0x7c8c))();
  return CONCAT44(in_D0,in_D1);
}


// ==== thunk_FUN_0001535a @ 0002309a ====

undefined8 thunk_FUN_0001535a(void)

{
  short sVar2;
  undefined4 uVar1;
  undefined4 in_D0;
  undefined4 in_D1;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  int unaff_A4;
  undefined4 *puVar8;
  
  sVar2 = 0xb7;
  puVar3 = *(undefined4 **)(unaff_A4 + -0x41b4);
  puVar5 = *(undefined4 **)(unaff_A4 + -0x407c);
  puVar7 = *(undefined4 **)(unaff_A4 + -0x4188);
  puVar6 = *(undefined4 **)(unaff_A4 + -0x40aa);
  do {
    puVar8 = puVar6;
    puVar4 = puVar5;
    puVar6 = puVar8 + 1;
    *puVar8 = *puVar3;
    puVar5 = puVar4 + 1;
    *puVar4 = *puVar7;
    sVar2 = sVar2 + -1;
    puVar3 = puVar3 + 1;
    puVar7 = puVar7 + 1;
  } while (sVar2 != -1);
  sVar2 = 0x17;
  puVar3 = *(undefined4 **)(unaff_A4 + -0x40ae);
  if (*(undefined4 **)(unaff_A4 + -0x40ae) == (undefined4 *)0x0) {
    puVar8 = puVar8 + 2;
    *puVar6 = 0;
    puVar4 = puVar4 + 2;
    *puVar5 = 0;
  }
  else {
    do {
      puVar8 = puVar6 + 1;
      *puVar6 = *puVar3;
      uVar1 = (**(code **)(unaff_A4 + -0x7d28))();
      puVar4 = puVar5 + 1;
      *puVar5 = uVar1;
      sVar2 = sVar2 + -1;
      puVar3 = puVar3 + 1;
      puVar5 = puVar4;
      puVar6 = puVar8;
    } while (sVar2 != -1);
  }
  sVar2 = 0x1a;
  puVar3 = *(undefined4 **)(unaff_A4 + -0x40b6);
  if (*(undefined4 **)(unaff_A4 + -0x40b6) == (undefined4 *)0x0) {
    puVar7 = puVar8 + 1;
    *puVar8 = 0;
    puVar5 = puVar4 + 1;
    *puVar4 = 0;
  }
  else {
    do {
      puVar7 = puVar8 + 1;
      *puVar8 = *puVar3;
      uVar1 = (**(code **)(unaff_A4 + -0x7d28))();
      puVar5 = puVar4 + 1;
      *puVar4 = uVar1;
      sVar2 = sVar2 + -1;
      puVar3 = puVar3 + 1;
      puVar4 = puVar5;
      puVar8 = puVar7;
    } while (sVar2 != -1);
  }
  sVar2 = 0xc;
  puVar3 = *(undefined4 **)(unaff_A4 + -0x40be);
  if (*(char *)(unaff_A4 + -0x5c86) == '\0') {
    puVar4 = puVar7 + 1;
    *puVar7 = 0;
    puVar6 = puVar5 + 1;
    *puVar5 = 0;
  }
  else {
    do {
      puVar4 = puVar7 + 1;
      *puVar7 = *puVar3;
      uVar1 = (**(code **)(unaff_A4 + -0x7d28))();
      puVar6 = puVar5 + 1;
      *puVar5 = uVar1;
      sVar2 = sVar2 + -1;
      puVar3 = puVar3 + 1;
      puVar5 = puVar6;
      puVar7 = puVar4;
    } while (sVar2 != -1);
  }
  sVar2 = 0x18;
  puVar3 = *(undefined4 **)(unaff_A4 + -0x40c6);
  if (*(undefined4 **)(unaff_A4 + -0x40c6) == (undefined4 *)0x0) {
    *puVar4 = 0;
    *puVar6 = 0;
  }
  else {
    do {
      *puVar4 = *puVar3;
      uVar1 = (**(code **)(unaff_A4 + -0x7d28))();
      *puVar6 = uVar1;
      sVar2 = sVar2 + -1;
      puVar3 = puVar3 + 1;
      puVar6 = puVar6 + 1;
      puVar4 = puVar4 + 1;
    } while (sVar2 != -1);
  }
  return CONCAT44(in_D0,in_D1);
}


// ==== thunk_FUN_00015460 @ 000230a0 ====

void thunk_FUN_00015460(void)

{
  uint uVar1;
  undefined4 in_D0;
  int in_D1;
  undefined2 unaff_D2w;
  short sVar2;
  undefined4 *puVar3;
  int extraout_A0;
  int extraout_A0_00;
  int unaff_A4;
  
  sVar2 = 0x27;
  puVar3 = *(undefined4 **)(unaff_A4 + -0x40a6);
  do {
    if (*(short *)(puVar3 + 4) == 0) {
      *puVar3 = in_D0;
      if (in_D1 < 0x100000) {
        in_D1 = 0x100000;
      }
      puVar3[1] = in_D1;
      *(undefined2 *)(puVar3 + 4) = unaff_D2w;
      *(undefined2 *)((int)puVar3 + 0x12) = 6;
      uVar1 = (**(code **)(unaff_A4 + -0x7d4c))();
      *(uint *)(extraout_A0 + 8) = (uVar1 & 0xffff) + 0x10000;
      uVar1 = (**(code **)(unaff_A4 + -0x7d4c))();
      *(uint *)(extraout_A0_00 + 0xc) = (uVar1 & 0xffff) + 0x10000;
      return;
    }
    puVar3 = puVar3 + 5;
    sVar2 = sVar2 + -1;
  } while (sVar2 != -1);
  return;
}


// ==== thunk_FUN_0001555a @ 000230a6 ====

undefined4 thunk_FUN_0001555a(void)

{
  undefined4 in_A0;
  int unaff_A4;
  
  if (*(int *)(unaff_A4 + -0x5848) == 0) {
    *(undefined4 *)(unaff_A4 + -0x5848) = in_A0;
    return 0;
  }
  return 0xffffffff;
}


// ==== thunk_FUN_0001556e @ 000230ac ====

void thunk_FUN_0001556e(void)

{
  int unaff_A4;
  
  if (*(short *)(unaff_A4 + -0x6352) != 0) {
                    /* WARNING: Could not recover jumptable at 0x00015576. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(unaff_A4 + -0x7c7a))();
    return;
  }
  return;
}


// ==== thunk_FUN_0001557c @ 000230b2 ====

void thunk_FUN_0001557c(void)

{
  ushort uVar2;
  char cVar3;
  uint uVar1;
  char cVar4;
  short *psVar5;
  int unaff_A4;
  
  if ((*(char *)(unaff_A4 + -0x5ca1) != '\0') && (*(short *)(unaff_A4 + -0x60c8) == 8)) {
    psVar5 = *(short **)(unaff_A4 + -0x4098);
    cVar4 = '\0';
    (**(code **)(unaff_A4 + -0x7c92))();
    do {
      if (*(char *)((int)psVar5 + 0x11) == '\0') {
        *psVar5 = *(short *)(unaff_A4 + -0x5c6c);
        *psVar5 = *psVar5 + -0x74;
        psVar5[2] = 0x38;
        uVar2 = (**(code **)(unaff_A4 + -0x7d4c))();
        uVar2 = uVar2 >> 0xc & 3;
        cVar3 = (char)uVar2;
        if (uVar2 == 0) {
          cVar3 = '\x02';
        }
        *(char *)(psVar5 + 8) = cVar3 + -1;
        uVar1 = (**(code **)(unaff_A4 + -0x7d4c))();
        *(uint *)(psVar5 + 4) = (uVar1 & 0xffff) * 2 + 0x10000;
        uVar1 = (**(code **)(unaff_A4 + -0x7d4c))();
        *(uint *)(psVar5 + 6) = (uVar1 & 0xffff) * 2 + 0x10000;
        *(undefined1 *)((int)psVar5 + 0x11) = 0xff;
      }
      FUN_00015174();
      psVar5 = psVar5 + 9;
      cVar4 = cVar4 + '\x01';
    } while (cVar4 != '\x14');
    (**(code **)(unaff_A4 + -0x7c8c))();
  }
  return;
}


// ==== thunk_FUN_00015624 @ 000230b8 ====

void thunk_FUN_00015624(void)

{
  FUN_00015078();
  FUN_0001555a();
  return;
}


// ==== thunk_FUN_00015694 @ 000230be ====

undefined4 thunk_FUN_00015694(void)

{
  char cVar1;
  undefined4 in_D0;
  char *pcVar2;
  int unaff_A4;
  
  *(short *)(unaff_A4 + -0x5c3e) = *(short *)(unaff_A4 + -0x5c3e) + 1;
  if (*(short *)(unaff_A4 + -0x5ab6 + (int)(short)(*(short *)(unaff_A4 + -0x5c40) * 2)) <
      *(short *)(unaff_A4 + -0x5c3e)) {
    *(undefined2 *)(unaff_A4 + -0x5c3e) = 1;
    *(short *)(unaff_A4 + -0x5c40) = *(short *)(unaff_A4 + -0x5c40) + 1;
    if (6 < *(short *)(unaff_A4 + -0x5c40)) {
      *(undefined2 *)(unaff_A4 + -0x5c40) = 6;
    }
    *(undefined1 *)(unaff_A4 + -0x5ca1) = 0xff;
    pcVar2 = (char *)(unaff_A4 + -0x3e94);
    do {
      cVar1 = *pcVar2;
      pcVar2 = pcVar2 + 1;
    } while (cVar1 != '\0');
    FUN_00015078();
  }
  else {
    pcVar2 = (char *)(unaff_A4 + -0x3e94);
    do {
      cVar1 = *pcVar2;
      pcVar2 = pcVar2 + 1;
    } while (cVar1 != '\0');
    FUN_00015078();
  }
  *(undefined1 **)(unaff_A4 + -0x5848) = &DAT_000270ba;
  *(undefined2 *)(unaff_A4 + -0x5c42) = 0xffff;
  return in_D0;
}


// ==== thunk_FUN_00015bc6 @ 000230c4 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

ulonglong thunk_FUN_00015bc6(void)

{
  int iVar1;
  undefined4 uVar2;
  undefined2 unaff_D5w;
  undefined4 *puVar3;
  undefined4 in_A0;
  int *piVar4;
  int *in_A1;
  undefined4 *puVar5;
  int unaff_A4;
  undefined8 uVar6;
  ulonglong uVar7;
  undefined8 uVar8;
  
  *(undefined4 *)(unaff_A4 + -0x595c) = in_A0;
  piVar4 = in_A1;
  do {
    iVar1 = *piVar4;
    piVar4 = piVar4 + 1;
  } while (iVar1 != 0);
  uVar6 = FUN_00015d50();
  uVar2 = (undefined4)uVar6;
  if ((int)((ulonglong)uVar6 >> 0x20) != 0) {
    puVar3 = (undefined4 *)0x0;
    if (in_A1 != (int *)0x0) {
      uVar6 = FUN_000158ec(unaff_D5w);
      puVar3 = (undefined4 *)((ulonglong)uVar6 >> 0x20);
      uVar2 = (undefined4)uVar6;
      if (puVar3 != (undefined4 *)0x0) {
        *puVar3 = 0;
        while( true ) {
          puVar5 = (undefined4 *)((ulonglong)uVar6 >> 0x20);
          uVar2 = (undefined4)uVar6;
          if (*in_A1 == 0) break;
          uVar8 = (**(code **)(unaff_A4 + -0x7d28))();
          uVar6 = CONCAT44(puVar5 + 1,(int)uVar8);
          *puVar5 = (int)((ulonglong)uVar8 >> 0x20);
          in_A1 = in_A1 + 1;
        }
      }
    }
    return CONCAT44(puVar3,uVar2);
  }
  uVar7 = (**(code **)(*(int *)(unaff_A4 + -0x40e0) + -0x84))();
  (**(code **)(_DAT_00000004 + -0x20a))((int)(uVar7 >> 0x20));
  return uVar7 & 0xffffffff;
}


// ==== thunk_FUN_00015c5c @ 000230ca ====

undefined4 * thunk_FUN_00015c5c(void)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  int *in_A1;
  undefined4 *puVar3;
  int unaff_A4;
  
  puVar2 = (undefined4 *)0x0;
  if ((in_A1 != (int *)0x0) && (puVar2 = (undefined4 *)FUN_000158ec(), puVar2 != (undefined4 *)0x0))
  {
    *puVar2 = 0;
    puVar3 = puVar2;
    while (*in_A1 != 0) {
      uVar1 = (**(code **)(unaff_A4 + -0x7d28))();
      *puVar3 = uVar1;
      puVar3 = puVar3 + 1;
      in_A1 = in_A1 + 1;
    }
  }
  return puVar2;
}


// ==== thunk_FUN_00015d5a @ 000230d0 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined2 thunk_FUN_00015d5a(void)

{
  return _DAT_00dff006;
}


// ==== thunk_FUN_00016086 @ 000230d6 ====

undefined2 thunk_FUN_00016086(undefined1 *param_1,undefined4 param_2,undefined4 param_3)

{
  undefined2 uVar2;
  short sVar3;
  short sVar4;
  uint uVar1;
  ushort uVar5;
  int unaff_A4;
  undefined2 uVar6;
  undefined2 uStack_68;
  short sStack_5e;
  undefined1 uStack_5b;
  short sStack_5a;
  short sStack_58;
  short sStack_56;
  undefined1 auStack_54 [80];
  
  uStack_68 = 0;
  (**(code **)(unaff_A4 + -0x7bc6))((short)*(undefined4 *)(unaff_A4 + -0x40e4),6);
  (**(code **)(unaff_A4 + -0x7bc0))((short)*(undefined4 *)(unaff_A4 + -0x40e4),0);
  (**(code **)(unaff_A4 + -0x7bba))((short)*(undefined4 *)(unaff_A4 + -0x40e4),1);
  sStack_5a = 0;
  do {
    auStack_54[sStack_5a] = 0x20;
    sStack_5a = sStack_5a + 1;
  } while (sStack_5a < 0x50);
  sStack_58 = -1;
  sStack_56 = 0;
  while( true ) {
    while( true ) {
      while( true ) {
        if (((sStack_56 != sStack_58) && (sStack_5e == 0)) && (-1 < sStack_58)) {
          FUN_00016032(param_3._0_2_);
        }
        uVar6 = SUB42(param_1,0);
        if (sStack_5e != 0) {
          (**(code **)(unaff_A4 + -0x7bd2))
                    ((short)*(undefined4 *)(unaff_A4 + -0x40e4),param_2._2_2_,
                     param_3._0_2_ + *(short *)(*(int *)(unaff_A4 + -0x40e4) + 0x3e));
          uVar2 = (**(code **)(unaff_A4 + -0x7c6e))(uVar6);
          (**(code **)(unaff_A4 + -0x7bb4))((short)*(undefined4 *)(unaff_A4 + -0x40e4),uVar6,uVar2);
          sVar3 = (**(code **)(unaff_A4 + -0x7c6e))(uVar6);
          if (sVar3 <= param_2._0_2_) {
            sVar3 = param_2._0_2_ + 1;
            sVar4 = (**(code **)(unaff_A4 + -0x7c6e))(uVar6);
            auStack_54[(short)(sVar3 - sVar4)] = 0;
            sVar3 = (**(code **)(unaff_A4 + -0x7c6e))
                              (uVar6,param_3._0_2_ + *(short *)(*(int *)(unaff_A4 + -0x40e4) + 0x3e)
                              );
            (**(code **)(unaff_A4 + -0x7bd2))
                      ((short)*(undefined4 *)(unaff_A4 + -0x40e4),param_2._2_2_ + sVar3 * 8);
            uVar2 = (**(code **)(unaff_A4 + -0x7c6e))((short)auStack_54);
            (**(code **)(unaff_A4 + -0x7bb4))
                      ((short)*(undefined4 *)(unaff_A4 + -0x40e4),(short)auStack_54,uVar2);
            sVar3 = param_2._0_2_ + 1;
            sVar4 = (**(code **)(unaff_A4 + -0x7c6e))(uVar6);
            auStack_54[(short)(sVar3 - sVar4)] = 0x20;
          }
        }
        if ((sStack_5e != 0) || (sStack_56 != sStack_58)) {
          FUN_00016032(param_3._0_2_);
        }
        sStack_58 = sStack_56;
        sStack_5e = 0;
        while (sVar3 = (**(code **)(unaff_A4 + -0x7d04))(), sVar3 == 0) {
          (**(code **)(unaff_A4 + -0x7bae))();
          sVar3 = (**(code **)(unaff_A4 + -0x7d40))();
          if (sVar3 != 0) goto LAB_00016444;
          sVar3 = (**(code **)(unaff_A4 + -0x7d3a))();
          if (sVar3 != 0) {
            if (*(short *)(unaff_A4 + -0x38bc) == 1) {
              FUN_00018228();
              uStack_68 = 0xffff;
              goto LAB_00016444;
            }
            if (*(short *)(unaff_A4 + -0x38bc) == 5) {
              FUN_00018228();
              uStack_68 = 1;
              goto LAB_00016444;
            }
          }
        }
        uVar1 = (**(code **)(unaff_A4 + -0x7cfe))();
        uVar5 = (ushort)uVar1 & 0xff;
        sVar3 = (**(code **)(unaff_A4 + -0x7d10))((ushort)uVar1);
        if ((uVar5 == 0x44) || (uVar5 == 0x43)) goto LAB_00016444;
        if (uVar5 != 0x4f) break;
        sStack_56 = sStack_56 + -1;
        if ((sStack_56 < 0) || ((uVar1 & 0x30000) != 0)) {
          sStack_56 = 0;
        }
      }
      if (uVar5 != 0x4e) break;
      sStack_56 = sStack_56 + 1;
      sVar3 = (**(code **)(unaff_A4 + -0x7c6e))(uVar6);
      if ((sVar3 < sStack_56) || ((uVar1 & 0x30000) != 0)) {
        sStack_56 = (**(code **)(unaff_A4 + -0x7c6e))(uVar6);
      }
    }
    if (uVar5 == 0x4c) break;
    if (uVar5 == 0x4d) {
      uStack_68 = 1;
LAB_00016444:
      FUN_00016032(param_3._0_2_);
      return uStack_68;
    }
    if (uVar5 == 0x46) {
LAB_00016340:
      if (param_1[sStack_56] != '\0') {
        sStack_5a = sStack_56;
        do {
          param_1[sStack_5a] = param_1[(short)(sStack_5a + 1)];
          sStack_5a = sStack_5a + 1;
          sStack_5e = 1;
        } while (param_1[sStack_5a] != '\0');
      }
    }
    else if (uVar5 == 0x41) {
      if (sStack_56 != 0) {
        sStack_56 = sStack_56 + -1;
        goto LAB_00016340;
      }
    }
    else {
      sVar4 = (**(code **)(unaff_A4 + -0x7d10))(uVar5);
      if ((sVar4 == 0x78) && ((uVar1 & 0x800000) != 0)) {
        sStack_56 = 0;
        *param_1 = 0;
        sStack_5e = 1;
      }
      else if ((sVar3 != 0) && (sStack_56 < param_2._0_2_)) {
        for (sStack_5a = param_2._0_2_; sStack_56 < sStack_5a; sStack_5a = sStack_5a + -1) {
          param_1[sStack_5a] = param_1[(short)(sStack_5a + -1)];
        }
        param_1[param_2._0_2_] = 0;
        uStack_5b = (undefined1)sVar3;
        param_1[sStack_56] = uStack_5b;
        sStack_56 = sStack_56 + 1;
        if (param_2._0_2_ < sStack_56) {
          sStack_56 = param_2._0_2_;
        }
        sStack_5e = 1;
      }
    }
  }
  uStack_68 = 0xffff;
  goto LAB_00016444;
}


// ==== thunk_FUN_00016b60 @ 000230dc ====

void thunk_FUN_00016b60(void)

{
  int unaff_A4;
  
  FUN_0001a9fc(*(undefined4 *)(unaff_A4 + -0x42b8));
  *(undefined4 *)(unaff_A4 + -0x38b6) = 0;
  *(undefined2 *)(unaff_A4 + -0x380e) = 0x280;
  *(undefined2 *)(unaff_A4 + -0x380c) = 200;
  *(undefined1 *)(unaff_A4 + -0x38ad) = 2;
  FUN_0001692c(unaff_A4 + -0x3606);
  *(undefined4 *)(unaff_A4 + -0x380a) = 0;
  *(undefined2 *)(unaff_A4 + -0x3762) = 0x280;
  *(undefined2 *)(unaff_A4 + -0x3760) = 200;
  *(undefined1 *)(unaff_A4 + -0x3801) = 2;
  FUN_0001692c(unaff_A4 + -0x35f8);
  FUN_00016fc4(unaff_A4 + -0x3606);
  return;
}


// ==== thunk_FUN_00016fc4 @ 000230e2 ====

void thunk_FUN_00016fc4(undefined4 param_1)

{
  int unaff_A4;
  
  FUN_00016f20(param_1);
  (**(code **)(unaff_A4 + -0x7e24))();
  return;
}


// ==== thunk_FUN_00017084 @ 000230e8 ====

void thunk_FUN_00017084(void)

{
  undefined4 uVar1;
  undefined2 uVar2;
  int unaff_A4;
  undefined2 auStackY_1008a [32];
  undefined2 auStackY_1004a [32732];
  undefined2 auStack_8a [32];
  undefined2 auStack_4a [32];
  short sStack_a;
  short sStack_8;
  short sStack_6;
  
  sStack_8 = 1 << (*(byte *)(*(int *)(unaff_A4 + -0x41d6) + 9) & 0x3f);
  for (sStack_6 = 0; sStack_6 < sStack_8; sStack_6 = sStack_6 + 1) {
    auStack_4a[sStack_6] =
         *(undefined2 *)(*(int *)(*(int *)(unaff_A4 + -0x41d6) + 0x98) + sStack_6 * 2);
  }
  if (*(int *)(*(int *)(unaff_A4 + -0x41d6) + 0x9c) != 0) {
    for (sStack_6 = 0; sStack_6 < sStack_8; sStack_6 = sStack_6 + 1) {
      auStack_8a[sStack_6] =
           *(undefined2 *)(*(int *)(*(int *)(unaff_A4 + -0x41d6) + 0x9c) + sStack_6 * 2);
    }
  }
  sStack_a = 0;
  do {
    for (sStack_6 = 0; sStack_6 < sStack_8; sStack_6 = sStack_6 + 1) {
      uVar2 = FUN_00016ff6();
      *(undefined2 *)(*(int *)(*(int *)(unaff_A4 + -0x41d6) + 0x98) + sStack_6 * 2) = uVar2;
      if (*(int *)(*(int *)(unaff_A4 + -0x41d6) + 0x9c) != 0) {
        uVar2 = FUN_00016ff6();
        *(undefined2 *)(*(int *)(*(int *)(unaff_A4 + -0x41d6) + 0x9c) + sStack_6 * 2) = uVar2;
      }
    }
    uVar1 = *(undefined4 *)(*(int *)(unaff_A4 + -0x41ce) + 2);
    *(undefined4 *)(*(int *)(unaff_A4 + -0x41ce) + 2) = *(undefined4 *)(unaff_A4 + -0x339a);
    *(undefined4 *)(unaff_A4 + -0x339a) = uVar1;
    FUN_0001a0d4(*(undefined4 *)(unaff_A4 + -0x41ce));
    FUN_00016f20(*(undefined4 *)(unaff_A4 + -0x41ce));
    sStack_a = sStack_a + 1;
  } while (sStack_a < 0x10);
  return;
}


// ==== thunk_FUN_000173b0 @ 000230ee ====

void thunk_FUN_000173b0(void)

{
  undefined2 auStack_46 [32];
  short sStack_6;
  
  sStack_6 = 0;
  do {
    auStack_46[sStack_6] = 0;
    sStack_6 = sStack_6 + 1;
  } while (sStack_6 < 0x20);
  FUN_00017084(auStack_46);
  return;
}


// ==== thunk_FUN_00018022 @ 000230f4 ====

void thunk_FUN_00018022(void)

{
  short sVar1;
  int unaff_A4;
  undefined1 auStack_44 [64];
  
  FUN_000123dc(0x8122,2);
  FUN_00017e80();
  FUN_000123dc(0x812b,1);
  FUN_00016ad8();
  FUN_00017422(0x8134,(short)auStack_44);
  FUN_00016fc4((short)*(undefined4 *)(unaff_A4 + -0x41d2));
  FUN_00017084((short)unaff_A4 + -0x56b2);
  sVar1 = FUN_00016eee();
  if (sVar1 == 0) {
    FUN_00017084((short)auStack_44);
    FUN_00017422(0x8146,(short)auStack_44);
    sVar1 = FUN_00016eee();
    if (sVar1 == 0) {
      FUN_000173b0();
      FUN_00016fc4((short)*(undefined4 *)(unaff_A4 + -0x41d2));
      FUN_00017084((short)auStack_44);
      FUN_00017422(0x8158,(short)auStack_44);
      sVar1 = FUN_00016eee();
      if (sVar1 == 0) {
        FUN_000173b0();
        FUN_00016fc4((short)*(undefined4 *)(unaff_A4 + -0x41d2));
        FUN_00017084((short)auStack_44);
        FUN_00016eee();
      }
    }
  }
  FUN_000173b0();
  return;
}


// ==== thunk_FUN_0001816c @ 000230fa ====

void thunk_FUN_0001816c(void)

{
  FUN_00016e96(s_User_requested_abort__0001817e);
  return;
}


// ==== thunk_FUN_00018262 @ 00023100 ====

undefined4 thunk_FUN_00018262(void)

{
  short sVar2;
  undefined4 uVar1;
  int unaff_A4;
  int iStack_50;
  short sStack_4a;
  undefined1 auStack_48 [64];
  undefined4 uStack_8;
  
  *(undefined2 *)(unaff_A4 + -0x439a) = 0;
  FUN_000123dc(0x84f0,4);
  FUN_00016ad8();
  *(undefined2 *)(unaff_A4 + -0x42be) = 0;
  FUN_00017422(0x84f9,(short)auStack_48);
  uStack_8 = FUN_00015d4c(0x850b);
  sStack_4a = *(short *)(unaff_A4 + -0x439a);
  (**(code **)(unaff_A4 + -0x7caa))((short)*(undefined4 *)(unaff_A4 + -0x41e2));
  (**(code **)(unaff_A4 + -0x7c9e))();
  iStack_50 = (**(code **)(unaff_A4 + -0x7d2e))((short)uStack_8);
  (**(code **)(unaff_A4 + -0x7cce))((short)iStack_50,*(undefined2 *)(iStack_50 + 10));
  FUN_00016fc4((short)*(undefined4 *)(unaff_A4 + -0x41d2));
  FUN_00017084((short)auStack_48);
  FUN_0001a9ca((short)*(undefined4 *)(unaff_A4 + -0x41ce),(short)*(undefined4 *)(unaff_A4 + -0x41d2)
              );
LAB_00018302:
  do {
    sVar2 = FUN_00018194();
    if (sVar2 != 0) {
      if (sVar2 != 1000) {
        *(short *)(unaff_A4 + -0x439a) = sVar2 + *(short *)(unaff_A4 + -0x439a);
        if (*(short *)(unaff_A4 + -0x439a) < 0) {
          *(undefined2 *)(unaff_A4 + -0x439a) = 7;
        }
        if (7 < *(short *)(unaff_A4 + -0x439a)) {
          *(undefined2 *)(unaff_A4 + -0x439a) = 0;
        }
        if (*(short *)(unaff_A4 + -0x439a) != sStack_4a) {
          (**(code **)(unaff_A4 + -0x7caa))((short)*(undefined4 *)(unaff_A4 + -0x41e2));
          (**(code **)(unaff_A4 + -0x7cce))((short)iStack_50,*(undefined2 *)(iStack_50 + 10));
          iStack_50 = (**(code **)(unaff_A4 + -0x7d2e))((short)uStack_8);
          (**(code **)(unaff_A4 + -0x7cce))((short)iStack_50,*(undefined2 *)(iStack_50 + 10));
          FUN_00016fc4((short)*(undefined4 *)(unaff_A4 + -0x41d2));
          FUN_0001a9ca((short)*(undefined4 *)(unaff_A4 + -0x41ce),
                       (short)*(undefined4 *)(unaff_A4 + -0x41d2));
          sStack_4a = *(short *)(unaff_A4 + -0x439a);
          FUN_00018228();
        }
        goto LAB_00018302;
      }
      *(undefined2 *)(unaff_A4 + -0x42b2) = 1;
    }
    if (*(short *)(unaff_A4 + -0x439a) != 7) {
      (**(code **)(unaff_A4 + -0x7cec))((short)uStack_8);
      FUN_000173b0();
      if ((*(short *)(unaff_A4 + -0x42b2) == 0) && (*(int *)(unaff_A4 + -0x4078) != 0)) {
        uVar1 = (**(code **)(unaff_A4 + -0x7cf8))(5000);
        *(undefined4 *)(unaff_A4 + -0x42b0) = uVar1;
        *(undefined2 *)(unaff_A4 + -0x42b2) = 2;
      }
      if (*(short *)(unaff_A4 + -0x42b2) == 1) {
        uVar1 = FUN_00015d3e(0x8521);
        *(undefined4 *)(unaff_A4 + -0x42b0) = uVar1;
      }
      *(undefined2 *)(unaff_A4 + -0x42ac) = 0;
      if (*(int *)(unaff_A4 + -0x42b0) == 0) {
        *(undefined2 *)(unaff_A4 + -0x42b2) = 0;
      }
      if (*(short *)(unaff_A4 + -0x42b2) != 0) {
        (**(code **)(unaff_A4 + -0x7e7e))();
        (**(code **)(unaff_A4 + -0x7d46))();
      }
      *(undefined2 *)(unaff_A4 + -0x5aa6) = *(undefined2 *)(unaff_A4 + -0x439a);
      *(undefined2 *)(unaff_A4 + -0x5c40) = *(undefined2 *)(unaff_A4 + -0x439a);
      if (*(short *)(unaff_A4 + -0x42b2) == 1) {
        sVar2 = *(short *)(unaff_A4 + -0x42ac);
        *(short *)(unaff_A4 + -0x42ac) = *(short *)(unaff_A4 + -0x42ac) + 1;
        *(short *)(unaff_A4 + -0x5c40) = (short)*(char *)(*(int *)(unaff_A4 + -0x42b0) + (int)sVar2)
        ;
      }
      if (*(short *)(unaff_A4 + -0x42b2) == 2) {
        sVar2 = *(short *)(unaff_A4 + -0x42ac);
        *(short *)(unaff_A4 + -0x42ac) = *(short *)(unaff_A4 + -0x42ac) + 1;
        *(undefined1 *)(*(int *)(unaff_A4 + -0x42b0) + (int)sVar2) =
             *(undefined1 *)(unaff_A4 + -0x5c3f);
      }
      *(undefined2 *)(unaff_A4 + -0x5c3e) = 1;
      goto LAB_000184d6;
    }
    sVar2 = FUN_00018b96();
    if (sVar2 == 0) {
      *(undefined2 *)(unaff_A4 + -0x42be) = 1;
      (**(code **)(unaff_A4 + -0x7cec))((short)uStack_8);
      FUN_000173b0();
LAB_000184d6:
      FUN_00012470();
      return *(undefined4 *)(unaff_A4 + -0x79ae + *(short *)(unaff_A4 + -0x5aa6) * 4);
    }
    FUN_00016a98((short)*(undefined4 *)(unaff_A4 + -0x41d2));
    FUN_0001a9ca((short)*(undefined4 *)(unaff_A4 + -0x41ce),
                 (short)*(undefined4 *)(unaff_A4 + -0x41d2));
    FUN_0001a0d4((short)*(undefined4 *)(unaff_A4 + -0x41d2));
  } while( true );
}


// ==== thunk_FUN_0001852a @ 00023106 ====

void thunk_FUN_0001852a(void)

{
  int unaff_A4;
  
  if ((*(short *)(unaff_A4 + -0x42b2) == 2) && (*(int *)(unaff_A4 + -0x4078) != 0)) {
    *(undefined1 *)(*(int *)(unaff_A4 + -0x42b0) + (int)*(short *)(unaff_A4 + -0x42ac)) = 0xff;
    (**(code **)(unaff_A4 + -0x7d64))
              (*(undefined4 *)(unaff_A4 + -0x4078),*(undefined4 *)(unaff_A4 + -0x42b0),5000);
  }
  FUN_000124dc(unaff_A4 + -0x42b0);
  *(undefined2 *)(unaff_A4 + -0x42b2) = 0;
  return;
}


// ==== thunk_FUN_00018590 @ 0002310c ====

undefined4 thunk_FUN_00018590(void)

{
  int iVar1;
  uint uVar2;
  char cVar4;
  short sVar3;
  int unaff_A4;
  undefined2 uVar5;
  short sStack_84;
  undefined1 auStack_76 [50];
  undefined1 auStack_44 [64];
  
  FUN_00016b04();
  iVar1 = (**(code **)(unaff_A4 + -0x7d34))((short)*(undefined4 *)(unaff_A4 + -0x69cc),0x6e6b);
  uVar5 = (undefined2)*(undefined4 *)(unaff_A4 + -0x41e2);
  (**(code **)(unaff_A4 + -0x7caa))(uVar5);
  (**(code **)(unaff_A4 + -0x7c9e))();
  (**(code **)(unaff_A4 + -0x7c5c))((short)unaff_A4 + -0x56d2,(short)auStack_44);
  (**(code **)(unaff_A4 + -0x7cda))((short)iVar1,0,0x65 - (*(ushort *)(iVar1 + 2) >> 1));
  (**(code **)(unaff_A4 + -0x7bd2))(uVar5,0x128,0x3d);
  FUN_00018570((short)*(undefined4 *)(unaff_A4 + -0x56ee + *(short *)(unaff_A4 + -0x5c40) * 4));
  (**(code **)(unaff_A4 + -0x7bd2))(uVar5,0x154,0x49);
  (**(code **)(unaff_A4 + -0x7c80))((short)auStack_76,0x8764);
  FUN_00018570((short)auStack_76);
  (**(code **)(unaff_A4 + -0x7bd2))(uVar5,0x154,0x77);
  (**(code **)(unaff_A4 + -0x7c80))((short)auStack_76,0x8767);
  FUN_00018570((short)auStack_76);
  (**(code **)(unaff_A4 + -0x7bd2))(uVar5,0x154,0x83);
  (**(code **)(unaff_A4 + -0x7c80))((short)auStack_76,0x876a);
  FUN_00018570((short)auStack_76);
  FUN_00016fc4((short)*(undefined4 *)(unaff_A4 + -0x41d2));
  FUN_00017084((short)auStack_44);
  (**(code **)(unaff_A4 + -0x7bae))();
  sStack_84 = 1;
  do {
    if ((0xef < sStack_84) || (sVar3 = (**(code **)(unaff_A4 + -0x7d40))(), sVar3 != 0)) {
      FUN_000173b0();
      return 0;
    }
    (**(code **)(unaff_A4 + -0x7bae))();
    sVar3 = (**(code **)(unaff_A4 + -0x7d04))();
    if (sVar3 != 0) {
      uVar2 = (**(code **)(unaff_A4 + -0x7cfe))();
      if (((uVar2 & 0x80000) != 0) &&
         (cVar4 = (**(code **)(unaff_A4 + -0x7d10))((short)uVar2), cVar4 == 'r')) {
        FUN_000173b0();
        return 1;
      }
    }
    sStack_84 = sStack_84 + 1;
  } while( true );
}


// ==== thunk_FUN_0001876e @ 00023112 ====

void thunk_FUN_0001876e(void)

{
  undefined2 uVar1;
  int unaff_A4;
  
  uVar1 = *(undefined2 *)(*(int *)(*(int *)(unaff_A4 + -0x41d2) + 2) + 2);
  *(undefined2 *)(*(int *)(*(int *)(unaff_A4 + -0x41d2) + 2) + 2) =
       *(undefined2 *)(unaff_A4 + -0x3392);
  FUN_00019a9c(*(undefined4 *)(*(int *)(unaff_A4 + -0x41d2) + 2));
  *(undefined2 *)(*(int *)(*(int *)(unaff_A4 + -0x41d2) + 2) + 2) = uVar1;
  return;
}


// ==== thunk_FUN_00018806 @ 00023118 ====

void thunk_FUN_00018806(void)

{
  int unaff_A4;
  undefined2 uStack_6;
  
  FUN_0001a9fc(*(undefined4 *)(unaff_A4 + -0x42b8));
  FUN_00016cc6();
  FUN_0001a548(*(undefined4 *)(unaff_A4 + -0x38ba),**(undefined4 **)(unaff_A4 + -0x41de));
  (**(code **)(unaff_A4 + -0x7cec))(*(undefined4 *)(unaff_A4 + -0x38ba));
  uStack_6 = 0;
  do {
    *(undefined2 *)(unaff_A4 + -0x3566 + uStack_6 * 2) =
         *(undefined2 *)(*(int *)(**(int **)(unaff_A4 + -0x41de) + 0x98) + uStack_6 * 2);
    *(undefined2 *)(unaff_A4 + -0x3526 + uStack_6 * 2) =
         *(undefined2 *)(*(int *)(**(int **)(unaff_A4 + -0x41de) + 0x98) + uStack_6 * 2);
    uStack_6 = uStack_6 + 1;
  } while (uStack_6 < 0x20);
  *(undefined4 *)(unaff_A4 + -0x5848) = 0;
  *(undefined2 *)(unaff_A4 + -0x5a36) = 0;
  FUN_00015d3e(*(undefined4 *)(unaff_A4 + -0x570e + *(short *)(unaff_A4 + -0x5c6e) * 4));
  FUN_00016dd6(*(undefined4 *)(unaff_A4 + -0x3384),
               *(undefined4 *)(*(int *)(unaff_A4 + -0x41de) + 0x98));
  (**(code **)(unaff_A4 + -0x7cec))(*(undefined4 *)(unaff_A4 + -0x3384));
  FUN_00015d3e(*(undefined4 *)(unaff_A4 + -0x56fe + *(short *)(unaff_A4 + -0x5c6e) * 4));
  FUN_00016dd6(*(undefined4 *)(unaff_A4 + -0x3384),
               *(undefined4 *)(*(int *)(unaff_A4 + -0x41de) + 0x9c));
  (**(code **)(unaff_A4 + -0x7cec))(*(undefined4 *)(unaff_A4 + -0x3384));
  *(undefined2 *)(*(int *)(*(int *)**(undefined4 **)(unaff_A4 + -0x41de) + 0x98) + 2) = 0x777;
  FUN_0001a9fc(*(undefined4 *)(unaff_A4 + -0x42b8));
  FUN_0001a9ca(*(undefined4 *)(unaff_A4 + -0x41d2),*(undefined4 *)(unaff_A4 + -0x41ce));
  FUN_0001a0d4(*(undefined4 *)(unaff_A4 + -0x41d2));
  FUN_0001a0d4(*(undefined4 *)(unaff_A4 + -0x41ce));
  FUN_000187ba(*(undefined4 *)(*(int *)(unaff_A4 + -0x41d2) + 2));
  FUN_000187ba(*(undefined4 *)(*(int *)(unaff_A4 + -0x41ce) + 2));
  FUN_0001d1ea();
  return;
}


// ==== thunk_FUN_00019856 @ 0002311e ====

void thunk_FUN_00019856(void)

{
  int unaff_A4;
  undefined1 auStack_21e [410];
  undefined1 auStack_84 [64];
  undefined1 auStack_44 [64];
  
  *(undefined1 **)(unaff_A4 + -0x3224) = auStack_21e;
  FUN_000123dc(0x9928,0);
  FUN_00019472();
  FUN_00016d7a();
  *(int *)(unaff_A4 + -0x41d2) = unaff_A4 + -0x3606;
  *(undefined4 *)(unaff_A4 + -0x41de) = **(undefined4 **)(*(int *)(unaff_A4 + -0x41d2) + 6);
  *(int *)(unaff_A4 + -0x41e2) = *(int *)(unaff_A4 + -0x41de) + 0x2c;
  *(int *)(unaff_A4 + -0x41ca) = *(int *)(unaff_A4 + -0x41de) + 4;
  FUN_00017422(0x9931,(short)auStack_84);
  (**(code **)(unaff_A4 + -0x7caa))((short)*(undefined4 *)(unaff_A4 + -0x41e2));
  (**(code **)(unaff_A4 + -0x7c9e))();
  FUN_0001967e();
  *(undefined4 *)(unaff_A4 + -0x41de) = *(undefined4 *)(*(int *)(unaff_A4 + -0x41d2) + 6);
  *(int *)(unaff_A4 + -0x41e2) = *(int *)(unaff_A4 + -0x41de) + 0x2c;
  *(int *)(unaff_A4 + -0x41ca) = *(int *)(unaff_A4 + -0x41de) + 4;
  FUN_00017422(0x9944,(short)auStack_44);
  FUN_00016fc4((short)*(undefined4 *)(unaff_A4 + -0x41d2));
  FUN_000171f2((short)auStack_44,(short)auStack_84);
  FUN_00016eee();
  FUN_000173e6();
  return;
}


// ==== thunk_FUN_0001aa32 @ 00023124 ====

void thunk_FUN_0001aa32(void)

{
  int unaff_A4;
  
  *(undefined1 *)(unaff_A4 + -0x5a40) = 0;
  do {
  } while (*(char *)(unaff_A4 + -0x5a40) == '\0');
  return;
}


// ==== thunk_FUN_0001aa3e @ 0002312a ====

void thunk_FUN_0001aa3e(void)

{
  int unaff_A4;
  
  do {
  } while (*(char *)(unaff_A4 + -0x5a40) == '\0');
  *(undefined1 *)(unaff_A4 + -0x5a40) = 0;
  return;
}


// ==== thunk_FUN_0001aa50 @ 00023130 ====

void thunk_FUN_0001aa50(void)

{
  int unaff_A4;
  
  *(undefined2 *)(unaff_A4 + -0x321c) = 1;
  *(undefined2 *)(unaff_A4 + -0x321a) = 0;
  return;
}


// ==== thunk_FUN_0001b682 @ 00023136 ====

void thunk_FUN_0001b682(void)

{
  short *psVar1;
  byte *pbVar2;
  short sVar3;
  int unaff_A4;
  int iVar4;
  undefined2 uStack_10;
  undefined2 uStack_e;
  
  if (*(short *)(unaff_A4 + -0x5c94) != 0) {
    uStack_e = 0;
    *(int *)(unaff_A4 + -0x320e) = unaff_A4 + -0x5dd4;
    while (uStack_e < 4) {
      if (*(short *)(*(int *)(unaff_A4 + -0x320e) + 4) == 3) {
        uStack_10 = *(short *)(*(int *)(unaff_A4 + -0x3212) + 2) -
                    *(short *)(*(int *)(unaff_A4 + -0x320e) + 0x20);
        if (uStack_10 < 0) {
          uStack_10 = -uStack_10;
        }
        sVar3 = **(short **)(unaff_A4 + -0x3212) - *(short *)(*(int *)(unaff_A4 + -0x320e) + 0x26);
        if (sVar3 < 0) {
          sVar3 = -sVar3;
        }
        if (((uStack_10 < 0xa0) && (sVar3 < 0x14)) && (*(short *)(unaff_A4 + -0x5bfc) == 0)) {
          *(undefined2 *)(*(int *)(unaff_A4 + -0x320e) + 6) = 1;
          iVar4 = *(int *)(unaff_A4 + -0x320e);
          psVar1 = (short *)(iVar4 + 10);
          *psVar1 = *psVar1 + -1;
          if (*(short *)(iVar4 + 10) < 1) {
            FUN_0001cae0(6,CONCAT22(*(short *)(*(int *)(unaff_A4 + -0x320e) + 0x20) + -0x10,
                                    *(short *)(*(int *)(unaff_A4 + -0x320e) + 0x26) + 10));
            psVar1 = (short *)(*(int *)(unaff_A4 + -0x320e) + 8);
            *psVar1 = *psVar1 + -8;
            if (*(short *)(*(int *)(unaff_A4 + -0x320e) + 8) < 0x60) {
              *(int *)(unaff_A4 + -0x5cb2) = *(int *)(unaff_A4 + -0x5cb2) + 0x15e;
              **(undefined2 **)(unaff_A4 + -0x320e) = 4;
              *(undefined2 *)(*(int *)(unaff_A4 + -0x320e) + 0x24) = 0xfffd;
              *(undefined2 *)(*(int *)(unaff_A4 + -0x320e) + 0x16) = 0;
              pbVar2 = (byte *)(*(int *)(unaff_A4 + -0x320e) + 3);
              *pbVar2 = *pbVar2 & 0xf7;
              FUN_0001d35a(*(undefined4 *)(unaff_A4 + -0x320e));
            }
            iVar4 = *(int *)(unaff_A4 + -0x320e);
            sVar3 = FUN_0001cac8();
            *(short *)(iVar4 + 10) = sVar3 + 6;
          }
        }
      }
      uStack_e = uStack_e + 1;
      *(int *)(unaff_A4 + -0x320e) = *(int *)(unaff_A4 + -0x320e) + 0x34;
    }
  }
  return;
}


// ==== thunk_FUN_0001b7ec @ 0002313c ====

void thunk_FUN_0001b7ec(void)

{
  short sVar2;
  undefined4 uVar1;
  int unaff_A4;
  int iVar3;
  
  *(int *)(unaff_A4 + -0x3212) = unaff_A4 + -0x5f86;
  FUN_0001b7bc();
  **(undefined2 **)(unaff_A4 + -0x3212) = 0;
  *(undefined2 *)(*(int *)(unaff_A4 + -0x3212) + 0x16) = 0;
  *(undefined2 *)(*(int *)(unaff_A4 + -0x3212) + 0x18) = 0;
  *(undefined2 *)(*(int *)(unaff_A4 + -0x3212) + 0xc) = 1;
  iVar3 = *(int *)(unaff_A4 + -0x3212);
  sVar2 = FUN_0001cac8();
  *(short *)(iVar3 + 0x10) = sVar2 + 6;
  *(undefined2 *)(*(int *)(unaff_A4 + -0x3212) + 0x12) = 0x80;
  *(undefined2 *)(*(int *)(unaff_A4 + -0x3212) + 0xe) = 0xc0;
  uVar1 = FUN_0001abde();
  *(undefined4 *)(*(int *)(unaff_A4 + -0x3212) + 8) = uVar1;
  uVar1 = FUN_0001cb30((short)*(undefined4 *)(unaff_A4 + -0x69c0),
                       *(undefined4 *)(*(int *)(unaff_A4 + -0x3212) + 8));
  *(undefined4 *)(*(int *)(unaff_A4 + -0x3212) + 4) = uVar1;
  uVar1 = FUN_0001cb30((short)*(undefined4 *)(unaff_A4 + -0x69bc),
                       *(undefined4 *)(*(int *)(unaff_A4 + -0x3212) + 8));
  *(undefined4 *)(unaff_A4 + -0x5be0) = uVar1;
  *(undefined2 *)(unaff_A4 + -0x5bfc) = 0;
  *(undefined2 *)(unaff_A4 + -0x5f6a) = 0x546;
  *(undefined2 *)(unaff_A4 + -0x5bea) = 0;
  *(undefined2 *)(unaff_A4 + -0x5bf4) = 5;
  *(undefined2 *)(unaff_A4 + -0x5cb4) = 5;
  *(undefined2 *)(unaff_A4 + -0x5562) = 0;
  *(undefined2 *)(unaff_A4 + -0x3e96) = 0x1c;
  *(undefined2 *)(unaff_A4 + -0x3cb0) = *(undefined2 *)(unaff_A4 + -0x3e96);
  return;
}


// ==== thunk_FUN_0001b9bc @ 00023142 ====

void thunk_FUN_0001b9bc(void)

{
  int unaff_A4;
  
  *(undefined2 *)(unaff_A4 + -0x5bd2) = 0;
  *(undefined2 *)(unaff_A4 + -0x5bd6) = 0;
  return;
}


// ==== thunk_FUN_0001b9cc @ 00023148 ====

void thunk_FUN_0001b9cc(void)

{
  int unaff_A4;
  
  *(undefined2 *)(unaff_A4 + -0x5bd2) = 0x28;
  *(undefined2 *)(unaff_A4 + -0x5bd6) = 0x28;
  *(undefined2 *)(unaff_A4 + -0x5bd0) = 0x328;
  *(undefined2 *)(unaff_A4 + -0x5bd4) = 0x328;
  *(undefined2 *)(unaff_A4 + -0x3216) = 0;
  return;
}


// ==== thunk_FUN_0001c660 @ 0002314e ====

void thunk_FUN_0001c660(void)

{
  short sVar1;
  undefined2 uVar2;
  short sVar3;
  int unaff_A4;
  undefined2 uStack_1a;
  undefined2 uVar4;
  
  *(undefined2 *)(unaff_A4 + -0x5bee) = 100;
  FUN_0001b5b0();
  FUN_0001bc02();
  if (*(short *)(unaff_A4 + -0x5c9a) == 0) {
    if (*(short *)(unaff_A4 + -0x5bea) == 0) {
      *(undefined2 *)(unaff_A4 + -0x4374) = 0;
    }
    switch(*(undefined2 *)(*(int *)(unaff_A4 + -0x3212) + 0xc)) {
    case 0:
      if ((*(short *)(*(int *)(unaff_A4 + -0x3212) + 0x12) < 0x60) ||
         (*(short *)(*(int *)(unaff_A4 + -0x3212) + 0xe) < 0)) {
        *(undefined1 *)(unaff_A4 + -0x5c9f) = 3;
        *(undefined2 *)(*(int *)(unaff_A4 + -0x3212) + 0xc) = 4;
        *(short *)(unaff_A4 + -0x5bea) = *(short *)(*(int *)(unaff_A4 + -0x3212) + 0x16) * 100;
        FUN_0001afba();
      }
      else if (**(short **)(unaff_A4 + -0x3212) < -6) {
        *(undefined2 *)(*(int *)(unaff_A4 + -0x3212) + 0xc) = 6;
        *(undefined2 *)(unaff_A4 + -0x5556) = 0;
        *(undefined2 *)(unaff_A4 + -0x5558) = 0;
        *(undefined2 *)(unaff_A4 + -0x555a) = 0;
        *(undefined1 *)(unaff_A4 + -0x5c9f) = 3;
      }
      else {
        FUN_0001bff4();
        FUN_0001b9f0();
        FUN_0001bdfa();
        FUN_0001ba80();
        if (**(short **)(unaff_A4 + -0x3212) < 0x51) {
          *(undefined1 *)(unaff_A4 + -0x5c9f) = 2;
        }
        else {
          *(undefined1 *)(unaff_A4 + -0x5c9f) = 3;
        }
        FUN_0001bcce();
      }
      break;
    case 1:
      FUN_0001c4e8();
      FUN_0001bdba();
      FUN_0001c5f4();
      FUN_0001b92e();
      FUN_0001bcce();
      break;
    default:
      uStack_1a = (undefined2)((uint)*(undefined4 *)(unaff_A4 + -0x3212) >> 0x10);
      uVar4 = (undefined2)*(undefined4 *)(unaff_A4 + -0x3212);
      sVar1 = FUN_0001aaea();
      uVar2 = FUN_0001c982();
      sVar3 = FUN_00015710(uVar2);
      *(short *)CONCAT22(uStack_1a,uVar4) = sVar3 + sVar1;
      if (*(short *)(*(int *)(unaff_A4 + -0x320a) + 2) == 0) {
        *(undefined2 *)(*(int *)(unaff_A4 + -0x3212) + 0xc) = 1;
      }
      break;
    case 4:
      *(undefined2 *)(unaff_A4 + -0x5bd6) = 0x19;
      *(undefined2 *)(unaff_A4 + -0x5bd4) = 0x3c0;
      *(undefined2 *)(unaff_A4 + -0x3216) = 0;
      *(undefined2 *)(unaff_A4 + -0x5c94) = 0;
      *(undefined2 *)(unaff_A4 + -0x5bf6) = 0;
      FUN_0001c982();
      *(undefined1 *)(unaff_A4 + -0x5c9f) = 3;
      *(undefined2 *)(unaff_A4 + -0x5560) = 0xffff;
      FUN_0001afba();
      break;
    case 6:
      *(undefined2 *)(unaff_A4 + -0x5bd6) = 0;
      *(short *)(unaff_A4 + -0x555a) = *(short *)(unaff_A4 + -0x555a) + 1;
      if (2 < *(short *)(unaff_A4 + -0x555a)) {
        *(undefined2 *)(unaff_A4 + -0x555a) = 0;
        **(short **)(unaff_A4 + -0x3212) = **(short **)(unaff_A4 + -0x3212) + -1;
      }
      *(short *)(unaff_A4 + -0x5bfc) = *(short *)(unaff_A4 + -0x5bfc) + -0xfa;
      if (*(short *)(unaff_A4 + -0x5bfc) < -0x1194) {
        *(undefined2 *)(unaff_A4 + -0x5bfc) = 0xee6c;
      }
      FUN_0001aed8();
      FUN_0001af7c();
      break;
    case 7:
      *(undefined2 *)(unaff_A4 + -0x5bd6) = 0x28;
      *(undefined2 *)(unaff_A4 + -0x5bd4) = 0x328;
      uStack_1a = (undefined2)((uint)*(undefined4 *)(unaff_A4 + -0x3212) >> 0x10);
      uVar4 = (undefined2)*(undefined4 *)(unaff_A4 + -0x3212);
      sVar1 = FUN_0001aaea();
      uVar2 = FUN_0001c982();
      sVar3 = FUN_00015710(uVar2);
      *(short *)CONCAT22(uStack_1a,uVar4) = sVar3 + sVar1;
      *(undefined2 *)(unaff_A4 + -0x5bfc) = 0;
      *(undefined2 *)(unaff_A4 + -0x5bf6) = 0;
      *(undefined2 *)(unaff_A4 + -0x4374) = 0;
      *(short *)(unaff_A4 + -0x5bea) = *(short *)(unaff_A4 + -0x5bea) + -0x6e;
      if (*(short *)(unaff_A4 + -0x5bea) < 0) {
        *(undefined2 *)(unaff_A4 + -0x5bea) = 0;
        *(undefined2 *)(*(int *)(unaff_A4 + -0x3212) + 0xc) = 1;
        *(undefined2 *)(unaff_A4 + -0x5560) = 0xffff;
      }
      FUN_0001bdba();
      break;
    case 8:
      *(undefined4 *)(*(int *)(unaff_A4 + -0x3212) + 8) = 0x68637235;
      if (*(short *)(*(int *)(unaff_A4 + -0x3212) + 0x14) == -1) {
        *(undefined4 *)(*(int *)(unaff_A4 + -0x3212) + 8) = 0x68637266;
      }
      *(undefined2 *)(unaff_A4 + -0x5a6c) = 0;
      uVar2 = FUN_0001c982();
      sVar1 = FUN_0001cb34(uVar2);
      if (sVar1 == 0) {
        uVar2 = FUN_0001aaea();
        **(undefined2 **)(unaff_A4 + -0x3212) = uVar2;
      }
      else {
        uStack_1a = (undefined2)((uint)*(undefined4 *)(unaff_A4 + -0x3212) >> 0x10);
        uVar4 = (undefined2)*(undefined4 *)(unaff_A4 + -0x3212);
        sVar1 = FUN_0001aaea();
        sVar3 = FUN_00015710(uVar2);
        *(short *)CONCAT22(uStack_1a,uVar4) = sVar3 + sVar1;
      }
      *(short *)(unaff_A4 + -0x437a) = *(short *)(unaff_A4 + -0x437a) + 1;
      if ((*(ushort *)(unaff_A4 + -0x437a) & 3) == 0) {
        FUN_0001cae0(6,**(short **)(unaff_A4 + -0x3212) + 0xb);
      }
      FUN_0001aed8();
      FUN_0001af7c();
      break;
    case 9:
    }
    FUN_0001b45a();
    FUN_0001c378();
  }
  else {
    *(undefined2 *)(unaff_A4 + -0x3214) = 0;
    *(undefined2 *)(unaff_A4 + -0x5bea) = 0;
  }
  *(undefined2 *)(unaff_A4 + -0x5c4e) = 8;
  if (0xba < **(short **)(unaff_A4 + -0x3212)) {
    *(undefined2 *)(unaff_A4 + -0x5c4e) = 1;
  }
  return;
}


// ==== thunk_FUN_0001c9ca @ 00023154 ====

void thunk_FUN_0001c9ca(void)

{
  short sVar1;
  int unaff_A4;
  
  *(int *)(unaff_A4 + -0x436c) = *(int *)(unaff_A4 + -0x436c) + 1;
  sVar1 = (**(code **)(unaff_A4 + -0x7d40))();
  if ((sVar1 != 0) && (*(short *)(unaff_A4 + -0x4372) == 0)) {
    *(undefined4 *)(unaff_A4 + -0x4370) = *(undefined4 *)(unaff_A4 + -0x436c);
  }
  if (*(int *)(unaff_A4 + -0x436c) < *(int *)(unaff_A4 + -0x4370) + 10) {
    if ((sVar1 == 0) && (*(short *)(unaff_A4 + -0x4372) != 0)) {
      *(undefined2 *)(unaff_A4 + -0x3202) = 1;
    }
  }
  else if (sVar1 != 0) {
    *(undefined2 *)(unaff_A4 + -0x3204) = 1;
  }
  if (sVar1 == 0) {
    *(undefined4 *)(unaff_A4 + -0x4370) = 0;
  }
  *(short *)(unaff_A4 + -0x4372) = sVar1;
  return;
}


// ==== thunk_FUN_0001ca32 @ 0002315a ====

void thunk_FUN_0001ca32(void)

{
  ushort uVar1;
  int unaff_A4;
  
  uVar1 = FUN_0001cb20();
  *(undefined2 *)(unaff_A4 + -0x3c98) = 0;
  if (*(short *)(unaff_A4 + -0x3202) != 0) {
    *(byte *)(unaff_A4 + -0x3c97) = *(byte *)(unaff_A4 + -0x3c97) | 0x20;
    *(undefined2 *)(unaff_A4 + -0x3202) = 0;
    *(undefined2 *)(unaff_A4 + -0x3204) = 0;
  }
  if (*(short *)(unaff_A4 + -0x3204) != 0) {
    *(byte *)(unaff_A4 + -0x3c97) = *(byte *)(unaff_A4 + -0x3c97) | 0x10;
    *(undefined2 *)(unaff_A4 + -0x3204) = 0;
  }
  if ((uVar1 & 1) != 0) {
    *(byte *)(unaff_A4 + -0x3c97) = *(byte *)(unaff_A4 + -0x3c97) | 1;
  }
  if ((uVar1 & 2) != 0) {
    *(byte *)(unaff_A4 + -0x3c97) = *(byte *)(unaff_A4 + -0x3c97) | 2;
  }
  if ((uVar1 & 4) != 0) {
    *(byte *)(unaff_A4 + -0x3c97) = *(byte *)(unaff_A4 + -0x3c97) | 8;
  }
  if ((uVar1 & 8) != 0) {
    *(byte *)(unaff_A4 + -0x3c97) = *(byte *)(unaff_A4 + -0x3c97) | 4;
  }
  return;
}


// ==== thunk_FUN_0001cbf2 @ 00023160 ====

undefined4 thunk_FUN_0001cbf2(undefined4 param_1)

{
  short sVar1;
  int unaff_A4;
  short sStack_8;
  
  sVar1 = FUN_0001cb34(param_1);
  if (sVar1 == 0) {
    (**(code **)(unaff_A4 + -0x7c7a))(s_Not_over_a_ship_in_ShipNum__0001cc76);
  }
  else {
    sVar1 = (short)param_1 - (short)*(undefined4 *)(unaff_A4 + -0x69d6);
    sStack_8 = 0;
    do {
      if ((**(short **)(unaff_A4 + -0x5aa4 + sStack_8 * 4) <= sVar1) &&
         (sVar1 <= *(short *)(*(int *)(unaff_A4 + -0x5aa4 + sStack_8 * 4) + 2))) {
        return CONCAT22((short)((uint)(sStack_8 * 4) >> 0x10),sStack_8);
      }
      sStack_8 = sStack_8 + 1;
    } while (sStack_8 < 5);
    (**(code **)(unaff_A4 + -0x7c7a))(s_COULDN_T_FIND_A_SHIP_in_ShipNum__0001cc93);
  }
  return 1;
}


// ==== thunk_FUN_0001ccb6 @ 00023166 ====

void thunk_FUN_0001ccb6(undefined4 param_1)

{
  int iVar1;
  int unaff_A4;
  
  iVar1 = FUN_00022b7c(0);
  if (((iVar1 < 400000) && (param_1._0_2_ != 0)) &&
     (*(int *)(*(int *)(unaff_A4 + -0x40d8) + 0x34) != 0)) {
    *(undefined2 *)(unaff_A4 + -0x41e4) = 1;
    FUN_00022f1c(*(undefined4 *)(*(int *)(unaff_A4 + -0x40d8) + 0x34));
  }
  FUN_00022f28();
  return;
}


// ==== thunk_FUN_0001ccf6 @ 0002316c ====

/* WARNING: Control flow encountered unimplemented instructions */

void thunk_FUN_0001ccf6(void)

{
  byte bVar1;
  ushort uVar2;
  uint uVar3;
  char cVar8;
  short sVar6;
  undefined2 uVar7;
  undefined4 uVar4;
  int iVar5;
  ushort *puVar9;
  int unaff_A4;
  undefined1 uVar10;
  
  *(undefined4 *)(unaff_A4 + -0x40a2) = 0;
  uVar10 = 1;
LAB_0001ccfa:
  while( true ) {
    (**(code **)(unaff_A4 + -0x7d04))();
    if ((bool)uVar10) {
      return;
    }
    uVar3 = (**(code **)(unaff_A4 + -0x7cfe))();
    *(uint *)(unaff_A4 + -0x40a2) = uVar3 & 0x7fffffff;
    cVar8 = (**(code **)(unaff_A4 + -0x7d10))((short)uVar3);
    if ((*(ushort *)(unaff_A4 + -0x40a2) & 8) == 0) break;
    if (cVar8 == 'r') {
      *(undefined4 *)(unaff_A4 + -0x5848) = 0;
      FUN_00016bbc();
      uVar10 = 0;
      FUN_000173e6();
      *(undefined1 *)(unaff_A4 + -0x5a3e) = 0xff;
      *(undefined1 *)(unaff_A4 + -0x5c3c) = 0xff;
    }
    else if (cVar8 == 's') {
      bVar1 = ~*(byte *)(unaff_A4 + -0x5b07);
      *(byte *)(unaff_A4 + -0x5b07) = bVar1;
      uVar10 = bVar1 == 0;
      if (!(bool)uVar10) {
        (**(code **)(unaff_A4 + -0x7f9e))();
      }
    }
    else if (cVar8 == 'f') {
      bVar1 = ~*(byte *)(unaff_A4 + -0x5b08);
      *(byte *)(unaff_A4 + -0x5b08) = bVar1;
      uVar10 = bVar1 == 0;
    }
    else if (cVar8 == 'g') {
      uVar10 = 0;
      if (*(short *)(unaff_A4 + -0x5f7a) == 1) {
        (**(code **)(unaff_A4 + -0x7f9e))();
        uVar10 = 0;
        FUN_00018b96();
        FUN_00016d32();
        (**(code **)(unaff_A4 + -0x7fb6))();
      }
    }
    else if (cVar8 == 'l') {
      uVar10 = 0;
      if (*(short *)(unaff_A4 + -0x42b2) == 0) {
        (**(code **)(unaff_A4 + -0x7f9e))();
        (**(code **)(unaff_A4 + -0x7f56))();
        (**(code **)(unaff_A4 + -0x7f5c))();
        (**(code **)(unaff_A4 + -0x7fc2))();
        *(undefined2 *)(unaff_A4 + -0x42be) = 0;
        sVar6 = FUN_00018b96();
        uVar10 = sVar6 == 0;
        if ((bool)uVar10) {
          *(undefined2 *)(unaff_A4 + -0x42be) = 1;
          FUN_0001653c();
          (**(code **)(unaff_A4 + -0x7e42))();
          (**(code **)(unaff_A4 + -0x7d8e))();
          (**(code **)(unaff_A4 + -0x7e36))();
          (**(code **)(unaff_A4 + -0x7f68))();
          FUN_0001535a();
          (**(code **)(unaff_A4 + -0x7f62))();
          *(undefined1 *)(unaff_A4 + -0x69b0) = 0;
          *(undefined2 *)(unaff_A4 + -0x42be) = 0;
          uVar10 = 1;
          (**(code **)(unaff_A4 + -0x7fbc))();
          (**(code **)(unaff_A4 + -0x7fb6))();
        }
        else {
          FUN_0001653c();
          (**(code **)(unaff_A4 + -0x7f62))();
          FUN_00016d32();
          (**(code **)(unaff_A4 + -0x7fb6))();
        }
      }
    }
    else {
      if (cVar8 == 'b') {
                    /* WARNING: Unimplemented instruction - Truncating control flow here */
        halt_unimplemented();
      }
      if (cVar8 == 'c') {
        uVar10 = 0;
        (**(code **)(*(int *)(unaff_A4 + -0x40e0) + -0x48))();
      }
      else {
        if (cVar8 != 'v') break;
        uVar10 = *(short *)(unaff_A4 + -0x321c) == 0;
        (**(code **)(unaff_A4 + -0x7f1a))(*(undefined2 *)(unaff_A4 + -0x321a));
        (**(code **)(unaff_A4 + -0x7ea8))();
      }
    }
  }
  if (cVar8 == '\x1b') {
    bVar1 = ~*(byte *)(unaff_A4 + -0x5aa8);
    *(byte *)(unaff_A4 + -0x5aa8) = bVar1;
    uVar10 = bVar1 == 0;
    if (!(bool)uVar10) {
      (**(code **)(unaff_A4 + -0x7f9e))();
    }
    goto LAB_0001ccfa;
  }
  if (cVar8 == 'o') {
    if (*(short *)(unaff_A4 + -0x50e6) == 1) {
      sVar6 = *(short *)(unaff_A4 + -0x50e6) + 1;
      *(short *)(unaff_A4 + -0x50e6) = sVar6;
      uVar10 = sVar6 == 0;
      goto LAB_0001ccfa;
    }
  }
  else if (cVar8 == 'l') {
    if (*(short *)(unaff_A4 + -0x50e6) == 2) {
      sVar6 = *(short *)(unaff_A4 + -0x50e6) + 1;
      *(short *)(unaff_A4 + -0x50e6) = sVar6;
      uVar10 = sVar6 == 0;
      goto LAB_0001ccfa;
    }
  }
  else {
    if (cVar8 != 'n') {
      if (cVar8 == 'i') {
        uVar10 = 1;
        if (*(short *)(unaff_A4 + -0x50e6) == 0) goto LAB_0001ccfa;
        if (*(short *)(unaff_A4 + -0x50e6) == 5) {
          sVar6 = *(short *)(unaff_A4 + -0x50e8) + 0x32;
          *(short *)(unaff_A4 + -0x50e8) = sVar6;
          uVar10 = sVar6 == 0;
          goto LAB_0001ccfa;
        }
        if (*(short *)(unaff_A4 + -0x50e6) == 3) {
          sVar6 = *(short *)(unaff_A4 + -0x50e6) + 1;
          *(short *)(unaff_A4 + -0x50e6) = sVar6;
          uVar10 = sVar6 == 0;
          goto LAB_0001ccfa;
        }
        *(undefined2 *)(unaff_A4 + -0x50e6) = 0;
      }
      if (cVar8 == 'k') {
        uVar10 = 0;
        if (*(short *)(unaff_A4 + -0x50e6) == 5) {
          sVar6 = *(short *)(unaff_A4 + -0x50e8) + -0x32;
          *(short *)(unaff_A4 + -0x50e8) = sVar6;
          uVar10 = sVar6 == 0;
        }
      }
      else if (cVar8 == 'f') {
        uVar10 = 0;
        if (*(short *)(unaff_A4 + -0x50e6) == 5) {
          *(undefined2 *)(unaff_A4 + -0x5f78) = 0x80;
          uVar10 = 0;
        }
      }
      else if (cVar8 == 'p') {
        uVar10 = 0;
        if (*(short *)(unaff_A4 + -0x50e6) == 5) {
          cVar8 = *(char *)(unaff_A4 + -0x5ca2) + '\x01';
          *(char *)(unaff_A4 + -0x5ca2) = cVar8;
          uVar10 = cVar8 == '\0';
        }
      }
      else if (*(char *)(unaff_A4 + -0x409f) == 'Y') {
        uVar10 = 0;
        if (*(short *)(unaff_A4 + -0x50e6) == 5) {
          *(undefined4 *)(unaff_A4 + -0x5848) = 0;
          uVar10 = 1;
        }
      }
      else if (cVar8 == ' ') {
        uVar10 = 0;
        if (*(short *)(unaff_A4 + -0x50e6) == 5) {
          iVar5 = *(int *)(unaff_A4 + -0x408a);
          uVar7 = (**(code **)(iVar5 + -0xd8))();
          uVar7 = (**(code **)(iVar5 + -0xd8))(uVar7);
          uVar4 = (**(code **)(iVar5 + -0xd8))(uVar7);
          iVar5 = (**(code **)(iVar5 + -0xd8))(uVar4);
          uVar10 = iVar5 == 0;
          (**(code **)(unaff_A4 + -0x7f1a))(iVar5);
          (**(code **)(unaff_A4 + -0x7ea8))();
        }
      }
      else if (*(char *)(unaff_A4 + -0x409f) == '_') {
        uVar10 = 0;
        if (*(short *)(unaff_A4 + -0x50e6) == 5) {
          sVar6 = 0;
          puVar9 = (ushort *)(unaff_A4 + -0x5bc6);
          while (*puVar9 <= *(ushort *)(unaff_A4 + -0x41a2) >> 2) {
            sVar6 = sVar6 + 1;
            puVar9 = puVar9 + 1;
          }
          uVar10 = sVar6 == 0;
          (**(code **)(unaff_A4 + -0x7f1a))();
          (**(code **)(unaff_A4 + -0x7ea8))();
        }
      }
      else if (cVar8 == 'q') {
        uVar10 = *(short *)(unaff_A4 + -0x50e6) == 5;
        if ((bool)uVar10) {
          *(undefined1 *)(unaff_A4 + -0x407e) = 0xff;
          *(undefined1 *)(unaff_A4 + -0x5c3c) = 0xff;
        }
      }
      else if (cVar8 == 'm') {
        uVar10 = 0;
        if (*(short *)(unaff_A4 + -0x50e6) == 5) {
          if (*(char *)(unaff_A4 + -0x5c91) == -1) {
            cVar8 = *(char *)(unaff_A4 + -0x6405 + (int)*(short *)(unaff_A4 + -0x5c5a));
            *(char *)(unaff_A4 + -0x5c91) = cVar8;
            uVar10 = cVar8 == '\0';
            (**(code **)(unaff_A4 + -0x7d88))();
          }
          else {
            *(undefined1 *)(unaff_A4 + -0x5c91) = 0xff;
            uVar10 = 0;
          }
        }
      }
      else if (cVar8 == 'r') {
        uVar10 = *(short *)(unaff_A4 + -0x50e6) == 5;
        if ((bool)uVar10) {
          (**(code **)(unaff_A4 + -0x7f4a))();
        }
      }
      else {
        if (cVar8 != 'c') {
          if (cVar8 == '8') {
            uVar10 = *(short *)(unaff_A4 + -0x50e6) == 5;
            if (!(bool)uVar10) goto LAB_0001ccfa;
            *(int *)(unaff_A4 + -0x5cae) = *(int *)(unaff_A4 + -0x5cae) + 0x1000;
          }
          else if (cVar8 == '2') {
            uVar10 = *(short *)(unaff_A4 + -0x50e6) == 5;
            if (!(bool)uVar10) goto LAB_0001ccfa;
            *(int *)(unaff_A4 + -0x5cae) = *(int *)(unaff_A4 + -0x5cae) + -0x1000;
          }
          else if (cVar8 == '4') {
            uVar10 = *(short *)(unaff_A4 + -0x50e6) == 5;
            if (!(bool)uVar10) goto LAB_0001ccfa;
            *(int *)(unaff_A4 + -0x5cae) = *(int *)(unaff_A4 + -0x5cae) + -0x100;
          }
          else if (cVar8 == '6') {
            uVar10 = *(short *)(unaff_A4 + -0x50e6) == 5;
            if (!(bool)uVar10) goto LAB_0001ccfa;
            *(int *)(unaff_A4 + -0x5cae) = *(int *)(unaff_A4 + -0x5cae) + 0x100;
          }
          uVar10 = 0;
          if ((cVar8 == 'd') && (uVar10 = 0, *(short *)(unaff_A4 + -0x50e6) == 5)) {
            *(undefined2 *)(unaff_A4 + -0x5f74) = 0x80;
            *(undefined2 *)(unaff_A4 + -0x5f7a) = 0;
            uVar2 = ~*(ushort *)(unaff_A4 + -0x408c);
            *(ushort *)(unaff_A4 + -0x408c) = uVar2;
            uVar10 = uVar2 == 0;
          }
          goto LAB_0001ccfa;
        }
        if (*(short *)(unaff_A4 + -0x50e6) == 0) {
          sVar6 = *(short *)(unaff_A4 + -0x50e6) + 1;
          *(short *)(unaff_A4 + -0x50e6) = sVar6;
          uVar10 = sVar6 == 0;
        }
        else {
          uVar10 = 0;
          if (*(short *)(unaff_A4 + -0x50e6) == 5) {
            *(short *)(unaff_A4 + -0x5c5a) = *(short *)(unaff_A4 + -0x5c5a) + 1;
            uVar10 = 0;
            if (*(short *)(unaff_A4 + -0x5c5a) == 3) {
              *(undefined2 *)(unaff_A4 + -0x5c5a) = 0;
              uVar10 = 1;
            }
          }
        }
      }
      goto LAB_0001ccfa;
    }
    if (*(short *)(unaff_A4 + -0x50e6) == 4) {
      sVar6 = *(short *)(unaff_A4 + -0x50e6) + 1;
      *(short *)(unaff_A4 + -0x50e6) = sVar6;
      uVar10 = sVar6 == 0;
      goto LAB_0001ccfa;
    }
  }
  *(undefined2 *)(unaff_A4 + -0x50e6) = 0;
  uVar10 = 1;
  goto LAB_0001ccfa;
}


// ==== thunk_FUN_0001e4d0 @ 00023172 ====

void thunk_FUN_0001e4d0(undefined4 param_1,undefined4 param_2)

{
  undefined2 *puVar1;
  bool bVar2;
  short sVar3;
  short sVar4;
  int unaff_A4;
  
  sVar4 = -1;
  bVar2 = false;
  for (sVar3 = 0; sVar3 < 4; sVar3 = sVar3 + 1) {
    if (*(short *)(unaff_A4 + -0x5dd4 + sVar3 * 0x34) == 0) {
      sVar4 = sVar3;
    }
    if (((*(byte *)(unaff_A4 + -0x5dd1 + sVar3 * 0x34) & 4) != 0) &&
       (*(short *)(unaff_A4 + -0x5dd4 + sVar3 * 0x34) != 0)) {
      bVar2 = true;
    }
  }
  if ((sVar4 != -1) && (((param_1._0_2_ != 0 && (!bVar2)) || (param_1._0_2_ == 0)))) {
    puVar1 = (undefined2 *)(unaff_A4 + -0x5dd4 + sVar4 * 0x34);
    *puVar1 = 2;
    puVar1[10] = param_2._2_2_;
    puVar1[0x10] = param_1._2_2_;
    puVar1[0x12] = 0x32;
    puVar1[0xf] = *(undefined2 *)(unaff_A4 + -0x50ac);
    puVar1[0xe] = *(undefined2 *)(unaff_A4 + -0x50ac);
    puVar1[4] = 0xf0;
    sVar3 = FUN_0001cac8();
    puVar1[5] = sVar3 + 5;
    puVar1[3] = 0;
    puVar1[2] = 0;
    puVar1[0xc] = 0;
    puVar1[0xb] = 0;
    puVar1[6] = 0;
    if (param_1._0_2_ == 0) {
      *(short *)(unaff_A4 + -0x5e28) = *(short *)(unaff_A4 + -0x5e28) + 1;
      puVar1[1] = 1;
      puVar1[0x13] = param_2._0_2_;
    }
    else {
      puVar1[1] = 4;
      puVar1[0x13] = 0x32;
    }
  }
  return;
}


// ==== thunk_FUN_0001e608 @ 00023178 ====

void thunk_FUN_0001e608(void)

{
  int unaff_A4;
  undefined1 *puStack_10;
  ushort uStack_8;
  short sStack_6;
  
  sStack_6 = 0;
  do {
    puStack_10 = (undefined1 *)(unaff_A4 + -0x5dd4 + sStack_6 * 0x34);
    for (uStack_8 = 0; uStack_8 < 0x34; uStack_8 = uStack_8 + 1) {
      *puStack_10 = 0;
      puStack_10 = puStack_10 + 1;
    }
    sStack_6 = sStack_6 + 1;
  } while (sStack_6 < 4);
  return;
}


// ==== thunk_FUN_0001e7d6 @ 0002317e ====

void thunk_FUN_0001e7d6(void)

{
  short sVar1;
  short *psVar2;
  short sVar3;
  int unaff_A4;
  
  *(undefined2 *)(unaff_A4 + -0x3198) = 0;
  sVar3 = 0;
  do {
    psVar2 = (short *)(unaff_A4 + -0x5dd4 + sVar3 * 0x34);
    if (*psVar2 != 0) {
      FUN_0001d3b4(psVar2);
      FUN_0001d476();
      sVar1 = *psVar2;
      if (sVar1 == 1) {
        FUN_0001e4c8(psVar2);
      }
      else if (sVar1 == 2) {
        FUN_0001e728(psVar2);
        if (((*(byte *)((int)psVar2 + 3) & 4) == 0) && (psVar2[0x12] < 0x21)) {
          psVar2[0x12] = 0x21;
        }
      }
      else if (sVar1 == 4) {
        FUN_0001e244(psVar2);
      }
      else if ((sVar1 != 8) && (sVar1 == 0x10)) {
        FUN_0001e3e8(psVar2);
      }
      FUN_0001e64e(psVar2);
      if (*psVar2 != 0x10) {
        FUN_0001d796(psVar2);
      }
      FUN_0001d35a(psVar2);
    }
    sVar3 = sVar3 + 1;
  } while (sVar3 < 4);
  return;
}


// ==== thunk_FUN_0001e8b8 @ 00023184 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 thunk_FUN_0001e8b8(void)

{
  short sVar1;
  undefined4 *puVar2;
  int unaff_A4;
  
  if (*(short *)(unaff_A4 + -0x3196) == 0) {
    *(undefined4 *)(unaff_A4 + -0x3194) = 0;
    sVar1 = 3;
    puVar2 = (undefined4 *)(unaff_A4 + -0x3190);
    do {
      *puVar2 = 0;
      *(undefined2 *)(puVar2 + 2) = 0;
      *(undefined4 *)((int)puVar2 + 0x16) = 0xffffffff;
      puVar2[1] = 0;
      puVar2 = (undefined4 *)((int)puVar2 + 0x1e);
      sVar1 = sVar1 + -1;
    } while (sVar1 != -1);
    _DAT_00dff096 = 0xf;
    _DAT_00dff09e = 0xff;
    *(code **)(unaff_A4 + -0x3118) = _DAT_00000070;
    _DAT_00000070 = FUN_0001ebaa;
    _DAT_00dff09c = 0x780;
    _DAT_00dff09a = 0x8780;
    *(undefined1 *)(unaff_A4 + -0x310c) = 2;
    *(undefined1 *)(unaff_A4 + -0x310b) = 0x1e;
    *(char **)(unaff_A4 + -0x310a) = s_SoundFX_IntHandler_00026154;
    *(undefined1 **)(unaff_A4 + -0x3102) = &LAB_0001ec64;
    (**(code **)(*(int *)(unaff_A4 + -0x408a) + -0xa8))();
    *(undefined2 *)(unaff_A4 + -0x3196) = 1;
  }
  return 0;
}


// ==== thunk_FUN_0001e94c @ 0002318a ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 thunk_FUN_0001e94c(void)

{
  int unaff_A4;
  
  if (*(short *)(unaff_A4 + -0x3196) != 0) {
    (**(code **)(unaff_A4 + -0x7da6))();
    (**(code **)(*(int *)(unaff_A4 + -0x40e0) + -0xc6))();
    (**(code **)(*(int *)(unaff_A4 + -0x408a) + -0xae))();
    _DAT_00dff09a = 0x780;
    _DAT_00dff096 = 0xf;
    _DAT_00000070 = *(undefined4 *)(unaff_A4 + -0x3118);
    *(undefined2 *)(unaff_A4 + -0x3196) = 0;
  }
  return 0;
}


// ==== thunk_FUN_0001e9de @ 00023190 ====

undefined4 thunk_FUN_0001e9de(void)

{
  undefined4 in_D0;
  int unaff_A4;
  
  do {
    if (*(char *)(unaff_A4 + -0x30ea) < '\0') {
      return in_D0;
    }
  } while (DAT_00bfe0ff < '\0');
  return in_D0;
}


// ==== thunk_FUN_0001e9f4 @ 00023196 ====

undefined8 thunk_FUN_0001e9f4(void)

{
  undefined4 in_D0;
  undefined4 in_D1;
  int unaff_A4;
  
  *(undefined1 *)(unaff_A4 + -0x30ea) = 0;
  *(undefined1 *)(unaff_A4 + -0x30e9) = 0xff;
  (**(code **)(unaff_A4 + -0x7da0))();
  (**(code **)(*(int *)(unaff_A4 + -0x40e0) + -0xc6))();
  *(undefined1 *)(unaff_A4 + -0x30e8) = 0;
  return CONCAT44(in_D0,in_D1);
}


// ==== thunk_FUN_0001ea18 @ 0002319c ====

void thunk_FUN_0001ea18(void)

{
  int unaff_A4;
  
  (**(code **)(unaff_A4 + -0x7da0))();
  *(undefined1 *)(unaff_A4 + -0x30e9) = 0;
  *(undefined1 *)(unaff_A4 + -0x30e8) = 0;
  return;
}


// ==== thunk_FUN_0001ea28 @ 000231a2 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 thunk_FUN_0001ea28(void)

{
  undefined4 *puVar1;
  short sVar2;
  uint in_D0;
  short extraout_D1w;
  short extraout_D1w_00;
  short sVar3;
  undefined4 in_D1;
  undefined2 unaff_D2w;
  undefined2 unaff_D3w;
  undefined2 unaff_D4w;
  undefined4 extraout_A0;
  undefined4 extraout_A0_00;
  undefined4 uVar4;
  int in_A0;
  int unaff_A4;
  
  if (in_A0 != 0) {
    if ((short)in_D1 == 6) {
      FUN_0001e9f4();
    }
    sVar2 = (**(code **)(unaff_A4 + -0x7d9a))();
    uVar4 = extraout_A0;
    sVar3 = extraout_D1w;
    if (sVar2 != 0) {
      (**(code **)(unaff_A4 + -0x7da0))();
      uVar4 = extraout_A0_00;
      sVar3 = extraout_D1w_00;
    }
    _DAT_00dff09c = (ushort)(1 << ((ushort)(sVar3 + 7) & 0x1f));
    _DAT_00dff09a = _DAT_00dff09c | 0x8000;
    puVar1 = (undefined4 *)(unaff_A4 + -0x3190 + (int)(short)(sVar3 * 0x1e));
    *(short *)((int)puVar1 + 10) = (short)(in_D0 >> 1);
    *(undefined2 *)(puVar1 + 3) = unaff_D2w;
    *(undefined2 *)((int)puVar1 + 0xe) = unaff_D3w;
    *(undefined2 *)(puVar1 + 4) = 0;
    *(undefined2 *)((int)puVar1 + 0x12) = unaff_D4w;
    *puVar1 = uVar4;
    *(undefined4 *)((int)puVar1 + 0x16) = 0xffffffff;
    *(undefined2 *)(puVar1 + 2) = 1;
  }
  return in_D1;
}


// ==== thunk_FUN_0001eab4 @ 000231a8 ====

void thunk_FUN_0001eab4(void)

{
  short sVar1;
  int unaff_A4;
  
  do {
    sVar1 = (**(code **)(unaff_A4 + -0x7da0))();
  } while (sVar1 != 0);
  return;
}


// ==== thunk_FUN_0001eac0 @ 000231ae ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8 thunk_FUN_0001eac0(void)

{
  undefined4 *puVar1;
  short sVar2;
  uint in_D0;
  undefined4 in_D1;
  int unaff_A4;
  
  sVar2 = (short)in_D0;
  puVar1 = (undefined4 *)(unaff_A4 + -0x3190 + (int)(short)(sVar2 * 0x1e));
  _DAT_00dff09a = 0x80 << (in_D0 & 0x3f);
  *(undefined2 *)(puVar1 + 2) = 0;
  _DAT_00dff096 = 1 << (in_D0 & 0x3f);
  *puVar1 = 0;
  *(undefined2 *)(puVar1 + 5) = 0xffff;
  *(undefined4 *)((int)puVar1 + 0x16) = 0xffffffff;
  *(undefined2 *)(&DAT_00dff0a8 + (short)(sVar2 << 4)) = 0;
  puVar1[1] = *(undefined4 *)(unaff_A4 + -0x3194);
  *(undefined2 *)(&DAT_00dff0a6 + (short)(sVar2 << 4)) = 0x7c;
  if (sVar2 == 2) {
    *(undefined1 *)(unaff_A4 + -0x30e8) = 0;
  }
  return CONCAT44(in_D0,in_D1);
}


// ==== thunk_FUN_0001eb2e @ 000231b4 ====

undefined8 thunk_FUN_0001eb2e(void)

{
  undefined4 uVar1;
  undefined4 in_D1;
  int unaff_A4;
  
  uVar1 = 0;
  if (*(int *)(unaff_A4 + -0x3190 + (int)(short)((short)in_D1 * 0x1e)) != 0) {
    uVar1 = 0xffffffff;
  }
  return CONCAT44(uVar1,in_D1);
}


// ==== thunk_FUN_0001eb4c @ 000231ba ====

void thunk_FUN_0001eb4c(void)

{
  int iVar1;
  short in_D0w;
  short in_D1w;
  short unaff_D2w;
  int unaff_A4;
  
  iVar1 = unaff_A4 + -0x3190 + (int)(short)(in_D0w * 0x1e);
  if (-1 < in_D1w) {
    *(short *)(&DAT_00dff0a6 + (short)(in_D0w << 4)) = in_D1w;
  }
  if (-1 < unaff_D2w) {
    *(undefined4 *)(iVar1 + 0x16) = 0xffffffff;
    *(short *)(iVar1 + 0xe) = unaff_D2w;
    *(undefined2 *)(iVar1 + 0x10) = 0;
    *(short *)(&DAT_00dff0a8 + (short)(in_D0w << 4)) = unaff_D2w;
  }
  return;
}


// ==== thunk_FUN_0001edaa @ 000231c0 ====

void thunk_FUN_0001edaa(void)

{
  FUN_0001ed7a();
  FUN_0001ed7a();
  return;
}


// ==== thunk_FUN_0001edbc @ 000231c6 ====

void thunk_FUN_0001edbc(void)

{
  int unaff_A4;
  
  *(ushort *)(unaff_A4 + -0x30d4) = (*(byte *)(unaff_A4 + -0x5c91) / 10) * -8 + 0x50;
  *(ushort *)(unaff_A4 + -0x30d2) = ((ushort)*(byte *)(unaff_A4 + -0x5c91) % 10) * -8 + 0x50;
  *(undefined1 *)(unaff_A4 + -0x30c4) = 0xff;
  *(undefined1 *)(unaff_A4 + -0x30b0) = 0xff;
  return;
}


// ==== thunk_FUN_0001edea @ 000231cc ====

void thunk_FUN_0001edea(void)

{
  ushort uVar1;
  byte bVar2;
  int unaff_A4;
  
  bVar2 = *(byte *)(unaff_A4 + -0x5ca2);
  if ((char)bVar2 < '\0') {
    bVar2 = 0;
  }
  uVar1 = (ushort)bVar2;
  if (9 < bVar2) {
    uVar1 = 9;
  }
  *(ushort *)(unaff_A4 + -0x30d0) = uVar1 * -8 + 0x59;
  *(undefined1 *)(unaff_A4 + -0x30c2) = 0xff;
  *(undefined1 *)(unaff_A4 + -0x30ae) = 0xff;
  return;
}


// ==== thunk_FUN_0001ee16 @ 000231d2 ====

undefined4 thunk_FUN_0001ee16(void)

{
  short sVar1;
  short sVar2;
  ushort uVar3;
  byte bVar4;
  short sVar5;
  short sVar6;
  ushort uVar7;
  int unaff_A4;
  short *psVar8;
  
  psVar8 = (short *)((int)**(short **)(unaff_A4 + -0x41d2) + unaff_A4 + -0x30ce);
  (**(code **)(unaff_A4 + -0x7c92))();
  (**(code **)(unaff_A4 + -0x7d70))();
  *(undefined1 *)(unaff_A4 + -0x30a2) = 0xff;
  if (((*(short *)(unaff_A4 + -0x5f7a) != 0) && (*(short *)(unaff_A4 + -0x5f7a) != 1)) &&
     (*(short *)(unaff_A4 + -0x5f7a) != 7)) {
    *(undefined2 *)(unaff_A4 + -0x30a2) = 0;
  }
  FUN_0001f21a();
  sVar6 = *(short *)(unaff_A4 + -0x5f74) + -0x60;
  if (*(short *)(unaff_A4 + -0x5f74) < 0x60) {
    sVar6 = 0;
  }
  uVar7 = sVar6 * 2 & 0xfffc;
  if ((*(short *)(unaff_A4 + -0x5f7a) < 2) && (*(short *)(unaff_A4 + -0x3216) != 0)) {
    uVar7 = uVar7 + 0x18;
  }
  if (uVar7 != *(ushort *)(unaff_A4 + -0x30a6)) {
    if ((short)uVar7 < (short)*(ushort *)(unaff_A4 + -0x30a6)) {
      *(short *)(unaff_A4 + -0x30a6) = *(short *)(unaff_A4 + -0x30a6) + -4;
    }
    else {
      *(short *)(unaff_A4 + -0x30a6) = *(short *)(unaff_A4 + -0x30a6) + 4;
    }
  }
  sVar6 = *(short *)(unaff_A4 + -0x30a6);
  sVar5 = 0xc;
  if ((*(short *)(unaff_A4 + -0x30a2) != 0) && (*(ushort *)(unaff_A4 + -0x5f74) < 0x74)) {
    sVar5 = 0x10;
    sVar1 = *(short *)(unaff_A4 + -0x30a0);
    sVar2 = sVar1 + -1;
    *(short *)(unaff_A4 + -0x30a0) = sVar2;
    if ((sVar2 == 0 || sVar1 < 1) && (sVar5 = 0xc, *(short *)(unaff_A4 + -0x30a0) != 0)) {
      *(undefined2 *)(unaff_A4 + -0x30a0) = 10;
    }
  }
  if ((sVar5 != *psVar8) || (sVar6 != psVar8[1])) {
    *psVar8 = sVar5;
    psVar8[1] = sVar6;
    (**(code **)(unaff_A4 + -0x7cd4))();
    (**(code **)(unaff_A4 + -0x7cd4))();
    (**(code **)(unaff_A4 + -0x7cd4))();
  }
  uVar7 = *(ushort *)(unaff_A4 + -0x5f78);
  if ((short)uVar7 < 0) {
    uVar7 = 0;
  }
  uVar7 = uVar7 >> 1;
  if (0x58 < uVar7) {
    uVar7 = 0x58;
  }
  uVar7 = uVar7 & 0xfffc;
  if ((uVar7 == 0) && (*(short *)(unaff_A4 + -0x30a2) != 0)) {
    uVar7 = (**(code **)(unaff_A4 + -0x7d52))();
    uVar7 = uVar7 >> 0xd & 4;
  }
  if (uVar7 != *(ushort *)(unaff_A4 + -0x30a4)) {
    if ((short)uVar7 < (short)*(ushort *)(unaff_A4 + -0x30a4)) {
      *(short *)(unaff_A4 + -0x30a4) = *(short *)(unaff_A4 + -0x30a4) + -4;
    }
    else {
      *(short *)(unaff_A4 + -0x30a4) = *(short *)(unaff_A4 + -0x30a4) + 4;
    }
  }
  sVar6 = *(short *)(unaff_A4 + -0x30a4);
  sVar5 = 0xc;
  if ((*(short *)(unaff_A4 + -0x30a2) != 0) && (*(short *)(unaff_A4 + -0x5f78) < 0x41)) {
    sVar5 = 0x10;
    sVar1 = *(short *)(unaff_A4 + -0x309e);
    sVar2 = sVar1 + -1;
    *(short *)(unaff_A4 + -0x309e) = sVar2;
    if ((sVar2 == 0 || sVar1 < 1) && (sVar5 = 0xc, *(short *)(unaff_A4 + -0x309e) != 0)) {
      *(undefined2 *)(unaff_A4 + -0x309e) = 8;
    }
  }
  if ((sVar5 != psVar8[2]) || (sVar6 != psVar8[3])) {
    psVar8[2] = sVar5;
    psVar8[3] = sVar6;
    (**(code **)(unaff_A4 + -0x7cd4))();
    (**(code **)(unaff_A4 + -0x7cd4))();
    (**(code **)(unaff_A4 + -0x7cd4))();
  }
  if (*(short *)(unaff_A4 + -0x5c5a) != psVar8[4]) {
    psVar8[4] = *(short *)(unaff_A4 + -0x5c5a);
    (**(code **)(unaff_A4 + -0x7ce0))();
  }
  bVar4 = *(byte *)(unaff_A4 + -0x5c91);
  if ((bVar4 == 0xff) || ((ushort)bVar4 != psVar8[5])) {
    sVar6 = -1;
    uVar7 = (ushort)bVar4;
    do {
      uVar3 = uVar7;
      sVar6 = sVar6 + 1;
      uVar7 = uVar3 - 10;
    } while (9 < uVar3);
    sVar5 = uVar3 * -8 + 0x50;
    sVar6 = sVar6 * -8 + 0x50;
    if (bVar4 == 0xff) {
      sVar5 = 100;
      sVar6 = 100;
    }
    sVar1 = *(short *)(unaff_A4 + -0x30d4);
    if ((sVar1 == sVar6) && (*(short *)(unaff_A4 + -0x30d2) == sVar5)) {
      psVar8[5] = (ushort)bVar4;
    }
    else {
      uVar7 = *(short *)(unaff_A4 + -0x30d2) + 1;
      if (0x50 < uVar7) {
        uVar7 = 1;
      }
      *(ushort *)(unaff_A4 + -0x30d2) = uVar7;
      if ((sVar1 != sVar6) && (*(ushort *)(unaff_A4 + -0x30d2) < 9)) {
        uVar7 = sVar1 + 1;
        if (0x50 < uVar7) {
          uVar7 = 1;
        }
        *(ushort *)(unaff_A4 + -0x30d4) = uVar7;
      }
    }
    *(undefined2 *)(unaff_A4 + -0x46a2) = 0x13;
    *(undefined2 *)(unaff_A4 + -0x46a0) = 0x1c;
    (**(code **)(unaff_A4 + -0x7cd4))();
    (**(code **)(unaff_A4 + -0x7cd4))();
  }
  bVar4 = *(byte *)(unaff_A4 + -0x5ca2);
  if ((char)bVar4 < '\0') {
    bVar4 = 0;
  }
  uVar7 = (ushort)bVar4;
  if (9 < bVar4) {
    uVar7 = 9;
  }
  if (uVar7 != psVar8[6]) {
    sVar5 = uVar7 * -8 + 0x59;
    sVar6 = *(short *)(unaff_A4 + -0x30d0);
    if (sVar5 == sVar6) {
      psVar8[6] = uVar7;
    }
    else {
      if (sVar5 < sVar6) {
        sVar6 = sVar6 + -1;
      }
      else {
        sVar6 = sVar6 + 1;
      }
      *(short *)(unaff_A4 + -0x30d0) = sVar6;
    }
    *(undefined2 *)(unaff_A4 + -0x46a2) = 0x13;
    *(undefined2 *)(unaff_A4 + -0x46a0) = 0x1c;
    (**(code **)(unaff_A4 + -0x7cd4))();
  }
  if (*(int *)(unaff_A4 + -0x5cb2) != *(int *)(psVar8 + 8)) {
    *(int *)(psVar8 + 8) = *(int *)(unaff_A4 + -0x5cb2);
    FUN_0001f26a();
  }
  uVar7 = (ushort)*(byte *)(unaff_A4 + -0x5c7f);
  if (99 < uVar7) {
    uVar7 = 99;
  }
  if (uVar7 != psVar8[7]) {
    psVar8[7] = uVar7;
    *(undefined2 *)(unaff_A4 + -0x46a2) = 0x14;
    *(undefined2 *)(unaff_A4 + -0x46a0) = 0x1c;
    FUN_0001f2b0();
    FUN_0001f2b0();
    *(undefined2 *)(unaff_A4 + -0x46a2) = 0x13;
    *(undefined2 *)(unaff_A4 + -0x46a0) = 0x1f;
    FUN_0001f200();
    FUN_0001f200();
  }
  (**(code **)(unaff_A4 + -0x7c8c))();
  return 0;
}


// ==== thunk_FUN_0001ee16 @ 000231d8 ====

undefined4 thunk_FUN_0001ee16(void)

{
  short sVar1;
  short sVar2;
  ushort uVar3;
  byte bVar4;
  short sVar5;
  short sVar6;
  ushort uVar7;
  int unaff_A4;
  short *psVar8;
  
  psVar8 = (short *)((int)**(short **)(unaff_A4 + -0x41d2) + unaff_A4 + -0x30ce);
  (**(code **)(unaff_A4 + -0x7c92))();
  (**(code **)(unaff_A4 + -0x7d70))();
  *(undefined1 *)(unaff_A4 + -0x30a2) = 0xff;
  if (((*(short *)(unaff_A4 + -0x5f7a) != 0) && (*(short *)(unaff_A4 + -0x5f7a) != 1)) &&
     (*(short *)(unaff_A4 + -0x5f7a) != 7)) {
    *(undefined2 *)(unaff_A4 + -0x30a2) = 0;
  }
  FUN_0001f21a();
  sVar6 = *(short *)(unaff_A4 + -0x5f74) + -0x60;
  if (*(short *)(unaff_A4 + -0x5f74) < 0x60) {
    sVar6 = 0;
  }
  uVar7 = sVar6 * 2 & 0xfffc;
  if ((*(short *)(unaff_A4 + -0x5f7a) < 2) && (*(short *)(unaff_A4 + -0x3216) != 0)) {
    uVar7 = uVar7 + 0x18;
  }
  if (uVar7 != *(ushort *)(unaff_A4 + -0x30a6)) {
    if ((short)uVar7 < (short)*(ushort *)(unaff_A4 + -0x30a6)) {
      *(short *)(unaff_A4 + -0x30a6) = *(short *)(unaff_A4 + -0x30a6) + -4;
    }
    else {
      *(short *)(unaff_A4 + -0x30a6) = *(short *)(unaff_A4 + -0x30a6) + 4;
    }
  }
  sVar6 = *(short *)(unaff_A4 + -0x30a6);
  sVar5 = 0xc;
  if ((*(short *)(unaff_A4 + -0x30a2) != 0) && (*(ushort *)(unaff_A4 + -0x5f74) < 0x74)) {
    sVar5 = 0x10;
    sVar1 = *(short *)(unaff_A4 + -0x30a0);
    sVar2 = sVar1 + -1;
    *(short *)(unaff_A4 + -0x30a0) = sVar2;
    if ((sVar2 == 0 || sVar1 < 1) && (sVar5 = 0xc, *(short *)(unaff_A4 + -0x30a0) != 0)) {
      *(undefined2 *)(unaff_A4 + -0x30a0) = 10;
    }
  }
  if ((sVar5 != *psVar8) || (sVar6 != psVar8[1])) {
    *psVar8 = sVar5;
    psVar8[1] = sVar6;
    (**(code **)(unaff_A4 + -0x7cd4))();
    (**(code **)(unaff_A4 + -0x7cd4))();
    (**(code **)(unaff_A4 + -0x7cd4))();
  }
  uVar7 = *(ushort *)(unaff_A4 + -0x5f78);
  if ((short)uVar7 < 0) {
    uVar7 = 0;
  }
  uVar7 = uVar7 >> 1;
  if (0x58 < uVar7) {
    uVar7 = 0x58;
  }
  uVar7 = uVar7 & 0xfffc;
  if ((uVar7 == 0) && (*(short *)(unaff_A4 + -0x30a2) != 0)) {
    uVar7 = (**(code **)(unaff_A4 + -0x7d52))();
    uVar7 = uVar7 >> 0xd & 4;
  }
  if (uVar7 != *(ushort *)(unaff_A4 + -0x30a4)) {
    if ((short)uVar7 < (short)*(ushort *)(unaff_A4 + -0x30a4)) {
      *(short *)(unaff_A4 + -0x30a4) = *(short *)(unaff_A4 + -0x30a4) + -4;
    }
    else {
      *(short *)(unaff_A4 + -0x30a4) = *(short *)(unaff_A4 + -0x30a4) + 4;
    }
  }
  sVar6 = *(short *)(unaff_A4 + -0x30a4);
  sVar5 = 0xc;
  if ((*(short *)(unaff_A4 + -0x30a2) != 0) && (*(short *)(unaff_A4 + -0x5f78) < 0x41)) {
    sVar5 = 0x10;
    sVar1 = *(short *)(unaff_A4 + -0x309e);
    sVar2 = sVar1 + -1;
    *(short *)(unaff_A4 + -0x309e) = sVar2;
    if ((sVar2 == 0 || sVar1 < 1) && (sVar5 = 0xc, *(short *)(unaff_A4 + -0x309e) != 0)) {
      *(undefined2 *)(unaff_A4 + -0x309e) = 8;
    }
  }
  if ((sVar5 != psVar8[2]) || (sVar6 != psVar8[3])) {
    psVar8[2] = sVar5;
    psVar8[3] = sVar6;
    (**(code **)(unaff_A4 + -0x7cd4))();
    (**(code **)(unaff_A4 + -0x7cd4))();
    (**(code **)(unaff_A4 + -0x7cd4))();
  }
  if (*(short *)(unaff_A4 + -0x5c5a) != psVar8[4]) {
    psVar8[4] = *(short *)(unaff_A4 + -0x5c5a);
    (**(code **)(unaff_A4 + -0x7ce0))();
  }
  bVar4 = *(byte *)(unaff_A4 + -0x5c91);
  if ((bVar4 == 0xff) || ((ushort)bVar4 != psVar8[5])) {
    sVar6 = -1;
    uVar7 = (ushort)bVar4;
    do {
      uVar3 = uVar7;
      sVar6 = sVar6 + 1;
      uVar7 = uVar3 - 10;
    } while (9 < uVar3);
    sVar5 = uVar3 * -8 + 0x50;
    sVar6 = sVar6 * -8 + 0x50;
    if (bVar4 == 0xff) {
      sVar5 = 100;
      sVar6 = 100;
    }
    sVar1 = *(short *)(unaff_A4 + -0x30d4);
    if ((sVar1 == sVar6) && (*(short *)(unaff_A4 + -0x30d2) == sVar5)) {
      psVar8[5] = (ushort)bVar4;
    }
    else {
      uVar7 = *(short *)(unaff_A4 + -0x30d2) + 1;
      if (0x50 < uVar7) {
        uVar7 = 1;
      }
      *(ushort *)(unaff_A4 + -0x30d2) = uVar7;
      if ((sVar1 != sVar6) && (*(ushort *)(unaff_A4 + -0x30d2) < 9)) {
        uVar7 = sVar1 + 1;
        if (0x50 < uVar7) {
          uVar7 = 1;
        }
        *(ushort *)(unaff_A4 + -0x30d4) = uVar7;
      }
    }
    *(undefined2 *)(unaff_A4 + -0x46a2) = 0x13;
    *(undefined2 *)(unaff_A4 + -0x46a0) = 0x1c;
    (**(code **)(unaff_A4 + -0x7cd4))();
    (**(code **)(unaff_A4 + -0x7cd4))();
  }
  bVar4 = *(byte *)(unaff_A4 + -0x5ca2);
  if ((char)bVar4 < '\0') {
    bVar4 = 0;
  }
  uVar7 = (ushort)bVar4;
  if (9 < bVar4) {
    uVar7 = 9;
  }
  if (uVar7 != psVar8[6]) {
    sVar5 = uVar7 * -8 + 0x59;
    sVar6 = *(short *)(unaff_A4 + -0x30d0);
    if (sVar5 == sVar6) {
      psVar8[6] = uVar7;
    }
    else {
      if (sVar5 < sVar6) {
        sVar6 = sVar6 + -1;
      }
      else {
        sVar6 = sVar6 + 1;
      }
      *(short *)(unaff_A4 + -0x30d0) = sVar6;
    }
    *(undefined2 *)(unaff_A4 + -0x46a2) = 0x13;
    *(undefined2 *)(unaff_A4 + -0x46a0) = 0x1c;
    (**(code **)(unaff_A4 + -0x7cd4))();
  }
  if (*(int *)(unaff_A4 + -0x5cb2) != *(int *)(psVar8 + 8)) {
    *(int *)(psVar8 + 8) = *(int *)(unaff_A4 + -0x5cb2);
    FUN_0001f26a();
  }
  uVar7 = (ushort)*(byte *)(unaff_A4 + -0x5c7f);
  if (99 < uVar7) {
    uVar7 = 99;
  }
  if (uVar7 != psVar8[7]) {
    psVar8[7] = uVar7;
    *(undefined2 *)(unaff_A4 + -0x46a2) = 0x14;
    *(undefined2 *)(unaff_A4 + -0x46a0) = 0x1c;
    FUN_0001f2b0();
    FUN_0001f2b0();
    *(undefined2 *)(unaff_A4 + -0x46a2) = 0x13;
    *(undefined2 *)(unaff_A4 + -0x46a0) = 0x1f;
    FUN_0001f200();
    FUN_0001f200();
  }
  (**(code **)(unaff_A4 + -0x7c8c))();
  return 0;
}


// ==== thunk_FUN_0001f2dc @ 000231de ====

void thunk_FUN_0001f2dc(void)

{
  int unaff_A4;
  
  (**(code **)(unaff_A4 + -0x7c98))();
  return;
}


// ==== thunk_FUN_0001f41a @ 000231e4 ====

undefined2 thunk_FUN_0001f41a(void)

{
  ushort uVar1;
  short sVar2;
  undefined2 uVar3;
  undefined2 *puVar4;
  int unaff_A4;
  undefined1 auStack_90 [50];
  undefined2 uStack_5e;
  undefined2 uStack_5c;
  undefined2 uStack_5a;
  short sStack_58;
  undefined2 uStack_56;
  undefined4 uStack_54;
  undefined1 auStack_50 [65];
  undefined1 auStack_f [11];
  
  uStack_56 = 0;
  (**(code **)(unaff_A4 + -0x7c5c))((short)(unaff_A4 + -0x470e),(short)auStack_50);
  (**(code **)(unaff_A4 + -0x7e72))();
  uStack_54 = *(undefined4 *)(unaff_A4 + -0x41e2);
  (**(code **)(unaff_A4 + -0x7caa))((short)uStack_54);
  (**(code **)(unaff_A4 + -0x7c9e))();
  (**(code **)(unaff_A4 + -0x7d52))();
  (**(code **)(unaff_A4 + -0x7d52))();
  (**(code **)(unaff_A4 + -0x7d52))();
  (**(code **)(unaff_A4 + -0x7d52))();
  uVar1 = (**(code **)(unaff_A4 + -0x7d52))();
  uVar1 = uVar1 & 0xff;
  while (uVar1 != 0) {
    (**(code **)(unaff_A4 + -0x7d52))();
    uVar1 = uVar1 - 1;
  }
  sStack_58 = (**(code **)(unaff_A4 + -0x7e7e))();
  puVar4 = (undefined2 *)(unaff_A4 + -0x4930 + (sStack_58 % 0x21) * 0x10);
  FUN_0001f374(0x2b,0xa4);
  (**(code **)(unaff_A4 + -0x7bc6))((short)uStack_54,1);
  uStack_5a = *puVar4;
  uStack_5c = puVar4[1];
  uStack_5e = puVar4[2];
  FUN_0001f332(0x30,0xf658);
  FUN_0001f332(0x3d,0xf677);
  FUN_0001f332(0x4a,0xf696);
  FUN_0001f332(0x57,0xf6a7);
  FUN_0001f332(100,0xf6c6);
  FUN_0001f332(0x71,0xf6e5);
  FUN_0001f332(0x82,0xf6f2);
  (**(code **)(unaff_A4 + -0x7bc6))((short)uStack_54,2);
  (**(code **)(unaff_A4 + -0x7bd2))((short)*(undefined4 *)(unaff_A4 + -0x41e2),0x70,0x8c);
  (**(code **)(unaff_A4 + -0x7c80))((short)auStack_90,0xf70d,uStack_5c);
  FUN_00018570((short)auStack_90);
  (**(code **)(unaff_A4 + -0x7bc6))((short)uStack_54);
  (**(code **)(unaff_A4 + -0x7e6c))((short)*(undefined4 *)(unaff_A4 + -0x41d2));
  (**(code **)(unaff_A4 + -0x7e66))((short)auStack_50);
  auStack_f[0] = 0;
  (**(code **)(unaff_A4 + -0x7bc6))((short)uStack_54,5);
  FUN_0001f374(0x91,0x99);
  (**(code **)(unaff_A4 + -0x7e78))((short)auStack_f,200,0);
  sVar2 = (**(code **)(unaff_A4 + -0x7c62))((short)auStack_f,0xf727);
  if (sVar2 == 0) {
    uStack_56 = 1;
  }
  uVar3 = FUN_0001f2ec((short)auStack_f,(short)(puVar4 + 3));
  sVar2 = (**(code **)(unaff_A4 + -0x7c62))(uVar3);
  if (sVar2 == 0) {
    uStack_56 = 1;
  }
  (**(code **)(unaff_A4 + -0x7e60))();
  return uStack_56;
}


// ==== thunk_FUN_0001fe50 @ 000231ea ====

undefined2 thunk_FUN_0001fe50(undefined4 param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  int iVar2;
  int unaff_A4;
  undefined2 uStack_6;
  
  uStack_6 = 0;
  iVar1 = (**(code **)(unaff_A4 + -0x7c14))(param_1,0x3ee);
  if (iVar1 == 0) {
    uStack_6 = (**(code **)(unaff_A4 + -0x7c20))();
  }
  else {
    iVar2 = (**(code **)(unaff_A4 + -0x7c02))(iVar1,param_2,param_3);
    (**(code **)(unaff_A4 + -0x7c38))(iVar1);
    if (iVar2 != param_3) {
      uStack_6 = (**(code **)(unaff_A4 + -0x7c20))();
    }
  }
  return uStack_6;
}


// ==== thunk_FUN_0001feb4 @ 000231f0 ====

void thunk_FUN_0001feb4(undefined4 param_1)

{
  FUN_0001ff16(param_1,0x10001);
  return;
}


// ==== thunk_FUN_0001feca @ 000231f6 ====

void thunk_FUN_0001feca(undefined4 param_1)

{
  FUN_0001ff16(param_1,0x10003);
  return;
}


// ==== thunk_FUN_000203be @ 000231fc ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void thunk_FUN_000203be(void)

{
  int unaff_A4;
  
  *(ushort *)(unaff_A4 + -0x46ee) = _DAT_00dff006 ^ *(short *)(unaff_A4 + -0x46ec) * 0x1afb - 0x333U
  ;
  return;
}


// ==== thunk_FUN_000203be @ 00023202 ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void thunk_FUN_000203be(void)

{
  int unaff_A4;
  
  *(ushort *)(unaff_A4 + -0x46ee) = _DAT_00dff006 ^ *(short *)(unaff_A4 + -0x46ec) * 0x1afb - 0x333U
  ;
  return;
}


// ==== thunk_FUN_000203da @ 00023208 ====

void thunk_FUN_000203da(undefined4 param_1)

{
  int unaff_A4;
  
  *(undefined2 *)(unaff_A4 + -0x46ee) = param_1._0_2_;
  *(undefined2 *)(unaff_A4 + -0x46ec) = param_1._0_2_;
  return;
}


// ==== thunk_FUN_0002044c @ 0002320e ====

void thunk_FUN_0002044c(void)

{
  undefined2 uVar1;
  int unaff_A4;
  
  uVar1 = FUN_0002046a();
  *(undefined2 *)(unaff_A4 + -0x3098) = uVar1;
  return;
}


// ==== thunk_FUN_00020454 @ 00023214 ====

void thunk_FUN_00020454(void)

{
  undefined2 uVar1;
  int unaff_A4;
  
  uVar1 = FUN_00020488();
  *(undefined2 *)(unaff_A4 + -0x38bc) = uVar1;
  return;
}


// ==== thunk_FUN_000204f4 @ 0002321a ====

undefined4 thunk_FUN_000204f4(void)

{
  undefined4 extraout_A0;
  
  FUN_00020560();
  return extraout_A0;
}


// ==== thunk_FUN_0002050e @ 00023220 ====

int thunk_FUN_0002050e(int param_1,undefined4 param_2)

{
  return param_1 + (uint)(ushort)(*(short *)(param_1 + 4) << 3) +
                   *(int *)(param_1 + (uint)(ushort)(param_2._0_2_ + *(short *)(param_1 + 4)) * 4 +
                           6) + 6;
}


// ==== thunk_FUN_00020560 @ 00023226 ====

undefined8 thunk_FUN_00020560(void)

{
  int *piVar1;
  int iVar2;
  int in_D0;
  short sVar3;
  undefined4 in_D1;
  int in_A0;
  int *piVar4;
  
  sVar3 = *(short *)(in_A0 + 4);
  if (0 < sVar3) {
    piVar1 = (int *)(in_A0 + 6);
    do {
      piVar4 = piVar1;
      if (in_D0 <= *piVar4) break;
      sVar3 = sVar3 + -1;
      piVar1 = piVar4 + 1;
    } while (sVar3 != -1);
    if (in_D0 == *piVar4) {
      iVar2 = *(short *)(in_A0 + 4) * 8 +
              in_A0 + *(int *)((short)((uint)((int)piVar4 + (-6 - in_A0)) >> 2) * 4 +
                               *(short *)(in_A0 + 4) * 4 + in_A0 + 6) + 6;
      goto LAB_000205ac;
    }
  }
  iVar2 = 0;
LAB_000205ac:
  return CONCAT44(iVar2,in_D1);
}


// ==== thunk_FUN_000205cc @ 0002322c ====

void thunk_FUN_000205cc(undefined4 param_1)

{
  undefined4 uVar1;
  int unaff_A4;
  
  *(undefined2 *)(unaff_A4 + -0x42ce) = param_1._0_2_;
  *(undefined2 *)(unaff_A4 + -0x4346) = 10;
  *(undefined2 *)(unaff_A4 + -0x4348) = 0;
  uVar1 = FUN_00022ba4(0,0);
  *(undefined4 *)(unaff_A4 + -0x4344) = uVar1;
  uVar1 = FUN_00022c8e(*(undefined4 *)(unaff_A4 + -0x4344));
  *(undefined4 *)(unaff_A4 + -0x433c) = uVar1;
  *(int *)(unaff_A4 + -0x432a) = unaff_A4 + -0x4322;
  *(code **)(unaff_A4 + -0x4326) = FUN_0002075a;
  *(undefined1 *)(unaff_A4 + -0x432f) = 0x7f;
  FUN_00022dc4(unaff_A4 + -0x46e8,0,*(undefined4 *)(unaff_A4 + -0x433c),0);
  *(undefined2 *)(*(int *)(unaff_A4 + -0x433c) + 0x1c) = 9;
  *(int *)(*(int *)(unaff_A4 + -0x433c) + 0x28) = unaff_A4 + -0x4338;
  FUN_00022d50(*(undefined4 *)(unaff_A4 + -0x433c));
  uVar1 = FUN_00022ba4(0,0);
  *(undefined4 *)(unaff_A4 + -0x4340) = uVar1;
  uVar1 = FUN_00022cb6(*(undefined4 *)(unaff_A4 + -0x4340),0x20);
  *(undefined4 *)(unaff_A4 + -0x42d2) = uVar1;
  FUN_00022dc4(unaff_A4 + -0x46db,0xffffffff,*(undefined4 *)(unaff_A4 + -0x42d2),0);
  *(undefined4 *)(unaff_A4 + -0x3094) = *(undefined4 *)(*(int *)(unaff_A4 + -0x42d2) + 0x14);
  return;
}


// ==== thunk_FUN_0002067c @ 00023232 ====

void thunk_FUN_0002067c(void)

{
  int unaff_A4;
  
  if (*(int *)(unaff_A4 + -0x42d2) != 0) {
    FUN_00022b88(*(undefined4 *)(unaff_A4 + -0x42d2));
    FUN_00022cfa(*(undefined4 *)(unaff_A4 + -0x42d2));
    *(undefined4 *)(unaff_A4 + -0x42d2) = 0;
    FUN_00022c30(*(undefined4 *)(unaff_A4 + -0x4340));
    *(undefined4 *)(unaff_A4 + -0x4340) = 0;
    *(undefined2 *)(*(int *)(unaff_A4 + -0x433c) + 0x1c) = 10;
    *(int *)(*(int *)(unaff_A4 + -0x433c) + 0x28) = unaff_A4 + -0x4338;
    FUN_00022d50(*(undefined4 *)(unaff_A4 + -0x433c));
    FUN_00022b88(*(undefined4 *)(unaff_A4 + -0x433c));
    FUN_00022ca4(*(undefined4 *)(unaff_A4 + -0x433c));
    *(undefined4 *)(unaff_A4 + -0x433c) = 0;
    FUN_00022c30(*(undefined4 *)(unaff_A4 + -0x4344));
    *(undefined4 *)(unaff_A4 + -0x4344) = 0;
  }
  return;
}


// ==== thunk_FUN_000206ee @ 00023238 ====

void thunk_FUN_000206ee(void)

{
  undefined4 uVar1;
  
  uVar1 = FUN_000207e4();
  FUN_00020700(uVar1);
  return;
}


// ==== thunk_FUN_00020700 @ 0002323e ====

ushort thunk_FUN_00020700(undefined4 param_1)

{
  short sVar1;
  byte abStack_20 [2];
  undefined4 uStack_1e;
  undefined1 uStack_1a;
  undefined1 uStack_19;
  undefined2 uStack_18;
  undefined2 uStack_16;
  ushort uStack_6;
  
  uStack_6 = 0;
  uStack_1e = 0;
  uStack_1a = 1;
  uStack_19 = 0;
  uStack_18 = param_1._2_2_;
  uStack_16 = (undefined2)((uint)param_1 >> 0x10);
  sVar1 = FUN_00022f30(&uStack_1e,abStack_20,1,0);
  if (sVar1 == 1) {
    uStack_6 = (ushort)abStack_20[0];
  }
  return uStack_6;
}


// ==== thunk_FUN_0002075a @ 00023244 ====

void thunk_FUN_0002075a(void)

{
  ushort uVar1;
  ushort uVar2;
  short sVar3;
  int *in_A0;
  
  do {
    sVar3 = DAT_00026c06;
    uVar1 = *(ushort *)((int)in_A0 + 6);
    uVar2 = *(ushort *)(in_A0 + 2);
    if (*(char *)(in_A0 + 1) == '\x02') {
      if (uVar1 == 0x69) {
        DAT_00027ebe = CONCAT11(0xff,(undefined1)DAT_00027ebe);
      }
      if (uVar1 == 0xe9) {
        DAT_00027ebe = 0;
        goto LAB_0002078c;
      }
    }
    else {
LAB_0002078c:
      if (((*(char *)(in_A0 + 1) == '\x01') && ((uVar1 & 0x80) == 0)) &&
         ((DAT_00026c80 == 0 || ((DAT_00026c80 & uVar2) != 0)))) {
        if (DAT_00026c06 < DAT_00026c08) {
          (&DAT_00026be8)[DAT_00026c06] = (char)uVar1;
          *(ushort *)((int)&DAT_00026bf2 + (int)(short)(sVar3 * 2)) = uVar2;
          DAT_00026c06 = DAT_00026c06 + 1;
        }
        *(undefined2 *)(in_A0 + 1) = 0;
      }
    }
    in_A0 = (int *)*in_A0;
    if (in_A0 == (int *)0x0) {
      return;
    }
  } while( true );
}


// ==== thunk_FUN_000207d8 @ 0002324a ====

undefined4 thunk_FUN_000207d8(void)

{
  undefined4 uVar1;
  int unaff_A4;
  
  uVar1 = 0;
  if (*(short *)(unaff_A4 + -0x4348) != 0) {
    uVar1 = 0xffffffff;
  }
  return uVar1;
}


// ==== thunk_FUN_000207e4 @ 00023250 ====

undefined8 thunk_FUN_000207e4(void)

{
  ushort uVar1;
  byte bVar2;
  uint uVar3;
  short sVar4;
  undefined4 in_D1;
  short sVar5;
  int unaff_A4;
  undefined1 in_ZF;
  
  while( true ) {
    FUN_000207d8();
    if (!(bool)in_ZF) break;
    (**(code **)(unaff_A4 + -0x7bae))();
  }
  (**(code **)(unaff_A4 + -0x7bfc))();
  uVar1 = *(ushort *)(unaff_A4 + -0x435c);
  bVar2 = *(byte *)(unaff_A4 + -0x4366);
  uVar3 = CONCAT31((int3)(((uint)uVar1 << 0x10) >> 8),bVar2);
  *(short *)(unaff_A4 + -0x4348) = *(short *)(unaff_A4 + -0x4348) + -1;
  sVar4 = 0;
  sVar5 = 0;
  do {
    *(undefined1 *)(unaff_A4 + -0x4366 + (int)sVar4) =
         *(undefined1 *)(unaff_A4 + -0x4365 + (int)sVar4);
    *(undefined2 *)(unaff_A4 + -0x435c + (int)sVar5) =
         *(undefined2 *)(unaff_A4 + -0x435a + (int)sVar5);
    sVar4 = sVar4 + 1;
    sVar5 = sVar5 + 2;
  } while (sVar4 <= *(short *)(unaff_A4 + -0x4348));
  (**(code **)(unaff_A4 + -0x7bf6))();
  if (*(ushort *)(unaff_A4 + -0x42ce) != 0) {
    uVar3 = (uint)(~*(ushort *)(unaff_A4 + -0x42ce) & uVar1) << 0x10 | (uint)bVar2;
  }
  return CONCAT44(uVar3,in_D1);
}


// ==== thunk_FUN_00020848 @ 00023256 ====

void thunk_FUN_00020848(undefined4 param_1)

{
  FUN_00020874(param_1,0x10001);
  return;
}


// ==== thunk_FUN_0002085e @ 0002325c ====

void thunk_FUN_0002085e(undefined4 param_1)

{
  FUN_00020874(param_1,0x10003);
  return;
}


// ==== thunk_FUN_0002090a @ 00023262 ====

undefined4 thunk_FUN_0002090a(int param_1)

{
  undefined4 *puVar1;
  int unaff_A4;
  
  if (param_1 != 0) {
    if (param_1 == -1) {
      while (*(int *)(unaff_A4 + -0x46cc) != 0) {
        FUN_0002090a(*(int *)(unaff_A4 + -0x46cc) + 0xc);
      }
    }
    else {
      puVar1 = (undefined4 *)(param_1 + -0xc);
      if (puVar1 == *(undefined4 **)(unaff_A4 + -0x46cc)) {
        *(undefined4 *)(unaff_A4 + -0x46cc) = *(undefined4 *)(param_1 + -8);
      }
      if (puVar1 == *(undefined4 **)(param_1 + -8)) {
        *(undefined4 *)(unaff_A4 + -0x46cc) = 0;
      }
      *(undefined4 *)(*(int *)(param_1 + -8) + 8) = *(undefined4 *)(param_1 + -4);
      *(undefined4 *)(*(int *)(param_1 + -4) + 4) = *(undefined4 *)(param_1 + -8);
      thunk_FUN_00022d8a(puVar1,*puVar1);
    }
  }
  return 0;
}


// ==== thunk_FUN_00020aee @ 00023268 ====

void thunk_FUN_00020aee(void)

{
  int unaff_A4;
  
  (**(code **)(unaff_A4 + -0x7c92))();
  FUN_00020b0c();
                    /* WARNING: Could not recover jumptable at 0x00020b08. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(unaff_A4 + -0x7c8c))();
  return;
}


// ==== thunk_FUN_00020b0c @ 0002326e ====

undefined8 thunk_FUN_00020b0c(void)

{
  int iVar1;
  int iVar2;
  short sVar3;
  undefined2 uVar4;
  short sVar5;
  byte bVar6;
  byte bVar7;
  undefined4 in_D0;
  undefined4 in_D1;
  ushort uVar8;
  ushort uVar9;
  byte bVar10;
  int iVar11;
  int in_A0;
  int *piVar12;
  int unaff_A4;
  byte *pbVar13;
  int unaff_A6;
  undefined1 in_CF;
  
  FUN_000209bc();
  if (!(bool)in_CF) {
    bVar6 = *(byte *)(*(int *)(unaff_A4 + -0x40e4) + 0x18);
    iVar11 = *(int *)(unaff_A4 + -0x3078);
    iVar2 = *(int *)(unaff_A4 + -0x3074);
    sVar3 = *(short *)(unaff_A4 + -0x3066);
    uVar4 = *(undefined2 *)(unaff_A4 + -0x306e);
    sVar5 = *(short *)(unaff_A4 + -0x3070);
    uVar8 = *(ushort *)(unaff_A4 + -0x3060) << 0xc | *(ushort *)(unaff_A4 + -0x3060) >> 4;
    bVar10 = *(byte *)(unaff_A6 + 2);
    while ((bVar10 & 0x40) != 0) {
      bVar10 = *(byte *)(unaff_A6 + 2);
    }
    *(undefined2 *)(unaff_A6 + 0x44) = *(undefined2 *)(unaff_A4 + -0x305e);
    *(undefined2 *)(unaff_A6 + 0x46) = *(undefined2 *)(unaff_A4 + -0x305c);
    *(undefined2 *)(unaff_A6 + 0x42) = 0;
    uVar9 = 0xbca;
    if (iVar2 == 0) {
      uVar9 = 0x3ca;
      *(undefined2 *)(unaff_A6 + 0x74) = 0xffff;
      if (uVar8 == 0) {
        uVar9 = 0x1ca;
        *(undefined2 *)(unaff_A6 + 0x70) = 0xffff;
      }
    }
    uVar9 = uVar9 | uVar8;
    *(undefined2 *)(unaff_A6 + 100) = *(undefined2 *)(unaff_A4 + -0x3068);
    *(undefined2 *)(unaff_A6 + 0x62) = *(undefined2 *)(unaff_A4 + -0x306a);
    *(undefined2 *)(unaff_A6 + 0x60) = *(undefined2 *)(unaff_A4 + -0x306c);
    *(undefined2 *)(unaff_A6 + 0x66) = *(undefined2 *)(unaff_A4 + -0x306c);
    bVar10 = bVar6 & *(byte *)(in_A0 + 0xc);
    if (bVar10 != 0) {
      piVar12 = (int *)(*(int *)(unaff_A4 + -0x3eb0) + 8);
      *(ushort *)(unaff_A6 + 0x40) = uVar9;
      *(undefined2 *)(unaff_A6 + 0x72) = 0;
      do {
        bVar7 = bVar10 & 1;
        bVar10 = bVar10 >> 1;
        if (bVar7 != 0) {
          iVar1 = *piVar12;
          *(int *)(unaff_A6 + 0x50) = iVar2;
          *(int *)(unaff_A6 + 0x48) = sVar5 + iVar1;
          *(int *)(unaff_A6 + 0x54) = sVar5 + iVar1;
          *(undefined2 *)(unaff_A6 + 0x58) = uVar4;
          bVar7 = *(byte *)(unaff_A6 + 2);
          while ((bVar7 & 0x40) != 0) {
            bVar7 = *(byte *)(unaff_A6 + 2);
          }
        }
        piVar12 = piVar12 + 1;
      } while (bVar10 != 0);
    }
    bVar10 = bVar6 & *(byte *)(in_A0 + 0xd);
    if (bVar10 != 0) {
      piVar12 = (int *)(*(int *)(unaff_A4 + -0x3eb0) + 8);
      *(ushort *)(unaff_A6 + 0x40) = uVar9;
      *(undefined2 *)(unaff_A6 + 0x72) = 0xffff;
      do {
        bVar7 = bVar10 & 1;
        bVar10 = bVar10 >> 1;
        if (bVar7 != 0) {
          iVar1 = *piVar12;
          *(int *)(unaff_A6 + 0x50) = iVar2;
          *(int *)(unaff_A6 + 0x48) = sVar5 + iVar1;
          *(int *)(unaff_A6 + 0x54) = sVar5 + iVar1;
          *(undefined2 *)(unaff_A6 + 0x58) = uVar4;
          bVar7 = *(byte *)(unaff_A6 + 2);
          while ((bVar7 & 0x40) != 0) {
            bVar7 = *(byte *)(unaff_A6 + 2);
          }
        }
        piVar12 = piVar12 + 1;
      } while (bVar10 != 0);
    }
    *(ushort *)(unaff_A6 + 0x42) = uVar8;
    *(ushort *)(unaff_A6 + 0x40) = uVar9 | 0x400;
    pbVar13 = (byte *)(in_A0 + 0xe);
    while( true ) {
      if (*pbVar13 == 0) break;
      bVar10 = bVar6 & *pbVar13;
      if (bVar10 != 0) {
        piVar12 = (int *)(*(int *)(unaff_A4 + -0x3eb0) + 8);
        do {
          bVar7 = bVar10 & 1;
          bVar10 = bVar10 >> 1;
          if (bVar7 != 0) {
            iVar1 = *piVar12;
            *(int *)(unaff_A6 + 0x50) = iVar2;
            *(int *)(unaff_A6 + 0x4c) = iVar11;
            *(int *)(unaff_A6 + 0x48) = sVar5 + iVar1;
            *(int *)(unaff_A6 + 0x54) = sVar5 + iVar1;
            *(undefined2 *)(unaff_A6 + 0x58) = uVar4;
            bVar7 = *(byte *)(unaff_A6 + 2);
            while ((bVar7 & 0x40) != 0) {
              bVar7 = *(byte *)(unaff_A6 + 2);
            }
          }
          piVar12 = piVar12 + 1;
        } while (bVar10 != 0);
      }
      iVar11 = sVar3 + iVar11;
      pbVar13 = pbVar13 + 1;
    }
  }
  return CONCAT44(in_D0,in_D1);
}


// ==== thunk_FUN_00020cc4 @ 00023274 ====

void thunk_FUN_00020cc4(void)

{
  int unaff_A4;
  
  (**(code **)(unaff_A4 + -0x7c92))();
  FUN_00020ce2();
                    /* WARNING: Could not recover jumptable at 0x00020cde. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(unaff_A4 + -0x7c8c))();
  return;
}


// ==== thunk_FUN_00020ce2 @ 0002327a ====

undefined4 thunk_FUN_00020ce2(void)

{
  int iVar1;
  int iVar2;
  short sVar3;
  undefined2 uVar4;
  char cVar5;
  byte bVar6;
  byte bVar7;
  uint uVar8;
  undefined4 uVar9;
  ushort uVar10;
  ushort uVar11;
  undefined4 in_D0;
  short sVar12;
  byte bVar13;
  int iVar14;
  uint *puVar15;
  ushort *in_A0;
  ushort *puVar16;
  uint *puVar17;
  int in_A1;
  uint *puVar18;
  int *piVar19;
  uint *puVar20;
  int unaff_A4;
  uint *puVar21;
  uint *puVar22;
  int unaff_A6;
  bool bVar23;
  
  bVar23 = false;
  if (in_A1 != 0) {
    FUN_000209bc();
    if (!bVar23) {
      bVar6 = *(byte *)(*(int *)(unaff_A4 + -0x40e4) + 0x18);
      iVar14 = *(int *)(unaff_A4 + -0x3078);
      iVar2 = *(int *)(unaff_A4 + -0x3074);
      sVar3 = *(short *)(unaff_A4 + -0x3066);
      uVar4 = *(undefined2 *)(unaff_A4 + -0x306e);
      sVar12 = *(short *)(unaff_A4 + -0x3070);
      uVar10 = *(ushort *)(unaff_A4 + -0x3060) << 0xc | *(ushort *)(unaff_A4 + -0x3060) >> 4;
      bVar13 = *(byte *)(unaff_A6 + 2);
      while ((bVar13 & 0x40) != 0) {
        bVar13 = *(byte *)(unaff_A6 + 2);
      }
      *(undefined2 *)(unaff_A6 + 0x44) = *(undefined2 *)(unaff_A4 + -0x305e);
      *(undefined2 *)(unaff_A6 + 0x46) = *(undefined2 *)(unaff_A4 + -0x305c);
      *(undefined2 *)(unaff_A6 + 0x42) = 0;
      uVar11 = 0xbca;
      if (iVar2 == 0) {
        uVar11 = 0x3ca;
        *(undefined2 *)(unaff_A6 + 0x74) = 0xffff;
        if (uVar10 == 0) {
          uVar11 = 0x1ca;
          *(undefined2 *)(unaff_A6 + 0x70) = 0xffff;
        }
      }
      uVar11 = uVar11 | uVar10;
      *(undefined2 *)(unaff_A6 + 100) = *(undefined2 *)(unaff_A4 + -0x3068);
      *(undefined2 *)(unaff_A6 + 0x62) = *(undefined2 *)(unaff_A4 + -0x306a);
      *(undefined2 *)(unaff_A6 + 0x60) = *(undefined2 *)(unaff_A4 + -0x306c);
      *(undefined2 *)(unaff_A6 + 0x66) = *(undefined2 *)(unaff_A4 + -0x306c);
      bVar13 = bVar6 & *(byte *)(in_A0 + 6);
      if (bVar13 != 0) {
        piVar19 = (int *)(*(int *)(unaff_A4 + -0x3eb0) + 8);
        *(ushort *)(unaff_A6 + 0x40) = uVar11;
        *(undefined2 *)(unaff_A6 + 0x72) = 0;
        do {
          bVar7 = bVar13 & 1;
          bVar13 = bVar13 >> 1;
          if (bVar7 != 0) {
            iVar1 = *piVar19;
            *(int *)(unaff_A6 + 0x50) = iVar2;
            *(int *)(unaff_A6 + 0x48) = sVar12 + iVar1;
            *(int *)(unaff_A6 + 0x54) = sVar12 + iVar1;
            *(undefined2 *)(unaff_A6 + 0x58) = uVar4;
            bVar7 = *(byte *)(unaff_A6 + 2);
            while ((bVar7 & 0x40) != 0) {
              bVar7 = *(byte *)(unaff_A6 + 2);
            }
          }
          piVar19 = piVar19 + 1;
        } while (bVar13 != 0);
      }
      bVar13 = bVar6 & *(byte *)((int)in_A0 + 0xd);
      if (bVar13 != 0) {
        piVar19 = (int *)(*(int *)(unaff_A4 + -0x3eb0) + 8);
        *(ushort *)(unaff_A6 + 0x40) = uVar11;
        *(undefined2 *)(unaff_A6 + 0x72) = 0xffff;
        do {
          bVar7 = bVar13 & 1;
          bVar13 = bVar13 >> 1;
          if (bVar7 != 0) {
            iVar1 = *piVar19;
            *(int *)(unaff_A6 + 0x50) = iVar2;
            *(int *)(unaff_A6 + 0x48) = sVar12 + iVar1;
            *(int *)(unaff_A6 + 0x54) = sVar12 + iVar1;
            *(undefined2 *)(unaff_A6 + 0x58) = uVar4;
            bVar7 = *(byte *)(unaff_A6 + 2);
            while ((bVar7 & 0x40) != 0) {
              bVar7 = *(byte *)(unaff_A6 + 2);
            }
          }
          piVar19 = piVar19 + 1;
        } while (bVar13 != 0);
      }
      *(ushort *)(unaff_A6 + 0x42) = uVar10;
      *(ushort *)(unaff_A6 + 0x40) = uVar11 | 0x400;
      puVar16 = in_A0 + 7;
      while( true ) {
        if (*(byte *)puVar16 == 0) break;
        bVar13 = bVar6 & *(byte *)puVar16;
        if (bVar13 != 0) {
          piVar19 = (int *)(*(int *)(unaff_A4 + -0x3eb0) + 8);
          do {
            bVar7 = bVar13 & 1;
            bVar13 = bVar13 >> 1;
            if (bVar7 != 0) {
              iVar1 = *piVar19;
              *(int *)(unaff_A6 + 0x50) = iVar2;
              *(int *)(unaff_A6 + 0x4c) = iVar14;
              *(int *)(unaff_A6 + 0x48) = sVar12 + iVar1;
              *(int *)(unaff_A6 + 0x54) = sVar12 + iVar1;
              *(undefined2 *)(unaff_A6 + 0x58) = uVar4;
              bVar7 = *(byte *)(unaff_A6 + 2);
              while ((bVar7 & 0x40) != 0) {
                bVar7 = *(byte *)(unaff_A6 + 2);
              }
            }
            piVar19 = piVar19 + 1;
          } while (bVar13 != 0);
        }
        iVar14 = sVar3 + iVar14;
        puVar16 = (ushort *)((int)puVar16 + 1);
      }
    }
    return in_D0;
  }
  uVar8 = (uint)*in_A0 * (uint)in_A0[1];
  if (*(uint *)(unaff_A4 + -0x3bc4) <= uVar8 && uVar8 - *(uint *)(unaff_A4 + -0x3bc4) != 0) {
    uVar9 = FUN_00020b0c();
    return uVar9;
  }
  puVar16 = in_A0 + 7;
  sVar3 = -1;
  do {
    sVar12 = sVar3;
    cVar5 = *(char *)puVar16;
    puVar16 = (ushort *)((int)puVar16 + 1);
    sVar3 = sVar12 + 1;
  } while (cVar5 != '\0');
  if ((short)(sVar12 + 1) != 0 && sVar12 != 0) {
    puVar17 = *(uint **)(unaff_A4 + -0x3bc8);
    puVar15 = (uint *)(in_A0 + 10);
    uVar11 = (ushort)uVar8;
    puVar18 = (uint *)((int)puVar15 + (int)(short)uVar11);
    puVar20 = (uint *)((int)puVar18 + (int)(short)uVar11);
    puVar21 = (uint *)((int)puVar20 + (int)(short)uVar11);
    puVar22 = (uint *)((int)puVar21 + (int)(short)uVar11);
    uVar10 = uVar11 >> 1;
    if (sVar12 == 1) {
      uVar11 = uVar11 >> 2;
      if ((uVar10 & 1) != 0) {
        *(ushort *)puVar17 = *(ushort *)puVar18 | *(ushort *)puVar15;
        puVar15 = (uint *)(in_A0 + 0xb);
        puVar17 = (uint *)((int)puVar17 + 2);
        puVar18 = (uint *)((int)puVar18 + 2);
      }
      while (uVar11 = uVar11 - 1, uVar11 != 0xffff) {
        *puVar17 = *puVar18 | *puVar15;
        puVar15 = puVar15 + 1;
        puVar17 = puVar17 + 1;
        puVar18 = puVar18 + 1;
      }
    }
    else if (sVar12 == 2) {
      uVar11 = uVar11 >> 2;
      if ((uVar10 & 1) != 0) {
        *(ushort *)puVar17 = *(ushort *)puVar20 | *(ushort *)puVar18 | *(ushort *)puVar15;
        puVar15 = (uint *)(in_A0 + 0xb);
        puVar17 = (uint *)((int)puVar17 + 2);
        puVar18 = (uint *)((int)puVar18 + 2);
        puVar20 = (uint *)((int)puVar20 + 2);
      }
      while (uVar11 = uVar11 - 1, uVar11 != 0xffff) {
        *puVar17 = *puVar20 | *puVar18 | *puVar15;
        puVar15 = puVar15 + 1;
        puVar17 = puVar17 + 1;
        puVar18 = puVar18 + 1;
        puVar20 = puVar20 + 1;
      }
    }
    else if (sVar12 == 3) {
      uVar11 = uVar11 >> 2;
      if ((uVar10 & 1) != 0) {
        *(ushort *)puVar17 =
             *(ushort *)puVar21 | *(ushort *)puVar20 | *(ushort *)puVar18 | *(ushort *)puVar15;
        puVar15 = (uint *)(in_A0 + 0xb);
        puVar17 = (uint *)((int)puVar17 + 2);
        puVar18 = (uint *)((int)puVar18 + 2);
        puVar20 = (uint *)((int)puVar20 + 2);
        puVar21 = (uint *)((int)puVar21 + 2);
      }
      while (uVar11 = uVar11 - 1, uVar11 != 0xffff) {
        *puVar17 = *puVar21 | *puVar20 | *puVar18 | *puVar15;
        puVar15 = puVar15 + 1;
        puVar17 = puVar17 + 1;
        puVar18 = puVar18 + 1;
        puVar20 = puVar20 + 1;
        puVar21 = puVar21 + 1;
      }
    }
    else {
      uVar11 = uVar11 >> 2;
      if ((uVar10 & 1) != 0) {
        *(ushort *)puVar17 =
             *(ushort *)puVar22 |
             *(ushort *)puVar21 | *(ushort *)puVar20 | *(ushort *)puVar18 | *(ushort *)puVar15;
        puVar15 = (uint *)(in_A0 + 0xb);
        puVar17 = (uint *)((int)puVar17 + 2);
        puVar18 = (uint *)((int)puVar18 + 2);
        puVar20 = (uint *)((int)puVar20 + 2);
        puVar21 = (uint *)((int)puVar21 + 2);
        puVar22 = (uint *)((int)puVar22 + 2);
      }
      while (uVar11 = uVar11 - 1, uVar11 != 0xffff) {
        *puVar17 = *puVar22 | *puVar21 | *puVar20 | *puVar18 | *puVar15;
        puVar15 = puVar15 + 1;
        puVar17 = puVar17 + 1;
        puVar18 = puVar18 + 1;
        puVar20 = puVar20 + 1;
        puVar21 = puVar21 + 1;
        puVar22 = puVar22 + 1;
      }
    }
  }
  uVar9 = FUN_00020b0c();
  return uVar9;
}


// ==== thunk_FUN_00020e0a @ 00023280 ====

void thunk_FUN_00020e0a(void)

{
  int unaff_A4;
  
  (**(code **)(unaff_A4 + -0x7c92))();
  FUN_00020e24();
                    /* WARNING: Could not recover jumptable at 0x00020e20. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(unaff_A4 + -0x7c8c))();
  return;
}


// ==== thunk_FUN_00020e24 @ 00023286 ====

undefined8 thunk_FUN_00020e24(void)

{
  short sVar1;
  undefined2 uVar2;
  short sVar3;
  short sVar4;
  byte bVar5;
  byte bVar6;
  undefined4 in_D0;
  undefined4 in_D1;
  ushort uVar7;
  byte bVar8;
  int iVar9;
  int in_A0;
  int iVar10;
  int *piVar11;
  int unaff_A4;
  byte *pbVar12;
  int unaff_A6;
  undefined1 in_CF;
  
  FUN_000209bc();
  if (!(bool)in_CF) {
    bVar5 = *(byte *)(*(int *)(unaff_A4 + -0x40e4) + 0x18);
    iVar9 = *(int *)(unaff_A4 + -0x3078);
    sVar1 = *(short *)(unaff_A4 + -0x3066);
    uVar2 = *(undefined2 *)(unaff_A4 + -0x306e);
    sVar3 = *(short *)(unaff_A4 + -0x3070);
    uVar7 = *(ushort *)(unaff_A4 + -0x3060) << 0xc | *(ushort *)(unaff_A4 + -0x3060) >> 4;
    bVar8 = *(byte *)(unaff_A6 + 2);
    while ((bVar8 & 0x40) != 0) {
      bVar8 = *(byte *)(unaff_A6 + 2);
    }
    *(undefined2 *)(unaff_A6 + 0x44) = *(undefined2 *)(unaff_A4 + -0x305e);
    sVar4 = *(short *)(unaff_A4 + -0x305a);
    *(short *)(unaff_A6 + 0x46) = sVar4;
    if (sVar4 == 0) {
      *(undefined2 *)(unaff_A6 + 0x46) = *(undefined2 *)(unaff_A4 + -0x305c);
    }
    *(undefined2 *)(unaff_A6 + 0x42) = 0;
    *(undefined2 *)(unaff_A6 + 0x74) = 0xffff;
    *(undefined2 *)(unaff_A6 + 0x62) = *(undefined2 *)(unaff_A4 + -0x306a);
    *(undefined2 *)(unaff_A6 + 0x60) = *(undefined2 *)(unaff_A4 + -0x306c);
    *(undefined2 *)(unaff_A6 + 0x66) = *(undefined2 *)(unaff_A4 + -0x306c);
    *(int *)(unaff_A6 + 0x4c) = iVar9;
    bVar8 = bVar5 & *(byte *)(in_A0 + 0xd);
    if (bVar8 != 0) {
      piVar11 = (int *)(*(int *)(unaff_A4 + -0x3eb0) + 8);
      *(ushort *)(unaff_A6 + 0x40) = uVar7 | 0x36a;
      *(undefined2 *)(unaff_A6 + 0x72) = 0xffff;
      do {
        bVar6 = bVar8 & 1;
        bVar8 = bVar8 >> 1;
        if (bVar6 != 0) {
          iVar10 = (int)sVar3 + *piVar11;
          *(int *)(unaff_A6 + 0x48) = iVar10;
          *(int *)(unaff_A6 + 0x54) = iVar10;
          *(undefined2 *)(unaff_A6 + 0x58) = uVar2;
          bVar6 = *(byte *)(unaff_A6 + 2);
          while ((bVar6 & 0x40) != 0) {
            bVar6 = *(byte *)(unaff_A6 + 2);
          }
        }
        piVar11 = piVar11 + 1;
      } while (bVar8 != 0);
    }
    *(ushort *)(unaff_A6 + 0x42) = uVar7;
    *(ushort *)(unaff_A6 + 0x40) = uVar7 | 0x76a;
    pbVar12 = (byte *)(in_A0 + 0xe);
    while( true ) {
      if (*pbVar12 == 0) break;
      bVar8 = bVar5 & *pbVar12;
      if (bVar8 != 0) {
        piVar11 = (int *)(*(int *)(unaff_A4 + -0x3eb0) + 8);
        do {
          bVar6 = bVar8 & 1;
          bVar8 = bVar8 >> 1;
          if (bVar6 != 0) {
            iVar10 = (int)sVar3 + *piVar11;
            *(int *)(unaff_A6 + 0x4c) = iVar9;
            *(int *)(unaff_A6 + 0x48) = iVar10;
            *(int *)(unaff_A6 + 0x54) = iVar10;
            *(undefined2 *)(unaff_A6 + 0x58) = uVar2;
            bVar6 = *(byte *)(unaff_A6 + 2);
            while ((bVar6 & 0x40) != 0) {
              bVar6 = *(byte *)(unaff_A6 + 2);
            }
          }
          piVar11 = piVar11 + 1;
        } while (bVar8 != 0);
      }
      iVar9 = sVar1 + iVar9;
      pbVar12 = pbVar12 + 1;
    }
  }
  return CONCAT44(in_D0,in_D1);
}


// ==== thunk_FUN_00020ff2 @ 0002328c ====

void thunk_FUN_00020ff2(void)

{
  int unaff_A4;
  
  (**(code **)(unaff_A4 + -0x7c92))();
  FUN_00021010();
  (**(code **)(unaff_A4 + -0x7c8c))();
  return;
}


// ==== thunk_FUN_00021010 @ 00023292 ====

undefined8 thunk_FUN_00021010(void)

{
  short *psVar1;
  short sVar2;
  byte bVar3;
  short sVar4;
  short sVar5;
  short sVar6;
  uint uVar7;
  ushort uVar8;
  uint in_D0;
  uint uVar9;
  short sVar10;
  uint in_D1;
  undefined2 uVar11;
  ushort unaff_D2w;
  short unaff_D3w;
  uint unaff_D4;
  ushort uVar12;
  ushort uVar13;
  undefined3 uVar14;
  undefined4 unaff_D7;
  int iVar15;
  int *piVar16;
  int *piVar17;
  int unaff_A4;
  int unaff_A6;
  
  uVar7 = in_D0;
  if ((short)in_D0 < *(short *)(unaff_A4 + -0x469e)) {
    uVar7 = (uint)*(ushort *)(unaff_A4 + -0x469e);
  }
  if (*(short *)(unaff_A4 + -0x469c) <= (short)unaff_D2w) {
    unaff_D2w = *(short *)(unaff_A4 + -0x469c) - 1;
  }
  uVar9 = in_D1;
  if ((short)in_D1 < *(short *)(unaff_A4 + -0x46a2)) {
    uVar9 = (uint)*(ushort *)(unaff_A4 + -0x46a2);
  }
  if (*(short *)(unaff_A4 + -0x46a0) <= unaff_D3w) {
    unaff_D3w = *(short *)(unaff_A4 + -0x46a0) + -1;
  }
  uVar8 = (ushort)uVar7;
  sVar10 = (short)uVar9;
  uVar14 = (undefined3)((uint)unaff_D7 >> 8);
  if (((uVar8 | unaff_D2w + 1) & 0xf) != 0) {
    sVar4 = (unaff_D3w - sVar10) + 1;
    if (sVar4 != 0 && -2 < (short)(unaff_D3w - sVar10)) {
      psVar1 = *(short **)(unaff_A4 + -0x3eb0);
      sVar2 = *psVar1;
      uVar13 = (short)uVar8 >> 3 & 0xfffe;
      sVar5 = ((short)unaff_D2w >> 3 & 0xfffeU) + 2;
      bVar3 = *(byte *)(unaff_A6 + 2);
      while ((bVar3 & 0x40) != 0) {
        bVar3 = *(byte *)(unaff_A6 + 2);
      }
      *(undefined2 *)(unaff_A6 + 0x44) =
           *(undefined2 *)(unaff_A4 + -0x4696 + (int)(short)((uVar8 & 0xf) * 2));
      *(undefined2 *)(unaff_A6 + 0x46) =
           *(undefined2 *)(unaff_A4 + -0x4672 + (int)(short)((unaff_D2w & 0xf) * 2));
      uVar8 = sVar5 - uVar13;
      if (uVar8 != 0 && (short)uVar13 <= sVar5) {
        sVar5 = *psVar1;
        *(ushort *)(unaff_A6 + 0x62) = sVar5 - uVar8;
        *(ushort *)(unaff_A6 + 0x66) = sVar5 - uVar8;
        *(undefined2 *)(unaff_A6 + 0x74) = 0xffff;
        *(undefined2 *)(unaff_A6 + 0x42) = 0;
        uVar12 = (ushort)*(byte *)((int)psVar1 + 5);
        uVar7 = CONCAT31(uVar14,*(undefined1 *)(*(int *)(unaff_A4 + -0x40e4) + 0x18));
        piVar17 = (int *)(psVar1 + 4);
        while (uVar12 = uVar12 - 1, uVar12 != 0xffff) {
          piVar16 = piVar17 + 1;
          iVar15 = *piVar17;
          uVar11 = 0x50c;
          uVar9 = unaff_D4 & 1;
          unaff_D4 = unaff_D4 >> 1 & 0x7fff;
          if (uVar9 != 0) {
            uVar11 = 0x5fc;
          }
          uVar9 = uVar7 & 1;
          uVar7 = uVar7 >> 1 & 0x7fff;
          piVar17 = piVar16;
          if (uVar9 != 0) {
            iVar15 = (short)(uVar13 + sVar10 * sVar2) + iVar15;
            bVar3 = *(byte *)(unaff_A6 + 2);
            while ((bVar3 & 0x40) != 0) {
              bVar3 = *(byte *)(unaff_A6 + 2);
            }
            *(int *)(unaff_A6 + 0x4c) = iVar15;
            *(int *)(unaff_A6 + 0x54) = iVar15;
            *(undefined2 *)(unaff_A6 + 0x40) = uVar11;
            *(ushort *)(unaff_A6 + 0x58) = uVar8 >> 1 | sVar4 * 0x40;
          }
        }
      }
    }
    return CONCAT44(in_D0,in_D1);
  }
  sVar4 = (unaff_D3w - sVar10) + 1;
  if (sVar4 != 0 && -2 < (short)(unaff_D3w - sVar10)) {
    psVar1 = *(short **)(unaff_A4 + -0x3eb0);
    sVar2 = *psVar1;
    sVar5 = (short)(uVar8 + 0xf & 0xfff0) >> 3;
    sVar6 = (short)(unaff_D2w + 1 & 0xfff0) >> 3;
    bVar3 = *(byte *)(unaff_A6 + 2);
    while ((bVar3 & 0x40) != 0) {
      bVar3 = *(byte *)(unaff_A6 + 2);
    }
    uVar8 = sVar6 - sVar5;
    if (uVar8 != 0 && sVar5 <= sVar6) {
      *(ushort *)(unaff_A6 + 0x66) = *psVar1 - uVar8;
      *(undefined2 *)(unaff_A6 + 0x42) = 0;
      uVar13 = (ushort)*(byte *)((int)psVar1 + 5);
      uVar7 = CONCAT31(uVar14,*(undefined1 *)(*(int *)(unaff_A4 + -0x40e4) + 0x18));
      piVar17 = (int *)(psVar1 + 4);
      while (uVar13 = uVar13 - 1, uVar13 != 0xffff) {
        piVar16 = piVar17 + 1;
        iVar15 = *piVar17;
        uVar11 = 0x100;
        uVar9 = unaff_D4 & 1;
        unaff_D4 = unaff_D4 >> 1 & 0x7fff;
        if (uVar9 != 0) {
          uVar11 = 0x1ff;
        }
        uVar9 = uVar7 & 1;
        uVar7 = uVar7 >> 1 & 0x7fff;
        piVar17 = piVar16;
        if (uVar9 != 0) {
          bVar3 = *(byte *)(unaff_A6 + 2);
          while ((bVar3 & 0x40) != 0) {
            bVar3 = *(byte *)(unaff_A6 + 2);
          }
          *(int *)(unaff_A6 + 0x54) = (short)(sVar5 + sVar10 * sVar2) + iVar15;
          *(undefined2 *)(unaff_A6 + 0x40) = uVar11;
          *(ushort *)(unaff_A6 + 0x58) = uVar8 >> 1 | sVar4 * 0x40;
        }
      }
    }
  }
  return CONCAT44(in_D0,in_D1);
}


// ==== thunk_FUN_00021120 @ 00023298 ====

undefined8 thunk_FUN_00021120(void)

{
  undefined4 in_D0;
  undefined4 in_D1;
  int unaff_A4;
  
  (**(code **)(unaff_A4 + -0x7c92))();
  FUN_0002113e();
  (**(code **)(unaff_A4 + -0x7c8c))();
  return CONCAT44(in_D0,in_D1);
}


// ==== thunk_FUN_0002113e @ 0002329e ====

undefined8 thunk_FUN_0002113e(void)

{
  int iVar1;
  short *psVar2;
  byte bVar3;
  short sVar4;
  short sVar5;
  ushort uVar6;
  short sVar7;
  short sVar8;
  uint uVar9;
  uint uVar10;
  uint in_D0;
  uint uVar11;
  uint in_D1;
  undefined2 uVar12;
  short unaff_D2w;
  short unaff_D3w;
  uint unaff_D4;
  ushort uVar13;
  undefined4 unaff_D7;
  int *piVar14;
  int *piVar15;
  int unaff_A4;
  int unaff_A6;
  
  uVar10 = in_D0;
  if ((short)in_D0 < *(short *)(unaff_A4 + -0x469e)) {
    uVar10 = (uint)*(ushort *)(unaff_A4 + -0x469e);
  }
  if (*(short *)(unaff_A4 + -0x469c) <= unaff_D2w) {
    unaff_D2w = *(short *)(unaff_A4 + -0x469c) + -1;
  }
  uVar11 = in_D1;
  if ((short)in_D1 < *(short *)(unaff_A4 + -0x46a2)) {
    uVar11 = (uint)*(ushort *)(unaff_A4 + -0x46a2);
  }
  if (*(short *)(unaff_A4 + -0x46a0) <= unaff_D3w) {
    unaff_D3w = *(short *)(unaff_A4 + -0x46a0) + -1;
  }
  sVar5 = unaff_D3w - (short)uVar11;
  sVar4 = sVar5 + 1;
  if (sVar4 != 0 && -2 < sVar5) {
    psVar2 = *(short **)(unaff_A4 + -0x3eb0);
    sVar5 = *psVar2;
    sVar7 = (short)((short)uVar10 + 0xfU & 0xfff0) >> 3;
    sVar8 = (short)(unaff_D2w + 1U & 0xfff0) >> 3;
    bVar3 = *(byte *)(unaff_A6 + 2);
    while ((bVar3 & 0x40) != 0) {
      bVar3 = *(byte *)(unaff_A6 + 2);
    }
    uVar6 = sVar8 - sVar7;
    if (uVar6 != 0 && sVar7 <= sVar8) {
      *(ushort *)(unaff_A6 + 0x66) = *psVar2 - uVar6;
      *(undefined2 *)(unaff_A6 + 0x42) = 0;
      uVar13 = (ushort)*(byte *)((int)psVar2 + 5);
      uVar10 = CONCAT31((int3)((uint)unaff_D7 >> 8),
                        *(undefined1 *)(*(int *)(unaff_A4 + -0x40e4) + 0x18));
      piVar15 = (int *)(psVar2 + 4);
      while (uVar13 = uVar13 - 1, uVar13 != 0xffff) {
        piVar14 = piVar15 + 1;
        iVar1 = *piVar15;
        uVar12 = 0x100;
        uVar9 = unaff_D4 & 1;
        unaff_D4 = unaff_D4 >> 1 & 0x7fff;
        if (uVar9 != 0) {
          uVar12 = 0x1ff;
        }
        uVar9 = uVar10 & 1;
        uVar10 = uVar10 >> 1 & 0x7fff;
        piVar15 = piVar14;
        if (uVar9 != 0) {
          bVar3 = *(byte *)(unaff_A6 + 2);
          while ((bVar3 & 0x40) != 0) {
            bVar3 = *(byte *)(unaff_A6 + 2);
          }
          *(int *)(unaff_A6 + 0x54) = (short)(sVar7 + (short)uVar11 * sVar5) + iVar1;
          *(undefined2 *)(unaff_A6 + 0x40) = uVar12;
          *(ushort *)(unaff_A6 + 0x58) = uVar6 >> 1 | sVar4 * 0x40;
        }
      }
    }
  }
  return CONCAT44(in_D0,in_D1);
}


// ==== thunk_FUN_00021246 @ 000232a4 ====

undefined4 thunk_FUN_00021246(int param_1)

{
  int iVar1;
  ushort uVar2;
  undefined4 in_D0;
  undefined4 *puVar3;
  undefined4 *puVar4;
  int unaff_A4;
  
  *(int *)(unaff_A4 + -0x40e4) = param_1;
  iVar1 = *(int *)(param_1 + 4);
  *(int *)(unaff_A4 + -0x3eb0) = iVar1;
  *(byte *)(param_1 + 0x18) = 0xff >> ((byte)(8 - *(char *)(iVar1 + 5)) & 0x3f);
  uVar2 = (ushort)*(byte *)(iVar1 + 5);
  puVar3 = (undefined4 *)(unaff_A4 + -0x46c2);
  puVar4 = (undefined4 *)(iVar1 + 8);
  while (uVar2 = uVar2 - 1, uVar2 != 0xffff) {
    *puVar3 = *puVar4;
    puVar3 = puVar3 + 1;
    puVar4 = puVar4 + 1;
  }
  return in_D0;
}


// ==== thunk_FUN_0002124a @ 000232aa ====

undefined4 thunk_FUN_0002124a(void)

{
  int iVar1;
  ushort uVar2;
  undefined4 in_D0;
  undefined4 *puVar3;
  int in_A0;
  undefined4 *puVar4;
  int unaff_A4;
  
  *(int *)(unaff_A4 + -0x40e4) = in_A0;
  iVar1 = *(int *)(in_A0 + 4);
  *(int *)(unaff_A4 + -0x3eb0) = iVar1;
  *(byte *)(in_A0 + 0x18) = 0xff >> ((byte)(8 - *(char *)(iVar1 + 5)) & 0x3f);
  uVar2 = (ushort)*(byte *)(iVar1 + 5);
  puVar3 = (undefined4 *)(unaff_A4 + -0x46c2);
  puVar4 = (undefined4 *)(iVar1 + 8);
  while (uVar2 = uVar2 - 1, uVar2 != 0xffff) {
    *puVar3 = *puVar4;
    puVar3 = puVar3 + 1;
    puVar4 = puVar4 + 1;
  }
  return in_D0;
}


// ==== thunk_FUN_00021280 @ 000232b0 ====

undefined8 thunk_FUN_00021280(void)

{
  undefined4 in_D0;
  undefined4 in_D1;
  
  FUN_0002129c();
  return CONCAT44(in_D0,in_D1);
}


// ==== thunk_FUN_0002129c @ 000232b6 ====

void thunk_FUN_0002129c(void)

{
  undefined2 in_D0w;
  undefined2 in_D1w;
  undefined2 unaff_D2w;
  undefined2 unaff_D3w;
  int unaff_A4;
  
  *(undefined2 *)(unaff_A4 + -0x46a2) = in_D0w;
  *(undefined2 *)(unaff_A4 + -0x46a0) = in_D1w;
  *(undefined2 *)(unaff_A4 + -0x469e) = unaff_D2w;
  *(undefined2 *)(unaff_A4 + -0x469c) = unaff_D3w;
  *(ushort *)(unaff_A4 + -0x469e) = *(ushort *)(unaff_A4 + -0x469e) & 0xfff0;
  *(ushort *)(unaff_A4 + -0x469c) = *(ushort *)(unaff_A4 + -0x469c) & 0xfff0;
  *(undefined2 *)(unaff_A4 + -0x4698) = *(undefined2 *)(unaff_A4 + -0x469c);
  *(short *)(unaff_A4 + -0x4698) = *(short *)(unaff_A4 + -0x4698) + -1;
  *(undefined2 *)(unaff_A4 + -0x469a) = *(undefined2 *)(unaff_A4 + -0x46a0);
  *(short *)(unaff_A4 + -0x469a) = *(short *)(unaff_A4 + -0x469a) + -1;
  return;
}


// ==== thunk_FUN_000212ce @ 000232bc ====

void thunk_FUN_000212ce(void)

{
  FUN_00022e8a();
  return;
}


// ==== thunk_FUN_000212d4 @ 000232c2 ====

void thunk_FUN_000212d4(void)

{
  do {
  } while ((DAT_00dff002 & 0x40) != 0);
  FUN_00022e40();
  return;
}


// ==== thunk_FUN_00021318 @ 000232c8 ====

undefined8 thunk_FUN_00021318(void)

{
  ushort *puVar1;
  byte bVar2;
  short sVar3;
  short sVar4;
  ushort uVar5;
  uint uVar6;
  uint in_D0;
  uint uVar7;
  uint in_D1;
  ushort uVar8;
  ushort unaff_D2w;
  ushort unaff_D3w;
  ushort uVar10;
  int iVar9;
  uint unaff_D4;
  ushort uVar11;
  ushort uVar12;
  ushort uVar13;
  uint uVar14;
  ushort *puVar15;
  ushort *puVar16;
  int iVar17;
  int unaff_A4;
  int unaff_A6;
  undefined4 uStack_34;
  
  *(undefined2 *)(unaff_A4 + -0x469a) = *(undefined2 *)(unaff_A4 + -0x46a0);
  *(undefined2 *)(unaff_A4 + -0x4698) = *(undefined2 *)(unaff_A4 + -0x469c);
  *(short *)(unaff_A4 + -0x469a) = *(short *)(unaff_A4 + -0x469a) + -1;
  *(short *)(unaff_A4 + -0x4698) = *(short *)(unaff_A4 + -0x4698) + -1;
  uVar14 = unaff_D4 & 0xffff;
  uVar10 = 10;
  if ((*(short *)(unaff_A4 + -0x469e) <= (short)unaff_D2w) &&
     (uVar10 = 2, *(short *)(unaff_A4 + -0x4698) < (short)unaff_D2w)) {
    uVar10 = 6;
  }
  if ((*(short *)(unaff_A4 + -0x46a2) <= (short)unaff_D3w) &&
     (uVar10 = uVar10 & 0xfffd, *(short *)(unaff_A4 + -0x469a) < (short)unaff_D3w)) {
    uVar10 = uVar10 | 1;
  }
  uVar11 = 10;
  if ((*(short *)(unaff_A4 + -0x469e) <= (short)in_D0) &&
     (uVar11 = 2, *(short *)(unaff_A4 + -0x4698) < (short)in_D0)) {
    uVar11 = 6;
  }
  if ((*(short *)(unaff_A4 + -0x46a2) <= (short)in_D1) &&
     (uVar11 = uVar11 & 0xfffd, *(short *)(unaff_A4 + -0x469a) < (short)in_D1)) {
    uVar11 = uVar11 | 1;
  }
  uStack_34 = CONCAT22(uVar11,uVar10);
  uVar6 = in_D0;
  uVar7 = in_D1;
  while( true ) {
    uVar10 = (ushort)uVar6;
    uVar11 = (ushort)uVar7;
    if (uStack_34._2_2_ == 0 && uStack_34._0_2_ == 0) {
      *(undefined1 *)(unaff_A4 + -0x3051) = *(undefined1 *)(*(int *)(unaff_A4 + -0x40e4) + 0x18);
      puVar1 = *(ushort **)(unaff_A4 + -0x3eb0);
      iVar9 = (uint)*puVar1 * (uVar7 & 0xffff);
      uVar13 = unaff_D3w - uVar11;
      if ((short)uVar13 < 0) {
        uVar13 = -uVar13;
      }
      uVar12 = unaff_D2w - uVar10;
      if ((short)uVar12 < 0) {
        uVar12 = -uVar12;
      }
      uVar8 = uVar12;
      uVar5 = uVar13;
      if ((short)uVar13 < (short)uVar12) {
        uVar8 = uVar13;
        uVar5 = uVar12;
      }
      uVar11 = (ushort)*(byte *)(unaff_A4 + -0x4652 +
                                (int)(short)(ushort)(byte)(((unaff_D3w < uVar11) * '\x02' +
                                                           (unaff_D2w < uVar10)) * '\x02' +
                                                          (uVar13 < uVar12)));
      sVar3 = uVar8 * 2;
      uVar13 = (ushort)*(byte *)((int)puVar1 + 5);
      puVar16 = puVar1 + 4;
      while (uVar13 = uVar13 - 1, uVar13 != 0xffff) {
        bVar2 = *(byte *)(unaff_A6 + 2);
        while ((bVar2 & 0x40) != 0) {
          bVar2 = *(byte *)(unaff_A6 + 2);
        }
        puVar15 = puVar16 + 2;
        iVar17 = *(int *)puVar16;
        *(undefined2 *)(unaff_A6 + 0x72) = 0xffff;
        *(undefined2 *)(unaff_A6 + 0x44) = 0xffff;
        *(ushort *)(unaff_A6 + 0x40) = uVar10 << 0xc | 0xbca;
        *(undefined2 *)(unaff_A6 + 0x74) = 0x8000;
        uVar6 = uVar14 & 1;
        uVar14 = uVar14 >> 1;
        if (uVar6 == 0) {
          *(undefined2 *)(unaff_A6 + 0x72) = 0;
        }
        uVar12 = *(ushort *)(unaff_A4 + -0x3052);
        *(ushort *)(unaff_A4 + -0x3052) = uVar12 >> 1;
        puVar16 = puVar15;
        if ((uVar12 & 1) != 0) {
          *(short *)(unaff_A6 + 0x62) = sVar3;
          uVar12 = uVar11;
          if (sVar3 < (short)uVar5) {
            uVar12 = uVar11 | 0x40;
          }
          *(ushort *)(unaff_A6 + 0x52) = sVar3 - uVar5;
          *(ushort *)(unaff_A6 + 100) = (sVar3 - uVar5) - uVar5;
          *(ushort *)(unaff_A6 + 0x42) = uVar12;
          iVar17 = CONCAT22((short)((uint)iVar9 >> 0x10),(uVar10 >> 4) * 2 + (short)iVar9) + iVar17;
          *(int *)(unaff_A6 + 0x48) = iVar17;
          *(int *)(unaff_A6 + 0x54) = iVar17;
          *(ushort *)(unaff_A6 + 0x60) = *puVar1;
          *(ushort *)(unaff_A6 + 0x66) = *puVar1;
          *(ushort *)(unaff_A6 + 0x58) = (uVar5 + 1) * 0x40 + 2;
        }
      }
      return CONCAT44(in_D0,in_D1);
    }
    if ((uStack_34._2_2_ & uStack_34._0_2_) != 0) break;
    sVar3 = unaff_D2w - uVar10;
    sVar4 = unaff_D3w - uVar11;
    if (uStack_34._0_2_ == 0) {
      if ((uStack_34 & 8) == 0) {
        if ((uStack_34 & 4) == 0) {
          if ((uStack_34 & 2) == 0) {
            if ((uStack_34 & 1) != 0) {
              if (sVar3 != 0) {
                unaff_D2w = (short)(((int)(short)(*(short *)(unaff_A4 + -0x469a) - unaff_D3w) *
                                    (int)sVar3) / (int)sVar4) + unaff_D2w;
              }
              unaff_D3w = *(ushort *)(unaff_A4 + -0x469a);
            }
          }
          else {
            if (sVar3 != 0) {
              unaff_D2w = (short)(((int)(short)(*(short *)(unaff_A4 + -0x46a2) - unaff_D3w) *
                                  (int)sVar3) / (int)sVar4) + unaff_D2w;
            }
            unaff_D3w = *(ushort *)(unaff_A4 + -0x46a2);
          }
        }
        else {
          if (sVar4 != 0) {
            unaff_D3w = (short)(((int)(short)(*(short *)(unaff_A4 + -0x4698) - unaff_D2w) *
                                (int)sVar4) / (int)sVar3) + unaff_D3w;
          }
          unaff_D2w = *(ushort *)(unaff_A4 + -0x4698);
        }
      }
      else {
        if (sVar4 != 0) {
          unaff_D3w = (short)(((int)(short)(*(short *)(unaff_A4 + -0x469e) - unaff_D2w) * (int)sVar4
                              ) / (int)sVar3) + unaff_D3w;
        }
        unaff_D2w = *(ushort *)(unaff_A4 + -0x469e);
      }
      uVar10 = 10;
      if ((*(short *)(unaff_A4 + -0x469e) <= (short)unaff_D2w) &&
         (uVar10 = 2, *(short *)(unaff_A4 + -0x4698) < (short)unaff_D2w)) {
        uVar10 = 6;
      }
      if ((*(short *)(unaff_A4 + -0x46a2) <= (short)unaff_D3w) &&
         (uVar10 = uVar10 & 0xfffd, *(short *)(unaff_A4 + -0x469a) < (short)unaff_D3w)) {
        uVar10 = uVar10 | 1;
      }
      uStack_34 = (uint)uVar10;
    }
    else {
      if ((uStack_34 & 0x80000) == 0) {
        if ((uStack_34 & 0x40000) == 0) {
          if ((uStack_34 & 0x20000) == 0) {
            if ((uStack_34 & 0x10000) != 0) {
              if (sVar3 != 0) {
                uVar6 = (uint)(ushort)((short)(((int)(short)(*(short *)(unaff_A4 + -0x469a) - uVar11
                                                            ) * (int)sVar3) / (int)sVar4) + uVar10);
              }
              uVar7 = (uint)*(ushort *)(unaff_A4 + -0x469a);
            }
          }
          else {
            if (sVar3 != 0) {
              uVar6 = (uint)(ushort)((short)(((int)(short)(*(short *)(unaff_A4 + -0x46a2) - uVar11)
                                             * (int)sVar3) / (int)sVar4) + uVar10);
            }
            uVar7 = (uint)*(ushort *)(unaff_A4 + -0x46a2);
          }
        }
        else {
          if (sVar4 != 0) {
            uVar7 = (uint)(ushort)((short)(((int)(short)(*(short *)(unaff_A4 + -0x4698) - uVar10) *
                                           (int)sVar4) / (int)sVar3) + uVar11);
          }
          uVar6 = (uint)*(ushort *)(unaff_A4 + -0x4698);
        }
      }
      else {
        if (sVar4 != 0) {
          uVar7 = (uint)(ushort)((short)(((int)(short)(*(short *)(unaff_A4 + -0x469e) - uVar10) *
                                         (int)sVar4) / (int)sVar3) + uVar11);
        }
        uVar6 = (uint)*(ushort *)(unaff_A4 + -0x469e);
      }
      uVar10 = 10;
      if ((*(short *)(unaff_A4 + -0x469e) <= (short)uVar6) &&
         (uVar10 = 2, *(short *)(unaff_A4 + -0x4698) < (short)uVar6)) {
        uVar10 = 6;
      }
      if ((*(short *)(unaff_A4 + -0x46a2) <= (short)uVar7) &&
         (uVar10 = uVar10 & 0xfffd, *(short *)(unaff_A4 + -0x469a) < (short)uVar7)) {
        uVar10 = uVar10 | 1;
      }
      uStack_34 = CONCAT22(uVar10,uStack_34._2_2_);
    }
  }
  return CONCAT44(in_D0,in_D1);
}


// ==== thunk_FUN_000215d8 @ 000232ce ====

undefined2 thunk_FUN_000215d8(undefined4 param_1,undefined4 param_2)

{
  undefined2 uVar1;
  int unaff_A4;
  
  *(undefined4 *)(unaff_A4 + -0x42cc) = param_1;
  uVar1 = FUN_000216b2(&LAB_00021608,param_2,&stack0x0000000c);
  **(undefined1 **)(unaff_A4 + -0x42cc) = 0;
  return uVar1;
}


// ==== thunk_FUN_00021dce @ 000232d4 ====

void thunk_FUN_00021dce(void)

{
  FUN_00021de2();
  return;
}


// ==== thunk_FUN_00021e02 @ 000232da ====

char * thunk_FUN_00021e02(char *param_1,char *param_2)

{
  char cVar1;
  char *pcVar2;
  
  pcVar2 = param_1;
  do {
    cVar1 = *param_2;
    *pcVar2 = cVar1;
    pcVar2 = pcVar2 + 1;
    param_2 = param_2 + 1;
  } while (cVar1 != '\0');
  return param_1;
}


// ==== thunk_FUN_00021e12 @ 000232e0 ====

char * thunk_FUN_00021e12(char *param_1)

{
  char cVar1;
  char *pcVar2;
  char *pcVar3;
  
  pcVar3 = param_1;
  do {
    pcVar2 = pcVar3 + 1;
    cVar1 = *pcVar3;
    pcVar3 = pcVar2;
  } while (cVar1 != '\0');
  return pcVar2 + (-1 - (int)param_1);
}


// ==== thunk_FUN_00021e82 @ 000232e6 ====

byte thunk_FUN_00021e82(undefined4 param_1)

{
  if ((0x40 < param_1._1_1_) && (param_1._1_1_ < 0x5b)) {
    param_1._1_1_ = param_1._1_1_ + 0x20;
  }
  return param_1._1_1_;
}


// ==== thunk_FUN_00021e9a @ 000232ec ====

undefined4 thunk_FUN_00021e9a(byte *param_1,byte *param_2)

{
  byte bVar1;
  short sVar2;
  
  sVar2 = 0x7ffe;
  do {
    bVar1 = *param_2;
    param_2 = param_2 + 1;
    if (*param_1 != bVar1) {
      if (*param_1 <= bVar1) {
        return 0xffffffff;
      }
      return 1;
    }
  } while ((*param_1 != 0) && (sVar2 = sVar2 + -1, param_1 = param_1 + 1, sVar2 != -1));
  return 0;
}


// ==== thunk_FUN_00021eca @ 000232f2 ====

void thunk_FUN_00021eca(undefined1 *param_1,undefined1 *param_2,undefined4 param_3)

{
  if (param_2 == param_1) {
    return;
  }
  if (param_2 <= param_1) {
    while (param_3._0_2_ = param_3._0_2_ + -1, param_3._0_2_ != -1) {
      *param_2 = *param_1;
      param_1 = param_1 + 1;
      param_2 = param_2 + 1;
    }
    return;
  }
  param_1 = param_1 + param_3._0_2_;
  param_2 = param_2 + param_3._0_2_;
  while (param_3._0_2_ = param_3._0_2_ + -1, param_3._0_2_ != -1) {
    param_1 = param_1 + -1;
    param_2 = param_2 + -1;
    *param_2 = *param_1;
  }
  return;
}


// ==== thunk_FUN_00021ef4 @ 000232f8 ====

undefined4 thunk_FUN_00021ef4(char *param_1)

{
  short sVar2;
  undefined4 uVar1;
  
  do {
    if (*param_1 == '\0') {
      uVar1 = FUN_00022474();
      return uVar1;
    }
    param_1 = param_1 + 1;
    sVar2 = FUN_00022474();
  } while (sVar2 != -1);
  return 0xffffffff;
}


// ==== thunk_FUN_00021f2e @ 000232fe ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void thunk_FUN_00021f2e(void)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  short sVar4;
  undefined4 extraout_A0;
  undefined4 *puVar5;
  int unaff_A4;
  
  uVar2 = FUN_00021fa0();
  sVar4 = 0x4e3;
  puVar5 = (undefined4 *)(unaff_A4 + -0x439e);
  do {
    *puVar5 = 0;
    sVar4 = sVar4 + -1;
    puVar5 = puVar5 + 1;
  } while (sVar4 != -1);
  *(BADSPACEBASE **)(unaff_A4 + -0x304c) = register0x0000003c;
  iVar1 = _DAT_00000004;
  *(int *)(unaff_A4 + -0x408a) = _DAT_00000004;
  if ((*(byte *)(iVar1 + 0x129) & 0x10) != 0) {
    (**(code **)(iVar1 + -0x1e))(uVar2,extraout_A0);
  }
  iVar3 = (**(code **)(iVar1 + -0x198))();
  *(int *)(unaff_A4 + -0x40e0) = iVar3;
  if (iVar3 == 0) {
    (**(code **)(iVar1 + -0x6c))();
  }
  else {
    FUN_00021fa8();
  }
  return;
}


// ==== thunk_FUN_000222a8 @ 00023304 ====

char * thunk_FUN_000222a8(char *param_1,char *param_2)

{
  char cVar1;
  short sVar2;
  char *pcVar3;
  char *pcVar4;
  
  pcVar3 = param_1;
  do {
    pcVar4 = pcVar3;
    pcVar3 = pcVar4 + 1;
  } while (*pcVar4 != '\0');
  sVar2 = 0x7ffe;
  do {
    cVar1 = *param_2;
    pcVar3 = pcVar4 + 1;
    *pcVar4 = cVar1;
    if (cVar1 == '\0') break;
    sVar2 = sVar2 + -1;
    pcVar4 = pcVar3;
    param_2 = param_2 + 1;
  } while (sVar2 != -1);
  if (cVar1 != '\0') {
    *pcVar3 = '\0';
  }
  return param_1;
}


// ==== thunk_FUN_000222d2 @ 0002330a ====

char * thunk_FUN_000222d2(char *param_1,char *param_2,undefined4 param_3)

{
  char cVar1;
  char *pcVar2;
  bool bVar3;
  
  bVar3 = param_3._0_2_ == 0;
  pcVar2 = param_1;
  while ((!bVar3 && (param_3._0_2_ = param_3._0_2_ + -1, param_3._0_2_ != -1))) {
    cVar1 = *param_2;
    *pcVar2 = cVar1;
    bVar3 = cVar1 == '\0';
    pcVar2 = pcVar2 + 1;
    param_2 = param_2 + 1;
  }
  if (!bVar3) {
    param_3._0_2_ = param_3._0_2_ + 1;
  }
  while (param_3._0_2_ = param_3._0_2_ + -1, param_3._0_2_ != -1) {
    *pcVar2 = '\0';
    pcVar2 = pcVar2 + 1;
  }
  return param_1;
}


// ==== thunk_FUN_000223cc @ 00023310 ====

undefined8 thunk_FUN_000223cc(void)

{
  int iVar1;
  int in_D0;
  int in_D1;
  bool bVar2;
  
  bVar2 = in_D0 < 0;
  if (in_D1 < 0) {
    bVar2 = !bVar2;
  }
  iVar1 = FUN_00022424();
  if (bVar2) {
    iVar1 = -iVar1;
  }
  return CONCAT44(iVar1,in_D1);
}


// ==== thunk_FUN_00022ab2 @ 00023316 ====

void thunk_FUN_00022ab2(void)

{
  int unaff_A4;
  
                    /* WARNING: Could not recover jumptable at 0x00022aba. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(int *)(unaff_A4 + -0x40e0) + -0x24))();
  return;
}


// ==== thunk_FUN_00022ace @ 0002331c ====

void thunk_FUN_00022ace(void)

{
  int unaff_A4;
  
                    /* WARNING: Could not recover jumptable at 0x00022ad6. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(int *)(unaff_A4 + -0x40e0) + -0x48))();
  return;
}


// ==== thunk_FUN_00022ade @ 00023322 ====

void thunk_FUN_00022ade(void)

{
  int unaff_A4;
  
                    /* WARNING: Could not recover jumptable at 0x00022ae8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(int *)(unaff_A4 + -0x40e0) + -0x66))();
  return;
}


// ==== thunk_FUN_00022aec @ 00023328 ====

void thunk_FUN_00022aec(void)

{
  int unaff_A4;
  
                    /* WARNING: Could not recover jumptable at 0x00022af6. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(int *)(unaff_A4 + -0x40e0) + -0x6c))();
  return;
}


// ==== thunk_FUN_00022b06 @ 0002332e ====

void thunk_FUN_00022b06(void)

{
  int unaff_A4;
  
                    /* WARNING: Could not recover jumptable at 0x00022b0a. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(int *)(unaff_A4 + -0x40e0) + -0x84))();
  return;
}


// ==== thunk_FUN_00022b1e @ 00023334 ====

void thunk_FUN_00022b1e(void)

{
  int unaff_A4;
  
                    /* WARNING: Could not recover jumptable at 0x00022b28. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(int *)(unaff_A4 + -0x40e0) + -0x54))();
  return;
}


// ==== thunk_FUN_00022b30 @ 0002333a ====

void thunk_FUN_00022b30(void)

{
  int unaff_A4;
  
                    /* WARNING: Could not recover jumptable at 0x00022b3a. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(int *)(unaff_A4 + -0x40e0) + -0x1e))();
  return;
}


// ==== thunk_FUN_00022b42 @ 00023340 ====

void thunk_FUN_00022b42(void)

{
  int unaff_A4;
  
                    /* WARNING: Could not recover jumptable at 0x00022b4c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(int *)(unaff_A4 + -0x40e0) + -0x2a))();
  return;
}


// ==== thunk_FUN_00022b54 @ 00023346 ====

void thunk_FUN_00022b54(void)

{
  int unaff_A4;
  
                    /* WARNING: Could not recover jumptable at 0x00022b5c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(int *)(unaff_A4 + -0x40e0) + -0x5a))();
  return;
}


// ==== thunk_FUN_00021d6e @ 0002334c ====

void thunk_FUN_00021d6e(void)

{
  int unaff_A4;
  
                    /* WARNING: Could not recover jumptable at 0x00021d78. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(int *)(unaff_A4 + -0x40e0) + -0x30))();
  return;
}


// ==== thunk_FUN_00022d48 @ 00023352 ====

void thunk_FUN_00022d48(void)

{
  int unaff_A4;
  
                    /* WARNING: Could not recover jumptable at 0x00022d4c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(int *)(unaff_A4 + -0x408a) + -0x78))();
  return;
}


// ==== thunk_FUN_00022d66 @ 00023358 ====

void thunk_FUN_00022d66(void)

{
  int unaff_A4;
  
                    /* WARNING: Could not recover jumptable at 0x00022d6a. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(int *)(unaff_A4 + -0x408a) + -0x7e))();
  return;
}


// ==== thunk_FUN_00022e0c @ 0002335e ====

void thunk_FUN_00022e0c(void)

{
  int unaff_A4;
  
  (**(code **)(*(int *)(unaff_A4 + -0x40dc) + -0x1e))();
  return;
}


// ==== thunk_FUN_00022e2e @ 00023364 ====

void thunk_FUN_00022e2e(void)

{
  int unaff_A4;
  
                    /* WARNING: Could not recover jumptable at 0x00022e3c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(int *)(unaff_A4 + -0x40dc) + -300))();
  return;
}


// ==== thunk_FUN_00022e48 @ 0002336a ====

void thunk_FUN_00022e48(void)

{
  int unaff_A4;
  
                    /* WARNING: Could not recover jumptable at 0x00022e56. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(int *)(unaff_A4 + -0x40dc) + -0xf6))();
  return;
}


// ==== thunk_FUN_00022e5a @ 00023370 ====

void thunk_FUN_00022e5a(void)

{
  int unaff_A4;
  
                    /* WARNING: Could not recover jumptable at 0x00022e68. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(int *)(unaff_A4 + -0x40dc) + -0x186))();
  return;
}


// ==== thunk_FUN_00022e6c @ 00023376 ====

void thunk_FUN_00022e6c(void)

{
  int unaff_A4;
  
                    /* WARNING: Could not recover jumptable at 0x00022e74. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(int *)(unaff_A4 + -0x40dc) + -0xc6))();
  return;
}


// ==== thunk_FUN_00022e78 @ 0002337c ====

void thunk_FUN_00022e78(void)

{
  int unaff_A4;
  
                    /* WARNING: Could not recover jumptable at 0x00022e86. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(int *)(unaff_A4 + -0x40dc) + -0xf0))();
  return;
}


// ==== thunk_FUN_00022e92 @ 00023382 ====

void thunk_FUN_00022e92(void)

{
  int unaff_A4;
  
                    /* WARNING: Could not recover jumptable at 0x00022ea0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(int *)(unaff_A4 + -0x40dc) + -0x132))();
  return;
}


// ==== thunk_FUN_00022ea4 @ 00023388 ====

void thunk_FUN_00022ea4(void)

{
  int unaff_A4;
  
                    /* WARNING: Could not recover jumptable at 0x00022eb0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(int *)(unaff_A4 + -0x40dc) + -0x156))();
  return;
}


// ==== thunk_FUN_00022eb4 @ 0002338e ====

void thunk_FUN_00022eb4(void)

{
  int unaff_A4;
  
                    /* WARNING: Could not recover jumptable at 0x00022ec0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(int *)(unaff_A4 + -0x40dc) + -0x15c))();
  return;
}


// ==== thunk_FUN_00022ec4 @ 00023394 ====

void thunk_FUN_00022ec4(void)

{
  int unaff_A4;
  
                    /* WARNING: Could not recover jumptable at 0x00022ed0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(int *)(unaff_A4 + -0x40dc) + -0x162))();
  return;
}


// ==== thunk_FUN_00022ed4 @ 0002339a ====

void thunk_FUN_00022ed4(void)

{
  int unaff_A4;
  
  (**(code **)(*(int *)(unaff_A4 + -0x40dc) + -0x3c))();
  return;
}


// ==== thunk_FUN_00022eee @ 000233a0 ====

void thunk_FUN_00022eee(void)

{
  int unaff_A4;
  
                    /* WARNING: Could not recover jumptable at 0x00022ef2. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(int *)(unaff_A4 + -0x40dc) + -0x10e))();
  return;
}


