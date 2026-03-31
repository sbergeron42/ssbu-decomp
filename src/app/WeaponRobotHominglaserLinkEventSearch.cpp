#include "types.h"
struct LargeRet { unsigned long long a, b, c; };
#define VT(m) (*reinterpret_cast<void***>(m))

struct WeaponRobotHominglaserLinkEventSearch;

namespace app::lua_bind {

LargeRet WeaponRobotHominglaserLinkEventSearch__store_l2c_table_impl(WeaponRobotHominglaserLinkEventSearch* ev) { return reinterpret_cast<LargeRet(*)(WeaponRobotHominglaserLinkEventSearch*)>(VT(ev)[0x28/8])(ev); }
void WeaponRobotHominglaserLinkEventSearch__load_from_l2c_table_impl(WeaponRobotHominglaserLinkEventSearch* obj,u64 p1) { reinterpret_cast<void(*)(WeaponRobotHominglaserLinkEventSearch*,u64)>(VT(obj)[0x38/8])(obj,p1); }

LargeRet WeaponRobotHominglaserLinkEventSearch__store_l2c_table_impl_710217c4b0(WeaponRobotHominglaserLinkEventSearch* ev, u64 p1) { return reinterpret_cast<LargeRet(*)(WeaponRobotHominglaserLinkEventSearch*, u64)>(VT(ev)[0x30/8])(ev, p1); }
} // namespace app::lua_bind
