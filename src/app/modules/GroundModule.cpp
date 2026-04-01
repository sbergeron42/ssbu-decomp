#include "app/BattleObjectModuleAccessor.h"
// GroundModule — accessor+0x58
#define GM(a) (a->ground_module)
#define VT(m) (*reinterpret_cast<void***>(m))
namespace app::lua_bind {
// Pure dispatchers (4 instructions)
void GroundModule__set_init_circle_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=GM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x100/8])(m,p1); }
f32 GroundModule__get_circle_radius_impl(BattleObjectModuleAccessor* a) { auto* m=GM(a); return reinterpret_cast<f32(*)(void*)>(VT(m)[0x118/8])(m); }
f32 GroundModule__get_offset_x_impl(BattleObjectModuleAccessor* a) { auto* m=GM(a); return reinterpret_cast<f32(*)(void*)>(VT(m)[0x130/8])(m); }
f32 GroundModule__get_offset_y_impl(BattleObjectModuleAccessor* a) { auto* m=GM(a); return reinterpret_cast<f32(*)(void*)>(VT(m)[0x138/8])(m); }
void GroundModule__correct_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=GM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x148/8])(m,p1); }
void GroundModule__set_correct_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=GM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x150/8])(m,p1); }
u32 GroundModule__get_correct_impl(BattleObjectModuleAccessor* a) { auto* m=GM(a); return reinterpret_cast<u32(*)(void*)>(VT(m)[0x158/8])(m); }
bool GroundModule__is_passable_check_impl(BattleObjectModuleAccessor* a) { auto* m=GM(a); return reinterpret_cast<bool(*)(void*)>(VT(m)[0x198/8])(m); }
bool GroundModule__is_ignore_fighter_other_impl(BattleObjectModuleAccessor* a) { auto* m=GM(a); return reinterpret_cast<bool(*)(void*)>(VT(m)[0x1f0/8])(m); }
bool GroundModule__is_ignore_fighter_other_wall_l_impl(BattleObjectModuleAccessor* a) { auto* m=GM(a); return reinterpret_cast<bool(*)(void*)>(VT(m)[0x200/8])(m); }
bool GroundModule__is_ignore_fighter_other_wall_r_impl(BattleObjectModuleAccessor* a) { auto* m=GM(a); return reinterpret_cast<bool(*)(void*)>(VT(m)[0x208/8])(m); }
void GroundModule__set_cliff_check_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=GM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x218/8])(m,p1); }
u32 GroundModule__cliff_check_impl(BattleObjectModuleAccessor* a) { auto* m=GM(a); return reinterpret_cast<u32(*)(void*)>(VT(m)[0x220/8])(m); }
bool GroundModule__is_status_cliff_impl(BattleObjectModuleAccessor* a) { auto* m=GM(a); return reinterpret_cast<bool(*)(void*)>(VT(m)[0x240/8])(m); }
void GroundModule__entry_cliff_impl(BattleObjectModuleAccessor* a) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x58)); reinterpret_cast<void(*)(void*)>(VT(m)[0x250/8])(m); }
bool GroundModule__can_entry_cliff_impl(BattleObjectModuleAccessor* a) { auto* m=GM(a); return reinterpret_cast<bool(*)(void*)>(VT(m)[0x260/8])(m); }
bool GroundModule__can_entry_cliff_same_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x58)); return reinterpret_cast<bool(*)(void*,u64)>(VT(m)[0x268/8])(m,p1); }
bool GroundModule__can_entry_cliff_hang_data_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x58)); return reinterpret_cast<bool(*)(void*,u64,u64)>(VT(m)[0x270/8])(m,p1,p2); }
void* GroundModule__get_cliff_movement_speed_impl(BattleObjectModuleAccessor* a) { auto* m=GM(a); return reinterpret_cast<void*(*)(void*)>(VT(m)[0x2a8/8])(m); }
bool GroundModule__is_cliff_move_exception_impl(BattleObjectModuleAccessor* a) { auto* m=GM(a); return reinterpret_cast<bool(*)(void*)>(VT(m)[0x2b0/8])(m); }
void GroundModule__clear_cliff_point_impl(BattleObjectModuleAccessor* a) { auto* m=GM(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x2c8/8])(m); }
void GroundModule__set_coll_stop_slidable_length_impl(BattleObjectModuleAccessor* a) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x58)); reinterpret_cast<void(*)(void*)>(VT(m)[0x2e0/8])(m); }
bool GroundModule__is_ottotto_impl(BattleObjectModuleAccessor* a) { auto* m=GM(a); return reinterpret_cast<bool(*)(void*)>(VT(m)[0x300/8])(m); }
bool GroundModule__is_ottotto_lr_impl(BattleObjectModuleAccessor* a) { auto* m=GM(a); return reinterpret_cast<bool(*)(void*)>(VT(m)[0x308/8])(m); }
bool GroundModule__is_myground_nearcliff_impl(BattleObjectModuleAccessor* a) { auto* m=GM(a); return reinterpret_cast<bool(*)(void*)>(VT(m)[0x310/8])(m); }
bool GroundModule__is_near_cliff_impl(BattleObjectModuleAccessor* a) { auto* m=GM(a); return reinterpret_cast<bool(*)(void*)>(VT(m)[0x318/8])(m); }
bool GroundModule__is_miss_foot_impl(BattleObjectModuleAccessor* a) { auto* m=GM(a); return reinterpret_cast<bool(*)(void*)>(VT(m)[0x320/8])(m); }
void GroundModule__set_init_shape_kind_impl(BattleObjectModuleAccessor* a) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x58)); reinterpret_cast<void(*)(void*)>(VT(m)[0x370/8])(m); }
u32 GroundModule__get_shape_kind_impl(BattleObjectModuleAccessor* a) { auto* m=GM(a); return reinterpret_cast<u32(*)(void*)>(VT(m)[0x378/8])(m); }
bool GroundModule__is_attachable_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x58)); return reinterpret_cast<bool(*)(void*,u64)>(VT(m)[0x3b0/8])(m,p1); }
void GroundModule__attach_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=GM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x3b8/8])(m,p1); }
bool GroundModule__is_attach_impl(BattleObjectModuleAccessor* a) { auto* m=GM(a); return reinterpret_cast<bool(*)(void*)>(VT(m)[0x3c8/8])(m); }
void* GroundModule__get_line_movement_speed_impl(BattleObjectModuleAccessor* a,void* p1) { auto* m=GM(a); return reinterpret_cast<void*(*)(void*,void*)>(VT(m)[0x3d0/8])(m,p1); }
void GroundModule__detach_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=GM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x3e8/8])(m,p1); }
void* GroundModule__get_touch_normal_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=GM(a); return reinterpret_cast<void*(*)(void*,u64)>(VT(m)[0x408/8])(m,p1); }
void* GroundModule__get_touch_normal_consider_gravity_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=GM(a); return reinterpret_cast<void*(*)(void*,u64)>(VT(m)[0x420/8])(m,p1); }
void* GroundModule__get_touch_normal_fixed_consider_gravity_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=GM(a); return reinterpret_cast<void*(*)(void*,u64)>(VT(m)[0x440/8])(m,p1); }
void* GroundModule__get_touch_normal_for_touch_attack_data_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=GM(a); return reinterpret_cast<void*(*)(void*,u64)>(VT(m)[0x448/8])(m,p1); }
u32 GroundModule__get_touch_flag_impl(BattleObjectModuleAccessor* a) { auto* m=GM(a); return reinterpret_cast<u32(*)(void*)>(VT(m)[0x468/8])(m); }
u32 GroundModule__get_touch_moment_flag_impl(BattleObjectModuleAccessor* a) { auto* m=GM(a); return reinterpret_cast<u32(*)(void*)>(VT(m)[0x470/8])(m); }
u32 GroundModule__get_touch_material_type_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=GM(a); return reinterpret_cast<u32(*)(void*,u64)>(VT(m)[0x478/8])(m,p1); }
bool GroundModule__is_touch_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=GM(a); return reinterpret_cast<bool(*)(void*,u64)>(VT(m)[0x4a0/8])(m,p1); }
void* GroundModule__get_touch_line_raw_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=GM(a); return reinterpret_cast<void*(*)(void*,u64)>(VT(m)[0x4d8/8])(m,p1); }
bool GroundModule__is_floor_touch_line_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=GM(a); return reinterpret_cast<bool(*)(void*,u64)>(VT(m)[0x4e8/8])(m,p1); }
bool GroundModule__is_wall_touch_line_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=GM(a); return reinterpret_cast<bool(*)(void*,u64)>(VT(m)[0x4f0/8])(m,p1); }
bool GroundModule__is_passable_ground_impl(BattleObjectModuleAccessor* a) { auto* m=GM(a); return reinterpret_cast<bool(*)(void*)>(VT(m)[0x4f8/8])(m); }
bool GroundModule__is_floor_vanishing_impl(BattleObjectModuleAccessor* a) { auto* m=GM(a); return reinterpret_cast<bool(*)(void*)>(VT(m)[0x518/8])(m); }
u32 GroundModule__get_cliff_id_uint32_impl(BattleObjectModuleAccessor* a) { auto* m=GM(a); return reinterpret_cast<u32(*)(void*)>(VT(m)[0x568/8])(m); }
void* GroundModule__get_down_pos_impl(BattleObjectModuleAccessor* a) { auto* m=GM(a); return reinterpret_cast<void*(*)(void*)>(VT(m)[0x580/8])(m); }
void* GroundModule__get_left_pos_impl(BattleObjectModuleAccessor* a) { auto* m=GM(a); return reinterpret_cast<void*(*)(void*)>(VT(m)[0x588/8])(m); }
void* GroundModule__get_right_pos_impl(BattleObjectModuleAccessor* a) { auto* m=GM(a); return reinterpret_cast<void*(*)(void*)>(VT(m)[0x590/8])(m); }
void* GroundModule__get_center_pos_impl(BattleObjectModuleAccessor* a) { auto* m=GM(a); return reinterpret_cast<void*(*)(void*)>(VT(m)[0x598/8])(m); }
void* GroundModule__center_pos_impl(BattleObjectModuleAccessor* a) { auto* m=GM(a); return reinterpret_cast<void*(*)(void*)>(VT(m)[0x5a0/8])(m); }
void* GroundModule__get_down_movement_speed_impl(BattleObjectModuleAccessor* a) { auto* m=GM(a); return reinterpret_cast<void*(*)(void*)>(VT(m)[0x5b0/8])(m); }
void* GroundModule__check_down_correct_pos_impl(BattleObjectModuleAccessor* a) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x58)); return reinterpret_cast<void*(*)(void*)>(VT(m)[0x5c0/8])(m); }
void* GroundModule__get_latest_down_correct_pos_impl(BattleObjectModuleAccessor* a) { auto* m=GM(a); return reinterpret_cast<void*(*)(void*)>(VT(m)[0x5c8/8])(m); }
void* GroundModule__get_down_correct_edge_pos_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x58)); return reinterpret_cast<void*(*)(void*,u64,u64)>(VT(m)[0x5f0/8])(m,p1,p2); }
f32 GroundModule__get_down_friction_impl(BattleObjectModuleAccessor* a) { auto* m=GM(a); return reinterpret_cast<f32(*)(void*)>(VT(m)[0x5f8/8])(m); }
void* GroundModule__get_correct_pos_impl(BattleObjectModuleAccessor* a) { auto* m=GM(a); return reinterpret_cast<void*(*)(void*)>(VT(m)[0x6c8/8])(m); }
void GroundModule__set_correct_pos_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=GM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x6d0/8])(m,p1); }
void* GroundModule__get_correct_pos_local_impl(BattleObjectModuleAccessor* a) { auto* m=GM(a); return reinterpret_cast<void*(*)(void*)>(VT(m)[0x6d8/8])(m); }
bool GroundModule__is_attach_cliff_impl(BattleObjectModuleAccessor* a) { auto* m=GM(a); return reinterpret_cast<bool(*)(void*)>(VT(m)[0x710/8])(m); }
void GroundModule__clear_pass_floor_impl(BattleObjectModuleAccessor* a) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x58)); reinterpret_cast<void(*)(void*)>(VT(m)[0x730/8])(m); }
void GroundModule__set_no_cliff_stop_energy_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=GM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x788/8])(m,p1); }
void GroundModule__enable_recovery_impl(BattleObjectModuleAccessor* a) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x58)); reinterpret_cast<void(*)(void*)>(VT(m)[0x7a0/8])(m); }
void* GroundModule__get_shape_data_rhombus_modify_node_offset_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=GM(a); return reinterpret_cast<void*(*)(void*,u64)>(VT(m)[0x7b0/8])(m,p1); }
// Bool-mask dispatchers (5 instructions, and wN #1)
void GroundModule__set_collidable_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=GM(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x168/8])(m,p1); }
void GroundModule__set_cloud_through_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=GM(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x1a8/8])(m,p1); }
void GroundModule__set_ignore_line_type1_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=GM(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x1e0/8])(m,p1); }
void GroundModule__set_ignore_boss_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=GM(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x1e8/8])(m,p1); }
void GroundModule__set_ignore_fighter_other_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=GM(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x1f8/8])(m,p1); }
void GroundModule__set_correct_ignore_slope_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=GM(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x210/8])(m,p1); }
void GroundModule__set_ignore_slide_up_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=GM(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x2f0/8])(m,p1); }
void* GroundModule__attach_ground_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x58)); return reinterpret_cast<void*(*)(void*,bool)>(VT(m)[0x398/8])(m,p1); }
void GroundModule__set_attach_ground_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x58)); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x3a8/8])(m,p1); }
void GroundModule__get_distance_to_floor_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { auto* m=GM(a); reinterpret_cast<void(*)(void*,u64,bool)>(VT(m)[0x600/8])(m,p1,p2); }
void GroundModule__is_still_on_floor_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=GM(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x608/8])(m,p1); }
void GroundModule__set_ignore_friction_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=GM(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x6c0/8])(m,p1); }
// 710202a3d0
void GroundModule__set_auto_detach_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=GM(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x750/8])(m,p1); }
// 710202a420
void GroundModule__set_gr_collision_mode_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x58)); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x7a8/8])(m,p1); }
void GroundModule__set_keep_distant_cliff_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x58)); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x7d0/8])(m,p1); }
void GroundModule__set_is_ignore_geometry_move_power_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=GM(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x818/8])(m,p1); }
// Remaining GroundModule dispatchers from agent data
// 7102029900
void GroundModule__v0x80(BattleObjectModuleAccessor* a,u64 p1) { auto* m=GM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x80/8])(m,p1); }
void GroundModule__v0x88(BattleObjectModuleAccessor* a,bool p1) { auto* m=GM(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x88/8])(m,p1); }
// 7102029960
void GroundModule__v0xc0(BattleObjectModuleAccessor* a,u64 p1) { auto* m=GM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0xc0/8])(m,p1); }
// 7102029990
void GroundModule__v0x120(BattleObjectModuleAccessor* a,u64 p1) { auto* m=GM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x120/8])(m,p1); }
// 71020299a0
void GroundModule__v0x128(BattleObjectModuleAccessor* a,u64 p1) { auto* m=GM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x128/8])(m,p1); }
void GroundModule__v0x140(BattleObjectModuleAccessor* a,u64 p1) { auto* m=GM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x140/8])(m,p1); }
void GroundModule__v0x190(BattleObjectModuleAccessor* a,bool p1) { auto* m=GM(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x190/8])(m,p1); }
void GroundModule__v0x228(BattleObjectModuleAccessor* a,u64 p1) { auto* m=GM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x228/8])(m,p1); }
// 7102029ba0
void GroundModule__v0x258(BattleObjectModuleAccessor* a,u64 p1) { auto* m=GM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x258/8])(m,p1); }
// 7102029be0
void GroundModule__v0x278(BattleObjectModuleAccessor* a,u64 p1) { auto* m=GM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x278/8])(m,p1); }
// 7102029c10
void GroundModule__v0x288(BattleObjectModuleAccessor* a,u64 p1) { auto* m=GM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x288/8])(m,p1); }
// 7102029c40
void GroundModule__v0x298(BattleObjectModuleAccessor* a,u64 p1) { auto* m=GM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x298/8])(m,p1); }
// 7102029c50
void GroundModule__v0x2a0(BattleObjectModuleAccessor* a,u64 p1) { auto* m=GM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x2a0/8])(m,p1); }
void GroundModule__v0x2d0(BattleObjectModuleAccessor* a,bool p1) { auto* m=GM(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x2d0/8])(m,p1); }
void GroundModule__v0x2d8(BattleObjectModuleAccessor* a,bool p1) { auto* m=GM(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x2d8/8])(m,p1); }
void GroundModule__v0x338(BattleObjectModuleAccessor* a,u64 p1,bool p2) { auto* m=GM(a); reinterpret_cast<void(*)(void*,u64,bool)>(VT(m)[0x338/8])(m,p1,p2); }
void GroundModule__v0x348(BattleObjectModuleAccessor* a,u64 p1) { auto* m=GM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x348/8])(m,p1); }
// 7102029da0
void GroundModule__v0x360(BattleObjectModuleAccessor* a,u64 p1) { auto* m=GM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x360/8])(m,p1); }
void GroundModule__v0x368(BattleObjectModuleAccessor* a,u64 p1) { auto* m=GM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x368/8])(m,p1); }
// 7102029de0
void GroundModule__v0x380(BattleObjectModuleAccessor* a,u64 p1) { auto* m=GM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x380/8])(m,p1); }
// 7102029df0
void GroundModule__v0x388(BattleObjectModuleAccessor* a,u64 p1) { auto* m=GM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x388/8])(m,p1); }
// 7102029e90
void GroundModule__v0x400(BattleObjectModuleAccessor* a,u64 p1) { auto* m=GM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x400/8])(m,p1); }
void GroundModule__v0x410(BattleObjectModuleAccessor* a,u64 p1) { auto* m=GM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x410/8])(m,p1); }
void GroundModule__v0x418(BattleObjectModuleAccessor* a,u64 p1) { auto* m=GM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x418/8])(m,p1); }
void GroundModule__v0x430(BattleObjectModuleAccessor* a,u64 p1) { auto* m=GM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x430/8])(m,p1); }
void GroundModule__v0x438(BattleObjectModuleAccessor* a,u64 p1) { auto* m=GM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x438/8])(m,p1); }
// 7102029f20
void GroundModule__v0x458(BattleObjectModuleAccessor* a,u64 p1) { auto* m=GM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x458/8])(m,p1); }
void GroundModule__v0x460(BattleObjectModuleAccessor* a,u64 p1,bool p2,bool p3) { auto* m=GM(a); reinterpret_cast<void(*)(void*,u64,bool,bool)>(VT(m)[0x460/8])(m,p1,p2,p3); }
// 7102029fc0
void GroundModule__v0x4e0(BattleObjectModuleAccessor* a,u64 p1) { auto* m=GM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x4e0/8])(m,p1); }
// 710202a020
void GroundModule__v0x578(BattleObjectModuleAccessor* a,u64 p1) { auto* m=GM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x578/8])(m,p1); }
// 710202a080
void GroundModule__v0x5a8(BattleObjectModuleAccessor* a,u64 p1) { auto* m=GM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x5a8/8])(m,p1); }
void GroundModule__v0x618(BattleObjectModuleAccessor* a,u64 p1,u64 p2,bool p3) { auto* m=GM(a); reinterpret_cast<void(*)(void*,u64,u64,bool)>(VT(m)[0x618/8])(m,p1,p2,p3); }
void GroundModule__v0x620(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3,bool p4) { auto* m=GM(a); reinterpret_cast<void(*)(void*,u64,u64,u64,bool)>(VT(m)[0x620/8])(m,p1,p2,p3,p4); }
void GroundModule__v0x628(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3,bool p4) { auto* m=GM(a); reinterpret_cast<void(*)(void*,u64,u64,u64,bool)>(VT(m)[0x628/8])(m,p1,p2,p3,p4); }
void GroundModule__v0x630(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3,u64 p4,bool p5) { auto* m=GM(a); reinterpret_cast<void(*)(void*,u64,u64,u64,u64,bool)>(VT(m)[0x630/8])(m,p1,p2,p3,p4,p5); }
void GroundModule__v0x638(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3,u64 p4,bool p5) { auto* m=GM(a); reinterpret_cast<void(*)(void*,u64,u64,u64,u64,bool)>(VT(m)[0x638/8])(m,p1,p2,p3,p4,p5); }
void GroundModule__v0x640(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3,u64 p4,bool p5) { auto* m=GM(a); reinterpret_cast<void(*)(void*,u64,u64,u64,u64,bool)>(VT(m)[0x640/8])(m,p1,p2,p3,p4,p5); }
void GroundModule__v0x648(BattleObjectModuleAccessor* a,u64 p1,u64 p2,bool p3) { auto* m=GM(a); reinterpret_cast<void(*)(void*,u64,u64,bool)>(VT(m)[0x648/8])(m,p1,p2,p3); }
void GroundModule__v0x650(BattleObjectModuleAccessor* a,u64 p1,u64 p2,bool p3) { auto* m=GM(a); reinterpret_cast<void(*)(void*,u64,u64,bool)>(VT(m)[0x650/8])(m,p1,p2,p3); }
void GroundModule__v0x658(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3,bool p4) { auto* m=GM(a); reinterpret_cast<void(*)(void*,u64,u64,u64,bool)>(VT(m)[0x658/8])(m,p1,p2,p3,p4); }
void GroundModule__v0x668(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3,bool p4) { auto* m=GM(a); reinterpret_cast<void(*)(void*,u64,u64,u64,bool)>(VT(m)[0x668/8])(m,p1,p2,p3,p4); }
void GroundModule__v0x670(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3,bool p4) { auto* m=GM(a); reinterpret_cast<void(*)(void*,u64,u64,u64,bool)>(VT(m)[0x670/8])(m,p1,p2,p3,p4); }
void GroundModule__v0x678(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3,bool p4) { auto* m=GM(a); reinterpret_cast<void(*)(void*,u64,u64,u64,bool)>(VT(m)[0x678/8])(m,p1,p2,p3,p4); }
// 710202a2a0
void GroundModule__v0x680(BattleObjectModuleAccessor* a,u64 p1) { auto* m=GM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x680/8])(m,p1); }
// 710202a2b0
void GroundModule__v0x688(BattleObjectModuleAccessor* a,u64 p1) { auto* m=GM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x688/8])(m,p1); }
// 710202a2c0
void GroundModule__v0x690(BattleObjectModuleAccessor* a,u64 p1) { auto* m=GM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x690/8])(m,p1); }
void GroundModule__v0x6a0(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3,u64 p4,bool p5) { auto* m=GM(a); reinterpret_cast<void(*)(void*,u64,u64,u64,u64,bool)>(VT(m)[0x6a0/8])(m,p1,p2,p3,p4,p5); }
void GroundModule__v0x6a8(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3,u64 p4,bool p5) { auto* m=GM(a); reinterpret_cast<void(*)(void*,u64,u64,u64,u64,bool)>(VT(m)[0x6a8/8])(m,p1,p2,p3,p4,p5); }
// 710202a320
void GroundModule__v0x6b8(BattleObjectModuleAccessor* a,u64 p1) { auto* m=GM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x6b8/8])(m,p1); }
void GroundModule__v0x6e0(BattleObjectModuleAccessor* a,bool p1) { auto* m=GM(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x6e0/8])(m,p1); }
// 710202a3b0
void GroundModule__v0x728(BattleObjectModuleAccessor* a,u64 p1) { auto* m=GM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x728/8])(m,p1); }
void GroundModule__v0x750(BattleObjectModuleAccessor* a,bool p1) { auto* m=GM(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x750/8])(m,p1); }
// 710202a400
void GroundModule__v0x798(BattleObjectModuleAccessor* a,u64 p1) { auto* m=GM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x798/8])(m,p1); }
void GroundModule__v0x7a8b(BattleObjectModuleAccessor* a,bool p1) { auto* m=GM(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x7a8/8])(m,p1); }
// 710202a450
void GroundModule__v0x7b8(BattleObjectModuleAccessor* a,u64 p1) { auto* m=GM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x7b8/8])(m,p1); }
// 710202a460
void GroundModule__v0x7c0(BattleObjectModuleAccessor* a,u64 p1) { auto* m=GM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x7c0/8])(m,p1); }
// Auto-generated named dispatchers
void GroundModule__update_force_impl(BattleObjectModuleAccessor* a) { auto* m=GM(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x80/8])(m); }
void* GroundModule__get_rhombus_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=GM(a); void* ret=reinterpret_cast<void*(*)(void*,bool)>(VT(m)[0xb8/8])(m,p1); asm(""); return ret; }
// 7102029910
void GroundModule__update_shape_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=GM(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x88/8])(m,p1); }
void GroundModule__modify_rhombus_impl(BattleObjectModuleAccessor* a) { auto* m=GM(a); reinterpret_cast<void(*)(void*)>(VT(m)[0xc0/8])(m); }
void GroundModule__set_offset_x_impl(BattleObjectModuleAccessor* a) { auto* m=GM(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x120/8])(m); }
void GroundModule__set_offset_y_impl(BattleObjectModuleAccessor* a) { auto* m=GM(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x128/8])(m); }
// 71020299d0
void GroundModule__set_rhombus_offset_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=GM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x140/8])(m,p1); }
// 7102029a30
void GroundModule__set_passable_check_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=GM(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x190/8])(m,p1); }
// 7102029b50
void GroundModule__select_cliff_hangdata_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=GM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x228/8])(m,p1); }
void* GroundModule__correct_pos_impl(BattleObjectModuleAccessor* a) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x58)); void* ret = reinterpret_cast<void*(*)(void*)>(VT(m)[0x248/8])(m); asm(""); return ret; }
void GroundModule__reentry_cliff_impl(BattleObjectModuleAccessor* a) { auto* m=GM(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x258/8])(m); }
void GroundModule__leave_cliff_impl(BattleObjectModuleAccessor* a) { auto* m=GM(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x278/8])(m); }
void* GroundModule__hang_cliff_pos_impl(BattleObjectModuleAccessor* a) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x58)); void* ret = reinterpret_cast<void*(*)(void*)>(VT(m)[0x280/8])(m); asm(""); return ret; }
void* GroundModule__hang_cliff_pos_3f_impl(BattleObjectModuleAccessor* a) { auto* m=GM(a); return reinterpret_cast<void*(*)(void*)>(VT(m)[0x288/8])(m); }
void* GroundModule__hang_can_entry_cliff_pos_impl(BattleObjectModuleAccessor* a) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x58)); void* ret = reinterpret_cast<void*(*)(void*)>(VT(m)[0x290/8])(m); asm(""); return ret; }
void* GroundModule__hang_cliff_dir_impl(BattleObjectModuleAccessor* a) { auto* m=GM(a); return reinterpret_cast<void*(*)(void*)>(VT(m)[0x298/8])(m); }
void* GroundModule__hang_can_entry_cliff_dir_impl(BattleObjectModuleAccessor* a) { auto* m=GM(a); return reinterpret_cast<void*(*)(void*)>(VT(m)[0x2a0/8])(m); }
// 7102029c90
void GroundModule__set_test_coll_stop_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=GM(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x2d0/8])(m,p1); }
// 7102029cb0
void GroundModule__set_test_coll_stop_status_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=GM(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x2d8/8])(m,p1); }
// 7102029d50
void GroundModule__set_shape_flag_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { auto* m=GM(a); reinterpret_cast<void(*)(void*,u64,bool)>(VT(m)[0x338/8])(m,p1,p2); }
void GroundModule__set_shape_safe_pos_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=GM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x348/8])(m,p1); }
void* GroundModule__get_shape_safe_pos_impl(BattleObjectModuleAccessor* a) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x58)); void* ret = reinterpret_cast<void*(*)(void*)>(VT(m)[0x358/8])(m); asm(""); return ret; }
void GroundModule__set_status_ground_impl(BattleObjectModuleAccessor* a) { auto* m=GM(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x360/8])(m); }
// 7102029db0
void GroundModule__set_shape_kind_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=GM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x368/8])(m,p1); }
void GroundModule__set_z_impl(BattleObjectModuleAccessor* a) { auto* m=GM(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x380/8])(m); }
f32 GroundModule__get_z_impl(BattleObjectModuleAccessor* a) { auto* m=GM(a); return reinterpret_cast<f32(*)(void*)>(VT(m)[0x388/8])(m); }
void* GroundModule__test_impl(BattleObjectModuleAccessor* a) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x58)); return reinterpret_cast<void*(*)(void*)>(VT(m)[0x400/8])(m); }
// 7102029eb0
void* GroundModule__get_touch_normal_x_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=GM(a); return reinterpret_cast<void*(*)(void*,u64)>(VT(m)[0x410/8])(m,p1); }
// 7102029ec0
void* GroundModule__get_touch_normal_y_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=GM(a); return reinterpret_cast<void*(*)(void*,u64)>(VT(m)[0x418/8])(m,p1); }
void* GroundModule__get_touch_normal_x_consider_gravity_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=GM(a); return reinterpret_cast<void*(*)(void*,u64)>(VT(m)[0x430/8])(m,p1); }
// 7102029ef0
void* GroundModule__get_touch_normal_y_consider_gravity_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=GM(a); return reinterpret_cast<void*(*)(void*,u64)>(VT(m)[0x438/8])(m,p1); }
u32 GroundModule__ground_touch_flag_impl(BattleObjectModuleAccessor* a) { auto* m=GM(a); return reinterpret_cast<u32(*)(void*)>(VT(m)[0x458/8])(m); }
void* GroundModule__get_touch_pos_impl(BattleObjectModuleAccessor* a) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x58)); void* ret = reinterpret_cast<void*(*)(void*)>(VT(m)[0x480/8])(m); asm(""); return ret; }
void* GroundModule__get_touch_wall_cliff_pos_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x58)); return reinterpret_cast<void*(*)(void*,u64,u64)>(VT(m)[0x4e0/8])(m,p1,p2); }
void* GroundModule__get_up_pos_impl(BattleObjectModuleAccessor* a) { auto* m=GM(a); return reinterpret_cast<void*(*)(void*)>(VT(m)[0x578/8])(m); }
f32 GroundModule__get_width_impl(BattleObjectModuleAccessor* a) { auto* m=GM(a); return reinterpret_cast<f32(*)(void*)>(VT(m)[0x5a8/8])(m); }
// 710202a120
void GroundModule__ray_check_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,bool p3) { auto* m=GM(a); reinterpret_cast<void(*)(void*,u64,u64,bool)>(VT(m)[0x618/8])(m,p1,p2,p3); }
// 710202a140
void* GroundModule__ray_check_hit_pos_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3,bool p4) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x58)); return reinterpret_cast<void*(*)(void*,u64,u64,u64,bool)>(VT(m)[0x620/8])(m,p1,p2,p3,p4); }
void* GroundModule__ray_check_hit_normal_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3,bool p4) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x58)); return reinterpret_cast<void*(*)(void*,u64,u64,u64,bool)>(VT(m)[0x628/8])(m,p1,p2,p3,p4); }
// 710202a180
void* GroundModule__ray_check_hit_pos_normal_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3,u64 p4,bool p5) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x58)); return reinterpret_cast<void*(*)(void*,u64,u64,u64,u64,bool)>(VT(m)[0x630/8])(m,p1,p2,p3,p4,p5); }
// 710202a1a0
void* GroundModule__ray_check_hit_pos_normal_no_culling_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3,u64 p4,bool p5) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x58)); return reinterpret_cast<void*(*)(void*,u64,u64,u64,u64,bool)>(VT(m)[0x638/8])(m,p1,p2,p3,p4,p5); }
void* GroundModule__ray_check_hit_pos_target_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3,u64 p4,bool p5) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x58)); return reinterpret_cast<void*(*)(void*,u64,u64,u64,u64,bool)>(VT(m)[0x640/8])(m,p1,p2,p3,p4,p5); }
// 710202a1e0
bool GroundModule__ray_check_get_line_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,bool p3) { auto* m=GM(a); return reinterpret_cast<bool(*)(void*,u64,u64,bool)>(VT(m)[0x648/8])(m,p1,p2,p3); }
// 710202a200
bool GroundModule__ray_check_get_line_no_culling_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,bool p3) { auto* m=GM(a); return reinterpret_cast<bool(*)(void*,u64,u64,bool)>(VT(m)[0x650/8])(m,p1,p2,p3); }
// 710202a220
void* GroundModule__ray_check_get_line_hit_pos_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3,bool p4) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x58)); return reinterpret_cast<void*(*)(void*,u64,u64,u64,bool)>(VT(m)[0x658/8])(m,p1,p2,p3,p4); }
// 710202a240
void* GroundModule__ray_check_get_line_hit_pos_no_culling_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3,bool p4) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x58)); return reinterpret_cast<void*(*)(void*,u64,u64,u64,bool)>(VT(m)[0x668/8])(m,p1,p2,p3,p4); }
// 710202a260
void* GroundModule__ray_check_get_line_target_any_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3,bool p4) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x58)); return reinterpret_cast<void*(*)(void*,u64,u64,u64,bool)>(VT(m)[0x670/8])(m,p1,p2,p3,p4); }
// 710202a280
void* GroundModule__ray_check_get_line_target_any_no_culling_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3,bool p4) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x58)); return reinterpret_cast<void*(*)(void*,u64,u64,u64,bool)>(VT(m)[0x678/8])(m,p1,p2,p3,p4); }
void* GroundModule__ray_check_get_line_ignore_any_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x58)); return reinterpret_cast<void*(*)(void*,u64,u64,u64)>(VT(m)[0x680/8])(m,p1,p2,p3); }
void* GroundModule__ray_check_get_line_ignore_any_no_culling_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x58)); return reinterpret_cast<void*(*)(void*,u64,u64,u64)>(VT(m)[0x688/8])(m,p1,p2,p3); }
void* GroundModule__ray_check_get_line_hit_pos_ignore_any_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3,u64 p4) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x58)); return reinterpret_cast<void*(*)(void*,u64,u64,u64,u64)>(VT(m)[0x690/8])(m,p1,p2,p3,p4); }
void* GroundModule__ray_check_get_line_hit_pos_ignore_any_no_culling_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3,u64 p4) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x58)); return reinterpret_cast<void*(*)(void*,u64,u64,u64,u64)>(VT(m)[0x698/8])(m,p1,p2,p3,p4); }
// 710202a2e0
void* GroundModule__ray_check_get_line_hit_pos_target_any_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3,u64 p4,bool p5) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x58)); return reinterpret_cast<void*(*)(void*,u64,u64,u64,u64,bool)>(VT(m)[0x6a0/8])(m,p1,p2,p3,p4,p5); }
// 710202a300
void* GroundModule__line_segment_check_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3,u64 p4,bool p5) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x58)); return reinterpret_cast<void*(*)(void*,u64,u64,u64,u64,bool)>(VT(m)[0x6a8/8])(m,p1,p2,p3,p4,p5); }
void* GroundModule__test_ground_impl(BattleObjectModuleAccessor* a) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x58)); return reinterpret_cast<void*(*)(void*)>(VT(m)[0x6b8/8])(m); }
// 710202a380
void GroundModule__set_update_shape_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x58)); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x6e0/8])(m,p1); }
void* GroundModule__pass_floor_impl(BattleObjectModuleAccessor* a) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x58)); return reinterpret_cast<void*(*)(void*)>(VT(m)[0x728/8])(m); }
void* GroundModule__ignore_recovery_impl(BattleObjectModuleAccessor* a) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x58)); return reinterpret_cast<void*(*)(void*)>(VT(m)[0x798/8])(m); }
void GroundModule__update_lr_impl(BattleObjectModuleAccessor* a) { auto* m=GM(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x7b8/8])(m); }
void GroundModule__set_shape_data_rhombus_modify_node_offset_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x58)); reinterpret_cast<void(*)(void*,u64,u64)>(VT(m)[0x7c0/8])(m,p1,p2); }
void GroundModule__set_rhombus_modify_air_lasso_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x58)); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x7f8/8])(m,p1); }
void GroundModule__set_rhombus_modify_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=GM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x800/8])(m,p1); }
// Multi-bool dispatchers (auto-generated)
void* GroundModule__ground_touch_flag_ex_impl(BattleObjectModuleAccessor* a,bool p1,bool p2) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x58)); return reinterpret_cast<void*(*)(void*,bool,bool)>(VT(m)[0x460/8])(m,p1,p2); }
void GroundModule__set_reverse_direction_impl(BattleObjectModuleAccessor* a,bool p1,bool p2) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x58)); reinterpret_cast<void(*)(void*,bool,bool)>(VT(m)[0x7d8/8])(m,p1,p2); }
} // namespace app::lua_bind
