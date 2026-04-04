#include "app/BattleObjectModuleAccessor.h"
#include "app/modules/CatchModule.h"
#define CTM(a) static_cast<CatchModule*>((a)->catch_module)

namespace app::lua_bind {

void CatchModule__set_catch_impl(BattleObjectModuleAccessor* a, u64 p1) { CTM(a)->set_catch(p1); }
bool CatchModule__is_catch_impl(BattleObjectModuleAccessor* a) { return CTM(a)->is_catch(); }
void CatchModule__catch_cut_impl(BattleObjectModuleAccessor* a, bool p1, bool p2) { CTM(a)->catch_cut(p1, p2); }
void CatchModule__update_pos_cling_impl(BattleObjectModuleAccessor* a) { CTM(a)->update_pos_cling(); }
void CatchModule__cling_cut_impl(BattleObjectModuleAccessor* a, bool p1) { CTM(a)->cling_cut(p1); }
void CatchModule__check_damage_impl(BattleObjectModuleAccessor* a) { CTM(a)->check_damage(); }
void CatchModule__set_send_cut_event_impl(BattleObjectModuleAccessor* a, bool p1) { CTM(a)->set_send_cut_event(p1); }
u32 CatchModule__capture_object_id_impl(BattleObjectModuleAccessor* a, bool p1) { return CTM(a)->capture_object_id(p1); }
f32 CatchModule__capture_pos_x_diff_impl(BattleObjectModuleAccessor* a) { return CTM(a)->capture_pos_x_diff(); }

} // namespace app::lua_bind
