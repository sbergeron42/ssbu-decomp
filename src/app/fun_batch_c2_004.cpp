#include "types.h"

// Batch decompiled via Ghidra MCP -- pool-c, batch 004
// Range: 0x7102000000 -- 0x7102FFFFFF

// Forward declarations
[[noreturn]] extern "C" void abort();
extern u8 DAT_7105157768;

// ── __throw_out_of_range thunks ───────────────────────────────────────────────

// 0x710253e3ac
[[noreturn]] void FUN_710253e3ac()
{
  abort();
}

// 0x710257eb3c
[[noreturn]] void FUN_710257eb3c()
{
  abort();
}

// 0x7102ce204c
[[noreturn]] void FUN_7102ce204c()
{
  abort();
}

// 0x71027cea9c
[[noreturn]] void FUN_71027cea9c()
{
  abort();
}

// 0x710287787c
[[noreturn]] void FUN_710287787c()
{
  abort();
}

// 0x7102898d6c
[[noreturn]] void FUN_7102898d6c()
{
  abort();
}

// 0x7102898efc
[[noreturn]] void FUN_7102898efc()
{
  abort();
}

// 0x710293a80c
[[noreturn]] void FUN_710293a80c()
{
  abort();
}

// 0x7102c7aa8c
[[noreturn]] void FUN_7102c7aa8c()
{
  abort();
}

// 0x7102cbf3cc
[[noreturn]] void FUN_7102cbf3cc()
{
  abort();
}

// 0x7102df744c
[[noreturn]] void FUN_7102df744c()
{
  abort();
}

// 0x7102f408ec
[[noreturn]] void FUN_7102f408ec()
{
  abort();
}

// ── real functions ────────────────────────────────────────────────────────────

// 0x7102f747f0
// Sets param_2[0] = vtable ptr, copies 2 fields from param_1 struct
void FUN_7102f747f0(s64 param_1, u64 *param_2)
{
  u64 uVar1;

  *param_2 = (u64)&DAT_7105157768;
  uVar1 = *(u64 *)(param_1 + 0x10);
  param_2[1] = *(u64 *)(param_1 + 8);
  param_2[2] = uVar1;
  return;
}
