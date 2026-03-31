#include "types.h"
struct LargeRet { unsigned long long a, b, c; };
#define VT(m) (*reinterpret_cast<void***>(m))

struct LinkEventThrow;

namespace app::lua_bind {

LargeRet LinkEventThrow__store_l2c_table_impl(LinkEventThrow* ev) { return reinterpret_cast<LargeRet(*)(LinkEventThrow*)>(VT(ev)[0x28/8])(ev); }
void LinkEventThrow__load_from_l2c_table_impl(LinkEventThrow* obj,u64 p1) { reinterpret_cast<void(*)(LinkEventThrow*,u64)>(VT(obj)[0x38/8])(obj,p1); }

LargeRet LinkEventThrow__store_l2c_table_impl_7101ffd080(LinkEventThrow* ev, u64 p1) { return reinterpret_cast<LargeRet(*)(LinkEventThrow*, u64)>(VT(ev)[0x30/8])(ev, p1); }
} // namespace app::lua_bind
