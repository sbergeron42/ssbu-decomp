#include "types.h"

// Batch decompiled via Ghidra MCP -- pool-e, batch 002
// Range: 0x7100000000 -- 0x7100FFFFFF

// ---- External declarations --------------------------------------------------

extern "C" {
    int strcmp(const char *, const char *);
}

// Called functions
extern u64  FUN_71000c9c60(s64);
extern u64  FUN_71000b1b90(void);
extern s64  FUN_7100130810(u64, u64);
extern void FUN_71000d4b40(s64, u32);
extern void FUN_71000d4ee0(s64, u32);
extern void FUN_71001875f0(void);
extern void FUN_7100187f50(void);
extern void FUN_710003e230(s64, u32);
extern void FUN_7100078b00(u64, s64);
extern void FUN_71000c4d90(u64);
extern u32  FUN_7100251c80(u64);
extern void thunk_FUN_7100251e90(u64);

// Data pointer variables (u8*)
extern u8 *PTR_DAT_71052a4010;
extern u8 *PTR_DAT_71052a4220;
extern u8 *PTR_DAT_71052a3d88;

// ---- Functions --------------------------------------------------------------
// 0x71000c7460
u64 FUN_71000c7460(s64 param_1)
{
    s64 lVar1;

    if (*(s64 *)(param_1 + 0x18) != 0) {
    }
    return 0;
}

// 0x71000d46d0
s64 FUN_71000d46d0(u64 param_1, u32 param_2)
{
    u64 uVar1;
    s64 lVar2;

    uVar1 = FUN_71000b1b90();
    lVar2 = FUN_7100130810(0x18, uVar1);
    if (lVar2 != 0) {
        FUN_71000d4b40(lVar2, param_2);
    }
    return lVar2;
}

// 0x71000d4aa0
s64 FUN_71000d4aa0(u64 param_1, u32 param_2)
{
    u64 uVar1;
    s64 lVar2;

    uVar1 = FUN_71000b1b90();
    lVar2 = FUN_7100130810(0x18, uVar1);
    if (lVar2 != 0) {
        FUN_71000d4ee0(lVar2, param_2);
    }
    return lVar2;
}

// 0x71000d5ea0
void FUN_71000d5ea0(s64 *param_1)
{
    FUN_7100187f50();
    *param_1 = (s64)(PTR_DAT_71052a4220 + 0x10);
}

// FUN_71000500a0 — TODO: decompile

// 0x71000e8240
u32 FUN_71000e8240(u64 param_1, u64 param_2)
{
    u8 *puVar1;
    u32 uVar2;

    puVar1 = PTR_DAT_71052a3d88;
    FUN_71000c4d90(*(u64 *)PTR_DAT_71052a3d88);
    uVar2 = FUN_7100251c80(param_2);
    thunk_FUN_7100251e90(*(u64 *)puVar1);
    return uVar2;
}
