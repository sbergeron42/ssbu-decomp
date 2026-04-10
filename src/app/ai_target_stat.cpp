#include "types.h"
#include "app/placeholders/FighterAI.h"
#include "app/placeholders/AITargetStat.h"

// AI target status checking, attack data accessors, and misc AI helpers.
// All functions in namespace app::ai, operating on FighterAI context via lua_State.

#define HIDDEN __attribute__((visibility("hidden")))

// ════════════════════════════════════════════════════════════════════
// External declarations
// ════════════════════════════════════════════════════════════════════

// Resolve target stat from AI manager + target tracking block address
// [derived: all check_target_stat_* call this with (mgr, ctx+0xc50)]
extern "C" AITargetStat* aiGetTargetById_7100314030(void*, u64);

// Lookup attack data entry by handle + hash40
// [derived: attack_data_x0/x1/y0/y1 call this with (ctx->attack_handle, hash)]
extern "C" AIAttackData* FUN_710033c510(u32, u64);

// AI action dispatch (used by change_action — currently non-matching)
// extern "C" void FUN_71002edd30(void*, u16, void*);

// lib::Singleton<app::FighterAIManager>::instance_
extern "C" void* DAT_71052b5fd8 HIDDEN;

// ════════════════════════════════════════════════════════════════════
// Helpers
// ════════════════════════════════════════════════════════════════════

// Resolve target stat for the AI's current target.
// The target tracking block starts at FighterAI+0xc50 (target_entry_id).
static inline AITargetStat* get_target_stat(u64 L) {
    FighterAI* ctx = get_ai_context(L);
    return aiGetTargetById_7100314030(DAT_71052b5fd8, reinterpret_cast<u64>(ctx) + 0xc50);
}

// ════════════════════════════════════════════════════════════════════
// check_target_stat_* — AI target status queries
// All resolve target via aiGetTargetById_7100314030, then compare status_kind (+0x74)
// ════════════════════════════════════════════════════════════════════

// 0x7100366770 (48B) — check if target is in a "final" state (KO'd / eliminated)
// [derived: app::ai::check_target_stat_final in .dynsym]
bool check_target_stat_final_366770(u64 L) {
    AITargetStat* stat = get_target_stat(L);
    return (stat->final_flags & 3) != 0;
}

// 0x71003669a0 (48B) — check if target is down (status_kind == 4)
// [derived: app::ai::check_target_stat_down in .dynsym]
bool check_target_stat_down_3669a0(u64 L) {
    return get_target_stat(L)->status_kind == 4;
}

// 0x71003669d0 (48B) — check if target is in special fall (status_kind == 0x10)
// [derived: app::ai::check_target_stat_fall_sp in .dynsym]
bool check_target_stat_fall_sp_3669d0(u64 L) {
    return get_target_stat(L)->status_kind == 0x10;
}

// 0x7100366a40 (48B) — check if target is stunned/piyo_l (status_kind == 0xb)
// [derived: app::ai::check_target_stat_piyo_l in .dynsym]
bool check_target_stat_piyo_l_366a40(u64 L) {
    return get_target_stat(L)->status_kind == 0xb;
}

// 0x7100366a70 (48B) — check if target is hit by dragoon (status_kind == 0x11)
// [derived: app::ai::check_target_stat_dragoon in .dynsym]
bool check_target_stat_dragoon_366a70(u64 L) {
    return get_target_stat(L)->status_kind == 0x11;
}

// 0x7100366aa0 (48B) — check if target is on cliff/ledge (status_kind == 6)
// [derived: app::ai::check_target_stat_cliff in .dynsym]
bool check_target_stat_cliff_366aa0(u64 L) {
    return get_target_stat(L)->status_kind == 6;
}

// 0x7100366ad0 (48B) — check if target is acting from cliff (status_kind == 7)
// [derived: app::ai::check_target_stat_cliff_act in .dynsym]
bool check_target_stat_cliff_act_366ad0(u64 L) {
    return get_target_stat(L)->status_kind == 7;
}

// 0x7100366a00 (52B) — check if target is in any piyo state (status_kind 9, 10, or 11)
// [derived: app::ai::check_target_stat_piyo in .dynsym]
bool check_target_stat_piyo_366a00(u64 L) {
    return (u32)(get_target_stat(L)->status_kind - 9) < 3;
}

// 0x7100366b00 (48B) — check if target is caught (status_kind == 0xc)
// [derived: app::ai::check_target_stat_catch in .dynsym]
bool check_target_stat_catch_366b00(u64 L) {
    return get_target_stat(L)->status_kind == 0xc;
}

// 0x7100366b30 (48B) — check if target is in damage (status_kind == 5)
// [derived: app::ai::check_target_stat_damage in .dynsym]
bool check_target_stat_damage_366b30(u64 L) {
    return get_target_stat(L)->status_kind == 5;
}

// 0x7100366b60 (48B) — check if target is guarding (status_kind == 0x1a)
// [derived: app::ai::check_target_stat_guard in .dynsym]
bool check_target_stat_guard_366b60(u64 L) {
    return get_target_stat(L)->status_kind == 0x1a;
}

// 0x7100366b90 (48B) — check if target is escaping (status_kind == 0x1e)
// [derived: app::ai::check_target_stat_escape in .dynsym]
bool check_target_stat_escape_366b90(u64 L) {
    return get_target_stat(L)->status_kind == 0x1e;
}

// 0x7100366bc0 (48B) — check if target is in rebirth (status_kind == 0x1f)
// [derived: app::ai::check_target_stat_rebirth in .dynsym]
bool check_target_stat_rebirth_366bc0(u64 L) {
    return get_target_stat(L)->status_kind == 0x1f;
}

// 0x7100366800 (92B) — check target invincibility (long form)
// [derived: app::ai::check_target_stat_invincible_l in .dynsym]
// Mirror of check_stat_invincible_l but operating on the resolved target stat.
// Order matters: final_flags bit 5 gate, flags_0x5e bit 4 early-true, invinc_counter > 0,
// then status_kind ∈ {0x11, 0x12, 0xb}.
bool check_target_stat_invincible_l_366800(u64 L) {
    AITargetStat* stat = get_target_stat(L);
    if (((stat->final_flags >> 5) & 1) == 0) {
        return false;
    }
    if ((stat->flags_0x5e >> 4) & 1) {
        return true;
    }
    if (stat->invinc_counter > 0) {
        return true;
    }
    s32 k = stat->status_kind;
    return (u32)(k - 0x11) < 2 || k == 0xb;
}

// ════════════════════════════════════════════════════════════════════
// target_* — AI target property accessors (non-stat, typed)
// ════════════════════════════════════════════════════════════════════

// 0x71003611c0 (24B) — AI's current target battle object id
// [derived: app::ai::target_id in .dynsym; reads *(stat->+0x10) + 8]
s32 target_id_3611c0(u64 L) {
    AITargetStat* stat = get_target_stat(L);
    return *reinterpret_cast<s32*>(reinterpret_cast<u8*>(stat->battle_object_id_holder) + 8);
}

// 0x71003665f0 (24B) — target's fighter_kind (FighterKind enum)
// [derived: app::ai::target_fighter_kind in .dynsym]
s32 target_fighter_kind_3665f0(u64 L) {
    return get_target_stat(L)->fighter_kind;
}

// 0x7100366620 (24B) — target's copy_fighter_kind (mimic/echo kind)
// [derived: app::ai::target_copy_fighter_kind in .dynsym]
s32 target_copy_fighter_kind_366620(u64 L) {
    return get_target_stat(L)->copy_fighter_kind;
}

// 0x7100366f00 (148B) — target's remaining jump budget, gated by state
// [derived: app::ai::target_jump_rest_available in .dynsym]
// Gates:
//   status_kind == 0x10 (fall_sp) → 0
//   flags_0x59 bit 5 set → 0
//   fighter_kind == 0x22 AND flags_0x68 bit 2 clear → 0
//   fighter_kind == 0x29 AND flags_0x68 bit 0 set → 0
//   otherwise → jump_rest (u16)
// NOTE: expected asm checks 0x22 first then 0x29. Written inverted so Clang 8's
// block layout inlines the 0x29 path and makes 0x22 the out-of-line target.
u16 target_jump_rest_available_366f00(u64 L) {
    AITargetStat* stat = get_target_stat(L);
    if (stat->status_kind == 0x10) {
        return 0;
    }
    if ((stat->flags_0x59 >> 5) & 1) {
        return 0;
    }
    s32 kind = stat->fighter_kind;
    if (kind == 0x29) {
        if (stat->flags_0x68 & 1) {
            return 0;
        }
    } else if (kind == 0x22 && ((stat->flags_0x68 >> 2) & 1) == 0) {
        return 0;
    }
    return stat->jump_rest;
}

// NOTE: is_target_on_same_floor_3672b0 and check_target_over_ground_367b00
// already exist in src/app/ai_helpers_a.cpp (pool-a territory). Do not redefine here.

// ════════════════════════════════════════════════════════════════════
// analyst::target_* — target status history (direct manager table lookup)
// These bypass aiGetTargetById_7100314030 and read from
// manager->analyst_entries[clamp(entry_id, 0x10)].
// Leaf functions, no frame — note the guard pattern: sign bit, self-check, clamp.
// IMPORTANT:
//  1. No null check on the entry pointer — the table is assumed dense.
//  2. Manager-chain load must appear in C BEFORE the clamp so that x9
//     (holding the entries pointer) is live across the csel, forcing the
//     0x10 constant into w10 rather than reusing w9.
// ════════════════════════════════════════════════════════════════════

// 0x7100376a20 (80B, leaf) — target's current tracked status
// [derived: app::analyst::target_status in .dynsym]
u32 target_status_376a20(u64 L) {
    FighterAI* ctx = get_ai_context(L);
    s32 entry_id = ctx->target_entry_id;
    if (entry_id < 0) return 0;
    if ((u32)entry_id == ctx->parent_entry_id) return 0;
    FighterAIManager* mgr = *reinterpret_cast<FighterAIManager**>(DAT_71052b5fd8);
    AIAnalyst** entries = mgr->analyst_entries;
    u32 idx = (u32)entry_id < 0x10 ? (u32)entry_id : 0x10u;
    return entries[idx]->status;
}

// 0x7100376a70 (80B, leaf) — target's previous status before current
// [derived: app::analyst::target_status_prev in .dynsym]
u32 target_status_prev_376a70(u64 L) {
    FighterAI* ctx = get_ai_context(L);
    s32 entry_id = ctx->target_entry_id;
    if (entry_id < 0) return 0;
    if ((u32)entry_id == ctx->parent_entry_id) return 0;
    FighterAIManager* mgr = *reinterpret_cast<FighterAIManager**>(DAT_71052b5fd8);
    AIAnalyst** entries = mgr->analyst_entries;
    u32 idx = (u32)entry_id < 0x10 ? (u32)entry_id : 0x10u;
    return entries[idx]->status_prev;
}

// 0x7100376ae0 (80B, leaf) — frames spent in current status
// [derived: app::analyst::target_status_count in .dynsym]
u32 target_status_count_376ae0(u64 L) {
    FighterAI* ctx = get_ai_context(L);
    s32 entry_id = ctx->target_entry_id;
    if (entry_id < 0) return 0;
    if ((u32)entry_id == ctx->parent_entry_id) return 0;
    FighterAIManager* mgr = *reinterpret_cast<FighterAIManager**>(DAT_71052b5fd8);
    AIAnalyst** entries = mgr->analyst_entries;
    u32 idx = (u32)entry_id < 0x10 ? (u32)entry_id : 0x10u;
    return entries[idx]->status_count;
}

// 0x7100376bb0 (80B, leaf) — frame when target's current status became chanced
// [derived: app::analyst::target_chanced_frame in .dynsym]
u32 target_chanced_frame_376bb0(u64 L) {
    FighterAI* ctx = get_ai_context(L);
    s32 entry_id = ctx->target_entry_id;
    if (entry_id < 0) return 0;
    if ((u32)entry_id == ctx->parent_entry_id) return 0;
    FighterAIManager* mgr = *reinterpret_cast<FighterAIManager**>(DAT_71052b5fd8);
    AIAnalyst** entries = mgr->analyst_entries;
    u32 idx = (u32)entry_id < 0x10 ? (u32)entry_id : 0x10u;
    return entries[idx]->chanced_frame;
}

// ════════════════════════════════════════════════════════════════════
// attack_data_* — attack bounding rect queries
// All lookup attack data via FUN_710033c510(ctx->attack_handle, hash40)
// ════════════════════════════════════════════════════════════════════

// Helper: get attack data handle from FighterAI+0x988
// [derived: all attack_data_* load u32 from ctx+0x988]
static inline u32 get_attack_handle(FighterAI* ctx) {
    return *reinterpret_cast<u32*>(reinterpret_cast<u8*>(ctx) + 0x988);
}

// 0x7100369c10 (48B) — get attack rect x0 (left bound)
// [derived: app::ai::attack_data_x0 in .dynsym]
f32 attack_data_x0_369c10(u64 L, u64 hash40) {
    FighterAI* ctx = get_ai_context(L);
    AIAttackData* data = FUN_710033c510(get_attack_handle(ctx), hash40);
    if (data != nullptr) {
        return data->x0;
    }
    return 0.0f;
}

// 0x7100369c40 (48B) — get attack rect x1 (right bound)
// [derived: app::ai::attack_data_x1 in .dynsym]
f32 attack_data_x1_369c40(u64 L, u64 hash40) {
    FighterAI* ctx = get_ai_context(L);
    AIAttackData* data = FUN_710033c510(get_attack_handle(ctx), hash40);
    if (data != nullptr) {
        return data->x1;
    }
    return 0.0f;
}

// 0x7100369c70 (48B) — get attack rect y0 (bottom bound)
// [derived: app::ai::attack_data_y0 in .dynsym]
f32 attack_data_y0_369c70(u64 L, u64 hash40) {
    FighterAI* ctx = get_ai_context(L);
    AIAttackData* data = FUN_710033c510(get_attack_handle(ctx), hash40);
    if (data != nullptr) {
        return data->y0;
    }
    return 0.0f;
}

// 0x7100369ca0 (48B) — get attack rect y1 (top bound)
// [derived: app::ai::attack_data_y1 in .dynsym]
f32 attack_data_y1_369ca0(u64 L, u64 hash40) {
    FighterAI* ctx = get_ai_context(L);
    AIAttackData* data = FUN_710033c510(get_attack_handle(ctx), hash40);
    if (data != nullptr) {
        return data->y1;
    }
    return 0.0f;
}

// ════════════════════════════════════════════════════════════════════
// Misc AI helpers
// ════════════════════════════════════════════════════════════════════

// 0x7100368190 (48B) — check if update count is divisible by 3
// [derived: app::ai::is_update_count_odd in .dynsym]
// NOTE: Despite the name "odd", this actually checks divisibility by 3.
bool is_update_count_odd_368190(u64 L) {
    FighterAI* ctx = get_ai_context(L);
    s32 count = ctx->update_count;
    return count == (count / 3) * 3;
}

// ════════════════════════════════════════════════════════════════════
// is_valid_target — combined target resolution + validity check
// ════════════════════════════════════════════════════════════════════

// 0x71003611f0 (84B) — check if AI has a valid target
// [derived: app::ai::is_valid_target in .dynsym]
// Resolves target stat, then checks entry_id >= 0, != self, and not flagged dead (bit 3).
bool is_valid_target_3611f0(u64 L) {
    FighterAI* ctx = get_ai_context(L);
    AITargetStat* stat = aiGetTargetById_7100314030(DAT_71052b5fd8, reinterpret_cast<u64>(ctx) + 0xc50);
    bool invalid;
    if (ctx->target_entry_id < 0 || ctx->target_entry_id == (s32)ctx->parent_entry_id) {
        invalid = true;
    } else {
        invalid = (stat->final_flags & 8) != 0;
    }
    return !invalid;
}

// ════════════════════════════════════════════════════════════════════
// check_stat_* — FighterAIState field checks (ground/air/chr/floor)
// ════════════════════════════════════════════════════════════════════

// 0x7100361670 (88B) — check if target is in a "ground free" state
// [derived: app::ai::check_stat_ground_free in .dynsym]
// Checks multiple conditions on FighterAIState flags/uniq_stat.
u64 check_stat_ground_free_361670(u64 L) {
    FighterAIState* state = get_ai_context(L)->state;
    if ((state->stat_flags >> 30) & 1) return 0;
    if (state->uniq_stat == 1) return 1;
    u32 flags_64 = *reinterpret_cast<u32*>(reinterpret_cast<u8*>(state) + 0x64);
    if (((~flags_64) & 0x99) == 0) return 1;
    if ((state->stat_flags & 1) == 0 && (s8)state->unk_0x58 < 0) return 1;
    return 0;
}

// 0x7100361740 (88B) — check if target is in an "air free" state
// [derived: app::ai::check_stat_air_free in .dynsym]
// Mirror of ground_free for airborne checks.
u64 check_stat_air_free_361740(u64 L) {
    FighterAIState* state = get_ai_context(L)->state;
    if ((state->stat_flags >> 30) & 1) return 0;
    if (state->uniq_stat == 2) return 1;
    u32 flags_64 = *reinterpret_cast<u32*>(reinterpret_cast<u8*>(state) + 0x64);
    if ((~flags_64 & 0xE00) == 0) return 1;
    if ((state->stat_flags & 1) != 0 && (s8)state->unk_0x58 < 0) return 1;
    return 0;
}

// 0x7100361a60 (56B) — check character-specific status flag
// [derived: app::ai::check_chr_stat in .dynsym]
// If fighter_kind matches (or param_3 == -1), checks bitmask against chr status flags.
u64 check_chr_stat_361a60(u64 L, u32 char_status, s32 fighter_kind) {
    FighterAIState* state = get_ai_context(L)->state;
    if ((fighter_kind == -1 || (s32)state->fighter_kind == fighter_kind) &&
        (*reinterpret_cast<u32*>(reinterpret_cast<u8*>(state) + 0x68) & char_status) != 0) {
        return 1;
    }
    return 0;
}

// 0x7100361640 (48B) — check if floor deals damage
// [derived: app::ai::check_stat_floor_damage in .dynsym]
// Checks: floor state at +0xd8 != 2 AND floor_data->flags_0x5e bit 0 is set.
u64 check_stat_floor_damage_361640(u64 L) {
    FighterAIState* state = get_ai_context(L)->state;
    s32 floor_state = *reinterpret_cast<s32*>(reinterpret_cast<u8*>(state) + 0xd8);
    if (floor_state != 2 && (state->floor_data->flags_0x5e & 1) != 0) {
        return 1;
    }
    return 0;
}

// ════════════════════════════════════════════════════════════════════
// check_stat_* extended — ground/air/command/invincibility checks
// ════════════════════════════════════════════════════════════════════

// 0x71003616d0 (100B) — check if target is in "ground free 2" state (variant with status_kind filter)
// [derived: app::ai::check_stat_ground_free2 in .dynsym]
u64 check_stat_ground_free2_3616d0(u64 L) {
    FighterAIState* state = get_ai_context(L)->state;
    if ((state->stat_flags >> 30) & 1) return 0;
    if (state->uniq_stat == 1 && state->status_kind != 0x17) return 1;
    u32 flags_64 = *reinterpret_cast<u32*>(reinterpret_cast<u8*>(state) + 0x64);
    if ((~flags_64 & 0x99) == 0) return 1;
    if ((state->stat_flags & 1) == 0 && (s8)state->unk_0x58 < 0) return 1;
    return 0;
}

// 0x71003613f0 (92B) — check if fighter is invincible (long form)
// [derived: app::ai::check_stat_invincible_l in .dynsym]
// Checks stat_flags bit 13, floor flags, invincibility counter, and uniq_stat.
bool check_stat_invincible_l_3613f0(u64 L) {
    FighterAIState* state = get_ai_context(L)->state;
    if (((state->stat_flags >> 13) & 1) == 0) {
        return false;
    }
    if ((state->unk_0x5a[4] >> 4) & 1) {
        return true;
    }
    s32 invinc_counter = *reinterpret_cast<s32*>(&state->unk_0xf8[0x24]);
    if (invinc_counter > 0) {
        return true;
    }
    return (u32)(state->uniq_stat - 0x11) < 2 || state->uniq_stat == 0xb;
}

// 0x7100361ad0 (68B) — check if fighter can grab cliff (position-based)
// [derived: app::ai::check_cliffable in .dynsym]
// NON-MATCHING: 29% (5/17 — float load scheduling: binary loads all from floor_data before computing)
// Selects left (0x40) or right (0x80) mask based on position vs floor center,
// then checks against floor collision flags at +0x5c.
bool check_cliffable_361ad0(u64 L) {
    FighterAIState* state = get_ai_context(L)->state;
    AIFloorCollisionData* floor = state->floor_data;
    f32 left = floor->left_edge;
    f32 right = floor->right_edge;
    u32 floor_flags = *reinterpret_cast<u32*>(reinterpret_cast<u8*>(floor) + 0x5c);
    u32 mask = 0x40;
    if ((left + right) * 0.5f <= state->pos_x) {
        mask = 0x80;
    }
    return (mask & floor_flags) != 0;
}

// 0x7100361d70 (88B) — check if AI should use command input
// [derived: app::ai::check_use_command in .dynsym]
// Returns 1 if fighter_kind is 0x3c/0x3d, or copy_fighter_kind is and action_id matches.
u64 check_use_command_361d70(u64 L) {
    FighterAI* ctx = get_ai_context(L);
    FighterAIState* state = ctx->state;
    if ((state->fighter_kind & ~1u) == 0x3c) return 1;
    if ((state->copy_fighter_kind & ~1u) == 0x3c) {
        s16 action = ctx->action_id;
        if (action == 0x6038 || action == 0x6046) return 1;
    }
    return 0;
}

// ════════════════════════════════════════════════════════════════════
// check_command_*_step — command input recognition by fighter kind
// All check fighter_kind against specific values and test flag bits.
// ════════════════════════════════════════════════════════════════════

// 0x7100361ec0 (92B) — check 41236 (half-circle forward) command step
// [derived: app::ai::check_command_41236_step in .dynsym]
u64 check_command_41236_step_361ec0(u64 L) {
    FighterAIState* state = get_ai_context(L)->state;
    s32 kind = state->fighter_kind;
    if (kind == 6) {
        if ((state->unk_0x69[0] >> 2) & 1) return 1;
    } else if (kind == 0x3d) {
        if ((state->flags_0x68 >> 4) & 1) return 1;
    } else if (kind == 0x3c && ((state->flags_0x68 >> 4) & 1)) {
        return 1;
    }
    return 0;
}

// 0x7100361f20 (92B) — check 214 (quarter-circle back) command step
// [derived: app::ai::check_command_214_step in .dynsym]
u64 check_command_214_step_361f20(u64 L) {
    FighterAIState* state = get_ai_context(L)->state;
    s32 kind = state->fighter_kind;
    if (kind == 0x55) {
        if ((state->flags_0x68 >> 4) & 1) return 1;
    } else if (kind == 0x3d) {
        if ((state->flags_0x68 >> 5) & 1) return 1;
    } else if (kind == 0x3c && ((state->flags_0x68 >> 5) & 1)) {
        return 1;
    }
    return 0;
}

// 0x7100361f80 (92B) — check 623 (dragon punch) command step
// [derived: app::ai::check_command_623_step in .dynsym]
u64 check_command_623_step_361f80(u64 L) {
    FighterAIState* state = get_ai_context(L)->state;
    s32 kind = state->fighter_kind;
    if (kind == 0x55) {
        if ((state->flags_0x68 >> 5) & 1) return 1;
    } else if (kind == 0x3d) {
        if ((state->flags_0x68 >> 6) & 1) return 1;
    } else if (kind == 0x3c && ((state->flags_0x68 >> 6) & 1)) {
        return 1;
    }
    return 0;
}

// ════════════════════════════════════════════════════════════════════
// Non-matching functions (skipped per 3-attempt rule)
// ════════════════════════════════════════════════════════════════════

// 0x7100368140 — change_action: NON-MATCHING 50% (scheduling: sentinel store order)
// 0x71003681e0 — get_cmd_id_from_req_id: NON-MATCHING (same scheduling issue)
