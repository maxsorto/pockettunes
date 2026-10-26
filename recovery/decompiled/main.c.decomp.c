// ===== drmp3_bs_get_bits @ 10405440 =====

uint drmp3_bs_get_bits(int *param_1,int param_2)

{
  uint uVar1;
  byte *pbVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  
  gp = &__global_pointer_;
  uVar4 = param_1[1];
  param_1[1] = uVar4 + param_2;
  if (param_1[2] < (int)(uVar4 + param_2)) {
    return 0;
  }
  pbVar2 = (byte *)(*param_1 + ((int)uVar4 >> 3));
  param_2 = param_2 + (uVar4 & 7);
  uVar6 = param_2 - 8;
  uVar4 = (uint)*pbVar2 & 0xff >> (uVar4 & 7);
  if ((int)uVar6 < 1) {
    uVar5 = 0;
  }
  else {
    uVar5 = 0;
    uVar3 = uVar6;
    do {
      pbVar2 = pbVar2 + 1;
      uVar1 = uVar3 & 0x1f;
      uVar3 = uVar3 - 8;
      uVar5 = uVar5 | uVar4 << uVar1;
      uVar4 = (uint)*pbVar2;
    } while (uVar3 != (param_2 + -0x10) - (param_2 - 9U & 0xfffffff8));
    param_2 = uVar6 - (param_2 - 9U & 0xfffffff8);
  }
  return uVar4 >> (8U - param_2 & 0x1f) | uVar5;
}


// ===== drmp3_L3_read_side_info @ 10405500 =====

uint drmp3_L3_read_side_info(int param_1,undefined4 *param_2,int param_3)

{
  byte bVar1;
  int iVar2;
  char cVar3;
  char cVar4;
  undefined1 uVar5;
  ushort uVar6;
  ushort uVar7;
  int iVar8;
  uint uVar9;
  uint uVar10;
  undefined4 *puVar11;
  int iVar12;
  int iVar13;
  uint uStack_48;
  
  gp = &__global_pointer_;
  bVar1 = *(byte *)(param_3 + 1);
  iVar2 = ((bVar1 >> 3 & 1) + (bVar1 >> 4 & 1)) * 3 + (*(byte *)(param_3 + 2) >> 2 & 3);
  uVar10 = (uint)((*(byte *)(param_3 + 3) & 0xc0) != 0xc0);
  iVar2 = iVar2 - (uint)(iVar2 != 0);
  iVar12 = uVar10 + 1;
  if ((bVar1 & 8) == 0) {
    uStack_48 = drmp3_bs_get_bits(param_1,uVar10 + 9);
    uStack_48 = uStack_48 >> iVar12;
    uVar10 = 0;
  }
  else {
    uStack_48 = drmp3_bs_get_bits(param_1,9);
    iVar12 = iVar12 * 2;
    uVar10 = drmp3_bs_get_bits(param_1,iVar12 + 7);
  }
  puVar11 = param_2 + iVar12 * 7;
  iVar12 = iVar2 * 0x28;
  iVar13 = 0;
  do {
    if ((*(byte *)(param_3 + 3) & 0xc0) == 0xc0) {
      uVar10 = uVar10 << 4;
    }
    uVar6 = drmp3_bs_get_bits(param_1,0xc);
    *(ushort *)(param_2 + 1) = uVar6;
    uVar7 = drmp3_bs_get_bits(param_1,9);
    *(ushort *)((int)param_2 + 6) = uVar7;
    if (0x120 < uVar7) goto LAB_ram_10405780;
    uVar5 = drmp3_bs_get_bits(param_1,8);
    *(undefined1 *)((int)param_2 + 10) = uVar5;
    uVar7 = drmp3_bs_get_bits(param_1,(-((*(byte *)(param_3 + 1) & 8) == 0) & 5U) + 4);
    *param_2 = g_scf_long_46 + iVar2 * 0x17;
    *(undefined1 *)((int)param_2 + 0xd) = 0x16;
    *(undefined1 *)((int)param_2 + 0xe) = 0;
    *(ushort *)(param_2 + 2) = uVar7;
    iVar8 = drmp3_bs_get_bits(param_1,1);
    if (iVar8 == 0) {
      *(undefined1 *)((int)param_2 + 0xb) = 0;
      *(undefined1 *)(param_2 + 3) = 0;
      uVar9 = drmp3_bs_get_bits(param_1,0xf);
      uVar5 = drmp3_bs_get_bits(param_1,4);
      *(undefined1 *)((int)param_2 + 0x12) = uVar5;
      uVar5 = drmp3_bs_get_bits(param_1,3);
      *(undefined1 *)((int)param_2 + 0x13) = uVar5;
      *(undefined1 *)(param_2 + 5) = 0xff;
    }
    else {
      cVar3 = drmp3_bs_get_bits(param_1,2);
      *(char *)((int)param_2 + 0xb) = cVar3;
      if (cVar3 == '\0') goto LAB_ram_10405780;
      cVar4 = drmp3_bs_get_bits(param_1,1);
      *(undefined2 *)((int)param_2 + 0x12) = 0xff07;
      *(char *)(param_2 + 3) = cVar4;
      if (cVar3 == '\x02') {
        uVar10 = uVar10 & 0xf0f;
        if (cVar4 == '\0') {
          *param_2 = g_scf_short_45 + iVar12;
          *(undefined1 *)((int)param_2 + 0x12) = 8;
          *(undefined1 *)((int)param_2 + 0xd) = 0;
          *(undefined1 *)((int)param_2 + 0xe) = 0x27;
        }
        else {
          *param_2 = g_scf_mixed_44 + iVar12;
          bVar1 = *(byte *)(param_3 + 1);
          *(undefined1 *)((int)param_2 + 0xe) = 0x1e;
          *(byte *)((int)param_2 + 0xd) = (-((bVar1 & 8) == 0) & 0xfeU) + 8;
        }
      }
      iVar8 = drmp3_bs_get_bits(param_1,10);
      uVar9 = iVar8 << 5;
      uVar5 = drmp3_bs_get_bits(param_1,3);
      *(undefined1 *)((int)param_2 + 0x15) = uVar5;
      uVar5 = drmp3_bs_get_bits(param_1,3);
      *(undefined1 *)((int)param_2 + 0x16) = uVar5;
      uVar5 = drmp3_bs_get_bits(param_1,3);
      *(undefined1 *)((int)param_2 + 0x17) = uVar5;
    }
    *(byte *)(param_2 + 4) = (byte)(uVar9 >> 5) & 0x1f;
    *(char *)((int)param_2 + 0xf) = (char)(uVar9 >> 10);
    *(byte *)((int)param_2 + 0x11) = (byte)uVar9 & 0x1f;
    uVar5 = 499 < uVar7;
    iVar13 = iVar13 + (uint)uVar6;
    if ((*(byte *)(param_3 + 1) & 8) != 0) {
      uVar5 = drmp3_bs_get_bits(param_1,1);
    }
    *(undefined1 *)(param_2 + 6) = uVar5;
    uVar5 = drmp3_bs_get_bits(param_1,1);
    *(undefined1 *)((int)param_2 + 0x19) = uVar5;
    uVar5 = drmp3_bs_get_bits(param_1,1);
    *(undefined1 *)((int)param_2 + 0x1a) = uVar5;
    *(byte *)((int)param_2 + 0x1b) = (byte)(uVar10 >> 0xc) & 0xf;
    param_2 = param_2 + 7;
    uVar10 = uVar10 << 4;
  } while (param_2 != puVar11);
  if ((int)(uStack_48 * 8 + *(int *)(param_1 + 8)) < iVar13 + *(int *)(param_1 + 4)) {
LAB_ram_10405780:
    uStack_48 = 0xffffffff;
  }
  return uStack_48;
}


// ===== drmp3_L3_dct3_9 @ 10405800 =====

void drmp3_L3_dct3_9(float *param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  
  gp = &__global_pointer_;
  fVar2 = param_1[7];
  fVar15 = (float)*(undefined8 *)(param_1 + 5);
  fVar12 = (float)*(undefined8 *)(param_1 + 1);
  fVar3 = param_1[8];
  fVar4 = (float)*(undefined8 *)(param_1 + 6) * DAT_ram_1043493c + *param_1;
  fVar13 = (float)*(undefined8 *)(param_1 + 2);
  fVar5 = (fVar12 + fVar15) * DAT_ram_1043494c;
  fVar6 = (fVar15 - fVar2) * DAT_ram_10434950;
  fVar16 = (float)*(undefined8 *)(param_1 + 4);
  fVar10 = *param_1 - (float)*(undefined8 *)(param_1 + 6);
  fVar1 = (fVar3 - fVar13) + fVar16;
  fVar14 = (float)*(undefined8 *)(param_1 + 3);
  fVar7 = -(fVar1 * DAT_ram_1043493c) + fVar10;
  fVar11 = (-(fVar14 * DAT_ram_10434954) + fVar6) - fVar5;
  fVar8 = -((fVar12 + fVar2) * DAT_ram_10434958) + fVar14 * DAT_ram_10434954 + fVar6;
  fVar9 = -((fVar16 - fVar3) * DAT_ram_10434944) + (fVar13 + fVar16) * DAT_ram_10434948 + fVar4;
  fVar6 = (fVar13 + fVar3) * DAT_ram_10434940 + -((fVar13 + fVar16) * DAT_ram_10434948) + fVar4;
  fVar3 = (fVar16 - fVar3) * DAT_ram_10434944 + -((fVar13 + fVar3) * DAT_ram_10434940) + fVar4;
  fVar4 = (fVar12 - fVar15) - fVar2;
  fVar5 = -((fVar12 + fVar2) * DAT_ram_10434958) + -(fVar14 * DAT_ram_10434954) + fVar5;
  fVar2 = fVar4 * DAT_ram_10434954;
  fVar4 = fVar4 * DAT_ram_10434954;
  param_1[4] = fVar10 + fVar1;
  *param_1 = fVar9 - fVar11;
  *(ulonglong *)(param_1 + 8) = (ulonglong)(uint)(fVar9 + fVar11);
  param_1[1] = fVar2 + fVar7;
  *(ulonglong *)(param_1 + 7) = (ulonglong)(uint)(-fVar4 + fVar7);
  param_1[2] = fVar6 - fVar8;
  *(ulonglong *)(param_1 + 6) = (ulonglong)(uint)(fVar6 + fVar8);
  *(ulonglong *)(param_1 + 3) = (ulonglong)(uint)(fVar3 + fVar5);
  *(ulonglong *)(param_1 + 5) = (ulonglong)(uint)(fVar3 - fVar5);
  return;
}


// ===== drmp3_L3_imdct36 @ 10405980 =====

void drmp3_L3_imdct36(float *param_1,float *param_2,float *param_3,int param_4)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float *pfVar4;
  float *pfVar5;
  float *pfVar6;
  undefined8 *puVar7;
  float *pfVar8;
  float *pfVar9;
  float *pfVar10;
  float *pfVar11;
  float *pfVar12;
  int iVar13;
  float *pfVar14;
  float fVar15;
  undefined8 uVar16;
  undefined8 uVar17;
  undefined8 uVar18;
  undefined8 uVar19;
  float local_88;
  undefined1 auStack_84 [32];
  float local_64 [5];
  float fStack_50;
  float fStack_48;
  undefined8 auStack_44 [2];
  
  gp = &__global_pointer_;
  if (param_4 < 1) {
    return;
  }
  pfVar11 = param_2 + 9;
  pfVar12 = param_1 + 0x11;
  iVar13 = 0;
  pfVar14 = pfVar11;
  while( true ) {
    local_64[0] = *pfVar12;
    pfVar9 = local_64;
    local_88 = -*param_1;
    pfVar10 = &local_88;
    pfVar8 = param_1 + 1;
    pfVar4 = pfVar10;
    pfVar6 = pfVar9;
    do {
      uVar16 = *(undefined8 *)(pfVar8 + 2);
      uVar18 = *(undefined8 *)(pfVar8 + 3);
      uVar19 = *(undefined8 *)pfVar8;
      uVar17 = *(undefined8 *)(pfVar8 + 1);
      pfVar8 = pfVar8 + 4;
      *(ulonglong *)(pfVar6 + 7) = (ulonglong)(uint)((float)uVar18 - (float)uVar16);
      *(ulonglong *)(pfVar6 + 8) = (ulonglong)(uint)((float)uVar19 - (float)uVar17);
      *(ulonglong *)(pfVar4 + 2) = (ulonglong)(uint)-((float)uVar18 + (float)uVar16);
      *(ulonglong *)(pfVar4 + 1) = (ulonglong)(uint)((float)uVar19 + (float)uVar17);
      pfVar6 = pfVar6 + -2;
      pfVar4 = pfVar4 + 2;
    } while (pfVar8 != pfVar12);
    drmp3_L3_dct3_9(&local_88);
    drmp3_L3_dct3_9(local_64);
    local_64[1] = -local_64[1];
    local_64[3] = -local_64[3];
    fStack_50 = -fStack_50;
    fStack_48 = -fStack_48;
    puVar7 = &g_twid9_29;
    pfVar4 = param_1;
    pfVar6 = param_3;
    pfVar8 = pfVar12;
    do {
      fVar1 = *pfVar9;
      uVar17 = *puVar7;
      fVar2 = *pfVar10;
      fVar15 = (float)*(undefined8 *)((int)puVar7 + 0x24);
      uVar16 = *(undefined8 *)param_2;
      pfVar5 = param_2 + 1;
      pfVar9 = pfVar9 + 1;
      fVar3 = fVar2 * fVar15 + fVar1 * (float)uVar17;
      pfVar10 = pfVar10 + 1;
      puVar7 = (undefined8 *)((int)puVar7 + 4);
      *param_2 = fVar2 * (float)uVar17 - fVar15 * fVar1;
      *pfVar4 = (float)*(undefined8 *)pfVar6 * (float)uVar16 -
                fVar3 * (float)*(undefined8 *)(pfVar6 + 9);
      *pfVar8 = (float)*(undefined8 *)(pfVar6 + 9) * (float)uVar16 + fVar3 * *pfVar6;
      pfVar4 = pfVar4 + 1;
      param_2 = pfVar5;
      pfVar6 = pfVar6 + 1;
      pfVar8 = pfVar8 + -1;
    } while (pfVar5 != pfVar11);
    iVar13 = iVar13 + 1;
    param_1 = param_1 + 0x12;
    pfVar11 = pfVar11 + 9;
    pfVar12 = pfVar12 + 0x12;
    if (param_4 == iVar13) break;
    param_2 = pfVar14;
    pfVar14 = pfVar14 + 9;
  }
  return;
}


// ===== drmp3_L3_imdct12 @ 10405b40 =====

void drmp3_L3_imdct12(float *param_1,float *param_2,float *param_3)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float *pfVar6;
  float *pfVar7;
  float *pfVar8;
  float *pfVar9;
  undefined8 *puVar10;
  undefined8 *puVar11;
  float *pfVar12;
  float fVar13;
  undefined8 uVar14;
  undefined8 uVar15;
  undefined8 uVar16;
  undefined8 uVar17;
  float local_18;
  float fStack_14;
  float fStack_10;
  float local_c;
  float fStack_8;
  float fStack_4;
  
  gp = &__global_pointer_;
  fVar4 = (float)*(undefined8 *)(param_1 + 6) - (float)*(undefined8 *)(param_1 + 3);
  fVar1 = (float)*(undefined8 *)(param_1 + 0xc) + (float)*(undefined8 *)(param_1 + 9);
  fVar13 = (float)*(undefined8 *)(param_1 + 6) + (float)*(undefined8 *)(param_1 + 3);
  fVar5 = (float)*(undefined8 *)(param_1 + 0xc) - (float)*(undefined8 *)(param_1 + 9);
  fVar3 = -(fVar4 * DAT_ram_1043493c) + (float)*(undefined8 *)(param_1 + 0xf);
  fVar2 = -(fVar1 * DAT_ram_1043493c) - *param_1;
  puVar11 = &g_twid3_30;
  fStack_8 = -((float)*(undefined8 *)(param_1 + 0xf) + fVar4);
  local_c = fVar5 * DAT_ram_10434954 + fVar3;
  fStack_4 = -(fVar5 * DAT_ram_10434954) + fVar3;
  fStack_14 = fVar1 - *param_1;
  local_18 = fVar13 * DAT_ram_10434954 + fVar2;
  fStack_10 = -(fVar13 * DAT_ram_10434954) + fVar2;
  pfVar6 = &local_18;
  pfVar9 = &local_c;
  pfVar7 = param_3;
  puVar10 = &g_twid3_30;
  pfVar12 = param_2 + 5;
  do {
    uVar15 = *(undefined8 *)pfVar9;
    uVar16 = *puVar11;
    uVar17 = *(undefined8 *)pfVar6;
    fVar13 = (float)*(undefined8 *)((int)puVar11 + 0xc);
    uVar14 = *(undefined8 *)pfVar7;
    pfVar8 = pfVar7 + 1;
    pfVar9 = pfVar9 + 1;
    fVar1 = (float)uVar17 * fVar13 + (float)uVar15 * (float)uVar16;
    pfVar6 = pfVar6 + 1;
    puVar11 = (undefined8 *)((int)puVar11 + 4);
    *pfVar7 = (float)uVar17 * (float)uVar16 - fVar13 * (float)uVar15;
    uVar15 = puVar10[1];
    fVar13 = (float)*(undefined8 *)((int)puVar10 + 0x14);
    *param_2 = (float)uVar15 * (float)uVar14 - fVar13 * fVar1;
    *pfVar12 = fVar13 * (float)uVar14 + (float)uVar15 * fVar1;
    param_2 = param_2 + 1;
    pfVar7 = pfVar8;
    puVar10 = (undefined8 *)((int)puVar10 + -4);
    pfVar12 = pfVar12 + -1;
  } while (pfVar8 != param_3 + 3);
  return;
}


// ===== drmp3d_synth_pair @ 10405c80 =====

void drmp3d_synth_pair(short *param_1,int param_2,undefined8 *param_3)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  short sVar11;
  undefined8 uVar12;
  
  fVar10 = DAT_ram_104349a0;
  fVar9 = DAT_ram_1043499c;
  fVar8 = DAT_ram_1043497c;
  gp = &__global_pointer_;
  fVar6 = *(float *)(param_3 + 0xe0) * DAT_ram_10434978 +
          (*(float *)(param_3 + 0x100) - *(float *)(param_3 + 0xc0)) * DAT_ram_10434974 +
          (*(float *)(param_3 + 0xa0) + *(float *)(param_3 + 0x120)) * DAT_ram_10434970 +
          (*(float *)(param_3 + 0x140) - *(float *)(param_3 + 0x80)) * DAT_ram_1043496c +
          (*(float *)(param_3 + 0x60) + *(float *)(param_3 + 0x160)) * DAT_ram_10434968 +
          (*(float *)(param_3 + 0x180) - *(float *)(param_3 + 0x40)) * DAT_ram_10434964 +
          (*(float *)(param_3 + 0x1c0) - (float)*param_3) * DAT_ram_10434960 +
          (*(float *)(param_3 + 0x20) + *(float *)(param_3 + 0x1a0)) * DAT_ram_1043495c;
  if (DAT_ram_1043497c <= fVar6) {
    sVar11 = 0x7fff;
  }
  else if (fVar6 <= DAT_ram_10434980) {
    sVar11 = -0x8000;
  }
  else {
    sVar11 = (short)(int)(fVar6 + DAT_ram_1043493c) -
             (short)(((int)(fVar6 + DAT_ram_1043493c) & 0xffffU) >> 0xf);
  }
  fVar7 = *(float *)(param_3 + 0x181) * DAT_ram_10434984;
  fVar1 = *(float *)(param_3 + 0x1c1) * DAT_ram_10434988;
  fVar2 = *(float *)(param_3 + 0x141) * DAT_ram_1043498c;
  fVar3 = *(float *)(param_3 + 0x101) * DAT_ram_10434990;
  fVar6 = *(float *)(param_3 + 0x41);
  fVar4 = *(float *)(param_3 + 0xc1) * DAT_ram_10434994;
  uVar12 = param_3[1];
  fVar5 = *(float *)(param_3 + 0x81) * DAT_ram_10434998;
  *param_1 = sVar11;
  fVar6 = (float)uVar12 * fVar10 + fVar6 * fVar9 + fVar5 + fVar4 + fVar3 + fVar2 + fVar1 + fVar7;
  if (fVar6 < fVar8) {
    if (fVar6 <= DAT_ram_10434980) {
      sVar11 = -0x8000;
    }
    else {
      sVar11 = (short)(int)(fVar6 + DAT_ram_1043493c) -
               (short)(((int)(fVar6 + DAT_ram_1043493c) & 0xffffU) >> 0xf);
    }
    param_1[param_2 * 0x10] = sVar11;
    return;
  }
  param_1[param_2 * 0x10] = 0x7fff;
  return;
}


// ===== arrow_of @ 10405ec0 =====

bool arrow_of(uint param_1,int *param_2)

{
  bool bVar1;
  int iVar2;
  
  gp = &__global_pointer_;
  iVar2 = *param_2;
  if (3 < iVar2) {
    return iVar2 == 6;
  }
  bVar1 = true;
  if (iVar2 < 2) {
    if (iVar2 != 0) {
      return false;
    }
    bVar1 = param_1 - 5 < 2 || param_1 < 3;
  }
  return bVar1;
}


// ===== drmp3d_synth_granule @ 10405f40 =====

void drmp3d_synth_granule
               (undefined4 *param_1,uint *param_2,int param_3,int param_4,int param_5,void *param_6)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  uint *puVar18;
  ulonglong *puVar19;
  short *psVar20;
  short *psVar21;
  float *pfVar22;
  short *psVar23;
  float *pfVar24;
  float *pfVar25;
  short *psVar26;
  float *pfVar27;
  float *pfVar28;
  undefined8 *puVar29;
  void *pvVar30;
  short sVar31;
  float *pfVar32;
  ulonglong *puVar33;
  ulonglong *puVar34;
  uint *puVar35;
  void *pvVar36;
  ulonglong *puVar37;
  short *psVar38;
  short *psVar39;
  short *psVar40;
  int iVar41;
  short *psVar42;
  short *psVar43;
  float *pfVar44;
  uint *puVar45;
  short *psVar46;
  undefined8 *puVar47;
  uint *puVar48;
  uint *puVar49;
  uint *puVar50;
  float fVar51;
  float fVar52;
  ulonglong uVar53;
  undefined8 uVar54;
  float fVar55;
  short *local_130;
  float local_e0 [4];
  float local_d0 [4];
  undefined8 uStack_c0;
  float fStack_b8;
  undefined8 uStack_b4;
  float afStack_ac [6];
  float fStack_94;
  float fStack_90;
  float afStack_8c [6];
  float fStack_74;
  uint uStack_70;
  undefined8 uStack_54;
  float afStack_50 [7];
  
  fVar6 = DAT_ram_104349c4;
  fVar5 = DAT_ram_104349c0;
  fVar4 = DAT_ram_104349bc;
  fVar17 = DAT_ram_104349b8;
  fVar15 = DAT_ram_104349b4;
  fVar13 = DAT_ram_104349b0;
  fVar16 = DAT_ram_104349ac;
  fVar14 = DAT_ram_104349a8;
  fVar12 = DAT_ram_104349a4;
  gp = &__global_pointer_;
  iVar41 = param_4 << 3;
  if (0 < param_4) {
    iVar41 = param_4 * 8;
    pfVar27 = (float *)(param_2 + param_3 + 0x1f8);
    do {
      pfVar24 = pfVar27 + -param_3;
      do {
        pfVar22 = pfVar24 + -0xea;
        pfVar28 = (float *)&g_sec_22;
        pfVar25 = pfVar24 + -0x1f8;
        pfVar44 = local_d0;
        do {
          fVar51 = (float)*(undefined8 *)pfVar25 + pfVar22[0x120];
          fVar2 = *pfVar28;
          fVar8 = (float)*(undefined8 *)pfVar22 - pfVar25[0x120];
          fVar52 = ((float)*(undefined8 *)pfVar25 - pfVar22[0x120]) * pfVar28[1];
          fVar55 = (float)*(undefined8 *)pfVar22 + pfVar25[0x120];
          fVar3 = pfVar28[2];
          pfVar32 = pfVar44 + 1;
          pfVar22 = pfVar22 + -0x12;
          pfVar25 = pfVar25 + 0x12;
          *(ulonglong *)(pfVar44 + 0x10) = (ulonglong)(uint)(fVar8 * fVar2 + fVar52);
          *pfVar44 = fVar51 + fVar55;
          pfVar28 = pfVar28 + 3;
          *(ulonglong *)(pfVar44 + 0x18) = (ulonglong)(uint)((-(fVar8 * fVar2) + fVar52) * fVar3);
          *(ulonglong *)(pfVar44 + 8) = (ulonglong)(uint)((fVar51 - fVar55) * fVar3);
          pfVar44 = pfVar32;
        } while (pfVar32 != (float *)((int)&uStack_b4 + 4));
        pfVar25 = local_d0;
        do {
          fVar9 = (float)*(undefined8 *)pfVar25 - (float)*(undefined8 *)(pfVar25 + 7);
          fVar1 = (float)*(undefined8 *)pfVar25 + (float)*(undefined8 *)(pfVar25 + 7);
          fVar52 = pfVar25[1] - (float)*(undefined8 *)(pfVar25 + 6);
          fVar51 = pfVar25[1] + (float)*(undefined8 *)(pfVar25 + 6);
          fVar10 = pfVar25[2] - pfVar25[5];
          fVar55 = pfVar25[2] + pfVar25[5];
          fVar2 = pfVar25[3] + (float)*(undefined8 *)(pfVar25 + 4);
          fVar3 = fVar9 + fVar52;
          pfVar44 = pfVar25 + 8;
          fVar52 = fVar52 + fVar10;
          fVar11 = fVar1 - fVar2;
          fVar8 = fVar51 + fVar55;
          fVar7 = -(fVar52 * fVar12) + fVar9;
          fVar10 = -(fVar3 * fVar14) + fVar10 + (pfVar25[3] - (float)*(undefined8 *)(pfVar25 + 4));
          fVar9 = fVar52 * fVar12 + fVar9;
          fVar51 = (fVar51 - fVar55) + fVar11;
          fVar1 = fVar1 + fVar2;
          fVar3 = fVar10 * fVar16 + fVar3;
          fVar10 = -(fVar3 * fVar14) + fVar10;
          pfVar25[1] = (fVar3 + fVar9) * fVar13;
          pfVar25[7] = (fVar9 - fVar3) * fVar6;
          pfVar25[3] = (fVar7 - fVar10) * fVar17;
          pfVar25[5] = (fVar10 + fVar7) * fVar4;
          pfVar25[2] = (fVar51 * fVar12 + fVar11) * fVar15;
          pfVar25[6] = (-(fVar51 * fVar12) + fVar11) * fVar5;
          pfVar25[4] = (fVar1 - fVar8) * fVar12;
          *pfVar25 = fVar1 + fVar8;
          pfVar25 = pfVar44;
        } while (pfVar44 != (float *)((int)register0x00002008 + -0x50));
        uVar53 = (ulonglong)uStack_70;
        pfVar25 = pfVar24 + -0x1f8;
        pfVar44 = local_d0;
        fVar55 = uStack_b4._4_4_;
        fVar51 = fStack_90;
        do {
          pfVar22 = pfVar25;
          fVar52 = (float)uVar53;
          fVar2 = fVar51 + fVar52;
          fVar51 = pfVar44[0x11];
          uVar53 = *(ulonglong *)(pfVar44 + 0x19);
          fVar3 = pfVar44[9];
          *pfVar22 = *pfVar44;
          *(ulonglong *)(pfVar22 + 0x12) = (ulonglong)(uint)(fVar2 + (float)uVar53);
          pfVar25 = pfVar22 + 0x48;
          pfVar22[0x24] = fVar3 + fVar55;
          pfVar22[0x36] = fVar51 + fVar52 + (float)uVar53;
          pfVar44 = pfVar44 + 1;
          fVar55 = fVar3;
        } while (pfVar25 != pfVar24);
        pfVar24 = pfVar22 + 0x49;
        *(ulonglong *)pfVar25 = CONCAT44(uStack_b4._4_4_,(undefined4)uStack_b4);
        *(ulonglong *)(pfVar22 + 0x5a) = (ulonglong)(uint)(fStack_74 + (float)uStack_54);
        pfVar22[0x7e] = (float)uStack_54;
        pfVar22[0x6c] = fStack_94;
      } while (pfVar27 != pfVar24);
      pfVar27 = pfVar22 + 0x289;
    } while ((float *)(param_2 + param_4 * 0x240 + param_3 + 0x1f8) != pfVar27);
  }
  memcpy(param_6,param_1,0xf00);
  fVar16 = DAT_ram_10434980;
  fVar14 = DAT_ram_1043497c;
  fVar12 = DAT_ram_1043493c;
  puVar45 = param_2 + (iVar41 + param_4) * 0x40 + -0x240;
  psVar42 = (short *)(param_5 + param_4 * 0x3e);
  psVar39 = (short *)(param_4 * 2 + param_5 + -2);
  psVar46 = (short *)(param_4 * 0x40 + param_5 + -2);
  puVar33 = (ulonglong *)((int)param_6 + 0xff0);
  pvVar30 = param_6;
  do {
    *puVar33 = (ulonglong)param_2[0x120];
    *(ulonglong *)((int)puVar33 + 4) = (ulonglong)puVar45[0x120];
    puVar33[1] = (ulonglong)*param_2;
    *(ulonglong *)((int)puVar33 + 0xc) = (ulonglong)*puVar45;
    *(uint *)(puVar33 + 0x20) = param_2[0x121];
    *(uint *)((int)puVar33 + 0x104) = puVar45[0x121];
    *(uint *)(puVar33 + 0x21) = param_2[1];
    *(uint *)((int)puVar33 + 0x10c) = puVar45[1];
    drmp3d_synth_pair(psVar39,param_4,(int)pvVar30 + 0xf4);
    drmp3d_synth_pair(psVar46 + param_4,param_4,(int)pvVar30 + 500);
    drmp3d_synth_pair(psVar39 + (1 - param_4),param_4,(int)pvVar30 + 0xf0);
    drmp3d_synth_pair(psVar46 + 1,param_4,(int)pvVar30 + 0x1f0);
    fVar17 = DAT_ram_10434980;
    fVar15 = DAT_ram_1043497c;
    fVar13 = DAT_ram_1043493c;
    psVar21 = psVar46 + param_4 + param_4 * 0x1f;
    psVar23 = psVar21 + param_4 * -0x1e;
    psVar38 = psVar42 + param_4 * 0x20;
    psVar26 = psVar38 + param_4 * -0x1e;
    psVar20 = psVar39 + 1;
    puVar35 = (uint *)((int)pvVar30 + 0xee8);
    puVar37 = (ulonglong *)((int)pvVar30 + 0xfe0);
    puVar18 = param_2 + 0x132;
    puVar50 = puVar45 + 0x132;
    puVar49 = param_2 + 0x10e;
    puVar48 = puVar45 + 0x10e;
    puVar47 = (undefined8 *)((int)pvVar30 + 0xe0);
    puVar19 = puVar33;
    pfVar27 = (float *)&g_win_21;
    pvVar36 = pvVar30;
    psVar40 = psVar39 + param_4;
    psVar43 = psVar23;
    local_130 = psVar26;
    do {
      puVar35[0x3e] = *puVar18;
      puVar35[0x3f] = *puVar50;
      puVar35[0x40] = puVar18[1];
      puVar35[0x41] = puVar50[1];
      puVar35[0x7e] = puVar49[1];
      puVar35[0x7f] = puVar48[1];
      *puVar35 = *puVar49;
      puVar35[1] = *puVar48;
      fVar4 = *pfVar27;
      fVar5 = pfVar27[1];
      pfVar24 = local_d0;
      puVar29 = puVar47;
      puVar34 = puVar37;
      pfVar25 = local_e0;
      do {
        uVar54 = *puVar29;
        uVar53 = *puVar34;
        puVar34 = (ulonglong *)((int)puVar34 + 4);
        puVar29 = (undefined8 *)((int)puVar29 + 4);
        *pfVar24 = fVar5 * (float)uVar53 + fVar4 * (float)uVar54;
        *pfVar25 = fVar4 * (float)uVar53 - fVar5 * (float)uVar54;
        pfVar24 = pfVar24 + 1;
        pfVar25 = pfVar25 + 1;
      } while (puVar19 != puVar34);
      fVar4 = pfVar27[2];
      uVar54 = *(undefined8 *)(pfVar27 + 3);
      puVar29 = puVar47;
      pfVar24 = local_d0;
      pfVar25 = local_e0;
      do {
        fVar5 = *(float *)(puVar29 + 0x20);
        fVar6 = *(float *)(puVar29 + 0x1c0);
        fVar51 = *pfVar25;
        pfVar44 = pfVar24 + 1;
        puVar29 = (undefined8 *)((int)puVar29 + 4);
        *pfVar24 = (float)uVar54 * fVar6 + fVar4 * fVar5 + *pfVar24;
        *pfVar25 = ((float)uVar54 * fVar5 - fVar4 * fVar6) + fVar51;
        pfVar24 = pfVar44;
        pfVar25 = pfVar25 + 1;
      } while ((float *)&uStack_c0 != pfVar44);
      fVar4 = pfVar27[4];
      fVar5 = pfVar27[5];
      puVar29 = puVar47;
      pfVar24 = local_d0;
      pfVar25 = local_e0;
      do {
        fVar6 = *(float *)(puVar29 + 0x40);
        fVar51 = *(float *)(puVar29 + 0x1a0);
        fVar55 = *pfVar25;
        pfVar44 = pfVar24 + 1;
        puVar29 = (undefined8 *)((int)puVar29 + 4);
        *pfVar24 = fVar5 * fVar51 + fVar4 * fVar6 + *pfVar24;
        *pfVar25 = (fVar4 * fVar51 - fVar5 * fVar6) + fVar55;
        pfVar24 = pfVar44;
        pfVar25 = pfVar25 + 1;
      } while ((float *)&uStack_c0 != pfVar44);
      fVar4 = pfVar27[6];
      uVar54 = *(undefined8 *)(pfVar27 + 7);
      puVar29 = puVar47;
      pfVar24 = local_d0;
      pfVar25 = local_e0;
      do {
        fVar5 = *(float *)(puVar29 + 0x60);
        fVar6 = *(float *)(puVar29 + 0x180);
        fVar51 = *pfVar25;
        pfVar44 = pfVar24 + 1;
        puVar29 = (undefined8 *)((int)puVar29 + 4);
        *pfVar24 = (float)uVar54 * fVar6 + fVar4 * fVar5 + *pfVar24;
        *pfVar25 = ((float)uVar54 * fVar5 - fVar4 * fVar6) + fVar51;
        pfVar24 = pfVar44;
        pfVar25 = pfVar25 + 1;
      } while ((float *)&uStack_c0 != pfVar44);
      fVar4 = pfVar27[8];
      fVar5 = pfVar27[9];
      pfVar44 = (float *)((int)pvVar36 + 0x4e0);
      pfVar24 = local_e0;
      pfVar25 = local_d0;
      do {
        fVar6 = *pfVar44;
        fVar51 = pfVar44[0x1c0];
        fVar55 = *pfVar24;
        pfVar22 = pfVar25 + 1;
        pfVar44 = pfVar44 + 1;
        *pfVar25 = fVar5 * fVar51 + fVar4 * fVar6 + *pfVar25;
        *pfVar24 = (fVar4 * fVar51 - fVar5 * fVar6) + fVar55;
        pfVar24 = pfVar24 + 1;
        pfVar25 = pfVar22;
      } while ((float *)&uStack_c0 != pfVar22);
      fVar4 = pfVar27[10];
      uVar54 = *(undefined8 *)(pfVar27 + 0xb);
      pfVar44 = (float *)((int)pvVar36 + 0x5e0);
      pfVar24 = local_e0;
      pfVar25 = local_d0;
      do {
        fVar5 = pfVar44[0x140];
        fVar6 = *pfVar44;
        fVar51 = *pfVar25;
        pfVar22 = pfVar25 + 1;
        pfVar44 = pfVar44 + 1;
        *pfVar24 = ((float)uVar54 * fVar6 - fVar4 * fVar5) + *pfVar24;
        *pfVar25 = (float)uVar54 * fVar5 + fVar4 * fVar6 + fVar51;
        pfVar24 = pfVar24 + 1;
        pfVar25 = pfVar22;
      } while ((float *)&uStack_c0 != pfVar22);
      fVar4 = pfVar27[0xc];
      fVar5 = pfVar27[0xd];
      pfVar44 = (float *)((int)pvVar36 + 0x6e0);
      pfVar24 = local_e0;
      pfVar25 = local_d0;
      do {
        fVar6 = *pfVar44;
        fVar51 = pfVar44[0xc0];
        fVar55 = *pfVar24;
        pfVar22 = pfVar25 + 1;
        pfVar44 = pfVar44 + 1;
        *pfVar25 = fVar5 * fVar51 + fVar4 * fVar6 + *pfVar25;
        *pfVar24 = (fVar4 * fVar51 - fVar5 * fVar6) + fVar55;
        pfVar24 = pfVar24 + 1;
        pfVar25 = pfVar22;
      } while ((float *)&uStack_c0 != pfVar22);
      fVar4 = pfVar27[0xe];
      puVar29 = (undefined8 *)((int)pvVar36 + 0x7e0);
      pfVar25 = pfVar27 + 0x10;
      fVar5 = pfVar27[0xf];
      pfVar27 = local_e0;
      pfVar24 = local_d0;
      do {
        fVar6 = *(float *)(puVar29 + 0x20);
        uVar54 = *puVar29;
        fVar51 = *pfVar24;
        pfVar44 = pfVar24 + 1;
        puVar29 = (undefined8 *)((int)puVar29 + 4);
        *pfVar27 = (fVar5 * (float)uVar54 - fVar4 * fVar6) + *pfVar27;
        *pfVar24 = fVar5 * fVar6 + fVar4 * (float)uVar54 + fVar51;
        pfVar27 = pfVar27 + 1;
        pfVar24 = pfVar44;
      } while ((float *)&uStack_c0 != pfVar44);
      if (fVar14 <= local_e0[1]) {
        sVar31 = 0x7fff;
      }
      else if (local_e0[1] <= fVar16) {
        sVar31 = -0x8000;
      }
      else {
        sVar31 = (short)(int)(local_e0[1] + fVar12) -
                 (short)(((int)(local_e0[1] + fVar12) & 0xffffU) >> 0xf);
      }
      *psVar40 = sVar31;
      if (fVar14 <= local_d0[1]) {
        sVar31 = 0x7fff;
      }
      else if (local_d0[1] <= fVar16) {
        sVar31 = -0x8000;
      }
      else {
        sVar31 = (short)(int)(local_d0[1] + fVar13) -
                 (short)(((int)(local_d0[1] + fVar13) & 0xffffU) >> 0xf);
      }
      *psVar46 = sVar31;
      if (fVar15 <= local_e0[0]) {
        sVar31 = 0x7fff;
      }
      else if (local_e0[0] <= fVar17) {
        sVar31 = -0x8000;
      }
      else {
        sVar31 = (short)(int)(local_e0[0] + fVar13) -
                 (short)(((int)(local_e0[0] + fVar13) & 0xffffU) >> 0xf);
      }
      *psVar20 = sVar31;
      if (fVar15 <= local_d0[0]) {
        sVar31 = 0x7fff;
      }
      else if (local_d0[0] <= fVar17) {
        sVar31 = -0x8000;
      }
      else {
        sVar31 = (short)(int)(local_d0[0] + fVar13) -
                 (short)(((int)(local_d0[0] + fVar13) & 0xffffU) >> 0xf);
      }
      *psVar42 = sVar31;
      if (fVar15 <= local_e0[3]) {
        sVar31 = 0x7fff;
      }
      else if (local_e0[3] <= fVar17) {
        sVar31 = -0x8000;
      }
      else {
        sVar31 = (short)(int)(local_e0[3] + fVar13) -
                 (short)(((int)(local_e0[3] + fVar13) & 0xffffU) >> 0xf);
      }
      *psVar43 = sVar31;
      if (fVar15 <= local_d0[3]) {
        sVar31 = 0x7fff;
      }
      else if (local_d0[3] <= fVar17) {
        sVar31 = -0x8000;
      }
      else {
        sVar31 = (short)(int)(local_d0[3] + fVar13) -
                 (short)(((int)(local_d0[3] + fVar13) & 0xffffU) >> 0xf);
      }
      *psVar21 = sVar31;
      fVar4 = DAT_ram_1043497c;
      if (fVar15 <= local_e0[2]) {
        sVar31 = 0x7fff;
      }
      else if (local_e0[2] <= fVar17) {
        sVar31 = -0x8000;
      }
      else {
        sVar31 = (short)(int)(local_e0[2] + DAT_ram_1043493c) -
                 (short)(((int)(local_e0[2] + DAT_ram_1043493c) & 0xffffU) >> 0xf);
      }
      *local_130 = sVar31;
      if (fVar4 <= local_d0[2]) {
        sVar31 = 0x7fff;
      }
      else if (local_d0[2] <= DAT_ram_10434980) {
        sVar31 = -0x8000;
      }
      else {
        sVar31 = (short)(int)(local_d0[2] + DAT_ram_1043493c) -
                 (short)(((int)(local_d0[2] + DAT_ram_1043493c) & 0xffffU) >> 0xf);
      }
      *psVar38 = sVar31;
      puVar18 = puVar18 + 0x12;
      puVar35 = puVar35 + -4;
      local_130 = local_130 + param_4;
      pvVar36 = (void *)((int)pvVar36 + -0x10);
      puVar50 = puVar50 + 0x12;
      puVar49 = puVar49 + -0x12;
      puVar48 = puVar48 + -0x12;
      psVar38 = psVar38 + -param_4;
      psVar21 = psVar21 + -param_4;
      psVar43 = psVar43 + param_4;
      psVar42 = psVar42 + -param_4;
      psVar20 = psVar20 + param_4;
      psVar46 = psVar46 + -param_4;
      psVar40 = psVar40 + param_4;
      puVar47 = puVar47 + -2;
      puVar37 = puVar37 + -2;
      puVar19 = puVar19 + -2;
      pfVar27 = pfVar25;
    } while (pfVar25 != (float *)&g_sec_22);
    psVar39 = psVar39 + param_4 + param_4 * 0x3f;
    pvVar30 = (void *)((int)pvVar30 + 0x200);
    psVar42 = psVar26 + param_4 * 0x3e;
    param_2 = param_2 + 2;
    puVar33 = puVar33 + 0x40;
    puVar45 = puVar45 + 2;
    psVar46 = psVar23 + param_4 * 0x3e;
  } while ((void *)((int)param_6 + (param_3 - 1U >> 1) * 0x200 + 0x200) != pvVar30);
  if (param_4 != 1) {
    memcpy(param_1,(void *)(param_3 * 0x100 + (int)param_6),0xf00);
    return;
  }
  puVar47 = (undefined8 *)(param_3 * 0x100 + (int)param_6);
  do {
    uVar54 = *puVar47;
    puVar47 = puVar47 + 1;
    *param_1 = (int)uVar54;
    param_1 = param_1 + 2;
  } while (puVar47 != (undefined8 *)(param_3 * 0x100 + 0xf00 + (int)param_6));
  return;
}


// ===== drmp3__on_read @ 104069c0 =====

int drmp3__on_read(int param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  
  gp = &__global_pointer_;
  if (param_1 == 0) {
                    /* WARNING: Subroutine does not return */
    __assert_fail(s_pMP3______void__0__ram_104173d0,s_dr_mp3_h_ram_104173c4,0xa4d,__func___16);
  }
  if (*(code **)(param_1 + 0x5980) == (code *)0x0) {
                    /* WARNING: Subroutine does not return */
    __assert_fail(s_pMP3_>onRead______void__0__ram_104173e4,s_dr_mp3_h_ram_104173c4,0xa4e,
                  __func___16);
  }
  iVar1 = 0;
  if (param_3 != 0) {
    iVar1 = (**(code **)(param_1 + 0x5980))(*(undefined4 *)(param_1 + 0x598c));
    uVar3 = *(uint *)(param_1 + 0x7dc0);
    uVar2 = uVar3 + iVar1;
    *(uint *)(param_1 + 0x7dc0) = uVar2;
    *(uint *)(param_1 + 0x7dc4) = (uint)(uVar2 < uVar3) + *(int *)(param_1 + 0x7dc4);
  }
  return iVar1;
}


// ===== drmp3__on_read_clamped @ 10406a80 =====

void drmp3__on_read_clamped(int param_1,undefined4 param_2,uint param_3)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  
  gp = &__global_pointer_;
  if (param_1 == 0) {
                    /* WARNING: Subroutine does not return */
    __assert_fail(s_pMP3______void__0__ram_104173d0,s_dr_mp3_h_ram_104173c4,0xa60,__func___17);
  }
  if (*(int *)(param_1 + 0x5980) == 0) {
                    /* WARNING: Subroutine does not return */
    __assert_fail(s_pMP3_>onRead______void__0__ram_104173e4,s_dr_mp3_h_ram_104173c4,0xa61,
                  __func___17);
  }
  uVar2 = *(uint *)(param_1 + 0x7dc8);
  iVar3 = *(int *)(param_1 + 0x7dcc);
  if (uVar2 == 0xffffffff) {
    if ((iVar3 == -1) ||
       (uVar1 = -*(int *)(param_1 + 0x7dc0) - 1, iVar3 != *(int *)(param_1 + 0x7dc4)))
    goto LAB_ram_10406aca;
  }
  else {
    uVar1 = uVar2 - *(int *)(param_1 + 0x7dc0);
    if (iVar3 - *(int *)(param_1 + 0x7dc4) != (uint)(uVar2 < uVar1)) goto LAB_ram_10406aca;
  }
  if (uVar1 < param_3) {
    param_3 = uVar1;
  }
LAB_ram_10406aca:
  drmp3__on_read(param_1,param_2,param_3);
  return;
}


// ===== drmp3__on_seek_memory @ 10406b80 =====

undefined4 drmp3__on_seek_memory(int param_1,uint param_2,int param_3)

{
  int iVar1;
  int iVar2;
  
  gp = &__global_pointer_;
  if (param_1 == 0) {
                    /* WARNING: Subroutine does not return */
    __assert_fail(s_pMP3______void__0__ram_104173d0,s_dr_mp3_h_ram_104173c4,0xd1e,__func___14);
  }
  iVar1 = (int)param_2 >> 0x1f;
  if (param_3 != 0) {
    if (param_3 == 1) {
      iVar2 = *(int *)(param_1 + 0x7e14);
    }
    else {
      if (param_3 != 2) {
                    /* WARNING: Subroutine does not return */
        __assert_fail(s___Invalid_seek_origin__ram_10417400,s_dr_mp3_h_ram_104173c4,0xd27,
                      __func___14);
      }
      iVar2 = *(int *)(param_1 + 0x7e10);
    }
    iVar1 = (uint)(iVar2 + param_2 < param_2) + iVar1;
    param_2 = iVar2 + param_2;
  }
  if ((iVar1 < 0) || (*(uint *)(param_1 + 0x7e10) < param_2)) {
    return 0;
  }
  *(uint *)(param_1 + 0x7e14) = param_2;
  return 1;
}


// ===== drmp3__on_read_memory @ 10406c40 =====

size_t drmp3__on_read_memory(int param_1,void *param_2,size_t param_3)

{
  uint uVar1;
  uint uVar2;
  
  gp = &__global_pointer_;
  if (param_1 == 0) {
                    /* WARNING: Subroutine does not return */
    __assert_fail(s_pMP3______void__0__ram_104173d0,s_dr_mp3_h_ram_104173c4,0xd09,__func___13);
  }
  uVar1 = *(uint *)(param_1 + 0x7e14);
  if (*(uint *)(param_1 + 0x7e10) < uVar1) {
                    /* WARNING: Subroutine does not return */
    __assert_fail(s_pMP3_>memory_dataSize_>__pMP3_>m_ram_10417418,s_dr_mp3_h_ram_104173c4,0xd0a,
                  __func___13);
  }
  uVar2 = *(uint *)(param_1 + 0x7e10) - uVar1;
  if (uVar2 <= param_3) {
    param_3 = uVar2;
  }
  if (param_3 == 0) {
    return 0;
  }
  memcpy(param_2,(void *)(*(int *)(param_1 + 0x7e0c) + uVar1),param_3);
  *(size_t *)(param_1 + 0x7e14) = *(int *)(param_1 + 0x7e14) + param_3;
  return param_3;
}


// ===== drmp3__free_default @ 10406d00 =====

void drmp3__free_default(int param_1)

{
  int iVar1;
  int *piVar2;
  uint uVar3;
  size_t __len;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  undefined8 uVar8;
  
  gp = &__global_pointer_;
  if (param_1 == 0) {
    return;
  }
  iVar1 = get_meta();
  uVar6 = *(uint *)(iVar1 + 0x14);
  uVar3 = *(byte *)(param_1 + -3) & 0x1f;
  uVar4 = 1 << uVar3;
  *(undefined1 *)(param_1 + -3) = 0xff;
  *(undefined2 *)(param_1 + -2) = 0;
  do {
    uVar5 = *(uint *)(iVar1 + 0x10);
    uVar7 = *(uint *)(iVar1 + 0xc) | uVar5;
    if ((uVar4 & uVar7) != 0) {
      uRam00000000 = 0;
      ebreak();
    }
    if ((uVar5 == 0) || (uVar7 + uVar4 == (2 << (uVar6 & 0x1f)) + -1)) {
      if (DAT_ram_1254be33 != '\0') {
        __lock(&__malloc_lock);
      }
      uVar8 = nontrivial_free(iVar1,uVar3);
      __len = (size_t)((ulonglong)uVar8 >> 0x20);
      __unlock(&__malloc_lock);
      if (__len == 0) {
        gp = &__global_pointer_;
        return;
      }
      piVar2 = __errno_location();
      iVar1 = *piVar2;
      munmap((void *)uVar8,__len);
      *piVar2 = iVar1;
      gp = &__global_pointer_;
      return;
    }
    if (DAT_ram_1254be33 == '\0') {
      *(uint *)(iVar1 + 0x10) = uVar4 + uVar5;
      gp = &__global_pointer_;
      return;
    }
    uVar7 = *(uint *)(iVar1 + 0x10);
    if (uVar7 == uVar5) {
      *(uint *)(iVar1 + 0x10) = uVar4 + uVar5;
    }
  } while (uVar5 != uVar7);
  return;
}


// ===== drmp3__realloc_default @ 10406d40 =====

void * drmp3__realloc_default(void *param_1,uint param_2)

{
  byte *pbVar1;
  int iVar2;
  int unaff_s1;
  void *pvVar3;
  void *__dest;
  int *piVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  char *pcVar9;
  undefined1 *puVar10;
  uint uVar11;
  uint uVar12;
  char *unaff_s2;
  uint uVar13;
  char unaff_s6;
  
  gp = &__global_pointer_;
  if (param_1 == (void *)0x0) {
    pvVar3 = (void *)__libc_malloc_impl(param_2);
    return pvVar3;
  }
  if (0x7fffeffe < param_2) {
    piVar4 = __errno_location();
    *piVar4 = 0xc;
    return (void *)0x0;
  }
  pvVar3 = param_1;
  if (((uint)param_1 & 0xf) == 0) goto LAB_ram_10410e44;
LAB_ram_10410e3e:
  do {
    do {
      do {
        do {
          uRam00000000 = 0;
          ebreak();
LAB_ram_10410e44:
          pbVar1 = (byte *)((int)pvVar3 + -3);
          uVar11 = (uint)*(ushort *)((int)pvVar3 + -2);
          uVar7 = *pbVar1 & 0x1f;
        } while ((*(char *)((int)pvVar3 + -4) != '\0') &&
                ((uVar11 != 0 || (uVar11 = *(uint *)((int)pvVar3 + -8), (int)uVar11 < 0x10000))));
        uVar13 = *(uint *)((int)param_1 + uVar11 * -0x10 + -0x10);
        pvVar3 = *(void **)(uVar13 + 8);
      } while ((void *)((int)param_1 + uVar11 * -0x10 + -0x10) != pvVar3);
      uVar6 = *(uint *)(uVar13 + 0x14);
    } while (((((uVar6 & 0x1f) < uVar7) || ((*(uint *)(uVar13 + 0xc) >> uVar7 & 1) != 0)) ||
             ((*(uint *)(uVar13 + 0x10) >> uVar7 & 1) != 0)) ||
            ((*(int *)(uVar13 & 0xfffff000) != __malloc_context ||
             (((int *)(uVar13 & 0xfffff000))[1] != DAT_ram_1254be6c))));
    uVar5 = uVar6 >> 6 & 0x3f;
    if (uVar5 < 0x30) {
      iVar2 = uVar7 * *(ushort *)(__malloc_size_classes + uVar5 * 2);
      if (((int)uVar11 < iVar2) ||
         ((int)((uint)*(ushort *)(__malloc_size_classes + uVar5 * 2) + iVar2) <= (int)uVar11))
      goto LAB_ram_10410e3e;
LAB_ram_10410ef2:
      if (uVar6 < 0x1000) {
LAB_ram_10410f0e:
        iVar2 = (uint)*(ushort *)(__malloc_size_classes + uVar5 * 2) << 4;
      }
      else {
        if ((uVar6 >> 0xc) * 0x100 - 1 < uVar11) goto LAB_ram_10410e3e;
        iVar2 = (uVar6 >> 0xc) * 0x1000 + -0x10;
        if ((uVar6 & 0x1f) != 0) goto LAB_ram_10410f0e;
      }
      uVar11 = (uint)(*pbVar1 >> 5);
      unaff_s1 = (int)pvVar3 + uVar7 * iVar2 + 0x10;
      pcVar9 = (char *)(iVar2 + -4 + unaff_s1);
      if (((4 < uVar11) &&
          (((uVar11 != 5 || (uVar11 = *(uint *)(pcVar9 + -4), uVar11 < 5)) || (pcVar9[-5] != '\0')))
          ) || (((uVar12 = (int)pcVar9 - (int)param_1, uVar12 < uVar11 ||
                 (unaff_s2 = pcVar9 + -uVar11, *unaff_s2 != '\0')) ||
                (unaff_s6 = *pcVar9, unaff_s6 != '\0')))) goto LAB_ram_10410e3e;
      if (uVar12 < param_2) goto LAB_ram_10411062;
      if (param_2 < 0x1ffec) {
        uVar11 = param_2 + 3 >> 4;
        if (uVar11 < 10) {
          if (uVar11 + 1 < uVar5) goto LAB_ram_10411000;
        }
        else {
          uVar11 = uVar11 + 1;
          uVar13 = uVar11 >> 2 | uVar11 >> 1;
          uVar13 = uVar13 | uVar13 >> 2;
          uVar13 = uVar13 | uVar13 >> 4;
          uVar13 = uVar13 | uVar13 >> 8;
          iVar2 = ((byte)debruijn32_0[(~uVar13 & uVar13 + 1) * 0x76be629 >> 0x1b] - 1) * 4;
          iVar8 = iVar2 + 1;
          if (*(ushort *)(__malloc_size_classes + iVar8 * 2) < uVar11) {
            iVar8 = iVar2 + 3;
            iVar2 = iVar2 + 2;
          }
          if ((int)(iVar8 + (uint)(*(ushort *)(__malloc_size_classes + iVar2 * 2) < uVar11)) <
              (int)uVar5) goto LAB_ram_10411000;
        }
        iVar2 = uVar12 - param_2;
        if (uVar12 != param_2) {
          pcVar9[-iVar2] = '\0';
          if (iVar2 < 5) {
            uVar7 = (*(byte *)((int)param_1 + -3) & 0x1f) + iVar2 * 0x20 & 0xff;
          }
          else {
            *(int *)(pcVar9 + -4) = iVar2;
            pcVar9[-5] = '\0';
            uVar7 = (*(byte *)((int)param_1 + -3) & 0x1f) - 0x60 & 0xff;
          }
        }
        *(char *)((int)param_1 + -3) = (char)uVar7;
        return param_1;
      }
      if (uVar5 < 0x30) goto LAB_ram_10411000;
    }
    else {
      if ((uVar6 & 0xfc0) == 0xfc0) goto LAB_ram_10410ef2;
      uRam00000000 = 0;
      ebreak();
LAB_ram_10411062:
      if ((uVar5 < 0x30) || (param_2 < 0x1ffec)) goto LAB_ram_10411000;
    }
    if ((uVar6 & 0xfc0) == 0xfc0) {
      uVar7 = (int)param_1 + ((param_2 + 0x1013) - unaff_s1);
      uVar11 = uVar7 & 0xfffff000;
      if ((uVar6 & 0xfffff000) != uVar11) {
        pvVar3 = mremap(pvVar3,uVar6 & 0xfffff000,uVar11,1);
      }
      if (pvVar3 == (void *)0xffffffff) {
LAB_ram_10411000:
        __dest = (void *)__libc_malloc_impl(param_2);
        if (__dest != (void *)0x0) {
          uVar7 = (int)unaff_s2 - (int)param_1;
          if (param_2 < (uint)((int)unaff_s2 - (int)param_1)) {
            uVar7 = param_2;
          }
          memcpy(__dest,param_1,uVar7);
          __libc_free(param_1);
        }
      }
      else {
        *(uint *)(uVar13 + 0x14) = *(uint *)(uVar13 + 0x14) & 0xfff | uVar7 & 0xfffff000;
        *(void **)(uVar13 + 8) = pvVar3;
        puVar10 = (undefined1 *)((int)pvVar3 + (uVar11 - 4));
        iVar8 = (int)param_1 + (param_2 - unaff_s1);
        *puVar10 = 0;
        __dest = (void *)((int)param_1 + (int)pvVar3 + (0x10 - unaff_s1));
        iVar2 = (uVar11 - 0x14) - iVar8;
        if (uVar11 - 0x14 != iVar8) {
          *(undefined1 *)((int)pvVar3 + iVar8 + 0x10) = 0;
          if (iVar2 < 5) {
            unaff_s6 = (char)iVar2 * ' ';
          }
          else {
            *(int *)(puVar10 + -4) = iVar2;
            puVar10[-5] = 0;
            unaff_s6 = -0x60;
          }
        }
        *(byte *)((int)__dest + -3) = unaff_s6 + (*(byte *)((int)__dest + -3) & 0x1f);
      }
      return __dest;
    }
  } while( true );
}


// ===== drmp3__malloc_default @ 10406d80 =====

uint drmp3__malloc_default(uint param_1)

{
  bool bVar1;
  int iVar2;
  int *piVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  int iVar10;
  undefined4 *puVar11;
  char cVar12;
  byte bVar13;
  
  gp = &__global_pointer_;
  if (0x7fffeffe < param_1) {
    piVar3 = __errno_location();
    *piVar3 = 0xc;
    return 0;
  }
  uVar6 = param_1;
  if (0x1ffeb < param_1) goto LAB_ram_1040d4ac;
  uVar6 = param_1 + 3 >> 4;
  if (9 < uVar6) {
    uVar6 = uVar6 + 1;
    uVar8 = uVar6 >> 2 | uVar6 >> 1;
    uVar8 = uVar8 | uVar8 >> 2;
    uVar8 = uVar8 | uVar8 >> 4;
    uVar8 = uVar8 | uVar8 >> 8;
    iVar2 = ((byte)debruijn32_0[(~uVar8 & uVar8 + 1) * 0x76be629 >> 0x1b] - 1) * 4;
    if (*(ushort *)(__malloc_size_classes + (iVar2 + 1) * 2) < uVar6) {
      iVar2 = iVar2 + 2;
    }
    uVar6 = iVar2 + (uint)(*(ushort *)(__malloc_size_classes + iVar2 * 2) < uVar6);
  }
  if (DAT_ram_1254be33 != '\0') {
    __lock(&__malloc_lock);
  }
  iVar2 = (&__malloc_context)[uVar6 + 0xc];
  uVar8 = uVar6;
  if (iVar2 != 0) goto LAB_ram_1040d402;
  if ((((uVar6 - 4 < 0x1c) && (uVar6 != 6)) && ((uVar6 & 1) == 0)) &&
     ((&__malloc_context)[uVar6 + 0x3c] == 0)) {
    uVar8 = uVar6 | 1;
    iVar2 = (&__malloc_context)[uVar8 + 0xc];
    uVar7 = (&__malloc_context)[uVar8 + 0x3c];
    if (iVar2 == 0) {
      if (uVar7 + 3 < 0xd) {
        uVar6 = uVar8;
      }
    }
    else if ((*(int *)(iVar2 + 0xc) == 0) && (*(int *)(iVar2 + 0x10) == 0)) {
      if (uVar7 + 3 < 0xd) goto LAB_ram_1040d402;
    }
    else if (uVar7 < 0xd) {
LAB_ram_1040d402:
      uVar7 = *(uint *)(iVar2 + 0xc);
      uVar9 = -uVar7 & uVar7;
      uVar6 = uVar8;
      if (uVar9 != 0) {
        *(uint *)(iVar2 + 0xc) = uVar7 - uVar9;
        uVar8 = (uint)(byte)debruijn32_0[(-uVar9 & uVar9) * 0x76be629 >> 0x1b];
        goto LAB_ram_1040d440;
      }
    }
  }
  uVar8 = alloc_slot(uVar6,param_1);
  if ((int)uVar8 < 0) {
    __unlock(&__malloc_lock);
    return 0;
  }
  iVar2 = (&__malloc_context)[uVar6 + 0xc];
LAB_ram_1040d440:
  while( true ) {
    uVar7 = DAT_ram_1254be74;
    __unlock(&__malloc_lock);
    uVar6 = *(uint *)(iVar2 + 0x14);
    if (((uVar6 & 0x1f) == 0) && (0xfff < uVar6)) {
      iVar10 = (uVar6 & 0xfffff000) - 0x10;
    }
    else {
      iVar10 = (uint)*(ushort *)(__malloc_size_classes + (uVar6 >> 5 & 0x7e)) << 4;
    }
    uVar4 = (iVar10 - param_1) - 4;
    iVar5 = *(int *)(iVar2 + 8) + 0x10;
    uVar9 = uVar4 >> 4;
    uVar6 = uVar8 * iVar10 + iVar5;
    iVar10 = iVar10 + -4 + uVar6;
    if (*(char *)(uVar6 - 3) != '\0') {
      uVar7 = *(ushort *)(uVar6 - 2) + 1;
    }
    uVar7 = uVar7 & 0xff;
    if ((*(char *)(uVar6 - 4) == '\0') &&
       (((uVar7 <= uVar9 ||
         (uVar4 = uVar4 >> 5 | uVar9, uVar4 = uVar4 | uVar4 >> 2,
         uVar7 = uVar7 & (uVar4 | uVar4 >> 4), uVar7 <= uVar9)) ||
        (uVar7 = (uVar7 - uVar9) - 1, uVar7 <= uVar9)))) {
      if (uVar7 != 0) {
        *(short *)(uVar6 - 2) = (short)uVar7;
        *(undefined1 *)(uVar6 - 3) = 0xe0;
        uVar6 = uVar6 + uVar7 * 0x10;
        *(undefined1 *)(uVar6 - 4) = 0;
        iVar5 = *(int *)(iVar2 + 8) + 0x10;
      }
      bVar13 = (byte)uVar8;
      *(short *)(uVar6 - 2) = (short)(uVar6 - iVar5 >> 4);
      *(byte *)(uVar6 - 3) = bVar13;
      iVar2 = (iVar10 - uVar6) - param_1;
      cVar12 = '\0';
      if (iVar10 - uVar6 != param_1) {
        *(undefined1 *)(iVar10 - iVar2) = 0;
        if (iVar2 < 5) {
          cVar12 = (char)iVar2 * ' ';
          bVar13 = *(byte *)(uVar6 - 3);
        }
        else {
          *(int *)(iVar10 + -4) = iVar2;
          *(undefined1 *)(iVar10 + -5) = 0;
          bVar13 = *(byte *)(uVar6 - 3);
          cVar12 = -0x60;
        }
      }
      *(byte *)(uVar6 - 3) = cVar12 + (bVar13 & 0x1f);
      return uVar6;
    }
    uRam00000000 = 0;
    ebreak();
LAB_ram_1040d4ac:
    piVar3 = mmap((void *)0x0,uVar6 + 0x14,3,0x22,-1,0);
    if (piVar3 == (int *)0xffffffff) {
      return 0;
    }
    if (DAT_ram_1254be33 != '\0') {
      __lock(&__malloc_lock);
    }
    bVar1 = DAT_ram_1254c058 == -1;
    DAT_ram_1254c058 = DAT_ram_1254c058 + '\x01';
    if (bVar1) {
      puVar11 = &__malloc_context;
      do {
        puVar11[0x6c] = 0;
        puVar11 = puVar11 + 1;
      } while (puVar11 != &DAT_ram_1254be88);
      DAT_ram_1254c058 = '\x01';
    }
    iVar2 = __malloc_alloc_meta();
    if (iVar2 == 0) break;
    *(int **)(iVar2 + 8) = piVar3;
    *piVar3 = iVar2;
    *(undefined4 *)(iVar2 + 0x10) = 0;
    *(undefined4 *)(iVar2 + 0xc) = 0;
    DAT_ram_1254be74 = DAT_ram_1254be74 + 1;
    *(uint *)(iVar2 + 0x14) = param_1 + 0x1013 & 0xfffff000 | 0xfe0;
    uVar8 = 0;
  }
  __unlock(&__malloc_lock);
  munmap(piVar3,uVar6 + 0x14);
  return 0;
}


// ===== cmpstr @ 10406dc0 =====

int cmpstr(char *__s1,char *__s2)

{
  byte bVar1;
  uint uVar2;
  
  gp = &__global_pointer_;
  do {
    uVar2 = (uint)(byte)*__s1;
    bVar1 = *__s2;
    if (uVar2 != bVar1) break;
    __s1 = __s1 + 1;
    __s2 = __s2 + 1;
  } while (uVar2 != 0);
  return uVar2 - bVar1;
}


// ===== add_unique @ 10406e00 =====

void add_unique(char *param_1,int *param_2,char *param_3)

{
  int iVar1;
  char *__s1;
  int iVar2;
  int iVar3;
  
  gp = &__global_pointer_;
  iVar3 = *param_2;
  if (0 < iVar3) {
    iVar1 = 0;
    __s1 = param_1;
    do {
      iVar2 = strcmp(__s1,param_3);
      iVar1 = iVar1 + 1;
      if (iVar2 == 0) {
        return;
      }
      __s1 = __s1 + 0x50;
    } while (iVar1 != iVar3);
    if (0x1ff < iVar3) {
      return;
    }
  }
  snprintf(param_1 + iVar3 * 0x50,0x50,&DAT_ram_10417450,param_3);
  *param_2 = *param_2 + 1;
  return;
}


// ===== nav_push @ 10406ec0 =====

void nav_push(uint param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  char *pcVar5;
  
  gp = &__global_pointer_;
  if (0xb < navdepth) {
    return;
  }
  iVar3 = navdepth + 1;
  (&nav)[navdepth * 4] = param_1;
  (&DAT_ram_104d4434)[navdepth * 4] = 0;
  (&DAT_ram_104d4438)[navdepth * 4] = 0;
  (&DAT_ram_104d443c)[navdepth * 4] = param_2;
  iVar1 = ntracks;
  navdepth = iVar3;
  if ((0x12U >> (param_1 & 0x1f) & 1) == 0) {
    if ((param_1 == 5) && (curlen = 0, 0 < ntracks)) {
      pcVar5 = tracks + 0xe0;
      iVar3 = 0;
      do {
        iVar2 = strcmp(pcVar5,albums + param_2 * 0x50);
        if (iVar2 == 0) {
          piVar4 = &curlist + curlen;
          curlen = curlen + 1;
          *piVar4 = iVar3;
        }
        iVar3 = iVar3 + 1;
        pcVar5 = pcVar5 + 0x138;
      } while (iVar3 != iVar1);
    }
  }
  else {
    curlen = 0;
    if (param_1 == 1) {
      if (0 < ntracks) {
        piVar4 = &curlist;
        curlen = 0;
        do {
          *piVar4 = curlen;
          curlen = curlen + 1;
          piVar4 = piVar4 + 1;
        } while (curlen != iVar1);
        return;
      }
    }
    else if (0 < ntracks) {
      pcVar5 = tracks + 0x90;
      iVar3 = 0;
      do {
        iVar2 = strcmp(pcVar5,artists + param_2 * 0x50);
        if (iVar2 == 0) {
          piVar4 = &curlist + curlen;
          curlen = curlen + 1;
          *piVar4 = iVar3;
        }
        iVar3 = iVar3 + 1;
        pcVar5 = pcVar5 + 0x138;
      } while (iVar3 != iVar1);
    }
  }
  return;
}


// ===== open_any @ 10407100 =====

void open_any(char *param_1)

{
  char *pcVar1;
  FILE *pFVar2;
  char *pcVar3;
  char cVar4;
  char acStack_120 [96];
  char acStack_c0 [172];
  
  gp = &__global_pointer_;
  snprintf(acStack_c0,0xa0,s__s__s_ram_1041745c,s__music_ram_10417454,param_1);
  pFVar2 = fopen(acStack_c0,&DAT_ram_10417464);
  if (pFVar2 == (FILE *)0x0) {
    cVar4 = *param_1;
    pcVar1 = acStack_120;
    pcVar3 = param_1;
    while (cVar4 != '\0') {
      pcVar3 = pcVar3 + 1;
      if ((byte)(cVar4 + 0x9fU) < 0x1a) {
        cVar4 = cVar4 + -0x20;
      }
      *pcVar1 = cVar4;
      pcVar1 = pcVar1 + 1;
      cVar4 = *pcVar3;
    }
    *pcVar1 = '\0';
    snprintf(acStack_c0,0xa0,s__s__s_ram_1041745c,s__music_ram_10417454,acStack_120);
    pFVar2 = fopen(acStack_c0,&DAT_ram_10417464);
    if (pFVar2 == (FILE *)0x0) {
      snprintf(acStack_c0,0xa0,s__s__s_1_ram_10417468,s__music_ram_10417454,acStack_120);
      pFVar2 = fopen(acStack_c0,&DAT_ram_10417464);
      if ((pFVar2 == (FILE *)0x0) &&
         (pFVar2 = fopen(param_1,&DAT_ram_10417464), pFVar2 == (FILE *)0x0)) {
        snprintf(acStack_c0,0xa0,&DAT_ram_10417470,param_1);
        fopen(acStack_c0,&DAT_ram_10417464);
      }
    }
  }
  return;
}


// ===== label_of @ 10407240 =====

undefined1 * label_of(int param_1,undefined4 *param_2)

{
  int iVar1;
  char *pcVar2;
  char *param4;
  
  gp = &__global_pointer_;
  switch(*param_2) {
  case 0:
    return (&MAIN_ITEMS)[param_1];
  default:
    return (undefined1 *)((&curlist)[param_1] * 0x138 + 0x104e8530);
  case 2:
    return artists + param_1 * 0x50;
  case 3:
    return albums + param_1 * 0x50;
  case 6:
    pcVar2 = (char *)ui_theme_name();
    snprintf(buf_0,0x30,s_Theme___s_ram_10417478,pcVar2);
    break;
  case 7:
    pcVar2 = (&IPOD_THEMES)[param_1 * 0xc];
    iVar1 = ui_theme_index();
    param4 = &DAT_ram_104174c0;
    if (iVar1 == param_1) {
      param4 = &DAT_ram_10417474;
    }
    snprintf(buf_0,0x30,&DAT_ram_10417484,pcVar2,param4);
    break;
  case 8:
    return *(undefined1 **)(&GAMES)[param_1];
  }
  return buf_0;
}


// ===== drmp3__realloc_from_callbacks @ 10407380 =====

void * drmp3__realloc_from_callbacks
                 (void *param_1,undefined4 param_2,size_t param_3,undefined4 *param_4)

{
  void *pvVar1;
  
  gp = &__global_pointer_;
  if ((code *)param_4[2] != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x10407386. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    pvVar1 = (void *)(*(code *)param_4[2])(param_1,param_2,*param_4);
    return pvVar1;
  }
  if (((code *)param_4[1] == (code *)0x0) || (param_4[3] == 0)) {
    return (void *)0x0;
  }
  pvVar1 = (void *)(*(code *)param_4[1])(param_2,*param_4);
  if ((pvVar1 != (void *)0x0) && (param_1 != (void *)0x0)) {
    memcpy(pvVar1,param_1,param_3);
    (*(code *)param_4[3])(param_1,*param_4);
  }
  return pvVar1;
}


// ===== drmp3__on_tell_memory @ 10407400 =====

undefined4 drmp3__on_tell_memory(int param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  
  gp = &__global_pointer_;
  if (param_1 == 0) {
                    /* WARNING: Subroutine does not return */
    __assert_fail(s_pMP3______void__0__ram_104173d0,s_dr_mp3_h_ram_104173c4,0xd3d,__func___15);
  }
  if (param_2 == (undefined4 *)0x0) {
                    /* WARNING: Subroutine does not return */
    __assert_fail(s_pCursor______void__0__ram_1041748c,s_dr_mp3_h_ram_104173c4,0xd3e,__func___15);
  }
  uVar1 = *(undefined4 *)(param_1 + 0x7e14);
  param_2[1] = 0;
  *param_2 = uVar1;
  return 1;
}


// ===== np_scrolling.part.0 @ 10407480 =====

bool np_scrolling_part_0(void)

{
  int iVar1;
  int iVar2;
  
  gp = &__global_pointer_;
  iVar1 = (&queue)[qpos] * 0x138;
  iVar2 = ui_text_w(iVar1 + 0x104e8530);
  if ((iVar2 < 0x189) && (iVar2 = ui_text_w(iVar1 + 0x104e8580), iVar2 < 0x189)) {
    iVar1 = ui_text_w(iVar1 + 0x104e85d0);
    return 0x188 < iVar1;
  }
  return true;
}


// ===== frame_count.isra.0 @ 10407540 =====

undefined4 frame_count_isra_0(undefined4 param_1)

{
  gp = &__global_pointer_;
  switch(param_1) {
  case 0:
    return 7;
  default:
    return curlen;
  case 2:
    return nartists;
  case 3:
    return nalbums;
  case 6:
    return 1;
  case 7:
    return IPOD_NTHEMES;
  case 8:
    return 4;
  }
}


// ===== drmp3_hdr_frame_bytes @ 104075c0 =====

uint drmp3_hdr_frame_bytes(int param_1,uint param_2)

{
  byte bVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  
  gp = &__global_pointer_;
  bVar1 = *(byte *)(param_1 + 1);
  uVar3 = (uint)bVar1;
  iVar2 = 0x180;
  if ((uVar3 & 6) != 6) {
    iVar2 = (-(uint)((uVar3 & 0xe) != 2) & 0x240) + 0x240;
  }
  uVar5 = (uVar3 & 8) >> 3;
  uVar4 = (*(uint *)(g_hz_48 + (*(byte *)(param_1 + 2) & 0xc)) >> (uVar5 ^ 1)) >>
          (bVar1 >> 4 & 1 ^ 1);
  if (uVar4 == 0) {
    uVar4 = 0xffffffff;
  }
  else {
    uVar4 = ((uint)(byte)halfrate_47
                         [(uint)(*(byte *)(param_1 + 2) >> 4) +
                          ((bVar1 >> 1 & 3) - 1) * 0xf + (((uVar3 & 8) >> 2) + uVar5) * 0xf] * 2 *
             iVar2 * 0x7d) / uVar4;
  }
  if ((uVar3 & 6) == 6) {
    uVar4 = uVar4 & 0xfffffffc;
  }
  if (uVar4 == 0) {
    uVar4 = param_2;
  }
  return uVar4;
}


// ===== drmp3_hdr_compare @ 104076c0 =====

bool drmp3_hdr_compare(int param_1,char *param_2)

{
  byte bVar1;
  byte bVar2;
  
  gp = &__global_pointer_;
  if (*param_2 == -1) {
    bVar1 = param_2[1];
    if ((bVar1 & 0xf0) == 0xf0) {
      if ((bVar1 & 6) == 0) {
        return false;
      }
    }
    else if ((bVar1 & 0xfe) != 0xe2) {
      return false;
    }
    bVar2 = param_2[2];
    if ((((bVar2 >> 4 != 0xf) && ((bVar2 & 0xc) != 0xc)) && ((bVar1 ^ *(byte *)(param_1 + 1)) < 2))
       && (((*(byte *)(param_1 + 2) ^ bVar2) & 0xc) == 0)) {
      return 0xf < *(byte *)(param_1 + 2) != bVar2 < 0x10;
    }
  }
  return false;
}


// ===== render_np @ 10407780 =====

void render_np(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  UDItype UVar5;
  char acStack_18 [8];
  
  gp = &__global_pointer_;
  uVar2 = (**(code **)(_of_svc_ptr + 0x10))();
  uVar3 = DAT_ram_104d3c18;
  iVar4 = qpos;
  if (P == 0) {
    uVar3 = ui_bg();
    ui_clear(uVar2,uVar3);
    ui_status_bar(uVar2,s_Now_Playing_ram_10417390,100);
    uVar3 = ui_fg();
    ui_text(uVar2,0x12,0xdc,s_Nothing_playing_ram_104174a4,uVar3);
  }
  else {
    iVar1 = (&queue)[qpos] * 0x138;
    UVar5 = __udivdi3(CONCAT44(DAT_ram_104d3c14,DAT_ram_104d3c10),48000);
    ui_now_playing(uVar2,iVar1 + 0x104e8530,iVar1 + 0x104e8580,iVar1 + 0x104e85d0,iVar4 + 1,qlen,
                   (int)UVar5,uVar3,DAT_ram_104d3c1c,100,DAT_ram_104cbdec,param_1);
    ecall();
    if (g_vol_until != 0) {
      uVar3 = ui_bg(0,0,0,0,0,g_vol_until,3,0xc0de0006);
      ui_fill(uVar2,0x10,0x174,0x260,0x5a,uVar3);
      uVar3 = ui_fg();
      ui_text(uVar2,0x20,0x180,s_Volume_ram_104174b4,uVar3);
      snprintf(acStack_18,8,&DAT_ram_104174bc,g_vol);
      uVar3 = ui_fg();
      ui_text_right(uVar2,0x260,0x180,acStack_18,uVar3);
      uVar3 = ui_fg();
      ui_fill(uVar2,0x22,0x1aa,0x23c,0x16,uVar3);
      uVar3 = ui_bg();
      ui_fill(uVar2,0x24,0x1ac,0x238,0x12,uVar3);
      iVar4 = g_vol * 0x238;
      uVar3 = ui_fg();
      ui_fill(uVar2,0x24,0x1ac,iVar4 / 100,0x12,uVar3);
    }
  }
                    /* WARNING: Could not recover jumptable at 0x10407864. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(_of_svc_ptr + 0x14))();
  return;
}


// ===== drmp3_decode_next_frame_ex @ 10409740 =====

int drmp3_decode_next_frame_ex
              (int param_1,undefined4 param_2,uint *param_3,int *param_4,undefined4 param_5,
              uint param_6)

{
  void *__dest;
  int iVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  uint uStack_44;
  uint uStack_40;
  uint uStack_3c;
  uint uStack_38;
  uint uStack_34;
  
  gp = &__global_pointer_;
  iVar4 = *(int *)(param_1 + 0x7e0c);
  if ((iVar4 == 0) || (iVar1 = *(int *)(param_1 + 0x7e10), iVar1 == 0)) {
    if (*(int *)(param_1 + 0x5980) == 0) {
                    /* WARNING: Subroutine does not return */
      __assert_fail(s_pMP3_>onRead______void__0__ram_104173e4,s_dr_mp3_h_ram_104173c4,0xab4,
                    __func___18);
    }
    if (*(int *)(param_1 + 0x7e08) == 0) {
      uVar2 = *(uint *)(param_1 + 0x7df8);
      while( true ) {
        do {
          if (uVar2 < 0x4000) {
            __dest = *(void **)(param_1 + 0x7e04);
            iVar4 = 0;
            if (__dest != (void *)0x0) {
              memmove(__dest,(void *)((int)__dest + *(int *)(param_1 + 0x7e00)),uVar2);
              iVar4 = *(int *)(param_1 + 0x7e04);
            }
            uVar2 = *(uint *)(param_1 + 0x7dfc);
            *(undefined4 *)(param_1 + 0x7e00) = 0;
            if (uVar2 < 0x10000) {
              iVar4 = drmp3__realloc_from_callbacks(iVar4,0x10000,uVar2,param_1 + 0x5994);
              if (iVar4 == 0) {
                return 0;
              }
              *(int *)(param_1 + 0x7e04) = iVar4;
              *(undefined4 *)(param_1 + 0x7dfc) = 0x10000;
              uVar2 = 0x10000;
            }
            iVar4 = drmp3__on_read_clamped
                              (param_1,iVar4 + *(int *)(param_1 + 0x7df8),
                               uVar2 - *(int *)(param_1 + 0x7df8));
            if (iVar4 == 0 && *(int *)(param_1 + 0x7df8) == 0) goto LAB_ram_104098dc;
            uVar2 = iVar4 + *(int *)(param_1 + 0x7df8);
            *(uint *)(param_1 + 0x7df8) = uVar2;
          }
          if ((int)uVar2 < 0) goto LAB_ram_104098dc;
          if (*(int *)(param_1 + 0x7e04) == 0) {
                    /* WARNING: Subroutine does not return */
            __assert_fail(s_pMP3_>pData______void__0__ram_104174c4,s_dr_mp3_h_ram_104173c4,0xae7,
                          __func___18);
          }
          if (*(int *)(param_1 + 0x7dfc) == 0) {
                    /* WARNING: Subroutine does not return */
            __assert_fail(s_pMP3_>dataCapacity_>_0_ram_104174e0,s_dr_mp3_h_ram_104173c4,0xae8,
                          __func___18);
          }
          iVar4 = drmp3dec_decode_frame
                            (param_1,*(int *)(param_1 + 0x7e00) + *(int *)(param_1 + 0x7e04),uVar2,
                             param_2,&uStack_44);
          iVar5 = *(int *)(param_1 + 0x7e00);
          iVar1 = iVar5 + uStack_44;
          uVar2 = *(int *)(param_1 + 0x7df8) - uStack_44;
          *(int *)(param_1 + 0x7e00) = iVar1;
          *(uint *)(param_1 + 0x7df8) = uVar2;
          if (iVar4 != 0) {
            iVar4 = 0x180;
            if ((*(byte *)(param_1 + 0x1809) & 6) != 6) {
              iVar4 = (-(uint)((*(byte *)(param_1 + 0x1809) & 0xe) != 2) & 0x240) + 0x240;
            }
            *(undefined4 *)(param_1 + 0x59ac) = 0;
            *(int *)(param_1 + 0x59b0) = iVar4;
            *(uint *)(param_1 + 0x59a4) = uStack_40;
            *(uint *)(param_1 + 0x59a8) = uStack_3c;
            if (param_3 != (uint *)0x0) {
              param_3[1] = uStack_40;
              param_3[2] = uStack_3c;
              *param_3 = uStack_44;
              param_3[3] = uStack_38;
              param_3[4] = uStack_34;
            }
            if (param_4 == (int *)0x0) {
              return iVar4;
            }
            *param_4 = *(int *)(param_1 + 0x7e04) + iVar5;
            return iVar4;
          }
        } while (uStack_44 != 0);
        memmove(*(void **)(param_1 + 0x7e04),(void *)(iVar1 + (int)*(void **)(param_1 + 0x7e04)),
                uVar2);
        iVar1 = *(int *)(param_1 + 0x7dfc);
        iVar5 = *(int *)(param_1 + 0x7df8);
        *(undefined4 *)(param_1 + 0x7e00) = 0;
        iVar4 = *(int *)(param_1 + 0x7e04);
        if (iVar1 == iVar5) {
          iVar1 = iVar1 + 0x10000;
          iVar4 = drmp3__realloc_from_callbacks();
          if (iVar4 == 0) {
            return 0;
          }
          iVar5 = *(int *)(param_1 + 0x7df8);
          *(int *)(param_1 + 0x7e04) = iVar4;
          *(int *)(param_1 + 0x7dfc) = iVar1;
        }
        iVar4 = drmp3__on_read_clamped(param_1,iVar4 + iVar5,iVar1 - iVar5);
        if (iVar4 == 0) break;
        uVar2 = iVar4 + *(int *)(param_1 + 0x7df8);
        *(uint *)(param_1 + 0x7df8) = uVar2;
      }
LAB_ram_104098dc:
      *(undefined4 *)(param_1 + 0x7e08) = 1;
      return 0;
    }
  }
  else if (*(int *)(param_1 + 0x7e08) == 0) {
    iVar5 = *(int *)(param_1 + 0x7e14);
    while( true ) {
      uStack_44 = param_6;
      iVar4 = drmp3dec_decode_frame(param_1,iVar5 + iVar4,iVar1 - iVar5,param_2,&uStack_44);
      iVar6 = *(int *)(param_1 + 0x7e14);
      iVar3 = *(int *)(param_1 + 0x7dc0);
      iVar1 = *(int *)(param_1 + 0x7dc4);
      iVar5 = iVar6 + uStack_44;
      if (iVar4 != 0) break;
      iVar4 = 0;
      if ((int)uStack_44 < 1) goto LAB_ram_104099aa;
      uVar2 = iVar3 + uStack_44;
      *(uint *)(param_1 + 0x7dc4) = (uint)(uVar2 < uStack_44) + iVar1;
      iVar1 = *(int *)(param_1 + 0x7e10);
      iVar4 = *(int *)(param_1 + 0x7e0c);
      *(uint *)(param_1 + 0x7dc0) = uVar2;
      *(int *)(param_1 + 0x7e14) = iVar5;
      param_6 = uStack_44;
    }
    iVar4 = 0x180;
    if ((*(byte *)(param_1 + 0x1809) & 6) != 6) {
      iVar4 = (-(uint)((*(byte *)(param_1 + 0x1809) & 0xe) != 2) & 0x240) + 0x240;
    }
    *(undefined4 *)(param_1 + 0x59ac) = 0;
    *(int *)(param_1 + 0x59b0) = iVar4;
    *(uint *)(param_1 + 0x59a4) = uStack_40;
    *(uint *)(param_1 + 0x59a8) = uStack_3c;
    if (param_3 != (uint *)0x0) {
      param_3[1] = uStack_40;
      param_3[2] = uStack_3c;
      *param_3 = uStack_44;
      param_3[3] = uStack_38;
      param_3[4] = uStack_34;
    }
    if (param_4 != (int *)0x0) {
      *param_4 = iVar6 + *(int *)(param_1 + 0x7e0c);
    }
LAB_ram_104099aa:
    uVar2 = iVar3 + uStack_44;
    *(uint *)(param_1 + 0x7dc4) = (uint)(uVar2 < uStack_44) + iVar1;
    *(int *)(param_1 + 0x7e14) = iVar5;
    *(uint *)(param_1 + 0x7dc0) = uVar2;
    return iVar4;
  }
  return 0;
}


// ===== drmp3_read_pcm_frames_raw.part.0 @ 10409ac0 =====

undefined8 drmp3_read_pcm_frames_raw_part_0(int param_1,uint param_2,int param_3,int param_4)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  uint uVar10;
  int iVar11;
  
  gp = &__global_pointer_;
  if (param_2 == 0 && param_3 == 0) {
    iVar11 = param_3;
LAB_ram_10409cc2:
    return CONCAT44(iVar11,param_2);
  }
  iVar11 = 0;
  uVar6 = param_2;
  uVar2 = 0;
  do {
    uVar8 = *(uint *)(param_1 + 0x7db8);
    uVar7 = *(uint *)(param_1 + 0x7de0);
    uVar10 = *(uint *)(param_1 + 0x59b0);
    if ((*(int *)(param_1 + 0x7dbc) == 0) && (uVar8 < uVar7)) {
      uVar3 = uVar7 - uVar8;
      if ((uVar3 <= uVar7) && (uVar3 < uVar10)) {
        *(uint *)(param_1 + 0x7db8) = uVar7;
        uVar10 = uVar10 + (uVar8 - uVar7);
        *(uint *)(param_1 + 0x59b0) = uVar10;
        *(uint *)(param_1 + 0x59ac) = uVar3 + *(int *)(param_1 + 0x59ac);
        goto LAB_ram_10409cea;
      }
      *(uint *)(param_1 + 0x7dbc) = (uint)(uVar8 + uVar10 < uVar8);
      *(uint *)(param_1 + 0x7db8) = uVar8 + uVar10;
      *(uint *)(param_1 + 0x59ac) = uVar10 + *(int *)(param_1 + 0x59ac);
      *(undefined4 *)(param_1 + 0x59b0) = 0;
      uVar10 = 0;
      uVar7 = 0;
LAB_ram_10409b88:
      uVar8 = *(uint *)(param_1 + 0x7de8);
      iVar9 = *(int *)(param_1 + 0x7dec);
      if (uVar8 != 0xffffffff) goto LAB_ram_10409b94;
LAB_ram_10409d02:
      if (iVar9 != -1) goto LAB_ram_10409b94;
LAB_ram_10409d06:
      uVar1 = uVar7;
      iVar9 = 0;
    }
    else {
LAB_ram_10409cea:
      if ((param_3 == 0) && (uVar7 = uVar6, uVar6 < uVar10)) goto LAB_ram_10409b88;
      uVar8 = *(uint *)(param_1 + 0x7de8);
      iVar9 = *(int *)(param_1 + 0x7dec);
      uVar7 = uVar10;
      if (uVar8 == 0xffffffff) goto LAB_ram_10409d02;
LAB_ram_10409b94:
      if ((iVar9 == 0) && (uVar8 <= *(uint *)(param_1 + 0x7de4))) goto LAB_ram_10409d06;
      uVar4 = uVar8 - *(uint *)(param_1 + 0x7de4);
      uVar3 = *(uint *)(param_1 + 0x7dbc);
      uVar8 = iVar9 - (uint)(uVar8 < uVar4);
      if ((uVar8 <= uVar3) &&
         ((param_2 = uVar2, uVar8 != uVar3 || (uVar4 <= *(uint *)(param_1 + 0x7db8)))))
      goto LAB_ram_10409cc2;
      uVar1 = uVar4 - *(uint *)(param_1 + 0x7db8);
      iVar9 = (uVar8 - uVar3) - (uint)(uVar4 < uVar1);
      if ((uVar8 - uVar3 != (uint)(uVar4 < uVar1)) || (uVar7 <= uVar1)) goto LAB_ram_10409d06;
    }
    if (param_4 != 0) {
      iVar5 = *(int *)(param_1 + 0x5978) * 2;
      memcpy((void *)(iVar5 * uVar2 + param_4),
             (void *)(*(int *)(param_1 + 0x59a4) * *(int *)(param_1 + 0x59ac) * 2 + param_1 + 0x59b4
                     ),uVar1 * iVar5);
      uVar10 = *(uint *)(param_1 + 0x59b0);
    }
    uVar3 = *(int *)(param_1 + 0x7db8) + uVar1;
    uVar7 = uVar6 - uVar1;
    uVar8 = (uint)(uVar3 < uVar1) + *(int *)(param_1 + 0x7dbc) + iVar9;
    param_3 = (param_3 - iVar9) - (uint)(uVar6 < uVar7);
    param_2 = uVar1 + uVar2;
    *(uint *)(param_1 + 0x7db8) = uVar3;
    *(uint *)(param_1 + 0x7dbc) = uVar8;
    *(uint *)(param_1 + 0x59b0) = uVar10 - uVar1;
    *(uint *)(param_1 + 0x59ac) = *(int *)(param_1 + 0x59ac) + uVar1;
    iVar11 = (uint)(param_2 < uVar2) + iVar9 + iVar11;
    if (uVar7 == 0 && param_3 == 0) goto LAB_ram_10409cc2;
    uVar6 = *(uint *)(param_1 + 0x7de8);
    iVar9 = *(int *)(param_1 + 0x7dec);
    if (((uVar6 != 0xffffffff) || (iVar9 != -1)) &&
       ((iVar9 != 0 || (*(uint *)(param_1 + 0x7de4) < uVar6)))) {
      uVar2 = uVar6 - *(uint *)(param_1 + 0x7de4);
      uVar6 = iVar9 - (uint)(uVar6 < uVar2);
      if ((uVar6 <= uVar8) && ((uVar6 != uVar8 || (uVar2 <= uVar3)))) goto LAB_ram_10409cc2;
    }
    if (uVar10 - uVar1 != 0) {
                    /* WARNING: Subroutine does not return */
      __assert_fail(s_pMP3_>pcmFramesRemainingInMP3Fra_ram_104174f8,s_dr_mp3_h_ram_104173c4,0x109a,
                    __func___12);
    }
    iVar9 = drmp3_decode_next_frame_ex(param_1,param_1 + 0x59b4,0,0);
    uVar6 = uVar7;
    uVar2 = param_2;
    if (iVar9 == 0) goto LAB_ram_10409cc2;
  } while( true );
}


// ===== drmp3_init_internal @ 10409e00 =====

undefined4
drmp3_init_internal(int param_1,code *param_2,code *param_3,code *param_4,int param_5,
                   undefined4 param_6,undefined4 param_7,undefined4 *param_8)

{
  byte bVar1;
  uint uVar2;
  undefined1 *puVar3;
  undefined4 *puVar4;
  int iVar5;
  int iVar6;
  char *pcVar7;
  uint uVar8;
  int iVar9;
  uint uVar10;
  bool bVar11;
  bool bVar12;
  uint uVar13;
  int iStack_450;
  undefined4 uStack_44c;
  int iStack_448;
  int iStack_444;
  uint uStack_440;
  char *pcStack_43c;
  uint uStack_438;
  undefined4 uStack_434;
  undefined4 uStack_430;
  undefined4 uStack_42c;
  undefined4 uStack_420;
  undefined4 uStack_41c;
  uint uStack_418;
  int iStack_408;
  
  gp = &__global_pointer_;
  if (param_1 == 0) {
                    /* WARNING: Subroutine does not return */
    __assert_fail(s_pMP3______void__0__ram_104173d0,s_dr_mp3_h_ram_104173c4,0xb86,__func___20);
  }
  if (param_2 == (code *)0x0) {
                    /* WARNING: Subroutine does not return */
    __assert_fail(s_onRead______void__0__ram_10417520,s_dr_mp3_h_ram_104173c4,0xb87,__func___20);
  }
  *(undefined1 *)(param_1 + 0x1808) = 0;
  *(code **)(param_1 + 0x5980) = param_2;
  *(code **)(param_1 + 0x5984) = param_3;
  *(int *)(param_1 + 0x5988) = param_5;
  *(undefined4 *)(param_1 + 0x598c) = param_6;
  *(undefined4 *)(param_1 + 0x5990) = param_7;
  if (param_8 == (undefined4 *)0x0) {
    *(undefined4 *)(param_1 + 0x5994) = 0;
    *(code **)(param_1 + 0x5998) = drmp3__malloc_default;
    *(code **)(param_1 + 0x599c) = drmp3__realloc_default;
    *(code **)(param_1 + 0x59a0) = drmp3__free_default;
  }
  else {
    iVar5 = param_8[1];
    iVar9 = param_8[2];
    iVar6 = param_8[3];
    *(undefined4 *)(param_1 + 0x5994) = *param_8;
    *(int *)(param_1 + 0x5998) = iVar5;
    *(int *)(param_1 + 0x599c) = iVar9;
    *(int *)(param_1 + 0x59a0) = iVar6;
    if (iVar6 == 0) {
      return 0;
    }
    if (iVar9 == 0 && iVar5 == 0) {
      return 0;
    }
  }
  *(undefined4 *)(param_1 + 0x7dc0) = 0;
  *(undefined4 *)(param_1 + 0x7dc4) = 0;
  *(undefined4 *)(param_1 + 0x7dd0) = 0;
  *(undefined4 *)(param_1 + 0x7dd4) = 0;
  *(undefined4 *)(param_1 + 0x7de0) = 0;
  *(undefined4 *)(param_1 + 0x7de4) = 0;
  *(undefined4 *)(param_1 + 0x7dc8) = 0xffffffff;
  *(undefined4 *)(param_1 + 0x7dcc) = 0xffffffff;
  *(undefined4 *)(param_1 + 0x7de8) = 0xffffffff;
  *(undefined4 *)(param_1 + 0x7dec) = 0xffffffff;
  if ((param_3 != (code *)0x0 && param_4 != (code *)0x0) &&
     (iVar5 = (*param_3)(param_6,0,2), iVar5 != 0)) {
    iVar5 = (*param_4)(param_6,&uStack_440);
    if (iVar5 == 0) {
      iVar5 = (*param_3)(param_6,0,0);
      if (iVar5 == 0) {
        return 0;
      }
    }
    else {
      if (((int)pcStack_43c < 1) && ((pcStack_43c != (char *)0x0 || (uStack_440 < 0x81)))) {
        iVar5 = 0;
      }
      else {
        iVar5 = (*param_3)(param_6,0xffffff80,2);
        if ((((iVar5 == 0) || (iVar5 = (*param_2)(param_6,&uStack_44c,3), iVar5 != 3)) ||
            ((char)uStack_44c != 'T')) || ((uStack_44c._1_1_ != 'A' || (uStack_44c._2_1_ != 'G'))))
        {
          iVar5 = 0;
        }
        else {
          uVar10 = uStack_440 - 0x80;
          pcStack_43c = (char *)((int)pcStack_43c + -1 + (uint)(uVar10 < uStack_440));
          uStack_440 = uVar10;
          if (param_5 != 0) {
            uStack_420 = CONCAT13(uStack_420._3_1_,0x474154);
            iVar5 = (*param_2)(param_6,(int)&uStack_420 + 3,0x7d);
            if ((iVar5 == 0x7d) && (*(code **)(param_1 + 0x5988) != (code *)0x0)) {
              uStack_430 = &uStack_420;
              uStack_434 = 0;
              uStack_42c = 0x80;
              (**(code **)(param_1 + 0x5988))(*(undefined4 *)(param_1 + 0x5990),&uStack_434);
            }
          }
          iVar5 = -0x80;
        }
      }
      if ((0 < (int)pcStack_43c) || ((pcStack_43c == (char *)0x0 && (0x20 < uStack_440)))) {
        iVar6 = (*param_3)(param_6,iVar5 + -0x20,2);
        if ((iVar6 != 0) &&
           ((iVar6 = (*param_2)(param_6,&uStack_420,0x20), iVar6 == 0x20 &&
            ((uStack_420 & 0xff) == 0x41)))) {
          if (uStack_420._1_1_ == 'P') {
            if (uStack_420._2_1_ == 'E') {
              if ((uStack_420._3_1_ == 'T') && (((uint)uStack_41c & 0xff) == 0x41)) {
                if (uStack_41c._1_1_ == 'G') {
                  if (uStack_41c._2_1_ == 'E') {
                    if ((uStack_41c._3_1_ == 'X') &&
                       ((uVar10 = iStack_408 + 0x20, 0 < (int)pcStack_43c ||
                        ((pcStack_43c == (char *)0x0 && (uVar10 < uStack_440)))))) {
                      uVar2 = uStack_440 - uVar10;
                      pcStack_43c = (char *)((int)pcStack_43c - (uint)(uStack_440 < uVar2));
                      uStack_440 = uVar2;
                      if ((param_5 != 0) &&
                         ((iVar5 = (*param_3)(param_6,(iVar5 - iStack_408) + -0x20,2), iVar5 != 0 &&
                          (puVar4 = (undefined4 *)drmp3_malloc(uVar10,param_8),
                          puVar4 != (undefined4 *)0x0)))) {
                        uVar2 = (*param_2)(param_6,puVar4,uVar10);
                        if ((uVar10 == uVar2) && (*(code **)(param_1 + 0x5988) != (code *)0x0)) {
                          uStack_434 = 2;
                          uStack_430 = puVar4;
                          uStack_42c = uVar10;
                          (**(code **)(param_1 + 0x5988))
                                    (*(undefined4 *)(param_1 + 0x5990),&uStack_434);
                        }
                        drmp3_free(puVar4,param_8);
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
      iVar5 = (*param_3)(param_6,0,0);
      if (iVar5 == 0) {
        return 0;
      }
      *(char **)(param_1 + 0x7dcc) = pcStack_43c;
      *(uint *)(param_1 + 0x7dc8) = uStack_440;
      if (*(int *)(param_1 + 0x7e0c) != 0) {
        *(uint *)(param_1 + 0x7e10) = uStack_440;
      }
    }
  }
  iVar5 = (*param_2)(param_6,&uStack_434,10);
  if (iVar5 != 10) {
    return 0;
  }
  if ((((uStack_434 & 0xff) == 0x49) && (uStack_434._1_1_ == 'D')) && (uStack_434._2_1_ == '3')) {
    uVar2 = ((uint)uStack_430 >> 0x10 & 0x7f) << 0x15 | ((uint)uStack_430 >> 0x18 & 0x7f) << 0xe |
            uStack_42c >> 8 & 0x7f | (uStack_42c & 0x7f) << 7;
    uVar10 = 10;
    if (((uint)uStack_430 & 0x1000) == 0) {
      if (param_5 != 0) goto LAB_ram_1040a218;
      if (param_3 == (code *)0x0) goto joined_r0x1040a5ca;
LAB_ram_1040a546:
      iVar5 = (*param_3)(param_6,uVar2,1);
      if (iVar5 == 0) {
        return 0;
      }
      uVar10 = uVar2 + 10;
    }
    else {
      uVar2 = uVar2 + 10;
      if (param_5 == 0) {
        if (param_3 != (code *)0x0) goto LAB_ram_1040a546;
        do {
          uVar13 = uVar2;
          if (0x400 < uVar2) {
            uVar13 = 0x400;
          }
          uVar8 = (*param_2)(param_6,&uStack_420,uVar13);
          if (uVar8 != uVar13) {
            return 0;
          }
          uVar2 = uVar2 - uVar13;
joined_r0x1040a5ca:
        } while (uVar2 != 0);
      }
      else {
LAB_ram_1040a218:
        uVar10 = uVar2 + 10;
        puVar3 = (undefined1 *)drmp3_malloc(uVar10,param_8);
        if (puVar3 != (undefined1 *)0x0) {
          *puVar3 = (undefined1)uStack_434;
          puVar3[1] = uStack_434._1_1_;
          puVar3[2] = uStack_434._2_1_;
          puVar3[3] = uStack_434._3_1_;
          puVar3[4] = (undefined1)uStack_430;
          puVar3[7] = uStack_430._3_1_;
          puVar3[8] = (undefined1)uStack_42c;
          puVar3[5] = uStack_430._1_1_;
          puVar3[6] = uStack_430._2_1_;
          puVar3[9] = uStack_42c._1_1_;
          uVar13 = (*param_2)(param_6,puVar3 + 10,uVar2);
          if ((uVar13 == uVar2) && (*(code **)(param_1 + 0x5988) != (code *)0x0)) {
            uStack_420 = 1;
            uStack_41c = puVar3;
            uStack_418 = uVar10;
            (**(code **)(param_1 + 0x5988))(*(undefined4 *)(param_1 + 0x5990),&uStack_420);
          }
          if (param_8 == (undefined4 *)0x0) {
            free(puVar3);
          }
          else if ((code *)param_8[3] != (code *)0x0) {
            (*(code *)param_8[3])(puVar3,*param_8);
          }
        }
      }
    }
    uVar2 = *(int *)(param_1 + 0x7dd0) + uVar10;
    iVar5 = (uint)(uVar2 < uVar10) + *(int *)(param_1 + 0x7dd4);
    *(uint *)(param_1 + 0x7dd0) = uVar2;
    *(uint *)(param_1 + 0x7dc0) = uVar2;
    *(int *)(param_1 + 0x7dd4) = iVar5;
    *(int *)(param_1 + 0x7dc4) = iVar5;
  }
  else if ((param_3 != (code *)0x0) && (iVar5 = (*param_3)(param_6,0,0), iVar5 == 0)) {
    return 0;
  }
  uVar2 = drmp3_decode_next_frame_ex(param_1,param_1 + 0x59b4,&uStack_434,&iStack_450);
  uVar10 = uStack_434;
  if (uVar2 == 0) {
    if (*(int *)(param_1 + 0x7e04) == 0) {
      return 0;
    }
    if (*(code **)(param_1 + 0x59a0) == (code *)0x0) {
      return 0;
    }
    (**(code **)(param_1 + 0x59a0))(*(int *)(param_1 + 0x7e04),*(undefined4 *)(param_1 + 0x5994));
    return 0;
  }
  if (iStack_450 == 0) {
                    /* WARNING: Subroutine does not return */
    __assert_fail(s_pFirstFrameData______void__0__ram_10417538,s_dr_mp3_h_ram_104173c4,0xc59,
                  __func___20);
  }
  if ((int)uStack_434 < 1) {
                    /* WARNING: Subroutine does not return */
    __assert_fail(s_firstFrameInfo_frame_bytes_>_0_ram_10417558,s_dr_mp3_h_ram_104173c4,0xc63,
                  __func___20);
  }
  iStack_444 = (uStack_434 - 4) * 8;
  uStack_44c = iStack_450 + 4;
  iStack_448 = (~(uint)*(byte *)(iStack_450 + 1) & 1) << 4;
  iVar5 = drmp3_L3_read_side_info(&uStack_44c,&uStack_420,iStack_450);
  if (iVar5 < 0) goto LAB_ram_1040a180;
  iVar5 = ((int)((iStack_448 >> 0x1f & 7U) + iStack_448) >> 3) + 4;
  uStack_438 = uVar10 - iVar5;
  if (uStack_438 < 8) goto LAB_ram_1040a180;
  pcStack_43c = (char *)(iVar5 + iStack_450);
  if (*pcStack_43c == 'X') {
    if (((pcStack_43c[1] != 'i') || (pcStack_43c[2] != 'n')) || (pcStack_43c[3] != 'g'))
    goto LAB_ram_1040a180;
    bVar11 = true;
    bVar12 = false;
  }
  else {
    if (((*pcStack_43c != 'I') || (pcStack_43c[1] != 'n')) || (pcStack_43c[2] != 'f'))
    goto LAB_ram_1040a180;
    bVar11 = false;
    bVar12 = true;
    if (pcStack_43c[3] != 'o') goto LAB_ram_1040a180;
  }
  bVar1 = pcStack_43c[7];
  pcVar7 = pcStack_43c + 8;
  if ((bVar1 & 1) == 0) {
    if ((bVar1 & 2) == 0) {
      if ((bVar1 & 4) != 0) {
        uVar13 = 0xffffffff;
        if (uVar10 - ((int)pcVar7 - iStack_450) < 100) goto LAB_ram_1040a180;
LAB_ram_1040a3ba:
        pcVar7 = pcVar7 + 100;
        goto LAB_ram_1040a3be;
      }
      if ((bVar1 & 8) != 0) {
        uVar13 = 0xffffffff;
        if (uVar10 - ((int)pcVar7 - iStack_450) < 4) goto LAB_ram_1040a180;
LAB_ram_1040a3d0:
        pcVar7 = pcVar7 + 4;
        goto LAB_ram_1040a3d2;
      }
      if (pcStack_43c[8] == '\0') {
        uVar13 = 0xffffffff;
      }
      else {
        uVar13 = 0xffffffff;
        if (uVar10 - ((int)pcVar7 - iStack_450) < 0x24) goto LAB_ram_1040a180;
LAB_ram_1040a0b6:
        uVar8 = (((byte)pcVar7[0x16] & 0xf) << 8 | (uint)(byte)pcVar7[0x17]) - 0x211;
        *(uint *)(param_1 + 0x7de0) =
             ((uint)(byte)pcVar7[0x15] << 4 | (uint)((byte)pcVar7[0x16] >> 4)) + 0x211;
        *(uint *)(param_1 + 0x7de4) = uVar8 & (int)~uVar8 >> 0x1f;
      }
LAB_ram_1040a0ec:
      if (bVar11) {
        *(undefined4 *)(param_1 + 0x7df0) = 1;
        uStack_440 = 3;
        if (param_5 != 0) goto LAB_ram_1040a100;
      }
      else if (bVar12) {
        *(undefined4 *)(param_1 + 0x7df4) = 1;
        if (param_5 != 0) {
          uStack_440 = 4;
          goto LAB_ram_1040a100;
        }
      }
      else if (param_5 != 0) {
        uStack_440 = 4;
LAB_ram_1040a100:
        if (*(code **)(param_1 + 0x5988) != (code *)0x0) {
          (**(code **)(param_1 + 0x5988))(*(undefined4 *)(param_1 + 0x5990),&uStack_440);
        }
      }
      uVar8 = *(int *)(param_1 + 0x7dd0) + uVar10;
      *(undefined4 *)(param_1 + 0x59b0) = 0;
      iVar5 = (uint)(uVar8 < uVar10) + *(int *)(param_1 + 0x7dd4);
      *(int *)(param_1 + 0x7dd4) = iVar5;
      *(int *)(param_1 + 0x7dc4) = iVar5;
      *(uint *)(param_1 + 0x7dd0) = uVar8;
      *(uint *)(param_1 + 0x7dc0) = uVar8;
      *(undefined1 *)(param_1 + 0x1808) = 0;
    }
    else {
      uVar13 = 0xffffffff;
      if (uVar10 - ((int)pcVar7 - iStack_450) < 4) goto LAB_ram_1040a180;
LAB_ram_1040a3a2:
      pcVar7 = pcVar7 + 4;
LAB_ram_1040a3a4:
      if ((bVar1 & 4) == 0) {
LAB_ram_1040a3be:
        if ((bVar1 & 8) == 0) {
LAB_ram_1040a3d2:
          if (*pcVar7 == '\0') goto LAB_ram_1040a0ec;
          if (0x23 < uVar10 - ((int)pcVar7 - iStack_450)) goto LAB_ram_1040a0b6;
        }
        else if (3 < uVar10 - ((int)pcVar7 - iStack_450)) goto LAB_ram_1040a3d0;
      }
      else if (99 < uVar10 - ((int)pcVar7 - iStack_450)) goto LAB_ram_1040a3ba;
    }
  }
  else {
    if (uVar10 - ((int)pcVar7 - iStack_450) < 4) goto LAB_ram_1040a180;
    uVar13 = (uint)(byte)pcStack_43c[8] << 0x18 | (uint)(byte)pcStack_43c[9] << 0x10 |
             (uint)(byte)pcStack_43c[0xb] | (uint)(byte)pcStack_43c[10] << 8;
    pcVar7 = pcStack_43c + 0xc;
    if ((bVar1 & 2) == 0) goto LAB_ram_1040a3a4;
    if (3 < uVar10 - ((int)pcVar7 - iStack_450)) goto LAB_ram_1040a3a2;
  }
  if (uVar13 != 0xffffffff) {
    *(uint *)(param_1 + 0x7de8) = uVar13 * uVar2;
    *(int *)(param_1 + 0x7dec) = (int)((ulonglong)uVar13 * (ulonglong)uVar2 >> 0x20);
  }
LAB_ram_1040a180:
  *(undefined4 *)(param_1 + 0x5978) = *(undefined4 *)(param_1 + 0x59a4);
  *(undefined4 *)(param_1 + 0x597c) = *(undefined4 *)(param_1 + 0x59a8);
  return 1;
}


// ===== player_load_current @ 1040a800 =====

void player_load_current(void)

{
  char *pcVar1;
  FILE *__stream;
  size_t sVar2;
  uint uVar3;
  int iVar4;
  uint __n;
  int iVar5;
  char acStack_a8 [64];
  char acStack_68 [72];
  
  gp = &__global_pointer_;
  if (((P != 0) && (DAT_ram_104d3bfc != 0)) && (DAT_ram_104d1798 != (code *)0x0)) {
    (*DAT_ram_104d1798)(DAT_ram_104d3bfc,DAT_ram_104d178c);
  }
  if (DAT_ram_104d3c20 != (FILE *)0x0) {
    fclose(DAT_ram_104d3c20);
    DAT_ram_104d3c20 = (FILE *)0x0;
  }
  iVar5 = (&queue)[qpos];
  P = 0;
  DAT_ram_104d3c24 = 0;
  DAT_ram_104d3c28 = 0;
  DAT_ram_104cbdf0 = 0;
  DAT_ram_104cbdec = 0;
  DAT_ram_104d3c10 = 0;
  DAT_ram_104d3c14 = 0;
  snprintf(acStack_a8,0x40,&DAT_ram_10417450,tracks + iVar5 * 0x138);
  pcVar1 = strrchr(acStack_a8,0x2e);
  if (pcVar1 != (char *)0x0) {
    *pcVar1 = '\0';
  }
  snprintf(acStack_68,0x48,s_art__s_bin_ram_10417578,acStack_a8);
  __stream = (FILE *)open_any(acStack_68);
  if ((__stream == (FILE *)0x0) &&
     (__stream = (FILE *)open_any(s_art_placeholder_bin_ram_10417584), __stream == (FILE *)0x0)) {
    DAT_ram_104d3c1c = (undefined1 *)0x0;
  }
  else {
    sVar2 = fread_unlocked(g_artsrc,2,40000,__stream);
    fclose(__stream);
    DAT_ram_104d3c1c = (undefined1 *)0x0;
    if (sVar2 == 40000) {
      DAT_ram_104d3c1c = g_artsrc;
    }
  }
  DAT_ram_104d3c2c = *(int *)(tracks + iVar5 * 0x138 + 0x134);
  if (DAT_ram_104d3c2c < 1) {
    DAT_ram_104d3c2c = 0x100;
  }
  DAT_ram_104d3c20 = (FILE *)open_any(tracks + iVar5 * 0x138);
  if (DAT_ram_104d3c20 != (FILE *)0x0) {
    fseek(DAT_ram_104d3c20,0,2);
    uVar3 = ftell(DAT_ram_104d3c20);
    fseek(DAT_ram_104d3c20,0,0);
    if (0x1ffffff < uVar3 - 1) {
      fclose(DAT_ram_104d3c20);
      DAT_ram_104d3c20 = (FILE *)0x0;
      return;
    }
    __n = uVar3;
    if (0x10000 < uVar3) {
      __n = 0x10000;
    }
    DAT_ram_104d3c28 = uVar3;
    DAT_ram_104d3c24 = fread_unlocked(filebuf,1,__n,DAT_ram_104d3c20);
    if (DAT_ram_104d3c28 <= DAT_ram_104d3c24) {
      fclose(DAT_ram_104d3c20);
      DAT_ram_104d3c20 = (FILE *)0x0;
    }
    iVar4 = drmp3_init_memory_with_metadata(&DAT_ram_104cbdf8,filebuf,DAT_ram_104d3c28,0,0,0);
    if (iVar4 == 0) {
      if (DAT_ram_104d3c20 != (FILE *)0x0) {
        fclose(DAT_ram_104d3c20);
        DAT_ram_104d3c20 = (FILE *)0x0;
      }
    }
    else {
      DAT_ram_104d3c18 = *(uint *)(tracks + iVar5 * 0x138 + 0x130);
      if ((int)DAT_ram_104d3c18 < 1) {
        P = 1;
        DAT_ram_104d3c18 = DAT_ram_104d3c28 / 32000;
      }
      else {
        P = 1;
      }
    }
  }
  return;
}


// ===== mq_new @ 1040aa80 =====

void mq_new(void)

{
  bool bVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  undefined4 uVar6;
  int iVar7;
  int iVar8;
  int unaff_s4;
  undefined4 *puVar9;
  
  gp = &__global_pointer_;
  iVar3 = rand();
  piVar2 = &mq_choice;
  if (ntracks != 0) {
    iVar3 = iVar3 % ntracks;
  }
  mq_n = 1;
  iVar8 = mq_n;
  mq_choice = iVar3;
joined_r0x1040aac0:
  if (iVar8 < 5) {
    if (iVar8 < ntracks) {
      iVar4 = rand();
      piVar5 = &mq_choice;
      if (ntracks != 0) {
        iVar4 = iVar4 % ntracks;
      }
      bVar1 = false;
      if (0 < mq_n) goto LAB_ram_1040ab00;
      goto LAB_ram_1040ab40;
    }
    if (iVar8 < 2) goto LAB_ram_1040abe6;
  }
  puVar9 = &mq_choice + iVar8;
  do {
    iVar4 = rand();
    if (iVar8 != 0) {
      iVar4 = iVar4 % iVar8;
    }
    uVar6 = puVar9[-1];
    iVar8 = iVar8 + -1;
    puVar9 = puVar9 + -1;
    *puVar9 = (&mq_choice)[iVar4];
    (&mq_choice)[iVar4] = uVar6;
  } while (iVar8 != 1);
  iVar8 = mq_n;
LAB_ram_1040abe6:
  mq_correct = 0;
  if (0 < iVar8) {
    bVar1 = false;
    iVar4 = 0;
    do {
      iVar7 = *piVar2;
      piVar2 = piVar2 + 1;
      if (iVar3 == iVar7) {
        bVar1 = true;
        unaff_s4 = iVar4;
      }
      iVar4 = iVar4 + 1;
    } while (iVar4 != iVar8);
    if (bVar1) {
      mq_correct = unaff_s4;
    }
  }
  mq_sel = 0;
  mq_reveal = 0;
  qlen = 1;
  qpos = 0;
  queue = iVar3;
  player_load_current();
  return;
LAB_ram_1040ab00:
  do {
    iVar8 = *piVar5;
    piVar5 = piVar5 + 1;
    bVar1 = (bool)(bVar1 | iVar8 == iVar4);
  } while (piVar5 != &mq_choice + mq_n);
  iVar8 = mq_n;
  if (!bVar1) {
LAB_ram_1040ab40:
    iVar8 = mq_n + 1;
    piVar5 = &mq_choice + mq_n;
    mq_n = iVar8;
    *piVar5 = iVar4;
  }
  goto joined_r0x1040aac0;
}


// ===== mq_step @ 1040ac80 =====

undefined4 mq_step(undefined4 param_1)

{
  int *piVar1;
  int iVar2;
  undefined4 uVar3;
  char *pcVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  char acStack_4c [32];
  
  gp = &__global_pointer_;
  if ((DAT_ram_1254be1c & 0x20) != 0) {
    return 1;
  }
  if (ntracks < 2) {
    uVar3 = ui_bg();
    ui_clear(param_1,uVar3);
    ui_status_bar(param_1,s_Music_Quiz_ram_104175cc,100);
    uVar3 = ui_fg();
    ui_text(param_1,0x12,0xdc,s_Need_more_songs_ram_104175d8,uVar3);
  }
  else {
    if (mq_reveal == 0) {
      if (((DAT_ram_1254be1c & 2) != 0) && (mq_sel < mq_n + -1)) {
        mq_sel = mq_sel + 1;
      }
      if (((DAT_ram_1254be1c & 1) != 0) && (0 < mq_sel)) {
        mq_sel = mq_sel + -1;
      }
      uVar3 = param_1;
      if ((DAT_ram_1254be1c & 0x10) != 0) {
        mq_total = mq_total + 1;
        if (mq_sel == mq_correct) {
          mq_score = mq_score + 1;
        }
        mq_reveal = 1;
        uVar3 = 0;
        ecall();
        mq_reveal_until = 0x5dc;
      }
    }
    else {
      uVar3 = 0;
      ecall();
      uVar6 = 0;
      if ((mq_reveal_until == 0) || (uVar6 = DAT_ram_1254be1c & 0x10, uVar6 != 0)) {
        uVar3 = mq_new(0,0,0,0,0,uVar6,3,0xc0de0006);
      }
    }
    uVar3 = ui_bg(uVar3);
    ui_clear(param_1,uVar3);
    ui_status_bar(param_1,s_Music_Quiz_ram_104175cc,100);
    snprintf(acStack_4c,0x1c,s_Score__d____d_ram_104175e8,mq_score,mq_total);
    uVar3 = ui_fg();
    ui_text(param_1,0x12,0x38,acStack_4c,uVar3);
    uVar3 = ui_fg();
    ui_text(param_1,0x12,100,s_Guess_the_song__ram_104175f8,uVar3);
    if (0 < mq_n) {
      piVar1 = &mq_choice;
      iVar7 = 0;
      iVar2 = 0x98;
      do {
        iVar5 = mq_sel;
        uVar3 = ui_fg();
        if (iVar5 == iVar7) {
          if (mq_reveal == 0) {
            ui_fill(param_1,0,iVar2 + -8,0x280,0x34,0x3bf9);
            uVar3 = 0xffff;
            if (mq_reveal == 0) goto LAB_ram_1040adc0;
          }
          uVar3 = 0x2fec;
          if (mq_correct != iVar7) {
            uVar3 = 0xf986;
          }
        }
        else if ((mq_reveal != 0) && (iVar7 == mq_correct)) {
          uVar3 = 0x2fec;
        }
LAB_ram_1040adc0:
        iVar5 = *piVar1;
        iVar7 = iVar7 + 1;
        piVar1 = piVar1 + 1;
        ui_text_clip(param_1,0x18,iVar2,0x250,iVar5 * 0x138 + 0x104e8530,uVar3);
        iVar2 = iVar2 + 0x3c;
      } while (iVar7 < mq_n);
    }
    if (mq_reveal == 0) {
      pcVar4 = s_Up_Down___A_B__exit_ram_104175b0;
    }
    else {
      pcVar4 = s_A__next_B__exit_ram_10417598;
    }
    ui_text_center(param_1,0x140,0x1c0,pcVar4,0x8c71);
  }
  return 0;
}


// ===== mq_reset @ 1040af80 =====

void mq_reset(void)

{
  gp = &__global_pointer_;
  mq_score = 0;
  mq_total = 0;
  if (ntracks < 1) {
    return;
  }
  mq_new();
  return;
}


// ===== shuffle_all @ 1040afc0 =====

void shuffle_all(void)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  undefined4 *puVar7;
  int *piVar8;
  int aiStack_824 [515];
  
  gp = &__global_pointer_;
  piVar8 = aiStack_824 + 1;
  piVar1 = aiStack_824 + 1;
  if (ntracks < 1) {
    return;
  }
  iVar5 = 0;
  do {
    *piVar1 = iVar5;
    iVar5 = iVar5 + 1;
    piVar1 = piVar1 + 1;
  } while (iVar5 != ntracks);
  if (iVar5 != 1) {
    piVar1 = aiStack_824 + iVar5;
    do {
      iVar3 = rand();
      if (iVar5 != 0) {
        iVar3 = iVar3 % iVar5;
      }
      iVar6 = *piVar1;
      piVar2 = piVar1 + -1;
      iVar5 = iVar5 + -1;
      *piVar1 = aiStack_824[iVar3 + 1];
      aiStack_824[iVar3 + 1] = iVar6;
      piVar1 = piVar2;
    } while (aiStack_824 + 1 != piVar2);
    if (ntracks < 1) {
      gp = &__global_pointer_;
      return;
    }
  }
  qlen = ntracks;
  puVar7 = &queue;
  iVar5 = 0;
  do {
    uVar4 = *piVar8;
    iVar5 = iVar5 + 1;
    piVar8 = piVar8 + 1;
    *puVar7 = uVar4;
    puVar7 = puVar7 + 1;
  } while (iVar5 < qlen);
  qpos = 0;
  player_load_current();
  return;
}


