#include "types.h"

// Batch decompiled via Ghidra MCP -- pool-b, batch 013
// Range: 0x71014 range

[[noreturn]] extern "C" void abort();

// Data symbols
extern u8 PTR_LAB_7105064358;
extern u8 PTR_LAB_7105064310;
extern u8 PTR_LAB_71050642c8;
extern u8 PTR_LAB_7105064280;
extern u8 PTR_LAB_7105064238;
extern u8 PTR_LAB_71050641f0;
extern u8 PTR_LAB_71050641a8;
extern u8 PTR_LAB_7105064160;
extern u8 PTR_LAB_7105064118;

// ── __throw_out_of_range thunk ────────────────────────────────────────────────

// 0x7101401580
[[noreturn]] void FUN_7101401580() { abort(); }

// ── Simple field getter ───────────────────────────────────────────────────────

// 0x7101401590
u32 FUN_7101401590(s64 param_1)
{
  return *(u32 *)(param_1 + 0x28);
}

// ── Iterator begin() vtable-stub cluster ─────────────────────────────────────
// Each function sets up an iterator pair: (vtable-ptr, data-ptr)

// 0x710140f780
void FUN_710140f780(s64 param_1, u64 *param_2)
{
  *param_2 = (u64)&PTR_LAB_7105064358;
  param_2[1] = *(u64 *)(param_1 + 8);
}

// 0x710140f990
void FUN_710140f990(s64 param_1, u64 *param_2)
{
  *param_2 = (u64)&PTR_LAB_7105064310;
  param_2[1] = *(u64 *)(param_1 + 8);
}

// 0x710140fa80
void FUN_710140fa80(s64 param_1, u64 *param_2)
{
  *param_2 = (u64)&PTR_LAB_71050642c8;
  param_2[1] = *(u64 *)(param_1 + 8);
}

// 0x710140fb80
void FUN_710140fb80(s64 param_1, u64 *param_2)
{
  *param_2 = (u64)&PTR_LAB_7105064280;
  param_2[1] = *(u64 *)(param_1 + 8);
}

// 0x710140fd10
void FUN_710140fd10(s64 param_1, u64 *param_2)
{
  *param_2 = (u64)&PTR_LAB_7105064238;
  param_2[1] = *(u64 *)(param_1 + 8);
}

// 0x710140fe20
void FUN_710140fe20(s64 param_1, u64 *param_2)
{
  *param_2 = (u64)&PTR_LAB_71050641f0;
  param_2[1] = *(u64 *)(param_1 + 8);
}

// 0x710140ff50
void FUN_710140ff50(s64 param_1, u64 *param_2)
{
  *param_2 = (u64)&PTR_LAB_71050641a8;
  param_2[1] = *(u64 *)(param_1 + 8);
}

// 0x71014100e0
void FUN_71014100e0(s64 param_1, u64 *param_2)
{
  *param_2 = (u64)&PTR_LAB_7105064160;
  param_2[1] = *(u64 *)(param_1 + 8);
}

// 0x71014101f0
void FUN_71014101f0(s64 param_1, u64 *param_2)
{
  *param_2 = (u64)&PTR_LAB_7105064118;
  param_2[1] = *(u64 *)(param_1 + 8);
}

// ── __throw_out_of_range thunks ───────────────────────────────────────────────

// 0x71014150c8
[[noreturn]] void FUN_71014150c8() { abort(); }

// 0x71014150fc
[[noreturn]] void FUN_71014150fc() { abort(); }
