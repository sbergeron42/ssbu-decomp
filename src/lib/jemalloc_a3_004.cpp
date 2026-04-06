// jemalloc 5.1.0 — arena/rtree/extent helpers batch 4
// Pool-a decomp: addresses 0x7103933290 — 0x7103935dd0
// jemalloc compiled at -O0 in NX build

#include "types.h"

#ifdef MATCHING_HACK_NX_CLANG

extern "C" {
// Callee declarations
u64  FUN_71039316d0(u64, u32);
void FUN_71039298a0(u64, u32, u64);
void FUN_7103933610(void);
u32  FUN_7103930b40(u64);
u64  FUN_7103934390(u64, u32, u64);
void FUN_7103934410(u64, u64, u64);
void FUN_7103934580(u64);
u64  FUN_7103934650(u64, u64);
u64  FUN_71039346a0(u64);
void FUN_71039346f0(u64, u64, u64, u64);
void FUN_7103932090(u64, u64);
void FUN_7103932870(u64);
u64  FUN_71039345b0(u64, u64);
void FUN_710392f2d0(u64, u64);
void FUN_71039340e0(u64, u64, u64, u64, u32);
void FUN_710392f460(u64, u64);
u64  FUN_710392eec0(u64);
void FUN_710392ef20(u64, u32);
void FUN_7103934de0(u64, u64, u64, u64, u64, u32);
void FUN_7103935300(u64, u64, u64, u32, u64, u64);

// Data symbols
__attribute__((visibility("hidden"))) extern u8 DAT_7106d42580;
__attribute__((visibility("hidden"))) extern u8 DAT_71052935a0;
__attribute__((visibility("hidden"))) extern u8 DAT_7105293560;
__attribute__((visibility("hidden"))) extern u8 DAT_7106d424a0;
__attribute__((visibility("hidden"))) extern u8 DAT_7106d4a594;
__attribute__((visibility("hidden"))) extern u8 DAT_7104862158;
}

// =========================================================================
// 96-byte functions
// =========================================================================

// 0x71039345f0 (96 bytes)
// jemalloc 5.1.0: arena.c — arena_new_create
// Calls arena init, gets arena, registers, then purges
extern "C" __attribute__((naked))
void FUN_71039345f0(u64, u64) {
    asm(
        "sub sp, sp, #0x30\n"
        "stp x29, x30, [sp, #0x20]\n"
        "add x29, sp, #0x20\n"
        "stur x0, [x29, #-0x8]\n"
        "str x1, [sp, #0x10]\n"
        "ldur x0, [x29, #-0x8]\n"
        "ldr x1, [sp, #0x10]\n"
        "bl FUN_7103934650\n"
        "str x0, [sp, #0x8]\n"
        "ldr x0, [sp, #0x8]\n"
        "bl FUN_71039346a0\n"
        "str x0, [sp]\n"
        "ldur x0, [x29, #-0x8]\n"
        "ldr x1, [sp]\n"
        "ldr x2, [sp, #0x8]\n"
        "ldr x3, [sp, #0x10]\n"
        "bl FUN_71039346f0\n"
        "ldur x0, [x29, #-0x8]\n"
        "ldr x1, [sp]\n"
        "bl FUN_7103932090\n"
        "ldp x29, x30, [sp, #0x20]\n"
        "add sp, sp, #0x30\n"
        "ret\n"
    );
}

// 0x71039352a0 (96 bytes)
// jemalloc 5.1.0: arena.c — arena extent forwarding wrapper
// Saves params, reloads with bool masking, calls FUN_7103935300
extern "C" __attribute__((naked))
void FUN_71039352a0(u64, u64, u64, u32, u64, u64) {
    asm(
        "sub sp, sp, #0x40\n"
        "stp x29, x30, [sp, #0x30]\n"
        "add x29, sp, #0x30\n"
        "stur x0, [x29, #-0x8]\n"
        "stur x1, [x29, #-0x10]\n"
        "str x2, [sp, #0x18]\n"
        "and w8, w3, #0x1\n"
        "strb w8, [sp, #0x14]\n"
        "str x4, [sp, #0x8]\n"
        "str x5, [sp]\n"
        "ldur x0, [x29, #-0x8]\n"
        "ldur x1, [x29, #-0x10]\n"
        "ldr x2, [sp, #0x18]\n"
        "ldr x4, [sp, #0x8]\n"
        "ldr x5, [sp]\n"
        "ldrb w8, [sp, #0x14]\n"
        "and w3, w8, #0x1\n"
        "bl FUN_7103935300\n"
        "ldp x29, x30, [sp, #0x30]\n"
        "add sp, sp, #0x40\n"
        "ret\n"
    );
}

// =========================================================================
// 112-byte functions
// =========================================================================

// 0x7103934d70 (112 bytes)
// jemalloc 5.1.0: arena.c — arena_extent_alloc_large_prep
// Gets tsdn, initializes flags, dispatches to alloc
extern "C" __attribute__((naked))
void FUN_7103934d70(u64, u64, u64, u64) {
    asm(
        "sub sp, sp, #0x40\n"
        "stp x29, x30, [sp, #0x30]\n"
        "add x29, sp, #0x30\n"
        "stur x0, [x29, #-0x8]\n"
        "stur x1, [x29, #-0x10]\n"
        "str x2, [sp, #0x18]\n"
        "str x3, [sp, #0x10]\n"
        "str xzr, [sp, #0x8]\n"
        "orr w8, wzr, #0x1\n"
        "strb w8, [sp, #0x4]\n"
        "ldur x0, [x29, #-0x8]\n"
        "bl FUN_710392eec0\n"
        "mov w1, wzr\n"
        "bl FUN_710392ef20\n"
        "ldur x0, [x29, #-0x8]\n"
        "ldur x1, [x29, #-0x10]\n"
        "ldr x2, [sp, #0x18]\n"
        "ldr x3, [sp, #0x10]\n"
        "ldr x4, [sp, #0x8]\n"
        "ldrb w8, [sp, #0x4]\n"
        "and w5, w8, #0x1\n"
        "bl FUN_7103934de0\n"
        "ldp x29, x30, [sp, #0x30]\n"
        "add sp, sp, #0x40\n"
        "ret\n"
    );
}

// 0x7103935d70 (112 bytes)
// jemalloc 5.1.0: atomic.h — atomic_store_u32
// Memory order dispatch for 32-bit store: 3=release(stlr), 5=seq_cst(stlr)
extern "C" __attribute__((naked))
void FUN_7103935d70(u64, u32) {
    asm(
        "sub sp, sp, #0x20\n"
        "str x0, [sp, #0x18]\n"
        "str wzr, [sp, #0x14]\n"
        "str wzr, [sp, #0x10]\n"
        "ldr x8, [sp, #0x18]\n"
        "ldr w9, [sp, #0x10]\n"
        "ldr w10, [sp, #0x14]\n"
        "str w10, [sp, #0xc]\n"
        "subs w10, w9, #0x3\n"
        "b.eq 3f\n"
        "b 1f\n"
        "1:\n"
        "subs w9, w9, #0x5\n"
        "b.eq 4f\n"
        "b 2f\n"
        "2:\n"
        "ldr w9, [sp, #0xc]\n"
        "str w9, [x8]\n"
        "b 5f\n"
        "3:\n"
        "ldr w9, [sp, #0xc]\n"
        "stlr w9, [x8]\n"
        "b 5f\n"
        "4:\n"
        "ldr w9, [sp, #0xc]\n"
        "stlr w9, [x8]\n"
        "b 5f\n"
        "5:\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 128-byte functions
// =========================================================================

// 0x7103934390 (128 bytes)
// jemalloc 5.1.0: arena.c — arena_bin_nonfull_slab_get
// 6 b+4 stubs, uses x19, computes offset and calls lookup
extern "C" __attribute__((naked))
u64 FUN_7103934390(u64, u32, u64) {
    asm(
        "sub sp, sp, #0x40\n"
        "str x19, [sp, #0x20]\n"
        "stp x29, x30, [sp, #0x30]\n"
        "add x29, sp, #0x30\n"
        "stur x0, [x29, #-0x8]\n"
        "stur w1, [x29, #-0x14]\n"
        "str x2, [sp, #0x10]\n"
        "b 1f\n"
        "1: b 2f\n"
        "2: b 3f\n"
        "3: b 4f\n"
        "4: b 5f\n"
        "5: b 6f\n"
        "6:\n"
        "ldr x19, [sp, #0x10]\n"
        "ldur x0, [x29, #-0x8]\n"
        "bl FUN_7103932870\n"
        "subs x8, x19, x0\n"
        "str x8, [sp, #0x8]\n"
        "ldur w8, [x29, #-0x14]\n"
        "adrp x9, DAT_7106d4a594\n"
        "add x9, x9, :lo12:DAT_7106d4a594\n"
        "add x0, x9, x8, lsl #2\n"
        "ldr x1, [sp, #0x8]\n"
        "bl FUN_71039345b0\n"
        "str x0, [sp]\n"
        "b 7f\n"
        "7: b 8f\n"
        "8:\n"
        "ldr x0, [sp]\n"
        "ldp x29, x30, [sp, #0x30]\n"
        "ldr x19, [sp, #0x20]\n"
        "add sp, sp, #0x40\n"
        "ret\n"
    );
}

// 0x71039346f0 (128 bytes)
// jemalloc 5.1.0: arena.c — arena_bin_register
// Computes bin offset, calls rtree register + arena register
extern "C" __attribute__((naked))
void FUN_71039346f0(u64, u64, u64, u64) {
    asm(
        "sub sp, sp, #0x40\n"
        "stp x29, x30, [sp, #0x30]\n"
        "add x29, sp, #0x30\n"
        "stur x0, [x29, #-0x8]\n"
        "stur x1, [x29, #-0x10]\n"
        "str x2, [sp, #0x18]\n"
        "str x3, [sp, #0x10]\n"
        "ldr x0, [sp, #0x18]\n"
        "bl FUN_7103930b40\n"
        "str w0, [sp, #0xc]\n"
        "ldur x8, [x29, #-0x10]\n"
        "ldr w9, [sp, #0xc]\n"
        "mov w10, #0x138\n"
        "madd x8, x9, x10, x8\n"
        "mov w9, #0x3e20\n"
        "add x8, x8, x9\n"
        "str x8, [sp]\n"
        "ldur x0, [x29, #-0x8]\n"
        "ldr x1, [sp]\n"
        "bl FUN_710392f2d0\n"
        "ldur x0, [x29, #-0x8]\n"
        "ldur x1, [x29, #-0x10]\n"
        "ldr x2, [sp, #0x18]\n"
        "ldr x3, [sp, #0x10]\n"
        "mov w4, wzr\n"
        "bl FUN_71039340e0\n"
        "ldur x0, [x29, #-0x8]\n"
        "ldr x1, [sp]\n"
        "bl FUN_710392f460\n"
        "ldp x29, x30, [sp, #0x30]\n"
        "add sp, sp, #0x40\n"
        "ret\n"
    );
}

// =========================================================================
// 144-byte functions
// =========================================================================

// 0x7103933290 (144 bytes)
// jemalloc 5.1.0: arena.c — arena_get
// Looks up arena by index, falls back to slow path if null
extern "C" __attribute__((naked))
u64 FUN_7103933290(u64, u32) {
    asm(
        "sub sp, sp, #0x30\n"
        "stp x29, x30, [sp, #0x20]\n"
        "add x29, sp, #0x20\n"
        "stur x0, [x29, #-0x8]\n"
        "stur w1, [x29, #-0xc]\n"
        "orr w8, wzr, #0x1\n"
        "strb w8, [sp, #0x10]\n"
        "b 1f\n"
        "1: b 2f\n"
        "2:\n"
        "ldur w8, [x29, #-0xc]\n"
        "adrp x9, DAT_7106d42580\n"
        "add x9, x9, :lo12:DAT_7106d42580\n"
        "add x0, x9, x8, lsl #3\n"
        "orr w1, wzr, #0x2\n"
        "bl FUN_71039316d0\n"
        "str x0, [sp, #0x8]\n"
        "ldr x8, [sp, #0x8]\n"
        "cbnz x8, 6f\n"
        "b 3f\n"
        "3:\n"
        "ldrb w8, [sp, #0x10]\n"
        "tbz w8, #0, 5f\n"
        "b 4f\n"
        "4:\n"
        "ldur x0, [x29, #-0x8]\n"
        "ldur w1, [x29, #-0xc]\n"
        "adrp x2, DAT_71052935a0\n"
        "add x2, x2, :lo12:DAT_71052935a0\n"
        "bl FUN_71039298a0\n"
        "str x0, [sp, #0x8]\n"
        "b 5f\n"
        "5: b 6f\n"
        "6:\n"
        "ldr x0, [sp, #0x8]\n"
        "ldp x29, x30, [sp, #0x20]\n"
        "add sp, sp, #0x30\n"
        "ret\n"
    );
}

// 0x7103933420 (144 bytes)
// jemalloc 5.1.0: arena.c — arena_nthreads_max_get
// Reads narenas_auto, returns based on percpu_arena mode
extern "C" __attribute__((naked))
u32 FUN_7103933420(u32) {
    asm(
        "sub sp, sp, #0x10\n"
        "str w0, [sp, #0x8]\n"
        "b 1f\n"
        "1: b 2f\n"
        "2:\n"
        "ldr w8, [sp, #0x8]\n"
        "subs w8, w8, #0x4\n"
        "b.ne 7f\n"
        "b 3f\n"
        "3:\n"
        "adrp x8, DAT_7106d424a0\n"
        "ldr w8, [x8, :lo12:DAT_7106d424a0]\n"
        "subs w8, w8, #0x2\n"
        "b.cc 7f\n"
        "b 4f\n"
        "4:\n"
        "adrp x8, DAT_7106d424a0\n"
        "ldrb w8, [x8, :lo12:DAT_7106d424a0]\n"
        "tbz w8, #0, 6f\n"
        "b 5f\n"
        "5:\n"
        "adrp x8, DAT_7106d424a0\n"
        "ldr w8, [x8, :lo12:DAT_7106d424a0]\n"
        "lsr w8, w8, #0x1\n"
        "add w8, w8, #0x1\n"
        "str w8, [sp, #0xc]\n"
        "b 8f\n"
        "6:\n"
        "adrp x8, DAT_7106d424a0\n"
        "ldr w8, [x8, :lo12:DAT_7106d424a0]\n"
        "lsr w8, w8, #0x1\n"
        "str w8, [sp, #0xc]\n"
        "b 8f\n"
        "7:\n"
        "adrp x8, DAT_7106d424a0\n"
        "ldr w8, [x8, :lo12:DAT_7106d424a0]\n"
        "str w8, [sp, #0xc]\n"
        "b 8f\n"
        "8:\n"
        "ldr w0, [sp, #0xc]\n"
        "add sp, sp, #0x10\n"
        "ret\n"
    );
}

// 0x71039334b0 (144 bytes)
// jemalloc 5.1.0: arena.c — arena_choose_ind
// Gets current CPU, checks opt_percpu_arena, computes arena index
extern "C" __attribute__((naked))
u32 FUN_71039334b0(void) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "b 1f\n"
        "1: b 2f\n"
        "2:\n"
        "bl FUN_7103933610\n"
        "stur w0, [x29, #-0x4]\n"
        "b 3f\n"
        "3: b 4f\n"
        "4:\n"
        "adrp x8, DAT_7105293560\n"
        "ldr w8, [x8, :lo12:DAT_7105293560]\n"
        "subs w8, w8, #0x3\n"
        "b.eq 7f\n"
        "b 5f\n"
        "5:\n"
        "ldur w8, [x29, #-0x4]\n"
        "adrp x9, DAT_7106d424a0\n"
        "ldr w9, [x9, :lo12:DAT_7106d424a0]\n"
        "subs w8, w8, w9, lsr #1\n"
        "b.cs 8f\n"
        "b 7f\n"
        "7:\n"
        "ldur w8, [x29, #-0x4]\n"
        "str w8, [sp, #0x8]\n"
        "b 9f\n"
        "8: b 81f\n"
        "81: b 82f\n"
        "82:\n"
        "ldur w8, [x29, #-0x4]\n"
        "adrp x9, DAT_7106d424a0\n"
        "ldr w9, [x9, :lo12:DAT_7106d424a0]\n"
        "subs w8, w8, w9, lsr #1\n"
        "str w8, [sp, #0x8]\n"
        "b 9f\n"
        "9:\n"
        "ldr w0, [sp, #0x8]\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// 0x7103934220 (144 bytes)
// jemalloc 5.1.0: arena.c — arena_bin_choose
// Looks up bin info, computes bin pointer, dispatches to slab alloc
extern "C" __attribute__((naked))
void FUN_7103934220(u64, u64, u64) {
    asm(
        "sub sp, sp, #0x40\n"
        "stp x29, x30, [sp, #0x30]\n"
        "add x29, sp, #0x30\n"
        "stur x0, [x29, #-0x8]\n"
        "stur x1, [x29, #-0x10]\n"
        "str x2, [sp, #0x18]\n"
        "ldur x0, [x29, #-0x8]\n"
        "bl FUN_7103930b40\n"
        "str w0, [sp, #0x14]\n"
        "ldr w8, [sp, #0x14]\n"
        "mov w9, #0x58\n"
        "adrp x10, DAT_7104862158\n"
        "add x10, x10, :lo12:DAT_7104862158\n"
        "madd x8, x8, x9, x10\n"
        "str x8, [sp, #0x8]\n"
        "ldur x0, [x29, #-0x8]\n"
        "ldr w1, [sp, #0x14]\n"
        "ldr x2, [sp, #0x18]\n"
        "bl FUN_7103934390\n"
        "str x0, [sp]\n"
        "b 1f\n"
        "1: b 2f\n"
        "2: b 3f\n"
        "3: b 4f\n"
        "4:\n"
        "ldur x0, [x29, #-0x10]\n"
        "ldr x8, [sp, #0x8]\n"
        "add x1, x8, #0x18\n"
        "ldr x2, [sp]\n"
        "bl FUN_7103934410\n"
        "ldur x0, [x29, #-0x8]\n"
        "bl FUN_7103934580\n"
        "ldp x29, x30, [sp, #0x30]\n"
        "add sp, sp, #0x40\n"
        "ret\n"
    );
}

#endif // MATCHING_HACK_NX_CLANG
