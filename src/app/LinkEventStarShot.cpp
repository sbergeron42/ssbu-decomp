#include "types.h"
#define VT(m) (*reinterpret_cast<void***>(m))

struct LinkEventStarShot;

namespace app::lua_bind {

void LinkEventStarShot__load_from_l2c_table_impl(LinkEventStarShot* obj,u64 p1) { reinterpret_cast<void(*)(LinkEventStarShot*,u64)>(VT(obj)[0x38/8])(obj,p1); }

} // namespace app::lua_bind
