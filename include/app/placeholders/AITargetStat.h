#pragma once

#include "types.h"

// Floor/ground collision data attached to AITargetStat.
// [derived: check_target_over_ground reads flags_0x5e from *(target->+0xd0)]
struct AITargetFloorData {
    u8 unk_0x00[0x5e];
    u8 flags_0x5e;          // +0x5e [derived: check_target_over_ground reads bit 1]
};

// AITargetStat — resolved target state from aiGetTargetById_7100314030.
// Contains status kind and flag fields used by check_target_stat_* functions.
// [derived: all app::ai::check_target_stat_* resolve target via
//  aiGetTargetById_7100314030(FighterAIManager, ctx+0xc50) and read fields from the result]
//
// NOTE: This struct mirrors FighterAIState in layout. Field names here match the
// target_* / check_target_stat_* naming convention in .dynsym to keep the
// one-to-one mapping clear; do not consolidate with FighterAIState without
// renaming all call sites.
struct AITargetStat {
    u8  unk_0x00[0x10];
    void* battle_object_id_holder;  // +0x10 [derived: target_id reads *(this+0x10)+8 as entry_id]
    u8  unk_0x18[0x8];
    void* fighter_ptr;      // +0x20 [derived: target_attack_start_frame reads +0x988 from this,
                            //         target_width reads +0xb2c, target_range_middle reads +0xab8; null-checked]
    s32 fighter_kind;       // +0x28 [derived: target_fighter_kind reads this]
    u8  unk_0x2c[0x28];
    u8  flags_0x54;         // +0x54 [derived: check_target_over_ground reads +0x54 as u32 and tests bits 0, 1]
    u8  final_flags;        // +0x55 [derived: check_target_stat_final checks (flags & 3) != 0;
                            //         is_valid_target checks (flags & 8) == 0;
                            //         check_target_stat_invincible_l tests bit 5]
    u8  unk_0x56[0x3];
    u8  flags_0x59;         // +0x59 [derived: target_jump_rest_available tests bit 5]
    u8  unk_0x5a[0x4];
    u8  flags_0x5e;         // +0x5e [derived: check_target_stat_invincible_l tests bit 4]
    u8  unk_0x5f[0x9];
    u8  flags_0x68;         // +0x68 [derived: target_jump_rest_available tests bits 0, 2]
    u8  unk_0x69[0xb];
    s32 status_kind;        // +0x74 [derived: check_target_stat_down/fall_sp/piyo_l/dragoon/
                            //         cliff/cliff_act/catch/damage/guard/escape/rebirth compare this;
                            //         target_jump_rest_available checks == 0x10]
    u8  unk_0x78[0x54];
    u16 jump_rest;          // +0xcc [derived: target_jump_rest_available returns this]
    u8  unk_0xce[0x2];
    AITargetFloorData* floor_data;  // +0xd0 [derived: is_target_on_same_floor compares this;
                                    //         check_target_over_ground reads flags_0x5e through this]
    u8  unk_0xd8[0x44];
    s32 invinc_counter;     // +0x11c [derived: check_target_stat_invincible_l checks > 0]
    u8  unk_0x120[0xd4];
    s32 copy_fighter_kind;  // +0x1f4 [derived: target_copy_fighter_kind reads as s32]
    u8  unk_0x1f8[0x6c];
    f32 hit_collision_rect[4];  // +0x264 [derived: target_hit_collision_rect returns 16B NEON vector]
};

// AIAttackData — resolved attack entry from FUN_710033c510.
// Contains attack bounding rect coordinates.
// [derived: app::ai::attack_data_x0/x1/y0/y1 call FUN_710033c510(handle, hash40)
//  and read f32 fields from the result. Returns in s0 register (float).]
struct AIAttackData {
    u8  unk_0x00[0x18];
    f32 x0;                 // +0x18 [derived: attack_data_x0 reads this]
    f32 x1;                 // +0x1c [derived: attack_data_x1 reads this]
    f32 y0;                 // +0x20 [derived: attack_data_y0 reads this]
    f32 y1;                 // +0x24 [derived: attack_data_y1 reads this]
};
