#include "app/BattleObjectModuleAccessor.h"
#include "app/modules/ComboModule.h"
#define CM(a) static_cast<ComboModule*>((a)->combo_module)
namespace app::lua_bind {
void ComboModule__set_impl(BattleObjectModuleAccessor* a,u64 p1) { CM(a)->set(p1); }
void ComboModule__reset_impl(BattleObjectModuleAccessor* a) { CM(a)->reset(); }
void ComboModule__clear_setting_impl(BattleObjectModuleAccessor* a) { CM(a)->clear_setting(); }
u32 ComboModule__count_impl(BattleObjectModuleAccessor* a) { return CM(a)->count(); }
bool ComboModule__is_enable_combo_input_impl(BattleObjectModuleAccessor* a) { return CM(a)->is_enable_combo_input(); }
} // namespace app::lua_bind
