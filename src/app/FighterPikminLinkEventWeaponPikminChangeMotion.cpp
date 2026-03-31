#include "types.h"
#define VT(m) (*reinterpret_cast<void***>(m))

struct FighterPikminLinkEventWeaponPikminChangeMotion;

namespace app::lua_bind {

void FighterPikminLinkEventWeaponPikminChangeMotion__store_l2c_table_impl(FighterPikminLinkEventWeaponPikminChangeMotion* ev) { reinterpret_cast<void(*)(FighterPikminLinkEventWeaponPikminChangeMotion*)>(VT(ev)[0x28/8])(ev); }
void FighterPikminLinkEventWeaponPikminChangeMotion__load_from_l2c_table_impl(FighterPikminLinkEventWeaponPikminChangeMotion* obj,u64 p1) { reinterpret_cast<void(*)(FighterPikminLinkEventWeaponPikminChangeMotion*,u64)>(VT(obj)[0x38/8])(obj,p1); }

} // namespace app::lua_bind
