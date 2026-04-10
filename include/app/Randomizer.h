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

// 9 xorshift128 channels selected by phx::Hash40. The live data block that a
// rollback snapshot must capture. Allocated separately from the owning
// RandomizerChannelVec — reach it via `vec->channels` (not by casting the vec).
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

// libc++ `std::vector<Xorshift128>` header. Owns the 180-byte channel array as
// a separately-allocated backing buffer. The standard libc++ layout is:
//     +0x00 __begin_    (T*)
//     +0x08 __end_      (T*)
//     +0x10 __end_cap_  (T*)   — the pointer half of the __compressed_pair
//     +0x18 __alloc     (8 B)  — the allocator half; empty allocator EBO gives 8 B slack
// The constructor (FUN_7101344cf0) zero-inits the first 24 bytes, then repurposes
// the 4-byte slack at +0x18 to hold the match seed — 0x87654321 as a placeholder
// during construction, overwritten with the real u32 seed by 0x71013454c8. The
// `resize(9)` call at 0x7101344e28 (std_vector_Xorshift128_resize_710143ab00)
// allocates the 180-byte buffer via je_aligned_alloc and populates __begin_/__end_.
// [derived: FUN_7101344cf0 @ 0x7101344dac-0x7101344e28 allocates 32 bytes via
//  aligned_alloc(16,32); std_vector_Xorshift128_resize identified by its stride
//  constants (0x14) and the Marsaglia 2003 xorshift128 default state values
//  0x075bcd15/0x159a55e5/0x1f123bb5/0x05491333 used for default-construction.]
struct RandomizerChannelVec {
    RandomizerChannels* channels;    // +0x00  libc++ __begin_
    Xorshift128*        end;         // +0x08  libc++ __end_     (= begin + 9)
    Xorshift128*        end_cap;     // +0x10  libc++ __end_cap_ (= end here)
    u32                 match_seed;  // +0x18  [derived: 0x71013454c8 writes w19 here;
                                     //         placeholder 0x87654321 at construction]
    u32                 pad_0x1c;    // +0x1c  allocator EBO slack
};
static_assert(sizeof(RandomizerChannelVec) == 0x20, "RandomizerChannelVec must be 32 bytes");

// Outer singleton allocated by FUN_7101344cf0. It is just a single pointer to
// the channel vector — the actual 180 bytes of RNG state live two levels deeper.
// [derived: 0x7101344d50 `mov w1,#0x8; bl alloc` allocates 8 bytes; 0x7101344e18
//  `str x0,[x20]` stores the newly constructed RandomizerChannelVec into it.]
struct Randomizer {
    RandomizerChannelVec* vec;     // +0x00
};
static_assert(sizeof(Randomizer) == 0x8, "Randomizer outer must be 8 bytes");

// libapp writes/reads this global. It is the address of the Randomizer singleton pointer.
// Every caller reads it through a THREE-level indirection chain:
//     ldr xN, [xBase, #0x5b0]   ; load 1: xN = Randomizer*
//     ldr xN, [xN]              ; load 2: xN = RandomizerChannelVec*
//     ldr xN, [xN]              ; load 3: xN = RandomizerChannels* (= vec->channels)
// The third load is easy to miss in Ghidra decompile output because the decompiler
// collapses the first indirection into its `DAT_` symbol notation.
// [derived: adrp x8,0x71052c2000 ; ldr x20,[x8, #0x5b0] at 0x71013454b8..71013454bc;
//  identical three-load sequence at 0x7102275374-80 (sv_math::rand), 0x710134a4e4-f0
//  (seed init), and every other reader sampled.]
extern Randomizer* g_randomizer_instance_71052c25b0;

} // namespace app
