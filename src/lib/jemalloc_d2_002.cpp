// jemalloc 5.1.0 — wrappers + tsd_get + prof (pool-d, round 3 batch 2)
// Address range: 0x710392xxxx
// All compiled at -O0 in NX build; naked asm for byte-exact match.
// jemalloc 5.1.0: tsd.h, jemalloc.c, prof.h, bits.h

#include "types.h"

#ifdef MATCHING_HACK_NX_CLANG

// External functions
extern "C" {
void* FUN_7103927800(void*);    // malloc_init check
void* FUN_71039297e0(void*);    // tsd accessor wrapper (+0x3)
void* FUN_7103928590(u64);      // pow2_ceil_u64 (in pool-a jemalloc_a_001)
u32   FUN_7103928560(u64);      // ffs_u64 inner (calls __builtin_ctzll)
void* FUN_71039c7d10(u64);      // __builtin_ctzll equivalent
void* FUN_710392c6b0(void*);    // extent field accessor +0x1b8
void  FUN_7103956fa0(const char*, ...);  // malloc_printf
void  abortWrapper_71039c20a0(void);     // abort
void* FUN_710392ac60(void);     // tsdn_fetch (in pool-a)
void  FUN_710392acb0(void*);    // check_entry_exit_locking (in pool-a)
void  FUN_7103958900(void*, void*, void*); // tsd_boot0 helper
void* FUN_710395fba0(u32);      // pthread_getspecific
void* FUN_710395f070(void*, void*); // pthread_key_create
void* FUN_710395f1e0(void);     // base_alloc for tsd
void  FUN_7103954000(const char*, ...); // malloc_write
void  FUN_710392af50(void*);    // tsd_set (pthread_setspecific wrapper)
void* FUN_710395f240(void*, void*); // cleanup install
void* FUN_710395faf0(u32, void*);  // pthread_setspecific
void* FUN_71039292b0(void*, void*); // malloc_mutex_lock
void* FUN_71039293e0(void*, void*); // malloc_mutex_unlock
void* FUN_7103929ac0(void);     // prof_active atomic load
}

// External globals
extern "C" {
__attribute__((visibility("hidden"))) extern u32 DAT_7106dd40b0;  // tsd_tls_key
__attribute__((visibility("hidden"))) extern u8  DAT_7106dd40b4;  // tsd_booted
__attribute__((visibility("hidden"))) extern u32 DAT_71052934c8;  // prof_active (atomic)
}

// External string constants
extern "C" {
extern const char STR_710442e4e12[];  // "<jemalloc>: Error in ..."
extern const char STR_71044337f74[];  // jemalloc abort message
}

// =========================================================================
// 0x71039277d0 (48 bytes, -O0) — malloc_init wrapper
// jemalloc 5.1.0: jemalloc.c — wraps FUN_7103927800 (malloc_init_hard check)
// [derived: single-call forwarding pattern]
// =========================================================================
extern "C" __attribute__((naked))
void* FUN_71039277d0(void*) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "ldr x0, [sp, #0x8]\n"
        "bl FUN_7103927800\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103927b00 (48 bytes, -O0) — tsd_fast check
// jemalloc 5.1.0: tsd.h — calls tsd accessor, returns byte at result
// FUN_71039297e0 = tsd accessor wrapper (returns &tsd->field_0x3)
// [derived: call accessor, ldrb from result, returns bool]
// =========================================================================
extern "C" __attribute__((naked))
u8 FUN_7103927b00(void*) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "ldr x0, [sp, #0x8]\n"
        "bl FUN_71039297e0\n"
        "ldrb w0, [x0]\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103928450 (48 bytes, -O0) — pow2_ceil wrapper
// jemalloc 5.1.0: bits.h — wraps pow2_ceil_u64 (FUN_7103928590)
// [derived: single-call forwarding, used by lg_floor in sz_s2u_compute]
// =========================================================================
extern "C" __attribute__((naked))
void* FUN_7103928450(u64) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "ldr x0, [sp, #0x8]\n"
        "bl FUN_7103928590\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103928530 (48 bytes, -O0) — ffs_u64 wrapper
// jemalloc 5.1.0: bits.h — wraps FUN_7103928560 (__builtin_ctzll)
// [derived: single-call forwarding, called from lg_floor]
// =========================================================================
extern "C" __attribute__((naked))
u32 FUN_7103928530(u64) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "ldr x0, [sp, #0x8]\n"
        "bl FUN_7103928560\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103928560 (48 bytes, -O0) — ffs_u64 inner (__builtin_ctzll wrapper)
// jemalloc 5.1.0: bits.h — wraps FUN_71039c7d10 (ctzll)
// [derived: single-call forwarding to external]
// =========================================================================
extern "C" __attribute__((naked))
u32 FUN_7103928560(u64) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "ldr x0, [sp, #0x8]\n"
        "bl FUN_71039c7d10\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 0x710392c680 (48 bytes, -O0) — extent accessor wrapper for +0x1b8
// jemalloc 5.1.0: extent.h — wraps FUN_710392c6b0 (extent field +0x1b8)
// [derived: single-call forwarding with branch nops]
// =========================================================================
extern "C" __attribute__((naked))
void* FUN_710392c680(void*) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "b 1f\n"
        "1: b 2f\n"
        "2: ldr x0, [sp, #0x8]\n"
        "bl FUN_710392c6b0\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 0x710392b350 (32 bytes, noreturn) — malloc abort
// jemalloc 5.1.0: jemalloc.c — prints error message and aborts
// FUN_7103956fa0 = malloc_printf
// abortWrapper_71039c20a0 = abort
// STR_71044337f74 = abort message string
// [derived: adrp+add to .rodata string, bl printf, bl abort]
// =========================================================================
extern "C" __attribute__((naked))
void FUN_710392b350(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "b 1f\n"
        "1: b 2f\n"
        "2: adrp x0, STR_71044337f74\n"
        "add x0, x0, :lo12:STR_71044337f74\n"
        "bl FUN_7103956fa0\n"
        "bl abortWrapper_71039c20a0\n"
    );
}

// =========================================================================
// 0x710392af50 (48 bytes, -O0) — tsd_set (pthread_setspecific wrapper)
// jemalloc 5.1.0: tsd.h — calls pthread_setspecific(tsd_tls_key, val)
// DAT_7106dd40b0 = tsd_tls_key [derived: loaded as first arg to setspecific]
// FUN_710395faf0 = pthread_setspecific
// [derived: adrp+ldr global key, forward param as value]
// =========================================================================
extern "C" __attribute__((naked))
void FUN_710392af50(void*) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "adrp x8, DAT_7106dd40b0\n"
        "ldr w0, [x8, :lo12:DAT_7106dd40b0]\n"
        "ldr x1, [sp, #0x8]\n"
        "bl FUN_710395faf0\n"
        "b 1f\n"
        "1: ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103929a70 (80 bytes, -O0) — prof_active_get_unlocked
// jemalloc 5.1.0: prof.h — atomically reads prof_active flag
// DAT_71052934c8 = prof_active [derived: atomic bool, address from adrp+add]
// FUN_71039292b0 = atomic_load helper (lock)
// FUN_7103929ac0 = atomic_load_bool
// FUN_71039293e0 = atomic_load helper (unlock)
// [derived: lock-load-unlock pattern, returns bool]
// =========================================================================
extern "C" __attribute__((naked))
u8 FUN_7103929a70(void) {
    asm(
        "str x19, [sp, #-0x20]!\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "adrp x19, DAT_71052934c8\n"
        "add x19, x19, :lo12:DAT_71052934c8\n"
        "mov x0, xzr\n"
        "mov x1, x19\n"
        "bl FUN_71039292b0\n"
        "bl FUN_7103929ac0\n"
        "and w8, w0, #0x1\n"
        "sturb w8, [x29, #-0x4]\n"
        "mov x0, xzr\n"
        "mov x1, x19\n"
        "bl FUN_71039293e0\n"
        "ldurb w8, [x29, #-0x4]\n"
        "and w0, w8, #0x1\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "ldr x19, [sp], #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 0x710392ad80 (128 bytes, -O0) — tsd_get
// jemalloc 5.1.0: tsd.h — gets TSD pointer, optionally allocates
// FUN_710392ae30 = tsd_get_allocator (allocates TSD if needed)
// FUN_710392ae00 = nop (witness check)
// Returns tsd_t* + 0x8 (skips header) or NULL.
// [derived: init check, alloc path, +0x8 offset on return]
// =========================================================================
extern "C" __attribute__((naked))
void* FUN_710392ad80(u32) {
    asm(
        "sub sp, sp, #0x30\n"
        "stp x29, x30, [sp, #0x20]\n"
        "add x29, sp, #0x20\n"
        "and w8, w0, #0x1\n"
        "sturb w8, [x29, #-0xc]\n"
        "b 1f\n"
        "1: b 2f\n"
        "2: ldurb w8, [x29, #-0xc]\n"
        "and w0, w8, #0x1\n"
        "bl FUN_710392ae30\n"
        "str x0, [sp, #0x8]\n"
        "bl FUN_710392ae00\n"
        "b 3f\n"
        "3: ldurb w8, [x29, #-0xc]\n"
        "tbnz w8, #0x0, 10f\n"
        "b 5f\n"
        "5: ldr x8, [sp, #0x8]\n"
        "cbnz x8, 10f\n"
        "b 7f\n"
        "7: stur xzr, [x29, #-0x8]\n"
        "b 99f\n"
        "10: ldr x8, [sp, #0x8]\n"
        "add x8, x8, #0x8\n"
        "stur x8, [x29, #-0x8]\n"
        "b 99f\n"
        "99: ldur x0, [x29, #-0x8]\n"
        "ldp x29, x30, [sp, #0x20]\n"
        "add sp, sp, #0x30\n"
        "ret\n"
    );
}

// =========================================================================
// 0x710392abf0 (112 bytes, -O0) — tsd boot helper
// jemalloc 5.1.0: tsd.h — boots TSD, calls tsdn_fetch → check_entry_exit_locking
// FUN_710392ac60 = tsdn_fetch (in pool-a)
// FUN_710392acb0 = check_entry_exit_locking (in pool-a)
// FUN_7103958900 = tsd_boot0 init helper
// DAT_7106dd3fd5 = tsd init data pointer
// [derived: init sequence with zero'd locals, check-boot-check pattern]
// =========================================================================
extern "C" __attribute__((naked))
void FUN_710392abf0(void) {
    asm(
        "sub sp, sp, #0x30\n"
        "stp x29, x30, [sp, #0x20]\n"
        "add x29, sp, #0x20\n"
        "stur xzr, [x29, #-0x8]\n"
        "str xzr, [sp, #0x10]\n"
        "adrp x8, DAT_7106dd3fd5\n"
        "add x8, x8, :lo12:DAT_7106dd3fd5\n"
        "str x8, [sp, #0x8]\n"
        "b 1f\n"
        "1: b 2f\n"
        "2: bl FUN_710392ac60\n"
        "str x0, [sp]\n"
        "ldr x0, [sp]\n"
        "bl FUN_710392acb0\n"
        "ldur x0, [x29, #-0x8]\n"
        "ldr x1, [sp, #0x10]\n"
        "ldr x2, [sp, #0x8]\n"
        "bl FUN_7103958900\n"
        "ldr x0, [sp]\n"
        "bl FUN_710392acb0\n"
        "b 3f\n"
        "3: b 4f\n"
        "4: ldp x29, x30, [sp, #0x20]\n"
        "add sp, sp, #0x30\n"
        "ret\n"
    );
}

// =========================================================================
// 0x710392ae30 (288 bytes, -O0) — tsd_get_allocator
// jemalloc 5.1.0: tsd.h — allocates TSD on first use via pthread_getspecific/create
// Large function: checks TLS key, optionally creates new TSD with memset+memcpy init.
// DAT_7106dd40b0 = tsd_tls_key
// FUN_710395fba0 = pthread_getspecific
// FUN_710395f070 = pthread_key_create
// FUN_710395f1e0 = base_alloc (for tsd)
// FUN_7103954000 = malloc_write (error print)
// abortWrapper_71039c20a0 = abort
// FUN_71039bfcf0 = memset
// FUN_71039bfb30 = memcpy
// FUN_710392af50 = tsd_set (pthread_setspecific wrapper)
// FUN_710395f240 = cleanup_install
// STR_710442e4e12 = "<jemalloc>: Error in tsd_get_allocator"
// [derived: full tsd alloc path, memset 0x1810 bytes, state byte init to 5]
// =========================================================================
extern "C" __attribute__((naked))
void* FUN_710392ae30(u32) {
    asm(
        "stp x28, x19, [sp, #-0x20]!\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "sub sp, sp, #0x1, lsl #12\n"
        "sub sp, sp, #0x850\n"
        "sub x19, x29, #0x1c\n"
        "and w8, w0, #0x1\n"
        "strb w8, [x19]\n"
        // tsd = pthread_getspecific(tsd_tls_key)
        "adrp x8, DAT_7106dd40b0\n"
        "ldr w0, [x8, :lo12:DAT_7106dd40b0]\n"
        "bl FUN_710395fba0\n"
        "stur x0, [x29, #-0x28]\n"
        // if (!init && tsd != NULL) → return early
        "ldrb w8, [x19]\n"
        "tbz w8, #0x0, 20f\n"
        "b 3f\n"
        "3: ldur x8, [x29, #-0x28]\n"
        "cbnz x8, 20f\n"
        "b 5f\n"
        // init path: pthread_key_create
        "5: adrp x0, DAT_71052934c8+0x1d0\n"
        "add x0, x0, :lo12:DAT_71052934c8+0x1d0\n"
        "sub x1, x29, #0x48\n"
        "bl FUN_710395f070\n"
        "stur x0, [x29, #-0x28]\n"
        "ldur x8, [x29, #-0x28]\n"
        "cbz x8, 10f\n"
        "b 7f\n"
        "7: ldur x8, [x29, #-0x28]\n"
        "stur x8, [x29, #-0x18]\n"
        "b 99f\n"
        // allocate new TSD
        "10: bl FUN_710395f1e0\n"
        "stur x0, [x29, #-0x28]\n"
        "ldur x8, [x29, #-0x28]\n"
        "stur x8, [x29, #-0x30]\n"
        "ldur x8, [x29, #-0x28]\n"
        "cbnz x8, 15f\n"
        "b 12f\n"
        // allocation failed: abort
        "12: adrp x0, STR_710442e4e12\n"
        "add x0, x0, :lo12:STR_710442e4e12\n"
        "bl FUN_7103954000\n"
        "bl abortWrapper_71039c20a0\n"
        // init allocated TSD
        "15: ldur x8, [x29, #-0x28]\n"
        "strb wzr, [x8]\n"
        "mov w19, #0x1810\n"
        "add x0, sp, #0x8\n"
        "mov w1, wzr\n"
        "mov x2, x19\n"
        "bl FUN_71039bfcf0\n"
        "mov w8, #0x5\n"
        "strb w8, [sp, #0x8]\n"
        "ldur x8, [x29, #-0x28]\n"
        "add x0, x8, #0x8\n"
        "add x1, sp, #0x8\n"
        "mov x2, x19\n"
        "bl FUN_71039bfb30\n"
        "b 17f\n"
        // tsd_set + cleanup install
        "17: ldur x0, [x29, #-0x28]\n"
        "bl FUN_710392af50\n"
        "adrp x0, DAT_71052934c8+0x1d0\n"
        "add x0, x0, :lo12:DAT_71052934c8+0x1d0\n"
        "sub x1, x29, #0x48\n"
        "bl FUN_710395f240\n"
        "b 20f\n"
        "20: ldur x8, [x29, #-0x28]\n"
        "stur x8, [x29, #-0x18]\n"
        "b 99f\n"
        "99: ldur x0, [x29, #-0x18]\n"
        "add sp, sp, #0x1, lsl #12\n"
        "add sp, sp, #0x850\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "ldp x28, x19, [sp], #0x20\n"
        "ret\n"
    );
}

// External functions for remaining
extern "C" {
void* FUN_71039bfcf0(void*, u32, u64);  // memset
void* FUN_71039bfb30(void*, void*, u64); // memcpy
void  FUN_710392ae00(void);  // nop (witness)
}

#endif // MATCHING_HACK_NX_CLANG
