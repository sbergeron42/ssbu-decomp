// jemalloc 5.1.0 — atomic ops, decay init, extent alloc, page mask
// Pool-a decomp: addresses 0x7103930dc0 — 0x7103931a90
// jemalloc compiled at -O0 in NX build

#include "types.h"

#ifdef MATCHING_HACK_NX_CLANG

extern "C" {
// Callee declarations
void FUN_7103930e70(u64, u64);
void FUN_7103957670(u64, u64);
void FUN_7103957810(u64);
void FUN_7103957890(u64);
void FUN_710392f750(u64);
void FUN_71039bfcf0(u64, u32, u32);
u64  FUN_7103930160(u64);
void FUN_7103930970(u64, u64);
void FUN_710392ee30(u64, u64, u64, u64);
u64  FUN_7103931740(u64, u64, u64, u64, u32);
u64  FUN_7103931640(u64, u64, u64, u32);
u32  FUN_7103931690(u64);
u32  FUN_71039316b0(u64);

// Forward declarations (defined below)
u64  FUN_71039315b0(u64, u64, u64, u64, u32);

// Data symbols
__attribute__((visibility("hidden"))) extern u8 DAT_7106d4a678;
}

// =========================================================================
// 96-byte functions
// =========================================================================

// 0x7103931450 (96 bytes)
// jemalloc 5.1.0: arena.c — arena_extent_alloc_large
// Calls page size calc, updates nactive, then arena alloc
extern "C" __attribute__((naked))
void FUN_7103931450(u64, u64, u64) {
    asm(
        "sub sp, sp, #0x40\n"
        "str x19, [sp, #0x20]\n"
        "stp x29, x30, [sp, #0x30]\n"
        "add x29, sp, #0x30\n"
        "stur x0, [x29, #-0x8]\n"
        "str x1, [sp, #0x18]\n"
        "str x2, [sp, #0x10]\n"
        "ldr x19, [sp, #0x18]\n"
        "ldr x0, [sp, #0x10]\n"
        "bl FUN_7103930160\n"
        "lsr x1, x0, #0x10\n"
        "mov x0, x19\n"
        "bl FUN_7103930970\n"
        "str xzr, [sp, #0x8]\n"
        "ldur x0, [x29, #-0x8]\n"
        "ldr x1, [sp, #0x18]\n"
        "ldr x3, [sp, #0x10]\n"
        "add x2, sp, #0x8\n"
        "bl FUN_710392ee30\n"
        "ldp x29, x30, [sp, #0x30]\n"
        "ldr x19, [sp, #0x20]\n"
        "add sp, sp, #0x40\n"
        "ret\n"
    );
}

// 0x7103931a90 (96 bytes)
// jemalloc 5.1.0: pages.h — page_addr_mask
// Computes page-aligned mask: addr & ~((1 << (64-32)) - 1)
extern "C" __attribute__((naked))
u64 FUN_7103931a90(u64) {
    asm(
        "sub sp, sp, #0x20\n"
        "str x0, [sp, #0x18]\n"
        "orr w8, wzr, #0x40\n"
        "str w8, [sp, #0x14]\n"
        "orr w8, wzr, #0x20\n"
        "str w8, [sp, #0x10]\n"
        "ldr w8, [sp, #0x14]\n"
        "ldr w9, [sp, #0x10]\n"
        "subs w8, w8, w9\n"
        "str w8, [sp, #0xc]\n"
        "ldr w8, [sp, #0xc]\n"
        "orr w9, wzr, #0x1\n"
        "lsl x8, x9, x8\n"
        "subs x8, x8, #0x1\n"
        "mvn x8, x8\n"
        "str x8, [sp]\n"
        "ldr x8, [sp, #0x18]\n"
        "ldr x9, [sp]\n"
        "and x0, x8, x9\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 112-byte functions
// =========================================================================

// 0x7103931500 (112 bytes)
// jemalloc 5.1.0: atomic.h — atomic_store_u64 (duplicate pattern)
// Same structure as FUN_7103930ea0
extern "C" __attribute__((naked))
void FUN_7103931500(u64, u64) {
    asm(
        "sub sp, sp, #0x20\n"
        "str x0, [sp, #0x18]\n"
        "str x1, [sp, #0x10]\n"
        "str wzr, [sp, #0xc]\n"
        "ldr x8, [sp, #0x18]\n"
        "ldr w9, [sp, #0xc]\n"
        "ldr x10, [sp, #0x10]\n"
        "str x10, [sp]\n"
        "subs w10, w9, #0x3\n"
        "b.eq 3f\n"
        "b 1f\n"
        "1:\n"
        "subs w9, w9, #0x5\n"
        "b.eq 4f\n"
        "b 2f\n"
        "2:\n"
        "ldr x9, [sp]\n"
        "str x9, [x8]\n"
        "b 5f\n"
        "3:\n"
        "ldr x9, [sp]\n"
        "stlr x9, [x8]\n"
        "b 5f\n"
        "4:\n"
        "ldr x9, [sp]\n"
        "stlr x9, [x8]\n"
        "b 5f\n"
        "5:\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// 0x71039316d0 (112 bytes)
// jemalloc 5.1.0: atomic.h — atomic_load_u64
// Memory order dispatch: 1,2=acquire(ldar), 5=seq_cst(ldar), else=relaxed(ldr)
extern "C" __attribute__((naked))
u64 FUN_71039316d0(u64, u32) {
    asm(
        "sub sp, sp, #0x20\n"
        "str x0, [sp, #0x18]\n"
        "str w1, [sp, #0x14]\n"
        "ldr x8, [sp, #0x18]\n"
        "str x8, [sp, #0x8]\n"
        "ldr x9, [sp, #0x8]\n"
        "ldr w10, [sp, #0x14]\n"
        "mov x8, sp\n"
        "subs w11, w10, #0x1\n"
        "subs w11, w11, #0x2\n"
        "b.cc 4f\n"
        "b 1f\n"
        "1:\n"
        "subs w10, w10, #0x5\n"
        "b.eq 5f\n"
        "b 2f\n"
        "2:\n"
        "ldr x9, [x9]\n"
        "str x9, [x8]\n"
        "b 6f\n"
        "4:\n"
        "ldar x9, [x9]\n"
        "str x9, [x8]\n"
        "b 6f\n"
        "5:\n"
        "ldar x9, [x9]\n"
        "str x9, [x8]\n"
        "b 6f\n"
        "6:\n"
        "ldr x0, [x8]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 144-byte functions
// =========================================================================

// 0x71039315b0 (144 bytes)
// jemalloc 5.1.0: arena.c — arena_extent_cache_find
// Calls FUN_7103931740 (extent alloc), returns result or null
extern "C" __attribute__((naked))
u64 FUN_71039315b0(u64, u64, u64, u64, u32) {
    asm(
        "sub sp, sp, #0x50\n"
        "stp x29, x30, [sp, #0x40]\n"
        "add x29, sp, #0x40\n"
        "stur x0, [x29, #-0x10]\n"
        "stur x1, [x29, #-0x18]\n"
        "str x2, [sp, #0x20]\n"
        "str x3, [sp, #0x18]\n"
        "and w8, w4, #0x1\n"
        "strb w8, [sp, #0x14]\n"
        "ldur x0, [x29, #-0x10]\n"
        "ldur x1, [x29, #-0x18]\n"
        "ldr x2, [sp, #0x20]\n"
        "ldr x3, [sp, #0x18]\n"
        "ldrb w8, [sp, #0x14]\n"
        "and w4, w8, #0x1\n"
        "bl FUN_7103931740\n"
        "str x0, [sp, #0x8]\n"
        "ldrb w8, [sp, #0x14]\n"
        "tbnz w8, #0, 7f\n"
        "b 1f\n"
        "1:\n"
        "ldr x8, [sp, #0x8]\n"
        "cbnz x8, 7f\n"
        "b 2f\n"
        "2:\n"
        "stur xzr, [x29, #-0x8]\n"
        "b 9f\n"
        "7: b 3f\n"
        "3: b 4f\n"
        "4:\n"
        "ldr x8, [sp, #0x8]\n"
        "stur x8, [x29, #-0x8]\n"
        "b 9f\n"
        "9:\n"
        "ldur x0, [x29, #-0x8]\n"
        "ldp x29, x30, [sp, #0x40]\n"
        "add sp, sp, #0x50\n"
        "ret\n"
    );
}

// =========================================================================
// 176-byte functions
// =========================================================================

// 0x7103930dc0 (176 bytes)
// jemalloc 5.1.0: arena.c — arena_decay_init
// Initializes decay state: time, epoch, jitter, counters
extern "C" __attribute__((naked))
void FUN_7103930dc0(u64, u64) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "str x1, [sp]\n"
        "ldr x0, [sp, #0x8]\n"
        "ldr x1, [sp]\n"
        "bl FUN_7103930e70\n"
        "ldr x8, [sp]\n"
        "subs x8, x8, #0x1\n"
        "b.lt 2f\n"
        "b 1f\n"
        "1:\n"
        "ldr x8, [sp, #0x8]\n"
        "add x0, x8, #0xa8\n"
        "ldr x8, [sp]\n"
        "mov w9, #0x4240\n"
        "movk w9, #0xf, lsl #16\n"
        "mul x1, x8, x9\n"
        "bl FUN_7103957670\n"
        "ldr x8, [sp, #0x8]\n"
        "add x0, x8, #0xa8\n"
        "bl FUN_7103957810\n"
        "b 2f\n"
        "2:\n"
        "ldr x8, [sp, #0x8]\n"
        "add x0, x8, #0xb0\n"
        "mov x1, xzr\n"
        "bl FUN_7103957670\n"
        "ldr x8, [sp, #0x8]\n"
        "add x0, x8, #0xb0\n"
        "bl FUN_7103957890\n"
        "ldr x8, [sp, #0x8]\n"
        "str x8, [x8, #0xb8]\n"
        "ldr x0, [sp, #0x8]\n"
        "bl FUN_710392f750\n"
        "ldr x8, [sp, #0x8]\n"
        "str xzr, [x8, #0xc8]\n"
        "ldr x8, [sp, #0x8]\n"
        "add x0, x8, #0xd0\n"
        "mov w2, #0x640\n"
        "mov w1, wzr\n"
        "bl FUN_71039bfcf0\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 208-byte functions
// =========================================================================

// 0x7103931380 (208 bytes)
// jemalloc 5.1.0: arena.c — arena_extent_alloc_large_hard
// Allocates via cache, then processes result through szind/slab accessors
extern "C" __attribute__((naked))
u8 FUN_7103931380(u64, u64, u64, u64, u64) {
    asm(
        "sub sp, sp, #0x60\n"
        "stp x29, x30, [sp, #0x50]\n"
        "add x29, sp, #0x50\n"
        "stur x0, [x29, #-0x10]\n"
        "adrp x8, DAT_7106d4a678\n"
        "add x8, x8, :lo12:DAT_7106d4a678\n"
        "stur x8, [x29, #-0x18]\n"
        "stur x1, [x29, #-0x20]\n"
        "str x2, [sp, #0x28]\n"
        "orr w8, wzr, #0x1\n"
        "strb w8, [sp, #0x24]\n"
        "str x3, [sp, #0x18]\n"
        "str x4, [sp, #0x10]\n"
        "ldur x0, [x29, #-0x10]\n"
        "ldur x1, [x29, #-0x18]\n"
        "ldur x2, [x29, #-0x20]\n"
        "ldr x3, [sp, #0x28]\n"
        "ldrb w8, [sp, #0x24]\n"
        "and w4, w8, #0x1\n"
        "bl FUN_71039315b0\n"
        "str x0, [sp, #0x8]\n"
        "ldrb w8, [sp, #0x24]\n"
        "tbnz w8, #0, 7f\n"
        "b 1f\n"
        "1:\n"
        "ldr x8, [sp, #0x8]\n"
        "cbnz x8, 7f\n"
        "b 2f\n"
        "2:\n"
        "orr w8, wzr, #0x1\n"
        "sturb w8, [x29, #-0x1]\n"
        "b 9f\n"
        "7:\n"
        "ldur x0, [x29, #-0x10]\n"
        "ldur x1, [x29, #-0x18]\n"
        "ldr x2, [sp, #0x8]\n"
        "ldrb w8, [sp, #0x24]\n"
        "and w3, w8, #0x1\n"
        "bl FUN_7103931640\n"
        "str x0, [sp]\n"
        "ldr x0, [sp]\n"
        "bl FUN_7103931690\n"
        "ldr x8, [sp, #0x18]\n"
        "str w0, [x8]\n"
        "ldr x0, [sp]\n"
        "bl FUN_71039316b0\n"
        "ldr x8, [sp, #0x10]\n"
        "and w9, w0, #0x1\n"
        "strb w9, [x8]\n"
        "sturb wzr, [x29, #-0x1]\n"
        "b 9f\n"
        "9:\n"
        "ldp x29, x30, [sp, #0x50]\n"
        "add sp, sp, #0x60\n"
        "ret\n"
    );
}

#endif // MATCHING_HACK_NX_CLANG
