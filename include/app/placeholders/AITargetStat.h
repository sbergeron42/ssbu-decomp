#pragma once

#include "types.h"

// AITargetStat — resolved target state from FUN_7100314030.
// Contains status kind and flag fields used by check_target_stat_* functions.
// [derived: all app::ai::check_target_stat_* resolve target via
//  FUN_7100314030(FighterAIManager, ctx+0xc50) and read fields from the result]
struct AITargetStat {
    u8  unk_0x00[0x55];
    u8  final_flags;        // +0x55 [derived: check_target_stat_final checks (flags & 3) != 0;
                            //         is_valid_target checks (flags & 8) == 0]
    u8  unk_0x56[0x1E];
    s32 status_kind;        // +0x74 [derived: check_target_stat_down/fall_sp/piyo_l/dragoon/
                            //         cliff/cliff_act/catch/damage/guard/escape/rebirth compare this]
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
