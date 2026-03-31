#include "app/BattleObjectModuleAccessor.h"
#define AT(a) (*reinterpret_cast<void**>(reinterpret_cast<u8*>(a) + 0xA0))
#define VT(m) (*reinterpret_cast<void***>(m))
namespace app::lua_bind {
// Existing
bool AttackModule__is_attack_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { auto* m=AT(a); return reinterpret_cast<bool(*)(void*,u64,bool)>(VT(m)[0xC8/8])(m,p1,p2); }
bool AttackModule__is_invalid_invincible_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { auto* m=AT(a); return reinterpret_cast<bool(*)(void*,u64,bool)>(VT(m)[0xD8/8])(m,p1,p2); }
bool AttackModule__is_invalid_xlu_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { auto* m=AT(a); return reinterpret_cast<bool(*)(void*,u64,bool)>(VT(m)[0xE8/8])(m,p1,p2); }
bool AttackModule__is_hit_abs_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=AT(a); return reinterpret_cast<bool(*)(void*,u64)>(VT(m)[0xF0/8])(m,p1); }
bool AttackModule__is_infliction_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=AT(a); return reinterpret_cast<bool(*)(void*,u64)>(VT(m)[0x3C0/8])(m,p1); }
bool AttackModule__is_infliction_status_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=AT(a); return reinterpret_cast<bool(*)(void*,u64)>(VT(m)[0x3D0/8])(m,p1); }
bool AttackModule__is_power_up_reaction_impl(BattleObjectModuleAccessor* a) { auto* m=AT(a); return reinterpret_cast<bool(*)(void*)>(VT(m)[0x5A0/8])(m); }
bool AttackModule__is_attack_occur_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=AT(a); return reinterpret_cast<bool(*)(void*,u64)>(VT(m)[0x5C8/8])(m,p1); }
bool AttackModule__is_constraint_pos_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=AT(a); return reinterpret_cast<bool(*)(void*,u64)>(VT(m)[0x5D8/8])(m,p1); }
bool AttackModule__is_no_dead_damage_fly_effect_impl(BattleObjectModuleAccessor* a) { auto* m=AT(a); return reinterpret_cast<bool(*)(void*)>(VT(m)[0x5E8/8])(m); }
bool AttackModule__is_critical_attack_impl(BattleObjectModuleAccessor* a) { auto* m=AT(a); return reinterpret_cast<bool(*)(void*)>(VT(m)[0x6D8/8])(m); }
void AttackModule__set_is_critical_attack_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=AT(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x6F0/8])(m,p1); }
// Batch 1 — 59 new dispatchers
void AttackModule__clear_all_impl(BattleObjectModuleAccessor* a) { auto* m=AT(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x50/8])(m); }
void AttackModule__clear_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64,bool)>(VT(m)[0x58/8])(m,p1,p2); }
void AttackModule__sleep_partialy_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64,bool)>(VT(m)[0x60/8])(m,p1,p2); }
void AttackModule__set_attack_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x68/8])(m,p1); }
void AttackModule__set_attack_2_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x70/8])(m,p1); }
void AttackModule__set_absolute_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x78/8])(m,p1); }
void AttackModule__hit_absolute_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x80/8])(m,p1); }
void AttackModule__hit_absolute_joint_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x88/8])(m,p1); }
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
void AttackModule__set_target_category_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x120/8])(m,p1); }
void AttackModule__off_target_kind_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x128/8])(m,p1); }
void AttackModule__set_offset_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x130/8])(m,p1); }
void AttackModule__set_offset2_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x138/8])(m,p1); }
void AttackModule__get_offset2_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64,bool)>(VT(m)[0x140/8])(m,p1,p2); }
void AttackModule__set_node_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x148/8])(m,p1); }
void AttackModule__set_serial_hit_frame_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x150/8])(m,p1); }
void AttackModule__get_power_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2,bool p3) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64,bool,bool)>(VT(m)[0x158/8])(m,p1,p2,p3); }
u32 AttackModule__group_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=AT(a); return reinterpret_cast<u32(*)(void*,u64)>(VT(m)[0x168/8])(m,p1); }
f32 AttackModule__reaction_effect_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { auto* m=AT(a); return reinterpret_cast<f32(*)(void*,u64,bool)>(VT(m)[0x170/8])(m,p1,p2); }
void AttackModule__set_reaction_effect_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,bool p3) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64,u64,bool)>(VT(m)[0x178/8])(m,p1,p2,p3); }
f32 AttackModule__reaction_fix_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { auto* m=AT(a); return reinterpret_cast<f32(*)(void*,u64,bool)>(VT(m)[0x180/8])(m,p1,p2); }
void AttackModule__set_reaction_fix_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,bool p3) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64,u64,bool)>(VT(m)[0x188/8])(m,p1,p2,p3); }
f32 AttackModule__reaction_add_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { auto* m=AT(a); return reinterpret_cast<f32(*)(void*,u64,bool)>(VT(m)[0x190/8])(m,p1,p2); }
void AttackModule__set_reaction_add_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,bool p3) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64,u64,bool)>(VT(m)[0x198/8])(m,p1,p2,p3); }
f32 AttackModule__reaction_mul_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=AT(a); return reinterpret_cast<f32(*)(void*,u64)>(VT(m)[0x1a0/8])(m,p1); }
void AttackModule__set_pos_x_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x1a8/8])(m,p1); }
f32 AttackModule__pos_x_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { auto* m=AT(a); return reinterpret_cast<f32(*)(void*,u64,bool)>(VT(m)[0x1b0/8])(m,p1,p2); }
f32 AttackModule__pos_x_2_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=AT(a); return reinterpret_cast<f32(*)(void*,u64)>(VT(m)[0x1b8/8])(m,p1); }
f32 AttackModule__pos_y_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=AT(a); return reinterpret_cast<f32(*)(void*,u64)>(VT(m)[0x1c0/8])(m,p1); }
void* AttackModule__center_pos_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { auto* m=AT(a); return reinterpret_cast<void*(*)(void*,u64,bool)>(VT(m)[0x1c8/8])(m,p1,p2); }
f32 AttackModule__speed_x_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=AT(a); return reinterpret_cast<f32(*)(void*,u64)>(VT(m)[0x1d0/8])(m,p1); }
void AttackModule__set_speed_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x1e0/8])(m,p1); }
void* AttackModule__attack_data_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { auto* m=AT(a); return reinterpret_cast<void*(*)(void*,u64,bool)>(VT(m)[0x1e8/8])(m,p1,p2); }
void AttackModule__set_power_mul_status_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x1f0/8])(m,p1); }
f32 AttackModule__power_mul_status_impl(BattleObjectModuleAccessor* a) { auto* m=AT(a); return reinterpret_cast<f32(*)(void*)>(VT(m)[0x1f8/8])(m); }
void AttackModule__set_power_add_status_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x200/8])(m,p1); }
f32 AttackModule__power_add_status_impl(BattleObjectModuleAccessor* a) { auto* m=AT(a); return reinterpret_cast<f32(*)(void*)>(VT(m)[0x208/8])(m); }
void AttackModule__set_power_speed_status_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x210/8])(m,p1); }
f32 AttackModule__power_speed_status_impl(BattleObjectModuleAccessor* a) { auto* m=AT(a); return reinterpret_cast<f32(*)(void*)>(VT(m)[0x218/8])(m); }
void AttackModule__set_power_speed_limit_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x220/8])(m,p1); }
f32 AttackModule__power_speed_limit_impl(BattleObjectModuleAccessor* a) { auto* m=AT(a); return reinterpret_cast<f32(*)(void*)>(VT(m)[0x228/8])(m); }
void AttackModule__set_power_mul_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x230/8])(m,p1); }
f32 AttackModule__power_mul_impl(BattleObjectModuleAccessor* a) { auto* m=AT(a); return reinterpret_cast<f32(*)(void*)>(VT(m)[0x238/8])(m); }
void AttackModule__set_power_mul_2nd_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x240/8])(m,p1); }
f32 AttackModule__power_mul_2nd_impl(BattleObjectModuleAccessor* a) { auto* m=AT(a); return reinterpret_cast<f32(*)(void*)>(VT(m)[0x248/8])(m); }
void AttackModule__set_power_mul_3rd_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x250/8])(m,p1); }
f32 AttackModule__power_mul_3rd_impl(BattleObjectModuleAccessor* a) { auto* m=AT(a); return reinterpret_cast<f32(*)(void*)>(VT(m)[0x258/8])(m); }
void AttackModule__set_power_mul_4th_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=AT(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x260/8])(m,p1); }
f32 AttackModule__power_mul_4th_impl(BattleObjectModuleAccessor* a) { auto* m=AT(a); return reinterpret_cast<f32(*)(void*)>(VT(m)[0x268/8])(m); }
} // namespace app::lua_bind
