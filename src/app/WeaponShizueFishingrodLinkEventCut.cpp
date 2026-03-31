#include "types.h"
#define VT(m) (*reinterpret_cast<void***>(m))

struct WeaponShizueFishingrodLinkEventCut;

namespace app::lua_bind {

void WeaponShizueFishingrodLinkEventCut__store_l2c_table_impl(WeaponShizueFishingrodLinkEventCut* ev) { reinterpret_cast<void(*)(WeaponShizueFishingrodLinkEventCut*)>(VT(ev)[0x28/8])(ev); }
void WeaponShizueFishingrodLinkEventCut__load_from_l2c_table_impl(WeaponShizueFishingrodLinkEventCut* obj,u64 p1) { reinterpret_cast<void(*)(WeaponShizueFishingrodLinkEventCut*,u64)>(VT(obj)[0x38/8])(obj,p1); }

} // namespace app::lua_bind
