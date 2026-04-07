#pragma once
#include "types.h"

// phx::Fiber — lightweight fiber wrapper used by resource service threads
// [derived: phx::Fiber namespace from Ghidra symbol "phx::Fiber::~Fiber"]
// [derived: FiberImpl layout from Ghidra 13.0.4 decompilation of setup/finalize/~Fiber]

namespace phx {

// FiberImpl — game-internal fiber control block (wraps nn::os::FiberType)
// [derived: je_aligned_alloc(0x10, 0xC0) in phx::Fiber::setup at 0x710353c5b0]
// [derived: nn::os::InitializeFiber/FinalizeFiber operate on this as first param]
// [derived: all field offsets from 13.0.4 disassembly cross-referenced across 5 functions]
struct FiberImpl {
    u8 os_data[0x58];     // +0x00 — [derived: nn::os::FiberType internals, opaque to game code]
    void* stack;           // +0x58 — [derived: freed via VirtualFreeHook + je_free in dtor at 0x710353c210]
    const char* name;      // +0x60 — [derived: stored from param in setup, default "(NamelessFiber)"]
    u8 pad_68[8];         // +0x68 — [unknown]
    u8 func_buf[0x20];    // +0x70 — [derived: std::function SBO inline storage, compared with +0x90]
    void* func_impl;       // +0x90 — [derived: std::function __f_ ptr, vtable dispatch at +0x20/+0x28]
    u8 pad_98[8];         // +0x98 — [unknown]
    u8 initialized;        // +0xA0 — [derived: strb wzr at +0xA0 in finalize; ldrb+cbz in switch_to_fiber]
    u8 pad_a1[0x0F];     // +0xA1 — [unknown padding]
    u32 state;             // +0xB0 — [derived: cmp w8,#0x2 in finalize; 1=ready, 2=running, 3=locked]
    u8 pad_b4[0x0C];     // +0xB4 — [unknown padding to 0xC0]
};
static_assert(sizeof(FiberImpl) == 0xC0, "FiberImpl must be 0xC0 bytes");

// Fiber — thin wrapper holding a single FiberImpl pointer
// [derived: constructor at 0x710353c200 zeros the pointer (8 bytes)]
struct Fiber {
    FiberImpl* impl;       // +0x00 — [derived: ldr x19,[x0] pattern in all Fiber methods]
};

} // namespace phx
