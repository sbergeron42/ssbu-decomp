#include "types.h"

// Batch decompiled via Ghidra MCP — pool-c, batch 011
// Range: 0x7102000000 — 0x7102FFFFFF

// Forward declarations
[[noreturn]] extern "C" void abort();
extern void *PTR_LAB_71050b9f88;

// ── __throw_out_of_range thunks ───────────────────────────────────────────────

// 0x710254012c
[[noreturn]] void FUN_710254012c()
{
  abort();
}

// 0x710254026c
[[noreturn]] void FUN_710254026c()
{
  abort();
}

// 0x710255774c
[[noreturn]] void FUN_710255774c()
{
  abort();
}

// 0x7102740dbc
[[noreturn]] void FUN_7102740dbc()
{
  abort();
}

// 0x71027701ac
[[noreturn]] void FUN_71027701ac()
{
  abort();
}

// 0x71027cdf0c
[[noreturn]] void FUN_71027cdf0c()
{
  abort();
}

// 0x71028128dc
[[noreturn]] void FUN_71028128dc()
{
  abort();
}

// 0x710287793c
[[noreturn]] void FUN_710287793c()
{
  abort();
}

// 0x7102878d3c
[[noreturn]] void FUN_7102878d3c()
{
  abort();
}

// 0x710290a73c
[[noreturn]] void FUN_710290a73c()
{
  abort();
}

// 0x7102a3f3ec
[[noreturn]] void FUN_7102a3f3ec()
{
  abort();
}

// 0x7102b23dec
[[noreturn]] void FUN_7102b23dec()
{
  abort();
}

// 0x7102ce1f0c
[[noreturn]] void FUN_7102ce1f0c()
{
  abort();
}

// 0x7102d9e4ac
[[noreturn]] void FUN_7102d9e4ac()
{
  abort();
}

// 0x7102dc250c
[[noreturn]] void FUN_7102dc250c()
{
  abort();
}

// 0x7102e296bc
[[noreturn]] void FUN_7102e296bc()
{
  abort();
}

// 0x7102e2a1ec
[[noreturn]] void FUN_7102e2a1ec()
{
  abort();
}

// 0x7102e756ac
[[noreturn]] void FUN_7102e756ac()
{
  abort();
}

// 0x7102eb658c
[[noreturn]] void FUN_7102eb658c()
{
  abort();
}

// 0x7102f40b9c
[[noreturn]] void FUN_7102f40b9c()
{
  abort();
}

// 0x7102f5ab1c
[[noreturn]] void FUN_7102f5ab1c()
{
  abort();
}

// 0x7102f7a65c
[[noreturn]] void FUN_7102f7a65c()
{
  abort();
}

// 0x7102f7aadc
[[noreturn]] void FUN_7102f7aadc()
{
  abort();
}

// ── real functions ────────────────────────────────────────────────────────────

// 0x7102407130
// Initialises 2-field object: sets vtable ptr then copies one field from param_1
void FUN_7102407130(s64 param_1, u64 *param_2)
{
  *param_2 = (u64)&PTR_LAB_71050b9f88;
  param_2[1] = *(u64 *)(param_1 + 8);
  return;
}
