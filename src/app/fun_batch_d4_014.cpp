#include "types.h"

// MEDIUM-tier FUN_* functions — mixed 0x7100 ranges, batch d4-014
// Pool-d worker: auto-generated from Ghidra decompilation
// Includes: struct initializers, lookup tables, zero-fills, singleton guards

// ---- External declarations -----------------------------------------------

// Bitmask immediate constants used in struct initializers
// Ghidra misinterprets these as &DAT_ addresses; they are literal values

// Lookup tables
#pragma GCC visibility push(hidden)
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
#pragma GCC visibility pop

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
void FUN_7100031330(s64 self)
{
    *(u8 *)(self + 1) = 2;
    *(u64 *)(self + 2) = 0x1000100000000ULL;
    *(u64 *)(self + 0x14) = 0x100000001ULL;
    *(u64 *)(self + 0xc) = 0;
    *(u64 *)(self + 0x1c) = 1;
}

// 0x71000313f0 — init u64* struct with &DAT_100000001 pointer at index 2
void FUN_71000313f0(u64 *self)
{
    self[2] = 0x100000001ULL;
    *self = 0;
    self[1] = 0x100000000ULL;
    *(u16 *)(self + 3) = 0;
    *(u64 *)((s64)self + 0x1c) = 0x100000000ULL;
}

// 0x7100031410 — init u64* struct with &DAT_100000001 pointer at index 3
void FUN_7100031410(u64 *self)
{
    self[2] = 0;
    self[3] = 0x100000001ULL;
    *(u32 *)(self + 4) = 1;
    *self = 0;
    self[1] = 0;
    *(u16 *)((s64)self + 0x24) = 0;
    self[5] = 0x100000000ULL;
}

// 0x71000316b0 — decode mode [1,2,3] using flag_a/flag_b bit0 flags
u32 FUN_71000316b0(s32 mode, u64 flag_a, u64 flag_b)
{
    u32 alt_result;
    u32 result;

    if (mode == 3) {
        return 2;
    }
    if (mode == 2) {
        result = 6;
        alt_result = 7;
        if ((flag_b & 1) == 0) {
            result = 1;
            alt_result = 5;
        }
        if ((flag_a & 1) != 0) {
            result = alt_result;
        }
        return result;
    }
    if (mode != 1) {
        nn::detail::UnexpectedDefaultImpl("", "", 0);
    }
    alt_result = 4;
    if ((flag_a & 1) == 0) {
        alt_result = 0;
    }
    return alt_result;
}

// 0x7100037790 — table lookup in DAT_71044705bc, stride 8, index = index & 0xffffffff
u32 FUN_7100037790(u64 index)
{
    return *(u32 *)(&DAT_71044705bc + (index & 0xffffffff) * 8);
}

// 0x7100037cb0 — singleton init: zero 9 u64 globals, return &DAT_71052aa338
u64 *FUN_7100037cb0(void)
{
    s32 acquired;

    if (((DAT_71052aa330 & 1) == 0) && (acquired = __cxa_guard_acquire(&DAT_71052aa330), acquired != 0)) {
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

// 0x71000380b0 — check nested ptr: if [inner+0x30] != [inner+0x20], clear; else call FUN_71000339b0
void FUN_71000380b0(s64 self)
{
    s64 inner;

    inner = *(s64 *)(self + 0x28);
    if (*(s64 *)(inner + 0x30) != *(s64 *)(inner + 0x20)) {
        *(u64 *)(inner + 0x30) = 0;
        return;
    }
    FUN_71000339b0();
    *(u64 *)(inner + 0x30) = 0;
}

// 0x7100038120 — zero-fill 15 u64 fields (out-of-order sequence)
void FUN_7100038120(u64 *data)
{
    data[0xd] = 0;
    data[0xe] = 0;
    *data = 0;
    data[0xb] = 0;
    data[0xc] = 0;
    data[9] = 0;
    data[10] = 0;
    data[7] = 0;
    data[8] = 0;
    data[5] = 0;
    data[6] = 0;
    data[3] = 0;
    data[4] = 0;
    data[1] = 0;
    data[2] = 0;
}

// 0x7100039e30 — zero-fill 9 u64 fields
void FUN_7100039e30(u64 *data)
{
    data[7] = 0;
    data[8] = 0;
    *data = 0;
    data[5] = 0;
    data[6] = 0;
    data[3] = 0;
    data[4] = 0;
    data[1] = 0;
    data[2] = 0;
}

// 0x710003a0e0 — zero-fill 27 u64 fields (out-of-order sequence)
void FUN_710003a0e0(u64 *data)
{
    data[0x19] = 0;
    data[0x1a] = 0;
    *data = 0;
    data[0x17] = 0;
    data[0x18] = 0;
    data[0x15] = 0;
    data[0x16] = 0;
    data[0x13] = 0;
    data[0x14] = 0;
    data[0x11] = 0;
    data[0x12] = 0;
    data[0xf] = 0;
    data[0x10] = 0;
    data[0xd] = 0;
    data[0xe] = 0;
    data[0xb] = 0;
    data[0xc] = 0;
    data[9] = 0;
    data[10] = 0;
    data[7] = 0;
    data[8] = 0;
    data[5] = 0;
    data[6] = 0;
    data[3] = 0;
    data[4] = 0;
    data[1] = 0;
    data[2] = 0;
}

// 0x710003a240 — zero-fill 9 u64 fields
void FUN_710003a240(u64 *data)
{
    data[7] = 0;
    data[8] = 0;
    *data = 0;
    data[5] = 0;
    data[6] = 0;
    data[3] = 0;
    data[4] = 0;
    data[1] = 0;
    data[2] = 0;
}

// 0x710003a3c0 — zero-fill 9 u64 fields
void FUN_710003a3c0(u64 *data)
{
    data[7] = 0;
    data[8] = 0;
    *data = 0;
    data[5] = 0;
    data[6] = 0;
    data[3] = 0;
    data[4] = 0;
    data[1] = 0;
    data[2] = 0;
}

// 0x71000a6610 — check 8 mask/value pairs at self+0x1188..+0x11a4, return matching u64
u64 FUN_71000a6610(s64 self, u64 mask_bits)
{
    if (mask_bits == 0) return 0;
    if ((*(u32 *)(self + 0x1188) & mask_bits) != 0)
        return *(u64 *)(self + 0x11a8);
    if ((*(u32 *)(self + 0x118c) & mask_bits) != 0)
        return *(u64 *)(self + 0x11b0);
    if ((*(u32 *)(self + 0x1190) & mask_bits) != 0)
        return *(u64 *)(self + 0x11b8);
    if ((*(u32 *)(self + 0x1194) & mask_bits) != 0)
        return *(u64 *)(self + 0x11c0);
    if ((*(u32 *)(self + 0x1198) & mask_bits) != 0)
        return *(u64 *)(self + 0x11c8);
    if ((*(u32 *)(self + 0x119c) & mask_bits) != 0)
        return *(u64 *)(self + 0x11d0);
    if ((*(u32 *)(self + 0x11a0) & mask_bits) != 0)
        return *(u64 *)(self + 0x11d8);
    if ((*(u32 *)(self + 0x11a4) & mask_bits) != 0)
        return *(u64 *)(self + 0x11e0);
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
    s32 acquired;

    if (((DAT_71052b7950 & 1) == 0) && (acquired = __cxa_guard_acquire(&DAT_71052b7950), acquired != 0)) {
        __cxa_guard_release(&DAT_71052b7950);
    }
    return &DAT_71052b7960;
}

// 0x7100489e80 — singleton guard: init vtable ptr, return &DAT_71052b6a08
u64 *FUN_7100489e80(void)
{
    s32 acquired;

    if (((DAT_71052b6f18 & 1) == 0) && (acquired = __cxa_guard_acquire(&DAT_71052b6f18), acquired != 0)) {
        DAT_71052b6a08 = (u64)&PTR_LAB_7104f62810;
        __cxa_guard_release(&DAT_71052b6f18);
    }
    return &DAT_71052b6a08;
}
