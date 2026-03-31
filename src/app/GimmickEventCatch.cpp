#include "types.h"
struct LargeRet { unsigned long long a, b, c; };
#define VT(m) (*reinterpret_cast<void***>(m))

struct GimmickEventCatch;

namespace app::lua_bind {

LargeRet GimmickEventCatch__store_l2c_table_impl(GimmickEventCatch* ev) { return reinterpret_cast<LargeRet(*)(GimmickEventCatch*)>(VT(ev)[0x28/8])(ev); }
void GimmickEventCatch__load_from_l2c_table_impl(GimmickEventCatch* obj,u64 p1) { reinterpret_cast<void(*)(GimmickEventCatch*,u64)>(VT(obj)[0x38/8])(obj,p1); }

} // namespace app::lua_bind
