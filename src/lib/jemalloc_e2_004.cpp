// jemalloc 5.1.0 — extent helpers, mutex, arena (pool-e, batch 5)
// NX jemalloc compiled at -O0 — uses naked asm for matching
// jemalloc 5.1.0: extent.c, arena.c, mutex.c

#include "types.h"

#ifdef MATCHING_HACK_NX_CLANG

// External callees
extern "C" {
u32  FUN_7103942b80(u64, u64, u32);
u32  FUN_710393ea90(u64, u64, u64, u64, u64, u32);
u32  FUN_7103957fe0(void);
u32  FUN_71039575c0(void);
u64  FUN_7103938870(u64);
void FUN_710393c360(u64, u32);
u64  FUN_710393cfe0(u64);
void FUN_7103941be0(u64, u64);
void FUN_710393cdc0(u64, u32);
void FUN_710393cc10(u64, u64, u64, u64, u64, u32);
u64  FUN_7103941400(u64, u64, u64, u64, u64, u32, u32, u64);
u8   FUN_7103941090(u64, u64, u64, u64, u64, u64, u32);
void FUN_710393e1a0(u64, u32);
u64  FUN_710393df00(u64, u64, u64, u64, u64, u64, u64, u32);
u32  FUN_710393c1e0(u64);
void FUN_710393e1d0(u64, u64, u64);
}

// =========================================================================
// 0x7103942360 (32 bytes, leaf) — return param + 0x28
// jemalloc 5.1.0: extent.c — extent mutex pointer
// =========================================================================
extern "C" __attribute__((naked))
u64 FUN_7103942360(u64) {
    asm(
        "sub sp, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "ldr x8, [sp, #0x8]\n"
        "add x0, x8, #0x28\n"
        "add sp, sp, #0x10\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103942580 (32 bytes, leaf) — return *param (deref pointer)
// jemalloc 5.1.0: extent.h — extent_base_get or similar
// =========================================================================
extern "C" __attribute__((naked))
u64 FUN_7103942580(u64) {
    asm(
        "sub sp, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "ldr x8, [sp, #0x8]\n"
        "ldr x0, [x8]\n"
        "add sp, sp, #0x10\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103942c80 (48 bytes, leaf) — extract bits [18:25] from *param
// jemalloc 5.1.0: extent.h — extent_nfree_get
// =========================================================================
extern "C" __attribute__((naked))
u32 FUN_7103942c80(u64) {
    asm(
        "sub sp, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "ldr x8, [sp, #0x8]\n"
        "ldr x8, [x8]\n"
        "ubfx x8, x8, #0x12, #0x8\n"
        "str w8, [sp, #0x4]\n"
        "b 0f\n"
        "0: b 1f\n"
        "1: ldr w0, [sp, #0x4]\n"
        "add sp, sp, #0x10\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103942300 (48 bytes) — extent lock wrapper
// jemalloc 5.1.0: extent.c — extent_lock
// =========================================================================
extern "C" __attribute__((naked))
void FUN_7103942300(u64) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "ldr x0, [sp, #0x8]\n"
        "bl FUN_7103942330\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103942330 (48 bytes) — extent lock impl (nop branches)
// jemalloc 5.1.0: extent.c — extent_lock_impl
// =========================================================================
extern "C" __attribute__((naked))
void FUN_7103942330(u64) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "b 0f\n"
        "0: b 1f\n"
        "1: ldr x0, [sp, #0x8]\n"
        "bl FUN_7103942360\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103942b40 (64 bytes) — mutex trylock wrapper (w2=1)
// jemalloc 5.1.0: mutex.c — malloc_mutex_lock
// =========================================================================
extern "C" __attribute__((naked))
u32 FUN_7103942b40(u64, u64) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "str x1, [sp]\n"
        "ldr x0, [sp, #0x8]\n"
        "ldr x1, [sp]\n"
        "mov w2, #0x1\n"
        "bl FUN_7103942b80\n"
        "and w0, w0, #0x1\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103943300 (64 bytes) — mutex unlock wrapper (w2=0)
// jemalloc 5.1.0: mutex.c — malloc_mutex_unlock
// =========================================================================
extern "C" __attribute__((naked))
u32 FUN_7103943300(u64, u64) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "str x1, [sp]\n"
        "ldr x0, [sp, #0x8]\n"
        "ldr x1, [sp]\n"
        "mov w2, wzr\n"
        "bl FUN_7103942b80\n"
        "and w0, w0, #0x1\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103943760 (64 bytes) — calls mutex lock, stores result
// jemalloc 5.1.0: arena.c — arena_mutex_lock wrapper
// =========================================================================
extern "C" __attribute__((naked))
void FUN_7103943760(u64, u64) {
    asm(
        "sub sp, sp, #0x30\n"
        "stp x29, x30, [sp, #0x20]\n"
        "add x29, sp, #0x20\n"
        "stur x0, [x29, #-0x8]\n"
        "str x1, [sp, #0x10]\n"
        "ldur x0, [x29, #-0x8]\n"
        "ldr x1, [sp, #0x10]\n"
        "bl FUN_7103942b40\n"
        "and w8, w0, #0x1\n"
        "strb w8, [sp, #0xc]\n"
        "b 0f\n"
        "0: b 1f\n"
        "1: ldp x29, x30, [sp, #0x20]\n"
        "add sp, sp, #0x30\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103943b50 (80 bytes) — 5-param hook wrapper (w5=0)
// jemalloc 5.1.0: extent.c — extent_purge_lazy_wrapper
// =========================================================================
extern "C" __attribute__((naked))
u32 FUN_7103943b50(u64, u64, u64, u64, u64) {
    asm(
        "sub sp, sp, #0x40\n"
        "stp x29, x30, [sp, #0x30]\n"
        "add x29, sp, #0x30\n"
        "stur x0, [x29, #-0x8]\n"
        "stur x1, [x29, #-0x10]\n"
        "str x2, [sp, #0x18]\n"
        "str x3, [sp, #0x10]\n"
        "str x4, [sp, #0x8]\n"
        "ldur x0, [x29, #-0x8]\n"
        "ldur x1, [x29, #-0x10]\n"
        "ldr x2, [sp, #0x18]\n"
        "ldr x3, [sp, #0x10]\n"
        "ldr x4, [sp, #0x8]\n"
        "mov w5, wzr\n"
        "bl FUN_710393ea90\n"
        "and w0, w0, #0x1\n"
        "ldp x29, x30, [sp, #0x30]\n"
        "add sp, sp, #0x40\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103943ba0 (96 bytes) — two-level oversize check
// jemalloc 5.1.0: extent.c — extent_may_force_decay
// =========================================================================
extern "C" __attribute__((naked))
u8 FUN_7103943ba0(void) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "bl FUN_7103957fe0\n"
        "tbz w0, #0x0, 2f\n"
        "b 0f\n"
        "0: mov w8, #0x1\n"
        "sturb w8, [x29, #-0x1]\n"
        "b 5f\n"
        "2: bl FUN_71039575c0\n"
        "tbz w0, #0x0, 4f\n"
        "b 3f\n"
        "3: mov w8, #0x1\n"
        "sturb w8, [x29, #-0x1]\n"
        "b 5f\n"
        "4: sturb wzr, [x29, #-0x1]\n"
        "b 5f\n"
        "5: ldurb w0, [x29, #-0x1]\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103942380 (160 bytes) — extent alloc + usize/zeroed setup
// jemalloc 5.1.0: extent.c — extent_recycle_extract
// 6 nop branches = -O0 artifact
// =========================================================================
extern "C" __attribute__((naked))
void FUN_7103942380(u64, u64, u64, u64, u64) {
    asm(
        "sub sp, sp, #0x40\n"
        "str x19, [sp, #0x20]\n"
        "stp x29, x30, [sp, #0x30]\n"
        "add x29, sp, #0x30\n"
        "stur x0, [x29, #-0x8]\n"
        "str x1, [sp, #0x18]\n"
        "str x2, [sp, #0x10]\n"
        "str x3, [sp, #0x8]\n"
        "str x4, [sp]\n"
        "b 0f\n"
        "0: b 1f\n"
        "1: b 2f\n"
        "2: b 3f\n"
        "3: b 4f\n"
        "4: b 5f\n"
        "5: ldur x0, [x29, #-0x8]\n"
        "bl FUN_7103938870\n"
        "mov w1, wzr\n"
        "bl FUN_710393c360\n"
        "ldr x19, [sp]\n"
        "mov x0, x19\n"
        "bl FUN_710393cfe0\n"
        "mov x1, x0\n"
        "mov x0, x19\n"
        "bl FUN_7103941be0\n"
        "ldr x0, [sp]\n"
        "mov w1, wzr\n"
        "bl FUN_710393cdc0\n"
        "ldur x0, [x29, #-0x8]\n"
        "ldr x1, [sp, #0x18]\n"
        "ldr x2, [sp, #0x10]\n"
        "ldr x3, [sp, #0x8]\n"
        "ldr x4, [sp]\n"
        "mov w5, wzr\n"
        "bl FUN_710393cc10\n"
        "ldp x29, x30, [sp, #0x30]\n"
        "ldr x19, [sp, #0x20]\n"
        "add sp, sp, #0x40\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103943a60 (96 bytes) — commit impl wrapper (w6=0)
// jemalloc 5.1.0: extent.c — extent_commit_zero
// =========================================================================
extern "C" __attribute__((naked))
u32 FUN_7103943a60(u64, u64, u64, u64, u64, u64) {
    asm(
        "sub sp, sp, #0x40\n"
        "stp x29, x30, [sp, #0x30]\n"
        "add x29, sp, #0x30\n"
        "stur x0, [x29, #-0x8]\n"
        "stur x1, [x29, #-0x10]\n"
        "str x2, [sp, #0x18]\n"
        "str x3, [sp, #0x10]\n"
        "str x4, [sp, #0x8]\n"
        "str x5, [sp]\n"
        "ldur x0, [x29, #-0x8]\n"
        "ldur x1, [x29, #-0x10]\n"
        "ldr x2, [sp, #0x18]\n"
        "ldr x3, [sp, #0x10]\n"
        "ldr x4, [sp, #0x8]\n"
        "ldr x5, [sp]\n"
        "mov w6, wzr\n"
        "bl FUN_7103941090\n"
        "and w0, w0, #0x1\n"
        "ldp x29, x30, [sp, #0x30]\n"
        "add sp, sp, #0x40\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103943ac0 (144 bytes) — extent split call with stack params
// jemalloc 5.1.0: extent.c — extent_split_wrapper
// 8 register params + 1 stack param
// =========================================================================
extern "C" __attribute__((naked))
u64 FUN_7103943ac0(u64, u64, u64, u64, u64, u32, u32, u64) {
    asm(
        "sub sp, sp, #0x70\n"
        "stp x29, x30, [sp, #0x60]\n"
        "add x29, sp, #0x60\n"
        "ldrb w8, [x29, #0x18]\n"
        "stur x0, [x29, #-0x8]\n"
        "stur x1, [x29, #-0x10]\n"
        "stur x2, [x29, #-0x18]\n"
        "stur x3, [x29, #-0x20]\n"
        "stur x4, [x29, #-0x28]\n"
        "stur w5, [x29, #-0x2c]\n"
        "and w9, w6, #0x1\n"
        "strb w9, [sp, #0x30]\n"
        "str x7, [sp, #0x28]\n"
        "and w8, w8, #0x1\n"
        "strb w8, [sp, #0x24]\n"
        "ldur x0, [x29, #-0x8]\n"
        "ldur x1, [x29, #-0x10]\n"
        "ldur x2, [x29, #-0x18]\n"
        "ldur x3, [x29, #-0x20]\n"
        "ldur x4, [x29, #-0x28]\n"
        "ldur w5, [x29, #-0x2c]\n"
        "ldr x7, [sp, #0x28]\n"
        "ldr w8, [x29, #0x10]\n"
        "ldrb w9, [sp, #0x24]\n"
        "ldrb w10, [sp, #0x30]\n"
        "strb wzr, [sp, #0x10]\n"
        "and w9, w9, #0x1\n"
        "strb w9, [sp, #0x8]\n"
        "str w8, [sp]\n"
        "and w6, w10, #0x1\n"
        "bl FUN_7103941400\n"
        "ldp x29, x30, [sp, #0x60]\n"
        "add sp, sp, #0x70\n"
        "ret\n"
    );
}

// =========================================================================
// 0x71039425a0 (192 bytes) — extent split + state update
// jemalloc 5.1.0: extent.c — extent_recycle_split
// Sets state, calls split, updates hook type
// =========================================================================
extern "C" __attribute__((naked))
u8 FUN_71039425a0(u64, u64, u64, u64, u64, u64) {
    asm(
        "sub sp, sp, #0x50\n"
        "str x19, [sp, #0x30]\n"
        "stp x29, x30, [sp, #0x40]\n"
        "add x29, sp, #0x40\n"
        "stur x0, [x29, #-0x18]\n"
        "str x1, [sp, #0x20]\n"
        "str x2, [sp, #0x18]\n"
        "str x3, [sp, #0x10]\n"
        "str x4, [sp, #0x8]\n"
        "str x5, [sp]\n"
        "ldr x0, [sp]\n"
        "mov w1, wzr\n"
        "bl FUN_710393e1a0\n"
        "ldur x0, [x29, #-0x18]\n"
        "ldr x1, [sp, #0x20]\n"
        "ldr x2, [sp, #0x18]\n"
        "ldr x3, [sp, #0x10]\n"
        "ldr x4, [sp, #0x8]\n"
        "ldr x5, [sp]\n"
        "sub x6, x29, #0x4\n"
        "mov w7, wzr\n"
        "bl FUN_710393df00\n"
        "str x0, [sp]\n"
        "ldr x19, [sp]\n"
        "ldr x0, [sp, #0x8]\n"
        "bl FUN_710393c1e0\n"
        "mov w1, w0\n"
        "mov x0, x19\n"
        "bl FUN_710393e1a0\n"
        "ldurb w8, [x29, #-0x4]\n"
        "tbnz w8, #0x0, 1f\n"
        "b 0f\n"
        "0: mov w8, #0x1\n"
        "sturb w8, [x29, #-0x1]\n"
        "b 3f\n"
        "1: ldur x0, [x29, #-0x18]\n"
        "ldr x1, [sp, #0x8]\n"
        "ldr x2, [sp]\n"
        "bl FUN_710393e1d0\n"
        "sturb wzr, [x29, #-0x1]\n"
        "b 3f\n"
        "3: ldurb w0, [x29, #-0x1]\n"
        "ldp x29, x30, [sp, #0x40]\n"
        "ldr x19, [sp, #0x30]\n"
        "add sp, sp, #0x50\n"
        "ret\n"
    );
}

#endif // MATCHING_HACK_NX_CLANG
