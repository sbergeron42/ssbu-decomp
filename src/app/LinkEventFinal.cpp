#include "types.h"
struct LargeRet { unsigned long long a, b, c; };
#define VT(m) (*reinterpret_cast<void***>(m))

struct LinkEventFinal;

namespace app::lua_bind {

LargeRet LinkEventFinal__store_l2c_table_impl(LinkEventFinal* ev) { return reinterpret_cast<LargeRet(*)(LinkEventFinal*)>(VT(ev)[0x28/8])(ev); }
void LinkEventFinal__load_from_l2c_table_impl(LinkEventFinal* obj,u64 p1) { reinterpret_cast<void(*)(LinkEventFinal*,u64)>(VT(obj)[0x38/8])(obj,p1); }

LargeRet LinkEventFinal__store_l2c_table_impl_71020b1940(LinkEventFinal* ev, u64 p1) { return reinterpret_cast<LargeRet(*)(LinkEventFinal*, u64)>(VT(ev)[0x30/8])(ev, p1); }
} // namespace app::lua_bind
