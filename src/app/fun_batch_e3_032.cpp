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
u64 FUN_71020f7020(u64 mod) {
    (**(void(**)(u64))(*(u64*)mod + 0x48))(mod);
    return 0;
}

// 0x71020f70f0 — str x10, vtable[0x50]
u64 FUN_71020f70f0(u64 mod) {
    (**(void(**)(u64))(*(u64*)mod + 0x50))(mod);
    return 0;
}

// 0x71020f7dc0 — str x10, vtable[0x78]
u64 FUN_71020f7dc0(u64 mod) {
    (**(void(**)(u64))(*(u64*)mod + 0x78))(mod);
    return 0;
}

// 0x71020f7e90 — str x10, vtable[0x80]
u64 FUN_71020f7e90(u64 mod) {
    (**(void(**)(u64))(*(u64*)mod + 0x80))(mod);
    return 0;
}

// ---- named bl wrappers -----------------------------------------------------

// 0x71020d2620 — bl FUN_7101610890
u64 FUN_71020d2620(u64 mod) {
    FUN_7101610890(mod);
    return 0;
}

// 0x7102146620 — bl set_item_hold_anim_for_script
u64 FUN_7102146620(u64 mod) {
    set_item_hold_anim_for_script(mod);
    return 0;
}

// 0x7102146bd0 — bl to_item
u64 FUN_7102146bd0(u64 mod) {
    to_item(mod);
    return 0;
}

// 0x7102149810 — bl inhale_object
u64 FUN_7102149810(u64 mod) {
    inhale_object(mod);
    return 0;
}

// 0x7102149e50 — bl special_n_set_power
u64 FUN_7102149e50(u64 mod) {
    special_n_set_power(mod);
    return 0;
}

// 0x710214a000 — bl special_n_req_effect_dash_smoke
u64 FUN_710214a000(u64 mod) {
    special_n_req_effect_dash_smoke(mod);
    return 0;
}

// 0x710214f5d0 — bl final_start_init
u64 FUN_710214f5d0(u64 mod) {
    final_start_init_7100a651a0(mod);
    return 0;
}

// 0x710214f690 — bl final_start_exit
u64 FUN_710214f690(u64 mod) {
    final_start_exit_7100a655e0(mod);
    return 0;
}

// 0x710214f750 — bl final_ready_init
u64 FUN_710214f750(u64 mod) {
    final_ready_init_7100a65960(mod);
    return 0;
}

// 0x710214f810 — bl final_ready_exec
u64 FUN_710214f810(u64 mod) {
    final_ready_exec_7100a65bb0(mod);
    return 0;
}

// 0x710214f950 — bl final_ready_exit
u64 FUN_710214f950(u64 mod) {
    final_ready_exit_7100a66fb0(mod);
    return 0;
}

// 0x710214fa10 — bl final_scene01_init
u64 FUN_710214fa10(u64 mod) {
    final_scene01_init_7100a676e0(mod);
    return 0;
}

// 0x710214fad0 — bl final_scene01_exec_fix_pos
u64 FUN_710214fad0(u64 mod) {
    final_scene01_exec_fix_pos_7100a67bc0(mod);
    return 0;
}

// 0x710214fb90 — bl final_scene01_exit
u64 FUN_710214fb90(u64 mod) {
    final_scene01_exit_7100a68570(mod);
    return 0;
}

// 0x710214fc50 — bl final_end_init
u64 FUN_710214fc50(u64 mod) {
    final_end_init_7100a68e50(mod);
    return 0;
}

// 0x710214fd10 — bl final_end_exec
u64 FUN_710214fd10(u64 mod) {
    final_end_exec_7100a692f0(mod);
    return 0;
}

// 0x710214fdd0 — bl final_end_exit
u64 FUN_710214fdd0(u64 mod) {
    final_end_exit_7100a698f0(mod);
    return 0;
}

// 0x7102153610 — bl delete_plunger
u64 FUN_7102153610(u64 mod) {
    delete_plunger(mod);
    return 0;
}

// 0x71021536d0 — bl modify_physics_param
u64 FUN_71021536d0(u64 mod) {
    modify_physics_param(mod);
    return 0;
}

// 0x7102153790 — bl modify_physics_param_2nd
u64 FUN_7102153790(u64 mod) {
    modify_physics_param_2nd(mod);
    return 0;
}
