#include "app/BattleObjectModuleAccessor.h"
#define SM(a) (*reinterpret_cast<void**>(reinterpret_cast<u8*>(a) + 0x100))
#define VT(m) (*reinterpret_cast<void***>(m))
namespace app::lua_bind {
void ShieldModule__clean_impl(BattleObjectModuleAccessor* a) { auto* m=SM(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x50/8])(m); }
// x3 scratch → 3 body params
bool ShieldModule__is_shield_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) asm("_ZN3app8lua_bind28ShieldModule__is_shield_implEPNS_26BattleObjectModuleAccessorE");
bool ShieldModule__is_shield_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=SM(a); return reinterpret_cast<bool(*)(void*,u64,u64)>(VT(m)[0x88/8])(m,p1,p2); }
// x3 scratch → 3 body params
void ShieldModule__set_size_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) asm("_ZN3app8lua_bind27ShieldModule__set_size_implEPNS_26BattleObjectModuleAccessorEy");
void ShieldModule__set_size_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=SM(a); reinterpret_cast<void(*)(void*,u64,u64)>(VT(m)[0x90/8])(m,p1,p2); }
// x4 scratch → 4 body params
void ShieldModule__set_status_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3) asm("_ZN3app8lua_bind29ShieldModule__set_status_implEPNS_26BattleObjectModuleAccessorEy");
void ShieldModule__set_status_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3) { auto* m=SM(a); reinterpret_cast<void(*)(void*,u64,u64,u64)>(VT(m)[0x98/8])(m,p1,p2,p3); }
// x3 scratch → 3 body params
void ShieldModule__set_status_all_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) asm("_ZN3app8lua_bind33ShieldModule__set_status_all_implEPNS_26BattleObjectModuleAccessorEy");
void ShieldModule__set_status_all_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=SM(a); reinterpret_cast<void(*)(void*,u64,u64)>(VT(m)[0xa0/8])(m,p1,p2); }
// x2 scratch → 2 body params
bool ShieldModule__is_turn_impl(BattleObjectModuleAccessor* a,u64 p1) asm("_ZN3app8lua_bind26ShieldModule__is_turn_implEPNS_26BattleObjectModuleAccessorE");
bool ShieldModule__is_turn_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=SM(a); return reinterpret_cast<bool(*)(void*,u64)>(VT(m)[0xa8/8])(m,p1); }
// x2 scratch → 2 body params
bool ShieldModule__is_front_impl(BattleObjectModuleAccessor* a,u64 p1) asm("_ZN3app8lua_bind27ShieldModule__is_front_implEPNS_26BattleObjectModuleAccessorE");
bool ShieldModule__is_front_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=SM(a); return reinterpret_cast<bool(*)(void*,u64)>(VT(m)[0xb0/8])(m,p1); }
// x2 scratch → 2 body params
bool ShieldModule__is_hop_impl(BattleObjectModuleAccessor* a,u64 p1) asm("_ZN3app8lua_bind25ShieldModule__is_hop_implEPNS_26BattleObjectModuleAccessorE");
bool ShieldModule__is_hop_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=SM(a); return reinterpret_cast<bool(*)(void*,u64)>(VT(m)[0xb8/8])(m,p1); }
// x2 scratch → 2 body params
void* ShieldModule__get_hop_angle_impl(BattleObjectModuleAccessor* a,u64 p1) asm("_ZN3app8lua_bind32ShieldModule__get_hop_angle_implEPNS_26BattleObjectModuleAccessorE");
void* ShieldModule__get_hop_angle_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=SM(a); return reinterpret_cast<void*(*)(void*,u64)>(VT(m)[0xc0/8])(m,p1); }
// x2 scratch → 2 body params
bool ShieldModule__is_no_hop_impl(BattleObjectModuleAccessor* a,u64 p1) asm("_ZN3app8lua_bind28ShieldModule__is_no_hop_implEPNS_26BattleObjectModuleAccessorE");
bool ShieldModule__is_no_hop_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=SM(a); return reinterpret_cast<bool(*)(void*,u64)>(VT(m)[0xc8/8])(m,p1); }
// x3 scratch → 3 body params, bool at x1 (and w1,w1,#1)
void ShieldModule__set_turn_impl(BattleObjectModuleAccessor* a,bool p1,u64 p2) asm("_ZN3app8lua_bind27ShieldModule__set_turn_implEPNS_26BattleObjectModuleAccessorEb");
void ShieldModule__set_turn_impl(BattleObjectModuleAccessor* a,bool p1,u64 p2) { auto* m=SM(a); reinterpret_cast<void(*)(void*,bool,u64)>(VT(m)[0xd0/8])(m,p1,p2); }
// x3 scratch → 3 body params
void ShieldModule__set_front_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) asm("_ZN3app8lua_bind28ShieldModule__set_front_implEPNS_26BattleObjectModuleAccessorEy");
void ShieldModule__set_front_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=SM(a); reinterpret_cast<void(*)(void*,u64,u64)>(VT(m)[0xd8/8])(m,p1,p2); }
// x3 scratch → 3 body params, bool at x1 (and w1,w1,#1)
void ShieldModule__set_hop_impl(BattleObjectModuleAccessor* a,bool p1,u64 p2) asm("_ZN3app8lua_bind26ShieldModule__set_hop_implEPNS_26BattleObjectModuleAccessorEb");
void ShieldModule__set_hop_impl(BattleObjectModuleAccessor* a,bool p1,u64 p2) { auto* m=SM(a); reinterpret_cast<void(*)(void*,bool,u64)>(VT(m)[0xe0/8])(m,p1,p2); }
void ShieldModule__set_attack_mul_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=SM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0xe8/8])(m,p1); }
// x2 scratch → 2 body params
void* ShieldModule__get_attack_mul_impl(BattleObjectModuleAccessor* a,u64 p1) asm("_ZN3app8lua_bind33ShieldModule__get_attack_mul_implEPNS_26BattleObjectModuleAccessorE");
void* ShieldModule__get_attack_mul_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=SM(a); return reinterpret_cast<void*(*)(void*,u64)>(VT(m)[0xf0/8])(m,p1); }
void ShieldModule__set_speed_mul_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=SM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0xf8/8])(m,p1); }
// x2 scratch → 2 body params
void* ShieldModule__get_speed_mul_impl(BattleObjectModuleAccessor* a,u64 p1) asm("_ZN3app8lua_bind32ShieldModule__get_speed_mul_implEPNS_26BattleObjectModuleAccessorE");
void* ShieldModule__get_speed_mul_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=SM(a); return reinterpret_cast<void*(*)(void*,u64)>(VT(m)[0x100/8])(m,p1); }
void ShieldModule__set_life_mul_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=SM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x108/8])(m,p1); }
// x2 scratch → 2 body params
void* ShieldModule__get_life_mul_impl(BattleObjectModuleAccessor* a,u64 p1) asm("_ZN3app8lua_bind31ShieldModule__get_life_mul_implEPNS_26BattleObjectModuleAccessorE");
void* ShieldModule__get_life_mul_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=SM(a); return reinterpret_cast<void*(*)(void*,u64)>(VT(m)[0x110/8])(m,p1); }
void ShieldModule__set_attack_limit_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=SM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x118/8])(m,p1); }
// x2 scratch → 2 body params
void* ShieldModule__get_attack_limit_impl(BattleObjectModuleAccessor* a,u64 p1) asm("_ZN3app8lua_bind35ShieldModule__get_attack_limit_implEPNS_26BattleObjectModuleAccessorE");
void* ShieldModule__get_attack_limit_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=SM(a); return reinterpret_cast<void*(*)(void*,u64)>(VT(m)[0x120/8])(m,p1); }
// x1 scratch → 1 body param
void ShieldModule__set_hit_stop_mul_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind35ShieldModule__set_hit_stop_mul_implEPNS_26BattleObjectModuleAccessorEy");
void ShieldModule__set_hit_stop_mul_impl(BattleObjectModuleAccessor* a) { auto* m=SM(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x130/8])(m); }
// x2 scratch → 2 body params
bool ShieldModule__is_no_m_ball_impl(BattleObjectModuleAccessor* a,u64 p1) asm("_ZN3app8lua_bind31ShieldModule__is_no_m_ball_implEPNS_26BattleObjectModuleAccessorE");
bool ShieldModule__is_no_m_ball_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=SM(a); return reinterpret_cast<bool(*)(void*,u64)>(VT(m)[0x140/8])(m,p1); }
// x2 scratch → 2 body params
void* ShieldModule__get_part_size_impl(BattleObjectModuleAccessor* a,u64 p1) asm("_ZN3app8lua_bind32ShieldModule__get_part_size_implEPNS_26BattleObjectModuleAccessorE");
void* ShieldModule__get_part_size_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=SM(a); return reinterpret_cast<void*(*)(void*,u64)>(VT(m)[0x148/8])(m,p1); }
u32 ShieldModule__get_team_no_impl(BattleObjectModuleAccessor* a) { auto* m=SM(a); return reinterpret_cast<u32(*)(void*)>(VT(m)[0x150/8])(m); }
void ShieldModule__set_no_team_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=SM(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x158/8])(m,p1); }
// x4 scratch → 4 body params
void ShieldModule__set_shield_type_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3) asm("_ZN3app8lua_bind34ShieldModule__set_shield_type_implEPNS_26BattleObjectModuleAccessorEy");
void ShieldModule__set_shield_type_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3) { auto* m=SM(a); reinterpret_cast<void(*)(void*,u64,u64,u64)>(VT(m)[0x160/8])(m,p1,p2,p3); }
void ShieldModule__clear_all_impl(BattleObjectModuleAccessor* a) { auto* m=SM(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x188/8])(m); }
// x2 scratch → 2 body params
void ShieldModule__clear_all_2_impl(BattleObjectModuleAccessor* a,u64 p1) asm("_ZN3app8lua_bind30ShieldModule__clear_all_2_implEPNS_26BattleObjectModuleAccessorE");
void ShieldModule__clear_all_2_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=SM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x190/8])(m,p1); }
// x3 scratch → 3 body params
void* ShieldModule__get_center_pos_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) asm("_ZN3app8lua_bind33ShieldModule__get_center_pos_implEPNS_26BattleObjectModuleAccessorE");
void* ShieldModule__get_center_pos_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=SM(a); return reinterpret_cast<void*(*)(void*,u64,u64)>(VT(m)[0x198/8])(m,p1,p2); }
// x2 scratch → 2 body params
void* ShieldModule__get_lr_impl(BattleObjectModuleAccessor* a,u64 p1) asm("_ZN3app8lua_bind25ShieldModule__get_lr_implEPNS_26BattleObjectModuleAccessorE");
void* ShieldModule__get_lr_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=SM(a); return reinterpret_cast<void*(*)(void*,u64)>(VT(m)[0x1a0/8])(m,p1); }
u32 ShieldModule__get_group_num_impl(BattleObjectModuleAccessor* a) { auto* m=SM(a); return reinterpret_cast<u32(*)(void*)>(VT(m)[0x1A8/8])(m); }
// x2 scratch → 2 body params
void* ShieldModule__get_pos_x_impl(BattleObjectModuleAccessor* a,u64 p1) asm("_ZN3app8lua_bind28ShieldModule__get_pos_x_implEPNS_26BattleObjectModuleAccessorE");
void* ShieldModule__get_pos_x_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=SM(a); return reinterpret_cast<void*(*)(void*,u64)>(VT(m)[0x1b0/8])(m,p1); }
// x3 scratch → 3 body params
void ShieldModule__set_target_property_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) asm("_ZN3app8lua_bind38ShieldModule__set_target_property_implEPNS_26BattleObjectModuleAccessorEy");
void ShieldModule__set_target_property_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=SM(a); reinterpret_cast<void(*)(void*,u64,u64)>(VT(m)[0x1b8/8])(m,p1,p2); }
// x3 scratch → 3 body params
void ShieldModule__set_target_category_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) asm("_ZN3app8lua_bind38ShieldModule__set_target_category_implEPNS_26BattleObjectModuleAccessorEy");
void ShieldModule__set_target_category_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=SM(a); reinterpret_cast<void(*)(void*,u64,u64)>(VT(m)[0x1c0/8])(m,p1,p2); }
void ShieldModule__sleep_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=SM(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x1d0/8])(m,p1); }
void ShieldModule__set_hit_stop_slow_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=SM(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x1e8/8])(m,p1); }
} // namespace app::lua_bind
