#pragma once

#include "types.h"

// ============================================================================
// Weapon param sub-structs — read from FighterParamAccessor2 singleton
// Each struct is accessed via FPA2 → character param block → weapon sub-param pointer.
// All offsets confirmed from Ghidra analysis of param getter functions.
// These are binary-read params (u32 bitcast of f32), so all fields typed as u32.
// ============================================================================

// ---------------------------------------------------------------------------
// MechakoopaParams — Bowser Jr. mechakoopa weapon sub-params
// Accessed via: FPA2+0xd20 (Bowser Jr. char params) → +0x198 (mechakoopa sub-params)
// [derived: 20 getter functions at 0x71016611e0-0x7101661540]
// ---------------------------------------------------------------------------
struct MechakoopaParams {
    u32 burst_frame;               // +0x00 [derived: MECHAKOOPA_BURST_FRAME at 0x71016611e0]
    u32 count_down_frame;          // +0x04 [derived: MECHAKOOPA_COUNT_DOWN_FRAME at 0x7101661200]
    u32 hp;                        // +0x08 [derived: MECHAKOOPA_HP at 0x71016612e0]
    u8  unk_0x0c[0x4];
    u32 gravity;                   // +0x10 [derived: MECHAKOOPA_GRAVITY at 0x71016612a0]
    u32 limit_speed_y;             // +0x14 [derived: MECHAKOOPA_LIMIT_SPEED_Y at 0x7101661320]
    u32 shoot_speed_x;             // +0x18 [derived: MECHAKOOPA_SHOOT_SPEED_X at 0x7101661360]
    u32 shoot_brake;               // +0x1c [derived: MECHAKOOPA_SHOOT_BRAKE at 0x7101661380]
    u32 bound_speed_threshold;     // +0x20 [derived: MECHAKOOPA_BOUND_SPEED_THRESHOLD at 0x71016612c0]
    u32 bound_speed_x;             // +0x24 [derived: MECHAKOOPA_BOUND_SPEED_X at 0x71016613a0]
    u32 bound_speed_y;             // +0x28 [derived: MECHAKOOPA_BOUND_SPEED_Y at 0x71016613c0]
    u32 bound_brake;               // +0x2c [derived: MECHAKOOPA_BOUND_BRAKE at 0x71016613e0]
    u32 speed_x;                   // +0x30 [derived: MECHAKOOPA_SPEED_X at 0x7101661300]
    u32 turn_num;                  // +0x34 [derived: MECHAKOOPA_TURN_NUM at 0x7101661400]
    u32 hop_speed_x;               // +0x38 [derived: MECHAKOOPA_HOP_SPEED_X at 0x7101661260]
    u32 hop_speed_y;               // +0x3c [derived: MECHAKOOPA_HOP_SPEED_Y at 0x7101661280]
    u32 hop_burst_frame;           // +0x40 [derived: MECHAKOOPA_HOP_BURST_FRAME at 0x7101661220]
    u32 dead_burst_frame;          // +0x44 [derived: MECHAKOOPA_DEAD_BURST_FRAME at 0x7101661420]
    u32 hop_lost_frame;            // +0x48 [derived: MECHAKOOPA_HOP_LOST_FRAME at 0x7101661240]
    u32 stop_speed_mul;            // +0x4c [derived: MECHAKOOPA_STOP_SPEED_MUL at 0x7101661520]
    u32 stop_brake;                // +0x50 [derived: MECHAKOOPA_STOP_BRAKE at 0x7101661540]
};

// ---------------------------------------------------------------------------
// PeachDaikonParams — Peach/Daisy peachdaikon weapon sub-params
// Accessed via: FPA2+0x348 (Peach) or FPA2+0x380 (Daisy) → +0x158
// [derived: 16 getter functions at 0x7101668c90-0x7101668e70]
// ---------------------------------------------------------------------------
struct PeachDaikonParams {
    u8  unk_0x00[0x20];
    u32 daikon_1_power;            // +0x20 [derived: PEACH_PEACHDAIKON_DAIKON_1_POWER at 0x7101668d90]
    u32 daikon_2_power;            // +0x24 [derived: at 0x7101668db0]
    u32 daikon_3_power;            // +0x28 [derived: at 0x7101668dd0]
    u32 daikon_4_power;            // +0x2c [derived: at 0x7101668df0]
    u32 daikon_5_power;            // +0x30 [derived: at 0x7101668e10]
    u32 daikon_6_power;            // +0x34 [derived: at 0x7101668e30]
    u32 daikon_7_power;            // +0x38 [derived: at 0x7101668e50]
    u32 daikon_8_power;            // +0x3c [derived: at 0x7101668e70]
    u32 daikon_1_prob;             // +0x40 [derived: PEACH_PEACHDAIKON_DAIKON_1_PROB at 0x7101668c90]
    u32 daikon_2_prob;             // +0x44 [derived: at 0x7101668cb0]
    u32 daikon_3_prob;             // +0x48 [derived: at 0x7101668cd0]
    u32 daikon_4_prob;             // +0x4c [derived: at 0x7101668cf0]
    u32 daikon_5_prob;             // +0x50 [derived: at 0x7101668d10]
    u32 daikon_6_prob;             // +0x54 [derived: at 0x7101668d30]
    u32 daikon_7_prob;             // +0x58 [derived: at 0x7101668d50]
    u32 daikon_8_prob;             // +0x5c [derived: at 0x7101668d70]
};

// ---------------------------------------------------------------------------
// DollParams — Mr. Game & Watch doll weapon sub-params
// Accessed via: FPA2+0xc08 → +0x178
// [derived: 15 getter functions at 0x710165c3d0-0x710165c630]
// ---------------------------------------------------------------------------
struct DollParams {
    u32 speed_y;                   // +0x00 [derived: DOLL_SPEED_Y at 0x710165c510]
    u8  unk_0x04[0x4];
    u32 rot_speed_z;               // +0x08 [derived: DOLL_ROT_SPEED_Z at 0x710165c530]
    u32 reaction_mul;              // +0x0c [derived: DOLL_REACTION_MUL at 0x710165c3f0]
    u32 smash_max_speed_x;         // +0x10 [derived: DOLL_SMASH_MAX_SPEED_X at 0x710165c450]
    u32 smash_max_speed_y;         // +0x14 [derived: DOLL_SMASH_MAX_SPEED_Y at 0x710165c470]
    u8  unk_0x18[0x8];
    u32 smash_accel_y;             // +0x20 [derived: DOLL_SMASH_ACCEL_Y at 0x710165c430]
    u32 rot_speed_min;             // +0x24 [derived: DOLL_ROT_SPEED_MIN at 0x710165c4f0]
    u32 rot_speed_max;             // +0x28 [derived: DOLL_ROT_SPEED_MAX at 0x710165c4d0]
    u32 power_min;                 // +0x2c [derived: DOLL_POWER_MIN at 0x710165c4b0]
    u32 power_max;                 // +0x30 [derived: DOLL_POWER_MAX at 0x710165c490]
    u32 life;                      // +0x34 [derived: DOLL_LIFE at 0x710165c3d0]
    u32 life_dec_mul;              // +0x38 [derived: DOLL_LIFE_DEC_MUL at 0x710165c410]
    u32 min_degree_y;              // +0x3c [derived: DOLL_MIN_DEGREE_Y at 0x710165c630]
    u32 max_degree_y;              // +0x40 [derived: DOLL_MAX_DEGREE_Y at 0x710165c610]
    u32 rot_z_ratio;               // +0x44 [derived: DOLL_ROT_Z_RATIO at 0x710165c550]
};

// ---------------------------------------------------------------------------
// DollShapeParams — separate sub-struct for doll shape type
// Accessed via: FPA2+0xc08 → +0x1c0
// [derived: DOLL_SHAPE_TYPE at 0x710165c5f0]
// ---------------------------------------------------------------------------
struct DollShapeParams {
    u32 shape_type;                // +0x00 [derived: DOLL_SHAPE_TYPE at 0x710165c5f0]
};

// ---------------------------------------------------------------------------
// ExplosionBombParams — Link remote bomb weapon sub-params
// Accessed via: FPA2+0x3f0 → +0x108
// [derived: 14 getter functions at 0x710165d2c0-0x710165d460]
// ---------------------------------------------------------------------------
struct ExplosionBombParams {
    u32 gravity;                   // +0x00 [derived: EXPLOSIONBOMB_GRAVITY at 0x710165d2c0]
    u32 limit_gravity;             // +0x04 [derived: EXPLOSIONBOMB_LIMIT_GRAVITY at 0x710165d2e0]
    u32 hop_speed_mul_x;           // +0x08 [derived: EXPLOSIONBOMB_HOP_SPEED_MUL_X at 0x710165d300]
    u32 hop_speed_y;               // +0x0c [derived: EXPLOSIONBOMB_HOP_SPEED_Y at 0x710165d320]
    u32 bound_speed_mul_x;         // +0x10 [derived: EXPLOSIONBOMB_BOUND_SPEED_MUL_X at 0x710165d360]
    u32 bound_speed_mul_y;         // +0x14 [derived: EXPLOSIONBOMB_BOUND_SPEED_MUL_Y at 0x710165d380]
    u32 bound_num;                 // +0x18 [derived: EXPLOSIONBOMB_BOUND_NUM at 0x710165d340]
    u32 ignition_frame;            // +0x1c [derived: EXPLOSIONBOMB_IGNITION_FRAME at 0x710165d3a0]
    u32 wire_speed_x;              // +0x20 [derived: EXPLOSIONBOMB_WIRE_SPEED_X at 0x710165d3c0]
    u32 wire_speed_y;              // +0x24 [derived: EXPLOSIONBOMB_WIRE_SPEED_Y at 0x710165d3e0]
    u32 wire_gravity;              // +0x28 [derived: EXPLOSIONBOMB_WIRE_GRAVITY at 0x710165d400]
    u32 wire_bound_mul_y;          // +0x2c [derived: EXPLOSIONBOMB_WIRE_BOUND_MUL_Y at 0x710165d420]
    u32 burst_frame;               // +0x30 [derived: EXPLOSIONBOMB_BURST_FRAME at 0x710165d440]
    u8  unk_0x34[0x4];
    u32 life_misfire;              // +0x38 [derived: EXPLOSIONBOMB_LIFE_MISFIRE at 0x710165d460]
};

// ---------------------------------------------------------------------------
// HolywaterParams — Simon/Richter holywater weapon sub-params
// Accessed via: FPA2+0xf18 (Simon) or FPA2+0xf50 (Richter) → +0x240
// [derived: 3 getter functions at 0x7101670dd0-0x7101670e30]
// ---------------------------------------------------------------------------
struct HolywaterParams {
    u8  unk_0x00[0x18];
    u32 reflect_shield_gravity_accel;     // +0x18 [derived: at 0x7101670dd0]
    u32 reflect_shield_gravity_accel_max; // +0x1c [derived: at 0x7101670e00]
    u32 reflect_shield_rot_speed;         // +0x20 [derived: at 0x7101670e30]
};

// ---------------------------------------------------------------------------
// LinkArrowParams — Link arrow item sub-params
// Accessed via: FPA2+0xe0 → +0x120
// [derived: 2 getter functions at 0x710165eb30-0x710165eb50]
// ---------------------------------------------------------------------------
struct LinkArrowParams {
    u8  unk_0x00[0x2c];
    u32 item_life;                 // +0x2c [derived: LINKARROW_ITEM_LIFE at 0x710165eb30]
    u32 item_throw_degree;         // +0x30 [derived: LINKARROW_ITEM_THROW_DEGREE at 0x710165eb50]
};
