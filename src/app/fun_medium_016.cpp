#include "types.h"

// MEDIUM-tier FUN_* functions -- mixed address range, batch 17
// Pool-d worker: auto-generated from Ghidra decompilation

// ---- External declarations -----------------------------------------------

extern "C" int   __cxa_guard_acquire(u64*);
extern "C" void  __cxa_guard_release(u64*);

// curlx_tvnow returns a 16-byte timeval struct
struct CurlTimeval { u64 tv_sec; u64 tv_usec; };

// External C functions -- Curl
extern "C" u64         Curl_nnssl_data_pending();
extern "C" u64         FUN_7100015dd0(s64, s32);
extern "C" u32         FUN_7100015800(u32, u32, u32, u32);
extern "C" void        Curl_hash_start_iterate(u64, u8*);
extern "C" s64         Curl_hash_next_element(u8*);
extern "C" s32         FUN_710001f100(s64);
extern "C" void        Curl_disconnect(s64, s32);
extern "C" CurlTimeval curlx_tvnow();
extern "C" s32         FUN_71000243b0(u64, u64, s64, u64*, u64*, s32);
extern "C" u32         FUN_71000270b0();
extern "C" void        Curl_SigloFree(u64);

// External data (cxa_guard guards / singleton storage)
extern u8  PTR_DAT_71052a2380[];   // base inner guard
extern u8  PTR_DAT_71052a2388[];   // base inner data
extern u8  PTR_DAT_71052a23d0[];   // mid guard (FUN_710003e120)
extern u8  PTR_DAT_71052a23d8[];   // mid data  (FUN_710003e120)
extern u8  PTR_DAT_71052a23f8[];   // outer guard (FUN_710003d480)
extern u8  PTR_DAT_71052a2400[];   // outer data  (FUN_710003d480)
extern u8  PTR_DAT_71052a2428[];   // outer guard (FUN_710003d730)
extern u8  PTR_DAT_71052a2430[];   // outer data  (FUN_710003d730)
extern u8  PTR_DAT_71052a2438[];   // outer guard (FUN_710003d9c0)
extern u8  PTR_DAT_71052a2440[];   // outer data  (FUN_710003d9c0)
extern u8  PTR_DAT_71052a2450[];   // outer guard (FUN_710003dce0)
extern u8  PTR_DAT_71052a2458[];   // outer data  (FUN_710003dce0)
extern u8  PTR_DAT_71052a2460[];   // outer guard (FUN_710003df20)
extern u8  PTR_DAT_71052a2468[];   // outer data  (FUN_710003df20)
extern u8  PTR_DAT_71052a2470[];   // outer guard (FUN_710003e120)
extern u8  PTR_DAT_71052a2478[];   // outer data  (FUN_710003e120)

// ---- Curl SSL / hash helpers ---------------------------------------------

// 7100004270 -- SSL pending check, fall through to FUN_7100015800
u32 FUN_7100004270(s64 param_1, s32 param_2)
{
    u64 uVar2 = Curl_nnssl_data_pending();
    if ((uVar2 & 1) != 0)
        return 1;
    uVar2 = FUN_7100015dd0(param_1, param_2);
    if ((uVar2 & 1) != 0)
        return 1;
    u32 uVar1 = FUN_7100015800(*(u32*)(param_1 + (s64)param_2 * 4 + 600),
                                0xffffffff, 0xffffffff, 0);
    return (u32)(0 < (s32)uVar1) & uVar1;
}

// 7100004720 -- iterate curl hash, return first non-null element data
u64 FUN_7100004720(u64 param_1)
{
    u64* puVar2;
    u8 auStack_28[24];
    Curl_hash_start_iterate(param_1, auStack_28);
    do {
        s64 lVar1 = Curl_hash_next_element(auStack_28);
        if (lVar1 == 0)
            return 0;
        puVar2 = *(u64**)(*(s64*)(lVar1 + 0x18) + 0x10);
    } while (puVar2 == nullptr);
    return *puVar2;
}

// 7100005a10 -- conditional pointer move, call disconnect
s32 FUN_7100005a10(s64 param_1)
{
    if (*(s64*)(param_1 + 0xa48) != 0) {
        *(s64*)(param_1 + 0x70) = *(s64*)(param_1 + 0xa48);
        *(u64*)(param_1 + 0xa48) = 0;
    }
    s32 iVar1 = FUN_710001f100(param_1);
    if (iVar1 != 0) {
        Curl_disconnect(param_1, 0);
    }
    return iVar1;
}

// 7100015110 -- reset timer fields using curlx_tvnow
void FUN_7100015110(s64 param_1)
{
    *(u32*)(param_1 + 0xb58) = 0;
    *(CurlTimeval*)(param_1 + 0xa58) = curlx_tvnow();
    *(u64*)(param_1 + 0xa98) = 0;
    *(u32*)(param_1 + 0xaa0) = 0;
    *(u64*)(param_1 + 0xab0) = 0;
    *(u32*)(param_1 + 0xab8) = 0;
    *(u32*)(param_1 + 0xa08) = *(u32*)(param_1 + 0xa08) & 0x90;
}

// 7100024310 -- Curl base64/siglo decode helper
u64 FUN_7100024310(u64 param_1, u64 param_2, s32 param_3, u32* param_4)
{
    u64 local_28;
    u64 local_18 = 0;
    if (param_3 >= 0) {
        s32 iVar1 = FUN_71000243b0(param_1, param_2, (s64)param_3,
                                    &local_18, &local_28, 0);
        if (iVar1 == 0) {
            if (param_4 != nullptr) {
                if (local_28 >> 0x1f == 0) {
                    u32 uVar2 = FUN_71000270b0();
                    *param_4 = uVar2;
                    return local_18;
                }
                Curl_SigloFree(local_18);
                local_18 = 0;
            }
            return local_18;
        }
    }
    return 0;
}

// ---- cxa_guard singleton chains (all share base inner 2380/2388) ---------

// 710003d480 -- nested: outer 23f8/2400, inner 2380/2388
u8* FUN_710003d480()
{
    s32 iVar1;
    if ((*PTR_DAT_71052a23f8 & 1) == 0) {
        iVar1 = __cxa_guard_acquire((u64*)PTR_DAT_71052a23f8);
        if (iVar1 != 0) {
            if ((*PTR_DAT_71052a2380 & 1) == 0) {
                iVar1 = __cxa_guard_acquire((u64*)PTR_DAT_71052a2380);
                if (iVar1 != 0) {
                    *(u64*)PTR_DAT_71052a2388 = 0;
                    __cxa_guard_release((u64*)PTR_DAT_71052a2380);
                }
            }
            *(u8**)PTR_DAT_71052a2400 = PTR_DAT_71052a2388;
            __cxa_guard_release((u64*)PTR_DAT_71052a23f8);
        }
    }
    return PTR_DAT_71052a2400;
}

// 710003d730 -- nested: outer 2428/2430, inner 2380/2388
u8* FUN_710003d730()
{
    s32 iVar1;
    if ((*PTR_DAT_71052a2428 & 1) == 0) {
        iVar1 = __cxa_guard_acquire((u64*)PTR_DAT_71052a2428);
        if (iVar1 != 0) {
            if ((*PTR_DAT_71052a2380 & 1) == 0) {
                iVar1 = __cxa_guard_acquire((u64*)PTR_DAT_71052a2380);
                if (iVar1 != 0) {
                    *(u64*)PTR_DAT_71052a2388 = 0;
                    __cxa_guard_release((u64*)PTR_DAT_71052a2380);
                }
            }
            *(u8**)PTR_DAT_71052a2430 = PTR_DAT_71052a2388;
            __cxa_guard_release((u64*)PTR_DAT_71052a2428);
        }
    }
    return PTR_DAT_71052a2430;
}

// 710003d9c0 -- nested: outer 2438/2440, inner 2380/2388
u8* FUN_710003d9c0()
{
    s32 iVar1;
    if ((*PTR_DAT_71052a2438 & 1) == 0) {
        iVar1 = __cxa_guard_acquire((u64*)PTR_DAT_71052a2438);
        if (iVar1 != 0) {
            if ((*PTR_DAT_71052a2380 & 1) == 0) {
                iVar1 = __cxa_guard_acquire((u64*)PTR_DAT_71052a2380);
                if (iVar1 != 0) {
                    *(u64*)PTR_DAT_71052a2388 = 0;
                    __cxa_guard_release((u64*)PTR_DAT_71052a2380);
                }
            }
            *(u8**)PTR_DAT_71052a2440 = PTR_DAT_71052a2388;
            __cxa_guard_release((u64*)PTR_DAT_71052a2438);
        }
    }
    return PTR_DAT_71052a2440;
}

// 710003dce0 -- triple: outer 2450/2458 → middle 23f8/2400 → inner 2380/2388
u8* FUN_710003dce0()
{
    s32 iVar1;
    if ((*PTR_DAT_71052a2450 & 1) == 0) {
        iVar1 = __cxa_guard_acquire((u64*)PTR_DAT_71052a2450);
        if (iVar1 != 0) {
            if ((*PTR_DAT_71052a23f8 & 1) == 0) {
                iVar1 = __cxa_guard_acquire((u64*)PTR_DAT_71052a23f8);
                if (iVar1 != 0) {
                    if ((*PTR_DAT_71052a2380 & 1) == 0) {
                        iVar1 = __cxa_guard_acquire((u64*)PTR_DAT_71052a2380);
                        if (iVar1 != 0) {
                            *(u64*)PTR_DAT_71052a2388 = 0;
                            __cxa_guard_release((u64*)PTR_DAT_71052a2380);
                        }
                    }
                    *(u8**)PTR_DAT_71052a2400 = PTR_DAT_71052a2388;
                    __cxa_guard_release((u64*)PTR_DAT_71052a23f8);
                }
            }
            *(u8**)PTR_DAT_71052a2458 = PTR_DAT_71052a2400;
            __cxa_guard_release((u64*)PTR_DAT_71052a2450);
        }
    }
    return PTR_DAT_71052a2458;
}

// 710003df20 -- nested: outer 2460/2468, inner 2380/2388
u8* FUN_710003df20()
{
    s32 iVar1;
    if ((*PTR_DAT_71052a2460 & 1) == 0) {
        iVar1 = __cxa_guard_acquire((u64*)PTR_DAT_71052a2460);
        if (iVar1 != 0) {
            if ((*PTR_DAT_71052a2380 & 1) == 0) {
                iVar1 = __cxa_guard_acquire((u64*)PTR_DAT_71052a2380);
                if (iVar1 != 0) {
                    *(u64*)PTR_DAT_71052a2388 = 0;
                    __cxa_guard_release((u64*)PTR_DAT_71052a2380);
                }
            }
            *(u8**)PTR_DAT_71052a2468 = PTR_DAT_71052a2388;
            __cxa_guard_release((u64*)PTR_DAT_71052a2460);
        }
    }
    return PTR_DAT_71052a2468;
}

// 710003e120 -- triple: outer 2470/2478 → middle 23d0/23d8 → inner 2380/2388
u8* FUN_710003e120()
{
    s32 iVar1;
    if ((*PTR_DAT_71052a2470 & 1) == 0) {
        iVar1 = __cxa_guard_acquire((u64*)PTR_DAT_71052a2470);
        if (iVar1 != 0) {
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
                }
            }
            *(u8**)PTR_DAT_71052a2478 = PTR_DAT_71052a23d8;
            __cxa_guard_release((u64*)PTR_DAT_71052a2470);
        }
    }
    return PTR_DAT_71052a2478;
}
