#include "types.h"
#define VT(m) (*reinterpret_cast<void***>(m))

struct FighterPikminLinkEventWeaponPikminSetFloat;

namespace app::lua_bind {

void FighterPikminLinkEventWeaponPikminSetFloat__store_l2c_table_impl(FighterPikminLinkEventWeaponPikminSetFloat* ev) { reinterpret_cast<void(*)(FighterPikminLinkEventWeaponPikminSetFloat*)>(VT(ev)[0x28/8])(ev); }
void FighterPikminLinkEventWeaponPikminSetFloat__load_from_l2c_table_impl(FighterPikminLinkEventWeaponPikminSetFloat* obj,u64 p1) { reinterpret_cast<void(*)(FighterPikminLinkEventWeaponPikminSetFloat*,u64)>(VT(obj)[0x38/8])(obj,p1); }

} // namespace app::lua_bind
