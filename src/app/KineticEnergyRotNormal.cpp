#include "types.h"
#define VT(m) (*reinterpret_cast<void***>(m))

typedef float v4sf __attribute__((vector_size(16)));

struct KineticEnergyRotNormal {
    u8  pad_0x00[0x20];
    u8  rot_speed[0x10];     // +0x20
    u8  pad_0x30[0x10];
    u8  accel[0x10];         // +0x40
    u8  stable_speed[0x10];  // +0x50
    u8  brake[0x10];         // +0x60
    u8  limit_speed[0x10];   // +0x70
};

namespace app::lua_bind {

void* KineticEnergyRotNormal__get_accel_impl(KineticEnergyRotNormal* obj) { return obj->accel; }
void* KineticEnergyRotNormal__get_stable_speed_impl(KineticEnergyRotNormal* obj) { return obj->stable_speed; }
void* KineticEnergyRotNormal__get_brake_impl(KineticEnergyRotNormal* obj) { return obj->brake; }
void* KineticEnergyRotNormal__get_limit_speed_impl(KineticEnergyRotNormal* obj) { return obj->limit_speed; }
void* KineticEnergyRotNormal__get_rot_speed_impl(KineticEnergyRotNormal* obj) { return obj->rot_speed; }

} // namespace app::lua_bind

