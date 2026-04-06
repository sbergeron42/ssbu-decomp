// jemalloc 5.1.0 — small accessors/nops batch 3 (pool-d, round 3)
// Address range: 0x71039300xx — 0x710393xxxx
// All compiled at -O0 in NX build; naked asm for byte-exact match.
// jemalloc 5.1.0: extent.h, arena.h, rtree.h, tsd.h, witness.h

#include "types.h"

#ifdef MATCHING_HACK_NX_CLANG

// External functions
extern "C" {
void* FUN_71037c9240(void);     // pthread/TLS (outside jemalloc)
void* FUN_710392ed50(void*);    // arena extent accessor (in pool-d d_002)
}

// External globals
extern "C" {
__attribute__((visibility("hidden"))) extern u8 DAT_7106d4a668;  // opt_retain dirty
__attribute__((visibility("hidden"))) extern u8 DAT_7106d4a670;  // opt_retain muzzy
}

// =========================================================================
// 0x7103930140 (24 bytes, leaf, -O0) — load u64 from pointer
// jemalloc 5.1.0: extent.h — return *(u64*)param
// [derived: ldr x0,[x8] → loads first qword]
// =========================================================================
extern "C" __attribute__((naked))
u64 FUN_7103930140(void*) {
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
// 0x7103930160 (28 bytes, leaf, -O0) — extent address extraction
// jemalloc 5.1.0: extent.h — returns [param+0x10] & ~0xFFFF (page-aligned addr)
// [derived: ldr+and mask pattern, extracts base address from extent]
// =========================================================================
extern "C" __attribute__((naked))
u64 FUN_7103930160(void*) {
    asm(
        "sub sp, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "ldr x8, [sp, #0x8]\n"
        "ldr x8, [x8, #0x10]\n"
        "and x0, x8, #-0x10000\n"
        "add sp, sp, #0x10\n"
        "ret\n"
    );
}

// =========================================================================
// 0x71039302c0 (28 bytes, leaf, -O0) — null check (returns param == NULL)
// jemalloc 5.1.0: extent.h — returns (param == 0) as bool
// [derived: subs+cset eq pattern]
// =========================================================================
extern "C" __attribute__((naked))
u32 FUN_71039302c0(void*) {
    asm(
        "sub sp, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "ldr x8, [sp, #0x8]\n"
        "subs x8, x8, #0x0\n"
        "cset w0, eq\n"
        "add sp, sp, #0x10\n"
        "ret\n"
    );
}

// =========================================================================
// 0x71039302e0 (28 bytes, leaf, -O0) — identity with branch nops
// jemalloc 5.1.0: extent.h — identity function
// [derived: store-branch-branch-load-return]
// =========================================================================
extern "C" __attribute__((naked))
void* FUN_71039302e0(void*) {
    asm(
        "sub sp, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "b 1f\n"
        "1: b 2f\n"
        "2: ldr x0, [sp, #0x8]\n"
        "add sp, sp, #0x10\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103930330 (28 bytes, leaf, -O0) — arena field accessor: +0x1800
// jemalloc 5.1.0: arena.h — returns &arena->field_0x1800
// [derived: orr w9,wzr,#0x1800 + add pattern]
// =========================================================================
extern "C" __attribute__((naked))
void* FUN_7103930330(void*) {
    asm(
        "sub sp, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "ldr x8, [sp, #0x8]\n"
        "orr w9, wzr, #0x1800\n"
        "add x0, x8, x9\n"
        "add sp, sp, #0x10\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103931300 (20 bytes, leaf, -O0) — identity function
// jemalloc 5.1.0: cast/identity — returns param unchanged
// [derived: store+load+return]
// =========================================================================
extern "C" __attribute__((naked))
void* FUN_7103931300(void*) {
    asm(
        "sub sp, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "ldr x0, [sp, #0x8]\n"
        "add sp, sp, #0x10\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103931690 (20 bytes, leaf, -O0) — halfword field read (high u16)
// jemalloc 5.1.0: extent.h — reads u16 from bits 48-63 of stored param
// [derived: ldrh w0,[sp,#0xe] reads bytes 6-7 of x0]
// =========================================================================
extern "C" __attribute__((naked))
u32 FUN_7103931690(u64) {
    asm(
        "sub sp, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "ldrh w0, [sp, #0xe]\n"
        "add sp, sp, #0x10\n"
        "ret\n"
    );
}

// =========================================================================
// 0x71039316b0 (24 bytes, leaf, -O0) — low bit extraction
// jemalloc 5.1.0: extent.h — returns param & 1
// [derived: ldr w8 then and w0,w8,#0x1]
// =========================================================================
extern "C" __attribute__((naked))
u32 FUN_71039316b0(u64) {
    asm(
        "sub sp, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "ldr w8, [sp, #0x8]\n"
        "and w0, w8, #0x1\n"
        "add sp, sp, #0x10\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103931ba0 (24 bytes, leaf, -O0) — field accessor: +0x28
// jemalloc 5.1.0: extent.h — returns &extent->field_0x28
// [derived: add immediate pattern]
// =========================================================================
extern "C" __attribute__((naked))
void* FUN_7103931ba0(void*) {
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
// 0x71039322b0 (28 bytes, leaf, -O0) — copy field [+4] to [+0]
// jemalloc 5.1.0: tsd.h — delete_stage equivalent for different module
// [derived: ldr w9,[x8,#4]; str w9,[x8] pattern]
// =========================================================================
extern "C" __attribute__((naked))
void FUN_71039322b0(void*) {
    asm(
        "sub sp, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "ldr x8, [sp, #0x8]\n"
        "ldr w9, [x8, #0x4]\n"
        "str w9, [x8]\n"
        "add sp, sp, #0x10\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103932450 (24 bytes, leaf, -O0) — field accessor: +0x4
// jemalloc 5.1.0: extent.h — returns &extent->field_0x4
// [derived: add immediate pattern]
// =========================================================================
extern "C" __attribute__((naked))
void* FUN_7103932450(void*) {
    asm(
        "sub sp, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "ldr x8, [sp, #0x8]\n"
        "add x0, x8, #0x4\n"
        "add sp, sp, #0x10\n"
        "ret\n"
    );
}

// =========================================================================
// 0x71039324a0 (24 bytes, leaf, -O0) — field accessor: +0x1b8
// jemalloc 5.1.0: extent.h — returns &extent->field_0x1b8
// [derived: add immediate pattern]
// =========================================================================
extern "C" __attribute__((naked))
void* FUN_71039324a0(void*) {
    asm(
        "sub sp, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "ldr x8, [sp, #0x8]\n"
        "add x0, x8, #0x1b8\n"
        "add sp, sp, #0x10\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103932870 (32 bytes, leaf, -O0) — load qword at +0x8 with branch nops
// jemalloc 5.1.0: extent.h — returns *(u64*)(param + 0x8)
// [derived: ldr x0,[x8,#0x8] with branch nops]
// =========================================================================
extern "C" __attribute__((naked))
u64 FUN_7103932870(void*) {
    asm(
        "sub sp, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "b 1f\n"
        "1: b 2f\n"
        "2: ldr x8, [sp, #0x8]\n"
        "ldr x0, [x8, #0x8]\n"
        "add sp, sp, #0x10\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103932890 (28 bytes, leaf, -O0) — bitfield extract: [*param] >> 0x28
// jemalloc 5.1.0: extent.h — extract bits [40:63] from extent header
// [derived: ldr+lsr #0x28, used for extent size/index field]
// =========================================================================
extern "C" __attribute__((naked))
u64 FUN_7103932890(void*) {
    asm(
        "sub sp, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "ldr x8, [sp, #0x8]\n"
        "ldr x8, [x8]\n"
        "lsr x0, x8, #0x28\n"
        "add sp, sp, #0x10\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103932b40 (32 bytes, leaf, -O0) — field accessor: +0x40 with branch nops
// jemalloc 5.1.0: extent.h — returns &extent->field_0x40
// [derived: add immediate with branch nops]
// =========================================================================
extern "C" __attribute__((naked))
void* FUN_7103932b40(void*) {
    asm(
        "sub sp, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "b 1f\n"
        "1: b 2f\n"
        "2: ldr x8, [sp, #0x8]\n"
        "add x0, x8, #0x40\n"
        "add sp, sp, #0x10\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103933610 (32 bytes, -O0) — TLS call wrapper
// jemalloc 5.1.0: tsd.h — wraps pthread/TLS call to FUN_71037c9240
// [derived: frame pointer + branch nops + bl external]
// =========================================================================
extern "C" __attribute__((naked))
void* FUN_7103933610(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "b 1f\n"
        "1: b 2f\n"
        "2: bl FUN_71037c9240\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103933660 (24 bytes, leaf, -O0) — tsd field accessor: +0x1c0
// [derived: add immediate pattern]
// =========================================================================
extern "C" __attribute__((naked))
void* FUN_7103933660(void*) {
    asm(
        "sub sp, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "ldr x8, [sp, #0x8]\n"
        "add x0, x8, #0x1c0\n"
        "add sp, sp, #0x10\n"
        "ret\n"
    );
}

// =========================================================================
// 0x71039336e0 (24 bytes, leaf, -O0) — field accessor: +0x1
// [derived: add immediate pattern]
// =========================================================================
extern "C" __attribute__((naked))
void* FUN_71039336e0(void*) {
    asm(
        "sub sp, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "ldr x8, [sp, #0x8]\n"
        "add x0, x8, #0x1\n"
        "add sp, sp, #0x10\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103933730 (24 bytes, leaf, -O0) — tsd field accessor: +0x1b0
// [derived: add immediate pattern]
// =========================================================================
extern "C" __attribute__((naked))
void* FUN_7103933730(void*) {
    asm(
        "sub sp, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "ldr x8, [sp, #0x8]\n"
        "add x0, x8, #0x1b0\n"
        "add sp, sp, #0x10\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103933780 (24 bytes, leaf, -O0) — tsd field accessor: +0x1a8
// [derived: add immediate pattern]
// =========================================================================
extern "C" __attribute__((naked))
void* FUN_7103933780(void*) {
    asm(
        "sub sp, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "ldr x8, [sp, #0x8]\n"
        "add x0, x8, #0x1a8\n"
        "add sp, sp, #0x10\n"
        "ret\n"
    );
}

// =========================================================================
// 0x71039337d0 (24 bytes, leaf, -O0) — field accessor: +0x3
// [derived: add immediate pattern]
// =========================================================================
extern "C" __attribute__((naked))
void* FUN_71039337d0(void*) {
    asm(
        "sub sp, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "ldr x8, [sp, #0x8]\n"
        "add x0, x8, #0x3\n"
        "add sp, sp, #0x10\n"
        "ret\n"
    );
}

// =========================================================================
// 0x71039353c0 (32 bytes, -O0) — arena dirty decay accessor
// jemalloc 5.1.0: arena.c — wraps FUN_710392ed50 with &opt_retain_dirty
// DAT_7106d4a668 = opt_retain flags [derived: adrp+add to .bss]
// =========================================================================
extern "C" __attribute__((naked))
void* FUN_71039353c0(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "adrp x0, DAT_7106d4a668\n"
        "add x0, x0, :lo12:DAT_7106d4a668\n"
        "bl FUN_710392ed50\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103935440 (32 bytes, -O0) — arena muzzy decay accessor
// jemalloc 5.1.0: arena.c — wraps FUN_710392ed50 with &opt_retain_muzzy
// DAT_7106d4a670 = opt_retain muzzy flags [derived: adrp+add to .bss]
// =========================================================================
extern "C" __attribute__((naked))
void* FUN_7103935440(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "adrp x0, DAT_7106d4a670\n"
        "add x0, x0, :lo12:DAT_7106d4a670\n"
        "bl FUN_710392ed50\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103935f80 (24 bytes, leaf, -O0) — nop (store param, return)
// jemalloc 5.1.0: witness.h — debug stub
// [derived: store+branch+branch+return]
// =========================================================================
extern "C" __attribute__((naked))
void FUN_7103935f80(void*) {
    asm(
        "sub sp, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "b 1f\n"
        "1: b 2f\n"
        "2: add sp, sp, #0x10\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103936250 (24 bytes, leaf, -O0) — zero-store to pointer (no branch nops)
// jemalloc 5.1.0: extent.c — *param = 0
// [derived: str xzr,[x8] pattern]
// =========================================================================
extern "C" __attribute__((naked))
void FUN_7103936250(void*) {
    asm(
        "sub sp, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "ldr x8, [sp, #0x8]\n"
        "str xzr, [x8]\n"
        "add sp, sp, #0x10\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103936cb0 (24 bytes, leaf, -O0) — load u16 at +0x10
// jemalloc 5.1.0: arena.c — returns *(u16*)(param + 0x10)
// [derived: ldrh w0,[x8,#0x10]]
// =========================================================================
extern "C" __attribute__((naked))
u32 FUN_7103936cb0(void*) {
    asm(
        "sub sp, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "ldr x8, [sp, #0x8]\n"
        "ldrh w0, [x8, #0x10]\n"
        "add sp, sp, #0x10\n"
        "ret\n"
    );
}

// =========================================================================
// 0x71039388d0 (20 bytes, leaf, -O0) — store nop (2 params, 0x20 frame)
// [derived: stores 2 params, returns void]
// =========================================================================
extern "C" __attribute__((naked))
void FUN_71039388d0(void*, void*) {
    asm(
        "sub sp, sp, #0x20\n"
        "str x0, [sp, #0x18]\n"
        "str x1, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 0x71039388f0 (28 bytes, leaf, -O0) — null check
// [derived: subs+cset eq pattern]
// =========================================================================
extern "C" __attribute__((naked))
u32 FUN_71039388f0(void*) {
    asm(
        "sub sp, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "ldr x8, [sp, #0x8]\n"
        "subs x8, x8, #0x0\n"
        "cset w0, eq\n"
        "add sp, sp, #0x10\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103938910 (28 bytes, leaf, -O0) — identity with branch nops
// [derived: store-branch-branch-load-return]
// =========================================================================
extern "C" __attribute__((naked))
void* FUN_7103938910(void*) {
    asm(
        "sub sp, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "b 1f\n"
        "1: b 2f\n"
        "2: ldr x0, [sp, #0x8]\n"
        "add sp, sp, #0x10\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103938960 (28 bytes, leaf, -O0) — field accessor: +0x1800
// [derived: orr w9,wzr,#0x1800 + add pattern]
// =========================================================================
extern "C" __attribute__((naked))
void* FUN_7103938960(void*) {
    asm(
        "sub sp, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "ldr x8, [sp, #0x8]\n"
        "orr w9, wzr, #0x1800\n"
        "add x0, x8, x9\n"
        "add sp, sp, #0x10\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103938980 (20 bytes, leaf, -O0) — store nop (2 params, 0x30 frame)
// [derived: stores 2 params, returns void]
// =========================================================================
extern "C" __attribute__((naked))
void FUN_7103938980(void*, void*) {
    asm(
        "sub sp, sp, #0x30\n"
        "str x0, [sp, #0x28]\n"
        "str x1, [sp, #0x20]\n"
        "add sp, sp, #0x30\n"
        "ret\n"
    );
}

// =========================================================================
// 0x71039389d0 (20 bytes, leaf, -O0) — store nop (2 params, 0x10 frame)
// [derived: stores 2 params, returns void]
// =========================================================================
extern "C" __attribute__((naked))
void FUN_71039389d0(void*, void*) {
    asm(
        "sub sp, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "str x1, [sp]\n"
        "add sp, sp, #0x10\n"
        "ret\n"
    );
}

// =========================================================================
// 0x71039389f0 (20 bytes, leaf, -O0) — store nop (2 params, 0x30 frame)
// [derived: stores 2 params, returns void]
// =========================================================================
extern "C" __attribute__((naked))
void FUN_71039389f0(void*, void*) {
    asm(
        "sub sp, sp, #0x30\n"
        "str x0, [sp, #0x28]\n"
        "str x1, [sp, #0x20]\n"
        "add sp, sp, #0x30\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103938af0 (24 bytes, leaf, -O0) — zero-store to pointer
// jemalloc 5.1.0: extent.c — *param = 0
// [derived: str xzr,[x8] pattern]
// =========================================================================
extern "C" __attribute__((naked))
void FUN_7103938af0(void*) {
    asm(
        "sub sp, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "ldr x8, [sp, #0x8]\n"
        "str xzr, [x8]\n"
        "add sp, sp, #0x10\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103938b10 (32 bytes, leaf, -O0) — deref + null check
// jemalloc 5.1.0: extent.h — returns (*param == NULL)
// [derived: ldr+subs+cset eq, dereferences pointer then null checks]
// =========================================================================
extern "C" __attribute__((naked))
u32 FUN_7103938b10(void*) {
    asm(
        "sub sp, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "ldr x8, [sp, #0x8]\n"
        "ldr x8, [x8]\n"
        "subs x8, x8, #0x0\n"
        "cset w0, eq\n"
        "add sp, sp, #0x10\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103939580 (32 bytes, leaf, -O0) — load qword at +0x8 with branch nops
// [derived: ldr x0,[x8,#0x8] with branch nops]
// =========================================================================
extern "C" __attribute__((naked))
u64 FUN_7103939580(void*) {
    asm(
        "sub sp, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "b 1f\n"
        "1: b 2f\n"
        "2: ldr x8, [sp, #0x8]\n"
        "ldr x0, [x8, #0x8]\n"
        "add sp, sp, #0x10\n"
        "ret\n"
    );
}

// =========================================================================
// 0x71039395a0 (28 bytes, leaf, -O0) — bitfield extract: [*param] >> 0x28
// [derived: ldr+lsr #0x28 pattern]
// =========================================================================
extern "C" __attribute__((naked))
u64 FUN_71039395a0(void*) {
    asm(
        "sub sp, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "ldr x8, [sp, #0x8]\n"
        "ldr x8, [x8]\n"
        "lsr x0, x8, #0x28\n"
        "add sp, sp, #0x10\n"
        "ret\n"
    );
}

// =========================================================================
// 0x710393c150 (32 bytes, leaf, -O0) — zero-store with branch nops
// jemalloc 5.1.0: extent.c — *param = 0 (with branch nops)
// [derived: str xzr,[x8] with 2 branch nops]
// =========================================================================
extern "C" __attribute__((naked))
void FUN_710393c150(void*) {
    asm(
        "sub sp, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "b 1f\n"
        "1: ldr x8, [sp, #0x8]\n"
        "str xzr, [x8]\n"
        "b 2f\n"
        "2: add sp, sp, #0x10\n"
        "ret\n"
    );
}

// =========================================================================
// 0x710393c1e0 (24 bytes, leaf, -O0) — load u32 at +0x690
// jemalloc 5.1.0: arena.c — returns *(u32*)(param + 0x690)
// [derived: ldr w0,[x8,#0x690] — arena struct field]
// =========================================================================
extern "C" __attribute__((naked))
u32 FUN_710393c1e0(void*) {
    asm(
        "sub sp, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "ldr x8, [sp, #0x8]\n"
        "ldr w0, [x8, #0x690]\n"
        "add sp, sp, #0x10\n"
        "ret\n"
    );
}

// =========================================================================
// 0x710393c360 (28 bytes, leaf, -O0) — arena decay init params nop
// jemalloc 5.1.0: arena.c — stores params with constant 0xb, nop
// [derived: mov w8,#0xb constant, stores 3 values]
// =========================================================================
extern "C" __attribute__((naked))
void FUN_710393c360(void*, u32) {
    asm(
        "sub sp, sp, #0x30\n"
        "str x0, [sp, #0x28]\n"
        "mov w8, #0xb\n"
        "str w8, [sp, #0x24]\n"
        "str w1, [sp, #0x20]\n"
        "add sp, sp, #0x30\n"
        "ret\n"
    );
}

// =========================================================================
// 0x710393ca60 (28 bytes, leaf, -O0) — bitfield extract: bit 13
// jemalloc 5.1.0: extent.h — ubfx extracts single bit at position 13
// [derived: ubfx x0,x8,#0xd,#0x1 pattern]
// =========================================================================
extern "C" __attribute__((naked))
u64 FUN_710393ca60(void*) {
    asm(
        "sub sp, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "ldr x8, [sp, #0x8]\n"
        "ldr x8, [x8]\n"
        "ubfx x0, x8, #0xd, #0x1\n"
        "add sp, sp, #0x10\n"
        "ret\n"
    );
}

// =========================================================================
// 0x710393ca80 (28 bytes, leaf, -O0) — extent address extraction
// jemalloc 5.1.0: extent.h — returns [param+0x10] & ~0xFFFF
// [derived: ldr+and mask pattern]
// =========================================================================
extern "C" __attribute__((naked))
u64 FUN_710393ca80(void*) {
    asm(
        "sub sp, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "ldr x8, [sp, #0x8]\n"
        "ldr x8, [x8, #0x10]\n"
        "and x0, x8, #-0x10000\n"
        "add sp, sp, #0x10\n"
        "ret\n"
    );
}

// =========================================================================
// 0x710393cdf0 (28 bytes, leaf, -O0) — bitfield extract: bit 15
// jemalloc 5.1.0: extent.h — ubfx extracts single bit at position 15
// [derived: ubfx x0,x8,#0xf,#0x1 pattern]
// =========================================================================
extern "C" __attribute__((naked))
u64 FUN_710393cdf0(void*) {
    asm(
        "sub sp, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "ldr x8, [sp, #0x8]\n"
        "ldr x8, [x8]\n"
        "ubfx x0, x8, #0xf, #0x1\n"
        "add sp, sp, #0x10\n"
        "ret\n"
    );
}

#endif // MATCHING_HACK_NX_CLANG
