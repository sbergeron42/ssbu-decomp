#include "app/BattleObjectModuleAccessor.h"
#define SH(a) (a->shadow_module)
#define VT(m) (*reinterpret_cast<void***>(m))
namespace app::lua_bind {
void ShadowModule__set_draw_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { auto* m=SH(a); reinterpret_cast<void(*)(void*,u64,bool)>(VT(m)[0x48/8])(m,p1,p2); }
void ShadowModule__set_draw_status_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=SH(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x50/8])(m,p1); }
void ShadowModule__set_size_impl(BattleObjectModuleAccessor* a) { auto* m=SH(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x60/8])(m); }
void ShadowModule__set_offset_y_impl(BattleObjectModuleAccessor* a) { auto* m=SH(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x78/8])(m); }
} // namespace app::lua_bind
