#include "types.h"

// HARD-tier FUN_* functions — 0x7103 address range, batch hard-c-010

extern "C" {
    void jeFree_710392e590(void *p);
    void StageBase_dtor_71025d7310(void *p);
    void FUN_71025e55a0(void *p);
    void FUN_7103036620(void *p);
    void FUN_710303be40(void *p);
    void FUN_710303c4c0(void *p);
    void FUN_710303ea10(void *p);
    void FUN_7103041a00(void *p);
    void FUN_7103044a50(void *p);
    void FUN_71030517a0(void *p);
    void FUN_7103051eb0(u64 a, u64 b);
    void FUN_710305a9b0(void *p);
    void FUN_7103090090(void *p);
    void FUN_710315b4c0(void *p);
    void FUN_710315d960(void *p);
}

#define DAT_HIDDEN __attribute__((visibility("hidden")))

extern "C" DAT_HIDDEN u64 DAT_7105161b00;
extern "C" DAT_HIDDEN u64 DAT_71051624a8;
extern "C" DAT_HIDDEN u64 DAT_7105162db8;
extern "C" DAT_HIDDEN u64 DAT_7105162f50;
extern "C" DAT_HIDDEN u64 DAT_7105162fa0;
extern "C" DAT_HIDDEN u64 DAT_7105163130;
extern "C" DAT_HIDDEN u64 DAT_71051635d8;
extern "C" DAT_HIDDEN u64 DAT_71051636d0;
extern "C" DAT_HIDDEN u64 DAT_7105163d78;
extern "C" DAT_HIDDEN u64 DAT_7105168a60;
extern "C" DAT_HIDDEN u64 DAT_71052b84f8;   // lib::Singleton<app::FighterManager>::instance_

// 0x7103018000 — recursive tree delete
void FUN_7103018000(u64 *param_1)
{
    if (param_1) {
        FUN_7103018000((u64 *)param_1[0]);
        FUN_7103018000((u64 *)param_1[1]);
        jeFree_710392e590(param_1);
    }
}

// 0x7103035d90 — D1 destructor, param_1[0xee] field + FUN_71025e55a0
void FUN_7103035d90(u64 *param_1)
{
    u64 lVar1 = param_1[0xee];
    param_1[0] = (u64)&DAT_7105161b00;
    param_1[0xee] = 0;
    if (lVar1 != 0) {
        FUN_7103036620((void *)lVar1);
        jeFree_710392e590((void *)lVar1);
    }
    FUN_71025e55a0(param_1);
}

// 0x7103035de0 — D0 destructor (same as FUN_7103035d90 + free self)
void FUN_7103035de0(u64 *param_1)
{
    u64 lVar1 = param_1[0xee];
    param_1[0] = (u64)&DAT_7105161b00;
    param_1[0xee] = 0;
    if (lVar1 != 0) {
        FUN_7103036620((void *)lVar1);
        jeFree_710392e590((void *)lVar1);
    }
    FUN_71025e55a0(param_1);
    jeFree_710392e590(param_1);
}

// 0x7103036720 — D1 destructor, param_1[0xe7] field + StageBase_dtor_71025d7310
void FUN_7103036720(u64 *param_1)
{
    u64 lVar1 = param_1[0xe7];
    param_1[0] = (u64)&DAT_71051624a8;
    param_1[0xe7] = 0;
    if (lVar1 != 0) {
        FUN_710303be40((void *)lVar1);
        jeFree_710392e590((void *)lVar1);
    }
    StageBase_dtor_71025d7310(param_1);
}

// 0x710303c470 — D0 destructor, param_1[1] field + FUN_710303c4c0
void FUN_710303c470(u64 *param_1)
{
    u64 lVar1 = param_1[1];
    param_1[0] = (u64)&DAT_7105162db8;
    param_1[1] = 0;
    if (lVar1 != 0) {
        FUN_710303c4c0((void *)lVar1);
        jeFree_710392e590((void *)lVar1);
    }
    jeFree_710392e590(param_1);
}

// 0x710303cf20 — recursive tree delete
void FUN_710303cf20(u64 *param_1)
{
    if (param_1) {
        FUN_710303cf20((u64 *)param_1[0]);
        FUN_710303cf20((u64 *)param_1[1]);
        jeFree_710392e590(param_1);
    }
}

// 0x710303e9c0 — D0 destructor, param_1[1] field + FUN_710303ea10
void FUN_710303e9c0(u64 *param_1)
{
    u64 lVar1 = param_1[1];
    param_1[0] = (u64)&DAT_7105162f50;
    param_1[1] = 0;
    if (lVar1 != 0) {
        FUN_710303ea10((void *)lVar1);
        jeFree_710392e590((void *)lVar1);
    }
    jeFree_710392e590(param_1);
}

// 0x71030419b0 — D0 destructor, param_1[1] field + FUN_7103041a00
void FUN_71030419b0(u64 *param_1)
{
    u64 lVar1 = param_1[1];
    param_1[0] = (u64)&DAT_7105162fa0;
    param_1[1] = 0;
    if (lVar1 != 0) {
        FUN_7103041a00((void *)lVar1);
        jeFree_710392e590((void *)lVar1);
    }
    jeFree_710392e590(param_1);
}

// 0x7103044a00 — D0 destructor, param_1[1] field + FUN_7103044a50
void FUN_7103044a00(u64 *param_1)
{
    u64 lVar1 = param_1[1];
    param_1[0] = (u64)&DAT_7105163130;
    param_1[1] = 0;
    if (lVar1 != 0) {
        FUN_7103044a50((void *)lVar1);
        jeFree_710392e590((void *)lVar1);
    }
    jeFree_710392e590(param_1);
}

// 0x7103051750 — D0 destructor, param_1[1] field + FUN_71030517a0
void FUN_7103051750(u64 *param_1)
{
    u64 lVar1 = param_1[1];
    param_1[0] = (u64)&DAT_71051635d8;
    param_1[1] = 0;
    if (lVar1 != 0) {
        FUN_71030517a0((void *)lVar1);
        jeFree_710392e590((void *)lVar1);
    }
    jeFree_710392e590(param_1);
}

// 0x7103051e50 — D0 destructor, param_1[1] field + conditional FighterManager unregister
void FUN_7103051e50(u64 *param_1)
{
    u64 lVar1 = param_1[1];
    param_1[0] = (u64)&DAT_71051636d0;
    param_1[1] = 0;
    if (lVar1 != 0) {
        if (DAT_71052b84f8 != 0 && *(char *)(lVar1 + 8) == '\0') {
            FUN_7103051eb0(*(u64 *)DAT_71052b84f8, lVar1);
        }
        jeFree_710392e590((void *)lVar1);
    }
    jeFree_710392e590(param_1);
}

// 0x710305a960 — D0 destructor, param_1[1] field + FUN_710305a9b0
void FUN_710305a960(u64 *param_1)
{
    u64 lVar1 = param_1[1];
    param_1[0] = (u64)&DAT_7105163d78;
    param_1[1] = 0;
    if (lVar1 != 0) {
        FUN_710305a9b0((void *)lVar1);
        jeFree_710392e590((void *)lVar1);
    }
    jeFree_710392e590(param_1);
}

// 0x710308faf0 — D1 destructor, param_1[0xe7] field + StageBase_dtor_71025d7310
void FUN_710308faf0(u64 *param_1)
{
    u64 lVar1 = param_1[0xe7];
    param_1[0] = (u64)&DAT_7105168a60;
    param_1[0xe7] = 0;
    if (lVar1 != 0) {
        FUN_7103090090((void *)lVar1);
        jeFree_710392e590((void *)lVar1);
    }
    StageBase_dtor_71025d7310(param_1);
}

// 0x710315b460 — recursive tree delete with conditional cleanup at param_1[5]
void FUN_710315b460(u64 *param_1)
{
    if (param_1) {
        FUN_710315b460((u64 *)param_1[0]);
        FUN_710315b460((u64 *)param_1[1]);
        u64 lVar1 = param_1[5];
        param_1[5] = 0;
        if (lVar1 != 0) {
            FUN_710315b4c0((void *)lVar1);
            jeFree_710392e590((void *)lVar1);
        }
        jeFree_710392e590(param_1);
    }
}

// 0x710315d900 — recursive tree delete with conditional cleanup at param_1[5]
void FUN_710315d900(u64 *param_1)
{
    if (param_1) {
        FUN_710315d900((u64 *)param_1[0]);
        FUN_710315d900((u64 *)param_1[1]);
        u64 lVar1 = param_1[5];
        param_1[5] = 0;
        if (lVar1 != 0) {
            FUN_710315d960((void *)lVar1);
            jeFree_710392e590((void *)lVar1);
        }
        jeFree_710392e590(param_1);
    }
}
