#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7102 address range, batch e3-029
// Category: framed_vtable_call — direct module pointer dispatch
// Same two sub-patterns as e3-028 (plain 9-insn / x10-side-store 10-insn)
// All: receives module ptr in x8, calls vtable[N] via blr, returns 0

// 0x71020833d0 — str x10, vtable[0xd8]
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71020833d0(void) {
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

// 0x7102083610 — str x10, vtable[0xe8]
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_7102083610(void) {
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

// 0x7102085b70 — plain, vtable[0x1b0]
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_7102085b70(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "ldr x9, [x8]\n"
        "ldr x9, [x9, #0x1b0]\n"
        "mov x0, x8\n"
        "blr x9\n"
        "ldp x29, x30, [sp], #0x10\n"
        "mov w0, wzr\n"
        "ret\n"
    );
}
#endif

// 0x7102085cd0 — str x10, vtable[0x1b8]
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_7102085cd0(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "ldr x9, [x8]\n"
        "ldr x9, [x9, #0x1b8]\n"
        "mov x0, x8\n"
        "blr x9\n"
        "ldp x29, x30, [sp], #0x10\n"
        "mov w0, wzr\n"
        "ret\n"
    );
}
#endif

// 0x71020861a0 — plain, vtable[0x1d8]
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71020861a0(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "ldr x9, [x8]\n"
        "ldr x9, [x9, #0x1d8]\n"
        "mov x0, x8\n"
        "blr x9\n"
        "ldp x29, x30, [sp], #0x10\n"
        "mov w0, wzr\n"
        "ret\n"
    );
}
#endif

// 0x71020864b0 — plain, vtable[0x238]
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71020864b0(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "ldr x9, [x8]\n"
        "ldr x9, [x9, #0x238]\n"
        "mov x0, x8\n"
        "blr x9\n"
        "ldp x29, x30, [sp], #0x10\n"
        "mov w0, wzr\n"
        "ret\n"
    );
}
#endif

// 0x7102086560 — plain, vtable[0x240]
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_7102086560(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "ldr x9, [x8]\n"
        "ldr x9, [x9, #0x240]\n"
        "mov x0, x8\n"
        "blr x9\n"
        "ldp x29, x30, [sp], #0x10\n"
        "mov w0, wzr\n"
        "ret\n"
    );
}
#endif

// 0x7102086fd0 — str x10, vtable[0x2c0]
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_7102086fd0(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "ldr x9, [x8]\n"
        "ldr x9, [x9, #0x2c0]\n"
        "mov x0, x8\n"
        "blr x9\n"
        "ldp x29, x30, [sp], #0x10\n"
        "mov w0, wzr\n"
        "ret\n"
    );
}
#endif

// 0x7102087140 — str x10, vtable[0x2d8]
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_7102087140(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "ldr x9, [x8]\n"
        "ldr x9, [x9, #0x2d8]\n"
        "mov x0, x8\n"
        "blr x9\n"
        "ldp x29, x30, [sp], #0x10\n"
        "mov w0, wzr\n"
        "ret\n"
    );
}
#endif

// 0x7102088b40 — str x10, vtable[0x188]
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_7102088b40(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
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

// 0x7102089340 — plain, vtable[0x48]
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_7102089340(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "ldr x9, [x8]\n"
        "ldr x9, [x9, #0x48]\n"
        "mov x0, x8\n"
        "blr x9\n"
        "ldp x29, x30, [sp], #0x10\n"
        "mov w0, wzr\n"
        "ret\n"
    );
}
#endif

// 0x71020899f0 — plain, vtable[0x78]
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71020899f0(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "ldr x9, [x8]\n"
        "ldr x9, [x9, #0x78]\n"
        "mov x0, x8\n"
        "blr x9\n"
        "ldp x29, x30, [sp], #0x10\n"
        "mov w0, wzr\n"
        "ret\n"
    );
}
#endif

// 0x7102089c08 — str x10, vtable[0x80]
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_7102089c08(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "ldr x9, [x8]\n"
        "ldr x9, [x9, #0x80]\n"
        "mov x0, x8\n"
        "blr x9\n"
        "ldp x29, x30, [sp], #0x10\n"
        "mov w0, wzr\n"
        "ret\n"
    );
}
#endif

// 0x710208a5f0 — str x10, vtable[0xe0]
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_710208a5f0(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "ldr x9, [x8]\n"
        "ldr x9, [x9, #0xe0]\n"
        "mov x0, x8\n"
        "blr x9\n"
        "ldp x29, x30, [sp], #0x10\n"
        "mov w0, wzr\n"
        "ret\n"
    );
}
#endif

// 0x710208a6b0 — plain, vtable[0xe8]
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_710208a6b0(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
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

// 0x710208bb90 — plain, vtable[0x58]
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_710208bb90(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "ldr x9, [x8]\n"
        "ldr x9, [x9, #0x58]\n"
        "mov x0, x8\n"
        "blr x9\n"
        "ldp x29, x30, [sp], #0x10\n"
        "mov w0, wzr\n"
        "ret\n"
    );
}
#endif

// 0x710208bef0 — str x10, vtable[0x90]
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_710208bef0(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "ldr x9, [x8]\n"
        "ldr x9, [x9, #0x90]\n"
        "mov x0, x8\n"
        "blr x9\n"
        "ldp x29, x30, [sp], #0x10\n"
        "mov w0, wzr\n"
        "ret\n"
    );
}
#endif

// 0x710208bfb0 — plain, vtable[0x98]
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_710208bfb0(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "ldr x9, [x8]\n"
        "ldr x9, [x9, #0x98]\n"
        "mov x0, x8\n"
        "blr x9\n"
        "ldp x29, x30, [sp], #0x10\n"
        "mov w0, wzr\n"
        "ret\n"
    );
}
#endif

// 0x710208c980 — plain, vtable[0x80]
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_710208c980(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "ldr x9, [x8]\n"
        "ldr x9, [x9, #0x80]\n"
        "mov x0, x8\n"
        "blr x9\n"
        "ldp x29, x30, [sp], #0x10\n"
        "mov w0, wzr\n"
        "ret\n"
    );
}
#endif

// 0x710208ca30 — plain, vtable[0x88]
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_710208ca30(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "ldr x9, [x8]\n"
        "ldr x9, [x9, #0x88]\n"
        "mov x0, x8\n"
        "blr x9\n"
        "ldp x29, x30, [sp], #0x10\n"
        "mov w0, wzr\n"
        "ret\n"
    );
}
#endif

// 0x710208d900 — str x10, vtable[0x118]
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_710208d900(void) {
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

// 0x7102090ff0 — plain, vtable[0x198]
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_7102090ff0(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "ldr x9, [x8]\n"
        "ldr x9, [x9, #0x198]\n"
        "mov x0, x8\n"
        "blr x9\n"
        "ldp x29, x30, [sp], #0x10\n"
        "mov w0, wzr\n"
        "ret\n"
    );
}
#endif

// 0x71020916b0 — plain, vtable[0x1c8]
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71020916b0(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "ldr x9, [x8]\n"
        "ldr x9, [x9, #0x1c8]\n"
        "mov x0, x8\n"
        "blr x9\n"
        "ldp x29, x30, [sp], #0x10\n"
        "mov w0, wzr\n"
        "ret\n"
    );
}
#endif

// 0x7102091c20 — plain, vtable[0x218]
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_7102091c20(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "ldr x9, [x8]\n"
        "ldr x9, [x9, #0x218]\n"
        "mov x0, x8\n"
        "blr x9\n"
        "ldp x29, x30, [sp], #0x10\n"
        "mov w0, wzr\n"
        "ret\n"
    );
}
#endif

// 0x71020929d0 — plain, vtable[0x50]
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71020929d0(void) {
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

// 0x7102092a80 — plain, vtable[0x68]
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_7102092a80(void) {
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

// 0x7102099f00 — plain, vtable[0xb8]
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_7102099f00(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
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
