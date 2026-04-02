#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7102 address range, batch e2-006
// Pool-e worker: auto-generated from Ghidra decompilation
// Pattern: framed vtable call — x8 holds object, vtable[0xNN](obj), return 0

// ---- framed vtable call wrappers (36 bytes each) -----------------------------------------------
// Pattern: stp; mov x29; ldr x9,[x8]; ldr x9,[x9,#0xNN]; mov x0,x8; blr x9; ldp; mov w0,wzr; ret
// x8 = object (BattleObjectModuleAccessor or similar), x0/x1 unused

// 0x7102008fd0 — vtable[0x3e8/8](obj) (36 bytes)
// 0x710206cb80 — vtable[0xc8/8](obj) (36 bytes)
