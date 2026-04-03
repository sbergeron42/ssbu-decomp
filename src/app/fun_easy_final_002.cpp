#include "types.h"

// EASY-tier batch 002 — pool-a worker

// External globals
extern u64 DAT_71052a80d8;
extern u64 DAT_71052a80e0;

// ── Noops ────────────────────────────────────────────────────────────────────

// 0x710007db60
void FUN_710007db60(void) {}

// 0x710007db70
void FUN_710007db70(void) {}

// 0x710007db80
void FUN_710007db80(void) {}

// 0x710008d090
void FUN_710008d090(void) {}

// 0x71000af310
void FUN_71000af310(void) {}

// ── Simple functions ─────────────────────────────────────────────────────────

// 0x7100016cc0
void FUN_7100016cc0(s64 param_1)
{
    *(u64 *)(param_1 + 0xb78) = 0;
    *(u64 *)(param_1 + 0xb70) = 0;
}

// 0x71000177a0
s64 FUN_71000177a0(s64 param_1, s32 param_2, s64 param_3, s32 param_4)
{
    if ((u64)(param_1 - param_3) > 0x862) {
        return 0x7fffffff;
    }
    return (param_1 - param_3) * 1000000 + (s64)(param_2 - param_4);
}

// 0x71000189d0
void FUN_71000189d0(s64 param_1)
{
    *(u64 *)(param_1 + 0x4fd0) = *(u64 *)(param_1 + 0x318);
    *(u64 *)(param_1 + 0x4fd8) = *(u64 *)(param_1 + 0x288);
}

// 0x7100000220
void FUN_7100000220(u64 param_1, u64 param_2)
{
    DAT_71052a80d8 = param_1;
    DAT_71052a80e0 = param_2;
}
