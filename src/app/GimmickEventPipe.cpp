#include "types.h"
struct LargeRet { unsigned long long a, b, c; };
#define VT(m) (*reinterpret_cast<void***>(m))

struct GimmickEventPipe;

namespace app::lua_bind {

LargeRet GimmickEventPipe__store_l2c_table_impl(GimmickEventPipe* ev) { return reinterpret_cast<LargeRet(*)(GimmickEventPipe*)>(VT(ev)[0x28/8])(ev); }
void GimmickEventPipe__load_from_l2c_table_impl(GimmickEventPipe* obj,u64 p1) { reinterpret_cast<void(*)(GimmickEventPipe*,u64)>(VT(obj)[0x38/8])(obj,p1); }

LargeRet GimmickEventPipe__store_l2c_table_impl_71020df7b0(GimmickEventPipe* ev, u64 p1) { return reinterpret_cast<LargeRet(*)(GimmickEventPipe*, u64)>(VT(ev)[0x30/8])(ev, p1); }
} // namespace app::lua_bind
