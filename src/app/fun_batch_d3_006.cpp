#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7100/0x7102 address range, batch d3-006
// Pool-d worker: auto-generated from Ghidra decompilation

// ---- External declarations -----------------------------------------------

// External data
extern u8  PTR_DAT_71052a5808[];
extern u8  PTR_DAT_71052a3cd0[];
extern u8  DAT_710449be2f;

// External FUN_* forward declarations
extern void FUN_7100156390();
extern u64  FUN_7100157cf0(s64);
extern void FUN_71001aea60(s64 *);
extern u64  FUN_71001f5750(s64, s64, u32, u8 *);
extern s64  FUN_71001f2ba0(u64, const char *, s32);
extern void FUN_71001f1f40();
extern void FUN_71001bee30(s64);
extern void FUN_71002121e0();
extern s32  FUN_7100228310(u64);

// ---- Functions ---------------------------------------------------------------

// 0x71001aeb00 — ctor: parent init, set vtable, init sub-object, clear fields (80 bytes)
void FUN_71001aeb00(s64 *param_1)
{
    FUN_7100156390();
    *param_1 = (s64)(PTR_DAT_71052a5808 + 0x10);
    FUN_71001aea60(param_1 + 9);
    param_1[0xc] = 0;
    *(u16 *)(param_1 + 0xd) = 0;
    *(u32 *)(param_1 + 0xb) = 2000;
    param_1[0x13] = 0;
    *(u64 *)((s64)param_1 + 0x6c) = 0;
}

// 0x71001a8b40 — flag/channel check: vtable at +0xc8, bit-pattern match (128 bytes)
bool FUN_71001a8b40(s64 *param_1, s64 param_2)
{
    u8 bVar1;
    u32 uVar2;
    u64 uVar3;

    uVar3 = (*(u64 (**)())(*(s64 *)param_1 + 0xc8))();
    if ((uVar3 & 1) != 0) {
        return true;
    }
    bVar1 = *(u8 *)(param_2 + 0x31);
    if ((bVar1 >> 1 & 1) != 0) {
        if ((bVar1 & 1) == 0) {
            return false;
        }
        uVar3 = FUN_7100157cf0(param_2);
        if (uVar3 >> 0x20 != 0) {
            return false;
        }
        if ((s32)param_1[0x22] != 0) {
            uVar2 = (u32)FUN_7100157cf0(param_2);
            return (uVar2 & (*(u32 *)(param_1 + 0x22) ^ 0xffffffffu)) != 0;
        }
        return true;
    }
    if ((bVar1 & 1) == 0) {
        return false;
    }
    uVar3 = FUN_7100157cf0(param_2);
    if (uVar3 >> 0x20 != 0) {
        return false;
    }
    return (s32)param_1[0x22] == 0;
}

// 0x710015d240 — setter: store (global * param_2) / 1000 at +0x488 (32 bytes)
void FUN_710015d240(s64 param_1, u32 param_2)
{
    *(s64 *)(param_1 + 0x488) = (s64)(*(s64 *)PTR_DAT_71052a3cd0 * (u64)param_2) / 1000;
}

// 0x71001e0670 — delegate: FUN_71001f5750 on +0x18 sub-object, copy byte out (96 bytes)
u64 FUN_71001e0670(s64 param_1, u32 param_2, u8 *param_3)
{
    u64 uVar1;

    uVar1 = FUN_71001f5750(*(s64 *)(param_1 + 0x18) + 0xf0, param_1, param_2,
                           (u8 *)(param_1 + 0x20));
    if ((uVar1 & 1) != 0) {
        if (param_3 != (u8 *)0x0) {
            *param_3 = *(u8 *)(param_1 + 0x20);
        }
        return 1;
    }
    return 0;
}

// 0x71001e5e90 — delegate: FUN_71001f2ba0 with DAT string and zero flags (48 bytes)
void FUN_71001e5e90(u64 param_1)
{
    FUN_71001f2ba0(param_1, (const char *)&DAT_710449be2f, 0);
}

// 0x71001ece20 — wrapper: call FUN_71001f1f40, return param_1 unchanged (32 bytes)
u64 FUN_71001ece20(u64 param_1)
{
    FUN_71001f1f40();
    return param_1;
}

// 0x71001f4cc0 — delegate: call FUN_71001bee30 on +0x130 sub-object, return 1 (32 bytes)
u64 FUN_71001f4cc0(s64 param_1)
{
    FUN_71001bee30(param_1 + 0x130);
    return 1;
}

// 0x71002125e0 — wrapper: call FUN_71002121e0, return 0 (32 bytes)
u64 FUN_71002125e0(void)
{
    FUN_71002121e0();
    return 0;
}

// 0x7100212d80 — wrapper: call FUN_71002121e0, return 1 (32 bytes)
u64 FUN_7100212d80(void)
{
    FUN_71002121e0();
    return 1;
}

// 0x7100213080 — vtable dispatch: call +0x10 sub-object's method at vtable[3] (64 bytes)
u64 FUN_7100213080(s64 param_1, s64 param_2, u64 param_3, u64 param_4, u64 param_5)
{
    s64 *ppObj = *(s64 **)(param_1 + 0x10);
    (*(void (**)(s64 *, s64, u64, u64, u8, u64, u64, u64))(*ppObj + 0x18))
        (ppObj, param_2, (u64)1, (u64)0, *(u8 *)(param_2 + 0x42), param_3, (u64)0, param_5);
    return 1;
}

// 0x71002134e0 — vtable dispatch: call +0x10 sub-object's method at vtable[3] (64 bytes)
u64 FUN_71002134e0(s64 param_1, s64 param_2, u64 param_3, u64 param_4, u64 param_5)
{
    s64 *ppObj = *(s64 **)(param_1 + 0x10);
    (*(void (**)(s64 *, s64, u64, u64, u8, u64, u64, u64))(*ppObj + 0x18))
        (ppObj, param_2, (u64)1, (u64)0, *(u8 *)(param_2 + 0x42), param_3, (u64)0, param_5);
    return 1;
}

// 0x71002275e0 — bool check: flag at +0x21, queue empty checks at +0x80/+0x88 (80 bytes)
bool FUN_71002275e0(s64 param_1)
{
    s32 iVar1;

    if (*(s8 *)(param_1 + 0x21) == '\0') {
        return false;
    }
    iVar1 = FUN_7100228310(*(u64 *)(param_1 + 0x80));
    if (iVar1 != 0) {
        iVar1 = FUN_7100228310(*(u64 *)(param_1 + 0x88));
        if (iVar1 != 0) {
            return *(s64 *)(param_1 + 0x78) != 0;
        }
        return true;
    }
    return true;
}

// 0x7100227700 — bit util: reverse byte order of u32 (bswap) (32 bytes)
u32 FUN_7100227700(u32 param_1)
{
    return ((param_1 & 0xff00ff00u) >> 8 | (param_1 & 0x00ff00ffu) << 8) << 0x10 |
           param_1 >> 0x18 | (param_1 >> 0x10 & 0x00ff00ffu) << 8;
}
