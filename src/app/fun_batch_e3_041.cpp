#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7102 address range, batch e3-041
// Category: framed_vtable_call — named bl wrappers (mixed 10-insn and 6-insn variants)
// Address cluster: 0x7102247940–0x710226e0c0

extern "C" void shoot_7101675670(u64);
extern "C" void start_item_capture(u64);
extern "C" void set_attack_offset_back_line_z(u64);
extern "C" void heal_fighters(u64);
extern "C" void set_clatter(u64);
extern "C" void set_reflector(u64);
extern "C" void set_shield_7101646010(u64);
extern "C" void FUN_710160dea0(u64);
extern "C" void set_all_shield(u64);
extern "C" void set_bullet_shield(u64);
extern "C" void set_reflector_710164c830(u64);
extern "C" void set_captured_fighter_visibility_and_hit(u64);
extern "C" void set_all_shield_710164ef40(u64);
extern "C" void set_bullet_shield_710164f550(u64);
extern "C" void set_all_shield_710164e100(u64);
extern "C" void set_bullet_shield_710164e710(u64);
extern "C" void set_grab(u64);
extern "C" void notify_melee_start_to_hud_manager(u64);
extern "C" void update_collision_work(u64);
extern "C" void set_material_visibility_mesh_all_invisible(u64);
extern "C" void check_range_from_onwer(u64);
extern "C" void update_blink(u64);

// 0x7102247940 — bl shoot (0x7101675670)
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_7102247940(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl shoot_7101675670\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x7102247af0 — bl start_item_capture
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_7102247af0(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl start_item_capture\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x7102247ca0 — bl set_attack_offset_back_line_z
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_7102247ca0(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl set_attack_offset_back_line_z\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x7102247d60 — bl heal_fighters
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_7102247d60(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl heal_fighters\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x71022499b0 — bl set_clatter
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71022499b0(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl set_clatter\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x7102249a70 — bl set_reflector
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_7102249a70(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl set_reflector\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x7102249b30 — bl set_shield (0x7101646010)
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_7102249b30(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl set_shield_7101646010\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x710224b5e0 — bl FUN_710160dea0
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_710224b5e0(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "bl FUN_710160dea0\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x710224c3d0 — bl set_all_shield
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_710224c3d0(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl set_all_shield\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x710224c490 — bl set_bullet_shield
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_710224c490(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl set_bullet_shield\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x710224d760 — bl set_reflector (0x710164c830)
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_710224d760(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl set_reflector_710164c830\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x710224e230 — bl set_captured_fighter_visibility_and_hit
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_710224e230(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl set_captured_fighter_visibility_and_hit\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x7102251380 — bl FUN_710160dea0
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_7102251380(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "bl FUN_710160dea0\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x7102252e00 — bl set_all_shield (0x710164ef40)
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_7102252e00(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl set_all_shield_710164ef40\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x7102252ec0 — bl set_bullet_shield (0x710164f550)
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_7102252ec0(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl set_bullet_shield_710164f550\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x7102254220 — bl set_all_shield (0x710164e100)
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_7102254220(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl set_all_shield_710164e100\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x71022542e0 — bl set_bullet_shield (0x710164e710)
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71022542e0(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl set_bullet_shield_710164e710\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x7102256790 — bl set_grab
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_7102256790(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl set_grab\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x7102256b00 — bl notify_melee_start_to_hud_manager
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_7102256b00(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "bl notify_melee_start_to_hud_manager\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x7102258b60 — bl FUN_710160dea0
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_7102258b60(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "bl FUN_710160dea0\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x710226d400 — bl update_collision_work
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_710226d400(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl update_collision_work\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x710226d4c0 — bl set_material_visibility_mesh_all_invisible
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_710226d4c0(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl set_material_visibility_mesh_all_invisible\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x710226e000 — bl check_range_from_onwer
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_710226e000(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl check_range_from_onwer\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 0x710226e0c0 — bl update_blink
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_710226e0c0(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "mov x0, x8\n"
        "bl update_blink\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif
