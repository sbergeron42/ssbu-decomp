#include "types.h"

// HARD-tier FUN_* functions — 0x7102 address range, batch hard-c-005

extern "C" {
    void jeFree_710392e590(void *p);
    void StageBase_dtor_71025d7310(void *p);
    void FUN_71025e55a0(void *p);
    void FUN_71028ac930(void *p);
    void FUN_7102988e70(void *p);
    void FUN_7102a2a430(void *p);
    void FUN_7102a2c950(void *p);
    void FUN_7102a2d640(void *p);
    void FUN_7102a31c20(void *p);
    void FUN_7102a36520(void *p);
    void FUN_7102b15af0(void *p);
    void FUN_7102b39540(void *p);
}

#define DAT_HIDDEN __attribute__((visibility("hidden")))

extern "C" DAT_HIDDEN u64 DAT_71050efb70;
extern "C" DAT_HIDDEN u64 DAT_71050f87a8;
extern "C" DAT_HIDDEN u64 DAT_7105102240;
extern "C" DAT_HIDDEN u64 DAT_7105102b48;
extern "C" DAT_HIDDEN u64 DAT_7105103410;
extern "C" DAT_HIDDEN u64 DAT_71051035e0;
extern "C" DAT_HIDDEN u64 DAT_7105103660;
extern "C" DAT_HIDDEN u64 DAT_71051036f0;
extern "C" DAT_HIDDEN u64 DAT_7105111048;
extern "C" DAT_HIDDEN u64 DAT_7105113840;

// 0x71028abeb0 — D1 destructor, param_1[0xe7] field + StageBase_dtor_71025d7310
void FUN_71028abeb0(u64 *param_1)
{
    u64 lVar1 = param_1[0xe7];
    param_1[0] = (u64)&DAT_71050efb70;
    param_1[0xe7] = 0;
    if (lVar1 != 0) {
        FUN_71028ac930((void *)lVar1);
        jeFree_710392e590((void *)lVar1);
    }
    StageBase_dtor_71025d7310(param_1);
}

// 0x71028abf00 — D0 destructor (same as FUN_71028abeb0 + free self)
void FUN_71028abf00(u64 *param_1)
{
    u64 lVar1 = param_1[0xe7];
    param_1[0] = (u64)&DAT_71050efb70;
    param_1[0xe7] = 0;
    if (lVar1 != 0) {
        FUN_71028ac930((void *)lVar1);
        jeFree_710392e590((void *)lVar1);
    }
    StageBase_dtor_71025d7310(param_1);
    jeFree_710392e590(param_1);
}

// 0x7102987840 — D1 destructor, param_1[0xe7] field + StageBase_dtor_71025d7310
void FUN_7102987840(u64 *param_1)
{
    u64 lVar1 = param_1[0xe7];
    param_1[0] = (u64)&DAT_71050f87a8;
    param_1[0xe7] = 0;
    if (lVar1 != 0) {
        FUN_7102988e70((void *)lVar1);
        jeFree_710392e590((void *)lVar1);
    }
    StageBase_dtor_71025d7310(param_1);
}

// 0x7102a287e0 — D1 destructor, param_1[0xee] field + FUN_71025e55a0
void FUN_7102a287e0(u64 *param_1)
{
    u64 lVar1 = param_1[0xee];
    param_1[0] = (u64)&DAT_7105102240;
    param_1[0xee] = 0;
    if (lVar1 != 0) {
        FUN_7102a2a430((void *)lVar1);
        jeFree_710392e590((void *)lVar1);
    }
    FUN_71025e55a0(param_1);
}

// 0x7102a2a3e0 — recursive tree delete with conditional free at param_1[7] (flag in param_1[5] byte)
void FUN_7102a2a3e0(u64 *param_1)
{
    if (param_1) {
        FUN_7102a2a3e0((u64 *)param_1[0]);
        FUN_7102a2a3e0((u64 *)param_1[1]);
        if ((*(u8 *)(param_1 + 5) & 1) && param_1[7] != 0)
            jeFree_710392e590((void *)param_1[7]);
        jeFree_710392e590(param_1);
    }
}

// 0x7102a2b2a0 — D1 destructor, param_1[0xe7] field + StageBase_dtor_71025d7310
void FUN_7102a2b2a0(u64 *param_1)
{
    u64 lVar1 = param_1[0xe7];
    param_1[0] = (u64)&DAT_7105102b48;
    param_1[0xe7] = 0;
    if (lVar1 != 0) {
        FUN_7102a2c950((void *)lVar1);
        jeFree_710392e590((void *)lVar1);
    }
    StageBase_dtor_71025d7310(param_1);
}

// 0x7102a2d190 — recursive tree delete with vtable call on param_1[5]
void FUN_7102a2d190(u64 *param_1)
{
    if (param_1) {
        FUN_7102a2d190((u64 *)param_1[0]);
        FUN_7102a2d190((u64 *)param_1[1]);
        u64 *plVar1 = (u64 *)param_1[5];
        param_1[5] = 0;
        if (plVar1 != nullptr) {
            u64 *vtable = (u64 *)plVar1[0];
            ((void (*)(u64 *))vtable[1])(plVar1);
        }
        jeFree_710392e590(param_1);
    }
}

// 0x7102a2d5e0 — D0 destructor, group 2 + sub-call + vtable call on inner[0]
void FUN_7102a2d5e0(u64 *param_1)
{
    u64 *plVar2 = (u64 *)param_1[1];
    param_1[0] = (u64)&DAT_7105103410;
    param_1[1] = 0;
    if (plVar2 != nullptr) {
        FUN_7102a2d640((void *)plVar2[2]);
        u64 *plVar1 = (u64 *)plVar2[0];
        plVar2[0] = 0;
        if (plVar1 != nullptr) {
            u64 *vtable = (u64 *)plVar1[0];
            ((void (*)(u64 *))vtable[1])(plVar1);
        }
        jeFree_710392e590(plVar2);
    }
    jeFree_710392e590(param_1);
}

// 0x7102a31bd0 — D0 destructor, group 2 + FUN_7102a31c20 cleanup
void FUN_7102a31bd0(u64 *param_1)
{
    u64 lVar1 = param_1[1];
    param_1[0] = (u64)&DAT_71051035e0;
    param_1[1] = 0;
    if (lVar1 != 0) {
        FUN_7102a31c20((void *)lVar1);
        jeFree_710392e590((void *)lVar1);
    }
    jeFree_710392e590(param_1);
}

// 0x7102a35500 — recursive tree delete with inner pointer free at param_1[5]
void FUN_7102a35500(u64 *param_1)
{
    if (param_1) {
        FUN_7102a35500((u64 *)param_1[0]);
        FUN_7102a35500((u64 *)param_1[1]);
        u64 *plVar2 = (u64 *)param_1[5];
        param_1[5] = 0;
        if (plVar2 != nullptr) {
            u64 lVar1 = plVar2[0];
            plVar2[0] = 0;
            if (lVar1 != 0)
                jeFree_710392e590((void *)lVar1);
            jeFree_710392e590(plVar2);
        }
        jeFree_710392e590(param_1);
    }
}

// 0x7102a358e0 — recursive tree delete with two conditional frees (flags in param_1[8]/param_1[5])
void FUN_7102a358e0(u64 *param_1)
{
    if (param_1) {
        FUN_7102a358e0((u64 *)param_1[0]);
        FUN_7102a358e0((u64 *)param_1[1]);
        if ((*(u8 *)(param_1 + 8) & 1) && param_1[10] != 0)
            jeFree_710392e590((void *)param_1[10]);
        if ((*(u8 *)(param_1 + 5) & 1) && param_1[7] != 0)
            jeFree_710392e590((void *)param_1[7]);
        jeFree_710392e590(param_1);
    }
}

// 0x7102a36300 — D0 destructor, group 2 + FUN_7102a36520 cleanup
void FUN_7102a36300(u64 *param_1)
{
    u64 lVar1 = param_1[1];
    param_1[0] = (u64)&DAT_7105103660;
    param_1[1] = 0;
    if (lVar1 != 0) {
        FUN_7102a36520((void *)lVar1);
        jeFree_710392e590((void *)lVar1);
    }
    jeFree_710392e590(param_1);
}

// 0x7102a3a120 — D0 destructor, group 2 + vtable call at inner+0x10
void FUN_7102a3a120(u64 *param_1)
{
    u64 lVar2 = param_1[1];
    param_1[0] = (u64)&DAT_71051036f0;
    param_1[1] = 0;
    if (lVar2 != 0) {
        u64 *plVar1 = (u64 *)*(u64 *)(lVar2 + 0x10);
        *(u64 *)(lVar2 + 0x10) = 0;
        if (plVar1 != nullptr) {
            u64 *vtable = (u64 *)plVar1[0];
            ((void (*)(u64 *))vtable[1])(plVar1);
        }
        jeFree_710392e590((void *)lVar2);
    }
    jeFree_710392e590(param_1);
}

// 0x7102b14280 — D1 destructor, param_1[0xe7] field + StageBase_dtor_71025d7310
void FUN_7102b14280(u64 *param_1)
{
    u64 lVar1 = param_1[0xe7];
    param_1[0] = (u64)&DAT_7105111048;
    param_1[0xe7] = 0;
    if (lVar1 != 0) {
        FUN_7102b15af0((void *)lVar1);
        jeFree_710392e590((void *)lVar1);
    }
    StageBase_dtor_71025d7310(param_1);
}

// 0x7102b394f0 — D0 destructor, group 2 + FUN_7102b39540 cleanup
void FUN_7102b394f0(u64 *param_1)
{
    u64 lVar1 = param_1[1];
    param_1[0] = (u64)&DAT_7105113840;
    param_1[1] = 0;
    if (lVar1 != 0) {
        FUN_7102b39540((void *)lVar1);
        jeFree_710392e590((void *)lVar1);
    }
    jeFree_710392e590(param_1);
}
