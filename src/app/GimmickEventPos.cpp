#include "types.h"
struct LargeRet { unsigned long long a, b, c; };
#define VT(m) (*reinterpret_cast<void***>(m))

struct GimmickEventPos;

namespace app::lua_bind {

LargeRet GimmickEventPos__store_l2c_table_impl(GimmickEventPos* ev) { return reinterpret_cast<LargeRet(*)(GimmickEventPos*)>(VT(ev)[0x28/8])(ev); }
void GimmickEventPos__load_from_l2c_table_impl(GimmickEventPos* obj,u64 p1) { reinterpret_cast<void(*)(GimmickEventPos*,u64)>(VT(obj)[0x38/8])(obj,p1); }

} // namespace app::lua_bind
