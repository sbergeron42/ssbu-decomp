// jemalloc 5.1.0 — small functions batch 4 (pool-b2)
// Unclaimed functions: extent_init sequence, conditional ops, slab indexing
// All compiled at -O0 in NX build; naked asm for byte-exact match.

#include "types.h"

#ifdef MATCHING_HACK_NX_CLANG

// External data
extern "C" {
__attribute__((visibility("hidden"))) extern u8 DAT_7106dd3f1c; // opt flag (opt_retain or similar)
}

// External functions
extern "C" {
void  FUN_7103944dc0(void*);         // extent_arena_set (NULL → 0xFFF)
void  FUN_7103944e20(void*, void*);  // extent_addr_set
void  FUN_7103944e40(void*, void*);  // extent_size_set
void  FUN_7103944e60(void*);         // extent field setter
void  FUN_7103944e90(void*);         // extent_szind_set (NSIZES)
void  FUN_7103944ed0(void*, void*);  // extent_sn_set
void  FUN_7103944f00(void*);         // extent field setter
void  FUN_7103944f30(void*);         // extent field setter
void  FUN_7103944f60(void*);         // extent field setter
void  FUN_7103944f90(void*);         // extent field setter
bool  FUN_71039447f0(void*);         // extent_slab_get or similar check
void* FUN_7103944830(void*);         // extent accessor
void* FUN_7103945590(void*);         // wrapper (returns param + 0x1800)
void* FUN_7103946810(void*);         // returns ptr if bit 0 set, else NULL
bool  FUN_7103947040(void*);         // extent check
void* FUN_7103947060(void*);         // extent accessor
void* FUN_7103947080(void*);         // wrapper (returns param + 0x1800)
void  FUN_7103957c40(void*, void*);  // conditional init function
}

// =========================================================================
// 0x7103944d30 (128 bytes, -O0) — extent_init (decomposed at -O0)
// jemalloc 5.1.0: extent_inlines.h — calls 10 individual field setters
// extent_init(extent, addr, size, sn) — remaining fields set to constants
// =========================================================================
extern "C" __attribute__((naked))
void FUN_7103944d30(void*, void*, void*, void*) {
    asm(
        "sub sp, sp, #0x30\n"
        "stp x29, x30, [sp, #0x20]\n"
        "add x29, sp, #0x20\n"
        "stur x0, [x29, #-0x8]\n"
        "str x1, [sp, #0x10]\n"
        "str x2, [sp, #0x8]\n"
        "str x3, [sp]\n"
        // extent_arena_set(extent, NULL) → arena_ind = 0xFFF
        "ldur x0, [x29, #-0x8]\n"
        "bl FUN_7103944dc0\n"
        // extent_addr_set(extent, addr)
        "ldur x0, [x29, #-0x8]\n"
        "ldr x1, [sp, #0x10]\n"
        "bl FUN_7103944e20\n"
        // extent_size_set(extent, size)
        "ldur x0, [x29, #-0x8]\n"
        "ldr x1, [sp, #0x8]\n"
        "bl FUN_7103944e40\n"
        // extent field (state? zeroed?)
        "ldur x0, [x29, #-0x8]\n"
        "bl FUN_7103944e60\n"
        // extent_szind_set(extent, NSIZES)
        "ldur x0, [x29, #-0x8]\n"
        "bl FUN_7103944e90\n"
        // extent_sn_set(extent, sn)
        "ldur x0, [x29, #-0x8]\n"
        "ldr x1, [sp]\n"
        "bl FUN_7103944ed0\n"
        // remaining constant setters
        "ldur x0, [x29, #-0x8]\n"
        "bl FUN_7103944f00\n"
        "ldur x0, [x29, #-0x8]\n"
        "bl FUN_7103944f30\n"
        "ldur x0, [x29, #-0x8]\n"
        "bl FUN_7103944f60\n"
        "ldur x0, [x29, #-0x8]\n"
        "bl FUN_7103944f90\n"
        "ldp x29, x30, [sp, #0x20]\n"
        "add sp, sp, #0x30\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103945510 (96 bytes, -O0) — extent_bsize_get (checks slab, gets base)
// jemalloc 5.1.0: if slab → return 0; else → accessor(param) + 0x1800
// =========================================================================
extern "C" __attribute__((naked))
void* FUN_7103945510(void*) {
    asm(
        "sub sp, sp, #0x30\n"
        "stp x29, x30, [sp, #0x20]\n"
        "add x29, sp, #0x20\n"
        "str x0, [sp, #0x10]\n"
        "ldr x0, [sp, #0x10]\n"
        "bl FUN_71039447f0\n"
        "tbz w0, #0x0, 1f\n"
        "b 2f\n"
        "2: stur xzr, [x29, #-0x8]\n"
        "b 3f\n"
        "1: ldr x0, [sp, #0x10]\n"
        "bl FUN_7103944830\n"
        "str x0, [sp, #0x8]\n"
        "ldr x0, [sp, #0x8]\n"
        "bl FUN_7103945590\n"
        "stur x0, [x29, #-0x8]\n"
        "b 3f\n"
        "3: ldur x0, [x29, #-0x8]\n"
        "ldp x29, x30, [sp, #0x20]\n"
        "add sp, sp, #0x30\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103945dc0 (80 bytes, -O0) — conditional call based on global flag
// jemalloc 5.1.0: witness_assert pattern (check opt flag, call if needed)
// =========================================================================
extern "C" __attribute__((naked))
u8 FUN_7103945dc0(void*, void*) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "str x1, [sp]\n"
        "adrp x8, DAT_7106dd3f1c\n"
        "ldrb w8, [x8, :lo12:DAT_7106dd3f1c]\n"
        "tbnz w8, #0x0, 1f\n"
        "b 2f\n"
        "2: ldr x0, [sp, #0x8]\n"
        "ldr x1, [sp]\n"
        "bl FUN_7103957c40\n"
        "b 1f\n"
        "1: adrp x8, DAT_7106dd3f1c\n"
        "ldrb w0, [x8, :lo12:DAT_7106dd3f1c]\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103946840 (96 bytes, -O0) — slab element indexing
// jemalloc 5.1.0: checks slab ptr via bit 0, then computes ptr + idx * 0x28
// =========================================================================
extern "C" __attribute__((naked))
void* FUN_7103946840(void*, u64) {
    asm(
        "sub sp, sp, #0x30\n"
        "stp x29, x30, [sp, #0x20]\n"
        "add x29, sp, #0x20\n"
        "stur x0, [x29, #-0x8]\n"
        "str x1, [sp, #0x10]\n"
        "ldur x8, [x29, #-0x8]\n"
        "ldr x0, [x8, #0x18]\n"
        "bl FUN_7103946810\n"
        "str x0, [sp, #0x8]\n"
        "ldr x8, [sp, #0x8]\n"
        "cbz x8, 1f\n"
        "b 2f\n"
        "2: ldr x8, [sp, #0x8]\n"
        "ldr x9, [sp, #0x10]\n"
        "mov w10, #0x28\n"
        "madd x0, x9, x10, x8\n"       // ptr + idx * 40
        "b 3f\n"
        "1: mov x0, xzr\n"
        "b 3f\n"
        "3: ldp x29, x30, [sp, #0x20]\n"
        "add sp, sp, #0x30\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103946fc0 (96 bytes, -O0) — same pattern as FUN_7103945510
// jemalloc 5.1.0: check → accessor → wrapper (+0x1800)
// =========================================================================
extern "C" __attribute__((naked))
void* FUN_7103946fc0(void*) {
    asm(
        "sub sp, sp, #0x30\n"
        "stp x29, x30, [sp, #0x20]\n"
        "add x29, sp, #0x20\n"
        "str x0, [sp, #0x10]\n"
        "ldr x0, [sp, #0x10]\n"
        "bl FUN_7103947040\n"
        "tbz w0, #0x0, 1f\n"
        "b 2f\n"
        "2: stur xzr, [x29, #-0x8]\n"
        "b 3f\n"
        "1: ldr x0, [sp, #0x10]\n"
        "bl FUN_7103947060\n"
        "str x0, [sp, #0x8]\n"
        "ldr x0, [sp, #0x8]\n"
        "bl FUN_7103947080\n"
        "stur x0, [x29, #-0x8]\n"
        "b 3f\n"
        "3: ldur x0, [x29, #-0x8]\n"
        "ldp x29, x30, [sp, #0x20]\n"
        "add sp, sp, #0x30\n"
        "ret\n"
    );
}

#endif // MATCHING_HACK_NX_CLANG
