#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7102 address range, batch e3-035
// Category: framed_vtable_call — named bl wrappers (x8-dispatch, str-x10 variant)
// Address cluster: 0x7102177a40–0x710217ff90

extern "C" void end_special_n_shot_object_hit(u64);
extern "C" void req_aura_effect_both(u64);
extern "C" void effect_suspend(u64);
extern "C" void effect_resume(u64);
extern "C" void set_scale(u64);
extern "C" void calc_pos(u64);
extern "C" void start_final_sonic(u64);
extern "C" void start_final_sonic_camera(u64);
extern "C" void end_final_sonic(u64);

// 0x7102177a40 — bl end_special_n_shot_object_hit
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_7102177a40(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl end_special_n_shot_object_hit\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x710217b270 — bl req_aura_effect_both
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_710217b270(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl req_aura_effect_both\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x710217b330 — bl effect_suspend
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_710217b330(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl effect_suspend\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x710217b3f0 — bl effect_resume
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_710217b3f0(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl effect_resume\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x710217b900 — bl set_scale
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_710217b900(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl set_scale\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x710217c470 — bl calc_pos
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_710217c470(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl calc_pos\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x710217fe10 — bl start_final_sonic
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_710217fe10(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl start_final_sonic\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x710217fed0 — bl start_final_sonic_camera
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_710217fed0(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl start_final_sonic_camera\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x710217ff90 — bl end_final_sonic
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_710217ff90(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl end_final_sonic\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif
