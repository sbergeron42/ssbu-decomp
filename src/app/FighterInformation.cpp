#include "app/FighterInformation.h"

using app::FighterInformation;
using app::FighterInformationData;

namespace app::lua_bind {

// Simple 3-instruction struct reads (ldr data ptr, ldr/ldrb field, ret)
u8 FighterInformation__fighter_color_impl(FighterInformation* fi) {
    return fi->data->fighter_color;
}
bool FighterInformation__is_rabbit_cap_impl(FighterInformation* fi) {
    return fi->data->rabbit_cap;
}
bool FighterInformation__is_reflector_impl(FighterInformation* fi) {
    return fi->data->reflector;
}
bool FighterInformation__is_superleaf_impl(FighterInformation* fi) {
    return fi->data->superleaf;
}
bool FighterInformation__is_rocketbelt_impl(FighterInformation* fi) {
    return fi->data->rocketbelt;
}
bool FighterInformation__is_screw_impl(FighterInformation* fi) {
    return fi->data->screw;
}
bool FighterInformation__is_backshield_impl(FighterInformation* fi) {
    return fi->data->backshield;
}
bool FighterInformation__is_operation_cpu_impl(FighterInformation* fi) {
    return fi->data->operation_cpu;
}
u32 FighterInformation__stock_count_impl(FighterInformation* fi) {
    return fi->data->stock_count;
}
u8 FighterInformation__fighter_category_impl(FighterInformation* fi) {
    return fi->data->fighter_category;
}

// 6-instruction branching function
f32 FighterInformation__hit_point_max_impl(FighterInformation* fi, bool include_temp) {
    auto* d = fi->data;
    f32 base = d->hp_base;
    if (!include_temp) {
        base += d->hp_temp;
    }
    return base;
}

// Additional simple getters from agent data
// 71020c9e30
bool FighterInformation__is_operation_cpu_real_impl(FighterInformation* fi) {
    return fi->data->operation_cpu;
}
bool FighterInformation__get_no_change_hp_impl(FighterInformation* fi) {
    return fi->data->no_change_hp;
}
bool FighterInformation__is_last_dead_suicide_impl(FighterInformation* fi) {
    return fi->data->last_dead_suicide;
}
// setter -- stores float to field
void FighterInformation__set_add_rebirth_wait_frame_impl(FighterInformation* fi, f32 val) {
    fi->data->add_rebirth_wait_frame = val;
}
bool FighterInformation__is_on_rebirth_impl(FighterInformation* fi) {
    return fi->data->on_rebirth;
}
f32 FighterInformation__gravity_impl(FighterInformation* fi) {
    return fi->data->gravity;
}
u32 FighterInformation__summon_boss_id_impl(FighterInformation* fi) {
    return fi->data->summon_boss_id;
}
u32 FighterInformation__summon_bomb_ready_frame_impl(FighterInformation* fi) {
    return fi->data->summon_bomb_ready_frame;
}
u32 FighterInformation__summon_pre_bomb_effect_frame_impl(FighterInformation* fi) {
    return fi->data->summon_pre_bomb_effect_frame;
}
f32 FighterInformation__summon_suicide_bomb_attack_mul_impl(FighterInformation* fi) {
    return fi->data->summon_suicide_bomb_attack_mul;
}
f32 FighterInformation__summon_suicide_bomb_reaction_mul_impl(FighterInformation* fi) {
    return fi->data->summon_suicide_bomb_reaction_mul;
}
bool FighterInformation__is_battle_event_stick_reverse_impl(FighterInformation* fi) {
    return fi->data->battle_event_stick_reverse;
}

// 71020c9d60 -- hit_point (14 instructions, vtable call + float math)
// Original: str d8,[sp,#-0x20]!; stp x29,x30,[sp,#0x10]; add x29,sp,#0x10
//   ldp x8,x9,[x0]; ldr x8,[x8,#0x20]; ldp s0,s1,[x9,#0x38]; fadd s8,s0,s1
//   blr x8; fsub s0,s8,s0; fmov s1,wzr; fmax s0,s0,s1
//   ldp x29,x30,[sp,#0x10]; ldr d8,[sp],#0x20; ret
f32 FighterInformation__hit_point_impl(FighterInformation* fi) {
    auto fn = reinterpret_cast<f32(*)(FighterInformation*)>(fi->vtable[0x20/8]);
    auto* d = fi->data;
    f32 max_hp = d->hp_base + d->hp_temp;
    f32 damage = fn(fi);
#ifdef MATCHING_HACK_NX_CLANG
    asm("" : "+w"(max_hp));
#endif
    f32 result = max_hp - damage;
    f32 zero = 0.0f;
#ifdef MATCHING_HACK_NX_CLANG
    asm volatile("fmax %s0, %s1, %s2" : "=w"(result) : "w"(result), "w"(zero));
#else
    result = result > zero ? result : zero;
#endif
    return result;
}

// 71020c9e50 -- dead_count (11 instructions, branch on w1==-2)
s32 FighterInformation__dead_count_impl(FighterInformation* fi, s32 index) {
    auto* d = fi->data;
    if (index == -2) {
        s32 a = d->dead_count[0];
        s32 b = d->dead_count[1];
        s32 c = d->dead_count[2];
        s32 temp = b + a;
#ifdef MATCHING_HACK_NX_CLANG
        asm("" : "+r"(c), "+r"(temp));
#endif
        return c + temp;
    }
    return d->dead_count[index];
}

// 71020c9e90 -- suicide_count (20 instructions)
s32 FighterInformation__suicide_count_impl(FighterInformation* fi, s32 index) {
    auto* d = fi->data;
    if (index != -2) {
        s32 a = d->suicide_count_a[index];
        s32 b = d->suicide_count_b[index];
        return a + b;
    }
    s32 v0 = d->suicide_count_a[0];
    s32 v1 = d->suicide_count_a[1];
    s32 sum01 = v1 + v0;
    s32 v3 = d->suicide_count_b[0];
    s32 v4 = d->suicide_count_b[1];
    s32 v2 = d->suicide_count_a[2];
    s32 v5 = d->suicide_count_b[2];
#ifdef MATCHING_HACK_NX_CLANG
    asm("" : "+r"(v3), "+r"(v4), "+r"(v2), "+r"(v5), "+r"(sum01));
#endif
    s32 sum34 = v4 + v3;
    s32 sum012 = v2 + sum01;
    s32 sum345 = v5 + sum34;
    return sum345 + sum012;
}

// 71020c9ee0 -- total_beat_count (2 instructions, tail call)
extern "C" void FUN_710065e8a0(void*);
void FighterInformation__total_beat_count_impl(FighterInformation* fi) {
    FUN_710065e8a0(fi->data);
}

} // namespace app::lua_bind
