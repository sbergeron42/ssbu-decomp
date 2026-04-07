// jemalloc 5.1.0 — extent, rtree, bitmap, and mutex utilities (pool-e, batch 2)
// Address range: continued from jemalloc_e_001.cpp
// NX jemalloc compiled at -O0 — uses naked asm for matching
// jemalloc 5.1.0: extent.c, rtree.c, bitmap.c

#include "types.h"

#ifdef MATCHING_HACK_NX_CLANG

// External callees (C linkage for bl targets)
extern "C" {
// From jemalloc_e_001.o
u8   FUN_7103940490(void);
void FUN_71039409d0(u64, u64, u64, u8);
u64  FUN_7103940a20(u64);

// From other jemalloc TUs
u64  FUN_710393fb50(u64);
u64  FUN_710393fe20(void);
void FUN_710393e2c0(u64, u64);
u64  FUN_710393ca80(u64);
u64  FUN_710393e300(u64);
u32  FUN_710393e390(u64);
void FUN_710393a6f0(u64, u64);
u32  FUN_7103938b10(u64);
u64  FUN_710393c230(u64);
void FUN_710393c170(u64, u64);
u64  FUN_710393f250(u64, u64);
void FUN_7103938830(u64, u64);
void FUN_710393f290(u64, u64);
void FUN_710393e8c0(u64, u64);
void FUN_710393d3d0(u64, u64, u64, u64, u32, u32);
u64  FUN_710393d0c0(u64, u64, u64, u64, u32, u32);
void FUN_71039387c0(u64, u64);
u64  FUN_710393cfe0(u64);
u64  FUN_7103941400(u64, u64, u64, u64, u64, u32, u32, u64);
void FUN_710393de00(u64, u32);
u64  FUN_7103939580(u64);
void FUN_7103941810(u64, u64, u64, u32, u32);
u64  FUN_710393e720(u64);
void FUN_710393e130(u64, u64, u64, u64);
u64  FUN_7103945d20(u64, u64, u64, u64, u64);
}

// External globals (hidden visibility for direct adrp access)
extern "C" {
__attribute__((visibility("hidden"))) extern u8 DAT_7104862118;
__attribute__((visibility("hidden"))) extern u8 DAT_7106dca710;
__attribute__((visibility("hidden"))) extern u8 DAT_7106d4a678;
}

// =========================================================================
// 0x7103940290 (80 bytes) — conditional retained extent allocation
// jemalloc 5.1.0: extent.c — extent_grow_retained
// =========================================================================
extern "C" __attribute__((naked))
u64 FUN_7103940290(void) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "bl FUN_7103940490\n"
        "tbnz w0, #0x0, 1f\n"
        "b 0f\n"
        "0: str xzr, [sp, #0x8]\n"
        "b 2f\n"
        "1: mov w0, wzr\n"
        "bl FUN_710393fb50\n"
        "bl FUN_710393fe20\n"
        "str x0, [sp, #0x8]\n"
        "b 2f\n"
        "2: ldr x0, [sp, #0x8]\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 0x71039402e0 (176 bytes) — 7-param extent alloc wrapper
// jemalloc 5.1.0: extent.c — extent_alloc_retained
// Reads atomic counter at param2+0x1a28, then dispatches to FUN_7103940400
// =========================================================================
extern "C" __attribute__((naked))
u64 FUN_71039402e0(u64, u64, u64, u64, u64, u64, u64) {
    asm(
        "sub sp, sp, #0x90\n"
        "str x25, [sp, #0x40]\n"
        "stp x24, x23, [sp, #0x50]\n"
        "stp x22, x21, [sp, #0x60]\n"
        "stp x20, x19, [sp, #0x70]\n"
        "stp x29, x30, [sp, #0x80]\n"
        "add x29, sp, #0x80\n"
        "stur x0, [x29, #-0x38]\n"
        "str x1, [sp, #0x38]\n"
        "str x2, [sp, #0x30]\n"
        "str x3, [sp, #0x28]\n"
        "str x4, [sp, #0x20]\n"
        "str x5, [sp, #0x18]\n"
        "str x6, [sp, #0x10]\n"
        "ldur x19, [x29, #-0x38]\n"
        "ldr x20, [sp, #0x38]\n"
        "ldr x21, [sp, #0x30]\n"
        "ldr x22, [sp, #0x28]\n"
        "ldr x23, [sp, #0x20]\n"
        "ldr x24, [sp, #0x18]\n"
        "ldr x25, [sp, #0x10]\n"
        "mov w8, #0x1a28\n"
        "add x0, x20, x8\n"
        "bl FUN_7103940390\n"
        "mov w7, w0\n"
        "mov x0, x19\n"
        "mov x1, x20\n"
        "mov x2, x21\n"
        "mov x3, x22\n"
        "mov x4, x23\n"
        "mov x5, x24\n"
        "mov x6, x25\n"
        "bl FUN_7103940400\n"
        "str x0, [sp, #0x8]\n"
        "ldr x0, [sp, #0x8]\n"
        "ldp x29, x30, [sp, #0x80]\n"
        "ldp x20, x19, [sp, #0x70]\n"
        "ldp x22, x21, [sp, #0x60]\n"
        "ldp x24, x23, [sp, #0x50]\n"
        "ldr x25, [sp, #0x40]\n"
        "add sp, sp, #0x90\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103940390 (112 bytes, leaf) — atomic_load switch on memory order
// jemalloc 5.1.0: jemalloc_internal.h — atomic_load_u32
// order=0 means relaxed (plain ldr), order=1/2 means acquire (ldar),
// order=5 means seq_cst (ldar)
// =========================================================================
extern "C" __attribute__((naked))
u32 FUN_7103940390(u64) {
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
        "b 0f\n"
        "0: subs w9, w9, #0x5\n"
        "b.eq 2f\n"
        "b 3f\n"
        "3: ldr w8, [x8]\n"
        "str w8, [sp, #0x4]\n"
        "b 4f\n"
        "1: ldar w8, [x8]\n"
        "str w8, [sp, #0x4]\n"
        "b 4f\n"
        "2: ldar w8, [x8]\n"
        "str w8, [sp, #0x4]\n"
        "b 4f\n"
        "4: ldr w0, [sp, #0x4]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103940400 (144 bytes) — 8-param extent alloc with null check
// jemalloc 5.1.0: extent.c — extent_recycle
// 4 nop branches = -O0 dead-code artifact
// =========================================================================
extern "C" __attribute__((naked))
u64 FUN_7103940400(u64, u64, u64, u64, u64, u64, u64, u32) {
    asm(
        "sub sp, sp, #0x60\n"
        "stp x29, x30, [sp, #0x50]\n"
        "add x29, sp, #0x50\n"
        "stur x0, [x29, #-0x10]\n"
        "stur x1, [x29, #-0x18]\n"
        "stur x2, [x29, #-0x20]\n"
        "str x3, [sp, #0x28]\n"
        "str x4, [sp, #0x20]\n"
        "str x5, [sp, #0x18]\n"
        "str x6, [sp, #0x10]\n"
        "str w7, [sp, #0xc]\n"
        "b 0f\n"
        "0: b 1f\n"
        "1: b 2f\n"
        "2: b 3f\n"
        "3: ldur x0, [x29, #-0x20]\n"
        "ldr x1, [sp, #0x28]\n"
        "ldr x2, [sp, #0x20]\n"
        "ldr x3, [sp, #0x18]\n"
        "ldr x4, [sp, #0x10]\n"
        "bl FUN_7103945d20\n"
        "str x0, [sp]\n"
        "cbz x0, 5f\n"
        "b 4f\n"
        "4: ldr x8, [sp]\n"
        "stur x8, [x29, #-0x8]\n"
        "b 6f\n"
        "5: stur xzr, [x29, #-0x8]\n"
        "b 6f\n"
        "6: ldur x0, [x29, #-0x8]\n"
        "ldp x29, x30, [sp, #0x50]\n"
        "add sp, sp, #0x60\n"
        "ret\n"
    );
}

// =========================================================================
// 0x71039404a0 (240 bytes) — extent deregister + bitmap + counter update
// jemalloc 5.1.0: extent.c — extent_deregister_locked
// =========================================================================
extern "C" __attribute__((naked))
void FUN_71039404a0(u64, u64, u64) {
    asm(
        "sub sp, sp, #0x50\n"
        "stp x29, x30, [sp, #0x40]\n"
        "add x29, sp, #0x40\n"
        "stur x0, [x29, #-0x8]\n"
        "stur x1, [x29, #-0x10]\n"
        "stur x2, [x29, #-0x18]\n"
        "ldur x0, [x29, #-0x8]\n"
        "ldur x1, [x29, #-0x10]\n"
        "bl FUN_710393e2c0\n"
        "b 0f\n"
        "0: b 1f\n"
        "1: ldur x0, [x29, #-0x18]\n"
        "bl FUN_710393ca80\n"
        "str x0, [sp, #0x20]\n"
        "ldr x0, [sp, #0x20]\n"
        "bl FUN_710393e300\n"
        "str x0, [sp, #0x18]\n"
        "ldr x0, [sp, #0x18]\n"
        "bl FUN_710393e390\n"
        "str w0, [sp, #0x14]\n"
        "ldur x8, [x29, #-0x10]\n"
        "ldr w9, [sp, #0x14]\n"
        "add x8, x8, x9, lsl #0x3\n"
        "add x0, x8, #0x98\n"
        "ldur x1, [x29, #-0x18]\n"
        "bl FUN_710393a6f0\n"
        "ldur x8, [x29, #-0x10]\n"
        "ldr w9, [sp, #0x14]\n"
        "add x8, x8, x9, lsl #0x3\n"
        "add x0, x8, #0x98\n"
        "bl FUN_7103938b10\n"
        "tbz w0, #0x0, 3f\n"
        "b 2f\n"
        "2: ldur x8, [x29, #-0x10]\n"
        "add x0, x8, #0x658\n"
        "ldr w1, [sp, #0x14]\n"
        "bl FUN_7103940590\n"
        "b 3f\n"
        "3: ldur x8, [x29, #-0x10]\n"
        "add x0, x8, #0x680\n"
        "ldur x1, [x29, #-0x18]\n"
        "bl FUN_71039406f0\n"
        "ldr x8, [sp, #0x20]\n"
        "lsr x8, x8, #0x10\n"
        "str x8, [sp, #0x8]\n"
        "ldur x8, [x29, #-0x10]\n"
        "add x0, x8, #0x688\n"
        "bl FUN_710393c230\n"
        "str x0, [sp]\n"
        "b 4f\n"
        "4: b 5f\n"
        "5: ldur x8, [x29, #-0x10]\n"
        "add x0, x8, #0x688\n"
        "ldr x8, [sp]\n"
        "ldr x9, [sp, #0x20]\n"
        "subs x1, x8, x9, lsr #0x10\n"
        "bl FUN_710393c170\n"
        "ldp x29, x30, [sp, #0x40]\n"
        "add sp, sp, #0x50\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103940590 (352 bytes, leaf) — bitmap hierarchical unset + propagate
// jemalloc 5.1.0: bitmap.c — bitmap_unset
// Toggles bit in bitmap, propagates up if group becomes zero
// =========================================================================
extern "C" __attribute__((naked))
void FUN_7103940590(u64, u64) {
    asm(
        "sub sp, sp, #0x40\n"
        "str x0, [sp, #0x38]\n"
        "adrp x8, DAT_7104862118\n"
        "add x8, x8, :lo12:DAT_7104862118\n"
        "str x8, [sp, #0x30]\n"
        "str x1, [sp, #0x28]\n"
        "b 0f\n"
        "0: b 1f\n"
        "1: b 2f\n"
        "2: b 3f\n"
        "3: ldr x8, [sp, #0x28]\n"
        "lsr x8, x8, #0x6\n"
        "str x8, [sp, #0x20]\n"
        "ldr x8, [sp, #0x38]\n"
        "ldr x9, [sp, #0x20]\n"
        "add x8, x8, x9, lsl #0x3\n"
        "str x8, [sp, #0x18]\n"
        "ldr x8, [sp, #0x18]\n"
        "ldr x8, [x8]\n"
        "str x8, [sp, #0x10]\n"
        "b 4f\n"
        "4: b 5f\n"
        "5: ldr x8, [sp, #0x28]\n"
        "mov w9, #0x1\n"
        "lsl x8, x9, x8\n"
        "ldr x9, [sp, #0x10]\n"
        "eor x8, x9, x8\n"
        "str x8, [sp, #0x10]\n"
        "ldr x8, [sp, #0x10]\n"
        "ldr x9, [sp, #0x18]\n"
        "str x8, [x9]\n"
        "b 6f\n"
        "6: b 7f\n"
        "7: ldr x8, [sp, #0x10]\n"
        "cbnz x8, 18f\n"
        "b 8f\n"
        "8: mov w8, #0x1\n"
        "str w8, [sp, #0xc]\n"
        "b 9f\n"
        "9: ldr w8, [sp, #0xc]\n"
        "ldr x9, [sp, #0x30]\n"
        "ldr w9, [x9, #0x8]\n"
        "subs w8, w8, w9\n"
        "b.cs 16f\n"
        "b 10f\n"
        "10: ldr x8, [sp, #0x20]\n"
        "str x8, [sp, #0x28]\n"
        "ldr x8, [sp, #0x28]\n"
        "lsr x8, x8, #0x6\n"
        "str x8, [sp, #0x20]\n"
        "ldr x8, [sp, #0x38]\n"
        "ldr x9, [sp, #0x30]\n"
        "ldr w10, [sp, #0xc]\n"
        "add x9, x9, x10, lsl #0x3\n"
        "ldr x9, [x9, #0x10]\n"
        "ldr x10, [sp, #0x20]\n"
        "add x9, x9, x10\n"
        "add x8, x8, x9, lsl #0x3\n"
        "str x8, [sp, #0x18]\n"
        "ldr x8, [sp, #0x18]\n"
        "ldr x8, [x8]\n"
        "str x8, [sp, #0x10]\n"
        "b 11f\n"
        "11: b 12f\n"
        "12: ldr x8, [sp, #0x28]\n"
        "mov w9, #0x1\n"
        "lsl x8, x9, x8\n"
        "ldr x9, [sp, #0x10]\n"
        "eor x8, x9, x8\n"
        "str x8, [sp, #0x10]\n"
        "ldr x8, [sp, #0x10]\n"
        "ldr x9, [sp, #0x18]\n"
        "str x8, [x9]\n"
        "ldr x8, [sp, #0x10]\n"
        "cbz x8, 13f\n"
        "b 14f\n"
        "14: b 17f\n"
        "13: b 15f\n"
        "15: ldr w8, [sp, #0xc]\n"
        "add w8, w8, #0x1\n"
        "str w8, [sp, #0xc]\n"
        "b 9b\n"
        "16: b 17f\n"
        "17: b 18f\n"
        "18: add sp, sp, #0x40\n"
        "ret\n"
    );
}

// =========================================================================
// 0x71039406f0 (176 bytes, leaf) — doubly-linked list remove
// jemalloc 5.1.0: extent.c — extent_list_remove (ql_remove)
// Unlinks node from circular doubly-linked list at +0x18/+0x20
// =========================================================================
extern "C" __attribute__((naked))
void FUN_71039406f0(u64, u64) {
    asm(
        "sub sp, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "str x1, [sp]\n"
        "b 0f\n"
        "0: ldr x8, [sp, #0x8]\n"
        "ldr x8, [x8]\n"
        "ldr x9, [sp]\n"
        "subs x8, x8, x9\n"
        "b.ne 2f\n"
        "b 1f\n"
        "1: ldr x8, [sp, #0x8]\n"
        "ldr x9, [x8]\n"
        "ldr x9, [x9, #0x18]\n"
        "str x9, [x8]\n"
        "b 2f\n"
        "2: ldr x8, [sp, #0x8]\n"
        "ldr x8, [x8]\n"
        "ldr x9, [sp]\n"
        "subs x8, x8, x9\n"
        "b.eq 6f\n"
        "b 3f\n"
        "3: b 4f\n"
        "4: ldr x8, [sp]\n"
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
        "b 5f\n"
        "5: b 7f\n"
        "6: ldr x8, [sp, #0x8]\n"
        "str xzr, [x8]\n"
        "b 7f\n"
        "7: b 8f\n"
        "8: add sp, sp, #0x10\n"
        "ret\n"
    );
}

// =========================================================================
// 0x71039407a0 (96 bytes) — extent heap insert
// jemalloc 5.1.0: extent.c — extent_heap_insert
// Looks up in global rtree, inserts into heap, then removes from rtree
// =========================================================================
extern "C" __attribute__((naked))
void FUN_71039407a0(u64, u64) {
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
// 0x7103940820 (176 bytes) — extent CAS-loop: find, lock, verify, return
// jemalloc 5.1.0: extent.c — extent_lock_from_addr
// Returns 0 on success, 1 on retry needed, 2 on not found
// =========================================================================
extern "C" __attribute__((naked))
u32 FUN_7103940820(u64, u64, u64) {
    asm(
        "sub sp, sp, #0x40\n"
        "stp x29, x30, [sp, #0x30]\n"
        "add x29, sp, #0x30\n"
        "stur x0, [x29, #-0x10]\n"
        "str x1, [sp, #0x18]\n"
        "str x2, [sp, #0x10]\n"
        "ldur x0, [x29, #-0x10]\n"
        "ldr x1, [sp, #0x18]\n"
        "bl FUN_71039408d0\n"
        "str x0, [sp, #0x8]\n"
        "ldr x8, [sp, #0x8]\n"
        "cbnz x8, 1f\n"
        "b 0f\n"
        "0: mov w8, #0x2\n"
        "stur w8, [x29, #-0x4]\n"
        "b 4f\n"
        "1: ldur x0, [x29, #-0x10]\n"
        "ldr x1, [sp, #0x8]\n"
        "bl FUN_7103940930\n"
        "ldur x0, [x29, #-0x10]\n"
        "ldr x1, [sp, #0x18]\n"
        "bl FUN_71039408d0\n"
        "str x0, [sp]\n"
        "ldr x8, [sp, #0x8]\n"
        "ldr x9, [sp]\n"
        "subs x8, x8, x9\n"
        "b.ne 3f\n"
        "b 2f\n"
        "2: ldr x8, [sp, #0x8]\n"
        "ldr x9, [sp, #0x10]\n"
        "str x8, [x9]\n"
        "stur wzr, [x29, #-0x4]\n"
        "b 4f\n"
        "3: ldur x0, [x29, #-0x10]\n"
        "ldr x1, [sp, #0x8]\n"
        "bl FUN_710393e8c0\n"
        "mov w8, #0x1\n"
        "stur w8, [x29, #-0x4]\n"
        "b 4f\n"
        "4: ldur w0, [x29, #-0x4]\n"
        "ldp x29, x30, [sp, #0x30]\n"
        "add sp, sp, #0x40\n"
        "ret\n"
    );
}

// =========================================================================
// 0x71039408d0 (96 bytes) — rtree lookup: get addr from rtree with acquire
// jemalloc 5.1.0: rtree.c — rtree_read_acquire
// Calls rtree_szind_slab_read then extent_addr_get
// =========================================================================
extern "C" __attribute__((naked))
u64 FUN_71039408d0(u64, u64) {
    asm(
        "sub sp, sp, #0x40\n"
        "stp x29, x30, [sp, #0x30]\n"
        "add x29, sp, #0x30\n"
        "stur x0, [x29, #-0x8]\n"
        "adrp x8, DAT_7106d4a678\n"
        "add x8, x8, :lo12:DAT_7106d4a678\n"
        "stur x8, [x29, #-0x10]\n"
        "str x1, [sp, #0x18]\n"
        "mov w8, #0x1\n"
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
// 0x7103940930 (64 bytes) — extent heap remove wrapper
// jemalloc 5.1.0: extent.c — extent_heap_remove (nop branches = -O0)
// =========================================================================
extern "C" __attribute__((naked))
void FUN_7103940930(u64, u64) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "str x1, [sp]\n"
        "b 0f\n"
        "0: b 1f\n"
        "1: ldr x0, [sp, #0x8]\n"
        "ldr x1, [sp]\n"
        "bl FUN_7103940970\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103940970 (96 bytes) — extent heap remove impl
// jemalloc 5.1.0: extent.c — extent_heap_remove_impl
// Uses global rtree at DAT_7106dca710
// =========================================================================
extern "C" __attribute__((naked))
void FUN_7103940970(u64, u64) {
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
// 0x7103940a60 (112 bytes) — extent dealloc wrapper
// jemalloc 5.1.0: extent.c — extent_dalloc_wrapper
// =========================================================================
extern "C" __attribute__((naked))
void FUN_7103940a60(u64, u64, u64) {
    asm(
        "sub sp, sp, #0x40\n"
        "stp x29, x30, [sp, #0x30]\n"
        "add x29, sp, #0x30\n"
        "stur x0, [x29, #-0x8]\n"
        "adrp x8, DAT_7106d4a678\n"
        "add x8, x8, :lo12:DAT_7106d4a678\n"
        "stur x8, [x29, #-0x10]\n"
        "str x1, [sp, #0x18]\n"
        "str x2, [sp, #0x10]\n"
        "ldur x0, [x29, #-0x8]\n"
        "ldur x1, [x29, #-0x10]\n"
        "ldr x2, [sp, #0x18]\n"
        "ldr x3, [sp, #0x10]\n"
        "bl FUN_7103940ad0\n"
        "str x0, [sp, #0x8]\n"
        "b 0f\n"
        "0: b 1f\n"
        "1: ldur x0, [x29, #-0x8]\n"
        "ldur x1, [x29, #-0x10]\n"
        "ldr x2, [sp, #0x8]\n"
        "mov w4, #0xe8\n"
        "mov x3, xzr\n"
        "mov w5, wzr\n"
        "bl FUN_710393d3d0\n"
        "ldp x29, x30, [sp, #0x30]\n"
        "add sp, sp, #0x40\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103940ad0 (144 bytes) — extent alloc with zero-init flag
// jemalloc 5.1.0: extent.c — extent_alloc
// =========================================================================
extern "C" __attribute__((naked))
u64 FUN_7103940ad0(u64, u64, u64, u64) {
    asm(
        "sub sp, sp, #0x50\n"
        "stp x29, x30, [sp, #0x40]\n"
        "add x29, sp, #0x40\n"
        "stur x0, [x29, #-0x10]\n"
        "stur x1, [x29, #-0x18]\n"
        "str x2, [sp, #0x20]\n"
        "str x3, [sp, #0x18]\n"
        "mov w8, #0x1\n"
        "strb w8, [sp, #0x14]\n"
        "ldur x0, [x29, #-0x10]\n"
        "ldur x1, [x29, #-0x18]\n"
        "ldr x2, [sp, #0x20]\n"
        "ldr x3, [sp, #0x18]\n"
        "ldrb w8, [sp, #0x14]\n"
        "and w4, w8, #0x1\n"
        "mov w5, wzr\n"
        "bl FUN_710393d0c0\n"
        "str x0, [sp, #0x8]\n"
        "ldrb w8, [sp, #0x14]\n"
        "tbnz w8, #0x0, 2f\n"
        "b 0f\n"
        "0: ldr x8, [sp, #0x8]\n"
        "cbnz x8, 2f\n"
        "b 1f\n"
        "1: stur xzr, [x29, #-0x8]\n"
        "b 5f\n"
        "2: b 3f\n"
        "3: b 4f\n"
        "4: ldr x8, [sp, #0x8]\n"
        "stur x8, [x29, #-0x8]\n"
        "b 5f\n"
        "5: ldur x0, [x29, #-0x8]\n"
        "ldp x29, x30, [sp, #0x40]\n"
        "add sp, sp, #0x50\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103940b90 (848 bytes) — extent_split_impl
// jemalloc 5.1.0: extent.c — extent_split_impl
// Large function: alignment, head/tail split, bitmap updates
// 8 register params + stack params
// =========================================================================
extern "C" __attribute__((naked))
u32 FUN_7103940b90(u64, u64, u64, u64, u64, u64, u64, u64) {
    asm(
        "sub sp, sp, #0xa0\n"
        "stp x20, x19, [sp, #0x80]\n"
        "stp x29, x30, [sp, #0x90]\n"
        "add x29, sp, #0x90\n"
        "ldrb w8, [x29, #0x48]\n"
        "ldrb w9, [x29, #0x38]\n"
        "stur x0, [x29, #-0x20]\n"
        "stur x1, [x29, #-0x28]\n"
        "stur x2, [x29, #-0x30]\n"
        "stur x3, [x29, #-0x38]\n"
        "stur x4, [x29, #-0x40]\n"
        "str x5, [sp, #0x48]\n"
        "str x6, [sp, #0x40]\n"
        "str x7, [sp, #0x38]\n"
        "and w9, w9, #0x1\n"
        "strb w9, [sp, #0x34]\n"
        "and w8, w8, #0x1\n"
        "strb w8, [sp, #0x30]\n"
        "ldr x8, [x29, #0x20]\n"
        "ldr x9, [x29, #0x28]\n"
        "add x8, x8, x9\n"
        "str x8, [sp, #0x28]\n"
        "ldur x8, [x29, #-0x40]\n"
        "ldr x0, [x8]\n"
        "bl FUN_710393cfe0\n"
        "ldr x8, [x29, #0x30]\n"
        "orr w9, wzr, #0xffff\n"
        "add x8, x8, x9\n"
        "and x8, x8, #-0x10000\n"
        "add x9, x0, x8\n"
        "subs x9, x9, #0x1\n"
        "negs x8, x8\n"
        "and x19, x9, x8\n"
        "ldur x8, [x29, #-0x40]\n"
        "ldr x0, [x8]\n"
        "bl FUN_710393cfe0\n"
        "subs x8, x19, x0\n"
        "str x8, [sp, #0x20]\n"
        "b 0f\n"
        "0: b 1f\n"
        "1: ldur x8, [x29, #-0x40]\n"
        "ldr x0, [x8]\n"
        "bl FUN_710393ca80\n"
        "ldr x8, [sp, #0x20]\n"
        "ldr x9, [sp, #0x28]\n"
        "add x8, x8, x9\n"
        "subs x8, x0, x8\n"
        "b.cs 3f\n"
        "b 2f\n"
        "2: mov w8, #0x1\n"
        "stur w8, [x29, #-0x14]\n"
        "b 30f\n"
        "3: ldur x8, [x29, #-0x40]\n"
        "ldr x0, [x8]\n"
        "bl FUN_710393ca80\n"
        "ldr x8, [sp, #0x20]\n"
        "subs x8, x0, x8\n"
        "ldr x9, [sp, #0x28]\n"
        "subs x8, x8, x9\n"
        "str x8, [sp, #0x18]\n"
        "ldr x8, [sp, #0x48]\n"
        "str xzr, [x8]\n"
        "ldr x8, [sp, #0x40]\n"
        "str xzr, [x8]\n"
        "ldr x8, [sp, #0x38]\n"
        "str xzr, [x8]\n"
        "ldr x8, [x29, #0x10]\n"
        "str xzr, [x8]\n"
        "ldr x8, [sp, #0x20]\n"
        "cbz x8, 10f\n"
        "b 4f\n"
        "4: ldur x8, [x29, #-0x40]\n"
        "ldr x8, [x8]\n"
        "ldr x9, [sp, #0x48]\n"
        "str x8, [x9]\n"
        "ldur x0, [x29, #-0x20]\n"
        "ldur x1, [x29, #-0x28]\n"
        "ldur x2, [x29, #-0x30]\n"
        "ldr x8, [sp, #0x48]\n"
        "ldr x3, [x8]\n"
        "ldr x4, [sp, #0x20]\n"
        "ldr x8, [sp, #0x28]\n"
        "ldr x9, [sp, #0x18]\n"
        "add x7, x8, x9\n"
        "ldr w8, [x29, #0x40]\n"
        "ldrb w9, [sp, #0x34]\n"
        "ldrb w10, [sp, #0x30]\n"
        "and w10, w10, #0x1\n"
        "strb w10, [sp, #0x10]\n"
        "and w9, w9, #0x1\n"
        "strb w9, [sp, #0x8]\n"
        "str w8, [sp]\n"
        "mov w5, #0xe8\n"
        "mov w6, wzr\n"
        "bl FUN_7103941400\n"
        "ldur x8, [x29, #-0x40]\n"
        "str x0, [x8]\n"
        "ldur x8, [x29, #-0x40]\n"
        "ldr x8, [x8]\n"
        "cbnz x8, 6f\n"
        "b 5f\n"
        "5: ldr x8, [sp, #0x48]\n"
        "ldr x8, [x8]\n"
        "ldr x9, [sp, #0x38]\n"
        "str x8, [x9]\n"
        "ldr x8, [sp, #0x48]\n"
        "str xzr, [x8]\n"
        "mov w8, #0x2\n"
        "stur w8, [x29, #-0x14]\n"
        "b 30f\n"
        "6: b 10f\n"
        "10: ldr x8, [sp, #0x18]\n"
        "cbz x8, 16f\n"
        "b 11f\n"
        "11: ldur x0, [x29, #-0x20]\n"
        "ldur x1, [x29, #-0x28]\n"
        "ldur x2, [x29, #-0x30]\n"
        "ldur x8, [x29, #-0x40]\n"
        "ldr x3, [x8]\n"
        "ldr x4, [sp, #0x28]\n"
        "ldr w5, [x29, #0x40]\n"
        "ldr x7, [sp, #0x18]\n"
        "ldrb w8, [sp, #0x30]\n"
        "ldrb w9, [sp, #0x34]\n"
        "and w8, w8, #0x1\n"
        "strb w8, [sp, #0x10]\n"
        "strb wzr, [sp, #0x8]\n"
        "mov w8, #0xe8\n"
        "str w8, [sp]\n"
        "and w6, w9, #0x1\n"
        "bl FUN_7103941400\n"
        "ldr x8, [sp, #0x40]\n"
        "str x0, [x8]\n"
        "ldr x8, [sp, #0x40]\n"
        "ldr x8, [x8]\n"
        "cbnz x8, 14f\n"
        "b 12f\n"
        "12: ldur x8, [x29, #-0x40]\n"
        "ldr x8, [x8]\n"
        "ldr x9, [sp, #0x38]\n"
        "str x8, [x9]\n"
        "ldr x8, [sp, #0x48]\n"
        "ldr x8, [x8]\n"
        "ldr x9, [x29, #0x10]\n"
        "str x8, [x9]\n"
        "ldr x8, [sp, #0x48]\n"
        "str xzr, [x8]\n"
        "ldur x8, [x29, #-0x40]\n"
        "str xzr, [x8]\n"
        "mov w8, #0x2\n"
        "stur w8, [x29, #-0x14]\n"
        "b 30f\n"
        "14: b 16f\n"
        "16: ldr x8, [sp, #0x20]\n"
        "cbnz x8, 25f\n"
        "b 17f\n"
        "17: ldr x8, [sp, #0x18]\n"
        "cbnz x8, 25f\n"
        "b 18f\n"
        "18: ldur x8, [x29, #-0x40]\n"
        "ldr x0, [x8]\n"
        "ldr w1, [x29, #0x40]\n"
        "bl FUN_710393de00\n"
        "ldr w8, [x29, #0x40]\n"
        "subs w8, w8, #0xe8\n"
        "b.eq 24f\n"
        "b 19f\n"
        "19: ldur x19, [x29, #-0x20]\n"
        "ldur x20, [x29, #-0x38]\n"
        "ldur x8, [x29, #-0x40]\n"
        "ldr x0, [x8]\n"
        "bl FUN_7103939580\n"
        "mov x2, x0\n"
        "ldr w3, [x29, #0x40]\n"
        "ldrb w8, [sp, #0x34]\n"
        "and w4, w8, #0x1\n"
        "mov x0, x19\n"
        "mov x1, x20\n"
        "bl FUN_7103941810\n"
        "ldrb w8, [sp, #0x34]\n"
        "tbz w8, #0x0, 23f\n"
        "b 20f\n"
        "20: ldur x8, [x29, #-0x40]\n"
        "ldr x0, [x8]\n"
        "bl FUN_710393ca80\n"
        "subs x8, x0, #0x10, lsl #12\n"
        "b.ls 23f\n"
        "b 21f\n"
        "21: ldur x19, [x29, #-0x20]\n"
        "ldur x20, [x29, #-0x38]\n"
        "ldur x8, [x29, #-0x40]\n"
        "ldr x0, [x8]\n"
        "bl FUN_710393e720\n"
        "subs x2, x0, #0x10, lsl #12\n"
        "ldr w3, [x29, #0x40]\n"
        "ldrb w8, [sp, #0x34]\n"
        "and w4, w8, #0x1\n"
        "mov x0, x19\n"
        "mov x1, x20\n"
        "bl FUN_7103941810\n"
        "b 23f\n"
        "23: b 24f\n"
        "24: b 25f\n"
        "25: stur wzr, [x29, #-0x14]\n"
        "b 30f\n"
        "30: ldur w0, [x29, #-0x14]\n"
        "ldp x29, x30, [sp, #0x90]\n"
        "ldp x20, x19, [sp, #0x80]\n"
        "add sp, sp, #0xa0\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103940ee0 (96 bytes) — extent replace in heap
// jemalloc 5.1.0: extent.c — extent_heap_replace
// =========================================================================
extern "C" __attribute__((naked))
void FUN_7103940ee0(u64, u64, u64, u64) {
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

#endif // MATCHING_HACK_NX_CLANG
