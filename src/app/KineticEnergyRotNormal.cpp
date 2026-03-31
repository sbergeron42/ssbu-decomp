#include "types.h"
#define VT(m) (*reinterpret_cast<void***>(m))

struct KineticEnergyRotNormal;

namespace app::lua_bind {

void* KineticEnergyRotNormal__get_accel_impl(KineticEnergyRotNormal* obj) { return reinterpret_cast<u8*>(obj) + 0x40; }
void* KineticEnergyRotNormal__get_stable_speed_impl(KineticEnergyRotNormal* obj) { return reinterpret_cast<u8*>(obj) + 0x50; }
void* KineticEnergyRotNormal__get_brake_impl(KineticEnergyRotNormal* obj) { return reinterpret_cast<u8*>(obj) + 0x60; }
void* KineticEnergyRotNormal__get_limit_speed_impl(KineticEnergyRotNormal* obj) { return reinterpret_cast<u8*>(obj) + 0x70; }
void* KineticEnergyRotNormal__get_rot_speed_impl(KineticEnergyRotNormal* obj) { return reinterpret_cast<u8*>(obj) + 0x20; }

} // namespace app::lua_bind
