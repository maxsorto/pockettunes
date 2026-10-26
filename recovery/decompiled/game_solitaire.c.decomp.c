// ===== do_move @ 104019c0 =====

undefined4 do_move(int param_1,int param_2,int param_3)

{
  undefined1 uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  
  gp = &__global_pointer_;
  if (-1 < param_2) {
    if (param_2 < (int)(&DAT_ram_1043508c)[param_1 * 0x1b]) {
      uVar4 = param_3 - 2;
      if (uVar4 < 4) {
        if (((&DAT_ram_1043508c)[param_1 * 0x1b] + -1 == param_2) &&
           (iVar2 = (int)(char)(&piles)[param_2 + param_1 * 0x6c], uVar4 == iVar2 / 0xd)) {
          iVar2 = iVar2 + uVar4 * -0xd;
          iVar3 = (&DAT_ram_1043508c)[param_3 * 0x1b];
          if (iVar3 == 0) {
            if (iVar2 == 0) goto LAB_ram_10401b28;
          }
          else {
            if (iVar3 < 1) {
              iVar5 = -1;
            }
            else {
              iVar5 = (int)(char)(&DAT_ram_10435023)[param_3 * 0x6c + iVar3];
            }
            if (iVar2 == iVar5 % 0xd + 1) {
LAB_ram_10401b28:
              iVar2 = param_2;
              while( true ) {
                iVar5 = iVar2 + param_1 * 0x6c;
                iVar2 = iVar2 + 1;
                if (iVar3 < 0x34) {
                  uVar1 = (&piles)[iVar5];
                  (&piles + iVar3 + param_3 * 0x6c)[0x34] = 1;
                  (&DAT_ram_1043508c)[param_3 * 0x1b] = iVar3 + 1;
                  (&piles)[iVar3 + param_3 * 0x6c] = uVar1;
                }
                if ((int)(&DAT_ram_1043508c)[param_1 * 0x1b] <= iVar2) break;
                iVar3 = (&DAT_ram_1043508c)[param_3 * 0x1b];
              }
              (&DAT_ram_1043508c)[param_1 * 0x1b] = param_2;
              if ((param_2 != 0 && 5 < param_1) &&
                 (param_2 = param_1 * 0x6c + param_2, (&DAT_ram_10435023)[param_2 + 0x34] == '\0'))
              {
                (&DAT_ram_10435023)[param_2 + 0x34] = 1;
              }
              if (DAT_ram_10435164 + DAT_ram_104351d0 + DAT_ram_1043523c + DAT_ram_104352a8 == 0x34)
              {
                game_state = 1;
              }
              return 1;
            }
          }
        }
      }
      else if (5 < param_3) {
        iVar2 = (int)(char)(&piles)[param_2 + param_1 * 0x6c];
        iVar3 = (&DAT_ram_1043508c)[param_3 * 0x1b];
        if (iVar3 == 0) {
          if (iVar2 + -0xc == (iVar2 / 0xd) * 0xd) goto LAB_ram_10401b28;
        }
        else {
          if (iVar3 < 1) {
            iVar5 = -1;
          }
          else {
            iVar5 = (int)(char)(&piles)[iVar3 + -1 + param_3 * 0x6c];
          }
          if ((((&DAT_ram_10435058)[param_3 * 0x6c + iVar3 + -1] != '\0') &&
              (iVar2 % 0xd == iVar5 % 0xd + -1)) && (iVar2 - 0xdU < 0x1a != iVar5 - 0xdU < 0x1a))
          goto LAB_ram_10401b28;
        }
      }
    }
  }
  return 0;
}


// ===== fix_cur_idx @ 10401c00 =====

void fix_cur_idx(void)

{
  int iVar1;
  int iVar2;
  
  gp = &__global_pointer_;
  iVar1 = (&DAT_ram_1043508c)[cur_pile * 0x1b];
  if (cur_pile < 6) {
    if (iVar1 < 1) {
      cur_idx = 0;
      return;
    }
    cur_idx = iVar1 + -1;
  }
  else {
    if (iVar1 == 0) {
      cur_idx = 0;
      return;
    }
    if (iVar1 <= cur_idx) {
      cur_idx = iVar1 + -1;
    }
    if (0 < iVar1) {
      iVar2 = 0;
      do {
        if ((&DAT_ram_10435058)[iVar2 + cur_pile * 0x6c] != '\0') {
          if (iVar2 != iVar1) {
            if (cur_idx < iVar2) {
              cur_idx = iVar2;
              return;
            }
            return;
          }
          break;
        }
        iVar2 = iVar2 + 1;
      } while (iVar2 != iVar1);
    }
    if (cur_idx < iVar1 + -1) {
      cur_idx = iVar1 + -1;
      return;
    }
  }
  return;
}


// ===== draw_pip @ 10401cc0 =====

void draw_pip(int param_1,int param_2,int param_3,uint param_4,undefined2 param_5)

{
  int iVar1;
  undefined2 *puVar2;
  undefined2 *puVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  byte *pbVar7;
  int iVar8;
  int iVar9;
  
  gp = &__global_pointer_;
  if (param_4 < 3) {
    pbVar7 = (&CSWTCH_97)[param_4];
    uVar5 = (uint)*pbVar7;
  }
  else {
    pbVar7 = (byte *)&club_1;
    uVar5 = 0x1c;
  }
  iVar8 = param_3 * 0x280;
  iVar1 = param_3 + 2;
  iVar9 = param_3 + 0x10;
  while( true ) {
    puVar3 = (undefined2 *)(iVar8 * 2 + param_1 + param_2 * 2);
    uVar4 = 6;
    while( true ) {
      if (((int)uVar5 >> (uVar4 & 0x1f) & 1U) != 0) {
        puVar2 = puVar3;
        iVar6 = param_3;
        do {
          if (iVar6 < 0x1e0) {
            *puVar2 = param_5;
            puVar2[1] = param_5;
          }
          iVar6 = iVar6 + 1;
          puVar2 = puVar2 + 0x280;
        } while (iVar6 != iVar1);
      }
      if (uVar4 == 0) break;
      uVar4 = uVar4 - 1;
      uVar5 = (uint)*pbVar7;
      puVar3 = puVar3 + 2;
    }
    iVar1 = iVar1 + 2;
    if (iVar1 == iVar9) break;
    pbVar7 = pbVar7 + 1;
    param_3 = param_3 + 2;
    iVar8 = iVar8 + 0x500;
    uVar5 = (uint)*pbVar7;
  }
  return;
}


// ===== draw_facedown @ 10401dc0 =====

void draw_facedown(int param_1,int param_2,int param_3)

{
  undefined2 *puVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  undefined2 *puVar5;
  uint uVar6;
  
  gp = &__global_pointer_;
  ui_fill();
  ui_fill(param_1,param_2 + 2,param_3 + 2,0x38,0x4c,0x211a);
  puVar1 = (undefined2 *)((param_3 * 0x280 + param_2) * 2 + param_1 + 0x1e0c);
  uVar4 = param_3 + 0x3c + param_2;
  iVar2 = param_3 + 6;
  do {
    uVar6 = uVar4 - 0x30;
    puVar5 = puVar1;
LAB_ram_10401e80:
    do {
      uVar3 = uVar6 + 1;
      if ((uVar6 & 3) == 0) {
        if (iVar2 < 0x1e0) {
          *puVar5 = 0x429f;
          if (uVar6 + 1 == uVar4) break;
          uVar6 = uVar6 + 2;
          puVar5 = puVar5 + 2;
          if (uVar6 == uVar4) break;
          goto LAB_ram_10401e80;
        }
        uVar6 = uVar6 + 2;
        if ((uVar4 == uVar3) || (uVar6 == uVar4)) break;
        puVar5 = puVar5 + 2;
      }
      uVar6 = uVar6 + 1;
      puVar5 = puVar5 + 1;
    } while (uVar6 != uVar4);
    iVar2 = iVar2 + 1;
    uVar4 = uVar4 + 1;
    puVar1 = puVar1 + 0x280;
    if (iVar2 == param_3 + 0x4a) {
      return;
    }
  } while( true );
}


// ===== draw_outline @ 10401f00 =====

void draw_outline(undefined4 param_1,int param_2,int param_3,int param_4,int param_5,
                 undefined4 param_6)

{
  gp = &__global_pointer_;
  ui_fill(param_1,param_2 + -4,param_3 + -4,param_4 + 8,4);
  ui_fill(param_1,param_2 + -4,param_3 + param_5,param_4 + 8,4,param_6);
  ui_fill(param_1,param_2 + -4,param_3 + -4,4,param_5 + 8,param_6);
  ui_fill(param_1,param_2 + param_4,param_3 + -4,4,param_5 + 8,param_6);
  return;
}


// ===== draw_faceup @ 10401fc0 =====

void draw_faceup(undefined4 param_1,int param_2,int param_3,int param_4,int param_5)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  
  gp = &__global_pointer_;
  uVar1 = 0xe0c6;
  if (0x19 < param_4 - 0xdU) {
    uVar1 = 0x1082;
  }
  iVar2 = param_2 + 0x2a;
  iVar3 = param_3 + 6;
  if (param_5 == 0) {
    ui_fill(param_1,param_2,param_3,0x3c,0x24,0x630c);
    ui_fill(param_1,param_2 + 2,param_3 + 2,0x38,0x20,0xffff);
    ui_text(param_1,param_2 + 4,param_3 + -8,(&r_0)[param_4 % 0xd],uVar1);
  }
  else {
    ui_fill(param_1,param_2,param_3,0x3c,0x50,0x630c);
    ui_fill(param_1,param_2 + 2,param_3 + 2,0x38,0x4c,0xffff);
    ui_text(param_1,param_2 + 4,param_3 + -8,(&r_0)[param_4 % 0xd],uVar1);
    draw_pip(param_1,iVar2,iVar3,param_4 / 0xd,uVar1);
    iVar3 = param_3 + 0x22;
    iVar2 = param_2 + 0x18;
  }
  draw_pip(param_1,iVar2,iVar3,param_4 / 0xd,uVar1);
  return;
}


// ===== sol_reset @ 10402140 =====

void sol_reset(void)

{
  bool bVar1;
  int *piVar2;
  int *piVar3;
  int iVar4;
  undefined1 *puVar5;
  int *piVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  undefined4 *puVar11;
  int iVar12;
  int local_e0 [51];
  int local_14;
  
  gp = &__global_pointer_;
  piVar2 = local_e0;
  iVar9 = 0;
  do {
    *piVar2 = iVar9;
    iVar9 = iVar9 + 1;
    piVar2 = piVar2 + 1;
  } while (iVar9 != 0x34);
  iVar9 = 0x34;
  piVar2 = &local_14;
  do {
    iVar4 = rand();
    if (iVar9 != 0) {
      iVar4 = iVar4 % iVar9;
    }
    iVar10 = *piVar2;
    piVar3 = piVar2 + -1;
    iVar9 = iVar9 + -1;
    *piVar2 = local_e0[iVar4];
    local_e0[iVar4] = iVar10;
    piVar2 = piVar3;
  } while (local_e0 != piVar3);
  puVar5 = &piles;
  puVar11 = &DAT_ram_1043508c;
  do {
    *puVar11 = 0;
    puVar11 = puVar11 + 0x1b;
  } while (puVar11 != (undefined4 *)(g_mfb + 0x38));
  iVar10 = 1;
  iVar4 = 0;
  iVar9 = 0;
  do {
    piVar2 = local_e0 + iVar4;
    iVar7 = 0;
    do {
      iVar12 = iVar7;
      iVar7 = *(int *)(puVar5 + 0x2f0);
      if (iVar7 < 0x34) {
        iVar8 = *piVar2;
        (&piles + iVar7 + (iVar9 + 6) * 0x6c)[0x34] = iVar9 == iVar12;
        (&piles)[iVar7 + (iVar9 + 6) * 0x6c] = (char)iVar8;
        *(int *)(puVar5 + 0x2f0) = iVar7 + 1;
      }
      piVar2 = piVar2 + 1;
      iVar7 = iVar12 + 1;
    } while (iVar12 + 1 != iVar10);
    iVar4 = iVar4 + 1 + iVar9;
    iVar9 = iVar9 + 1;
    iVar10 = iVar12 + 2;
    puVar5 = puVar5 + 0x6c;
  } while (iVar9 != 7);
  if (0x33 < iVar4) goto LAB_ram_10402320;
  piVar2 = local_e0 + iVar4;
  bVar1 = false;
  piVar3 = local_e0 + 0x34;
  iVar9 = DAT_ram_1043508c;
  do {
    if (0x33 < iVar9) goto LAB_ram_1040234a;
    iVar4 = *piVar2;
    (&DAT_ram_10435058)[iVar9] = 0;
    piVar2 = piVar2 + 1;
    (&piles)[iVar9] = (char)iVar4;
    iVar9 = iVar9 + 1;
    bVar1 = true;
  } while (piVar3 != piVar2);
  goto LAB_ram_1040231c;
  while (piVar3 != piVar2) {
LAB_ram_1040234a:
    piVar6 = piVar2 + 1;
    piVar2 = piVar2 + 2;
    if (piVar3 == piVar6) break;
  }
  if (!bVar1) goto LAB_ram_10402320;
LAB_ram_1040231c:
  DAT_ram_1043508c = iVar9;
LAB_ram_10402320:
  cur_idx = DAT_ram_10435314 + -1;
  cur_pile = 6;
  sel_pile = 0xffffffff;
  sel_idx = 0xffffffff;
  game_state = 0;
  return;
}


// ===== sol_step @ 10402380 =====

uint sol_step(uint param_1)

{
  undefined1 uVar1;
  bool bVar2;
  undefined2 *puVar3;
  int iVar4;
  uint uVar5;
  undefined2 *puVar6;
  undefined *puVar7;
  int iVar8;
  uint uVar9;
  uint uVar10;
  undefined1 *puVar11;
  int iVar12;
  undefined2 *puVar13;
  undefined1 *puVar14;
  char *pcVar15;
  int iVar16;
  int iVar17;
  char *pcVar18;
  undefined2 *puStack_48;
  
  gp = &__global_pointer_;
  if (game_state == 1) {
    ui_vgrad(param_1,0,0,0x280,0x1e0,0x138a,0x144);
    ui_text_center(param_1,0x140,0xb8,s_YOU_WIN_ram_104172c4,0xffff);
    ui_text_center(param_1,0x140,0xf8,s_A__new_game_ram_10417308,0xe71c);
    ui_text_center(param_1,0x140,0x120,s_B__exit_ram_10417314,0xe71c);
    if ((DAT_ram_1254be1c & 0x10) != 0) {
      sol_reset();
    }
    return DAT_ram_1254be1c >> 5 & 1;
  }
  if ((DAT_ram_1254be1c & 0x20) != 0) {
    uVar5 = 1;
    if ((int)sel_pile < 0) {
      return uVar5;
    }
    sel_pile = 0xffffffff;
    sel_idx = 0xffffffff;
    if ((DAT_ram_1254be1c & 4) != 0) goto LAB_ram_104026aa;
LAB_ram_104023c4:
    if ((DAT_ram_1254be1c & 8) == 0) goto LAB_ram_104023cc;
LAB_ram_104026d0:
    if ((int)cur_pile < 6) {
      if (cur_pile != 5) {
        cur_pile = cur_pile + 1 & (int)~(cur_pile + 1) >> 0x1f;
      }
    }
    else if ((int)cur_pile < 0xc) {
      cur_pile = cur_pile + 1;
    }
    uVar5 = fix_cur_idx(uVar5);
    if ((DAT_ram_1254be1c & 1) != 0) goto LAB_ram_104026f6;
LAB_ram_104023d4:
    if ((DAT_ram_1254be1c & 2) == 0) goto LAB_ram_104023e4;
    if ((int)cur_pile < 6) goto LAB_ram_10402b24;
    iVar4 = (&DAT_ram_1043508c)[cur_pile * 0x1b];
    if (iVar4 < 1) {
LAB_ram_10402af0:
      if ((DAT_ram_1254be1c & 0x10) == 0) goto LAB_ram_104023ec;
      if (-1 < (int)sel_pile) goto LAB_ram_104029ca;
      iVar4 = (&DAT_ram_1043508c)[cur_pile * 0x1b];
      if (iVar4 != 0) goto LAB_ram_10402a84;
    }
    else {
LAB_ram_104029b0:
      if (iVar4 + -1 <= (int)cur_idx) goto LAB_ram_10402af0;
      if (-1 < (int)sel_pile) {
        if ((DAT_ram_1254be1c & 0x10) != 0) goto LAB_ram_104029ca;
        goto LAB_ram_104023ec;
      }
      cur_idx = cur_idx + 1;
      if ((DAT_ram_1254be1c & 0x10) == 0) goto LAB_ram_104023ec;
      if ((&DAT_ram_1043508c)[cur_pile * 0x1b] == 0) goto LAB_ram_10402a2e;
LAB_ram_10402b6c:
      if ((5 < (int)cur_pile) && ((&DAT_ram_10435058)[cur_pile * 0x6c + cur_idx] != '\0')) {
        sel_idx = cur_idx;
        sel_pile = cur_pile;
        goto LAB_ram_104029d8;
      }
    }
    goto LAB_ram_10402a2e;
  }
  uVar5 = param_1;
  if ((DAT_ram_1254be1c & 4) == 0) goto LAB_ram_104023c4;
LAB_ram_104026aa:
  if ((int)cur_pile < 6) {
    if (0 < (int)cur_pile) goto LAB_ram_104026ba;
  }
  else if (cur_pile != 6) {
LAB_ram_104026ba:
    cur_pile = cur_pile - 1;
  }
  uVar5 = fix_cur_idx(uVar5);
  if ((DAT_ram_1254be1c & 8) != 0) goto LAB_ram_104026d0;
LAB_ram_104023cc:
  if ((DAT_ram_1254be1c & 1) == 0) goto LAB_ram_104023d4;
LAB_ram_104026f6:
  if (5 < (int)cur_pile) {
    iVar4 = (&DAT_ram_1043508c)[cur_pile * 0x1b];
    if (0 < iVar4) {
      iVar12 = 0;
      do {
        uVar5 = (uint)(byte)(&DAT_ram_10435058)[iVar12 + cur_pile * 0x6c];
        if (uVar5 != 0) {
          if (((iVar12 < iVar4) && (uVar5 = cur_idx, iVar12 < (int)cur_idx)) && ((int)sel_pile < 0))
          {
            cur_idx = cur_idx - 1;
            if ((DAT_ram_1254be1c & 2) != 0) goto LAB_ram_104029b0;
            if ((DAT_ram_1254be1c & 0x10) == 0) goto LAB_ram_104023ec;
            goto LAB_ram_10402a68;
          }
          break;
        }
        iVar12 = iVar12 + 1;
      } while (iVar4 != iVar12);
    }
    cur_pile = cur_pile - 6;
    if (5 < (int)cur_pile) {
      cur_pile = 5;
    }
    uVar5 = fix_cur_idx(uVar5);
  }
  if ((DAT_ram_1254be1c & 2) != 0) {
LAB_ram_10402b24:
    cur_pile = cur_pile + 6;
    fix_cur_idx(uVar5);
  }
LAB_ram_104023e4:
  uVar5 = DAT_ram_1254be1c;
  if ((DAT_ram_1254be1c & 0x10) == 0) {
LAB_ram_104023ec:
    if ((DAT_ram_1254be1c & 0x40) == 0) goto LAB_ram_10402416;
    if (-1 < (int)sel_pile) goto LAB_ram_104023fc;
LAB_ram_10402a3e:
    iVar4 = (&DAT_ram_1043508c)[cur_pile * 0x1b];
    uVar5 = cur_pile;
    if (cur_pile == 0 || iVar4 < 1) goto LAB_ram_10402416;
  }
  else {
    if (cur_pile == 0) {
      if (DAT_ram_1043508c < 1) {
        if (0 < DAT_ram_104350f8) {
          puVar14 = &piles + DAT_ram_104350f8;
          bVar2 = false;
          iVar4 = DAT_ram_1043508c;
          do {
            if (iVar4 == 0x34) goto LAB_ram_10402c1a;
            uVar1 = puVar14[0x6b];
            (&DAT_ram_10435058)[iVar4] = 0;
            puVar14 = puVar14 + -1;
            (&piles)[iVar4] = uVar1;
            iVar4 = iVar4 + 1;
            bVar2 = true;
          } while (puVar14 != &piles);
          DAT_ram_1043508c = iVar4;
          goto LAB_ram_10402c14;
        }
      }
      else {
        iVar4 = DAT_ram_1043508c + -1;
        puVar7 = &DAT_ram_10435023 + DAT_ram_1043508c;
        DAT_ram_1043508c = iVar4;
        if (DAT_ram_104350f8 < 0x34) {
          (&DAT_ram_10435090)[DAT_ram_104350f8] = *puVar7;
          puVar7 = &DAT_ram_104350c4 + DAT_ram_104350f8;
          DAT_ram_104350f8 = DAT_ram_104350f8 + 1;
          *puVar7 = 1;
        }
      }
      goto LAB_ram_10402bd4;
    }
LAB_ram_10402a68:
    if ((int)sel_pile < 0) {
      iVar4 = (&DAT_ram_1043508c)[cur_pile * 0x1b];
      if (iVar4 == 0) {
LAB_ram_10402a2e:
        uVar5 = DAT_ram_1254be1c;
        goto LAB_ram_10402a32;
      }
      if (cur_pile != 1) {
LAB_ram_10402a84:
        if (3 < cur_pile - 2) goto LAB_ram_10402b6c;
      }
      sel_idx = iVar4 - 1;
      sel_pile = cur_pile;
    }
    else {
LAB_ram_104029ca:
      if (sel_pile == cur_pile) {
        sel_pile = 0xffffffff;
        sel_idx = 0xffffffff;
        uVar5 = DAT_ram_1254be1c;
LAB_ram_10402a32:
        if ((uVar5 & 0x40) == 0) goto LAB_ram_10402416;
        goto LAB_ram_10402a3e;
      }
      iVar4 = do_move(sel_pile,sel_idx);
      if (iVar4 != 0) {
        sel_pile = 0xffffffff;
        sel_idx = 0xffffffff;
        fix_cur_idx();
        goto LAB_ram_10402a2e;
      }
    }
LAB_ram_104029d8:
    if ((DAT_ram_1254be1c & 0x40) == 0) goto LAB_ram_10402416;
LAB_ram_104023fc:
    iVar4 = (&DAT_ram_1043508c)[sel_pile * 0x1b];
    uVar5 = sel_pile;
    if (sel_pile == 0 || iVar4 < 1) goto LAB_ram_10402416;
  }
  uVar9 = sel_pile;
  iVar4 = do_move(uVar5,iVar4 + -1,(int)(char)(&piles)[iVar4 + -1 + uVar5 * 0x6c] / 0xd + 2);
  if (iVar4 != 0) {
    if (-1 < (int)uVar9) {
      sel_pile = 0xffffffff;
      sel_idx = 0xffffffff;
    }
    fix_cur_idx();
  }
LAB_ram_10402416:
  puVar14 = &piles;
  ui_vgrad(param_1,0,0,0x280,0x1e0,0x1308,0x9c4);
  if (DAT_ram_1043508c < 1) {
    ui_fill(param_1,0xc,0xc,0x3c,0x50,0x43cc);
    ui_fill(param_1,0xe,0xe,0x38,0x4c,0xa05);
    ui_text_center(param_1,0x2a,0x22,&DAT_ram_1041731c,0xa514);
  }
  else {
    draw_facedown(param_1,0xc);
  }
  if (DAT_ram_104350f8 < 1) {
    ui_fill(param_1,0x4e,0xc,0x3c,0x50,0x43cc);
    ui_fill(param_1,0x50,0xe,0x38,0x4c,0xa05);
  }
  else {
    draw_faceup(param_1,0x4e,0xc,(int)*(char *)((int)&DAT_ram_1043508c + DAT_ram_104350f8 + 3),1);
  }
  iVar4 = 0x164;
  iVar12 = 0;
  do {
    if (*(int *)(puVar14 + 0x140) < 1) {
      ui_fill(param_1,iVar4,0xc,0x3c,0x50,0x43cc);
      ui_fill(param_1,iVar4 + 2,0xe,0x38,0x4c,0xa05);
      draw_pip(param_1,iVar4 + 0x18,0x2e,iVar12,0x7450);
    }
    else {
      draw_faceup();
    }
    iVar12 = iVar12 + 1;
    puVar14 = puVar14 + 0x6c;
    iVar4 = iVar4 + 0x40;
  } while (iVar12 != 4);
  puStack_48 = (undefined2 *)(param_1 + 0x24e24);
  pcVar15 = &DAT_ram_104352ac;
  iVar4 = 0xe;
  do {
    while( true ) {
      iVar8 = *(int *)(pcVar15 + 0x68);
      iVar12 = iVar4 + -2;
      if (iVar8 == 0) break;
      iVar17 = 0x76;
      iVar16 = 0;
      puVar13 = puStack_48;
      pcVar18 = pcVar15;
      if (0 < iVar8) {
        do {
          while( true ) {
            if (pcVar18[0x34] == '\0') break;
            draw_faceup(param_1,iVar12,iVar17 + -6,(int)*pcVar18,iVar8 + -1 == iVar16);
            iVar8 = *(int *)(pcVar15 + 0x68);
            iVar16 = iVar16 + 1;
            pcVar18 = pcVar18 + 1;
            iVar17 = iVar17 + 0x1c;
            puVar13 = puVar13 + 0x4600;
            if (iVar8 <= iVar16) goto LAB_ram_10402546;
          }
          if (iVar8 + -1 == iVar16) {
            draw_facedown(param_1,iVar12);
          }
          else {
            ui_fill(param_1,iVar12,iVar17 + -6,0x3c,0x20,0xffff);
            ui_fill(param_1,iVar4,iVar17 + -4,0x38,0x1c,0x211a);
            iVar8 = iVar17 * 0x280;
            uVar5 = iVar4 + 0x34 + iVar17;
            puVar3 = puVar13;
            do {
              uVar9 = uVar5 - 0x30;
              puVar6 = puVar3;
              do {
                while (uVar10 = uVar9 & 3, uVar9 = uVar9 + 1,
                      !(uVar10 != 0 || 0x1df < (int)((-0x34 - iVar4) + uVar5))) {
                  *puVar6 = 0x429f;
                  puVar6 = puVar6 + 1;
                  if (uVar5 == uVar9) goto LAB_ram_104027ee;
                }
                puVar6 = puVar6 + 1;
              } while (uVar5 != uVar9);
LAB_ram_104027ee:
              iVar8 = iVar8 + 0x280;
              uVar5 = uVar5 + 1;
              puVar3 = puVar3 + 0x280;
            } while (iVar16 * 0x4600 + 0x15e00 != iVar8);
          }
          iVar8 = *(int *)(pcVar15 + 0x68);
          iVar16 = iVar16 + 1;
          pcVar18 = pcVar18 + 1;
          iVar17 = iVar17 + 0x1c;
          puVar13 = puVar13 + 0x4600;
        } while (iVar16 < iVar8);
      }
LAB_ram_10402546:
      iVar4 = iVar4 + 0x4c;
      puStack_48 = puStack_48 + 0x4c;
      pcVar15 = pcVar15 + 0x6c;
      if (iVar4 == 0x222) goto LAB_ram_1040255e;
    }
    ui_fill(param_1,iVar4 + -2,0x70,0x3c,0x50,0x43cc);
    ui_fill(param_1,iVar4,0x72,0x38,0x4c,0xa05);
    iVar4 = iVar4 + 0x4c;
    puStack_48 = puStack_48 + 0x4c;
    pcVar15 = pcVar15 + 0x6c;
  } while (iVar4 != 0x222);
LAB_ram_1040255e:
  if (-1 < (int)sel_pile) {
    if (sel_pile == 1) {
      iVar8 = 0x50;
      iVar12 = 0xc;
      iVar4 = 0x4e;
    }
    else if (sel_pile - 2 < 4) {
      iVar4 = sel_pile * 0x40 + 0xe4;
      iVar8 = 0x50;
      iVar12 = 0xc;
    }
    else {
      uVar5 = sel_idx & (int)~sel_idx >> 0x1f;
      uVar9 = (&DAT_ram_1043508c)[sel_pile * 0x1b] - 1U &
              -(&DAT_ram_1043508c)[sel_pile * 0x1b] >> 0x1f;
      iVar4 = (sel_pile - 6) * 0x4c + 0xc;
      if ((int)uVar9 < (int)uVar5) {
        uVar5 = uVar9;
      }
      iVar8 = (uVar9 - uVar5) * 0x1c + 0x50;
      iVar12 = uVar5 * 0x1c + 0x70;
    }
    draw_outline(param_1,iVar4,iVar12,0x3c,iVar8,0xff88);
  }
  iVar4 = 0xc;
  iVar12 = 0xc;
  if ((cur_pile != 0) && (iVar4 = 0x4e, cur_pile != 1)) {
    if (cur_pile - 2 < 4) {
      iVar4 = cur_pile * 0x40 + 0xe4;
    }
    else {
      iVar12 = 0x70;
      iVar8 = (&DAT_ram_1043508c)[cur_pile * 0x1b];
      iVar4 = (cur_pile - 6) * 0x4c + 0xc;
      if (iVar8 != 0) {
        uVar5 = cur_idx;
        if (iVar8 <= (int)cur_idx) {
          uVar5 = iVar8 - 1;
        }
        iVar12 = uVar5 * 0x1c + 0x70;
      }
    }
  }
  draw_outline(param_1,iVar4,iVar12,0x3c,0x50,0x479f);
  ui_text(param_1,0xc,0x1c0,s_A_pick_move_B_cancel_exit_X__>fo_ram_10417320,0xa596);
  return 0;
  while (puVar14 = puVar11, puVar11 != &piles) {
LAB_ram_10402c1a:
    puVar11 = puVar14 + -2;
    if (puVar14 == &DAT_ram_10435025) break;
  }
  if (bVar2) {
    DAT_ram_1043508c = 0x34;
  }
LAB_ram_10402c14:
  DAT_ram_104350f8 = 0;
LAB_ram_10402bd4:
  if (-1 < (int)sel_pile) {
    sel_pile = 0xffffffff;
    sel_idx = 0xffffffff;
  }
  goto LAB_ram_10402a32;
}


