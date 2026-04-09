#pragma once

#include "types.h"

namespace app {

// All field names derived from .dynsym FighterInformation__*_impl functions.
// Access pattern: fi->vtable at +0x0, fi->data at +0x8; impl reads data+OFFSET.
struct FighterInformationData {
    u8    pad_0x00[0x38];
    f32   hp_base;                           // +0x38 [derived: hit_point_impl (.dynsym) reads +0x38 as base HP; hit_point_max_impl returns +0x38 alone when include_temp=true]
    f32   hp_temp;                           // +0x3C [derived: hit_point_impl (.dynsym) adds +0x3C to hp_base; hit_point_max_impl conditionally adds +0x3C]
    u8    pad_0x40[0x11];
    u8    fighter_color;                     // +0x51 [derived: fighter_color_impl (.dynsym) reads +0x51 as u8]
    u8    pad_0x52[0x07];
    bool  rabbit_cap;                        // +0x59 [derived: is_rabbit_cap_impl (.dynsym) reads +0x59 as bool]
    bool  reflector;                         // +0x5A [derived: is_reflector_impl (.dynsym) reads +0x5A as bool]
    bool  superleaf;                         // +0x5B [derived: is_superleaf_impl (.dynsym) reads +0x5B as bool]
    bool  rocketbelt;                        // +0x5C [derived: is_rocketbelt_impl (.dynsym) reads +0x5C as bool]
    bool  screw;                             // +0x5D [derived: is_screw_impl (.dynsym) reads +0x5D as bool]
    bool  backshield;                        // +0x5E [derived: is_backshield_impl (.dynsym) reads +0x5E as bool]
    u8    pad_0x5F[0x0F];
    u8    dead_up_force_crush;               // +0x6E [derived: sv_information::is_dead_up_force_crush reads +0x6E as u8]
    u8    pad_0x6F[0x0D];
    u32   star_fall_prob;                    // +0x7C [derived: sv_fighter_util::get_dead_up_star_fall_prob reads +0x7C as u32]
    u8    pad_0x80[0x12];
    bool  operation_cpu;                     // +0x92 [derived: is_operation_cpu_impl (.dynsym) reads +0x92 as bool]
    bool  no_change_hp;                      // +0x93 [derived: get_no_change_hp_impl (.dynsym) reads +0x93 as bool]
    u8    pad_0x94[0x38];
    s32   dead_count[3];                     // +0xCC [derived: dead_count_impl (.dynsym) indexes +0xCC with index*4; index=-2 sums all 3]
    u32   stock_count;                       // +0xD8 [derived: stock_count_impl (.dynsym) reads +0xD8 as u32]
    u8    pad_0xDC[0x70];
    s32   suicide_count_a[3];                // +0x14C [derived: suicide_count_impl (.dynsym) reads +0x14C with index*4, adds to suicide_count_b]
    s32   suicide_count_b[3];                // +0x158 [derived: suicide_count_impl (.dynsym) reads +0x158 with index*4, summed with suicide_count_a]
    u8    pad_0x164[0x3F];
    bool  last_dead_suicide;                 // +0x1A3 [derived: is_last_dead_suicide_impl (.dynsym) reads +0x1A3 as bool]
    u8    pad_0x1A4[0x08];
    f32   add_rebirth_wait_frame;            // +0x1AC [derived: set_add_rebirth_wait_frame_impl (.dynsym) writes +0x1AC as f32]
    u8    pad_0x1B0[0x1BC];
    f32   gravity;                           // +0x36C [derived: gravity_impl (.dynsym) reads +0x36C as f32]
    u32   handi;                              // +0x370 [derived: sv_information::owner_handi reads +0x370 as u32]
    u8    pad_0x374[0x10];
    u32   sleep_time_mul;                    // +0x384 [derived: sv_information::sleep_time_mul reads +0x384 as u32]
    u8    pad_0x388[0x04];
    bool  on_rebirth;                        // +0x38C [derived: is_on_rebirth_impl (.dynsym) reads +0x38C as bool]
    u8    pad_0x38D[0x1F];
    u8    fighter_category;                  // +0x3AC [derived: fighter_category_impl (.dynsym) reads +0x3AC as u8]
    u8    pad_0x3AD[0x5F3];
    u32   summon_boss_id;                    // +0x9A0 [derived: summon_boss_id_impl (.dynsym) reads +0x9A0 as u32]
    u8    pad_0x9A4[0x08];
    u32   summon_bomb_ready_frame;           // +0x9AC [derived: summon_bomb_ready_frame_impl (.dynsym) reads +0x9AC as u32]
    u32   summon_pre_bomb_effect_frame;      // +0x9B0 [derived: summon_pre_bomb_effect_frame_impl (.dynsym) reads +0x9B0 as u32]
    u8    pad_0x9B4[0x08];
    f32   summon_suicide_bomb_attack_mul;    // +0x9BC [derived: summon_suicide_bomb_attack_mul_impl (.dynsym) reads +0x9BC as f32]
    f32   summon_suicide_bomb_reaction_mul;  // +0x9C0 [derived: summon_suicide_bomb_reaction_mul_impl (.dynsym) reads +0x9C0 as f32]
    u8    pad_0x9C4[0x06];
    bool  battle_event_stick_reverse;        // +0x9CA [derived: is_battle_event_stick_reverse_impl (.dynsym) reads +0x9CA as bool]
};

struct FighterInformation {
    void**                vtable;            // +0x0 [derived: hit_point_impl (.dynsym) loads vtable from fi+0, calls vtable[0x20/8]]
    FighterInformationData* data;            // +0x8 [derived: all FighterInformation__*_impl (.dynsym) dereference fi+8 to reach data fields]
};

} // namespace app
