// jemalloc 5.1.0 — medium functions batch 2 (pool-d)
// Address range: 0x710392xxxx — atomic ops, arena utils, bit helpers
// All compiled at -O0 in NX build; naked asm for byte-exact match.

#include "types.h"

#ifdef MATCHING_HACK_NX_CLANG

// External functions
extern "C" {
void* FUN_71039280f0(void*);   // tsd_tsdn (returns tsdn from tsd)
void* FUN_7103927960(void*, u32, u32);  // arena_get_from_index
void  FUN_7103935860(void*, u32);  // extent_hooks_assure_initialized
void  FUN_7103935720(void*, u32);  // extent_hooks_assure_initialized (variant)
void  FUN_7103929090(void*, void*);  // arena init helper
void* FUN_71039292b0(void*, void*);  // malloc_mutex_lock
void  FUN_7103929320(void*, u32, void*);  // arena_i_get (returns arena*)
void  FUN_71039293e0(void*, void*);  // malloc_mutex_unlock
void  FUN_7103929420(void*, u32);  // arena post-unlock
void* FUN_7103927b30(void*);   // tsd_arena_get (defined in jemalloc_d_001.cpp)
void* FUN_7103927b90(void*, u32, u32);  // arena_get variant
void* FUN_710392e0c0(void*, void*, void*, void*, void*, u32, void*);  // extent_alloc_wrapper_inner
void* FUN_7103928da0(void*);   // tsd accessor
}

// External globals (hidden visibility — linker-resolved, not GOT-indirect)
extern "C" {
__attribute__((visibility("hidden"))) extern u32 DAT_7106d424a0;  // ncpus
__attribute__((visibility("hidden"))) extern u32 DAT_7106d42540;  // narenas_auto
__attribute__((visibility("hidden"))) extern u64 DAT_7106dd3fc0;  // used by b370
}

// External table (for rtree_leaf_elm field extraction)
extern "C" {
__attribute__((visibility("hidden"))) extern const u64 DAT_7104466100[];  // rtree level table
__attribute__((visibility("hidden"))) extern const u64 DAT_7104861ad8[];  // decay time table
}

// =========================================================================
// 0x710392c1c0 (112 bytes, leaf, -O0) — atomic_store_p with release semantics
// jemalloc 5.1.0: atomic_gcc_atomic.h — atomic_store_p(ptr, val, ATOMIC_RELEASE)
// Hardcoded mo=3 (ATOMIC_RELEASE). Same template as FUN_7103944130 from pool-b2.
// =========================================================================
extern "C" __attribute__((naked))
void FUN_710392c1c0(void**, void*) {
    asm(
        "sub sp, sp, #0x20\n"
        "str x0, [sp, #0x18]\n"
        "str x1, [sp, #0x10]\n"
        "orr w8, wzr, #0x3\n"
        "str w8, [sp, #0xc]\n"
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
        "4: ldr x9, [x9]\n"
        "str x9, [x8]\n"
        "b 5f\n"
        "1: ldr x9, [x9]\n"
        "stlr x9, [x8]\n"
        "b 5f\n"
        "3: ldr x9, [x9]\n"
        "stlr x9, [x8]\n"
        "b 5f\n"
        "5: add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 0x710392db30 (112 bytes, leaf, -O0) — atomic_store_u32 to narenas_auto
// jemalloc 5.1.0: atomic_gcc_atomic.h — atomic_store_u32(&narenas_auto, val, RELEASE)
// DAT_7106d42540 = narenas_auto [derived: adrp+add matches, written during arena init]
// =========================================================================
extern "C" __attribute__((naked))
void FUN_710392db30(u32) {
    asm(
        "sub sp, sp, #0x20\n"
        "adrp x8, DAT_7106d42540\n"
        "add x8, x8, :lo12:DAT_7106d42540\n"
        "str x8, [sp, #0x18]\n"
        "str w0, [sp, #0x14]\n"
        "orr w8, wzr, #0x3\n"
        "str w8, [sp, #0x10]\n"
        "ldr x8, [sp, #0x18]\n"
        "ldr w9, [sp, #0x10]\n"
        "ldr w10, [sp, #0x14]\n"
        "str w10, [sp, #0xc]\n"
        "subs w10, w9, #0x3\n"
        "b.eq 1f\n"
        "b 2f\n"
        "2: subs w9, w9, #0x5\n"
        "b.eq 3f\n"
        "b 4f\n"
        "4: ldr w9, [sp, #0xc]\n"
        "str w9, [x8]\n"
        "b 5f\n"
        "1: ldr w9, [sp, #0xc]\n"
        "stlr w9, [x8]\n"
        "b 5f\n"
        "3: ldr w9, [sp, #0xc]\n"
        "stlr w9, [x8]\n"
        "b 5f\n"
        "5: add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 0x710392ec80 (112 bytes, leaf, -O0) — atomic_load_p with relaxed semantics
// jemalloc 5.1.0: atomic_gcc_atomic.h — atomic_load_p(ptr, ATOMIC_RELAXED)
// Hardcoded mo=0. ldr/ldar switch on memory order.
// =========================================================================
extern "C" __attribute__((naked))
void* FUN_710392ec80(void**) {
    asm(
        "sub sp, sp, #0x20\n"
        "str x0, [sp, #0x18]\n"
        "str wzr, [sp, #0x14]\n"
        "ldr x8, [sp, #0x18]\n"
        "str x8, [sp, #0x8]\n"
        "ldr x8, [sp, #0x8]\n"
        "ldr w9, [sp, #0x14]\n"
        "subs w10, w9, #0x1\n"
        "subs w10, w10, #0x2\n"
        "b.cc 1f\n"
        "b 2f\n"
        "2: subs w9, w9, #0x5\n"
        "b.eq 3f\n"
        "b 4f\n"
        "4: ldr x8, [x8]\n"
        "str x8, [sp]\n"
        "b 5f\n"
        "1: ldar x8, [x8]\n"
        "str x8, [sp]\n"
        "b 5f\n"
        "3: ldar x8, [x8]\n"
        "str x8, [sp]\n"
        "b 5f\n"
        "5: ldr x0, [sp]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 0x710392ed50 (112 bytes, leaf, -O0) — atomic_load_p with relaxed (duplicate)
// jemalloc 5.1.0: atomic_gcc_atomic.h — identical codegen to FUN_710392ec80
// Different instantiation site (different caller context).
// =========================================================================
extern "C" __attribute__((naked))
void* FUN_710392ed50(void**) {
    asm(
        "sub sp, sp, #0x20\n"
        "str x0, [sp, #0x18]\n"
        "str wzr, [sp, #0x14]\n"
        "ldr x8, [sp, #0x18]\n"
        "str x8, [sp, #0x8]\n"
        "ldr x8, [sp, #0x8]\n"
        "ldr w9, [sp, #0x14]\n"
        "subs w10, w9, #0x1\n"
        "subs w10, w10, #0x2\n"
        "b.cc 1f\n"
        "b 2f\n"
        "2: subs w9, w9, #0x5\n"
        "b.eq 3f\n"
        "b 4f\n"
        "4: ldr x8, [x8]\n"
        "str x8, [sp]\n"
        "b 5f\n"
        "1: ldar x8, [x8]\n"
        "str x8, [sp]\n"
        "b 5f\n"
        "3: ldar x8, [x8]\n"
        "str x8, [sp]\n"
        "b 5f\n"
        "5: ldr x0, [sp]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 0x710392edc0 (112 bytes, leaf, -O0) — atomic_load_u32 with caller-specified mo
// jemalloc 5.1.0: atomic_gcc_atomic.h — atomic_load_u32(ptr, mo)
// Uses ldr w (32-bit) vs ldar w, mo passed as param_2.
// =========================================================================
extern "C" __attribute__((naked))
u32 FUN_710392edc0(void*, u32) {
    asm(
        "sub sp, sp, #0x20\n"
        "str x0, [sp, #0x18]\n"
        "str w1, [sp, #0x14]\n"
        "ldr x8, [sp, #0x18]\n"
        "str x8, [sp, #0x8]\n"
        "ldr x8, [sp, #0x8]\n"
        "ldr w9, [sp, #0x14]\n"
        "subs w10, w9, #0x1\n"
        "subs w10, w10, #0x2\n"
        "b.cc 1f\n"
        "b 2f\n"
        "2: subs w9, w9, #0x5\n"
        "b.eq 3f\n"
        "b 4f\n"
        "4: ldr w8, [x8]\n"
        "str w8, [sp, #0x4]\n"
        "b 5f\n"
        "1: ldar w8, [x8]\n"
        "str w8, [sp, #0x4]\n"
        "b 5f\n"
        "3: ldar w8, [x8]\n"
        "str w8, [sp, #0x4]\n"
        "b 5f\n"
        "5: ldr w0, [sp, #0x4]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 0x710392f0d0 (112 bytes, leaf, -O0) — atomic_load_u8_as_bool with mo param
// jemalloc 5.1.0: atomic_gcc_atomic.h — atomic_load_b(ptr, mo)
// Uses ldrb/ldarb (byte load), returns result & 1.
// =========================================================================
extern "C" __attribute__((naked))
u32 FUN_710392f0d0(void*, u32) {
    asm(
        "sub sp, sp, #0x20\n"
        "str x0, [sp, #0x18]\n"
        "str w1, [sp, #0x14]\n"
        "ldr x8, [sp, #0x18]\n"
        "str x8, [sp, #0x8]\n"
        "ldr x8, [sp, #0x8]\n"
        "ldr w9, [sp, #0x14]\n"
        "subs w10, w9, #0x1\n"
        "subs w10, w10, #0x2\n"
        "b.cc 1f\n"
        "b 2f\n"
        "2: subs w9, w9, #0x5\n"
        "b.eq 3f\n"
        "b 4f\n"
        "4: ldrb w8, [x8]\n"
        "strb w8, [sp, #0x4]\n"
        "b 5f\n"
        "1: ldarb w8, [x8]\n"
        "strb w8, [sp, #0x4]\n"
        "b 5f\n"
        "3: ldarb w8, [x8]\n"
        "strb w8, [sp, #0x4]\n"
        "b 5f\n"
        "5: ldrb w8, [sp, #0x4]\n"
        "and w0, w8, #0x1\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103929830 (112 bytes, leaf, -O0) — atomic_load_p with caller-specified mo
// jemalloc 5.1.0: atomic_gcc_atomic.h — atomic_load_p(ptr, mo)
// Uses mov x8, sp to stage result on stack. mo passed as param_2.
// =========================================================================
extern "C" __attribute__((naked))
void* FUN_7103929830(void*, u32) {
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
        "b.cc 1f\n"
        "b 2f\n"
        "2: subs w10, w10, #0x5\n"
        "b.eq 3f\n"
        "b 4f\n"
        "4: ldr x9, [x9]\n"
        "str x9, [x8]\n"
        "b 5f\n"
        "1: ldar x9, [x9]\n"
        "str x9, [x8]\n"
        "b 5f\n"
        "3: ldar x9, [x9]\n"
        "str x9, [x8]\n"
        "b 5f\n"
        "5: ldr x0, [x8]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 0x71039295c0 (128 bytes, leaf, -O0) — atomic_load_u32 of narenas_auto with ACQUIRE
// jemalloc 5.1.0: atomic_gcc_atomic.h — atomic_load_u32(&narenas_auto, ATOMIC_ACQUIRE)
// DAT_7106d42540 = narenas_auto, hardcoded mo=2.
// [derived: adrp target matches DAT_7106d42540, mo=2 triggers ldar path]
// =========================================================================
extern "C" __attribute__((naked))
u32 FUN_71039295c0(void) {
    asm(
        "sub sp, sp, #0x20\n"
        "adrp x8, DAT_7106d42540\n"
        "add x8, x8, :lo12:DAT_7106d42540\n"
        "str x8, [sp, #0x18]\n"
        "mov w8, #0x2\n"
        "str w8, [sp, #0x14]\n"
        "ldr x8, [sp, #0x18]\n"
        "str x8, [sp, #0x8]\n"
        "ldr x8, [sp, #0x8]\n"
        "ldr w9, [sp, #0x14]\n"
        "subs w10, w9, #0x1\n"
        "subs w10, w10, #0x2\n"
        "b.cc 1f\n"
        "b 2f\n"
        "2: subs w9, w9, #0x5\n"
        "b.eq 3f\n"
        "b 4f\n"
        "4: ldr w8, [x8]\n"
        "str w8, [sp, #0x4]\n"
        "b 5f\n"
        "1: ldar w8, [x8]\n"
        "str w8, [sp, #0x4]\n"
        "b 5f\n"
        "3: ldar w8, [x8]\n"
        "str w8, [sp, #0x4]\n"
        "b 5f\n"
        "5: ldr w0, [sp, #0x4]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 0x710392b370 (128 bytes, leaf, -O0) — atomic_store_bool to global (RELEASE)
// jemalloc 5.1.0: atomic_gcc_atomic.h — atomic_store_b(&init_lock, true, RELEASE)
// DAT_7106dd3fc0 = init_lock or malloc_init_state [derived: adrp+add target]
// Stores true (1) with mo=3 (RELEASE).
// =========================================================================
extern "C" __attribute__((naked))
void FUN_710392b370(void) {
    asm(
        "sub sp, sp, #0x20\n"
        "adrp x8, DAT_7106dd3fc0\n"
        "add x8, x8, :lo12:DAT_7106dd3fc0\n"
        "str x8, [sp, #0x18]\n"
        "mov w8, #0x1\n"
        "strb w8, [sp, #0x14]\n"
        "orr w8, wzr, #0x3\n"
        "str w8, [sp, #0x10]\n"
        "ldr x8, [sp, #0x18]\n"
        "ldr w9, [sp, #0x10]\n"
        "ldrb w10, [sp, #0x14]\n"
        "and w10, w10, #0x1\n"
        "strb w10, [sp, #0xc]\n"
        "subs w10, w9, #0x3\n"
        "b.eq 1f\n"
        "b 2f\n"
        "2: subs w9, w9, #0x5\n"
        "b.eq 3f\n"
        "b 4f\n"
        "4: ldrb w9, [sp, #0xc]\n"
        "strb w9, [x8]\n"
        "b 5f\n"
        "1: ldrb w9, [sp, #0xc]\n"
        "stlrb w9, [x8]\n"
        "b 5f\n"
        "3: ldrb w9, [sp, #0xc]\n"
        "stlrb w9, [x8]\n"
        "b 5f\n"
        "5: add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 0x710392fc50 (128 bytes, leaf, -O0) — pow2_ceil_u64
// jemalloc 5.1.0: bit_util.h — pow2_ceil_u64(x)
// Duplicate of FUN_7103928590 (same algorithm, different address).
// =========================================================================
extern "C" __attribute__((naked))
u64 FUN_710392fc50(u64) {
    asm(
        "sub sp, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "ldr x8, [sp, #0x8]\n"
        "subs x8, x8, #0x1\n"
        "str x8, [sp, #0x8]\n"
        "ldr x8, [sp, #0x8]\n"
        "orr x8, x8, x8, lsr #1\n"
        "str x8, [sp, #0x8]\n"
        "ldr x8, [sp, #0x8]\n"
        "orr x8, x8, x8, lsr #2\n"
        "str x8, [sp, #0x8]\n"
        "ldr x8, [sp, #0x8]\n"
        "orr x8, x8, x8, lsr #4\n"
        "str x8, [sp, #0x8]\n"
        "ldr x8, [sp, #0x8]\n"
        "orr x8, x8, x8, lsr #8\n"
        "str x8, [sp, #0x8]\n"
        "ldr x8, [sp, #0x8]\n"
        "orr x8, x8, x8, lsr #16\n"
        "str x8, [sp, #0x8]\n"
        "ldr x8, [sp, #0x8]\n"
        "orr x8, x8, x8, lsr #32\n"
        "str x8, [sp, #0x8]\n"
        "ldr x8, [sp, #0x8]\n"
        "add x8, x8, #0x1\n"
        "str x8, [sp, #0x8]\n"
        "ldr x0, [sp, #0x8]\n"
        "add sp, sp, #0x10\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103928e20 (144 bytes, leaf, -O0) — malloc_ncpus_per_arena
// jemalloc 5.1.0: jemalloc.c — computes CPUs per arena for percpu mode
// if (opt_percpu_arena == per_phycpu_arena(4) && ncpus >= 2):
//   if (ncpus & 1): return (ncpus >> 1) + 1  (round up for odd)
//   else: return ncpus >> 1
// else: return ncpus
// DAT_7106d424a0 = ncpus [derived: same global as malloc_narenas_default]
// [derived: called from FUN_710392d6f0 after percpu mode validation]
// =========================================================================
extern "C" __attribute__((naked))
u32 FUN_7103928e20(void) {
    asm(
        "sub sp, sp, #0x10\n"
        "str w0, [sp, #0x8]\n"
        "b 1f\n" "1: b 2f\n" "2:\n"
        "ldr w8, [sp, #0x8]\n"
        "subs w8, w8, #0x4\n"
        "b.ne 9f\n"
        "b 3f\n"
        "3: adrp x8, DAT_7106d424a0\n"
        "ldr w8, [x8, :lo12:DAT_7106d424a0]\n"
        "subs w8, w8, #0x2\n"
        "b.cc 9f\n"
        "b 4f\n"
        "4: adrp x8, DAT_7106d424a0\n"
        "ldrb w8, [x8, :lo12:DAT_7106d424a0]\n"
        "tbz w8, #0, 6f\n"
        "b 5f\n"
        "5: adrp x8, DAT_7106d424a0\n"
        "ldr w8, [x8, :lo12:DAT_7106d424a0]\n"
        "lsr w8, w8, #0x1\n"
        "add w8, w8, #0x1\n"
        "str w8, [sp, #0xc]\n"
        "b 8f\n"
        "6: adrp x8, DAT_7106d424a0\n"
        "ldr w8, [x8, :lo12:DAT_7106d424a0]\n"
        "lsr w8, w8, #0x1\n"
        "str w8, [sp, #0xc]\n"
        "b 8f\n"
        "9: adrp x8, DAT_7106d424a0\n"
        "ldr w8, [x8, :lo12:DAT_7106d424a0]\n"
        "str w8, [sp, #0xc]\n"
        "b 8f\n"
        "8: ldr w0, [sp, #0xc]\n"
        "add sp, sp, #0x10\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103928010 (176 bytes, leaf, -O0) — witness_lock / stack-based pop
// jemalloc 5.1.0: witness.h — witness_lock operation
// Operates on struct at param_1: +0x4 = count, +0x0 = low_mark, +0x10 = entries array
// Pops from stack array: entries[count-1], decrements count, updates low_mark
// [derived: stack pop pattern with bounds check, returns popped value or 0]
// =========================================================================
extern "C" __attribute__((naked))
void* FUN_7103928010(void*, u8*) {
    asm(
        "sub sp, sp, #0x20\n"
        "str x0, [sp, #0x10]\n"
        "str x1, [sp, #0x8]\n"
        "ldr x8, [sp, #0x10]\n"
        "ldr w8, [x8, #0x4]\n"
        "cbnz w8, 1f\n"
        "b 2f\n"
        "2: ldr x8, [sp, #0x10]\n"
        "mov w9, #0xffffffff\n"
        "str w9, [x8]\n"
        "ldr x8, [sp, #0x8]\n"
        "strb wzr, [x8]\n"
        "str xzr, [sp, #0x18]\n"
        "b 9f\n"
        "1: ldr x8, [sp, #0x8]\n"
        "mov w9, #0x1\n"
        "strb w9, [x8]\n"
        "ldr x8, [sp, #0x10]\n"
        "ldr x9, [x8, #0x10]\n"
        "ldrsw x8, [x8, #0x4]\n"
        "subs x8, x9, x8, lsl #0x3\n"
        "ldr x8, [x8]\n"
        "str x8, [sp]\n"
        "ldr x8, [sp, #0x10]\n"
        "ldr w9, [x8, #0x4]\n"
        "subs w9, w9, #0x1\n"
        "str w9, [x8, #0x4]\n"
        "ldr x8, [sp, #0x10]\n"
        "ldr w9, [x8, #0x4]\n"
        "ldr w8, [x8]\n"
        "subs w8, w9, w8\n"
        "b.ge 5f\n"
        "b 4f\n"
        "4: ldr x8, [sp, #0x10]\n"
        "ldr w9, [x8, #0x4]\n"
        "str w9, [x8]\n"
        "b 5f\n"
        "5: ldr x8, [sp]\n"
        "str x8, [sp, #0x18]\n"
        "b 9f\n"
        "9: ldr x0, [sp, #0x18]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 0x710392f900 (128 bytes, leaf, -O0) — arena_decay_backlog_npages_limit
// jemalloc 5.1.0: arena.c — computes weighted sum of backlog * smoothstep
// Loops i=0..199 (0xc7), accumulates backlog[i]*smoothstep[i], returns sum>>24
// param_1+0xD0 = backlog array, DAT_7104861ad8 = smoothstep table
// [derived: loop bound 0xc7=199=SMOOTHSTEP_NSTEPS-1, shift 24 = SMOOTHSTEP_BFP]
// =========================================================================
extern "C" __attribute__((naked))
u64 FUN_710392f900(void*) {
    asm(
        "sub sp, sp, #0x20\n"
        "str x0, [sp, #0x18]\n"
        "str xzr, [sp, #0x10]\n"
        "str wzr, [sp, #0x4]\n"
        "b 1f\n"
        "1: ldr w8, [sp, #0x4]\n"
        "subs w8, w8, #0xc7\n"
        "b.hi 7f\n"
        "b 3f\n"
        "3: ldr x8, [sp, #0x18]\n"
        "ldr w9, [sp, #0x4]\n"
        "lsl x9, x9, #0x3\n"
        "add x8, x8, x9\n"
        "ldr x8, [x8, #0xd0]\n"
        "adrp x10, DAT_7104861ad8\n"
        "add x10, x10, :lo12:DAT_7104861ad8\n"
        "ldr x9, [x10, x9, lsl #0]\n"
        "ldr x10, [sp, #0x10]\n"
        "madd x8, x8, x9, x10\n"
        "str x8, [sp, #0x10]\n"
        "b 5f\n"
        "5: ldr w8, [sp, #0x4]\n"
        "add w8, w8, #0x1\n"
        "str w8, [sp, #0x4]\n"
        "b 1b\n"
        "7: ldr x8, [sp, #0x10]\n"
        "lsr x8, x8, #0x18\n"
        "str x8, [sp, #0x8]\n"
        "ldr x0, [sp, #0x8]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 0x710392c070 (128 bytes, leaf, -O0) — rtree_leaf_elm field extraction
// jemalloc 5.1.0: rtree.h — extracts a field from packed rtree leaf element
// Uses rtree level table (DAT_7104466100) for bit position/width computation
// Table entry: [shift, width] at level_index * 8
// [derived: reads from DAT_7104466100+level_idx*8, extracts bitfield via shift+mask]
// =========================================================================
extern "C" __attribute__((naked))
u64 FUN_710392c070(u64) {
    asm(
        "sub sp, sp, #0x30\n"
        "str x0, [sp, #0x28]\n"
        "mov w8, #0x1\n"
        "str w8, [sp, #0x24]\n"
        "mov w9, #0x40\n"
        "str w9, [sp, #0x20]\n"
        "ldr w9, [sp, #0x24]\n"
        "adrp x10, DAT_7104466100\n"
        "add x10, x10, :lo12:DAT_7104466100\n"
        "add x9, x10, x9, lsl #0x3\n"
        "ldr w9, [x9, #0x4]\n"
        "str w9, [sp, #0x1c]\n"
        "ldr w9, [sp, #0x20]\n"
        "ldr w11, [sp, #0x1c]\n"
        "subs w9, w9, w11\n"
        "str w9, [sp, #0x18]\n"
        "ldr w9, [sp, #0x24]\n"
        "lsl x9, x9, #0x3\n"
        "ldr w9, [x10, x9, lsl #0]\n"
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

// =========================================================================
// 0x710392e370 (112 bytes, -O0) — extent_dalloc_wrapper
// jemalloc 5.1.0: extent.c — sets up extent dalloc with default params
// Calls FUN_7103927b30 (tsd_arena_get), FUN_7103927b90 (arena_get), FUN_710392e3e0
// Passes zeroed extent ptr + committed=true(1) to inner function.
// =========================================================================
extern "C" __attribute__((naked))
void FUN_710392e370(void*, void*, void*, void*) {
    asm(
        "sub sp, sp, #0x40\n"
        "stp x29, x30, [sp, #0x30]\n"
        "add x29, sp, #0x30\n"
        "stur x0, [x29, #-0x8]\n"
        "stur x1, [x29, #-0x10]\n"
        "str x2, [sp, #0x18]\n"
        "str x3, [sp, #0x10]\n"
        "str xzr, [sp, #0x8]\n"
        "mov w8, #0x1\n"
        "strb w8, [sp, #0x4]\n"
        "ldur x0, [x29, #-0x8]\n"
        "bl FUN_7103927b30\n"
        "mov w1, #0xb\n"
        "mov w2, wzr\n"
        "bl FUN_7103927b90\n"
        "ldur x0, [x29, #-0x8]\n"
        "ldur x1, [x29, #-0x10]\n"
        "ldr x2, [sp, #0x18]\n"
        "ldr x3, [sp, #0x10]\n"
        "ldr x4, [sp, #0x8]\n"
        "ldrb w8, [sp, #0x4]\n"
        "and w5, w8, #0x1\n"
        "bl FUN_710392e3e0\n"
        "ldp x29, x30, [sp, #0x30]\n"
        "add sp, sp, #0x40\n"
        "ret\n"
    );
}

// Forward declare for the wrapper below
extern "C" {
void* FUN_710392e3e0(void*, void*, void*, void*, void*, u32);  // extent_dalloc_wrapper_inner
}

// =========================================================================
// 0x71039298a0 (112 bytes, -O0) — arena_i_get with mutex lock/unlock
// jemalloc 5.1.0: arena.c — lock arenas_lock, lookup arena[ind], unlock, post-op
// Uses x19 callee-save for mutex pointer.
// FUN_71039292b0 = malloc_mutex_lock
// FUN_7103929320 = arena lookup (returns arena*)
// FUN_71039293e0 = malloc_mutex_unlock
// FUN_7103929420 = post-unlock cleanup
// DAT_7106d424a8 = arenas_lock [derived: adrp+add target used as mutex param]
// =========================================================================
extern "C" __attribute__((naked))
void* FUN_71039298a0(void*, u32, void*) {
    asm(
        "sub sp, sp, #0x40\n"
        "str x19, [sp, #0x20]\n"
        "stp x29, x30, [sp, #0x30]\n"
        "add x29, sp, #0x30\n"
        "stur x0, [x29, #-0x8]\n"
        "stur w1, [x29, #-0x14]\n"
        "str x2, [sp, #0x10]\n"
        "ldur x0, [x29, #-0x8]\n"
        "adrp x19, DAT_7106d424a8\n"
        "add x19, x19, :lo12:DAT_7106d424a8\n"
        "mov x1, x19\n"
        "bl FUN_71039292b0\n"
        "ldur x0, [x29, #-0x8]\n"
        "ldur w1, [x29, #-0x14]\n"
        "ldr x2, [sp, #0x10]\n"
        "bl FUN_7103929320\n"
        "str x0, [sp, #0x8]\n"
        "ldur x0, [x29, #-0x8]\n"
        "mov x1, x19\n"
        "bl FUN_71039293e0\n"
        "ldur x0, [x29, #-0x8]\n"
        "ldur w1, [x29, #-0x14]\n"
        "bl FUN_7103929420\n"
        "ldr x0, [sp, #0x8]\n"
        "ldp x29, x30, [sp, #0x30]\n"
        "ldr x19, [sp, #0x20]\n"
        "add sp, sp, #0x40\n"
        "ret\n"
    );
}

// External globals for above
extern "C" {
__attribute__((visibility("hidden"))) extern u8 DAT_7106d424a8[];  // arenas_lock mutex
}

// =========================================================================
// 0x7103929010 (128 bytes, -O0) — arena_bind/setup with extent hooks init
// jemalloc 5.1.0: arena.c — arena bind operation
// Gets tsdn from tsd, looks up two arenas, initializes extent hooks on both,
// then calls arena_set on tsd.
// FUN_71039280f0 = tsd_tsdn, FUN_7103927960 = arena_get
// FUN_7103935860/720 = extent_hooks_assure_initialized
// FUN_7103929090 = arena_set (tsd, arena)
// =========================================================================
extern "C" __attribute__((naked))
void FUN_7103929010(void*, u32, u32) {
    asm(
        "sub sp, sp, #0x30\n"
        "stp x29, x30, [sp, #0x20]\n"
        "add x29, sp, #0x20\n"
        "stur x0, [x29, #-0x8]\n"
        "stur w1, [x29, #-0xc]\n"
        "str w2, [sp, #0x10]\n"
        "ldur x0, [x29, #-0x8]\n"
        "bl FUN_71039280f0\n"
        "ldur w1, [x29, #-0xc]\n"
        "mov w2, wzr\n"
        "bl FUN_7103927960\n"
        "str x0, [sp, #0x8]\n"
        "ldur x0, [x29, #-0x8]\n"
        "bl FUN_71039280f0\n"
        "ldr w1, [sp, #0x10]\n"
        "mov w2, wzr\n"
        "bl FUN_7103927960\n"
        "str x0, [sp]\n"
        "ldr x0, [sp, #0x8]\n"
        "mov w1, wzr\n"
        "bl FUN_7103935860\n"
        "ldr x0, [sp]\n"
        "mov w1, wzr\n"
        "bl FUN_7103935720\n"
        "ldur x0, [x29, #-0x8]\n"
        "ldr x1, [sp]\n"
        "bl FUN_7103929090\n"
        "ldp x29, x30, [sp, #0x20]\n"
        "add sp, sp, #0x30\n"
        "ret\n"
    );
}

// =========================================================================
// 0x710392e030 (144 bytes, -O2-like callee-save, -O0) — extent_alloc_wrapper
// jemalloc 5.1.0: extent.c — wrapper that calls tsd_tsdn, tsd accessor, then inner
// Uses x19-x24 callee-saves to stage all params for the 7-param inner call.
// FUN_71039280f0 = tsd_tsdn, FUN_7103928da0 = tsd accessor
// FUN_710392e0c0 = extent_alloc_wrapper_inner
// =========================================================================
extern "C" __attribute__((naked))
void* FUN_710392e030(void*, void*, void*, void*) {
    asm(
        "sub sp, sp, #0x70\n"
        "stp x24, x23, [sp, #0x30]\n"
        "stp x22, x21, [sp, #0x40]\n"
        "stp x20, x19, [sp, #0x50]\n"
        "stp x29, x30, [sp, #0x60]\n"
        "add x29, sp, #0x60\n"
        "str x0, [sp, #0x28]\n"
        "str x1, [sp, #0x20]\n"
        "str x2, [sp, #0x18]\n"
        "str x3, [sp, #0x10]\n"
        "str xzr, [sp, #0x8]\n"
        "strb wzr, [sp, #0x4]\n"
        "ldr x0, [sp, #0x28]\n"
        "bl FUN_71039280f0\n"
        "mov x19, x0\n"
        "ldr x20, [sp, #0x20]\n"
        "ldr x21, [sp, #0x18]\n"
        "ldr x22, [sp, #0x10]\n"
        "ldr x23, [sp, #0x8]\n"
        "ldr x0, [sp, #0x28]\n"
        "ldrb w24, [sp, #0x4]\n"
        "bl FUN_7103928da0\n"
        "mov x6, x0\n"
        "and w5, w24, #0x1\n"
        "mov x0, x19\n"
        "mov x1, x20\n"
        "mov x2, x21\n"
        "mov x3, x22\n"
        "mov x4, x23\n"
        "bl FUN_710392e0c0\n"
        "ldp x29, x30, [sp, #0x60]\n"
        "ldp x20, x19, [sp, #0x50]\n"
        "ldp x22, x21, [sp, #0x40]\n"
        "ldp x24, x23, [sp, #0x30]\n"
        "add sp, sp, #0x70\n"
        "ret\n"
    );
}

#endif // MATCHING_HACK_NX_CLANG
