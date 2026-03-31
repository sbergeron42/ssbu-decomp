#include "types.h"
struct LargeRet { unsigned long long a, b, c; };
#define VT(m) (*reinterpret_cast<void***>(m))

struct LinkEventCapture;

namespace app::lua_bind {

LargeRet LinkEventCapture__store_l2c_table_impl(LinkEventCapture* ev) { return reinterpret_cast<LargeRet(*)(LinkEventCapture*)>(VT(ev)[0x28/8])(ev); }
void LinkEventCapture__load_from_l2c_table_impl(LinkEventCapture* obj,u64 p1) { reinterpret_cast<void(*)(LinkEventCapture*,u64)>(VT(obj)[0x38/8])(obj,p1); }

LargeRet LinkEventCapture__store_l2c_table_impl_7101ff8ce0(LinkEventCapture* ev, u64 p1) { return reinterpret_cast<LargeRet(*)(LinkEventCapture*, u64)>(VT(ev)[0x30/8])(ev, p1); }
} // namespace app::lua_bind
