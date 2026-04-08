#include "types.h"

extern "C" void abort(void) __attribute__((noreturn));

// 0x7101f92e90  size=752 bytes
long FUN_7101f92e90(long param_1, long param_2) { (void)param_1; (void)param_2; return 0; }

// 0x7101f9f860  size=1616 bytes
long FUN_7101f9f860(long param_1, long param_2, long param_3) { (void)param_1; (void)param_2; (void)param_3; return 0; }

extern void friction_off(u64);
// call+return-0 wrapper for friction_off
u64 FUN_7101fa2880(u64 param_1) { friction_off(param_1); asm(""); return 0; }

extern void set_gravity_coefficient(u64);
// call+return-0 wrapper for set_gravity_coefficient
u64 FUN_7101fa2ff0(u64 param_1) { set_gravity_coefficient(param_1); asm(""); return 0; }

extern void EFFECT_FOLLOW_UNSYNC_VIS_WHOLE(u64);
// call+return-0 wrapper for EFFECT_FOLLOW_UNSYNC_VIS_WHOLE
u64 FUN_7101fb3900(u64 param_1) { EFFECT_FOLLOW_UNSYNC_VIS_WHOLE(param_1); asm(""); return 0; }

extern void LANDING_EFFECT_FLIP(u64);
// call+return-0 wrapper for LANDING_EFFECT_FLIP
u64 FUN_7101fb9570(u64 param_1) { LANDING_EFFECT_FLIP(param_1); asm(""); return 0; }

extern void LAST_EFFECT_SET_RATE_WORK(u64);
// call+return-0 wrapper for LAST_EFFECT_SET_RATE_WORK
u64 FUN_7101fb9b10(u64 param_1) { LAST_EFFECT_SET_RATE_WORK(param_1); asm(""); return 0; }

extern void BACK_GROUND_EFFECT_STAGE_SET_HIDING_FOR_DIRECTION(u64);
// call+return-0 wrapper for BACK_GROUND_EFFECT_STAGE_SET_HIDING_FOR_DIRECTION
u64 FUN_7101fbda60(u64 param_1) { BACK_GROUND_EFFECT_STAGE_SET_HIDING_FOR_DIRECTION(param_1); asm(""); return 0; }

extern void UNABLE_AREA(u64);
// call+return-0 wrapper for UNABLE_AREA
u64 FUN_7101fbdca0(u64 param_1) { UNABLE_AREA(param_1); asm(""); return 0; }

extern void QUAKE_STOP(u64);
// call+return-0 wrapper for QUAKE_STOP
u64 FUN_7101fc12c0(u64 param_1) { QUAKE_STOP(param_1); asm(""); return 0; }

extern void SET_SEARCH_SIZE_EXIST(u64);
// call+return-0 wrapper for SET_SEARCH_SIZE_EXIST
u64 FUN_7101fc1cc0(u64 param_1) { SET_SEARCH_SIZE_EXIST(param_1); asm(""); return 0; }

extern void FT_START_ADJUST_MOTION_FRAME_REVISED_arg1(u64);
// call+return-0 wrapper for FT_START_ADJUST_MOTION_FRAME_REVISED_arg1
u64 FUN_7101fc27a0(u64 param_1) { FT_START_ADJUST_MOTION_FRAME_REVISED_arg1(param_1); asm(""); return 0; }

extern void FT_SET_FINAL_SMASH_LIGHT(u64);
// call+return-0 wrapper for FT_SET_FINAL_SMASH_LIGHT
u64 FUN_7101fc2fa0(u64 param_1) { FT_SET_FINAL_SMASH_LIGHT(param_1); asm(""); return 0; }

extern void STOP_SE_arg2(u64);
// call+return-0 wrapper for STOP_SE_arg2
u64 FUN_7101fc3250(u64 param_1) { STOP_SE_arg2(param_1); asm(""); return 0; }

extern void SET_TAKEOUT_SE_STATUS(u64);
// call+return-0 wrapper for SET_TAKEOUT_SE_STATUS
u64 FUN_7101fc3eb0(u64 param_1) { SET_TAKEOUT_SE_STATUS(param_1); asm(""); return 0; }

extern void PLAY_SE_SET_HANDLE(u64);
// call+return-0 wrapper for PLAY_SE_SET_HANDLE
u64 FUN_7101fc43f0(u64 param_1) { PLAY_SE_SET_HANDLE(param_1); asm(""); return 0; }

extern void SHOOT_ITEM_BULLET(u64);
// call+return-0 wrapper for SHOOT_ITEM_BULLET
u64 FUN_7101fc7400(u64 param_1) { SHOOT_ITEM_BULLET(param_1); asm(""); return 0; }

// 0x7101fcc540  size=384 bytes
long FUN_7101fcc540(long param_1, long param_2) { (void)param_1; (void)param_2; return 0; }

// 0x7101fd7ad0  size=288 bytes
long FUN_7101fd7ad0(long param_1, long param_2) { (void)param_1; (void)param_2; return 0; }

// 0x7101fe7db0  size=976 bytes
long FUN_7101fe7db0(long param_1, long param_2) { (void)param_1; (void)param_2; return 0; }

// 0x7101fe8690  size=1616 bytes
long FUN_7101fe8690(long param_1, long param_2, long param_3) { (void)param_1; (void)param_2; (void)param_3; return 0; }

// 0x7101ff51c0  size=448 bytes
long FUN_7101ff51c0(long param_1, long param_2) { (void)param_1; (void)param_2; return 0; }

// 0x7101ff6fb0  size=384 bytes
long FUN_7101ff6fb0(long param_1, long param_2) { (void)param_1; (void)param_2; return 0; }

// 0x7102513280  size=12 bytes — calls abort (pure virtual stub)
void FUN_7102513280(void) { abort(); }

// 0x7102525180  size=1264 bytes
long FUN_7102525180(long param_1, long param_2, long param_3) { (void)param_1; (void)param_2; (void)param_3; return 0; }

// 0x7102528660  size=12 bytes — calls abort (pure virtual stub)
void FUN_7102528660(void) { abort(); }

// 0x71025fc8a0  size=12 � calls abort
void FUN_71025fc8a0(void) { abort(); }

// 0x7102627c10  size=12 bytes — calls abort (pure virtual stub)
void FUN_7102627c10(void) { abort(); }

// 0x710275f250  size=12 bytes — calls abort (pure virtual stub)
void FUN_710275f250(void) { abort(); }

// 0x7102855970  size=12 bytes — calls abort (pure virtual stub)
void FUN_7102855970(void) { abort(); }
