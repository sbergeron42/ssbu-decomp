#include "types.h"
#define VT(m) (*reinterpret_cast<void***>(m))

struct lib;

namespace app::lua_bind {

void* lib__BasicEvent__load_from_l2c_table_impl(lib* obj,u64 p1) { return reinterpret_cast<void*(*)(lib*,u64)>(VT(obj)[0x38/8])(obj,p1); }

} // namespace app::lua_bind
