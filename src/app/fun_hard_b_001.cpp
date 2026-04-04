#include "types.h"

// HARD-tier FUN_* — 0x71001–0x71003 address range, batch hard-b-001
// Pool-b worker: destructor/constructor patterns with vtable globals

// ---- Vtable global declarations -----------------------------------------------

extern "C" __attribute__((visibility("hidden"))) char* PTR_DAT_71052a4860;
extern "C" __attribute__((visibility("hidden"))) char* PTR_DAT_71052a5498;
extern "C" __attribute__((visibility("hidden"))) char* PTR_DAT_71052a5508;
extern "C" __attribute__((visibility("hidden"))) char* PTR_DAT_71052a56e8;
extern "C" __attribute__((visibility("hidden"))) char* PTR_DAT_71052a6780;

// ---- External function declarations -------------------------------------------

extern void FUN_71000b1cf0(long*);
extern void FUN_71000bed20(long*);
extern void FUN_71001308d0(void*);
extern void FUN_7100130920(void*);
extern void FUN_71000b4140(long*);
extern void FUN_71000baa70(long*);
extern void FUN_710015e410(long*);
extern void FUN_71001cfad0(long*);
extern void FUN_710022e920(long*);
extern void FUN_71001d39a0(long*);
extern void FUN_71001af8a0(long*);
extern void FUN_7100266670(long, long);
extern void FUN_7100266770(long, long, long, long);

// ---- Functions ----------------------------------------------------------------

// 0x71001185c0 — constructor: 2 vtable ptrs, zero field[0x14], init 4 sub-objects (96 bytes)
// Clang 8 hoists adrp before stp x29,x30; NX Clang does fp-setup first — use naked asm
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void FUN_71001185c0(long*)
{
    asm(
        "stp x20, x19, [sp, #-0x20]!\n"
        "stp x29, x30, [sp, #0x10]\n"
        "add x29, sp, #0x10\n"
        "adrp x8, PTR_DAT_71052a4860\n"
        "ldr x8, [x8, :lo12:PTR_DAT_71052a4860]\n"
        "str xzr, [x0, #0xa0]\n"
        "add x9, x8, #0x10\n"
        "add x8, x8, #0x40\n"
        "mov x19, x0\n"
        "str x9, [x0]\n"
        "str x8, [x0, #0x18]\n"
        "add x20, x0, #0x20\n"
        "add x0, x0, #0x80\n"
        "bl FUN_71000b1cf0\n"
        "add x0, x19, #0x60\n"
        "bl FUN_71000b1cf0\n"
        "add x0, x19, #0x40\n"
        "bl FUN_71000b1cf0\n"
        "mov x0, x20\n"
        "bl FUN_71000b1cf0\n"
        "ldp x29, x30, [sp, #0x10]\n"
        "mov x0, x19\n"
        "ldp x20, x19, [sp], #0x20\n"
        "b FUN_71000bed20\n"
    );
}
#endif

// 0x7100184600 — destructor: vtable reset, virtual dtor on field[0xb], cleanup (96 bytes)
void FUN_7100184600(long* param_1)
{
    long* puVar1 = (long*)param_1[0xb];
    *param_1 = (long)(PTR_DAT_71052a5498 + 0x10);
    if (puVar1 != (long*)0) {
        (*(void(**)(long*))(*puVar1))(puVar1);
        FUN_71001308d0(puVar1);
        param_1[0xb] = 0;
    }
    param_1[0x16] = 0;
    FUN_71000b4140(param_1 + 0xd);
    FUN_71000baa70(param_1);
}

// 0x7100185b60 — destructor: vtable reset, cleanup 2 optional child objects (96 bytes)
void FUN_7100185b60(long* param_1)
{
    long* puVar1 = (long*)param_1[0xf];
    *param_1 = (long)(PTR_DAT_71052a5508 + 0x10);
    if (puVar1 != (long*)0) {
        FUN_7100130920(puVar1);
        FUN_71001308d0(puVar1);
        param_1[0xf] = 0;
    }
    long* pLVar2 = (long*)param_1[0xe];
    if (pLVar2 != (long*)0) {
        FUN_71001308d0(pLVar2);
        param_1[0xe] = 0;
    }
    param_1[0x10] = 0;
    FUN_71000baa70(param_1);
}

// 0x710019b620 — destructor: vtable reset, virtual dtor on field[0x16] (96 bytes)
void FUN_710019b620(long* param_1)
{
    long* puVar1 = (long*)param_1[0x16];
    *param_1 = (long)(PTR_DAT_71052a56e8 + 0x10);
    if (puVar1 != (long*)0) {
        (*(void(**)(long*))(*puVar1))(puVar1);
        FUN_71001308d0(puVar1);
        param_1[0x16] = 0;
    }
    FUN_710015e410(param_1);
}

// 0x7100235cf0 — constructor: vtable, init sub-obj at +0x188, then +0xc8 (80 bytes)
void FUN_7100235cf0(long* param_1)
{
    char* puVar1 = PTR_DAT_71052a6780;
    *param_1 = (long)(puVar1 + 0x10);
    FUN_71001cfad0((long*)((char*)param_1 + 0x188));
    FUN_710022e920((long*)((char*)param_1 + 0xc8));
    FUN_71001d39a0(param_1);
}

// 0x7100235d40 — constructor: vtable, init sub-objs, extra call before tail (80 bytes)
void FUN_7100235d40(long* param_1)
{
    char* puVar1 = PTR_DAT_71052a6780;
    *param_1 = (long)(puVar1 + 0x10);
    FUN_71001cfad0((long*)((char*)param_1 + 0x188));
    FUN_710022e920((long*)((char*)param_1 + 0xc8));
    FUN_71001d39a0(param_1);
    FUN_71001af8a0(param_1);
}

// 0x7100266620 — wrapper: dispatch two calls with offset args (72 bytes)
// NX Clang groups all stps before any movs; Clang 8 interleaves — use naked asm
#ifdef MATCHING_HACK_NX_CLANG
__attribute__((naked))
void FUN_7100266620(long, long, long, long)
{
    asm(
        "stp x22, x21, [sp, #-0x30]!\n"
        "stp x20, x19, [sp, #0x10]\n"
        "stp x29, x30, [sp, #0x20]\n"
        "add x29, sp, #0x20\n"
        "mov x21, x1\n"
        "add x1, x2, #0x48\n"
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
        "b FUN_7100266770\n"
    );
}
#endif
