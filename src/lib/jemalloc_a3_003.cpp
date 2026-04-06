// jemalloc 5.1.0 — rtree, arena decay, extent helpers
// Pool-a decomp: addresses 0x7103931af0 — 0x7103932b3c
// jemalloc compiled at -O0 in NX build

#include "types.h"

#ifdef MATCHING_HACK_NX_CLANG

extern "C" {
// Callee declarations
void FUN_7103931300(u64);
void FUN_7103938a80(u64);
u64  FUN_7103942420(u64, u64, u64, u64, u64);
void FUN_7103943900(u64, u64, u64, u64);
u64  FUN_7103932b40(u64);
u64  FUN_7103932ba0(u64, u64);
u64  FUN_7103932870(u64);
void FUN_7103932c80(u64);
void FUN_71039320f0(u64, u64);
void FUN_7103932130(u64, u64);
u32  FUN_71039327d0(u64, u64);
u32  FUN_7103932820(u64, u64);
void FUN_71039322b0(u64);
u64  FUN_710392eec0(u64);
void FUN_710392ef20(u64, u32);
u64  FUN_7103942660(u64, u64, u64, u64, u64, u64, u32, u32);
u64  FUN_710392f170(u64);
void FUN_710392c180(u64, u64);
void FUN_7103945780(u64, u64);

// Forward declarations
void FUN_7103931c40(u64, u64);

// Data symbols
__attribute__((visibility("hidden"))) extern u8 DAT_7104466100;
}

// =========================================================================
// 96-byte functions
// =========================================================================

// 0x7103932090 (96 bytes)
// jemalloc 5.1.0: arena.c — arena_purge_to_limit
// Dispatches to dirty+muzzy decay, then full purge
extern "C" __attribute__((naked))
void FUN_7103932090(u64, u64) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "str x1, [sp]\n"
        "ldr x0, [sp, #0x8]\n"
        "ldr x8, [sp]\n"
        "mov w9, #0x2ea0\n"
        "add x1, x8, x9\n"
        "bl FUN_71039320f0\n"
        "ldr x0, [sp, #0x8]\n"
        "ldr x8, [sp]\n"
        "mov w9, #0x35c0\n"
        "add x1, x8, x9\n"
        "bl FUN_71039320f0\n"
        "ldr x0, [sp, #0x8]\n"
        "ldr x1, [sp]\n"
        "bl FUN_7103932130\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 112-byte functions
// =========================================================================

// 0x7103931c40 (112 bytes)
// jemalloc 5.1.0: arena.c — arena_extent_cache_drain (loop)
// Calls rtree lookup in a loop until null, then exits
extern "C" __attribute__((naked))
void FUN_7103931c40(u64, u64) {
    asm(
        "sub sp, sp, #0x30\n"
        "stp x29, x30, [sp, #0x20]\n"
        "add x29, sp, #0x20\n"
        "stur x0, [x29, #-0x8]\n"
        "str x1, [sp, #0x10]\n"
        "ldr x0, [sp, #0x10]\n"
        "bl FUN_7103938a80\n"
        "str x0, [sp, #0x8]\n"
        "b 0f\n"
        "0:\n"
        "ldur x0, [x29, #-0x8]\n"
        "ldr x1, [sp, #0x10]\n"
        "mov w8, #0x2808\n"
        "add x3, x1, x8\n"
        "add x2, sp, #0x8\n"
        "mov x4, xzr\n"
        "bl FUN_7103942420\n"
        "str x0, [sp]\n"
        "cbz x0, 2f\n"
        "b 1f\n"
        "1:\n"
        "ldur x0, [x29, #-0x8]\n"
        "ldr x1, [sp, #0x10]\n"
        "ldr x3, [sp]\n"
        "add x2, sp, #0x8\n"
        "bl FUN_7103943900\n"
        "b 0b\n"
        "2:\n"
        "ldp x29, x30, [sp, #0x20]\n"
        "add sp, sp, #0x30\n"
        "ret\n"
    );
}

// 0x7103932240 (112 bytes)
// jemalloc 5.1.0: arena.c — arena_nthreads_dec
// Decrements thread counter, returns true if underflowed
extern "C" __attribute__((naked))
u8 FUN_7103932240(u64, u32) {
    asm(
        "sub sp, sp, #0x30\n"
        "stp x29, x30, [sp, #0x20]\n"
        "add x29, sp, #0x20\n"
        "str x0, [sp, #0x10]\n"
        "str w1, [sp, #0xc]\n"
        "ldr w8, [sp, #0xc]\n"
        "ldr x9, [sp, #0x10]\n"
        "ldr w10, [x9]\n"
        "subs w8, w10, w8\n"
        "str w8, [x9]\n"
        "ldr x8, [sp, #0x10]\n"
        "ldr w8, [x8]\n"
        "tbz w8, #0x1f, 3f\n"
        "b 1f\n"
        "1:\n"
        "ldr x0, [sp, #0x10]\n"
        "bl FUN_71039322b0\n"
        "orr w8, wzr, #0x1\n"
        "sturb w8, [x29, #-0x1]\n"
        "b 4f\n"
        "3:\n"
        "sturb wzr, [x29, #-0x1]\n"
        "b 4f\n"
        "4:\n"
        "ldurb w0, [x29, #-0x1]\n"
        "ldp x29, x30, [sp, #0x20]\n"
        "add sp, sp, #0x30\n"
        "ret\n"
    );
}

// 0x7103932720 (112 bytes)
// jemalloc 5.1.0: arena.c — arena_try_purge (try fast, then slow path)
extern "C" __attribute__((naked))
u32 FUN_7103932720(u64, u64) {
    asm(
        "sub sp, sp, #0x30\n"
        "stp x29, x30, [sp, #0x20]\n"
        "add x29, sp, #0x20\n"
        "str x0, [sp, #0x10]\n"
        "str x1, [sp, #0x8]\n"
        "ldr x0, [sp, #0x10]\n"
        "ldr x1, [sp, #0x8]\n"
        "bl FUN_71039327d0\n"
        "str w0, [sp, #0x4]\n"
        "ldr w8, [sp, #0x4]\n"
        "cbz w8, 2f\n"
        "b 1f\n"
        "1:\n"
        "ldr w8, [sp, #0x4]\n"
        "stur w8, [x29, #-0x4]\n"
        "b 3f\n"
        "2:\n"
        "ldr x0, [sp, #0x10]\n"
        "ldr x1, [sp, #0x8]\n"
        "bl FUN_7103932820\n"
        "str w0, [sp, #0x4]\n"
        "ldr w8, [sp, #0x4]\n"
        "stur w8, [x29, #-0x4]\n"
        "b 3f\n"
        "3:\n"
        "ldur w0, [x29, #-0x4]\n"
        "ldp x29, x30, [sp, #0x20]\n"
        "add sp, sp, #0x30\n"
        "ret\n"
    );
}

// =========================================================================
// 128-byte functions
// =========================================================================

// 0x7103931af0 (128 bytes)
// jemalloc 5.1.0: rtree.h — rtree_subkey
// Extracts subkey from address using rtree level table
extern "C" __attribute__((naked))
u64 FUN_7103931af0(u64) {
    asm(
        "sub sp, sp, #0x30\n"
        "str x0, [sp, #0x28]\n"
        "orr w8, wzr, #0x1\n"
        "str w8, [sp, #0x24]\n"
        "orr w9, wzr, #0x40\n"
        "str w9, [sp, #0x20]\n"
        "ldr w9, [sp, #0x24]\n"
        "adrp x10, DAT_7104466100\n"
        "add x10, x10, :lo12:DAT_7104466100\n"
        "add x9, x10, x9, lsl #3\n"
        "ldr w9, [x9, #0x4]\n"
        "str w9, [sp, #0x1c]\n"
        "ldr w9, [sp, #0x20]\n"
        "ldr w11, [sp, #0x1c]\n"
        "subs w9, w9, w11\n"
        "str w9, [sp, #0x18]\n"
        "ldr w9, [sp, #0x24]\n"
        "lsl x9, x9, #0x3\n"
        "ldr w9, [x10, x9]\n"
        "str w9, [sp, #0x14]\n"
        "ldr w9, [sp, #0x14]\n"
        "lsl x8, x8, x9\n"
        "subs x8, x8, #0x1\n"
        "str x8, [sp, #0x8]\n"
        "ldr x8, [sp, #0x28]\n"
        "ldr w9, [sp, #0x18]\n"
        "lsr x8, x8, x9\n"
        "ldr x9, [sp, #0x8]\n"
        "and x0, x8, x9\n"
        "add sp, sp, #0x30\n"
        "ret\n"
    );
}

// 0x7103931bc0 (128 bytes)
// jemalloc 5.1.0: arena.c — arena_extent_cache_drain_and_decommit
// 10 assertion b+4 stubs, then 6 calls
extern "C" __attribute__((naked))
void FUN_7103931bc0(u64, u64) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "str x1, [sp]\n"
        "b 1f\n"
        "1: b 2f\n"
        "2: b 3f\n"
        "3: b 4f\n"
        "4: b 5f\n"
        "5: b 6f\n"
        "6: b 7f\n"
        "7: b 8f\n"
        "8: b 9f\n"
        "9: b 0f\n"
        "0:\n"
        "ldr x0, [sp, #0x8]\n"
        "bl FUN_7103931300\n"
        "ldr x1, [sp]\n"
        "bl FUN_7103931c40\n"
        "ldr x8, [sp]\n"
        "ldr x0, [x8, #0x7d80]\n"
        "bl FUN_710392f170\n"
        "mov x1, xzr\n"
        "bl FUN_710392c180\n"
        "ldr x0, [sp, #0x8]\n"
        "bl FUN_7103931300\n"
        "ldr x8, [sp]\n"
        "ldr x1, [x8, #0x7d80]\n"
        "bl FUN_7103945780\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// 0x7103931e80 (128 bytes)
// jemalloc 5.1.0: rtree.h — rtree_extent_addr_read
// Reads extent from rtree, computes address via madd
extern "C" __attribute__((naked))
u64 FUN_7103931e80(u64, u64) {
    asm(
        "sub sp, sp, #0x40\n"
        "stp x29, x30, [sp, #0x30]\n"
        "add x29, sp, #0x30\n"
        "stur x0, [x29, #-0x8]\n"
        "stur x1, [x29, #-0x10]\n"
        "ldur x0, [x29, #-0x8]\n"
        "bl FUN_7103932b40\n"
        "str x0, [sp, #0x10]\n"
        "b 1f\n"
        "1: b 2f\n"
        "2: b 3f\n"
        "3: b 4f\n"
        "4:\n"
        "ldr x0, [sp, #0x10]\n"
        "ldur x8, [x29, #-0x10]\n"
        "add x1, x8, #0x18\n"
        "bl FUN_7103932ba0\n"
        "str x0, [sp, #0x8]\n"
        "ldur x0, [x29, #-0x8]\n"
        "bl FUN_7103932870\n"
        "ldur x8, [x29, #-0x10]\n"
        "ldr x8, [x8]\n"
        "ldr x9, [sp, #0x8]\n"
        "madd x8, x8, x9, x0\n"
        "str x8, [sp, #0x18]\n"
        "ldur x0, [x29, #-0x8]\n"
        "bl FUN_7103932c80\n"
        "ldr x0, [sp, #0x18]\n"
        "ldp x29, x30, [sp, #0x30]\n"
        "add sp, sp, #0x40\n"
        "ret\n"
    );
}

// =========================================================================
// 144-byte functions
// =========================================================================

// 0x7103932ab0 (144 bytes)
// jemalloc 5.1.0: arena.c — arena_extent_alloc_wrapper
// Gets tsdn, initializes flags, calls extent_alloc
extern "C" __attribute__((naked))
u64 FUN_7103932ab0(u64, u64, u64, u64, u32) {
    asm(
        "sub sp, sp, #0x60\n"
        "stp x29, x30, [sp, #0x50]\n"
        "add x29, sp, #0x50\n"
        "stur x0, [x29, #-0x8]\n"
        "stur x1, [x29, #-0x10]\n"
        "stur x2, [x29, #-0x18]\n"
        "stur x3, [x29, #-0x20]\n"
        "stur w4, [x29, #-0x24]\n"
        "ldur x0, [x29, #-0x8]\n"
        "bl FUN_710392eec0\n"
        "mov w1, wzr\n"
        "bl FUN_710392ef20\n"
        "strb wzr, [sp, #0x1c]\n"
        "orr w8, wzr, #0x1\n"
        "strb w8, [sp, #0x18]\n"
        "ldur x0, [x29, #-0x8]\n"
        "ldur x1, [x29, #-0x10]\n"
        "ldur x2, [x29, #-0x18]\n"
        "ldur x8, [x29, #-0x20]\n"
        "ldr x4, [x8, #0x8]\n"
        "ldur w8, [x29, #-0x24]\n"
        "add x9, sp, #0x18\n"
        "str x9, [sp, #0x10]\n"
        "add x9, sp, #0x1c\n"
        "str x9, [sp, #0x8]\n"
        "str w8, [sp]\n"
        "mov x3, xzr\n"
        "mov x5, xzr\n"
        "orr w6, wzr, #0x10000\n"
        "orr w7, wzr, #0x1\n"
        "bl FUN_7103942660\n"
        "str x0, [sp, #0x20]\n"
        "ldr x0, [sp, #0x20]\n"
        "ldp x29, x30, [sp, #0x50]\n"
        "add sp, sp, #0x60\n"
        "ret\n"
    );
}

#endif // MATCHING_HACK_NX_CLANG
