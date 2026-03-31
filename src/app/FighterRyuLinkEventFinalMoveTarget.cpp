#include "types.h"
#define VT(m) (*reinterpret_cast<void***>(m))

struct FighterRyuLinkEventFinalMoveTarget;

namespace app::lua_bind {

void FighterRyuLinkEventFinalMoveTarget__load_from_l2c_table_impl(FighterRyuLinkEventFinalMoveTarget* obj,u64 p1) { reinterpret_cast<void(*)(FighterRyuLinkEventFinalMoveTarget*,u64)>(VT(obj)[0x38/8])(obj,p1); }

} // namespace app::lua_bind
