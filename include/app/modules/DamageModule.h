#pragma once

// DamageModule vtable layout recovered from lua_bind dispatchers
// Accessed via BattleObjectModuleAccessor+0xA8
//
// Vtable offsets [confirmed: Ghidra decompilation of 35 lua_bind functions]:
//   0x50  sleep(bool)
//   0x60  init_damage()
//   0xA0  set_force_damage(uint, Vector3f const&, int, int, bool, bool, bool, bool)
//   0xC0  add_damage(u64)
//   0xC8  damage(u64) → void*
//   0xD0  reaction(u64) → void*
//   0xD8  power_max(u64) → void*
//   0xE0  check_no_reaction(u64)
//   0xE8  set_no_reaction_mode_status(u64, u64)
//   0xF8  reset_no_reaction_mode_status()
//   0x120 set_no_reaction_damage_power()
//   0x128 set_no_reaction_no_effect(bool)
//   0x130 is_no_reaction_mode_perfect() → bool
//   0x188 damage_log() → void*
//   0x1B0 set_attacker_info(u64)
//   0x1D8 is_capture_cut() → bool
//   0x1E8 set_ignore_capture_cut_no(u64)
//   0x210 set_damage_mul()
//   0x218 set_damage_mul_2nd()
//   0x220 set_force_damage_mul()
//   0x228 set_reaction_mul()
//   0x230 set_reaction_mul_2nd()
//   0x238 set_reaction_mul_4th()
//   0x240 set_weak_param(u64)
//   0x248 set_damage_lock(bool)
//   0x250 set_damage_lock_2nd(bool)
//   0x258 is_damage_lock() → bool
//   0x268 heal(u64)
//   0x288 overwrite_log_reaction_frame()
//   0x290 start_damage_info_log()
//   0x298 end_damage_info_log()
//   0x2A0 set_force_damage_from_last_damage()
//   0x2A8 is_paralyze() → bool
//   0x2D0 set_critical_hit(bool)
//   0x2D8 is_critical_hit() → bool

namespace app {
struct DamageModule;
} // namespace app
