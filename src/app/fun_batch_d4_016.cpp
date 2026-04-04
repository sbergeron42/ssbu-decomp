#include "types.h"

// MEDIUM-tier FUN_* functions — mixed 0x7100 ranges, batch d4-016
// Pool-d worker: auto-generated from Ghidra decompilation
// Includes: list ops, struct inits, memcpy group, UTF-8 counter, table lookups, nn::os

// ---- External declarations -----------------------------------------------

#pragma GCC visibility push(hidden)
extern s64 *PTR_DAT_71052a3bc0; // base for FUN_71000af810
extern u64 PTR_DAT_71052a3c18;  // array base for FUN_71000b1b50
extern s64 DAT_7104492890;      // index table for FUN_71000b1b50
extern u64 PTR_DAT_71052a3c10;  // u32* target for FUN_71000b1bb0
extern u8 DAT_7104492960;       // index table for FUN_71000b1bb0
extern u8 *PTR_DAT_71052a3d28;  // vtable base for FUN_71000bed20
extern u8 *PTR_DAT_71052a3ee8;  // vtable base for FUN_71000cf5c0
extern s64 *PTR_DAT_71052a4080; // global ptr for FUN_71000ee650
#pragma GCC visibility pop

extern "C" void *memcpy(void *, const void *, u64);

namespace nn { namespace os {
    struct ThreadType;
    void StartThread(ThreadType *);
}}

// ---- Functions ---------------------------------------------------------------

// 0x7100078b00 — doubly-linked list splice: insert param_1+0x38 node after param_2+0x48
void FUN_7100078b00(s64 param_1, s64 param_2)
{
    s64 *plVar1;
    s64 *plVar2;
    s64 lVar3;

    plVar2 = (s64 *)(param_2 + 0x48);
    lVar3 = *plVar2;
    plVar1 = (s64 *)(param_1 + 0x38);
    *plVar2 = *plVar1;
    *(s64 **)(lVar3 + 8) = plVar1;
    *(s64 **)(*plVar1 + 8) = plVar2;
    *plVar1 = lVar3;
}

// 0x71000887d0 — cycling counter: advance slot index modulo 2 or 3 (based on flag)
u64 FUN_71000887d0(s64 param_1, s32 param_2)
{
    s32 iVar1;
    u32 uVar2;
    s32 iVar3;
    s32 iVar4;

    if (param_2 == 2) {
        if ((*(s8 *)(param_1 + 9) == '\0') && (*(s8 *)(param_1 + 10) == '\0')) {
            return 0;
        }
    }
    else if (param_2 != 1) {
        return 0;
    }
    *(u16 *)(param_1 + 9) = 0;
    iVar1 = *(s32 *)(param_1 + 0x30) + 1;
    iVar4 = 2;
    if (*(s8 *)(*(s64 *)(*(s64 *)(param_1 + 0x78) + 0x20) + 0x36) != '\0') {
        iVar4 = 3;
    }
    iVar3 = 0;
    if (iVar4 != 0) {
        iVar3 = iVar1 / iVar4;
    }
    uVar2 = iVar1 - iVar3 * iVar4;
    *(u32 *)(param_1 + 0x30) = uVar2;
    *(u64 *)(param_1 + 0xc0) = param_1 + (u64)uVar2 * 0x58 + 200;
    return 1;
}

// 0x710008d670 — bulk memcpy: copy up to 11 channel buffers from param_2 to puVar1 array
void FUN_710008d670(u64 param_1, s64 param_2)
{
    u64 n;
    u64 *puVar1;

    if (*(s8 *)(*(s64 *)(param_2 + 0xa0) + 0x752) == '\0') {
        puVar1 = *(u64 **)(param_2 + 0xc0);
        n = (u64)((s64)*(s32 *)(param_2 + 0x28) << 4);
        memcpy((void *)puVar1[0], *(void **)(param_2 + 0x1d0), n);
        memcpy((void *)puVar1[1], *(void **)(param_2 + 0x1d8), n);
        memcpy((void *)puVar1[2], *(void **)(param_2 + 0x1e0), n);
        memcpy((void *)puVar1[4], *(void **)(param_2 + 0x1f0), n);
        memcpy((void *)puVar1[3], *(void **)(param_2 + 0x1e8), n);
        memcpy((void *)puVar1[5], *(void **)(param_2 + 0x1f8), n);
        if ((void *)puVar1[6] != (void *)0x0) {
            memcpy((void *)puVar1[6], *(void **)(param_2 + 0x200), n);
            memcpy((void *)puVar1[7], *(void **)(param_2 + 0x208), n);
        }
        if ((void *)puVar1[8] != (void *)0x0) {
            memcpy((void *)puVar1[8], *(void **)(param_2 + 0x210), n);
            memcpy((void *)puVar1[9], *(void **)(param_2 + 0x218), n);
            memcpy((void *)puVar1[10], *(void **)(param_2 + 0x220), n);
        }
    }
}

// 0x71000af810 — indexed lookup: PTR_DAT_71052a3bc0 base + packed byte index * 0xa8
s64 FUN_71000af810(s64 param_1)
{
    return *PTR_DAT_71052a3bc0 +
           ((u64)*(u8 *)(param_1 + 9) + (u64)*(u8 *)(param_1 + 8) * 4 +
           (u64)*(u8 *)(param_1 + 10) * 0x10) * 0xa8;
}

// 0x71000b1b50 — double-indexed lookup: table DAT_7104492890 → array at PTR_DAT_71052a3c18
u64 FUN_71000b1b50(s32 param_1)
{
    if ((u32)(param_1 - 2) < 0x19) {
        return *(u64 *)(PTR_DAT_71052a3c18 +
               *(s64 *)(&DAT_7104492890 + (s64)(s32)((u32)param_1 - 2) * 8) * 8);
    }
    return *(u64 *)(PTR_DAT_71052a3c18 + 200);
}

// 0x71000b1bb0 — write indexed u32 from DAT_7104492960 to *(u32*)PTR_DAT_71052a3c10
void FUN_71000b1bb0(s32 param_1)
{
    if ((u32)(param_1 - 2) < 0x19) {
        *(u32 *)PTR_DAT_71052a3c10 =
            *(u32 *)(&DAT_7104492960 + (s64)(s32)((u32)param_1 - 2) * 4);
        return;
    }
    *(u32 *)PTR_DAT_71052a3c10 = 0x19;
}

// 0x71000bb050 — count UTF-8 characters in string within bounds, handling multi-byte sequences
u32 FUN_71000bb050(s64 param_1)
{
    u32 uVar1;
    u32 uVar2;
    u8 bVar3;
    u32 uVar4;
    u8 *pbVar5;
    u8 *pbVar6;
    u32 uVar7;
    u32 uVar8;

    pbVar5 = *(u8 **)(param_1 + 8);
    if (pbVar5 == (u8 *)0x0) {
        return 0;
    }
    uVar2 = *(u32 *)(param_1 + 0x14);
    if (uVar2 != 0) {
        if (*(s32 *)(param_1 + 0x18) != 1) {
            uVar4 = 0;
            if (*(s32 *)(param_1 + 0x18) == 2) {
                uVar4 = uVar2 >> 1;
            }
            return uVar4;
        }
        uVar4 = 0;
        pbVar6 = pbVar5;
        while (true) {
            bVar3 = *pbVar6;
            if (bVar3 == 0) {
                return uVar4;
            }
            if ((s64)(u64)uVar2 <= (s64)pbVar6 - (s64)pbVar5) break;
            if ((s8)bVar3 < '\0') {
                uVar8 = (u32)(s8)bVar3;
                if (uVar8 + 0x3e < 0x1e) {
                    uVar7 = 2;
                }
                else if ((uVar8 & 0xfffffff0) == 0xffffffe0) {
                    uVar7 = 3;
                }
                else if ((uVar8 & 0xfffffff8) == 0xfffffff0) {
                    uVar7 = 4;
                }
                else {
                    uVar7 = 5;
                    if (((uVar8 & 0xfffffffc) != 0xfffffff8) && (uVar7 = 6, (bVar3 & 0xfe) != 0xfc)) {
                        uVar7 = 0;
                    }
                }
            }
            else {
                uVar7 = 1;
            }
            uVar8 = uVar7;
            if (uVar7 == 0) {
                uVar8 = 1;
            }
            uVar1 = uVar4;
            if (uVar7 != 0) {
                uVar1 = uVar4 + 1;
            }
            uVar4 = uVar4 + 1;
            pbVar6 = pbVar6 + uVar8;
            if (uVar7 == 0) {
                return uVar1;
            }
        }
        return uVar4;
    }
    return 0;
}

// 0x71000bed20 — init s64* struct: zero [2], store PTR_DAT_71052a3d28+0x10 as vtable
void FUN_71000bed20(s64 *param_1)
{
    u8 *puVar1;

    puVar1 = PTR_DAT_71052a3d28;
    param_1[2] = 0;
    *param_1 = (s64)(puVar1 + 0x10);
}

// 0x71000bf2f0 — validate: check magic+flag at +8/+0xc, then range-check field +0x5e8
u8 FUN_71000bf2f0(s64 param_1)
{
    if ((*(s32 *)(param_1 + 8) == 0x32ab9864) && ((*(u8 *)(param_1 + 0xc) & 0x7f) == 4)) {
        return (u32)(*(s32 *)(param_1 + 0x5e8)) - 0x20U < 0x5a1;
    }
    return 0;
}

// 0x71000c4d40 — vtable call +0x28 on *(param_1+0x50): return null on failure, 1 on success
s64 *FUN_71000c4d40(s64 param_1)
{
    s64 *plVar1;
    u64 uVar2;

    plVar1 = *(s64 **)(param_1 + 0x50);
    if (plVar1 != (s64 *)0x0) {
        uVar2 = (*(u64(**)(void))(*plVar1 + 0x28))();
        if ((uVar2 & 1) == 0) {
            return (s64 *)0x0;
        }
        plVar1 = (s64 *)0x1;
        *(u64 *)(param_1 + 0xc0) = 0;
    }
    return plVar1;
}

// 0x71000cf5c0 — init s64* struct: zero fields, store PTR_DAT_71052a3ee8+0x10 as vtable
void FUN_71000cf5c0(s64 *param_1)
{
    u8 *puVar1;

    puVar1 = PTR_DAT_71052a3ee8;
    *(u32 *)(param_1 + 1) = 0;
    *(u8 *)((s64)param_1 + 0xc) = 0;
    param_1[2] = 0;
    *param_1 = (s64)(puVar1 + 0x10);
    *(u32 *)(param_1 + 3) = 0;
}

// 0x71000e4340 — map param_1: 0→1, 1→2, else→0
s32 FUN_71000e4340(s32 param_1)
{
    s32 iVar1;

    iVar1 = (u32)(param_1 == 1) << 1;
    if (param_1 == 0) {
        iVar1 = 1;
    }
    return iVar1;
}

// 0x71000ee650 — count valid linked-list entries matching param_2 across four dispatch paths
s32 FUN_71000ee650(s64 param_1, s32 param_2)
{
    s32 iVar1;
    s64 lVar2;
    s32 *piVar3;
    s32 *piVar4;

    lVar2 = *(s64 *)(param_1 + 0x2d8);
    if (lVar2 == 0 || *PTR_DAT_71052a4080 == 0) {
        return 0;
    }
    piVar4 = (s32 *)(lVar2 + 0x10);
    if (*piVar4 != param_2) {
        if (*(s32 *)(lVar2 + 0x658) != param_2) {
            if (*(s32 *)(lVar2 + 0xca0) == param_2) {
                piVar3 = (s32 *)(lVar2 + 0xca8);
                piVar4 = *(s32 **)(lVar2 + 0xcb0);
                if (piVar4 == piVar3) {
                    return 0;
                }
            }
            else {
                if (*(s32 *)(lVar2 + 0x12e8) != param_2) {
                    return 0;
                }
                piVar3 = (s32 *)(lVar2 + 0x12f0);
                piVar4 = *(s32 **)(lVar2 + 0x12f8);
                if (piVar4 == piVar3) {
                    return 0;
                }
            }
            goto LAB_71000ee6a4;
        }
        piVar4 = (s32 *)(lVar2 + 0x658);
    }
    piVar3 = piVar4 + 2;
    piVar4 = *(s32 **)(piVar4 + 4);
    if (piVar4 == piVar3) {
        return 0;
    }
LAB_71000ee6a4:
    iVar1 = 0;
    do {
        if (((*(s64 *)(piVar4 + 4) != 0) && (*(s64 *)(piVar4 + 4) == *(s64 *)(piVar4 + 6))) &&
           (0 < *(s16 *)((s64)piVar4 + 0x22))) {
            iVar1 = iVar1 + 1;
        }
        piVar4 = *(s32 **)(piVar4 + 2);
    } while (piVar4 != piVar3);
    return iVar1;
}
