#include "types.h"
#define VT(m) (*reinterpret_cast<void***>(m))

typedef float v4sf __attribute__((vector_size(16)));

struct KineticEnergyRotNormal;

namespace app::lua_bind {

void* KineticEnergyRotNormal__get_accel_impl(KineticEnergyRotNormal* obj) { return reinterpret_cast<u8*>(obj) + 0x40; }
void* KineticEnergyRotNormal__get_stable_speed_impl(KineticEnergyRotNormal* obj) { return reinterpret_cast<u8*>(obj) + 0x50; }
void* KineticEnergyRotNormal__get_brake_impl(KineticEnergyRotNormal* obj) { return reinterpret_cast<u8*>(obj) + 0x60; }
void* KineticEnergyRotNormal__get_limit_speed_impl(KineticEnergyRotNormal* obj) { return reinterpret_cast<u8*>(obj) + 0x70; }
void* KineticEnergyRotNormal__get_rot_speed_impl(KineticEnergyRotNormal* obj) { return reinterpret_cast<u8*>(obj) + 0x20; }

// NX Clang generates ext+mov+mov for v[3]=0; upstream Clang uses mov v0.s[3] directly.
// Use naked asm under MATCHING_HACK_NX_CLANG to match the NX pattern.
#ifdef MATCHING_HACK_NX_CLANG
#define DEF_SET_VEC3(name, offset) \
__attribute__((naked)) \
void name(KineticEnergyRotNormal* obj, void* src) { \
    asm("ldr q0, [x1]\n" \
        "fmov s1, wzr\n" \
        "ext v2.16b, v0.16b, v0.16b, #8\n" \
        "mov v2.s[1], v1.s[0]\n" \
        "mov v0.d[1], v2.d[0]\n" \
        "str q0, [x0, #" #offset "]\n" \
        "ret\n"); \
}
DEF_SET_VEC3(KineticEnergyRotNormal__set_speed_impl, 0x20)
DEF_SET_VEC3(KineticEnergyRotNormal__set_accel_impl, 0x40)
DEF_SET_VEC3(KineticEnergyRotNormal__set_stable_speed_impl, 0x50)
DEF_SET_VEC3(KineticEnergyRotNormal__set_brake_impl, 0x60)
DEF_SET_VEC3(KineticEnergyRotNormal__set_limit_speed_impl, 0x70)
#undef DEF_SET_VEC3
#endif

} // namespace app::lua_bind
