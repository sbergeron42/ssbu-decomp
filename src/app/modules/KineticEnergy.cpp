#include "types.h"
#define VT(m) (*reinterpret_cast<void***>(m))

struct KineticEnergy;

namespace app::lua_bind {

// Framed vtable call + float dereference from result
// get_speed_x: calls vtable[0x20] which returns vec3*, then loads [x0] (x component)
f32 KineticEnergy__get_speed_x_impl(KineticEnergy* ke) {
    auto* result = reinterpret_cast<f32*(*)(KineticEnergy*)>(VT(ke)[0x20/8])(ke);
    asm("");
    return result[0];
}
f32 KineticEnergy__get_speed_y_impl(KineticEnergy* ke) {
    auto* result = reinterpret_cast<f32*(*)(KineticEnergy*)>(VT(ke)[0x20/8])(ke);
    asm("");
    return result[1];
}
// get_speed3f: calls vtable[0x20], returns the pointer directly
void* KineticEnergy__get_speed3f_impl(KineticEnergy* ke) {
    void* ret = reinterpret_cast<void*(*)(KineticEnergy*)>(VT(ke)[0x20/8])(ke);
    asm("");
    return ret;
}

// Pointer to field
void* KineticEnergy__get_rotation_impl(KineticEnergy* ke) { return reinterpret_cast<u8*>(ke) + 0x20; }

// Vtable dispatchers (operate on KineticEnergy* directly, vtable at [x0])
void KineticEnergy__reset_energy_impl(KineticEnergy* ke,u64 p1,u64 p2,u64 p3,u64 p4) { reinterpret_cast<void(*)(KineticEnergy*,u64,u64,u64,u64)>(VT(ke)[0x40/8])(ke,p1,p2,p3,p4); }
void KineticEnergy__clear_speed_impl(KineticEnergy* ke) { reinterpret_cast<void(*)(KineticEnergy*)>(VT(ke)[0x48/8])(ke); }
void KineticEnergy__clear_rot_speed_impl(KineticEnergy* ke) { reinterpret_cast<void(*)(KineticEnergy*)>(VT(ke)[0x50/8])(ke); }
void KineticEnergy__mul_speed_impl(KineticEnergy* ke,u64 p1) { reinterpret_cast<void(*)(KineticEnergy*,u64)>(VT(ke)[0x58/8])(ke,p1); }
void KineticEnergy__mul_accel_impl(KineticEnergy* ke,u64 p1) { reinterpret_cast<void(*)(KineticEnergy*,u64)>(VT(ke)[0x60/8])(ke,p1); }
void KineticEnergy__reflect_speed_impl(KineticEnergy* ke,u64 p1) { reinterpret_cast<void(*)(KineticEnergy*,u64)>(VT(ke)[0x68/8])(ke,p1); }
void KineticEnergy__reflect_accel_impl(KineticEnergy* ke,u64 p1) { reinterpret_cast<void(*)(KineticEnergy*,u64)>(VT(ke)[0x70/8])(ke,p1); }
void KineticEnergy__on_consider_ground_friction_impl(KineticEnergy* ke) { reinterpret_cast<void(*)(KineticEnergy*)>(VT(ke)[0x78/8])(ke); }
void KineticEnergy__off_consider_ground_friction_impl(KineticEnergy* ke) { reinterpret_cast<void(*)(KineticEnergy*)>(VT(ke)[0x80/8])(ke); }

// Bool flags
void KineticEnergy__enable_impl(KineticEnergy* ke) { *reinterpret_cast<u8*>(reinterpret_cast<u8*>(ke) + 0x30) = 1; }
void KineticEnergy__unable_impl(KineticEnergy* ke) { *reinterpret_cast<u8*>(reinterpret_cast<u8*>(ke) + 0x30) = 0; }

} // namespace app::lua_bind
