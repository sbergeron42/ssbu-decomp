#include "types.h"
struct LargeRet { unsigned long long a, b, c; };
#define VT(m) (*reinterpret_cast<void***>(m))

struct FighterPikminLinkEventWeaponPikminOnFlag;

namespace app::lua_bind {

LargeRet FighterPikminLinkEventWeaponPikminOnFlag__store_l2c_table_impl(FighterPikminLinkEventWeaponPikminOnFlag* ev) { return reinterpret_cast<LargeRet(*)(FighterPikminLinkEventWeaponPikminOnFlag*)>(VT(ev)[0x28/8])(ev); }
void FighterPikminLinkEventWeaponPikminOnFlag__load_from_l2c_table_impl(FighterPikminLinkEventWeaponPikminOnFlag* obj,u64 p1) { reinterpret_cast<void(*)(FighterPikminLinkEventWeaponPikminOnFlag*,u64)>(VT(obj)[0x38/8])(obj,p1); }

} // namespace app::lua_bind
