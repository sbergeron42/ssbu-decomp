#include "types.h"
struct LargeRet { unsigned long long a, b, c; };
#define VT(m) (*reinterpret_cast<void***>(m))

struct FighterPikminLinkEventWeaponPikminSetInt;

namespace app::lua_bind {

LargeRet FighterPikminLinkEventWeaponPikminSetInt__store_l2c_table_impl(FighterPikminLinkEventWeaponPikminSetInt* ev) { return reinterpret_cast<LargeRet(*)(FighterPikminLinkEventWeaponPikminSetInt*)>(VT(ev)[0x28/8])(ev); }
void FighterPikminLinkEventWeaponPikminSetInt__load_from_l2c_table_impl(FighterPikminLinkEventWeaponPikminSetInt* obj,u64 p1) { reinterpret_cast<void(*)(FighterPikminLinkEventWeaponPikminSetInt*,u64)>(VT(obj)[0x38/8])(obj,p1); }

LargeRet FighterPikminLinkEventWeaponPikminSetInt__store_l2c_table_impl_710216fef0(FighterPikminLinkEventWeaponPikminSetInt* ev, u64 p1) { return reinterpret_cast<LargeRet(*)(FighterPikminLinkEventWeaponPikminSetInt*, u64)>(VT(ev)[0x30/8])(ev, p1); }
} // namespace app::lua_bind
