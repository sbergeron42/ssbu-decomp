#include "app/BattleObjectModuleAccessor.h"
#define IP(a) (*reinterpret_cast<void**>(reinterpret_cast<u8*>(a) + 0x198))
#define VT(m) (*reinterpret_cast<void***>(m))
namespace app::lua_bind {
f32 InkPaintModule__ink_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=IP(a); return reinterpret_cast<f32(*)(void*,u64)>(VT(m)[0x60/8])(m,p1); }
f32 InkPaintModule__ink_max_impl(BattleObjectModuleAccessor* a) { auto* m=IP(a); return reinterpret_cast<f32(*)(void*)>(VT(m)[0x68/8])(m); }
void InkPaintModule__add_ink_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=IP(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x70/8])(m,p1); }
void InkPaintModule__set_ink_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=IP(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x78/8])(m,p1); }
void InkPaintModule__reset_ink_impl(BattleObjectModuleAccessor* a) { auto* m=IP(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x80/8])(m); }
u32 InkPaintModule__get_ink_color_impl(BattleObjectModuleAccessor* a) { auto* m=IP(a); return reinterpret_cast<u32(*)(void*)>(VT(m)[0x88/8])(m); }
void InkPaintModule__set_special_paint_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=IP(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0xb8/8])(m,p1); }
} // namespace app::lua_bind
