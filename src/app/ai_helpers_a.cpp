#include "types.h"
#include "app/placeholders/FighterAI.h"

// pool-c Phase 3: AI helper functions rewritten with typed struct access
// Domains: app::ai, app::ai_camera, app::ai_param, app::ai_stage, app::analyst, app::ai_system
// All functions operate on FighterAI context accessed via lua_State.

#define HIDDEN __attribute__((visibility("hidden")))

// ---- External data ----

// lib::Singleton<app::FighterAIManager>::instance_ (AI manager root)
// [derived: DAT_71052b5fd8 in Ghidra, adrp 0x71052b5000 + 0xfd8]
// Singleton pattern: global stores ptr → deref once to get FighterAIManager*
extern "C" void* DAT_71052b5fd8 HIDDEN;

// AI param accessor singleton
// [derived: DAT_71052b60e8 in Ghidra, adrp 0x71052b6000 + 0xe8]
extern "C" void* DAT_71052b60e8 HIDDEN;

// lib::Singleton<app::StageManager>::instance_
// [derived: adrp 0x7105329000 + 0x9d8 in is_in_transition asm]
extern "C" u64 DAT_71053299d8 HIDDEN;

// PTR_ConstantZero — pointer to 16-byte zero vector at 0x71052a7a80
// [derived: used by reset_stick, adrp+ldr loads pointer, then ldr q0 through it]
extern "C" void* PTR_ConstantZero_71052a7a80 HIDDEN;

// ---- app::ai — fighter AI queries ----

// ---------------------------------------------------------------------------
// 0x71003694f0 — predict_landing_frame (20B)
// [derived: app::ai::predict_landing_frame in Ghidra .dynsym]
// Reads s32 at AI_STATE + 0x274, converts to float (scvtf)
// ---------------------------------------------------------------------------
float predict_landing_frame_3694f0(u64 L) {
    FighterAI* ctx = get_ai_context(L);
    return (float)ctx->state->predict_landing_frame;
}

// ---------------------------------------------------------------------------
// 0x7100367910 — floor_width (28B)
// [derived: app::ai::floor_width in Ghidra]
// Reads floor collision rect: fabsf(right - left) from ground data +0xd0
// ---------------------------------------------------------------------------
float floor_width_367910(u64 L) {
    FighterAI* ctx = get_ai_context(L);
    AIFloorCollisionData* floor = ctx->state->floor_data;
    return __builtin_fabsf(floor->right_edge - floor->left_edge);
}

// ---------------------------------------------------------------------------
// 0x7100367930 — floor_center (36B)
// [derived: app::ai::floor_center in Ghidra]
// Average of floor left and right edges
// ---------------------------------------------------------------------------
float floor_center_367930(u64 L) {
    FighterAI* ctx = get_ai_context(L);
    AIFloorCollisionData* floor = ctx->state->floor_data;
    return (floor->right_edge + floor->left_edge) * 0.5f;
}

// ---- app::ai_camera — blast zone boundaries ----
// All read from the camera boundary struct at FighterAIManager + 0xc8
// [derived: app::ai_camera::dead_* in Ghidra, float return via ldr s0]

// ---------------------------------------------------------------------------
// 0x710036b180 — dead_top (24B)
// ---------------------------------------------------------------------------
float dead_top_36b180() {
    FighterAIManager* mgr = reinterpret_cast<FighterAIManager*>(*(u64*)DAT_71052b5fd8);
    return mgr->cam_bounds->dead_top;
}

// ---------------------------------------------------------------------------
// 0x710036b1a0 — dead_bottom (24B)
// ---------------------------------------------------------------------------
float dead_bottom_36b1a0() {
    FighterAIManager* mgr = reinterpret_cast<FighterAIManager*>(*(u64*)DAT_71052b5fd8);
    return mgr->cam_bounds->dead_bottom;
}

// ---------------------------------------------------------------------------
// 0x710036b1c0 — dead_left (24B)
// ---------------------------------------------------------------------------
float dead_left_36b1c0() {
    FighterAIManager* mgr = reinterpret_cast<FighterAIManager*>(*(u64*)DAT_71052b5fd8);
    return mgr->cam_bounds->dead_left;
}

// ---------------------------------------------------------------------------
// 0x710036b1e0 — dead_right (24B)
// ---------------------------------------------------------------------------
float dead_right_36b1e0() {
    FighterAIManager* mgr = reinterpret_cast<FighterAIManager*>(*(u64*)DAT_71052b5fd8);
    return mgr->cam_bounds->dead_right;
}

// ---- app::ai_stage — stage state queries ----

// ---------------------------------------------------------------------------
// 0x710036b200 — current_id (20B)
// [derived: app::ai_stage::current_id in Ghidra]
// Returns current stage ID from AI manager
// ---------------------------------------------------------------------------
u32 current_id_36b200() {
    FighterAIManager* mgr = reinterpret_cast<FighterAIManager*>(*(u64*)DAT_71052b5fd8);
    return mgr->current_stage_id;
}

// ---------------------------------------------------------------------------
// 0x710036b470 — is_in_transition (28B)
// [derived: app::ai_stage::is_in_transition in Ghidra]
// Reads StageManager singleton field at +0xbc, returns nonzero
// ---------------------------------------------------------------------------
bool is_in_transition_36b470(u64 L) {
    u64 sm = *(u64*)DAT_71053299d8;
    return *(s32*)(sm + 0xbc) != 0;
}

// ---- app::ai_param — indexed param table reads ----
// All follow the pattern: read fighter_kind index from state + 0x240,
// then index into a per-fighter param array on the FighterAI context.
// [derived: app::ai_param::* in Ghidra, float return via ldr s0]

// ---------------------------------------------------------------------------
// 0x710036b8b0 — air_high (32B)
// [derived: app::ai_param::air_high in Ghidra]
// (ctx_param - 3.0) * ai_state_scale
// ---------------------------------------------------------------------------
float air_high_36b8b0(u64 L) {
    FighterAI* ctx = get_ai_context(L);
    return (ctx->air_high_base + -3.0f) * ctx->state->air_high_scale;
}

// ---------------------------------------------------------------------------
// 0x710036b8d0 — air_length (32B)
// [derived: app::ai_param::air_length in Ghidra]
// ---------------------------------------------------------------------------
float air_length_36b8d0(u64 L) {
    FighterAI* ctx = get_ai_context(L);
    return (ctx->air_length_base + -3.0f) * ctx->state->air_length_scale;
}

// ---------------------------------------------------------------------------
// 0x710036b8f0 — sp_u_high (24B)
// [derived: app::ai_param::sp_u_high in Ghidra]
// Per-fighter indexed float: ctx + fighter_kind * 4 + 0xad0
// ---------------------------------------------------------------------------
float sp_u_high_36b8f0(u64 L) {
    FighterAI* ctx = get_ai_context(L);
    s32 idx = ctx->state->fighter_kind_index;
    return ctx->sp_u_high[idx];
}

// ---------------------------------------------------------------------------
// 0x710036b910 — sp_u_length (24B)
// ---------------------------------------------------------------------------
float sp_u_length_36b910(u64 L) {
    FighterAI* ctx = get_ai_context(L);
    s32 idx = ctx->state->fighter_kind_index;
    return ctx->sp_u_length[idx];
}

// ---------------------------------------------------------------------------
// 0x710036b930 — return_sp_u_cliff_x (24B)
// ---------------------------------------------------------------------------
float return_sp_u_cliff_x_36b930(u64 L) {
    FighterAI* ctx = get_ai_context(L);
    s32 idx = ctx->state->fighter_kind_index;
    return ctx->return_sp_u_cliff_x[idx];
}

// ---------------------------------------------------------------------------
// 0x710036b950 — return_sp_u_cliff_y (24B)
// ---------------------------------------------------------------------------
float return_sp_u_cliff_y_36b950(u64 L) {
    FighterAI* ctx = get_ai_context(L);
    s32 idx = ctx->state->fighter_kind_index;
    return ctx->return_sp_u_cliff_y[idx];
}

// ---------------------------------------------------------------------------
// 0x710036b970 — return_goal_x (24B)
// ---------------------------------------------------------------------------
float return_goal_x_36b970(u64 L) {
    FighterAI* ctx = get_ai_context(L);
    s32 idx = ctx->state->fighter_kind_index;
    return ctx->return_goal_x[idx];
}

// ---------------------------------------------------------------------------
// 0x710036b990 — return_goal_x_strict (24B)
// ---------------------------------------------------------------------------
float return_goal_x_strict_36b990(u64 L) {
    FighterAI* ctx = get_ai_context(L);
    s32 idx = ctx->state->fighter_kind_index;
    return ctx->return_goal_x_strict[idx];
}

// ---------------------------------------------------------------------------
// 0x710036b9b0 — return_goal_pad_x_strict (24B)
// ---------------------------------------------------------------------------
float return_goal_pad_x_strict_36b9b0(u64 L) {
    FighterAI* ctx = get_ai_context(L);
    s32 idx = ctx->state->fighter_kind_index;
    return ctx->return_goal_pad_x_strict[idx];
}

// ---- app::ai_param — global AI param singleton reads ----
// All read from *DAT_71052b60e8 + offset. Return float (ldr s0).
// [derived: app::ai_param::* in Ghidra]

// ---------------------------------------------------------------------------
// 0x710036c140 — zako2_search_range (20B)
// ---------------------------------------------------------------------------
float zako2_search_range_36c140(u64 L) {
    u64 params = *(u64*)DAT_71052b60e8;
    return *(float*)(params + 0x78);
}

// ---------------------------------------------------------------------------
// 0x710036c160 — training_smash_interval (20B)
// [derived: binary uses ldr w0 (integer return), not ldr s0]
// ---------------------------------------------------------------------------
u32 training_smash_interval_36c160(u64 L) {
    u64 params = *(u64*)DAT_71052b60e8;
    return *(u32*)(params + 0x7c);
}

// ---------------------------------------------------------------------------
// 0x710036c180 — training_special_interval (20B)
// [derived: binary uses ldr w0 (integer return), not ldr s0]
// ---------------------------------------------------------------------------
u32 training_special_interval_36c180(u64 L) {
    u64 params = *(u64*)DAT_71052b60e8;
    return *(u32*)(params + 0x80);
}

// ---------------------------------------------------------------------------
// 0x710036c1a0 — challenger_guard_rate (20B)
// ---------------------------------------------------------------------------
float challenger_guard_rate_36c1a0(u64 L) {
    u64 params = *(u64*)DAT_71052b60e8;
    return *(float*)(params + 0x84);
}

// ---- app::analyst — status history queries ----
// Read from the analyst object at *(ctx->analyst_ptr), double-deref.
// [derived: app::analyst::* in Ghidra, u32 return via ldr w0]

// ---------------------------------------------------------------------------
// 0x7100376a00 — status_prev (20B)
// ---------------------------------------------------------------------------
u32 status_prev_376a00(u64 L) {
    FighterAI* ctx = get_ai_context(L);
    AIAnalyst* analyst = reinterpret_cast<AIAnalyst*>(*ctx->analyst_ptr);
    return analyst->status_prev;
}

// ---------------------------------------------------------------------------
// 0x7100376ac0 — status_count (20B)
// ---------------------------------------------------------------------------
u32 status_count_376ac0(u64 L) {
    FighterAI* ctx = get_ai_context(L);
    AIAnalyst* analyst = reinterpret_cast<AIAnalyst*>(*ctx->analyst_ptr);
    return analyst->status_count;
}

// ---------------------------------------------------------------------------
// 0x7100376b90 — chanced_frame (20B)
// ---------------------------------------------------------------------------
u32 chanced_frame_376b90(u64 L) {
    FighterAI* ctx = get_ai_context(L);
    AIAnalyst* analyst = reinterpret_cast<AIAnalyst*>(*ctx->analyst_ptr);
    return analyst->chanced_frame;
}

// ---- app::ai_system — input/mode control ----

// ---------------------------------------------------------------------------
// 0x71003762f0 — reset_stick (24B)
// [derived: app::ai_system::reset_stick in Ghidra]
// Copies 16-byte zero vector (ConstantZero) to ctx + 0xc30
// Asm: ldr q0,[ConstantZero]; str q0,[ctx+0xc30]
// Uses 128-bit vector copy (stick data is 2 x Vector2f)
// ---------------------------------------------------------------------------
typedef float v4sf __attribute__((vector_size(16)));
void reset_stick_3762f0(u64 L) {
    FighterAI* ctx = get_ai_context(L);
    *reinterpret_cast<v4sf*>(ctx->stick_data) =
        *reinterpret_cast<const v4sf*>((u64)PTR_ConstantZero_71052a7a80);
}

// ---------------------------------------------------------------------------
// 0x7100376330 — set_action_id_none (24B)
// [derived: app::ai_system::set_action_id_none in Ghidra]
// Saves current action_id to prev, then clears current
// ---------------------------------------------------------------------------
void set_action_id_none_376330(u64 L) {
    FighterAI* ctx = get_ai_context(L);
    u16 current = ctx->action_id;
    if (current != 0) {
        ctx->action_id_prev = current;
    }
    ctx->action_id = 0;
}

// ---- app::ai_system — button/mode control (32B functions) ----

// Button mask lookup table
// [derived: adrp 0x7104538000 + 0xfec = DAT_7104538fec, indexed by ControlPadButtonKind]
extern "C" u32 DAT_7104538fec[] HIDDEN;

// ---------------------------------------------------------------------------
// 0x7100376310 — add_button (32B)
// [derived: app::ai_system::add_button in Ghidra]
// ORs button bitmask into AI button state at ctx + 0xc40
// ---------------------------------------------------------------------------
void add_button_376310(u64 L, s32 kind) {
    FighterAI* ctx = get_ai_context(L);
    ctx->button_state |= DAT_7104538fec[kind];
}

// ---------------------------------------------------------------------------
// 0x7100376360 — change_mode_action (32B)
// [derived: app::ai_system::change_mode_action in Ghidra]
// Double-deref: *(*(ctx)) -> mode struct; sets byte +0x39 if +0x38 != 0
// ---------------------------------------------------------------------------
void change_mode_action_376360(u64 L) {
    FighterAI* ctx = get_ai_context(L);
    u64 mode = *(u64*)ctx->mode_ptr;
    if (*(u8*)(mode + 0x38) != 0) {
        *(u8*)(mode + 0x39) = 1;
    }
}

// ---------------------------------------------------------------------------
// 0x71003763a0 — change_mode (32B)
// [derived: app::ai_system::change_mode in Ghidra]
// Non-leaf: calls FUN_71002d8ef0(ctx, mode, -1, 0) to switch AI mode
// ---------------------------------------------------------------------------
extern void FUN_71002d8ef0(u64, u32, u32, u32);
__attribute__((disable_tail_calls))
void change_mode_3763a0(u64 L, u32 mode) {
    FUN_71002d8ef0(reinterpret_cast<u64>(get_ai_context(L)), mode, 0xFFFFFFFF, 0);
}

// ---- External functions for AI subsystems ----

// Action system dispatchers (ctx + 0x180 = action sub-object base)
extern void FUN_71002edd30(u64, u16, u32*);
extern void FUN_71002eeb20(float, float, u64, u32);
extern void FUN_71002f43c0(u64);
extern void FUN_71002f4590(u64);
extern void FUN_71002f46a0(u64, u32);
extern void FUN_71002f5770(u64, u32);

// AI state check
extern void FUN_7100359e30(u64);

// Target lookup: returns pointer to target's AI state snapshot
// [derived: used by all target_* functions, first param is manager global]
extern u64 aiGetTargetById_7100314030(void*, u64);

// Threshold constants
// [derived: distance threshold for lr_to_target, adrp+ldr pattern]
extern "C" float DAT_71044724d4 HIDDEN;
// [derived: param for check_over_ground_distance_current_lr]
extern "C" float DAT_7104471e0c HIDDEN;

// ---- app::ai — new function decomps (Phase 3, struct-typed) ----

// ---------------------------------------------------------------------------
// 0x71003680e0 — goal_pos (12B)
// [derived: app::ai::goal_pos in Ghidra]
// Returns 16-byte Vector4f goal position from ctx + 0x270
// ---------------------------------------------------------------------------
typedef float v4sf_ret __attribute__((vector_size(16)));
v4sf_ret goal_pos_3680e0(u64 L) {
    FighterAI* ctx = get_ai_context(L);
    return *reinterpret_cast<v4sf_ret*>(ctx->goal_pos);
}

// ---------------------------------------------------------------------------
// 0x71003680f0 — check_away_floor (12B)
// [derived: app::ai::check_away_floor in Ghidra]
// Dispatches to floor-check subroutine on the AI state
// ---------------------------------------------------------------------------
void check_away_floor_3680f0(u64 L) {
    FighterAI* ctx = get_ai_context(L);
    FUN_7100359e30(reinterpret_cast<u64>(ctx->state));
}

// ---------------------------------------------------------------------------
// 0x7100368170 — set_auto_stop (12B)
// [derived: app::ai::set_auto_stop in Ghidra]
// Writes s32 to ctx + 0x2bc (700 decimal)
// ---------------------------------------------------------------------------
void set_auto_stop_368170(u64 L, s32 val) {
    FighterAI* ctx = get_ai_context(L);
    ctx->auto_stop = val;
}

// ---------------------------------------------------------------------------
// 0x7100368180 — update_count (12B)
// [derived: app::ai::update_count in Ghidra]
// Returns u32 frame counter from ctx + 0x2fc
// ---------------------------------------------------------------------------
u32 update_count_368180(u64 L) {
    FighterAI* ctx = get_ai_context(L);
    return ctx->update_count;
}

// ---------------------------------------------------------------------------
// 0x71003681c0 — reset_return_count (12B)
// [derived: app::ai::reset_return_count in Ghidra]
// Zeroes u16 at ctx + 0xc7c
// ---------------------------------------------------------------------------
void reset_return_count_3681c0(u64 L) {
    FighterAI* ctx = get_ai_context(L);
    ctx->return_count = 0;
}

// ---------------------------------------------------------------------------
// 0x71003681d0 — set_no_return_frame (16B)
// [derived: app::ai::set_no_return_frame in Ghidra]
// Stores negated s16 to ctx + 0xc7c
// ---------------------------------------------------------------------------
void set_no_return_frame_3681d0(u64 L, s32 frames) {
    FighterAI* ctx = get_ai_context(L);
    ctx->return_count = -(s16)frames;
}

// ---------------------------------------------------------------------------
// 0x7100368cf0 — enable_command (12B)
// [derived: app::ai::enable_command in Ghidra]
// Delegates to action sub-object command enable
// ---------------------------------------------------------------------------
void enable_command_368cf0(u64 L, u32 cmd_id) {
    FUN_71002f5770(reinterpret_cast<u64>(get_ai_context(L)) + 0x180, cmd_id);
}

// ---------------------------------------------------------------------------
// 0x7100368d00 — disable_command (12B)
// [derived: app::ai::disable_command in Ghidra]
// ---------------------------------------------------------------------------
void disable_command_368d00(u64 L, u32 cmd_id) {
    FUN_71002f46a0(reinterpret_cast<u64>(get_ai_context(L)) + 0x180, cmd_id);
}

// ---------------------------------------------------------------------------
// 0x7100368d10 — disable_command_ground_all (12B)
// [derived: app::ai::disable_command_ground_all in Ghidra]
// ---------------------------------------------------------------------------
void disable_command_ground_all_368d10(u64 L) {
    FUN_71002f43c0(reinterpret_cast<u64>(get_ai_context(L)) + 0x180);
}

// ---------------------------------------------------------------------------
// 0x7100368d20 — disable_command_air_all (12B)
// [derived: app::ai::disable_command_air_all in Ghidra]
// ---------------------------------------------------------------------------
void disable_command_air_all_368d20(u64 L) {
    FUN_71002f4590(reinterpret_cast<u64>(get_ai_context(L)) + 0x180);
}

// ---------------------------------------------------------------------------
// 0x7100367e90 — floor_moves (20B)
// [derived: app::ai::floor_moves in Ghidra]
// Returns 16-byte floor movement vector from floor_data + 0x10
// ---------------------------------------------------------------------------
v4sf_ret floor_moves_367e90(u64 L) {
    FighterAI* ctx = get_ai_context(L);
    return *reinterpret_cast<v4sf_ret*>(ctx->state->floor_data->movement);
}

// ---------------------------------------------------------------------------
// 0x7100368140 — change_action (48B)
// [derived: app::ai::change_action in Ghidra]
// Non-leaf: builds stack arg {0xFFFFFFFF}, calls action dispatcher
// ---------------------------------------------------------------------------
__attribute__((disable_tail_calls))
void change_action_368140(u64 L, u16 action_id) {
    u32 arg = 0xFFFFFFFF;
    FUN_71002edd30(reinterpret_cast<u64>(get_ai_context(L)) + 0x180, action_id, &arg);
}

// ---------------------------------------------------------------------------
// 0x7100368190 — is_update_count_odd (48B)
// [derived: app::ai::is_update_count_odd in Ghidra]
// Despite the name, checks if update_count is divisible by 3
// ---------------------------------------------------------------------------
bool is_update_count_odd_368190(u64 L) {
    FighterAI* ctx = get_ai_context(L);
    s32 count = ctx->update_count;
    return count == (count / 3) * 3;
}

// ---------------------------------------------------------------------------
// 0x7100367960 — floor_lr (56B)
// [derived: app::ai::floor_lr in Ghidra]
// Returns 1.0f if fighter is left of floor center, -1.0f if right
// ---------------------------------------------------------------------------
u32 floor_lr_367960(u64 L) {
    FighterAI* ctx = get_ai_context(L);
    FighterAIState* state = ctx->state;
    AIFloorCollisionData* floor = state->floor_data;
    u32 result = 0x3f800000;  // 1.0f
    if ((floor->left_edge + floor->right_edge) * 0.5f <= state->pos_x) {
        result = 0xbf800000;  // -1.0f
    }
    return result;
}

// ---------------------------------------------------------------------------
// 0x7100367230 — distance_x_to_target (60B)
// [derived: app::ai::distance_x_to_target in Ghidra]
// Absolute X distance between self and target
// ---------------------------------------------------------------------------
float distance_x_to_target_367230(u64 L) {
    FighterAI* ctx = get_ai_context(L);
    float self_x = ctx->state->pos_x;
    u64 target = aiGetTargetById_7100314030(DAT_71052b5fd8, reinterpret_cast<u64>(ctx) + 0xc50);
    return __builtin_fabsf(self_x - *(float*)(target + 0x80));
}

// ---------------------------------------------------------------------------
// 0x7100367270 — distance_y_to_target (60B)
// [derived: app::ai::distance_y_to_target in Ghidra]
// Absolute Y distance between self and target
// ---------------------------------------------------------------------------
float distance_y_to_target_367270(u64 L) {
    FighterAI* ctx = get_ai_context(L);
    float self_y = ctx->state->pos_y;
    u64 target = aiGetTargetById_7100314030(DAT_71052b5fd8, reinterpret_cast<u64>(ctx) + 0xc50);
    return __builtin_fabsf(self_y - *(float*)(target + 0x84));
}

// ---------------------------------------------------------------------------
// 0x71003672b0 — is_target_on_same_floor (64B)
// [derived: app::ai::is_target_on_same_floor in Ghidra]
// Compares floor collision data pointers between self and target
// ---------------------------------------------------------------------------
bool is_target_on_same_floor_3672b0(u64 L) {
    FighterAI* ctx = get_ai_context(L);
    u64 target = aiGetTargetById_7100314030(DAT_71052b5fd8, reinterpret_cast<u64>(ctx) + 0xc50);
    return reinterpret_cast<u64>(ctx->state->floor_data) == *(u64*)(target + 0xd0);
}

// ---------------------------------------------------------------------------
// 0x7100367080 — target_hit_collision_rect (64B)
// [derived: app::ai::target_hit_collision_rect in Ghidra]
// Returns 16-byte hit rect from target state + 0x264
// ---------------------------------------------------------------------------
v4sf_ret target_hit_collision_rect_367080(u64 L) {
    FighterAI* ctx = get_ai_context(L);
    u64 target = aiGetTargetById_7100314030(DAT_71052b5fd8, reinterpret_cast<u64>(ctx) + 0xc50);
    return *reinterpret_cast<v4sf_ret*>(target + 0x264);
}

// ---------------------------------------------------------------------------
// 0x7100367a90 — check_over_ground (72B)
// [derived: app::ai::check_over_ground in Ghidra]
// Multi-condition ground check using state flags and floor data
// ---------------------------------------------------------------------------
bool check_over_ground_367a90(u64 L) {
    FighterAI* ctx = get_ai_context(L);
    FighterAIState* state = ctx->state;
    if ((state->stat_flags & 1) == 0 &&
        ((*(u8*)((u64)state->floor_data + 0x5e) >> 1) & 1) == 0) {
        return true;
    }
    if ((state->uniq_stat & 0xFFFFFFFE) == 6) {
        return true;
    }
    return (state->stat_flags & 2) == 0;
}

// ---------------------------------------------------------------------------
// 0x7100367ae0 — check_over_ground_distance_current_lr (24B)
// [derived: app::ai::check_over_ground_distance_current_lr in Ghidra]
// Delegates to ground distance check with threshold
// ---------------------------------------------------------------------------
void check_over_ground_distance_current_lr_367ae0(u64 L, float dist) {
    FUN_71002eeb20(dist, DAT_7104471e0c, reinterpret_cast<u64>(get_ai_context(L)) + 0x180, 1);
}

// ---- Batch 2: additional AI function decomps ----

// External functions for batch 2
extern u64 FUN_71002f04f0(u64, u32, u32*, u32*, u32*);

// ---------------------------------------------------------------------------
// 0x71003670c0 — lr_to_target (104B)
// [derived: app::ai::lr_to_target in Ghidra]
// Returns facing direction toward target as 1.0f/-1.0f raw bits,
// or current LR if within threshold distance
// ---------------------------------------------------------------------------
u32 lr_to_target_3670c0(u64 L) {
    FighterAI* ctx = get_ai_context(L);
    FighterAIState* state = ctx->state;
    u64 target = aiGetTargetById_7100314030(DAT_71052b5fd8, reinterpret_cast<u64>(ctx) + 0xc50);
    float self_x = state->pos_x;
    if (DAT_71044724d4 <= __builtin_fabsf(*(float*)(target + 0x80) - self_x)) {
        u32 result = 0xbf800000;  // -1.0f
        if (0.0f <= *(float*)(target + 0x80) - self_x) {
            result = 0x3f800000;  // 1.0f
        }
        return result;
    }
    return *(u32*)&state->lr;
}

// ---------------------------------------------------------------------------
// 0x7100367b00 — check_target_over_ground (104B)
// [derived: app::ai::check_target_over_ground in Ghidra]
// Same logic as check_over_ground but on target's state
// ---------------------------------------------------------------------------
bool check_target_over_ground_367b00(u64 L) {
    FighterAI* ctx = get_ai_context(L);
    FighterAIState* target = reinterpret_cast<FighterAIState*>(
        aiGetTargetById_7100314030(DAT_71052b5fd8, reinterpret_cast<u64>(ctx) + 0xc50));
    if ((target->stat_flags & 1) == 0 &&
        ((target->floor_data->flags_0x5e >> 1) & 1) == 0) {
        return true;
    }
    if ((target->uniq_stat & 0xFFFFFFFE) == 6) {
        return true;
    }
    return (target->stat_flags & 2) == 0;
}

// ---------------------------------------------------------------------------
// 0x7100367b70 — check_over_goal (80B)
// [derived: app::ai::check_over_goal in Ghidra]
// Checks if fighter has reached a navigation goal point
// Uses ctx+0x188 sub-object (different from state at +0x168)
// ---------------------------------------------------------------------------
bool check_over_goal_367b70(u64 L) {
    FighterAI* ctx = get_ai_context(L);
    AIGoalState* goal = reinterpret_cast<AIGoalState*>(*(u64*)ctx->sub_0x188);
    AIGoalFloorData* gfloor = goal->floor;
    AIGoalNavNode* node = gfloor->nav_node;
    if (node != nullptr &&
        ctx->goal_check_a == node->nav_id &&
        ctx->goal_check_b == gfloor->floor_id &&
        goal->goal_state == 1) {
        return true;
    }
    return false;
}

// ---------------------------------------------------------------------------
// 0x71003681e0 — get_cmd_id_from_req_id (48B)
// [derived: app::ai::get_cmd_id_from_req_id in Ghidra]
// Non-leaf: allocates 3 stack locals, calls FUN_71002f04f0
// ---------------------------------------------------------------------------
__attribute__((disable_tail_calls))
void get_cmd_id_from_req_id_3681e0(u64 L, u32 req_id) {
    u32 a, b, c;
    FUN_71002f04f0(reinterpret_cast<u64>(get_ai_context(L)) + 0x180, req_id, &a, &b, &c);
}

// ---------------------------------------------------------------------------
// 0x7100361c70 — jump_rest_available (104B)
// [derived: app::ai::jump_rest_available in Ghidra]
// Returns remaining jump count, with special cases for certain fighter kinds
// ---------------------------------------------------------------------------
u16 jump_rest_available_361c70(u64 L) {
    FighterAI* ctx = get_ai_context(L);
    FighterAIState* state = ctx->state;
    if (state->uniq_stat == 0x10) {
        return 0;
    }
    if ((state->flags_0x59 >> 5 & 1) == 0) {
        if (state->fighter_kind == 0x22) {
            if ((state->flags_0x68 >> 2 & 1) == 0) {
                return 0;
            }
        } else if (state->fighter_kind == 0x29 && (state->flags_0x68 & 1) != 0) {
            return 0;
        }
        return state->jump_rest;
    }
    return 0;
}

// ---------------------------------------------------------------------------
// 0x7100367460 — parent_pos_y (68B)
// [derived: app::ai::parent_pos_y in Ghidra]
// Looks up parent fighter's Y position
// ---------------------------------------------------------------------------
__attribute__((disable_tail_calls))
u32 parent_pos_y_367460(u64 L) {
    FighterAI* ctx = get_ai_context(L);
    u32 local[2];
    local[0] = ctx->parent_entry_id & 7;
    if (ctx->parent_entry_id > 0xf) {
        local[0] = 0xFFFFFFFF;
    }
    u64 parent = aiGetTargetById_7100314030(DAT_71052b5fd8, reinterpret_cast<u64>(local));
    return *(u32*)(parent + 0x84);
}

// ---------------------------------------------------------------------------
// 0x71003674b0 — parent_speed_y (68B)
// [derived: app::ai::parent_speed_y in Ghidra]
// Looks up parent fighter's Y speed
// ---------------------------------------------------------------------------
__attribute__((disable_tail_calls))
u32 parent_speed_y_3674b0(u64 L) {
    FighterAI* ctx = get_ai_context(L);
    u32 local[2];
    local[0] = ctx->parent_entry_id & 7;
    if (ctx->parent_entry_id > 0xf) {
        local[0] = 0xFFFFFFFF;
    }
    u64 parent = aiGetTargetById_7100314030(DAT_71052b5fd8, reinterpret_cast<u64>(local));
    return *(u32*)(parent + 0xa4);
}

// ---------------------------------------------------------------------------
// 0x7100367400 — check_parent_same_floor (84B)
// [derived: app::ai::check_parent_same_floor in Ghidra]
// Checks if self and parent are on the same floor collision data
// ---------------------------------------------------------------------------
__attribute__((disable_tail_calls))
bool check_parent_same_floor_367400(u64 L) {
    FighterAI* ctx = get_ai_context(L);
    u32 local[2];
    local[0] = ctx->parent_entry_id & 7;
    if (ctx->parent_entry_id > 0xf) {
        local[0] = 0xFFFFFFFF;
    }
    u64 parent = aiGetTargetById_7100314030(DAT_71052b5fd8, reinterpret_cast<u64>(local));
    return reinterpret_cast<u64>(ctx->state->floor_data) == *(u64*)(parent + 0xd0);
}

// ---------------------------------------------------------------------------
// 0x71003672b0 already done above as is_target_on_same_floor
// ---------------------------------------------------------------------------

// ---- Batch 3: small AI functions ----

// External functions for batch 3
extern void FUN_710033e5c0(u64, u64);
extern void FUN_71002ec1a0(u64);
extern void FUN_710036a5c0(u64, u32, u32);
extern void FUN_710160e340(u64);
extern void FUN_71002ee310(u64, u64*, u32);
extern u64 FUN_71003596f0(u64);
extern void FUN_7100358a80(float, u64, u64);

// BattleObjectWorld singleton (double-deref pattern like FighterAIManager)
// [derived: app::ai_stage::scroll_x reads from this + 0x20]
extern "C" void* DAT_71052b7ed8 HIDDEN;

// ---------------------------------------------------------------------------
// 0x7100376350 — set_update_count (12B)
// [derived: app::ai_system::set_update_count in Ghidra]
// ---------------------------------------------------------------------------
void set_update_count_376350(u64 L, s32 val) {
    FighterAI* ctx = get_ai_context(L);
    ctx->update_count = val;
}

// ---------------------------------------------------------------------------
// 0x71003763c0 — change_target (8B)
// [derived: app::ai_system::change_target in Ghidra]
// Tail-calls FUN_71002ec1a0 with raw ctx pointer
// ---------------------------------------------------------------------------
void change_target_3763c0(u64 L) {
    FUN_71002ec1a0(reinterpret_cast<u64>(get_ai_context(L)));
}

// ---------------------------------------------------------------------------
// 0x7100376390 — prev_mode (12B)
// [derived: app::ai_system::prev_mode in Ghidra]
// Returns u32 from ctx + 0xc68
// ---------------------------------------------------------------------------
u32 prev_mode_376390(u64 L) {
    u64 ctx = reinterpret_cast<u64>(get_ai_context(L));
    return *(u32*)(ctx + 0xc68);
}

// ---------------------------------------------------------------------------
// 0x710036a130 — motion_to_cmd_id (12B)
// [derived: app::ai::motion_to_cmd_id in Ghidra]
// Dispatches hash lookup on cmd table at ctx + 0x988
// ---------------------------------------------------------------------------
void motion_to_cmd_id_36a130(u64 L, u64 hash) {
    FUN_710033e5c0(reinterpret_cast<u64>(get_ai_context(L)) + 0x988, hash);
}

// ---------------------------------------------------------------------------
// 0x710036a5b0 — range_in (12B)
// [derived: app::ai_deprecated::range_in in Ghidra]
// Deprecated: always calls predict with mode=1, extra=0
// ---------------------------------------------------------------------------
void range_in_36a5b0(u64 L, float a, float b) {
    FUN_710036a5c0(L, 1, 0);
}

// ---------------------------------------------------------------------------
// 0x710036acf0 — distance_in (12B)
// [derived: app::ai_deprecated::distance_in in Ghidra]
// Deprecated: always calls predict with mode=0, extra=0
// ---------------------------------------------------------------------------
void distance_in_36acf0(u64 L, float a, float b) {
    FUN_710036a5c0(L, 0, 0);
}

// ---------------------------------------------------------------------------
// 0x710036ad00 — other_in (12B)
// [derived: app::ai_deprecated::other_in in Ghidra]
// Deprecated: always calls predict with mode=0, extra=1
// ---------------------------------------------------------------------------
void other_in_36ad00(u64 L, float a, float b) {
    FUN_710036a5c0(L, 0, 1);
}

// ---------------------------------------------------------------------------
// 0x710036b3d0 — scroll_x (16B)
// [derived: app::ai_stage::scroll_x in Ghidra]
// Returns BattleObjectWorld + 0x20 as u32 (stage scroll speed X)
// ---------------------------------------------------------------------------
u32 scroll_x_36b3d0() {
    u64 wrapper = *(u64*)DAT_71052b7ed8;
    u64 world = *(u64*)wrapper;
    return *(u32*)(world + 0x20);
}

// ---------------------------------------------------------------------------
// 0x710036b3e0 — calc_offset_with_gravity (8B)
// [derived: app::ai_stage::calc_offset_with_gravity in Ghidra]
// Tail-calls FUN_710160e340 with contents of param_2 (packed 2xf32)
// ---------------------------------------------------------------------------
void calc_offset_with_gravity_36b3e0(void* param_1, u64* param_2) {
    FUN_710160e340(*param_2);
}

// ---------------------------------------------------------------------------
// 0x710036b030 — most_earliest_weapon (36B)
// [derived: app::ai_weapon::most_earliest_weapon in Ghidra]
// Finds the first weapon in the AI state, returns weapon+8 or 0
// ---------------------------------------------------------------------------
u64 most_earliest_weapon_36b030(u64 L) {
    FighterAI* ctx = get_ai_context(L);
    u64 result = FUN_71003596f0(reinterpret_cast<u64>(ctx->state));
    if (result != 0) {
        result = *(u64*)(result + 8);
    }
    return result;
}

// ---------------------------------------------------------------------------
// 0x710036ad10 — get_target_vector (24B)
// [derived: app::ai_deprecated::get_target_vector in Ghidra]
// Scales a float by ctx+0xc20 and passes to target vector computation
// ---------------------------------------------------------------------------
void get_target_vector_36ad10(u64 L, float scale) {
    FighterAI* ctx = get_ai_context(L);
    u64 raw = reinterpret_cast<u64>(ctx);
    FUN_7100358a80(*(float*)(raw + 0xc20) * scale,
                   reinterpret_cast<u64>(ctx->state),
                   raw + 0xc50);
}

// ---------------------------------------------------------------------------
// 0x710036ad30 — get_safe_fall (52B)
// [derived: app::ai_deprecated::get_safe_fall in Ghidra]
// Initializes stack-local Vector4f to zero, calls safe fall computation
// ---------------------------------------------------------------------------
__attribute__((disable_tail_calls))
v4sf_ret get_safe_fall_36ad30(u64 L) {
    u64 local[2] = {0, 0};
    FUN_71002ee310(reinterpret_cast<u64>(get_ai_context(L)) + 0x180,
                   local, 1);
    return *reinterpret_cast<v4sf_ret*>(local);
}

// ---------------------------------------------------------------------------
// 0x710036ad70 — get_safe_fall_current (52B)
// [derived: app::ai_deprecated::get_safe_fall_current in Ghidra]
// Same as get_safe_fall but with param=0
// ---------------------------------------------------------------------------
__attribute__((disable_tail_calls))
v4sf_ret get_safe_fall_current_36ad70(u64 L) {
    u64 local[2] = {0, 0};
    FUN_71002ee310(reinterpret_cast<u64>(get_ai_context(L)) + 0x180,
                   local, 0);
    return *reinterpret_cast<v4sf_ret*>(local);
}

// ---- Batch 4: dangerzone/target/rule functions ----

extern void FUN_71002f9ca0(u64, u64, u64, u32);

// ---------------------------------------------------------------------------
// 0x7100369510 — predict_target_landing_frame (76B)
// [derived: app::ai::predict_target_landing_frame in Ghidra]
// Returns target's predicted landing frame, or 0 if target is self/parent
// ---------------------------------------------------------------------------
float predict_target_landing_frame_369510(u64 L) {
    FighterAI* ctx = get_ai_context(L);
    u64 target = aiGetTargetById_7100314030(DAT_71052b5fd8, reinterpret_cast<u64>(ctx) + 0xc50);
    float result = 0.0f;
    if (ctx->target_entry_id >= 0 &&
        ctx->target_entry_id != (s32)ctx->parent_entry_id) {
        result = (float)*(s32*)(target + 0x274);
    }
    return result;
}

// ---------------------------------------------------------------------------
// 0x710036b540 — width (52B)
// [derived: app::ai_dangerzone::width in Ghidra]
// Returns width of dangerzone entry: right - left
// ---------------------------------------------------------------------------
float width_36b540(s32 index) {
    if ((u32)index < 0x38) {
        FighterAIManager* mgr = reinterpret_cast<FighterAIManager*>(*(u64*)DAT_71052b5fd8);
        u64 entry = reinterpret_cast<u64>(mgr->dangerzone_array) + (s64)index * 0x14;
        return *(float*)(entry + 8) - *(float*)(entry + 4);
    }
    return 0.0f;
}

// ---------------------------------------------------------------------------
// 0x710036b4b0 — check_line_segment (32B)
// [derived: app::ai_dangerzone::check_line_segment in Ghidra]
// Delegates to dangerzone line segment check
// ---------------------------------------------------------------------------
void check_line_segment_36b4b0(u64 L, u64 start, u64 end) {
    FighterAI* ctx = get_ai_context(L);
    FighterAIManager* mgr = reinterpret_cast<FighterAIManager*>(*(u64*)DAT_71052b5fd8);
    FUN_71002f9ca0(reinterpret_cast<u64>(mgr->dangerzone_array),
                   start, end, ctx->state->dangerzone_index);
}

// ---------------------------------------------------------------------------
// 0x710036b580 — is_1on1 (64B)
// [derived: app::ai_rule::is_1on1 in Ghidra]
// Returns true if 2-player match and the other player is alive
// ---------------------------------------------------------------------------
bool is_1on1_36b580(u64 L) {
    FighterAIManager* mgr = reinterpret_cast<FighterAIManager*>(*(u64*)DAT_71052b5fd8);
    if (mgr->player_count == 2) {
        FighterAI* ctx = get_ai_context(L);
        return mgr->player_alive[ctx->state->player_index] == 1;
    }
    return false;
}
