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
void JostleModule__set_ignore_speed_x_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=JM(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x60/8])(m,p1); }
void JostleModule__sleep_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=JM(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x68/8])(m,p1); }
f32 JostleModule__speed_attenuation_rate_impl(BattleObjectModuleAccessor* a) { auto* m=JM(a); return reinterpret_cast<f32(*)(void*)>(VT(m)[0x98/8])(m); }
void JostleModule__set_refer_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=JM(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0xb0/8])(m,p1); }
void JostleModule__set_push_speed_x_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=JM(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0xb8/8])(m,p1); }
void JostleModule__set_push_speed_x_2_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=JM(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0xc0/8])(m,p1); }
void JostleModule__set_priority_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=JM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0xc8/8])(m,p1); }
void JostleModule__set_ignore_owner_id_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=JM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0xe8/8])(m,p1); }
void JostleModule__set_ignore_pri_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=JM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x108/8])(m,p1); }
void JostleModule__set_push_speed_x_overlap_rate_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=JM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x110/8])(m,p1); }
void JostleModule__set_push_speed_x_overlap_rate_status_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=JM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x118/8])(m,p1); }
f32 JostleModule__weight_impl(BattleObjectModuleAccessor* a) { auto* m=JM(a); return reinterpret_cast<f32(*)(void*)>(VT(m)[0x128/8])(m); }
void JostleModule__set_weight_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=JM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x130/8])(m,p1); }
void JostleModule__set_influence_opponent_weight_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=JM(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x138/8])(m,p1); }
} // namespace app::lua_bind
