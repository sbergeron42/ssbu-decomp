#include "types.h"
struct LargeRet { unsigned long long a, b, c; };
#define VT(m) (*reinterpret_cast<void***>(m))

struct GimmickEventDrumShake;

namespace app::lua_bind {

LargeRet GimmickEventDrumShake__store_l2c_table_impl(GimmickEventDrumShake* ev) { return reinterpret_cast<LargeRet(*)(GimmickEventDrumShake*)>(VT(ev)[0x28/8])(ev); }
void GimmickEventDrumShake__load_from_l2c_table_impl(GimmickEventDrumShake* obj,u64 p1) { reinterpret_cast<void(*)(GimmickEventDrumShake*,u64)>(VT(obj)[0x38/8])(obj,p1); }

LargeRet GimmickEventDrumShake__store_l2c_table_impl_71020ebda0(GimmickEventDrumShake* ev, u64 p1) { return reinterpret_cast<LargeRet(*)(GimmickEventDrumShake*, u64)>(VT(ev)[0x30/8])(ev, p1); }
} // namespace app::lua_bind
