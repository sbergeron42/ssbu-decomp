#include "types.h"
#define VT(m) (*reinterpret_cast<void***>(m))

struct LinkEventCapture;

namespace app::lua_bind {

void LinkEventCapture__store_l2c_table_impl(LinkEventCapture* ev) { reinterpret_cast<void(*)(LinkEventCapture*)>(VT(ev)[0x28/8])(ev); }
void LinkEventCapture__load_from_l2c_table_impl(LinkEventCapture* obj,u64 p1) { reinterpret_cast<void(*)(LinkEventCapture*,u64)>(VT(obj)[0x38/8])(obj,p1); }

} // namespace app::lua_bind
