#include "app/BattleObjectModuleAccessor.h"
#include "app/modules/AbsorberModule.h"
#define AB(a) static_cast<AbsorberModule*>((a)->absorber_module)

namespace app::lua_bind {

void AbsorberModule__clean_impl(BattleObjectModuleAccessor* a) { AB(a)->clean(); }
bool AbsorberModule__is_shield_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2) asm("_ZN3app8lua_bind30AbsorberModule__is_shield_implEPNS_26BattleObjectModuleAccessorE");
bool AbsorberModule__is_shield_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2) { return AB(a)->is_shield(p1, p2); }
void AbsorberModule__set_size_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2) asm("_ZN3app8lua_bind29AbsorberModule__set_size_implEPNS_26BattleObjectModuleAccessorEy");
void AbsorberModule__set_size_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2) { AB(a)->set_size(p1, p2); }
void AbsorberModule__set_status_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3) asm("_ZN3app8lua_bind31AbsorberModule__set_status_implEPNS_26BattleObjectModuleAccessorEy");
void AbsorberModule__set_status_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3) { AB(a)->set_status(p1, p2, p3); }
void AbsorberModule__set_status_all_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2) asm("_ZN3app8lua_bind35AbsorberModule__set_status_all_implEPNS_26BattleObjectModuleAccessorEy");
void AbsorberModule__set_status_all_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2) { AB(a)->set_status_all(p1, p2); }
bool AbsorberModule__is_turn_impl(BattleObjectModuleAccessor* a, u64 p1) asm("_ZN3app8lua_bind28AbsorberModule__is_turn_implEPNS_26BattleObjectModuleAccessorE");
bool AbsorberModule__is_turn_impl(BattleObjectModuleAccessor* a, u64 p1) { return AB(a)->is_turn(p1); }
bool AbsorberModule__is_front_impl(BattleObjectModuleAccessor* a, u64 p1) asm("_ZN3app8lua_bind29AbsorberModule__is_front_implEPNS_26BattleObjectModuleAccessorE");
bool AbsorberModule__is_front_impl(BattleObjectModuleAccessor* a, u64 p1) { return AB(a)->is_front(p1); }
bool AbsorberModule__is_hop_impl(BattleObjectModuleAccessor* a, u64 p1) asm("_ZN3app8lua_bind27AbsorberModule__is_hop_implEPNS_26BattleObjectModuleAccessorE");
bool AbsorberModule__is_hop_impl(BattleObjectModuleAccessor* a, u64 p1) { return AB(a)->is_hop(p1); }
void* AbsorberModule__get_hop_angle_impl(BattleObjectModuleAccessor* a, u64 p1) asm("_ZN3app8lua_bind34AbsorberModule__get_hop_angle_implEPNS_26BattleObjectModuleAccessorE");
void* AbsorberModule__get_hop_angle_impl(BattleObjectModuleAccessor* a, u64 p1) { return AB(a)->get_hop_angle(p1); }
bool AbsorberModule__is_no_hop_impl(BattleObjectModuleAccessor* a, u64 p1) asm("_ZN3app8lua_bind30AbsorberModule__is_no_hop_implEPNS_26BattleObjectModuleAccessorE");
bool AbsorberModule__is_no_hop_impl(BattleObjectModuleAccessor* a, u64 p1) { return AB(a)->is_no_hop(p1); }
void AbsorberModule__set_turn_impl(BattleObjectModuleAccessor* a, bool p1, u64 p2) asm("_ZN3app8lua_bind29AbsorberModule__set_turn_implEPNS_26BattleObjectModuleAccessorEb");
void AbsorberModule__set_turn_impl(BattleObjectModuleAccessor* a, bool p1, u64 p2) { AB(a)->set_turn(p1, p2); }
void AbsorberModule__set_front_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2) asm("_ZN3app8lua_bind30AbsorberModule__set_front_implEPNS_26BattleObjectModuleAccessorEy");
void AbsorberModule__set_front_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2) { AB(a)->set_front(p1, p2); }
void AbsorberModule__set_hop_impl(BattleObjectModuleAccessor* a, bool p1, u64 p2) asm("_ZN3app8lua_bind28AbsorberModule__set_hop_implEPNS_26BattleObjectModuleAccessorEb");
void AbsorberModule__set_hop_impl(BattleObjectModuleAccessor* a, bool p1, u64 p2) { AB(a)->set_hop(p1, p2); }
void AbsorberModule__set_attack_mul_impl(BattleObjectModuleAccessor* a, u64 p1) { AB(a)->set_attack_mul(p1); }
void* AbsorberModule__get_attack_mul_impl(BattleObjectModuleAccessor* a, u64 p1) asm("_ZN3app8lua_bind35AbsorberModule__get_attack_mul_implEPNS_26BattleObjectModuleAccessorE");
void* AbsorberModule__get_attack_mul_impl(BattleObjectModuleAccessor* a, u64 p1) { return AB(a)->get_attack_mul(p1); }
void AbsorberModule__set_speed_mul_impl(BattleObjectModuleAccessor* a, u64 p1) { AB(a)->set_speed_mul(p1); }
void* AbsorberModule__get_speed_mul_impl(BattleObjectModuleAccessor* a, u64 p1) asm("_ZN3app8lua_bind34AbsorberModule__get_speed_mul_implEPNS_26BattleObjectModuleAccessorE");
void* AbsorberModule__get_speed_mul_impl(BattleObjectModuleAccessor* a, u64 p1) { return AB(a)->get_speed_mul(p1); }
void AbsorberModule__set_life_mul_impl(BattleObjectModuleAccessor* a, u64 p1) { AB(a)->set_life_mul(p1); }
void* AbsorberModule__get_life_mul_impl(BattleObjectModuleAccessor* a, u64 p1) asm("_ZN3app8lua_bind33AbsorberModule__get_life_mul_implEPNS_26BattleObjectModuleAccessorE");
void* AbsorberModule__get_life_mul_impl(BattleObjectModuleAccessor* a, u64 p1) { return AB(a)->get_life_mul(p1); }
void AbsorberModule__set_attack_limit_impl(BattleObjectModuleAccessor* a, u64 p1) { AB(a)->set_attack_limit(p1); }
void* AbsorberModule__get_attack_limit_impl(BattleObjectModuleAccessor* a, u64 p1) asm("_ZN3app8lua_bind37AbsorberModule__get_attack_limit_implEPNS_26BattleObjectModuleAccessorE");
void* AbsorberModule__get_attack_limit_impl(BattleObjectModuleAccessor* a, u64 p1) { return AB(a)->get_attack_limit(p1); }
void AbsorberModule__set_hit_stop_mul_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind37AbsorberModule__set_hit_stop_mul_implEPNS_26BattleObjectModuleAccessorEy");
void AbsorberModule__set_hit_stop_mul_impl(BattleObjectModuleAccessor* a) { AB(a)->set_hit_stop_mul(); }
bool AbsorberModule__is_no_m_ball_impl(BattleObjectModuleAccessor* a, u64 p1) asm("_ZN3app8lua_bind33AbsorberModule__is_no_m_ball_implEPNS_26BattleObjectModuleAccessorE");
bool AbsorberModule__is_no_m_ball_impl(BattleObjectModuleAccessor* a, u64 p1) { return AB(a)->is_no_m_ball(p1); }
void* AbsorberModule__get_part_size_impl(BattleObjectModuleAccessor* a, u64 p1) asm("_ZN3app8lua_bind34AbsorberModule__get_part_size_implEPNS_26BattleObjectModuleAccessorE");
void* AbsorberModule__get_part_size_impl(BattleObjectModuleAccessor* a, u64 p1) { return AB(a)->get_part_size(p1); }
u32 AbsorberModule__get_team_no_impl(BattleObjectModuleAccessor* a) { return AB(a)->get_team_no(); }
void AbsorberModule__set_no_team_impl(BattleObjectModuleAccessor* a, bool p1) { AB(a)->set_no_team(p1); }
void AbsorberModule__set_shield_type_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3) asm("_ZN3app8lua_bind36AbsorberModule__set_shield_type_implEPNS_26BattleObjectModuleAccessorEy");
void AbsorberModule__set_shield_type_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3) { AB(a)->set_shield_type(p1, p2, p3); }
void AbsorberModule__clear_all_impl(BattleObjectModuleAccessor* a) { AB(a)->clear_all(); }
void AbsorberModule__clear_all_2_impl(BattleObjectModuleAccessor* a, u64 p1) asm("_ZN3app8lua_bind32AbsorberModule__clear_all_2_implEPNS_26BattleObjectModuleAccessorE");
void AbsorberModule__clear_all_2_impl(BattleObjectModuleAccessor* a, u64 p1) { AB(a)->clear_all_2(p1); }
void* AbsorberModule__get_center_pos_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2) asm("_ZN3app8lua_bind35AbsorberModule__get_center_pos_implEPNS_26BattleObjectModuleAccessorE");
void* AbsorberModule__get_center_pos_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2) { return AB(a)->get_center_pos(p1, p2); }
void* AbsorberModule__get_lr_impl(BattleObjectModuleAccessor* a, u64 p1) asm("_ZN3app8lua_bind27AbsorberModule__get_lr_implEPNS_26BattleObjectModuleAccessorE");
void* AbsorberModule__get_lr_impl(BattleObjectModuleAccessor* a, u64 p1) { return AB(a)->get_lr(p1); }
u32 AbsorberModule__get_group_num_impl(BattleObjectModuleAccessor* a) { return AB(a)->get_group_num(); }
void* AbsorberModule__get_pos_x_impl(BattleObjectModuleAccessor* a, u64 p1) asm("_ZN3app8lua_bind30AbsorberModule__get_pos_x_implEPNS_26BattleObjectModuleAccessorE");
void* AbsorberModule__get_pos_x_impl(BattleObjectModuleAccessor* a, u64 p1) { return AB(a)->get_pos_x(p1); }
void AbsorberModule__set_target_property_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2) asm("_ZN3app8lua_bind40AbsorberModule__set_target_property_implEPNS_26BattleObjectModuleAccessorEy");
void AbsorberModule__set_target_property_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2) { AB(a)->set_target_property(p1, p2); }
void AbsorberModule__set_target_category_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2) asm("_ZN3app8lua_bind40AbsorberModule__set_target_category_implEPNS_26BattleObjectModuleAccessorEy");
void AbsorberModule__set_target_category_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2) { AB(a)->set_target_category(p1, p2); }
void AbsorberModule__sleep_impl(BattleObjectModuleAccessor* a, bool p1) { AB(a)->sleep(p1); }

} // namespace app::lua_bind
