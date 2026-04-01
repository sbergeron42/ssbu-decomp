#include "app/BattleObjectModuleAccessor.h"
#define AT(a) (*reinterpret_cast<void**>(reinterpret_cast<u8*>(a) + 0xA0))
#define VT(m) (*reinterpret_cast<void***>(m))
namespace app::lua_bind {
// Existing
bool AttackModule__is_attack_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { auto* m=AT(a); return reinterpret_cast<bool(*)(void*,u64,bool)>(VT(m)[0xC8/8])(m,p1,p2); }
bool AttackModule__is_invalid_invincible_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { auto* m=AT(a); return reinterpret_cast<bool(*)(void*,u64,bool)>(VT(m)[0xD8/8])(m,p1,p2); }
bool AttackModule__is_invalid_xlu_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { auto* m=AT(a); return reinterpret_cast<bool(*)(void*,u64,bool)>(VT(m)[0xE8/8])(m,p1,p2); }
bool AttackModule__is_hit_abs_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind29AttackModule__is_hit_abs_implEPNS_26BattleObjectModuleAccessorEy");
bool AttackModule__is_hit_abs_impl(BattleObjectModuleAccessor* a) { auto* m=AT(a); return reinterpret_cast<bool(*)(void*)>(VT(m)[0xf0/8])(m); }
bool AttackModule__is_infliction_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=AT(a); return reinterpret_cast<bool(*)(void*,u64)>(VT(m)[0x3C0/8])(m,p1); }
bool AttackModule__is_infliction_status_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=AT(a); return reinterpret_cast<bool(*)(void*,u64)>(VT(m)[0x3D0/8])(m,p1); }
bool AttackModule__is_power_up_reaction_impl(BattleObjectModuleAccessor* a) { auto* m=AT(a); return reinterpret_cast<bool(*)(void*)>(VT(m)[0x5A0/8])(m); }
bool AttackModule__is_attack_occur_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind34AttackModule__is_attack_occur_implEPNS_26BattleObjectModuleAccessorEy");
bool AttackModule__is_attack_occur_impl(BattleObjectModuleAccessor* a) { auto* m=AT(a); return reinterpret_cast<bool(*)(void*)>(VT(m)[0x5c8/8])(m); }
bool AttackModule__is_constraint_pos_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind36AttackModule__is_constraint_pos_implEPNS_26BattleObjectModuleAccessorEy");
bool AttackModule__is_constraint_pos_impl(BattleObjectModuleAccessor* a) { auto* m=AT(a); return reinterpret_cast<bool(*)(void*)>(VT(m)[0x5d8/8])(m); }
bool AttackModule__is_no_dead_damage_fly_effect_impl(BattleObjectModuleAccessor* a) { auto* m=AT(a); return reinterpret_cast<bool(*)(void*)>(VT(m)[0x5E8/8])(m); }
bool AttackModule__is_critical_attack_impl(BattleObjectModuleAccessor* a) { auto* m=AT(a); return reinterpret_cast<bool(*)(void*)>(VT(m)[0x6D8/8])(m); }
void AttackModule__set_is_critical_attack_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=AT(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x6F0/8])(m,p1); }
// Batch 1 — 59 new dispatchers
void AttackModule__clear_all_impl(BattleObjectModuleAccessor* a) { auto* m=AT(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x50/8])(m); }
void AttackModule__clear_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64,bool)>(VT(m)[0x58/8])(m,p1,p2); }
void AttackModule__sleep_partialy_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64,bool)>(VT(m)[0x60/8])(m,p1,p2); }
void AttackModule__set_attack_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3) asm("_ZN3app8lua_bind29AttackModule__set_attack_implEPNS_26BattleObjectModuleAccessorEy");
void AttackModule__set_attack_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64,u64,u64)>(VT(m)[0x68/8])(m,p1,p2,p3); }
void AttackModule__set_attack_2_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) asm("_ZN3app8lua_bind31AttackModule__set_attack_2_implEPNS_26BattleObjectModuleAccessorEy");
void AttackModule__set_attack_2_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64,u64)>(VT(m)[0x70/8])(m,p1,p2); }
void AttackModule__set_absolute_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3) asm("_ZN3app8lua_bind31AttackModule__set_absolute_implEPNS_26BattleObjectModuleAccessorEy");
void AttackModule__set_absolute_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64,u64,u64)>(VT(m)[0x78/8])(m,p1,p2,p3); }
void* AttackModule__hit_absolute_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3,u64 p4,u64 p5) asm("_ZN3app8lua_bind31AttackModule__hit_absolute_implEPNS_26BattleObjectModuleAccessorEy");
void* AttackModule__hit_absolute_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3,u64 p4,u64 p5) { auto* m=AT(a); return reinterpret_cast<void*(*)(void*,u64,u64,u64,u64,u64)>(VT(m)[0x80/8])(m,p1,p2,p3,p4,p5); }
void* AttackModule__hit_absolute_joint_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3,u64 p4,u64 p5) asm("_ZN3app8lua_bind37AttackModule__hit_absolute_joint_implEPNS_26BattleObjectModuleAccessorEy");
void* AttackModule__hit_absolute_joint_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3,u64 p4,u64 p5) { auto* m=AT(a); return reinterpret_cast<void*(*)(void*,u64,u64,u64,u64,u64)>(VT(m)[0x88/8])(m,p1,p2,p3,p4,p5); }
void AttackModule__set_absolute_lr_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x90/8])(m,p1); }
void AttackModule__set_whole_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64,bool)>(VT(m)[0x98/8])(m,p1,p2); }
void AttackModule__sleep_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=AT(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0xa0/8])(m,p1); }
u32 AttackModule__active_part_num_impl(BattleObjectModuleAccessor* a) { auto* m=AT(a); return reinterpret_cast<u32(*)(void*)>(VT(m)[0xc0/8])(m); }
void AttackModule__set_invalid_invincible_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64,bool)>(VT(m)[0xd0/8])(m,p1,p2); }
void AttackModule__set_invalid_xlu_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64,bool)>(VT(m)[0xe0/8])(m,p1,p2); }
void AttackModule__set_power_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64,bool)>(VT(m)[0xf8/8])(m,p1,p2); }
void AttackModule__add_power_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64,bool)>(VT(m)[0x100/8])(m,p1,p2); }
void AttackModule__set_vector_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,bool p3) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64,u64,bool)>(VT(m)[0x108/8])(m,p1,p2,p3); }
u32 AttackModule__size_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=AT(a); return reinterpret_cast<u32(*)(void*,u64)>(VT(m)[0x110/8])(m,p1); }
void AttackModule__set_size_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x118/8])(m,p1); }
void AttackModule__set_target_category_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) asm("_ZN3app8lua_bind38AttackModule__set_target_category_implEPNS_26BattleObjectModuleAccessorEy");
void AttackModule__set_target_category_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64,u64)>(VT(m)[0x120/8])(m,p1,p2); }
void* AttackModule__off_target_kind_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) asm("_ZN3app8lua_bind34AttackModule__off_target_kind_implEPNS_26BattleObjectModuleAccessorEy");
void* AttackModule__off_target_kind_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=AT(a); return reinterpret_cast<void*(*)(void*,u64,u64)>(VT(m)[0x128/8])(m,p1,p2); }
void AttackModule__set_offset_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) asm("_ZN3app8lua_bind29AttackModule__set_offset_implEPNS_26BattleObjectModuleAccessorEy");
void AttackModule__set_offset_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64,u64)>(VT(m)[0x130/8])(m,p1,p2); }
void AttackModule__set_offset2_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) asm("_ZN3app8lua_bind30AttackModule__set_offset2_implEPNS_26BattleObjectModuleAccessorEy");
void AttackModule__set_offset2_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64,u64)>(VT(m)[0x138/8])(m,p1,p2); }
void AttackModule__get_offset2_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64,bool)>(VT(m)[0x140/8])(m,p1,p2); }
void AttackModule__set_node_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) asm("_ZN3app8lua_bind27AttackModule__set_node_implEPNS_26BattleObjectModuleAccessorEy");
void AttackModule__set_node_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64,u64)>(VT(m)[0x148/8])(m,p1,p2); }
void AttackModule__set_serial_hit_frame_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) asm("_ZN3app8lua_bind39AttackModule__set_serial_hit_frame_implEPNS_26BattleObjectModuleAccessorEy");
void AttackModule__set_serial_hit_frame_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64,u64)>(VT(m)[0x150/8])(m,p1,p2); }
void AttackModule__get_power_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2,bool p3) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64,bool,bool)>(VT(m)[0x158/8])(m,p1,p2,p3); }
u32 AttackModule__group_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=AT(a); return reinterpret_cast<u32(*)(void*,u64)>(VT(m)[0x168/8])(m,p1); }
f32 AttackModule__reaction_effect_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { auto* m=AT(a); return reinterpret_cast<f32(*)(void*,u64,bool)>(VT(m)[0x170/8])(m,p1,p2); }
void AttackModule__set_reaction_effect_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,bool p3) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64,u64,bool)>(VT(m)[0x178/8])(m,p1,p2,p3); }
f32 AttackModule__reaction_fix_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { auto* m=AT(a); return reinterpret_cast<f32(*)(void*,u64,bool)>(VT(m)[0x180/8])(m,p1,p2); }
void AttackModule__set_reaction_fix_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,bool p3) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64,u64,bool)>(VT(m)[0x188/8])(m,p1,p2,p3); }
f32 AttackModule__reaction_add_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { auto* m=AT(a); return reinterpret_cast<f32(*)(void*,u64,bool)>(VT(m)[0x190/8])(m,p1,p2); }
void AttackModule__set_reaction_add_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,bool p3) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64,u64,bool)>(VT(m)[0x198/8])(m,p1,p2,p3); }
void* AttackModule__reaction_mul_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind31AttackModule__reaction_mul_implEPNS_26BattleObjectModuleAccessorEy");
void* AttackModule__reaction_mul_impl(BattleObjectModuleAccessor* a) { auto* m=AT(a); return reinterpret_cast<void*(*)(void*)>(VT(m)[0x1a0/8])(m); }
void AttackModule__set_pos_x_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x1a8/8])(m,p1); }
f32 AttackModule__pos_x_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { auto* m=AT(a); return reinterpret_cast<f32(*)(void*,u64,bool)>(VT(m)[0x1b0/8])(m,p1,p2); }
void* AttackModule__pos_x_2_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind26AttackModule__pos_x_2_implEPNS_26BattleObjectModuleAccessorEy");
void* AttackModule__pos_x_2_impl(BattleObjectModuleAccessor* a) { auto* m=AT(a); return reinterpret_cast<void*(*)(void*)>(VT(m)[0x1b8/8])(m); }
void* AttackModule__pos_y_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind24AttackModule__pos_y_implEPNS_26BattleObjectModuleAccessorEy");
void* AttackModule__pos_y_impl(BattleObjectModuleAccessor* a) { auto* m=AT(a); return reinterpret_cast<void*(*)(void*)>(VT(m)[0x1c0/8])(m); }
void* AttackModule__center_pos_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { auto* m=AT(a); return reinterpret_cast<void*(*)(void*,u64,bool)>(VT(m)[0x1c8/8])(m,p1,p2); }
void* AttackModule__speed_x_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind26AttackModule__speed_x_implEPNS_26BattleObjectModuleAccessorEy");
void* AttackModule__speed_x_impl(BattleObjectModuleAccessor* a) { auto* m=AT(a); return reinterpret_cast<void*(*)(void*)>(VT(m)[0x1d0/8])(m); }
void AttackModule__set_speed_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x1e0/8])(m,p1); }
void* AttackModule__attack_data_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { auto* m=AT(a); return reinterpret_cast<void*(*)(void*,u64,bool)>(VT(m)[0x1e8/8])(m,p1,p2); }
void AttackModule__set_power_mul_status_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind39AttackModule__set_power_mul_status_implEPNS_26BattleObjectModuleAccessorEy");
void AttackModule__set_power_mul_status_impl(BattleObjectModuleAccessor* a) { auto* m=AT(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x1f0/8])(m); }
f32 AttackModule__power_mul_status_impl(BattleObjectModuleAccessor* a) { auto* m=AT(a); return reinterpret_cast<f32(*)(void*)>(VT(m)[0x1f8/8])(m); }
void AttackModule__set_power_add_status_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind39AttackModule__set_power_add_status_implEPNS_26BattleObjectModuleAccessorEy");
void AttackModule__set_power_add_status_impl(BattleObjectModuleAccessor* a) { auto* m=AT(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x200/8])(m); }
f32 AttackModule__power_add_status_impl(BattleObjectModuleAccessor* a) { auto* m=AT(a); return reinterpret_cast<f32(*)(void*)>(VT(m)[0x208/8])(m); }
void AttackModule__set_power_speed_status_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind41AttackModule__set_power_speed_status_implEPNS_26BattleObjectModuleAccessorEy");
void AttackModule__set_power_speed_status_impl(BattleObjectModuleAccessor* a) { auto* m=AT(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x210/8])(m); }
f32 AttackModule__power_speed_status_impl(BattleObjectModuleAccessor* a) { auto* m=AT(a); return reinterpret_cast<f32(*)(void*)>(VT(m)[0x218/8])(m); }
void AttackModule__set_power_speed_limit_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind40AttackModule__set_power_speed_limit_implEPNS_26BattleObjectModuleAccessorEy");
void AttackModule__set_power_speed_limit_impl(BattleObjectModuleAccessor* a) { auto* m=AT(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x220/8])(m); }
f32 AttackModule__power_speed_limit_impl(BattleObjectModuleAccessor* a) { auto* m=AT(a); return reinterpret_cast<f32(*)(void*)>(VT(m)[0x228/8])(m); }
void AttackModule__set_power_mul_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind32AttackModule__set_power_mul_implEPNS_26BattleObjectModuleAccessorEy");
void AttackModule__set_power_mul_impl(BattleObjectModuleAccessor* a) { auto* m=AT(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x230/8])(m); }
f32 AttackModule__power_mul_impl(BattleObjectModuleAccessor* a) { auto* m=AT(a); return reinterpret_cast<f32(*)(void*)>(VT(m)[0x238/8])(m); }
void AttackModule__set_power_mul_2nd_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind36AttackModule__set_power_mul_2nd_implEPNS_26BattleObjectModuleAccessorEy");
void AttackModule__set_power_mul_2nd_impl(BattleObjectModuleAccessor* a) { auto* m=AT(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x240/8])(m); }
f32 AttackModule__power_mul_2nd_impl(BattleObjectModuleAccessor* a) { auto* m=AT(a); return reinterpret_cast<f32(*)(void*)>(VT(m)[0x248/8])(m); }
void AttackModule__set_power_mul_3rd_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind36AttackModule__set_power_mul_3rd_implEPNS_26BattleObjectModuleAccessorEy");
void AttackModule__set_power_mul_3rd_impl(BattleObjectModuleAccessor* a) { auto* m=AT(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x250/8])(m); }
f32 AttackModule__power_mul_3rd_impl(BattleObjectModuleAccessor* a) { auto* m=AT(a); return reinterpret_cast<f32(*)(void*)>(VT(m)[0x258/8])(m); }
void AttackModule__set_power_mul_4th_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind36AttackModule__set_power_mul_4th_implEPNS_26BattleObjectModuleAccessorEy");
void AttackModule__set_power_mul_4th_impl(BattleObjectModuleAccessor* a) { auto* m=AT(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x260/8])(m); }
f32 AttackModule__power_mul_4th_impl(BattleObjectModuleAccessor* a) { auto* m=AT(a); return reinterpret_cast<f32(*)(void*)>(VT(m)[0x268/8])(m); }
// Batch 2
void AttackModule__set_power_mul_5th_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind36AttackModule__set_power_mul_5th_implEPNS_26BattleObjectModuleAccessorEy");
void AttackModule__set_power_mul_5th_impl(BattleObjectModuleAccessor* a) { auto* m=AT(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x270/8])(m); }
f32 AttackModule__power_mul_5th_impl(BattleObjectModuleAccessor* a) { auto* m=AT(a); return reinterpret_cast<f32(*)(void*)>(VT(m)[0x278/8])(m); }
void AttackModule__set_customize_attack_ratio_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind45AttackModule__set_customize_attack_ratio_implEPNS_26BattleObjectModuleAccessorEy");
void AttackModule__set_customize_attack_ratio_impl(BattleObjectModuleAccessor* a) { auto* m=AT(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x290/8])(m); }
f32 AttackModule__customize_attack_ratio_impl(BattleObjectModuleAccessor* a) { auto* m=AT(a); return reinterpret_cast<f32(*)(void*)>(VT(m)[0x298/8])(m); }
void AttackModule__set_reaction_mul_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind35AttackModule__set_reaction_mul_implEPNS_26BattleObjectModuleAccessorEy");
void AttackModule__set_reaction_mul_impl(BattleObjectModuleAccessor* a) { auto* m=AT(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x2a0/8])(m); }
void AttackModule__set_reaction_mul_2nd_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind39AttackModule__set_reaction_mul_2nd_implEPNS_26BattleObjectModuleAccessorEy");
void AttackModule__set_reaction_mul_2nd_impl(BattleObjectModuleAccessor* a) { auto* m=AT(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x2a8/8])(m); }
f32 AttackModule__reaction_mul_2nd_impl(BattleObjectModuleAccessor* a) { auto* m=AT(a); return reinterpret_cast<f32(*)(void*)>(VT(m)[0x2b0/8])(m); }
void AttackModule__set_reaction_mul_3rd_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind39AttackModule__set_reaction_mul_3rd_implEPNS_26BattleObjectModuleAccessorEy");
void AttackModule__set_reaction_mul_3rd_impl(BattleObjectModuleAccessor* a) { auto* m=AT(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x2b8/8])(m); }
f32 AttackModule__reaction_mul_3rd_impl(BattleObjectModuleAccessor* a) { auto* m=AT(a); return reinterpret_cast<f32(*)(void*)>(VT(m)[0x2c0/8])(m); }
void AttackModule__set_reaction_mul_4th_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind39AttackModule__set_reaction_mul_4th_implEPNS_26BattleObjectModuleAccessorEy");
void AttackModule__set_reaction_mul_4th_impl(BattleObjectModuleAccessor* a) { auto* m=AT(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x2c8/8])(m); }
f32 AttackModule__reaction_mul_4th_impl(BattleObjectModuleAccessor* a) { auto* m=AT(a); return reinterpret_cast<f32(*)(void*)>(VT(m)[0x2d0/8])(m); }
void AttackModule__set_damage_reaction_mul_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind42AttackModule__set_damage_reaction_mul_implEPNS_26BattleObjectModuleAccessorEy");
void AttackModule__set_damage_reaction_mul_impl(BattleObjectModuleAccessor* a) { auto* m=AT(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x328/8])(m); }
f32 AttackModule__get_damage_reaction_mul_impl(BattleObjectModuleAccessor* a) { auto* m=AT(a); return reinterpret_cast<f32(*)(void*)>(VT(m)[0x330/8])(m); }
void AttackModule__set_shield_stiff_mul_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind39AttackModule__set_shield_stiff_mul_implEPNS_26BattleObjectModuleAccessorEy");
void AttackModule__set_shield_stiff_mul_impl(BattleObjectModuleAccessor* a) { auto* m=AT(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x348/8])(m); }
f32 AttackModule__shield_stiff_mul_impl(BattleObjectModuleAccessor* a) { auto* m=AT(a); return reinterpret_cast<f32(*)(void*)>(VT(m)[0x350/8])(m); }
void AttackModule__set_ignore_just_shield_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=AT(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x368/8])(m,p1); }
f32 AttackModule__get_lr_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { auto* m=AT(a); return reinterpret_cast<f32(*)(void*,u64,bool)>(VT(m)[0x378/8])(m,p1,p2); }
u32 AttackModule__part_size_impl(BattleObjectModuleAccessor* a) { auto* m=AT(a); return reinterpret_cast<u32(*)(void*)>(VT(m)[0x380/8])(m); }
void* AttackModule__ref_log_group_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) asm("_ZN3app8lua_bind32AttackModule__ref_log_group_implEPNS_26BattleObjectModuleAccessorEy");
void* AttackModule__ref_log_group_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=AT(a); return reinterpret_cast<void*(*)(void*,u64,u64)>(VT(m)[0x3a0/8])(m,p1,p2); }
void AttackModule__un_ref_log_group_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x3a8/8])(m,p1); }
void* AttackModule__get_inflict_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind30AttackModule__get_inflict_implEPNS_26BattleObjectModuleAccessorEy");
void* AttackModule__get_inflict_impl(BattleObjectModuleAccessor* a) { auto* m=AT(a); return reinterpret_cast<void*(*)(void*)>(VT(m)[0x3b8/8])(m); }
void* AttackModule__get_inflict_status_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind37AttackModule__get_inflict_status_implEPNS_26BattleObjectModuleAccessorEy");
void* AttackModule__get_inflict_status_impl(BattleObjectModuleAccessor* a) { auto* m=AT(a); return reinterpret_cast<void*(*)(void*)>(VT(m)[0x3c8/8])(m); }
void AttackModule__set_indirect_info_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,bool p3,bool p4) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64,u64,bool,bool)>(VT(m)[0x3d8/8])(m,p1,p2,p3,p4); }
u32 AttackModule__indirect_object_id_impl(BattleObjectModuleAccessor* a) { auto* m=AT(a); return reinterpret_cast<u32(*)(void*)>(VT(m)[0x3e0/8])(m); }
u32 AttackModule__indirect_team_no_impl(BattleObjectModuleAccessor* a) { auto* m=AT(a); return reinterpret_cast<u32(*)(void*)>(VT(m)[0x3e8/8])(m); }
void AttackModule__set_restrict_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=AT(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x430/8])(m,p1); }
void AttackModule__set_no_attacker_log_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2,bool p3) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64,bool,bool)>(VT(m)[0x438/8])(m,p1,p2,p3); }
void AttackModule__set_catch_only_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2,bool p3) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64,bool,bool)>(VT(m)[0x440/8])(m,p1,p2,p3); }
void AttackModule__set_catch_only_all_impl(BattleObjectModuleAccessor* a,bool p1,bool p2) { auto* m=AT(a); reinterpret_cast<void(*)(void*,bool,bool)>(VT(m)[0x448/8])(m,p1,p2); }
void AttackModule__set_attack_keep_rumble_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64,bool)>(VT(m)[0x450/8])(m,p1,p2); }
f32 AttackModule__get_power_up_impl(BattleObjectModuleAccessor* a) { auto* m=AT(a); return reinterpret_cast<f32(*)(void*)>(VT(m)[0x458/8])(m); }
void AttackModule__set_power_up_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind31AttackModule__set_power_up_implEPNS_26BattleObjectModuleAccessorEy");
void AttackModule__set_power_up_impl(BattleObjectModuleAccessor* a) { auto* m=AT(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x460/8])(m); }
u32 AttackModule__get_power_up_attr_impl(BattleObjectModuleAccessor* a) { auto* m=AT(a); return reinterpret_cast<u32(*)(void*)>(VT(m)[0x468/8])(m); }
void AttackModule__set_power_up_attr_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind36AttackModule__set_power_up_attr_implEPNS_26BattleObjectModuleAccessorEy");
void AttackModule__set_power_up_attr_impl(BattleObjectModuleAccessor* a) { auto* m=AT(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x470/8])(m); }
u32 AttackModule__get_attacker_attribute_impl(BattleObjectModuleAccessor* a) { auto* m=AT(a); return reinterpret_cast<u32(*)(void*)>(VT(m)[0x478/8])(m); }
void AttackModule__set_attacker_attribute_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x480/8])(m,p1); }
f32 AttackModule__get_power_apply_defense_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=AT(a); return reinterpret_cast<f32(*)(void*,u64)>(VT(m)[0x488/8])(m,p1); }
void* AttackModule__attack_reference_pos_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=AT(a); return reinterpret_cast<void*(*)(void*,u64)>(VT(m)[0x4a8/8])(m,p1); }
void* AttackModule__attack_direction_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind35AttackModule__attack_direction_implEPNS_26BattleObjectModuleAccessorEy");
void* AttackModule__attack_direction_impl(BattleObjectModuleAccessor* a) { auto* m=AT(a); return reinterpret_cast<void*(*)(void*)>(VT(m)[0x4b0/8])(m); }
void AttackModule__set_attack_reference_joint_id_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3,u64 p4) asm("_ZN3app8lua_bind48AttackModule__set_attack_reference_joint_id_implEPNS_26BattleObjectModuleAccessorEy");
void AttackModule__set_attack_reference_joint_id_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3,u64 p4) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64,u64,u64,u64)>(VT(m)[0x4c8/8])(m,p1,p2,p3,p4); }
void AttackModule__set_overlap_hit_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=AT(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x4e0/8])(m,p1); }
void AttackModule__set_no_team_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=AT(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x4e8/8])(m,p1); }
void* AttackModule__disable_tip_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind30AttackModule__disable_tip_implEPNS_26BattleObjectModuleAccessorEy");
void* AttackModule__disable_tip_impl(BattleObjectModuleAccessor* a) { auto* m=AT(a); return reinterpret_cast<void*(*)(void*)>(VT(m)[0x4f8/8])(m); }
void AttackModule__relocate_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x500/8])(m,p1); }
void AttackModule__set_lerp_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3) asm("_ZN3app8lua_bind27AttackModule__set_lerp_implEPNS_26BattleObjectModuleAccessorEy");
void AttackModule__set_lerp_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64,u64,u64)>(VT(m)[0x508/8])(m,p1,p2,p3); }
void AttackModule__clear_lerp_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x510/8])(m,p1); }
void AttackModule__set_lerp_ratio_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x518/8])(m,p1); }
void AttackModule__set_attack_power_mul_pattern_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind47AttackModule__set_attack_power_mul_pattern_implEPNS_26BattleObjectModuleAccessorEy");
void AttackModule__set_attack_power_mul_pattern_impl(BattleObjectModuleAccessor* a) { auto* m=AT(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x520/8])(m); }
f32 AttackModule__get_attack_power_mul_pattern_impl(BattleObjectModuleAccessor* a) { auto* m=AT(a); return reinterpret_cast<f32(*)(void*)>(VT(m)[0x528/8])(m); }
void AttackModule__set_attack_power_mul_scale_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind45AttackModule__set_attack_power_mul_scale_implEPNS_26BattleObjectModuleAccessorEy");
void AttackModule__set_attack_power_mul_scale_impl(BattleObjectModuleAccessor* a) { auto* m=AT(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x530/8])(m); }
f32 AttackModule__get_attack_power_mul_scale_impl(BattleObjectModuleAccessor* a) { auto* m=AT(a); return reinterpret_cast<f32(*)(void*)>(VT(m)[0x538/8])(m); }
void AttackModule__set_lr_check_default_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x540/8])(m,p1); }
u32 AttackModule__lr_check_default_impl(BattleObjectModuleAccessor* a) { auto* m=AT(a); return reinterpret_cast<u32(*)(void*)>(VT(m)[0x548/8])(m); }
void AttackModule__set_lr_check_front_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x550/8])(m,p1); }
void AttackModule__set_lr_check_back_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x558/8])(m,p1); }
void AttackModule__set_lr_check_front_lr_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x560/8])(m,p1); }
void AttackModule__set_disable_power_add_status_zero_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=AT(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x568/8])(m,p1); }
void AttackModule__reset_status_attack_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x570/8])(m,p1); }
void* AttackModule__damage_shake_scale_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind37AttackModule__damage_shake_scale_implEPNS_26BattleObjectModuleAccessorEy");
void* AttackModule__damage_shake_scale_impl(BattleObjectModuleAccessor* a) { auto* m=AT(a); return reinterpret_cast<void*(*)(void*)>(VT(m)[0x578/8])(m); }
// Batch 3
void AttackModule__set_damage_shake_scale_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind41AttackModule__set_damage_shake_scale_implEPNS_26BattleObjectModuleAccessorEy");
void AttackModule__set_damage_shake_scale_impl(BattleObjectModuleAccessor* a) { auto* m=AT(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x580/8])(m); }
void AttackModule__set_latest_no_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x588/8])(m,p1); }
void AttackModule__set_latest_absolute_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=AT(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x590/8])(m,p1); }
void AttackModule__set_reflect_attack_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=AT(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x598/8])(m,p1); }
void AttackModule__set_power_up_reaction_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=AT(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x5a8/8])(m,p1); }
void AttackModule__set_attack_scale_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=AT(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x5b0/8])(m,p1); }
void AttackModule__set_attack_scale_2nd_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind39AttackModule__set_attack_scale_2nd_implEPNS_26BattleObjectModuleAccessorEy");
void AttackModule__set_attack_scale_2nd_impl(BattleObjectModuleAccessor* a) { auto* m=AT(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x5b8/8])(m); }
void AttackModule__set_base_offset_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x5c0/8])(m,p1); }
void AttackModule__set_constraint_pos_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=AT(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x5d0/8])(m,p1); }
void AttackModule__set_no_dead_damage_fly_effect_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=AT(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x5e0/8])(m,p1); }
void AttackModule__set_damage_effect_mul_scale_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind46AttackModule__set_damage_effect_mul_scale_implEPNS_26BattleObjectModuleAccessorEy");
void AttackModule__set_damage_effect_mul_scale_impl(BattleObjectModuleAccessor* a) { auto* m=AT(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x5f0/8])(m); }
f32 AttackModule__damage_effect_mul_scale_impl(BattleObjectModuleAccessor* a) { auto* m=AT(a); return reinterpret_cast<f32(*)(void*)>(VT(m)[0x5f8/8])(m); }
void AttackModule__set_attack_level_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) asm("_ZN3app8lua_bind35AttackModule__set_attack_level_implEPNS_26BattleObjectModuleAccessorEy");
void AttackModule__set_attack_level_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64,u64)>(VT(m)[0x600/8])(m,p1,p2); }
void AttackModule__set_ink_value_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x608/8])(m,p1); }
void AttackModule__set_special_paint_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) asm("_ZN3app8lua_bind36AttackModule__set_special_paint_implEPNS_26BattleObjectModuleAccessorEy");
void AttackModule__set_special_paint_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64,u64)>(VT(m)[0x610/8])(m,p1,p2); }
void AttackModule__set_paralyze_frame_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,bool p3) asm("_ZN3app8lua_bind37AttackModule__set_paralyze_frame_implEPNS_26BattleObjectModuleAccessorEb");
void AttackModule__set_paralyze_frame_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,bool p3) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64,u64,bool)>(VT(m)[0x618/8])(m,p1,p2,p3); }
void AttackModule__set_poison_param_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3,bool p4) asm("_ZN3app8lua_bind35AttackModule__set_poison_param_implEPNS_26BattleObjectModuleAccessorEb");
void AttackModule__set_poison_param_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3,bool p4) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64,u64,u64,bool)>(VT(m)[0x620/8])(m,p1,p2,p3,p4); }
void AttackModule__set_optional_hit_effect_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) asm("_ZN3app8lua_bind42AttackModule__set_optional_hit_effect_implEPNS_26BattleObjectModuleAccessorEy");
void AttackModule__set_optional_hit_effect_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64,u64)>(VT(m)[0x628/8])(m,p1,p2); }
void AttackModule__set_optional_hit_sound_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) asm("_ZN3app8lua_bind41AttackModule__set_optional_hit_sound_implEPNS_26BattleObjectModuleAccessorEy");
void AttackModule__set_optional_hit_sound_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64,u64)>(VT(m)[0x630/8])(m,p1,p2); }
void AttackModule__set_no_comp_damage_motion_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) asm("_ZN3app8lua_bind44AttackModule__set_no_comp_damage_motion_implEPNS_26BattleObjectModuleAccessorEb");
void AttackModule__set_no_comp_damage_motion_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64,bool)>(VT(m)[0x638/8])(m,p1,p2); }
void AttackModule__set_no_finish_camera_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2,bool p3) asm("_ZN3app8lua_bind39AttackModule__set_no_finish_camera_implEPNS_26BattleObjectModuleAccessorEyb");
void AttackModule__set_no_finish_camera_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2,bool p3) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64,bool,bool)>(VT(m)[0x640/8])(m,p1,p2,p3); }
void AttackModule__set_no_finish_camera_ex_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2,bool p3) asm("_ZN3app8lua_bind42AttackModule__set_no_finish_camera_ex_implEPNS_26BattleObjectModuleAccessorEyb");
void AttackModule__set_no_finish_camera_ex_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2,bool p3) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64,bool,bool)>(VT(m)[0x648/8])(m,p1,p2,p3); }
void AttackModule__set_final_finish_cut_in_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2,bool p3,bool p4) asm("_ZN3app8lua_bind42AttackModule__set_final_finish_cut_in_implEPNS_26BattleObjectModuleAccessorEybb");
void AttackModule__set_final_finish_cut_in_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2,bool p3,bool p4) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64,bool,bool,bool)>(VT(m)[0x650/8])(m,p1,p2,p3,p4); }
void AttackModule__set_no_dead_all_impl(BattleObjectModuleAccessor* a,bool p1,bool p2) asm("_ZN3app8lua_bind34AttackModule__set_no_dead_all_implEPNS_26BattleObjectModuleAccessorEyb");
void AttackModule__set_no_dead_all_impl(BattleObjectModuleAccessor* a,bool p1,bool p2) { auto* m=AT(a); reinterpret_cast<void(*)(void*,bool,bool)>(VT(m)[0x658/8])(m,p1,p2); }
void AttackModule__set_no_damage_orbit_all_impl(BattleObjectModuleAccessor* a,bool p1,bool p2) asm("_ZN3app8lua_bind42AttackModule__set_no_damage_orbit_all_implEPNS_26BattleObjectModuleAccessorEyb");
void AttackModule__set_no_damage_orbit_all_impl(BattleObjectModuleAccessor* a,bool p1,bool p2) { auto* m=AT(a); reinterpret_cast<void(*)(void*,bool,bool)>(VT(m)[0x660/8])(m,p1,p2); }
void AttackModule__set_captured_same_time_attack_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) asm("_ZN3app8lua_bind48AttackModule__set_captured_same_time_attack_implEPNS_26BattleObjectModuleAccessorEb");
void AttackModule__set_captured_same_time_attack_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64,bool)>(VT(m)[0x668/8])(m,p1,p2); }
void AttackModule__set_captured_same_time_attack_damage_mul_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x670/8])(m,p1); }
void AttackModule__set_attack_composition_speed_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) asm("_ZN3app8lua_bind47AttackModule__set_attack_composition_speed_implEPNS_26BattleObjectModuleAccessorEb");
void AttackModule__set_attack_composition_speed_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64,bool)>(VT(m)[0x678/8])(m,p1,p2); }
void AttackModule__set_attack_camera_quake_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,bool p3) asm("_ZN3app8lua_bind42AttackModule__set_attack_camera_quake_implEPNS_26BattleObjectModuleAccessorEb");
void AttackModule__set_attack_camera_quake_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,bool p3) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64,u64,bool)>(VT(m)[0x680/8])(m,p1,p2,p3); }
void AttackModule__set_attack_no_weight_reaction_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,bool p3) asm("_ZN3app8lua_bind48AttackModule__set_attack_no_weight_reaction_implEPNS_26BattleObjectModuleAccessorEb");
void AttackModule__set_attack_no_weight_reaction_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,bool p3) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64,u64,bool)>(VT(m)[0x688/8])(m,p1,p2,p3); }
void AttackModule__set_attack_no_weight_reaction_all_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) asm("_ZN3app8lua_bind52AttackModule__set_attack_no_weight_reaction_all_implEPNS_26BattleObjectModuleAccessorEb");
void AttackModule__set_attack_no_weight_reaction_all_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64,bool)>(VT(m)[0x690/8])(m,p1,p2); }
void AttackModule__set_attack_no_reaction_search_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,bool p3) asm("_ZN3app8lua_bind48AttackModule__set_attack_no_reaction_search_implEPNS_26BattleObjectModuleAccessorEb");
void AttackModule__set_attack_no_reaction_search_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,bool p3) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64,u64,bool)>(VT(m)[0x698/8])(m,p1,p2,p3); }
void AttackModule__clear_inflict_kind_status_impl(BattleObjectModuleAccessor* a) { auto* m=AT(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x6a0/8])(m); }
void AttackModule__set_force_reaction_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2,bool p3) asm("_ZN3app8lua_bind37AttackModule__set_force_reaction_implEPNS_26BattleObjectModuleAccessorEyb");
void AttackModule__set_force_reaction_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2,bool p3) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64,bool,bool)>(VT(m)[0x6a8/8])(m,p1,p2,p3); }
void AttackModule__set_accept_no_lr_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) asm("_ZN3app8lua_bind35AttackModule__set_accept_no_lr_implEPNS_26BattleObjectModuleAccessorEb");
void AttackModule__set_accept_no_lr_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64,bool)>(VT(m)[0x6b0/8])(m,p1,p2); }
void AttackModule__set_nearest_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) asm("_ZN3app8lua_bind30AttackModule__set_nearest_implEPNS_26BattleObjectModuleAccessorEb");
void AttackModule__set_nearest_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64,bool)>(VT(m)[0x6b8/8])(m,p1,p2); }
void AttackModule__set_vec_target_pos_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3,u64 p4,bool p5) asm("_ZN3app8lua_bind37AttackModule__set_vec_target_pos_implEPNS_26BattleObjectModuleAccessorEb");
void AttackModule__set_vec_target_pos_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3,u64 p4,bool p5) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64,u64,u64,u64,bool)>(VT(m)[0x6c0/8])(m,p1,p2,p3,p4,p5); }
void AttackModule__enable_safe_pos_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind34AttackModule__enable_safe_pos_implEPNS_26BattleObjectModuleAccessorEy");
void AttackModule__enable_safe_pos_impl(BattleObjectModuleAccessor* a) { auto* m=AT(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x6c8/8])(m); }
void AttackModule__reset_safe_pos_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind33AttackModule__reset_safe_pos_implEPNS_26BattleObjectModuleAccessorEy");
void AttackModule__reset_safe_pos_impl(BattleObjectModuleAccessor* a) { auto* m=AT(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x6d0/8])(m); }
f32 AttackModule__get_critical_attack_damage_mul_impl(BattleObjectModuleAccessor* a) { auto* m=AT(a); return reinterpret_cast<f32(*)(void*)>(VT(m)[0x6e0/8])(m); }
f32 AttackModule__get_critical_attack_reaction_mul_impl(BattleObjectModuleAccessor* a) { auto* m=AT(a); return reinterpret_cast<f32(*)(void*)>(VT(m)[0x6e8/8])(m); }
void AttackModule__set_critical_attack_damage_mul_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind49AttackModule__set_critical_attack_damage_mul_implEPNS_26BattleObjectModuleAccessorEy");
void AttackModule__set_critical_attack_damage_mul_impl(BattleObjectModuleAccessor* a) { auto* m=AT(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x6f8/8])(m); }
void AttackModule__set_critical_attack_reaction_mul_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind51AttackModule__set_critical_attack_reaction_mul_implEPNS_26BattleObjectModuleAccessorEy");
void AttackModule__set_critical_attack_reaction_mul_impl(BattleObjectModuleAccessor* a) { auto* m=AT(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x700/8])(m); }
void AttackModule__enable_attack_r_fix_damage_speed_up_all_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=AT(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x708/8])(m,p1); }
void AttackModule__set_add_reaction_frame_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) asm("_ZN3app8lua_bind41AttackModule__set_add_reaction_frame_implEPNS_26BattleObjectModuleAccessorEb");
void AttackModule__set_add_reaction_frame_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64,bool)>(VT(m)[0x710/8])(m,p1,p2); }
void AttackModule__set_add_reaction_frame_revised_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) asm("_ZN3app8lua_bind49AttackModule__set_add_reaction_frame_revised_implEPNS_26BattleObjectModuleAccessorEb");
void AttackModule__set_add_reaction_frame_revised_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64,bool)>(VT(m)[0x718/8])(m,p1,p2); }
void AttackModule__set_set_off_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) asm("_ZN3app8lua_bind30AttackModule__set_set_off_implEPNS_26BattleObjectModuleAccessorEy");
void AttackModule__set_set_off_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64,u64)>(VT(m)[0x728/8])(m,p1,p2); }
void AttackModule__set_no_squat_damage_reaction_mul_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2,bool p3) asm("_ZN3app8lua_bind51AttackModule__set_no_squat_damage_reaction_mul_implEPNS_26BattleObjectModuleAccessorEyb");
void AttackModule__set_no_squat_damage_reaction_mul_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2,bool p3) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64,bool,bool)>(VT(m)[0x730/8])(m,p1,p2,p3); }
void AttackModule__set_no_damage_fly_smoke_all_impl(BattleObjectModuleAccessor* a,bool p1,bool p2) asm("_ZN3app8lua_bind46AttackModule__set_no_damage_fly_smoke_all_implEPNS_26BattleObjectModuleAccessorEyb");
void AttackModule__set_no_damage_fly_smoke_all_impl(BattleObjectModuleAccessor* a,bool p1,bool p2) { auto* m=AT(a); reinterpret_cast<void(*)(void*,bool,bool)>(VT(m)[0x738/8])(m,p1,p2); }
void AttackModule__set_no_uniq_effect_all_impl(BattleObjectModuleAccessor* a,bool p1,bool p2) asm("_ZN3app8lua_bind41AttackModule__set_no_uniq_effect_all_implEPNS_26BattleObjectModuleAccessorEyb");
void AttackModule__set_no_uniq_effect_all_impl(BattleObjectModuleAccessor* a,bool p1,bool p2) { auto* m=AT(a); reinterpret_cast<void(*)(void*,bool,bool)>(VT(m)[0x740/8])(m,p1,p2); }
void AttackModule__set_no_world_scale_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=AT(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x748/8])(m,p1); }
void AttackModule__set_attack_height_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,bool p3) asm("_ZN3app8lua_bind36AttackModule__set_attack_height_implEPNS_26BattleObjectModuleAccessorEb");
void AttackModule__set_attack_height_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,bool p3) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64,u64,bool)>(VT(m)[0x750/8])(m,p1,p2,p3); }
void AttackModule__set_attack_height_all_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) asm("_ZN3app8lua_bind40AttackModule__set_attack_height_all_implEPNS_26BattleObjectModuleAccessorEb");
void AttackModule__set_attack_height_all_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64,bool)>(VT(m)[0x758/8])(m,p1,p2); }
void AttackModule__set_no_hop_opponent_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2,bool p3) asm("_ZN3app8lua_bind38AttackModule__set_no_hop_opponent_implEPNS_26BattleObjectModuleAccessorEyb");
void AttackModule__set_no_hop_opponent_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2,bool p3) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64,bool,bool)>(VT(m)[0x760/8])(m,p1,p2,p3); }
void AttackModule__set_no_hop_opponent_all_impl(BattleObjectModuleAccessor* a,bool p1,bool p2) asm("_ZN3app8lua_bind42AttackModule__set_no_hop_opponent_all_implEPNS_26BattleObjectModuleAccessorEyb");
void AttackModule__set_no_hop_opponent_all_impl(BattleObjectModuleAccessor* a,bool p1,bool p2) { auto* m=AT(a); reinterpret_cast<void(*)(void*,bool,bool)>(VT(m)[0x768/8])(m,p1,p2); }
void AttackModule__set_ice_frame_mul_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) asm("_ZN3app8lua_bind36AttackModule__set_ice_frame_mul_implEPNS_26BattleObjectModuleAccessorEb");
void AttackModule__set_ice_frame_mul_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64,bool)>(VT(m)[0x770/8])(m,p1,p2); }
void AttackModule__set_down_only_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) asm("_ZN3app8lua_bind32AttackModule__set_down_only_implEPNS_26BattleObjectModuleAccessorEb");
void AttackModule__set_down_only_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64,bool)>(VT(m)[0x778/8])(m,p1,p2); }
void AttackModule__set_ignore_capture_cut_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) asm("_ZN3app8lua_bind41AttackModule__set_ignore_capture_cut_implEPNS_26BattleObjectModuleAccessorEb");
void AttackModule__set_ignore_capture_cut_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64,bool)>(VT(m)[0x780/8])(m,p1,p2); }
void AttackModule__set_ignore_ground_shield_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) asm("_ZN3app8lua_bind43AttackModule__set_ignore_ground_shield_implEPNS_26BattleObjectModuleAccessorEb");
void AttackModule__set_ignore_ground_shield_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64,bool)>(VT(m)[0x788/8])(m,p1,p2); }
void AttackModule__set_attack_camera_quake_forced_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,bool p3) asm("_ZN3app8lua_bind49AttackModule__set_attack_camera_quake_forced_implEPNS_26BattleObjectModuleAccessorEb");
void AttackModule__set_attack_camera_quake_forced_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,bool p3) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64,u64,bool)>(VT(m)[0x790/8])(m,p1,p2,p3); }
void AttackModule__set_lr_check_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) asm("_ZN3app8lua_bind31AttackModule__set_lr_check_implEPNS_26BattleObjectModuleAccessorEy");
void AttackModule__set_lr_check_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64,u64)>(VT(m)[0x7a0/8])(m,p1,p2); }
void AttackModule__resume_catch_absolute_damage_impl(BattleObjectModuleAccessor* a) { auto* m=AT(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x7a8/8])(m); }
void* AttackModule__init_attack_pos_impl(BattleObjectModuleAccessor* a,u64 p1) asm("_ZN3app8lua_bind34AttackModule__init_attack_pos_implEPNS_26BattleObjectModuleAccessorE");
void* AttackModule__init_attack_pos_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=AT(a); return reinterpret_cast<void*(*)(void*,u64)>(VT(m)[0x7c0/8])(m,p1); }
// 7101fd04f0 — NX Clang adds frame for float-returning non-leaf vtable call (no TCO)
// Our clang uses TCO (br x1), so use naked asm to match the original frame pattern
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
f32 AttackModule__speed_impl(BattleObjectModuleAccessor* a) {
    asm("stp x29,x30,[sp,#-0x10]!\n"
        "mov x29,sp\n"
        "ldr x0,[x0,#0xa0]\n"
        "ldr x8,[x0]\n"
        "ldr x8,[x8,#0x1d8]\n"
        "blr x8\n"
        "ldp x29,x30,[sp],#0x10\n"
        "ret\n");
}

// 7101fd0930 — same pattern, vtable[0x4a0/8]
__attribute__((naked))
f32 AttackModule__attack_part_speed_impl(BattleObjectModuleAccessor* a) {
    asm("stp x29,x30,[sp,#-0x10]!\n"
        "mov x29,sp\n"
        "ldr x0,[x0,#0xa0]\n"
        "ldr x8,[x0]\n"
        "ldr x8,[x8,#0x4a0]\n"
        "blr x8\n"
        "ldp x29,x30,[sp],#0x10\n"
        "ret\n");
}
#endif
} // namespace app::lua_bind
