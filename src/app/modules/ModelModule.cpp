#include "app/BattleObjectModuleAccessor.h"
#define MM(a) (*reinterpret_cast<void**>(reinterpret_cast<u8*>(a) + 0x78))
#define TEAM_MODULE(a) MM(a)
#define VT(m) (*reinterpret_cast<void***>(m))
namespace app::lua_bind {
u32 ModelModule__rotation_order_impl(BattleObjectModuleAccessor* a) { auto* m=MM(a); return reinterpret_cast<u32(*)(void*)>(VT(m)[0xE8/8])(m); }
void* ModelModule__scale_impl(BattleObjectModuleAccessor* a) { auto* m=MM(a); return reinterpret_cast<void*(*)(void*)>(VT(m)[0xF0/8])(m); }
f32 ModelModule__scale_z_impl(BattleObjectModuleAccessor* a) { auto* m=MM(a); return reinterpret_cast<f32(*)(void*)>(VT(m)[0x100/8])(m); }
void* ModelModule__joint_global_position_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,bool p3) { auto* m=MM(a); return reinterpret_cast<void*(*)(void*,u64,u64,bool)>(VT(m)[0x150/8])(m,p1,p2,p3); }
void* ModelModule__joint_global_position_with_offset_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3,bool p4) { auto* m=MM(a); return reinterpret_cast<void*(*)(void*,u64,u64,u64,bool)>(VT(m)[0x158/8])(m,p1,p2,p3,p4); }
void* ModelModule__joint_global_offset_from_top_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x78)); return reinterpret_cast<void*(*)(void*,u64,u64)>(VT(m)[0x170/8])(m,p1,p2); }
void* ModelModule__joint_global_rotation_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,bool p3) { auto* m=MM(a); return reinterpret_cast<void*(*)(void*,u64,u64,bool)>(VT(m)[0x180/8])(m,p1,p2,p3); }
void* ModelModule__joint_global_axis_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,bool p3) { auto* m=MM(a); return reinterpret_cast<void*(*)(void*,u64,u64,bool)>(VT(m)[0x188/8])(m,p1,p2,p3); }
void ModelModule__clear_joint_srt_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=MM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x1B0/8])(m,p1); }
void* ModelModule__joint_rotate_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x78)); return reinterpret_cast<void*(*)(void*,u64,u64)>(VT(m)[0x1b8/8])(m,p1,p2); }
bool ModelModule__is_visible_impl(BattleObjectModuleAccessor* a) { auto* m=MM(a); return reinterpret_cast<bool(*)(void*)>(VT(m)[0x1C8/8])(m); }
void ModelModule__set_alpha_impl(BattleObjectModuleAccessor* a) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x78)); reinterpret_cast<void(*)(void*)>(VT(m)[0x1f0/8])(m); }
void ModelModule__set_color_rgb_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=MM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x1F8/8])(m,p1); }
void ModelModule__enable_gold_eye_impl(BattleObjectModuleAccessor* a) { auto* m=MM(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x358/8])(m); }
void ModelModule__disable_gold_eye_impl(BattleObjectModuleAccessor* a) { auto* m=MM(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x360/8])(m); }
// Additional ModelModule dispatchers
void ModelModule__set_rotation_order_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=MM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0xe0/8])(m,p1); }
void ModelModule__set_scale_impl(BattleObjectModuleAccessor* a) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x78)); reinterpret_cast<void(*)(void*)>(VT(m)[0xf8/8])(m); }
void ModelModule__set_scale_z_impl(BattleObjectModuleAccessor* a) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x78)); reinterpret_cast<void(*)(void*)>(VT(m)[0x108/8])(m); }
void ModelModule__set_temporary_scale_z_impl(BattleObjectModuleAccessor* a) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x78)); reinterpret_cast<void(*)(void*)>(VT(m)[0x110/8])(m); }
// Auto-generated named dispatchers
void* ModelModule__top_joint_global_position_from_joint_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3) { auto* m=TEAM_MODULE(a); return reinterpret_cast<void*(*)(void*,u64,u64,u64)>(VT(m)[0x178/8])(m,p1,p2,p3); }
void ModelModule__set_joint_srt_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3,u64 p4) { auto* m=TEAM_MODULE(a); reinterpret_cast<void(*)(void*,u64,u64,u64,u64)>(VT(m)[0x190/8])(m,p1,p2,p3,p4); }
void ModelModule__set_joint_scale_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=TEAM_MODULE(a); reinterpret_cast<void(*)(void*,u64,u64)>(VT(m)[0x198/8])(m,p1,p2); }
void ModelModule__set_joint_rotate_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3,u64 p4) { auto* m=TEAM_MODULE(a); reinterpret_cast<void(*)(void*,u64,u64,u64,u64)>(VT(m)[0x1a0/8])(m,p1,p2,p3,p4); }
void ModelModule__set_visibility_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=TEAM_MODULE(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x1c0/8])(m,p1); }
void ModelModule__set_mesh_visibility_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { auto* m=TEAM_MODULE(a); reinterpret_cast<void(*)(void*,u64,bool)>(VT(m)[0x1d0/8])(m,p1,p2); }
void ModelModule__set_emmisive_scale_impl(BattleObjectModuleAccessor* a) { auto* m=TEAM_MODULE(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x258/8])(m); }
void ModelModule__set_render_offset_position_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=TEAM_MODULE(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x2d8/8])(m,p1); }
void ModelModule__set_depth_offset_impl(BattleObjectModuleAccessor* a) { auto* m=TEAM_MODULE(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x2e8/8])(m); }
void ModelModule__set_depth_stencil_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=TEAM_MODULE(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x2f0/8])(m,p1); }
void* ModelModule__virtual_joint_tra_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=TEAM_MODULE(a); return reinterpret_cast<void*(*)(void*,u64)>(VT(m)[0x328/8])(m,p1); }
// Multi-bool dispatchers (auto-generated)
void ModelModule__set_joint_translate_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,bool p3,bool p4) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x78)); reinterpret_cast<void(*)(void*,u64,u64,bool,bool)>(VT(m)[0x1a8/8])(m,p1,p2,p3,p4); }
} // namespace app::lua_bind
