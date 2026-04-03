#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7100 address range, batch d3-019
// Pool-d worker: auto-generated from Ghidra decompilation

// ---- External declarations -----------------------------------------------

namespace nn {
    namespace util {
        void ReferSymbol(const char *);
    }
}

// ---- Functions ---------------------------------------------------------------
// 0x710013dcc0 — Reset: zero 4 fields (2+1+2+1 bytes) (48 bytes)
void FUN_710013dcc0(s64 param_1)
{
    *(u16 *)(param_1 + 8) = 0;
    *(u8 *)(param_1 + 10) = 0;
    *(u16 *)(param_1 + 0xc) = 0;
    *(u8 *)(param_1 + 0xe) = 0;
}
// 0x710013f9b0 — Reset: zero 3 fields (16 bytes)
void FUN_710013f9b0(s64 param_1)
{
    *(u32 *)(param_1 + 0x10) = 0;
    *(u16 *)(param_1 + 0x14) = 0;
    *(u64 *)(param_1 + 8) = 0;
}
// 0x7100146be0 — GetStationNum: return u32 at +0x1a8 (16 bytes)
u32 FUN_7100146be0(s64 param_1)
{
    return *(u32 *)(param_1 + 0x1a8);
}
// 0x7100149240 — SetCurrentSessionOpenStatus: indexed write to open-status array (16 bytes)
void FUN_7100149240(s64 param_1, u32 param_2)
{
    *(u32 *)(param_1 + (u64)*(u8 *)(param_1 + 0x162) * 4 + 400) = param_2;
}

// 0x7100149250 — SetBufferSessionOpenStatus: indexed write to other slot (32 bytes)
void FUN_7100149250(s64 param_1, u32 param_2)
{
    *(u32 *)(param_1 + (u64)(*(s8 *)(param_1 + 0x162) == '\0') * 4 + 400) = param_2;
}

// 0x710014f0b0 — Reset: clear u32 and set u64 sentinel (16 bytes)
void FUN_710014f0b0(s64 param_1)
{
    *(u32 *)(param_1 + 0x10) = 0;
    *(u64 *)(param_1 + 8) = 0x1400000000;
}
