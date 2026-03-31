#include "app/BattleObjectModuleAccessor.h"

#define VT(p) (*reinterpret_cast<void***>(p))

namespace app::lua_bind {

// 71020d1b20 — dispatch on 40-bit hash (0x2369A2644, 0xEE085517C, 0xAC3A7D97E),
//   call vtable[0x188] on damage module, return float from +0x44/+0x48/+0x58
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
f32 ItemDamageModuleImpl__damage_log_value_float_impl(BattleObjectModuleAccessor* accessor, u64 hash) {
    asm(
        "stp x29,x30,[sp, #-0x10]!\n"
        "mov x29,sp\n"
        "ldr x0,[x0, #0xa8]\n"
        "mov x9,#0x2644\n"
        "movk x9,#0x369a,LSL #16\n"
        "and x8,x1,#0xffffffffff\n"
        "movk x9,#0x2,LSL #32\n"
        "cmp x8,x9\n"
        "b.eq 1f\n"
        "mov x9,#0x517c\n"
        "movk x9,#0xe085,LSL #16\n"
        "movk x9,#0xe,LSL #32\n"
        "cmp x8,x9\n"
        "b.eq 2f\n"
        "mov x9,#0xd97e\n"
        "movk x9,#0xc3a7,LSL #16\n"
        "movk x9,#0xa,LSL #32\n"
        "cmp x8,x9\n"
        "b.ne 3f\n"
        "ldr x8,[x0]\n"
        "ldr x8,[x8, #0x188]\n"
        "blr x8\n"
        "ldr s0,[x0, #0x58]\n"
        "ldp x29,x30,[sp], #0x10\n"
        "ret\n"
        "1:\n"
        "ldr x8,[x0]\n"
        "ldr x8,[x8, #0x188]\n"
        "blr x8\n"
        "ldr s0,[x0, #0x44]\n"
        "ldp x29,x30,[sp], #0x10\n"
        "ret\n"
        "2:\n"
        "ldr x8,[x0]\n"
        "ldr x8,[x8, #0x188]\n"
        "blr x8\n"
        "ldr s0,[x0, #0x48]\n"
        "ldp x29,x30,[sp], #0x10\n"
        "ret\n"
        "3:\n"
        "fmov s0,wzr\n"
        "ldp x29,x30,[sp], #0x10\n"
        "ret\n"
    );
}
#endif

} // namespace app::lua_bind
