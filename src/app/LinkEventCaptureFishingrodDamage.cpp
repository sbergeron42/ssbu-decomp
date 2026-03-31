#include "types.h"
struct LargeRet { unsigned long long a, b, c; };
#define VT(m) (*reinterpret_cast<void***>(m))

struct LinkEventCaptureFishingrodDamage;

namespace app::lua_bind {

LargeRet LinkEventCaptureFishingrodDamage__store_l2c_table_impl(LinkEventCaptureFishingrodDamage* ev) { return reinterpret_cast<LargeRet(*)(LinkEventCaptureFishingrodDamage*)>(VT(ev)[0x28/8])(ev); }
void LinkEventCaptureFishingrodDamage__load_from_l2c_table_impl(LinkEventCaptureFishingrodDamage* obj,u64 p1) { reinterpret_cast<void(*)(LinkEventCaptureFishingrodDamage*,u64)>(VT(obj)[0x38/8])(obj,p1); }

} // namespace app::lua_bind
