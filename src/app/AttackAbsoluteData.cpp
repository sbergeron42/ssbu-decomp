#include "types.h"

struct AttackAbsoluteData;
struct LargeRet { u64 a, b, c; };

namespace app::lua_bind {

// 7101febaa0 — 1888 bytes: reads many fields from nested L2C table via adrp globals — won't match
void AttackAbsoluteData__load_from_l2c_table_impl(AttackAbsoluteData* self, void* table) {
    (void)self; (void)table;
}

// 7101fec200 — 208 bytes: allocates L2C table + adrp globals — won't match
LargeRet AttackAbsoluteData__store_l2c_table_impl(AttackAbsoluteData* self) {
    (void)self;
    return {};
}

// 7101fec920 — 192 bytes: LargeRet tail-call rearranges args — won't match
LargeRet AttackAbsoluteData__store_l2c_table_impl_7101fec920(AttackAbsoluteData* self, void* table) {
    (void)self; (void)table;
    return {};
}

} // namespace app::lua_bind
