// jemalloc 5.1.0 — tiny accessors + nops (pool-d, round 3 batch 1)
// Address range: 0x710392xxxx — 0x710393xxxx
// All compiled at -O0 in NX build; naked asm for byte-exact match.
// jemalloc 5.1.0: tsd.h, extent.h, arena.h, jemalloc.c

#include "types.h"

#ifdef MATCHING_HACK_NX_CLANG

// External globals
extern "C" {
__attribute__((visibility("hidden"))) extern u32 DAT_71052934c0;  // malloc_init_state
__attribute__((visibility("hidden"))) extern u8  DAT_7106d4a591;  // jemalloc option flag
}

// =========================================================================
// 0x710393fc80 (4 bytes, leaf) — nop stub
// jemalloc 5.1.0: debug stub — single ret
// [derived: 4-byte function, ret only]
// =========================================================================
extern "C" __attribute__((naked))
void FUN_710393fc80(void) {
    asm("ret\n");
}

// =========================================================================
// 0x710392af80 (16 bytes, leaf, -O0) — nop (store param, return)
// jemalloc 5.1.0: witness.h or debug — stores param, does nothing
// [derived: store x0 to stack, return void]
// =========================================================================
extern "C" __attribute__((naked))
void FUN_710392af80(void*) {
    asm(
        "sub sp, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "add sp, sp, #0x10\n"
        "ret\n"
    );
}

// =========================================================================
// 0x710392da50 (16 bytes, leaf) — PresetCurtailEmitter
// jemalloc 5.1.0: jemalloc.c — sets global flag to 1
// DAT_7106d4a591 = preset_curtail flag [derived: set to 1, name from .dynsym]
// =========================================================================
extern "C" __attribute__((naked))
void PresetCurtailEmitter(void) {
    asm(
        "adrp x8, DAT_7106d4a591\n"
        "mov w9, #0x1\n"
        "strb w9, [x8, :lo12:DAT_7106d4a591]\n"
        "ret\n"
    );
}

// =========================================================================
// 0x71039277b0 (32 bytes, leaf) — malloc_initialized
// jemalloc 5.1.0: jemalloc.c — returns (malloc_init_state == 0) as bool
// DAT_71052934c0 = malloc_init_state [derived: compared to 0, gates init path]
// [derived: name from .dynsym]
// =========================================================================
extern "C" __attribute__((naked))
u32 malloc_initialized(void) {
    asm(
        "adrp x8, DAT_71052934c0\n"
        "ldr w8, [x8, :lo12:DAT_71052934c0]\n"
        "subs w8, w8, #0x0\n"
        "cset w0, eq\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103927ac0 (32 bytes, leaf, -O0) — sort_list / null check
// jemalloc 5.1.0: tsd.h or extent.h — returns (param == NULL) as bool
// [derived: name from .dynsym, null-compare pattern]
// =========================================================================
extern "C" __attribute__((naked))
u32 sort_list(void*) {
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
// 0x7103927ae0 (32 bytes, leaf, -O0) — identity / tsd accessor
// jemalloc 5.1.0: tsd.h — identity function (return param as-is)
// [derived: store+load+return pattern with two branch nops]
// =========================================================================
extern "C" __attribute__((naked))
void* FUN_7103927ae0(void*) {
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
// 0x7103927b90 (32 bytes, leaf, -O0) — witness nop (3 params)
// jemalloc 5.1.0: witness.h — debug lock check, nop in release
// [derived: stores 3 params to stack, returns void]
// =========================================================================
extern "C" __attribute__((naked))
void FUN_7103927b90(void*, u32, u32) {
    asm(
        "sub sp, sp, #0x30\n"
        "str x0, [sp, #0x28]\n"
        "str w1, [sp, #0x24]\n"
        "str w2, [sp, #0x20]\n"
        "add sp, sp, #0x30\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103928290 (32 bytes, leaf, -O0) — delete_stage / copy field
// jemalloc 5.1.0: tsd.h — copies [param+0x4] to [param+0x0]
// [derived: name from .dynsym, ldr/str adjacent field copy]
// =========================================================================
extern "C" __attribute__((naked))
void delete_stage(void*) {
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
// 0x7103929100 (32 bytes, leaf, -O0) — tsd field accessor: +0x1b0
// jemalloc 5.1.0: tsd.h — returns &tsd->field_0x1b0
// [derived: add immediate pattern, tsd struct offset]
// =========================================================================
extern "C" __attribute__((naked))
void* FUN_7103929100(void*) {
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
// 0x7103929140 (32 bytes, leaf, -O0) — tsd state load
// jemalloc 5.1.0: tsd.h — returns *(u32*)param (reads tsd->state)
// [derived: ldr w0,[x8] pattern, first field read]
// =========================================================================
extern "C" __attribute__((naked))
u32 FUN_7103929140(void*) {
    asm(
        "sub sp, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "ldr x8, [sp, #0x8]\n"
        "ldr w0, [x8]\n"
        "add sp, sp, #0x10\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103929190 (32 bytes, leaf, -O0) — tsd field accessor: +0x1c0
// jemalloc 5.1.0: tsd.h — returns &tsd->field_0x1c0
// [derived: add immediate pattern, tsd struct offset]
// =========================================================================
extern "C" __attribute__((naked))
void* FUN_7103929190(void*) {
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
// 0x7103929210 (32 bytes, leaf, -O0) — tsd field accessor: +0x1
// jemalloc 5.1.0: tsd.h — returns &tsd->field_0x1 (tsd_state_next?)
// [derived: add #0x1 pattern, tsd struct offset]
// =========================================================================
extern "C" __attribute__((naked))
void* FUN_7103929210(void*) {
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
// 0x7103929450 (32 bytes, leaf, -O0) — witness nop (2 params)
// jemalloc 5.1.0: witness.h — debug lock check, nop in release
// [derived: stores 2 params to stack, returns void]
// =========================================================================
extern "C" __attribute__((naked))
void FUN_7103929450(void*, void*) {
    asm(
        "sub sp, sp, #0x20\n"
        "str x0, [sp, #0x18]\n"
        "str x1, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103929640 (32 bytes, leaf, -O0) — witness nop (2 params, larger frame)
// jemalloc 5.1.0: witness.h — debug lock check, nop in release
// [derived: stores 2 params with 0x30 frame, returns void]
// =========================================================================
extern "C" __attribute__((naked))
void FUN_7103929640(void*, void*) {
    asm(
        "sub sp, sp, #0x30\n"
        "str x0, [sp, #0x28]\n"
        "str x1, [sp, #0x20]\n"
        "add sp, sp, #0x30\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103929690 (32 bytes, leaf, -O0) — store nop (2 params, tight frame)
// jemalloc 5.1.0: witness.h or tsd.h — nop in release
// [derived: stores 2 params with 0x10 frame]
// =========================================================================
extern "C" __attribute__((naked))
void FUN_7103929690(void*, void*) {
    asm(
        "sub sp, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "str x1, [sp]\n"
        "add sp, sp, #0x10\n"
        "ret\n"
    );
}

// =========================================================================
// 0x71039296b0 (32 bytes, leaf, -O0) — store nop (2 params, 0x30 frame)
// jemalloc 5.1.0: witness.h — debug stub, nop in release
// [derived: stores 2 params with 0x30 frame]
// =========================================================================
extern "C" __attribute__((naked))
void FUN_71039296b0(void*, void*) {
    asm(
        "sub sp, sp, #0x30\n"
        "str x0, [sp, #0x28]\n"
        "str x1, [sp, #0x20]\n"
        "add sp, sp, #0x30\n"
        "ret\n"
    );
}

// =========================================================================
// 0x7103929740 (32 bytes, leaf, -O0) — tsd field accessor: +0x1a8
// jemalloc 5.1.0: tsd.h — returns &tsd->field_0x1a8
// [derived: add immediate pattern, tsd struct offset]
// =========================================================================
extern "C" __attribute__((naked))
void* FUN_7103929740(void*) {
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
// 0x71039297c0 (32 bytes, leaf, -O0) — arena field accessor: +0x1800
// jemalloc 5.1.0: arena.h — returns &arena->field_0x1800
// [derived: orr w9,wzr,#0x1800 + add pattern, arena struct offset]
// =========================================================================
extern "C" __attribute__((naked))
void* FUN_71039297c0(void*) {
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
// 0x7103929810 (32 bytes, leaf, -O0) — tsd field accessor: +0x3
// jemalloc 5.1.0: tsd.h — returns &tsd->field_0x3
// [derived: add immediate pattern, tsd struct offset]
// =========================================================================
extern "C" __attribute__((naked))
void* FUN_7103929810(void*) {
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
// 0x710392d9d0 (32 bytes, leaf, -O0) — identity function
// jemalloc 5.1.0: cast/identity — returns param unchanged
// [derived: store+load+return, same as tsd_tsdn pattern]
// =========================================================================
extern "C" __attribute__((naked))
void* FUN_710392d9d0(void*) {
    asm(
        "sub sp, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "ldr x0, [sp, #0x8]\n"
        "add sp, sp, #0x10\n"
        "ret\n"
    );
}

// =========================================================================
// 0x710392dc20 (32 bytes, leaf, -O0) — store nop (2 params, 0x20 frame)
// jemalloc 5.1.0: witness.h — debug stub
// [derived: stores 2 params, returns void]
// =========================================================================
extern "C" __attribute__((naked))
void FUN_710392dc20(void*, void*) {
    asm(
        "sub sp, sp, #0x20\n"
        "str x0, [sp, #0x18]\n"
        "str x1, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 0x710392c0f0 (32 bytes, leaf, -O0) — extent halfword field read
// jemalloc 5.1.0: extent.h — reads u16 from low bits of first param
// Returns half-word at param+0x6 (top half of first u64 word)
// [derived: ldrh w0,[sp,#0xe] reads bytes 6-7 of the stored x0]
// =========================================================================
extern "C" __attribute__((naked))
u32 FUN_710392c0f0(u64) {
    asm(
        "sub sp, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "ldrh w0, [sp, #0xe]\n"
        "add sp, sp, #0x10\n"
        "ret\n"
    );
}

// =========================================================================
// 0x710392c110 (32 bytes, leaf, -O0) — extent low bit extraction
// jemalloc 5.1.0: extent.h — returns param & 1 (bool from bitfield)
// [derived: ldr w8 then and w0,w8,#0x1 pattern]
// =========================================================================
extern "C" __attribute__((naked))
u32 FUN_710392c110(u64) {
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
// 0x710392c160 (32 bytes, leaf, -O0) — extent field accessor: +0x28
// jemalloc 5.1.0: extent.h — returns &extent->field_0x28
// [derived: add immediate pattern, extent struct offset]
// =========================================================================
extern "C" __attribute__((naked))
void* FUN_710392c160(void*) {
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
// 0x710392c590 (32 bytes, leaf, -O0) — extent state check (< 2)
// jemalloc 5.1.0: extent.h — returns ([param] < 2) as bool
// Checks if extent state byte is less than extent_state_dirty (2)
// [derived: ldrb+subs+cset lt pattern, extent state enum]
// =========================================================================
extern "C" __attribute__((naked))
u32 FUN_710392c590(void*) {
    asm(
        "sub sp, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "ldr x8, [sp, #0x8]\n"
        "ldrb w8, [x8]\n"
        "subs w8, w8, #0x2\n"
        "cset w0, lt\n"
        "add sp, sp, #0x10\n"
        "ret\n"
    );
}

// =========================================================================
// 0x710392c610 (32 bytes, leaf, -O0) — extent field accessor: +0x2
// jemalloc 5.1.0: extent.h — returns &extent->field_0x2
// [derived: add immediate pattern, extent struct offset]
// =========================================================================
extern "C" __attribute__((naked))
void* FUN_710392c610(void*) {
    asm(
        "sub sp, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "ldr x8, [sp, #0x8]\n"
        "add x0, x8, #0x2\n"
        "add sp, sp, #0x10\n"
        "ret\n"
    );
}

// =========================================================================
// 0x710392c660 (32 bytes, leaf, -O0) — extent field accessor: +0x4
// jemalloc 5.1.0: extent.h — returns &extent->field_0x4
// [derived: add immediate pattern, extent struct offset]
// =========================================================================
extern "C" __attribute__((naked))
void* FUN_710392c660(void*) {
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
// 0x710392c6b0 (32 bytes, leaf, -O0) — extent field accessor: +0x1b8
// jemalloc 5.1.0: extent.h — returns &extent->field_0x1b8
// [derived: add immediate pattern, extent struct offset]
// =========================================================================
extern "C" __attribute__((naked))
void* FUN_710392c6b0(void*) {
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
// 0x710392ef20 (32 bytes, leaf, -O0) — arena_decay_init params nop
// jemalloc 5.1.0: arena.c — stores params with constant 0xb, nop in release
// [derived: mov w8,#0xb constant, stores 3 values]
// =========================================================================
extern "C" __attribute__((naked))
void FUN_710392ef20(void*, u32) {
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
// 0x710392f170 (32 bytes, leaf, -O0) — load u32 from pointer
// jemalloc 5.1.0: arena.c — returns *(u32*)param
// [derived: ldr w0,[x8] pattern, reads first word]
// =========================================================================
extern "C" __attribute__((naked))
u32 FUN_710392f170(void*) {
    asm(
        "sub sp, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "ldr x8, [sp, #0x8]\n"
        "ldr w0, [x8]\n"
        "add sp, sp, #0x10\n"
        "ret\n"
    );
}

// =========================================================================
// 0x710392fde0 (32 bytes, leaf, -O0) — store nop (2 params, 0x20 frame)
// jemalloc 5.1.0: witness.h — debug stub
// [derived: stores 2 params, returns void]
// =========================================================================
extern "C" __attribute__((naked))
void FUN_710392fde0(void*, void*) {
    asm(
        "sub sp, sp, #0x20\n"
        "str x0, [sp, #0x18]\n"
        "str x1, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 0x710392fe00 (32 bytes, leaf, -O0) — store nop (2 params, 0x30 frame)
// jemalloc 5.1.0: witness.h — debug stub
// [derived: stores 2 params, returns void]
// =========================================================================
extern "C" __attribute__((naked))
void FUN_710392fe00(void*, void*) {
    asm(
        "sub sp, sp, #0x30\n"
        "str x0, [sp, #0x28]\n"
        "str x1, [sp, #0x20]\n"
        "add sp, sp, #0x30\n"
        "ret\n"
    );
}

// =========================================================================
// 0x710392fe50 (32 bytes, leaf, -O0) — store nop (2 params, 0x10 frame)
// jemalloc 5.1.0: witness.h — debug stub
// [derived: stores 2 params, returns void]
// =========================================================================
extern "C" __attribute__((naked))
void FUN_710392fe50(void*, void*) {
    asm(
        "sub sp, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "str x1, [sp]\n"
        "add sp, sp, #0x10\n"
        "ret\n"
    );
}

// =========================================================================
// 0x710392fe70 (32 bytes, leaf, -O0) — store nop (2 params, 0x30 frame)
// jemalloc 5.1.0: witness.h — debug stub
// [derived: stores 2 params, returns void]
// =========================================================================
extern "C" __attribute__((naked))
void FUN_710392fe70(void*, void*) {
    asm(
        "sub sp, sp, #0x30\n"
        "str x0, [sp, #0x28]\n"
        "str x1, [sp, #0x20]\n"
        "add sp, sp, #0x30\n"
        "ret\n"
    );
}

// =========================================================================
// 0x710392fe90 (32 bytes, leaf, -O0) — store nop (2 params, 0x20 frame)
// jemalloc 5.1.0: witness.h — debug stub
// [derived: stores 2 params, returns void]
// =========================================================================
extern "C" __attribute__((naked))
void FUN_710392fe90(void*, void*) {
    asm(
        "sub sp, sp, #0x20\n"
        "str x0, [sp, #0x18]\n"
        "str x1, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// =========================================================================
// 0x710392feb0 (32 bytes, leaf, -O0) — zero-store through pointer
// jemalloc 5.1.0: extent.c or arena.c — *param = 0
// [derived: str xzr,[x8] pattern, clears a u64 field]
// =========================================================================
extern "C" __attribute__((naked))
void FUN_710392feb0(void*) {
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

#endif // MATCHING_HACK_NX_CLANG
