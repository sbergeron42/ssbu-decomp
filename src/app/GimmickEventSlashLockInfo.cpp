#include "types.h"
struct LargeRet { unsigned long long a, b, c; };
#define VT(m) (*reinterpret_cast<void***>(m))

struct GimmickEventSlashLockInfo;

namespace app::lua_bind {

LargeRet GimmickEventSlashLockInfo__store_l2c_table_impl(GimmickEventSlashLockInfo* ev) { return reinterpret_cast<LargeRet(*)(GimmickEventSlashLockInfo*)>(VT(ev)[0x28/8])(ev); }
void GimmickEventSlashLockInfo__load_from_l2c_table_impl(GimmickEventSlashLockInfo* obj,u64 p1) { reinterpret_cast<void(*)(GimmickEventSlashLockInfo*,u64)>(VT(obj)[0x38/8])(obj,p1); }

LargeRet GimmickEventSlashLockInfo__store_l2c_table_impl_71020edc10(GimmickEventSlashLockInfo* ev, u64 p1) { return reinterpret_cast<LargeRet(*)(GimmickEventSlashLockInfo*, u64)>(VT(ev)[0x30/8])(ev, p1); }
} // namespace app::lua_bind
