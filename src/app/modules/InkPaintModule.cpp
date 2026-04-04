#include "app/BattleObjectModuleAccessor.h"
#include "app/modules/InkPaintModule.h"
#define IP(a) static_cast<InkPaintModule*>((a)->ink_paint_module)

namespace app::lua_bind {

f32 InkPaintModule__ink_impl(BattleObjectModuleAccessor* a, u64 p1) { return IP(a)->ink(p1); }
f32 InkPaintModule__ink_max_impl(BattleObjectModuleAccessor* a) { return IP(a)->ink_max(); }
void InkPaintModule__add_ink_impl(BattleObjectModuleAccessor* a, u64 p1) { IP(a)->add_ink(p1); }
void InkPaintModule__set_ink_impl(BattleObjectModuleAccessor* a, u64 p1) { IP(a)->set_ink(p1); }
void InkPaintModule__reset_ink_impl(BattleObjectModuleAccessor* a) { IP(a)->reset_ink(); }
u32 InkPaintModule__get_ink_color_impl(BattleObjectModuleAccessor* a) { return IP(a)->get_ink_color(); }
void InkPaintModule__set_special_paint_impl(BattleObjectModuleAccessor* a, u64 p1) { IP(a)->set_special_paint(p1); }

} // namespace app::lua_bind
