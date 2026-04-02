#include "types.h"

// MEDIUM-tier FUN_* functions -- mixed address range, batch 13
// Pool-d worker: auto-generated from Ghidra decompilation

// ---- External declarations -----------------------------------------------

extern "C" s32  memcmp(const void*, const void*, u64);
extern "C" s32  strcmp(const char*, const char*);
extern "C" [[noreturn]] void abort();
extern "C" [[noreturn]] void nndetailDiagAbortFormatImpl(void*, void*, void*, s32, void*);
extern "C" s32  __cxa_guard_acquire(u64*);
extern "C" void __cxa_guard_release(u64*);

// Game/libcurl functions
extern "C" void  Curl_hash_destroy(void*);
extern "C" s32   FUN_7100026170(u64, s32, u64);
extern "C" void  FUN_7100004200(u64, s32);
extern "C" s64   FUN_71000272b0();
extern "C" void  Curl_SigloFree(u64);
extern "C" void  FUN_7100057350(s64*, s32, s32, u64, u64);
extern "C" void  FUN_71000067e0(u32*, void*);
extern "C" void  FUN_7100059f90(u8*, u64, s64);
extern "C" void  FUN_7100059760(u64, u8*, u32);

// External data
extern u8  DAT_71052a80f8;
extern u8  DAT_71052a8100[];

// cxa_guard data
extern u8  PTR_DAT_71052a2370[];
extern u8  PTR_DAT_71052a2378[];
extern u8  PTR_DAT_71052a2380[];
extern u8  PTR_DAT_71052a2388[];
extern u8  PTR_DAT_71052a23d0[];
extern u8  PTR_DAT_71052a23d8[];
extern u8  PTR_DAT_71052a23e0[];
extern u8  PTR_DAT_71052a23e8[];
extern u8  PTR_DAT_71052a2498[];
extern u8  PTR_DAT_71052a24a0[];
extern u8  PTR_DAT_71052a24a8[];
extern u8  PTR_DAT_71052a24b0[];
extern u8  PTR_DAT_71052a24b8[];
extern u8  PTR_DAT_71052a24c0[];
extern u8  PTR_DAT_71052a24d0[];
extern u8  PTR_DAT_71052a24d8[];
extern u8  PTR_DAT_71052a24e0[];
extern u8  PTR_DAT_71052a24e8[];
extern u8  PTR_DAT_71052a24f0[];
extern u8  PTR_DAT_71052a24f8[];
extern u8  PTR_DAT_71052a2520[];
extern u8  PTR_DAT_71052a2528[];
extern u8  PTR_DAT_71052a2548[];
extern u8  PTR_DAT_71052a2550[];
extern u8  PTR_DAT_71052a2558[];
extern u8  PTR_DAT_71052a2560[];
extern u8  PTR_DAT_71052a2568[];
extern u8  PTR_DAT_71052a2570[];
extern u8  PTR_DAT_71052a2588[];
extern u8  PTR_DAT_71052a2590[];
extern u8  PTR_DAT_71052a2510[];
extern u8  PTR_DAT_71052a2530[];
extern void* PTR_LAB_71052a1240;

// ---- Simple wrappers / comparisons ----------------------------------------

// 7100005878 -- memcmp: return 1 if equal, 0 if not
u64 FUN_7100005878(void* param_1, u64 param_2, void* param_3)
{
    s32 iVar1 = memcmp(param_1, param_3, param_2);
    if (iVar1 != 0)
        return 0;
    return 1;
}

// 710004f50c -- strcmp at +0x10 vs +0x18, return 1 if equal
u64 FUN_710004f50c(s64 param_1, s64 param_2)
{
    s32 iVar1 = strcmp(*(const char**)(param_1 + 0x10), *(const char**)(param_2 + 0x18));
    if (iVar1 != 0)
        return 0;
    return 1;
}

// 710004f57c -- identical to FUN_710004f50c
u64 FUN_710004f57c(s64 param_1, s64 param_2)
{
    s32 iVar1 = strcmp(*(const char**)(param_1 + 0x10), *(const char**)(param_2 + 0x18));
    if (iVar1 != 0)
        return 0;
    return 1;
}

// ---- libcurl helpers -------------------------------------------------------

// 7100005b40 -- conditional Curl_hash_destroy + clear flag
void FUN_7100005b40()
{
    if (DAT_71052a80f8 == '\x01') {
        Curl_hash_destroy(DAT_71052a8100);
        DAT_71052a80f8 = '\0';
    }
}

// 710000e730 -- FUN_7100026170 dispatch with conditional FUN_7100004200
s32 FUN_710000e730(u64 param_1, u64 param_2)
{
    s32 iVar1 = FUN_7100026170(param_1, 0, param_2);
    if (iVar1 != 0)
        FUN_7100004200(param_1, 1);
    return iVar1;
}

// 7100017580 -- FUN_71000272b0 result check; conditionally free param_1
s64 FUN_7100017580(u64 param_1, s64 param_2)
{
    s64 lVar1 = FUN_71000272b0();
    if ((param_2 != 0) && (lVar1 == 0))
        Curl_SigloFree(param_1);
    return lVar1;
}

// ---- [[noreturn]] abort wrappers ------------------------------------------

// 7100027950
[[noreturn]] void FUN_7100027950()
{
    abort();
}

// 71000279e0
[[noreturn]] void FUN_71000279e0()
{
    abort();
}

// 7100027a40
[[noreturn]] void FUN_7100027a40()
{
    abort();
}

// ---- Misc helpers ---------------------------------------------------------

// 7100027110 -- init sub-object then set first field to 1
u64 FUN_7100027110(u32* param_1)
{
    FUN_71000067e0(param_1 + 6, PTR_LAB_71052a1240);
    *param_1 = 1;
    return 0;
}

// 710004ad50 -- conditional: init local buffer, call two subs
void FUN_710004ad50(s64 param_1, u64 param_2, u32 param_3)
{
    u8 auStack_48[40];
    if (*(s64*)(param_1 + 0x18) != 0) {
        FUN_7100059f90(auStack_48, param_2, param_1);
        FUN_7100059760(*(u64*)(param_1 + 0x18), auStack_48, param_3 & 1);
    }
}

// ---- nn::ui2d Pane vtable init helpers ------------------------------------

// 7100043160 -- call FUN_7100057350, set vtable to PTR+0x10
void FUN_7100043160(s64* param_1, u64 param_2, u64 param_3, u64 param_4)
{
    FUN_7100057350(param_1, 0, 0, param_2, param_4);
    *param_1 = (s64)(PTR_DAT_71052a2510 + 0x10);
}

// 7100043310 -- call FUN_7100057350, set vtable to PTR+0x10 (different vtable)
void FUN_7100043310(s64* param_1, u64 param_2, u64 param_3, u64 param_4)
{
    FUN_7100057350(param_1, 0, 0, param_2, param_4);
    *param_1 = (s64)(PTR_DAT_71052a2530 + 0x10);
}

// ---- __cxa_guard_acquire singleton init patterns --------------------------
// Pattern: check guard bit 0, acquire, init data to 0, release, return ptr

// 710003bc20
u8* FUN_710003bc20()
{
    s32 iVar1;
    if ((*PTR_DAT_71052a2380 & 1) == 0) {
        iVar1 = __cxa_guard_acquire((u64*)PTR_DAT_71052a2380);
        if (iVar1 != 0) {
            *(u64*)PTR_DAT_71052a2388 = 0;
            __cxa_guard_release((u64*)PTR_DAT_71052a2380);
            return PTR_DAT_71052a2388;
        }
    }
    return PTR_DAT_71052a2388;
}

// 710004c600
u8* FUN_710004c600()
{
    s32 iVar1;
    if ((*PTR_DAT_71052a2370 & 1) == 0) {
        iVar1 = __cxa_guard_acquire((u64*)PTR_DAT_71052a2370);
        if (iVar1 != 0) {
            *(u64*)PTR_DAT_71052a2378 = 0;
            __cxa_guard_release((u64*)PTR_DAT_71052a2370);
            return PTR_DAT_71052a2378;
        }
    }
    return PTR_DAT_71052a2378;
}

// 7100044990
u8* FUN_7100044990()
{
    s32 iVar1;
    if ((*PTR_DAT_71052a2568 & 1) == 0) {
        iVar1 = __cxa_guard_acquire((u64*)PTR_DAT_71052a2568);
        if (iVar1 != 0) {
            *(u64*)PTR_DAT_71052a2570 = 0;
            __cxa_guard_release((u64*)PTR_DAT_71052a2568);
            return PTR_DAT_71052a2570;
        }
    }
    return PTR_DAT_71052a2570;
}

// 7100044f10
u8* FUN_7100044f10()
{
    s32 iVar1;
    if ((*PTR_DAT_71052a2588 & 1) == 0) {
        iVar1 = __cxa_guard_acquire((u64*)PTR_DAT_71052a2588);
        if (iVar1 != 0) {
            *(u64*)PTR_DAT_71052a2590 = 0;
            __cxa_guard_release((u64*)PTR_DAT_71052a2588);
            return PTR_DAT_71052a2590;
        }
    }
    return PTR_DAT_71052a2590;
}

// 710005a160
u8* FUN_710005a160()
{
    s32 iVar1;
    if ((*PTR_DAT_71052a2498 & 1) == 0) {
        iVar1 = __cxa_guard_acquire((u64*)PTR_DAT_71052a2498);
        if (iVar1 != 0) {
            *(u64*)PTR_DAT_71052a24a0 = 0;
            __cxa_guard_release((u64*)PTR_DAT_71052a2498);
            return PTR_DAT_71052a24a0;
        }
    }
    return PTR_DAT_71052a24a0;
}

// ---- Nested __cxa_guard_acquire patterns ----------------------------------

// 7100043260 -- acquire outer guard, init inner (PTR_DAT_71052a2498), link pointers
u8* FUN_7100043260()
{
    s32 iVar1;
    if ((*PTR_DAT_71052a2520 & 1) == 0) {
        iVar1 = __cxa_guard_acquire((u64*)PTR_DAT_71052a2520);
        if (iVar1 != 0) {
            if ((*PTR_DAT_71052a2498 & 1) == 0) {
                iVar1 = __cxa_guard_acquire((u64*)PTR_DAT_71052a2498);
                if (iVar1 != 0) {
                    *(u64*)PTR_DAT_71052a24a0 = 0;
                    __cxa_guard_release((u64*)PTR_DAT_71052a2498);
                }
            }
            *(u8**)PTR_DAT_71052a2528 = PTR_DAT_71052a24a0;
            __cxa_guard_release((u64*)PTR_DAT_71052a2520);
            return PTR_DAT_71052a2528;
        }
    }
    return PTR_DAT_71052a2528;
}

// 7100044060
u8* FUN_7100044060()
{
    s32 iVar1;
    if ((*PTR_DAT_71052a2548 & 1) == 0) {
        iVar1 = __cxa_guard_acquire((u64*)PTR_DAT_71052a2548);
        if (iVar1 != 0) {
            if ((*PTR_DAT_71052a2498 & 1) == 0) {
                iVar1 = __cxa_guard_acquire((u64*)PTR_DAT_71052a2498);
                if (iVar1 != 0) {
                    *(u64*)PTR_DAT_71052a24a0 = 0;
                    __cxa_guard_release((u64*)PTR_DAT_71052a2498);
                }
            }
            *(u8**)PTR_DAT_71052a2550 = PTR_DAT_71052a24a0;
            __cxa_guard_release((u64*)PTR_DAT_71052a2548);
            return PTR_DAT_71052a2550;
        }
    }
    return PTR_DAT_71052a2550;
}

// 7100044110
u8* FUN_7100044110()
{
    s32 iVar1;
    if ((*PTR_DAT_71052a2558 & 1) == 0) {
        iVar1 = __cxa_guard_acquire((u64*)PTR_DAT_71052a2558);
        if (iVar1 != 0) {
            if ((*PTR_DAT_71052a2568 & 1) == 0) {
                iVar1 = __cxa_guard_acquire((u64*)PTR_DAT_71052a2568);
                if (iVar1 != 0) {
                    *(u64*)PTR_DAT_71052a2570 = 0;
                    __cxa_guard_release((u64*)PTR_DAT_71052a2568);
                }
            }
            *(u8**)PTR_DAT_71052a2560 = PTR_DAT_71052a2570;
            __cxa_guard_release((u64*)PTR_DAT_71052a2558);
            return PTR_DAT_71052a2560;
        }
    }
    return PTR_DAT_71052a2560;
}

// 710003cf90 -- nested: outer guard 23d0, inner uses 2380/2388
u8* FUN_710003cf90()
{
    s32 iVar1;
    if ((*PTR_DAT_71052a23d0 & 1) == 0) {
        iVar1 = __cxa_guard_acquire((u64*)PTR_DAT_71052a23d0);
        if (iVar1 != 0) {
            if ((*PTR_DAT_71052a2380 & 1) == 0) {
                iVar1 = __cxa_guard_acquire((u64*)PTR_DAT_71052a2380);
                if (iVar1 != 0) {
                    *(u64*)PTR_DAT_71052a2388 = 0;
                    __cxa_guard_release((u64*)PTR_DAT_71052a2380);
                }
            }
            *(u8**)PTR_DAT_71052a23d8 = PTR_DAT_71052a2388;
            __cxa_guard_release((u64*)PTR_DAT_71052a23d0);
            return PTR_DAT_71052a23d8;
        }
    }
    return PTR_DAT_71052a23d8;
}

// 710003d160
u8* FUN_710003d160()
{
    s32 iVar1;
    if ((*PTR_DAT_71052a23e0 & 1) == 0) {
        iVar1 = __cxa_guard_acquire((u64*)PTR_DAT_71052a23e0);
        if (iVar1 != 0) {
            if ((*PTR_DAT_71052a2380 & 1) == 0) {
                iVar1 = __cxa_guard_acquire((u64*)PTR_DAT_71052a2380);
                if (iVar1 != 0) {
                    *(u64*)PTR_DAT_71052a2388 = 0;
                    __cxa_guard_release((u64*)PTR_DAT_71052a2380);
                }
            }
            *(u8**)PTR_DAT_71052a23e8 = PTR_DAT_71052a2388;
            __cxa_guard_release((u64*)PTR_DAT_71052a23e0);
            return PTR_DAT_71052a23e8;
        }
    }
    return PTR_DAT_71052a23e8;
}

// 7100041570 -- triple-nested: 24f0 > 24a8 > 24b8/24c0, links 24f8->24b0->24c0
u8* FUN_7100041570()
{
    s32 iVar1;
    if ((*PTR_DAT_71052a24f0 & 1) == 0) {
        iVar1 = __cxa_guard_acquire((u64*)PTR_DAT_71052a24f0);
        if (iVar1 != 0) {
            if ((*PTR_DAT_71052a24a8 & 1) == 0) {
                iVar1 = __cxa_guard_acquire((u64*)PTR_DAT_71052a24a8);
                if (iVar1 != 0) {
                    if ((*PTR_DAT_71052a24b8 & 1) == 0) {
                        iVar1 = __cxa_guard_acquire((u64*)PTR_DAT_71052a24b8);
                        if (iVar1 != 0) {
                            *(u64*)PTR_DAT_71052a24c0 = 0;
                            __cxa_guard_release((u64*)PTR_DAT_71052a24b8);
                        }
                    }
                    *(u8**)PTR_DAT_71052a24b0 = PTR_DAT_71052a24c0;
                    __cxa_guard_release((u64*)PTR_DAT_71052a24a8);
                }
            }
            *(u8**)PTR_DAT_71052a24f8 = PTR_DAT_71052a24b0;
            __cxa_guard_release((u64*)PTR_DAT_71052a24f0);
            return PTR_DAT_71052a24f8;
        }
    }
    return PTR_DAT_71052a24f8;
}

// 7100041420 -- acquire 24d0, call FUN_7100041570, store result at 24d8
u8* FUN_7100041420()
{
    s32 iVar1;
    if ((*PTR_DAT_71052a24d0 & 1) == 0) {
        iVar1 = __cxa_guard_acquire((u64*)PTR_DAT_71052a24d0);
        if (iVar1 != 0) {
            u64 uVar2 = (u64)FUN_7100041570();
            *(u64*)PTR_DAT_71052a24d8 = uVar2;
            __cxa_guard_release((u64*)PTR_DAT_71052a24d0);
            return PTR_DAT_71052a24d8;
        }
    }
    return PTR_DAT_71052a24d8;
}

// 71000414c0 -- same as FUN_7100041420 but guard at 24e0, data at 24e8
u8* FUN_71000414c0()
{
    s32 iVar1;
    if ((*PTR_DAT_71052a24e0 & 1) == 0) {
        iVar1 = __cxa_guard_acquire((u64*)PTR_DAT_71052a24e0);
        if (iVar1 != 0) {
            u64 uVar2 = (u64)FUN_7100041570();
            *(u64*)PTR_DAT_71052a24e8 = uVar2;
            __cxa_guard_release((u64*)PTR_DAT_71052a24e0);
            return PTR_DAT_71052a24e8;
        }
    }
    return PTR_DAT_71052a24e8;
}
