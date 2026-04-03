#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7102 address range, batch e3-031
// Category: framed_vtable_call — two sub-patterns:
//   (a) vtable dispatch: receives module in x8, calls vtable[N], returns 0
//   (b) direct bl call:  receives module in x8, calls named function, returns 0

// Forward declarations for (b) pattern targets
extern "C" void init_big_small(u64);
extern "C" void exec_big_small(u64);
extern "C" void exit_big_small(u64);
extern "C" void reset_hit_data(u64);
extern "C" void clung_thrown_diddy_unlink_capture(u64);
extern "C" void set_restart_up_position(u64);
extern "C" void set_parent_external_stat_bank_handle(u64);
extern "C" void flash_eye_info(u64);
extern "C" void jump_board_on(u64);

// ---- (a) vtable dispatch -----------------------------------------------

// 0x71020afd68 — str x10, vtable[0x460]
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71020afd68(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "ldr x9, [x8]\n"
        "ldr x9, [x9, #0x460]\n"
        "mov x0, x8\n"
        "blr x9\n"
        "ldp x29, x30, [sp], #0x10\n"
        "mov w0, wzr\n"
        "ret\n"
    );
}
#endif

// ---- (b) direct bl call ------------------------------------------------

// 0x71020c04f0 — bl init_big_small
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71020c04f0(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl init_big_small\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x71020c05b0 — bl exec_big_small
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71020c05b0(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl exec_big_small\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x71020c0670 — bl exit_big_small
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71020c0670(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl exit_big_small\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x71020c0d90 — bl reset_hit_data
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71020c0d90(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl reset_hit_data\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x71020c11b0 — bl clung_thrown_diddy_unlink_capture
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71020c11b0(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl clung_thrown_diddy_unlink_capture\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x71020c13b0 — bl set_restart_up_position
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71020c13b0(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl set_restart_up_position\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x71020c1690 — bl set_parent_external_stat_bank_handle
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71020c1690(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl set_parent_external_stat_bank_handle\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x71020c3ba0 — bl flash_eye_info
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71020c3ba0(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl flash_eye_info\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x71020c6d60 — bl jump_board_on
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71020c6d60(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl jump_board_on\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif
