#include "app/BattleObjectModuleAccessor.h"

namespace app::lua_bind {

// 71020ae240 — 6 instructions
void FighterAreaModuleImpl__enable_fix_jostle_area_impl(BattleObjectModuleAccessor* accessor, f32 x, f32 y) {
    auto* data = reinterpret_cast<u8*>(accessor->fighter_area_module);
    data[0x2a0] = 1;
    *reinterpret_cast<f32*>(data + 0x2a4) = x;
    *reinterpret_cast<f32*>(data + 0x2a8) = y;
}

// 71020ae260 — 8 instructions
void FighterAreaModuleImpl__enable_fix_jostle_area_xy_impl(BattleObjectModuleAccessor* accessor, f32 x, f32 y, f32 w, f32 h) {
    auto* data = reinterpret_cast<u8*>(accessor->fighter_area_module);
    // Compiler packs these two adjacent bytes as a single strh 0x0101
    data[0x2a0] = 1;
    data[0x2a1] = 1;
    *reinterpret_cast<f32*>(data + 0x2a4) = x;
    *reinterpret_cast<f32*>(data + 0x2a8) = y;
    *reinterpret_cast<f32*>(data + 0x2ac) = w;
    *reinterpret_cast<f32*>(data + 0x2b0) = h;
}

// 71020ae280 — 7 instructions
void FighterAreaModuleImpl__disable_fix_jostle_area_impl(BattleObjectModuleAccessor* accessor) {
    auto* data = reinterpret_cast<u8*>(accessor->fighter_area_module);
    *reinterpret_cast<u16*>(data + 0x2a0) = 0;
    // Compiler zeros these as two 8-byte stores (xzr), covering 0x2a4..0x2b3
    *reinterpret_cast<u64*>(data + 0x2a4) = 0;
    *reinterpret_cast<u64*>(data + 0x2ac) = 0;
}

} // namespace app::lua_bind
