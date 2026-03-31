#include "types.h"
struct LargeRet { unsigned long long a, b, c; };
#define VT(m) (*reinterpret_cast<void***>(m))

struct FighterPikminLinkEventWeaponPikminSetFloat;

namespace app::lua_bind {

LargeRet FighterPikminLinkEventWeaponPikminSetFloat__store_l2c_table_impl(FighterPikminLinkEventWeaponPikminSetFloat* ev) { return reinterpret_cast<LargeRet(*)(FighterPikminLinkEventWeaponPikminSetFloat*)>(VT(ev)[0x28/8])(ev); }
void FighterPikminLinkEventWeaponPikminSetFloat__load_from_l2c_table_impl(FighterPikminLinkEventWeaponPikminSetFloat* obj,u64 p1) { reinterpret_cast<void(*)(FighterPikminLinkEventWeaponPikminSetFloat*,u64)>(VT(obj)[0x38/8])(obj,p1); }

LargeRet FighterPikminLinkEventWeaponPikminSetFloat__store_l2c_table_impl_7102170bf0(FighterPikminLinkEventWeaponPikminSetFloat* ev, u64 p1) { return reinterpret_cast<LargeRet(*)(FighterPikminLinkEventWeaponPikminSetFloat*, u64)>(VT(ev)[0x30/8])(ev, p1); }
} // namespace app::lua_bind
