#include "types.h"

// HARD-tier FUN_* functions — 0x7102 address range, batch hard-c-004

extern "C" {
    void FUN_710392e590(void *p);
    void FUN_710276a2f0(void *p);
    void FUN_71027bc030(void *p);
    void FUN_71027c3060(void *p);
    void FUN_7102810180(void *p);
    void FUN_710280cf00(void *p);
    void FUN_71025d7310(void *p);
    void FUN_71025e55a0(void *p);
    void FUN_7102851d30(void *p);
    void FUN_71028554a0(void *p);
    void FUN_7102859660(void *p);
    void FUN_710285d4d0(void *p);
    void FUN_710285e6c0(void *p);
    void FUN_710285ea30(void *p);
    void FUN_71028675d0(void *p);
    void FUN_71028abd60(void *p);
}

#define DAT_HIDDEN __attribute__((visibility("hidden")))

extern "C" DAT_HIDDEN u64 DAT_71050dad28;
extern "C" DAT_HIDDEN u64 DAT_71050e06c8;
extern "C" DAT_HIDDEN u64 DAT_71050e49c0;
extern "C" DAT_HIDDEN u64 DAT_71050e52a8;
extern "C" DAT_HIDDEN u64 DAT_71050e9eb0;
extern "C" DAT_HIDDEN u64 DAT_71050eb118;
extern "C" DAT_HIDDEN u64 DAT_71050eb2b0;
extern "C" DAT_HIDDEN u64 DAT_71050eb320;
extern "C" DAT_HIDDEN u64 DAT_71050eb370;
extern "C" DAT_HIDDEN u64 DAT_71050eb3e0;
extern "C" DAT_HIDDEN u64 DAT_71050eb460;
extern "C" DAT_HIDDEN u64 DAT_71050eb580;
extern "C" DAT_HIDDEN u64 DAT_71050eb6b0;
extern "C" DAT_HIDDEN u64 DAT_71050ef248;

// 0x7102769530 — D0 destructor, group 2 + FUN_710276a2f0 cleanup
void FUN_7102769530(u64 *param_1)
{
    u64 lVar1 = param_1[1];
    param_1[0] = (u64)&DAT_71050dad28;
    param_1[1] = 0;
    if (lVar1 != 0) {
        FUN_710276a2f0((void *)lVar1);
        FUN_710392e590((void *)lVar1);
    }
    FUN_710392e590(param_1);
}

// 0x71027bc3e0 — D1 destructor, param_1[0x179] field + sub-cleanup at param_1+0xe8
void FUN_71027bc3e0(u64 *param_1)
{
    u64 lVar1 = param_1[0x179];
    param_1[0] = (u64)&DAT_71050e06c8;
    param_1[0x179] = 0;
    if (lVar1 != 0) {
        FUN_71027c3060((void *)lVar1);
        FUN_710392e590((void *)lVar1);
    }
    FUN_71027bc030(param_1 + 0xe8);
    FUN_71025d7310(param_1);
}

// 0x710280cfa0 — D1 destructor, param_1[0x108] field + sub-cleanup at param_1+0xef
void FUN_710280cfa0(u64 *param_1)
{
    u64 lVar1 = param_1[0x108];
    param_1[0] = (u64)&DAT_71050e49c0;
    param_1[0x108] = 0;
    if (lVar1 != 0) {
        FUN_7102810180((void *)lVar1);
        FUN_710392e590((void *)lVar1);
    }
    FUN_710280cf00(param_1 + 0xef);
    FUN_71025e55a0(param_1);
}

// 0x710280d2d0 — D1 destructor, param_1[0x101] field + sub-cleanup at param_1+0xe8
void FUN_710280d2d0(u64 *param_1)
{
    u64 lVar1 = param_1[0x101];
    param_1[0] = (u64)&DAT_71050e52a8;
    param_1[0x101] = 0;
    if (lVar1 != 0) {
        FUN_7102810180((void *)lVar1);
        FUN_710392e590((void *)lVar1);
    }
    FUN_710280cf00(param_1 + 0xe8);
    FUN_71025d7310(param_1);
}

// 0x7102852060 — D1 destructor, param_1[0xee] field + FUN_7102851d30(inner+0x10) + FUN_71025e55a0
void FUN_7102852060(u64 *param_1)
{
    u64 lVar1 = param_1[0xee];
    param_1[0] = (u64)&DAT_71050e9eb0;
    param_1[0xee] = 0;
    if (lVar1 != 0) {
        FUN_7102851d30((void *)(lVar1 + 0x10));
        FUN_710392e590((void *)lVar1);
    }
    FUN_71025e55a0(param_1);
}

// 0x7102855450 — D0 destructor, group 2 + FUN_71028554a0 cleanup
void FUN_7102855450(u64 *param_1)
{
    u64 lVar1 = param_1[1];
    param_1[0] = (u64)&DAT_71050eb118;
    param_1[1] = 0;
    if (lVar1 != 0) {
        FUN_71028554a0((void *)lVar1);
        FUN_710392e590((void *)lVar1);
    }
    FUN_710392e590(param_1);
}

// 0x7102859610 — D0 destructor, group 2 + FUN_7102859660 cleanup
void FUN_7102859610(u64 *param_1)
{
    u64 lVar1 = param_1[1];
    param_1[0] = (u64)&DAT_71050eb2b0;
    param_1[1] = 0;
    if (lVar1 != 0) {
        FUN_7102859660((void *)lVar1);
        FUN_710392e590((void *)lVar1);
    }
    FUN_710392e590(param_1);
}

// 0x710285aae0 — D0 destructor, group 2 + copy-then-free at inner[0]/inner[1]
void FUN_710285aae0(u64 *param_1)
{
    u64 *plVar1 = (u64 *)param_1[1];
    param_1[0] = (u64)&DAT_71050eb320;
    param_1[1] = 0;
    if (plVar1 != nullptr) {
        u64 tmp = plVar1[0];
        if (tmp != 0) {
            plVar1[1] = tmp;
            FUN_710392e590((void *)tmp);
        }
        FUN_710392e590(plVar1);
    }
    FUN_710392e590(param_1);
}

// 0x710285d480 — D0 destructor, group 2 + FUN_710285d4d0 cleanup
void FUN_710285d480(u64 *param_1)
{
    u64 lVar1 = param_1[1];
    param_1[0] = (u64)&DAT_71050eb370;
    param_1[1] = 0;
    if (lVar1 != 0) {
        FUN_710285d4d0((void *)lVar1);
        FUN_710392e590((void *)lVar1);
    }
    FUN_710392e590(param_1);
}

// 0x710285e670 — D0 destructor, group 2 + FUN_710285e6c0 cleanup
void FUN_710285e670(u64 *param_1)
{
    u64 lVar1 = param_1[1];
    param_1[0] = (u64)&DAT_71050eb3e0;
    param_1[1] = 0;
    if (lVar1 != 0) {
        FUN_710285e6c0((void *)lVar1);
        FUN_710392e590((void *)lVar1);
    }
    FUN_710392e590(param_1);
}

// 0x710285e9e0 — D0 destructor, group 2 + FUN_710285ea30(inner+8) cleanup
void FUN_710285e9e0(u64 *param_1)
{
    u64 lVar1 = param_1[1];
    param_1[0] = (u64)&DAT_71050eb460;
    param_1[1] = 0;
    if (lVar1 != 0) {
        FUN_710285ea30((void *)(lVar1 + 8));
        FUN_710392e590((void *)lVar1);
    }
    FUN_710392e590(param_1);
}

// 0x7102867580 — D0 destructor, group 2 + FUN_71028675d0 cleanup
void FUN_7102867580(u64 *param_1)
{
    u64 lVar1 = param_1[1];
    param_1[0] = (u64)&DAT_71050eb580;
    param_1[1] = 0;
    if (lVar1 != 0) {
        FUN_71028675d0((void *)lVar1);
        FUN_710392e590((void *)lVar1);
    }
    FUN_710392e590(param_1);
}

// 0x710286b090 — D0 destructor, group 2 + vtable call at inner+0x20
void FUN_710286b090(u64 *param_1)
{
    u64 lVar2 = param_1[1];
    param_1[0] = (u64)&DAT_71050eb6b0;
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

// 0x71028ab2e0 — D1 destructor, param_1[0xee] field + FUN_71028abd60 + FUN_71025e55a0
void FUN_71028ab2e0(u64 *param_1)
{
    u64 lVar1 = param_1[0xee];
    param_1[0] = (u64)&DAT_71050ef248;
    param_1[0xee] = 0;
    if (lVar1 != 0) {
        FUN_71028abd60((void *)lVar1);
        FUN_710392e590((void *)lVar1);
    }
    FUN_71025e55a0(param_1);
}

// 0x71028ab330 — D0 destructor (same as FUN_71028ab2e0 + free self)
void FUN_71028ab330(u64 *param_1)
{
    u64 lVar1 = param_1[0xee];
    param_1[0] = (u64)&DAT_71050ef248;
    param_1[0xee] = 0;
    if (lVar1 != 0) {
        FUN_71028abd60((void *)lVar1);
        FUN_710392e590((void *)lVar1);
    }
    FUN_71025e55a0(param_1);
    FUN_710392e590(param_1);
}
