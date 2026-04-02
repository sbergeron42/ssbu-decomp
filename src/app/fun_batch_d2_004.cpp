#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7103 address range, batch d2-004
// Pool-d worker: auto-generated from Ghidra decompilation

// ---- External declarations -----------------------------------------------

extern "C" int  __cxa_guard_acquire(u64 *);
extern "C" void __cxa_guard_release(u64 *);

extern void FUN_71003a4ca0(u32 *, const char *, s32);

// External data
extern u64 PTR_PTR_710529c400[];
extern u8 DAT_710532e9a0[];
extern u8 DAT_710532e9a8[];
extern u8 PTR_FUN_71051ac5d0[];

// ---- Functions ---------------------------------------------------------------

// 0x710339d440 — controller icon name → FNV-1a hash40 writer (640 bytes)
void FUN_710339d440(u32 *param_1, u32 param_2)
{
    u32 uVar1;
    u8 *pbVar2;
    u32 uVar3;

    uVar1 = 0x811c9dc5;
    switch (param_2) {
    case 1:
        param_1[0] = 0; param_1[1] = 0x13;
        param_1[2] = 0x746e6f63; param_1[3] = 0x6c6c6f72;
        param_1[4] = 0x685f7265; param_1[5] = 0x68646e61;
        uVar3 = 99; param_1[6] = 0x646c65;
        pbVar2 = (u8 *)((s64)param_1 + 9);
        do { uVar1 = uVar1 * 0x89 ^ uVar3; uVar3 = (u32)*pbVar2; pbVar2++; } while (uVar3 != 0);
        break;
    case 2:
        param_1[0] = 0; param_1[1] = 0x13;
        param_1[2] = 0x746e6f63; param_1[3] = 0x6c6c6f72;
        param_1[4] = 0x6a5f7265; param_1[5] = 0x645f796f;
        uVar3 = 99; param_1[6] = 0x6c6175;
        pbVar2 = (u8 *)((s64)param_1 + 9);
        do { uVar1 = uVar1 * 0x89 ^ uVar3; uVar3 = (u32)*pbVar2; pbVar2++; } while (uVar3 != 0);
        break;
    case 3:
        *(u8 *)(param_1 + 6) = 0;
        param_1[4] = 0x6a5f7265; param_1[5] = 0x6c5f796f;
        param_1[0] = 0; param_1[1] = 0x10;
        param_1[2] = 0x746e6f63; param_1[3] = 0x6c6c6f72;
        uVar3 = 99;
        pbVar2 = (u8 *)((s64)param_1 + 9);
        do { uVar1 = uVar1 * 0x89 ^ uVar3; uVar3 = (u32)*pbVar2; pbVar2++; } while (uVar3 != 0);
        break;
    case 4:
        *(u8 *)(param_1 + 6) = 0;
        param_1[4] = 0x6a5f7265; param_1[5] = 0x725f796f;
        param_1[0] = 0; param_1[1] = 0x10;
        param_1[2] = 0x746e6f63; param_1[3] = 0x6c6c6f72;
        uVar3 = 99;
        pbVar2 = (u8 *)((s64)param_1 + 9);
        do { uVar1 = uVar1 * 0x89 ^ uVar3; uVar3 = (u32)*pbVar2; pbVar2++; } while (uVar3 != 0);
        break;
    case 5:
        *(u8 *)((s64)param_1 + 0x16) = 0;
        param_1[0] = 0; param_1[1] = 0xe;
        param_1[2] = 0x746e6f63; param_1[3] = 0x6c6c6f72;
        *(u16 *)(param_1 + 5) = 0x6f72;
        uVar3 = 99; param_1[4] = 0x705f7265;
        pbVar2 = (u8 *)((s64)param_1 + 9);
        do { uVar1 = uVar1 * 0x89 ^ uVar3; uVar3 = (u32)*pbVar2; pbVar2++; } while (uVar3 != 0);
        break;
    case 6:
        param_1[4] = 0x675f7265;
        param_1[0] = 0; param_1[1] = 0xd;
        param_1[2] = 0x746e6f63; param_1[3] = 0x6c6c6f72;
        uVar3 = 99; *(u16 *)(param_1 + 5) = 99;
        pbVar2 = (u8 *)((s64)param_1 + 9);
        do { uVar1 = uVar1 * 0x89 ^ uVar3; uVar3 = (u32)*pbVar2; pbVar2++; } while (uVar3 != 0);
        break;
    default:
        *(u8 *)((s64)param_1 + 0x16) = 0;
        param_1[0] = 0; param_1[1] = 0xe;
        param_1[2] = 0x746e6f63; param_1[3] = 0x6c6c6f72;
        *(u16 *)(param_1 + 5) = 0x6666;
        uVar3 = 99; param_1[4] = 0x6f5f7265;
        pbVar2 = (u8 *)((s64)param_1 + 9);
        do { uVar1 = uVar1 * 0x89 ^ uVar3; uVar3 = (u32)*pbVar2; pbVar2++; } while (uVar3 != 0);
    }
    *param_1 = uVar1;
    return;
}

// 0x710339d6c0 — player/team color index → FNV-1a hash40 writer (368 bytes)
void FUN_710339d6c0(u32 *param_1, s16 param_2)
{
    s32 iVar1;
    u32 uVar2;
    const char *pcVar3;
    u8 *pbVar4;
    u32 uVar5;

    switch (param_2) {
    case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8:
        iVar1 = (s32)param_2;
        pcVar3 = "player_color_%dp";
        goto LAB_710339d710;
    case 9:
        uVar2 = 0x811c9dc5;
        param_1[0] = 0; param_1[1] = 0xf;
        param_1[2] = 0x79616c70; param_1[3] = 0x635f7265;
        param_1[4] = 0x726f6c6f; param_1[5] = 0x70635f;
        uVar5 = 0x70;
        pbVar4 = (u8 *)((s64)param_1 + 9);
        do { uVar2 = uVar2 * 0x89 ^ uVar5; uVar5 = (u32)*pbVar4; pbVar4++; } while (uVar5 != 0);
        break;
    case 10:
        uVar2 = 0x811c9dc5;
        param_1[0] = 0; param_1[1] = 0xf;
        param_1[2] = 0x79616c70; param_1[3] = 0x635f7265;
        param_1[4] = 0x726f6c6f; param_1[5] = 0x70665f;
        uVar5 = 0x70;
        pbVar4 = (u8 *)((s64)param_1 + 9);
        do { uVar2 = uVar2 * 0x89 ^ uVar5; uVar5 = (u32)*pbVar4; pbVar4++; } while (uVar5 != 0);
        break;
    case 0xb: case 0xc: case 0xd: case 0xe:
        iVar1 = param_2 + -10;
        goto LAB_710339d708;
    case 0xf: case 0x10: case 0x11: case 0x12:
        iVar1 = param_2 + -0xe;
LAB_710339d708:
        pcVar3 = "team_color_%d";
LAB_710339d710:
        FUN_71003a4ca0(param_1, pcVar3, iVar1);
        return;
    default:
        *(u8 *)(param_1 + 6) = 0;
        param_1[0] = 0; param_1[1] = 0x10;
        param_1[2] = 0x79616c70; param_1[3] = 0x635f7265;
        uVar2 = 0x811c9dc5;
        param_1[4] = 0x726f6c6f; param_1[5] = 0x66666f5f;
        uVar5 = 0x70;
        pbVar4 = (u8 *)((s64)param_1 + 9);
        do { uVar2 = uVar2 * 0x89 ^ uVar5; uVar5 = (u32)*pbVar4; pbVar4++; } while (uVar5 != 0);
    }
    *param_1 = uVar2;
    return;
}

// 0x71033be790 — lookup fighter action-info pointer by index, or return static singleton (816 bytes)
u64 *FUN_71033be790(u32 param_1)
{
    s32 iVar1;

    if (param_1 < 0x267) {
        return (u64 *)PTR_PTR_710529c400[(s32)param_1];
    }
    if (((*(u8 *)DAT_710532e9a0 & 1) == 0) &&
        (iVar1 = __cxa_guard_acquire((u64 *)DAT_710532e9a0), iVar1 != 0)) {
        *(u8 **)DAT_710532e9a8 = PTR_FUN_71051ac5d0;
        __cxa_guard_release((u64 *)DAT_710532e9a0);
    }
    return (u64 *)DAT_710532e9a8;
}

// 0x7103441ae0 — set flag byte then vtable call at +0x10 (816 bytes)
void FUN_7103441ae0(u64 param_1, u64 param_2, s64 *param_3)
{
    u64 local_20;
    u64 uStack_18;

    *(u8 *)(param_3 + 0x10) = 1;
    local_20 = 0;
    uStack_18 = 0;
    (*(void (*)(s64 *, u64 *))(*param_3 + 0x10))(param_3, &local_20);
    return;
}

// 0x71034d0c20 — vtable call at +0x10 on param_3 (416 bytes)
void FUN_71034d0c20(u64 param_1, u64 param_2, s64 *param_3)
{
    u64 local_20;
    u64 uStack_18;

    local_20 = 0;
    uStack_18 = 0;
    (*(void (*)(s64 *, u64 *))(*param_3 + 0x10))(param_3, &local_20);
    return;
}
