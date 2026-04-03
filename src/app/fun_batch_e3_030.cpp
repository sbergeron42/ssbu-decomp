#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7102 address range, batch e3-030
// Category: framed_vtable_call — direct module pointer dispatch
// Same two sub-patterns as e3-028/029 (plain 9-insn / x10-side-store 10-insn)

// 0x710209b1e0 — plain, vtable[0x150]
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_710209b1e0(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "ldr x9, [x8]\n"
        "ldr x9, [x9, #0x150]\n"
        "mov x0, x8\n"
        "blr x9\n"
        "ldp x29, x30, [sp], #0x10\n"
        "mov w0, wzr\n"
        "ret\n"
    );
}
#endif

// 0x710209f2f0 — str x10, vtable[0x2b0]
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_710209f2f0(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "ldr x9, [x8]\n"
        "ldr x9, [x9, #0x2b0]\n"
        "mov x0, x8\n"
        "blr x9\n"
        "ldp x29, x30, [sp], #0x10\n"
        "mov w0, wzr\n"
        "ret\n"
    );
}
#endif

// 0x710209fee8 — str x10, vtable[0x60]
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_710209fee8(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "ldr x9, [x8]\n"
        "ldr x9, [x9, #0x60]\n"
        "mov x0, x8\n"
        "blr x9\n"
        "ldp x29, x30, [sp], #0x10\n"
        "mov w0, wzr\n"
        "ret\n"
    );
}
#endif

// 0x710209ff90 — plain, vtable[0x88]
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_710209ff90(void) {
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

// 0x71020a04c0 — str x10, vtable[0xc8]
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71020a04c0(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
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

// 0x71020a0800 — str x10, vtable[0xf8]
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71020a0800(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "ldr x9, [x8]\n"
        "ldr x9, [x9, #0xf8]\n"
        "mov x0, x8\n"
        "blr x9\n"
        "ldp x29, x30, [sp], #0x10\n"
        "mov w0, wzr\n"
        "ret\n"
    );
}
#endif

// 0x71020a1ae0 — str x10, vtable[0x180]
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71020a1ae0(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "ldr x9, [x8]\n"
        "ldr x9, [x9, #0x180]\n"
        "mov x0, x8\n"
        "blr x9\n"
        "ldp x29, x30, [sp], #0x10\n"
        "mov w0, wzr\n"
        "ret\n"
    );
}
#endif

// 0x71020a1d20 — str x10, vtable[0x198]
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71020a1d20(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
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

// 0x71020a2e00 — plain, vtable[0x200]
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71020a2e00(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "ldr x9, [x8]\n"
        "ldr x9, [x9, #0x200]\n"
        "mov x0, x8\n"
        "blr x9\n"
        "ldp x29, x30, [sp], #0x10\n"
        "mov w0, wzr\n"
        "ret\n"
    );
}
#endif

// 0x71020a5c40 — plain, vtable[0x2e8]
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71020a5c40(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "ldr x9, [x8]\n"
        "ldr x9, [x9, #0x2e8]\n"
        "mov x0, x8\n"
        "blr x9\n"
        "ldp x29, x30, [sp], #0x10\n"
        "mov w0, wzr\n"
        "ret\n"
    );
}
#endif

// 0x71020a5da0 — str x10, vtable[0x2f0]
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71020a5da0(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "ldr x9, [x8]\n"
        "ldr x9, [x9, #0x2f0]\n"
        "mov x0, x8\n"
        "blr x9\n"
        "ldp x29, x30, [sp], #0x10\n"
        "mov w0, wzr\n"
        "ret\n"
    );
}
#endif

// 0x71020a5f10 — str x10, vtable[0x300]
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71020a5f10(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "ldr x9, [x8]\n"
        "ldr x9, [x9, #0x300]\n"
        "mov x0, x8\n"
        "blr x9\n"
        "ldp x29, x30, [sp], #0x10\n"
        "mov w0, wzr\n"
        "ret\n"
    );
}
#endif

// 0x71020a7008 — str x10, vtable[0x3a8]
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71020a7008(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "ldr x9, [x8]\n"
        "ldr x9, [x9, #0x3a8]\n"
        "mov x0, x8\n"
        "blr x9\n"
        "ldp x29, x30, [sp], #0x10\n"
        "mov w0, wzr\n"
        "ret\n"
    );
}
#endif

// 0x71020a7160 — str x10, vtable[0x3b8]
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71020a7160(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "ldr x9, [x8]\n"
        "ldr x9, [x9, #0x3b8]\n"
        "mov x0, x8\n"
        "blr x9\n"
        "ldp x29, x30, [sp], #0x10\n"
        "mov w0, wzr\n"
        "ret\n"
    );
}
#endif

// 0x71020a79e0 — plain, vtable[0x70]
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71020a79e0(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "ldr x9, [x8]\n"
        "ldr x9, [x9, #0x70]\n"
        "mov x0, x8\n"
        "blr x9\n"
        "ldp x29, x30, [sp], #0x10\n"
        "mov w0, wzr\n"
        "ret\n"
    );
}
#endif

// 0x71020adef0 — str x10, vtable[0x280]
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
u64 FUN_71020adef0(void) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "str x10, [x0, #0x10]\n"
        "ldr x9, [x8]\n"
        "ldr x9, [x9, #0x280]\n"
        "mov x0, x8\n"
        "blr x9\n"
        "ldp x29, x30, [sp], #0x10\n"
        "mov w0, wzr\n"
        "ret\n"
    );
}
#endif
