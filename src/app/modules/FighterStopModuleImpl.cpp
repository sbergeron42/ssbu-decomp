#include "app/BattleObjectModuleAccessor.h"

#define VT(m) (*reinterpret_cast<void***>(m))

namespace app::lua_bind {

// 71020ad720 -- is_damage_stop: check status range, dispatch to work module query
// Flow: get status → if in damage range, check work module value; else tail-call base class
// NX Clang reloads chain (stop+8) after each call instead of caching in register
bool FighterStopModuleImpl__is_damage_stop_impl(BattleObjectModuleAccessor* a) {
    auto* stop = reinterpret_cast<u8*>(a->stop_module);
    auto* status_mod = *reinterpret_cast<void**>(*reinterpret_cast<u8**>(stop + 0x8) + 0x40);
    s32 status = reinterpret_cast<s32(*)(void*)>(VT(status_mod)[0x110/8])(status_mod);
#ifdef MATCHING_HACK_NX_CLANG
    asm volatile("" ::: "memory");
#endif
    if (__builtin_expect(status > 0xc7, 0)) goto larger_check;
    if (__builtin_expect((u32)(status - 0x47) >= 5, 0)) goto base_class;
    {
        auto* work = *reinterpret_cast<void**>(*reinterpret_cast<u8**>(stop + 0x8) + 0x50);
        if (reinterpret_cast<u32(*)(void*, u32)>(VT(work)[0x108/8])(work, 0x2100000fu) & 1)
            goto damage_range;
    }

base_class:
    return reinterpret_cast<bool(*)(void*)>(VT(stop)[0xa0/8])(stop);

larger_check:
    if (status == 0xc8) goto damage_range;
    if (status == 0x149) goto damage_range;
    if (status == 0x14c) goto damage_range;
    goto base_class;

damage_range:
    {
        auto* work2 = *reinterpret_cast<void**>(*reinterpret_cast<u8**>(stop + 0x8) + 0x50);
        s32 val = reinterpret_cast<s32(*)(void*, u32)>(VT(work2)[0x98/8])(work2, 0x11000006u);
        return val > 0;
    }
}

// 71020ad7e0 -- get_damage_stop_frame: same status check, tail call to work module or base class
void FighterStopModuleImpl__get_damage_stop_frame_impl(BattleObjectModuleAccessor* a) {
    auto* stop = reinterpret_cast<u8*>(a->stop_module);
    auto* status_mod = *reinterpret_cast<void**>(*reinterpret_cast<u8**>(stop + 0x8) + 0x40);
    s32 status = reinterpret_cast<s32(*)(void*)>(VT(status_mod)[0x110/8])(status_mod);
#ifdef MATCHING_HACK_NX_CLANG
    asm volatile("" ::: "memory");
#endif
    if (__builtin_expect(status > 0xc7, 0)) goto larger_check;
    if (__builtin_expect((u32)(status - 0x47) >= 5, 0)) goto base_class;
    {
        auto* work = *reinterpret_cast<void**>(*reinterpret_cast<u8**>(stop + 0x8) + 0x50);
        if (reinterpret_cast<u32(*)(void*, u32)>(VT(work)[0x108/8])(work, 0x2100000fu) & 1)
            goto damage_range;
    }

base_class:
    reinterpret_cast<void(*)(void*)>(VT(stop)[0xc8/8])(stop);
    return;

larger_check:
    if (status == 0xc8) goto damage_range;
    if (status == 0x149) goto damage_range;
    if (status == 0x14c) goto damage_range;
    goto base_class;

damage_range:
    {
        auto* work2 = *reinterpret_cast<void**>(*reinterpret_cast<u8**>(stop + 0x8) + 0x50);
        reinterpret_cast<void(*)(void*, u32)>(VT(work2)[0x98/8])(work2, 0x11000006u);
    }
}

} // namespace app::lua_bind
