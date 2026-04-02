#include "types.h"

// Batch decompiled via Ghidra MCP — pool-b, batch 015
// Range: 0x71018 range

[[noreturn]] extern "C" void abort();

// Data symbols
extern u8 PTR_FUN_71050a0b28;

// ── __throw_out_of_range thunks (0x71018 range) ──────────────────────────────

// 0x7101809534
[[noreturn]] void FUN_7101809534() { abort(); }

// 0x710180fd44
[[noreturn]] void FUN_710180fd44() { abort(); }

// 0x710181dd98
[[noreturn]] void FUN_710181dd98() { abort(); }

// 0x710182e17c
[[noreturn]] void FUN_710182e17c() { abort(); }

// 0x710182e83c
[[noreturn]] void FUN_710182e83c() { abort(); }

// 0x7101850c04
[[noreturn]] void FUN_7101850c04() { abort(); }

// ── Iterator begin() vtable-stub ──────────────────────────────────────────────

// 0x710184b8d0
void FUN_710184b8d0(s64 param_1, u64 *param_2)
{
  *param_2 = (u64)&PTR_FUN_71050a0b28;
  param_2[1] = *(u64 *)(param_1 + 8);
}

// ── Trivial no-op ─────────────────────────────────────────────────────────────

// 0x710184b8f0
void FUN_710184b8f0() {}
