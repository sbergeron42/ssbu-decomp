#include "app/BattleObjectModuleAccessor.h"

// DamageModule -- accessed via acc->damage_module (+0xA8)
#define DMG(acc) (acc->damage_module)
#define VT(mod) (*reinterpret_cast<void***>(mod))

namespace app::lua_bind {

// 710200b690 [vtable+0x50]
void DamageModule__sleep_impl(BattleObjectModuleAccessor* a, bool p1) {
    auto* m = DMG(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x50/8])(m,p1);
}
// 710200b6b0 [vtable+0x60]
void DamageModule__init_damage_impl(BattleObjectModuleAccessor* a) {
    auto* m = DMG(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x60/8])(m);
}
// 710200b6c0 [vtable+0xA0]
void DamageModule__set_force_damage_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2, u64 p3, u64 p4, bool p5, bool p6, bool p7, bool p8) {
    auto* m = DMG(a); reinterpret_cast<void(*)(void*,u64,u64,u64,u64,bool,bool,bool,bool)>(VT(m)[0xa0/8])(m,p1,p2,p3,p4,p5,p6,p7,p8);
}
// 710200b6f0 [vtable+0xC0]
void DamageModule__add_damage_impl(BattleObjectModuleAccessor* a, u64 p1) {
    auto* m = DMG(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0xc0/8])(m,p1);
}
// 710200b700 [vtable+0xC8]
void* DamageModule__damage_impl(BattleObjectModuleAccessor* a, u64 p1) {
    auto* m = DMG(a); return reinterpret_cast<void*(*)(void*,u64)>(VT(m)[0xc8/8])(m,p1);
}
// 710200b710 [vtable+0xD0]
void* DamageModule__reaction_impl(BattleObjectModuleAccessor* a, u64 p1) {
    auto* m = DMG(a); return reinterpret_cast<void*(*)(void*,u64)>(VT(m)[0xd0/8])(m,p1);
}
// 710200b720 [vtable+0xD8]
void* DamageModule__power_max_impl(BattleObjectModuleAccessor* a, u64 p1) {
    auto* m = DMG(a); return reinterpret_cast<void*(*)(void*,u64)>(VT(m)[0xd8/8])(m,p1);
}
// 710200b730 [vtable+0xE0]
void DamageModule__check_no_reaction_impl(BattleObjectModuleAccessor* a, u64 p1) {
    auto* m = DMG(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0xe0/8])(m,p1);
}
// 710200b740 [vtable+0xE8]
void DamageModule__set_no_reaction_mode_status_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2) {
    auto* m = DMG(a); reinterpret_cast<void(*)(void*,u64,u64)>(VT(m)[0xe8/8])(m,p1,p2);
}
// 710200b750 [vtable+0xF8]
void DamageModule__reset_no_reaction_mode_status_impl(BattleObjectModuleAccessor* a) {
    auto* m = DMG(a); reinterpret_cast<void(*)(void*)>(VT(m)[0xf8/8])(m);
}
// 710200b760 [vtable+0x120]
void DamageModule__set_no_reaction_damage_power_impl(BattleObjectModuleAccessor* a) {
    auto* m = DMG(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x120/8])(m);
}
// 710200b770 [vtable+0x128]
void DamageModule__set_no_reaction_no_effect_impl(BattleObjectModuleAccessor* a, bool p1) {
    auto* m = DMG(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x128/8])(m,p1);
}
// 710200b790 [vtable+0x130]
bool DamageModule__is_no_reaction_mode_perfect_impl(BattleObjectModuleAccessor* a) {
    auto* m = DMG(a); return reinterpret_cast<bool(*)(void*)>(VT(m)[0x130/8])(m);
}
// 710200b7a0 [vtable+0x188]
void* DamageModule__damage_log_impl(BattleObjectModuleAccessor* a) {
    auto* m = DMG(a); return reinterpret_cast<void*(*)(void*)>(VT(m)[0x188/8])(m);
}
// 710200b7b0 [vtable+0x1B0]
void DamageModule__set_attacker_info_impl(BattleObjectModuleAccessor* a, u64 p1) {
    auto* m = DMG(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x1b0/8])(m,p1);
}
// 710200b7c0 [vtable+0x1D8]
bool DamageModule__is_capture_cut_impl(BattleObjectModuleAccessor* a) {
    auto* m = DMG(a); return reinterpret_cast<bool(*)(void*)>(VT(m)[0x1d8/8])(m);
}
// 710200b7d0 [vtable+0x1E8]
void DamageModule__set_ignore_capture_cut_no_impl(BattleObjectModuleAccessor* a, u64 p1) {
    auto* m = DMG(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x1e8/8])(m,p1);
}
// 710200b7e0 [vtable+0x210]
void DamageModule__set_damage_mul_impl(BattleObjectModuleAccessor* a) {
    auto* m = DMG(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x210/8])(m);
}
// 710200b7f0 [vtable+0x218]
void DamageModule__set_damage_mul_2nd_impl(BattleObjectModuleAccessor* a) {
    auto* m = DMG(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x218/8])(m);
}
// 710200b800 [vtable+0x220]
void DamageModule__set_force_damage_mul_impl(BattleObjectModuleAccessor* a) {
    auto* m = DMG(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x220/8])(m);
}
// 710200b810 [vtable+0x228]
void DamageModule__set_reaction_mul_impl(BattleObjectModuleAccessor* a) {
    auto* m = DMG(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x228/8])(m);
}
// 710200b820 [vtable+0x230]
void DamageModule__set_reaction_mul_2nd_impl(BattleObjectModuleAccessor* a) {
    auto* m = DMG(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x230/8])(m);
}
// 710200b830 [vtable+0x238]
void DamageModule__set_reaction_mul_4th_impl(BattleObjectModuleAccessor* a) {
    auto* m = DMG(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x238/8])(m);
}
// 710200b840 [vtable+0x240]
void DamageModule__set_weak_param_impl(BattleObjectModuleAccessor* a, u64 p1) {
    auto* m = DMG(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x240/8])(m,p1);
}
// 710200b850 [vtable+0x248]
void DamageModule__set_damage_lock_impl(BattleObjectModuleAccessor* a, bool p1) {
    auto* m = DMG(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x248/8])(m,p1);
}
// 710200b870 [vtable+0x250]
void DamageModule__set_damage_lock_2nd_impl(BattleObjectModuleAccessor* a, bool p1) {
    auto* m = DMG(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x250/8])(m,p1);
}
// 710200b890 [vtable+0x258]
bool DamageModule__is_damage_lock_impl(BattleObjectModuleAccessor* a) {
    auto* m = DMG(a); return reinterpret_cast<bool(*)(void*)>(VT(m)[0x258/8])(m);
}
// 710200b8a0 [vtable+0x268]
void DamageModule__heal_impl(BattleObjectModuleAccessor* a, u64 p1) {
    auto* m = DMG(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x268/8])(m,p1);
}
// 710200b8b0 [vtable+0x288]
void DamageModule__overwrite_log_reaction_frame_impl(BattleObjectModuleAccessor* a) {
    auto* m = DMG(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x288/8])(m);
}
// 710200b8c0 [vtable+0x290]
void DamageModule__start_damage_info_log_impl(BattleObjectModuleAccessor* a) {
    auto* m = DMG(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x290/8])(m);
}
// 710200b8d0 [vtable+0x298]
void DamageModule__end_damage_info_log_impl(BattleObjectModuleAccessor* a) {
    auto* m = DMG(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x298/8])(m);
}
// 710200b8e0 [vtable+0x2A0]
void DamageModule__set_force_damage_from_last_damage_impl(BattleObjectModuleAccessor* a) {
    auto* m = DMG(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x2a0/8])(m);
}
// 710200b8f0 [vtable+0x2A8]
bool DamageModule__is_paralyze_impl(BattleObjectModuleAccessor* a) {
    auto* m = DMG(a); return reinterpret_cast<bool(*)(void*)>(VT(m)[0x2a8/8])(m);
}
// 710200b900 [vtable+0x2D0]
void DamageModule__set_critical_hit_impl(BattleObjectModuleAccessor* a, bool p1) {
    auto* m = DMG(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x2d0/8])(m,p1);
}
// 710200b920 [vtable+0x2D8]
bool DamageModule__is_critical_hit_impl(BattleObjectModuleAccessor* a) {
    auto* m = DMG(a); return reinterpret_cast<bool(*)(void*)>(VT(m)[0x2d8/8])(m);
}

} // namespace app::lua_bind
