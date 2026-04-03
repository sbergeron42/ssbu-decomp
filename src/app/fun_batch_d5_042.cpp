#include "types.h"

// MEDIUM-tier FUN_* functions — mixed batch d5-042
// Pool-d worker: auto-generated from Ghidra decompilation
// 272-byte (0x110) mixed group + 176-byte (0xB0) mixed group + 560-byte (0x230) mixed group

// ---- External declarations -----------------------------------------------

[[noreturn]] extern "C" void abort();
extern "C" s32  __cxa_guard_acquire(s64 *);
extern "C" void __cxa_guard_release(s64 *);

struct lua_State;

namespace app {
    namespace sv_animcmd {
        void EFFECT_REMOVE_ATTR(lua_State *);
        void LAST_EFFECT_SET_DISABLE_SYSTEM_SLOW(lua_State *);
        void SCREEN_EFFECT_SLOW_WHOLE(lua_State *);
        void FT_START_ADJUST_MOTION_FRAME_arg1(lua_State *);
        void SLOW_OPPONENT(lua_State *);
        void EFFECT_OFF_KIND(lua_State *);
    }
}

// Global dispatch
extern "C" u64 *DAT_71052c2760;
extern void FUN_710150eaa0(u64);
extern void FUN_71015030c0(u64);

// PTR_ConstantZero guards (176B + 560B groups)
extern "C" u64 DAT_71052b6ef0;
extern "C" u64 DAT_71052b6f00;
extern "C" u64 DAT_71052b6f08;
extern "C" u8 *PTR_ConstantZero_71052a7a88;

extern "C" u64 DAT_71052b6fb0;
extern "C" u64 DAT_71052b6fc0;
extern "C" u64 DAT_71052b6fc8;
extern "C" u8 *PTR_ConstantZero_71052a7a80;

// Nested CXA guard series (176B)
extern "C" u64 DAT_7105323690;
extern "C" u64 DAT_7105323698;
extern "C" u64 DAT_7105323708;
extern "C" u64 DAT_7105323710;

// Float constant init (176B)
extern "C" u64 DAT_71052b79e0;
extern "C" u64 DAT_71052b7810;
extern "C" u64 DAT_71052b7818;
extern "C" u64 DAT_71052b7820;
extern "C" u64 DAT_71052b7828;
extern "C" u64 DAT_71052b7830;
extern "C" u64 DAT_71052b7840;
extern "C" u64 DAT_71052b7850;
extern "C" u32 DAT_71052b7858;
extern "C" u32 DAT_71052b785c;
extern "C" u32 DAT_71052b7864;
extern "C" u32 DAT_71052b786c;
extern "C" u64 DAT_71052b7870;
extern "C" u64 DAT_71052b7880;
extern "C" u32 DAT_71052b7888;
extern "C" u64 DAT_71052b7890;
extern "C" u64 DAT_71052b7898;
extern "C" u32 DAT_71052b78a0;
extern "C" u64 DAT_7104467ca0;
extern "C" u64 DAT_7104467ca8;

// g_team_param_init guard (560B)
extern "C" s64  g_team_param_init_guard;
extern "C" void global_param_init_sets_team_flag();
extern "C" void FUN_71000001c0(void *, void *, void *);
extern "C" void FUN_7101763de0();
extern "C" u8   DAT_71052c4180;
extern "C" u8   PTR_LOOP_7104f16000;
extern "C" u64  DAT_71052c45c0;

// ============================================================
// 272-byte (0x110) framed_vtable_call mixed group
// ============================================================

// ---- Abort thunks -----------------------------------------------------------

// 0x71005f1d8c
[[noreturn]] void FUN_71005f1d8c(void) { abort(); }
// 0x71007a92cc
[[noreturn]] void FUN_71007a92cc(void) { abort(); }
// 0x7100868bdc
[[noreturn]] void FUN_7100868bdc(void) { abort(); }
// 0x7100a8582c
[[noreturn]] void FUN_7100a8582c(void) { abort(); }
// 0x7100bef66c
[[noreturn]] void FUN_7100bef66c(void) { abort(); }
// 0x7100d43bfc
[[noreturn]] void FUN_7100d43bfc(void) { abort(); }
// 0x7100d4806c
[[noreturn]] void FUN_7100d4806c(void) { abort(); }
// 0x7100d48abc
[[noreturn]] void FUN_7100d48abc(void) { abort(); }
// 0x7100d55a4c
[[noreturn]] void FUN_7100d55a4c(void) { abort(); }
// 0x7100d7dcac
[[noreturn]] void FUN_7100d7dcac(void) { abort(); }
// 0x7100e68ddc
[[noreturn]] void FUN_7100e68ddc(void) { abort(); }
// 0x7100f1df6c
[[noreturn]] void FUN_7100f1df6c(void) { abort(); }
// 0x7100f9a29c
[[noreturn]] void FUN_7100f9a29c(void) { abort(); }
// 0x7100fc297c
[[noreturn]] void FUN_7100fc297c(void) { abort(); }
// 0x710112eb8c
[[noreturn]] void FUN_710112eb8c(void) { abort(); }
// 0x710133164c
[[noreturn]] void FUN_710133164c(void) { abort(); }

// ---- Vtable dispatcher ------------------------------------------------------

// 0x710049e3a0 — vtable+0x680, return high bit of *(u8*)(result+0x10)
u8 FUN_710049e3a0(s64 *p1)
{
    s64 lVar1 = (*(s64(**)())(*p1 + 0x680))();
    return *(u8*)(lVar1 + 0x10) >> 7;
}

// ---- Global-dispatch wrappers (via *DAT_71052c2760) -------------------------

// 0x71014d3920
void FUN_71014d3920(void) { FUN_710150eaa0(*DAT_71052c2760); }
// 0x71014d44a0
void FUN_71014d44a0(void) { FUN_71015030c0(*DAT_71052c2760); }
// 0x710151f5f0
void FUN_710151f5f0(void) { FUN_710150eaa0(*DAT_71052c2760); }
// 0x710151f850
void FUN_710151f850(void) { FUN_71015030c0(*DAT_71052c2760); }

// ---- lua_bind wrappers -------------------------------------------------------

// 0x7101fb4160
u32 FUN_7101fb4160(lua_State *p1)
{
    app::sv_animcmd::EFFECT_REMOVE_ATTR(p1);
    return 0;
}
// 0x7101fba1b0
u32 FUN_7101fba1b0(lua_State *p1)
{
    app::sv_animcmd::LAST_EFFECT_SET_DISABLE_SYSTEM_SLOW(p1);
    return 0;
}

// ---- in_x10 vtable wrappers -------------------------------------------------

// 0x7101fcc940 — in_x10 → p2+0x10, vtable call at *p1+0xa0
u64 FUN_7101fcc940(s64 *p1, s64 p2)
{
    u64 in_x10 = 0;
    *(u64*)(p2 + 0x10) = in_x10;
    (*(void(**)(s64*))(*p1 + 0xa0))(p1);
    return 0;
}
// 0x7101fe4960 — in_x10 → p2+0x10, vtable call at *p1+0x5e0
u64 FUN_7101fe4960(s64 *p1, s64 p2)
{
    u64 in_x10 = 0;
    *(u64*)(p2 + 0x10) = in_x10;
    (*(void(**)(s64*))(*p1 + 0x5e0))(p1);
    return 0;
}

// ============================================================
// 176-byte (0xB0) framed_vtable_call mixed group
// ============================================================

// ---- Abort thunk ------------------------------------------------------------

// 0x710083a2ec
[[noreturn]] void FUN_710083a2ec(void) { abort(); }

// ---- PTR_ConstantZero guard init --------------------------------------------

// 0x71003b01a0 — guard: DAT_71052b6ef0, data: DAT_71052b6f00/f08, src: PTR_ConstantZero_71052a7a88
u64 *FUN_71003b01a0(void)
{
    if (!(DAT_71052b6ef0 & 1)) {
        s32 iVar1 = __cxa_guard_acquire((s64*)&DAT_71052b6ef0);
        if (iVar1 != 0) {
            DAT_71052b6f08 = *(u64*)(PTR_ConstantZero_71052a7a88 + 8);
            DAT_71052b6f00 = *(u64*)PTR_ConstantZero_71052a7a88;
            __cxa_guard_release((s64*)&DAT_71052b6ef0);
        }
    }
    return &DAT_71052b6f00;
}

// ---- Complex float-constant CXA guard init ----------------------------------

// 0x710048a350 — guard: DAT_71052b79e0, init float table 0x71052b7810–0x78a0
u64 *FUN_710048a350(void)
{
    if (!(DAT_71052b79e0 & 1)) {
        s32 iVar1 = __cxa_guard_acquire((s64*)&DAT_71052b79e0);
        if (iVar1 != 0) {
            DAT_71052b7810 = 0x437f0000437f0000ULL;
            DAT_71052b7818 = 0x437f0000437f0000ULL;
            DAT_71052b7850 = 0x3f8000003f800000ULL;
            DAT_71052b7830 = 0x3f8000003f800000ULL;
            DAT_71052b7870 = 0x3f8000003f800000ULL;
            DAT_71052b7880 = 0x3f8000003f800000ULL;
            DAT_71052b7888 = 0x3f800000;
            DAT_71052b7820 = 0;
            DAT_71052b7828 = 0;
            DAT_71052b7840 = 0;
            DAT_71052b7858 = 0x3f800000;
            DAT_71052b786c = 0;
            DAT_71052b7864 = 0;
            DAT_71052b785c = 0;
            DAT_71052b78a0 = 0x40a00000;
            DAT_71052b7898 = DAT_7104467ca8;
            DAT_71052b7890 = DAT_7104467ca0;
            __cxa_guard_release((s64*)&DAT_71052b79e0);
        }
    }
    return &DAT_71052b7810;
}

// ---- Vtable call returning 0 ------------------------------------------------

// 0x710151a950 — vtable+0x10 on p2
u32 FUN_710151a950(u64 p1, s64 *p2)
{
    (*(void(**)(s64*))(*p2 + 0x10))(p2);
    return 0;
}

// ---- Nested CXA-guard (inner: DAT_7105323690/7698) --------------------------

// 0x71017f4b40 — outer: DAT_7105323708 → DAT_7105323710
u64 *FUN_71017f4b40(void)
{
    if (!(DAT_7105323708 & 1)) {
        s32 iVar1 = __cxa_guard_acquire((s64*)&DAT_7105323708);
        if (iVar1 != 0) {
            if (!(DAT_7105323690 & 1)) {
                s32 iVar2 = __cxa_guard_acquire((s64*)&DAT_7105323690);
                if (iVar2 != 0) {
                    DAT_7105323698 = 0;
                    __cxa_guard_release((s64*)&DAT_7105323690);
                }
            }
            DAT_7105323710 = (u64)&DAT_7105323698;
            __cxa_guard_release((s64*)&DAT_7105323708);
        }
    }
    return (u64*)&DAT_7105323710;
}

// ---- lua_bind wrappers -------------------------------------------------------

// 0x7101fbdbb0
u32 FUN_7101fbdbb0(lua_State *p1)
{
    app::sv_animcmd::SCREEN_EFFECT_SLOW_WHOLE(p1);
    return 0;
}
// 0x7101fc26f0
u32 FUN_7101fc26f0(lua_State *p1)
{
    app::sv_animcmd::FT_START_ADJUST_MOTION_FRAME_arg1(p1);
    return 0;
}

// ---- Vtable calls returning 0 -----------------------------------------------

// 0x7101fe7d00 — vtable+0x6c8
u64 FUN_7101fe7d00(s64 *p1)
{
    (*(void(**)(s64*))(*p1 + 0x6c8))(p1);
    return 0;
}
// 0x7101ff7130 — vtable+200 (0xc8)
u64 FUN_7101ff7130(s64 *p1)
{
    (*(void(**)(s64*))(*p1 + 200))(p1);
    return 0;
}

// ---- in_x10 vtable wrapper --------------------------------------------------

// 0x7101ffc820 — in_x10 → p2+0x10, vtable call at *p1+0x90
u64 FUN_7101ffc820(s64 *p1, s64 p2)
{
    u64 in_x10 = 0;
    *(u64*)(p2 + 0x10) = in_x10;
    (*(void(**)(s64*))(*p1 + 0x90))(p1);
    return 0;
}

// ============================================================
// 560-byte (0x230) framed_vtable_call mixed group
// ============================================================

// ---- PTR_ConstantZero guard init --------------------------------------------

// 0x71003b1f70 — guard: DAT_71052b6fb0, data: DAT_71052b6fc0/fc8, src: PTR_ConstantZero_71052a7a80
u64 *FUN_71003b1f70(void)
{
    if (!(DAT_71052b6fb0 & 1)) {
        s32 iVar1 = __cxa_guard_acquire((s64*)&DAT_71052b6fb0);
        if (iVar1 != 0) {
            DAT_71052b6fc8 = *(u64*)(PTR_ConstantZero_71052a7a80 + 8);
            DAT_71052b6fc0 = *(u64*)PTR_ConstantZero_71052a7a80;
            __cxa_guard_release((s64*)&DAT_71052b6fb0);
        }
    }
    return &DAT_71052b6fc0;
}

// ---- g_team_param_init guard ------------------------------------------------

// 0x7101388960 — g_team_param_init: init team params and register
u64 *FUN_7101388960(void)
{
    if (!(g_team_param_init_guard & 1)) {
        s32 iVar1 = __cxa_guard_acquire(&g_team_param_init_guard);
        if (iVar1 != 0) {
            global_param_init_sets_team_flag();
            FUN_71000001c0((void *)FUN_7101763de0, &DAT_71052c4180, &PTR_LOOP_7104f16000);
            __cxa_guard_release(&g_team_param_init_guard);
        }
    }
    return &DAT_71052c45c0;
}

// ---- lua_bind wrappers -------------------------------------------------------

// 0x7101fb91e0
u32 FUN_7101fb91e0(lua_State *p1)
{
    app::sv_animcmd::EFFECT_OFF_KIND(p1);
    return 0;
}
// 0x7101fc1e40
u32 FUN_7101fc1e40(lua_State *p1)
{
    app::sv_animcmd::SLOW_OPPONENT(p1);
    return 0;
}

// ---- Vtable call returning 0 ------------------------------------------------

// 0x7101ff71e0 — vtable+0xd0
u64 FUN_7101ff71e0(s64 *p1)
{
    (*(void(**)(s64*))(*p1 + 0xd0))(p1);
    return 0;
}

// ---- Abort thunks -----------------------------------------------------------

// 0x71003bca0c
[[noreturn]] void FUN_71003bca0c(void) { abort(); }
// 0x71005c9b8c
[[noreturn]] void FUN_71005c9b8c(void) { abort(); }
// 0x7100c7d1d4
[[noreturn]] void FUN_7100c7d1d4(void) { abort(); }
// 0x7100e36084
[[noreturn]] void FUN_7100e36084(void) { abort(); }
// 0x7100e36a5c
[[noreturn]] void FUN_7100e36a5c(void) { abort(); }
// 0x7100e917f4
[[noreturn]] void FUN_7100e917f4(void) { abort(); }
// 0x7100fe4514
[[noreturn]] void FUN_7100fe4514(void) { abort(); }
// 0x71010125b4
[[noreturn]] void FUN_71010125b4(void) { abort(); }
// 0x710106a1ec
[[noreturn]] void FUN_710106a1ec(void) { abort(); }
// 0x710106a41c
[[noreturn]] void FUN_710106a41c(void) { abort(); }
// 0x71010e0f94
[[noreturn]] void FUN_71010e0f94(void) { abort(); }
// 0x71010fc544
[[noreturn]] void FUN_71010fc544(void) { abort(); }
// 0x710117a454
[[noreturn]] void FUN_710117a454(void) { abort(); }
// 0x71011e2c74
[[noreturn]] void FUN_71011e2c74(void) { abort(); }
// 0x7101202e94
[[noreturn]] void FUN_7101202e94(void) { abort(); }
// 0x7101234794
[[noreturn]] void FUN_7101234794(void) { abort(); }
// 0x71012e61d4
[[noreturn]] void FUN_71012e61d4(void) { abort(); }
// 0x7101b20ec0
[[noreturn]] void FUN_7101b20ec0(void) { abort(); }
