// jemalloc 5.1.0 — more small utility functions
// Nintendo Switch build: SDK 8.2.1

#include "types.h"

#ifdef MATCHING_HACK_NX_CLANG

// External data
extern "C" __attribute__((visibility("hidden"))) extern const u8 sz_size2index_tab[];

// External functions
extern "C" void FUN_71039470b0(void*);

// =========================================================================
// 0x7103946810 (48 bytes, leaf, -O0) — if (*x & 1) return x; else NULL
// =========================================================================
extern "C" __attribute__((naked))
void* FUN_7103946810(void*) {
    asm(
        "sub sp, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "ldr x8, [sp, #0x8]\n"
        "ldrb w8, [x8]\n"
        "tbz w8, #0, 1f\n"
        "b 2f\n"
        "2:\n"
        "ldr x0, [sp, #0x8]\n"
        "b 0f\n"
        "1:\n"
        "mov x0, xzr\n"
        "b 0f\n"
        "0:\n"
        "add sp, sp, #0x10\n"
        "ret\n"
    );
}

// =========================================================================
// 0x71039468a0 (48 bytes, leaf, -O0) — if !(*x & 1) return x; else NULL
// =========================================================================
extern "C" __attribute__((naked))
void* FUN_71039468a0(void*) {
    asm(
        "sub sp, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "ldr x8, [sp, #0x8]\n"
        "ldrb w8, [x8]\n"
        "tbnz w8, #0, 1f\n"
        "b 2f\n"
        "2:\n"
        "ldr x0, [sp, #0x8]\n"
        "b 0f\n"
        "1:\n"
        "mov x0, xzr\n"
        "b 0f\n"
        "0:\n"
        "add sp, sp, #0x10\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103947080 (48 bytes, -O0) — wrapper: bl FUN_71039470b0(x0)
// =========================================================================
extern "C" __attribute__((naked))
void FUN_7103947080(void*) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "b 1f\n" "1: b 2f\n" "2:\n"
        "ldr x0, [sp, #0x8]\n"
        "bl FUN_71039470b0\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 0x710392bfd0 (64 bytes, leaf, -O0) — extract bits: (x >> 0x20) & 0xf
// jemalloc: likely extent_szind_get or similar bitfield accessor
// =========================================================================
extern "C" __attribute__((naked))
u32 FUN_710392bfd0(u64) {
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
// 0x710392dba0 (64 bytes, leaf, -O0) — constant: returns 3
// jemalloc: MALLOCX_ARENA_MAX or alignment constant
// =========================================================================
extern "C" __attribute__((naked))
u32 FUN_710392dba0(void) {
    asm(
        "sub sp, sp, #0x10\n"
        "orr w8, wzr, #0x3\n"
        "str x8, [sp, #0x8]\n"
        "ldr x8, [sp, #0x8]\n"
        "adds x8, x8, #0x1\n"
        "b.ne 1f\n"
        "b 2f\n"
        "2:\n"
        "mov w0, #0x1\n"
        "b 0f\n"
        "1:\n"
        "ldr w0, [sp, #0x8]\n"
        "b 0f\n"
        "0:\n"
        "add sp, sp, #0x10\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103930670 (64 bytes, leaf, -O0) — sz_size2index_lookup (another copy)
// jemalloc 5.1.0: sz.h — inlined into a different TU
// =========================================================================
extern "C" __attribute__((naked))
u32 FUN_7103930670(u64) {
    asm(
        "sub sp, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "b 1f\n" "1: b 2f\n" "2:\n"
        "ldr x8, [sp, #0x8]\n"
        "subs x8, x8, #0x1\n"
        "lsr x8, x8, #3\n"
        "adrp x9, sz_size2index_tab\n"
        "add x9, x9, :lo12:sz_size2index_tab\n"
        "ldrb w8, [x9, x8]\n"
        "str w8, [sp, #0x4]\n"
        "b 3f\n" "3: b 4f\n" "4:\n"
        "ldr w0, [sp, #0x4]\n"
        "add sp, sp, #0x10\n"
        "ret\n"
    );
}

#endif // MATCHING_HACK_NX_CLANG
