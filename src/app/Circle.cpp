#include "types.h"

struct Circle;
struct LargeRet { u64 a, b, c; };

namespace app::lua_bind {

// 71020f1980 — 480 bytes: reads fields from nested L2C table via adrp globals — won't match
void Circle__load_from_l2c_table_impl(Circle* self, void* table) {
    (void)self; (void)table;
}

// 71020f1b60 — 208 bytes: allocates L2C table + adrp globals — won't match
LargeRet Circle__store_l2c_table_impl(Circle* self) {
    (void)self;
    return {};
}

// 71020f1f20 — 2272 bytes: LargeRet with arg setup — won't match
LargeRet Circle__store_l2c_table_impl_71020f1f20(Circle* self, void* table) {
    (void)self; (void)table;
    return {};
}

} // namespace app::lua_bind
