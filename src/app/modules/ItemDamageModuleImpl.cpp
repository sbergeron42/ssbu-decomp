#include "app/BattleObjectModuleAccessor.h"

#define DMG(acc) (acc->damage_module)
#define VT(mod) (*reinterpret_cast<void***>(mod))

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

} // namespace app::lua_bind

