#include "types.h"
#define VT(m) (*reinterpret_cast<void***>(m))

struct LinkEventFinal;

namespace app::lua_bind {

void LinkEventFinal__load_from_l2c_table_impl(LinkEventFinal* obj,u64 p1) { reinterpret_cast<void(*)(LinkEventFinal*,u64)>(VT(obj)[0x38/8])(obj,p1); }

} // namespace app::lua_bind
