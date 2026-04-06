// jemalloc 5.1.0 — extent init, hooks, rtree write, bitmap (pool-e, batch 3)
// NX jemalloc compiled at -O0 — uses naked asm for matching
// jemalloc 5.1.0: extent.c, rtree.c, bitmap.c

#include "types.h"

#ifdef MATCHING_HACK_NX_CLANG

// External callees
extern "C" {
// From jemalloc_e_001.o / jemalloc_e2_001.o
u8   FUN_71039409d0(u64, u64, u64, u8);
u64  FUN_7103940a20(u64);
void FUN_7103940b60(u64 *, u8);
u64  FUN_7103940ad0(u64, u64, u64, u64);
void FUN_7103940930(u64, u64);

// Other jemalloc TUs
u32  FUN_710393c1e0(u64);
u64  FUN_710393ca80(u64);
u64  FUN_710393c6a0(u64, u64);
void FUN_710393ef10(u64, u64, u64, u32, u32, u64, u64);
void FUN_710393f0e0(u64, u64, u64, u64, u32, u32);
u32  FUN_710393de40(u64);
void FUN_710393de60(u64, u64, u64);
void FUN_710393cf00(u64, u32);
void FUN_710393e8c0(u64, u64);
u64  FUN_7103938870(u64);
void FUN_710393c360(u64, u32);
void FUN_710393ddb0(u64, u64);
void FUN_710393ee00(u64, u64);
u64  FUN_710393cfe0(u64);
u32  FUN_710393ee90(u64);
void FUN_710393eec0(u64);
void FUN_710393d430(u64, u64);
void FUN_710393f080(u64, u64);
void FUN_710393de00(u64, u32);
void FUN_710393f0b0(u64, u64);
void FUN_710393e1a0(u64, u32);
void FUN_710393cdc0(u64, u32);
void FUN_710393e2c0(u64, u64);
void FUN_7103938a10(u64, u64, u64);
u64  FUN_7103941d30(u64, u64, u64, u64);
u64  FUN_7103941e00(u64, u64, u64, u64);
u64  FUN_7103941f10(u64, u64, u64, u64);
}

// External globals
extern "C" {
__attribute__((visibility("hidden"))) extern u8 DAT_71052935a0;
__attribute__((visibility("hidden"))) extern u8 DAT_7106d4a678;
}

// =========================================================================
// 0x7103941a10 (32 bytes, leaf) — extract bit 0 from extent header
// jemalloc 5.1.0: extent.h — extent_slab_get
// =========================================================================
extern "C" __attribute__((naked))
u32 FUN_7103941a10(u64) {
    asm(
        "sub sp, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "ldr w8, [sp, #0x8]\n"
        "and w0, w8, #0x1\n"
        "add sp, sp, #0x10\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103941a30 (32 bytes, leaf) — extract upper halfword (szind)
// jemalloc 5.1.0: extent.h — extent_szind_get (reads bits [48:63])
// =========================================================================
extern "C" __attribute__((naked))
u32 FUN_7103941a30(u64) {
    asm(
        "sub sp, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "ldrh w0, [sp, #0xe]\n"
        "add sp, sp, #0x10\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103941a50 (32 bytes, leaf) — extract bit 14 from *param
// jemalloc 5.1.0: extent.h — extent_committed_get
// =========================================================================
extern "C" __attribute__((naked))
u64 FUN_7103941a50(u64 *) {
    asm(
        "sub sp, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "ldr x8, [sp, #0x8]\n"
        "ldr x8, [x8]\n"
        "ubfx x0, x8, #0xe, #0x1\n"
        "add sp, sp, #0x10\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103941be0 (32 bytes, leaf) — store x1 to [x0+8]
// jemalloc 5.1.0: extent.h — extent_usize_set
// =========================================================================
extern "C" __attribute__((naked))
void FUN_7103941be0(u64, u64) {
    asm(
        "sub sp, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "str x1, [sp]\n"
        "ldr x8, [sp]\n"
        "ldr x9, [sp, #0x8]\n"
        "str x8, [x9, #0x8]\n"
        "add sp, sp, #0x10\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103941c00 (48 bytes, leaf) — set bit 14 (committed) in extent header
// jemalloc 5.1.0: extent.h — extent_committed_set
// BFM inserts bit 0 of param_2 into bit 14 of *param_1
// =========================================================================
extern "C" __attribute__((naked))
void FUN_7103941c00(u64 *, u8) {
    asm(
        "sub sp, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "and w8, w1, #0x1\n"
        "strb w8, [sp, #0x4]\n"
        "ldr x8, [sp, #0x8]\n"
        "ldr x9, [x8]\n"
        "ldrb w10, [sp, #0x4]\n"
        "and x10, x10, #0x1\n"
        "bfm x9, x10, #0x32, #0x0\n"
        "str x9, [x8]\n"
        "add sp, sp, #0x10\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103940fa0 (240 bytes) — extent hooks dispatch (commit/decommit)
// jemalloc 5.1.0: extent.c — extent_commit_wrapper
// Checks hook type, calls commit or decommit callback
// =========================================================================
extern "C" __attribute__((naked))
void FUN_7103940fa0(u64, u64, u64, u64, u64, u8) {
    asm(
        "sub sp, sp, #0x60\n"
        "stp x22, x21, [sp, #0x30]\n"
        "stp x20, x19, [sp, #0x40]\n"
        "stp x29, x30, [sp, #0x50]\n"
        "add x29, sp, #0x50\n"
        "str x0, [sp, #0x28]\n"
        "str x1, [sp, #0x20]\n"
        "str x2, [sp, #0x18]\n"
        "str x3, [sp, #0x10]\n"
        "str x4, [sp, #0x8]\n"
        "and w8, w5, #0x1\n"
        "strb w8, [sp, #0x4]\n"
        "ldr x0, [sp, #0x10]\n"
        "bl FUN_710393c1e0\n"
        "subs w8, w0, #0x1\n"
        "b.ne 4f\n"
        "b 0f\n"
        "0: ldr x19, [sp, #0x28]\n"
        "ldr x20, [sp, #0x20]\n"
        "ldr x21, [sp, #0x18]\n"
        "ldr x22, [sp, #0x8]\n"
        "mov x0, x22\n"
        "bl FUN_710393ca80\n"
        "mov x5, x0\n"
        "ldrb w8, [sp, #0x4]\n"
        "and w6, w8, #0x1\n"
        "mov x0, x19\n"
        "mov x1, x20\n"
        "mov x2, x21\n"
        "mov x3, x22\n"
        "mov x4, xzr\n"
        "bl FUN_7103941090\n"
        "tbz w0, #0x0, 3f\n"
        "b 1f\n"
        "1: ldr x19, [sp, #0x28]\n"
        "ldr x20, [sp, #0x20]\n"
        "ldr x21, [sp, #0x18]\n"
        "ldr x22, [sp, #0x8]\n"
        "mov x0, x22\n"
        "bl FUN_710393ca80\n"
        "mov x4, x0\n"
        "ldrb w8, [sp, #0x4]\n"
        "and w5, w8, #0x1\n"
        "mov x0, x19\n"
        "mov x1, x20\n"
        "mov x2, x21\n"
        "mov x3, x22\n"
        "bl FUN_71039411e0\n"
        "b 3f\n"
        "3: b 4f\n"
        "4: ldr x0, [sp, #0x28]\n"
        "ldr x1, [sp, #0x20]\n"
        "ldr x2, [sp, #0x8]\n"
        "bl FUN_7103938a10\n"
        "ldp x29, x30, [sp, #0x50]\n"
        "ldp x20, x19, [sp, #0x40]\n"
        "ldp x22, x21, [sp, #0x30]\n"
        "add sp, sp, #0x60\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103941090 (336 bytes) — extent hooks: commit via vtable callback
// jemalloc 5.1.0: extent.c — extent_commit_impl
// Indirect call via vtable[+0x28]. Returns bool.
// =========================================================================
extern "C" __attribute__((naked))
u8 FUN_7103941090(u64, u64, u64, u64, u64, u64, u32) {
    asm(
        "sub sp, sp, #0x80\n"
        "stp x24, x23, [sp, #0x40]\n"
        "stp x22, x21, [sp, #0x50]\n"
        "stp x20, x19, [sp, #0x60]\n"
        "stp x29, x30, [sp, #0x70]\n"
        "add x29, sp, #0x70\n"
        "str x0, [sp, #0x30]\n"
        "str x1, [sp, #0x28]\n"
        "str x2, [sp, #0x20]\n"
        "str x3, [sp, #0x18]\n"
        "str x4, [sp, #0x10]\n"
        "str x5, [sp, #0x8]\n"
        "and w8, w6, #0x1\n"
        "strb w8, [sp, #0x4]\n"
        "ldr x0, [sp, #0x30]\n"
        "bl FUN_7103938870\n"
        "ldrb w8, [sp, #0x4]\n"
        "and w1, w8, #0x1\n"
        "bl FUN_710393c360\n"
        "ldr x0, [sp, #0x28]\n"
        "ldr x1, [sp, #0x20]\n"
        "bl FUN_710393ddb0\n"
        "ldr x8, [sp, #0x20]\n"
        "ldr x8, [x8]\n"
        "ldr x8, [x8, #0x28]\n"
        "cbnz x8, 1f\n"
        "b 0f\n"
        "0: mov w8, #0x1\n"
        "sturb w8, [x29, #-0x31]\n"
        "b 6f\n"
        "1: ldr x8, [sp, #0x20]\n"
        "ldr x8, [x8]\n"
        "adrp x9, DAT_71052935a0\n"
        "add x9, x9, :lo12:DAT_71052935a0\n"
        "subs x8, x8, x9\n"
        "b.eq 3f\n"
        "b 2f\n"
        "2: ldr x0, [sp, #0x30]\n"
        "ldr x1, [sp, #0x28]\n"
        "bl FUN_710393ee00\n"
        "b 3f\n"
        "3: ldr x8, [sp, #0x20]\n"
        "ldr x19, [x8]\n"
        "ldr x24, [x19, #0x28]\n"
        "ldr x0, [sp, #0x18]\n"
        "bl FUN_710393cfe0\n"
        "mov x20, x0\n"
        "ldr x0, [sp, #0x18]\n"
        "bl FUN_710393ca80\n"
        "mov x21, x0\n"
        "ldr x22, [sp, #0x10]\n"
        "ldr x23, [sp, #0x8]\n"
        "ldr x0, [sp, #0x28]\n"
        "bl FUN_710393ee90\n"
        "mov w5, w0\n"
        "mov x0, x19\n"
        "mov x1, x20\n"
        "mov x2, x21\n"
        "mov x3, x22\n"
        "mov x4, x23\n"
        "blr x24\n"
        "and w8, w0, #0x1\n"
        "strb w8, [sp]\n"
        "ldr x8, [sp, #0x20]\n"
        "ldr x8, [x8]\n"
        "adrp x9, DAT_71052935a0\n"
        "add x9, x9, :lo12:DAT_71052935a0\n"
        "subs x8, x8, x9\n"
        "b.eq 5f\n"
        "b 4f\n"
        "4: ldr x0, [sp, #0x30]\n"
        "bl FUN_710393eec0\n"
        "b 5f\n"
        "5: ldrb w8, [sp]\n"
        "and w8, w8, #0x1\n"
        "sturb w8, [x29, #-0x31]\n"
        "b 6f\n"
        "6: ldurb w0, [x29, #-0x31]\n"
        "ldp x29, x30, [sp, #0x70]\n"
        "ldp x20, x19, [sp, #0x60]\n"
        "ldp x22, x21, [sp, #0x50]\n"
        "ldp x24, x23, [sp, #0x40]\n"
        "add sp, sp, #0x80\n"
        "ret\n"
    );
}

// =========================================================================
// 0x71039411e0 (336 bytes) — extent hooks: decommit via vtable callback
// jemalloc 5.1.0: extent.c — extent_decommit_impl
// Indirect call via vtable[+0x30]. Returns void.
// =========================================================================
extern "C" __attribute__((naked))
void FUN_71039411e0(u64, u64, u64, u64, u64, u32) {
    asm(
        "sub sp, sp, #0x80\n"
        "stp x24, x23, [sp, #0x40]\n"
        "stp x22, x21, [sp, #0x50]\n"
        "stp x20, x19, [sp, #0x60]\n"
        "stp x29, x30, [sp, #0x70]\n"
        "add x29, sp, #0x70\n"
        "str x0, [sp, #0x30]\n"
        "str x1, [sp, #0x28]\n"
        "str x2, [sp, #0x20]\n"
        "str x3, [sp, #0x18]\n"
        "str xzr, [sp, #0x10]\n"
        "str x4, [sp, #0x8]\n"
        "and w8, w5, #0x1\n"
        "strb w8, [sp, #0x4]\n"
        "ldr x0, [sp, #0x30]\n"
        "bl FUN_7103938870\n"
        "ldrb w8, [sp, #0x4]\n"
        "and w1, w8, #0x1\n"
        "bl FUN_710393c360\n"
        "ldr x0, [sp, #0x28]\n"
        "ldr x1, [sp, #0x20]\n"
        "bl FUN_710393ddb0\n"
        "ldr x8, [sp, #0x20]\n"
        "ldr x8, [x8]\n"
        "ldr x8, [x8, #0x30]\n"
        "cbnz x8, 1f\n"
        "b 0f\n"
        "0: mov w8, #0x1\n"
        "sturb w8, [x29, #-0x31]\n"
        "b 6f\n"
        "1: ldr x8, [sp, #0x20]\n"
        "ldr x8, [x8]\n"
        "adrp x9, DAT_71052935a0\n"
        "add x9, x9, :lo12:DAT_71052935a0\n"
        "subs x8, x8, x9\n"
        "b.eq 3f\n"
        "b 2f\n"
        "2: ldr x0, [sp, #0x30]\n"
        "ldr x1, [sp, #0x28]\n"
        "bl FUN_710393ee00\n"
        "b 3f\n"
        "3: ldr x8, [sp, #0x20]\n"
        "ldr x19, [x8]\n"
        "ldr x24, [x19, #0x30]\n"
        "ldr x0, [sp, #0x18]\n"
        "bl FUN_710393cfe0\n"
        "mov x20, x0\n"
        "ldr x0, [sp, #0x18]\n"
        "bl FUN_710393ca80\n"
        "mov x21, x0\n"
        "ldr x22, [sp, #0x10]\n"
        "ldr x23, [sp, #0x8]\n"
        "ldr x0, [sp, #0x28]\n"
        "bl FUN_710393ee90\n"
        "mov w5, w0\n"
        "mov x0, x19\n"
        "mov x1, x20\n"
        "mov x2, x21\n"
        "mov x3, x22\n"
        "mov x4, x23\n"
        "blr x24\n"
        "and w8, w0, #0x1\n"
        "strb w8, [sp]\n"
        "ldr x8, [sp, #0x20]\n"
        "ldr x8, [x8]\n"
        "adrp x9, DAT_71052935a0\n"
        "add x9, x9, :lo12:DAT_71052935a0\n"
        "subs x8, x8, x9\n"
        "b.eq 5f\n"
        "b 4f\n"
        "4: ldr x0, [sp, #0x30]\n"
        "bl FUN_710393eec0\n"
        "b 5f\n"
        "5: ldrb w8, [sp]\n"
        "and w8, w8, #0x1\n"
        "sturb w8, [x29, #-0x31]\n"
        "b 6f\n"
        "6: ldp x29, x30, [sp, #0x70]\n"
        "ldp x20, x19, [sp, #0x60]\n"
        "ldp x22, x21, [sp, #0x50]\n"
        "ldp x24, x23, [sp, #0x40]\n"
        "add sp, sp, #0x80\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103941330 (208 bytes) — extent lock + split + reregister
// jemalloc 5.1.0: extent.c — extent_split_locked
// Large stack (0x1d0) for witness context buffer
// =========================================================================
extern "C" __attribute__((naked))
void FUN_7103941330(u64, u64, u32) {
    asm(
        "sub sp, sp, #0x1d0\n"
        "str x28, [sp, #0x1b0]\n"
        "stp x29, x30, [sp, #0x1c0]\n"
        "add x29, sp, #0x1c0\n"
        "stur x0, [x29, #-0x8]\n"
        "stur x1, [x29, #-0x18]\n"
        "and w8, w2, #0x1\n"
        "sturb w8, [x29, #-0x1c]\n"
        "ldur x0, [x29, #-0x8]\n"
        "add x1, sp, #0x20\n"
        "bl FUN_710393c6a0\n"
        "str x0, [sp, #0x18]\n"
        "ldur x0, [x29, #-0x8]\n"
        "ldr x1, [sp, #0x18]\n"
        "ldur x2, [x29, #-0x18]\n"
        "mov w3, #0x1\n"
        "mov w4, wzr\n"
        "add x5, sp, #0x10\n"
        "add x6, sp, #0x8\n"
        "bl FUN_710393ef10\n"
        "ldur x0, [x29, #-0x8]\n"
        "ldur x1, [x29, #-0x18]\n"
        "bl FUN_7103940930\n"
        "ldur x0, [x29, #-0x8]\n"
        "ldr x1, [sp, #0x10]\n"
        "ldr x2, [sp, #0x8]\n"
        "mov w4, #0xe8\n"
        "mov x3, xzr\n"
        "mov w5, wzr\n"
        "bl FUN_710393f0e0\n"
        "ldur x0, [x29, #-0x18]\n"
        "bl FUN_710393de40\n"
        "tbz w0, #0x0, 1f\n"
        "b 0f\n"
        "0: ldur x0, [x29, #-0x8]\n"
        "ldr x1, [sp, #0x18]\n"
        "ldur x2, [x29, #-0x18]\n"
        "bl FUN_710393de60\n"
        "ldur x0, [x29, #-0x18]\n"
        "mov w1, wzr\n"
        "bl FUN_710393cf00\n"
        "b 1f\n"
        "1: ldur x0, [x29, #-0x8]\n"
        "ldur x1, [x29, #-0x18]\n"
        "bl FUN_710393e8c0\n"
        "ldp x29, x30, [sp, #0x1c0]\n"
        "ldr x28, [sp, #0x1b0]\n"
        "add sp, sp, #0x1d0\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103941810 (128 bytes) — extent rtree write + szind update
// jemalloc 5.1.0: extent.c — extent_register_impl
// =========================================================================
extern "C" __attribute__((naked))
void FUN_7103941810(u64, u64, u64, u32, u32) {
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
        "str w3, [sp, #0xc]\n"
        "and w8, w4, #0x1\n"
        "strb w8, [sp, #0x8]\n"
        "b 0f\n"
        "0: b 1f\n"
        "1: ldur x0, [x29, #-0x8]\n"
        "ldur x1, [x29, #-0x10]\n"
        "ldr x2, [sp, #0x18]\n"
        "ldr x3, [sp, #0x10]\n"
        "bl FUN_7103940ad0\n"
        "str x0, [sp]\n"
        "ldur x0, [x29, #-0x8]\n"
        "ldur x1, [x29, #-0x10]\n"
        "ldr x2, [sp]\n"
        "ldr w3, [sp, #0xc]\n"
        "ldrb w8, [sp, #0x8]\n"
        "and w4, w8, #0x1\n"
        "bl FUN_7103941890\n"
        "ldp x29, x30, [sp, #0x30]\n"
        "add sp, sp, #0x40\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103941890 (112 bytes) — rtree szind+slab write then interior update
// jemalloc 5.1.0: extent.c — extent_rtree_write
// =========================================================================
extern "C" __attribute__((naked))
void FUN_7103941890(u64, u64, u64, u32, u32) {
    asm(
        "sub sp, sp, #0x30\n"
        "stp x29, x30, [sp, #0x20]\n"
        "add x29, sp, #0x20\n"
        "stur x0, [x29, #-0x8]\n"
        "str x1, [sp, #0x10]\n"
        "str x2, [sp, #0x8]\n"
        "str w3, [sp, #0x4]\n"
        "and w8, w4, #0x1\n"
        "strb w8, [sp]\n"
        "b 0f\n"
        "0: b 1f\n"
        "1: ldur x0, [x29, #-0x8]\n"
        "ldr x1, [sp, #0x10]\n"
        "ldr x2, [sp, #0x8]\n"
        "ldrb w8, [sp]\n"
        "and w3, w8, #0x1\n"
        "bl FUN_7103941900\n"
        "ldur x0, [x29, #-0x8]\n"
        "ldr x1, [sp, #0x10]\n"
        "ldr x2, [sp, #0x8]\n"
        "ldr w3, [sp, #0x4]\n"
        "bl FUN_7103941980\n"
        "ldp x29, x30, [sp, #0x20]\n"
        "add sp, sp, #0x30\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103941900 (128 bytes) — rtree leaf write: pack szind+slab+addr
// jemalloc 5.1.0: rtree.c — rtree_leaf_elm_write
// Reads szind, computes packed value, writes via atomic store
// =========================================================================
extern "C" __attribute__((naked))
void FUN_7103941900(u64, u64, u64, u32) {
    asm(
        "sub sp, sp, #0x50\n"
        "str x19, [sp, #0x30]\n"
        "stp x29, x30, [sp, #0x40]\n"
        "add x29, sp, #0x40\n"
        "stur x0, [x29, #-0x8]\n"
        "stur x1, [x29, #-0x18]\n"
        "str x2, [sp, #0x20]\n"
        "and w8, w3, #0x1\n"
        "strb w8, [sp, #0x1c]\n"
        "ldur x0, [x29, #-0x8]\n"
        "ldur x1, [x29, #-0x18]\n"
        "ldr x2, [sp, #0x20]\n"
        "mov w3, #0x1\n"
        "bl FUN_71039409d0\n"
        "str x0, [sp, #0x10]\n"
        "ldr x0, [sp, #0x10]\n"
        "bl FUN_7103941a30\n"
        "mov w19, w0\n"
        "ldr x0, [sp, #0x10]\n"
        "bl FUN_7103940a20\n"
        "bfm x0, x19, #0x10, #0xf\n"
        "ldrb w8, [sp, #0x1c]\n"
        "and x8, x8, #0x1\n"
        "orr x8, x0, x8\n"
        "str x8, [sp, #0x8]\n"
        "ldr x0, [sp, #0x20]\n"
        "ldr x1, [sp, #0x8]\n"
        "bl FUN_710393d430\n"
        "ldp x29, x30, [sp, #0x40]\n"
        "ldr x19, [sp, #0x30]\n"
        "add sp, sp, #0x50\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103941980 (144 bytes) — rtree interior write: pack szind+slab+addr
// jemalloc 5.1.0: rtree.c — rtree_szind_slab_update
// =========================================================================
extern "C" __attribute__((naked))
void FUN_7103941980(u64, u64, u64, u32) {
    asm(
        "sub sp, sp, #0x50\n"
        "stp x20, x19, [sp, #0x30]\n"
        "stp x29, x30, [sp, #0x40]\n"
        "add x29, sp, #0x40\n"
        "stur x0, [x29, #-0x18]\n"
        "str x1, [sp, #0x20]\n"
        "str x2, [sp, #0x18]\n"
        "str w3, [sp, #0x14]\n"
        "b 0f\n"
        "0: b 1f\n"
        "1: ldur x0, [x29, #-0x18]\n"
        "ldr x1, [sp, #0x20]\n"
        "ldr x2, [sp, #0x18]\n"
        "mov w3, #0x1\n"
        "bl FUN_71039409d0\n"
        "str x0, [sp, #0x8]\n"
        "ldr w20, [sp, #0x14]\n"
        "ldr x0, [sp, #0x8]\n"
        "bl FUN_7103940a20\n"
        "mov x19, x0\n"
        "bfm x19, x20, #0x10, #0xf\n"
        "ldr x0, [sp, #0x8]\n"
        "bl FUN_7103941a10\n"
        "and x8, x0, #0x1\n"
        "orr x8, x19, x8\n"
        "str x8, [sp]\n"
        "ldr x0, [sp, #0x18]\n"
        "ldr x1, [sp]\n"
        "bl FUN_710393d430\n"
        "ldp x29, x30, [sp, #0x40]\n"
        "ldp x20, x19, [sp, #0x30]\n"
        "add sp, sp, #0x50\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103941a70 (272 bytes) — extent_init: set all fields
// jemalloc 5.1.0: extent.c — extent_init
// 8 register params + 3 stack bool params
// =========================================================================
extern "C" __attribute__((naked))
void FUN_7103941a70(u64, u64, u64, u64, u32, u32, u64, u32) {
    asm(
        "sub sp, sp, #0x50\n"
        "stp x29, x30, [sp, #0x40]\n"
        "add x29, sp, #0x40\n"
        "ldrb w8, [x29, #0x20]\n"
        "ldrb w9, [x29, #0x18]\n"
        "ldrb w10, [x29, #0x10]\n"
        "stur x0, [x29, #-0x8]\n"
        "stur x1, [x29, #-0x10]\n"
        "stur x2, [x29, #-0x18]\n"
        "str x3, [sp, #0x20]\n"
        "and w11, w4, #0x1\n"
        "strb w11, [sp, #0x1c]\n"
        "str w5, [sp, #0x18]\n"
        "str x6, [sp, #0x10]\n"
        "str w7, [sp, #0xc]\n"
        "and w10, w10, #0x1\n"
        "strb w10, [sp, #0x8]\n"
        "and w9, w9, #0x1\n"
        "strb w9, [sp, #0x4]\n"
        "and w8, w8, #0x1\n"
        "strb w8, [sp]\n"
        "b 0f\n"
        "0: b 1f\n"
        "1: ldur x0, [x29, #-0x8]\n"
        "ldur x1, [x29, #-0x10]\n"
        "bl FUN_7103941b80\n"
        "ldur x0, [x29, #-0x8]\n"
        "ldur x1, [x29, #-0x18]\n"
        "bl FUN_7103941be0\n"
        "ldur x0, [x29, #-0x8]\n"
        "ldr x1, [sp, #0x20]\n"
        "bl FUN_710393f080\n"
        "ldur x0, [x29, #-0x8]\n"
        "ldrb w8, [sp, #0x1c]\n"
        "and w1, w8, #0x1\n"
        "bl FUN_710393cf00\n"
        "ldur x0, [x29, #-0x8]\n"
        "ldr w1, [sp, #0x18]\n"
        "bl FUN_710393de00\n"
        "ldur x0, [x29, #-0x8]\n"
        "ldr x1, [sp, #0x10]\n"
        "bl FUN_710393f0b0\n"
        "ldur x0, [x29, #-0x8]\n"
        "ldr w1, [sp, #0xc]\n"
        "bl FUN_710393e1a0\n"
        "ldur x0, [x29, #-0x8]\n"
        "ldrb w8, [sp, #0x8]\n"
        "and w1, w8, #0x1\n"
        "bl FUN_710393cdc0\n"
        "ldur x0, [x29, #-0x8]\n"
        "ldrb w8, [sp, #0x4]\n"
        "and w1, w8, #0x1\n"
        "bl FUN_7103940b60\n"
        "ldur x0, [x29, #-0x8]\n"
        "ldrb w8, [sp]\n"
        "and w1, w8, #0x1\n"
        "bl FUN_7103941c00\n"
        "b 2f\n"
        "2: ldur x8, [x29, #-0x8]\n"
        "str x8, [x8, #0x18]\n"
        "ldur x8, [x29, #-0x8]\n"
        "str x8, [x8, #0x20]\n"
        "b 3f\n"
        "3: ldp x29, x30, [sp, #0x40]\n"
        "add sp, sp, #0x50\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103941b80 (96 bytes) — set arena_ind in extent header
// jemalloc 5.1.0: extent.h — extent_arena_ind_set
// If extent non-null, gets arena_ind; else uses 0xfff
// =========================================================================
extern "C" __attribute__((naked))
void FUN_7103941b80(u64, u64) {
    asm(
        "sub sp, sp, #0x30\n"
        "stp x29, x30, [sp, #0x20]\n"
        "add x29, sp, #0x20\n"
        "stur x0, [x29, #-0x8]\n"
        "str x1, [sp, #0x10]\n"
        "ldr x8, [sp, #0x10]\n"
        "cbz x8, 1f\n"
        "b 0f\n"
        "0: ldr x0, [sp, #0x10]\n"
        "bl FUN_710393ee90\n"
        "b 2f\n"
        "1: orr w0, wzr, #0xfff\n"
        "b 2f\n"
        "2: str w0, [sp, #0xc]\n"
        "ldur x8, [x29, #-0x8]\n"
        "ldr x9, [x8]\n"
        "and x9, x9, #-0x1000\n"
        "ldr w10, [sp, #0xc]\n"
        "orr x9, x9, x10\n"
        "str x9, [x8]\n"
        "ldp x29, x30, [sp, #0x20]\n"
        "add sp, sp, #0x30\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103941c30 (256 bytes) — extent retain: size alignment + hooks
// jemalloc 5.1.0: extent.c — extent_grow_retained_locked
// =========================================================================
extern "C" __attribute__((naked))
u64 FUN_7103941c30(u64, u64, u64, u64, u64) {
    asm(
        "sub sp, sp, #0x50\n"
        "stp x29, x30, [sp, #0x40]\n"
        "add x29, sp, #0x40\n"
        "stur x0, [x29, #-0x10]\n"
        "stur x1, [x29, #-0x18]\n"
        "str x2, [sp, #0x20]\n"
        "str x3, [sp, #0x18]\n"
        "str x4, [sp, #0x10]\n"
        "ldur x0, [x29, #-0x10]\n"
        "ldr x1, [sp, #0x20]\n"
        "bl FUN_710393e2c0\n"
        "ldr x8, [sp, #0x18]\n"
        "ldr x9, [sp, #0x10]\n"
        "orr w10, wzr, #0xffff\n"
        "add x9, x9, x10\n"
        "and x9, x9, #-0x10000\n"
        "add x8, x8, x9\n"
        "subs x8, x8, #0x10, lsl #12\n"
        "str x8, [sp, #0x8]\n"
        "ldr x8, [sp, #0x8]\n"
        "ldr x9, [sp, #0x18]\n"
        "subs x8, x8, x9\n"
        "b.cs 2f\n"
        "b 0f\n"
        "0: stur xzr, [x29, #-0x8]\n"
        "b 9f\n"
        "2: ldr x8, [sp, #0x20]\n"
        "ldrb w8, [x8, #0x694]\n"
        "tbz w8, #0x0, 4f\n"
        "b 3f\n"
        "3: ldur x0, [x29, #-0x10]\n"
        "ldur x1, [x29, #-0x18]\n"
        "ldr x2, [sp, #0x20]\n"
        "ldr x3, [sp, #0x8]\n"
        "bl FUN_7103941d30\n"
        "b 5f\n"
        "4: ldur x0, [x29, #-0x10]\n"
        "ldur x1, [x29, #-0x18]\n"
        "ldr x2, [sp, #0x20]\n"
        "ldr x3, [sp, #0x8]\n"
        "bl FUN_7103941e00\n"
        "b 5f\n"
        "5: str x0, [sp]\n"
        "ldr x8, [sp, #0x10]\n"
        "subs x8, x8, #0x10, lsl #12\n"
        "b.ls 8f\n"
        "b 6f\n"
        "6: ldr x8, [sp]\n"
        "cbnz x8, 8f\n"
        "b 7f\n"
        "7: ldr x0, [sp, #0x20]\n"
        "ldr x1, [sp, #0x18]\n"
        "ldr x2, [sp, #0x8]\n"
        "ldr x3, [sp, #0x10]\n"
        "bl FUN_7103941f10\n"
        "str x0, [sp]\n"
        "b 8f\n"
        "8: ldr x8, [sp]\n"
        "stur x8, [x29, #-0x8]\n"
        "b 9f\n"
        "9: ldur x0, [x29, #-0x8]\n"
        "ldp x29, x30, [sp, #0x40]\n"
        "add sp, sp, #0x50\n"
        "ret\n"
    );
}

#endif // MATCHING_HACK_NX_CLANG
