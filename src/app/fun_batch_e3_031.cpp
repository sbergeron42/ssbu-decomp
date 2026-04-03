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
u64 FUN_71020afd68(u64 mod) {
    (**(void(**)(u64))(*(u64*)mod + 0x460))(mod);
    return 0;
}

// ---- (b) direct bl call ------------------------------------------------

// 0x71020c04f0 — bl init_big_small
u64 FUN_71020c04f0(u64 mod) {
    init_big_small(mod);
    return 0;
}

// 0x71020c05b0 — bl exec_big_small
u64 FUN_71020c05b0(u64 mod) {
    exec_big_small(mod);
    return 0;
}

// 0x71020c0670 — bl exit_big_small
u64 FUN_71020c0670(u64 mod) {
    exit_big_small(mod);
    return 0;
}

// 0x71020c0d90 — bl reset_hit_data
u64 FUN_71020c0d90(u64 mod) {
    reset_hit_data(mod);
    return 0;
}

// 0x71020c11b0 — bl clung_thrown_diddy_unlink_capture
u64 FUN_71020c11b0(u64 mod) {
    clung_thrown_diddy_unlink_capture(mod);
    return 0;
}

// 0x71020c13b0 — bl set_restart_up_position
u64 FUN_71020c13b0(u64 mod) {
    set_restart_up_position(mod);
    return 0;
}

// 0x71020c1690 — bl set_parent_external_stat_bank_handle
u64 FUN_71020c1690(u64 mod) {
    set_parent_external_stat_bank_handle(mod);
    return 0;
}

// 0x71020c3ba0 — bl flash_eye_info
u64 FUN_71020c3ba0(u64 mod) {
    flash_eye_info(mod);
    return 0;
}

// 0x71020c6d60 — bl jump_board_on
u64 FUN_71020c6d60(u64 mod) {
    jump_board_on(mod);
    return 0;
}
