#include "types.h"

// KineticEnergyNormal -- operates on KineticEnergyNormal* directly
// Vec3 fields at struct offsets; simple getters return pointer to offset,
// setters copy 16-byte vec2 from source pointer to struct offset.

struct KineticEnergyNormal;
struct WeaponSnakeNikitaMissileKineticEnergyNormal;

namespace app::lua_bind {

// 71020f82e0 -- add x0,x0,#0x40; ret
void* KineticEnergyNormal__get_accel_impl(KineticEnergyNormal* ke) {
    return reinterpret_cast<u8*>(ke) + 0x40;
}

// 71020f82f0 -- add x0,x0,#0x50; ret
void* KineticEnergyNormal__get_stable_speed_impl(KineticEnergyNormal* ke) {
    return reinterpret_cast<u8*>(ke) + 0x50;
}

// 71020f8300 -- add x0,x0,#0x60; ret
void* KineticEnergyNormal__get_brake_impl(KineticEnergyNormal* ke) {
    return reinterpret_cast<u8*>(ke) + 0x60;
}

// 71020f8310 -- add x0,x0,#0x70; ret
void* KineticEnergyNormal__get_limit_speed_impl(KineticEnergyNormal* ke) {
    return reinterpret_cast<u8*>(ke) + 0x70;
}

// 71020f8360 -- set_accel: copies 16 bytes from x1 to x0+0x40
// ldr x8,[x1,#0x8]; str x8,[x0,#0x48]; ldr x8,[x1]; str x8,[x0,#0x40]; ret
void KineticEnergyNormal__set_accel_impl(KineticEnergyNormal* ke, void* src) {
    auto* d = reinterpret_cast<u64*>(reinterpret_cast<u8*>(ke) + 0x40);
    auto* s = reinterpret_cast<u64*>(src);
    d[1] = s[1];
    d[0] = s[0];
}

// 71020f8380 -- set_stable_speed: copies 16 bytes from x1 to x0+0x50
void KineticEnergyNormal__set_stable_speed_impl(KineticEnergyNormal* ke, void* src) {
    auto* d = reinterpret_cast<u64*>(reinterpret_cast<u8*>(ke) + 0x50);
    auto* s = reinterpret_cast<u64*>(src);
    d[1] = s[1];
    d[0] = s[0];
}

// 71020f83a0 -- set_brake: copies 16 bytes from x1 to x0+0x60
void KineticEnergyNormal__set_brake_impl(KineticEnergyNormal* ke, void* src) {
    auto* d = reinterpret_cast<u64*>(reinterpret_cast<u8*>(ke) + 0x60);
    auto* s = reinterpret_cast<u64*>(src);
    d[1] = s[1];
    d[0] = s[0];
}

// 71020f83c0 -- set_limit_speed: copies 16 bytes from x1 to x0+0x70
void KineticEnergyNormal__set_limit_speed_impl(KineticEnergyNormal* ke, void* src) {
    auto* d = reinterpret_cast<u64*>(reinterpret_cast<u8*>(ke) + 0x70);
    auto* s = reinterpret_cast<u64*>(src);
    d[1] = s[1];
    d[0] = s[0];
}

// 71020f83e0 -- mov w8,#0x1; strb w8,[x0,#0x80]; ret
void KineticEnergyNormal__on_consider_ground_normal_impl(KineticEnergyNormal* ke) {
    *reinterpret_cast<u8*>(reinterpret_cast<u8*>(ke) + 0x80) = 1;
}

// 71020f83f0 -- strb wzr,[x0,#0x80]; ret
void KineticEnergyNormal__off_consider_ground_normal_impl(KineticEnergyNormal* ke) {
    *reinterpret_cast<u8*>(reinterpret_cast<u8*>(ke) + 0x80) = 0;
}

// 71020f8320 -- SIMD vec2 copy with zeroed zw: ldr q0,[x1]; movi v1.2d,#0; ext v1.16b,v0.16b,v1.16b,#8; ext v0.16b,v0.16b,v1.16b,#8; str q0,[x0,#0x10]; ret
typedef float v4sf __attribute__((vector_size(16)));
void KineticEnergyNormal__set_speed_impl(KineticEnergyNormal* ke, v4sf* src) {
    v4sf v = *src; v[2] = 0.0f; v[3] = 0.0f;
    *reinterpret_cast<v4sf*>(reinterpret_cast<u8*>(ke) + 0x10) = v;
}

// 71020f8340 -- SIMD 3d: ldr q0,[x1]; fmov s1,wzr; ext v2,v0,v0,#8; mov v2.S[1],v1.S[0]; mov v0.D[1],v2.D[0]; str q0,[x0,#0x10]; ret
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void KineticEnergyNormal__set_speed_3d_impl(KineticEnergyNormal* ke, v4sf* src) {
    asm("ldr q0, [x1]\n"
        "fmov s1, wzr\n"
        "ext v2.16b, v0.16b, v0.16b, #8\n"
        "mov v2.s[1], v1.s[0]\n"
        "mov v0.d[1], v2.d[0]\n"
        "str q0, [x0, #0x10]\n"
        "ret\n");
}
#else
void KineticEnergyNormal__set_speed_3d_impl(KineticEnergyNormal* ke, v4sf* src) {
    v4sf v = *src;
    f32 zero = 0.0f;
    v4sf rot = __builtin_shufflevector(v, v, 2, 3, 0, 1);
    rot[1] = zero;
    typedef unsigned long long v2di __attribute__((vector_size(16)));
    v2di vi = (v2di)v;
    vi[1] = ((v2di)rot)[0];
    *reinterpret_cast<v4sf*>(reinterpret_cast<u8*>(ke) + 0x10) = (v4sf)vi;
}
#endif

// 71020f8400 -- ldrb w0,[x0,#0x80]; ret
u8 KineticEnergyNormal__is_consider_ground_normal_impl(KineticEnergyNormal* ke) {
    return *reinterpret_cast<u8*>(reinterpret_cast<u8*>(ke) + 0x80);
}

// --- WeaponSnakeNikitaMissileKineticEnergyNormal ---
// (moved to modules/WeaponSnakeNikitaMissileKineticEnergyNormal.cpp)

// --- WeaponKineticEnergyGravity ---

struct WeaponKineticEnergyGravity;

// 71021362f0 -- str s0,[x0,#0x34]; ret
void WeaponKineticEnergyGravity__set_accel_impl(WeaponKineticEnergyGravity* ke, f32 val) {
    *reinterpret_cast<f32*>(reinterpret_cast<u8*>(ke) + 0x34) = val;
}

// 7102136300 -- SIMD: set speed Y component at +0x10 (ldr q1, mov v1.S[1], str q1)
typedef float v4sf __attribute__((vector_size(16)));
void WeaponKineticEnergyGravity__set_speed_impl(WeaponKineticEnergyGravity* ke, f32 val) {
    auto* p = reinterpret_cast<u8*>(ke) + 0x10;
    v4sf v = *reinterpret_cast<v4sf*>(p);
    v[1] = val;
    *reinterpret_cast<v4sf*>(p) = v;
}

// 7102136310 -- ldr s0,[x0,#0x38]; ret
f32 WeaponKineticEnergyGravity__get_limit_speed_impl(WeaponKineticEnergyGravity* ke) {
    return *reinterpret_cast<f32*>(reinterpret_cast<u8*>(ke) + 0x38);
}

// 7102136320 -- str s0,[x0,#0x38]; ret
void WeaponKineticEnergyGravity__set_limit_speed_impl(WeaponKineticEnergyGravity* ke, f32 val) {
    *reinterpret_cast<f32*>(reinterpret_cast<u8*>(ke) + 0x38) = val;
}

} // namespace app::lua_bind
