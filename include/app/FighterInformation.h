#pragma once

#include "types.h"

namespace app {

// FighterInformation — operates on its own pointer
// Access pattern: ldr x8,[x0,#0x8] gets internal data pointer, then field reads
// Known internal data fields (via data ptr at +0x8):
//   +0x38   f32 hp_base
//   +0x3C   f32 hp_temp
//   +0x51   u8  fighter_color
//   +0x59   bool rabbit_cap
//   +0x5A   bool reflector
//   +0x5B   bool superleaf
//   +0x5C   bool rocketbelt
//   +0x5D   bool screw
//   +0x5E   bool backshield
//   +0x92   bool operation_cpu
//   +0x93   bool no_change_hp
//   +0xCC   s32 dead_count[3]
//   +0xD8   u32 stock_count
//   +0x14C  s32 suicide_count[6]
//   +0x158  s32 suicide_count_b[6]
//   +0x1A3  bool last_dead_suicide
//   +0x1AC  f32 add_rebirth_wait_frame
//   +0x36C  f32 gravity
//   +0x38C  bool on_rebirth
//   +0x3AC  u8  fighter_category
//   +0x9A0  u32 summon_boss_id
//   +0x9AC  u32 summon_bomb_ready_frame
//   +0x9B0  u32 summon_pre_bomb_effect_frame
//   +0x9BC  f32 summon_suicide_bomb_attack_mul
//   +0x9C0  f32 summon_suicide_bomb_reaction_mul
//   +0x9CA  bool battle_event_stick_reverse
struct FighterInformation;

} // namespace app
