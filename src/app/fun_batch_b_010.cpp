#include "types.h"

// Batch decompiled via Ghidra MCP -- pool-b, batch 010
// Range: 0x7101000000 -- 0x7101FFFFFF

// Forward declarations
extern "C" void FUN_710114d0a0(u64, u64, u32);

// ── Trivial return-zero function ────────────────────────────────────────────

// 0x7101120880
u64 FUN_7101120880() { return 0; }

// ── FUN_710114d0a0 wrapper ──────────────────────────────────────────────────

// 0x710114d260
u64 FUN_710114d260(u64 param_1, u64 param_2)
{
#ifdef MATCHING_HACK_NX_CLANG
  asm("");
#endif
  FUN_710114d0a0(param_1, param_2, 0);
  return 1;
}

// Removed: FUN_710116a3b0, FUN_710116b7d0, FUN_710116d880
// These addresses are mid-function (epilogue/non-entry) in the original binary.
