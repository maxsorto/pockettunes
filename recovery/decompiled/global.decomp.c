// ===== ui_text_center @ 10403b80 =====

void ui_text_center(undefined4 param_1,int param_2,undefined4 param_3,byte *param_4,
                   undefined4 param_5)

{
  byte bVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  byte *pbVar5;
  uint uVar6;
  
  gp = &__global_pointer_;
  uVar3 = (uint)*param_4;
  if (uVar3 != 0) {
    iVar2 = 0;
    uVar4 = uVar3;
    pbVar5 = param_4;
    do {
      pbVar5 = pbVar5 + 1;
      uVar6 = 0xf;
      if ((uVar4 - 0x20 & 0xff) < 0x5f) {
        uVar6 = (uint)(byte)(&FP_FONT)[(uVar4 - 0x20) * 0x450];
      }
      uVar4 = (uint)*pbVar5;
      iVar2 = iVar2 + uVar6;
    } while (uVar4 != 0);
    param_2 = param_2 - iVar2 / 2;
    do {
      ui_char(param_1,param_2,param_3,uVar3,param_5);
      bVar1 = *param_4;
      uVar4 = 0xf;
      param_4 = param_4 + 1;
      if ((bVar1 - 0x20 & 0xff) < 0x5f) {
        uVar4 = (uint)(byte)(&FP_FONT)[(bVar1 - 0x20) * 0x450];
      }
      uVar3 = (uint)*param_4;
      param_2 = param_2 + uVar4;
    } while (uVar3 != 0);
  }
  return;
}


// ===== ui_text_right @ 10403a80 =====

void ui_text_right(undefined4 param_1,int param_2,undefined4 param_3,byte *param_4,
                  undefined4 param_5)

{
  byte bVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  byte *pbVar5;
  uint uVar6;
  
  gp = &__global_pointer_;
  uVar3 = (uint)*param_4;
  if (uVar3 != 0) {
    iVar2 = 0;
    uVar4 = uVar3;
    pbVar5 = param_4;
    do {
      pbVar5 = pbVar5 + 1;
      uVar6 = 0xf;
      if ((uVar4 - 0x20 & 0xff) < 0x5f) {
        uVar6 = (uint)(byte)(&FP_FONT)[(uVar4 - 0x20) * 0x450];
      }
      uVar4 = (uint)*pbVar5;
      iVar2 = iVar2 + uVar6;
    } while (uVar4 != 0);
    param_2 = param_2 - iVar2;
    do {
      ui_char(param_1,param_2,param_3,uVar3,param_5);
      bVar1 = *param_4;
      uVar4 = 0xf;
      param_4 = param_4 + 1;
      if ((bVar1 - 0x20 & 0xff) < 0x5f) {
        uVar4 = (uint)(byte)(&FP_FONT)[(bVar1 - 0x20) * 0x450];
      }
      uVar3 = (uint)*param_4;
      param_2 = param_2 + uVar4;
    } while (uVar3 != 0);
  }
  return;
}


// ===== ui_clear @ 10403680 =====

void ui_clear(undefined2 *param_1,uint param_2)

{
  undefined2 *puVar1;
  
  gp = &__global_pointer_;
  puVar1 = param_1 + 0x4b000;
  if (param_2 >> 8 == (param_2 & 0xff)) {
    memset(param_1,param_2 >> 8,0x96000);
    return;
  }
  do {
    *param_1 = (short)param_2;
    param_1 = param_1 + 1;
  } while (param_1 != puVar1);
  return;
}


// ===== ui_visible_rows @ 10404340 =====

undefined4 ui_visible_rows(void)

{
  gp = &__global_pointer_;
  return 7;
}


// ===== ui_now_playing @ 10404880 =====

/* WARNING: Type propagation algorithm not settling */

void ui_now_playing(ushort *param_1,undefined *param_2,undefined *param_3,undefined *param_4,
                   int param_5,int param_6,int param_7,int param_8,void *param_9,undefined4 param_10
                   ,undefined4 param_11,undefined4 param_12)

{
  char *pcVar1;
  byte bVar2;
  ushort uVar3;
  undefined2 uVar4;
  undefined2 uVar5;
  undefined *puVar6;
  undefined2 uVar7;
  void *pvVar8;
  int iVar9;
  char cVar10;
  int iVar11;
  uint uVar12;
  ushort *puVar13;
  char cVar14;
  uint uVar15;
  undefined4 *puVar16;
  byte *pbVar17;
  undefined2 *puVar18;
  ushort *puVar19;
  ushort *puVar20;
  char *pcVar21;
  int iVar22;
  uint uVar23;
  int iVar24;
  int iVar25;
  byte *pbVar26;
  int iVar27;
  void *pvVar28;
  char acStack_7c [8];
  char acStack_74 [8];
  byte local_6c [8];
  byte local_64 [12];
  undefined1 local_58 [36];
  
  puVar6 = T;
  gp = &__global_pointer_;
  uVar3 = *(ushort *)(T + 4);
  puVar20 = param_1;
  if ((uVar3 & 0xff) == (uint)(uVar3 >> 8)) {
    memset(param_1,uVar3 & 0xff,0x96000);
  }
  else {
    do {
      *puVar20 = uVar3;
      puVar20 = puVar20 + 1;
    } while (puVar20 != param_1 + 0x4b000);
  }
  ui_status_bar(param_1,s_Now_Playing_ram_10417390,param_10);
  uVar3 = *(ushort *)(puVar6 + 0x1e);
  puVar20 = param_1 + 0xa5dc;
  do {
    puVar13 = puVar20 + -0xcc;
    do {
      puVar19 = puVar13;
      *puVar19 = uVar3;
      puVar13 = puVar19 + 1;
    } while (puVar19 + 1 != puVar20);
    puVar20 = puVar19 + 0x281;
  } while (puVar20 != param_1 + 0x2a3dc);
  if (param_9 == (void *)0x0) {
    uVar3 = *(ushort *)(puVar6 + 0x20);
    puVar20 = param_1 + 0xaada;
    do {
      puVar13 = puVar20 + -200;
      do {
        puVar19 = puVar13;
        *puVar19 = uVar3;
        puVar13 = puVar19 + 1;
      } while (puVar19 + 1 != puVar20);
      puVar20 = puVar19 + 0x281;
    } while (puVar20 != param_1 + 0x29eda);
    uVar3 = *(ushort *)(puVar6 + 6);
    puVar20 = param_1 + 0x10e8e;
    do {
      puVar13 = puVar20 + -8;
      do {
        puVar19 = puVar13;
        *puVar19 = uVar3;
        puVar13 = puVar19 + 1;
      } while (puVar19 + 1 != puVar20);
      puVar20 = puVar19 + 0x281;
    } while (puVar20 != param_1 + 0x1f48e);
    uVar3 = *(ushort *)(puVar6 + 6);
    puVar20 = param_1 + 0x1cc8e;
    do {
      puVar13 = puVar20 + -0x24;
      do {
        puVar19 = puVar13;
        *puVar19 = uVar3;
        puVar13 = puVar19 + 1;
      } while (puVar19 + 1 != puVar20);
      puVar20 = puVar19 + 0x281;
    } while (puVar20 != param_1 + 0x2128e);
    uVar3 = *(ushort *)(puVar6 + 6);
    puVar20 = param_1 + 0x104a6;
    do {
      puVar13 = puVar20 + -0x20;
      do {
        *puVar13 = uVar3;
        puVar13 = puVar13 + 1;
      } while (puVar13 != puVar20);
      puVar20 = puVar20 + 0x280;
    } while (puVar20 != param_1 + 0x11da6);
  }
  else {
    puVar20 = param_1 + 0xaa12;
    pvVar28 = (void *)((int)param_9 + 80000);
    do {
      pvVar8 = memcpy(puVar20,param_9,400);
      param_9 = (void *)((int)param_9 + 400);
      puVar20 = (ushort *)((int)pvVar8 + 0x500);
    } while (param_9 != pvVar28);
  }
  if (param_2 == (undefined *)0x0) {
    param_2 = &DAT_ram_104174c0;
  }
  ui_marquee_constprop_0(param_1,0x60,param_2,*(undefined2 *)(puVar6 + 6),param_12);
  if (param_3 == (undefined *)0x0) {
    param_3 = &DAT_ram_104174c0;
  }
  ui_marquee_constprop_0(param_1,0x90,param_3,*(undefined2 *)(puVar6 + 0x1a),param_12);
  if (param_4 == (undefined *)0x0) {
    param_4 = &DAT_ram_104174c0;
  }
  ui_marquee_constprop_0(param_1,0xc0,param_4,*(undefined2 *)(puVar6 + 0x1c),param_12);
  if (param_5 == 0) {
    acStack_7c[0] = '0';
    acStack_7c[1] = '\0';
    cVar10 = '0';
    if (param_6 == 0) {
      acStack_74[0] = '0';
      acStack_74[1] = '\0';
      cVar14 = '0';
LAB_ram_104049f6:
      pcVar21 = acStack_7c;
      iVar27 = 0;
      do {
        iVar11 = iVar27;
        iVar27 = iVar11 + 1;
        pcVar21 = pcVar21 + 1;
        *(char *)((int)local_58 + iVar11) = cVar10;
        cVar10 = *pcVar21;
      } while (cVar10 != '\0');
      iVar25 = iVar11 + 2;
      iVar9 = iVar11 + 3;
      iVar22 = iVar11 + 4;
      iVar11 = iVar11 + 5;
    }
    else {
LAB_ram_10404dde:
      iVar11 = 0;
      do {
        iVar9 = iVar11;
        puVar16 = (undefined4 *)((int)local_58 + iVar9 + 1);
        iVar27 = param_6 / 10;
        *(char *)((int)local_58 + iVar9) = (char)param_6 + (char)iVar27 * -10 + '0';
        iVar11 = iVar9 + 1;
        param_6 = iVar27;
      } while (iVar27 != 0);
      pcVar21 = acStack_74;
      do {
        pcVar1 = (char *)((int)puVar16 + -1);
        puVar16 = (undefined4 *)((int)puVar16 + -1);
        *pcVar21 = *pcVar1;
        pcVar21 = pcVar21 + 1;
      } while ((undefined4 *)local_58 != puVar16);
      acStack_74[iVar9 + 1] = '\0';
      cVar14 = acStack_74[0];
      if (cVar10 != '\0') goto LAB_ram_104049f6;
      iVar11 = 4;
      iVar22 = 3;
      iVar9 = 2;
      iVar25 = 1;
      iVar27 = 0;
    }
    *(undefined1 *)((int)local_58 + iVar27) = 0x20;
    *(undefined1 *)((int)local_58 + iVar25) = 0x6f;
    *(undefined1 *)((int)local_58 + iVar9) = 0x66;
    *(undefined1 *)((int)local_58 + iVar22) = 0x20;
    if (cVar14 == '\0') {
      iVar27 = iVar11;
      goto LAB_ram_10404a96;
    }
  }
  else {
    iVar11 = 0;
    do {
      iVar9 = iVar11;
      puVar16 = (undefined4 *)((int)local_58 + iVar9 + 1);
      iVar27 = param_5 / 10;
      *(char *)((int)local_58 + iVar9) = (char)param_5 + (char)iVar27 * -10 + '0';
      iVar11 = iVar9 + 1;
      param_5 = iVar27;
    } while (iVar27 != 0);
    pcVar21 = acStack_7c;
    do {
      pcVar1 = (char *)((int)puVar16 + -1);
      puVar16 = (undefined4 *)((int)puVar16 + -1);
      *pcVar21 = *pcVar1;
      pcVar21 = pcVar21 + 1;
    } while ((undefined4 *)local_58 != puVar16);
    acStack_7c[iVar9 + 1] = '\0';
    cVar10 = acStack_7c[0];
    if (param_6 != 0) goto LAB_ram_10404dde;
    cVar14 = '0';
    acStack_74[0] = '0';
    acStack_74[1] = '\0';
    if (acStack_7c[0] != '\0') goto LAB_ram_104049f6;
    local_58._0_4_ = 0x20666f20;
    iVar11 = 4;
  }
  iVar9 = iVar11;
  do {
    iVar27 = iVar9 + 1;
    *(char *)((int)local_58 + iVar9) = cVar14;
    cVar14 = acStack_74[iVar27 - iVar11];
    iVar9 = iVar27;
  } while (cVar14 != '\0');
LAB_ram_10404a96:
  pbVar26 = local_58;
  pbVar26[iVar27] = 0;
  uVar15 = (uint)(byte)local_58[0];
  if (uVar15 != 0) {
    uVar4 = *(undefined2 *)(puVar6 + 0x1c);
    iVar11 = 0;
    pbVar17 = pbVar26;
    uVar23 = uVar15;
    do {
      pbVar17 = pbVar17 + 1;
      uVar12 = 0xf;
      if ((uVar23 - 0x20 & 0xff) < 0x5f) {
        uVar12 = (uint)(byte)(&FP_FONT)[(uVar23 - 0x20) * 0x450];
      }
      uVar23 = (uint)*pbVar17;
      iVar11 = iVar11 + uVar12;
    } while (uVar23 != 0);
    iVar11 = 0x270 - iVar11;
    do {
      ui_char(param_1,iVar11,0x34,uVar15,uVar4);
      bVar2 = *pbVar26;
      uVar23 = 0xf;
      pbVar26 = pbVar26 + 1;
      if ((bVar2 - 0x20 & 0xff) < 0x5f) {
        uVar23 = (uint)(byte)(&FP_FONT)[(bVar2 - 0x20) * 0x450];
      }
      uVar15 = (uint)*pbVar26;
      iVar11 = iVar11 + uVar23;
    } while (uVar15 != 0);
  }
  uVar3 = *(ushort *)(puVar6 + 0x20);
  puVar20 = param_1 + 0x4305c;
  do {
    puVar13 = puVar20 + -0x238;
    do {
      puVar19 = puVar13;
      *puVar19 = uVar3;
      puVar13 = puVar19 + 1;
    } while (puVar19 + 1 != puVar20);
    puVar20 = puVar19 + 0x281;
  } while (param_1 + 0x45d5c != puVar20);
  uVar3 = *(ushort *)(puVar6 + 0xc);
  puVar20 = param_1 + 0x42e24;
  do {
    *puVar20 = uVar3;
    puVar20 = puVar20 + 1;
  } while (puVar20 != param_1 + 0x4305c);
  puVar20 = param_1 + 0x430a4;
  do {
    *puVar20 = uVar3;
    puVar20 = puVar20 + 1;
  } while (puVar20 != param_1 + 0x432dc);
  uVar3 = *(ushort *)(puVar6 + 0xc);
  puVar20 = param_1 + 0x45624;
  do {
    *puVar20 = uVar3;
    puVar20 = puVar20 + 1;
  } while (param_1 + 0x4585c != puVar20);
  puVar20 = param_1 + 0x458a4;
  do {
    *puVar20 = uVar3;
    puVar20 = puVar20 + 1;
  } while (param_1 + 0x45adc != puVar20);
  fmt_time(local_6c,param_7);
  if (local_6c[0] != 0) {
    uVar4 = *(undefined2 *)(puVar6 + 0x28);
    pbVar26 = local_6c;
    iVar11 = 0x20;
    do {
      ui_char(param_1,iVar11,0x180,local_6c[0],uVar4);
      bVar2 = *pbVar26;
      uVar15 = 0xf;
      pbVar26 = pbVar26 + 1;
      if ((bVar2 - 0x20 & 0xff) < 0x5f) {
        uVar15 = (uint)(byte)(&FP_FONT)[(bVar2 - 0x20) * 0x450];
      }
      local_6c[0] = *pbVar26;
      iVar11 = iVar11 + uVar15;
    } while (local_6c[0] != 0);
  }
  if (0 < param_8) {
    if (param_7 < 0) {
      iVar27 = 0x24;
      iVar11 = 0x28;
      iVar9 = 0x22;
    }
    else {
      iVar11 = param_7;
      if (param_8 < param_7) {
        iVar11 = param_8;
      }
      if (param_8 == 0) {
        iVar22 = -1;
      }
      else {
        iVar22 = (iVar11 * 0x238) / param_8;
      }
      iVar9 = iVar22 + 0x22;
      iVar11 = iVar22 + 0x28;
      iVar27 = iVar22 + 0x24;
      if (iVar22 != 0) {
        uVar4 = *(undefined2 *)(puVar6 + 0x22);
        uVar5 = *(undefined2 *)(puVar6 + 0x24);
        iVar25 = 0x85c00;
        iVar22 = 0;
        do {
          uVar7 = lerp565(uVar4,uVar5,iVar22,0x11);
          puVar18 = (undefined2 *)((int)param_1 + iVar25 + 0x48);
          iVar24 = 0x24;
          do {
            if (iVar24 < 0x280) {
              *puVar18 = uVar7;
            }
            iVar24 = iVar24 + 1;
            puVar18 = puVar18 + 1;
          } while (iVar24 < iVar27);
          iVar22 = iVar22 + 1;
          iVar25 = iVar25 + 0x500;
        } while (iVar22 != 0x12);
      }
    }
    if (iVar27 != 0x24) {
      uVar3 = *(ushort *)(puVar6 + 0x26);
      puVar20 = param_1 + 0x43324;
      iVar22 = 0x24;
      while( true ) {
        if (iVar22 < 0x280) {
          *puVar20 = uVar3;
        }
        puVar20 = puVar20 + 1;
        if (iVar27 == iVar22 + 1) break;
        iVar22 = iVar22 + 1;
      }
      puVar20 = param_1 + 0x435a4;
      iVar27 = 0x24;
      while( true ) {
        if (iVar27 < 0x280) {
          *puVar20 = uVar3;
        }
        puVar20 = puVar20 + 1;
        if (iVar22 == iVar27) break;
        iVar27 = iVar27 + 1;
      }
    }
    puVar13 = param_1 + iVar9 + 0x42400;
    puVar20 = puVar13;
    do {
      puVar19 = puVar20;
      iVar27 = iVar9;
      do {
        if (iVar27 < 0x280) {
          *puVar19 = 0xffff;
        }
        iVar27 = iVar27 + 1;
        puVar19 = puVar19 + 1;
      } while (iVar27 < iVar11);
      puVar20 = puVar20 + 0x280;
    } while (puVar20 != param_1 + iVar9 + 0x46500);
    uVar3 = *(ushort *)(puVar6 + 0x24);
    iVar27 = iVar9;
    do {
      if (iVar27 < 0x280) {
        *puVar13 = uVar3;
      }
      iVar27 = iVar27 + 1;
      puVar13 = puVar13 + 1;
    } while (iVar27 < iVar11);
    puVar20 = param_1 + iVar9 + 0x42680;
    iVar27 = iVar9;
    do {
      if (iVar27 < 0x280) {
        *puVar20 = uVar3;
      }
      iVar27 = iVar27 + 1;
      puVar20 = puVar20 + 1;
    } while (iVar27 < iVar11);
    uVar3 = *(ushort *)(puVar6 + 0x24);
    puVar20 = param_1 + iVar9 + 0x46000;
    iVar27 = iVar9;
    do {
      if (iVar27 < 0x280) {
        *puVar20 = uVar3;
      }
      iVar27 = iVar27 + 1;
      puVar20 = puVar20 + 1;
    } while (iVar27 < iVar11);
    puVar20 = param_1 + iVar9 + 0x46280;
    do {
      if (iVar9 < 0x280) {
        *puVar20 = uVar3;
      }
      iVar9 = iVar9 + 1;
      puVar20 = puVar20 + 1;
    } while (iVar9 < iVar11);
    local_64[0] = 0x2d;
    fmt_time(local_64 + 1,param_8 - param_7);
    uVar15 = (uint)local_64[0];
    if (uVar15 != 0) {
      uVar4 = *(undefined2 *)(puVar6 + 0x28);
      pbVar26 = local_64;
      iVar11 = 0;
      uVar23 = uVar15;
      do {
        pbVar26 = pbVar26 + 1;
        uVar12 = 0xf;
        if ((uVar23 - 0x20 & 0xff) < 0x5f) {
          uVar12 = (uint)(byte)(&FP_FONT)[(uVar23 - 0x20) * 0x450];
        }
        uVar23 = (uint)*pbVar26;
        iVar11 = iVar11 + uVar12;
      } while (uVar23 != 0);
      iVar11 = 0x260 - iVar11;
      pbVar26 = local_64;
      do {
        ui_char(param_1,iVar11,0x180,uVar15,uVar4);
        bVar2 = *pbVar26;
        uVar23 = 0xf;
        pbVar26 = pbVar26 + 1;
        if ((bVar2 - 0x20 & 0xff) < 0x5f) {
          uVar23 = (uint)(byte)(&FP_FONT)[(bVar2 - 0x20) * 0x450];
        }
        uVar15 = (uint)*pbVar26;
        iVar11 = iVar11 + uVar23;
      } while (uVar15 != 0);
    }
  }
  return;
}


// ===== ui_text_clip @ 10403cc0 =====

void ui_text_clip(undefined4 param_1,int param_2,undefined4 param_3,int param_4,byte *param_5,
                 undefined4 param_6)

{
  byte bVar1;
  int iVar2;
  uint uVar3;
  byte *pbVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  
  gp = &__global_pointer_;
  uVar6 = (uint)*param_5;
  if (uVar6 == 0) {
    if (-1 < param_4) {
      return;
    }
  }
  else {
    iVar2 = 0;
    pbVar4 = param_5;
    uVar5 = uVar6;
    do {
      pbVar4 = pbVar4 + 1;
      uVar3 = 0xf;
      if ((uVar5 - 0x20 & 0xff) < 0x5f) {
        uVar3 = (uint)(byte)(&FP_FONT)[(uVar5 - 0x20) * 0x450];
      }
      uVar5 = (uint)*pbVar4;
      iVar2 = iVar2 + uVar3;
    } while (uVar5 != 0);
    iVar7 = param_4 + param_2;
    if (iVar2 <= param_4) {
      do {
        ui_char(param_1,param_2,param_3,uVar6,param_6);
        bVar1 = *param_5;
        uVar5 = 0xf;
        param_5 = param_5 + 1;
        if ((bVar1 - 0x20 & 0xff) < 0x5f) {
          uVar5 = (uint)(byte)(&FP_FONT)[(bVar1 - 0x20) * 0x450];
        }
        uVar6 = (uint)*param_5;
        param_2 = param_2 + uVar5;
      } while (uVar6 != 0);
      return;
    }
    do {
      uVar5 = 0xf;
      if ((uVar6 - 0x20 & 0xff) < 0x5f) {
        uVar5 = (uint)(byte)(&FP_FONT)[(uVar6 - 0x20) * 0x450];
      }
      iVar2 = uVar5 + param_2;
      if (iVar7 < iVar2 + 0x10) break;
      ui_char(param_1,param_2,param_3,uVar6,param_6);
      uVar6 = (uint)param_5[1];
      param_5 = param_5 + 1;
      param_2 = iVar2;
    } while (uVar6 != 0);
  }
  pbVar4 = (byte *)0x1041738c;
  uVar6 = 0x2e;
  do {
    ui_char(param_1,param_2,param_3,uVar6,param_6);
    pbVar4 = pbVar4 + 1;
    uVar5 = 0xf;
    if ((uVar6 - 0x20 & 0xff) < 0x5f) {
      uVar5 = (uint)(byte)(&FP_FONT)[(uVar6 - 0x20) * 0x450];
    }
    uVar6 = (uint)*pbVar4;
    param_2 = param_2 + uVar5;
  } while (pbVar4 != (byte *)0x1041738e);
  return;
}


// ===== ui_vgrad @ 10403800 =====

void ui_vgrad(int param_1,uint param_2,int param_3,int param_4,int param_5,undefined4 param_6,
             undefined4 param_7)

{
  int iVar1;
  undefined2 uVar2;
  int iVar3;
  uint uVar4;
  undefined2 *puVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  
  gp = &__global_pointer_;
  if (param_5 < 1) {
    return;
  }
  iVar8 = param_5;
  if (param_5 < 2) {
    iVar8 = 2;
  }
  iVar6 = param_3 * 0x500;
  iVar1 = 0;
  do {
    if ((uint)(iVar1 + param_3) < 0x1e0) {
      if (param_4 < 1) {
        do {
          iVar3 = iVar1 + 1;
          iVar1 = iVar1 + 2;
          if (param_5 == iVar3) {
            return;
          }
          if (param_5 == iVar1) {
            return;
          }
          iVar6 = iVar6 + 0xa00;
        } while ((uint)(iVar1 + param_3) < 0x1e0);
        goto LAB_ram_10403856;
      }
      do {
        iVar7 = iVar6;
        iVar3 = iVar1;
        uVar2 = lerp565(param_6,param_7,iVar3,iVar8 + -1);
        puVar5 = (undefined2 *)(param_1 + param_2 * 2 + iVar7);
        uVar4 = param_2;
        do {
          if (uVar4 < 0x280) {
            *puVar5 = uVar2;
          }
          uVar4 = uVar4 + 1;
          puVar5 = puVar5 + 1;
        } while ((int)uVar4 < (int)(param_2 + param_4));
        iVar1 = iVar3 + 1;
        if (param_5 == iVar1) {
          return;
        }
        iVar6 = iVar7 + 0x500;
      } while ((uint)(iVar1 + param_3) < 0x1e0);
      iVar1 = iVar3 + 2;
      iVar6 = iVar7 + 0xa00;
    }
    else {
LAB_ram_10403856:
      iVar1 = iVar1 + 1;
      iVar6 = iVar6 + 0x500;
    }
    if (param_5 == iVar1) {
      return;
    }
  } while( true );
}


// ===== ui_fill @ 10403700 =====

void ui_fill(int param_1,uint param_2,uint param_3,int param_4,int param_5,undefined2 param_6)

{
  uint uVar1;
  int iVar2;
  undefined2 *puVar3;
  int iVar4;
  
  gp = &__global_pointer_;
  if (0 < param_5) {
    param_5 = param_5 + param_3;
    iVar4 = param_3 * 0x500;
    do {
      if (param_3 < 0x1e0) {
        if (param_4 < 1) {
          do {
            iVar2 = param_3 + 1;
            param_3 = param_3 + 2;
            if (param_5 <= iVar2) {
              return;
            }
            if (param_5 <= (int)param_3) {
              return;
            }
            iVar4 = iVar4 + 0xa00;
          } while ((int)param_3 < 0x1e0);
        }
        else {
          do {
            puVar3 = (undefined2 *)(param_1 + param_2 * 2 + iVar4);
            uVar1 = param_2;
            do {
              if (uVar1 < 0x280) {
                *puVar3 = param_6;
              }
              uVar1 = uVar1 + 1;
              puVar3 = puVar3 + 1;
            } while ((int)uVar1 < (int)(param_2 + param_4));
            param_3 = param_3 + 1;
            if (param_5 <= (int)param_3) {
              return;
            }
            iVar4 = iVar4 + 0x500;
          } while (param_3 != 0x1e0);
        }
      }
      param_3 = param_3 + 1;
      iVar4 = iVar4 + 0x500;
    } while ((int)param_3 < param_5);
  }
  return;
}


// ===== ui_status_bar @ 10403f00 =====

void ui_status_bar(int param_1,byte *param_2,uint param_3)

{
  byte bVar1;
  undefined2 uVar2;
  undefined *puVar3;
  undefined2 uVar4;
  undefined2 uVar5;
  uint uVar6;
  uint uVar7;
  byte *pbVar8;
  int iVar9;
  undefined2 *puVar10;
  uint uVar11;
  undefined2 *puVar12;
  int iVar13;
  int iVar14;
  undefined2 *puVar15;
  int iVar16;
  
  puVar3 = T;
  gp = &__global_pointer_;
  uVar5 = *(undefined2 *)(T + 10);
  uVar2 = *(undefined2 *)(T + 8);
  puVar15 = (undefined2 *)(param_1 + 0x500);
  iVar16 = 0;
  do {
    uVar4 = lerp565(uVar2,uVar5,iVar16,0x29);
    puVar10 = puVar15 + -0x280;
    do {
      puVar12 = puVar10;
      *puVar12 = uVar4;
      puVar10 = puVar12 + 1;
    } while (puVar12 + 1 != puVar15);
    iVar16 = iVar16 + 1;
    puVar15 = puVar12 + 0x281;
  } while (iVar16 != 0x2a);
  uVar5 = *(undefined2 *)(puVar3 + 0xc);
  puVar15 = (undefined2 *)(param_1 + 0xc800);
  puVar10 = (undefined2 *)(param_1 + 0xcd00);
  do {
    *puVar15 = uVar5;
    puVar15 = puVar15 + 1;
  } while (puVar15 != puVar10);
  do {
    *puVar10 = uVar5;
    puVar10 = puVar10 + 1;
  } while (puVar10 != (undefined2 *)(param_1 + 0xd200));
  if ((param_2 != (byte *)0x0) && (uVar7 = (uint)*param_2, uVar7 != 0)) {
    uVar5 = *(undefined2 *)(puVar3 + 6);
    iVar16 = 0;
    pbVar8 = param_2;
    uVar11 = uVar7;
    do {
      pbVar8 = pbVar8 + 1;
      uVar6 = 0xf;
      if ((uVar11 - 0x20 & 0xff) < 0x5f) {
        uVar6 = (uint)(byte)(&FP_FONT)[(uVar11 - 0x20) * 0x450];
      }
      uVar11 = (uint)*pbVar8;
      iVar16 = iVar16 + uVar6;
    } while (uVar11 != 0);
    iVar16 = 0x140 - iVar16 / 2;
    do {
      ui_char(param_1,iVar16,2,uVar7,uVar5);
      bVar1 = *param_2;
      uVar11 = 0xf;
      param_2 = param_2 + 1;
      if ((bVar1 - 0x20 & 0xff) < 0x5f) {
        uVar11 = (uint)(byte)(&FP_FONT)[(bVar1 - 0x20) * 0x450];
      }
      uVar7 = (uint)*param_2;
      iVar16 = iVar16 + uVar11;
    } while (uVar7 != 0);
  }
  if (g_play != 0) {
    uVar5 = *(undefined2 *)(puVar3 + 6);
    if (g_play == 1) {
      iVar16 = 0x3c00;
      iVar13 = 0;
      iVar9 = 0x22;
      uVar7 = 1;
      do {
        iVar14 = 0x24 - iVar9;
        uVar11 = uVar7;
        while( true ) {
          puVar15 = (undefined2 *)(param_1 + 0x440 + iVar16);
          do {
            *puVar15 = uVar5;
            puVar15 = puVar15 + 1;
          } while (puVar15 != (undefined2 *)((iVar14 + iVar13) * 2 + param_1 + 0x4040));
          uVar7 = uVar11 + 1;
          iVar16 = iVar16 + 0x500;
          iVar9 = iVar9 + -2;
          iVar13 = iVar13 + 0x280;
          if (uVar7 == 0x13) goto LAB_ram_104040b8;
          if (uVar11 < 8) break;
          uVar11 = uVar7;
          iVar14 = iVar9;
          if (iVar9 == 0) goto LAB_ram_104040b8;
        }
      } while( true );
    }
    if (g_play == 2) {
      iVar9 = param_1 + 0x3c0c;
      iVar16 = iVar9;
      do {
        iVar13 = iVar16 + -0xc;
        do {
          *(undefined2 *)(iVar13 + 0x440) = uVar5;
          iVar13 = iVar13 + 2;
        } while (iVar13 != iVar16);
        iVar16 = iVar16 + 0x500;
      } while (iVar16 != param_1 + 0x960c);
      do {
        iVar16 = iVar9 + -0xc;
        do {
          *(undefined2 *)(iVar16 + 0x454) = uVar5;
          iVar16 = iVar16 + 2;
        } while (iVar16 != iVar9);
        iVar9 = iVar9 + 0x500;
      } while (iVar9 != param_1 + 0x960c);
    }
  }
LAB_ram_104040b8:
  uVar5 = *(undefined2 *)(puVar3 + 0x2e);
  puVar15 = (undefined2 *)(param_1 + 0x40e0);
  do {
    puVar10 = puVar15 + -0x30;
    do {
      puVar12 = puVar10;
      *puVar12 = uVar5;
      puVar10 = puVar12 + 1;
    } while (puVar12 + 1 != puVar15);
    puVar15 = puVar12 + 0x281;
  } while (puVar15 != (undefined2 *)(param_1 + 0xa4e0));
  uVar5 = *(undefined2 *)(puVar3 + 4);
  puVar15 = (undefined2 *)(param_1 + 0x4adc);
  do {
    puVar10 = puVar15 + -0x2c;
    do {
      puVar12 = puVar10;
      *puVar12 = uVar5;
      puVar10 = puVar12 + 1;
    } while (puVar12 + 1 != puVar15);
    puVar15 = puVar12 + 0x281;
  } while ((undefined2 *)(param_1 + 0x9adc) != puVar15);
  uVar5 = *(undefined2 *)(puVar3 + 0x2e);
  puVar15 = (undefined2 *)(param_1 + 0x54e0);
  do {
    *puVar15 = uVar5;
    puVar15[1] = uVar5;
    puVar15[2] = uVar5;
    puVar15[3] = uVar5;
    puVar15 = puVar15 + 0x280;
  } while ((undefined2 *)(param_1 + 0x90e0) != puVar15);
  uVar7 = 100;
  if ((int)param_3 < 0x65) {
    uVar7 = param_3 & (int)~param_3 >> 0x1f;
  }
  if ((int)param_3 < 0x10) {
    uVar5 = *(undefined2 *)(puVar3 + 0x2c);
  }
  else {
    uVar5 = *(undefined2 *)(puVar3 + 0x2a);
  }
  if (99 < (int)(uVar7 * 0x28)) {
    iVar16 = 0x5000;
    do {
      iVar9 = param_1 + iVar16;
      iVar13 = 0x244;
      do {
        *(undefined2 *)(iVar9 + 0x488) = uVar5;
        iVar13 = iVar13 + 1;
        iVar9 = iVar9 + 2;
      } while (iVar13 < (int)((uVar7 * 0x28) / 100 + 0x244));
      iVar16 = iVar16 + 0x500;
    } while (iVar16 != 0x8c00);
  }
  return;
}


// ===== ui_bg @ 10403580 =====

undefined2 ui_bg(void)

{
  gp = &__global_pointer_;
  return *(undefined2 *)(T + 4);
}


// ===== ui_set_playstate @ 10403ec0 =====

void ui_set_playstate(undefined4 param_1)

{
  gp = &__global_pointer_;
  g_play = param_1;
  return;
}


// ===== ui_theme_index @ 104034c0 =====

undefined4 ui_theme_index(void)

{
  gp = &__global_pointer_;
  return g_ti;
}


// ===== ui_fg @ 10403600 =====

undefined2 ui_fg(void)

{
  gp = &__global_pointer_;
  return *(undefined2 *)(T + 6);
}


// ===== ui_set_theme @ 10403480 =====

void ui_set_theme(uint param_1)

{
  gp = &__global_pointer_;
  if ((int)param_1 < 3) {
    g_ti = param_1 & (int)~param_1 >> 0x1f;
  }
  else {
    g_ti = 2;
  }
  T = (undefined *)(&IPOD_THEMES + g_ti * 0xc);
  return;
}


// ===== main @ 1040b100 =====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void main(void)

{
  longlong lVar1;
  longlong lVar2;
  longlong lVar3;
  uint uVar4;
  int iVar5;
  undefined4 uVar6;
  FILE *__stream;
  size_t sVar7;
  char *pcVar8;
  char *pcVar9;
  undefined4 uVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  void *__dest;
  uint uVar14;
  uint uVar15;
  char cVar16;
  undefined4 *puVar17;
  code *pcVar18;
  undefined4 *puVar19;
  short *psVar20;
  uint uVar21;
  int iVar22;
  int iVar23;
  undefined4 *puVar24;
  int iVar25;
  char *pcVar26;
  uint uVar27;
  uint uVar28;
  int *piVar29;
  longlong lVar30;
  UDItype UVar31;
  int iStack_a4;
  uint uStack_88;
  uint uStack_84;
  undefined4 *puStack_6c;
  char *apcStack_58 [5];
  char *pcStack_44;
  
  (**(code **)(_of_svc_ptr + 0xc))();
  apcStack_58[0] = (char *)0x1e00280;
  apcStack_58[1] = (char *)0x30000;
  if (0x5e < *(uint *)(_of_svc_ptr + 8)) {
    if ((*(code **)(_of_svc_ptr + 0x184) != (code *)0x0) &&
       (iVar5 = (**(code **)(_of_svc_ptr + 0x184))(apcStack_58), iVar5 == 0)) goto LAB_ram_1040b14e;
  }
  (**(code **)(_of_svc_ptr + 0x38))(3);
LAB_ram_1040b14e:
  (**(code **)(_of_svc_ptr + 0x34))(1);
  uVar6 = (**(code **)(_of_svc_ptr + 0x10))();
  ui_boot(uVar6,0);
  (**(code **)(_of_svc_ptr + 0x14))();
  (**(code **)(_of_svc_ptr + 0xac))();
  g_ring = (**(code **)(_of_svc_ptr + 0xb4))();
  (**(code **)(_of_svc_ptr + 0xf8))(48000);
  __stream = (FILE *)open_any(s_playlist_tsv_ram_10417650,_DAT_ram_c0de000e,s_iso9660_ram_1041763c,1
                              ,0,0,3);
  if (__stream != (FILE *)0x0) {
    sVar7 = fread_unlocked(&plbuf,1,0x27fff,__stream);
    pcVar26 = &plbuf;
    fclose(__stream);
    (&plbuf)[sVar7] = 0;
    if (plbuf != '\0') {
      while (iVar5 = ntracks, ntracks < 0x200) {
        pcVar8 = strchr(pcVar26,10);
        if (pcVar8 != (char *)0x0) {
          *pcVar8 = '\0';
        }
        pcVar9 = strchr(pcVar26,0xd);
        if (pcVar9 != (char *)0x0) {
          *pcVar9 = '\0';
        }
        cVar16 = *pcVar26;
        if (cVar16 != '\0') {
          iVar11 = 1;
          pcVar9 = pcVar26;
          do {
            pcVar9 = pcVar9 + 1;
            if (cVar16 == '\t') goto LAB_ram_1040b290;
            cVar16 = *pcVar9;
            if (cVar16 == '\0') break;
            while (pcVar9 = pcVar9 + 1, cVar16 == '\t') {
LAB_ram_1040b290:
              cVar16 = *pcVar9;
              pcVar9[-1] = '\0';
              apcStack_58[iVar11] = pcVar9;
              iVar11 = iVar11 + 1;
              if (cVar16 == '\0') goto LAB_ram_1040b4f4;
              if (iVar11 == 6) goto LAB_ram_1040b2aa;
            }
            cVar16 = *pcVar9;
          } while (cVar16 != '\0');
LAB_ram_1040b4f4:
          if (3 < iVar11) {
LAB_ram_1040b2aa:
            iVar22 = iVar5 * 0x138;
            ntracks = iVar5 + 1;
            snprintf(tracks + iVar22,0x40,&DAT_ram_10417450,pcVar26);
            snprintf(tracks + iVar22 + 0x40,0x50,&DAT_ram_10417450,apcStack_58[1]);
            snprintf(tracks + iVar22 + 0x90,0x50,&DAT_ram_10417450,apcStack_58[2]);
            snprintf(tracks + iVar22 + 0xe0,0x50,&DAT_ram_10417450,apcStack_58[3]);
            if (iVar11 == 4) {
              *(undefined4 *)(tracks + iVar22 + 0x130) = 0;
LAB_ram_1040b320:
              iVar11 = 0x100;
            }
            else {
              iVar13 = atoi(apcStack_58[4]);
              *(int *)(tracks + iVar22 + 0x130) = iVar13;
              if (iVar11 != 6) goto LAB_ram_1040b320;
              iVar11 = atoi(pcStack_44);
            }
            *(int *)(tracks + iVar5 * 0x138 + 0x134) = iVar11;
            add_unique(artists,&nartists,tracks + iVar22 + 0x90);
            add_unique(albums,&nalbums,tracks + iVar22 + 0xe0);
          }
        }
        if ((pcVar8 == (char *)0x0) || (pcVar26 = pcVar8 + 1, pcVar8[1] == '\0')) break;
      }
    }
    qsort(artists,nartists,0x50,cmpstr);
    qsort(albums,nalbums,0x50,cmpstr);
  }
  srand(_DAT_ram_c0de0006 | 1);
  uVar28 = _DAT_ram_c0de0006;
  while( true ) {
    uVar15 = (_DAT_ram_c0de0006 - uVar28) * 100;
    pcVar18 = *(code **)(_of_svc_ptr + 0x10);
    if (0x1d96f < uVar15) break;
    uVar6 = (*pcVar18)(0,(int)((ulonglong)uVar15 * 0x1b4e81b5 >> 0x20),0,0,pcVar18,_of_svc_ptr,3);
    ui_boot(uVar6,uVar15 / 0x4b0);
    (**(code **)(_of_svc_ptr + 0x14))();
    if (uVar15 / 0x4b0 == 100) goto LAB_ram_1040b43c;
    usleep(16000);
  }
  uVar6 = (*pcVar18)(0,uVar15,0,0,pcVar18,_of_svc_ptr,3);
  ui_boot(uVar6,100);
  (**(code **)(_of_svc_ptr + 0x14))();
LAB_ram_1040b43c:
  if (ntracks == 0) {
    uVar6 = (**(code **)(_of_svc_ptr + 0x10))();
    uVar10 = ui_bg();
    ui_clear(uVar6,uVar10);
    ui_status_bar(uVar6,s_PocketTunes_ram_10417660,100);
    uVar10 = ui_fg();
    ui_text(uVar6,0x12,0xdc,s_No_tracks_found_in_music_iso_ram_1041766c,uVar10);
    (**(code **)(_of_svc_ptr + 0x14))();
    do {
      usleep(100000);
    } while( true );
  }
  nav = 0;
  DAT_ram_104d4434 = 0;
  DAT_ram_104d4438 = 0;
  DAT_ram_104d443c = 0;
  navdepth = 1;
  iVar11 = ui_visible_rows();
  puStack_6c = &curlist;
  uStack_84 = 0;
  iStack_a4 = -2;
  uVar28 = 1;
  uStack_88 = 0xffffffff;
  iVar5 = -1;
LAB_ram_1040b600:
  do {
    (**(code **)(_of_svc_ptr + 0x44))();
    (**(code **)(_of_svc_ptr + 0x48))(0,&_of_input_p0);
    (**(code **)(_of_svc_ptr + 0x48))(1,_of_input_p1);
    lVar1 = CONCAT44(DAT_ram_104d3c14,DAT_ram_104d3c10);
    if (screen == 2) {
      iVar22 = 0x8340;
LAB_ram_1040b644:
      iVar13 = P;
      g_target = iVar22;
      lVar1 = CONCAT44(DAT_ram_104d3c14,DAT_ram_104d3c10);
      if (P != 0) {
        iVar13 = 2;
        lVar1 = CONCAT44(DAT_ram_104d3c14,DAT_ram_104d3c10);
        if (DAT_ram_104cbdec == 0) {
          if ((DAT_ram_104d3c20 != (FILE *)0x0) && (DAT_ram_104d3c24 < DAT_ram_104d3c28)) {
            sVar7 = 0x20000;
            if (DAT_ram_104d3c28 < DAT_ram_104d3c24 + 0x20000) {
              sVar7 = DAT_ram_104d3c28 - DAT_ram_104d3c24;
            }
            sVar7 = fread_unlocked(filebuf + DAT_ram_104d3c24,1,sVar7,DAT_ram_104d3c20);
            DAT_ram_104d3c24 = sVar7 + DAT_ram_104d3c24;
            if (DAT_ram_104d3c28 <= DAT_ram_104d3c24 || sVar7 == 0) {
              fclose(DAT_ram_104d3c20);
              DAT_ram_104d3c20 = (FILE *)0x0;
            }
          }
          lVar1 = CONCAT44(DAT_ram_104d3c14,DAT_ram_104d3c10);
          if (DAT_ram_104cbdf0 == 0) {
            iVar22 = 0x40;
            do {
              DAT_ram_104d3c14 = (undefined4)((ulonglong)lVar1 >> 0x20);
              DAT_ram_104d3c10 = (undefined4)lVar1;
              iVar12 = (**(code **)(_of_svc_ptr + 0xb4))();
              iVar13 = g_ring;
              lVar1 = CONCAT44(DAT_ram_104d3c14,DAT_ram_104d3c10);
              if (iVar12 < 0x400) break;
              iVar12 = (**(code **)(_of_svc_ptr + 0xb4))();
              lVar1 = CONCAT44(DAT_ram_104d3c14,DAT_ram_104d3c10);
              if (g_target <= iVar13 - iVar12) break;
              lVar3 = lVar1;
              if (DAT_ram_104d1778 == 0) {
LAB_ram_1040be40:
                DAT_ram_104cbdf0 = 1;
                lVar1 = lVar3;
                break;
              }
              lVar30 = drmp3_read_pcm_frames_raw_part_0(&DAT_ram_104cbdf8,0x400,0,&chunk);
              iVar13 = _of_svc_ptr;
              lVar3 = CONCAT44(DAT_ram_104d3c14,DAT_ram_104d3c10);
              uVar15 = (uint)lVar30;
              if (lVar30 == 0) goto LAB_ram_1040be40;
              iVar12 = (int)(DAT_ram_104d3c2c * g_vol) / 100;
              if (iVar12 == 0x100) {
LAB_ram_1040b73e:
                (**(code **)(iVar13 + 0xb0))(&chunk,uVar15);
                lVar2 = CONCAT44(DAT_ram_104d3c14,DAT_ram_104d3c10);
                lVar3 = lVar30 + lVar2;
                lVar1 = lVar30 + lVar2;
                if (((int)((ulonglong)lVar30 >> 0x20) == 0) &&
                   (lVar1 = lVar30 + lVar2, uVar15 < 0x400)) goto LAB_ram_1040be40;
              }
              else {
                if (0 < (int)uVar15) {
                  psVar20 = &chunk;
                  do {
                    iVar25 = *psVar20 * iVar12 >> 8;
                    iVar23 = 0x7fff;
                    if ((iVar25 < 0x8000) && (iVar23 = 0x18000, -0x8001 < iVar25)) {
                      iVar23 = iVar25;
                    }
                    *psVar20 = (short)iVar23;
                    psVar20 = psVar20 + 1;
                  } while (psVar20 != &chunk + uVar15 * 2);
                  goto LAB_ram_1040b73e;
                }
                (**(code **)(_of_svc_ptr + 0xb0))(&chunk,uVar15);
                lVar1 = lVar30 + CONCAT44(DAT_ram_104d3c14,DAT_ram_104d3c10);
              }
              iVar22 = iVar22 + -1;
            } while (iVar22 != 0);
          }
          else {
            iVar22 = (**(code **)(_of_svc_ptr + 0xb4))();
            lVar1 = CONCAT44(DAT_ram_104d3c14,DAT_ram_104d3c10);
            if ((g_ring + -0x400 <= iVar22) &&
               (lVar1 = CONCAT44(DAT_ram_104d3c14,DAT_ram_104d3c10), qlen != 0)) {
              qpos = qpos + 1;
              if (qlen != 0) {
                qpos = (int)qpos % qlen;
              }
              player_load_current();
              lVar1 = CONCAT44(DAT_ram_104d3c14,DAT_ram_104d3c10);
            }
          }
          iVar13 = P;
          if (P != 0) {
            iVar13 = (DAT_ram_104cbdec != 0) + 1;
          }
        }
      }
    }
    else {
      iVar22 = 0x3840;
      if (screen != 1) goto LAB_ram_1040b644;
      if (P != 0) {
        iVar13 = np_scrolling_part_0();
        iVar22 = 0x8340;
        if (iVar13 == 0) {
          iVar22 = 0x3840;
        }
        goto LAB_ram_1040b644;
      }
      g_target = 0x3840;
      iVar13 = P;
    }
    DAT_ram_104d3c14 = (undefined4)((ulonglong)lVar1 >> 0x20);
    DAT_ram_104d3c10 = (undefined4)lVar1;
    g_ps = iVar13;
    ui_set_playstate();
    iVar22 = g_ps;
    if (g_ps != iVar5) {
      uVar28 = uVar28 | screen == 0;
      iStack_a4 = -2;
    }
    iVar5 = iVar22;
    if (screen != 2) {
      if ((int)(DAT_ram_1254be1c << 0x10) < 0) {
        if (P != 0) {
          uVar28 = uVar28 | screen == 0;
          DAT_ram_104cbdec = (uint)(DAT_ram_104cbdec == 0);
          if ((DAT_ram_1254be1c & 0x4000) != 0) {
LAB_ram_1040b7d8:
            screen = 1;
          }
          iStack_a4 = -2;
joined_r0x1040be7a:
          if ((DAT_ram_1254be1c & 0x200) == 0) {
joined_r0x1040bea8:
            if ((DAT_ram_1254be1c & 0x100) == 0) goto LAB_ram_1040b7f6;
            if (qlen != 0) {
              qpos = (qpos - 1) + qlen;
              if (qlen != 0) {
                qpos = (int)qpos % qlen;
              }
              player_load_current();
            }
          }
          else if (qlen == 0) {
            if ((DAT_ram_1254be1c & 0x100) == 0) {
              iStack_a4 = -2;
              goto LAB_ram_1040b7f6;
            }
          }
          else {
            qpos = qpos + 1;
            if (qlen != 0) {
              qpos = (int)qpos % qlen;
            }
            player_load_current();
            if (P != 0) {
              iStack_a4 = -2;
              goto joined_r0x1040bea8;
            }
          }
          iStack_a4 = -2;
        }
LAB_ram_1040b7f6:
        uVar15 = uVar28;
        if (screen != 0) goto LAB_ram_1040bc40;
LAB_ram_1040b7fa:
        iVar12 = navdepth + -1;
        uVar6 = (&nav)[iVar12 * 4];
        iVar13 = frame_count_isra_0(uVar6);
        uVar27 = DAT_ram_1254be1c;
        iVar22 = P;
        uVar28 = DAT_ram_1254be1c & 1;
        if (((DAT_ram_1254be1c & 2) == 0) || (iVar13 + -1 <= (int)(&DAT_ram_104d4434)[iVar12 * 4]))
        {
          if ((uVar28 != 0) && (iVar23 = (&DAT_ram_104d4434)[iVar12 * 4], 0 < iVar23)) {
LAB_ram_1040b840:
            iVar23 = iVar23 + -1;
            (&DAT_ram_104d4434)[iVar12 * 4] = iVar23;
            if (iVar22 == 0) {
              if ((uVar27 & 0x200) != 0) {
                iVar25 = iVar23 + iVar11;
                (&DAT_ram_104d4434)[iVar12 * 4] = iVar25;
                if (iVar13 <= iVar25) goto LAB_ram_1040bfa6;
                if ((uVar27 & 0x100) == 0) {
                  iVar23 = iVar25;
                  goto LAB_ram_1040b880;
                }
                goto LAB_ram_1040bf3e;
              }
              if ((uVar27 & 0x100) != 0) goto LAB_ram_1040bf36;
            }
            goto LAB_ram_1040b880;
          }
          if (P == 0) {
            if ((DAT_ram_1254be1c & 0x200) != 0) goto LAB_ram_1040bbbc;
            if ((DAT_ram_1254be1c & 0x100) != 0) goto LAB_ram_1040bf30;
          }
          if (uVar15 != 0) goto LAB_ram_1040be4e;
        }
        else {
          iVar23 = (&DAT_ram_104d4434)[iVar12 * 4] + 1;
          (&DAT_ram_104d4434)[iVar12 * 4] = iVar23;
          if (uVar28 == 0) {
            if (iVar22 == 0) {
LAB_ram_1040bf96:
              if ((uVar27 & 0x200) == 0) {
                if ((uVar27 & 0x100) == 0) goto LAB_ram_1040be4e;
LAB_ram_1040bf30:
                iVar23 = (&DAT_ram_104d4434)[iVar12 * 4];
LAB_ram_1040bf36:
                iVar22 = iVar23 - iVar11;
              }
              else {
LAB_ram_1040bbbc:
                iVar22 = (&DAT_ram_104d4434)[iVar12 * 4];
                iVar23 = iVar11 + iVar22;
                (&DAT_ram_104d4434)[iVar12 * 4] = iVar23;
                if (iVar13 <= iVar23) {
LAB_ram_1040bfa6:
                  iVar23 = iVar13 + -1;
                  iVar22 = 0;
                  (&DAT_ram_104d4434)[iVar12 * 4] = iVar23;
                  if ((uVar27 & 0x100) == 0) goto LAB_ram_1040b880;
                  goto LAB_ram_1040bf36;
                }
                if ((uVar27 & 0x100) == 0) {
                  iVar22 = 0;
                  goto LAB_ram_1040b880;
                }
              }
              iVar23 = iVar22;
              if (iVar22 < 0) {
                iVar22 = 0;
                (&DAT_ram_104d4434)[iVar12 * 4] = 0;
                iVar23 = 0;
              }
              else {
LAB_ram_1040bf3e:
                iVar22 = 0;
                (&DAT_ram_104d4434)[iVar12 * 4] = iVar23;
              }
            }
          }
          else {
            if (0 < iVar23) goto LAB_ram_1040b840;
            if (iVar22 == 0) goto LAB_ram_1040bf96;
LAB_ram_1040be4e:
            iVar23 = (&DAT_ram_104d4434)[iVar12 * 4];
          }
LAB_ram_1040b880:
          iVar13 = (&DAT_ram_104d4438)[iVar12 * 4];
          if (iVar23 < (int)(&DAT_ram_104d4438)[iVar12 * 4]) {
            (&DAT_ram_104d4438)[iVar12 * 4] = iVar23;
            iVar13 = iVar23;
          }
          if (iVar13 + iVar11 <= iVar23) {
            (&DAT_ram_104d4438)[iVar12 * 4] = (iVar23 - iVar11) + 1;
          }
          uVar15 = 1;
        }
        iVar13 = curlen;
        uVar28 = uVar15;
        if ((uVar27 & 0x10) == 0) {
          if (((DAT_ram_1254be1c & 0x20) == 0) || (navdepth < 2)) {
            if ((screen == 0) && (uVar15 != 0)) goto LAB_ram_1040b98c;
            goto LAB_ram_1040ba80;
          }
          goto LAB_ram_1040b980;
        }
        uVar28 = (&DAT_ram_104d4434)[iVar12 * 4];
        switch(uVar6) {
        case 0:
          switch(uVar28) {
          case 0:
            uVar28 = 0;
            uVar6 = 1;
            break;
          case 1:
            nav_push(2,0);
            if ((DAT_ram_1254be1c & 0x20) == 0) {
              if (screen != 0) goto LAB_ram_1040ba80;
              goto LAB_ram_1040b98c;
            }
            if (1 < navdepth) goto LAB_ram_1040b980;
            if (screen == 0) goto LAB_ram_1040b98c;
            goto LAB_ram_1040ba80;
          case 2:
            uVar28 = 0;
            uVar6 = 3;
            break;
          case 3:
            shuffle_all();
            uVar28 = DAT_ram_1254be1c & 0x20;
            if (P == 0) goto joined_r0x1040c150;
LAB_ram_1040c168:
            screen = 1;
            if (uVar28 == 0) {
              iStack_a4 = -2;
              uVar28 = 1;
              goto LAB_ram_1040ba80;
            }
            iStack_a4 = -2;
            if (1 < navdepth) goto LAB_ram_1040b980;
            goto LAB_ram_1040ba02;
          case 4:
            uVar28 = DAT_ram_1254be1c & 0x20;
            if (iVar22 != 0) goto LAB_ram_1040c168;
            goto joined_r0x1040c150;
          case 5:
            uVar28 = 0;
            uVar6 = 8;
            break;
          case 6:
            uVar28 = 0;
            uVar6 = 6;
            break;
          default:
            goto joined_r0x1040b9e4;
          }
          break;
        default:
          if (0 < curlen) {
            puVar17 = &curlist + curlen;
            puVar19 = &queue;
            puVar24 = puStack_6c;
            do {
              uVar6 = *puVar24;
              puVar24 = puVar24 + 1;
              *puVar19 = uVar6;
              puVar19 = puVar19 + 1;
            } while (puVar24 != puVar17);
            qlen = iVar13;
            if ((int)uVar28 < 0) {
              uVar28 = 0;
            }
            else if (iVar13 <= (int)uVar28) {
              uVar28 = iVar13 - 1;
            }
            qpos = uVar28;
            player_load_current();
          }
          screen = 1;
          iStack_a4 = -2;
          goto LAB_ram_1040b942;
        case 2:
          nav_push(4,uVar28);
          if ((DAT_ram_1254be1c & 0x20) == 0) {
            uVar28 = 1;
            if (screen == 0) goto LAB_ram_1040b98c;
            goto LAB_ram_1040ba80;
          }
          goto LAB_ram_1040b9e6;
        case 3:
          uVar6 = 5;
          break;
        case 6:
          uVar28 = 0;
          uVar6 = 7;
          break;
        case 7:
          ui_set_theme(uVar28);
          goto joined_r0x1040b9e4;
        case 8:
          cur_game = (&GAMES)[uVar28];
          (**(code **)(cur_game + 4))();
          screen = 2;
LAB_ram_1040b942:
          uVar28 = uVar15;
          if ((DAT_ram_1254be1c & 0x20) != 0) {
            if (navdepth < 2) goto LAB_ram_1040ba80;
            goto LAB_ram_1040b980;
          }
          goto LAB_ram_1040ba80;
        }
        nav_push(uVar6,uVar28);
joined_r0x1040b9e4:
        uVar28 = DAT_ram_1254be1c & 0x20;
joined_r0x1040c150:
        if (uVar28 == 0) {
          if (screen == 0) goto LAB_ram_1040b98c;
LAB_ram_1040ba02:
          uVar28 = 1;
          usleep(5000);
        }
        else {
LAB_ram_1040b9e6:
          if (1 < navdepth) {
LAB_ram_1040b980:
            navdepth = navdepth + -1;
          }
          if (screen != 0) goto LAB_ram_1040ba02;
LAB_ram_1040b98c:
          iVar23 = navdepth + -1;
          piVar29 = &nav + iVar23 * 4;
          iVar22 = frame_count_isra_0(*piVar29);
          iVar13 = ui_theme_index();
          iVar12 = (&DAT_ram_104d4434)[iVar23 * 4];
          if (((((m_psel < 0) || (m_pk != *piVar29)) || (m_ptop != (&DAT_ram_104d4438)[iVar23 * 4]))
              || (((&DAT_ram_104d443c)[iVar23 * 4] != m_pflt || (iVar13 != m_pth)))) ||
             ((g_ps != m_pps || (iVar22 != m_pn)))) {
            switch(*piVar29) {
            case 0:
              pcVar26 = &DAT_ram_10417608;
              break;
            case 1:
              pcVar26 = &DAT_ram_10417694;
              break;
            case 2:
              pcVar26 = s_Artists_ram_10417610;
              break;
            case 3:
              pcVar26 = s_Albums_ram_10417618;
              break;
            case 4:
              pcVar26 = artists + (&DAT_ram_104d443c)[iVar23 * 4] * 0x50;
              break;
            case 5:
              pcVar26 = albums + (&DAT_ram_104d443c)[iVar23 * 4] * 0x50;
              break;
            case 6:
              pcVar26 = s_Settings_ram_10417620;
              break;
            case 7:
              pcVar26 = s_Theme_ram_1041762c;
              break;
            case 8:
              pcVar26 = &DAT_ram_10417634;
              break;
            default:
              pcVar26 = &DAT_ram_104174c0;
            }
            ui_menu(g_mfb,pcVar26,iVar22,iVar12,(&DAT_ram_104d4438)[iVar23 * 4],label_of,arrow_of,
                    piVar29);
          }
          else if (m_psel != iVar12) {
            ui_menu_row(g_mfb,m_psel - m_ptop,iVar22,iVar12,m_ptop,label_of,arrow_of,piVar29);
            ui_menu_row(g_mfb,(&DAT_ram_104d4434)[iVar23 * 4] - (&DAT_ram_104d4438)[iVar23 * 4],
                        iVar22,(&DAT_ram_104d4434)[iVar23 * 4],(&DAT_ram_104d4438)[iVar23 * 4],
                        label_of,arrow_of,piVar29);
            ui_menu_scrollbar(g_mfb,iVar22,(&DAT_ram_104d4438)[iVar23 * 4]);
          }
          __dest = (void *)(**(code **)(_of_svc_ptr + 0x10))();
          memcpy(__dest,g_mfb,0x96000);
          (**(code **)(_of_svc_ptr + 0x14))();
          m_pk = (&nav)[iVar23 * 4];
          m_ptop = (&DAT_ram_104d4438)[iVar23 * 4];
          m_psel = (&DAT_ram_104d4434)[iVar23 * 4];
          m_pflt = (&DAT_ram_104d443c)[iVar23 * 4];
          m_pps = g_ps;
          uVar28 = 0;
          m_pn = iVar22;
          m_pth = iVar13;
LAB_ram_1040ba80:
          usleep(5000);
        }
      }
      else {
        if ((DAT_ram_1254be1c & 0x4000) == 0) {
          if (P != 0) goto joined_r0x1040be7a;
          goto LAB_ram_1040b7f6;
        }
        if (P != 0) goto LAB_ram_1040b7d8;
        uVar15 = uVar28;
        if (screen == 0) goto LAB_ram_1040b7fa;
LAB_ram_1040bc40:
        if (screen != 1) goto LAB_ram_1040bbe4;
        if ((DAT_ram_1254be1c & 0x20) == 0) {
          if (((DAT_ram_1254be1c & 8) != 0) && (iStack_a4 = -2, qlen != 0)) {
            qpos = qpos + 1;
            if (qlen != 0) {
              qpos = (int)qpos % qlen;
            }
            player_load_current();
          }
          if (((DAT_ram_1254be1c & 4) != 0) && (iStack_a4 = -2, qlen != 0)) {
            qpos = (qpos - 1) + qlen;
            if (qlen != 0) {
              qpos = (int)qpos % qlen;
            }
            player_load_current();
          }
          uVar15 = qpos;
          if ((DAT_ram_1254be1c & 1) != 0) {
            g_vol = g_vol + 5;
            if (100 < (int)g_vol) {
              g_vol = 100;
            }
            g_vol_until = _DAT_ram_c0de0006 + 0x5dc;
          }
          if ((DAT_ram_1254be1c & 2) != 0) {
            g_vol = g_vol - 5 & (int)~(g_vol - 5) >> 0x1f;
            g_vol_until = _DAT_ram_c0de0006 + 0x5dc;
          }
          if (qpos != uStack_88) {
            uStack_84 = _DAT_ram_c0de0006;
          }
          if ((DAT_ram_104d3c20 == (FILE *)0x0) || (DAT_ram_104d3c28 <= DAT_ram_104d3c24)) {
            uVar27 = 0;
          }
          else {
            uStack_84 = _DAT_ram_c0de0006;
            uVar27 = 1;
          }
          iVar13 = _DAT_ram_c0de0006 - uStack_84;
          iVar22 = 0;
          if (P != 0) {
            UVar31 = __udivdi3(CONCAT44(DAT_ram_104d3c14,DAT_ram_104d3c10),48000);
            iVar22 = (int)UVar31;
          }
          uVar4 = _DAT_ram_c0de0006;
          uVar14 = g_vol_until;
          uVar21 = 0;
          if ((_DAT_ram_c0de0006 < g_vol_until) || (uVar21 = g_vol_prev, g_vol_prev != 0)) {
            render_np(iVar13,_DAT_ram_c0de0006,0,0,uVar21,g_vol_until,3);
            g_vol_prev = (uint)(uVar4 < uVar14);
            usleep(33000);
            uStack_88 = uVar15;
            iStack_a4 = -2;
          }
          else if ((P == 0) || (uVar14 = np_scrolling_part_0(0), ((uVar27 ^ 1) & uVar14) == 0)) {
            if (iStack_a4 == iVar22) {
              usleep(8000);
              uStack_88 = uVar15;
            }
            else {
              render_np(iVar13);
              usleep(8000);
              uStack_88 = uVar15;
              iStack_a4 = iVar22;
            }
          }
          else {
            render_np(iVar13);
            usleep(40000);
            uStack_88 = uVar15;
          }
        }
        else {
          screen = 0;
          usleep(8000);
          uVar28 = 1;
        }
      }
      goto LAB_ram_1040b600;
    }
LAB_ram_1040bbe4:
    (**(code **)(_of_svc_ptr + 0x10))();
    if ((cur_game != (undefined *)0x0) && (iVar22 = (**(code **)(cur_game + 8))(), iVar22 != 0)) {
      screen = 0;
      uVar28 = 1;
    }
    (**(code **)(_of_svc_ptr + 0x14))();
    usleep(16000);
  } while( true );
}


// ===== ui_boot @ 104052c0 =====

void ui_boot(void *param_1,uint param_2)

{
  undefined2 *puVar1;
  ushort *puVar2;
  void *pvVar3;
  uint uVar4;
  ushort uVar5;
  int iVar6;
  byte *pbVar7;
  int iVar8;
  uint uVar9;
  undefined2 *puVar10;
  int iVar11;
  ushort *puVar12;
  undefined2 *puVar13;
  ushort *puVar14;
  byte *pbVar15;
  
  gp = &__global_pointer_;
  pvVar3 = memset(param_1,0,0x96000);
  puVar14 = (ushort *)((int)pvVar3 + 0x296dc);
  pbVar15 = &APPLE_COV;
  do {
    pbVar7 = pbVar15;
    puVar2 = puVar14 + -0x5c;
    do {
      while( true ) {
        puVar12 = puVar2;
        uVar9 = (uint)*pbVar7;
        uVar5 = 0xffff;
        pbVar7 = pbVar7 + 1;
        if (uVar9 < 8) break;
        if (uVar9 < 0xf8) {
          uVar4 = (uVar9 * 0x1f) / 0xff;
          uVar5 = (ushort)uVar4 | (ushort)((uVar9 * 0x3f) / 0xff << 5) | (ushort)(uVar4 << 0xb);
        }
        *puVar12 = uVar5;
        puVar12[1] = uVar5;
        puVar12[0x280] = uVar5;
        puVar12[0x281] = uVar5;
        puVar2 = puVar12 + 2;
        if (puVar12 + 2 == puVar14) goto LAB_ram_1040535a;
      }
      puVar2 = puVar12 + 2;
    } while (puVar12 + 2 != puVar14);
LAB_ram_1040535a:
    puVar14 = puVar12 + 0x502;
    pbVar15 = pbVar15 + 0x2e;
    if (puVar14 == (ushort *)((int)pvVar3 + 0x48adc)) {
      puVar10 = (undefined2 *)((int)pvVar3 + 0x6d954);
      do {
        puVar1 = puVar10 + -0xd4;
        do {
          puVar13 = puVar1;
          *puVar13 = 0x4208;
          puVar1 = puVar13 + 1;
        } while (puVar13 + 1 != puVar10);
        puVar10 = puVar13 + 0x281;
      } while (puVar10 != (undefined2 *)((int)pvVar3 + 0x72954));
      puVar10 = (undefined2 *)((int)pvVar3 + 0x6e350);
      do {
        puVar1 = puVar10 + -0xd0;
        do {
          puVar13 = puVar1;
          *puVar13 = 0x18e3;
          puVar1 = puVar13 + 1;
        } while (puVar13 + 1 != puVar10);
        puVar10 = puVar13 + 0x281;
      } while (puVar10 != (undefined2 *)((int)pvVar3 + 0x71f50));
      uVar9 = 100;
      if ((int)param_2 < 0x65) {
        uVar9 = (int)~param_2 >> 0x1f & param_2;
      }
      if (99 < (int)(uVar9 * 0xd0)) {
        iVar6 = 0x6e000;
        do {
          iVar8 = (int)pvVar3 + iVar6;
          iVar11 = 0xd8;
          do {
            *(undefined2 *)(iVar8 + 0x1b0) = 0xdefb;
            iVar11 = iVar11 + 1;
            iVar8 = iVar8 + 2;
          } while (iVar11 < (int)((uVar9 * 0xd0) / 100 + 0xd8));
          iVar6 = iVar6 + 0x500;
        } while (iVar6 != 0x71c00);
      }
      return;
    }
  } while( true );
}


// ===== ui_menu @ 10404740 =====

void ui_menu(ushort *param_1,undefined4 param_2,int param_3,undefined4 param_4,int param_5,
            undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  ushort uVar1;
  int iVar2;
  int iVar3;
  ushort *puVar4;
  
  gp = &__global_pointer_;
  uVar1 = *(ushort *)(T + 4);
  puVar4 = param_1;
  if ((uVar1 & 0xff) == (uint)(uVar1 >> 8)) {
    memset(param_1,uVar1 & 0xff,0x96000);
  }
  else {
    do {
      *puVar4 = uVar1;
      puVar4 = puVar4 + 1;
    } while (puVar4 != param_1 + 0x4b000);
  }
  iVar2 = 0;
  do {
    if (param_3 <= param_5 + iVar2) break;
    iVar3 = iVar2 + 1;
    ui_menu_row(param_1,iVar2,param_3,param_4,param_5,param_6,param_7,param_8);
    iVar2 = iVar3;
  } while (iVar3 != 7);
  if (7 < param_3) {
    ui_menu_scrollbar_part_0(param_1,param_3,param_5);
  }
  ui_status_bar(param_1,param_2,100);
  return;
}


// ===== ui_text @ 10403940 =====

int ui_text(undefined4 param_1,int param_2,undefined4 param_3,byte *param_4,undefined4 param_5)

{
  byte bVar1;
  uint uVar2;
  
  gp = &__global_pointer_;
  bVar1 = *param_4;
  while (bVar1 != 0) {
    ui_char(param_1,param_2,param_3,bVar1,param_5);
    bVar1 = *param_4;
    uVar2 = 0xf;
    param_4 = param_4 + 1;
    if ((bVar1 - 0x20 & 0xff) < 0x5f) {
      uVar2 = (uint)(byte)(&FP_FONT)[(bVar1 - 0x20) * 0x450];
    }
    param_2 = param_2 + uVar2;
    bVar1 = *param_4;
  }
  return param_2;
}


// ===== ui_text_w @ 10403a00 =====

int ui_text_w(byte *param_1)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  
  gp = &__global_pointer_;
  uVar3 = (uint)*param_1;
  if (uVar3 == 0) {
    return 0;
  }
  iVar1 = 0;
  do {
    param_1 = param_1 + 1;
    uVar2 = 0xf;
    if ((uVar3 - 0x20 & 0xff) < 0x5f) {
      uVar2 = (uint)(byte)(&FP_FONT)[(uVar3 - 0x20) * 0x450];
    }
    uVar3 = (uint)*param_1;
    iVar1 = iVar1 + uVar2;
  } while (uVar3 != 0);
  return iVar1;
}


// ===== ui_theme_name @ 10403500 =====

undefined4 ui_theme_name(void)

{
  gp = &__global_pointer_;
  return *(undefined4 *)T;
}


// ===== ui_menu_row @ 104043c0 =====

void ui_menu_row(int param_1,int param_2,int param_3,int param_4,int param_5,code *param_6,
                code *param_7,undefined4 param_8)

{
  undefined2 uVar1;
  undefined2 uVar2;
  undefined2 *puVar3;
  int iVar4;
  uint uVar5;
  undefined2 uVar6;
  undefined *puVar7;
  int iVar8;
  undefined2 *puVar9;
  uint uVar10;
  undefined2 *puVar11;
  
  puVar7 = T;
  gp = &__global_pointer_;
  iVar4 = param_2 * 0x11800;
  uVar1 = *(undefined2 *)(T + 4);
  uVar5 = -(uint)(param_3 < 8) & 10;
  param_5 = param_2 + param_5;
  puVar11 = (undefined2 *)(param_1 + 0xd700 + iVar4);
  param_2 = param_2 * 0x38;
  uVar10 = param_2 + 0x2a;
  puVar9 = puVar11;
  do {
    if (uVar10 < 0x1e0) {
      puVar3 = puVar9 + -0x280;
      do {
        *puVar3 = uVar1;
        puVar3 = puVar3 + 1;
      } while (puVar3 != puVar9);
    }
    uVar10 = uVar10 + 1;
    puVar9 = puVar9 + 0x280;
  } while (uVar10 != param_2 + 0x62U);
  if (param_3 <= param_5 || param_5 < 0) {
    return;
  }
  if (param_5 == param_4) {
    uVar1 = *(undefined2 *)(puVar7 + 0xe);
    iVar8 = 0;
    uVar2 = *(undefined2 *)(puVar7 + 0x10);
    do {
      while (0x1df < (uint)(param_2 + 0x2a + iVar8)) {
        iVar8 = iVar8 + 1;
        puVar11 = puVar11 + 0x280;
        if (iVar8 == 0x38) goto LAB_ram_104045d4;
      }
      uVar6 = lerp565(uVar1,uVar2,iVar8,0x37);
      puVar9 = puVar11 + -0x280;
      do {
        *puVar9 = uVar6;
        puVar9 = puVar9 + 1;
      } while (puVar9 != puVar11);
      iVar8 = iVar8 + 1;
      puVar11 = puVar11 + 0x280;
    } while (iVar8 != 0x38);
LAB_ram_104045d4:
    uVar1 = *(undefined2 *)(puVar7 + 0x12);
    puVar9 = (undefined2 *)(param_1 + 0xe100 + iVar4);
    iVar8 = 2;
    while( true ) {
      if ((uint)((param_2 + 0x2e) - iVar8) < 0x1e0) {
        puVar11 = puVar9 + -0x280;
        do {
          *puVar11 = uVar1;
          puVar11 = puVar11 + 1;
        } while (puVar9 != puVar11);
      }
      if (iVar8 == 1) break;
      puVar9 = puVar9 + 0x280;
      iVar8 = 1;
    }
    uVar1 = *(undefined2 *)(puVar7 + 0x14);
    puVar9 = (undefined2 *)(param_1 + 0x1e500 + iVar4);
    iVar4 = 2;
    while( true ) {
      if ((param_2 + 0x62U) - iVar4 < 0x1e0) {
        puVar11 = puVar9 + -0x280;
        do {
          *puVar11 = uVar1;
          puVar11 = puVar11 + 1;
        } while (puVar9 != puVar11);
      }
      if (iVar4 == 1) break;
      puVar9 = puVar9 + 0x280;
      iVar4 = 1;
    }
    uVar1 = *(undefined2 *)(puVar7 + 0x16);
  }
  else {
    uVar1 = *(undefined2 *)(puVar7 + 6);
  }
  if (param_7 == (code *)0x0) {
    puVar7 = (undefined *)(*param_6)(param_5,param_8);
  }
  else {
    iVar4 = (*param_7)();
    puVar7 = (undefined *)(*param_6)(param_5,param_8);
    if (iVar4 != 0) {
      if (puVar7 == (undefined *)0x0) {
        puVar7 = &DAT_ram_104174c0;
      }
      ui_text_clip(param_1,0x12,param_2 + 0x35,uVar5 + 0x238,puVar7,uVar1);
      if (param_5 == param_4) {
        uVar1 = *(undefined2 *)(T + 0x16);
      }
      else {
        uVar1 = *(undefined2 *)(T + 0x18);
      }
      ui_char(param_1,uVar5 + 0x24a,param_2 + 0x35,0x3e,uVar1);
      return;
    }
  }
  if (puVar7 == (undefined *)0x0) {
    puVar7 = &DAT_ram_104174c0;
  }
  ui_text_clip(param_1,0x12,param_2 + 0x35,uVar5 + 0x24c,puVar7,uVar1);
  return;
}


// ===== ui_menu_scrollbar @ 10404700 =====

void ui_menu_scrollbar(undefined4 param_1,int param_2)

{
  gp = &__global_pointer_;
  if (param_2 < 8) {
    return;
  }
  ui_menu_scrollbar_part_0();
  return;
}


