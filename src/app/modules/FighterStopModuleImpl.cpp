#include "app/BattleObjectModuleAccessor.h"

namespace app::lua_bind {

// 71020ad720 -- is_damage_stop: check status range, dispatch to work module query
bool FighterStopModuleImpl__is_damage_stop_impl(BattleObjectModuleAccessor* a) {
    auto* stop = reinterpret_cast<u8*>(*reinterpret_cast<void**>(reinterpret_cast<u8*>(a) + 0x90));
    auto* chain = *reinterpret_cast<u8**>(stop + 0x8);
    // Get current status
    auto* status_mod = *reinterpret_cast<void**>(chain + 0x40);
    s32 status = reinterpret_cast<s32(*)(void*)>((*reinterpret_cast<void***>(status_mod))[0x110/8])(status_mod);
    bool is_damage_range = false;
    if (status > 0xc7) {
        is_damage_range = (status == 0xc8 || status == 0x149 || status == 0x14c);
    } else {
        u32 sub = static_cast<u32>(status - 0x47);
        if (sub < 5) {
            // Check work module flag
            auto* work = *reinterpret_cast<void**>(chain + 0x50);
            bool flag = reinterpret_cast<bool(*)(void*, u32)>((*reinterpret_cast<void***>(work))[0x108/8])(work, 0x2100000fu);
            if (flag) is_damage_range = true;
        }
    }
    if (!is_damage_range) {
        // Fall through to base class is_damage_stop
        auto fn = reinterpret_cast<bool(*)(void*)>((*reinterpret_cast<void***>(stop))[0xa0/8]);
        return fn(stop);
    }
    // Get work module value
    auto* work2 = *reinterpret_cast<void**>(chain + 0x50);
    s32 val = reinterpret_cast<s32(*)(void*, u32)>((*reinterpret_cast<void***>(work2))[0x98/8])(work2, 0x11000006u);
    return val > 0;
}

// 71020ad7e0 -- get_damage_stop_frame: same status check, tail call to work module
void FighterStopModuleImpl__get_damage_stop_frame_impl(BattleObjectModuleAccessor* a) {
    auto* stop = reinterpret_cast<u8*>(*reinterpret_cast<void**>(reinterpret_cast<u8*>(a) + 0x90));
    auto* chain = *reinterpret_cast<u8**>(stop + 0x8);
    // Get current status
    auto* status_mod = *reinterpret_cast<void**>(chain + 0x40);
    s32 status = reinterpret_cast<s32(*)(void*)>((*reinterpret_cast<void***>(status_mod))[0x110/8])(status_mod);
    bool is_damage_range = false;
    if (status > 0xc7) {
        is_damage_range = (status == 0xc8 || status == 0x149 || status == 0x14c);
    } else {
        u32 sub = static_cast<u32>(status - 0x47);
        if (sub < 5) {
            auto* work = *reinterpret_cast<void**>(chain + 0x50);
            bool flag = reinterpret_cast<bool(*)(void*, u32)>((*reinterpret_cast<void***>(work))[0x108/8])(work, 0x2100000fu);
            if (flag) is_damage_range = true;
        }
    }
    if (!is_damage_range) {
        // Fall through to base class get_damage_stop_frame
        auto fn = reinterpret_cast<void(*)(void*)>((*reinterpret_cast<void***>(stop))[0xc8/8]);
        fn(stop);
        return;
    }
    // Tail call to work module get value
    auto* work2 = *reinterpret_cast<void**>(chain + 0x50);
    reinterpret_cast<void(*)(void*, u32)>((*reinterpret_cast<void***>(work2))[0x98/8])(work2, 0x11000006u);
}

} // namespace app::lua_bind
