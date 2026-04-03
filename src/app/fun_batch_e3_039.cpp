#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7102 address range, batch e3-039
// Category: framed_vtable_call — named bl wrappers (6-insn standard-call variant)
// No str-x10 / mov-x0,x8; argument arrives in x0 directly
// Address cluster: 0x71021f72f0–0x710220c2a0

extern "C" void FUN_71015c0410(u64);
extern "C" void apply_powerup_throw(u64);
extern "C" void apply_powerup_etc(u64);
extern "C" void apply_powerup_attr(u64);
extern "C" void send_event_on_boss_dead(u64);
extern "C" void disable_ground_collision(u64);
extern "C" void del_cursor(u64);
extern "C" void clear_owner_color(u64);

// 0x71021f72f0 — bl FUN_71015c0410
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
// FUN_71021f72f0 � defined in earlier batch file
#endif

// 0x71021ff030 — bl apply_powerup_throw
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71021ff030(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "bl apply_powerup_throw\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x71021ff1c0 — bl apply_powerup_etc
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71021ff1c0(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "bl apply_powerup_etc\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x71021ff230 — bl apply_powerup_attr
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71021ff230(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "bl apply_powerup_attr\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x7102208d00 — bl send_event_on_boss_dead
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_7102208d00(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "bl send_event_on_boss_dead\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x710220bf50 — bl disable_ground_collision
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_710220bf50(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "bl disable_ground_collision\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x710220c280 — bl del_cursor
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_710220c280(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "bl del_cursor\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x710220c2a0 — bl clear_owner_color
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_710220c2a0(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "bl clear_owner_color\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif
