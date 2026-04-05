#include "types.h"
#include "app/BattleObjectModuleAccessor.h"

// MEDIUM-tier FUN_* functions -- 0x71033-0x71035 address range, batch d-016
// Rewritten from Ghidra paste to use BattleObjectModuleAccessor struct fields
// Pattern: lua_bind-style functions where param_2+0x20 holds accessor pointer

using app::BattleObjectModuleAccessor;

// ---- External declarations -----------------------------------------------

extern "C" [[noreturn]] void FUN_71039c20a0();  // abort

extern void  FUN_71032e5480(u64);
extern void  FUN_71032e47c0(u64, u32, u32, u32, u32, u32);
extern void  FUN_710347cff0(u64);
extern void  FUN_710348cc70(u64);

// External data
extern s64 DAT_710532e7c8;

// ---- Helper: extract accessor from lua context param_2 --------------------
// param_2+0x20 holds a BattleObjectModuleAccessor*
#define ACC(p) reinterpret_cast<BattleObjectModuleAccessor*>(*(s64*)((p) + 0x20))

// ---- Functions ---------------------------------------------------------------

// 0x7103344c38 -- abort wrapper (24 bytes)
[[noreturn]] void FUN_7103344c38(void) { FUN_71039c20a0(); }

// 0x71033625b8 -- vtable call at *param_1+8, return 0 (32 bytes)
u32 FUN_71033625b8(s64 *param_1)
{
    (*(void(*)())(*(s64*)(*param_1 + 8)))();
    return 0;
}

// 0x7103366970 -- wrapper: FUN_71032e5480(*(global+8)), return 0 (48 bytes)
u64 FUN_7103366970(void) { FUN_71032e5480(*(u64*)(DAT_710532e7c8 + 8)); return 0; }

// 0x7103366ac0 -- FUN_71032e47c0 with global+8 and constants, return 0 (64 bytes)
u64 FUN_7103366ac0(void)
{
    FUN_71032e47c0(*(u64*)(DAT_710532e7c8 + 8), 1, 0xfffffffe, 2, 0, 0);
    return 0;
}

// 0x71033c94c0 -- status_module vtable[0x110](this) != 5 (48 bytes)
u8 FUN_71033c94c0(u64 param_1, s64 param_2)
{
    auto* acc = ACC(param_2);
    s64* status_mod = static_cast<s64*>(acc->status_module);
    s32 status_kind = (*(s32(*)(s64*))(*(s64*)(*status_mod + 0x110)))(status_mod);
    return (u8)(status_kind != 5);
}

// 0x71033ec8c0 -- status_module vtable[0x110](), 2 < (result - 3) (64 bytes)
u8 FUN_71033ec8c0(u64 param_1, s64 param_2)
{
    auto* acc = ACC(param_2);
    s64* status_mod = static_cast<s64*>(acc->status_module);
    s32 status_kind = (*(s32(*)(s64*))(*(s64*)(*status_mod + 0x110)))(status_mod);
    return (u8)(2 < (u32)(status_kind - 3));
}

// 0x71033f34a0 -- status_module vtable[0x110](), (result - 1) < 6 (48 bytes)
u8 FUN_71033f34a0(u64 param_1, s64 param_2)
{
    auto* acc = ACC(param_2);
    s64* status_mod = static_cast<s64*>(acc->status_module);
    s32 status_kind = (*(s32(*)(s64*))(*(s64*)(*status_mod + 0x110)))(status_mod);
    return (u8)((u32)(status_kind - 1) < 6);
}

// 0x71033f34d0 -- status_module vtable[0x110](), 5 < (result - 1) (48 bytes)
u8 FUN_71033f34d0(u64 param_1, s64 param_2)
{
    auto* acc = ACC(param_2);
    s64* status_mod = static_cast<s64*>(acc->status_module);
    s32 status_kind = (*(s32(*)(s64*))(*(s64*)(*status_mod + 0x110)))(status_mod);
    return (u8)(5 < (u32)(status_kind - 1));
}

// 0x71033fbf00 -- status_module vtable[0x110]() == 1 (48 bytes)
u8 FUN_71033fbf00(u64 param_1, s64 param_2)
{
    auto* acc = ACC(param_2);
    s64* status_mod = static_cast<s64*>(acc->status_module);
    s32 status_kind = (*(s32(*)(s64*))(*(s64*)(*status_mod + 0x110)))(status_mod);
    return (u8)(status_kind == 1);
}

// 0x71034298d0 -- work_module vtable[0x110](ptr, 0x2000000e), return 1 (48 bytes)
u64 FUN_71034298d0(u64 param_1, s64 param_2)
{
    auto* acc = ACC(param_2);
    s64* work_mod = static_cast<s64*>(acc->work_module);
    (*(void(*)(s64*, u32))(*(s64*)(*work_mod + 0x110)))(work_mod, 0x2000000e);
    return 1;
}

// 0x71034336f0 -- status_module vtable[0x110]() != 1 (48 bytes)
u8 FUN_71034336f0(u64 param_1, s64 param_2)
{
    auto* acc = ACC(param_2);
    s64* status_mod = static_cast<s64*>(acc->status_module);
    s32 status_kind = (*(s32(*)(s64*))(*(s64*)(*status_mod + 0x110)))(status_mod);
    return (u8)(status_kind != 1);
}

// 0x710346c7f0 -- status_module vtable[0x110]() != 1 (48 bytes)
u8 FUN_710346c7f0(u64 param_1, s64 param_2)
{
    auto* acc = ACC(param_2);
    s64* status_mod = static_cast<s64*>(acc->status_module);
    s32 status_kind = (*(s32(*)(s64*))(*(s64*)(*status_mod + 0x110)))(status_mod);
    return (u8)(status_kind != 1);
}

// 0x710347d410 -- wrapper: FUN_710347cff0(param_2), return 0 (32 bytes)
u32 FUN_710347d410(u64 param_1, u64 param_2) { FUN_710347cff0(param_2); return 0; }

// 0x710348c480 -- status_module vtable[0x110]() != 1 (48 bytes)
u8 FUN_710348c480(u64 param_1, s64 param_2)
{
    auto* acc = ACC(param_2);
    s64* status_mod = static_cast<s64*>(acc->status_module);
    s32 status_kind = (*(s32(*)(s64*))(*(s64*)(*status_mod + 0x110)))(status_mod);
    return (u8)(status_kind != 1);
}

// 0x710348cc50 -- wrapper: FUN_710348cc70(param_2), return 1 (32 bytes)
u64 FUN_710348cc50(u64 param_1, u64 param_2) { FUN_710348cc70(param_2); return 1; }

// 0x710349d810 -- link_module vtable[0x78](ptr, 10), return ~result & 1 (48 bytes)
u64 FUN_710349d810(u64 param_1, s64 param_2)
{
    auto* acc = ACC(param_2);
    s64* link_mod = static_cast<s64*>(acc->link_module);
    u32 result = (*(u32(*)(s64*, s32))(*(s64*)(*link_mod + 0x78)))(link_mod, 10);
    return ~result & 1;
}

// 0x71034d3ae0 -- status_module vtable[0x110](), (result - 4) < 3 (48 bytes)
u8 FUN_71034d3ae0(u64 param_1, s64 param_2)
{
    auto* acc = ACC(param_2);
    s64* status_mod = static_cast<s64*>(acc->status_module);
    s32 status_kind = (*(s32(*)(s64*))(*(s64*)(*status_mod + 0x110)))(status_mod);
    return (u8)((u32)(status_kind - 4) < 3);
}

// 0x7103517a60 -- status_module vtable[0x110]() != 7 (64 bytes)
u8 FUN_7103517a60(u64 param_1, s64 param_2)
{
    auto* acc = ACC(param_2);
    s64* status_mod = static_cast<s64*>(acc->status_module);
    s32 status_kind = (*(s32(*)(s64*))(*(s64*)(*status_mod + 0x110)))(status_mod);
    return (u8)(status_kind != 7);
}

// 0x71035343b0 -- status_module vtable[0x110]() != 1 (48 bytes)
u8 FUN_71035343b0(u64 param_1, s64 param_2)
{
    auto* acc = ACC(param_2);
    s64* status_mod = static_cast<s64*>(acc->status_module);
    s32 status_kind = (*(s32(*)(s64*))(*(s64*)(*status_mod + 0x110)))(status_mod);
    return (u8)(status_kind != 1);
}
