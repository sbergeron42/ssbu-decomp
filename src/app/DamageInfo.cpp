#include "types.h"

struct DamageInfo;
struct LargeRet { u64 a, b, c; };

namespace app::lua_bind {

// 71020112a0 — 2096 bytes: reads fields from nested L2C table via adrp globals — won't match
void DamageInfo__load_from_l2c_table_impl(DamageInfo* self, void* table) {
    (void)self; (void)table;
}

// 71020x11ad0 — 208 bytes: allocates L2C table + adrp globals — won't match
LargeRet DamageInfo__store_l2c_table_impl(DamageInfo* self) {
    (void)self;
    return {};
}

// 71020124e0 — 496 bytes: LargeRet with arg setup — won't match
LargeRet DamageInfo__store_l2c_table_impl_71020124e0(DamageInfo* self, void* table) {
    (void)self; (void)table;
    return {};
}

} // namespace app::lua_bind
