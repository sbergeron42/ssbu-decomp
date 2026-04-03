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
// FUN_7100037cb0 — deduped to fun_medium_001.cpp
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
