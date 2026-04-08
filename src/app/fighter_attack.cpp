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
