#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7102 address range, batch e3-033
// Category: framed_vtable_call — named bl wrappers (mov x0,x8 / bl NAMED / return 0)
// Two address clusters: 0x7102157540–0x7102158860 and 0x710215db90–0x710215e090

// Forward declarations — cluster 1 (Ice Climbers / Link LW character-specific)
extern "C" void special_lw_check_num_of_item(u64);
extern "C" void final_rand_create_item(u64);
extern "C" void init_lr_special_s_partner(u64);
extern "C" void init_lr_special_hi_cliff_comp(u64);
extern "C" void change_status_special_s_partner(u64);
extern "C" void init_final_partner(u64);
extern "C" void start_partner_turn(u64);
extern "C" void start_final_popo(u64);
extern "C" void start_final_popo_camera(u64);
extern "C" void enable_partner_catch_transition(u64);
extern "C" void end_final_deactivated_iceberg(u64);

// Forward declarations — cluster 2 (final_* phase wrappers, address-suffixed to
// disambiguate from the identically-named targets in fun_batch_e3_032.cpp)
extern "C" void final_start_init_7100a48080(u64);
extern "C" void final_start_exit_7100a483f0(u64);
extern "C" void final_ready_init_7100a48770(u64);
extern "C" void final_ready_exec_7100a489c0(u64);
extern "C" void final_ready_exit_7100a49cd0(u64);
extern "C" void final_scene01_init_7100a4a400(u64);
extern "C" void final_scene01_exec_fix_pos_7100a4a8e0(u64);

// ---- cluster 1 — 0x7102157540–0x7102158860 --------------------------------

// 0x7102157540 — bl special_lw_check_num_of_item
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_7102157540(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl special_lw_check_num_of_item\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x7102157720 — bl final_rand_create_item
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_7102157720(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl final_rand_create_item\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x7102157b90 — bl init_lr_special_s_partner
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_7102157b90(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl init_lr_special_s_partner\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x7102157c50 — bl init_lr_special_hi_cliff_comp
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_7102157c50(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl init_lr_special_hi_cliff_comp\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x7102157d10 — bl change_status_special_s_partner
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_7102157d10(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl change_status_special_s_partner\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x7102157ee0 — bl init_final_partner
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_7102157ee0(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl init_final_partner\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x71021580c0 — bl start_partner_turn
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71021580c0(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl start_partner_turn\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x7102158530 — bl start_final_popo
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_7102158530(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl start_final_popo\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x71021585f0 — bl start_final_popo_camera
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71021585f0(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl start_final_popo_camera\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x71021587a0 — bl enable_partner_catch_transition
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71021587a0(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl enable_partner_catch_transition\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x7102158860 — bl end_final_deactivated_iceberg
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_7102158860(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl end_final_deactivated_iceberg\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// ---- cluster 2 — 0x710215db90–0x710215e090 ---------------------------------

// 0x710215db90 — bl final_start_init (0x7100a48080)
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_710215db90(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl final_start_init_7100a48080\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x710215dc50 — bl final_start_exit (0x7100a483f0)
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_710215dc50(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl final_start_exit_7100a483f0\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x710215dd10 — bl final_ready_init (0x7100a48770)
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_710215dd10(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl final_ready_init_7100a48770\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x710215ddd0 — bl final_ready_exec (0x7100a489c0)
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_710215ddd0(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl final_ready_exec_7100a489c0\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x710215df10 — bl final_ready_exit (0x7100a49cd0)
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_710215df10(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl final_ready_exit_7100a49cd0\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x710215dfd0 — bl final_scene01_init (0x7100a4a400)
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_710215dfd0(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl final_scene01_init_7100a4a400\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x710215e090 — bl final_scene01_exec_fix_pos (0x7100a4a8e0)
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_710215e090(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl final_scene01_exec_fix_pos_7100a4a8e0\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif
