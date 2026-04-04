#include "app/BattleObjectModuleAccessor.h"
#include "app/modules/ControlModule.h"
#define CM(a) static_cast<ControlModule*>((a)->fighter_control_module)

namespace app::lua_bind {

// -- stick --
f32 ControlModule__get_stick_angle_impl(BattleObjectModuleAccessor* a) { return CM(a)->get_stick_angle(); }
s32 ControlModule__get_stick_dir_impl(BattleObjectModuleAccessor* a) { return CM(a)->get_stick_dir(); }
bool ControlModule__is_stick_side_impl(BattleObjectModuleAccessor* a) { return CM(a)->is_stick_side(); }
s32 ControlModule__get_sub_stick_dir_impl(BattleObjectModuleAccessor* a) { return CM(a)->get_sub_stick_dir(); }
bool ControlModule__is_sub_stickSide_impl(BattleObjectModuleAccessor* a) { return CM(a)->is_sub_stickSide(); }
bool ControlModule__is_enable_flick_jump_impl(BattleObjectModuleAccessor* a) { return CM(a)->is_enable_flick_jump(); }

// -- clatter --
void ControlModule__start_clatter_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,bool p3,bool p4) { CM(a)->start_clatter(p1,p2,p3,p4); }
void ControlModule__set_dec_time_impl(BattleObjectModuleAccessor* a,u64 p1) { CM(a)->set_dec_time(p1); }
void ControlModule__set_dec_time_recovery_impl(BattleObjectModuleAccessor* a,u64 p1) { CM(a)->set_dec_time_recovery(p1); }
void ControlModule__set_clatter_time_impl(BattleObjectModuleAccessor* a,u64 p1) { CM(a)->set_clatter_time(p1); }
void ControlModule__add_clatter_time_impl(BattleObjectModuleAccessor* a,u64 p1) { CM(a)->add_clatter_time(p1); }
void* ControlModule__get_clatter_time_impl(BattleObjectModuleAccessor* a,u64 p1) { return CM(a)->get_clatter_time(p1); }
void ControlModule__set_clatter_stop_impl(BattleObjectModuleAccessor* a,bool p1) { CM(a)->set_clatter_stop(p1); }
bool ControlModule__is_clatter_stop_impl(BattleObjectModuleAccessor* a) { return CM(a)->is_clatter_stop(); }
void ControlModule__start_clatter_motion_rate_impl(BattleObjectModuleAccessor* a) { CM(a)->start_clatter_motion_rate(); }
void ControlModule__end_clatter_motion_rate_impl(BattleObjectModuleAccessor* a) { CM(a)->end_clatter_motion_rate(); }
void* ControlModule__end_clatter_impl(BattleObjectModuleAccessor* a,u64 p1) { return CM(a)->end_clatter(p1); }
bool ControlModule__is_input_clatter_impl(BattleObjectModuleAccessor* a) { return CM(a)->is_input_clatter(); }
void ControlModule__set_clatter_shake_scale_impl(BattleObjectModuleAccessor* a) { CM(a)->set_clatter_shake_scale(); }

// -- button/stick reset --
void ControlModule__reset_button_impl(BattleObjectModuleAccessor* a) { CM(a)->reset_button(); }
void ControlModule__reset_button_on_impl(BattleObjectModuleAccessor* a) { CM(a)->reset_button_on(); }
void ControlModule__reset_button_off_impl(BattleObjectModuleAccessor* a,u64 p1) { CM(a)->reset_button_off(p1); }
void ControlModule__reset_button_trigger_impl(BattleObjectModuleAccessor* a) { CM(a)->reset_button_trigger(); }
void ControlModule__reset_trigger_impl(BattleObjectModuleAccessor* a) { CM(a)->reset_trigger(); }
void ControlModule__reset_trigger_2_impl(BattleObjectModuleAccessor* a,u64 p1) { CM(a)->reset_trigger_2(p1); }
void ControlModule__set_main_stick_x_impl(BattleObjectModuleAccessor* a) { CM(a)->set_main_stick_x(); }
void ControlModule__set_main_stick_y_impl(BattleObjectModuleAccessor* a) { CM(a)->set_main_stick_y(); }
void ControlModule__reset_main_stick_impl(BattleObjectModuleAccessor* a) { CM(a)->reset_main_stick(); }
void ControlModule__reset_main_stick_x_impl(BattleObjectModuleAccessor* a) { CM(a)->reset_main_stick_x(); }
void ControlModule__reset_main_stick_y_impl(BattleObjectModuleAccessor* a) { CM(a)->reset_main_stick_y(); }
void ControlModule__reset_sub_stick_impl(BattleObjectModuleAccessor* a) { CM(a)->reset_sub_stick(); }
void ControlModule__reset_sub_stick_x_impl(BattleObjectModuleAccessor* a) { CM(a)->reset_sub_stick_x(); }
void ControlModule__reset_sub_stick_y_impl(BattleObjectModuleAccessor* a) { CM(a)->reset_sub_stick_y(); }

// -- flick reset --
void ControlModule__reset_flick_x_impl(BattleObjectModuleAccessor* a) { CM(a)->reset_flick_x(); }
void ControlModule__reset_flick_y_impl(BattleObjectModuleAccessor* a) { CM(a)->reset_flick_y(); }
void ControlModule__reset_flick_sub_x_impl(BattleObjectModuleAccessor* a) { CM(a)->reset_flick_sub_x(); }
void ControlModule__reset_flick_sub_y_impl(BattleObjectModuleAccessor* a) { CM(a)->reset_flick_sub_y(); }
void ControlModule__reset_trigger_count_impl(BattleObjectModuleAccessor* a) { CM(a)->reset_trigger_count(); }

// -- stick values --
f32 ControlModule__get_stick_x_impl(BattleObjectModuleAccessor* a) { return CM(a)->get_stick_x(); }
f32 ControlModule__get_stick_prev_x_impl(BattleObjectModuleAccessor* a) { return CM(a)->get_stick_prev_x(); }
f32 ControlModule__get_stick_y_impl(BattleObjectModuleAccessor* a) { return CM(a)->get_stick_y(); }
f32 ControlModule__get_stick_prev_y_impl(BattleObjectModuleAccessor* a) { return CM(a)->get_stick_prev_y(); }
f32 ControlModule__get_flick_x_impl(BattleObjectModuleAccessor* a) { return CM(a)->get_flick_x(); }
s32 ControlModule__get_flick_x_dir_impl(BattleObjectModuleAccessor* a) { return CM(a)->get_flick_x_dir(); }
f32 ControlModule__get_flick_y_impl(BattleObjectModuleAccessor* a) { return CM(a)->get_flick_y(); }
s32 ControlModule__get_flick_y_dir_impl(BattleObjectModuleAccessor* a) { return CM(a)->get_flick_y_dir(); }
f32 ControlModule__get_flick_no_reset_x_impl(BattleObjectModuleAccessor* a) { return CM(a)->get_flick_no_reset_x(); }
f32 ControlModule__get_flick_no_reset_y_impl(BattleObjectModuleAccessor* a) { return CM(a)->get_flick_no_reset_y(); }
f32 ControlModule__get_flick_after_x_impl(BattleObjectModuleAccessor* a) { return CM(a)->get_flick_after_x(); }
s32 ControlModule__get_flick_after_x_dir_impl(BattleObjectModuleAccessor* a) { return CM(a)->get_flick_after_x_dir(); }
f32 ControlModule__get_flick_after_y_impl(BattleObjectModuleAccessor* a) { return CM(a)->get_flick_after_y(); }
f32 ControlModule__get_flick_sub_x_impl(BattleObjectModuleAccessor* a) { return CM(a)->get_flick_sub_x(); }
s32 ControlModule__get_flick_sub_x_dir_impl(BattleObjectModuleAccessor* a) { return CM(a)->get_flick_sub_x_dir(); }
f32 ControlModule__get_flick_sub_y_impl(BattleObjectModuleAccessor* a) { return CM(a)->get_flick_sub_y(); }
s32 ControlModule__get_flick_sub_y_dir_impl(BattleObjectModuleAccessor* a) { return CM(a)->get_flick_sub_y_dir(); }
f32 ControlModule__get_sub_stick_x_impl(BattleObjectModuleAccessor* a) { return CM(a)->get_sub_stick_x(); }
f32 ControlModule__get_sub_stick_prev_x_impl(BattleObjectModuleAccessor* a) { return CM(a)->get_sub_stick_prev_x(); }
f32 ControlModule__get_sub_stick_y_impl(BattleObjectModuleAccessor* a) { return CM(a)->get_sub_stick_y(); }
f32 ControlModule__get_sub_stick_prev_y_impl(BattleObjectModuleAccessor* a) { return CM(a)->get_sub_stick_prev_y(); }
f32 ControlModule__get_flick_y_no_reset_impl(BattleObjectModuleAccessor* a) { return CM(a)->get_flick_y_no_reset(); }
s32 ControlModule__get_flick_y_no_reset_dir_impl(BattleObjectModuleAccessor* a) { return CM(a)->get_flick_y_no_reset_dir(); }

// -- trigger/button --
u32 ControlModule__get_trigger_impl(BattleObjectModuleAccessor* a) { return CM(a)->get_trigger(); }
u32 ControlModule__get_trigger_count_impl(BattleObjectModuleAccessor* a,u64 p1) { return CM(a)->get_trigger_count(p1); }
u32 ControlModule__get_trigger_count_prev_impl(BattleObjectModuleAccessor* a,u64 p1) { return CM(a)->get_trigger_count_prev(p1); }
u32 ControlModule__get_button_impl(BattleObjectModuleAccessor* a) { return CM(a)->get_button(); }
u32 ControlModule__get_button_prev_impl(BattleObjectModuleAccessor* a) { return CM(a)->get_button_prev(); }
u32 ControlModule__get_release_impl(BattleObjectModuleAccessor* a) { return CM(a)->get_release(); }
bool ControlModule__check_button_trigger_impl(BattleObjectModuleAccessor* a,u64 p1) { return CM(a)->check_button_trigger(p1); }
bool ControlModule__check_button_release_impl(BattleObjectModuleAccessor* a,u64 p1) { return CM(a)->check_button_release(p1); }
bool ControlModule__check_button_on_impl(BattleObjectModuleAccessor* a,u64 p1) { return CM(a)->check_button_on(p1); }
bool ControlModule__check_button_off_impl(BattleObjectModuleAccessor* a,u64 p1) { return CM(a)->check_button_off(p1); }
bool ControlModule__check_button_on_trriger_impl(BattleObjectModuleAccessor* a,u64 p1) { return CM(a)->check_button_on_trriger(p1); }
bool ControlModule__check_button_on_release_impl(BattleObjectModuleAccessor* a,u64 p1) { return CM(a)->check_button_on_release(p1); }
void ControlModule__set_off_impl(BattleObjectModuleAccessor* a,bool p1) { CM(a)->set_off(p1); }

// -- near cliff/stick reverse --
void ControlModule__set_near_cliff_impl(BattleObjectModuleAccessor* a,bool p1,u64 p2) { CM(a)->set_near_cliff(p1,p2); }
void ControlModule__set_stick_reverse_impl(BattleObjectModuleAccessor* a,bool p1,u64 p2) { CM(a)->set_stick_reverse(p1,p2); }
bool ControlModule__is_stick_reversed_impl(BattleObjectModuleAccessor* a,u64 p1) { return CM(a)->is_stick_reversed(p1); }
void* ControlModule__get_clatter_threshold_impl(BattleObjectModuleAccessor* a,u64 p1) { return CM(a)->get_clatter_threshold(p1); }

// -- rumble --
void ControlModule__set_rumble_hit_data_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,bool p3,u64 p4,u64 p5) { CM(a)->set_rumble_hit_data(p1,p2,p3,p4,p5); }
void ControlModule__clear_rumble_hit_data_impl(BattleObjectModuleAccessor* a) { CM(a)->clear_rumble_hit_data(); }
void* ControlModule__request_rumble_hit_impl(BattleObjectModuleAccessor* a) { return CM(a)->request_rumble_hit(); }
void ControlModule__set_rumble_body_impl(BattleObjectModuleAccessor* a) { CM(a)->set_rumble_body(); }
void ControlModule__set_rumble_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,bool p3,u64 p4) { CM(a)->set_rumble(p1,p2,p3,p4); }
void ControlModule__set_rumble_all_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3) { CM(a)->set_rumble_all(p1,p2,p3); }
void ControlModule__set_rumble_heavy_hit_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { CM(a)->set_rumble_heavy_hit(p1,p2); }
void ControlModule__set_rumble_hit_damage_impl(BattleObjectModuleAccessor* a,u64 p1) { CM(a)->set_rumble_hit_damage(p1); }
void ControlModule__set_keep_rumble_impl(BattleObjectModuleAccessor* a,bool p1) { CM(a)->set_keep_rumble(p1); }
void* ControlModule__stop_rumble_impl(BattleObjectModuleAccessor* a,bool p1) { return CM(a)->stop_rumble(p1); }
void* ControlModule__stop_rumble_kind_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { return CM(a)->stop_rumble_kind(p1,p2); }
void* ControlModule__stop_rumble_id_impl(BattleObjectModuleAccessor* a,u64 p1) { return CM(a)->stop_rumble_id(p1); }
void* ControlModule__stop_rumble_all_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { return CM(a)->stop_rumble_all(p1,p2); }

// -- lr/reverse --
void ControlModule__set_reverse_x_frame_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { CM(a)->set_reverse_x_frame(p1,p2); }
f32 ControlModule__get_lr_impl(BattleObjectModuleAccessor* a) { return CM(a)->get_lr(); }
f32 ControlModule__get_flick_bonus_impl(BattleObjectModuleAccessor* a) { return CM(a)->get_flick_bonus(); }
f32 ControlModule__get_flick_bonus_lr_impl(BattleObjectModuleAccessor* a) { return CM(a)->get_flick_bonus_lr(); }
void ControlModule__reset_flick_bonus_impl(BattleObjectModuleAccessor* a) { CM(a)->reset_flick_bonus(); }
void ControlModule__reset_flick_bonus_lr_impl(BattleObjectModuleAccessor* a) { CM(a)->reset_flick_bonus_lr(); }
f32 ControlModule__get_stick_x_no_clamp_impl(BattleObjectModuleAccessor* a) { return CM(a)->get_stick_x_no_clamp(); }
f32 ControlModule__get_stick_y_no_clamp_impl(BattleObjectModuleAccessor* a) { return CM(a)->get_stick_y_no_clamp(); }

// -- pad/command --
u32 ControlModule__get_pad_flag_impl(BattleObjectModuleAccessor* a) { return CM(a)->get_pad_flag(); }
u32 ControlModule__get_command_flag_cat_impl(BattleObjectModuleAccessor* a,u64 p1) { return CM(a)->get_command_flag_cat(p1); }
void ControlModule__clear_command_impl(BattleObjectModuleAccessor* a,bool p1) { CM(a)->clear_command(p1); }
void ControlModule__clear_command_one_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { CM(a)->clear_command_one(p1,p2); }
void* ControlModule__get_command_life_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { return CM(a)->get_command_life(p1,p2); }
u32 ControlModule__get_command_life_count_max_impl(BattleObjectModuleAccessor* a) { return CM(a)->get_command_life_count_max(); }
void ControlModule__set_command_life_extend_impl(BattleObjectModuleAccessor* a,u64 p1) { CM(a)->set_command_life_extend(p1); }
bool ControlModule__is_clear_command_impl(BattleObjectModuleAccessor* a) { return CM(a)->is_clear_command(); }
void ControlModule__exec_command_impl(BattleObjectModuleAccessor* a,bool p1) { CM(a)->exec_command(p1); }
void ControlModule__set_back_command_impl(BattleObjectModuleAccessor* a) { CM(a)->set_back_command(); }

// -- attack kind --
s32 ControlModule__get_attack_s4_kind_impl(BattleObjectModuleAccessor* a) { return CM(a)->get_attack_s4_kind(); }
void ControlModule__reset_turn_lr_impl(BattleObjectModuleAccessor* a) { CM(a)->reset_turn_lr(); }
s32 ControlModule__get_attack_hi3_fb_kind_impl(BattleObjectModuleAccessor* a) { return CM(a)->get_attack_hi3_fb_kind(); }
s32 ControlModule__get_attack_lw3_fb_kind_impl(BattleObjectModuleAccessor* a) { return CM(a)->get_attack_lw3_fb_kind(); }
s32 ControlModule__get_attack_air_kind_impl(BattleObjectModuleAccessor* a) { return CM(a)->get_attack_air_kind(); }
s32 ControlModule__get_attack_hi4_kind_impl(BattleObjectModuleAccessor* a) { return CM(a)->get_attack_hi4_kind(); }
void ControlModule__reset_attack_air_kind_impl(BattleObjectModuleAccessor* a) { CM(a)->reset_attack_air_kind(); }
void ControlModule__set_attack_air_kind_impl(BattleObjectModuleAccessor* a,u64 p1) { CM(a)->set_attack_air_kind(p1); }
f32 ControlModule__get_attack_air_stick_x_impl(BattleObjectModuleAccessor* a) { return CM(a)->get_attack_air_stick_x(); }
f32 ControlModule__get_attack_air_stick_y_impl(BattleObjectModuleAccessor* a) { return CM(a)->get_attack_air_stick_y(); }
s32 ControlModule__get_attack_air_stick_dir_impl(BattleObjectModuleAccessor* a) { return CM(a)->get_attack_air_stick_dir(); }
s32 ControlModule__get_down_stand_fb_kind_impl(BattleObjectModuleAccessor* a) { return CM(a)->get_down_stand_fb_kind(); }
void ControlModule__reset_down_stand_fb_kind_impl(BattleObjectModuleAccessor* a) { CM(a)->reset_down_stand_fb_kind(); }
void ControlModule__set_down_stand_fb_kind_impl(BattleObjectModuleAccessor* a,u64 p1) { CM(a)->set_down_stand_fb_kind(p1); }
s32 ControlModule__get_catch_fb_kind_impl(BattleObjectModuleAccessor* a) { return CM(a)->get_catch_fb_kind(); }
s32 ControlModule__get_jump_fb_kind_impl(BattleObjectModuleAccessor* a) { return CM(a)->get_jump_fb_kind(); }
s32 ControlModule__get_escape_fb_kind_impl(BattleObjectModuleAccessor* a) { return CM(a)->get_escape_fb_kind(); }
s32 ControlModule__get_pass_fb_kind_impl(BattleObjectModuleAccessor* a) { return CM(a)->get_pass_fb_kind(); }
s32 ControlModule__get_appeal_fb_kind_impl(BattleObjectModuleAccessor* a) { return CM(a)->get_appeal_fb_kind(); }
s32 ControlModule__get_appeal_ud_kind_impl(BattleObjectModuleAccessor* a) { return CM(a)->get_appeal_ud_kind(); }
s32 ControlModule__get_cstick_tilt_fb_kind_impl(BattleObjectModuleAccessor* a) { return CM(a)->get_cstick_tilt_fb_kind(); }

// -- jump mini/remake --
bool ControlModule__is_jump_mini_button_impl(BattleObjectModuleAccessor* a) { return CM(a)->is_jump_mini_button(); }
void ControlModule__set_add_jump_mini_button_life_impl(BattleObjectModuleAccessor* a,u64 p1) { CM(a)->set_add_jump_mini_button_life(p1); }
bool ControlModule__is_remake_command_impl(BattleObjectModuleAccessor* a) { return CM(a)->is_remake_command(); }

// -- reserve/special command --
void* ControlModule__get_reserve_turn_lr_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { return CM(a)->get_reserve_turn_lr(p1,p2); }
void* ControlModule__delete_reserve_turn_lr_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { return CM(a)->delete_reserve_turn_lr(p1,p2); }
void ControlModule__set_special_command_impl(BattleObjectModuleAccessor* a,bool p1) { CM(a)->set_special_command(p1); }
void ControlModule__set_special_command_reserve_impl(BattleObjectModuleAccessor* a,bool p1) { CM(a)->set_special_command_reserve(p1); }
bool ControlModule__get_special_command_reserve_impl(BattleObjectModuleAccessor* a) { return CM(a)->get_special_command_reserve(); }
void* ControlModule__get_special_command_lr_impl(BattleObjectModuleAccessor* a,u64 p1) { return CM(a)->get_special_command_lr(p1); }
f32 ControlModule__get_special_command_stick_lr_impl(BattleObjectModuleAccessor* a) { return CM(a)->get_special_command_stick_lr(); }
void ControlModule__set_overwrite_special_button_raw_impl(BattleObjectModuleAccessor* a,bool p1) { CM(a)->set_overwrite_special_button_raw(p1); }
void ControlModule__set_special_command_life_count_max_impl(BattleObjectModuleAccessor* a,u64 p1) { CM(a)->set_special_command_life_count_max(p1); }
void ControlModule__set_special_command_life_count_extend_impl(BattleObjectModuleAccessor* a,u64 p1) { CM(a)->set_special_command_life_count_extend(p1); }
void ControlModule__set_special_command_life_extend_impl(BattleObjectModuleAccessor* a,u64 p1) { CM(a)->set_special_command_life_extend(p1); }
void ControlModule__reset_special_command_impl(BattleObjectModuleAccessor* a,bool p1) { CM(a)->reset_special_command(p1); }
void* ControlModule__reverse_special_command_impl(BattleObjectModuleAccessor* a) { return CM(a)->reverse_special_command(); }
void* ControlModule__reverse_x_frame_impl(BattleObjectModuleAccessor* a) { return CM(a)->reverse_x_frame(); }

// -- item throw --
void* ControlModule__item_light_throw_fb_kind_impl(BattleObjectModuleAccessor* a) { return CM(a)->item_light_throw_fb_kind(); }
void* ControlModule__item_light_throw_fb4_kind_impl(BattleObjectModuleAccessor* a) { return CM(a)->item_light_throw_fb4_kind(); }
void* ControlModule__item_light_throw_air_fb_kind_impl(BattleObjectModuleAccessor* a) { return CM(a)->item_light_throw_air_fb_kind(); }
void* ControlModule__item_light_throw_air_fb4_kind_impl(BattleObjectModuleAccessor* a) { return CM(a)->item_light_throw_air_fb4_kind(); }
void* ControlModule__item_heavy_throw_fb_kind_impl(BattleObjectModuleAccessor* a) { return CM(a)->item_heavy_throw_fb_kind(); }
void* ControlModule__special_s_turn_impl(BattleObjectModuleAccessor* a) { return CM(a)->special_s_turn(); }

} // namespace app::lua_bind
