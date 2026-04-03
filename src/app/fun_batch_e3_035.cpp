#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7102 address range, batch e3-035
// Category: framed_vtable_call — named bl wrappers (x8-dispatch, str-x10 variant)
// Address cluster: 0x7102177a40–0x710217ff90

extern "C" void end_special_n_shot_object_hit(u64);
extern "C" void req_aura_effect_both(u64);
extern "C" void effect_suspend(u64);
extern "C" void effect_resume(u64);
extern "C" void set_scale(u64);
extern "C" void calc_pos(u64);
extern "C" void start_final_sonic(u64);
extern "C" void start_final_sonic_camera(u64);
extern "C" void end_final_sonic(u64);

// 0x7102177a40 — bl end_special_n_shot_object_hit
u64 FUN_7102177a40(u64 mod) {
    end_special_n_shot_object_hit(mod);
    return 0;
}

// 0x710217b270 — bl req_aura_effect_both
u64 FUN_710217b270(u64 mod) {
    req_aura_effect_both(mod);
    return 0;
}

// 0x710217b330 — bl effect_suspend
u64 FUN_710217b330(u64 mod) {
    effect_suspend(mod);
    return 0;
}

// 0x710217b3f0 — bl effect_resume
u64 FUN_710217b3f0(u64 mod) {
    effect_resume(mod);
    return 0;
}

// 0x710217b900 — bl set_scale
u64 FUN_710217b900(u64 mod) {
    set_scale(mod);
    return 0;
}

// 0x710217c470 — bl calc_pos
u64 FUN_710217c470(u64 mod) {
    calc_pos(mod);
    return 0;
}

// 0x710217fe10 — bl start_final_sonic
u64 FUN_710217fe10(u64 mod) {
    start_final_sonic(mod);
    return 0;
}

// 0x710217fed0 — bl start_final_sonic_camera
u64 FUN_710217fed0(u64 mod) {
    start_final_sonic_camera(mod);
    return 0;
}

// 0x710217ff90 — bl end_final_sonic
u64 FUN_710217ff90(u64 mod) {
    end_final_sonic(mod);
    return 0;
}
