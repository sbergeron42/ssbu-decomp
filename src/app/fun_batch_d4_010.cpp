#include "types.h"

// MEDIUM-tier FUN_* functions — mixed 0x7100 ranges, batch d4-010
// Pool-d worker: auto-generated from Ghidra decompilation
// Includes: DLL ops, searches, Unicode check, popcount, bit-ops, struct inits

// ---- External declarations -----------------------------------------------

// FUN_710012b490 helpers
extern "C" void FUN_71000b40e0(s64);
extern "C" void FUN_71000b4160(s64);

// FUN_71000b3c70 / FUN_71000b3d10 globals
extern u64 DAT_7104f49388;
extern u64 DAT_7104f49390;
extern u64 DAT_7104f49428;
extern u64 DAT_7104f49430;

// ---- Functions ---------------------------------------------------------------

// 0x710007a9d0 — call function pointer param_2 with two addr args, then write sentinel
void FUN_710007a9d0(s64 param_1, void (*param_2)(s64, s64))
{
    (*param_2)(param_1 + 0x408, param_1 + 0x390);
    *(u64 *)(param_1 + 0x408) = 0xffffffffffffffff;
}

// 0x710007c310 — scan variable-stride entry list for matching int, return data ptr
s32 *FUN_710007c310(s64 param_1, s32 param_2)
{
    u32 uVar1;
    s32 *piVar2;

    if (*(u16 *)(param_1 + 0x10) != 0) {
        uVar1 = 0;
        piVar2 = (s32 *)(param_1 + (u64)*(u16 *)(param_1 + 6));
        do {
            if (*piVar2 == param_2) {
                return piVar2 + 2;
            }
            uVar1 = uVar1 + 1;
            piVar2 = (s32 *)((s64)piVar2 + (u64)(u32)piVar2[1]);
        } while (uVar1 < *(u16 *)(param_1 + 0x10));
    }
    return (s32 *)0x0;
}

// 0x71000837a0 — return 0 for Unicode non-visible/format codepoints, else 1
u64 FUN_71000837a0(u32 param_1)
{
    if ((param_1 & 0xffffff00) == 0x2000) {
        switch(param_1) {
        case 0x200b:
        case 0x200e:
        case 0x200f:
        case 0x202a:
        case 0x202b:
        case 0x202c:
        case 0x202d:
        case 0x202e:
        case 0x2060:
            return 0;
        }
        if (param_1 - 0x2066 < 4) {
            return 0;
        }
    }
    return 1;
}

// 0x710008a130 — doubly-linked list node remove: unlink param_2 from its list
void FUN_710008a130(s64 param_1, s8 *param_2)
{
    s64 lVar1;
    s64 lVar2;

    if (*param_2 == '\0') {
        lVar2 = *(s64 *)(param_2 + 0x88);
        if ((lVar2 != 0) && (*(s64 *)(param_2 + 0x80) != 0)) {
            *(s64 *)(lVar2 + 0x80) = *(s64 *)(param_2 + 0x80);
            *(u64 *)(*(s64 *)(param_2 + 0x80) + 0x88) = *(u64 *)(param_2 + 0x88);
            return;
        }
        if (*(s8 **)(param_1 + 0x150) == param_2) {
            *(u64 *)(param_1 + 0x150) = *(u64 *)(param_2 + 0x80);
            lVar2 = *(s64 *)(param_2 + 0x80);
            if (lVar2 == 0) {
                *(u64 *)(param_1 + 0x158) = 0;
                return;
            }
            goto LAB_710008a204;
        }
        if (*(s8 **)(param_1 + 0x158) != param_2) {
            return;
        }
        *(s64 *)(param_1 + 0x158) = lVar2;
        lVar2 = *(s64 *)(param_2 + 0x88);
        if (lVar2 == 0) {
            *(u64 *)(param_1 + 0x150) = 0;
            return;
        }
    }
    else {
        lVar2 = *(s64 *)(param_2 + 0x88);
        if ((lVar2 != 0) && (*(s64 *)(param_2 + 0x80) != 0)) {
            *(s64 *)(lVar2 + 0x80) = *(s64 *)(param_2 + 0x80);
            *(u64 *)(*(s64 *)(param_2 + 0x80) + 0x88) = *(u64 *)(param_2 + 0x88);
            return;
        }
        lVar1 = *(s64 *)(param_2 + 0x548) + (s64)*(s32 *)(param_2 + 0x20) * 8;
        if (*(s8 **)(lVar1 + 0x440) == param_2) {
            *(u64 *)(lVar1 + 0x440) = *(u64 *)(param_2 + 0x80);
            lVar2 = *(s64 *)(param_2 + 0x80);
            if (lVar2 == 0) {
                *(u64 *)(lVar1 + 0x4c0) = 0;
                return;
            }
LAB_710008a204:
            *(u64 *)(lVar2 + 0x88) = *(u64 *)(param_2 + 0x88);
            return;
        }
        if (*(s8 **)(lVar1 + 0x4c0) != param_2) {
            return;
        }
        *(s64 *)(lVar1 + 0x4c0) = lVar2;
        lVar2 = *(s64 *)(param_2 + 0x88);
        if (lVar2 == 0) {
            *(u64 *)(lVar1 + 0x440) = 0;
            return;
        }
    }
    *(u64 *)(lVar2 + 0x80) = *(u64 *)(param_2 + 0x80);
}

// 0x710008a3b0 — walk singly-linked list at param_1+0x150, skip param_2 entries
void FUN_710008a3b0(s64 param_1, s32 param_2)
{
    s64 lVar1;

    lVar1 = *(s64 *)(param_1 + 0x150);
    if ((param_2 != 0) && (lVar1 != 0)) {
        param_2 = param_2 + -1;
        do {
            lVar1 = *(s64 *)(lVar1 + 0x80);
            if (param_2 == 0) {
                return;
            }
            param_2 = param_2 + -1;
        } while (lVar1 != 0);
    }
}

// 0x710008a3e0 — return *param_1 if field[0x2c] matches param_1[1], else 0
s64 FUN_710008a3e0(s64 *param_1)
{
    s64 lVar1;

    lVar1 = *param_1;
    if (lVar1 != 0) {
        if ((s32)param_1[1] != *(s32 *)(lVar1 + 0x2c)) {
            lVar1 = 0;
        }
        return lVar1;
    }
    return 0;
}

// 0x7100112c40 — copy 7 bytes from param_2+8..+0xf into param_1+0x260..+0x267
void FUN_7100112c40(s64 param_1, s64 param_2)
{
    *(u16 *)(param_1 + 0x260) = *(u16 *)(param_2 + 8);
    *(u8 *)(param_1 + 0x262) = *(u8 *)(param_2 + 10);
    *(u8 *)(param_1 + 0x263) = *(u8 *)(param_2 + 0xb);
    *(u8 *)(param_1 + 0x264) = *(u8 *)(param_2 + 0xc);
    *(u8 *)(param_1 + 0x265) = *(u8 *)(param_2 + 0xd);
    *(u8 *)(param_1 + 0x266) = *(u8 *)(param_2 + 0xe);
    *(u8 *)(param_1 + 0x267) = *(u8 *)(param_2 + 0xf);
}

// 0x71001158e0 — if param_2 < 2: write bit0(param_3) at +0x14, param_2 at +0x10, set flag
void FUN_71001158e0(s64 param_1, u32 param_2, u8 param_3)
{
    if (param_2 < 2) {
        *(u8 *)(param_1 + 0x14) = param_3 & 1;
        *(u32 *)(param_1 + 0x10) = param_2;
        *(u32 *)(param_1 + 0x628) = *(u32 *)(param_1 + 0x628) | 0x2000;
    }
}

// 0x710011be80 — return pointer to array entry param_2 at base param_1+0x11e8, or null if > 1
u8 *FUN_710011be80(s64 param_1, u8 param_2)
{
    u8 *puVar1;

    puVar1 = (u8 *)(param_1 + 0x11e8) + (u64)param_2 * 0x268;
    if (1 < param_2) {
        puVar1 = (u8 *)0x0;
    }
    return puVar1;
}

// 0x710012b490 — validate param_2 ∈ {1,2}, check field, write and trigger callback
u64 FUN_710012b490(s64 param_1, s8 param_2)
{
    if (1 < (u8)(param_2 - 1U)) {
        return 0;
    }
    if (*(s32 *)(param_1 + 0xd88) == 1) {
        return 0;
    }
    *(u8 *)(param_1 + 0xd81) = 1;
    *(s8 *)(param_1 + 0xd80) = param_2;
    FUN_71000b40e0(param_1 + 0xd88);
    FUN_71000b4160(param_1 + 0xd88);
    return 1;
}

// 0x710012eb40 — write param_2 to u16 pair at +0x25a/+0x25c, set flag bit 1
void FUN_710012eb40(s64 param_1, u16 param_2)
{
    *(u16 *)(param_1 + 0x25a) = param_2;
    *(u16 *)(param_1 + 0x25c) = param_2;
    *(u32 *)(param_1 + 0x260) = *(u32 *)(param_1 + 0x260) | 2;
}

// 0x710012eb60 — store bit0 of param_2 at byte +0x25e, set flag bit 2
void FUN_710012eb60(s64 param_1, u8 param_2)
{
    *(u8 *)(param_1 + 0x25e) = param_2 & 1;
    *(u32 *)(param_1 + 0x260) = *(u32 *)(param_1 + 0x260) | 4;
}

// 0x710012eb80 — store bit0 of param_2 at byte +0x25f, set flag bit 3
void FUN_710012eb80(s64 param_1, u8 param_2)
{
    *(u8 *)(param_1 + 0x25f) = param_2 & 1;
    *(u32 *)(param_1 + 0x260) = *(u32 *)(param_1 + 0x260) | 8;
}

// 0x7100130aa0 — doubly-linked list: insert param_2 before head at param_1+8
void FUN_7100130aa0(s64 param_1, s64 *param_2)
{
    u64 *puVar1;

    puVar1 = *(u64 **)(param_1 + 8);
    *(s64 **)(param_1 + 8) = param_2;
    *param_2 = param_1;
    param_2[1] = (s64)puVar1;
    if (puVar1 != (u64 *)0x0) {
        *puVar1 = (u64)param_2;
    }
}

// 0x7100130ac0 — doubly-linked list: insert param_2 after head at *param_1
void FUN_7100130ac0(s64 *param_1, s64 *param_2)
{
    s64 lVar1;

    lVar1 = *param_1;
    *param_1 = (s64)param_2;
    *param_2 = lVar1;
    param_2[1] = (s64)param_1;
    if (lVar1 != 0) {
        *(s64 **)(lVar1 + 8) = param_2;
    }
}

// 0x7100130b10 — doubly-linked list: clear all nodes and reset sentinel head
void FUN_7100130b10(u64 *param_1)
{
    u64 *puVar1;
    u64 *puVar2;

    puVar1 = (u64 *)param_1[1];
    while (puVar1 != param_1) {
        puVar2 = (u64 *)puVar1[1];
        *puVar1 = 0;
        puVar1[1] = 0;
        puVar1 = puVar2;
    }
    *(u32 *)(param_1 + 2) = 0;
    *param_1 = (u64)param_1;
    param_1[1] = (u64)param_1;
}

// 0x71001353c0 — init 3-field descriptor: ptr, count, value
void FUN_71001353c0(u32 *param_1, s32 param_2, s64 param_3)
{
    if ((0 < param_2) && (param_3 != 0)) {
        *(s64 *)(param_1 + 2) = param_3;
        *param_1 = 0;
        param_1[1] = param_2;
    }
}

// 0x71001354c0 — popcount (Hamming weight) of lower 32 bits via bit-parallel sum
u32 FUN_71001354c0(u64 param_1)
{
    u32 uVar1;

    uVar1 = (s32)param_1 - ((u32)(param_1 >> 1) & 0x55555555);
    uVar1 = (uVar1 >> 2 & 0x33333333) + (uVar1 & 0x33333333);
    uVar1 = uVar1 + (uVar1 >> 4) & 0xf0f0f0f;
    uVar1 = uVar1 + (uVar1 >> 8);
    return uVar1 + (uVar1 >> 0x10) & 0x3f;
}

// 0x7100135500 — find 0-based index of (param_2+1)-th set bit in param_1 via popcount
u32 FUN_7100135500(u32 param_1, s32 param_2)
{
    u32 uVar1;

    if (param_1 == 0) {
        return 0xffffffff;
    }
    param_2 = param_2 + 1;
    do {
        param_2 = param_2 + -1;
        if (param_2 < 2) {
            uVar1 = (param_1 & -param_1) - 1;
            uVar1 = uVar1 - (uVar1 >> 1 & 0x55555555);
            uVar1 = (uVar1 >> 2 & 0x33333333) + (uVar1 & 0x33333333);
            uVar1 = uVar1 + (uVar1 >> 4) & 0xf0f0f0f;
            uVar1 = uVar1 + (uVar1 >> 8);
            return uVar1 + (uVar1 >> 0x10) & 0x3f;
        }
        param_1 = param_1 - 1 & param_1;
    } while (param_1 != 0);
    return 0xffffffff;
}

// 0x710013dc90 — copy 6 bytes (2+1+1+2+1) from param_2+8..+0xe to param_1+8..+0xe
void FUN_710013dc90(s64 param_1, s64 param_2)
{
    *(u16 *)(param_1 + 8) = *(u16 *)(param_2 + 8);
    *(u8 *)(param_1 + 10) = *(u8 *)(param_2 + 10);
    *(u16 *)(param_1 + 0xc) = *(u16 *)(param_2 + 0xc);
    *(u8 *)(param_1 + 0xe) = *(u8 *)(param_2 + 0xe);
}

// 0x7100145a10 — true if field+0x140 == 1 and field+0x110 is in [2..4]
u8 FUN_7100145a10(s64 param_1)
{
    if (*(s32 *)(param_1 + 0x140) == 1) {
        return *(s32 *)(param_1 + 0x110) - 2U < 3;
    }
    return 0;
}

// 0x7100145ce0 — true if field+0x140 == 2 and field+0x110 is in [2..4]
u8 FUN_7100145ce0(s64 param_1)
{
    if (*(s32 *)(param_1 + 0x140) == 2) {
        return *(s32 *)(param_1 + 0x110) - 2U < 3;
    }
    return 0;
}

// 0x71000b3c70 — return DAT_7104f49390 / DAT_7104f49388 or 0 if denominator is zero
u64 FUN_71000b3c70(void)
{
    u64 uVar1;

    if (DAT_7104f49388 != 0) {
        uVar1 = 0;
        if ((u64)DAT_7104f49388 != 0) {
            uVar1 = DAT_7104f49390 / DAT_7104f49388;
        }
        return uVar1;
    }
    return 0;
}

// 0x71000b3d10 — return DAT_7104f49430 / DAT_7104f49428 or 0 if denominator is zero
u64 FUN_71000b3d10(void)
{
    u64 uVar1;

    if (DAT_7104f49428 != 0) {
        uVar1 = 0;
        if ((u64)DAT_7104f49428 != 0) {
            uVar1 = DAT_7104f49430 / DAT_7104f49428;
        }
        return uVar1;
    }
    return 0;
}
