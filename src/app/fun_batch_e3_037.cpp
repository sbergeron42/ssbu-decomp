#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7102 address range, batch e3-037
// Category: framed_vtable_call — named bl wrappers (x8-dispatch, str-x10 variant)
// Address cluster: 0x71021aa240–0x71021c4000

extern "C" void request_special_s_wall_effect(u64);
extern "C" void generate_rope(u64);
extern "C" void revenge_off(u64);
extern "C" void sleep_attack_by_speed(u64);
extern "C" void reset_node_fix_flag_list(u64);
extern "C" void update_special_n_spikeball_pos(u64);
extern "C" void start_final_packun(u64);
extern "C" void end_final_packun(u64);
extern "C" void end_turn(u64);
extern "C" void set_doyle_suspend(u64);
extern "C" void update_aura_visible(u64);
extern "C" void lot_critical(u64);
extern "C" void special_lw_open_command(u64);
extern "C" void special_lw_start_select_command(u64);
extern "C" void special_lw_close_window(u64);
extern "C" void special_lw_cursor_decide(u64);
extern "C" void special_lw_start_cursor_blink(u64);
extern "C" void special_lw_on_start_command(u64);
extern "C" void request_effect_71033c94f0(u64);
extern "C" void exec_map_collection(u64);
extern "C" void update_special_n_partner_motion(u64);
extern "C" void request_bound_effect_71033cd000(u64);

// 0x71021aa240 — bl request_special_s_wall_effect
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71021aa240(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl request_special_s_wall_effect\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x71021ab100 — bl generate_rope
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71021ab100(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl generate_rope\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x71021ab250 — bl revenge_off
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71021ab250(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl revenge_off\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x71021ac310 — bl sleep_attack_by_speed
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71021ac310(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl sleep_attack_by_speed\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x71021ad260 — bl reset_node_fix_flag_list
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71021ad260(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl reset_node_fix_flag_list\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x71021b0d00 — bl update_special_n_spikeball_pos
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71021b0d00(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl update_special_n_spikeball_pos\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x71021b0dc0 — bl start_final_packun
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71021b0dc0(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl start_final_packun\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x71021b0e80 — bl end_final_packun
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71021b0e80(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl end_final_packun\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x71021b0f40 — bl end_turn
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71021b0f40(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl end_turn\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x71021b3884 — bl set_doyle_suspend
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71021b3884(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl set_doyle_suspend\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x71021b3c50 — bl update_aura_visible
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71021b3c50(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl update_aura_visible\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x71021b6250 — bl lot_critical
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71021b6250(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl lot_critical\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x71021b6490 — bl special_lw_open_command
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71021b6490(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl special_lw_open_command\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x71021b6550 — bl special_lw_start_select_command
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71021b6550(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl special_lw_start_select_command\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x71021b67b0 — bl special_lw_close_window
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71021b67b0(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl special_lw_close_window\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x71021b6980 — bl special_lw_cursor_decide
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71021b6980(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl special_lw_cursor_decide\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x71021b6a40 — bl special_lw_start_cursor_blink
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71021b6a40(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl special_lw_start_cursor_blink\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x71021b6c10 — bl special_lw_on_start_command
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71021b6c10(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl special_lw_on_start_command\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x71021b7e60 — bl request_effect (0x71033c94f0)
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71021b7e60(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl request_effect_71033c94f0\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x71021b7f20 — bl exec_map_collection
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71021b7f20(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl exec_map_collection\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x71021ba7c0 — bl update_special_n_partner_motion
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71021ba7c0(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl update_special_n_partner_motion\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x71021ba9d0 — bl request_bound_effect (0x71033cd000)
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71021ba9d0(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl request_bound_effect_71033cd000\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif
