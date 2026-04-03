#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7100 address range, batch d3-016
// Pool-d worker: auto-generated from Ghidra decompilation

// ---- External declarations -----------------------------------------------

// External FUN_* forward declarations
extern void FUN_71000b2b10(s64, s64);

namespace nn {
    namespace util {
        void ReferSymbol(const char *);
    }
    namespace pia { namespace common {
        struct InetAddress { static bool IsValid(s64); };
    } }
}

// ---- Functions ---------------------------------------------------------------
// 0x71000bf170 — GetPayload: compute packet payload pointer (16 bytes)
s64 FUN_71000bf170(s64 param_1, s32 param_2)
{
    return param_1 + (u64)(param_2 + 0x20) + 0x28;
}
// 0x71000c03c0 — Finalize: clear two fields at +0x70 and +0x78 (16 bytes)
void FUN_71000c03c0(s64 param_1)
{
    *(u64 *)(param_1 + 0x70) = 0;
    *(u32 *)(param_1 + 0x78) = 0;
}
// 0x71000ee2c0 — GetSessionIdArraySize: if ptr non-null return 4, else 0 (32 bytes)
u32 FUN_71000ee2c0(s64 param_1)
{
    if (*(s64 *)(param_1 + 0x2d8) != 0) {
        return 4;
    }
    return 0;
}
