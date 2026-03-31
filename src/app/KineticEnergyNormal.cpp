#include "types.h"

// KineticEnergyNormal — operates on KineticEnergyNormal* directly
// Vec3 fields at struct offsets; simple getters return pointer to offset,
// setters copy 16-byte vec2 from source pointer to struct offset.

struct KineticEnergyNormal;
struct WeaponSnakeNikitaMissileKineticEnergyNormal;

namespace app::lua_bind {

// 71020f82e0 — add x0,x0,#0x40; ret
void* KineticEnergyNormal__get_accel_impl(KineticEnergyNormal* ke) {
    return reinterpret_cast<u8*>(ke) + 0x40;
}

// 71020f82f0 — add x0,x0,#0x50; ret
void* KineticEnergyNormal__get_stable_speed_impl(KineticEnergyNormal* ke) {
    return reinterpret_cast<u8*>(ke) + 0x50;
}

// 71020f8300 — add x0,x0,#0x60; ret
void* KineticEnergyNormal__get_brake_impl(KineticEnergyNormal* ke) {
    return reinterpret_cast<u8*>(ke) + 0x60;
}

// 71020f8310 — add x0,x0,#0x70; ret
void* KineticEnergyNormal__get_limit_speed_impl(KineticEnergyNormal* ke) {
    return reinterpret_cast<u8*>(ke) + 0x70;
}

// 71020f8360 — set_accel: copies 16 bytes from x1 to x0+0x40
// ldr x8,[x1,#0x8]; str x8,[x0,#0x48]; ldr x8,[x1]; str x8,[x0,#0x40]; ret
void KineticEnergyNormal__set_accel_impl(KineticEnergyNormal* ke, void* src) {
    auto* d = reinterpret_cast<u64*>(reinterpret_cast<u8*>(ke) + 0x40);
    auto* s = reinterpret_cast<u64*>(src);
    d[1] = s[1];
    d[0] = s[0];
}

// 71020f8380 — set_stable_speed: copies 16 bytes from x1 to x0+0x50
void KineticEnergyNormal__set_stable_speed_impl(KineticEnergyNormal* ke, void* src) {
    auto* d = reinterpret_cast<u64*>(reinterpret_cast<u8*>(ke) + 0x50);
    auto* s = reinterpret_cast<u64*>(src);
    d[1] = s[1];
    d[0] = s[0];
}

// 71020f83a0 — set_brake: copies 16 bytes from x1 to x0+0x60
void KineticEnergyNormal__set_brake_impl(KineticEnergyNormal* ke, void* src) {
    auto* d = reinterpret_cast<u64*>(reinterpret_cast<u8*>(ke) + 0x60);
    auto* s = reinterpret_cast<u64*>(src);
    d[1] = s[1];
    d[0] = s[0];
}

// 71020f83c0 — set_limit_speed: copies 16 bytes from x1 to x0+0x70
void KineticEnergyNormal__set_limit_speed_impl(KineticEnergyNormal* ke, void* src) {
    auto* d = reinterpret_cast<u64*>(reinterpret_cast<u8*>(ke) + 0x70);
    auto* s = reinterpret_cast<u64*>(src);
    d[1] = s[1];
    d[0] = s[0];
}

// 71020f83e0 — mov w8,#0x1; strb w8,[x0,#0x80]; ret
void KineticEnergyNormal__on_consider_ground_normal_impl(KineticEnergyNormal* ke) {
    *reinterpret_cast<u8*>(reinterpret_cast<u8*>(ke) + 0x80) = 1;
}

// 71020f83f0 — strb wzr,[x0,#0x80]; ret
void KineticEnergyNormal__off_consider_ground_normal_impl(KineticEnergyNormal* ke) {
    *reinterpret_cast<u8*>(reinterpret_cast<u8*>(ke) + 0x80) = 0;
}

// Skip: set_speed_impl (SIMD: ldr q0, movi, ext, ext, str q0)
// Skip: set_speed_3d_impl (SIMD: ldr q0, fmov, ext, mov, mov, str q0)

// --- WeaponSnakeNikitaMissileKineticEnergyNormal ---

// 7102164020 — str s0,[x0,#0xa0]; ret
void WeaponSnakeNikitaMissileKineticEnergyNormal__set_rot_z_impl(
        WeaponSnakeNikitaMissileKineticEnergyNormal* ke, f32 val) {
    *reinterpret_cast<f32*>(reinterpret_cast<u8*>(ke) + 0xa0) = val;
}

// 7102164030 — ldr s0,[x0,#0xa0]; ret
f32 WeaponSnakeNikitaMissileKineticEnergyNormal__rot_z_impl(
        WeaponSnakeNikitaMissileKineticEnergyNormal* ke) {
    return *reinterpret_cast<f32*>(reinterpret_cast<u8*>(ke) + 0xa0);
}

// --- WeaponKineticEnergyGravity ---

struct WeaponKineticEnergyGravity;

// 71021362f0 — str s0,[x0,#0x34]; ret
void WeaponKineticEnergyGravity__set_accel_impl(WeaponKineticEnergyGravity* ke, f32 val) {
    *reinterpret_cast<f32*>(reinterpret_cast<u8*>(ke) + 0x34) = val;
}

// 7102136300 — SIMD: set speed Y component at +0x10
void WeaponKineticEnergyGravity__set_speed_impl(WeaponKineticEnergyGravity* ke, f32 val) {
    // ldr q1,[x0,#0x10]; mov v1.S[1],v0.S[0]; str q1,[x0,#0x10]; ret
    // Sets the Y component (index 1) of the Vec3 at offset +0x10
    reinterpret_cast<f32*>(reinterpret_cast<u8*>(ke) + 0x10)[1] = val;
}

// 7102136310 — ldr s0,[x0,#0x38]; ret
f32 WeaponKineticEnergyGravity__get_limit_speed_impl(WeaponKineticEnergyGravity* ke) {
    return *reinterpret_cast<f32*>(reinterpret_cast<u8*>(ke) + 0x38);
}

} // namespace app::lua_bind
