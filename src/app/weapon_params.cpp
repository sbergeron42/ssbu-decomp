#include "types.h"

// Weapon parameter accessor functions — pool-c
// These read from FighterParamAccessor2 singleton via GOT (non-hidden)

// FighterParamAccessor2 singleton pointer (accessed through GOT, NOT hidden)
// [derived: lib::Singleton<app::FighterParamAccessor2>::instance_]
extern "C" void* DAT_71052bb3b0;

// Helper: FPA2 singleton double-deref + two chained pointer reads + final f32
#define FPA2_PARAM(off1, off2, off3) \
    *reinterpret_cast<f32*>( \
        *reinterpret_cast<u64*>( \
            *reinterpret_cast<u64*>( \
                reinterpret_cast<u8*>(DAT_71052bb3b0) + (off1)) + (off2)) + (off3))

// ════════════════════════════════════════════════════════════════════
// DAISY DAISYDAIKON — probability and power tables (24B each)
// [derived: FPA2+0x380 → +0x158 → final offset]
// ════════════════════════════════════════════════════════════════════

f32 DAISY_DAISYDAIKON_DAIKON_1_PROB_710165be40() { return FPA2_PARAM(0x380, 0x158, 0x40); }
f32 DAISY_DAISYDAIKON_DAIKON_2_PROB_710165be60() { return FPA2_PARAM(0x380, 0x158, 0x44); }
f32 DAISY_DAISYDAIKON_DAIKON_3_PROB_710165be80() { return FPA2_PARAM(0x380, 0x158, 0x48); }
f32 DAISY_DAISYDAIKON_DAIKON_4_PROB_710165bea0() { return FPA2_PARAM(0x380, 0x158, 0x4c); }
f32 DAISY_DAISYDAIKON_DAIKON_5_PROB_710165bec0() { return FPA2_PARAM(0x380, 0x158, 0x50); }
f32 DAISY_DAISYDAIKON_DAIKON_6_PROB_710165bee0() { return FPA2_PARAM(0x380, 0x158, 0x54); }
f32 DAISY_DAISYDAIKON_DAIKON_7_PROB_710165bf00() { return FPA2_PARAM(0x380, 0x158, 0x58); }
f32 DAISY_DAISYDAIKON_DAIKON_8_PROB_710165bf20() { return FPA2_PARAM(0x380, 0x158, 0x5c); }

f32 DAISY_DAISYDAIKON_DAIKON_1_POWER_710165bf40() { return FPA2_PARAM(0x380, 0x158, 0x20); }
f32 DAISY_DAISYDAIKON_DAIKON_2_POWER_710165bf60() { return FPA2_PARAM(0x380, 0x158, 0x24); }
f32 DAISY_DAISYDAIKON_DAIKON_3_POWER_710165bf80() { return FPA2_PARAM(0x380, 0x158, 0x28); }
f32 DAISY_DAISYDAIKON_DAIKON_4_POWER_710165bfa0() { return FPA2_PARAM(0x380, 0x158, 0x2c); }
f32 DAISY_DAISYDAIKON_DAIKON_5_POWER_710165bfc0() { return FPA2_PARAM(0x380, 0x158, 0x30); }
f32 DAISY_DAISYDAIKON_DAIKON_6_POWER_710165bfe0() { return FPA2_PARAM(0x380, 0x158, 0x34); }
f32 DAISY_DAISYDAIKON_DAIKON_7_POWER_710165c000() { return FPA2_PARAM(0x380, 0x158, 0x38); }
f32 DAISY_DAISYDAIKON_DAIKON_8_POWER_710165c020() { return FPA2_PARAM(0x380, 0x158, 0x3c); }

// ════════════════════════════════════════════════════════════════════
// DOLL params (24B each)
// [derived: FPA2+0xc08 → +0x178 → final offset]
// ════════════════════════════════════════════════════════════════════

f32 DOLL_LIFE_710165c3d0()             { return FPA2_PARAM(0xc08, 0x178, 0x34); }
f32 DOLL_REACTION_MUL_710165c3f0()     { return FPA2_PARAM(0xc08, 0x178, 0x0c); }
f32 DOLL_LIFE_DEC_MUL_710165c410()     { return FPA2_PARAM(0xc08, 0x178, 0x38); }
f32 DOLL_SMASH_ACCEL_Y_710165c430()    { return FPA2_PARAM(0xc08, 0x178, 0x20); }
f32 DOLL_SMASH_MAX_SPEED_X_710165c450(){ return FPA2_PARAM(0xc08, 0x178, 0x10); }
f32 DOLL_SMASH_MAX_SPEED_Y_710165c470(){ return FPA2_PARAM(0xc08, 0x178, 0x14); }
f32 DOLL_POWER_MAX_710165c490()        { return FPA2_PARAM(0xc08, 0x178, 0x30); }
f32 DOLL_POWER_MIN_710165c4b0()        { return FPA2_PARAM(0xc08, 0x178, 0x2c); }
f32 DOLL_ROT_SPEED_MAX_710165c4d0()    { return FPA2_PARAM(0xc08, 0x178, 0x28); }
f32 DOLL_ROT_SPEED_MIN_710165c4f0()    { return FPA2_PARAM(0xc08, 0x178, 0x24); }
f32 DOLL_SPEED_Y_710165c510()          { return FPA2_PARAM(0xc08, 0x178, 0x18); }
f32 DOLL_ROT_SPEED_Z_710165c530()      { return FPA2_PARAM(0xc08, 0x178, 0x40); }
f32 DOLL_ROT_Z_RATIO_710165c550()      { return FPA2_PARAM(0xc08, 0x178, 0x44); }
