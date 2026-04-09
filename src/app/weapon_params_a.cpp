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

// ---- app::pickelobject — Pickel (Steve) object params ----
// Chain: FPA2 → +0x13b0 → +field (2-deref, 20B)

// 0x710166e110 — flash_start_frame (20B)
u32 flash_start_frame_166e110() { return *(u32*)FPA2_2(0x13b0, 0x51c); }
