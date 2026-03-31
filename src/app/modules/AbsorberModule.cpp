#include "app/BattleObjectModuleAccessor.h"
#define AB(a) (*reinterpret_cast<void**>(reinterpret_cast<u8*>(a) + 0x110))
#define VT(m) (*reinterpret_cast<void***>(m))
namespace app::lua_bind {
void AbsorberModule__clean_impl(BattleObjectModuleAccessor* a) { auto* m=AB(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x50/8])(m); }
bool AbsorberModule__is_shield_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x110)); return reinterpret_cast<bool(*)(void*,u64,u64)>(VT(m)[0x88/8])(m,p1,p2); }
bool AbsorberModule__is_turn_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x110)); return reinterpret_cast<bool(*)(void*,u64)>(VT(m)[0xa8/8])(m,p1); }
bool AbsorberModule__is_front_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x110)); return reinterpret_cast<bool(*)(void*,u64)>(VT(m)[0xb0/8])(m,p1); }
bool AbsorberModule__is_hop_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x110)); return reinterpret_cast<bool(*)(void*,u64)>(VT(m)[0xb8/8])(m,p1); }
void* AbsorberModule__get_hop_angle_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x110)); return reinterpret_cast<void*(*)(void*,u64)>(VT(m)[0xc0/8])(m,p1); }
bool AbsorberModule__is_no_hop_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x110)); return reinterpret_cast<bool(*)(void*,u64)>(VT(m)[0xc8/8])(m,p1); }
void* AbsorberModule__get_attack_mul_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x110)); return reinterpret_cast<void*(*)(void*,u64)>(VT(m)[0xf0/8])(m,p1); }
void* AbsorberModule__get_speed_mul_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x110)); return reinterpret_cast<void*(*)(void*,u64)>(VT(m)[0x100/8])(m,p1); }
void* AbsorberModule__get_life_mul_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x110)); return reinterpret_cast<void*(*)(void*,u64)>(VT(m)[0x110/8])(m,p1); }
void* AbsorberModule__get_attack_limit_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x110)); return reinterpret_cast<void*(*)(void*,u64)>(VT(m)[0x120/8])(m,p1); }
bool AbsorberModule__is_no_m_ball_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x110)); return reinterpret_cast<bool(*)(void*,u64)>(VT(m)[0x140/8])(m,p1); }
void* AbsorberModule__get_part_size_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x110)); return reinterpret_cast<void*(*)(void*,u64)>(VT(m)[0x148/8])(m,p1); }
u32 AbsorberModule__get_team_no_impl(BattleObjectModuleAccessor* a) { auto* m=AB(a); return reinterpret_cast<u32(*)(void*)>(VT(m)[0x150/8])(m); }
void AbsorberModule__clear_all_impl(BattleObjectModuleAccessor* a) { auto* m=AB(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x188/8])(m); }
void AbsorberModule__clear_all_2_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x110)); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x190/8])(m,p1); }
void* AbsorberModule__get_center_pos_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x110)); return reinterpret_cast<void*(*)(void*,u64,u64)>(VT(m)[0x198/8])(m,p1,p2); }
void* AbsorberModule__get_lr_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x110)); return reinterpret_cast<void*(*)(void*,u64)>(VT(m)[0x1a0/8])(m,p1); }
u32 AbsorberModule__get_group_num_impl(BattleObjectModuleAccessor* a) { auto* m=AB(a); return reinterpret_cast<u32(*)(void*)>(VT(m)[0x1A8/8])(m); }
void* AbsorberModule__get_pos_x_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x110)); return reinterpret_cast<void*(*)(void*,u64)>(VT(m)[0x1b0/8])(m,p1); }
void AbsorberModule__set_size_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x110)); reinterpret_cast<void(*)(void*,u64,u64)>(VT(m)[0x90/8])(m,p1,p2); }
void AbsorberModule__set_status_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x110)); reinterpret_cast<void(*)(void*,u64,u64,u64)>(VT(m)[0x98/8])(m,p1,p2,p3); }
void AbsorberModule__set_status_all_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x110)); reinterpret_cast<void(*)(void*,u64,u64)>(VT(m)[0xa0/8])(m,p1,p2); }
void AbsorberModule__set_turn_impl(BattleObjectModuleAccessor* a,bool p1,u64 p2) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x110)); reinterpret_cast<void(*)(void*,bool,u64)>(VT(m)[0xd0/8])(m,p1,p2); }
void AbsorberModule__set_front_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x110)); reinterpret_cast<void(*)(void*,u64,u64)>(VT(m)[0xd8/8])(m,p1,p2); }
void AbsorberModule__set_hop_impl(BattleObjectModuleAccessor* a,bool p1,u64 p2) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x110)); reinterpret_cast<void(*)(void*,bool,u64)>(VT(m)[0xe0/8])(m,p1,p2); }
void AbsorberModule__set_attack_mul_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=AB(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0xe8/8])(m,p1); }
void AbsorberModule__set_speed_mul_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=AB(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0xf8/8])(m,p1); }
void AbsorberModule__set_life_mul_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=AB(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x108/8])(m,p1); }
void AbsorberModule__set_attack_limit_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=AB(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x118/8])(m,p1); }
void AbsorberModule__set_hit_stop_mul_impl(BattleObjectModuleAccessor* a) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x110)); reinterpret_cast<void(*)(void*)>(VT(m)[0x130/8])(m); }
void AbsorberModule__set_no_team_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=AB(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x158/8])(m,p1); }
void AbsorberModule__set_shield_type_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2,u64 p3) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x110)); reinterpret_cast<void(*)(void*,u64,u64,u64)>(VT(m)[0x160/8])(m,p1,p2,p3); }
void AbsorberModule__set_target_property_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x110)); reinterpret_cast<void(*)(void*,u64,u64)>(VT(m)[0x1b8/8])(m,p1,p2); }
void AbsorberModule__set_target_category_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=reinterpret_cast<void*>(*reinterpret_cast<u64*>(reinterpret_cast<u8*>(a)+0x110)); reinterpret_cast<void(*)(void*,u64,u64)>(VT(m)[0x1c0/8])(m,p1,p2); }
void AbsorberModule__sleep_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=AB(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x1d0/8])(m,p1); }
} // namespace app::lua_bind
