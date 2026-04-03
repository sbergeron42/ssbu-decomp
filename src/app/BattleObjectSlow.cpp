#include "types.h"

// BattleObjectSlow -- operates on BattleObjectSlow* directly (not accessor)
// These are direct struct field reads, not vtable dispatchers

struct BattleObjectSlow {
    s32 mode;     // +0x0
    f32 rate;     // +0x4
    u8  type;     // +0x8
};

namespace app::lua_bind {

// 7101fca5b0 -- 2 instructions (ldr s0,[x0,#4]; ret)
f32 BattleObjectSlow__rate_impl(BattleObjectSlow* slow) {
    return slow->rate;
}

// 7101fca650 -- 7 instructions (branch on byte field)
bool BattleObjectSlow__is_estimate_impl(BattleObjectSlow* slow) {
    if (slow->type == 0) return true;
    return slow->mode == 0;
}

// 7101fca670 -- 7 instructions (branch on byte field, compare to 2)
bool BattleObjectSlow__is_adjust_impl(BattleObjectSlow* slow) {
    if (slow->type == 0) return true;
    return slow->mode == 2;
}

// 7101fca5c0 -- rate_request_impl (36 instructions): DCL, reads global byte, returns 1.0f/byte
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
f32 BattleObjectSlow__rate_request_impl(BattleObjectSlow* slow) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "adrp x8, DAT_71052c2610\n"
        "ldr x0, [x8, :lo12:DAT_71052c2610]\n"
        "ldrb w8, [x0, #0x40]\n"
        "cbz w8, 0f\n"
        "bl FUN_71014a2cd0\n"
        "b 1f\n"
        "0:\n"
        "adrp x8, DAT_71053134d8\n"
        "add x8, x8, :lo12:DAT_71053134d8\n"
        "ldarb w8, [x8]\n"
        "tbz w8, #0, 2f\n"
        "3:\n"
        "adrp x8, DAT_71052c4189\n"
        "ldrb w0, [x8, :lo12:DAT_71052c4189]\n"
        "1:\n"
        "and w8, w0, #0xff\n"
        "ucvtf s0, w8\n"
        "fmov s1, #1.0\n"
        "fdiv s0, s1, s0\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
        "2:\n"
        "adrp x0, DAT_71053134d8\n"
        "add x0, x0, :lo12:DAT_71053134d8\n"
        "bl FUN_71039c0100\n"
        "cbz w0, 3b\n"
        "bl FUN_71017641a0\n"
        "adrp x0, DAT_7101763de0\n"
        "add x0, x0, :lo12:DAT_7101763de0\n"
        "adrp x1, DAT_71052c4180\n"
        "add x1, x1, :lo12:DAT_71052c4180\n"
        "adrp x2, DAT_7104f16000\n"
        "add x2, x2, :lo12:DAT_7104f16000\n"
        "bl FUN_71000001c0\n"
        "adrp x0, DAT_71053134d8\n"
        "add x0, x0, :lo12:DAT_71053134d8\n"
        "bl FUN_71039c0110\n"
        "b 3b\n"
    );
}
#endif

} // namespace app::lua_bind
