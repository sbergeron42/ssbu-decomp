#include "types.h"

// MEDIUM-tier FUN_* functions — mixed 0x7100 ranges, batch d4-016
// Pool-d worker: auto-generated from Ghidra decompilation
// Includes: list ops, struct inits, memcpy group, UTF-8 counter, table lookups, nn::os

// ---- External declarations -----------------------------------------------

extern s64 *PTR_DAT_71052a3bc0; // base for FUN_71000af810
extern u64 PTR_DAT_71052a3c18;  // array base for FUN_71000b1b50
extern s64 DAT_7104492890;      // index table for FUN_71000b1b50
extern u64 PTR_DAT_71052a3c10;  // u32* target for FUN_71000b1bb0
extern u8 DAT_7104492960;       // index table for FUN_71000b1bb0
extern u8 *PTR_DAT_71052a3d28;  // vtable base for FUN_71000bed20
extern u8 *PTR_DAT_71052a3ee8;  // vtable base for FUN_71000cf5c0
extern s64 *PTR_DAT_71052a4080; // global ptr for FUN_71000ee650

extern "C" void *memcpy(void *, const void *, u64);

namespace nn { namespace os {
    struct ThreadType;
    void StartThread(ThreadType *);
}}

// ---- Functions ---------------------------------------------------------------
// FUN_71000b71c0 — deduped to fun_medium_003.cpp
// 0x71000bb9f0 — check if byte is control char or 0xfd
u8 FUN_71000bb9f0(u8 param_1)
{
    return param_1 < 0x20 || param_1 == 0xfd;
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
