#include "types.h"
struct LargeRet { unsigned long long a, b, c; };
#define VT(m) (*reinterpret_cast<void***>(m))

struct GimmickEventDrumCheckNeedHide;

namespace app::lua_bind {

LargeRet GimmickEventDrumCheckNeedHide__store_l2c_table_impl(GimmickEventDrumCheckNeedHide* ev) { return reinterpret_cast<LargeRet(*)(GimmickEventDrumCheckNeedHide*)>(VT(ev)[0x28/8])(ev); }
void GimmickEventDrumCheckNeedHide__load_from_l2c_table_impl(GimmickEventDrumCheckNeedHide* obj,u64 p1) { reinterpret_cast<void(*)(GimmickEventDrumCheckNeedHide*,u64)>(VT(obj)[0x38/8])(obj,p1); }

LargeRet GimmickEventDrumCheckNeedHide__store_l2c_table_impl_71020e9f70(GimmickEventDrumCheckNeedHide* ev, u64 p1) { return reinterpret_cast<LargeRet(*)(GimmickEventDrumCheckNeedHide*, u64)>(VT(ev)[0x30/8])(ev, p1); }
} // namespace app::lua_bind
