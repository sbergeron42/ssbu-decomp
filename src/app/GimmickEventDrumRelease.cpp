#include "types.h"
struct LargeRet { unsigned long long a, b, c; };
#define VT(m) (*reinterpret_cast<void***>(m))

struct GimmickEventDrumRelease;

namespace app::lua_bind {

LargeRet GimmickEventDrumRelease__store_l2c_table_impl(GimmickEventDrumRelease* ev) { return reinterpret_cast<LargeRet(*)(GimmickEventDrumRelease*)>(VT(ev)[0x28/8])(ev); }
void GimmickEventDrumRelease__load_from_l2c_table_impl(GimmickEventDrumRelease* obj,u64 p1) { reinterpret_cast<void(*)(GimmickEventDrumRelease*,u64)>(VT(obj)[0x38/8])(obj,p1); }

LargeRet GimmickEventDrumRelease__store_l2c_table_impl_71020ed100(GimmickEventDrumRelease* ev, u64 p1) { return reinterpret_cast<LargeRet(*)(GimmickEventDrumRelease*, u64)>(VT(ev)[0x30/8])(ev, p1); }
} // namespace app::lua_bind
