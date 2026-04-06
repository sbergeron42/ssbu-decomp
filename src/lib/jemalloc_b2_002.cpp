// jemalloc 5.1.0 — small functions batch 2 (pool-b2)
// Unclaimed functions: atomic loads, div_init, queue ops, wrappers
// All compiled at -O0 in NX build; naked asm for byte-exact match.

#include "types.h"

#ifdef MATCHING_HACK_NX_CLANG

// External data (hidden visibility — linker-resolved)
extern "C" {
__attribute__((visibility("hidden"))) extern u8 DAT_7106dca710[]; // extent_mutex_pool
__attribute__((visibility("hidden"))) extern u8 DAT_7106d4a678[]; // global rtree or similar
}

// External functions
extern "C" {
bool  FUN_7103940490(void);      // malloc_initialized check
void  FUN_710393fb50(int);       // malloc_init_hard_a0 or similar
void* FUN_710393fe20(void);      // returns allocated ptr
void* FUN_710393f250(void*, void*);  // mutex_pool helper
void  FUN_7103938830(void*, void*);  // ph_insert or similar
void  FUN_710393f290(void*, void*);  // mutex_pool_unlock or similar
void* FUN_71039409d0(void*, void*, void*, int); // rtree_leaf_elm_lookup_hard or similar
void  FUN_7103940a20(void*);     // rtree post-lookup
}

// =========================================================================
// 0x7103940290 (80 bytes, -O0) — lazy init: check initialized, allocate
// jemalloc 5.1.0: base_alloc or extent_alloc init path
// =========================================================================
extern "C" __attribute__((naked))
void* FUN_7103940290(void) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "bl FUN_7103940490\n"
        "tbnz w0, #0x0, 1f\n"
        "b 2f\n"
        "2: str xzr, [sp, #0x8]\n"
        "b 3f\n"
        "1: mov w0, wzr\n"
        "bl FUN_710393fb50\n"
        "bl FUN_710393fe20\n"
        "str x0, [sp, #0x8]\n"
        "b 3f\n"
        "3: ldr x0, [sp, #0x8]\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103940390 (112 bytes, leaf, -O0) — atomic_load_u (mo=RELAXED)
// jemalloc 5.1.0: atomic_gcc_atomic.h — __atomic_load_n with mo=0
// Switch: mo<3 → ldar, mo==5 → ldar, else → ldr (relaxed path taken)
// =========================================================================
extern "C" __attribute__((naked))
u32 FUN_7103940390(void*) {
    asm(
        "sub sp, sp, #0x20\n"
        "str x0, [sp, #0x18]\n"
        "str wzr, [sp, #0x14]\n"        // mo = 0 (RELAXED)
        "ldr x8, [sp, #0x18]\n"
        "str x8, [sp, #0x8]\n"
        "ldr x8, [sp, #0x8]\n"
        "ldr w9, [sp, #0x14]\n"
        "subs w10, w9, #0x1\n"
        "subs w10, w10, #0x2\n"
        "b.cc 1f\n"                      // if mo < 3 → acquire path
        "b 2f\n"
        "2: subs w9, w9, #0x5\n"
        "b.eq 3f\n"                      // if mo == 5 → seq_cst path
        "b 4f\n"
        // default (relaxed): plain ldr w
        "4: ldr w8, [x8]\n"
        "str w8, [sp, #0x4]\n"
        "b 5f\n"
        // acquire/consume: ldar w
        "1: ldar w8, [x8]\n"
        "str w8, [sp, #0x4]\n"
        "b 5f\n"
        // seq_cst: ldar w
        "3: ldar w8, [x8]\n"
        "str w8, [sp, #0x4]\n"
        "b 5f\n"
        "5: ldr w0, [sp, #0x4]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 0x71039407a0 (96 bytes, -O0) — extent_mutex_pool insert
// jemalloc 5.1.0: calls mutex_pool helper + ph_insert + mutex_pool_unlock
// Uses global DAT_7106dca710 (extent_mutex_pool)
// =========================================================================
extern "C" __attribute__((naked))
void FUN_71039407a0(void*, void*) {
    asm(
        "sub sp, sp, #0x30\n"
        "stp x29, x30, [sp, #0x20]\n"
        "add x29, sp, #0x20\n"
        "stur x0, [x29, #-0x8]\n"
        "adrp x8, DAT_7106dca710\n"
        "add x8, x8, :lo12:DAT_7106dca710\n"
        "str x8, [sp, #0x10]\n"
        "str x1, [sp, #0x8]\n"
        "ldr x0, [sp, #0x10]\n"
        "ldr x1, [sp, #0x8]\n"
        "bl FUN_710393f250\n"
        "str x0, [sp]\n"
        "ldur x0, [x29, #-0x8]\n"
        "ldr x1, [sp]\n"
        "bl FUN_7103938830\n"
        "ldur x0, [x29, #-0x8]\n"
        "ldr x1, [sp, #0x10]\n"
        "bl FUN_710393f290\n"
        "ldp x29, x30, [sp, #0x20]\n"
        "add sp, sp, #0x30\n"
        "ret\n"
    );
}

// =========================================================================
// 0x71039408d0 (96 bytes, -O0) — rtree lookup + post-process wrapper
// jemalloc 5.1.0: calls FUN_71039409d0 with global + param, then FUN_7103940a20
// Uses global DAT_7106d4a678
// =========================================================================
extern "C" __attribute__((naked))
void FUN_71039408d0(void*, void*) {
    asm(
        "sub sp, sp, #0x40\n"
        "stp x29, x30, [sp, #0x30]\n"
        "add x29, sp, #0x30\n"
        "stur x0, [x29, #-0x8]\n"
        "adrp x8, DAT_7106d4a678\n"
        "add x8, x8, :lo12:DAT_7106d4a678\n"
        "stur x8, [x29, #-0x10]\n"
        "str x1, [sp, #0x18]\n"
        "orr w8, wzr, #0x1\n"           // true (init_missing = true)
        "strb w8, [sp, #0x14]\n"
        "ldur x0, [x29, #-0x8]\n"
        "ldur x1, [x29, #-0x10]\n"
        "ldr x2, [sp, #0x18]\n"
        "ldrb w8, [sp, #0x14]\n"
        "and w3, w8, #0x1\n"
        "bl FUN_71039409d0\n"
        "str x0, [sp, #0x8]\n"
        "ldr x0, [sp, #0x8]\n"
        "bl FUN_7103940a20\n"
        "ldp x29, x30, [sp, #0x30]\n"
        "add sp, sp, #0x40\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103945840 (112 bytes, leaf, -O0) — atomic_load_p (mo=ACQUIRE)
// jemalloc 5.1.0: atomic_gcc_atomic.h — __atomic_load_n with mo=2
// =========================================================================
extern "C" __attribute__((naked))
void* FUN_7103945840(void**) {
    asm(
        "sub sp, sp, #0x20\n"
        "str x0, [sp, #0x18]\n"
        "orr w8, wzr, #0x2\n"           // mo = 2 (ACQUIRE)
        "str w8, [sp, #0x14]\n"
        "ldr x8, [sp, #0x18]\n"
        "str x8, [sp, #0x8]\n"
        "ldr x9, [sp, #0x8]\n"
        "ldr w10, [sp, #0x14]\n"
        "mov x8, sp\n"
        "subs w11, w10, #0x1\n"
        "subs w11, w11, #0x2\n"
        "b.cc 1f\n"                      // if mo < 3 → acquire path
        "b 2f\n"
        "2: subs w10, w10, #0x5\n"
        "b.eq 3f\n"                      // if mo == 5 → seq_cst
        "b 4f\n"
        // default (relaxed): plain ldr
        "4: ldr x9, [x9]\n"
        "str x9, [x8]\n"
        "b 5f\n"
        // acquire/consume: ldar
        "1: ldar x9, [x9]\n"
        "str x9, [x8]\n"
        "b 5f\n"
        // seq_cst: ldar
        "3: ldar x9, [x9]\n"
        "str x9, [x8]\n"
        "b 5f\n"
        "5: ldr x0, [x8]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 0x71039460a0 (112 bytes, leaf, -O0) — div_init
// jemalloc 5.1.0: div.c — computes ceil(2^32 / divisor)
// =========================================================================
extern "C" __attribute__((naked))
void FUN_71039460a0(u32*, u64) {
    asm(
        "sub sp, sp, #0x20\n"
        "str x0, [sp, #0x18]\n"
        "str x1, [sp, #0x10]\n"
        "b 1f\n" "1: b 2f\n" "2: b 3f\n" "3: b 4f\n" "4:\n"
        "orr x8, xzr, #0x100000000\n"   // 2^32
        "str x8, [sp, #0x8]\n"
        "ldr x8, [sp, #0x8]\n"
        "ldr x9, [sp, #0x10]\n"
        "udiv x8, x8, x9\n"             // 2^32 / d (truncated)
        "str w8, [sp, #0x4]\n"
        "ldr x8, [sp, #0x8]\n"
        "ldr x9, [sp, #0x10]\n"
        "udiv x10, x8, x9\n"
        "msub x8, x10, x9, x8\n"        // 2^32 % d
        "cbz x8, 5f\n"                  // if remainder == 0, skip increment
        "b 6f\n"
        "6: ldr w8, [sp, #0x4]\n"
        "add w8, w8, #0x1\n"            // round up
        "str w8, [sp, #0x4]\n"
        "b 5f\n"
        "5: ldr w8, [sp, #0x4]\n"
        "ldr x9, [sp, #0x18]\n"
        "str w8, [x9]\n"                 // *out = result
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

#endif // MATCHING_HACK_NX_CLANG
