#include "app/BattleObjectModuleAccessor.h"

namespace app::lua_bind {

<<<<<<< HEAD
// 71020ad720 — is_damage_stop (192B)
// stop_module[+8] is back-pointer to accessor. Checks status in [0x47..0x4b] with flag
// 0x2100000f, or status 0xc8/0x149/0x14c; returns work_int(0x11000006) > 0 or tail-calls.
=======
// 71020ad720 — is_damage_stop: check status range, dispatch to work module query
>>>>>>> worker/pool-b
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
bool FighterStopModuleImpl__is_damage_stop_impl(BattleObjectModuleAccessor* a) {
    asm(
        "str x19, [sp, #-0x20]!\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "ldr x19, [x0, #0x90]\n"
        "ldr x8, [x19, #0x8]\n"
        "ldr x0, [x8, #0x40]\n"
        "ldr x8, [x0]\n"
        "ldr x8, [x8, #0x110]\n"
        "blr x8\n"
        "cmp w0, #0xc7\n"
<<<<<<< HEAD
        "b.gt 1f\n"
        "sub w8, w0, #0x47\n"
        "cmp w8, #0x5\n"
        "b.cs 2f\n"
=======
        "b.gt 3f\n"
        "sub w8, w0, #0x47\n"
        "cmp w8, #0x5\n"
        "b.cs 1f\n"
>>>>>>> worker/pool-b
        "ldr x8, [x19, #0x8]\n"
        "ldr x0, [x8, #0x50]\n"
        "ldr x8, [x0]\n"
        "ldr x8, [x8, #0x108]\n"
        "mov w1, #0xf\n"
        "movk w1, #0x2100, lsl #16\n"
        "blr x8\n"
<<<<<<< HEAD
        "tbnz w0, #0x0, 3f\n"
        "2:\n"
=======
        "tbnz w0, #0, 2f\n"
        "1:\n"
>>>>>>> worker/pool-b
        "ldr x8, [x19]\n"
        "ldr x1, [x8, #0xa0]\n"
        "mov x0, x19\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "ldr x19, [sp], #0x20\n"
        "br x1\n"
<<<<<<< HEAD
        "1:\n"
        "cmp w0, #0xc8\n"
        "b.eq 3f\n"
        "cmp w0, #0x149\n"
        "b.eq 3f\n"
        "cmp w0, #0x14c\n"
        "b.ne 2b\n"
        "3:\n"
=======
        "3:\n"
        "cmp w0, #0xc8\n"
        "b.eq 2f\n"
        "cmp w0, #0x149\n"
        "b.eq 2f\n"
        "cmp w0, #0x14c\n"
        "b.ne 1b\n"
        "2:\n"
>>>>>>> worker/pool-b
        "ldr x8, [x19, #0x8]\n"
        "ldr x0, [x8, #0x50]\n"
        "ldr x8, [x0]\n"
        "ldr x8, [x8, #0x98]\n"
        "mov w1, #0x6\n"
        "movk w1, #0x1100, lsl #16\n"
        "blr x8\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "cmp w0, #0x0\n"
        "cset w0, gt\n"
        "ldr x19, [sp], #0x20\n"
        "ret\n"
    );
}
#endif

<<<<<<< HEAD
// 71020ad7e0 — get_damage_stop_frame (176B)
// Same status-check pattern; fallthrough uses vtable[0xc8/8], common path tail-calls via x2.
=======
// 71020ad7e0 — get_damage_stop_frame: same status check, tail call to work module
>>>>>>> worker/pool-b
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void FighterStopModuleImpl__get_damage_stop_frame_impl(BattleObjectModuleAccessor* a) {
    asm(
        "str x19, [sp, #-0x20]!\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "ldr x19, [x0, #0x90]\n"
        "ldr x8, [x19, #0x8]\n"
        "ldr x0, [x8, #0x40]\n"
        "ldr x8, [x0]\n"
        "ldr x8, [x8, #0x110]\n"
        "blr x8\n"
        "cmp w0, #0xc7\n"
<<<<<<< HEAD
        "b.gt 1f\n"
        "sub w8, w0, #0x47\n"
        "cmp w8, #0x5\n"
        "b.cs 2f\n"
=======
        "b.gt 3f\n"
        "sub w8, w0, #0x47\n"
        "cmp w8, #0x5\n"
        "b.cs 1f\n"
>>>>>>> worker/pool-b
        "ldr x8, [x19, #0x8]\n"
        "ldr x0, [x8, #0x50]\n"
        "ldr x8, [x0]\n"
        "ldr x8, [x8, #0x108]\n"
        "mov w1, #0xf\n"
        "movk w1, #0x2100, lsl #16\n"
        "blr x8\n"
<<<<<<< HEAD
        "tbnz w0, #0x0, 3f\n"
        "2:\n"
=======
        "tbnz w0, #0, 2f\n"
        "1:\n"
>>>>>>> worker/pool-b
        "ldr x8, [x19]\n"
        "ldr x1, [x8, #0xc8]\n"
        "mov x0, x19\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "ldr x19, [sp], #0x20\n"
        "br x1\n"
<<<<<<< HEAD
        "1:\n"
        "cmp w0, #0xc8\n"
        "b.eq 3f\n"
        "cmp w0, #0x149\n"
        "b.eq 3f\n"
        "cmp w0, #0x14c\n"
        "b.ne 2b\n"
        "3:\n"
=======
        "3:\n"
        "cmp w0, #0xc8\n"
        "b.eq 2f\n"
        "cmp w0, #0x149\n"
        "b.eq 2f\n"
        "cmp w0, #0x14c\n"
        "b.ne 1b\n"
        "2:\n"
>>>>>>> worker/pool-b
        "ldr x8, [x19, #0x8]\n"
        "ldr x0, [x8, #0x50]\n"
        "mov w1, #0x6\n"
        "movk w1, #0x1100, lsl #16\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "ldr x8, [x0]\n"
        "ldr x2, [x8, #0x98]\n"
        "ldr x19, [sp], #0x20\n"
        "br x2\n"
    );
}
#endif

} // namespace app::lua_bind
