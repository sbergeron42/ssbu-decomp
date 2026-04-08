#include "types.h"

// Batch decompiled via Ghidra MCP -- pool-b, batch 017
// Range: 0x71018 range (continued)

[[noreturn]] extern "C" void abort();

// ── Trivial no-ops ────────────────────────────────────────────────────────────

// addr-TBD-710185ed70
void FUN_710185ed70() {}

// addr-TBD-71018ce2e0
void FUN_71018ce2e0() {}

// ── __throw_out_of_range thunks (0x71018 range) ──────────────────────────────

// 0x710188c324
[[noreturn]] void FUN_710188c324() { abort(); }

// 0x7101886388
[[noreturn]] void FUN_7101886388() { abort(); }

// 0x71018b058c
[[noreturn]] void FUN_71018b058c() { abort(); }

// 0x71018b5258
[[noreturn]] void FUN_71018b5258() { abort(); }

// 0x71018c0c84
[[noreturn]] void FUN_71018c0c84() { abort(); }

// 0x71018cb574
[[noreturn]] void FUN_71018cb574() { abort(); }

// 0x71018f054c
[[noreturn]] void FUN_71018f054c() { abort(); }

// 0x71018f653c

namespace std { namespace __1 {
template<bool> struct __vector_base_common {
    [[noreturn]] static void __throw_out_of_range();
};
}}

[[noreturn]] void FUN_71018f653c() { abort(); }
