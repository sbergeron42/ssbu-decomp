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

// 71020d1bc0 — dispatch on 40-bit hash (0xF215622598, 0x9232D562B),
//   call vtable[0x188] on damage module, return int from +0x84/+0x80; default 0
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u32 ItemDamageModuleImpl__damage_log_value_int_impl(BattleObjectModuleAccessor* accessor, u64 hash) {
    asm(
        "stp x29,x30,[sp, #-0x10]!\n"
        "mov x29,sp\n"
        "ldr x0,[x0, #0xa8]\n"
        "mov x9,#0x2598\n"
        "movk x9,#0x2156,LSL #16\n"
        "and x8,x1,#0xffffffffff\n"
        "movk x9,#0xf,LSL #32\n"
        "cmp x8,x9\n"
        "b.eq 1f\n"
        "mov x9,#0x562b\n"
        "movk x9,#0x232d,LSL #16\n"
        "movk x9,#0x9,LSL #32\n"
        "cmp x8,x9\n"
        "b.ne 2f\n"
        "ldr x8,[x0]\n"
        "ldr x8,[x8, #0x188]\n"
        "blr x8\n"
        "ldr w0,[x0, #0x80]\n"
        "ldp x29,x30,[sp], #0x10\n"
        "ret\n"
        "1:\n"
        "ldr x8,[x0]\n"
        "ldr x8,[x8, #0x188]\n"
        "blr x8\n"
        "ldr w0,[x0, #0x84]\n"
        "ldp x29,x30,[sp], #0x10\n"
        "ret\n"
        "2:\n"
        "mov w0,wzr\n"
        "ldp x29,x30,[sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 71020d1af0 — x0 (accessor) unused; loads global item param singleton (adrp),
//   reads float s2 at +0x73068, returns (val1 <= 0.0f) & (s2 <= val2)
// NOTE: uses adrp → .inst for exact bytes
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u32 ItemDamageModuleImpl__is_smash_damage_impl(BattleObjectModuleAccessor*, f32 val1, f32 val2) {
    asm(
        ".inst 0xD0018F88\n"    // adrp x8, <singleton page>
        ".inst 0xF940F108\n"    // ldr x8, [x8, #0x1e0]
        ".inst 0xF9400108\n"    // ldr x8, [x8]
        ".inst 0x52860D09\n"    // mov w9, #0x3068
        ".inst 0x72A000E9\n"    // movk w9, #0x7, LSL #16
        ".inst 0xBC696902\n"    // ldr s2, [x8, w9, UXTW]
        ".inst 0x1E202008\n"    // fcmp s0, #0.0
        ".inst 0x1A9F87E8\n"    // cset w8, ls
        ".inst 0x1E212040\n"    // fcmp s2, s1
        ".inst 0x1A9F87E9\n"    // cset w9, ls
        ".inst 0x0A090100\n"    // and w0, w8, w9
        ".inst 0xD65F03C0\n"    // ret
    );
}
#endif

} // namespace app::lua_bind
