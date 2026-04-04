#include "app/BattleObjectModuleAccessor.h"
#include "app/modules/LinkModule.h"
#define LM(a) static_cast<LinkModule*>((a)->link_module)
namespace app::lua_bind {
// -- Named dispatchers with asm symbol overrides --
void* LinkModule__get_link_speed_impl(BattleObjectModuleAccessor* a,u64 p1) asm("_ZN3app8lua_bind31LinkModule__get_link_speed_implEPNS_26BattleObjectModuleAccessorE");
void* LinkModule__get_link_speed_impl(BattleObjectModuleAccessor* a,u64 p1) { return LM(a)->get_link_speed(p1); }
u32 LinkModule__get_model_constraint_flag_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind42LinkModule__get_model_constraint_flag_implEPNS_26BattleObjectModuleAccessorEy");
u32 LinkModule__get_model_constraint_flag_impl(BattleObjectModuleAccessor* a) { return LM(a)->get_model_constraint_flag(); }
void* LinkModule__get_model_constraint_joint_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind43LinkModule__get_model_constraint_joint_implEPNS_26BattleObjectModuleAccessorEy");
void* LinkModule__get_model_constraint_joint_impl(BattleObjectModuleAccessor* a) { return LM(a)->get_model_constraint_joint(); }
void* LinkModule__get_model_constraint_target_joint_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind50LinkModule__get_model_constraint_target_joint_implEPNS_26BattleObjectModuleAccessorEy");
void* LinkModule__get_model_constraint_target_joint_impl(BattleObjectModuleAccessor* a) { return LM(a)->get_model_constraint_target_joint(); }
u32 LinkModule__get_model_constraint_no_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind40LinkModule__get_model_constraint_no_implEPNS_26BattleObjectModuleAccessorEy");
u32 LinkModule__get_model_constraint_no_impl(BattleObjectModuleAccessor* a) { return LM(a)->get_model_constraint_no(); }
void* LinkModule__adjust_model_constraint_posture_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) asm("_ZN3app8lua_bind48LinkModule__adjust_model_constraint_posture_implEPNS_26BattleObjectModuleAccessorEy");
void* LinkModule__adjust_model_constraint_posture_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { return LM(a)->adjust_model_constraint_posture(p1,p2); }
void* LinkModule__get_model_constraint_target_joint_rotation_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind59LinkModule__get_model_constraint_target_joint_rotation_implEPNS_26BattleObjectModuleAccessorEy");
void* LinkModule__get_model_constraint_target_joint_rotation_impl(BattleObjectModuleAccessor* a) { return LM(a)->get_model_constraint_target_joint_rotation(); }
void* LinkModule__get_node_rotation_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3) asm("_ZN3app8lua_bind34LinkModule__get_node_rotation_implEPNS_26BattleObjectModuleAccessorEy");
void* LinkModule__get_node_rotation_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3) { return LM(a)->get_node_rotation(p1,p2,p3); }
void* LinkModule__get_constraint_model_scale_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind43LinkModule__get_constraint_model_scale_implEPNS_26BattleObjectModuleAccessorEy");
void* LinkModule__get_constraint_model_scale_impl(BattleObjectModuleAccessor* a) { return LM(a)->get_constraint_model_scale(); }
void* LinkModule__get_constraint_translate_offset_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind48LinkModule__get_constraint_translate_offset_implEPNS_26BattleObjectModuleAccessorEy");
void* LinkModule__get_constraint_translate_offset_impl(BattleObjectModuleAccessor* a) { return LM(a)->get_constraint_translate_offset(); }
bool LinkModule__chk_attribute_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) asm("_ZN3app8lua_bind30LinkModule__chk_attribute_implEPNS_26BattleObjectModuleAccessorEy");
bool LinkModule__chk_attribute_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { return LM(a)->chk_attribute(p1,p2); }
void* LinkModule__get_node_catprue_pos_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) asm("_ZN3app8lua_bind37LinkModule__get_node_catprue_pos_implEPNS_26BattleObjectModuleAccessorEy");
void* LinkModule__get_node_catprue_pos_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { return LM(a)->get_node_catprue_pos(p1,p2); }
// -- Simple dispatchers --
void* LinkModule__get_node_object_id_impl(BattleObjectModuleAccessor* a,u64 p1) { return LM(a)->get_node_object_id(p1); }
void* LinkModule__chk_link_stop_impl(BattleObjectModuleAccessor* a) { return LM(a)->chk_link_stop(); }
void* LinkModule__chk_link_visibility_impl(BattleObjectModuleAccessor* a) { return LM(a)->chk_link_visibility(); }
void* LinkModule__get_link_scale_impl(BattleObjectModuleAccessor* a) { return LM(a)->get_link_scale(); }
void* LinkModule__get_model_constraint_joint_global_position_impl(BattleObjectModuleAccessor* a,u64 p1) { return LM(a)->get_model_constraint_joint_global_position(p1); }
void* LinkModule__get_model_constraint_joint_global_position_recursive_impl(BattleObjectModuleAccessor* a,u64 p1) { return LM(a)->get_model_constraint_joint_global_position_recursive(p1); }
bool LinkModule__chk_linked_attribute_impl(BattleObjectModuleAccessor* a,u64 p1) { return LM(a)->chk_linked_attribute(p1); }
// -- Link management --
void* LinkModule__link_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { return LM(a)->link(p1,p2); }
void* LinkModule__unlink_all_impl(BattleObjectModuleAccessor* a) { return LM(a)->unlink_all(); }
void* LinkModule__unlink_node_impl(BattleObjectModuleAccessor* a,u64 p1) { return LM(a)->unlink_node(p1); }
void* LinkModule__unlink_node_all_impl(BattleObjectModuleAccessor* a) { return LM(a)->unlink_node_all(); }
void* LinkModule__unlink_impl(BattleObjectModuleAccessor* a,u64 p1) { return LM(a)->unlink(p1); }
bool LinkModule__is_link_impl(BattleObjectModuleAccessor* a,u64 p1) { return LM(a)->is_link(p1); }
bool LinkModule__is_linked_impl(BattleObjectModuleAccessor* a,u64 p1) { return LM(a)->is_linked(p1); }
u32 LinkModule__get_parent_id_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { return LM(a)->get_parent_id(p1,p2); }
void* LinkModule__search_parent_impl(BattleObjectModuleAccessor* a,u64 p1) { return LM(a)->search_parent(p1); }
void* LinkModule__search_parent_attr_impl(BattleObjectModuleAccessor* a,u64 p1) { return LM(a)->search_parent_attr(p1); }
void* LinkModule__search_node_impl(BattleObjectModuleAccessor* a,u64 p1) { return LM(a)->search_node(p1); }
void* LinkModule__send_event_parents_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { return LM(a)->send_event_parents(p1,p2); }
void* LinkModule__send_event_parents_struct_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { return LM(a)->send_event_parents_struct(p1,p2); }
void* LinkModule__send_event_nodes_struct_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3) { return LM(a)->send_event_nodes_struct(p1,p2,p3); }
void* LinkModule__send_event_nodes_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3) { return LM(a)->send_event_nodes(p1,p2,p3); }
void* LinkModule__send_event_nodes_throw_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,bool p3,u64 p4,u64 p5,u64 p6) { return LM(a)->send_event_nodes_throw(p1,p2,p3,p4,p5,p6); }
// -- Node damage --
bool LinkModule__is_node_damage_reaction_impl(BattleObjectModuleAccessor* a,u64 p1) { return LM(a)->is_node_damage_reaction(p1); }
bool LinkModule__is_node_damage_capture_cut_impl(BattleObjectModuleAccessor* a,u64 p1) { return LM(a)->is_node_damage_capture_cut(p1); }
bool LinkModule__is_valid_link_stop_impl(BattleObjectModuleAccessor* a) { return LM(a)->is_valid_link_stop(); }
bool LinkModule__is_link_pos_impl(BattleObjectModuleAccessor* a) { return LM(a)->is_link_pos(); }
void LinkModule__update_link_pos_impl(BattleObjectModuleAccessor* a) { LM(a)->update_link_pos(); }
void* LinkModule__get_parent_scale_impl(BattleObjectModuleAccessor* a,u64 p1) { return LM(a)->get_parent_scale(p1); }
// -- Parent model/joint queries --
void* LinkModule__get_parent_model_joint_global_position_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,bool p3) { return LM(a)->get_parent_model_joint_global_position(p1,p2,p3); }
void* LinkModule__get_parent_model_joint_global_rotation_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,bool p3) { return LM(a)->get_parent_model_joint_global_rotation(p1,p2,p3); }
void* LinkModule__get_parent_motion_frame_impl(BattleObjectModuleAccessor* a,u64 p1) { return LM(a)->get_parent_motion_frame(p1); }
void* LinkModule__get_parent_motion_whole_rate_impl(BattleObjectModuleAccessor* a,u64 p1) { return LM(a)->get_parent_motion_whole_rate(p1); }
void* LinkModule__get_parent_motion_rate_impl(BattleObjectModuleAccessor* a,u64 p1) { return LM(a)->get_parent_motion_rate(p1); }
u32 LinkModule__get_parent_motion_kind_impl(BattleObjectModuleAccessor* a,u64 p1) { return LM(a)->get_parent_motion_kind(p1); }
u32 LinkModule__get_parent_situation_kind_impl(BattleObjectModuleAccessor* a,u64 p1) { return LM(a)->get_parent_situation_kind(p1); }
u32 LinkModule__get_parent_status_kind_impl(BattleObjectModuleAccessor* a,u64 p1) { return LM(a)->get_parent_status_kind(p1); }
void* LinkModule__get_parent_lr_impl(BattleObjectModuleAccessor* a,u64 p1) { return LM(a)->get_parent_lr(p1); }
void* LinkModule__get_parent_sum_speed_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { return LM(a)->get_parent_sum_speed(p1,p2); }
u32 LinkModule__get_parent_object_id_impl(BattleObjectModuleAccessor* a,u64 p1) { return LM(a)->get_parent_object_id(p1); }
bool LinkModule__is_capture_damage_parent_object_id_impl(BattleObjectModuleAccessor* a,u64 p1) { return LM(a)->is_capture_damage_parent_object_id(p1); }
// -- Parent pos (with asm barriers) --
void* LinkModule__get_parent_pos_impl(BattleObjectModuleAccessor* a) { void* ret = LM(a)->get_parent_pos(); asm(""); return ret; }
void* LinkModule__get_parent_prev_pos_impl(BattleObjectModuleAccessor* a) { void* ret = LM(a)->get_parent_prev_pos(); asm(""); return ret; }
// -- Parent damage/state --
void* LinkModule__get_parent_rot_impl(BattleObjectModuleAccessor* a,u64 p1) { return LM(a)->get_parent_rot(p1); }
void* LinkModule__get_parent_damage_impl(BattleObjectModuleAccessor* a,u64 p1) { return LM(a)->get_parent_damage(p1); }
void* LinkModule__get_parent_damage_reaction_impl(BattleObjectModuleAccessor* a,u64 p1) { return LM(a)->get_parent_damage_reaction(p1); }
void* LinkModule__get_parent_damage_power_max_impl(BattleObjectModuleAccessor* a,u64 p1) { return LM(a)->get_parent_damage_power_max(p1); }
void* LinkModule__get_parent_top_angle_impl(BattleObjectModuleAccessor* a,u64 p1) { return LM(a)->get_parent_top_angle(p1); }
void LinkModule__set_node_scale_power_mul_impl(BattleObjectModuleAccessor* a) { LM(a)->set_node_scale_power_mul(); }
void LinkModule__set_node_link_scale_impl(BattleObjectModuleAccessor* a,bool p1) { LM(a)->set_node_link_scale(p1); }
bool LinkModule__is_parent_damage_reaction_impl(BattleObjectModuleAccessor* a,u64 p1) { return LM(a)->is_parent_damage_reaction(p1); }
bool LinkModule__is_parent_damage_catch_cut_impl(BattleObjectModuleAccessor* a,u64 p1) { return LM(a)->is_parent_damage_catch_cut(p1); }
void* LinkModule__get_parent_total_hit_status_impl(BattleObjectModuleAccessor* a,u64 p1) { return LM(a)->get_parent_total_hit_status(p1); }
bool LinkModule__is_valid_parent_shape_impl(BattleObjectModuleAccessor* a,u64 p1) { return LM(a)->is_valid_parent_shape(p1); }
void* LinkModule__get_parent_shape_center_pos_impl(BattleObjectModuleAccessor* a,u64 p1) { return LM(a)->get_parent_shape_center_pos(p1); }
void* LinkModule__get_parent_shape_center_pos_object_id_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { return LM(a)->get_parent_shape_center_pos_object_id(p1,p2); }
// -- Power up --
bool LinkModule__is_parent_effect_sync_scale_impl(BattleObjectModuleAccessor* a,u64 p1) { return LM(a)->is_parent_effect_sync_scale(p1); }
bool LinkModule__is_link_power_up_impl(BattleObjectModuleAccessor* a) { return LM(a)->is_link_power_up(); }
void* LinkModule__get_parent_power_up_attack_impl(BattleObjectModuleAccessor* a) { return LM(a)->get_parent_power_up_attack(); }
void* LinkModule__get_parent_power_up_defense_impl(BattleObjectModuleAccessor* a) { return LM(a)->get_parent_power_up_defense(); }
void* LinkModule__get_parent_power_up_attr_impl(BattleObjectModuleAccessor* a) { return LM(a)->get_parent_power_up_attr(); }
f32 LinkModule__get_parent_customize_attack_ratio_impl(BattleObjectModuleAccessor* a) { return LM(a)->get_parent_customize_attack_ratio(); }
bool LinkModule__is_link_node_attack_impl(BattleObjectModuleAccessor* a) { return LM(a)->is_link_node_attack(); }
void* LinkModule__get_parent_reaction_mul_4th_impl(BattleObjectModuleAccessor* a) { return LM(a)->get_parent_reaction_mul_4th(); }
bool LinkModule__is_parent_power_up_reaction_impl(BattleObjectModuleAccessor* a) { return LM(a)->is_parent_power_up_reaction(); }
// -- Hit/attacker info --
void LinkModule__set_parent_hit_stop_frame_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,bool p3) { LM(a)->set_parent_hit_stop_frame(p1,p2,p3); }
void LinkModule__set_parent_attacker_info_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { LM(a)->set_parent_attacker_info(p1,p2); }
void LinkModule__set_node_attacker_info_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { LM(a)->set_node_attacker_info(p1,p2); }
void LinkModule__set_parent_log_damage_player_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3,u64 p4) { LM(a)->set_parent_log_damage_player(p1,p2,p3,p4); }
void LinkModule__set_node_log_damage_player_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3,u64 p4) { LM(a)->set_node_log_damage_player(p1,p2,p3,p4); }
// -- Node properties --
void LinkModule__set_node_depth_offset_impl(BattleObjectModuleAccessor* a,u64 p1) { LM(a)->set_node_depth_offset(p1); }
void* LinkModule__get_parent_have_item_visibility_impl(BattleObjectModuleAccessor* a,u64 p1) { return LM(a)->get_parent_have_item_visibility(p1); }
void* LinkModule__get_parent_attach_item_visibility_impl(BattleObjectModuleAccessor* a,u64 p1) { return LM(a)->get_parent_attach_item_visibility(p1); }
void* LinkModule__get_parent_main_color_impl(BattleObjectModuleAccessor* a) { void* ret = LM(a)->get_parent_main_color(); asm(""); return ret; }
bool LinkModule__is_parent_enable_sub_color_impl(BattleObjectModuleAccessor* a,u64 p1) { return LM(a)->is_parent_enable_sub_color(p1); }
void* LinkModule__get_parent_sub_color_impl(BattleObjectModuleAccessor* a) { void* ret = LM(a)->get_parent_sub_color(); asm(""); return ret; }
u32 LinkModule__get_parent_battle_object_kind_impl(BattleObjectModuleAccessor* a,u64 p1) { return LM(a)->get_parent_battle_object_kind(p1); }
u32 LinkModule__get_parent_object_id_motion_transactor_link_impl(BattleObjectModuleAccessor* a) { return LM(a)->get_parent_object_id_motion_transactor_link(); }
// -- Model constraint --
void LinkModule__set_model_constraint_pos_ort_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3,u64 p4,bool p5) { LM(a)->set_model_constraint_pos_ort(p1,p2,p3,p4,p5); }
void LinkModule__set_model_constraint_attribute_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { LM(a)->set_model_constraint_attribute(p1,p2); }
void LinkModule__set_model_constraint_flag_impl(BattleObjectModuleAccessor* a,u64 p1) { LM(a)->set_model_constraint_flag(p1); }
void* LinkModule__off_model_constraint_flag_impl(BattleObjectModuleAccessor* a,u64 p1) { return LM(a)->off_model_constraint_flag(p1); }
void LinkModule__set_model_constraint_joint_impl(BattleObjectModuleAccessor* a,u64 p1) { LM(a)->set_model_constraint_joint(p1); }
void LinkModule__set_model_constraint_joint_immediate_impl(BattleObjectModuleAccessor* a,u64 p1) { LM(a)->set_model_constraint_joint_immediate(p1); }
void LinkModule__set_model_constraint_target_joint_impl(BattleObjectModuleAccessor* a,u64 p1) { LM(a)->set_model_constraint_target_joint(p1); }
void* LinkModule__remove_model_constraint_impl(BattleObjectModuleAccessor* a,bool p1) { return LM(a)->remove_model_constraint(p1); }
bool LinkModule__is_model_constraint_impl(BattleObjectModuleAccessor* a) { return LM(a)->is_model_constraint(); }
bool LinkModule__is_model_constraint_mutual_impl(BattleObjectModuleAccessor* a) { return LM(a)->is_model_constraint_mutual(); }
void* LinkModule__get_model_constraint_target_node_position_impl(BattleObjectModuleAccessor* a) { return LM(a)->get_model_constraint_target_node_position(); }
bool LinkModule__is_change_model_constraint_matrix_impl(BattleObjectModuleAccessor* a) { return LM(a)->is_change_model_constraint_matrix(); }
// -- Attribute --
void LinkModule__set_attribute_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,bool p3) { LM(a)->set_attribute(p1,p2,p3); }
// -- Parent state queries --
bool LinkModule__is_link_parent_slow_impl(BattleObjectModuleAccessor* a,u64 p1) { return LM(a)->is_link_parent_slow(p1); }
bool LinkModule__is_parent_flip_impl(BattleObjectModuleAccessor* a,u64 p1) { return LM(a)->is_parent_flip(p1); }
bool LinkModule__is_parent_hit_stop_impl(BattleObjectModuleAccessor* a,u64 p1) { return LM(a)->is_parent_hit_stop(p1); }
void* LinkModule__get_parent_stick_x_impl(BattleObjectModuleAccessor* a,u64 p1) { return LM(a)->get_parent_stick_x(p1); }
// -- Node scale/speed --
void* LinkModule__get_node_sum_speed_impl(BattleObjectModuleAccessor* a,u64 p1) { return LM(a)->get_node_sum_speed(p1); }
void* LinkModule__get_node_scale_impl(BattleObjectModuleAccessor* a,u64 p1) { return LM(a)->get_node_scale(p1); }
// -- Constraint offsets --
void LinkModule__set_constraint_rot_offset_x_impl(BattleObjectModuleAccessor* a) { LM(a)->set_constraint_rot_offset_x(); }
void LinkModule__set_constraint_rot_offset_y_impl(BattleObjectModuleAccessor* a) { LM(a)->set_constraint_rot_offset_y(); }
void LinkModule__set_constraint_rot_offset_z_impl(BattleObjectModuleAccessor* a) { LM(a)->set_constraint_rot_offset_z(); }
void LinkModule__set_constraint_rot_offset_impl(BattleObjectModuleAccessor* a,u64 p1) { LM(a)->set_constraint_rot_offset(p1); }
void LinkModule__set_constraint_scale_offset_impl(BattleObjectModuleAccessor* a,u64 p1) { LM(a)->set_constraint_scale_offset(p1); }
void LinkModule__set_constraint_translate_offset_impl(BattleObjectModuleAccessor* a,u64 p1) { LM(a)->set_constraint_translate_offset(p1); }
// -- Misc --
void LinkModule__set_unreference_parent_scale_impl(BattleObjectModuleAccessor* a,bool p1) { LM(a)->set_unreference_parent_scale(p1); }
void* LinkModule__model_constraint_node_top_z_impl(BattleObjectModuleAccessor* a) { return LM(a)->model_constraint_node_top_z(); }
bool LinkModule__is_parent_spycloak_impl(BattleObjectModuleAccessor* a,u64 p1) { return LM(a)->is_parent_spycloak(p1); }
void* LinkModule__get_parent_model_visible_impl(BattleObjectModuleAccessor* a,u64 p1) { return LM(a)->get_parent_model_visible(p1); }
} // namespace app::lua_bind
