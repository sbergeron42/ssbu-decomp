#pragma once
#include "types.h"

namespace app {

// LinkModule — accessed at BattleObjectModuleAccessor+0xD0
// Manages parent-child linking between battle objects (items, projectiles, fighters).
// Vtable layout recovered from lua_bind dispatcher analysis (offsets 0x48–0x520).
// All method names derived from .dynsym lua_bind::LinkModule__*_impl dispatcher analysis.
struct LinkModule {
    void** _vt;

    // -- Link management (0x48–0xb8) -- [confirmed: lua_bind API names]
    void* link(u64 p1, u64 p2) { return ((void*(*)(LinkModule*,u64,u64))_vt[0x48/8])(this,p1,p2); }
    void* unlink_all() { return ((void*(*)(LinkModule*))_vt[0x50/8])(this); }
    void* unlink_node(u64 p1) { return ((void*(*)(LinkModule*,u64))_vt[0x58/8])(this,p1); }
    void* unlink_node_all() { return ((void*(*)(LinkModule*))_vt[0x60/8])(this); }
    void* unlink(u64 p1) { return ((void*(*)(LinkModule*,u64))_vt[0x68/8])(this,p1); }
    bool is_link(u64 p1) { return ((bool(*)(LinkModule*,u64))_vt[0x70/8])(this,p1); }
    bool is_linked(u64 p1) { return ((bool(*)(LinkModule*,u64))_vt[0x78/8])(this,p1); }
    u32 get_parent_id(u64 p1, bool p2) { return ((u32(*)(LinkModule*,u64,bool))_vt[0x80/8])(this,p1,p2); }
    void* search_parent(u64 p1) { return ((void*(*)(LinkModule*,u64))_vt[0x88/8])(this,p1); }
    void* search_parent_attr(u64 p1) { return ((void*(*)(LinkModule*,u64))_vt[0x90/8])(this,p1); }
    void* search_node(u64 p1) { return ((void*(*)(LinkModule*,u64))_vt[0x98/8])(this,p1); }
    void* send_event_parents(u64 p1, u64 p2) { return ((void*(*)(LinkModule*,u64,u64))_vt[0xa0/8])(this,p1,p2); }
    void* send_event_parents_struct(u64 p1, u64 p2) { return ((void*(*)(LinkModule*,u64,u64))_vt[0xa8/8])(this,p1,p2); }
    void* send_event_nodes_struct(u64 p1, u64 p2, u64 p3) { return ((void*(*)(LinkModule*,u64,u64,u64))_vt[0xb0/8])(this,p1,p2,p3); }
    void* send_event_nodes(u64 p1, u64 p2, u64 p3) { return ((void*(*)(LinkModule*,u64,u64,u64))_vt[0xb8/8])(this,p1,p2,p3); }

    // -- Event/throw dispatch (0xc8) --
    void* send_event_nodes_throw(u64 p1, u64 p2, bool p3, u64 p4, u64 p5, u64 p6) { return ((void*(*)(LinkModule*,u64,u64,bool,u64,u64,u64))_vt[0xc8/8])(this,p1,p2,p3,p4,p5,p6); }

    // -- Node queries (0xd0–0xf0) --
    void* get_node_object_id(u64 p1) { return ((void*(*)(LinkModule*,u64))_vt[0xd0/8])(this,p1); }
    bool is_node_damage_reaction(u64 p1) { return ((bool(*)(LinkModule*,u64))_vt[0xd8/8])(this,p1); }
    bool is_node_damage_capture_cut(u64 p1) { return ((bool(*)(LinkModule*,u64))_vt[0xe0/8])(this,p1); }
    void* chk_link_stop() { return ((void*(*)(LinkModule*))_vt[0xe8/8])(this); }
    bool is_valid_link_stop() { return ((bool(*)(LinkModule*))_vt[0xf0/8])(this); }

    // -- Visibility/scale/speed (0x118–0x148) --
    void* chk_link_visibility() { return ((void*(*)(LinkModule*))_vt[0x118/8])(this); }
    void* get_link_scale() { return ((void*(*)(LinkModule*))_vt[0x128/8])(this); }
    bool is_link_pos() { return ((bool(*)(LinkModule*))_vt[0x130/8])(this); }
    void update_link_pos() { ((void(*)(LinkModule*))_vt[0x138/8])(this); }
    void* get_link_speed(u64 p1) { return ((void*(*)(LinkModule*,u64))_vt[0x140/8])(this,p1); }
    void* get_parent_scale(u64 p1) { return ((void*(*)(LinkModule*,u64))_vt[0x148/8])(this,p1); }

    // -- Parent joint/model queries (0x160–0x1b0) --
    void* get_parent_model_joint_global_position(u64 p1, u64 p2, bool p3) { return ((void*(*)(LinkModule*,u64,u64,bool))_vt[0x160/8])(this,p1,p2,p3); }
    void* get_parent_model_joint_global_rotation(u64 p1, u64 p2, bool p3) { return ((void*(*)(LinkModule*,u64,u64,bool))_vt[0x170/8])(this,p1,p2,p3); }
    void* get_parent_motion_frame(u64 p1) { return ((void*(*)(LinkModule*,u64))_vt[0x178/8])(this,p1); }
    void* get_parent_motion_whole_rate(u64 p1) { return ((void*(*)(LinkModule*,u64))_vt[0x180/8])(this,p1); }
    void* get_parent_motion_rate(u64 p1) { return ((void*(*)(LinkModule*,u64))_vt[0x188/8])(this,p1); }
    u32 get_parent_motion_kind(u64 p1) { return ((u32(*)(LinkModule*,u64))_vt[0x190/8])(this,p1); }
    u32 get_parent_situation_kind(u64 p1) { return ((u32(*)(LinkModule*,u64))_vt[0x198/8])(this,p1); }
    u32 get_parent_status_kind(u64 p1) { return ((u32(*)(LinkModule*,u64))_vt[0x1a0/8])(this,p1); }
    void* get_parent_lr(u64 p1) { return ((void*(*)(LinkModule*,u64))_vt[0x1a8/8])(this,p1); }
    void* get_parent_sum_speed(u64 p1, u64 p2) { return ((void*(*)(LinkModule*,u64,u64))_vt[0x1b0/8])(this,p1,p2); }

    // -- Parent object/position queries (0x1b8–0x1f8) --
    u32 get_parent_object_id(u64 p1) { return ((u32(*)(LinkModule*,u64))_vt[0x1b8/8])(this,p1); }
    bool is_capture_damage_parent_object_id(u64 p1) { return ((bool(*)(LinkModule*,u64))_vt[0x1c0/8])(this,p1); }
    void* get_parent_pos() { return ((void*(*)(LinkModule*))_vt[0x1c8/8])(this); }
    void* get_parent_prev_pos() { return ((void*(*)(LinkModule*))_vt[0x1d0/8])(this); }
    void* get_parent_rot(u64 p1) { return ((void*(*)(LinkModule*,u64))_vt[0x1d8/8])(this,p1); }
    void* get_parent_damage(u64 p1) { return ((void*(*)(LinkModule*,u64))_vt[0x1e0/8])(this,p1); }
    void* get_parent_damage_reaction(u64 p1) { return ((void*(*)(LinkModule*,u64))_vt[0x1e8/8])(this,p1); }
    void* get_parent_damage_power_max(u64 p1) { return ((void*(*)(LinkModule*,u64))_vt[0x1f0/8])(this,p1); }
    void* get_parent_top_angle(u64 p1) { return ((void*(*)(LinkModule*,u64))_vt[0x1f8/8])(this,p1); }

    // -- Node/parent state (0x200–0x238) --
    void set_node_scale_power_mul() { ((void(*)(LinkModule*))_vt[0x200/8])(this); }
    void set_node_link_scale(bool p1) { ((void(*)(LinkModule*,bool))_vt[0x208/8])(this,p1); }
    bool is_parent_damage_reaction(u64 p1) { return ((bool(*)(LinkModule*,u64))_vt[0x210/8])(this,p1); }
    bool is_parent_damage_catch_cut(u64 p1) { return ((bool(*)(LinkModule*,u64))_vt[0x218/8])(this,p1); }
    void* get_parent_total_hit_status(u64 p1) { return ((void*(*)(LinkModule*,u64))_vt[0x220/8])(this,p1); }
    bool is_valid_parent_shape(u64 p1) { return ((bool(*)(LinkModule*,u64))_vt[0x228/8])(this,p1); }
    void* get_parent_shape_center_pos(u64 p1) { return ((void*(*)(LinkModule*,u64))_vt[0x230/8])(this,p1); }
    void* get_parent_shape_center_pos_object_id(u64 p1, u64 p2) { return ((void*(*)(LinkModule*,u64,u64))_vt[0x238/8])(this,p1,p2); }

    // -- Power up / effect (0x270–0x2a0) --
    bool is_parent_effect_sync_scale(u64 p1) { return ((bool(*)(LinkModule*,u64))_vt[0x270/8])(this,p1); }
    bool is_link_power_up() { return ((bool(*)(LinkModule*))_vt[0x278/8])(this); }
    void* get_parent_power_up_attack() { return ((void*(*)(LinkModule*))_vt[0x280/8])(this); }
    void* get_parent_power_up_defense() { return ((void*(*)(LinkModule*))_vt[0x288/8])(this); }
    void* get_parent_power_up_attr() { return ((void*(*)(LinkModule*))_vt[0x290/8])(this); }
    f32 get_parent_customize_attack_ratio() { return ((f32(*)(LinkModule*))_vt[0x298/8])(this); }
    bool is_link_node_attack() { return ((bool(*)(LinkModule*))_vt[0x2a0/8])(this); }

    // -- Reaction / damage info (0x2d8–0x308) --
    void* get_parent_reaction_mul_4th() { return ((void*(*)(LinkModule*))_vt[0x2d8/8])(this); }
    bool is_parent_power_up_reaction() { return ((bool(*)(LinkModule*))_vt[0x2e0/8])(this); }
    void set_parent_hit_stop_frame(u64 p1, u64 p2, bool p3) { ((void(*)(LinkModule*,u64,u64,bool))_vt[0x2e8/8])(this,p1,p2,p3); }
    void set_parent_attacker_info(u64 p1, u64 p2) { ((void(*)(LinkModule*,u64,u64))_vt[0x2f0/8])(this,p1,p2); }
    void set_node_attacker_info(u64 p1, u64 p2) { ((void(*)(LinkModule*,u64,u64))_vt[0x2f8/8])(this,p1,p2); }
    void set_parent_log_damage_player(u64 p1, u64 p2, u64 p3, u64 p4) { ((void(*)(LinkModule*,u64,u64,u64,u64))_vt[0x300/8])(this,p1,p2,p3,p4); }
    void set_node_log_damage_player(u64 p1, u64 p2, u64 p3, u64 p4) { ((void(*)(LinkModule*,u64,u64,u64,u64))_vt[0x308/8])(this,p1,p2,p3,p4); }

    // -- Node properties (0x310–0x350) --
    void set_node_depth_offset(u64 p1) { ((void(*)(LinkModule*,u64))_vt[0x310/8])(this,p1); }
    void* get_parent_have_item_visibility(u64 p1) { return ((void*(*)(LinkModule*,u64))_vt[0x318/8])(this,p1); }
    void* get_parent_attach_item_visibility(u64 p1) { return ((void*(*)(LinkModule*,u64))_vt[0x320/8])(this,p1); }
    void* get_parent_main_color() { return ((void*(*)(LinkModule*))_vt[0x330/8])(this); }
    bool is_parent_enable_sub_color(u64 p1) { return ((bool(*)(LinkModule*,u64))_vt[0x338/8])(this,p1); }
    void* get_parent_sub_color() { return ((void*(*)(LinkModule*))_vt[0x340/8])(this); }
    u32 get_parent_battle_object_kind(u64 p1) { return ((u32(*)(LinkModule*,u64))_vt[0x348/8])(this,p1); }
    u32 get_parent_object_id_motion_transactor_link() { return ((u32(*)(LinkModule*))_vt[0x350/8])(this); }

    // -- Model constraint system (0x358–0x420) --
    void set_model_constraint_pos_ort(u64 p1, u64 p2, u64 p3, u64 p4, bool p5) { ((void(*)(LinkModule*,u64,u64,u64,u64,bool))_vt[0x358/8])(this,p1,p2,p3,p4,p5); }
    void set_model_constraint_attribute(u64 p1, bool p2) { ((void(*)(LinkModule*,u64,bool))_vt[0x360/8])(this,p1,p2); }
    u32 get_model_constraint_flag() { return ((u32(*)(LinkModule*))_vt[0x368/8])(this); }
    void set_model_constraint_flag(u64 p1) { ((void(*)(LinkModule*,u64))_vt[0x370/8])(this,p1); }
    void* off_model_constraint_flag(u64 p1) { return ((void*(*)(LinkModule*,u64))_vt[0x378/8])(this,p1); }
    void* get_model_constraint_joint() { return ((void*(*)(LinkModule*))_vt[0x380/8])(this); }
    void* get_model_constraint_target_joint() { return ((void*(*)(LinkModule*))_vt[0x388/8])(this); }
    void set_model_constraint_joint(u64 p1) { ((void(*)(LinkModule*,u64))_vt[0x390/8])(this,p1); }
    void set_model_constraint_joint_immediate(u64 p1) { ((void(*)(LinkModule*,u64))_vt[0x398/8])(this,p1); }
    void set_model_constraint_target_joint(u64 p1) { ((void(*)(LinkModule*,u64))_vt[0x3a0/8])(this,p1); }
    u32 get_model_constraint_no() { return ((u32(*)(LinkModule*))_vt[0x3a8/8])(this); }
    void* adjust_model_constraint_posture(u64 p1, u64 p2) { return ((void*(*)(LinkModule*,u64,u64))_vt[0x3b0/8])(this,p1,p2); }
    void* remove_model_constraint(bool p1) { return ((void*(*)(LinkModule*,bool))_vt[0x3c0/8])(this,p1); }
    bool is_model_constraint() { return ((bool(*)(LinkModule*))_vt[0x3c8/8])(this); }
    bool is_model_constraint_mutual() { return ((bool(*)(LinkModule*))_vt[0x3d0/8])(this); }
    void* get_model_constraint_target_node_position() { return ((void*(*)(LinkModule*))_vt[0x3e0/8])(this); }
    void* get_model_constraint_joint_global_position(u64 p1) { return ((void*(*)(LinkModule*,u64))_vt[0x3e8/8])(this,p1); }
    void* get_model_constraint_joint_global_position_recursive(u64 p1) { return ((void*(*)(LinkModule*,u64))_vt[0x3f0/8])(this,p1); }
    void* get_model_constraint_target_joint_rotation() { return ((void*(*)(LinkModule*))_vt[0x3f8/8])(this); }
    void* get_node_rotation(u64 p1, u64 p2, u64 p3) { return ((void*(*)(LinkModule*,u64,u64,u64))_vt[0x400/8])(this,p1,p2,p3); }
    void* get_constraint_model_scale() { return ((void*(*)(LinkModule*))_vt[0x408/8])(this); }
    void* get_constraint_translate_offset() { return ((void*(*)(LinkModule*))_vt[0x410/8])(this); }
    bool is_change_model_constraint_matrix() { return ((bool(*)(LinkModule*))_vt[0x420/8])(this); }

    // -- Attribute system (0x428–0x438) --
    void set_attribute(u64 p1, u64 p2, bool p3) { ((void(*)(LinkModule*,u64,u64,bool))_vt[0x428/8])(this,p1,p2,p3); }
    bool chk_attribute(u64 p1, u64 p2) { return ((bool(*)(LinkModule*,u64,u64))_vt[0x430/8])(this,p1,p2); }
    bool chk_linked_attribute(u64 p1) { return ((bool(*)(LinkModule*,u64))_vt[0x438/8])(this,p1); }

    // -- Parent state queries (0x460–0x4a0) --
    bool is_link_parent_slow(u64 p1) { return ((bool(*)(LinkModule*,u64))_vt[0x460/8])(this,p1); }
    bool is_parent_flip(u64 p1) { return ((bool(*)(LinkModule*,u64))_vt[0x480/8])(this,p1); }
    bool is_parent_hit_stop(u64 p1) { return ((bool(*)(LinkModule*,u64))_vt[0x488/8])(this,p1); }
    void* get_parent_stick_x(u64 p1) { return ((void*(*)(LinkModule*,u64))_vt[0x4a0/8])(this,p1); }

    // -- Node capture/scale (0x4b8–0x4c8) --
    void* get_node_catprue_pos(u64 p1, u64 p2) { return ((void*(*)(LinkModule*,u64,u64))_vt[0x4b8/8])(this,p1,p2); }
    void* get_node_sum_speed(u64 p1) { return ((void*(*)(LinkModule*,u64))_vt[0x4c0/8])(this,p1); }
    void* get_node_scale(u64 p1) { return ((void*(*)(LinkModule*,u64))_vt[0x4c8/8])(this,p1); }

    // -- Constraint offsets (0x4d0–0x4f8) --
    void set_constraint_rot_offset_x() { ((void(*)(LinkModule*))_vt[0x4d0/8])(this); }
    void set_constraint_rot_offset_y() { ((void(*)(LinkModule*))_vt[0x4d8/8])(this); }
    void set_constraint_rot_offset_z() { ((void(*)(LinkModule*))_vt[0x4e0/8])(this); }
    void set_constraint_rot_offset(u64 p1) { ((void(*)(LinkModule*,u64))_vt[0x4e8/8])(this,p1); }
    void set_constraint_scale_offset(u64 p1) { ((void(*)(LinkModule*,u64))_vt[0x4f0/8])(this,p1); }
    void set_constraint_translate_offset(u64 p1) { ((void(*)(LinkModule*,u64))_vt[0x4f8/8])(this,p1); }

    // -- Misc (0x508–0x520) --
    void set_unreference_parent_scale(bool p1) { ((void(*)(LinkModule*,bool))_vt[0x508/8])(this,p1); }
    void* model_constraint_node_top_z() { return ((void*(*)(LinkModule*))_vt[0x510/8])(this); }
    bool is_parent_spycloak(u64 p1) { return ((bool(*)(LinkModule*,u64))_vt[0x518/8])(this,p1); }
    void* get_parent_model_visible(u64 p1) { return ((void*(*)(LinkModule*,u64))_vt[0x520/8])(this,p1); }
};

} // namespace app
