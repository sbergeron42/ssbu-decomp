#include "types.h"

// HARD-tier FUN_* functions — 0x7100 address range, batch hard-d-005
// Pool-d worker: struct zero, wrappers, list ops, virtual dtors

// ---- External declarations -----------------------------------------------

extern void FUN_7100127430(u64);
extern void FUN_71000b2890(s64);
extern u64  FUN_710015f8a0(s64);
extern void FUN_71001545b0(void);
extern void FUN_7100154360(s64);
extern void FUN_7100165330(void);
extern void FUN_71001308d0(u64 *);
extern void FUN_71001d6880(s64);
extern void FUN_71001cba40(s64);
extern void FUN_71001ce8e0(s64);
extern void FUN_7100228130(void);
extern void FUN_710022adb0(s64);
extern void FUN_710022adb0(s64, u64);
extern void FUN_71000319e0(u64, u64, u64);
extern void FUN_71000319d0(u64);
extern void FUN_710003a260(s64);
extern void FUN_710003a120(s64);
extern void FUN_7100130920(s64);
extern void FUN_71001549d0(s64);
extern void FUN_710013f900(void);

namespace nn { namespace os {
    void LockMutex(void *);
    void UnlockMutex(void *);
}}

// ---- Functions ---------------------------------------------------------------

// 0x7100038250 — zero 29 u64 slots of struct (64 bytes)
void FUN_7100038250(u64 *param_1)
{
    param_1[0x1b] = 0; param_1[0x1c] = 0;
    param_1[0]    = 0;
    param_1[0x19] = 0; param_1[0x1a] = 0;
    param_1[0x17] = 0; param_1[0x18] = 0;
    param_1[0x15] = 0; param_1[0x16] = 0;
    param_1[0x13] = 0; param_1[0x14] = 0;
    param_1[0x11] = 0; param_1[0x12] = 0;
    param_1[0x0f] = 0; param_1[0x10] = 0;
    param_1[0x0d] = 0; param_1[0x0e] = 0;
    param_1[0x0b] = 0; param_1[0x0c] = 0;
    param_1[9]    = 0; param_1[10]   = 0;
    param_1[7]    = 0; param_1[8]    = 0;
    param_1[5]    = 0; param_1[6]    = 0;
    param_1[3]    = 0; param_1[4]    = 0;
    param_1[1]    = 0; param_1[2]    = 0;
}

// 0x7100117080 — wrapper: load *param_1 and forward to fn (64 bytes)
void FUN_7100117080(u64 *param_1)
{
    FUN_7100127430(*param_1);
}

// 0x7100118510 — call fn 4 times at +0x20, +0x40, +0x60, +0x80 (64 bytes)
void FUN_7100118510(s64 param_1)
{
    FUN_71000b2890(param_1 + 0x20);
    FUN_71000b2890(param_1 + 0x40);
    FUN_71000b2890(param_1 + 0x60);
    FUN_71000b2890(param_1 + 0x80);
}

// 0x710013ce70 — see fun_hard_d_006.cpp (PTR_DAT)

// 0x710013d130 — see fun_hard_d_006.cpp (PTR_DAT)

// 0x710013e400 — see fun_hard_d_006.cpp (PTR_DAT)

// 0x7100153770 — guard check then clear two fields and call (64 bytes)
void FUN_7100153770(s64 param_1)
{
    if (*(s64 *)(param_1 + 0xd0) != 0) {
        FUN_71001545b0();
    }
    *(u64 *)(param_1 + 0x30) = 0;
    *(u64 *)(param_1 + 0x38) = 0;
    FUN_7100154360(param_1);
}

// 0x7100154800 — lock, call inner fn, unlock (64 bytes)
void FUN_7100154800(s64 param_1)
{
    nn::os::LockMutex((void *)(param_1 + 0x340));
    FUN_71001549d0(param_1);
    nn::os::UnlockMutex((void *)(param_1 + 0x340));
}

// 0x7100156b10 — guard: if param_2 non-null, call dtor and free (48 bytes)
void FUN_7100156b10(u64 param_1, s64 param_2)
{
    if (param_2 != 0) {
        FUN_7100130920(param_2);
        FUN_71001308d0((u64 *)param_2);
    }
}

// 0x71001570d0 — linked list walk: clear two fields per node (64 bytes)
void FUN_71001570d0(s64 param_1)
{
    s64 lVar1;
    s64 lVar2;

    if (*(s64 *)(param_1 + 0x18) != param_1 + 0x10) {
        lVar1 = (s64)*(s32 *)(param_1 + 0x24);
        lVar2 = *(s64 *)(param_1 + 0x18) - lVar1;
        do {
            *(u64 *)(lVar2 + 8)    = 0;
            *(u64 *)(lVar2 + 0x10) = 0;
            lVar2 = *(s64 *)(lVar2 + lVar1 + 8) - lVar1;
        } while (lVar2 != (param_1 + 0x10) - lVar1);
    }
    *(u8 *)(param_1 + 0x28) = 0;
}

// 0x71001628a0 — assert two pointer fields are null (64 bytes)
void FUN_71001628a0(s64 param_1)
{
    if (*(s64 *)(param_1 + 0x18) != 0) {
        FUN_7100165330();
    }
    if (*(s64 *)(param_1 + 0x20) != 0) {
        FUN_7100165330();
    }
}

// 0x71001772b0 — set vtable pointer (48 bytes)
// NOTE: uses PTR_DAT_71052a5278 — see fun_hard_d_006.cpp

// 0x71001794c0 — virtual dtor: call vtable[0], then free (48 bytes)
void FUN_71001794c0(u64 param_1, u64 *param_2)
{
    if (param_2 != nullptr) {
        (*(void (**)(u64 *))(*param_2))(param_2);
        FUN_71001308d0(param_2);
    }
}

// 0x7100179540 — virtual dtor: same pattern (48 bytes)
void FUN_7100179540(u64 param_1, u64 *param_2)
{
    if (param_2 != nullptr) {
        (*(void (**)(u64 *))(*param_2))(param_2);
        FUN_71001308d0(param_2);
    }
}

// 0x7100179670 — virtual dtor: same pattern (48 bytes)
void FUN_7100179670(u64 param_1, u64 *param_2)
{
    if (param_2 != nullptr) {
        (*(void (**)(u64 *))(*param_2))(param_2);
        FUN_71001308d0(param_2);
    }
}

// 0x7100179780 — virtual dtor: same pattern (48 bytes)
void FUN_7100179780(u64 param_1, u64 *param_2)
{
    if (param_2 != nullptr) {
        (*(void (**)(u64 *))(*param_2))(param_2);
        FUN_71001308d0(param_2);
    }
}

// 0x7100179810 — virtual dtor: same pattern (48 bytes)
void FUN_7100179810(u64 param_1, u64 *param_2)
{
    if (param_2 != nullptr) {
        (*(void (**)(u64 *))(*param_2))(param_2);
        FUN_71001308d0(param_2);
    }
}

// 0x71001798a0 — virtual dtor: same pattern (48 bytes)
void FUN_71001798a0(u64 param_1, u64 *param_2)
{
    if (param_2 != nullptr) {
        (*(void (**)(u64 *))(*param_2))(param_2);
        FUN_71001308d0(param_2);
    }
}

// 0x71002282c0 — pop front of simple linked list (48 bytes)
void FUN_71002282c0(s64 *param_1)
{
    s64 lVar1 = *param_1;
    *param_1 = *(s64 *)(lVar1 + 8);
    if (lVar1 != param_1[1]) {
        FUN_7100228130();
        return;
    }
    param_1[1] = 0;
    FUN_7100228130();
}

// 0x710022ba90 — init three sub-objects at fixed offsets (48 bytes)
void FUN_710022ba90(s64 param_1)
{
    FUN_71001d6880(param_1 + 0x378);
    FUN_71001cba40(param_1 + 0x2a0);
    FUN_71001ce8e0(param_1 + 8);
}

// 0x710024b140 — init two sub-objects at +0x20 and +0xb0 (48 bytes)
void FUN_710024b140(s64 param_1, u64 param_2)
{
    FUN_710022adb0(param_1 + 0x20);
    FUN_710022adb0(param_1 + 0xb0, param_2);
}

// 0x710015f5c0 — conditional lookup: 3-way guard then indexed access (64 bytes)
u64 FUN_710015f5c0(s64 param_1, u8 param_2)
{
    if ((*(u8 *)(param_1 + 0x38) != 0xfd) &&
        (*(u8 *)(param_1 + 0x38) != param_2) &&
        (param_2 < *(u8 *)(param_1 + 0x60))) {
        return FUN_710015f8a0(*(s64 *)(param_1 + 0x58) + (u64)param_2 * 0x58);
    }
    return 0xffffffff;
}

// 0x71002bad10 — set-then-drain two-step init (48 bytes)
void FUN_71002bad10(u64 param_1, u64 param_2)
{
    FUN_71000319e0(param_1, 0, param_2);
    FUN_71000319d0(param_1);
}

// 0x71002c2fa0 — cleanup: call two finalizers at offsets (48 bytes)
void FUN_71002c2fa0(s64 param_1)
{
    FUN_710003a260(param_1 + 0xd8);
    FUN_710003a120(param_1);
}
