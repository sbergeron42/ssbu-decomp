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
u64 FUN_710215e150(u64 mod) {
    final_scene01_exit_7100a4b130(mod);
    return 0;
}

// 0x710215e210 — bl final_end_init (0x7100a4bbb0)
u64 FUN_710215e210(u64 mod) {
    final_end_init_7100a4bbb0(mod);
    return 0;
}

// 0x710215e2d0 — bl final_end_exec (0x7100a4c050)
u64 FUN_710215e2d0(u64 mod) {
    final_end_exec_7100a4c050(mod);
    return 0;
}

// 0x710215e390 — bl final_end_exit (0x7100a4c650)
u64 FUN_710215e390(u64 mod) {
    final_end_exit_7100a4c650(mod);
    return 0;
}

// 0x7102162550 — bl end_final
u64 FUN_7102162550(u64 mod) {
    end_final(mod);
    return 0;
}

// 0x7102162700 — bl initialize_reticle
u64 FUN_7102162700(u64 mod) {
    initialize_reticle(mod);
    return 0;
}

// 0x7102162a00 — bl lock_on_ready
u64 FUN_7102162a00(u64 mod) {
    lock_on_ready(mod);
    return 0;
}

// 0x7102162ac0 — bl lock_on
u64 FUN_7102162ac0(u64 mod) {
    lock_on(mod);
    return 0;
}

// 0x7102163c70 — bl detach_constraint
u64 FUN_7102163c70(u64 mod) {
    detach_constraint(mod);
    return 0;
}

// 0x7102167070 — bl set_special_n_ground_effect
u64 FUN_7102167070(u64 mod) {
    set_special_n_ground_effect(mod);
    return 0;
}

// 0x7102167130 — bl check_edge_special_lw
u64 FUN_7102167130(u64 mod) {
    check_edge_special_lw(mod);
    return 0;
}

// 0x71021673b0 — bl request_cut_in_chariotsight
u64 FUN_71021673b0(u64 mod) {
    request_cut_in_chariotsight(mod);
    return 0;
}

// 0x7102168ec0 — bl start_final_szerosuit
u64 FUN_7102168ec0(u64 mod) {
    start_final_szerosuit(mod);
    return 0;
}

// 0x7102168f80 — bl start_final_szerosuit_camera
u64 FUN_7102168f80(u64 mod) {
    start_final_szerosuit_camera(mod);
    return 0;
}

// 0x7102169040 — bl exec_final_szerosuit_camera
u64 FUN_7102169040(u64 mod) {
    exec_final_szerosuit_camera(mod);
    return 0;
}

// 0x7102169100 — bl end_final_szerosuit
u64 FUN_7102169100(u64 mod) {
    end_final_szerosuit(mod);
    return 0;
}

// 0x710216adb0 — bl reduce_pikmin_all
u64 FUN_710216adb0(u64 mod) {
    reduce_pikmin_all(mod);
    return 0;
}

// 0x710216ae70 — bl reduce_pikmin_all_change_top_pikmin
u64 FUN_710216ae70(u64 mod) {
    reduce_pikmin_all_change_top_pikmin(mod);
    return 0;
}

// 0x710216b1a0 — bl liberty_pikmin_all
u64 FUN_710216b1a0(u64 mod) {
    liberty_pikmin_all(mod);
    return 0;
}
