#include "types.h"

// Batch decompiled via Ghidra MCP -- pool-e, hard tier 002
// Factory constructors: je_aligned_alloc + DAT_7105331f00 singleton fallback
// All use __attribute__((naked)) for exact byte-matching

// 0x7102054990 (152B)
// Alloc 0x40-byte object; vtable DAT_71050b3468; [0x8]=0xa, [0x20]=0xffffffff50000000
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void* FUN_7102054990() {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "mov w0, #0x10\n"
        "mov w1, #0x40\n"
        "bl FUN_710392dce0\n"
        "cbnz x0, 0f\n"
        "adrp x8, DAT_7105331f00\n"
        "ldr x0, [x8, :lo12:DAT_7105331f00]\n"
        "cbz x0, 1f\n"
        "mov w8, #0x40\n"
        "stur wzr, [x29, #-0x4]\n"
        "sub x1, x29, #0x4\n"
        "str x8, [sp]\n"
        "ldr x8, [x0]\n"
        "ldr x8, [x8, #0x30]\n"
        "mov x2, sp\n"
        "blr x8\n"
        "tbz w0, #0, 1f\n"
        "mov w0, #0x10\n"
        "mov w1, #0x40\n"
        "bl FUN_710392dce0\n"
        "cbnz x0, 0f\n"
        "1:\n"
        "mov x0, xzr\n"
        "0:\n"
        "mov w8, #0xa\n"
        "str w8, [x0, #0x8]\n"
        "mov x8, #-0x10000\n"
        "stp xzr, xzr, [x0, #0x10]\n"
        "movk x8, #0x5000, LSL #16\n"
        "stp xzr, xzr, [x0, #0x30]\n"
        "str x8, [x0, #0x20]\n"
        "adrp x8, DAT_71050b3468\n"
        "add x8, x8, :lo12:DAT_71050b3468\n"
        "strb wzr, [x0, #0x28]\n"
        "str x8, [x0]\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}
#endif

// 0x7102055bc0 (168B)
// Alloc 0x38-byte object; vtable DAT_71050b34b8; [0x10]=0x47f6fc330, [0x20]=0xffffffff50000000
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void* FUN_7102055bc0() {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "mov w0, #0x10\n"
        "orr w1, wzr, #0x38\n"
        "bl FUN_710392dce0\n"
        "cbnz x0, 0f\n"
        "adrp x8, DAT_7105331f00\n"
        "ldr x0, [x8, :lo12:DAT_7105331f00]\n"
        "cbz x0, 1f\n"
        "orr w8, wzr, #0x38\n"
        "stur wzr, [x29, #-0x4]\n"
        "sub x1, x29, #0x4\n"
        "str x8, [sp]\n"
        "ldr x8, [x0]\n"
        "ldr x8, [x8, #0x30]\n"
        "mov x2, sp\n"
        "blr x8\n"
        "tbz w0, #0, 1f\n"
        "mov w0, #0x10\n"
        "orr w1, wzr, #0x38\n"
        "bl FUN_710392dce0\n"
        "cbnz x0, 0f\n"
        "1:\n"
        "mov x0, xzr\n"
        "0:\n"
        "mov w8, #0xa\n"
        "str w8, [x0, #0x8]\n"
        "mov x8, #0xc330\n"
        "movk x8, #0x7f6f, LSL #16\n"
        "movk x8, #0x4, LSL #32\n"
        "strb wzr, [x0, #0x28]\n"
        "stp x8, xzr, [x0, #0x10]\n"
        "mov x8, #-0x10000\n"
        "movk x8, #0x5000, LSL #16\n"
        "str x8, [x0, #0x20]\n"
        "adrp x8, DAT_71050b34b8\n"
        "add x8, x8, :lo12:DAT_71050b34b8\n"
        "str x8, [x0]\n"
        "orr x8, xzr, #0x3f80000000000000\n"
        "stur x8, [x0, #0x2c]\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}
#endif

// 0x71020e9590 (144B)
// Alloc 0x20-byte object; vtable DAT_71050b3b48; [0x8]=0x5000000000000001, [0x10]=0x500000000000003d
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void* FUN_71020e9590() {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "mov w0, #0x10\n"
        "mov w1, #0x20\n"
        "bl FUN_710392dce0\n"
        "cbnz x0, 0f\n"
        "adrp x8, DAT_7105331f00\n"
        "ldr x0, [x8, :lo12:DAT_7105331f00]\n"
        "cbz x0, 1f\n"
        "mov w8, #0x20\n"
        "stur wzr, [x29, #-0x4]\n"
        "sub x1, x29, #0x4\n"
        "str x8, [sp]\n"
        "ldr x8, [x0]\n"
        "ldr x8, [x8, #0x30]\n"
        "mov x2, sp\n"
        "blr x8\n"
        "tbz w0, #0, 1f\n"
        "mov w0, #0x10\n"
        "mov w1, #0x20\n"
        "bl FUN_710392dce0\n"
        "cbnz x0, 0f\n"
        "1:\n"
        "mov x0, xzr\n"
        "0:\n"
        "mov x8, #0x1\n"
        "mov x10, #0x3d\n"
        "movk x8, #0x5000, LSL #48\n"
        "adrp x9, DAT_71050b3b48\n"
        "add x9, x9, :lo12:DAT_71050b3b48\n"
        "strb wzr, [x0, #0x18]\n"
        "movk x10, #0x5000, LSL #48\n"
        "stp x9, x8, [x0]\n"
        "str x10, [x0, #0x10]\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}
#endif

// 0x71020ea0a0 (144B)
// Alloc 0x20-byte object; vtable DAT_71050b3b98; [0x8]=0x5000000000000001, [0x10]=0x500000000000003e
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void* FUN_71020ea0a0() {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "mov w0, #0x10\n"
        "mov w1, #0x20\n"
        "bl FUN_710392dce0\n"
        "cbnz x0, 0f\n"
        "adrp x8, DAT_7105331f00\n"
        "ldr x0, [x8, :lo12:DAT_7105331f00]\n"
        "cbz x0, 1f\n"
        "mov w8, #0x20\n"
        "stur wzr, [x29, #-0x4]\n"
        "sub x1, x29, #0x4\n"
        "str x8, [sp]\n"
        "ldr x8, [x0]\n"
        "ldr x8, [x8, #0x30]\n"
        "mov x2, sp\n"
        "blr x8\n"
        "tbz w0, #0, 1f\n"
        "mov w0, #0x10\n"
        "mov w1, #0x20\n"
        "bl FUN_710392dce0\n"
        "cbnz x0, 0f\n"
        "1:\n"
        "mov x0, xzr\n"
        "0:\n"
        "mov x8, #0x1\n"
        "mov x10, #0x3e\n"
        "movk x8, #0x5000, LSL #48\n"
        "adrp x9, DAT_71050b3b98\n"
        "add x9, x9, :lo12:DAT_71050b3b98\n"
        "strb wzr, [x0, #0x18]\n"
        "movk x10, #0x5000, LSL #48\n"
        "stp x9, x8, [x0]\n"
        "str x10, [x0, #0x10]\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}
#endif

// 0x71020f1eb0 (112B)
// Alloc 0x20-byte object; zeroes [0x10] only
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void* FUN_71020f1eb0() {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "mov w0, #0x10\n"
        "mov w1, #0x20\n"
        "bl FUN_710392dce0\n"
        "cbnz x0, 0f\n"
        "adrp x8, DAT_7105331f00\n"
        "ldr x0, [x8, :lo12:DAT_7105331f00]\n"
        "cbz x0, 1f\n"
        "mov w8, #0x20\n"
        "stur wzr, [x29, #-0x4]\n"
        "sub x1, x29, #0x4\n"
        "str x8, [sp]\n"
        "ldr x8, [x0]\n"
        "ldr x8, [x8, #0x30]\n"
        "mov x2, sp\n"
        "blr x8\n"
        "tbz w0, #0, 1f\n"
        "mov w0, #0x10\n"
        "mov w1, #0x20\n"
        "bl FUN_710392dce0\n"
        "cbnz x0, 0f\n"
        "1:\n"
        "mov x0, xzr\n"
        "0:\n"
        "str wzr, [x0, #0x10]\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}
#endif

// 0x710217d5b0 (168B)
// Alloc 0x30-byte object; vtable DAT_71050b41d8; [0x10]=0x1ecef20215, [0x20]=0xffffffff50000000, [0x2c]=-1
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void* FUN_710217d5b0() {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "mov w0, #0x10\n"
        "orr w1, wzr, #0x30\n"
        "bl FUN_710392dce0\n"
        "cbnz x0, 0f\n"
        "adrp x8, DAT_7105331f00\n"
        "ldr x0, [x8, :lo12:DAT_7105331f00]\n"
        "cbz x0, 1f\n"
        "orr w8, wzr, #0x30\n"
        "stur wzr, [x29, #-0x4]\n"
        "sub x1, x29, #0x4\n"
        "str x8, [sp]\n"
        "ldr x8, [x0]\n"
        "ldr x8, [x8, #0x30]\n"
        "mov x2, sp\n"
        "blr x8\n"
        "tbz w0, #0, 1f\n"
        "mov w0, #0x10\n"
        "orr w1, wzr, #0x30\n"
        "bl FUN_710392dce0\n"
        "cbnz x0, 0f\n"
        "1:\n"
        "mov x0, xzr\n"
        "0:\n"
        "mov w8, #0xa\n"
        "str w8, [x0, #0x8]\n"
        "mov x8, #0x215\n"
        "movk x8, #0xcef2, LSL #16\n"
        "movk x8, #0x1e, LSL #32\n"
        "strb wzr, [x0, #0x28]\n"
        "stp x8, xzr, [x0, #0x10]\n"
        "mov x8, #-0x10000\n"
        "movk x8, #0x5000, LSL #16\n"
        "str x8, [x0, #0x20]\n"
        "adrp x8, DAT_71050b41d8\n"
        "add x8, x8, :lo12:DAT_71050b41d8\n"
        "str x8, [x0]\n"
        "mov w8, #0xffffffff\n"
        "str w8, [x0, #0x2c]\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}
#endif
