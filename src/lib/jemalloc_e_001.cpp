// jemalloc 5.1.0 — extent, rtree, and mutex utilities (pool-e)
// Address range: 0x7103940000-0x7103960000
// NX jemalloc compiled at -O0 — uses naked asm for matching
// jemalloc 5.1.0: extent.c, extent.h, rtree.c, mutex.c, witness.c

#include "types.h"

#ifdef MATCHING_HACK_NX_CLANG

// External callees (C linkage for bl targets)
extern "C" {
void FUN_7103957c40(u64, u64);
u32  FUN_7103945dc0(u64, u64);
void FUN_7103941330(u64, u64, u32);
void FUN_71039515d0(u64, u64);
u64  FUN_7103951470(u64);
void FUN_7103951540(u64, u64);
int  pthread_mutex_unlock(void *);
void FUN_710393ede0(u64, u64);
void FUN_710393dc80(u64, u32);
u64  FUN_7103950670(u64);
}

// External globals (hidden visibility for direct adrp access, not GOT-indirect)
extern "C" {
__attribute__((visibility("hidden"))) extern u8 DAT_7106dd40b4;
}

// =========================================================================
// 0x7103940490 (16 bytes) — returns global byte flag
// jemalloc 5.1.0: jemalloc.c — malloc_initialized or opt_retain
// =========================================================================
extern "C" __attribute__((naked))
u8 FUN_7103940490(void) {
    asm(
        "adrp x8, DAT_7106dd40b4\n"
        "ldrb w0, [x8, :lo12:DAT_7106dd40b4]\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103940800 (32 bytes, leaf) — extract bits [17:16] from extent header
// jemalloc 5.1.0: extent.h — extent_state_get
// =========================================================================
extern "C" __attribute__((naked))
u64 FUN_7103940800(u64 *) {
    asm(
        "sub sp, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "ldr x8, [sp, #0x8]\n"
        "ldr x8, [x8]\n"
        "ubfx x0, x8, #0x10, #0x2\n"
        "add sp, sp, #0x10\n"
        "ret\n"
    );
}

// =========================================================================
// 0x71039506a0 (32 bytes, leaf) — returns param + 3
// jemalloc 5.1.0: witness.c — witness rank offset helper
// =========================================================================
extern "C" __attribute__((naked))
u64 FUN_71039506a0(u64) {
    asm(
        "sub sp, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "ldr x8, [sp, #0x8]\n"
        "add x0, x8, #0x3\n"
        "add sp, sp, #0x10\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103950e00 (32 bytes, leaf) — identity / passthrough
// jemalloc 5.1.0: nstime.c — nstime passthrough
// Two unconditional branches to next instruction = -O0 dead-code artifact
// =========================================================================
extern "C" __attribute__((naked))
u64 FUN_7103950e00(u64) {
    asm(
        "sub sp, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "b 1f\n"
        "1: b 2f\n"
        "2:\n"
        "ldr x0, [sp, #0x8]\n"
        "add sp, sp, #0x10\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103940230 (48 bytes) — wrapper for FUN_7103957c40
// jemalloc 5.1.0: extent.c — extent register / deregister wrapper
// =========================================================================
extern "C" __attribute__((naked))
void FUN_7103940230(u64, u64) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "str x1, [sp]\n"
        "ldr x0, [sp, #0x8]\n"
        "ldr x1, [sp]\n"
        "bl FUN_7103957c40\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103940260 (48 bytes) — call function, return bit 0
// jemalloc 5.1.0: extent.h — extent_committed_get or similar bool check
// =========================================================================
extern "C" __attribute__((naked))
u32 FUN_7103940260(u64, u64) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "str x1, [sp]\n"
        "ldr x0, [sp, #0x8]\n"
        "ldr x1, [sp]\n"
        "bl FUN_7103945dc0\n"
        "and w0, w0, #0x1\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103940b60 (48 bytes, leaf) — set bit 13 in extent header
// jemalloc 5.1.0: extent.h — extent_zeroed_set
// BFM inserts bit 0 of param_2 into bit 13 of *param_1
// =========================================================================
extern "C" __attribute__((naked))
void FUN_7103940b60(u64 *, u8) {
    asm(
        "sub sp, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "and w8, w1, #0x1\n"
        "strb w8, [sp, #0x4]\n"
        "ldr x8, [sp, #0x8]\n"
        "ldr x9, [x8]\n"
        "ldrb w10, [sp, #0x4]\n"
        "and x10, x10, #0x1\n"
        "bfm x9, x10, #51, #0\n"
        "str x9, [x8]\n"
        "add sp, sp, #0x10\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103940f40 (48 bytes) — wrapper: call with 3rd arg = 1
// jemalloc 5.1.0: extent.c — extent_lock (try_lock=true)
// =========================================================================
extern "C" __attribute__((naked))
void FUN_7103940f40(u64, u64) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "str x1, [sp]\n"
        "ldr x0, [sp, #0x8]\n"
        "ldr x1, [sp]\n"
        "orr w2, wzr, #0x1\n"
        "bl FUN_7103941330\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103940f70 (48 bytes) — wrapper: call with 3rd arg = 0
// jemalloc 5.1.0: extent.c — extent_unlock (try_lock=false)
// =========================================================================
extern "C" __attribute__((naked))
void FUN_7103940f70(u64, u64) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "str x1, [sp]\n"
        "ldr x0, [sp, #0x8]\n"
        "ldr x1, [sp]\n"
        "mov w2, wzr\n"
        "bl FUN_7103941330\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103950e20 (48 bytes) — wrapper for FUN_71039515d0
// jemalloc 5.1.0: nstime.c or witness.c — timer/witness wrapper
// =========================================================================
extern "C" __attribute__((naked))
void FUN_7103950e20(u64, u64) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "str x1, [sp]\n"
        "ldr x0, [sp, #0x8]\n"
        "ldr x1, [sp]\n"
        "bl FUN_71039515d0\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103940a20 (64 bytes, leaf) — mask: clear bit 0 and top 16 bits
// jemalloc 5.1.0: extent.h — extent_addr_get
// Computes: param & (0xffffffffffff & ~1) = param & 0xfffffffffffe
// Two-step mask construction is -O0 codegen of inline function
// =========================================================================
extern "C" __attribute__((naked))
u64 FUN_7103940a20(u64) {
    asm(
        "sub sp, sp, #0x20\n"
        "str x0, [sp, #0x18]\n"
        "orr x8, xzr, #0xffffffffffff\n"
        "str x8, [sp, #0x10]\n"
        "orr x8, xzr, #0xfffffffffffffffe\n"
        "str x8, [sp, #0x8]\n"
        "ldr x8, [sp, #0x10]\n"
        "ldr x9, [sp, #0x8]\n"
        "and x8, x8, x9\n"
        "str x8, [sp]\n"
        "ldr x8, [sp, #0x18]\n"
        "ldr x9, [sp]\n"
        "and x0, x8, x9\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103950f90 (64 bytes) — unlock sequence: get tsd, notify, mutex_unlock
// jemalloc 5.1.0: mutex.c — malloc_mutex_unlock
// Calls FUN_7103951470 (tsd_tsdn), FUN_7103951540 (witness_unlock),
//       pthread_mutex_unlock
// =========================================================================
extern "C" __attribute__((naked))
int FUN_7103950f90(u64, u64) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "str x1, [sp]\n"
        "ldr x0, [sp, #0x8]\n"
        "bl FUN_7103951470\n"
        "ldr x8, [sp]\n"
        "add x1, x8, #0x60\n"
        "bl FUN_7103951540\n"
        "ldr x8, [sp]\n"
        "add x0, x8, #0x40\n"
        "bl pthread_mutex_unlock\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 0x71039401e0 (80 bytes) — 7-param wrapper, calls FUN_710393ede0(p2, p4)
// jemalloc 5.1.0: extent.c — extent_purge_lazy/forced callback
// Returns 0 (success)
// =========================================================================
extern "C" __attribute__((naked))
u64 FUN_71039401e0(u64, u64, u64, u64, u64, u8, u32) {
    asm(
        "sub sp, sp, #0x40\n"
        "stp x29, x30, [sp, #0x30]\n"
        "add x29, sp, #0x30\n"
        "stur x0, [x29, #-0x8]\n"
        "stur x1, [x29, #-0x10]\n"
        "str x2, [sp, #0x18]\n"
        "str x3, [sp, #0x10]\n"
        "str x4, [sp, #0x8]\n"
        "and w8, w5, #0x1\n"
        "strb w8, [sp, #0x4]\n"
        "str w6, [sp]\n"
        "ldur x0, [x29, #-0x10]\n"
        "ldr x1, [sp, #0x10]\n"
        "bl FUN_710393ede0\n"
        "mov w0, wzr\n"
        "ldp x29, x30, [sp, #0x30]\n"
        "add sp, sp, #0x40\n"
        "ret\n"
    );
}

// =========================================================================
// 0x71039409d0 (80 bytes) — conditional mode set
// jemalloc 5.1.0: extent.c — rtree_szind_slab_update (set szind mode)
// If (flag & 1) != 0: mode = 0, else mode = 2
// Calls FUN_710393dc80(param3, mode)
// =========================================================================
extern "C" __attribute__((naked))
void FUN_71039409d0(u64, u64, u64, u8) {
    asm(
        "sub sp, sp, #0x30\n"
        "stp x29, x30, [sp, #0x20]\n"
        "add x29, sp, #0x20\n"
        "stur x0, [x29, #-0x8]\n"
        "str x1, [sp, #0x10]\n"
        "str x2, [sp, #0x8]\n"
        "and w8, w3, #0x1\n"
        "strb w8, [sp, #0x4]\n"
        "ldr x0, [sp, #0x8]\n"
        "ldrb w8, [sp, #0x4]\n"
        "ands w8, w8, #0x1\n"
        "orr w8, wzr, #0x2\n"
        "csel w1, wzr, w8, ne\n"
        "bl FUN_710393dc80\n"
        "ldp x29, x30, [sp, #0x20]\n"
        "add sp, sp, #0x30\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103940060 (60 bytes) — 5-param wrapper, calls FUN_7103940230(p2, p3)
// jemalloc 5.1.0: extent.c — extent_commit/decommit wrapper
// =========================================================================
extern "C" __attribute__((naked))
void FUN_7103940060(u64, u64, u64, u8, u32) {
    asm(
        "sub sp, sp, #0x30\n"
        "stp x29, x30, [sp, #0x20]\n"
        "add x29, sp, #0x20\n"
        "stur x0, [x29, #-0x8]\n"
        "str x1, [sp, #0x10]\n"
        "str x2, [sp, #0x8]\n"
        "and w8, w3, #0x1\n"
        "strb w8, [sp, #0x4]\n"
        "str w4, [sp]\n"
        "ldr x0, [sp, #0x10]\n"
        "ldr x1, [sp, #0x8]\n"
        "bl FUN_7103940230\n"
        "ldp x29, x30, [sp, #0x20]\n"
        "add sp, sp, #0x30\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103950370 (40 bytes) — call helper, dereference and return byte
// jemalloc 5.1.0: witness.c — witness_owner_get or similar
// =========================================================================
extern "C" __attribute__((naked))
u8 FUN_7103950370(u64) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "ldr x0, [sp, #0x8]\n"
        "bl FUN_7103950670\n"
        "ldrb w0, [x0]\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

#endif // MATCHING_HACK_NX_CLANG
