// jemalloc 5.1.0 — bitmap search, extent heap lookup (pool-e, batch 4)
// NX jemalloc compiled at -O0 — uses naked asm for matching
// jemalloc 5.1.0: extent.c, bitmap.c

#include "types.h"

#ifdef MATCHING_HACK_NX_CLANG

// External callees
extern "C" {
u32  FUN_710393e390(u64);
u64  FUN_710393e6a0(u32);
u64  FUN_7103938b30(u64);
u64  FUN_710393e300(u64);
int  FUN_7103939470(u64, u64);
u32  FUN_710393dd80(u64);
u64  FUN_710393cfe0(u64);
u64  FUN_710393ca80(u64);
}

// External globals
extern "C" {
__attribute__((visibility("hidden"))) extern u8 DAT_7104862118;
__attribute__((visibility("hidden"))) extern u8 DAT_71052935e8;
}

// =========================================================================
// 0x71039420a0 (128 bytes) — page-align extent size lookup
// jemalloc 5.1.0: extent.c — extent_size_quantize_ceil helper
// =========================================================================
extern "C" __attribute__((naked))
u64 FUN_71039420a0(u64) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "b 0f\n"
        "0: b 1f\n"
        "1: b 2f\n"
        "2: b 3f\n"
        "3: b 4f\n"
        "4: b 5f\n"
        "5: ldr x0, [sp, #0x8]\n"
        "bl FUN_710393e300\n"
        "str x0, [sp]\n"
        "ldr x8, [sp]\n"
        "ldr x9, [sp, #0x8]\n"
        "subs x8, x8, x9\n"
        "b.cs 8f\n"
        "b 6f\n"
        "6: ldr x8, [sp]\n"
        "orr x9, xzr, #0xffffffffffff0001\n"
        "add x0, x8, x9\n"
        "bl FUN_710393e390\n"
        "bl FUN_710393e6a0\n"
        "add x8, x0, #0x10, lsl #12\n"
        "str x8, [sp]\n"
        "b 8f\n"
        "8: ldr x0, [sp]\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103941d30 (208 bytes) — extent first-fit search (one level)
// jemalloc 5.1.0: extent.c — extent_first_best_fit
// Looks up in bitmap, checks size class, returns extent or null
// =========================================================================
extern "C" __attribute__((naked))
u64 FUN_7103941d30(u64, u64, u64, u64) {
    asm(
        "sub sp, sp, #0x50\n"
        "stp x29, x30, [sp, #0x40]\n"
        "add x29, sp, #0x40\n"
        "stur x0, [x29, #-0x10]\n"
        "stur x1, [x29, #-0x18]\n"
        "str x2, [sp, #0x20]\n"
        "str x3, [sp, #0x18]\n"
        "ldr x0, [sp, #0x18]\n"
        "bl FUN_71039420a0\n"
        "bl FUN_710393e390\n"
        "str w0, [sp, #0x14]\n"
        "ldr x8, [sp, #0x20]\n"
        "add x0, x8, #0x658\n"
        "ldr w2, [sp, #0x14]\n"
        "adrp x1, DAT_7104862118\n"
        "add x1, x1, :lo12:DAT_7104862118\n"
        "bl FUN_7103942120\n"
        "str w0, [sp, #0x10]\n"
        "ldr w8, [sp, #0x10]\n"
        "subs w8, w8, #0xb7\n"
        "b.hi 6f\n"
        "b 0f\n"
        "0: ldr w0, [sp, #0x10]\n"
        "bl FUN_710393e6a0\n"
        "adrp x8, DAT_71052935e8\n"
        "ldr x8, [x8, :lo12:DAT_71052935e8]\n"
        "lsr x8, x0, x8\n"
        "ldr x9, [sp, #0x18]\n"
        "subs x8, x8, x9\n"
        "b.ls 2f\n"
        "b 1f\n"
        "1: stur xzr, [x29, #-0x8]\n"
        "b 7f\n"
        "2: b 3f\n"
        "3: b 4f\n"
        "4: ldr x8, [sp, #0x20]\n"
        "ldr w9, [sp, #0x10]\n"
        "add x8, x8, x9, lsl #0x3\n"
        "add x0, x8, #0x98\n"
        "bl FUN_7103938b30\n"
        "str x0, [sp, #0x8]\n"
        "b 5f\n"
        "5: b 50f\n"
        "50: ldr x8, [sp, #0x8]\n"
        "stur x8, [x29, #-0x8]\n"
        "b 7f\n"
        "6: stur xzr, [x29, #-0x8]\n"
        "b 7f\n"
        "7: ldur x0, [x29, #-0x8]\n"
        "ldp x29, x30, [sp, #0x40]\n"
        "add sp, sp, #0x50\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103941e00 (272 bytes) — extent best-fit search (multi-level loop)
// jemalloc 5.1.0: extent.c — extent_best_fit_locked
// Iterates size classes, finds best-fit extent via linked-list comparison
// =========================================================================
extern "C" __attribute__((naked))
u64 FUN_7103941e00(u64, u64, u64, u64) {
    asm(
        "sub sp, sp, #0x50\n"
        "stp x29, x30, [sp, #0x40]\n"
        "add x29, sp, #0x40\n"
        "stur x0, [x29, #-0x8]\n"
        "stur x1, [x29, #-0x10]\n"
        "stur x2, [x29, #-0x18]\n"
        "str x3, [sp, #0x20]\n"
        "str xzr, [sp, #0x18]\n"
        "ldr x0, [sp, #0x20]\n"
        "bl FUN_71039420a0\n"
        "bl FUN_710393e390\n"
        "str w0, [sp, #0x14]\n"
        "ldur x8, [x29, #-0x18]\n"
        "add x0, x8, #0x658\n"
        "ldr w2, [sp, #0x14]\n"
        "adrp x1, DAT_7104862118\n"
        "add x1, x1, :lo12:DAT_7104862118\n"
        "bl FUN_7103942120\n"
        "str w0, [sp, #0x10]\n"
        // loop head
        "b 0f\n"
        "0: ldr w8, [sp, #0x10]\n"
        "subs w8, w8, #0xb7\n"
        "b.hi 20f\n"
        "b 1f\n"
        "1: b 2f\n"
        "2: b 3f\n"
        "3: ldur x8, [x29, #-0x18]\n"
        "ldr w9, [sp, #0x10]\n"
        "add x8, x8, x9, lsl #0x3\n"
        "add x0, x8, #0x98\n"
        "bl FUN_7103938b30\n"
        "str x0, [sp, #0x8]\n"
        "b 4f\n"
        "4: b 5f\n"
        "5: ldr x8, [sp, #0x18]\n"
        "cbz x8, 7f\n"
        "b 6f\n"
        "6: ldr x0, [sp, #0x8]\n"
        "ldr x1, [sp, #0x18]\n"
        "bl FUN_7103939470\n"
        "tbz w0, #0x1f, 9f\n"
        "b 7f\n"
        "7: ldr x8, [sp, #0x8]\n"
        "str x8, [sp, #0x18]\n"
        "b 9f\n"
        "9: ldr w8, [sp, #0x10]\n"
        "subs w8, w8, #0xb7\n"
        "b.ne 11f\n"
        "b 10f\n"
        "10: b 21f\n"
        "11: b 12f\n"
        "12: b 13f\n"
        "13: b 14f\n"
        "14: ldur x8, [x29, #-0x18]\n"
        "add x0, x8, #0x658\n"
        "ldr w8, [sp, #0x10]\n"
        "add x2, x8, #0x1\n"
        "adrp x1, DAT_7104862118\n"
        "add x1, x1, :lo12:DAT_7104862118\n"
        "bl FUN_7103942120\n"
        "str w0, [sp, #0x10]\n"
        "b 0b\n"
        // end loop
        "20: b 21f\n"
        "21: ldr x0, [sp, #0x18]\n"
        "ldp x29, x30, [sp, #0x40]\n"
        "add sp, sp, #0x50\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103941f10 (400 bytes) — extent retained fit search
// jemalloc 5.1.0: extent.c — extent_grow_retained_fit
// Iterates size classes, checks alignment, finds fit
// =========================================================================
extern "C" __attribute__((naked))
u64 FUN_7103941f10(u64, u64, u64, u64) {
    asm(
        "sub sp, sp, #0x70\n"
        "stp x29, x30, [sp, #0x60]\n"
        "add x29, sp, #0x60\n"
        "stur x0, [x29, #-0x10]\n"
        "stur x1, [x29, #-0x18]\n"
        "stur x2, [x29, #-0x20]\n"
        "stur x3, [x29, #-0x28]\n"
        "ldur x0, [x29, #-0x18]\n"
        "bl FUN_71039420a0\n"
        "bl FUN_710393e390\n"
        "stur w0, [x29, #-0x2c]\n"
        "ldur x0, [x29, #-0x20]\n"
        "bl FUN_71039420a0\n"
        "bl FUN_710393e390\n"
        "str w0, [sp, #0x30]\n"
        "ldur x8, [x29, #-0x10]\n"
        "add x0, x8, #0x658\n"
        "ldur w2, [x29, #-0x2c]\n"
        "adrp x1, DAT_7104862118\n"
        "add x1, x1, :lo12:DAT_7104862118\n"
        "bl FUN_7103942120\n"
        "str w0, [sp, #0x2c]\n"
        // loop head
        "b 0f\n"
        "0: ldr w8, [sp, #0x2c]\n"
        "ldr w9, [sp, #0x30]\n"
        "subs w8, w8, w9\n"
        "b.cs 30f\n"
        "b 1f\n"
        "1: b 2f\n"
        "2: b 3f\n"
        "3: b 4f\n"
        "4: b 5f\n"
        "5: ldur x8, [x29, #-0x10]\n"
        "ldr w9, [sp, #0x2c]\n"
        "add x8, x8, x9, lsl #0x3\n"
        "add x0, x8, #0x98\n"
        "bl FUN_7103938b30\n"
        "str x0, [sp, #0x20]\n"
        "ldr x0, [sp, #0x20]\n"
        "bl FUN_710393cfe0\n"
        "str x0, [sp, #0x18]\n"
        "ldr x0, [sp, #0x20]\n"
        "bl FUN_710393ca80\n"
        "str x0, [sp, #0x10]\n"
        "b 6f\n"
        "6: b 7f\n"
        "7: ldr x8, [sp, #0x18]\n"
        "ldur x9, [x29, #-0x28]\n"
        "orr w10, wzr, #0xffff\n"
        "add x9, x9, x10\n"
        "and x9, x9, #-0x10000\n"
        "add x8, x8, x9\n"
        "subs x8, x8, #0x1\n"
        "negs x9, x9\n"
        "and x8, x8, x9\n"
        "str x8, [sp, #0x8]\n"
        "ldr x8, [sp, #0x18]\n"
        "ldr x9, [sp, #0x8]\n"
        "subs x8, x8, x9\n"
        "b.hi 10f\n"
        "b 8f\n"
        "8: ldr x8, [sp, #0x18]\n"
        "ldr x9, [sp, #0x10]\n"
        "add x8, x8, x9\n"
        "ldr x9, [sp, #0x8]\n"
        "subs x8, x8, x9\n"
        "b.hi 11f\n"
        "b 10f\n"
        "10: b 20f\n"
        "11: ldr x8, [sp, #0x8]\n"
        "ldr x9, [sp, #0x18]\n"
        "subs x8, x8, x9\n"
        "str x8, [sp]\n"
        "ldr x8, [sp, #0x10]\n"
        "ldr x9, [sp]\n"
        "subs x8, x8, x9\n"
        "ldur x9, [x29, #-0x18]\n"
        "subs x8, x8, x9\n"
        "b.cc 13f\n"
        "b 12f\n"
        "12: ldr x8, [sp, #0x20]\n"
        "stur x8, [x29, #-0x8]\n"
        "b 40f\n"
        "13: b 20f\n"
        // loop increment
        "20: ldur x8, [x29, #-0x10]\n"
        "add x0, x8, #0x658\n"
        "ldr w8, [sp, #0x2c]\n"
        "add x2, x8, #0x1\n"
        "adrp x1, DAT_7104862118\n"
        "add x1, x1, :lo12:DAT_7104862118\n"
        "bl FUN_7103942120\n"
        "str w0, [sp, #0x2c]\n"
        "b 0b\n"
        // loop exit
        "30: stur xzr, [x29, #-0x8]\n"
        "b 40f\n"
        "40: ldur x0, [x29, #-0x8]\n"
        "ldp x29, x30, [sp, #0x60]\n"
        "add sp, sp, #0x70\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103942120 (468 bytes) — bitmap_sfu: hierarchical bitmap search
// jemalloc 5.1.0: bitmap.c — bitmap_sfu (search-first-unset)
// Recursive function: searches bitmap levels to find first set bit
// Uses loop over bitmap levels, with self-recursive call
// =========================================================================
extern "C" __attribute__((naked))
u64 FUN_7103942120(u64, u64, u64) {
    asm(
        "sub sp, sp, #0x70\n"
        "stp x29, x30, [sp, #0x60]\n"
        "add x29, sp, #0x60\n"
        "stur x0, [x29, #-0x10]\n"
        "stur x1, [x29, #-0x18]\n"
        "stur x2, [x29, #-0x20]\n"
        "b 0f\n"
        "0: b 1f\n"
        "1: stur xzr, [x29, #-0x28]\n"
        "ldur x8, [x29, #-0x18]\n"
        "ldr w8, [x8, #0x8]\n"
        "stur w8, [x29, #-0x2c]\n"
        // loop head
        "b 2f\n"
        "2: ldur w8, [x29, #-0x2c]\n"
        "subs w9, w8, #0x1\n"
        "stur w9, [x29, #-0x2c]\n"
        "cbz w8, 30f\n"
        "b 3f\n"
        // loop body
        "3: ldur w8, [x29, #-0x2c]\n"
        "orr w9, wzr, #0x6\n"
        "orr w10, wzr, #0x6\n"
        "madd w8, w8, w9, w10\n"
        "str x8, [sp, #0x28]\n"
        "ldur x8, [x29, #-0x10]\n"
        "ldur x9, [x29, #-0x18]\n"
        "ldur w10, [x29, #-0x2c]\n"
        "add x9, x9, x10, lsl #0x3\n"
        "ldr x9, [x9, #0x10]\n"
        "ldur x10, [x29, #-0x28]\n"
        "ldr x11, [sp, #0x28]\n"
        "lsr x10, x10, x11\n"
        "add x9, x9, x10\n"
        "ldr x8, [x8, x9, lsl #0x3]\n"
        "str x8, [sp, #0x20]\n"
        "ldur x8, [x29, #-0x20]\n"
        "ldur x9, [x29, #-0x28]\n"
        "subs x8, x8, x9\n"
        "b.ls 5f\n"
        "b 4f\n"
        "4: ldur x8, [x29, #-0x20]\n"
        "ldur x9, [x29, #-0x28]\n"
        "subs x8, x8, x9\n"
        "b 6f\n"
        "5: mov x8, xzr\n"
        "b 6f\n"
        "6: ldr x9, [sp, #0x28]\n"
        "subs x9, x9, #0x6\n"
        "lsr x8, x8, x9\n"
        "str w8, [sp, #0x1c]\n"
        "b 7f\n"
        "7: b 8f\n"
        "8: ldr w8, [sp, #0x1c]\n"
        "mov w9, #0x1\n"
        "lsl x8, x9, x8\n"
        "subs x8, x8, #0x1\n"
        "mvn x8, x8\n"
        "str x8, [sp, #0x10]\n"
        "ldr x8, [sp, #0x20]\n"
        "ldr x9, [sp, #0x10]\n"
        "and x8, x8, x9\n"
        "str x8, [sp, #0x8]\n"
        "ldr x8, [sp, #0x8]\n"
        "cbnz x8, 18f\n"
        "b 9f\n"
        // x8 was zero path
        "9: ldr x8, [sp, #0x20]\n"
        "cbnz x8, 11f\n"
        "b 10f\n"
        "10: ldur x8, [x29, #-0x18]\n"
        "ldr x8, [x8]\n"
        "stur x8, [x29, #-0x8]\n"
        "b 40f\n"
        "11: ldur x8, [x29, #-0x28]\n"
        "ldr x9, [sp, #0x28]\n"
        "mov w10, #0x1\n"
        "lsl x9, x10, x9\n"
        "add x8, x8, x9\n"
        "str x8, [sp]\n"
        "b 12f\n"
        "12: b 13f\n"
        "13: b 14f\n"
        "14: b 15f\n"
        "15: ldr x8, [sp]\n"
        "ldur x9, [x29, #-0x18]\n"
        "ldr x9, [x9]\n"
        "subs x8, x8, x9\n"
        "b.cc 17f\n"
        "b 16f\n"
        "16: ldur x8, [x29, #-0x18]\n"
        "ldr x8, [x8]\n"
        "stur x8, [x29, #-0x8]\n"
        "b 40f\n"
        "17: ldur x0, [x29, #-0x10]\n"
        "ldur x1, [x29, #-0x18]\n"
        "ldr x2, [sp]\n"
        "bl FUN_7103942120\n"
        "stur x0, [x29, #-0x8]\n"
        "b 40f\n"
        // x8 was nonzero path (found bit)
        "18: ldr x0, [sp, #0x8]\n"
        "bl FUN_710393dd80\n"
        "subs w8, w0, #0x1\n"
        "ldr x9, [sp, #0x28]\n"
        "subs x9, x9, #0x6\n"
        "lsl x8, x8, x9\n"
        "ldur x9, [x29, #-0x28]\n"
        "add x8, x9, x8\n"
        "stur x8, [x29, #-0x28]\n"
        "b 2b\n"
        // loop exit
        "30: b 31f\n"
        "31: b 32f\n"
        "32: b 33f\n"
        "33: b 34f\n"
        "34: ldur x8, [x29, #-0x28]\n"
        "stur x8, [x29, #-0x8]\n"
        "b 40f\n"
        // function exit
        "40: ldur x0, [x29, #-0x8]\n"
        "ldp x29, x30, [sp, #0x60]\n"
        "add sp, sp, #0x70\n"
        "ret\n"
    );
}

#endif // MATCHING_HACK_NX_CLANG
