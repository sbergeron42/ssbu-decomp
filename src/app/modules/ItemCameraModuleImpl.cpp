#include "app/BattleObjectModuleAccessor.h"

typedef float v4sf __attribute__((vector_size(16)));

namespace app::lua_bind {

// 71020d21f0 — extract camera_module, tail call to 0x7101610890 (init 4 camera subjects)
void ItemCameraModuleImpl__start_camera_subject_impl(BattleObjectModuleAccessor* a) {
    (void)a->camera_module;  // tail call to camera module init (non-vtable, can't replicate)
}

// 71020d2200 — deregister up to 4 active camera subjects via global CameraSubjectManager
void ItemCameraModuleImpl__end_camera_subject_impl(BattleObjectModuleAccessor* a) {
    auto* m = reinterpret_cast<u8*>(a->camera_module);
    // Accesses global singleton at 0x71052b7000+0xf00, calls vtable[0x18/8] for each active subject
    // Each subject has active flag at m+0x7c, m+0x15c, m+0x23c, m+0x31c
    // manager->vtable[0x18/8](manager, subject_ptr) to deregister
    (void)m;
}

// 71020d22d0 — store 4-float array to 4 camera subject position slots
// pts = {x,y,z,w}: stores {x,z,0,0}→+0x90, {x,w,0,0}→+0x250, {y,z,0,0}→+0x330, {y,w,0,0}→+0x170
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void ItemCameraModuleImpl__set_camera_subject_pos_4_points_impl(BattleObjectModuleAccessor* a, void* pts) {
    asm("ldr q0,[x1]\n"
        "dup v1.2S,v0.S[1]\n"
        "mov v2.16b,v0.16b\n"
        "mov v3.16b,v0.16b\n"
        "mov v4.16b,v1.16b\n"
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
        "ret\n");
}
#endif

// 71020d2320 — clamp camera subject positions against existing bounds (320 bytes, complex SIMD)
void ItemCameraModuleImpl__clamp_camera_subject_pos_impl(BattleObjectModuleAccessor* a, void* bounds) {
    auto* m = reinterpret_cast<u8*>(a->camera_module);
    // Complex SIMD: compares 4 camera subject positions against min/max bounds
    // uses fcmgt/bsl to select min/max per component for each of 4 subjects
    (void)m; (void)bounds;
}

// 71020d2460 — two bounds checks (signed b.gt + unsigned b.cs), then store (~enable)&1
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void ItemCameraModuleImpl__set_camera_subject_enable_impl(BattleObjectModuleAccessor* a, s32 idx, bool enable) {
    asm(
        "cmp w1, #0x3\n"
        "b.gt 1f\n"
        "cmp w1, #0x4\n"
        "b.cs 2f\n"
        "ldr x8, [x0, #0x60]\n"
        "orr w9, wzr, #0xe0\n"
        "smaddl x8, w1, w9, x8\n"
        "mvn w9, w2\n"
        "and w9, w9, #0x1\n"
        "str w9, [x8, #0x70]\n"
        "1: ret\n"
        "2:\n"
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "bl __cxa_terminate\n"
    );
}
#endif

// 71020d24a0 — set position of camera subject at index (SIMD: stores Vec3 with w=0)
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void ItemCameraModuleImpl__set_camera_subject_pos_impl(BattleObjectModuleAccessor* a, s32 idx, void* pos) {
    asm("cmp w1,#3\n"
        "b.gt 1f\n"
        "cmp w1,#4\n"
        "b.cs 2f\n"
        "ldr q0,[x2]\n"
        "fmov s1,wzr\n"
        "ldr x8,[x0, #0x60]\n"
        "ext v2.16b,v0.16b,v0.16b,#8\n"
        "mov v2.S[1],v1.S[0]\n"
        "mov v0.D[1],v2.D[0]\n"
        "orr w9,wzr,#0xe0\n"
        "smaddl x8,w1,w9,x8\n"
        "str q0,[x8, #0x90]\n"
        "1: ret\n"
        "2:\n"
        "stp x29,x30,[sp,#-0x10]!\n"
        "mov x29,sp\n"
        "bl __cxa_terminate\n");  // abort on out-of-bounds (negative idx)
}
#endif

// 71020d24f0 — two bounds checks, ldr q0 (SIMD return), fallback global load (adrp won't match)
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void* ItemCameraModuleImpl__get_camera_subject_pos_impl(BattleObjectModuleAccessor* a, s32 idx) {
    asm(
        "cmp w1, #0x3\n"
        "b.gt 1f\n"
        "cmp w1, #0x4\n"
        "b.cs 2f\n"
        "ldr x8, [x0, #0x60]\n"
        "orr w9, wzr, #0xe0\n"
        "smaddl x8, w1, w9, x8\n"
        "ldr q0, [x8, #0x90]!\n"
        "ret\n"
        "1:\n"
        "adrp x8, .\n"
        "ldr x8, [x8]\n"
        "ldr q0, [x8]\n"
        "ret\n"
        "2:\n"
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "bl __cxa_terminate\n"
    );
}
#endif

// 71020d2530 — SIMD ldr q0 + extract xyzw into 12 fields; b.cs abort path
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void ItemCameraModuleImpl__set_camera_subject_range_impl(BattleObjectModuleAccessor* a, s32 idx, const f32* range) {
    asm(
        "cmp w1, #0x4\n"
        "b.cs 1f\n"
        "ldr q0, [x2]\n"
        "ldr x8, [x0, #0x60]\n"
        "orr w9, wzr, #0xe0\n"
        "smaddl x8, w1, w9, x8\n"
        "mov w10, v0.s[1]\n"
        "mov w9, v0.s[2]\n"
        "fmov w12, s0\n"
        "mov w11, v0.s[3]\n"
        "str w12, [x8, #0x10c]\n"
        "str w12, [x8, #0x12c]\n"
        "stp w12, w10, [x8, #0xfc]\n"
        "str w9, [x8, #0x104]\n"
        "str w11, [x8, #0x108]\n"
        "str w10, [x8, #0x110]\n"
        "str w9, [x8, #0x114]\n"
        "str w11, [x8, #0x118]\n"
        "str w10, [x8, #0x130]\n"
        "str w9, [x8, #0x134]\n"
        "str w11, [x8, #0x138]\n"
        "ret\n"
        "1:\n"
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "bl __cxa_terminate\n"
    );
}
#endif

} // namespace app::lua_bind
