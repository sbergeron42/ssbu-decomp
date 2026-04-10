// Batch C - 015: Matched functions from 0x7102 range
// Cleaned: removed 5 unmatched Ghidra paste functions, kept 4 verified (M)

#include "types.h"

extern "C" void FUN_710062dc20(u64, const char *, u32);

// 0x7102ef5030 — format string call, always returns 1 (quality=M)
u64 FUN_7102ef5030(u64 param_1, u32 param_2, u64 param_3)
{
    FUN_710062dc20(param_3, "resultstage_effect_set_%02d", param_2);
    return 1;
}

// 0x7102220920 — kinetic module vtable dispatch, clear flag (quality=M)
u32 FUN_7102220920(s64 param_1)
{
    s64 *module;
    s64 entry;
    module = *(s64 **)(*(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0) + 0x68);
    entry = (**(s64 (**)(s64 *, s64))(*module + 0x60))(module, 2);
    *(u8 *)(entry + 0x30) = 0;
    return 0;
}

// 0x7102220a40 — kinetic module vtable +0x60 then +0x48 dispatch (quality=M)
u32 FUN_7102220a40(s64 param_1)
{
    s64 *module;
    module = *(s64 **)(*(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0) + 0x68);
    module = (s64 *)(**(s64 (**)(s64 *, s64))(*module + 0x60))(module, 2);
    (**(void (**)(void))(*module + 0x48))();
    return 0;
}

// 0x7102224040 — kinetic module vtable +0x60(4) then +0x48 dispatch (quality=M)
u32 FUN_7102224040(s64 param_1)
{
    s64 *module;
    module = *(s64 **)(*(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0) + 0x68);
    module = (s64 *)(**(s64 (**)(s64 *, s64))(*module + 0x60))(module, 4);
    (**(void (**)(void))(*module + 0x48))();
    return 0;
}
