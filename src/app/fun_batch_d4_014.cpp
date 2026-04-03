#include "types.h"

// MEDIUM-tier FUN_* functions — mixed 0x7100 ranges, batch d4-014
// Pool-d worker: auto-generated from Ghidra decompilation
// Includes: struct initializers, lookup tables, zero-fills, singleton guards

// ---- External declarations -----------------------------------------------

// DAT_100000001 — sentinel constant (address 0x100000001)
extern u8 DAT_100000001;

// Lookup tables
extern u8 DAT_710446f0e0; // FUN_7100031510 table
extern u8 DAT_710446f090; // FUN_7100031540 table
extern u8 DAT_71044705bc; // FUN_7100037790 table

// Static init globals (FUN_7100037cb0)
extern u64 DAT_71052aa330; // guard
extern u64 DAT_71052aa338, DAT_71052aa340, DAT_71052aa348, DAT_71052aa350, DAT_71052aa358;
extern u64 DAT_71052aa360, DAT_71052aa368, DAT_71052aa370, DAT_71052aa378;

// Static init globals (FUN_7100489c20)
extern u64 DAT_71052b7950; // guard
extern u8 DAT_71052b7960;  // singleton data

// Static init globals (FUN_7100489e80)
extern u64 DAT_71052b6f18; // guard
extern u64 DAT_71052b6a08; // vtable ptr storage
extern u64 PTR_LAB_7104f62810; // vtable label

// Forward-declared functions
extern "C" void FUN_71000339b0();
extern "C" void abort();

extern "C" s32 __cxa_guard_acquire(u64 *);
extern "C" void __cxa_guard_release(u64 *);

namespace nn { namespace detail {
    [[noreturn]] void UnexpectedDefaultImpl(const char *, const char *, s32);
}}

// ---- Functions ---------------------------------------------------------------

// 0x7100031330 — init struct: byte flag, packed const, &DAT_100000001 ptr at +0x14
void FUN_7100031330(s64 param_1)
{
    *(u8 *)(param_1 + 1) = 2;
    *(u64 *)(param_1 + 2) = 0x1000100000000ULL;
    *(u8 **)(param_1 + 0x14) = &DAT_100000001;
    *(u64 *)(param_1 + 0xc) = 0;
    *(u64 *)(param_1 + 0x1c) = 1;
}

// 0x7100031360 — init u16* struct with packed constants
void FUN_7100031360(u16 *param_1)
{
    *param_1 = 1;
    *(u64 *)(param_1 + 2) = 0x504030200000000ULL;
    *(u32 *)(param_1 + 8) = 0x10000;
    *(u64 *)(param_1 + 0x10) = 0x100000000ULL;
    *(u64 *)(param_1 + 0x18) = 0;
}

// 0x7100031390 — init u8* struct: flag, reserved, version fields
void FUN_7100031390(u8 *param_1)
{
    *param_1 = 1;
    *(u64 *)(param_1 + 4) = 0;
    *(u16 *)(param_1 + 2) = 0;
    *(u32 *)(param_1 + 0xc) = 1;
    *(u64 *)(param_1 + 0x18) = 0;
}

// 0x71000313b0 — init u8* struct: flag, u16 zero, packed constant
void FUN_71000313b0(u8 *param_1)
{
    *param_1 = 1;
    *(u16 *)(param_1 + 2) = 0;
    *(u64 *)(param_1 + 8) = 0x100000000ULL;
    *(u64 *)(param_1 + 0x18) = 0;
}

// 0x71000313f0 — init u64* struct with &DAT_100000001 pointer at index 2
void FUN_71000313f0(u64 *param_1)
{
    param_1[2] = (u64)&DAT_100000001;
    *param_1 = 0;
    param_1[1] = 0x100000000ULL;
    *(u16 *)(param_1 + 3) = 0;
    *(u64 *)((s64)param_1 + 0x1c) = 0x100000000ULL;
}

// 0x7100031410 — init u64* struct with &DAT_100000001 pointer at index 3
void FUN_7100031410(u64 *param_1)
{
    param_1[2] = 0;
    param_1[3] = (u64)&DAT_100000001;
    *(u32 *)(param_1 + 4) = 1;
    *param_1 = 0;
    param_1[1] = 0;
    *(u16 *)((s64)param_1 + 0x24) = 0;
    param_1[5] = 0x100000000ULL;
}

// 0x71000314e0 — init u8* struct: set flag, OR byte[1] bit0, store u64 param_2
void FUN_71000314e0(u8 *param_1, u64 param_2)
{
    *param_1 = 1;
    param_1[1] = param_1[1] | 1;
    *(u64 *)(param_1 + 8) = param_2;
}

// 0x7100031510 — table lookup in DAT_710446f0e0, range [0x27..0x3b), default 4
u32 FUN_7100031510(s32 param_1)
{
    if ((u32)(param_1 - 0x27) < 0x14) {
        return *(u32 *)(&DAT_710446f0e0 + (s64)(s32)((u32)param_1 - 0x27) * 4);
    }
    return 4;
}

// 0x7100031540 — table lookup in DAT_710446f090, range [0x27..0x3b), default 4
u32 FUN_7100031540(s32 param_1)
{
    if ((u32)(param_1 - 0x27) < 0x14) {
        return *(u32 *)(&DAT_710446f090 + (s64)(s32)((u32)param_1 - 0x27) * 4);
    }
    return 4;
}

// 0x71000316b0 — decode mode [1,2,3] using param_2/param_3 bit0 flags
u32 FUN_71000316b0(s32 param_1, u64 param_2, u64 param_3)
{
    u32 uVar1;
    u32 uVar2;

    if (param_1 == 3) {
        return 2;
    }
    if (param_1 == 2) {
        uVar2 = 6;
        uVar1 = 7;
        if ((param_3 & 1) == 0) {
            uVar2 = 1;
            uVar1 = 5;
        }
        if ((param_2 & 1) != 0) {
            uVar2 = uVar1;
        }
        return uVar2;
    }
    if (param_1 != 1) {
        nn::detail::UnexpectedDefaultImpl("", "", 0);
    }
    uVar1 = 4;
    if ((param_2 & 1) == 0) {
        uVar1 = 0;
    }
    return uVar1;
}

// 0x7100037790 — table lookup in DAT_71044705bc, stride 8, index = param_1 & 0xffffffff
u32 FUN_7100037790(u64 param_1)
{
    return *(u32 *)(&DAT_71044705bc + (param_1 & 0xffffffff) * 8);
}

// 0x7100037cb0 — singleton init: zero 9 u64 globals, return &DAT_71052aa338
u64 *FUN_7100037cb0(void)
{
    s32 iVar1;

    if (((DAT_71052aa330 & 1) == 0) && (iVar1 = __cxa_guard_acquire(&DAT_71052aa330), iVar1 != 0)) {
        DAT_71052aa370 = 0;
        DAT_71052aa378 = 0;
        DAT_71052aa360 = 0;
        DAT_71052aa368 = 0;
        DAT_71052aa338 = 0;
        DAT_71052aa350 = 0;
        DAT_71052aa358 = 0;
        DAT_71052aa340 = 0;
        DAT_71052aa348 = 0;
        __cxa_guard_release(&DAT_71052aa330);
    }
    return &DAT_71052aa338;
}

// 0x71000380b0 — check nested ptr: if [lVar1+0x30] != [lVar1+0x20], clear; else call FUN_71000339b0
void FUN_71000380b0(s64 param_1)
{
    s64 lVar1;

    lVar1 = *(s64 *)(param_1 + 0x28);
    if (*(s64 *)(lVar1 + 0x30) != *(s64 *)(lVar1 + 0x20)) {
        *(u64 *)(lVar1 + 0x30) = 0;
        return;
    }
    FUN_71000339b0();
    *(u64 *)(lVar1 + 0x30) = 0;
}

// 0x7100038120 — zero-fill 15 u64 fields (out-of-order sequence)
void FUN_7100038120(u64 *param_1)
{
    param_1[0xd] = 0;
    param_1[0xe] = 0;
    *param_1 = 0;
    param_1[0xb] = 0;
    param_1[0xc] = 0;
    param_1[9] = 0;
    param_1[10] = 0;
    param_1[7] = 0;
    param_1[8] = 0;
    param_1[5] = 0;
    param_1[6] = 0;
    param_1[3] = 0;
    param_1[4] = 0;
    param_1[1] = 0;
    param_1[2] = 0;
}

// 0x7100039e30 — zero-fill 9 u64 fields
void FUN_7100039e30(u64 *param_1)
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

// 0x710003a0e0 — zero-fill 27 u64 fields (out-of-order sequence)
void FUN_710003a0e0(u64 *param_1)
{
    param_1[0x19] = 0;
    param_1[0x1a] = 0;
    *param_1 = 0;
    param_1[0x17] = 0;
    param_1[0x18] = 0;
    param_1[0x15] = 0;
    param_1[0x16] = 0;
    param_1[0x13] = 0;
    param_1[0x14] = 0;
    param_1[0x11] = 0;
    param_1[0x12] = 0;
    param_1[0xf] = 0;
    param_1[0x10] = 0;
    param_1[0xd] = 0;
    param_1[0xe] = 0;
    param_1[0xb] = 0;
    param_1[0xc] = 0;
    param_1[9] = 0;
    param_1[10] = 0;
    param_1[7] = 0;
    param_1[8] = 0;
    param_1[5] = 0;
    param_1[6] = 0;
    param_1[3] = 0;
    param_1[4] = 0;
    param_1[1] = 0;
    param_1[2] = 0;
}

// 0x710003a240 — zero-fill 9 u64 fields
void FUN_710003a240(u64 *param_1)
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

// 0x710003a3c0 — zero-fill 9 u64 fields
void FUN_710003a3c0(u64 *param_1)
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

// 0x71000a6610 — check 8 mask/value pairs at param_1+0x1188..+0x11a4, return matching u64
u64 FUN_71000a6610(s64 param_1, u64 param_2)
{
    if (param_2 == 0) return 0;
    if ((*(u32 *)(param_1 + 0x1188) & param_2) != 0)
        return *(u64 *)(param_1 + 0x11a8);
    if ((*(u32 *)(param_1 + 0x118c) & param_2) != 0)
        return *(u64 *)(param_1 + 0x11b0);
    if ((*(u32 *)(param_1 + 0x1190) & param_2) != 0)
        return *(u64 *)(param_1 + 0x11b8);
    if ((*(u32 *)(param_1 + 0x1194) & param_2) != 0)
        return *(u64 *)(param_1 + 0x11c0);
    if ((*(u32 *)(param_1 + 0x1198) & param_2) != 0)
        return *(u64 *)(param_1 + 0x11c8);
    if ((*(u32 *)(param_1 + 0x119c) & param_2) != 0)
        return *(u64 *)(param_1 + 0x11d0);
    if ((*(u32 *)(param_1 + 0x11a0) & param_2) != 0)
        return *(u64 *)(param_1 + 0x11d8);
    if ((*(u32 *)(param_1 + 0x11a4) & param_2) != 0)
        return *(u64 *)(param_1 + 0x11e0);
    return 0;
}

// 0x71003cb310 — abort wrapper
void FUN_71003cb310(void)
{
    abort();
}

// 0x7100489c20 — singleton guard: init guard byte, return &DAT_71052b7960
u8 *FUN_7100489c20(void)
{
    s32 iVar1;

    if (((DAT_71052b7950 & 1) == 0) && (iVar1 = __cxa_guard_acquire(&DAT_71052b7950), iVar1 != 0)) {
        __cxa_guard_release(&DAT_71052b7950);
    }
    return &DAT_71052b7960;
}

// 0x7100489e80 — singleton guard: init vtable ptr, return &DAT_71052b6a08
u64 *FUN_7100489e80(void)
{
    s32 iVar1;

    if (((DAT_71052b6f18 & 1) == 0) && (iVar1 = __cxa_guard_acquire(&DAT_71052b6f18), iVar1 != 0)) {
        DAT_71052b6a08 = (u64)&PTR_LAB_7104f62810;
        __cxa_guard_release(&DAT_71052b6f18);
    }
    return &DAT_71052b6a08;
}
