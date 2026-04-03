#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7102 address range, batch e3-038
// Category: framed_vtable_call — named bl wrappers (x8-dispatch, str-x10 variant)
// Address cluster: 0x71021beeb4–0x71021e2520

extern "C" void set_search_7103443100(u64);
extern "C" void check_attack_reverse(u64);
extern "C" void clear_control_command_punch(u64);
extern "C" void clear_control_command_move(u64);
extern "C" void update_tip_pos(u64);
extern "C" void update_dragon_beam_nest_tip_pos(u64);
extern "C" void check_attach(u64);
extern "C" void create_table(u64);
extern "C" void update_mining_pickelobject(u64);
extern "C" void FUN_7100f03ef0(u64);
extern "C" void remove_have_craft_weapon_all(u64);
extern "C" void set_head_angle_change_motion(u64);
extern "C" void send_link_event_nodes_check_collision(u64);
extern "C" void set_original_pickel_team(u64);
extern "C" void set_z_pos_for_flat_stage(u64);
extern "C" void check_disabled_motion_camera_of_stage(u64);
extern "C" void check_disabled_motion_camera_of_scale(u64);
extern "C" void update_fly_posture(u64);
extern "C" void change_magic(u64);
extern "C" void remove_constraint(u64);
extern "C" void set_one_winged_light_weight_data(u64);
extern "C" void request_effect_71033ec900(u64);

// 0x71021beeb4 — bl set_search (0x7103443100)
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71021beeb4(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl set_search_7103443100\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x71021c2650 — bl check_attack_reverse
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71021c2650(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl check_attack_reverse\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x71021c2930 — bl clear_control_command_punch
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71021c2930(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl clear_control_command_punch\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x71021c29f0 — bl clear_control_command_move
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71021c29f0(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl clear_control_command_move\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x71021c3050 — bl update_tip_pos
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71021c3050(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl update_tip_pos\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x71021c3890 — bl update_dragon_beam_nest_tip_pos
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71021c3890(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl update_dragon_beam_nest_tip_pos\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x71021c4000 — bl check_attach
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71021c4000(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl check_attach\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x71021c7c1c — bl create_table
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71021c7c1c(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl create_table\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x71021c86e0 — bl update_mining_pickelobject
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71021c86e0(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl update_mining_pickelobject\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x71021c8c30 — bl FUN_7100f03ef0
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71021c8c30(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl FUN_7100f03ef0\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x71021ca8e0 — bl remove_have_craft_weapon_all
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71021ca8e0(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl remove_have_craft_weapon_all\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x71021cbd00 — bl set_head_angle_change_motion
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71021cbd00(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl set_head_angle_change_motion\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x71021cc550 — bl send_link_event_nodes_check_collision
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71021cc550(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl send_link_event_nodes_check_collision\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x71021cc610 — bl set_original_pickel_team
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71021cc610(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl set_original_pickel_team\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x71021d3680 — bl set_z_pos_for_flat_stage
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71021d3680(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl set_z_pos_for_flat_stage\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x71021d8910 — bl check_disabled_motion_camera_of_stage
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71021d8910(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl check_disabled_motion_camera_of_stage\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x71021d89d0 — bl check_disabled_motion_camera_of_scale
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71021d89d0(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl check_disabled_motion_camera_of_scale\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x71021d9730 — bl update_fly_posture
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71021d9730(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl update_fly_posture\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x71021db850 — bl change_magic
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71021db850(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl change_magic\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x71021de820 — bl remove_constraint
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71021de820(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl remove_constraint\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x71021e1290 — bl set_one_winged_light_weight_data
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71021e1290(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl set_one_winged_light_weight_data\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x71021e2520 — bl request_effect (0x71033ec900)
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71021e2520(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl request_effect_71033ec900\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif
