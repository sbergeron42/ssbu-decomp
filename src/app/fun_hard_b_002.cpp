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
extern void    jeFree_710392e590(void*);
extern void    FUN_71000001c0(void*, void*, void*);
extern void    FUN_710055bc00(void*);
extern void    FUN_710059c110(void*);
extern void    FUN_710077e1c0(void*);
extern void    FUN_7100266670(long, long);
extern void    FUN_7100266f70(long, long, long, long);

// ---- Functions -------------------------------------------------------------

// 0x710046c0d0 — destructor: vtable, drain linked list, free tail (96 bytes)
void FUN_710046c0d0(long* param_1)
{
    *param_1 = (long)&PTR_FUN_7104f6d4c0;
    long* node = (long*)param_1[4];
    if (node) {
        do {
            long next = *node;
            jeFree_710392e590(node);
            node = (long*)next;
        } while (node);
    }
    long* item = (long*)param_1[2];
    param_1[2] = 0;
    if (item) {
        jeFree_710392e590(item);
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
            jeFree_710392e590(node);
            node = (long*)next;
        } while (node);
    }
    long* item = (long*)param_1[2];
    param_1[2] = 0;
    if (item) {
        jeFree_710392e590(item);
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
        jeFree_710392e590(item);
    }
    jeFree_710392e590(param_1);
}

// 0x710059c0c0 — destructor: vtable via adrp+add, zero field, free child (80 bytes)
void FUN_710059c0c0(long* param_1)
{
    long* item = (long*)*(char**)(param_1 + 0x17);
    *param_1 = (long)&DAT_7104f784d0;
    *(char**)(param_1 + 0x17) = nullptr;
    if (item) {
        FUN_710059c110(item);
        jeFree_710392e590(item);
    }
    jeFree_710392e590(param_1);
}

// 0x71006f1860 — destructor: same linked-list pattern, offset 0x70 (96 bytes)
void FUN_71006f1860(long* param_1)
{
    *param_1 = (long)&DAT_7104f89490;
    long* node = (long*)*(long**)((char*)param_1 + 0x70);
    if (node) {
        do {
            long next = *node;
            jeFree_710392e590(node);
            node = (long*)next;
        } while (node);
    }
    long* item = (long*)*(long**)((char*)param_1 + 0x60);
    *(long**)((char*)param_1 + 0x60) = nullptr;
    if (item) {
        jeFree_710392e590(item);
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
        jeFree_710392e590(item);
    }
    jeFree_710392e590(param_1);
}

