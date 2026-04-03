#include "types.h"

// MEDIUM-tier FUN_* functions — batch d5-054
// Pool-d worker: 0x71039* medium-size functions (jemalloc/arena, 80-256B)
// FUN_7103929a70 FUN_710392ba00 FUN_710392bbe0 FUN_710392bc30 FUN_710392ea70
// FUN_7103930920 FUN_7103931640 FUN_71039327d0 FUN_7103932820 FUN_7103934650
// FUN_7103934870 FUN_7103936c20 FUN_71039394e0 FUN_7103939530 FUN_71039401e0
// FUN_71039409d0 FUN_7103943b50 FUN_71039458b0 FUN_7103946f70 FUN_7103952dc0
// FUN_7103953a60 FUN_7103953e20 FUN_7103953f60 FUN_7103953fb0 FUN_7103958760
// FUN_710395a6a0 FUN_710395b640 FUN_710395bf00 FUN_710395bf50 FUN_710395f590

extern "C" {
    __attribute__((noreturn)) void abort(void);
    int pthread_mutex_unlock(void *mutex);
}

// ---- External declarations ----

extern void   FUN_71039292b0(int, void *);
extern u8     FUN_7103929ac0(void);
extern s32    FUN_71039293e0(u64, s64);
extern void   FUN_710392ba50(u64, void *);
extern void   FUN_710392bab0(u64, u64, u64);
extern void   FUN_710392bc80(u64);
extern void   FUN_710392c0f0(u64);
extern void   FUN_7103929830(u64, u32);
extern u64    FUN_7103930160(u64);
extern void   FUN_7103930970(u64, u64);
extern void   FUN_71039316d0(u64, u32);
extern u64    FUN_7103932890(u64);
extern u64    FUN_7103932870(u64);
extern void   FUN_7103934770(u64, void *);
extern void   FUN_71039347d0(u64, u64, u64);
extern void   FUN_71039348c0(u64);
extern u64    FUN_7103936cb0(u64);
extern u64    FUN_71039395a0(u64);
extern u64    FUN_7103939580(u64);
extern void   FUN_710393ede0(u64, u64);
extern void   FUN_710393dc80(u64, u32);
extern u32    FUN_710393ea90(u64, u64, u64, u64, u64, int);
extern void   FUN_7103945810(s64);
extern void   FUN_7103944130(s64, u64, int);
extern u64    FUN_7103946fc0(u64);
extern void   FUN_7103947020(u64, void *);
extern void   FUN_7103951d40(u64, u32);
extern void   FUN_7103952a90(u64, void *);
extern void   FUN_7103953d80(u64, u64, u64);
extern void   FUN_7103952e10(u64);
extern u64    FUN_71039526e0(u64);
extern void   FUN_7103953b10(u64, u64, u64, int);
extern void   FUN_7103953c10(u64, u64, u64);
extern u64    FUN_7103943c00(void);
extern void   FUN_7103945900(u64, u64, u64, u64);
extern void   FUN_710395a780(u64, u64, u64, u32, u64, int, int, int);
extern void   FUN_710395bd70(u64, void *);
extern void   FUN_710395bdd0(u64, u64, u64);
extern void   FUN_710395bfa0(u64);
extern void   FUN_710395bd00(u64, u32);
extern void   FUN_710395ee40(u8 *);
extern void   FUN_710395ed30(u8 *);

extern void *DAT_7106dd3f80;
extern void *DAT_7106dd3f60;

// Forward declarations (defined later in this file or externally called)
void FUN_710392bc30(u64 param_1, u64 param_2, u64 param_3, u8 param_4);
void FUN_710395bf50(u64 param_1, u64 param_2, u64 param_3, u8 param_4);
extern void FUN_710395f620(u8 *param_1);

// ---- 0x71039* medium functions ----

// 0x7103929a70 — init mutex + call + unlock (80B)
u8 FUN_7103929a70(void) {
    FUN_71039292b0(0, &DAT_7106dd3f80);
    u8 bVar1 = FUN_7103929ac0();
    FUN_71039293e0(0, (s64)&DAT_7106dd3f80);
    return bVar1 & 1;
}

// 0x710392ba00 — stack-alloc call + second call (80B)
void FUN_710392ba00(u64 param_1, u64 param_2) {
    u8 auStack_1a8[384];
    u64 local_28 = param_2;
    u64 uVar1;
    FUN_710392ba50(param_1, auStack_1a8);
    uVar1 = *(u64 *)auStack_1a8;  // just read result slot
    FUN_710392bab0(param_1, uVar1, local_28);
}

// 0x710392bbe0 — call bc30 + mask (80B)
void FUN_710392bbe0(u64 param_1, u64 param_2, u64 param_3, u8 param_4) {
    u64 uVar1;
    FUN_710392bc30(param_1, param_2, param_3, param_4 & 1);
    uVar1 = *(u64 *)&param_3; // placeholder — compiler will optimize
    FUN_710392bc80(uVar1);
}

// 0x710392bc30 — conditional set mode param (80B)
void FUN_710392bc30(u64 param_1, u64 param_2, u64 param_3, u8 param_4) {
    u32 uVar1 = 0;
    if ((param_4 & 1) == 0) {
        uVar1 = 2;
    }
    FUN_7103929830(param_3, uVar1);
}

// 0x710392ea70 — call bc30 + c0f0 (80B)
void FUN_710392ea70(u64 param_1, u64 param_2, u64 param_3, u8 param_4) {
    u64 uVar1;
    FUN_710392bc30(param_1, param_2, param_3, param_4 & 1);
    uVar1 = *(u64 *)&param_3;
    FUN_710392c0f0(uVar1);
}

// 0x7103930920 — shift/pass sub-result (80B)
void FUN_7103930920(u64 param_1, u64 param_2, u64 param_3) {
    u64 uVar1 = FUN_7103930160(param_3);
    FUN_7103930970(param_2, uVar1 >> 0x10);
}

// 0x7103931640 — conditional set mode param (80B)
void FUN_7103931640(u64 param_1, u64 param_2, u64 param_3, u8 param_4) {
    u32 uVar1 = 0;
    if ((param_4 & 1) == 0) {
        uVar1 = 2;
    }
    FUN_71039316d0(param_3, uVar1);
}

// 0x71039327d0 — three-way compare via two sub-calls (80B)
s32 FUN_71039327d0(u64 param_1, u64 param_2) {
    u64 uVar1 = FUN_7103932890(param_1);
    u64 uVar2 = FUN_7103932890(param_2);
    return (u32)(uVar2 < uVar1) - (u32)(uVar1 < uVar2);
}

// 0x7103932820 — three-way compare via two sub-calls (80B)
s32 FUN_7103932820(u64 param_1, u64 param_2) {
    u64 uVar1 = FUN_7103932870(param_1);
    u64 uVar2 = FUN_7103932870(param_2);
    return (u32)(uVar2 < uVar1) - (u32)(uVar1 < uVar2);
}

// 0x7103934650 — stack-alloc call + second call (80B)
void FUN_7103934650(u64 param_1, u64 param_2) {
    u8 auStack_1a8[384];
    u64 local_28 = param_2;
    u64 uVar1;
    FUN_7103934770(param_1, auStack_1a8);
    uVar1 = *(u64 *)auStack_1a8;
    FUN_71039347d0(param_1, uVar1, local_28);
}

// 0x7103934870 — call 1640 + mask (80B)
void FUN_7103934870(u64 param_1, u64 param_2, u64 param_3, u8 param_4) {
    FUN_7103931640(param_1, param_2, param_3, param_4 & 1);
    FUN_71039348c0(param_3);
}

// 0x7103936c20 — three-way compare via two sub-calls (80B)
s32 FUN_7103936c20(u64 param_1, u64 param_2) {
    u64 uVar1 = FUN_7103936cb0(param_1);
    u64 uVar2 = FUN_7103936cb0(param_2);
    return (u32)(uVar2 < uVar1) - (u32)(uVar1 < uVar2);
}

// 0x71039394e0 — three-way compare via two sub-calls (80B)
s32 FUN_71039394e0(u64 param_1, u64 param_2) {
    u64 uVar1 = FUN_71039395a0(param_1);
    u64 uVar2 = FUN_71039395a0(param_2);
    return (u32)(uVar2 < uVar1) - (u32)(uVar1 < uVar2);
}

// 0x7103939530 — three-way compare via two sub-calls (80B)
s32 FUN_7103939530(u64 param_1, u64 param_2) {
    u64 uVar1 = FUN_7103939580(param_1);
    u64 uVar2 = FUN_7103939580(param_2);
    return (u32)(uVar2 < uVar1) - (u32)(uVar1 < uVar2);
}

// 0x71039401e0 — call two params, return 0 (80B)
u64 FUN_71039401e0(u64 param_1, u64 param_2, u64 param_3, u64 param_4) {
    FUN_710393ede0(param_2, param_4);
    return 0;
}

// 0x71039409d0 — conditional set mode param (80B)
void FUN_71039409d0(u64 param_1, u64 param_2, u64 param_3, u8 param_4) {
    u32 uVar1 = 0;
    if ((param_4 & 1) == 0) {
        uVar1 = 2;
    }
    FUN_710393dc80(param_3, uVar1);
}

// 0x7103943b50 — call with 6 args adding 0 (80B)
u32 FUN_7103943b50(u64 param_1, u64 param_2, u64 param_3, u64 param_4, u64 param_5) {
    u32 uVar1 = FUN_710393ea90(param_1, param_2, param_3, param_4, param_5, 0);
    return uVar1 & 1;
}

// 0x71039458b0 — call + set flags (80B)
u64 FUN_71039458b0(s64 param_1, u64 param_2) {
    FUN_7103945810(param_1);
    FUN_7103944130(param_1 + 8, param_2, 3);
    return 0; // placeholder for return
}

// 0x7103946f70 — call + mutex_unlock on globals (80B)
s32 FUN_7103946f70(u64 param_1) {
    u64 uVar2 = FUN_7103946fc0(param_1);
    FUN_7103947020(uVar2, &DAT_7106dd3f80);
    return pthread_mutex_unlock((void *)&DAT_7106dd3f60);
}

// 0x7103952dc0 — conditional set mode param (80B)
void FUN_7103952dc0(u64 param_1, u64 param_2, u64 param_3, u8 param_4) {
    u32 uVar1 = 0;
    if ((param_4 & 1) == 0) {
        uVar1 = 2;
    }
    FUN_7103951d40(param_3, uVar1);
}

// 0x7103953a60 — stack-alloc call + second call (80B)
void FUN_7103953a60(u64 param_1, u64 param_2) {
    u8 auStack_1a8[384];
    u64 local_28 = param_2;
    u64 uVar1;
    FUN_7103952a90(param_1, auStack_1a8);
    uVar1 = *(u64 *)auStack_1a8;
    FUN_7103953d80(param_1, uVar1, local_28);
}

// 0x7103953e20 — call 52dc + mask (80B)
void FUN_7103953e20(u64 param_1, u64 param_2, u64 param_3, u8 param_4) {
    FUN_7103952dc0(param_1, param_2, param_3, param_4 & 1);
    FUN_7103952e10(param_3);
}

// 0x7103953f60 — two-call with sub-result (80B)
void FUN_7103953f60(u64 param_1, u64 param_2) {
    u64 uVar1 = FUN_71039526e0(param_2);
    FUN_7103953b10(param_1, uVar1, param_2, 1);
}

// 0x7103953fb0 — two-call with sub-result (80B)
void FUN_7103953fb0(u64 param_1, u64 param_2) {
    u64 uVar1 = FUN_71039526e0(param_2);
    FUN_7103953c10(param_1, uVar1, param_2);
}

// 0x7103958760 — call 3c00 + pass shifted (80B)
void FUN_7103958760(u64 param_1, u64 param_2, s64 param_3) {
    u64 uVar1 = FUN_7103943c00();
    FUN_7103945900(param_1, uVar1, (u64)(param_3 << 3), 0x40);
}

// 0x710395a6a0 — 5-arg wrapper adding 0,0,0 (80B)
void FUN_710395a6a0(u64 param_1, u64 param_2, u64 param_3, u32 param_4, u64 param_5) {
    FUN_710395a780(param_1, param_2, param_3, param_4, param_5, 0, 0, 0);
}

// 0x710395b640 — stack-alloc call + second call (80B)
void FUN_710395b640(u64 param_1, u64 param_2) {
    u8 auStack_1a8[384];
    u64 local_28 = param_2;
    u64 uVar1;
    FUN_710395bd70(param_1, auStack_1a8);
    uVar1 = *(u64 *)auStack_1a8;
    FUN_710395bdd0(param_1, uVar1, local_28);
}

// 0x710395bf00 — call bf50 + mask (80B)
void FUN_710395bf00(u64 param_1, u64 param_2, u64 param_3, u8 param_4) {
    FUN_710395bf50(param_1, param_2, param_3, param_4 & 1);
    FUN_710395bfa0(param_3);
}

// 0x710395bf50 — conditional set mode param (80B)
void FUN_710395bf50(u64 param_1, u64 param_2, u64 param_3, u8 param_4) {
    u32 uVar1 = 0;
    if ((param_4 & 1) == 0) {
        uVar1 = 2;
    }
    FUN_710395bd00(param_3, uVar1);
}

// 0x710395f590 — state machine with switch (144B)
void FUN_710395f590(u8 *param_1) {
    switch (*param_1) {
    case 2:
    case 4:
        FUN_710395ee40(param_1);
        // fallthrough
    case 0:
    case 1:
        FUN_710395f620(param_1);
        *param_1 = 3;
        FUN_710395ed30(param_1);
        break;
    case 3:
        break;
    case 5:
        break;
    default:
        abort();
    }
}

