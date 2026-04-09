#include "types.h"

// Weapon parameter accessor functions — pool-c
// These read from FighterParamAccessor2 singleton via GOT (non-hidden)

// FighterParamAccessor2 singleton pointer (hidden visibility — direct adrp+ldr access)
// [derived: lib::Singleton<app::FighterParamAccessor2>::instance_]
extern "C" __attribute__((visibility("hidden"))) void* DAT_71052bb3b0;

// Helper: FPA2 singleton + two chained pointer reads + final f32/u32
#define FPA2_PARAM(off1, off2, off3) \
    *reinterpret_cast<f32*>( \
        *reinterpret_cast<u64*>( \
            *reinterpret_cast<u64*>( \
                reinterpret_cast<u8*>(DAT_71052bb3b0) + (off1)) + (off2)) + (off3))

#define FPA2_U32(off1, off2, off3) \
    *reinterpret_cast<u32*>( \
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

u32 DOLL_LIFE_710165c3d0()             { return FPA2_U32(0xc08, 0x178, 0x34); }
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
u32 DOLL_SHAPE_TYPE_710165c5f0()       { return FPA2_U32(0xc08, 0x1c0, 0x00); }

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
u32 EXPLOSIONBOMB_BOUND_NUM_710165d340()        { return FPA2_U32(0x3f0, 0x108, 0x18); }
u32 EXPLOSIONBOMB_IGNITION_FRAME_710165d3a0()   { return FPA2_U32(0x3f0, 0x108, 0x1c); }
f32 EXPLOSIONBOMB_WIRE_SPEED_X_710165d3c0()     { return FPA2_PARAM(0x3f0, 0x108, 0x20); }
f32 EXPLOSIONBOMB_WIRE_SPEED_Y_710165d3e0()     { return FPA2_PARAM(0x3f0, 0x108, 0x24); }
f32 EXPLOSIONBOMB_WIRE_GRAVITY_710165d400()     { return FPA2_PARAM(0x3f0, 0x108, 0x28); }
f32 EXPLOSIONBOMB_WIRE_BOUND_MUL_Y_710165d420() { return FPA2_PARAM(0x3f0, 0x108, 0x2c); }
u32 EXPLOSIONBOMB_BURST_FRAME_710165d440()      { return FPA2_U32(0x3f0, 0x108, 0x30); }
u32 EXPLOSIONBOMB_LIFE_MISFIRE_710165d460()     { return FPA2_U32(0x3f0, 0x108, 0x38); }

// ════════════════════════════════════════════════════════════════════
// KROOLCROWN spawn/delete params (24B each)
// [derived: FPA2+0xf88 → +0x1c8 → final offset]
// ════════════════════════════════════════════════════════════════════

u32 spawn_frame_710165e800()              { return FPA2_U32(0xf88, 0x1c8, 0x1c); }
u32 spawn_frame_add_710165e820()          { return FPA2_U32(0xf88, 0x1c8, 0x20); }
u32 spawn_frame_max_710165e840()          { return FPA2_U32(0xf88, 0x1c8, 0x24); }
u32 spawn_frame_get_krool_only_710165e860(){ return FPA2_U32(0xf88, 0x1c8, 0x2c); }
u32 delete_frame_710165e880()             { return FPA2_U32(0xf88, 0x1c8, 0x34); }
u32 delete_flash_frame_710165e8a0()       { return FPA2_U32(0xf88, 0x1c8, 0x38); }

// ════════════════════════════════════════════════════════════════════
// LINKARROW params (24B each)
// [derived: FPA2+0xe0 → +0x120 → final offset]
// ════════════════════════════════════════════════════════════════════

u32 LINKARROW_ITEM_LIFE_710165eb30()         { return FPA2_U32(0xe0, 0x120, 0x2c); }
f32 LINKARROW_ITEM_THROW_DEGREE_710165eb50() { return FPA2_PARAM(0xe0, 0x120, 0x30); }

// ════════════════════════════════════════════════════════════════════
// LOG params — same base as DOLL (24B each)
// [derived: FPA2+0xc08 → +0x178 → final offset]
// ════════════════════════════════════════════════════════════════════

u32 LOG_LIFE_710165f120()             { return FPA2_U32(0xc08, 0x178, 0x34); }
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

u32 MECHAKOOPA_BURST_FRAME_71016611e0()           { return FPA2_U32(0xd20, 0x198, 0x00); }
u32 MECHAKOOPA_COUNT_DOWN_FRAME_7101661200()      { return FPA2_U32(0xd20, 0x198, 0x04); }

// Helper: FPA2 singleton → one pointer read → final f32/u32 (2-level pattern)
// [derived: *(*(FPA2 + off1) + off2)]
#define FPA2_PARAM2(off1, off2) \
    *reinterpret_cast<f32*>( \
        *reinterpret_cast<u64*>( \
            reinterpret_cast<u8*>(DAT_71052bb3b0) + (off1)) + (off2))

#define FPA2_U32_2(off1, off2) \
    *reinterpret_cast<u32*>( \
        *reinterpret_cast<u64*>( \
            reinterpret_cast<u8*>(DAT_71052bb3b0) + (off1)) + (off2))

// ════════════════════════════════════════════════════════════════════
// BUDDYBOMB params — Snake's C4 (20B each)
// [derived: FPA2+0x12d0 → final offset]
// ════════════════════════════════════════════════════════════════════

u32 init_bound_frame_71016593a0()              { return FPA2_U32_2(0x12d0, 0x230); }
f32 special_lw_gravity_71016593c0()            { return FPA2_PARAM2(0x12d0, 0x234); }
f32 special_lw_speed_y_max_71016593e0()        { return FPA2_PARAM2(0x12d0, 0x238); }
f32 length_gravity_7101659400()                { return FPA2_PARAM2(0x12d0, 0x240); }
f32 length_speed_y_max_7101659420()            { return FPA2_PARAM2(0x12d0, 0x244); }
f32 length_angle_x_velocity_7101659440()       { return FPA2_PARAM2(0x12d0, 0x260); }
f32 length_angle_y_velocity_7101659460()       { return FPA2_PARAM2(0x12d0, 0x264); }
f32 length_angle_z_velocity_7101659480()       { return FPA2_PARAM2(0x12d0, 0x268); }
f32 side_gravity_71016594a0()                  { return FPA2_PARAM2(0x12d0, 0x26c); }
f32 side_speed_y_max_71016594c0()              { return FPA2_PARAM2(0x12d0, 0x270); }
f32 side_angle_x_velocity_71016594e0()         { return FPA2_PARAM2(0x12d0, 0x28c); }
f32 side_angle_y_velocity_7101659500()         { return FPA2_PARAM2(0x12d0, 0x290); }
f32 side_angle_z_velocity_7101659520()         { return FPA2_PARAM2(0x12d0, 0x294); }
u32 flashing_frame_before_life_over_7101659560(){ return FPA2_U32_2(0x12d0, 0x2a4); }
f32 rebound_speed_x_add_7101659580()           { return FPA2_PARAM2(0x12d0, 0x2a8); }
f32 rebound_speed_y_add_71016595a0()           { return FPA2_PARAM2(0x12d0, 0x2ac); }

// ════════════════════════════════════════════════════════════════════
// EXPLOSIONBOMB extra params (20B)
// [derived: FPA2+0x3f0 → +0x120]
// ════════════════════════════════════════════════════════════════════

u32 EXPLOSIONBOMB_WIRE_ROT_SPEED_710165d480()  { return FPA2_U32_2(0x3f0, 0x120); }

// ════════════════════════════════════════════════════════════════════
// PICKELBOMB params — Minecraft TNT (20B each)
// [derived: FPA2+0x13b0 → final offset]
// ════════════════════════════════════════════════════════════════════

f32 reaction_7101668fa0()                      { return FPA2_PARAM2(0x13b0, 0x750); }
f32 ignition_7101669000()                      { return FPA2_PARAM2(0x13b0, 0x75c); }
u32 lost_7101669060()                          { return FPA2_U32_2(0x13b0, 0x768); }
f32 gravity_accel_71016690a0()                 { return FPA2_PARAM2(0x13b0, 0x770); }
f32 gravity_accel_max_71016690c0()             { return FPA2_PARAM2(0x13b0, 0x774); }
u32 gravity_frame_71016690e0()                 { return FPA2_U32_2(0x13b0, 0x778); }
u32 flashing_frame_before_life_7101669100()    { return FPA2_U32_2(0x13b0, 0x77c); }

// ════════════════════════════════════════════════════════════════════
// PICKELOBJECT params — Minecraft objects (20B each)
// [derived: FPA2+0x13b0 → final offset]
// ════════════════════════════════════════════════════════════════════

u32 flash_start_frame_710166e110()             { return FPA2_U32_2(0x13b0, 0x51c); }
f32 camera_range_damag_mul_start_rate_710166e190() { return FPA2_PARAM2(0x13b0, 0x530); }
f32 camera_range_damag_mul_end_rate_710166e1b0()   { return FPA2_PARAM2(0x13b0, 0x534); }
f32 camera_range_damag_mul_min_710166e1d0()    { return FPA2_PARAM2(0x13b0, 0x538); }
f32 camera_range_damag_mul_max_710166e1f0()    { return FPA2_PARAM2(0x13b0, 0x53c); }
u32 generate_continuous_forbid_frame_710166e210() { return FPA2_U32_2(0x13b0, 0x540); }
u32 jostle_touch_ground_frame_710166e250()     { return FPA2_U32_2(0x13b0, 0x554); }
u32 jostle_up_touch_ground_frame_710166e270()  { return FPA2_U32_2(0x13b0, 0x55c); }
u32 jostle_up_touch_air_frame_710166e290()     { return FPA2_U32_2(0x13b0, 0x560); }

// ════════════════════════════════════════════════════════════════════
// POWERESA / ROCKETBELT params (20B each)
// ════════════════════════════════════════════════════════════════════

u32 POWERESA_SHAPE_TYPE_710166f720()           { return FPA2_U32_2(0xc78, 0x3a0); }
f32 get_energy_max_frame_710166fc60()          { return FPA2_PARAM2(0x50, 0xefc); }

// ════════════════════════════════════════════════════════════════════
// DAISY_DAISYDAIKON_DAIKON_LIFE_FRAME (28B)
// [derived: FPA2+0x380 → +0x158 → +0x14, cast float→int]
// ════════════════════════════════════════════════════════════════════

s32 DAISY_DAISYDAIKON_DAIKON_LIFE_FRAME_710165be20() { return (s32)FPA2_PARAM(0x380, 0x158, 0x14); }

// ════════════════════════════════════════════════════════════════════
// WIIFITBALL params (24B each)
// [derived: FPA2+0xb60 → +0x120 → final offset]
// ════════════════════════════════════════════════════════════════════

u32 WIIFITBALL_LIFE_7101678190()                  { return FPA2_U32(0xb60, 0x120, 0x24); }
u32 WIIFITBALL_BOUND_MAX_71016781f0()             { return FPA2_U32(0xb60, 0x120, 0x30); }
f32 WIIFITBALL_HEADING_SHOT_SPEED_7101678210()    { return FPA2_PARAM(0xb60, 0x120, 0x0c); }
f32 WIIFITBALL_START_GROUND_GRAVITY_7101678230()  { return FPA2_PARAM(0xb60, 0x120, 0x64); }
f32 WIIFITBALL_STAY_GROUND_START_FRAME_7101678250(){ return FPA2_PARAM(0xb60, 0x120, 0x68); }
f32 WIIFITBALL_STAY_GROUND_SPEED_Y_7101678270()   { return FPA2_PARAM(0xb60, 0x120, 0x6c); }
f32 WIIFITBALL_STAY_GROUND_GRAVITY_7101678290()   { return FPA2_PARAM(0xb60, 0x120, 0x70); }
f32 WIIFITBALL_FREE_GROUND_START_FRAME_71016782b0(){ return FPA2_PARAM(0xb60, 0x120, 0x74); }
f32 WIIFITBALL_START_AIR_GRAVITY_71016782d0()     { return FPA2_PARAM(0xb60, 0x120, 0x84); }
f32 WIIFITBALL_STAY_AIR_START_FRAME_71016782f0()  { return FPA2_PARAM(0xb60, 0x120, 0x88); }
f32 WIIFITBALL_STAY_AIR_SPEED_Y_7101678310()      { return FPA2_PARAM(0xb60, 0x120, 0x8c); }
f32 WIIFITBALL_STAY_AIR_GRAVITY_7101678330()      { return FPA2_PARAM(0xb60, 0x120, 0x90); }
f32 WIIFITBALL_FREE_AIR_START_FRAME_7101678350()  { return FPA2_PARAM(0xb60, 0x120, 0x94); }
u32 WIIFITBALL_LIFE_MINOUS_BOUND_GROUND_7101678370(){ return FPA2_U32(0xb60, 0x120, 0x2c); }
f32 WIIFITBALL_BRAKE_X_71016783f0()               { return FPA2_PARAM(0xb60, 0x120, 0x08); }
f32 WIIFITBALL_SCALE_7101678430()                 { return FPA2_PARAM(0xb60, 0x120, 0x48); }
f32 WIIFITBALL_REACTION_MUL_7101678470()          { return FPA2_PARAM(0xb60, 0x120, 0x50); }

// WIIFITBALL_RHOMBUS_SHAPE — different chain: FPA2+0xb60 → +0x138 → deref (offset 0)
u32 WIIFITBALL_RHOMBUS_SHAPE_7101678410()         { return FPA2_U32(0xb60, 0x138, 0x00); }

// ════════════════════════════════════════════════════════════════════
// PACMAN weapon params — per-fruit-type accessors (24B each)
// All use FPA2 base 0xc78, fruit-specific second offset
// [derived: FPA2+0xc78 → +fruit_off → final offset]
// ════════════════════════════════════════════════════════════════════

// --- pacmanapple (off2=0x138, shape_off2=0x2b8) ---
f32 PACMAN_ACCEL_Y_7101661f80()                   { return FPA2_PARAM(0xc78, 0x138, 0x10); }
u32 PACMAN_LIFE_7101661fa0()                      { return FPA2_U32(0xc78, 0x138, 0x00); }
u32 PACMAN_REFLECTION_MAX_NUM_7101661fc0()        { return FPA2_U32(0xc78, 0x138, 0x24); }
u32 PACMAN_SHAPE_TYPE_7101662000()                { return FPA2_U32(0xc78, 0x2b8, 0x00); }

// --- pacmanbell (off2=0x180, shape_off2=0x300) ---
f32 PACMAN_ACCEL_Y_7101662c50()                   { return FPA2_PARAM(0xc78, 0x180, 0x10); }
u32 PACMAN_LIFE_7101662c70()                      { return FPA2_U32(0xc78, 0x180, 0x00); }
u32 PACMAN_REFLECTION_MAX_NUM_7101662c90()        { return FPA2_U32(0xc78, 0x180, 0x24); }
u32 PACMAN_SHAPE_TYPE_7101662cd0()                { return FPA2_U32(0xc78, 0x300, 0x00); }

// --- pacmanboss (off2=0x168, shape_off2=0x2e8) ---
f32 PACMAN_ACCEL_Y_7101663a20()                   { return FPA2_PARAM(0xc78, 0x168, 0x0c); }
u32 PACMAN_LIFE_7101663a40()                      { return FPA2_U32(0xc78, 0x168, 0x00); }
u32 PACMAN_REFLECTION_MAX_NUM_7101663a60()        { return FPA2_U32(0xc78, 0x168, 0x1c); }
u32 PACMAN_SHAPE_TYPE_7101663aa0()                { return FPA2_U32(0xc78, 0x2e8, 0x00); }

// --- pacmancherry (off2=0xf0, shape_off2=0x270) ---
f32 PACMAN_ACCEL_Y_7101664a90()                   { return FPA2_PARAM(0xc78, 0xf0, 0x10); }
u32 PACMAN_LIFE_7101664ab0()                      { return FPA2_U32(0xc78, 0xf0, 0x00); }
u32 PACMAN_REFLECTION_MAX_NUM_7101664ad0()        { return FPA2_U32(0xc78, 0xf0, 0x24); }
u32 PACMAN_SHAPE_TYPE_7101664b10()                { return FPA2_U32(0xc78, 0x270, 0x00); }

// --- pacmanfruittarget_common (off2=0xd8) ---
u32 PACMAN_LANDING_LIFE_7101665760()              { return FPA2_U32(0xc78, 0xd8, 0x04); }

// --- pacmankey (off2=0x198, shape_off2=0x318) ---
f32 PACMAN_ACCEL_Y_71016657a0()                   { return FPA2_PARAM(0xc78, 0x198, 0x0c); }
u32 PACMAN_LIFE_71016657c0()                      { return FPA2_U32(0xc78, 0x198, 0x00); }
u32 PACMAN_REFLECTION_MAX_NUM_71016657e0()        { return FPA2_U32(0xc78, 0x198, 0x1c); }
u32 PACMAN_SHAPE_TYPE_7101665820()                { return FPA2_U32(0xc78, 0x318, 0x00); }

// --- pacmanmelon (off2=0x150, shape_off2=0x2d0) ---
f32 PACMAN_ACCEL_Y_71016664a0()                   { return FPA2_PARAM(0xc78, 0x150, 0x10); }
u32 PACMAN_LIFE_71016664c0()                      { return FPA2_U32(0xc78, 0x150, 0x00); }
u32 PACMAN_REFLECTION_MAX_NUM_71016664e0()        { return FPA2_U32(0xc78, 0x150, 0x24); }
u32 PACMAN_SHAPE_TYPE_7101666520()                { return FPA2_U32(0xc78, 0x2d0, 0x00); }

// --- pacmanorange (off2=0x120, shape_off2=0x2a0) ---
f32 PACMAN_ACCEL_Y_7101667170()                   { return FPA2_PARAM(0xc78, 0x120, 0x0c); }
u32 PACMAN_LIFE_7101667190()                      { return FPA2_U32(0xc78, 0x120, 0x00); }
u32 PACMAN_REFLECTION_MAX_NUM_71016671b0()        { return FPA2_U32(0xc78, 0x120, 0x1c); }
u32 PACMAN_SHAPE_TYPE_71016671f0()                { return FPA2_U32(0xc78, 0x2a0, 0x00); }

// --- pacmanstrawberry (off2=0x108, shape_off2=0x288) ---
f32 PACMAN_ACCEL_Y_7101667e50()                   { return FPA2_PARAM(0xc78, 0x108, 0x10); }
u32 PACMAN_LIFE_7101667e70()                      { return FPA2_U32(0xc78, 0x108, 0x00); }
u32 PACMAN_REFLECTION_MAX_NUM_7101667e90()        { return FPA2_U32(0xc78, 0x108, 0x24); }
u32 PACMAN_SHAPE_TYPE_7101667ed0()                { return FPA2_U32(0xc78, 0x288, 0x00); }

// ════════════════════════════════════════════════════════════════════
// ROCKMAN_METALBLADE params (24B each)
// [derived: FPA2+0xb28 → +0x1a0 → final offset]
// ════════════════════════════════════════════════════════════════════

u32 ROCKMAN_METALBLADE_WAIT_LOST_COUNT_THROW_7101661660() { return FPA2_U32(0xb28, 0x1a0, 0x04); }
u32 ROCKMAN_METALBLADE_WAIT_LOST_COUNT_STICK_7101661680() { return FPA2_U32(0xb28, 0x1a0, 0x0c); }
f32 ROCKMAN_METALBLADE_STICK_PERCENT_71016616a0()         { return FPA2_PARAM(0xb28, 0x1a0, 0x08); }
u32 ROCKMAN_METALBLADE_SPEED_REVERSE_FRAME_71016616e0()   { return FPA2_U32(0xb28, 0x1a0, 0x30); }
u32 ROCKMAN_METALBLADE_LIFE_SUBTRACT_7101661780()         { return FPA2_U32(0xb28, 0x1a0, 0x10); }
u32 ROCKMAN_METALBLADE_STICK_ROT_STOP_FRAME_71016617a0()  { return FPA2_U32(0xb28, 0x1a0, 0x14); }
f32 ROCKMAN_METALBLADE_JOSTLE_SCALE_71016617c0()          { return FPA2_PARAM(0xb28, 0x1a0, 0x18); }

// ROCKMAN_METALBLADE_IS_CATCH — returns bool (32B: FPA2_PARAM + cmp + cset)
// [derived: FPA2+0xb28 → +0x1a0 → +0x20, != 0]
bool ROCKMAN_METALBLADE_IS_CATCH_71016616c0() {
    return *reinterpret_cast<s32*>(
        *reinterpret_cast<u64*>(
            *reinterpret_cast<u64*>(
                reinterpret_cast<u8*>(DAT_71052bb3b0) + 0xb28) + 0x1a0) + 0x20) != 0;
}

// ════════════════════════════════════════════════════════════════════
// OTHER_METALBLADE params (24B each)
// [derived: FPA2+0xb28 → +0x1b8 → final offset]
// ════════════════════════════════════════════════════════════════════

u32 OTHER_METALBLADE_WAIT_LOST_COUNT_THROW_7101661700()   { return FPA2_U32(0xb28, 0x1b8, 0x04); }
u32 OTHER_METALBLADE_WAIT_LOST_COUNT_STICK_7101661720()   { return FPA2_U32(0xb28, 0x1b8, 0x0c); }
f32 OTHER_METALBLADE_STICK_PERCENT_7101661740()           { return FPA2_PARAM(0xb28, 0x1b8, 0x08); }
u32 OTHER_METALBLADE_SPEED_REVERSE_FRAME_7101661760()     { return FPA2_U32(0xb28, 0x1b8, 0x20); }

// ════════════════════════════════════════════════════════════════════
// POWERESA params (24B each)
// [derived: FPA2+0xc78 → +0x360 → final offset]
// ════════════════════════════════════════════════════════════════════

f32 POWERESA_ACCEL_Y_710166f6c0()                 { return FPA2_PARAM(0xc78, 0x360, 0x04); }
u32 POWERESA_LIFE_710166f6e0()                    { return FPA2_U32(0xc78, 0x360, 0x10); }
f32 POWERESA_HEAL_BASE_710166f740()               { return FPA2_PARAM(0xc78, 0x360, 0x14); }

// ════════════════════════════════════════════════════════════════════
// ROBOTGYRO params (24B each)
// [derived: FPA2+0xa48 → +0x158 → final offset]
// ════════════════════════════════════════════════════════════════════

f32 ROBOTGYRO_MOVE_SPEED_710166f9c0()             { return FPA2_PARAM(0xa48, 0x158, 0x34); }
u32 ROBOTGYRO_MOVE_BASE_FRAME_710166f9e0()        { return FPA2_U32(0xa48, 0x158, 0x2c); }
u32 ROBOTGYRO_MOVE_RANDOM_FRAME_710166fa00()      { return FPA2_U32(0xa48, 0x158, 0x30); }

// ════════════════════════════════════════════════════════════════════
// WOOD params (24B)
// [derived: FPA2+0xaf0 → +0x2d0 → deref (offset 0)]
// ════════════════════════════════════════════════════════════════════

u32 WOOD_LIFE_71016787e0()                        { return FPA2_U32(0xaf0, 0x2d0, 0x00); }

// ════════════════════════════════════════════════════════════════════
// LOG_SHAPE_TYPE (24B)
// [derived: FPA2+0xc08 → +0x190 → deref (offset 0)]
// ════════════════════════════════════════════════════════════════════

u32 LOG_SHAPE_TYPE_710165f340()                   { return FPA2_U32(0xc08, 0x190, 0x00); }

// ════════════════════════════════════════════════════════════════════
// PEACH_PEACHDAIKON_DAIKON_LIFE_FRAME (28B)
// [derived: FPA2+0x348 → +0x158 → +0x14, cast float→int]
// ════════════════════════════════════════════════════════════════════

s32 PEACH_PEACHDAIKON_DAIKON_LIFE_FRAME_7101668c70() { return (s32)FPA2_PARAM(0x348, 0x158, 0x14); }
