// fun_typed_d_002.cpp — SoundModule signature-fix dispatchers
// The binary's mangled names have different parameter counts than our
// SoundModule.cpp compiles. These asm()-labeled functions produce the
// correct binary symbol names while keeping the correct vtable dispatch body.

#include "app/BattleObjectModuleAccessor.h"
#include "app/modules/SoundModule.h"

using app::BattleObjectModuleAccessor;
using app::SoundModule;
#define SM(a) static_cast<SoundModule*>((a)->sound_module)

namespace app::lua_bind {

// --- Functions where binary has fewer params than our build ---

void* SoundModule__play_hit_se_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2)
    asm("_ZN3app8lua_bind29SoundModule__play_hit_se_implEPNS_26BattleObjectModuleAccessorEy");
void* SoundModule__play_hit_se_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2) {
    return SM(a)->play_hit_se(p1, p2);
}

void* SoundModule__play_damage_se_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3, u64 p4)
    asm("_ZN3app8lua_bind32SoundModule__play_damage_se_implEPNS_26BattleObjectModuleAccessorEy");
void* SoundModule__play_damage_se_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3, u64 p4) {
    return SM(a)->play_damage_se(p1, p2, p3, p4);
}

void* SoundModule__play_step_flippable_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2)
    asm("_ZN3app8lua_bind37SoundModule__play_step_flippable_implEPNS_26BattleObjectModuleAccessorEy");
void* SoundModule__play_step_flippable_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2) {
    return SM(a)->play_step_flippable(p1, p2);
}

void* SoundModule__play_fly_voice_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2)
    asm("_ZN3app8lua_bind32SoundModule__play_fly_voice_implEPNS_26BattleObjectModuleAccessorEy");
void* SoundModule__play_fly_voice_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2) {
    return SM(a)->play_fly_voice(p1, p2);
}

void SoundModule__set_se_vol_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2)
    asm("_ZN3app8lua_bind28SoundModule__set_se_vol_implEPNS_26BattleObjectModuleAccessorEy");
void SoundModule__set_se_vol_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2) {
    SM(a)->set_se_vol(p1, p2);
}

void SoundModule__set_se_vol_db_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2)
    asm("_ZN3app8lua_bind31SoundModule__set_se_vol_db_implEPNS_26BattleObjectModuleAccessorEy");
void SoundModule__set_se_vol_db_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2) {
    SM(a)->set_se_vol_db(p1, p2);
}

void SoundModule__stop_se_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2)
    asm("_ZN3app8lua_bind25SoundModule__stop_se_implEPNS_26BattleObjectModuleAccessorEy");
void SoundModule__stop_se_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2) {
    SM(a)->stop_se(p1, p2);
}

void SoundModule__stop_se_handle_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2)
    asm("_ZN3app8lua_bind32SoundModule__stop_se_handle_implEPNS_26BattleObjectModuleAccessorEy");
void SoundModule__stop_se_handle_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2) {
    SM(a)->stop_se_handle(p1, p2);
}

void SoundModule__set_play_inhivit_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2)
    asm("_ZN3app8lua_bind34SoundModule__set_play_inhivit_implEPNS_26BattleObjectModuleAccessorEy");
void SoundModule__set_play_inhivit_fix(BattleObjectModuleAccessor* a, u64 p1, u64 p2) {
    SM(a)->set_play_inhivit(p1, p2);
}

// --- Functions where binary has more params than our build ---

void* SoundModule__get_se_vol_fix(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind28SoundModule__get_se_vol_implEPNS_26BattleObjectModuleAccessorE");
void* SoundModule__get_se_vol_fix(BattleObjectModuleAccessor* a, u64 p1) {
    return SM(a)->get_se_vol(p1);
}

void* SoundModule__get_se_vol_db_fix(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind31SoundModule__get_se_vol_db_implEPNS_26BattleObjectModuleAccessorE");
void* SoundModule__get_se_vol_db_fix(BattleObjectModuleAccessor* a, u64 p1) {
    return SM(a)->get_se_vol_db(p1);
}

void SoundModule__set_auto_se_pitch_fix(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind35SoundModule__set_auto_se_pitch_implEPNS_26BattleObjectModuleAccessorEy");
void SoundModule__set_auto_se_pitch_fix(BattleObjectModuleAccessor* a, u64 p1) {
    SM(a)->set_auto_se_pitch();
}

void SoundModule__set_se_pitch_status_fix(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind37SoundModule__set_se_pitch_status_implEPNS_26BattleObjectModuleAccessorEy");
void SoundModule__set_se_pitch_status_fix(BattleObjectModuleAccessor* a, u64 p1) {
    SM(a)->set_se_pitch_status();
}

void SoundModule__stop_loop_se_all_fix(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind34SoundModule__stop_loop_se_all_implEPNS_26BattleObjectModuleAccessorE");
void SoundModule__stop_loop_se_all_fix(BattleObjectModuleAccessor* a, u64 p1) {
    SM(a)->stop_loop_se_all(p1);
}

bool SoundModule__is_playing_fix(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind28SoundModule__is_playing_implEPNS_26BattleObjectModuleAccessorE");
bool SoundModule__is_playing_fix(BattleObjectModuleAccessor* a, u64 p1) {
    return SM(a)->is_playing(p1);
}

bool SoundModule__is_playing_status_fix(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind35SoundModule__is_playing_status_implEPNS_26BattleObjectModuleAccessorE");
bool SoundModule__is_playing_status_fix(BattleObjectModuleAccessor* a, u64 p1) {
    return SM(a)->is_playing_status(p1);
}

void* SoundModule__get_common_sound_label_fix(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind40SoundModule__get_common_sound_label_implEPNS_26BattleObjectModuleAccessorE");
void* SoundModule__get_common_sound_label_fix(BattleObjectModuleAccessor* a, u64 p1) {
    return SM(a)->get_common_sound_label(p1);
}

} // namespace app::lua_bind
