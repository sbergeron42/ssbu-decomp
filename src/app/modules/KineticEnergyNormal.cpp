#include "types.h"

struct KineticEnergyNormal;

namespace app::lua_bind {

// Getters — return pointer to field
void* KineticEnergyNormal__get_accel_impl(KineticEnergyNormal* ke) { return reinterpret_cast<u8*>(ke) + 0x40; }
void* KineticEnergyNormal__get_stable_speed_impl(KineticEnergyNormal* ke) { return reinterpret_cast<u8*>(ke) + 0x50; }
void* KineticEnergyNormal__get_brake_impl(KineticEnergyNormal* ke) { return reinterpret_cast<u8*>(ke) + 0x60; }
void* KineticEnergyNormal__get_limit_speed_impl(KineticEnergyNormal* ke) { return reinterpret_cast<u8*>(ke) + 0x70; }

// Setters — copy 16 bytes (vec3 with hi64 first for correct store order)
void KineticEnergyNormal__set_accel_impl(KineticEnergyNormal* ke, void* src) { auto* s = reinterpret_cast<u64*>(src); auto* d = reinterpret_cast<u64*>(reinterpret_cast<u8*>(ke) + 0x40); d[1] = s[1]; d[0] = s[0]; }
void KineticEnergyNormal__set_stable_speed_impl(KineticEnergyNormal* ke, void* src) { auto* s = reinterpret_cast<u64*>(src); auto* d = reinterpret_cast<u64*>(reinterpret_cast<u8*>(ke) + 0x50); d[1] = s[1]; d[0] = s[0]; }
void KineticEnergyNormal__set_brake_impl(KineticEnergyNormal* ke, void* src) { auto* s = reinterpret_cast<u64*>(src); auto* d = reinterpret_cast<u64*>(reinterpret_cast<u8*>(ke) + 0x60); d[1] = s[1]; d[0] = s[0]; }
void KineticEnergyNormal__set_limit_speed_impl(KineticEnergyNormal* ke, void* src) { auto* s = reinterpret_cast<u64*>(src); auto* d = reinterpret_cast<u64*>(reinterpret_cast<u8*>(ke) + 0x70); d[1] = s[1]; d[0] = s[0]; }

// Bool flag at +0x80
void KineticEnergyNormal__on_consider_ground_normal_impl(KineticEnergyNormal* ke) { *reinterpret_cast<u8*>(reinterpret_cast<u8*>(ke) + 0x80) = 1; }
void KineticEnergyNormal__off_consider_ground_normal_impl(KineticEnergyNormal* ke) { *reinterpret_cast<u8*>(reinterpret_cast<u8*>(ke) + 0x80) = 0; }

} // namespace app::lua_bind
