// jemalloc 5.1.0 — malloc entry points, arena helpers, ctl
// Nintendo Switch build: SDK 8.2.1
// Source: jemalloc.c, arena.c, ctl.c

#include "types.h"

#ifdef MATCHING_HACK_NX_CLANG

// External functions
extern "C" {
void* tsd_fetch_impl(u8, u8);
void* tsd_tsdn(void*);
u8    tsd_booted_get(void);
u8    FUN_71039277b0(void);        // malloc_initialized (check init flag)
void* malloc_init_hard(void);      // 0x710392d370
void* FUN_710392ba50(void*, void*); // arena helper
u32   FUN_710392e9d0(void*, void*, void*); // arena_salloc inner
usize sz_index2size(u32);          // 0x7103928170
void* FUN_71039bfba0(void);       // __errno (returns &errno)
}

// =========================================================================
// jemalloc 5.1.0: tsd.h — check_entry_exit_locking (no-op assert stub)
// 0x710392acb0 (16 bytes, leaf, -O0)
// =========================================================================
extern "C" __attribute__((naked))
void check_entry_exit_locking(void*) {
    asm(
        "sub sp, sp, #0x20\n"
        "str x0, [sp, #0x18]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// jemalloc 5.1.0: jemalloc.c — set_errno (write errno via __errno())
// 0x710392b1e0 (48 bytes, -O0)
// Calls: FUN_71039bfba0 (__errno)
// =========================================================================
extern "C" __attribute__((naked))
void set_errno(u32) {
    asm(
        "str x19, [sp, #-0x20]!\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "stur w0, [x29, #-0x4]\n"
        "ldur w19, [x29, #-0x4]\n"
        "bl FUN_71039bfba0\n"          // __errno()
        "str w19, [x0]\n"              // *errno = val
        "ldp x29, x30, [sp, #0x10]\n"
        "ldr x19, [sp], #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// jemalloc 5.1.0: jemalloc.c — isalloc (assert wrapper → arena_salloc)
// 0x710392e920 (64 bytes, -O0)
// Calls: arena_salloc (0x710392e960)
// =========================================================================
extern "C" __attribute__((naked))
u64 isalloc(void*, void*) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "str x1, [sp]\n"
        "b 1f\n"
        "1: b 2f\n"
        "2:\n"
        "ldr x0, [sp, #0x8]\n"
        "ldr x1, [sp]\n"
        "bl arena_salloc\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// jemalloc 5.1.0: tsd.h — tsdn_fetch
// 0x710392ac60 (80 bytes, -O0)
// Calls: tsd_booted_get, tsd_fetch_impl, tsd_tsdn
// =========================================================================
extern "C" __attribute__((naked))
void* tsdn_fetch(void) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        // if (!tsd_booted_get()) return NULL
        "bl tsd_booted_get\n"
        "tbnz w0, #0, 1f\n"
        "b 2f\n"
        "2:\n"
        "str xzr, [sp, #0x8]\n"
        "b 0f\n"
        // tsd = tsd_fetch_impl(false, false), return tsd_tsdn(tsd)
        "1:\n"
        "mov w0, wzr\n"
        "mov w1, wzr\n"
        "bl tsd_fetch_impl\n"
        "bl tsd_tsdn\n"
        "str x0, [sp, #0x8]\n"
        "b 0f\n"
        "0:\n"
        "ldr x0, [sp, #0x8]\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// jemalloc 5.1.0: jemalloc.c — malloc_init (check init, call hard if needed)
// 0x710392ca70 (80 bytes, -O0)
// Calls: FUN_71039277b0 (malloc_initialized), malloc_init_hard
// =========================================================================
extern "C" __attribute__((naked))
u8 malloc_init(void) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        // if (malloc_initialized()) return false
        "bl FUN_71039277b0\n"
        "tbnz w0, #0, 0f\n"
        "b 1f\n"
        "1:\n"
        // if (malloc_init_hard()) return true
        "bl malloc_init_hard\n"
        "tbz w0, #0, 0f\n"
        "b 2f\n"
        "2:\n"
        "mov w8, #0x1\n"
        "sturb w8, [x29, #-0x1]\n"
        "b 3f\n"
        "0:\n"
        "sturb wzr, [x29, #-0x1]\n"
        "b 3f\n"
        "3:\n"
        "ldurb w0, [x29, #-0x1]\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// jemalloc 5.1.0: arena.c — arena_salloc
// 0x710392e960 (112 bytes, -O0)
// Uses x28,x19 callee-saved; calls FUN_710392ba50, FUN_710392e9d0, sz_index2size
// =========================================================================
extern "C" __attribute__((naked))
usize arena_salloc(void*, void*) {
    asm(
        "sub sp, sp, #0x1c0\n"
        "stp x28, x19, [sp, #0x1a0]\n"
        "stp x29, x30, [sp, #0x1b0]\n"
        "add x29, sp, #0x1b0\n"
        "sub x19, x29, #0x20\n"
        "str x0, [x19, #0x8]\n"
        "str x1, [x19]\n"
        "b 1f\n"
        "1: b 2f\n"
        "2:\n"
        "ldr x0, [x19, #0x8]\n"
        "add x1, sp, #0x10\n"
        "bl FUN_710392ba50\n"
        "str x0, [sp, #0x8]\n"
        "ldr x0, [x19, #0x8]\n"
        "ldr x1, [sp, #0x8]\n"
        "ldr x2, [x19]\n"
        "bl FUN_710392e9d0\n"
        "str w0, [sp, #0x4]\n"
        "b 3f\n"
        "3: b 4f\n"
        "4:\n"
        "ldr w0, [sp, #0x4]\n"
        "bl sz_index2size\n"
        "ldp x29, x30, [sp, #0x1b0]\n"
        "ldp x28, x19, [sp, #0x1a0]\n"
        "add sp, sp, #0x1c0\n"
        "ret\n"
    );
}

#endif // MATCHING_HACK_NX_CLANG
