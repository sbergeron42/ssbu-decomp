#include "types.h"
struct LargeRet { unsigned long long a, b, c; };
#define VT(m) (*reinterpret_cast<void***>(m))

struct GimmickEventTornadoMoveInfo;

namespace app::lua_bind {

LargeRet GimmickEventTornadoMoveInfo__store_l2c_table_impl(GimmickEventTornadoMoveInfo* ev) { return reinterpret_cast<LargeRet(*)(GimmickEventTornadoMoveInfo*)>(VT(ev)[0x28/8])(ev); }
void GimmickEventTornadoMoveInfo__load_from_l2c_table_impl(GimmickEventTornadoMoveInfo* obj,u64 p1) { reinterpret_cast<void(*)(GimmickEventTornadoMoveInfo*,u64)>(VT(obj)[0x38/8])(obj,p1); }

} // namespace app::lua_bind
