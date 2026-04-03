#include "types.h"

// MEDIUM-tier FUN_* functions -- 0x7100 address range, batch 30
// Pool-d worker: trimmed to unique functions only (others were duplicates of earlier batches)

// ---- External declarations -----------------------------------------------

extern void Curl_SigloFree(u64);

// ---- Functions ---------------------------------------------------------------

// 0x710000c950 -- null-check field at +0xb70 then clear (44 bytes)
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void FUN_710000c950(s64 param_1)
{
    asm(
        "str x19, [sp, #-0x20]!\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "ldr x19, [x0, #0x10]\n"
        "ldr x0, [x19, #0xb70]\n"
        "cbz x0, 0f\n"
        "bl Curl_SigloFree\n"
        "str xzr, [x19, #0xb70]\n"
        "0:\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "ldr x19, [sp], #0x20\n"
        "ret\n"
    );
}
#else
void FUN_710000c950(s64 param_1)
{
    s64 lVar1 = *(s64*)(param_1 + 0x10);
    if (*(s64*)(lVar1 + 0xb70) != 0) {
        Curl_SigloFree(*(u64*)(lVar1 + 0xb70));
        *(u64*)(lVar1 + 0xb70) = 0;
    }
}
#endif
