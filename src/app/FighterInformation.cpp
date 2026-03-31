#include "types.h"

// FighterInformation — operates on FighterInformation* directly
// Pattern: ldr x8,[x0,#0x8] gets internal data, then field reads

struct FighterInformation;

namespace app::lua_bind {

// Simple 3-instruction struct reads (ldr data ptr, ldr/ldrb field, ret)
u8 FighterInformation__fighter_color_impl(FighterInformation* fi) {
    auto* data = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(fi) + 0x8);
    return data[0x51];
}
bool FighterInformation__is_rabbit_cap_impl(FighterInformation* fi) {
    auto* data = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(fi) + 0x8);
    return data[0x59];
}
bool FighterInformation__is_reflector_impl(FighterInformation* fi) {
    auto* data = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(fi) + 0x8);
    return data[0x5a];
}
bool FighterInformation__is_superleaf_impl(FighterInformation* fi) {
    auto* data = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(fi) + 0x8);
    return data[0x5b];
}
bool FighterInformation__is_rocketbelt_impl(FighterInformation* fi) {
    auto* data = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(fi) + 0x8);
    return data[0x5c];
}
bool FighterInformation__is_screw_impl(FighterInformation* fi) {
    auto* data = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(fi) + 0x8);
    return data[0x5d];
}
bool FighterInformation__is_backshield_impl(FighterInformation* fi) {
    auto* data = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(fi) + 0x8);
    return data[0x5e];
}
bool FighterInformation__is_operation_cpu_impl(FighterInformation* fi) {
    auto* data = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(fi) + 0x8);
    return data[0x5f];
}
u32 FighterInformation__stock_count_impl(FighterInformation* fi) {
    auto* data = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(fi) + 0x8);
    return *reinterpret_cast<u32*>(data + 0xd8);
}
u8 FighterInformation__fighter_category_impl(FighterInformation* fi) {
    auto* data = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(fi) + 0x8);
    return data[0x3ac];
}

// 6-instruction branching function
f32 FighterInformation__hit_point_max_impl(FighterInformation* fi, bool include_temp) {
    auto* data = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(fi) + 0x8);
    f32 base = *reinterpret_cast<f32*>(data + 0x38);
    if (!include_temp) {
        base += *reinterpret_cast<f32*>(data + 0x3c);
    }
    return base;
}

// Additional simple getters from agent data
bool FighterInformation__is_operation_cpu_real_impl(FighterInformation* fi) {
    auto* data = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(fi) + 0x8);
    return data[0x92];
}
bool FighterInformation__get_no_change_hp_impl(FighterInformation* fi) {
    auto* data = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(fi) + 0x8);
    return data[0x93];
}
bool FighterInformation__is_last_dead_suicide_impl(FighterInformation* fi) {
    auto* data = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(fi) + 0x8);
    return data[0x1a3];
}
// setter — stores float to field
void FighterInformation__set_add_rebirth_wait_frame_impl(FighterInformation* fi, f32 val) {
    auto* data = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(fi) + 0x8);
    *reinterpret_cast<f32*>(data + 0x1ac) = val;
}
bool FighterInformation__is_on_rebirth_impl(FighterInformation* fi) {
    auto* data = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(fi) + 0x8);
    return data[0x38c];
}
f32 FighterInformation__gravity_impl(FighterInformation* fi) {
    auto* data = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(fi) + 0x8);
    return *reinterpret_cast<f32*>(data + 0x36c);
}
u32 FighterInformation__summon_boss_id_impl(FighterInformation* fi) {
    auto* data = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(fi) + 0x8);
    return *reinterpret_cast<u32*>(data + 0x9a0);
}
u32 FighterInformation__summon_bomb_ready_frame_impl(FighterInformation* fi) {
    auto* data = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(fi) + 0x8);
    return *reinterpret_cast<u32*>(data + 0x9ac);
}
u32 FighterInformation__summon_pre_bomb_effect_frame_impl(FighterInformation* fi) {
    auto* data = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(fi) + 0x8);
    return *reinterpret_cast<u32*>(data + 0x9b0);
}
f32 FighterInformation__summon_suicide_bomb_attack_mul_impl(FighterInformation* fi) {
    auto* data = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(fi) + 0x8);
    return *reinterpret_cast<f32*>(data + 0x9bc);
}
f32 FighterInformation__summon_suicide_bomb_reaction_mul_impl(FighterInformation* fi) {
    auto* data = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(fi) + 0x8);
    return *reinterpret_cast<f32*>(data + 0x9c0);
}
bool FighterInformation__is_battle_event_stick_reverse_impl(FighterInformation* fi) {
    auto* data = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(fi) + 0x8);
    return data[0x9ca];
}

} // namespace app::lua_bind
