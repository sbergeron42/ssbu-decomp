#include "types.h"

// MEDIUM-tier FUN_* functions — batch d5-053
// Pool-d worker: 0x71037*-0x71038* remaining + misc
// FUN_7103761150 FUN_7103762160 FUN_71037621b0 FUN_71037cc620 FUN_71037cc670
// FUN_71038357a0 FUN_71038cebd0 FUN_71039293e0 FUN_710392f460 FUN_710392f710
// FUN_710392f7f0 FUN_7103930530 FUN_71039320f0 FUN_71039359a0 FUN_710393e720
// FUN_710393f250 FUN_7103950f90 FUN_7103951050 FUN_7103951350 FUN_7103951380
// FUN_7103951560 FUN_71039517e0

extern "C" {
    __attribute__((noreturn)) void abort(void);
    int pthread_mutex_unlock(void *mutex);
    int pthread_mutex_trylock(void *mutex);
}

// ---- External declarations ----

// 0x71037* externals
extern void FUN_710007db70(void);
extern void FUN_710007db80(void);
extern void jeFree_710392e590(void *);
extern void FUN_71037aeed0(float, float, void *);
extern void FUN_71037aedd0(void *, void *);
extern void FUN_71037aec40(u64, u64);
extern void noop_71037aeec0(u64);

// Semaphore
namespace nn { namespace os {
    void FinalizeSemaphore(void *sem);
} }
extern void jeFree_710392e590_v(void *);

// 0x71038 externals
extern void   FUN_710381cc80(u32);
extern void   FUN_710356bb20(void);
extern void   FUN_71038344a0(void);
extern void   FUN_7103834b10(int);
extern void   FUN_71035f33d0(int);
extern void   FUN_710388e230(void);
extern void   FUN_71038cef60(void);

// 0x71039 externals
extern u64    FUN_7103927b30(u64);
extern void   FUN_7103929450(u64, s64);
extern int    pthread_mutex_unlock_v(void *);
extern u64    FUN_710392eec0(u64);
extern void   FUN_710392fe90(u64, s64);
extern void   FUN_710392fde0(u64, s64);
extern void   FUN_710392fe00(u64, s64);
extern s32    FUN_7103957720(u64 *, u64 *);
extern s32    FUN_7103957260(s64);
extern void   FUN_7103930570(s64, int);
extern s64    FUN_710393cfe0(u64);
extern s64    FUN_710393ca80(u64);
extern void   FUN_710393f340(void *, void *);
extern u64    FUN_7103951470(u64);
extern void   FUN_7103951540(u64, s64);
extern void   FUN_71039514d0(u64, s64);
extern u64 *  FUN_7103951400(u64);
extern u32 *  FUN_71039513b0(u64);
extern u8  *  FUN_7103951db0(u64);
extern u64 *  FUN_7103951cf0(u64);
extern u8  *  FUN_7103951c50(u64);

// External for semaphore type (PTR refs skipped, just fwd)
extern void *PTR_FUN_7105241098;

// ---- 0x71037* ----

// 0x7103761150 — abort wrapper (240B in binary but just abort)
void FUN_7103761150(void) {
    abort();
}

// 0x7103762160 — copy fields from a struct (80B)
void FUN_7103762160(s64 param_1, u64 *param_2) {
    FUN_710007db70();
    *(u8 *)(param_1 + 0x5c) = 0;
    u32 *puVar2 = (u32 *)*param_2;
    puVar2[0]  = *(u32 *)(param_1 + 0x44);
    puVar2[1]  = *(u32 *)(param_1 + 0x44);
    *(u8 *)((u8 *)puVar2 + 0x39) = *(u8 *)(param_1 + 0x4d);
    puVar2[3]  = *(u32 *)(param_1 + 0x50);
    puVar2[4]  = *(u32 *)(param_1 + 0x54);
}

// 0x71037621b0 — conditional copy from external struct (80B)
void FUN_71037621b0(s64 param_1, s64 *param_2) {
    FUN_710007db80();
    if (*(u8 *)(param_1 + 0x5c) == '\0') {
        s64 lVar1 = *param_2;
        *(u32 *)(param_1 + 0x40) = *(u32 *)(lVar1 + 0x18);
        *(u32 *)(param_1 + 0x50) = *(u32 *)(lVar1 + 0xc);
        *(u32 *)(param_1 + 0x54) = *(u32 *)(lVar1 + 0x10);
    }
}

// 0x71037cc620 — finalize semaphore and zero the pointer (80B)
void FUN_71037cc620(u64 *param_1) {
    void *pSVar1 = (void *)param_1[1];
    param_1[0] = (u64)&PTR_FUN_7105241098;
    if (pSVar1 != (void *)0) {
        nn::os::FinalizeSemaphore(pSVar1);
        jeFree_710392e590(pSVar1);
        param_1[1] = 0;
    }
}

// 0x71037cc670 — finalize semaphore + free self (80B)
void FUN_71037cc670(u64 *param_1) {
    void *pSVar1 = (void *)param_1[1];
    param_1[0] = (u64)&PTR_FUN_7105241098;
    if (pSVar1 != (void *)0) {
        nn::os::FinalizeSemaphore(pSVar1);
        jeFree_710392e590(pSVar1);
        param_1[1] = 0;
    }
    jeFree_710392e590(param_1);
}

// ---- 0x71038* ----

// 0x71038357a0 — switch: copy values or abort (112B)
void FUN_71038357a0(u32 param_1, s64 *param_2, u64 *param_3) {
    switch (param_1) {
    case 0:
    case 1: {
        FUN_710381cc80(*(u32 *)*param_2 ^ (u32)((s32)*(u32 *)*param_2 >> 0x1f));
        s64 lVar2 = *param_2;
        u64 uVar1 = *param_3;
        *(u64 *)(lVar2 + 0xc) = param_3[1];
        *(u64 *)(lVar2 + 4)   = uVar1;
        *(u32 *)*param_2      = (u32)param_2[1];
        return;
    }
    default:
        FUN_710356bb20();
    }
}

// 0x71038cebd0 — switch/vtable call (128B)
void FUN_71038cebd0(u32 param_1, u64 *param_2) {
    switch (param_1) {
    case 0:
    case 1:
        (*reinterpret_cast<void(**)(u64 *)>(*param_2))(param_2);
        return;
    default:
        FUN_710356bb20();
    }
}

// ---- 0x71039* remaining ----

// 0x71039293e0 — call + mutex_unlock (64B)
__attribute__((optnone))
s32 FUN_71039293e0(u64 param_1, s64 param_2) {
    u64 uVar2 = FUN_7103927b30(param_1);
    FUN_7103929450(uVar2, param_2 + 0x60);
    return pthread_mutex_unlock((void *)(param_2 + 0x40));
}

// 0x710392f460 — call + mutex_unlock (64B)
__attribute__((optnone))
s32 FUN_710392f460(u64 param_1, s64 param_2) {
    u64 uVar2 = FUN_710392eec0(param_1);
    FUN_710392fe90(uVar2, param_2 + 0x60);
    return pthread_mutex_unlock((void *)(param_2 + 0x40));
}

// 0x710392f710 — two-call wrapper (64B)
__attribute__((optnone))
void FUN_710392f710(u64 param_1, s64 param_2) {
    u64 uVar1 = FUN_710392eec0(param_1);
    FUN_710392fde0(uVar1, param_2 + 0x60);
}

// 0x710392f7f0 — call, return result < 1 (64B)
__attribute__((optnone))
bool FUN_710392f7f0(s64 param_1, u64 param_2) {
    s32 iVar1 = FUN_7103957720((u64 *)(param_1 + 0xc0), (u64 *)param_2);
    return iVar1 < 1;
}

// 0x7103930530 — pass offset to sub-call (64B)
__attribute__((optnone))
void FUN_7103930530(s64 param_1, u64 param_2) {
    FUN_7103930570((s64)(0x1a30 + param_1), param_2);
}

// 0x71039320f0 — two-call wrapper (64B)
__attribute__((optnone))
void FUN_71039320f0(u64 param_1, s64 param_2) {
    u64 uVar1 = FUN_710392eec0(param_1);
    FUN_710392fe00(uVar1, param_2 + 0x60);
}

// 0x71039359a0 — pass offset to sub-call (48B)
__attribute__((optnone))
void FUN_71039359a0(s64 param_1) {
    FUN_7103930570((s64)(0x1a20 + param_1), 1);
}

// 0x710393e720 — sum two calls (64B)
__attribute__((optnone))
s64 FUN_710393e720(u64 param_1) {
    s64 lVar1 = FUN_710393cfe0(param_1);
    s64 lVar2 = FUN_710393ca80(param_1);
    return lVar1 + lVar2;
}

// 0x710393f250 — call + index stride 0x98 (64B)
__attribute__((optnone))
s64 FUN_710393f250(s64 param_1, u64 param_2) {
    u8 local_30[16];
    u64 local_20 = param_2;
    s64 local_18 = param_1;
    FUN_710393f340(&local_20, local_30);
    return local_18 + (u64)local_30[0] * 0x98;
}

// 0x7103950f90 — call + mutex_unlock (64B)
__attribute__((optnone))
s32 FUN_7103950f90(u64 param_1, s64 param_2) {
    u64 uVar2 = FUN_7103951470(param_1);
    FUN_7103951540(uVar2, param_2 + 0x60);
    return pthread_mutex_unlock((void *)(param_2 + 0x40));
}

// 0x7103951050 — two-call wrapper (64B)
__attribute__((optnone))
void FUN_7103951050(u64 param_1, s64 param_2) {
    u64 uVar1 = FUN_7103951470(param_1);
    FUN_71039514d0(uVar1, param_2 + 0x60);
}

// 0x7103951350 — call + deref u64 (48B)
__attribute__((optnone))
u64 FUN_7103951350(u64 param_1) {
    u64 *puVar1 = FUN_7103951400(param_1);
    return *puVar1;
}

// 0x7103951380 — call + deref u32 (48B)
__attribute__((optnone))
u32 FUN_7103951380(u64 param_1) {
    u32 *puVar1 = FUN_71039513b0(param_1);
    return *puVar1;
}

// 0x7103951560 — pthread_mutex_trylock (48B)
__attribute__((optnone))
bool FUN_7103951560(s64 param_1) {
    return pthread_mutex_trylock((void *)(param_1 + 0x40)) != 0;
}

// 0x71039517e0 — call + deref byte (48B)
u8 FUN_71039517e0(u64 param_1) {
    u8 *puVar1 = FUN_7103951db0(param_1);
    return *puVar1;
}
