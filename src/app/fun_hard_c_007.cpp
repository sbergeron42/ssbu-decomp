#include "types.h"

// HARD-tier FUN_* functions — 0x7102 address range, batch hard-c-007

extern "C" {
    void jeFree_710392e590(void *p);
    void StageBase_dtor_71025d7310(void *p);
    void FUN_71025d7970(void *p);
    void FUN_71025e55a0(void *p);
    void FUN_7102d3eef0(void *p);
    void FUN_7102d33020(void *p);
    void FUN_7102e720d0(void *p);
    void FUN_7102ea8940(void *p);
    void FUN_7102f2c150(void *p);
    void FUN_7102f22f90(void *p);
    void FUN_7103195290(void *p);
    void FUN_7102f316f0(void *p);
    void FUN_7102f31890(void *p);
    void FUN_7102f4d9c0(void *p);
    void FUN_7102f4a3e0(void *p);
}

#define DAT_HIDDEN __attribute__((visibility("hidden")))

extern "C" DAT_HIDDEN u64 DAT_7105133080;
extern "C" DAT_HIDDEN u64 DAT_710513e810;
extern "C" DAT_HIDDEN u64 DAT_710513e8f8;
extern "C" DAT_HIDDEN u64 DAT_7105142440;
extern "C" DAT_HIDDEN u64 DAT_7105144f68;
extern "C" DAT_HIDDEN u64 DAT_710514f588;
extern "C" DAT_HIDDEN u64 DAT_710514fe70;
extern "C" DAT_HIDDEN u64 DAT_7105150d98;
extern "C" DAT_HIDDEN u64 DAT_7105153178;
extern "C" DAT_HIDDEN u64 DAT_7105153a60;

// 0x7102d333a0 — D1 destructor, param_1[0x154] field + sub at param_1+0xe7 + StageBase_dtor_71025d7310
void FUN_7102d333a0(u64 *param_1)
{
    u64 lVar1 = param_1[0x154];
    param_1[0] = (u64)&DAT_7105133080;
    param_1[0x154] = 0;
    if (lVar1 != 0) {
        FUN_7102d3eef0((void *)lVar1);
        jeFree_710392e590((void *)lVar1);
    }
    FUN_7102d33020(param_1 + 0xe7);
    StageBase_dtor_71025d7310(param_1);
}

// 0x7102d333f0 — D0 destructor (same as FUN_7102d333a0 + free self)
void FUN_7102d333f0(u64 *param_1)
{
    u64 lVar1 = param_1[0x154];
    param_1[0] = (u64)&DAT_7105133080;
    param_1[0x154] = 0;
    if (lVar1 != 0) {
        FUN_7102d3eef0((void *)lVar1);
        jeFree_710392e590((void *)lVar1);
    }
    FUN_7102d33020(param_1 + 0xe7);
    StageBase_dtor_71025d7310(param_1);
    jeFree_710392e590(param_1);
}

// 0x7102dfe100 — D0 destructor, group 2 + copy-then-free at inner+8/+0x10
void FUN_7102dfe100(u64 *param_1)
{
    u64 lVar1 = param_1[1];
    param_1[0] = (u64)&DAT_710513e810;
    param_1[1] = 0;
    if (lVar1 != 0) {
        u64 tmp = *(u64 *)(lVar1 + 8);
        if (tmp != 0) {
            *(u64 *)(lVar1 + 0x10) = tmp;
            jeFree_710392e590((void *)tmp);
        }
        jeFree_710392e590((void *)lVar1);
    }
    jeFree_710392e590(param_1);
}

// 0x7102e06ab0 — D0 destructor, group 2 + vtable call at inner+0x90
void FUN_7102e06ab0(u64 *param_1)
{
    u64 lVar2 = param_1[1];
    param_1[0] = (u64)&DAT_710513e8f8;
    param_1[1] = 0;
    if (lVar2 != 0) {
        u64 *plVar1 = (u64 *)*(u64 *)(lVar2 + 0x90);
        *(u64 *)(lVar2 + 0x90) = 0;
        if (plVar1 != nullptr) {
            u64 *vtable = (u64 *)plVar1[0];
            ((void (*)(u64 *))vtable[1])(plVar1);
        }
        jeFree_710392e590((void *)lVar2);
    }
    jeFree_710392e590(param_1);
}

// 0x7102e72080 — D0 destructor, group 2 + FUN_7102e720d0 cleanup
void FUN_7102e72080(u64 *param_1)
{
    u64 lVar1 = param_1[1];
    param_1[0] = (u64)&DAT_7105142440;
    param_1[1] = 0;
    if (lVar1 != 0) {
        FUN_7102e720d0((void *)lVar1);
        jeFree_710392e590((void *)lVar1);
    }
    jeFree_710392e590(param_1);
}

// 0x7102ea6530 — D1 destructor, param_1[0xe7] field + StageBase_dtor_71025d7310
void FUN_7102ea6530(u64 *param_1)
{
    u64 lVar1 = param_1[0xe7];
    param_1[0] = (u64)&DAT_7105144f68;
    param_1[0xe7] = 0;
    if (lVar1 != 0) {
        FUN_7102ea8940((void *)lVar1);
        jeFree_710392e590((void *)lVar1);
    }
    StageBase_dtor_71025d7310(param_1);
}

// 0x7102f23110 — D1 destructor, param_1[0x10d] field + sub at param_1+0xef + FUN_71025e55a0
void FUN_7102f23110(u64 *param_1)
{
    u64 lVar1 = param_1[0x10d];
    param_1[0] = (u64)&DAT_710514f588;
    param_1[0x10d] = 0;
    if (lVar1 != 0) {
        FUN_7102f2c150((void *)lVar1);
        jeFree_710392e590((void *)lVar1);
    }
    FUN_7102f22f90(param_1 + 0xef);
    FUN_71025e55a0(param_1);
}

// 0x7102f23460 — D1 destructor, param_1[0x106] field + sub at param_1+0xe8 + StageBase_dtor_71025d7310
void FUN_7102f23460(u64 *param_1)
{
    u64 lVar1 = param_1[0x106];
    param_1[0] = (u64)&DAT_710514fe70;
    param_1[0x106] = 0;
    if (lVar1 != 0) {
        FUN_7102f2c150((void *)lVar1);
        jeFree_710392e590((void *)lVar1);
    }
    FUN_7102f22f90(param_1 + 0xe8);
    StageBase_dtor_71025d7310(param_1);
}

// 0x7102f31930 — D1 destructor, param_1[0x174] field + two sub-cleanups + StageBase_dtor_71025d7310
void FUN_7102f31930(u64 *param_1)
{
    u64 lVar1 = param_1[0x174];
    param_1[0] = (u64)&DAT_7105150d98;
    param_1[0x174] = 0;
    if (lVar1 != 0) {
        FUN_7103195290((void *)lVar1);
        jeFree_710392e590((void *)lVar1);
    }
    FUN_7102f316f0(param_1 + 0x155);
    FUN_7102f31890(param_1 + 0xe8);
    StageBase_dtor_71025d7310(param_1);
}

// 0x7102f31990 — D0 destructor (same as FUN_7102f31930 + free self)
void FUN_7102f31990(u64 *param_1)
{
    u64 lVar1 = param_1[0x174];
    param_1[0] = (u64)&DAT_7105150d98;
    param_1[0x174] = 0;
    if (lVar1 != 0) {
        FUN_7103195290((void *)lVar1);
        jeFree_710392e590((void *)lVar1);
    }
    FUN_7102f316f0(param_1 + 0x155);
    FUN_7102f31890(param_1 + 0xe8);
    StageBase_dtor_71025d7310(param_1);
    jeFree_710392e590(param_1);
}

// 0x7102f319f0 — field cleanup at param_1+0xba0 + FUN_71025d7970 (interior pointer)
void FUN_7102f319f0(u64 param_1)
{
    u64 lVar1 = *(u64 *)(param_1 + 0xba0);
    *(u64 *)(param_1 + 0xba0) = 0;
    if (lVar1 != 0) {
        FUN_7103195290((void *)lVar1);
        jeFree_710392e590((void *)lVar1);
    }
    FUN_71025d7970((void *)param_1);
}

// 0x7102f4a4f0 — D1 destructor, param_1[0x125] field + sub at param_1+0xef + FUN_71025e55a0
void FUN_7102f4a4f0(u64 *param_1)
{
    u64 lVar1 = param_1[0x125];
    param_1[0] = (u64)&DAT_7105153178;
    param_1[0x125] = 0;
    if (lVar1 != 0) {
        FUN_7102f4d9c0((void *)lVar1);
        jeFree_710392e590((void *)lVar1);
    }
    FUN_7102f4a3e0(param_1 + 0xef);
    FUN_71025e55a0(param_1);
}

// 0x7102f4a800 — D1 destructor, param_1[0x11e] field + sub at param_1+0xe8 + StageBase_dtor_71025d7310
void FUN_7102f4a800(u64 *param_1)
{
    u64 lVar1 = param_1[0x11e];
    param_1[0] = (u64)&DAT_7105153a60;
    param_1[0x11e] = 0;
    if (lVar1 != 0) {
        FUN_7102f4d9c0((void *)lVar1);
        jeFree_710392e590((void *)lVar1);
    }
    FUN_7102f4a3e0(param_1 + 0xe8);
    StageBase_dtor_71025d7310(param_1);
}
