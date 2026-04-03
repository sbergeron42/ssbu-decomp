#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7100 address range, batch d4-006
// Pool-d worker: auto-generated from Ghidra decompilation
// Includes: scene inits, vtable dispatchers, static inits, loop dispatchers

// ---- External declarations -----------------------------------------------

[[noreturn]] extern "C" void abort();
extern "C" s32  __cxa_guard_acquire(u64 *);
extern "C" void __cxa_guard_release(u64 *);

// Vtable/PTR data
extern u8 PTR_PTR_FUN_71050b5898;
extern u8 PTR_PTR_FUN_71050b8608;
extern u8 PTR__Module_7104f61810;

// Scene data fields — MeleeScene (0x7100422720)
extern u64        DAT_7105326b80;
extern const char *DAT_7105326b88;
extern u64        DAT_7105326b90;
extern u64        DAT_7105326b98;
extern u64        DAT_7105326ba0;
extern u64        DAT_71053267b0;  // guard

// Scene data fields — StaffRollScene (0x7100428010)
extern u64        DAT_7105327d48;
extern const char *DAT_7105327d50;
extern u64        DAT_7105327d58;
extern u64        DAT_7105327d60;
extern u64        DAT_7105327d68;
extern u64        DAT_7105327d70;  // guard

// Static-init data (FUN_7100489c00)
extern u64 DAT_71052b6950;  // guard
extern u8  DAT_71052b6960;  // data

// Static-init data (FUN_7100489e60)
extern u64 DAT_71052b5f18;  // guard
extern u64 DAT_71052b5a08;  // stores vtable pointer

// Static-init data (FUN_710048a790)
extern u64 DAT_71052b6218;  // guard
extern u64 DAT_71052b5da0;
extern u64 DAT_71052b5da8;

// Static-init data (FUN_710049f630)
extern u64 DAT_71052b6a38;  // guard
extern u64 DAT_71052b6a40;
extern u64 DAT_71052b6a48;

// ---- Functions ---------------------------------------------------------------

// 0x7100422720 — scene init: MeleeScene registration
void FUN_7100422720()
{
    s32 iVar1;

    DAT_7105326b80 = 0;
    DAT_7105326b88 = "MeleeScene";
    if (((DAT_71053267b0 & 1) == 0) && (iVar1 = __cxa_guard_acquire(&DAT_71053267b0), iVar1 != 0)) {
        __cxa_guard_release(&DAT_71053267b0);
    }
    DAT_7105326b98 = 0;
    DAT_7105326ba0 = 0;
    DAT_7105326b90 = (u64)&PTR_PTR_FUN_71050b5898;
}

// 0x7100428010 — scene init: StaffRollScene registration
void FUN_7100428010()
{
    s32 iVar1;

    DAT_7105327d48 = 0;
    DAT_7105327d50 = "StaffRollScene";
    if (((DAT_7105327d70 & 1) == 0) && (iVar1 = __cxa_guard_acquire(&DAT_7105327d70), iVar1 != 0)) {
        __cxa_guard_release(&DAT_7105327d70);
    }
    DAT_7105327d60 = 0;
    DAT_7105327d68 = 0;
    DAT_7105327d58 = (u64)&PTR_PTR_FUN_71050b8608;
}

// 0x71004523d8 — vtable dispatch: call vtable[0x248], return XOR 1
u32 FUN_71004523d8(s64 *param_1)
{
    u32 uVar1;

    uVar1 = (**(u32 (**)())(*param_1 + 0x248))();
    return (uVar1 ^ 1) & 1;
}

// 0x710047a040 — loop: iterate linked entries, dispatch vtable[0x18] if active and unlinked
void FUN_710047a040(s64 param_1, u32 param_2)
{
    s32 iVar1;
    s64 *plVar2;
    s64 lVar3;
    s64 *plVar4;

    if (*(u8 *)(param_1 + 0x1bc) == '\0') {
        iVar1 = *(s32 *)(param_1 + 0x20);
        if (param_2 == 0xffffffff) {
            if (0 < iVar1) {
                lVar3 = (s64)iVar1 + 1;
                plVar4 = (s64 *)(param_1 + (s64)iVar1 * 0x18 + 0x18);
                do {
                    plVar2 = (s64 *)*plVar4;
                    if (((u8)plVar2[6] != '\0') && (*(u8 *)((s64)plVar2 + 0x31) == '\0')) {
                        (**(void (**)(s64 *, u64))(*plVar2 + 0x18))(plVar2, *(u64 *)(param_1 + 8));
                    }
                    lVar3 = lVar3 + -1;
                    plVar4 = plVar4 + -3;
                } while (1 < lVar3);
            }
        }
        else if (0 < iVar1) {
            lVar3 = (s64)iVar1 + 1;
            plVar4 = (s64 *)(param_1 + (s64)iVar1 * 0x18 + 0x18);
            do {
                if ((((*(u32 *)((s64)plVar4 + 0xc) & param_2) != 0) &&
                    (plVar2 = (s64 *)*plVar4, (u8)plVar2[6] != '\0')) &&
                   (*(u8 *)((s64)plVar2 + 0x31) == '\0')) {
                    (**(void (**)(s64 *, u64))(*plVar2 + 0x18))(plVar2, *(u64 *)(param_1 + 8));
                }
                lVar3 = lVar3 + -1;
                plVar4 = plVar4 + -3;
            } while (1 < lVar3);
        }
    }
}

// 0x7100489c00 — static init: empty guard, return pointer to data
u8 *FUN_7100489c00()
{
    s32 iVar1;

    if (((DAT_71052b6950 & 1) == 0) && (iVar1 = __cxa_guard_acquire(&DAT_71052b6950), iVar1 != 0)) {
        __cxa_guard_release(&DAT_71052b6950);
    }
    return &DAT_71052b6960;
}

// 0x7100489e60 — static init: set module vtable pointer, return pointer
u64 *FUN_7100489e60()
{
    s32 iVar1;

    if (((DAT_71052b5f18 & 1) == 0) && (iVar1 = __cxa_guard_acquire(&DAT_71052b5f18), iVar1 != 0)) {
        DAT_71052b5a08 = (u64)&PTR__Module_7104f61810;
        __cxa_guard_release(&DAT_71052b5f18);
    }
    return &DAT_71052b5a08;
}

// 0x710048a790 — static init: set -1 sentinel + 0, return pointer
u64 *FUN_710048a790()
{
    s32 iVar1;

    if (((DAT_71052b6218 & 1) == 0) && (iVar1 = __cxa_guard_acquire(&DAT_71052b6218), iVar1 != 0)) {
        DAT_71052b5da0 = 0xffffffffffffffff;
        DAT_71052b5da8 = 0;
        __cxa_guard_release(&DAT_71052b6218);
    }
    return &DAT_71052b5da0;
}

// 0x710049d9d0 — vtable dispatch: call vtable[0x280], mask 40 bits, return != 0
u8 FUN_710049d9d0(s64 *param_1)
{
    u64 uVar1;

    uVar1 = (**(u64 (**)())(*param_1 + 0x280))();
    return (uVar1 & 0xffffffffff) != 0;
}

// 0x710049f550 — vtable chain: deref +0x10+0x38, call vtable[0x10] then vtable[0x78], return NOT(bit0)
u32 FUN_710049f550(s64 param_1)
{
    u32 uVar1;
    s64 *plVar2;

    plVar2 = *(s64 **)(*(s64 *)(param_1 + 0x10) + 0x38);
    plVar2 = (s64 *)(**(u64 (**)(s64 *, s32))(*plVar2 + 0x10))(plVar2, 0);
    uVar1 = (**(u32 (**)())(*plVar2 + 0x78))();
    return ~uVar1 & 1;
}

// 0x710049f598 — vtable dispatch: call vtable[0x20] with 40-bit param, return != -1
u8 FUN_710049f598(s64 param_1, u64 param_2, u64 param_3)
{
    s32 iVar1;

    iVar1 = (**(s32 (**)(s64 *, u64))(**(s64 **)(param_1 + 8) + 0x20))
                (*(s64 **)(param_1 + 8), param_3 & 0xffffffffff);
    return iVar1 != -1;
}
// 0x710049f630 — conditional static init + vtable lookup
u64 FUN_710049f630(s64 param_1, u64 param_2)
{
    s32 iVar1;
    u64 uVar2;
    s64 lVar3;

    lVar3 = *(s64 *)(param_1 + 0x18);
    if (lVar3 == 0) {
        if (((DAT_71052b6a38 & 1) == 0) && (iVar1 = __cxa_guard_acquire(&DAT_71052b6a38), iVar1 != 0)) {
            DAT_71052b6a40 = 0;
            DAT_71052b6a48 = 0;
            __cxa_guard_release(&DAT_71052b6a38);
        }
        return DAT_71052b6a40;
    }
    if (((param_2 & 0xffffffff) < (u64)((*(s64 *)(lVar3 + 0x90) - *(s64 *)(lVar3 + 0x88)) >> 3)) &&
       (lVar3 = *(s64 *)(*(s64 *)(lVar3 + 0x88) + (s64)(param_2 & 0xffffffff) * 8),
       *(u8 *)(lVar3 + 0x88) != '\0')) {
        uVar2 = (**(u64 (**)())(**(s64 **)(lVar3 + 0x70) + 0x60))();
        return uVar2;
    }
    return 0;
}
