// ===== para_reset @ 10400a40 =====

void para_reset(void)

{
  gp = &__global_pointer_;
  memset(&bullets,0,0xa0);
  memset(&troops,0,0x150);
  aim = 6;
  score = 0;
  lives = 3;
  gameover = 0;
  frame = 0;
  spawn_interval = 0x6e;
  spawn_timer = 0x28;
  return;
}


// ===== disc @ 10400ac0 =====

void disc(int param_1,int param_2,int param_3,int param_4,undefined2 param_5)

{
  int iVar1;
  int iVar2;
  undefined2 *puVar3;
  int iVar4;
  int iVar5;
  
  gp = &__global_pointer_;
  iVar5 = (param_3 - param_4) * 0x280;
  iVar4 = -param_4;
  do {
    puVar3 = (undefined2 *)(iVar5 * 2 + param_1 + (param_2 - param_4) * 2);
    iVar1 = -param_4;
    do {
      while ((iVar2 = iVar1, param_4 * param_4 < iVar2 * iVar2 + iVar4 * iVar4 ||
             (0x1df < (uint)(iVar4 + param_3) || 0x27f < (uint)(iVar2 + param_2)))) {
        puVar3 = puVar3 + 1;
        iVar1 = iVar2 + 1;
        if (iVar2 + 1 == param_4 + 1) goto LAB_ram_10400b80;
      }
      *puVar3 = param_5;
      puVar3 = puVar3 + 1;
      iVar1 = iVar2 + 1;
    } while (iVar2 + 1 != param_4 + 1);
LAB_ram_10400b80:
    iVar4 = iVar4 + 1;
    iVar5 = iVar5 + 0x280;
    if (iVar4 == iVar2 + 1) {
      return;
    }
  } while( true );
}


// ===== line @ 10400bc0 =====

void line(int param_1,uint param_2,uint param_3,int param_4,int param_5,undefined2 param_6)

{
  bool bVar1;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  bool bVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  uint uVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  
  gp = &__global_pointer_;
  uVar9 = (int)(param_4 - param_2) >> 0x1f;
  uVar7 = (int)(param_5 - param_3) >> 0x1f;
  iVar8 = (param_5 - param_3 ^ uVar7) - uVar7;
  iVar11 = (uVar9 ^ param_4 - param_2) - uVar9;
  bVar1 = (int)param_3 < param_5;
  bVar2 = (int)param_2 < param_4;
  iVar10 = iVar11 - iVar8;
  bVar3 = param_3 < 0x1e0;
  bVar4 = param_2 < 0x280;
  iVar13 = param_2 - param_4;
  iVar12 = param_3 - param_5;
LAB_ram_10400c40:
  bVar5 = iVar13 == 0 && iVar12 == 0;
  iVar6 = iVar10 << 1;
  if ((bool)(bVar3 & bVar4)) goto LAB_ram_10400ca4;
  do {
    if (bVar5) {
      return;
    }
    while( true ) {
      if (-iVar8 <= iVar6) {
        param_2 = param_2 + (bVar2 - 1 | 1);
        iVar10 = iVar10 - iVar8;
        bVar4 = param_2 < 0x280;
        iVar13 = param_2 - param_4;
        if (iVar11 < iVar6) goto LAB_ram_10400c40;
      }
      param_3 = param_3 + (bVar1 - 1 | 1);
      bVar3 = param_3 < 0x1e0;
      iVar12 = param_3 - param_5;
      iVar10 = iVar10 + iVar11;
      bVar5 = iVar13 == 0 && iVar12 == 0;
      iVar6 = iVar10 * 2;
      if (!(bool)(bVar3 & bVar4)) break;
LAB_ram_10400ca4:
      *(undefined2 *)((param_3 * 0x280 + param_2) * 2 + param_1) = param_6;
      if (bVar5) {
        return;
      }
    }
  } while( true );
}


// ===== para_step @ 10400d00 =====

undefined4 para_step(int param_1)

{
  bool bVar1;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  uint uVar5;
  undefined2 uVar6;
  int iVar7;
  char cVar8;
  uint uVar9;
  int iVar10;
  uint uVar11;
  int iVar12;
  int iVar13;
  int *piVar14;
  undefined2 *puVar15;
  int iVar16;
  char *pcVar17;
  uint uVar18;
  uint uVar19;
  char *pcVar20;
  int iVar21;
  int *piVar22;
  int *piVar23;
  undefined2 *puVar24;
  uint uVar25;
  uint uVar26;
  int *piStack_84;
  char local_70 [6];
  char cStack_6a;
  undefined1 uStack_69;
  char local_60 [6];
  char acStack_5a [38];
  
  uVar5 = DAT_ram_1254be1c;
  gp = &__global_pointer_;
  if ((DAT_ram_1254be1c & 0x20) != 0) {
    return 1;
  }
  if (gameover == 0) {
    iVar16 = frame + 1;
    spawn_timer = spawn_timer + -1;
  }
  else {
    if ((DAT_ram_1254be1c & 0x10) == 0) {
      ui_vgrad(param_1,0,0,0x280,0x1e0,0x108a,0x4218);
      ui_text_center(param_1,0x140,0x8c,s_GAME_OVER_ram_104172b8,0xfa94);
      if (score == 0) {
        local_70[0] = '0';
        iVar7 = 0;
      }
      else {
        iVar16 = 0;
        uVar5 = score;
        if ((int)score < 1) {
          iVar7 = -1;
        }
        else {
          do {
            iVar7 = iVar16;
            local_70[iVar7] = (char)uVar5 + (char)(uVar5 / 10) * -10 + '0';
            bVar3 = 9 < (int)uVar5;
            iVar16 = iVar7 + 1;
            uVar5 = uVar5 / 10;
          } while (bVar3);
        }
      }
      pcVar20 = s_SCORE_ram_104172d4;
      cVar8 = 'S';
      pcVar17 = local_60;
      do {
        *pcVar17 = cVar8;
        pcVar20 = pcVar20 + 1;
        cVar8 = *pcVar20;
        pcVar17 = pcVar17 + 1;
      } while (pcVar20 != s_SCORE_ram_104172d4 + 6);
      if (iVar7 == -1) {
        iVar7 = 6;
      }
      else {
        pcVar20 = local_70 + iVar7;
        pcVar17 = acStack_5a;
        do {
          cVar8 = *pcVar20;
          pcVar20 = pcVar20 + -1;
          *pcVar17 = cVar8;
          pcVar17 = pcVar17 + 1;
        } while (local_70 + -1 != pcVar20);
        iVar7 = iVar7 + 7;
      }
      local_60[iVar7] = '\0';
      ui_text_center(param_1,0x140,0xd2,local_60,0xffff);
      ui_text_center(param_1,0x140,300,s_A___RESTART_ram_104172dc,0xa654);
      ui_text_center(param_1,0x140,0x158,s_B___EXIT_ram_104172e8,0x4508);
      return 0;
    }
    memset(&bullets,0,0xa0);
    memset(&troops,0,0x150);
    aim = 6;
    lives = 3;
    spawn_interval = 0x6e;
    gameover = 0;
    score = 0;
    spawn_timer = 0x27;
    iVar16 = 1;
  }
  piVar22 = &troops;
  piVar23 = &bullets;
  if ((uVar5 & 4) == 0) {
LAB_ram_10400d6e:
    if (((uVar5 & 8) != 0) && (aim < 0xc)) {
LAB_ram_10401638:
      aim = aim + 1;
    }
  }
  else {
    if (0 < aim) {
      aim = aim + -1;
      goto LAB_ram_10400d6e;
    }
    if ((uVar5 & 8) != 0) goto LAB_ram_10401638;
  }
  uVar9 = _of_input_p0 & 8;
  if ((_of_input_p0 & 4) == 0) {
    if ((uVar9 == 0) || (0x24924924 < (uint)(iVar16 * -0x49249249))) goto LAB_ram_10400da0;
LAB_ram_1040160e:
    if (0xb < aim) goto LAB_ram_10400da0;
  }
  else {
    if (0x24924924 < (uint)(iVar16 * -0x49249249)) goto LAB_ram_10400da0;
    if (0 < aim) {
      aim = aim + -1;
      if (uVar9 == 0) goto LAB_ram_10400da0;
      goto LAB_ram_1040160e;
    }
    if (uVar9 == 0) goto LAB_ram_10400da0;
  }
  aim = aim + 1;
LAB_ram_10400da0:
  iVar7 = 0;
  piVar14 = piVar23;
  frame = iVar16;
  if ((uVar5 & 0x50) != 0) {
    do {
      iVar10 = *piVar14;
      piVar14 = piVar14 + 5;
      if (iVar10 == 0) {
        iVar21 = *(int *)(aim_dx + aim * 4);
        iVar12 = iVar21 * 0x24;
        iVar10 = *(int *)(aim_dy + aim * 4);
        iVar13 = iVar10 * 0x24;
        (&DAT_ram_10434f88)[iVar7 * 5] =
             (((int)((iVar12 >> 0x1f & 0xffU) + iVar12) >> 8) + 0x140) * 0x10;
        (&bullets)[iVar7 * 5] = 1;
        iVar21 = iVar21 * 0xc0;
        iVar10 = iVar10 * 0xc0;
        (&DAT_ram_10434f8c)[iVar7 * 5] =
             (((int)((iVar13 >> 0x1f & 0xffU) + iVar13) >> 8) + 0x1bc) * 0x10;
        (&DAT_ram_10434f90)[iVar7 * 5] = (int)((iVar21 >> 0x1f & 0xffU) + iVar21) >> 8;
        (&DAT_ram_10434f94)[iVar7 * 5] = (int)((iVar10 >> 0x1f & 0xffU) + iVar10) >> 8;
        break;
      }
      iVar7 = iVar7 + 1;
    } while (iVar7 != 8);
  }
  if (spawn_timer < 1) {
    iVar7 = 0;
    piVar14 = piVar22;
    do {
      iVar10 = *piVar14;
      piVar14 = piVar14 + 7;
      if (iVar10 == 0) {
        (&troops)[iVar7 * 7] = 1;
        uVar5 = rand();
        *(uint *)(iVar7 * 0x1c + 0x10434e48) = (uint)(uVar5 % 100 < 0x23);
        uVar9 = rand();
        (&DAT_ram_10434e3c)[iVar7 * 7] = 0x100;
        (&DAT_ram_10434e4c)[iVar7 * 7] = 0;
        (&DAT_ram_10434e38)[iVar7 * 7] = (uVar9 % 0x230 + 0x28) * 0x10;
        if (uVar5 % 100 < 0x23) {
          uVar5 = rand();
          uVar5 = uVar5 & 1;
          if (uVar5 == 0) {
            uVar5 = 0xffffffff;
          }
          uVar9 = rand();
          (&DAT_ram_10434e40)[iVar7 * 7] = ((uVar9 & 0xf) + 0x10) * uVar5;
          uVar5 = rand();
          iVar16 = frame;
          (&DAT_ram_10434e44)[iVar7 * 7] = (uVar5 & 7) + 8;
        }
        else {
          uVar5 = rand();
          uVar5 = uVar5 & 1;
          if (uVar5 == 0) {
            uVar5 = 0xffffffff;
          }
          uVar9 = rand();
          (&DAT_ram_10434e40)[iVar7 * 7] = (uVar9 % 0xc) * uVar5;
          uVar5 = rand();
          iVar16 = frame;
          (&DAT_ram_10434e44)[iVar7 * 7] = uVar5 % 0xc + 0xe;
        }
        break;
      }
      iVar7 = iVar7 + 1;
    } while (iVar7 != 0xc);
    spawn_timer = spawn_interval;
  }
  if (((iVar16 * -0x60000000 + ((uint)(iVar16 * -0x5b05b05b) >> 3) < 0xb60b61) &&
      (0x23 < spawn_interval)) && (spawn_interval = spawn_interval + -8, spawn_interval < 0x23)) {
    spawn_interval = 0x23;
  }
  piVar14 = piVar23;
  do {
    if (*piVar14 != 0) {
      iVar16 = piVar14[1] + piVar14[3];
      iVar7 = piVar14[2] + piVar14[4];
      piVar14[1] = iVar16;
      piVar14[2] = iVar7;
      if ((0x290 < ((int)((iVar16 >> 0x1f & 0xfU) + iVar16) >> 4) + 8U) ||
         (0x1f0 < ((int)((iVar7 >> 0x1f & 0xfU) + iVar7) >> 4) + 8U)) {
        *piVar14 = 0;
      }
    }
    piVar14 = piVar14 + 5;
  } while (piVar14 != (int *)&piles);
  bVar3 = false;
  bVar1 = false;
  iVar16 = lives;
  piVar14 = piVar22;
  do {
    if (*piVar14 != 0) {
      iVar10 = piVar14[2];
      iVar13 = piVar14[1] + piVar14[3];
      piVar14[1] = iVar13;
      piVar14[2] = iVar10 + piVar14[4];
      piVar14[6] = piVar14[6] + 1;
      iVar7 = -piVar14[3];
      if (iVar13 < 0x1c0) {
        piVar14[1] = 0x1c0;
        piVar14[3] = iVar7;
      }
      else if (0x264f < iVar13) {
        piVar14[1] = 0x2640;
        piVar14[3] = iVar7;
      }
      if (0x1b7f < iVar10 + piVar14[4]) {
        *piVar14 = 0;
        iVar16 = iVar16 + -1;
        bVar1 = true;
        if (iVar16 < 1) {
          bVar3 = true;
          iVar16 = 0;
        }
      }
    }
    piVar14 = piVar14 + 7;
  } while (piVar14 != &bullets);
  if (bVar3) {
    gameover = 1;
  }
  if (bVar1) {
    lives = iVar16;
  }
  uVar5 = score;
  bVar3 = false;
LAB_ram_10400ee4:
  do {
    if (*piVar23 != 0) {
      iVar16 = 0;
      piVar14 = piVar22;
      do {
        iVar10 = 0x12;
        iVar7 = 0x20;
        if (*piVar14 != 0) {
          uVar9 = ((int)((piVar23[1] >> 0x1f & 0xfU) + piVar23[1]) >> 4) -
                  ((int)((piVar14[1] >> 0x1f & 0xfU) + piVar14[1]) >> 4);
          uVar25 = (int)uVar9 >> 0x1f;
          uVar18 = ((int)((piVar23[2] >> 0x1f & 0xfU) + piVar23[2]) >> 4) -
                   ((int)((piVar14[2] >> 0x1f & 0xfU) + piVar14[2]) >> 4);
          uVar26 = (int)uVar18 >> 0x1f;
          if (piVar14[5] != 0) {
            iVar10 = 0x18;
            iVar7 = 0x10;
          }
          bVar1 = (int)((uVar25 ^ uVar9) - uVar25) <= iVar10;
          bVar2 = (int)((uVar26 ^ uVar18) - uVar26) <= iVar7;
          bVar4 = bVar2 && bVar1;
          if (bVar2 && bVar1) {
            uVar5 = uVar5 + (-(uint)(piVar14[5] == 0) & 0xfffffff1) + 0x19;
            *piVar23 = 0;
            (&troops)[iVar16 * 7] = 0;
            piVar23 = piVar23 + 5;
            bVar3 = bVar4;
            if (piVar23 != (int *)&piles) goto LAB_ram_10400ee4;
            goto LAB_ram_10400fa0;
          }
        }
        iVar16 = iVar16 + 1;
        piVar14 = piVar14 + 7;
      } while (iVar16 != 0xc);
    }
    piVar23 = piVar23 + 5;
  } while (piVar23 != (int *)&piles);
LAB_ram_10400fa0:
  if (bVar3) {
    score = uVar5;
  }
  ui_vgrad(param_1,0,0,0x280,0x1e0,0x331f,0xa61f);
  ui_fill(param_1,0,0x1c4,0x280,0x1c,0x3246);
  ui_fill(param_1,0,0x1c0,0x280,4,0x534a);
  piStack_84 = &bullets;
  do {
    while (*piVar22 == 0) {
LAB_ram_1040111c:
      piVar22 = piVar22 + 7;
      if (piVar22 == &bullets) goto LAB_ram_104012bc;
    }
    uVar9 = (int)((piVar22[1] >> 0x1f & 0xfU) + piVar22[1]) >> 4;
    iVar7 = (int)((piVar22[2] >> 0x1f & 0xfU) + piVar22[2]) >> 4;
    iVar16 = uVar9 + 0xc;
    uVar5 = iVar7 - 8;
    if (piVar22[5] != 0) {
      iVar10 = piVar22[6];
      iVar13 = uVar9 - 0xe;
      ui_fill(param_1,iVar13,iVar7 + -6,0x1c,0xe,0x429f);
      ui_fill(param_1,uVar9 - 0x12,iVar7 + -2,10,8,0x2198);
      ui_fill(param_1,iVar16,iVar7 + -2,0x12,6,0x2198);
      ui_fill(param_1,uVar9 + 0x1c,uVar5,4,0xc,0x429f);
      line(param_1,uVar9 - 0xc,iVar7 + 10,iVar16,iVar7 + 10,0x2198);
      iVar16 = 0xe;
      if ((iVar10 / 3 & 1U) != 0) {
        iVar13 = uVar9 - 0x18;
        iVar16 = 0x18;
      }
      line(param_1,iVar13,iVar7 + -10,iVar16 + uVar9,iVar7 + -10,0xd69a);
      uVar18 = iVar7 - 0xc;
      if ((~uVar18 >> 0x1f & (uint)(uVar9 < 0x280)) == 0) {
        if (((uint)(uVar9 < 0x280) & ~uVar5 >> 0x1f) == 0) goto LAB_ram_1040111c;
      }
      else if ((int)uVar18 < 0x1e0) {
        *(undefined2 *)((uVar18 * 0x280 + uVar9) * 2 + param_1) = 0xd69a;
      }
      if ((int)uVar5 < 0x1e0) {
        *(undefined2 *)((uVar5 * 0x280 + uVar9) * 2 + param_1) = 0xd69a;
      }
      goto LAB_ram_1040111c;
    }
    uVar25 = iVar7 - 0x1a;
    puVar24 = (undefined2 *)((iVar7 * 0x280 + uVar9) * 2 + param_1 + -0x8220);
    uVar26 = uVar9 - 0x10;
    uVar18 = 0xfffffff0;
    do {
      uVar6 = 0xe108;
      if ((uVar18 & 8) != 0) {
        uVar6 = 0xfbce;
      }
      uVar11 = (iVar7 + -0x1d) - ((int)((0x100 - uVar18 * uVar18) * 0xe) >> 8);
      puVar15 = puVar24 + -0x500;
      uVar19 = iVar7 - 0x1c;
      do {
        while (bVar3 = uVar19 < 0x1e0, uVar19 = uVar19 - 1, !(bVar3 && uVar26 < 0x280)) {
          puVar15 = puVar15 + -0x280;
          if (uVar11 == uVar19) goto LAB_ram_10401218;
        }
        *puVar15 = uVar6;
        puVar15 = puVar15 + -0x280;
      } while (uVar11 != uVar19);
LAB_ram_10401218:
      if (uVar26 < 0x280 && uVar25 < 0x1e0) {
        *puVar24 = 0xe108;
      }
      uVar18 = uVar18 + 1;
      puVar24 = puVar24 + 1;
      uVar26 = uVar26 + 1;
    } while (uVar18 != 0x11);
    line(param_1,uVar9 - 0xc,uVar25,uVar9,uVar5,0xa514);
    line(param_1,iVar16,uVar25,uVar9,uVar5,0xa514);
    disc(param_1,uVar9,iVar7,6,0x33c8);
    uVar5 = iVar7 + 8;
    if ((~uVar5 >> 0x1f & (uint)(uVar9 < 0x280)) == 0) {
      if (((uint)(uVar9 < 0x280) & ~(iVar7 + 10U) >> 0x1f) != 0) goto LAB_ram_10401296;
      goto LAB_ram_1040111c;
    }
    if (0x1df < (int)uVar5) goto LAB_ram_1040111c;
    *(undefined2 *)((uVar5 * 0x280 + uVar9) * 2 + param_1) = 0x33c8;
LAB_ram_10401296:
    if (0x1df < iVar7 + 10) goto LAB_ram_1040111c;
    *(undefined2 *)(((iVar7 + 10) * 0x280 + uVar9) * 2 + param_1) = 0x33c8;
    piVar22 = piVar22 + 7;
  } while (piVar22 != &bullets);
LAB_ram_104012bc:
  ui_fill(param_1,0x120,0x1c0,0x40,0x1c,0x738e);
  ui_fill(param_1,300,0x1b4,0x28,0x10,0xb596);
  disc(param_1,0x140,0x1bc,0xc,0xb596);
  iVar16 = ((int)((*(int *)(aim_dy + aim * 4) * 0x2c >> 0x1f & 0xffU) +
                 *(int *)(aim_dy + aim * 4) * 0x2c) >> 8) + 0x1bc;
  iVar7 = (int)((*(int *)(aim_dx + aim * 4) * 0x2c >> 0x1f & 0xffU) +
               *(int *)(aim_dx + aim * 4) * 0x2c) >> 8;
  line(param_1,0x140,0x1bc,iVar7 + 0x140,iVar16,0xe71c);
  line(param_1,0x13e,0x1bc,iVar7 + 0x13e,iVar16,0xe71c);
  line(param_1,0x142,0x1bc,iVar7 + 0x142,iVar16,0xe71c);
  disc(param_1,iVar7 + 0x140,iVar16,2,0xffff);
  do {
    while (*piStack_84 == 0) {
LAB_ram_104013b6:
      piStack_84 = piStack_84 + 5;
      if (piStack_84 == (int *)&piles) goto LAB_ram_10401420;
    }
    iVar16 = piStack_84[2];
    uVar5 = (int)((piStack_84[1] >> 0x1f & 0xfU) + piStack_84[1]) >> 4;
    iVar7 = (int)((iVar16 >> 0x1f & 0xfU) + iVar16) >> 4;
    disc(param_1,uVar5,iVar7,4,0xff94);
    if (!(iVar16 + 0xfU < 0x1e0f && uVar5 < 0x280)) goto LAB_ram_104013b6;
    *(undefined2 *)((iVar7 * 0x280 + uVar5) * 2 + param_1) = 0xffff;
    piStack_84 = piStack_84 + 5;
  } while (piStack_84 != (int *)&piles);
LAB_ram_10401420:
  if (score == 0) {
    local_70[0] = '0';
    iVar7 = 0;
  }
  else {
    iVar16 = 0;
    uVar5 = score;
    if ((int)score < 1) {
      iVar7 = -1;
    }
    else {
      do {
        iVar7 = iVar16;
        local_70[iVar7] = (char)uVar5 + (char)(uVar5 / 10) * -10 + '0';
        bVar3 = 9 < (int)uVar5;
        iVar16 = iVar7 + 1;
        uVar5 = uVar5 / 10;
      } while (bVar3);
    }
  }
  pcVar20 = s_SCORE_ram_104172d4;
  cVar8 = 'S';
  pcVar17 = local_60;
  do {
    *pcVar17 = cVar8;
    pcVar20 = pcVar20 + 1;
    cVar8 = *pcVar20;
    pcVar17 = pcVar17 + 1;
  } while (pcVar20 != s_SCORE_ram_104172d4 + 6);
  if (iVar7 == -1) {
    iVar7 = 6;
  }
  else {
    pcVar20 = local_70 + iVar7;
    pcVar17 = acStack_5a;
    do {
      cVar8 = *pcVar20;
      pcVar20 = pcVar20 + -1;
      *pcVar17 = cVar8;
      pcVar17 = pcVar17 + 1;
    } while (local_70 + -1 != pcVar20);
    iVar7 = iVar7 + 7;
  }
  local_60[iVar7] = '\0';
  ui_text(param_1,0xe,0xe,local_60,0);
  ui_text(param_1,0xc,0xc,local_60,0xffff);
  pcVar20 = s_LIVES_ram_104172f4;
  cVar8 = 'L';
  pcVar17 = local_70;
  do {
    *pcVar17 = cVar8;
    pcVar20 = pcVar20 + 1;
    cVar8 = *pcVar20;
    pcVar17 = pcVar17 + 1;
  } while (pcVar20 != s_LIVES_ram_104172f4 + 6);
  cStack_6a = '0';
  if (-1 < lives) {
    cStack_6a = (char)lives + '0';
  }
  uStack_69 = 0;
  ui_text_right(param_1,0x274,0xe,local_70,0);
  ui_text_right(param_1,0x272,0xc,local_70,0xffff);
  return 0;
}


