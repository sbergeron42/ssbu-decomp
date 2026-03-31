#include "types.h"
#define VT(m) (*reinterpret_cast<void***>(m))

struct lib;

namespace app::lua_bind {

void* lib__BasicEvent__load_from_l2c_table_impl(lib* obj,u64 p1) { return reinterpret_cast<void*(*)(lib*,u64)>(VT(obj)[0x38/8])(obj,p1); }
// NOTE: NX Clang uses x9 for vtable temp; vanilla Clang 8 uses x8 (regalloc divergence)
void lib__BasicEvent__store_l2c_table_impl(lib* obj) { reinterpret_cast<void(*)(lib*)>(VT(obj)[0x28/8])(obj); }
// NOTE: NX Clang uses x9 for vtable temp; vanilla Clang 8 uses x8 (regalloc divergence)
void lib__BasicEvent__store_l2c_table_impl_71020faf80(lib* obj,u64 p1) { reinterpret_cast<void(*)(lib*,u64)>(VT(obj)[0x30/8])(obj,p1); }

} // namespace app::lua_bind
