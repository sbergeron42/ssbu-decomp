#include "types.h"

// BattleObjectWorld -- operates on BattleObjectWorld* directly
// Simple struct field reads

struct BattleObjectWorld;

namespace app::lua_bind {

// 7101fca1f0 -- 2 instructions
f32 BattleObjectWorld__gravity_speed_coefficient_impl(BattleObjectWorld* world) {
    return *reinterpret_cast<f32*>(reinterpret_cast<u8*>(world) + 0x4);
}

// 7101fca2d0 -- 2 instructions
bool BattleObjectWorld__is_move_impl(BattleObjectWorld* world) {
    return *reinterpret_cast<bool*>(reinterpret_cast<u8*>(world) + 0x5a);
}

// 7101fca2e0 -- 2 instructions (returns pointer to +0x20)
void* BattleObjectWorld__move_speed_impl(BattleObjectWorld* world) {
    return reinterpret_cast<u8*>(world) + 0x20;
}

// 7101fca2f0 -- 2 instructions
bool BattleObjectWorld__is_disable_reverse_impl(BattleObjectWorld* world) {
    return *reinterpret_cast<bool*>(reinterpret_cast<u8*>(world) + 0x5d);
}

// 7101fca200 -- scale_z (5 instructions, branch)
f32 BattleObjectWorld__scale_z_impl(BattleObjectWorld* world) {
    auto* p = reinterpret_cast<u8*>(world);
    if (p[0xc]) return 1.0f;
    return *reinterpret_cast<f32*>(p + 0x8);
}

// 7101fca2b0 -- is_gravity_normal (8 instructions, branch)
bool BattleObjectWorld__is_gravity_normal_impl(BattleObjectWorld* world) {
    auto* p = reinterpret_cast<u8*>(world);
    if (p[0x5c]) return true;
    return p[0x59] != 0;
}

// 7101fca220 -- gravity_pos_impl (34 instructions): DCL zero-vec singleton
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void* BattleObjectWorld__gravity_pos_impl(BattleObjectWorld* world) {
    asm(
        "str x19, [sp, #-0x20]!\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "ldrb w8, [x0, #0x5c]\n"
        "cbz w8, 0f\n"
        "adrp x8, DAT_71052b7608\n"
        "add x8, x8, :lo12:DAT_71052b7608\n"
        "ldarb w8, [x8]\n"
        "tbz w8, #0, 1f\n"
        "adrp x0, DAT_71052b7610\n"
        "add x0, x0, :lo12:DAT_71052b7610\n"
        "b 2f\n"
        "0:\n"
        "add x0, x0, #0x10\n"
        "2:\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "ldr x19, [sp], #0x20\n"
        "ret\n"
        "1:\n"
        "adrp x0, DAT_71052b7608\n"
        "add x0, x0, :lo12:DAT_71052b7608\n"
        "bl FUN_71039c0100\n"
        "adrp x8, DAT_71052b7610\n"
        "add x8, x8, :lo12:DAT_71052b7610\n"
        "cbz w0, 3f\n"
        "adrp x9, DAT_71052a7a80\n"
        "ldr x9, [x9, :lo12:DAT_71052a7a80]\n"
        "ldr q0, [x9]\n"
        "adrp x0, DAT_71052b7608\n"
        "add x0, x0, :lo12:DAT_71052b7608\n"
        "mov x19, x8\n"
        "str q0, [x8]\n"
        "bl FUN_71039c0110\n"
        "mov x0, x19\n"
        "b 2b\n"
        "3:\n"
        "mov x0, x8\n"
        "b 2b\n"
    );
}
#endif

} // namespace app::lua_bind
