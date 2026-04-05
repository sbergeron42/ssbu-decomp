// jemalloc 5.1.0 — size class utilities and bit helpers
// Nintendo Switch build: SDK 8.2.1
// jemalloc 5.1.0-2-g97d9c2105f87d2490f707a4daecc3baac5c170ed
// Config: LG_QUANTUM=4, LG_PAGE=12, LG_SIZE_CLASS_GROUP=2, LG_TINY_MIN=3, NTBINS=1
//
// NX jemalloc compiled at -O0 — upstream Clang -O2 cannot match the codegen.
// Uses naked asm for most functions; optnone for simple wrappers.
// Source: bit_util.h (lg_floor, pow2_ceil_u64), sz.h (sz_* functions)

#include "types.h"

// External tables (hidden visibility: linker-resolved, not GOT-indirect)
extern "C" {
__attribute__((visibility("hidden"))) extern const usize sz_index2size_tab[];
__attribute__((visibility("hidden"))) extern const u8 sz_size2index_tab[];
}

// Forward declarations for extern "C" functions defined below
extern "C" {
usize sz_index2size_lookup(u32);
u32   sz_size2index_lookup(usize);
usize sz_s2u_lookup(usize);
usize sz_s2u_compute(usize);
u32   sz_size2index_compute(usize);
}

#ifdef MATCHING_HACK_NX_CLANG

// =========================================================================
// jemalloc 5.1.0: bit_util.h — pow2_ceil_u64
// 0x7103928590 (128 bytes, leaf)
// C++ linkage: matches extern declaration in fun_batch_d_011.cpp
// =========================================================================
__attribute__((naked))
void FUN_7103928590(u64) {
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
// jemalloc 5.1.0: bit_util.h — lg_floor (fallback, no __builtin_clz)
// 0x7103928480 (176 bytes)
// Calls: FUN_7103928530 (ffs_zu wrapper, C++ linkage)
// =========================================================================
extern "C" __attribute__((naked))
u32 FUN_7103928480(usize) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp]\n"
        "b 1f\n"
        "1: b 2f\n"
        "2:\n"
        "ldr x8, [sp]\n"
        "orr x8, x8, x8, lsr #1\n"
        "str x8, [sp]\n"
        "ldr x8, [sp]\n"
        "orr x8, x8, x8, lsr #2\n"
        "str x8, [sp]\n"
        "ldr x8, [sp]\n"
        "orr x8, x8, x8, lsr #4\n"
        "str x8, [sp]\n"
        "ldr x8, [sp]\n"
        "orr x8, x8, x8, lsr #8\n"
        "str x8, [sp]\n"
        "ldr x8, [sp]\n"
        "orr x8, x8, x8, lsr #16\n"
        "str x8, [sp]\n"
        "ldr x8, [sp]\n"
        "orr x8, x8, x8, lsr #32\n"
        "str x8, [sp]\n"
        "ldr x8, [sp]\n"
        "adds x8, x8, #0x1\n"
        "b.ne 3f\n"
        "b 4f\n"
        "4:\n"
        "orr w8, wzr, #0x3f\n"
        "stur w8, [x29, #-0x4]\n"
        "b 0f\n"
        "3:\n"
        "ldr x8, [sp]\n"
        "add x8, x8, #0x1\n"
        "str x8, [sp]\n"
        "ldr x0, [sp]\n"
        "bl _Z14FUN_7103928530y\n"
        "subs w8, w0, #0x2\n"
        "stur w8, [x29, #-0x4]\n"
        "b 0f\n"
        "0:\n"
        "ldur w0, [x29, #-0x4]\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// jemalloc 5.1.0: sz.h — sz_index2size_lookup
// 0x71039282b0 (48 bytes, leaf)
// =========================================================================
extern "C" __attribute__((naked))
usize sz_index2size_lookup(u32) {
    asm(
        "sub sp, sp, #0x10\n"
        "str w0, [sp, #0xc]\n"
        "ldr w8, [sp, #0xc]\n"
        "adrp x9, sz_index2size_tab\n"
        "add x9, x9, :lo12:sz_index2size_tab\n"
        "ldr x8, [x9, x8, lsl #3]\n"
        "str x8, [sp]\n"
        "b 1f\n"
        "1: b 2f\n"
        "2:\n"
        "ldr x0, [sp]\n"
        "add sp, sp, #0x10\n"
        "ret\n"
    );
}

// =========================================================================
// jemalloc 5.1.0: sz.h — sz_size2index_lookup
// 0x7103928610 (64 bytes, leaf)
// =========================================================================
extern "C" __attribute__((naked))
u32 sz_size2index_lookup(usize) {
    asm(
        "sub sp, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "b 1f\n"
        "1: b 2f\n"
        "2:\n"
        "ldr x8, [sp, #0x8]\n"
        "subs x8, x8, #0x1\n"
        "lsr x8, x8, #3\n"
        "adrp x9, sz_size2index_tab\n"
        "add x9, x9, :lo12:sz_size2index_tab\n"
        "ldrb w8, [x9, x8]\n"
        "str w8, [sp, #0x4]\n"
        "b 3f\n"
        "3: b 4f\n"
        "4:\n"
        "ldr w0, [sp, #0x4]\n"
        "add sp, sp, #0x10\n"
        "ret\n"
    );
}

// =========================================================================
// jemalloc 5.1.0: sz.h — sz_s2u_lookup
// 0x71039282e0 (64 bytes)
// Calls: sz_size2index_lookup, sz_index2size_lookup
// =========================================================================
extern "C" __attribute__((naked))
usize sz_s2u_lookup(usize) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "ldr x0, [sp, #0x8]\n"
        "bl sz_size2index_lookup\n"
        "bl sz_index2size_lookup\n"
        "str x0, [sp]\n"
        "b 1f\n"
        "1: b 2f\n"
        "2:\n"
        "ldr x0, [sp]\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// jemalloc 5.1.0: sz.h — sz_s2u_compute
// 0x7103928320 (304 bytes)
// Calls: FUN_7103928450 (pow2_ceil_zu), FUN_7103928480 (lg_floor)
// =========================================================================
extern "C" __attribute__((naked))
usize sz_s2u_compute(usize) {
    asm(
        "sub sp, sp, #0x60\n"
        "stp x29, x30, [sp, #0x50]\n"
        "add x29, sp, #0x50\n"
        "stur x0, [x29, #-0x10]\n"
        // if (size > LARGE_MAXCLASS) return 0
        "ldur x8, [x29, #-0x10]\n"
        "mov x9, #0x1\n"
        "movk x9, #0x7000, lsl #48\n"
        "subs x8, x8, x9\n"
        "b.cc 1f\n"
        "b 2f\n"
        "2:\n"
        "stur xzr, [x29, #-0x8]\n"
        "b 0f\n"
        // if (size <= 8) — tiny path
        "1:\n"
        "ldur x8, [x29, #-0x10]\n"
        "subs x8, x8, #0x8\n"
        "b.hi 3f\n"
        "b 4f\n"
        "4:\n"
        "orr w8, wzr, #0x3\n"           // lg_tmin = 3
        "stur x8, [x29, #-0x18]\n"
        "ldur x0, [x29, #-0x10]\n"
        "bl _Z14FUN_7103928450y\n"       // pow2_ceil_zu(size)
        "bl FUN_7103928480\n"            // lg_floor(result)
        "mov w8, w0\n"
        "stur x8, [x29, #-0x20]\n"
        "ldur x8, [x29, #-0x20]\n"
        "ldur x9, [x29, #-0x18]\n"
        "subs x8, x8, x9\n"
        "b.cs 5f\n"
        "b 6f\n"
        "6:\n"
        "ldur x8, [x29, #-0x18]\n"
        "mov w9, #0x1\n"
        "lsl x8, x9, x8\n"
        "b 7f\n"
        "5:\n"
        "ldur x8, [x29, #-0x20]\n"
        "mov w9, #0x1\n"
        "lsl x8, x9, x8\n"
        "b 7f\n"
        "7:\n"
        "stur x8, [x29, #-0x8]\n"
        "b 0f\n"
        // General path
        "3:\n"
        "ldur x8, [x29, #-0x10]\n"
        "lsl x8, x8, #1\n"
        "subs x0, x8, #0x1\n"
        "bl FUN_7103928480\n"            // lg_floor((size<<1)-1)
        "mov w8, w0\n"
        "str x8, [sp, #0x28]\n"
        "ldr x8, [sp, #0x28]\n"
        "subs x8, x8, #0x6\n"           // x < 7?
        "b.hi 8f\n"
        "b 9f\n"
        "9:\n"
        "mov w8, #0x4\n"                // lg_delta = LG_QUANTUM = 4
        "b 10f\n"
        "8:\n"
        "ldr x8, [sp, #0x28]\n"
        "subs x8, x8, #0x3\n"           // lg_delta = x - 3
        "b 10f\n"
        "10:\n"
        "str x8, [sp, #0x20]\n"
        "ldr x8, [sp, #0x20]\n"
        "mov w9, #0x1\n"
        "lsl x8, x9, x8\n"              // delta = 1 << lg_delta
        "str x8, [sp, #0x18]\n"
        "ldr x8, [sp, #0x18]\n"
        "subs x8, x8, #0x1\n"           // delta_mask = delta - 1
        "str x8, [sp, #0x10]\n"
        "ldur x8, [x29, #-0x10]\n"
        "ldr x9, [sp, #0x10]\n"
        "add x8, x8, x9\n"              // size + delta_mask
        "bic x8, x8, x9\n"              // & ~delta_mask
        "str x8, [sp, #0x8]\n"
        "ldr x8, [sp, #0x8]\n"
        "stur x8, [x29, #-0x8]\n"
        "b 0f\n"
        // Return
        "0:\n"
        "ldur x0, [x29, #-0x8]\n"
        "ldp x29, x30, [sp, #0x50]\n"
        "add sp, sp, #0x60\n"
        "ret\n"
    );
}

// =========================================================================
// jemalloc 5.1.0: sz.h — sz_size2index_compute
// 0x7103929910 (352 bytes)
// Calls: FUN_7103928450 (pow2_ceil_zu), FUN_7103928480 (lg_floor)
// =========================================================================
extern "C" __attribute__((naked))
u32 sz_size2index_compute(usize) {
    asm(
        "sub sp, sp, #0x50\n"
        "stp x29, x30, [sp, #0x40]\n"
        "add x29, sp, #0x40\n"
        "stur x0, [x29, #-0x10]\n"
        // if (size > LARGE_MAXCLASS) return NSIZES
        "ldur x8, [x29, #-0x10]\n"
        "mov x9, #0x1\n"
        "movk x9, #0x7000, lsl #48\n"
        "subs x8, x8, x9\n"
        "b.cc 1f\n"
        "b 2f\n"
        "2:\n"
        "mov w8, #0xe8\n"               // NSIZES = 232
        "stur w8, [x29, #-0x4]\n"
        "b 0f\n"
        // if (size <= 8) — tiny path
        "1:\n"
        "ldur x8, [x29, #-0x10]\n"
        "subs x8, x8, #0x8\n"
        "b.hi 3f\n"
        "b 4f\n"
        "4:\n"
        "orr w8, wzr, #0x3\n"           // lg_tmin = 3
        "stur w8, [x29, #-0x14]\n"
        "ldur x0, [x29, #-0x10]\n"
        "bl _Z14FUN_7103928450y\n"       // pow2_ceil_zu(size)
        "bl FUN_7103928480\n"            // lg_floor(result)
        "stur w0, [x29, #-0x18]\n"
        "ldur w8, [x29, #-0x18]\n"
        "ldur w9, [x29, #-0x14]\n"
        "subs w8, w8, w9\n"
        "b.cs 5f\n"
        "b 6f\n"
        "6:\n"
        "mov w8, wzr\n"                 // return 0
        "b 7f\n"
        "5:\n"
        "ldur w8, [x29, #-0x18]\n"
        "ldur w9, [x29, #-0x14]\n"
        "subs w8, w8, w9\n"             // lg_ceil - lg_tmin
        "b 7f\n"
        "7:\n"
        "stur w8, [x29, #-0x4]\n"
        "b 0f\n"
        // General path
        "3:\n"
        "ldur x8, [x29, #-0x10]\n"
        "lsl x8, x8, #1\n"
        "subs x0, x8, #0x1\n"
        "bl FUN_7103928480\n"            // x = lg_floor((size<<1)-1)
        "stur w0, [x29, #-0x1c]\n"
        // shift = (x < 6) ? 0 : x - 6
        "ldur w8, [x29, #-0x1c]\n"
        "subs w8, w8, #0x5\n"
        "b.hi 8f\n"
        "b 9f\n"
        "9:\n"
        "mov w8, wzr\n"
        "b 10f\n"
        "8:\n"
        "ldur w8, [x29, #-0x1c]\n"
        "subs w8, w8, #0x6\n"
        "b 10f\n"
        "10:\n"
        // grp = shift << 2
        "str w8, [sp, #0x20]\n"
        "ldr w8, [sp, #0x20]\n"
        "lsl w8, w8, #2\n"
        "str w8, [sp, #0x1c]\n"
        // lg_delta = (x < 7) ? 4 : x - 3
        "ldur w8, [x29, #-0x1c]\n"
        "subs w8, w8, #0x6\n"
        "b.hi 11f\n"
        "b 12f\n"
        "12:\n"
        "mov w8, #0x4\n"
        "b 13f\n"
        "11:\n"
        "ldur w8, [x29, #-0x1c]\n"
        "subs w8, w8, #0x3\n"
        "b 13f\n"
        "13:\n"
        // delta_inverse_mask = -1 << lg_delta
        "str w8, [sp, #0x18]\n"
        "ldr w8, [sp, #0x18]\n"
        "mov x9, #-1\n"
        "lsl x8, x9, x8\n"
        "str x8, [sp, #0x10]\n"
        // mod = (((size-1) & mask) >> lg_delta) & 3
        "ldur x8, [x29, #-0x10]\n"
        "subs x8, x8, #0x1\n"
        "ldr x9, [sp, #0x10]\n"
        "and x8, x8, x9\n"
        "ldr w9, [sp, #0x18]\n"
        "lsr x8, x8, x9\n"
        "and w8, w8, #0x3\n"
        "str w8, [sp, #0xc]\n"
        // index = NTBINS + grp + mod = 1 + grp + mod
        "ldr w8, [sp, #0x1c]\n"
        "ldr w9, [sp, #0xc]\n"
        "add w8, w8, w9\n"
        "add w8, w8, #0x1\n"
        "str w8, [sp, #0x8]\n"
        "ldr w8, [sp, #0x8]\n"
        "stur w8, [x29, #-0x4]\n"
        "b 0f\n"
        // Return
        "0:\n"
        "ldur w0, [x29, #-0x4]\n"
        "ldp x29, x30, [sp, #0x40]\n"
        "add sp, sp, #0x50\n"
        "ret\n"
    );
}

// =========================================================================
// jemalloc 5.1.0: sz.h — sz_size2index
// 0x7103927900 (96 bytes)
// Calls: sz_size2index_lookup, sz_size2index_compute
// =========================================================================
extern "C" __attribute__((naked))
u32 sz_size2index(usize) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp]\n"
        "b 1f\n"
        "1: b 2f\n"
        "2:\n"
        "ldr x8, [sp]\n"
        "subs x8, x8, #0x1, lsl #12\n"  // x8 = size - 0x1000
        "b.hi 3f\n"
        "b 4f\n"
        "4:\n"
        "ldr x0, [sp]\n"
        "bl sz_size2index_lookup\n"
        "stur w0, [x29, #-0x4]\n"
        "b 0f\n"
        "3:\n"
        "ldr x0, [sp]\n"
        "bl sz_size2index_compute\n"
        "stur w0, [x29, #-0x4]\n"
        "b 0f\n"
        "0:\n"
        "ldur w0, [x29, #-0x4]\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// jemalloc 5.1.0: sz.h — sz_s2u
// 0x7103928110 (96 bytes)
// Calls: sz_s2u_lookup, sz_s2u_compute
// =========================================================================
extern "C" __attribute__((naked))
usize sz_s2u(usize) {
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
        "bl sz_s2u_lookup\n"
        "str x0, [sp, #0x8]\n"
        "b 0f\n"
        "3:\n"
        "ldr x0, [sp]\n"
        "bl sz_s2u_compute\n"
        "str x0, [sp, #0x8]\n"
        "b 0f\n"
        "0:\n"
        "ldr x0, [sp, #0x8]\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// jemalloc 5.1.0: sz.h — sz_index2size
// 0x7103928170 (48 bytes)
// Calls: sz_index2size_lookup
// =========================================================================
extern "C" __attribute__((optnone))
usize sz_index2size(u32 index) {
    goto a; a:; do {} while(0);
    return sz_index2size_lookup(index);
}

#endif // MATCHING_HACK_NX_CLANG
