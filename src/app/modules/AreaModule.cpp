#include "app/BattleObjectModuleAccessor.h"
#include "app/modules/AreaModule.h"
// AreaModule shares accessor+0xC0 with FighterAreaModule (polymorphic)
#define AM(a) static_cast<AreaModule*>((a)->fighter_area_module)

namespace app::lua_bind {

void AreaModule__force_update_impl(BattleObjectModuleAccessor* a) { AM(a)->force_update(); }
void AreaModule__set_auto_layer_update_impl(BattleObjectModuleAccessor* a, bool p1) { AM(a)->set_auto_layer_update(p1); }
void AreaModule__clean_impl(BattleObjectModuleAccessor* a) { AM(a)->clean(); }
void AreaModule__set_layer_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2) { AM(a)->set_layer(p1, p2); }
void* AreaModule__layer_impl(BattleObjectModuleAccessor* a, u64 p1) { return AM(a)->layer(p1); }
void AreaModule__set_whole_impl(BattleObjectModuleAccessor* a, bool p1) { AM(a)->set_whole(p1); }
u32 AreaModule__get_whole_impl(BattleObjectModuleAccessor* a) { return AM(a)->get_whole(); }
void* AreaModule__get_group_impl(BattleObjectModuleAccessor* a, u64 p1) { return AM(a)->get_group(p1); }
u32 AreaModule__area_instance_size_impl(BattleObjectModuleAccessor* a) { return AM(a)->area_instance_size(); }
void AreaModule__enable_area_impl(BattleObjectModuleAccessor* a, u64 p1, bool p2, u64 p3) { AM(a)->enable_area(p1, p2, p3); }
bool AreaModule__is_enable_area_impl(BattleObjectModuleAccessor* a, u64 p1) { return AM(a)->is_enable_area(p1); }
void AreaModule__reset_area_impl(BattleObjectModuleAccessor* a, u64 p1) { AM(a)->reset_area(p1); }
void AreaModule__set_area_target_group_mask_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2) { AM(a)->set_area_target_group_mask(p1, p2); }
void AreaModule__set_area_target_local_group_mask_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2) { AM(a)->set_area_target_local_group_mask(p1, p2); }
void AreaModule__set_area_shape_aabb_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3) { AM(a)->set_area_shape_aabb(p1, p2, p3); }
void AreaModule__set_area_shape_circle_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2) { AM(a)->set_area_shape_circle(p1, p2); }
void AreaModule__set_area_shape_type_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2) { AM(a)->set_area_shape_type(p1, p2); }
void AreaModule__set_center_x0_impl(BattleObjectModuleAccessor* a, u64 p1, bool p2) { AM(a)->set_center_x0(p1, p2); }
u32 AreaModule__get_area_id_impl(BattleObjectModuleAccessor* a, u64 p1) { return AM(a)->get_area_id(p1); }
bool AreaModule__is_exist_area_instance_impl(BattleObjectModuleAccessor* a, u64 p1) { return AM(a)->is_exist_area_instance(p1); }
u32 AreaModule__get_area_index_from_id_impl(BattleObjectModuleAccessor* a, u64 p1) { return AM(a)->get_area_index_from_id(p1); }
u32 AreaModule__get_area_contact_count_impl(BattleObjectModuleAccessor* a, u64 p1) { return AM(a)->get_area_contact_count(p1); }
void* AreaModule__get_area_contact_log_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2) { return AM(a)->get_area_contact_log(p1, p2); }
u32 AreaModule__get_area_contact_target_id_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2) { return AM(a)->get_area_contact_target_id(p1, p2); }
void AreaModule__erase_wind_impl(BattleObjectModuleAccessor* a, u64 p1) { AM(a)->erase_wind(p1); }
void AreaModule__add_wind_area_2nd_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3, u64 p4) { AM(a)->add_wind_area_2nd(p1, p2, p3, p4); }
void AreaModule__add_wind_area_2nd_rad_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3) { AM(a)->add_wind_area_2nd_rad(p1, p2, p3); }
void AreaModule__sleep_impl(BattleObjectModuleAccessor* a, bool p1) { AM(a)->sleep(p1); }
bool AreaModule__is_sleep_impl(BattleObjectModuleAccessor* a) { return AM(a)->is_sleep(); }
bool AreaModule__is_water_impl(BattleObjectModuleAccessor* a) { return AM(a)->is_water(); }
u32 AreaModule__get_water_task_id_impl(BattleObjectModuleAccessor* a) { return AM(a)->get_water_task_id(); }
f32 AreaModule__get_water_surface_y_impl(BattleObjectModuleAccessor* a) { return AM(a)->get_water_surface_y(); }
void* AreaModule__test_water_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2) { return AM(a)->test_water(p1, p2); }

} // namespace app::lua_bind
