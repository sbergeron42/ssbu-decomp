#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7100 address range, batch d3-011
// Pool-d worker: auto-generated from Ghidra decompilation

// ---- External declarations -----------------------------------------------

extern "C" {
    int strcmp(const char *, const char *);
}

// External data
extern u8 PTR_DAT_71052a3510[];
extern u8 PTR_DAT_71052a3530[];
extern u8 PTR_DAT_71052a3648[];

// External FUN_* forward declarations
extern void FUN_7100057350(s64 *, u64, u64, u64, u64);
extern void FUN_7100048dd0(void);
extern void FUN_7100031e90(u64, u32, u32, s64, u32, u64);
extern void FUN_71000325b0(u64, u64, s64, u32, u32);
extern void FUN_7100059f90(u8 *, u64, s64);
extern void FUN_7100059760(u64, u8 *, u32);
extern void FUN_710003e230(s64, u32);
extern void FUN_7100078b00(u64, s64);

// ---- Functions ---------------------------------------------------------------
// 0x710004f860 — type guard + 2x strcmp: check +0x10==8, compare two string fields (64 bytes)
bool FUN_710004f860(s64 param_1, s64 param_2)
{
    s32 iVar1;

    if (*(s32 *)(param_2 + 0x10) != 8) {
        return false;
    }
    iVar1 = strcmp(*(const char **)(param_2 + 0x20), *(const char **)(param_1 + 0x10));
    if (iVar1 != 0) {
        return false;
    }
    iVar1 = strcmp(*(const char **)(param_2 + 0x28), *(const char **)(param_1 + 0x18));
    return iVar1 == 0;
}

// 0x71000500a0 — delegate + conditional self-insert: call update, optionally add to list (64 bytes)
void FUN_71000500a0(s64 param_1, u32 param_2)
{
    FUN_710003e230(param_1, param_2 & 1);
    if ((param_2 & 1) == 0) {
        *(u32 *)(param_1 + 0x3c) = 0;
        return;
    }
    if (*(s64 *)(param_1 + 0x50) != param_1 + 0x48) {
        return;
    }
    FUN_7100078b00(*(u64 *)(*(s64 *)(param_1 + 0x58) + 0x60), param_1);
}
