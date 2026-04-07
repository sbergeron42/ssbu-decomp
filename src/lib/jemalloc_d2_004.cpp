// jemalloc 5.1.0 — 48-byte wrappers + accessors (pool-d, round 3 batch 4)
// Address range: 0x710392xxxx
// All compiled at -O0 in NX build; naked asm for byte-exact match.

#include "types.h"

#ifdef MATCHING_HACK_NX_CLANG

// External functions
extern "C" {
void* FUN_7103928220(void*);    // witness_owner inner
void* FUN_7103928650(void*, void*); // setup_submenu inner
void* FUN_71039291e0(void*);    // tsd accessor wrapper (+0x1)
void* FUN_7103927b90(void*, u32, u32); // witness nop
void* FUN_710392db30(u32);      // malloc_ncpus_init inner
void  FUN_710392da60(u32);      // percpu_arena_mode_factor
void  FUN_710392da20(void*);    // arena init wrapper
void* FUN_710392c680(void*);    // extent accessor wrapper (+0x1b8)
void* FUN_710392c630(void*);    // extent accessor wrapper (+0x4)
void* FUN_710392c610(void*);    // extent field accessor (+0x2)
void* FUN_710392ed20(void*);    // arena decay accessor wrapper
void* FUN_710392ed50(void*);    // arena extent accessor (in d_002)
void* FUN_710392ecf0(void*);    // arena decay wrapper
u32   FUN_710392edc0(void*, u32); // arena_decay_ms_read (in d_002)
u32   FUN_710392f0d0(void*, u32); // atomic_load_u32 (in d_002)
u32   FUN_710392f170(void*);    // load u32 from ptr (in d2_001)
void* FUN_710392fdb0(void*);    // ffs wrapper
void* FUN_71039c7d10(u64);      // __builtin_ctzll
void* FUN_71039c7d30(void*);    // __builtin_popcount / trylock
void* FUN_710392b420(void*);    // extent hook wrapper
void* FUN_710392c130(void*);    // extent accessor wrapper (+0x28)
}

// External globals
extern "C" {
__attribute__((visibility("hidden"))) extern u32 DAT_7105293560;  // opt_percpu
__attribute__((visibility("hidden"))) extern u8  DAT_7106dd3f1e;  // arena_cleanup flag
}

// =========================================================================
// 0x71039280c0 (48 bytes, -O0) — forwarding wrapper (2 params)
// jemalloc 5.1.0: jemalloc.c — forwards to FUN_7103928650
// [derived: 2-param forward, called from setup path]
// =========================================================================
extern "C" __attribute__((naked))
void* FUN_71039280c0(void*, void*) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "str x1, [sp]\n"
        "ldr x0, [sp, #0x8]\n"
        "ldr x1, [sp]\n"
        "bl FUN_7103928650\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 0x71039281f0 (48 bytes, -O0) — witness_owner (returns bool & 1)
// jemalloc 5.1.0: witness.h — calls inner, masks return to bool
// FUN_7103928220 = witness_owner inner
// [derived: call+and w0,#0x1 pattern]
// =========================================================================
extern "C" __attribute__((naked))
u32 FUN_71039281f0(void*) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "ldr x0, [sp, #0x8]\n"
        "bl FUN_7103928220\n"
        "and w0, w0, #0x1\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 0x71039291b0 (48 bytes, -O0) — tsd bool field read via accessor
// jemalloc 5.1.0: tsd.h — calls accessor, reads byte, masks to bool
// FUN_71039291e0 = tsd accessor wrapper (returns &tsd->field_0x1)
// [derived: call+ldrb+and #0x1 pattern]
// =========================================================================
extern "C" __attribute__((naked))
u32 FUN_71039291b0(void*) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "ldr x0, [sp, #0x8]\n"
        "bl FUN_71039291e0\n"
        "ldrb w8, [x0]\n"
        "and w0, w8, #0x1\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103929420 (48 bytes, leaf, -O0) — conditional nop (cbnz skip)
// jemalloc 5.1.0: witness.h — if param2 != 0, skip; else branch-nop
// [derived: cbnz+b+b pattern, nop in release]
// =========================================================================
extern "C" __attribute__((naked))
void FUN_7103929420(void*, u32) {
    asm(
        "sub sp, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "str w1, [sp, #0x4]\n"
        "ldr w8, [sp, #0x4]\n"
        "cbnz w8, 5f\n"
        "b 3f\n"
        "3: b 5f\n"
        "5: add sp, sp, #0x10\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103929660 (48 bytes, -O0) — mutex trylock wrapper
// jemalloc 5.1.0: mutex.h — calls trylock on param+0x40, returns bool
// FUN_71039c7d30 = pthread_mutex_trylock or similar
// [derived: add #0x40 + bl + subs+cset ne pattern]
// =========================================================================
extern "C" __attribute__((naked))
u32 FUN_7103929660(void*) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "ldr x8, [sp, #0x8]\n"
        "add x0, x8, #0x40\n"
        "bl FUN_71039c7d30\n"
        "subs w8, w0, #0x0\n"
        "cset w0, ne\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 0x710392c480 (48 bytes, -O0) — extent qword read via accessor
// jemalloc 5.1.0: extent.h — calls accessor(+0x1b8), loads qword
// FUN_710392c680 = accessor returning &extent->field_0x1b8
// [derived: call+ldr x0,[x0] pattern]
// =========================================================================
extern "C" __attribute__((naked))
u64 FUN_710392c480(void*) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "ldr x0, [sp, #0x8]\n"
        "bl FUN_710392c680\n"
        "ldr x0, [x0]\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 0x710392c4b0 (48 bytes, -O0) — extent u32 read via accessor
// jemalloc 5.1.0: extent.h — calls accessor(+0x4), loads u32
// FUN_710392c630 = accessor wrapper for +0x4
// [derived: call+ldr w0,[x0] pattern]
// =========================================================================
extern "C" __attribute__((naked))
u32 FUN_710392c4b0(void*) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "ldr x0, [sp, #0x8]\n"
        "bl FUN_710392c630\n"
        "ldr w0, [x0]\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 0x710392c560 (48 bytes, -O0) — extent accessor wrapper for +0x2
// jemalloc 5.1.0: extent.h — wraps FUN_710392c610 with branch nops
// [derived: single-call forward with branch nops]
// =========================================================================
extern "C" __attribute__((naked))
void* FUN_710392c560(void*) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "b 1f\n"
        "1: b 2f\n"
        "2: ldr x0, [sp, #0x8]\n"
        "bl FUN_710392c610\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 0x710392c5b0 (36 bytes, leaf, -O0) — copy qword through two pointers
// jemalloc 5.1.0: extent.h — *param1 = *param2
// [derived: ldr from [param2], str to [param1]]
// =========================================================================
extern "C" __attribute__((naked))
void FUN_710392c5b0(void*, void*) {
    asm(
        "sub sp, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "str x1, [sp]\n"
        "ldr x8, [sp, #0x8]\n"
        "ldr x9, [sp]\n"
        "ldr x9, [x9]\n"
        "str x9, [x8]\n"
        "add sp, sp, #0x10\n"
        "ret\n"
    );
}

// =========================================================================
// 0x710392c5e0 (48 bytes, leaf, -O0) — init u32 pair to 1000
// jemalloc 5.1.0: arena.c — stores 0x3e8 (1000) to [param] and [param+4]
// [derived: mov w8,#0x3e8; str to [x9] and [x9,#4]]
// =========================================================================
extern "C" __attribute__((naked))
void FUN_710392c5e0(void*) {
    asm(
        "sub sp, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "mov w8, #0x3e8\n"
        "str w8, [sp, #0x4]\n"
        "ldr w8, [sp, #0x4]\n"
        "ldr x9, [sp, #0x8]\n"
        "str w8, [x9]\n"
        "ldr w8, [sp, #0x4]\n"
        "ldr x9, [sp, #0x8]\n"
        "str w8, [x9, #0x4]\n"
        "add sp, sp, #0x10\n"
        "ret\n"
    );
}

// =========================================================================
// 0x710392c630 (48 bytes, -O0) — extent accessor wrapper for +0x4
// jemalloc 5.1.0: extent.h — wraps FUN_710392c660 with branch nops
// [derived: single-call forward with branch nops]
// =========================================================================
extern "C" __attribute__((naked))
void* FUN_710392c630(void*) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "b 1f\n"
        "1: b 2f\n"
        "2: ldr x0, [sp, #0x8]\n"
        "bl FUN_710392c660\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 0x710392d900 (48 bytes, -O0) — percpu arena init
// jemalloc 5.1.0: jemalloc.c — reads opt_percpu, calls factor, writes back
// DAT_7105293560 = opt_percpu_arena [derived: ldr+bl+str pattern]
// FUN_710392da60 = percpu_arena_mode_factor (in d_001)
// =========================================================================
extern "C" __attribute__((naked))
void FUN_710392d900(void) {
    asm(
        "str x19, [sp, #-0x20]!\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "adrp x19, DAT_7105293560\n"
        "ldr w0, [x19, :lo12:DAT_7105293560]\n"
        "bl FUN_710392da60\n"
        "str w0, [x19, :lo12:DAT_7105293560]\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "ldr x19, [sp], #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 0x710392d9f0 (48 bytes, -O0) — forwarding wrapper
// jemalloc 5.1.0: jemalloc.c — wraps FUN_710392da20
// [derived: single-call forward]
// =========================================================================
extern "C" __attribute__((naked))
void* FUN_710392d9f0(void*) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "ldr x0, [sp, #0x8]\n"
        "bl FUN_710392da20\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 0x710392da20 (48 bytes, -O0) — arena witness init wrapper
// jemalloc 5.1.0: jemalloc.c — calls witness nop with params (1, 0)
// FUN_7103927b90 = witness nop (3 params)
// [derived: stores wzr, forwards with immediate #0x1]
// =========================================================================
extern "C" __attribute__((naked))
void FUN_710392da20(void*) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "str wzr, [sp, #0x4]\n"
        "ldr x0, [sp, #0x8]\n"
        "ldr w2, [sp, #0x4]\n"
        "orr w1, wzr, #0x1\n"
        "bl FUN_7103927b90\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 0x710392db00 (48 bytes, -O0) — ncpus wrapper
// jemalloc 5.1.0: jemalloc.c — wraps FUN_710392db30 (malloc_ncpus)
// [derived: single-call forward with u32 param]
// =========================================================================
extern "C" __attribute__((naked))
void FUN_710392db00(u32) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "stur w0, [x29, #-0x4]\n"
        "ldur w0, [x29, #-0x4]\n"
        "bl FUN_710392db30\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 0x710392ebf0 (48 bytes, -O0) — arena_decay_ms_read at +0x1a28
// jemalloc 5.1.0: arena.c — reads decay ms from arena+0x1a28 with mo=2
// FUN_710392edc0 = arena_decay_ms_read
// [derived: mov w9,#0x1a28; add+bl pattern]
// =========================================================================
extern "C" __attribute__((naked))
u32 FUN_710392ebf0(void*) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "ldr x8, [sp, #0x8]\n"
        "mov w9, #0x1a28\n"
        "add x0, x8, x9\n"
        "orr w1, wzr, #0x2\n"
        "bl FUN_710392edc0\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 0x710392ec20 (48 bytes, -O0) — arena_decay wrapper at +0x2ea0
// jemalloc 5.1.0: arena.c — wraps decay accessor for dirty extents
// FUN_710392ecf0 = arena_decay accessor wrapper
// [derived: mov w9,#0x2ea0; add+bl pattern]
// =========================================================================
extern "C" __attribute__((naked))
void* FUN_710392ec20(void*) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "ldr x8, [sp, #0x8]\n"
        "mov w9, #0x2ea0\n"
        "add x0, x8, x9\n"
        "bl FUN_710392ecf0\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 0x710392ec50 (48 bytes, -O0) — arena_decay wrapper at +0x35c0
// jemalloc 5.1.0: arena.c — wraps decay accessor for muzzy extents
// FUN_710392ecf0 = arena_decay accessor wrapper
// [derived: mov w9,#0x35c0; add+bl pattern]
// =========================================================================
extern "C" __attribute__((naked))
void* FUN_710392ec50(void*) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "ldr x8, [sp, #0x8]\n"
        "mov w9, #0x35c0\n"
        "add x0, x8, x9\n"
        "bl FUN_710392ecf0\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 0x710392ecf0 (48 bytes, -O0) — arena_decay forwarding wrapper
// jemalloc 5.1.0: arena.c — wraps FUN_710392ed20
// [derived: single-call forward]
// =========================================================================
extern "C" __attribute__((naked))
void* FUN_710392ecf0(void*) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "ldr x0, [sp, #0x8]\n"
        "bl FUN_710392ed20\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 0x710392ed20 (48 bytes, -O0) — arena_decay accessor at +0xa0
// jemalloc 5.1.0: arena.c — adds 0xa0 offset, calls FUN_710392ed50
// [derived: add #0xa0 + bl pattern]
// =========================================================================
extern "C" __attribute__((naked))
void* FUN_710392ed20(void*) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "ldr x8, [sp, #0x8]\n"
        "add x0, x8, #0xa0\n"
        "bl FUN_710392ed50\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 0x710392f020 (48 bytes, -O0) — arena_cleanup_check
// jemalloc 5.1.0: arena.c — atomic load from global, returns bool
// DAT_7106dd3f1e = arena_cleanup flag
// FUN_710392f0d0 = atomic_load_u32
// [derived: adrp+add global, bl+and #0x1 pattern]
// =========================================================================
extern "C" __attribute__((naked))
u32 FUN_710392f020(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "adrp x0, DAT_7106dd3f1e\n"
        "add x0, x0, :lo12:DAT_7106dd3f1e\n"
        "mov w1, wzr\n"
        "bl FUN_710392f0d0\n"
        "and w0, w0, #0x1\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}

// =========================================================================
// 0x710392f0a0 (48 bytes, -O0) — arena_decay_ms at +0x9c with mo=2
// jemalloc 5.1.0: arena.c — reads decay ms from struct+0x9c
// FUN_710392f0d0 = atomic_load_u32
// [derived: add #0x9c + mov w1,#2 + bl + and #0x1]
// =========================================================================
extern "C" __attribute__((naked))
u32 FUN_710392f0a0(void*) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "ldr x8, [sp, #0x8]\n"
        "add x0, x8, #0x9c\n"
        "orr w1, wzr, #0x2\n"
        "bl FUN_710392f0d0\n"
        "and w0, w0, #0x1\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 0x710392f140 (48 bytes, -O0) — arena npages read at +0x7d80
// jemalloc 5.1.0: arena.c — loads [param+0x7d80], reads u32
// FUN_710392f170 = load u32 from ptr
// [derived: ldr at large offset + bl pattern]
// =========================================================================
extern "C" __attribute__((naked))
u32 FUN_710392f140(void*) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "ldr x8, [sp, #0x8]\n"
        "ldr x0, [x8, #0x7d80]\n"
        "bl FUN_710392f170\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 0x710392fcd0 (48 bytes, -O0) — forwarding wrapper for ffs
// jemalloc 5.1.0: bits.h — wraps FUN_710392fdb0 (ffs inner)
// [derived: single-call forward]
// =========================================================================
extern "C" __attribute__((naked))
void* FUN_710392fcd0(void*) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "ldr x0, [sp, #0x8]\n"
        "bl FUN_710392fdb0\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 0x710392fdb0 (48 bytes, -O0) — __builtin_ctzll wrapper
// jemalloc 5.1.0: bits.h — wraps FUN_71039c7d10 (ctzll)
// [derived: single-call forward to external]
// =========================================================================
extern "C" __attribute__((naked))
void* FUN_710392fdb0(void*) {
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
// 0x710392fe20 (48 bytes, -O0) — mutex trylock wrapper
// jemalloc 5.1.0: mutex.h — calls trylock on param+0x40, returns bool
// FUN_71039c7d30 = pthread_mutex_trylock
// [derived: add #0x40 + bl + subs+cset ne pattern]
// =========================================================================
extern "C" __attribute__((naked))
u32 FUN_710392fe20(void*) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "ldr x8, [sp, #0x8]\n"
        "add x0, x8, #0x40\n"
        "bl FUN_71039c7d30\n"
        "subs w8, w0, #0x0\n"
        "cset w0, ne\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 0x710392b3f0 (48 bytes, -O0) — extent hook forwarding wrapper
// jemalloc 5.1.0: extent.c — wraps FUN_710392b420
// [derived: single-call forward]
// =========================================================================
extern "C" __attribute__((naked))
void* FUN_710392b3f0(void*) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "ldr x0, [sp, #0x8]\n"
        "bl FUN_710392b420\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 0x710392b720 (48 bytes, -O0) — extent alloc core wrapper
// jemalloc 5.1.0: extent.c — wraps FUN_710392c130 (extent accessor +0x28)
// [derived: single-call forward]
// =========================================================================
extern "C" __attribute__((naked))
void* FUN_710392b720(void*) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "ldr x0, [sp, #0x8]\n"
        "bl FUN_710392c130\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// External function declarations used only as call targets
extern "C" {
void* FUN_710392c660(void*);    // extent field accessor +0x4
}

#endif // MATCHING_HACK_NX_CLANG
