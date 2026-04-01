#include "types.h"

struct AttackData;
struct LargeRet { u64 a, b, c; };

namespace app::lua_bind {

// 7101fed120 — 7088 bytes: reads many fields from nested L2C table via adrp globals — won't match
void AttackData__load_from_l2c_table_impl(AttackData* self, void* table) {
    (void)self; (void)table;
}

// 7101feecd0 — 208 bytes: allocates L2C table + adrp globals — won't match
LargeRet AttackData__store_l2c_table_impl(AttackData* self) {
    (void)self;
    return {};
}

// 7101ff0280 — 1152 bytes: LargeRet with arg setup — won't match
LargeRet AttackData__store_l2c_table_impl_7101ff0280(AttackData* self, void* table) {
    (void)self; (void)table;
    return {};
}

} // namespace app::lua_bind
