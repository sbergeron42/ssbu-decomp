#include "app/BattleObjectModuleAccessor.h"
#define RF(a) (*reinterpret_cast<void**>(reinterpret_cast<u8*>(a) + 0x108))
#define VT(m) (*reinterpret_cast<void***>(m))
namespace app::lua_bind {
void ReflectorModule__clean_impl(BattleObjectModuleAccessor* a) { auto* m=RF(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x50/8])(m); }
// x3 scratch → 3 body params
bool ReflectorModule__is_shield_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) asm("_ZN3app8lua_bind31ReflectorModule__is_shield_implEPNS_26BattleObjectModuleAccessorE");
bool ReflectorModule__is_shield_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=RF(a); return reinterpret_cast<bool(*)(void*,u64,u64)>(VT(m)[0x88/8])(m,p1,p2); }
// x3 scratch → 3 body params
void ReflectorModule__set_size_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) asm("_ZN3app8lua_bind30ReflectorModule__set_size_implEPNS_26BattleObjectModuleAccessorEy");
void ReflectorModule__set_size_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=RF(a); reinterpret_cast<void(*)(void*,u64,u64)>(VT(m)[0x90/8])(m,p1,p2); }
// x4 scratch → 4 body params
void ReflectorModule__set_status_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3) asm("_ZN3app8lua_bind32ReflectorModule__set_status_implEPNS_26BattleObjectModuleAccessorEy");
void ReflectorModule__set_status_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3) { auto* m=RF(a); reinterpret_cast<void(*)(void*,u64,u64,u64)>(VT(m)[0x98/8])(m,p1,p2,p3); }
// x3 scratch → 3 body params
void ReflectorModule__set_status_all_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) asm("_ZN3app8lua_bind36ReflectorModule__set_status_all_implEPNS_26BattleObjectModuleAccessorEy");
void ReflectorModule__set_status_all_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=RF(a); reinterpret_cast<void(*)(void*,u64,u64)>(VT(m)[0xa0/8])(m,p1,p2); }
// x2 scratch → 2 body params
bool ReflectorModule__is_turn_impl(BattleObjectModuleAccessor* a,u64 p1) asm("_ZN3app8lua_bind29ReflectorModule__is_turn_implEPNS_26BattleObjectModuleAccessorE");
bool ReflectorModule__is_turn_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=RF(a); return reinterpret_cast<bool(*)(void*,u64)>(VT(m)[0xa8/8])(m,p1); }
// x2 scratch → 2 body params
bool ReflectorModule__is_front_impl(BattleObjectModuleAccessor* a,u64 p1) asm("_ZN3app8lua_bind30ReflectorModule__is_front_implEPNS_26BattleObjectModuleAccessorE");
bool ReflectorModule__is_front_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=RF(a); return reinterpret_cast<bool(*)(void*,u64)>(VT(m)[0xb0/8])(m,p1); }
// x2 scratch → 2 body params
bool ReflectorModule__is_hop_impl(BattleObjectModuleAccessor* a,u64 p1) asm("_ZN3app8lua_bind28ReflectorModule__is_hop_implEPNS_26BattleObjectModuleAccessorE");
bool ReflectorModule__is_hop_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=RF(a); return reinterpret_cast<bool(*)(void*,u64)>(VT(m)[0xb8/8])(m,p1); }
// x2 scratch → 2 body params
void* ReflectorModule__get_hop_angle_impl(BattleObjectModuleAccessor* a,u64 p1) asm("_ZN3app8lua_bind35ReflectorModule__get_hop_angle_implEPNS_26BattleObjectModuleAccessorE");
void* ReflectorModule__get_hop_angle_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=RF(a); return reinterpret_cast<void*(*)(void*,u64)>(VT(m)[0xc0/8])(m,p1); }
// x2 scratch → 2 body params
bool ReflectorModule__is_no_hop_impl(BattleObjectModuleAccessor* a,u64 p1) asm("_ZN3app8lua_bind31ReflectorModule__is_no_hop_implEPNS_26BattleObjectModuleAccessorE");
bool ReflectorModule__is_no_hop_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=RF(a); return reinterpret_cast<bool(*)(void*,u64)>(VT(m)[0xc8/8])(m,p1); }
// x3 scratch → 3 body params, bool at x1 (and w1,w1,#1)
void ReflectorModule__set_turn_impl(BattleObjectModuleAccessor* a,bool p1,u64 p2) asm("_ZN3app8lua_bind30ReflectorModule__set_turn_implEPNS_26BattleObjectModuleAccessorEb");
void ReflectorModule__set_turn_impl(BattleObjectModuleAccessor* a,bool p1,u64 p2) { auto* m=RF(a); reinterpret_cast<void(*)(void*,bool,u64)>(VT(m)[0xd0/8])(m,p1,p2); }
// x3 scratch → 3 body params
void ReflectorModule__set_front_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) asm("_ZN3app8lua_bind31ReflectorModule__set_front_implEPNS_26BattleObjectModuleAccessorEy");
void ReflectorModule__set_front_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=RF(a); reinterpret_cast<void(*)(void*,u64,u64)>(VT(m)[0xd8/8])(m,p1,p2); }
// x3 scratch → 3 body params, bool at x1 (and w1,w1,#1)
void ReflectorModule__set_hop_impl(BattleObjectModuleAccessor* a,bool p1,u64 p2) asm("_ZN3app8lua_bind29ReflectorModule__set_hop_implEPNS_26BattleObjectModuleAccessorEb");
void ReflectorModule__set_hop_impl(BattleObjectModuleAccessor* a,bool p1,u64 p2) { auto* m=RF(a); reinterpret_cast<void(*)(void*,bool,u64)>(VT(m)[0xe0/8])(m,p1,p2); }
void ReflectorModule__set_attack_mul_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=RF(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0xe8/8])(m,p1); }
// x2 scratch → 2 body params
void* ReflectorModule__get_attack_mul_impl(BattleObjectModuleAccessor* a,u64 p1) asm("_ZN3app8lua_bind36ReflectorModule__get_attack_mul_implEPNS_26BattleObjectModuleAccessorE");
void* ReflectorModule__get_attack_mul_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=RF(a); return reinterpret_cast<void*(*)(void*,u64)>(VT(m)[0xf0/8])(m,p1); }
void ReflectorModule__set_speed_mul_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=RF(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0xf8/8])(m,p1); }
// x2 scratch → 2 body params
void* ReflectorModule__get_speed_mul_impl(BattleObjectModuleAccessor* a,u64 p1) asm("_ZN3app8lua_bind35ReflectorModule__get_speed_mul_implEPNS_26BattleObjectModuleAccessorE");
void* ReflectorModule__get_speed_mul_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=RF(a); return reinterpret_cast<void*(*)(void*,u64)>(VT(m)[0x100/8])(m,p1); }
void ReflectorModule__set_life_mul_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=RF(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x108/8])(m,p1); }
// x2 scratch → 2 body params
void* ReflectorModule__get_life_mul_impl(BattleObjectModuleAccessor* a,u64 p1) asm("_ZN3app8lua_bind34ReflectorModule__get_life_mul_implEPNS_26BattleObjectModuleAccessorE");
void* ReflectorModule__get_life_mul_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=RF(a); return reinterpret_cast<void*(*)(void*,u64)>(VT(m)[0x110/8])(m,p1); }
void ReflectorModule__set_attack_limit_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=RF(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x118/8])(m,p1); }
// x2 scratch → 2 body params
void* ReflectorModule__get_attack_limit_impl(BattleObjectModuleAccessor* a,u64 p1) asm("_ZN3app8lua_bind38ReflectorModule__get_attack_limit_implEPNS_26BattleObjectModuleAccessorE");
void* ReflectorModule__get_attack_limit_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=RF(a); return reinterpret_cast<void*(*)(void*,u64)>(VT(m)[0x120/8])(m,p1); }
// x1 scratch → 1 body param
void ReflectorModule__set_hit_stop_mul_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind38ReflectorModule__set_hit_stop_mul_implEPNS_26BattleObjectModuleAccessorEy");
void ReflectorModule__set_hit_stop_mul_impl(BattleObjectModuleAccessor* a) { auto* m=RF(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x130/8])(m); }
// x2 scratch → 2 body params
bool ReflectorModule__is_no_m_ball_impl(BattleObjectModuleAccessor* a,u64 p1) asm("_ZN3app8lua_bind34ReflectorModule__is_no_m_ball_implEPNS_26BattleObjectModuleAccessorE");
bool ReflectorModule__is_no_m_ball_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=RF(a); return reinterpret_cast<bool(*)(void*,u64)>(VT(m)[0x140/8])(m,p1); }
// x2 scratch → 2 body params
void* ReflectorModule__get_part_size_impl(BattleObjectModuleAccessor* a,u64 p1) asm("_ZN3app8lua_bind35ReflectorModule__get_part_size_implEPNS_26BattleObjectModuleAccessorE");
void* ReflectorModule__get_part_size_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=RF(a); return reinterpret_cast<void*(*)(void*,u64)>(VT(m)[0x148/8])(m,p1); }
u32 ReflectorModule__get_team_no_impl(BattleObjectModuleAccessor* a) { auto* m=RF(a); return reinterpret_cast<u32(*)(void*)>(VT(m)[0x150/8])(m); }
void ReflectorModule__set_no_team_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=RF(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x158/8])(m,p1); }
// x4 scratch → 4 body params
void ReflectorModule__set_shield_type_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3) asm("_ZN3app8lua_bind37ReflectorModule__set_shield_type_implEPNS_26BattleObjectModuleAccessorEy");
void ReflectorModule__set_shield_type_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3) { auto* m=RF(a); reinterpret_cast<void(*)(void*,u64,u64,u64)>(VT(m)[0x160/8])(m,p1,p2,p3); }
void ReflectorModule__clear_all_impl(BattleObjectModuleAccessor* a) { auto* m=RF(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x188/8])(m); }
// x2 scratch → 2 body params
void ReflectorModule__clear_all_2_impl(BattleObjectModuleAccessor* a,u64 p1) asm("_ZN3app8lua_bind33ReflectorModule__clear_all_2_implEPNS_26BattleObjectModuleAccessorE");
void ReflectorModule__clear_all_2_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=RF(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x190/8])(m,p1); }
// x3 scratch → 3 body params
void* ReflectorModule__get_center_pos_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) asm("_ZN3app8lua_bind36ReflectorModule__get_center_pos_implEPNS_26BattleObjectModuleAccessorE");
void* ReflectorModule__get_center_pos_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=RF(a); return reinterpret_cast<void*(*)(void*,u64,u64)>(VT(m)[0x198/8])(m,p1,p2); }
// x2 scratch → 2 body params
void* ReflectorModule__get_lr_impl(BattleObjectModuleAccessor* a,u64 p1) asm("_ZN3app8lua_bind28ReflectorModule__get_lr_implEPNS_26BattleObjectModuleAccessorE");
void* ReflectorModule__get_lr_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=RF(a); return reinterpret_cast<void*(*)(void*,u64)>(VT(m)[0x1a0/8])(m,p1); }
u32 ReflectorModule__get_group_num_impl(BattleObjectModuleAccessor* a) { auto* m=RF(a); return reinterpret_cast<u32(*)(void*)>(VT(m)[0x1A8/8])(m); }
// x2 scratch → 2 body params
void* ReflectorModule__get_pos_x_impl(BattleObjectModuleAccessor* a,u64 p1) asm("_ZN3app8lua_bind31ReflectorModule__get_pos_x_implEPNS_26BattleObjectModuleAccessorE");
void* ReflectorModule__get_pos_x_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=RF(a); return reinterpret_cast<void*(*)(void*,u64)>(VT(m)[0x1b0/8])(m,p1); }
// x3 scratch → 3 body params
void ReflectorModule__set_target_property_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) asm("_ZN3app8lua_bind41ReflectorModule__set_target_property_implEPNS_26BattleObjectModuleAccessorEy");
void ReflectorModule__set_target_property_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=RF(a); reinterpret_cast<void(*)(void*,u64,u64)>(VT(m)[0x1b8/8])(m,p1,p2); }
// x3 scratch → 3 body params
void ReflectorModule__set_target_category_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) asm("_ZN3app8lua_bind41ReflectorModule__set_target_category_implEPNS_26BattleObjectModuleAccessorEy");
void ReflectorModule__set_target_category_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=RF(a); reinterpret_cast<void(*)(void*,u64,u64)>(VT(m)[0x1c0/8])(m,p1,p2); }
void ReflectorModule__sleep_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=RF(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x1d0/8])(m,p1); }
} // namespace app::lua_bind
