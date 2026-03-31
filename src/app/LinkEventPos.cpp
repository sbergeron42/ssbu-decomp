#include "types.h"
struct LargeRet { unsigned long long a, b, c; };
#define VT(m) (*reinterpret_cast<void***>(m))

struct LinkEventPos;

namespace app::lua_bind {

LargeRet LinkEventPos__store_l2c_table_impl(LinkEventPos* ev) { return reinterpret_cast<LargeRet(*)(LinkEventPos*)>(VT(ev)[0x28/8])(ev); }
void LinkEventPos__load_from_l2c_table_impl(LinkEventPos* obj,u64 p1) { reinterpret_cast<void(*)(LinkEventPos*,u64)>(VT(obj)[0x38/8])(obj,p1); }

} // namespace app::lua_bind
