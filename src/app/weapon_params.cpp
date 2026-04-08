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
f32 DOLL_MIN_DEGREE_Y_710165c610()     { return FPA2_PARAM(0xc08, 0x178, 0x3c); }
f32 DOLL_MAX_DEGREE_Y_710165c630()     { return FPA2_PARAM(0xc08, 0x178, 0x40); }

// DOLL_SHAPE_TYPE uses a different chain: FPA2+0xc08 → +0x1c0 → deref (offset 0)
// [derived: double pointer dereference at end — single value pointer]
f32 DOLL_SHAPE_TYPE_710165c5f0() {
    u8* fpa2 = reinterpret_cast<u8*>(DAT_71052bb3b0);
    void* p1 = *reinterpret_cast<void**>(
        *reinterpret_cast<u64*>(fpa2 + 0xc08) + 0x1c0);
    return *reinterpret_cast<f32*>(p1);
}

// ════════════════════════════════════════════════════════════════════
// EXPLOSIONBOMB params (24B each)
// [derived: FPA2+0x3f0 → +0x108 → final offset]
// ════════════════════════════════════════════════════════════════════

f32 EXPLOSIONBOMB_GRAVITY_710165d2c0()          { return FPA2_PARAM(0x3f0, 0x108, 0x00); }
f32 EXPLOSIONBOMB_LIMIT_GRAVITY_710165d2e0()    { return FPA2_PARAM(0x3f0, 0x108, 0x04); }
f32 EXPLOSIONBOMB_HOP_SPEED_MUL_X_710165d300()  { return FPA2_PARAM(0x3f0, 0x108, 0x08); }
f32 EXPLOSIONBOMB_HOP_SPEED_Y_710165d320()      { return FPA2_PARAM(0x3f0, 0x108, 0x0c); }
f32 EXPLOSIONBOMB_BOUND_SPEED_MUL_X_710165d360(){ return FPA2_PARAM(0x3f0, 0x108, 0x10); }
f32 EXPLOSIONBOMB_BOUND_SPEED_MUL_Y_710165d380(){ return FPA2_PARAM(0x3f0, 0x108, 0x14); }
f32 EXPLOSIONBOMB_BOUND_NUM_710165d340()        { return FPA2_PARAM(0x3f0, 0x108, 0x18); }
f32 EXPLOSIONBOMB_IGNITION_FRAME_710165d3a0()   { return FPA2_PARAM(0x3f0, 0x108, 0x1c); }
f32 EXPLOSIONBOMB_WIRE_SPEED_X_710165d3c0()     { return FPA2_PARAM(0x3f0, 0x108, 0x20); }
f32 EXPLOSIONBOMB_WIRE_SPEED_Y_710165d3e0()     { return FPA2_PARAM(0x3f0, 0x108, 0x24); }
f32 EXPLOSIONBOMB_WIRE_GRAVITY_710165d400()     { return FPA2_PARAM(0x3f0, 0x108, 0x28); }
f32 EXPLOSIONBOMB_WIRE_BOUND_MUL_Y_710165d420() { return FPA2_PARAM(0x3f0, 0x108, 0x2c); }
f32 EXPLOSIONBOMB_BURST_FRAME_710165d440()      { return FPA2_PARAM(0x3f0, 0x108, 0x30); }
f32 EXPLOSIONBOMB_LIFE_MISFIRE_710165d460()     { return FPA2_PARAM(0x3f0, 0x108, 0x38); }

// ════════════════════════════════════════════════════════════════════
// KROOLCROWN spawn/delete params (24B each)
// [derived: FPA2+0xf88 → +0x1c8 → final offset]
// ════════════════════════════════════════════════════════════════════

f32 spawn_frame_710165e800()              { return FPA2_PARAM(0xf88, 0x1c8, 0x1c); }
f32 spawn_frame_add_710165e820()          { return FPA2_PARAM(0xf88, 0x1c8, 0x20); }
f32 spawn_frame_max_710165e840()          { return FPA2_PARAM(0xf88, 0x1c8, 0x24); }
f32 spawn_frame_get_krool_only_710165e860(){ return FPA2_PARAM(0xf88, 0x1c8, 0x2c); }
f32 delete_frame_710165e880()             { return FPA2_PARAM(0xf88, 0x1c8, 0x34); }
f32 delete_flash_frame_710165e8a0()       { return FPA2_PARAM(0xf88, 0x1c8, 0x38); }

// ════════════════════════════════════════════════════════════════════
// LINKARROW params (24B each)
// [derived: FPA2+0xe0 → +0x120 → final offset]
// ════════════════════════════════════════════════════════════════════

f32 LINKARROW_ITEM_LIFE_710165eb30()         { return FPA2_PARAM(0xe0, 0x120, 0x2c); }
f32 LINKARROW_ITEM_THROW_DEGREE_710165eb50() { return FPA2_PARAM(0xe0, 0x120, 0x30); }

// ════════════════════════════════════════════════════════════════════
// LOG params — same base as DOLL (24B each)
// [derived: FPA2+0xc08 → +0x178 → final offset]
// ════════════════════════════════════════════════════════════════════

f32 LOG_LIFE_710165f120()             { return FPA2_PARAM(0xc08, 0x178, 0x34); }
f32 LOG_REACTION_MUL_710165f140()     { return FPA2_PARAM(0xc08, 0x178, 0x0c); }
f32 LOG_LIFE_DEC_MUL_710165f160()     { return FPA2_PARAM(0xc08, 0x178, 0x38); }
f32 LOG_SMASH_ACCEL_Y_710165f180()    { return FPA2_PARAM(0xc08, 0x178, 0x20); }
f32 LOG_SMASH_MAX_SPEED_X_710165f1a0(){ return FPA2_PARAM(0xc08, 0x178, 0x10); }
f32 LOG_SMASH_MAX_SPEED_Y_710165f1c0(){ return FPA2_PARAM(0xc08, 0x178, 0x14); }
f32 LOG_POWER_MAX_710165f1e0()        { return FPA2_PARAM(0xc08, 0x178, 0x30); }
f32 LOG_POWER_MIN_710165f200()        { return FPA2_PARAM(0xc08, 0x178, 0x2c); }
f32 LOG_ROT_SPEED_MAX_710165f220()    { return FPA2_PARAM(0xc08, 0x178, 0x28); }
f32 LOG_ROT_SPEED_MIN_710165f240()    { return FPA2_PARAM(0xc08, 0x178, 0x24); }
f32 LOG_SPEED_Y_710165f260()          { return FPA2_PARAM(0xc08, 0x178, 0x18); }
f32 LOG_ROT_SPEED_Z_710165f280()      { return FPA2_PARAM(0xc08, 0x178, 0x40); }
f32 LOG_ROT_Z_RATIO_710165f2a0()      { return FPA2_PARAM(0xc08, 0x178, 0x44); }

// MECHAKOOPA params (24B each)
// [derived: FPA2+0xd20 → +0x198 → final offset]

f32 MECHAKOOPA_BURST_FRAME_71016611e0()           { return FPA2_PARAM(0xd20, 0x198, 0x00); }
f32 MECHAKOOPA_COUNT_DOWN_FRAME_7101661200()      { return FPA2_PARAM(0xd20, 0x198, 0x04); }
