#include "types.h"
#define VT(m) (*reinterpret_cast<void***>(m))

struct WeaponShizueFishingrodLinkEventReel;

namespace app::lua_bind {

void WeaponShizueFishingrodLinkEventReel__store_l2c_table_impl(WeaponShizueFishingrodLinkEventReel* ev) { reinterpret_cast<void(*)(WeaponShizueFishingrodLinkEventReel*)>(VT(ev)[0x28/8])(ev); }
void WeaponShizueFishingrodLinkEventReel__load_from_l2c_table_impl(WeaponShizueFishingrodLinkEventReel* obj,u64 p1) { reinterpret_cast<void(*)(WeaponShizueFishingrodLinkEventReel*,u64)>(VT(obj)[0x38/8])(obj,p1); }

} // namespace app::lua_bind
