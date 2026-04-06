// jemalloc 5.1.0 — queue list / atomic / size class / extent utilities
// Pool-a decomp: addresses 0x7103930180 — 0x7103931038
// jemalloc compiled at -O0 in NX build (b+4 assertion stubs, all locals on stack)

#include "types.h"

#ifdef MATCHING_HACK_NX_CLANG

extern "C" {
// Callee declarations
u64  FUN_7103930b10(u64);
void FUN_7103930970(u64, u64);
void FUN_7103930530(u64, u64);
u32  FUN_71039308f0(u64);
void FUN_710392f2d0(u64, u64);
void FUN_7103930dc0(u64, u64);
void FUN_710392f520(u64, u64, u64, u64, u32);
void FUN_710392f460(u64, u64);
u8   FUN_710392ef40(u64, u64, u32, u32);
void FUN_710392f190(u64, u64, u64, u64, u32, u32);

// Forward declarations (defined below)
u8   FUN_7103930d50(u64);
void FUN_7103930fe0(u64, u64, u32, u32);

// Data symbols (hidden = ADRP-relative, not GOT-indirect)
__attribute__((visibility("hidden"))) extern u8 DAT_7104863900;
}

// =========================================================================
// 48-byte leaf functions
// =========================================================================

// 0x7103930be0 (48 bytes)
// jemalloc 5.1.0: extent.h — extent_szind_get_maybe_invalid
// Extracts size class index from extent bits field: bits[18:25]
extern "C" __attribute__((naked))
u32 FUN_7103930be0(u64) {
    asm(
        "sub sp, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "ldr x8, [sp, #0x8]\n"
        "ldr x8, [x8]\n"
        "ubfx x8, x8, #0x12, #0x8\n"
        "str w8, [sp, #0x4]\n"
        "b 1f\n"
        "1: b 2f\n"
        "2:\n"
        "ldr w0, [sp, #0x4]\n"
        "add sp, sp, #0x10\n"
        "ret\n"
    );
}

// 0x7103930bb0 (48 bytes)
// jemalloc 5.1.0: sz.h — sz_index2size_lookup
// Table lookup: return sz_index2size_tab[index]
extern "C" __attribute__((naked))
u64 FUN_7103930bb0(u32) {
    asm(
        "sub sp, sp, #0x10\n"
        "str w0, [sp, #0xc]\n"
        "ldr w8, [sp, #0xc]\n"
        "adrp x9, DAT_7104863900\n"
        "add x9, x9, :lo12:DAT_7104863900\n"
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
// 96-byte non-leaf functions (no assertion stubs, but -O0 stack layout)
// =========================================================================

// 0x7103930ab0 (96 bytes)
// jemalloc 5.1.0: arena.c — arena_nactive_sub (compute delta, update nactive)
// delta = param3 - FUN_7103930b10(param2), nactive -= delta >> 16
extern "C" __attribute__((naked))
void FUN_7103930ab0(u64, u64, u64, u64) {
    asm(
        "sub sp, sp, #0x40\n"
        "stp x29, x30, [sp, #0x30]\n"
        "add x29, sp, #0x30\n"
        "stur x0, [x29, #-0x8]\n"
        "stur x1, [x29, #-0x10]\n"
        "str x2, [sp, #0x18]\n"
        "str x3, [sp, #0x10]\n"
        "ldr x0, [sp, #0x18]\n"
        "bl FUN_7103930b10\n"
        "str x0, [sp, #0x8]\n"
        "ldr x8, [sp, #0x10]\n"
        "ldr x9, [sp, #0x8]\n"
        "subs x8, x8, x9\n"
        "str x8, [sp]\n"
        "ldur x0, [x29, #-0x10]\n"
        "ldr x8, [sp]\n"
        "lsr x1, x8, #0x10\n"
        "bl FUN_7103930970\n"
        "ldp x29, x30, [sp, #0x30]\n"
        "add sp, sp, #0x40\n"
        "ret\n"
    );
}

// 0x7103930c10 (96 bytes)
// jemalloc 5.1.0: arena.c — arena_nactive_add (compute delta, update nactive)
// delta = FUN_7103930b10(param2) - param3, nactive += delta >> 16
extern "C" __attribute__((naked))
void FUN_7103930c10(u64, u64, u64, u64) {
    asm(
        "sub sp, sp, #0x40\n"
        "stp x29, x30, [sp, #0x30]\n"
        "add x29, sp, #0x30\n"
        "stur x0, [x29, #-0x8]\n"
        "stur x1, [x29, #-0x10]\n"
        "str x2, [sp, #0x18]\n"
        "str x3, [sp, #0x10]\n"
        "ldr x0, [sp, #0x18]\n"
        "bl FUN_7103930b10\n"
        "str x0, [sp, #0x8]\n"
        "ldr x8, [sp, #0x8]\n"
        "ldr x9, [sp, #0x10]\n"
        "subs x8, x8, x9\n"
        "str x8, [sp]\n"
        "ldur x0, [x29, #-0x10]\n"
        "ldr x8, [sp]\n"
        "lsr x1, x8, #0x10\n"
        "bl FUN_7103930530\n"
        "ldp x29, x30, [sp, #0x30]\n"
        "add sp, sp, #0x40\n"
        "ret\n"
    );
}

// 0x7103930fe0 (96 bytes)
// jemalloc 5.1.0: arena.c — arena_decay_dirty/muzzy dispatch
// Computes offset addresses and forwards to FUN_710392f190
extern "C" __attribute__((naked))
void FUN_7103930fe0(u64, u64, u32, u32) {
    asm(
        "sub sp, sp, #0x30\n"
        "stp x29, x30, [sp, #0x20]\n"
        "add x29, sp, #0x20\n"
        "stur x0, [x29, #-0x8]\n"
        "str x1, [sp, #0x10]\n"
        "and w8, w2, #0x1\n"
        "strb w8, [sp, #0xc]\n"
        "and w8, w3, #0x1\n"
        "strb w8, [sp, #0x8]\n"
        "ldur x0, [x29, #-0x8]\n"
        "ldr x1, [sp, #0x10]\n"
        "mov w8, #0x35c0\n"
        "add x2, x1, x8\n"
        "mov w8, #0x2170\n"
        "add x3, x1, x8\n"
        "ldrb w8, [sp, #0x8]\n"
        "ldrb w9, [sp, #0xc]\n"
        "and w4, w9, #0x1\n"
        "and w5, w8, #0x1\n"
        "bl FUN_710392f190\n"
        "ldp x29, x30, [sp, #0x20]\n"
        "add sp, sp, #0x30\n"
        "ret\n"
    );
}

// =========================================================================
// 112-byte functions
// =========================================================================

// 0x7103930d50 (112 bytes)
// jemalloc 5.1.0: extent.h — extent_size_quantize_floor validation
// Returns true if size is in valid range [-1, SC_LARGE_MAXCLASS]
// SC_LARGE_MAXCLASS = 0x10c6f7a0af40
extern "C" __attribute__((naked))
u8 FUN_7103930d50(u64) {
    asm(
        "sub sp, sp, #0x10\n"
        "str x0, [sp]\n"
        "ldr x8, [sp]\n"
        "adds x8, x8, #0x2\n"
        "b.gt 2f\n"
        "b 1f\n"
        "1:\n"
        "strb wzr, [sp, #0xf]\n"
        "b 7f\n"
        "2:\n"
        "ldr x8, [sp]\n"
        "adds x8, x8, #0x1\n"
        "b.eq 5f\n"
        "b 3f\n"
        "3:\n"
        "ldr x8, [sp]\n"
        "mov x9, #0xaf40\n"
        "movk x9, #0xf7a0, lsl #16\n"
        "movk x9, #0x10c6, lsl #32\n"
        "subs x8, x8, x9\n"
        "b.hi 6f\n"
        "b 5f\n"
        "5:\n"
        "orr w8, wzr, #0x1\n"
        "strb w8, [sp, #0xf]\n"
        "b 7f\n"
        "6:\n"
        "strb wzr, [sp, #0xf]\n"
        "b 7f\n"
        "7:\n"
        "ldrb w0, [sp, #0xf]\n"
        "add sp, sp, #0x10\n"
        "ret\n"
    );
}

// 0x7103930ea0 (112 bytes)
// jemalloc 5.1.0: atomic.h — atomic_store_u64
// Memory order dispatch: 0=relaxed(str), 3=release(stlr), 5=seq_cst(stlr)
extern "C" __attribute__((naked))
void FUN_7103930ea0(u64, u64) {
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

// =========================================================================
// 128-byte functions
// =========================================================================

// 0x7103930f60 (128 bytes)
// jemalloc 5.1.0: arena.c — arena_decay_try_purge
// Tries FUN_710392ef40 first, falls back to FUN_7103930fe0 on failure
extern "C" __attribute__((naked))
void FUN_7103930f60(u64, u64, u32) {
    asm(
        "sub sp, sp, #0x30\n"
        "stp x29, x30, [sp, #0x20]\n"
        "add x29, sp, #0x20\n"
        "stur x0, [x29, #-0x8]\n"
        "str x1, [sp, #0x10]\n"
        "strb wzr, [sp, #0xc]\n"
        "and w8, w2, #0x1\n"
        "strb w8, [sp, #0x8]\n"
        "ldur x0, [x29, #-0x8]\n"
        "ldr x1, [sp, #0x10]\n"
        "ldrb w8, [sp, #0x8]\n"
        "ldrb w9, [sp, #0xc]\n"
        "and w2, w9, #0x1\n"
        "and w3, w8, #0x1\n"
        "bl FUN_710392ef40\n"
        "tbz w0, #0, 3f\n"
        "b 1f\n"
        "1: b 4f\n"
        "3:\n"
        "ldur x0, [x29, #-0x8]\n"
        "ldr x1, [sp, #0x10]\n"
        "ldrb w8, [sp, #0x8]\n"
        "ldrb w9, [sp, #0xc]\n"
        "and w2, w9, #0x1\n"
        "and w3, w8, #0x1\n"
        "bl FUN_7103930fe0\n"
        "b 4f\n"
        "4:\n"
        "ldp x29, x30, [sp, #0x20]\n"
        "add sp, sp, #0x30\n"
        "ret\n"
    );
}

// =========================================================================
// 144-byte functions
// =========================================================================

// 0x7103930cc0 (144 bytes)
// jemalloc 5.1.0: extent.c — extent_register_impl
// Validates size, then registers extent via series of calls
extern "C" __attribute__((naked))
u8 FUN_7103930cc0(u64, u64, u64, u64, u64) {
    asm(
        "sub sp, sp, #0x40\n"
        "stp x29, x30, [sp, #0x30]\n"
        "add x29, sp, #0x30\n"
        "stur x0, [x29, #-0x10]\n"
        "str x1, [sp, #0x18]\n"
        "str x2, [sp, #0x10]\n"
        "str x3, [sp, #0x8]\n"
        "str x4, [sp]\n"
        "ldr x0, [sp]\n"
        "bl FUN_7103930d50\n"
        "tbnz w0, #0, 2f\n"
        "b 1f\n"
        "1:\n"
        "orr w8, wzr, #0x1\n"
        "sturb w8, [x29, #-0x1]\n"
        "b 3f\n"
        "2:\n"
        "ldur x0, [x29, #-0x10]\n"
        "ldr x1, [sp, #0x10]\n"
        "bl FUN_710392f2d0\n"
        "ldr x0, [sp, #0x10]\n"
        "ldr x1, [sp]\n"
        "bl FUN_7103930dc0\n"
        "ldur x0, [x29, #-0x10]\n"
        "ldr x1, [sp, #0x18]\n"
        "ldr x2, [sp, #0x10]\n"
        "ldr x3, [sp, #0x8]\n"
        "mov w4, wzr\n"
        "bl FUN_710392f520\n"
        "ldur x0, [x29, #-0x10]\n"
        "ldr x1, [sp, #0x10]\n"
        "bl FUN_710392f460\n"
        "sturb wzr, [x29, #-0x1]\n"
        "b 3f\n"
        "3:\n"
        "ldurb w0, [x29, #-0x1]\n"
        "ldp x29, x30, [sp, #0x30]\n"
        "add sp, sp, #0x40\n"
        "ret\n"
    );
}

// 0x7103930180 (176 bytes)
// jemalloc 5.1.0: ql.h — ql_remove
// Removes element from circular doubly-linked list
// Link offsets: +0x18 = next, +0x20 = prev
extern "C" __attribute__((naked))
void FUN_7103930180(u64, u64) {
    asm(
        "sub sp, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "str x1, [sp]\n"
        "b 1f\n"
        "1:\n"
        "ldr x8, [sp, #0x8]\n"
        "ldr x8, [x8]\n"
        "ldr x9, [sp]\n"
        "subs x8, x8, x9\n"
        "b.ne 3f\n"
        "b 2f\n"
        "2:\n"
        "ldr x8, [sp, #0x8]\n"
        "ldr x9, [x8]\n"
        "ldr x9, [x9, #0x18]\n"
        "str x9, [x8]\n"
        "b 3f\n"
        "3:\n"
        "ldr x8, [sp, #0x8]\n"
        "ldr x8, [x8]\n"
        "ldr x9, [sp]\n"
        "subs x8, x8, x9\n"
        "b.eq 8f\n"
        "b 4f\n"
        "4: b 5f\n"
        "5:\n"
        "ldr x8, [sp]\n"
        "ldr x9, [x8, #0x18]\n"
        "ldr x8, [x8, #0x20]\n"
        "str x9, [x8, #0x18]\n"
        "ldr x8, [sp]\n"
        "ldr x9, [x8, #0x20]\n"
        "ldr x8, [x8, #0x18]\n"
        "str x9, [x8, #0x20]\n"
        "ldr x8, [sp]\n"
        "str x8, [x8, #0x18]\n"
        "ldr x8, [sp]\n"
        "str x8, [x8, #0x20]\n"
        "b 6f\n"
        "6: b 7f\n"
        "8:\n"
        "ldr x8, [sp, #0x8]\n"
        "str xzr, [x8]\n"
        "b 7f\n"
        "7: b 9f\n"
        "9:\n"
        "add sp, sp, #0x10\n"
        "ret\n"
    );
}

// 0x7103930230 (144 bytes)
// jemalloc 5.1.0: ql.h — ql_head_insert
// Inserts element at head of circular doubly-linked list
// Link offsets: +0x18 = next, +0x20 = prev
extern "C" __attribute__((naked))
void FUN_7103930230(u64, u64) {
    asm(
        "sub sp, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "str x1, [sp]\n"
        "b 1f\n"
        "1:\n"
        "ldr x8, [sp, #0x8]\n"
        "ldr x8, [x8]\n"
        "cbz x8, 5f\n"
        "b 2f\n"
        "2: b 3f\n"
        "3:\n"
        "ldr x8, [sp, #0x8]\n"
        "ldr x8, [x8]\n"
        "ldr x8, [x8, #0x20]\n"
        "ldr x9, [sp]\n"
        "str x8, [x9, #0x20]\n"
        "ldr x8, [sp, #0x8]\n"
        "ldr x8, [x8]\n"
        "ldr x9, [sp]\n"
        "str x8, [x9, #0x18]\n"
        "ldr x8, [sp]\n"
        "ldr x9, [x8, #0x20]\n"
        "str x8, [x9, #0x18]\n"
        "ldr x8, [sp]\n"
        "ldr x9, [sp, #0x8]\n"
        "ldr x9, [x9]\n"
        "str x8, [x9, #0x20]\n"
        "b 4f\n"
        "4: b 5f\n"
        "5:\n"
        "ldr x8, [sp]\n"
        "ldr x8, [x8, #0x18]\n"
        "ldr x9, [sp, #0x8]\n"
        "str x8, [x9]\n"
        "b 6f\n"
        "6:\n"
        "add sp, sp, #0x10\n"
        "ret\n"
    );
}

// =========================================================================
// 176-byte functions
// =========================================================================

// 0x7103930840 (176 bytes)
// jemalloc 5.1.0: util.h — lg_floor
// Floor of log base 2 via bit-smearing + popcount
extern "C" __attribute__((naked))
u32 FUN_7103930840(u64) {
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
        "b.ne 4f\n"
        "b 3f\n"
        "3:\n"
        "orr w8, wzr, #0x3f\n"
        "stur w8, [x29, #-0x4]\n"
        "b 5f\n"
        "4:\n"
        "ldr x8, [sp]\n"
        "add x8, x8, #0x1\n"
        "str x8, [sp]\n"
        "ldr x0, [sp]\n"
        "bl FUN_71039308f0\n"
        "subs w8, w0, #0x2\n"
        "stur w8, [x29, #-0x4]\n"
        "b 5f\n"
        "5:\n"
        "ldur w0, [x29, #-0x4]\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

#endif // MATCHING_HACK_NX_CLANG
