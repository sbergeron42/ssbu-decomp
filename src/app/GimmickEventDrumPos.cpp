#include "types.h"
struct LargeRet { unsigned long long a, b, c; };
#define VT(m) (*reinterpret_cast<void***>(m))

struct GimmickEventDrumPos;

namespace app::lua_bind {

LargeRet GimmickEventDrumPos__store_l2c_table_impl(GimmickEventDrumPos* ev) { return reinterpret_cast<LargeRet(*)(GimmickEventDrumPos*)>(VT(ev)[0x28/8])(ev); }
void GimmickEventDrumPos__load_from_l2c_table_impl(GimmickEventDrumPos* obj,u64 p1) { reinterpret_cast<void(*)(GimmickEventDrumPos*,u64)>(VT(obj)[0x38/8])(obj,p1); }

LargeRet GimmickEventDrumPos__store_l2c_table_impl_71020eac10(GimmickEventDrumPos* ev, u64 p1) { return reinterpret_cast<LargeRet(*)(GimmickEventDrumPos*, u64)>(VT(ev)[0x30/8])(ev, p1); }
} // namespace app::lua_bind
