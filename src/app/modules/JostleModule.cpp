#include "app/BattleObjectModuleAccessor.h"
#define JM(a) (a->jostle_module)
#define COLOR_BLEND_MODULE(a) JM(a)
#define VT(m) (*reinterpret_cast<void***>(m))
namespace app::lua_bind {
void JostleModule__set_fix_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=JM(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x58/8])(m,p1); }
bool JostleModule__is_sleep_impl(BattleObjectModuleAccessor* a) { auto* m=JM(a); return reinterpret_cast<bool(*)(void*)>(VT(m)[0x70/8])(m); }
f32 JostleModule__jostle_speed_x_impl(BattleObjectModuleAccessor* a) { auto* m=JM(a); return reinterpret_cast<f32(*)(void*)>(VT(m)[0x80/8])(m); }
f32 JostleModule__pos_z_impl(BattleObjectModuleAccessor* a) { auto* m=JM(a); return reinterpret_cast<f32(*)(void*)>(VT(m)[0xA8/8])(m); }
u32 JostleModule__priority_impl(BattleObjectModuleAccessor* a) { auto* m=JM(a); return reinterpret_cast<u32(*)(void*)>(VT(m)[0xD0/8])(m); }
void JostleModule__set_force_gap_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=JM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0xE0/8])(m,p1); }
void* JostleModule__ignore_owner_id_impl(BattleObjectModuleAccessor* a) { auto* m=a->jostle_module; return reinterpret_cast<void*(*)(void*)>(VT(m)[0xf0/8])(m); }
void JostleModule__reset_area_impl(BattleObjectModuleAccessor* a) { auto* m=JM(a); reinterpret_cast<void(*)(void*)>(VT(m)[0xF8/8])(m); }
void JostleModule__overlap_x_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=JM(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x100/8])(m,p1); }
u32 JostleModule__area_kind_impl(BattleObjectModuleAccessor* a) { auto* m=JM(a); return reinterpret_cast<u32(*)(void*)>(VT(m)[0x120/8])(m); }
void JostleModule__set_ignore_speed_x_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=JM(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x60/8])(m,p1); }
void JostleModule__sleep_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=JM(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x68/8])(m,p1); }
f32 JostleModule__speed_attenuation_rate_impl(BattleObjectModuleAccessor* a) { auto* m=JM(a); return reinterpret_cast<f32(*)(void*)>(VT(m)[0x98/8])(m); }
void JostleModule__set_refer_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=JM(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0xb0/8])(m,p1); }
void JostleModule__set_push_speed_x_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=JM(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0xb8/8])(m,p1); }
void JostleModule__set_push_speed_x_2_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { auto* m=a->jostle_module; reinterpret_cast<void(*)(void*,u64,bool)>(VT(m)[0xc0/8])(m,p1,p2); }
void JostleModule__set_priority_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=JM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0xc8/8])(m,p1); }
void JostleModule__set_ignore_owner_id_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=JM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0xe8/8])(m,p1); }
void JostleModule__set_ignore_pri_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=JM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x108/8])(m,p1); }
void JostleModule__set_push_speed_x_overlap_rate_impl(BattleObjectModuleAccessor* a) { auto* m=a->jostle_module; reinterpret_cast<void(*)(void*)>(VT(m)[0x110/8])(m); }
void JostleModule__set_push_speed_x_overlap_rate_status_impl(BattleObjectModuleAccessor* a) { auto* m=a->jostle_module; reinterpret_cast<void(*)(void*)>(VT(m)[0x118/8])(m); }
f32 JostleModule__weight_impl(BattleObjectModuleAccessor* a) { auto* m=JM(a); return reinterpret_cast<f32(*)(void*)>(VT(m)[0x128/8])(m); }
void JostleModule__set_weight_impl(BattleObjectModuleAccessor* a) { auto* m=a->jostle_module; reinterpret_cast<void(*)(void*)>(VT(m)[0x130/8])(m); }
void JostleModule__set_influence_opponent_weight_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=JM(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x138/8])(m,p1); }
// Auto-generated named dispatchers
void JostleModule__set_status_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=COLOR_BLEND_MODULE(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x48/8])(m,p1); }
void JostleModule__set_layer_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=COLOR_BLEND_MODULE(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x50/8])(m,p1); }
void* JostleModule__target_weight_impl(BattleObjectModuleAccessor* a) { auto* m=COLOR_BLEND_MODULE(a); return reinterpret_cast<void*(*)(void*)>(VT(m)[0xa0/8])(m); }
void JostleModule__set_propagate_push_speed_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=COLOR_BLEND_MODULE(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x140/8])(m,p1); }
void JostleModule__set_overlap_rate_mul_impl(BattleObjectModuleAccessor* a) { auto* m=COLOR_BLEND_MODULE(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x158/8])(m); }
// Multi-bool dispatchers (auto-generated)
void JostleModule__set_team_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=a->jostle_module; reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x160/8])(m,p1); }
} // namespace app::lua_bind
