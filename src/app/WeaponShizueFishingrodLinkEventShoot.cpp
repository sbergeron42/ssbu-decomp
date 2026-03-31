#include "types.h"
struct LargeRet { unsigned long long a, b, c; };
#define VT(m) (*reinterpret_cast<void***>(m))

struct WeaponShizueFishingrodLinkEventShoot;

namespace app::lua_bind {

LargeRet WeaponShizueFishingrodLinkEventShoot__store_l2c_table_impl(WeaponShizueFishingrodLinkEventShoot* ev) { return reinterpret_cast<LargeRet(*)(WeaponShizueFishingrodLinkEventShoot*)>(VT(ev)[0x28/8])(ev); }
void WeaponShizueFishingrodLinkEventShoot__load_from_l2c_table_impl(WeaponShizueFishingrodLinkEventShoot* obj,u64 p1) { reinterpret_cast<void(*)(WeaponShizueFishingrodLinkEventShoot*,u64)>(VT(obj)[0x38/8])(obj,p1); }

} // namespace app::lua_bind
