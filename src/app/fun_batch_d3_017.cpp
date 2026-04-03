#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7100 address range, batch d3-017
// Pool-d worker: auto-generated from Ghidra decompilation

// ---- External declarations -----------------------------------------------

// External FUN_* forward declarations
extern void FUN_7100127500(u64);

// ---- Functions ---------------------------------------------------------------
// 0x7100112be0 — SetUserPasswordEnabled: write param_2&1 to +0x234 (16 bytes)
void FUN_7100112be0(s64 param_1, u8 param_2)
{
    *(u8 *)(param_1 + 0x234) = param_2 & 1;
}

// 0x7100112bf0 — SetSystemPasswordEnabled: write param_2&1 to +0x235 (16 bytes)
void FUN_7100112bf0(s64 param_1, u8 param_2)
{
    *(u8 *)(param_1 + 0x235) = param_2 & 1;
}

// 0x7100112c00 — SetSessionType: set type and enabled flag (16 bytes)
void FUN_7100112c00(s64 param_1, u32 param_2, u8 param_3)
{
    *(u32 *)(param_1 + 0x238) = param_2;
    *(u8 *)(param_1 + 0x23c) = param_3 & 1;
}
// 0x7100114d90 — SetApplicationDataEnabled: write param_2&1 to +0x97f (16 bytes)
void FUN_7100114d90(s64 param_1, u8 param_2)
{
    *(u8 *)(param_1 + 0x97f) = param_2 & 1;
}
