#include "types.h"

// Batch decompiled via Ghidra MCP — pool-b, batch 005
// Range: 0x7101000000 — 0x7101FFFFFF

// Forward declarations
[[noreturn]] extern "C" void abort();
extern "C" u64 FUN_7103262bf0(u64, u64);
extern "C" void FUN_7103779b70(s64, ...);
extern "C" void FUN_71037a22f0(s64, u8 *);
extern "C" void ui2d_apply_named_animation(u32, u64, const char *);

// Data symbols
extern u64 DAT_710532e730;
extern u8 DAT_7104866c2e;
extern u8 DAT_710446fbe0 __attribute__((visibility("hidden")));
extern u8 PTR_LAB_71050b0530 __attribute__((visibility("hidden")));

// 0x7101cc4bc0
u64 FUN_7101cc4bc0(u32 param_1)
{
  if (param_1 < 4) {
    return *(u64 *)(&DAT_710446fbe0 + (s64)(s32)param_1 * 8);
  }
  return 0x58ffff0000000000ULL;
}

// 0x7101cd5f40
u8 FUN_7101cd5f40(s64 param_1)
{
  u8 bVar1;
  u64 uVar2;
  s32 iVar3;
  u64 uVar4;

  switch(*(u32 *)(param_1 + 0x208)) {
  case 0:
    iVar3 = *(s32 *)(param_1 + 0x20c);
    break;
  case 1:
    uVar4 = *(u64 *)(param_1 + 0x210);
    if ((uVar4 & 0xff00000000000000ULL) == 0xc100000000000000ULL && (uVar4 & 0xffffffffffULL) != 0) {
      uVar2 = FUN_7103262bf0(*(u64 *)(*(s64 *)(DAT_710532e730 + 8) + 0x168), 0x14ca4126b0ULL);
      if ((uVar2 & 0xff00000000000000ULL) == 0xc100000000000000ULL && (uVar2 & 0xffffffffffULL) != 0) {
        if (((uVar2 ^ uVar4) & 0xffffffffffULL) != 0) {
          return true;
        }
      }
      else if ((uVar2 & 0xffffffffffULL) == 0 || (uVar2 & 0xff00000000000000ULL) != 0xc100000000000000ULL) {
        return true;
      }
    }
    if (*(s32 *)(param_1 + 0x21c) != 0) {
      return true;
    }
    iVar3 = *(s32 *)(param_1 + 0x220);
    break;
  case 2:
    uVar4 = *(u64 *)(param_1 + 0x228);
    if ((uVar4 & 0xff00000000000000ULL) == 0xc100000000000000ULL && (uVar4 & 0xffffffffffULL) != 0) {
      uVar2 = FUN_7103262bf0(*(u64 *)(*(s64 *)(DAT_710532e730 + 8) + 0x168), 0x14ca4126b0ULL);
      if ((uVar2 & 0xff00000000000000ULL) == 0xc100000000000000ULL && (uVar2 & 0xffffffffffULL) != 0) {
        if (((uVar2 ^ uVar4) & 0xffffffffffULL) != 0) {
          return true;
        }
      }
      else if ((uVar2 & 0xffffffffffULL) == 0 || (uVar2 & 0xff00000000000000ULL) != 0xc100000000000000ULL) {
        return true;
      }
    }
    if (*(s32 *)(param_1 + 0x234) != 0) {
      return true;
    }
    iVar3 = *(s32 *)(param_1 + 0x238);
    break;
  case 3:
    iVar3 = *(s32 *)(param_1 + 0x240);
    break;
  case 4:
    if (*(s32 *)(param_1 + 0x244) != 0) {
      return true;
    }
    bVar1 = (u8)(*(s32 *)(param_1 + 0x248) == 1);
    goto LAB_7101cd6094;
  case 5:
    iVar3 = *(s32 *)(param_1 + 0x24c);
    break;
  default:
    return false;
  }
  bVar1 = (u8)(iVar3 == 0);
LAB_7101cd6094:
  return !bVar1;
}

// 0x7101dd8440
void FUN_7101dd8440(s64 param_1, char param_2)
{
  switch(param_2) {
  case '\0':
    ui2d_apply_named_animation(0x3f800000, *(u64 *)(param_1 + 0xd8), "select_setorg");
    return;
  case '\x01':
    ui2d_apply_named_animation(0x3f800000, *(u64 *)(param_1 + 0xd8), "select_raise");
    return;
  case '\x02':
    ui2d_apply_named_animation(0x3f800000, *(u64 *)(param_1 + 0xd8), "select_return");
    return;
  case '\x03':
    ui2d_apply_named_animation(0x3f800000, *(u64 *)(param_1 + 0xd8), "select_recall");
    return;
  case '\x04':
  case '\x05':
    if (*(char *)(param_1 + 0x38) != '\0') {
      if (param_2 == '\x05') {
        ui2d_apply_named_animation(0x3f800000, *(u64 *)(param_1 + 0x20), "preview_01");
        return;
      }
      if (param_2 != '\x04') {
        return;
      }
      ui2d_apply_named_animation(0x3f800000, *(u64 *)(param_1 + 0x20), "preview_00");
      return;
    }
switchD_7101dd8460_caseD_8:
    ui2d_apply_named_animation(0x3f800000, *(u64 *)(param_1 + 0xd8), "select_directory");
    return;
  case '\x06':
    ui2d_apply_named_animation(0x3f800000, *(u64 *)(param_1 + 0xd8), "select_facility");
    return;
  case '\a':
    ui2d_apply_named_animation(0x3f800000, *(u64 *)(param_1 + 0xd8), "select_shop");
    return;
  case '\b':
    goto switchD_7101dd8460_caseD_8;
  default:
    return;
  }
}

// 0x7101e027f0
void FUN_7101e027f0(s64 param_1, u64 *param_2)
{
  *param_2 = (u64)&PTR_LAB_71050b0530;
  param_2[1] = *(u64 *)(param_1 + 8);
  return;
}

// 0x7101e57dc0
void FUN_7101e57dc0(s64 param_1, u32 param_2)
{
  s64 lVar1;

  switch(param_2) {
  case 0:
    FUN_7103779b70(param_1, "cam_menu_etc_help_grade");
    return;
  case 1:
    FUN_7103779b70(param_1, "cam_menu_etc_help_button_option");
    return;
  case 2:
    FUN_7103779b70(param_1, "cam_menu_etc_help_directory");
    return;
  case 3:
    FUN_7103779b70(param_1, "cam_menu_etc_help_how_to_play");
    return;
  case 4:
    FUN_7103779b70(param_1, "cam_menu_etc_help_save");
    return;
  case 5:
    FUN_7103779b70(param_1, "cam_menu_etc_help_spirits_directory");
    return;
  case 6:
    FUN_7103779b70(param_1, "cam_menu_etc_help_item_list");
    return;
  case 0xffffffff:
    lVar1 = *(s64 *)(*(s64 *)(param_1 + 8) + 0x10);
    if (lVar1 != 0) {
      FUN_71037a22f0(lVar1, &DAT_7104866c2e);
      return;
    }
  }
  return;
}

// 0x710116a3d0
u64 FUN_710116a3d0(s64 param_1)
{
  u32 uVar1;
  u64 uVar2;

  uVar1 = (*(u32(*)(void))(*(s64*)(*(s64*)(*(s64*)(param_1 + 0x20) + 0x40)) + 0x110))();
  uVar2 = 0;
  switch(uVar1) {
  case 0:
  case 1:
  case 3:
  case 4:
  case 6:
  case 7:
  case 8:
  case 0xb:
  case 0xc:
  case 0xd:
  case 0xe:
  case 0xf:
  case 0x16:
  case 0x17:
  case 0x18:
  case 0x1a:
  case 0x47:
  case 0x48:
  case 0x49:
  case 0x4a:
  case 0x4b:
  case 0x4c:
  case 0x4d:
  case 0x4e:
  case 0x4f:
  case 0x7f:
  case 0xa7:
  case 0xa8:
  case 0xa9:
  case 0xd0:
  case 0x11b:
  case 0x11e:
  case 0x149:
  case 0x14c:
    uVar2 = 1;
  }
  return uVar2;
}

// 0x71013c92b4
[[noreturn]] void FUN_71013c92b4()
{
  abort();
}
