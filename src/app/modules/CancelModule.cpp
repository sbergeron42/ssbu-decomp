#include "app/BattleObjectModuleAccessor.h"

namespace app::lua_bind {

// CancelModule -- accessor+0x128

// 7102092860 -- is_enable_cancel
bool CancelModule__is_enable_cancel_impl(BattleObjectModuleAccessor* accessor) {
    auto* module = accessor->cancel_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    return reinterpret_cast<bool (*)(void*)>(vtable[0x48 / 8])(module);
}

// 7102092870 -- enable_cancel
void CancelModule__enable_cancel_impl(BattleObjectModuleAccessor* accessor) {
    auto* module = accessor->cancel_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    reinterpret_cast<void (*)(void*)>(vtable[0x50 / 8])(module);
}

} // namespace app::lua_bind
