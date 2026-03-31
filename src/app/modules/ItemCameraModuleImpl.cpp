#include "app/BattleObjectModuleAccessor.h"

// ItemCameraModuleImpl — accesses CameraModule at accessor+0x60
// These operate on the inner camera subject struct

namespace app::lua_bind {

// 71020d3c60 — set_fix_rate (4 instructions: ldr ptr chain, str float)
void ItemMotionAnimcmdModuleImpl__set_fix_rate_impl(BattleObjectModuleAccessor* a, f32 rate) {
    auto* mac = *reinterpret_cast<void**>(reinterpret_cast<u8*>(a) + 0x188);
    auto* inner = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(mac) + 0x8);
    *reinterpret_cast<f32*>(inner + 0x48) = rate;
}

} // namespace app::lua_bind
