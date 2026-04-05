// Batch C - 016: MEDIUM FUN_* batch decompilation (0x7102 range)
// Functions: 7 - Misc compilable functions from broader 0x7102 range

#include "types.h"

extern "C" void FUN_7102496ed0();
extern "C" void FUN_7102a63350(u32 *, u32 *, u32 *, u32 *);
extern "C" void FUN_7102a63500(u32 *, u32 *, u32 *, u32 *, u32 *);

// 0x7102ff82b0 — vtable[0] call, return inverted low bit
u64 FUN_7102ff82b0(u64 *param_1)
{
    u32 result;
    result = (**(u32 (**)(void))(*param_1))();
    return ~result & 1;
}

// 0x71024bb34c
void FUN_71024bb34c(s64 param_1)
{
    *(u8 *)(param_1 + 100) = 1;
    FUN_7102496ed0();
}

// 0x710264fc40
void FUN_710264fc40(s64 param_1)
{
    (**(void (**)(void))(**(s64 **)(param_1 + 0x20) + 0x178))();
}

// 0x71029cceb8
u64 FUN_71029cceb8(s64 *param_1, u32 param_2)
{
    (**(void (**)(s64 *, s32, u32))(*param_1 + 0x88))(param_1, 0, param_2);
    return 1;
}

// 0x71024a7d30 — Set flag byte in array-of-structs (stride 0x40) by index
// Each struct has a state byte at +0x00 and a param byte at +0x01
// Valid state transitions: state < 8 and state is in {1, 6, 7} (bitmask 0xC2)
void FUN_71024a7d30(s64 param_1, u32 param_2, u8 param_3)
{
    switch(param_2) {
    case 0:
        if ((*(u8 *)(param_1 + 0x10) < 8) &&
           ((1 << (u64)(*(u8 *)(param_1 + 0x10) & 0x1f) & 0xc2U) != 0)) {
            *(u8 *)(param_1 + 0x10) = 5;
            *(u8 *)(param_1 + 0x11) = param_3;
            return;
        }
        break;
    case 1:
        if ((*(u8 *)(param_1 + 0x50) < 8) &&
           ((1 << (u64)(*(u8 *)(param_1 + 0x50) & 0x1f) & 0xc2U) != 0)) {
            *(u8 *)(param_1 + 0x50) = 5;
            *(u8 *)(param_1 + 0x51) = param_3;
            return;
        }
        break;
    case 2:
        if ((*(u8 *)(param_1 + 0x90) < 8) &&
           ((1 << (u64)(*(u8 *)(param_1 + 0x90) & 0x1f) & 0xc2U) != 0)) {
            *(u8 *)(param_1 + 0x90) = 5;
            *(u8 *)(param_1 + 0x91) = param_3;
            return;
        }
        break;
    case 3:
        if ((*(u8 *)(param_1 + 0xd0) < 8) &&
           ((1 << (u64)(*(u8 *)(param_1 + 0xd0) & 0x1f) & 0xc2U) != 0)) {
            *(u8 *)(param_1 + 0xd0) = 5;
            *(u8 *)(param_1 + 0xd1) = param_3;
            return;
        }
        break;
    case 4:
        if ((*(u8 *)(param_1 + 0x110) < 8) &&
           ((1 << (u64)(*(u8 *)(param_1 + 0x110) & 0x1f) & 0xc2U) != 0)) {
            *(u8 *)(param_1 + 0x110) = 5;
            *(u8 *)(param_1 + 0x111) = param_3;
            return;
        }
        break;
    case 5:
        if ((*(u8 *)(param_1 + 0x150) < 8) &&
           ((1 << (u64)(*(u8 *)(param_1 + 0x150) & 0x1f) & 0xc2U) != 0)) {
            *(u8 *)(param_1 + 0x150) = 5;
            *(u8 *)(param_1 + 0x151) = param_3;
            return;
        }
        break;
    case 6:
        if ((*(u8 *)(param_1 + 400) < 8) &&
           ((1 << (u64)(*(u8 *)(param_1 + 400) & 0x1f) & 0xc2U) != 0)) {
            *(u8 *)(param_1 + 400) = 5;
            *(u8 *)(param_1 + 0x191) = param_3;
            return;
        }
        break;
    case 7:
        if ((*(u8 *)(param_1 + 0x1d0) < 8) &&
           ((1 << (u64)(*(u8 *)(param_1 + 0x1d0) & 0x1f) & 0xc2U) != 0)) {
            *(u8 *)(param_1 + 0x1d0) = 5;
            *(u8 *)(param_1 + 0x1d1) = param_3;
            return;
        }
        break;
    case 8:
        if ((*(u8 *)(param_1 + 0x210) < 8) &&
           ((1 << (u64)(*(u8 *)(param_1 + 0x210) & 0x1f) & 0xc2U) != 0)) {
            *(u8 *)(param_1 + 0x210) = 5;
            *(u8 *)(param_1 + 0x211) = param_3;
        }
        break;
    case 0xffffffff:
        if ((*(u8 *)(param_1 + 0x10) < 8) &&
           ((1 << (u64)(*(u8 *)(param_1 + 0x10) & 0x1f) & 0xc2U) != 0)) {
            *(u8 *)(param_1 + 0x10) = 5;
            *(u8 *)(param_1 + 0x11) = param_3;
        }
        if ((*(u8 *)(param_1 + 0x50) < 8) &&
           ((1 << (u64)(*(u8 *)(param_1 + 0x50) & 0x1f) & 0xc2U) != 0)) {
            *(u8 *)(param_1 + 0x50) = 5;
            *(u8 *)(param_1 + 0x51) = param_3;
        }
        if ((*(u8 *)(param_1 + 0x90) < 8) &&
           ((1 << (u64)(*(u8 *)(param_1 + 0x90) & 0x1f) & 0xc2U) != 0)) {
            *(u8 *)(param_1 + 0x90) = 5;
            *(u8 *)(param_1 + 0x91) = param_3;
        }
        if ((*(u8 *)(param_1 + 0xd0) < 8) &&
           ((1 << (u64)(*(u8 *)(param_1 + 0xd0) & 0x1f) & 0xc2U) != 0)) {
            *(u8 *)(param_1 + 0xd0) = 5;
            *(u8 *)(param_1 + 0xd1) = param_3;
        }
        if ((*(u8 *)(param_1 + 0x110) < 8) &&
           ((1 << (u64)(*(u8 *)(param_1 + 0x110) & 0x1f) & 0xc2U) != 0)) {
            *(u8 *)(param_1 + 0x110) = 5;
            *(u8 *)(param_1 + 0x111) = param_3;
        }
        if ((*(u8 *)(param_1 + 0x150) < 8) &&
           ((1 << (u64)(*(u8 *)(param_1 + 0x150) & 0x1f) & 0xc2U) != 0)) {
            *(u8 *)(param_1 + 0x150) = 5;
            *(u8 *)(param_1 + 0x151) = param_3;
        }
        if ((*(u8 *)(param_1 + 400) < 8) &&
           ((1 << (u64)(*(u8 *)(param_1 + 400) & 0x1f) & 0xc2U) != 0)) {
            *(u8 *)(param_1 + 400) = 5;
            *(u8 *)(param_1 + 0x191) = param_3;
        }
        if ((*(u8 *)(param_1 + 0x1d0) < 8) &&
           ((1 << (u64)(*(u8 *)(param_1 + 0x1d0) & 0x1f) & 0xc2U) != 0)) {
            *(u8 *)(param_1 + 0x1d0) = 5;
            *(u8 *)(param_1 + 0x1d1) = param_3;
        }
        if ((*(u8 *)(param_1 + 0x210) < 8) &&
           ((1 << (u64)(*(u8 *)(param_1 + 0x210) & 0x1f) & 0xc2U) != 0)) {
            *(u8 *)(param_1 + 0x210) = 5;
            *(u8 *)(param_1 + 0x211) = param_3;
        }
    case 9:
        if ((*(u8 *)(param_1 + 0x250) < 8) &&
           ((1 << (u64)(*(u8 *)(param_1 + 0x250) & 0x1f) & 0xc2U) != 0)) {
            *(u8 *)(param_1 + 0x250) = 5;
            *(u8 *)(param_1 + 0x251) = param_3;
            return;
        }
    }
}

// 0x71025c6520 — Compute custom hash of "mnu_spirits_sort_XX" by sort-type index
// Writes string as u32 words at param_1[2..6], then hashes it (FNV-like: seed 0x811c9dc5, mul 0x89)
// String suffixes: 0→"_01", 1→"_00", 2→"_02", 3→"_18", 4→"_03", 5→"_04", 6→"_05", 7→"_06",
//   8→"_07", 9→"_08", 10→"_09", 11→"_10", 12→"_11", 13→"_12", 14→"_13", 15→"_14",
//   16→"_15", 17→"_16", 18→"_17", 19→"_19", 20→"_22", 21→"_24", 22→"_21"
void FUN_71025c6520(u32 *param_1, u32 param_2)
{
    u32 uVar1;
    u8 *pbVar2;
    u32 uVar3;

    switch(param_2) {
    case 1:
        uVar1 = 0x811c9dc5;
        param_1[0] = 0;
        param_1[1] = 0x13;
        param_1[2] = 0x5f756e6d;
        param_1[3] = 0x72697073;
        param_1[4] = 0x5f737469;
        param_1[5] = 0x74726f73;
        param_1[6] = 0x31305f;
        uVar3 = 0x6d;
        pbVar2 = (u8 *)((long)param_1 + 9);
        do {
            uVar1 = uVar1 * 0x89 ^ uVar3;
            uVar3 = (u32)*pbVar2;
            pbVar2 = pbVar2 + 1;
        } while (uVar3 != 0);
        *param_1 = uVar1;
        return;
    case 2:
        uVar1 = 0x811c9dc5;
        param_1[0] = 0;
        param_1[1] = 0x13;
        param_1[2] = 0x5f756e6d;
        param_1[3] = 0x72697073;
        param_1[4] = 0x5f737469;
        param_1[5] = 0x74726f73;
        param_1[6] = 0x30305f;
        uVar3 = 0x6d;
        pbVar2 = (u8 *)((long)param_1 + 9);
        do {
            uVar1 = uVar1 * 0x89 ^ uVar3;
            uVar3 = (u32)*pbVar2;
            pbVar2 = pbVar2 + 1;
        } while (uVar3 != 0);
        *param_1 = uVar1;
        return;
    case 3:
        uVar1 = 0x811c9dc5;
        param_1[0] = 0;
        param_1[1] = 0x13;
        param_1[2] = 0x5f756e6d;
        param_1[3] = 0x72697073;
        param_1[4] = 0x5f737469;
        param_1[5] = 0x74726f73;
        param_1[6] = 0x32305f;
        uVar3 = 0x6d;
        pbVar2 = (u8 *)((long)param_1 + 9);
        do {
            uVar1 = uVar1 * 0x89 ^ uVar3;
            uVar3 = (u32)*pbVar2;
            pbVar2 = pbVar2 + 1;
        } while (uVar3 != 0);
        *param_1 = uVar1;
        return;
    case 4:
        uVar1 = 0x811c9dc5;
        param_1[0] = 0;
        param_1[1] = 0x13;
        param_1[2] = 0x5f756e6d;
        param_1[3] = 0x72697073;
        param_1[4] = 0x5f737469;
        param_1[5] = 0x74726f73;
        param_1[6] = 0x38315f;
        uVar3 = 0x6d;
        pbVar2 = (u8 *)((long)param_1 + 9);
        do {
            uVar1 = uVar1 * 0x89 ^ uVar3;
            uVar3 = (u32)*pbVar2;
            pbVar2 = pbVar2 + 1;
        } while (uVar3 != 0);
        *param_1 = uVar1;
        return;
    case 5:
        uVar1 = 0x811c9dc5;
        param_1[0] = 0;
        param_1[1] = 0x13;
        param_1[2] = 0x5f756e6d;
        param_1[3] = 0x72697073;
        param_1[4] = 0x5f737469;
        param_1[5] = 0x74726f73;
        param_1[6] = 0x33305f;
        uVar3 = 0x6d;
        pbVar2 = (u8 *)((long)param_1 + 9);
        do {
            uVar1 = uVar1 * 0x89 ^ uVar3;
            uVar3 = (u32)*pbVar2;
            pbVar2 = pbVar2 + 1;
        } while (uVar3 != 0);
        *param_1 = uVar1;
        return;
    case 6:
        uVar1 = 0x811c9dc5;
        param_1[0] = 0;
        param_1[1] = 0x13;
        param_1[2] = 0x5f756e6d;
        param_1[3] = 0x72697073;
        param_1[4] = 0x5f737469;
        param_1[5] = 0x74726f73;
        param_1[6] = 0x34305f;
        uVar3 = 0x6d;
        pbVar2 = (u8 *)((long)param_1 + 9);
        do {
            uVar1 = uVar1 * 0x89 ^ uVar3;
            uVar3 = (u32)*pbVar2;
            pbVar2 = pbVar2 + 1;
        } while (uVar3 != 0);
        *param_1 = uVar1;
        return;
    case 7:
        uVar1 = 0x811c9dc5;
        param_1[0] = 0;
        param_1[1] = 0x13;
        param_1[2] = 0x5f756e6d;
        param_1[3] = 0x72697073;
        param_1[4] = 0x5f737469;
        param_1[5] = 0x74726f73;
        param_1[6] = 0x35305f;
        uVar3 = 0x6d;
        pbVar2 = (u8 *)((long)param_1 + 9);
        do {
            uVar1 = uVar1 * 0x89 ^ uVar3;
            uVar3 = (u32)*pbVar2;
            pbVar2 = pbVar2 + 1;
        } while (uVar3 != 0);
        *param_1 = uVar1;
        return;
    case 8:
        uVar1 = 0x811c9dc5;
        param_1[0] = 0;
        param_1[1] = 0x13;
        param_1[2] = 0x5f756e6d;
        param_1[3] = 0x72697073;
        param_1[4] = 0x5f737469;
        param_1[5] = 0x74726f73;
        param_1[6] = 0x36305f;
        uVar3 = 0x6d;
        pbVar2 = (u8 *)((long)param_1 + 9);
        break;
    case 9:
        uVar1 = 0x811c9dc5;
        param_1[0] = 0;
        param_1[1] = 0x13;
        param_1[2] = 0x5f756e6d;
        param_1[3] = 0x72697073;
        param_1[4] = 0x5f737469;
        param_1[5] = 0x74726f73;
        param_1[6] = 0x37305f;
        uVar3 = 0x6d;
        pbVar2 = (u8 *)((long)param_1 + 9);
        do {
            uVar1 = uVar1 * 0x89 ^ uVar3;
            uVar3 = (u32)*pbVar2;
            pbVar2 = pbVar2 + 1;
        } while (uVar3 != 0);
        *param_1 = uVar1;
        return;
    case 10:
        uVar1 = 0x811c9dc5;
        param_1[0] = 0;
        param_1[1] = 0x13;
        param_1[2] = 0x5f756e6d;
        param_1[3] = 0x72697073;
        param_1[4] = 0x5f737469;
        param_1[5] = 0x74726f73;
        param_1[6] = 0x38305f;
        uVar3 = 0x6d;
        pbVar2 = (u8 *)((long)param_1 + 9);
        do {
            uVar1 = uVar1 * 0x89 ^ uVar3;
            uVar3 = (u32)*pbVar2;
            pbVar2 = pbVar2 + 1;
        } while (uVar3 != 0);
        *param_1 = uVar1;
        return;
    case 0xb:
        uVar1 = 0x811c9dc5;
        param_1[0] = 0;
        param_1[1] = 0x13;
        param_1[2] = 0x5f756e6d;
        param_1[3] = 0x72697073;
        param_1[4] = 0x5f737469;
        param_1[5] = 0x74726f73;
        param_1[6] = 0x39305f;
        uVar3 = 0x6d;
        pbVar2 = (u8 *)((long)param_1 + 9);
        do {
            uVar1 = uVar1 * 0x89 ^ uVar3;
            uVar3 = (u32)*pbVar2;
            pbVar2 = pbVar2 + 1;
        } while (uVar3 != 0);
        *param_1 = uVar1;
        return;
    case 0xc:
        uVar1 = 0x811c9dc5;
        param_1[0] = 0;
        param_1[1] = 0x13;
        param_1[2] = 0x5f756e6d;
        param_1[3] = 0x72697073;
        param_1[4] = 0x5f737469;
        param_1[5] = 0x74726f73;
        param_1[6] = 0x30315f;
        uVar3 = 0x6d;
        pbVar2 = (u8 *)((long)param_1 + 9);
        do {
            uVar1 = uVar1 * 0x89 ^ uVar3;
            uVar3 = (u32)*pbVar2;
            pbVar2 = pbVar2 + 1;
        } while (uVar3 != 0);
        *param_1 = uVar1;
        return;
    case 0xd:
        uVar1 = 0x811c9dc5;
        param_1[0] = 0;
        param_1[1] = 0x13;
        param_1[2] = 0x5f756e6d;
        param_1[3] = 0x72697073;
        param_1[4] = 0x5f737469;
        param_1[5] = 0x74726f73;
        param_1[6] = 0x31315f;
        uVar3 = 0x6d;
        pbVar2 = (u8 *)((long)param_1 + 9);
        do {
            uVar1 = uVar1 * 0x89 ^ uVar3;
            uVar3 = (u32)*pbVar2;
            pbVar2 = pbVar2 + 1;
        } while (uVar3 != 0);
        *param_1 = uVar1;
        return;
    case 0xe:
        uVar1 = 0x811c9dc5;
        param_1[0] = 0;
        param_1[1] = 0x13;
        param_1[2] = 0x5f756e6d;
        param_1[3] = 0x72697073;
        param_1[4] = 0x5f737469;
        param_1[5] = 0x74726f73;
        param_1[6] = 0x32315f;
        uVar3 = 0x6d;
        pbVar2 = (u8 *)((long)param_1 + 9);
        do {
            uVar1 = uVar1 * 0x89 ^ uVar3;
            uVar3 = (u32)*pbVar2;
            pbVar2 = pbVar2 + 1;
        } while (uVar3 != 0);
        *param_1 = uVar1;
        return;
    case 0xf:
        uVar1 = 0x811c9dc5;
        param_1[0] = 0;
        param_1[1] = 0x13;
        param_1[2] = 0x5f756e6d;
        param_1[3] = 0x72697073;
        param_1[4] = 0x5f737469;
        param_1[5] = 0x74726f73;
        param_1[6] = 0x33315f;
        uVar3 = 0x6d;
        pbVar2 = (u8 *)((long)param_1 + 9);
        do {
            uVar1 = uVar1 * 0x89 ^ uVar3;
            uVar3 = (u32)*pbVar2;
            pbVar2 = pbVar2 + 1;
        } while (uVar3 != 0);
        *param_1 = uVar1;
        return;
    case 0x10:
        uVar1 = 0x811c9dc5;
        param_1[0] = 0;
        param_1[1] = 0x13;
        param_1[2] = 0x5f756e6d;
        param_1[3] = 0x72697073;
        param_1[4] = 0x5f737469;
        param_1[5] = 0x74726f73;
        param_1[6] = 0x34315f;
        uVar3 = 0x6d;
        pbVar2 = (u8 *)((long)param_1 + 9);
        do {
            uVar1 = uVar1 * 0x89 ^ uVar3;
            uVar3 = (u32)*pbVar2;
            pbVar2 = pbVar2 + 1;
        } while (uVar3 != 0);
        *param_1 = uVar1;
        return;
    case 0x11:
        uVar1 = 0x811c9dc5;
        param_1[0] = 0;
        param_1[1] = 0x13;
        param_1[2] = 0x5f756e6d;
        param_1[3] = 0x72697073;
        param_1[4] = 0x5f737469;
        param_1[5] = 0x74726f73;
        param_1[6] = 0x35315f;
        uVar3 = 0x6d;
        pbVar2 = (u8 *)((long)param_1 + 9);
        do {
            uVar1 = uVar1 * 0x89 ^ uVar3;
            uVar3 = (u32)*pbVar2;
            pbVar2 = pbVar2 + 1;
        } while (uVar3 != 0);
        *param_1 = uVar1;
        return;
    case 0x12:
        uVar1 = 0x811c9dc5;
        param_1[0] = 0;
        param_1[1] = 0x13;
        param_1[2] = 0x5f756e6d;
        param_1[3] = 0x72697073;
        param_1[4] = 0x5f737469;
        param_1[5] = 0x74726f73;
        param_1[6] = 0x36315f;
        uVar3 = 0x6d;
        pbVar2 = (u8 *)((long)param_1 + 9);
        do {
            uVar1 = uVar1 * 0x89 ^ uVar3;
            uVar3 = (u32)*pbVar2;
            pbVar2 = pbVar2 + 1;
        } while (uVar3 != 0);
        *param_1 = uVar1;
        return;
    case 0x13:
        uVar1 = 0x811c9dc5;
        param_1[0] = 0;
        param_1[1] = 0x13;
        param_1[2] = 0x5f756e6d;
        param_1[3] = 0x72697073;
        param_1[4] = 0x5f737469;
        param_1[5] = 0x74726f73;
        param_1[6] = 0x37315f;
        uVar3 = 0x6d;
        pbVar2 = (u8 *)((long)param_1 + 9);
        do {
            uVar1 = uVar1 * 0x89 ^ uVar3;
            uVar3 = (u32)*pbVar2;
            pbVar2 = pbVar2 + 1;
        } while (uVar3 != 0);
        *param_1 = uVar1;
        return;
    case 0x14:
        uVar1 = 0x811c9dc5;
        param_1[0] = 0;
        param_1[1] = 0x13;
        param_1[2] = 0x5f756e6d;
        param_1[3] = 0x72697073;
        param_1[4] = 0x5f737469;
        param_1[5] = 0x74726f73;
        param_1[6] = 0x39315f;
        uVar3 = 0x6d;
        pbVar2 = (u8 *)((long)param_1 + 9);
        do {
            uVar1 = uVar1 * 0x89 ^ uVar3;
            uVar3 = (u32)*pbVar2;
            pbVar2 = pbVar2 + 1;
        } while (uVar3 != 0);
        *param_1 = uVar1;
        return;
    case 0x15:
        uVar1 = 0x811c9dc5;
        param_1[0] = 0;
        param_1[1] = 0x13;
        param_1[2] = 0x5f756e6d;
        param_1[3] = 0x72697073;
        param_1[4] = 0x5f737469;
        param_1[5] = 0x74726f73;
        param_1[6] = 0x32325f;
        uVar3 = 0x6d;
        pbVar2 = (u8 *)((long)param_1 + 9);
        do {
            uVar1 = uVar1 * 0x89 ^ uVar3;
            uVar3 = (u32)*pbVar2;
            pbVar2 = pbVar2 + 1;
        } while (uVar3 != 0);
        *param_1 = uVar1;
        return;
    case 0x16:
        uVar1 = 0x811c9dc5;
        param_1[0] = 0;
        param_1[1] = 0x13;
        param_1[2] = 0x5f756e6d;
        param_1[3] = 0x72697073;
        param_1[4] = 0x5f737469;
        param_1[5] = 0x74726f73;
        param_1[6] = 0x34325f;
        uVar3 = 0x6d;
        pbVar2 = (u8 *)((long)param_1 + 9);
        do {
            uVar1 = uVar1 * 0x89 ^ uVar3;
            uVar3 = (u32)*pbVar2;
            pbVar2 = pbVar2 + 1;
        } while (uVar3 != 0);
        *param_1 = uVar1;
        return;
    case 0x17:
        uVar1 = 0x811c9dc5;
        param_1[0] = 0;
        param_1[1] = 0x13;
        param_1[2] = 0x5f756e6d;
        param_1[3] = 0x72697073;
        param_1[4] = 0x5f737469;
        param_1[5] = 0x74726f73;
        param_1[6] = 0x31325f;
        uVar3 = 0x6d;
        pbVar2 = (u8 *)((long)param_1 + 9);
        do {
            uVar1 = uVar1 * 0x89 ^ uVar3;
            uVar3 = (u32)*pbVar2;
            pbVar2 = pbVar2 + 1;
        } while (uVar3 != 0);
        *param_1 = uVar1;
        return;
    default:
        *(u8 *)(param_1 + 2) = 0;
        param_1[0] = 0;
        param_1[1] = 0;
        return;
    }
    do {
        uVar1 = uVar1 * 0x89 ^ uVar3;
        uVar3 = (u32)*pbVar2;
        pbVar2 = pbVar2 + 1;
    } while (uVar3 != 0);
    *param_1 = uVar1;
}

// 0x7102a63620 — Partial insertion sort for u32 pairs (key-value at stride 2)
// Handles small arrays (0-5 elements) with specialized swaps, then falls back
// to bounded insertion sort (max 8 swaps before bailing)
bool FUN_7102a63620(u32 *param_1, u32 *param_2)
{
    u32 *puVar1;
    u32 uVar2;
    u32 uVar3;
    u32 uVar4;
    u32 uVar5;
    s64 lVar6;
    u32 uVar7;
    s64 lVar8;
    s32 iVar9;
    u32 *puVar10;
    u32 *puVar11;
    s64 lVar12;
    u32 *puVar13;

    switch((s64)param_2 - (s64)param_1 >> 3) {
    case 0:
    case 1:
        break;
    case 2:
        if ((u32)param_1[1] <= (u32)param_2[-1]) {
            return true;
        }
LAB_7102a63680:
        uVar7 = *param_1;
        *param_1 = param_2[-2];
        param_2[-2] = uVar7;
        uVar7 = param_1[1];
        param_1[1] = param_2[-1];
        goto LAB_7102a6369c;
    case 3:
        uVar2 = param_1[3];
        uVar3 = param_1[1];
        if (uVar3 <= uVar2) {
            if (uVar2 <= (u32)param_2[-1]) {
                return true;
            }
            uVar7 = param_1[2];
            param_1[2] = param_2[-2];
            param_2[-2] = uVar7;
            uVar7 = param_1[3];
            param_1[3] = param_2[-1];
            param_2[-1] = uVar7;
            uVar2 = param_1[1];
            if (uVar2 <= (u32)param_1[3]) {
                return true;
            }
            uVar7 = *param_1;
            *param_1 = param_1[2];
            param_1[1] = param_1[3];
            param_1[2] = uVar7;
            param_1[3] = uVar2;
            return true;
        }
        if ((u32)param_2[-1] < uVar2) goto LAB_7102a63680;
        uVar7 = *param_1;
        *param_1 = param_1[2];
        param_1[1] = uVar2;
        param_1[2] = uVar7;
        param_1[3] = uVar3;
        if (uVar3 <= (u32)param_2[-1]) {
            return true;
        }
        param_1[2] = param_2[-2];
        param_2[-2] = uVar7;
        uVar7 = param_1[3];
        param_1[3] = param_2[-1];
LAB_7102a6369c:
        param_2[-1] = uVar7;
        break;
    case 4:
        FUN_7102a63350(param_1, param_1 + 2, param_1 + 4, param_2 + -2);
        break;
    case 5:
        FUN_7102a63500(param_1, param_1 + 2, param_1 + 4, param_1 + 6, param_2 + -2);
        break;
    default:
        uVar5 = param_1[1];
        uVar2 = param_1[3];
        uVar3 = param_1[5];
        if (uVar2 < uVar5) {
            if (uVar3 < uVar2) {
                uVar7 = *param_1;
                *param_1 = param_1[4];
                param_1[1] = uVar3;
                param_1[4] = uVar7;
            }
            else {
                uVar7 = *param_1;
                *param_1 = param_1[2];
                param_1[1] = uVar2;
                param_1[2] = uVar7;
                param_1[3] = uVar5;
                if (uVar5 <= uVar3) goto LAB_7102a637e8;
                uVar4 = param_1[4];
                param_1[3] = uVar3;
                param_1[4] = uVar7;
                param_1[2] = uVar4;
            }
            param_1[5] = uVar5;
        }
        else if (uVar3 < uVar2) {
            uVar7 = param_1[2];
            uVar4 = param_1[4];
            param_1[2] = uVar4;
            param_1[3] = uVar3;
            param_1[4] = uVar7;
            param_1[5] = uVar2;
            if (uVar3 < uVar5) {
                uVar7 = *param_1;
                *param_1 = uVar4;
                param_1[1] = uVar3;
                param_1[2] = uVar7;
                param_1[3] = uVar5;
            }
        }
LAB_7102a637e8:
        if (param_1 + 6 != param_2) {
            lVar8 = 0;
            iVar9 = 0;
            puVar10 = param_1 + 4;
            puVar11 = param_1 + 6;
            do {
                if ((u32)puVar11[1] < (u32)puVar10[1]) {
                    uVar7 = *puVar11;
                    uVar2 = puVar11[1];
                    lVar6 = lVar8;
                    do {
                        lVar12 = lVar6;
                        *(u32 *)((s64)param_1 + lVar12 + 0x18) =
                             *(u32 *)((s64)param_1 + lVar12 + 0x10);
                        *(u32 *)((s64)param_1 + lVar12 + 0x1c) =
                             *(u32 *)((s64)param_1 + lVar12 + 0x14);
                        puVar13 = param_1 + 1;
                        puVar10 = param_1;
                        if (lVar12 == -0x10) goto LAB_7102a63858;
                        lVar6 = lVar12 + -8;
                    } while (uVar2 < *(u32 *)((s64)param_1 + lVar12 + 0xc));
                    puVar13 = (u32 *)((s64)param_1 + lVar12 + 0x14);
                    puVar10 = (u32 *)((s64)param_1 + lVar12 + 0x10);
LAB_7102a63858:
                    iVar9 = iVar9 + 1;
                    *puVar10 = uVar7;
                    *puVar13 = uVar2;
                    if (iVar9 == 8) {
                        return puVar11 + 2 == param_2;
                    }
                }
                puVar1 = puVar11 + 2;
                lVar8 = lVar8 + 8;
                puVar10 = puVar11;
                puVar11 = puVar1;
            } while (puVar1 != param_2);
        }
    }
    return true;
}
