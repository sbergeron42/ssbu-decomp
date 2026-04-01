#include "types.h"

struct DamageLog;
struct LargeRet { u64 a, b, c; };

namespace app::lua_bind {

// 7102013080 — 4896 bytes: reads many fields from nested L2C table via adrp globals — won't match
void DamageLog__load_from_l2c_table_impl(DamageLog* self, void* table) {
    (void)self; (void)table;
}

// 71020143a0 — 208 bytes: allocates L2C table + adrp globals — won't match
LargeRet DamageLog__store_l2c_table_impl(DamageLog* self) {
    (void)self;
    return {};
}

// 7102015430 — 8080 bytes: LargeRet with large arg setup — won't match
LargeRet DamageLog__store_l2c_table_impl_7102015430(DamageLog* self, void* table) {
    (void)self; (void)table;
    return {};
}

} // namespace app::lua_bind
