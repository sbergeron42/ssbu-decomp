#include "app/BattleObjectModuleAccessor.h"
#include "app/modules/HitModule.h"
#define HM(a) static_cast<HitModule*>((a)->hit_module)
namespace app::lua_bind {
void HitModule__clean_impl(BattleObjectModuleAccessor* a) { HM(a)->clean(); }
void HitModule__reset_status_all_impl(BattleObjectModuleAccessor* a,u64 p1) { HM(a)->reset_status_all(p1); }
void HitModule__set_status_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3) asm("_ZN3app8lua_bind26HitModule__set_status_implEPNS_26BattleObjectModuleAccessorEy");
void HitModule__set_status_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3) { HM(a)->set_status(p1,p2,p3); }
void HitModule__set_status_joint_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3) asm("_ZN3app8lua_bind32HitModule__set_status_joint_implEPNS_26BattleObjectModuleAccessorEy");
void HitModule__set_status_joint_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3) { HM(a)->set_status_joint(p1,p2,p3); }
void HitModule__set_status_joint_default_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3) asm("_ZN3app8lua_bind40HitModule__set_status_joint_default_implEPNS_26BattleObjectModuleAccessorEy");
void HitModule__set_status_joint_default_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3) { HM(a)->set_status_joint_default(p1,p2,p3); }
void HitModule__set_status_all_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) asm("_ZN3app8lua_bind30HitModule__set_status_all_implEPNS_26BattleObjectModuleAccessorEy");
void HitModule__set_status_all_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { HM(a)->set_status_all(p1,p2); }
void HitModule__set_whole_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) asm("_ZN3app8lua_bind25HitModule__set_whole_implEPNS_26BattleObjectModuleAccessorEy");
void HitModule__set_whole_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { HM(a)->set_whole(p1,p2); }
void* HitModule__get_whole_impl(BattleObjectModuleAccessor* a,u64 p1) asm("_ZN3app8lua_bind25HitModule__get_whole_implEPNS_26BattleObjectModuleAccessorE");
void* HitModule__get_whole_impl(BattleObjectModuleAccessor* a,u64 p1) { return HM(a)->get_whole(p1); }
void HitModule__set_check_catch_impl(BattleObjectModuleAccessor* a,bool p1,u64 p2) asm("_ZN3app8lua_bind31HitModule__set_check_catch_implEPNS_26BattleObjectModuleAccessorEb");
void HitModule__set_check_catch_impl(BattleObjectModuleAccessor* a,bool p1,u64 p2) { HM(a)->set_check_catch(p1,p2); }
void HitModule__cancel_xlu_global_impl(BattleObjectModuleAccessor* a,u64 p1) { HM(a)->cancel_xlu_global(p1); }
void HitModule__set_xlu_frame_global_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) asm("_ZN3app8lua_bind36HitModule__set_xlu_frame_global_implEPNS_26BattleObjectModuleAccessorEy");
void HitModule__set_xlu_frame_global_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { HM(a)->set_xlu_frame_global(p1,p2); }
void HitModule__set_invincible_frame_global_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2,u64 p3) asm("_ZN3app8lua_bind43HitModule__set_invincible_frame_global_implEPNS_26BattleObjectModuleAccessorEyb");
void HitModule__set_invincible_frame_global_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2,u64 p3) { HM(a)->set_invincible_frame_global(p1,p2,p3); }
void* HitModule__get_status_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) asm("_ZN3app8lua_bind26HitModule__get_status_implEPNS_26BattleObjectModuleAccessorEy");
void* HitModule__get_status_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { return HM(a)->get_status(p1,p2); }
void* HitModule__get_total_status_impl(BattleObjectModuleAccessor* a,u64 p1) asm("_ZN3app8lua_bind32HitModule__get_total_status_implEPNS_26BattleObjectModuleAccessorE");
void* HitModule__get_total_status_impl(BattleObjectModuleAccessor* a,u64 p1) { return HM(a)->get_total_status(p1); }
void* HitModule__get_total_status_disguise_impl(BattleObjectModuleAccessor* a,u64 p1) asm("_ZN3app8lua_bind41HitModule__get_total_status_disguise_implEPNS_26BattleObjectModuleAccessorE");
void* HitModule__get_total_status_disguise_impl(BattleObjectModuleAccessor* a,u64 p1) { return HM(a)->get_total_status_disguise(p1); }
void HitModule__set_total_status_disguise_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) asm("_ZN3app8lua_bind41HitModule__set_total_status_disguise_implEPNS_26BattleObjectModuleAccessorEy");
void HitModule__set_total_status_disguise_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { HM(a)->set_total_status_disguise(p1,p2); }
u32 HitModule__get_part_size_impl(BattleObjectModuleAccessor* a,u64 p1) { return HM(a)->get_part_size(p1); }
void HitModule__set_no_team_impl(BattleObjectModuleAccessor* a,bool p1) { HM(a)->set_no_team(p1); }
void HitModule__set_hit_stop_mul_impl(BattleObjectModuleAccessor* a,u64 p1) { HM(a)->set_hit_stop_mul(p1); }
void* HitModule__get_center_pos_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) asm("_ZN3app8lua_bind30HitModule__get_center_pos_implEPNS_26BattleObjectModuleAccessorEy");
void* HitModule__get_center_pos_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { return HM(a)->get_center_pos(p1,p2); }
void HitModule__set_defense_mul_status_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind38HitModule__set_defense_mul_status_implEPNS_26BattleObjectModuleAccessorEy");
void HitModule__set_defense_mul_status_impl(BattleObjectModuleAccessor* a) { HM(a)->set_defense_mul_status(); }
void* HitModule__exist_log_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) asm("_ZN3app8lua_bind25HitModule__exist_log_implEPNS_26BattleObjectModuleAccessorEy");
void* HitModule__exist_log_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { return HM(a)->exist_log(p1,p2); }
void HitModule__sleep_impl(BattleObjectModuleAccessor* a,bool p1) { HM(a)->sleep(p1); }
void HitModule__set_xlu_global_impl(BattleObjectModuleAccessor* a,u64 p1) { HM(a)->set_xlu_global(p1); }
void HitModule__set_reaction_frame_impl(BattleObjectModuleAccessor* a,u64 p1) { HM(a)->set_reaction_frame(p1); }
} // namespace app::lua_bind
