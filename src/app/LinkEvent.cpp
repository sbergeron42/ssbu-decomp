#include "types.h"
#define VT(m) (*reinterpret_cast<void***>(m))

struct LinkEvent;

namespace app::lua_bind {

void LinkEvent__store_l2c_table_impl(LinkEvent* ev) { reinterpret_cast<void(*)(LinkEvent*)>(VT(ev)[0x28/8])(ev); }
void LinkEvent__load_from_l2c_table_impl(LinkEvent* obj,u64 p1) { reinterpret_cast<void(*)(LinkEvent*,u64)>(VT(obj)[0x38/8])(obj,p1); }

} // namespace app::lua_bind
