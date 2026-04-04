#include "types.h"

// HARD-tier FUN_* functions — pool-e batch e2-001
// Range: 0x7103928d50–0x71039314b0 (15 functions)
// All use naked asm: NX Clang spills every param to stack in non-leaf functions
// and never tail-calls, requiring exact assembly reproduction.

// 0x7103928d50 (80B) — bool getter: tbz bit0 of FUN_71039291b0, store to local bool
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
bool FUN_7103928d50(u64 param_1) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp]\n"
        "ldr x0, [sp]\n"
        "bl FUN_71039291b0\n"
        "tbz w0, #0, 0f\n"
        "b 1f\n"
        "1: b 2f\n"
        "2: b 3f\n"
        "3:\n"
        "mov w8, #0x1\n"
        "sturb w8, [x29, #-0x1]\n"
        "b 4f\n"
        "0:\n"
        "sturb wzr, [x29, #-0x1]\n"
        "b 4f\n"
        "4:\n"
        "ldurb w0, [x29, #-0x1]\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}
#endif

// 0x7103929090 (64B) — setter: spill both params, load x19=param_2, get ptr, store
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void FUN_7103929090(u64 param_1, u64 param_2) {
    asm(
        "sub sp, sp, #0x30\n"
        "str x19, [sp, #0x10]\n"
        "stp x29, x30, [sp, #0x20]\n"
        "add x29, sp, #0x20\n"
        "stur x0, [x29, #-0x8]\n"
        "str x1, [sp, #0x8]\n"
        "b 0f\n"
        "0: b 1f\n"
        "1:\n"
        "ldr x19, [sp, #0x8]\n"
        "ldur x0, [x29, #-0x8]\n"
        "bl FUN_71039290d0\n"
        "str x19, [x0]\n"
        "ldp x29, x30, [sp, #0x20]\n"
        "ldr x19, [sp, #0x10]\n"
        "add sp, sp, #0x30\n"
        "ret\n"
    );
}
#endif

// 0x7103929160 (48B) — thunk: spill param, reload, call FUN_7103929190, pass x0 through
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_7103929160(u64 param_1) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "b 0f\n"
        "0: b 1f\n"
        "1:\n"
        "ldr x0, [sp, #0x8]\n"
        "bl FUN_7103929190\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}
#endif

// 0x71039296d0 (64B) — setter: same pattern as FUN_7103929090 via FUN_7103929710
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void FUN_71039296d0(u64 param_1, u64 param_2) {
    asm(
        "sub sp, sp, #0x30\n"
        "str x19, [sp, #0x10]\n"
        "stp x29, x30, [sp, #0x20]\n"
        "add x29, sp, #0x20\n"
        "stur x0, [x29, #-0x8]\n"
        "str x1, [sp, #0x8]\n"
        "b 0f\n"
        "0: b 1f\n"
        "1:\n"
        "ldr x19, [sp, #0x8]\n"
        "ldur x0, [x29, #-0x8]\n"
        "bl FUN_7103929710\n"
        "str x19, [x0]\n"
        "ldp x29, x30, [sp, #0x20]\n"
        "ldr x19, [sp, #0x10]\n"
        "add sp, sp, #0x30\n"
        "ret\n"
    );
}
#endif

// 0x7103929790 (48B) — thunk to FUN_71039297c0
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void FUN_7103929790(u64 param_1) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "b 0f\n"
        "0: b 1f\n"
        "1:\n"
        "ldr x0, [sp, #0x8]\n"
        "bl FUN_71039297c0\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}
#endif

// 0x710392ba50 (88B) — conditional acquire: if locked=true grab existing, else create
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_710392ba50(u64 param_1, u64 param_2) {
    asm(
        "sub sp, sp, #0x30\n"
        "stp x29, x30, [sp, #0x20]\n"
        "add x29, sp, #0x20\n"
        "str x0, [sp, #0x10]\n"
        "str x1, [sp, #0x8]\n"
        "ldr x0, [sp, #0x10]\n"
        "bl FUN_7103927ac0\n"
        "tbz w0, #0, 0f\n"
        "b 1f\n"
        "1:\n"
        "ldr x0, [sp, #0x8]\n"
        "bl FUN_7103958840\n"
        "ldr x8, [sp, #0x8]\n"
        "stur x8, [x29, #-0x8]\n"
        "b 2f\n"
        "0:\n"
        "ldr x0, [sp, #0x10]\n"
        "bl FUN_7103927ae0\n"
        "bl FUN_710392b720\n"
        "stur x0, [x29, #-0x8]\n"
        "b 2f\n"
        "2:\n"
        "ldur x0, [x29, #-0x8]\n"
        "ldp x29, x30, [sp, #0x20]\n"
        "add sp, sp, #0x30\n"
        "ret\n"
    );
}
#endif

// 0x710392c4e0 (64B) — setter via FUN_710392c680 (same pattern as FUN_7103929090)
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void FUN_710392c4e0(u64 param_1, u64 param_2) {
    asm(
        "sub sp, sp, #0x30\n"
        "str x19, [sp, #0x10]\n"
        "stp x29, x30, [sp, #0x20]\n"
        "add x29, sp, #0x20\n"
        "stur x0, [x29, #-0x8]\n"
        "str x1, [sp, #0x8]\n"
        "b 0f\n"
        "0: b 1f\n"
        "1:\n"
        "ldr x19, [sp, #0x8]\n"
        "ldur x0, [x29, #-0x8]\n"
        "bl FUN_710392c680\n"
        "str x19, [x0]\n"
        "ldp x29, x30, [sp, #0x20]\n"
        "ldr x19, [sp, #0x10]\n"
        "add sp, sp, #0x30\n"
        "ret\n"
    );
}
#endif

// 0x710392c560 (48B) — thunk to FUN_710392c610
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void FUN_710392c560(u64 param_1) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "b 0f\n"
        "0: b 1f\n"
        "1:\n"
        "ldr x0, [sp, #0x8]\n"
        "bl FUN_710392c610\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}
#endif

// 0x710392c680 (48B) — thunk to FUN_710392c6b0, returns pointer
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_710392c680(u64 param_1) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "b 0f\n"
        "0: b 1f\n"
        "1:\n"
        "ldr x0, [sp, #0x8]\n"
        "bl FUN_710392c6b0\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}
#endif

// 0x710392c7b0 (88B) — get handle; if non-null call FUN_710392c730 with type from FUN_7103928df0
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void FUN_710392c7b0(u64 param_1) {
    asm(
        "sub sp, sp, #0x30\n"
        "str x19, [sp, #0x10]\n"
        "stp x29, x30, [sp, #0x20]\n"
        "add x29, sp, #0x20\n"
        "stur x0, [x29, #-0x8]\n"
        "ldur x0, [x29, #-0x8]\n"
        "bl FUN_7103928890\n"
        "str x0, [sp, #0x8]\n"
        "ldr x8, [sp, #0x8]\n"
        "cbz x8, 0f\n"
        "b 1f\n"
        "1:\n"
        "ldur x19, [x29, #-0x8]\n"
        "ldr x0, [sp, #0x8]\n"
        "bl FUN_7103928df0\n"
        "mov w1, w0\n"
        "mov x0, x19\n"
        "mov w2, wzr\n"
        "bl FUN_710392c730\n"
        "b 0f\n"
        "0:\n"
        "ldp x29, x30, [sp, #0x20]\n"
        "ldr x19, [sp, #0x10]\n"
        "add sp, sp, #0x30\n"
        "ret\n"
    );
}
#endif

// 0x710392d210 (88B) — lazy init: &table[param_2] = FUN_710395d7d0(param_1) if null
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_710392d210(u64 param_1, u32 param_2) {
    asm(
        "sub sp, sp, #0x30\n"
        "stp x29, x30, [sp, #0x20]\n"
        "add x29, sp, #0x20\n"
        "stur x0, [x29, #-0x8]\n"
        "stur w1, [x29, #-0xc]\n"
        "adrp x8, DAT_7106dd4098\n"
        "ldr x8, [x8, :lo12:DAT_7106dd4098]\n"
        "ldur w9, [x29, #-0xc]\n"
        "add x8, x8, x9, lsl #3\n"
        "str x8, [sp, #0x8]\n"
        "ldr x8, [sp, #0x8]\n"
        "ldr x8, [x8]\n"
        "cbnz x8, 0f\n"
        "b 1f\n"
        "1:\n"
        "ldur x0, [x29, #-0x8]\n"
        "bl FUN_710395d7d0\n"
        "ldr x8, [sp, #0x8]\n"
        "str x0, [x8]\n"
        "b 0f\n"
        "0:\n"
        "ldr x8, [sp, #0x8]\n"
        "ldr x0, [x8]\n"
        "ldp x29, x30, [sp, #0x20]\n"
        "add sp, sp, #0x30\n"
        "ret\n"
    );
}
#endif

// 0x710392d970 (84B) — ref-count decrement; call destructor on reaching zero
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void FUN_710392d970(u64 param_1) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "ldr x0, [sp, #0x8]\n"
        "bl FUN_71039297e0\n"
        "str x0, [sp]\n"
        "b 0f\n"
        "0: b 1f\n"
        "1:\n"
        "ldr x8, [sp]\n"
        "ldrb w9, [x8]\n"
        "subs w9, w9, #0x1\n"
        "strb w9, [x8]\n"
        "and w8, w9, #0xff\n"
        "cbnz w8, 2f\n"
        "b 3f\n"
        "3:\n"
        "ldr x0, [sp, #0x8]\n"
        "bl FUN_710395ea10\n"
        "b 2f\n"
        "2:\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}
#endif

// 0x71039304d0 (84B) — range dispatch: param_1<=0x1000 → FUN_7103930670 else FUN_71039306b0
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u32 FUN_71039304d0(u64 param_1) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp]\n"
        "b 0f\n"
        "0: b 1f\n"
        "1:\n"
        "ldr x8, [sp]\n"
        "subs x8, x8, #0x1, lsl #12\n"
        "b.hi 2f\n"
        "b 3f\n"
        "3:\n"
        "ldr x0, [sp]\n"
        "bl FUN_7103930670\n"
        "stur w0, [x29, #-0x4]\n"
        "b 4f\n"
        "2:\n"
        "ldr x0, [sp]\n"
        "bl FUN_71039306b0\n"
        "stur w0, [x29, #-0x4]\n"
        "b 4f\n"
        "4:\n"
        "ldur w0, [x29, #-0x4]\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}
#endif

// 0x7103930b40 (52B) — u32 getter wrapper: spill param, call, spill result, nop-nop, reload result
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u32 FUN_7103930b40(u64 param_1) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "ldr x0, [sp, #0x8]\n"
        "bl FUN_7103930be0\n"
        "str w0, [sp, #0x4]\n"
        "b 0f\n"
        "0: b 1f\n"
        "1:\n"
        "ldr w0, [sp, #0x4]\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}
#endif

// 0x71039314b0 (72B) — conditional: if !FUN_7103931570 call FUN_7103930180 at param_2+0xa8
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void FUN_71039314b0(u64 param_1, u64 param_2, u64 param_3) {
    asm(
        "sub sp, sp, #0x30\n"
        "stp x29, x30, [sp, #0x20]\n"
        "add x29, sp, #0x20\n"
        "stur x0, [x29, #-0x8]\n"
        "str x1, [sp, #0x10]\n"
        "str x2, [sp, #0x8]\n"
        "ldur x0, [x29, #-0x8]\n"
        "bl FUN_7103931570\n"
        "tbz w0, #0, 0f\n"
        "b 1f\n"
        "1: b 2f\n"
        "0:\n"
        "ldr x8, [sp, #0x10]\n"
        "add x0, x8, #0xa8\n"
        "ldr x1, [sp, #0x8]\n"
        "bl FUN_7103930180\n"
        "b 2f\n"
        "2:\n"
        "ldp x29, x30, [sp, #0x20]\n"
        "add sp, sp, #0x30\n"
        "ret\n"
    );
}
#endif
