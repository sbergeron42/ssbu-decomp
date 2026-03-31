#include "types.h"
#define VT(m) (*reinterpret_cast<void***>(m))

struct GimmickEventWarp;

namespace app::lua_bind {

void GimmickEventWarp__store_l2c_table_impl(GimmickEventWarp* ev) { reinterpret_cast<void(*)(GimmickEventWarp*)>(VT(ev)[0x28/8])(ev); }
void GimmickEventWarp__load_from_l2c_table_impl(GimmickEventWarp* obj,u64 p1) { reinterpret_cast<void(*)(GimmickEventWarp*,u64)>(VT(obj)[0x38/8])(obj,p1); }

} // namespace app::lua_bind
