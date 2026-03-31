#include "types.h"
struct LargeRet { unsigned long long a, b, c; };
#define VT(m) (*reinterpret_cast<void***>(m))

struct GimmickEventSpring;

namespace app::lua_bind {

LargeRet GimmickEventSpring__store_l2c_table_impl(GimmickEventSpring* ev) { return reinterpret_cast<LargeRet(*)(GimmickEventSpring*)>(VT(ev)[0x28/8])(ev); }
void GimmickEventSpring__load_from_l2c_table_impl(GimmickEventSpring* obj,u64 p1) { reinterpret_cast<void(*)(GimmickEventSpring*,u64)>(VT(obj)[0x38/8])(obj,p1); }

LargeRet GimmickEventSpring__store_l2c_table_impl_71020dcfc0(GimmickEventSpring* ev, u64 p1) { return reinterpret_cast<LargeRet(*)(GimmickEventSpring*, u64)>(VT(ev)[0x30/8])(ev, p1); }
} // namespace app::lua_bind
