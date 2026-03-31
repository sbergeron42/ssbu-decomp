#include "types.h"
#define VT(m) (*reinterpret_cast<void***>(m))

struct GimmickEvent;

namespace app::lua_bind {

void GimmickEvent__load_from_l2c_table_impl(GimmickEvent* obj,u64 p1) { reinterpret_cast<void(*)(GimmickEvent*,u64)>(VT(obj)[0x38/8])(obj,p1); }

} // namespace app::lua_bind
