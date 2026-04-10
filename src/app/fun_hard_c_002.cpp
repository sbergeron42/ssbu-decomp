#include "types.h"

// HARD-tier FUN_* functions — 0x7102 address range, batch hard-c-002

extern "C" {
    void jeFree_710392e590(void *p);
    void FUN_71037238c0(void *a, void *b);
    void FUN_7103724110(void *p);
    void FUN_71023a6a30(void *p);
    void FUN_71023b01f0(void *p);
    void FUN_71024970d0(void *p);
    void FUN_71025157f0(void *p);
    void FUN_71025a5ff0(void *p);
    __attribute__((noreturn)) void abortWrapper_71039c20a0(void);
}

#define DAT_HIDDEN __attribute__((visibility("hidden")))

// Group 1 base vtable (shared with 001)
extern "C" DAT_HIDDEN u64 DAT_71050b52f0;
// Group 1B vtables
extern "C" DAT_HIDDEN u64 DAT_71050b8ac0;
// Group 1A vtables
extern "C" DAT_HIDDEN u64 DAT_71050b8e60;
extern "C" DAT_HIDDEN u64 DAT_71050b91f0;
// Group 2 vtables
extern "C" DAT_HIDDEN u64 DAT_71050bf9f8;
extern "C" DAT_HIDDEN u64 DAT_71050c4440;
extern "C" DAT_HIDDEN u64 DAT_71050c4460;
// Data arg for FUN_71037238c0
extern "C" DAT_HIDDEN u64 DAT_7105328788;

// 0x710239e060 — D1 destructor, group 1B (FUN_71037238c0 cleanup)
void FUN_710239e060(u64 *param_1)
{
    u64 *puVar1 = (u64 *)param_1[0x1d];
    param_1[0] = (u64)&DAT_71050b8ac0;
    param_1[0x1d] = 0;
    if (puVar1 != nullptr) {
        FUN_71037238c0((void *)puVar1[0], &DAT_7105328788);
        jeFree_710392e590(puVar1);
    }
    param_1[0] = (u64)&DAT_71050b52f0;
    FUN_7103724110(param_1 + 10);
}

// 0x71023a6c40 — D1 destructor, group 1A (FUN_71023a6a30 cleanup)
void FUN_71023a6c40(u64 *param_1)
{
    u64 lVar1 = param_1[0x1d];
    param_1[0] = (u64)&DAT_71050b8e60;
    param_1[0x1d] = 0;
    if (lVar1 != 0) {
        FUN_71023a6a30((void *)lVar1);
        jeFree_710392e590((void *)lVar1);
    }
    param_1[0] = (u64)&DAT_71050b52f0;
    FUN_7103724110(param_1 + 10);
}

// 0x71023b0420 — D1 destructor, group 1A (FUN_71023b01f0 cleanup)
void FUN_71023b0420(u64 *param_1)
{
    u64 lVar1 = param_1[0x1d];
    param_1[0] = (u64)&DAT_71050b91f0;
    param_1[0x1d] = 0;
    if (lVar1 != 0) {
        FUN_71023b01f0((void *)lVar1);
        jeFree_710392e590((void *)lVar1);
    }
    param_1[0] = (u64)&DAT_71050b52f0;
    FUN_7103724110(param_1 + 10);
}

// 0x71023d44b0 — binary tree recursive delete
void FUN_71023d44b0(u64 *p)
{
    if (p) {
        FUN_71023d44b0((u64 *)p[0]);
        FUN_71023d44b0((u64 *)p[1]);
        jeFree_710392e590(p);
    }
}

// 0x710248fac0 — binary tree recursive delete
void FUN_710248fac0(u64 *p)
{
    if (p) {
        FUN_710248fac0((u64 *)p[0]);
        FUN_710248fac0((u64 *)p[1]);
        jeFree_710392e590(p);
    }
}

// 0x71024971b0 — call cleanup fn then free param_1 if non-null
void FUN_71024971b0(u64 *param_1)
{
    FUN_71024970d0(param_1);
    if (param_1 != nullptr)
        jeFree_710392e590(param_1);
}

// 0x7102518a90 — D0 destructor, group 2 (FUN_71025157f0 cleanup)
void FUN_7102518a90(u64 *param_1)
{
    u64 lVar1 = param_1[1];
    param_1[0] = (u64)&DAT_71050bf9f8;
    param_1[1] = 0;
    if (lVar1 != 0) {
        FUN_71025157f0((void *)lVar1);
        jeFree_710392e590((void *)lVar1);
    }
    jeFree_710392e590(param_1);
}

// 0x710259e5a0 — abort wrapper (noreturn)
void FUN_710259e5a0(void)
{
    abortWrapper_71039c20a0();
}

// 0x71025a76f0 — D0 destructor, group 2 with double cleanup (FUN_71025a5ff0)
void FUN_71025a76f0(u64 *param_1)
{
    u64 lVar1 = param_1[1];
    param_1[0] = (u64)&DAT_71050c4440;
    param_1[1] = 0;
    if (lVar1 != 0) {
        FUN_71025a5ff0((void *)lVar1);
        jeFree_710392e590((void *)lVar1);
        lVar1 = param_1[1];
        param_1[1] = 0;
        if (lVar1 != 0) {
            FUN_71025a5ff0((void *)lVar1);
            jeFree_710392e590((void *)lVar1);
        }
    }
    jeFree_710392e590(param_1);
}

// 0x71025accb0 — D0 destructor, group 2 with inner field at +0x218
void FUN_71025accb0(u64 *param_1)
{
    u64 lVar2 = param_1[1];
    param_1[0] = (u64)&DAT_71050c4460;
    param_1[1] = 0;
    if (lVar2 != 0) {
        u64 lVar1 = *(u64 *)(lVar2 + 0x218);
        *(u64 *)(lVar2 + 0x218) = 0;
        if (lVar1 != 0) {
            jeFree_710392e590((void *)lVar1);
        }
        jeFree_710392e590((void *)lVar2);
    }
    jeFree_710392e590(param_1);
}
