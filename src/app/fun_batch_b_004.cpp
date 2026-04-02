#include "types.h"

// Batch decompiled via Ghidra MCP -- pool-b, batch 004
// Range: 0x7101000000 -- 0x7101FFFFFF

// Forward declarations
extern "C" void FUN_7103779b70(s64, ...);
extern "C" void FUN_7103779cd0(s64, const char *, ...);
extern "C" void FUN_71037a1cc0(s64, u32 *, s32, s32);
extern "C" void FUN_710326f0f0(s64 *, s32, s32, s32, s32, s32, s32);
extern "C" void FUN_710392e590(...);
extern "C" void FUN_7101c08b50(u8 *, u8 *, u8 *, u8 *, u8 *);

// 0x7101bbbf80
void FUN_7101bbbf80(s64 param_1, u32 param_2, u64 param_3)
{
  switch(param_2) {
  case 2:
    FUN_7103779cd0(param_3, "mel_training_cp_lv_n", 1, *(s32 *)(param_1 + 0xb50) + 1);
    return;
  case 3:
    FUN_7103779b70(param_3, "mel_training_cp_walk");
    return;
  case 4:
    FUN_7103779b70(param_3, "mel_training_cp_escape");
    return;
  case 5:
    FUN_7103779b70(param_3, "mel_training_cp_jump");
    return;
  case 6:
    FUN_7103779b70(param_3, "mel_training_cp_attack");
    return;
  case 7:
    FUN_7103779b70(param_3, "mel_training_cp_smash_side");
    return;
  case 8:
    FUN_7103779b70(param_3, "mel_training_cp_operation");
    return;
  default:
    FUN_7103779b70(param_3, "mel_training_cp_stop");
    return;
  }
}

// 0x7101bcbe40
void FUN_7101bcbe40(s64 param_1, s32 param_2)
{
  s64 lVar1;
  u32 local_14;

  if ((u32)(param_2 - 1) < 0xb) {
    param_1 = param_1 + 0x2e0;
    switch(param_2) {
    case 1:
      FUN_7103779b70(param_1, "mel_mockbattle_entry");
      return;
    case 2:
      FUN_7103779b70(param_1, "mel_mockbattle_hope_join");
      return;
    case 3:
      FUN_7103779b70(param_1, "mel_mockbattle_preparation");
      return;
    case 4:
      FUN_7103779b70(param_1, "mel_mockbattle_setting_rule");
      return;
    case 5:
      FUN_7103779b70(param_1, "mel_mockbattle_sel_stage");
      return;
    default:
      FUN_7103779b70(param_1, "mel_mockbattle_sel_fighter");
      return;
    case 8:
      FUN_7103779b70(param_1, "mel_mockbattle_check_rule");
      return;
    case 9:
      FUN_7103779b70(param_1, "mel_mockbattle_result");
      return;
    case 10:
      FUN_7103779b70(param_1, "mel_mockbattle_bye");
      return;
    case 0xb:
      FUN_7103779b70(param_1, "mel_mockbattle_battle");
      return;
    }
  }
  lVar1 = *(s64 *)(*(s64 *)(param_1 + 0x2e8) + 0x10);
  if (lVar1 != 0) {
    local_14 = 0;
    FUN_71037a1cc0(lVar1, &local_14, 0, 0);
  }
  return;
}

// 0x7101c043c0
u32 FUN_7101c043c0(s64 param_1, s64 param_2, u8 param_3)
{
  u16 uVar1;
  u64 uVar2;
  u32 uVar3;
  s32 iVar4;
  s64 local_38;
  s64 local_30;

  switch(param_3) {
  case 2:
    return (u32)*(u8 *)(param_1 + 1);
  case 3:
    return (u32)*(u8 *)(param_1 + 2);
  case 4:
    break;
  case 5:
    return *(u8 *)(param_1 + 6) - 1;
  case 6:
    return (u32)*(u8 *)(param_1 + 7);
  case 7:
    return (u32)*(u8 *)(param_1 + 8);
  case 8:
    return (u32)*(u8 *)(param_1 + 9);
  case 9:
    return (u32)*(u8 *)(param_1 + 10);
  case 10:
    return (u32)*(u8 *)(param_1 + 0xb);
  case 0xb:
    return (u32)*(u8 *)(param_1 + 0xc);
  default:
    return 0;
  case 0xe:
    return (u32)*(u8 *)(param_1 + 0xd);
  case 0xf:
    return *(u8 *)(param_1 + 0xe) - 5;
  case 0x10:
    return (u32)*(u8 *)(param_1 + 0xf);
  case 0x11:
    return (u32)*(u8 *)(param_1 + 0x10);
  case 0x12:
    return (u32)*(u8 *)(param_1 + 0x11);
  case 0x13:
    return *(u8 *)(param_1 + 0x12) - 1;
  case 0x14:
    return (u32)*(u8 *)(param_1 + 0x13);
  case 0x15:
    return (u32)*(u8 *)(param_1 + 0x14);
  case 0x16:
    return (u32)*(u8 *)(param_1 + 0x15);
  case 0x17:
    return (u32)*(u8 *)(param_1 + 0x16);
  case 0x18:
    return (u32)*(u8 *)(param_1 + 0x17);
  case 0x1b:
    if (*(s32 *)(param_2 + 4) == 0) {
      FUN_710326f0f0(&local_38, 0, 1, 1, 0, 0, 1);
      uVar2 = local_30 - local_38;
      if (local_38 != 0) {
        local_30 = local_38;
        FUN_710392e590();
      }
      iVar4 = (s32)(uVar2 >> 3);
      if (iVar4 < 0) {
        iVar4 = iVar4 + 1;
      }
      iVar4 = iVar4 >> 1;
      if (iVar4 < 2) {
        iVar4 = 1;
      }
      return iVar4 - 1;
    }
    return *(s32 *)(param_2 + 4) - 1;
  case 0x1c:
    return (u32)*(u8 *)(param_2 + 8);
  case 0x1d:
    return (u32)*(u8 *)(param_2 + 1);
  case 0x1e:
    return (u32)*(u8 *)(param_2 + 2);
  }
  uVar1 = *(u16 *)(param_1 + 4);
  if (0x5cc < (u32)((uVar1 - 1 >> 2) & 0x3fff)) {
    return 0x65;
  }
  if (0x3b < uVar1) {
    uVar3 = uVar1 / 0x3c;
    if ((u32)uVar1 != (uVar3 * 0x3c & 0xfffc)) {
      uVar3 = uVar1 / 0x3c + 1;
    }
    if (2 < uVar3) {
      uVar3 = 3;
    }
    return (uVar1 / 0x3c + uVar3) - 2;
  }
  return 0;
}

// 0x7101c045a0
s32 FUN_7101c045a0(u8 param_1)
{
  u64 uVar1;
  s32 iVar2;
  s64 local_38;
  s64 local_30;

  iVar2 = 4;
  switch(param_1) {
  case 0:
    goto switchD_7101c045c8_caseD_0;
  case 1:
  case 2:
  case 3:
    return 3;
  case 4:
    return 0x66;
  case 5:
    return 99;
  case 6:
    return 0xc;
  case 7:
    return 5;
  case 8:
    return 2;
  case 9:
    return 10;
  case 10:
    return 3;
  case 0xb:
    return 8;
  default:
    iVar2 = 0;
switchD_7101c045c8_caseD_0:
    return iVar2;
  case 0xe:
    return 2;
  case 0xf:
    return 0x10;
  case 0x10:
  case 0x11:
  case 0x12:
    return 2;
  case 0x13:
    return 3;
  case 0x14:
  case 0x15:
    return 0xb;
  case 0x16:
  case 0x17:
  case 0x18:
    return 2;
  case 0x1b:
    FUN_710326f0f0(&local_38, 0, 1, 1, 0, 0, 1);
    uVar1 = local_30 - local_38;
    if (local_38 != 0) {
      local_30 = local_38;
      FUN_710392e590();
    }
    iVar2 = (s32)(uVar1 >> 3);
    if (iVar2 < 0) {
      iVar2 = iVar2 + 1;
    }
    iVar2 = iVar2 >> 1;
    if (iVar2 < 2) {
      iVar2 = 1;
    }
    return iVar2;
  case 0x1c:
  case 0x1d:
  case 0x1e:
    return 2;
  }
}

// 0x7101c08ce0
u8 FUN_7101c08ce0(u8 *param_1, u8 *param_2)
{
  u8 bVar1;
  u8 bVar2;
  s64 lVar3;
  u8 bVar4;
  u8 *pbVar5;
  u8 bVar6;
  u8 *pbVar7;
  s64 lVar8;
  s32 iVar9;
  s64 lVar10;

  switch((s64)param_2 - (s64)param_1) {
  case 0:
  case 1:
    return true;
  case 2:
    bVar6 = *param_1;
    if (bVar6 <= param_2[-1]) {
      return true;
    }
    *param_1 = param_2[-1];
LAB_7101c08f14:
    param_2[-1] = bVar6;
    return true;
  case 3:
    bVar1 = param_1[1];
    bVar6 = *param_1;
    bVar2 = param_2[-1];
    if (bVar1 < bVar6) {
      if (bVar2 < bVar1) {
        *param_1 = bVar2;
      }
      else {
        *param_1 = bVar1;
        param_1[1] = bVar6;
        if (bVar6 <= param_2[-1]) {
          return true;
        }
        param_1[1] = param_2[-1];
      }
      goto LAB_7101c08f14;
    }
    if (bVar1 <= bVar2) {
      return true;
    }
    param_1[1] = bVar2;
    param_2[-1] = bVar1;
    bVar1 = param_1[1];
    bVar6 = *param_1;
    if (bVar6 <= bVar1) {
      return true;
    }
    goto LAB_7101c08f80;
  case 4:
    break;
  case 5:
    FUN_7101c08b50(param_1, param_1 + 1, param_1 + 2, param_1 + 3, param_2 + -1);
    return true;
  default:
    bVar1 = param_1[1];
    bVar6 = *param_1;
    bVar2 = param_1[2];
    bVar4 = bVar2;
    if (bVar1 < bVar6) {
      if (bVar2 < bVar1) {
        *param_1 = bVar2;
      }
      else {
        *param_1 = bVar1;
        param_1[1] = bVar6;
        if (bVar6 <= bVar2) goto LAB_7101c08e64;
        param_1[1] = bVar2;
      }
      param_1[2] = bVar6;
      bVar4 = bVar6;
    }
    else if (bVar2 < bVar1) {
      param_1[1] = bVar2;
      param_1[2] = bVar1;
      bVar4 = bVar1;
      if (bVar2 < bVar6) {
        *param_1 = bVar2;
        param_1[1] = bVar6;
      }
    }
LAB_7101c08e64:
    if (param_1 + 3 == param_2) {
      return true;
    }
    lVar8 = 0;
    iVar9 = 0;
    pbVar7 = param_1 + 3;
    do {
      bVar1 = *pbVar7;
      lVar3 = lVar8;
      if (bVar1 < bVar4) {
        do {
          lVar10 = lVar3;
          param_1[lVar10 + 3] = bVar4;
          pbVar5 = param_1;
          if (lVar10 == -2) goto LAB_7101c08ec8;
          bVar4 = param_1[lVar10 + 1];
          lVar3 = lVar10 + -1;
        } while (bVar1 < bVar4);
        pbVar5 = param_1 + lVar10 + 2;
LAB_7101c08ec8:
        iVar9 = iVar9 + 1;
        *pbVar5 = bVar1;
        if (iVar9 == 8) {
          return (u8)(pbVar7 + 1 == param_2);
        }
      }
      if (pbVar7 + 1 == param_2) {
        return true;
      }
      bVar4 = *pbVar7;
      lVar8 = lVar8 + 1;
      pbVar7 = pbVar7 + 1;
    } while( true );
  }
  bVar1 = param_1[1];
  bVar6 = *param_1;
  bVar2 = param_1[2];
  bVar4 = bVar2;
  if (bVar1 < bVar6) {
    if (bVar2 < bVar1) {
      *param_1 = bVar2;
    }
    else {
      *param_1 = bVar1;
      param_1[1] = bVar6;
      if (bVar6 <= bVar2) goto LAB_7101c08f48;
      param_1[1] = bVar2;
    }
    param_1[2] = bVar6;
    bVar4 = bVar6;
  }
  else if (bVar2 < bVar1) {
    param_1[1] = bVar2;
    param_1[2] = bVar1;
    bVar4 = bVar1;
    if (bVar2 < bVar6) {
      *param_1 = bVar2;
      param_1[1] = bVar6;
    }
  }
LAB_7101c08f48:
  if (bVar4 <= param_2[-1]) {
    return true;
  }
  param_1[2] = param_2[-1];
  param_2[-1] = bVar4;
  bVar1 = param_1[2];
  if (param_1[1] <= bVar1) {
    return true;
  }
  param_1[2] = param_1[1];
  bVar6 = *param_1;
  param_1[1] = bVar1;
  if (bVar6 <= bVar1) {
    return true;
  }
LAB_7101c08f80:
  *param_1 = bVar1;
  param_1[1] = bVar6;
  return true;
}
