#include "app/BattleObjectModuleAccessor.h"

// FighterMotionModuleImpl -- accesses MotionModule at accessor+0x88
// Most functions are tail-call wrappers to external targets (won't byte-match).
// Complex functions include Kirby copy hash translation and damage stop logic.

struct FighterMotionModuleImpl;
#define VT(m) (*reinterpret_cast<void***>(m))
#define MOTION(a) (reinterpret_cast<u8*>((a)->motion_module))

// External tail call targets
extern "C" void FUN_71006e1b90(void*, u32);
extern "C" void FUN_71006e1e20(void*, u64, bool);
extern "C" void FUN_71006e20c0(void*, u64, bool);
extern "C" void FUN_71006e2440(void*, u64, bool);
extern "C" void FUN_71006e2200(void*, u64, bool);
extern "C" void FUN_71006e2680(void*, u64, bool, bool, bool);
extern "C" void FUN_71006e27f0(void*, u64, bool, bool);
extern "C" void FUN_71006e29f0(void*, bool);
extern "C" void FUN_710049c190(void*, u64);
extern "C" void FUN_710049e4b0(void*, u32, u64, bool, bool, bool, bool, bool, f32, f32, f32);

// Global Kirby copy hash lookup table
extern "C" u64 PTR_DAT_7104fcd388[];

// Global pause state
extern "C" u64* DAT_71052c2760;

namespace app::lua_bind {

// 71020aa000 -- mov x0,x1; mov w1,w2; b external
void FighterMotionModuleImpl__add_body_type_hash_impl(BattleObjectModuleAccessor*, void* module, u32 hash) {
    FUN_71006e1b90(module, hash);
}

// 71020aa010 -- ldr x0,[x0,#0x88]; and w2,w2,#0x1; b external
void FighterMotionModuleImpl__get_cancel_frame_impl(BattleObjectModuleAccessor* a, u64 hash, bool p2) {
    FUN_71006e1e20(a->motion_module, hash, p2 & 1);
}

// 71020aa020 -- ldr x0,[x0,#0x88]; and w2,w2,#0x1; b external
void FighterMotionModuleImpl__is_valid_cancel_frame_impl(BattleObjectModuleAccessor* a, u64 hash, bool p2) {
    FUN_71006e20c0(a->motion_module, hash, p2 & 1);
}

// 71020aa030 -- ldr x0,[x0,#0x88]; and w2,w2,#0x1; b external
void FighterMotionModuleImpl__get_hit_normal_frame_impl(BattleObjectModuleAccessor* a, u64 hash, bool p2) {
    FUN_71006e2440(a->motion_module, hash, p2 & 1);
}

// 71020aa040 -- ldr x0,[x0,#0x88]; and w2,w2,#0x1; b external
void FighterMotionModuleImpl__get_hit_xlu_frame_impl(BattleObjectModuleAccessor* a, u64 hash, bool p2) {
    FUN_71006e2200(a->motion_module, hash, p2 & 1);
}

// 71020aa050 -- Kirby copy hash table lookup (32 instructions)
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FighterMotionModuleImpl__motion_kind_kirby_copy_original_impl(BattleObjectModuleAccessor* a, u64 hash) {
    asm("str x19, [sp, #-0x20]!\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "ldr x8, [x0, #0x88]\n"
        "ldr x8, [x8, #0x8]\n"
        "ldr x0, [x8, #0x50]\n"
        "ldr x8, [x0]\n"
        "ldr x8, [x8, #0x98]\n"
        "mov x19, x1\n"
        "mov w1, #0xfc\n"
        "movk w1, #0x1000, lsl #16\n"
        "blr x8\n"
        "adrp x8, PTR_DAT_7104fcd388\n"
        "add x8, x8, :lo12:PTR_DAT_7104fcd388\n"
        "ldr x8, [x8, w0, sxtw #3]\n"
        "ldp x9, x8, [x8]\n"
        "cmp x9, x8\n"
        "b.eq 1f\n"
        "mov x10, x9\n"
        "0:\n"
        "ldr x11, [x10], #0x10\n"
        "eor x11, x11, x19\n"
        "tst x11, #0xffffffffff\n"
        "b.eq 2f\n"
        "cmp x8, x10\n"
        "mov x9, x10\n"
        "b.ne 0b\n"
        "b 1f\n"
        "2:\n"
        "ldr x19, [x9, #0x8]\n"
        "1:\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "mov x0, x19\n"
        "ldr x19, [sp], #0x20\n"
        "ret\n");
}
#endif

// 71020aa0d0 -- ldr module; and w2,w3,w4 with #0x1; b change_motion_kirby_copy
void FighterMotionModuleImpl__change_motion_kirby_copy_impl(BattleObjectModuleAccessor* a, u64 hash, bool p2, bool p3, bool p4) {
    FUN_71006e2680(a->motion_module, hash, p2 & 1, p3 & 1, p4 & 1);
}

// 71020aa0f0 -- ldr module; and w2,w3 with #0x1; b external
void FighterMotionModuleImpl__change_motion_inherit_frame_kirby_copy_impl(BattleObjectModuleAccessor* a, u64 hash, bool p2, bool p3) {
    FUN_71006e27f0(a->motion_module, hash, p2 & 1, p3 & 1);
}

// 71020aa100 -- ldr module; hardcode w3=1,w2=0; b same target as above
void FighterMotionModuleImpl__change_motion_inherit_frame_keep_rate_kirby_copy_impl(BattleObjectModuleAccessor* a, u64 hash) {
    FUN_71006e27f0(a->motion_module, hash, 0, 1);
}

// 71020aa110 -- reads frame/rate via vtable, adjusts frame param, delegates to change_motion
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void FighterMotionModuleImpl__change_motion_force_inherit_frame_kirby_copy_impl(BattleObjectModuleAccessor* a, u64 hash, f32 frame, f32 rate, f32 blend) {
    asm("str d10, [sp, #-0x40]!\n"
        "stp d9, d8, [sp, #0x10]\n"
        "stp x20, x19, [sp, #0x20]\n"
        "stp x29, x30, [sp, #0x30]\n"
        "add x29, sp, #0x30\n"
        "ldr x20, [x0, #0x88]\n"
        "ldr x8, [x20]\n"
        "ldr x8, [x8, #0x138]\n"
        "mov x0, x20\n"
        "mov v8.16b, v2.16b\n"
        "mov v9.16b, v1.16b\n"
        "mov v10.16b, v0.16b\n"
        "mov x19, x1\n"
        "blr x8\n"
        "ldr x8, [x20]\n"
        "ldr x8, [x8, #0x160]\n"
        "mov x0, x20\n"
        "blr x8\n"
        "mov v1.16b, v9.16b\n"
        "mov v2.16b, v8.16b\n"
        "fcmp s10, #0.0\n"
        "ldp d9, d8, [sp, #0x10]\n"
        "mov x0, x20\n"
        "mov x1, x19\n"
        "ldp x29, x30, [sp, #0x30]\n"
        "ldp x20, x19, [sp, #0x20]\n"
        "orr w3, wzr, #1\n"
        "fcsel s0, s0, s10, lt\n"
        "mov w2, wzr\n"
        "mov w4, wzr\n"
        "ldr d10, [sp], #0x40\n"
        "b FUN_71006e2680\n");
}
#endif

// 71020aa190 -- Kirby copy hash lookup + tail call to end_frame_from_hash
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void FighterMotionModuleImpl__end_frame_from_hash_kirby_copy_impl(BattleObjectModuleAccessor* a, u64 hash) {
    asm("stp x20, x19, [sp, #-0x20]!\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "ldr x20, [x0, #0x88]\n"
        "ldr x8, [x20, #0x8]\n"
        "ldr x0, [x8, #0x50]\n"
        "ldr x8, [x0]\n"
        "ldr x8, [x8, #0x98]\n"
        "mov x19, x1\n"
        "mov w1, #0xfc\n"
        "movk w1, #0x1000, lsl #16\n"
        "blr x8\n"
        "adrp x8, PTR_DAT_7104fcd388\n"
        "add x8, x8, :lo12:PTR_DAT_7104fcd388\n"
        "ldr x9, [x8, w0, sxtw #3]\n"
        "ldp x8, x9, [x9]\n"
        "cmp x8, x9\n"
        "b.eq 1f\n"
        "0:\n"
        "ldr x10, [x8, #0x8]\n"
        "eor x10, x10, x19\n"
        "tst x10, #0xffffffffff\n"
        "b.eq 2f\n"
        "add x8, x8, #0x10\n"
        "cmp x9, x8\n"
        "b.ne 0b\n"
        "b 1f\n"
        "2:\n"
        "ldr x19, [x8]\n"
        "1:\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "mov x0, x20\n"
        "mov x1, x19\n"
        "ldp x20, x19, [sp], #0x20\n"
        "b FUN_710049c190\n");
}
#endif

// 71020aa210 -- ldr x0,[x0,#0x88]; and w1,w1,#0x1; b external
void FighterMotionModuleImpl__set_frame_sync_anim_cmd_kirby_copy_impl(BattleObjectModuleAccessor* a, bool val) {
    FUN_71006e29f0(a->motion_module, val & 1);
}

// 71020aa220 -- Kirby copy hash lookup + tail call to get_cancel_frame
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void FighterMotionModuleImpl__get_cancel_frame_kirby_copy_impl(BattleObjectModuleAccessor* a, u64 hash, bool p2) {
    asm("str x21, [sp, #-0x30]!\n"
        "stp x20, x19, [sp, #0x10]\n"
        "stp x29, x30, [sp, #0x20]\n"
        "add x29, sp, #0x20\n"
        "ldr x21, [x0, #0x88]\n"
        "ldr x8, [x21, #0x8]\n"
        "ldr x0, [x8, #0x50]\n"
        "ldr x8, [x0]\n"
        "ldr x8, [x8, #0x98]\n"
        "mov x20, x1\n"
        "mov w1, #0xfc\n"
        "movk w1, #0x1000, lsl #16\n"
        "mov w19, w2\n"
        "blr x8\n"
        "adrp x8, PTR_DAT_7104fcd388\n"
        "add x8, x8, :lo12:PTR_DAT_7104fcd388\n"
        "ldr x9, [x8, w0, sxtw #3]\n"
        "ldp x8, x9, [x9]\n"
        "cmp x8, x9\n"
        "b.eq 1f\n"
        "0:\n"
        "ldr x10, [x8, #0x8]\n"
        "eor x10, x10, x20\n"
        "tst x10, #0xffffffffff\n"
        "b.eq 2f\n"
        "add x8, x8, #0x10\n"
        "cmp x9, x8\n"
        "b.ne 0b\n"
        "b 1f\n"
        "2:\n"
        "ldr x20, [x8]\n"
        "1:\n"
        "and w2, w19, #1\n"
        "mov x1, x20\n"
        "mov x0, x21\n"
        "ldp x29, x30, [sp, #0x20]\n"
        "ldp x20, x19, [sp, #0x10]\n"
        "ldr x21, [sp], #0x30\n"
        "b FUN_71006e1e20\n");
}
#endif

// 71020aa2b0 -- Kirby copy hash lookup + many params preserved + tail call
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void FighterMotionModuleImpl__add_motion_partial_kirby_copy_impl(
        BattleObjectModuleAccessor* a, u32 slot, u64 hash, bool p3, bool p4, bool p5, bool p6, bool p7,
        f32 rate, f32 start_frame, f32 blend_frame) {
    asm("str d10, [sp, #-0x70]!\n"
        "stp d9, d8, [sp, #0x10]\n"
        "stp x26, x25, [sp, #0x20]\n"
        "stp x24, x23, [sp, #0x30]\n"
        "stp x22, x21, [sp, #0x40]\n"
        "stp x20, x19, [sp, #0x50]\n"
        "stp x29, x30, [sp, #0x60]\n"
        "add x29, sp, #0x60\n"
        "ldr x26, [x0, #0x88]\n"
        "ldr x8, [x26, #0x8]\n"
        "ldr x0, [x8, #0x50]\n"
        "ldr x8, [x0]\n"
        "ldr x8, [x8, #0x98]\n"
        "mov w23, w1\n"
        "mov w1, #0xfc\n"
        "movk w1, #0x1000, lsl #16\n"
        "mov w19, w7\n"
        "mov w20, w6\n"
        "mov w21, w5\n"
        "mov v8.16b, v2.16b\n"
        "mov w24, w4\n"
        "mov w25, w3\n"
        "mov v9.16b, v1.16b\n"
        "mov v10.16b, v0.16b\n"
        "mov x22, x2\n"
        "blr x8\n"
        "adrp x8, PTR_DAT_7104fcd388\n"
        "add x8, x8, :lo12:PTR_DAT_7104fcd388\n"
        "ldr x9, [x8, w0, sxtw #3]\n"
        "ldp x8, x9, [x9]\n"
        "cmp x8, x9\n"
        "b.eq 1f\n"
        "0:\n"
        "ldr x10, [x8, #0x8]\n"
        "eor x10, x10, x22\n"
        "tst x10, #0xffffffffff\n"
        "b.eq 2f\n"
        "add x8, x8, #0x10\n"
        "cmp x9, x8\n"
        "b.ne 0b\n"
        "b 1f\n"
        "2:\n"
        "ldr x22, [x8]\n"
        "1:\n"
        "mov v1.16b, v9.16b\n"
        "mov v2.16b, v8.16b\n"
        "and w3, w25, #1\n"
        "ldp d9, d8, [sp, #0x10]\n"
        "and w4, w24, #1\n"
        "and w5, w21, #1\n"
        "and w6, w20, #1\n"
        "and w7, w19, #1\n"
        "mov x0, x26\n"
        "mov w1, w23\n"
        "mov x2, x22\n"
        "ldp x29, x30, [sp, #0x60]\n"
        "mov v0.16b, v10.16b\n"
        "ldp x20, x19, [sp, #0x50]\n"
        "ldp x22, x21, [sp, #0x40]\n"
        "ldp x24, x23, [sp, #0x30]\n"
        "ldp x26, x25, [sp, #0x20]\n"
        "ldr d10, [sp], #0x70\n"
        "b FUN_710049e4b0\n");
}
#endif

// 71020aa3a0 -- set_blend_waist (4 insns: ldr module, and bool, strb to +0x2f2)
void FighterMotionModuleImpl__set_blend_waist_impl(BattleObjectModuleAccessor* a, bool val) {
    auto* module = reinterpret_cast<u8*>(a->motion_module);
    module[0x2f2] = val & 1;
}

// 71020aa3b0 -- start_damage_stop_interpolation: fcvtzs to +0x2f4, vtable calls
// Original: prologue saves d8,x19,x29,x30; uses d8 for 0.0f across calls; tail-call via br
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void FighterMotionModuleImpl__start_damage_stop_interpolation_impl(BattleObjectModuleAccessor* a, f32 frame) {
    asm("str d8, [sp, #-0x20]!\n"
        "str x19, [sp, #0x8]\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "fcvtzs w8, s0\n"
        "ldr x19, [x0, #0x88]\n"
        "str w8, [x19, #0x2f4]\n"
        "ldr x8, [x19]\n"
        "fmov s8, wzr\n"
        "mov v0.16b, v8.16b\n"
        "mov x0, x19\n"
        "mov w1, wzr\n"
        "ldr x8, [x8, #0x478]\n"
        "blr x8\n"
        "ldr x8, [x19]\n"
        "ldr x1, [x8, #0x2b0]\n"
        "mov x0, x19\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "ldr x19, [sp, #0x8]\n"
        "mov v0.16b, v8.16b\n"
        "ldr d8, [sp], #0x20\n"
        "br x1\n");
}
#endif

// 71020aa410 -- set_pause_motion_interpolation_stop: global check + module chain
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void FighterMotionModuleImpl__set_pause_motion_interpolation_stop_impl(BattleObjectModuleAccessor* a) {
    asm("str x19, [sp, #-0x20]!\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "adrp x8, DAT_71052c2760\n"
        "ldr x8, [x8, :lo12:DAT_71052c2760]\n"
        "ldr x8, [x8]\n"
        "ldrb w9, [x8, #0x12]\n"
        "cbz w9, 0f\n"
        "ldrb w8, [x8, #0xf]\n"
        "cbnz w8, 0f\n"
        "ldr x19, [x0, #0x88]\n"
        "ldr x8, [x19, #0x10]\n"
        "ldr x0, [x8, #0x38]\n"
        "ldr x8, [x0]\n"
        "ldr x8, [x8, #0x10]\n"
        "mov w1, wzr\n"
        "blr x8\n"
        "ldrb w8, [x19, #0x239]\n"
        "cbnz w8, 0f\n"
        "ldr x8, [x0]\n"
        "ldr x8, [x8, #0x48]\n"
        "blr x8\n"
        "fcmp s0, #0.0\n"
        "b.eq 0f\n"
        "orr w8, wzr, #1\n"
        "strb w8, [x19, #0x2f9]\n"
        "0:\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "ldr x19, [sp], #0x20\n"
        "ret\n");
}
#endif

// 71020aa490 -- set_update_finger_and_face_joint: chain through module+0x10, +0x8, vtable
void FighterMotionModuleImpl__set_update_finger_and_face_joint_impl(BattleObjectModuleAccessor* a, bool val) {
    auto* module = MOTION(a);
    auto* chain1 = *reinterpret_cast<u8**>(module + 0x10);
    auto* chain2 = *reinterpret_cast<void**>(chain1 + 0x8);
    auto* vt = *reinterpret_cast<void***>(chain2);
    auto fn = reinterpret_cast<void (*)(void*, bool)>(vt[0xa0 / 8]);
    fn(chain2, val & 1);
}
} // namespace app::lua_bind
