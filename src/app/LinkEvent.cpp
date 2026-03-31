#include "types.h"
struct LargeRet { unsigned long long a, b, c; };
#define VT(m) (*reinterpret_cast<void***>(m))

struct LinkEvent;

namespace app::lua_bind {

LargeRet LinkEvent__store_l2c_table_impl(LinkEvent* ev) { return reinterpret_cast<LargeRet(*)(LinkEvent*)>(VT(ev)[0x28/8])(ev); }
void LinkEvent__load_from_l2c_table_impl(LinkEvent* obj,u64 p1) { reinterpret_cast<void(*)(LinkEvent*,u64)>(VT(obj)[0x38/8])(obj,p1); }

LargeRet LinkEvent__store_l2c_table_impl_71020542c0(LinkEvent* ev, u64 p1) { return reinterpret_cast<LargeRet(*)(LinkEvent*, u64)>(VT(ev)[0x30/8])(ev, p1); }
} // namespace app::lua_bind
