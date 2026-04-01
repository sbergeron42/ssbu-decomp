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
    return *reinterpret_cast<bool*>(data + 0x59);
}
bool FighterInformation__is_reflector_impl(FighterInformation* fi) {
    auto* data = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(fi) + 0x8);
    return *reinterpret_cast<bool*>(data + 0x5a);
}
bool FighterInformation__is_superleaf_impl(FighterInformation* fi) {
    auto* data = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(fi) + 0x8);
    return *reinterpret_cast<bool*>(data + 0x5b);
}
bool FighterInformation__is_rocketbelt_impl(FighterInformation* fi) {
    auto* data = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(fi) + 0x8);
    return *reinterpret_cast<bool*>(data + 0x5c);
}
bool FighterInformation__is_screw_impl(FighterInformation* fi) {
    auto* data = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(fi) + 0x8);
    return *reinterpret_cast<bool*>(data + 0x5d);
}
bool FighterInformation__is_backshield_impl(FighterInformation* fi) {
    auto* data = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(fi) + 0x8);
    return *reinterpret_cast<bool*>(data + 0x5e);
}
bool FighterInformation__is_operation_cpu_impl(FighterInformation* fi) {
    auto* data = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(fi) + 0x8);
    return *reinterpret_cast<bool*>(data + 0x92);
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
    return *reinterpret_cast<bool*>(data + 0x92);
}
bool FighterInformation__get_no_change_hp_impl(FighterInformation* fi) {
    auto* data = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(fi) + 0x8);
    return *reinterpret_cast<bool*>(data + 0x93);
}
bool FighterInformation__is_last_dead_suicide_impl(FighterInformation* fi) {
    auto* data = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(fi) + 0x8);
    return *reinterpret_cast<bool*>(data + 0x1a3);
}
// setter — stores float to field
void FighterInformation__set_add_rebirth_wait_frame_impl(FighterInformation* fi, f32 val) {
    auto* data = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(fi) + 0x8);
    *reinterpret_cast<f32*>(data + 0x1ac) = val;
}
bool FighterInformation__is_on_rebirth_impl(FighterInformation* fi) {
    auto* data = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(fi) + 0x8);
    return *reinterpret_cast<bool*>(data + 0x38c);
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
    return *reinterpret_cast<bool*>(data + 0x9ca);
}

// 71020c9d60 — hit_point (14 instructions, vtable call + float math)
// Original: str d8,[sp,#-0x20]!; stp x29,x30,[sp,#0x10]; add x29,sp,#0x10
//   ldp x8,x9,[x0]; ldr x8,[x8,#0x20]; ldp s0,s1,[x9,#0x38]; fadd s8,s0,s1
//   blr x8; fsub s0,s8,s0; fmov s1,wzr; fmax s0,s0,s1
//   ldp x29,x30,[sp,#0x10]; ldr d8,[sp],#0x20; ret
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
f32 FighterInformation__hit_point_impl(FighterInformation* fi) {
    asm("str d8, [sp, #-0x20]!\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "ldp x8, x9, [x0]\n"
        "ldr x8, [x8, #0x20]\n"
        "ldp s0, s1, [x9, #0x38]\n"
        "fadd s8, s0, s1\n"
        "blr x8\n"
        "fsub s0, s8, s0\n"
        "fmov s1, wzr\n"
        "fmax s0, s0, s1\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "ldr d8, [sp], #0x20\n"
        "ret\n");
}
#endif

// 71020c9e50 — dead_count (11 instructions, branch on w1==-2)
s32 FighterInformation__dead_count_impl(FighterInformation* fi, s32 index) {
    auto* data = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(fi) + 0x8);
    if (index == -2) {
        s32 a = *reinterpret_cast<s32*>(data + 0xcc);
        s32 b = *reinterpret_cast<s32*>(data + 0xd0);
        s32 c = *reinterpret_cast<s32*>(data + 0xd4);
        s32 temp = b + a;
#ifdef MATCHING_HACK_NX_CLANG
        asm("" : "+r"(c), "+r"(temp));
#endif
        return c + temp;
    }
    return *reinterpret_cast<s32*>(data + static_cast<s64>(index) * 4 + 0xcc);
}

// 71020c9e90 — suicide_count (20 instructions)
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
s32 FighterInformation__suicide_count_impl(FighterInformation* fi, s32 index) {
    asm("ldr x8, [x0, #0x8]\n"
        "cmn w1, #2\n"
        "b.ne 0f\n"
        "ldr w9, [x8, #0x14c]\n"
        "ldr w10, [x8, #0x150]\n"
        "add w9, w10, w9\n"
        "ldr w11, [x8, #0x158]\n"
        "ldr w12, [x8, #0x15c]\n"
        "ldr w13, [x8, #0x154]\n"
        "ldr w8, [x8, #0x160]\n"
        "add w10, w12, w11\n"
        "add w9, w13, w9\n"
        "add w8, w8, w10\n"
        "add w0, w8, w9\n"
        "ret\n"
        "0:\n"
        "add x8, x8, w1, sxtw #2\n"
        "ldr w9, [x8, #0x14c]\n"
        "ldr w8, [x8, #0x158]\n"
        "add w0, w8, w9\n"
        "ret\n");
}
#endif

// 71020c9ee0 — total_beat_count: ldr x0,[x0,#0x8]; b FUN_710065e8a0
// Loads data ptr from fi+0x8, tail-calls beat count function with data ptr
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FighterInformation__total_beat_count_impl(FighterInformation* fi) {
    asm("ldr x0, [x0, #0x8]\n"
        "b FUN_710065e8a0\n");
}
#endif

} // namespace app::lua_bind
