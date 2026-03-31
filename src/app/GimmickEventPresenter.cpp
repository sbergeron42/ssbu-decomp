#include "types.h"

struct GimmickEventPresenter;
struct GimmickEvent;

extern "C" void FUN_710315f230(u64);
extern u8 g_StageManagerSingleton[];

namespace app::lua_bind {

// 71021453e0 — load StageManager singleton, pass field 0x1e0 to external fn (won't byte-match: b is PC-relative)
void GimmickEventPresenter__dispatch_event_from_fighter_impl(GimmickEventPresenter*, GimmickEvent*) {
    auto* mgr = *reinterpret_cast<u8**>(reinterpret_cast<u64*>(g_StageManagerSingleton));
    FUN_710315f230(*reinterpret_cast<u64*>(mgr + 0x1e0));
}

} // namespace app::lua_bind
