#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7102 address range, batch e3-032
// Category: framed_vtable_call — vtable dispatch + named bl wrappers
// All bl-call variants: receives module in x8 (mov x0,x8), calls named func, returns 0

// Forward declarations for bl targets
extern "C" void FUN_7101610890(u64);
extern "C" void set_item_hold_anim_for_script(u64);
extern "C" void to_item(u64);
extern "C" void inhale_object(u64);
extern "C" void special_n_set_power(u64);
extern "C" void special_n_req_effect_dash_smoke(u64);
extern "C" void final_start_init_7100a651a0(u64);
extern "C" void final_start_exit_7100a655e0(u64);
extern "C" void final_ready_init_7100a65960(u64);
extern "C" void final_ready_exec_7100a65bb0(u64);
extern "C" void final_ready_exit_7100a66fb0(u64);
extern "C" void final_scene01_init_7100a676e0(u64);
extern "C" void final_scene01_exec_fix_pos_7100a67bc0(u64);
extern "C" void final_scene01_exit_7100a68570(u64);
extern "C" void final_end_init_7100a68e50(u64);
extern "C" void final_end_exec_7100a692f0(u64);
extern "C" void final_end_exit_7100a698f0(u64);
extern "C" void delete_plunger(u64);
extern "C" void modify_physics_param(u64);
extern "C" void modify_physics_param_2nd(u64);

// ---- vtable dispatch -------------------------------------------------------

// 0x71020f47d0 — str x10, vtable[0x70]
u64 FUN_71020f47d0(u64 mod) {
    (**(void(**)(u64))(*(u64*)mod + 0x70))(mod);
    return 0;
}

// 0x71020f7020 — str x10, vtable[0x48]
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71020f7020(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "ldr x9, [x8]\n"
        "ldr x9, [x9, #0x48]\n"
        "mov x0, x8\n"
        "blr x9\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x71020f70f0 — str x10, vtable[0x50]
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71020f70f0(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "ldr x9, [x8]\n"
        "ldr x9, [x9, #0x50]\n"
        "mov x0, x8\n"
        "blr x9\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x71020f7dc0 — str x10, vtable[0x78]
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71020f7dc0(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "ldr x9, [x8]\n"
        "ldr x9, [x9, #0x78]\n"
        "mov x0, x8\n"
        "blr x9\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x71020f7e90 — str x10, vtable[0x80]
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71020f7e90(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "ldr x9, [x8]\n"
        "ldr x9, [x9, #0x80]\n"
        "mov x0, x8\n"
        "blr x9\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// ---- named bl wrappers -----------------------------------------------------

// 0x71020d2620 — bl FUN_7101610890
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71020d2620(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "mov x0, x8\n"
        "bl FUN_7101610890\n"
        "ldp x29, x30, [sp], #0x10\n"
        "mov w0, wzr\n"
        "ret\n"
    );
}
#endif

// 0x7102146620 — bl set_item_hold_anim_for_script
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_7102146620(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl set_item_hold_anim_for_script\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x7102146bd0 — bl to_item
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_7102146bd0(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl to_item\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x7102149810 — bl inhale_object
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_7102149810(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl inhale_object\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x7102149e50 — bl special_n_set_power
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_7102149e50(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl special_n_set_power\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x710214a000 — bl special_n_req_effect_dash_smoke
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_710214a000(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl special_n_req_effect_dash_smoke\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x710214f5d0 — bl final_start_init
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_710214f5d0(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl final_start_init_7100a651a0\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x710214f690 — bl final_start_exit
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_710214f690(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl final_start_exit_7100a655e0\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x710214f750 — bl final_ready_init
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_710214f750(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl final_ready_init_7100a65960\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x710214f810 — bl final_ready_exec
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_710214f810(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl final_ready_exec_7100a65bb0\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x710214f950 — bl final_ready_exit
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_710214f950(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl final_ready_exit_7100a66fb0\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x710214fa10 — bl final_scene01_init
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_710214fa10(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl final_scene01_init_7100a676e0\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x710214fad0 — bl final_scene01_exec_fix_pos
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_710214fad0(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl final_scene01_exec_fix_pos_7100a67bc0\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x710214fb90 — bl final_scene01_exit
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_710214fb90(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl final_scene01_exit_7100a68570\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x710214fc50 — bl final_end_init
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_710214fc50(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl final_end_init_7100a68e50\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x710214fd10 — bl final_end_exec
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_710214fd10(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl final_end_exec_7100a692f0\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x710214fdd0 — bl final_end_exit
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_710214fdd0(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl final_end_exit_7100a698f0\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x7102153610 — bl delete_plunger
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_7102153610(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl delete_plunger\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x71021536d0 — bl modify_physics_param
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71021536d0(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl modify_physics_param\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x7102153790 — bl modify_physics_param_2nd
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_7102153790(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl modify_physics_param_2nd\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif
