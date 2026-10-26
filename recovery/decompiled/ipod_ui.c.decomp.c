// ===== lerp565 @ 10402c80 =====

uint lerp565(uint param_1,uint param_2,int param_3,int param_4)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  
  gp = &__global_pointer_;
  uVar3 = param_1 >> 5 & 0x3f;
  if (param_4 == 0) {
    iVar2 = -1;
    iVar1 = -1;
    param_4 = -1;
  }
  else {
    iVar2 = (int)(((param_2 >> 5 & 0x3f) - uVar3) * param_3) / param_4;
    iVar1 = (int)(((param_2 >> 0xb) - (param_1 >> 0xb)) * param_3) / param_4;
    param_4 = (int)(((param_2 & 0x1f) - (param_1 & 0x1f)) * param_3) / param_4;
  }
  return ((iVar2 + uVar3) * 0x20 | (iVar1 + (param_1 >> 0xb)) * 0x800 | param_4 + (param_1 & 0x1f))
         & 0xffff;
}


// ===== ui_char @ 10402d40 =====

void ui_char(int param_1,int param_2,uint param_3,int param_4,undefined4 param_5)

{
  byte bVar1;
  byte bVar2;
  byte *pbVar3;
  undefined2 *puVar4;
  undefined4 uVar5;
  int iVar6;
  uint uVar7;
  undefined2 *puVar8;
  byte *pbVar9;
  
  gp = &__global_pointer_;
  uVar7 = param_4 - 0x20;
  if ((uVar7 & 0xff) < 0x5f) {
    iVar6 = uVar7 * 0x450;
  }
  else {
    iVar6 = 0x85b0;
    uVar7 = 0x1f;
  }
  puVar8 = (undefined2 *)(param_1 + (param_3 * 0x280 + param_2) * 2);
  pbVar9 = &DAT_ram_10418166 + iVar6;
  do {
    while ((0x1df < param_3 || (bVar1 = (&DAT_ram_10418165)[uVar7 * 0x450], bVar1 == 0))) {
      pbVar9 = pbVar9 + 0x1d;
      param_3 = param_3 + 1;
      puVar8 = puVar8 + 0x280;
      if (pbVar9 == (byte *)(iVar6 + 0x104185b4)) {
        return;
      }
    }
    pbVar3 = pbVar9;
    puVar4 = puVar8;
    do {
      bVar2 = *pbVar3;
      if ((0xb < bVar2) && (pbVar3 + (param_2 - (int)pbVar9) < (byte *)0x280)) {
        uVar5 = param_5;
        if (bVar2 < 0xf8) {
          uVar5 = lerp565(*puVar4,param_5,bVar2,0xff);
        }
        *puVar4 = (short)uVar5;
      }
      pbVar3 = pbVar3 + 1;
      puVar4 = puVar4 + 1;
    } while (pbVar3 != pbVar9 + bVar1);
    pbVar9 = pbVar9 + 0x1d;
    param_3 = param_3 + 1;
    puVar8 = puVar8 + 0x280;
  } while (pbVar9 != (byte *)(iVar6 + 0x104185b4));
  gp = &__global_pointer_;
  return;
}


// ===== fmt_time @ 10402ec0 =====

void fmt_time(char *param_1,uint param_2)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  char *pcVar7;
  int iVar8;
  
  gp = &__global_pointer_;
  uVar3 = (int)~param_2 >> 0x1f & param_2;
  uVar4 = uVar3 / 0x3c;
  uVar3 = uVar3 % 0x3c;
  if ((int)param_2 < 600) {
    iVar8 = 4;
    iVar5 = 3;
    iVar6 = 2;
    iVar2 = 1;
    pcVar7 = param_1;
  }
  else {
    iVar8 = 5;
    iVar5 = 4;
    iVar6 = 3;
    iVar2 = 2;
    *param_1 = (char)(uVar4 / 10) + (char)((uVar4 / 10) / 10) * -10 + '0';
    pcVar7 = param_1 + 1;
  }
  *pcVar7 = (char)uVar4 + (char)(uVar4 / 10) * -10 + '0';
  param_1[iVar2] = ':';
  cVar1 = (char)(uVar3 / 10);
  param_1[iVar6] = cVar1 + '0';
  param_1[iVar5] = (char)uVar3 + cVar1 * -10 + '0';
  param_1[iVar8] = '\0';
  return;
}


// ===== ui_menu_scrollbar.part.0 @ 10402fc0 =====

void ui_menu_scrollbar_part_0(int param_1,int param_2,int param_3)

{
  undefined2 uVar1;
  undefined *puVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  
  puVar2 = T;
  gp = &__global_pointer_;
  uVar1 = *(undefined2 *)(T + 0x20);
  iVar5 = param_1 + 0xd214;
  do {
    iVar3 = iVar5 + -0x14;
    do {
      iVar6 = iVar3;
      *(undefined2 *)(iVar6 + 0x4ec) = uVar1;
      iVar3 = iVar6 + 2;
    } while (iVar6 + 2 != iVar5);
    iVar5 = iVar6 + 0x502;
  } while (iVar5 != param_1 + 0x96014);
  if (param_2 == 0) {
    iVar5 = -1;
  }
  else {
    iVar5 = 0xbfa / param_2;
  }
  if (iVar5 < 0x20) {
    iVar5 = 0x20;
  }
  uVar1 = *(undefined2 *)(puVar2 + 0x18);
  if (param_2 + -7 == 0) {
    iVar3 = -1;
  }
  else {
    iVar3 = ((0x1b6 - iVar5) * param_3) / (param_2 + -7);
  }
  uVar4 = iVar3 + 0x2a;
  iVar3 = iVar3 * 0x500 + param_1 + 0xd214;
  iVar5 = iVar5 + uVar4;
  do {
    if (uVar4 < 0x1e0) {
      iVar6 = iVar3 + -0x14;
      do {
        *(undefined2 *)(iVar6 + 0x4ec) = uVar1;
        iVar6 = iVar6 + 2;
      } while (iVar6 != iVar3);
    }
    uVar4 = uVar4 + 1;
    iVar3 = iVar3 + 0x500;
  } while ((int)uVar4 < iVar5);
  return;
}


// ===== ui_marquee.constprop.0 @ 10403140 =====

void ui_marquee_constprop_0(int param_1,int param_2,byte *param_3,undefined4 param_4,uint param_5)

{
  byte bVar1;
  uint uVar2;
  byte *pbVar3;
  undefined2 *puVar4;
  undefined4 uVar5;
  int iVar6;
  uint uVar7;
  byte *pbVar8;
  int iVar9;
  byte *pbVar10;
  undefined2 *puVar11;
  int iVar12;
  uint uStack_50;
  byte *pbStack_44;
  
  gp = &__global_pointer_;
  uStack_50 = (uint)*param_3;
  if (uStack_50 == 0) {
    return;
  }
  iVar9 = 0;
  uVar7 = uStack_50;
  pbVar8 = param_3;
  do {
    pbVar8 = pbVar8 + 1;
    uVar2 = 0xf;
    if ((uVar7 - 0x20 & 0xff) < 0x5f) {
      uVar2 = (uint)(byte)(&FP_FONT)[(uVar7 - 0x20) * 0x450];
    }
    uVar7 = (uint)*pbVar8;
    iVar9 = iVar9 + uVar2;
  } while (uVar7 != 0);
  pbStack_44 = param_3;
  if (iVar9 < 0x189) {
    iVar9 = 0xec;
    do {
      ui_char(param_1,iVar9,param_2,uStack_50,param_4);
      bVar1 = *pbStack_44;
      pbStack_44 = pbStack_44 + 1;
      uVar7 = 0xf;
      if ((bVar1 - 0x20 & 0xff) < 0x5f) {
        uVar7 = (uint)(byte)(&FP_FONT)[(bVar1 - 0x20) * 0x450];
      }
      iVar9 = iVar9 + uVar7;
      uStack_50 = (uint)*pbStack_44;
    } while (uStack_50 != 0);
    return;
  }
  iVar9 = iVar9 + -0x188;
  iVar12 = 0xec;
  uVar7 = (uint)(iVar9 * 1000) / 0x22;
  iVar6 = uVar7 + 0x4b0;
  if (iVar6 != 0) {
    param_5 = param_5 % (uint)(iVar6 * 2);
  }
  if (0x4af < param_5) {
    if ((int)param_5 < iVar6) {
      if (uVar7 == 0) {
        iVar12 = -1;
      }
      else {
        iVar12 = (int)((param_5 - 0x4b0) * iVar9) / (int)uVar7;
      }
      iVar12 = 0xec - iVar12;
    }
    else {
      if ((int)(uVar7 + 0x960) <= (int)param_5) {
        if (uVar7 == 0) {
          iVar12 = -1;
        }
        else {
          iVar12 = (int)((param_5 - (uVar7 + 0x960)) * iVar9) / (int)uVar7;
        }
        iVar9 = iVar9 - iVar12;
      }
      iVar12 = 0xec - iVar9;
    }
  }
  if ((uStack_50 - 0x20 & 0xff) < 0x5f) {
    uStack_50 = uStack_50 - 0x20;
    goto LAB_ram_10403380;
  }
  uStack_50 = 0x1f;
  uVar7 = 0xe;
  if (0xec < iVar12 + 0xe) goto LAB_ram_1040339c;
LAB_ram_10403248:
  iVar12 = iVar12 + (uint)(byte)(&FP_FONT)[uStack_50 * 0x450];
  do {
    pbVar8 = pbStack_44 + 1;
    pbStack_44 = pbStack_44 + 1;
    if (*pbVar8 == 0) {
      return;
    }
    uStack_50 = *pbVar8 - 0x20;
    if ((uStack_50 & 0xff) < 0x5f) {
LAB_ram_10403380:
      uVar7 = (uint)(byte)(&DAT_ram_10418165)[uStack_50 * 0x450];
      if ((int)(iVar12 + uVar7) < 0xed) goto LAB_ram_10403248;
LAB_ram_1040339c:
      if (0x273 < iVar12) {
        return;
      }
    }
    else {
      uStack_50 = 0x1f;
      uVar7 = 0xe;
      if (iVar12 < 0xdf) goto LAB_ram_10403248;
    }
    iVar9 = uStack_50 * 0x450;
    pbVar8 = &DAT_ram_10418166 + iVar9;
    if (uVar7 != 0) {
      pbVar10 = &DAT_ram_10418166 + iVar9 + uVar7;
      puVar11 = (undefined2 *)((param_2 * 0x280 + iVar12) * 2 + param_1);
      do {
        pbVar3 = pbVar8;
        puVar4 = puVar11;
        do {
          bVar1 = *pbVar3;
          if ((0xb < bVar1) && (pbVar3 + ((iVar12 + -0xec) - (int)pbVar8) < (byte *)0x188)) {
            uVar5 = param_4;
            if (bVar1 < 0xf8) {
              uVar5 = lerp565(*puVar4,param_4,bVar1,0xff);
            }
            *puVar4 = (short)uVar5;
          }
          pbVar3 = pbVar3 + 1;
          puVar4 = puVar4 + 1;
        } while (pbVar3 != pbVar10);
        pbVar8 = pbVar8 + 0x1d;
        pbVar10 = pbVar10 + 0x1d;
        puVar11 = puVar11 + 0x280;
      } while (pbVar8 != (byte *)(iVar9 + 0x104185b4));
    }
    iVar12 = iVar12 + (uint)(byte)(&FP_FONT)[uStack_50 * 0x450];
    if (0x273 < iVar12) {
      return;
    }
  } while( true );
}


