#include "app/BattleObjectModuleAccessor.h"
#include "app/modules/GroundModule.h"

namespace app::lua_bind {

static inline GroundModule* GM(BattleObjectModuleAccessor* a) {
    return static_cast<GroundModule*>(a->ground_module);
}

// Shape / Update
void GroundModule__update_force_impl(BattleObjectModuleAccessor* a) {
    GM(a)->update_force();
}

void GroundModule__update_shape_impl(BattleObjectModuleAccessor* a, bool p1) {
    GM(a)->update_shape(p1);
}

void* GroundModule__get_rhombus_impl(BattleObjectModuleAccessor* a, bool p1) {
    void* ret = GM(a)->get_rhombus(p1);
    asm("");
    return ret;
}

void GroundModule__modify_rhombus_impl(BattleObjectModuleAccessor* a) {
    GM(a)->modify_rhombus();
}

// Circle / Offset
void GroundModule__set_init_circle_impl(BattleObjectModuleAccessor* a, u64 p1) {
    GM(a)->set_init_circle(p1);
}

f32 GroundModule__get_circle_radius_impl(BattleObjectModuleAccessor* a) {
    return GM(a)->get_circle_radius();
}

void GroundModule__set_offset_x_impl(BattleObjectModuleAccessor* a) {
    GM(a)->set_offset_x();
}

void GroundModule__set_offset_y_impl(BattleObjectModuleAccessor* a) {
    GM(a)->set_offset_y();
}

f32 GroundModule__get_offset_x_impl(BattleObjectModuleAccessor* a) {
    return GM(a)->get_offset_x();
}

f32 GroundModule__get_offset_y_impl(BattleObjectModuleAccessor* a) {
    return GM(a)->get_offset_y();
}

void GroundModule__set_rhombus_offset_impl(BattleObjectModuleAccessor* a, u64 p1) {
    GM(a)->set_rhombus_offset(p1);
}

void GroundModule__correct_impl(BattleObjectModuleAccessor* a, u64 p1) {
    GM(a)->correct(p1);
}

void GroundModule__set_correct_impl(BattleObjectModuleAccessor* a, u64 p1) {
    GM(a)->set_correct(p1);
}

u32 GroundModule__get_correct_impl(BattleObjectModuleAccessor* a) {
    return GM(a)->get_correct();
}

// Collision settings
void GroundModule__set_collidable_impl(BattleObjectModuleAccessor* a, bool p1) {
    GM(a)->set_collidable(p1);
}

void GroundModule__set_passable_check_impl(BattleObjectModuleAccessor* a, bool p1) {
    GM(a)->set_passable_check(p1);
}

bool GroundModule__is_passable_check_impl(BattleObjectModuleAccessor* a) {
    return GM(a)->is_passable_check();
}

void GroundModule__set_cloud_through_impl(BattleObjectModuleAccessor* a, bool p1) {
    GM(a)->set_cloud_through(p1);
}

void GroundModule__set_ignore_line_type1_impl(BattleObjectModuleAccessor* a, bool p1) {
    GM(a)->set_ignore_line_type1(p1);
}

void GroundModule__set_ignore_boss_impl(BattleObjectModuleAccessor* a, bool p1) {
    GM(a)->set_ignore_boss(p1);
}

bool GroundModule__is_ignore_fighter_other_impl(BattleObjectModuleAccessor* a) {
    return GM(a)->is_ignore_fighter_other();
}

void GroundModule__set_ignore_fighter_other_impl(BattleObjectModuleAccessor* a, bool p1) {
    GM(a)->set_ignore_fighter_other(p1);
}

bool GroundModule__is_ignore_fighter_other_wall_l_impl(BattleObjectModuleAccessor* a) {
    return GM(a)->is_ignore_fighter_other_wall_l();
}

bool GroundModule__is_ignore_fighter_other_wall_r_impl(BattleObjectModuleAccessor* a) {
    return GM(a)->is_ignore_fighter_other_wall_r();
}

void GroundModule__set_correct_ignore_slope_impl(BattleObjectModuleAccessor* a, bool p1) {
    GM(a)->set_correct_ignore_slope(p1);
}

// Cliff system
void GroundModule__set_cliff_check_impl(BattleObjectModuleAccessor* a, u64 p1) {
    GM(a)->set_cliff_check(p1);
}

u32 GroundModule__cliff_check_impl(BattleObjectModuleAccessor* a) {
    return GM(a)->cliff_check();
}

void GroundModule__select_cliff_hangdata_impl(BattleObjectModuleAccessor* a, u64 p1) {
    GM(a)->select_cliff_hangdata(p1);
}

bool GroundModule__is_status_cliff_impl(BattleObjectModuleAccessor* a) {
    return GM(a)->is_status_cliff();
}

void* GroundModule__correct_pos_impl(BattleObjectModuleAccessor* a) {
    void* ret = GM(a)->correct_pos();
    asm("");
    return ret;
}

void GroundModule__entry_cliff_impl(BattleObjectModuleAccessor* a) {
    GM(a)->entry_cliff();
}

void GroundModule__reentry_cliff_impl(BattleObjectModuleAccessor* a) {
    GM(a)->reentry_cliff();
}

bool GroundModule__can_entry_cliff_impl(BattleObjectModuleAccessor* a) {
    return GM(a)->can_entry_cliff();
}

bool GroundModule__can_entry_cliff_same_impl(BattleObjectModuleAccessor* a, u64 p1) {
    return GM(a)->can_entry_cliff_same(p1);
}

bool GroundModule__can_entry_cliff_hang_data_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2) {
    return GM(a)->can_entry_cliff_hang_data(p1, p2);
}

void GroundModule__leave_cliff_impl(BattleObjectModuleAccessor* a) {
    GM(a)->leave_cliff();
}

void* GroundModule__hang_cliff_pos_impl(BattleObjectModuleAccessor* a) {
    void* ret = GM(a)->hang_cliff_pos();
    asm("");
    return ret;
}

void* GroundModule__hang_cliff_pos_3f_impl(BattleObjectModuleAccessor* a) {
    return GM(a)->hang_cliff_pos_3f();
}

void* GroundModule__hang_can_entry_cliff_pos_impl(BattleObjectModuleAccessor* a) {
    void* ret = GM(a)->hang_can_entry_cliff_pos();
    asm("");
    return ret;
}

void* GroundModule__hang_cliff_dir_impl(BattleObjectModuleAccessor* a) {
    return GM(a)->hang_cliff_dir();
}

void* GroundModule__hang_can_entry_cliff_dir_impl(BattleObjectModuleAccessor* a) {
    return GM(a)->hang_can_entry_cliff_dir();
}

void* GroundModule__get_cliff_movement_speed_impl(BattleObjectModuleAccessor* a) {
    return GM(a)->get_cliff_movement_speed();
}

bool GroundModule__is_cliff_move_exception_impl(BattleObjectModuleAccessor* a) {
    return GM(a)->is_cliff_move_exception();
}

void GroundModule__clear_cliff_point_impl(BattleObjectModuleAccessor* a) {
    GM(a)->clear_cliff_point();
}

// Collision stop / Slide
void GroundModule__set_test_coll_stop_impl(BattleObjectModuleAccessor* a, bool p1) {
    GM(a)->set_test_coll_stop(p1);
}

void GroundModule__set_test_coll_stop_status_impl(BattleObjectModuleAccessor* a, bool p1) {
    GM(a)->set_test_coll_stop_status(p1);
}

void GroundModule__set_coll_stop_slidable_length_impl(BattleObjectModuleAccessor* a) {
    GM(a)->set_coll_stop_slidable_length();
}

void GroundModule__set_ignore_slide_up_impl(BattleObjectModuleAccessor* a, bool p1) {
    GM(a)->set_ignore_slide_up(p1);
}

// Ottotto / Edge detection
bool GroundModule__is_ottotto_impl(BattleObjectModuleAccessor* a) {
    return GM(a)->is_ottotto();
}

bool GroundModule__is_ottotto_lr_impl(BattleObjectModuleAccessor* a) {
    return GM(a)->is_ottotto_lr();
}

bool GroundModule__is_myground_nearcliff_impl(BattleObjectModuleAccessor* a) {
    return GM(a)->is_myground_nearcliff();
}

bool GroundModule__is_near_cliff_impl(BattleObjectModuleAccessor* a) {
    return GM(a)->is_near_cliff();
}

bool GroundModule__is_miss_foot_impl(BattleObjectModuleAccessor* a) {
    return GM(a)->is_miss_foot();
}

// Shape management
void GroundModule__set_shape_flag_impl(BattleObjectModuleAccessor* a, u64 p1, bool p2) {
    GM(a)->set_shape_flag(p1, p2);
}

void GroundModule__set_shape_safe_pos_impl(BattleObjectModuleAccessor* a, u64 p1) {
    GM(a)->set_shape_safe_pos(p1);
}

void* GroundModule__get_shape_safe_pos_impl(BattleObjectModuleAccessor* a) {
    void* ret = GM(a)->get_shape_safe_pos();
    asm("");
    return ret;
}

void GroundModule__set_status_ground_impl(BattleObjectModuleAccessor* a) {
    GM(a)->set_status_ground();
}

void GroundModule__set_shape_kind_impl(BattleObjectModuleAccessor* a, u64 p1) {
    GM(a)->set_shape_kind(p1);
}

void GroundModule__set_init_shape_kind_impl(BattleObjectModuleAccessor* a) {
    GM(a)->set_init_shape_kind();
}

u32 GroundModule__get_shape_kind_impl(BattleObjectModuleAccessor* a) {
    return GM(a)->get_shape_kind();
}

void GroundModule__set_z_impl(BattleObjectModuleAccessor* a) {
    GM(a)->set_z();
}

f32 GroundModule__get_z_impl(BattleObjectModuleAccessor* a) {
    return GM(a)->get_z();
}

// Attachment
void* GroundModule__attach_ground_impl(BattleObjectModuleAccessor* a, bool p1) {
    return GM(a)->attach_ground(p1);
}

void GroundModule__set_attach_ground_impl(BattleObjectModuleAccessor* a, bool p1) {
    GM(a)->set_attach_ground(p1);
}

bool GroundModule__is_attachable_impl(BattleObjectModuleAccessor* a, u64 p1) {
    return GM(a)->is_attachable(p1);
}

void GroundModule__attach_impl(BattleObjectModuleAccessor* a, u64 p1) {
    GM(a)->attach(p1);
}

bool GroundModule__is_attach_impl(BattleObjectModuleAccessor* a) {
    return GM(a)->is_attach();
}

void* GroundModule__get_line_movement_speed_impl(BattleObjectModuleAccessor* a, void* p1) {
    return GM(a)->get_line_movement_speed(p1);
}

void GroundModule__detach_impl(BattleObjectModuleAccessor* a, u64 p1) {
    GM(a)->detach(p1);
}

// Test / Touch normal
void* GroundModule__test_impl(BattleObjectModuleAccessor* a) {
    return GM(a)->test();
}

void* GroundModule__get_touch_normal_impl(BattleObjectModuleAccessor* a, u64 p1) {
    return GM(a)->get_touch_normal(p1);
}

void* GroundModule__get_touch_normal_x_impl(BattleObjectModuleAccessor* a, u64 p1) {
    return GM(a)->get_touch_normal_x(p1);
}

void* GroundModule__get_touch_normal_y_impl(BattleObjectModuleAccessor* a, u64 p1) {
    return GM(a)->get_touch_normal_y(p1);
}

void* GroundModule__get_touch_normal_consider_gravity_impl(BattleObjectModuleAccessor* a, u64 p1) {
    return GM(a)->get_touch_normal_consider_gravity(p1);
}

void* GroundModule__get_touch_normal_x_consider_gravity_impl(BattleObjectModuleAccessor* a, u64 p1) {
    return GM(a)->get_touch_normal_x_consider_gravity(p1);
}

void* GroundModule__get_touch_normal_y_consider_gravity_impl(BattleObjectModuleAccessor* a, u64 p1) {
    return GM(a)->get_touch_normal_y_consider_gravity(p1);
}

void* GroundModule__get_touch_normal_fixed_consider_gravity_impl(BattleObjectModuleAccessor* a, u64 p1) {
    return GM(a)->get_touch_normal_fixed_consider_gravity(p1);
}

void* GroundModule__get_touch_normal_for_touch_attack_data_impl(BattleObjectModuleAccessor* a, u64 p1) {
    return GM(a)->get_touch_normal_for_touch_attack_data(p1);
}

// Touch flags
u32 GroundModule__ground_touch_flag_impl(BattleObjectModuleAccessor* a) {
    return GM(a)->ground_touch_flag();
}

void* GroundModule__ground_touch_flag_ex_impl(BattleObjectModuleAccessor* a, bool p1, bool p2) {
    return GM(a)->ground_touch_flag_ex(p1, p2);
}

u32 GroundModule__get_touch_flag_impl(BattleObjectModuleAccessor* a) {
    return GM(a)->get_touch_flag();
}

u32 GroundModule__get_touch_moment_flag_impl(BattleObjectModuleAccessor* a) {
    return GM(a)->get_touch_moment_flag();
}

u32 GroundModule__get_touch_material_type_impl(BattleObjectModuleAccessor* a, u64 p1) {
    return GM(a)->get_touch_material_type(p1);
}

void* GroundModule__get_touch_pos_impl(BattleObjectModuleAccessor* a) {
    void* ret = GM(a)->get_touch_pos();
    asm("");
    return ret;
}

bool GroundModule__is_touch_impl(BattleObjectModuleAccessor* a, u64 p1) {
    return GM(a)->is_touch(p1);
}

void* GroundModule__get_touch_line_raw_impl(BattleObjectModuleAccessor* a, u64 p1) {
    return GM(a)->get_touch_line_raw(p1);
}

void* GroundModule__get_touch_wall_cliff_pos_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2) {
    return GM(a)->get_touch_wall_cliff_pos(p1, p2);
}

bool GroundModule__is_floor_touch_line_impl(BattleObjectModuleAccessor* a, u64 p1) {
    return GM(a)->is_floor_touch_line(p1);
}

bool GroundModule__is_wall_touch_line_impl(BattleObjectModuleAccessor* a, u64 p1) {
    return GM(a)->is_wall_touch_line(p1);
}

bool GroundModule__is_passable_ground_impl(BattleObjectModuleAccessor* a) {
    return GM(a)->is_passable_ground();
}

bool GroundModule__is_floor_vanishing_impl(BattleObjectModuleAccessor* a) {
    return GM(a)->is_floor_vanishing();
}

u32 GroundModule__get_cliff_id_uint32_impl(BattleObjectModuleAccessor* a) {
    return GM(a)->get_cliff_id_uint32();
}

// Positions
void* GroundModule__get_up_pos_impl(BattleObjectModuleAccessor* a) {
    return GM(a)->get_up_pos();
}

void* GroundModule__get_down_pos_impl(BattleObjectModuleAccessor* a) {
    return GM(a)->get_down_pos();
}

void* GroundModule__get_left_pos_impl(BattleObjectModuleAccessor* a) {
    return GM(a)->get_left_pos();
}

void* GroundModule__get_right_pos_impl(BattleObjectModuleAccessor* a) {
    return GM(a)->get_right_pos();
}

void* GroundModule__get_center_pos_impl(BattleObjectModuleAccessor* a) {
    return GM(a)->get_center_pos();
}

void* GroundModule__center_pos_impl(BattleObjectModuleAccessor* a) {
    return GM(a)->center_pos();
}

f32 GroundModule__get_width_impl(BattleObjectModuleAccessor* a) {
    return GM(a)->get_width();
}

void* GroundModule__get_down_movement_speed_impl(BattleObjectModuleAccessor* a) {
    return GM(a)->get_down_movement_speed();
}

void* GroundModule__check_down_correct_pos_impl(BattleObjectModuleAccessor* a) {
    return GM(a)->check_down_correct_pos();
}

void* GroundModule__get_latest_down_correct_pos_impl(BattleObjectModuleAccessor* a) {
    return GM(a)->get_latest_down_correct_pos();
}

void* GroundModule__get_down_correct_edge_pos_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2) {
    return GM(a)->get_down_correct_edge_pos(p1, p2);
}

f32 GroundModule__get_down_friction_impl(BattleObjectModuleAccessor* a) {
    return GM(a)->get_down_friction();
}

void GroundModule__get_distance_to_floor_impl(BattleObjectModuleAccessor* a, u64 p1, bool p2) {
    GM(a)->get_distance_to_floor(p1, p2);
}

void GroundModule__is_still_on_floor_impl(BattleObjectModuleAccessor* a, bool p1) {
    GM(a)->is_still_on_floor(p1);
}

// Ray check
void GroundModule__ray_check_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2, bool p3) {
    GM(a)->ray_check(p1, p2, p3);
}

void* GroundModule__ray_check_hit_pos_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3, bool p4) {
    return GM(a)->ray_check_hit_pos(p1, p2, p3, p4);
}

void* GroundModule__ray_check_hit_normal_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3, bool p4) {
    return GM(a)->ray_check_hit_normal(p1, p2, p3, p4);
}

void* GroundModule__ray_check_hit_pos_normal_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3, u64 p4, bool p5) {
    return GM(a)->ray_check_hit_pos_normal(p1, p2, p3, p4, p5);
}

void* GroundModule__ray_check_hit_pos_normal_no_culling_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3, u64 p4, bool p5) {
    return GM(a)->ray_check_hit_pos_normal_no_culling(p1, p2, p3, p4, p5);
}

void* GroundModule__ray_check_hit_pos_target_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3, u64 p4, bool p5) {
    return GM(a)->ray_check_hit_pos_target(p1, p2, p3, p4, p5);
}

bool GroundModule__ray_check_get_line_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2, bool p3) {
    return GM(a)->ray_check_get_line(p1, p2, p3);
}

bool GroundModule__ray_check_get_line_no_culling_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2, bool p3) {
    return GM(a)->ray_check_get_line_no_culling(p1, p2, p3);
}

void* GroundModule__ray_check_get_line_hit_pos_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3, bool p4) {
    return GM(a)->ray_check_get_line_hit_pos(p1, p2, p3, p4);
}

void* GroundModule__ray_check_get_line_hit_pos_no_culling_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3, bool p4) {
    return GM(a)->ray_check_get_line_hit_pos_no_culling(p1, p2, p3, p4);
}

void* GroundModule__ray_check_get_line_target_any_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3, bool p4) {
    return GM(a)->ray_check_get_line_target_any(p1, p2, p3, p4);
}

void* GroundModule__ray_check_get_line_target_any_no_culling_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3, bool p4) {
    return GM(a)->ray_check_get_line_target_any_no_culling(p1, p2, p3, p4);
}

void* GroundModule__ray_check_get_line_ignore_any_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3) {
    return GM(a)->ray_check_get_line_ignore_any(p1, p2, p3);
}

void* GroundModule__ray_check_get_line_ignore_any_no_culling_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3) {
    return GM(a)->ray_check_get_line_ignore_any_no_culling(p1, p2, p3);
}

void* GroundModule__ray_check_get_line_hit_pos_ignore_any_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3, u64 p4) {
    return GM(a)->ray_check_get_line_hit_pos_ignore_any(p1, p2, p3, p4);
}

void* GroundModule__ray_check_get_line_hit_pos_ignore_any_no_culling_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3, u64 p4) {
    return GM(a)->ray_check_get_line_hit_pos_ignore_any_no_culling(p1, p2, p3, p4);
}

void* GroundModule__ray_check_get_line_hit_pos_target_any_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3, u64 p4, bool p5) {
    return GM(a)->ray_check_get_line_hit_pos_target_any(p1, p2, p3, p4, p5);
}

void* GroundModule__line_segment_check_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3, u64 p4, bool p5) {
    return GM(a)->line_segment_check(p1, p2, p3, p4, p5);
}

// Ground test / Friction / Correct pos
void* GroundModule__test_ground_impl(BattleObjectModuleAccessor* a) {
    return GM(a)->test_ground();
}

void GroundModule__set_ignore_friction_impl(BattleObjectModuleAccessor* a, bool p1) {
    GM(a)->set_ignore_friction(p1);
}

void* GroundModule__get_correct_pos_impl(BattleObjectModuleAccessor* a) {
    return GM(a)->get_correct_pos();
}

void GroundModule__set_correct_pos_impl(BattleObjectModuleAccessor* a, u64 p1) {
    GM(a)->set_correct_pos(p1);
}

void* GroundModule__get_correct_pos_local_impl(BattleObjectModuleAccessor* a) {
    return GM(a)->get_correct_pos_local();
}

void GroundModule__set_update_shape_impl(BattleObjectModuleAccessor* a, bool p1) {
    GM(a)->set_update_shape(p1);
}

// Cliff attachment / Pass floor
bool GroundModule__is_attach_cliff_impl(BattleObjectModuleAccessor* a) {
    return GM(a)->is_attach_cliff();
}

void* GroundModule__pass_floor_impl(BattleObjectModuleAccessor* a) {
    return GM(a)->pass_floor();
}

void GroundModule__clear_pass_floor_impl(BattleObjectModuleAccessor* a) {
    GM(a)->clear_pass_floor();
}

void GroundModule__set_auto_detach_impl(BattleObjectModuleAccessor* a, bool p1) {
    GM(a)->set_auto_detach(p1);
}

void GroundModule__set_no_cliff_stop_energy_impl(BattleObjectModuleAccessor* a, u64 p1) {
    GM(a)->set_no_cliff_stop_energy(p1);
}

void* GroundModule__ignore_recovery_impl(BattleObjectModuleAccessor* a) {
    return GM(a)->ignore_recovery();
}

void GroundModule__enable_recovery_impl(BattleObjectModuleAccessor* a) {
    GM(a)->enable_recovery();
}

// Collision mode / Rhombus
void GroundModule__set_gr_collision_mode_impl(BattleObjectModuleAccessor* a, bool p1) {
    GM(a)->set_gr_collision_mode(p1);
}

void* GroundModule__get_shape_data_rhombus_modify_node_offset_impl(BattleObjectModuleAccessor* a, u64 p1) {
    return GM(a)->get_shape_data_rhombus_modify_node_offset(p1);
}

void GroundModule__update_lr_impl(BattleObjectModuleAccessor* a) {
    GM(a)->update_lr();
}

void GroundModule__set_shape_data_rhombus_modify_node_offset_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2) {
    GM(a)->set_shape_data_rhombus_modify_node_offset(p1, p2);
}

void GroundModule__set_keep_distant_cliff_impl(BattleObjectModuleAccessor* a, bool p1) {
    GM(a)->set_keep_distant_cliff(p1);
}

void GroundModule__set_reverse_direction_impl(BattleObjectModuleAccessor* a, bool p1, bool p2) {
    GM(a)->set_reverse_direction(p1, p2);
}

void GroundModule__set_rhombus_modify_air_lasso_impl(BattleObjectModuleAccessor* a, bool p1) {
    GM(a)->set_rhombus_modify_air_lasso(p1);
}

void GroundModule__set_rhombus_modify_impl(BattleObjectModuleAccessor* a, u64 p1) {
    GM(a)->set_rhombus_modify(p1);
}

void GroundModule__set_is_ignore_geometry_move_power_impl(BattleObjectModuleAccessor* a, bool p1) {
    GM(a)->set_is_ignore_geometry_move_power(p1);
}

} // namespace app::lua_bind
