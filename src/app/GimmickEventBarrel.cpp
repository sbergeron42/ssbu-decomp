#include "types.h"
#define VT(m) (*reinterpret_cast<void***>(m))

struct GimmickEventBarrel;

namespace app::lua_bind {

void GimmickEventBarrel__store_l2c_table_impl(GimmickEventBarrel* ev) { reinterpret_cast<void(*)(GimmickEventBarrel*)>(VT(ev)[0x28/8])(ev); }
void GimmickEventBarrel__load_from_l2c_table_impl(GimmickEventBarrel* obj,u64 p1) { reinterpret_cast<void(*)(GimmickEventBarrel*,u64)>(VT(obj)[0x38/8])(obj,p1); }

} // namespace app::lua_bind
