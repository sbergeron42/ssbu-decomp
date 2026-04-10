#pragma once
#include "types.h"

// ============================================================================
// FighterAI struct hierarchy — placeholder types for AI decision system
// Created from binary evidence across ~40 app::ai::* / app::ai_param::* functions.
//
// Access pattern: lua_State* L → *(u64*)(L - 8) = FighterAI*
//   ctx->state (at +0x168) = FighterAIState (cached per-frame fighter snapshot)
//   *(*(ctx + 0x170)) = AIAnalyst (status history tracking)
//
// IMPORTANT: These are PLACEHOLDER structs. Field names are provisional.
// See [derived:] tags for binary evidence chain.
// ============================================================================

// Forward declarations
struct FighterAI;
struct FighterAIState;
struct AIAnalyst;
struct AIFloorCollisionData;
struct AIDeadZone;
struct FighterAIManager;
struct AIGoalNavNode;
struct AIGoalFloorData;
struct AIGoalState;

// ---------------------------------------------------------------------------
// AIGoalNavNode — navigation node in goal path
// Accessed via: AIGoalFloorData->nav_node (+0x60)
// Size: >= 0x2C bytes
// ---------------------------------------------------------------------------
struct AIGoalNavNode {
    u8 unk_0x00[0x28];
    s32 nav_id;                // +0x28 [derived: check_over_goal compares with goal_check_a]
};

// ---------------------------------------------------------------------------
// AIGoalFloorData — floor data associated with navigation goal
// Accessed via: AIGoalState->floor (+0xd0)
// Size: >= 0x6C bytes
// ---------------------------------------------------------------------------
struct AIGoalFloorData {
    u8 unk_0x00[0x60];
    AIGoalNavNode* nav_node;   // +0x60 [derived: check_over_goal loads and null-checks this]
    s32 floor_id;              // +0x68 [derived: check_over_goal compares with goal_check_b]
};

// ---------------------------------------------------------------------------
// AIGoalState — goal navigation state (at FighterAI+0x188)
// Accessed via: FighterAI->sub_0x188, then deref
// Size: >= 0xDC bytes
// ---------------------------------------------------------------------------
struct AIGoalState {
    u8 unk_0x00[0xd0];
    AIGoalFloorData* floor;    // +0xd0 [derived: check_over_goal loads through this]
    s32 goal_state;            // +0xd8 [derived: check_over_goal checks == 1]
};

// ---------------------------------------------------------------------------
// AIFloorCollisionData — ground collision rect the AI uses for floor queries
// Accessed via: FighterAIState->floor_data (+0xd0)
// Size: >= 0x60 bytes (from largest known offset +0x5e)
// ---------------------------------------------------------------------------
struct AIFloorCollisionData {
    u8 unk_0x00[0x10];
    f32 movement[4];           // +0x10 [derived: floor_moves returns 16B from here]
    f32 left_edge;             // +0x20 [derived: floor_width = fabsf(right - left)]
    u8 unk_0x24[0xC];
    f32 right_edge;            // +0x30 [derived: floor_width, floor_center use this]
    u8 unk_0x34[0x2A];
    u8 flags_0x5e;             // +0x5e [derived: check_over_ground reads bit 1]
};

// ---------------------------------------------------------------------------
// FighterAIState — per-frame cached snapshot of fighter state
// Accessed via: FighterAI->state (+0x168)
// Size: >= 0x278 bytes
// Contains: identity, status, motion, position, combat stats, AI params
// ---------------------------------------------------------------------------
struct FighterAIState {
    u8 unk_0x00[0x10];
    void* accessor_chain;      // +0x10 [derived: escape_air_slide chain starts here]
    u8 unk_0x18[0x10];
    u32 fighter_kind;          // +0x28 [derived: app::ai::fighter_kind reads this]
    u32 status_kind;           // +0x2c [derived: app::ai::status_kind reads this]
    u32 prev_status_kind;      // +0x30 [derived: app::ai::prev_status_kind reads this]
    u8 unk_0x34[0x4];
    u64 motion_kind;           // +0x38 [derived: app::ai::motion_kind reads as u64 hash]
    u8 unk_0x40[0x8];
    u32 motion_frame;          // +0x48 [derived: app::ai::motion_frame reads this]
    u32 motion_cancel_frame;   // +0x4c [derived: app::ai::motion_cancel_frame reads this]
    u8 unk_0x50[0x4];
    u32 stat_flags;            // +0x54 [derived: check_stat_air reads bit 0; check_over_ground reads bits 0,1]
    u8 unk_0x58;
    u8 flags_0x59;             // +0x59 [derived: jump_rest_available reads bit 5]
    u8 unk_0x5a[0xE];
    u8 flags_0x68;             // +0x68 [derived: jump_rest_available reads bits 0,2]
    u8 unk_0x69[0xB];
    u32 uniq_stat;             // +0x74 [derived: app::ai::uniq_stat; check_over_ground checks 6/7]
    u8 unk_0x78[0x8];
    f32 pos_x;                 // +0x80 [derived: floor_lr, lr_to_target, distance_to_target (lo 32)]
    f32 pos_y;                 // +0x84 [derived: distance_to_target reads (hi 32) as pos_y]
    u8 unk_0x88[0x3C];
    f32 lr;                    // +0xc4 [derived: app::ai::lr reads this; lr_to_target fallback]
    u8 unk_0xc8[0x4];
    u16 jump_rest;             // +0xcc [derived: jump_rest_available returns this]
    u8 unk_0xce[0x2];
    AIFloorCollisionData* floor_data;  // +0xd0 [derived: floor_width, floor_center deref this]
    u8 unk_0xd8[0x8];
    u32 damage;                // +0xe0 [derived: app::ai::damage reads this]
    u32 hp;                    // +0xe4 [derived: app::ai::hp reads this]
    f32 shield_hp;             // +0xe8 [derived: shield_rate computes e8/ec]
    f32 shield_max;            // +0xec [derived: shield_rate computes e8/ec]
    u32 dangerzone_index;      // +0xf0 [derived: check_line_segment reads this]
    s32 player_index;          // +0xf4 [derived: is_1on1 indexes mgr array by this]
    u8 unk_0xf8[0x34];
    u32 current_attack_cancel_frame;  // +0x12c [derived: 300 decimal, app::ai::current_attack_cancel_frame]
    u32 attack_phase;          // +0x130 [derived: app::ai::attack_phase reads this]
    u8 unk_0x134[0xC0];
    u32 copy_fighter_kind;     // +0x1f4 [derived: 500 decimal, app::ai::copy_fighter_kind]
    u8 unk_0x1f8[0x4];
    f32 air_length_scale;      // +0x1fc [derived: air_length multiplies by this]
    f32 air_high_scale;        // +0x200 [derived: air_high multiplies by this]
    u8 unk_0x204[0x2C];
    f32 escape_air_slide_scale;  // +0x230 [derived: escape_air_slide_move_distance multiplies by this]
    u32 escape_air_cancel_frame; // +0x234 [derived: app::ai_param::escape_air_cancel_frame]
    u8 unk_0x238[0x8];
    s32 fighter_kind_index;    // +0x240 [derived: sp_u_high, sp_u_length index by this * 4]
    u8 unk_0x244[0x18];
    u32 stop_frame;            // +0x25c [derived: app::ai::stop_frame reads this]
    u8 unk_0x260[0x14];
    s32 predict_landing_frame; // +0x274 [derived: predict_landing_frame reads as s32, scvtf]
};

// ---------------------------------------------------------------------------
// AIAnalyst — tracks status history for opponent analysis
// Accessed via: **(ctx + 0x170) (double-deref)
// Size: >= 0x20 bytes
// ---------------------------------------------------------------------------
struct AIAnalyst {
    u8 unk_0x00[0x10];
    u32 status_prev;           // +0x10 [derived: app::analyst::status_prev reads this]
    u32 status_count;          // +0x14 [derived: app::analyst::status_count reads this]
    u8 unk_0x18[0x4];
    u32 chanced_frame;         // +0x1c [derived: app::analyst::chanced_frame reads this]
};

// ---------------------------------------------------------------------------
// AIDeadZone — blast zone boundaries for AI
// Accessed via: FighterAIManager->cam_bounds (+0xc8)
// Size: >= 0x18 bytes
// ---------------------------------------------------------------------------
struct AIDeadZone {
    u8 unk_0x00[0x8];
    f32 dead_left;             // +0x08 [derived: app::ai_camera::dead_left]
    f32 dead_right;            // +0x0c [derived: app::ai_camera::dead_right]
    f32 dead_top;              // +0x10 [derived: app::ai_camera::dead_top]
    f32 dead_bottom;           // +0x14 [derived: app::ai_camera::dead_bottom]
};

// ---------------------------------------------------------------------------
// FighterAIManager — singleton managing all fighter AIs
// Accessed via: DAT_71052b5fd8
// Size: >= 0x158 bytes
// ---------------------------------------------------------------------------
struct FighterAIManager {
    u8 unk_0x00[0xc0];
    void* dangerzone_array;    // +0xc0 [derived: width, check_line_segment read through this]
    AIDeadZone* cam_bounds;    // +0xc8 [derived: dead_top/bottom/left/right read through this]
    u8 unk_0xd0[0x80];
    u32 current_stage_id;      // +0x150 [derived: app::ai_stage::current_id reads this]
    u8 unk_0x154[0x18];
    s32 player_count;          // +0x16c [derived: is_1on1 checks == 2]
    u8 unk_0x170[0x20];
    s32 player_alive[8];       // +0x190 (400 decimal) [derived: is_1on1 indexes by player_index]
};

// ---------------------------------------------------------------------------
// FighterAI — root AI context object for one fighter
// Accessed via: *(u64*)(lua_State - 8)
// Size: >= 0xc80 bytes (from largest known offset 0xc7c + 2)
//
// Contains: mode control, state snapshot, action system, param tables,
//           input state, target tracking, return logic
// ---------------------------------------------------------------------------
struct FighterAI {
    void* mode_ptr;            // +0x00 [derived: change_mode_action double-derefs *(*(ctx))]
    u8 unk_0x08[0x158];
    u32 parent_entry_id;       // +0x160 [derived: parent_pos_y reads this, masks &7 for entry index]
    u8 unk_0x164[0x4];
    FighterAIState* state;     // +0x168 [derived: all AI_STATE macro accesses go through this]
    void** analyst_ptr;        // +0x170 [derived: status_prev does *(*(ctx+0x170))+0x10]
    u8 unk_0x178[0x8];
    // +0x180: action sub-object base [derived: change_action, check_over_ground_distance_current_lr]
    u8 action_base[0x8];       // +0x180 [derived: FUN_71002edd30(ctx+0x180, ...)]
    void* sub_0x188;           // +0x188 [derived: check_over_goal reads +0xd0/+0xd8 from *this]
    u8 unk_0x190[0x8];
    u16 action_id;             // +0x198 [derived: act_id reads this; set_action_id_none saves/clears]
    u16 action_id_prev;        // +0x19a [derived: set_action_id_none copies current here]
    u8 unk_0x19c[0xD4];
    f32 goal_pos[4];           // +0x270 [derived: goal_pos returns 16B Vector4f from here]
    u8 unk_0x280[0x28];
    s32 goal_check_a;          // +0x2a8 [derived: check_over_goal compares this]
    s32 goal_check_b;          // +0x2ac [derived: check_over_goal compares this]
    u8 unk_0x2b0[0xC];
    s32 auto_stop;             // +0x2bc [derived: set_auto_stop writes here (700 decimal)]
    u8 unk_0x2c0[0x3C];
    u32 update_count;          // +0x2fc [derived: update_count reads; is_update_count_odd checks %3]
    u8 unk_0x300[0x7D0];

    // ---- Per-fighter indexed param tables (indexed by state->fighter_kind_index) ----
    // Each array has 4 entries (gap between consecutive = 0x10 = 4 floats)
    f32 sp_u_high[4];         // +0xad0 [derived: app::ai_param::sp_u_high]
    f32 sp_u_length[4];       // +0xae0 [derived: app::ai_param::sp_u_length]
    u8 unk_0xaf0[0x14];
    f32 air_high_base;         // +0xb04 [derived: air_high reads this (non-indexed)]
    f32 air_length_base;       // +0xb08 [derived: air_length reads this (non-indexed)]
    u8 unk_0xb0c[0x28];
    f32 return_sp_u_cliff_x[4]; // +0xb34 [derived: app::ai_param::return_sp_u_cliff_x]
    f32 return_sp_u_cliff_y[4]; // +0xb44 [derived: app::ai_param::return_sp_u_cliff_y]
    f32 return_goal_x[4];      // +0xb54 [derived: app::ai_param::return_goal_x]
    f32 return_goal_x_strict[4]; // +0xb64 [derived: app::ai_param::return_goal_x_strict]
    f32 return_goal_pad_x_strict[4]; // +0xb74 [derived: app::ai_param::return_goal_pad_x_strict]
    u8 unk_0xb84[0x84];

    // ---- CP config fields ----
    u8 cp_type;                // +0xc08 [derived: app::ai::cp_type reads as u8]
    u8 unk_0xc09[0x3];
    s32 rank;                  // +0xc0c [derived: app::ai::rank converts s32→float]
    u8 unk_0xc10[0x2];
    u16 cp_flag;               // +0xc12 [derived: app::ai::cp_flag reads as u16]
    u8 unk_0xc14[0x1C];

    // ---- Input state ----
    f32 stick_data[4];         // +0xc30 [derived: reset_stick zeroes 16B via NEON]
    u32 button_state;          // +0xc40 [derived: add_button ORs bitmask here]
    u8 unk_0xc44[0xC];

    // ---- Target tracking ----
    s32 target_entry_id;       // +0xc50 [derived: predict_target_landing_frame checks >=0 and != parent_entry_id]
    u8 target_ref_rest[0x28];  // +0xc54 [derived: remaining target reference data]

    // ---- Return logic ----
    s16 return_count;          // +0xc7c [derived: reset_return_count zeroes; set_no_return_frame negates]
};

// ---------------------------------------------------------------------------
// Helper: extract FighterAI* from lua_State*
// Replaces the AI_CTX(L) macro
// ---------------------------------------------------------------------------
static inline FighterAI* get_ai_context(u64 L) {
    return *reinterpret_cast<FighterAI**>(L - 8);
}
