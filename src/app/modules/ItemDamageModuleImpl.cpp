#include "app/BattleObjectModuleAccessor.h"

#define DMG(acc) (acc->damage_module)
#define VT(mod) (*reinterpret_cast<void***>(mod))
#define HIDDEN __attribute__((visibility("hidden")))

// lib::Singleton<app::ItemParamAccessor>::instance_
extern "C" void* DAT_71052c31e0 HIDDEN;

namespace app::lua_bind {

// 71020d1b20 -- hash-switch on field name, call vtable[0x188/8] (refresh), return float field
// hash 0x2369a2644 → damage_log+0x44, 0xee085517c → +0x48, 0xac3a7d97e → +0x58
f32 ItemDamageModuleImpl__damage_log_value_float_impl(BattleObjectModuleAccessor* a, u64 hash) {
    auto* m = DMG(a);
    u64 h = hash & 0xffffffffffULL;
    if (h == 0x2369a2644ULL) {
        void* log = reinterpret_cast<void*(*)(void*)>(VT(m)[0x188/8])(m);
        return *reinterpret_cast<f32*>(reinterpret_cast<u8*>(log) + 0x44);
    }
    if (h == 0xee085517cULL) {
        void* log = reinterpret_cast<void*(*)(void*)>(VT(m)[0x188/8])(m);
        return *reinterpret_cast<f32*>(reinterpret_cast<u8*>(log) + 0x48);
    }
    if (h == 0xac3a7d97eULL) {
        void* log = reinterpret_cast<void*(*)(void*)>(VT(m)[0x188/8])(m);
        return *reinterpret_cast<f32*>(reinterpret_cast<u8*>(log) + 0x58);
    }
    return 0.0f;
}

// 71020d1bc0 -- hash-switch on field name, return int field
// hash 0xf21562598 → damage_log+0x84, 0x9232d562b → +0x80
u32 ItemDamageModuleImpl__damage_log_value_int_impl(BattleObjectModuleAccessor* a, u64 hash) {
    auto* m = DMG(a);
    u64 h = hash & 0xffffffffffULL;
    if (h == 0xf21562598ULL) {
        void* log = reinterpret_cast<void*(*)(void*)>(VT(m)[0x188/8])(m);
        return *reinterpret_cast<u32*>(reinterpret_cast<u8*>(log) + 0x84);
    }
    if (h == 0x9232d562bULL) {
        void* log = reinterpret_cast<void*(*)(void*)>(VT(m)[0x188/8])(m);
        return *reinterpret_cast<u32*>(reinterpret_cast<u8*>(log) + 0x80);
    }
    return 0;
}

// 71020d1af0 -- check if damage values are within smash thresholds
// Loads threshold from ItemParamAccessor singleton at offset 0x73068
bool ItemDamageModuleImpl__is_smash_damage_impl(BattleObjectModuleAccessor* a, f32 damage, f32 knockback) {
    u8* params = *reinterpret_cast<u8**>(DAT_71052c31e0);
    f32 threshold = *reinterpret_cast<f32*>(params + 0x73068);
    return (damage <= 0.0f) & (threshold <= knockback);
}

} // namespace app::lua_bind

