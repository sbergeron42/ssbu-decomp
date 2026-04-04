#pragma once

#include "types.h"

namespace app {

struct FighterInformationData {
    u8    pad_0x00[0x38];
    f32   hp_base;                           // +0x38
    f32   hp_temp;                           // +0x3C
    u8    pad_0x40[0x11];
    u8    fighter_color;                     // +0x51
    u8    pad_0x52[0x07];
    bool  rabbit_cap;                        // +0x59
    bool  reflector;                         // +0x5A
    bool  superleaf;                         // +0x5B
    bool  rocketbelt;                        // +0x5C
    bool  screw;                             // +0x5D
    bool  backshield;                        // +0x5E
    u8    pad_0x5F[0x33];
    bool  operation_cpu;                     // +0x92
    bool  no_change_hp;                      // +0x93
    u8    pad_0x94[0x38];
    s32   dead_count[3];                     // +0xCC
    u32   stock_count;                       // +0xD8
    u8    pad_0xDC[0x70];
    s32   suicide_count_a[3];                // +0x14C
    s32   suicide_count_b[3];                // +0x158
    u8    pad_0x164[0x3F];
    bool  last_dead_suicide;                 // +0x1A3
    u8    pad_0x1A4[0x08];
    f32   add_rebirth_wait_frame;            // +0x1AC
    u8    pad_0x1B0[0x1BC];
    f32   gravity;                           // +0x36C
    u8    pad_0x370[0x1C];
    bool  on_rebirth;                        // +0x38C
    u8    pad_0x38D[0x1F];
    u8    fighter_category;                  // +0x3AC
    u8    pad_0x3AD[0x5F3];
    u32   summon_boss_id;                    // +0x9A0
    u8    pad_0x9A4[0x08];
    u32   summon_bomb_ready_frame;           // +0x9AC
    u32   summon_pre_bomb_effect_frame;      // +0x9B0
    u8    pad_0x9B4[0x08];
    f32   summon_suicide_bomb_attack_mul;    // +0x9BC
    f32   summon_suicide_bomb_reaction_mul;  // +0x9C0
    u8    pad_0x9C4[0x06];
    bool  battle_event_stick_reverse;        // +0x9CA
};

struct FighterInformation {
    void**                vtable;            // +0x0
    FighterInformationData* data;            // +0x8
};

} // namespace app
