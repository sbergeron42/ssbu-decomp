#include "types.h"

// KineticEnergyNormal -- operates on KineticEnergyNormal* directly
// Vec3 fields at struct offsets; simple getters return pointer to offset,
// setters copy 16-byte vec2 from source pointer to struct offset.

struct KineticEnergyNormal {
    u8  pad_0x00[0x10];
    u8  speed[0x10];                // +0x10 (v4sf)
    u8  pad_0x20[0x20];
    u8  accel[0x10];                // +0x40
    u8  stable_speed[0x10];         // +0x50
    u8  brake[0x10];                // +0x60
    u8  limit_speed[0x10];          // +0x70
    u8  consider_ground_normal;     // +0x80
};
struct WeaponSnakeNikitaMissileKineticEnergyNormal;

namespace app::lua_bind {

// 71020f82e0 -- add x0,x0,#0x40; ret
void* KineticEnergyNormal__get_accel_impl(KineticEnergyNormal* ke) {
    return ke->accel;
}

// 71020f82f0 -- add x0,x0,#0x50; ret
void* KineticEnergyNormal__get_stable_speed_impl(KineticEnergyNormal* ke) {
    return ke->stable_speed;
}

// 71020f8300 -- add x0,x0,#0x60; ret
void* KineticEnergyNormal__get_brake_impl(KineticEnergyNormal* ke) {
    return ke->brake;
}

// 71020f8310 -- add x0,x0,#0x70; ret
void* KineticEnergyNormal__get_limit_speed_impl(KineticEnergyNormal* ke) {
    return ke->limit_speed;
}

// 71020f8360 -- set_accel: copies 16 bytes from x1 to x0+0x40
// ldr x8,[x1,#0x8]; str x8,[x0,#0x48]; ldr x8,[x1]; str x8,[x0,#0x40]; ret
void KineticEnergyNormal__set_accel_impl(KineticEnergyNormal* ke, void* src) {
    auto* d = reinterpret_cast<u64*>(ke->accel);
    auto* s = reinterpret_cast<u64*>(src);
    d[1] = s[1];
    d[0] = s[0];
}

// 71020f8380 -- set_stable_speed: copies 16 bytes from x1 to x0+0x50
void KineticEnergyNormal__set_stable_speed_impl(KineticEnergyNormal* ke, void* src) {
    auto* d = reinterpret_cast<u64*>(ke->stable_speed);
    auto* s = reinterpret_cast<u64*>(src);
    d[1] = s[1];
    d[0] = s[0];
}

// 71020f83a0 -- set_brake: copies 16 bytes from x1 to x0+0x60
void KineticEnergyNormal__set_brake_impl(KineticEnergyNormal* ke, void* src) {
    auto* d = reinterpret_cast<u64*>(ke->brake);
    auto* s = reinterpret_cast<u64*>(src);
    d[1] = s[1];
    d[0] = s[0];
}

// 71020f83c0 -- set_limit_speed: copies 16 bytes from x1 to x0+0x70
void KineticEnergyNormal__set_limit_speed_impl(KineticEnergyNormal* ke, void* src) {
    auto* d = reinterpret_cast<u64*>(ke->limit_speed);
    auto* s = reinterpret_cast<u64*>(src);
    d[1] = s[1];
    d[0] = s[0];
}

// 71020f83e0 -- mov w8,#0x1; strb w8,[x0,#0x80]; ret
void KineticEnergyNormal__on_consider_ground_normal_impl(KineticEnergyNormal* ke) {
    ke->consider_ground_normal = 1;
}

// 71020f83f0 -- strb wzr,[x0,#0x80]; ret
void KineticEnergyNormal__off_consider_ground_normal_impl(KineticEnergyNormal* ke) {
    ke->consider_ground_normal = 0;
}

// 71020f8320 -- SIMD vec2 copy with zeroed zw: ldr q0,[x1]; movi v1.2d,#0; ext v1.16b,v0.16b,v1.16b,#8; ext v0.16b,v0.16b,v1.16b,#8; str q0,[x0,#0x10]; ret
typedef float v4sf __attribute__((vector_size(16)));
void KineticEnergyNormal__set_speed_impl(KineticEnergyNormal* ke, v4sf* src) {
    v4sf v = *src; v[2] = 0.0f; v[3] = 0.0f;
    *reinterpret_cast<v4sf*>(ke->speed) = v;
}

// 71020f8400 -- ldrb w0,[x0,#0x80]; ret
u8 KineticEnergyNormal__is_consider_ground_normal_impl(KineticEnergyNormal* ke) {
    return ke->consider_ground_normal;
}

// --- WeaponSnakeNikitaMissileKineticEnergyNormal ---
// (moved to modules/WeaponSnakeNikitaMissileKineticEnergyNormal.cpp)

// --- WeaponKineticEnergyGravity ---

struct WeaponKineticEnergyGravity {
    u8  pad_0x00[0x10];
    u8  speed[0x10];         // +0x10 (v4sf)
    u8  pad_0x20[0x14];
    f32 accel;               // +0x34
    f32 limit_speed;         // +0x38
};

// 71021362f0 -- str s0,[x0,#0x34]; ret
void WeaponKineticEnergyGravity__set_accel_impl(WeaponKineticEnergyGravity* ke, f32 val) {
    ke->accel = val;
}

// 7102136300 -- SIMD: set speed Y component at +0x10 (ldr q1, mov v1.S[1], str q1)
void WeaponKineticEnergyGravity__set_speed_impl(WeaponKineticEnergyGravity* ke, f32 val) {
    auto* v = reinterpret_cast<v4sf*>(ke->speed);
    (*v)[1] = val;
}

// 7102136310 -- ldr s0,[x0,#0x38]; ret
f32 WeaponKineticEnergyGravity__get_limit_speed_impl(WeaponKineticEnergyGravity* ke) {
    return ke->limit_speed;
}

// 7102136320 -- str s0,[x0,#0x38]; ret
void WeaponKineticEnergyGravity__set_limit_speed_impl(WeaponKineticEnergyGravity* ke, f32 val) {
    ke->limit_speed = val;
}

} // namespace app::lua_bind

