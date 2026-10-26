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
  snprintf(acStack_c0,0xa0,&DAT_ram_1041745c,s__music_ram_10417454,param_1);
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
    snprintf(acStack_c0,0xa0,&DAT_ram_1041745c,s__music_ram_10417454);
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
  undefined4 uVar1;
  int iVar2;
  char *param3;
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
    uVar1 = ui_theme_name();
    snprintf(buf_0,0x30,&DAT_ram_10417478,uVar1);
    break;
  case 7:
    param3 = (&IPOD_THEMES)[param_1 * 0xc];
    iVar2 = ui_theme_index();
    param4 = &DAT_ram_104174c0;
    if (iVar2 == param_1) {
      param4 = &DAT_ram_10417474;
    }
    snprintf(buf_0,0x30,&DAT_ram_10417484,param3,param4);
    break;
  case 8:
    return *(undefined1 **)(&GAMES)[param_1];
  }
  return buf_0;
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


// ===== render_np @ 10407780 =====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

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
    if (_DAT_ram_c0de0006 < g_vol_until) {
      uVar3 = ui_bg(0,_DAT_ram_c0de0006,0,0,0,g_vol_until,3);
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

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

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
        mq_reveal_until = _DAT_ram_c0de0006 + 0x5dc;
      }
    }
    else {
      uVar3 = 0;
      uVar6 = mq_reveal_until;
      if ((mq_reveal_until <= _DAT_ram_c0de0006) || (uVar6 = DAT_ram_1254be1c & 0x10, uVar6 != 0)) {
        uVar3 = mq_new(0,_DAT_ram_c0de0006,0,0,0,uVar6,3);
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


