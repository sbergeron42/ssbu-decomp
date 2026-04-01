#include "types.h"

// Forward declarations
struct BattleObjectManager;

extern "C" void* get_battle_object_from_id(u32 id);

namespace app::lua_bind {

// 7101fca0b0 — 19 instructions (calls, branches, tbz, cset)
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
bool BattleObjectManager__is_active_find_battle_object_impl(BattleObjectManager* mgr, u32 id) {
    asm("str x19, [sp, #-0x20]!\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "mov w0, w1\n"
        "bl get_battle_object_from_id\n"
        "cbz x0, 0f\n"
        "ldr x8, [x0]\n"
        "ldr x8, [x8]\n"
        "mov x19, x0\n"
        "blr x8\n"
        "tbz w0, #0, 1f\n"
        "mov w0, wzr\n"
        "b 0f\n"
        "1:\n"
        "ldrb w8, [x19, #0x3a]\n"
        "cmp w8, #3\n"
        "cset w0, hi\n"
        "0:\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "ldr x19, [sp], #0x20\n"
        "ret\n");
}
#endif

} // namespace app::lua_bind
