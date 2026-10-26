// ===== brick_reset @ 10400040 =====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void brick_reset(void)

{
  undefined4 *puVar1;
  
  gp = &__global_pointer_;
  _rowcol = 0xfd06f908;
  puVar1 = (undefined4 *)&bricks;
  DAT_ram_10434e08 = 0x431f;
  DAT_ram_10434e04 = 0x464ce746;
  score = 0;
  lives = 3;
  state = 0;
  paused = 0;
  paddle_x = 0x112;
  brick_w = 0x47;
  do {
    *puVar1 = 0x1010101;
    puVar1[1] = 0x1010101;
    puVar1 = puVar1 + 2;
  } while (puVar1 != &troops);
  ball_y = 0x1b300;
  bricks_left = 0x28;
  ball_x = 0x14000;
  ball_vx = 0;
  ball_vy = 0;
  return;
}


// ===== draw_overlay_center @ 10400100 =====

void draw_overlay_center(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4
                        )

{
  gp = &__global_pointer_;
  ui_fill(param_1,100,0xaa,0x1b8,0x8c,4);
  ui_fill(param_1,100,0xaa,0x1b8,2,0xa512);
  ui_fill(param_1,100,0x134,0x1b8,2,0xa512);
  ui_fill(param_1,100,0xaa,2,0x8c,0xa512);
  ui_fill(param_1,0x21a,0xaa,2,0x8c,0xa512);
  ui_text_center(param_1,0x140,0xc6,param_2,param_4);
  ui_text_center(param_1,0x140,0xfa,param_3,0xffff);
  return;
}


// ===== brick_step @ 10400200 =====

undefined4 brick_step(int param_1)

{
  char *pcVar1;
  undefined2 uVar2;
  bool bVar3;
  char *pcVar4;
  int iVar5;
  int iVar6;
  size_t __n;
  int iVar7;
  uint uVar8;
  uint uVar9;
  char *pcVar10;
  int iVar11;
  undefined2 *puVar12;
  uint uVar13;
  int iVar14;
  int iVar15;
  uint uVar16;
  int iVar17;
  undefined2 *puVar18;
  int iVar19;
  undefined1 *puVar20;
  char acStack_80 [8];
  char acStack_78 [8];
  undefined4 uStack_70;
  undefined2 uStack_6c;
  char cStack_6a;
  undefined1 uStack_69;
  undefined4 uStack_60;
  undefined2 uStack_5c;
  undefined1 auStack_5a [38];
  
  gp = &__global_pointer_;
  if ((DAT_ram_1254be1c & 0x20) != 0) {
    return 1;
  }
  if (((int)(DAT_ram_1254be1c << 0x10) < 0) && (state < 2)) {
    paused = (uint)(paused == 0);
LAB_ram_10400268:
    if (paused == 0) {
      if ((_of_input_p0 & 4) != 0) {
        paddle_x = paddle_x - 10;
      }
      if ((_of_input_p0 & 8) != 0) {
        paddle_x = paddle_x + 10;
      }
      if ((int)paddle_x < 0x10) {
        paddle_x = 0x10;
      }
      else if (0x214 < (int)paddle_x) {
        paddle_x = 0x214;
      }
      if (state == 0) {
        ball_x = (paddle_x + 0x2e) * 0x100;
        ball_y = 0x1b300;
        if ((DAT_ram_1254be1c & 0x10) != 0) {
          uVar8 = rand();
          ball_vx = ((uVar8 & 1) - 1 & 0xfffffa00) + 0x300;
          state = 1;
          ball_vy = -0x600;
        }
      }
      else {
        ball_x = ball_x + ball_vx;
        iVar17 = (int)((ball_x >> 0x1f & 0xffU) + ball_x) >> 8;
        iVar15 = ball_y + ball_vy;
        iVar19 = iVar17 + -4;
        if (iVar19 < 0x11) {
          ball_vx = -ball_vx;
          ball_x = 0x1400;
          iVar19 = 0x10;
          iVar17 = 0x14;
        }
        else if (0x267 < iVar19) {
          ball_vx = -ball_vx;
          ball_x = 0x26c00;
          iVar19 = 0x268;
          iVar17 = 0x26c;
        }
        if (iVar15 < 0x3500) {
          ball_vy = -ball_vy;
          ball_y = 0x3400;
        }
        else {
          iVar5 = iVar15 >> 8;
          ball_y = iVar15;
          if ((ball_vy < 1) || (0x14 < iVar5 - 0x1b8U)) {
            if (iVar5 - 0x4dU < 0x93) {
              puVar20 = &bricks;
              iVar14 = 0;
              iVar11 = 0x50;
              do {
                if ((iVar11 <= iVar5 + 3) && (iVar5 + -4 <= iVar11 + 0x17)) {
                  iVar6 = 0;
                  iVar7 = 0x14;
                  do {
                    if (((puVar20[iVar6] != '\0') && (iVar7 <= iVar17 + 3)) &&
                       (iVar19 < brick_w + iVar7)) {
                      uVar8 = iVar5 - (iVar11 + 0xc);
                      uVar16 = (int)uVar8 >> 0x1f;
                      uVar9 = iVar17 - (iVar7 + brick_w / 2);
                      uVar13 = (int)uVar9 >> 0x1f;
                      if ((int)(((uVar16 ^ uVar8) - uVar16) * (brick_w / 2)) <
                          (int)(((uVar9 ^ uVar13) - uVar13) * 0xc)) {
                        ball_vx = -ball_vx;
                      }
                      else {
                        ball_vy = -ball_vy;
                      }
                      (&bricks)[iVar6 + iVar14 * 8] = 0;
                      score = (5 - iVar14) * 10 + score;
                      bricks_left = bricks_left + -1;
                      if (bricks_left == 0) {
                        state = 3;
                      }
                      goto LAB_ram_104008d6;
                    }
                    iVar6 = iVar6 + 1;
                    iVar7 = iVar7 + brick_w + 4;
                  } while (iVar6 != 8);
                }
                iVar14 = iVar14 + 1;
                iVar11 = iVar11 + 0x1c;
                puVar20 = puVar20 + 8;
              } while (iVar14 != 5);
            }
          }
          else if (((int)paddle_x <= iVar17 + 4) && (iVar19 <= (int)(paddle_x + 0x5c))) {
            ball_y = 0x1b700;
            ball_vy = -0x600;
            ball_vx = (int)((iVar17 - (paddle_x + 0x2e)) * 0x600) / 0x2e;
            goto LAB_ram_1040027e;
          }
LAB_ram_104008d6:
          if (0x1e0ff < iVar15) {
            lives = lives + -1;
            if (lives < 1) {
              state = 2;
            }
            else {
              ball_y = 0x1b300;
              paddle_x = 0x112;
              ball_vx = 0;
              ball_vy = 0;
              state = 0;
              ball_x = 0x14000;
            }
          }
        }
      }
    }
  }
  else {
    if (1 < state - 2) goto LAB_ram_10400268;
    if ((DAT_ram_1254be1c & 0x10) != 0) {
      brick_reset();
    }
  }
LAB_ram_1040027e:
  puVar20 = &bricks;
  ui_vgrad(param_1,0,0,0x280,0x1e0,0x108a,2);
  if (score == 0) {
    acStack_80[0] = '0';
    __n = 2;
    iVar15 = 1;
  }
  else if ((int)score < 1) {
    __n = 1;
    iVar15 = 0;
  }
  else {
    uVar8 = score;
    iVar15 = 0;
    do {
      iVar17 = iVar15;
      iVar15 = iVar17 + 1;
      bVar3 = 9 < (int)uVar8;
      pcVar4 = acStack_78 + iVar15;
      acStack_78[iVar17] = (char)uVar8 + (char)(uVar8 / 10) * -10 + '0';
      uVar8 = uVar8 / 10;
    } while (bVar3 && iVar17 != 6);
    pcVar10 = acStack_80;
    do {
      pcVar1 = pcVar4 + -1;
      pcVar4 = pcVar4 + -1;
      *pcVar10 = *pcVar1;
      pcVar10 = pcVar10 + 1;
    } while (acStack_78 != pcVar4);
    __n = iVar17 + 2;
  }
  uStack_5c = 0x2045;
  acStack_80[iVar15] = '\0';
  uStack_60 = 0x524f4353;
  memcpy(auStack_5a,acStack_80,__n);
  ui_text(param_1,0x10,6,&uStack_60,0xffff);
  uStack_6c = 0x2053;
  uStack_70 = 0x4556494c;
  cStack_6a = '0';
  if (-1 < lives) {
    cStack_6a = (char)lives + '0';
  }
  uStack_69 = 0;
  ui_text_right(param_1,0x270,6,&uStack_70,0xfe54);
  ui_fill(param_1,0,0x2e,0x280,2,0xa512);
  puVar18 = &rowcol;
  iVar15 = 0x66;
  do {
    uVar2 = *puVar18;
    iVar17 = 0;
    do {
      if (puVar20[iVar17] != '\0') {
        iVar19 = (brick_w + 4) * iVar17;
        ui_fill(param_1,iVar19 + 0x14,iVar15 + -0x16,brick_w,0x18,uVar2);
        ui_fill(param_1,iVar19 + 0x14,iVar15 + -0x16,brick_w,2,0xffff);
        ui_fill(param_1,iVar19 + 0x14,iVar15,brick_w,2,0x1086);
      }
      uVar8 = paddle_x;
      iVar17 = iVar17 + 1;
    } while (iVar17 != 8);
    iVar15 = iVar15 + 0x1c;
    puVar18 = puVar18 + 1;
    puVar20 = puVar20 + 8;
  } while (iVar15 != 0xf2);
  ui_fill(param_1,paddle_x,0x1bc,0x5c,0xc,0xa65f);
  ui_fill(param_1,uVar8 + 2,0x1bc,0x58,2,0xffff);
  ui_fill(param_1,uVar8 + 2,0x1c6,0x58,2,0x430e);
  if (uVar8 < 0x280) {
    iVar15 = (uVar8 + 0x45600) * 2;
    puVar18 = (undefined2 *)(param_1 + iVar15);
    *puVar18 = 0x108a;
    puVar12 = (undefined2 *)(iVar15 + 0x3700 + param_1);
    if (0x224 < (int)uVar8) goto LAB_ram_10400474;
    puVar18[0x5b] = 0x108a;
    *puVar12 = 0x108a;
    *(undefined2 *)((uVar8 + 0x471db) * 2 + param_1) = 0x108a;
  }
  else if (uVar8 + 0x5b < 0x280) {
    *(undefined2 *)((uVar8 + 0x4565b) * 2 + param_1) = 0x108a;
    puVar12 = (undefined2 *)((uVar8 + 0x471db) * 2 + param_1);
LAB_ram_10400474:
    *puVar12 = 0x108a;
  }
  iVar17 = (int)((ball_y >> 0x1f & 0xffU) + ball_y) >> 8;
  iVar15 = (int)((ball_x >> 0x1f & 0xffU) + ball_x) >> 8;
  uVar8 = iVar17 - 4;
  puVar18 = (undefined2 *)((iVar17 * 0x280 + iVar15) * 2 + param_1 + -0x1408);
  do {
    if (uVar8 < 0x1e0) {
      uVar13 = iVar15 - 4;
      puVar12 = puVar18;
      do {
        if (uVar13 < 0x280) {
          *puVar12 = 0xff9f;
        }
        uVar13 = uVar13 + 1;
        puVar12 = puVar12 + 1;
      } while (uVar13 != iVar15 + 4U);
    }
    uVar8 = uVar8 + 1;
    puVar18 = puVar18 + 0x280;
  } while (uVar8 != iVar17 + 4U);
  if (state == 0) {
    if (paused == 0) {
      ui_text_center(param_1,0x140,0x178,s_PRESS_A_TO_LAUNCH_ram_10417278,0xe712);
      goto LAB_ram_104005ae;
    }
  }
  else {
LAB_ram_104005ae:
    if (paused == 0) goto joined_r0x104005ba;
  }
  draw_overlay_center(param_1,s_PAUSED_ram_1041729c,s_START_to_resume_ram_1041728c,0xffff);
joined_r0x104005ba:
  if (state == 2) {
    draw_overlay_center(param_1,s_GAME_OVER_ram_104172b8,s_A_restart_B_exit_ram_104172a4,0xf988);
  }
  if (state == 3) {
    draw_overlay_center(param_1,s_YOU_WIN_ram_104172c4,s_A_restart_B_exit_ram_104172a4,0xe74a);
  }
  return 0;
}


