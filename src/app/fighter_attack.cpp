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
