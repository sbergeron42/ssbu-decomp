#include "types.h"
struct LargeRet { unsigned long long a, b, c; };
#define VT(m) (*reinterpret_cast<void***>(m))

struct GimmickEventBarrel;

namespace app::lua_bind {

LargeRet GimmickEventBarrel__store_l2c_table_impl(GimmickEventBarrel* ev) { return reinterpret_cast<LargeRet(*)(GimmickEventBarrel*)>(VT(ev)[0x28/8])(ev); }
void GimmickEventBarrel__load_from_l2c_table_impl(GimmickEventBarrel* obj,u64 p1) { reinterpret_cast<void(*)(GimmickEventBarrel*,u64)>(VT(obj)[0x38/8])(obj,p1); }

LargeRet GimmickEventBarrel__store_l2c_table_impl_71020d8070(GimmickEventBarrel* ev, u64 p1) { return reinterpret_cast<LargeRet(*)(GimmickEventBarrel*, u64)>(VT(ev)[0x30/8])(ev, p1); }
} // namespace app::lua_bind
