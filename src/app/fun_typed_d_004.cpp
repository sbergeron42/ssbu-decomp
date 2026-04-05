// fun_typed_d_004.cpp — KineticModule v0xNN alias dispatchers
// The binary has two symbols for certain KineticModule functions: one with a
// human-readable name (already compiled in KineticModule.cpp) and one with a
// vtable-offset name (v0xNN). These produce the v0xNN symbol variants.
// Note: v0xNN versions use u64 params while named versions use s32.

#include "app/BattleObjectModuleAccessor.h"

// KineticModule uses raw vtable dispatch (no full struct header)
#define KIN(acc) (acc->item_kinetic_module)
#define VT(mod) (*reinterpret_cast<void***>(mod))

namespace app::lua_bind {

// v0xa0 = clear_speed_attr
void KineticModule__v0xa0(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind20KineticModule__v0xa0EPNS_26BattleObjectModuleAccessorEy");
void KineticModule__v0xa0(BattleObjectModuleAccessor* a, u64 p1) {
    auto* m = KIN(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0xa0/8])(m,p1);
}

// v0xe8 = get_sum_rotation
void KineticModule__v0xe8(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind20KineticModule__v0xe8EPNS_26BattleObjectModuleAccessorEy");
void KineticModule__v0xe8(BattleObjectModuleAccessor* a, u64 p1) {
    auto* m = KIN(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0xe8/8])(m,p1);
}

// v0x128 = enable_energy
void KineticModule__v0x128(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind21KineticModule__v0x128EPNS_26BattleObjectModuleAccessorEy");
void KineticModule__v0x128(BattleObjectModuleAccessor* a, u64 p1) {
    auto* m = KIN(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x128/8])(m,p1);
}

// v0x130 = unable_energy
void KineticModule__v0x130(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind21KineticModule__v0x130EPNS_26BattleObjectModuleAccessorEy");
void KineticModule__v0x130(BattleObjectModuleAccessor* a, u64 p1) {
    auto* m = KIN(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x130/8])(m,p1);
}

// v0x140 = suspend_energy
void KineticModule__v0x140(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind21KineticModule__v0x140EPNS_26BattleObjectModuleAccessorEy");
void KineticModule__v0x140(BattleObjectModuleAccessor* a, u64 p1) {
    auto* m = KIN(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x140/8])(m,p1);
}

// v0x148 = resume_energy
void KineticModule__v0x148(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind21KineticModule__v0x148EPNS_26BattleObjectModuleAccessorEy");
void KineticModule__v0x148(BattleObjectModuleAccessor* a, u64 p1) {
    auto* m = KIN(a); reinterpret_cast<void(*)(void*,u64)>(VT(m)[0x148/8])(m,p1);
}

// v0x150 = is_suspend_energy
bool KineticModule__v0x150(BattleObjectModuleAccessor* a, u64 p1)
    asm("_ZN3app8lua_bind21KineticModule__v0x150EPNS_26BattleObjectModuleAccessorEy");
bool KineticModule__v0x150(BattleObjectModuleAccessor* a, u64 p1) {
    auto* m = KIN(a); return reinterpret_cast<bool(*)(void*,u64)>(VT(m)[0x150/8])(m,p1);
}

// v0x168 = sleep
void KineticModule__v0x168(BattleObjectModuleAccessor* a, bool p1)
    asm("_ZN3app8lua_bind21KineticModule__v0x168EPNS_26BattleObjectModuleAccessorEb");
void KineticModule__v0x168(BattleObjectModuleAccessor* a, bool p1) {
    auto* m = KIN(a); reinterpret_cast<void(*)(void*,bool)>(VT(m)[0x168/8])(m,p1);
}

} // namespace app::lua_bind
