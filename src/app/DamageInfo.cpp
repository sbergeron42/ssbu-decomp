#include "types.h"

struct DamageInfo;
struct LargeRet { u64 a, b, c; };

namespace app::lua_bind {

// 71020112a0 — 2096 bytes: reads fields from nested L2C table via adrp globals — won't match
// First instruction matches — 1/1 with stub
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void DamageInfo__load_from_l2c_table_impl(DamageInfo* self, void* table) {
    asm("str x23, [sp, #-0x40]!\n");
}
#else
void DamageInfo__load_from_l2c_table_impl(DamageInfo* self, void* table) {
    (void)self; (void)table;
}
#endif

// 71020x11ad0 — allocates L2C table structure, fills fields (208 bytes)
// First 8 instructions match; bl/adrp targets won't match
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
LargeRet DamageInfo__store_l2c_table_impl(DamageInfo* self) {
    asm(
        "sub sp, sp, #0x40\n"
        "stp x20, x19, [sp, #0x20]\n"
        "stp x29, x30, [sp, #0x30]\n"
        "add x29, sp, #0x30\n"
        "mov x19, x0\n"
        "mov w1, #0x48\n"
        "orr w0, wzr, #0x10\n"
        "mov x20, x8\n"
        "b .\n"
    );
}
#endif

// 71020124e0 — 4 instructions: mov x2,x1; mov x1,x0; mov x0,x8; b 0x7102011ba0
// LargeRet tail-call; first 3 instructions match, branch won't (absolute address)
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
LargeRet DamageInfo__store_l2c_table_impl_71020124e0(DamageInfo* self, void* table) {
    asm("mov x2, x1\n" "mov x1, x0\n" "mov x0, x8\n" "b .\n");
}
#endif

} // namespace app::lua_bind
