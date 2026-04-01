#include "types.h"

// placement new
inline void* operator new(unsigned long, void* p) noexcept { return p; }
inline void  operator delete(void*, void*) noexcept {}

// MEDIUM-tier FUN_* functions — mixed address range, batch 20
// Pool-d worker: auto-generated from Ghidra decompilation

// ---- External declarations -----------------------------------------------

extern "C" void* memcpy(void*, const void*, u64);
extern "C" void* memset(void*, int, u64);
extern "C" int   __cxa_guard_acquire(u64*);
extern "C" void  __cxa_guard_release(u64*);

// nn namespaces
namespace nn {
namespace pia {
namespace common {
    struct StepSequenceJob { StepSequenceJob(); };
}
}
}

// External C functions
extern "C" u64  FUN_7100088c50(s64, u64, u64);
extern "C" s64  FUN_71000c9c60(s64);

// External data
extern u8  PTR_DAT_71052a29b8[];   // outer guard (FUN_71000854a0)
extern u8  PTR_DAT_71052a29c0[];   // outer data  (FUN_71000854a0)
extern u8  PTR_DAT_71052a2900[];   // inner guard  (FUN_71000854a0)
extern u8  PTR_DAT_71052a2908[];   // inner data   (FUN_71000854a0)
extern u8  PTR_g_SamplerPatternCount_71052a2bc8[];
extern u8  PTR_g_SamplerBuffer_71052a2bc0[];
extern u8  PTR_DAT_71052a2e50[];   // vtable (FUN_71000c8830)

// ---- Struct index + call helper ------------------------------------------

// 7100088090 — index by param_2*0x20, store fields, call FUN_7100088c50
u64 FUN_7100088090(s64 param_1, s32 param_2, u64 param_3)
{
    s64 lVar1 = param_1 + (s64)param_2 * 0x20;
    s64 lVar2 = *(s64*)(param_1 + 0x700);
    *(u64*)(lVar1 + 0x720) = param_3;
    *(s64*)(lVar1 + 0x718) = lVar2;
    u64 uVar3 = FUN_7100088c50(lVar2, param_3, *(u64*)(lVar2 + 0x1c8));
    *(u64*)(lVar1 + 0x708) = uVar3;
    return 1;
}

// ---- Float scale with NaN passthrough ------------------------------------

// 710009e100 — scale float at +0x14 by field +0x4c, pass through if <=1 or NaN
s32 FUN_710009e100(s64 param_1)
{
    f32 fVar1 = *(f32*)(*(s64*)(*(s64*)(param_1 + 0x238) + 0x338) + 0x14);
    f32 fVar3 = *(f32*)(param_1 + 0x4c);
    f32 fVar2 = fVar1 * fVar3;
    if (fVar3 == 1.0f || !(fVar3 >= 1.0f)) {
        fVar2 = fVar1;
    }
    return (s32)fVar2;
}

// 71000a38f0 — same as FUN_710009e100 but reads offset +0x18
s32 FUN_71000a38f0(s64 param_1)
{
    f32 fVar1 = *(f32*)(*(s64*)(*(s64*)(param_1 + 0x238) + 0x338) + 0x18);
    f32 fVar3 = *(f32*)(param_1 + 0x4c);
    f32 fVar2 = fVar1 * fVar3;
    if (fVar3 == 1.0f || !(fVar3 >= 1.0f)) {
        fVar2 = fVar1;
    }
    return (s32)fVar2;
}

// ---- Variable-length struct linear search --------------------------------

// 710007c310 — do-while search through variable-stride entries
s32* FUN_710007c310(s64 param_1, s32 param_2)
{
    u32 uVar1;
    s32* piVar2;

    if (*(u16*)(param_1 + 0x10) != 0) {
        uVar1 = 0;
        piVar2 = (s32*)(param_1 + (u64)*(u16*)(param_1 + 6));
        do {
            if (*piVar2 == param_2) {
                return piVar2 + 2;
            }
            uVar1 = uVar1 + 1;
            piVar2 = (s32*)((s64)piVar2 + (u64)(u32)piVar2[1]);
        } while (uVar1 < *(u16*)(param_1 + 0x10));
    }
    return (s32*)0;
}

// ---- cxa_guard singleton -------------------------------------------------

// 71000854a0 — nested cxa_guard: outer 29b8/29c0, inner 2900/2908
u8* FUN_71000854a0()
{
    s32 iVar1;
    if ((*PTR_DAT_71052a29b8 & 1) == 0) {
        iVar1 = __cxa_guard_acquire((u64*)PTR_DAT_71052a29b8);
        if (iVar1 != 0) {
            if ((*PTR_DAT_71052a2900 & 1) == 0) {
                iVar1 = __cxa_guard_acquire((u64*)PTR_DAT_71052a2900);
                if (iVar1 != 0) {
                    *(u64*)PTR_DAT_71052a2908 = 0;
                    __cxa_guard_release((u64*)PTR_DAT_71052a2900);
                }
            }
            *(u8**)PTR_DAT_71052a29c0 = PTR_DAT_71052a2908;
            __cxa_guard_release((u64*)PTR_DAT_71052a29b8);
        }
    }
    return PTR_DAT_71052a29c0;
}

// ---- Conditional memcpy block --------------------------------------------

// 710008d670 — copy up to 11 buffer slots when flag byte is zero
void FUN_710008d670(u64 param_1, s64 param_2)
{
    if (*(s8*)(*(s64*)(param_2 + 0xa0) + 0x752) == '\0') {
        u64* puVar1 = *(u64**)(param_2 + 0xc0);
        u64 __n = (u64)*(s32*)(param_2 + 0x28) << 4;
        memcpy((void*)*puVar1,         *(void**)(param_2 + 0x1d0), __n);
        memcpy((void*)puVar1[1],       *(void**)(param_2 + 0x1d8), __n);
        memcpy((void*)puVar1[2],       *(void**)(param_2 + 0x1e0), __n);
        memcpy((void*)puVar1[4],       *(void**)(param_2 + 0x1f0), __n);
        memcpy((void*)puVar1[3],       *(void**)(param_2 + 0x1e8), __n);
        memcpy((void*)puVar1[5],       *(void**)(param_2 + 0x1f8), __n);
        if ((void*)puVar1[6] != nullptr) {
            memcpy((void*)puVar1[6],   *(void**)(param_2 + 0x200), __n);
            memcpy((void*)puVar1[7],   *(void**)(param_2 + 0x208), __n);
        }
        if ((void*)puVar1[8] != nullptr) {
            memcpy((void*)puVar1[8],   *(void**)(param_2 + 0x210), __n);
            memcpy((void*)puVar1[9],   *(void**)(param_2 + 0x218), __n);
            memcpy((void*)puVar1[10],  *(void**)(param_2 + 0x220), __n);
        }
    }
}

// ---- Sampler pattern callback loop ---------------------------------------

// 71000a6c30 — iterate sampler buffer, invoke callback on each entry
void FUN_71000a6c30(u64 param_1, void (*param_2)(s64, s64, u64), u64 param_3)
{
    u8* puVar2 = PTR_g_SamplerPatternCount_71052a2bc8;
    u8* puVar1 = PTR_g_SamplerBuffer_71052a2bc0;
    if (0 < *(s32*)PTR_g_SamplerPatternCount_71052a2bc8) {
        s64 lVar3 = 0;
        s64 lVar4 = 0x28;
        do {
            param_2(*(s64*)puVar1 + lVar4, *(s64*)puVar1 + lVar4 + 8, param_3);
            lVar3 = lVar3 + 1;
            lVar4 = lVar4 + 0xa8;
        } while (lVar3 < *(s32*)puVar2);
    }
}

// ---- memset+memcpy struct init -------------------------------------------

// 71000b1d10 — zero 0x10 bytes at +8, then memcpy 4 bytes of param_2 into it
void FUN_71000b1d10(s64 param_1, u32 param_2)
{
    u32 local_18[2];
    local_18[0] = param_2;
    memset((void*)(param_1 + 8), 0, 0x10);
    memcpy((void*)(param_1 + 8), local_18, 4);
}

// ---- Vtable chain null checks --------------------------------------------

// 71000c5330 — guard-null + vtable chain + field check
u64 FUN_71000c5330(s64 param_1)
{
    if (*(s64*)(param_1 + 0x90) == 0)
        return 0;
    s64 lVar1 = *(s64*)(*(s64*)(param_1 + 0x90) + 0x18);
    if (lVar1 != 0) {
        lVar1 = FUN_71000c9c60(lVar1 + 0x178);
        if (lVar1 != 0 && *(s32*)(lVar1 + 0x9c) != -1) {
            return 1;
        }
    }
    return 0;
}

// ---- StepSequenceJob constructor with extended zero fields ---------------

// 71000c8830 — StepSequenceJob base + zero 5 fields + vtable 2e50
void FUN_71000c8830(s64* param_1)
{
    new (param_1) nn::pia::common::StepSequenceJob();
    param_1[0xf] = 0;
    param_1[0xb] = 0;
    param_1[0xc] = 0;
    param_1[0xd] = 0;
    param_1[0xe] = 0;
    *param_1 = (s64)(PTR_DAT_71052a2e50 + 0x10);
    *(u16*)(param_1 + 0x10) = 0;
    param_1[0x11] = 0;
    *(u8*)(param_1 + 0x12) = 0;
}
