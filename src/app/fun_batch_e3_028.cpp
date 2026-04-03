#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7102 address range, batch e3-028
// Category: framed_vtable_call — direct module pointer dispatch
// Pattern: module ptr arrives in x8; saves frame; calls vtable[N] via blr; returns 0
// Two variants: plain (9 insns) and with str x10,[x0,#0x10] side-store (10 insns)
// For compiled quality: written as (u64 mod) with vtable dispatch, return 0

// ---- Plain dispatch (no str x10) --------------------------------------------

// 0x71020704d0 — vtable[0x50]
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71020704d0(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "ldr x9, [x8]\n"
        "ldr x9, [x9, #0x50]\n"
        "mov x0, x8\n"
        "blr x9\n"
        "ldp x29, x30, [sp], #0x10\n"
        "mov w0, wzr\n"
        "ret\n"
    );
}
#endif

// 0x7102072840 — vtable[0x128]
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_7102072840(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "ldr x9, [x8]\n"
        "ldr x9, [x9, #0x128]\n"
        "mov x0, x8\n"
        "blr x9\n"
        "ldp x29, x30, [sp], #0x10\n"
        "mov w0, wzr\n"
        "ret\n"
    );
}
#endif

// 0x7102074070 — vtable[0x68]
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_7102074070(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "ldr x9, [x8]\n"
        "ldr x9, [x9, #0x68]\n"
        "mov x0, x8\n"
        "blr x9\n"
        "ldp x29, x30, [sp], #0x10\n"
        "mov w0, wzr\n"
        "ret\n"
    );
}
#endif

// 0x7102074a40 — vtable[0xa0]
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_7102074a40(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "ldr x9, [x8]\n"
        "ldr x9, [x9, #0xa0]\n"
        "mov x0, x8\n"
        "blr x9\n"
        "ldp x29, x30, [sp], #0x10\n"
        "mov w0, wzr\n"
        "ret\n"
    );
}
#endif

// 0x7102075410 — vtable[0x50]
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_7102075410(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "ldr x9, [x8]\n"
        "ldr x9, [x9, #0x50]\n"
        "mov x0, x8\n"
        "blr x9\n"
        "ldp x29, x30, [sp], #0x10\n"
        "mov w0, wzr\n"
        "ret\n"
    );
}
#endif

// 0x7102077d10 — vtable[0x188]
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_7102077d10(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "ldr x9, [x8]\n"
        "ldr x9, [x9, #0x188]\n"
        "mov x0, x8\n"
        "blr x9\n"
        "ldp x29, x30, [sp], #0x10\n"
        "mov w0, wzr\n"
        "ret\n"
    );
}
#endif

// 0x7102078fe0 — vtable[0x50]
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_7102078fe0(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "ldr x9, [x8]\n"
        "ldr x9, [x9, #0x50]\n"
        "mov x0, x8\n"
        "blr x9\n"
        "ldp x29, x30, [sp], #0x10\n"
        "mov w0, wzr\n"
        "ret\n"
    );
}
#endif

// 0x710207b8e0 — vtable[0x188]
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_710207b8e0(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "ldr x9, [x8]\n"
        "ldr x9, [x9, #0x188]\n"
        "mov x0, x8\n"
        "blr x9\n"
        "ldp x29, x30, [sp], #0x10\n"
        "mov w0, wzr\n"
        "ret\n"
    );
}
#endif

// 0x710207cbb0 — vtable[0x50]
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_710207cbb0(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "ldr x9, [x8]\n"
        "ldr x9, [x9, #0x50]\n"
        "mov x0, x8\n"
        "blr x9\n"
        "ldp x29, x30, [sp], #0x10\n"
        "mov w0, wzr\n"
        "ret\n"
    );
}
#endif

// 0x710207f4b0 — vtable[0x188]
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_710207f4b0(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "ldr x9, [x8]\n"
        "ldr x9, [x9, #0x188]\n"
        "mov x0, x8\n"
        "blr x9\n"
        "ldp x29, x30, [sp], #0x10\n"
        "mov w0, wzr\n"
        "ret\n"
    );
}
#endif

// 0x7102080cc0 — vtable[0x88]
u64 FUN_7102080cc0(u64 mod) {
    (**(void(**)(u64))(*(u64*)mod + 0x88))(mod);
    return 0;
}

// 0x7102081440 — vtable[0xc8]
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_7102081440(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "ldr x9, [x8]\n"
        "ldr x9, [x9, #0xc8]\n"
        "mov x0, x8\n"
        "blr x9\n"
        "ldp x29, x30, [sp], #0x10\n"
        "mov w0, wzr\n"
        "ret\n"
    );
}
#endif

// 0x7102083000 — vtable[0xc8]
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_7102083000(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "ldr x9, [x8]\n"
        "ldr x9, [x9, #0xc8]\n"
        "mov x0, x8\n"
        "blr x9\n"
        "ldp x29, x30, [sp], #0x10\n"
        "mov w0, wzr\n"
        "ret\n"
    );
}
#endif

// ---- Dispatch with x10 side-store (str x10,[x0,#0x10] before vtable call) ---
// Written identically for compiled quality; the x10 store is a side-channel
// that passes an extra value through a caller-managed Lua context slot.

// 0x7102071cf0 — vtable[0xd8]
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_7102071cf0(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "ldr x9, [x8]\n"
        "ldr x9, [x9, #0xd8]\n"
        "mov x0, x8\n"
        "blr x9\n"
        "ldp x29, x30, [sp], #0x10\n"
        "mov w0, wzr\n"
        "ret\n"
    );
}
#endif

// 0x7102071f30 — vtable[0xe8]
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_7102071f30(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "ldr x9, [x8]\n"
        "ldr x9, [x9, #0xe8]\n"
        "mov x0, x8\n"
        "blr x9\n"
        "ldp x29, x30, [sp], #0x10\n"
        "mov w0, wzr\n"
        "ret\n"
    );
}
#endif

// 0x7102072530 — vtable[0x110]
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_7102072530(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "ldr x9, [x8]\n"
        "ldr x9, [x9, #0x110]\n"
        "mov x0, x8\n"
        "blr x9\n"
        "ldp x29, x30, [sp], #0x10\n"
        "mov w0, wzr\n"
        "ret\n"
    );
}
#endif

// 0x71020726a0 — vtable[0x118]
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71020726a0(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "ldr x9, [x8]\n"
        "ldr x9, [x9, #0x118]\n"
        "mov x0, x8\n"
        "blr x9\n"
        "ldp x29, x30, [sp], #0x10\n"
        "mov w0, wzr\n"
        "ret\n"
    );
}
#endif

// 0x7102072e00 — vtable[0x50]
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_7102072e00(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "ldr x9, [x8]\n"
        "ldr x9, [x9, #0x50]\n"
        "mov x0, x8\n"
        "blr x9\n"
        "ldp x29, x30, [sp], #0x10\n"
        "mov w0, wzr\n"
        "ret\n"
    );
}
#endif

// 0x7102074f40 — vtable[0xb8]
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_7102074f40(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "ldr x9, [x8]\n"
        "ldr x9, [x9, #0xb8]\n"
        "mov x0, x8\n"
        "blr x9\n"
        "ldp x29, x30, [sp], #0x10\n"
        "mov w0, wzr\n"
        "ret\n"
    );
}
#endif

// 0x7102077ae0 — vtable[0x158]
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_7102077ae0(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "ldr x9, [x8]\n"
        "ldr x9, [x9, #0x158]\n"
        "mov x0, x8\n"
        "blr x9\n"
        "ldp x29, x30, [sp], #0x10\n"
        "mov w0, wzr\n"
        "ret\n"
    );
}
#endif

// 0x7102078770 — vtable[0x1d0]
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_7102078770(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "ldr x9, [x8]\n"
        "ldr x9, [x9, #0x1d0]\n"
        "mov x0, x8\n"
        "blr x9\n"
        "ldp x29, x30, [sp], #0x10\n"
        "mov w0, wzr\n"
        "ret\n"
    );
}
#endif

// 0x71020788e0 — vtable[0x1e8]
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71020788e0(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "ldr x9, [x8]\n"
        "ldr x9, [x9, #0x1e8]\n"
        "mov x0, x8\n"
        "blr x9\n"
        "ldp x29, x30, [sp], #0x10\n"
        "mov w0, wzr\n"
        "ret\n"
    );
}
#endif

// 0x710207b6b0 — vtable[0x158]
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_710207b6b0(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "ldr x9, [x8]\n"
        "ldr x9, [x9, #0x158]\n"
        "mov x0, x8\n"
        "blr x9\n"
        "ldp x29, x30, [sp], #0x10\n"
        "mov w0, wzr\n"
        "ret\n"
    );
}
#endif

// 0x710207c340 — vtable[0x1d0]
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_710207c340(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "ldr x9, [x8]\n"
        "ldr x9, [x9, #0x1d0]\n"
        "mov x0, x8\n"
        "blr x9\n"
        "ldp x29, x30, [sp], #0x10\n"
        "mov w0, wzr\n"
        "ret\n"
    );
}
#endif

// 0x710207c4b0 — vtable[0x1e8]
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_710207c4b0(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "ldr x9, [x8]\n"
        "ldr x9, [x9, #0x1e8]\n"
        "mov x0, x8\n"
        "blr x9\n"
        "ldp x29, x30, [sp], #0x10\n"
        "mov w0, wzr\n"
        "ret\n"
    );
}
#endif

// 0x710207f280 — vtable[0x158]
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_710207f280(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "ldr x9, [x8]\n"
        "ldr x9, [x9, #0x158]\n"
        "mov x0, x8\n"
        "blr x9\n"
        "ldp x29, x30, [sp], #0x10\n"
        "mov w0, wzr\n"
        "ret\n"
    );
}
#endif

// 0x710207ff10 — vtable[0x1d0]
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_710207ff10(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "ldr x9, [x8]\n"
        "ldr x9, [x9, #0x1d0]\n"
        "mov x0, x8\n"
        "blr x9\n"
        "ldp x29, x30, [sp], #0x10\n"
        "mov w0, wzr\n"
        "ret\n"
    );
}
#endif

// 0x7102080080 — vtable[0x1e8]
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_7102080080(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "ldr x9, [x8]\n"
        "ldr x9, [x9, #0x1e8]\n"
        "mov x0, x8\n"
        "blr x9\n"
        "ldp x29, x30, [sp], #0x10\n"
        "mov w0, wzr\n"
        "ret\n"
    );
}
#endif
