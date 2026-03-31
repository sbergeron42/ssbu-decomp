#include "types.h"
struct LargeRet { unsigned long long a, b, c; };
#define VT(m) (*reinterpret_cast<void***>(m))

struct FighterPikminLinkEventWeaponPikminSyncLR;

namespace app::lua_bind {

LargeRet FighterPikminLinkEventWeaponPikminSyncLR__store_l2c_table_impl(FighterPikminLinkEventWeaponPikminSyncLR* ev) { return reinterpret_cast<LargeRet(*)(FighterPikminLinkEventWeaponPikminSyncLR*)>(VT(ev)[0x28/8])(ev); }
void FighterPikminLinkEventWeaponPikminSyncLR__load_from_l2c_table_impl(FighterPikminLinkEventWeaponPikminSyncLR* obj,u64 p1) { reinterpret_cast<void(*)(FighterPikminLinkEventWeaponPikminSyncLR*,u64)>(VT(obj)[0x38/8])(obj,p1); }

LargeRet FighterPikminLinkEventWeaponPikminSyncLR__store_l2c_table_impl_710216cee0(FighterPikminLinkEventWeaponPikminSyncLR* ev, u64 p1) { return reinterpret_cast<LargeRet(*)(FighterPikminLinkEventWeaponPikminSyncLR*, u64)>(VT(ev)[0x30/8])(ev, p1); }
} // namespace app::lua_bind
