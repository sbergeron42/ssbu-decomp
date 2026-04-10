#include "app/BattleObjectModuleAccessor.h"
#include "app/modules/DamageModule.h"
#define DM(a) static_cast<DamageModule*>((a)->damage_module)
namespace app::lua_bind {
// 710200b690 (20 bytes) — sleep: vtable slot 10 (0x50)
void DamageModule__sleep_impl(BattleObjectModuleAccessor* a, bool p1) { DM(a)->sleep(p1); }
// 710200b6b0 (16 bytes) — init_damage: vtable slot 12 (0x60)
void DamageModule__init_damage_impl(BattleObjectModuleAccessor* a) { DM(a)->init_damage(); }
// 710200b6c0 (40 bytes) — set_force_damage: vtable slot 20 (0xA0)
void DamageModule__set_force_damage_impl(BattleObjectModuleAccessor* a, u32 p1, void* p2, s32 p3, s32 p4, bool p5, bool p6, bool p7, bool p8) {
    DM(a)->set_force_damage(p1, p2, p3, p4, p5, p6, p7, p8);
}
// 710200b6f0 (16 bytes) — add_damage: vtable slot 24 (0xC0)
// Binary passes u64 in x1 (passthrough); .dynsym says (accessor, float)
void DamageModule__add_damage_impl(BattleObjectModuleAccessor* a, u64 p1) asm("_ZN3app8lua_bind29DamageModule__add_damage_implEPNS_26BattleObjectModuleAccessorEf");
void DamageModule__add_damage_impl(BattleObjectModuleAccessor* a, u64 p1) { DM(a)->add_damage(p1); }
// 710200b700 (16 bytes) — damage: vtable slot 25 (0xC8)
// Binary passes u64 in x1 (passthrough); .dynsym omits it
void* DamageModule__damage_impl(BattleObjectModuleAccessor* a, u64 p1) asm("_ZN3app8lua_bind25DamageModule__damage_implEPNS_26BattleObjectModuleAccessorE");
void* DamageModule__damage_impl(BattleObjectModuleAccessor* a, u64 p1) { return DM(a)->damage(p1); }
// 710200b710 (16 bytes) — reaction: vtable slot 26 (0xD0)
void* DamageModule__reaction_impl(BattleObjectModuleAccessor* a, u64 p1) asm("_ZN3app8lua_bind27DamageModule__reaction_implEPNS_26BattleObjectModuleAccessorE");
void* DamageModule__reaction_impl(BattleObjectModuleAccessor* a, u64 p1) { return DM(a)->reaction(p1); }
// 710200b720 (16 bytes) — power_max: vtable slot 27 (0xD8)
void* DamageModule__power_max_impl(BattleObjectModuleAccessor* a, u64 p1) asm("_ZN3app8lua_bind28DamageModule__power_max_implEPNS_26BattleObjectModuleAccessorE");
void* DamageModule__power_max_impl(BattleObjectModuleAccessor* a, u64 p1) { return DM(a)->power_max(p1); }
// 710200b730 (16 bytes) — check_no_reaction: vtable slot 28 (0xE0)
void DamageModule__check_no_reaction_impl(BattleObjectModuleAccessor* a, u64 p1) { DM(a)->check_no_reaction(p1); }
// 710200b740 (16 bytes) — set_no_reaction_mode_status: vtable slot 29 (0xE8)
void DamageModule__set_no_reaction_mode_status_impl(BattleObjectModuleAccessor* a, u64 p1, u64 p2) { DM(a)->set_no_reaction_mode_status(p1, p2); }
// 710200b750 (16 bytes) — reset_no_reaction_mode_status: vtable slot 31 (0xF8)
void DamageModule__reset_no_reaction_mode_status_impl(BattleObjectModuleAccessor* a) { DM(a)->reset_no_reaction_mode_status(); }
// 710200b760 (16 bytes) — set_no_reaction_damage_power: vtable slot 36 (0x120)
void DamageModule__set_no_reaction_damage_power_impl(BattleObjectModuleAccessor* a) { DM(a)->set_no_reaction_damage_power(); }
// 710200b770 (20 bytes) — set_no_reaction_no_effect: vtable slot 37 (0x128)
void DamageModule__set_no_reaction_no_effect_impl(BattleObjectModuleAccessor* a, bool p1) { DM(a)->set_no_reaction_no_effect(p1); }
// 710200b790 (16 bytes) — is_no_reaction_mode_perfect: vtable slot 38 (0x130)
bool DamageModule__is_no_reaction_mode_perfect_impl(BattleObjectModuleAccessor* a) { return DM(a)->is_no_reaction_mode_perfect(); }
// 710200b7a0 (16 bytes) — damage_log: vtable slot 49 (0x188)
void* DamageModule__damage_log_impl(BattleObjectModuleAccessor* a) { return DM(a)->damage_log(); }
// 710200b7b0 (16 bytes) — set_attacker_info: vtable slot 54 (0x1B0)
void DamageModule__set_attacker_info_impl(BattleObjectModuleAccessor* a, u64 p1) { DM(a)->set_attacker_info(p1); }
// 710200b7c0 (16 bytes) — is_capture_cut: vtable slot 59 (0x1D8)
bool DamageModule__is_capture_cut_impl(BattleObjectModuleAccessor* a) { return DM(a)->is_capture_cut(); }
// 710200b7d0 (16 bytes) — set_ignore_capture_cut_no: vtable slot 61 (0x1E8)
void DamageModule__set_ignore_capture_cut_no_impl(BattleObjectModuleAccessor* a, u64 p1) { DM(a)->set_ignore_capture_cut_no(p1); }
// 710200b7e0 (16 bytes) — set_damage_mul: vtable slot 66 (0x210)
void DamageModule__set_damage_mul_impl(BattleObjectModuleAccessor* a) { DM(a)->set_damage_mul(); }
// 710200b7f0 (16 bytes) — set_damage_mul_2nd: vtable slot 67 (0x218)
void DamageModule__set_damage_mul_2nd_impl(BattleObjectModuleAccessor* a) { DM(a)->set_damage_mul_2nd(); }
// 710200b800 (16 bytes) — set_force_damage_mul: vtable slot 68 (0x220)
void DamageModule__set_force_damage_mul_impl(BattleObjectModuleAccessor* a) { DM(a)->set_force_damage_mul(); }
// 710200b810 (16 bytes) — set_reaction_mul: vtable slot 69 (0x228)
void DamageModule__set_reaction_mul_impl(BattleObjectModuleAccessor* a) { DM(a)->set_reaction_mul(); }
// 710200b820 (16 bytes) — set_reaction_mul_2nd: vtable slot 70 (0x230)
void DamageModule__set_reaction_mul_2nd_impl(BattleObjectModuleAccessor* a) { DM(a)->set_reaction_mul_2nd(); }
// 710200b830 (16 bytes) — set_reaction_mul_4th: vtable slot 71 (0x238)
void DamageModule__set_reaction_mul_4th_impl(BattleObjectModuleAccessor* a) { DM(a)->set_reaction_mul_4th(); }
// 710200b840 (16 bytes) — set_weak_param: vtable slot 72 (0x240)
void DamageModule__set_weak_param_impl(BattleObjectModuleAccessor* a, u64 p1) { DM(a)->set_weak_param(p1); }
// 710200b850 (20 bytes) — set_damage_lock: vtable slot 73 (0x248)
void DamageModule__set_damage_lock_impl(BattleObjectModuleAccessor* a, bool p1) { DM(a)->set_damage_lock(p1); }
// 710200b870 (20 bytes) — set_damage_lock_2nd: vtable slot 74 (0x250)
void DamageModule__set_damage_lock_2nd_impl(BattleObjectModuleAccessor* a, bool p1) { DM(a)->set_damage_lock_2nd(p1); }
// 710200b890 (16 bytes) — is_damage_lock: vtable slot 75 (0x258)
bool DamageModule__is_damage_lock_impl(BattleObjectModuleAccessor* a) { return DM(a)->is_damage_lock(); }
// 710200b8a0 (16 bytes) — heal: vtable slot 77 (0x268)
void DamageModule__heal_impl(BattleObjectModuleAccessor* a, u64 p1) { DM(a)->heal(p1); }
// 710200b8b0 (16 bytes) — overwrite_log_reaction_frame: vtable slot 81 (0x288)
void DamageModule__overwrite_log_reaction_frame_impl(BattleObjectModuleAccessor* a) { DM(a)->overwrite_log_reaction_frame(); }
// 710200b8c0 (16 bytes) — start_damage_info_log: vtable slot 82 (0x290)
void DamageModule__start_damage_info_log_impl(BattleObjectModuleAccessor* a) { DM(a)->start_damage_info_log(); }
// 710200b8d0 (16 bytes) — end_damage_info_log: vtable slot 83 (0x298)
void DamageModule__end_damage_info_log_impl(BattleObjectModuleAccessor* a) { DM(a)->end_damage_info_log(); }
// 710200b8e0 (16 bytes) — set_force_damage_from_last_damage: vtable slot 84 (0x2A0)
void DamageModule__set_force_damage_from_last_damage_impl(BattleObjectModuleAccessor* a) { DM(a)->set_force_damage_from_last_damage(); }
// 710200b8f0 (16 bytes) — is_paralyze: vtable slot 85 (0x2A8)
bool DamageModule__is_paralyze_impl(BattleObjectModuleAccessor* a) { return DM(a)->is_paralyze(); }
// 710200b900 (20 bytes) — set_critical_hit: vtable slot 90 (0x2D0)
void DamageModule__set_critical_hit_impl(BattleObjectModuleAccessor* a, bool p1) { DM(a)->set_critical_hit(p1); }
// 710200b920 (16 bytes) — is_critical_hit: vtable slot 91 (0x2D8)
bool DamageModule__is_critical_hit_impl(BattleObjectModuleAccessor* a) { return DM(a)->is_critical_hit(); }
} // namespace app::lua_bind
