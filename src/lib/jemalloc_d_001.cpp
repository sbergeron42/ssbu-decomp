// jemalloc 5.1.0 — small functions batch 1 (pool-d)
// Address range: 0x710392xxxx
// All compiled at -O0 in NX build; naked asm for byte-exact match.
// jemalloc 5.1.0: jemalloc.c, arena.c, extent.c, rtree.c

#include "types.h"

#ifdef MATCHING_HACK_NX_CLANG

// External functions
extern "C" {
void* FUN_7103927ac0(void*);  // tsd check (returns bool in w0)
void* FUN_7103927ae0(void*);  // tsd accessor
void* FUN_7103929790(void*);  // arena_get / tsd_arena_get
void* FUN_7103929a70(u64);    // prof_active_get_unlocked
void  FUN_7103956fa0(const char*, ...);  // malloc_printf
void  FUN_710392d2d0(void*, void*, void*, u32, void*, void*);  // extent_record inner
void  FUN_710392f190(void*, void*, void*, void*, u32, u32);     // arena_decay_impl
}

// External globals (hidden visibility — linker-resolved, not GOT-indirect)
extern "C" {
__attribute__((visibility("hidden"))) extern u32 DAT_71052934c0;  // opt_prof
__attribute__((visibility("hidden"))) extern u32 DAT_7106d424a0;  // ncpus
__attribute__((visibility("hidden"))) extern u8  DAT_7106d4a590;  // had_conf_error
}

// String constant (defined in .rodata, referenced by adrp+add)
extern "C" {
extern const char STR_71043ab527[];  // "<jemalloc>: %s: %.*s:%.*s\n"
}

// =========================================================================
// 0x710392da60 (68 bytes, leaf, -O0) — percpu arena mode factor
// jemalloc 5.1.0: jemalloc.c — maps percpu_arena_mode to narenas factor
// Called from malloc_init_narenas (FUN_710392d6f0) with opt_percpu_arena
// if mode != disabled(2), returns mode + 3; else returns 2 (no-op)
// [derived: caller checks result==4 for per_phycpu hyper-threading validation]
// =========================================================================
extern "C" __attribute__((naked))
int FUN_710392da60(int) {
    asm(
        "sub sp, sp, #0x10\n"
        "str w0, [sp, #0xc]\n"
        "b 1f\n" "1: b 2f\n" "2: b 3f\n" "3: b 4f\n" "4:\n"
        "ldr w8, [sp, #0xc]\n"
        "subs w8, w8, #0x2\n"
        "b.eq 8f\n"
        "b 6f\n"
        "6: ldr w8, [sp, #0xc]\n"
        "add w8, w8, #0x3\n"
        "str w8, [sp, #0xc]\n"
        "b 8f\n"
        "8: ldr w0, [sp, #0xc]\n"
        "add sp, sp, #0x10\n"
        "ret\n"
    );
}

// =========================================================================
// 0x710392dab0 (76 bytes, leaf, -O0) — malloc_narenas_default
// jemalloc 5.1.0: jemalloc.c:837 — static unsigned malloc_narenas_default(void)
// Returns (ncpus >= 2) ? ncpus * 4 : 1
// DAT_7106d424a0 = ncpus [derived: used in percpu check + narenas limit 0xffe]
// =========================================================================
extern "C" __attribute__((naked))
u32 FUN_710392dab0(void) {
    asm(
        "sub sp, sp, #0x10\n"
        "b 1f\n" "1: b 2f\n" "2:\n"
        "adrp x8, DAT_7106d424a0\n"
        "ldr w8, [x8, :lo12:DAT_7106d424a0]\n"
        "subs w8, w8, #0x2\n"
        "b.cc 5f\n"
        "b 3f\n"
        "3: adrp x8, DAT_7106d424a0\n"
        "ldr w8, [x8, :lo12:DAT_7106d424a0]\n"
        "lsl w8, w8, #0x2\n"
        "str w8, [sp, #0xc]\n"
        "b 7f\n"
        "5: mov w8, #0x1\n"
        "str w8, [sp, #0xc]\n"
        "b 7f\n"
        "7: ldr w0, [sp, #0xc]\n"
        "add sp, sp, #0x10\n"
        "ret\n"
    );
}

// =========================================================================
// 0x710392c010 (84 bytes, leaf, -O0) — bitfield mask extraction
// jemalloc 5.1.0: extent.h or rtree.h — extracts upper 32 bits from packed u64
// Computes mask = ~((1UL << (64-32)) - 1) = 0xFFFFFFFF00000000, returns val & mask
// [derived: called from FUN_710392bcc0 which operates on extent/rtree leaf elements]
// =========================================================================
extern "C" __attribute__((naked))
u64 FUN_710392c010(u64) {
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
        "ldr w8, [sp, #0xc]\n"
        "mov w9, #0x1\n"
        "lsl x8, x9, x8\n"
        "subs x8, x8, #0x1\n"
        "mvn x8, x8\n"
        "str x8, [sp]\n"
        "ldr x8, [sp, #0x18]\n"
        "ldr x9, [sp]\n"
        "and x0, x8, x9\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 0x710392fb80 (88 bytes, leaf, -O0) — decay backlog update
// jemalloc 5.1.0: arena.c — updates decay backlog at struct+0x708
// Computes max(0, current_npages - decay_npages_limit) and stores it
// param_1+0xC8 = npages_limit, param_1+0x708 = backlog entry
// [derived: offset 0x708 in arena_decay_t, called from decay tick path]
// =========================================================================
extern "C" __attribute__((naked))
void FUN_710392fb80(void*, u64) {
    asm(
        "sub sp, sp, #0x20\n"
        "str x0, [sp, #0x18]\n"
        "str x1, [sp, #0x10]\n"
        "ldr x8, [sp, #0x10]\n"
        "ldr x9, [sp, #0x18]\n"
        "ldr x9, [x9, #0xc8]\n"
        "subs x8, x8, x9\n"
        "b.ls 5f\n"
        "b 3f\n"
        "3: ldr x8, [sp, #0x10]\n"
        "ldr x9, [sp, #0x18]\n"
        "ldr x9, [x9, #0xc8]\n"
        "subs x8, x8, x9\n"
        "b 7f\n"
        "5: mov x8, xzr\n"
        "b 7f\n"
        "7: str x8, [sp, #0x8]\n"
        "ldr x8, [sp, #0x8]\n"
        "ldr x9, [sp, #0x18]\n"
        "str x8, [x9, #0x708]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103927b30 (84 bytes, -O0) — tsd arena get (with null check)
// jemalloc 5.1.0: tsd.h — if tsd_nominal(tsd), return arena_get(tsd_arenap(tsd))
// FUN_7103927ac0 = tsd_nominal (returns bool, inverted: 0=nominal, 1=not)
// FUN_7103927ae0 = tsd accessor (e.g. tsd_arenap)
// FUN_7103929790 = arena_get or tsd_arena_get
// [derived: call chain tsd_nominal → tsd_arenap → arena_get, returns void* arena]
// =========================================================================
extern "C" __attribute__((naked))
void* FUN_7103927b30(void*) {
    asm(
        "sub sp, sp, #0x30\n"
        "stp x29, x30, [sp, #0x20]\n"
        "add x29, sp, #0x20\n"
        "str x0, [sp, #0x10]\n"
        "ldr x0, [sp, #0x10]\n"
        "bl FUN_7103927ac0\n"
        "tbz w0, #0, 3f\n"
        "b 2f\n"
        "2: stur xzr, [x29, #-0x8]\n"
        "b 7f\n"
        "3: ldr x0, [sp, #0x10]\n"
        "bl FUN_7103927ae0\n"
        "str x0, [sp, #0x8]\n"
        "ldr x0, [sp, #0x8]\n"
        "bl FUN_7103929790\n"
        "stur x0, [x29, #-0x8]\n"
        "b 7f\n"
        "7: ldur x0, [x29, #-0x8]\n"
        "ldp x29, x30, [sp, #0x20]\n"
        "add sp, sp, #0x30\n"
        "ret\n"
    );
}

// =========================================================================
// 0x710392d270 (84 bytes, -O0) — extent_record wrapper (bool-cast param_4)
// jemalloc 5.1.0: extent.c — thin wrapper around extent_record inner function
// Casts param_4 to bool (& 1) before forwarding all params
// FUN_710392d2d0 = extent_record_impl or similar
// [derived: 6-param call with bool cast on 4th, matches extent_record wrapper]
// =========================================================================
extern "C" __attribute__((naked))
void FUN_710392d270(void*, void*, void*, u32, void*, void*) {
    asm(
        "sub sp, sp, #0x40\n"
        "stp x29, x30, [sp, #0x30]\n"
        "add x29, sp, #0x30\n"
        "stur x0, [x29, #-0x8]\n"
        "stur x1, [x29, #-0x10]\n"
        "str x2, [sp, #0x18]\n"
        "and w8, w3, #0x1\n"
        "strb w8, [sp, #0x14]\n"
        "str x4, [sp, #0x8]\n"
        "str x5, [sp]\n"
        "ldur x0, [x29, #-0x8]\n"
        "ldur x1, [x29, #-0x10]\n"
        "ldr x2, [sp, #0x18]\n"
        "ldr x4, [sp, #0x8]\n"
        "ldr x5, [sp]\n"
        "ldrb w8, [sp, #0x14]\n"
        "and w3, w8, #0x1\n"
        "bl FUN_710392d2d0\n"
        "ldp x29, x30, [sp, #0x30]\n"
        "add sp, sp, #0x40\n"
        "ret\n"
    );
}

// =========================================================================
// 0x710392ef40 (96 bytes, -O0) — arena_decay wrapper with offset computation
// jemalloc 5.1.0: arena.c — wraps arena_decay_impl, computes sub-struct offsets
// param_2 + 0x2ea0 and param_2 + 0x1ad8 are sub-struct pointers within arena_t
// FUN_710392f190 = arena_decay_impl
// [derived: offset 0x2ea0/0x1ad8 within arena struct, bool params for dirty/muzzy]
// =========================================================================
extern "C" __attribute__((naked))
u32 FUN_710392ef40(void*, void*, u32, u32) {
    asm(
        "sub sp, sp, #0x30\n"
        "stp x29, x30, [sp, #0x20]\n"
        "add x29, sp, #0x20\n"
        "stur x0, [x29, #-0x8]\n"
        "str x1, [sp, #0x10]\n"
        "and w8, w2, #0x1\n"
        "strb w8, [sp, #0xc]\n"
        "and w8, w3, #0x1\n"
        "strb w8, [sp, #0x8]\n"
        "ldur x0, [x29, #-0x8]\n"
        "ldr x1, [sp, #0x10]\n"
        "mov w8, #0x2ea0\n"
        "add x2, x1, x8\n"
        "mov w8, #0x1ad8\n"
        "add x3, x1, x8\n"
        "ldrb w8, [sp, #0x8]\n"
        "ldrb w9, [sp, #0xc]\n"
        "and w4, w9, #0x1\n"
        "and w5, w8, #0x1\n"
        "bl FUN_710392f190\n"
        "and w0, w0, #0x1\n"
        "ldp x29, x30, [sp, #0x20]\n"
        "add sp, sp, #0x30\n"
        "ret\n"
    );
}

// =========================================================================
// 0x71039278b0 (72 bytes, -O0) — prof_active check
// jemalloc 5.1.0: prof.h — checks if profiling is in active mode
// DAT_71052934c0 = opt_prof [derived: compared to 3 (prof_mode enum), gates profiling]
// FUN_7103929a70 = prof_active_get_unlocked
// [derived: single caller FUN_7103927800, gates prof path, returns bool]
// =========================================================================
extern "C" __attribute__((naked))
u8 FUN_71039278b0(void) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "adrp x8, DAT_71052934c0\n"
        "ldr w8, [x8, :lo12:DAT_71052934c0]\n"
        "subs w8, w8, #0x3\n"
        "b.ne 5f\n"
        "b 3f\n"
        "3: bl FUN_7103929a70\n"
        "and w8, w0, #0x1\n"
        "sturb w8, [x29, #-0x1]\n"
        "b 7f\n"
        "5: sturb wzr, [x29, #-0x1]\n"
        "b 7f\n"
        "7: ldurb w0, [x29, #-0x1]\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 0x710392b180 (88 bytes, -O0) — malloc_conf_error
// jemalloc 5.1.0: jemalloc.c:799 — static void malloc_conf_error(...)
// Prints "<jemalloc>: %s: %.*s:%.*s\n" via malloc_printf, sets had_conf_error=1
// FUN_7103956fa0 = malloc_printf [derived: format string match]
// DAT_7106d4a590 = had_conf_error [derived: set to 1 after error print]
// STR_71043ab527 = format string "<jemalloc>: %s: %.*s:%.*s\n"
// =========================================================================
extern "C" __attribute__((naked))
void FUN_710392b180(void*, void*, u32, void*, u32) {
    asm(
        "sub sp, sp, #0x40\n"
        "stp x29, x30, [sp, #0x30]\n"
        "add x29, sp, #0x30\n"
        "stur x0, [x29, #-0x8]\n"
        "stur x1, [x29, #-0x10]\n"
        "str x2, [sp, #0x18]\n"
        "str x3, [sp, #0x10]\n"
        "str x4, [sp, #0x8]\n"
        "ldur x1, [x29, #-0x8]\n"
        "ldr w2, [sp, #0x18]\n"
        "ldur x3, [x29, #-0x10]\n"
        "ldr w4, [sp, #0x8]\n"
        "ldr x5, [sp, #0x10]\n"
        "adrp x0, STR_71043ab527\n"
        "add x0, x0, :lo12:STR_71043ab527\n"
        "bl FUN_7103956fa0\n"
        "adrp x8, DAT_7106d4a590\n"
        "mov w9, #0x1\n"
        "strb w9, [x8, :lo12:DAT_7106d4a590]\n"
        "ldp x29, x30, [sp, #0x30]\n"
        "add sp, sp, #0x40\n"
        "ret\n"
    );
}

#endif // MATCHING_HACK_NX_CLANG
