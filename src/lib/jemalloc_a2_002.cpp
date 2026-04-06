// jemalloc 5.1.0 — arena/extent/base utility functions (batch 2)
// Pool-a decomp: addresses 0x71039353e0 — 0x7103945dc0
// NOTE: jemalloc was compiled with -O0 equivalent in NX build

#include "types.h"

#ifdef MATCHING_HACK_NX_CLANG

extern "C" {
// Callee declarations
void FUN_71039388f0(u64);
void FUN_7103938910(u64);
void FUN_7103942300(void);
void FUN_7103958840(void);
void FUN_710393dc80(u64, u32);
void FUN_7103938a80(u64);
void FUN_71039407a0(u64, u64);
void FUN_71039404a0(u64, u64, u64);
void FUN_710393e1a0(u64, u32);
void FUN_710393fa80(void);
void FUN_710393fb00(u64);
void FUN_710395ea10(u64);
void FUN_710393f970(u64, u64, u64);
void FUN_710393f1b0(u64, u64, u64);
void FUN_710393f390(u64, u32, u32, u64);
void FUN_710393fc90(u64);
void FUN_7103940490(void);
void FUN_710393fb50(u32);
void FUN_710393fe20(void);
void FUN_7103940970(u64, u64);
void FUN_710393ee90(u64);
void FUN_7103942b40(u64, u64);
void FUN_7103957fe0(void);
void FUN_71039575c0(void);
void FUN_7103944490(u64);
void FUN_71039444d0(u64);
void FUN_71039449a0(u64);
void FUN_7103944a40(u64);
void FUN_7103944fc0(u64);
void FUN_71039447f0(u64);
void FUN_7103944830(u64);
void FUN_7103945590(u64);
void FUN_7103957c40(u64, u64);
void FUN_7103930d50(u64);
void FUN_7103930ea0(u64, u64);
void FUN_71039337a0(u64);
void FUN_7103935f80(u64);
void FUN_7103938930(u64);
void FUN_710393faa0(u64);

// Data symbols
__attribute__((visibility("hidden"))) extern u8  DAT_7106d42580;
__attribute__((visibility("hidden"))) extern u8  DAT_7106dd3f1c;
__attribute__((visibility("hidden"))) extern u8  DAT_7106d4a668;
__attribute__((visibility("hidden"))) extern u8  DAT_7106d4a670;
}

// =========================================================================
// 2-param assertion-guarded wrappers (64 bytes)
// =========================================================================

// 0x710393e8c0 (64 bytes) — forwards to FUN_71039407a0
// jemalloc 5.1.0: large_ralloc wrapper
extern "C" __attribute__((naked))
void FUN_710393e8c0(u64, u64) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "str x1, [sp]\n"
        "b 1f\n"
        "1: b 2f\n"
        "2:\n"
        "ldr x0, [sp, #0x8]\n"
        "ldr x1, [sp]\n"
        "bl FUN_71039407a0\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// 0x7103940930 (64 bytes) — forwards to FUN_7103940970
// jemalloc 5.1.0: large_dalloc wrapper
extern "C" __attribute__((naked))
void FUN_7103940930(u64, u64) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "str x1, [sp]\n"
        "b 1f\n"
        "1: b 2f\n"
        "2:\n"
        "ldr x0, [sp, #0x8]\n"
        "ldr x1, [sp]\n"
        "bl FUN_7103940970\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 3-param assertion-guarded wrappers (64 bytes)
// =========================================================================

// 0x710393f040 (64 bytes) — forwards to FUN_710393f970
// jemalloc 5.1.0: large_palloc wrapper
extern "C" __attribute__((naked))
void FUN_710393f040(u64, u64, u64) {
    asm(
        "sub sp, sp, #0x30\n"
        "stp x29, x30, [sp, #0x20]\n"
        "add x29, sp, #0x20\n"
        "stur x0, [x29, #-0x8]\n"
        "str x1, [sp, #0x10]\n"
        "str x2, [sp, #0x8]\n"
        "b 1f\n"
        "1: b 2f\n"
        "2:\n"
        "ldur x0, [x29, #-0x8]\n"
        "ldr x1, [sp, #0x10]\n"
        "ldr x2, [sp, #0x8]\n"
        "bl FUN_710393f970\n"
        "ldp x29, x30, [sp, #0x20]\n"
        "add sp, sp, #0x30\n"
        "ret\n"
    );
}

// 0x710393f170 (64 bytes) — forwards to FUN_710393f1b0
// jemalloc 5.1.0: large_ralloc_no_move wrapper
extern "C" __attribute__((naked))
void FUN_710393f170(u64, u64, u64) {
    asm(
        "sub sp, sp, #0x30\n"
        "stp x29, x30, [sp, #0x20]\n"
        "add x29, sp, #0x20\n"
        "stur x0, [x29, #-0x8]\n"
        "str x1, [sp, #0x10]\n"
        "str x2, [sp, #0x8]\n"
        "b 1f\n"
        "1: b 2f\n"
        "2:\n"
        "ldur x0, [x29, #-0x8]\n"
        "ldr x1, [sp, #0x10]\n"
        "ldr x2, [sp, #0x8]\n"
        "bl FUN_710393f1b0\n"
        "ldp x29, x30, [sp, #0x20]\n"
        "add sp, sp, #0x30\n"
        "ret\n"
    );
}

// =========================================================================
// 4-param wrapper with 4× b+1 stubs (96 bytes)
// =========================================================================

// 0x710393ea30 (96 bytes)
// jemalloc 5.1.0: large_ralloc_move_helper
extern "C" __attribute__((naked))
void FUN_710393ea30(u64, u64, u64, u64) {
    asm(
        "sub sp, sp, #0x30\n"
        "stp x29, x30, [sp, #0x20]\n"
        "add x29, sp, #0x20\n"
        "stur x0, [x29, #-0x8]\n"
        "str x1, [sp, #0x10]\n"
        "str x2, [sp, #0x8]\n"
        "str x3, [sp]\n"
        "b 1f\n"
        "1: b 2f\n"
        "2: b 3f\n"
        "3: b 4f\n"
        "4:\n"
        "ldur x0, [x29, #-0x8]\n"
        "ldr x1, [sp, #0x8]\n"
        "ldr x2, [sp]\n"
        "bl FUN_71039404a0\n"
        "ldr x0, [sp]\n"
        "mov w1, wzr\n"
        "bl FUN_710393e1a0\n"
        "ldp x29, x30, [sp, #0x20]\n"
        "add sp, sp, #0x30\n"
        "ret\n"
    );
}

// =========================================================================
// Constant-arg wrapper (80 bytes)
// =========================================================================

// 0x710393f340 (80 bytes)
// jemalloc 5.1.0: arena.c — wrapper with constant args 8, 0xd50dcc1b
extern "C" __attribute__((naked))
void FUN_710393f340(u64, u64) {
    asm(
        "sub sp, sp, #0x30\n"
        "stp x29, x30, [sp, #0x20]\n"
        "add x29, sp, #0x20\n"
        "stur x0, [x29, #-0x8]\n"
        "mov w8, #0x8\n"
        "str x8, [sp, #0x10]\n"
        "mov w8, #0xcc1b\n"
        "movk w8, #0xd50d, lsl #16\n"
        "str w8, [sp, #0xc]\n"
        "str x1, [sp]\n"
        "b 1f\n"
        "1: b 2f\n"
        "2:\n"
        "ldur x0, [x29, #-0x8]\n"
        "ldr w1, [sp, #0x10]\n"
        "ldr w2, [sp, #0xc]\n"
        "ldr x3, [sp]\n"
        "bl FUN_710393f390\n"
        "ldp x29, x30, [sp, #0x20]\n"
        "add sp, sp, #0x30\n"
        "ret\n"
    );
}

// =========================================================================
// Refcount decrement pattern (96 bytes each)
// call get_ptr → ldrb → sub 1 → strb → cbnz → call release
// =========================================================================

// 0x710393faa0 (96 bytes)
// jemalloc 5.1.0: base.c — base refcount dec, calls FUN_710393fb00
extern "C" __attribute__((naked))
void FUN_710393faa0(u64) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "ldr x0, [sp, #0x8]\n"
        "bl FUN_710393fb00\n"
        "str x0, [sp]\n"
        "b 1f\n"
        "1: b 2f\n"
        "2:\n"
        "ldr x8, [sp]\n"
        "ldrb w9, [x8]\n"
        "subs w9, w9, #0x1\n"
        "strb w9, [x8]\n"
        "and w8, w9, #0xff\n"
        "cbnz w8, 3f\n"
        "b 4f\n"
        "4:\n"
        "ldr x0, [sp, #0x8]\n"
        "bl FUN_710395ea10\n"
        "b 3f\n"
        "3:\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// 0x71039448d0 (96 bytes)
// jemalloc 5.1.0: tcache.c — tcache refcount dec, calls FUN_71039449a0
extern "C" __attribute__((naked))
void FUN_71039448d0(u64) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "ldr x0, [sp, #0x8]\n"
        "bl FUN_71039449a0\n"
        "str x0, [sp]\n"
        "b 1f\n"
        "1: b 2f\n"
        "2:\n"
        "ldr x8, [sp]\n"
        "ldrb w9, [x8]\n"
        "subs w9, w9, #0x1\n"
        "strb w9, [x8]\n"
        "and w8, w9, #0xff\n"
        "cbnz w8, 3f\n"
        "b 4f\n"
        "4:\n"
        "ldr x0, [sp, #0x8]\n"
        "bl FUN_710395ea10\n"
        "b 3f\n"
        "3:\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// 0x7103935ed0 (96 bytes)
// jemalloc 5.1.0: extent.c — extent refcount dec, calls FUN_71039337a0
extern "C" __attribute__((naked))
void FUN_7103935ed0(u64) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "ldr x0, [sp, #0x8]\n"
        "bl FUN_71039337a0\n"
        "str x0, [sp]\n"
        "b 1f\n"
        "1: b 2f\n"
        "2:\n"
        "ldr x8, [sp]\n"
        "ldrb w9, [x8]\n"
        "subs w9, w9, #0x1\n"
        "strb w9, [x8]\n"
        "and w8, w9, #0xff\n"
        "cbnz w8, 3f\n"
        "b 4f\n"
        "4:\n"
        "ldr x0, [sp, #0x8]\n"
        "bl FUN_710395ea10\n"
        "b 3f\n"
        "3:\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// Bool check pattern (80 bytes each)
// ldrb → subs #0 → cset eq → strb → tbz → call → return saved bool
// =========================================================================

// 0x710393ff50 (80 bytes)
// jemalloc 5.1.0: base.c — base_ind_get_try_lock
extern "C" __attribute__((naked))
u8 FUN_710393ff50(u64) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "ldr x8, [sp, #0x8]\n"
        "ldrb w8, [x8]\n"
        "subs w8, w8, #0x0\n"
        "cset w8, eq\n"
        "strb w8, [sp, #0x4]\n"
        "ldrb w8, [sp, #0x4]\n"
        "tbz w8, #0, 0f\n"
        "b 1f\n"
        "1:\n"
        "ldr x0, [sp, #0x8]\n"
        "bl FUN_710393fc90\n"
        "b 0f\n"
        "0:\n"
        "ldrb w8, [sp, #0x4]\n"
        "and w0, w8, #0x1\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// 0x71039449f0 (80 bytes)
// jemalloc 5.1.0: tcache.c — tcache try_lock check
extern "C" __attribute__((naked))
u8 FUN_71039449f0(u64) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "ldr x8, [sp, #0x8]\n"
        "ldrb w8, [x8]\n"
        "subs w8, w8, #0x0\n"
        "cset w8, eq\n"
        "strb w8, [sp, #0x4]\n"
        "ldrb w8, [sp, #0x4]\n"
        "tbz w8, #0, 0f\n"
        "b 1f\n"
        "1:\n"
        "ldr x0, [sp, #0x8]\n"
        "bl FUN_7103944a40\n"
        "b 0f\n"
        "0:\n"
        "ldrb w8, [sp, #0x4]\n"
        "and w0, w8, #0x1\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// 0x7103935f30 (80 bytes)
// jemalloc 5.1.0: extent.c — extent try_lock check
extern "C" __attribute__((naked))
u8 FUN_7103935f30(u64) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "ldr x8, [sp, #0x8]\n"
        "ldrb w8, [x8]\n"
        "subs w8, w8, #0x0\n"
        "cset w8, eq\n"
        "strb w8, [sp, #0x4]\n"
        "ldrb w8, [sp, #0x4]\n"
        "tbz w8, #0, 0f\n"
        "b 1f\n"
        "1:\n"
        "ldr x0, [sp, #0x8]\n"
        "bl FUN_7103935f80\n"
        "b 0f\n"
        "0:\n"
        "ldrb w8, [sp, #0x4]\n"
        "and w0, w8, #0x1\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// Conditional dispatch (tbz → two paths returning value) (96 bytes)
// =========================================================================

// 0x710393c6a0 (96 bytes)
// jemalloc 5.1.0: tcache.c — conditional arena operation
extern "C" __attribute__((naked))
u64 FUN_710393c6a0(u64, u64) {
    asm(
        "sub sp, sp, #0x30\n"
        "stp x29, x30, [sp, #0x20]\n"
        "add x29, sp, #0x20\n"
        "str x0, [sp, #0x10]\n"
        "str x1, [sp, #0x8]\n"
        "ldr x0, [sp, #0x10]\n"
        "bl FUN_71039388f0\n"
        "tbz w0, #0, 1f\n"
        "b 0f\n"
        "0:\n"
        "ldr x0, [sp, #0x8]\n"
        "bl FUN_7103958840\n"
        "ldr x8, [sp, #0x8]\n"
        "stur x8, [x29, #-0x8]\n"
        "b 2f\n"
        "1:\n"
        "ldr x0, [sp, #0x10]\n"
        "bl FUN_7103938910\n"
        "bl FUN_7103942300\n"
        "stur x0, [x29, #-0x8]\n"
        "b 2f\n"
        "2:\n"
        "ldur x0, [x29, #-0x8]\n"
        "ldp x29, x30, [sp, #0x20]\n"
        "add sp, sp, #0x30\n"
        "ret\n"
    );
}

// 0x7103938870 (96 bytes)
// jemalloc 5.1.0: arena.c — arena conditional lookup
extern "C" __attribute__((naked))
u64 FUN_7103938870(u64) {
    asm(
        "sub sp, sp, #0x30\n"
        "stp x29, x30, [sp, #0x20]\n"
        "add x29, sp, #0x20\n"
        "str x0, [sp, #0x10]\n"
        "ldr x0, [sp, #0x10]\n"
        "bl FUN_71039388f0\n"
        "tbz w0, #0, 1f\n"
        "b 0f\n"
        "0:\n"
        "stur xzr, [x29, #-0x8]\n"
        "b 2f\n"
        "1:\n"
        "ldr x0, [sp, #0x10]\n"
        "bl FUN_7103938910\n"
        "str x0, [sp, #0x8]\n"
        "ldr x0, [sp, #0x8]\n"
        "bl FUN_7103938930\n"
        "stur x0, [x29, #-0x8]\n"
        "b 2f\n"
        "2:\n"
        "ldur x0, [x29, #-0x8]\n"
        "ldp x29, x30, [sp, #0x20]\n"
        "add sp, sp, #0x30\n"
        "ret\n"
    );
}

// 0x7103945510 (96 bytes)
// jemalloc 5.1.0: tcache.c — conditional tcache lookup
extern "C" __attribute__((naked))
u64 FUN_7103945510(u64) {
    asm(
        "sub sp, sp, #0x30\n"
        "stp x29, x30, [sp, #0x20]\n"
        "add x29, sp, #0x20\n"
        "str x0, [sp, #0x10]\n"
        "ldr x0, [sp, #0x10]\n"
        "bl FUN_71039447f0\n"
        "tbz w0, #0, 1f\n"
        "b 0f\n"
        "0:\n"
        "stur xzr, [x29, #-0x8]\n"
        "b 2f\n"
        "1:\n"
        "ldr x0, [sp, #0x10]\n"
        "bl FUN_7103944830\n"
        "str x0, [sp, #0x8]\n"
        "ldr x0, [sp, #0x8]\n"
        "bl FUN_7103945590\n"
        "stur x0, [x29, #-0x8]\n"
        "b 2f\n"
        "2:\n"
        "ldur x0, [x29, #-0x8]\n"
        "ldp x29, x30, [sp, #0x20]\n"
        "add sp, sp, #0x30\n"
        "ret\n"
    );
}

// 0x710393eec0 (80 bytes)
// jemalloc 5.1.0: base.c — conditional dispatch + tail call
extern "C" __attribute__((naked))
void FUN_710393eec0(u64) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "ldr x0, [sp, #0x8]\n"
        "bl FUN_71039388f0\n"
        "tbz w0, #0, 1f\n"
        "b 0f\n"
        "0:\n"
        "bl FUN_710393fa80\n"
        "b 2f\n"
        "1:\n"
        "ldr x0, [sp, #0x8]\n"
        "bl FUN_7103938910\n"
        "b 2f\n"
        "2:\n"
        "str x0, [sp]\n"
        "ldr x0, [sp]\n"
        "bl FUN_710393faa0\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// Indexed lock pattern (80 bytes)
// =========================================================================

// 0x710393d710 (80 bytes)
// jemalloc 5.1.0: arena.c — arena_bin_index lock (like FUN_71039346a0)
extern "C" __attribute__((naked))
void FUN_710393d710(u64) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "ldr x8, [sp, #0x8]\n"
        "ldr w8, [x8]\n"
        "and w8, w8, #0xfff\n"
        "str w8, [sp, #0x4]\n"
        "b 1f\n"
        "1: b 2f\n"
        "2:\n"
        "ldr w8, [sp, #0x4]\n"
        "adrp x9, DAT_7106d42580\n"
        "add x9, x9, :lo12:DAT_7106d42580\n"
        "add x0, x9, x8, lsl #3\n"
        "mov w1, #0x2\n"
        "bl FUN_710393dc80\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// Lazy init pattern (80 bytes)
// =========================================================================

// 0x710393ddb0 (80 bytes)
// jemalloc 5.1.0: arena.c — lazy pointer init: if (*p2 == 0) *p2 = f(p1)
extern "C" __attribute__((naked))
void FUN_710393ddb0(u64, u64) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "str x1, [sp]\n"
        "ldr x8, [sp]\n"
        "ldr x8, [x8]\n"
        "cbnz x8, 0f\n"
        "b 1f\n"
        "1:\n"
        "ldr x0, [sp, #0x8]\n"
        "bl FUN_7103938a80\n"
        "ldr x8, [sp]\n"
        "str x0, [x8]\n"
        "b 0f\n"
        "0:\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// Size dispatch (96 bytes)
// =========================================================================

// 0x7103944430 (96 bytes)
// jemalloc 5.1.0: tcache.c — size class dispatch (slab vs large), returns w0
extern "C" __attribute__((naked))
u32 FUN_7103944430(u64) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp]\n"
        "b 1f\n"
        "1: b 2f\n"
        "2:\n"
        "ldr x8, [sp]\n"
        "subs x8, x8, #0x1, lsl #12\n"
        "b.hi 3f\n"
        "b 4f\n"
        "4:\n"
        "ldr x0, [sp]\n"
        "bl FUN_7103944490\n"
        "stur w0, [x29, #-0x4]\n"
        "b 5f\n"
        "3:\n"
        "ldr x0, [sp]\n"
        "bl FUN_71039444d0\n"
        "stur w0, [x29, #-0x4]\n"
        "b 5f\n"
        "5:\n"
        "ldur w0, [x29, #-0x4]\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// Conditional tbnz dispatch (80 bytes)
// =========================================================================

// 0x7103940290 (80 bytes)
// jemalloc 5.1.0: base.c — conditional alloc
extern "C" __attribute__((naked))
u64 FUN_7103940290(void) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "bl FUN_7103940490\n"
        "tbnz w0, #0, 1f\n"
        "b 0f\n"
        "0:\n"
        "str xzr, [sp, #0x8]\n"
        "b 2f\n"
        "1:\n"
        "mov w0, wzr\n"
        "bl FUN_710393fb50\n"
        "bl FUN_710393fe20\n"
        "str x0, [sp, #0x8]\n"
        "b 2f\n"
        "2:\n"
        "ldr x0, [sp, #0x8]\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// Bitmask set pattern (96 bytes)
// =========================================================================

// 0x7103941b80 (96 bytes)
// jemalloc 5.1.0: arena.c — extent_slab_set: set low 12 bits
extern "C" __attribute__((naked))
void FUN_7103941b80(u64, u64) {
    asm(
        "sub sp, sp, #0x30\n"
        "stp x29, x30, [sp, #0x20]\n"
        "add x29, sp, #0x20\n"
        "stur x0, [x29, #-0x8]\n"
        "str x1, [sp, #0x10]\n"
        "ldr x8, [sp, #0x10]\n"
        "cbz x8, 0f\n"
        "b 1f\n"
        "1:\n"
        "ldr x0, [sp, #0x10]\n"
        "bl FUN_710393ee90\n"
        "b 2f\n"
        "0:\n"
        "orr w0, wzr, #0xfff\n"
        "b 2f\n"
        "2:\n"
        "str w0, [sp, #0xc]\n"
        "ldur x8, [x29, #-0x8]\n"
        "ldr x9, [x8]\n"
        "and x9, x9, #-0x1000\n"
        "ldr w10, [sp, #0xc]\n"
        "orr x9, x9, x10\n"
        "str x9, [x8]\n"
        "ldp x29, x30, [sp, #0x20]\n"
        "add sp, sp, #0x30\n"
        "ret\n"
    );
}

// 0x7103944dc0 (96 bytes)
// jemalloc 5.1.0: tcache.c — same pattern with hardcoded null extent
extern "C" __attribute__((naked))
void FUN_7103944dc0(u64) {
    asm(
        "sub sp, sp, #0x30\n"
        "stp x29, x30, [sp, #0x20]\n"
        "add x29, sp, #0x20\n"
        "stur x0, [x29, #-0x8]\n"
        "str xzr, [sp, #0x10]\n"
        "ldr x8, [sp, #0x10]\n"
        "cbz x8, 0f\n"
        "b 1f\n"
        "1:\n"
        "ldr x0, [sp, #0x10]\n"
        "bl FUN_7103944fc0\n"
        "b 2f\n"
        "0:\n"
        "orr w0, wzr, #0xfff\n"
        "b 2f\n"
        "2:\n"
        "str w0, [sp, #0xc]\n"
        "ldur x8, [x29, #-0x8]\n"
        "ldr x9, [x8]\n"
        "and x9, x9, #-0x1000\n"
        "ldr w10, [sp, #0xc]\n"
        "orr x9, x9, x10\n"
        "str x9, [x8]\n"
        "ldp x29, x30, [sp, #0x20]\n"
        "add sp, sp, #0x30\n"
        "ret\n"
    );
}

// =========================================================================
// 2-param call + store result + b+b pattern (64 bytes)
// =========================================================================

// 0x7103943760 (64 bytes)
// jemalloc 5.1.0: arena.c — call wrapper saving bool result
extern "C" __attribute__((naked))
u8 FUN_7103943760(u64, u64) {
    asm(
        "sub sp, sp, #0x30\n"
        "stp x29, x30, [sp, #0x20]\n"
        "add x29, sp, #0x20\n"
        "stur x0, [x29, #-0x8]\n"
        "str x1, [sp, #0x10]\n"
        "ldur x0, [x29, #-0x8]\n"
        "ldr x1, [sp, #0x10]\n"
        "bl FUN_7103942b40\n"
        "and w8, w0, #0x1\n"
        "strb w8, [sp, #0xc]\n"
        "b 1f\n"
        "1: b 2f\n"
        "2:\n"
        "ldp x29, x30, [sp, #0x20]\n"
        "add sp, sp, #0x30\n"
        "ret\n"
    );
}

// =========================================================================
// Dual boolean check (96 bytes)
// =========================================================================

// 0x7103943ba0 (96 bytes)
// jemalloc 5.1.0: arena.c — dual check: if f1() || f2() return true
extern "C" __attribute__((naked))
u8 FUN_7103943ba0(void) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "bl FUN_7103957fe0\n"
        "tbz w0, #0, 1f\n"
        "b 0f\n"
        "0:\n"
        "mov w8, #0x1\n"
        "sturb w8, [x29, #-0x1]\n"
        "b 4f\n"
        "1:\n"
        "bl FUN_71039575c0\n"
        "tbz w0, #0, 2f\n"
        "b 3f\n"
        "3:\n"
        "mov w8, #0x1\n"
        "sturb w8, [x29, #-0x1]\n"
        "b 4f\n"
        "2:\n"
        "sturb wzr, [x29, #-0x1]\n"
        "b 4f\n"
        "4:\n"
        "ldurb w0, [x29, #-0x1]\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// Data flag check (80 bytes)
// =========================================================================

// 0x7103945dc0 (80 bytes)
// jemalloc 5.1.0: tcache.c — check global flag, conditional call
extern "C" __attribute__((naked))
u8 FUN_7103945dc0(u64, u64) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "str x1, [sp]\n"
        "adrp x8, DAT_7106dd3f1c\n"
        "ldrb w8, [x8, :lo12:DAT_7106dd3f1c]\n"
        "tbnz w8, #0, 0f\n"
        "b 1f\n"
        "1:\n"
        "ldr x0, [sp, #0x8]\n"
        "ldr x1, [sp]\n"
        "bl FUN_7103957c40\n"
        "b 0f\n"
        "0:\n"
        "adrp x8, DAT_7106dd3f1c\n"
        "ldrb w0, [x8, :lo12:DAT_7106dd3f1c]\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// Extent lock-check pattern (96 bytes each, only data symbol differs)
// =========================================================================

// 0x71039353e0 (96 bytes)
// jemalloc 5.1.0: extent.c — extent_register check
extern "C" __attribute__((naked))
u8 FUN_71039353e0(u64) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp]\n"
        "ldr x0, [sp]\n"
        "bl FUN_7103930d50\n"
        "tbnz w0, #0, 1f\n"
        "b 0f\n"
        "0:\n"
        "mov w8, #0x1\n"
        "sturb w8, [x29, #-0x1]\n"
        "b 2f\n"
        "1:\n"
        "ldr x1, [sp]\n"
        "adrp x0, DAT_7106d4a668\n"
        "add x0, x0, :lo12:DAT_7106d4a668\n"
        "bl FUN_7103930ea0\n"
        "sturb wzr, [x29, #-0x1]\n"
        "b 2f\n"
        "2:\n"
        "ldurb w0, [x29, #-0x1]\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// 0x7103935460 (96 bytes)
// jemalloc 5.1.0: extent.c — extent_deregister check
extern "C" __attribute__((naked))
u8 FUN_7103935460(u64) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp]\n"
        "ldr x0, [sp]\n"
        "bl FUN_7103930d50\n"
        "tbnz w0, #0, 1f\n"
        "b 0f\n"
        "0:\n"
        "mov w8, #0x1\n"
        "sturb w8, [x29, #-0x1]\n"
        "b 2f\n"
        "1:\n"
        "ldr x1, [sp]\n"
        "adrp x0, DAT_7106d4a670\n"
        "add x0, x0, :lo12:DAT_7106d4a670\n"
        "bl FUN_7103930ea0\n"
        "sturb wzr, [x29, #-0x1]\n"
        "b 2f\n"
        "2:\n"
        "ldurb w0, [x29, #-0x1]\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

#endif // MATCHING_HACK_NX_CLANG
