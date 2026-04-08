#include "types.h"

// MEDIUM-tier FUN_* functions — batch d5-052
// Pool-d worker: 0x71039* small functions (jemalloc/pthread/misc, continued)
// FUN_71039518c0 FUN_7103951c20 FUN_7103951fd0 FUN_71039520b0 FUN_71039520e0
// FUN_71039523c0 FUN_7103952a50 FUN_7103952e10 FUN_7103953330 FUN_7103953d00
// FUN_7103953f00 FUN_71039544d0 FUN_7103957230 FUN_7103957260 FUN_7103957690
// FUN_7103957720 FUN_7103957c80 FUN_7103957d20 FUN_7103957dd0 FUN_7103957e40
// FUN_71039585a0 FUN_71039587d0 FUN_710395b750 FUN_710395ba80 FUN_710395bab0
// FUN_710395bc90 FUN_710395bfa0 FUN_710395c410 FUN_710395c5e0 FUN_710395cc50
// FUN_710395cea0 FUN_710395ced0 FUN_710395cf00 FUN_710395d210 FUN_710395d5a0
// FUN_710395d680 FUN_710395d6b0 FUN_710395e0e0 FUN_710395eac0 FUN_710395eaf0
// FUN_710395eda0 FUN_710395f380 FUN_710395f4f0 FUN_710395f560 FUN_710395f950
// FUN_710395fc40 FUN_710395fc90 FUN_710395fcc0

extern "C" {
    int pthread_mutex_unlock(void *mutex);
    int pthread_mutex_trylock(void *mutex);
    int pthread_mutex_lock(void *mutex);
    int ffsl(long i);
    int *__errno_location(void);
}

// ---- External declarations ----

extern u64    FUN_7103951cf0(u64);
extern u8  *  FUN_7103951c50(u64);
extern void   FUN_7103952110(u64);
// FUN_71039520e0 defined below
extern void   FUN_71039533e0(u64);
extern void   FUN_7103953420(void);
extern s64    FUN_71039533b0(u64);
extern s64    FUN_7103952870(u64);
extern void   FUN_7103953360(u64);
extern u64    FUN_7103951470(u64);
extern void   FUN_7103953d40(u64, s64);
extern u32    FUN_71039511d0(u64, int);
extern void   FUN_7103954070(char *, u64);
extern u64    FUN_7103957cc0(u64, u64, int);
extern void   FUN_7103957e00(u64, u64);
extern void   FUN_7103957e70(u64, u64);
extern u64    FUN_7103958650(u64);
extern void   FUN_71039586b0(u64, s64);
extern u64    FUN_710395bba0(u64);
extern void   FUN_710395bc00(u64, s64);
extern u64    FUN_710395bb30(u64);
extern u32 *  FUN_710395bae0(u64);
extern void   FUN_710395c440(u64);
extern void   FUN_710395c620(u64, u64);
extern void   FUN_710395c5b0(u64, u64, u64);
extern void   FUN_710395cc80(u64, int, int);
extern u8  *  FUN_710395d330(u64);
extern u64 *  FUN_710395d2e0(u64);
extern u64 *  FUN_710395d290(u64);
extern u8  *  FUN_710395d240(u64);
extern void   FUN_710395d6e0(u64);
// FUN_710395d6b0 defined below
extern u32    FUN_710395b900(u64, int);
extern u8  *  FUN_710395eb70(u64);
extern u8  *  FUN_710395eb20(u64);
extern void   FUN_710395ee90(u64);
extern void   FUN_7103958840(void);
extern u64 *  FUN_710395ef00(u64);
extern void   FUN_710395c650(u64);
extern u64    FUN_710395f3c0(int);
extern void   FUN_710395f420(u64, s64);
extern void   FUN_710392b3f0(u64);
extern void   FUN_710395f990(void);
extern u64    FUN_710395f730(void);
extern void   FUN_710395ea10(u64);
extern u8  *  FUN_710395eeb0(u64);
extern void   FUN_710395fc70(u64);
// FUN_710395fc90 defined below
// FUN_710395fcc0 defined below
extern void   FUN_710395fcf0(u64, int);

// Forward declarations for functions defined in this file
s32 FUN_71039520e0(s64 param_1);
s32 FUN_710395d6b0(s64 param_1);
void FUN_710395fc90(u64 param_1);
void FUN_710395fcc0(u64 param_1);

// ---- 0x71039* functions ----

// 0x71039518c0 — call + deref u64 (48B)
__attribute__((optnone))
u64 FUN_71039518c0(u64 param_1) {
    u64 *puVar1 = (u64 *)FUN_7103951cf0(param_1);
    return *puVar1;
}

// 0x7103951c20 — call + deref + mask low bit (48B)
u8 FUN_7103951c20(u64 param_1) {
    u8 *pbVar1 = FUN_7103951c50(param_1);
    return *pbVar1 & 1;
}

// 0x7103951fd0 — wrapper (48B)
__attribute__((optnone))
void FUN_7103951fd0(u64 param_1) {
    FUN_7103952110(param_1);
}

// 0x71039520b0 — wrapper (48B)
__attribute__((optnone))
void FUN_71039520b0(u64 param_1) {
    FUN_71039520e0(param_1);
}

// 0x71039520e0 — ffsl wrapper (48B)
__attribute__((optnone))
s32 FUN_71039520e0(s64 param_1) {
    return ffsl(param_1);
}

// 0x71039523c0 — two-call wrapper (48B)
__attribute__((optnone))
void FUN_71039523c0(u64 param_1) {
    FUN_71039533e0(param_1);
    FUN_7103953420();
}

// 0x7103952a50 — sum two calls (64B)
__attribute__((optnone))
s64 FUN_7103952a50(u64 param_1) {
    s64 lVar1 = FUN_71039533b0(param_1);
    s64 lVar2 = FUN_7103952870(param_1);
    return lVar1 + lVar2;
}

// 0x7103952e10 — mask low bit: x & ~1 (64B)
__attribute__((optnone))
u64 FUN_7103952e10(u64 param_1) {
    return param_1 & 0xffffffffffffeULL;
}

// 0x7103953330 — wrapper (48B)
__attribute__((optnone))
void FUN_7103953330(u64 param_1) {
    FUN_7103953360(param_1);
}

// 0x7103953d00 — two-call wrapper (64B)
__attribute__((optnone))
void FUN_7103953d00(u64 param_1, s64 param_2) {
    u64 uVar1 = FUN_7103951470(param_1);
    FUN_7103953d40(uVar1, param_2 + 0x60);
}

// 0x7103953f00 — call with 1 + mask (48B)
__attribute__((optnone))
u32 FUN_7103953f00(u64 param_1) {
    u32 uVar1 = FUN_71039511d0(param_1, 1);
    return uVar1 & 1;
}

// 0x71039544d0 — set errno (48B)
__attribute__((optnone))
void FUN_71039544d0(s32 param_1) {
    *__errno_location() = param_1;
}

// 0x7103957230 — pthread_mutex_trylock (48B)
__attribute__((optnone))
bool FUN_7103957230(s64 param_1) {
    return pthread_mutex_trylock((void *)(param_1 + 0x40)) != 0;
}

// 0x7103957260 — pthread_mutex_lock (48B)
__attribute__((optnone))
s32 FUN_7103957260(s64 param_1) {
    return pthread_mutex_lock((void *)(param_1 + 0x40));
}

// 0x7103957690 — set timespec from sec + nsec (64B)
__attribute__((optnone))
void FUN_7103957690(s64 *param_1, s64 param_2, s64 param_3) {
    *param_1 = param_3 + param_2 * 1000000000;
}

// 0x7103957720 — three-way compare of pointed-to u64 (64B)
__attribute__((optnone))
s32 FUN_7103957720(u64 *param_1, u64 *param_2) {
    return (u32)(*param_2 < *param_1) - (u32)(*param_1 < *param_2);
}

// 0x7103957c80 — call with 1 + mask (64B)
__attribute__((optnone))
u32 FUN_7103957c80(u64 param_1, u64 param_2) {
    u32 uVar1 = FUN_7103957cc0(param_1, param_2, 1);
    return uVar1 & 1;
}

// 0x7103957d20 — call with 0 + mask (64B)
__attribute__((optnone))
u32 FUN_7103957d20(u64 param_1, u64 param_2) {
    u32 uVar1 = FUN_7103957cc0(param_1, param_2, 0);
    return uVar1 & 1;
}

// 0x7103957dd0 — wrapper (48B)
__attribute__((optnone))
void FUN_7103957dd0(u64 param_1, u64 param_2) {
    FUN_7103957e00(param_1, param_2);
}

// 0x7103957e40 — wrapper (48B)
__attribute__((optnone))
void FUN_7103957e40(u64 param_1, u64 param_2) {
    FUN_7103957e70(param_1, param_2);
}

// 0x71039585a0 — call + pthread_mutex_unlock (64B)
__attribute__((optnone))
s32 FUN_71039585a0(u64 param_1, s64 param_2) {
    u64 uVar2 = FUN_7103958650(param_1);
    FUN_71039586b0(uVar2, param_2 + 0x60);
    return pthread_mutex_unlock((void *)(param_2 + 0x40));
}

// 0x71039587d0 — pthread_mutex_trylock (48B)
__attribute__((optnone))
bool FUN_71039587d0(s64 param_1) {
    return pthread_mutex_trylock((void *)(param_1 + 0x40)) != 0;
}

// 0x710395b750 — call + pthread_mutex_unlock (64B)
__attribute__((optnone))
s32 FUN_710395b750(u64 param_1, s64 param_2) {
    u64 uVar2 = FUN_710395bba0(param_1);
    FUN_710395bc00(uVar2, param_2 + 0x60);
    return pthread_mutex_unlock((void *)(param_2 + 0x40));
}

// 0x710395ba80 — call + deref u64 (48B)
__attribute__((optnone))
u64 FUN_710395ba80(u64 param_1) {
    u64 *puVar1 = (u64 *)FUN_710395bb30(param_1);
    return *puVar1;
}

// 0x710395bab0 — call + deref u32 (48B)
__attribute__((optnone))
u32 FUN_710395bab0(u64 param_1) {
    u32 *puVar1 = FUN_710395bae0(param_1);
    return *puVar1;
}

// 0x710395bc90 — pthread_mutex_trylock (48B)
__attribute__((optnone))
bool FUN_710395bc90(s64 param_1) {
    return pthread_mutex_trylock((void *)(param_1 + 0x40)) != 0;
}

// 0x710395bfa0 — mask low bit: x & ~1 (64B)
__attribute__((optnone))
u64 FUN_710395bfa0(u64 param_1) {
    return param_1 & 0xffffffffffffeULL;
}

// 0x710395c410 — wrapper (48B)
__attribute__((optnone))
void FUN_710395c410(u64 param_1) {
    FUN_710395c440(param_1);
}

// 0x710395c5e0 — two-call wrapper (64B)
__attribute__((optnone))
void FUN_710395c5e0(u64 param_1, u64 param_2, u64 param_3) {
    FUN_710395c620(param_1, param_2);
    FUN_710395c5b0(param_1, param_2, param_3);
}

// 0x710395cc50 — call with zeros (48B)
__attribute__((optnone))
void FUN_710395cc50(u64 param_1) {
    FUN_710395cc80(param_1, 0, 0);
}

// 0x710395cea0 — call + deref byte (48B)
u8 FUN_710395cea0(u64 param_1) {
    u8 *puVar1 = FUN_710395d330(param_1);
    return *puVar1;
}

// 0x710395ced0 — call + deref u64 (48B)
__attribute__((optnone))
u64 FUN_710395ced0(u64 param_1) {
    u64 *puVar1 = (u64 *)FUN_710395d2e0(param_1);
    return *puVar1;
}

// 0x710395cf00 — call + deref u64 (48B)
__attribute__((optnone))
u64 FUN_710395cf00(u64 param_1) {
    u64 *puVar1 = (u64 *)FUN_710395d290(param_1);
    return *puVar1;
}

// 0x710395d210 — call + deref + mask low bit (48B)
u8 FUN_710395d210(u64 param_1) {
    u8 *pbVar1 = FUN_710395d240(param_1);
    return *pbVar1 & 1;
}

// 0x710395d5a0 — wrapper (48B)
__attribute__((optnone))
void FUN_710395d5a0(u64 param_1) {
    FUN_710395d6e0(param_1);
}

// 0x710395d680 — wrapper (48B)
__attribute__((optnone))
void FUN_710395d680(u64 param_1) {
    FUN_710395d6b0(param_1);
}

// 0x710395d6b0 — ffsl wrapper (48B)
__attribute__((optnone))
s32 FUN_710395d6b0(s64 param_1) {
    return ffsl(param_1);
}

// 0x710395e0e0 — call with 1 + mask (48B)
__attribute__((optnone))
u32 FUN_710395e0e0(u64 param_1) {
    u32 uVar1 = FUN_710395b900(param_1, 1);
    return uVar1 & 1;
}

// 0x710395eac0 — call + deref + mask low bit (48B)
u8 FUN_710395eac0(u64 param_1) {
    u8 *pbVar1 = FUN_710395eb70(param_1);
    return *pbVar1 & 1;
}

// 0x710395eaf0 — call + deref byte (48B)
u8 FUN_710395eaf0(u64 param_1) {
    u8 *puVar1 = FUN_710395eb20(param_1);
    return *puVar1;
}

// 0x710395eda0 — init sequence (64B)
__attribute__((optnone))
void FUN_710395eda0(u64 param_1) {
    FUN_710395ee90(param_1);
    FUN_7103958840();
    u64 *puVar1 = FUN_710395ef00(param_1);
    *puVar1 = param_1;
    FUN_710395c650(param_1);
}

// 0x710395f380 — call(0) + pthread_mutex_unlock (64B)
__attribute__((optnone))
s32 FUN_710395f380(s64 param_1) {
    u64 uVar2 = FUN_710395f3c0(0);
    FUN_710395f420(uVar2, param_1 + 0x60);
    return pthread_mutex_unlock((void *)(param_1 + 0x40));
}

// 0x710395f4f0 — pthread_mutex_trylock (48B)
__attribute__((optnone))
bool FUN_710395f4f0(s64 param_1) {
    return pthread_mutex_trylock((void *)(param_1 + 0x40)) != 0;
}

// 0x710395f560 — wrapper (48B)
__attribute__((optnone))
void FUN_710395f560(u64 param_1) {
    FUN_710392b3f0(param_1);
}

// 0x710395f950 — 4-call sequence (64B)
__attribute__((optnone))
void FUN_710395f950(void) {
    FUN_710395f990();
    u64 uVar1 = FUN_710395f730();
    FUN_710395ea10(uVar1);
    u8 *puVar2 = FUN_710395eeb0(uVar1);
    *puVar2 = 0;
}

// FUN_710395fc40 skipped — inconsistent arity in callee

// 0x710395fc90 — wrapper (48B)
__attribute__((optnone))
void FUN_710395fc90(u64 param_1) {
    FUN_710395fcc0(param_1);
}

// 0x710395fcc0 — call with 0 (48B)
__attribute__((optnone))
void FUN_710395fcc0(u64 param_1) {
    FUN_710395fcf0(param_1, 0);
}
