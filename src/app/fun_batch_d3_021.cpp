#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7100 address range, batch d3-021
// Pool-d worker: auto-generated from Ghidra decompilation

// ---- External declarations -----------------------------------------------

// External FUN_* forward declarations
extern void FUN_710015ffc0(s64);
extern void FUN_7100181270(s64);
extern void FUN_710017f100(s64);
// 0x7100161fa0 — getter: return u64 at +0x90 (GetStation) (16 bytes)
u64 FUN_7100161fa0(s64 param_1)
{
    return *(u64 *)(param_1 + 0x90);
}
