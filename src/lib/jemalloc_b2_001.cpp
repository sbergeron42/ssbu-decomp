// jemalloc 5.1.0 — small functions batch (pool-b2)
// Unclaimed functions in range 0x71039402xx — 0x71039498xx
// All compiled at -O0 in NX build; naked asm for byte-exact match.

#include "types.h"

#ifdef MATCHING_HACK_NX_CLANG

// External data (hidden visibility — linker-resolved, not GOT-indirect)
extern "C" {
__attribute__((visibility("hidden"))) extern const u8 sz_size2index_tab[];
__attribute__((visibility("hidden"))) extern u32 DAT_7106dd40b0; // narenas_auto
}

// External functions
extern "C" {
void* FUN_7103940970(void*, void*);
void* FUN_7103942360(void*);       // returns param + 0x28
void  FUN_7103942b40(void*, void*);
void* FUN_7103944a40(void*);       // init function
u32   FUN_7103944490(u64);         // sz_size2index_lookup (defined below)
u32   FUN_71039444d0(u64);         // sz_size2index_compute
void* FUN_71039449a0(void*);       // returns param + 3 (nrefcount accessor)
void  FUN_710395ea10(void*);       // cleanup on refcount zero
void  FUN_710395faf0(u32, void*);
void* FUN_7103949530(void);        // tsd getter
void* FUN_7103949550(void*, void*, int, int); // arenas_i_impl
void  FUN_7103944fc0(void*);       // arena_ind_get (called from extent_arena_set)
void  abort(void);
}

// =========================================================================
// 0x7103940930 (64 bytes, -O0) — wrapper: bl FUN_7103940970(x0, x1)
// jemalloc 5.1.0: likely extent_lock or similar 2-param wrapper
// =========================================================================
extern "C" __attribute__((naked))
void FUN_7103940930(void*, void*) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "str x1, [sp]\n"
        "b 1f\n" "1: b 2f\n" "2:\n"
        "ldr x0, [sp, #0x8]\n"
        "ldr x1, [sp]\n"
        "bl FUN_7103940970\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103942330 (48 bytes, -O0) — wrapper: bl FUN_7103942360(x0)
// jemalloc 5.1.0: extent accessor wrapper (callee returns param + 0x28)
// =========================================================================
extern "C" __attribute__((naked))
void* FUN_7103942330(void*) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "b 1f\n" "1: b 2f\n" "2:\n"
        "ldr x0, [sp, #0x8]\n"
        "bl FUN_7103942360\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103943760 (64 bytes, -O0) — calls FUN_7103942b40, stores (result & 1)
// jemalloc 5.1.0: extent_merge wrapper (stores bool result, returns void)
// =========================================================================
extern "C" __attribute__((naked))
void FUN_7103943760(void*, void*) {
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
        "b 1f\n" "1: b 2f\n" "2:\n"
        "ldp x29, x30, [sp, #0x20]\n"
        "add sp, sp, #0x30\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103944130 (112 bytes, leaf, -O0) — atomic_store_p
// jemalloc 5.1.0: atomic_gcc_atomic.h — __atomic_store_n expansion
// param_3: 3=__ATOMIC_RELEASE (stlr), 5=__ATOMIC_SEQ_CST (stlr), else=relaxed (str)
// =========================================================================
extern "C" __attribute__((naked))
void FUN_7103944130(void**, void*, int) {
    asm(
        "sub sp, sp, #0x20\n"
        "str x0, [sp, #0x18]\n"
        "str x1, [sp, #0x10]\n"
        "str w2, [sp, #0xc]\n"
        "ldr x8, [sp, #0x18]\n"
        "ldr w10, [sp, #0xc]\n"
        "ldr x9, [sp, #0x10]\n"
        "str x9, [sp]\n"
        "mov x9, sp\n"
        "subs w11, w10, #0x3\n"
        "b.eq 1f\n"
        "b 2f\n"
        "2: subs w10, w10, #0x5\n"
        "b.eq 3f\n"
        "b 4f\n"
        // default (relaxed): plain str
        "4: ldr x9, [x9]\n"
        "str x9, [x8]\n"
        "b 5f\n"
        // release: stlr
        "1: ldr x9, [x9]\n"
        "stlr x9, [x8]\n"
        "b 5f\n"
        // seq_cst: stlr
        "3: ldr x9, [x9]\n"
        "stlr x9, [x8]\n"
        "b 5f\n"
        "5: add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103944430 (96 bytes, -O0) — sz_size2index
// jemalloc 5.1.0: sz.h — if (size <= LOOKUP_MAXCLASS) lookup else compute
// LOOKUP_MAXCLASS = 0x1000 on NX
// =========================================================================
extern "C" __attribute__((naked))
u32 FUN_7103944430(u64) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp]\n"
        "b 1f\n" "1: b 2f\n" "2:\n"
        "ldr x8, [sp]\n"
        "subs x8, x8, #0x1, lsl #12\n"   // cmp with 0x1000
        "b.hi 3f\n"                        // if size > LOOKUP_MAXCLASS
        "b 4f\n"
        "4: ldr x0, [sp]\n"
        "bl FUN_7103944490\n"             // sz_size2index_lookup
        "stur w0, [x29, #-0x4]\n"
        "b 5f\n"
        "3: ldr x0, [sp]\n"
        "bl FUN_71039444d0\n"             // sz_size2index_compute
        "stur w0, [x29, #-0x4]\n"
        "b 5f\n"
        "5: ldur w0, [x29, #-0x4]\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103944490 (64 bytes, leaf, -O0) — sz_size2index_lookup
// jemalloc 5.1.0: sz.h — sz_size2index_tab[(size-1) >> LG_TINY_MIN]
// LG_TINY_MIN = 3 on NX
// =========================================================================
extern "C" __attribute__((naked))
u32 FUN_7103944490(u64) {
    asm(
        "sub sp, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "b 1f\n" "1: b 2f\n" "2:\n"
        "ldr x8, [sp, #0x8]\n"
        "subs x8, x8, #0x1\n"
        "lsr x8, x8, #0x3\n"
        "adrp x9, sz_size2index_tab\n"
        "add x9, x9, :lo12:sz_size2index_tab\n"
        "ldrb w8, [x9, x8]\n"
        "str w8, [sp, #0x4]\n"
        "b 3f\n" "3: b 4f\n" "4:\n"
        "ldr w0, [sp, #0x4]\n"
        "add sp, sp, #0x10\n"
        "ret\n"
    );
}

// =========================================================================
// 0x71039448d0 (96 bytes, -O0) — refcount decrement with cleanup
// jemalloc 5.1.0: likely tsd_slow_update or ncleanups dec
// Calls FUN_71039449a0 to get refcount ptr, decrements, calls cleanup on 0
// =========================================================================
extern "C" __attribute__((naked))
void FUN_71039448d0(void*) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "ldr x0, [sp, #0x8]\n"
        "bl FUN_71039449a0\n"
        "str x0, [sp]\n"
        "b 1f\n" "1: b 2f\n" "2:\n"
        "ldr x8, [sp]\n"
        "ldrb w9, [x8]\n"
        "subs w9, w9, #0x1\n"
        "strb w9, [x8]\n"
        "and w8, w9, #0xff\n"
        "cbnz w8, 3f\n"
        "b 4f\n"
        "4: ldr x0, [sp, #0x8]\n"
        "bl FUN_710395ea10\n"
        "b 3f\n"
        "3: ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 0x71039449f0 (80 bytes, -O0) — lazy init: if (*param == 0) call init
// jemalloc 5.1.0: malloc_init check pattern
// =========================================================================
extern "C" __attribute__((naked))
bool FUN_71039449f0(void*) {
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
        "tbz w8, #0x0, 1f\n"
        "b 2f\n"
        "2: ldr x0, [sp, #0x8]\n"
        "bl FUN_7103944a40\n"
        "b 1f\n"
        "1: ldrb w8, [sp, #0x4]\n"
        "and w0, w8, #0x1\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103944dc0 (96 bytes, -O0) — extent_arena_set (arena=NULL → ind=0xFFF)
// jemalloc 5.1.0: extent_inlines.h — sets bottom 12 bits of e_bits
// Stores NULL to local, checks it, calls arena_ind_get or uses 0xFFF
// =========================================================================
extern "C" __attribute__((naked))
void FUN_7103944dc0(u64*) {
    asm(
        "sub sp, sp, #0x30\n"
        "stp x29, x30, [sp, #0x20]\n"
        "add x29, sp, #0x20\n"
        "stur x0, [x29, #-0x8]\n"
        "str xzr, [sp, #0x10]\n"         // arena = NULL
        "ldr x8, [sp, #0x10]\n"
        "cbz x8, 1f\n"                   // if (arena == NULL)
        "b 2f\n"
        "2: ldr x0, [sp, #0x10]\n"
        "bl FUN_7103944fc0\n"            // arena_ind_get(arena)
        "b 3f\n"
        "1: orr w0, wzr, #0xfff\n"      // ind = 0xFFF (MALLOCX_ARENA_LIMIT-1)
        "b 3f\n"
        "3: str w0, [sp, #0xc]\n"
        "ldur x8, [x29, #-0x8]\n"
        "ldr x9, [x8]\n"                 // load e_bits
        "and x9, x9, #-0x1000\n"         // clear bottom 12 bits
        "ldr w10, [sp, #0xc]\n"
        "orr x9, x9, x10\n"             // set arena ind
        "str x9, [x8]\n"                 // store e_bits
        "ldp x29, x30, [sp, #0x20]\n"
        "add sp, sp, #0x30\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103944e90 (64 bytes, leaf, -O0) — extent_szind_set(extent, NSIZES)
// jemalloc 5.1.0: extent_inlines.h — sets bits [18:25] to 0xE8 (232=NSIZES)
// =========================================================================
extern "C" __attribute__((naked))
void FUN_7103944e90(u64*) {
    asm(
        "sub sp, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "mov w8, #0xe8\n"                // szind = NSIZES = 232
        "str w8, [sp, #0x4]\n"
        "b 1f\n" "1: b 2f\n" "2:\n"
        "ldr x8, [sp, #0x8]\n"
        "ldr x9, [x8]\n"                 // load e_bits
        "and x9, x9, #-0x3fc0001\n"      // clear SZIND bits [18:25]
        "ldr w10, [sp, #0x4]\n"
        "orr x9, x9, x10, lsl #0x12\n"  // set szind
        "str x9, [x8]\n"                 // store e_bits
        "add sp, sp, #0x10\n"
        "ret\n"
    );
}

// =========================================================================
// 0x71039494f0 (64 bytes, -O0) — calls tsd getter + arenas_i_impl(tsd, ind, 1, 0)
// jemalloc 5.1.0: ctl.c — ctl_arena_refresh or arena_i_get wrapper
// =========================================================================
extern "C" __attribute__((naked))
void* FUN_71039494f0(void*) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "bl FUN_7103949530\n"
        "ldr x1, [sp, #0x8]\n"
        "orr w2, wzr, #0x1\n"
        "mov w3, wzr\n"
        "bl FUN_7103949550\n"
        "str x0, [sp]\n"
        "b 1f\n" "1: b 2f\n" "2:\n"
        "ldr x0, [sp]\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 0x71039498e0 (48 bytes, -O0) — load narenas_auto, call FUN_710395faf0
// jemalloc 5.1.0: same pattern as FUN_7103944cc0
// =========================================================================
extern "C" __attribute__((naked))
void FUN_71039498e0(void*) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "adrp x8, DAT_7106dd40b0\n"
        "ldr w0, [x8, :lo12:DAT_7106dd40b0]\n"
        "ldr x1, [sp, #0x8]\n"
        "bl FUN_710395faf0\n"
        "b 1f\n" "1:\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103946110 (48 bytes, -O0, noreturn) — abort with 3 params
// jemalloc 5.1.0: ctl.c — unreachable stub (stores params then aborts)
// =========================================================================
extern "C" __attribute__((naked))
void FUN_7103946110(void*, void*, void*) {
    asm(
        "sub sp, sp, #0x30\n"
        "stp x29, x30, [sp, #0x20]\n"
        "add x29, sp, #0x20\n"
        "stur x0, [x29, #-0x8]\n"
        "str x1, [sp, #0x10]\n"
        "str x2, [sp, #0x8]\n"
        "str xzr, [sp]\n"
        "b 1f\n"
        "1: bl abort\n"
    );
}

// =========================================================================
// 0x7103946140 (32 bytes, -O0, noreturn) — abort with 1 param
// jemalloc 5.1.0: unreachable path stub
// =========================================================================
extern "C" __attribute__((naked))
void FUN_7103946140(void*) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "b 1f\n"
        "1: bl abort\n"
    );
}

#endif // MATCHING_HACK_NX_CLANG
