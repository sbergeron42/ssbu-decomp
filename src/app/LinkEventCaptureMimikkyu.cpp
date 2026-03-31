#include "types.h"
struct LargeRet { unsigned long long a, b, c; };
#define VT(m) (*reinterpret_cast<void***>(m))

struct LinkEventCaptureMimikkyu;

namespace app::lua_bind {

LargeRet LinkEventCaptureMimikkyu__store_l2c_table_impl(LinkEventCaptureMimikkyu* ev) { return reinterpret_cast<LargeRet(*)(LinkEventCaptureMimikkyu*)>(VT(ev)[0x28/8])(ev); }
void LinkEventCaptureMimikkyu__load_from_l2c_table_impl(LinkEventCaptureMimikkyu* obj,u64 p1) { reinterpret_cast<void(*)(LinkEventCaptureMimikkyu*,u64)>(VT(obj)[0x38/8])(obj,p1); }

} // namespace app::lua_bind
