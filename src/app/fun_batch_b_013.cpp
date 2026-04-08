#include "types.h"

// Batch decompiled via Ghidra MCP -- pool-b, batch 013
// Range: 0x71014 range

[[noreturn]] extern "C" void abort();

// Data symbols
extern u8 PTR_LAB_7105064358;
extern u8 PTR_LAB_7105064310;
extern u8 PTR_LAB_71050642c8;
extern u8 PTR_LAB_7105064280;
extern u8 PTR_LAB_7105064238;
extern u8 PTR_LAB_71050641f0;
extern u8 PTR_LAB_71050641a8;
extern u8 PTR_LAB_7105064160;
extern u8 PTR_LAB_7105064118;

// ── __throw_out_of_range thunk ────────────────────────────────────────────────

// 0x7101401580
[[noreturn]] void FUN_7101401580() { abort(); }

// ── Simple field getter ───────────────────────────────────────────────────────

// 0x7101401590 -- original is just ret (identity/pass-through)
u64 FUN_7101401590(u64 x) { return x; }

// ── Iterator begin() vtable-stub cluster ─────────────────────────────────────
// REMOVED: Addresses 0x710140f780-0x71014101f0 were incorrectly identified as
// function entry points. The original bytes at these addresses are epilogue code
// (ldp x29,x30 frame restore) inside larger functions. Correct addresses TBD.

// ── __throw_out_of_range thunks ───────────────────────────────────────────────

// 0x71014150c8
[[noreturn]] void FUN_71014150c8() { abort(); }

// 0x71014150fc

namespace std { namespace __1 {
template<bool> struct __vector_base_common {
    [[noreturn]] static void __throw_out_of_range();
};
}}

[[noreturn]] void FUN_71014150fc() { abort(); }
