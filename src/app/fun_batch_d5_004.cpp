#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7101 range, batch d5-004
// Pool-d worker: auto-generated from Ghidra decompilation
// Includes: abort() thunks + global-dispatch wrappers (DAT_71052c2760) + indirect wrappers

// ---- External declarations -----------------------------------------------

[[noreturn]] extern "C" void abort();

extern "C" void FUN_71002f43c0(s64);
extern "C" void FUN_71002f4590(s64);
extern "C" void FUN_71002f4830(s64);
extern "C" void FUN_71014f6c60(u64);
extern "C" void FUN_71014f10c0(u64);
extern "C" void FUN_71014fede0(u64);
extern "C" void FUN_710150b040(u64);
extern "C" void FUN_710150f0c0(u64);

extern "C" u64 *DAT_71052c2760;

// ---- abort() thunks -------------------------------------------------------

// 0x71013c9770
[[noreturn]] void FUN_71013c9770(void) { abort(); }

// 0x71013ea564
[[noreturn]] void FUN_71013ea564(void) { abort(); }

// 0x71016222c0
[[noreturn]] void FUN_71016222c0(void) { abort(); }

// 0x7101851a50
[[noreturn]] void FUN_7101851a50(void) { abort(); }

// 0x7101852230
[[noreturn]] void FUN_7101852230(void) { abort(); }

// ---- Global-dispatch wrappers (via *DAT_71052c2760) -----------------------

// 0x7101344cd0 — dispatch to FUN_71014f10c0
void FUN_7101344cd0(void)
{
    FUN_71014f10c0(*DAT_71052c2760);
}

// 0x71014ac130 — dispatch to FUN_71014fede0
void FUN_71014ac130(void)
{
    FUN_71014fede0(*DAT_71052c2760);
}

// 0x71014aca80 — dispatch to FUN_710150f0c0
void FUN_71014aca80(void)
{
    FUN_710150f0c0(*DAT_71052c2760);
}

// 0x71014b2a20 — dispatch to FUN_71014f10c0
void FUN_71014b2a20(void)
{
    FUN_71014f10c0(*DAT_71052c2760);
}

// 0x71014d47b0 — dispatch to FUN_710150f0c0
void FUN_71014d47b0(void)
{
    FUN_710150f0c0(*DAT_71052c2760);
}

// 0x71014d5ba0 — dispatch to FUN_71014fede0
void FUN_71014d5ba0(void)
{
    FUN_71014fede0(*DAT_71052c2760);
}

// 0x71014d5dc0 — dispatch to FUN_71014f6c60
void FUN_71014d5dc0(void)
{
    FUN_71014f6c60(*DAT_71052c2760);
}

// 0x710151f700 — dispatch to FUN_710150b040
void FUN_710151f700(void)
{
    FUN_710150b040(*DAT_71052c2760);
}

// 0x710151fb60 — dispatch to FUN_710150f0c0
void FUN_710151fb60(void)
{
    FUN_710150f0c0(*DAT_71052c2760);
}

// 0x710151fe10 — dispatch to FUN_71014fede0
void FUN_710151fe10(void)
{
    FUN_71014fede0(*DAT_71052c2760);
}

// 0x71015200b0 — dispatch to FUN_71014f6c60
void FUN_71015200b0(void)
{
    FUN_71014f6c60(*DAT_71052c2760);
}

// 0x7101523b40 — dispatch to FUN_71014f10c0
void FUN_7101523b40(void)
{
    FUN_71014f10c0(*DAT_71052c2760);
}

// ---- Indirect call wrappers -----------------------------------------------
// Pattern: call helper with *(param_1 - 8) + offset as argument

// 0x7101f78db0 — FUN_71002f43c0(*(param_1 - 8) + 0x180)
u32 FUN_7101f78db0(s64 param_1)
{
    FUN_71002f43c0(*(s64 *)(param_1 - 8) + 0x180);
    return 0;
}

// 0x7101f78dd0 — FUN_71002f4590(*(param_1 - 8) + 0x180)
u32 FUN_7101f78dd0(s64 param_1)
{
    FUN_71002f4590(*(s64 *)(param_1 - 8) + 0x180);
    return 0;
}

// 0x7101f78df0 — FUN_71002f4830(*(param_1 - 8) + 0x180)
u32 FUN_7101f78df0(s64 param_1)
{
    FUN_71002f4830(*(s64 *)(param_1 - 8) + 0x180);
    return 0;
}
