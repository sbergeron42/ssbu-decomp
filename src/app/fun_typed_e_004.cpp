// pool-e: Shield/Damage/Hit module functions
// Types-first HARD decomp targeting ShieldModule, DamageModule, HitModule

#include "types.h"
#include "app/BattleObjectModuleAccessor.h"

#define VT(m) (*reinterpret_cast<void***>(m))

extern "C" bool FUN_710068f7a0(app::BattleObjectModuleAccessor*);

// ---------------------------------------------------------------------------
// 0x7100479590  96B  InitDamage  [VERIFIED 100%]
// ---------------------------------------------------------------------------
bool FUN_7100479590_479590(void** module, u32 param) {
    if (!(reinterpret_cast<bool(*)(void**)>(VT(module)[0x70 / 8])(module) & 1)) {
        return false;
    }
    void* result = reinterpret_cast<void*(*)(void**, u32)>(VT(module)[0x68 / 8])(module, param);
    return *reinterpret_cast<u8*>(reinterpret_cast<u8*>(result) + 0x30) != 0;
}

// ---------------------------------------------------------------------------
// 0x71006ebba0  80B  SetHitStopFrameFix (HARD)
// NOTE: prologue add x29 gap=13 exceeds fix_prologue_sched.py MAX_GAP=8.
// All instructions match but frame pointer scheduling differs.
// ---------------------------------------------------------------------------
void FUN_71006ebba0_6ebba0(void* self, u32 param) {
    void* acc = *reinterpret_cast<void**>(reinterpret_cast<u8*>(self) + 0x8);
    void** wm = *reinterpret_cast<void***>(reinterpret_cast<u8*>(acc) + 0x50);
    u32 val = reinterpret_cast<u32(*)(void**, u64, u64)>(VT(wm)[0x250 / 8])(
        wm, 0x6e5ec7051ULL, 0x1a99c94c70ULL);
    *reinterpret_cast<u32*>(reinterpret_cast<u8*>(self) + 0x14) = param;
    *reinterpret_cast<u32*>(reinterpret_cast<u8*>(self) + 0x18) = val;
}

// ---------------------------------------------------------------------------
// 0x71006988b0  128B  check_hit_dead_effect
// Checks initial condition, then 3 WorkModule flags.
// Returns true only if initial check passes and all 3 flags are clear.
// ---------------------------------------------------------------------------
bool FUN_71006988b0_6988b0(app::BattleObjectModuleAccessor* acc) {
    void** wm = reinterpret_cast<void**>(acc->work_module);
    if (FUN_710068f7a0(acc) & 1) {
        u32 base_flag = 0x20000087;
        if (!(reinterpret_cast<u32(*)(void**, u32)>(VT(wm)[0x108 / 8])(wm, base_flag) & 1)) {
            if (!(reinterpret_cast<u32(*)(void**, u32)>(VT(wm)[0x108 / 8])(wm, base_flag + 0x16) & 1)) {
                if (__builtin_expect(!(reinterpret_cast<u32(*)(void**, u32)>(VT(wm)[0x108 / 8])(wm, base_flag + 0x39) & 1), 0)) {
                    return true;
                }
            }
        }
    }
    return false;
}

// ---------------------------------------------------------------------------
// 0x7100694c70  64B  get_just_shield_se  [VERIFIED 100%]
// ---------------------------------------------------------------------------
u64 FUN_7100694c70_694c70(int kind) {
    u64 result = 0x14a0d4a6ffULL;
    if (kind == 0x3d) {
        result = 0x110f909727ULL;
    }
    if (kind == 0x3c) {
        result = 0x11944302d8ULL;
    }
    return result;
}

// ---------------------------------------------------------------------------
// 0x7101655610  48B  is_visible_backshield  [VERIFIED 100%]
// ---------------------------------------------------------------------------
bool FUN_7101655610_1655610(app::BattleObjectModuleAccessor* acc) {
    void** wm = reinterpret_cast<void**>(acc->work_module);
    bool flag = reinterpret_cast<bool(*)(void**, u32)>(VT(wm)[0x108 / 8])(wm, 0x2000007d);
    return !flag;
}

// ---------------------------------------------------------------------------
// 0x7101655640  32B  is_force_visible_backshield  [VERIFIED 100%]
// ---------------------------------------------------------------------------
bool FUN_7101655640_1655640(app::BattleObjectModuleAccessor* acc) {
    void** wm = reinterpret_cast<void**>(acc->work_module);
    return reinterpret_cast<bool(*)(void**, u32)>(VT(wm)[0x108 / 8])(wm, 0x2000007e);
}

// ---------------------------------------------------------------------------
// 0x71016555e0  48B  is_enable_backshield  [VERIFIED 100%]
// ---------------------------------------------------------------------------
bool FUN_71016555e0_16555e0(app::BattleObjectModuleAccessor* acc) {
    void** cm = reinterpret_cast<void**>(acc->capture_module);
    bool flag = reinterpret_cast<bool(*)(void**)>(VT(cm)[0x68 / 8])(cm);
    return !flag;
}

// 0x7100694cb0 is_valid_just_shield_reflector — SKIPPED after 3 attempts
// Issues: prologue str x19 scheduling + post-call conditional pattern diverge from NX Clang
