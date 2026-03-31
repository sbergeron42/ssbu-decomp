#include "app/BattleObjectModuleAccessor.h"
#define MM(a) (*reinterpret_cast<void**>(reinterpret_cast<u8*>(a) + 0x78))
#define VT(m) (*reinterpret_cast<void***>(m))
namespace app::lua_bind {
u32 ModelModule__rotation_order_impl(BattleObjectModuleAccessor* a) { auto* m=MM(a); return reinterpret_cast<u32(*)(void*)>(VT(m)[0xE8/8])(m); }
void* ModelModule__scale_impl(BattleObjectModuleAccessor* a) { auto* m=MM(a); return reinterpret_cast<void*(*)(void*)>(VT(m)[0xF0/8])(m); }
f32 ModelModule__scale_z_impl(BattleObjectModuleAccessor* a) { auto* m=MM(a); return reinterpret_cast<f32(*)(void*)>(VT(m)[0x100/8])(m); }
void* ModelModule__joint_global_position_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,bool p3) { auto* m=MM(a); return reinterpret_cast<void*(*)(void*,u64,u64,bool)>(VT(m)[0x150/8])(m,p1,p2,p3); }
void* ModelModule__joint_global_position_with_offset_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3,bool p4) { auto* m=MM(a); return reinterpret_cast<void*(*)(void*,u64,u64,u64,bool)>(VT(m)[0x158/8])(m,p1,p2,p3,p4); }
void* ModelModule__joint_global_offset_from_top_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=MM(a); return reinterpret_cast<void*(*)(void*,u64)>(VT(m)[0x170/8])(m,p1); }
void* ModelModule__joint_global_rotation_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,bool p3) { auto* m=MM(a); return reinterpret_cast<void*(*)(void*,u64,u64,bool)>(VT(m)[0x180/8])(m,p1,p2,p3); }
void* ModelModule__joint_global_axis_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,bool p3) { auto* m=MM(a); return reinterpret_cast<void*(*)(void*,u64,u64,bool)>(VT(m)[0x188/8])(m,p1,p2,p3); }
void ModelModule__clear_joint_srt_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=MM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x1B0/8])(m,p1); }
void ModelModule__joint_rotate_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=MM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x1B8/8])(m,p1); }
bool ModelModule__is_visible_impl(BattleObjectModuleAccessor* a) { auto* m=MM(a); return reinterpret_cast<bool(*)(void*)>(VT(m)[0x1C8/8])(m); }
void ModelModule__set_alpha_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=MM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x1F0/8])(m,p1); }
void ModelModule__set_color_rgb_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=MM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x1F8/8])(m,p1); }
void ModelModule__enable_gold_eye_impl(BattleObjectModuleAccessor* a) { auto* m=MM(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x358/8])(m); }
void ModelModule__disable_gold_eye_impl(BattleObjectModuleAccessor* a) { auto* m=MM(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x360/8])(m); }
// Additional ModelModule dispatchers
void ModelModule__set_rotation_order_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=MM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0xe0/8])(m,p1); }
void ModelModule__set_scale_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=MM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0xf8/8])(m,p1); }
void ModelModule__set_scale_z_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=MM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x108/8])(m,p1); }
void ModelModule__set_temporary_scale_z_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=MM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x110/8])(m,p1); }
} // namespace app::lua_bind
