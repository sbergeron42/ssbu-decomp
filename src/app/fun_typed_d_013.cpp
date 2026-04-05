// fun_typed_d_013.cpp — LinkModule v0x* lua_bind dispatchers
// These are .dynsym-exported functions named by vtable offset (e.g. LinkModule__v0x58).
// They duplicate the named dispatchers but with different .dynsym symbols.
// Addresses 0x7102048030–0x7102048800

#include "app/BattleObjectModuleAccessor.h"
#include "app/modules/LinkModule.h"

using app::BattleObjectModuleAccessor;
using app::LinkModule;

#define LM(a) static_cast<LinkModule*>((a)->link_module)

namespace app::lua_bind {

// 0x7102048030 (16B) vtable 0x58 = unlink_node
void* LinkModule__v0x58(BattleObjectModuleAccessor* a, u64 p1) { return LM(a)->unlink_node(p1); }

// 0x7102048050 (16B) vtable 0x68 = unlink
void* LinkModule__v0x68(BattleObjectModuleAccessor* a, u64 p1) { return LM(a)->unlink(p1); }

// 0x7102048060 (16B) vtable 0x70 = is_link
bool LinkModule__v0x70(BattleObjectModuleAccessor* a, u64 p1) { return LM(a)->is_link(p1); }

// 0x7102048070 (16B) vtable 0x78 = is_linked
bool LinkModule__v0x78(BattleObjectModuleAccessor* a, u64 p1) { return LM(a)->is_linked(p1); }

// 0x7102048080 (20B) vtable 0x80 = get_parent_id
u32 LinkModule__v0x80(BattleObjectModuleAccessor* a, u64 p1, bool p2) { return LM(a)->get_parent_id(p1, p2); }

// 0x71020480a0 (16B) vtable 0x88 = search_parent
void* LinkModule__v0x88(BattleObjectModuleAccessor* a, u64 p1) { return LM(a)->search_parent(p1); }

// 0x71020480b0 (16B) vtable 0x90 = search_parent_attr
void* LinkModule__v0x90(BattleObjectModuleAccessor* a, u64 p1) { return LM(a)->search_parent_attr(p1); }

// 0x71020480c0 (16B) vtable 0x98 = search_node
void* LinkModule__v0x98(BattleObjectModuleAccessor* a, u64 p1) { return LM(a)->search_node(p1); }

// 0x7102048140 (16B) vtable 0xd8 = is_node_damage_reaction
bool LinkModule__v0xd8(BattleObjectModuleAccessor* a, u64 p1) { return LM(a)->is_node_damage_reaction(p1); }

// 0x7102048150 (16B) vtable 0xe0 = is_node_damage_capture_cut
bool LinkModule__v0xe0(BattleObjectModuleAccessor* a, u64 p1) { return LM(a)->is_node_damage_capture_cut(p1); }

// 0x71020481d0 (16B) vtable 0x148 = get_parent_scale
void* LinkModule__v0x148(BattleObjectModuleAccessor* a, u64 p1) { return LM(a)->get_parent_scale(p1); }

// 0x71020481e0 (20B) vtable 0x160 = get_parent_model_joint_global_position
void* LinkModule__v0x160(BattleObjectModuleAccessor* a, u64 p1, u64 p2, bool p3) { return LM(a)->get_parent_model_joint_global_position(p1, p2, p3); }

// 0x7102048200 (20B) vtable 0x170 = get_parent_model_joint_global_rotation
void* LinkModule__v0x170(BattleObjectModuleAccessor* a, u64 p1, u64 p2, bool p3) { return LM(a)->get_parent_model_joint_global_rotation(p1, p2, p3); }

// 0x7102048220 (16B) vtable 0x178 = get_parent_motion_frame
void* LinkModule__v0x178(BattleObjectModuleAccessor* a, u64 p1) { return LM(a)->get_parent_motion_frame(p1); }

// 0x7102048230 (16B) vtable 0x180 = get_parent_motion_whole_rate
void* LinkModule__v0x180(BattleObjectModuleAccessor* a, u64 p1) { return LM(a)->get_parent_motion_whole_rate(p1); }

// 0x7102048240 (16B) vtable 0x188 = get_parent_motion_rate
void* LinkModule__v0x188(BattleObjectModuleAccessor* a, u64 p1) { return LM(a)->get_parent_motion_rate(p1); }

// 0x7102048250 (16B) vtable 0x190 = get_parent_motion_kind
u32 LinkModule__v0x190(BattleObjectModuleAccessor* a, u64 p1) { return LM(a)->get_parent_motion_kind(p1); }

// 0x7102048260 (16B) vtable 0x198 = get_parent_situation_kind
u32 LinkModule__v0x198(BattleObjectModuleAccessor* a, u64 p1) { return LM(a)->get_parent_situation_kind(p1); }

// 0x7102048270 (16B) vtable 0x1a0 = get_parent_status_kind
u32 LinkModule__v0x1a0(BattleObjectModuleAccessor* a, u64 p1) { return LM(a)->get_parent_status_kind(p1); }

// 0x7102048280 (16B) vtable 0x1a8 = get_parent_lr
void* LinkModule__v0x1a8(BattleObjectModuleAccessor* a, u64 p1) { return LM(a)->get_parent_lr(p1); }

// 0x71020482a0 (16B) vtable 0x1b8 = get_parent_object_id
u32 LinkModule__v0x1b8(BattleObjectModuleAccessor* a, u64 p1) { return LM(a)->get_parent_object_id(p1); }

// 0x71020482b0 (16B) vtable 0x1c0 = is_capture_damage_parent_object_id
bool LinkModule__v0x1c0(BattleObjectModuleAccessor* a, u64 p1) { return LM(a)->is_capture_damage_parent_object_id(p1); }

// 0x7102048300 (16B) vtable 0x1d8 = get_parent_rot
void* LinkModule__v0x1d8(BattleObjectModuleAccessor* a, u64 p1) { return LM(a)->get_parent_rot(p1); }

// 0x7102048310 (16B) vtable 0x1e0 = get_parent_damage
void* LinkModule__v0x1e0(BattleObjectModuleAccessor* a, u64 p1) { return LM(a)->get_parent_damage(p1); }

// 0x7102048320 (16B) vtable 0x1e8 = get_parent_damage_reaction
void* LinkModule__v0x1e8(BattleObjectModuleAccessor* a, u64 p1) { return LM(a)->get_parent_damage_reaction(p1); }

// 0x7102048330 (16B) vtable 0x1f0 = get_parent_damage_power_max
void* LinkModule__v0x1f0(BattleObjectModuleAccessor* a, u64 p1) { return LM(a)->get_parent_damage_power_max(p1); }

// 0x7102048340 (16B) vtable 0x1f8 = get_parent_top_angle
void* LinkModule__v0x1f8(BattleObjectModuleAccessor* a, u64 p1) { return LM(a)->get_parent_top_angle(p1); }

// 0x7102048360 (20B) vtable 0x208 = set_node_link_scale
void LinkModule__v0x208(BattleObjectModuleAccessor* a, bool p1) { LM(a)->set_node_link_scale(p1); }

// 0x7102048380 (16B) vtable 0x210 = is_parent_damage_reaction
bool LinkModule__v0x210(BattleObjectModuleAccessor* a, u64 p1) { return LM(a)->is_parent_damage_reaction(p1); }

// 0x7102048390 (16B) vtable 0x218 = is_parent_damage_catch_cut
bool LinkModule__v0x218(BattleObjectModuleAccessor* a, u64 p1) { return LM(a)->is_parent_damage_catch_cut(p1); }

// 0x71020483a0 (16B) vtable 0x220 = get_parent_total_hit_status
void* LinkModule__v0x220(BattleObjectModuleAccessor* a, u64 p1) { return LM(a)->get_parent_total_hit_status(p1); }

// 0x71020483c0 (16B) vtable 0x230 = get_parent_shape_center_pos
void* LinkModule__v0x230(BattleObjectModuleAccessor* a, u64 p1) { return LM(a)->get_parent_shape_center_pos(p1); }

// 0x71020483e0 (16B) vtable 0x270 = is_parent_effect_sync_scale
bool LinkModule__v0x270(BattleObjectModuleAccessor* a, u64 p1) { return LM(a)->is_parent_effect_sync_scale(p1); }

// 0x7102048470 (20B) vtable 0x2e8 = set_parent_hit_stop_frame
void LinkModule__v0x2e8(BattleObjectModuleAccessor* a, u64 p1, u64 p2, bool p3) { LM(a)->set_parent_hit_stop_frame(p1, p2, p3); }

// 0x71020484d0 (16B) vtable 0x310 = set_node_depth_offset
void LinkModule__v0x310(BattleObjectModuleAccessor* a, u64 p1) { LM(a)->set_node_depth_offset(p1); }

// 0x71020484e0 (16B) vtable 0x318 = get_parent_have_item_visibility
void* LinkModule__v0x318(BattleObjectModuleAccessor* a, u64 p1) { return LM(a)->get_parent_have_item_visibility(p1); }

// 0x71020484f0 (16B) vtable 0x320 = get_parent_attach_item_visibility
void* LinkModule__v0x320(BattleObjectModuleAccessor* a, u64 p1) { return LM(a)->get_parent_attach_item_visibility(p1); }

// 0x7102048520 (16B) vtable 0x338 = is_parent_enable_sub_color
bool LinkModule__v0x338(BattleObjectModuleAccessor* a, u64 p1) { return LM(a)->is_parent_enable_sub_color(p1); }

// 0x7102048550 (16B) vtable 0x348 = get_parent_battle_object_kind
u32 LinkModule__v0x348(BattleObjectModuleAccessor* a, u64 p1) { return LM(a)->get_parent_battle_object_kind(p1); }

// 0x7102048570 (20B) vtable 0x358 = set_model_constraint_pos_ort
void LinkModule__v0x358(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3, u64 p4, bool p5) { LM(a)->set_model_constraint_pos_ort(p1, p2, p3, p4, p5); }

// 0x7102048590 (20B) vtable 0x360 = set_model_constraint_attribute
void LinkModule__v0x360(BattleObjectModuleAccessor* a, u64 p1, bool p2) { LM(a)->set_model_constraint_attribute(p1, p2); }

// 0x71020485c0 (16B) vtable 0x370 = set_model_constraint_flag
void LinkModule__v0x370(BattleObjectModuleAccessor* a, u64 p1) { LM(a)->set_model_constraint_flag(p1); }

// 0x71020485d0 (16B) vtable 0x378 = off_model_constraint_flag
void* LinkModule__v0x378(BattleObjectModuleAccessor* a, u64 p1) { return LM(a)->off_model_constraint_flag(p1); }

// 0x7102048600 (16B) vtable 0x390 = set_model_constraint_joint
void LinkModule__v0x390(BattleObjectModuleAccessor* a, u64 p1) { LM(a)->set_model_constraint_joint(p1); }

// 0x7102048610 (16B) vtable 0x398 = set_model_constraint_joint_immediate
void LinkModule__v0x398(BattleObjectModuleAccessor* a, u64 p1) { LM(a)->set_model_constraint_joint_immediate(p1); }

// 0x7102048620 (16B) vtable 0x3a0 = set_model_constraint_target_joint
void LinkModule__v0x3a0(BattleObjectModuleAccessor* a, u64 p1) { LM(a)->set_model_constraint_target_joint(p1); }

// 0x7102048650 (20B) vtable 0x3c0 = remove_model_constraint
void* LinkModule__v0x3c0(BattleObjectModuleAccessor* a, bool p1) { return LM(a)->remove_model_constraint(p1); }

// 0x7102048710 (20B) vtable 0x428 = set_attribute
void LinkModule__v0x428(BattleObjectModuleAccessor* a, u64 p1, u64 p2, bool p3) { LM(a)->set_attribute(p1, p2, p3); }

// 0x7102048750 (16B) vtable 0x460 = is_link_parent_slow
bool LinkModule__v0x460(BattleObjectModuleAccessor* a, u64 p1) { return LM(a)->is_link_parent_slow(p1); }

// 0x7102048760 (16B) vtable 0x480 = is_parent_flip
bool LinkModule__v0x480(BattleObjectModuleAccessor* a, u64 p1) { return LM(a)->is_parent_flip(p1); }

// 0x7102048770 (16B) vtable 0x488 = is_parent_hit_stop
bool LinkModule__v0x488(BattleObjectModuleAccessor* a, u64 p1) { return LM(a)->is_parent_hit_stop(p1); }

// 0x7102048780 (16B) vtable 0x4a0 = get_parent_stick_x
void* LinkModule__v0x4a0(BattleObjectModuleAccessor* a, u64 p1) { return LM(a)->get_parent_stick_x(p1); }

// 0x71020487a0 (16B) vtable 0x4c0 = get_node_sum_speed
void* LinkModule__v0x4c0(BattleObjectModuleAccessor* a, u64 p1) { return LM(a)->get_node_sum_speed(p1); }

// 0x71020487b0 (16B) vtable 0x4c8 = get_node_scale
void* LinkModule__v0x4c8(BattleObjectModuleAccessor* a, u64 p1) { return LM(a)->get_node_scale(p1); }

// 0x71020487f0 (16B) vtable 0x4e8 = set_constraint_rot_offset
void LinkModule__v0x4e8(BattleObjectModuleAccessor* a, u64 p1) { LM(a)->set_constraint_rot_offset(p1); }

// 0x7102048800 (16B) vtable 0x4f0 = set_constraint_scale_offset
void LinkModule__v0x4f0(BattleObjectModuleAccessor* a, u64 p1) { LM(a)->set_constraint_scale_offset(p1); }

} // namespace app::lua_bind
