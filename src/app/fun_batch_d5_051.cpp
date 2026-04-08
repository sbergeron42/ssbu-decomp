#include "types.h"

// MEDIUM-tier FUN_* functions — batch d5-051
// Pool-d worker: 0x71039* small functions (jemalloc/arena internals, pthread wrappers)
// FUN_710392bc80 FUN_710392fd70 FUN_7103933680 FUN_7103933ed0 FUN_71039340a0
// FUN_7103934360 FUN_71039348c0 FUN_7103935720 FUN_7103935860 FUN_7103936c70
// FUN_7103938830 FUN_71039389a0 FUN_710393c200 FUN_710393d820 FUN_710393dcf0
// FUN_710393dd50 FUN_710393dd80 FUN_710393f300 FUN_710393fa40 FUN_7103940230
// FUN_7103940260 FUN_7103940a20 FUN_7103940f40 FUN_7103940f70 FUN_7103942300
// FUN_7103942b40 FUN_7103943300 FUN_7103944630 FUN_7103944710 FUN_7103944740
// FUN_7103945370 FUN_71039455e0 FUN_71039456e0 FUN_7103945900 FUN_7103945f80
// FUN_7103949930 FUN_7103950e20

extern "C" {
    int  pthread_mutex_unlock(void *mutex);
    int  pthread_mutex_trylock(void *mutex);
    int  ffsl(long i);
}

// ---- External declarations ----

extern u8 *   FUN_71039336b0(u64);
extern u32    FUN_7103932240(u64, int);
extern void   FUN_71039340e0(u64, u64, u64, u64, int);
extern void   FUN_710393a6f0(s64, u64);
extern void   FUN_7103935760(s64);
extern void   FUN_71039358a0(s64);
extern void   FUN_7103938870(u64);
extern void   FUN_7103938980(u64, s64);
extern void   FUN_710388d5b0(u64);
extern void   FUN_71039388d0(u64, s64);
extern void   FUN_710393c230(s64);
// FUN_710393dd80 is defined below (ffsl wrapper)
extern void   FUN_7103938980_2(u64, s64);
extern void   FUN_7103930570(s64, int);
extern void   FUN_710393f340(void *, void *);
extern void   FUN_7103938980_3(u64, s64);
extern u64    FUN_7103927b30(u64);
extern void   FUN_7103938980_fn(u64, s64);
extern u64    FUN_710392eec0(u64);
extern void   FUN_710392fde0(u64, s64);
extern void   FUN_710392fe00(u64, s64);
extern void   FUN_710392fe90(u64, s64);
extern s64    FUN_710393cfe0(u64);
extern s64    FUN_710393ca80(u64);
extern void   FUN_7103957c40(u64, u64);
extern u32    FUN_7103945dc0(u64, u64);
extern void   FUN_7103941330(u64, u64, int);
extern void   FUN_7103942330(u64);
extern u32    FUN_7103942b80(u64, u64, int);
extern void   FUN_7103944770(u64);
// FUN_7103944740 is defined below (ffsl wrapper)
extern u64    FUN_7103945510(u64);
extern void   FUN_7103945570(u64, s64);
extern void   FUN_71039456a0(u64, s64);
extern void   FUN_7103945940(u64, u64, u64, u64, int);
extern s64    FUN_7103945fb0(u64);
extern void   FUN_71039515d0(u64, u64);
extern u64    FUN_7103938870_2(u64);

// Forward declarations for functions defined later in this file
s32 FUN_710393dd80(s64 param_1);
s32 FUN_7103944740(s64 param_1);

// ---- 0x71039* small utility functions ----
// NOTE: jemalloc functions were compiled at -O0 in the original binary
#define _O0 __attribute__((optnone))

// 0x710392bc80 — mask low bit: x & ~1 (64B)
_O0 u64 FUN_710392bc80(u64 param_1) {
    return param_1 & 0xffffffffffffeULL;
}

// 0x710392fd70 — splitmix64 LCG step (64B)
_O0 s64 FUN_710392fd70(s64 param_1) {
    return param_1 * 0x5851f42d4c957f2dLL + 0x14057b7ef767814fLL;
}

// 0x7103933680 — get low bit of byte from sub-call (48B)
_O0 u8 FUN_7103933680(u64 param_1) {
    u8 *flags = FUN_71039336b0(param_1);
    return *flags & 1;
}

// 0x7103933ed0 — call with flag=1, return low bit (48B)
_O0 u32 FUN_7103933ed0(u64 param_1) {
    u32 result = FUN_7103932240(param_1, 1);
    return result & 1;
}

// 0x71039340a0 — four-arg wrapper adding extra arg 1 (64B)
_O0 void FUN_71039340a0(u64 param_1, u64 param_2, u64 param_3, u64 param_4) {
    FUN_71039340e0(param_1, param_2, param_3, param_4, 1);
}

// 0x7103934360 — pass param_1+0xa0 to sub-call (48B)
_O0 void FUN_7103934360(s64 param_1, u64 param_2) {
    FUN_710393a6f0(param_1 + 0xa0, param_2);
}

// 0x71039348c0 — mask low bit: x & ~1 (64B)
_O0 u64 FUN_71039348c0(u64 param_1) {
    return param_1 & 0xffffffffffffeULL;
}

// 0x7103935720 — dispatch to offset depending on low bit (64B)
_O0 void FUN_7103935720(s64 param_1, u8 param_2) {
    FUN_7103935760(param_1 + (u64)(param_2 & 1) * 4);
}

// 0x7103935860 — dispatch to offset depending on low bit (64B)
_O0 void FUN_7103935860(s64 param_1, u8 param_2) {
    FUN_71039358a0(param_1 + (u64)(param_2 & 1) * 4);
}

// 0x7103936c70 — three-way compare (64B)
_O0 s32 FUN_7103936c70(u64 param_1, u64 param_2) {
    return (u32)(param_2 < param_1) - (u32)(param_1 < param_2);
}

// 0x7103938830 — call + pthread_mutex_unlock (64B)
_O0 s32 FUN_7103938830(u64 param_1, s64 param_2) {
    FUN_71039388d0(FUN_7103938870_2(param_1), param_2 + 0x60);
    return pthread_mutex_unlock((void *)(param_2 + 0x40));
}

// 0x71039389a0 — pthread_mutex_trylock wrapper (48B)
_O0 bool FUN_71039389a0(s64 param_1) {
    return pthread_mutex_trylock((void *)(param_1 + 0x40)) != 0;
}

// 0x710393c200 — pass param_1+0x688 to sub-call (48B)
_O0 void FUN_710393c200(s64 param_1) {
    FUN_710393c230(param_1 + 0x688);
}

// 0x710393d820 — splitmix64 LCG step (64B)
_O0 s64 FUN_710393d820(s64 param_1) {
    return param_1 * 0x5851f42d4c957f2dLL + 0x14057b7ef767814fLL;
}

// 0x710393dcf0 — splitmix64 LCG step (64B)
_O0 s64 FUN_710393dcf0(s64 param_1) {
    return param_1 * 0x5851f42d4c957f2dLL + 0x14057b7ef767814fLL;
}

// 0x710393dd50 — wrapper (48B)
_O0 void FUN_710393dd50(u64 param_1) {
    FUN_710393dd80(param_1);
}

// 0x710393dd80 — ffsl wrapper (48B)
_O0 s32 FUN_710393dd80(s64 param_1) {
    return ffsl(param_1);
}

// 0x710393f300 — call + store at +0x60 (64B)
_O0 void FUN_710393f300(u64 param_1, s64 param_2) {
    FUN_7103938980(FUN_7103938870_2(param_1), param_2 + 0x60);
}

// 0x710393fa40 — sum two calls minus 0x10000 (64B)
_O0 s64 FUN_710393fa40(u64 param_1) {
    return FUN_710393cfe0(param_1) + FUN_710393ca80(param_1) - 0x10000;
}

// 0x7103940230 — wrapper (48B)
_O0 void FUN_7103940230(u64 param_1, u64 param_2) {
    FUN_7103957c40(param_1, param_2);
}

// 0x7103940260 — call with two args, return low bit (48B)
_O0 u32 FUN_7103940260(u64 param_1, u64 param_2) {
    u32 result = FUN_7103945dc0(param_1, param_2);
    return result & 1;
}

// 0x7103940a20 — mask low bit: x & ~1 (64B)
_O0 u64 FUN_7103940a20(u64 param_1) {
    return param_1 & 0xffffffffffffeULL;
}

// 0x7103940f40 — call with extra arg 1 (48B)
_O0 void FUN_7103940f40(u64 param_1, u64 param_2) {
    FUN_7103941330(param_1, param_2, 1);
}

// 0x7103940f70 — call with extra arg 0 (48B)
_O0 void FUN_7103940f70(u64 param_1, u64 param_2) {
    FUN_7103941330(param_1, param_2, 0);
}

// 0x7103942300 — wrapper (48B)
_O0 void FUN_7103942300(u64 param_1) {
    FUN_7103942330(param_1);
}

// 0x7103942b40 — call with 1 + mask low bit (64B)
_O0 u32 FUN_7103942b40(u64 param_1, u64 param_2) {
    u32 result = FUN_7103942b80(param_1, param_2, 1);
    return result & 1;
}

// 0x7103943300 — call with 0 + mask low bit (64B)
_O0 u32 FUN_7103943300(u64 param_1, u64 param_2) {
    u32 result = FUN_7103942b80(param_1, param_2, 0);
    return result & 1;
}

// 0x7103944630 — wrapper (48B)
_O0 void FUN_7103944630(u64 param_1) {
    FUN_7103944770(param_1);
}

// 0x7103944710 — wrapper (48B)
_O0 void FUN_7103944710(u64 param_1) {
    FUN_7103944740(param_1);
}

// 0x7103944740 — ffsl wrapper (48B)
_O0 s32 FUN_7103944740(s64 param_1) {
    return ffsl(param_1);
}

// 0x7103945370 — call + pthread_mutex_unlock (64B)
_O0 s32 FUN_7103945370(u64 param_1, s64 param_2) {
    FUN_7103945570(FUN_7103945510(param_1), param_2 + 0x60);
    return pthread_mutex_unlock((void *)(param_2 + 0x40));
}

// 0x71039455e0 — call + store at +0x60 (64B)
_O0 void FUN_71039455e0(u64 param_1, s64 param_2) {
    FUN_71039456a0(FUN_7103945510(param_1), param_2 + 0x60);
}

// 0x71039456e0 — pthread_mutex_trylock wrapper (48B)
_O0 bool FUN_71039456e0(s64 param_1) {
    return pthread_mutex_trylock((void *)(param_1 + 0x40)) != 0;
}

// 0x7103945900 — four-arg wrapper adding extra arg 0 (64B)
_O0 void FUN_7103945900(u64 param_1, u64 param_2, u64 param_3, u64 param_4) {
    FUN_7103945940(param_1, param_2, param_3, param_4, 0);
}

// 0x7103945f80 — call + left shift 3 (multiply by 8 for pointer stride) (48B)
_O0 s64 FUN_7103945f80(u64 param_1) {
    return FUN_7103945fb0(param_1) << 3;
}

// 0x7103949930 — pthread_mutex_trylock wrapper (48B)
_O0 bool FUN_7103949930(s64 param_1) {
    return pthread_mutex_trylock((void *)(param_1 + 0x40)) != 0;
}

// 0x7103950e20 — wrapper (48B)
_O0 void FUN_7103950e20(u64 param_1, u64 param_2) {
    FUN_71039515d0(param_1, param_2);
}
