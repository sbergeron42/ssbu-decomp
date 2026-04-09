#include "types.h"
#include "app/BattleObjectModuleAccessor.h"
#include "app/modules/AttackModule.h"
#include "app/modules/WorkModule.h"

// Fighter attack/combat AI helper functions — pool-e
// Decompiled from Ghidra analysis of SSBU 13.0.4

#define HIDDEN __attribute__((visibility("hidden")))

using namespace app;

// ---- External declarations --------------------------------------------------

// AI target lookup: resolves target battle object from AI context
// [derived: used by all target_* AI property accessors]
extern "C" u64 FUN_7100314030(void*, void*);

// BattleObjectWorld singleton — used for target resolution
// [derived: DAT_71052b5fd8 in Ghidra, passed as first arg to FUN_7100314030]
extern "C" void* DAT_71052b5fd8 HIDDEN;

// ---- AI target property accessors ------------------------------------------
// Family of 10 functions, each 40 bytes, all follow the same pattern:
//   1. Look up target info via FUN_7100314030(DAT_71052b5fd8, *(L-8) + 0xc50)
//   2. Return a specific field from the result struct
// The target info struct layout is inferred from field offsets across the family.
//
// Target info struct (partial):
//   +0x2c [inferred: status_kind, s32]
//   +0x38 [inferred: motion_kind, u64 / Hash40]
//   +0x48 [inferred: motion_frame, f32]
//   +0x80 [inferred: pos_x, f32]
//   +0x84 [inferred: pos_y, f32]
//   +0xa0 [inferred: speed_x, f32]
//   +0xa4 [inferred: speed_y, f32]
//   +0xc0 [inferred: scale, f32]
//   +0xc4 [inferred: lr, f32]
//   +0xc8 [inferred: height, f32]

// 0x7100366de0 (40 bytes) — app::ai::target_height
extern "C" f32 target_height(u64 L) {
    u64 ctx = *(u64*)(L - 8);
    u64 info = FUN_7100314030(DAT_71052b5fd8, (void*)(ctx + 0xc50));
    return *(f32*)(info + 0xc8);
}

// 0x7100366e10 (40 bytes) — app::ai::target_pos_x
extern "C" f32 target_pos_x(u64 L) {
    u64 ctx = *(u64*)(L - 8);
    u64 info = FUN_7100314030(DAT_71052b5fd8, (void*)(ctx + 0xc50));
    return *(f32*)(info + 0x80);
}

// 0x7100366e40 (40 bytes) — app::ai::target_pos_y
extern "C" f32 target_pos_y(u64 L) {
    u64 ctx = *(u64*)(L - 8);
    u64 info = FUN_7100314030(DAT_71052b5fd8, (void*)(ctx + 0xc50));
    return *(f32*)(info + 0x84);
}

// 0x7100366e70 (40 bytes) — app::ai::target_speed_x
extern "C" f32 target_speed_x(u64 L) {
    u64 ctx = *(u64*)(L - 8);
    u64 info = FUN_7100314030(DAT_71052b5fd8, (void*)(ctx + 0xc50));
    return *(f32*)(info + 0xa0);
}

// 0x7100366ea0 (40 bytes) — app::ai::target_speed_y
extern "C" f32 target_speed_y(u64 L) {
    u64 ctx = *(u64*)(L - 8);
    u64 info = FUN_7100314030(DAT_71052b5fd8, (void*)(ctx + 0xc50));
    return *(f32*)(info + 0xa4);
}

// 0x7100366ed0 (40 bytes) — app::ai::target_scale
extern "C" f32 target_scale(u64 L) {
    u64 ctx = *(u64*)(L - 8);
    u64 info = FUN_7100314030(DAT_71052b5fd8, (void*)(ctx + 0xc50));
    return *(f32*)(info + 0xc0);
}

// 0x7100366fc0 (40 bytes) — app::ai::target_lr
extern "C" f32 target_lr(u64 L) {
    u64 ctx = *(u64*)(L - 8);
    u64 info = FUN_7100314030(DAT_71052b5fd8, (void*)(ctx + 0xc50));
    return *(f32*)(info + 0xc4);
}

// 0x7100366ff0 (40 bytes) — app::ai::target_status_kind
extern "C" u32 target_status_kind(u64 L) {
    u64 ctx = *(u64*)(L - 8);
    u64 info = FUN_7100314030(DAT_71052b5fd8, (void*)(ctx + 0xc50));
    return *(u32*)(info + 0x2c);
}

// 0x7100367020 (40 bytes) — app::ai::target_motion_kind
// Returns Hash40 (u64) — motion animation hash
extern "C" u64 target_motion_kind(u64 L) {
    u64 ctx = *(u64*)(L - 8);
    u64 info = FUN_7100314030(DAT_71052b5fd8, (void*)(ctx + 0xc50));
    return *(u64*)(info + 0x38);
}

// 0x7100367050 (40 bytes) — app::ai::target_motion_frame
extern "C" f32 target_motion_frame(u64 L) {
    u64 ctx = *(u64*)(L - 8);
    u64 info = FUN_7100314030(DAT_71052b5fd8, (void*)(ctx + 0xc50));
    return *(f32*)(info + 0x48);
}

// has_air_catch at 0x7100375f20: SKIPPED — leaf scheduling differs (NX compiler
// generates redundant mov w8,w8 zero-extension that upstream Clang 8 optimizes out)

// ---- Stage status dispatchers (kiiladarzmanager) ---------------------------
// All four functions: load StageManager singleton, get sub-module at +0x128,
// call vtable[0x228/8] with (sub-module, status_code, 0).
// Kiila/Darz are Ultimate's Hands boss characters.

// lib::Singleton<app::StageManager>::instance_
// [derived: used by all set_stage_status_* functions, deref to get StageManager*]
extern "C" void* DAT_710532e7a0 HIDDEN;

// 0x7101653650 (36 bytes) — app::kiiladarzmanager::set_stage_status_default
// Sets stage status to 0x2f (default/neutral)
extern "C" void set_stage_status_default() {
    u8* mgr = *(u8**)DAT_710532e7a0;
    u8* sub = mgr + 0x128;
    void** vt = *(void***)sub;
    reinterpret_cast<void(*)(void*, s32, s32)>(vt[0x228 / 8])(sub, 0x2f, 0);
}

// 0x7101653680 (36 bytes) — app::kiiladarzmanager::set_stage_status_kiila_and_darz
// Sets stage status to 0x30 (both Kiila and Darz active)
extern "C" void set_stage_status_kiila_and_darz() {
    u8* mgr = *(u8**)DAT_710532e7a0;
    u8* sub = mgr + 0x128;
    void** vt = *(void***)sub;
    reinterpret_cast<void(*)(void*, s32, s32)>(vt[0x228 / 8])(sub, 0x30, 0);
}

// 0x71016536b0 (36 bytes) — app::kiiladarzmanager::set_stage_status_kiila
// Sets stage status to 0x31 (only Kiila active)
extern "C" void set_stage_status_kiila() {
    u8* mgr = *(u8**)DAT_710532e7a0;
    u8* sub = mgr + 0x128;
    void** vt = *(void***)sub;
    reinterpret_cast<void(*)(void*, s32, s32)>(vt[0x228 / 8])(sub, 0x31, 0);
}

// 0x71016536e0 (36 bytes) — app::kiiladarzmanager::set_stage_status_darz
// Sets stage status to 0x32 (only Darz active)
extern "C" void set_stage_status_darz() {
    u8* mgr = *(u8**)DAT_710532e7a0;
    u8* sub = mgr + 0x128;
    void** vt = *(void***)sub;
    reinterpret_cast<void(*)(void*, s32, s32)>(vt[0x228 / 8])(sub, 0x32, 0);
}

// set_slow_whole @ 0x71015c1690: SKIPPED — NX Clang generates frame for tail call thunks,
// upstream Clang 8 optimizes to frameless leaf (20B vs 36B)
// begin_scale_animation_simple @ 0x71015c1170: SKIPPED — same NX tail-call frame issue

// ---- AI stat check functions (all leaf, 32 bytes each) ---------------------
// Family of 28+ functions that read single-bit flags from the AI battle object
// state bitfields. All follow the same pointer chain:
//   *(L-8) → +0x168 → battle object state struct
// Then read a byte/word at a specific offset and extract one bit.
//
// Battle object state bitfield layout (partial, from +0x54):
//   +0x54 bit 0: air         +0x55 bit 1: final_act     +0x56 bit 4: sp_dir
//   +0x54 bit 2: build_max   +0x55 bit 5: invincible    +0x56 bit 5: unguarded_hind
//   +0x54 bit 3: build_up    +0x58 bit 0: touch_l       +0x56 bit 6: unguarded
//   +0x54 bit 5: gorogoro    +0x58 bit 1: touch_r       +0x58 bit 4: cannot_catch_cliff
//   +0x54 bit 6: attention   +0x58 bit 2: touch_u       +0x58 bit 5: dive
//   +0x59 bit 1: unable_cliff_xlu   +0x59 bit 4: unable_special  +0x5c bit 0: have
//   +0x59 bit 2: unable_escape_air  +0x59 bit 5: unable_jump     +0x5c bit 1: put_bomb
//   +0x59 bit 6: unable_shield      +0x5c bit 4: can_use_superleaf
//   +0x5c bit 5: can_use_rocketbelt +0x5d bit 4: have_throw
//   +0x5d bit 5: have_shoot  +0x5d bit 6: have_swing
//   +0x60 bit 4: dogs_blind_own  +0x60 bit 6: target_invisible

// Helper macro for the common pointer chain
#define AI_STATE(L) (*(u64*)(*(u64*)(L - 8) + 0x168))

// 0x71003612f0 — check_stat_air (word load, bit 0)
extern "C" u32 check_stat_air(u64 L) { return *(u32*)(AI_STATE(L) + 0x54) & 1; }
// 0x7100361310 — check_stat_build_max (byte load, bit 2)
extern "C" u8 check_stat_build_max(u64 L) { return (*(u8*)(AI_STATE(L) + 0x54) >> 2) & 1; }
// 0x7100361330 — check_stat_build_up (byte load, bit 3)
extern "C" u8 check_stat_build_up(u64 L) { return (*(u8*)(AI_STATE(L) + 0x54) >> 3) & 1; }
// 0x7100361350 — check_stat_gorogoro (word load, multi-bit bitmask)
extern "C" bool check_stat_gorogoro(u64 L) {
    return (*(u32*)(AI_STATE(L) + 0x54) & 0x80020) != 0;
}
// 0x7100361370 — check_stat_attention (byte load, bit 6)
extern "C" u8 check_stat_attention(u64 L) { return (*(u8*)(AI_STATE(L) + 0x54) >> 6) & 1; }
// 0x71003613b0 — check_stat_final_act (byte load at +0x55, bit 1)
extern "C" u8 check_stat_final_act(u64 L) { return (*(u8*)(AI_STATE(L) + 0x55) >> 1) & 1; }
// 0x71003613d0 — check_stat_invincible (byte load at +0x55, bit 5)
extern "C" u8 check_stat_invincible(u64 L) { return (*(u8*)(AI_STATE(L) + 0x55) >> 5) & 1; }
// 0x7100361470 — check_stat_sp_dir (byte load at +0x56, bit 4)
extern "C" u8 check_stat_sp_dir(u64 L) { return (*(u8*)(AI_STATE(L) + 0x56) >> 4) & 1; }
// 0x7100361490 — check_stat_unguarded_hind (byte load at +0x56, bit 5)
extern "C" u8 check_stat_unguarded_hind(u64 L) { return (*(u8*)(AI_STATE(L) + 0x56) >> 5) & 1; }
// 0x71003614b0 — check_stat_unguarded (byte load at +0x56, bit 6)
extern "C" u8 check_stat_unguarded(u64 L) { return (*(u8*)(AI_STATE(L) + 0x56) >> 6) & 1; }
// 0x71003617a0 — check_stat_touch_u (byte load at +0x58, bit 2)
extern "C" u8 check_stat_touch_u(u64 L) { return (*(u8*)(AI_STATE(L) + 0x58) >> 2) & 1; }
// 0x71003617c0 — check_stat_touch_l (word load at +0x58, bit 0)
extern "C" u32 check_stat_touch_l(u64 L) { return *(u32*)(AI_STATE(L) + 0x58) & 1; }
// 0x71003617e0 — check_stat_touch_r (byte load at +0x58, bit 1)
extern "C" u8 check_stat_touch_r(u64 L) { return (*(u8*)(AI_STATE(L) + 0x58) >> 1) & 1; }
// 0x7100361800 — check_stat_cannot_catch_cliff (byte load at +0x58, bit 4)
extern "C" u8 check_stat_cannot_catch_cliff(u64 L) { return (*(u8*)(AI_STATE(L) + 0x58) >> 4) & 1; }
// 0x7100361820 — check_stat_dive (byte load at +0x58, bit 5)
extern "C" u8 check_stat_dive(u64 L) { return (*(u8*)(AI_STATE(L) + 0x58) >> 5) & 1; }
// 0x7100361840 — check_stat_unable_cliff_xlu (byte load at +0x59, bit 1)
extern "C" u8 check_stat_unable_cliff_xlu(u64 L) { return (*(u8*)(AI_STATE(L) + 0x59) >> 1) & 1; }
// 0x7100361860 — check_stat_unable_escape_air (byte load at +0x59, bit 2)
extern "C" u8 check_stat_unable_escape_air(u64 L) { return (*(u8*)(AI_STATE(L) + 0x59) >> 2) & 1; }
// 0x71003618a0 — check_stat_unable_special (byte load at +0x59, bit 4)
extern "C" u8 check_stat_unable_special(u64 L) { return (*(u8*)(AI_STATE(L) + 0x59) >> 4) & 1; }
// 0x71003618c0 — check_stat_unable_jump (byte load at +0x59, bit 5)
extern "C" u8 check_stat_unable_jump(u64 L) { return (*(u8*)(AI_STATE(L) + 0x59) >> 5) & 1; }
// 0x71003618e0 — check_stat_unable_shield (byte load at +0x59, bit 6)
extern "C" u8 check_stat_unable_shield(u64 L) { return (*(u8*)(AI_STATE(L) + 0x59) >> 6) & 1; }
// 0x7100361900 — check_stat_have (word load at +0x5c, bit 0)
extern "C" u32 check_stat_have(u64 L) { return *(u32*)(AI_STATE(L) + 0x5c) & 1; }
// 0x7100361920 — check_stat_put_bomb (byte load at +0x5c, bit 1)
extern "C" u8 check_stat_put_bomb(u64 L) { return (*(u8*)(AI_STATE(L) + 0x5c) >> 1) & 1; }
// 0x7100361940 — check_stat_can_use_superleaf (byte load at +0x5c, bit 4)
extern "C" u8 check_stat_can_use_superleaf(u64 L) { return (*(u8*)(AI_STATE(L) + 0x5c) >> 4) & 1; }
// 0x7100361960 — check_stat_can_use_rocketbelt (byte load at +0x5c, bit 5)
extern "C" u8 check_stat_can_use_rocketbelt(u64 L) { return (*(u8*)(AI_STATE(L) + 0x5c) >> 5) & 1; }
// 0x7100361980 — check_stat_have_throw (byte load at +0x5d, bit 4)
extern "C" u8 check_stat_have_throw(u64 L) { return (*(u8*)(AI_STATE(L) + 0x5d) >> 4) & 1; }
// 0x71003619a0 — check_stat_have_shoot (byte load at +0x5d, bit 5)
extern "C" u8 check_stat_have_shoot(u64 L) { return (*(u8*)(AI_STATE(L) + 0x5d) >> 5) & 1; }
// 0x71003619c0 — check_stat_have_swing (byte load at +0x5d, bit 6)
extern "C" u8 check_stat_have_swing(u64 L) { return (*(u8*)(AI_STATE(L) + 0x5d) >> 6) & 1; }
// 0x71003619e0 — check_stat_dogs_blind_own (byte load at +0x60, bit 4)
extern "C" u8 check_stat_dogs_blind_own(u64 L) { return (*(u8*)(AI_STATE(L) + 0x60) >> 4) & 1; }
// 0x7100361a00 — check_stat_target_invisible (byte load at +0x60, bit 6)
extern "C" u8 check_stat_target_invisible(u64 L) { return (*(u8*)(AI_STATE(L) + 0x60) >> 6) & 1; }

// ---- AI check_stat — status/state queries (comparisons, multi-field) -------
// These check higher-level fighter state: status_kind (+0x74), action category (+0x64),
// situation (+0xd8), and composite conditions for "free to act" logic.
//
// AI fighter state struct additions (partial):
//   +0x10 [inferred: fighter BattleObject pointer]
//   +0x2c [inferred: sub_status_kind, s32 — ground_free2 excludes 0x17]
//   +0x55 bits 0-1 [derived: final smash active, from check_stat_final name]
//   +0x5e bit 4 [inferred: super armor active]
//   +0x64 [inferred: action_category flags, u32 — ground=0x99, air=0xe00]
//   +0x74 [derived: status_kind, s32 — used by all status comparisons]
//   +0xd0 [inferred: ground collision data pointer]
//     +0x5c bit 5 [inferred: platform passthrough available]
//   +0xd8 [inferred: situation_kind, s32 — 0 = ground]
//   +0x11c [inferred: invincible timer, s32 — > 0 means invincible]

// 0x7100361390 — check_stat_final (bits 0-1 of +0x55)
// [derived: final smash active or pending, from Ghidra function name]
extern "C" bool check_stat_final(u64 L) {
    return (*(u8*)(AI_STATE(L) + 0x55) & 3) != 0;
}
// 0x71003613f0 — check_stat_invincible_l (complex invincibility check, 92B)
// [derived: checks invincible flag, super armor, timer, and special statuses]
extern "C" bool check_stat_invincible_l(u64 L) {
    u64 ai = AI_STATE(L);
    if (((*(u8*)(ai + 0x55) >> 5) & 1) == 0) {
        return false;
    }
    if (((*(u8*)(ai + 0x5e) >> 4) & 1) != 0) {
        return true;
    }
    if (*(s32*)(ai + 0x11c) > 0) {
        return true;
    }
    s32 status = *(s32*)(ai + 0x74);
    // NOTE: orr operand order mismatch — upstream emits orr w0,w8,w9 vs NX orr w0,w9,w8
    return (u32)(status - 0x11) < 2 || status == 0xb;
}
// 0x71003614d0 — check_stat_dash (status_kind == 3)
extern "C" bool check_stat_dash(u64 L) {
    return *(s32*)(AI_STATE(L) + 0x74) == 3;
}
// 0x71003614f0 — check_stat_down (status_kind == 4)
extern "C" bool check_stat_down(u64 L) {
    return *(s32*)(AI_STATE(L) + 0x74) == 4;
}
// 0x7100361510 — check_stat_piyo (status_kind in [9, 10, 11] — dizzy)
extern "C" bool check_stat_piyo(u64 L) {
    return (u32)(*(s32*)(AI_STATE(L) + 0x74) - 9) < 3;
}
// 0x7100361530 — check_stat_dragoon (status_kind == 0x11)
extern "C" bool check_stat_dragoon(u64 L) {
    return *(s32*)(AI_STATE(L) + 0x74) == 0x11;
}
// 0x7100361550 — check_stat_genesis (status_kind == 0x12)
extern "C" bool check_stat_genesis(u64 L) {
    return *(s32*)(AI_STATE(L) + 0x74) == 0x12;
}
// 0x7100361570 — check_stat_catch (status_kind == 0xc — grab)
extern "C" bool check_stat_catch(u64 L) {
    return *(s32*)(AI_STATE(L) + 0x74) == 0xc;
}
// 0x71003615b0 — check_stat_guard (status_kind == 0x1a — shield)
extern "C" bool check_stat_guard(u64 L) {
    return *(s32*)(AI_STATE(L) + 0x74) == 0x1a;
}
// 0x71003615f0 — check_stat_floor_pass (80B, platform passthrough / GroundModule query)
// [derived: grounded + platform bit → true; else if fighter ground type >= 4, tail-calls GroundModule vtable[0x9f]]
// +0x10 → +0x3a [inferred: ground type byte, >= 4 means special ground handling]
// +0x10 → +0x20 = accessor → +0x58 = GroundModule → vtable[0x9f] (offset 0x4f8)
extern "C" bool check_stat_floor_pass(u64 L) {
    u64 ai = AI_STATE(L);
    if (*(s32*)(ai + 0xd8) == 0) {
        if ((*(u8*)(*(u64*)(ai + 0xd0) + 0x5c) >> 5) & 1) {
            return true;
        }
    }
    u64 fighter = *(u64*)(ai + 0x10);
    if (*(u8*)(fighter + 0x3a) >= 4) {
        u64 acc = *(u64*)(fighter + 0x20);
        u64 ground = *(u64*)(acc + 0x58);
        u64* vt = *(u64**)ground;
        return reinterpret_cast<bool(*)(u64)>(vt[0x9f])(ground);
    }
    return false;
}
// 0x7100361670 — check_stat_ground_free (88B, can act on ground)
// [derived: true if fighter is free to act while grounded]
// +0x54 bit 30 [inferred: action_lock, blocks all free checks]
// +0x54 bit 0 [derived: air flag, from check_stat_air]
// +0x58 bit 7 [inferred: special ground action pending]
extern "C" bool check_stat_ground_free(u64 L) {
    u64 ai = AI_STATE(L);
    u32 flags = *(u32*)(ai + 0x54);
    if ((flags >> 30) & 1) {
        return false;
    }
    if (*(s32*)(ai + 0x74) == 1) {
        return true;
    }
    if ((~*(u32*)(ai + 0x64) & 0x99) == 0) {
        return true;
    }
    if (!(flags & 1)) {
        u32 b58 = *(u8*)(ai + 0x58);
#ifdef MATCHING_HACK_NX_CLANG
        asm("" : "+r"(b58));
#endif
        if (b58 & 0x80) return true;
    }
    return false;
}
// 0x71003616d0 — check_stat_ground_free2 (100B, ground free with sub-status filter)
// [derived: like ground_free but excludes sub_status 0x17]
// +0x2c [inferred: sub_status_kind, value 0x17 excluded]
extern "C" bool check_stat_ground_free2(u64 L) {
    u64 ai = AI_STATE(L);
    u32 flags = *(u32*)(ai + 0x54);
    if ((flags >> 30) & 1) {
        return false;
    }
    if (*(s32*)(ai + 0x74) == 1 && *(s32*)(ai + 0x2c) != 0x17) {
        return true;
    }
    if ((~*(u32*)(ai + 0x64) & 0x99) == 0) {
        return true;
    }
    if (!(flags & 1)) {
        u32 b58 = *(u8*)(ai + 0x58);
#ifdef MATCHING_HACK_NX_CLANG
        asm("" : "+r"(b58));
#endif
        if (b58 & 0x80) return true;
    }
    return false;
}
// 0x7100361740 — check_stat_air_free (88B, can act in air)
// [derived: true if fighter is free to act while airborne]
// Uses air bitmask 0xe00 instead of ground bitmask 0x99
extern "C" bool check_stat_air_free(u64 L) {
    u64 ai = AI_STATE(L);
    u32 flags = *(u32*)(ai + 0x54);
    if ((flags >> 30) & 1) {
        return false;
    }
    if (*(s32*)(ai + 0x74) == 2) {
        return true;
    }
    if ((~*(u32*)(ai + 0x64) & 0xe00) == 0) {
        return true;
    }
    if (flags & 1) {
        u32 b58 = *(u8*)(ai + 0x58);
#ifdef MATCHING_HACK_NX_CLANG
        asm("" : "+r"(b58));
#endif
        if (b58 & 0x80) return true;
    }
    return false;
}

// ---- AI state queries — skill/spirits/character status, misc ---------------
// These continue the AI state struct at AI_STATE(L):
//   +0x28 [derived: fighter_kind, FighterKind enum, from check_chr_stat]
//   +0x68 [derived: character_status flags, u32, from check_chr_stat]
//   +0x6c [derived: skill_status flags, u32, from check_skill_stat]
//   +0x70 [derived: spirits_event_status flags, u32, from check_spirits_event_stat]
//   +0x80 [inferred: pos_x, f32, from check_cliffable]
//   +0xd0 [inferred: ground collision data pointer]
//     +0x20 [inferred: cliff_left_x, f32]
//     +0x30 [inferred: cliff_right_x, f32]
//     +0x5c [inferred: ground flags — bit5: passable, bit6: cliff_left, bit7: cliff_right]
//   +0xe8 [inferred: current shield HP, f32]
//   +0xec [inferred: max shield HP, f32]
//   +0x1f4 [inferred: secondary fighter_kind, u32]

extern "C" void FUN_7100358c20(u64, s32);

// 0x7100361a20 — check_skill_stat (24B, bitmask test at +0x6c)
// [derived: tests skill status flags against param mask]
extern "C" bool check_skill_stat(u64 L, u32 mask) {
    return (*(u32*)(AI_STATE(L) + 0x6c) & mask) != 0;
}
// 0x7100361a40 — check_spirits_event_stat (24B, bitmask test at +0x70)
// [derived: tests spirits event status flags against param mask]
extern "C" bool check_spirits_event_stat(u64 L, u32 mask) {
    return (*(u32*)(AI_STATE(L) + 0x70) & mask) != 0;
}
// 0x7100361a60 — check_chr_stat (56B, character-specific status check)
// [derived: checks fighter_kind match (or -1 for any), then tests character status mask at +0x68]
extern "C" bool check_chr_stat(u64 L, u32 mask, s32 kind) {
    u64 ai = AI_STATE(L);
    if ((kind == -1 || *(s32*)(ai + 0x28) == kind) &&
        (*(u32*)(ai + 0x68) & mask) != 0) {
        return true;
    }
    return false;
}
// 0x7100361b50 — check_passable (24B, platform passthrough flag)
// [derived: reads bit 5 from ground_data->0x5c, same field as check_stat_floor_pass]
extern "C" u8 check_passable(u64 L) {
    return (*(u8*)(*(u64*)(AI_STATE(L) + 0xd0) + 0x5c) >> 5) & 1;
}
// 0x7100361b70 — shield_rate (20B, current shield health ratio)
// [derived: divides current shield HP by max shield HP]
extern "C" f32 shield_rate(u64 L) {
    u64 ai = AI_STATE(L);
    return *(f32*)(ai + 0xe8) / *(f32*)(ai + 0xec);
}
// 0x7100361ce0 — is_sp_u_available (16B, tail-call)
// [derived: checks if up-special is available, passes AI state + mode 0]
extern "C" void is_sp_u_available(u64 L) {
    FUN_7100358c20(AI_STATE(L), 0);
}
// 0x7100361cf0 — is_sp_u_weaken_available (16B, tail-call)
// [derived: checks if weakened up-special is available, passes AI state + mode 1]
extern "C" void is_sp_u_weaken_available(u64 L) {
    FUN_7100358c20(AI_STATE(L), 1);
}
// 0x7100361ad0 — check_cliffable (68B, cliff grab availability)
// [derived: checks if fighter is near enough to cliff edge to grab it]
// Compares pos_x to midpoint of cliff left/right, selects appropriate side flag
extern "C" bool check_cliffable(u64 L) {
    u64 ctx = *(u64*)(L - 8);
    u64 ai = *(u64*)(ctx + 0x168);
    u64 ground = *(u64*)(ai + 0xd0);
    u32 mask = 0x40;
    if ((*(f32*)(ground + 0x20) + *(f32*)(ground + 0x30)) * 0.5f <= *(f32*)(ai + 0x80)) {
        mask = 0x80;
    }
    return (mask & *(u32*)(ground + 0x5c)) != 0;
}
// 0x7100361b20 — check_cliffable_floor_lr (44B, cliff grab direction check)
// [derived: checks cliff availability in specified direction]
// dir > 0 → check left cliff (bit 6), else check right cliff (bit 7)
extern "C" bool check_cliffable_floor_lr(u64 L, f32 dir) {
    u32 mask = 0x40;
    if (!(dir > 0.0f)) {
        mask = 0x80;
    }
    return (*(u32*)(*(u64*)(AI_STATE(L) + 0xd0) + 0x5c) & mask) != 0;
}
// 0x71003611f0 — is_valid_target (84B, target validity check)
// [derived: validates that AI target is not self and not in invincible state (bit 3 of +0x55)]
// +0xc50 [inferred: target battle_object_id, s32, in ctx]
// +0x160 [inferred: own battle_object_id, s32, in ctx]
extern "C" bool is_valid_target(u64 L) {
    u64 ctx = *(u64*)(L - 8);
    u64 info = FUN_7100314030(DAT_71052b5fd8, (void*)(ctx + 0xc50));
    if (*(s32*)(ctx + 0xc50) < 0 || *(s32*)(ctx + 0xc50) == *(s32*)(ctx + 0x160)) {
        return false;
    }
    return (*(u8*)(info + 0x55) & 8) == 0;
}
// 0x7100361d70 — check_use_command (88B, command input active check)
// [derived: checks if current fighter is using a command input (motion input)]
// +0x28 [derived: fighter_kind, FighterKind]
// +0x1f4 [inferred: secondary fighter_kind, u32]
// +0x198 [inferred: command_id, s16, in ctx — 0x6038/0x6046 are specific command IDs]
extern "C" bool check_use_command(u64 L) {
    u64 ctx = *(u64*)(L - 8);
    u64 ai = *(u64*)(ctx + 0x168);
    if ((*(u32*)(ai + 0x28) & 0xfffffffe) == 0x3c) {
        return true;
    }
    if ((*(u32*)(ai + 0x1f4) & 0xfffffffe) == 0x3c) {
        s16 cmd = *(s16*)(ctx + 0x198);
        if (cmd == 0x6038 || cmd == 0x6046) {
            return true;
        }
    }
    return false;
}

// ---- AI command input step checkers ----------------------------------------
// These check if a specific motion input command step is active, based on
// fighter_kind (+0x28) and character_status bits (+0x68/+0x69).
// Names reflect traditional fighting game numpad notation (214 = QCB, 623 = DP, etc.)

// 0x7100361ec0 — check_command_41236_step (92B)
// [derived: half-circle forward command step, 3-way kind switch]
extern "C" bool check_command_41236_step(u64 L) {
    u64 ai = AI_STATE(L);
    s32 kind = *(s32*)(ai + 0x28);
    if (kind == 6) {
        if ((*(u8*)(ai + 0x69) >> 2) & 1) return true;
    } else if (kind == 0x3d) {
        if ((*(u8*)(ai + 0x68) >> 4) & 1) return true;
    } else if (kind == 0x3c && ((*(u8*)(ai + 0x68) >> 4) & 1)) {
        return true;
    }
    return false;
}
// 0x7100361f20 — check_command_214_step (92B)
// [derived: quarter-circle back command step]
extern "C" bool check_command_214_step(u64 L) {
    u64 ai = AI_STATE(L);
    s32 kind = *(s32*)(ai + 0x28);
    if (kind == 0x55) {
        if ((*(u8*)(ai + 0x68) >> 4) & 1) return true;
    } else if (kind == 0x3d) {
        if ((*(u8*)(ai + 0x68) >> 5) & 1) return true;
    } else if (kind == 0x3c && ((*(u8*)(ai + 0x68) >> 5) & 1)) {
        return true;
    }
    return false;
}
// 0x7100361f80 — check_command_623_step (92B)
// [derived: dragon punch command step]
extern "C" bool check_command_623_step(u64 L) {
    u64 ai = AI_STATE(L);
    s32 kind = *(s32*)(ai + 0x28);
    if (kind == 0x55) {
        if ((*(u8*)(ai + 0x68) >> 5) & 1) return true;
    } else if (kind == 0x3d) {
        if ((*(u8*)(ai + 0x68) >> 6) & 1) return true;
    } else if (kind == 0x3c && ((*(u8*)(ai + 0x68) >> 6) & 1)) {
        return true;
    }
    return false;
}
// 0x7100361fe0 — check_command_236236_step (44B)
// [derived: double quarter-circle forward command step]
extern "C" bool check_command_236236_step(u64 L) {
    u64 ai = AI_STATE(L);
    if (*(s32*)(ai + 0x28) == 0x55) {
        u32 b68 = *(u8*)(ai + 0x68);
#ifdef MATCHING_HACK_NX_CLANG
        asm("" : "+r"(b68));
#endif
        if (b68 & 0x80) return true;
    }
    return false;
}
// 0x7100362010 — check_command_21416_step (44B)
// [derived: 21416 command step]
extern "C" bool check_command_21416_step(u64 L) {
    u64 ai = AI_STATE(L);
    if (*(s32*)(ai + 0x28) == 0x55 && (*(u8*)(ai + 0x69) & 1)) {
        return true;
    }
    return false;
}
// 0x7100362040 — check_command_214214_step (44B)
// [derived: double quarter-circle back command step]
extern "C" bool check_command_214214_step(u64 L) {
    u64 ai = AI_STATE(L);
    if (*(s32*)(ai + 0x28) == 0x55 && ((*(u8*)(ai + 0x69) >> 1) & 1)) {
        return true;
    }
    return false;
}
// 0x7100362070 — check_command_23634_step (44B)
// [derived: 23634 command step]
extern "C" bool check_command_23634_step(u64 L) {
    u64 ai = AI_STATE(L);
    if (*(s32*)(ai + 0x28) == 0x55 && ((*(u8*)(ai + 0x69) >> 2) & 1)) {
        return true;
    }
    return false;
}

// ---- AI target state queries (target info via FUN_7100314030) ---------------
// Target info struct mirrors the local AI state but for the opponent.
// Obtained by calling FUN_7100314030(BattleObjectWorld, ctx + 0xc50).
// Field layout matches the AI state struct at the same offsets.

// 0x71003666e0 — check_target_stat_air (44B, word load, bit 0)
extern "C" u32 check_target_stat_air(u64 L) {
    u64 ctx = *(u64*)(L - 8);
    u64 info = FUN_7100314030(DAT_71052b5fd8, (void*)(ctx + 0xc50));
    return *(u32*)(info + 0x54) & 1;
}
// 0x7100366710 — check_target_stat_build_up (44B, byte load, bit 3)
extern "C" u8 check_target_stat_build_up(u64 L) {
    u64 ctx = *(u64*)(L - 8);
    u64 info = FUN_7100314030(DAT_71052b5fd8, (void*)(ctx + 0xc50));
    return (*(u8*)(info + 0x54) >> 3) & 1;
}
// 0x7100366740 — check_target_stat_attention (44B, byte load, bit 6)
extern "C" u8 check_target_stat_attention(u64 L) {
    u64 ctx = *(u64*)(L - 8);
    u64 info = FUN_7100314030(DAT_71052b5fd8, (void*)(ctx + 0xc50));
    return (*(u8*)(info + 0x54) >> 6) & 1;
}
// 0x7100366770 — check_target_stat_final (48B, byte load, bits 0-1)
extern "C" bool check_target_stat_final(u64 L) {
    u64 ctx = *(u64*)(L - 8);
    u64 info = FUN_7100314030(DAT_71052b5fd8, (void*)(ctx + 0xc50));
    return (*(u8*)(info + 0x55) & 3) != 0;
}
// 0x71003667a0 — check_target_stat_dead (44B, byte load, bit 3)
extern "C" u8 check_target_stat_dead(u64 L) {
    u64 ctx = *(u64*)(L - 8);
    u64 info = FUN_7100314030(DAT_71052b5fd8, (void*)(ctx + 0xc50));
    return (*(u8*)(info + 0x55) >> 3) & 1;
}
// 0x71003667d0 — check_target_stat_invincible (44B, byte load, bit 5)
extern "C" u8 check_target_stat_invincible(u64 L) {
    u64 ctx = *(u64*)(L - 8);
    u64 info = FUN_7100314030(DAT_71052b5fd8, (void*)(ctx + 0xc50));
    return (*(u8*)(info + 0x55) >> 5) & 1;
}
// 0x71003668b0 — check_target_stat_reflect (44B, byte load at +0x56, bit 2)
extern "C" u8 check_target_stat_reflect(u64 L) {
    u64 ctx = *(u64*)(L - 8);
    u64 info = FUN_7100314030(DAT_71052b5fd8, (void*)(ctx + 0xc50));
    return (*(u8*)(info + 0x56) >> 2) & 1;
}
// 0x71003668e0 — check_target_stat_unguarded_hind (44B, byte load at +0x56, bit 5)
extern "C" u8 check_target_stat_unguarded_hind(u64 L) {
    u64 ctx = *(u64*)(L - 8);
    u64 info = FUN_7100314030(DAT_71052b5fd8, (void*)(ctx + 0xc50));
    return (*(u8*)(info + 0x56) >> 5) & 1;
}
// 0x7100366910 — check_target_stat_unguarded (44B, byte load at +0x56, bit 6)
extern "C" u8 check_target_stat_unguarded(u64 L) {
    u64 ctx = *(u64*)(L - 8);
    u64 info = FUN_7100314030(DAT_71052b5fd8, (void*)(ctx + 0xc50));
    return (*(u8*)(info + 0x56) >> 6) & 1;
}
// 0x7100366940 — check_target_stat_combo (44B, byte load at +0x56, bit 7)
extern "C" u8 check_target_stat_combo(u64 L) {
    u64 ctx = *(u64*)(L - 8);
    u64 info = FUN_7100314030(DAT_71052b5fd8, (void*)(ctx + 0xc50));
    return *(u8*)(info + 0x56) >> 7;
}
// 0x7100366970 — check_target_stat_no_counter (44B, byte load at +0x57, bit 5)
extern "C" u8 check_target_stat_no_counter(u64 L) {
    u64 ctx = *(u64*)(L - 8);
    u64 info = FUN_7100314030(DAT_71052b5fd8, (void*)(ctx + 0xc50));
    return (*(u8*)(info + 0x57) >> 5) & 1;
}
// 0x71003669a0 — check_target_stat_down (48B, status_kind == 4)
extern "C" bool check_target_stat_down(u64 L) {
    u64 ctx = *(u64*)(L - 8);
    u64 info = FUN_7100314030(DAT_71052b5fd8, (void*)(ctx + 0xc50));
    return *(s32*)(info + 0x74) == 4;
}
// 0x71003669d0 — check_target_stat_fall_sp (48B, status_kind == 0x10)
extern "C" bool check_target_stat_fall_sp(u64 L) {
    u64 ctx = *(u64*)(L - 8);
    u64 info = FUN_7100314030(DAT_71052b5fd8, (void*)(ctx + 0xc50));
    return *(s32*)(info + 0x74) == 0x10;
}

// 0x7100366a00 — check_target_stat_piyo (52B, status_kind in [9,10,11])
extern "C" bool check_target_stat_piyo(u64 L) {
    u64 ctx = *(u64*)(L - 8);
    u64 info = FUN_7100314030(DAT_71052b5fd8, (void*)(ctx + 0xc50));
    return (u32)(*(s32*)(info + 0x74) - 9) < 3;
}
// 0x7100366a40 — check_target_stat_piyo_l (48B, status_kind == 0xb)
extern "C" bool check_target_stat_piyo_l(u64 L) {
    u64 ctx = *(u64*)(L - 8);
    u64 info = FUN_7100314030(DAT_71052b5fd8, (void*)(ctx + 0xc50));
    return *(s32*)(info + 0x74) == 0xb;
}
// 0x7100366a70 — check_target_stat_dragoon (48B, status_kind == 0x11)
extern "C" bool check_target_stat_dragoon(u64 L) {
    u64 ctx = *(u64*)(L - 8);
    u64 info = FUN_7100314030(DAT_71052b5fd8, (void*)(ctx + 0xc50));
    return *(s32*)(info + 0x74) == 0x11;
}
// 0x7100366aa0 — check_target_stat_cliff (48B, status_kind == 6)
extern "C" bool check_target_stat_cliff(u64 L) {
    u64 ctx = *(u64*)(L - 8);
    u64 info = FUN_7100314030(DAT_71052b5fd8, (void*)(ctx + 0xc50));
    return *(s32*)(info + 0x74) == 6;
}
// 0x7100366ad0 — check_target_stat_cliff_act (48B, status_kind == 7)
extern "C" bool check_target_stat_cliff_act(u64 L) {
    u64 ctx = *(u64*)(L - 8);
    u64 info = FUN_7100314030(DAT_71052b5fd8, (void*)(ctx + 0xc50));
    return *(s32*)(info + 0x74) == 7;
}
// 0x7100366b00 — check_target_stat_catch (48B, status_kind == 0xc)
extern "C" bool check_target_stat_catch(u64 L) {
    u64 ctx = *(u64*)(L - 8);
    u64 info = FUN_7100314030(DAT_71052b5fd8, (void*)(ctx + 0xc50));
    return *(s32*)(info + 0x74) == 0xc;
}
// 0x7100366b60 — check_target_stat_guard (48B, status_kind == 0x1a)
extern "C" bool check_target_stat_guard(u64 L) {
    u64 ctx = *(u64*)(L - 8);
    u64 info = FUN_7100314030(DAT_71052b5fd8, (void*)(ctx + 0xc50));
    return *(s32*)(info + 0x74) == 0x1a;
}
// 0x7100366b90 — check_target_stat_escape (48B, status_kind == 0x1e)
extern "C" bool check_target_stat_escape(u64 L) {
    u64 ctx = *(u64*)(L - 8);
    u64 info = FUN_7100314030(DAT_71052b5fd8, (void*)(ctx + 0xc50));
    return *(s32*)(info + 0x74) == 0x1e;
}
// 0x7100366bc0 — check_target_stat_rebirth (48B, status_kind == 0x1f)
extern "C" bool check_target_stat_rebirth(u64 L) {
    u64 ctx = *(u64*)(L - 8);
    u64 info = FUN_7100314030(DAT_71052b5fd8, (void*)(ctx + 0xc50));
    return *(s32*)(info + 0x74) == 0x1f;
}
// 0x7100366c70 — check_target_stat_squat (44B, byte at +0x58, bit 6)
extern "C" u8 check_target_stat_squat(u64 L) {
    u64 ctx = *(u64*)(L - 8);
    u64 info = FUN_7100314030(DAT_71052b5fd8, (void*)(ctx + 0xc50));
    return (*(u8*)(info + 0x58) >> 6) & 1;
}
// 0x7100366cd0 — check_target_stat_unable_special (44B, byte at +0x59, bit 4)
extern "C" u8 check_target_stat_unable_special(u64 L) {
    u64 ctx = *(u64*)(L - 8);
    u64 info = FUN_7100314030(DAT_71052b5fd8, (void*)(ctx + 0xc50));
    return (*(u8*)(info + 0x59) >> 4) & 1;
}
// 0x7100366d00 — check_target_stat_specialflag_hoist (44B, byte at +0x5c, bit 7)
extern "C" u8 check_target_stat_specialflag_hoist(u64 L) {
    u64 ctx = *(u64*)(L - 8);
    u64 info = FUN_7100314030(DAT_71052b5fd8, (void*)(ctx + 0xc50));
    return *(u8*)(info + 0x5c) >> 7;
}

// 0x7100366d30 — check_target_chr_stat (96B, character-specific target status check)
// [derived: like check_chr_stat but for target fighter]
extern "C" bool check_target_chr_stat(u64 L, u32 mask, s32 kind) {
    u64 ctx = *(u64*)(L - 8);
    u64 info = FUN_7100314030(DAT_71052b5fd8, (void*)(ctx + 0xc50));
    if ((kind == -1 || *(s32*)(info + 0x28) == kind) &&
        (*(u32*)(info + 0x68) & mask) != 0) {
        return true;
    }
    return false;
}
// 0x7100366d90 — target_width (68B, target fighter width)
// [derived: returns target's collision width (param_base->0xb2c * scale), or 3.0 if no battle object]
// +0x20 [inferred: target BattleObject pointer]
// +0xb2c [inferred: base collision width, f32, in BattleObject]
// +0xc0 [inferred: scale, f32]
extern "C" f32 target_width(u64 L) {
    u64 ctx = *(u64*)(L - 8);
    u64 info = FUN_7100314030(DAT_71052b5fd8, (void*)(ctx + 0xc50));
    if (*(u64*)(info + 0x20) != 0) {
        return *(f32*)(*(u64*)(info + 0x20) + 0xb2c) * *(f32*)(info + 0xc0);
    }
    return 3.0f;
}

// ---- Boss manager queries (leaf, singleton access) -------------------------

// lib::Singleton<app::BossManager>::instance_
// [derived: address 0x71052b7ef8 from adrp+ldr in is_boss_stop disassembly]
extern "C" void* DAT_71052b7ef8 HIDDEN;

// 0x71015c8bf0 (40 bytes) — app::boss_private::is_boss_stop
// Returns true if boss stop count > 0. BossManager at +8 → data at +0x164.
// +0x8 [inferred: BossManager instance data pointer]
// +0x164 [inferred: boss stop count, s32]
extern "C" bool is_boss_stop() {
    void* mgr = DAT_71052b7ef8;
    if (mgr == nullptr) return false;
    u8* data = *(u8**)((u8*)mgr + 8);
    return *(s32*)(data + 0x164) > 0;
}

// 0x71015c8c20 (40 bytes) — app::boss_private::is_boss_no_dead
// Returns true if boss no-dead flag is set.
// +0x14e [inferred: no-dead flag, u8]
extern "C" bool is_boss_no_dead() {
    void* mgr = DAT_71052b7ef8;
    if (mgr == nullptr) return false;
    u8* data = *(u8**)((u8*)mgr + 8);
    return *(u8*)(data + 0x14e) != 0;
}

// ---- AI stage/rule queries (leaf, singleton tail-call or field read) --------

// lib::Singleton<app::FighterManager>::instance_
// [derived: address 0x71052b84f8 from adrp+ldr in is_hp disassembly]
extern "C" void* DAT_71052b84f8 HIDDEN;

extern "C" u32 FUN_7100314d50(u32);
extern "C" u32 FUN_7100314dc0(u32);

// 0x710036b220 (32 bytes) — app::ai_stage::is_small
// Reads stage param from BattleObjectWorld, passes to stage size check
// DAT_71052b5fd8 [derived: BattleObjectWorld singleton, same as target_* functions]
// +0x150 [inferred: stage param index, u32]
extern "C" u32 is_small() {
    u8* world = *(u8**)DAT_71052b5fd8;
    return FUN_7100314d50(*(u32*)(world + 0x150));
}

// 0x710036b380 (32 bytes) — app::ai_stage::is_1on1
// Same pattern as is_small but different check function
extern "C" u32 is_1on1() {
    u8* world = *(u8**)DAT_71052b5fd8;
    return FUN_7100314dc0(*(u32*)(world + 0x150));
}

// 0x710036b680 (32 bytes) — app::ai_rule::is_hp
// Returns true if HP mode is active (byte at FighterManager+0xc3)
// DAT_71052b84f8 [derived: FighterManager singleton]
// +0xc3 [inferred: HP mode flag, u8]
extern "C" u8 is_hp() {
    u8* mgr = *(u8**)DAT_71052b84f8;
    return *(u8*)(mgr + 0xc3);
}

// ---- Item param accessors (leaf, singleton + indexed array load) ------------

// lib::Singleton<app::ItemParamAccessor>::instance_
// [derived: address 0x71052c31e0 from adrp+ldr in game_param_float disassembly]
extern "C" void* DAT_71052c31e0 HIDDEN;

// 0x71015bfa00 (32 bytes) — app::item::game_param_float
// Reads float from ItemParamAccessor's game param table at base offset 0x72f08
// First param (x0) is lua_State (unused), second param (w1) is index
extern "C" f32 game_param_float(u64 L, u32 idx) {
    u8* acc = *(u8**)DAT_71052c31e0;
    return *(f32*)(acc + (u64)idx * 4 + 0x72f08);
}

// 0x71015bfa20 (32 bytes) — app::item::game_param_int
// Same pattern, base offset 0x72fe8, returns u32
extern "C" u32 game_param_int(u64 L, u32 idx) {
    u8* acc = *(u8**)DAT_71052c31e0;
    return *(u32*)(acc + (u64)idx * 4 + 0x72fe8);
}

// 0x71015c4e00 (32 bytes) — app::item::assist_param_float
// Only one param (w0) is index, base offset 0x73060
extern "C" f32 assist_param_float(u32 idx) {
    u8* acc = *(u8**)DAT_71052c31e0;
    return *(f32*)(acc + (u64)idx * 4 + 0x73060);
}

// 0x71015c4e20 (32 bytes) — app::item::assist_param_int
// Same pattern, base offset 0x73140, returns u32
extern "C" u32 assist_param_int(u32 idx) {
    u8* acc = *(u8**)DAT_71052c31e0;
    return *(u32*)(acc + (u64)idx * 4 + 0x73140);
}

// ---- Camera query (leaf, singleton access) ---------------------------------

// [inferred: camera mode/state pointer-to-pointer]
// [derived: address 0x71052b7f00 from adrp+ldr in is_photo_camera disassembly]
extern "C" void* DAT_71052b7f00 HIDDEN;

// 0x7100696bb0 (40 bytes) — app::FighterUtil::is_photo_camera
// Returns true if current camera mode is photo (value 2 at *ptr + 4).
// +0x4 [inferred: camera mode enum, s32, 2=photo]
extern "C" bool is_photo_camera() {
    if (DAT_71052b7f00 == nullptr) return false;
    return *(s32*)(*(u8**)DAT_71052b7f00 + 4) == 2;
}

// ---- Boss common param (leaf, indexed array lookup from ItemParamAccessor) ---

// 0x71015c79e0 (64 bytes) — app::boss_private::common_param_float
// Reads a float from the boss common param table indexed by ItemKind and param slot.
// [derived: common_param_float (community name) — check pointer at kind*8+0xef8,
//  then read float at kind*100+param*4+0x73188]
f32 common_param_float_71015c79e0(s32 kind, u32 param_idx) {
    u8* acc = *(u8**)DAT_71052c31e0;
    if (*(u64*)(acc + (s64)kind * 8 + 0xef8) == 0) {
        return 0.0f;
    }
    return *(f32*)(acc + (s64)kind * 100 + (u64)param_idx * 4 + 0x73188);
}
