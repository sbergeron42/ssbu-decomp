#include "types.h"

// MEDIUM-tier FUN_* functions — mixed 0x7100 ranges, batch d4-015
// Pool-d worker: auto-generated from Ghidra decompilation
// Includes: zero-fills, struct inits with PTR_DAT vtables, vtable dispatch, u16 bit ops

// ---- External declarations -----------------------------------------------

// PTR_DAT globals — hold runtime pointer values
extern u8 *PTR_DAT_71052a3328; // vtable base for FUN_710003aac0
extern u8 *PTR_DAT_71052a3390; // vtable base for FUN_710003bc80
extern s32 *PTR_DAT_71052a3648; // count limit for FUN_710004a590

// ---- Functions ---------------------------------------------------------------

// 0x710003a4e0 — zero-fill 9 u64 fields
void FUN_710003a4e0(u64 *param_1)
{
    param_1[7] = 0;
    param_1[8] = 0;
    *param_1 = 0;
    param_1[5] = 0;
    param_1[6] = 0;
    param_1[3] = 0;
    param_1[4] = 0;
    param_1[1] = 0;
    param_1[2] = 0;
}

// 0x710003a7d0 — zero-fill 24 u64 fields in pairs
void FUN_710003a7d0(u64 *param_1)
{
    param_1[0x16] = 0;
    param_1[0x17] = 0;
    param_1[0x14] = 0;
    param_1[0x15] = 0;
    param_1[0x12] = 0;
    param_1[0x13] = 0;
    param_1[0x10] = 0;
    param_1[0x11] = 0;
    param_1[0xe] = 0;
    param_1[0xf] = 0;
    param_1[0xc] = 0;
    param_1[0xd] = 0;
    param_1[10] = 0;
    param_1[0xb] = 0;
    param_1[8] = 0;
    param_1[9] = 0;
    param_1[6] = 0;
    param_1[7] = 0;
    param_1[4] = 0;
    param_1[5] = 0;
    param_1[2] = 0;
    param_1[3] = 0;
    *param_1 = 0;
    param_1[1] = 0;
}

// 0x710003aac0 — init s64* struct: set fields, store PTR_DAT_71052a3328+0x10 as vtable
void FUN_710003aac0(s64 *param_1, u32 param_2, u32 param_3)
{
    u8 *puVar1;

    param_1[2] = 0;
    *(u32 *)(param_1 + 3) = param_2;
    *(u32 *)((s64)param_1 + 0x1c) = 2;
    puVar1 = PTR_DAT_71052a3328;
    *(u32 *)(param_1 + 4) = param_3;
    *(u64 *)((s64)param_1 + 0x24) = 0;
    param_1[6] = 0;
    param_1[7] = 0;
    *param_1 = (s64)(puVar1 + 0x10);
    param_1[1] = 0;
}

// 0x710003ac20 — set field+0x1c to 1 or 2 based on threshold, store param_2 at +0x28
void FUN_710003ac20(s64 param_1, s32 param_2)
{
    u32 uVar1;

    uVar1 = 1;
    if (0xffff < param_2) {
        uVar1 = 2;
    }
    *(u32 *)(param_1 + 0x1c) = uVar1;
    *(s32 *)(param_1 + 0x28) = param_2;
}

// 0x710003bc80 — init s64* struct: store PTR_DAT_71052a3390+0x10 as vtable, const at index 1
void FUN_710003bc80(s64 *param_1)
{
    u8 *puVar1;

    puVar1 = PTR_DAT_71052a3390;
    param_1[2] = 0;
    param_1[3] = 0;
    *param_1 = (s64)(puVar1 + 0x10);
    param_1[1] = 0x1f00000000LL;
    *(u32 *)(param_1 + 4) = 0;
}

// 0x710003c350 — vtable dispatch: cases 0,2 call vfuncs +0xd8/+0x98; cases 4,6 return 0
u64 FUN_710003c350(s64 *param_1)
{
    switch ((s32)param_1[1]) {
    case 0:
    case 2:
        (*(void(**)(s64 *, s32))(*param_1 + 0xd8))(param_1, 1);
        (*(void(**)(s64 *))(*param_1 + 0x98))(param_1);
        break;
    case 4:
    case 6:
        return 0;
    }
    return 1;
}

// 0x710003de30 — vtable dispatch: cases 0,2,5 call vfuncs +0xd8/+0x98; cases 4,6 return 0
u64 FUN_710003de30(s64 *param_1)
{
    switch ((s32)param_1[1]) {
    case 0:
    case 2:
    case 5:
        (*(void(**)(s64 *, s32))(*param_1 + 0xd8))(param_1, 1);
        (*(void(**)(s64 *))(*param_1 + 0x98))(param_1);
        break;
    case 4:
    case 6:
        return 0;
    }
    return 1;
}

// 0x710003e030 — vtable dispatch: cases 0,2,5 call vfuncs +0xd8/+0x98; cases 4,6 return 0
u64 FUN_710003e030(s64 *param_1)
{
    switch ((s32)param_1[1]) {
    case 0:
    case 2:
    case 5:
        (*(void(**)(s64 *, s32))(*param_1 + 0xd8))(param_1, 1);
        (*(void(**)(s64 *))(*param_1 + 0x98))(param_1);
        break;
    case 4:
    case 6:
        return 0;
    }
    return 1;
}
