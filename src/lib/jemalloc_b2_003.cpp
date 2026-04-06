// jemalloc 5.1.0 — small functions batch 3 (pool-b2)
// Unclaimed functions: mutex_pool ops, extent_arena_set, tree rekey, bool OR
// All compiled at -O0 in NX build; naked asm for byte-exact match.

#include "types.h"

#ifdef MATCHING_HACK_NX_CLANG

// External data
extern "C" {
__attribute__((visibility("hidden"))) extern u8 DAT_7106dca710[]; // extent_mutex_pool
}

// External functions
extern "C" {
void* FUN_710393f250(void*, void*);  // mutex_pool_lock (returns idx)
void  FUN_710393f290(void*, void*);  // mutex_pool_unlock
void  FUN_71039387c0(void*, void*);  // ph_remove
void  FUN_7103938830(void*, void*);  // ph_insert
void  FUN_710393e130(void*, void*, void*, void*); // ph_rekey/extent_heaps_insert
void  FUN_7103944d30(void*, void*, void*, void*); // extent_init
u32   FUN_710393ee90(void*);         // arena_ind_get
bool  FUN_7103957fe0(void);          // check function 1
bool  FUN_71039575c0(void);          // check function 2
}

// =========================================================================
// 0x7103940970 (96 bytes, -O0) — extent_deregister (mutex_pool relock pattern)
// jemalloc 5.1.0: unlock old, lock new, remove from pairing heap
// Uses global DAT_7106dca710 (extent_mutex_pool)
// =========================================================================
extern "C" __attribute__((naked))
void FUN_7103940970(void*, void*) {
    asm(
        "sub sp, sp, #0x30\n"
        "stp x29, x30, [sp, #0x20]\n"
        "add x29, sp, #0x20\n"
        "stur x0, [x29, #-0x8]\n"
        "adrp x8, DAT_7106dca710\n"
        "add x8, x8, :lo12:DAT_7106dca710\n"
        "str x8, [sp, #0x10]\n"
        "str x1, [sp, #0x8]\n"
        "ldur x0, [x29, #-0x8]\n"
        "ldr x1, [sp, #0x10]\n"
        "bl FUN_710393f290\n"
        "ldr x0, [sp, #0x10]\n"
        "ldr x1, [sp, #0x8]\n"
        "bl FUN_710393f250\n"
        "str x0, [sp]\n"
        "ldur x0, [x29, #-0x8]\n"
        "ldr x1, [sp]\n"
        "bl FUN_71039387c0\n"
        "ldp x29, x30, [sp, #0x20]\n"
        "add sp, sp, #0x30\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103940ee0 (96 bytes, -O0) — extent rekey: ph_remove + reinsert
// jemalloc 5.1.0: extent_heaps op (remove, modify, insert)
// =========================================================================
extern "C" __attribute__((naked))
void FUN_7103940ee0(void*, void*, void*, void*) {
    asm(
        "sub sp, sp, #0x30\n"
        "stp x29, x30, [sp, #0x20]\n"
        "add x29, sp, #0x20\n"
        "stur x0, [x29, #-0x8]\n"
        "str x1, [sp, #0x10]\n"
        "str x2, [sp, #0x8]\n"
        "str x3, [sp]\n"
        "ldur x0, [x29, #-0x8]\n"
        "ldr x1, [sp, #0x8]\n"
        "bl FUN_71039387c0\n"
        "ldur x0, [x29, #-0x8]\n"
        "ldr x1, [sp, #0x10]\n"
        "ldr x2, [sp, #0x8]\n"
        "ldr x3, [sp]\n"
        "bl FUN_710393e130\n"
        "ldur x0, [x29, #-0x8]\n"
        "ldr x1, [sp, #0x8]\n"
        "bl FUN_7103938830\n"
        "ldp x29, x30, [sp, #0x20]\n"
        "add sp, sp, #0x30\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103941b80 (96 bytes, -O0) — extent_arena_set (proper, with arena ptr)
// jemalloc 5.1.0: extent_inlines.h — if arena==NULL ind=0xFFF else arena_ind_get
// Then clears bottom 12 bits of e_bits and ORs in new arena_ind.
// =========================================================================
extern "C" __attribute__((naked))
void FUN_7103941b80(u64*, void*) {
    asm(
        "sub sp, sp, #0x30\n"
        "stp x29, x30, [sp, #0x20]\n"
        "add x29, sp, #0x20\n"
        "stur x0, [x29, #-0x8]\n"
        "str x1, [sp, #0x10]\n"
        "ldr x8, [sp, #0x10]\n"
        "cbz x8, 1f\n"                  // if (arena == NULL) goto 0xFFF
        "b 2f\n"
        "2: ldr x0, [sp, #0x10]\n"
        "bl FUN_710393ee90\n"           // arena_ind_get(arena)
        "b 3f\n"
        "1: orr w0, wzr, #0xfff\n"     // ind = 0xFFF (MALLOCX_ARENA_LIMIT-1)
        "b 3f\n"
        "3: str w0, [sp, #0xc]\n"
        "ldur x8, [x29, #-0x8]\n"
        "ldr x9, [x8]\n"                // load e_bits
        "and x9, x9, #-0x1000\n"        // clear bottom 12 bits
        "ldr w10, [sp, #0xc]\n"
        "orr x9, x9, x10\n"            // set arena ind
        "str x9, [x8]\n"                // store e_bits
        "ldp x29, x30, [sp, #0x20]\n"
        "add sp, sp, #0x30\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103943ba0 (96 bytes, -O0) — boolean OR of two check functions
// jemalloc 5.1.0: likely opt_abort || opt_abort_conf check
// =========================================================================
extern "C" __attribute__((naked))
bool FUN_7103943ba0(void) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "bl FUN_7103957fe0\n"
        "tbz w0, #0x0, 1f\n"
        "b 2f\n"
        "2: orr w8, wzr, #0x1\n"       // result = true
        "sturb w8, [x29, #-0x1]\n"
        "b 3f\n"
        "1: bl FUN_71039575c0\n"
        "tbz w0, #0x0, 4f\n"
        "b 5f\n"
        "5: orr w8, wzr, #0x1\n"       // result = true
        "sturb w8, [x29, #-0x1]\n"
        "b 3f\n"
        "4: sturb wzr, [x29, #-0x1]\n" // result = false
        "b 3f\n"
        "3: ldurb w0, [x29, #-0x1]\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 0x71039454b0 (96 bytes, -O0) — increment counter + extent_init
// jemalloc 5.1.0: extent_avail_remove or similar: (*count)++, then init extent
// =========================================================================
extern "C" __attribute__((naked))
void FUN_71039454b0(u64*, void*, void*, void*) {
    asm(
        "sub sp, sp, #0x40\n"
        "stp x29, x30, [sp, #0x30]\n"
        "add x29, sp, #0x30\n"
        "stur x0, [x29, #-0x8]\n"
        "stur x1, [x29, #-0x10]\n"
        "str x2, [sp, #0x18]\n"
        "str x3, [sp, #0x10]\n"
        "ldur x8, [x29, #-0x8]\n"
        "ldr x8, [x8]\n"               // old = *count
        "str x8, [sp, #0x8]\n"
        "ldur x8, [x29, #-0x8]\n"
        "ldr x9, [x8]\n"
        "add x9, x9, #0x1\n"           // (*count)++
        "str x9, [x8]\n"
        "ldur x0, [x29, #-0x10]\n"
        "ldr x1, [sp, #0x18]\n"
        "ldr x2, [sp, #0x10]\n"
        "ldr x3, [sp, #0x8]\n"
        "bl FUN_7103944d30\n"           // extent_init(extent, addr, size, old_count)
        "ldp x29, x30, [sp, #0x30]\n"
        "add sp, sp, #0x40\n"
        "ret\n"
    );
}

#endif // MATCHING_HACK_NX_CLANG
