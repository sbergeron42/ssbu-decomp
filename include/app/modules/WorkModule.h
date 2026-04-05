#pragma once

namespace app {

// WorkModule -- fighter variable storage (floats, ints, flags, transition terms)
// Accessed at BattleObjectModuleAccessor offset +0x50
// Internal allocation: 0x1920 bytes
//
// Vtable layout (offsets from vtable base):
//   0x58  get_float(s32 index) -> f32
//   0x60  set_float(s32 index, f32 value)
//   0x70  rnd_float(s32 index) -> f32
//   0x78  add_float(s32 index, f32 value) -> f32
//   0x80  sub_float(s32 index, f32 value) -> f32
//   0x88  mul_float(s32 index, f32 value) -> f32
//   0x90  div_float(s32 index, f32 value) -> f32
//   0x98  get_int(s32 index) -> s32
//   0xa0  set_int(s32 index, s32 value)
//   0xb0  get_int64(s32 index) -> s64
//   0xb8  set_int64(s32 index, s64 value)
//   0xc0  rnd_int(s32 low, s32 high, s32 seed) -> s32
//   0xc8  inc_int(s32 index)
//   0xd0  dec_int(s32 index)
//   0xd8  add_int(s32 index, s32 value)
//   0xe0  sub_int(s32 index, s32 value)
//   0xe8  mul_int(s32 index, s32 value)
//   0xf0  div_int(s32 index, s32 value)
//   0xf8  count_down_int(s32 index, s32 min, s32 step)
//   0x108 is_flag(s32 index) -> bool
//   0x110 on_flag(s32 index)
//   0x120 off_flag(s32 index)
//   0x130 set_flag(bool value, s32 index)
//   0x138 turn_off_flag(s32 index)
//   0x140 enable_transition_term_group(s32 group)
//   0x148 unable_transition_term_group(s32 group)
//   0x150 clear_transition_term_group(s32 group)
//   0x158 is_enable_transition_term_group(s32 group) -> bool
//   0x160 enable_transition_term_group_ex(s32 group)
//   0x168 enable_transition_term_group_ex_all(s32 group)
//   0x170 unable_transition_term_group_ex(s32 group)
//   0x178 unable_transition_term_group_ex_all(s32 group)
//   0x180 is_enable_transition_term(s32 term) -> bool
//   0x188 enable_transition_term(s32 term)
//   0x190 unable_transition_term(s32 term)
//   0x198 clear_transition_term()
//   0x1a0 is_enable_transition_term_forbid(s32 term) -> bool
//   0x1a8 enable_transition_term_forbid(s32 term)
//   0x1b0 unable_transition_term_forbid(s32 term)
//   0x1b8 enable_transition_term_forbid_group(s32 group)
//   0x1c0 unable_transition_term_forbid_group(s32 group)
//   0x1c8 clear_transition_term_forbid()
//   0x1f8 enable_transition_term_forbid_indivi(s32 term)
//   0x200 unable_transition_term_forbid_indivi(s32 term)
//   0x220 clear_all(s32 flags)
//   0x248 get_param_int(s32 hash1, s32 hash2) -> s32
//   0x258 get_param_int64(s32 hash1, s32 hash2) -> s64
//   0x268 get_param_float(s32 hash1, s32 hash2) -> f32
//   0x278 set_customize_no(s32 p1, s32 p2)
//   0x280 calc_param(bool p1, bool p2)  [FighterWorkModuleImpl]
// All vtable method names derived from .dynsym lua_bind::WorkModule__*_impl dispatcher analysis.

struct WorkModule;

} // namespace app
