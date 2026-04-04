#include "types.h"

// HARD-tier FUN_* functions — 0x7103 address range, batch hard-c-011

extern "C" {
    void FUN_710392e590(void *p);
    void FUN_710315f0a0(void *p);
    void FUN_7103163ac0(void *p);
    void FUN_7103168090(void *p);
    void FUN_710326de90(void *p);
    void FUN_71032ce2d0(void *p);
    void FUN_71032e5d80(void *p);
    void FUN_71032ea640(void *p);
    void FUN_71032f3a10(void *p);
    void FUN_710330a7b0(void *p);
    void FUN_7103311e20(void *p);
    void FUN_71033174c0(void *p);
    void FUN_7103547110(void *p);
    void FUN_71035471c0(void *p);
}

#define DAT_HIDDEN __attribute__((visibility("hidden")))

extern "C" DAT_HIDDEN u64 DAT_7105180e98;
extern "C" DAT_HIDDEN u64 DAT_7105182338;
extern "C" DAT_HIDDEN u64 DAT_71051825f0;
extern "C" DAT_HIDDEN u64 DAT_7105182630;
extern "C" DAT_HIDDEN u64 DAT_7105182708;
extern "C" DAT_HIDDEN u64 DAT_7105182848;
extern "C" DAT_HIDDEN u64 DAT_71051828d0;
extern "C" DAT_HIDDEN u64 DAT_71051828f0;

// 0x710315f1d0 — recursive tree delete with interior-pointer cleanup at param_1[5]+8
void FUN_710315f1d0(u64 *param_1)
{
    if (param_1) {
        FUN_710315f1d0((u64 *)param_1[0]);
        FUN_710315f1d0((u64 *)param_1[1]);
        u64 lVar1 = param_1[5];
        param_1[5] = 0;
        if (lVar1 != 0) {
            FUN_710315f0a0((void *)(lVar1 + 8));
            FUN_710392e590((void *)lVar1);
        }
        FUN_710392e590(param_1);
    }
}

// 0x7103163a60 — recursive tree delete with conditional cleanup at param_1[5]
void FUN_7103163a60(u64 *param_1)
{
    if (param_1) {
        FUN_7103163a60((u64 *)param_1[0]);
        FUN_7103163a60((u64 *)param_1[1]);
        u64 lVar1 = param_1[5];
        param_1[5] = 0;
        if (lVar1 != 0) {
            FUN_7103163ac0((void *)lVar1);
            FUN_710392e590((void *)lVar1);
        }
        FUN_710392e590(param_1);
    }
}

// 0x7103168030 — recursive tree delete with conditional cleanup at param_1[5]
void FUN_7103168030(u64 *param_1)
{
    if (param_1) {
        FUN_7103168030((u64 *)param_1[0]);
        FUN_7103168030((u64 *)param_1[1]);
        u64 lVar1 = param_1[5];
        param_1[5] = 0;
        if (lVar1 != 0) {
            FUN_7103168090((void *)lVar1);
            FUN_710392e590((void *)lVar1);
        }
        FUN_710392e590(param_1);
    }
}

// 0x710316ae00 — recursive tree delete, just free param_1[5] (no separate cleanup)
void FUN_710316ae00(u64 *param_1)
{
    if (param_1) {
        FUN_710316ae00((u64 *)param_1[0]);
        FUN_710316ae00((u64 *)param_1[1]);
        u64 lVar1 = param_1[5];
        param_1[5] = 0;
        if (lVar1 != 0) {
            FUN_710392e590((void *)lVar1);
        }
        FUN_710392e590(param_1);
    }
}

// 0x7103178b70 — recursive tree delete, just free param_1[5] (no separate cleanup)
void FUN_7103178b70(u64 *param_1)
{
    if (param_1) {
        FUN_7103178b70((u64 *)param_1[0]);
        FUN_7103178b70((u64 *)param_1[1]);
        u64 lVar1 = param_1[5];
        param_1[5] = 0;
        if (lVar1 != 0) {
            FUN_710392e590((void *)lVar1);
        }
        FUN_710392e590(param_1);
    }
}

// 0x71032131f0 — recursive tree delete
void FUN_71032131f0(u64 *param_1)
{
    if (param_1) {
        FUN_71032131f0((u64 *)param_1[0]);
        FUN_71032131f0((u64 *)param_1[1]);
        FUN_710392e590(param_1);
    }
}

// 0x710321a950 — recursive tree delete
void FUN_710321a950(u64 *param_1)
{
    if (param_1) {
        FUN_710321a950((u64 *)param_1[0]);
        FUN_710321a950((u64 *)param_1[1]);
        FUN_710392e590(param_1);
    }
}

// 0x710326de40 — D0 destructor, param_1[1] field + FUN_710326de90
void FUN_710326de40(u64 *param_1)
{
    u64 lVar1 = param_1[1];
    param_1[0] = (u64)&DAT_7105180e98;
    param_1[1] = 0;
    if (lVar1 != 0) {
        FUN_710326de90((void *)lVar1);
        FUN_710392e590((void *)lVar1);
    }
    FUN_710392e590(param_1);
}

// 0x71032ce280 — D0 destructor, param_1[1] field + FUN_71032ce2d0
void FUN_71032ce280(u64 *param_1)
{
    u64 lVar1 = param_1[1];
    param_1[0] = (u64)&DAT_7105182338;
    param_1[1] = 0;
    if (lVar1 != 0) {
        FUN_71032ce2d0((void *)lVar1);
        FUN_710392e590((void *)lVar1);
    }
    FUN_710392e590(param_1);
}

// 0x71032e8520 — D0 destructor, param_1[1] field + FUN_71032e5d80
void FUN_71032e8520(u64 *param_1)
{
    u64 lVar1 = param_1[1];
    param_1[0] = (u64)&DAT_71051825f0;
    param_1[1] = 0;
    if (lVar1 != 0) {
        FUN_71032e5d80((void *)lVar1);
        FUN_710392e590((void *)lVar1);
    }
    FUN_710392e590(param_1);
}

// 0x71032ea780 — D0 destructor, param_1[1] field + FUN_71032ea640
void FUN_71032ea780(u64 *param_1)
{
    u64 lVar1 = param_1[1];
    param_1[0] = (u64)&DAT_7105182630;
    param_1[1] = 0;
    if (lVar1 != 0) {
        FUN_71032ea640((void *)lVar1);
        FUN_710392e590((void *)lVar1);
    }
    FUN_710392e590(param_1);
}

// 0x71032fe3d0 — D0 destructor, param_1[1] field + FUN_71032f3a10
void FUN_71032fe3d0(u64 *param_1)
{
    u64 lVar1 = param_1[1];
    param_1[0] = (u64)&DAT_7105182708;
    param_1[1] = 0;
    if (lVar1 != 0) {
        FUN_71032f3a10((void *)lVar1);
        FUN_710392e590((void *)lVar1);
    }
    FUN_710392e590(param_1);
}

// 0x7103310cb0 — D0 destructor, param_1[1] field + FUN_710330a7b0
void FUN_7103310cb0(u64 *param_1)
{
    u64 lVar1 = param_1[1];
    param_1[0] = (u64)&DAT_7105182848;
    param_1[1] = 0;
    if (lVar1 != 0) {
        FUN_710330a7b0((void *)lVar1);
        FUN_710392e590((void *)lVar1);
    }
    FUN_710392e590(param_1);
}

// 0x7103311f00 — recursive tree delete
void FUN_7103311f00(u64 *param_1)
{
    if (param_1) {
        FUN_7103311f00((u64 *)param_1[0]);
        FUN_7103311f00((u64 *)param_1[1]);
        FUN_710392e590(param_1);
    }
}

// 0x7103313fd0 — D0 destructor, param_1[1] field + FUN_7103311e20
void FUN_7103313fd0(u64 *param_1)
{
    u64 lVar1 = param_1[1];
    param_1[0] = (u64)&DAT_71051828d0;
    param_1[1] = 0;
    if (lVar1 != 0) {
        FUN_7103311e20((void *)lVar1);
        FUN_710392e590((void *)lVar1);
    }
    FUN_710392e590(param_1);
}

// 0x71033176a0 — D0 destructor, param_1[1] field + FUN_71033174c0
void FUN_71033176a0(u64 *param_1)
{
    u64 lVar1 = param_1[1];
    param_1[0] = (u64)&DAT_71051828f0;
    param_1[1] = 0;
    if (lVar1 != 0) {
        FUN_71033174c0((void *)lVar1);
        FUN_710392e590((void *)lVar1);
    }
    FUN_710392e590(param_1);
}

// 0x710334bdd0 — recursive tree delete
void FUN_710334bdd0(u64 *param_1)
{
    if (param_1) {
        FUN_710334bdd0((u64 *)param_1[0]);
        FUN_710334bdd0((u64 *)param_1[1]);
        FUN_710392e590(param_1);
    }
}

// 0x710334be10 — recursive tree delete
void FUN_710334be10(u64 *param_1)
{
    if (param_1) {
        FUN_710334be10((u64 *)param_1[0]);
        FUN_710334be10((u64 *)param_1[1]);
        FUN_710392e590(param_1);
    }
}

// 0x710353b1c0 — recursive tree delete
void FUN_710353b1c0(u64 *param_1)
{
    if (param_1) {
        FUN_710353b1c0((u64 *)param_1[0]);
        FUN_710353b1c0((u64 *)param_1[1]);
        FUN_710392e590(param_1);
    }
}

// 0x710353fec0 — recursive tree delete
void FUN_710353fec0(u64 *param_1)
{
    if (param_1) {
        FUN_710353fec0((u64 *)param_1[0]);
        FUN_710353fec0((u64 *)param_1[1]);
        FUN_710392e590(param_1);
    }
}

// 0x71035470c0 — recursive tree delete with two cleanup calls
void FUN_71035470c0(u64 *param_1)
{
    if (param_1) {
        FUN_71035470c0((u64 *)param_1[0]);
        FUN_71035470c0((u64 *)param_1[1]);
        FUN_7103547110((void *)param_1[9]);
        FUN_71035471c0((void *)param_1[6]);
        FUN_710392e590(param_1);
    }
}
