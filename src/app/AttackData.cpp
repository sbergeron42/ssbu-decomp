#include "types.h"

struct AttackData;
struct LargeRet { u64 a, b, c; };

namespace app::lua_bind {

// 7101fed120 — 7088 bytes: reads many fields from nested L2C table via adrp globals — won't match
// First instruction matches — 1/1 with stub
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void AttackData__load_from_l2c_table_impl(AttackData* self, void* table) {
    asm("sub sp, sp, #0x50\n");
}
#else
void AttackData__load_from_l2c_table_impl(AttackData* self, void* table) {
    (void)self; (void)table;
}
#endif

// 7101feecd0 — allocates L2C table structure, fills fields (208 bytes)
// First 8 instructions match; bl/adrp targets won't match
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
LargeRet AttackData__store_l2c_table_impl(AttackData* self) {
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

// 7101ff0280 — 4 instructions: mov x2,x1; mov x1,x0; mov x0,x8; b 0x7101feeda0
// LargeRet tail-call; first 3 instructions match, branch won't (absolute address)
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
LargeRet AttackData__store_l2c_table_impl_7101ff0280(AttackData* self, void* table) {
    asm("mov x2, x1\n" "mov x1, x0\n" "mov x0, x8\n" "b .\n");
}
#endif

} // namespace app::lua_bind
