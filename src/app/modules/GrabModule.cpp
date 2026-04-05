#include "app/BattleObjectModuleAccessor.h"
#include "app/modules/GrabModule.h"
#define GM(a) static_cast<GrabModule*>((a)->grab_module)

namespace app::lua_bind {

void GrabModule__clear_all_impl(BattleObjectModuleAccessor* a) { GM(a)->clear_all(); }
void GrabModule__clear_impl(BattleObjectModuleAccessor* a, u64 p1) { GM(a)->clear(p1); }
void GrabModule__set_constraint_impl(BattleObjectModuleAccessor* a, u64 p1, bool p2) { GM(a)->set_constraint(p1, p2); }
bool GrabModule__is_grab_impl(BattleObjectModuleAccessor* a, u64 p1) asm("_ZN3app8lua_bind24GrabModule__is_grab_implEPNS_26BattleObjectModuleAccessorE");
bool GrabModule__is_grab_impl(BattleObjectModuleAccessor* a, u64 p1) { return GM(a)->is_grab(p1); }
void* GrabModule__size_impl(BattleObjectModuleAccessor* a, u64 p1) asm("_ZN3app8lua_bind21GrabModule__size_implEPNS_26BattleObjectModuleAccessorE");
void* GrabModule__size_impl(BattleObjectModuleAccessor* a, u64 p1) { return GM(a)->size(p1); }
void GrabModule__set_size_impl(BattleObjectModuleAccessor* a, u64 p1) { GM(a)->set_size(p1); }
f32 GrabModule__pos_x_impl(BattleObjectModuleAccessor* a) { return GM(a)->pos_x(); }
void* GrabModule__center_pos_impl(BattleObjectModuleAccessor* a, u64 p1) asm("_ZN3app8lua_bind27GrabModule__center_pos_implEPNS_26BattleObjectModuleAccessorE");
void* GrabModule__center_pos_impl(BattleObjectModuleAccessor* a, u64 p1) { return GM(a)->center_pos(p1); }
void* GrabModule__node_impl(BattleObjectModuleAccessor* a, u64 p1) { return GM(a)->node(p1); }
void GrabModule__set_power_up_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind29GrabModule__set_power_up_implEPNS_26BattleObjectModuleAccessorEy");
void GrabModule__set_power_up_impl(BattleObjectModuleAccessor* a) { GM(a)->set_power_up(); }
void GrabModule__set_scale_2nd_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind30GrabModule__set_scale_2nd_implEPNS_26BattleObjectModuleAccessorEy");
void GrabModule__set_scale_2nd_impl(BattleObjectModuleAccessor* a) { GM(a)->set_scale_2nd(); }
void GrabModule__relocate_impl(BattleObjectModuleAccessor* a, u64 p1) { GM(a)->relocate(p1); }
void GrabModule__set_check_front_impl(BattleObjectModuleAccessor* a, bool p1) { GM(a)->set_check_front(p1); }
void GrabModule__set_rebound_impl(BattleObjectModuleAccessor* a, bool p1) { GM(a)->set_rebound(p1); }
bool GrabModule__is_rebound_impl(BattleObjectModuleAccessor* a) { return GM(a)->is_rebound(); }
bool GrabModule__check_rebound_impl(BattleObjectModuleAccessor* a, u64 p1) { return GM(a)->check_rebound(p1); }
void GrabModule__disable_sub_fighter_impl(BattleObjectModuleAccessor* a) { GM(a)->disable_sub_fighter(); }
void GrabModule__set_size_mul_impl(BattleObjectModuleAccessor* a, f32 p1) { GM(a)->set_size_mul(); }
void GrabModule__sleep_impl(BattleObjectModuleAccessor* a, bool p1) { GM(a)->sleep(p1); }

} // namespace app::lua_bind
