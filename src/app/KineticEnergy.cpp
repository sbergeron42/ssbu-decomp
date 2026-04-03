#include "types.h"

// KineticEnergy -- operates on KineticEnergy* directly
// Vtable at [x0], fields at direct offsets.
// Tail-call pattern: ldr x8,[x0]; ldr xN,[x8,#off]; br xN
// Framed-call pattern: stp/mov frame; vtable call; load result; ldp/ret

struct KineticEnergy {
    void** vtable;          // +0x0
    u8  pad_0x08[0x18];
    u8  rotation[0x10];     // +0x20
    u8  enabled;            // +0x30
};

#define VT(p) (*reinterpret_cast<void***>(p))

namespace app::lua_bind {

// Skip: get_speed_x_impl (framed call -- prologue mismatch)
// Skip: get_speed_y_impl (framed call -- prologue mismatch)
// Skip: get_speed3f_impl (framed call -- prologue mismatch)

// 71020f64c0 -- add x0,x0,#0x20; ret
void* KineticEnergy__get_rotation_impl(KineticEnergy* ke) {
    return ke->rotation;
}

// 71020f64d0 -- ldr x8,[x0]; ldr x5,[x8,#0x40]; br x5 (uses x5: x0-x4 are forwarded)
void KineticEnergy__reset_energy_impl(KineticEnergy* ke, u64 p1, u64 p2, u64 p3, u64 p4) {
    reinterpret_cast<void(*)(KineticEnergy*, u64, u64, u64, u64)>(VT(ke)[0x40/8])(ke, p1, p2, p3, p4);
}

// 71020f64e0 -- ldr x8,[x0]; ldr x1,[x8,#0x48]; br x1 (tail call, 0 extra params)
void KineticEnergy__clear_speed_impl(KineticEnergy* ke) {
    reinterpret_cast<void(*)(KineticEnergy*)>(VT(ke)[0x48/8])(ke);
}

// 71020f64f0 -- ldr x8,[x0]; ldr x1,[x8,#0x50]; br x1 (tail call, 0 extra params)
void KineticEnergy__clear_rot_speed_impl(KineticEnergy* ke) {
    reinterpret_cast<void(*)(KineticEnergy*)>(VT(ke)[0x50/8])(ke);
}

// 71020f6500 -- ldr x8,[x0]; ldr x2,[x8,#0x58]; br x2 (tail call, 1 extra param)
void KineticEnergy__mul_speed_impl(KineticEnergy* ke, u64 p1) {
    reinterpret_cast<void(*)(KineticEnergy*, u64)>(VT(ke)[0x58/8])(ke, p1);
}

// 71020f6510 -- ldr x8,[x0]; ldr x2,[x8,#0x60]; br x2 (tail call, 1 extra param)
void KineticEnergy__mul_accel_impl(KineticEnergy* ke, u64 p1) {
    reinterpret_cast<void(*)(KineticEnergy*, u64)>(VT(ke)[0x60/8])(ke, p1);
}

// 71020f6520 -- ldr x8,[x0]; ldr x2,[x8,#0x68]; br x2 (tail call, 1 extra param)
void KineticEnergy__reflect_speed_impl(KineticEnergy* ke, u64 p1) {
    reinterpret_cast<void(*)(KineticEnergy*, u64)>(VT(ke)[0x68/8])(ke, p1);
}

// 71020f6530 -- ldr x8,[x0]; ldr x2,[x8,#0x70]; br x2 (tail call, 1 extra param)
void KineticEnergy__reflect_accel_impl(KineticEnergy* ke, u64 p1) {
    reinterpret_cast<void(*)(KineticEnergy*, u64)>(VT(ke)[0x70/8])(ke, p1);
}

// 71020f6540 -- ldr x8,[x0]; ldr x1,[x8,#0x78]; br x1 (tail call)
void KineticEnergy__on_consider_ground_friction_impl(KineticEnergy* ke) {
    reinterpret_cast<void(*)(KineticEnergy*)>(VT(ke)[0x78/8])(ke);
}

// 71020f6550 -- ldr x8,[x0]; ldr x1,[x8,#0x80]; br x1 (tail call)
void KineticEnergy__off_consider_ground_friction_impl(KineticEnergy* ke) {
    reinterpret_cast<void(*)(KineticEnergy*)>(VT(ke)[0x80/8])(ke);
}

// 71020f6560 -- mov w8,#0x1; strb w8,[x0,#0x30]; ret
void KineticEnergy__enable_impl(KineticEnergy* ke) {
    ke->enabled = 1;
}

// 71020f6570 -- strb wzr,[x0,#0x30]; ret
void KineticEnergy__unable_impl(KineticEnergy* ke) {
    ke->enabled = 0;
}

} // namespace app::lua_bind
