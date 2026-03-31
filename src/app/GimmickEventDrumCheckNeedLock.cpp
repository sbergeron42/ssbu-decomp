#include "types.h"
#define VT(m) (*reinterpret_cast<void***>(m))

struct GimmickEventDrumCheckNeedLock;

namespace app::lua_bind {

void GimmickEventDrumCheckNeedLock__store_l2c_table_impl(GimmickEventDrumCheckNeedLock* ev) { reinterpret_cast<void(*)(GimmickEventDrumCheckNeedLock*)>(VT(ev)[0x28/8])(ev); }
void GimmickEventDrumCheckNeedLock__load_from_l2c_table_impl(GimmickEventDrumCheckNeedLock* obj,u64 p1) { reinterpret_cast<void(*)(GimmickEventDrumCheckNeedLock*,u64)>(VT(obj)[0x38/8])(obj,p1); }

} // namespace app::lua_bind
