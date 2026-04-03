#include "app/BattleObjectModuleAccessor.h"
#define HM(a) (a->hit_module)
#define VT(m) (*reinterpret_cast<void***>(m))
namespace app::lua_bind {
void HitModule__clean_impl(BattleObjectModuleAccessor* a) { auto* m=HM(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x58/8])(m); }
void HitModule__reset_status_all_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=HM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x88/8])(m,p1); }
void HitModule__set_status_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3) asm("_ZN3app8lua_bind26HitModule__set_status_implEPNS_26BattleObjectModuleAccessorEy");
void HitModule__set_status_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3) { auto* m=HM(a); reinterpret_cast<void(*)(void*,u64,u64,u64)>(VT(m)[0xb0/8])(m,p1,p2,p3); }
void HitModule__set_status_joint_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3) asm("_ZN3app8lua_bind32HitModule__set_status_joint_implEPNS_26BattleObjectModuleAccessorEy");
void HitModule__set_status_joint_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3) { auto* m=HM(a); reinterpret_cast<void(*)(void*,u64,u64,u64)>(VT(m)[0xb8/8])(m,p1,p2,p3); }
void HitModule__set_status_joint_default_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3) asm("_ZN3app8lua_bind40HitModule__set_status_joint_default_implEPNS_26BattleObjectModuleAccessorEy");
void HitModule__set_status_joint_default_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3) { auto* m=HM(a); reinterpret_cast<void(*)(void*,u64,u64,u64)>(VT(m)[0xc0/8])(m,p1,p2,p3); }
void HitModule__set_status_all_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) asm("_ZN3app8lua_bind30HitModule__set_status_all_implEPNS_26BattleObjectModuleAccessorEy");
void HitModule__set_status_all_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=HM(a); reinterpret_cast<void(*)(void*,u64,u64)>(VT(m)[0xc8/8])(m,p1,p2); }
void HitModule__set_whole_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) asm("_ZN3app8lua_bind25HitModule__set_whole_implEPNS_26BattleObjectModuleAccessorEy");
void HitModule__set_whole_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=HM(a); reinterpret_cast<void(*)(void*,u64,u64)>(VT(m)[0xd0/8])(m,p1,p2); }
void* HitModule__get_whole_impl(BattleObjectModuleAccessor* a,u64 p1) asm("_ZN3app8lua_bind25HitModule__get_whole_implEPNS_26BattleObjectModuleAccessorE");
void* HitModule__get_whole_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=HM(a); return reinterpret_cast<void*(*)(void*,u64)>(VT(m)[0xd8/8])(m,p1); }
void HitModule__set_check_catch_impl(BattleObjectModuleAccessor* a,bool p1,u64 p2) asm("_ZN3app8lua_bind31HitModule__set_check_catch_implEPNS_26BattleObjectModuleAccessorEb");
void HitModule__set_check_catch_impl(BattleObjectModuleAccessor* a,bool p1,u64 p2) { auto* m=HM(a); reinterpret_cast<void(*)(void*,bool,u64)>(VT(m)[0xe8/8])(m,p1,p2); }
void HitModule__cancel_xlu_global_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=HM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x110/8])(m,p1); }
void HitModule__set_xlu_frame_global_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) asm("_ZN3app8lua_bind36HitModule__set_xlu_frame_global_implEPNS_26BattleObjectModuleAccessorEy");
void HitModule__set_xlu_frame_global_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=HM(a); reinterpret_cast<void(*)(void*,u64,u64)>(VT(m)[0x118/8])(m,p1,p2); }
void HitModule__set_invincible_frame_global_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2,u64 p3) asm("_ZN3app8lua_bind43HitModule__set_invincible_frame_global_implEPNS_26BattleObjectModuleAccessorEyb");
void HitModule__set_invincible_frame_global_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2,u64 p3) { auto* m=HM(a); reinterpret_cast<void(*)(void*,u64,bool,u64)>(VT(m)[0x130/8])(m,p1,p2,p3); }
void* HitModule__get_status_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) asm("_ZN3app8lua_bind26HitModule__get_status_implEPNS_26BattleObjectModuleAccessorEy");
void* HitModule__get_status_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=HM(a); return reinterpret_cast<void*(*)(void*,u64,u64)>(VT(m)[0x148/8])(m,p1,p2); }
void* HitModule__get_total_status_impl(BattleObjectModuleAccessor* a,u64 p1) asm("_ZN3app8lua_bind32HitModule__get_total_status_implEPNS_26BattleObjectModuleAccessorE");
void* HitModule__get_total_status_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=HM(a); return reinterpret_cast<void*(*)(void*,u64)>(VT(m)[0x150/8])(m,p1); }
void* HitModule__get_total_status_disguise_impl(BattleObjectModuleAccessor* a,u64 p1) asm("_ZN3app8lua_bind41HitModule__get_total_status_disguise_implEPNS_26BattleObjectModuleAccessorE");
void* HitModule__get_total_status_disguise_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=HM(a); return reinterpret_cast<void*(*)(void*,u64)>(VT(m)[0x158/8])(m,p1); }
void HitModule__set_total_status_disguise_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) asm("_ZN3app8lua_bind41HitModule__set_total_status_disguise_implEPNS_26BattleObjectModuleAccessorEy");
void HitModule__set_total_status_disguise_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=HM(a); reinterpret_cast<void(*)(void*,u64,u64)>(VT(m)[0x160/8])(m,p1,p2); }
u32 HitModule__get_part_size_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=HM(a); return reinterpret_cast<u32(*)(void*,u64)>(VT(m)[0x170/8])(m,p1); }
void HitModule__set_no_team_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=HM(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x188/8])(m,p1); }
void HitModule__set_hit_stop_mul_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=HM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x1E8/8])(m,p1); }
void* HitModule__get_center_pos_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) asm("_ZN3app8lua_bind30HitModule__get_center_pos_implEPNS_26BattleObjectModuleAccessorEy");
void* HitModule__get_center_pos_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=HM(a); return reinterpret_cast<void*(*)(void*,u64,u64)>(VT(m)[0x200/8])(m,p1,p2); }
void HitModule__set_defense_mul_status_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind38HitModule__set_defense_mul_status_implEPNS_26BattleObjectModuleAccessorEy");
void HitModule__set_defense_mul_status_impl(BattleObjectModuleAccessor* a) { auto* m=HM(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x210/8])(m); }
void* HitModule__exist_log_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) asm("_ZN3app8lua_bind25HitModule__exist_log_implEPNS_26BattleObjectModuleAccessorEy");
void* HitModule__exist_log_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=HM(a); return reinterpret_cast<void*(*)(void*,u64,u64)>(VT(m)[0x228/8])(m,p1,p2); }
void HitModule__sleep_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=HM(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x70/8])(m,p1); }
void HitModule__set_xlu_global_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=HM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x108/8])(m,p1); }
void HitModule__set_reaction_frame_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=HM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x1d8/8])(m,p1); }
} // namespace app::lua_bind
