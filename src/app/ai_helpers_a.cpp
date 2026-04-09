#include "types.h"

// pool-a round 6: AI module helper functions
// Domains: app::ai, app::ai_camera, app::ai_param, app::ai_stage, app::analyst, app::ai_system
// All functions operate on the FighterAI context structure accessed via lua_State.

#define HIDDEN __attribute__((visibility("hidden")))

// ---- External data ----

// lib::Singleton<app::FighterAIManager>::instance_ (AI manager root)
// [derived: DAT_71052b5fd8 in Ghidra, adrp 0x71052b5000 + 0xfd8]
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

// ---- Helper macros ----

// Common pointer chains for AI context access:
//   L → *(L - 8) = FighterAI context base
//   ctx + 0x168 = AI state object (target tracking, floor data, etc.)
//   ctx + 0x170 = analyst object pointer (status history)
#define AI_CTX(L)   (*(u64*)(L - 8))
#define AI_STATE(L)  (*(u64*)(*(u64*)(L - 8) + 0x168))

// ---- app::ai — fighter AI queries ----

// ---------------------------------------------------------------------------
// 0x71003694f0 — predict_landing_frame (20B)
// [derived: app::ai::predict_landing_frame in Ghidra .dynsym]
// Reads s32 at AI_STATE + 0x274, converts to float (scvtf)
// ---------------------------------------------------------------------------
float predict_landing_frame_3694f0(u64 L) {
    return (float)*(s32*)(AI_STATE(L) + 0x274);
}

// ---------------------------------------------------------------------------
// 0x7100367910 — floor_width (28B)
// [derived: app::ai::floor_width in Ghidra]
// Reads floor collision rect: fabsf(right - left) from ground data +0xd0
// ---------------------------------------------------------------------------
float floor_width_367910(u64 L) {
    u64 floor = *(u64*)(AI_STATE(L) + 0xd0);
    float right = *(float*)(floor + 0x30);
    float left = *(float*)(floor + 0x20);
    return __builtin_fabsf(right - left);
}

// ---------------------------------------------------------------------------
// 0x7100367930 — floor_center (36B)
// [derived: app::ai::floor_center in Ghidra]
// Average of floor left and right edges
// ---------------------------------------------------------------------------
float floor_center_367930(u64 L) {
    u64 floor = *(u64*)(AI_STATE(L) + 0xd0);
    return (*(float*)(floor + 0x30) + *(float*)(floor + 0x20)) * 0.5f;
}

// ---- app::ai_camera — blast zone boundaries ----
// All read from the camera boundary struct at *DAT_71052b5fd8 + 0xc8
// [derived: app::ai_camera::dead_* in Ghidra, float return via ldr s0]

// ---------------------------------------------------------------------------
// 0x710036b180 — dead_top (24B)
// ---------------------------------------------------------------------------
float dead_top_36b180() {
    u64 mgr = *(u64*)DAT_71052b5fd8;
    u64 cam = *(u64*)(mgr + 0xc8);
    return *(float*)(cam + 0x10);
}

// ---------------------------------------------------------------------------
// 0x710036b1a0 — dead_bottom (24B)
// ---------------------------------------------------------------------------
float dead_bottom_36b1a0() {
    u64 mgr = *(u64*)DAT_71052b5fd8;
    u64 cam = *(u64*)(mgr + 0xc8);
    return *(float*)(cam + 0x14);
}

// ---------------------------------------------------------------------------
// 0x710036b1c0 — dead_left (24B)
// ---------------------------------------------------------------------------
float dead_left_36b1c0() {
    u64 mgr = *(u64*)DAT_71052b5fd8;
    u64 cam = *(u64*)(mgr + 0xc8);
    return *(float*)(cam + 0x8);
}

// ---------------------------------------------------------------------------
// 0x710036b1e0 — dead_right (24B)
// ---------------------------------------------------------------------------
float dead_right_36b1e0() {
    u64 mgr = *(u64*)DAT_71052b5fd8;
    u64 cam = *(u64*)(mgr + 0xc8);
    return *(float*)(cam + 0xc);
}

// ---- app::ai_stage — stage state queries ----

// ---------------------------------------------------------------------------
// 0x710036b200 — current_id (20B)
// [derived: app::ai_stage::current_id in Ghidra]
// Returns current stage ID from AI manager
// ---------------------------------------------------------------------------
u32 current_id_36b200() {
    u64 mgr = *(u64*)DAT_71052b5fd8;
    return *(u32*)(mgr + 0x150);
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
// All follow the pattern: read fighter_kind index from AI_STATE + 0x240,
// then index into a per-fighter param array at ctx + base_offset.
// [derived: app::ai_param::* in Ghidra, float return via ldr s0]

// ---------------------------------------------------------------------------
// 0x710036b8b0 — air_high (32B)
// [derived: app::ai_param::air_high in Ghidra]
// (ctx_param - 3.0) * ai_state_scale
// ---------------------------------------------------------------------------
float air_high_36b8b0(u64 L) {
    u64 ctx = AI_CTX(L);
    float base = *(float*)(ctx + 0xb04);
    float scale = *(float*)(AI_STATE(L) + 0x200);
    return (base + -3.0f) * scale;
}

// ---------------------------------------------------------------------------
// 0x710036b8d0 — air_length (32B)
// [derived: app::ai_param::air_length in Ghidra]
// ---------------------------------------------------------------------------
float air_length_36b8d0(u64 L) {
    u64 ctx = AI_CTX(L);
    float base = *(float*)(ctx + 0xb08);
    float scale = *(float*)(AI_STATE(L) + 0x1fc);
    return (base + -3.0f) * scale;
}

// ---------------------------------------------------------------------------
// 0x710036b8f0 — sp_u_high (24B)
// [derived: app::ai_param::sp_u_high in Ghidra]
// Per-fighter indexed float: ctx + fighter_kind * 4 + 0xad0
// ---------------------------------------------------------------------------
float sp_u_high_36b8f0(u64 L) {
    u64 ctx = AI_CTX(L);
    s32 idx = *(s32*)(AI_STATE(L) + 0x240);
    return *(float*)(ctx + (s64)idx * 4 + 0xad0);
}

// ---------------------------------------------------------------------------
// 0x710036b910 — sp_u_length (24B)
// ---------------------------------------------------------------------------
float sp_u_length_36b910(u64 L) {
    u64 ctx = AI_CTX(L);
    s32 idx = *(s32*)(AI_STATE(L) + 0x240);
    return *(float*)(ctx + (s64)idx * 4 + 0xae0);
}

// ---------------------------------------------------------------------------
// 0x710036b930 — return_sp_u_cliff_x (24B)
// ---------------------------------------------------------------------------
float return_sp_u_cliff_x_36b930(u64 L) {
    u64 ctx = AI_CTX(L);
    s32 idx = *(s32*)(AI_STATE(L) + 0x240);
    return *(float*)(ctx + (s64)idx * 4 + 0xb34);
}

// ---------------------------------------------------------------------------
// 0x710036b950 — return_sp_u_cliff_y (24B)
// ---------------------------------------------------------------------------
float return_sp_u_cliff_y_36b950(u64 L) {
    u64 ctx = AI_CTX(L);
    s32 idx = *(s32*)(AI_STATE(L) + 0x240);
    return *(float*)(ctx + (s64)idx * 4 + 0xb44);
}

// ---------------------------------------------------------------------------
// 0x710036b970 — return_goal_x (24B)
// ---------------------------------------------------------------------------
float return_goal_x_36b970(u64 L) {
    u64 ctx = AI_CTX(L);
    s32 idx = *(s32*)(AI_STATE(L) + 0x240);
    return *(float*)(ctx + (s64)idx * 4 + 0xb54);
}

// ---------------------------------------------------------------------------
// 0x710036b990 — return_goal_x_strict (24B)
// ---------------------------------------------------------------------------
float return_goal_x_strict_36b990(u64 L) {
    u64 ctx = AI_CTX(L);
    s32 idx = *(s32*)(AI_STATE(L) + 0x240);
    return *(float*)(ctx + (s64)idx * 4 + 0xb64);
}

// ---------------------------------------------------------------------------
// 0x710036b9b0 — return_goal_pad_x_strict (24B)
// ---------------------------------------------------------------------------
float return_goal_pad_x_strict_36b9b0(u64 L) {
    u64 ctx = AI_CTX(L);
    s32 idx = *(s32*)(AI_STATE(L) + 0x240);
    return *(float*)(ctx + (s64)idx * 4 + 0xb74);
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
// Read from the analyst object at *(ctx + 0x170), double-deref.
// [derived: app::analyst::* in Ghidra, u32 return via ldr w0]

// ---------------------------------------------------------------------------
// 0x7100376a00 — status_prev (20B)
// ---------------------------------------------------------------------------
u32 status_prev_376a00(u64 L) {
    u64 ctx = AI_CTX(L);
    u64 analyst = *(u64*)(*(u64*)(ctx + 0x170));
    return *(u32*)(analyst + 0x10);
}

// ---------------------------------------------------------------------------
// 0x7100376ac0 — status_count (20B)
// ---------------------------------------------------------------------------
u32 status_count_376ac0(u64 L) {
    u64 ctx = AI_CTX(L);
    u64 analyst = *(u64*)(*(u64*)(ctx + 0x170));
    return *(u32*)(analyst + 0x14);
}

// ---------------------------------------------------------------------------
// 0x7100376b90 — chanced_frame (20B)
// ---------------------------------------------------------------------------
u32 chanced_frame_376b90(u64 L) {
    u64 ctx = AI_CTX(L);
    u64 analyst = *(u64*)(*(u64*)(ctx + 0x170));
    return *(u32*)(analyst + 0x1c);
}

// ---- app::ai_system — input/mode control ----

// ---------------------------------------------------------------------------
// 0x71003762f0 — reset_stick (24B)
// [derived: app::ai_system::reset_stick in Ghidra]
// Copies 16-byte zero vector (ConstantZero) to ctx + 0xc30
// Asm: ldr q0,[ConstantZero]; str q0,[ctx+0xc30]
// Uses 128-bit vector copy (stick data is 2 × Vector2f)
// ---------------------------------------------------------------------------
typedef float v4sf __attribute__((vector_size(16)));
void reset_stick_3762f0(u64 L) {
    u64 ctx = AI_CTX(L);
    *reinterpret_cast<v4sf*>(ctx + 0xc30) =
        *reinterpret_cast<const v4sf*>((u64)PTR_ConstantZero_71052a7a80);
}

// ---------------------------------------------------------------------------
// 0x7100376330 — set_action_id_none (24B)
// [derived: app::ai_system::set_action_id_none in Ghidra]
// Saves current action_id to prev, then clears current
// ---------------------------------------------------------------------------
void set_action_id_none_376330(u64 L) {
    u64 ctx = AI_CTX(L);
    u16 current = *(u16*)(ctx + 0x198);
    if (current != 0) {
        *(u16*)(ctx + 0x19a) = current;
    }
    *(u16*)(ctx + 0x198) = 0;
}
