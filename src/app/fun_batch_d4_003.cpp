#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7100 address range, batch d4-003
// Pool-d worker: auto-generated from Ghidra decompilation
// Includes: float dispatchers, noreturn stubs, static initializers, vtable init

// ---- External declarations -----------------------------------------------

[[noreturn]] extern "C" void abort();
extern "C" s32  __cxa_guard_acquire(u64 *);
extern "C" void __cxa_guard_release(u64 *);

// External FUN_* forward declarations
extern "C" void FUN_71037378c0(u64 *);
extern "C" void FUN_71000001c0(void *, void *, void *);

// External labels (used as function/destructor pointers)
extern void LAB_7103737890();

// External data
extern u32 DAT_71044718a4;
extern u32 DAT_71044723d8;
extern u64 PTR_FUN_7104f61778;
extern u8  PTR_LAB_7104f65570;
extern u8  PTR_LOOP_7104f16000;

// Static-init guard variables
extern u64 DAT_71052b7030;
extern u64 DAT_71052b70e0;
extern u64 DAT_71052b71b8;
extern u64 DAT_71052b7218;
extern u64 DAT_71052b72c8;
extern u64 DAT_71052b72d0;
extern u64 DAT_71052b72d8;

// Static-init data variables
extern u64 DAT_71052b7040;
extern u64 DAT_71052b7048;
extern u64 DAT_71052b7050;
extern u64 DAT_71052b7058;
extern u64 DAT_71052b7060;
extern u64 DAT_71052b7068;
extern u64 DAT_71052b7070;
extern u64 DAT_71052b7078;
extern u64 DAT_71052b70e8;
extern u64 DAT_71052b70f0;
extern u64 DAT_71052b6d68;
extern u64 DAT_71052b6da0;
extern u64 DAT_71052b6da8;
extern u64 DAT_71052b6e10;
extern u64 DAT_71052b6e18;
extern u64 DAT_71052b6e20;
extern u64 DAT_71052b6e28;
extern u64 DAT_71052b6e30;
extern u64 DAT_71052b6e38;

// ---- Functions ---------------------------------------------------------------

// 0x7100325e50 — float table lookup: return float constant for motion group index
u32 FUN_7100325e50(s64 param_1, u32 param_2)
{
    switch(param_2) {
    case 0x23:
        return 0;
    case 0x24:
    case 0x25:
    case 0x26:
    case 0x27:
        return 0x41c80000;
    case 0x3f:
    case 0x40:
    case 0x41:
        return DAT_71044718a4;
    case 0x42:
    case 0x43:
    case 0x44:
    case 0x45:
    case 0x46:
        if (*(s32 *)(param_1 + 0x120) == 0x39) {
            return 0x41a00000;
        }
        if (*(s32 *)(param_1 + 0x120) == 0x47) {
            return 0x41a00000;
        }
    }
    return DAT_71044723d8;
}

// 0x71003a48bc — [[noreturn]] std::vector out-of-range throw stub
[[noreturn]] void FUN_71003a48bc()
{
    abort();
}

// 0x71003a71f0 — ctor init: set vtable, init two list nodes to empty/invalid
void FUN_71003a71f0(u64 *param_1)
{
    *param_1 = (u64)&PTR_FUN_7104f61778;
    FUN_71037378c0(param_1 + 0xc);
    param_1[0xc] = 0;
    *(u32 *)(param_1 + 0xd) = 0xffffffff;
    FUN_71037378c0(param_1 + 10);
    *(u32 *)(param_1 + 0xb) = 0xffffffff;
    param_1[10] = 0;
}

// 0x71003b18a0 — static init: zero 8 u64 fields, return pointer to first
u64 *FUN_71003b18a0()
{
    s32 acquired;

    if (((DAT_71052b7030 & 1) == 0) && (acquired = __cxa_guard_acquire(&DAT_71052b7030), acquired != 0)) {
        DAT_71052b7070 = 0;
        DAT_71052b7078 = 0;
        DAT_71052b7060 = 0;
        DAT_71052b7068 = 0;
        DAT_71052b7050 = 0;
        DAT_71052b7058 = 0;
        DAT_71052b7040 = 0;
        DAT_71052b7048 = 0;
        __cxa_guard_release(&DAT_71052b7030);
    }
    return &DAT_71052b7040;
}

// 0x71003b2db0 — static init: set pair of float-packed u64 constants, return pointer
u64 *FUN_71003b2db0()
{
    s32 acquired;

    if (((DAT_71052b70e0 & 1) == 0) && (acquired = __cxa_guard_acquire(&DAT_71052b70e0), acquired != 0)) {
        DAT_71052b70e8 = 0x40800000c0800000;
        DAT_71052b70f0 = 0xc120000041600000;
        __cxa_guard_release(&DAT_71052b70e0);
    }
    return &DAT_71052b70e8;
}

// 0x71003b6890 — static init: set vtable pointer, return pointer to it
u64 *FUN_71003b6890()
{
    s32 acquired;

    if (((DAT_71052b71b8 & 1) == 0) && (acquired = __cxa_guard_acquire(&DAT_71052b71b8), acquired != 0)) {
        DAT_71052b6d68 = (u64)&PTR_LAB_7104f65570;
        __cxa_guard_release(&DAT_71052b71b8);
    }
    return &DAT_71052b6d68;
}

// 0x71003b79b0 — static init: set -1 sentinel + 0, return pointer
u64 *FUN_71003b79b0()
{
    s32 acquired;

    if (((DAT_71052b7218 & 1) == 0) && (acquired = __cxa_guard_acquire(&DAT_71052b7218), acquired != 0)) {
        DAT_71052b6da0 = 0xffffffffffffffff;
        DAT_71052b6da8 = 0;
        __cxa_guard_release(&DAT_71052b7218);
    }
    return &DAT_71052b6da0;
}

// 0x71003b7a50 — static init: set -1 sentinel + 0, return pointer (same body as b79b0)
u64 *FUN_71003b7a50()
{
    s32 acquired;

    if (((DAT_71052b7218 & 1) == 0) && (acquired = __cxa_guard_acquire(&DAT_71052b7218), acquired != 0)) {
        DAT_71052b6da0 = 0xffffffffffffffff;
        DAT_71052b6da8 = 0;
        __cxa_guard_release(&DAT_71052b7218);
    }
    return &DAT_71052b6da0;
}

// 0x71003b7af0 — static init: set -1 sentinel + 0, return pointer (same body as b79b0)
u64 *FUN_71003b7af0()
{
    s32 acquired;

    if (((DAT_71052b7218 & 1) == 0) && (acquired = __cxa_guard_acquire(&DAT_71052b7218), acquired != 0)) {
        DAT_71052b6da0 = 0xffffffffffffffff;
        DAT_71052b6da8 = 0;
        __cxa_guard_release(&DAT_71052b7218);
    }
    return &DAT_71052b6da0;
}

// 0x71003b9270 — vtable dispatch: call vtable[0x150] with no args, mask to 40 bits
u64 FUN_71003b9270(s64 *param_1)
{
    u64 result;

    result = (**(u64 (**)())(*param_1 + 0x150))();
    return result & 0xffffffffff;
}

// 0x71003ba030 — static init: init object, register destructor, return pointer
u64 *FUN_71003ba030()
{
    s32 acquired;

    if (((DAT_71052b72d8 & 1) == 0) && (acquired = __cxa_guard_acquire(&DAT_71052b72d8), acquired != 0)) {
        DAT_71052b6e10 = 0;
        DAT_71052b6e18 = 0xffffffff;
        FUN_71000001c0((void *)&LAB_7103737890, (void *)&DAT_71052b6e10, (void *)&PTR_LOOP_7104f16000);
        __cxa_guard_release(&DAT_71052b72d8);
    }
    return &DAT_71052b6e10;
}

// 0x71003ba3b0 — static init: init object, register destructor, return pointer
u64 *FUN_71003ba3b0()
{
    s32 acquired;

    if (((DAT_71052b72d0 & 1) == 0) && (acquired = __cxa_guard_acquire(&DAT_71052b72d0), acquired != 0)) {
        DAT_71052b6e20 = 0;
        DAT_71052b6e28 = 0xffffffff;
        FUN_71000001c0((void *)&LAB_7103737890, (void *)&DAT_71052b6e20, (void *)&PTR_LOOP_7104f16000);
        __cxa_guard_release(&DAT_71052b72d0);
    }
    return &DAT_71052b6e20;
}

// 0x71003ba420 — static init: set two u32 out-params to -1, init object, register dtor
u64 *FUN_71003ba420(u64 param_1, u32 *param_2, u32 *param_3)
{
    s32 acquired;

    *param_2 = 0xffffffff;
    *param_3 = 0xffffffff;
    if (((DAT_71052b72c8 & 1) == 0) && (acquired = __cxa_guard_acquire(&DAT_71052b72c8), acquired != 0)) {
        DAT_71052b6e30 = 0;
        DAT_71052b6e38 = 0xffffffff;
        FUN_71000001c0((void *)&LAB_7103737890, (void *)&DAT_71052b6e30, (void *)&PTR_LOOP_7104f16000);
        __cxa_guard_release(&DAT_71052b72c8);
    }
    return &DAT_71052b6e30;
}

// 0x71003cb1b0 — [[noreturn]] abort stub
[[noreturn]] void FUN_71003cb1b0()
{
    abort();
}
