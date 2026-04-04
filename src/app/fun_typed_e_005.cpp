// pool-e: Shield/Damage/Hit module functions — batch 2
// Types-first HARD decomp targeting ShieldModule, DamageModule, HitModule

#include "types.h"
#include "app/BattleObjectModuleAccessor.h"

#define VT(m) (*reinterpret_cast<void***>(m))

// ---------------------------------------------------------------------------
// 0x71003618e0  32B  check_stat_unable_shield
// Leaf function: reads byte at +0x59 from pointer chain, extracts bit 6.
// lua_State* → *(lua_state - 8) → +0x168 → byte at +0x59 → bit 6
// ---------------------------------------------------------------------------
u8 FUN_71003618e0_3618e0(void* lua_state) {
    void* ptr = *reinterpret_cast<void**>(reinterpret_cast<u8*>(lua_state) - 8);
    void* obj = *reinterpret_cast<void**>(reinterpret_cast<u8*>(ptr) + 0x168);
    u8 byte_val = *reinterpret_cast<u8*>(reinterpret_cast<u8*>(obj) + 0x59);
    return (byte_val >> 6) & 1;
}

// ---------------------------------------------------------------------------
// 0x7100361b70  32B  shield_rate
// Leaf function: float division of two adjacent fields at +0xe8 and +0xec.
// ---------------------------------------------------------------------------
f32 FUN_7100361b70_361b70(void* lua_state) {
    void* ptr = *reinterpret_cast<void**>(reinterpret_cast<u8*>(lua_state) - 8);
    u8* obj = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(ptr) + 0x168);
    f32 a = *reinterpret_cast<f32*>(obj + 0xe8);
    f32 b = *reinterpret_cast<f32*>(obj + 0xec);
    return a / b;
}

// ---------------------------------------------------------------------------
// 0x7100693e50  160B  check_damage_speed_up
// Accesses DamageModule (+0xA8) and WorkModule (+0x50).
// Calls DamageModule vt[0x31] to get damage info struct, then checks
// work param threshold against float param, plus struct condition checks.
// Returns 1 if speed-up conditions met, 0 otherwise.
// ---------------------------------------------------------------------------
u64 FUN_7100693e50_693e50(app::BattleObjectModuleAccessor* acc, f32 threshold) {
    void** dm = reinterpret_cast<void**>(acc->damage_module);
    void* info = reinterpret_cast<void*(*)(void**)>(VT(dm)[0x188 / 8])(dm);
    if (!info) return 0;
    u8* p = reinterpret_cast<u8*>(info);
    void** wm = reinterpret_cast<void**>(acc->work_module);
    s32 param_val = reinterpret_cast<s32(*)(void**, u64, u64)>(VT(wm)[0x250 / 8])(
        wm, 0xd8ddb421dULL, 0x26ca30e786ULL);
    f32 fval = static_cast<f32>(param_val);
    if (__builtin_expect(threshold <= fval, 0)) return 0;
    if (__builtin_expect(p[0x8f] != 0, 0)) return 0;
    if (p[0x92] != 0 && __builtin_expect(p[0x93] == 0, 0)) return 0;
    if (__builtin_expect(*reinterpret_cast<s32*>(p + 0x98) != 0, 0)) return 0;
    return 1;
}
