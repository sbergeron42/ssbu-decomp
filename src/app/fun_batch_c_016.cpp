// Batch C - 016: Matched functions from 0x7102 range
// Cleaned: removed 5 unmatched Ghidra paste functions, kept 2 verified (M)

#include "types.h"

// 0x7102ff82b0 — vtable[0] call, return inverted low bit (36 bytes, quality=M)
u64 FUN_7102ff82b0(u64 *param_1)
{
    u32 result;
    result = (**(u32 (**)(void))(*param_1))();
    return ~result & 1;
}

// 0x71029cceb8 — vtable +0x88 dispatch, always returns 1 (40 bytes, quality=M)
u64 FUN_71029cceb8(s64 *param_1, u32 param_2)
{
    (**(void (**)(s64 *, s32, u32))(*param_1 + 0x88))(param_1, 0, param_2);
    return 1;
}
