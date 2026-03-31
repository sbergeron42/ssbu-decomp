#include "types.h"
#define VT(m) (*reinterpret_cast<void***>(m))

struct GimmickEventDrumPos;

namespace app::lua_bind {

void GimmickEventDrumPos__store_l2c_table_impl(GimmickEventDrumPos* ev) { reinterpret_cast<void(*)(GimmickEventDrumPos*)>(VT(ev)[0x28/8])(ev); }
void GimmickEventDrumPos__load_from_l2c_table_impl(GimmickEventDrumPos* obj,u64 p1) { reinterpret_cast<void(*)(GimmickEventDrumPos*,u64)>(VT(obj)[0x38/8])(obj,p1); }

} // namespace app::lua_bind
