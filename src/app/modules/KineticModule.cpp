#include "app/BattleObjectModuleAccessor.h"

// KineticModule uses the same accessor field as ItemKineticModule (+0x68)
// The field is a polymorphic KineticModule base -- Item and Fighter variants share it

#define KINETIC_MODULE(a) (a->item_kinetic_module)
#define VT(m) (*reinterpret_cast<void***>(m))

namespace app::lua_bind {

// 7102043990 -- clear_speed_all
void KineticModule__clear_speed_all_impl(BattleObjectModuleAccessor* accessor) {
    auto* module = accessor->item_kinetic_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    reinterpret_cast<void (*)(void*)>(vtable[0x90 / 8])(module);
}

// 71020439f0 -- get_sum_speed
void* KineticModule__get_sum_speed_impl(BattleObjectModuleAccessor* accessor, void* out) {
    auto* module = accessor->item_kinetic_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    return reinterpret_cast<void* (*)(void*, void*)>(vtable[0xc0 / 8])(module, out);
}

// 7102043a00 -- get_sum_speed_x
void* KineticModule__get_sum_speed_x_impl(BattleObjectModuleAccessor* accessor, void* out) {
    auto* module = accessor->item_kinetic_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    return reinterpret_cast<void* (*)(void*, void*)>(vtable[0xc8 / 8])(module, out);
}

// 7102043a10 -- get_sum_speed_y
void* KineticModule__get_sum_speed_y_impl(BattleObjectModuleAccessor* accessor, void* out) {
    auto* module = accessor->item_kinetic_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    return reinterpret_cast<void* (*)(void*, void*)>(vtable[0xd0 / 8])(module, out);
}

// 7102043a20 -- get_sum_speed_length
void* KineticModule__get_sum_speed_length_impl(BattleObjectModuleAccessor* accessor, void* out) {
    auto* module = accessor->item_kinetic_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    return reinterpret_cast<void* (*)(void*, void*)>(vtable[0xd8 / 8])(module, out);
}

// 7102043a30 -- get_sum_speed3f
void* KineticModule__get_sum_speed3f_impl(BattleObjectModuleAccessor* accessor, void* out) {
    auto* module = accessor->item_kinetic_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    return reinterpret_cast<void* (*)(void*, void*)>(vtable[0xe0 / 8])(module, out);
}

// 7102043a70 -- mul_speed
void KineticModule__mul_speed_impl(BattleObjectModuleAccessor* accessor, void* speed, u64 p2) {
    auto* module = accessor->item_kinetic_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    reinterpret_cast<void (*)(void*, void*, u64)>(vtable[0xf8 / 8])(module, speed, p2);
}

// 7102043ab0 -- change_kinetic
void KineticModule__change_kinetic_impl(BattleObjectModuleAccessor* accessor, s32 kind) {
    auto* module = accessor->item_kinetic_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    reinterpret_cast<void (*)(void*, s32)>(vtable[0x118 / 8])(module, kind);
}

// 7102043ac0 -- get_kinetic_type
s32 KineticModule__get_kinetic_type_impl(BattleObjectModuleAccessor* accessor) {
    auto* module = accessor->item_kinetic_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    return reinterpret_cast<s32 (*)(void*)>(vtable[0x120 / 8])(module);
}

// 7102043af0 -- is_enable_energy
bool KineticModule__is_enable_energy_impl(BattleObjectModuleAccessor* accessor, s32 id) {
    auto* module = accessor->item_kinetic_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    return reinterpret_cast<bool (*)(void*, s32)>(vtable[0x138 / 8])(module, id);
}

// 7102043b30 -- add_speed
void KineticModule__add_speed_impl(BattleObjectModuleAccessor* accessor, void* speed) {
    auto* module = accessor->item_kinetic_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    reinterpret_cast<void (*)(void*, void*)>(vtable[0x158 / 8])(module, speed);
}

// 7102043b40 -- add_speed_outside
void KineticModule__add_speed_outside_impl(BattleObjectModuleAccessor* accessor, void* speed, u64 p2) {
    auto* module = accessor->item_kinetic_module;
    auto* vtable = *reinterpret_cast<void***>(module);
    reinterpret_cast<void (*)(void*, void*, u64)>(vtable[0x160 / 8])(module, speed, p2);
}

// Remaining KineticModule dispatchers
// 71020439a0
void KineticModule__v0x98(BattleObjectModuleAccessor* a,u64 p1) { auto* m=a->item_kinetic_module; auto* vt=*reinterpret_cast<void***>(m); reinterpret_cast<void(*)(void*,u64)>(vt[0x98/8])(m,p1); }
void KineticModule__v0xa0(BattleObjectModuleAccessor* a,u64 p1) { auto* m=a->item_kinetic_module; auto* vt=*reinterpret_cast<void***>(m); reinterpret_cast<void(*)(void*,u64)>(vt[0xa0/8])(m,p1); }
// 71020439c0
void KineticModule__v0xa8(BattleObjectModuleAccessor* a) { auto* m=a->item_kinetic_module; auto* vt=*reinterpret_cast<void***>(m); reinterpret_cast<void(*)(void*)>(vt[0xa8/8])(m); }
// 71020439d0
void KineticModule__v0xb0(BattleObjectModuleAccessor* a) { auto* m=a->item_kinetic_module; auto* vt=*reinterpret_cast<void***>(m); reinterpret_cast<void(*)(void*)>(vt[0xb0/8])(m); }
// 71020439e0
void KineticModule__v0xb8(BattleObjectModuleAccessor* a) { auto* m=a->item_kinetic_module; auto* vt=*reinterpret_cast<void***>(m); reinterpret_cast<void(*)(void*)>(vt[0xb8/8])(m); }
void KineticModule__v0xe8(BattleObjectModuleAccessor* a,u64 p1) { auto* m=a->item_kinetic_module; auto* vt=*reinterpret_cast<void***>(m); reinterpret_cast<void(*)(void*,u64)>(vt[0xe8/8])(m,p1); }
// 7102043a50
void KineticModule__v0xf0(BattleObjectModuleAccessor* a,bool p1,u64 p2) { auto* m=a->item_kinetic_module; auto* vt=*reinterpret_cast<void***>(m); reinterpret_cast<void(*)(void*,bool,u64)>(vt[0xf0/8])(m,p1,p2); }
// 7102043a80
void KineticModule__v0x100(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=a->item_kinetic_module; auto* vt=*reinterpret_cast<void***>(m); reinterpret_cast<void(*)(void*,u64,u64)>(vt[0x100/8])(m,p1,p2); }
// 7102043a90
void KineticModule__v0x108(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=a->item_kinetic_module; auto* vt=*reinterpret_cast<void***>(m); reinterpret_cast<void(*)(void*,u64,u64)>(vt[0x108/8])(m,p1,p2); }
// 7102043aa0
void KineticModule__v0x110(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=a->item_kinetic_module; auto* vt=*reinterpret_cast<void***>(m); reinterpret_cast<void(*)(void*,u64,u64)>(vt[0x110/8])(m,p1,p2); }
void KineticModule__v0x128(BattleObjectModuleAccessor* a,u64 p1) { auto* m=a->item_kinetic_module; auto* vt=*reinterpret_cast<void***>(m); reinterpret_cast<void(*)(void*,u64)>(vt[0x128/8])(m,p1); }
void KineticModule__v0x130(BattleObjectModuleAccessor* a,u64 p1) { auto* m=a->item_kinetic_module; auto* vt=*reinterpret_cast<void***>(m); reinterpret_cast<void(*)(void*,u64)>(vt[0x130/8])(m,p1); }
void KineticModule__v0x140(BattleObjectModuleAccessor* a,u64 p1) { auto* m=a->item_kinetic_module; auto* vt=*reinterpret_cast<void***>(m); reinterpret_cast<void(*)(void*,u64)>(vt[0x140/8])(m,p1); }
void KineticModule__v0x148(BattleObjectModuleAccessor* a,u64 p1) { auto* m=a->item_kinetic_module; auto* vt=*reinterpret_cast<void***>(m); reinterpret_cast<void(*)(void*,u64)>(vt[0x148/8])(m,p1); }
void KineticModule__v0x150(BattleObjectModuleAccessor* a,u64 p1) { auto* m=a->item_kinetic_module; auto* vt=*reinterpret_cast<void***>(m); reinterpret_cast<void(*)(void*,u64)>(vt[0x150/8])(m,p1); }
void KineticModule__v0x168(BattleObjectModuleAccessor* a,bool p1) { auto* m=a->item_kinetic_module; auto* vt=*reinterpret_cast<void***>(m); reinterpret_cast<void(*)(void*,bool)>(vt[0x168/8])(m,p1); }
// Auto-generated named dispatchers
void* KineticModule__get_energy_impl(BattleObjectModuleAccessor* a) { auto* m=a->item_kinetic_module; void* ret = reinterpret_cast<void*(*)(void*)>(VT(m)[0x60/8])(m); asm(""); return ret; }
void KineticModule__clear_speed_energy_id_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=KINETIC_MODULE(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x98/8])(m,p1); }
// 71020439b0
void KineticModule__clear_speed_attr_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=KINETIC_MODULE(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0xa0/8])(m,p1); }
void* KineticModule__suspend_energy_all_impl(BattleObjectModuleAccessor* a) { auto* m=KINETIC_MODULE(a); return reinterpret_cast<void*(*)(void*)>(VT(m)[0xa8/8])(m); }
void* KineticModule__resume_energy_all_impl(BattleObjectModuleAccessor* a) { auto* m=KINETIC_MODULE(a); return reinterpret_cast<void*(*)(void*)>(VT(m)[0xb0/8])(m); }
void KineticModule__unable_energy_all_impl(BattleObjectModuleAccessor* a) { auto* m=KINETIC_MODULE(a); reinterpret_cast<void(*)(void*)>(VT(m)[0xb8/8])(m); }
// 7102043a40
void* KineticModule__get_sum_rotation_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=KINETIC_MODULE(a); return reinterpret_cast<void*(*)(void*,u64)>(VT(m)[0xe8/8])(m,p1); }
void KineticModule__set_consider_ground_friction_impl(BattleObjectModuleAccessor* a,bool p1,u64 p2) { auto* m=KINETIC_MODULE(a); reinterpret_cast<void(*)(void*,bool,u64)>(VT(m)[0xf0/8])(m,p1,p2); }
void* KineticModule__mul_accel_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=KINETIC_MODULE(a); return reinterpret_cast<void*(*)(void*,u64,u64)>(VT(m)[0x100/8])(m,p1,p2); }
void* KineticModule__reflect_speed_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=KINETIC_MODULE(a); return reinterpret_cast<void*(*)(void*,u64,u64)>(VT(m)[0x108/8])(m,p1,p2); }
void* KineticModule__reflect_accel_impl(BattleObjectModuleAccessor* a,u64 p1,u64 p2) { auto* m=KINETIC_MODULE(a); return reinterpret_cast<void*(*)(void*,u64,u64)>(VT(m)[0x110/8])(m,p1,p2); }
void KineticModule__enable_energy_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=KINETIC_MODULE(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x128/8])(m,p1); }
// 7102043ae0
void KineticModule__unable_energy_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=KINETIC_MODULE(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x130/8])(m,p1); }
// 7102043b00
void* KineticModule__suspend_energy_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=KINETIC_MODULE(a); return reinterpret_cast<void*(*)(void*,u64)>(VT(m)[0x140/8])(m,p1); }
// 7102043b10
void* KineticModule__resume_energy_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=KINETIC_MODULE(a); return reinterpret_cast<void*(*)(void*,u64)>(VT(m)[0x148/8])(m,p1); }
// 7102043b20
bool KineticModule__is_suspend_energy_impl(BattleObjectModuleAccessor* a,u64 p1) { auto* m=KINETIC_MODULE(a); return reinterpret_cast<bool(*)(void*,u64)>(VT(m)[0x150/8])(m,p1); }
// 7102043b50
void* KineticModule__sleep_impl(BattleObjectModuleAccessor* a,bool p1) { auto* m=KINETIC_MODULE(a); return reinterpret_cast<void*(*)(void*,bool)>(VT(m)[0x168/8])(m,p1); }
// Multi-bool dispatchers (auto-generated)
} // namespace app::lua_bind
