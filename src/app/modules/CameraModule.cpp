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

// Remaining CameraModule dispatchers
void CameraModule__v0x70(BattleObjectModuleAccessor* a,u64 p1) { auto* m=CAMERA_MODULE(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x70/8])(m,p1); }
void CameraModule__v0x80(BattleObjectModuleAccessor* a,u64 p1) { auto* m=CAMERA_MODULE(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x80/8])(m,p1); }
void CameraModule__v0x88(BattleObjectModuleAccessor* a,bool p1) { auto* m=CAMERA_MODULE(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x88/8])(m,p1); }
void CameraModule__v0x90(BattleObjectModuleAccessor* a,bool p1) { auto* m=CAMERA_MODULE(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x90/8])(m,p1); }
void CameraModule__v0x98(BattleObjectModuleAccessor* a,u64 p1) { auto* m=CAMERA_MODULE(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x98/8])(m,p1); }
void CameraModule__v0xa0(BattleObjectModuleAccessor* a,bool p1) { auto* m=CAMERA_MODULE(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0xa0/8])(m,p1); }
void CameraModule__v0xb8(BattleObjectModuleAccessor* a,u64 p1) { auto* m=CAMERA_MODULE(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0xb8/8])(m,p1); }
void CameraModule__v0xc0(BattleObjectModuleAccessor* a,u64 p1) { auto* m=CAMERA_MODULE(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0xc0/8])(m,p1); }
void CameraModule__v0xe8(BattleObjectModuleAccessor* a,u64 p1) { auto* m=CAMERA_MODULE(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0xe8/8])(m,p1); }
void CameraModule__v0xf0(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3,bool p4) { auto* m=CAMERA_MODULE(a); reinterpret_cast<void(*)(void*,u64,u64,u64,bool)>(VT(m)[0xf0/8])(m,p1,p2,p3,p4); }
void CameraModule__v0xf8(BattleObjectModuleAccessor* a,u64 p1) { auto* m=CAMERA_MODULE(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0xf8/8])(m,p1); }
void CameraModule__v0x128(BattleObjectModuleAccessor* a,u64 p1) { auto* m=CAMERA_MODULE(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x128/8])(m,p1); }
void CameraModule__v0x130(BattleObjectModuleAccessor* a,u64 p1) { auto* m=CAMERA_MODULE(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x130/8])(m,p1); }
void CameraModule__v0x140(BattleObjectModuleAccessor* a,u64 p1) { auto* m=CAMERA_MODULE(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x140/8])(m,p1); }
void CameraModule__v0x160(BattleObjectModuleAccessor* a,u64 p1) { auto* m=CAMERA_MODULE(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x160/8])(m,p1); }
void CameraModule__v0x170(BattleObjectModuleAccessor* a,u64 p1) { auto* m=CAMERA_MODULE(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x170/8])(m,p1); }
void CameraModule__v0x180(BattleObjectModuleAccessor* a,u64 p1) { auto* m=CAMERA_MODULE(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x180/8])(m,p1); }
void CameraModule__v0x198(BattleObjectModuleAccessor* a,bool p1) { auto* m=CAMERA_MODULE(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x198/8])(m,p1); }
void CameraModule__v0x1a0(BattleObjectModuleAccessor* a,bool p1) { auto* m=CAMERA_MODULE(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x1a0/8])(m,p1); }
void CameraModule__v0x1b8(BattleObjectModuleAccessor* a,u64 p1) { auto* m=CAMERA_MODULE(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x1b8/8])(m,p1); }
void CameraModule__v0x1f0(BattleObjectModuleAccessor* a,u64 p1) { auto* m=CAMERA_MODULE(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x1f0/8])(m,p1); }
void CameraModule__v0x200(BattleObjectModuleAccessor* a,u64 p1) { auto* m=CAMERA_MODULE(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x200/8])(m,p1); }
void CameraModule__v0x208(BattleObjectModuleAccessor* a,u64 p1) { auto* m=CAMERA_MODULE(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x208/8])(m,p1); }
void CameraModule__v0x210(BattleObjectModuleAccessor* a,u64 p1) { auto* m=CAMERA_MODULE(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x210/8])(m,p1); }
void CameraModule__v0x220(BattleObjectModuleAccessor* a,u64 p1) { auto* m=CAMERA_MODULE(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x220/8])(m,p1); }
void CameraModule__v0x238(BattleObjectModuleAccessor* a,u64 p1) { auto* m=CAMERA_MODULE(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x238/8])(m,p1); }
// Auto-generated named dispatchers
void CameraModule__reset_all_impl(BattleObjectModuleAccessor* a) { auto* m=CAMERA_MODULE(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x70/8])(m); }
void CameraModule__update_force_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3) { auto* m=CAMERA_MODULE(a); reinterpret_cast<void(*)(void*,u64,u64,u64)>(VT(m)[0x80/8])(m,p1,p2,p3); }
void CameraModule__set_enable_camera_impl(BattleObjectModuleAccessor* a,bool p1,u64 p2) { auto* m=CAMERA_MODULE(a); reinterpret_cast<void(*)(void*,bool,u64)>(VT(m)[0x88/8])(m,p1,p2); }
void CameraModule__set_whole_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=CAMERA_MODULE(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x90/8])(m,p1); }
void CameraModule__set_enable_update_pos_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=CAMERA_MODULE(a); reinterpret_cast<void(*)(void*,u64,u64)>(VT(m)[0x98/8])(m,p1,p2); }
void CameraModule__set_enable_interpolate_pos_impl(BattleObjectModuleAccessor* a,bool p1,u64 p2) { auto* m=CAMERA_MODULE(a); reinterpret_cast<void(*)(void*,bool,u64)>(VT(m)[0xa0/8])(m,p1,p2); }
void CameraModule__reset_camera_range_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=CAMERA_MODULE(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0xb8/8])(m,p1); }
void CameraModule__set_camera_range_offset_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=CAMERA_MODULE(a); reinterpret_cast<void(*)(void*,u64,u64)>(VT(m)[0xc0/8])(m,p1,p2); }
void* CameraModule__un_regist_camera_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=CAMERA_MODULE(a); return reinterpret_cast<void*(*)(void*,u64)>(VT(m)[0xe8/8])(m,p1); }
void* CameraModule__zoom_in_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3,bool p4) { auto* m=CAMERA_MODULE(a); return reinterpret_cast<void*(*)(void*,u64,u64,u64,bool)>(VT(m)[0xf0/8])(m,p1,p2,p3,p4); }
void* CameraModule__zoom_out_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=CAMERA_MODULE(a); return reinterpret_cast<void*(*)(void*,u64)>(VT(m)[0xf8/8])(m,p1); }
void CameraModule__set_status_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=CAMERA_MODULE(a); reinterpret_cast<void(*)(void*,u64,u64)>(VT(m)[0x128/8])(m,p1,p2); }
void CameraModule__set_priority_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=CAMERA_MODULE(a); reinterpret_cast<void(*)(void*,u64,u64)>(VT(m)[0x130/8])(m,p1,p2); }
void CameraModule__set_player_no_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=CAMERA_MODULE(a); reinterpret_cast<void(*)(void*,u64,u64)>(VT(m)[0x140/8])(m,p1,p2); }
void CameraModule__set_damage_fly_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=CAMERA_MODULE(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x160/8])(m,p1); }
void CameraModule__set_run_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=CAMERA_MODULE(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x170/8])(m,p1); }
void CameraModule__set_being_carried_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=CAMERA_MODULE(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x180/8])(m,p1); }
bool CameraModule__is_clip_in_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=CAMERA_MODULE(a); return reinterpret_cast<bool(*)(void*,bool)>(VT(m)[0x198/8])(m,p1); }
bool CameraModule__is_clip_in_all_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=CAMERA_MODULE(a); return reinterpret_cast<bool(*)(void*,bool)>(VT(m)[0x1a0/8])(m,p1); }
void CameraModule__set_camera_range_global_rect_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=CAMERA_MODULE(a); reinterpret_cast<void(*)(void*,u64,u64)>(VT(m)[0x1b8/8])(m,p1,p2); }
void* CameraModule__get_main_camera_target_pos_impl(BattleObjectModuleAccessor* a) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x60)); void* ret = reinterpret_cast<void*(*)(void*)>(VT(m)[0x1c8/8])(m); asm(""); return ret; }
void* CameraModule__get_internal_camera_target_pos_impl(BattleObjectModuleAccessor* a) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x60)); void* ret = reinterpret_cast<void*(*)(void*)>(VT(m)[0x1d8/8])(m); asm(""); return ret; }
void CameraModule__set_camera_type_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=CAMERA_MODULE(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x1f0/8])(m,p1); }
void* CameraModule__req_quake_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=CAMERA_MODULE(a); return reinterpret_cast<void*(*)(void*,u64)>(VT(m)[0x200/8])(m,p1); }
void* CameraModule__req_quake_pos_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=CAMERA_MODULE(a); return reinterpret_cast<void*(*)(void*,u64,u64)>(VT(m)[0x208/8])(m,p1,p2); }
void* CameraModule__stop_quake_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=CAMERA_MODULE(a); return reinterpret_cast<void*(*)(void*,u64)>(VT(m)[0x210/8])(m,p1); }
void* CameraModule__start_final_zoom_out_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3) { auto* m=CAMERA_MODULE(a); return reinterpret_cast<void*(*)(void*,u64,u64,u64)>(VT(m)[0x220/8])(m,p1,p2,p3); }
} // namespace app::lua_bind
