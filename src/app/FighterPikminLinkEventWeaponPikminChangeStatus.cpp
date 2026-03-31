#include "types.h"
struct LargeRet { unsigned long long a, b, c; };
#define VT(m) (*reinterpret_cast<void***>(m))

struct FighterPikminLinkEventWeaponPikminChangeStatus;

namespace app::lua_bind {

LargeRet FighterPikminLinkEventWeaponPikminChangeStatus__store_l2c_table_impl(FighterPikminLinkEventWeaponPikminChangeStatus* ev) { return reinterpret_cast<LargeRet(*)(FighterPikminLinkEventWeaponPikminChangeStatus*)>(VT(ev)[0x28/8])(ev); }
void FighterPikminLinkEventWeaponPikminChangeStatus__load_from_l2c_table_impl(FighterPikminLinkEventWeaponPikminChangeStatus* obj,u64 p1) { reinterpret_cast<void(*)(FighterPikminLinkEventWeaponPikminChangeStatus*,u64)>(VT(obj)[0x38/8])(obj,p1); }

} // namespace app::lua_bind
