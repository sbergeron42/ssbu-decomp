#include "types.h"
struct LargeRet { unsigned long long a, b, c; };
#define VT(m) (*reinterpret_cast<void***>(m))

struct LinkEventMask;

namespace app::lua_bind {

LargeRet LinkEventMask__store_l2c_table_impl(LinkEventMask* ev) { return reinterpret_cast<LargeRet(*)(LinkEventMask*)>(VT(ev)[0x28/8])(ev); }
void LinkEventMask__load_from_l2c_table_impl(LinkEventMask* obj,u64 p1) { reinterpret_cast<void(*)(LinkEventMask*,u64)>(VT(obj)[0x38/8])(obj,p1); }

LargeRet LinkEventMask__store_l2c_table_impl_7102055a50(LinkEventMask* ev, u64 p1) { return reinterpret_cast<LargeRet(*)(LinkEventMask*, u64)>(VT(ev)[0x30/8])(ev, p1); }
} // namespace app::lua_bind
