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
