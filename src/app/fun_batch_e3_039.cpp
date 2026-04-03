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
u64 FUN_71021f72f0(u64 mod) {
    FUN_71015c0410(mod);
    return 0;
}

// 0x71021ff030 — bl apply_powerup_throw
u64 FUN_71021ff030(u64 mod) {
    apply_powerup_throw(mod);
    return 0;
}

// 0x71021ff1c0 — bl apply_powerup_etc
u64 FUN_71021ff1c0(u64 mod) {
    apply_powerup_etc(mod);
    return 0;
}

// 0x71021ff230 — bl apply_powerup_attr
u64 FUN_71021ff230(u64 mod) {
    apply_powerup_attr(mod);
    return 0;
}

// 0x7102208d00 — bl send_event_on_boss_dead
u64 FUN_7102208d00(u64 mod) {
    send_event_on_boss_dead(mod);
    return 0;
}

// 0x710220bf50 — bl disable_ground_collision
u64 FUN_710220bf50(u64 mod) {
    disable_ground_collision(mod);
    return 0;
}

// 0x710220c280 — bl del_cursor
u64 FUN_710220c280(u64 mod) {
    del_cursor(mod);
    return 0;
}

// 0x710220c2a0 — bl clear_owner_color
u64 FUN_710220c2a0(u64 mod) {
    clear_owner_color(mod);
    return 0;
}
