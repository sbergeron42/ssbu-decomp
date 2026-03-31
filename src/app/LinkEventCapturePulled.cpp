#include "types.h"
struct LargeRet { unsigned long long a, b, c; };
#define VT(m) (*reinterpret_cast<void***>(m))

struct LinkEventCapturePulled;

namespace app::lua_bind {

LargeRet LinkEventCapturePulled__store_l2c_table_impl(LinkEventCapturePulled* ev) { return reinterpret_cast<LargeRet(*)(LinkEventCapturePulled*)>(VT(ev)[0x28/8])(ev); }
void LinkEventCapturePulled__load_from_l2c_table_impl(LinkEventCapturePulled* obj,u64 p1) { reinterpret_cast<void(*)(LinkEventCapturePulled*,u64)>(VT(obj)[0x38/8])(obj,p1); }

} // namespace app::lua_bind
