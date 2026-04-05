#include "types.h"

// ---- External declarations -----------------------------------------------

[[noreturn]] extern "C" void abort();
extern "C" s32  __cxa_guard_acquire(u64 *);
extern "C" void __cxa_guard_release(u64 *);

extern u8 PTR_PTR_FUN_71050b5898;
extern u8 PTR_PTR_FUN_71050b8608;
extern u8 PTR__Module_7104f61810;

// MeleeScene data (0x7100422720)
extern u64        DAT_7105326b80;
extern const char *DAT_7105326b88;
extern u64        DAT_7105326b90;
extern u64        DAT_7105326b98;
extern u64        DAT_7105326ba0;
extern u64        DAT_71053267b0;

// StaffRollScene data (0x7100428010)
extern u64        DAT_7105327d48;
extern const char *DAT_7105327d50;
extern u64        DAT_7105327d58;
extern u64        DAT_7105327d60;
extern u64        DAT_7105327d68;
extern u64        DAT_7105327d70;

// Static-init guards and data
extern u64 DAT_71052b6950;
extern u8  DAT_71052b6960;
extern u64 DAT_71052b5f18;
extern u64 DAT_71052b5a08;
extern u64 DAT_71052b6218;
extern u64 DAT_71052b5da0;
extern u64 DAT_71052b5da8;
extern u64 DAT_71052b6a38;
extern u64 DAT_71052b6a40;
extern u64 DAT_71052b6a48;

// ---- Functions ---------------------------------------------------------------

// 0x7100422720 — MeleeScene registration: set name, guard-init, store vtable
void FUN_7100422720()
{
    s32 acquired;

    DAT_7105326b80 = 0;
    DAT_7105326b88 = "MeleeScene";
    if (((DAT_71053267b0 & 1) == 0) && (acquired = __cxa_guard_acquire(&DAT_71053267b0), acquired != 0)) {
        __cxa_guard_release(&DAT_71053267b0);
    }
    DAT_7105326b98 = 0;
    DAT_7105326ba0 = 0;
    DAT_7105326b90 = (u64)&PTR_PTR_FUN_71050b5898;
}

// 0x7100428010 — StaffRollScene registration: set name, guard-init, store vtable
void FUN_7100428010()
{
    s32 acquired;

    DAT_7105327d48 = 0;
    DAT_7105327d50 = "StaffRollScene";
    if (((DAT_7105327d70 & 1) == 0) && (acquired = __cxa_guard_acquire(&DAT_7105327d70), acquired != 0)) {
        __cxa_guard_release(&DAT_7105327d70);
    }
    DAT_7105327d60 = 0;
    DAT_7105327d68 = 0;
    DAT_7105327d58 = (u64)&PTR_PTR_FUN_71050b8608;
}

// 0x71004523d8 — Calls vtable[0x248], returns inverted bit 0
u32 FUN_71004523d8(s64 *this_ptr)
{
    u32 result;

    result = (**(u32 (**)())(*this_ptr + 0x248))();
    return (result ^ 1) & 1;
}

// 0x710047a040 — Iterates entry list in reverse, dispatches vtable[0x18] on active/unlinked entries
// Entries at stride 0x18 from base+0x30 down to base+0x18; count at +0x20
// Each entry slot: [0]=ptr to entry obj, [+0xc]=filter mask
// Entry obj: vtable at [0], active flag at byte[0x30], linked flag at byte[0x31]
void FUN_710047a040(s64 list, u32 filter_mask)
{
    s32 num_entries;
    s64 *entry;
    s64 remaining;
    s64 *slot;

    if (*(u8 *)(list + 0x1bc) == '\0') {
        num_entries = *(s32 *)(list + 0x20);
        if (filter_mask == 0xffffffff) {
            if (0 < num_entries) {
                remaining = (s64)num_entries + 1;
                slot = (s64 *)(list + (s64)num_entries * 0x18 + 0x18);
                do {
                    entry = (s64 *)*slot;
                    if (((u8)entry[6] != '\0') && (*(u8 *)((s64)entry + 0x31) == '\0')) {
                        (**(void (**)(s64 *, u64))(*entry + 0x18))(entry, *(u64 *)(list + 8));
                    }
                    remaining = remaining + -1;
                    slot = slot + -3;
                } while (1 < remaining);
            }
        }
        else if (0 < num_entries) {
            remaining = (s64)num_entries + 1;
            slot = (s64 *)(list + (s64)num_entries * 0x18 + 0x18);
            do {
                if ((((*(u32 *)((s64)slot + 0xc) & filter_mask) != 0) &&
                    (entry = (s64 *)*slot, (u8)entry[6] != '\0')) &&
                   (*(u8 *)((s64)entry + 0x31) == '\0')) {
                    (**(void (**)(s64 *, u64))(*entry + 0x18))(entry, *(u64 *)(list + 8));
                }
                remaining = remaining + -1;
                slot = slot + -3;
            } while (1 < remaining);
        }
    }
}

// 0x7100489c00 — Static init: empty guard body, returns &DAT_71052b6960
u8 *FUN_7100489c00()
{
    s32 acquired;

    if (((DAT_71052b6950 & 1) == 0) && (acquired = __cxa_guard_acquire(&DAT_71052b6950), acquired != 0)) {
        __cxa_guard_release(&DAT_71052b6950);
    }
    return &DAT_71052b6960;
}

// 0x7100489e60 — Static init: stores module vtable pointer, returns &DAT_71052b5a08
u64 *FUN_7100489e60()
{
    s32 acquired;

    if (((DAT_71052b5f18 & 1) == 0) && (acquired = __cxa_guard_acquire(&DAT_71052b5f18), acquired != 0)) {
        DAT_71052b5a08 = (u64)&PTR__Module_7104f61810;
        __cxa_guard_release(&DAT_71052b5f18);
    }
    return &DAT_71052b5a08;
}

// 0x710048a790 — Static init: stores {-1, 0} sentinel pair, returns pointer
u64 *FUN_710048a790()
{
    s32 acquired;

    if (((DAT_71052b6218 & 1) == 0) && (acquired = __cxa_guard_acquire(&DAT_71052b6218), acquired != 0)) {
        DAT_71052b5da0 = 0xffffffffffffffff;
        DAT_71052b5da8 = 0;
        __cxa_guard_release(&DAT_71052b6218);
    }
    return &DAT_71052b5da0;
}

// 0x710049d9d0 — Calls vtable[0x280], returns whether lower 40 bits are nonzero
u8 FUN_710049d9d0(s64 *this_ptr)
{
    u64 result;

    result = (**(u64 (**)())(*this_ptr + 0x280))();
    return (result & 0xffffffffff) != 0;
}

// 0x710049f550 — Chains: deref +0x10→+0x38, call vtable[0x10](0), then vtable[0x78], return NOT(bit0)
u32 FUN_710049f550(s64 this_ptr)
{
    u32 result;
    s64 *inner;

    inner = *(s64 **)(*(s64 *)(this_ptr + 0x10) + 0x38);
    inner = (s64 *)(**(u64 (**)(s64 *, s32))(*inner + 0x10))(inner, 0);
    result = (**(u32 (**)())(*inner + 0x78))();
    return ~result & 1;
}

// 0x710049f598 — Calls vtable[0x20] on sub-object at +0x8, with 40-bit masked param, returns != -1
u8 FUN_710049f598(s64 this_ptr, u64 param_2, u64 hash40)
{
    s32 index;

    index = (**(s32 (**)(s64 *, u64))(**(s64 **)(this_ptr + 8) + 0x20))
                (*(s64 **)(this_ptr + 8), hash40 & 0xffffffffff);
    return index != -1;
}

// 0x710049f630 — Looks up entry by index in array at sub+0x88, calls vtable[0x60] if active
u64 FUN_710049f630(s64 this_ptr, u64 index)
{
    s32 acquired;
    u64 result;
    s64 sub;

    sub = *(s64 *)(this_ptr + 0x18);
    if (sub == 0) {
        if (((DAT_71052b6a38 & 1) == 0) && (acquired = __cxa_guard_acquire(&DAT_71052b6a38), acquired != 0)) {
            DAT_71052b6a40 = 0;
            DAT_71052b6a48 = 0;
            __cxa_guard_release(&DAT_71052b6a38);
        }
        return DAT_71052b6a40;
    }
    if (((index & 0xffffffff) < (u64)((*(s64 *)(sub + 0x90) - *(s64 *)(sub + 0x88)) >> 3)) &&
       (sub = *(s64 *)(*(s64 *)(sub + 0x88) + (s64)(index & 0xffffffff) * 8),
       *(u8 *)(sub + 0x88) != '\0')) {
        result = (**(u64 (**)())(**(s64 **)(sub + 0x70) + 0x60))();
        return result;
    }
    return 0;
}
