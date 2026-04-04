#include "types.h"

// HARD-tier functions — 0x710392xxxx-0x710393xxxx range
// Pool-d worker: decompiled from Ghidra + assembly analysis

// ---- External declarations -----------------------------------------------

extern "C" {
u64  FUN_71039281f0(u64);
void FUN_710395ae10(u64, u64);
u64  FUN_7103928d50(u64);
u64  FUN_7103929160(u64);
void FUN_7103929100(u64);
void FUN_7103929210(u64);
void FUN_7103929740(u64);
void FUN_7103929810(u64);
void FUN_710392c160(u64);
u32* FUN_710392c660(u64);
u64  FUN_7103928860(u64);
u32  FUN_7103928df0(u64);
void FUN_710392c730(u64, u32, u32);
u8*  FUN_710392c560(u64);
u64  FUN_710392c480(u64);
void FUN_710392c4e0(u64, u64);
void FUN_710392b3f0(u64);
void FUN_71039575b0(void);
void FUN_710392da50(void);
u64  FUN_71039302c0(u64);
u64  FUN_71039302e0(u64);
u64  FUN_7103930300(u64);
void FUN_71039309b0(u64, u64);
void FUN_7103930bb0(u32);

__attribute__((visibility("hidden"))) u32 DAT_71052934c0;
}

// ---- Matching C functions (wrappers) -----------------------------------------

// 0x71039290d0 — wrapper (48 bytes)
extern "C" __attribute__((optnone))
void FUN_71039290d0(u64 param_1)
{
    goto a; a:; do {} while(0);
    FUN_7103929100(param_1);
}

// 0x71039291e0 — wrapper (48 bytes)
extern "C" __attribute__((optnone))
void FUN_71039291e0(u64 param_1)
{
    goto a; a:; do {} while(0);
    FUN_7103929210(param_1);
}

// 0x7103929710 — wrapper (48 bytes)
extern "C" __attribute__((optnone))
void FUN_7103929710(u64 param_1)
{
    goto a; a:; do {} while(0);
    FUN_7103929740(param_1);
}

// 0x71039297e0 — wrapper (48 bytes)
extern "C" __attribute__((optnone))
void FUN_71039297e0(u64 param_1)
{
    goto a; a:; do {} while(0);
    FUN_7103929810(param_1);
}

// 0x710392c130 — wrapper (48 bytes)
extern "C" __attribute__((optnone))
void FUN_710392c130(u64 param_1)
{
    goto a; a:; do {} while(0);
    FUN_710392c160(param_1);
}

// 0x710392c630 — wrapper returning pointer (48 bytes)
extern "C" __attribute__((optnone))
u32* FUN_710392c630(u64 param_1)
{
    goto a; a:; do {} while(0);
    return FUN_710392c660(param_1);
}

// 0x7103930b80 — wrapper u32 (48 bytes)
extern "C" __attribute__((optnone))
void FUN_7103930b80(u32 param_1)
{
    goto a; a:; do {} while(0);
    FUN_7103930bb0(param_1);
}

// ---- Naked asm functions (NX Clang codegen divergence) -----------------------

#ifdef MATCHING_HACK_NX_CLANG

// 0x71039281a0 — conditional call based on bool check (80 bytes)
extern "C" __attribute__((naked))
void FUN_71039281a0(u64 param_1, u64 param_2)
{
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "str x1, [sp]\n"
        "ldr x8, [sp]\n"
        "add x0, x8, #0x8\n"
        "bl FUN_71039281f0\n"
        "tbz w0, #0, 0f\n"
        "b 1f\n"
        "1:\n"
        "ldr x0, [sp, #0x8]\n"
        "ldr x1, [sp]\n"
        "bl FUN_710395ae10\n"
        "b 0f\n"
        "0:\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// 0x7103928da0 — conditional return value (80 bytes)
extern "C" __attribute__((naked))
u64 FUN_7103928da0(u64 param_1)
{
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp]\n"
        "ldr x0, [sp]\n"
        "bl FUN_7103928d50\n"
        "tbnz w0, #0, 1f\n"
        "b 2f\n"
        "2:\n"
        "str xzr, [sp, #0x8]\n"
        "b 0f\n"
        "1:\n"
        "ldr x0, [sp]\n"
        "bl FUN_7103929160\n"
        "str x0, [sp, #0x8]\n"
        "b 0f\n"
        "0:\n"
        "ldr x0, [sp, #0x8]\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// 0x710392c520 — get pointer from c630, store param_2 (64 bytes)
extern "C" __attribute__((naked))
void FUN_710392c520(u64 param_1, u32 param_2)
{
    asm(
        "sub sp, sp, #0x30\n"
        "str x19, [sp, #0x10]\n"
        "stp x29, x30, [sp, #0x20]\n"
        "add x29, sp, #0x20\n"
        "stur x0, [x29, #-0x8]\n"
        "str w1, [sp, #0xc]\n"
        "b 1f\n"
        "1:\n"
        "b 2f\n"
        "2:\n"
        "ldr w19, [sp, #0xc]\n"
        "ldur x0, [x29, #-0x8]\n"
        "bl FUN_710392c630\n"
        "str w19, [x0]\n"
        "ldp x29, x30, [sp, #0x20]\n"
        "ldr x19, [sp, #0x10]\n"
        "add sp, sp, #0x30\n"
        "ret\n"
    );
}

// 0x710392c6d0 — conditional: get handle, get value, forward (96 bytes)
extern "C" __attribute__((naked))
void FUN_710392c6d0(u64 param_1)
{
    asm(
        "sub sp, sp, #0x30\n"
        "str x19, [sp, #0x10]\n"
        "stp x29, x30, [sp, #0x20]\n"
        "add x29, sp, #0x20\n"
        "stur x0, [x29, #-0x8]\n"
        "ldur x0, [x29, #-0x8]\n"
        "bl FUN_7103928860\n"
        "str x0, [sp, #0x8]\n"
        "ldr x8, [sp, #0x8]\n"
        "cbz x8, 0f\n"
        "b 1f\n"
        "1:\n"
        "ldur x19, [x29, #-0x8]\n"
        "ldr x0, [sp, #0x8]\n"
        "bl FUN_7103928df0\n"
        "mov w1, w0\n"
        "mov x0, x19\n"
        "mov w2, #0x1\n"
        "bl FUN_710392c730\n"
        "b 0f\n"
        "0:\n"
        "ldp x29, x30, [sp, #0x20]\n"
        "ldr x19, [sp, #0x10]\n"
        "add sp, sp, #0x30\n"
        "ret\n"
    );
}

// 0x710392c810 — set byte flag, conditional cleanup (96 bytes)
extern "C" __attribute__((naked))
void FUN_710392c810(u64 param_1)
{
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "ldr x0, [sp, #0x8]\n"
        "bl FUN_710392c560\n"
        "mov w8, #0x1\n"
        "strb w8, [x0]\n"
        "ldr x0, [sp, #0x8]\n"
        "bl FUN_710392c480\n"
        "str x0, [sp]\n"
        "ldr x8, [sp]\n"
        "cbz x8, 0f\n"
        "b 1f\n"
        "1:\n"
        "ldr x0, [sp, #0x8]\n"
        "mov x1, xzr\n"
        "bl FUN_710392c4e0\n"
        "ldr x0, [sp]\n"
        "bl FUN_710392b3f0\n"
        "b 0f\n"
        "0:\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// 0x710392d930 — init: call setup, clear global, call cleanup, return 0 (64 bytes)
extern "C" __attribute__((naked))
u8 FUN_710392d930(void)
{
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "bl FUN_71039575b0\n"
        "b 1f\n"
        "1:\n"
        "adrp x8, DAT_71052934c0\n"
        "str wzr, [x8, :lo12:DAT_71052934c0]\n"
        "bl FUN_710392da50\n"
        "sturb wzr, [x29, #-0x1]\n"
        "b 2f\n"
        "2:\n"
        "ldurb w0, [x29, #-0x1]\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

// 0x710392eec0 — conditional: if flag set return 0, else chain two calls (96 bytes)
extern "C" __attribute__((naked))
u64 FUN_710392eec0(u64 param_1)
{
    asm(
        "sub sp, sp, #0x30\n"
        "stp x29, x30, [sp, #0x20]\n"
        "add x29, sp, #0x20\n"
        "str x0, [sp, #0x10]\n"
        "ldr x0, [sp, #0x10]\n"
        "bl FUN_71039302c0\n"
        "tbz w0, #0, 1f\n"
        "b 2f\n"
        "2:\n"
        "stur xzr, [x29, #-0x8]\n"
        "b 0f\n"
        "1:\n"
        "ldr x0, [sp, #0x10]\n"
        "bl FUN_71039302e0\n"
        "str x0, [sp, #0x8]\n"
        "ldr x0, [sp, #0x8]\n"
        "bl FUN_7103930300\n"
        "stur x0, [x29, #-0x8]\n"
        "b 0f\n"
        "0:\n"
        "ldur x0, [x29, #-0x8]\n"
        "ldp x29, x30, [sp, #0x20]\n"
        "add sp, sp, #0x30\n"
        "ret\n"
    );
}

// 0x7103930970 — offset delegate: call at param_1+0x1a30 (64 bytes)
extern "C" __attribute__((naked))
void FUN_7103930970(u64 param_1, u64 param_2)
{
    asm(
        "sub sp, sp, #0x20\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "str x0, [sp, #0x8]\n"
        "str x1, [sp]\n"
        "b 1f\n"
        "1:\n"
        "b 2f\n"
        "2:\n"
        "ldr x8, [sp, #0x8]\n"
        "mov w9, #0x1a30\n"
        "add x0, x8, x9\n"
        "ldr x1, [sp]\n"
        "bl FUN_71039309b0\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "add sp, sp, #0x20\n"
        "ret\n"
    );
}

#endif // MATCHING_HACK_NX_CLANG
