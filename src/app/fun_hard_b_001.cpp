// Hard B - 001: HARD FUN_* batch decompilation (0x7100 range)
// Functions: 4

#include "types.h"

extern "C" {
    extern u64 strlen(const char *s);
    void FUN_710007a160();
    void *FUN_7100045fd0(void *, int);
    void FUN_71000322b0(void *, void *);
    u64  FUN_7100044dd0(void *, void *, u8);
    void FUN_7100047800(void *, void *, u32);
    void FUN_7100044db0(void *, void *);
}

// 0x7100044d00 — checks two pointers in struct, calls assert fn if non-null
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void FUN_7100044d00(char *param_1)
{
    asm(
        "str x19, [sp, #-0x20]!\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "mov x19, x0\n"
        "ldr x0, [x0, #0xc8]\n"
        "cbz x0, 1f\n"
        "bl FUN_710007a160\n"
        "1:\n"
        "ldr x0, [x19, #0xd0]\n"
        "cbz x0, 2f\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "ldr x19, [sp], #0x20\n"
        "b FUN_710007a160\n"
        "2:\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "ldr x19, [sp], #0x20\n"
        "ret\n"
    );
}
#endif

// 0x7100059f60 — SetBlendState helper: get blend from param_3+0xb8, call SetBlendState
void FUN_7100059f60(void *param_1, void *param_2, char *param_3)
{
#ifdef MATCHING_HACK_NX_CLANG
    asm volatile("" : : "r"(__builtin_frame_address(0)));
#endif
    void *uVar1 = FUN_7100045fd0(*(void **)(param_3 + 0xb8), 1);
    FUN_71000322b0(param_2, uVar1);
}

// 0x7100066060 — sum strlen+1 for param_2 strings at param_1+0x50
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
s64 FUN_7100066060(char *param_1, u32 param_2)
{
    asm(
        "str x21, [sp, #-0x30]!\n"
        "stp x20, x19, [sp, #0x10]\n"
        "stp x29, x30, [sp, #0x20]\n"
        "add x29, sp, #0x20\n"
        "cmp w1, #0x1\n"
        "b.lt 1f\n"
        "mov x19, xzr\n"
        "mov w20, w1\n"
        "add x21, x0, #0x50\n"
        "0:\n"
        "ldr x0, [x21], #0x8\n"
        "bl strlen\n"
        "add x8, x19, x0\n"
        "add x19, x8, #0x1\n"
        "subs x20, x20, #0x1\n"
        "b.ne 0b\n"
        "b 2f\n"
        "1:\n"
        "mov x19, xzr\n"
        "2:\n"
        "mov x0, x19\n"
        "ldp x29, x30, [sp, #0x20]\n"
        "ldp x20, x19, [sp, #0x10]\n"
        "ldr x21, [sp], #0x30\n"
        "ret\n"
    );
}
#endif

// 0x7100066600 — conditional dispatch: check, maybe call fn, always call cleanup
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void FUN_7100066600(void *param_1, void *param_2, void *param_3, u32 param_4)
{
    asm(
        "stp x22, x21, [sp, #-0x30]!\n"
        "stp x20, x19, [sp, #0x10]\n"
        "stp x29, x30, [sp, #0x20]\n"
        "add x29, sp, #0x20\n"
        "mov x22, x2\n"
        "mov x19, x1\n"
        "and w2, w3, #0xff\n"
        "mov x1, x22\n"
        "mov w21, w3\n"
        "mov x20, x0\n"
        "bl FUN_7100044dd0\n"
        "tbz w0, #0, 1f\n"
        "mov x0, x22\n"
        "mov x1, x19\n"
        "mov w2, w21\n"
        "bl FUN_7100047800\n"
        "1:\n"
        "mov x0, x20\n"
        "mov x1, x19\n"
        "ldp x29, x30, [sp, #0x20]\n"
        "ldp x20, x19, [sp, #0x10]\n"
        "ldp x22, x21, [sp], #0x30\n"
        "b FUN_7100044db0\n"
    );
}
#endif
