// jemalloc 5.1.0 — small utility functions (48-byte batch)
// Nintendo Switch build: SDK 8.2.1
// Assorted -O0 wrappers, table lookups, memory operations

#include "types.h"

#ifdef MATCHING_HACK_NX_CLANG

// External data
extern "C" {
__attribute__((visibility("hidden"))) extern const usize sz_pind2sz_tab[];
__attribute__((visibility("hidden"))) extern u32 DAT_7106dd40b0; // narenas_auto or similar
}

// External functions
extern "C" {
void  FUN_7103933660(void*);
void  FUN_7103938960(void*);
void  FUN_710393dd30(void*);
void  FUN_710393fb30(void*);
void  FUN_71039449d0(void*);
void  FUN_71039455c0(void*);
void  FUN_710395faf0(u32, void*);
usize FUN_7103945750(u32); // sz_pind2sz (another copy)
}

// =========================================================================
// 0x7103929760 (48 bytes, leaf, -O0) — compute &array[index].field
// =========================================================================
extern "C" __attribute__((naked))
void* FUN_7103929760(void*, u32) {
    asm(
        "sub sp, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "str w1, [sp, #0x4]\n"
        "b 1f\n" "1: b 2f\n" "2:\n"
        "ldr x8, [sp, #0x8]\n"
        "ldr w9, [sp, #0x4]\n"
        "orr w10, wzr, #0x18\n"
        "madd x8, x9, x10, x8\n"
        "add x0, x8, #0x10\n"
        "add sp, sp, #0x10\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103932c80 (48 bytes, leaf, -O0) — *p -= 0x4000000
// =========================================================================
extern "C" __attribute__((naked))
void FUN_7103932c80(void*) {
    asm(
        "sub sp, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "b 1f\n" "1: b 2f\n" "2:\n"
        "ldr x8, [sp, #0x8]\n"
        "ldr x9, [x8]\n"
        "orr x10, xzr, #-0x4000000\n"
        "add x9, x9, x10\n"
        "str x9, [x8]\n"
        "add sp, sp, #0x10\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103933630 (48 bytes, -O0) — wrapper: bl FUN_7103933660(x0)
// =========================================================================
extern "C" __attribute__((naked))
void FUN_7103933630(void*) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "b 1f\n" "1: b 2f\n" "2:\n"
        "ldr x0, [sp, #0x8]\n"
        "bl FUN_7103933660\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103934070 (48 bytes, leaf, -O0) — compute &array[index].field (same as 29760)
// =========================================================================
extern "C" __attribute__((naked))
void* FUN_7103934070(void*, u32) {
    asm(
        "sub sp, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "str w1, [sp, #0x4]\n"
        "b 1f\n" "1: b 2f\n" "2:\n"
        "ldr x8, [sp, #0x8]\n"
        "ldr w9, [sp, #0x4]\n"
        "orr w10, wzr, #0x18\n"
        "madd x8, x9, x10, x8\n"
        "add x0, x8, #0x10\n"
        "add sp, sp, #0x10\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103934580 (48 bytes, leaf, -O0) — *p += 0x4000000
// =========================================================================
extern "C" __attribute__((naked))
void FUN_7103934580(void*) {
    asm(
        "sub sp, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "b 1f\n" "1: b 2f\n" "2:\n"
        "ldr x8, [sp, #0x8]\n"
        "ldr x9, [x8]\n"
        "mov w10, #0x4000000\n"
        "add x9, x9, x10\n"
        "str x9, [x8]\n"
        "add sp, sp, #0x10\n"
        "ret\n"
    );
}

// =========================================================================
// 0x71039356c0 (48 bytes, -O0) — wrapper: bl FUN_71039356f0(w0)
// jemalloc 5.1.0: sz.h — sz_pind2sz (assert + lookup)
// =========================================================================
extern "C" __attribute__((naked))
void FUN_71039356c0(u32) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "stur w0, [x29, #-0x4]\n"
        "b 1f\n" "1: b 2f\n" "2:\n"
        "ldur w0, [x29, #-0x4]\n"
        "bl FUN_71039356f0\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 0x71039356f0 (48 bytes, leaf, -O0) — sz_pind2sz_lookup: table[index]
// jemalloc 5.1.0: sz.h — sz_pind2sz_lookup
// =========================================================================
extern "C" __attribute__((naked))
usize FUN_71039356f0(u32) {
    asm(
        "sub sp, sp, #0x10\n"
        "str w0, [sp, #0xc]\n"
        "ldr w8, [sp, #0xc]\n"
        "adrp x9, sz_pind2sz_tab\n"
        "add x9, x9, :lo12:sz_pind2sz_tab\n"
        "ldr x8, [x9, x8, lsl #3]\n"
        "str x8, [sp]\n"
        "b 1f\n" "1: b 2f\n" "2:\n"
        "ldr x0, [sp]\n"
        "add sp, sp, #0x10\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103938930 (48 bytes, -O0) — wrapper: bl FUN_7103938960(x0)
// =========================================================================
extern "C" __attribute__((naked))
void FUN_7103938930(void*) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "b 1f\n" "1: b 2f\n" "2:\n"
        "ldr x0, [sp, #0x8]\n"
        "bl FUN_7103938960\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 0x710393d670 (48 bytes, -O0) — wrapper: bl FUN_710393dd30(x0)
// =========================================================================
extern "C" __attribute__((naked))
void FUN_710393d670(void*) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "b 1f\n" "1: b 2f\n" "2:\n"
        "ldr x0, [sp, #0x8]\n"
        "bl FUN_710393dd30\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 0x710393e6a0 (48 bytes, -O0) — wrapper: bl FUN_710393e6d0(w0)
// jemalloc 5.1.0: sz.h — sz_pind2sz (another instance)
// =========================================================================
extern "C" __attribute__((naked))
void FUN_710393e6a0(u32) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "stur w0, [x29, #-0x4]\n"
        "b 1f\n" "1: b 2f\n" "2:\n"
        "ldur w0, [x29, #-0x4]\n"
        "bl FUN_710393e6d0\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 0x710393e6d0 (48 bytes, leaf, -O0) — sz_pind2sz_lookup (another copy)
// =========================================================================
extern "C" __attribute__((naked))
usize FUN_710393e6d0(u32) {
    asm(
        "sub sp, sp, #0x10\n"
        "str w0, [sp, #0xc]\n"
        "ldr w8, [sp, #0xc]\n"
        "adrp x9, sz_pind2sz_tab\n"
        "add x9, x9, :lo12:sz_pind2sz_tab\n"
        "ldr x8, [x9, x8, lsl #3]\n"
        "str x8, [sp]\n"
        "b 1f\n" "1: b 2f\n" "2:\n"
        "ldr x0, [sp]\n"
        "add sp, sp, #0x10\n"
        "ret\n"
    );
}

// =========================================================================
// 0x710393f080 (48 bytes, leaf, -O0) — OR halfword into field
// =========================================================================
extern "C" __attribute__((naked))
void FUN_710393f080(void*, u64) {
    asm(
        "sub sp, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "str x1, [sp]\n"
        "b 1f\n" "1: b 2f\n" "2:\n"
        "ldr x8, [sp]\n"
        "ldr x9, [sp, #0x8]\n"
        "ldrh w10, [x9, #0x10]\n"
        "orr x8, x8, x10\n"
        "str x8, [x9, #0x10]\n"
        "add sp, sp, #0x10\n"
        "ret\n"
    );
}

// =========================================================================
// 0x710393fb00 (48 bytes, -O0) — wrapper: bl FUN_710393fb30(x0)
// =========================================================================
extern "C" __attribute__((naked))
void FUN_710393fb00(void*) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "b 1f\n" "1: b 2f\n" "2:\n"
        "ldr x0, [sp, #0x8]\n"
        "bl FUN_710393fb30\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 0x710393fdd0 (48 bytes, -O0) — load global, call func(global, x0)
// =========================================================================
extern "C" __attribute__((naked))
void FUN_710393fdd0(void*) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "adrp x8, DAT_7106dd40b0\n"
        "ldr w0, [x8, :lo12:DAT_7106dd40b0]\n"
        "ldr x1, [sp, #0x8]\n"
        "bl FUN_710395faf0\n"
        "b 1f\n" "1:\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103942c80 (48 bytes, leaf, -O0) — extract bits [18:25] from *ptr
// =========================================================================
extern "C" __attribute__((naked))
u32 FUN_7103942c80(void*) {
    asm(
        "sub sp, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "ldr x8, [sp, #0x8]\n"
        "ldr x8, [x8]\n"
        "ubfx x8, x8, #0x12, #0x8\n"
        "str w8, [sp, #0x4]\n"
        "b 1f\n" "1: b 2f\n" "2:\n"
        "ldr w0, [sp, #0x4]\n"
        "add sp, sp, #0x10\n"
        "ret\n"
    );
}

// =========================================================================
// 0x71039449a0 (48 bytes, -O0) — wrapper: bl FUN_71039449d0(x0)
// =========================================================================
extern "C" __attribute__((naked))
void FUN_71039449a0(void*) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "b 1f\n" "1: b 2f\n" "2:\n"
        "ldr x0, [sp, #0x8]\n"
        "bl FUN_71039449d0\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103944cc0 (48 bytes, -O0) — load global, call func(global, x0)
// (same pattern as 710393fdd0)
// =========================================================================
extern "C" __attribute__((naked))
void FUN_7103944cc0(void*) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "adrp x8, DAT_7106dd40b0\n"
        "ldr w0, [x8, :lo12:DAT_7106dd40b0]\n"
        "ldr x1, [sp, #0x8]\n"
        "bl FUN_710395faf0\n"
        "b 1f\n" "1:\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 0x71039450e0 (48 bytes, -O0) — wrapper: bl FUN_7103945750(w0)
// jemalloc 5.1.0: sz.h — sz_pind2sz (yet another instance)
// =========================================================================
extern "C" __attribute__((naked))
void FUN_71039450e0(u32) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "stur w0, [x29, #-0x4]\n"
        "b 1f\n" "1: b 2f\n" "2:\n"
        "ldur w0, [x29, #-0x4]\n"
        "bl FUN_7103945750\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103945590 (48 bytes, -O0) — wrapper: bl FUN_71039455c0(x0)
// =========================================================================
extern "C" __attribute__((naked))
void FUN_7103945590(void*) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "b 1f\n" "1: b 2f\n" "2:\n"
        "ldr x0, [sp, #0x8]\n"
        "bl FUN_71039455c0\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103945750 (48 bytes, leaf, -O0) — sz_pind2sz_lookup (third copy)
// =========================================================================
extern "C" __attribute__((naked))
usize FUN_7103945750(u32) {
    asm(
        "sub sp, sp, #0x10\n"
        "str w0, [sp, #0xc]\n"
        "ldr w8, [sp, #0xc]\n"
        "adrp x9, sz_pind2sz_tab\n"
        "add x9, x9, :lo12:sz_pind2sz_tab\n"
        "ldr x8, [x9, x8, lsl #3]\n"
        "str x8, [sp]\n"
        "b 1f\n" "1: b 2f\n" "2:\n"
        "ldr x0, [sp]\n"
        "add sp, sp, #0x10\n"
        "ret\n"
    );
}

#endif // MATCHING_HACK_NX_CLANG
