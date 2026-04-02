#include "app/BattleObjectModuleAccessor.h"

#define DMG(acc) (acc->damage_module)
#define VT(mod) (*reinterpret_cast<void***>(mod))

namespace app::lua_bind {

// 71020d1b20 -- hash-switch on field name, call vtable[0x188/8] (refresh), return float field
// hash 0x2369a2644 → damage_module+0x44
// hash 0xe085e_517c → damage_module+0x48
// hash 0xa_c3a7_d97e → damage_module+0x58
f32 ItemDamageModuleImpl__damage_log_value_float_impl(BattleObjectModuleAccessor* a, u64 hash) {
    auto* m = DMG(a);
    u64 h = hash & 0xffffffffffULL;
    if (h == 0xac3a7d97eULL) {
        void* log = reinterpret_cast<void*(*)(void*)>(VT(m)[0x188/8])(m);
        asm("");
        return *reinterpret_cast<f32*>(reinterpret_cast<u8*>(log) + 0x58);
    } else if (h == 0xe085e517cULL) {
        void* log = reinterpret_cast<void*(*)(void*)>(VT(m)[0x188/8])(m);
        asm("");
        return *reinterpret_cast<f32*>(reinterpret_cast<u8*>(log) + 0x48);
    } else if (h == 0x2369a2644ULL) {
        void* log = reinterpret_cast<void*(*)(void*)>(VT(m)[0x188/8])(m);
        asm("");
        return *reinterpret_cast<f32*>(reinterpret_cast<u8*>(log) + 0x44);
    }
    return 0.0f;
}

// 71020d1bc0 -- hash-switch on field name, return int field
// hash 0xf_2156_2598 → damage_module+0x84
// hash 0x9_232d_562b → damage_module+0x80
u32 ItemDamageModuleImpl__damage_log_value_int_impl(BattleObjectModuleAccessor* a, u64 hash) {
    auto* m = DMG(a);
    u64 h = hash & 0xffffffffffULL;
    if (h == 0x9232d562bULL) {
        void* log = reinterpret_cast<void*(*)(void*)>(VT(m)[0x188/8])(m);
        asm("");
        return *reinterpret_cast<u32*>(reinterpret_cast<u8*>(log) + 0x80);
    } else if (h == 0xf21562598ULL) {
        void* log = reinterpret_cast<void*(*)(void*)>(VT(m)[0x188/8])(m);
        asm("");
        return *reinterpret_cast<u32*>(reinterpret_cast<u8*>(log) + 0x84);
    }
    return 0;
}

// 71020d1af0 -- x0 (accessor) unused; loads global item param singleton (adrp),
//   reads float s2 at +0x73068, returns (val1 <= 0.0f) & (s2 <= val2)
// NOTE: uses adrp → .inst for exact bytes
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u32 ItemDamageModuleImpl__is_smash_damage_impl(BattleObjectModuleAccessor*, f32 val1, f32 val2) {
    asm(
        ".inst 0xD0018F88\n"    // adrp x8, <singleton page>
        ".inst 0xF940F108\n"    // ldr x8, [x8, #0x1e0]
        ".inst 0xF9400108\n"    // ldr x8, [x8]
        ".inst 0x52860D09\n"    // mov w9, #0x3068
        ".inst 0x72A000E9\n"    // movk w9, #0x7, LSL #16
        ".inst 0xBC696902\n"    // ldr s2, [x8, w9, UXTW]
        ".inst 0x1E202008\n"    // fcmp s0, #0.0
        ".inst 0x1A9F87E8\n"    // cset w8, ls
        ".inst 0x1E212040\n"    // fcmp s2, s1
        ".inst 0x1A9F87E9\n"    // cset w9, ls
        ".inst 0x0A090100\n"    // and w0, w8, w9
        ".inst 0xD65F03C0\n"    // ret
    );
}
#endif

} // namespace app::lua_bind
