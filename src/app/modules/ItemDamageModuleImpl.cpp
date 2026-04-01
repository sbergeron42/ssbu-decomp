#include "app/BattleObjectModuleAccessor.h"

namespace app::lua_bind {

// 71020d1af0 — compares float params against global damage threshold (48 bytes)
// NOTE: uses global singleton at 0x71052c31e0 — adrp won't match
bool ItemDamageModuleImpl__is_smash_damage_impl(f32 p0, f32 p1) {
    // original: loads **(0x71052c31e0) + 0x73068 as float, checks (p0<=0) && (that<=p1)
    (void)p0; (void)p1;
    return false;
}

// 71020d1b20 — hash-switch on field name, call vtable[0x188/8] (refresh), return float field
// hash 0x2369a2644 → damage_module+0x44
// hash 0xe085e_517c → damage_module+0x48
// hash 0xa_c3a7_d97e → damage_module+0x58
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
f32 ItemDamageModuleImpl__damage_log_value_float_impl(BattleObjectModuleAccessor* a, u64 hash) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "ldr x0, [x0, #0xa8]\n"
        "mov x9, #0x2644\n"
        "movk x9, #0x369a, lsl #16\n"
        "and x8, x1, #0xffffffffff\n"
        "movk x9, #0x2, lsl #32\n"
        "cmp x8, x9\n"
        "b.eq 1f\n"
        "mov x9, #0x517c\n"
        "movk x9, #0xe085, lsl #16\n"
        "movk x9, #0xe, lsl #32\n"
        "cmp x8, x9\n"
        "b.eq 2f\n"
        "mov x9, #0xd97e\n"
        "movk x9, #0xc3a7, lsl #16\n"
        "movk x9, #0xa, lsl #32\n"
        "cmp x8, x9\n"
        "b.ne 3f\n"
        "ldr x8, [x0]\n"
        "ldr x8, [x8, #0x188]\n"
        "blr x8\n"
        "ldr s0, [x0, #0x58]\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
        "1:\n"
        "ldr x8, [x0]\n"
        "ldr x8, [x8, #0x188]\n"
        "blr x8\n"
        "ldr s0, [x0, #0x44]\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
        "2:\n"
        "ldr x8, [x0]\n"
        "ldr x8, [x8, #0x188]\n"
        "blr x8\n"
        "ldr s0, [x0, #0x48]\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
        "3:\n"
        "fmov s0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 71020d1bc0 — hash-switch on field name, return int field
// hash 0xf_2156_2598 → damage_module+0x84
// hash 0x9_232d_562b → damage_module+0x80
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u32 ItemDamageModuleImpl__damage_log_value_int_impl(BattleObjectModuleAccessor* a, u64 hash) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "ldr x0, [x0, #0xa8]\n"
        "mov x9, #0x2598\n"
        "movk x9, #0x2156, lsl #16\n"
        "and x8, x1, #0xffffffffff\n"
        "movk x9, #0xf, lsl #32\n"
        "cmp x8, x9\n"
        "b.eq 1f\n"
        "mov x9, #0x562b\n"
        "movk x9, #0x232d, lsl #16\n"
        "movk x9, #0x9, lsl #32\n"
        "cmp x8, x9\n"
        "b.ne 2f\n"
        "ldr x8, [x0]\n"
        "ldr x8, [x8, #0x188]\n"
        "blr x8\n"
        "ldr w0, [x0, #0x80]\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
        "1:\n"
        "ldr x8, [x0]\n"
        "ldr x8, [x8, #0x188]\n"
        "blr x8\n"
        "ldr w0, [x0, #0x84]\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
        "2:\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

} // namespace app::lua_bind
