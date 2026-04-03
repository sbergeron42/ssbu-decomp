#include "types.h"

// MEDIUM-tier FUN_* functions — mixed 0x7101 range, batch d5-007
// Pool-d worker: auto-generated from Ghidra decompilation
// Includes: sv_animcmd/sv_kinetic_energy wrappers, abort thunks, vtable dispatchers

// NOTE: FUN_7101fff758 carries a value in AArch64 register X10 that cannot be
// represented in standard C++. Initialized to 0 here; will not verify.

// ---- External declarations -----------------------------------------------

[[noreturn]] extern "C" void abort();

extern "C" void FUN_7101502850(u64);
extern "C" void FUN_7101755480(u64, s32);

extern "C" u64 *DAT_71052c2760;
extern "C" u64 *DAT_71052c40f8;

struct lua_State;

namespace app {
    namespace sv_kinetic_energy {
        void set_motion_energy_update_flag(lua_State *);
    }
    namespace sv_animcmd {
        void PLAY_ITEM_EMPTY_SE(lua_State *);
        void THROW_ITEM(lua_State *);
        void THROW_ITEM_REFLET(lua_State *);
        void THROW_ITEM_OFFSET(lua_State *);
        void THROW_ITEM_OFFSET_arg4(lua_State *);
    }
}

// ---- sv_kinetic_energy / sv_animcmd wrappers -----------------------------

// 0x7101fa3060
u32 FUN_7101fa3060(lua_State *param_1) { app::sv_kinetic_energy::set_motion_energy_update_flag(param_1); return 0; }

// 0x7101fc43d0
u32 FUN_7101fc43d0(lua_State *param_1) { app::sv_animcmd::PLAY_ITEM_EMPTY_SE(param_1); return 0; }

// 0x7101fc7280
u32 FUN_7101fc7280(lua_State *param_1) { app::sv_animcmd::THROW_ITEM(param_1); return 0; }

// 0x7101fc73a0
u32 FUN_7101fc73a0(lua_State *param_1) { app::sv_animcmd::THROW_ITEM_REFLET(param_1); return 0; }

// 0x7101fc73c0
u32 FUN_7101fc73c0(lua_State *param_1) { app::sv_animcmd::THROW_ITEM_OFFSET(param_1); return 0; }

// 0x7101fc73e0
u32 FUN_7101fc73e0(lua_State *param_1) { app::sv_animcmd::THROW_ITEM_OFFSET_arg4(param_1); return 0; }

// ---- abort() thunks -------------------------------------------------------

// 0x710147d138
[[noreturn]] void FUN_710147d138(void) { abort(); }

// 0x710154a078
[[noreturn]] void FUN_710154a078(void) { abort(); }

// 0x7101486d10
[[noreturn]] void FUN_7101486d10(void) { abort(); }

// 0x7101851e28
[[noreturn]] void FUN_7101851e28(void) { abort(); }

// 0x7101851f9c
[[noreturn]] void FUN_7101851f9c(void) { abort(); }

// 0x710185258c
[[noreturn]] void FUN_710185258c(void) { abort(); }

// 0x7101b32944
[[noreturn]] void FUN_7101b32944(void) { abort(); }

// 0x7101b3385c
[[noreturn]] void FUN_7101b3385c(void) { abort(); }

// 0x7101b33aa0
[[noreturn]] void FUN_7101b33aa0(void) { abort(); }

// 0x7101ba3e14
[[noreturn]] void FUN_7101ba3e14(void) { abort(); }

// 0x7101bfe5b0
[[noreturn]] void FUN_7101bfe5b0(void) { abort(); }

// 0x7101e66128
[[noreturn]] void FUN_7101e66128(void) { abort(); }

// ---- Simple vtable dispatchers --------------------------------------------

// 0x710151a920 — vtable call at *param_2+0x10, no pass-through of param_2
u64 FUN_710151a920(u64 param_1, s64 *param_2)
{
    (*(void (**)())(*param_2 + 0x10))();
    return 0;
}

// 0x7101f90b2c — vtable call at *param_1+0x30, no arg
u64 FUN_7101f90b2c(s64 *param_1)
{
    (*(void (**)())(*param_1 + 0x30))();
    return 0;
}

// 0x7101f9510c — vtable call at *param_1+0x30, no arg (same pattern)
u64 FUN_7101f9510c(s64 *param_1)
{
    (*(void (**)())(*param_1 + 0x30))();
    return 0;
}

// 0x7101fe7360 — vtable call at *param_1+0x6a0, passes param_1
u64 FUN_7101fe7360(s64 *param_1)
{
    (*(void(**)(s64 *))(*param_1 + 0x6a0))(param_1);
    return 0;
}

// 0x7101fea6b0 — vtable call at *param_1+0x7a8, passes param_1
u64 FUN_7101fea6b0(s64 *param_1)
{
    (*(void(**)(s64 *))(*param_1 + 0x7a8))(param_1);
    return 0;
}

// 0x7101ff5380 — vtable call at *param_1+0x238, passes param_1
u64 FUN_7101ff5380(s64 *param_1)
{
    (*(void(**)(s64 *))(*param_1 + 0x238))(param_1);
    return 0;
}

// ---- in_x10 wrapper -------------------------------------------------------

// 0x7101fff758 — store in_x10 at param_2+0x10, vtable call +0xa0
u64 FUN_7101fff758(s64 *param_1, s64 param_2)
{
    u64 in_x10 = 0;
    *(u64 *)(param_2 + 0x10) = in_x10;
    (*(void(**)(s64 *))(*param_1 + 0xa0))(param_1);
    return 0;
}

// ---- Misc wrappers --------------------------------------------------------

// 0x71014d45b0 — clear field +0x14, dispatch via DAT_71052c2760
void FUN_71014d45b0(s64 param_1)
{
    *(u32 *)(param_1 + 0x14) = 0;
    FUN_7101502850(*DAT_71052c2760);
}

// 0x710151f960 — clear field +0x14, dispatch via DAT_71052c2760 (same pattern)
void FUN_710151f960(s64 param_1)
{
    *(u32 *)(param_1 + 0x14) = 0;
    FUN_7101502850(*DAT_71052c2760);
}

// 0x7101755450 — call FUN_7101755480 with global ptr and 0, return 1
u64 FUN_7101755450(void)
{
    FUN_7101755480(*DAT_71052c40f8, 0);
    return 1;
}

// 0x710164baf0 — double-deref: obj=*(param_2+0xd0), vtable call obj[0]+0xc0
u64 FUN_710164baf0(u64 param_1, s64 param_2)
{
    s64 *obj = *(s64 **)(param_2 + 0xd0);
    (*(void (**)())(*(s64 *)obj + 0xc0))();
    return 1;
}

// 0x710165a960 — double-deref: obj=*(param_2+0xe8), vtable +0xa0 with two consts
u32 FUN_710165a960(u64 param_1, s64 param_2)
{
    s64 *obj = *(s64 **)(param_2 + 0xe8);
    (*(void(**)(s64 *, u32, u32))(*(s64 *)obj + 0xa0))(obj, 0x50000000, 0x10000000);
    return 0;
}

// 0x710165c960 — double-deref: vtable +0x110 return == 0x41
bool FUN_710165c960(u64 param_1, s64 param_2)
{
    s32 iVar1 = (*(s32 (**)())(*(s64 *)(*(s64 *)(param_2 + 0xd8) + 0x110)))();
    return iVar1 == 0x41;
}

// 0x710165e050 — same as 710165a960
u32 FUN_710165e050(u64 param_1, s64 param_2)
{
    s64 *obj = *(s64 **)(param_2 + 0xe8);
    (*(void(**)(s64 *, u32, u32))(*(s64 *)obj + 0xa0))(obj, 0x50000000, 0x10000000);
    return 0;
}

// 0x7101660df0 — same as 710165c960
bool FUN_7101660df0(u64 param_1, s64 param_2)
{
    s32 iVar1 = (*(s32 (**)())(*(s64 *)(*(s64 *)(param_2 + 0xd8) + 0x110)))();
    return iVar1 == 0x41;
}

// 0x710166ec80 — double-deref: vtable +0x110 return == 7
bool FUN_710166ec80(u64 param_1, s64 param_2)
{
    s32 iVar1 = (*(s32 (**)())(*(s64 *)(*(s64 *)(param_2 + 0xd8) + 0x110)))();
    return iVar1 == 7;
}

// 0x7101674ba0 — same as 710165a960
u32 FUN_7101674ba0(u64 param_1, s64 param_2)
{
    s64 *obj = *(s64 **)(param_2 + 0xe8);
    (*(void(**)(s64 *, u32, u32))(*(s64 *)obj + 0xa0))(obj, 0x50000000, 0x10000000);
    return 0;
}

// 0x710167b2f0 — double-deref: vtable +0x98 with const 0x10000012, return == 0
bool FUN_710167b2f0(u64 param_1, s64 param_2)
{
    s64 *obj = *(s64 **)(param_2 + 0xe8);
    s32 iVar1 = (*(s32(**)(s64 *, u32))(*(s64 *)obj + 0x98))(obj, 0x10000012);
    return iVar1 == 0;
}
