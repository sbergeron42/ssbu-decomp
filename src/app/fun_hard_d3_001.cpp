#include "types.h"

// HARD-tier functions — 0x710392xxxx-0x710393xxxx range
// Pool-d worker: decompiled from Ghidra + assembly analysis

// ---- External declarations -----------------------------------------------

extern "C" {
u64  FUN_71039281f0(u64);
void FUN_710395ae10(u64, u64);
u64  FUN_7103928d50(u64);
u64  FUN_7103929160(u64);
void FUN_7103929100(u64);
void FUN_7103929210(u64);
void FUN_7103929740(u64);
void FUN_7103929810(u64);
void FUN_710392c160(u64);
u32* FUN_710392c660(u64);
u64  FUN_7103928860(u64);
u32  FUN_7103928df0(u64);
void FUN_710392c730(u64, u32, u32);
u8*  FUN_710392c560(u64);
u64  FUN_710392c480(u64);
void FUN_710392c4e0(u64, u64);
void FUN_710392b3f0(u64);
void FUN_71039575b0(void);
void FUN_710392da50(void);
u64  FUN_71039302c0(u64);
u64  FUN_71039302e0(u64);
u64  FUN_7103930300(u64);
void FUN_71039309b0(u64, u64);
void FUN_7103930bb0(u32);

__attribute__((visibility("hidden"))) u32 DAT_71052934c0;
}

// ---- Matching C functions (wrappers) -----------------------------------------

// 0x71039290d0 — wrapper (48 bytes)
extern "C" __attribute__((optnone))
void FUN_71039290d0(u64 param_1)
{
    goto a; a:; do {} while(0);
    FUN_7103929100(param_1);
}

// 0x71039291e0 — wrapper (48 bytes)
extern "C" __attribute__((optnone))
void FUN_71039291e0(u64 param_1)
{
    goto a; a:; do {} while(0);
    FUN_7103929210(param_1);
}

// 0x7103929710 — wrapper (48 bytes)
extern "C" __attribute__((optnone))
void FUN_7103929710(u64 param_1)
{
    goto a; a:; do {} while(0);
    FUN_7103929740(param_1);
}

// 0x71039297e0 — wrapper (48 bytes)
extern "C" __attribute__((optnone))
void FUN_71039297e0(u64 param_1)
{
    goto a; a:; do {} while(0);
    FUN_7103929810(param_1);
}

// 0x710392c130 — wrapper (48 bytes)
extern "C" __attribute__((optnone))
void FUN_710392c130(u64 param_1)
{
    goto a; a:; do {} while(0);
    FUN_710392c160(param_1);
}

// 0x710392c630 — wrapper returning pointer (48 bytes)
extern "C" __attribute__((optnone))
u32* FUN_710392c630(u64 param_1)
{
    goto a; a:; do {} while(0);
    return FUN_710392c660(param_1);
}

// 0x7103930b80 — wrapper u32 (48 bytes)
extern "C" __attribute__((optnone))
void FUN_7103930b80(u32 param_1)
{
    goto a; a:; do {} while(0);
    FUN_7103930bb0(param_1);
}
