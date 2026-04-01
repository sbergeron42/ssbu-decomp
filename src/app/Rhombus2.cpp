#include "types.h"

struct Rhombus2;
struct LargeRet { u64 a, b, c; };

namespace app::lua_bind {

// 71020f0250 — 1280 bytes: reads fields from nested L2C table via adrp globals — won't match
void Rhombus2__load_from_l2c_table_impl(Rhombus2* self, void* table) {
    (void)self; (void)table;
}

// 71020f0750 — 208 bytes: allocates L2C table + adrp globals — won't match
LargeRet Rhombus2__store_l2c_table_impl(Rhombus2* self) {
    (void)self;
    return {};
}

// 71020f0eb0 — 2576 bytes: LargeRet with arg setup — won't match
LargeRet Rhombus2__store_l2c_table_impl_71020f0eb0(Rhombus2* self, void* table) {
    (void)self; (void)table;
    return {};
}

} // namespace app::lua_bind
