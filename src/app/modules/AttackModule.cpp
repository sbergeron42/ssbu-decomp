#include "app/BattleObjectModuleAccessor.h"
#include "app/modules/AttackModule.h"
#define AT(a) static_cast<AttackModule*>((a)->attack_module)
namespace app::lua_bind {
// Existing
bool AttackModule__is_attack_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { return AT(a)->is_attack(p1,p2); }
bool AttackModule__is_invalid_invincible_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { return AT(a)->is_invalid_invincible(p1,p2); }
bool AttackModule__is_invalid_xlu_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { return AT(a)->is_invalid_xlu(p1,p2); }
bool AttackModule__is_hit_abs_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind29AttackModule__is_hit_abs_implEPNS_26BattleObjectModuleAccessorEy");
bool AttackModule__is_hit_abs_impl(BattleObjectModuleAccessor* a) { return AT(a)->is_hit_abs(); }
bool AttackModule__is_infliction_impl(BattleObjectModuleAccessor* a,u64 p1) { return AT(a)->is_infliction(p1); }
bool AttackModule__is_infliction_status_impl(BattleObjectModuleAccessor* a,u64 p1) { return AT(a)->is_infliction_status(p1); }
bool AttackModule__is_power_up_reaction_impl(BattleObjectModuleAccessor* a) { return AT(a)->is_power_up_reaction(); }
bool AttackModule__is_attack_occur_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind34AttackModule__is_attack_occur_implEPNS_26BattleObjectModuleAccessorEy");
bool AttackModule__is_attack_occur_impl(BattleObjectModuleAccessor* a) { return AT(a)->is_attack_occur(); }
bool AttackModule__is_constraint_pos_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind36AttackModule__is_constraint_pos_implEPNS_26BattleObjectModuleAccessorEy");
bool AttackModule__is_constraint_pos_impl(BattleObjectModuleAccessor* a) { return AT(a)->is_constraint_pos(); }
bool AttackModule__is_no_dead_damage_fly_effect_impl(BattleObjectModuleAccessor* a) { return AT(a)->is_no_dead_damage_fly_effect(); }
bool AttackModule__is_critical_attack_impl(BattleObjectModuleAccessor* a) { return AT(a)->is_critical_attack(); }
void AttackModule__set_is_critical_attack_impl(BattleObjectModuleAccessor* a,bool p1) { AT(a)->set_is_critical_attack(p1); }
// Batch 1
void AttackModule__clear_all_impl(BattleObjectModuleAccessor* a) { AT(a)->clear_all(); }
void AttackModule__clear_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { AT(a)->clear(p1,p2); }
void AttackModule__sleep_partialy_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { AT(a)->sleep_partialy(p1,p2); }
void AttackModule__set_attack_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3) asm("_ZN3app8lua_bind29AttackModule__set_attack_implEPNS_26BattleObjectModuleAccessorEy");
void AttackModule__set_attack_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3) { AT(a)->set_attack(p1,p2,p3); }
void AttackModule__set_attack_2_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) asm("_ZN3app8lua_bind31AttackModule__set_attack_2_implEPNS_26BattleObjectModuleAccessorEy");
void AttackModule__set_attack_2_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { AT(a)->set_attack_2(p1,p2); }
void AttackModule__set_absolute_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3) asm("_ZN3app8lua_bind31AttackModule__set_absolute_implEPNS_26BattleObjectModuleAccessorEy");
void AttackModule__set_absolute_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3) { AT(a)->set_absolute(p1,p2,p3); }
void* AttackModule__hit_absolute_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3,u64 p4,u64 p5) asm("_ZN3app8lua_bind31AttackModule__hit_absolute_implEPNS_26BattleObjectModuleAccessorEy");
void* AttackModule__hit_absolute_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3,u64 p4,u64 p5) { return AT(a)->hit_absolute(p1,p2,p3,p4,p5); }
void* AttackModule__hit_absolute_joint_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3,u64 p4,u64 p5) asm("_ZN3app8lua_bind37AttackModule__hit_absolute_joint_implEPNS_26BattleObjectModuleAccessorEy");
void* AttackModule__hit_absolute_joint_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3,u64 p4,u64 p5) { return AT(a)->hit_absolute_joint(p1,p2,p3,p4,p5); }
void AttackModule__set_absolute_lr_impl(BattleObjectModuleAccessor* a,u64 p1) { AT(a)->set_absolute_lr(p1); }
void AttackModule__set_whole_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { AT(a)->set_whole(p1,p2); }
void AttackModule__sleep_impl(BattleObjectModuleAccessor* a,bool p1) { AT(a)->sleep(p1); }
u32 AttackModule__active_part_num_impl(BattleObjectModuleAccessor* a) { return AT(a)->active_part_num(); }
void AttackModule__set_invalid_invincible_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { AT(a)->set_invalid_invincible(p1,p2); }
void AttackModule__set_invalid_xlu_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { AT(a)->set_invalid_xlu(p1,p2); }
void AttackModule__set_power_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { AT(a)->set_power(p1,p2); }
void AttackModule__add_power_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { AT(a)->add_power(p1,p2); }
void AttackModule__set_vector_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,bool p3) { AT(a)->set_vector(p1,p2,p3); }
u32 AttackModule__size_impl(BattleObjectModuleAccessor* a,u64 p1) { return AT(a)->size(p1); }
void AttackModule__set_size_impl(BattleObjectModuleAccessor* a,u64 p1) { AT(a)->set_size(p1); }
void AttackModule__set_target_category_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) asm("_ZN3app8lua_bind38AttackModule__set_target_category_implEPNS_26BattleObjectModuleAccessorEy");
void AttackModule__set_target_category_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { AT(a)->set_target_category(p1,p2); }
void* AttackModule__off_target_kind_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) asm("_ZN3app8lua_bind34AttackModule__off_target_kind_implEPNS_26BattleObjectModuleAccessorEy");
void* AttackModule__off_target_kind_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { return AT(a)->off_target_kind(p1,p2); }
void AttackModule__set_offset_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) asm("_ZN3app8lua_bind29AttackModule__set_offset_implEPNS_26BattleObjectModuleAccessorEy");
void AttackModule__set_offset_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { AT(a)->set_offset(p1,p2); }
void AttackModule__set_offset2_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) asm("_ZN3app8lua_bind30AttackModule__set_offset2_implEPNS_26BattleObjectModuleAccessorEy");
void AttackModule__set_offset2_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { AT(a)->set_offset2(p1,p2); }
void AttackModule__get_offset2_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { AT(a)->get_offset2(p1,p2); }
void AttackModule__set_node_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) asm("_ZN3app8lua_bind27AttackModule__set_node_implEPNS_26BattleObjectModuleAccessorEy");
void AttackModule__set_node_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { AT(a)->set_node(p1,p2); }
void AttackModule__set_serial_hit_frame_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) asm("_ZN3app8lua_bind39AttackModule__set_serial_hit_frame_implEPNS_26BattleObjectModuleAccessorEy");
void AttackModule__set_serial_hit_frame_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { AT(a)->set_serial_hit_frame(p1,p2); }
void AttackModule__get_power_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2,bool p3) { AT(a)->get_power(p1,p2,p3); }
u32 AttackModule__group_impl(BattleObjectModuleAccessor* a,u64 p1) { return AT(a)->group(p1); }
f32 AttackModule__reaction_effect_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { return AT(a)->reaction_effect(p1,p2); }
void AttackModule__set_reaction_effect_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,bool p3) { AT(a)->set_reaction_effect(p1,p2,p3); }
f32 AttackModule__reaction_fix_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { return AT(a)->reaction_fix(p1,p2); }
void AttackModule__set_reaction_fix_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,bool p3) { AT(a)->set_reaction_fix(p1,p2,p3); }
f32 AttackModule__reaction_add_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { return AT(a)->reaction_add(p1,p2); }
void AttackModule__set_reaction_add_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,bool p3) { AT(a)->set_reaction_add(p1,p2,p3); }
void* AttackModule__reaction_mul_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind31AttackModule__reaction_mul_implEPNS_26BattleObjectModuleAccessorEy");
void* AttackModule__reaction_mul_impl(BattleObjectModuleAccessor* a) { return AT(a)->reaction_mul(); }
void AttackModule__set_pos_x_impl(BattleObjectModuleAccessor* a,u64 p1) { AT(a)->set_pos_x(p1); }
f32 AttackModule__pos_x_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { return AT(a)->pos_x(p1,p2); }
void* AttackModule__pos_x_2_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind26AttackModule__pos_x_2_implEPNS_26BattleObjectModuleAccessorEy");
void* AttackModule__pos_x_2_impl(BattleObjectModuleAccessor* a) { return AT(a)->pos_x_2(); }
void* AttackModule__pos_y_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind24AttackModule__pos_y_implEPNS_26BattleObjectModuleAccessorEy");
void* AttackModule__pos_y_impl(BattleObjectModuleAccessor* a) { return AT(a)->pos_y(); }
void* AttackModule__center_pos_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { return AT(a)->center_pos(p1,p2); }
void* AttackModule__speed_x_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind26AttackModule__speed_x_implEPNS_26BattleObjectModuleAccessorEy");
void* AttackModule__speed_x_impl(BattleObjectModuleAccessor* a) { return AT(a)->speed_x(); }
void AttackModule__set_speed_impl(BattleObjectModuleAccessor* a,u64 p1) { AT(a)->set_speed(p1); }
void* AttackModule__attack_data_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { return AT(a)->attack_data(p1,p2); }
void AttackModule__set_power_mul_status_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind39AttackModule__set_power_mul_status_implEPNS_26BattleObjectModuleAccessorEy");
void AttackModule__set_power_mul_status_impl(BattleObjectModuleAccessor* a) { AT(a)->set_power_mul_status(); }
f32 AttackModule__power_mul_status_impl(BattleObjectModuleAccessor* a) { return AT(a)->power_mul_status(); }
void AttackModule__set_power_add_status_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind39AttackModule__set_power_add_status_implEPNS_26BattleObjectModuleAccessorEy");
void AttackModule__set_power_add_status_impl(BattleObjectModuleAccessor* a) { AT(a)->set_power_add_status(); }
f32 AttackModule__power_add_status_impl(BattleObjectModuleAccessor* a) { return AT(a)->power_add_status(); }
void AttackModule__set_power_speed_status_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind41AttackModule__set_power_speed_status_implEPNS_26BattleObjectModuleAccessorEy");
void AttackModule__set_power_speed_status_impl(BattleObjectModuleAccessor* a) { AT(a)->set_power_speed_status(); }
f32 AttackModule__power_speed_status_impl(BattleObjectModuleAccessor* a) { return AT(a)->power_speed_status(); }
void AttackModule__set_power_speed_limit_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind40AttackModule__set_power_speed_limit_implEPNS_26BattleObjectModuleAccessorEy");
void AttackModule__set_power_speed_limit_impl(BattleObjectModuleAccessor* a) { AT(a)->set_power_speed_limit(); }
f32 AttackModule__power_speed_limit_impl(BattleObjectModuleAccessor* a) { return AT(a)->power_speed_limit(); }
void AttackModule__set_power_mul_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind32AttackModule__set_power_mul_implEPNS_26BattleObjectModuleAccessorEy");
void AttackModule__set_power_mul_impl(BattleObjectModuleAccessor* a) { AT(a)->set_power_mul(); }
f32 AttackModule__power_mul_impl(BattleObjectModuleAccessor* a) { return AT(a)->power_mul(); }
void AttackModule__set_power_mul_2nd_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind36AttackModule__set_power_mul_2nd_implEPNS_26BattleObjectModuleAccessorEy");
void AttackModule__set_power_mul_2nd_impl(BattleObjectModuleAccessor* a) { AT(a)->set_power_mul_2nd(); }
f32 AttackModule__power_mul_2nd_impl(BattleObjectModuleAccessor* a) { return AT(a)->power_mul_2nd(); }
void AttackModule__set_power_mul_3rd_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind36AttackModule__set_power_mul_3rd_implEPNS_26BattleObjectModuleAccessorEy");
void AttackModule__set_power_mul_3rd_impl(BattleObjectModuleAccessor* a) { AT(a)->set_power_mul_3rd(); }
f32 AttackModule__power_mul_3rd_impl(BattleObjectModuleAccessor* a) { return AT(a)->power_mul_3rd(); }
void AttackModule__set_power_mul_4th_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind36AttackModule__set_power_mul_4th_implEPNS_26BattleObjectModuleAccessorEy");
void AttackModule__set_power_mul_4th_impl(BattleObjectModuleAccessor* a) { AT(a)->set_power_mul_4th(); }
f32 AttackModule__power_mul_4th_impl(BattleObjectModuleAccessor* a) { return AT(a)->power_mul_4th(); }
// Batch 2
void AttackModule__set_power_mul_5th_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind36AttackModule__set_power_mul_5th_implEPNS_26BattleObjectModuleAccessorEy");
void AttackModule__set_power_mul_5th_impl(BattleObjectModuleAccessor* a) { AT(a)->set_power_mul_5th(); }
f32 AttackModule__power_mul_5th_impl(BattleObjectModuleAccessor* a) { return AT(a)->power_mul_5th(); }
void AttackModule__set_customize_attack_ratio_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind45AttackModule__set_customize_attack_ratio_implEPNS_26BattleObjectModuleAccessorEy");
void AttackModule__set_customize_attack_ratio_impl(BattleObjectModuleAccessor* a) { AT(a)->set_customize_attack_ratio(); }
f32 AttackModule__customize_attack_ratio_impl(BattleObjectModuleAccessor* a) { return AT(a)->customize_attack_ratio(); }
void AttackModule__set_reaction_mul_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind35AttackModule__set_reaction_mul_implEPNS_26BattleObjectModuleAccessorEy");
void AttackModule__set_reaction_mul_impl(BattleObjectModuleAccessor* a) { AT(a)->set_reaction_mul(); }
void AttackModule__set_reaction_mul_2nd_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind39AttackModule__set_reaction_mul_2nd_implEPNS_26BattleObjectModuleAccessorEy");
void AttackModule__set_reaction_mul_2nd_impl(BattleObjectModuleAccessor* a) { AT(a)->set_reaction_mul_2nd(); }
f32 AttackModule__reaction_mul_2nd_impl(BattleObjectModuleAccessor* a) { return AT(a)->reaction_mul_2nd(); }
void AttackModule__set_reaction_mul_3rd_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind39AttackModule__set_reaction_mul_3rd_implEPNS_26BattleObjectModuleAccessorEy");
void AttackModule__set_reaction_mul_3rd_impl(BattleObjectModuleAccessor* a) { AT(a)->set_reaction_mul_3rd(); }
f32 AttackModule__reaction_mul_3rd_impl(BattleObjectModuleAccessor* a) { return AT(a)->reaction_mul_3rd(); }
void AttackModule__set_reaction_mul_4th_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind39AttackModule__set_reaction_mul_4th_implEPNS_26BattleObjectModuleAccessorEy");
void AttackModule__set_reaction_mul_4th_impl(BattleObjectModuleAccessor* a) { AT(a)->set_reaction_mul_4th(); }
f32 AttackModule__reaction_mul_4th_impl(BattleObjectModuleAccessor* a) { return AT(a)->reaction_mul_4th(); }
void AttackModule__set_damage_reaction_mul_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind42AttackModule__set_damage_reaction_mul_implEPNS_26BattleObjectModuleAccessorEy");
void AttackModule__set_damage_reaction_mul_impl(BattleObjectModuleAccessor* a) { AT(a)->set_damage_reaction_mul(); }
f32 AttackModule__get_damage_reaction_mul_impl(BattleObjectModuleAccessor* a) { return AT(a)->get_damage_reaction_mul(); }
void AttackModule__set_shield_stiff_mul_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind39AttackModule__set_shield_stiff_mul_implEPNS_26BattleObjectModuleAccessorEy");
void AttackModule__set_shield_stiff_mul_impl(BattleObjectModuleAccessor* a) { AT(a)->set_shield_stiff_mul(); }
f32 AttackModule__shield_stiff_mul_impl(BattleObjectModuleAccessor* a) { return AT(a)->shield_stiff_mul(); }
void AttackModule__set_ignore_just_shield_impl(BattleObjectModuleAccessor* a,bool p1) { AT(a)->set_ignore_just_shield(p1); }
f32 AttackModule__get_lr_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { return AT(a)->get_lr(p1,p2); }
u32 AttackModule__part_size_impl(BattleObjectModuleAccessor* a) { return AT(a)->part_size(); }
void* AttackModule__ref_log_group_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) asm("_ZN3app8lua_bind32AttackModule__ref_log_group_implEPNS_26BattleObjectModuleAccessorEy");
void* AttackModule__ref_log_group_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { return AT(a)->ref_log_group(p1,p2); }
void AttackModule__un_ref_log_group_impl(BattleObjectModuleAccessor* a,u64 p1) { AT(a)->un_ref_log_group(p1); }
void* AttackModule__get_inflict_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind30AttackModule__get_inflict_implEPNS_26BattleObjectModuleAccessorEy");
void* AttackModule__get_inflict_impl(BattleObjectModuleAccessor* a) { return AT(a)->get_inflict(); }
void* AttackModule__get_inflict_status_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind37AttackModule__get_inflict_status_implEPNS_26BattleObjectModuleAccessorEy");
void* AttackModule__get_inflict_status_impl(BattleObjectModuleAccessor* a) { return AT(a)->get_inflict_status(); }
void AttackModule__set_indirect_info_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,bool p3,bool p4) { AT(a)->set_indirect_info(p1,p2,p3,p4); }
u32 AttackModule__indirect_object_id_impl(BattleObjectModuleAccessor* a) { return AT(a)->indirect_object_id(); }
u32 AttackModule__indirect_team_no_impl(BattleObjectModuleAccessor* a) { return AT(a)->indirect_team_no(); }
void AttackModule__set_restrict_impl(BattleObjectModuleAccessor* a,bool p1) { AT(a)->set_restrict(p1); }
void AttackModule__set_no_attacker_log_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2,bool p3) { AT(a)->set_no_attacker_log(p1,p2,p3); }
void AttackModule__set_catch_only_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2,bool p3) { AT(a)->set_catch_only(p1,p2,p3); }
void AttackModule__set_catch_only_all_impl(BattleObjectModuleAccessor* a,bool p1,bool p2) { AT(a)->set_catch_only_all(p1,p2); }
void AttackModule__set_attack_keep_rumble_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { AT(a)->set_attack_keep_rumble(p1,p2); }
f32 AttackModule__get_power_up_impl(BattleObjectModuleAccessor* a) { return AT(a)->get_power_up(); }
void AttackModule__set_power_up_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind31AttackModule__set_power_up_implEPNS_26BattleObjectModuleAccessorEy");
void AttackModule__set_power_up_impl(BattleObjectModuleAccessor* a) { AT(a)->set_power_up(); }
u32 AttackModule__get_power_up_attr_impl(BattleObjectModuleAccessor* a) { return AT(a)->get_power_up_attr(); }
void AttackModule__set_power_up_attr_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind36AttackModule__set_power_up_attr_implEPNS_26BattleObjectModuleAccessorEy");
void AttackModule__set_power_up_attr_impl(BattleObjectModuleAccessor* a) { AT(a)->set_power_up_attr(); }
u32 AttackModule__get_attacker_attribute_impl(BattleObjectModuleAccessor* a) { return AT(a)->get_attacker_attribute(); }
void AttackModule__set_attacker_attribute_impl(BattleObjectModuleAccessor* a,u64 p1) { AT(a)->set_attacker_attribute(p1); }
f32 AttackModule__get_power_apply_defense_impl(BattleObjectModuleAccessor* a,u64 p1) { return AT(a)->get_power_apply_defense(p1); }
void* AttackModule__attack_reference_pos_impl(BattleObjectModuleAccessor* a,u64 p1) { return AT(a)->attack_reference_pos(p1); }
void* AttackModule__attack_direction_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind35AttackModule__attack_direction_implEPNS_26BattleObjectModuleAccessorEy");
void* AttackModule__attack_direction_impl(BattleObjectModuleAccessor* a) { return AT(a)->attack_direction(); }
void AttackModule__set_attack_reference_joint_id_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3,u64 p4) asm("_ZN3app8lua_bind48AttackModule__set_attack_reference_joint_id_implEPNS_26BattleObjectModuleAccessorEy");
void AttackModule__set_attack_reference_joint_id_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3,u64 p4) { AT(a)->set_attack_reference_joint_id(p1,p2,p3,p4); }
void AttackModule__set_overlap_hit_impl(BattleObjectModuleAccessor* a,bool p1) { AT(a)->set_overlap_hit(p1); }
void AttackModule__set_no_team_impl(BattleObjectModuleAccessor* a,bool p1) { AT(a)->set_no_team(p1); }
void* AttackModule__disable_tip_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind30AttackModule__disable_tip_implEPNS_26BattleObjectModuleAccessorEy");
void* AttackModule__disable_tip_impl(BattleObjectModuleAccessor* a) { return AT(a)->disable_tip(); }
void AttackModule__relocate_impl(BattleObjectModuleAccessor* a,u64 p1) { AT(a)->relocate(p1); }
void AttackModule__set_lerp_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3) asm("_ZN3app8lua_bind27AttackModule__set_lerp_implEPNS_26BattleObjectModuleAccessorEy");
void AttackModule__set_lerp_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3) { AT(a)->set_lerp(p1,p2,p3); }
void AttackModule__clear_lerp_impl(BattleObjectModuleAccessor* a,u64 p1) { AT(a)->clear_lerp(p1); }
void AttackModule__set_lerp_ratio_impl(BattleObjectModuleAccessor* a,u64 p1) { AT(a)->set_lerp_ratio(p1); }
void AttackModule__set_attack_power_mul_pattern_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind47AttackModule__set_attack_power_mul_pattern_implEPNS_26BattleObjectModuleAccessorEy");
void AttackModule__set_attack_power_mul_pattern_impl(BattleObjectModuleAccessor* a) { AT(a)->set_attack_power_mul_pattern(); }
f32 AttackModule__get_attack_power_mul_pattern_impl(BattleObjectModuleAccessor* a) { return AT(a)->get_attack_power_mul_pattern(); }
void AttackModule__set_attack_power_mul_scale_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind45AttackModule__set_attack_power_mul_scale_implEPNS_26BattleObjectModuleAccessorEy");
void AttackModule__set_attack_power_mul_scale_impl(BattleObjectModuleAccessor* a) { AT(a)->set_attack_power_mul_scale(); }
f32 AttackModule__get_attack_power_mul_scale_impl(BattleObjectModuleAccessor* a) { return AT(a)->get_attack_power_mul_scale(); }
void AttackModule__set_lr_check_default_impl(BattleObjectModuleAccessor* a,u64 p1) { AT(a)->set_lr_check_default(p1); }
u32 AttackModule__lr_check_default_impl(BattleObjectModuleAccessor* a) { return AT(a)->lr_check_default(); }
void AttackModule__set_lr_check_front_impl(BattleObjectModuleAccessor* a,u64 p1) { AT(a)->set_lr_check_front(p1); }
void AttackModule__set_lr_check_back_impl(BattleObjectModuleAccessor* a,u64 p1) { AT(a)->set_lr_check_back(p1); }
void AttackModule__set_lr_check_front_lr_impl(BattleObjectModuleAccessor* a,u64 p1) { AT(a)->set_lr_check_front_lr(p1); }
void AttackModule__set_disable_power_add_status_zero_impl(BattleObjectModuleAccessor* a,bool p1) { AT(a)->set_disable_power_add_status_zero(p1); }
void AttackModule__reset_status_attack_impl(BattleObjectModuleAccessor* a,u64 p1) { AT(a)->reset_status_attack(p1); }
void* AttackModule__damage_shake_scale_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind37AttackModule__damage_shake_scale_implEPNS_26BattleObjectModuleAccessorEy");
void* AttackModule__damage_shake_scale_impl(BattleObjectModuleAccessor* a) { return AT(a)->damage_shake_scale(); }
// Batch 3
void AttackModule__set_damage_shake_scale_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind41AttackModule__set_damage_shake_scale_implEPNS_26BattleObjectModuleAccessorEy");
void AttackModule__set_damage_shake_scale_impl(BattleObjectModuleAccessor* a) { AT(a)->set_damage_shake_scale(); }
void AttackModule__set_latest_no_impl(BattleObjectModuleAccessor* a,u64 p1) { AT(a)->set_latest_no(p1); }
void AttackModule__set_latest_absolute_impl(BattleObjectModuleAccessor* a,bool p1) { AT(a)->set_latest_absolute(p1); }
void AttackModule__set_reflect_attack_impl(BattleObjectModuleAccessor* a,bool p1) { AT(a)->set_reflect_attack(p1); }
void AttackModule__set_power_up_reaction_impl(BattleObjectModuleAccessor* a,bool p1) { AT(a)->set_power_up_reaction(p1); }
void AttackModule__set_attack_scale_impl(BattleObjectModuleAccessor* a,bool p1) { AT(a)->set_attack_scale(p1); }
void AttackModule__set_attack_scale_2nd_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind39AttackModule__set_attack_scale_2nd_implEPNS_26BattleObjectModuleAccessorEy");
void AttackModule__set_attack_scale_2nd_impl(BattleObjectModuleAccessor* a) { AT(a)->set_attack_scale_2nd(); }
void AttackModule__set_base_offset_impl(BattleObjectModuleAccessor* a,u64 p1) { AT(a)->set_base_offset(p1); }
void AttackModule__set_constraint_pos_impl(BattleObjectModuleAccessor* a,bool p1) { AT(a)->set_constraint_pos(p1); }
void AttackModule__set_no_dead_damage_fly_effect_impl(BattleObjectModuleAccessor* a,bool p1) { AT(a)->set_no_dead_damage_fly_effect(p1); }
void AttackModule__set_damage_effect_mul_scale_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind46AttackModule__set_damage_effect_mul_scale_implEPNS_26BattleObjectModuleAccessorEy");
void AttackModule__set_damage_effect_mul_scale_impl(BattleObjectModuleAccessor* a) { AT(a)->set_damage_effect_mul_scale(); }
f32 AttackModule__damage_effect_mul_scale_impl(BattleObjectModuleAccessor* a) { return AT(a)->damage_effect_mul_scale(); }
void AttackModule__set_attack_level_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) asm("_ZN3app8lua_bind35AttackModule__set_attack_level_implEPNS_26BattleObjectModuleAccessorEy");
void AttackModule__set_attack_level_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { AT(a)->set_attack_level(p1,p2); }
void AttackModule__set_ink_value_impl(BattleObjectModuleAccessor* a,u64 p1) { AT(a)->set_ink_value(p1); }
void AttackModule__set_special_paint_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) asm("_ZN3app8lua_bind36AttackModule__set_special_paint_implEPNS_26BattleObjectModuleAccessorEy");
void AttackModule__set_special_paint_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { AT(a)->set_special_paint(p1,p2); }
void AttackModule__set_paralyze_frame_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,bool p3) asm("_ZN3app8lua_bind37AttackModule__set_paralyze_frame_implEPNS_26BattleObjectModuleAccessorEb");
void AttackModule__set_paralyze_frame_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,bool p3) { AT(a)->set_paralyze_frame(p1,p2,p3); }
void AttackModule__set_poison_param_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3,bool p4) asm("_ZN3app8lua_bind35AttackModule__set_poison_param_implEPNS_26BattleObjectModuleAccessorEb");
void AttackModule__set_poison_param_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3,bool p4) { AT(a)->set_poison_param(p1,p2,p3,p4); }
void AttackModule__set_optional_hit_effect_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) asm("_ZN3app8lua_bind42AttackModule__set_optional_hit_effect_implEPNS_26BattleObjectModuleAccessorEy");
void AttackModule__set_optional_hit_effect_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { AT(a)->set_optional_hit_effect(p1,p2); }
void AttackModule__set_optional_hit_sound_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) asm("_ZN3app8lua_bind41AttackModule__set_optional_hit_sound_implEPNS_26BattleObjectModuleAccessorEy");
void AttackModule__set_optional_hit_sound_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { AT(a)->set_optional_hit_sound(p1,p2); }
void AttackModule__set_no_comp_damage_motion_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) asm("_ZN3app8lua_bind44AttackModule__set_no_comp_damage_motion_implEPNS_26BattleObjectModuleAccessorEb");
void AttackModule__set_no_comp_damage_motion_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { AT(a)->set_no_comp_damage_motion(p1,p2); }
void AttackModule__set_no_finish_camera_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2,bool p3) asm("_ZN3app8lua_bind39AttackModule__set_no_finish_camera_implEPNS_26BattleObjectModuleAccessorEyb");
void AttackModule__set_no_finish_camera_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2,bool p3) { AT(a)->set_no_finish_camera(p1,p2,p3); }
void AttackModule__set_no_finish_camera_ex_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2,bool p3) asm("_ZN3app8lua_bind42AttackModule__set_no_finish_camera_ex_implEPNS_26BattleObjectModuleAccessorEyb");
void AttackModule__set_no_finish_camera_ex_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2,bool p3) { AT(a)->set_no_finish_camera_ex(p1,p2,p3); }
void AttackModule__set_final_finish_cut_in_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2,bool p3,bool p4) asm("_ZN3app8lua_bind42AttackModule__set_final_finish_cut_in_implEPNS_26BattleObjectModuleAccessorEybb");
void AttackModule__set_final_finish_cut_in_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2,bool p3,bool p4) { AT(a)->set_final_finish_cut_in(p1,p2,p3,p4); }
void AttackModule__set_no_dead_all_impl(BattleObjectModuleAccessor* a,bool p1,bool p2) asm("_ZN3app8lua_bind34AttackModule__set_no_dead_all_implEPNS_26BattleObjectModuleAccessorEyb");
void AttackModule__set_no_dead_all_impl(BattleObjectModuleAccessor* a,bool p1,bool p2) { AT(a)->set_no_dead_all(p1,p2); }
void AttackModule__set_no_damage_orbit_all_impl(BattleObjectModuleAccessor* a,bool p1,bool p2) asm("_ZN3app8lua_bind42AttackModule__set_no_damage_orbit_all_implEPNS_26BattleObjectModuleAccessorEyb");
void AttackModule__set_no_damage_orbit_all_impl(BattleObjectModuleAccessor* a,bool p1,bool p2) { AT(a)->set_no_damage_orbit_all(p1,p2); }
void AttackModule__set_captured_same_time_attack_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) asm("_ZN3app8lua_bind48AttackModule__set_captured_same_time_attack_implEPNS_26BattleObjectModuleAccessorEb");
void AttackModule__set_captured_same_time_attack_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { AT(a)->set_captured_same_time_attack(p1,p2); }
void AttackModule__set_captured_same_time_attack_damage_mul_impl(BattleObjectModuleAccessor* a,u64 p1) { AT(a)->set_captured_same_time_attack_damage_mul(p1); }
void AttackModule__set_attack_composition_speed_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) asm("_ZN3app8lua_bind47AttackModule__set_attack_composition_speed_implEPNS_26BattleObjectModuleAccessorEb");
void AttackModule__set_attack_composition_speed_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { AT(a)->set_attack_composition_speed(p1,p2); }
void AttackModule__set_attack_camera_quake_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,bool p3) asm("_ZN3app8lua_bind42AttackModule__set_attack_camera_quake_implEPNS_26BattleObjectModuleAccessorEb");
void AttackModule__set_attack_camera_quake_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,bool p3) { AT(a)->set_attack_camera_quake(p1,p2,p3); }
void AttackModule__set_attack_no_weight_reaction_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,bool p3) asm("_ZN3app8lua_bind48AttackModule__set_attack_no_weight_reaction_implEPNS_26BattleObjectModuleAccessorEb");
void AttackModule__set_attack_no_weight_reaction_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,bool p3) { AT(a)->set_attack_no_weight_reaction(p1,p2,p3); }
void AttackModule__set_attack_no_weight_reaction_all_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) asm("_ZN3app8lua_bind52AttackModule__set_attack_no_weight_reaction_all_implEPNS_26BattleObjectModuleAccessorEb");
void AttackModule__set_attack_no_weight_reaction_all_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { AT(a)->set_attack_no_weight_reaction_all(p1,p2); }
void AttackModule__set_attack_no_reaction_search_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,bool p3) asm("_ZN3app8lua_bind48AttackModule__set_attack_no_reaction_search_implEPNS_26BattleObjectModuleAccessorEb");
void AttackModule__set_attack_no_reaction_search_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,bool p3) { AT(a)->set_attack_no_reaction_search(p1,p2,p3); }
void AttackModule__clear_inflict_kind_status_impl(BattleObjectModuleAccessor* a) { AT(a)->clear_inflict_kind_status(); }
void AttackModule__set_force_reaction_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2,bool p3) asm("_ZN3app8lua_bind37AttackModule__set_force_reaction_implEPNS_26BattleObjectModuleAccessorEyb");
void AttackModule__set_force_reaction_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2,bool p3) { AT(a)->set_force_reaction(p1,p2,p3); }
void AttackModule__set_accept_no_lr_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) asm("_ZN3app8lua_bind35AttackModule__set_accept_no_lr_implEPNS_26BattleObjectModuleAccessorEb");
void AttackModule__set_accept_no_lr_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { AT(a)->set_accept_no_lr(p1,p2); }
void AttackModule__set_nearest_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) asm("_ZN3app8lua_bind30AttackModule__set_nearest_implEPNS_26BattleObjectModuleAccessorEb");
void AttackModule__set_nearest_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { AT(a)->set_nearest(p1,p2); }
void AttackModule__set_vec_target_pos_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3,u64 p4,bool p5) asm("_ZN3app8lua_bind37AttackModule__set_vec_target_pos_implEPNS_26BattleObjectModuleAccessorEb");
void AttackModule__set_vec_target_pos_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3,u64 p4,bool p5) { AT(a)->set_vec_target_pos(p1,p2,p3,p4,p5); }
void AttackModule__enable_safe_pos_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind34AttackModule__enable_safe_pos_implEPNS_26BattleObjectModuleAccessorEy");
void AttackModule__enable_safe_pos_impl(BattleObjectModuleAccessor* a) { AT(a)->enable_safe_pos(); }
void AttackModule__reset_safe_pos_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind33AttackModule__reset_safe_pos_implEPNS_26BattleObjectModuleAccessorEy");
void AttackModule__reset_safe_pos_impl(BattleObjectModuleAccessor* a) { AT(a)->reset_safe_pos(); }
f32 AttackModule__get_critical_attack_damage_mul_impl(BattleObjectModuleAccessor* a) { return AT(a)->get_critical_attack_damage_mul(); }
f32 AttackModule__get_critical_attack_reaction_mul_impl(BattleObjectModuleAccessor* a) { return AT(a)->get_critical_attack_reaction_mul(); }
void AttackModule__set_critical_attack_damage_mul_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind49AttackModule__set_critical_attack_damage_mul_implEPNS_26BattleObjectModuleAccessorEy");
void AttackModule__set_critical_attack_damage_mul_impl(BattleObjectModuleAccessor* a) { AT(a)->set_critical_attack_damage_mul(); }
void AttackModule__set_critical_attack_reaction_mul_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind51AttackModule__set_critical_attack_reaction_mul_implEPNS_26BattleObjectModuleAccessorEy");
void AttackModule__set_critical_attack_reaction_mul_impl(BattleObjectModuleAccessor* a) { AT(a)->set_critical_attack_reaction_mul(); }
void AttackModule__enable_attack_r_fix_damage_speed_up_all_impl(BattleObjectModuleAccessor* a,bool p1) { AT(a)->enable_attack_r_fix_damage_speed_up_all(p1); }
void AttackModule__set_add_reaction_frame_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) asm("_ZN3app8lua_bind41AttackModule__set_add_reaction_frame_implEPNS_26BattleObjectModuleAccessorEb");
void AttackModule__set_add_reaction_frame_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { AT(a)->set_add_reaction_frame(p1,p2); }
void AttackModule__set_add_reaction_frame_revised_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) asm("_ZN3app8lua_bind49AttackModule__set_add_reaction_frame_revised_implEPNS_26BattleObjectModuleAccessorEb");
void AttackModule__set_add_reaction_frame_revised_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { AT(a)->set_add_reaction_frame_revised(p1,p2); }
void AttackModule__set_set_off_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) asm("_ZN3app8lua_bind30AttackModule__set_set_off_implEPNS_26BattleObjectModuleAccessorEy");
void AttackModule__set_set_off_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { AT(a)->set_set_off(p1,p2); }
void AttackModule__set_no_squat_damage_reaction_mul_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2,bool p3) asm("_ZN3app8lua_bind51AttackModule__set_no_squat_damage_reaction_mul_implEPNS_26BattleObjectModuleAccessorEyb");
void AttackModule__set_no_squat_damage_reaction_mul_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2,bool p3) { AT(a)->set_no_squat_damage_reaction_mul(p1,p2,p3); }
void AttackModule__set_no_damage_fly_smoke_all_impl(BattleObjectModuleAccessor* a,bool p1,bool p2) asm("_ZN3app8lua_bind46AttackModule__set_no_damage_fly_smoke_all_implEPNS_26BattleObjectModuleAccessorEyb");
void AttackModule__set_no_damage_fly_smoke_all_impl(BattleObjectModuleAccessor* a,bool p1,bool p2) { AT(a)->set_no_damage_fly_smoke_all(p1,p2); }
void AttackModule__set_no_uniq_effect_all_impl(BattleObjectModuleAccessor* a,bool p1,bool p2) asm("_ZN3app8lua_bind41AttackModule__set_no_uniq_effect_all_implEPNS_26BattleObjectModuleAccessorEyb");
void AttackModule__set_no_uniq_effect_all_impl(BattleObjectModuleAccessor* a,bool p1,bool p2) { AT(a)->set_no_uniq_effect_all(p1,p2); }
void AttackModule__set_no_world_scale_impl(BattleObjectModuleAccessor* a,bool p1) { AT(a)->set_no_world_scale(p1); }
void AttackModule__set_attack_height_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,bool p3) asm("_ZN3app8lua_bind36AttackModule__set_attack_height_implEPNS_26BattleObjectModuleAccessorEb");
void AttackModule__set_attack_height_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,bool p3) { AT(a)->set_attack_height(p1,p2,p3); }
void AttackModule__set_attack_height_all_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) asm("_ZN3app8lua_bind40AttackModule__set_attack_height_all_implEPNS_26BattleObjectModuleAccessorEb");
void AttackModule__set_attack_height_all_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { AT(a)->set_attack_height_all(p1,p2); }
void AttackModule__set_no_hop_opponent_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2,bool p3) asm("_ZN3app8lua_bind38AttackModule__set_no_hop_opponent_implEPNS_26BattleObjectModuleAccessorEyb");
void AttackModule__set_no_hop_opponent_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2,bool p3) { AT(a)->set_no_hop_opponent(p1,p2,p3); }
void AttackModule__set_no_hop_opponent_all_impl(BattleObjectModuleAccessor* a,bool p1,bool p2) asm("_ZN3app8lua_bind42AttackModule__set_no_hop_opponent_all_implEPNS_26BattleObjectModuleAccessorEyb");
void AttackModule__set_no_hop_opponent_all_impl(BattleObjectModuleAccessor* a,bool p1,bool p2) { AT(a)->set_no_hop_opponent_all(p1,p2); }
void AttackModule__set_ice_frame_mul_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) asm("_ZN3app8lua_bind36AttackModule__set_ice_frame_mul_implEPNS_26BattleObjectModuleAccessorEb");
void AttackModule__set_ice_frame_mul_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { AT(a)->set_ice_frame_mul(p1,p2); }
void AttackModule__set_down_only_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) asm("_ZN3app8lua_bind32AttackModule__set_down_only_implEPNS_26BattleObjectModuleAccessorEb");
void AttackModule__set_down_only_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { AT(a)->set_down_only(p1,p2); }
void AttackModule__set_ignore_capture_cut_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) asm("_ZN3app8lua_bind41AttackModule__set_ignore_capture_cut_implEPNS_26BattleObjectModuleAccessorEb");
void AttackModule__set_ignore_capture_cut_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { AT(a)->set_ignore_capture_cut(p1,p2); }
void AttackModule__set_ignore_ground_shield_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) asm("_ZN3app8lua_bind43AttackModule__set_ignore_ground_shield_implEPNS_26BattleObjectModuleAccessorEb");
void AttackModule__set_ignore_ground_shield_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { AT(a)->set_ignore_ground_shield(p1,p2); }
void AttackModule__set_attack_camera_quake_forced_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,bool p3) asm("_ZN3app8lua_bind49AttackModule__set_attack_camera_quake_forced_implEPNS_26BattleObjectModuleAccessorEb");
void AttackModule__set_attack_camera_quake_forced_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,bool p3) { AT(a)->set_attack_camera_quake_forced(p1,p2,p3); }
void AttackModule__set_lr_check_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) asm("_ZN3app8lua_bind31AttackModule__set_lr_check_implEPNS_26BattleObjectModuleAccessorEy");
void AttackModule__set_lr_check_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { AT(a)->set_lr_check(p1,p2); }
void AttackModule__resume_catch_absolute_damage_impl(BattleObjectModuleAccessor* a) { AT(a)->resume_catch_absolute_damage(); }
void* AttackModule__init_attack_pos_impl(BattleObjectModuleAccessor* a,u64 p1) asm("_ZN3app8lua_bind34AttackModule__init_attack_pos_implEPNS_26BattleObjectModuleAccessorE");
void* AttackModule__init_attack_pos_impl(BattleObjectModuleAccessor* a,u64 p1) { return AT(a)->init_attack_pos(p1); }
// 7101fd04f0 -- speed_impl: vtable[59] -- non-leaf (NX Clang frame)
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void* AttackModule__speed_impl(BattleObjectModuleAccessor* a) {
    asm("stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "ldr x0, [x0, #0xa0]\n"
        "ldr x8, [x0]\n"
        "ldr x8, [x8, #0x1d8]\n"
        "blr x8\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n");
}
#else
void* AttackModule__speed_impl(BattleObjectModuleAccessor* a) { return AT(a)->speed(); }
#endif
// 7101fd0930 -- attack_part_speed_impl: vtable[148] -- non-leaf (NX Clang frame)
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void* AttackModule__attack_part_speed_impl(BattleObjectModuleAccessor* a, u64 p1) {
    asm("stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "ldr x0, [x0, #0xa0]\n"
        "ldr x8, [x0]\n"
        "ldr x8, [x8, #0x4a0]\n"
        "blr x8\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n");
}
#else
void* AttackModule__attack_part_speed_impl(BattleObjectModuleAccessor* a, u64 p1) { return AT(a)->attack_part_speed(p1); }
#endif
} // namespace app::lua_bind
