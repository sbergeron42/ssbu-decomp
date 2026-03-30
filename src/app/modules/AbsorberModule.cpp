#include "app/BattleObjectModuleAccessor.h"
#define AB(a) (*reinterpret_cast<void**>(reinterpret_cast<u8*>(a) + 0x110))
#define VT(m) (*reinterpret_cast<void***>(m))
namespace app::lua_bind {
void AbsorberModule__clean_impl(BattleObjectModuleAccessor* a) { auto* m=AB(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x50/8])(m); }
bool AbsorberModule__is_shield_impl(BattleObjectModuleAccessor* a) { auto* m=AB(a); return reinterpret_cast<bool(*)(void*)>(VT(m)[0x88/8])(m); }
bool AbsorberModule__is_turn_impl(BattleObjectModuleAccessor* a) { auto* m=AB(a); return reinterpret_cast<bool(*)(void*)>(VT(m)[0xA8/8])(m); }
bool AbsorberModule__is_front_impl(BattleObjectModuleAccessor* a) { auto* m=AB(a); return reinterpret_cast<bool(*)(void*)>(VT(m)[0xB0/8])(m); }
bool AbsorberModule__is_hop_impl(BattleObjectModuleAccessor* a) { auto* m=AB(a); return reinterpret_cast<bool(*)(void*)>(VT(m)[0xB8/8])(m); }
f32 AbsorberModule__get_hop_angle_impl(BattleObjectModuleAccessor* a) { auto* m=AB(a); return reinterpret_cast<f32(*)(void*)>(VT(m)[0xC0/8])(m); }
bool AbsorberModule__is_no_hop_impl(BattleObjectModuleAccessor* a) { auto* m=AB(a); return reinterpret_cast<bool(*)(void*)>(VT(m)[0xC8/8])(m); }
f32 AbsorberModule__get_attack_mul_impl(BattleObjectModuleAccessor* a) { auto* m=AB(a); return reinterpret_cast<f32(*)(void*)>(VT(m)[0xF0/8])(m); }
f32 AbsorberModule__get_speed_mul_impl(BattleObjectModuleAccessor* a) { auto* m=AB(a); return reinterpret_cast<f32(*)(void*)>(VT(m)[0x100/8])(m); }
f32 AbsorberModule__get_life_mul_impl(BattleObjectModuleAccessor* a) { auto* m=AB(a); return reinterpret_cast<f32(*)(void*)>(VT(m)[0x110/8])(m); }
f32 AbsorberModule__get_attack_limit_impl(BattleObjectModuleAccessor* a) { auto* m=AB(a); return reinterpret_cast<f32(*)(void*)>(VT(m)[0x120/8])(m); }
bool AbsorberModule__is_no_m_ball_impl(BattleObjectModuleAccessor* a) { auto* m=AB(a); return reinterpret_cast<bool(*)(void*)>(VT(m)[0x140/8])(m); }
u32 AbsorberModule__get_part_size_impl(BattleObjectModuleAccessor* a) { auto* m=AB(a); return reinterpret_cast<u32(*)(void*)>(VT(m)[0x148/8])(m); }
u32 AbsorberModule__get_team_no_impl(BattleObjectModuleAccessor* a) { auto* m=AB(a); return reinterpret_cast<u32(*)(void*)>(VT(m)[0x150/8])(m); }
void AbsorberModule__clear_all_impl(BattleObjectModuleAccessor* a) { auto* m=AB(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x188/8])(m); }
void AbsorberModule__clear_all_2_impl(BattleObjectModuleAccessor* a) { auto* m=AB(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x190/8])(m); }
void* AbsorberModule__get_center_pos_impl(BattleObjectModuleAccessor* a) { auto* m=AB(a); return reinterpret_cast<void*(*)(void*)>(VT(m)[0x198/8])(m); }
f32 AbsorberModule__get_lr_impl(BattleObjectModuleAccessor* a) { auto* m=AB(a); return reinterpret_cast<f32(*)(void*)>(VT(m)[0x1A0/8])(m); }
u32 AbsorberModule__get_group_num_impl(BattleObjectModuleAccessor* a) { auto* m=AB(a); return reinterpret_cast<u32(*)(void*)>(VT(m)[0x1A8/8])(m); }
f32 AbsorberModule__get_pos_x_impl(BattleObjectModuleAccessor* a) { auto* m=AB(a); return reinterpret_cast<f32(*)(void*)>(VT(m)[0x1B0/8])(m); }
} // namespace app::lua_bind
