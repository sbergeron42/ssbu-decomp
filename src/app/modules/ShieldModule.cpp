#include "app/BattleObjectModuleAccessor.h"
#include "app/modules/ShieldModule.h"
#define SM(a) static_cast<ShieldModule*>((a)->shield_module)
namespace app::lua_bind {
void ShieldModule__clean_impl(BattleObjectModuleAccessor* a) { SM(a)->clean(); }
bool ShieldModule__is_shield_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) asm("_ZN3app8lua_bind28ShieldModule__is_shield_implEPNS_26BattleObjectModuleAccessorE");
bool ShieldModule__is_shield_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { return SM(a)->is_shield(p1,p2); }
void ShieldModule__set_size_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) asm("_ZN3app8lua_bind27ShieldModule__set_size_implEPNS_26BattleObjectModuleAccessorEy");
void ShieldModule__set_size_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { SM(a)->set_size(p1,p2); }
void ShieldModule__set_status_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3) asm("_ZN3app8lua_bind29ShieldModule__set_status_implEPNS_26BattleObjectModuleAccessorEy");
void ShieldModule__set_status_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3) { SM(a)->set_status(p1,p2,p3); }
void ShieldModule__set_status_all_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) asm("_ZN3app8lua_bind33ShieldModule__set_status_all_implEPNS_26BattleObjectModuleAccessorEy");
void ShieldModule__set_status_all_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { SM(a)->set_status_all(p1,p2); }
bool ShieldModule__is_turn_impl(BattleObjectModuleAccessor* a,u64 p1) asm("_ZN3app8lua_bind26ShieldModule__is_turn_implEPNS_26BattleObjectModuleAccessorE");
bool ShieldModule__is_turn_impl(BattleObjectModuleAccessor* a,u64 p1) { return SM(a)->is_turn(p1); }
bool ShieldModule__is_front_impl(BattleObjectModuleAccessor* a,u64 p1) asm("_ZN3app8lua_bind27ShieldModule__is_front_implEPNS_26BattleObjectModuleAccessorE");
bool ShieldModule__is_front_impl(BattleObjectModuleAccessor* a,u64 p1) { return SM(a)->is_front(p1); }
bool ShieldModule__is_hop_impl(BattleObjectModuleAccessor* a,u64 p1) asm("_ZN3app8lua_bind25ShieldModule__is_hop_implEPNS_26BattleObjectModuleAccessorE");
bool ShieldModule__is_hop_impl(BattleObjectModuleAccessor* a,u64 p1) { return SM(a)->is_hop(p1); }
void* ShieldModule__get_hop_angle_impl(BattleObjectModuleAccessor* a,u64 p1) asm("_ZN3app8lua_bind32ShieldModule__get_hop_angle_implEPNS_26BattleObjectModuleAccessorE");
void* ShieldModule__get_hop_angle_impl(BattleObjectModuleAccessor* a,u64 p1) { return SM(a)->get_hop_angle(p1); }
bool ShieldModule__is_no_hop_impl(BattleObjectModuleAccessor* a,u64 p1) asm("_ZN3app8lua_bind28ShieldModule__is_no_hop_implEPNS_26BattleObjectModuleAccessorE");
bool ShieldModule__is_no_hop_impl(BattleObjectModuleAccessor* a,u64 p1) { return SM(a)->is_no_hop(p1); }
void ShieldModule__set_turn_impl(BattleObjectModuleAccessor* a,bool p1,u64 p2) asm("_ZN3app8lua_bind27ShieldModule__set_turn_implEPNS_26BattleObjectModuleAccessorEb");
void ShieldModule__set_turn_impl(BattleObjectModuleAccessor* a,bool p1,u64 p2) { SM(a)->set_turn(p1,p2); }
void ShieldModule__set_front_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) asm("_ZN3app8lua_bind28ShieldModule__set_front_implEPNS_26BattleObjectModuleAccessorEy");
void ShieldModule__set_front_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { SM(a)->set_front(p1,p2); }
void ShieldModule__set_hop_impl(BattleObjectModuleAccessor* a,bool p1,u64 p2) asm("_ZN3app8lua_bind26ShieldModule__set_hop_implEPNS_26BattleObjectModuleAccessorEb");
void ShieldModule__set_hop_impl(BattleObjectModuleAccessor* a,bool p1,u64 p2) { SM(a)->set_hop(p1,p2); }
void ShieldModule__set_attack_mul_impl(BattleObjectModuleAccessor* a,u64 p1) { SM(a)->set_attack_mul(p1); }
void* ShieldModule__get_attack_mul_impl(BattleObjectModuleAccessor* a,u64 p1) asm("_ZN3app8lua_bind33ShieldModule__get_attack_mul_implEPNS_26BattleObjectModuleAccessorE");
void* ShieldModule__get_attack_mul_impl(BattleObjectModuleAccessor* a,u64 p1) { return SM(a)->get_attack_mul(p1); }
void ShieldModule__set_speed_mul_impl(BattleObjectModuleAccessor* a,u64 p1) { SM(a)->set_speed_mul(p1); }
void* ShieldModule__get_speed_mul_impl(BattleObjectModuleAccessor* a,u64 p1) asm("_ZN3app8lua_bind32ShieldModule__get_speed_mul_implEPNS_26BattleObjectModuleAccessorE");
void* ShieldModule__get_speed_mul_impl(BattleObjectModuleAccessor* a,u64 p1) { return SM(a)->get_speed_mul(p1); }
void ShieldModule__set_life_mul_impl(BattleObjectModuleAccessor* a,u64 p1) { SM(a)->set_life_mul(p1); }
void* ShieldModule__get_life_mul_impl(BattleObjectModuleAccessor* a,u64 p1) asm("_ZN3app8lua_bind31ShieldModule__get_life_mul_implEPNS_26BattleObjectModuleAccessorE");
void* ShieldModule__get_life_mul_impl(BattleObjectModuleAccessor* a,u64 p1) { return SM(a)->get_life_mul(p1); }
void ShieldModule__set_attack_limit_impl(BattleObjectModuleAccessor* a,u64 p1) { SM(a)->set_attack_limit(p1); }
void* ShieldModule__get_attack_limit_impl(BattleObjectModuleAccessor* a,u64 p1) asm("_ZN3app8lua_bind35ShieldModule__get_attack_limit_implEPNS_26BattleObjectModuleAccessorE");
void* ShieldModule__get_attack_limit_impl(BattleObjectModuleAccessor* a,u64 p1) { return SM(a)->get_attack_limit(p1); }
void ShieldModule__set_hit_stop_mul_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind35ShieldModule__set_hit_stop_mul_implEPNS_26BattleObjectModuleAccessorEy");
void ShieldModule__set_hit_stop_mul_impl(BattleObjectModuleAccessor* a) { SM(a)->set_hit_stop_mul(); }
bool ShieldModule__is_no_m_ball_impl(BattleObjectModuleAccessor* a,u64 p1) asm("_ZN3app8lua_bind31ShieldModule__is_no_m_ball_implEPNS_26BattleObjectModuleAccessorE");
bool ShieldModule__is_no_m_ball_impl(BattleObjectModuleAccessor* a,u64 p1) { return SM(a)->is_no_m_ball(p1); }
void* ShieldModule__get_part_size_impl(BattleObjectModuleAccessor* a,u64 p1) asm("_ZN3app8lua_bind32ShieldModule__get_part_size_implEPNS_26BattleObjectModuleAccessorE");
void* ShieldModule__get_part_size_impl(BattleObjectModuleAccessor* a,u64 p1) { return SM(a)->get_part_size(p1); }
u32 ShieldModule__get_team_no_impl(BattleObjectModuleAccessor* a) { return SM(a)->get_team_no(); }
void ShieldModule__set_no_team_impl(BattleObjectModuleAccessor* a,bool p1) { SM(a)->set_no_team(p1); }
void ShieldModule__set_shield_type_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3) asm("_ZN3app8lua_bind34ShieldModule__set_shield_type_implEPNS_26BattleObjectModuleAccessorEy");
void ShieldModule__set_shield_type_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3) { SM(a)->set_shield_type(p1,p2,p3); }
void ShieldModule__clear_all_impl(BattleObjectModuleAccessor* a) { SM(a)->clear_all(); }
void ShieldModule__clear_all_2_impl(BattleObjectModuleAccessor* a,u64 p1) asm("_ZN3app8lua_bind30ShieldModule__clear_all_2_implEPNS_26BattleObjectModuleAccessorE");
void ShieldModule__clear_all_2_impl(BattleObjectModuleAccessor* a,u64 p1) { SM(a)->clear_all_2(p1); }
void* ShieldModule__get_center_pos_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) asm("_ZN3app8lua_bind33ShieldModule__get_center_pos_implEPNS_26BattleObjectModuleAccessorE");
void* ShieldModule__get_center_pos_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { return SM(a)->get_center_pos(p1,p2); }
void* ShieldModule__get_lr_impl(BattleObjectModuleAccessor* a,u64 p1) asm("_ZN3app8lua_bind25ShieldModule__get_lr_implEPNS_26BattleObjectModuleAccessorE");
void* ShieldModule__get_lr_impl(BattleObjectModuleAccessor* a,u64 p1) { return SM(a)->get_lr(p1); }
u32 ShieldModule__get_group_num_impl(BattleObjectModuleAccessor* a) { return SM(a)->get_group_num(); }
void* ShieldModule__get_pos_x_impl(BattleObjectModuleAccessor* a,u64 p1) asm("_ZN3app8lua_bind28ShieldModule__get_pos_x_implEPNS_26BattleObjectModuleAccessorE");
void* ShieldModule__get_pos_x_impl(BattleObjectModuleAccessor* a,u64 p1) { return SM(a)->get_pos_x(p1); }
void ShieldModule__set_target_property_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) asm("_ZN3app8lua_bind38ShieldModule__set_target_property_implEPNS_26BattleObjectModuleAccessorEy");
void ShieldModule__set_target_property_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { SM(a)->set_target_property(p1,p2); }
void ShieldModule__set_target_category_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) asm("_ZN3app8lua_bind38ShieldModule__set_target_category_implEPNS_26BattleObjectModuleAccessorEy");
void ShieldModule__set_target_category_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { SM(a)->set_target_category(p1,p2); }
void ShieldModule__sleep_impl(BattleObjectModuleAccessor* a,bool p1) { SM(a)->sleep(p1); }
void ShieldModule__set_hit_stop_slow_impl(BattleObjectModuleAccessor* a,bool p1) { SM(a)->set_hit_stop_slow(p1); }
} // namespace app::lua_bind
