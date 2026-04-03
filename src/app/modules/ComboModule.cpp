#include "app/BattleObjectModuleAccessor.h"
#define CM(a) ((a)->combo_module)
#define VT(m) (*reinterpret_cast<void***>(m))
namespace app::lua_bind {
void ComboModule__set_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=CM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x48/8])(m,p1); }
void ComboModule__reset_impl(BattleObjectModuleAccessor* a) { auto* m=CM(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x58/8])(m); }
void ComboModule__clear_setting_impl(BattleObjectModuleAccessor* a) { auto* m=CM(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x60/8])(m); }
u32 ComboModule__count_impl(BattleObjectModuleAccessor* a) { auto* m=CM(a); return reinterpret_cast<u32(*)(void*)>(VT(m)[0x68/8])(m); }
bool ComboModule__is_enable_combo_input_impl(BattleObjectModuleAccessor* a) { auto* m=CM(a); return reinterpret_cast<bool(*)(void*)>(VT(m)[0xB0/8])(m); }
} // namespace app::lua_bind
