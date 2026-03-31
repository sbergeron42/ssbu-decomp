#include "types.h"
struct LargeRet { unsigned long long a, b, c; };
#define VT(m) (*reinterpret_cast<void***>(m))

struct GimmickEventTornadoEscape;

namespace app::lua_bind {

LargeRet GimmickEventTornadoEscape__store_l2c_table_impl(GimmickEventTornadoEscape* ev) { return reinterpret_cast<LargeRet(*)(GimmickEventTornadoEscape*)>(VT(ev)[0x28/8])(ev); }
void GimmickEventTornadoEscape__load_from_l2c_table_impl(GimmickEventTornadoEscape* obj,u64 p1) { reinterpret_cast<void(*)(GimmickEventTornadoEscape*,u64)>(VT(obj)[0x38/8])(obj,p1); }

} // namespace app::lua_bind
