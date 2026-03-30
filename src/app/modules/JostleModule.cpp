#include "app/BattleObjectModuleAccessor.h"
#define JM(a) (*reinterpret_cast<void**>(reinterpret_cast<u8*>(a) + 0x118))
#define VT(m) (*reinterpret_cast<void***>(m))
namespace app::lua_bind {
void JostleModule__set_fix_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=JM(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x58/8])(m,p1); }
bool JostleModule__is_sleep_impl(BattleObjectModuleAccessor* a) { auto* m=JM(a); return reinterpret_cast<bool(*)(void*)>(VT(m)[0x70/8])(m); }
f32 JostleModule__jostle_speed_x_impl(BattleObjectModuleAccessor* a) { auto* m=JM(a); return reinterpret_cast<f32(*)(void*)>(VT(m)[0x80/8])(m); }
f32 JostleModule__pos_z_impl(BattleObjectModuleAccessor* a) { auto* m=JM(a); return reinterpret_cast<f32(*)(void*)>(VT(m)[0xA8/8])(m); }
u32 JostleModule__priority_impl(BattleObjectModuleAccessor* a) { auto* m=JM(a); return reinterpret_cast<u32(*)(void*)>(VT(m)[0xD0/8])(m); }
void JostleModule__set_force_gap_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=JM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0xE0/8])(m,p1); }
void JostleModule__ignore_owner_id_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=JM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0xF0/8])(m,p1); }
void JostleModule__reset_area_impl(BattleObjectModuleAccessor* a) { auto* m=JM(a); reinterpret_cast<void(*)(void*)>(VT(m)[0xF8/8])(m); }
void JostleModule__overlap_x_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=JM(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x100/8])(m,p1); }
u32 JostleModule__area_kind_impl(BattleObjectModuleAccessor* a) { auto* m=JM(a); return reinterpret_cast<u32(*)(void*)>(VT(m)[0x120/8])(m); }
} // namespace app::lua_bind
