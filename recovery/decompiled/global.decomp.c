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

/* WARNING: Removing unreachable block (ram,0x1040b42a) */
/* WARNING: Removing unreachable block (ram,0x1040b43c) */
/* WARNING: Removing unreachable block (ram,0x1040b444) */
/* WARNING: Removing unreachable block (ram,0x1040b4c0) */
/* WARNING: Removing unreachable block (ram,0x1040b526) */
/* WARNING: Removing unreachable block (ram,0x1040b600) */
/* WARNING: Removing unreachable block (ram,0x1040bbdc) */
/* WARNING: Removing unreachable block (ram,0x1040b638) */
/* WARNING: Removing unreachable block (ram,0x1040bdce) */
/* WARNING: Removing unreachable block (ram,0x1040bf4a) */
/* WARNING: Removing unreachable block (ram,0x1040bf5c) */
/* WARNING: Removing unreachable block (ram,0x1040b644) */
/* WARNING: Removing unreachable block (ram,0x1040b64c) */
/* WARNING: Removing unreachable block (ram,0x1040b654) */
/* WARNING: Removing unreachable block (ram,0x1040b65a) */
/* WARNING: Removing unreachable block (ram,0x1040b666) */
/* WARNING: Removing unreachable block (ram,0x1040b672) */
/* WARNING: Removing unreachable block (ram,0x1040b676) */
/* WARNING: Removing unreachable block (ram,0x1040b69e) */
/* WARNING: Removing unreachable block (ram,0x1040b6aa) */
/* WARNING: Removing unreachable block (ram,0x1040bdd8) */
/* WARNING: Removing unreachable block (ram,0x1040bdee) */
/* WARNING: Removing unreachable block (ram,0x1040bdf6) */
/* WARNING: Removing unreachable block (ram,0x1040bdfc) */
/* WARNING: Removing unreachable block (ram,0x1040be00) */
/* WARNING: Removing unreachable block (ram,0x1040b6b0) */
/* WARNING: Removing unreachable block (ram,0x1040b6ce) */
/* WARNING: Removing unreachable block (ram,0x1040b6dc) */
/* WARNING: Removing unreachable block (ram,0x1040b6f6) */
/* WARNING: Removing unreachable block (ram,0x1040b700) */
/* WARNING: Removing unreachable block (ram,0x1040b71a) */
/* WARNING: Removing unreachable block (ram,0x1040bee6) */
/* WARNING: Removing unreachable block (ram,0x1040beea) */
/* WARNING: Removing unreachable block (ram,0x1040bf00) */
/* WARNING: Removing unreachable block (ram,0x1040bf12) */
/* WARNING: Removing unreachable block (ram,0x1040bf18) */
/* WARNING: Removing unreachable block (ram,0x1040bf1a) */
/* WARNING: Removing unreachable block (ram,0x1040bf24) */
/* WARNING: Removing unreachable block (ram,0x1040c0e8) */
/* WARNING: Removing unreachable block (ram,0x1040b73e) */
/* WARNING: Removing unreachable block (ram,0x1040be0c) */
/* WARNING: Removing unreachable block (ram,0x1040be14) */
/* WARNING: Removing unreachable block (ram,0x1040be40) */
/* WARNING: Removing unreachable block (ram,0x1040b768) */
/* WARNING: Removing unreachable block (ram,0x1040b76e) */
/* WARNING: Removing unreachable block (ram,0x1040b780) */
/* WARNING: Removing unreachable block (ram,0x1040b784) */
/* WARNING: Removing unreachable block (ram,0x1040bdd2) */
/* WARNING: Removing unreachable block (ram,0x1040b78c) */
/* WARNING: Removing unreachable block (ram,0x1040b7a0) */
/* WARNING: Removing unreachable block (ram,0x1040b7ac) */
/* WARNING: Removing unreachable block (ram,0x1040b7b2) */
/* WARNING: Removing unreachable block (ram,0x1040bc14) */
/* WARNING: Removing unreachable block (ram,0x1040be72) */
/* WARNING: Removing unreachable block (ram,0x1040be76) */
/* WARNING: Removing unreachable block (ram,0x1040bc18) */
/* WARNING: Removing unreachable block (ram,0x1040bc1c) */
/* WARNING: Removing unreachable block (ram,0x1040bc20) */
/* WARNING: Removing unreachable block (ram,0x1040b7c4) */
/* WARNING: Removing unreachable block (ram,0x1040b7c6) */
/* WARNING: Removing unreachable block (ram,0x1040b7d8) */
/* WARNING: Removing unreachable block (ram,0x1040b7de) */
/* WARNING: Removing unreachable block (ram,0x1040be7e) */
/* WARNING: Removing unreachable block (ram,0x1040bfb8) */
/* WARNING: Removing unreachable block (ram,0x1040bfc0) */
/* WARNING: Removing unreachable block (ram,0x1040be86) */
/* WARNING: Removing unreachable block (ram,0x1040be8c) */
/* WARNING: Removing unreachable block (ram,0x1040be90) */
/* WARNING: Removing unreachable block (ram,0x1040be9c) */
/* WARNING: Removing unreachable block (ram,0x1040beac) */
/* WARNING: Removing unreachable block (ram,0x1040b7ea) */
/* WARNING: Removing unreachable block (ram,0x1040bec0) */
/* WARNING: Removing unreachable block (ram,0x1040bec6) */
/* WARNING: Removing unreachable block (ram,0x1040bece) */
/* WARNING: Removing unreachable block (ram,0x1040bed2) */
/* WARNING: Removing unreachable block (ram,0x1040beda) */
/* WARNING: Removing unreachable block (ram,0x1040b7f2) */
/* WARNING: Removing unreachable block (ram,0x1040b7f6) */
/* WARNING: Removing unreachable block (ram,0x1040bc40) */
/* WARNING: Removing unreachable block (ram,0x1040bc46) */
/* WARNING: Removing unreachable block (ram,0x1040c02c) */
/* WARNING: Removing unreachable block (ram,0x1040bc52) */
/* WARNING: Removing unreachable block (ram,0x1040bffe) */
/* WARNING: Removing unreachable block (ram,0x1040c00a) */
/* WARNING: Removing unreachable block (ram,0x1040c010) */
/* WARNING: Removing unreachable block (ram,0x1040c014) */
/* WARNING: Removing unreachable block (ram,0x1040bc5a) */
/* WARNING: Removing unreachable block (ram,0x1040bfd8) */
/* WARNING: Removing unreachable block (ram,0x1040bfe4) */
/* WARNING: Removing unreachable block (ram,0x1040bfec) */
/* WARNING: Removing unreachable block (ram,0x1040bff0) */
/* WARNING: Removing unreachable block (ram,0x1040bc62) */
/* WARNING: Removing unreachable block (ram,0x1040bc68) */
/* WARNING: Removing unreachable block (ram,0x1040bc76) */
/* WARNING: Removing unreachable block (ram,0x1040bc78) */
/* WARNING: Removing unreachable block (ram,0x1040bca0) */
/* WARNING: Removing unreachable block (ram,0x1040bca4) */
/* WARNING: Removing unreachable block (ram,0x1040bcd6) */
/* WARNING: Removing unreachable block (ram,0x1040bce0) */
/* WARNING: Removing unreachable block (ram,0x1040bcfa) */
/* WARNING: Removing unreachable block (ram,0x1040bd00) */
/* WARNING: Removing unreachable block (ram,0x1040bd0c) */
/* WARNING: Removing unreachable block (ram,0x1040be56) */
/* WARNING: Removing unreachable block (ram,0x1040bd0e) */
/* WARNING: Removing unreachable block (ram,0x1040bd34) */
/* WARNING: Removing unreachable block (ram,0x1040bd4e) */
/* WARNING: Removing unreachable block (ram,0x1040bd6e) */
/* WARNING: Removing unreachable block (ram,0x1040bd76) */
/* WARNING: Removing unreachable block (ram,0x1040bd7a) */
/* WARNING: Removing unreachable block (ram,0x1040c1bc) */
/* WARNING: Removing unreachable block (ram,0x1040bd8c) */
/* WARNING: Removing unreachable block (ram,0x1040c118) */
/* WARNING: Removing unreachable block (ram,0x1040bd92) */
/* WARNING: Removing unreachable block (ram,0x1040bf66) */
/* WARNING: Removing unreachable block (ram,0x1040b7fa) */
/* WARNING: Removing unreachable block (ram,0x1040b824) */
/* WARNING: Removing unreachable block (ram,0x1040bba4) */
/* WARNING: Removing unreachable block (ram,0x1040bba6) */
/* WARNING: Removing unreachable block (ram,0x1040bbb0) */
/* WARNING: Removing unreachable block (ram,0x1040bbb4) */
/* WARNING: Removing unreachable block (ram,0x1040bf28) */
/* WARNING: Removing unreachable block (ram,0x1040be4a) */
/* WARNING: Removing unreachable block (ram,0x1040b830) */
/* WARNING: Removing unreachable block (ram,0x1040bf92) */
/* WARNING: Removing unreachable block (ram,0x1040b83c) */
/* WARNING: Removing unreachable block (ram,0x1040b840) */
/* WARNING: Removing unreachable block (ram,0x1040b84a) */
/* WARNING: Removing unreachable block (ram,0x1040c022) */
/* WARNING: Removing unreachable block (ram,0x1040c02a) */
/* WARNING: Removing unreachable block (ram,0x1040b852) */
/* WARNING: Removing unreachable block (ram,0x1040b864) */
/* WARNING: Removing unreachable block (ram,0x1040b868) */
/* WARNING: Removing unreachable block (ram,0x1040c042) */
/* WARNING: Removing unreachable block (ram,0x1040c046) */
/* WARNING: Removing unreachable block (ram,0x1040bf96) */
/* WARNING: Removing unreachable block (ram,0x1040bf9e) */
/* WARNING: Removing unreachable block (ram,0x1040bfa4) */
/* WARNING: Removing unreachable block (ram,0x1040bf30) */
/* WARNING: Removing unreachable block (ram,0x1040bbbc) */
/* WARNING: Removing unreachable block (ram,0x1040bfa6) */
/* WARNING: Removing unreachable block (ram,0x1040bfb6) */
/* WARNING: Removing unreachable block (ram,0x1040bf36) */
/* WARNING: Removing unreachable block (ram,0x1040bbd2) */
/* WARNING: Removing unreachable block (ram,0x1040bbd6) */
/* WARNING: Removing unreachable block (ram,0x1040bf3a) */
/* WARNING: Removing unreachable block (ram,0x1040bfc8) */
/* WARNING: Removing unreachable block (ram,0x1040bf3e) */
/* WARNING: Removing unreachable block (ram,0x1040be4e) */
/* WARNING: Removing unreachable block (ram,0x1040b880) */
/* WARNING: Removing unreachable block (ram,0x1040b88c) */
/* WARNING: Removing unreachable block (ram,0x1040b890) */
/* WARNING: Removing unreachable block (ram,0x1040b898) */
/* WARNING: Removing unreachable block (ram,0x1040b8a2) */
/* WARNING: Removing unreachable block (ram,0x1040b8a4) */
/* WARNING: Removing unreachable block (ram,0x1040bdac) */
/* WARNING: Removing unreachable block (ram,0x1040bdb6) */
/* WARNING: Removing unreachable block (ram,0x1040bdc0) */
/* WARNING: Removing unreachable block (ram,0x1040bdc8) */
/* WARNING: Removing unreachable block (ram,0x1040bdcc) */
/* WARNING: Removing unreachable block (ram,0x1040b8ac) */
/* WARNING: Removing unreachable block (ram,0x1040b8ba) */
/* WARNING: Removing unreachable block (ram,0x1040b92e) */
/* WARNING: Removing unreachable block (ram,0x1040b9d2) */
/* WARNING: Removing unreachable block (ram,0x1040ba10) */
/* WARNING: Removing unreachable block (ram,0x1040ba2e) */
/* WARNING: Removing unreachable block (ram,0x1040ba34) */
/* WARNING: Removing unreachable block (ram,0x1040ba4a) */
/* WARNING: Removing unreachable block (ram,0x1040ba4e) */
/* WARNING: Removing unreachable block (ram,0x1040ba8e) */
/* WARNING: Removing unreachable block (ram,0x1040b9d8) */
/* WARNING: Removing unreachable block (ram,0x1040ba94) */
/* WARNING: Removing unreachable block (ram,0x1040c18a) */
/* WARNING: Removing unreachable block (ram,0x1040c13a) */
/* WARNING: Removing unreachable block (ram,0x1040c142) */
/* WARNING: Removing unreachable block (ram,0x1040c158) */
/* WARNING: Removing unreachable block (ram,0x1040c168) */
/* WARNING: Removing unreachable block (ram,0x1040c170) */
/* WARNING: Removing unreachable block (ram,0x1040c1d4) */
/* WARNING: Removing unreachable block (ram,0x1040c1e0) */
/* WARNING: Removing unreachable block (ram,0x1040c14c) */
/* WARNING: Removing unreachable block (ram,0x1040c154) */
/* WARNING: Removing unreachable block (ram,0x1040c17a) */
/* WARNING: Removing unreachable block (ram,0x1040c192) */
/* WARNING: Removing unreachable block (ram,0x1040c1e6) */
/* WARNING: Removing unreachable block (ram,0x1040c1ea) */
/* WARNING: Removing unreachable block (ram,0x1040c1a8) */
/* WARNING: Removing unreachable block (ram,0x1040c1b2) */
/* WARNING: Removing unreachable block (ram,0x1040c1b6) */
/* WARNING: Removing unreachable block (ram,0x1040c182) */
/* WARNING: Removing unreachable block (ram,0x1040ba14) */
/* WARNING: Removing unreachable block (ram,0x1040b9e6) */
/* WARNING: Removing unreachable block (ram,0x1040b9f0) */
/* WARNING: Removing unreachable block (ram,0x1040b9f2) */
/* WARNING: Removing unreachable block (ram,0x1040ba26) */
/* WARNING: Removing unreachable block (ram,0x1040ba28) */
/* WARNING: Removing unreachable block (ram,0x1040b8c6) */
/* WARNING: Removing unreachable block (ram,0x1040b8ce) */
/* WARNING: Removing unreachable block (ram,0x1040b900) */
/* WARNING: Removing unreachable block (ram,0x1040b90e) */
/* WARNING: Removing unreachable block (ram,0x1040c12a) */
/* WARNING: Removing unreachable block (ram,0x1040b916) */
/* WARNING: Removing unreachable block (ram,0x1040b91a) */
/* WARNING: Removing unreachable block (ram,0x1040b91e) */
/* WARNING: Removing unreachable block (ram,0x1040b926) */
/* WARNING: Removing unreachable block (ram,0x1040b942) */
/* WARNING: Removing unreachable block (ram,0x1040b952) */
/* WARNING: Removing unreachable block (ram,0x1040b95c) */
/* WARNING: Removing unreachable block (ram,0x1040b980) */
/* WARNING: Removing unreachable block (ram,0x1040ba00) */
/* WARNING: Removing unreachable block (ram,0x1040ba02) */
/* WARNING: Removing unreachable block (ram,0x1040b98c) */
/* WARNING: Removing unreachable block (ram,0x1040b9ba) */
/* WARNING: Removing unreachable block (ram,0x1040c048) */
/* WARNING: Removing unreachable block (ram,0x1040c050) */
/* WARNING: Removing unreachable block (ram,0x1040c05c) */
/* WARNING: Removing unreachable block (ram,0x1040c064) */
/* WARNING: Removing unreachable block (ram,0x1040c074) */
/* WARNING: Removing unreachable block (ram,0x1040b9c2) */
/* WARNING: Removing unreachable block (ram,0x1040c130) */
/* WARNING: Removing unreachable block (ram,0x1040b9c8) */
/* WARNING: Removing unreachable block (ram,0x1040bb5e) */
/* WARNING: Removing unreachable block (ram,0x1040bb4a) */
/* WARNING: Removing unreachable block (ram,0x1040bb54) */
/* WARNING: Removing unreachable block (ram,0x1040bb68) */
/* WARNING: Removing unreachable block (ram,0x1040bb7c) */
/* WARNING: Removing unreachable block (ram,0x1040bb90) */
/* WARNING: Removing unreachable block (ram,0x1040bb9a) */
/* WARNING: Removing unreachable block (ram,0x1040baa0) */
/* WARNING: Removing unreachable block (ram,0x1040bb40) */
/* WARNING: Removing unreachable block (ram,0x1040bac0) */
/* WARNING: Removing unreachable block (ram,0x1040c080) */
/* WARNING: Removing unreachable block (ram,0x1040c084) */
/* WARNING: Removing unreachable block (ram,0x1040bae0) */
/* WARNING: Removing unreachable block (ram,0x1040ba80) */
/* WARNING: Removing unreachable block (ram,0x1040bbe4) */
/* WARNING: Removing unreachable block (ram,0x1040bbf2) */
/* WARNING: Removing unreachable block (ram,0x1040bbf8) */
/* WARNING: Removing unreachable block (ram,0x1040bbfe) */
/* WARNING: Recovered jumptable eliminated as dead code */

void main(void)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  FILE *__stream;
  size_t sVar4;
  char *pcVar5;
  char *pcVar6;
  int iVar7;
  char cVar8;
  int iVar9;
  char *__s;
  char *apcStack_58 [5];
  char *pcStack_44;
  
  (**(code **)(_of_svc_ptr + 0xc))();
  apcStack_58[0] = (char *)0x1e00280;
  apcStack_58[1] = (char *)0x30000;
  if (0x5e < *(uint *)(_of_svc_ptr + 8)) {
    if ((*(code **)(_of_svc_ptr + 0x184) != (code *)0x0) &&
       (iVar2 = (**(code **)(_of_svc_ptr + 0x184))(apcStack_58), iVar2 == 0)) goto LAB_ram_1040b14e;
  }
  (**(code **)(_of_svc_ptr + 0x38))(3);
LAB_ram_1040b14e:
  (**(code **)(_of_svc_ptr + 0x34))(1);
  uVar3 = (**(code **)(_of_svc_ptr + 0x10))();
  ui_boot(uVar3,0);
  (**(code **)(_of_svc_ptr + 0x14))();
  (**(code **)(_of_svc_ptr + 0xac))();
  g_ring = (**(code **)(_of_svc_ptr + 0xb4))();
  (**(code **)(_of_svc_ptr + 0xf8))(48000);
  ecall();
  __stream = (FILE *)open_any(s_playlist_tsv_ram_10417650,s__music_ram_10417454,
                              s_iso9660_ram_1041763c,1,0,0,3,0xc0de000e);
  if (__stream != (FILE *)0x0) {
    sVar4 = fread_unlocked(&plbuf,1,0x27fff,__stream);
    __s = &plbuf;
    fclose(__stream);
    (&plbuf)[sVar4] = 0;
    if (plbuf != '\0') {
      while (iVar2 = ntracks, ntracks < 0x200) {
        pcVar5 = strchr(__s,10);
        if (pcVar5 != (char *)0x0) {
          *pcVar5 = '\0';
        }
        pcVar6 = strchr(__s,0xd);
        if (pcVar6 != (char *)0x0) {
          *pcVar6 = '\0';
        }
        cVar8 = *__s;
        if (cVar8 != '\0') {
          iVar9 = 1;
          pcVar6 = __s;
          do {
            pcVar6 = pcVar6 + 1;
            if (cVar8 == '\t') goto LAB_ram_1040b290;
            cVar8 = *pcVar6;
            if (cVar8 == '\0') break;
            while (pcVar6 = pcVar6 + 1, cVar8 == '\t') {
LAB_ram_1040b290:
              cVar8 = *pcVar6;
              pcVar6[-1] = '\0';
              apcStack_58[iVar9] = pcVar6;
              iVar9 = iVar9 + 1;
              if (cVar8 == '\0') goto LAB_ram_1040b4f4;
              if (iVar9 == 6) goto LAB_ram_1040b2aa;
            }
            cVar8 = *pcVar6;
          } while (cVar8 != '\0');
LAB_ram_1040b4f4:
          if (3 < iVar9) {
LAB_ram_1040b2aa:
            iVar1 = iVar2 * 0x138;
            ntracks = iVar2 + 1;
            snprintf(tracks + iVar1,0x40,&DAT_ram_10417450,__s);
            snprintf(tracks + iVar1 + 0x40,0x50,&DAT_ram_10417450,apcStack_58[1]);
            snprintf(tracks + iVar1 + 0x90,0x50,&DAT_ram_10417450,apcStack_58[2]);
            snprintf(tracks + iVar1 + 0xe0,0x50,&DAT_ram_10417450,apcStack_58[3]);
            if (iVar9 == 4) {
              *(undefined4 *)(tracks + iVar1 + 0x130) = 0;
LAB_ram_1040b320:
              iVar9 = 0x100;
            }
            else {
              iVar7 = atoi(apcStack_58[4]);
              *(int *)(tracks + iVar1 + 0x130) = iVar7;
              if (iVar9 != 6) goto LAB_ram_1040b320;
              iVar9 = atoi(pcStack_44);
            }
            *(int *)(tracks + iVar2 * 0x138 + 0x134) = iVar9;
            add_unique(artists,&nartists,tracks + iVar1 + 0x90);
            add_unique(albums,&nalbums,tracks + iVar1 + 0xe0);
          }
        }
        if ((pcVar5 == (char *)0x0) || (__s = pcVar5 + 1, pcVar5[1] == '\0')) break;
      }
    }
    qsort(artists,nartists,0x50,cmpstr);
    qsort(albums,nalbums,0x50,cmpstr);
  }
  ecall();
  srand(1);
  ecall();
  do {
    ecall();
    uVar3 = (**(code **)(_of_svc_ptr + 0x10))
                      (0,0,0,0,*(code **)(_of_svc_ptr + 0x10),_of_svc_ptr,3,0xc0de0006);
    ui_boot(uVar3,0);
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


