#pragma once

#include "types.h"

namespace app {

// Single xorshift128 generator + call counter.
// [derived: app::sv_math::rand @ 0x7102275320 — reads state[3] at +0xc,
//  increments counter at +0x10, advances state[0..3] by Marsaglia 2003 xorshift128]
struct Xorshift128 {
    u32 x;            // +0x00  state[0]
    u32 y;            // +0x04  state[1]
    u32 z;            // +0x08  state[2]
    u32 w;            // +0x0c  state[3]  (return value comes from here)
    u32 call_count;   // +0x10  [derived: every rand call does *(int*)(state+0x10) += 1]
};
static_assert(sizeof(Xorshift128) == 0x14, "Xorshift128 must be 20 bytes");

// The gameplay sync RNG: an array of 9 xorshift128 channels, selected by phx::Hash40.
// [derived: app::sv_math::rand dispatches on a Hash40 arg to base offsets 0, +0x14,
//  +0x28, +0x3c, +0x50, +0x64, +0x78, +0x8c, +0xa0 — each slot is one Xorshift128]
struct RandomizerChannels {
    Xorshift128 default_channel;   // +0x00   hash = unmatched / default
    Xorshift128 ch_0x77a08c3fc;    // +0x14   [derived: Hero lot_critical, attack SE lot]
    Xorshift128 ch_0x66933a7e6;    // +0x28
    Xorshift128 ch_0x5c27c9369;    // +0x3c
    Xorshift128 ai_random;         // +0x50   hash = 0x2095191e5
                                   //         [derived: app::ai_random::range_int/range_float/get_float/is_percent]
    Xorshift128 ch_0x5fb9f5aa9;    // +0x64
    Xorshift128 random;            // +0x78   hash = 0x41f1b251e
                                   //         [derived: app::random::range_int/range_float/get_float/is_percent]
    Xorshift128 ch_0x5f88ec384;    // +0x8c
    Xorshift128 ch_0x63b1cee05;    // +0xa0
};
static_assert(sizeof(RandomizerChannels) == 0xb4, "RandomizerChannels must be 180 bytes");

// Owner of the gameplay RNG state. Accessed via the global singleton pointer at 0x71052c25b0.
// Reads in decomp look like: `lVar = *(long *)*DAT_71052c25b0; lVar + channel_offset`.
// That means: singleton = [0x71052c25b0]; state = [singleton + 0x00]; then add channel offset.
// [derived: every reader of DAT_71052c25b0 (hundreds of sites) uses this exact two-deref pattern]
struct Randomizer {
    RandomizerChannels* channels;   // +0x00  [derived: init at 0x71013454c0 does `ldr x8,[x20]`]
    // Remaining layout not yet recovered — the init routine also takes a vector begin/end
    // pair, suggesting the channels live inside a std::vector header. Treat the rest as
    // opaque until a constructor is decompiled.
};

// libapp writes/reads this global. It is the address of the Randomizer singleton pointer.
// [derived: adrp x8,0x71052c2000 ; ldr x20,[x8, #0x5b0] at 0x71013454b8..71013454bc,
//  and `*DAT_71052c25b0` in every Ghidra decompile of a rand caller]
extern Randomizer* g_randomizer_instance_71052c25b0;

} // namespace app
