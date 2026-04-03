#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7100 address range, batch d3-012
// Pool-d worker: auto-generated from Ghidra decompilation

// ---- External declarations -----------------------------------------------

extern "C" void *memset(void *, int, u64);
// 0x710005e9f0 — vtable dispatch at +0x50, return 0 or field[0x1b] (32 bytes)
s64 FUN_710005e9f0(s64 *param_1, s32 param_2)
{
    (*(void (**)(void))(*param_1 + 0x50))();
    if (param_2 != 0) {
        return 0;
    }
    return param_1[0x1b];
}
