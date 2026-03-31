#include "app/BattleObjectModuleAccessor.h"

// ItemCameraModuleImpl — accesses CameraModule at accessor+0x60
// These operate on the inner camera subject struct

namespace app::lua_bind {

// 71020d3c60 — set_fix_rate (4 instructions: ldr ptr chain, str float)
void ItemMotionAnimcmdModuleImpl__set_fix_rate_impl(BattleObjectModuleAccessor* a, f32 rate) {
    auto* mac = *reinterpret_cast<void**>(reinterpret_cast<u8*>(a) + 0x188);
    auto* inner = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(mac) + 0x8);
    *reinterpret_cast<f32*>(inner + 0x48) = rate;
}

// 71020d2320 — clamp 4 camera subject positions against bounds from x1 (Vector4f min/max pairs)
// Pure SIMD: fcmgt+bsl+dup for per-lane clamp across 4 subject slots
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void ItemCameraModuleImpl__clamp_camera_subject_pos_impl(BattleObjectModuleAccessor* accessor, void* bounds) {
    asm(
        "ldr x8,[x0, #0x60]\n"
        "ldr q4,[x8, #0x90]\n"
        "ldr q1,[x1]\n"
        "fcmgt v6.4S,v1.4S,v4.4S\n"
        "mov v16.16B,v4.16B\n"
        "mov v16.S[0],v1.S[0]\n"
        "movi d0,#0x0\n"
        "dup v7.4S,v1.S[2]\n"
        "ldr q5,[x8, #0x170]\n"
        "mov v2.16B,v0.16B\n"
        "mov v2.S[0],v5.S[2]\n"
        "ldr q17,[x8, #0x250]\n"
        "mov v3.16B,v0.16B\n"
        "mov v3.S[0],v17.S[2]\n"
        "dup v6.4S,v6.S[0]\n"
        "bsl v6.16B,v16.16B,v4.16B\n"
        "mov v4.16B,v6.16B\n"
        "dup v16.4S,v6.S[1]\n"
        "mov v4.S[1],v1.S[2]\n"
        "fcmgt v16.4S,v16.4S,v7.4S\n"
        "dup v16.4S,v16.S[0]\n"
        "bsl v16.16B,v4.16B,v6.16B\n"
        "dup v4.4S,v1.S[1]\n"
        "fcmgt v6.4S,v5.4S,v4.4S\n"
        "dup v6.4S,v6.S[0]\n"
        "mov v5.D[1],v2.D[0]\n"
        "mov v2.16B,v5.16B\n"
        "mov v2.S[0],v1.S[1]\n"
        "bsl v6.16B,v2.16B,v5.16B\n"
        "ldr q2,[x8, #0x330]\n"
        "fcmgt v5.4S,v1.4S,v17.4S\n"
        "dup v5.4S,v5.S[0]\n"
        "mov v17.D[1],v3.D[0]\n"
        "mov v3.16B,v17.16B\n"
        "fcmgt v4.4S,v2.4S,v4.4S\n"
        "dup v4.4S,v4.S[0]\n"
        "mov v3.S[0],v1.S[0]\n"
        "bsl v5.16B,v3.16B,v17.16B\n"
        "mov v3.16B,v0.16B\n"
        "mov v3.S[0],v2.S[2]\n"
        "dup v17.4S,v1.S[3]\n"
        "mov v2.D[1],v3.D[0]\n"
        "mov v3.16B,v2.16B\n"
        "mov v3.S[0],v1.S[1]\n"
        "bsl v4.16B,v3.16B,v2.16B\n"
        "mov v2.16B,v6.16B\n"
        "dup v3.4S,v6.S[1]\n"
        "mov v2.S[1],v1.S[3]\n"
        "fcmgt v3.4S,v17.4S,v3.4S\n"
        "dup v3.4S,v3.S[0]\n"
        "bsl v3.16B,v2.16B,v6.16B\n"
        "dup v2.4S,v5.S[1]\n"
        "mov v6.16B,v5.16B\n"
        "fcmgt v2.4S,v17.4S,v2.4S\n"
        "mov v6.S[1],v1.S[3]\n"
        "dup v2.4S,v2.S[0]\n"
        "bsl v2.16B,v6.16B,v5.16B\n"
        "mov v5.16B,v4.16B\n"
        "mov v5.S[1],v1.S[2]\n"
        "dup v1.4S,v4.S[1]\n"
        "fcmgt v1.4S,v1.4S,v7.4S\n"
        "dup v1.4S,v1.S[0]\n"
        "mov v6.16B,v0.16B\n"
        "mov v6.S[0],v16.S[2]\n"
        "mov v16.D[1],v6.D[0]\n"
        "bsl v1.16B,v5.16B,v4.16B\n"
        "mov v4.16B,v0.16B\n"
        "mov v5.16B,v0.16B\n"
        "mov v4.S[0],v3.S[2]\n"
        "mov v0.S[0],v1.S[2]\n"
        "mov v5.S[0],v2.S[2]\n"
        "str q16,[x8, #0x90]\n"
        "mov v3.D[1],v4.D[0]\n"
        "mov v2.D[1],v5.D[0]\n"
        "mov v1.D[1],v0.D[0]\n"
        "str q3,[x8, #0x170]\n"
        "str q2,[x8, #0x250]\n"
        "str q1,[x8, #0x330]\n"
        "ret\n"
    );
}
#endif

// 71020d22d0 — load vec4 [x,y,z,w] from x1, build 4 pos pairs and store to 4 camera slots
// Slot 0 (+0x90): [x, z, 0, 0]   Slot 1 (+0x170): [y, w, 0, 0]
// Slot 2 (+0x250): [x, w, 0, 0]  Slot 3 (+0x330): [y, z, 0, 0]
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void ItemCameraModuleImpl__set_camera_subject_pos_4_points_impl(BattleObjectModuleAccessor* accessor, void* vec4) {
    asm(
        "ldr q0,[x1]\n"
        "dup v1.2S,v0.S[1]\n"
        "mov v2.16B,v0.16B\n"
        "mov v3.16B,v0.16B\n"
        "mov v4.16B,v1.16B\n"
        "ldr x8,[x0, #0x60]\n"
        "mov v2.S[1],v0.S[2]\n"
        "mov v3.S[1],v0.S[3]\n"
        "mov v1.S[1],v0.S[2]\n"
        "mov v4.S[1],v0.S[3]\n"
        "movi d0,#0x0\n"
        "mov v2.D[1],v0.D[0]\n"
        "mov v3.D[1],v0.D[0]\n"
        "mov v1.D[1],v0.D[0]\n"
        "mov v4.D[1],v0.D[0]\n"
        "str q2,[x8, #0x90]\n"
        "str q3,[x8, #0x250]\n"
        "str q1,[x8, #0x330]\n"
        "str q4,[x8, #0x170]\n"
        "ret\n"
    );
}
#endif

} // namespace app::lua_bind
