#include "types.h"

// MEDIUM-tier FUN_* functions -- 0x71037/71039 address range, batch d-020
// Pool-d worker: auto-generated from Ghidra decompilation

// ---- External declarations -----------------------------------------------

extern u64  FUN_71037adee0(u32, u32);
extern void FUN_71037ade50(u64, u64, u32*);

extern void FUN_710392ed30(u64);

extern void FUN_710393ead0(s32);

extern void FUN_710393e310(u64, s32, u32, u64);

// ---- Functions ---------------------------------------------------------------

// 0x71037b0a90 -- paired FUN_71037adee0 calls + FUN_71037ade50, return first result (80 bytes)
u64 FUN_71037b0a90(u32 *param_1, u32 *param_2)
{
    u64 uVar1;
    u64 uVar2;
    u32 local_18[2];

    uVar1 = FUN_71037adee0(*param_1, *param_2);
    uVar2 = FUN_71037adee0(param_1[1], param_2[1]);
    FUN_71037ade50(uVar1, uVar2, local_18);
    return local_18[0];
}

// 0x710392ec50 -- wrapper: FUN_710392ed30(param_1) (48 bytes)
__attribute__((optnone))
void FUN_710392ec50(u64 param_1)
{
    FUN_710392ed30(param_1);
}

// 0x710393ea00 -- call FUN_710393ead0(1) (48 bytes)
__attribute__((optnone))
void FUN_710393ea00(void)
{
    FUN_710393ead0(1);
}

// 0x710393e2c0 -- hash wrapper: FUN_710393e310(param_1, 8, 0xd50dcc1b, param_2) (64 bytes)
__attribute__((optnone))
void FUN_710393e2c0(u64 param_1, u64 param_2)
{
    FUN_710393e310(param_1, 8, 0xd50dcc1b, param_2);
}
