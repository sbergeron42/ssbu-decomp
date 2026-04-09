#include "types.h"

// pool-a round 6b: Weapon/fighter param reader functions
// All read from lib::Singleton<app::FighterParamAccessor2>::instance_
// [derived: adrp 0x71052bb000 + 0x3b0 = 0x71052bb3b0]

#define HIDDEN __attribute__((visibility("hidden")))

// FighterParamAccessor2 singleton
extern "C" void* DAT_71052bb3b0 HIDDEN;

// Helper macros for param reader chains
// 3-deref: FPA2 → offset1 → offset2 → field
#define FPA2       ((u64)DAT_71052bb3b0)
#define FPA2_3(o1, o2, field)  (*(u64*)(*(u64*)(FPA2 + (o1)) + (o2)) + (field))
// 2-deref: FPA2 → offset1 → field
#define FPA2_2(o1, field)      (*(u64*)(FPA2 + (o1)) + (field))

// ---- app::daisydaikon — Daisy Daikon probability/power params ----
// Chain: FPA2 → +0x380 → +0x158 → +field
// [derived: app::daisydaikon::* in Ghidra, all return float via ldr s0]

// 0x710165be40 — DAISY_DAISYDAIKON_DAIKON_1_PROB (24B)
float DAISY_DAISYDAIKON_DAIKON_1_PROB_165be40() { return *(float*)FPA2_3(0x380, 0x158, 0x40); }
// 0x710165be60 — DAISY_DAISYDAIKON_DAIKON_2_PROB (24B)
float DAISY_DAISYDAIKON_DAIKON_2_PROB_165be60() { return *(float*)FPA2_3(0x380, 0x158, 0x44); }
// 0x710165be80 — DAISY_DAISYDAIKON_DAIKON_3_PROB (24B)
float DAISY_DAISYDAIKON_DAIKON_3_PROB_165be80() { return *(float*)FPA2_3(0x380, 0x158, 0x48); }
// 0x710165bea0 — DAISY_DAISYDAIKON_DAIKON_4_PROB (24B)
float DAISY_DAISYDAIKON_DAIKON_4_PROB_165bea0() { return *(float*)FPA2_3(0x380, 0x158, 0x4c); }
// 0x710165bec0 — DAISY_DAISYDAIKON_DAIKON_5_PROB (24B)
float DAISY_DAISYDAIKON_DAIKON_5_PROB_165bec0() { return *(float*)FPA2_3(0x380, 0x158, 0x50); }
// 0x710165bee0 — DAISY_DAISYDAIKON_DAIKON_6_PROB (24B)
float DAISY_DAISYDAIKON_DAIKON_6_PROB_165bee0() { return *(float*)FPA2_3(0x380, 0x158, 0x54); }
// 0x710165bf00 — DAISY_DAISYDAIKON_DAIKON_7_PROB (24B)
float DAISY_DAISYDAIKON_DAIKON_7_PROB_165bf00() { return *(float*)FPA2_3(0x380, 0x158, 0x58); }
// 0x710165bf20 — DAISY_DAISYDAIKON_DAIKON_8_PROB (24B)
float DAISY_DAISYDAIKON_DAIKON_8_PROB_165bf20() { return *(float*)FPA2_3(0x380, 0x158, 0x5c); }

// 0x710165bf40 — DAISY_DAISYDAIKON_DAIKON_1_POWER (24B)
float DAISY_DAISYDAIKON_DAIKON_1_POWER_165bf40() { return *(float*)FPA2_3(0x380, 0x158, 0x20); }
// 0x710165bf60 — DAISY_DAISYDAIKON_DAIKON_2_POWER (24B)
float DAISY_DAISYDAIKON_DAIKON_2_POWER_165bf60() { return *(float*)FPA2_3(0x380, 0x158, 0x24); }
// 0x710165bf80 — DAISY_DAISYDAIKON_DAIKON_3_POWER (24B)
float DAISY_DAISYDAIKON_DAIKON_3_POWER_165bf80() { return *(float*)FPA2_3(0x380, 0x158, 0x28); }
// 0x710165bfa0 — DAISY_DAISYDAIKON_DAIKON_4_POWER (24B)
float DAISY_DAISYDAIKON_DAIKON_4_POWER_165bfa0() { return *(float*)FPA2_3(0x380, 0x158, 0x2c); }
// 0x710165bfc0 — DAISY_DAISYDAIKON_DAIKON_5_POWER (24B)
float DAISY_DAISYDAIKON_DAIKON_5_POWER_165bfc0() { return *(float*)FPA2_3(0x380, 0x158, 0x30); }
// 0x710165bfe0 — DAISY_DAISYDAIKON_DAIKON_6_POWER (24B)
float DAISY_DAISYDAIKON_DAIKON_6_POWER_165bfe0() { return *(float*)FPA2_3(0x380, 0x158, 0x34); }
// 0x710165c000 — DAISY_DAISYDAIKON_DAIKON_7_POWER (24B)
float DAISY_DAISYDAIKON_DAIKON_7_POWER_165c000() { return *(float*)FPA2_3(0x380, 0x158, 0x38); }
// 0x710165c020 — DAISY_DAISYDAIKON_DAIKON_8_POWER (24B)
float DAISY_DAISYDAIKON_DAIKON_8_POWER_165c020() { return *(float*)FPA2_3(0x380, 0x158, 0x3c); }

// ---- app::kroolcrown — K. Rool Crown spawn/delete frame params ----
// Chain: FPA2 → +0xf88 → +0x1c8 → +field
// [derived: app::kroolcrown::* in Ghidra, all return u32 via ldr w0]

// 0x710165e800 — spawn_frame (24B)
u32 spawn_frame_165e800() { return *(u32*)FPA2_3(0xf88, 0x1c8, 0x1c); }
// 0x710165e820 — spawn_frame_add (24B)
u32 spawn_frame_add_165e820() { return *(u32*)FPA2_3(0xf88, 0x1c8, 0x20); }
// 0x710165e840 — spawn_frame_max (24B)
u32 spawn_frame_max_165e840() { return *(u32*)FPA2_3(0xf88, 0x1c8, 0x24); }
// 0x710165e860 — spawn_frame_get_krool_only (24B)
u32 spawn_frame_get_krool_only_165e860() { return *(u32*)FPA2_3(0xf88, 0x1c8, 0x2c); }
// 0x710165e880 — delete_frame (24B)
u32 delete_frame_165e880() { return *(u32*)FPA2_3(0xf88, 0x1c8, 0x34); }
// 0x710165e8a0 — delete_flash_frame (24B)
u32 delete_flash_frame_165e8a0() { return *(u32*)FPA2_3(0xf88, 0x1c8, 0x38); }

// ---- app::log — Log item params ----
// Chain: FPA2 → +0xc08 → +0x178 → +field
// [derived: app::log::* in Ghidra]

// 0x710165f120 — LOG_LIFE (24B)
u32 LOG_LIFE_165f120() { return *(u32*)FPA2_3(0xc08, 0x178, 0x34); }
// 0x710165f140 — LOG_REACTION_MUL (24B)
float LOG_REACTION_MUL_165f140() { return *(float*)FPA2_3(0xc08, 0x178, 0xc); }

// ---- app::buddybomb — Buddy Bomb physics params ----
// Chain: FPA2 → +0x12d0 → +field (2-deref, 20B = 5 instr)
// [derived: app::buddybomb::* in Ghidra]

// 0x71016593a0 — init_bound_frame (20B)
u32 init_bound_frame_16593a0() { return *(u32*)FPA2_2(0x12d0, 0x230); }
// 0x71016593c0 — special_lw_gravity (20B)
float special_lw_gravity_16593c0() { return *(float*)FPA2_2(0x12d0, 0x234); }
// 0x71016593e0 — special_lw_speed_y_max (20B)
float special_lw_speed_y_max_16593e0() { return *(float*)FPA2_2(0x12d0, 0x238); }
// 0x7101659400 — length_gravity (20B)
float length_gravity_1659400() { return *(float*)FPA2_2(0x12d0, 0x240); }
// 0x7101659420 — length_speed_y_max (20B)
float length_speed_y_max_1659420() { return *(float*)FPA2_2(0x12d0, 0x244); }
// 0x7101659440 — length_angle_x_velocity (20B)
float length_angle_x_velocity_1659440() { return *(float*)FPA2_2(0x12d0, 0x260); }
// 0x7101659460 — length_angle_y_velocity (20B)
float length_angle_y_velocity_1659460() { return *(float*)FPA2_2(0x12d0, 0x264); }
// 0x7101659480 — length_angle_z_velocity (20B)
float length_angle_z_velocity_1659480() { return *(float*)FPA2_2(0x12d0, 0x268); }
// 0x71016594a0 — side_gravity (20B)
float side_gravity_16594a0() { return *(float*)FPA2_2(0x12d0, 0x26c); }
// 0x71016594c0 — side_speed_y_max (20B)
float side_speed_y_max_16594c0() { return *(float*)FPA2_2(0x12d0, 0x270); }
// 0x71016594e0 — side_angle_x_velocity (20B)
float side_angle_x_velocity_16594e0() { return *(float*)FPA2_2(0x12d0, 0x28c); }
// 0x7101659500 — side_angle_y_velocity (20B)
float side_angle_y_velocity_1659500() { return *(float*)FPA2_2(0x12d0, 0x290); }
// 0x7101659520 — side_angle_z_velocity (20B)
float side_angle_z_velocity_1659520() { return *(float*)FPA2_2(0x12d0, 0x294); }
// 0x7101659560 — flashing_frame_before_life_over (20B)
// [derived: ldr w0 = u32 return]
u32 flashing_frame_before_life_over_1659560() { return *(u32*)FPA2_2(0x12d0, 0x2a4); }
// 0x7101659580 — rebound_speed_x_add (20B)
float rebound_speed_x_add_1659580() { return *(float*)FPA2_2(0x12d0, 0x2a8); }
// 0x71016595a0 — rebound_speed_y_add (20B)
float rebound_speed_y_add_16595a0() { return *(float*)FPA2_2(0x12d0, 0x2ac); }

// ---- app::explosionbomb — Explosion bomb wire params ----
// Chain: FPA2 → +0x3f0 → +field (2-deref, 20B)

// 0x710165d480 — EXPLOSIONBOMB_WIRE_ROT_SPEED (20B)
// [derived: ldr w0 = u32 return]
u32 EXPLOSIONBOMB_WIRE_ROT_SPEED_165d480() { return *(u32*)FPA2_2(0x3f0, 0x120); }

// ---- app::log — additional Log item params ----
// Chain: FPA2 → +0xc08 → +0x178 → +field (3-deref, 24B)

// 0x710165f160 — LOG_LIFE_DEC_MUL (24B)
float LOG_LIFE_DEC_MUL_165f160() { return *(float*)FPA2_3(0xc08, 0x178, 0x38); }
// 0x710165f180 — LOG_SMASH_ACCEL_Y (24B)
float LOG_SMASH_ACCEL_Y_165f180() { return *(float*)FPA2_3(0xc08, 0x178, 0x20); }
// 0x710165f1a0 — LOG_SMASH_MAX_SPEED_X (24B)
float LOG_SMASH_MAX_SPEED_X_165f1a0() { return *(float*)FPA2_3(0xc08, 0x178, 0x10); }
// 0x710165f1c0 — LOG_SMASH_MAX_SPEED_Y (24B)
float LOG_SMASH_MAX_SPEED_Y_165f1c0() { return *(float*)FPA2_3(0xc08, 0x178, 0x14); }
// 0x710165f1e0 — LOG_POWER_MAX (24B)
float LOG_POWER_MAX_165f1e0() { return *(float*)FPA2_3(0xc08, 0x178, 0x30); }
// 0x710165f200 — LOG_POWER_MIN (24B)
float LOG_POWER_MIN_165f200() { return *(float*)FPA2_3(0xc08, 0x178, 0x2c); }
// 0x710165f220 — LOG_ROT_SPEED_MAX (24B)
float LOG_ROT_SPEED_MAX_165f220() { return *(float*)FPA2_3(0xc08, 0x178, 0x28); }
// 0x710165f240 — LOG_ROT_SPEED_MIN (24B)
float LOG_ROT_SPEED_MIN_165f240() { return *(float*)FPA2_3(0xc08, 0x178, 0x24); }
// 0x710165f260 — LOG_SPEED_Y (24B)
float LOG_SPEED_Y_165f260() { return *(float*)FPA2_3(0xc08, 0x178, 0x0); }
// 0x710165f280 — LOG_ROT_SPEED_Z (24B)
float LOG_ROT_SPEED_Z_165f280() { return *(float*)FPA2_3(0xc08, 0x178, 0x8); }
// 0x710165f2a0 — LOG_ROT_Z_RATIO (24B)
float LOG_ROT_Z_RATIO_165f2a0() { return *(float*)FPA2_3(0xc08, 0x178, 0x44); }

// ---- app::log — LOG_SHAPE_TYPE (different sub-table) ----
// Chain: FPA2 → +0xc08 → +0x190 → +field (3-deref, 24B)
// [derived: ldr w0 = u32 return, different offset2 than other LOG params]

// 0x710165f340 — LOG_SHAPE_TYPE (24B)
u32 LOG_SHAPE_TYPE_165f340() { return *(u32*)FPA2_3(0xc08, 0x190, 0x0); }

// ---- app::pickelobject — Pickel (Steve) object params ----
// Chain: FPA2 → +0x13b0 → +field (2-deref, 20B)

// 0x710166e110 — flash_start_frame (20B)
u32 flash_start_frame_166e110() { return *(u32*)FPA2_2(0x13b0, 0x51c); }
// 0x710166e210 — generate_continuous_forbid_frame (20B)
u32 generate_continuous_forbid_frame_166e210() { return *(u32*)FPA2_2(0x13b0, 0x540); }
// 0x710166e250 — jostle_touch_ground_frame (20B)
u32 jostle_touch_ground_frame_166e250() { return *(u32*)FPA2_2(0x13b0, 0x554); }
// 0x710166e270 — jostle_up_touch_ground_frame (20B)
u32 jostle_up_touch_ground_frame_166e270() { return *(u32*)FPA2_2(0x13b0, 0x55c); }
// 0x710166e290 — jostle_up_touch_air_frame (20B)
u32 jostle_up_touch_air_frame_166e290() { return *(u32*)FPA2_2(0x13b0, 0x560); }

// ---- app::pickelobject — motion bomb params ----
// Chain: FPA2 → +0x13b0 → +field (2-deref, 20B)

// 0x7101668fa0 — reaction (20B)
float reaction_1668fa0() { return *(float*)FPA2_2(0x13b0, 0x750); }
// 0x7101669000 — ignition (20B)
float ignition_1669000() { return *(float*)FPA2_2(0x13b0, 0x75c); }
// 0x7101669060 — lost (20B)
u32 lost_1669060() { return *(u32*)FPA2_2(0x13b0, 0x768); }
// 0x71016690a0 — gravity_accel (20B)
float gravity_accel_16690a0() { return *(float*)FPA2_2(0x13b0, 0x770); }
// 0x71016690c0 — gravity_accel_max (20B)
float gravity_accel_max_16690c0() { return *(float*)FPA2_2(0x13b0, 0x774); }
// 0x71016690e0 — gravity_frame (20B)
u32 gravity_frame_16690e0() { return *(u32*)FPA2_2(0x13b0, 0x778); }
// 0x7101669100 — flashing_frame_before_life (20B)
u32 flashing_frame_before_life_1669100() { return *(u32*)FPA2_2(0x13b0, 0x77c); }

// ---- app::rockman_metalblade — Metal Blade params ----
// Rockman (Mega Man) chain: FPA2 → +0xb28 → +0x1a0 → +field (3-deref, 24B)
// [derived: app::rockman_metalblade::* in Ghidra]

// 0x7101661660 — ROCKMAN_METALBLADE_WAIT_LOST_COUNT_THROW (24B)
u32 ROCKMAN_METALBLADE_WAIT_LOST_COUNT_THROW_1661660() { return *(u32*)FPA2_3(0xb28, 0x1a0, 0x4); }
// 0x7101661680 — ROCKMAN_METALBLADE_WAIT_LOST_COUNT_STICK (24B)
u32 ROCKMAN_METALBLADE_WAIT_LOST_COUNT_STICK_1661680() { return *(u32*)FPA2_3(0xb28, 0x1a0, 0xc); }
// 0x71016616a0 — ROCKMAN_METALBLADE_STICK_PERCENT (24B)
float ROCKMAN_METALBLADE_STICK_PERCENT_16616a0() { return *(float*)FPA2_3(0xb28, 0x1a0, 0x8); }
// 0x71016616e0 — ROCKMAN_METALBLADE_SPEED_REVERSE_FRAME (24B)
u32 ROCKMAN_METALBLADE_SPEED_REVERSE_FRAME_16616e0() { return *(u32*)FPA2_3(0xb28, 0x1a0, 0x30); }
// 0x7101661780 — ROCKMAN_METALBLADE_LIFE_SUBTRACT (24B)
u32 ROCKMAN_METALBLADE_LIFE_SUBTRACT_1661780() { return *(u32*)FPA2_3(0xb28, 0x1a0, 0x10); }
// 0x71016617a0 — ROCKMAN_METALBLADE_STICK_ROT_STOP_FRAME (24B)
u32 ROCKMAN_METALBLADE_STICK_ROT_STOP_FRAME_16617a0() { return *(u32*)FPA2_3(0xb28, 0x1a0, 0x14); }
// 0x71016617c0 — ROCKMAN_METALBLADE_JOSTLE_SCALE (24B)
float ROCKMAN_METALBLADE_JOSTLE_SCALE_16617c0() { return *(float*)FPA2_3(0xb28, 0x1a0, 0x18); }

// ---- Other Metal Blade (non-Rockman owner) ----
// Chain: FPA2 → +0xb28 → +0x1b8 → +field (3-deref, 24B)

// 0x7101661700 — OTHER_METALBLADE_WAIT_LOST_COUNT_THROW (24B)
u32 OTHER_METALBLADE_WAIT_LOST_COUNT_THROW_1661700() { return *(u32*)FPA2_3(0xb28, 0x1b8, 0x4); }
// 0x7101661720 — OTHER_METALBLADE_WAIT_LOST_COUNT_STICK (24B)
u32 OTHER_METALBLADE_WAIT_LOST_COUNT_STICK_1661720() { return *(u32*)FPA2_3(0xb28, 0x1b8, 0xc); }
// 0x7101661740 — OTHER_METALBLADE_STICK_PERCENT (24B)
float OTHER_METALBLADE_STICK_PERCENT_1661740() { return *(float*)FPA2_3(0xb28, 0x1b8, 0x8); }
// 0x7101661760 — OTHER_METALBLADE_SPEED_REVERSE_FRAME (24B)
u32 OTHER_METALBLADE_SPEED_REVERSE_FRAME_1661760() { return *(u32*)FPA2_3(0xb28, 0x1b8, 0x20); }

// ---- app::pacman — Pac-Man bonus fruit params ----
// Chain: FPA2 → +0xc78 → +0x138 → +field (3-deref, 24B)

// 0x7101661f80 — PACMAN_ACCEL_Y (24B)
float PACMAN_ACCEL_Y_1661f80() { return *(float*)FPA2_3(0xc78, 0x138, 0x10); }
// 0x7101661fa0 — PACMAN_LIFE (24B)
u32 PACMAN_LIFE_1661fa0() { return *(u32*)FPA2_3(0xc78, 0x138, 0x0); }
// 0x7101661fc0 — PACMAN_REFLECTION_MAX_NUM (24B)
u32 PACMAN_REFLECTION_MAX_NUM_1661fc0() { return *(u32*)FPA2_3(0xc78, 0x138, 0x24); }

// Pac-Man shape type (different sub-table)
// Chain: FPA2 → +0xc78 → +0x2b8 → +field
// 0x7101662000 — PACMAN_SHAPE_TYPE (24B)
u32 PACMAN_SHAPE_TYPE_1662000() { return *(u32*)FPA2_3(0xc78, 0x2b8, 0x0); }

// Pac-Man landing (different sub-table)
// Chain: FPA2 → +0xc78 → +0xd8 → +field
// 0x7101665760 — PACMAN_LANDING_LIFE (24B)
u32 PACMAN_LANDING_LIFE_1665760() { return *(u32*)FPA2_3(0xc78, 0xd8, 0x4); }

// ---- app::poweresa — Power Star params ----
// Chain: FPA2 → +0xc78 → +0x360 → +field (3-deref, 24B)

// 0x710166f6c0 — POWERESA_ACCEL_Y (24B)
float POWERESA_ACCEL_Y_166f6c0() { return *(float*)FPA2_3(0xc78, 0x360, 0x4); }
// 0x710166f6e0 — POWERESA_LIFE (24B)
u32 POWERESA_LIFE_166f6e0() { return *(u32*)FPA2_3(0xc78, 0x360, 0x10); }
// 0x710166f740 — POWERESA_HEAL_BASE (24B)
float POWERESA_HEAL_BASE_166f740() { return *(float*)FPA2_3(0xc78, 0x360, 0x14); }

// Power Star shape type (2-deref, 20B)
// Chain: FPA2 → +0xc78 → +0x3a0
// 0x710166f720 — POWERESA_SHAPE_TYPE (20B)
u32 POWERESA_SHAPE_TYPE_166f720() { return *(u32*)FPA2_2(0xc78, 0x3a0); }

// ---- app::robotgyro — R.O.B. Gyro params ----
// Chain: FPA2 → +0xa48 → +0x158 → +field (3-deref, 24B)

// 0x710166f9c0 — ROBOTGYRO_MOVE_SPEED (24B)
float ROBOTGYRO_MOVE_SPEED_166f9c0() { return *(float*)FPA2_3(0xa48, 0x158, 0x34); }
// 0x710166f9e0 — ROBOTGYRO_MOVE_BASE_FRAME (24B)
u32 ROBOTGYRO_MOVE_BASE_FRAME_166f9e0() { return *(u32*)FPA2_3(0xa48, 0x158, 0x2c); }
// 0x710166fa00 — ROBOTGYRO_MOVE_RANDOM_FRAME (24B)
u32 ROBOTGYRO_MOVE_RANDOM_FRAME_166fa00() { return *(u32*)FPA2_3(0xa48, 0x158, 0x30); }

// ---- app::wiifitball — Wii Fit Ball params ----
// Chain: FPA2 → +0xb60 → +0x120 → +field (3-deref, 24B)

// 0x7101678190 — WIIFITBALL_LIFE (24B)
u32 WIIFITBALL_LIFE_1678190() { return *(u32*)FPA2_3(0xb60, 0x120, 0x24); }
// 0x71016781f0 — WIIFITBALL_BOUND_MAX (24B)
u32 WIIFITBALL_BOUND_MAX_16781f0() { return *(u32*)FPA2_3(0xb60, 0x120, 0x30); }
// 0x7101678210 — WIIFITBALL_HEADING_SHOT_SPEED (24B)
float WIIFITBALL_HEADING_SHOT_SPEED_1678210() { return *(float*)FPA2_3(0xb60, 0x120, 0xc); }
// 0x7101678230 — WIIFITBALL_START_GROUND_GRAVITY (24B)
float WIIFITBALL_START_GROUND_GRAVITY_1678230() { return *(float*)FPA2_3(0xb60, 0x120, 0x64); }
