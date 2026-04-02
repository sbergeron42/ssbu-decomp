#include "types.h"

// Batch decompiled via Ghidra MCP -- pool-b, batch 012
// Range: 0x71013 range

[[noreturn]] extern "C" void abort();
extern "C" s32 __cxa_guard_acquire(s64 *);
extern "C" void __cxa_guard_release(s64 *);
extern "C" long FUN_7100646fc0(u64);

// Data symbols
extern u64 DAT_71052c0bc0;
extern void *DAT_71052c0bc8;
extern u8 PTR_LAB_710505be38;

// ── Guard-init vtable setter ─────────────────────────────────────────────────

// 0x710130e1d0
void FUN_710130e1d0(u64 param_1, s64 param_2)
{
  s32 iVar1;

  if ((DAT_71052c0bc0 & 1) == 0) {
    iVar1 = __cxa_guard_acquire((s64 *)&DAT_71052c0bc0);
    if (iVar1 != 0) {
      DAT_71052c0bc8 = &PTR_LAB_710505be38;
      __cxa_guard_release((s64 *)&DAT_71052c0bc0);
    }
  }
  *(void ***)(param_2 + 0x318) = &DAT_71052c0bc8;
  return;
}

// ── Status-kind check ─────────────────────────────────────────────────────────

// 0x710130f1d0
u64 FUN_710130f1d0(s64 param_1)
{
  s32 iVar1;

  iVar1 = (*(s32(*)(void))(*(s64*)(*(s64*)(*(s64*)(param_1 + 0x20) + 0x40)) + 0x110))();
  return iVar1 != 0x1e3;
}

// ── __throw_out_of_range thunk ────────────────────────────────────────────────

// 0x71013165bc
[[noreturn]] void FUN_71013165bc() { abort(); }

// ── Simple vtable wrappers ────────────────────────────────────────────────────

// 0x71013184a0
u32 FUN_71013184a0(s64 *param_1)
{
  u32 uVar1;

  uVar1 = (*(u32(*)(void))(*param_1 + 0x130))();
  return ~uVar1 & 1;
}

// 0x7101318670
u64 FUN_7101318670(s64 param_1)
{
  s64 lVar1;

  lVar1 = FUN_7100646fc0(*(u64 *)(param_1 + 0x10));
  return *(s8 *)(*(s64 *)(lVar1 + 8) + 0x9c6) == '\0';
}

// ── Work-flag vtable wrappers ─────────────────────────────────────────────────

// 0x71013272d0
u64 FUN_71013272d0(u64 param_1, s64 param_2)
{
  s64 *plVar1;

  plVar1 = *(s64 **)(param_2 + 0x50);
  (*(void(*)(s64 *, u32, s32))(*(s64*)(**(s64**)(param_2 + 0x40) + 0x48)))(*(s64 **)(param_2 + 0x40), 0x122, 0);
  (*(void(*)(s64 *, u32, u32))(*(s64*)(*plVar1 + 0xa0)))(plVar1, 2, 0x11000005);
  (*(void(*)(s64 *, u32, u32))(*(s64*)(*plVar1 + 0xa0)))(plVar1, 0, 0x11000006);
  (*(void(*)(s64 *, u32, u32))(*(s64*)(*plVar1 + 0xa0)))(plVar1, 0, 0x11000007);
  return 1;
}

// 0x71013287b0
u64 FUN_71013287b0(u64 param_1, s64 param_2)
{
  (*(void(*)(s64 *, u32))(*(s64*)(**(s64**)(param_2 + 0x50) + 0x110)))(*(s64 **)(param_2 + 0x50), 0x2100000d);
  return 1;
}

// 0x71013292b0
u32 FUN_71013292b0(u64 param_1, s64 param_2)
{
  u32 uVar1;

  uVar1 = (*(u32(*)(s64 *, u32))(*(s64*)(**(s64**)(param_2 + 0x50) + 0x108)))(*(s64 **)(param_2 + 0x50), 0x2100000c);
  return ~uVar1 & 1;
}

// 0x7101329670
u32 FUN_7101329670(u64 param_1, s64 param_2)
{
  u32 uVar1;

  uVar1 = (*(u32(*)(s64 *, u32))(*(s64*)(**(s64**)(param_2 + 0x50) + 0x108)))(*(s64 **)(param_2 + 0x50), 0x2100000c);
  return ~uVar1 & 1;
}

// 0x7101329890
u32 FUN_7101329890(u64 param_1, s64 param_2)
{
  u32 uVar1;

  uVar1 = (*(u32(*)(s64 *, u32))(*(s64*)(**(s64**)(param_2 + 0x50) + 0x108)))(*(s64 **)(param_2 + 0x50), 0x2100000c);
  return ~uVar1 & 1;
}

// 0x710132d3c0
u64 FUN_710132d3c0(u64 param_1, s64 param_2)
{
  (*(void(*)(s64 *, u32))(*(s64*)(**(s64**)(param_2 + 0x50) + 0x110)))(*(s64 **)(param_2 + 0x50), 0x2100000d);
  return 1;
}

// ── __throw_out_of_range thunks ───────────────────────────────────────────────

// 0x710133066c
[[noreturn]] void FUN_710133066c() { abort(); }

// 0x7101330a4c
[[noreturn]] void FUN_7101330a4c() { abort(); }

// 0x710133104c
[[noreturn]] void FUN_710133104c() { abort(); }

// 0x710133162c
[[noreturn]] void FUN_710133162c() { abort(); }

// 0x710133173c
[[noreturn]] void FUN_710133173c() { abort(); }

// 0x710133f734
[[noreturn]] void FUN_710133f734() { abort(); }
