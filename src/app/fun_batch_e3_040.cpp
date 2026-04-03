#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7102 address range, batch e3-040
// Category: framed_vtable_call — named bl wrappers (mixed 10-insn and 6-insn variants)
// Address cluster: 0x7102238360–0x7102247d60

extern "C" void set_reflector_7101655660(u64);
extern "C" void set_grab_7101656010(u64);
extern "C" void check_roll_up_area(u64);
extern "C" void set_dragoonsight_effect(u64);
extern "C" void fighter_heal(u64);
extern "C" void homerun_contest_change_fly_camera(u64);
extern "C" void homerun_contest_change_landing_camera(u64);
extern "C" void homerun_contest_change_timeup_fly_camera(u64);
extern "C" void homerun_contest_change_normal_camera(u64);
extern "C" void escape_from_fighter(u64);
extern "C" void chase_fighter(u64);
extern "C" void clear_collision_info(u64);
extern "C" void free_log_group(u64);
extern "C" void hit_check(u64);
extern "C" void set_shield(u64);
extern "C" void throw_attack_71016479a0(u64);
extern "C" void set_nintendogs_effect(u64);
extern "C" void yorokobemo(u64);
extern "C" void healdamo(u64);
extern "C" void stealdamo(u64);
extern "C" void set_reflector_710164fda0(u64);
extern "C" void ReflectOnViewFrame(u64);
extern "C" void set_reflector_710167cc50(u64);
extern "C" void powerup(u64);
extern "C" void send_link_event_final_finish_pre(u64);

// 0x7102238360 — bl set_reflector (0x7101655660)
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_7102238360(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl set_reflector_7101655660\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x7102238550 — bl set_grab (0x7101656010)
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_7102238550(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl set_grab_7101656010\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x7102239370 — bl check_roll_up_area
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_7102239370(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl check_roll_up_area\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x710223a064 — bl set_dragoonsight_effect
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_710223a064(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl set_dragoonsight_effect\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x710223ad10 — bl fighter_heal
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_710223ad10(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl fighter_heal\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x710223fc70 — bl homerun_contest_change_fly_camera
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_710223fc70(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "bl homerun_contest_change_fly_camera\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x710223fc90 — bl homerun_contest_change_landing_camera
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_710223fc90(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "bl homerun_contest_change_landing_camera\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x710223fcb0 — bl homerun_contest_change_timeup_fly_camera
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_710223fcb0(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "bl homerun_contest_change_timeup_fly_camera\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x710223fcd0 — bl homerun_contest_change_normal_camera
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_710223fcd0(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "bl homerun_contest_change_normal_camera\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x71022409e0 — bl escape_from_fighter
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71022409e0(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl escape_from_fighter\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x7102240aa0 — bl chase_fighter
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_7102240aa0(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl chase_fighter\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x7102241d50 — bl clear_collision_info
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_7102241d50(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl clear_collision_info\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x7102242a70 — bl free_log_group
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_7102242a70(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl free_log_group\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x7102242bb0 — bl hit_check
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_7102242bb0(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl hit_check\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x71022438f0 — bl set_shield
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71022438f0(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl set_shield\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x7102243e60 — bl throw_attack (0x71016479a0)
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_7102243e60(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl throw_attack_71016479a0\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x7102244924 — bl set_nintendogs_effect
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_7102244924(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl set_nintendogs_effect\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x7102244ad0 — bl yorokobemo
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_7102244ad0(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl yorokobemo\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x7102244b90 — bl healdamo
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_7102244b90(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl healdamo\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x7102244c50 — bl stealdamo
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_7102244c50(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl stealdamo\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x71022453f0 — bl set_reflector (0x710164fda0)
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71022453f0(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl set_reflector_710164fda0\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x7102246b80 — bl ReflectOnViewFrame
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_7102246b80(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl ReflectOnViewFrame\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x7102247040 — bl set_reflector (0x710167cc50)
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_7102247040(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl set_reflector_710167cc50\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x7102247280 — bl powerup
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_7102247280(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl powerup\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x71022475d0 — bl send_link_event_final_finish_pre
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71022475d0(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl send_link_event_final_finish_pre\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif
