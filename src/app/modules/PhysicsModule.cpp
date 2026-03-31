#include "app/BattleObjectModuleAccessor.h"
#define PM(a) (*reinterpret_cast<void**>(reinterpret_cast<u8*>(a) + 0x80))
#define SLOW_MODULE(a) PM(a)
#define VT(m) (*reinterpret_cast<void***>(m))
namespace app::lua_bind {
u32 PhysicsModule__get_2nd_status_impl(BattleObjectModuleAccessor* a) { auto* m=PM(a); return reinterpret_cast<u32(*)(void*)>(VT(m)[0x118/8])(m); }
f32 PhysicsModule__get_2nd_line_length_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=PM(a); return reinterpret_cast<f32(*)(void*,u64)>(VT(m)[0x130/8])(m,p1); }
u32 PhysicsModule__get_2nd_node_num_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind36PhysicsModule__get_2nd_node_num_implEPNS_26BattleObjectModuleAccessorEy");
u32 PhysicsModule__get_2nd_node_num_impl(BattleObjectModuleAccessor* a) { auto* m=PM(a); return reinterpret_cast<u32(*)(void*)>(VT(m)[0x150/8])(m); }
u32 PhysicsModule__get_2nd_active_node_num_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind43PhysicsModule__get_2nd_active_node_num_implEPNS_26BattleObjectModuleAccessorEy");
u32 PhysicsModule__get_2nd_active_node_num_impl(BattleObjectModuleAccessor* a) { auto* m=PM(a); return reinterpret_cast<u32(*)(void*)>(VT(m)[0x158/8])(m); }
void* PhysicsModule__get_2nd_active_length_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind41PhysicsModule__get_2nd_active_length_implEPNS_26BattleObjectModuleAccessorEy");
void* PhysicsModule__get_2nd_active_length_impl(BattleObjectModuleAccessor* a) { auto* m=PM(a); return reinterpret_cast<void*(*)(void*)>(VT(m)[0x160/8])(m); }
u32 PhysicsModule__get_2nd_joint_num_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind37PhysicsModule__get_2nd_joint_num_implEPNS_26BattleObjectModuleAccessorEy");
u32 PhysicsModule__get_2nd_joint_num_impl(BattleObjectModuleAccessor* a) { auto* m=PM(a); return reinterpret_cast<u32(*)(void*)>(VT(m)[0x248/8])(m); }
u32 PhysicsModule__get_2nd_joint_id_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=PM(a); return reinterpret_cast<u32(*)(void*,u64)>(VT(m)[0x250/8])(m,p1); }
void* PhysicsModule__get_2nd_pos_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=PM(a); return reinterpret_cast<void*(*)(void*,u64)>(VT(m)[0x2A8/8])(m,p1); }
void* PhysicsModule__get_2nd_speed_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=PM(a); return reinterpret_cast<void*(*)(void*,u64)>(VT(m)[0x2B8/8])(m,p1); }
void PhysicsModule__clear_2nd_speed_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind35PhysicsModule__clear_2nd_speed_implEPNS_26BattleObjectModuleAccessorEy");
void PhysicsModule__clear_2nd_speed_impl(BattleObjectModuleAccessor* a) { auto* m=PM(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x2e8/8])(m); }
// Remaining PhysicsModule dispatchers
void PhysicsModule__v0x60(BattleObjectModuleAccessor* a,bool p1,bool p2) { auto* m=PM(a); reinterpret_cast<void(*)(void*,bool,bool)>(VT(m)[0x60/8])(m,p1,p2); }
void PhysicsModule__v0x88(BattleObjectModuleAccessor* a,u64 p1) { auto* m=PM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x88/8])(m,p1); }
void PhysicsModule__v0xa8(BattleObjectModuleAccessor* a,bool p1) { auto* m=PM(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0xa8/8])(m,p1); }
void PhysicsModule__v0xc0(BattleObjectModuleAccessor* a,bool p1,u64 p2,bool p3) { auto* m=PM(a); reinterpret_cast<void(*)(void*,bool,u64,bool)>(VT(m)[0xc0/8])(m,p1,p2,p3); }
void PhysicsModule__v0xc8(BattleObjectModuleAccessor* a,bool p1) { auto* m=PM(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0xc8/8])(m,p1); }
void PhysicsModule__v0xf0(BattleObjectModuleAccessor* a,u64 p1) { auto* m=PM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0xf0/8])(m,p1); }
void PhysicsModule__v0xf8(BattleObjectModuleAccessor* a,bool p1) { auto* m=PM(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0xf8/8])(m,p1); }
void PhysicsModule__v0x100(BattleObjectModuleAccessor* a,u64 p1) { auto* m=PM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x100/8])(m,p1); }
void PhysicsModule__v0x110(BattleObjectModuleAccessor* a,u64 p1) { auto* m=PM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x110/8])(m,p1); }
void PhysicsModule__v0x120(BattleObjectModuleAccessor* a,u64 p1) { auto* m=PM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x120/8])(m,p1); }
void PhysicsModule__v0x140(BattleObjectModuleAccessor* a,u64 p1) { auto* m=PM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x140/8])(m,p1); }
void PhysicsModule__v0x168(BattleObjectModuleAccessor* a,u64 p1) { auto* m=PM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x168/8])(m,p1); }
void PhysicsModule__v0x178(BattleObjectModuleAccessor* a,u64 p1) { auto* m=PM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x178/8])(m,p1); }
void PhysicsModule__v0x180(BattleObjectModuleAccessor* a,bool p1) { auto* m=PM(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x180/8])(m,p1); }
void PhysicsModule__v0x190(BattleObjectModuleAccessor* a,u64 p1) { auto* m=PM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x190/8])(m,p1); }
void PhysicsModule__v0x198(BattleObjectModuleAccessor* a,bool p1) { auto* m=PM(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x198/8])(m,p1); }
void PhysicsModule__v0x1b0(BattleObjectModuleAccessor* a,u64 p1) { auto* m=PM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x1b0/8])(m,p1); }
void PhysicsModule__v0x1d0(BattleObjectModuleAccessor* a,u64 p1) { auto* m=PM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x1d0/8])(m,p1); }
void PhysicsModule__v0x1d8(BattleObjectModuleAccessor* a,u64 p1) { auto* m=PM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x1d8/8])(m,p1); }
void PhysicsModule__v0x1e0(BattleObjectModuleAccessor* a,u64 p1) { auto* m=PM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x1e0/8])(m,p1); }
void PhysicsModule__v0x1f0(BattleObjectModuleAccessor* a,u64 p1) { auto* m=PM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x1f0/8])(m,p1); }
void PhysicsModule__v0x200(BattleObjectModuleAccessor* a,u64 p1) { auto* m=PM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x200/8])(m,p1); }
void PhysicsModule__v0x210(BattleObjectModuleAccessor* a,u64 p1) { auto* m=PM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x210/8])(m,p1); }
void PhysicsModule__v0x218(BattleObjectModuleAccessor* a,u64 p1) { auto* m=PM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x218/8])(m,p1); }
void PhysicsModule__v0x228(BattleObjectModuleAccessor* a,u64 p1) { auto* m=PM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x228/8])(m,p1); }
void PhysicsModule__v0x240(BattleObjectModuleAccessor* a,u64 p1) { auto* m=PM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x240/8])(m,p1); }
void PhysicsModule__v0x258(BattleObjectModuleAccessor* a,u64 p1) { auto* m=PM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x258/8])(m,p1); }
void PhysicsModule__v0x268(BattleObjectModuleAccessor* a,u64 p1) { auto* m=PM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x268/8])(m,p1); }
void PhysicsModule__v0x270(BattleObjectModuleAccessor* a,u64 p1,bool p2) { auto* m=PM(a); reinterpret_cast<void(*)(void*,u64,bool)>(VT(m)[0x270/8])(m,p1,p2); }
void PhysicsModule__v0x278(BattleObjectModuleAccessor* a,u64 p1,bool p2) { auto* m=PM(a); reinterpret_cast<void(*)(void*,u64,bool)>(VT(m)[0x278/8])(m,p1,p2); }
void PhysicsModule__v0x280(BattleObjectModuleAccessor* a,u64 p1) { auto* m=PM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x280/8])(m,p1); }
void PhysicsModule__v0x288(BattleObjectModuleAccessor* a,u64 p1) { auto* m=PM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x288/8])(m,p1); }
void PhysicsModule__v0x290(BattleObjectModuleAccessor* a,u64 p1) { auto* m=PM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x290/8])(m,p1); }
void PhysicsModule__v0x2a0(BattleObjectModuleAccessor* a,u64 p1) { auto* m=PM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x2a0/8])(m,p1); }
void PhysicsModule__v0x2b0(BattleObjectModuleAccessor* a,u64 p1) { auto* m=PM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x2b0/8])(m,p1); }
void PhysicsModule__v0x2c0(BattleObjectModuleAccessor* a,u64 p1) { auto* m=PM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x2c0/8])(m,p1); }
void PhysicsModule__v0x2e0(BattleObjectModuleAccessor* a,u64 p1) { auto* m=PM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x2e0/8])(m,p1); }
void PhysicsModule__v0x2f0(BattleObjectModuleAccessor* a,bool p1) { auto* m=PM(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x2f0/8])(m,p1); }
void PhysicsModule__v0x300(BattleObjectModuleAccessor* a,bool p1) { auto* m=PM(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x300/8])(m,p1); }
void PhysicsModule__v0x308(BattleObjectModuleAccessor* a,u64 p1) { auto* m=PM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x308/8])(m,p1); }
void PhysicsModule__v0x310(BattleObjectModuleAccessor* a,u64 p1) { auto* m=PM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x310/8])(m,p1); }
void PhysicsModule__v0x318(BattleObjectModuleAccessor* a,u64 p1) { auto* m=PM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x318/8])(m,p1); }
void PhysicsModule__v0x320(BattleObjectModuleAccessor* a,u64 p1) { auto* m=PM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x320/8])(m,p1); }
void PhysicsModule__v0x340(BattleObjectModuleAccessor* a,u64 p1) { auto* m=PM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x340/8])(m,p1); }
void PhysicsModule__v0x358(BattleObjectModuleAccessor* a,u64 p1) { auto* m=PM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x358/8])(m,p1); }
void PhysicsModule__v0x3a8(BattleObjectModuleAccessor* a,u64 p1) { auto* m=PM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x3a8/8])(m,p1); }
void PhysicsModule__v0x3b8(BattleObjectModuleAccessor* a,bool p1) { auto* m=PM(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x3b8/8])(m,p1); }
// Auto-generated named dispatchers
void PhysicsModule__reset_swing_impl(BattleObjectModuleAccessor* a) { auto* m=SLOW_MODULE(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x88/8])(m); }
void PhysicsModule__set_swing_only_anim_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=SLOW_MODULE(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0xa8/8])(m,p1); }
void PhysicsModule__set_swing_wind_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=SLOW_MODULE(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0xc8/8])(m,p1); }
void PhysicsModule__set_swing_rate_impl(BattleObjectModuleAccessor* a) { auto* m=SLOW_MODULE(a); reinterpret_cast<void(*)(void*)>(VT(m)[0xf0/8])(m); }
void PhysicsModule__set_swing_rebirth_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=SLOW_MODULE(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0xf8/8])(m,p1); }
void PhysicsModule__set_2nd_gravity_impl(BattleObjectModuleAccessor* a) { auto* m=SLOW_MODULE(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x100/8])(m); }
void PhysicsModule__set_2nd_status_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=SLOW_MODULE(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x110/8])(m,p1); }
void PhysicsModule__set_2nd_end_pos_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=SLOW_MODULE(a); reinterpret_cast<void(*)(void*,u64,u64)>(VT(m)[0x120/8])(m,p1,p2); }
void PhysicsModule__set_2nd_line_length_all_impl(BattleObjectModuleAccessor* a) { auto* m=SLOW_MODULE(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x140/8])(m); }
void PhysicsModule__set_2nd_active_node_num_impl(BattleObjectModuleAccessor* a) { auto* m=SLOW_MODULE(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x168/8])(m); }
bool PhysicsModule__is_2nd_precede_impl(BattleObjectModuleAccessor* a) { auto* m=SLOW_MODULE(a); return reinterpret_cast<bool(*)(void*)>(VT(m)[0x178/8])(m); }
void PhysicsModule__set_2nd_precede_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=SLOW_MODULE(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x180/8])(m,p1); }
bool PhysicsModule__is_2nd_flip_impl(BattleObjectModuleAccessor* a) { auto* m=SLOW_MODULE(a); return reinterpret_cast<bool(*)(void*)>(VT(m)[0x190/8])(m); }
void PhysicsModule__set_2nd_flip_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=SLOW_MODULE(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x198/8])(m,p1); }
void PhysicsModule__set_2nd_back_speed_impl(BattleObjectModuleAccessor* a) { auto* m=SLOW_MODULE(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x1b0/8])(m); }
void PhysicsModule__set_ik_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=SLOW_MODULE(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x1d0/8])(m,p1); }
void PhysicsModule__set_ik_target_pos_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3) { auto* m=SLOW_MODULE(a); reinterpret_cast<void(*)(void*,u64,u64,u64)>(VT(m)[0x1d8/8])(m,p1,p2,p3); }
void PhysicsModule__set_ik_target_dir_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3) { auto* m=SLOW_MODULE(a); reinterpret_cast<void(*)(void*,u64,u64,u64)>(VT(m)[0x1e0/8])(m,p1,p2,p3); }
u32 PhysicsModule__get_ik_end_joint_id_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=SLOW_MODULE(a); return reinterpret_cast<u32(*)(void*,u64)>(VT(m)[0x1f0/8])(m,p1); }
void* PhysicsModule__stop_charge_impl(BattleObjectModuleAccessor* a) { auto* m=SLOW_MODULE(a); return reinterpret_cast<void*(*)(void*)>(VT(m)[0x200/8])(m); }
void PhysicsModule__set_2nd_air_resistance_impl(BattleObjectModuleAccessor* a) { auto* m=SLOW_MODULE(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x210/8])(m); }
void PhysicsModule__set_2nd_air_resistance_2_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=SLOW_MODULE(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x218/8])(m,p1); }
void PhysicsModule__set_2nd_water_resistance_impl(BattleObjectModuleAccessor* a) { auto* m=SLOW_MODULE(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x228/8])(m); }
void* PhysicsModule__get_2nd_tension_impl(BattleObjectModuleAccessor* a) { auto* m=SLOW_MODULE(a); return reinterpret_cast<void*(*)(void*)>(VT(m)[0x240/8])(m); }
void PhysicsModule__set_2nd_collision_size_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=SLOW_MODULE(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x258/8])(m,p1); }
void PhysicsModule__set_2nd_mass_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=SLOW_MODULE(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x268/8])(m,p1); }
void PhysicsModule__set_2nd_disable_collision_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { auto* m=SLOW_MODULE(a); reinterpret_cast<void(*)(void*,u64,bool)>(VT(m)[0x270/8])(m,p1,p2); }
void PhysicsModule__set_2nd_fix_flag_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { auto* m=SLOW_MODULE(a); reinterpret_cast<void(*)(void*,u64,bool)>(VT(m)[0x278/8])(m,p1,p2); }
void PhysicsModule__set_reflect_param_wall_impl(BattleObjectModuleAccessor* a) { auto* m=SLOW_MODULE(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x280/8])(m); }
void PhysicsModule__set_reflect_param_ceil_impl(BattleObjectModuleAccessor* a) { auto* m=SLOW_MODULE(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x288/8])(m); }
void PhysicsModule__set_reflect_param_floor_impl(BattleObjectModuleAccessor* a) { auto* m=SLOW_MODULE(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x290/8])(m); }
void PhysicsModule__set_2nd_length_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=SLOW_MODULE(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x2a0/8])(m,p1); }
void PhysicsModule__set_2nd_pos_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=SLOW_MODULE(a); reinterpret_cast<void(*)(void*,u64,u64)>(VT(m)[0x2b0/8])(m,p1,p2); }
void PhysicsModule__set_2nd_speed_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=SLOW_MODULE(a); reinterpret_cast<void(*)(void*,u64,u64)>(VT(m)[0x2c0/8])(m,p1,p2); }
void PhysicsModule__set_2nd_node_num_max_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=SLOW_MODULE(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x2e0/8])(m,p1); }
void PhysicsModule__set_2nd_collision_object_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=SLOW_MODULE(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x2f0/8])(m,p1); }
void PhysicsModule__set_2nd_sync_gravity_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=SLOW_MODULE(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x300/8])(m,p1); }
void PhysicsModule__set_2nd_restitution_range_impl(BattleObjectModuleAccessor* a) { auto* m=SLOW_MODULE(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x308/8])(m); }
void PhysicsModule__set_2nd_restitution_rate_impl(BattleObjectModuleAccessor* a) { auto* m=SLOW_MODULE(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x310/8])(m); }
void PhysicsModule__set_2nd_restitution_rate_2_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=SLOW_MODULE(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x318/8])(m,p1); }
void PhysicsModule__set_2nd_friction_rate_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=SLOW_MODULE(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x320/8])(m,p1); }
void PhysicsModule__set_2nd_fixed_tip_num_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=SLOW_MODULE(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x338/8])(m,p1); }
void PhysicsModule__set_2nd_z_range_impl(BattleObjectModuleAccessor* a) { auto* m=SLOW_MODULE(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x340/8])(m); }
u32 PhysicsModule__get_2nd_touch_ground_line_num_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=SLOW_MODULE(a); return reinterpret_cast<u32(*)(void*,u64)>(VT(m)[0x358/8])(m,p1); }
void PhysicsModule__set_enable_floor_collision_line_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=SLOW_MODULE(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x3a8/8])(m,p1); }
void PhysicsModule__set_swing_ground_collision_all_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=SLOW_MODULE(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x3b8/8])(m,p1); }
void PhysicsModule__set_swing_special_state_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x80)); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x3d8/8])(m,p1); }
} // namespace app::lua_bind
