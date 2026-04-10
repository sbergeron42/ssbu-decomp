// Batch D - 001: Matched functions from 0x7103 range
// Cleaned: removed 9 unmatched Ghidra paste functions, kept 2 verified (M)

#include "types.h"

// External data symbols used by matched functions
extern u8 PTR_LAB_710517b8e0[] __attribute__((visibility("hidden")));
extern u8 DAT_7105182268[] __attribute__((visibility("hidden")));

// 0x71031758c0 — vtable + field copy, 2 fields (24 bytes, quality=M)
void FUN_71031758c0(s64 param_1, u64 *param_2)
{
    *param_2 = (u64)PTR_LAB_710517b8e0;
    param_2[1] = *(u64 *)(param_1 + 8);
}

// 0x71032ca720 — vtable + field copy, 3 fields (24 bytes, quality=M)
void FUN_71032ca720(s64 param_1, u64 *param_2)
{
    u64 val = *(u64 *)(param_1 + 0x10);
    *param_2 = (u64)DAT_7105182268;
    param_2[1] = *(u64 *)(param_1 + 8);
    param_2[2] = val;
}
