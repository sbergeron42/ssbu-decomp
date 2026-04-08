#include "types.h"
#include "app/BattleObjectModuleAccessor.h"
#include "app/modules/StatusModule.h"
#include "app/modules/WorkModule.h"

// MEDIUM-tier FUN_* functions -- 0x7103 address range, batch d-004
// Rewritten from Ghidra paste with meaningful names and struct field access

using app::BattleObjectModuleAccessor;
using app::StatusModule;
using app::WorkModule;

// ---- External declarations -----------------------------------------------

extern "C" {
    int  __cxa_guard_acquire(u64*);
    void __cxa_guard_release(u64*);
}

extern void FUN_710392e590(void*);
extern void FUN_71033137f0(u64, u32);

// External data
extern u8 DAT_710532e8d0[];

// FUN_710379d480 guard data
extern u8 DAT_710593abf8[];
extern u8 DAT_710593aa98[];
extern u8 DAT_710593aaa0[];
extern u8 DAT_710593aaa8[];
extern u8 DAT_710593aab0[];
extern u8 DAT_710593ac00[];

// FUN_710379dc50 / FUN_71037a1170 shared guard data
extern u8 DAT_710593aa20[];
extern u8 DAT_710593aa28[];
extern u8 DAT_710593a9e0[];
extern u8 DAT_710593a9e8[];
extern u8 DAT_710593aa30[];
extern u8 DAT_710593aa38[];

// FUN_71037a1170 guard data
extern u8 DAT_710593aa00[];
extern u8 DAT_710593aa08[];
extern u8 DAT_710593aa10[];
extern u8 DAT_710593aa18[];

// ---- Helper: extract accessor from lua context ----------------------------
// +0x20 [derived: all lua_bind_impl (.dynsym) dispatchers extract BattleObjectModuleAccessor* from lua context at offset 0x20]
#define ACC(p) reinterpret_cast<BattleObjectModuleAccessor*>(*(s64*)((p) + 0x20))

// ---- Functions ---------------------------------------------------------------

// 0x710395f890 -- no-op
__attribute__((optnone))
void FUN_710395f890(void)
{
    return;
}

// 0x71038f9be4 -- wrapper: FUN_710392e590(param_2), return 0
u64 FUN_71038f9be4(u64 param_1, u64 param_2)
{
    FUN_710392e590((void*)param_2);
    return 0;
}

// 0x71031d0660 -- vtable dispatch at 0x20, return 1
// +0x20 [inferred: vtable slot 4, unknown virtual method]
u64 FUN_71031d0660(s64 *obj)
{
    (*(void(*)())(*(s64 *)(*obj + 0x20)))();
    return 1;
}

// 0x710336e170 -- call FUN_71033137f0 via DAT_710532e8d0+8, return 0
u32 FUN_710336e170(void)
{
    FUN_71033137f0(*(u64*)(DAT_710532e8d0 + 8), 0);
    return 0;
}

// 0x71034d3d70 -- StatusModule::StatusKind() == 0
// [derived: acc+0x40 = status_module (.dynsym), vtable+0x110 = StatusKind (StatusModule.h)]
u8 FUN_71034d3d70(u64 param_1, s64 param_2)
{
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
    auto* acc = ACC(param_2);
    auto* status_mod = static_cast<StatusModule*>(acc->status_module);
    s32 status_kind = status_mod->vtbl->StatusKind(status_mod);
    return (u8)(status_kind == 0);
}

// 0x7103791bb0 -- vtable dispatch at 0x230, return 1
// +0x230 [inferred: vtable slot 0x46, unknown virtual method]
u64 FUN_7103791bb0(s64 *obj)
{
    (*(void(*)())(*(s64 *)(*obj + 0x230)))();
    return 1;
}

// 0x710379d480 -- static init: triple-nested guard, returns &DAT_710593ac00
u64 *FUN_710379d480(void)
{
    s32 acquired;

    if (((*(u64*)DAT_710593abf8 & 1) == 0) &&
        (acquired = __cxa_guard_acquire((u64*)DAT_710593abf8), acquired != 0)) {
        if (((*(u64*)DAT_710593aa98 & 1) == 0) &&
            (acquired = __cxa_guard_acquire((u64*)DAT_710593aa98), acquired != 0)) {
            if (((*(u64*)DAT_710593aaa0 & 1) == 0) &&
                (acquired = __cxa_guard_acquire((u64*)DAT_710593aaa0), acquired != 0)) {
                *(u64*)DAT_710593aaa8 = 0;
                __cxa_guard_release((u64*)DAT_710593aaa0);
            }
            *(u8**)DAT_710593aab0 = DAT_710593aaa8;
            __cxa_guard_release((u64*)DAT_710593aa98);
        }
        *(u8**)DAT_710593ac00 = DAT_710593aab0;
        __cxa_guard_release((u64*)DAT_710593abf8);
    }
    return (u64*)DAT_710593ac00;
}

// 0x710379dc50 -- static init: triple-nested guard, returns &DAT_710593aa38
u64 *FUN_710379dc50(void)
{
    s32 acquired;

    if (((*(u64*)DAT_710593aa20 & 1) == 0) &&
        (acquired = __cxa_guard_acquire((u64*)DAT_710593aa20), acquired != 0)) {
        if (((*(u64*)DAT_710593aa28 & 1) == 0) &&
            (acquired = __cxa_guard_acquire((u64*)DAT_710593aa28), acquired != 0)) {
            if (((*(u64*)DAT_710593a9e0 & 1) == 0) &&
                (acquired = __cxa_guard_acquire((u64*)DAT_710593a9e0), acquired != 0)) {
                *(u64*)DAT_710593a9e8 = 0;
                __cxa_guard_release((u64*)DAT_710593a9e0);
            }
            *(u8**)DAT_710593aa30 = DAT_710593a9e8;
            __cxa_guard_release((u64*)DAT_710593aa28);
        }
        *(u8**)DAT_710593aa38 = DAT_710593aa30;
        __cxa_guard_release((u64*)DAT_710593aa20);
    }
    return (u64*)DAT_710593aa38;
}

// 0x71037a0060 -- vtable dispatch at 0x230, return 1
// +0x230 [inferred: vtable slot 0x46, same as FUN_7103791bb0]
u64 FUN_71037a0060(s64 *obj)
{
    (*(void(*)())(*(s64 *)(*obj + 0x230)))();
    return 1;
}

// 0x71037a1170 -- static init: triple-nested guard (shares inner with dc50), returns &DAT_710593aa18
u64 *FUN_71037a1170(void)
{
    s32 acquired;

    if (((*(u64*)DAT_710593aa00 & 1) == 0) &&
        (acquired = __cxa_guard_acquire((u64*)DAT_710593aa00), acquired != 0)) {
        if (((*(u64*)DAT_710593aa08 & 1) == 0) &&
            (acquired = __cxa_guard_acquire((u64*)DAT_710593aa08), acquired != 0)) {
            if (((*(u64*)DAT_710593a9e0 & 1) == 0) &&
                (acquired = __cxa_guard_acquire((u64*)DAT_710593a9e0), acquired != 0)) {
                *(u64*)DAT_710593a9e8 = 0;
                __cxa_guard_release((u64*)DAT_710593a9e0);
            }
            *(u8**)DAT_710593aa10 = DAT_710593a9e8;
            __cxa_guard_release((u64*)DAT_710593aa08);
        }
        *(u8**)DAT_710593aa18 = DAT_710593aa10;
        __cxa_guard_release((u64*)DAT_710593aa00);
    }
    return (u64*)DAT_710593aa18;
}

// 0x71033c86a0 -- !WorkModule::is_flag(0x20000006)
// [derived: acc+0x50 = work_module (.dynsym), vtable+0x108 = is_flag (WorkModule.h)]
u64 FUN_71033c86a0(u64 param_1, s64 param_2)
{
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
    auto* acc = ACC(param_2);
    auto* work_mod = static_cast<WorkModule*>(acc->work_module);
    // Use u32-typed call to preserve 32-bit register width for ~result & 1
    u32 result = ((u32(*)(WorkModule*, u32))work_mod->_vt[0x108/8])(work_mod, 0x20000006);
    return ~result & 1;
}

// 0x71031cfe40 -- vtable dispatch at 0x20, return 1
// +0x20 [inferred: vtable slot 4, unknown virtual method]
u64 FUN_71031cfe40(s64 *obj)
{
    (*(void(*)())(*(s64 *)(*obj + 0x20)))();
    return 1;
}
