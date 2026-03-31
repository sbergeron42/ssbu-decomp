#include "types.h"
struct LargeRet { unsigned long long a, b, c; };
#define VT(m) (*reinterpret_cast<void***>(m))

struct LinkEventStarShot;

namespace app::lua_bind {

LargeRet LinkEventStarShot__store_l2c_table_impl(LinkEventStarShot* ev) { return reinterpret_cast<LargeRet(*)(LinkEventStarShot*)>(VT(ev)[0x28/8])(ev); }
void LinkEventStarShot__load_from_l2c_table_impl(LinkEventStarShot* obj,u64 p1) { reinterpret_cast<void(*)(LinkEventStarShot*,u64)>(VT(obj)[0x38/8])(obj,p1); }

LargeRet LinkEventStarShot__store_l2c_table_impl_71020b38c0(LinkEventStarShot* ev, u64 p1) { return reinterpret_cast<LargeRet(*)(LinkEventStarShot*, u64)>(VT(ev)[0x30/8])(ev, p1); }
} // namespace app::lua_bind
