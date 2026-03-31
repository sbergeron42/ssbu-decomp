#include "types.h"
struct LargeRet { unsigned long long a, b, c; };
#define VT(m) (*reinterpret_cast<void***>(m))

struct FighterCloudLinkEventFinal;

namespace app::lua_bind {

LargeRet FighterCloudLinkEventFinal__store_l2c_table_impl(FighterCloudLinkEventFinal* ev) { return reinterpret_cast<LargeRet(*)(FighterCloudLinkEventFinal*)>(VT(ev)[0x28/8])(ev); }
void FighterCloudLinkEventFinal__load_from_l2c_table_impl(FighterCloudLinkEventFinal* obj,u64 p1) { reinterpret_cast<void(*)(FighterCloudLinkEventFinal*,u64)>(VT(obj)[0x38/8])(obj,p1); }

LargeRet FighterCloudLinkEventFinal__store_l2c_table_impl_71021992e0(FighterCloudLinkEventFinal* ev, u64 p1) { return reinterpret_cast<LargeRet(*)(FighterCloudLinkEventFinal*, u64)>(VT(ev)[0x30/8])(ev, p1); }
} // namespace app::lua_bind
