#include "app/BattleObjectModuleAccessor.h"

namespace app::lua_bind {

// 71020d1af0 — compares float params against global damage threshold (48 bytes)
// NOTE: uses global singleton at 0x71052c31e0 — adrp won't match
bool ItemDamageModuleImpl__is_smash_damage_impl(f32 p0, f32 p1) {
    // original: loads **(0x71052c31e0) + 0x73068 as float, checks (p0<=0) && (that<=p1)
    (void)p0; (void)p1;
    return false;
}

// 71020d1b20 — hash-switch on field name, call vtable[0x188/8] (refresh), return float field
// hash 0x2369a2644 → damage_module+0x44
// hash 0xe085e_517c → damage_module+0x48
// hash 0xa_c3a7_d97e → damage_module+0x58
f32 ItemDamageModuleImpl__damage_log_value_float_impl(BattleObjectModuleAccessor* a, u64 hash) {
    auto* m = reinterpret_cast<u8*>(a->damage_module);
    auto* vt = *reinterpret_cast<void***>(m);
    u64 key = hash & 0xffffffffffull;
    if (key == 0x2369a2644ull) {
        reinterpret_cast<void(*)(void*)>(vt[0x188/8])(m);
        return *reinterpret_cast<f32*>(m + 0x44);
    }
    if (key == 0xe085e517cull) {
        reinterpret_cast<void(*)(void*)>(vt[0x188/8])(m);
        return *reinterpret_cast<f32*>(m + 0x48);
    }
    if (key == 0xac3a7d97eull) {
        reinterpret_cast<void(*)(void*)>(vt[0x188/8])(m);
        return *reinterpret_cast<f32*>(m + 0x58);
    }
    return 0.0f;
}

// 71020d1bc0 — hash-switch on field name, return int field (720 bytes, many cases)
// hash 0xf_2156_2598 → damage_module+0x84
// hash 0x9_232d_562b → damage_module+0x80
u32 ItemDamageModuleImpl__damage_log_value_int_impl(BattleObjectModuleAccessor* a, u64 hash) {
    auto* m = reinterpret_cast<u8*>(a->damage_module);
    auto* vt = *reinterpret_cast<void***>(m);
    u64 key = hash & 0xffffffffffull;
    if (key == 0xf21562598ull) {
        reinterpret_cast<void(*)(void*)>(vt[0x188/8])(m);
        return *reinterpret_cast<u32*>(m + 0x84);
    }
    if (key == 0x9232d562bull) {
        reinterpret_cast<void(*)(void*)>(vt[0x188/8])(m);
        return *reinterpret_cast<u32*>(m + 0x80);
    }
    return 0;
}

} // namespace app::lua_bind
