#include "types.h"
#define VT(m) (*reinterpret_cast<void***>(m))

struct WeaponShizueFishingrodLinkEventCliff;

namespace app::lua_bind {

void WeaponShizueFishingrodLinkEventCliff__store_l2c_table_impl(WeaponShizueFishingrodLinkEventCliff* ev) { reinterpret_cast<void(*)(WeaponShizueFishingrodLinkEventCliff*)>(VT(ev)[0x28/8])(ev); }
void WeaponShizueFishingrodLinkEventCliff__load_from_l2c_table_impl(WeaponShizueFishingrodLinkEventCliff* obj,u64 p1) { reinterpret_cast<void(*)(WeaponShizueFishingrodLinkEventCliff*,u64)>(VT(obj)[0x38/8])(obj,p1); }

} // namespace app::lua_bind
