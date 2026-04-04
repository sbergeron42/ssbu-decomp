#include "app/BattleObjectModuleAccessor.h"
#include "app/modules/SoundModule.h"

namespace app::lua_bind {

static inline SoundModule* SM(BattleObjectModuleAccessor* a) {
    return static_cast<SoundModule*>(a->sound_module);
}

// Sound playback
void SoundModule__set_position_sub_impl(BattleObjectModuleAccessor* a, u64 p1) {
    SM(a)->set_position_sub(p1);
}

void SoundModule__play_se_impl(BattleObjectModuleAccessor* a, u64 hash, bool p2, bool p3, bool p4, bool p5, u64 p6) {
    SM(a)->play_se(hash, p2, p3, p4, p5, p6);
}

void SoundModule__play_se_no3d_impl(BattleObjectModuleAccessor* a, u64 p1, bool p2, bool p3) {
    SM(a)->play_se_no3d(p1, p2, p3);
}

void SoundModule__play_se_pos_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2, bool p3, bool p4) {
    SM(a)->play_se_pos(p1, p2, p3, p4);
}

void SoundModule__play_status_se_impl(BattleObjectModuleAccessor* a, u64 p1, bool p2, bool p3, bool p4) {
    SM(a)->play_status_se(p1, p2, p3, p4);
}

void SoundModule__stop_status_se_impl(BattleObjectModuleAccessor* a) {
    SM(a)->stop_status_se();
}

void SoundModule__play_sequence_impl(BattleObjectModuleAccessor* a, u64 p1, bool p2, bool p3) {
    SM(a)->play_sequence(p1, p2, p3);
}

// Hit SE flags
void SoundModule__set_play_hit_se_flag_impl(BattleObjectModuleAccessor* a, bool p1) {
    SM(a)->set_play_hit_se_flag(p1);
}

u32 SoundModule__get_play_hit_se_flag_impl(BattleObjectModuleAccessor* a) {
    return SM(a)->get_play_hit_se_flag();
}

void SoundModule__set_no_hit_se_impl(BattleObjectModuleAccessor* a, bool p1) {
    SM(a)->set_no_hit_se(p1);
}

u64 SoundModule__get_no_hit_se_impl(BattleObjectModuleAccessor* a) {
    return SM(a)->get_no_hit_se();
}

// Hit / Damage / Step
void* SoundModule__play_hit_se_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2) {
    return SM(a)->play_hit_se(p1, p2);
}

void* SoundModule__play_damage_se_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3, u64 p4) {
    return SM(a)->play_damage_se(p1, p2, p3, p4);
}

void SoundModule__play_step_impl(BattleObjectModuleAccessor* a, u64 p1) {
    SM(a)->play_step(p1);
}

void* SoundModule__play_step_flippable_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2) {
    return SM(a)->play_step_flippable(p1, p2);
}

// Landing / Down / Voice
void SoundModule__play_landing_se_impl(BattleObjectModuleAccessor* a, u64 p1) {
    SM(a)->play_landing_se(p1);
}

void SoundModule__play_down_se_impl(BattleObjectModuleAccessor* a, u64 p1) {
    SM(a)->play_down_se(p1);
}

void* SoundModule__play_fly_voice_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2) {
    return SM(a)->play_fly_voice(p1, p2);
}

// Volume control
void SoundModule__set_se_vol_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2) {
    SM(a)->set_se_vol(p1, p2);
}

void* SoundModule__get_se_vol_impl(BattleObjectModuleAccessor* a, u64 p1) {
    return SM(a)->get_se_vol(p1);
}

void SoundModule__set_se_vol_db_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2) {
    SM(a)->set_se_vol_db(p1, p2);
}

void* SoundModule__get_se_vol_db_impl(BattleObjectModuleAccessor* a, u64 p1) {
    return SM(a)->get_se_vol_db(p1);
}

// Pitch control
void SoundModule__set_auto_se_pitch_impl(BattleObjectModuleAccessor* a) {
    SM(a)->set_auto_se_pitch();
}

f32 SoundModule__get_auto_se_pitch_impl(BattleObjectModuleAccessor* a) {
    return SM(a)->get_auto_se_pitch();
}

void SoundModule__set_se_pitch_cent_impl(BattleObjectModuleAccessor* a, u64 p1) {
    SM(a)->set_se_pitch_cent(p1);
}

void SoundModule__set_se_pitch_ratio_impl(BattleObjectModuleAccessor* a, u64 p1) {
    SM(a)->set_se_pitch_ratio(p1);
}

void SoundModule__set_se_pitch_status_impl(BattleObjectModuleAccessor* a) {
    SM(a)->set_se_pitch_status();
}

void SoundModule__set_se_pitch_status_handle_impl(BattleObjectModuleAccessor* a, u64 p1) {
    SM(a)->set_se_pitch_status_handle(p1);
}

void SoundModule__set_continue_se_at_game_finish_impl(BattleObjectModuleAccessor* a, u64 p1, bool p2) {
    SM(a)->set_continue_se_at_game_finish(p1, p2);
}

// Stop / Pause
void SoundModule__stop_se_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2) {
    SM(a)->stop_se(p1, p2);
}

void SoundModule__stop_se_all_impl(BattleObjectModuleAccessor* a, u64 p1, bool p2, bool p3) {
    SM(a)->stop_se_all(p1, p2, p3);
}

void SoundModule__stop_loop_se_all_impl(BattleObjectModuleAccessor* a, u64 p1) {
    SM(a)->stop_loop_se_all(p1);
}

void SoundModule__stop_se_handle_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2) {
    SM(a)->stop_se_handle(p1, p2);
}

void SoundModule__stop_all_sound_impl(BattleObjectModuleAccessor* a) {
    SM(a)->stop_all_sound();
}

void SoundModule__pause_se_all_impl(BattleObjectModuleAccessor* a, bool p1) {
    SM(a)->pause_se_all(p1);
}

// Speed / Landing SE
void SoundModule__set_se_speed_impl(BattleObjectModuleAccessor* a, u64 p1) {
    SM(a)->set_se_speed(p1);
}

void SoundModule__set_landing_se_impl(BattleObjectModuleAccessor* a, u64 p1) {
    SM(a)->set_landing_se(p1);
}

u64 SoundModule__get_landing_se_impl(BattleObjectModuleAccessor* a) {
    return SM(a)->get_landing_se();
}

void SoundModule__play_landing_se_registered_impl(BattleObjectModuleAccessor* a) {
    SM(a)->play_landing_se_registered();
}

// Takeout SE
void SoundModule__set_takeout_se_impl(BattleObjectModuleAccessor* a, u64 p1) {
    SM(a)->set_takeout_se(p1);
}

void SoundModule__set_takeout_se_status_impl(BattleObjectModuleAccessor* a, u64 p1) {
    SM(a)->set_takeout_se_status(p1);
}

void SoundModule__reset_takeout_se_impl(BattleObjectModuleAccessor* a) {
    SM(a)->reset_takeout_se();
}

void SoundModule__play_takeout_se_impl(BattleObjectModuleAccessor* a) {
    SM(a)->play_takeout_se();
}

u64 SoundModule__get_takeout_se_impl(BattleObjectModuleAccessor* a) {
    return SM(a)->get_takeout_se();
}

u32 SoundModule__get_takeout_se_status_flag_impl(BattleObjectModuleAccessor* a) {
    return SM(a)->get_takeout_se_status_flag();
}

void SoundModule__set_play_inhivit_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2) {
    SM(a)->set_play_inhivit(p1, p2);
}

// Playing state / Labels
bool SoundModule__is_playing_impl(BattleObjectModuleAccessor* a, u64 p1) {
    return SM(a)->is_playing(p1);
}

bool SoundModule__is_playing_status_impl(BattleObjectModuleAccessor* a, u64 p1) {
    return SM(a)->is_playing_status(p1);
}

bool SoundModule__is_playing_voice_impl(BattleObjectModuleAccessor* a) {
    return SM(a)->is_playing_voice();
}

void* SoundModule__get_common_sound_label_impl(BattleObjectModuleAccessor* a, u64 p1) {
    return SM(a)->get_common_sound_label(p1);
}

void SoundModule__play_status_bgm_impl(BattleObjectModuleAccessor* a, u64 p1) {
    SM(a)->play_status_bgm(p1);
}

// Calibration / Remain
void SoundModule__set_gamespeed_se_calibration_impl(BattleObjectModuleAccessor* a, bool p1) {
    SM(a)->set_gamespeed_se_calibration(p1);
}

void SoundModule__set_remain_se_impl(BattleObjectModuleAccessor* a, bool p1) {
    SM(a)->set_remain_se(p1);
}

} // namespace app::lua_bind
