#include "types.h"

// FighterEntry -- operates on FighterEntry* directly

struct FighterEntry;

namespace app::lua_bind {

// 71020cbc40 -- fighter_num (2 instructions)
u32 FighterEntry__fighter_num_impl(FighterEntry* entry) {
    return *reinterpret_cast<u32*>(reinterpret_cast<u8*>(entry) + 0x14);
}

// 71020cbc50 -- get_fighter_id: bounds check + optional active check via vtable
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u32 FighterEntry__get_fighter_id_impl(FighterEntry* entry, s32 index, bool check_active) {
    asm("stp x20, x19, [sp, #-0x20]!\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "ldr x9, [x0, #0x4150]\n"
        "sxtw x8, w1\n"
        "mov w19, #0x50000000\n"
        "cmp x9, x8\n"
        "b.ls 0f\n"
        "add x20, x0, x8, lsl #3\n"
        "ldr x0, [x20, #0x4160]\n"
        "cbz x0, 0f\n"
        "tbz w2, #0, 1f\n"
        "ldr x8, [x0]\n"
        "ldr x8, [x8, #0x518]\n"
        "blr x8\n"
        "tbz w0, #0, 0f\n"
        "mov w8, #0x4160\n"
        "add x8, x20, x8\n"
        "ldr x0, [x8]\n"
        "1:\n"
        "ldr w19, [x0, #0x8]\n"
        "0:\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "mov w0, w19\n"
        "ldp x20, x19, [sp], #0x20\n"
        "ret\n");
}
#endif

// 71020cbcb0 -- current_fighter_id: use current index at +0x5918
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u32 FighterEntry__current_fighter_id_impl(FighterEntry* entry) {
    asm("stp x20, x19, [sp, #-0x20]!\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "mov w8, #0x5918\n"
        "ldrb w8, [x0, x8]\n"
        "ldr x9, [x0, #0x4150]\n"
        "mov w19, #0x50000000\n"
        "cmp x9, x8\n"
        "b.ls 0f\n"
        "add x20, x0, x8, lsl #3\n"
        "ldr x0, [x20, #0x4160]\n"
        "cbz x0, 0f\n"
        "ldr x8, [x0]\n"
        "ldr x8, [x8, #0x518]\n"
        "blr x8\n"
        "tbz w0, #0, 0f\n"
        "mov w8, #0x4160\n"
        "add x8, x20, x8\n"
        "ldr x8, [x8]\n"
        "ldr w19, [x8, #0x8]\n"
        "0:\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "mov w0, w19\n"
        "ldp x20, x19, [sp], #0x20\n"
        "ret\n");
}
#endif

// 71020cbd10 -- heal: applies damage to one or all fighters via external function
extern "C" void FUN_71006645d0(f32, u64, bool, s32, u64);
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void FighterEntry__heal_impl(FighterEntry* entry, f32 damage, bool param3, s32 target, u64 hash) {
    asm("str d8, [sp, #-0x50]!\n"
        "str x25, [sp, #0x8]\n"
        "stp x24, x23, [sp, #0x10]\n"
        "stp x22, x21, [sp, #0x20]\n"
        "stp x20, x19, [sp, #0x30]\n"
        "stp x29, x30, [sp, #0x40]\n"
        "add x29, sp, #0x40\n"
        "ldr x22, [x0, #0x4150]\n"
        "mov v8.16b, v0.16b\n"
        "mov x19, x3\n"
        "mov w20, w1\n"
        "mov x21, x0\n"
        "cmp w2, #3\n"
        "b.ne 5f\n"
        // target == 3 loop
        "cbz x22, 9f\n"
        "fneg s8, s8\n"
        "mov x8, xzr\n"
        "orr w23, wzr, #1\n"
        "mov w24, #0x4160\n"
        "3:\n"
        "add x25, x21, x8, lsl #3\n"
        "ldr x0, [x25, #0x4160]\n"
        "cbz x0, 4f\n"
        "ldr x8, [x0]\n"
        "ldr x8, [x8, #0x518]\n"
        "blr x8\n"
        "tbz w0, #0, 4f\n"
        "add x8, x25, x24\n"
        "ldr x0, [x8]\n"
        "mov v0.16b, v8.16b\n"
        "and w1, w20, #1\n"
        "mov w2, wzr\n"
        "mov x3, x19\n"
        "bl FUN_71006645d0\n"
        "4:\n"
        "mov w8, w23\n"
        "add w23, w23, #1\n"
        "cmp x22, x8\n"
        "b.hi 3b\n"
        "b 9f\n"
        // target != 3
        "5:\n"
        "sxtw x8, w2\n"
        "cmp x22, x8\n"
        "b.ls 9f\n"
        "add x21, x21, x8, lsl #3\n"
        "ldr x0, [x21, #0x4160]\n"
        "cbz x0, 9f\n"
        "ldr x8, [x0]\n"
        "ldr x8, [x8, #0x518]\n"
        "blr x8\n"
        "tbz w0, #0, 9f\n"
        "mov w8, #0x4160\n"
        "add x8, x21, x8\n"
        "ldr x0, [x8]\n"
        "and w1, w20, #1\n"
        "mov x3, x19\n"
        "ldr x25, [sp, #0x8]\n"
        "ldp x29, x30, [sp, #0x40]\n"
        "fneg s0, s8\n"
        "ldp x20, x19, [sp, #0x30]\n"
        "mov w2, wzr\n"
        "ldp x22, x21, [sp, #0x20]\n"
        "ldp x24, x23, [sp, #0x10]\n"
        "ldr d8, [sp], #0x50\n"
        "b FUN_71006645d0\n"
        "9:\n"
        "ldp x29, x30, [sp, #0x40]\n"
        "ldr x25, [sp, #0x8]\n"
        "ldp x20, x19, [sp, #0x30]\n"
        "ldp x22, x21, [sp, #0x20]\n"
        "ldp x24, x23, [sp, #0x10]\n"
        "ldr d8, [sp], #0x50\n"
        "ret\n");
}
#endif

// 71020cbe30 -- eat_item: tail call to external function
extern "C" void FUN_710065d530(void*, void*, bool);
void FighterEntry__eat_item_impl(FighterEntry* entry, void* touch_event, bool param3) {
    FUN_710065d530(entry, touch_event, param3);
}

} // namespace app::lua_bind
