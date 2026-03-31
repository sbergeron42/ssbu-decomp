#include "types.h"
struct LargeRet { unsigned long long a, b, c; };
#define VT(m) (*reinterpret_cast<void***>(m))

struct GimmickEvent;

namespace app::lua_bind {

LargeRet GimmickEvent__store_l2c_table_impl(GimmickEvent* ev) { return reinterpret_cast<LargeRet(*)(GimmickEvent*)>(VT(ev)[0x28/8])(ev); }
void GimmickEvent__load_from_l2c_table_impl(GimmickEvent* obj,u64 p1) { reinterpret_cast<void(*)(GimmickEvent*,u64)>(VT(obj)[0x38/8])(obj,p1); }

LargeRet GimmickEvent__store_l2c_table_impl_71020d4760(GimmickEvent* ev, u64 p1) { return reinterpret_cast<LargeRet(*)(GimmickEvent*, u64)>(VT(ev)[0x30/8])(ev, p1); }
} // namespace app::lua_bind
