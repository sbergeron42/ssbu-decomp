#include "types.h"

// Batch decompiled via Ghidra MCP — pool-b, batch 008
// Range: 0x7101000000 — 0x7101FFFFFF

[[noreturn]] extern "C" void abort();
extern "C" s32 __cxa_guard_acquire(s64 *);
extern "C" void __cxa_guard_release(s64 *);

// Data symbols
extern u64 DAT_71052c08b8;
extern void *DAT_71052c08c0;
extern u8 PTR_LAB_71050228b8;

// ── Guard init / vtable setter ────────────────────────────────────────────────

// 0x7101005830
void FUN_7101005830(u64 param_1, s64 param_2)
{
  s32 iVar1;

  if ((DAT_71052c08b8 & 1) == 0) {
    iVar1 = __cxa_guard_acquire((s64 *)&DAT_71052c08b8);
    if (iVar1 != 0) {
      DAT_71052c08c0 = &PTR_LAB_71050228b8;
      __cxa_guard_release((s64 *)&DAT_71052c08b8);
    }
  }
  *(void ***)(param_2 + 0x318) = &DAT_71052c08c0;
  *(u8 *)(param_2 + 0xe8) = 7;
  return;
}

// ── __throw_out_of_range thunks ───────────────────────────────────────────────

// 0x710104c2e4
[[noreturn]] void FUN_710104c2e4() { abort(); }

// 0x710104c6f4
[[noreturn]] void FUN_710104c6f4() { abort(); }

// 0x710104c8c4
[[noreturn]] void FUN_710104c8c4() { abort(); }

// 0x710104ccac
[[noreturn]] void FUN_710104ccac() { abort(); }

// 0x710104ce7c
[[noreturn]] void FUN_710104ce7c() { abort(); }

// 0x710104cfe4
[[noreturn]] void FUN_710104cfe4() { abort(); }

// 0x710106031c
[[noreturn]] void FUN_710106031c() { abort(); }

// 0x710106040c
[[noreturn]] void FUN_710106040c() { abort(); }

// 0x710106050c
[[noreturn]] void FUN_710106050c() { abort(); }
