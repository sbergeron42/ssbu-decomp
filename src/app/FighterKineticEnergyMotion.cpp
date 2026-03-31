#include "types.h"

// FighterKineticEnergyMotion — operates on FighterKineticEnergyMotion* directly
// Direct struct field access at various offsets.

struct FighterKineticEnergyMotion;

namespace app::lua_bind {

// 7102120f60 — str s0,[x0,#0x8c]; ret
void FighterKineticEnergyMotion__set_angle_impl(FighterKineticEnergyMotion* ke, f32 val) {
    *reinterpret_cast<f32*>(reinterpret_cast<u8*>(ke) + 0x8c) = val;
}

// 7102120fa0 — str s0,[x0,#0x9c]; ret
void FighterKineticEnergyMotion__set_speed_mul_impl(FighterKineticEnergyMotion* ke, f32 val) {
    *reinterpret_cast<f32*>(reinterpret_cast<u8*>(ke) + 0x9c) = val;
}

// 7102120fe0 — reverse_chara_dir: negate vec x component and field at 0x88
// ldr q0,[x0,#0xa0]; fneg s1,s0; mov v0.S[0],v1.S[0]; str q0,[x0,#0xa0];
// ldr s0,[x0,#0x88]; fneg s0,s0; str s0,[x0,#0x88]; ret
// This uses SIMD — skip for now.

// 7102121000 — and w8,w1,#0x1; strb w8,[x0,#0xc0]; ret
void FighterKineticEnergyMotion__set_update_flag_impl(FighterKineticEnergyMotion* ke, bool val) {
    *reinterpret_cast<u8*>(reinterpret_cast<u8*>(ke) + 0xc0) = val & 1;
}

// 7102121010 — set_speed_mul_2nd: copies 16 bytes from x1 to x0+0xb0
// ldr x8,[x1,#0x8]; str x8,[x0,#0xb8]; ldr x8,[x1]; str x8,[x0,#0xb0]; ret
void FighterKineticEnergyMotion__set_speed_mul_2nd_impl(FighterKineticEnergyMotion* ke, void* src) {
    auto* d = reinterpret_cast<u64*>(reinterpret_cast<u8*>(ke) + 0xb0);
    auto* s = reinterpret_cast<u64*>(src);
    d[1] = s[1];
    d[0] = s[0];
}

// 7102121030 — ldr s0,[x0,#0x8c]; ret
f32 FighterKineticEnergyMotion__get_angle_impl(FighterKineticEnergyMotion* ke) {
    return *reinterpret_cast<f32*>(reinterpret_cast<u8*>(ke) + 0x8c);
}

// 7102121040 — ldr s0,[x0,#0x90]; ret
f32 FighterKineticEnergyMotion__get_angle_whole_impl(FighterKineticEnergyMotion* ke) {
    return *reinterpret_cast<f32*>(reinterpret_cast<u8*>(ke) + 0x90);
}

// 7102121050 — ldr s0,[x0,#0x88]; ret
f32 FighterKineticEnergyMotion__get_chara_dir_impl(FighterKineticEnergyMotion* ke) {
    return *reinterpret_cast<f32*>(reinterpret_cast<u8*>(ke) + 0x88);
}

// 7102121060 — ldr s0,[x0,#0x9c]; ret
f32 FighterKineticEnergyMotion__get_speed_mul_impl(FighterKineticEnergyMotion* ke) {
    return *reinterpret_cast<f32*>(reinterpret_cast<u8*>(ke) + 0x9c);
}

// 7102121070 — ldr w8,[x0,#0x84]; cmp w8,#0xb; cset w0,eq; ret
bool FighterKineticEnergyMotion__is_cliff_ground_trans_impl(FighterKineticEnergyMotion* ke) {
    return *reinterpret_cast<u32*>(reinterpret_cast<u8*>(ke) + 0x84) == 0xb;
}

} // namespace app::lua_bind
