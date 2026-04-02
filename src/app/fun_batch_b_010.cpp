#include "types.h"

// Batch decompiled via Ghidra MCP — pool-b, batch 010
// Range: 0x7101000000 — 0x7101FFFFFF

// Forward declarations
extern "C" s32 __cxa_guard_acquire(s64 *);
extern "C" void __cxa_guard_release(s64 *);
extern "C" void FUN_710114d080(u64, u64, u32);

// Data symbols
extern u64 DAT_71052c0980;
extern void *DAT_71052c0988;
extern u8 PTR_LAB_7105038af0;

// ── Guard-init vtable setter ────────────────────────────────────────────────

// 0x7101120880
void FUN_7101120880(u64 param_1, s64 param_2)
{
  s32 iVar1;

  if ((DAT_71052c0980 & 1) == 0) {
    iVar1 = __cxa_guard_acquire((s64 *)&DAT_71052c0980);
    if (iVar1 != 0) {
      DAT_71052c0988 = &PTR_LAB_7105038af0;
      __cxa_guard_release((s64 *)&DAT_71052c0980);
    }
  }
  *(void ***)(param_2 + 0x318) = &DAT_71052c0988;
  return;
}

// ── Tiny vtable call wrapper ────────────────────────────────────────────────

// 0x7101124170
u64 FUN_7101124170(s64 *param_1)
{
  (*(void (*)(u32, s64 *, s32))(*param_1 + 0x78))(0x3f800000, param_1, 1);
  return 1;
}

// ── FUN_710114d080 wrappers ─────────────────────────────────────────────────

// 0x710114d060
u64 FUN_710114d060(u64 param_1, u64 param_2)
{
  FUN_710114d080(param_1, param_2, 0xffffffff);
  return 1;
}

// 0x710114d240
u64 FUN_710114d240(u64 param_1, u64 param_2)
{
  FUN_710114d080(param_1, param_2, 0);
  return 1;
}

// 0x710114d260
u64 FUN_710114d260(u64 param_1, u64 param_2)
{
  FUN_710114d080(param_1, param_2, 0xffffffff);
  return 1;
}

// 0x710114da20
u64 FUN_710114da20(u64 param_1, u64 param_2)
{
  FUN_710114d080(param_1, param_2, 0xffffffff);
  return 1;
}

// ── Status-kind switch functions ────────────────────────────────────────────
// Return 1 if the current status kind is one of a set of ground/aerial states.

// 0x710116a3b0
u64 FUN_710116a3b0(s64 param_1)
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

// 0x710116b7d0
u64 FUN_710116b7d0(s64 param_1)
{
  s32 iVar1;

  iVar1 = (*(s32(*)(void))(*(s64*)(*(s64*)(*(s64*)(param_1 + 0x20) + 0x40)) + 0x110))();
  if (iVar1 < 0xd0) {
    switch(iVar1) {
    case 0:
    case 1:
    case 3:
    case 4:
    case 0xb:
    case 0xc:
    case 0xd:
    case 0xe:
    case 0xf:
    case 0x16:
    case 0x17:
    case 0x18:
    case 0x1a:
    case 0x7f:
    case 0xa7:
    case 0xa8:
    case 0xa9:
      goto return_1;
    default:
      return 0;
    }
  }
  if (iVar1 < 0x11e) {
    if ((iVar1 != 0xd0) && (iVar1 != 0x11b)) {
      return 0;
    }
  }
  else if (((iVar1 != 0x11e) && (iVar1 != 0x2ce)) && (iVar1 != 0x1dc)) {
    return 0;
  }
return_1:
  return 1;
}

// 0x710116d880
u64 FUN_710116d880(s64 param_1)
{
  s32 iVar1;

  iVar1 = (*(s32(*)(void))(*(s64*)(*(s64*)(*(s64*)(param_1 + 0x20) + 0x40)) + 0x110))();
  if (iVar1 < 0x149) {
    switch(iVar1) {
    case 0:
    case 1:
    case 3:
    case 4:
    case 6:
    case 7:
    case 8:
    case 0xb:
    case 0xc:
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
    case 0x50:
    case 0x53:
    case 0x57:
    case 0x58:
    case 0x59:
    case 0x7f:
      goto return_1;
    default:
      return 0;
    }
  }
  if (iVar1 < 0x1dc) {
    if ((iVar1 != 0x149) && (iVar1 != 0x14c)) {
      return 0;
    }
  }
  else if ((iVar1 != 0x2ce) && (iVar1 != 0x1dc)) {
    return 0;
  }
return_1:
  return 1;
}
