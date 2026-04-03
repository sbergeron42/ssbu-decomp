#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7102 address range, batch e3-036
// Category: framed_vtable_call — named bl wrappers (x8-dispatch, str-x10 variant)
// Address cluster: 0x7102182090–0x71021a2fa4

extern "C" void special_n_set_power(u64);
extern "C" void special_n_req_effect_dash_smoke(u64);
extern "C" void init_final_settings(u64);
extern "C" void exit_special_n_tron_hold(u64);
extern "C" void special_lw_heal_damage(u64);
extern "C" void send_final_attack_event(u64);
extern "C" void set_special_s_transition_term_forbid_group(u64);
extern "C" void set_link_final_end(u64);
extern "C" void update_moon_position(u64);
extern "C" void raise_moon_position(u64);
extern "C" void set_leafshield(u64);
extern "C" void set_final_stage_disp_status(u64);
extern "C" void hit_absolute_final_chrom(u64);
extern "C" void generate_rollerink(u64);
extern "C" void lack_ink(u64);
extern "C" void setup_physics_air_resistance(u64);
extern "C" void start_cut(u64);
extern "C" void enable_search(u64);

// 0x7102182090 — bl special_n_set_power
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_7102182090(void) {
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

// 0x7102182240 — bl special_n_req_effect_dash_smoke
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_7102182240(void) {
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

// 0x7102189d70 — bl init_final_settings
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_7102189d70(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl init_final_settings\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x710218a2c0 — bl exit_special_n_tron_hold
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_710218a2c0(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl exit_special_n_tron_hold\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x710218a920 — bl special_lw_heal_damage
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_710218a920(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl special_lw_heal_damage\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x710218ab20 — bl send_final_attack_event
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_710218ab20(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl send_final_attack_event\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x710218d844 — bl set_special_s_transition_term_forbid_group
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_710218d844(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl set_special_s_transition_term_forbid_group\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x710218db34 — bl set_link_final_end
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_710218db34(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl set_link_final_end\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x710218dc10 — bl update_moon_position
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_710218dc10(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl update_moon_position\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x710218dcd0 — bl raise_moon_position
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_710218dcd0(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl raise_moon_position\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x7102192724 — bl set_leafshield
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_7102192724(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl set_leafshield\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x71021958a8 — bl set_final_stage_disp_status
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71021958a8(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl set_final_stage_disp_status\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x7102198f90 — bl hit_absolute_final_chrom
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_7102198f90(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl hit_absolute_final_chrom\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x710219e950 — bl generate_rollerink
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_710219e950(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl generate_rollerink\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x710219ec30 — bl lack_ink
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_710219ec30(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl lack_ink\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x71021a2db0 — bl setup_physics_air_resistance
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71021a2db0(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl setup_physics_air_resistance\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x71021a2e70 — bl start_cut
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71021a2e70(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl start_cut\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x71021a2fa4 — bl enable_search
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71021a2fa4(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl enable_search\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif
