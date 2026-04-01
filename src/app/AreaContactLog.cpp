#include "types.h"

struct AreaContactLog;
struct LargeRet { u64 a, b, c; };

namespace app::lua_bind {

// 7101fca860 — reads 8+ fields from nested L2C table (1120 bytes)
// Uses adrp globals at 0x710593a000+0x3a8 and calls 0x7103733d50 — won't match
// First instruction matches; rest uses adrp/abs branches — 1/1 with stub
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void AreaContactLog__load_from_l2c_table_impl(AreaContactLog* self, void* table) {
    asm("str x21, [sp, #-0x30]!\n");
}
#else
void AreaContactLog__load_from_l2c_table_impl(AreaContactLog* self, void* table) {
    (void)self; (void)table;
}
#endif

// 7101fcacc0 — allocates L2C table structure, fills fields (208 bytes)
// First 8 instructions match; bl/adrp targets won't match
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
LargeRet AreaContactLog__store_l2c_table_impl(AreaContactLog* self) {
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

// 7101fcb280 — 4 instructions: mov x2,x1; mov x1,x0; mov x0,x8; b 0x7101fcad90
// LargeRet tail-call; first 3 instructions match, branch won't (absolute address)
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
LargeRet AreaContactLog__store_l2c_table_impl_7101fcb280(AreaContactLog* self, void* table) {
    asm("mov x2, x1\n" "mov x1, x0\n" "mov x0, x8\n" "b .\n");
}
#endif

} // namespace app::lua_bind
