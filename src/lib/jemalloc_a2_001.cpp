// jemalloc 5.1.0 — arena/extent/rtree wrapper and utility functions
// Pool-a decomp: addresses 0x71039278b0 — 0x7103946140
// NOTE: jemalloc was compiled with -O0 equivalent in NX build
// All functions require naked asm due to -O0 branch patterns (b+4 stubs)

#include "types.h"

#ifdef MATCHING_HACK_NX_CLANG

// External function declarations (C linkage for asm bl targets)
extern "C" {
void FUN_7103929a70(void);
void FUN_7103927ac0(u64);
void FUN_7103927ae0(u64);
void FUN_7103929790(u64);
void FUN_710392f140(u64);
void FUN_71039322d0(u64, u32);
void FUN_7103930230(u64, u64);
void FUN_710392f460(u64, u64);
void FUN_7103931450(u64, u64, u64);
void FUN_710392f2d0(u64, u64);
void FUN_7103939690(u64);
void FUN_7103933680(u64);
void FUN_7103933630(u64);
void FUN_7103933f00(u64);
void FUN_7103933f40(u64);
void FUN_7103933ed0(u64);
void FUN_710395ae10(u64, u64);
void FUN_71039316d0(u64, u32);
void FUN_71039302c0(u64);
void FUN_71039302e0(u64);
void FUN_7103931350(void);
void FUN_7103958840(void);
void FUN_7103931ba0(u64);
void FUN_7103932450(u64);
void FUN_71039324a0(u64);
void FUN_71039336e0(u64);
void FUN_7103933730(u64);
void FUN_7103933780(u64);
void FUN_71039337d0(u64);
void FUN_7103942360(u64);
u8   FUN_7103931570(u64);
void abort(void);

// Data symbols (hidden = ADRP-relative, not GOT-indirect)
__attribute__((visibility("hidden"))) extern u32 DAT_71052934c0;
__attribute__((visibility("hidden"))) extern u32 DAT_7106d424a4;
__attribute__((visibility("hidden"))) extern u8  DAT_7106d42580;
}

// =========================================================================
// 48-byte wrapper functions
// jemalloc 5.1.0: arena.h / extent.h — assertion-guarded forwarding wrappers
// Pattern: save x0, b+4, b+4 (assertion stub), load x0, bl callee, ret
// =========================================================================

// 0x7103931b70 (48 bytes) — forwards to FUN_7103931ba0 (field +0x28)
// jemalloc 5.1.0: arena.h — arena_get_offset wrapper
extern "C" __attribute__((naked))
void FUN_7103931b70(u64) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "b 1f\n"
        "1: b 2f\n"
        "2:\n"
        "ldr x0, [sp, #0x8]\n"
        "bl FUN_7103931ba0\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// 0x7103932420 (48 bytes) — forwards to FUN_7103932450 (field +4)
// jemalloc 5.1.0: extent.h — extent accessor wrapper
extern "C" __attribute__((naked))
void FUN_7103932420(u64) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "b 1f\n"
        "1: b 2f\n"
        "2:\n"
        "ldr x0, [sp, #0x8]\n"
        "bl FUN_7103932450\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// 0x7103932470 (48 bytes) — forwards to FUN_71039324a0 (field +0x1b8)
// jemalloc 5.1.0: extent.h — extent accessor wrapper
extern "C" __attribute__((naked))
void FUN_7103932470(u64) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "b 1f\n"
        "1: b 2f\n"
        "2:\n"
        "ldr x0, [sp, #0x8]\n"
        "bl FUN_71039324a0\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// 0x71039336b0 (48 bytes) — forwards to FUN_71039336e0 (increment +1)
// jemalloc 5.1.0: rtree.h — rtree accessor wrapper
extern "C" __attribute__((naked))
void FUN_71039336b0(u64) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "b 1f\n"
        "1: b 2f\n"
        "2:\n"
        "ldr x0, [sp, #0x8]\n"
        "bl FUN_71039336e0\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// 0x7103933700 (48 bytes) — forwards to FUN_7103933730 (field +0x1b0)
// jemalloc 5.1.0: rtree.h — rtree accessor wrapper
extern "C" __attribute__((naked))
void FUN_7103933700(u64) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "b 1f\n"
        "1: b 2f\n"
        "2:\n"
        "ldr x0, [sp, #0x8]\n"
        "bl FUN_7103933730\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// 0x7103933750 (48 bytes) — forwards to FUN_7103933780 (field +0x1a8)
// jemalloc 5.1.0: rtree.h — rtree accessor wrapper
extern "C" __attribute__((naked))
void FUN_7103933750(u64) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "b 1f\n"
        "1: b 2f\n"
        "2:\n"
        "ldr x0, [sp, #0x8]\n"
        "bl FUN_7103933780\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// 0x71039337a0 (48 bytes) — forwards to FUN_71039337d0 (increment +3)
// jemalloc 5.1.0: rtree.h — rtree accessor wrapper
extern "C" __attribute__((naked))
void FUN_71039337a0(u64) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "b 1f\n"
        "1: b 2f\n"
        "2:\n"
        "ldr x0, [sp, #0x8]\n"
        "bl FUN_71039337d0\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// 0x7103942330 (48 bytes) — forwards to FUN_7103942360 (field +0x28)
// jemalloc 5.1.0: arena.h — arena_get_offset wrapper (duplicate pattern)
extern "C" __attribute__((naked))
void FUN_7103942330(u64) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "b 1f\n"
        "1: b 2f\n"
        "2:\n"
        "ldr x0, [sp, #0x8]\n"
        "bl FUN_7103942360\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 64-byte functions
// =========================================================================

// 0x7103931570 (64 bytes)
// jemalloc 5.1.0: arena.c — arena_ind_valid: return arena_ind < narenas_total
extern "C" __attribute__((naked))
u8 FUN_7103931570(u64) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "b 1f\n"
        "1: b 2f\n"
        "2:\n"
        "ldr x0, [sp, #0x8]\n"
        "bl FUN_710392f140\n"
        "adrp x8, DAT_7106d424a4\n"
        "ldr w8, [x8, :lo12:DAT_7106d424a4]\n"
        "subs w8, w0, w8\n"
        "cset w0, cc\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 80-byte functions
// =========================================================================

// 0x71039278b0 (80 bytes)
// jemalloc 5.1.0: jemalloc.c — percpu arena check
// if (opt_percpu_arena == percpu_arena_percpu) return arenas_tdata_cleanup(0) & 1
extern "C" __attribute__((naked))
u8 FUN_71039278b0(void) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "adrp x8, DAT_71052934c0\n"
        "ldr w8, [x8, :lo12:DAT_71052934c0]\n"
        "subs w8, w8, #0x3\n"
        "b.ne 0f\n"
        "b 1f\n"
        "1:\n"
        "bl FUN_7103929a70\n"
        "and w8, w0, #0x1\n"
        "sturb w8, [x29, #-0x1]\n"
        "b 2f\n"
        "0:\n"
        "sturb wzr, [x29, #-0x1]\n"
        "b 2f\n"
        "2:\n"
        "ldurb w0, [x29, #-0x1]\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// 0x71039328b0 (80 bytes)
// jemalloc 5.1.0: arena.c — arena extent list wrapper with null check
extern "C" __attribute__((naked))
u64 FUN_71039328b0(u64) {
    asm(
        "sub sp, sp, #0x30\n"
        "stp x29, x30, [sp, #0x20]\n"
        "add x29, sp, #0x20\n"
        "str x0, [sp, #0x10]\n"
        "ldr x8, [sp, #0x10]\n"
        "add x0, x8, #0xa0\n"
        "bl FUN_7103939690\n"
        "str x0, [sp, #0x8]\n"
        "ldr x8, [sp, #0x8]\n"
        "cbnz x8, 1f\n"
        "b 0f\n"
        "0:\n"
        "stur xzr, [x29, #-0x8]\n"
        "b 2f\n"
        "1:\n"
        "ldr x8, [sp, #0x8]\n"
        "stur x8, [x29, #-0x8]\n"
        "b 2f\n"
        "2:\n"
        "ldur x0, [x29, #-0x8]\n"
        "ldp x29, x30, [sp, #0x20]\n"
        "add sp, sp, #0x30\n"
        "ret\n"
    );
}

// 0x7103933380 (80 bytes)
// jemalloc 5.1.0: rtree.h — rtree_leaf_elm_bits_read, return bool
extern "C" __attribute__((naked))
u8 FUN_7103933380(u64) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp]\n"
        "ldr x0, [sp]\n"
        "bl FUN_7103933680\n"
        "tbz w0, #0, 0f\n"
        "b 1f\n"
        "1: b 2f\n"
        "2: b 3f\n"
        "3:\n"
        "mov w8, #0x1\n"
        "sturb w8, [x29, #-0x1]\n"
        "b 4f\n"
        "0:\n"
        "sturb wzr, [x29, #-0x1]\n"
        "b 4f\n"
        "4:\n"
        "ldurb w0, [x29, #-0x1]\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// 0x7103933e80 (80 bytes)
// jemalloc 5.1.0: rtree.h — rtree conditional decommit
extern "C" __attribute__((naked))
void FUN_7103933e80(u64, u64) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "str x1, [sp]\n"
        "ldr x8, [sp]\n"
        "add x0, x8, #0x8\n"
        "bl FUN_7103933ed0\n"
        "tbz w0, #0, 0f\n"
        "b 1f\n"
        "1:\n"
        "ldr x0, [sp, #0x8]\n"
        "ldr x1, [sp]\n"
        "bl FUN_710395ae10\n"
        "b 0f\n"
        "0:\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 96-byte functions
// =========================================================================

// 0x7103927b30 (96 bytes)
// jemalloc 5.1.0: jemalloc.c — arena_tdata_get_hard lookup
extern "C" __attribute__((naked))
u64 FUN_7103927b30(u64) {
    asm(
        "sub sp, sp, #0x30\n"
        "stp x29, x30, [sp, #0x20]\n"
        "add x29, sp, #0x20\n"
        "str x0, [sp, #0x10]\n"
        "ldr x0, [sp, #0x10]\n"
        "bl FUN_7103927ac0\n"
        "tbz w0, #0, 1f\n"
        "b 0f\n"
        "0:\n"
        "stur xzr, [x29, #-0x8]\n"
        "b 2f\n"
        "1:\n"
        "ldr x0, [sp, #0x10]\n"
        "bl FUN_7103927ae0\n"
        "str x0, [sp, #0x8]\n"
        "ldr x0, [sp, #0x8]\n"
        "bl FUN_7103929790\n"
        "stur x0, [x29, #-0x8]\n"
        "b 2f\n"
        "2:\n"
        "ldur x0, [x29, #-0x8]\n"
        "ldp x29, x30, [sp, #0x20]\n"
        "add sp, sp, #0x30\n"
        "ret\n"
    );
}

// 0x71039321e0 (96 bytes)
// jemalloc 5.1.0: arena.c — arena_extent_alloc wrapper with null check
extern "C" __attribute__((naked))
u64 FUN_71039321e0(u64, u32) {
    asm(
        "sub sp, sp, #0x30\n"
        "stp x29, x30, [sp, #0x20]\n"
        "add x29, sp, #0x20\n"
        "str x0, [sp, #0x10]\n"
        "str w1, [sp, #0xc]\n"
        "ldr x0, [sp, #0x10]\n"
        "ldr w1, [sp, #0xc]\n"
        "bl FUN_71039322d0\n"
        "str x0, [sp]\n"
        "ldr x8, [sp]\n"
        "cbnz x8, 1f\n"
        "b 0f\n"
        "0:\n"
        "stur xzr, [x29, #-0x8]\n"
        "b 2f\n"
        "1:\n"
        "ldr x8, [sp]\n"
        "stur x8, [x29, #-0x8]\n"
        "b 2f\n"
        "2:\n"
        "ldur x0, [x29, #-0x8]\n"
        "ldp x29, x30, [sp, #0x20]\n"
        "add sp, sp, #0x30\n"
        "ret\n"
    );
}

// 0x71039324c0 (96 bytes)
// jemalloc 5.1.0: arena.c — conditional extent list append
extern "C" __attribute__((naked))
void FUN_71039324c0(u64, u64, u64) {
    asm(
        "sub sp, sp, #0x30\n"
        "stp x29, x30, [sp, #0x20]\n"
        "add x29, sp, #0x20\n"
        "stur x0, [x29, #-0x8]\n"
        "str x1, [sp, #0x10]\n"
        "str x2, [sp, #0x8]\n"
        "b 1f\n"
        "1: b 2f\n"
        "2:\n"
        "ldur x0, [x29, #-0x8]\n"
        "bl FUN_7103931570\n"
        "tbz w0, #0, 3f\n"
        "b 4f\n"
        "4:\n"
        "b 5f\n"
        "3:\n"
        "ldr x8, [sp, #0x10]\n"
        "add x0, x8, #0xa8\n"
        "ldr x1, [sp, #0x8]\n"
        "bl FUN_7103930230\n"
        "b 5f\n"
        "5:\n"
        "ldp x29, x30, [sp, #0x20]\n"
        "add sp, sp, #0x30\n"
        "ret\n"
    );
}

// 0x7103932600 (96 bytes)
// jemalloc 5.1.0: arena.c — arena lock+op+unlock pattern
extern "C" __attribute__((naked))
void FUN_7103932600(u64, u64, u64, u64) {
    asm(
        "sub sp, sp, #0x30\n"
        "stp x29, x30, [sp, #0x20]\n"
        "add x29, sp, #0x20\n"
        "stur x0, [x29, #-0x8]\n"
        "str x1, [sp, #0x10]\n"
        "str x2, [sp, #0x8]\n"
        "str x3, [sp]\n"
        "b 1f\n"
        "1: b 2f\n"
        "2:\n"
        "ldur x0, [x29, #-0x8]\n"
        "ldr x1, [sp]\n"
        "bl FUN_710392f460\n"
        "ldur x0, [x29, #-0x8]\n"
        "ldr x1, [sp, #0x10]\n"
        "ldr x2, [sp, #0x8]\n"
        "bl FUN_7103931450\n"
        "ldur x0, [x29, #-0x8]\n"
        "ldr x1, [sp]\n"
        "bl FUN_710392f2d0\n"
        "ldp x29, x30, [sp, #0x20]\n"
        "add sp, sp, #0x30\n"
        "ret\n"
    );
}

// 0x71039333d0 (80 bytes)
// jemalloc 5.1.0: rtree.h — rtree_leaf_elm_extent_read
extern "C" __attribute__((naked))
u64 FUN_71039333d0(u64) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp]\n"
        "ldr x0, [sp]\n"
        "bl FUN_7103933380\n"
        "tbnz w0, #0, 1f\n"
        "b 0f\n"
        "0:\n"
        "str xzr, [sp, #0x8]\n"
        "b 2f\n"
        "1:\n"
        "ldr x0, [sp]\n"
        "bl FUN_7103933630\n"
        "str x0, [sp, #0x8]\n"
        "b 2f\n"
        "2:\n"
        "ldr x0, [sp, #0x8]\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// 0x7103933e20 (96 bytes)
// jemalloc 5.1.0: extent.c — extent_alloc dispatch (small vs large)
extern "C" __attribute__((naked))
u64 FUN_7103933e20(u64) {
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
        "bl FUN_7103933f00\n"
        "str x0, [sp, #0x8]\n"
        "b 5f\n"
        "3:\n"
        "ldr x0, [sp]\n"
        "bl FUN_7103933f40\n"
        "str x0, [sp, #0x8]\n"
        "b 5f\n"
        "5:\n"
        "ldr x0, [sp, #0x8]\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// 0x71039346a0 (80 bytes)
// jemalloc 5.1.0: arena.c — arena_bin_index based slab lock
extern "C" __attribute__((naked))
void FUN_71039346a0(u64) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "ldr x8, [sp, #0x8]\n"
        "ldr w8, [x8]\n"
        "and w8, w8, #0xfff\n"
        "str w8, [sp, #0x4]\n"
        "b 1f\n"
        "1: b 2f\n"
        "2:\n"
        "ldr w8, [sp, #0x4]\n"
        "adrp x9, DAT_7106d42580\n"
        "add x9, x9, :lo12:DAT_7106d42580\n"
        "add x0, x9, x8, lsl #3\n"
        "mov w1, #0x2\n"
        "bl FUN_71039316d0\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// 0x7103934770 (96 bytes)
// jemalloc 5.1.0: arena.c — conditional arena operation dispatch
extern "C" __attribute__((naked))
u64 FUN_7103934770(u64, u64) {
    asm(
        "sub sp, sp, #0x30\n"
        "stp x29, x30, [sp, #0x20]\n"
        "add x29, sp, #0x20\n"
        "str x0, [sp, #0x10]\n"
        "str x1, [sp, #0x8]\n"
        "ldr x0, [sp, #0x10]\n"
        "bl FUN_71039302c0\n"
        "tbz w0, #0, 1f\n"
        "b 0f\n"
        "0:\n"
        "ldr x0, [sp, #0x8]\n"
        "bl FUN_7103958840\n"
        "ldr x8, [sp, #0x8]\n"
        "stur x8, [x29, #-0x8]\n"
        "b 2f\n"
        "1:\n"
        "ldr x0, [sp, #0x10]\n"
        "bl FUN_71039302e0\n"
        "bl FUN_7103931350\n"
        "stur x0, [x29, #-0x8]\n"
        "b 2f\n"
        "2:\n"
        "ldur x0, [x29, #-0x8]\n"
        "ldp x29, x30, [sp, #0x20]\n"
        "add sp, sp, #0x30\n"
        "ret\n"
    );
}

// =========================================================================
// Abort stubs — unreachable code paths
// =========================================================================

// 0x7103946110 (48 bytes) — abort with 3 params stored
// jemalloc 5.1.0: unreachable abort stub
extern "C" __attribute__((naked))
void FUN_7103946110(u64, u64, u64) {
    asm(
        "sub sp, sp, #0x30\n"
        "stp x29, x30, [sp, #0x20]\n"
        "add x29, sp, #0x20\n"
        "stur x0, [x29, #-0x8]\n"
        "str x1, [sp, #0x10]\n"
        "str x2, [sp, #0x8]\n"
        "str xzr, [sp]\n"
        "b 1f\n"
        "1:\n"
        "bl abort\n"
    );
}

// 0x7103946140 (32 bytes) — abort with 1 param stored
// jemalloc 5.1.0: unreachable abort stub
extern "C" __attribute__((naked))
void FUN_7103946140(u64) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "b 1f\n"
        "1:\n"
        "bl abort\n"
    );
}

#endif // MATCHING_HACK_NX_CLANG
