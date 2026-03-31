#include "app/BattleObjectModuleAccessor.h"

// ColorBlendModule — accessor+0x70
#define COLORBLEND_MODULE(acc) (*reinterpret_cast<void**>(reinterpret_cast<u8*>(acc) + 0x70))
#define VTABLE(mod) (*reinterpret_cast<void***>(mod))

namespace app::lua_bind {

// 7101ffe7e0 — off_flash (bool param) [vtable+0x80]
void ColorBlendModule__off_flash_impl(BattleObjectModuleAccessor* accessor, bool p1) {
    auto* m = COLORBLEND_MODULE(accessor); reinterpret_cast<void (*)(void*, bool)>(VTABLE(m)[0x80 / 8])(m, p1);
}

// 7101ffe800 — set_enable_flash (bool param) [vtable+0x88]
void ColorBlendModule__set_enable_flash_impl(BattleObjectModuleAccessor* accessor, bool p1) {
    auto* m = COLORBLEND_MODULE(accessor); reinterpret_cast<void (*)(void*, bool)>(VTABLE(m)[0x88 / 8])(m, p1);
}

// 7101ffe820 — set_burn_color (bool param at p2) [vtable+0x90]
void ColorBlendModule__set_burn_color_impl(BattleObjectModuleAccessor* accessor, u64 p1, bool p2) {
    auto* m = COLORBLEND_MODULE(accessor); reinterpret_cast<void (*)(void*, u64, bool)>(VTABLE(m)[0x90 / 8])(m, p1, p2);
}

// 7101ffe840 — set_burn_color_frame (bool param at p2) [vtable+0x98]
void ColorBlendModule__set_burn_color_frame_impl(BattleObjectModuleAccessor* accessor, u64 p1, bool p2) {
    auto* m = COLORBLEND_MODULE(accessor); reinterpret_cast<void (*)(void*, u64, bool)>(VTABLE(m)[0x98 / 8])(m, p1, p2);
}

// 7101ffe860 — off_burn_color (bool param) [vtable+0xa0]
void ColorBlendModule__off_burn_color_impl(BattleObjectModuleAccessor* accessor, bool p1) {
    auto* m = COLORBLEND_MODULE(accessor); reinterpret_cast<void (*)(void*, bool)>(VTABLE(m)[0xa0 / 8])(m, p1);
}

// 7101ffe880 — set_burn_color_priority (bool param at p2) [vtable+0xa8]
void ColorBlendModule__set_burn_color_priority_impl(BattleObjectModuleAccessor* accessor, u64 p1, bool p2) {
    auto* m = COLORBLEND_MODULE(accessor); reinterpret_cast<void (*)(void*, u64, bool)>(VTABLE(m)[0xa8 / 8])(m, p1, p2);
}

// 7101ffe8e0 — set_last_attack_direction [vtable+0xe0]
void ColorBlendModule__set_last_attack_direction_impl(BattleObjectModuleAccessor* accessor, u64 p1) {
    auto* m = COLORBLEND_MODULE(accessor); reinterpret_cast<void (*)(void*, u64)>(VTABLE(m)[0xe0 / 8])(m, p1);
}

// 7101ffe910 — cancel_main_color [vtable+0x100]
void ColorBlendModule__cancel_main_color_impl(BattleObjectModuleAccessor* accessor, u64 p1) {
    auto* m = COLORBLEND_MODULE(accessor); reinterpret_cast<void (*)(void*, u64)>(VTABLE(m)[0x100 / 8])(m, p1);
}

// 7101ffe940 — get_status [vtable+0x170]
s32 ColorBlendModule__get_status_impl(BattleObjectModuleAccessor* accessor) {
    auto* m = COLORBLEND_MODULE(accessor); return reinterpret_cast<s32 (*)(void*)>(VTABLE(m)[0x170 / 8])(m);
}

// 7101ffe950 — set_disable_camera_depth_influence (bool param) [vtable+0x1b0]
void ColorBlendModule__set_disable_camera_depth_influence_impl(BattleObjectModuleAccessor* accessor, bool p1) {
    auto* m = COLORBLEND_MODULE(accessor); reinterpret_cast<void (*)(void*, bool)>(VTABLE(m)[0x1b0 / 8])(m, p1);
}

void ColorBlendModule__set_priority_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { auto* m=COLORBLEND_MODULE(a); reinterpret_cast<void(*)(void*,u64,bool)>(VTABLE(m)[0xc8/8])(m,p1,p2); }
void ColorBlendModule__set_shadow_bloom_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { auto* m=COLORBLEND_MODULE(a); reinterpret_cast<void(*)(void*,u64,bool)>(VTABLE(m)[0xd8/8])(m,p1,p2); }
void ColorBlendModule__set_main_color_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { auto* m=COLORBLEND_MODULE(a); reinterpret_cast<void(*)(void*,u64,bool)>(VTABLE(m)[0xf8/8])(m,p1,p2); }
void ColorBlendModule__set_status_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { auto* m=COLORBLEND_MODULE(a); reinterpret_cast<void(*)(void*,u64,bool)>(VTABLE(m)[0x168/8])(m,p1,p2); }
} // namespace app::lua_bind
