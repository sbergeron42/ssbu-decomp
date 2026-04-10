#include "types.h"
#include "app/BattleObjectModuleAccessor.h"

// MEDIUM-tier FUN_* functions — mixed 0x7100-0x7101 range, batch d5-010
// Pool-d worker: auto-generated from Ghidra decompilation
// Includes: abort() thunks, sv_kinetic_energy/sv_animcmd wrappers,
//           g_team_param_init_guard CXA-guard functions, vtable dispatchers, misc

// ---- External declarations -----------------------------------------------

[[noreturn]] extern "C" void abort();

extern "C" s32  __cxa_guard_acquire(s64 *);
extern "C" void __cxa_guard_release(s64 *);
extern "C" void global_param_init_sets_team_flag();
extern "C" void FUN_71000001c0(void *, void *, void *);
extern "C" void FUN_7101763de0();
extern "C" void FUN_710337a860(u64, u64, u64);   // hash-dispatch helper
extern "C" void FUN_710181e8a0(s64);
extern "C" void jeFree_710392e590(s64);
extern "C" void FUN_71025e9900(s64);

extern "C" s64 g_team_param_init_guard;
extern "C" u8  DAT_71052c4180;
extern "C" u8  PTR_LOOP_7104f16000;
extern "C" u8  DAT_71052c41b0;
extern "C" u64 DAT_71052c4730;
extern "C" u64 DAT_71052c45c0;
extern "C" u8  DAT_7105326b90;

struct lua_State;

namespace app {
    namespace sv_kinetic_energy {
        void unable(lua_State *);
        void clear_speed_ex(lua_State *);
    }
    namespace sv_animcmd {
        void RUMBLE_HIT_STATUS(lua_State *);
        void FT_START_CUTIN_JACK_FINAL(lua_State *);
    }
}

// ---- abort() / __throw_out_of_range thunks --------------------------------

// 0x71017588d8
[[noreturn]] void FUN_71017588d8(void) { abort(); }

// 0x71018b107c
[[noreturn]] void FUN_71018b107c(void) { abort(); }

// 0x710197f32c
[[noreturn]] void FUN_710197f32c(void) { abort(); }

// 0x7101426c00
[[noreturn]] void FUN_7101426c00(void) { abort(); }

// 0x7101495480
[[noreturn]] void FUN_7101495480(void) { abort(); }

// 0x71014867b0 - already in d5_009, omitted here

// 0x71019d544c
[[noreturn]] void FUN_71019d544c(void) { abort(); }

// 0x7101859500
[[noreturn]] void FUN_7101859500(void) { abort(); }

// 0x7101b37a80
[[noreturn]] void FUN_7101b37a80(void) { abort(); }

// 0x7101ca2c48
[[noreturn]] void FUN_7101ca2c48(void) { abort(); }

// ---- sv_kinetic_energy / sv_animcmd wrappers -----------------------------

// 0x7101fa2790
u32 FUN_7101fa2790(lua_State *param_1) { app::sv_kinetic_energy::unable(param_1); return 0; }

// 0x7101fa2d20
u32 FUN_7101fa2d20(lua_State *param_1) { app::sv_kinetic_energy::clear_speed_ex(param_1); return 0; }

// 0x7101fc2c00
u32 FUN_7101fc2c00(lua_State *param_1) { app::sv_animcmd::RUMBLE_HIT_STATUS(param_1); return 0; }

// 0x7101fc2ec0
u32 FUN_7101fc2ec0(lua_State *param_1) { app::sv_animcmd::FT_START_CUTIN_JACK_FINAL(param_1); return 0; }

// ---- Simple call wrapper -------------------------------------------------

// 0x7101ea50e8 — call FUN_710337a860 with hash constant
void FUN_7101ea50e8(void)
{
    FUN_710337a860(0x4dffff1e95633cb8ULL, 0, 0);
}

// ---- Vtable dispatchers --------------------------------------------------

// 0x71013292d0 — WorkModule vtable +0x108, const 0x2100000c, return ~result&1
u32 FUN_71013292d0(u64 param_1, app::BattleObjectModuleAccessor* acc)
{
    s64 *work = reinterpret_cast<s64*>(acc->work_module);
    u32 flag = (*(u32(**)(s64*, u32))(*work + 0x108))(work, 0x2100000c);
    return ~flag & 1;
}

// 0x7101329690 — same pattern as FUN_71013292d0
u32 FUN_7101329690(u64 param_1, app::BattleObjectModuleAccessor* acc)
{
    s64 *work = reinterpret_cast<s64*>(acc->work_module);
    u32 flag = (*(u32(**)(s64*, u32))(*work + 0x108))(work, 0x2100000c);
    return ~flag & 1;
}

// 0x7101f9509c — vtable +0x30, passes param_1 and &DAT_7105326b90
u64 FUN_7101f9509c(s64 *param_1)
{
    (*(void(**)(s64 *, u8 *))(*param_1 + 0x30))(param_1, &DAT_7105326b90);
    return 0;
}

// ---- g_team_param_init_guard CXA-guard pattern ---------------------------
// All seven functions share the same guard/init sequence and return different
// static data pointers.

// 0x710137e210
u8 *FUN_710137e210(void)
{
    if (!(g_team_param_init_guard & 1)) {
        s32 iVar1 = __cxa_guard_acquire(&g_team_param_init_guard);
        if (iVar1 != 0) {
            global_param_init_sets_team_flag();
            FUN_71000001c0((void *)FUN_7101763de0, &DAT_71052c4180, &PTR_LOOP_7104f16000);
            __cxa_guard_release(&g_team_param_init_guard);
        }
    }
    return &DAT_71052c41b0;
}

// 0x710137e280
u64 *FUN_710137e280(void)
{
    if (!(g_team_param_init_guard & 1)) {
        s32 iVar1 = __cxa_guard_acquire(&g_team_param_init_guard);
        if (iVar1 != 0) {
            global_param_init_sets_team_flag();
            FUN_71000001c0((void *)FUN_7101763de0, &DAT_71052c4180, &PTR_LOOP_7104f16000);
            __cxa_guard_release(&g_team_param_init_guard);
        }
    }
    return &DAT_71052c4730;
}

// 0x71013809c0 — same init, returns &DAT_71052c41b0
u8 *FUN_71013809c0(void)
{
    if (!(g_team_param_init_guard & 1)) {
        s32 iVar1 = __cxa_guard_acquire(&g_team_param_init_guard);
        if (iVar1 != 0) {
            global_param_init_sets_team_flag();
            FUN_71000001c0((void *)FUN_7101763de0, &DAT_71052c4180, &PTR_LOOP_7104f16000);
            __cxa_guard_release(&g_team_param_init_guard);
        }
    }
    return &DAT_71052c41b0;
}

// 0x7101380a30 — same init, returns &DAT_71052c4730
u64 *FUN_7101380a30(void)
{
    if (!(g_team_param_init_guard & 1)) {
        s32 iVar1 = __cxa_guard_acquire(&g_team_param_init_guard);
        if (iVar1 != 0) {
            global_param_init_sets_team_flag();
            FUN_71000001c0((void *)FUN_7101763de0, &DAT_71052c4180, &PTR_LOOP_7104f16000);
            __cxa_guard_release(&g_team_param_init_guard);
        }
    }
    return &DAT_71052c4730;
}

// 0x7101380aa0 — same init, returns &DAT_71052c45c0
u64 *FUN_7101380aa0(void)
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

// 0x7101388880 — same init, returns &DAT_71052c41b0
u8 *FUN_7101388880(void)
{
    if (!(g_team_param_init_guard & 1)) {
        s32 iVar1 = __cxa_guard_acquire(&g_team_param_init_guard);
        if (iVar1 != 0) {
            global_param_init_sets_team_flag();
            FUN_71000001c0((void *)FUN_7101763de0, &DAT_71052c4180, &PTR_LOOP_7104f16000);
            __cxa_guard_release(&g_team_param_init_guard);
        }
    }
    return &DAT_71052c41b0;
}

// 0x71013888f0 — same init, returns &DAT_71052c4730
u64 *FUN_71013888f0(void)
{
    if (!(g_team_param_init_guard & 1)) {
        s32 iVar1 = __cxa_guard_acquire(&g_team_param_init_guard);
        if (iVar1 != 0) {
            global_param_init_sets_team_flag();
            FUN_71000001c0((void *)FUN_7101763de0, &DAT_71052c4180, &PTR_LOOP_7104f16000);
            __cxa_guard_release(&g_team_param_init_guard);
        }
    }
    return &DAT_71052c4730;
}

// ---- Misc wrappers -------------------------------------------------------

// 0x71014ca730 — iterate vector-like array, clear flag and call FUN_71025e9900
void FUN_71014ca730(s64 param_1)
{
    s64 *vec_inner = *(s64 **)(param_1 + 0x18);
    s64 *plVar2 = (s64 *)vec_inner[1];
    for (s64 *plVar1 = (s64 *)vec_inner[0]; plVar1 != plVar2; plVar1++) {
        s64 lVar3 = *plVar1;
        if (lVar3 != 0) {
            *(u8 *)(lVar3 + 0x110) = 0;
            FUN_71025e9900(lVar3 + 0x108);
        }
    }
}

// 0x710181e9f0 — check vtable field==7, zero field, conditionally call two helpers

namespace std { namespace __1 {
template<bool> struct __vector_base_common {
    [[noreturn]] static void __throw_out_of_range();
};
}}

bool FUN_710181e9f0(s64 param_1)
{
    s64 lVar2 = *(s64 *)(param_1 + 0x58);
    s32 iVar1 = *(s32 *)(*(s64 *)(*(s64 *)(lVar2 + 0x100) + 0x80) + 0xf8);
    if ((iVar1 == 7) && (*(u64 *)(param_1 + 0x58) = 0, lVar2 != 0)) {
        FUN_710181e8a0(lVar2);
        jeFree_710392e590(lVar2);
    }
    return iVar1 == 7;
}
