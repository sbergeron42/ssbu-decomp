#include "app/BattleObjectModuleAccessor.h"
#include "app/modules/KineticModule.h"

// KineticModule -- accessed via acc->item_kinetic_module (+0x68)
// Polymorphic base shared by Fighter and Item kinetic variants.
// All dispatchers use typed virtual dispatch via KineticModule.h (no raw vtable casts).

namespace app::lua_bind {

// 7102043970 [vtable+0x60]
void* KineticModule__get_energy_impl(BattleObjectModuleAccessor* a, s32 p1) {
    void* ret = a->item_kinetic_module->get_energy(p1);
    asm("");
    return ret;
}
// 7102043990 [vtable+0x90]
void KineticModule__clear_speed_all_impl(BattleObjectModuleAccessor* a) {
    a->item_kinetic_module->clear_speed_all();
}
// 71020439a0 [vtable+0x98]
void KineticModule__clear_speed_energy_id_impl(BattleObjectModuleAccessor* a, s32 p1) {
    a->item_kinetic_module->clear_speed_energy_id(p1);
}
// 71020439b0 [vtable+0xA0]
void KineticModule__clear_speed_attr_impl(BattleObjectModuleAccessor* a, u64 p1) {
    a->item_kinetic_module->clear_speed_attr(p1);
}
// 71020439c0 [vtable+0xA8]
void KineticModule__suspend_energy_all_impl(BattleObjectModuleAccessor* a) {
    a->item_kinetic_module->suspend_energy_all();
}
// 71020439d0 [vtable+0xB0]
void KineticModule__resume_energy_all_impl(BattleObjectModuleAccessor* a) {
    a->item_kinetic_module->resume_energy_all();
}
// 71020439e0 [vtable+0xB8]
void KineticModule__unable_energy_all_impl(BattleObjectModuleAccessor* a) {
    a->item_kinetic_module->unable_energy_all();
}
// 71020439f0 [vtable+0xC0]
void* KineticModule__get_sum_speed_impl(BattleObjectModuleAccessor* a, void* out) {
    return a->item_kinetic_module->get_sum_speed(out);
}
// 7102043a00 [vtable+0xC8]
void* KineticModule__get_sum_speed_x_impl(BattleObjectModuleAccessor* a, void* out) {
    return a->item_kinetic_module->get_sum_speed_x(out);
}
// 7102043a10 [vtable+0xD0]
void* KineticModule__get_sum_speed_y_impl(BattleObjectModuleAccessor* a, void* out) {
    return a->item_kinetic_module->get_sum_speed_y(out);
}
// 7102043a20 [vtable+0xD8]
void* KineticModule__get_sum_speed_length_impl(BattleObjectModuleAccessor* a, void* out) {
    return a->item_kinetic_module->get_sum_speed_length(out);
}
// 7102043a30 [vtable+0xE0]
void* KineticModule__get_sum_speed3f_impl(BattleObjectModuleAccessor* a, void* out) {
    return a->item_kinetic_module->get_sum_speed3f(out);
}
// 7102043a40 [vtable+0xE8]
void KineticModule__get_sum_rotation_impl(BattleObjectModuleAccessor* a, u64 p1) {
    a->item_kinetic_module->get_sum_rotation(p1);
}
// 7102043a50 [vtable+0xF0]
void KineticModule__set_consider_ground_friction_impl(BattleObjectModuleAccessor* a, bool p1, s32 p2) {
    a->item_kinetic_module->set_consider_ground_friction(p1, p2);
}
// 7102043a70 [vtable+0xF8]
void KineticModule__mul_speed_impl(BattleObjectModuleAccessor* a, void* speed, u64 p2) {
    a->item_kinetic_module->mul_speed(speed, p2);
}
// 7102043a80 [vtable+0x100]
void KineticModule__mul_accel_impl(BattleObjectModuleAccessor* a, void* vec, s32 p2) {
    a->item_kinetic_module->mul_accel(vec, p2);
}
// 7102043a90 [vtable+0x108]
void KineticModule__reflect_speed_impl(BattleObjectModuleAccessor* a, void* vec, s32 p2) {
    a->item_kinetic_module->reflect_speed(vec, p2);
}
// 7102043aa0 [vtable+0x110]
void KineticModule__reflect_accel_impl(BattleObjectModuleAccessor* a, void* vec, s32 p2) {
    a->item_kinetic_module->reflect_accel(vec, p2);
}
// 7102043ab0 [vtable+0x118]
void KineticModule__change_kinetic_impl(BattleObjectModuleAccessor* a, s32 kind) {
    a->item_kinetic_module->change_kinetic(kind);
}
// 7102043ac0 [vtable+0x120]
s32 KineticModule__get_kinetic_type_impl(BattleObjectModuleAccessor* a) {
    return a->item_kinetic_module->get_kinetic_type();
}
// 7102043ad0 [vtable+0x128]
void KineticModule__enable_energy_impl(BattleObjectModuleAccessor* a, s32 p1) {
    a->item_kinetic_module->enable_energy(p1);
}
// 7102043ae0 [vtable+0x130]
void KineticModule__unable_energy_impl(BattleObjectModuleAccessor* a, s32 p1) {
    a->item_kinetic_module->unable_energy(p1);
}
// 7102043af0 [vtable+0x138]
bool KineticModule__is_enable_energy_impl(BattleObjectModuleAccessor* a, s32 id) {
    return a->item_kinetic_module->is_enable_energy(id);
}
// 7102043b00 [vtable+0x140]
void KineticModule__suspend_energy_impl(BattleObjectModuleAccessor* a, s32 p1) {
    a->item_kinetic_module->suspend_energy(p1);
}
// 7102043b10 [vtable+0x148]
void KineticModule__resume_energy_impl(BattleObjectModuleAccessor* a, s32 p1) {
    a->item_kinetic_module->resume_energy(p1);
}
// 7102043b20 [vtable+0x150]
bool KineticModule__is_suspend_energy_impl(BattleObjectModuleAccessor* a, s32 p1) {
    return a->item_kinetic_module->is_suspend_energy(p1);
}
// 7102043b30 [vtable+0x158]
void KineticModule__add_speed_impl(BattleObjectModuleAccessor* a, void* speed) {
    a->item_kinetic_module->add_speed(speed);
}
// 7102043b40 [vtable+0x160]
void KineticModule__add_speed_outside_impl(BattleObjectModuleAccessor* a, void* speed, u64 p2) {
    a->item_kinetic_module->add_speed_outside(speed, p2);
}
// 7102043b50 [vtable+0x168]
void KineticModule__sleep_impl(BattleObjectModuleAccessor* a, bool p1) {
    a->item_kinetic_module->sleep(p1);
}

} // namespace app::lua_bind
