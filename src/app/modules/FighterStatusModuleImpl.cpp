#include "app/BattleObjectModuleAccessor.h"

namespace app::lua_bind {

// 71020a9a20 — 3 instructions (field write: clear byte)
void FighterStatusModuleImpl__off_disable_intrrupt_warp_impl(BattleObjectModuleAccessor* a) {
    auto* module = reinterpret_cast<u8*>(a->status_module);
    module[0x12c] = 0;
}

} // namespace app::lua_bind
