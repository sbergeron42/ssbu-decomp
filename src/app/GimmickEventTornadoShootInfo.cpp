#include "types.h"
struct LargeRet { unsigned long long a, b, c; };
#define VT(m) (*reinterpret_cast<void***>(m))

struct GimmickEventTornadoShootInfo;

namespace app::lua_bind {

LargeRet GimmickEventTornadoShootInfo__store_l2c_table_impl(GimmickEventTornadoShootInfo* ev) { return reinterpret_cast<LargeRet(*)(GimmickEventTornadoShootInfo*)>(VT(ev)[0x28/8])(ev); }
void GimmickEventTornadoShootInfo__load_from_l2c_table_impl(GimmickEventTornadoShootInfo* obj,u64 p1) { reinterpret_cast<void(*)(GimmickEventTornadoShootInfo*,u64)>(VT(obj)[0x38/8])(obj,p1); }

} // namespace app::lua_bind
