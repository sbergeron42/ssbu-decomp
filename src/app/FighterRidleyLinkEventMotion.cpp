#include "types.h"
struct LargeRet { unsigned long long a, b, c; };
#define VT(m) (*reinterpret_cast<void***>(m))

struct FighterRidleyLinkEventMotion;

namespace app::lua_bind {

LargeRet FighterRidleyLinkEventMotion__store_l2c_table_impl(FighterRidleyLinkEventMotion* ev) { return reinterpret_cast<LargeRet(*)(FighterRidleyLinkEventMotion*)>(VT(ev)[0x28/8])(ev); }
void FighterRidleyLinkEventMotion__load_from_l2c_table_impl(FighterRidleyLinkEventMotion* obj,u64 p1) { reinterpret_cast<void(*)(FighterRidleyLinkEventMotion*,u64)>(VT(obj)[0x38/8])(obj,p1); }

LargeRet FighterRidleyLinkEventMotion__store_l2c_table_impl_71021aa550(FighterRidleyLinkEventMotion* ev, u64 p1) { return reinterpret_cast<LargeRet(*)(FighterRidleyLinkEventMotion*, u64)>(VT(ev)[0x30/8])(ev, p1); }
} // namespace app::lua_bind
