#include "app/BattleObjectModuleAccessor.h"
// AreaModule shares accessor+0xC0 with FighterAreaModule (polymorphic)
#define AM(a) (a->fighter_area_module)
#define VT(m) (*reinterpret_cast<void***>(m))
namespace app::lua_bind {
void AreaModule__force_update_impl(BattleObjectModuleAccessor* a) { auto* m=AM(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x50/8])(m); }
void AreaModule__clean_impl(BattleObjectModuleAccessor* a) { auto* m=AM(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x70/8])(m); }
u32 AreaModule__get_group_impl(BattleObjectModuleAccessor* a) { auto* m=AM(a); return reinterpret_cast<u32(*)(void*)>(VT(m)[0xB0/8])(m); }
u32 AreaModule__area_instance_size_impl(BattleObjectModuleAccessor* a) { auto* m=AM(a); return reinterpret_cast<u32(*)(void*)>(VT(m)[0xB8/8])(m); }
void AreaModule__enable_area_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { auto* m=AM(a); reinterpret_cast<void(*)(void*,u64,bool)>(VT(m)[0xC0/8])(m,p1,p2); }
bool AreaModule__is_enable_area_impl(BattleObjectModuleAccessor* a) { auto* m=AM(a); return reinterpret_cast<bool(*)(void*)>(VT(m)[0xC8/8])(m); }
u32 AreaModule__get_area_id_impl(BattleObjectModuleAccessor* a) { auto* m=AM(a); return reinterpret_cast<u32(*)(void*)>(VT(m)[0x108/8])(m); }
bool AreaModule__is_exist_area_instance_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=AM(a); return reinterpret_cast<bool(*)(void*,u64)>(VT(m)[0x110/8])(m,p1); }
u32 AreaModule__get_area_index_from_id_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=AM(a); return reinterpret_cast<u32(*)(void*,u64)>(VT(m)[0x120/8])(m,p1); }
u32 AreaModule__get_area_contact_count_impl(BattleObjectModuleAccessor* a) { auto* m=AM(a); return reinterpret_cast<u32(*)(void*)>(VT(m)[0x128/8])(m); }
void* AreaModule__get_area_contact_log_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=AM(a); return reinterpret_cast<void*(*)(void*,u64)>(VT(m)[0x130/8])(m,p1); }
u32 AreaModule__get_area_contact_target_id_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=AM(a); return reinterpret_cast<u32(*)(void*,u64)>(VT(m)[0x138/8])(m,p1); }
void AreaModule__erase_wind_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=AM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x140/8])(m,p1); }
void AreaModule__add_wind_area_2nd_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=AM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x158/8])(m,p1); }
void AreaModule__add_wind_area_2nd_rad_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=AM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x160/8])(m,p1); }
bool AreaModule__is_sleep_impl(BattleObjectModuleAccessor* a) { auto* m=AM(a); return reinterpret_cast<bool(*)(void*)>(VT(m)[0x170/8])(m); }
bool AreaModule__is_water_impl(BattleObjectModuleAccessor* a) { auto* m=AM(a); return reinterpret_cast<bool(*)(void*)>(VT(m)[0x198/8])(m); }
u32 AreaModule__get_water_task_id_impl(BattleObjectModuleAccessor* a) { auto* m=AM(a); return reinterpret_cast<u32(*)(void*)>(VT(m)[0x1B0/8])(m); }
f32 AreaModule__get_water_surface_y_impl(BattleObjectModuleAccessor* a) { auto* m=AM(a); return reinterpret_cast<f32(*)(void*)>(VT(m)[0x1B8/8])(m); }
void AreaModule__set_auto_layer_update_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=AM(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x58/8])(m,p1); }
void AreaModule__set_layer_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=AM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x90/8])(m,p1); }
u32 AreaModule__layer_impl(BattleObjectModuleAccessor* a) { auto* m=AM(a); return reinterpret_cast<u32(*)(void*)>(VT(m)[0x98/8])(m); }
void AreaModule__set_whole_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=AM(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0xa0/8])(m,p1); }
u32 AreaModule__get_whole_impl(BattleObjectModuleAccessor* a) { auto* m=AM(a); return reinterpret_cast<u32(*)(void*)>(VT(m)[0xa8/8])(m); }
void AreaModule__reset_area_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=AM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0xd0/8])(m,p1); }
void AreaModule__set_area_target_group_mask_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=AM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0xd8/8])(m,p1); }
void AreaModule__set_area_target_local_group_mask_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=AM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0xe0/8])(m,p1); }
void AreaModule__set_area_shape_aabb_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=AM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0xe8/8])(m,p1); }
void AreaModule__set_area_shape_circle_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=AM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0xf0/8])(m,p1); }
void AreaModule__set_area_shape_type_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=AM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0xf8/8])(m,p1); }
void AreaModule__set_center_x0_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=AM(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x100/8])(m,p1); }
void AreaModule__sleep_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=AM(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x168/8])(m,p1); }
void AreaModule__test_water_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=AM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x1c8/8])(m,p1); }
} // namespace app::lua_bind
