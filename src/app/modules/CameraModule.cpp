#include "app/BattleObjectModuleAccessor.h"

// CameraModule — accessor+0x60
#define CAMERA_MODULE(acc) (*reinterpret_cast<void**>(reinterpret_cast<u8*>(acc) + 0x60))
#define VT(mod) (*reinterpret_cast<void***>(mod))

namespace app::lua_bind {

// 7101ff08d0 [vtable+0xc8]
void CameraModule__add_camera_range_offset_impl(BattleObjectModuleAccessor* a, void* p1, u64 p2) {
    auto* m = CAMERA_MODULE(a); reinterpret_cast<void(*)(void*,void*,u64)>(VT(m)[0xc8/8])(m,p1,p2);
}
// 7101ff08e0 [vtable+0xd0]
void CameraModule__add_camera_range_rect_impl(BattleObjectModuleAccessor* a, void* p1, u64 p2) {
    auto* m = CAMERA_MODULE(a); reinterpret_cast<void(*)(void*,void*,u64)>(VT(m)[0xd0/8])(m,p1,p2);
}
// 7101ff0950 [vtable+0x138]
s32 CameraModule__get_priority_impl(BattleObjectModuleAccessor* a, u64 p1) {
    auto* m = CAMERA_MODULE(a); return reinterpret_cast<s32(*)(void*,u64)>(VT(m)[0x138/8])(m,p1);
}
// 7101ff0970 [vtable+0x148]
s32 CameraModule__get_player_no_impl(BattleObjectModuleAccessor* a, u64 p1) {
    auto* m = CAMERA_MODULE(a); return reinterpret_cast<s32(*)(void*,u64)>(VT(m)[0x148/8])(m,p1);
}
// 7101ff0990 [vtable+0x168]
void CameraModule__exit_damage_fly_impl(BattleObjectModuleAccessor* a, u64 p1) {
    auto* m = CAMERA_MODULE(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x168/8])(m,p1);
}
// 7101ff09b0 [vtable+0x178]
void CameraModule__exit_run_impl(BattleObjectModuleAccessor* a, u64 p1) {
    auto* m = CAMERA_MODULE(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x178/8])(m,p1);
}
// 7101ff09d0 [vtable+0x188]
void CameraModule__exit_being_carried_impl(BattleObjectModuleAccessor* a, u64 p1) {
    auto* m = CAMERA_MODULE(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x188/8])(m,p1);
}
// 7101ff0a50 [vtable+0x1d0]
void* CameraModule__get_main_camera_range_impl(BattleObjectModuleAccessor* a) {
    auto* m = CAMERA_MODULE(a); return reinterpret_cast<void*(*)(void*)>(VT(m)[0x1d0/8])(m);
}
// 7101ff0a80 [vtable+0x1e0]
s32 CameraModule__get_camera_type_impl(BattleObjectModuleAccessor* a) {
    auto* m = CAMERA_MODULE(a); return reinterpret_cast<s32(*)(void*)>(VT(m)[0x1e0/8])(m);
}
// 7101ff0a90 [vtable+0x1e8]
s32 CameraModule__get_camera_type_for_save_impl(BattleObjectModuleAccessor* a) {
    auto* m = CAMERA_MODULE(a); return reinterpret_cast<s32(*)(void*)>(VT(m)[0x1e8/8])(m);
}
// 7101ff0ae0 [vtable+0x218]
s32 CameraModule__get_quakeKind_impl(BattleObjectModuleAccessor* a) {
    auto* m = CAMERA_MODULE(a); return reinterpret_cast<s32(*)(void*)>(VT(m)[0x218/8])(m);
}
// 7101ff0b00 [vtable+0x228]
void CameraModule__end_final_zoom_out_impl(BattleObjectModuleAccessor* a) {
    auto* m = CAMERA_MODULE(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x228/8])(m);
}
// 7101ff0b10 [vtable+0x230]
void* CameraModule__get_camera_view_volume_z0_rect_impl(BattleObjectModuleAccessor* a) {
    auto* m = CAMERA_MODULE(a); return reinterpret_cast<void*(*)(void*)>(VT(m)[0x230/8])(m);
}

} // namespace app::lua_bind
