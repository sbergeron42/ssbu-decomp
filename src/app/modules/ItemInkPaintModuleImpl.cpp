#include "app/BattleObjectModuleAccessor.h"

namespace app::lua_bind {

// 71020d1970 -- load ink paint module from +0x198, call vtable[0x250] on sub[0x78],
//   call vtable[0x528] on sub[0xd0], check ret.w!=0, if so set w=1.0 and call vtable[0x240]
// NX clang prologue: sub sp; str x19; stp x29,x30; add x29
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void ItemInkPaintModuleImpl__apply_link_ink_paint_impl(BattleObjectModuleAccessor* accessor) {
    asm(
        "sub sp,sp,#0x30\n"
        "str x19,[sp, #0x10]\n"
        "stp x29,x30,[sp, #0x20]\n"
        "add x29,sp,#0x20\n"
        "ldr x19,[x0, #0x198]\n"
        "ldr x8,[x19, #0x8]\n"
        "ldr x0,[x8, #0x78]\n"
        "ldr x8,[x0]\n"
        "ldr x8,[x8, #0x250]\n"
        "blr x8\n"
        "ldr x8,[x19, #0x8]\n"
        "ldr x0,[x8, #0xd0]\n"
        "ldr x8,[x0]\n"
        "ldr x8,[x8, #0x528]\n"
        "blr x8\n"
        "dup s1,v0.S[3]\n"
        "fcmp s1,#0.0\n"
        "str q0,[sp]\n"
        "b.eq 1f\n"
        "fmov s1,#1.0\n"
        "mov v0.S[3],v1.S[0]\n"
        "str q0,[sp]\n"
        "ldr x8,[x19, #0x8]\n"
        "ldr x0,[x8, #0x78]\n"
        "ldr x8,[x0]\n"
        "ldr x8,[x8, #0x240]\n"
        "mov x1,sp\n"
        "blr x8\n"
        "1:\n"
        "ldp x29,x30,[sp, #0x20]\n"
        "ldr x19,[sp, #0x10]\n"
        "add sp,sp,#0x30\n"
        "ret\n"
    );
}
#endif

} // namespace app::lua_bind
