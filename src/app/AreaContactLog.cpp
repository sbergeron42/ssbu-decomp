#include "types.h"

struct AreaContactLog;
struct LargeRet { u64 a, b, c; };

namespace app::lua_bind {

// 7101fca860 — reads 8+ fields from nested L2C table (1120 bytes)
// Uses adrp globals at 0x710593a000+0x3a8 and calls 0x7103733d50 — won't match
void AreaContactLog__load_from_l2c_table_impl(AreaContactLog* self, void* table) {
    (void)self; (void)table;
}

// 7101fcacc0 — allocates L2C table structure, fills fields, calls 0x7101fcad90 (208 bytes)
// Uses adrp globals and absolute call targets — won't match
LargeRet AreaContactLog__store_l2c_table_impl(AreaContactLog* self) {
    (void)self;
    return {};
}

// 7101fcb280 — 4 instructions: mov x2,x1; mov x1,x0; mov x0,x8; b 0x7101fcad90
// LargeRet tail-call rearranges args — absolute branch won't match
LargeRet AreaContactLog__store_l2c_table_impl_7101fcb280(AreaContactLog* self, void* table) {
    (void)self; (void)table;
    return {};
}

} // namespace app::lua_bind
