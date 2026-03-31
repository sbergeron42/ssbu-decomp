#include "types.h"
struct LargeRet { unsigned long long a, b, c; };
#define VT(m) (*reinterpret_cast<void***>(m))

struct FighterRyuLinkEventFinalMoveTarget;

namespace app::lua_bind {

LargeRet FighterRyuLinkEventFinalMoveTarget__store_l2c_table_impl(FighterRyuLinkEventFinalMoveTarget* ev) { return reinterpret_cast<LargeRet(*)(FighterRyuLinkEventFinalMoveTarget*)>(VT(ev)[0x28/8])(ev); }
void FighterRyuLinkEventFinalMoveTarget__load_from_l2c_table_impl(FighterRyuLinkEventFinalMoveTarget* obj,u64 p1) { reinterpret_cast<void(*)(FighterRyuLinkEventFinalMoveTarget*,u64)>(VT(obj)[0x38/8])(obj,p1); }

LargeRet FighterRyuLinkEventFinalMoveTarget__store_l2c_table_impl_7102196660(FighterRyuLinkEventFinalMoveTarget* ev, u64 p1) { return reinterpret_cast<LargeRet(*)(FighterRyuLinkEventFinalMoveTarget*, u64)>(VT(ev)[0x30/8])(ev, p1); }
} // namespace app::lua_bind
