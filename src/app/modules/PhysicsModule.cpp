#include "app/BattleObjectModuleAccessor.h"
#include "app/modules/PhysicsModule.h"
#define PM(a) static_cast<PhysicsModule*>((a)->physics_module)
namespace app::lua_bind {
// -- Named dispatchers with asm symbol overrides --
u32 PhysicsModule__get_2nd_node_num_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind36PhysicsModule__get_2nd_node_num_implEPNS_26BattleObjectModuleAccessorEy");
u32 PhysicsModule__get_2nd_node_num_impl(BattleObjectModuleAccessor* a) { return PM(a)->get_2nd_node_num(); }
u32 PhysicsModule__get_2nd_active_node_num_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind43PhysicsModule__get_2nd_active_node_num_implEPNS_26BattleObjectModuleAccessorEy");
u32 PhysicsModule__get_2nd_active_node_num_impl(BattleObjectModuleAccessor* a) { return PM(a)->get_2nd_active_node_num(); }
void* PhysicsModule__get_2nd_active_length_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind41PhysicsModule__get_2nd_active_length_implEPNS_26BattleObjectModuleAccessorEy");
void* PhysicsModule__get_2nd_active_length_impl(BattleObjectModuleAccessor* a) { return PM(a)->get_2nd_active_length(); }
u32 PhysicsModule__get_2nd_joint_num_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind37PhysicsModule__get_2nd_joint_num_implEPNS_26BattleObjectModuleAccessorEy");
u32 PhysicsModule__get_2nd_joint_num_impl(BattleObjectModuleAccessor* a) { return PM(a)->get_2nd_joint_num(); }
void PhysicsModule__clear_2nd_speed_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind35PhysicsModule__clear_2nd_speed_implEPNS_26BattleObjectModuleAccessorEy");
void PhysicsModule__clear_2nd_speed_impl(BattleObjectModuleAccessor* a) { PM(a)->clear_2nd_speed(); }
// -- Simple dispatchers --
u32 PhysicsModule__get_2nd_status_impl(BattleObjectModuleAccessor* a) { return PM(a)->get_2nd_status(); }
f32 PhysicsModule__get_2nd_line_length_impl(BattleObjectModuleAccessor* a,u64 p1) { return PM(a)->get_2nd_line_length(p1); }
u32 PhysicsModule__get_2nd_joint_id_impl(BattleObjectModuleAccessor* a,u64 p1) { return PM(a)->get_2nd_joint_id(p1); }
void* PhysicsModule__get_2nd_pos_impl(BattleObjectModuleAccessor* a,u64 p1) { return PM(a)->get_2nd_pos(p1); }
void* PhysicsModule__get_2nd_speed_impl(BattleObjectModuleAccessor* a,u64 p1) { return PM(a)->get_2nd_speed(p1); }
// -- Swing --
void PhysicsModule__reset_swing_impl(BattleObjectModuleAccessor* a) { PM(a)->reset_swing(); }
void PhysicsModule__set_swing_only_anim_impl(BattleObjectModuleAccessor* a,bool p1) { PM(a)->set_swing_only_anim(p1); }
void PhysicsModule__set_swing_wind_impl(BattleObjectModuleAccessor* a,bool p1) { PM(a)->set_swing_wind(p1); }
void PhysicsModule__set_swing_rate_impl(BattleObjectModuleAccessor* a) { PM(a)->set_swing_rate(); }
void PhysicsModule__set_swing_rebirth_impl(BattleObjectModuleAccessor* a,bool p1) { PM(a)->set_swing_rebirth(p1); }
// -- 2nd-order simulation --
void PhysicsModule__set_2nd_gravity_impl(BattleObjectModuleAccessor* a) { PM(a)->set_2nd_gravity(); }
void PhysicsModule__set_2nd_status_impl(BattleObjectModuleAccessor* a,u64 p1) { PM(a)->set_2nd_status(p1); }
void PhysicsModule__set_2nd_end_pos_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { PM(a)->set_2nd_end_pos(p1,p2); }
void PhysicsModule__set_2nd_line_length_all_impl(BattleObjectModuleAccessor* a) { PM(a)->set_2nd_line_length_all(); }
void PhysicsModule__set_2nd_active_node_num_impl(BattleObjectModuleAccessor* a) { PM(a)->set_2nd_active_node_num(); }
// -- Precede/flip --
bool PhysicsModule__is_2nd_precede_impl(BattleObjectModuleAccessor* a) { return PM(a)->is_2nd_precede(); }
void PhysicsModule__set_2nd_precede_impl(BattleObjectModuleAccessor* a,bool p1) { PM(a)->set_2nd_precede(p1); }
bool PhysicsModule__is_2nd_flip_impl(BattleObjectModuleAccessor* a) { return PM(a)->is_2nd_flip(); }
void PhysicsModule__set_2nd_flip_impl(BattleObjectModuleAccessor* a,bool p1) { PM(a)->set_2nd_flip(p1); }
void PhysicsModule__set_2nd_back_speed_impl(BattleObjectModuleAccessor* a) { PM(a)->set_2nd_back_speed(); }
// -- IK --
void PhysicsModule__set_ik_impl(BattleObjectModuleAccessor* a,u64 p1) { PM(a)->set_ik(p1); }
void PhysicsModule__set_ik_target_pos_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3) { PM(a)->set_ik_target_pos(p1,p2,p3); }
void PhysicsModule__set_ik_target_dir_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3) { PM(a)->set_ik_target_dir(p1,p2,p3); }
u32 PhysicsModule__get_ik_end_joint_id_impl(BattleObjectModuleAccessor* a,u64 p1) { return PM(a)->get_ik_end_joint_id(p1); }
// -- Charge/resistance --
void* PhysicsModule__stop_charge_impl(BattleObjectModuleAccessor* a) { return PM(a)->stop_charge(); }
void PhysicsModule__set_2nd_air_resistance_impl(BattleObjectModuleAccessor* a) { PM(a)->set_2nd_air_resistance(); }
void PhysicsModule__set_2nd_air_resistance_2_impl(BattleObjectModuleAccessor* a,u64 p1) { PM(a)->set_2nd_air_resistance_2(p1); }
void PhysicsModule__set_2nd_water_resistance_impl(BattleObjectModuleAccessor* a) { PM(a)->set_2nd_water_resistance(); }
// -- Tension/joints --
void* PhysicsModule__get_2nd_tension_impl(BattleObjectModuleAccessor* a) { return PM(a)->get_2nd_tension(); }
void PhysicsModule__set_2nd_collision_size_impl(BattleObjectModuleAccessor* a,u64 p1) { PM(a)->set_2nd_collision_size(p1); }
void PhysicsModule__set_2nd_mass_impl(BattleObjectModuleAccessor* a,u64 p1) { PM(a)->set_2nd_mass(p1); }
// -- Collision --
void PhysicsModule__set_2nd_disable_collision_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { PM(a)->set_2nd_disable_collision(p1,p2); }
void PhysicsModule__set_2nd_fix_flag_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { PM(a)->set_2nd_fix_flag(p1,p2); }
void PhysicsModule__set_reflect_param_wall_impl(BattleObjectModuleAccessor* a) { PM(a)->set_reflect_param_wall(); }
void PhysicsModule__set_reflect_param_ceil_impl(BattleObjectModuleAccessor* a) { PM(a)->set_reflect_param_ceil(); }
void PhysicsModule__set_reflect_param_floor_impl(BattleObjectModuleAccessor* a) { PM(a)->set_reflect_param_floor(); }
// -- Length/pos/speed --
void PhysicsModule__set_2nd_length_impl(BattleObjectModuleAccessor* a,u64 p1) { PM(a)->set_2nd_length(p1); }
void PhysicsModule__set_2nd_pos_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { PM(a)->set_2nd_pos(p1,p2); }
void PhysicsModule__set_2nd_speed_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { PM(a)->set_2nd_speed(p1,p2); }
// -- Node/collision config --
void PhysicsModule__set_2nd_node_num_max_impl(BattleObjectModuleAccessor* a,u64 p1) { PM(a)->set_2nd_node_num_max(p1); }
void PhysicsModule__set_2nd_collision_object_impl(BattleObjectModuleAccessor* a,bool p1) { PM(a)->set_2nd_collision_object(p1); }
void PhysicsModule__set_2nd_sync_gravity_impl(BattleObjectModuleAccessor* a,bool p1) { PM(a)->set_2nd_sync_gravity(p1); }
void PhysicsModule__set_2nd_restitution_range_impl(BattleObjectModuleAccessor* a) { PM(a)->set_2nd_restitution_range(); }
void PhysicsModule__set_2nd_restitution_rate_impl(BattleObjectModuleAccessor* a) { PM(a)->set_2nd_restitution_rate(); }
void PhysicsModule__set_2nd_restitution_rate_2_impl(BattleObjectModuleAccessor* a,u64 p1) { PM(a)->set_2nd_restitution_rate_2(p1); }
void PhysicsModule__set_2nd_friction_rate_impl(BattleObjectModuleAccessor* a,u64 p1) { PM(a)->set_2nd_friction_rate(p1); }
// -- Misc params --
void PhysicsModule__set_2nd_fixed_tip_num_impl(BattleObjectModuleAccessor* a,u64 p1) { PM(a)->set_2nd_fixed_tip_num(p1); }
void PhysicsModule__set_2nd_z_range_impl(BattleObjectModuleAccessor* a) { PM(a)->set_2nd_z_range(); }
u32 PhysicsModule__get_2nd_touch_ground_line_num_impl(BattleObjectModuleAccessor* a,u64 p1) { return PM(a)->get_2nd_touch_ground_line_num(p1); }
// -- Floor collision/swing ground --
void PhysicsModule__set_enable_floor_collision_line_impl(BattleObjectModuleAccessor* a,u64 p1) { PM(a)->set_enable_floor_collision_line(p1); }
void PhysicsModule__set_swing_ground_collision_all_impl(BattleObjectModuleAccessor* a,bool p1) { PM(a)->set_swing_ground_collision_all(p1); }
void PhysicsModule__set_swing_special_state_impl(BattleObjectModuleAccessor* a,u64 p1) { PM(a)->set_swing_special_state(p1); }
// -- Unnamed dispatchers --
void PhysicsModule__v0x60(BattleObjectModuleAccessor* a,bool p1,bool p2) { PM(a)->_v0x60(p1,p2); }
void PhysicsModule__v0xc0(BattleObjectModuleAccessor* a,bool p1,u64 p2,bool p3) { PM(a)->_v0xc0(p1,p2,p3); }
} // namespace app::lua_bind
