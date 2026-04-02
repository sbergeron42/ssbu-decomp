#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7103 address range, batch e2-005
// Pool-e worker: auto-generated from Ghidra decompilation

// ---- Forward declarations -----------------------------------------------

extern "C" void FUN_71032e5640(u64);
extern "C" void FUN_71035231c0(u64);
extern "C" u64  DAT_710532e7c8;

// ---- struct getters/setters (stack-spill pattern) -----------------------------------------------
// Note: original uses sub/str/ldr stack spill — compiles correctly, may not verify

// ---- vtable dispatch + offset (32 bytes each) -----------------------------------------------
// Pattern: ldr x8,[x0]; ldr x8,[x8,#0xc0]; blr x8; add x0,x0,#offset; ret

// ---- simple wrappers -----------------------------------------------

