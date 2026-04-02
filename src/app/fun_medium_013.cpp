#include "types.h"

// MEDIUM-tier FUN_* functions -- mixed address range, batch 14
// Pool-d worker: auto-generated from Ghidra decompilation

// ---- External declarations -----------------------------------------------

extern "C" void* memset(void*, int, u64);
extern "C" void* memcpy(void*, const void*, u64);
extern "C" s32   memcmp(const void*, const void*, u64);
extern "C" char* strncpy(char*, const char*, u64);
extern "C" u64   strlen(const char*);
extern "C" float acosf(float);
extern "C" s32  __cxa_guard_acquire(u64*);
extern "C" void __cxa_guard_release(u64*);

// nn namespaces
namespace nn {
namespace ui2d {
namespace Layout {
    void* AllocateMemory(u64);
}
}
namespace nex {
namespace InetAddress {
    void SetAddress(u64, u32);
    void SetPortNumber(u64, u16);
}
}
namespace pia {
namespace common {
namespace CallContext {
    void SignalCancel(s32*);
    void Reset(s32*);
}
}
}
}

namespace pead {
    void getArraySize(s64);
    void freeToSeadHeap(s64);
}

// External C functions
extern "C" void  FUN_7100060e80(u64*);
extern "C" void  FUN_71000b1d10(s64, u32);
extern "C" void  FUN_71000b1da0(u8*, s64, u32*);
extern "C" s32   FUN_71001354c0(u32);
extern "C" void  FUN_7100057350(s64*, s32, s32, u64, u64);
extern "C" char* FUN_71000666b0(char*);

// External data
extern u8  DAT_71044919c4[];
extern f32 PTR_FloatPi_71052a27d8[];
extern u8  PTR_DAT_71052a27b0[];
extern u8  PTR_DAT_71052a2c80[];
extern u8  PTR_DAT_71052a2c88[];
extern u8  PTR_DAT_71052a2ce0[];
extern u8  PTR_DAT_71052a2ce8[];

// cxa_guard data
extern u8  PTR_DAT_71052a2380[];
extern u8  PTR_DAT_71052a2388[];
extern u8  PTR_DAT_71052a2418[];
extern u8  PTR_DAT_71052a2420[];
extern u8  PTR_DAT_71052a2488[];
extern u8  PTR_DAT_71052a2490[];
extern u8  PTR_DAT_71052a2498[];
extern u8  PTR_DAT_71052a24a0[];
extern u8  PTR_DAT_71052a2568[];
extern u8  PTR_DAT_71052a2570[];
extern u8  PTR_DAT_71052a25b8[];
extern u8  PTR_DAT_71052a25c0[];
extern u8  PTR_DAT_71052a25c8[];
extern u8  PTR_DAT_71052a25d0[];
extern u8  PTR_DAT_71052a25d8[];
extern u8  PTR_DAT_71052a25e0[];
extern u8  PTR_DAT_71052a25e8[];
extern u8  PTR_DAT_71052a25f0[];
extern u8  PTR_DAT_71052a25f8[];
extern u8  PTR_DAT_71052a2600[];
extern u8  PTR_DAT_71052a2718[];
extern u8  PTR_DAT_71052a2720[];
extern u8  PTR_DAT_71052a2530[];
extern u8  PTR_DAT_71052a2770[];
extern u8  PTR_DAT_71052a2778[];
extern u8  PTR_DAT_71052a27b8[];
extern u8  PTR_DAT_71052a27c0[];
extern u8  PTR_DAT_71052a27c8[];
extern u8  PTR_DAT_71052a27d0[];
extern u8  PTR_DAT_71052a26f0[];
extern u8  PTR_DAT_71052a26f8[];

// ---- __cxa_guard_acquire singleton init patterns --------------------------

// 710003d650 -- nested: outer 2418/2420, inner 2380/2388
u8* FUN_710003d650()
{
    s32 iVar1;
    if ((*PTR_DAT_71052a2418 & 1) == 0) {
        iVar1 = __cxa_guard_acquire((u64*)PTR_DAT_71052a2418);
        if (iVar1 != 0) {
            if ((*PTR_DAT_71052a2380 & 1) == 0) {
                iVar1 = __cxa_guard_acquire((u64*)PTR_DAT_71052a2380);
                if (iVar1 != 0) {
                    *(u64*)PTR_DAT_71052a2388 = 0;
                    __cxa_guard_release((u64*)PTR_DAT_71052a2380);
                }
            }
            *(u8**)PTR_DAT_71052a2420 = PTR_DAT_71052a2388;
            __cxa_guard_release((u64*)PTR_DAT_71052a2418);
            return PTR_DAT_71052a2420;
        }
    }
    return PTR_DAT_71052a2420;
}

// 710005e010 -- nested: outer 2488/2490, inner 2498/24a0
u8* FUN_710005e010()
{
    s32 iVar1;
    if ((*PTR_DAT_71052a2488 & 1) == 0) {
        iVar1 = __cxa_guard_acquire((u64*)PTR_DAT_71052a2488);
        if (iVar1 != 0) {
            if ((*PTR_DAT_71052a2498 & 1) == 0) {
                iVar1 = __cxa_guard_acquire((u64*)PTR_DAT_71052a2498);
                if (iVar1 != 0) {
                    *(u64*)PTR_DAT_71052a24a0 = 0;
                    __cxa_guard_release((u64*)PTR_DAT_71052a2498);
                }
            }
            *(u8**)PTR_DAT_71052a2490 = PTR_DAT_71052a24a0;
            __cxa_guard_release((u64*)PTR_DAT_71052a2488);
            return PTR_DAT_71052a2490;
        }
    }
    return PTR_DAT_71052a2490;
}

// 7100060700 -- nested: outer 25b8/25c0, inner 2498/24a0
u8* FUN_7100060700()
{
    s32 iVar1;
    if ((*PTR_DAT_71052a25b8 & 1) == 0) {
        iVar1 = __cxa_guard_acquire((u64*)PTR_DAT_71052a25b8);
        if (iVar1 != 0) {
            if ((*PTR_DAT_71052a2498 & 1) == 0) {
                iVar1 = __cxa_guard_acquire((u64*)PTR_DAT_71052a2498);
                if (iVar1 != 0) {
                    *(u64*)PTR_DAT_71052a24a0 = 0;
                    __cxa_guard_release((u64*)PTR_DAT_71052a2498);
                }
            }
            *(u8**)PTR_DAT_71052a25c0 = PTR_DAT_71052a24a0;
            __cxa_guard_release((u64*)PTR_DAT_71052a25b8);
            return PTR_DAT_71052a25c0;
        }
    }
    return PTR_DAT_71052a25c0;
}

// 71000646f0 -- nested: outer 25c8/25d0, inner 2498/24a0
u8* FUN_71000646f0()
{
    s32 iVar1;
    if ((*PTR_DAT_71052a25c8 & 1) == 0) {
        iVar1 = __cxa_guard_acquire((u64*)PTR_DAT_71052a25c8);
        if (iVar1 != 0) {
            if ((*PTR_DAT_71052a2498 & 1) == 0) {
                iVar1 = __cxa_guard_acquire((u64*)PTR_DAT_71052a2498);
                if (iVar1 != 0) {
                    *(u64*)PTR_DAT_71052a24a0 = 0;
                    __cxa_guard_release((u64*)PTR_DAT_71052a2498);
                }
            }
            *(u8**)PTR_DAT_71052a25d0 = PTR_DAT_71052a24a0;
            __cxa_guard_release((u64*)PTR_DAT_71052a25c8);
            return PTR_DAT_71052a25d0;
        }
    }
    return PTR_DAT_71052a25d0;
}

// 710006b690 -- nested: outer 25d8/25e0, inner 2498/24a0
u8* FUN_710006b690()
{
    s32 iVar1;
    if ((*PTR_DAT_71052a25d8 & 1) == 0) {
        iVar1 = __cxa_guard_acquire((u64*)PTR_DAT_71052a25d8);
        if (iVar1 != 0) {
            if ((*PTR_DAT_71052a2498 & 1) == 0) {
                iVar1 = __cxa_guard_acquire((u64*)PTR_DAT_71052a2498);
                if (iVar1 != 0) {
                    *(u64*)PTR_DAT_71052a24a0 = 0;
                    __cxa_guard_release((u64*)PTR_DAT_71052a2498);
                }
            }
            *(u8**)PTR_DAT_71052a25e0 = PTR_DAT_71052a24a0;
            __cxa_guard_release((u64*)PTR_DAT_71052a25d8);
            return PTR_DAT_71052a25e0;
        }
    }
    return PTR_DAT_71052a25e0;
}

// 710006e920 -- nested: outer 25e8/25f0, inner 2498/24a0
u8* FUN_710006e920()
{
    s32 iVar1;
    if ((*PTR_DAT_71052a25e8 & 1) == 0) {
        iVar1 = __cxa_guard_acquire((u64*)PTR_DAT_71052a25e8);
        if (iVar1 != 0) {
            if ((*PTR_DAT_71052a2498 & 1) == 0) {
                iVar1 = __cxa_guard_acquire((u64*)PTR_DAT_71052a2498);
                if (iVar1 != 0) {
                    *(u64*)PTR_DAT_71052a24a0 = 0;
                    __cxa_guard_release((u64*)PTR_DAT_71052a2498);
                }
            }
            *(u8**)PTR_DAT_71052a25f0 = PTR_DAT_71052a24a0;
            __cxa_guard_release((u64*)PTR_DAT_71052a25e8);
            return PTR_DAT_71052a25f0;
        }
    }
    return PTR_DAT_71052a25f0;
}

// 710006d210 -- nested: outer 25f8/2600, inner 2498/24a0
u8* FUN_710006d210()
{
    s32 iVar1;
    if ((*PTR_DAT_71052a25f8 & 1) == 0) {
        iVar1 = __cxa_guard_acquire((u64*)PTR_DAT_71052a25f8);
        if (iVar1 != 0) {
            if ((*PTR_DAT_71052a2498 & 1) == 0) {
                iVar1 = __cxa_guard_acquire((u64*)PTR_DAT_71052a2498);
                if (iVar1 != 0) {
                    *(u64*)PTR_DAT_71052a24a0 = 0;
                    __cxa_guard_release((u64*)PTR_DAT_71052a2498);
                }
            }
            *(u8**)PTR_DAT_71052a2600 = PTR_DAT_71052a24a0;
            __cxa_guard_release((u64*)PTR_DAT_71052a25f8);
            return PTR_DAT_71052a2600;
        }
    }
    return PTR_DAT_71052a2600;
}

// 7100060ac0 -- simple: guard 2770, data 2778
u8* FUN_7100060ac0()
{
    s32 iVar1;
    if ((*PTR_DAT_71052a2770 & 1) == 0) {
        iVar1 = __cxa_guard_acquire((u64*)PTR_DAT_71052a2770);
        if (iVar1 != 0) {
            *(u64*)PTR_DAT_71052a2778 = 0;
            __cxa_guard_release((u64*)PTR_DAT_71052a2770);
            return PTR_DAT_71052a2778;
        }
    }
    return PTR_DAT_71052a2778;
}

// 7100078a50 -- nested: outer 26f8/26f0, inner 2568/2570
u8* FUN_7100078a50()
{
    s32 iVar1;
    if ((*PTR_DAT_71052a26f8 & 1) == 0) {
        iVar1 = __cxa_guard_acquire((u64*)PTR_DAT_71052a26f8);
        if (iVar1 != 0) {
            if ((*PTR_DAT_71052a2568 & 1) == 0) {
                iVar1 = __cxa_guard_acquire((u64*)PTR_DAT_71052a2568);
                if (iVar1 != 0) {
                    *(u64*)PTR_DAT_71052a2570 = 0;
                    __cxa_guard_release((u64*)PTR_DAT_71052a2568);
                }
            }
            *(u8**)PTR_DAT_71052a26f0 = PTR_DAT_71052a2570;
            __cxa_guard_release((u64*)PTR_DAT_71052a26f8);
            return PTR_DAT_71052a26f0;
        }
    }
    return PTR_DAT_71052a26f0;
}

// 7100065380 -- triple-nested: 27b8 > 27c8 > 2718/2720, links 27c0->27d0->2720
u8* FUN_7100065380()
{
    s32 iVar1;
    if ((*PTR_DAT_71052a27b8 & 1) == 0) {
        iVar1 = __cxa_guard_acquire((u64*)PTR_DAT_71052a27b8);
        if (iVar1 != 0) {
            if ((*PTR_DAT_71052a27c8 & 1) == 0) {
                iVar1 = __cxa_guard_acquire((u64*)PTR_DAT_71052a27c8);
                if (iVar1 != 0) {
                    if ((*PTR_DAT_71052a2718 & 1) == 0) {
                        iVar1 = __cxa_guard_acquire((u64*)PTR_DAT_71052a2718);
                        if (iVar1 != 0) {
                            *(u64*)PTR_DAT_71052a2720 = 0;
                            __cxa_guard_release((u64*)PTR_DAT_71052a2718);
                        }
                    }
                    *(u8**)PTR_DAT_71052a27d0 = PTR_DAT_71052a2720;
                    __cxa_guard_release((u64*)PTR_DAT_71052a27c8);
                }
            }
            *(u8**)PTR_DAT_71052a27c0 = PTR_DAT_71052a27d0;
            __cxa_guard_release((u64*)PTR_DAT_71052a27b8);
            return PTR_DAT_71052a27c0;
        }
    }
    return PTR_DAT_71052a27c0;
}

// ---- nn::ui2d helpers -----------------------------------------------------

// 71000666b0 -- string dup: allocate sVar1+1 bytes, strncpy, return ptr
char* FUN_71000666b0(char* param_1)
{
    u64 sVar1 = strlen(param_1);
    char* dest = (char*)nn::ui2d::Layout::AllocateMemory(sVar1 + 1);
    strncpy(dest, param_1, sVar1 + 1);
    return dest;
}

// 7100065310 -- init struct: zero field[2], set vtable ptr, set field[1]=-1, string-dup field[2]
void FUN_7100065310(s64* param_1, u64 param_2)
{
    param_1[2] = 0;
    *param_1 = (s64)(PTR_DAT_71052a27b0 + 0x10);
    param_1[1] = -1;
    s64 lVar2 = (s64)FUN_71000666b0((char*)param_2);
    param_1[2] = lVar2;
}

// 7100064450 -- conditional store u32 at +0x150 or +0x154, set flag bits
void FUN_7100064450(u32 param_1, s64 param_2, s32 param_3)
{
    if (param_3 != 1) {
        if (param_3 == 0)
            **(u32**)(param_2 + 0x150) = param_1;
        *(u16*)(param_2 + 0x114) |= 4;
        return;
    }
    *(u32*)(*(s64*)(param_2 + 0x150) + 4) = param_1;
    *(u16*)(param_2 + 0x114) |= 4;
}

// 7100078970 -- write float if changed, set dirty bit
void FUN_7100078970(f32 param_1, s64 param_2)
{
    if (*(f32*)(param_2 + 0x150) != param_1) {
        *(f32*)(param_2 + 0x150) = param_1;
        *(u8*)(param_2 + 0x158) |= 1;
    }
}

// 71000716dc -- compute (pi / acosf(-2/x + 1)) * 4 + 8
s32 FUN_71000716dc(f32 param_1)
{
    f32 fVar1 = acosf(-2.0f / param_1 + 1.0f);
    if (fVar1 != 0.0f && fVar1 > 0.0f) {
        return (s32)(*PTR_FloatPi_71052a27d8 / fVar1) * 4 + 8;
    }
    return 8;
}

// ---- vtable dispatch helpers -----------------------------------------------

// 71000789e0 -- vtable call at +0x30 with 0, return result + 1
s32 FUN_71000789e0(s64* param_1)
{
    s32 iVar1 = (*(s32(**)(s64*, s32))(*(s64*)param_1 + 0x30))(param_1, 0);
    return iVar1 + 1;
}

// 7100078bc0 -- double-deref vtable at +0x20, return field*result
f32 FUN_7100078bc0(s64 param_1)
{
    s32 iVar1 = (*(s32(**)(void))(*(s64*)*(s64**)(param_1 + 0x28) + 0x20))();
    return *(f32*)(param_1 + 0xc) * (f32)iVar1;
}

// 7100078c00 -- double-deref vtable at +0x28, return field*result
f32 FUN_7100078c00(s64 param_1)
{
    s32 iVar1 = (*(s32(**)(void))(*(s64*)*(s64**)(param_1 + 0x28) + 0x28))();
    return *(f32*)(param_1 + 0x10) * (f32)iVar1;
}

// 7100078c40 -- double-deref vtable at +0x30, return field*result
f32 FUN_7100078c40(s64 param_1)
{
    s32 iVar1 = (*(s32(**)(void))(*(s64*)*(s64**)(param_1 + 0x28) + 0x30))();
    return *(f32*)(param_1 + 0x10) * (f32)iVar1;
}

// ---- Struct init helpers ---------------------------------------------------

// 710005a5e0 -- zero first field, call sub x3, memset middle region
void FUN_710005a5e0(u64* param_1)
{
    *param_1 = 0;
    FUN_7100060e80(param_1 + 2);
    FUN_7100060e80(param_1 + 4);
    FUN_7100060e80(param_1 + 0xc);
    memset(param_1 + 1, 0, 0x1a1);
}

// 71000b1d50 -- copy two 8-byte params to struct via stack locals
void FUN_71000b1d50(s64 param_1, u64 param_2, u64 param_3)
{
    u64 local_30 = param_2;
    u64 local_28 = param_3;
    memset((void*)(param_1 + 8), 0, 0x10);
    memcpy((void*)(param_1 + 8), &local_30, 0x10);
}

// 71000b1f50 -- two memcmp checks against constant data, return nonzero if either differs
u32 FUN_71000b1f50(s64 param_1)
{
    u32 uVar1 = (u32)memcmp((void*)(param_1 + 8), &DAT_71044919c4, 0x10);
    if (uVar1 != 0) {
        s32 iVar2 = memcmp((void*)(param_1 + 0xc), &DAT_71044919c4, 0xc);
        uVar1 = (u32)(iVar2 != 0);
    }
    return uVar1;
}

// ---- nn::pia / pead helpers ------------------------------------------------

// 71000b4000 -- conditional SignalCancel, then Reset, zero field
void FUN_71000b4000(s64 param_1)
{
    s32* piVar1 = (s32*)(param_1 + 0x58);
    if (*piVar1 == 1)
        nn::pia::common::CallContext::SignalCancel(piVar1);
    nn::pia::common::CallContext::Reset(piVar1);
    *(u64*)(param_1 + 0x88) = 0;
}

// 71000b6510 -- zero global ptr, then conditionally freeToSeadHeap
void FUN_71000b6510()
{
    if (*(s64*)PTR_DAT_71052a2c80 != 0)
        *(u64*)PTR_DAT_71052a2c80 = 0;
    u8* puVar1 = PTR_DAT_71052a2c88;
    s64 lVar2 = *(s64*)PTR_DAT_71052a2c88;
    if (lVar2 != 0) {
        pead::getArraySize(lVar2);
        pead::freeToSeadHeap(lVar2);
        *(u64*)puVar1 = 0;
    }
}

// 71000bb8e0 -- same pattern, different globals (2ce0/2ce8)
void FUN_71000bb8e0()
{
    if (*(s64*)PTR_DAT_71052a2ce0 != 0)
        *(u64*)PTR_DAT_71052a2ce0 = 0;
    u8* puVar1 = PTR_DAT_71052a2ce8;
    s64 lVar2 = *(s64*)PTR_DAT_71052a2ce8;
    if (lVar2 != 0) {
        pead::getArraySize(lVar2);
        pead::freeToSeadHeap(lVar2);
        *(u64*)puVar1 = 0;
    }
}

// 71000ba9b0 -- byte-swap u32 and u16, then call FUN_71000b1d10
void FUN_71000ba9b0(s64 param_1, s64 param_2)
{
    if (param_2 != 0) {
        u32 uVar1 = ((*(u32*)(param_1 + 4) & 0xff00ff00u) >> 8) |
                    ((*(u32*)(param_1 + 4) & 0x00ff00ffu) << 8);
        FUN_71000b1d10(param_2, uVar1 >> 0x10 | uVar1 << 0x10);
        *(u16*)(param_2 + 0x18) = (*(u16*)(param_1 + 2) >> 8) |
                                  (u16)((*(u16*)(param_1 + 2) & 0xff00u) << 8);
    }
}

// 71000bf770 -- FUN_71001354c0 result, floor to min 1
s32 FUN_71000bf770(s64 param_1)
{
    s32 iVar1 = FUN_71001354c0(*(u32*)(param_1 + 0x5f0));
    if (iVar1 < 2)
        iVar1 = 1;
    return iVar1;
}

// 71000c2a90 -- extract local address, set InetAddress fields
void FUN_71000c2a90(s64 param_1, u64 param_2)
{
    u8  auStack_38[16];
    u32 local_28[2];
    local_28[0] = 0;
    FUN_71000b1da0(auStack_38, param_1, local_28);
    nn::nex::InetAddress::SetAddress(param_2, local_28[0]);
    nn::nex::InetAddress::SetPortNumber(param_2, *(u16*)(param_1 + 0x18));
}
