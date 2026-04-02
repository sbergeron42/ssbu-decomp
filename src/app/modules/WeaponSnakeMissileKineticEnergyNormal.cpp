#include "types.h"

struct WeaponSnakeMissileKineticEnergyNormal;

namespace app::lua_bind {

// 71021643f0 -- load vec3 from x1, zero w-lane via ext+mov+mov, store to self+0xa0
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void WeaponSnakeMissileKineticEnergyNormal__set_direction_impl(WeaponSnakeMissileKineticEnergyNormal* self, void* dir) {
    asm(
        "ldr q0,[x1]\n"
        "fmov s1,wzr\n"
        "ext v2.16B,v0.16B,v0.16B,#0x8\n"
        "mov v2.S[1],v1.S[0]\n"
        "mov v0.D[1],v2.D[0]\n"
        "str q0,[x0, #0xa0]\n"
        "ret\n"
    );
}
#endif

} // namespace app::lua_bind
