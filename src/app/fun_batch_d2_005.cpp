#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7103 address range, batch d2-005
// Pool-d worker: auto-generated from Ghidra decompilation

// ---- External declarations -----------------------------------------------

extern void FUN_710356bb20(void);
extern void FUN_710392e590(void *);

namespace nu {
    extern void VirtualFreeHook(void *);
}

// External data
extern u8 PTR_VirtualFreeHook_71052a7a70[];
extern u8 PTR_FUN_710522ee80[];

// ---- Functions ---------------------------------------------------------------

// 0x7103398410 — src_appeal_* type index → FNV-1a hash40 writer (1664 bytes)
void FUN_7103398410(u32 *param_1, u32 param_2)
{
    u32 uVar1;
    u8 *pbVar2;
    u32 uVar3;

    *(u8 *)(param_1 + 2) = 0;
    param_1[0] = 0;
    param_1[1] = 0;
    switch (param_2) {
    case 1:
        param_1[2] = 0x5f726373;
        param_1[3] = 0x65707061;
        param_1[4] = 0x665f6c61;
        uVar1 = 0x811c9dc5;
        *(u8 *)((s64)param_1 + 0x16) = 0;
        *(u16 *)(param_1 + 5) = 0x786f;
        uVar3 = 0x73;
        param_1[1] = 0xe;
        pbVar2 = (u8 *)((s64)param_1 + 9);
        do { uVar1 = uVar1 * 0x89 ^ uVar3; uVar3 = (u32)*pbVar2; pbVar2++; } while (uVar3 != 0);
        break;
    case 2:
        *(u8 *)(param_1 + 6) = 0;
        uVar1 = 0x811c9dc5;
        param_1[2] = 0x5f726373;
        param_1[3] = 0x65707061;
        param_1[4] = 0x705f6c61;
        param_1[5] = 0x79707065;
        uVar3 = 0x73;
        param_1[1] = 0x10;
        pbVar2 = (u8 *)((s64)param_1 + 9);
        do { uVar1 = uVar1 * 0x89 ^ uVar3; uVar3 = (u32)*pbVar2; pbVar2++; } while (uVar3 != 0);
        break;
    case 3:
        uVar1 = 0x811c9dc5;
        param_1[2] = 0x5f726373;
        param_1[3] = 0x65707061;
        param_1[4] = 0x735f6c61;
        param_1[5] = 0x7070696c;
        *(u16 *)(param_1 + 6) = 0x79;
        param_1[1] = 0x11;
        uVar3 = 0x73;
        pbVar2 = (u8 *)((s64)param_1 + 9);
        do { uVar1 = uVar1 * 0x89 ^ uVar3; uVar3 = (u32)*pbVar2; pbVar2++; } while (uVar3 != 0);
        break;
    case 4:
        *(u8 *)(param_1 + 6) = 0;
        uVar1 = 0x811c9dc5;
        param_1[2] = 0x5f726373;
        param_1[3] = 0x65707061;
        param_1[4] = 0x665f6c61;
        param_1[5] = 0x6f636c61;
        uVar3 = 0x73;
        param_1[1] = 0x10;
        pbVar2 = (u8 *)((s64)param_1 + 9);
        do { uVar1 = uVar1 * 0x89 ^ uVar3; uVar3 = (u32)*pbVar2; pbVar2++; } while (uVar3 != 0);
        break;
    case 5:
        *(u8 *)((s64)param_1 + 0x1a) = 0;
        param_1[2] = 0x5f726373;
        param_1[3] = 0x65707061;
        param_1[4] = 0x6b5f6c61;
        param_1[5] = 0x74737972;
        uVar1 = 0x811c9dc5;
        *(u16 *)(param_1 + 6) = 0x6c61;
        param_1[1] = 0x12;
        uVar3 = 0x73;
        pbVar2 = (u8 *)((s64)param_1 + 9);
        do { uVar1 = uVar1 * 0x89 ^ uVar3; uVar3 = (u32)*pbVar2; pbVar2++; } while (uVar3 != 0);
        break;
    case 6:
        uVar1 = 0x811c9dc5;
        param_1[2] = 0x5f726373;
        param_1[3] = 0x65707061;
        param_1[4] = 0x775f6c61;
        param_1[5] = 0x666c6f;
        param_1[1] = 0xf;
        uVar3 = 0x73;
        pbVar2 = (u8 *)((s64)param_1 + 9);
        do { uVar1 = uVar1 * 0x89 ^ uVar3; uVar3 = (u32)*pbVar2; pbVar2++; } while (uVar3 != 0);
        break;
    case 7:
        *(u8 *)((s64)param_1 + 0x1a) = 0;
        param_1[2] = 0x5f726373;
        param_1[3] = 0x65707061;
        param_1[4] = 0x705f6c61;
        param_1[5] = 0x68746e61;
        uVar1 = 0x811c9dc5;
        *(u16 *)(param_1 + 6) = 0x7265;
        param_1[1] = 0x12;
        uVar3 = 0x73;
        pbVar2 = (u8 *)((s64)param_1 + 9);
        do { uVar1 = uVar1 * 0x89 ^ uVar3; uVar3 = (u32)*pbVar2; pbVar2++; } while (uVar3 != 0);
        break;
    default:
        *(u8 *)(param_1 + 2) = 0;
        param_1[0] = 0;
        param_1[1] = 0;
        return;
    case 9:
        uVar1 = 0x811c9dc5;
        param_1[2] = 0x5f726373;
        param_1[3] = 0x65707061;
        param_1[4] = 0x6c5f6c61;
        param_1[5] = 0x6e6f65;
        param_1[1] = 0xf;
        uVar3 = 0x73;
        pbVar2 = (u8 *)((s64)param_1 + 9);
        do { uVar1 = uVar1 * 0x89 ^ uVar3; uVar3 = (u32)*pbVar2; pbVar2++; } while (uVar3 != 0);
    }
    *param_1 = uVar1;
    return;
}

// 0x71035212e0 — check flag via vtable +0x88, conditional vtable call at +0x10 (80 bytes)
void FUN_71035212e0(s64 *param_1, s64 param_2)
{
    u64 uVar1;
    uVar1 = (**(u64 (**)())(*(*(s64 **)(param_2 + 0x90)) + 0x88))();
    if ((uVar1 & 1) != 0) {
        return;
    }
    (*(void (*)(s64 *, s64))(*param_1 + 0x10))(param_1, param_2);
    return;
}

// 0x710354d0d0 — vtable call at +0x418 test, then +0x450, then +0x28 (96 bytes)
void FUN_710354d0d0(s64 param_1)
{
    s64 lVar1;
    u64 uVar2;
    s64 lVar3;

    lVar1 = *(s64 *)(param_1 + 0x18);
    lVar3 = **(s64 **)(param_1 + 0x20);
    uVar2 = (**(u64 (**)())(*(*(s64 **)(lVar1 + 0x10)) + 0x418))();
    if ((uVar2 & 1) == 0) {
        return;
    }
    (*(void (*)(s64 *, u32))(*(*(s64 **)(lVar1 + 0x10)) + 0x450))(*(s64 **)(lVar1 + 0x10), *(u32 *)(lVar3 + 100));
    (**(void (**)())(*(*(s64 **)(lVar1 + 0x10)) + 0x28))();
    return;
}

// 0x71035517b0 — set vtable ptr, conditionally call slot +8 (160 bytes)
void FUN_71035517b0(u64 *param_1)
{
    *param_1 = (u64)PTR_FUN_710522ee80;
    if (((s64 *)param_1[2] != nullptr) &&
        (*(s64 *)param_1[2] == (s64)param_1[3]) &&
        ((s64 *)param_1[1] != nullptr)) {
        (**(void (**)())(*(s64 *)param_1[1] + 8))();
        return;
    }
    return;
}

// 0x7103566d40 — collision slot struct initialization (928 bytes)
void FUN_7103566d40(u32 param_1, u32 param_2, u32 param_3, u32 param_4,
                    u32 param_5, u32 param_6, s64 param_7, u32 param_8,
                    u32 *param_9, u32 *param_10, u32 param_11)
{
    u32 uVar1, uVar2, uVar3, uVar4, uVar5, uVar6, uVar7, uVar8;
    u64 uVar9;
    u32 *puVar10;

    if (param_8 >> 0x19 < 5) {
        uVar9 = (u64)(param_8 >> 0x18);
        puVar10 = (u32 *)(param_7 + (s64)uVar9 * 0x1b0);
        if ((puVar10 != nullptr) && (*puVar10 == param_8) &&
            (*(s32 *)(param_7 + (s64)uVar9 * 0x1b0 + 0x90) == 0)) {
            param_7 = param_7 + (s64)uVar9 * 0x1b0;
            uVar1 = *param_9;
            uVar5 = param_9[1];
            uVar2 = param_9[2];
            uVar6 = param_9[3];
            uVar3 = *param_10;
            uVar7 = param_10[1];
            uVar4 = param_10[2];
            uVar8 = param_10[3];
            *(u32 *)(param_7 + 4) = 2;
            *(u32 *)(param_7 + 0x120) = uVar1;
            *(u64 *)(param_7 + 0xa0) = *(u64 *)(param_7 + 0x20);
            *(u64 *)(param_7 + 0xa8) = *(u64 *)(param_7 + 0x28);
            *(u32 *)(param_7 + 0x124) = uVar5;
            *(u64 *)(param_7 + 0xc0) = *(u64 *)(param_7 + 0x40);
            *(u64 *)(param_7 + 200) = *(u64 *)(param_7 + 0x48);
            *(u32 *)(param_7 + 0x128) = uVar2;
            *(u64 *)(param_7 + 0x160) = 0x3f8000003f800000ULL;
            *(u64 *)(param_7 + 0x168) = 0x3f8000003f800000ULL;
            *(u32 *)(param_7 + 300) = uVar6;
            *(u64 *)(param_7 + 0xb0) = *(u64 *)(param_7 + 0x30);
            *(u64 *)(param_7 + 0xb8) = *(u64 *)(param_7 + 0x38);
            *(u32 *)(param_7 + 0x130) = uVar3;
            *(u32 *)(param_7 + 0x134) = uVar7;
            *(u64 *)(param_7 + 0xe0) = *(u64 *)(param_7 + 0x60);
            *(u64 *)(param_7 + 0xe8) = *(u64 *)(param_7 + 0x68);
            *(u32 *)(param_7 + 0x138) = uVar4;
            *(u32 *)(param_7 + 0x13c) = uVar8;
            *(u64 *)(param_7 + 0xd0) = *(u64 *)(param_7 + 0x50);
            *(u64 *)(param_7 + 0xd8) = *(u64 *)(param_7 + 0x58);
            *(u32 *)(param_7 + 0x110) = *(u32 *)(param_7 + 0x90);
            *(u64 *)(param_7 + 0x100) = *(u64 *)(param_7 + 0x80);
            *(u64 *)(param_7 + 0x108) = *(u64 *)(param_7 + 0x88);
            *(u32 *)(param_7 + 0x140) = param_2;
            *(u32 *)(param_7 + 0x144) = param_3;
            *(u64 *)(param_7 + 0xf0) = *(u64 *)(param_7 + 0x70);
            *(u64 *)(param_7 + 0xf8) = *(u64 *)(param_7 + 0x78);
            *(u32 *)(param_7 + 0x148) = param_4;
            *(u32 *)(param_7 + 0x14c) = param_5;
            *(u32 *)(param_7 + 0x150) = param_6;
            *(u32 *)(param_7 + 0x154) = param_11;
            *(u32 *)(param_7 + 0x170) = 0;
            *(u64 *)(param_7 + 0x174) = 0;
            *(u64 *)(param_7 + 0x17c) = 0x3f8000003f800000ULL;
            *(u32 *)(param_7 + 0x184) = 0x3f800000;
            *(u32 *)(param_7 + 400) = 0;
            *(u32 *)(param_7 + 0x10) = 0;
            *(u32 *)(param_7 + 0x14) = param_1;
            return;
        }
    }
    return;
}

// 0x710356ba40 — type-dispatch: free/destroy typed value object (224 bytes)
void FUN_710356ba40(u32 param_1, u64 *param_2)
{
    u64 *puVar1;
    u64 *puVar2;
    u64 *puVar3;

    switch (param_1) {
    case 0: case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8:
    case 10: case 0xf: case 0x12:
        break;
    case 9:
        puVar1 = (u64 *)*param_2;
        if (puVar1 != nullptr) {
            param_2[1] = (u64)puVar1;
LAB_710356baec:
            if (*(u8 **)PTR_VirtualFreeHook_71052a7a70 != nullptr) {
                nu::VirtualFreeHook(puVar1);
            }
            FUN_710392e590(puVar1);
            return;
        }
        break;
    case 0xb: case 0xd: case 0xe: case 0x10: case 0x11:
        (*(void (*)(u64 *))(*(u64 *)*param_2))(param_2);
        return;
    case 0xc:
        puVar3 = (u64 *)*param_2;
        if (puVar3 != nullptr) {
            puVar2 = (u64 *)param_2[1];
            puVar1 = puVar3;
            if (puVar2 != puVar3) {
                do {
                    puVar2 = puVar2 - 4;
                    (*(void (*)(u64 *))(*(u64 *)*puVar2))(puVar2);
                } while (puVar3 != puVar2);
                puVar1 = (u64 *)*param_2;
            }
            param_2[1] = (u64)puVar3;
            goto LAB_710356baec;
        }
        break;
    default:
        FUN_710356bb20();
    }
    return;
}

// 0x7103598a60 — type-dispatch: free/destroy vector typed value (208 bytes)
void FUN_7103598a60(u32 param_1, u64 *param_2)
{
    u64 *puVar1;
    u64 *puVar2;
    u64 *puVar3;

    switch (param_1) {
    case 0: case 1: case 3: case 4: case 5: case 6:
        (*(void (*)(u64 *))(*(u64 *)*param_2))(param_2);
        return;
    case 2:
        break;
    default:
        FUN_710356bb20();
    }
    puVar3 = (u64 *)*param_2;
    if (puVar3 != nullptr) {
        puVar1 = (u64 *)param_2[1];
        puVar2 = puVar3;
        if (puVar1 != puVar3) {
            do {
                puVar1 = puVar1 - 4;
                (*(void (*)(u64 *))(*(u64 *)*puVar1))(puVar1);
            } while (puVar3 != puVar1);
            puVar2 = (u64 *)*param_2;
        }
        param_2[1] = (u64)puVar3;
        if (*(u8 **)PTR_VirtualFreeHook_71052a7a70 != nullptr) {
            nu::VirtualFreeHook(puVar2);
        }
        FUN_710392e590(puVar2);
        return;
    }
    return;
}
