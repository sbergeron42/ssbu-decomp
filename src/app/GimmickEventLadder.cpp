#include "types.h"
struct LargeRet { unsigned long long a, b, c; };
#define VT(m) (*reinterpret_cast<void***>(m))

struct GimmickEventLadder;

namespace app::lua_bind {

LargeRet GimmickEventLadder__store_l2c_table_impl(GimmickEventLadder* ev) { return reinterpret_cast<LargeRet(*)(GimmickEventLadder*)>(VT(ev)[0x28/8])(ev); }
void GimmickEventLadder__load_from_l2c_table_impl(GimmickEventLadder* obj,u64 p1) { reinterpret_cast<void(*)(GimmickEventLadder*,u64)>(VT(obj)[0x38/8])(obj,p1); }

LargeRet GimmickEventLadder__store_l2c_table_impl_71020e59b0(GimmickEventLadder* ev, u64 p1) { return reinterpret_cast<LargeRet(*)(GimmickEventLadder*, u64)>(VT(ev)[0x30/8])(ev, p1); }
} // namespace app::lua_bind
