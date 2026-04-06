#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7100 address range, batch d4-005
// Pool-d worker: auto-generated from Ghidra decompilation
// Includes: vtable dispatchers, scene-registration initializers

// ---- External declarations -----------------------------------------------

[[noreturn]] extern "C" void abort();
extern "C" s32  __cxa_guard_acquire(u64 *);
extern "C" void __cxa_guard_release(u64 *);

// Float data
extern float DAT_7104471ef8;

// Scene vtable pointers (address-of used for assignment)
extern u8 PTR_PTR_LAB_7104f75410;
extern u8 PTR_PTR_LAB_71050a32c0;
extern u8 PTR_PTR_LAB_71050b5c70;
extern u8 PTR_PTR_LAB_71050b5d48;
extern u8 PTR_PTR_LAB_71050b5e20;
extern u8 PTR_PTR_LAB_71050b5ef8;
extern u8 PTR_PTR_LAB_71050b6290;
extern u8 PTR_PTR_LAB_71050b68a0;

// Guard variables
extern u64 DAT_71052b8330;
extern u64 DAT_7105323960;
extern u64 DAT_7105327448;
extern u64 DAT_7105327478;
extern u64 DAT_71053274a8;
extern u64 DAT_71053274d8;
extern u64 DAT_71053275a0;
extern u64 DAT_71053277b8;

// Scene data fields (string name, zero fields, vtable)
extern u64 DAT_71052b8308;
extern const char *DAT_71052b8310;
extern u64 DAT_71052b8318;
extern u64 DAT_71052b8320;
extern u64 DAT_71052b8328;

extern u64 DAT_7105323938;
extern const char *DAT_7105323940;
extern u64 DAT_7105323948;
extern u64 DAT_7105323950;
extern u64 DAT_7105323958;

extern u64 DAT_7105327420;
extern const char *DAT_7105327428;
extern u64 DAT_7105327430;
extern u64 DAT_7105327438;
extern u64 DAT_7105327440;

extern u64 DAT_7105327450;
extern const char *DAT_7105327458;
extern u64 DAT_7105327460;
extern u64 DAT_7105327468;
extern u64 DAT_7105327470;

extern u64 DAT_7105327480;
extern const char *DAT_7105327488;
extern u64 DAT_7105327490;
extern u64 DAT_7105327498;
extern u64 DAT_71053274a0;

extern u64 DAT_71053274b0;
extern const char *DAT_71053274b8;
extern u64 DAT_71053274c0;
extern u64 DAT_71053274c8;
extern u64 DAT_71053274d0;

extern u64 DAT_7105327578;
extern const char *DAT_7105327580;
extern u64 DAT_7105327588;
extern u64 DAT_7105327590;
extern u64 DAT_7105327598;

extern const char *DAT_71053278c8;
extern u64 DAT_71053278d0;
extern u64 DAT_71053278d8;
extern u64 DAT_71053278e0;
// 0x71003ee260 — vtable dispatch: call vtable[0x160] with 4 args, forward return
u32 FUN_71003ee260(s64 param_1)
{
    s64 *module;

    module = *(s64 **)(*(s64 *)(param_1 + 8) + 0xd0);
    return (u32)(**(u32 (**)(s64 *, u64, u64, s32))(*module + 0x160))(module, 0, *(u64 *)(param_1 + 0x10), 1);
}

// 0x71003f7fa0 — vtable dispatch: call vtable[0x50], return |val| < threshold
u8 FUN_71003f7fa0(s64 *param_1)
{
    float value;

    value = (**(float (**)())(*param_1 + 0x50))();
    return __builtin_fabsf(value) < DAT_7104471ef8;
}

// 0x71003f8020 — vtable dispatch: call vtable[0x60], return |val| < threshold
u8 FUN_71003f8020(s64 *param_1)
{
    float value;

    value = (**(float (**)())(*param_1 + 0x60))();
    return __builtin_fabsf(value) < DAT_7104471ef8;
}

// 0x71003f8730 — vtable dispatch: call vtable[0x260], return NOT(bit0)
u32 FUN_71003f8730(s64 *param_1)
{
    u32 result;

    result = (**(u32 (**)())(*param_1 + 0x260))();
    return ~result & 1;
}

// 0x71003fe250 — vtable call if bit0 set, then write bit0 of param_2 to +0x386
void FUN_71003fe250(s64 *param_1, u8 param_2)
{
    if ((param_2 & 1) != 0) {
        (**(void (**)(s64 *))(*param_1 + 0x68))(param_1);
    }
    *(u8 *)((s64)param_1 + 0x386) = param_2 & 1;
}

// 0x7100405d60 — vtable dispatch: call vtable[0x28], check if motion type is in ground range
u32 FUN_7100405d60(s64 *param_1)
{
    s32 motion_type;

    motion_type = (**(s32 (**)())(*param_1 + 0x28))();
    if (motion_type - 7U < 0x17) {
        return 0x500003U >> (u64)(motion_type - 7U & 0x1f) & 1;
    }
    return 0;
}

// 0x7100405db0 — vtable dispatch: call vtable[0x28], check if 0x10 or in range 1-6
u8 FUN_7100405db0(s64 *param_1)
{
    s32 motion_type;

    motion_type = (**(s32 (**)())(*param_1 + 0x28))();
    return motion_type == 0x10 || motion_type - 1U < 6;
}

// 0x71004074b0 — vtable dispatch: call vtable[0x168] of nested ptr at param_2+0x40, return == 2
u8 FUN_71004074b0(u64 param_1, s64 param_2)
{
    s32 result;

    result = (**(s32 (**)())(**(s64 **)(param_2 + 0x40) + 0x168))();
    return result == 2;
}

// 0x7100407e10 — scene init: IngameCallSequenceScene registration
void FUN_7100407e10()
{
    s32 acquired;

    DAT_71052b8308 = 0;
    DAT_71052b8310 = "IngameCallSequenceScene";
    if (((DAT_71052b8330 & 1) == 0) && (acquired = __cxa_guard_acquire(&DAT_71052b8330), acquired != 0)) {
        __cxa_guard_release(&DAT_71052b8330);
    }
    DAT_71052b8320 = 0;
    DAT_71052b8328 = 0;
    DAT_71052b8318 = (u64)&PTR_PTR_LAB_7104f75410;
}

// 0x710041dd90 — scene init: MeleeRuleScene registration
void FUN_710041dd90()
{
    s32 acquired;

    DAT_7105323938 = 0;
    DAT_7105323940 = "MeleeRuleScene";
    if (((DAT_7105323960 & 1) == 0) && (acquired = __cxa_guard_acquire(&DAT_7105323960), acquired != 0)) {
        __cxa_guard_release(&DAT_7105323960);
    }
    DAT_7105323950 = 0;
    DAT_7105323958 = 0;
    DAT_7105323948 = (u64)&PTR_PTR_LAB_71050a32c0;
}

// 0x7100420ed0 — scene init: CollectionAnniversaryScene registration
void FUN_7100420ed0()
{
    s32 acquired;

    DAT_7105327420 = 0;
    DAT_7105327428 = "CollectionAnniversaryScene";
    if (((DAT_7105327448 & 1) == 0) && (acquired = __cxa_guard_acquire(&DAT_7105327448), acquired != 0)) {
        __cxa_guard_release(&DAT_7105327448);
    }
    DAT_7105327438 = 0;
    DAT_7105327440 = 0;
    DAT_7105327430 = (u64)&PTR_PTR_LAB_71050b5c70;
}

// 0x7100420f40 — scene init: CollectionCardScene registration
void FUN_7100420f40()
{
    s32 acquired;

    DAT_7105327450 = 0;
    DAT_7105327458 = "CollectionCardScene";
    if (((DAT_7105327478 & 1) == 0) && (acquired = __cxa_guard_acquire(&DAT_7105327478), acquired != 0)) {
        __cxa_guard_release(&DAT_7105327478);
    }
    DAT_7105327468 = 0;
    DAT_7105327470 = 0;
    DAT_7105327460 = (u64)&PTR_PTR_LAB_71050b5d48;
}

// 0x7100420fb0 — scene init: CollectionCountScene registration
void FUN_7100420fb0()
{
    s32 acquired;

    DAT_7105327480 = 0;
    DAT_7105327488 = "CollectionCountScene";
    if (((DAT_71053274a8 & 1) == 0) && (acquired = __cxa_guard_acquire(&DAT_71053274a8), acquired != 0)) {
        __cxa_guard_release(&DAT_71053274a8);
    }
    DAT_7105327498 = 0;
    DAT_71053274a0 = 0;
    DAT_7105327490 = (u64)&PTR_PTR_LAB_71050b5e20;
}

// 0x7100421020 — scene init: CollectionFighterScene registration
void FUN_7100421020()
{
    s32 acquired;

    DAT_71053274b0 = 0;
    DAT_71053274b8 = "CollectionFighterScene";
    if (((DAT_71053274d8 & 1) == 0) && (acquired = __cxa_guard_acquire(&DAT_71053274d8), acquired != 0)) {
        __cxa_guard_release(&DAT_71053274d8);
    }
    DAT_71053274c8 = 0;
    DAT_71053274d0 = 0;
    DAT_71053274c0 = (u64)&PTR_PTR_LAB_71050b5ef8;
}

// 0x7100421210 — scene init: CollectionPlayingScene registration
void FUN_7100421210()
{
    s32 acquired;

    DAT_7105327578 = 0;
    DAT_7105327580 = "CollectionPlayingScene";
    if (((DAT_71053275a0 & 1) == 0) && (acquired = __cxa_guard_acquire(&DAT_71053275a0), acquired != 0)) {
        __cxa_guard_release(&DAT_71053275a0);
    }
    DAT_7105327590 = 0;
    DAT_7105327598 = 0;
    DAT_7105327588 = (u64)&PTR_PTR_LAB_71050b6290;
}

// 0x7100421d10 — scene init: HomeRunContestScene registration
void FUN_7100421d10()
{
    s32 acquired;

    DAT_71053278c8 = "HomeRunContestScene";
    if (((DAT_71053277b8 & 1) == 0) && (acquired = __cxa_guard_acquire(&DAT_71053277b8), acquired != 0)) {
        __cxa_guard_release(&DAT_71053277b8);
    }
    DAT_71053278d8 = 0;
    DAT_71053278e0 = 0;
    DAT_71053278d0 = (u64)&PTR_PTR_LAB_71050b68a0;
}
