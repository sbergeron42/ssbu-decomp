#include "app/BattleObjectModuleAccessor.h"
#define CTM(a) ((a)->catch_module)
#define VT(m) (*reinterpret_cast<void***>(m))
namespace app::lua_bind {
void CatchModule__set_catch_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=CTM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x58/8])(m,p1); }
bool CatchModule__is_catch_impl(BattleObjectModuleAccessor* a) { auto* m=CTM(a); return reinterpret_cast<bool(*)(void*)>(VT(m)[0x60/8])(m); }
void CatchModule__catch_cut_impl(BattleObjectModuleAccessor* a,bool p1,bool p2) { auto* m=CTM(a); reinterpret_cast<void(*)(void*,bool,bool)>(VT(m)[0x90/8])(m,p1,p2); }
void CatchModule__update_pos_cling_impl(BattleObjectModuleAccessor* a) { auto* m=CTM(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x98/8])(m); }
void CatchModule__cling_cut_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=CTM(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0xa8/8])(m,p1); }
void CatchModule__check_damage_impl(BattleObjectModuleAccessor* a) { auto* m=CTM(a); reinterpret_cast<void(*)(void*)>(VT(m)[0xb0/8])(m); }
void CatchModule__set_send_cut_event_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=CTM(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0xb8/8])(m,p1); }
u32 CatchModule__capture_object_id_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=CTM(a); return reinterpret_cast<u32(*)(void*,bool)>(VT(m)[0xe0/8])(m,p1); }
f32 CatchModule__capture_pos_x_diff_impl(BattleObjectModuleAccessor* a) { auto* m=CTM(a); return reinterpret_cast<f32(*)(void*)>(VT(m)[0xf0/8])(m); }
} // namespace app::lua_bind
