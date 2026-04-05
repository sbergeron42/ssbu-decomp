#pragma once
#include "types.h"

namespace app {

// ControlModule virtual dispatch wrapper
// Vtable entries recovered from lua_bind dispatcher analysis
// All method names derived from .dynsym lua_bind::ControlModule__*_impl dispatcher analysis.
// Module accessed via BattleObjectModuleAccessor +0x48 (fighter_control_module)
// FighterControlModuleImpl is the concrete subclass with additional field accesses
struct ControlModule {
    void** _vt;

    // Vtable dispatchers — index = byte_offset / 8
    // Names: [confirmed: lua_bind API name]
    // Dual-named entries share the same vtable slot

    // -- stick [9-14] --
    f32 get_stick_angle() { return ((f32(*)(ControlModule*))_vt[9])(this); }
    s32 get_stick_dir() { return ((s32(*)(ControlModule*))_vt[10])(this); }
    bool is_stick_side() { return ((bool(*)(ControlModule*))_vt[11])(this); }
    s32 get_sub_stick_dir() { return ((s32(*)(ControlModule*))_vt[12])(this); }
    bool is_sub_stickSide() { return ((bool(*)(ControlModule*))_vt[13])(this); }
    bool is_enable_flick_jump() { return ((bool(*)(ControlModule*))_vt[14])(this); }

    // -- clatter [15-26] --
    void start_clatter(u64 p1, u64 p2, bool p3, bool p4) { ((void(*)(ControlModule*,u64,u64,bool,bool))_vt[15])(this,p1,p2,p3,p4); }
    void set_dec_time(u64 p1) { ((void(*)(ControlModule*,u64))_vt[16])(this,p1); }
    void set_dec_time_recovery(u64 p1) { ((void(*)(ControlModule*,u64))_vt[17])(this,p1); }
    void set_clatter_time(u64 p1) { ((void(*)(ControlModule*,u64))_vt[18])(this,p1); }
    void add_clatter_time(u64 p1) { ((void(*)(ControlModule*,u64))_vt[19])(this,p1); }
    void* get_clatter_time(u64 p1) { return ((void*(*)(ControlModule*,u64))_vt[20])(this,p1); }
    void set_clatter_stop(bool p1) { ((void(*)(ControlModule*,bool))_vt[21])(this,p1); }
    bool is_clatter_stop() { return ((bool(*)(ControlModule*))_vt[22])(this); }
    void start_clatter_motion_rate() { ((void(*)(ControlModule*))_vt[23])(this); }
    void end_clatter_motion_rate() { ((void(*)(ControlModule*))_vt[24])(this); }
    void* end_clatter(u64 p1) { return ((void*(*)(ControlModule*,u64))_vt[25])(this,p1); }
    bool is_input_clatter() { return ((bool(*)(ControlModule*))_vt[26])(this); }

    // -- clatter shake [29] --
    void set_clatter_shake_scale() { ((void(*)(ControlModule*))_vt[29])(this); }

    // -- button reset [30-33] --
    void reset_button() { ((void(*)(ControlModule*))_vt[30])(this); }
    void reset_button_on() { ((void(*)(ControlModule*))_vt[31])(this); }
    void reset_trigger() { ((void(*)(ControlModule*))_vt[31])(this); }
    void reset_button_off(u64 p1) { ((void(*)(ControlModule*,u64))_vt[32])(this,p1); }
    void reset_trigger_2(u64 p1) { ((void(*)(ControlModule*,u64))_vt[32])(this,p1); }
    void reset_button_trigger() { ((void(*)(ControlModule*))_vt[33])(this); }
    void reset_main_stick_x() { ((void(*)(ControlModule*))_vt[33])(this); }

    // -- main stick [34-37] --
    void set_main_stick_x() { ((void(*)(ControlModule*))_vt[34])(this); }
    void reset_main_stick_y() { ((void(*)(ControlModule*))_vt[35])(this); }
    void set_main_stick_y() { ((void(*)(ControlModule*))_vt[36])(this); }
    void reset_main_stick() { ((void(*)(ControlModule*))_vt[37])(this); }

    // -- sub stick reset [38-40] --
    void reset_sub_stick_x() { ((void(*)(ControlModule*))_vt[38])(this); }
    void reset_sub_stick_y() { ((void(*)(ControlModule*))_vt[39])(this); }
    void reset_sub_stick() { ((void(*)(ControlModule*))_vt[40])(this); }

    // -- flick reset [43-46] --
    void reset_flick_x() { ((void(*)(ControlModule*))_vt[43])(this); }
    void reset_flick_y() { ((void(*)(ControlModule*))_vt[44])(this); }
    void reset_flick_sub_x() { ((void(*)(ControlModule*))_vt[45])(this); }
    void reset_flick_sub_y() { ((void(*)(ControlModule*))_vt[46])(this); }
    void reset_trigger_count() { ((void(*)(ControlModule*))_vt[46])(this); }

    // -- stick values [47-54] --
    f32 get_stick_x() { return ((f32(*)(ControlModule*))_vt[47])(this); }
    f32 get_stick_prev_x() { return ((f32(*)(ControlModule*))_vt[48])(this); }
    f32 get_stick_y() { return ((f32(*)(ControlModule*))_vt[49])(this); }
    f32 get_stick_prev_y() { return ((f32(*)(ControlModule*))_vt[50])(this); }
    f32 get_flick_x() { return ((f32(*)(ControlModule*))_vt[51])(this); }
    s32 get_flick_x_dir() { return ((s32(*)(ControlModule*))_vt[52])(this); }
    f32 get_flick_y() { return ((f32(*)(ControlModule*))_vt[53])(this); }
    s32 get_flick_y_dir() { return ((s32(*)(ControlModule*))_vt[54])(this); }

    // -- flick no reset [55-59] --
    f32 get_flick_no_reset_x() { return ((f32(*)(ControlModule*))_vt[55])(this); }
    f32 get_flick_no_reset_y() { return ((f32(*)(ControlModule*))_vt[56])(this); }
    f32 get_flick_after_x() { return ((f32(*)(ControlModule*))_vt[57])(this); }
    s32 get_flick_after_x_dir() { return ((s32(*)(ControlModule*))_vt[58])(this); }
    f32 get_flick_after_y() { return ((f32(*)(ControlModule*))_vt[59])(this); }

    // -- flick sub [60-63] --
    f32 get_flick_sub_x() { return ((f32(*)(ControlModule*))_vt[60])(this); }
    s32 get_flick_sub_x_dir() { return ((s32(*)(ControlModule*))_vt[61])(this); }
    f32 get_flick_sub_y() { return ((f32(*)(ControlModule*))_vt[62])(this); }
    s32 get_flick_sub_y_dir() { return ((s32(*)(ControlModule*))_vt[63])(this); }

    // -- sub stick values [64-67] --
    f32 get_sub_stick_x() { return ((f32(*)(ControlModule*))_vt[64])(this); }
    f32 get_sub_stick_prev_x() { return ((f32(*)(ControlModule*))_vt[65])(this); }
    f32 get_sub_stick_y() { return ((f32(*)(ControlModule*))_vt[66])(this); }
    f32 get_sub_stick_prev_y() { return ((f32(*)(ControlModule*))_vt[67])(this); }

    // -- trigger/button [68-80] --
    u32 get_trigger() { return ((u32(*)(ControlModule*))_vt[68])(this); }
    u32 get_trigger_count(u64 p1) { return ((u32(*)(ControlModule*,u64))_vt[69])(this,p1); }
    u32 get_trigger_count_prev(u64 p1) { return ((u32(*)(ControlModule*,u64))_vt[70])(this,p1); }
    u32 get_button() { return ((u32(*)(ControlModule*))_vt[71])(this); }
    u32 get_button_prev() { return ((u32(*)(ControlModule*))_vt[72])(this); }
    u32 get_release() { return ((u32(*)(ControlModule*))_vt[73])(this); }
    bool check_button_trigger(u64 p1) { return ((bool(*)(ControlModule*,u64))_vt[74])(this,p1); }
    bool check_button_release(u64 p1) { return ((bool(*)(ControlModule*,u64))_vt[75])(this,p1); }
    bool check_button_on(u64 p1) { return ((bool(*)(ControlModule*,u64))_vt[76])(this,p1); }
    bool check_button_off(u64 p1) { return ((bool(*)(ControlModule*,u64))_vt[77])(this,p1); }
    bool check_button_on_trriger(u64 p1) { return ((bool(*)(ControlModule*,u64))_vt[78])(this,p1); }
    bool check_button_on_release(u64 p1) { return ((bool(*)(ControlModule*,u64))_vt[79])(this,p1); }
    void set_off(bool p1) { ((void(*)(ControlModule*,bool))_vt[80])(this,p1); }

    // -- near cliff/stick reverse [82-84] --
    void set_near_cliff(bool p1, u64 p2) { ((void(*)(ControlModule*,bool,u64))_vt[82])(this,p1,p2); }
    void set_stick_reverse(bool p1, u64 p2) { ((void(*)(ControlModule*,bool,u64))_vt[82])(this,p1,p2); }
    bool is_stick_reversed(u64 p1) { return ((bool(*)(ControlModule*,u64))_vt[83])(this,p1); }
    void* get_clatter_threshold(u64 p1) { return ((void*(*)(ControlModule*,u64))_vt[84])(this,p1); }

    // -- rumble [86-95] --
    void set_rumble_hit_data(u64 p1, u64 p2, bool p3, u64 p4, u64 p5) { ((void(*)(ControlModule*,u64,u64,bool,u64,u64))_vt[86])(this,p1,p2,p3,p4,p5); }
    void clear_rumble_hit_data() { ((void(*)(ControlModule*))_vt[87])(this); }
    void set_rumble_body() { ((void(*)(ControlModule*))_vt[88])(this); }
    void* request_rumble_hit() { return ((void*(*)(ControlModule*))_vt[88])(this); }
    void set_rumble(u64 p1, u64 p2, bool p3, u64 p4) { ((void(*)(ControlModule*,u64,u64,bool,u64))_vt[90])(this,p1,p2,p3,p4); }
    void set_rumble_all(u64 p1, u64 p2, u64 p3) { ((void(*)(ControlModule*,u64,u64,u64))_vt[91])(this,p1,p2,p3); }
    void set_rumble_heavy_hit(u64 p1, u64 p2) { ((void(*)(ControlModule*,u64,u64))_vt[92])(this,p1,p2); }
    void* stop_rumble_kind(u64 p1, u64 p2) { return ((void*(*)(ControlModule*,u64,u64))_vt[92])(this,p1,p2); }
    void set_rumble_hit_damage(u64 p1) { ((void(*)(ControlModule*,u64))_vt[93])(this,p1); }
    void* stop_rumble_id(u64 p1) { return ((void*(*)(ControlModule*,u64))_vt[93])(this,p1); }
    void set_keep_rumble(bool p1) { ((void(*)(ControlModule*,bool))_vt[94])(this,p1); }
    void* stop_rumble(bool p1) { return ((void*(*)(ControlModule*,bool))_vt[94])(this,p1); }
    void* stop_rumble_all(u64 p1, u64 p2) { return ((void*(*)(ControlModule*,u64,u64))_vt[95])(this,p1,p2); }

    // -- lr/reverse [97-102] --
    void set_reverse_x_frame(u64 p1, bool p2) { ((void(*)(ControlModule*,u64,bool))_vt[97])(this,p1,p2); }
    f32 get_lr() { return ((f32(*)(ControlModule*))_vt[98])(this); }
    f32 get_flick_bonus() { return ((f32(*)(ControlModule*))_vt[99])(this); }
    f32 get_flick_bonus_lr() { return ((f32(*)(ControlModule*))_vt[100])(this); }
    f32 get_flick_y_no_reset() { return ((f32(*)(ControlModule*))_vt[101])(this); }
    void reset_flick_bonus() { ((void(*)(ControlModule*))_vt[101])(this); }
    s32 get_flick_y_no_reset_dir() { return ((s32(*)(ControlModule*))_vt[102])(this); }
    void reset_flick_bonus_lr() { ((void(*)(ControlModule*))_vt[102])(this); }

    // -- stick no clamp [103-104] --
    f32 get_stick_x_no_clamp() { return ((f32(*)(ControlModule*))_vt[103])(this); }
    f32 get_stick_y_no_clamp() { return ((f32(*)(ControlModule*))_vt[104])(this); }

    // -- pad/command [105-114] --
    u32 get_pad_flag() { return ((u32(*)(ControlModule*))_vt[105])(this); }
    u32 get_command_flag_cat(u64 p1) { return ((u32(*)(ControlModule*,u64))_vt[106])(this,p1); }
    void clear_command(bool p1) { ((void(*)(ControlModule*,bool))_vt[107])(this,p1); }
    void clear_command_one(u64 p1, u64 p2) { ((void(*)(ControlModule*,u64,u64))_vt[108])(this,p1,p2); }
    void* get_command_life(u64 p1, u64 p2) { return ((void*(*)(ControlModule*,u64,u64))_vt[109])(this,p1,p2); }
    u32 get_command_life_count_max() { return ((u32(*)(ControlModule*))_vt[110])(this); }
    void set_command_life_extend(u64 p1) { ((void(*)(ControlModule*,u64))_vt[111])(this,p1); }
    bool is_clear_command() { return ((bool(*)(ControlModule*))_vt[112])(this); }
    void exec_command(bool p1) { ((void(*)(ControlModule*,bool))_vt[113])(this,p1); }
    void set_back_command() { ((void(*)(ControlModule*))_vt[114])(this); }

    // -- attack kind [115-126] --
    s32 get_attack_s4_kind() { return ((s32(*)(ControlModule*))_vt[115])(this); }
    void reset_turn_lr() { ((void(*)(ControlModule*))_vt[115])(this); }
    s32 get_attack_hi3_fb_kind() { return ((s32(*)(ControlModule*))_vt[116])(this); }
    s32 get_attack_lw3_fb_kind() { return ((s32(*)(ControlModule*))_vt[117])(this); }
    s32 get_attack_air_kind() { return ((s32(*)(ControlModule*))_vt[118])(this); }
    s32 get_attack_hi4_kind() { return ((s32(*)(ControlModule*))_vt[119])(this); }
    void reset_attack_air_kind() { ((void(*)(ControlModule*))_vt[119])(this); }
    void set_attack_air_kind(u64 p1) { ((void(*)(ControlModule*,u64))_vt[120])(this,p1); }
    f32 get_attack_air_stick_x() { return ((f32(*)(ControlModule*))_vt[121])(this); }
    f32 get_attack_air_stick_y() { return ((f32(*)(ControlModule*))_vt[122])(this); }
    s32 get_attack_air_stick_dir() { return ((s32(*)(ControlModule*))_vt[123])(this); }
    s32 get_down_stand_fb_kind() { return ((s32(*)(ControlModule*))_vt[124])(this); }
    s32 get_catch_fb_kind() { return ((s32(*)(ControlModule*))_vt[125])(this); }
    void reset_down_stand_fb_kind() { ((void(*)(ControlModule*))_vt[125])(this); }
    void set_down_stand_fb_kind(u64 p1) { ((void(*)(ControlModule*,u64))_vt[126])(this,p1); }

    // -- fb kind [127-132] --
    s32 get_jump_fb_kind() { return ((s32(*)(ControlModule*))_vt[127])(this); }
    void* item_light_throw_fb_kind() { return ((void*(*)(ControlModule*))_vt[127])(this); }
    s32 get_escape_fb_kind() { return ((s32(*)(ControlModule*))_vt[128])(this); }
    void* item_light_throw_fb4_kind() { return ((void*(*)(ControlModule*))_vt[128])(this); }
    s32 get_pass_fb_kind() { return ((s32(*)(ControlModule*))_vt[129])(this); }
    void* item_light_throw_air_fb_kind() { return ((void*(*)(ControlModule*))_vt[129])(this); }
    s32 get_appeal_fb_kind() { return ((s32(*)(ControlModule*))_vt[130])(this); }
    void* item_light_throw_air_fb4_kind() { return ((void*(*)(ControlModule*))_vt[130])(this); }
    s32 get_appeal_ud_kind() { return ((s32(*)(ControlModule*))_vt[131])(this); }
    void* item_heavy_throw_fb_kind() { return ((void*(*)(ControlModule*))_vt[131])(this); }
    s32 get_cstick_tilt_fb_kind() { return ((s32(*)(ControlModule*))_vt[132])(this); }
    void* special_s_turn() { return ((void*(*)(ControlModule*))_vt[132])(this); }

    // -- jump mini/remake [133-136] --
    bool is_jump_mini_button() { return ((bool(*)(ControlModule*))_vt[133])(this); }
    void set_add_jump_mini_button_life(u64 p1) { ((void(*)(ControlModule*,u64))_vt[134])(this,p1); }
    bool is_remake_command() { return ((bool(*)(ControlModule*))_vt[136])(this); }

    // -- reserve/special command [137-146] --
    void* get_reserve_turn_lr(u64 p1, u64 p2) { return ((void*(*)(ControlModule*,u64,u64))_vt[137])(this,p1,p2); }
    void* delete_reserve_turn_lr(u64 p1, u64 p2) { return ((void*(*)(ControlModule*,u64,u64))_vt[138])(this,p1,p2); }
    void set_special_command(bool p1) { ((void(*)(ControlModule*,bool))_vt[139])(this,p1); }
    void set_special_command_reserve(bool p1) { ((void(*)(ControlModule*,bool))_vt[140])(this,p1); }
    void reset_special_command(bool p1) { ((void(*)(ControlModule*,bool))_vt[140])(this,p1); }
    bool get_special_command_reserve() { return ((bool(*)(ControlModule*))_vt[141])(this); }
    void* reverse_special_command() { return ((void*(*)(ControlModule*))_vt[141])(this); }
    void* get_special_command_lr(u64 p1) { return ((void*(*)(ControlModule*,u64))_vt[142])(this,p1); }
    f32 get_special_command_stick_lr() { return ((f32(*)(ControlModule*))_vt[143])(this); }
    void* reverse_x_frame() { return ((void*(*)(ControlModule*))_vt[143])(this); }
    void set_overwrite_special_button_raw(bool p1) { ((void(*)(ControlModule*,bool))_vt[144])(this,p1); }
    void set_special_command_life_count_max(u64 p1) { ((void(*)(ControlModule*,u64))_vt[145])(this,p1); }
    void set_special_command_life_extend(u64 p1) { ((void(*)(ControlModule*,u64))_vt[145])(this,p1); }
    void set_special_command_life_count_extend(u64 p1) { ((void(*)(ControlModule*,u64))_vt[146])(this,p1); }
};

} // namespace app
