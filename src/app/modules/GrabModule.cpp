#include "app/BattleObjectModuleAccessor.h"
#define GM(a) (*reinterpret_cast<void**>(reinterpret_cast<u8*>(a) + 0x158))
#define VT(m) (*reinterpret_cast<void***>(m))
namespace app::lua_bind {
void GrabModule__clear_all_impl(BattleObjectModuleAccessor* a) { auto* m=GM(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x50/8])(m); }
void GrabModule__clear_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=GM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x58/8])(m,p1); }
void GrabModule__set_constraint_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { auto* m=GM(a); reinterpret_cast<void(*)(void*,u64,bool)>(VT(m)[0x70/8])(m,p1,p2); }
// x2 scratch → body needs 2 params
bool GrabModule__is_grab_impl(BattleObjectModuleAccessor* a,u64 p1) asm("_ZN3app8lua_bind24GrabModule__is_grab_implEPNS_26BattleObjectModuleAccessorE");
bool GrabModule__is_grab_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=GM(a); return reinterpret_cast<bool(*)(void*,u64)>(VT(m)[0x78/8])(m,p1); }
f32 GrabModule__pos_x_impl(BattleObjectModuleAccessor* a) { auto* m=GM(a); return reinterpret_cast<f32(*)(void*)>(VT(m)[0x90/8])(m); }
// x2 scratch → body needs 2 params
void* GrabModule__center_pos_impl(BattleObjectModuleAccessor* a,u64 p1) asm("_ZN3app8lua_bind27GrabModule__center_pos_implEPNS_26BattleObjectModuleAccessorE");
void* GrabModule__center_pos_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=GM(a); return reinterpret_cast<void*(*)(void*,u64)>(VT(m)[0x98/8])(m,p1); }
void* GrabModule__node_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=GM(a); return reinterpret_cast<void*(*)(void*,u64)>(VT(m)[0xA8/8])(m,p1); }
// x1 scratch → body needs 1 param
void GrabModule__set_power_up_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind29GrabModule__set_power_up_implEPNS_26BattleObjectModuleAccessorEy");
void GrabModule__set_power_up_impl(BattleObjectModuleAccessor* a) { auto* m=GM(a); reinterpret_cast<void(*)(void*)>(VT(m)[0xb0/8])(m); }
// x1 scratch → body needs 1 param
void GrabModule__set_scale_2nd_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind30GrabModule__set_scale_2nd_implEPNS_26BattleObjectModuleAccessorEy");
void GrabModule__set_scale_2nd_impl(BattleObjectModuleAccessor* a) { auto* m=GM(a); reinterpret_cast<void(*)(void*)>(VT(m)[0xc0/8])(m); }
void GrabModule__relocate_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=GM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0xF0/8])(m,p1); }
void GrabModule__set_check_front_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=GM(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0xF8/8])(m,p1); }
void GrabModule__set_rebound_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=GM(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x100/8])(m,p1); }
bool GrabModule__is_rebound_impl(BattleObjectModuleAccessor* a) { auto* m=GM(a); return reinterpret_cast<bool(*)(void*)>(VT(m)[0x108/8])(m); }
bool GrabModule__check_rebound_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=GM(a); return reinterpret_cast<bool(*)(void*,u64)>(VT(m)[0x120/8])(m,p1); }
void GrabModule__disable_sub_fighter_impl(BattleObjectModuleAccessor* a) { auto* m=GM(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x128/8])(m); }
// x2 scratch → body needs 2 params
void* GrabModule__size_impl(BattleObjectModuleAccessor* a,u64 p1) asm("_ZN3app8lua_bind21GrabModule__size_implEPNS_26BattleObjectModuleAccessorE");
void* GrabModule__size_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=GM(a); return reinterpret_cast<void*(*)(void*,u64)>(VT(m)[0x80/8])(m,p1); }
void GrabModule__set_size_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=GM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x88/8])(m,p1); }
} // namespace app::lua_bind
