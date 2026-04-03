#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7102 address range, batch e3-034
// Category: framed_vtable_call — named bl wrappers (x8-dispatch, str-x10 variant)
// Address cluster: 0x710215e150–0x710216b1a0

// Forward declarations — final phase wrappers (address-suffixed, different targets than e3-032)
extern "C" void final_scene01_exit_7100a4b130(u64);
extern "C" void final_end_init_7100a4bbb0(u64);
extern "C" void final_end_exec_7100a4c050(u64);
extern "C" void final_end_exit_7100a4c650(u64);

// Forward declarations — mixed character-specific functions
extern "C" void end_final(u64);
extern "C" void initialize_reticle(u64);
extern "C" void lock_on_ready(u64);
extern "C" void lock_on(u64);
extern "C" void detach_constraint(u64);
extern "C" void set_special_n_ground_effect(u64);
extern "C" void check_edge_special_lw(u64);
extern "C" void request_cut_in_chariotsight(u64);
extern "C" void start_final_szerosuit(u64);
extern "C" void start_final_szerosuit_camera(u64);
extern "C" void exec_final_szerosuit_camera(u64);
extern "C" void end_final_szerosuit(u64);
extern "C" void reduce_pikmin_all(u64);
extern "C" void reduce_pikmin_all_change_top_pikmin(u64);
extern "C" void liberty_pikmin_all(u64);

// 0x710215e150 — bl final_scene01_exit (0x7100a4b130)
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_710215e150(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl final_scene01_exit_7100a4b130\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x710215e210 — bl final_end_init (0x7100a4bbb0)
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_710215e210(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl final_end_init_7100a4bbb0\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x710215e2d0 — bl final_end_exec (0x7100a4c050)
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_710215e2d0(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl final_end_exec_7100a4c050\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x710215e390 — bl final_end_exit (0x7100a4c650)
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_710215e390(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl final_end_exit_7100a4c650\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x7102162550 — bl end_final
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_7102162550(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl end_final\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x7102162700 — bl initialize_reticle
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_7102162700(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl initialize_reticle\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x7102162a00 — bl lock_on_ready
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_7102162a00(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl lock_on_ready\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x7102162ac0 — bl lock_on
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_7102162ac0(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl lock_on\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x7102163c70 — bl detach_constraint
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_7102163c70(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl detach_constraint\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x7102167070 — bl set_special_n_ground_effect
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_7102167070(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl set_special_n_ground_effect\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x7102167130 — bl check_edge_special_lw
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_7102167130(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl check_edge_special_lw\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x71021673b0 — bl request_cut_in_chariotsight
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71021673b0(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl request_cut_in_chariotsight\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x7102168ec0 — bl start_final_szerosuit
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_7102168ec0(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl start_final_szerosuit\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x7102168f80 — bl start_final_szerosuit_camera
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_7102168f80(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl start_final_szerosuit_camera\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x7102169040 — bl exec_final_szerosuit_camera
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_7102169040(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl exec_final_szerosuit_camera\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x7102169100 — bl end_final_szerosuit
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_7102169100(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl end_final_szerosuit\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x710216adb0 — bl reduce_pikmin_all
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_710216adb0(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl reduce_pikmin_all\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x710216ae70 — bl reduce_pikmin_all_change_top_pikmin
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_710216ae70(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl reduce_pikmin_all_change_top_pikmin\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x710216b1a0 — bl liberty_pikmin_all
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_710216b1a0(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl liberty_pikmin_all\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif
