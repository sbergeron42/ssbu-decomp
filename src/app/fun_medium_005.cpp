// fun_medium_005.cpp — Matched functions from 0x71001b range
// Cleaned: removed 10 unmatched Ghidra paste functions, kept 1 verified (M)

#include "types.h"

// 0x71001b1270 — Split u32 into quotient/remainder of 10000 (quality=M)
// Returns (quotient | remainder << 32) — used by decimal formatting
u64 FUN_71001b1270(u32 param_1)
{
    return (u64)param_1 / 10000 | (u64)(param_1 % 10000) << 0x20;
}
