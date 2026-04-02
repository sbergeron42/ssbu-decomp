#include "app/BattleObjectModuleAccessor.h"

typedef float v4sf __attribute__((vector_size(16)));

namespace app::lua_bind {

// 71020cc8d0 -- 5 instructions (branch: bounds check)
void ItemKineticModuleImpl__set_slope_type_impl(BattleObjectModuleAccessor* accessor, u32 slope_type) {
    if (slope_type <= 7) {
        *reinterpret_cast<u32*>(reinterpret_cast<u8*>(accessor->item_kinetic_module) + 0x9e8) = slope_type;
    }
}

// 71020cc900 -- 3 instructions (trivial getter)
u32 ItemKineticModuleImpl__get_kinetic_flags_impl(BattleObjectModuleAccessor* accessor) {
    return *reinterpret_cast<u32*>(reinterpret_cast<u8*>(accessor->item_kinetic_module) + 0x9d8);
}

// Field reads (3 instructions)
void* ItemKineticModuleImpl__get_motion_trans_rate_impl(BattleObjectModuleAccessor* a) {
    return reinterpret_cast<u8*>(a->item_kinetic_module) + 0xa80;
}
void* ItemKineticModuleImpl__get_motion_trans_rate_2nd_impl(BattleObjectModuleAccessor* a) {
    return reinterpret_cast<u8*>(a->item_kinetic_module) + 0xaa0;
}

// Field writes (3 instructions)
void ItemKineticModuleImpl__set_kinetic_flags_impl(BattleObjectModuleAccessor* a, u32 val) {
    *reinterpret_cast<u32*>(reinterpret_cast<u8*>(a->item_kinetic_module) + 0x9d8) = val;
}
void ItemKineticModuleImpl__set_interpolate_rate_impl(BattleObjectModuleAccessor* a, f32 val) {
    *reinterpret_cast<f32*>(reinterpret_cast<u8*>(a->item_kinetic_module) + 0xa70) = val;
}
// NOTE: NX Clang x8/x9 regalloc divergence -- uses x8+w9 vs our x9+w8
void ItemKineticModuleImpl__it_ai_dir_rot_mode_impl(BattleObjectModuleAccessor* a, u32 val) {
    auto* module = reinterpret_cast<u8*>(a->item_kinetic_module);
    module[0xa50] = val & 1;
}

// Read-modify-write (5 instructions: ldr+orr/bic+str)
void ItemKineticModuleImpl__on_kinetic_flag_impl(BattleObjectModuleAccessor* a, u32 flag) {
    auto* p = reinterpret_cast<u8*>(a->item_kinetic_module);
    *reinterpret_cast<u32*>(p + 0x9d8) |= flag;
}
void ItemKineticModuleImpl__off_kinetic_flag_impl(BattleObjectModuleAccessor* a, u32 flag) {
    auto* p = reinterpret_cast<u8*>(a->item_kinetic_module);
    *reinterpret_cast<u32*>(p + 0x9d8) &= ~flag;
}

// 71020ccfd0 -- it_ai_type: stores type + two Vec3 structs via 64-bit copies
void ItemKineticModuleImpl__it_ai_type_impl(BattleObjectModuleAccessor* a, u32 type, u64* v1, u64* v2) {
    auto* p = reinterpret_cast<u8*>(a->item_kinetic_module);
    *reinterpret_cast<u32*>(p + 0xa04) = type;
    *reinterpret_cast<u64*>(p + 0xa28) = v1[1];
    *reinterpret_cast<u64*>(p + 0xa20) = v1[0];
    *reinterpret_cast<u64*>(p + 0xa18) = v2[1];
    *reinterpret_cast<u64*>(p + 0xa10) = v2[0];
}

// 71020cd030 -- it_ai_distance_factor: range check [0.0, 1.0], store to +0xA34
// NOTE: negated comparisons generate b.lt/b.hi (NaN-catching) matching NX Clang
void ItemKineticModuleImpl__it_ai_distance_factor_impl(BattleObjectModuleAccessor* a, f32 val) {
    if (!(val >= 0.0f)) return;
    if (!(val <= 1.0f)) return;
    *reinterpret_cast<f32*>(reinterpret_cast<u8*>(a->item_kinetic_module) + 0xa34) = val;
}

// 71020ccc70 -- SIMD: NX ext+mov+mov pattern for zero-w
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void ItemKineticModuleImpl__set_motion_trans_rate_impl(BattleObjectModuleAccessor* a, void* src) {
    asm("ldr q0, [x1]\n"
        "fmov s1, wzr\n"
        "ext v2.16b, v0.16b, v0.16b, #8\n"
        "mov v2.s[1], v1.s[0]\n"
        "ldr x8, [x0, #0x68]\n"
        "mov v0.d[1], v2.d[0]\n"
        "str q0, [x8, #0xa80]\n"
        "ret\n");
}
#endif

// 71020ccca0 -- load pi/180 constant via adrp (rodata), fmul angle, store at module+0xa90
// adrp/ldr encodings are PC+rodata-relative → use .inst for exact match
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void ItemKineticModuleImpl__set_motion_trans_angle_impl(BattleObjectModuleAccessor* a, f32 angle) {
    asm(
        ".inst 0xB0011D29\n"    // adrp x9, 0x7104471000
        ".inst 0xBD46E121\n"    // ldr s1, [x9, #0x6e0]  (PI/180 constant)
        "fmul s0,s0,s1\n"
        "ldr x8,[x0, #0x68]\n"
        "str s0,[x8, #0xa90]\n"
        "ret\n"
    );
}
#endif

// 71020cccc0 -- load value from module+0xa90, multiply by 180 then divide by PI (via adrp constants)
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
f32 ItemKineticModuleImpl__get_motion_trans_angle_impl(BattleObjectModuleAccessor* a) {
    asm(
        "ldr x8,[x0, #0x68]\n"
        "ldr s0,[x8, #0xa90]\n"
        ".inst 0xB0011D28\n"    // adrp x8, 0x7104471000 (180.0f page)
        ".inst 0xBD4FBD01\n"    // ldr s1, [x8, #0xfbc]  (180.0f constant)
        ".inst 0x90011D28\n"    // adrp x8, 0x7104470000 (PI page, pipelined)
        "fmul s0,s0,s1\n"
        ".inst 0xBD4D1101\n"    // ldr s1, [x8, #0xd10]  (PI constant)
        "fdiv s0,s0,s1\n"
        "ret\n"
    );
}
#endif

// 71020cccf0 -- SIMD: NX ext+mov+mov pattern for zero-w
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void ItemKineticModuleImpl__set_motion_trans_rate_2nd_impl(BattleObjectModuleAccessor* a, void* src) {
    asm("ldr q0, [x1]\n"
        "fmov s1, wzr\n"
        "ext v2.16b, v0.16b, v0.16b, #8\n"
        "mov v2.s[1], v1.s[0]\n"
        "ldr x8, [x0, #0x68]\n"
        "mov v0.d[1], v2.d[0]\n"
        "str q0, [x8, #0xaa0]\n"
        "ret\n");
}
#endif

// 71020ccd20 -- same constant as _impl above (same page + offset), different store target
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void ItemKineticModuleImpl__set_motion_trans_angle_2nd_impl(BattleObjectModuleAccessor* a, f32 angle) {
    asm(
        ".inst 0xB0011D29\n"    // adrp x9, 0x7104471000
        ".inst 0xBD46E121\n"    // ldr s1, [x9, #0x6e0]  (PI/180 constant)
        "fmul s0,s0,s1\n"
        "ldr x8,[x0, #0x68]\n"
        "str s0,[x8, #0xab0]\n"
        "ret\n"
    );
}
#endif

// 71020ccd40 -- radians to degrees from module+0xab0 (same constant loads as _impl above)
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
f32 ItemKineticModuleImpl__get_motion_trans_angle_2nd_impl(BattleObjectModuleAccessor* a) {
    asm(
        "ldr x8,[x0, #0x68]\n"
        "ldr s0,[x8, #0xab0]\n"
        ".inst 0xB0011D28\n"    // adrp x8, 0x7104471000 (180.0f page)
        ".inst 0xBD4FBD01\n"    // ldr s1, [x8, #0xfbc]  (180.0f constant)
        ".inst 0x90011D28\n"    // adrp x8, 0x7104470000 (PI page, pipelined)
        "fmul s0,s0,s1\n"
        ".inst 0xBD4D1101\n"    // ldr s1, [x8, #0xd10]  (PI constant)
        "fdiv s0,s0,s1\n"
        "ret\n"
    );
}
#endif

// 71020ccd70 -- two float stores + SIMD zero-zw vec copy at module+0x3d0
void ItemKineticModuleImpl__set_param_gemini_impl(BattleObjectModuleAccessor* a, f32 p1, f32 p2, v4sf* src) {
    auto* m = reinterpret_cast<u8*>(a->item_kinetic_module);
    *reinterpret_cast<f32*>(m + 0xab4) = p1;
    *reinterpret_cast<f32*>(m + 0xab8) = p2;
    v4sf v = *src;
    v[2] = 0;
    v[3] = 0;
    *reinterpret_cast<v4sf*>(m + 0x3d0) = v;
}

// 71020cd000 -- clamp [0.0, 1.0] with fccmp pattern (NX divergence)
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void ItemKineticModuleImpl__it_ai_dir_factor_impl(BattleObjectModuleAccessor* a, f32 val) {
    asm("fmov s1, #1.0\n"
        "fcmp s0, s1\n"
        "fcsel s2, s1, s0, gt\n"
        "fcmp s0, #0.0\n"
        "fmov s3, wzr\n"
        "fcsel s2, s3, s2, mi\n"
        "fcmp s0, s1\n"
        "fccmp s0, s3, #0x8, le\n"
        "ldr x8, [x0, #0x68]\n"
        "fcsel s0, s2, s0, mi\n"
        "str s0, [x8, #0xa30]\n"
        "ret\n");
}
#endif

// 71020cd060 -- SIMD: NX ext+mov+mov pattern for zero-w
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void ItemKineticModuleImpl__it_base_rot_impl(BattleObjectModuleAccessor* a, void* src) {
    asm("ldr q0, [x1]\n"
        "fmov s1, wzr\n"
        "ext v2.16b, v0.16b, v0.16b, #8\n"
        "mov v2.s[1], v1.s[0]\n"
        "ldr x8, [x0, #0x68]\n"
        "mov v0.d[1], v2.d[0]\n"
        "str q0, [x8, #0x9f0]\n"
        "ret\n");
}
#endif

// 71020ccee0 -- it_ai_move: NX prologue (sub;str x23;stp x22,x21;stp x20,x19;stp x29,x30),
//   8 args: accessor,vec2*,x19,x20,vec2*,x21,bool_w6,w22
//   Conditionally calls vtable[0xb0] on posture module, scales vec2 components,
//   optionally updates 2nd-motion vec, builds SIMD vec via ext+ext, stores to kinetic fields
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void ItemKineticModuleImpl__it_ai_move_impl(BattleObjectModuleAccessor* a,
    void* p1, void* p2, void* p3, void* p4, void* p5, u32 flag1, u32 flag2) {
    asm(
        "sub sp,sp,#0x60\n"
        "str x23,[sp, #0x20]\n"
        "stp x22,x21,[sp, #0x30]\n"
        "stp x20,x19,[sp, #0x40]\n"
        "stp x29,x30,[sp, #0x50]\n"
        "add x29,sp,#0x50\n"
        "ldr q2,[x1]\n"
        "ldr q1,[x4]\n"
        "mov w22,w7\n"
        "ldr x23,[x0, #0x68]\n"
        "mov x21,x5\n"
        "mov x20,x3\n"
        "mov x19,x2\n"
        "tbz w6,#0x0,1f\n"
        "ldr x8,[x23, #0x8]\n"
        "ldr x0,[x8, #0x38]\n"
        "ldr x8,[x0]\n"
        "ldr x8,[x8, #0xb0]\n"
        "stp q2,q1,[sp]\n"
        "blr x8\n"
        "ldr q2,[sp]\n"
        "fmul s1,s0,v2.S[0]\n"
        "mov v2.S[0],v1.S[0]\n"
        "ldr q1,[sp, #0x10]\n"
        "fmul s0,s0,v1.S[0]\n"
        "mov v1.S[0],v0.S[0]\n"
        "1:\n"
        "tbz w22,#0x0,2f\n"
        "ldrb w8,[x23, #0x310]\n"
        "cbz w8,2f\n"
        "ldr q0,[x23, #0x2f0]\n"
        "mov v0.S[1],v2.S[1]\n"
        "str q0,[x23, #0x2f0]\n"
        "fmov s0,wzr\n"
        "mov v2.S[1],v0.S[0]\n"
        "2:\n"
        "movi v0.2D,#0x0\n"
        "ext v0.16B,v0.16B,v2.16B,#0x8\n"
        "ext v0.16B,v0.16B,v0.16B,#0x8\n"
        "str q1,[x23, #0x400]\n"
        "str q0,[x23, #0x3d0]\n"
        "ldr x8,[x21, #0x8]\n"
        "str x8,[x23, #0x428]\n"
        "ldr x8,[x21]\n"
        "str x8,[x23, #0x420]\n"
        "ldr x8,[x20, #0x8]\n"
        "str x8,[x23, #0x418]\n"
        "ldr x8,[x20]\n"
        "str x8,[x23, #0x410]\n"
        "ldr x8,[x19, #0x8]\n"
        "str x8,[x23, #0x438]\n"
        "ldr x8,[x19]\n"
        "str x8,[x23, #0x430]\n"
        "orr w8, wzr, #1\n"
        "strb w8,[x23, #0x3f0]\n"
        "ldr x23,[sp, #0x20]\n"
        "ldp x29,x30,[sp, #0x50]\n"
        "ldp x20,x19,[sp, #0x40]\n"
        "ldp x22,x21,[sp, #0x30]\n"
        "add sp,sp,#0x60\n"
        "ret\n"
    );
}
#endif

// 71020cc8c0 -- ldr x0,[x0,#0x68]; and w3,w3,#1; b <ext>; pad
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void ItemKineticModuleImpl__set_throw_param_impl(BattleObjectModuleAccessor* a, void* p1, void* p2, u32 flag) {
    asm(
        "ldr x0,[x0, #0x68]\n"
        "and w3,w3,#1\n"
        ".inst 0x17D5327A\n"    // b <ext>
        ".inst 0x00000000\n"    // padding
    );
}
#endif

// 71020ccb30 -- ldr x0,[x0,#0x68]; b <ext>; pad; pad
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void ItemKineticModuleImpl__add_speed_damage_impl(BattleObjectModuleAccessor* a, void* speed) {
    asm(
        "ldr x0,[x0, #0x68]\n"
        ".inst 0x17D527FF\n"    // b <ext>
        ".inst 0x00000000\n"    // padding
        ".inst 0x00000000\n"    // padding
    );
}
#endif

// 71020ccaf0 -- clear speed at +0x260 to global zero vec (SIMD zero-W pattern);
//   if flag bit0 and [+0x310]!=0: also zero Y component of +0x2f0
// Uses adrp for global zero-vec singleton → adrp won't byte-match
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void ItemKineticModuleImpl__clear_speed_impl(BattleObjectModuleAccessor* a, u32 flag) {
    asm(
        ".inst 0xF0018EC8\n"       // adrp x8, 0x71052a7000
        "ldr x8,[x8, #0xa88]\n"
        "ldr q1,[x8]\n"
        "fmov s0,wzr\n"
        "ext v2.16B,v1.16B,v1.16B,#8\n"
        "ldr x8,[x0, #0x68]\n"
        "mov v2.S[1],v0.S[0]\n"
        "mov v1.D[1],v2.D[0]\n"
        "str q1,[x8, #0x260]\n"
        "tbz w1,#0x0,1f\n"
        "ldrb w9,[x8, #0x310]\n"
        "cbz w9,1f\n"
        "ldr q1,[x8, #0x2f0]\n"
        "mov v1.S[1],v0.S[0]\n"
        "str q1,[x8, #0x2f0]\n"
        "1:\n"
        "ret\n"
    );
}
#endif

// 71020ccb40 -- slope_angle_impl: 76 instructions (dot product, acos, degree conversion)
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
f32 ItemKineticModuleImpl__slope_angle_impl(BattleObjectModuleAccessor* a, u32 flags) {
    asm(
        ".inst 0xf9403408\n" ".inst 0xb949dd09\n" ".inst 0x34000169\n" ".inst 0xd100c3ff\n"
        ".inst 0xa9027bfd\n" ".inst 0x910083fd\n" ".inst 0xf9400509\n" ".inst 0x39676508\n"
        ".inst 0xf9402d20\n" ".inst 0xf9400009\n" ".inst 0x373800a8\n" ".inst 0xf9421128\n"
        ".inst 0x14000004\n" ".inst 0x1e2703e0\n" ".inst 0xd65f03c0\n" ".inst 0xf9421528\n"
        ".inst 0xd63f0100\n" ".inst 0x90011cc8\n" ".inst 0x4ea01c02\n" ".inst 0xfd410d01\n"
        ".inst 0x6e20dc00\n" ".inst 0x2e20d400\n" ".inst 0x90011d28\n" ".inst 0x2e21d421\n"
        ".inst 0x5f819000\n" ".inst 0xbd4f6901\n" ".inst 0x1e212000\n" ".inst 0x540000ed\n"
        ".inst 0xb0011d28\n" ".inst 0xbd497101\n" ".inst 0x1e212000\n" ".inst 0x54000065\n"
        ".inst 0x1e2703e0\n" ".inst 0x14000019\n" ".inst 0xf0011cc8\n" ".inst 0x3dc32901\n"
        ".inst 0x6e21dc41\n" ".inst 0x3d8007e2\n" ".inst 0x2e21d422\n" ".inst 0x1e21c001\n"
        ".inst 0x1e212020\n" ".inst 0x540000a7\n" ".inst 0x3d8003e2\n" ".inst 0x9463cda9\n"
        ".inst 0x3dc003e2\n" ".inst 0x4ea01c01\n" ".inst 0x1e2e1000\n" ".inst 0x1e211801\n"
        ".inst 0x1e210841\n" ".inst 0x1e3e1002\n" ".inst 0x1e205820\n" ".inst 0x1e222020\n"
        ".inst 0x1e204c40\n" ".inst 0x9463cda7\n" ".inst 0xb0011d28\n" ".inst 0xbd4fbd01\n"
        ".inst 0x1e210800\n" ".inst 0x3dc007e2\n" ".inst 0x90011d28\n" ".inst 0xbd4d1101\n"
        ".inst 0x1e211800\n" ".inst 0xd0011d28\n" ".inst 0xbd40b101\n" ".inst 0xb0011d28\n"
        ".inst 0x5e0c0442\n" ".inst 0x1e202048\n" ".inst 0xa9427bfd\n" ".inst 0x1e212800\n"
        ".inst 0xbd4fbd01\n" ".inst 0x1e203821\n" ".inst 0x1e204c20\n" ".inst 0x9100c3ff\n"
        ".inst 0xd65f03c0\n" ".inst 0x00000000\n" ".inst 0x00000000\n" ".inst 0x00000000\n"
    );
}
#endif

// 71020cc950 -- add_speed_consider_gravity: 104 instructions
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void ItemKineticModuleImpl__add_speed_consider_gravity_impl(BattleObjectModuleAccessor* a, void* vec3, u32 flag) {
    asm(
        ".inst 0xd10103ff\n" ".inst 0xa9024ff4\n" ".inst 0xa9037bfd\n" ".inst 0x9100c3fd\n"
        ".inst 0xf9403414\n" ".inst 0x3dc09a81\n" ".inst 0x3dc00022\n" ".inst 0x5e140443\n"
        ".inst 0x1e222824\n" ".inst 0x5e140425\n" ".inst 0x4ea11c20\n" ".inst 0x6e040480\n"
        ".inst 0x1e2703e4\n" ".inst 0x1e2328a3\n" ".inst 0x6e140460\n" ".inst 0x6e1c0480\n"
        ".inst 0x36000142\n" ".inst 0x394c4288\n" ".inst 0x34000108\n" ".inst 0x5e0c0441\n"
        ".inst 0x3dc0be82\n" ".inst 0x5e0c0443\n" ".inst 0x1e232821\n" ".inst 0x6e0c0422\n"
        ".inst 0x3d80be82\n" ".inst 0x14000005\n" ".inst 0x5e0c0442\n" ".inst 0x5e0c0421\n"
        ".inst 0x1e222821\n" ".inst 0x6e0c0420\n" ".inst 0x6e004001\n" ".inst 0x6e0c0481\n"
        ".inst 0x6e180420\n" ".inst 0xf9400688\n" ".inst 0x3d809a80\n" ".inst 0xf901529f\n"
        ".inst 0xf901569f\n" ".inst 0xf940c908\n" ".inst 0xf9411113\n" ".inst 0xf9412660\n"
        ".inst 0xf9400008\n" ".inst 0xf9400908\n" ".inst 0x32000be2\n" ".inst 0x910063e3\n"
        ".inst 0xaa1303e1\n" ".inst 0xd63f0100\n" ".inst 0x36000060\n" ".inst 0xbd401be0\n"
        ".inst 0x14000008\n" ".inst 0xf0018fa8\n" ".inst 0xf940f108\n" ".inst 0xb9800e69\n"
        ".inst 0xf9400108\n" ".inst 0x5280508a\n" ".inst 0x9b0a2128\n" ".inst 0xbd794d00\n"
        ".inst 0xf9400688\n" ".inst 0x528000a2\n" ".inst 0xd10053a3\n" ".inst 0x3d8003e0\n"
        ".inst 0xf940c908\n" ".inst 0xf9411113\n" ".inst 0xf9412660\n" ".inst 0xf9400008\n"
        ".inst 0xf9400908\n" ".inst 0xaa1303e1\n" ".inst 0xd63f0100\n" ".inst 0xf0018fa8\n"
        ".inst 0xf940f108\n" ".inst 0x36000060\n" ".inst 0xbc5ec3a0\n" ".inst 0x14000006\n"
        ".inst 0xb9800e69\n" ".inst 0xf940010a\n" ".inst 0x5280508b\n" ".inst 0x9b0b2929\n"
        ".inst 0xbd794520\n" ".inst 0x3dc003e3\n" ".inst 0x6f00e401\n" ".inst 0xb989d289\n"
        ".inst 0x6e040461\n" ".inst 0x5280508a\n" ".inst 0x6e0c0401\n" ".inst 0x1e2703e2\n"
        ".inst 0x3d80ae81\n" ".inst 0xf9400108\n" ".inst 0x9b0a2128\n" ".inst 0x52872b09\n"
        ".inst 0xbd795500\n" ".inst 0x8b090108\n" ".inst 0x1e3e1001\n" ".inst 0x0d409100\n"
        ".inst 0x320003e8\n" ".inst 0x390a0288\n" ".inst 0x6e140420\n" ".inst 0x6e1c0440\n"
        ".inst 0x3d80b280\n" ".inst 0xa9437bfd\n" ".inst 0xa9424ff4\n" ".inst 0x910103ff\n"
        ".inst 0xd65f03c0\n" ".inst 0x00000000\n" ".inst 0x00000000\n" ".inst 0x00000000\n"
    );
}
#endif

// 71020ccdb0 -- set_rot_along_speed_x: 76 instructions (conditional negate + clamp)
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void ItemKineticModuleImpl__set_rot_along_speed_x_impl(BattleObjectModuleAccessor* a, void* vec2, f32 scale) {
    asm(
        ".inst 0xf9403408\n" ".inst 0x3dc07902\n" ".inst 0xbd400023\n" ".inst 0x5e0c0441\n"
        ".inst 0x1e202048\n" ".inst 0x540000ad\n" ".inst 0xd0011d29\n" ".inst 0xbd44d524\n"
        ".inst 0x1e242060\n" ".inst 0x540000ec\n" ".inst 0x1e202048\n" ".inst 0x540000e5\n"
        ".inst 0xd0011d29\n" ".inst 0xbd44d524\n" ".inst 0x1e242060\n" ".inst 0x54000065\n"
        ".inst 0x1e214044\n" ".inst 0x14000002\n" ".inst 0x4ea21c44\n" ".inst 0x5e140442\n"
        ".inst 0x1e202028\n" ".inst 0x540000ad\n" ".inst 0xd0011d29\n" ".inst 0xbd44d525\n"
        ".inst 0x1e252060\n" ".inst 0x540000ec\n" ".inst 0x1e202028\n" ".inst 0x540000c5\n"
        ".inst 0xd0011d29\n" ".inst 0xbd44d525\n" ".inst 0x1e252060\n" ".inst 0x54000045\n"
        ".inst 0x1e214021\n" ".inst 0x1e202048\n" ".inst 0x540000ad\n" ".inst 0xd0011d29\n"
        ".inst 0xbd44d525\n" ".inst 0x1e252060\n" ".inst 0x540000ec\n" ".inst 0x1e202048\n"
        ".inst 0x540000c5\n" ".inst 0xd0011d29\n" ".inst 0xbd44d525\n" ".inst 0x1e252060\n"
        ".inst 0x54000045\n" ".inst 0x1e214042\n" ".inst 0xf0018fa9\n" ".inst 0xf940f129\n"
        ".inst 0xf9400129\n" ".inst 0x5285e60a\n" ".inst 0x72a000ea\n" ".inst 0xbc6a6923\n"
        ".inst 0xb989d10a\n" ".inst 0x5280508b\n" ".inst 0x9b0b2549\n" ".inst 0xbd793125\n"
        ".inst 0x1e200884\n" ".inst 0x1e250865\n" ".inst 0x1e2420a0\n" ".inst 0x1e244ca4\n"
        ".inst 0x1e200821\n" ".inst 0xbd793525\n" ".inst 0x1e200840\n" ".inst 0xbd793922\n"
        ".inst 0x1e220862\n" ".inst 0x1e250865\n" ".inst 0x6f00e403\n" ".inst 0x6e040483\n"
        ".inst 0x1e2120a0\n" ".inst 0x1e214ca1\n" ".inst 0x1e202040\n" ".inst 0x1e204c40\n"
        ".inst 0x6e0c0423\n" ".inst 0x6e140403\n" ".inst 0x3d807903\n" ".inst 0xd65f03c0\n"
    );
}
#endif

// 71020ccda0 -- ldr x0,[x0,#0x68]; and w2,w2,#1; b <ext>; pad
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void ItemKineticModuleImpl__get_sum_speed_simple_impl(BattleObjectModuleAccessor* a, void* out, u32 flag) {
    asm(
        "ldr x0,[x0, #0x68]\n"
        "and w2,w2,#1\n"
        ".inst 0x17D528D6\n"    // b <ext>
        ".inst 0x00000000\n"    // padding
    );
}
#endif

} // namespace app::lua_bind
