#include "types.h"

// HARD-tier FUN_* functions — 0x7102 address range, batch hard-c-006

extern "C" {
    void FUN_710392e590(void *p);
    void FUN_71025d7310(void *p);
    void FUN_7102b63d10(u64 a, u64 b);
    void FUN_7102b9c830(void *p);
    void FUN_7102b9d820(void *p);
    void FUN_7102ba2960(void *p);
    void FUN_7102ba95c0(void *p);
    void FUN_7102ba9b00(void *p);
    void FUN_7102bf5230(void *p);
    void FUN_7102c0fdf0(void *p);
    void FUN_7102c6ee80(void *p);
    void FUN_7102ca3db0(void *p);
    void FUN_7102cb52e0(void *p);
    void FUN_7102cd6440(void *p);
    void FUN_7102cd84c0(void *p);
    void FUN_7102cdbd50(void *p);
}

#define DAT_HIDDEN __attribute__((visibility("hidden")))

extern "C" DAT_HIDDEN u64 DAT_71051187a0;
extern "C" DAT_HIDDEN u64 DAT_7105119080;
extern "C" DAT_HIDDEN u64 DAT_71051193a8;
extern "C" DAT_HIDDEN u64 DAT_7105119488;
extern "C" DAT_HIDDEN u64 DAT_71051194c8;
extern "C" DAT_HIDDEN u64 DAT_7105119658;
extern "C" DAT_HIDDEN u64 DAT_710511df30;
extern "C" DAT_HIDDEN u64 DAT_710511f750;
extern "C" DAT_HIDDEN u64 DAT_71051268e0;
extern "C" DAT_HIDDEN u64 DAT_710512a180;
extern "C" DAT_HIDDEN u64 DAT_710512c078;
extern "C" DAT_HIDDEN u64 DAT_710512f528;
extern "C" DAT_HIDDEN u64 DAT_710512f5f8;
extern "C" DAT_HIDDEN u64 DAT_710512f6a8;

// 0x7102b5af20 — two-field dispatch: calls FUN_7102b63d10 for each non-null field at +0x90/+0x98
void FUN_7102b5af20(u64 param_1, u64 param_2)
{
    if (*(u64 *)(param_1 + 0x90) != 0)
        FUN_7102b63d10(*(u64 *)(param_1 + 0x90), param_2);
    if (*(u64 *)(param_1 + 0x98) != 0)
        FUN_7102b63d10(*(u64 *)(param_1 + 0x98), param_2);
}

// 0x7102b93d30 — D1 destructor, param_1[0xe7] field + FUN_71025d7310
void FUN_7102b93d30(u64 *param_1)
{
    u64 lVar1 = param_1[0xe7];
    param_1[0] = (u64)&DAT_71051187a0;
    param_1[0xe7] = 0;
    if (lVar1 != 0) {
        FUN_7102b9c830((void *)lVar1);
        FUN_710392e590((void *)lVar1);
    }
    FUN_71025d7310(param_1);
}

// 0x7102b9d7d0 — D0 destructor, group 2 + FUN_7102b9d820 cleanup
void FUN_7102b9d7d0(u64 *param_1)
{
    u64 lVar1 = param_1[1];
    param_1[0] = (u64)&DAT_7105119080;
    param_1[1] = 0;
    if (lVar1 != 0) {
        FUN_7102b9d820((void *)lVar1);
        FUN_710392e590((void *)lVar1);
    }
    FUN_710392e590(param_1);
}

// 0x7102ba4980 — D1 destructor, param_1[0x73] field + inner-pointer free + FUN_7102ba2960
void FUN_7102ba4980(u64 *param_1)
{
    u64 *plVar2 = (u64 *)param_1[0x73];
    param_1[0] = (u64)&DAT_71051193a8;
    param_1[0x73] = 0;
    if (plVar2 != nullptr) {
        u64 lVar1 = plVar2[0];
        plVar2[0] = 0;
        if (lVar1 != 0)
            FUN_710392e590((void *)lVar1);
        FUN_710392e590(plVar2);
    }
    FUN_7102ba2960(param_1);
}

// 0x7102ba9570 — D0 destructor, group 2 + FUN_7102ba95c0 cleanup
void FUN_7102ba9570(u64 *param_1)
{
    u64 lVar1 = param_1[1];
    param_1[0] = (u64)&DAT_7105119488;
    param_1[1] = 0;
    if (lVar1 != 0) {
        FUN_7102ba95c0((void *)lVar1);
        FUN_710392e590((void *)lVar1);
    }
    FUN_710392e590(param_1);
}

// 0x7102ba9ab0 — D0 destructor, group 2 + FUN_7102ba9b00(inner+8)
void FUN_7102ba9ab0(u64 *param_1)
{
    u64 lVar1 = param_1[1];
    param_1[0] = (u64)&DAT_71051194c8;
    param_1[1] = 0;
    if (lVar1 != 0) {
        FUN_7102ba9b00((void *)*(u64 *)(lVar1 + 8));
        FUN_710392e590((void *)lVar1);
    }
    FUN_710392e590(param_1);
}

// 0x7102bae2c0 — D0 destructor, group 2 + vtable call at inner+0x20
void FUN_7102bae2c0(u64 *param_1)
{
    u64 lVar2 = param_1[1];
    param_1[0] = (u64)&DAT_7105119658;
    param_1[1] = 0;
    if (lVar2 != 0) {
        u64 *plVar1 = (u64 *)*(u64 *)(lVar2 + 0x20);
        *(u64 *)(lVar2 + 0x20) = 0;
        if (plVar1 != nullptr) {
            u64 *vtable = (u64 *)plVar1[0];
            ((void (*)(u64 *))vtable[1])(plVar1);
        }
        FUN_710392e590((void *)lVar2);
    }
    FUN_710392e590(param_1);
}

// 0x7102bf3470 — D1 destructor, param_1[0xe7] field + FUN_71025d7310
void FUN_7102bf3470(u64 *param_1)
{
    u64 lVar1 = param_1[0xe7];
    param_1[0] = (u64)&DAT_710511df30;
    param_1[0xe7] = 0;
    if (lVar1 != 0) {
        FUN_7102bf5230((void *)lVar1);
        FUN_710392e590((void *)lVar1);
    }
    FUN_71025d7310(param_1);
}

// 0x7102c0a4c0 — D1 destructor, param_1[0xe7] field + FUN_71025d7310
void FUN_7102c0a4c0(u64 *param_1)
{
    u64 lVar1 = param_1[0xe7];
    param_1[0] = (u64)&DAT_710511f750;
    param_1[0xe7] = 0;
    if (lVar1 != 0) {
        FUN_7102c0fdf0((void *)lVar1);
        FUN_710392e590((void *)lVar1);
    }
    FUN_71025d7310(param_1);
}

// 0x7102c6c8d0 — D1 destructor, param_1[0xe7] field + FUN_71025d7310
void FUN_7102c6c8d0(u64 *param_1)
{
    u64 lVar1 = param_1[0xe7];
    param_1[0] = (u64)&DAT_71051268e0;
    param_1[0xe7] = 0;
    if (lVar1 != 0) {
        FUN_7102c6ee80((void *)lVar1);
        FUN_710392e590((void *)lVar1);
    }
    FUN_71025d7310(param_1);
}

// 0x7102ca2410 — D1 destructor, param_1[0xe7] field + FUN_71025d7310
void FUN_7102ca2410(u64 *param_1)
{
    u64 lVar1 = param_1[0xe7];
    param_1[0] = (u64)&DAT_710512a180;
    param_1[0xe7] = 0;
    if (lVar1 != 0) {
        FUN_7102ca3db0((void *)lVar1);
        FUN_710392e590((void *)lVar1);
    }
    FUN_71025d7310(param_1);
}

// 0x7102cb2f60 — D1 destructor, param_1[0xe7] field + FUN_71025d7310
void FUN_7102cb2f60(u64 *param_1)
{
    u64 lVar1 = param_1[0xe7];
    param_1[0] = (u64)&DAT_710512c078;
    param_1[0xe7] = 0;
    if (lVar1 != 0) {
        FUN_7102cb52e0((void *)lVar1);
        FUN_710392e590((void *)lVar1);
    }
    FUN_71025d7310(param_1);
}

// 0x7102cd63f0 — D0 destructor, group 2 + FUN_7102cd6440 cleanup
void FUN_7102cd63f0(u64 *param_1)
{
    u64 lVar1 = param_1[1];
    param_1[0] = (u64)&DAT_710512f528;
    param_1[1] = 0;
    if (lVar1 != 0) {
        FUN_7102cd6440((void *)lVar1);
        FUN_710392e590((void *)lVar1);
    }
    FUN_710392e590(param_1);
}

// 0x7102cd8470 — D0 destructor, group 2 + FUN_7102cd84c0 cleanup
void FUN_7102cd8470(u64 *param_1)
{
    u64 lVar1 = param_1[1];
    param_1[0] = (u64)&DAT_710512f5f8;
    param_1[1] = 0;
    if (lVar1 != 0) {
        FUN_7102cd84c0((void *)lVar1);
        FUN_710392e590((void *)lVar1);
    }
    FUN_710392e590(param_1);
}

// 0x7102cdbd00 — D0 destructor, group 2 + FUN_7102cdbd50 cleanup
void FUN_7102cdbd00(u64 *param_1)
{
    u64 lVar1 = param_1[1];
    param_1[0] = (u64)&DAT_710512f6a8;
    param_1[1] = 0;
    if (lVar1 != 0) {
        FUN_7102cdbd50((void *)lVar1);
        FUN_710392e590((void *)lVar1);
    }
    FUN_710392e590(param_1);
}
