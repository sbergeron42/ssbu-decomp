#include "types.h"

// HARD-tier FUN_* functions — 0x7103 address range, batch hard-c-012

extern "C" {
    void jeFree_710392e590(void *p);
    void FUN_7101378af0(u64 a, u64 b, u64 *c);
    void FUN_7103170560(u64 a);
    void FUN_710320edb0(void *p);
    void FUN_7103378a60(void *p);
    void FUN_7103378d10(void *p);
    void FUN_71036e65d0(void *p);
}

#define DAT_HIDDEN __attribute__((visibility("hidden")))

extern "C" DAT_HIDDEN u64 DAT_710517c2c0;
extern "C" DAT_HIDDEN u64 DAT_710517f868;
extern "C" DAT_HIDDEN u64 DAT_7105184ec8;
extern "C" DAT_HIDDEN u64 DAT_710523a880;
extern "C" DAT_HIDDEN u64 DAT_71052b84f8;   // lib::Singleton<app::FighterManager>::instance_

// 0x7103170500 — recursive tree delete, dereference cleanup: FUN_7103170560(*(param_1[5]+8))
void FUN_7103170500(u64 *param_1)
{
    if (param_1) {
        FUN_7103170500((u64 *)param_1[0]);
        FUN_7103170500((u64 *)param_1[1]);
        u64 lVar1 = param_1[5];
        param_1[5] = 0;
        if (lVar1 != 0) {
            FUN_7103170560(*(u64 *)(lVar1 + 8));
            jeFree_710392e590((void *)lVar1);
        }
        jeFree_710392e590(param_1);
    }
}

// 0x710317fad0 — init: set vtable + register with FighterManager
void FUN_710317fad0(u64 *param_1)
{
#ifdef MATCHING_HACK_NX_CLANG
    asm volatile("" :: "r"(__builtin_frame_address(0)) : "memory");
#endif
    param_1[0] = (u64)&DAT_710517c2c0;
    if (DAT_71052b84f8 != 0) {
        FUN_7101378af0(*(u64 *)DAT_71052b84f8, 3, param_1 + 1);
        FUN_7101378af0(*(u64 *)DAT_71052b84f8, 4, param_1 + 2);
    }
}

// 0x710320ed50 — D0 destructor, param_1[2] cleanup + vtable call on param_1[1]
void FUN_710320ed50(u64 *param_1)
{
    u64 lVar2 = param_1[2];
    param_1[0] = (u64)&DAT_710517f868;
    param_1[2] = 0;
    if (lVar2 != 0) {
        FUN_710320edb0((void *)lVar2);
        jeFree_710392e590((void *)lVar2);
    }
    u64 *plVar1 = (u64 *)param_1[1];
    param_1[1] = 0;
    if (plVar1 != nullptr) {
        u64 *vtable = (u64 *)plVar1[0];
        ((void (*)(u64 *))vtable[1])(plVar1);
    }
    jeFree_710392e590(param_1);
}

// 0x7103378c60 — D1 destructor, pre-call FUN_7103378d10, param_1[1] field (no free self)
void FUN_7103378c60(u64 *param_1)
{
    param_1[0] = (u64)&DAT_7105184ec8;
    FUN_7103378d10((void *)param_1[1]);
    u64 lVar1 = param_1[1];
    param_1[1] = 0;
    if (lVar1 != 0) {
        FUN_7103378a60((void *)lVar1);
        jeFree_710392e590((void *)lVar1);
    }
}

// 0x7103378cc0 — D0 destructor (same as FUN_7103378c60 + free self)
void FUN_7103378cc0(u64 *param_1)
{
    param_1[0] = (u64)&DAT_7105184ec8;
    FUN_7103378d10((void *)param_1[1]);
    u64 lVar1 = param_1[1];
    param_1[1] = 0;
    if (lVar1 != 0) {
        FUN_7103378a60((void *)lVar1);
        jeFree_710392e590((void *)lVar1);
    }
    jeFree_710392e590(param_1);
}

// 0x710356c8d0 — recursive tree delete
void FUN_710356c8d0(u64 *param_1)
{
    if (param_1) {
        FUN_710356c8d0((u64 *)param_1[0]);
        FUN_710356c8d0((u64 *)param_1[1]);
        jeFree_710392e590(param_1);
    }
}

// 0x71035fe560 — recursive tree delete
void FUN_71035fe560(u64 *param_1)
{
    if (param_1) {
        FUN_71035fe560((u64 *)param_1[0]);
        FUN_71035fe560((u64 *)param_1[1]);
        jeFree_710392e590(param_1);
    }
}

// 0x71036659b0 — recursive tree delete
void FUN_71036659b0(u64 *param_1)
{
    if (param_1) {
        FUN_71036659b0((u64 *)param_1[0]);
        FUN_71036659b0((u64 *)param_1[1]);
        jeFree_710392e590(param_1);
    }
}

// 0x71036e6580 — D0 destructor, param_1[1] field + FUN_71036e65d0
void FUN_71036e6580(u64 *param_1)
{
    u64 lVar1 = param_1[1];
    param_1[0] = (u64)&DAT_710523a880;
    param_1[1] = 0;
    if (lVar1 != 0) {
        FUN_71036e65d0((void *)lVar1);
        jeFree_710392e590((void *)lVar1);
    }
    jeFree_710392e590(param_1);
}

// 0x7103724670 — recursive tree delete
void FUN_7103724670(u64 *param_1)
{
    if (param_1) {
        FUN_7103724670((u64 *)param_1[0]);
        FUN_7103724670((u64 *)param_1[1]);
        jeFree_710392e590(param_1);
    }
}

// 0x710376b020 — recursive tree delete
void FUN_710376b020(u64 *param_1)
{
    if (param_1) {
        FUN_710376b020((u64 *)param_1[0]);
        FUN_710376b020((u64 *)param_1[1]);
        jeFree_710392e590(param_1);
    }
}

// 0x710376b370 — recursive tree delete
void FUN_710376b370(u64 *param_1)
{
    if (param_1) {
        FUN_710376b370((u64 *)param_1[0]);
        FUN_710376b370((u64 *)param_1[1]);
        jeFree_710392e590(param_1);
    }
}

// 0x7103783f60 — recursive tree delete
void FUN_7103783f60(u64 *param_1)
{
    if (param_1) {
        FUN_7103783f60((u64 *)param_1[0]);
        FUN_7103783f60((u64 *)param_1[1]);
        jeFree_710392e590(param_1);
    }
}

// 0x7103795c50 — recursive tree delete
void FUN_7103795c50(u64 *param_1)
{
    if (param_1) {
        FUN_7103795c50((u64 *)param_1[0]);
        FUN_7103795c50((u64 *)param_1[1]);
        jeFree_710392e590(param_1);
    }
}
