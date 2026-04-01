#include "types.h"

// Particle/emitter functions — pool-c assignment

extern "C" void FUN_7100088060(void*);
extern "C" void FUN_71000a4f60(void*,void*,void*,void*,void*,u64,u64,u32);
extern "C" bool FUN_71000ac200(void*,void*,u32,void*,void*);
extern "C" void FUN_710395a570(s32*);

// 71000a4f20 (16B) — copy emitter handle field from src to dst
// Leaf function; matches directly.
void InitializeEmitter(u8* p0, u8* p1) {
    *reinterpret_cast<u64*>(p1 + 0x98) = *reinterpret_cast<u64*>(p0 + 0x8c0);
}

// 71000a4f30 (48B) — call finalizer helper, then increment ref count at +0x80
// Non-leaf; NX Clang schedules stp/add-x29 before mov x19,x0 (prologue scheduling divergence)
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void FinalizeEmitter(u8* /*p0*/, void* /*p1*/) {
    asm(
        "str x19, [sp, #-0x20]!\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "mov x19, x0\n"
        "mov x0, x1\n"
        "bl FUN_7100088060\n"
        "ldr w8, [x19, #0x80]\n"
        "add w8, w8, #1\n"
        "str w8, [x19, #0x80]\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "ldr x19, [sp], #0x20\n"
        "ret\n"
    );
}
#endif

// 71000a51a0 (32B) — swap args 6/7, zero new arg 6, mask bool arg 7, tail-call inner
// arg reorder: x5→x6, x6→w7(masked &1), x5=0
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void CreateEmitterSetId(void*,void*,void*,void*,void*,u64,u32) {
    asm(
        "mov x8, x5\n"
        "and w7, w6, #0x1\n"
        "mov w5, wzr\n"
        "mov x6, x8\n"
        "b FUN_71000a4f60\n"
    );
}
#endif

// 71000ac1c0 (64B) — unpack emitter callback struct fields, call inner, return 1
// Non-leaf; NX Clang places mov x29,sp early (after stp), upstream places it late.
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
bool EmitterDrawCallback(u64* /*p*/) {
    asm(
        "stp x29, x30, [sp, #-0x10]!\n"
        "mov x29, sp\n"
        "ldp x8, x1, [x0]\n"
        "ldr w2, [x0, #0x10]\n"
        "ldp x3, x4, [x0, #0x18]\n"
        "mov x0, x8\n"
        "bl FUN_71000ac200\n"
        "mov w0, #0x1\n"
        "ldp x29, x30, [sp], #0x10\n"
        "ret\n"
    );
}
#endif

// 710395a3e0 (64B) — if *p == 0, call object-end helper
// Compiler stores/reloads param from stack slot before conditional; cannot match without asm.
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void emitter_json_object_end(s32* /*p*/) {
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "ldr x8, [sp, #0x8]\n"
        "ldr w8, [x8]\n"
        "cbnz w8, 0f\n"
        "b 1f\n"
        "1:\n"
        "ldr x0, [sp, #0x8]\n"
        "bl FUN_710395a570\n"
        "b 0f\n"
        "0:\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}
#endif
