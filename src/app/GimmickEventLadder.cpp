#include "types.h"
#define VT(m) (*reinterpret_cast<void***>(m))

struct GimmickEventLadder;

namespace app::lua_bind {

void GimmickEventLadder__store_l2c_table_impl(GimmickEventLadder* ev) { reinterpret_cast<void(*)(GimmickEventLadder*)>(VT(ev)[0x28/8])(ev); }
void GimmickEventLadder__load_from_l2c_table_impl(GimmickEventLadder* obj,u64 p1) { reinterpret_cast<void(*)(GimmickEventLadder*,u64)>(VT(obj)[0x38/8])(obj,p1); }

} // namespace app::lua_bind
