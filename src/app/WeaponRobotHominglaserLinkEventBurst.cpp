#include "types.h"
#define VT(m) (*reinterpret_cast<void***>(m))

struct WeaponRobotHominglaserLinkEventBurst;

namespace app::lua_bind {

void WeaponRobotHominglaserLinkEventBurst__store_l2c_table_impl(WeaponRobotHominglaserLinkEventBurst* ev) { reinterpret_cast<void(*)(WeaponRobotHominglaserLinkEventBurst*)>(VT(ev)[0x28/8])(ev); }
void WeaponRobotHominglaserLinkEventBurst__load_from_l2c_table_impl(WeaponRobotHominglaserLinkEventBurst* obj,u64 p1) { reinterpret_cast<void(*)(WeaponRobotHominglaserLinkEventBurst*,u64)>(VT(obj)[0x38/8])(obj,p1); }

} // namespace app::lua_bind
