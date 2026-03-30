#include "app/BattleObjectModuleAccessor.h"
#define SM(a) (*reinterpret_cast<void**>(reinterpret_cast<u8*>(a) + 0x100))
#define VT(m) (*reinterpret_cast<void***>(m))
namespace app::lua_bind {
void ShieldModule__clean_impl(BattleObjectModuleAccessor* a) { auto* m=SM(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x50/8])(m); }
bool ShieldModule__is_front_impl(BattleObjectModuleAccessor* a) { auto* m=SM(a); return reinterpret_cast<bool(*)(void*)>(VT(m)[0xB0/8])(m); }
f32 ShieldModule__get_hop_angle_impl(BattleObjectModuleAccessor* a) { auto* m=SM(a); return reinterpret_cast<f32(*)(void*)>(VT(m)[0xC0/8])(m); }
f32 ShieldModule__get_attack_mul_impl(BattleObjectModuleAccessor* a) { auto* m=SM(a); return reinterpret_cast<f32(*)(void*)>(VT(m)[0xF0/8])(m); }
f32 ShieldModule__get_speed_mul_impl(BattleObjectModuleAccessor* a) { auto* m=SM(a); return reinterpret_cast<f32(*)(void*)>(VT(m)[0x100/8])(m); }
f32 ShieldModule__get_life_mul_impl(BattleObjectModuleAccessor* a) { auto* m=SM(a); return reinterpret_cast<f32(*)(void*)>(VT(m)[0x110/8])(m); }
f32 ShieldModule__get_attack_limit_impl(BattleObjectModuleAccessor* a) { auto* m=SM(a); return reinterpret_cast<f32(*)(void*)>(VT(m)[0x120/8])(m); }
u32 ShieldModule__get_part_size_impl(BattleObjectModuleAccessor* a) { auto* m=SM(a); return reinterpret_cast<u32(*)(void*)>(VT(m)[0x148/8])(m); }
u32 ShieldModule__get_team_no_impl(BattleObjectModuleAccessor* a) { auto* m=SM(a); return reinterpret_cast<u32(*)(void*)>(VT(m)[0x150/8])(m); }
void ShieldModule__clear_all_impl(BattleObjectModuleAccessor* a) { auto* m=SM(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x188/8])(m); }
void ShieldModule__clear_all_2_impl(BattleObjectModuleAccessor* a) { auto* m=SM(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x190/8])(m); }
void* ShieldModule__get_center_pos_impl(BattleObjectModuleAccessor* a) { auto* m=SM(a); return reinterpret_cast<void*(*)(void*)>(VT(m)[0x198/8])(m); }
f32 ShieldModule__get_lr_impl(BattleObjectModuleAccessor* a) { auto* m=SM(a); return reinterpret_cast<f32(*)(void*)>(VT(m)[0x1A0/8])(m); }
u32 ShieldModule__get_group_num_impl(BattleObjectModuleAccessor* a) { auto* m=SM(a); return reinterpret_cast<u32(*)(void*)>(VT(m)[0x1A8/8])(m); }
f32 ShieldModule__get_pos_x_impl(BattleObjectModuleAccessor* a) { auto* m=SM(a); return reinterpret_cast<f32(*)(void*)>(VT(m)[0x1B0/8])(m); }
} // namespace app::lua_bind
