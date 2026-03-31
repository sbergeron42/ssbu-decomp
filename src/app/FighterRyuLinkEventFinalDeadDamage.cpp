#include "types.h"
#define VT(m) (*reinterpret_cast<void***>(m))

struct FighterRyuLinkEventFinalDeadDamage;

namespace app::lua_bind {

void FighterRyuLinkEventFinalDeadDamage__store_l2c_table_impl(FighterRyuLinkEventFinalDeadDamage* ev) { reinterpret_cast<void(*)(FighterRyuLinkEventFinalDeadDamage*)>(VT(ev)[0x28/8])(ev); }
void FighterRyuLinkEventFinalDeadDamage__load_from_l2c_table_impl(FighterRyuLinkEventFinalDeadDamage* obj,u64 p1) { reinterpret_cast<void(*)(FighterRyuLinkEventFinalDeadDamage*,u64)>(VT(obj)[0x38/8])(obj,p1); }

} // namespace app::lua_bind
