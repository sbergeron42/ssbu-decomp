// jemalloc 5.1.0 — thread-specific data (TSD) functions
// Nintendo Switch build: SDK 8.2.1
// Source: tsd.h, tsd.c (tsd_fetch_impl, tsd_fast, tsd_fetch, etc.)

#include "types.h"

#ifdef MATCHING_HACK_NX_CLANG

// External functions referenced by tsd_fetch_impl
extern "C" {
void* FUN_710392ad80(u8);  // tsd_get / pthread_getspecific wrapper
void  FUN_710392ae00(void); // tsd_slow_update
void* FUN_710395ebc0(void*, u8); // tsd_fetch_slow
void  tsd_assert_fast(void*);
void* tsd_fetch_impl(u8, u8);
}

// External data
extern "C" __attribute__((visibility("hidden"))) u8 tsd_booted;

// =========================================================================
// jemalloc 5.1.0: tsd.h — tsd_tsdn (identity cast: tsd_t* -> tsdn_t*)
// 0x71039280f0 (32 bytes, leaf, -O0)
// =========================================================================
extern "C" __attribute__((naked))
void* tsd_tsdn(void*) {
    asm(
        "sub sp, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "ldr x0, [sp, #0x8]\n"
        "add sp, sp, #0x10\n"
        "ret\n"
    );
}

// =========================================================================
// jemalloc 5.1.0: tsd.h — tsd_booted_get (read global bool)
// 0x710392acc0 (16 bytes, leaf, -O2)
// =========================================================================
extern "C" __attribute__((naked))
u8 tsd_booted_get(void) {
    asm(
        "adrp x8, tsd_booted\n"
        "ldrb w0, [x8, :lo12:tsd_booted]\n"
        "ret\n"
    );
}

// =========================================================================
// jemalloc 5.1.0: tsd.h — tsd_assert_fast (debug assert, no-op in release)
// 0x710392ae10 (32 bytes, leaf, -O0)
// =========================================================================
extern "C" __attribute__((naked))
void tsd_assert_fast(void*) {
    asm(
        "sub sp, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "b 1f\n"
        "1: b 2f\n"
        "2:\n"
        "add sp, sp, #0x10\n"
        "ret\n"
    );
}

// =========================================================================
// jemalloc 5.1.0: tsd.c — tsd_fetch_impl
// 0x710392acd0 (176 bytes, -O0)
// Calls: FUN_710392ad80 (tsd_get), FUN_710392ae00 (tsd_slow_update),
//        FUN_710395ebc0 (tsd_fetch_slow), tsd_assert_fast
// =========================================================================
extern "C" __attribute__((naked))
void* tsd_fetch_impl(u8, u8) {
    asm(
        "sub sp, sp, #0x30\n"
        "stp x29, x30, [sp, #0x20]\n"
        "add x29, sp, #0x20\n"
        "and w8, w0, #0x1\n"
        "sturb w8, [x29, #-0xc]\n"
        "and w8, w1, #0x1\n"
        "strb w8, [sp, #0x10]\n"
        // tsd = tsd_get(minimal)
        "ldurb w8, [x29, #-0xc]\n"
        "and w0, w8, #0x1\n"
        "bl FUN_710392ad80\n"
        "str x0, [sp, #0x8]\n"
        // if (!minimal)
        "ldurb w8, [x29, #-0xc]\n"
        "tbnz w8, #0, 1f\n"
        "b 2f\n"
        "2:\n"
        "bl FUN_710392ae00\n"           // tsd_slow_update
        "b 3f\n"
        "3:\n"
        // if (tsd == NULL)
        "ldr x8, [sp, #0x8]\n"
        "cbnz x8, 1f\n"
        "b 4f\n"
        "4:\n"
        "stur xzr, [x29, #-0x8]\n"     // return NULL
        "b 0f\n"
        // tsd != NULL path
        "1:\n"
        "b 5f\n"
        "5: b 6f\n"
        "6:\n"
        // if (*tsd != 0) — check tsd->state
        "ldr x8, [sp, #0x8]\n"
        "ldrb w8, [x8]\n"
        "cbz w8, 7f\n"
        "b 8f\n"
        "8:\n"
        // tsd_fetch_slow(tsd, try_fast)
        "ldr x0, [sp, #0x8]\n"
        "ldrb w8, [sp, #0x10]\n"
        "and w1, w8, #0x1\n"
        "bl FUN_710395ebc0\n"
        "stur x0, [x29, #-0x8]\n"
        "b 0f\n"
        // tsd->state == 0 (fast path)
        "7:\n"
        "b 9f\n"
        "9: b 10f\n"
        "10:\n"
        "ldr x0, [sp, #0x8]\n"
        "bl tsd_assert_fast\n"
        "ldr x8, [sp, #0x8]\n"
        "stur x8, [x29, #-0x8]\n"
        "b 0f\n"
        // Return
        "0:\n"
        "ldur x0, [x29, #-0x8]\n"
        "ldp x29, x30, [sp, #0x20]\n"
        "add sp, sp, #0x30\n"
        "ret\n"
    );
}

// =========================================================================
// jemalloc 5.1.0: tsd.h — tsd_fetch (wrapper: fetch_impl(true, false))
// 0x710392cac0 (32 bytes, -O2)
// =========================================================================
extern "C" __attribute__((naked))
void* tsd_fetch(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "mov w0, #0x1\n"
        "mov w1, wzr\n"
        "bl tsd_fetch_impl\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}

// =========================================================================
// jemalloc 5.1.0: tsd.h — tsd_fast (check tsd state == 0)
// 0x710392cae0 (80 bytes, -O0)
// Calls: tsd_assert_fast
// =========================================================================
extern "C" __attribute__((naked))
u8 tsd_fast(void*) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "ldr x8, [sp, #0x8]\n"
        "ldrb w8, [x8]\n"
        "subs w8, w8, #0x0\n"
        "cset w8, eq\n"
        "strb w8, [sp, #0x4]\n"
        "ldrb w8, [sp, #0x4]\n"
        "tbz w8, #0, 0f\n"
        "b 1f\n"
        "1:\n"
        "ldr x0, [sp, #0x8]\n"
        "bl tsd_assert_fast\n"
        "b 0f\n"
        "0:\n"
        "ldrb w8, [sp, #0x4]\n"
        "and w0, w8, #0x1\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// jemalloc 5.1.0: tsd.h — tsd_fetch_min (wrapper: fetch_impl(true, true))
// 0x710392e670 (32 bytes, -O2)
// =========================================================================
extern "C" __attribute__((naked))
void* tsd_fetch_min(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "mov w0, #0x1\n"
        "mov w1, #0x1\n"
        "bl tsd_fetch_impl\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}

#endif // MATCHING_HACK_NX_CLANG
