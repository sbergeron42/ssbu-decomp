#include "app/BattleObjectModuleAccessor.h"
#define RM(a) (*reinterpret_cast<void**>(reinterpret_cast<u8*>(a) + 0xF8))
#define VT(m) (*reinterpret_cast<void***>(m))
namespace app::lua_bind {
void ReflectModule__reset_info_impl(BattleObjectModuleAccessor* a) { auto* m=RM(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x50/8])(m); }
u32 ReflectModule__object_id_impl(BattleObjectModuleAccessor* a) { auto* m=RM(a); return reinterpret_cast<u32(*)(void*)>(VT(m)[0x58/8])(m); }
void ReflectModule__set_object_id_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=RM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x60/8])(m,p1); }
u32 ReflectModule__team_no_impl(BattleObjectModuleAccessor* a) { auto* m=RM(a); return reinterpret_cast<u32(*)(void*)>(VT(m)[0x68/8])(m); }
void ReflectModule__set_team_no_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=RM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x70/8])(m,p1); }
f32 ReflectModule__attack_mul_impl(BattleObjectModuleAccessor* a) { auto* m=RM(a); return reinterpret_cast<f32(*)(void*)>(VT(m)[0x78/8])(m); }
// x1 scratch → body needs 1 param
void ReflectModule__set_attack_mul_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind34ReflectModule__set_attack_mul_implEPNS_26BattleObjectModuleAccessorEy");
void ReflectModule__set_attack_mul_impl(BattleObjectModuleAccessor* a) { auto* m=RM(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x80/8])(m); }
f32 ReflectModule__speed_mul_impl(BattleObjectModuleAccessor* a) { auto* m=RM(a); return reinterpret_cast<f32(*)(void*)>(VT(m)[0x88/8])(m); }
// x1 scratch → body needs 1 param
void ReflectModule__set_speed_mul_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind33ReflectModule__set_speed_mul_implEPNS_26BattleObjectModuleAccessorEy");
void ReflectModule__set_speed_mul_impl(BattleObjectModuleAccessor* a) { auto* m=RM(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x90/8])(m); }
f32 ReflectModule__life_mul_impl(BattleObjectModuleAccessor* a) { auto* m=RM(a); return reinterpret_cast<f32(*)(void*)>(VT(m)[0x98/8])(m); }
// x1 scratch → body needs 1 param
void ReflectModule__set_life_mul_impl(BattleObjectModuleAccessor* a) asm("_ZN3app8lua_bind32ReflectModule__set_life_mul_implEPNS_26BattleObjectModuleAccessorEy");
void ReflectModule__set_life_mul_impl(BattleObjectModuleAccessor* a) { auto* m=RM(a); reinterpret_cast<void(*)(void*)>(VT(m)[0xa0/8])(m); }
bool ReflectModule__is_reflect_impl(BattleObjectModuleAccessor* a) { auto* m=RM(a); return reinterpret_cast<bool(*)(void*)>(VT(m)[0xa8/8])(m); }
void ReflectModule__set_no_speed_mul_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=RM(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0xb0/8])(m,p1); }
bool ReflectModule__is_count_max_impl(BattleObjectModuleAccessor* a) { auto* m=RM(a); return reinterpret_cast<bool(*)(void*)>(VT(m)[0xb8/8])(m); }
u32 ReflectModule__count_impl(BattleObjectModuleAccessor* a) { auto* m=RM(a); return reinterpret_cast<u32(*)(void*)>(VT(m)[0xc0/8])(m); }
f32 ReflectModule__get_reverse_lr_impl(BattleObjectModuleAccessor* a) { auto* m=RM(a); return reinterpret_cast<f32(*)(void*)>(VT(m)[0xd8/8])(m); }
void ReflectModule__set_collision_no_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=RM(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0xe0/8])(m,p1); }
} // namespace app::lua_bind
