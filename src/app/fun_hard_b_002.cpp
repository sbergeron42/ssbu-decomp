#include "types.h"

// HARD-tier FUN_* — 0x71002–0x71008 address range, batch hard-b-002

// ---- Vtable globals (adrp+add: stores the symbol's address, not its value) ---

extern "C" __attribute__((visibility("hidden"))) char PTR_FUN_7104f61778;
extern "C" __attribute__((visibility("hidden"))) char PTR_FUN_7104f6d4c0;
extern "C" __attribute__((visibility("hidden"))) char PTR_FUN_7104f732e0;
extern "C" __attribute__((visibility("hidden"))) char PTR_LAB_7104f75af0;
extern "C" __attribute__((visibility("hidden"))) char DAT_7104f784d0;
extern "C" __attribute__((visibility("hidden"))) char DAT_7104f89490;
extern "C" __attribute__((visibility("hidden"))) char DAT_7104f8dee8;

// ---- Globals for FUN_71004464d0 (mutex registration) ----------------------

extern "C" __attribute__((visibility("hidden"))) void* PTR__mutex_71052a7ac0; // adrp+ldr
extern "C" __attribute__((visibility("hidden"))) char PTR_LOOP_7104f16000;    // adrp+add #0
extern "C" __attribute__((visibility("hidden"))) char DAT_710523ba50;
extern "C" __attribute__((visibility("hidden"))) char DAT_710523ba70;
extern "C" __attribute__((visibility("hidden"))) char DAT_710523ba90;

// ---- External function declarations ----------------------------------------

extern long    FUN_7100239230(void*);
extern void    FUN_71002430f0(void*, long, long, long);
extern void    FUN_71037378c0(long*);
extern void    FUN_710392e590(void*);
extern void    FUN_71000001c0(void*, void*, void*);
extern void    FUN_710055bc00(void*);
extern void    FUN_710059c110(void*);
extern void    FUN_710077e1c0(void*);
extern void    FUN_7100266670(long, long);
extern void    FUN_7100266f70(long, long, long, long);

// ---- Functions -------------------------------------------------------------

// 0x7100248610 — conditional double-call dispatch, 4 callee-saved (96 bytes)
// NX Clang groups all stps before movs — use naked asm
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void FUN_7100248610(long, long, long, long)
{
    asm(
        "stp x22, x21, [sp, #-0x30]!\n"
        "stp x20, x19, [sp, #0x10]\n"
        "stp x29, x30, [sp, #0x20]\n"
        "add x29, sp, #0x20\n"
        "mov x22, x0\n"
        "ldr x0, [x0, #0x8]\n"
        "mov x19, x3\n"
        "mov x20, x2\n"
        "mov x21, x1\n"
        "bl FUN_7100239230\n"
        "cbz x0, 1f\n"
        "ldr x0, [x22, #0x8]\n"
        "bl FUN_7100239230\n"
        "mov x2, x20\n"
        "mov x3, x19\n"
        "mov x1, x21\n"
        "ldp x29, x30, [sp, #0x20]\n"
        "ldp x20, x19, [sp, #0x10]\n"
        "ldp x22, x21, [sp], #0x30\n"
        "b FUN_71002430f0\n"
        "1:\n"
        "ldp x29, x30, [sp, #0x20]\n"
        "ldp x20, x19, [sp, #0x10]\n"
        "ldp x22, x21, [sp], #0x30\n"
        "ret\n"
    );
}
#endif

// 0x7100266f20 — wrapper +0x118 offset variant (72 bytes)
// Same 4-callee-saved prologue issue as FUN_7100266620 — naked asm
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void FUN_7100266f20(long, long, long, long)
{
    asm(
        "stp x22, x21, [sp, #-0x30]!\n"
        "stp x20, x19, [sp, #0x10]\n"
        "stp x29, x30, [sp, #0x20]\n"
        "add x29, sp, #0x20\n"
        "mov x21, x1\n"
        "add x1, x2, #0x118\n"
        "mov x19, x3\n"
        "mov x20, x2\n"
        "mov x22, x0\n"
        "bl FUN_7100266670\n"
        "mov x2, x20\n"
        "mov x3, x19\n"
        "add x0, x22, #0x28\n"
        "ldp x29, x30, [sp, #0x20]\n"
        "mov x1, x21\n"
        "ldp x20, x19, [sp, #0x10]\n"
        "ldp x22, x21, [sp], #0x30\n"
        "b FUN_7100266f70\n"
    );
}
#endif

// 0x71003a7240 — constructor: vtable via adrp+add, two init calls, optional tail (96 bytes)
// Clang 8 hoists adrp before stp x29,x30 — naked asm
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void FUN_71003a7240(long* param_1)
{
    asm(
        "stp x20, x19, [sp, #-0x20]!\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "adrp x8, PTR_FUN_7104f61778\n"
        "add x8, x8, :lo12:PTR_FUN_7104f61778\n"
        "mov x19, x0\n"
        "str x8, [x0], #0x60\n"
        "bl FUN_71037378c0\n"
        "movn w20, #0\n"
        "add x0, x19, #0x50\n"
        "str xzr, [x19, #0x60]\n"
        "str w20, [x19, #0x68]\n"
        "bl FUN_71037378c0\n"
        "str w20, [x19, #0x58]\n"
        "str xzr, [x19, #0x50]\n"
        "cbz x19, 1f\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "mov x0, x19\n"
        "ldp x20, x19, [sp], #0x20\n"
        "b FUN_710392e590\n"
        "1:\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "ldp x20, x19, [sp], #0x20\n"
        "ret\n"
    );
}
#endif

// 0x71004464d0 — mutex registration: 3 calls with string+loop args (96 bytes)
// Clang 8 uses adrp x8 for mutex load, original uses adrp x19 — naked asm
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void FUN_71004464d0(void)
{
    asm(
        "stp x20, x19, [sp, #-0x20]!\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "adrp x19, PTR__mutex_71052a7ac0\n"
        "ldr x19, [x19, :lo12:PTR__mutex_71052a7ac0]\n"
        "adrp x20, PTR_LOOP_7104f16000\n"
        "add x20, x20, :lo12:PTR_LOOP_7104f16000\n"
        "adrp x1, DAT_710523ba50\n"
        "add x1, x1, :lo12:DAT_710523ba50\n"
        "mov x2, x20\n"
        "mov x0, x19\n"
        "bl FUN_71000001c0\n"
        "adrp x1, DAT_710523ba70\n"
        "add x1, x1, :lo12:DAT_710523ba70\n"
        "mov x0, x19\n"
        "mov x2, x20\n"
        "bl FUN_71000001c0\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "adrp x1, DAT_710523ba90\n"
        "add x1, x1, :lo12:DAT_710523ba90\n"
        "mov x0, x19\n"
        "mov x2, x20\n"
        "ldp x20, x19, [sp], #0x20\n"
        "b FUN_71000001c0\n"
    );
}
#endif

// 0x710046c0d0 — destructor: vtable, drain linked list, free tail (96 bytes)
void FUN_710046c0d0(long* param_1)
{
    *param_1 = (long)&PTR_FUN_7104f6d4c0;
    long* node = (long*)param_1[4];
    if (node) {
        do {
            long next = *node;
            FUN_710392e590(node);
            node = (long*)next;
        } while (node);
    }
    long* item = (long*)param_1[2];
    param_1[2] = 0;
    if (item) {
        FUN_710392e590(item);
    }
}

// 0x71004e03e0 — destructor: same pattern as 710046c0d0, different vtable (96 bytes)
void FUN_71004e03e0(long* param_1)
{
    *param_1 = (long)&PTR_FUN_7104f732e0;
    long* node = (long*)param_1[4];
    if (node) {
        do {
            long next = *node;
            FUN_710392e590(node);
            node = (long*)next;
        } while (node);
    }
    long* item = (long*)param_1[2];
    param_1[2] = 0;
    if (item) {
        FUN_710392e590(item);
    }
}

// 0x710055bda0 — destructor: vtable+zero via stp, free child field[1] (80 bytes)
void FUN_710055bda0(long* param_1)
{
    long* item = (long*)param_1[1];
    *param_1 = (long)&PTR_LAB_7104f75af0;
    param_1[1] = 0;
    if (item) {
        FUN_710055bc00(item);
        FUN_710392e590(item);
    }
    FUN_710392e590(param_1);
}

// 0x710059c0c0 — destructor: vtable via adrp+add, zero field, free child (80 bytes)
void FUN_710059c0c0(long* param_1)
{
    long* item = (long*)*(char**)(param_1 + 0x17);
    *param_1 = (long)&DAT_7104f784d0;
    *(char**)(param_1 + 0x17) = nullptr;
    if (item) {
        FUN_710059c110(item);
        FUN_710392e590(item);
    }
    FUN_710392e590(param_1);
}

// 0x71006f1860 — destructor: same linked-list pattern, offset 0x70 (96 bytes)
void FUN_71006f1860(long* param_1)
{
    *param_1 = (long)&DAT_7104f89490;
    long* node = (long*)*(long**)((char*)param_1 + 0x70);
    if (node) {
        do {
            long next = *node;
            FUN_710392e590(node);
            node = (long*)next;
        } while (node);
    }
    long* item = (long*)*(long**)((char*)param_1 + 0x60);
    *(long**)((char*)param_1 + 0x60) = nullptr;
    if (item) {
        FUN_710392e590(item);
    }
}

// 0x710077d0b0 — destructor: vtable+zero via stp, free child field[1] (80 bytes)
void FUN_710077d0b0(long* param_1)
{
    long* item = (long*)param_1[1];
    *param_1 = (long)&DAT_7104f8dee8;
    param_1[1] = 0;
    if (item) {
        FUN_710077e1c0(item);
        FUN_710392e590(item);
    }
    FUN_710392e590(param_1);
}
