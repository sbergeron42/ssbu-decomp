#pragma once

// KineticModule vtable layout recovered from lua_bind dispatchers
// Accessed via BattleObjectModuleAccessor+0x68
// Polymorphic base shared by Fighter and Item kinetic module variants
//
// Vtable offsets [confirmed: Ghidra decompilation of 29 lua_bind functions]:
//   0x60  get_energy(int) → void* [inferred: returns KineticEnergy*]
//   0x90  clear_speed_all()
//   0x98  clear_speed_energy_id(int)
//   0xA0  clear_speed_attr(u64)
//   0xA8  suspend_energy_all()
//   0xB0  resume_energy_all()
//   0xB8  unable_energy_all()
//   0xC0  get_sum_speed(void* out) → void*
//   0xC8  get_sum_speed_x(void* out) → void*
//   0xD0  get_sum_speed_y(void* out) → void*
//   0xD8  get_sum_speed_length(void* out) → void*
//   0xE0  get_sum_speed3f(void* out) → void*
//   0xE8  get_sum_rotation(u64)
//   0xF0  set_consider_ground_friction(bool, int)
//   0xF8  mul_speed(void*, u64)
//   0x100 mul_accel(Vector3f const&, int)
//   0x108 reflect_speed(Vector3f const&, int)
//   0x110 reflect_accel(Vector3f const&, int)
//   0x118 change_kinetic(int)
//   0x120 get_kinetic_type() → int
//   0x128 enable_energy(int)
//   0x130 unable_energy(int)
//   0x138 is_enable_energy(int) → bool
//   0x140 suspend_energy(int)
//   0x148 resume_energy(int)
//   0x150 is_suspend_energy(int) → bool
//   0x158 add_speed(void*)
//   0x160 add_speed_outside(void*, u64)
//   0x168 sleep(bool)

namespace app {
struct KineticModule;
} // namespace app
