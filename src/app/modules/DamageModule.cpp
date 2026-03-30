#include "app/BattleObjectModuleAccessor.h"

// DamageModule — accessor+0xA8
#define DMG(acc) (acc->damage_module)
#define VT(mod) (*reinterpret_cast<void***>(mod))

namespace app::lua_bind {

// 710200b6b0 [vtable+0x60] — init_damage
void DamageModule__init_damage_impl(BattleObjectModuleAccessor* a) {
    auto* m = DMG(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x60/8])(m);
}
// 710200b6f0 [vtable+0xc0] — add_damage
void DamageModule__add_damage_impl(BattleObjectModuleAccessor* a, f32 d) {
    auto* m = DMG(a); reinterpret_cast<void(*)(void*,f32)>(VT(m)[0xc0/8])(m,d);
}
// 710200b700 [vtable+0xc8] — damage
f32 DamageModule__damage_impl(BattleObjectModuleAccessor* a) {
    auto* m = DMG(a); return reinterpret_cast<f32(*)(void*)>(VT(m)[0xc8/8])(m);
}
// 710200b710 [vtable+0xd0] — reaction
f32 DamageModule__reaction_impl(BattleObjectModuleAccessor* a) {
    auto* m = DMG(a); return reinterpret_cast<f32(*)(void*)>(VT(m)[0xd0/8])(m);
}
// 710200b720 [vtable+0xd8] — power_max
f32 DamageModule__power_max_impl(BattleObjectModuleAccessor* a) {
    auto* m = DMG(a); return reinterpret_cast<f32(*)(void*)>(VT(m)[0xd8/8])(m);
}
// 710200b730 [vtable+0xe0] — check_no_reaction
void DamageModule__check_no_reaction_impl(BattleObjectModuleAccessor* a, u64 p1) {
    auto* m = DMG(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0xe0/8])(m,p1);
}
// 710200b740 [vtable+0xe8] — set_no_reaction_mode_status
void DamageModule__set_no_reaction_mode_status_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2) {
    auto* m = DMG(a); reinterpret_cast<void(*)(void*,u64,u64)>(VT(m)[0xe8/8])(m,p1,p2);
}
// 710200b750 [vtable+0xf0] — reset_no_reaction_mode_status (search for this)
void DamageModule__reset_no_reaction_mode_status_impl(BattleObjectModuleAccessor* a) {
    auto* m = DMG(a); reinterpret_cast<void(*)(void*)>(VT(m)[0xf0/8])(m);
}
// 710200b760 [vtable+0x120] — set_no_reaction_damage_power
void DamageModule__set_no_reaction_damage_power_impl(BattleObjectModuleAccessor* a) {
    auto* m = DMG(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x120/8])(m);
}
// 710200b770 [vtable+0x128] — set_no_reaction_no_effect (bool, and w1 #1)
void DamageModule__set_no_reaction_no_effect_impl(BattleObjectModuleAccessor* a, bool p1) {
    auto* m = DMG(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x128/8])(m,p1);
}
// 710200b790 [vtable+0x130] — is_no_reaction_mode_perfect
bool DamageModule__is_no_reaction_mode_perfect_impl(BattleObjectModuleAccessor* a) {
    auto* m = DMG(a); return reinterpret_cast<bool(*)(void*)>(VT(m)[0x130/8])(m);
}
// 710200b7a0 [vtable+0x188] — damage_log
void* DamageModule__damage_log_impl(BattleObjectModuleAccessor* a) {
    auto* m = DMG(a); return reinterpret_cast<void*(*)(void*)>(VT(m)[0x188/8])(m);
}
// 710200b7b0 [vtable+0x1b0] — set_attacker_info
void DamageModule__set_attacker_info_impl(BattleObjectModuleAccessor* a, u64 p1) {
    auto* m = DMG(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x1b0/8])(m,p1);
}
// 710200b7c0 [vtable+0x1d8] — is_capture_cut
bool DamageModule__is_capture_cut_impl(BattleObjectModuleAccessor* a) {
    auto* m = DMG(a); return reinterpret_cast<bool(*)(void*)>(VT(m)[0x1d8/8])(m);
}
// 710200b7d0 [vtable+0x1e8] — set_ignore_capture_cut_no
void DamageModule__set_ignore_capture_cut_no_impl(BattleObjectModuleAccessor* a, u64 p1) {
    auto* m = DMG(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x1e8/8])(m,p1);
}
// 710200b7e0 [vtable+0x210] — set_damage_mul
void DamageModule__set_damage_mul_impl(BattleObjectModuleAccessor* a) {
    auto* m = DMG(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x210/8])(m);
}
// 710200b7f0 [vtable+0x218] — set_damage_mul_2nd
void DamageModule__set_damage_mul_2nd_impl(BattleObjectModuleAccessor* a) {
    auto* m = DMG(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x218/8])(m);
}
// 710200b800 [vtable+0x220] — set_force_damage_mul
void DamageModule__set_force_damage_mul_impl(BattleObjectModuleAccessor* a) {
    auto* m = DMG(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x220/8])(m);
}
// 710200b810 [vtable+0x228] — set_reaction_mul
void DamageModule__set_reaction_mul_impl(BattleObjectModuleAccessor* a) {
    auto* m = DMG(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x228/8])(m);
}
// 710200b820 [vtable+0x230] — set_reaction_mul_2nd
void DamageModule__set_reaction_mul_2nd_impl(BattleObjectModuleAccessor* a) {
    auto* m = DMG(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x230/8])(m);
}
// 710200b830 [vtable+0x238] — set_reaction_mul_4th
void DamageModule__set_reaction_mul_4th_impl(BattleObjectModuleAccessor* a) {
    auto* m = DMG(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x238/8])(m);
}
// 710200b840 [vtable+0x240] — set_weak_param
void DamageModule__set_weak_param_impl(BattleObjectModuleAccessor* a, u64 p1) {
    auto* m = DMG(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x240/8])(m,p1);
}
// 710200b850 [vtable+0x248] — set_damage_lock (bool, and w1 #1)
void DamageModule__set_damage_lock_impl(BattleObjectModuleAccessor* a, bool p1) {
    auto* m = DMG(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x248/8])(m,p1);
}
// 710200b870 [vtable+0x250] — set_damage_lock_2nd (bool, and w1 #1)
void DamageModule__set_damage_lock_2nd_impl(BattleObjectModuleAccessor* a, bool p1) {
    auto* m = DMG(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x250/8])(m,p1);
}
// 710200b890 [vtable+0x258] — is_damage_lock
bool DamageModule__is_damage_lock_impl(BattleObjectModuleAccessor* a) {
    auto* m = DMG(a); return reinterpret_cast<bool(*)(void*)>(VT(m)[0x258/8])(m);
}
// 710200b8a0 [vtable+0x268] — heal
void DamageModule__heal_impl(BattleObjectModuleAccessor* a, u64 p1) {
    auto* m = DMG(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x268/8])(m,p1);
}
// 710200b8b0 [vtable+0x288] — overwrite_log_reaction_frame
void DamageModule__overwrite_log_reaction_frame_impl(BattleObjectModuleAccessor* a) {
    auto* m = DMG(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x288/8])(m);
}
// 710200b8d0 [vtable+0x298] — end_damage_info_log
void DamageModule__end_damage_info_log_impl(BattleObjectModuleAccessor* a) {
    auto* m = DMG(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x298/8])(m);
}
// 710200b8e0 [vtable+0x2a0] — set_force_damage_from_last_damage
void DamageModule__set_force_damage_from_last_damage_impl(BattleObjectModuleAccessor* a) {
    auto* m = DMG(a); reinterpret_cast<void(*)(void*)>(VT(m)[0x2a0/8])(m);
}
// 710200b8f0 [vtable+0x2a8] — is_paralyze
bool DamageModule__is_paralyze_impl(BattleObjectModuleAccessor* a) {
    auto* m = DMG(a); return reinterpret_cast<bool(*)(void*)>(VT(m)[0x2a8/8])(m);
}
// 710200b900 [vtable+0x2d0] — set_critical_hit (bool, and w1 #1)
void DamageModule__set_critical_hit_impl(BattleObjectModuleAccessor* a, bool p1) {
    auto* m = DMG(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x2d0/8])(m,p1);
}
// 710200b920 [vtable+0x2d8] — is_critical_hit
bool DamageModule__is_critical_hit_impl(BattleObjectModuleAccessor* a) {
    auto* m = DMG(a); return reinterpret_cast<bool(*)(void*)>(VT(m)[0x2d8/8])(m);
}

} // namespace app::lua_bind
