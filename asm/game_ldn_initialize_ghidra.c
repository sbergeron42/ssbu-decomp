
/* WARNING: Heritage AFTER dead removal. Example location: r0x00710523bc80 : 0x00710374459c */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Restarted to delay deadcode elimination for space: ram */
/* WARNING: Restarted to delay deadcode elimination for space: stack */

void game_ldn_initialize(undefined8 param_1)

{
  ulong *puVar1;
  uint uVar2;
  uint uVar3;
  ushort uVar4;
  ushort uVar5;
  undefined1 auVar6 [16];
  undefined1 auVar7 [16];
  undefined1 auVar8 [16];
  undefined1 auVar9 [16];
  undefined1 auVar10 [16];
  undefined1 auVar11 [16];
  undefined1 auVar12 [16];
  undefined8 uVar13;
  undefined1 auVar14 [16];
  undefined1 auVar15 [16];
  undefined1 auVar16 [16];
  undefined1 auVar17 [16];
  undefined1 auVar18 [16];
  undefined1 auVar19 [16];
  undefined1 auVar20 [16];
  uint *puVar21;
  undefined4 uVar22;
  int iVar23;
  BitFlagSet BVar24;
  EventType *pEVar25;
  ulong uVar26;
  undefined1 *puVar27;
  undefined8 *puVar28;
  undefined8 *puVar29;
  void *__s;
  undefined8 *puVar30;
  long *plVar31;
  uint *puVar32;
  undefined8 uVar33;
  undefined2 *puVar34;
  ushort *puVar35;
  uint uVar36;
  code *pcVar37;
  ulong *puVar38;
  ulong *puVar39;
  long *plVar40;
  ushort *puVar41;
  undefined2 *puVar42;
  ushort uVar43;
  ushort uVar44;
  ulong uVar45;
  ulong uVar46;
  long lVar47;
  long *plVar48;
  long lVar49;
  long lVar50;
  long lVar51;
  long lVar52;
  int *piVar53;
  int *piVar54;
  int *piVar55;
  VibrationDeviceHandle *pVVar56;
  SixAxisSensorHandle *pSVar57;
  ulong uVar58;
  uint *puVar59;
  Uid *pUVar60;
  float fVar61;
  undefined8 uVar62;
  undefined8 uVar63;
  float fVar68;
  undefined8 uVar69;
  undefined1 auVar64 [16];
  undefined1 auVar65 [16];
  undefined1 auVar66 [16];
  undefined1 auVar67 [16];
  float fVar70;
  float fVar71;
  float fVar79;
  float fVar80;
  undefined1 auVar72 [16];
  undefined1 auVar73 [16];
  float fVar81;
  undefined1 auVar74 [16];
  undefined8 uVar82;
  undefined1 auVar75 [16];
  undefined1 auVar76 [16];
  undefined1 auVar77 [16];
  undefined1 auVar78 [16];
  float fVar83;
  undefined8 uVar84;
  undefined1 auVar85 [16];
  undefined8 uVar87;
  undefined1 auVar86 [16];
  float fVar88;
  float fVar89;
  undefined8 uVar90;
  undefined1 auVar91 [16];
  undefined1 auVar92 [16];
  undefined1 auVar93 [16];
  undefined1 auVar94 [16];
  undefined1 auVar95 [16];
  float fVar96;
  float fVar97;
  float fVar98;
  float fVar99;
  float fVar100;
  float fVar101;
  undefined8 uVar102;
  undefined1 auVar103 [16];
  undefined1 auVar104 [16];
  undefined1 auVar105 [16];
  undefined8 uVar106;
  undefined1 auVar107 [16];
  float fVar108;
  undefined1 auVar109 [16];
  float fVar110;
  undefined1 auVar111 [16];
  float fVar112;
  float fVar113;
  float fVar114;
  float fVar115;
  float fVar116;
  float fVar117;
  byte bVar118;
  byte bVar122;
  byte bVar123;
  byte bVar124;
  float fVar120;
  byte bVar125;
  byte bVar126;
  byte bVar127;
  byte bVar128;
  undefined1 uVar129;
  undefined1 uVar130;
  undefined1 uVar131;
  undefined1 uVar132;
  undefined8 uVar133;
  undefined1 auVar134 [16];
  undefined1 auVar135 [16];
  undefined1 auVar136 [16];
  undefined2 uVar140;
  float fVar141;
  undefined8 uVar142;
  byte bVar150;
  byte bVar151;
  byte bVar152;
  byte bVar154;
  byte bVar155;
  byte bVar156;
  undefined1 auVar144 [16];
  undefined1 auVar145 [16];
  undefined1 auVar146 [16];
  undefined1 auVar147 [16];
  float fVar153;
  undefined1 auVar148 [16];
  float fVar157;
  undefined8 uVar158;
  float fVar160;
  float fVar161;
  float fVar162;
  undefined1 auVar159 [16];
  undefined8 uVar163;
  undefined1 auVar164 [16];
  undefined1 auVar165 [16];
  undefined1 auVar166 [16];
  undefined1 auVar167 [16];
  float fVar168;
  undefined8 uVar169;
  undefined1 auVar170 [16];
  undefined1 auVar171 [16];
  undefined1 auVar172 [16];
  undefined1 auVar173 [16];
  undefined1 auVar174 [16];
  undefined1 auVar175 [16];
  undefined1 auVar176 [16];
  undefined1 auVar177 [16];
  undefined1 auVar178 [16];
  float fVar181;
  undefined1 auVar179 [16];
  undefined1 auVar180 [16];
  undefined1 auVar182 [16];
  float fVar183;
  float fVar184;
  float fVar185;
  float fVar186;
  undefined1 auVar187 [16];
  undefined1 auVar188 [16];
  undefined1 auVar189 [16];
  undefined1 auVar190 [16];
  undefined1 auVar191 [16];
  undefined1 auVar192 [16];
  undefined1 auVar193 [16];
  undefined1 auVar194 [16];
  float fVar195;
  undefined1 auVar196 [16];
  undefined1 auVar197 [16];
  undefined1 auVar198 [16];
  undefined1 auVar199 [16];
  undefined1 auVar200 [16];
  float fStack_1008;
  float fStack_ff8;
  float fStack_fe8;
  float fStack_fd8;
  float fStack_fc8;
  float fStack_fb8;
  float fStack_fa8;
  float fStack_f98;
  float fStack_f88;
  float fStack_f84;
  float fStack_f58;
  float fStack_f54;
  undefined8 uStack_f48;
  undefined1 local_f30;
  undefined1 uStack_f2f;
  undefined1 uStack_f2e;
  undefined1 uStack_f2d;
  float fStack_f08;
  float fStack_f04;
  float local_f00;
  float fStack_efc;
  float fStack_ef8;
  float fStack_ef4;
  float fStack_ee8;
  float fStack_ee4;
  float fStack_ed8;
  float fStack_ed4;
  float fStack_ec8;
  float fStack_ec4;
  float fStack_eb8;
  float fStack_eb4;
  undefined1 local_eb0;
  undefined1 uStack_eaf;
  undefined1 uStack_eae;
  undefined1 uStack_ead;
  undefined1 uStack_ea8;
  undefined1 uStack_ea7;
  undefined1 uStack_ea6;
  undefined1 uStack_ea5;
  undefined1 uStack_ea4;
  undefined1 uStack_ea3;
  undefined1 uStack_ea2;
  undefined1 uStack_ea1;
  float fStack_e98;
  float fStack_e94;
  float local_e40;
  float fStack_e3c;
  undefined1 uStack_e38;
  undefined7 uStack_e37;
  undefined8 local_e30;
  undefined *local_e28;
  long *local_e10;
  uint local_e00;
  uint uStack_dfc;
  uint local_df8;
  undefined4 uStack_df4;
  byte local_df0;
  undefined7 uStack_def;
  undefined1 local_de8;
  undefined2 uStack_de7;
  undefined1 uStack_de5;
  undefined4 uStack_de4;
  uint *local_de0;
  uint *local_dd8;
  undefined8 local_dd0;
  undefined4 local_dc8;
  uint *local_dc0;
  uint *local_db8;
  undefined8 local_db0;
  int local_da8;
  uint *local_da0;
  uint *local_d98;
  undefined8 local_d90;
  int local_d88;
  uint *local_d80;
  uint *local_d78;
  undefined8 local_d70;
  int local_d68;
  CachedNintendoAccountInfo aCStack_1ac [108];
  undefined8 local_140;
  undefined8 local_138 [15];
  int local_bc;
  undefined8 local_b8;
  int local_b0;
  undefined4 uStack_ac;
  float fVar119;
  undefined1 auVar121 [12];
  undefined1 auVar137 [16];
  undefined1 auVar138 [16];
  undefined1 auVar139 [16];
  undefined1 auVar143 [12];
  undefined1 auVar149 [16];
  
  nn::oe::Initialize();
  nn::oe::SetPerformanceConfiguration(0,0x20004);
  nn::oe::SetPerformanceConfiguration(1,0x10001);
  DAT_710593a540 = 2;
  nn::oe::SetFocusHandlingMode(2);
  nn::oe::DisableRecording();
  local_e30 = &PTR_LAB_710523c100;
  local_e10 = &local_e30;
  local_e28 = &DAT_7103741700;
  local_de0 = &local_e00;
  FUN_7103747220(&local_e30,&local_e00);
  puVar59 = local_de0;
  if (local_de0 == &local_e00) {
    if (DAT_710593a510 == (uint *)&DAT_710593a4f0) {
      (**(code **)(CONCAT44(uStack_dfc,local_e00) + 0x18))(local_de0,&local_140);
      (**(code **)(*(long *)local_de0 + 0x20))();
      local_de0 = (uint *)0x0;
      (**(code **)(*(long *)DAT_710593a510 + 0x18))(DAT_710593a510,&local_e00);
      (**(code **)(*(long *)DAT_710593a510 + 0x20))();
      DAT_710593a510 = (uint *)0x0;
      local_de0 = &local_e00;
      (**(code **)((long)local_140 + 0x18))(&local_140,&DAT_710593a4f0);
      (**(code **)((long)local_140 + 0x20))(&local_140);
      DAT_710593a510 = (uint *)&DAT_710593a4f0;
    }
    else {
      (**(code **)(CONCAT44(uStack_dfc,local_e00) + 0x18))(local_de0,&DAT_710593a4f0);
      (**(code **)(*(long *)local_de0 + 0x20))();
      local_de0 = DAT_710593a510;
      DAT_710593a510 = (uint *)&DAT_710593a4f0;
    }
  }
  else if (DAT_710593a510 == (uint *)&DAT_710593a4f0) {
    (**(code **)(DAT_710593a4f0 + 0x18))(&DAT_710593a4f0,&local_e00);
    (**(code **)(*(long *)DAT_710593a510 + 0x20))();
    DAT_710593a510 = local_de0;
    local_de0 = &local_e00;
  }
  else {
    local_de0 = DAT_710593a510;
    DAT_710593a510 = puVar59;
  }
  if (&local_e00 == local_de0) {
    pcVar37 = *(code **)(*(long *)local_de0 + 0x20);
LAB_7103741b94:
    (*pcVar37)(local_de0);
  }
  else if (local_de0 != (uint *)0x0) {
    pcVar37 = *(code **)(*(long *)local_de0 + 0x28);
    goto LAB_7103741b94;
  }
  DAT_710593a538 = nn::oe::GetNotificationMessageEvent();
  DAT_710593a534 = nn::oe::GetOperationMode();
  plVar31 = DAT_710593a528;
  pEVar25 = (EventType *)*DAT_710593a528;
  if (pEVar25 == (EventType *)0x0) {
    pEVar25 = (EventType *)je_aligned_alloc(0x10,0x28);
    if (pEVar25 == (EventType *)0x0) {
      if (DAT_7105331f00 != (long *)0x0) {
        local_140 = (uint *)((ulong)local_140 & 0xffffffff00000000);
        local_e00 = 0x28;
        uStack_dfc = 0;
        uVar26 = (**(code **)(*DAT_7105331f00 + 0x30))(DAT_7105331f00,&local_140,&local_e00);
        if (((uVar26 & 1) != 0) &&
           (pEVar25 = (EventType *)je_aligned_alloc(0x10,0x28), pEVar25 != (EventType *)0x0))
        goto LAB_7103741c20;
      }
      pEVar25 = (EventType *)0x0;
    }
LAB_7103741c20:
    nn::os::InitializeEvent(pEVar25,false,0);
    *plVar31 = (long)pEVar25;
    pEVar25 = (EventType *)*DAT_710593a528;
    if (pEVar25 != (EventType *)0x0) goto LAB_7103741c44;
  }
  else {
LAB_7103741c44:
    nn::os::SignalEvent(pEVar25);
  }
  local_e00 = 0x523c360;
  uStack_dfc = 0x71;
  local_df8 = 0x3754940;
  uStack_df4 = 0x71;
  local_df0 = 0;
  uStack_def = 0;
  local_de8 = 0xf0;
  uStack_de7 = 0x93a4;
  uStack_de5 = 5;
  uStack_de4 = 0x71;
  local_de0 = &local_e00;
  FUN_710353d000(&DAT_710593a520,&local_e00,5,0,0,0x40000);
  if (&local_e00 == local_de0) {
    pcVar37 = *(code **)(*(long *)local_de0 + 0x20);
LAB_7103741cb8:
    (*pcVar37)();
  }
  else if (local_de0 != (uint *)0x0) {
    pcVar37 = *(code **)(*(long *)local_de0 + 0x28);
    goto LAB_7103741cb8;
  }
  if (&local_e30 == local_e10) {
    pcVar37 = *(code **)(*local_e10 + 0x20);
LAB_7103741ce4:
    (*pcVar37)();
  }
  else if (local_e10 != (long *)0x0) {
    pcVar37 = *(code **)(*local_e10 + 0x28);
    goto LAB_7103741ce4;
  }
  DAT_710523c00c = FUN_7103741520();
  FUN_710374f360(param_1);
  if (DAT_710523c00c < 0xe) {
    puVar27 = (&PTR_s_jp_ja_710523c010)[(int)DAT_710523c00c];
  }
  else {
    puVar27 = &DAT_71043fee6b;
  }
  FUN_710353e760(puVar27);
  FUN_71035481d0(&DAT_7105332058,2);
  FUN_71035481d0(&DAT_71053320d0,2);
  FUN_71035481d0(&DAT_7105332148,1);
  FUN_71035481d0(&DAT_7105332508,1);
  FUN_71035481d0(&DAT_71053325f8,0);
  puVar28 = DAT_710593a588;
  if (DAT_710593a588 == (undefined8 *)0x0) {
    puVar28 = (undefined8 *)je_aligned_alloc(0x10,8);
    if (puVar28 == (undefined8 *)0x0) {
      if (DAT_7105331f00 != (long *)0x0) {
        local_140 = (uint *)((ulong)local_140 & 0xffffffff00000000);
        local_e00 = 8;
        uStack_dfc = 0;
        uVar26 = (**(code **)(*DAT_7105331f00 + 0x30))(DAT_7105331f00,&local_140,&local_e00);
        if (((uVar26 & 1) != 0) &&
           (puVar28 = (undefined8 *)je_aligned_alloc(0x10,8), puVar28 != (undefined8 *)0x0))
        goto LAB_7103741dd4;
      }
      puVar28 = (undefined8 *)0x0;
    }
LAB_7103741dd4:
    puVar29 = (undefined8 *)je_aligned_alloc(0x10,0x18);
    if (puVar29 == (undefined8 *)0x0) {
      if (DAT_7105331f00 != (long *)0x0) {
        local_140 = (uint *)((ulong)local_140 & 0xffffffff00000000);
        local_e00 = 0x18;
        uStack_dfc = 0;
        uVar26 = (**(code **)(*DAT_7105331f00 + 0x30))(DAT_7105331f00,&local_140,&local_e00);
        if (((uVar26 & 1) != 0) &&
           (puVar29 = (undefined8 *)je_aligned_alloc(0x10,0x18), puVar29 != (undefined8 *)0x0))
        goto LAB_7103741e34;
      }
      puVar29 = (undefined8 *)0x0;
    }
LAB_7103741e34:
    *(undefined1 *)((long)puVar29 + 10) = 0;
    *(undefined2 *)(puVar29 + 1) = 0;
    *puVar29 = 0;
    nn::err::ErrorResultVariant::ErrorResultVariant((ErrorResultVariant *)((long)puVar29 + 0xc));
    *puVar28 = puVar29;
    local_e00 = nn::nifm::Initialize();
    if (local_e00 != 0) {
      nn::err::ErrorResultVariant::operator=
                ((ErrorResultVariant *)((long)puVar29 + 0xc),(Result *)&local_e00);
      *puVar29 = 0;
      *(bool *)((long)puVar29 + 9) = local_e00 == 0;
      *(undefined1 *)((long)puVar29 + 10) = 1;
      *(undefined1 *)(puVar29 + 1) = 1;
    }
  }
  DAT_710593a588 = puVar28;
  puVar28 = DAT_710593a580;
  if (DAT_710593a580 == (undefined8 *)0x0) {
    puVar28 = (undefined8 *)je_aligned_alloc(0x10,8);
    if (puVar28 == (undefined8 *)0x0) {
      if (DAT_7105331f00 != (long *)0x0) {
        local_140 = (uint *)((ulong)local_140 & 0xffffffff00000000);
        local_e00 = 8;
        uStack_dfc = 0;
        uVar26 = (**(code **)(*DAT_7105331f00 + 0x30))(DAT_7105331f00,&local_140,&local_e00);
        if (((uVar26 & 1) != 0) &&
           (puVar28 = (undefined8 *)je_aligned_alloc(0x10,8), puVar28 != (undefined8 *)0x0))
        goto LAB_7103741ef8;
      }
      puVar28 = (undefined8 *)0x0;
    }
LAB_7103741ef8:
    __s = (void *)je_aligned_alloc(0x10,0x7320);
    if (__s == (void *)0x0) {
      if (DAT_7105331f00 != (long *)0x0) {
        local_140 = (uint *)((ulong)local_140 & 0xffffffff00000000);
        local_e00 = 0x7320;
        uStack_dfc = 0;
        uVar26 = (**(code **)(*DAT_7105331f00 + 0x30))(DAT_7105331f00,&local_140,&local_e00);
        if (((uVar26 & 1) != 0) && (__s = (void *)je_aligned_alloc(0x10,0x7320), __s != (void *)0x0)
           ) goto LAB_7103741f58;
      }
      __s = (void *)0x0;
    }
LAB_7103741f58:
    memset(__s,0,0xc54);
    nn::account::CachedNintendoAccountInfo::CachedNintendoAccountInfo
              ((CachedNintendoAccountInfo *)((long)__s + 0xc54));
    *(undefined8 *)((long)__s + 0x72d0) = 0;
    *(undefined1 *)((long)__s + 0x72d8) = 0;
    *(undefined8 *)((long)__s + 0x72c8) = 0;
    *(undefined8 *)((long)__s + 0x72c0) = 0;
    *(int *)((long)__s + 0x7300) = -1;
    *(undefined1 *)((long)__s + 0x730e) = 0;
    *(undefined2 *)((long)__s + 0x730c) = 0;
    *(undefined8 *)((long)__s + 0x7304) = 0;
    nn::err::ErrorResultVariant::ErrorResultVariant((ErrorResultVariant *)((long)__s + 0x7310));
    *puVar28 = __s;
    nn::account::Initialize();
    local_bc = 0;
    nn::account::ListAllUsers(&local_bc,(Uid *)&local_140,8);
    if (0 < local_bc) {
      lVar52 = 0;
      puVar1 = (ulong *)((long)__s + 0x72c0);
      pUVar60 = (Uid *)&local_140;
      do {
        local_df8 = (uint)*(undefined8 *)(pUVar60 + 8);
        uStack_df4 = (undefined4)((ulong)*(undefined8 *)(pUVar60 + 8) >> 0x20);
        local_e00 = (uint)*(undefined8 *)pUVar60;
        uStack_dfc = (uint)((ulong)*(undefined8 *)pUVar60 >> 0x20);
        memset(&local_df0,0,0xc44);
        nn::account::CachedNintendoAccountInfo::CachedNintendoAccountInfo(aCStack_1ac);
        nn::account::GetNickname((Nickname *)&local_dd0,pUVar60);
        if (7 < *puVar1) {
                    /* WARNING: Subroutine does not return */
          abort();
        }
        memcpy((void *)((long)__s + *puVar1 * 0xcc0 + 0xcc0),&local_e00,0xcc0);
        *puVar1 = *puVar1 + 1;
        lVar52 = lVar52 + 1;
        pUVar60 = pUVar60 + 0x10;
      } while (lVar52 < local_bc);
    }
    uVar26 = nn::account::TryOpenPreselectedUser((UserHandle *)&local_e00);
    if (((uVar26 & 1) != 0) &&
       (iVar23 = nn::account::GetUserId((Uid *)&local_b8,(UserHandle *)&local_e00), iVar23 == 0)) {
      lVar52 = *(long *)((long)__s + 0x72c0);
      puVar1 = (ulong *)((long)__s + 0xcc0);
      puVar38 = puVar1;
      if (lVar52 * 0xcc0 == 0) {
LAB_710374210c:
        if (puVar1 + lVar52 * 0x198 != puVar38) {
          *(undefined2 *)((long)puVar38 + 0xc51) = 0x101;
          puVar38[2] = CONCAT44(uStack_dfc,local_e00);
          puVar38[3] = CONCAT44(uStack_df4,local_df8);
          puVar38[4] = CONCAT71(uStack_def,local_df0);
          *(int *)((long)__s + 0x7300) =
               (int)((ulong)((long)puVar38 - (long)puVar1) >> 6) * -0x5050505;
        }
      }
      else {
        lVar49 = lVar52 * 0xcc0;
        do {
          if ((*puVar38 == local_b8) && (puVar38[1] == CONCAT44(uStack_ac,local_b0)))
          goto LAB_710374210c;
          puVar38 = puVar38 + 0x198;
          lVar49 = lVar49 + -0xcc0;
        } while (lVar49 != 0);
      }
    }
  }
  DAT_710593a580 = puVar28;
  puVar28 = DAT_71053388b0;
  if (DAT_71053388b0 == (undefined8 *)0x0) {
    puVar28 = (undefined8 *)je_aligned_alloc(0x10,0x10);
    if (puVar28 == (undefined8 *)0x0) {
      if (DAT_7105331f00 != (long *)0x0) {
        local_140 = (uint *)((ulong)local_140 & 0xffffffff00000000);
        local_e00 = 0x10;
        uStack_dfc = 0;
        uVar26 = (**(code **)(*DAT_7105331f00 + 0x30))(DAT_7105331f00,&local_140,&local_e00);
        if (((uVar26 & 1) != 0) &&
           (puVar28 = (undefined8 *)je_aligned_alloc(0x10,0x10), puVar28 != (undefined8 *)0x0))
        goto LAB_71037421c4;
      }
      puVar28 = (undefined8 *)0x0;
    }
LAB_71037421c4:
    *(undefined1 *)(puVar28 + 1) = 1;
    *puVar28 = &PTR_FUN_7105237f90;
    DAT_7105338860 = &DAT_7105338830;
    DAT_7105338868 = &DAT_7105338830;
    DAT_7105338870 = &DAT_7105338830;
    DAT_7105338878 = &DAT_7105338830;
    DAT_7105338880 = &DAT_7105338830;
    DAT_7105338888 = &DAT_7105338830;
    DAT_7105338890 = &DAT_7105338830;
    DAT_7105338898 = &DAT_7105338830;
    DAT_71053388a0 = &DAT_7105338830;
    DAT_71053388a8 = &DAT_7105338830;
    nn::hid::InitializeNpad();
    local_de0 = (uint *)CONCAT44(local_de0._4_4_,0x20);
    local_e00 = 0;
    uStack_dfc = 1;
    local_df0 = 4;
    uStack_def = 0x5000000;
    local_de8 = 6;
    uStack_de7 = 0;
    uStack_de5 = 0;
    uStack_de4 = 7;
    local_df8 = 2;
    uStack_df4 = 3;
    nn::hid::SetSupportedNpadStyleSet(0x3f);
    nn::hid::SetSupportedNpadIdType(&local_e00,9);
    nn::hid::SetNpadJoyHoldType(1);
    puVar29 = (undefined8 *)je_aligned_alloc(0x10,0x30);
    if (puVar29 == (undefined8 *)0x0) {
      if (DAT_7105331f00 != (long *)0x0) {
        local_140 = (uint *)((ulong)local_140 & 0xffffffff00000000);
        local_e00 = 0x30;
        uStack_dfc = 0;
        uVar26 = (**(code **)(*DAT_7105331f00 + 0x30))(DAT_7105331f00,&local_140,&local_e00);
        if (((uVar26 & 1) != 0) &&
           (puVar29 = (undefined8 *)je_aligned_alloc(0x10,0x30), puVar29 != (undefined8 *)0x0))
        goto LAB_71037422a4;
      }
      puVar29 = (undefined8 *)0x0;
    }
LAB_71037422a4:
    FUN_7103666880(puVar29,0);
    DAT_7105338860 = puVar29;
    puVar29 = (undefined8 *)je_aligned_alloc(0x10,0x30);
    if (puVar29 == (undefined8 *)0x0) {
      if (DAT_7105331f00 != (long *)0x0) {
        local_140 = (uint *)((ulong)local_140 & 0xffffffff00000000);
        local_e00 = 0x30;
        uStack_dfc = 0;
        uVar26 = (**(code **)(*DAT_7105331f00 + 0x30))(DAT_7105331f00,&local_140,&local_e00);
        if (((uVar26 & 1) != 0) &&
           (puVar29 = (undefined8 *)je_aligned_alloc(0x10,0x30), puVar29 != (undefined8 *)0x0))
        goto LAB_7103742318;
      }
      puVar29 = (undefined8 *)0x0;
    }
LAB_7103742318:
    FUN_7103666880(puVar29,1);
    DAT_7105338868 = puVar29;
    puVar29 = (undefined8 *)je_aligned_alloc(0x10,0x30);
    if (puVar29 == (undefined8 *)0x0) {
      if (DAT_7105331f00 != (long *)0x0) {
        local_140 = (uint *)((ulong)local_140 & 0xffffffff00000000);
        local_e00 = 0x30;
        uStack_dfc = 0;
        uVar26 = (**(code **)(*DAT_7105331f00 + 0x30))(DAT_7105331f00,&local_140,&local_e00);
        if (((uVar26 & 1) != 0) &&
           (puVar29 = (undefined8 *)je_aligned_alloc(0x10,0x30), puVar29 != (undefined8 *)0x0))
        goto LAB_710374238c;
      }
      puVar29 = (undefined8 *)0x0;
    }
LAB_710374238c:
    FUN_7103666880(puVar29,2);
    DAT_7105338870 = puVar29;
    puVar29 = (undefined8 *)je_aligned_alloc(0x10,0x30);
    if (puVar29 == (undefined8 *)0x0) {
      if (DAT_7105331f00 != (long *)0x0) {
        local_140 = (uint *)((ulong)local_140 & 0xffffffff00000000);
        local_e00 = 0x30;
        uStack_dfc = 0;
        uVar26 = (**(code **)(*DAT_7105331f00 + 0x30))(DAT_7105331f00,&local_140,&local_e00);
        if (((uVar26 & 1) != 0) &&
           (puVar29 = (undefined8 *)je_aligned_alloc(0x10,0x30), puVar29 != (undefined8 *)0x0))
        goto LAB_7103742400;
      }
      puVar29 = (undefined8 *)0x0;
    }
LAB_7103742400:
    FUN_7103666880(puVar29,3);
    DAT_7105338878 = puVar29;
    puVar29 = (undefined8 *)je_aligned_alloc(0x10,0x30);
    if (puVar29 == (undefined8 *)0x0) {
      if (DAT_7105331f00 != (long *)0x0) {
        local_140 = (uint *)((ulong)local_140 & 0xffffffff00000000);
        local_e00 = 0x30;
        uStack_dfc = 0;
        uVar26 = (**(code **)(*DAT_7105331f00 + 0x30))(DAT_7105331f00,&local_140,&local_e00);
        if (((uVar26 & 1) != 0) &&
           (puVar29 = (undefined8 *)je_aligned_alloc(0x10,0x30), puVar29 != (undefined8 *)0x0))
        goto LAB_7103742474;
      }
      puVar29 = (undefined8 *)0x0;
    }
LAB_7103742474:
    FUN_7103666880(puVar29,4);
    DAT_7105338880 = puVar29;
    puVar29 = (undefined8 *)je_aligned_alloc(0x10,0x30);
    if (puVar29 == (undefined8 *)0x0) {
      if (DAT_7105331f00 != (long *)0x0) {
        local_140 = (uint *)((ulong)local_140 & 0xffffffff00000000);
        local_e00 = 0x30;
        uStack_dfc = 0;
        uVar26 = (**(code **)(*DAT_7105331f00 + 0x30))(DAT_7105331f00,&local_140,&local_e00);
        if (((uVar26 & 1) != 0) &&
           (puVar29 = (undefined8 *)je_aligned_alloc(0x10,0x30), puVar29 != (undefined8 *)0x0))
        goto LAB_71037424e8;
      }
      puVar29 = (undefined8 *)0x0;
    }
LAB_71037424e8:
    FUN_7103666880(puVar29,5);
    DAT_7105338888 = puVar29;
    puVar29 = (undefined8 *)je_aligned_alloc(0x10,0x30);
    if (puVar29 == (undefined8 *)0x0) {
      if (DAT_7105331f00 != (long *)0x0) {
        local_140 = (uint *)((ulong)local_140 & 0xffffffff00000000);
        local_e00 = 0x30;
        uStack_dfc = 0;
        uVar26 = (**(code **)(*DAT_7105331f00 + 0x30))(DAT_7105331f00,&local_140,&local_e00);
        if (((uVar26 & 1) != 0) &&
           (puVar29 = (undefined8 *)je_aligned_alloc(0x10,0x30), puVar29 != (undefined8 *)0x0))
        goto LAB_710374255c;
      }
      puVar29 = (undefined8 *)0x0;
    }
LAB_710374255c:
    FUN_7103666880(puVar29,6);
    DAT_7105338890 = puVar29;
    puVar29 = (undefined8 *)je_aligned_alloc(0x10,0x30);
    if (puVar29 == (undefined8 *)0x0) {
      if (DAT_7105331f00 != (long *)0x0) {
        local_140 = (uint *)((ulong)local_140 & 0xffffffff00000000);
        local_e00 = 0x30;
        uStack_dfc = 0;
        uVar26 = (**(code **)(*DAT_7105331f00 + 0x30))(DAT_7105331f00,&local_140,&local_e00);
        if (((uVar26 & 1) != 0) &&
           (puVar29 = (undefined8 *)je_aligned_alloc(0x10,0x30), puVar29 != (undefined8 *)0x0))
        goto LAB_71037425d0;
      }
      puVar29 = (undefined8 *)0x0;
    }
LAB_71037425d0:
    FUN_7103666880(puVar29,7);
    DAT_7105338898 = puVar29;
    puVar29 = (undefined8 *)je_aligned_alloc(0x10,0x30);
    if (puVar29 == (undefined8 *)0x0) {
      if (DAT_7105331f00 != (long *)0x0) {
        local_140 = (uint *)((ulong)local_140 & 0xffffffff00000000);
        local_e00 = 0x30;
        uStack_dfc = 0;
        uVar26 = (**(code **)(*DAT_7105331f00 + 0x30))(DAT_7105331f00,&local_140,&local_e00);
        if (((uVar26 & 1) != 0) &&
           (puVar29 = (undefined8 *)je_aligned_alloc(0x10,0x30), puVar29 != (undefined8 *)0x0))
        goto LAB_7103742644;
      }
      puVar29 = (undefined8 *)0x0;
    }
LAB_7103742644:
    puVar29[2] = &DAT_71053386f0;
    puVar29[3] = &DAT_71053387c0;
    puVar29[4] = &DAT_71053387d0;
    puVar29[5] = &DAT_71053387f8;
    *puVar29 = &PTR_FUN_7105237fb0;
    puVar29[1] = 8;
    puVar30 = (undefined8 *)je_aligned_alloc(0x10,0xd0);
    if (puVar30 == (undefined8 *)0x0) {
      if (DAT_7105331f00 != (long *)0x0) {
        local_140 = (uint *)((ulong)local_140 & 0xffffffff00000000);
        local_e00 = 0xd0;
        uStack_dfc = 0;
        uVar26 = (**(code **)(*DAT_7105331f00 + 0x30))(DAT_7105331f00,&local_140,&local_e00);
        if (((uVar26 & 1) != 0) &&
           (puVar30 = (undefined8 *)je_aligned_alloc(0x10,0xd0), puVar30 != (undefined8 *)0x0))
        goto LAB_71037426dc;
      }
      puVar30 = (undefined8 *)0x0;
    }
LAB_71037426dc:
    puVar30[1] = 0;
    puVar30[0x10] = 0;
    puVar30[0x11] = 0;
    *(undefined4 *)((long)puVar30 + 0xb4) = 0;
    *(undefined8 *)((long)puVar30 + 0x94) = 0x500000012c;
    *(undefined4 *)(puVar30 + 0x12) = 0;
    *(undefined2 *)(puVar30 + 0x17) = 0x100;
    *(undefined1 *)(puVar30 + 0x18) = 0;
    *(undefined2 *)((long)puVar30 + 0xbe) = 0;
    *(undefined4 *)((long)puVar30 + 0xba) = 0;
    puVar30[0xe] = 0;
    puVar30[0xf] = 0;
    puVar30[0xc] = 0;
    puVar30[0xd] = 0;
    puVar30[10] = 0;
    puVar30[0xb] = 0;
    puVar30[8] = 0;
    puVar30[9] = 0;
    puVar30[6] = 0;
    puVar30[7] = 0;
    puVar30[4] = 0;
    puVar30[5] = 0;
    puVar30[2] = 0;
    puVar30[3] = 0;
    auVar134 = _ConstantZero;
    *puVar30 = &PTR_LAB_7105238008;
    *(undefined8 *)((long)puVar30 + 0x9c) = 0x800000001;
    uVar63 = auVar134._8_8_;
    puVar30[7] = uVar63;
    uVar33 = auVar134._0_8_;
    puVar30[6] = uVar33;
    puVar30[3] = uVar63;
    puVar30[2] = uVar33;
    puVar30[5] = uVar63;
    puVar30[4] = uVar33;
    plVar31 = (long *)puVar29[2];
    if (plVar31 != &DAT_71053386f0) {
      if (plVar31 != (long *)0x0) {
        (**(code **)(*plVar31 + 8))();
      }
      puVar29[2] = &DAT_71053386f0;
    }
    if (puVar30 != (undefined8 *)0x0) {
      puVar29[2] = puVar30;
    }
    puVar30 = (undefined8 *)je_aligned_alloc(0x10,0x30);
    if (puVar30 == (undefined8 *)0x0) {
      if (DAT_7105331f00 != (long *)0x0) {
        local_140 = (uint *)((ulong)local_140 & 0xffffffff00000000);
        local_e00 = 0x30;
        uStack_dfc = 0;
        uVar26 = (**(code **)(*DAT_7105331f00 + 0x30))(DAT_7105331f00,&local_140,&local_e00);
        if (((uVar26 & 1) != 0) &&
           (puVar30 = (undefined8 *)je_aligned_alloc(0x10,0x30), puVar30 != (undefined8 *)0x0))
        goto LAB_71037427dc;
      }
      puVar30 = (undefined8 *)0x0;
    }
LAB_71037427dc:
    *(undefined2 *)(puVar30 + 1) = 0x100;
    *puVar30 = &PTR_LAB_7105238110;
    puVar59 = (uint *)((long)puVar30 + 0xc);
    *puVar59 = 0x20;
    *(undefined8 *)((long)puVar30 + 0x24) = 0x43200000;
    *(undefined4 *)(puVar30 + 4) = 0;
    *(undefined4 *)((long)puVar30 + 0x2c) = 0x43a00000;
    puVar30[2] = 0;
    puVar30[3] = 0;
    BVar24 = nn::hid::GetNpadStyleSet(puVar59);
    *(BitFlagSet *)(puVar30 + 2) = BVar24;
    if (BVar24 == 0) {
      *(undefined1 *)(puVar30 + 1) = 0;
      *(undefined8 *)((long)puVar30 + 0x14) = 0;
      *(undefined4 *)((long)puVar30 + 0x1c) = 0;
    }
    else {
      pVVar56 = (VibrationDeviceHandle *)(puVar30 + 3);
      *(undefined1 *)(puVar30 + 1) = 1;
      iVar23 = nn::hid::GetVibrationDeviceHandles(pVVar56,2,puVar59,BVar24);
      *(int *)((long)puVar30 + 0x14) = iVar23;
      if (0 < iVar23) {
        lVar52 = 0;
        do {
          nn::hid::InitializeVibrationDevice(pVVar56);
          lVar52 = lVar52 + 1;
          pVVar56 = pVVar56 + 4;
        } while (lVar52 < *(int *)((long)puVar30 + 0x14));
      }
    }
    plVar31 = (long *)puVar29[3];
    if (plVar31 != &DAT_71053387c0) {
      if (plVar31 != (long *)0x0) {
        (**(code **)(*plVar31 + 8))();
      }
      puVar29[3] = &DAT_71053387c0;
    }
    puVar29[3] = puVar30;
    puVar30 = (undefined8 *)je_aligned_alloc(0x10,0x2b8);
    if (puVar30 == (undefined8 *)0x0) {
      if (DAT_7105331f00 != (long *)0x0) {
        local_140 = (uint *)((ulong)local_140 & 0xffffffff00000000);
        local_e00 = 0x2b8;
        uStack_dfc = 0;
        uVar26 = (**(code **)(*DAT_7105331f00 + 0x30))(DAT_7105331f00,&local_140,&local_e00);
        if (((uVar26 & 1) != 0) &&
           (puVar30 = (undefined8 *)je_aligned_alloc(0x10,0x2b8), puVar30 != (undefined8 *)0x0))
        goto LAB_7103742904;
      }
      puVar30 = (undefined8 *)0x0;
    }
LAB_7103742904:
    *(undefined1 *)(puVar30 + 4) = 0;
    puVar30[2] = 0;
    puVar30[3] = 0;
    *puVar30 = &PTR_LAB_7105238050;
    puVar30[1] = 0;
    memset(puVar30 + 5,0,0x290);
    nn::hid::InitializeTouchScreen();
    plVar31 = (long *)puVar29[4];
    if (plVar31 != &DAT_71053387d0) {
      if (plVar31 != (long *)0x0) {
        (**(code **)(*plVar31 + 8))();
      }
      puVar29[4] = &DAT_71053387d0;
    }
    if (puVar30 != (undefined8 *)0x0) {
      puVar29[4] = puVar30;
    }
    puVar30 = (undefined8 *)je_aligned_alloc(0x10,0x340);
    if (puVar30 == (undefined8 *)0x0) {
      if (DAT_7105331f00 != (long *)0x0) {
        local_140 = (uint *)((ulong)local_140 & 0xffffffff00000000);
        local_e00 = 0x340;
        uStack_dfc = 0;
        uVar26 = (**(code **)(*DAT_7105331f00 + 0x30))(DAT_7105331f00,&local_140,&local_e00);
        if (((uVar26 & 1) != 0) &&
           (puVar30 = (undefined8 *)je_aligned_alloc(0x10,0x340), puVar30 != (undefined8 *)0x0))
        goto LAB_71037429b4;
      }
      puVar30 = (undefined8 *)0x0;
    }
LAB_71037429b4:
    *(undefined1 *)(puVar30 + 1) = 0;
    *puVar30 = &PTR_LAB_71052380b0;
    piVar54 = (int *)((long)puVar30 + 0x14);
    puVar59 = (uint *)((long)puVar30 + 0xc);
    *puVar59 = 0x20;
    memset(puVar30 + 2,0,0x330);
    BVar24 = nn::hid::GetNpadStyleSet(puVar59);
    *(BitFlagSet *)(puVar30 + 2) = BVar24;
    if (BVar24 == 0) {
      *(undefined1 *)(puVar30 + 1) = 0;
      *(undefined4 *)((long)puVar30 + 0x34) = 0;
      *(undefined8 *)((long)puVar30 + 0x24) = 0;
      *(undefined8 *)((long)puVar30 + 0x2c) = 0;
      piVar54[0] = 0;
      piVar54[1] = 0;
      *(undefined8 *)((long)puVar30 + 0x1c) = 0;
    }
    else {
      pSVar57 = (SixAxisSensorHandle *)(puVar30 + 3);
      *(undefined1 *)(puVar30 + 1) = 1;
      iVar23 = nn::hid::GetSixAxisSensorHandles(pSVar57,8,puVar59,BVar24);
      *(int *)((long)puVar30 + 0x14) = iVar23;
      if (0 < iVar23) {
        lVar52 = 0;
        do {
          nn::hid::StartSixAxisSensor(pSVar57);
          lVar52 = lVar52 + 1;
          pSVar57 = pSVar57 + 4;
        } while (lVar52 < *piVar54);
      }
    }
    plVar31 = (long *)puVar29[5];
    if (plVar31 != &DAT_71053387f8) {
      if (plVar31 != (long *)0x0) {
        (**(code **)(*plVar31 + 8))();
      }
      puVar29[5] = &DAT_71053387f8;
    }
    puVar29[5] = puVar30;
    DAT_71053388a0 = puVar29;
    if (DAT_71053388b8 == (long *)0x0) {
      plVar31 = (long *)je_aligned_alloc(0x10,8);
      if (plVar31 == (long *)0x0) {
        if (DAT_7105331f00 != (long *)0x0) {
          local_140 = (uint *)((ulong)local_140 & 0xffffffff00000000);
          local_e00 = 8;
          uStack_dfc = 0;
          uVar26 = (**(code **)(*DAT_7105331f00 + 0x30))(DAT_7105331f00,&local_140,&local_e00);
          if (((uVar26 & 1) != 0) &&
             (plVar31 = (long *)je_aligned_alloc(0x10,8), plVar31 != (long *)0x0))
          goto LAB_7103742aec;
        }
        plVar31 = (long *)0x0;
      }
LAB_7103742aec:
      lVar52 = je_aligned_alloc(0x10,0x80);
      if (lVar52 == 0) {
        if (DAT_7105331f00 != (long *)0x0) {
          local_140 = (uint *)((ulong)local_140 & 0xffffffff00000000);
          local_e00 = 0x80;
          uStack_dfc = 0;
          uVar26 = (**(code **)(*DAT_7105331f00 + 0x30))(DAT_7105331f00,&local_140,&local_e00);
          if (((uVar26 & 1) != 0) && (lVar52 = je_aligned_alloc(0x10,0x80), lVar52 != 0))
          goto LAB_7103742b4c;
        }
        lVar52 = 0;
      }
LAB_7103742b4c:
      *(long *)lVar52 = lVar52;
      *(long *)(lVar52 + 8) = lVar52;
      *(undefined8 *)(lVar52 + 0x70) = 0;
      *(undefined8 *)(lVar52 + 0x78) = 0;
      *(undefined8 *)(lVar52 + 0x60) = 0;
      *(undefined8 *)(lVar52 + 0x68) = 0;
      *(undefined2 *)(lVar52 + 0x60) = 1;
      *(undefined1 *)(lVar52 + 0x62) = 0;
      *(undefined8 *)(lVar52 + 0x50) = 0;
      *(undefined8 *)(lVar52 + 0x58) = 0;
      *(undefined8 *)(lVar52 + 0x40) = 0;
      *(undefined8 *)(lVar52 + 0x48) = 0;
      *(undefined8 *)(lVar52 + 0x30) = 0;
      *(undefined8 *)(lVar52 + 0x38) = 0;
      *(undefined8 *)(lVar52 + 0x20) = 0;
      *(undefined8 *)(lVar52 + 0x28) = 0;
      *(undefined8 *)(lVar52 + 0x10) = 0;
      *(undefined8 *)(lVar52 + 0x18) = 0;
      nn::hid::InitializeTouchScreen();
      *plVar31 = lVar52;
      DAT_71053388b8 = plVar31;
    }
    if (DAT_71053388e0 == 0) {
      lVar52 = je_aligned_alloc(0x10,0x10);
      if (lVar52 == 0) {
        if (DAT_7105331f00 != (long *)0x0) {
          local_140 = (uint *)((ulong)local_140 & 0xffffffff00000000);
          local_e00 = 0x10;
          uStack_dfc = 0;
          uVar26 = (**(code **)(*DAT_7105331f00 + 0x30))(DAT_7105331f00,&local_140,&local_e00);
          if (((uVar26 & 1) != 0) && (lVar52 = je_aligned_alloc(0x10,0x10), lVar52 != 0))
          goto LAB_7103742bf0;
        }
        lVar52 = 0;
      }
LAB_7103742bf0:
      FUN_710366ca30(lVar52);
      DAT_71053388e0 = lVar52;
    }
  }
  DAT_71053388b0 = puVar28;
  if (DAT_710593a040 == (undefined8 *)0x0) {
    puVar28 = (undefined8 *)je_aligned_alloc(0x10,8);
    if (puVar28 == (undefined8 *)0x0) {
      if (DAT_7105331f00 != (long *)0x0) {
        local_140 = (uint *)((ulong)local_140 & 0xffffffff00000000);
        local_e00 = 8;
        uStack_dfc = 0;
        uVar26 = (**(code **)(*DAT_7105331f00 + 0x30))(DAT_7105331f00,&local_140,&local_e00);
        if (((uVar26 & 1) != 0) &&
           (puVar28 = (undefined8 *)je_aligned_alloc(0x10,8), puVar28 != (undefined8 *)0x0))
        goto LAB_7103742c6c;
      }
      puVar28 = (undefined8 *)0x0;
    }
LAB_7103742c6c:
    puVar29 = (undefined8 *)je_aligned_alloc(0x10,0xb0);
    if (puVar29 == (undefined8 *)0x0) {
      if (DAT_7105331f00 != (long *)0x0) {
        local_140 = (uint *)((ulong)local_140 & 0xffffffff00000000);
        local_e00 = 0xb0;
        uStack_dfc = 0;
        uVar26 = (**(code **)(*DAT_7105331f00 + 0x30))(DAT_7105331f00,&local_140,&local_e00);
        if (((uVar26 & 1) != 0) &&
           (puVar29 = (undefined8 *)je_aligned_alloc(0x10,0xb0), puVar29 != (undefined8 *)0x0))
        goto LAB_7103742cc4;
      }
      puVar29 = (undefined8 *)0x0;
    }
LAB_7103742cc4:
    puVar29[0xc] = 0;
    *(undefined1 *)((long)puVar29 + 0x74) = 0;
    puVar29[1] = 0;
    puVar29[2] = 0;
    *puVar29 = 0;
    *(undefined4 *)((long)puVar29 + 0x14) = 1;
    *(undefined4 *)(puVar29 + 0x10) = 0;
    *(undefined8 *)((long)puVar29 + 0x84) = 0;
    puVar29[0x12] = 0;
    puVar29[0x13] = 0;
    puVar29[0x14] = 0;
    *puVar28 = puVar29;
    DAT_710593a040 = puVar28;
  }
  nn::prepo::Initialize();
  puVar38 = *(ulong **)(**(long **)(DAT_7105331f20 + 0x78) + 0x70);
  uVar2 = *(uint *)(*(long *)(**(long **)(DAT_7105331f20 + 0x78) + 0x40) + 0xc);
  uVar26 = (ulong)uVar2;
  puVar1 = puVar38 + uVar26;
  puVar39 = puVar38;
  if (uVar2 != 0) {
    do {
      uVar45 = uVar26;
      if ((long)uVar26 < 0) {
        uVar45 = uVar26 + 1;
      }
      uVar45 = (long)uVar45 >> 1;
      puVar38 = puVar39 + uVar45 + 1;
      uVar26 = uVar26 + ~uVar45;
      if (0x112cb2a93d < (puVar39[uVar45] & 0xfffffffffe)) {
        puVar38 = puVar39;
        uVar26 = uVar45;
      }
      puVar39 = puVar38;
    } while (uVar26 != 0);
  }
  if ((puVar38 == puVar1) || ((*puVar38 & 0xffffffffff) != 0x112cb2a93e)) {
    uVar26 = 0xffffff;
  }
  else {
    uVar26 = *puVar38 >> 0x28;
  }
  puVar32 = (uint *)FUN_71035407a0(DAT_7105331f20,uVar26);
  lVar52 = DAT_7105331f20;
  puVar59 = (uint *)&UNK_7104470f50;
  if (puVar32 != (uint *)0x0) {
    puVar59 = puVar32;
  }
  uVar2 = *puVar59;
  uVar26 = (ulong)uVar2;
  if ((uVar2 != 0xffffff) && (uVar2 < *(uint *)(DAT_7105331f20 + 0x48))) {
    std::__1::recursive_mutex::lock();
    lVar52 = *(long *)(lVar52 + 0x40) + uVar26 * 0x48;
    bVar118 = *(byte *)(lVar52 + 8);
    std::__1::recursive_mutex::unlock();
    if (((bVar118 & 1) != 0) && (lVar52 != 0)) {
      FUN_71035427e0(lVar52,2);
    }
  }
  uVar3 = DAT_710593a4bc;
  puVar38 = *(ulong **)(**(long **)(DAT_7105331f20 + 0x78) + 0x70);
  uVar36 = *(uint *)(*(long *)(**(long **)(DAT_7105331f20 + 0x78) + 0x40) + 0xc);
  uVar45 = (ulong)uVar36;
  uVar58 = (ulong)DAT_710593a4bc;
  puVar1 = puVar38 + uVar45;
  puVar39 = puVar38;
  if (uVar36 != 0) {
    do {
      uVar46 = uVar45;
      if ((long)uVar45 < 0) {
        uVar46 = uVar45 + 1;
      }
      uVar46 = (long)uVar46 >> 1;
      puVar38 = puVar39 + uVar46 + 1;
      uVar45 = uVar45 + ~uVar46;
      if (0x151f417268 < (puVar39[uVar46] & 0xffffffffff)) {
        puVar38 = puVar39;
        uVar45 = uVar46;
      }
      puVar39 = puVar38;
    } while (uVar45 != 0);
  }
  if ((puVar38 == puVar1) || ((*puVar38 & 0xffffffffff) != 0x151f417269)) {
    uVar45 = 0xffffff;
  }
  else {
    uVar45 = *puVar38 >> 0x28;
  }
  puVar32 = (uint *)FUN_71035407a0(DAT_7105331f20,uVar45);
  lVar52 = DAT_7105331f20;
  puVar59 = (uint *)&UNK_7104470f50;
  if (puVar32 != (uint *)0x0) {
    puVar59 = puVar32;
  }
  DAT_710593a4bc = *puVar59;
  if ((uVar3 != 0xffffff) && (uVar3 < *(uint *)(DAT_7105331f20 + 0x48))) {
    std::__1::recursive_mutex::lock();
    lVar49 = *(long *)(lVar52 + 0x40);
    if ((*(byte *)(lVar49 + uVar58 * 0x48 + 8) & 1) != 0) {
      FUN_710353eff0(lVar52,lVar49 + uVar58 * 0x48);
    }
    std::__1::recursive_mutex::unlock();
  }
  uVar36 = DAT_710593a4bc;
  lVar52 = DAT_7105331f20;
  if ((DAT_710593a4bc != 0xffffff) && (DAT_710593a4bc < *(uint *)(DAT_7105331f20 + 0x48))) {
    std::__1::recursive_mutex::lock();
    lVar52 = *(long *)(lVar52 + 0x40) + (ulong)uVar36 * 0x48;
    bVar118 = *(byte *)(lVar52 + 8);
    std::__1::recursive_mutex::unlock();
    if (((bVar118 & 1) != 0) && (lVar52 != 0)) {
      FUN_71035427e0(lVar52,2);
    }
  }
  if (uVar2 != 0xffffff) goto LAB_7103742f54;
  do {
    do {
      do {
        do {
          do {
            nn::os::SleepThread(16000000);
          } while (uVar2 == 0xffffff);
LAB_7103742f54:
          lVar52 = DAT_7105331f20;
        } while (*(uint *)(DAT_7105331f20 + 0x48) <= uVar2);
        std::__1::recursive_mutex::lock();
        piVar54 = (int *)(*(long *)(lVar52 + 0x40) + uVar26 * 0x48);
        bVar118 = *(byte *)(piVar54 + 2);
        std::__1::recursive_mutex::unlock();
      } while ((((((bVar118 & 1) == 0) || (piVar54 == (int *)0x0)) || (*piVar54 == 0xffffff)) ||
               ((iVar23 = FUN_7103542ad0(piVar54), lVar52 = DAT_7105331f20, iVar23 != 3 ||
                (uVar45 = (ulong)DAT_710593a4bc, DAT_710593a4bc == 0xffffff)))) ||
              (*(uint *)(DAT_7105331f20 + 0x48) <= DAT_710593a4bc));
      std::__1::recursive_mutex::lock();
      piVar54 = (int *)(*(long *)(lVar52 + 0x40) + uVar45 * 0x48);
      bVar118 = *(byte *)(piVar54 + 2);
      std::__1::recursive_mutex::unlock();
    } while ((((bVar118 & 1) == 0) || (piVar54 == (int *)0x0)) || (*piVar54 == 0xffffff));
    iVar23 = FUN_7103542ad0(piVar54);
  } while (iVar23 != 3);
  if (DAT_7105335e08 == (undefined8 *)0x0) {
    puVar28 = (undefined8 *)je_aligned_alloc(0x10,&DAT_00003378);
    if (puVar28 == (undefined8 *)0x0) {
      if (DAT_7105331f00 != (long *)0x0) {
        local_140 = (uint *)((ulong)local_140 & 0xffffffff00000000);
        local_e00 = 0x3378;
        uStack_dfc = 0;
        uVar45 = (**(code **)(*DAT_7105331f00 + 0x30))(DAT_7105331f00,&local_140,&local_e00);
        if (((uVar45 & 1) != 0) &&
           (puVar28 = (undefined8 *)je_aligned_alloc(0x10,&DAT_00003378),
           puVar28 != (undefined8 *)0x0)) goto LAB_7103743074;
      }
      puVar28 = (undefined8 *)0x0;
    }
LAB_7103743074:
    FUN_710003a5f0(puVar28);
    FUN_71000338f0(puVar28 + 0x603);
    puVar28[0x63e] = 0;
    puVar28[0x63d] = 0;
    puVar28[0x63c] = 0;
    puVar28[0x63b] = 0;
    puVar28[0x63a] = 0;
    puVar28[0x639] = 0;
    puVar28[0x638] = 0;
    puVar28[0x637] = 0;
    puVar28[0x636] = 0;
    puVar28[0x635] = 0;
    puVar28[0x634] = 0;
    puVar28[0x633] = 0;
    puVar28[0x632] = 0;
    puVar28[0x631] = 0;
    puVar28[0x630] = 0;
    puVar28[0x62f] = 0;
    puVar28[0x62e] = 0;
    puVar28[0x62d] = 0;
    puVar28[0x62c] = 0;
    puVar28[0x62b] = 0;
    puVar28[0x62a] = 0;
    puVar28[0x629] = 0;
    puVar28[0x628] = 0;
    puVar28[0x627] = 0;
    FUN_71000336b0(puVar28 + 0x627);
    FUN_71000336b0(puVar28 + 0x62f);
    FUN_71000336b0(puVar28 + 0x637);
    memset(puVar28 + 0x63f,0,0x108);
    FUN_710003a9c0(puVar28 + 0x63f);
    FUN_710003a9c0(puVar28 + 0x64a);
    FUN_710003a9c0(puVar28 + 0x655);
    puVar28[0x660] = 0;
    *(undefined2 *)(puVar28 + 0x660) = 1;
    puVar28[0x663] = 0;
    puVar28[0x662] = 0;
    puVar28[0x661] = 0;
    *(undefined1 *)((long)puVar28 + 0x3302) = 0;
    puVar28[0x664] = 0;
    *(undefined2 *)(puVar28 + 0x664) = 1;
    puVar28[0x667] = 0;
    puVar28[0x666] = 0;
    puVar28[0x665] = 0;
    *(undefined1 *)((long)puVar28 + 0x3322) = 0;
    puVar28[0x668] = 0;
    puVar28[0x66b] = 0;
    *(undefined2 *)(puVar28 + 0x668) = 1;
    puVar28[0x66a] = 0;
    puVar28[0x669] = 0;
    *(undefined1 *)((long)puVar28 + 0x3342) = 0;
    puVar28[0x66e] = 0;
    puVar28[0x66d] = 0;
    puVar28[0x66c] = 0;
    DAT_7105335e08 = puVar28;
  }
  puVar28 = DAT_7105335e08;
  if (((DAT_7105334e18 & 1) == 0) && (iVar23 = __cxa_guard_acquire(&DAT_7105334e18), iVar23 != 0)) {
    FUN_71037c34c0(&DAT_7105334b90);
    DAT_7105334bc5._3_5_ = 0;
    DAT_7105334bb8 = 0;
    _DAT_7105334bc0 = 0;
    DAT_7105334bc5._0_3_ = 0;
    DAT_7105334b90 = &PTR_FUN_7105264b08;
    DAT_7105334ba8 = 0;
    DAT_7105334bb0 = 0;
    std::__1::recursive_mutex::recursive_mutex((recursive_mutex *)&DAT_7105334bd0);
    DAT_7105334b90 = &PTR_FUN_7105264b48;
    DAT_7105334bf0 = &PTR_DAT_7105264b98;
    DAT_7105334bf8 = 0;
    DAT_7105334c38 = 0;
    DAT_7105334c40 = 0;
    DAT_7105334c48 = 0;
    DAT_7105334c30 = 1;
    DAT_7105334c50 = 0x20000;
    DAT_7105334c20 = 0;
    DAT_7105334c28 = 0;
    DAT_7105334c10 = 0;
    DAT_7105334c18 = 0;
    DAT_7105334c00 = 0;
    DAT_7105334c08 = 0;
    DAT_7105334c88 = 0;
    DAT_7105334c90 = 0;
    DAT_7105334c78 = 0;
    DAT_7105334c80 = 0;
    DAT_7105334c68 = 0;
    DAT_7105334c70 = 0;
    DAT_7105334c58 = 0;
    DAT_7105334c60 = 0;
    FUN_71000001c0(FUN_71037fad70,&DAT_7105334b90,&PTR_LOOP_7104f16000);
    __cxa_guard_release(&DAT_7105334e18);
  }
  uVar33 = DAT_7105334bf8;
  FUN_710003a5e0();
  FUN_7100031440(puVar28,uVar33);
  local_de8 = 0;
  uStack_de7 = 0;
  uStack_de5 = 0;
  uStack_de4 = 0;
  local_df0 = 0;
  uStack_def = 0;
  local_df8 = 0;
  uStack_df4 = 0;
  local_e00 = 0;
  uStack_dfc = 0;
  FUN_71000310a0(&local_e00);
  local_e00 = 0x22;
  uVar33 = FUN_71000338d0(puVar28,&local_e00);
  lVar52 = je_aligned_alloc(uVar33,0x1800000);
  if (lVar52 == 0) {
    if (DAT_7105331f00 != (long *)0x0) {
      local_b8 = local_b8 & 0xffffffff00000000;
      local_140 = (uint *)0x1800000;
      uVar45 = (**(code **)(*DAT_7105331f00 + 0x30))(DAT_7105331f00,&local_b8,&local_140);
      if (((uVar45 & 1) != 0) && (lVar52 = je_aligned_alloc(uVar33,0x1800000), lVar52 != 0))
      goto LAB_710374326c;
    }
    lVar52 = 0;
  }
LAB_710374326c:
  iVar23 = FUN_71000338e0(puVar28,&local_e00);
  uStack_dfc = -iVar23 & 0x1800000;
  puVar29 = puVar28 + 0x603;
  local_df8 = (uint)lVar52;
  uStack_df4 = (undefined4)((ulong)lVar52 >> 0x20);
  FUN_7100033920(puVar29,puVar28,&local_e00);
  puVar28[0x626] = lVar52;
  local_b0 = 0;
  local_b8 = 0;
  (*DAT_71052a9348)(*puVar28,0x11,(ulong)&local_b8 | 4);
  (*DAT_71052a9348)(*puVar28,0x12,&local_b0);
  local_138[2] = 0;
  local_138[1] = 0;
  local_138[0] = 0;
  local_140 = (uint *)0x0;
  FUN_7100031090(&local_140);
  local_140._0_4_ = (uint)local_140 & 0xffffff00;
  local_140 = (uint *)CONCAT44(0x1000,(uint)local_140);
  lVar52 = FUN_7100033510(puVar28,&local_140);
  lVar49 = FUN_7100033600(puVar28,&local_140);
  uVar45 = (lVar52 + lVar49) - 1U & -lVar49;
  FUN_71000336d0(puVar28 + 0x627,puVar28,&local_140,puVar29,0,uVar45);
  FUN_710003aa00(puVar28 + 0x63f,&LAB_71035b8d20,lVar49,&LAB_71035b8da0,0,puVar28 + 0x627,
                 local_b8 & 0xffffffff,0x1000 - (int)local_b8,1);
  FUN_7100031090(&local_140);
  local_140 = (uint *)CONCAT71(local_140._1_7_,1);
  local_140 = (uint *)CONCAT44(0x1000,(uint)local_140);
  lVar52 = FUN_7100033510(puVar28,&local_140);
  lVar49 = FUN_7100033600(puVar28,&local_140);
  uVar58 = (lVar52 + lVar49) - 1U & -lVar49;
  FUN_71000336d0(puVar28 + 0x62f,puVar28,&local_140,puVar29,uVar45,uVar58);
  FUN_710003aa00(puVar28 + 0x64a,&LAB_71035b8d20,lVar49,&LAB_71035b8da0,0,puVar28 + 0x62f,
                 local_b8._4_4_,0x1000 - local_b8._4_4_,1);
  FUN_7100031090(&local_140);
  local_140 = (uint *)CONCAT71(local_140._1_7_,2);
  local_140 = (uint *)CONCAT44(0x1000,(uint)local_140);
  lVar52 = FUN_7100033510(puVar28,&local_140);
  lVar49 = FUN_7100033600(puVar28,&local_140);
  FUN_71000336d0(puVar28 + 0x637,puVar28,&local_140,puVar29,uVar58 + uVar45,
                 (lVar52 + lVar49) - 1U & -lVar49);
  FUN_710003aa00(puVar28 + 0x655,&LAB_71035b8d20,lVar49,&LAB_71035b8da0,0,puVar28 + 0x637,local_b0,
                 0x1000 - local_b0,1);
  lVar52 = je_aligned_alloc(0x10,8);
  if (lVar52 == 0) {
    if (DAT_7105331f00 != (long *)0x0) {
      local_140 = (uint *)((ulong)local_140 & 0xffffffff00000000);
      local_e00 = 8;
      uStack_dfc = 0;
      uVar45 = (**(code **)(*DAT_7105331f00 + 0x30))(DAT_7105331f00,&local_140,&local_e00);
      if (((uVar45 & 1) != 0) && (lVar52 = je_aligned_alloc(0x10,8), lVar52 != 0))
      goto LAB_7103743568;
    }
    lVar52 = 0;
  }
LAB_7103743568:
  local_e00 = 0x8200000;
  uStack_dfc = 0;
  local_df8 = 0x22;
  FUN_710363e870(lVar52,&local_e00);
  lVar49 = puVar28[0x66c];
  puVar28[0x66c] = lVar52;
  if (lVar49 != 0) {
    FUN_710363e950(lVar49);
    FUN_710392e590(lVar49);
  }
  lVar52 = je_aligned_alloc(0x10,8);
  if (lVar52 == 0) {
    if (DAT_7105331f00 != (long *)0x0) {
      local_140 = (uint *)((ulong)local_140 & 0xffffffff00000000);
      local_e00 = 8;
      uStack_dfc = 0;
      uVar45 = (**(code **)(*DAT_7105331f00 + 0x30))(DAT_7105331f00,&local_140,&local_e00);
      if (((uVar45 & 1) != 0) && (lVar52 = je_aligned_alloc(0x10,8), lVar52 != 0))
      goto LAB_7103743600;
    }
    lVar52 = 0;
  }
LAB_7103743600:
  local_e00 = 0x1200000;
  uStack_dfc = 0;
  local_df8 = 0x12;
  FUN_710363e870(lVar52,&local_e00);
  lVar49 = puVar28[0x66d];
  puVar28[0x66d] = lVar52;
  if (lVar49 != 0) {
    FUN_710363e950(lVar49);
    FUN_710392e590(lVar49);
  }
  lVar52 = je_aligned_alloc(0x10,8);
  if (lVar52 == 0) {
    if (DAT_7105331f00 != (long *)0x0) {
      local_140 = (uint *)((ulong)local_140 & 0xffffffff00000000);
      local_e00 = 8;
      uStack_dfc = 0;
      uVar45 = (**(code **)(*DAT_7105331f00 + 0x30))(DAT_7105331f00,&local_140,&local_e00);
      if (((uVar45 & 1) != 0) && (lVar52 = je_aligned_alloc(0x10,8), lVar52 != 0))
      goto LAB_7103743698;
    }
    lVar52 = 0;
  }
LAB_7103743698:
  local_e00 = 0x180000;
  uStack_dfc = 0;
  FUN_710363e150(lVar52,&local_e00);
  lVar49 = puVar28[0x66e];
  puVar28[0x66e] = lVar52;
  if (lVar49 != 0) {
    FUN_710363e230(lVar49);
    FUN_710392e590(lVar49);
  }
  if (DAT_7105334480 == (undefined8 *)0x0) {
    puVar28 = (undefined8 *)je_aligned_alloc(0x10,0x740);
    if (puVar28 == (undefined8 *)0x0) {
      if (DAT_7105331f00 != (long *)0x0) {
        local_140 = (uint *)((ulong)local_140 & 0xffffffff00000000);
        local_e00 = 0x740;
        uStack_dfc = 0;
        uVar45 = (**(code **)(*DAT_7105331f00 + 0x30))(DAT_7105331f00,&local_140,&local_e00);
        if (((uVar45 & 1) != 0) &&
           (puVar28 = (undefined8 *)je_aligned_alloc(0x10,0x740), puVar28 != (undefined8 *)0x0))
        goto LAB_7103743734;
      }
      puVar28 = (undefined8 *)0x0;
    }
LAB_7103743734:
    *puVar28 = &PTR_LAB_7105230500;
    puVar28[1] = 0;
    puVar28[4] = &PTR_LAB_7105230520;
    puVar28[5] = 0;
    puVar28[8] = &PTR_LAB_7105230540;
    puVar28[9] = 0;
    puVar28[0xc] = &PTR_LAB_710522ed48;
    puVar28[0xd] = 0;
    puVar28[0x10] = &PTR_LAB_710522eea0;
    puVar28[0x11] = 0;
    *(undefined1 *)((long)puVar28 + 0x194) = 0;
    *(undefined4 *)(puVar28 + 0x33) = 0;
    puVar28[0x14] = &PTR_LAB_7105230560;
    puVar28[0x15] = 0;
    puVar28[0x18] = &PTR_LAB_7105230580;
    puVar28[0x19] = 0;
    puVar28[0x1c] = &PTR_LAB_71052305a0;
    puVar28[0x1d] = 0;
    puVar28[0x20] = &PTR_LAB_710522ef60;
    puVar28[0x21] = 0;
    puVar28[0x24] = &PTR_LAB_710522ef60;
    puVar28[0x25] = 0;
    *(undefined4 *)(puVar28 + 0x32) = 0x40400000;
    puVar28[0x28] = &PTR_LAB_7105230fe8;
    *(undefined4 *)(puVar28 + 0x38) = 0x3f800000;
    puVar28[2] = 0;
    puVar28[3] = 0;
    puVar28[6] = 0;
    puVar28[7] = 0;
    puVar28[10] = 0;
    puVar28[0xb] = 0;
    puVar28[0xe] = 0;
    puVar28[0xf] = 0;
    puVar28[0x12] = 0;
    puVar28[0x13] = 0;
    puVar28[0x16] = 0;
    puVar28[0x17] = 0;
    puVar28[0x1a] = 0;
    puVar28[0x1b] = 0;
    puVar28[0x1e] = 0;
    puVar28[0x1f] = 0;
    puVar28[0x22] = 0;
    puVar28[0x23] = 0;
    puVar28[0x26] = 0;
    puVar28[0x27] = 0;
    puVar28[0x36] = 0;
    puVar28[0x37] = 0;
    puVar28[0x34] = 0;
    puVar28[0x35] = 0;
    memset(puVar28 + 0x44,0,0x1f0);
    auVar196 = _DAT_7104469360;
    auVar145 = _DAT_7104469350;
    auVar134 = _DAT_71044646b0;
    puVar28[0x2b] = 0;
    puVar28[0x2a] = 0x3f800000;
    uVar84 = auVar196._8_8_;
    puVar28[0x2d] = uVar84;
    uVar82 = auVar196._0_8_;
    puVar28[0x2c] = uVar82;
    uVar90 = auVar134._8_8_;
    puVar28[0x2f] = uVar90;
    uVar87 = auVar134._0_8_;
    puVar28[0x2e] = uVar87;
    uVar69 = auVar145._8_8_;
    puVar28[0x31] = uVar69;
    uVar62 = auVar145._0_8_;
    puVar28[0x30] = uVar62;
    auVar104._8_8_ = 0x446d2999446d2999;
    auVar104._0_8_ = 0x446d2999446d2999;
    auVar134 = NEON_frsqrte(auVar104,4);
    auVar144._0_4_ = auVar134._0_4_ * 948.64996;
    auVar144._4_4_ = auVar134._4_4_ * 948.64996;
    auVar144._8_4_ = auVar134._8_4_ * 948.64996;
    auVar144._12_4_ = auVar134._12_4_ * 948.64996;
    auVar145 = NEON_frsqrts(auVar134,auVar144,4);
    auVar180._0_4_ = auVar134._0_4_ * auVar145._0_4_;
    auVar180._4_4_ = auVar134._4_4_ * auVar145._4_4_;
    auVar180._8_4_ = auVar134._8_4_ * auVar145._8_4_;
    auVar180._12_4_ = auVar134._12_4_ * auVar145._12_4_;
    auVar146._0_4_ = auVar180._0_4_ * 948.64996;
    auVar146._4_4_ = auVar180._4_4_ * 948.64996;
    auVar146._8_4_ = auVar180._8_4_ * 948.64996;
    auVar146._12_4_ = auVar180._12_4_ * 948.64996;
    auVar134 = NEON_fcmeq(auVar104,0,4);
    auVar145 = NEON_frsqrts(auVar180,auVar146,4);
    DAT_7105335088 = puVar28 + 0x28;
    puVar28[0x42] = 0;
    *(undefined1 *)(puVar28 + 0xc0) = 0;
    puVar28[0xc3] = 0;
    puVar28[0xc2] = 0;
    puVar28[0xc1] = 0;
    puVar28[0x3b] = 0;
    puVar28[0x3a] = 0x3f800000;
    puVar28[0x3d] = uVar84;
    puVar28[0x3c] = uVar82;
    puVar28[0xc4] = 0x3fe38e3900000000;
    fVar99 = auVar180._0_4_ * auVar145._0_4_ * 0.0;
    fVar68 = auVar180._4_4_ * auVar145._4_4_ * 0.10000001;
    fVar61 = auVar180._8_4_ * auVar145._8_4_ * 30.8;
    fVar141 = auVar180._12_4_ * auVar145._12_4_ * 0.0;
    puVar28[0x3f] = uVar90;
    puVar28[0x3e] = uVar87;
    puVar28[0x41] = uVar69;
    puVar28[0x40] = uVar62;
    uVar163 = a64_TBL(ZEXT816(0),_ConstantUnitY,0xb0a090807060504);
    uVar33 = a64_TBL(ZEXT816(0),_ConstantUnitY,0xf0e0d0c03020100);
    uVar169 = a64_TBL(ZEXT816(0),_ConstantUnitY,0x30201000b0a0908);
    uVar158 = a64_TBL(ZEXT816(0),_ConstantUnitY,0xf0e0d0c07060504);
    bVar118 = SUB41(fVar99,0) & ~auVar134[0];
    bVar122 = (byte)((uint)fVar99 >> 8) & ~auVar134[1];
    bVar123 = (byte)((uint)fVar99 >> 0x10) & ~auVar134[2];
    bVar124 = (byte)((uint)fVar99 >> 0x18) & ~auVar134[3];
    fVar119 = (float)CONCAT13(bVar124,CONCAT12(bVar123,CONCAT11(bVar122,bVar118)));
    bVar125 = SUB41(fVar68,0) & ~auVar134[4];
    bVar126 = (byte)((uint)fVar68 >> 8) & ~auVar134[5];
    bVar127 = (byte)((uint)fVar68 >> 0x10) & ~auVar134[6];
    bVar128 = (byte)((uint)fVar68 >> 0x18) & ~auVar134[7];
    auVar121._0_8_ = CONCAT17(bVar128,CONCAT16(bVar127,CONCAT15(bVar126,CONCAT14(bVar125,fVar119))))
    ;
    auVar121[8] = SUB41(fVar61,0) & ~auVar134[8];
    auVar121[9] = (byte)((uint)fVar61 >> 8) & ~auVar134[9];
    auVar121[10] = (byte)((uint)fVar61 >> 0x10) & ~auVar134[10];
    auVar121[0xb] = (byte)((uint)fVar61 >> 0x18) & ~auVar134[0xb];
    auVar179[0xc] = SUB41(fVar141,0) & ~auVar134[0xc];
    auVar179._0_12_ = auVar121;
    auVar179[0xd] = (byte)((uint)fVar141 >> 8) & ~auVar134[0xd];
    auVar179[0xe] = (byte)((uint)fVar141 >> 0x10) & ~auVar134[0xe];
    auVar179[0xf] = (byte)((uint)fVar141 >> 0x18) & ~auVar134[0xf];
    uVar63 = a64_TBL(ZEXT816(0),auVar179,0x30201000b0a0908);
    uVar133 = a64_TBL(ZEXT816(0),auVar179,0xf0e0d0c07060504);
    uVar142 = a64_TBL(ZEXT816(0),auVar179,0xf0e0d0c03020100);
    auVar135._0_8_ = a64_TBL(ZEXT816(0),auVar179,0xb0a090807060504);
    auVar135._8_8_ = uVar142;
    fVar99 = (float)((ulong)uVar63 >> 0x20);
    fVar68 = (float)((ulong)uVar133 >> 0x20);
    fVar168 = (float)((ulong)auVar135._0_8_ >> 0x20);
    auVar138._12_4_ = (float)((ulong)uVar142 >> 0x20);
    fVar157 = (float)uVar163 * (float)uVar63 - (float)uVar169 * (float)auVar135._0_8_;
    fVar160 = (float)((ulong)uVar163 >> 0x20) * fVar99 - (float)((ulong)uVar169 >> 0x20) * fVar168;
    fVar161 = (float)uVar33 * (float)uVar133 - (float)uVar158 * (float)uVar142;
    fVar162 = (float)((ulong)uVar33 >> 0x20) * fVar68 -
              (float)((ulong)uVar158 >> 0x20) * auVar138._12_4_;
    auVar147._0_4_ = fVar157 * fVar157;
    auVar147._4_4_ = fVar160 * fVar160;
    auVar147._8_4_ = fVar161 * fVar161;
    auVar147._12_4_ = fVar162 * fVar162;
    auVar134 = NEON_ext(auVar147,auVar147,8,1);
    fVar141 = auVar134._0_4_ + auVar147._0_4_;
    fVar153 = auVar134._4_4_ + auVar147._4_4_;
    fVar61 = fVar141 + fVar153;
    fVar141 = fVar141 + fVar153;
    auVar148._8_8_ = CONCAT44(fVar141,fVar61);
    auVar148._0_8_ = CONCAT44(fVar141,fVar61);
    auVar134 = NEON_frsqrte(auVar148,4);
    auVar170._0_4_ = auVar134._0_4_ * fVar61;
    auVar170._4_4_ = auVar134._4_4_ * fVar141;
    auVar170._8_4_ = auVar134._8_4_ * fVar61;
    auVar170._12_4_ = auVar134._12_4_ * fVar141;
    auVar145 = NEON_frsqrts(auVar134,auVar170,4);
    auVar164._0_4_ = auVar134._0_4_ * auVar145._0_4_;
    auVar164._4_4_ = auVar134._4_4_ * auVar145._4_4_;
    auVar164._8_4_ = auVar134._8_4_ * auVar145._8_4_;
    auVar164._12_4_ = auVar134._12_4_ * auVar145._12_4_;
    auVar176._0_4_ = fVar61 * auVar164._0_4_;
    auVar176._4_4_ = fVar141 * auVar164._4_4_;
    auVar176._8_4_ = fVar61 * auVar164._8_4_;
    auVar176._12_4_ = fVar141 * auVar164._12_4_;
    auVar134 = NEON_fcmeq(auVar148,0,4);
    auVar145 = NEON_frsqrts(auVar164,auVar176,4);
    auVar173._0_4_ = fVar119 * -0.0;
    auVar173._4_4_ = (float)((ulong)auVar121._0_8_ >> 0x20) * -0.3;
    auVar173._8_4_ = auVar121._8_4_ * -30.8;
    auVar173._12_4_ = auVar179._12_4_ * -0.0;
    auVar179 = NEON_ext(auVar173,auVar173,8,1);
    fVar157 = fVar157 * auVar164._0_4_ * auVar145._0_4_;
    fVar160 = fVar160 * auVar164._4_4_ * auVar145._4_4_;
    fVar161 = fVar161 * auVar164._8_4_ * auVar145._8_4_;
    fVar162 = fVar162 * auVar164._12_4_ * auVar145._12_4_;
    uVar140 = CONCAT11((byte)((uint)fVar157 >> 8) & ~auVar134[1],SUB41(fVar157,0) & ~auVar134[0]);
    bVar150 = (byte)((uint)fVar157 >> 0x10) & ~auVar134[2];
    bVar151 = (byte)((uint)fVar157 >> 0x18) & ~auVar134[3];
    fVar119 = (float)CONCAT13(bVar151,CONCAT12(bVar150,uVar140));
    bVar152 = SUB41(fVar160,0) & ~auVar134[4];
    bVar154 = (byte)((uint)fVar160 >> 8) & ~auVar134[5];
    bVar155 = (byte)((uint)fVar160 >> 0x10) & ~auVar134[6];
    bVar156 = (byte)((uint)fVar160 >> 0x18) & ~auVar134[7];
    auVar143._0_8_ = CONCAT17(bVar156,CONCAT16(bVar155,CONCAT15(bVar154,CONCAT14(bVar152,fVar119))))
    ;
    auVar143[8] = SUB41(fVar161,0) & ~auVar134[8];
    auVar143[9] = (byte)((uint)fVar161 >> 8) & ~auVar134[9];
    auVar143[10] = (byte)((uint)fVar161 >> 0x10) & ~auVar134[10];
    auVar143[0xb] = (byte)((uint)fVar161 >> 0x18) & ~auVar134[0xb];
    auVar149[0xc] = SUB41(fVar162,0) & ~auVar134[0xc];
    auVar149._0_12_ = auVar143;
    auVar149[0xd] = (byte)((uint)fVar162 >> 8) & ~auVar134[0xd];
    auVar149[0xe] = (byte)((uint)fVar162 >> 0x10) & ~auVar134[0xe];
    auVar149[0xf] = (byte)((uint)fVar162 >> 0x18) & ~auVar134[0xf];
    uVar33 = a64_TBL(ZEXT816(0),auVar149,0x30201000b0a0908);
    uVar169 = a64_TBL(ZEXT816(0),auVar149,0xf0e0d0c07060504);
    uVar158 = a64_TBL(ZEXT816(0),auVar149,0xb0a090807060504);
    uVar163 = a64_TBL(ZEXT816(0),auVar149,0xf0e0d0c03020100);
    fVar61 = (float)auVar135._0_8_ * (float)uVar33 - (float)uVar63 * (float)uVar158;
    fVar99 = fVar168 * (float)((ulong)uVar33 >> 0x20) - fVar99 * (float)((ulong)uVar158 >> 0x20);
    fVar141 = (float)uVar142 * (float)uVar169 - (float)uVar133 * (float)uVar163;
    auVar191._0_4_ = fVar119 * -0.0;
    auVar191._4_4_ = (float)((ulong)auVar143._0_8_ >> 0x20) * -0.3;
    auVar191._8_4_ = auVar143._8_4_ * -30.8;
    auVar191._12_4_ = auVar149._12_4_ * -0.0;
    auVar103 = NEON_ext(auVar191,auVar191,8,1);
    auVar196._0_4_ = fVar61 * -0.0;
    auVar196._4_4_ = fVar99 * -0.3;
    auVar196._8_4_ = fVar141 * -30.8;
    auVar196._12_4_ =
         (auVar138._12_4_ * (float)((ulong)uVar169 >> 0x20) -
         fVar68 * (float)((ulong)uVar163 >> 0x20)) * -0.0;
    auVar104 = NEON_ext(auVar196,auVar196,8,1);
    auVar136._4_12_ = auVar135._4_12_;
    auVar136._0_4_ = fVar61;
    auVar138._0_8_ = auVar136._0_8_;
    auVar138._8_4_ = fVar99;
    auVar137._8_8_ = auVar138._8_8_;
    auVar137._4_4_ = 0;
    auVar137._0_4_ = fVar61;
    auVar139._0_12_ = auVar137._0_12_;
    auVar139._12_4_ = 0;
    auVar134[2] = bVar150;
    auVar134._0_2_ = uVar140;
    auVar134[3] = bVar151;
    auVar134[4] = bVar118;
    auVar134[5] = bVar122;
    auVar134[6] = bVar123;
    auVar134[7] = bVar124;
    auVar134[8] = bVar152;
    auVar134[9] = bVar154;
    auVar134[10] = bVar155;
    auVar134[0xb] = bVar156;
    auVar134[0xc] = bVar125;
    auVar134[0xd] = bVar126;
    auVar134[0xe] = bVar127;
    auVar134[0xf] = bVar128;
    auVar145[2] = bVar150;
    auVar145._0_2_ = uVar140;
    auVar145[3] = bVar151;
    auVar145[4] = bVar118;
    auVar145[5] = bVar122;
    auVar145[6] = bVar123;
    auVar145[7] = bVar124;
    auVar145[8] = bVar152;
    auVar145[9] = bVar154;
    auVar145[10] = bVar155;
    auVar145[0xb] = bVar156;
    auVar145[0xc] = bVar125;
    auVar145[0xd] = bVar126;
    auVar145[0xe] = bVar127;
    auVar145[0xf] = bVar128;
    auVar134 = NEON_ext(auVar134,auVar145,8,1);
    auVar145 = NEON_ext(auVar139,auVar139,8,1);
    *(uint *)(puVar28 + 0xc6) = CONCAT13(bVar151,CONCAT12(bVar150,uVar140));
    *(float *)((long)puVar28 + 0x634) = fVar61;
    *(uint *)(puVar28 + 199) = CONCAT13(bVar124,CONCAT12(bVar123,CONCAT11(bVar122,bVar118)));
    *(undefined4 *)((long)puVar28 + 0x63c) = 0;
    auVar103._0_8_ =
         CONCAT44(auVar104._0_4_ + auVar196._0_4_ + auVar104._4_4_ + auVar196._4_4_,
                  auVar103._0_4_ + auVar191._0_4_ + auVar103._4_4_ + auVar191._4_4_);
    auVar103._8_4_ = auVar179._0_4_ + auVar173._0_4_ + auVar179._4_4_ + auVar173._4_4_;
    *(int *)(puVar28 + 200) = auVar134._0_4_;
    *(int *)((long)puVar28 + 0x644) = auVar145._0_4_;
    *(int *)(puVar28 + 0xc9) = auVar134._4_4_;
    *(int *)((long)puVar28 + 0x64c) = auVar145._4_4_;
    *(float *)(puVar28 + 0xca) = auVar143._8_4_;
    *(float *)((long)puVar28 + 0x654) = fVar141;
    *(float *)(puVar28 + 0xcb) = auVar121._8_4_;
    *(undefined4 *)((long)puVar28 + 0x65c) = 0;
    puVar28[0xcf] = 0;
    puVar28[0xce] = 0x3f800000;
    puVar28[0xd7] = 0;
    puVar28[0xd6] = 0x3f800000;
    puVar28[0xdf] = 0;
    puVar28[0xde] = 0x3f800000;
    auVar103._12_4_ = 0x3f800000;
    puVar28[0xd1] = uVar84;
    puVar28[0xd0] = uVar82;
    puVar28[0xd3] = uVar90;
    puVar28[0xd2] = uVar87;
    puVar28[0xd5] = uVar69;
    puVar28[0xd4] = uVar62;
    puVar28[0xd9] = uVar84;
    puVar28[0xd8] = uVar82;
    puVar28[0xdb] = uVar90;
    puVar28[0xda] = uVar87;
    puVar28[0xdd] = uVar69;
    puVar28[0xdc] = uVar62;
    puVar28[0xe1] = uVar84;
    puVar28[0xe0] = uVar82;
    puVar28[0xe3] = uVar90;
    puVar28[0xe2] = uVar87;
    puVar28[0xe5] = uVar69;
    puVar28[0xe4] = uVar62;
    puVar28[0xcd] = auVar103._8_8_;
    puVar28[0xcc] = auVar103._0_8_;
    puVar29 = (undefined8 *)je_aligned_alloc(0x10,0x118);
    if (puVar29 == (undefined8 *)0x0) {
      if (DAT_7105331f00 != (long *)0x0) {
        local_140 = (uint *)((ulong)local_140 & 0xffffffff00000000);
        local_e00 = 0x118;
        uStack_dfc = 0;
        uVar45 = (**(code **)(*DAT_7105331f00 + 0x30))(DAT_7105331f00,&local_140,&local_e00);
        if (((uVar45 & 1) != 0) &&
           (puVar29 = (undefined8 *)je_aligned_alloc(0x10,0x118), puVar29 != (undefined8 *)0x0))
        goto LAB_7103743a7c;
      }
      puVar29 = (undefined8 *)0x0;
    }
LAB_7103743a7c:
    puVar29[0x1e] = 0;
    *puVar29 = 0;
    puVar29[1] = 0;
    puVar29[4] = 0;
    puVar29[5] = 0;
    puVar29[2] = 0;
    puVar29[3] = &PTR_LAB_71052305c0;
    puVar29[8] = 0;
    puVar29[9] = 0;
    puVar29[6] = 0;
    puVar29[7] = 0;
    puVar29[0xc] = 0;
    puVar29[0xd] = 0;
    puVar29[10] = &PTR_LAB_71052305c0;
    puVar29[0xb] = 0;
    puVar29[0xe] = 0;
    puVar29[0xf] = 0;
    puVar29[0x12] = 0;
    puVar29[0x13] = 0;
    puVar29[0x10] = 0;
    puVar29[0x11] = &PTR_LAB_71052305c0;
    puVar29[0x16] = 0;
    puVar29[0x17] = 0;
    puVar29[0x14] = 0;
    puVar29[0x15] = 0;
    puVar29[0x1a] = 0;
    puVar29[0x1b] = 0;
    puVar29[0x18] = &PTR_LAB_71052305c0;
    puVar29[0x19] = 0;
    puVar29[0x1c] = 0;
    puVar29[0x1d] = 0;
    puVar29[0x21] = 0;
    puVar29[0x22] = 0;
    puVar29[0x1f] = &PTR_LAB_71052305c0;
    puVar29[0x20] = 0;
    puVar28[0xe6] = puVar29;
    DAT_7105334480 = puVar28;
  }
  puVar28 = DAT_7105334480;
  puVar29 = (undefined8 *)je_aligned_alloc(0x10,0x88);
  if (puVar29 == (undefined8 *)0x0) {
    if (DAT_7105331f00 != (long *)0x0) {
      local_140 = (uint *)((ulong)local_140 & 0xffffffff00000000);
      local_e00 = 0x88;
      uStack_dfc = 0;
      uVar45 = (**(code **)(*DAT_7105331f00 + 0x30))(DAT_7105331f00,&local_140,&local_e00);
      if (((uVar45 & 1) != 0) &&
         (puVar29 = (undefined8 *)je_aligned_alloc(0x10,0x88), puVar29 != (undefined8 *)0x0))
      goto LAB_7103743b34;
    }
    puVar29 = (undefined8 *)0x0;
  }
LAB_7103743b34:
  FUN_71037c34c0(puVar29);
  *(undefined1 *)(puVar29 + 8) = 0;
  *puVar29 = &PTR_FUN_7105240f38;
  *(undefined1 *)(puVar29 + 0x10) = 0;
  *(undefined4 *)(puVar29 + 0xd) = 0x3f800000;
  plVar40 = (long *)puVar29[1];
  puVar29[0xb] = 0;
  puVar29[0xc] = 0;
  puVar29[9] = 0;
  puVar29[10] = 0;
  puVar29[6] = 0;
  puVar29[7] = 0;
  puVar29[4] = 0;
  puVar29[5] = 0;
  puVar29[2] = 0;
  puVar29[3] = 0;
  puVar29[0xe] = 0;
  puVar29[0xf] = 0;
  plVar31 = (long *)puVar28[1];
  plVar48 = (long *)puVar28[2];
  lVar52 = puVar28[3];
  puVar28[3] = *plVar40;
  puVar28[1] = puVar29;
  puVar28[2] = plVar40;
  if (((plVar48 != (long *)0x0) && (plVar31 != (long *)0x0)) && (*plVar48 == lVar52)) {
    (**(code **)(*plVar31 + 8))();
    plVar40 = (long *)puVar28[2];
  }
  if (((plVar40 == (long *)0x0) || (*plVar40 != puVar28[3])) ||
     ((lVar52 = puVar28[1], lVar52 == 0 || (*(long *)(lVar52 + 8) == 0)))) {
    uVar33 = 0;
    puVar28[5] = 0;
    puVar28[6] = 0;
  }
  else {
    puVar28[5] = lVar52;
    puVar29 = *(undefined8 **)(lVar52 + 8);
    puVar28[6] = puVar29;
    uVar33 = *puVar29;
  }
  puVar28[7] = uVar33;
  lVar52 = DAT_7105334480[5];
  local_e00 = 0xffffffff;
  uStack_dfc = 0xffffffff;
  local_df0 = 0x14;
  uStack_de4 = 0;
  local_de0 = (uint *)0x0;
  uStack_def = 0x6870617247756e;
  local_de8 = 0x69;
  uStack_de7 = 0x7363;
  local_dd8 = (uint *)CONCAT44(local_dd8._4_4_,0x101);
  uStack_de5 = 0;
  local_dd0 = 0;
  local_dc8 = CONCAT31(local_dc8._1_3_,1);
  local_df8 = 0x780;
  uStack_df4 = 0x438;
  std::__1::basic_string<>::assign((char *)&local_df0);
  local_dd8._0_3_ = (uint3)(ushort)local_dd8;
  nn::vi::Initialize();
  nn::vi::OpenDefaultDisplay((Display **)(lVar52 + 0x70));
  *(uint *)(lVar52 + 0x30) = local_df8;
  *(undefined4 *)(lVar52 + 0x34) = uStack_df4;
  nn::vi::CreateLayer((Layer **)(lVar52 + 0x78),*(Display **)(lVar52 + 0x70));
  nn::vi::GetNativeWindow((void **)(lVar52 + 0x10),*(Layer **)(lVar52 + 0x78));
  *(undefined8 *)(lVar52 + 0x38) = 0;
  *(undefined1 *)(lVar52 + 0x80) = 1;
  nn::oe::SetOperationModeChangedNotificationEnabled(true);
  if (((local_df0 & 1) != 0) && (local_de0 != (uint *)0x0)) {
    FUN_710392e590();
  }
  DAT_7107446024 = 0x44f00000;
  DAT_7107446028 = 0x44870000;
  DAT_710744601c = 0x44f00000;
  DAT_7107446020 = 0x44870000;
  uVar33 = puVar28[5];
  if (((DAT_7106d42468 & 1) == 0) && (iVar23 = __cxa_guard_acquire(&DAT_7106d42468), iVar23 != 0)) {
    DAT_7106d42418 = &PTR_LAB_7105292a68;
    DAT_7106d42428 = 4;
    DAT_7106d42430 = 0;
    DAT_7106d42438 = 0;
    DAT_7106d42440 = 1;
    DAT_7106d42420 = '\0';
    DAT_7106d42448 = 0;
    DAT_7106d42458 = 0;
    DAT_7106d42460 = 0;
    DAT_7106d42450 = &DAT_7106d42458;
    FUN_71000001c0(&LAB_71038f34e0,&DAT_7106d42418,&PTR_LOOP_7104f16000);
    __cxa_guard_release(&DAT_7106d42468);
  }
  if ((DAT_7106d42420 != '\0') &&
     (plVar31 = DAT_7106d42450, DAT_7106d42430 = uVar33, DAT_7106d42450 != &DAT_7106d42458)) {
    do {
      while( true ) {
        lVar47 = plVar31[5];
        lVar52 = *(long *)(lVar47 + 0x48);
        lVar49 = *(long *)(lVar47 + 0x50);
        *(undefined8 *)(lVar47 + 0x20) = uVar33;
        if (lVar49 != lVar52) {
          lVar50 = 0;
          uVar45 = 0;
          do {
            lVar51 = *(long *)(lVar52 + lVar50);
            if (lVar51 != 0) {
              *(undefined8 *)(lVar51 + 0x38) = *(undefined8 *)(lVar47 + 0x20);
              *(undefined1 *)(lVar51 + 0x31) = 1;
              lVar52 = *(long *)(lVar47 + 0x48);
              lVar49 = *(long *)(lVar47 + 0x50);
            }
            uVar45 = uVar45 + 1;
            lVar50 = lVar50 + 0x18;
          } while (uVar45 < (ulong)((lVar49 - lVar52 >> 3) * -0x5555555555555555));
        }
        plVar48 = (long *)plVar31[1];
        if ((long *)plVar31[1] == (long *)0x0) break;
        do {
          plVar31 = plVar48;
          plVar48 = (long *)*plVar31;
        } while ((long *)*plVar31 != (long *)0x0);
LAB_7103743ddc:
        if (plVar31 == &DAT_7106d42458) goto LAB_7103743df4;
      }
      plVar48 = plVar31 + 2;
      plVar40 = (long *)*plVar48;
      if ((long *)*plVar40 != plVar31) {
        do {
          lVar52 = *plVar48;
          plVar48 = (long *)(lVar52 + 0x10);
          plVar31 = (long *)*plVar48;
        } while (*plVar31 != lVar52);
        goto LAB_7103743ddc;
      }
      plVar31 = plVar40;
    } while (plVar40 != &DAT_7106d42458);
  }
LAB_7103743df4:
  local_df0 = 0;
  uStack_def = 0;
  local_df8 = 0;
  uStack_df4 = 0;
  local_e00 = 0;
  uStack_dfc = 0;
  local_de8 = 0xff;
  uStack_de7 = 0xffff;
  uStack_de5 = 0;
  local_dd0 = 0;
  local_dd8 = (uint *)0x0;
  local_de0 = (uint *)0x0;
  local_dc8 = 0xffffff;
  local_db0 = 0;
  local_db8 = (uint *)0x0;
  local_dc0 = (uint *)0x0;
  local_da8 = 0xffffff;
  local_d90 = 0;
  local_d98 = (uint *)0x0;
  local_da0 = (uint *)0x0;
  local_d88 = 0xffffff;
  local_d70 = 0;
  local_d78 = (uint *)0x0;
  local_d80 = (uint *)0x0;
  local_d68 = 0xffffff;
  FUN_710358eed0(&local_140,"render/shader/bin/nuSampleShaderList.");
  uVar3 = uStack_dfc;
  uVar36 = local_e00;
  piVar54 = (int *)CONCAT44(uStack_dfc,local_e00);
  if (piVar54 != (int *)0x0) {
    piVar55 = (int *)CONCAT44(uStack_df4,local_df8);
    if (piVar55 != piVar54) {
      do {
        piVar53 = piVar55 + -1;
        if (*piVar53 != 0xffffff) {
          FUN_7103540560(DAT_7105331f20);
          piVar55[-1] = 0xffffff;
        }
        piVar55 = piVar53;
      } while (piVar54 != piVar53);
      piVar54 = (int *)CONCAT44(uStack_dfc,local_e00);
    }
    local_df8 = uVar36;
    uStack_df4 = uVar3;
    if (piVar54 != (int *)0x0) {
      FUN_710392e590();
    }
  }
  local_e00 = (uint)local_140;
  uStack_dfc = (uint)((ulong)local_140 >> 0x20);
  local_df8 = (uint)local_138[0];
  uStack_df4 = (undefined4)((ulong)local_138[0] >> 0x20);
  local_df0 = (byte)local_138[1];
  uStack_def = (undefined7)((ulong)local_138[1] >> 8);
  FUN_710353d480(&local_140,0x2ac215e043);
  puVar59 = local_140;
  if (CONCAT13(uStack_de5,CONCAT21(uStack_de7,local_de8)) != 0xffffff) {
    FUN_7103540560(DAT_7105331f20);
  }
  local_de8 = SUB81(puVar59,0);
  uStack_de7 = (undefined2)((ulong)puVar59 >> 8);
  uStack_de5 = (undefined1)((ulong)puVar59 >> 0x18);
  FUN_710358eed0(&local_140,"render/shader/bin/3DFinal.");
  puVar59 = local_de0;
  puVar32 = local_dd8;
  if (local_de0 != (uint *)0x0) {
    while (puVar21 = puVar32, puVar21 != puVar59) {
      puVar32 = puVar21 + -1;
      if (*puVar32 != 0xffffff) {
        FUN_7103540560(DAT_7105331f20);
        puVar21[-1] = 0xffffff;
      }
    }
    local_dd8 = puVar59;
    if (local_de0 != (uint *)0x0) {
      FUN_710392e590();
    }
  }
  local_de0 = local_140;
  local_dd8 = (uint *)local_138[0];
  local_dd0 = local_138[1];
  FUN_710358eed0(&local_140,"render/shader/bin/nuC2ShaderList.");
  puVar59 = local_dc0;
  puVar32 = local_db8;
  if (local_dc0 != (uint *)0x0) {
    while (puVar21 = puVar32, puVar21 != puVar59) {
      puVar32 = puVar21 + -1;
      if (*puVar32 != 0xffffff) {
        FUN_7103540560(DAT_7105331f20);
        puVar21[-1] = 0xffffff;
      }
    }
    local_db8 = puVar59;
    if (local_dc0 != (uint *)0x0) {
      FUN_710392e590();
    }
  }
  local_dc0 = local_140;
  local_db8 = (uint *)local_138[0];
  local_db0 = local_138[1];
  FUN_710353d480(&local_140,0x262d2da64b);
  uVar22 = (uint)local_140;
  if (local_da8 != 0xffffff) {
    FUN_7103540560(DAT_7105331f20);
  }
  local_da8 = uVar22;
  FUN_710358eed0(&local_140,"render/shader/bin/PostEffectShaderList.");
  puVar59 = local_da0;
  puVar32 = local_d98;
  if (local_da0 != (uint *)0x0) {
    while (puVar21 = puVar32, puVar21 != puVar59) {
      puVar32 = puVar21 + -1;
      if (*puVar32 != 0xffffff) {
        FUN_7103540560(DAT_7105331f20);
        puVar21[-1] = 0xffffff;
      }
    }
    local_d98 = puVar59;
    if (local_da0 != (uint *)0x0) {
      FUN_710392e590();
    }
  }
  local_da0 = local_140;
  local_d98 = (uint *)local_138[0];
  local_d90 = local_138[1];
  FUN_710353d480(&local_140,0x2ca2c80607);
  uVar22 = (uint)local_140;
  if (local_d88 != 0xffffff) {
    FUN_7103540560(DAT_7105331f20);
  }
  local_d88 = uVar22;
  FUN_710358eed0(&local_140,"render/shader/bin/nuC2ShaderListNoTranscompiling.");
  puVar59 = local_d80;
  puVar32 = local_d78;
  if (local_d80 != (uint *)0x0) {
    while (puVar21 = puVar32, puVar21 != puVar59) {
      puVar32 = puVar21 + -1;
      if (*puVar32 != 0xffffff) {
        FUN_7103540560(DAT_7105331f20);
        puVar21[-1] = 0xffffff;
      }
    }
    local_d78 = puVar59;
    if (local_d80 != (uint *)0x0) {
      FUN_710392e590();
    }
  }
  local_d80 = local_140;
  local_d78 = (uint *)local_138[0];
  local_d70 = local_138[1];
  FUN_710353d480(&local_140,0x3630eacabc);
  uVar22 = (uint)local_140;
  if (local_d68 != 0xffffff) {
    FUN_7103540560(DAT_7105331f20);
  }
  local_d68 = uVar22;
  uVar45 = FUN_710358d020(puVar28[0xe6],&local_e00);
  if (((((uVar45 & 1) == 0) &&
       (uVar45 = FUN_710358d020(puVar28[0xe6] + 0x38,&local_de0), (uVar45 & 1) == 0)) &&
      (uVar45 = FUN_710358d020(puVar28[0xe6] + 0x70,&local_dc0), (uVar45 & 1) == 0)) &&
     ((uVar45 = FUN_710358d020(puVar28[0xe6] + 0xa8,&local_da0), (uVar45 & 1) == 0 &&
      (uVar45 = FUN_710358d020(puVar28[0xe6] + 0xe0,&local_d80), (uVar45 & 1) == 0)))) {
    FUN_710358eb60(&local_e00);
    fVar160 = nn::util::detail::Float2Pi;
    fVar157 = DAT_7107447714;
    fVar153 = nn::util::detail::Float1Divided2Pi;
    fVar168 = DAT_710744770c;
    fVar119 = nn::util::detail::CosCoefficients;
    fVar141 = DAT_7107447704;
    fVar61 = nn::util::detail::SinCoefficients;
    fVar68 = nn::util::detail::FloatPi;
    fVar99 = nn::util::detail::FloatPiDivided2;
    fVar96 = -nn::util::detail::CosCoefficients;
    fVar97 = -nn::util::detail::FloatPi;
    fVar101 = -nn::util::detail::FloatPiDivided2;
    uVar129 = SUB41(DAT_7107447704,0);
    uVar130 = (undefined1)((uint)DAT_7107447704 >> 8);
    uVar131 = (undefined1)((uint)DAT_7107447704 >> 0x10);
    uVar132 = (undefined1)((uint)DAT_7107447704 >> 0x18);
    fVar120 = -nn::util::detail::SinCoefficients;
    local_e30 = (undefined **)
                CONCAT44(nn::util::detail::FloatPiDivided2,nn::util::detail::FloatPiDivided2);
    fVar83 = -nn::util::detail::Float1Divided2Pi;
    fVar70 = -nn::util::detail::Float2Pi;
    fVar88 = -nn::util::detail::Float1Divided2Pi;
    auVar107._8_4_ = 0x3f000000;
    auVar107._0_8_ = 0x3f0000003f000000;
    auVar107._12_4_ = 0x3f000000;
    fVar89 = -nn::util::detail::CosCoefficients;
    auVar109._8_4_ = 0xbf000000;
    auVar109._0_8_ = 0xbf000000bf000000;
    auVar109._12_4_ = 0xbf000000;
    auVar134 = NEON_fmov(0xbf800000,4);
    auVar145 = NEON_fmov(0x3f800000,4);
    lVar52 = 0;
    puVar29 = (undefined8 *)&DAT_7105335790;
    uVar33 = auVar145._8_8_;
    fStack_ef8 = auVar145._8_4_;
    fStack_ef4 = auVar145._12_4_;
    local_f00 = auVar145._0_4_;
    fStack_efc = auVar145._4_4_;
    fVar161 = nn::util::detail::Float2Pi;
    fVar162 = nn::util::detail::Float2Pi;
    do {
      iVar23 = (int)lVar52;
      lVar52 = lVar52 + 1;
      fVar186 = (float)iVar23 * 0.69813174;
      auVar20._4_4_ = fVar99;
      auVar20._0_4_ = fVar99;
      auVar20[8] = uStack_e38;
      auVar20._9_7_ = uStack_e37;
      auVar187._0_4_ = fVar153 * 0.0;
      auVar187._4_4_ = fVar186 * fVar153;
      auVar187._8_4_ = fVar153 * 0.0;
      auVar187._12_4_ = fVar153 * 0.0;
      auVar196 = NEON_fcmge(auVar187,0,4);
      auVar196 = NEON_bsl(auVar196,auVar107,auVar109,1);
      auVar188._0_4_ = (int)(auVar187._0_4_ + auVar196._0_4_);
      auVar188._4_4_ = (int)(auVar187._4_4_ + auVar196._4_4_);
      auVar188._8_4_ = (int)(auVar187._8_4_ + auVar196._8_4_);
      auVar188._12_4_ = (int)(auVar187._12_4_ + auVar196._12_4_);
      auVar196 = NEON_scvtf(auVar188,4);
      auVar190._0_4_ = 0.0 - auVar196._0_4_ * fVar160;
      auVar190._4_4_ = fVar186 - auVar196._4_4_ * fVar160;
      auVar190._8_4_ = 0.0 - auVar196._8_4_ * fVar161;
      auVar190._12_4_ = 0.0 - auVar196._12_4_ * fVar162;
      auVar103 = NEON_fcmgt(auVar190,auVar20,4);
      auVar197._0_4_ = fVar101 - auVar190._0_4_;
      auVar197._4_4_ = fVar101 - auVar190._4_4_;
      auVar197._8_4_ =
           (float)CONCAT13(uStack_ea5,CONCAT12(uStack_ea6,CONCAT11(uStack_ea7,uStack_ea8))) -
           auVar190._8_4_;
      auVar197._12_4_ =
           (float)CONCAT13(uStack_ea1,CONCAT12(uStack_ea2,CONCAT11(uStack_ea3,uStack_ea4))) -
           auVar190._12_4_;
      auVar19._4_4_ = fVar97;
      auVar19._0_4_ = fVar97;
      auVar19._8_4_ = fStack_eb8;
      auVar19._12_4_ = fStack_eb4;
      auVar196 = NEON_bsl(auVar103,auVar197,auVar190,1);
      auVar103 = NEON_bsl(auVar103,auVar134,auVar145,1);
      auVar191 = NEON_fcmgt(auVar19,auVar196,4);
      auVar198._0_4_ = fVar120 - auVar196._0_4_;
      auVar198._4_4_ = fVar120 - auVar196._4_4_;
      auVar198._8_4_ = fStack_ec8 - auVar196._8_4_;
      auVar198._12_4_ = fStack_ec4 - auVar196._12_4_;
      auVar103 = NEON_bsl(auVar191,auVar134,auVar103,1);
      auVar196 = NEON_bsl(auVar191,auVar198,auVar196,1);
      fVar80 = auVar196._0_4_;
      fVar161 = fVar80 * fVar80;
      fVar110 = auVar196._4_4_;
      fVar162 = fVar110 * fVar110;
      fVar112 = auVar196._8_4_;
      fVar186 = fVar112 * fVar112;
      fVar113 = auVar196._12_4_;
      fVar108 = fVar113 * fVar113;
      auVar189._0_4_ =
           (local_f00 +
           fVar161 * (fVar88 + fVar161 * (fVar168 +
                                         fVar161 * (fVar96 + fVar161 * (fVar141 + fVar161 * fVar96))
                                         ))) * fVar80;
      auVar189._4_4_ =
           (fStack_efc +
           fVar162 * (fVar88 + fVar162 * (fVar168 +
                                         fVar162 * (fVar96 + fVar162 * ((float)(CONCAT17(uVar132,
                                                  CONCAT16(uVar131,CONCAT15(uVar130,CONCAT14(uVar129
                                                  ,fVar141)))) >> 0x20) + fVar162 * fVar96))))) *
           fVar110;
      auVar189._8_4_ =
           (fStack_ef8 +
           fVar186 * (fStack_f08 +
                     fVar186 * (fVar168 +
                               fVar186 * (fStack_ee8 + fVar186 * (fVar141 + fVar186 * fStack_ed8))))
           ) * fVar112;
      auVar189._12_4_ =
           (fStack_ef4 +
           fVar108 * (fStack_f04 +
                     fVar108 * (fVar168 +
                               fVar108 * (fStack_ee4 +
                                         fVar108 * ((float)(CONCAT17(uVar132,CONCAT16(uVar131,
                                                  CONCAT15(uVar130,CONCAT14(uVar129,fVar141)))) >>
                                                  0x20) + fVar108 * fStack_ed4))))) * fVar113;
      auVar192._0_4_ =
           (local_f00 +
           fVar161 * (fVar70 + fVar161 * (fVar157 +
                                         fVar161 * (fVar83 + fVar161 * (fVar168 + fVar161 * fVar89))
                                         ))) * auVar103._0_4_;
      auVar192._4_4_ =
           (fStack_efc +
           fVar162 * (fVar70 + fVar162 * (fVar157 +
                                         fVar162 * (fVar83 + fVar162 * (fVar168 + fVar162 * fVar89))
                                         ))) * auVar103._4_4_;
      auVar192._8_4_ =
           (fStack_ef8 +
           fVar186 * (fVar70 + fVar186 * (fVar157 +
                                         fVar186 * (fVar83 + fVar186 * (fVar168 + fVar186 * fVar89))
                                         ))) * auVar103._8_4_;
      auVar192._12_4_ =
           (fStack_ef4 +
           fVar108 * (fVar70 + fVar108 * (fVar157 +
                                         fVar108 * (fVar83 + fVar108 * (fVar168 + fVar108 * fVar89))
                                         ))) * auVar103._12_4_;
      auVar196 = NEON_ext(auVar189,auVar189,8,1);
      auVar103 = NEON_ext(auVar192,auVar192,8,1);
      fVar161 = auVar196._0_4_;
      fVar162 = auVar103._0_4_;
      fVar112 = auVar192._4_4_ * fVar162;
      fVar114 = auVar192._4_4_ * fVar161;
      fVar116 = auVar189._4_4_ * -1.0;
      fVar186 = fVar161 * auVar192._0_4_ * -1.0 + auVar189._4_4_ * fVar162 * auVar189._0_4_;
      fVar108 = fVar162 * auVar192._0_4_ * 1.0 + auVar189._4_4_ * fVar161 * auVar189._0_4_;
      fVar80 = auVar192._0_4_ * 0.0 * 0.0 + auVar192._4_4_ * 1.0 * auVar189._0_4_;
      fVar110 = fVar161 * auVar189._0_4_ * 1.0 + auVar189._4_4_ * fVar162 * auVar192._0_4_;
      fVar161 = fVar162 * auVar189._0_4_ * -1.0 + auVar189._4_4_ * fVar161 * auVar192._0_4_;
      fVar162 = auVar189._0_4_ * 0.0 * 0.0 + auVar192._4_4_ * 1.0 * auVar192._0_4_;
      auVar199._0_4_ = fVar112 * -0.50000006 + fVar186 * 0.0 + fVar110 * 0.8660254;
      auVar199._4_4_ = fVar114 * -0.50000006 + fVar108 * 0.0 + fVar161 * 0.8660254;
      auVar199._8_4_ = fVar116 * -0.50000006 + fVar80 * 0.0 + fVar162 * 0.8660254;
      fVar113 = fVar112 + fVar186 * 0.0;
      fVar115 = fVar114 + fVar108 * 0.0;
      fVar117 = fVar116 + fVar80 * 0.0;
      auVar199._12_4_ = 0;
      *(float *)(puVar29 + -5) = fVar116 * 0.1736481 + fVar80 * 0.0 + fVar162 * 0.9848078;
      *(undefined4 *)((long)puVar29 + -0x24) = 0;
      puVar29[-6] = CONCAT44(fVar114 * 0.1736481 + fVar108 * 0.0 + fVar161 * 0.9848078,
                             fVar112 * 0.1736481 + fVar186 * 0.0 + fVar110 * 0.9848078);
      *(undefined1 (*) [16])(puVar29 + -4) = auVar199;
      *(float *)(puVar29 + -1) = fVar116 * -0.9396927 + fVar80 * 0.0 + fVar162 * 0.34202;
      *(undefined4 *)((long)puVar29 + -4) = 0;
      puVar29[-2] = CONCAT44(fVar114 * -0.9396927 + fVar108 * 0.0 + fVar161 * 0.34202,
                             fVar112 * -0.9396927 + fVar186 * 0.0 + fVar110 * 0.34202);
      *(float *)(puVar29 + 1) = fVar116 * -0.93969256 + fVar80 * 0.0 + fVar162 * -0.3420204;
      *(undefined4 *)((long)puVar29 + 0xc) = 0;
      *puVar29 = CONCAT44(fVar114 * -0.93969256 + fVar108 * 0.0 + fVar161 * -0.3420204,
                          fVar112 * -0.93969256 + fVar186 * 0.0 + fVar110 * -0.3420204);
      auVar107._8_4_ = 0x3f000000;
      auVar107._0_8_ = 0x3f0000003f000000;
      auVar107._12_4_ = 0x3f000000;
      auVar109._8_4_ = 0xbf000000;
      auVar109._0_8_ = 0xbf000000bf000000;
      auVar109._12_4_ = 0xbf000000;
      *(float *)(puVar29 + 3) = fVar116 * -0.4999999 + fVar80 * 0.0 + fVar162 * -0.86602545;
      *(undefined4 *)((long)puVar29 + 0x1c) = 0;
      puVar29[2] = CONCAT44(fVar114 * -0.4999999 + fVar108 * 0.0 + fVar161 * -0.86602545,
                            fVar112 * -0.4999999 + fVar186 * 0.0 + fVar110 * -0.86602545);
      *(float *)(puVar29 + 5) = fVar116 * 0.17364863 + fVar80 * 0.0 + fVar162 * -0.98480767;
      *(undefined4 *)((long)puVar29 + 0x2c) = 0;
      puVar29[4] = CONCAT44(fVar114 * 0.17364863 + fVar108 * 0.0 + fVar161 * -0.98480767,
                            fVar112 * 0.17364863 + fVar186 * 0.0 + fVar110 * -0.98480767);
      *(float *)(puVar29 + 7) = fVar116 * 0.7660446 + fVar80 * 0.0 + fVar162 * -0.6427874;
      *(undefined4 *)((long)puVar29 + 0x3c) = 0;
      puVar29[6] = CONCAT44(fVar114 * 0.7660446 + fVar108 * 0.0 + fVar161 * -0.6427874,
                            fVar112 * 0.7660446 + fVar186 * 0.0 + fVar110 * -0.6427874);
      *(float *)(puVar29 + 9) = fVar117 + fVar162 * 1.7484555e-07;
      *(undefined4 *)((long)puVar29 + 0x4c) = 0;
      puVar29[8] = CONCAT44(fVar115 + fVar161 * 1.7484555e-07,fVar113 + fVar110 * 1.7484555e-07);
      puVar29[-9] = (ulong)(uint)(fVar117 + fVar162 * 0.0);
      puVar29[-10] = CONCAT44(fVar115 + fVar161 * 0.0,fVar113 + fVar110 * 0.0);
      *(float *)(puVar29 + -7) = fVar116 * 0.76604444 + fVar80 * 0.0 + fVar162 * 0.64278764;
      *(undefined4 *)((long)puVar29 + -0x34) = 0;
      puVar29[-8] = CONCAT44(fVar114 * 0.76604444 + fVar108 * 0.0 + fVar161 * 0.64278764,
                             fVar112 * 0.76604444 + fVar186 * 0.0 + fVar110 * 0.64278764);
      fVar80 = DAT_7107447714;
      fVar108 = DAT_710744770c;
      fVar186 = DAT_7107447704;
      puVar29 = puVar29 + 0x14;
      fVar161 = fStack_e98;
      fVar162 = fStack_e94;
    } while (lVar52 != 9);
    auVar193._4_4_ = fVar101;
    auVar193._0_4_ = fVar101;
    auVar193._8_4_ = fVar101;
    auVar193._12_4_ = fVar101;
    local_f30 = SUB41(fVar89,0);
    uStack_f2f = (undefined1)((uint)fVar89 >> 8);
    uStack_f2e = (undefined1)((uint)fVar89 >> 0x10);
    uStack_f2d = (undefined1)((uint)fVar89 >> 0x18);
    local_eb0 = SUB41(DAT_710744770c,0);
    uStack_eaf = (undefined1)((uint)DAT_710744770c >> 8);
    uStack_eae = (undefined1)((uint)DAT_710744770c >> 0x10);
    uStack_ead = (undefined1)((uint)DAT_710744770c >> 0x18);
    uVar36 = 0;
    puVar29 = (undefined8 *)&DAT_7105335310;
    uVar129 = local_f30;
    uVar130 = uStack_f2f;
    uVar131 = uStack_f2e;
    uVar132 = uStack_f2d;
    fVar141 = fVar88;
    fVar168 = fVar88;
    do {
      auVar72._0_4_ = fVar153 * 0.0;
      auVar72._4_4_ = (float)(int)uVar36 * 0.69813174 * fVar153;
      auVar72._8_4_ = fVar153 * 0.0;
      auVar72._12_4_ = fVar153 * 0.0;
      auVar196 = NEON_fcmge(auVar72,0,4);
      auVar196 = NEON_bsl(auVar196,auVar107,auVar109,1);
      auVar73._0_4_ = (int)(auVar72._0_4_ + auVar196._0_4_);
      auVar73._4_4_ = (int)(auVar72._4_4_ + auVar196._4_4_);
      auVar73._8_4_ = (int)(auVar72._8_4_ + auVar196._8_4_);
      auVar73._12_4_ = (int)(auVar72._12_4_ + auVar196._12_4_);
      auVar196 = NEON_scvtf(auVar73,4);
      auVar85._0_4_ = 0.0 - auVar196._0_4_ * fVar160;
      auVar85._4_4_ = (float)(int)uVar36 * 0.69813174 - auVar196._4_4_ * fVar160;
      auVar85._8_4_ = 0.0 - auVar196._8_4_ * fStack_e98;
      auVar85._12_4_ = 0.0 - auVar196._12_4_ * fStack_e94;
      auVar16._4_4_ = fVar99;
      auVar16._0_4_ = fVar99;
      auVar16._8_4_ = fVar99;
      auVar16._12_4_ = fVar99;
      auVar196 = NEON_fcmgt(auVar85,auVar16,4);
      auVar94._0_4_ = fVar68 - auVar85._0_4_;
      auVar94._4_4_ = fVar68 - auVar85._4_4_;
      auVar94._8_4_ = fVar68 - auVar85._8_4_;
      auVar94._12_4_ = fVar68 - auVar85._12_4_;
      auVar103 = NEON_bsl(auVar196,auVar134,auVar145,1);
      auVar191 = NEON_bsl(auVar196,auVar94,auVar85,1);
      auVar196 = NEON_fcmgt(auVar193,auVar191,4);
      auVar105._0_4_ = fVar97 - auVar191._0_4_;
      auVar105._4_4_ = fVar97 - auVar191._4_4_;
      auVar105._8_4_ = fVar97 - auVar191._8_4_;
      auVar105._12_4_ = fVar97 - auVar191._12_4_;
      auVar103 = NEON_bsl(auVar196,auVar134,auVar103,1);
      auVar196 = NEON_bsl(auVar196,auVar105,auVar191,1);
      fVar98 = auVar196._0_4_;
      fVar157 = fVar98 * fVar98;
      fVar100 = auVar196._4_4_;
      fVar161 = fVar100 * fVar100;
      fVar112 = auVar196._8_4_;
      fVar162 = fVar112 * fVar112;
      fVar113 = auVar196._12_4_;
      fVar110 = fVar113 * fVar113;
      fVar98 = (local_f00 +
               fVar157 * (fVar88 + fVar157 * (fVar108 +
                                             fVar157 * (fVar96 + fVar157 * (fVar186 +
                                                                           fVar157 * fVar120))))) *
               fVar98;
      fVar100 = (fStack_efc +
                fVar161 * (fVar88 + fVar161 * (fVar108 +
                                              fVar161 * (fVar96 + fVar161 * (fVar186 +
                                                                            fVar161 * fVar120))))) *
                fVar100;
      fVar112 = (fStack_ef8 +
                fVar162 * (fVar141 +
                          fVar162 * (fVar108 +
                                    fVar162 * (fVar96 + fVar162 * (fVar186 + fVar162 * fVar120)))))
                * fVar112;
      fVar113 = (fStack_ef4 +
                fVar110 * (fVar168 +
                          fVar110 * (fVar108 +
                                    fVar110 * (fVar96 + fVar110 * (fVar186 + fVar110 * fVar120)))))
                * fVar113;
      auVar6._4_4_ = fVar100;
      auVar6._0_4_ = fVar98;
      auVar6._8_4_ = fVar112;
      auVar6._12_4_ = fVar113;
      auVar7._4_4_ = fVar100;
      auVar7._0_4_ = fVar98;
      auVar7._8_4_ = fVar112;
      auVar7._12_4_ = fVar113;
      auVar196 = NEON_ext(auVar6,auVar7,8,1);
      auVar91._0_4_ =
           (local_f00 +
           fVar157 * (fVar70 + fVar157 * (fVar83 + fVar157 * (fVar83 + fVar157 * (fVar80 + fVar157 *
                                                                                           (float)
                                                  CONCAT13(uVar132,CONCAT12(uVar131,CONCAT11(uVar130
                                                  ,uVar129)))))))) * auVar103._0_4_;
      auVar91._4_4_ =
           (fStack_efc +
           fVar161 * (fVar70 + fVar161 * (fVar83 + fVar161 * (fVar83 + fVar161 * (fVar80 + fVar161 *
                                                                                           (float)
                                                  CONCAT13(uVar132,CONCAT12(uVar131,CONCAT11(uVar130
                                                  ,uVar129)))))))) * auVar103._4_4_;
      auVar91._8_4_ =
           (fStack_ef8 +
           fVar162 * (fStack_f08 +
                     fVar162 * (fStack_ec8 +
                               fVar162 * (fStack_ed8 + fVar162 * (fStack_eb8 + fVar162 * fVar89)))))
           * auVar103._8_4_;
      auVar91._12_4_ =
           (fStack_ef4 +
           fVar110 * (fStack_f04 +
                     fVar110 * (fStack_ec4 +
                               fVar110 * (fStack_ed4 + fVar110 * (fStack_eb4 + fVar110 * fVar89)))))
           * auVar103._12_4_;
      auVar103 = NEON_ext(auVar91,auVar91,8,1);
      fVar157 = auVar103._0_4_;
      fVar161 = auVar196._0_4_;
      fVar162 = auVar91._4_4_ * fVar157;
      fVar110 = auVar91._4_4_ * fVar161;
      fVar112 = fVar100 * -1.0;
      fVar114 = fVar161 * auVar91._0_4_ * -1.0 + fVar100 * fVar157 * fVar98;
      fVar115 = fVar157 * auVar91._0_4_ * 1.0 + fVar100 * fVar161 * fVar98;
      fVar116 = auVar91._0_4_ * 0.0 * 0.0 + auVar91._4_4_ * 1.0 * fVar98;
      fVar113 = auVar91._0_4_ * 0.0 * 0.0 + fVar98 * 0.0;
      fVar117 = fVar161 * fVar98 * 1.0 + fVar100 * fVar157 * auVar91._0_4_;
      fVar157 = fVar157 * fVar98 * -1.0 + fVar100 * fVar161 * auVar91._0_4_;
      fVar161 = fVar98 * 0.0 * 0.0 + auVar91._4_4_ * 1.0 * auVar91._0_4_;
      if ((uVar36 & 1) == 0) {
        fVar141 = fVar110 * 0.9238795 + fVar115 * 0.38268346 + fVar157 * 0.0;
        *(float *)(puVar29 + -3) = fVar112 + fVar116 * 0.0 + fVar161 * 0.0;
        *(undefined4 *)((long)puVar29 + -0x14) = 0;
        puVar29[-4] = CONCAT44(fVar110 + fVar115 * 0.0 + fVar157 * 0.0,
                               fVar162 + fVar114 * 0.0 + fVar117 * 0.0);
        puVar29[-1] = (ulong)(uint)(fVar112 * 0.9238795 + fVar116 * 0.38268346 + fVar161 * 0.0);
        puVar29[-2] = CONCAT17((char)((uint)fVar141 >> 0x18),
                               CONCAT16((char)((uint)fVar141 >> 0x10),
                                        CONCAT15((char)((uint)fVar141 >> 8),
                                                 CONCAT14(SUB41(fVar141,0),
                                                          fVar162 * 0.9238795 + fVar114 * 0.38268346
                                                          + fVar117 * 0.0))));
        fVar71 = fVar114 + fVar162 * -4.371139e-08;
        fVar79 = fVar115 + fVar110 * -4.371139e-08;
        fVar81 = fVar116 + fVar112 * -4.371139e-08;
        fVar113 = fVar113 + -0.0;
        *(float *)(puVar29 + 1) = fVar112 * 0.70710677 + fVar116 * 0.70710677 + fVar161 * 0.0;
        *(undefined4 *)((long)puVar29 + 0xc) = 0;
        *puVar29 = CONCAT44(fVar110 * 0.70710677 + fVar115 * 0.70710677 + fVar157 * 0.0,
                            fVar162 * 0.70710677 + fVar114 * 0.70710677 + fVar117 * 0.0);
        *(float *)(puVar29 + 3) = fVar112 * 0.38268343 + fVar116 * 0.9238795 + fVar161 * 0.0;
        *(undefined4 *)((long)puVar29 + 0x1c) = 0;
        puVar29[2] = CONCAT44(fVar110 * 0.38268343 + fVar115 * 0.9238795 + fVar157 * 0.0,
                              fVar162 * 0.38268343 + fVar114 * 0.9238795 + fVar117 * 0.0);
        fVar141 = fStack_ee8;
        fVar168 = fStack_ee4;
      }
      else {
        fVar100 = fVar110 * 0.70710677 + fVar115 * 0.70710677 + fVar157 * 0.0;
        fVar71 = fVar162 + fVar114 * 0.0;
        fVar79 = fVar110 + fVar115 * 0.0;
        fVar81 = fVar112 + fVar116 * 0.0;
        fVar113 = fVar113 * 0.0 + 0.0;
        *(float *)(puVar29 + -3) = fVar116 + fVar112 * -4.371139e-08 + fVar161 * 0.0;
        *(undefined4 *)((long)puVar29 + -0x14) = 0;
        puVar29[-4] = CONCAT44(fVar115 + fVar110 * -4.371139e-08 + fVar157 * 0.0,
                               fVar114 + fVar162 * -4.371139e-08 + fVar117 * 0.0);
        *(float *)(puVar29 + -1) = fVar112 * 0.38268343 + fVar116 * 0.9238795 + fVar161 * 0.0;
        *(undefined4 *)((long)puVar29 + -4) = 0;
        puVar29[-2] = CONCAT44(fVar110 * 0.38268343 + fVar115 * 0.9238795 + fVar157 * 0.0,
                               fVar162 * 0.38268343 + fVar114 * 0.9238795 + fVar117 * 0.0);
        puVar29[1] = (ulong)(uint)(fVar112 * 0.70710677 + fVar116 * 0.70710677 + fVar161 * 0.0);
        *puVar29 = CONCAT17((char)((uint)fVar100 >> 0x18),
                            CONCAT16((char)((uint)fVar100 >> 0x10),
                                     CONCAT15((char)((uint)fVar100 >> 8),
                                              CONCAT14(SUB41(fVar100,0),
                                                       fVar162 * 0.70710677 + fVar114 * 0.70710677 +
                                                       fVar117 * 0.0))));
        *(float *)(puVar29 + 3) = fVar112 * 0.9238795 + fVar116 * 0.38268346 + fVar161 * 0.0;
        *(undefined4 *)((long)puVar29 + 0x1c) = 0;
        puVar29[2] = CONCAT44(fVar110 * 0.9238795 + fVar115 * 0.38268346 + fVar157 * 0.0,
                              fVar162 * 0.9238795 + fVar114 * 0.38268346 + fVar117 * 0.0);
      }
      auVar74._0_8_ = CONCAT44(fVar79 + fVar157 * 0.0,fVar71 + fVar117 * 0.0);
      auVar74._8_4_ = fVar81 + fVar161 * 0.0;
      auVar74._12_4_ = fVar113 + (fVar98 * 0.0 * 0.0 + auVar91._0_4_ * 0.0) * 0.0;
      auVar196 = NEON_ext(auVar74,auVar74,8,1);
      uVar36 = uVar36 + 1;
      puVar29[5] = (ulong)auVar196._0_4_;
      puVar29[4] = auVar74._0_8_;
      puVar29 = puVar29 + 10;
      uVar129 = local_eb0;
      uVar130 = uStack_eaf;
      uVar131 = uStack_eae;
      uVar132 = uStack_ead;
    } while (uVar36 != 9);
    uRam00000071053351d8 = 0;
    _DAT_71053351d0 = 0x3f0000003f800000;
    uRam00000071053351e8 = 0;
    _DAT_71053351e0 = 0xbf0000003f800000;
    uRam00000071053351f8 = 0x3f248dbb;
    _DAT_71053351f0 = 0xbf0000003f441b7d;
    uRam0000007105335208 = 0x3f248dbb;
    _DAT_7105335200 = 0x3f0000003f441b7d;
    uRam0000007105335218 = 0x3f7c1c5d;
    _DAT_7105335210 = 0x3f0000003e31d0cf;
    uRam0000007105335228 = 0x3f7c1c5d;
    _DAT_7105335220 = 0xbf0000003e31d0cf;
    uRam0000007105335238 = 0x3f5db3d7;
    _DAT_7105335230 = 0xbf000000bf000001;
    uRam0000007105335248 = 0x3f5db3d7;
    _DAT_7105335240 = 0x3f000000bf000001;
    uRam0000007105335258 = 0x3eaf1d3f;
    _DAT_7105335250 = 0x3f000000bf708fb3;
    uRam0000007105335268 = 0x3eaf1d3f;
    _DAT_7105335260 = 0xbf000000bf708fb3;
    uRam0000007105335278 = 0xbeaf1d4c;
    _DAT_7105335270 = 0xbf000000bf708fb1;
    uRam0000007105335288 = 0xbeaf1d4c;
    _DAT_7105335280 = 0x3f000000bf708fb1;
    uRam0000007105335298 = 0xbf5db3d8;
    _DAT_7105335290 = 0x3f000000befffffd;
    uRam00000071053352a8 = 0xbf5db3d8;
    _DAT_71053352a0 = 0xbf000000befffffd;
    local_e40 = auVar134._0_4_;
    fStack_e3c = auVar134._4_4_;
    uRam00000071053352b8 = 0xbf7c1c5b;
    _DAT_71053352b0 = 0xbf0000003e31d0f2;
    uRam00000071053352c8 = 0xbf7c1c5b;
    _DAT_71053352c0 = 0x3f0000003e31d0f2;
    uRam00000071053352d8 = 0xbf248db7;
    _DAT_71053352d0 = 0x3f0000003f441b80;
    uRam00000071053352e8 = 0xbf248db7;
    _DAT_71053352e0 = 0xbf0000003f441b80;
    uRam0000007105335098 = 0;
    _DAT_7105335090 = 0x3f0000003f800000;
    uRam00000071053350a8 = 0x3f248dbb;
    _DAT_71053350a0 = 0x3f0000003f441b7d;
    uRam0000007105335118 = 0xbf248db7;
    _DAT_7105335110 = 0x3f0000003f441b80;
    uRam0000007105335128 = 0x343bbd2e;
    _DAT_7105335120 = 0x3f0000003f800000;
    uRam00000071053350b8 = 0x3f7c1c5d;
    _DAT_71053350b0 = 0x3f0000003e31d0cf;
    uRam00000071053350c8 = 0x3f5db3d7;
    _DAT_71053350c0 = 0x3f000000bf000001;
    uRam00000071053350d8 = 0x3eaf1d3f;
    _DAT_71053350d0 = 0x3f000000bf708fb3;
    uRam00000071053350e8 = 0xbeaf1d4c;
    _DAT_71053350e0 = 0x3f000000bf708fb1;
    uRam00000071053350f8 = 0xbf5db3d8;
    _DAT_71053350f0 = 0x3f000000befffffd;
    uRam0000007105335108 = 0xbf7c1c5b;
    _DAT_7105335100 = 0x3f0000003e31d0f2;
    uRam0000007105335138 = 0;
    _DAT_7105335130 = 0xbf0000003f800000;
    uRam0000007105335148 = 0x3f248dbb;
    _DAT_7105335140 = 0xbf0000003f441b7d;
    uRam0000007105335158 = 0x3f7c1c5d;
    _DAT_7105335150 = 0xbf0000003e31d0cf;
    uRam0000007105335168 = 0x3f5db3d7;
    _DAT_7105335160 = 0xbf000000bf000001;
    uRam0000007105335178 = 0x3eaf1d3f;
    _DAT_7105335170 = 0xbf000000bf708fb3;
    uRam0000007105335188 = 0xbeaf1d4c;
    _DAT_7105335180 = 0xbf000000bf708fb1;
    uRam0000007105335198 = 0xbf5db3d8;
    _DAT_7105335190 = 0xbf000000befffffd;
    uRam00000071053351a8 = 0xbf7c1c5b;
    _DAT_71053351a0 = 0xbf0000003e31d0f2;
    uRam00000071053351b8 = 0xbf248db7;
    _DAT_71053351b0 = 0xbf0000003f441b80;
    uRam00000071053351c8 = 0x343bbd2e;
    _DAT_71053351c0 = 0xbf0000003f800000;
    uVar106 = SUB168(_DAT_7104465860,8);
    uVar102 = SUB168(_DAT_7104465860,0);
    uVar169 = SUB168(_DAT_71044652b0,8);
    uVar163 = SUB168(_DAT_71044652b0,0);
    uVar62 = SUB168(_DAT_7104469070,8);
    uVar63 = SUB168(_DAT_7104469070,0);
    uVar82 = SUB168(_DAT_71044690c0,8);
    uVar69 = SUB168(_DAT_71044690c0,0);
    uVar87 = SUB168(_DAT_7104468270,8);
    uVar84 = SUB168(_DAT_7104468270,0);
    uRam0000007105335628 = 0x3f800000;
    _DAT_7105335620 = 0x3f800000bf800000;
    uVar158 = SUB168(_DAT_7104469520,8);
    uVar90 = SUB168(_DAT_7104469520,0);
    uVar142 = SUB168(_DAT_710446a0d0,8);
    uVar133 = SUB168(_DAT_710446a0d0,0);
    uRam0000007105335698 = 0x3f800000;
    _DAT_7105335690 = 0x3f800000bf800000;
    _DAT_71053355c0 = uVar63;
    uRam00000071053355c8 = uVar62;
    _DAT_71053355d0 = uVar84;
    uRam00000071053355d8 = uVar87;
    _DAT_71053355e0 = uVar102;
    uRam00000071053355e8 = uVar106;
    _DAT_71053355f0 = uVar90;
    uRam00000071053355f8 = uVar158;
    _DAT_7105335600 = uVar63;
    uRam0000007105335608 = uVar62;
    _DAT_7105335610 = uVar69;
    uRam0000007105335618 = uVar82;
    _DAT_7105335630 = uVar163;
    uRam0000007105335638 = uVar169;
    _DAT_7105335640 = uVar133;
    uRam0000007105335648 = uVar142;
    _DAT_7105335650 = uVar69;
    uRam0000007105335658 = uVar82;
    _DAT_7105335660 = uVar63;
    uRam0000007105335668 = uVar62;
    _DAT_7105335670 = uVar69;
    uRam0000007105335678 = uVar82;
    _DAT_7105335680 = uVar84;
    uRam0000007105335688 = uVar87;
    _DAT_71053356a0 = uVar90;
    uRam00000071053356a8 = uVar158;
    _DAT_71053356b0 = uVar133;
    uRam00000071053356b8 = uVar142;
    _DAT_71053356c0 = uVar102;
    uRam00000071053356c8 = uVar106;
    _DAT_71053356d0 = uVar163;
    uRam00000071053356d8 = uVar169;
    puVar59 = (uint *)je_aligned_alloc(0x10,0xd0);
    if (puVar59 == (uint *)0x0) {
      if (DAT_7105331f00 != (long *)0x0) {
        local_140 = (uint *)((ulong)local_140 & 0xffffffff00000000);
        local_e00 = 0xd0;
        uStack_dfc = 0;
        uVar45 = (**(code **)(*DAT_7105331f00 + 0x30))(DAT_7105331f00,&local_140,&local_e00);
        if (((uVar45 & 1) != 0) &&
           (puVar59 = (uint *)je_aligned_alloc(0x10,0xd0), puVar59 != (uint *)0x0))
        goto LAB_710374569c;
      }
      puVar59 = (uint *)0x0;
    }
LAB_710374569c:
    *(undefined8 **)(puVar59 + 0x30) = DAT_7105335088;
    puVar35 = (ushort *)je_aligned_alloc(0x10,&DAT_00001770);
    if (puVar35 == (ushort *)0x0) {
      if (DAT_7105331f00 != (long *)0x0) {
        local_140 = (uint *)((ulong)local_140 & 0xffffffff00000000);
        local_e00 = 6000;
        uStack_dfc = 0;
        uVar45 = (**(code **)(*DAT_7105331f00 + 0x30))(DAT_7105331f00,&local_140,&local_e00);
        if (((uVar45 & 1) != 0) &&
           (puVar35 = (ushort *)je_aligned_alloc(0x10,&DAT_00001770), puVar35 != (ushort *)0x0))
        goto LAB_7103745700;
      }
      puVar35 = (ushort *)0x0;
    }
LAB_7103745700:
    puVar41 = puVar35;
    uVar44 = 0;
    do {
      if ((uVar44 & 1) == 0) {
        *puVar41 = uVar44;
        uVar4 = uVar44 + 1;
      }
      else {
        *puVar41 = uVar44 + 1;
        uVar4 = uVar44;
      }
      uVar43 = uVar44 + 1;
      puVar41[1] = uVar4;
      puVar41[2] = uVar44 + 2;
      puVar41 = puVar41 + 3;
      uVar44 = uVar43;
    } while (uVar43 < 1000);
    *(ushort **)(puVar59 + 0x32) = puVar35;
    puVar59[6] = 0;
    puVar59[7] = 0;
    puVar29 = (undefined8 *)je_aligned_alloc(0x10,0x1000);
    if (puVar29 == (undefined8 *)0x0) {
      if (DAT_7105331f00 != (long *)0x0) {
        local_140 = (uint *)((ulong)local_140 & 0xffffffff00000000);
        local_e00 = 0x1000;
        uStack_dfc = 0;
        uVar45 = (**(code **)(*DAT_7105331f00 + 0x30))(DAT_7105331f00,&local_140,&local_e00);
        if (((uVar45 & 1) != 0) &&
           (puVar29 = (undefined8 *)je_aligned_alloc(0x10,0x1000), puVar29 != (undefined8 *)0x0))
        goto LAB_71037457b4;
      }
      puVar29 = (undefined8 *)0x0;
    }
LAB_71037457b4:
    *(undefined8 **)(puVar59 + 2) = puVar29;
    puVar35 = (ushort *)je_aligned_alloc(0x10,0x540);
    if (puVar35 == (ushort *)0x0) {
      if (DAT_7105331f00 != (long *)0x0) {
        local_140 = (uint *)((ulong)local_140 & 0xffffffff00000000);
        local_e00 = 0x540;
        uStack_dfc = 0;
        uVar45 = (**(code **)(*DAT_7105331f00 + 0x30))(DAT_7105331f00,&local_140,&local_e00);
        if (((uVar45 & 1) != 0) &&
           (puVar35 = (ushort *)je_aligned_alloc(0x10,0x540), puVar35 != (ushort *)0x0))
        goto LAB_7103745810;
      }
      puVar35 = (ushort *)0x0;
    }
LAB_7103745810:
    *(ushort **)(puVar59 + 4) = puVar35;
    puVar59[0] = 0;
    puVar59[1] = 0;
    auVar18._4_4_ = fVar70;
    auVar18._0_4_ = fVar70;
    auVar18._8_4_ = fStack_ef8;
    auVar18._12_4_ = fStack_ef4;
    uVar44 = 0;
    iVar23 = 0;
    do {
      fVar141 = (float)iVar23;
      iVar23 = iVar23 + 1;
      fVar168 = fVar141 * 6.2831855 * 0.0625;
      fVar141 = (float)iVar23 * 6.2831855 * 0.0625;
      auVar165._0_4_ = fVar153 * 0.0;
      auVar165._4_4_ = fVar168 * fVar153;
      auVar165._8_4_ = fVar153 * 0.0;
      auVar165._12_4_ = fVar153 * 0.0;
      auVar177._0_4_ = fVar153 * 0.0;
      auVar177._4_4_ = fVar141 * fVar153;
      auVar177._8_4_ = fVar153 * 0.0;
      auVar177._12_4_ = fVar153 * 0.0;
      auVar64._8_4_ = 0x3f000000;
      auVar64._0_8_ = 0x3f0000003f000000;
      auVar64._12_4_ = 0x3f000000;
      auVar145 = NEON_fcmge(auVar165,0,4);
      auVar196 = NEON_fcmge(auVar177,0,4);
      auVar8._8_4_ = 0xbf000000;
      auVar8._0_8_ = 0xbf000000bf000000;
      auVar8._12_4_ = 0xbf000000;
      auVar145 = NEON_bsl(auVar145,auVar64,auVar8,1);
      uVar4 = uVar44 | 2;
      auVar9._8_4_ = 0xbf000000;
      auVar9._0_8_ = 0xbf000000bf000000;
      auVar9._12_4_ = 0xbf000000;
      auVar196 = NEON_bsl(auVar196,auVar64,auVar9,1);
      auVar11._4_4_ = fVar99;
      auVar11._0_4_ = fVar99;
      auVar11._8_4_ = fVar99;
      auVar10._4_4_ = fVar99;
      auVar10._0_4_ = fVar99;
      auVar10._8_4_ = fVar99;
      auVar166._0_4_ = (int)(auVar165._0_4_ + auVar145._0_4_);
      auVar166._4_4_ = (int)(auVar165._4_4_ + auVar145._4_4_);
      auVar166._8_4_ = (int)(auVar165._8_4_ + auVar145._8_4_);
      auVar166._12_4_ = (int)(auVar165._12_4_ + auVar145._12_4_);
      auVar174._0_4_ = (int)(auVar177._0_4_ + auVar196._0_4_);
      auVar174._4_4_ = (int)(auVar177._4_4_ + auVar196._4_4_);
      auVar174._8_4_ = (int)(auVar177._8_4_ + auVar196._8_4_);
      auVar174._12_4_ = (int)(auVar177._12_4_ + auVar196._12_4_);
      auVar145 = NEON_scvtf(auVar166,4);
      auVar159._0_4_ = 0.0 - auVar145._0_4_ * fVar160;
      auVar159._4_4_ = fVar168 - auVar145._4_4_ * fVar160;
      auVar159._8_4_ = 0.0 - auVar145._8_4_ * fStack_e98;
      auVar159._12_4_ = 0.0 - auVar145._12_4_ * fStack_e94;
      auVar145 = NEON_scvtf(auVar174,4);
      auVar171._0_4_ = 0.0 - auVar145._0_4_ * fVar160;
      auVar171._4_4_ = fVar141 - auVar145._4_4_ * fVar160;
      auVar171._8_4_ = 0.0 - auVar145._8_4_ * fStack_e98;
      auVar171._12_4_ = 0.0 - auVar145._12_4_ * fStack_e94;
      auVar10._12_4_ = fVar99;
      auVar145 = NEON_fcmgt(auVar159,auVar10,4);
      auVar178._0_4_ = fVar68 - auVar159._0_4_;
      auVar178._4_4_ = fVar68 - auVar159._4_4_;
      auVar178._8_4_ = 0.0 - auVar159._8_4_;
      auVar178._12_4_ = 0.0 - auVar159._12_4_;
      auVar11._12_4_ = fVar99;
      auVar103 = NEON_fcmgt(auVar171,auVar11,4);
      fVar141 = (float)((ulong)uStack_f48 >> 0x20);
      auVar17._4_4_ = fVar101;
      auVar17._0_4_ = fVar101;
      auVar17._8_8_ = auVar193._8_8_;
      auVar182._0_4_ = fVar68 - auVar171._0_4_;
      auVar182._4_4_ = fVar68 - auVar171._4_4_;
      auVar182._8_4_ = 0.0 - auVar171._8_4_;
      auVar182._12_4_ = 0.0 - auVar171._12_4_;
      auVar180 = NEON_bsl(auVar145,auVar178,auVar159,1);
      auVar196 = NEON_bsl(auVar145,auVar134,auVar18,1);
      auVar104 = NEON_fcmgt(auVar17,auVar180,4);
      auVar191 = NEON_bsl(auVar103,auVar134,auVar18,1);
      auVar194._0_4_ = fVar97 - auVar180._0_4_;
      auVar194._4_4_ = fVar97 - auVar180._4_4_;
      auVar194._8_4_ = (float)uStack_f48 - auVar180._8_4_;
      auVar194._12_4_ = fVar141 - auVar180._12_4_;
      auVar103 = NEON_bsl(auVar103,auVar182,auVar171,1);
      auVar111._0_4_ = fVar97 - auVar103._0_4_;
      auVar111._4_4_ = fVar97 - auVar103._4_4_;
      auVar111._8_4_ = (float)uStack_f48 - auVar103._8_4_;
      auVar111._12_4_ = fVar141 - auVar103._12_4_;
      fVar168 = (float)(CONCAT17(uStack_f2d,
                                 CONCAT16(uStack_f2e,CONCAT15(uStack_f2f,CONCAT14(local_f30,fVar89))
                                         )) >> 0x20);
      fVar141 = (float)(CONCAT17(uStack_ead,
                                 CONCAT16(uStack_eae,
                                          CONCAT15(uStack_eaf,CONCAT14(local_eb0,fVar108)))) >> 0x20
                       );
      auVar145 = NEON_fcmgt(auVar17,auVar103,4);
      auVar179 = NEON_bsl(auVar104,auVar134,auVar196,1);
      auVar104 = NEON_bsl(auVar104,auVar194,auVar180,1);
      auVar196 = NEON_bsl(auVar145,auVar134,auVar191,1);
      fVar116 = auVar104._0_4_;
      fVar71 = fVar116 * fVar116;
      fVar117 = auVar104._4_4_;
      fVar79 = fVar117 * fVar117;
      fVar98 = auVar104._8_4_;
      fVar81 = fVar98 * fVar98;
      fVar100 = auVar104._12_4_;
      fVar195 = fVar100 * fVar100;
      auVar145 = NEON_bsl(auVar145,auVar111,auVar103,1);
      fVar157 = auVar145._0_4_;
      fVar112 = fVar157 * fVar157;
      fVar161 = auVar145._4_4_;
      fVar113 = fVar161 * fVar161;
      fVar162 = auVar145._8_4_;
      fVar114 = fVar162 * fVar162;
      fVar110 = auVar145._12_4_;
      fVar115 = fVar110 * fVar110;
      auVar175._0_4_ =
           (fVar70 + fVar71 * (fVar70 + fVar71 * (fVar83 + fVar71 * (fVar83 + fVar71 * (fVar80 + 
                                                  fVar71 * fVar108))))) * auVar179._0_4_;
      auVar175._4_4_ =
           (fVar70 + fVar79 * (fVar70 + fVar79 * (fVar83 + fVar79 * (fVar83 + fVar79 * (fVar80 + 
                                                  fVar79 * fVar141))))) * auVar179._4_4_;
      auVar175._8_4_ =
           (fStack_ef8 +
           fVar81 * (fStack_f08 +
                    fVar81 * (fStack_ec8 +
                             fVar81 * (fStack_ed8 + fVar81 * (fStack_eb8 + fVar81 * fVar89))))) *
           auVar179._8_4_;
      auVar175._12_4_ =
           (fStack_ef4 +
           fVar195 * (fStack_f04 +
                     fVar195 * (fStack_ec4 +
                               fVar195 * (fStack_ed4 + fVar195 * (fStack_eb4 + fVar195 * fVar168))))
           ) * auVar179._12_4_;
      auVar167._0_4_ =
           (fVar70 + fVar71 * (fVar88 + fVar71 * (fVar108 +
                                                 fVar71 * (fVar71 * (fVar186 + fVar71 * fVar120) +
                                                          0.38268346)))) * fVar116;
      auVar167._4_4_ =
           (fVar70 + fVar79 * (fVar88 + fVar79 * (fVar108 +
                                                 fVar79 * (fVar79 * (fVar186 + fVar79 * fVar120) +
                                                          0.38268346)))) * fVar117;
      auVar167._8_4_ =
           (fStack_ef8 +
           fVar81 * (fStack_ee8 +
                    fVar81 * (fVar108 +
                             fVar81 * (fStack_f88 + fVar81 * (fVar186 + fVar81 * fStack_f58))))) *
           fVar98;
      auVar167._12_4_ =
           (fStack_ef4 +
           fVar195 * (fStack_ee4 +
                     fVar195 * (fVar108 +
                               fVar195 * (fStack_f84 + fVar195 * (fVar186 + fVar195 * fStack_f54))))
           ) * fVar100;
      auVar172._0_4_ =
           (fVar70 + fVar112 * (fVar88 + fVar112 * (fVar108 +
                                                   fVar112 * (fVar112 * (fVar186 + fVar112 * fVar120
                                                                        ) + 0.38268346)))) * fVar157
      ;
      auVar172._4_4_ =
           (fVar70 + fVar113 * (fVar88 + fVar113 * (fVar108 +
                                                   fVar113 * (fVar113 * (fVar186 + fVar113 * fVar120
                                                                        ) + 0.38268346)))) * fVar161
      ;
      auVar172._8_4_ =
           (fStack_ef8 +
           fVar114 * (fStack_ee8 +
                     fVar114 * (fVar108 +
                               fVar114 * (fStack_f88 + fVar114 * (fVar186 + fVar114 * fStack_f58))))
           ) * fVar162;
      auVar172._12_4_ =
           (fStack_ef4 +
           fVar115 * (fStack_ee4 +
                     fVar115 * (fVar108 +
                               fVar115 * (fStack_f84 + fVar115 * (fVar186 + fVar115 * fStack_f54))))
           ) * fVar110;
      auVar145 = NEON_ext(auVar167,auVar167,8,1);
      fVar183 = (fVar70 + fVar112 * (fVar70 + fVar112 * (fVar83 + fVar112 * (fVar83 + fVar112 * (
                                                  fVar80 + fVar112 * fVar108))))) * auVar196._0_4_;
      fVar184 = (fVar70 + fVar113 * (fVar70 + fVar113 * (fVar83 + fVar113 * (fVar83 + fVar113 * (
                                                  fVar80 + fVar113 * fVar141))))) * auVar196._4_4_;
      fVar157 = (fStack_ef8 +
                fVar114 * (fStack_f08 +
                          fVar114 * (fStack_ec8 +
                                    fVar114 * (fStack_ed8 +
                                              fVar114 * (fStack_eb8 + fVar114 * fVar89))))) *
                auVar196._8_4_;
      fVar161 = (fStack_ef4 +
                fVar115 * (fStack_f04 +
                          fVar115 * (fStack_ec4 +
                                    fVar115 * (fStack_ed4 +
                                              fVar115 * (fStack_eb4 + fVar115 * fVar168))))) *
                auVar196._12_4_;
      auVar196 = NEON_ext(auVar175,auVar175,8,1);
      fVar141 = auVar196._0_4_;
      fVar168 = auVar145._0_4_;
      auVar196 = NEON_ext(auVar172,auVar172,8,1);
      auVar14._4_4_ = fVar184;
      auVar14._0_4_ = fVar183;
      auVar14._8_4_ = fVar157;
      auVar14._12_4_ = fVar161;
      auVar15._4_4_ = fVar184;
      auVar15._0_4_ = fVar183;
      auVar15._8_4_ = fVar157;
      auVar15._12_4_ = fVar161;
      auVar145 = NEON_ext(auVar14,auVar15,8,1);
      fVar157 = auVar196._0_4_;
      fVar161 = auVar145._0_4_;
      fVar162 = auVar175._4_4_ * fVar141;
      fVar110 = auVar175._4_4_ * fVar168;
      fVar112 = auVar167._4_4_ * -1.0;
      fVar113 = fVar184 * fVar161;
      fVar114 = fVar184 * fVar157;
      fVar115 = auVar172._4_4_ * -1.0;
      fVar100 = fVar168 * auVar175._0_4_ * -1.0 + auVar167._4_4_ * fVar141 * auVar167._0_4_;
      fVar71 = fVar141 * auVar175._0_4_ * 1.0 + auVar167._4_4_ * fVar168 * auVar167._0_4_;
      fVar79 = auVar175._0_4_ * 0.0 * 0.0 + auVar175._4_4_ * 1.0 * auVar167._0_4_;
      fVar116 = fVar168 * auVar167._0_4_ * 1.0 + auVar167._4_4_ * fVar141 * auVar175._0_4_;
      fVar117 = fVar141 * auVar167._0_4_ * -1.0 + auVar167._4_4_ * fVar168 * auVar175._0_4_;
      fVar98 = auVar167._0_4_ * 0.0 * 0.0 + auVar175._4_4_ * 1.0 * auVar175._0_4_;
      fVar141 = fVar162 * 0.9238795;
      fVar168 = fVar110 * 0.9238795;
      fVar81 = fVar157 * fVar183 * -1.0 + auVar172._4_4_ * fVar161 * auVar172._0_4_;
      fVar195 = fVar161 * fVar183 * 1.0 + auVar172._4_4_ * fVar157 * auVar172._0_4_;
      fVar181 = fVar183 * 0.0 * 0.0 + fVar184 * 1.0 * auVar172._0_4_;
      fVar185 = fVar157 * auVar172._0_4_ * 1.0 + auVar172._4_4_ * fVar161 * fVar183;
      fVar161 = fVar161 * auVar172._0_4_ * -1.0 + auVar172._4_4_ * fVar157 * fVar183;
      fVar183 = auVar172._0_4_ * 0.0 * 0.0 + fVar184 * 1.0 * fVar183;
      auVar200._0_4_ = fVar162 * 0.70710677 + fVar100 * 0.70710677 + fVar116 * 0.0;
      auVar200._4_4_ = fVar110 * 0.70710677 + fVar71 * 0.70710677 + fVar117 * 0.0;
      auVar200._8_4_ = fVar112 * 0.70710677 + fVar79 * 0.70710677 + fVar98 * 0.0;
      fVar157 = fVar168 + fVar71 * -0.70710677 + fVar117 * 0.0;
      auVar200._12_4_ = 0;
      *(float *)(puVar29 + 1) = fVar79 + fVar112 * 0.0 + fVar98 * 0.0;
      *(undefined4 *)((long)puVar29 + 0xc) = 0;
      *puVar29 = CONCAT44(fVar71 + fVar110 * 0.0 + fVar117 * 0.0,
                          fVar100 + fVar162 * 0.0 + fVar116 * 0.0);
      puVar59[1] = puVar59[1] + 1;
      puVar29[3] = (ulong)(uint)(fVar112 * fStack_f98 + fVar79 * 0.9238795 + fVar98 * 0.0);
      puVar29[2] = CONCAT44(fVar110 * 0.38268343 + fVar71 * 0.9238795 + fVar117 * 0.0,
                            fVar162 * 0.38268343 + fVar100 * 0.9238795 + fVar116 * 0.0);
      puVar29[5] = (ulong)(uint)(fVar115 * fStack_f98 + fVar181 * 0.9238795 + fVar183 * 0.0);
      puVar29[4] = CONCAT44(fVar114 * 0.38268343 + fVar195 * 0.9238795 + fVar161 * 0.0,
                            fVar113 * 0.38268343 + fVar81 * 0.9238795 + fVar185 * 0.0);
      puVar59[1] = puVar59[1] + 2;
      *(undefined1 (*) [16])(puVar29 + 6) = auVar200;
      puVar29[9] = (ulong)(uint)(fVar115 * 0.70710677 + fVar181 * 0.70710677 + fVar183 * 0.0);
      puVar29[8] = CONCAT44(fVar114 * 0.70710677 + fVar195 * 0.70710677 + fVar161 * 0.0,
                            fVar113 * 0.70710677 + fVar81 * 0.70710677 + fVar185 * 0.0);
      puVar59[1] = puVar59[1] + 2;
      puVar29[0xb] = (ulong)(uint)(fVar112 * 0.9238795 + fStack_fa8 * fVar79 + fVar98 * 0.0);
      puVar29[10] = CONCAT44((float)(CONCAT17((char)((uint)fVar168 >> 0x18),
                                              CONCAT16((char)((uint)fVar168 >> 0x10),
                                                       CONCAT15((char)((uint)fVar168 >> 8),
                                                                CONCAT14(SUB41(fVar168,0),fVar141)))
                                             ) >> 0x20) + fVar71 * -4.371139e-08 + fVar117 * 0.0,
                             fVar141 + fVar100 * -4.371139e-08 + fVar116 * 0.0);
      *(float *)(puVar29 + 0xd) = fVar115 * 0.9238795 + fStack_fa8 * fVar181 + fVar183 * 0.0;
      *(undefined4 *)((long)puVar29 + 0x6c) = 0;
      puVar29[0xc] = CONCAT44(fVar114 * 0.9238795 + fVar195 * -4.371139e-08 + fVar161 * 0.0,
                              fVar113 * 0.9238795 + fVar81 * -4.371139e-08 + fVar185 * 0.0);
      puVar59[1] = puVar59[1] + 2;
      puVar29[0xf] = (ulong)(uint)(fVar112 + fStack_fb8 * fVar79 + fVar98 * 0.0);
      puVar29[0xe] = CONCAT44(fVar110 + fVar71 * -0.38268352 + fVar117 * 0.0,
                              fVar162 + fVar100 * -0.38268352 + fVar116 * 0.0);
      puVar29[0x11] = (ulong)(uint)(fVar115 + fStack_fb8 * fVar181 + fVar183 * 0.0);
      puVar29[0x10] =
           CONCAT44(fVar114 + fVar195 * -0.38268352 + fVar161 * 0.0,
                    fVar113 + fVar81 * -0.38268352 + fVar185 * 0.0);
      puVar59[1] = puVar59[1] + 2;
      puVar29[0x13] = (ulong)(uint)(fVar112 * 0.9238795 + fStack_fc8 * fVar79 + fVar98 * 0.0);
      puVar29[0x12] =
           CONCAT17((char)((uint)fVar157 >> 0x18),
                    CONCAT16((char)((uint)fVar157 >> 0x10),
                             CONCAT15((char)((uint)fVar157 >> 8),
                                      CONCAT14(SUB41(fVar157,0),
                                               fVar141 + fVar100 * -0.70710677 + fVar116 * 0.0))));
      *(float *)(puVar29 + 0x15) = fVar115 * 0.9238795 + fStack_fc8 * fVar181 + fVar183 * 0.0;
      *(undefined4 *)((long)puVar29 + 0xac) = 0;
      puVar29[0x14] =
           CONCAT44(fVar114 * 0.9238795 + fVar195 * -0.70710677 + fVar161 * 0.0,
                    fVar113 * 0.9238795 + fVar81 * -0.70710677 + fVar185 * 0.0);
      puVar59[1] = puVar59[1] + 2;
      puVar29[0x17] = (ulong)(uint)(fVar112 * 0.70710677 + fStack_fd8 * fVar79 + fVar98 * 0.0);
      puVar29[0x16] =
           CONCAT44(fVar110 * 0.70710677 + fVar71 * 0.38268328 + fVar117 * 0.0,
                    fVar162 * 0.70710677 + fVar100 * 0.38268328 + fVar116 * 0.0);
      puVar29[0x19] = (ulong)(uint)(fVar115 * 0.70710677 + fStack_fd8 * fVar181 + fVar183 * 0.0);
      puVar29[0x18] =
           CONCAT44(fVar114 * 0.70710677 + fVar195 * 0.38268328 + fVar161 * 0.0,
                    fVar113 * 0.70710677 + fVar81 * 0.38268328 + fVar185 * 0.0);
      puVar59[1] = puVar59[1] + 2;
      puVar29[0x1b] = (ulong)(uint)(fVar112 * fStack_fe8 + fStack_ff8 * fVar79 + fVar98 * 0.0);
      puVar29[0x1a] =
           CONCAT44(fVar110 * -0.9238796 + fVar71 * -8.742278e-08 + fVar117 * 0.0,
                    fVar162 * -0.9238796 + fVar100 * -8.742278e-08 + fVar116 * 0.0);
      puVar29[0x1d] = (ulong)(uint)(fVar115 * fStack_fe8 + fStack_ff8 * fVar181 + fVar183 * 0.0);
      puVar29[0x1c] =
           CONCAT44(fVar114 * -0.9238796 + fVar195 * -8.742278e-08 + fVar161 * 0.0,
                    fVar113 * -0.9238796 + fVar81 * -8.742278e-08 + fVar185 * 0.0);
      puVar59[1] = puVar59[1] + 2;
      puVar29[0x1f] = (ulong)(uint)(fVar112 * fStack_1008 + auVar134._8_4_ * fVar79 + fVar98 * 0.0);
      puVar29[0x1e] =
           CONCAT44(fVar110 * -8.742278e-08 + fStack_e3c * fVar71 + fVar117 * 0.0,
                    fVar162 * -8.742278e-08 + local_e40 * fVar100 + fVar116 * 0.0);
      puVar59[1] = puVar59[1] + 1;
      *puVar35 = uVar44 | 1;
      puVar35[1] = uVar44;
      puVar35[2] = uVar4;
      *puVar59 = *puVar59 + 3;
      uVar43 = uVar44 | 3;
      puVar35[4] = uVar44 | 1;
      uVar5 = uVar44 | 4;
      puVar35[5] = uVar4;
      puVar35[6] = uVar43;
      puVar35[3] = uVar43;
      puVar35[7] = uVar4;
      puVar35[8] = uVar5;
      *puVar59 = *puVar59 + 6;
      uVar4 = uVar44 | 5;
      puVar35[10] = uVar43;
      uVar43 = uVar44 | 6;
      puVar35[0xb] = uVar5;
      puVar35[0xc] = uVar4;
      puVar35[9] = uVar4;
      puVar35[0xd] = uVar5;
      puVar35[0xe] = uVar43;
      uVar5 = uVar44 | 7;
      *puVar59 = *puVar59 + 6;
      puVar35[0x10] = uVar4;
      uVar4 = uVar44 | 8;
      puVar35[0xf] = uVar5;
      puVar35[0x11] = uVar43;
      puVar35[0x12] = uVar5;
      puVar35[0x13] = uVar43;
      uVar43 = uVar44 | 9;
      puVar35[0x14] = uVar4;
      *puVar59 = *puVar59 + 6;
      puVar35[0x16] = uVar5;
      uVar5 = uVar44 | 10;
      puVar35[0x15] = uVar43;
      puVar35[0x17] = uVar4;
      puVar35[0x18] = uVar43;
      puVar35[0x19] = uVar4;
      uVar4 = uVar44 | 0xb;
      puVar35[0x1a] = uVar5;
      *puVar59 = *puVar59 + 6;
      puVar35[0x1c] = uVar43;
      uVar43 = uVar44 | 0xc;
      puVar35[0x1b] = uVar4;
      puVar35[0x1d] = uVar5;
      puVar35[0x1e] = uVar4;
      puVar35[0x1f] = uVar5;
      uVar5 = uVar44 | 0xd;
      puVar35[0x20] = uVar43;
      *puVar59 = *puVar59 + 6;
      puVar35[0x22] = uVar4;
      uVar4 = uVar44 | 0xe;
      puVar35[0x21] = uVar5;
      puVar35[0x23] = uVar43;
      puVar35[0x24] = uVar5;
      puVar35[0x25] = uVar43;
      uVar43 = uVar44 | 0xf;
      uVar44 = uVar44 + 0x10;
      puVar35[0x26] = uVar4;
      *puVar59 = *puVar59 + 6;
      puVar35[0x27] = uVar43;
      puVar35[0x28] = uVar5;
      puVar35[0x29] = uVar4;
      puVar29 = puVar29 + 0x20;
      puVar35 = puVar35 + 0x2a;
      *puVar59 = *puVar59 + 3;
    } while (iVar23 != 0x10);
    *(undefined8 *)(puVar59 + 10) = *(undefined8 *)(puVar59 + 2);
    puVar59[0xe] = 0;
    puVar59[0xf] = 0;
    puVar59[9] = puVar59[1];
    puVar35 = (ushort *)je_aligned_alloc(0x10,0x2a0);
    if (puVar35 == (ushort *)0x0) {
      if (DAT_7105331f00 != (long *)0x0) {
        local_140 = (uint *)((ulong)local_140 & 0xffffffff00000000);
        local_e00 = 0x2a0;
        uStack_dfc = 0;
        uVar45 = (**(code **)(*DAT_7105331f00 + 0x30))(DAT_7105331f00,&local_140,&local_e00);
        if (((uVar45 & 1) != 0) &&
           (puVar35 = (ushort *)je_aligned_alloc(0x10,0x2a0), puVar35 != (ushort *)0x0))
        goto LAB_7103745f68;
      }
      puVar35 = (ushort *)0x0;
    }
LAB_7103745f68:
    uVar44 = 0;
    uVar36 = 0;
    *(ushort **)(puVar59 + 0xc) = puVar35;
    puVar59[8] = 0;
    do {
      if ((uVar36 & 1) != 0) {
        uVar4 = uVar44 | 2;
        *puVar35 = uVar44 | 1;
        puVar35[1] = uVar44;
        puVar35[2] = uVar4;
        uVar43 = uVar44 | 3;
        puVar59[8] = puVar59[8] + 3;
        puVar35[4] = uVar44 | 1;
        uVar5 = uVar44 | 4;
        puVar35[3] = uVar43;
        puVar35[5] = uVar4;
        puVar35[6] = uVar43;
        puVar35[7] = uVar4;
        uVar4 = uVar44 | 5;
        puVar35[8] = uVar5;
        puVar59[8] = puVar59[8] + 6;
        puVar35[10] = uVar43;
        uVar43 = uVar44 | 6;
        puVar35[9] = uVar4;
        puVar35[0xb] = uVar5;
        puVar35[0xc] = uVar4;
        puVar35[0xd] = uVar5;
        uVar5 = uVar44 | 7;
        puVar35[0xe] = uVar43;
        puVar59[8] = puVar59[8] + 6;
        puVar35[0x10] = uVar4;
        uVar4 = uVar44 | 8;
        puVar35[0xf] = uVar5;
        puVar35[0x11] = uVar43;
        puVar35[0x12] = uVar5;
        puVar35[0x13] = uVar43;
        uVar43 = uVar44 | 9;
        puVar35[0x14] = uVar4;
        puVar59[8] = puVar59[8] + 6;
        puVar35[0x16] = uVar5;
        uVar5 = uVar44 | 10;
        puVar35[0x15] = uVar43;
        puVar35[0x17] = uVar4;
        puVar35[0x18] = uVar43;
        puVar35[0x19] = uVar4;
        uVar4 = uVar44 | 0xb;
        puVar35[0x1a] = uVar5;
        puVar59[8] = puVar59[8] + 6;
        puVar35[0x1c] = uVar43;
        uVar43 = uVar44 | 0xc;
        puVar35[0x1b] = uVar4;
        puVar35[0x1d] = uVar5;
        puVar35[0x1e] = uVar4;
        puVar35[0x1f] = uVar5;
        uVar5 = uVar44 | 0xd;
        puVar35[0x20] = uVar43;
        puVar59[8] = puVar59[8] + 6;
        puVar35[0x22] = uVar4;
        puVar35[0x21] = uVar5;
        puVar35[0x23] = uVar43;
        puVar35[0x24] = uVar5;
        puVar35[0x25] = uVar43;
        puVar35[0x26] = uVar44 | 0xe;
        puVar59[8] = puVar59[8] + 6;
        puVar35[0x27] = uVar44 | 0xf;
        puVar35[0x28] = uVar5;
        puVar35[0x29] = uVar44 | 0xe;
        puVar35 = puVar35 + 0x2a;
        puVar59[8] = puVar59[8] + 3;
      }
      uVar36 = uVar36 + 1;
      uVar44 = uVar44 + 0x10;
    } while (uVar36 != 0x10);
    *(undefined8 *)(puVar59 + 0x12) = *(undefined8 *)(puVar59 + 2);
    puVar59[0x11] = puVar59[1];
    puVar35 = (ushort *)je_aligned_alloc(0x10,0x2a0);
    if (puVar35 == (ushort *)0x0) {
      if (DAT_7105331f00 != (long *)0x0) {
        local_140 = (uint *)((ulong)local_140 & 0xffffffff00000000);
        local_e00 = 0x2a0;
        uStack_dfc = 0;
        uVar45 = (**(code **)(*DAT_7105331f00 + 0x30))(DAT_7105331f00,&local_140,&local_e00);
        if (((uVar45 & 1) != 0) &&
           (puVar35 = (ushort *)je_aligned_alloc(0x10,0x2a0), puVar35 != (ushort *)0x0))
        goto LAB_710374613c;
      }
      puVar35 = (ushort *)0x0;
    }
LAB_710374613c:
    uVar36 = 0;
    uVar44 = 0;
    *(ushort **)(puVar59 + 0x14) = puVar35;
    puVar59[0x10] = 0;
    do {
      if ((uVar36 & 1) == 0) {
        uVar4 = uVar44 | 2;
        *puVar35 = uVar44 | 1;
        puVar35[1] = uVar44;
        puVar35[2] = uVar4;
        uVar43 = uVar44 | 3;
        puVar59[0x10] = puVar59[0x10] + 3;
        puVar35[4] = uVar44 | 1;
        uVar5 = uVar44 | 4;
        puVar35[3] = uVar43;
        puVar35[5] = uVar4;
        puVar35[6] = uVar43;
        puVar35[7] = uVar4;
        uVar4 = uVar44 | 5;
        puVar35[8] = uVar5;
        puVar59[0x10] = puVar59[0x10] + 6;
        puVar35[10] = uVar43;
        uVar43 = uVar44 | 6;
        puVar35[9] = uVar4;
        puVar35[0xb] = uVar5;
        puVar35[0xc] = uVar4;
        puVar35[0xd] = uVar5;
        uVar5 = uVar44 | 7;
        puVar35[0xe] = uVar43;
        puVar59[0x10] = puVar59[0x10] + 6;
        puVar35[0x10] = uVar4;
        uVar4 = uVar44 | 8;
        puVar35[0xf] = uVar5;
        puVar35[0x11] = uVar43;
        puVar35[0x12] = uVar5;
        puVar35[0x13] = uVar43;
        uVar43 = uVar44 | 9;
        puVar35[0x14] = uVar4;
        puVar59[0x10] = puVar59[0x10] + 6;
        puVar35[0x16] = uVar5;
        uVar5 = uVar44 | 10;
        puVar35[0x15] = uVar43;
        puVar35[0x17] = uVar4;
        puVar35[0x18] = uVar43;
        puVar35[0x19] = uVar4;
        uVar4 = uVar44 | 0xb;
        puVar35[0x1a] = uVar5;
        puVar59[0x10] = puVar59[0x10] + 6;
        puVar35[0x1c] = uVar43;
        uVar43 = uVar44 | 0xc;
        puVar35[0x1b] = uVar4;
        puVar35[0x1d] = uVar5;
        puVar35[0x1e] = uVar4;
        puVar35[0x1f] = uVar5;
        uVar5 = uVar44 | 0xd;
        puVar35[0x20] = uVar43;
        puVar59[0x10] = puVar59[0x10] + 6;
        puVar35[0x22] = uVar4;
        puVar35[0x21] = uVar5;
        puVar35[0x23] = uVar43;
        puVar35[0x24] = uVar5;
        puVar35[0x25] = uVar43;
        puVar35[0x26] = uVar44 | 0xe;
        puVar59[0x10] = puVar59[0x10] + 6;
        puVar35[0x27] = uVar44 | 0xf;
        puVar35[0x28] = uVar5;
        puVar35[0x29] = uVar44 | 0xe;
        puVar35 = puVar35 + 0x2a;
        puVar59[0x10] = puVar59[0x10] + 3;
      }
      uVar36 = uVar36 + 1;
      uVar44 = uVar44 + 0x10;
    } while (uVar36 != 0x10);
    uVar36 = puVar59[1] >> 1;
    lVar52 = (ulong)uVar36 << 4;
    if (uVar36 == 0) {
      lVar52 = 1;
    }
    puVar59[0x19] = uVar36;
    puVar59[0x1e] = 0;
    puVar59[0x1f] = 0;
    lVar49 = je_aligned_alloc(0x10,lVar52);
    if (lVar49 == 0) {
      if (DAT_7105331f00 != (long *)0x0) {
        local_140 = (uint *)((ulong)local_140 & 0xffffffff00000000);
        local_e00 = (uint)lVar52;
        uStack_dfc = (uint)((ulong)lVar52 >> 0x20);
        uVar45 = (**(code **)(*DAT_7105331f00 + 0x30))(DAT_7105331f00,&local_140,&local_e00);
        if (((uVar45 & 1) != 0) && (lVar49 = je_aligned_alloc(0x10,lVar52), lVar49 != 0))
        goto LAB_7103746318;
      }
      lVar49 = 0;
    }
LAB_7103746318:
    *(long *)(puVar59 + 0x1a) = lVar49;
    if (puVar59[0x19] != 0) {
      auVar92._8_4_ = 0x3f000000;
      auVar92._0_8_ = 0x3f0000003f000000;
      auVar92._12_4_ = 0x3f000000;
      auVar65._0_4_ = nn::util::detail::Float1Divided2Pi * 1.5707964;
      auVar65._4_4_ = nn::util::detail::Float1Divided2Pi * 0.0;
      auVar65._8_4_ = nn::util::detail::Float1Divided2Pi * 0.0;
      auVar65._12_4_ = nn::util::detail::Float1Divided2Pi * 0.0;
      auVar95._8_4_ = 0xbf000000;
      auVar95._0_8_ = 0xbf000000bf000000;
      auVar95._12_4_ = 0xbf000000;
      auVar145 = NEON_fcmge(auVar65,0,4);
      auVar145 = NEON_bsl(auVar145,auVar92,auVar95,1);
      auVar66._0_4_ = (int)(auVar65._0_4_ + auVar145._0_4_);
      auVar66._4_4_ = (int)(auVar65._4_4_ + auVar145._4_4_);
      auVar66._8_4_ = (int)(auVar65._8_4_ + auVar145._8_4_);
      auVar66._12_4_ = (int)(auVar65._12_4_ + auVar145._12_4_);
      auVar145 = NEON_scvtf(auVar66,4);
      auVar75._0_4_ = 1.5707964 - auVar145._0_4_ * nn::util::detail::Float2Pi;
      auVar75._4_4_ = 0.0 - auVar145._4_4_ * nn::util::detail::Float2Pi;
      auVar75._8_4_ = 0.0 - auVar145._8_4_ * nn::util::detail::Float2Pi;
      auVar75._12_4_ = 0.0 - auVar145._12_4_ * nn::util::detail::Float2Pi;
      auVar67._4_4_ = fVar99;
      auVar67._0_4_ = fVar99;
      auVar67._8_4_ = fVar99;
      auVar67._12_4_ = fVar99;
      auVar12._4_4_ = fVar70;
      auVar12._0_4_ = fVar70;
      auVar12._8_4_ = fStack_ef8;
      auVar145 = NEON_fcmgt(auVar75,auVar67,4);
      auVar86._0_4_ = fVar68 - auVar75._0_4_;
      auVar86._4_4_ = fVar68 - auVar75._4_4_;
      auVar86._8_4_ = fVar68 - auVar75._8_4_;
      auVar86._12_4_ = fVar68 - auVar75._12_4_;
      auVar103 = NEON_bsl(auVar145,auVar86,auVar75,1);
      auVar12._12_4_ = fStack_ef4;
      auVar145 = NEON_bsl(auVar145,auVar134,auVar12,1);
      auVar76._4_4_ = fVar101;
      auVar76._0_4_ = fVar101;
      auVar76._8_4_ = fVar101;
      auVar76._12_4_ = fVar101;
      auVar196 = NEON_fcmgt(auVar76,auVar103,4);
      auVar77._0_4_ = fVar97 - auVar103._0_4_;
      auVar77._4_4_ = fVar97 - auVar103._4_4_;
      auVar77._8_4_ = fVar97 - auVar103._8_4_;
      auVar77._12_4_ = fVar97 - auVar103._12_4_;
      auVar134 = NEON_bsl(auVar196,auVar134,auVar145,1);
      auVar145 = NEON_bsl(auVar196,auVar77,auVar103,1);
      fVar153 = auVar145._0_4_;
      fVar99 = fVar153 * fVar153;
      fVar157 = auVar145._4_4_;
      fVar68 = fVar157 * fVar157;
      fVar160 = auVar145._8_4_;
      fVar141 = fVar160 * fVar160;
      fVar161 = auVar145._12_4_;
      fVar168 = fVar161 * fVar161;
      uVar45 = 0;
      auVar78._0_4_ =
           (fVar70 + fVar99 * (fVar88 + fVar99 * (DAT_710744770c +
                                                 fVar99 * (fVar96 + fVar99 * (DAT_7107447704 -
                                                                             fVar99 * fVar61))))) *
           fVar153;
      auVar78._4_4_ =
           (fVar70 + fVar68 * (fVar88 + fVar68 * (DAT_710744770c +
                                                 fVar68 * (fVar96 + fVar68 * (DAT_7107447704 -
                                                                             fVar68 * fVar61))))) *
           fVar157;
      auVar78._8_4_ =
           (fStack_ef8 +
           fVar141 * (fVar88 + fVar141 * (DAT_710744770c +
                                         fVar141 * (fVar96 + fVar141 * (DAT_7107447704 -
                                                                       fVar141 * fVar61))))) *
           fVar160;
      auVar78._12_4_ =
           (fStack_ef4 +
           fVar168 * (fVar88 + fVar168 * (DAT_710744770c +
                                         fVar168 * (fVar96 + fVar168 * (DAT_7107447704 -
                                                                       fVar168 * fVar61))))) *
           fVar161;
      auVar93._0_4_ =
           (fVar70 + fVar99 * (fVar70 + fVar99 * (DAT_7107447714 +
                                                 fVar99 * (fVar83 + fVar99 * (DAT_710744770c -
                                                                             fVar99 * fVar119))))) *
           auVar134._0_4_;
      auVar93._4_4_ =
           (fVar70 + fVar68 * (fVar70 + fVar68 * (DAT_7107447714 +
                                                 fVar68 * (fVar83 + fVar68 * (DAT_710744770c -
                                                                             fVar68 * fVar119))))) *
           auVar134._4_4_;
      auVar93._8_4_ =
           (fStack_ef8 +
           fVar141 * (fVar70 + fVar141 * (DAT_7107447714 +
                                         fVar141 * (fVar83 + fVar141 * (DAT_710744770c -
                                                                       fVar141 * fVar119))))) *
           auVar134._8_4_;
      auVar93._12_4_ =
           (fStack_ef4 +
           fVar168 * (fVar70 + fVar168 * (DAT_7107447714 +
                                         fVar168 * (fVar83 + fVar168 * (DAT_710744770c -
                                                                       fVar168 * fVar119))))) *
           auVar134._12_4_;
      auVar134 = NEON_ext(auVar78,auVar78,8,1);
      auVar145 = NEON_ext(auVar93,auVar93,8,1);
      fVar99 = auVar145._0_4_;
      fVar68 = auVar134._0_4_;
      do {
        lVar52 = uVar45 * 0x10;
        uVar45 = uVar45 + 1;
        puVar29 = (undefined8 *)(*(long *)(puVar59 + 2) + lVar52);
        uVar13 = *puVar29;
        fVar61 = (float)uVar13;
        fVar141 = (float)((ulong)uVar13 >> 0x20);
        fVar119 = (float)puVar29[1];
        fVar168 = (fVar99 * auVar78._0_4_ * -1.0 + auVar78._4_4_ * fVar68 * auVar93._0_4_) * fVar119
                  + auVar93._4_4_ * fVar68 * fVar61 +
                    (fVar99 * auVar93._0_4_ * 1.0 + auVar78._4_4_ * fVar68 * auVar78._0_4_) *
                    fVar141 + 0.0;
        puVar29 = (undefined8 *)(*(long *)(puVar59 + 0x1a) + lVar52);
        puVar29[1] = (ulong)(uint)((auVar78._0_4_ * 0.0 * 0.0 + auVar93._4_4_ * 1.0 * auVar93._0_4_)
                                   * fVar119 +
                                   auVar78._4_4_ * -1.0 * fVar61 +
                                   (auVar93._0_4_ * 0.0 * 0.0 + auVar93._4_4_ * 1.0 * auVar78._0_4_)
                                   * fVar141 + 0.0);
        *puVar29 = CONCAT17((char)((uint)fVar168 >> 0x18),
                            CONCAT16((char)((uint)fVar168 >> 0x10),
                                     CONCAT15((char)((uint)fVar168 >> 8),
                                              CONCAT14(SUB41(fVar168,0),
                                                       (fVar68 * auVar78._0_4_ * 1.0 +
                                                       auVar78._4_4_ * fVar99 * auVar93._0_4_) *
                                                       fVar119 + auVar93._4_4_ * fVar99 * fVar61 +
                                                                 (fVar68 * auVar93._0_4_ * -1.0 +
                                                                 auVar78._4_4_ * fVar99 *
                                                                 auVar78._0_4_) * fVar141 + 0.0))));
      } while (uVar45 < puVar59[0x19]);
    }
    uVar3 = *puVar59;
    uVar36 = uVar3 & 0xfffffffe;
    if ((uVar3 & 0xfffffffe) == 0) {
      uVar36 = 1;
    }
    puVar59[0x18] = uVar3 >> 1;
    puVar34 = (undefined2 *)je_aligned_alloc(0x10,uVar36);
    if (puVar34 == (undefined2 *)0x0) {
      if (DAT_7105331f00 != (long *)0x0) {
        local_140 = (uint *)((ulong)local_140 & 0xffffffff00000000);
        uStack_dfc = 0;
        local_e00 = uVar36;
        uVar45 = (**(code **)(*DAT_7105331f00 + 0x30))(DAT_7105331f00,&local_140,&local_e00);
        if (((uVar45 & 1) != 0) &&
           (puVar34 = (undefined2 *)je_aligned_alloc(0x10,uVar36), puVar34 != (undefined2 *)0x0))
        goto LAB_71037465ec;
      }
      puVar34 = (undefined2 *)0x0;
    }
LAB_71037465ec:
    *(undefined2 **)(puVar59 + 0x1c) = puVar34;
    if (uVar3 >> 1 != 0) {
      puVar42 = *(undefined2 **)(puVar59 + 4);
      *puVar34 = *puVar42;
      if (1 < puVar59[0x18]) {
        uVar45 = 1;
        while( true ) {
          puVar34[uVar45] = puVar42[uVar45];
          if ((ulong)puVar59[0x18] <= uVar45 + 1) break;
          puVar34 = *(undefined2 **)(puVar59 + 0x1c);
          puVar42 = *(undefined2 **)(puVar59 + 4);
          uVar45 = uVar45 + 1;
        }
      }
    }
    puVar59[0x26] = 0;
    puVar59[0x27] = 0;
    puVar59[0x21] = 0x22;
    puVar29 = (undefined8 *)je_aligned_alloc(0x10,0x220);
    if (puVar29 == (undefined8 *)0x0) {
      if (DAT_7105331f00 != (long *)0x0) {
        local_140 = (uint *)((ulong)local_140 & 0xffffffff00000000);
        local_e00 = 0x220;
        uStack_dfc = 0;
        uVar45 = (**(code **)(*DAT_7105331f00 + 0x30))(DAT_7105331f00,&local_140,&local_e00);
        if (((uVar45 & 1) != 0) &&
           (puVar29 = (undefined8 *)je_aligned_alloc(0x10,0x220), puVar29 != (undefined8 *)0x0))
        goto LAB_710374669c;
      }
      puVar29 = (undefined8 *)0x0;
    }
LAB_710374669c:
    *(undefined8 **)(puVar59 + 0x22) = puVar29;
    puVar29[1] = 0x3e47c5c2;
    *puVar29 = 0x3f0000003f7b14be;
    puVar29[3] = 0x3e47c5c2;
    puVar29[2] = 0xbf0000003f7b14be;
    puVar29[5] = 0x3f0e39da;
    puVar29[4] = 0x3f0000003f54db31;
    puVar29[7] = 0x3f0e39da;
    puVar29[6] = 0xbf0000003f54db31;
    puVar29[9] = 0x3f54db32;
    puVar29[8] = 0x3f0000003f0e39d9;
    puVar29[0xb] = 0x3f54db32;
    puVar29[10] = 0xbf0000003f0e39d9;
    puVar29[0xd] = 0x3f7b14be;
    puVar29[0xc] = 0x3f0000003e47c5c4;
    puVar29[0xf] = 0x3f7b14be;
    puVar29[0xe] = 0xbf0000003e47c5c4;
    puVar29[0x11] = 0x3f7b14be;
    puVar29[0x10] = 0x3f000000be47c5c2;
    puVar29[0x13] = 0x3f7b14be;
    puVar29[0x12] = 0xbf000000be47c5c2;
    puVar29[0x15] = 0x3f54db30;
    puVar29[0x14] = 0x3f000000bf0e39dc;
    puVar29[0x17] = 0x3f54db30;
    puVar29[0x16] = 0xbf000000bf0e39dc;
    puVar29[0x19] = 0x3f0e39d9;
    puVar29[0x18] = 0x3f000000bf54db32;
    puVar29[0x1b] = 0x3f0e39d9;
    puVar29[0x1a] = 0xbf000000bf54db32;
    puVar29[0x1d] = 0x3e47c5b2;
    puVar29[0x1c] = 0x3f000000bf7b14bf;
    puVar29[0x1f] = 0x3e47c5b2;
    puVar29[0x1e] = 0xbf000000bf7b14bf;
    puVar29[0x21] = 0xbe47c5cd;
    puVar29[0x20] = 0x3f000000bf7b14be;
    puVar29[0x23] = 0xbe47c5cd;
    puVar29[0x22] = 0xbf000000bf7b14be;
    puVar29[0x25] = 0xbf0e39db;
    puVar29[0x24] = 0x3f000000bf54db30;
    puVar29[0x27] = 0xbf0e39db;
    puVar29[0x26] = 0xbf000000bf54db30;
    puVar29[0x29] = 0xbf54db34;
    puVar29[0x28] = 0x3f000000bf0e39d6;
    puVar29[0x2b] = 0xbf54db34;
    puVar29[0x2a] = 0xbf000000bf0e39d6;
    puVar29[0x2d] = 0xbf7b14c0;
    puVar29[0x2c] = 0x3f000000be47c5a7;
    puVar29[0x2f] = 0xbf7b14c0;
    puVar29[0x2e] = 0xbf000000be47c5a7;
    puVar29[0x31] = 0xbf7b14be;
    puVar29[0x30] = 0x3f0000003e47c5c8;
    puVar29[0x33] = 0xbf7b14be;
    puVar29[0x32] = 0xbf0000003e47c5c8;
    puVar29[0x35] = 0xbf54db2f;
    puVar29[0x34] = 0x3f0000003f0e39dd;
    puVar29[0x37] = 0xbf54db2f;
    puVar29[0x36] = 0xbf0000003f0e39dd;
    puVar29[0x39] = 0xbf0e39d4;
    puVar29[0x38] = 0x3f0000003f54db35;
    puVar29[0x3b] = 0xbf0e39d4;
    puVar29[0x3a] = 0xbf0000003f54db35;
    puVar29[0x3d] = 0xbe47c5bc;
    puVar29[0x3c] = 0x3f0000003f7b14bf;
    puVar29[0x3f] = 0xbe47c5bc;
    puVar29[0x3e] = 0xbf0000003f7b14bf;
    auVar145 = _DAT_7104465250;
    auVar134 = _DAT_7104464960;
    puVar29[0x41] = SUB168(_DAT_7104465250,8);
    puVar29[0x40] = auVar145._0_8_;
    puVar29[0x43] = auVar134._8_8_;
    puVar29[0x42] = auVar134._0_8_;
    puVar59[0x20] = 0x60;
    puVar29 = (undefined8 *)je_aligned_alloc(0x10,0xc0);
    if (puVar29 == (undefined8 *)0x0) {
      if (DAT_7105331f00 != (long *)0x0) {
        local_140 = (uint *)((ulong)local_140 & 0xffffffff00000000);
        local_e00 = 0xc0;
        uStack_dfc = 0;
        uVar45 = (**(code **)(*DAT_7105331f00 + 0x30))(DAT_7105331f00,&local_140,&local_e00);
        if (((uVar45 & 1) != 0) &&
           (puVar29 = (undefined8 *)je_aligned_alloc(0x10,0xc0), puVar29 != (undefined8 *)0x0))
        goto LAB_7103746854;
      }
      puVar29 = (undefined8 *)0x0;
    }
LAB_7103746854:
    *(undefined8 **)(puVar59 + 0x24) = puVar29;
    *puVar29 = 0x2000200010000;
    puVar29[1] = 0x3000200030001;
    puVar29[2] = 0x5000300040004;
    puVar29[3] = 0x6000600050004;
    *(undefined4 *)(puVar29 + 4) = 0x70005;
    *(undefined8 *)((long)puVar29 + 0x24) = 0x8000800070006;
    *(undefined8 *)((long)puVar29 + 0x2c) = 0x9000800090007;
    *(undefined8 *)((long)puVar29 + 0x34) = 0xb0009000a000a;
    *(undefined8 *)((long)puVar29 + 0x3c) = 0xc000c000b000a;
    *(undefined8 *)((long)puVar29 + 0x44) = 0xd000c000d000b;
    *(undefined4 *)((long)puVar29 + 0x4c) = 0xe000e;
    puVar29[10] = 0xf000e000f000d;
    *(undefined4 *)(puVar29 + 0xb) = 0x100010;
    *(undefined8 *)((long)puVar29 + 0x5c) = 0x1100100011000f;
    *(undefined8 *)((long)puVar29 + 100) = 0x13001100120012;
    *(undefined4 *)((long)puVar29 + 0x6c) = 0x130012;
    *(undefined2 *)(puVar29 + 0xe) = 0x14;
    *(undefined8 *)((long)puVar29 + 0x72) = 0x14001500130014;
    *(undefined8 *)((long)puVar29 + 0x7a) = 0x15001600160015;
    *(undefined8 *)((long)puVar29 + 0x82) = 0x18001700160017;
    *(undefined8 *)((long)puVar29 + 0x8a) = 0x18001900170018;
    *(undefined4 *)((long)puVar29 + 0x92) = 0x1a0019;
    *(undefined8 *)((long)puVar29 + 0x96) = 0x1a001b0019001a;
    *(undefined8 *)((long)puVar29 + 0x9e) = 0x1b001c001c001b;
    *(undefined8 *)((long)puVar29 + 0xa6) = 0x1e001d001c001d;
    *(undefined4 *)((long)puVar29 + 0xae) = 0x1d001e;
    *(undefined8 *)((long)puVar29 + 0xb2) = 0x20001f001e001f;
    *(undefined4 *)((long)puVar29 + 0xba) = 0x1f0020;
    *(undefined2 *)((long)puVar29 + 0xbe) = 0x21;
    puVar29 = (undefined8 *)je_aligned_alloc(0x10,0x180);
    if (puVar29 == (undefined8 *)0x0) {
      if (DAT_7105331f00 != (long *)0x0) {
        local_140 = (uint *)((ulong)local_140 & 0xffffffff00000000);
        local_e00 = 0x180;
        uStack_dfc = 0;
        uVar45 = (**(code **)(*DAT_7105331f00 + 0x30))(DAT_7105331f00,&local_140,&local_e00);
        if (((uVar45 & 1) != 0) &&
           (puVar29 = (undefined8 *)je_aligned_alloc(0x10,0x180), puVar29 != (undefined8 *)0x0))
        goto LAB_7103746a74;
      }
      puVar29 = (undefined8 *)0x0;
    }
LAB_7103746a74:
    *(undefined8 **)(puVar59 + 0x2a) = puVar29;
    puVar30 = (undefined8 *)je_aligned_alloc(0x10,0x180);
    if (puVar30 == (undefined8 *)0x0) {
      if (DAT_7105331f00 != (long *)0x0) {
        local_140 = (uint *)((ulong)local_140 & 0xffffffff00000000);
        local_e00 = 0x180;
        uStack_dfc = 0;
        uVar45 = (**(code **)(*DAT_7105331f00 + 0x30))(DAT_7105331f00,&local_140,&local_e00);
        if (((uVar45 & 1) != 0) &&
           (puVar30 = (undefined8 *)je_aligned_alloc(0x10,0x180), puVar30 != (undefined8 *)0x0))
        goto LAB_7103746ad8;
      }
      puVar30 = (undefined8 *)0x0;
    }
LAB_7103746ad8:
    *(undefined8 **)(puVar59 + 0x2e) = puVar30;
    lVar52 = je_aligned_alloc(0x10,0x48);
    if (lVar52 == 0) {
      if (DAT_7105331f00 != (long *)0x0) {
        local_140 = (uint *)((ulong)local_140 & 0xffffffff00000000);
        local_e00 = 0x48;
        uStack_dfc = 0;
        uVar45 = (**(code **)(*DAT_7105331f00 + 0x30))(DAT_7105331f00,&local_140,&local_e00);
        if (((uVar45 & 1) != 0) && (lVar52 = je_aligned_alloc(0x10,0x48), lVar52 != 0))
        goto LAB_7103746b34;
      }
      lVar52 = 0;
    }
LAB_7103746b34:
    *(long *)(puVar59 + 0x2c) = lVar52;
    puVar59[0x28] = 0;
    puVar29[1] = uVar82;
    *puVar29 = uVar69;
    puVar29[3] = 0x3f800000;
    puVar29[2] = 0x3f800000bf800000;
    puVar29[5] = uVar142;
    puVar29[4] = uVar133;
    puVar29[7] = uVar169;
    puVar29[6] = uVar163;
    puVar29[9] = uVar142;
    puVar29[8] = uVar133;
    puVar29[0xb] = uVar169;
    puVar29[10] = uVar163;
    puVar29[0x15] = uVar62;
    puVar29[0x14] = uVar63;
    puVar29[0x17] = uVar87;
    puVar29[0x16] = uVar84;
    puVar29[0xd] = uVar158;
    puVar29[0xc] = uVar90;
    puVar29[0xf] = uVar106;
    puVar29[0xe] = uVar102;
    puVar29[0x11] = uVar158;
    puVar29[0x10] = uVar90;
    puVar29[0x13] = uVar106;
    puVar29[0x12] = uVar102;
    puVar29[0x19] = uVar62;
    puVar29[0x18] = uVar63;
    puVar29[0x1b] = uVar87;
    puVar29[0x1a] = uVar84;
    puVar29[0x1d] = uVar82;
    puVar29[0x1c] = uVar69;
    puVar29[0x1f] = 0x3f800000;
    puVar29[0x1e] = 0x3f800000bf800000;
    puVar29[0x21] = 0x3f800000;
    puVar29[0x20] = 0x3f800000bf800000;
    puVar29[0x23] = uVar87;
    puVar29[0x22] = uVar84;
    puVar29[0x25] = uVar169;
    puVar29[0x24] = uVar163;
    puVar29[0x27] = uVar106;
    puVar29[0x26] = uVar102;
    puVar29[0x29] = uVar62;
    puVar29[0x28] = uVar63;
    puVar29[0x2b] = uVar82;
    puVar29[0x2a] = uVar69;
    puVar29[0x2d] = uVar158;
    puVar29[0x2c] = uVar90;
    puVar29[0x2f] = uVar142;
    puVar29[0x2e] = uVar133;
    puVar59[0x29] = 0x18;
    *(undefined4 *)(puVar30 + 2) = 0x3eb33333;
    *(undefined4 *)((long)puVar30 + 0x14) = 0x3eb33333;
    *puVar30 = 0x3eb333333eb33333;
    *(undefined4 *)(puVar30 + 4) = 0x3eb33333;
    *(undefined4 *)((long)puVar30 + 0x24) = 0x3eb33333;
    puVar30[2] = 0x3eb333333eb33333;
    *(undefined4 *)(puVar30 + 6) = 0x3eb33333;
    *(undefined4 *)((long)puVar30 + 0x34) = 0x3eb33333;
    puVar30[4] = 0x3eb333333eb33333;
    *(undefined4 *)(puVar30 + 8) = 0x3eb33333;
    *(undefined4 *)((long)puVar30 + 0x44) = 0x3eb33333;
    puVar30[6] = 0x3eb333333eb33333;
    *(undefined4 *)(puVar30 + 10) = 0x3f0ccccd;
    *(undefined4 *)((long)puVar30 + 0x54) = 0x3f0ccccd;
    puVar30[8] = 0x3f0ccccd3f0ccccd;
    *(undefined4 *)(puVar30 + 0xc) = 0x3f0ccccd;
    *(undefined4 *)((long)puVar30 + 100) = 0x3f0ccccd;
    puVar30[10] = 0x3f0ccccd3f0ccccd;
    *(undefined4 *)(puVar30 + 0xe) = 0x3f0ccccd;
    *(undefined4 *)((long)puVar30 + 0x74) = 0x3f0ccccd;
    puVar30[0xc] = 0x3f0ccccd3f0ccccd;
    *(undefined4 *)(puVar30 + 0x10) = 0x3f0ccccd;
    *(undefined4 *)((long)puVar30 + 0x84) = 0x3f0ccccd;
    puVar30[0xe] = 0x3f0ccccd3f0ccccd;
    *(undefined4 *)(puVar30 + 0x12) = 0x3f333333;
    *(undefined4 *)((long)puVar30 + 0x94) = 0x3f333333;
    puVar30[0x10] = 0x3f3333333f333333;
    *(undefined4 *)(puVar30 + 0x14) = 0x3f333333;
    *(undefined4 *)((long)puVar30 + 0xa4) = 0x3f333333;
    puVar30[0x12] = 0x3f3333333f333333;
    *(undefined4 *)(puVar30 + 0x16) = 0x3f333333;
    *(undefined4 *)((long)puVar30 + 0xb4) = 0x3f333333;
    puVar30[0x14] = 0x3f3333333f333333;
    *(undefined4 *)(puVar30 + 0x18) = 0x3f333333;
    *(undefined4 *)((long)puVar30 + 0xc4) = 0x3f333333;
    puVar30[0x16] = 0x3f3333333f333333;
    *(undefined4 *)(puVar30 + 0x1a) = 0x3f59999a;
    *(undefined4 *)((long)puVar30 + 0xd4) = 0x3f59999a;
    puVar30[0x18] = 0x3f59999a3f59999a;
    *(undefined4 *)(puVar30 + 0x1c) = 0x3f59999a;
    *(undefined4 *)((long)puVar30 + 0xe4) = 0x3f59999a;
    puVar30[0x1a] = 0x3f59999a3f59999a;
    *(undefined4 *)(puVar30 + 0x1e) = 0x3f59999a;
    *(undefined4 *)((long)puVar30 + 0xf4) = 0x3f59999a;
    puVar30[0x1c] = 0x3f59999a3f59999a;
    *(undefined4 *)(puVar30 + 0x20) = 0x3f59999a;
    *(undefined4 *)((long)puVar30 + 0x104) = 0x3f59999a;
    puVar30[0x1e] = 0x3f59999a3f59999a;
    uVar63 = CONCAT44(fVar70,fVar70);
    puVar30[0x21] = uVar33;
    puVar30[0x20] = uVar63;
    puVar30[0x23] = uVar33;
    puVar30[0x22] = uVar63;
    puVar30[0x25] = uVar33;
    puVar30[0x24] = uVar63;
    puVar30[0x27] = uVar33;
    puVar30[0x26] = uVar63;
    *(undefined4 *)(puVar30 + 0x2a) = 0x3e4ccccd;
    *(undefined4 *)((long)puVar30 + 0x154) = 0x3e4ccccd;
    puVar30[0x28] = 0x3e4ccccd3e4ccccd;
    *(undefined4 *)(puVar30 + 0x2c) = 0x3e4ccccd;
    *(undefined4 *)((long)puVar30 + 0x164) = 0x3e4ccccd;
    puVar30[0x2a] = 0x3e4ccccd3e4ccccd;
    *(undefined4 *)(puVar30 + 0x2e) = 0x3e4ccccd;
    *(undefined4 *)((long)puVar30 + 0x174) = 0x3e4ccccd;
    puVar30[0x2c] = 0x3e4ccccd3e4ccccd;
    *(undefined4 *)(puVar30 + 0x30) = 0x3e4ccccd;
    *(undefined4 *)((long)puVar30 + 0x184) = 0x3e4ccccd;
    puVar30[0x2e] = 0x3e4ccccd3e4ccccd;
    uVar36 = puVar59[0x28];
    *(undefined2 *)(lVar52 + (ulong)uVar36 * 2) = 0;
    *(undefined2 *)(lVar52 + (ulong)(uVar36 + 1) * 2) = 2;
    *(undefined2 *)(lVar52 + (ulong)(uVar36 + 2) * 2) = 1;
    *(undefined2 *)(lVar52 + (ulong)(uVar36 + 3) * 2) = 3;
    *(undefined2 *)(lVar52 + (ulong)(uVar36 + 4) * 2) = 1;
    *(undefined2 *)(lVar52 + (ulong)(uVar36 + 5) * 2) = 2;
    *(undefined2 *)(lVar52 + (ulong)(uVar36 + 6) * 2) = 4;
    *(undefined2 *)(lVar52 + (ulong)(uVar36 + 7) * 2) = 6;
    *(undefined2 *)(lVar52 + (ulong)(uVar36 + 8) * 2) = 5;
    *(undefined2 *)(lVar52 + (ulong)(uVar36 + 9) * 2) = 7;
    *(undefined2 *)(lVar52 + (ulong)(uVar36 + 10) * 2) = 5;
    *(undefined2 *)(lVar52 + (ulong)(uVar36 + 0xb) * 2) = 6;
    *(undefined2 *)(lVar52 + (ulong)(uVar36 + 0xc) * 2) = 8;
    *(undefined2 *)(lVar52 + (ulong)(uVar36 + 0xd) * 2) = 10;
    *(undefined2 *)(lVar52 + (ulong)(uVar36 + 0xe) * 2) = 9;
    *(undefined2 *)(lVar52 + (ulong)(uVar36 + 0xf) * 2) = 0xb;
    *(undefined2 *)(lVar52 + (ulong)(uVar36 + 0x10) * 2) = 9;
    *(undefined2 *)(lVar52 + (ulong)(uVar36 + 0x11) * 2) = 10;
    *(undefined2 *)(lVar52 + (ulong)(uVar36 + 0x12) * 2) = 0xc;
    *(undefined2 *)(lVar52 + (ulong)(uVar36 + 0x13) * 2) = 0xe;
    *(undefined2 *)(lVar52 + (ulong)(uVar36 + 0x14) * 2) = 0xd;
    *(undefined2 *)(lVar52 + (ulong)(uVar36 + 0x15) * 2) = 0xf;
    *(undefined2 *)(lVar52 + (ulong)(uVar36 + 0x16) * 2) = 0xd;
    *(undefined2 *)(lVar52 + (ulong)(uVar36 + 0x17) * 2) = 0xe;
    *(undefined2 *)(lVar52 + (ulong)(uVar36 + 0x18) * 2) = 0x10;
    *(undefined2 *)(lVar52 + (ulong)(uVar36 + 0x19) * 2) = 0x12;
    *(undefined2 *)(lVar52 + (ulong)(uVar36 + 0x1a) * 2) = 0x11;
    *(undefined2 *)(lVar52 + (ulong)(uVar36 + 0x1b) * 2) = 0x13;
    *(undefined2 *)(lVar52 + (ulong)(uVar36 + 0x1c) * 2) = 0x11;
    *(undefined2 *)(lVar52 + (ulong)(uVar36 + 0x1d) * 2) = 0x12;
    *(undefined2 *)(lVar52 + (ulong)(uVar36 + 0x1e) * 2) = 0x14;
    *(undefined2 *)(lVar52 + (ulong)(uVar36 + 0x1f) * 2) = 0x16;
    *(undefined2 *)(lVar52 + (ulong)(uVar36 + 0x20) * 2) = 0x15;
    *(undefined2 *)(lVar52 + (ulong)(uVar36 + 0x21) * 2) = 0x17;
    *(undefined2 *)(lVar52 + (ulong)(uVar36 + 0x22) * 2) = 0x15;
    *(undefined2 *)(lVar52 + (ulong)(uVar36 + 0x23) * 2) = 0x16;
    puVar59[0x28] = uVar36 + 0x24;
    puVar28[0x42] = puVar59;
    puVar28[0x45] = 0x3f800000;
    puVar28[0x44] = 0;
    puVar28[0x47] = 0x3f4f1bbd;
    puVar28[0x46] = 0x3f16791800000000;
    puVar28[0x49] = 0x3e9e3779;
    puVar28[0x48] = 0x3f73787100000000;
    puVar28[0x4b] = 0xbe9e377b;
    puVar28[0x4a] = 0x3f73787000000000;
    puVar28[0x4d] = 0xbf4f1bbe;
    puVar28[0x4c] = 0x3f16791700000000;
    puVar28[0x4f] = 0xbf800000;
    puVar28[0x4e] = 0xb3bbbd2e00000000;
    puVar28[0x51] = 0xbf4f1bbc;
    puVar28[0x50] = 0xbf16791a00000000;
    puVar28[0x53] = 0xbe9e376e;
    puVar28[0x52] = 0xbf73787200000000;
    puVar28[0x55] = 0x3e9e377e;
    puVar28[0x54] = 0xbf73787000000000;
    puVar28[0x57] = 0x3f4f1bbc;
    puVar28[0x56] = 0xbf16791900000000;
    puVar28[0x59] = 0x3f800000;
    puVar28[0x58] = 0;
    puVar28[0x5b] = 0x3f4f1bbd;
    puVar28[0x5a] = 0x3f167918;
    puVar28[0x5d] = 0x3e9e3779;
    puVar28[0x5c] = 0x3f737871;
    puVar28[0x5f] = 0xbe9e377b;
    puVar28[0x5e] = 0x3f737870;
    puVar28[0x61] = 0xbf4f1bbe;
    puVar28[0x60] = 0x3f167917;
    puVar28[99] = 0xbf800000;
    puVar28[0x62] = 0xb3bbbd2e;
    puVar28[0x65] = 0xbf4f1bbc;
    puVar28[100] = 0xbf16791a;
    puVar28[0x67] = 0;
    puVar28[0x66] = 0xbe9e376ebf737872;
    puVar28[0x69] = 0;
    puVar28[0x68] = 0x3e9e377ebf737870;
    puVar28[0x6b] = 0;
    puVar28[0x6a] = 0x3f4f1bbcbf167919;
    puVar28[0x6d] = 0;
    puVar28[0x6c] = 0x3f80000000000000;
    puVar28[0x6f] = 0;
    puVar28[0x6e] = 0x3f4f1bbd3f167918;
    puVar28[0x71] = 0;
    puVar28[0x70] = 0x3e9e37793f737871;
    puVar28[0x73] = 0;
    puVar28[0x72] = 0xbe9e377b3f737870;
    puVar28[0x75] = 0;
    puVar28[0x74] = 0xbf4f1bbe3f167917;
    puVar28[0x77] = 0;
    puVar28[0x76] = 0xbf800000b3bbbd2e;
    puVar28[0x79] = 0;
    puVar28[0x78] = 0xbf4f1bbcbf16791a;
    puVar28[0x7b] = 0xbe9e376e;
    puVar28[0x7a] = 0xbf737872;
    puVar28[0x7d] = 0x3e9e377e;
    puVar28[0x7c] = 0xbf737870;
    puVar28[0x7f] = 0x3f4f1bbc;
    puVar28[0x7e] = 0xbf167919;
    puVar28[0x81] = 0x3f800000;
    puVar28[0x80] = 0x343bbd2e;
    puVar28[0x83] = (ulong)*(uint *)(puVar28 + 0x83);
    *(undefined4 *)(puVar28 + 0x82) = *(undefined4 *)(puVar28 + 0x82);
    *(undefined4 *)((long)puVar28 + 0x414) = *(undefined4 *)((long)puVar28 + 0x414);
    puVar28[0x85] = (ulong)*(uint *)(puVar28 + 0x85);
    *(undefined4 *)(puVar28 + 0x84) = *(undefined4 *)(puVar28 + 0x84);
    *(undefined4 *)((long)puVar28 + 0x424) = *(undefined4 *)((long)puVar28 + 0x424);
    puVar28[0x87] = (ulong)*(uint *)(puVar28 + 0x87);
    *(undefined4 *)(puVar28 + 0x86) = *(undefined4 *)(puVar28 + 0x86);
    *(undefined4 *)((long)puVar28 + 0x434) = *(undefined4 *)((long)puVar28 + 0x434);
    puVar28[0x89] = (ulong)*(uint *)(puVar28 + 0x89);
    *(undefined4 *)(puVar28 + 0x88) = *(undefined4 *)(puVar28 + 0x88);
    *(undefined4 *)((long)puVar28 + 0x444) = *(undefined4 *)((long)puVar28 + 0x444);
    puVar28[0x8b] = (ulong)*(uint *)(puVar28 + 0x8b);
    *(undefined4 *)(puVar28 + 0x8a) = *(undefined4 *)(puVar28 + 0x8a);
    *(undefined4 *)((long)puVar28 + 0x454) = *(undefined4 *)((long)puVar28 + 0x454);
    puVar28[0x8d] = (ulong)*(uint *)(puVar28 + 0x8d);
    *(undefined4 *)(puVar28 + 0x8c) = *(undefined4 *)(puVar28 + 0x8c);
    *(undefined4 *)((long)puVar28 + 0x464) = *(undefined4 *)((long)puVar28 + 0x464);
    puVar28[0x8f] = (ulong)*(uint *)(puVar28 + 0x8f);
    *(undefined4 *)(puVar28 + 0x8e) = *(undefined4 *)(puVar28 + 0x8e);
    *(undefined4 *)((long)puVar28 + 0x474) = *(undefined4 *)((long)puVar28 + 0x474);
    puVar28[0x91] = (ulong)*(uint *)(puVar28 + 0x91);
    *(undefined4 *)(puVar28 + 0x90) = *(undefined4 *)(puVar28 + 0x90);
    *(undefined4 *)((long)puVar28 + 0x484) = *(undefined4 *)((long)puVar28 + 0x484);
    puVar28[0x93] = (ulong)*(uint *)(puVar28 + 0x93);
    *(undefined4 *)(puVar28 + 0x92) = *(undefined4 *)(puVar28 + 0x92);
    *(undefined4 *)((long)puVar28 + 0x494) = *(undefined4 *)((long)puVar28 + 0x494);
    puVar28[0x95] = (ulong)*(uint *)(puVar28 + 0x95);
    *(undefined4 *)(puVar28 + 0x94) = *(undefined4 *)(puVar28 + 0x94);
    *(undefined4 *)((long)puVar28 + 0x4a4) = *(undefined4 *)((long)puVar28 + 0x4a4);
    puVar28[0x97] = (ulong)*(uint *)(puVar28 + 0x97);
    *(undefined4 *)(puVar28 + 0x96) = *(undefined4 *)(puVar28 + 0x96);
    *(undefined4 *)((long)puVar28 + 0x4b4) = *(undefined4 *)((long)puVar28 + 0x4b4);
    puVar28[0x99] = (ulong)*(uint *)(puVar28 + 0x99);
    *(undefined4 *)(puVar28 + 0x98) = *(undefined4 *)(puVar28 + 0x98);
    *(undefined4 *)((long)puVar28 + 0x4c4) = *(undefined4 *)((long)puVar28 + 0x4c4);
    puVar28[0x9b] = (ulong)*(uint *)(puVar28 + 0x9b);
    *(undefined4 *)(puVar28 + 0x9a) = *(undefined4 *)(puVar28 + 0x9a);
    *(undefined4 *)((long)puVar28 + 0x4d4) = *(undefined4 *)((long)puVar28 + 0x4d4);
    puVar28[0x9d] = (ulong)*(uint *)(puVar28 + 0x9d);
    *(undefined4 *)(puVar28 + 0x9c) = *(undefined4 *)(puVar28 + 0x9c);
    *(undefined4 *)((long)puVar28 + 0x4e4) = *(undefined4 *)((long)puVar28 + 0x4e4);
    puVar28[0x9f] = (ulong)*(uint *)(puVar28 + 0x9f);
    *(undefined4 *)(puVar28 + 0x9e) = *(undefined4 *)(puVar28 + 0x9e);
    *(undefined4 *)((long)puVar28 + 0x4f4) = *(undefined4 *)((long)puVar28 + 0x4f4);
    puVar28[0xa1] = (ulong)*(uint *)(puVar28 + 0xa1);
    *(undefined4 *)(puVar28 + 0xa0) = *(undefined4 *)(puVar28 + 0xa0);
    *(undefined4 *)((long)puVar28 + 0x504) = *(undefined4 *)((long)puVar28 + 0x504);
    puVar28[0xa3] = (ulong)*(uint *)(puVar28 + 0xa3);
    *(undefined4 *)(puVar28 + 0xa2) = *(undefined4 *)(puVar28 + 0xa2);
    *(undefined4 *)((long)puVar28 + 0x514) = *(undefined4 *)((long)puVar28 + 0x514);
    puVar28[0xa5] = (ulong)*(uint *)(puVar28 + 0xa5);
    *(undefined4 *)(puVar28 + 0xa4) = *(undefined4 *)(puVar28 + 0xa4);
    *(undefined4 *)((long)puVar28 + 0x524) = *(undefined4 *)((long)puVar28 + 0x524);
    puVar28[0xa7] = (ulong)*(uint *)(puVar28 + 0xa7);
    *(undefined4 *)(puVar28 + 0xa6) = *(undefined4 *)(puVar28 + 0xa6);
    *(undefined4 *)((long)puVar28 + 0x534) = *(undefined4 *)((long)puVar28 + 0x534);
    puVar28[0xa9] = (ulong)*(uint *)(puVar28 + 0xa9);
    *(undefined4 *)(puVar28 + 0xa8) = *(undefined4 *)(puVar28 + 0xa8);
    *(undefined4 *)((long)puVar28 + 0x544) = *(undefined4 *)((long)puVar28 + 0x544);
    puVar28[0xab] = (ulong)*(uint *)(puVar28 + 0xab);
    *(undefined4 *)(puVar28 + 0xaa) = *(undefined4 *)(puVar28 + 0xaa);
    *(undefined4 *)((long)puVar28 + 0x554) = *(undefined4 *)((long)puVar28 + 0x554);
    puVar28[0xad] = (ulong)*(uint *)(puVar28 + 0xad);
    *(undefined4 *)(puVar28 + 0xac) = *(undefined4 *)(puVar28 + 0xac);
    *(undefined4 *)((long)puVar28 + 0x564) = *(undefined4 *)((long)puVar28 + 0x564);
    puVar28[0xaf] = (ulong)*(uint *)(puVar28 + 0xaf);
    *(undefined4 *)(puVar28 + 0xae) = *(undefined4 *)(puVar28 + 0xae);
    *(undefined4 *)((long)puVar28 + 0x574) = *(undefined4 *)((long)puVar28 + 0x574);
    puVar28[0xb1] = (ulong)*(uint *)(puVar28 + 0xb1);
    *(undefined4 *)(puVar28 + 0xb0) = *(undefined4 *)(puVar28 + 0xb0);
    *(undefined4 *)((long)puVar28 + 0x584) = *(undefined4 *)((long)puVar28 + 0x584);
    puVar28[0xb3] = (ulong)*(uint *)(puVar28 + 0xb3);
    *(undefined4 *)(puVar28 + 0xb2) = *(undefined4 *)(puVar28 + 0xb2);
    *(undefined4 *)((long)puVar28 + 0x594) = *(undefined4 *)((long)puVar28 + 0x594);
    puVar28[0xb5] = (ulong)*(uint *)(puVar28 + 0xb5);
    *(undefined4 *)(puVar28 + 0xb4) = *(undefined4 *)(puVar28 + 0xb4);
    *(undefined4 *)((long)puVar28 + 0x5a4) = *(undefined4 *)((long)puVar28 + 0x5a4);
    puVar28[0xb7] = (ulong)*(uint *)(puVar28 + 0xb7);
    *(undefined4 *)(puVar28 + 0xb6) = *(undefined4 *)(puVar28 + 0xb6);
    *(undefined4 *)((long)puVar28 + 0x5b4) = *(undefined4 *)((long)puVar28 + 0x5b4);
    puVar28[0xb9] = (ulong)*(uint *)(puVar28 + 0xb9);
    *(undefined4 *)(puVar28 + 0xb8) = *(undefined4 *)(puVar28 + 0xb8);
    *(undefined4 *)((long)puVar28 + 0x5c4) = *(undefined4 *)((long)puVar28 + 0x5c4);
    puVar28[0xbb] = (ulong)*(uint *)(puVar28 + 0xbb);
    *(undefined4 *)(puVar28 + 0xba) = *(undefined4 *)(puVar28 + 0xba);
    *(undefined4 *)((long)puVar28 + 0x5d4) = *(undefined4 *)((long)puVar28 + 0x5d4);
    puVar28[0xbd] = (ulong)*(uint *)(puVar28 + 0xbd);
    *(undefined4 *)(puVar28 + 0xbc) = *(undefined4 *)(puVar28 + 0xbc);
    *(undefined4 *)((long)puVar28 + 0x5e4) = *(undefined4 *)((long)puVar28 + 0x5e4);
    puVar28[0xbf] = (ulong)SUB164(*(undefined1 (*) [16])(puVar28 + 0xbe),8);
    puVar28[0xbe] = SUB168(*(undefined1 (*) [16])(puVar28 + 0xbe),0);
  }
  else {
    FUN_710358eb60(&local_e00);
  }
  if (DAT_7105334e90 == 0) {
    lVar52 = je_aligned_alloc(0x10,0x10);
    if (lVar52 == 0) {
      if (DAT_7105331f00 != (long *)0x0) {
        local_140 = (uint *)((ulong)local_140 & 0xffffffff00000000);
        local_e00 = 0x10;
        uStack_dfc = 0;
        uVar45 = (**(code **)(*DAT_7105331f00 + 0x30))(DAT_7105331f00,&local_140,&local_e00);
        if (((uVar45 & 1) != 0) && (lVar52 = je_aligned_alloc(0x10,0x10), lVar52 != 0))
        goto LAB_7103744338;
      }
      lVar52 = 0;
    }
LAB_7103744338:
    FUN_71035a4040(lVar52);
    DAT_7105334e90 = lVar52;
  }
  local_e00 = CONCAT31(local_e00._1_3_,1);
  uStack_dfc = 0x780;
  local_df8 = 0x780;
  FUN_71035a4130(DAT_7105334e90,&local_e00);
  FUN_7103618cf0(DAT_7105336ce8);
  FUN_7103618cf0(DAT_7105336ce8);
  FUN_710375a630();
  if (DAT_710593a218 != (undefined8 *)0x0) goto LAB_7103744c54;
  puVar28 = (undefined8 *)je_aligned_alloc(0x10,8);
  if (puVar28 == (undefined8 *)0x0) {
    if (DAT_7105331f00 != (long *)0x0) {
      local_140 = (uint *)((ulong)local_140 & 0xffffffff00000000);
      local_e00 = 8;
      uStack_dfc = 0;
      uVar45 = (**(code **)(*DAT_7105331f00 + 0x30))(DAT_7105331f00,&local_140,&local_e00);
      if (((uVar45 & 1) != 0) &&
         (puVar28 = (undefined8 *)je_aligned_alloc(0x10,8), puVar28 != (undefined8 *)0x0))
      goto LAB_71037443e8;
    }
    puVar28 = (undefined8 *)0x0;
  }
LAB_71037443e8:
  puVar34 = (undefined2 *)je_aligned_alloc(0x10,0x88);
  if (puVar34 == (undefined2 *)0x0) {
    if (DAT_7105331f00 != (long *)0x0) {
      local_140 = (uint *)((ulong)local_140 & 0xffffffff00000000);
      local_e00 = 0x88;
      uStack_dfc = 0;
      uVar45 = (**(code **)(*DAT_7105331f00 + 0x30))(DAT_7105331f00,&local_140,&local_e00);
      if (((uVar45 & 1) != 0) &&
         (puVar34 = (undefined2 *)je_aligned_alloc(0x10,0x88), puVar34 != (undefined2 *)0x0))
      goto LAB_7103744448;
    }
    puVar34 = (undefined2 *)0x0;
  }
LAB_7103744448:
  *puVar34 = 0;
  *(undefined4 *)(puVar34 + 2) = 1;
  *(undefined2 **)(puVar34 + 4) = puVar34 + 4;
  *(undefined2 **)(puVar34 + 8) = puVar34 + 4;
  *(undefined8 *)(puVar34 + 0x14) = 0;
  *(undefined8 *)(puVar34 + 0x18) = 0;
  puVar34[0x18] = 1;
  *(undefined1 *)(puVar34 + 0x19) = 0;
  *(undefined8 *)(puVar34 + 0x30) = 0;
  *(undefined8 *)(puVar34 + 0x1c) = 0;
  *(undefined8 *)(puVar34 + 0x20) = 0;
  *(undefined8 *)(puVar34 + 0xc) = 0;
  *(undefined8 *)(puVar34 + 0x10) = 0;
  *(undefined8 *)(puVar34 + 0x24) = 0;
  *(undefined8 *)(puVar34 + 0x28) = 0;
  puVar29 = (undefined8 *)(puVar34 + 0x2c);
  *puVar29 = 0;
  *(undefined8 *)(puVar34 + 0x3c) = 0;
  *(undefined8 *)(puVar34 + 0x40) = 0;
  *(undefined8 *)(puVar34 + 0x34) = 0;
  *(undefined8 *)(puVar34 + 0x38) = 0;
  lVar52 = je_aligned_alloc(0x10,0x2a0);
  if (lVar52 == 0) {
    if (DAT_7105331f00 != (long *)0x0) {
      local_140 = (uint *)((ulong)local_140 & 0xffffffff00000000);
      local_e00 = 0x2a0;
      uStack_dfc = 0;
      uVar45 = (**(code **)(*DAT_7105331f00 + 0x30))(DAT_7105331f00,&local_140,&local_e00);
      if (((uVar45 & 1) != 0) && (lVar52 = je_aligned_alloc(0x10,0x2a0), lVar52 != 0))
      goto LAB_71037444e8;
    }
    lVar52 = 0;
  }
LAB_71037444e8:
  *(long *)(puVar34 + 0x34) = lVar52 + 0x2a0;
  *(long *)(puVar34 + 0x2c) = lVar52;
  *(long *)(puVar34 + 0x30) = lVar52;
  local_e00 = 0x523bc68;
  uStack_dfc = 0x71;
  local_df8 = 0x3720a00;
  uStack_df4 = 0x71;
  local_df0 = 0;
  uStack_def = 0;
  local_de8 = SUB81(puVar34,0);
  uVar129 = local_de8;
  uStack_de7 = (undefined2)((ulong)puVar34 >> 8);
  uVar140 = uStack_de7;
  uStack_de5 = (undefined1)((ulong)puVar34 >> 0x18);
  uVar130 = uStack_de5;
  uStack_de4 = (undefined4)((ulong)puVar34 >> 0x20);
  uVar22 = uStack_de4;
  *(long *)(lVar52 + 0x20) = lVar52;
  local_de0 = &local_e00;
  (*(code *)PTR_FUN_710523bc80)();
  *(long *)(puVar34 + 0x30) = *(long *)(puVar34 + 0x30) + 0x30;
  if (&local_e00 == local_de0) {
    pcVar37 = *(code **)(*(long *)local_de0 + 0x20);
LAB_7103744560:
    (*pcVar37)();
  }
  else if (local_de0 != (uint *)0x0) {
    pcVar37 = *(code **)(*(long *)local_de0 + 0x28);
    goto LAB_7103744560;
  }
  local_df8 = 0x3720d20;
  uStack_df4 = 0x71;
  local_de0 = &local_e00;
  local_e00 = 0x523bc68;
  uStack_dfc = 0x71;
  local_df0 = 0;
  uStack_def = 0;
  uVar45 = *(ulong *)(puVar34 + 0x30);
  local_de8 = uVar129;
  uStack_de7 = uVar140;
  uStack_de5 = uVar130;
  uStack_de4 = uVar22;
  if (uVar45 < *(ulong *)(puVar34 + 0x34)) {
    *(ulong *)(uVar45 + 0x20) = uVar45;
    (*(code *)PTR_FUN_710523bc80)();
    *(long *)(puVar34 + 0x30) = *(long *)(puVar34 + 0x30) + 0x30;
  }
  else {
    FUN_7103720ad0(puVar29,&local_e00);
  }
  if (&local_e00 == local_de0) {
    pcVar37 = *(code **)(*(long *)local_de0 + 0x20);
LAB_71037445e8:
    (*pcVar37)();
  }
  else if (local_de0 != (uint *)0x0) {
    pcVar37 = *(code **)(*(long *)local_de0 + 0x28);
    goto LAB_71037445e8;
  }
  local_df8 = 0x3720d80;
  uStack_df4 = 0x71;
  local_de0 = &local_e00;
  local_e00 = 0x523bc68;
  uStack_dfc = 0x71;
  local_df0 = 0;
  uStack_def = 0;
  uVar45 = *(ulong *)(puVar34 + 0x30);
  if (uVar45 < *(ulong *)(puVar34 + 0x34)) {
    *(ulong *)(uVar45 + 0x20) = uVar45;
    local_de8 = uVar129;
    uStack_de7 = uVar140;
    uStack_de5 = uVar130;
    uStack_de4 = uVar22;
    (*(code *)PTR_FUN_710523bc80)();
    *(long *)(puVar34 + 0x30) = *(long *)(puVar34 + 0x30) + 0x30;
  }
  else {
    local_de8 = uVar129;
    uStack_de7 = uVar140;
    uStack_de5 = uVar130;
    uStack_de4 = uVar22;
    FUN_7103720ad0(puVar29,&local_e00);
  }
  if (&local_e00 == local_de0) {
    pcVar37 = *(code **)(*(long *)local_de0 + 0x20);
LAB_7103744670:
    (*pcVar37)();
  }
  else if (local_de0 != (uint *)0x0) {
    pcVar37 = *(code **)(*(long *)local_de0 + 0x28);
    goto LAB_7103744670;
  }
  local_df8 = 0x3720de0;
  uStack_df4 = 0x71;
  local_de0 = &local_e00;
  local_e00 = 0x523bc68;
  uStack_dfc = 0x71;
  local_df0 = 0;
  uStack_def = 0;
  uVar45 = *(ulong *)(puVar34 + 0x30);
  if (uVar45 < *(ulong *)(puVar34 + 0x34)) {
    *(ulong *)(uVar45 + 0x20) = uVar45;
    local_de8 = uVar129;
    uStack_de7 = uVar140;
    uStack_de5 = uVar130;
    uStack_de4 = uVar22;
    (*(code *)PTR_FUN_710523bc80)();
    *(long *)(puVar34 + 0x30) = *(long *)(puVar34 + 0x30) + 0x30;
  }
  else {
    local_de8 = uVar129;
    uStack_de7 = uVar140;
    uStack_de5 = uVar130;
    uStack_de4 = uVar22;
    FUN_7103720ad0(puVar29,&local_e00);
  }
  if (&local_e00 == local_de0) {
    pcVar37 = *(code **)(*(long *)local_de0 + 0x20);
LAB_71037446f8:
    (*pcVar37)();
  }
  else if (local_de0 != (uint *)0x0) {
    pcVar37 = *(code **)(*(long *)local_de0 + 0x28);
    goto LAB_71037446f8;
  }
  local_df8 = 0x3720e00;
  uStack_df4 = 0x71;
  local_de0 = &local_e00;
  local_e00 = 0x523bc68;
  uStack_dfc = 0x71;
  local_df0 = 0;
  uStack_def = 0;
  uVar45 = *(ulong *)(puVar34 + 0x30);
  if (uVar45 < *(ulong *)(puVar34 + 0x34)) {
    *(ulong *)(uVar45 + 0x20) = uVar45;
    local_de8 = uVar129;
    uStack_de7 = uVar140;
    uStack_de5 = uVar130;
    uStack_de4 = uVar22;
    (*(code *)PTR_FUN_710523bc80)();
    *(long *)(puVar34 + 0x30) = *(long *)(puVar34 + 0x30) + 0x30;
  }
  else {
    local_de8 = uVar129;
    uStack_de7 = uVar140;
    uStack_de5 = uVar130;
    uStack_de4 = uVar22;
    FUN_7103720ad0(puVar29,&local_e00);
  }
  if (&local_e00 == local_de0) {
    pcVar37 = *(code **)(*(long *)local_de0 + 0x20);
LAB_7103744780:
    (*pcVar37)();
  }
  else if (local_de0 != (uint *)0x0) {
    pcVar37 = *(code **)(*(long *)local_de0 + 0x28);
    goto LAB_7103744780;
  }
  local_df8 = 0x3720e20;
  uStack_df4 = 0x71;
  local_de0 = &local_e00;
  local_e00 = 0x523bc68;
  uStack_dfc = 0x71;
  local_df0 = 0;
  uStack_def = 0;
  uVar45 = *(ulong *)(puVar34 + 0x30);
  if (uVar45 < *(ulong *)(puVar34 + 0x34)) {
    *(ulong *)(uVar45 + 0x20) = uVar45;
    local_de8 = uVar129;
    uStack_de7 = uVar140;
    uStack_de5 = uVar130;
    uStack_de4 = uVar22;
    (*(code *)PTR_FUN_710523bc80)();
    *(long *)(puVar34 + 0x30) = *(long *)(puVar34 + 0x30) + 0x30;
  }
  else {
    local_de8 = uVar129;
    uStack_de7 = uVar140;
    uStack_de5 = uVar130;
    uStack_de4 = uVar22;
    FUN_7103720ad0(puVar29,&local_e00);
  }
  if (&local_e00 == local_de0) {
    pcVar37 = *(code **)(*(long *)local_de0 + 0x20);
LAB_7103744808:
    (*pcVar37)();
  }
  else if (local_de0 != (uint *)0x0) {
    pcVar37 = *(code **)(*(long *)local_de0 + 0x28);
    goto LAB_7103744808;
  }
  local_df8 = 0x3720e80;
  uStack_df4 = 0x71;
  local_de0 = &local_e00;
  local_e00 = 0x523bc68;
  uStack_dfc = 0x71;
  local_df0 = 0;
  uStack_def = 0;
  uVar45 = *(ulong *)(puVar34 + 0x30);
  if (uVar45 < *(ulong *)(puVar34 + 0x34)) {
    *(ulong *)(uVar45 + 0x20) = uVar45;
    local_de8 = uVar129;
    uStack_de7 = uVar140;
    uStack_de5 = uVar130;
    uStack_de4 = uVar22;
    (*(code *)PTR_FUN_710523bc80)();
    *(long *)(puVar34 + 0x30) = *(long *)(puVar34 + 0x30) + 0x30;
  }
  else {
    local_de8 = uVar129;
    uStack_de7 = uVar140;
    uStack_de5 = uVar130;
    uStack_de4 = uVar22;
    FUN_7103720ad0(puVar29,&local_e00);
  }
  if (&local_e00 == local_de0) {
    pcVar37 = *(code **)(*(long *)local_de0 + 0x20);
LAB_7103744890:
    (*pcVar37)();
  }
  else if (local_de0 != (uint *)0x0) {
    pcVar37 = *(code **)(*(long *)local_de0 + 0x28);
    goto LAB_7103744890;
  }
  local_df8 = 0x3720ee0;
  uStack_df4 = 0x71;
  local_de0 = &local_e00;
  local_e00 = 0x523bc68;
  uStack_dfc = 0x71;
  local_df0 = 0;
  uStack_def = 0;
  uVar45 = *(ulong *)(puVar34 + 0x30);
  if (uVar45 < *(ulong *)(puVar34 + 0x34)) {
    *(ulong *)(uVar45 + 0x20) = uVar45;
    local_de8 = uVar129;
    uStack_de7 = uVar140;
    uStack_de5 = uVar130;
    uStack_de4 = uVar22;
    (*(code *)PTR_FUN_710523bc80)();
    *(long *)(puVar34 + 0x30) = *(long *)(puVar34 + 0x30) + 0x30;
  }
  else {
    local_de8 = uVar129;
    uStack_de7 = uVar140;
    uStack_de5 = uVar130;
    uStack_de4 = uVar22;
    FUN_7103720ad0(puVar29,&local_e00);
  }
  if (&local_e00 == local_de0) {
    pcVar37 = *(code **)(*(long *)local_de0 + 0x20);
LAB_7103744918:
    (*pcVar37)();
  }
  else if (local_de0 != (uint *)0x0) {
    pcVar37 = *(code **)(*(long *)local_de0 + 0x28);
    goto LAB_7103744918;
  }
  local_df8 = 0x3720f10;
  uStack_df4 = 0x71;
  local_de0 = &local_e00;
  local_e00 = 0x523bc68;
  uStack_dfc = 0x71;
  local_df0 = 0;
  uStack_def = 0;
  uVar45 = *(ulong *)(puVar34 + 0x30);
  if (uVar45 < *(ulong *)(puVar34 + 0x34)) {
    *(ulong *)(uVar45 + 0x20) = uVar45;
    local_de8 = uVar129;
    uStack_de7 = uVar140;
    uStack_de5 = uVar130;
    uStack_de4 = uVar22;
    (*(code *)PTR_FUN_710523bc80)();
    *(long *)(puVar34 + 0x30) = *(long *)(puVar34 + 0x30) + 0x30;
  }
  else {
    local_de8 = uVar129;
    uStack_de7 = uVar140;
    uStack_de5 = uVar130;
    uStack_de4 = uVar22;
    FUN_7103720ad0(puVar29,&local_e00);
  }
  if (&local_e00 == local_de0) {
    pcVar37 = *(code **)(*(long *)local_de0 + 0x20);
LAB_71037449a0:
    (*pcVar37)();
  }
  else if (local_de0 != (uint *)0x0) {
    pcVar37 = *(code **)(*(long *)local_de0 + 0x28);
    goto LAB_71037449a0;
  }
  local_df8 = 0x3720f40;
  uStack_df4 = 0x71;
  local_de0 = &local_e00;
  local_e00 = 0x523bc68;
  uStack_dfc = 0x71;
  local_df0 = 0;
  uStack_def = 0;
  uVar45 = *(ulong *)(puVar34 + 0x30);
  if (uVar45 < *(ulong *)(puVar34 + 0x34)) {
    *(ulong *)(uVar45 + 0x20) = uVar45;
    local_de8 = uVar129;
    uStack_de7 = uVar140;
    uStack_de5 = uVar130;
    uStack_de4 = uVar22;
    (*(code *)PTR_FUN_710523bc80)();
    *(long *)(puVar34 + 0x30) = *(long *)(puVar34 + 0x30) + 0x30;
  }
  else {
    local_de8 = uVar129;
    uStack_de7 = uVar140;
    uStack_de5 = uVar130;
    uStack_de4 = uVar22;
    FUN_7103720ad0(puVar29,&local_e00);
  }
  if (&local_e00 == local_de0) {
    pcVar37 = *(code **)(*(long *)local_de0 + 0x20);
LAB_7103744a28:
    (*pcVar37)();
  }
  else if (local_de0 != (uint *)0x0) {
    pcVar37 = *(code **)(*(long *)local_de0 + 0x28);
    goto LAB_7103744a28;
  }
  local_df8 = 0x3720ff0;
  uStack_df4 = 0x71;
  local_de0 = &local_e00;
  local_e00 = 0x523bc68;
  uStack_dfc = 0x71;
  local_df0 = 0;
  uStack_def = 0;
  uVar45 = *(ulong *)(puVar34 + 0x30);
  if (uVar45 < *(ulong *)(puVar34 + 0x34)) {
    *(ulong *)(uVar45 + 0x20) = uVar45;
    local_de8 = uVar129;
    uStack_de7 = uVar140;
    uStack_de5 = uVar130;
    uStack_de4 = uVar22;
    (*(code *)PTR_FUN_710523bc80)();
    *(long *)(puVar34 + 0x30) = *(long *)(puVar34 + 0x30) + 0x30;
  }
  else {
    local_de8 = uVar129;
    uStack_de7 = uVar140;
    uStack_de5 = uVar130;
    uStack_de4 = uVar22;
    FUN_7103720ad0(puVar29,&local_e00);
  }
  if (&local_e00 == local_de0) {
    pcVar37 = *(code **)(*(long *)local_de0 + 0x20);
LAB_7103744ab0:
    (*pcVar37)();
  }
  else if (local_de0 != (uint *)0x0) {
    pcVar37 = *(code **)(*(long *)local_de0 + 0x28);
    goto LAB_7103744ab0;
  }
  local_df8 = 0x3721040;
  uStack_df4 = 0x71;
  local_de0 = &local_e00;
  local_e00 = 0x523bc68;
  uStack_dfc = 0x71;
  local_df0 = 0;
  uStack_def = 0;
  uVar45 = *(ulong *)(puVar34 + 0x30);
  if (uVar45 < *(ulong *)(puVar34 + 0x34)) {
    *(ulong *)(uVar45 + 0x20) = uVar45;
    local_de8 = uVar129;
    uStack_de7 = uVar140;
    uStack_de5 = uVar130;
    uStack_de4 = uVar22;
    (*(code *)PTR_FUN_710523bc80)();
    *(long *)(puVar34 + 0x30) = *(long *)(puVar34 + 0x30) + 0x30;
  }
  else {
    local_de8 = uVar129;
    uStack_de7 = uVar140;
    uStack_de5 = uVar130;
    uStack_de4 = uVar22;
    FUN_7103720ad0(puVar29,&local_e00);
  }
  if (&local_e00 == local_de0) {
    pcVar37 = *(code **)(*(long *)local_de0 + 0x20);
LAB_7103744b38:
    (*pcVar37)();
  }
  else if (local_de0 != (uint *)0x0) {
    pcVar37 = *(code **)(*(long *)local_de0 + 0x28);
    goto LAB_7103744b38;
  }
  local_df8 = 0x37212a0;
  uStack_df4 = 0x71;
  local_de0 = &local_e00;
  local_e00 = 0x523bc68;
  uStack_dfc = 0x71;
  local_df0 = 0;
  uStack_def = 0;
  uVar45 = *(ulong *)(puVar34 + 0x30);
  if (uVar45 < *(ulong *)(puVar34 + 0x34)) {
    *(ulong *)(uVar45 + 0x20) = uVar45;
    local_de8 = uVar129;
    uStack_de7 = uVar140;
    uStack_de5 = uVar130;
    uStack_de4 = uVar22;
    (*(code *)PTR_FUN_710523bc80)();
    *(long *)(puVar34 + 0x30) = *(long *)(puVar34 + 0x30) + 0x30;
  }
  else {
    local_de8 = uVar129;
    uStack_de7 = uVar140;
    uStack_de5 = uVar130;
    uStack_de4 = uVar22;
    FUN_7103720ad0(puVar29,&local_e00);
  }
  if (&local_e00 == local_de0) {
    pcVar37 = *(code **)(*(long *)local_de0 + 0x20);
LAB_7103744bc0:
    (*pcVar37)();
  }
  else if (local_de0 != (uint *)0x0) {
    pcVar37 = *(code **)(*(long *)local_de0 + 0x28);
    goto LAB_7103744bc0;
  }
  local_df8 = 0x37212c0;
  uStack_df4 = 0x71;
  local_de0 = &local_e00;
  local_e00 = 0x523bc68;
  uStack_dfc = 0x71;
  local_df0 = 0;
  uStack_def = 0;
  uVar45 = *(ulong *)(puVar34 + 0x30);
  if (uVar45 < *(ulong *)(puVar34 + 0x34)) {
    *(ulong *)(uVar45 + 0x20) = uVar45;
    local_de8 = uVar129;
    uStack_de7 = uVar140;
    uStack_de5 = uVar130;
    uStack_de4 = uVar22;
    (*(code *)PTR_FUN_710523bc80)();
    *(long *)(puVar34 + 0x30) = *(long *)(puVar34 + 0x30) + 0x30;
  }
  else {
    local_de8 = uVar129;
    uStack_de7 = uVar140;
    uStack_de5 = uVar130;
    uStack_de4 = uVar22;
    FUN_7103720ad0(puVar29,&local_e00);
  }
  if (&local_e00 == local_de0) {
    pcVar37 = *(code **)(*(long *)local_de0 + 0x20);
LAB_7103744c48:
    (*pcVar37)();
  }
  else if (local_de0 != (uint *)0x0) {
    pcVar37 = *(code **)(*(long *)local_de0 + 0x28);
    goto LAB_7103744c48;
  }
  *puVar28 = puVar34;
  DAT_710593a218 = puVar28;
LAB_7103744c54:
  DAT_710593a440 = 0;
  DAT_710523c000 = 1;
  nn::ro::Initialize();
  lVar52 = DAT_7105331f20;
  if (uVar2 < *(uint *)(DAT_7105331f20 + 0x48)) {
    std::__1::recursive_mutex::lock();
    lVar49 = *(long *)(lVar52 + 0x40);
    if ((*(byte *)(lVar49 + uVar26 * 0x48 + 8) & 1) != 0) {
      FUN_710353eff0(lVar52,lVar49 + uVar26 * 0x48);
    }
    std::__1::recursive_mutex::unlock();
  }
  return;
}

