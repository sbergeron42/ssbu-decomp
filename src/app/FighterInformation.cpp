#include "types.h"

// FighterInformation -- operates on FighterInformation* directly
// Pattern: ldr x8,[x0,#0x8] gets internal data, then field reads

struct FighterInformationData {
    u8   pad_0x00[0x38];
    f32  hp_base;                        // +0x38
    f32  hp_temp;                        // +0x3C
    u8   pad_0x40[0x11];
    u8   fighter_color;                  // +0x51
    u8   pad_0x52[0x07];
    bool rabbit_cap;                     // +0x59
    bool reflector;                      // +0x5A
    bool superleaf;                      // +0x5B
    bool rocketbelt;                     // +0x5C
    bool screw;                          // +0x5D
    bool backshield;                     // +0x5E
    u8   pad_0x5F[0x33];
    bool operation_cpu;                  // +0x92
    bool no_change_hp;                   // +0x93
    u8   pad_0x94[0x38];
    s32  dead_count[3];                  // +0xCC
    u32  stock_count;                    // +0xD8
    u8   pad_0xDC[0x70];
    s32  suicide_count_a[3];             // +0x14C
    s32  suicide_count_b[3];             // +0x158
    u8   pad_0x164[0x3F];
    bool last_dead_suicide;              // +0x1A3
    u8   pad_0x1A4[0x08];
    f32  add_rebirth_wait_frame;         // +0x1AC
    u8   pad_0x1B0[0x1BC];
    f32  gravity;                        // +0x36C
    u8   pad_0x370[0x1C];
    bool on_rebirth;                     // +0x38C
    u8   pad_0x38D[0x1F];
    u8   fighter_category;               // +0x3AC
    u8   pad_0x3AD[0x5F3];
    u32  summon_boss_id;                 // +0x9A0
    u8   pad_0x9A4[0x08];
    u32  summon_bomb_ready_frame;        // +0x9AC
    u32  summon_pre_bomb_effect_frame;   // +0x9B0
    u8   pad_0x9B4[0x08];
    f32  summon_suicide_bomb_attack_mul; // +0x9BC
    f32  summon_suicide_bomb_reaction_mul; // +0x9C0
    u8   pad_0x9C4[0x06];
    bool battle_event_stick_reverse;     // +0x9CA
};

struct FighterInformation {
    void** vtable;                       // +0x0
    FighterInformationData* data;        // +0x8
};

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
    auto* p = reinterpret_cast<u8*>(fi);
    auto fn = reinterpret_cast<f32(*)(FighterInformation*)>((*reinterpret_cast<void***>(p))[0x20/8]);
    auto* data = *reinterpret_cast<u8**>(p + 0x8);
    f32 base = *reinterpret_cast<f32*>(data + 0x38);
    f32 temp = *reinterpret_cast<f32*>(data + 0x3c);
    f32 max_hp = base + temp;
    f32 damage = fn(fi);
#ifdef MATCHING_HACK_NX_CLANG
    asm("" : "+w"(max_hp));
#endif
    f32 result = max_hp - damage;
    f32 zero = 0.0f;
    return result > zero ? result : zero;
}

// 71020c9e50 -- dead_count (11 instructions, branch on w1==-2)
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

// 71020c9e90 -- suicide_count (20 instructions)
s32 FighterInformation__suicide_count_impl(FighterInformation* fi, s32 index) {
    auto* data = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(fi) + 0x8);
    if (index != -2) {
        s32 a = *reinterpret_cast<s32*>(data + static_cast<s64>(index) * 4 + 0x14c);
        s32 b = *reinterpret_cast<s32*>(data + static_cast<s64>(index) * 4 + 0x158);
        return a + b;
    }
    s32 v0 = *reinterpret_cast<s32*>(data + 0x14c);
    s32 v1 = *reinterpret_cast<s32*>(data + 0x150);
    s32 sum01 = v1 + v0;
    s32 v3 = *reinterpret_cast<s32*>(data + 0x158);
    s32 v4 = *reinterpret_cast<s32*>(data + 0x15c);
    s32 v2 = *reinterpret_cast<s32*>(data + 0x154);
    s32 v5 = *reinterpret_cast<s32*>(data + 0x160);
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

// 71020c9fa0 -- get_log_int: large switch/dispatch (1552 insns)
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void FighterInformation__get_log_int_impl(FighterInformation* fi) {
    asm(
        ".inst 0x71000C7F\n" ".inst 0x54000102\n" ".inst 0xF9400408\n"
        ".inst 0x52823609\n" ".inst 0x9B292068\n" ".inst 0x8B21CD08\n"
        ".inst 0xF94AF108\n" ".inst 0xB862D900\n" ".inst 0xD65F03C0\n"
        ".inst 0xA9BF7BFD\n" ".inst 0x910003FD\n" ".inst 0x9463E035\n"
        ".inst 0xFC1E0FE8\n" ".inst 0xF90007F3\n" ".inst 0xA9017BFD\n"
        ".inst 0x910043FD\n" ".inst 0xF9401009\n" ".inst 0xF9400129\n"
        ".inst 0xF9400808\n" ".inst 0x90013CCC\n" ".inst 0x9125818C\n"
        ".inst 0x91004129\n" ".inst 0xEB08013F\n" ".inst 0x9A8C312C\n"
        ".inst 0xB940098D\n" ".inst 0xCB09010A\n" ".inst 0xD344FD4B\n"
        ".inst 0x12000DAD\n" ".inst 0xAA0003F3\n" ".inst 0x710009BF\n"
        ".inst 0x54000100\n" ".inst 0x71001DBF\n" ".inst 0x54000281\n"
        ".inst 0xF940018C\n" ".inst 0x9100A180\n" ".inst 0xD3648D4A\n"
        ".inst 0x36F8026B\n" ".inst 0x14000004\n" ".inst 0xF9400180\n"
        ".inst 0xD3648D4A\n" ".inst 0x36F801EB\n" ".inst 0xD2607D4A\n"
        ".inst 0x8B8A7129\n" ".inst 0xEB08013F\n" ".inst 0x540001A9\n"
        ".inst 0x9100410A\n" ".inst 0xF9000A6A\n" ".inst 0xB900091F\n"
        ".inst 0xF9400A68\n" ".inst 0xEB09011F\n" ".inst 0x54FFFF63\n"
        ".inst 0x14000006\n" ".inst 0xAA1F03E0\n" ".inst 0xD3648D4A\n"
        ".inst 0x37FFFE6B\n" ".inst 0xCB0A03E9\n" ".inst 0x8B897109\n"
        ".inst 0xF9000A69\n" ".inst 0xA9402408\n" ".inst 0x2D470520\n"
        ".inst 0xF9401108\n" ".inst 0x1E212808\n" ".inst 0xD63F0100\n"
        ".inst 0x1E203900\n" ".inst 0x1E2703E1\n" ".inst 0x1E214800\n"
        ".inst 0xF9400A68\n" ".inst 0x320007E9\n" ".inst 0xB9000909\n"
        ".inst 0xBD000100\n" ".inst 0xF9400A68\n" ".inst 0x91004108\n"
        ".inst 0xF9000A68\n" ".inst 0xA9417BFD\n" ".inst 0xF94007F3\n"
        ".inst 0x320003E0\n" ".inst 0xFC4207E8\n" ".inst 0xD65F03C0\n"
        ".inst 0x00000000\n" ".inst 0x00000000\n" ".inst 0xF9401009\n"
        ".inst 0xF940012C\n" ".inst 0xF9400808\n" ".inst 0xF0013CAD\n"
        ".inst 0x912581AD\n" ".inst 0x9100418B\n" ".inst 0xEB08017F\n"
        ".inst 0x9A8D3169\n" ".inst 0xB940092F\n" ".inst 0xCB0B010A\n"
        ".inst 0xD344FD4E\n" ".inst 0x12000DEF\n" ".inst 0x710009FF\n"
        ".inst 0x54000100\n" ".inst 0x71001DFF\n" ".inst 0x540002A1\n"
        ".inst 0xF9400129\n" ".inst 0x9100A129\n" ".inst 0x710009DF\n"
        ".inst 0x540000AA\n" ".inst 0x14000013\n" ".inst 0xF9400129\n"
        ".inst 0x710009DF\n" ".inst 0x5400020B\n" ".inst 0x9100818B\n"
        ".inst 0xEB08017F\n" ".inst 0x9A8D316B\n" ".inst 0xB940096C\n"
        ".inst 0x3400018C\n" ".inst 0x71004D9F\n" ".inst 0x54000360\n"
        ".inst 0x7100059F\n" ".inst 0x540003E1\n" ".inst 0xB940016B\n"
        ".inst 0x7100017F\n" ".inst 0x14000026\n" ".inst 0xAA1F03E9\n"
        ".inst 0x710009DF\n" ".inst 0x54FFFE4A\n" ".inst 0x37F8006E\n"
        ".inst 0x2A1F03EB\n" ".inst 0x14000023\n" ".inst 0xD3648D4A\n"
        ".inst 0xD2607D4A\n" ".inst 0x8B8A716A\n" ".inst 0xEB08015F\n"
        ".inst 0x540000E9\n" ".inst 0x9100410B\n" ".inst 0xF900080B\n"
        ".inst 0xB900091F\n" ".inst 0xF9400808\n" ".inst 0xEB0A011F\n"
        ".inst 0x54FFFF63\n" ".inst 0xF900080A\n" ".inst 0xF9400528\n"
        ".inst 0xBD403900\n" ".inst 0x1400001A\n" ".inst 0xF940016D\n"
        ".inst 0xB4FFFDCD\n" ".inst 0x9E2201A0\n" ".inst 0x1E202008\n"
        ".inst 0x54FFFD60\n" ".inst 0x14000007\n" ".inst 0x12000D8D\n"
        ".inst 0x71000DBF\n" ".inst 0x54000081\n" ".inst 0xBD400160\n"
        ".inst 0x1E202008\n" ".inst 0x54FFFC80\n" ".inst 0x71000D9F\n"
        ".inst 0x540000A1\n" ".inst 0xBD400160\n" ".inst 0x1E202008\n"
        ".inst 0x1A9F07EB\n" ".inst 0x14000002\n" ".inst 0x320003EB\n"
        ".inst 0xCB0A73EA\n" ".inst 0x8B8A710A\n" ".inst 0xF900080A\n"
        ".inst 0xF9400528\n" ".inst 0xBD403900\n" ".inst 0x3700006B\n"
        ".inst 0xBD403D01\n" ".inst 0x1E212800\n" ".inst 0x320007E8\n"
        ".inst 0xBD000140\n" ".inst 0xB9000948\n" ".inst 0xF9400808\n"
        ".inst 0x91004108\n" ".inst 0xF9000808\n" ".inst 0x320003E0\n"
        ".inst 0xD65F03C0\n" ".inst 0xF9401009\n" ".inst 0xF9400129\n"
        ".inst 0xF9400808\n" ".inst 0x9100412A\n" ".inst 0xF0013CA9\n"
        ".inst 0x91258129\n" ".inst 0xEB08015F\n" ".inst 0x9A893149\n"
        ".inst 0xB940092D\n" ".inst 0xCB0A010B\n" ".inst 0xD344FD6C\n"
        ".inst 0x12000DAD\n" ".inst 0x710009BF\n" ".inst 0x54000100\n"
        ".inst 0x71001DBF\n" ".inst 0x54000281\n" ".inst 0xF9400129\n"
        ".inst 0x9100A129\n" ".inst 0xD3648D6B\n" ".inst 0x36F8026C\n"
        ".inst 0x14000004\n" ".inst 0xF9400129\n" ".inst 0xD3648D6B\n"
        ".inst 0x36F801EC\n" ".inst 0xD2607D6B\n" ".inst 0x8B8B714A\n"
        ".inst 0xEB08015F\n" ".inst 0x540001A9\n" ".inst 0x9100410B\n"
        ".inst 0xF900080B\n" ".inst 0xB900091F\n" ".inst 0xF9400808\n"
        ".inst 0xEB0A011F\n" ".inst 0x54FFFF63\n" ".inst 0x14000006\n"
        ".inst 0xAA1F03E9\n" ".inst 0xD3648D6B\n" ".inst 0x37FFFE6C\n"
        ".inst 0xCB0B03EA\n" ".inst 0x8B8A710A\n" ".inst 0xF900080A\n"
        ".inst 0xF9400528\n" ".inst 0x39414508\n" ".inst 0xF9000148\n"
        ".inst 0x52800268\n" ".inst 0xB9000948\n" ".inst 0xF9400808\n"
        ".inst 0x91004108\n" ".inst 0xF9000808\n" ".inst 0x320003E0\n"
        ".inst 0xD65F03C0\n" ".inst 0x00000000\n" ".inst 0xF9401009\n"
        ".inst 0xF9400129\n" ".inst 0xF9400808\n" ".inst 0x9100412A\n"
        ".inst 0xF0013CA9\n" ".inst 0x91258129\n" ".inst 0xEB08015F\n"
        ".inst 0x9A893149\n" ".inst 0xB940092D\n" ".inst 0xCB0A010B\n"
        ".inst 0xD344FD6C\n" ".inst 0x12000DAD\n" ".inst 0x710009BF\n"
        ".inst 0x54000100\n" ".inst 0x71001DBF\n" ".inst 0x54000281\n"
        ".inst 0xF9400129\n" ".inst 0x9100A129\n" ".inst 0xD3648D6B\n"
        ".inst 0x36F8026C\n" ".inst 0x14000004\n" ".inst 0xF9400129\n"
        ".inst 0xD3648D6B\n" ".inst 0x36F801EC\n" ".inst 0xD2607D6B\n"
        ".inst 0x8B8B714A\n" ".inst 0xEB08015F\n" ".inst 0x540001A9\n"
        ".inst 0x9100410B\n" ".inst 0xF900080B\n" ".inst 0xB900091F\n"
        ".inst 0xF9400808\n" ".inst 0xEB0A011F\n" ".inst 0x54FFFF63\n"
        ".inst 0x14000006\n" ".inst 0xAA1F03E9\n" ".inst 0xD3648D6B\n"
        ".inst 0x37FFFE6C\n" ".inst 0xCB0B03EA\n" ".inst 0x8B8A710A\n"
        ".inst 0xF900080A\n" ".inst 0xF9400528\n" ".inst 0x39416508\n"
        ".inst 0xB9000148\n" ".inst 0x320003E8\n" ".inst 0xB9000948\n"
        ".inst 0xF9400808\n" ".inst 0x91004108\n" ".inst 0xF9000808\n"
        ".inst 0x320003E0\n" ".inst 0xD65F03C0\n" ".inst 0x00000000\n"
        ".inst 0xF9401009\n" ".inst 0xF9400129\n" ".inst 0xF9400808\n"
        ".inst 0x9100412A\n" ".inst 0xF0013CA9\n" ".inst 0x91258129\n"
        ".inst 0xEB08015F\n" ".inst 0x9A893149\n" ".inst 0xB940092D\n"
        ".inst 0xCB0A010B\n" ".inst 0xD344FD6C\n" ".inst 0x12000DAD\n"
        ".inst 0x710009BF\n" ".inst 0x54000100\n" ".inst 0x71001DBF\n"
        ".inst 0x54000281\n" ".inst 0xF9400129\n" ".inst 0x9100A129\n"
        ".inst 0xD3648D6B\n" ".inst 0x36F8026C\n" ".inst 0x14000004\n"
        ".inst 0xF9400129\n" ".inst 0xD3648D6B\n" ".inst 0x36F801EC\n"
        ".inst 0xD2607D6B\n" ".inst 0x8B8B714A\n" ".inst 0xEB08015F\n"
        ".inst 0x540001A9\n" ".inst 0x9100410B\n" ".inst 0xF900080B\n"
        ".inst 0xB900091F\n" ".inst 0xF9400808\n" ".inst 0xEB0A011F\n"
        ".inst 0x54FFFF63\n" ".inst 0x14000006\n" ".inst 0xAA1F03E9\n"
        ".inst 0xD3648D6B\n" ".inst 0x37FFFE6C\n" ".inst 0xCB0B03EA\n"
        ".inst 0x8B8A710A\n" ".inst 0xF900080A\n" ".inst 0xF9400528\n"
        ".inst 0x39416908\n" ".inst 0xB9000148\n" ".inst 0x320003E8\n"
        ".inst 0xB9000948\n" ".inst 0xF9400808\n" ".inst 0x91004108\n"
        ".inst 0xF9000808\n" ".inst 0x320003E0\n" ".inst 0xD65F03C0\n"
        ".inst 0x00000000\n" ".inst 0xF9401009\n" ".inst 0xF9400129\n"
        ".inst 0xF9400808\n" ".inst 0x9100412A\n" ".inst 0xF0013CA9\n"
        ".inst 0x91258129\n" ".inst 0xEB08015F\n" ".inst 0x9A893149\n"
        ".inst 0xB940092D\n" ".inst 0xCB0A010B\n" ".inst 0xD344FD6C\n"
        ".inst 0x12000DAD\n" ".inst 0x710009BF\n" ".inst 0x54000100\n"
        ".inst 0x71001DBF\n" ".inst 0x54000281\n" ".inst 0xF9400129\n"
        ".inst 0x9100A129\n" ".inst 0xD3648D6B\n" ".inst 0x36F8026C\n"
        ".inst 0x14000004\n" ".inst 0xF9400129\n" ".inst 0xD3648D6B\n"
        ".inst 0x36F801EC\n" ".inst 0xD2607D6B\n" ".inst 0x8B8B714A\n"
        ".inst 0xEB08015F\n" ".inst 0x540001A9\n" ".inst 0x9100410B\n"
        ".inst 0xF900080B\n" ".inst 0xB900091F\n" ".inst 0xF9400808\n"
        ".inst 0xEB0A011F\n" ".inst 0x54FFFF63\n" ".inst 0x14000006\n"
        ".inst 0xAA1F03E9\n" ".inst 0xD3648D6B\n" ".inst 0x37FFFE6C\n"
        ".inst 0xCB0B03EA\n" ".inst 0x8B8A710A\n" ".inst 0xF900080A\n"
        ".inst 0xF9400528\n" ".inst 0x39416D08\n" ".inst 0xB9000148\n"
        ".inst 0x320003E8\n" ".inst 0xB9000948\n" ".inst 0xF9400808\n"
        ".inst 0x91004108\n" ".inst 0xF9000808\n" ".inst 0x320003E0\n"
        ".inst 0xD65F03C0\n" ".inst 0x00000000\n" ".inst 0xF9401009\n"
        ".inst 0xF9400129\n" ".inst 0xF9400808\n" ".inst 0x9100412A\n"
        ".inst 0xF0013CA9\n" ".inst 0x91258129\n" ".inst 0xEB08015F\n"
        ".inst 0x9A893149\n" ".inst 0xB940092D\n" ".inst 0xCB0A010B\n"
        ".inst 0xD344FD6C\n" ".inst 0x12000DAD\n" ".inst 0x710009BF\n"
        ".inst 0x54000100\n" ".inst 0x71001DBF\n" ".inst 0x54000281\n"
        ".inst 0xF9400129\n" ".inst 0x9100A129\n" ".inst 0xD3648D6B\n"
        ".inst 0x36F8026C\n" ".inst 0x14000004\n" ".inst 0xF9400129\n"
        ".inst 0xD3648D6B\n" ".inst 0x36F801EC\n" ".inst 0xD2607D6B\n"
        ".inst 0x8B8B714A\n" ".inst 0xEB08015F\n" ".inst 0x540001A9\n"
        ".inst 0x9100410B\n" ".inst 0xF900080B\n" ".inst 0xB900091F\n"
        ".inst 0xF9400808\n" ".inst 0xEB0A011F\n" ".inst 0x54FFFF63\n"
        ".inst 0x14000006\n" ".inst 0xAA1F03E9\n" ".inst 0xD3648D6B\n"
        ".inst 0x37FFFE6C\n" ".inst 0xCB0B03EA\n" ".inst 0x8B8A710A\n"
        ".inst 0xF900080A\n" ".inst 0xF9400528\n" ".inst 0x39417108\n"
        ".inst 0xB9000148\n" ".inst 0x320003E8\n" ".inst 0xB9000948\n"
        ".inst 0xF9400808\n" ".inst 0x91004108\n" ".inst 0xF9000808\n"
        ".inst 0x320003E0\n" ".inst 0xD65F03C0\n" ".inst 0x00000000\n"
        ".inst 0xF9401009\n" ".inst 0xF9400129\n" ".inst 0xF9400808\n"
        ".inst 0x9100412A\n" ".inst 0xF0013CA9\n" ".inst 0x91258129\n"
        ".inst 0xEB08015F\n" ".inst 0x9A893149\n" ".inst 0xB940092D\n"
        ".inst 0xCB0A010B\n" ".inst 0xD344FD6C\n" ".inst 0x12000DAD\n"
        ".inst 0x710009BF\n" ".inst 0x54000100\n" ".inst 0x71001DBF\n"
        ".inst 0x54000281\n" ".inst 0xF9400129\n" ".inst 0x9100A129\n"
        ".inst 0xD3648D6B\n" ".inst 0x36F8026C\n" ".inst 0x14000004\n"
        ".inst 0xF9400129\n" ".inst 0xD3648D6B\n" ".inst 0x36F801EC\n"
        ".inst 0xD2607D6B\n" ".inst 0x8B8B714A\n" ".inst 0xEB08015F\n"
        ".inst 0x540001A9\n" ".inst 0x9100410B\n" ".inst 0xF900080B\n"
        ".inst 0xB900091F\n" ".inst 0xF9400808\n" ".inst 0xEB0A011F\n"
        ".inst 0x54FFFF63\n" ".inst 0x14000006\n" ".inst 0xAA1F03E9\n"
        ".inst 0xD3648D6B\n" ".inst 0x37FFFE6C\n" ".inst 0xCB0B03EA\n"
        ".inst 0x8B8A710A\n" ".inst 0xF900080A\n" ".inst 0xF9400528\n"
        ".inst 0x39417508\n" ".inst 0xB9000148\n" ".inst 0x320003E8\n"
        ".inst 0xB9000948\n" ".inst 0xF9400808\n" ".inst 0x91004108\n"
        ".inst 0xF9000808\n" ".inst 0x320003E0\n" ".inst 0xD65F03C0\n"
        ".inst 0x00000000\n" ".inst 0xF9401009\n" ".inst 0xF9400129\n"
        ".inst 0xF9400808\n" ".inst 0x9100412A\n" ".inst 0xF0013CA9\n"
        ".inst 0x91258129\n" ".inst 0xEB08015F\n" ".inst 0x9A893149\n"
        ".inst 0xB940092D\n" ".inst 0xCB0A010B\n" ".inst 0xD344FD6C\n"
        ".inst 0x12000DAD\n" ".inst 0x710009BF\n" ".inst 0x54000100\n"
        ".inst 0x71001DBF\n" ".inst 0x54000281\n" ".inst 0xF9400129\n"
        ".inst 0x9100A129\n" ".inst 0xD3648D6B\n" ".inst 0x36F8026C\n"
        ".inst 0x14000004\n" ".inst 0xF9400129\n" ".inst 0xD3648D6B\n"
        ".inst 0x36F801EC\n" ".inst 0xD2607D6B\n" ".inst 0x8B8B714A\n"
        ".inst 0xEB08015F\n" ".inst 0x540001A9\n" ".inst 0x9100410B\n"
        ".inst 0xF900080B\n" ".inst 0xB900091F\n" ".inst 0xF9400808\n"
        ".inst 0xEB0A011F\n" ".inst 0x54FFFF63\n" ".inst 0x14000006\n"
        ".inst 0xAA1F03E9\n" ".inst 0xD3648D6B\n" ".inst 0x37FFFE6C\n"
        ".inst 0xCB0B03EA\n" ".inst 0x8B8A710A\n" ".inst 0xF900080A\n"
        ".inst 0xF9400528\n" ".inst 0x39417908\n" ".inst 0xB9000148\n"
        ".inst 0x320003E8\n" ".inst 0xB9000948\n" ".inst 0xF9400808\n"
        ".inst 0x91004108\n" ".inst 0xF9000808\n" ".inst 0x320003E0\n"
        ".inst 0xD65F03C0\n" ".inst 0x00000000\n" ".inst 0xF9401009\n"
        ".inst 0xF9400129\n" ".inst 0xF9400808\n" ".inst 0x9100412A\n"
        ".inst 0xF0013CA9\n" ".inst 0x91258129\n" ".inst 0xEB08015F\n"
        ".inst 0x9A893149\n" ".inst 0xB940092D\n" ".inst 0xCB0A010B\n"
        ".inst 0xD344FD6C\n" ".inst 0x12000DAD\n" ".inst 0x710009BF\n"
        ".inst 0x54000100\n" ".inst 0x71001DBF\n" ".inst 0x54000281\n"
        ".inst 0xF9400129\n" ".inst 0x9100A129\n" ".inst 0xD3648D6B\n"
        ".inst 0x36F8026C\n" ".inst 0x14000004\n" ".inst 0xF9400129\n"
        ".inst 0xD3648D6B\n" ".inst 0x36F801EC\n" ".inst 0xD2607D6B\n"
        ".inst 0x8B8B714A\n" ".inst 0xEB08015F\n" ".inst 0x540001A9\n"
        ".inst 0x9100410B\n" ".inst 0xF900080B\n" ".inst 0xB900091F\n"
        ".inst 0xF9400808\n" ".inst 0xEB0A011F\n" ".inst 0x54FFFF63\n"
        ".inst 0x14000006\n" ".inst 0xAA1F03E9\n" ".inst 0xD3648D6B\n"
        ".inst 0x37FFFE6C\n" ".inst 0xCB0B03EA\n" ".inst 0x8B8A710A\n"
        ".inst 0xF900080A\n" ".inst 0xF9400528\n" ".inst 0x39424908\n"
        ".inst 0xB9000148\n" ".inst 0x320003E8\n" ".inst 0xB9000948\n"
        ".inst 0xF9400808\n" ".inst 0x91004108\n" ".inst 0xF9000808\n"
        ".inst 0x320003E0\n" ".inst 0xD65F03C0\n" ".inst 0x00000000\n"
        ".inst 0xF9401009\n" ".inst 0xF9400129\n" ".inst 0xF9400808\n"
        ".inst 0x9100412A\n" ".inst 0xF0013CA9\n" ".inst 0x91258129\n"
        ".inst 0xEB08015F\n" ".inst 0x9A893149\n" ".inst 0xB940092D\n"
        ".inst 0xCB0A010B\n" ".inst 0xD344FD6C\n" ".inst 0x12000DAD\n"
        ".inst 0x710009BF\n" ".inst 0x54000100\n" ".inst 0x71001DBF\n"
        ".inst 0x54000281\n" ".inst 0xF9400129\n" ".inst 0x9100A129\n"
        ".inst 0xD3648D6B\n" ".inst 0x36F8026C\n" ".inst 0x14000004\n"
        ".inst 0xF9400129\n" ".inst 0xD3648D6B\n" ".inst 0x36F801EC\n"
        ".inst 0xD2607D6B\n" ".inst 0x8B8B714A\n" ".inst 0xEB08015F\n"
        ".inst 0x540001A9\n" ".inst 0x9100410B\n" ".inst 0xF900080B\n"
        ".inst 0xB900091F\n" ".inst 0xF9400808\n" ".inst 0xEB0A011F\n"
        ".inst 0x54FFFF63\n" ".inst 0x14000006\n" ".inst 0xAA1F03E9\n"
        ".inst 0xD3648D6B\n" ".inst 0x37FFFE6C\n" ".inst 0xCB0B03EA\n"
        ".inst 0x8B8A710A\n" ".inst 0xF900080A\n" ".inst 0xF9400528\n"
        ".inst 0x39424D08\n" ".inst 0xB9000148\n" ".inst 0x320003E8\n"
        ".inst 0xB9000948\n" ".inst 0xF9400808\n" ".inst 0x91004108\n"
        ".inst 0xF9000808\n" ".inst 0x320003E0\n" ".inst 0xD65F03C0\n"
        ".inst 0x00000000\n" ".inst 0xF81D0FF5\n" ".inst 0xA9014FF4\n"
        ".inst 0xA9027BFD\n" ".inst 0x910083FD\n" ".inst 0xF9401009\n"
        ".inst 0xF9400129\n" ".inst 0xF9400808\n" ".inst 0xF0013CAB\n"
        ".inst 0x9125816B\n" ".inst 0x91004129\n" ".inst 0xEB08013F\n"
        ".inst 0x9A8B312B\n" ".inst 0xB940096C\n" ".inst 0xCB090115\n"
        ".inst 0xD344FEAA\n" ".inst 0x12000D8C\n" ".inst 0xAA0003F3\n"
        ".inst 0x7100099F\n" ".inst 0x54000100\n" ".inst 0x71001D9F\n"
        ".inst 0x540001E1\n" ".inst 0xF940016B\n" ".inst 0x9100A174\n"
        ".inst 0x7100095F\n" ".inst 0x540000AA\n" ".inst 0x1400000D\n"
        ".inst 0xF9400174\n" ".inst 0x7100095F\n" ".inst 0x5400014B\n"
        ".inst 0x321F03E1\n" ".inst 0xAA1303E0\n" ".inst 0xAA1F03E2\n"
        ".inst 0x9460A578\n" ".inst 0xF9400A68\n" ".inst 0x14000006\n"
        ".inst 0xAA1F03F4\n" ".inst 0x7100095F\n" ".inst 0x54FFFF0A\n"
        ".inst 0x37F8016A\n" ".inst 0x321F7BE0\n" ".inst 0xCB1573E9\n"
        ".inst 0x8B897109\n" ".inst 0xF9000A69\n" ".inst 0xF9400688\n"
        ".inst 0x3100081F\n" ".inst 0x54000220\n" ".inst 0x8B20C908\n"
        ".inst 0xB940CD08\n" ".inst 0x14000012\n" ".inst 0xD3648EAA\n"
        ".inst 0xD2607D4A\n" ".inst 0x8B8A7129\n" ".inst 0xEB08013F\n"
        ".inst 0x540000E9\n" ".inst 0x9100410A\n" ".inst 0xF9000A6A\n"
        ".inst 0xB900091F\n" ".inst 0xF9400A68\n" ".inst 0xEB09011F\n"
        ".inst 0x54FFFF63\n" ".inst 0xF9000A69\n" ".inst 0xF9400688\n"
        ".inst 0x2959AD0A\n" ".inst 0xB940D508\n" ".inst 0x0B0A016A\n"
        ".inst 0x0B0A0108\n" ".inst 0x93407D08\n" ".inst 0xF9000128\n"
        ".inst 0x52800268\n" ".inst 0xB9000928\n" ".inst 0xF9400A68\n"
        ".inst 0x91004108\n" ".inst 0xF9000A68\n" ".inst 0xA9427BFD\n"
        ".inst 0xA9414FF4\n" ".inst 0x320003E0\n" ".inst 0xF84307F5\n"
        ".inst 0xD65F03C0\n" ".inst 0x00000000\n" ".inst 0x00000000\n"
        ".inst 0xF9401009\n" ".inst 0xF9400129\n" ".inst 0xF9400808\n"
        ".inst 0x9100412A\n" ".inst 0xF0013CA9\n" ".inst 0x91258129\n"
        ".inst 0xEB08015F\n" ".inst 0x9A893149\n" ".inst 0xB940092D\n"
        ".inst 0xCB0A010B\n" ".inst 0xD344FD6C\n" ".inst 0x12000DAD\n"
        ".inst 0x710009BF\n" ".inst 0x54000100\n" ".inst 0x71001DBF\n"
        ".inst 0x54000281\n" ".inst 0xF9400129\n" ".inst 0x9100A129\n"
        ".inst 0xD3648D6B\n" ".inst 0x36F8026C\n" ".inst 0x14000004\n"
        ".inst 0xF9400129\n" ".inst 0xD3648D6B\n" ".inst 0x36F801EC\n"
        ".inst 0xD2607D6B\n" ".inst 0x8B8B714A\n" ".inst 0xEB08015F\n"
        ".inst 0x540001A9\n" ".inst 0x9100410B\n" ".inst 0xF900080B\n"
        ".inst 0xB900091F\n" ".inst 0xF9400808\n" ".inst 0xEB0A011F\n"
        ".inst 0x54FFFF63\n" ".inst 0x14000006\n" ".inst 0xAA1F03E9\n"
        ".inst 0xD3648D6B\n" ".inst 0x37FFFE6C\n" ".inst 0xCB0B03EA\n"
        ".inst 0x8B8A710A\n" ".inst 0xF900080A\n" ".inst 0xF9400528\n"
        ".inst 0xB980D908\n" ".inst 0xF9000148\n" ".inst 0x52800268\n"
        ".inst 0xB9000948\n" ".inst 0xF9400808\n" ".inst 0x91004108\n"
        ".inst 0xF9000808\n" ".inst 0x320003E0\n" ".inst 0xD65F03C0\n"
        ".inst 0x00000000\n" ".inst 0xF81D0FF5\n" ".inst 0xA9014FF4\n"
        ".inst 0xA9027BFD\n" ".inst 0x910083FD\n" ".inst 0xF9401009\n"
        ".inst 0xF9400129\n" ".inst 0xF9400808\n" ".inst 0xF0013CAB\n"
        ".inst 0x9125816B\n" ".inst 0x91004129\n" ".inst 0xEB08013F\n"
        ".inst 0x9A8B312B\n" ".inst 0xB940096C\n" ".inst 0xCB090115\n"
        ".inst 0xD344FEAA\n" ".inst 0x12000D8C\n" ".inst 0xAA0003F3\n"
        ".inst 0x7100099F\n" ".inst 0x54000100\n" ".inst 0x71001D9F\n"
        ".inst 0x540001E1\n" ".inst 0xF940016B\n" ".inst 0x9100A174\n"
        ".inst 0x7100095F\n" ".inst 0x540000AA\n" ".inst 0x1400000D\n"
        ".inst 0xF9400174\n" ".inst 0x7100095F\n" ".inst 0x5400014B\n"
        ".inst 0x321F03E1\n" ".inst 0xAA1303E0\n" ".inst 0xAA1F03E2\n"
        ".inst 0x9460A4F4\n" ".inst 0xF9400A68\n" ".inst 0x14000006\n"
        ".inst 0xAA1F03F4\n" ".inst 0x7100095F\n" ".inst 0x54FFFF0A\n"
        ".inst 0x37F8018A\n" ".inst 0x321F7BE0\n" ".inst 0xCB1573E9\n"
        ".inst 0x8B897109\n" ".inst 0xF9000A69\n" ".inst 0xF9400688\n"
        ".inst 0x3100081F\n" ".inst 0x54000240\n" ".inst 0x8B20C908\n"
        ".inst 0xB9414D0A\n" ".inst 0xB9415908\n" ".inst 0x14000018\n"
        ".inst 0xD3648EAA\n" ".inst 0xD2607D4A\n" ".inst 0x8B8A7129\n"
        ".inst 0xEB08013F\n" ".inst 0x540000E9\n" ".inst 0x9100410A\n"
        ".inst 0xF9000A6A\n" ".inst 0xB900091F\n" ".inst 0xF9400A68\n"
        ".inst 0xEB09011F\n" ".inst 0x54FFFF63\n" ".inst 0xF9000A69\n"
        ".inst 0xF9400688\n" ".inst 0xB9414D0A\n" ".inst 0xB941510B\n"
        ".inst 0x0B0A016A\n" ".inst 0xB941590C\n" ".inst 0xB9415D0D\n"
        ".inst 0xB941550E\n" ".inst 0xB9416108\n" ".inst 0x0B0C01AB\n"
        ".inst 0x0B0A01CA\n" ".inst 0x0B0B0108\n" ".inst 0x0B0A0108\n"
        ".inst 0x92403D08\n" ".inst 0xF9000128\n" ".inst 0x52800268\n"
        ".inst 0xB9000928\n" ".inst 0xF9400A68\n" ".inst 0x91004108\n"
        ".inst 0xF9000A68\n" ".inst 0x320003E0\n" ".inst 0xA9427BFD\n"
        ".inst 0xA9414FF4\n" ".inst 0xF84307F5\n" ".inst 0xD65F03C0\n"
        ".inst 0x00000000\n" ".inst 0x00000000\n" ".inst 0xF81D0FF5\n"
        ".inst 0xA9014FF4\n" ".inst 0xA9027BFD\n" ".inst 0x910083FD\n"
        ".inst 0xF9401009\n" ".inst 0xF9400129\n" ".inst 0xF9400808\n"
        ".inst 0xF0013CAB\n" ".inst 0x9125816B\n" ".inst 0x91004129\n"
        ".inst 0xEB08013F\n" ".inst 0x9A8B312B\n" ".inst 0xB940096C\n"
        ".inst 0xCB090115\n" ".inst 0xD344FEAA\n" ".inst 0x12000D8C\n"
        ".inst 0xAA0003F3\n" ".inst 0x7100099F\n" ".inst 0x54000100\n"
        ".inst 0x71001D9F\n" ".inst 0x54000201\n" ".inst 0xF940016B\n"
        ".inst 0x9100A174\n" ".inst 0x7100095F\n" ".inst 0x540000AA\n"
        ".inst 0x1400000E\n" ".inst 0xF9400174\n" ".inst 0x7100095F\n"
        ".inst 0x5400016B\n" ".inst 0x321F03E1\n" ".inst 0xAA1303E0\n"
        ".inst 0xAA1F03E2\n" ".inst 0x9460A49C\n" ".inst 0xF9400A68\n"
        ".inst 0xAA0003E1\n" ".inst 0x14000006\n" ".inst 0xAA1F03F4\n"
        ".inst 0x7100095F\n" ".inst 0x54FFFEEA\n" ".inst 0x37F800AA\n"
        ".inst 0x321F7BE1\n" ".inst 0xCB1573E9\n" ".inst 0x8B897115\n"
        ".inst 0x1400000D\n" ".inst 0xD3648EAA\n" ".inst 0xD2607D4A\n"
        ".inst 0x8B8A7135\n" ".inst 0xEB0802BF\n" ".inst 0x540000E9\n"
        ".inst 0x91004109\n" ".inst 0xF9000A69\n" ".inst 0xB900091F\n"
        ".inst 0xF9400A68\n" ".inst 0xEB15011F\n" ".inst 0x54FFFF63\n"
        ".inst 0x321F7BE1\n" ".inst 0xF9000A75\n" ".inst 0xF9400680\n"
        ".inst 0x97964EAA\n" ".inst 0x93407C08\n" ".inst 0x320003E0\n"
        ".inst 0xF90002A8\n" ".inst 0x52800268\n" ".inst 0xB9000AA8\n"
        ".inst 0xF9400A68\n" ".inst 0x91004108\n" ".inst 0xF9000A68\n"
        ".inst 0xA9427BFD\n" ".inst 0xA9414FF4\n" ".inst 0xF84307F5\n"
        ".inst 0xD65F03C0\n" ".inst 0x00000000\n" ".inst 0xF9401009\n"
        ".inst 0xF9400129\n" ".inst 0xF9400808\n" ".inst 0x9100412A\n"
        ".inst 0xF0013CA9\n" ".inst 0x91258129\n" ".inst 0xEB08015F\n"
        ".inst 0x9A893149\n" ".inst 0xB940092D\n" ".inst 0xCB0A010B\n"
        ".inst 0xD344FD6C\n" ".inst 0x12000DAD\n" ".inst 0x710009BF\n"
        ".inst 0x54000100\n" ".inst 0x71001DBF\n" ".inst 0x54000281\n"
        ".inst 0xF9400129\n" ".inst 0x9100A129\n" ".inst 0xD3648D6B\n"
        ".inst 0x36F8026C\n" ".inst 0x14000004\n" ".inst 0xF9400129\n"
        ".inst 0xD3648D6B\n" ".inst 0x36F801EC\n" ".inst 0xD2607D6B\n"
        ".inst 0x8B8B714A\n" ".inst 0xEB08015F\n" ".inst 0x540001A9\n"
        ".inst 0x9100410B\n" ".inst 0xF900080B\n" ".inst 0xB900091F\n"
        ".inst 0xF9400808\n" ".inst 0xEB0A011F\n" ".inst 0x54FFFF63\n"
        ".inst 0x14000006\n" ".inst 0xAA1F03E9\n" ".inst 0xD3648D6B\n"
        ".inst 0x37FFFE6C\n" ".inst 0xCB0B03EA\n" ".inst 0x8B8A710A\n"
        ".inst 0xF900080A\n" ".inst 0xF9400528\n" ".inst 0x39468D08\n"
        ".inst 0xB9000148\n" ".inst 0x320003E8\n" ".inst 0xB9000948\n"
        ".inst 0xF9400808\n" ".inst 0x91004108\n" ".inst 0xF9000808\n"
        ".inst 0x320003E0\n" ".inst 0xD65F03C0\n" ".inst 0x00000000\n"
        ".inst 0xD10143FF\n" ".inst 0xF9000BF7\n" ".inst 0xA90257F6\n"
        ".inst 0xA9034FF4\n" ".inst 0xA9047BFD\n" ".inst 0x910103FD\n"
        ".inst 0xF9401009\n" ".inst 0xF9400129\n" ".inst 0xF9400808\n"
        ".inst 0xF0013CAA\n" ".inst 0x9125814A\n" ".inst 0x9100412B\n"
        ".inst 0xEB08017F\n" ".inst 0xCB0B0115\n" ".inst 0x9A8A316B\n"
        ".inst 0xB940096C\n" ".inst 0x12000D8C\n" ".inst 0xAA0003F3\n"
        ".inst 0xD344FEB6\n" ".inst 0x7100099F\n" ".inst 0x540000C0\n"
        ".inst 0x71001D9F\n" ".inst 0x540000C1\n" ".inst 0xF940016B\n"
        ".inst 0x9100A174\n" ".inst 0x14000004\n" ".inst 0xF9400174\n"
        ".inst 0x14000002\n" ".inst 0xAA1F03F4\n" ".inst 0x91008129\n"
        ".inst 0xEB08013F\n" ".inst 0x9A8A3137\n" ".inst 0xB9400AE8\n"
        ".inst 0x71000D1F\n" ".inst 0x540000E1\n" ".inst 0xB94002E8\n"
        ".inst 0x37F80176\n" ".inst 0xF9400A69\n" ".inst 0xCB1573EA\n"
        ".inst 0x8B8A7129\n" ".inst 0x14000015\n" ".inst 0x71004D1F\n"
        ".inst 0x540003A1\n" ".inst 0xF94002E8\n" ".inst 0x9E220100\n"
        ".inst 0x1E260008\n" ".inst 0x36FFFEF6\n" ".inst 0xF9401269\n"
        ".inst 0xF9400129\n" ".inst 0xD3648EAB\n" ".inst 0xF9400A6A\n"
        ".inst 0xD2607D6B\n" ".inst 0x8B8B7129\n" ".inst 0x91004129\n"
        ".inst 0x14000005\n" ".inst 0x9100414B\n" ".inst 0xF9000A6B\n"
        ".inst 0xB900095F\n" ".inst 0xF9400A6A\n" ".inst 0xEB09015F\n"
        ".inst 0x54FFFF63\n" ".inst 0xF9000A69\n" ".inst 0xF9400689\n"
        ".inst 0xB901AD28\n" ".inst 0xA9447BFD\n" ".inst 0xF9400BF7\n"
        ".inst 0xA9434FF4\n" ".inst 0x2A1F03E0\n" ".inst 0xA94257F6\n"
        ".inst 0x910143FF\n" ".inst 0xD65F03C0\n" ".inst 0x12000D08\n"
        ".inst 0x7100111F\n" ".inst 0x540002E1\n" ".inst 0xF94002E8\n"
        ".inst 0x91006100\n" ".inst 0x910003E1\n" ".inst 0x9460F247\n"
        ".inst 0xF94002E8\n" ".inst 0x39402109\n" ".inst 0x7100113F\n"
        ".inst 0x54000061\n" ".inst 0x39402D08\n" ".inst 0x14000002\n"
        ".inst 0xF9400908\n" ".inst 0x91000508\n" ".inst 0xEB08001F\n"
        ".inst 0x54000121\n" ".inst 0xF94003E9\n" ".inst 0x9E220120\n"
        ".inst 0xB9400BE8\n" ".inst 0x71004D1F\n" ".inst 0x1E26000A\n"
        ".inst 0x1A890148\n" ".inst 0x36FFF8F6\n" ".inst 0x17FFFFD0\n"
        ".inst 0x2A1F03E8\n" ".inst 0x36FFF896\n" ".inst 0x17FFFFCD\n"
        ".inst 0x00000000\n" ".inst 0xF9401009\n" ".inst 0xF9400129\n"
        ".inst 0xF9400808\n" ".inst 0x9100412A\n" ".inst 0xD0013CA9\n"
        ".inst 0x91258129\n" ".inst 0xEB08015F\n" ".inst 0x9A893149\n"
        ".inst 0xB940092D\n" ".inst 0xCB0A010B\n" ".inst 0xD344FD6C\n"
        ".inst 0x12000DAD\n" ".inst 0x710009BF\n" ".inst 0x54000100\n"
        ".inst 0x71001DBF\n" ".inst 0x54000281\n" ".inst 0xF9400129\n"
        ".inst 0x9100A129\n" ".inst 0xD3648D6B\n" ".inst 0x36F8026C\n"
        ".inst 0x14000004\n" ".inst 0xF9400129\n" ".inst 0xD3648D6B\n"
        ".inst 0x36F801EC\n" ".inst 0xD2607D6B\n" ".inst 0x8B8B714A\n"
        ".inst 0xEB08015F\n" ".inst 0x540001A9\n" ".inst 0x9100410B\n"
        ".inst 0xF900080B\n" ".inst 0xB900091F\n" ".inst 0xF9400808\n"
        ".inst 0xEB0A011F\n" ".inst 0x54FFFF63\n" ".inst 0x14000006\n"
        ".inst 0xAA1F03E9\n" ".inst 0xD3648D6B\n" ".inst 0x37FFFE6C\n"
        ".inst 0xCB0B03EA\n" ".inst 0x8B8A710A\n" ".inst 0xF900080A\n"
        ".inst 0xF9400528\n" ".inst 0x394E3108\n" ".inst 0xB9000148\n"
        ".inst 0x320003E8\n" ".inst 0xB9000948\n" ".inst 0xF9400808\n"
        ".inst 0x91004108\n" ".inst 0xF9000808\n" ".inst 0x320003E0\n"
        ".inst 0xD65F03C0\n" ".inst 0x00000000\n" ".inst 0xF9401009\n"
        ".inst 0xF9400129\n" ".inst 0xF9400808\n" ".inst 0x9100412A\n"
        ".inst 0xD0013CA9\n" ".inst 0x91258129\n" ".inst 0xEB08015F\n"
        ".inst 0x9A893149\n" ".inst 0xB940092D\n" ".inst 0xCB0A010B\n"
        ".inst 0xD344FD6C\n" ".inst 0x12000DAD\n" ".inst 0x710009BF\n"
        ".inst 0x54000100\n" ".inst 0x71001DBF\n" ".inst 0x54000281\n"
        ".inst 0xF9400129\n" ".inst 0x9100A129\n" ".inst 0xD3648D6B\n"
        ".inst 0x36F8026C\n" ".inst 0x14000004\n" ".inst 0xF9400129\n"
        ".inst 0xD3648D6B\n" ".inst 0x36F801EC\n" ".inst 0xD2607D6B\n"
        ".inst 0x8B8B714A\n" ".inst 0xEB08015F\n" ".inst 0x540001A9\n"
        ".inst 0x9100410B\n" ".inst 0xF900080B\n" ".inst 0xB900091F\n"
        ".inst 0xF9400808\n" ".inst 0xEB0A011F\n" ".inst 0x54FFFF63\n"
        ".inst 0x14000006\n" ".inst 0xAA1F03E9\n" ".inst 0xD3648D6B\n"
        ".inst 0x37FFFE6C\n" ".inst 0xCB0B03EA\n" ".inst 0x8B8A710A\n"
        ".inst 0xF900080A\n" ".inst 0xF9400528\n" ".inst 0x394EB108\n"
        ".inst 0xF9000148\n" ".inst 0x52800268\n" ".inst 0xB9000948\n"
        ".inst 0xF9400808\n" ".inst 0x91004108\n" ".inst 0xF9000808\n"
        ".inst 0x320003E0\n" ".inst 0xD65F03C0\n" ".inst 0x00000000\n"
        ".inst 0xF9401009\n" ".inst 0xF9400129\n" ".inst 0xF9400808\n"
        ".inst 0x9100412A\n" ".inst 0xD0013CA9\n" ".inst 0x91258129\n"
        ".inst 0xEB08015F\n" ".inst 0x9A893149\n" ".inst 0xB940092D\n"
        ".inst 0xCB0A010B\n" ".inst 0xD344FD6C\n" ".inst 0x12000DAD\n"
        ".inst 0x710009BF\n" ".inst 0x54000100\n" ".inst 0x71001DBF\n"
        ".inst 0x54000281\n" ".inst 0xF9400129\n" ".inst 0x9100A129\n"
        ".inst 0xD3648D6B\n" ".inst 0x36F8026C\n" ".inst 0x14000004\n"
        ".inst 0xF9400129\n" ".inst 0xD3648D6B\n" ".inst 0x36F801EC\n"
        ".inst 0xD2607D6B\n" ".inst 0x8B8B714A\n" ".inst 0xEB08015F\n"
        ".inst 0x540001A9\n" ".inst 0x9100410B\n" ".inst 0xF900080B\n"
        ".inst 0xB900091F\n" ".inst 0xF9400808\n" ".inst 0xEB0A011F\n"
        ".inst 0x54FFFF63\n" ".inst 0x14000006\n" ".inst 0xAA1F03E9\n"
        ".inst 0xD3648D6B\n" ".inst 0x37FFFE6C\n" ".inst 0xCB0B03EA\n"
        ".inst 0x8B8A710A\n" ".inst 0xF900080A\n" ".inst 0xF9400528\n"
        ".inst 0xB9436D08\n" ".inst 0xB9000148\n" ".inst 0x320007E8\n"
        ".inst 0xB9000948\n" ".inst 0xF9400808\n" ".inst 0x91004108\n"
        ".inst 0xF9000808\n" ".inst 0x320003E0\n" ".inst 0xD65F03C0\n"
        ".inst 0x00000000\n" ".inst 0xF9401009\n" ".inst 0xF9400129\n"
        ".inst 0xF9400808\n" ".inst 0x9100412A\n" ".inst 0xD0013CA9\n"
        ".inst 0x91258129\n" ".inst 0xEB08015F\n" ".inst 0x9A893149\n"
        ".inst 0xB940092D\n" ".inst 0xCB0A010B\n" ".inst 0xD344FD6C\n"
        ".inst 0x12000DAD\n" ".inst 0x710009BF\n" ".inst 0x54000100\n"
        ".inst 0x71001DBF\n" ".inst 0x54000281\n" ".inst 0xF9400129\n"
        ".inst 0x9100A129\n" ".inst 0xD3648D6B\n" ".inst 0x36F8026C\n"
        ".inst 0x14000004\n" ".inst 0xF9400129\n" ".inst 0xD3648D6B\n"
        ".inst 0x36F801EC\n" ".inst 0xD2607D6B\n" ".inst 0x8B8B714A\n"
        ".inst 0xEB08015F\n" ".inst 0x540001A9\n" ".inst 0x9100410B\n"
        ".inst 0xF900080B\n" ".inst 0xB900091F\n" ".inst 0xF9400808\n"
        ".inst 0xEB0A011F\n" ".inst 0x54FFFF63\n" ".inst 0x14000006\n"
        ".inst 0xAA1F03E9\n" ".inst 0xD3648D6B\n" ".inst 0x37FFFE6C\n"
        ".inst 0xCB0B03EA\n" ".inst 0x8B8A710A\n" ".inst 0xF900080A\n"
        ".inst 0xF9400528\n" ".inst 0xB989A108\n" ".inst 0xF9000148\n"
        ".inst 0x52800268\n" ".inst 0xB9000948\n" ".inst 0xF9400808\n"
        ".inst 0x91004108\n" ".inst 0xF9000808\n" ".inst 0x320003E0\n"
        ".inst 0xD65F03C0\n" ".inst 0x00000000\n" ".inst 0xF9401009\n"
        ".inst 0xF9400129\n" ".inst 0xF9400808\n" ".inst 0x9100412A\n"
        ".inst 0xD0013CA9\n" ".inst 0x91258129\n" ".inst 0xEB08015F\n"
        ".inst 0x9A893149\n" ".inst 0xB940092D\n" ".inst 0xCB0A010B\n"
        ".inst 0xD344FD6C\n" ".inst 0x12000DAD\n" ".inst 0x710009BF\n"
        ".inst 0x54000100\n" ".inst 0x71001DBF\n" ".inst 0x54000281\n"
        ".inst 0xF9400129\n" ".inst 0x9100A129\n" ".inst 0xD3648D6B\n"
        ".inst 0x36F8026C\n" ".inst 0x14000004\n" ".inst 0xF9400129\n"
        ".inst 0xD3648D6B\n" ".inst 0x36F801EC\n" ".inst 0xD2607D6B\n"
        ".inst 0x8B8B714A\n" ".inst 0xEB08015F\n" ".inst 0x540001A9\n"
        ".inst 0x9100410B\n" ".inst 0xF900080B\n" ".inst 0xB900091F\n"
        ".inst 0xF9400808\n" ".inst 0xEB0A011F\n" ".inst 0x54FFFF63\n"
        ".inst 0x14000006\n" ".inst 0xAA1F03E9\n" ".inst 0xD3648D6B\n"
        ".inst 0x37FFFE6C\n" ".inst 0xCB0B03EA\n" ".inst 0x8B8A710A\n"
        ".inst 0xF900080A\n" ".inst 0xF9400528\n" ".inst 0xB989AD08\n"
        ".inst 0xF9000148\n" ".inst 0x52800268\n" ".inst 0xB9000948\n"
        ".inst 0xF9400808\n" ".inst 0x91004108\n" ".inst 0xF9000808\n"
        ".inst 0x320003E0\n" ".inst 0xD65F03C0\n" ".inst 0x00000000\n"
        ".inst 0xF9401009\n" ".inst 0xF9400129\n" ".inst 0xF9400808\n"
        ".inst 0x9100412A\n" ".inst 0xD0013CA9\n" ".inst 0x91258129\n"
        ".inst 0xEB08015F\n" ".inst 0x9A893149\n" ".inst 0xB940092D\n"
        ".inst 0xCB0A010B\n" ".inst 0xD344FD6C\n" ".inst 0x12000DAD\n"
        ".inst 0x710009BF\n" ".inst 0x54000100\n" ".inst 0x71001DBF\n"
        ".inst 0x54000281\n" ".inst 0xF9400129\n" ".inst 0x9100A129\n"
        ".inst 0xD3648D6B\n" ".inst 0x36F8026C\n" ".inst 0x14000004\n"
        ".inst 0xF9400129\n" ".inst 0xD3648D6B\n" ".inst 0x36F801EC\n"
        ".inst 0xD2607D6B\n" ".inst 0x8B8B714A\n" ".inst 0xEB08015F\n"
        ".inst 0x540001A9\n" ".inst 0x9100410B\n" ".inst 0xF900080B\n"
        ".inst 0xB900091F\n" ".inst 0xF9400808\n" ".inst 0xEB0A011F\n"
        ".inst 0x54FFFF63\n" ".inst 0x14000006\n" ".inst 0xAA1F03E9\n"
        ".inst 0xD3648D6B\n" ".inst 0x37FFFE6C\n" ".inst 0xCB0B03EA\n"
        ".inst 0x8B8A710A\n" ".inst 0xF900080A\n" ".inst 0xF9400528\n"
        ".inst 0xB989B108\n" ".inst 0xF9000148\n" ".inst 0x52800268\n"
        ".inst 0xB9000948\n" ".inst 0xF9400808\n" ".inst 0x91004108\n"
        ".inst 0xF9000808\n" ".inst 0x320003E0\n" ".inst 0xD65F03C0\n"
        ".inst 0x00000000\n" ".inst 0xF9401009\n" ".inst 0xF9400129\n"
        ".inst 0xF9400808\n" ".inst 0x9100412A\n" ".inst 0xD0013CA9\n"
        ".inst 0x91258129\n" ".inst 0xEB08015F\n" ".inst 0x9A893149\n"
        ".inst 0xB940092D\n" ".inst 0xCB0A010B\n" ".inst 0xD344FD6C\n"
        ".inst 0x12000DAD\n" ".inst 0x710009BF\n" ".inst 0x54000100\n"
        ".inst 0x71001DBF\n" ".inst 0x54000281\n" ".inst 0xF9400129\n"
        ".inst 0x9100A129\n" ".inst 0xD3648D6B\n" ".inst 0x36F8026C\n"
        ".inst 0x14000004\n" ".inst 0xF9400129\n" ".inst 0xD3648D6B\n"
        ".inst 0x36F801EC\n" ".inst 0xD2607D6B\n" ".inst 0x8B8B714A\n"
        ".inst 0xEB08015F\n" ".inst 0x540001A9\n" ".inst 0x9100410B\n"
        ".inst 0xF900080B\n" ".inst 0xB900091F\n" ".inst 0xF9400808\n"
        ".inst 0xEB0A011F\n" ".inst 0x54FFFF63\n" ".inst 0x14000006\n"
        ".inst 0xAA1F03E9\n" ".inst 0xD3648D6B\n" ".inst 0x37FFFE6C\n"
        ".inst 0xCB0B03EA\n" ".inst 0x8B8A710A\n" ".inst 0xF900080A\n"
        ".inst 0xF9400528\n" ".inst 0xB949BD08\n" ".inst 0xB9000148\n"
        ".inst 0x320007E8\n" ".inst 0xB9000948\n" ".inst 0xF9400808\n"
        ".inst 0x91004108\n" ".inst 0xF9000808\n" ".inst 0x320003E0\n"
        ".inst 0xD65F03C0\n" ".inst 0x00000000\n" ".inst 0xF9401009\n"
        ".inst 0xF9400129\n" ".inst 0xF9400808\n" ".inst 0x9100412A\n"
        ".inst 0xD0013CA9\n" ".inst 0x91258129\n" ".inst 0xEB08015F\n"
        ".inst 0x9A893149\n" ".inst 0xB940092D\n" ".inst 0xCB0A010B\n"
        ".inst 0xD344FD6C\n" ".inst 0x12000DAD\n" ".inst 0x710009BF\n"
        ".inst 0x54000100\n" ".inst 0x71001DBF\n" ".inst 0x54000281\n"
        ".inst 0xF9400129\n" ".inst 0x9100A129\n" ".inst 0xD3648D6B\n"
        ".inst 0x36F8026C\n" ".inst 0x14000004\n" ".inst 0xF9400129\n"
        ".inst 0xD3648D6B\n" ".inst 0x36F801EC\n" ".inst 0xD2607D6B\n"
        ".inst 0x8B8B714A\n" ".inst 0xEB08015F\n" ".inst 0x540001A9\n"
        ".inst 0x9100410B\n" ".inst 0xF900080B\n" ".inst 0xB900091F\n"
        ".inst 0xF9400808\n" ".inst 0xEB0A011F\n" ".inst 0x54FFFF63\n"
        ".inst 0x14000006\n" ".inst 0xAA1F03E9\n" ".inst 0xD3648D6B\n"
        ".inst 0x37FFFE6C\n" ".inst 0xCB0B03EA\n" ".inst 0x8B8A710A\n"
        ".inst 0xF900080A\n" ".inst 0xF9400528\n" ".inst 0xB949C108\n"
        ".inst 0xB9000148\n" ".inst 0x320007E8\n" ".inst 0xB9000948\n"
        ".inst 0xF9400808\n" ".inst 0x91004108\n" ".inst 0xF9000808\n"
        ".inst 0x320003E0\n" ".inst 0xD65F03C0\n" ".inst 0x00000000\n"
        ".inst 0xF9401009\n" ".inst 0xF9400129\n" ".inst 0xF9400808\n"
        ".inst 0x9100412A\n" ".inst 0xD0013CA9\n" ".inst 0x91258129\n"
        ".inst 0xEB08015F\n" ".inst 0x9A893149\n" ".inst 0xB940092D\n"
        ".inst 0xCB0A010B\n" ".inst 0xD344FD6C\n" ".inst 0x12000DAD\n"
        ".inst 0x710009BF\n" ".inst 0x54000100\n" ".inst 0x71001DBF\n"
        ".inst 0x54000281\n" ".inst 0xF9400129\n" ".inst 0x9100A129\n"
        ".inst 0xD3648D6B\n" ".inst 0x36F8026C\n" ".inst 0x14000004\n"
        ".inst 0xF9400129\n" ".inst 0xD3648D6B\n" ".inst 0x36F801EC\n"
        ".inst 0xD2607D6B\n" ".inst 0x8B8B714A\n" ".inst 0xEB08015F\n"
        ".inst 0x540001A9\n" ".inst 0x9100410B\n" ".inst 0xF900080B\n"
        ".inst 0xB900091F\n" ".inst 0xF9400808\n" ".inst 0xEB0A011F\n"
        ".inst 0x54FFFF63\n" ".inst 0x14000006\n" ".inst 0xAA1F03E9\n"
        ".inst 0xD3648D6B\n" ".inst 0x37FFFE6C\n" ".inst 0xCB0B03EA\n"
        ".inst 0x8B8A710A\n" ".inst 0xF900080A\n" ".inst 0xF9400528\n"
        ".inst 0x39672908\n" ".inst 0xB9000148\n" ".inst 0x320003E8\n"
        ".inst 0xB9000948\n" ".inst 0xF9400808\n" ".inst 0x91004108\n"
        ".inst 0xF9000808\n" ".inst 0x320003E0\n" ".inst 0xD65F03C0\n"
        ".inst 0x00000000\n"
    );
}
#endif

} // namespace app::lua_bind
