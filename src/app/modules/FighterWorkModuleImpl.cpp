#include "app/BattleObjectModuleAccessor.h"

namespace app::lua_bind {

// 71020adb50 — 6 instructions (vtable dispatcher with 2 bool masks)
void FighterWorkModuleImpl__calc_param_impl(BattleObjectModuleAccessor* a, bool p1, bool p2, u64 p3) {
    auto* module = a->work_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    reinterpret_cast<void(*)(void*, bool, bool, u64)>(vtable[0x280 / 8])(module, p1, p2, p3);
}

} // namespace app::lua_bind
