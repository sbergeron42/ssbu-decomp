#include "types.h"
struct LargeRet { unsigned long long a, b, c; };
#define VT(m) (*reinterpret_cast<void***>(m))

struct LinkEventLassoHang;

namespace app::lua_bind {

LargeRet LinkEventLassoHang__store_l2c_table_impl(LinkEventLassoHang* ev) { return reinterpret_cast<LargeRet(*)(LinkEventLassoHang*)>(VT(ev)[0x28/8])(ev); }
void LinkEventLassoHang__load_from_l2c_table_impl(LinkEventLassoHang* obj,u64 p1) { reinterpret_cast<void(*)(LinkEventLassoHang*,u64)>(VT(obj)[0x38/8])(obj,p1); }

} // namespace app::lua_bind
