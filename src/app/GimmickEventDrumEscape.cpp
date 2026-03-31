#include "types.h"
#define VT(m) (*reinterpret_cast<void***>(m))

struct GimmickEventDrumEscape;

namespace app::lua_bind {

void GimmickEventDrumEscape__load_from_l2c_table_impl(GimmickEventDrumEscape* obj,u64 p1) { reinterpret_cast<void(*)(GimmickEventDrumEscape*,u64)>(VT(obj)[0x38/8])(obj,p1); }

} // namespace app::lua_bind
