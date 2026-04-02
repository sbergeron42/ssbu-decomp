#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7100 address range, batch 30
// Pool-d worker: trimmed to unique functions only (others were duplicates of earlier batches)

// ---- External declarations -----------------------------------------------

extern void FUN_71000272a0(u64);

// ---- Functions ---------------------------------------------------------------

// 0x710000c950 — null-check field at +0xb70 then clear (48 bytes)
void FUN_710000c950(s64 param_1)
{
    s64 lVar1 = *(s64*)(param_1 + 0x10);
    if (*(s64*)(lVar1 + 0xb70) != 0) {
        FUN_71000272a0(*(u64*)(lVar1 + 0xb70));
        *(u64*)(lVar1 + 0xb70) = 0;
    }
}
