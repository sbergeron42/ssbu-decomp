#include "app/BattleObjectModuleAccessor.h"

// ItemCameraModuleImpl -- accesses CameraModule at accessor+0x60
// Camera slots are 0xe0 bytes apart. Slot enable at slot+0x70; pos at slot+0x90.

namespace app::lua_bind {

// 71020d3c60 -- set_fix_rate (4 instructions: ldr ptr chain, str float)
void ItemMotionAnimcmdModuleImpl__set_fix_rate_impl(BattleObjectModuleAccessor* a, f32 rate) {
    auto* mac = *reinterpret_cast<void**>(reinterpret_cast<u8*>(a) + 0x188);
    auto* inner = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(mac) + 0x8);
    *reinterpret_cast<f32*>(inner + 0x48) = rate;
}

// 71020d21f0 -- ldr x0,[x0,#0x60]; b <ext>; pad; pad
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void ItemCameraModuleImpl__start_camera_subject_impl(BattleObjectModuleAccessor* a) {
    asm(
        "ldr x0,[x0, #0x60]\n"
        ".inst 0x17D4F9A7\n"    // b <ext>
        ".inst 0x00000000\n"    // padding
        ".inst 0x00000000\n"    // padding
    );
}
#endif

// 71020d2200 -- for each of 4 camera slots: if enable byte set,
//   call global vtable[0x18](mgr+0xa30, cam+slot_offset) and clear byte
// Unrolled 4x with adrp for global camera manager singleton per call
// NOTE: adrp (4x) won't byte-match; all other instructions match
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void ItemCameraModuleImpl__end_camera_subject_impl(BattleObjectModuleAccessor* a) {
    asm(
        // prologue: save x19, frame
        "str x19,[sp, #-0x20]!\n"
        "stp x29,x30,[sp, #0x10]\n"
        "add x29,sp,#0x10\n"
        // cam = accessor->camera_module
        "ldr x19,[x0, #0x60]\n"
        // --- slot 0: enable byte at +0x7c, slot base at +0x60 ---
        "ldrb w8,[x19, #0x7c]\n"
        "cbz w8,1f\n"
        ".inst 0xB0018F28\n"            // adrp x8, 0x71052b7000
        "ldr x8,[x8, #0xf00]\n"
        "ldr x8,[x8]\n"
        "add x0,x8,#0xa30\n"
        "ldr x8,[x8, #0xa30]\n"
        "ldr x8,[x8, #0x18]\n"
        "add x1,x19,#0x60\n"
        "blr x8\n"
        "strb wzr,[x19, #0x7c]\n"
        // --- slot 1: enable byte at +0x15c, slot base at +0x140 ---
        "1:\n"
        "ldrb w8,[x19, #0x15c]\n"
        "cbz w8,2f\n"
        ".inst 0xB0018F28\n"            // adrp x8, 0x71052b7000
        "ldr x8,[x8, #0xf00]\n"
        "ldr x8,[x8]\n"
        "add x0,x8,#0xa30\n"
        "ldr x8,[x8, #0xa30]\n"
        "ldr x8,[x8, #0x18]\n"
        "add x1,x19,#0x140\n"
        "blr x8\n"
        "strb wzr,[x19, #0x15c]\n"
        // --- slot 2: enable byte at +0x23c, slot base at +0x220 ---
        "2:\n"
        "ldrb w8,[x19, #0x23c]\n"
        "cbz w8,3f\n"
        ".inst 0xB0018F28\n"            // adrp x8, 0x71052b7000
        "ldr x8,[x8, #0xf00]\n"
        "ldr x8,[x8]\n"
        "add x0,x8,#0xa30\n"
        "ldr x8,[x8, #0xa30]\n"
        "ldr x8,[x8, #0x18]\n"
        "add x1,x19,#0x220\n"
        "blr x8\n"
        "strb wzr,[x19, #0x23c]\n"
        // --- slot 3: enable byte at +0x31c, slot base at +0x300 ---
        "3:\n"
        "ldrb w8,[x19, #0x31c]\n"
        "cbz w8,4f\n"
        ".inst 0xB0018F28\n"            // adrp x8, 0x71052b7000
        "ldr x8,[x8, #0xf00]\n"
        "ldr x8,[x8]\n"
        "add x0,x8,#0xa30\n"
        "ldr x8,[x8, #0xa30]\n"
        "ldr x8,[x8, #0x18]\n"
        "add x1,x19,#0x300\n"
        "blr x8\n"
        "strb wzr,[x19, #0x31c]\n"
        // epilogue
        "4:\n"
        "ldp x29,x30,[sp, #0x10]\n"
        "ldr x19,[sp], #0x20\n"
        "ret\n"
    );
}
#endif

// 71020d2320 -- clamp 4 camera subject positions against bounds from x1 (Vector4f min/max pairs)
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

// 71020d22d0 -- load vec4 [x,y,z,w] from x1, build 4 pos pairs and store to 4 camera slots
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

// 71020d2460 -- bounds check slot [0..3], store ~enable&1 to slot+0x70
// orr w9,wzr,#0xe0 + smaddl for slot*0xe0 stride -- naked asm to match exactly
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void ItemCameraModuleImpl__set_camera_subject_enable_impl(BattleObjectModuleAccessor* a, u32 slot, u32 enable) {
    asm(
        "cmp w1,#0x3\n"
        "b.gt 1f\n"
        "cmp w1,#0x4\n"
        "b.cs 2f\n"
        "ldr x8,[x0, #0x60]\n"
        "orr w9,wzr,#0xe0\n"
        "smaddl x8,w1,w9,x8\n"
        "mvn w9,w2\n"
        "and w9,w9,#0x1\n"
        "str w9,[x8, #0x70]\n"
        "1:\n"
        "ret\n"
        "2:\n"
        "stp x29,x30,[sp, #-0x10]!\n"
        "add x29,sp,#0x0\n"
        ".inst 0x9463BF03\n"  // bl 0x71039c20a0 (from PC=0x71020d2494)
        ".inst 0x00000000\n"  // padding
        ".inst 0x00000000\n"  // padding
    );
}
#endif

// 71020d24a0 -- bounds check slot [0..3], SIMD zero-W vec store to slot+0x90
// orr w9,wzr,#0xe0 + smaddl -- naked asm to match exactly
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void ItemCameraModuleImpl__set_camera_subject_pos_impl(BattleObjectModuleAccessor* a, u32 slot, void* vec3) {
    asm(
        "cmp w1,#0x3\n"
        "b.gt 1f\n"
        "cmp w1,#0x4\n"
        "b.cs 2f\n"
        "ldr q0,[x2]\n"
        "fmov s1,wzr\n"
        "ldr x8,[x0, #0x60]\n"
        "ext v2.16B,v0.16B,v0.16B,#0x8\n"
        "mov v2.S[1],v1.S[0]\n"
        "mov v0.D[1],v2.D[0]\n"
        "orr w9,wzr,#0xe0\n"
        "smaddl x8,w1,w9,x8\n"
        "str q0,[x8, #0x90]\n"
        "1:\n"
        "ret\n"
        "2:\n"
        "stp x29,x30,[sp, #-0x10]!\n"
        "add x29,sp,#0x0\n"
        ".inst 0x9463BEF0\n"  // bl 0x71039c20a0 (from PC=0x71020d24e0)
        ".inst 0x00000000\n"  // padding
        ".inst 0x00000000\n"  // padding
        ".inst 0x00000000\n"  // padding
    );
}
#endif

// 71020d24f0 -- bounds check slot [0..3], load vec from slot+0x90;
//   if signed > 3 → return global zero vec (adrp); if unsigned >= 4 → panic
// orr w9,wzr,#0xe0 + smaddl; adrp for zero vec → partial match
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void ItemCameraModuleImpl__get_camera_subject_pos_impl(BattleObjectModuleAccessor* a, u32 slot) {
    asm(
        "cmp w1,#0x3\n"
        "b.gt 1f\n"
        "cmp w1,#0x4\n"
        "b.cs 2f\n"
        "ldr x8,[x0, #0x60]\n"
        "orr w9,wzr,#0xe0\n"
        "smaddl x8,w1,w9,x8\n"
        "ldr q0,[x8, #0x90]!\n"
        "ret\n"
        "1:\n"
        ".inst 0xB0018EA8\n"  // adrp x8, 0x71052a7000 (from PC=0x71020d2514)
        "ldr x8,[x8, #0xa88]\n"
        "ldr q0,[x8]\n"
        "ret\n"
        "2:\n"
        "stp x29,x30,[sp, #-0x10]!\n"
        "add x29,sp,#0x0\n"
        ".inst 0x9463BEDD\n"  // bl 0x71039c20a0 (from PC=0x71020d252c)
    );
}
#endif

// 71020d2530 -- bounds check slot [0..3], store 4 floats from vec4 to 12 fields in slot;
//   if unsigned >= 4 → panic. 240B total: 22 main insns + 3 abort + 3 pad + 32 second region.
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void ItemCameraModuleImpl__set_camera_subject_range_impl(BattleObjectModuleAccessor* a, u32 slot, void* vec4) {
    asm(
        // Main body (22 instructions, offsets 0x00-0x57)
        "cmp w1,#0x4\n"
        "b.cs 1f\n"
        "ldr q0,[x2]\n"
        "ldr x8,[x0, #0x60]\n"
        "orr w9,wzr,#0xe0\n"
        "smaddl x8,w1,w9,x8\n"
        "mov w10,v0.S[1]\n"
        "mov w9,v0.S[2]\n"
        "fmov w12,s0\n"
        "mov w11,v0.S[3]\n"
        "str w12,[x8, #0x10c]\n"
        "str w12,[x8, #0x12c]\n"
        "stp w12,w10,[x8, #0xfc]\n"
        "str w9,[x8, #0x104]\n"
        "str w11,[x8, #0x108]\n"
        "str w10,[x8, #0x110]\n"
        "str w9,[x8, #0x114]\n"
        "str w11,[x8, #0x118]\n"
        "str w10,[x8, #0x130]\n"
        "str w9,[x8, #0x134]\n"
        "str w11,[x8, #0x138]\n"
        "ret\n"
        // Abort path (3 instructions, offsets 0x58-0x63)
        "1:\n"
        "stp x29,x30,[sp, #-0x10]!\n"
        "add x29,sp,#0x0\n"
        ".inst 0x9463BEC4\n"  // bl 0x71039c20a0 (from PC=0x71020d2590)
        // Padding (3 words, offsets 0x64-0x6f)
        ".inst 0x00000000\n"
        ".inst 0x00000000\n"
        ".inst 0x00000000\n"
        // Second region (32 instructions, offsets 0x70-0xef)
        ".inst 0xF85F8008\n"
        ".inst 0xB4000488\n"
        ".inst 0xF9402508\n"
        ".inst 0xB4000448\n"
        ".inst 0xF940100A\n"
        ".inst 0xF940014A\n"
        ".inst 0xF9400809\n"
        ".inst 0x9100414B\n"
        ".inst 0xCB0B012A\n"
        ".inst 0xD344FD4C\n"
        ".inst 0x7100059F\n"
        ".inst 0x540002AB\n"
        ".inst 0xF0013C68\n"
        ".inst 0x91258108\n"
        ".inst 0xEB09017F\n"
        ".inst 0x9A883168\n"
        ".inst 0xB940090B\n"
        ".inst 0x12000D6B\n"
        ".inst 0x7100097F\n"
        ".inst 0x540000C0\n"
        ".inst 0x71001D7F\n"
        ".inst 0x540000C1\n"
        ".inst 0xF9400108\n"
        ".inst 0x9100A108\n"
        ".inst 0x14000004\n"
        ".inst 0xF9400108\n"
        ".inst 0x14000002\n"
        ".inst 0xAA1F03E8\n"
        ".inst 0xF9403108\n"
        ".inst 0xCB0A73EA\n"
        ".inst 0x8B8A7129\n"
        ".inst 0xF9000809\n"
    );
}
#endif

} // namespace app::lua_bind
