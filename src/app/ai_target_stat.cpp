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
extern "C" AITargetStat* FUN_7100314030(void*, u64);

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
    return FUN_7100314030(DAT_71052b5fd8, reinterpret_cast<u64>(ctx) + 0xc50);
}

// ════════════════════════════════════════════════════════════════════
// check_target_stat_* — AI target status queries
// All resolve target via FUN_7100314030, then compare status_kind (+0x74)
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
    AITargetStat* stat = FUN_7100314030(DAT_71052b5fd8, reinterpret_cast<u64>(ctx) + 0xc50);
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
// Non-matching functions (skipped per 3-attempt rule)
// ════════════════════════════════════════════════════════════════════

// 0x7100368140 — change_action: NON-MATCHING 50% (scheduling: sentinel store order)
// 0x71003681e0 — get_cmd_id_from_req_id: NON-MATCHING (same scheduling issue)
