#include "app/BattleObjectModuleAccessor.h"

// SoundModule — accessor+0x148
#define SOUND_MODULE(acc) (*reinterpret_cast<void**>(reinterpret_cast<u8*>(acc) + 0x148))
#define VTABLE(mod) (*reinterpret_cast<void***>(mod))

namespace app::lua_bind {

// 7102081940 — play_se (4 bool params) [vtable+0xa8]
void SoundModule__play_se_impl(BattleObjectModuleAccessor* accessor, u64 hash, bool p2, bool p3, bool p4, bool p5, u64 p6) {
    auto* m = SOUND_MODULE(accessor); reinterpret_cast<void (*)(void*, u64, bool, bool, bool, bool, u64)>(VTABLE(m)[0xa8 / 8])(m, hash, p2, p3, p4, p5, p6);
}

// 7102081a10 — get_play_hit_se_flag [vtable+0xe0]
u32 SoundModule__get_play_hit_se_flag_impl(BattleObjectModuleAccessor* accessor) {
    auto* m = SOUND_MODULE(accessor); return reinterpret_cast<u32 (*)(void*)>(VTABLE(m)[0xe0 / 8])(m);
}

// 7102081a40 — get_no_hit_se [vtable+0xf0]
u64 SoundModule__get_no_hit_se_impl(BattleObjectModuleAccessor* accessor) {
    auto* m = SOUND_MODULE(accessor); return reinterpret_cast<u64 (*)(void*)>(VTABLE(m)[0xf0 / 8])(m);
}

// 7102081a50 — play_hit_se [vtable+0xf8]
void* SoundModule__play_hit_se_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x148)); return reinterpret_cast<void*(*)(void*,u64,u64)>(VTABLE(m)[0xf8/8])(m,p1,p2); }

// 7102081a60 — play_damage_se [vtable+0x100]
void* SoundModule__play_damage_se_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3,u64 p4) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x148)); return reinterpret_cast<void*(*)(void*,u64,u64,u64,u64)>(VTABLE(m)[0x100/8])(m,p1,p2,p3,p4); }

// 7102081a90 — play_landing_se [vtable+0x120]
void SoundModule__play_landing_se_impl(BattleObjectModuleAccessor* accessor, u64 p1) {
    auto* m = SOUND_MODULE(accessor); reinterpret_cast<void (*)(void*, u64)>(VTABLE(m)[0x120 / 8])(m, p1);
}

// 7102081aa0 — play_down_se [vtable+0x128]
void SoundModule__play_down_se_impl(BattleObjectModuleAccessor* accessor, u64 p1) {
    auto* m = SOUND_MODULE(accessor); reinterpret_cast<void (*)(void*, u64)>(VTABLE(m)[0x128 / 8])(m, p1);
}

// 7102081ab0 — play_fly_voice [vtable+0x130]
void* SoundModule__play_fly_voice_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x148)); return reinterpret_cast<void*(*)(void*,u64,u64)>(VTABLE(m)[0x130/8])(m,p1,p2); }

// 7102081ad0 — get_se_vol [vtable+0x140]
void* SoundModule__get_se_vol_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x148)); return reinterpret_cast<void*(*)(void*,u64)>(VTABLE(m)[0x140/8])(m,p1); }

// 7102081af0 — get_se_vol_db [vtable+0x150]
void* SoundModule__get_se_vol_db_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x148)); return reinterpret_cast<void*(*)(void*,u64)>(VTABLE(m)[0x150/8])(m,p1); }

// 7102081b10 — get_auto_se_pitch [vtable+0x160]
f32 SoundModule__get_auto_se_pitch_impl(BattleObjectModuleAccessor* accessor) {
    auto* m = SOUND_MODULE(accessor); return reinterpret_cast<f32 (*)(void*)>(VTABLE(m)[0x160 / 8])(m);
}

// 7102081be0 — pause_se_all (bool param) [vtable+0x1b8]
void SoundModule__pause_se_all_impl(BattleObjectModuleAccessor* accessor, bool pause) {
    auto* m = SOUND_MODULE(accessor); reinterpret_cast<void (*)(void*, bool)>(VTABLE(m)[0x1b8 / 8])(m, pause);
}

// 7102081c20 — get_landing_se [vtable+0x1d0]
u64 SoundModule__get_landing_se_impl(BattleObjectModuleAccessor* accessor) {
    auto* m = SOUND_MODULE(accessor); return reinterpret_cast<u64 (*)(void*)>(VTABLE(m)[0x1d0 / 8])(m);
}

// 7102081c30 — play_landing_se_registered [vtable+0x1d8]
void SoundModule__play_landing_se_registered_impl(BattleObjectModuleAccessor* accessor) {
    auto* m = SOUND_MODULE(accessor); reinterpret_cast<void (*)(void*)>(VTABLE(m)[0x1d8 / 8])(m);
}

// 7102081c80 — get_takeout_se [vtable+0x248]
u64 SoundModule__get_takeout_se_impl(BattleObjectModuleAccessor* accessor) {
    auto* m = SOUND_MODULE(accessor); return reinterpret_cast<u64 (*)(void*)>(VTABLE(m)[0x248 / 8])(m);
}

// 7102081c90 — get_takeout_se_status_flag [vtable+0x250]
u32 SoundModule__get_takeout_se_status_flag_impl(BattleObjectModuleAccessor* accessor) {
    auto* m = SOUND_MODULE(accessor); return reinterpret_cast<u32 (*)(void*)>(VTABLE(m)[0x250 / 8])(m);
}

// 7102081cb0 — is_playing [vtable+0x260]
bool SoundModule__is_playing_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x148)); return reinterpret_cast<bool(*)(void*,u64)>(VTABLE(m)[0x260/8])(m,p1); }

// 7102081cc0 — is_playing_status [vtable+0x268]
bool SoundModule__is_playing_status_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x148)); return reinterpret_cast<bool(*)(void*,u64)>(VTABLE(m)[0x268/8])(m,p1); }

// 7102081cd0 — is_playing_voice [vtable+0x270]
bool SoundModule__is_playing_voice_impl(BattleObjectModuleAccessor* accessor) {
    auto* m = SOUND_MODULE(accessor); return reinterpret_cast<bool (*)(void*)>(VTABLE(m)[0x270 / 8])(m);
}

// 7102081ce0 — get_common_sound_label [vtable+0x278]
void* SoundModule__get_common_sound_label_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x148)); return reinterpret_cast<void*(*)(void*,u64)>(VTABLE(m)[0x278/8])(m,p1); }

// Remaining SoundModule dispatchers
void SoundModule__set_position_sub_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=SOUND_MODULE(a); reinterpret_cast<void(*)(void*,u64)>(VTABLE(m)[0xa0/8])(m,p1); }
void SoundModule__play_se_no3d_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2,bool p3) { auto* m=SOUND_MODULE(a); reinterpret_cast<void(*)(void*,u64,bool,bool)>(VTABLE(m)[0xb0/8])(m,p1,p2,p3); }
void SoundModule__play_se_pos_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,bool p3,bool p4) { auto* m=SOUND_MODULE(a); reinterpret_cast<void(*)(void*,u64,u64,bool,bool)>(VTABLE(m)[0xb8/8])(m,p1,p2,p3,p4); }
void SoundModule__play_status_se_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2,bool p3,bool p4) { auto* m=SOUND_MODULE(a); reinterpret_cast<void(*)(void*,u64,bool,bool,bool)>(VTABLE(m)[0xc0/8])(m,p1,p2,p3,p4); }
void SoundModule__stop_status_se_impl(BattleObjectModuleAccessor* a) { auto* m=SOUND_MODULE(a); reinterpret_cast<void(*)(void*)>(VTABLE(m)[0xc8/8])(m); }
void SoundModule__play_sequence_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2,bool p3) { auto* m=SOUND_MODULE(a); reinterpret_cast<void(*)(void*,u64,bool,bool)>(VTABLE(m)[0xd0/8])(m,p1,p2,p3); }
void SoundModule__set_play_hit_se_flag_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=SOUND_MODULE(a); reinterpret_cast<void(*)(void*,bool)>(VTABLE(m)[0xd8/8])(m,p1); }
void SoundModule__set_no_hit_se_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=SOUND_MODULE(a); reinterpret_cast<void(*)(void*,bool)>(VTABLE(m)[0xe8/8])(m,p1); }
void SoundModule__play_step_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=SOUND_MODULE(a); reinterpret_cast<void(*)(void*,u64)>(VTABLE(m)[0x108/8])(m,p1); }
void* SoundModule__play_step_flippable_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x148)); return reinterpret_cast<void*(*)(void*,u64,u64)>(VTABLE(m)[0x110/8])(m,p1,p2); }
void SoundModule__set_se_vol_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x148)); reinterpret_cast<void(*)(void*,u64,u64)>(VTABLE(m)[0x138/8])(m,p1,p2); }
void SoundModule__set_se_vol_db_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x148)); reinterpret_cast<void(*)(void*,u64,u64)>(VTABLE(m)[0x148/8])(m,p1,p2); }
void SoundModule__set_auto_se_pitch_impl(BattleObjectModuleAccessor* a) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x148)); reinterpret_cast<void(*)(void*)>(VTABLE(m)[0x158/8])(m); }
void SoundModule__set_se_pitch_cent_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=SOUND_MODULE(a); reinterpret_cast<void(*)(void*,u64)>(VTABLE(m)[0x168/8])(m,p1); }
void SoundModule__set_se_pitch_ratio_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=SOUND_MODULE(a); reinterpret_cast<void(*)(void*,u64)>(VTABLE(m)[0x170/8])(m,p1); }
void SoundModule__set_se_pitch_status_impl(BattleObjectModuleAccessor* a) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x148)); reinterpret_cast<void(*)(void*)>(VTABLE(m)[0x178/8])(m); }
void SoundModule__set_se_pitch_status_handle_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=SOUND_MODULE(a); reinterpret_cast<void(*)(void*,u64)>(VTABLE(m)[0x180/8])(m,p1); }
void SoundModule__set_continue_se_at_game_finish_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { auto* m=SOUND_MODULE(a); reinterpret_cast<void(*)(void*,u64,bool)>(VTABLE(m)[0x188/8])(m,p1,p2); }
void SoundModule__stop_se_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x148)); reinterpret_cast<void(*)(void*,u64,u64)>(VTABLE(m)[0x190/8])(m,p1,p2); }
void SoundModule__stop_se_all_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2,bool p3) { auto* m=SOUND_MODULE(a); reinterpret_cast<void(*)(void*,u64,bool,bool)>(VTABLE(m)[0x198/8])(m,p1,p2,p3); }
void SoundModule__stop_loop_se_all_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x148)); reinterpret_cast<void(*)(void*,u64)>(VTABLE(m)[0x1a0/8])(m,p1); }
void SoundModule__stop_se_handle_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x148)); reinterpret_cast<void(*)(void*,u64,u64)>(VTABLE(m)[0x1a8/8])(m,p1,p2); }
void SoundModule__stop_all_sound_impl(BattleObjectModuleAccessor* a) { auto* m=SOUND_MODULE(a); reinterpret_cast<void(*)(void*)>(VTABLE(m)[0x1b0/8])(m); }
void SoundModule__set_se_speed_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=SOUND_MODULE(a); reinterpret_cast<void(*)(void*,u64)>(VTABLE(m)[0x1c0/8])(m,p1); }
void SoundModule__set_landing_se_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=SOUND_MODULE(a); reinterpret_cast<void(*)(void*,u64)>(VTABLE(m)[0x1c8/8])(m,p1); }
void SoundModule__set_takeout_se_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=SOUND_MODULE(a); reinterpret_cast<void(*)(void*,u64)>(VTABLE(m)[0x220/8])(m,p1); }
void SoundModule__set_takeout_se_status_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=SOUND_MODULE(a); reinterpret_cast<void(*)(void*,u64)>(VTABLE(m)[0x228/8])(m,p1); }
void SoundModule__reset_takeout_se_impl(BattleObjectModuleAccessor* a) { auto* m=SOUND_MODULE(a); reinterpret_cast<void(*)(void*)>(VTABLE(m)[0x238/8])(m); }
void SoundModule__play_takeout_se_impl(BattleObjectModuleAccessor* a) { auto* m=SOUND_MODULE(a); reinterpret_cast<void(*)(void*)>(VTABLE(m)[0x240/8])(m); }
void SoundModule__set_play_inhivit_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x148)); reinterpret_cast<void(*)(void*,u64,u64)>(VTABLE(m)[0x258/8])(m,p1,p2); }
void SoundModule__play_status_bgm_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=SOUND_MODULE(a); reinterpret_cast<void(*)(void*,u64)>(VTABLE(m)[0x280/8])(m,p1); }
void SoundModule__set_gamespeed_se_calibration_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=SOUND_MODULE(a); reinterpret_cast<void(*)(void*,bool)>(VTABLE(m)[0x2c0/8])(m,p1); }
void SoundModule__set_remain_se_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=SOUND_MODULE(a); reinterpret_cast<void(*)(void*,bool)>(VTABLE(m)[0x2d8/8])(m,p1); }
} // namespace app::lua_bind
