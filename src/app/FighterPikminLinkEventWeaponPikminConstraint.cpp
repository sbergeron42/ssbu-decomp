#include "types.h"
#define VT(m) (*reinterpret_cast<void***>(m))

struct FighterPikminLinkEventWeaponPikminConstraint;

namespace app::lua_bind {

void FighterPikminLinkEventWeaponPikminConstraint__store_l2c_table_impl(FighterPikminLinkEventWeaponPikminConstraint* ev) { reinterpret_cast<void(*)(FighterPikminLinkEventWeaponPikminConstraint*)>(VT(ev)[0x28/8])(ev); }
void FighterPikminLinkEventWeaponPikminConstraint__load_from_l2c_table_impl(FighterPikminLinkEventWeaponPikminConstraint* obj,u64 p1) { reinterpret_cast<void(*)(FighterPikminLinkEventWeaponPikminConstraint*,u64)>(VT(obj)[0x38/8])(obj,p1); }

} // namespace app::lua_bind
