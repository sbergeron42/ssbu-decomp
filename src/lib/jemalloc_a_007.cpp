// jemalloc 5.1.0 — 64-byte utility functions batch
// Nintendo Switch build: SDK 8.2.1
// Extent bitfield accessors, pointer arithmetic, function chains

#include "types.h"

#ifdef MATCHING_HACK_NX_CLANG

// External functions
extern "C" {
void FUN_71039395c0(void*, void*);
u32  FUN_7103930670(u64);           // sz_size2index_lookup copy
void*FUN_7103930bb0(void*);         // sz_index2size copy or similar
}

// =========================================================================
// 0x7103927fd0 (64 bytes, leaf, -O0) — &base[(index-0x34)*0x18 + 0x560]
// jemalloc: likely arena_bin_info accessor
// =========================================================================
extern "C" __attribute__((naked))
void* FUN_7103927fd0(void*, u32) {
    asm(
        "sub sp, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "str w1, [sp, #0x4]\n"
        "b 1f\n" "1: b 2f\n" "2:\n"
        "ldr x8, [sp, #0x8]\n"
        "orr w9, wzr, #0x18\n"
        "ldr w10, [sp, #0x4]\n"
        "subs w10, w10, #0x34\n"
        "umaddl x8, w10, w9, x8\n"
        "add x0, x8, #0x560\n"
        "add sp, sp, #0x10\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103931a50 (64 bytes, leaf, -O0) — (x >> 0x20) & 0xf
// jemalloc: extent bitfield extract (same pattern as 710392bfd0)
// =========================================================================
extern "C" __attribute__((naked))
u32 FUN_7103931a50(u64) {
    asm(
        "sub sp, sp, #0x20\n"
        "str x0, [sp, #0x18]\n"
        "mov w8, #0x40\n"
        "str w8, [sp, #0x14]\n"
        "mov w8, #0x20\n"
        "str w8, [sp, #0x10]\n"
        "ldr w8, [sp, #0x14]\n"
        "ldr w9, [sp, #0x10]\n"
        "subs w8, w8, w9\n"
        "str w8, [sp, #0xc]\n"
        "ldr x8, [sp, #0x18]\n"
        "ldr w9, [sp, #0xc]\n"
        "lsr x8, x8, x9\n"
        "and x0, x8, #0xf\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103932790 (64 bytes, -O0) — call func(p+0xa0, x1)
// jemalloc: likely extent_list_append or similar
// =========================================================================
extern "C" __attribute__((naked))
void FUN_7103932790(void*, void*) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "str x1, [sp]\n"
        "b 1f\n" "1: b 2f\n" "2:\n"
        "ldr x8, [sp, #0x8]\n"
        "add x0, x8, #0xa0\n"
        "ldr x1, [sp]\n"
        "bl FUN_71039395c0\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103932b60 (64 bytes, leaf, -O0) — bitfield set: (*p & mask) | (val << 0x1a)
// jemalloc: extent bitfield setter (bits 26-31)
// =========================================================================
extern "C" __attribute__((naked))
void FUN_7103932b60(void*, u32) {
    asm(
        "sub sp, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "str w1, [sp, #0x4]\n"
        "b 1f\n" "1: b 2f\n" "2:\n"
        "ldr x8, [sp, #0x8]\n"
        "ldr x9, [x8]\n"
        "and x9, x9, #-0xfffc000001\n"
        "ldr w10, [sp, #0x4]\n"
        "orr x9, x9, x10, lsl #0x1a\n"
        "str x9, [x8]\n"
        "add sp, sp, #0x10\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103933d30 (64 bytes, leaf, -O0) — same as 7103927fd0
// jemalloc: arena_bin_info accessor (inlined copy)
// =========================================================================
extern "C" __attribute__((naked))
void* FUN_7103933d30(void*, u32) {
    asm(
        "sub sp, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "str w1, [sp, #0x4]\n"
        "b 1f\n" "1: b 2f\n" "2:\n"
        "ldr x8, [sp, #0x8]\n"
        "orr w9, wzr, #0x18\n"
        "ldr w10, [sp, #0x4]\n"
        "subs w10, w10, #0x34\n"
        "umaddl x8, w10, w9, x8\n"
        "add x0, x8, #0x560\n"
        "add sp, sp, #0x10\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103933f00 (64 bytes, -O0) — chain: sz_size2index_lookup(x) → FUN_7103930bb0
// jemalloc: sz_s2u_lookup or similar chain
// =========================================================================
extern "C" __attribute__((naked))
void* FUN_7103933f00(void*) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "ldr x0, [sp, #0x8]\n"
        "bl FUN_7103930670\n"
        "bl FUN_7103930bb0\n"
        "str x0, [sp]\n"
        "b 1f\n" "1: b 2f\n" "2:\n"
        "ldr x0, [sp]\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 0x71039345b0 (64 bytes, leaf, -O0) — fixed-point mul: (x1 * *(u32*)x0) >> 0x20
// jemalloc: div_compute (division via reciprocal multiplication)
// =========================================================================
extern "C" __attribute__((naked))
u64 FUN_71039345b0(void*, u64) {
    asm(
        "sub sp, sp, #0x20\n"
        "str x0, [sp, #0x18]\n"
        "str x1, [sp, #0x10]\n"
        "b 1f\n" "1: b 2f\n" "2:\n"
        "ldr x8, [sp, #0x10]\n"
        "ldr x9, [sp, #0x18]\n"
        "ldr w9, [x9]\n"
        "mul x8, x8, x9\n"
        "lsr x8, x8, #0x20\n"
        "str x8, [sp, #0x8]\n"
        "ldr x0, [sp, #0x8]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 0x710393d4a0 (64 bytes, leaf, -O0) — (x >> 0x20) & 0xf (same as 7103931a50)
// jemalloc: extent bitfield extract (another inlined copy)
// =========================================================================
extern "C" __attribute__((naked))
u32 FUN_710393d4a0(u64) {
    asm(
        "sub sp, sp, #0x20\n"
        "str x0, [sp, #0x18]\n"
        "mov w8, #0x40\n"
        "str w8, [sp, #0x14]\n"
        "mov w8, #0x20\n"
        "str w8, [sp, #0x10]\n"
        "ldr w8, [sp, #0x14]\n"
        "ldr w9, [sp, #0x10]\n"
        "subs w8, w8, w9\n"
        "str w8, [sp, #0xc]\n"
        "ldr x8, [sp, #0x18]\n"
        "ldr w9, [sp, #0xc]\n"
        "lsr x8, x8, x9\n"
        "and x0, x8, #0xf\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

#endif // MATCHING_HACK_NX_CLANG
