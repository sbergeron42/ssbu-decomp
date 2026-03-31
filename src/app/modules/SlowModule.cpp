#include "app/BattleObjectModuleAccessor.h"

// SlowModule — accessor+0x170
#define SLOW_MODULE(acc) (*reinterpret_cast<void**>(reinterpret_cast<u8*>(acc) + 0x170))
#define VT(mod) (*reinterpret_cast<void***>(mod))

namespace app::lua_bind {

// 7102080480 [vtable+0x58]
bool SlowModule__is_slow_impl(BattleObjectModuleAccessor* a) {
    auto* m = SLOW_MODULE(a); return reinterpret_cast<bool(*)(void*)>(VT(m)[0x58/8])(m);
}
// 71020804b0 [vtable+0x70]
f32 SlowModule__mag_impl(BattleObjectModuleAccessor* a, u64 p1) {
    auto* m = SLOW_MODULE(a); return reinterpret_cast<f32(*)(void*,u64)>(VT(m)[0x70/8])(m,p1);
}
// 71020804c0 [vtable+0x78]
f32 SlowModule__rate_ignore_effect_impl(BattleObjectModuleAccessor* a) {
    auto* m = SLOW_MODULE(a); return reinterpret_cast<f32(*)(void*)>(VT(m)[0x78/8])(m);
}
// 71020804d0 [vtable+0x80]
f32 SlowModule__frame_impl(BattleObjectModuleAccessor* a, u64 p1) {
    auto* m = SLOW_MODULE(a); return reinterpret_cast<f32(*)(void*,u64)>(VT(m)[0x80/8])(m,p1);
}
// 71020804e0 [vtable+0x88]
void SlowModule__clear_impl(BattleObjectModuleAccessor* a) {
    auto* m = SLOW_MODULE(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x88/8])(m);
}
// 71020804f0 [vtable+0x90]
void SlowModule__clear_2_impl(BattleObjectModuleAccessor* a, u64 p1) {
    auto* m = SLOW_MODULE(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x90/8])(m,p1);
}
// 7102080500 [vtable+0x98] (bool param, and w2 #1)
void SlowModule__clear_immediate_impl(BattleObjectModuleAccessor* a, u64 p1, bool p2) {
    auto* m = SLOW_MODULE(a); reinterpret_cast<void(*)(void*,u64,bool)>(VT(m)[0x98/8])(m,p1,p2);
}
// 7102080530 [vtable+0xb0]
bool SlowModule__is_skip_impl(BattleObjectModuleAccessor* a) {
    auto* m = SLOW_MODULE(a); return reinterpret_cast<bool(*)(void*)>(VT(m)[0xb0/8])(m);
}
// 7102080540 [vtable+0xb8]
bool SlowModule__is_prev_skip_impl(BattleObjectModuleAccessor* a) {
    auto* m = SLOW_MODULE(a); return reinterpret_cast<bool(*)(void*)>(VT(m)[0xb8/8])(m);
}
// 7102080560 [vtable+0xc8]
void SlowModule__clear_whole_impl(BattleObjectModuleAccessor* a) {
    auto* m = SLOW_MODULE(a); reinterpret_cast<void(*)(void*)>(VT(m)[0xc8/8])(m);
}

void SlowModule__set_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { auto* m=SLOW_MODULE(a); reinterpret_cast<void(*)(void*,u64,bool)>(VT(m)[0x60/8])(m,p1,p2); }
f32 SlowModule__rate_impl2(BattleObjectModuleAccessor* a) { auto* m=SLOW_MODULE(a); return reinterpret_cast<f32(*)(void*)>(VT(m)[0xa8/8])(m); }
void SlowModule__set_whole_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=SLOW_MODULE(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0xc0/8])(m,p1); }
f32 SlowModule__whole_mag_impl(BattleObjectModuleAccessor* a) { auto* m=SLOW_MODULE(a); return reinterpret_cast<f32(*)(void*)>(VT(m)[0xd0/8])(m); }
void SlowModule__set_whole_frame_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=SLOW_MODULE(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0xd8/8])(m,p1); }
f32 SlowModule__whole_frame_impl(BattleObjectModuleAccessor* a) { auto* m=SLOW_MODULE(a); return reinterpret_cast<f32(*)(void*)>(VT(m)[0xe0/8])(m); }
} // namespace app::lua_bind
