#include "app/BattleObjectModuleAccessor.h"
#define AM(a) (*reinterpret_cast<void**>(reinterpret_cast<u8*>(a) + 0xA0))
#define VT(m) (*reinterpret_cast<void***>(m))
namespace app::lua_bind {
bool AttackModule__is_attack_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { auto* m=AM(a); return reinterpret_cast<bool(*)(void*,u64,bool)>(VT(m)[0xC8/8])(m,p1,p2); }
bool AttackModule__is_invalid_invincible_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { auto* m=AM(a); return reinterpret_cast<bool(*)(void*,u64,bool)>(VT(m)[0xD8/8])(m,p1,p2); }
bool AttackModule__is_invalid_xlu_impl(BattleObjectModuleAccessor* a,u64 p1,bool p2) { auto* m=AM(a); return reinterpret_cast<bool(*)(void*,u64,bool)>(VT(m)[0xE8/8])(m,p1,p2); }
bool AttackModule__is_hit_abs_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=AM(a); return reinterpret_cast<bool(*)(void*,u64)>(VT(m)[0xF0/8])(m,p1); }
bool AttackModule__is_infliction_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=AM(a); return reinterpret_cast<bool(*)(void*,u64)>(VT(m)[0x3C0/8])(m,p1); }
bool AttackModule__is_infliction_status_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=AM(a); return reinterpret_cast<bool(*)(void*,u64)>(VT(m)[0x3D0/8])(m,p1); }
bool AttackModule__is_power_up_reaction_impl(BattleObjectModuleAccessor* a) { auto* m=AM(a); return reinterpret_cast<bool(*)(void*)>(VT(m)[0x5A0/8])(m); }
bool AttackModule__is_attack_occur_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=AM(a); return reinterpret_cast<bool(*)(void*,u64)>(VT(m)[0x5C8/8])(m,p1); }
bool AttackModule__is_constraint_pos_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=AM(a); return reinterpret_cast<bool(*)(void*,u64)>(VT(m)[0x5D8/8])(m,p1); }
bool AttackModule__is_no_dead_damage_fly_effect_impl(BattleObjectModuleAccessor* a) { auto* m=AM(a); return reinterpret_cast<bool(*)(void*)>(VT(m)[0x5E8/8])(m); }
bool AttackModule__is_critical_attack_impl(BattleObjectModuleAccessor* a) { auto* m=AM(a); return reinterpret_cast<bool(*)(void*)>(VT(m)[0x6D8/8])(m); }
void AttackModule__set_is_critical_attack_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=AM(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x6F0/8])(m,p1); }
} // namespace app::lua_bind
