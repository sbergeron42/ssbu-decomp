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

// 0x7100043160 — ctor: parent init + set vtable ptr (PTR_DAT_71052a3510) (48 bytes)
void FUN_7100043160(s64 *param_1, u64 param_2, u64 param_3, u64 param_4)
{
    FUN_7100057350(param_1, 0, 0, param_2, param_4);
    *param_1 = (s64)(PTR_DAT_71052a3510 + 0x10);
}

// 0x7100043310 — ctor: parent init + set vtable ptr (PTR_DAT_71052a3530) (48 bytes)
void FUN_7100043310(s64 *param_1, u64 param_2, u64 param_3, u64 param_4)
{
    FUN_7100057350(param_1, 0, 0, param_2, param_4);
    *param_1 = (s64)(PTR_DAT_71052a3530 + 0x10);
}

// 0x7100044480 — cleanup: if ptr-field non-null, call dtor and clear two fields (32 bytes)
void FUN_7100044480(u16 *param_1)
{
    if (*(s64 *)(param_1 + 4) != 0) {
        FUN_7100048dd0();
        *(u64 *)(param_1 + 4) = 0;
        *param_1 = 0;
    }
}

// 0x7100044970 — delegate: forward to FUN_7100031e90 with computed sub-offset (32 bytes)
void FUN_7100044970(u64 param_1, s64 param_2)
{
    FUN_7100031e90(param_1, 3, 1, *(s64 *)(param_2 + 0xb8) + 0x248, 6, 0);
}

// 0x7100044c70 — setter: set flag byte, clear two fields, store param_2 at +0xc0 (32 bytes)
void FUN_7100044c70(s64 param_1, u64 param_2)
{
    *(u8 *)(param_1 + 0x18c) = 1;
    *(u64 *)(param_1 + 400) = 0;
    *(u16 *)(param_1 + 0x198) = 0;
    *(u64 *)(param_1 + 0xc0) = param_2;
}

// 0x7100044dd0 — compare-and-update: if both fields match, return 0, else update and return 1 (48 bytes)
u64 FUN_7100044dd0(s64 param_1, s64 param_2, s16 param_3)
{
    if (*(s64 *)(param_1 + 400) == param_2 && *(s16 *)(param_1 + 0x198) == param_3) {
        return 0;
    }
    *(s64 *)(param_1 + 400) = param_2;
    *(s16 *)(param_1 + 0x198) = param_3;
    return 1;
}

// 0x7100046380 — delegate: forward param_2, offset at +0x1f0, to FUN_71000325b0 (32 bytes)
void FUN_7100046380(s64 param_1, u64 param_2)
{
    FUN_71000325b0(param_2, 0, param_1 + 0x1f0, 8, 0x20);
}

// 0x7100047c70 — doubly-linked list: splice param_1 after param_2 node (48 bytes)
void FUN_7100047c70(s64 *param_1, s64 param_2)
{
    s64 *plVar1;
    s64 lVar2;

    plVar1 = (s64 *)(param_2 + 8);
    lVar2 = *plVar1;
    *plVar1 = *param_1;
    *(s64 **)(lVar2 + 8) = param_1;
    *(s64 **)(*param_1 + 8) = plVar1;
    *param_1 = lVar2;
}

// 0x710004a590 — indexed access: bounds-check count, return element[count-1] (48 bytes)
u64 FUN_710004a590(s64 *param_1)
{
    s32 iVar1;

    iVar1 = (s32)param_1[1];
    if (iVar1 < 1 || *(s32 *)PTR_DAT_71052a3648 < iVar1) {
        return 0;
    }
    return *(u64 *)(*param_1 + (s64)(iVar1 + -1) * 8);
}

// 0x710004ad50 — delegate: if +0x18 ptr valid, build 40-byte ctx then forward (64 bytes)
void FUN_710004ad50(s64 param_1, u64 param_2, u32 param_3)
{
    u8 auStack_48[40];

    if (*(s64 *)(param_1 + 0x18) != 0) {
        FUN_7100059f90(auStack_48, param_2, param_1);
        FUN_7100059760(*(u64 *)(param_1 + 0x18), auStack_48, param_3 & 1);
    }
}

// 0x710004c5e0 — indexed access: return element at param_1[0][count-1-param_2] (16 bytes)
u64 FUN_710004c5e0(s64 *param_1, u32 param_2)
{
    return *(u64 *)(*param_1 + (s64)(s32)((s32)param_1[1] + ~param_2) * 8);
}

// 0x710004f50c — strcmp wrapper: compare ptr at +0x10 vs ptr at +0x18 (48 bytes)
u64 FUN_710004f50c(s64 param_1, s64 param_2)
{
    s32 iVar1;

    iVar1 = strcmp(*(const char **)(param_1 + 0x10), *(const char **)(param_2 + 0x18));
    if (iVar1 != 0) {
        return 0;
    }
    return 1;
}

// 0x710004f57c — strcmp wrapper: compare ptr at +0x10 vs ptr at +0x18 (48 bytes)
u64 FUN_710004f57c(s64 param_1, s64 param_2)
{
    s32 iVar1;

    iVar1 = strcmp(*(const char **)(param_1 + 0x10), *(const char **)(param_2 + 0x18));
    if (iVar1 != 0) {
        return 0;
    }
    return 1;
}

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
