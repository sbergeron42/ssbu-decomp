#include "types.h"

// Batch decompiled via Ghidra MCP -- pool-b, batch 014
// Range: 0x71015-0x71016 range

[[noreturn]] extern "C" void abort();

// ── __throw_out_of_range thunks (0x71015 range) ──────────────────────────────

// 0x7101513e30
[[noreturn]] void FUN_7101513e30() { abort(); }

// 0x7101513fc4
[[noreturn]] void FUN_7101513fc4() { abort(); }

// 0x7101514090
[[noreturn]] void FUN_7101514090() { abort(); }

// 0x7101514224
[[noreturn]] void FUN_7101514224() { abort(); }

// ── Simple vtable dispatch wrappers (0x71015 range) ──────────────────────────

// addr-TBD-710151a710
u64 FUN_710151a710(u64 param_1, s64 *param_2)
{
  (*(void(*)(s64 *))(*param_2 + 0x10))(param_2);
  return 0;
}

// addr-TBD-710151a740
u64 FUN_710151a740(u64 param_1, s64 *param_2)
{
  (*(void(*)(s64 *))(*param_2 + 0x10))(param_2);
  return 0;
}

// ── __throw_out_of_range thunks (0x71016 range) ──────────────────────────────

// 0x7101607420
[[noreturn]] void FUN_7101607420() { abort(); }

// 0x710160a740
[[noreturn]] void FUN_710160a740() { abort(); }

// ── Simple vtable call wrappers (0x71016 range) ──────────────────────────────

// addr-TBD-71016158b0
void FUN_71016158b0(s64 *param_1)
{
  (*(void(*)(void))(*param_1 + 0xc0))();
}

// addr-TBD-71016158d0
u32 FUN_71016158d0(s64 *param_1)
{
  return (*(u32(*)(void))(*param_1 + 0xc0))();
}
