#include "types.h"
struct LargeRet { unsigned long long a, b, c; };
#define VT(m) (*reinterpret_cast<void***>(m))

struct FighterPikminLinkEventWeaponPikminSetPowerMulStatus;

namespace app::lua_bind {

LargeRet FighterPikminLinkEventWeaponPikminSetPowerMulStatus__store_l2c_table_impl(FighterPikminLinkEventWeaponPikminSetPowerMulStatus* ev) { return reinterpret_cast<LargeRet(*)(FighterPikminLinkEventWeaponPikminSetPowerMulStatus*)>(VT(ev)[0x28/8])(ev); }
void FighterPikminLinkEventWeaponPikminSetPowerMulStatus__load_from_l2c_table_impl(FighterPikminLinkEventWeaponPikminSetPowerMulStatus* obj,u64 p1) { reinterpret_cast<void(*)(FighterPikminLinkEventWeaponPikminSetPowerMulStatus*,u64)>(VT(obj)[0x38/8])(obj,p1); }

} // namespace app::lua_bind
