#pragma once
#include "types.h"

namespace app {

// AttackModule virtual dispatch wrapper
// Vtable entries recovered from lua_bind dispatcher analysis
// All method names derived from .dynsym lua_bind::AttackModule__*_impl functions.
// Module accessed via BattleObjectModuleAccessor +0xA0
struct AttackModule {
    void** _vt;

    // Vtable dispatchers — index = byte_offset / 8

    // -- core [10-20] --
    void clear_all() { ((void(*)(AttackModule*))_vt[10])(this); }
    void clear(u64 p1, bool p2) { ((void(*)(AttackModule*,u64,bool))_vt[11])(this,p1,p2); }
    void sleep_partialy(u64 p1, bool p2) { ((void(*)(AttackModule*,u64,bool))_vt[12])(this,p1,p2); }
    void set_attack(u64 p1, u64 p2, u64 p3) { ((void(*)(AttackModule*,u64,u64,u64))_vt[13])(this,p1,p2,p3); }
    void set_attack_2(u64 p1, u64 p2) { ((void(*)(AttackModule*,u64,u64))_vt[14])(this,p1,p2); }
    void set_absolute(u64 p1, u64 p2, u64 p3) { ((void(*)(AttackModule*,u64,u64,u64))_vt[15])(this,p1,p2,p3); }
    void* hit_absolute(u64 p1, u64 p2, u64 p3, u64 p4, u64 p5) { return ((void*(*)(AttackModule*,u64,u64,u64,u64,u64))_vt[16])(this,p1,p2,p3,p4,p5); }
    void* hit_absolute_joint(u64 p1, u64 p2, u64 p3, u64 p4, u64 p5) { return ((void*(*)(AttackModule*,u64,u64,u64,u64,u64))_vt[17])(this,p1,p2,p3,p4,p5); }
    void set_absolute_lr(u64 p1) { ((void(*)(AttackModule*,u64))_vt[18])(this,p1); }
    void set_whole(u64 p1, bool p2) { ((void(*)(AttackModule*,u64,bool))_vt[19])(this,p1,p2); }
    void sleep(bool p1) { ((void(*)(AttackModule*,bool))_vt[20])(this,p1); }

    // -- queries [24-31] --
    u32 active_part_num() { return ((u32(*)(AttackModule*))_vt[24])(this); }
    bool is_attack(u64 p1, bool p2) { return ((bool(*)(AttackModule*,u64,bool))_vt[25])(this,p1,p2); }
    void set_invalid_invincible(u64 p1, bool p2) { ((void(*)(AttackModule*,u64,bool))_vt[26])(this,p1,p2); }
    bool is_invalid_invincible(u64 p1, bool p2) { return ((bool(*)(AttackModule*,u64,bool))_vt[27])(this,p1,p2); }
    void set_invalid_xlu(u64 p1, bool p2) { ((void(*)(AttackModule*,u64,bool))_vt[28])(this,p1,p2); }
    bool is_invalid_xlu(u64 p1, bool p2) { return ((bool(*)(AttackModule*,u64,bool))_vt[29])(this,p1,p2); }
    bool is_hit_abs() { return ((bool(*)(AttackModule*))_vt[30])(this); }
    void set_power(u64 p1, bool p2) { ((void(*)(AttackModule*,u64,bool))_vt[31])(this,p1,p2); }

    // -- properties [32-43] --
    void add_power(u64 p1, bool p2) { ((void(*)(AttackModule*,u64,bool))_vt[32])(this,p1,p2); }
    void set_vector(u64 p1, u64 p2, bool p3) { ((void(*)(AttackModule*,u64,u64,bool))_vt[33])(this,p1,p2,p3); }
    u32 size(u64 p1) { return ((u32(*)(AttackModule*,u64))_vt[34])(this,p1); }
    void set_size(u64 p1) { ((void(*)(AttackModule*,u64))_vt[35])(this,p1); }
    void set_target_category(u64 p1, u64 p2) { ((void(*)(AttackModule*,u64,u64))_vt[36])(this,p1,p2); }
    void* off_target_kind(u64 p1, u64 p2) { return ((void*(*)(AttackModule*,u64,u64))_vt[37])(this,p1,p2); }
    void set_offset(u64 p1, u64 p2) { ((void(*)(AttackModule*,u64,u64))_vt[38])(this,p1,p2); }
    void set_offset2(u64 p1, u64 p2) { ((void(*)(AttackModule*,u64,u64))_vt[39])(this,p1,p2); }
    void get_offset2(u64 p1, bool p2) { ((void(*)(AttackModule*,u64,bool))_vt[40])(this,p1,p2); }
    void set_node(u64 p1, u64 p2) { ((void(*)(AttackModule*,u64,u64))_vt[41])(this,p1,p2); }
    void set_serial_hit_frame(u64 p1, u64 p2) { ((void(*)(AttackModule*,u64,u64))_vt[42])(this,p1,p2); }
    void get_power(u64 p1, bool p2, bool p3) { ((void(*)(AttackModule*,u64,bool,bool))_vt[43])(this,p1,p2,p3); }

    // -- group/reaction [45-52] --
    u32 group(u64 p1) { return ((u32(*)(AttackModule*,u64))_vt[45])(this,p1); }
    f32 reaction_effect(u64 p1, bool p2) { return ((f32(*)(AttackModule*,u64,bool))_vt[46])(this,p1,p2); }
    void set_reaction_effect(u64 p1, u64 p2, bool p3) { ((void(*)(AttackModule*,u64,u64,bool))_vt[47])(this,p1,p2,p3); }
    f32 reaction_fix(u64 p1, bool p2) { return ((f32(*)(AttackModule*,u64,bool))_vt[48])(this,p1,p2); }
    void set_reaction_fix(u64 p1, u64 p2, bool p3) { ((void(*)(AttackModule*,u64,u64,bool))_vt[49])(this,p1,p2,p3); }
    f32 reaction_add(u64 p1, bool p2) { return ((f32(*)(AttackModule*,u64,bool))_vt[50])(this,p1,p2); }
    void set_reaction_add(u64 p1, u64 p2, bool p3) { ((void(*)(AttackModule*,u64,u64,bool))_vt[51])(this,p1,p2,p3); }
    void* reaction_mul() { return ((void*(*)(AttackModule*))_vt[52])(this); }

    // -- position [53-58] --
    void set_pos_x(u64 p1) { ((void(*)(AttackModule*,u64))_vt[53])(this,p1); }
    f32 pos_x(u64 p1, bool p2) { return ((f32(*)(AttackModule*,u64,bool))_vt[54])(this,p1,p2); }
    void* pos_x_2() { return ((void*(*)(AttackModule*))_vt[55])(this); }
    void* pos_y() { return ((void*(*)(AttackModule*))_vt[56])(this); }
    void* center_pos(u64 p1, bool p2) { return ((void*(*)(AttackModule*,u64,bool))_vt[57])(this,p1,p2); }
    void* speed_x() { return ((void*(*)(AttackModule*))_vt[58])(this); }

    // -- speed/data [59-61] --
    void* speed() { return ((void*(*)(AttackModule*))_vt[59])(this); }
    void set_speed(u64 p1) { ((void(*)(AttackModule*,u64))_vt[60])(this,p1); }
    void* attack_data(u64 p1, bool p2) { return ((void*(*)(AttackModule*,u64,bool))_vt[61])(this,p1,p2); }

    // -- power status [62-79] --
    void set_power_mul_status() { ((void(*)(AttackModule*))_vt[62])(this); }
    f32 power_mul_status() { return ((f32(*)(AttackModule*))_vt[63])(this); }
    void set_power_add_status() { ((void(*)(AttackModule*))_vt[64])(this); }
    f32 power_add_status() { return ((f32(*)(AttackModule*))_vt[65])(this); }
    void set_power_speed_status() { ((void(*)(AttackModule*))_vt[66])(this); }
    f32 power_speed_status() { return ((f32(*)(AttackModule*))_vt[67])(this); }
    void set_power_speed_limit() { ((void(*)(AttackModule*))_vt[68])(this); }
    f32 power_speed_limit() { return ((f32(*)(AttackModule*))_vt[69])(this); }
    void set_power_mul() { ((void(*)(AttackModule*))_vt[70])(this); }
    f32 power_mul() { return ((f32(*)(AttackModule*))_vt[71])(this); }
    void set_power_mul_2nd() { ((void(*)(AttackModule*))_vt[72])(this); }
    f32 power_mul_2nd() { return ((f32(*)(AttackModule*))_vt[73])(this); }
    void set_power_mul_3rd() { ((void(*)(AttackModule*))_vt[74])(this); }
    f32 power_mul_3rd() { return ((f32(*)(AttackModule*))_vt[75])(this); }
    void set_power_mul_4th() { ((void(*)(AttackModule*))_vt[76])(this); }
    f32 power_mul_4th() { return ((f32(*)(AttackModule*))_vt[77])(this); }
    void set_power_mul_5th() { ((void(*)(AttackModule*))_vt[78])(this); }
    f32 power_mul_5th() { return ((f32(*)(AttackModule*))_vt[79])(this); }

    // -- customize [82-83] --
    void set_customize_attack_ratio() { ((void(*)(AttackModule*))_vt[82])(this); }
    f32 customize_attack_ratio() { return ((f32(*)(AttackModule*))_vt[83])(this); }

    // -- reaction mul [84-90] --
    void set_reaction_mul() { ((void(*)(AttackModule*))_vt[84])(this); }
    void set_reaction_mul_2nd() { ((void(*)(AttackModule*))_vt[85])(this); }
    f32 reaction_mul_2nd() { return ((f32(*)(AttackModule*))_vt[86])(this); }
    void set_reaction_mul_3rd() { ((void(*)(AttackModule*))_vt[87])(this); }
    f32 reaction_mul_3rd() { return ((f32(*)(AttackModule*))_vt[88])(this); }
    void set_reaction_mul_4th() { ((void(*)(AttackModule*))_vt[89])(this); }
    f32 reaction_mul_4th() { return ((f32(*)(AttackModule*))_vt[90])(this); }

    // -- damage reaction [101-102] --
    void set_damage_reaction_mul() { ((void(*)(AttackModule*))_vt[101])(this); }
    f32 get_damage_reaction_mul() { return ((f32(*)(AttackModule*))_vt[102])(this); }

    // -- shield [105-106] --
    void set_shield_stiff_mul() { ((void(*)(AttackModule*))_vt[105])(this); }
    f32 shield_stiff_mul() { return ((f32(*)(AttackModule*))_vt[106])(this); }

    // -- just shield/lr [109-112] --
    void set_ignore_just_shield(bool p1) { ((void(*)(AttackModule*,bool))_vt[109])(this,p1); }
    f32 get_lr(u64 p1, bool p2) { return ((f32(*)(AttackModule*,u64,bool))_vt[111])(this,p1,p2); }
    u32 part_size() { return ((u32(*)(AttackModule*))_vt[112])(this); }

    // -- log/inflict [116-125] --
    void* ref_log_group(u64 p1, u64 p2) { return ((void*(*)(AttackModule*,u64,u64))_vt[116])(this,p1,p2); }
    void un_ref_log_group(u64 p1) { ((void(*)(AttackModule*,u64))_vt[117])(this,p1); }
    void* get_inflict() { return ((void*(*)(AttackModule*))_vt[119])(this); }
    bool is_infliction(u64 p1) { return ((bool(*)(AttackModule*,u64))_vt[120])(this,p1); }
    void* get_inflict_status() { return ((void*(*)(AttackModule*))_vt[121])(this); }
    bool is_infliction_status(u64 p1) { return ((bool(*)(AttackModule*,u64))_vt[122])(this,p1); }
    void set_indirect_info(u64 p1, u64 p2, bool p3, bool p4) { ((void(*)(AttackModule*,u64,u64,bool,bool))_vt[123])(this,p1,p2,p3,p4); }
    u32 indirect_object_id() { return ((u32(*)(AttackModule*))_vt[124])(this); }
    u32 indirect_team_no() { return ((u32(*)(AttackModule*))_vt[125])(this); }

    // -- restrict/catch [134-138] --
    void set_restrict(bool p1) { ((void(*)(AttackModule*,bool))_vt[134])(this,p1); }
    void set_no_attacker_log(u64 p1, bool p2, bool p3) { ((void(*)(AttackModule*,u64,bool,bool))_vt[135])(this,p1,p2,p3); }
    void set_catch_only(u64 p1, bool p2, bool p3) { ((void(*)(AttackModule*,u64,bool,bool))_vt[136])(this,p1,p2,p3); }
    void set_catch_only_all(bool p1, bool p2) { ((void(*)(AttackModule*,bool,bool))_vt[137])(this,p1,p2); }
    void set_attack_keep_rumble(u64 p1, bool p2) { ((void(*)(AttackModule*,u64,bool))_vt[138])(this,p1,p2); }

    // -- power up [139-145] --
    f32 get_power_up() { return ((f32(*)(AttackModule*))_vt[139])(this); }
    void set_power_up() { ((void(*)(AttackModule*))_vt[140])(this); }
    u32 get_power_up_attr() { return ((u32(*)(AttackModule*))_vt[141])(this); }
    void set_power_up_attr() { ((void(*)(AttackModule*))_vt[142])(this); }
    u32 get_attacker_attribute() { return ((u32(*)(AttackModule*))_vt[143])(this); }
    void set_attacker_attribute(u64 p1) { ((void(*)(AttackModule*,u64))_vt[144])(this,p1); }
    f32 get_power_apply_defense(u64 p1) { return ((f32(*)(AttackModule*,u64))_vt[145])(this,p1); }

    // -- attack part/reference [148-153] --
    void* attack_part_speed(u64 p1) { return ((void*(*)(AttackModule*,u64))_vt[148])(this,p1); }
    void* attack_reference_pos(u64 p1) { return ((void*(*)(AttackModule*,u64))_vt[149])(this,p1); }
    void* attack_direction() { return ((void*(*)(AttackModule*))_vt[150])(this); }
    void set_attack_reference_joint_id(u64 p1, u64 p2, u64 p3, u64 p4) { ((void(*)(AttackModule*,u64,u64,u64,u64))_vt[153])(this,p1,p2,p3,p4); }

    // -- overlap/team [156-157] --
    void set_overlap_hit(bool p1) { ((void(*)(AttackModule*,bool))_vt[156])(this,p1); }
    void set_no_team(bool p1) { ((void(*)(AttackModule*,bool))_vt[157])(this,p1); }

    // -- tip/relocate/lerp [159-167] --
    void* disable_tip() { return ((void*(*)(AttackModule*))_vt[159])(this); }
    void relocate(u64 p1) { ((void(*)(AttackModule*,u64))_vt[160])(this,p1); }
    void set_lerp(u64 p1, u64 p2, u64 p3) { ((void(*)(AttackModule*,u64,u64,u64))_vt[161])(this,p1,p2,p3); }
    void clear_lerp(u64 p1) { ((void(*)(AttackModule*,u64))_vt[162])(this,p1); }
    void set_lerp_ratio(u64 p1) { ((void(*)(AttackModule*,u64))_vt[163])(this,p1); }
    void set_attack_power_mul_pattern() { ((void(*)(AttackModule*))_vt[164])(this); }
    f32 get_attack_power_mul_pattern() { return ((f32(*)(AttackModule*))_vt[165])(this); }
    void set_attack_power_mul_scale() { ((void(*)(AttackModule*))_vt[166])(this); }
    f32 get_attack_power_mul_scale() { return ((f32(*)(AttackModule*))_vt[167])(this); }

    // -- lr check [168-174] --
    void set_lr_check_default(u64 p1) { ((void(*)(AttackModule*,u64))_vt[168])(this,p1); }
    u32 lr_check_default() { return ((u32(*)(AttackModule*))_vt[169])(this); }
    void set_lr_check_front(u64 p1) { ((void(*)(AttackModule*,u64))_vt[170])(this,p1); }
    void set_lr_check_back(u64 p1) { ((void(*)(AttackModule*,u64))_vt[171])(this,p1); }
    void set_lr_check_front_lr(u64 p1) { ((void(*)(AttackModule*,u64))_vt[172])(this,p1); }
    void set_disable_power_add_status_zero(bool p1) { ((void(*)(AttackModule*,bool))_vt[173])(this,p1); }
    void reset_status_attack(u64 p1) { ((void(*)(AttackModule*,u64))_vt[174])(this,p1); }

    // -- shake/latest [175-179] --
    void* damage_shake_scale() { return ((void*(*)(AttackModule*))_vt[175])(this); }
    void set_damage_shake_scale() { ((void(*)(AttackModule*))_vt[176])(this); }
    void set_latest_no(u64 p1) { ((void(*)(AttackModule*,u64))_vt[177])(this,p1); }
    void set_latest_absolute(bool p1) { ((void(*)(AttackModule*,bool))_vt[178])(this,p1); }
    void set_reflect_attack(bool p1) { ((void(*)(AttackModule*,bool))_vt[179])(this,p1); }

    // -- power up reaction/scale [180-184] --
    bool is_power_up_reaction() { return ((bool(*)(AttackModule*))_vt[180])(this); }
    void set_power_up_reaction(bool p1) { ((void(*)(AttackModule*,bool))_vt[181])(this,p1); }
    void set_attack_scale(bool p1) { ((void(*)(AttackModule*,bool))_vt[182])(this,p1); }
    void set_attack_scale_2nd() { ((void(*)(AttackModule*))_vt[183])(this); }
    void set_base_offset(u64 p1) { ((void(*)(AttackModule*,u64))_vt[184])(this,p1); }

    // -- occur/constraint [185-189] --
    bool is_attack_occur() { return ((bool(*)(AttackModule*))_vt[185])(this); }
    void set_constraint_pos(bool p1) { ((void(*)(AttackModule*,bool))_vt[186])(this,p1); }
    bool is_constraint_pos() { return ((bool(*)(AttackModule*))_vt[187])(this); }
    void set_no_dead_damage_fly_effect(bool p1) { ((void(*)(AttackModule*,bool))_vt[188])(this,p1); }
    bool is_no_dead_damage_fly_effect() { return ((bool(*)(AttackModule*))_vt[189])(this); }

    // -- damage effect [190-191] --
    void set_damage_effect_mul_scale() { ((void(*)(AttackModule*))_vt[190])(this); }
    f32 damage_effect_mul_scale() { return ((f32(*)(AttackModule*))_vt[191])(this); }

    // -- attack level/ink/paint [192-198] --
    void set_attack_level(u64 p1, u64 p2) { ((void(*)(AttackModule*,u64,u64))_vt[192])(this,p1,p2); }
    void set_ink_value(u64 p1) { ((void(*)(AttackModule*,u64))_vt[193])(this,p1); }
    void set_special_paint(u64 p1, u64 p2) { ((void(*)(AttackModule*,u64,u64))_vt[194])(this,p1,p2); }
    void set_paralyze_frame(u64 p1, u64 p2, bool p3) { ((void(*)(AttackModule*,u64,u64,bool))_vt[195])(this,p1,p2,p3); }
    void set_poison_param(u64 p1, u64 p2, u64 p3, bool p4) { ((void(*)(AttackModule*,u64,u64,u64,bool))_vt[196])(this,p1,p2,p3,p4); }
    void set_optional_hit_effect(u64 p1, u64 p2) { ((void(*)(AttackModule*,u64,u64))_vt[197])(this,p1,p2); }
    void set_optional_hit_sound(u64 p1, u64 p2) { ((void(*)(AttackModule*,u64,u64))_vt[198])(this,p1,p2); }

    // -- damage motion/camera [199-204] --
    void set_no_comp_damage_motion(u64 p1, bool p2) { ((void(*)(AttackModule*,u64,bool))_vt[199])(this,p1,p2); }
    void set_no_finish_camera(u64 p1, bool p2, bool p3) { ((void(*)(AttackModule*,u64,bool,bool))_vt[200])(this,p1,p2,p3); }
    void set_no_finish_camera_ex(u64 p1, bool p2, bool p3) { ((void(*)(AttackModule*,u64,bool,bool))_vt[201])(this,p1,p2,p3); }
    void set_final_finish_cut_in(u64 p1, bool p2, bool p3, bool p4) { ((void(*)(AttackModule*,u64,bool,bool,bool))_vt[202])(this,p1,p2,p3,p4); }
    void set_no_dead_all(bool p1, bool p2) { ((void(*)(AttackModule*,bool,bool))_vt[203])(this,p1,p2); }
    void set_no_damage_orbit_all(bool p1, bool p2) { ((void(*)(AttackModule*,bool,bool))_vt[204])(this,p1,p2); }

    // -- captured/composition [205-211] --
    void set_captured_same_time_attack(u64 p1, bool p2) { ((void(*)(AttackModule*,u64,bool))_vt[205])(this,p1,p2); }
    void set_captured_same_time_attack_damage_mul(u64 p1) { ((void(*)(AttackModule*,u64))_vt[206])(this,p1); }
    void set_attack_composition_speed(u64 p1, bool p2) { ((void(*)(AttackModule*,u64,bool))_vt[207])(this,p1,p2); }
    void set_attack_camera_quake(u64 p1, u64 p2, bool p3) { ((void(*)(AttackModule*,u64,u64,bool))_vt[208])(this,p1,p2,p3); }
    void set_attack_no_weight_reaction(u64 p1, u64 p2, bool p3) { ((void(*)(AttackModule*,u64,u64,bool))_vt[209])(this,p1,p2,p3); }
    void set_attack_no_weight_reaction_all(u64 p1, bool p2) { ((void(*)(AttackModule*,u64,bool))_vt[210])(this,p1,p2); }
    void set_attack_no_reaction_search(u64 p1, u64 p2, bool p3) { ((void(*)(AttackModule*,u64,u64,bool))_vt[211])(this,p1,p2,p3); }

    // -- inflict/force reaction [212-218] --
    void clear_inflict_kind_status() { ((void(*)(AttackModule*))_vt[212])(this); }
    void set_force_reaction(u64 p1, bool p2, bool p3) { ((void(*)(AttackModule*,u64,bool,bool))_vt[213])(this,p1,p2,p3); }
    void set_accept_no_lr(u64 p1, bool p2) { ((void(*)(AttackModule*,u64,bool))_vt[214])(this,p1,p2); }
    void set_nearest(u64 p1, bool p2) { ((void(*)(AttackModule*,u64,bool))_vt[215])(this,p1,p2); }
    void set_vec_target_pos(u64 p1, u64 p2, u64 p3, u64 p4, bool p5) { ((void(*)(AttackModule*,u64,u64,u64,u64,bool))_vt[216])(this,p1,p2,p3,p4,p5); }
    void enable_safe_pos() { ((void(*)(AttackModule*))_vt[217])(this); }
    void reset_safe_pos() { ((void(*)(AttackModule*))_vt[218])(this); }

    // -- critical [219-225] --
    bool is_critical_attack() { return ((bool(*)(AttackModule*))_vt[219])(this); }
    f32 get_critical_attack_damage_mul() { return ((f32(*)(AttackModule*))_vt[220])(this); }
    f32 get_critical_attack_reaction_mul() { return ((f32(*)(AttackModule*))_vt[221])(this); }
    void set_is_critical_attack(bool p1) { ((void(*)(AttackModule*,bool))_vt[222])(this,p1); }
    void set_critical_attack_damage_mul() { ((void(*)(AttackModule*))_vt[223])(this); }
    void set_critical_attack_reaction_mul() { ((void(*)(AttackModule*))_vt[224])(this); }
    void enable_attack_r_fix_damage_speed_up_all(bool p1) { ((void(*)(AttackModule*,bool))_vt[225])(this,p1); }

    // -- reaction frame [226-229] --
    void set_add_reaction_frame(u64 p1, bool p2) { ((void(*)(AttackModule*,u64,bool))_vt[226])(this,p1,p2); }
    void set_add_reaction_frame_revised(u64 p1, bool p2) { ((void(*)(AttackModule*,u64,bool))_vt[227])(this,p1,p2); }
    void set_set_off(u64 p1, u64 p2) { ((void(*)(AttackModule*,u64,u64))_vt[229])(this,p1,p2); }

    // -- squat/smoke/effect [230-233] --
    void set_no_squat_damage_reaction_mul(u64 p1, bool p2, bool p3) { ((void(*)(AttackModule*,u64,bool,bool))_vt[230])(this,p1,p2,p3); }
    void set_no_damage_fly_smoke_all(bool p1, bool p2) { ((void(*)(AttackModule*,bool,bool))_vt[231])(this,p1,p2); }
    void set_no_uniq_effect_all(bool p1, bool p2) { ((void(*)(AttackModule*,bool,bool))_vt[232])(this,p1,p2); }
    void set_no_world_scale(bool p1) { ((void(*)(AttackModule*,bool))_vt[233])(this,p1); }

    // -- height/hop/ice [234-242] --
    void set_attack_height(u64 p1, u64 p2, bool p3) { ((void(*)(AttackModule*,u64,u64,bool))_vt[234])(this,p1,p2,p3); }
    void set_attack_height_all(u64 p1, bool p2) { ((void(*)(AttackModule*,u64,bool))_vt[235])(this,p1,p2); }
    void set_no_hop_opponent(u64 p1, bool p2, bool p3) { ((void(*)(AttackModule*,u64,bool,bool))_vt[236])(this,p1,p2,p3); }
    void set_no_hop_opponent_all(bool p1, bool p2) { ((void(*)(AttackModule*,bool,bool))_vt[237])(this,p1,p2); }
    void set_ice_frame_mul(u64 p1, bool p2) { ((void(*)(AttackModule*,u64,bool))_vt[238])(this,p1,p2); }
    void set_down_only(u64 p1, bool p2) { ((void(*)(AttackModule*,u64,bool))_vt[239])(this,p1,p2); }
    void set_ignore_capture_cut(u64 p1, bool p2) { ((void(*)(AttackModule*,u64,bool))_vt[240])(this,p1,p2); }
    void set_ignore_ground_shield(u64 p1, bool p2) { ((void(*)(AttackModule*,u64,bool))_vt[241])(this,p1,p2); }
    void set_attack_camera_quake_forced(u64 p1, u64 p2, bool p3) { ((void(*)(AttackModule*,u64,u64,bool))_vt[242])(this,p1,p2,p3); }

    // -- lr check/resume [244-245] --
    void set_lr_check(u64 p1, u64 p2) { ((void(*)(AttackModule*,u64,u64))_vt[244])(this,p1,p2); }
    void resume_catch_absolute_damage() { ((void(*)(AttackModule*))_vt[245])(this); }

    // -- init [248] --
    void* init_attack_pos(u64 p1) { return ((void*(*)(AttackModule*,u64))_vt[248])(this,p1); }
};

} // namespace app
