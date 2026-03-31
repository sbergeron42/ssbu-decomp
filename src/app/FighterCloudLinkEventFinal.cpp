#include "types.h"
#define VT(m) (*reinterpret_cast<void***>(m))

struct FighterCloudLinkEventFinal;

namespace app::lua_bind {

void FighterCloudLinkEventFinal__store_l2c_table_impl(FighterCloudLinkEventFinal* ev) { reinterpret_cast<void(*)(FighterCloudLinkEventFinal*)>(VT(ev)[0x28/8])(ev); }
void FighterCloudLinkEventFinal__load_from_l2c_table_impl(FighterCloudLinkEventFinal* obj,u64 p1) { reinterpret_cast<void(*)(FighterCloudLinkEventFinal*,u64)>(VT(obj)[0x38/8])(obj,p1); }

} // namespace app::lua_bind
