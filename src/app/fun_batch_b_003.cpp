#include "types.h"

// Batch decompiled via Ghidra MCP -- pool-b, batch 003
// Range: 0x7101000000 -- 0x7101FFFFFF

// Forward declarations
[[noreturn]] extern "C" void abort();
extern "C" void *je_aligned_alloc(u64, u64);
extern "C" void FUN_7103776360(u64 *, u64, const char *);
extern "C" u64 FUN_7101704c50(s64);
extern "C" void FUN_710326f0f0(s64 *, s32, s32, s32, s32, s32, s32);
extern "C" u64 FUN_7101797640(u64, s32, s32);
extern "C" void FUN_710392e590(s64);
extern "C" u64 FUN_7101aab430(s32);
extern "C" s32 FUN_710328cae0(u64, u64);
extern "C" u64 FUN_7103262bf0(u64, u64);
extern "C" s32 FUN_71032b82d0(u64, u64, u32 *);
extern "C" void ui2d_apply_named_animation(u32, u64, const char *);
extern "C" void FUN_7103779b70(s64, s64);
extern "C" void FUN_7103779cd0(s64, const char *, ...);
extern "C" void FUN_710377a1a0(s64, ...);
extern "C" void FUN_710377a930(u32, s64);
extern "C" void FUN_710377aa60(u32, s64);
extern "C" void FUN_710377ab90(s64);
extern "C" void FUN_7103775b40(u64, s32);
extern "C" void FUN_71018e80b0(u64 *, u64 *, u64 *, u64 *, u64 *);
extern "C" void FUN_71019919c0(u64 *, u64 *, u64 *, u64 *, u64 *);
extern "C" s32 __cxa_guard_acquire(s64 *);
extern "C" void __cxa_guard_release(s64 *);

// Data symbols
extern u8 PTR_LAB_71050a90b8 __attribute__((visibility("hidden")));
extern u8 DAT_7104ad95d0 __attribute__((visibility("hidden")));
extern u8 PTR_DAT_710523c9a8;
extern s64 *DAT_7105331f00;
extern u64 DAT_71052c3c58;
extern u64 DAT_710532e730;
extern s64 *g_profile_chain_root;

// 0x71017ac210
void FUN_71017ac210(u64 *param_1)
{
  *param_1 = 0x69ffff0000000000ULL;
  param_1[1] = 0x69ffff0000000000ULL;
  param_1[2] = 0;
  param_1[3] = 0xd9ffff0000000000ULL;
  param_1[4] = 0;
  param_1[5] = 0xd9ffff0000000000ULL;
  return;
}

// 0x71018e8290
u8 FUN_71018e8290(u64 *param_1, u64 *param_2)
{
  u8 bVar1;
  u64 uVar2;
  u64 *puVar3;
  u64 *puVar4;
  s32 iVar5;
  u64 uVar6;
  u64 uVar7;
  u64 uVar8;
  u64 uVar9;
  u64 uVar10;
  u64 uVar11;
  u64 *puVar12;

  switch(((s64)param_2 - (s64)param_1) >> 3) {
  case 0:
  case 1:
    return true;
  case 2:
    uVar8 = *param_1;
    if ((uVar8 & 0xff0000ffffffffffULL) <= (param_2[-1] & 0xff0000ffffffffffULL)) {
      return true;
    }
    *param_1 = param_2[-1];
    break;
  case 3:
    uVar8 = *param_1;
    uVar10 = param_1[1];
    uVar2 = param_2[-1];
    uVar6 = uVar10 & 0xff0000ffffffffffULL;
    if ((uVar8 & 0xff0000ffffffffffULL) <= uVar6) {
      if (uVar6 <= (uVar2 & 0xff0000ffffffffffULL)) {
        return true;
      }
      param_1[1] = uVar2;
      param_2[-1] = uVar10;
      uVar8 = *param_1;
      if ((uVar8 & 0xff0000ffffffffffULL) <= (param_1[1] & 0xff0000ffffffffffULL)) {
        return true;
      }
      *param_1 = param_1[1];
      param_1[1] = uVar8;
      return true;
    }
    if ((uVar2 & 0xff0000ffffffffffULL) < uVar6) {
      *param_1 = uVar2;
    }
    else {
      *param_1 = uVar10;
      param_1[1] = uVar8;
      if ((uVar8 & 0xff0000ffffffffffULL) <= (param_2[-1] & 0xff0000ffffffffffULL)) {
        return true;
      }
      param_1[1] = param_2[-1];
    }
    break;
  case 4:
    uVar8 = *param_1;
    uVar10 = param_1[1];
    uVar9 = param_1[2];
    uVar7 = uVar10 & 0xff0000ffffffffffULL;
    uVar11 = uVar8 & 0xff0000ffffffffffULL;
    uVar6 = uVar9 & 0xff0000ffffffffffULL;
    uVar2 = uVar9;
    if (uVar7 < uVar11) {
      if (uVar6 < uVar7) {
        *param_1 = uVar9;
      }
      else {
        *param_1 = uVar10;
        param_1[1] = uVar8;
        if (uVar11 <= uVar6) goto LAB_71018e851c;
        param_1[1] = uVar9;
      }
      param_1[2] = uVar8;
      uVar2 = uVar8;
      uVar6 = uVar11;
    }
    else if (uVar6 < uVar7) {
      bVar1 = uVar6 < uVar11;
      param_1[1] = uVar9;
      param_1[2] = uVar10;
      uVar2 = uVar10;
      uVar6 = uVar7;
      if (bVar1) {
        *param_1 = uVar9;
        param_1[1] = uVar8;
      }
    }
LAB_71018e851c:
    if (uVar6 <= (param_2[-1] & 0xff0000ffffffffffULL)) {
      return true;
    }
    param_1[2] = param_2[-1];
    param_2[-1] = uVar2;
    uVar8 = param_1[1];
    uVar10 = param_1[2];
    if ((uVar8 & 0xff0000ffffffffffULL) <= (uVar10 & 0xff0000ffffffffffULL)) {
      return true;
    }
    param_1[1] = uVar10;
    param_1[2] = uVar8;
    uVar8 = *param_1;
    if ((uVar8 & 0xff0000ffffffffffULL) <= (uVar10 & 0xff0000ffffffffffULL)) {
      return true;
    }
    *param_1 = uVar10;
    param_1[1] = uVar8;
    return true;
  case 5:
    FUN_71018e80b0(param_1, param_1 + 1, param_1 + 2, param_1 + 3, param_2 + -1);
    return true;
  default:
    uVar8 = *param_1;
    uVar10 = param_1[1];
    uVar6 = param_1[2];
    uVar11 = uVar10 & 0xff0000ffffffffffULL;
    uVar7 = uVar8 & 0xff0000ffffffffffULL;
    uVar9 = uVar6 & 0xff0000ffffffffffULL;
    uVar2 = uVar6;
    if (uVar11 < uVar7) {
      if (uVar9 < uVar11) {
        *param_1 = uVar6;
      }
      else {
        *param_1 = uVar10;
        param_1[1] = uVar8;
        if (uVar7 <= uVar9) goto LAB_71018e8438;
        param_1[1] = uVar6;
      }
      param_1[2] = uVar8;
      uVar2 = uVar8;
    }
    else if (uVar9 < uVar11) {
      param_1[1] = uVar6;
      param_1[2] = uVar10;
      uVar2 = uVar10;
      if (uVar9 < uVar7) {
        *param_1 = uVar6;
        param_1[1] = uVar8;
      }
    }
LAB_71018e8438:
    if (param_1 + 3 == param_2) {
      return true;
    }
    iVar5 = 0;
    puVar4 = param_1 + 3;
    do {
      uVar8 = *puVar4;
      uVar10 = uVar8 & 0xff0000ffffffffffULL;
      puVar3 = puVar4;
      if (uVar10 < (uVar2 & 0xff0000ffffffffffULL)) {
        do {
          puVar12 = puVar3;
          *puVar12 = uVar2;
          puVar3 = param_1;
          if (puVar12 + -1 == param_1) goto LAB_71018e8498;
          uVar2 = puVar12[-2];
          puVar3 = puVar12 + -1;
        } while (uVar10 < (uVar2 & 0xff0000ffffffffffULL));
        puVar3 = puVar12 + -1;
LAB_71018e8498:
        iVar5 = iVar5 + 1;
        *puVar3 = uVar8;
        if (iVar5 == 8) {
          return (u8)(puVar4 + 1 == param_2);
        }
      }
      if (puVar4 + 1 == param_2) {
        return true;
      }
      uVar2 = *puVar4;
      puVar4 = puVar4 + 1;
    } while( true );
  }
  param_2[-1] = uVar8;
  return true;
}

// 0x7101991ba0
u8 FUN_7101991ba0(u64 *param_1, u64 *param_2)
{
  u8 bVar1;
  u64 uVar2;
  u64 *puVar3;
  u64 *puVar4;
  s32 iVar5;
  u64 uVar6;
  u64 uVar7;
  u64 uVar8;
  u64 uVar9;
  u64 uVar10;
  u64 uVar11;
  u64 *puVar12;

  switch(((s64)param_2 - (s64)param_1) >> 3) {
  case 0:
  case 1:
    return true;
  case 2:
    uVar8 = *param_1;
    if ((uVar8 & 0xff0000ffffffffffULL) <= (param_2[-1] & 0xff0000ffffffffffULL)) {
      return true;
    }
    *param_1 = param_2[-1];
    break;
  case 3:
    uVar8 = *param_1;
    uVar10 = param_1[1];
    uVar2 = param_2[-1];
    uVar6 = uVar10 & 0xff0000ffffffffffULL;
    if ((uVar8 & 0xff0000ffffffffffULL) <= uVar6) {
      if (uVar6 <= (uVar2 & 0xff0000ffffffffffULL)) {
        return true;
      }
      param_1[1] = uVar2;
      param_2[-1] = uVar10;
      uVar8 = *param_1;
      if ((uVar8 & 0xff0000ffffffffffULL) <= (param_1[1] & 0xff0000ffffffffffULL)) {
        return true;
      }
      *param_1 = param_1[1];
      param_1[1] = uVar8;
      return true;
    }
    if ((uVar2 & 0xff0000ffffffffffULL) < uVar6) {
      *param_1 = uVar2;
    }
    else {
      *param_1 = uVar10;
      param_1[1] = uVar8;
      if ((uVar8 & 0xff0000ffffffffffULL) <= (param_2[-1] & 0xff0000ffffffffffULL)) {
        return true;
      }
      param_1[1] = param_2[-1];
    }
    break;
  case 4:
    uVar8 = *param_1;
    uVar10 = param_1[1];
    uVar9 = param_1[2];
    uVar7 = uVar10 & 0xff0000ffffffffffULL;
    uVar11 = uVar8 & 0xff0000ffffffffffULL;
    uVar6 = uVar9 & 0xff0000ffffffffffULL;
    uVar2 = uVar9;
    if (uVar7 < uVar11) {
      if (uVar6 < uVar7) {
        *param_1 = uVar9;
      }
      else {
        *param_1 = uVar10;
        param_1[1] = uVar8;
        if (uVar11 <= uVar6) goto LAB_7101991e2c;
        param_1[1] = uVar9;
      }
      param_1[2] = uVar8;
      uVar2 = uVar8;
      uVar6 = uVar11;
    }
    else if (uVar6 < uVar7) {
      bVar1 = (u8)(uVar6 < uVar11);
      param_1[1] = uVar9;
      param_1[2] = uVar10;
      uVar2 = uVar10;
      uVar6 = uVar7;
      if (bVar1) {
        *param_1 = uVar9;
        param_1[1] = uVar8;
      }
    }
LAB_7101991e2c:
    if (uVar6 <= (param_2[-1] & 0xff0000ffffffffffULL)) {
      return true;
    }
    param_1[2] = param_2[-1];
    param_2[-1] = uVar2;
    uVar8 = param_1[1];
    uVar10 = param_1[2];
    if ((uVar8 & 0xff0000ffffffffffULL) <= (uVar10 & 0xff0000ffffffffffULL)) {
      return true;
    }
    param_1[1] = uVar10;
    param_1[2] = uVar8;
    uVar8 = *param_1;
    if ((uVar8 & 0xff0000ffffffffffULL) <= (uVar10 & 0xff0000ffffffffffULL)) {
      return true;
    }
    *param_1 = uVar10;
    param_1[1] = uVar8;
    return true;
  case 5:
    FUN_71019919c0(param_1, param_1 + 1, param_1 + 2, param_1 + 3, param_2 + -1);
    return true;
  default:
    uVar8 = *param_1;
    uVar10 = param_1[1];
    uVar6 = param_1[2];
    uVar11 = uVar10 & 0xff0000ffffffffffULL;
    uVar7 = uVar8 & 0xff0000ffffffffffULL;
    uVar9 = uVar6 & 0xff0000ffffffffffULL;
    uVar2 = uVar6;
    if (uVar11 < uVar7) {
      if (uVar9 < uVar11) {
        *param_1 = uVar6;
      }
      else {
        *param_1 = uVar10;
        param_1[1] = uVar8;
        if (uVar7 <= uVar9) goto LAB_7101991d48;
        param_1[1] = uVar6;
      }
      param_1[2] = uVar8;
      uVar2 = uVar8;
    }
    else if (uVar9 < uVar11) {
      param_1[1] = uVar6;
      param_1[2] = uVar10;
      uVar2 = uVar10;
      if (uVar9 < uVar7) {
        *param_1 = uVar6;
        param_1[1] = uVar8;
      }
    }
LAB_7101991d48:
    if (param_1 + 3 == param_2) {
      return true;
    }
    iVar5 = 0;
    puVar4 = param_1 + 3;
    do {
      uVar8 = *puVar4;
      uVar10 = uVar8 & 0xff0000ffffffffffULL;
      puVar3 = puVar4;
      if (uVar10 < (uVar2 & 0xff0000ffffffffffULL)) {
        do {
          puVar12 = puVar3;
          *puVar12 = uVar2;
          puVar3 = param_1;
          if (puVar12 + -1 == param_1) goto LAB_7101991da8;
          uVar2 = puVar12[-2];
          puVar3 = puVar12 + -1;
        } while (uVar10 < (uVar2 & 0xff0000ffffffffffULL));
        puVar3 = puVar12 + -1;
LAB_7101991da8:
        iVar5 = iVar5 + 1;
        *puVar3 = uVar8;
        if (iVar5 == 8) {
          return (u8)(puVar4 + 1 == param_2);
        }
      }
      if (puVar4 + 1 == param_2) {
        return true;
      }
      uVar2 = *puVar4;
      puVar4 = puVar4 + 1;
    } while( true );
  }
  param_2[-1] = uVar8;
  return true;
}

// 0x7101aeeac0
void FUN_7101aeeac0(s64 param_1, u64 *param_2)
{
  *param_2 = (u64)&PTR_LAB_71050a90b8;
  param_2[1] = *(u64 *)(param_1 + 8);
  return;
}

// 0x7101addcc0
void FUN_7101addcc0(u64 *param_1, u32 param_2, u64 param_3)
{
  u64 *puVar1;
  u64 uVar2;
  const char *pcVar3;
  u64 local_28;
  u32 local_14;

  switch(param_2) {
  case 0:
    pcVar3 = "set_rep_img_af";
    break;
  case 1:
    pcVar3 = "set_rep_img_pokemon";
    break;
  case 2:
    pcVar3 = "set_rep_img_item";
    break;
  case 3:
    pcVar3 = "set_rep_img_stage";
    break;
  default:
    *param_1 = (u64)&PTR_DAT_710523c9a8;
    puVar1 = (u64 *)je_aligned_alloc(0x10, 0x20);
    if (puVar1 == nullptr) {
      if (DAT_7105331f00 != nullptr) {
        local_14 = 0;
        local_28 = 0x20;
        uVar2 = (*(u64(*)(s64*, u32*, u64*))(*(s64*)(*DAT_7105331f00 + 0x30)))(DAT_7105331f00, &local_14, &local_28);
        if (((uVar2 & 1) != 0) &&
           (puVar1 = (u64 *)je_aligned_alloc(0x10, 0x20), puVar1 != nullptr))
        goto LAB_7101addd84;
      }
      puVar1 = nullptr;
    }
LAB_7101addd84:
    puVar1[2] = 0;
    puVar1[3] = 0;
    *puVar1 = 0;
    puVar1[1] = 0;
    param_1[1] = (u64)puVar1;
    return;
  case 5:
    pcVar3 = "set_rep_img_fighter";
    break;
  case 6:
    pcVar3 = "set_rep_img_fighter_00";
  }
  FUN_7103776360(param_1, param_3, pcVar3);
  return;
}

// 0x7101adddd0
void FUN_7101adddd0(u64 *param_1, s64 param_2)
{
  u8 bVar1;
  s32 iVar2;
  u64 uVar3;
  u64 uVar4;
  const char *pcVar5;
  u64 uVar6;
  u64 uVar7;
  s64 lVar8;
  u32 local_34;

  switch(*(u32 *)(param_1 + 3)) {
  case 1:
    lVar8 = *(s64 *)(DAT_710532e730 + 8);
    uVar6 = param_1[4];
    uVar3 = FUN_7103262bf0(*(u64 *)(lVar8 + 0x168), 0xfd5f7fa78ULL);
    uVar7 = uVar3 & 0xffffffffffULL;
    bVar1 = (u8)((uVar3 & 0xff00000000000000ULL) == 0xc100000000000000ULL);
    if ((uVar6 & 0xffffffffffULL) == 0) {
      if (!bVar1 || uVar7 == 0) goto LAB_7101addee4;
    }
    else if ((bVar1 && uVar7 != 0) && uVar7 == (uVar6 & 0xffffffffffULL)) {
LAB_7101addee4:
      uVar4 = *(u64 *)(param_2 + 8);
      pcVar5 = "category02";
      goto LAB_7101addefc;
    }
    local_34 = 0;
    iVar2 = FUN_71032b82d0(*(u64 *)(lVar8 + 0x1b8), *param_1, &local_34);
    uVar4 = *(u64 *)(param_2 + 8);
    if (iVar2 == 5) {
      pcVar5 = "category00";
    }
    else {
      pcVar5 = "category00_01";
    }
LAB_7101addefc:
    ui2d_apply_named_animation(0x3f800000, uVar4, pcVar5);
    return;
  case 2:
    uVar4 = *(u64 *)(param_2 + 8);
    pcVar5 = "category01";
    break;
  default:
    uVar4 = *(u64 *)(param_2 + 8);
    pcVar5 = "category05";
    break;
  case 4:
    uVar4 = *(u64 *)(param_2 + 8);
    pcVar5 = "category04";
    break;
  case 5:
    uVar4 = *(u64 *)(param_2 + 8);
    pcVar5 = "category03";
  }
  ui2d_apply_named_animation(0x3f800000, uVar4, pcVar5);
  return;
}

// 0x7101b00680
u8 FUN_7101b00680(u64 *param_1)
{
  u8 bVar1;

  bVar1 = (u8)param_1[1];
  if (bVar1 < 8) {
    if ((1 << (u64)(bVar1 & 0x1f) & 0xcbU) != 0) {
      return true;
    }
    if (bVar1 == 4) {
      return (*param_1 & 0xff0000ffffffffffULL) == 0xc100001b5affd87fULL;
    }
  }
  return false;
}

// 0x7101b43330
void FUN_7101b43330(s64 param_1, u32 param_2, s64 param_3)
{
  switch(param_2) {
  case 1:
    FUN_7103779b70(param_1 + 0x1e8, param_3 + 8);
    return;
  case 2:
    FUN_7103779cd0(param_1 + 0x1e8, "scr_appeal_starfox_line2", 2, param_3 + 8, param_3 + 0x50);
    return;
  case 3:
    FUN_7103779cd0(param_1 + 0x1e8, "scr_appeal_starfox_line3", 3, param_3 + 8, param_3 + 0x50,
                   param_3 + 0x98);
    return;
  case 4:
    FUN_7103779cd0(param_1 + 0x1e8, "scr_appeal_starfox_line4", 4, param_3 + 8, param_3 + 0x50,
                   param_3 + 0x98, param_3 + 0xe0);
    return;
  default:
    return;
  }
}

// 0x7101b433c0
void FUN_7101b433c0(s64 param_1, u32 param_2, s64 param_3)
{
  switch(param_2) {
  case 1:
    FUN_710377a1a0(param_1 + 0x1e8, param_3 + 8, 0);
    return;
  case 2:
    FUN_710377a1a0(param_1 + 0x1e8, "scr_appeal_starfox_line2", 2, param_3 + 8, param_3 + 0x50);
    return;
  case 3:
    FUN_710377a1a0(param_1 + 0x1e8, "scr_appeal_starfox_line3", 3, param_3 + 8, param_3 + 0x50,
                   param_3 + 0x98);
    return;
  case 4:
    FUN_710377a1a0(param_1 + 0x1e8, "scr_appeal_starfox_line4", 4, param_3 + 8, param_3 + 0x50,
                   param_3 + 0x98, param_3 + 0xe0);
    return;
  default:
    return;
  }
}

// 0x7101b4afe0
void FUN_7101b4afe0(s64 param_1, u32 param_2)
{
  u64 uVar1;

  switch(param_2) {
  case 0:
    param_1 = param_1 + 0x1d8;
    break;
  case 1:
    param_1 = param_1 + 0x1e8;
    break;
  case 2:
    param_1 = param_1 + 0x1f8;
    break;
  case 3:
    param_1 = param_1 + 0x208;
    break;
  case 4:
    param_1 = param_1 + 0x218;
    break;
  case 5:
    param_1 = param_1 + 0x228;
    break;
  case 6:
    param_1 = param_1 + 0x278;
    break;
  case 7:
    param_1 = param_1 + 0x238;
    break;
  case 8:
    param_1 = param_1 + 0x288;
    break;
  case 9:
    param_1 = param_1 + 0x298;
    break;
  case 10:
    param_1 = param_1 + 600;
    break;
  default:
    return;
  case 0xc:
    param_1 = param_1 + 0x268;
    break;
  case 0xd:
    uVar1 = 1;
    goto LAB_7101b4b138;
  case 0xe:
    uVar1 = 2;
    goto LAB_7101b4b138;
  case 0xf:
    uVar1 = 3;
    goto LAB_7101b4b138;
  case 0x10:
    uVar1 = 4;
    goto LAB_7101b4b138;
  case 0x11:
    uVar1 = 5;
    goto LAB_7101b4b138;
  case 0x12:
    uVar1 = 6;
    goto LAB_7101b4b138;
  case 0x13:
    uVar1 = 7;
    goto LAB_7101b4b138;
  case 0x14:
    uVar1 = 8;
LAB_7101b4b138:
    FUN_7103779cd0(param_1 + 0xa8, "mel_info_stage_poke_stadium_defeated", 1, uVar1);
    param_1 = param_1 + 0x248;
  }
  FUN_710377a930(0x3f800000, param_1);
  return;
}

// 0x7101b4f170
u8 *FUN_7101b4f170(u32 param_1)
{
  if (param_1 < 0xd) {
    return *(u8 **)(&DAT_7104ad95d0 + (s64)(s32)param_1 * 8);
  }
  return (u8 *)0xc1ffff0000000000ULL;
}

// 0x7101b508e0
void FUN_7101b508e0(s64 param_1, u32 param_2, u32 param_3, u32 param_4)
{
  u32 uVar1;

  switch(param_2) {
  case 0:
    uVar1 = 0;
    break;
  case 1:
    uVar1 = 0x3f800000;
    break;
  case 2:
    uVar1 = 0x40000000;
    break;
  case 3:
    uVar1 = 0x40400000;
    break;
  default:
    goto switchD_7101b50918_caseD_4;
  }
  FUN_710377aa60(uVar1, param_1 + 0x70);
switchD_7101b50918_caseD_4:
  if ((param_3 & 1) == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = 0x3f800000;
  }
  FUN_710377aa60(uVar1, param_1 + 0x80);
  uVar1 = 0x40000000;
  if ((param_4 & 1) == 0) {
    uVar1 = 0x3f800000;
  }
  FUN_710377a930(uVar1, param_1 + 0x60);
  return;
}

// 0x7101b95a70
void FUN_7101b95a70(s64 param_1, u32 param_2)
{
  switch(param_2) {
  case 0:
    FUN_710377ab90(param_1 + 0x4e0);
    FUN_710377ab90(param_1 + 0x520);
    return;
  case 1:
    param_1 = param_1 + 0x4c0;
    break;
  case 2:
    param_1 = param_1 + 0x4e0;
    break;
  case 3:
    param_1 = param_1 + 0x520;
    break;
  case 4:
    param_1 = param_1 + 0x500;
    break;
  default:
    return;
  }
  FUN_710377a930(0x3f800000, param_1);
  return;
}
