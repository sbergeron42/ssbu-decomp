#include "types.h"

// FighterManager — operates on FighterManager* (not BattleObjectModuleAccessor)
// These access FighterManager->internal_data (first ldr x8,[x0]) then fields

struct FighterManager;

namespace app::lua_bind {

// 7102140d60 — entry_count (3 instructions)
u32 FighterManager__entry_count_impl(FighterManager* mgr) {
    auto* data = *reinterpret_cast<u8**>(mgr);
    return *reinterpret_cast<u32*>(data + 0xa0);
}

// 7102141650 — enable_ko_camera (4 instructions)
void FighterManager__enable_ko_camera_impl(FighterManager* mgr) {
    auto* data = *reinterpret_cast<u8**>(mgr);
    data[0xee] = 1;
}

// 7102141660 — disable_ko_camera (3 instructions)
void FighterManager__disable_ko_camera_impl(FighterManager* mgr) {
    auto* data = *reinterpret_cast<u8**>(mgr);
    data[0xee] = 0;
}

} // namespace app::lua_bind
