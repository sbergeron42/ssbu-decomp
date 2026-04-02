#include "types.h"

// placement new
inline void* operator new(unsigned long, void* p) noexcept { return p; }
inline void  operator delete(void*, void*) noexcept {}

// MEDIUM-tier FUN_* functions -- mixed address range, batch 22
// Pool-d worker: auto-generated from Ghidra decompilation

// ---- External declarations -----------------------------------------------

extern "C" int  __cxa_guard_acquire(u64*);
extern "C" void __cxa_guard_release(u64*);

// nn namespaces
namespace nn {
namespace pia {
namespace common {
    struct StepSequenceJob { StepSequenceJob(); };
}
namespace nat {
namespace NatDetecter {
    void SetCurrentPort(u32);
}
}
}
namespace err {
    struct Result { u32 m_Value; };
    struct ErrorResultVariant {
        ErrorResultVariant();
        ErrorResultVariant& operator=(const Result&);
    };
}
}

// External C functions
extern "C" u16  FUN_71000c87e0();
extern "C" u32  FUN_71000c75f0();
extern "C" void FUN_71000c81f0(u32*, s64);
extern "C" void FUN_71000bcf30(s32*, u32*);

// External data
extern u8  PTR_DAT_71052a2f18[];   // vtable (FUN_71000d0910)
extern u8  PTR_DAT_71052a3f78[];   // vtable (FUN_71000d38f0)
extern u8  PTR_DAT_71052a29c8[];   // outer guard (FUN_71000855a0)
extern u8  PTR_DAT_71052a29d0[];   // outer data  (FUN_71000855a0)
extern u8  PTR_DAT_71052a2918[];   // inner guard  (FUN_71000855a0) -- shared
extern u8  PTR_DAT_71052a2920[];   // inner data   (FUN_71000855a0) -- shared
extern u8  PTR_DAT_71052a2890[];   // guard (FUN_710007a2f0)
extern u8  PTR_DAT_71052a2898[];   // data  (FUN_710007a2f0)
extern u8  PTR_DAT_71052a26d8[];   // outer guard  (FUN_7100050840)
extern u8  PTR_DAT_71052a26e0[];   // outer data   (FUN_7100050840)
extern u8  PTR_DAT_71052a24a8[];   // mid guard    (FUN_7100050840)
extern u8  PTR_DAT_71052a24b0[];   // mid data     (FUN_7100050840)
extern u8  PTR_DAT_71052a24b8[];   // inner guard  (FUN_7100050840)
extern u8  PTR_DAT_71052a24c0[];   // inner data   (FUN_7100050840)

// ---- StepSequenceJob constructors ----------------------------------------

// 71000d0910 -- StepSequenceJob base + zero 3 fields + vtable 2f18
void FUN_71000d0910(s64* param_1)
{
    new (param_1) nn::pia::common::StepSequenceJob();
    param_1[0xd] = 0;
    param_1[0xb] = 0;
    param_1[0xc] = 0;
    *param_1 = (s64)(PTR_DAT_71052a2f18 + 0x10);
}

// 71000d38f0 -- StepSequenceJob base + zero 1 field + vtable 2f78
void FUN_71000d38f0(s64* param_1)
{
    new (param_1) nn::pia::common::StepSequenceJob();
    param_1[0xb] = 0;
    *param_1 = (s64)(PTR_DAT_71052a3f78 + 0x10);
}

// ---- Float clamp with NaN guard ------------------------------------------

// 71000664b0 -- clamp *param_3 to max(param_1, *param_3) with NaN handling
void FUN_71000664b0(f32 param_1, f32 param_2, f32* param_3)
{
    f32 fVar5 = *param_3;
    f32 fVar4 = param_1;
    if (param_1 <= fVar5) {
        fVar4 = fVar5;
    }
    bool bVar1 = false, bVar2 = false, bVar3 = false;
    if (param_1 <= fVar5) {
        bVar1 = false; bVar2 = false; bVar3 = true;
        if (fVar4 == fVar4 && param_2 == param_2) {
            bVar1 = fVar4 < param_2;
            bVar2 = fVar4 == param_2;
            bVar3 = false;
        }
    }
    if (!bVar2 && bVar1 == bVar3) {
        if (fVar4 == param_2 || !(fVar4 >= param_2)) {
            param_2 = fVar4;
        }
        *param_3 = param_2;
    }
}

// ---- cxa_guard singletons ------------------------------------------------

// 710007a2f0 -- simple cxa_guard: 2890/2898
u8* FUN_710007a2f0()
{
    s32 iVar1;
    if ((*PTR_DAT_71052a2890 & 1) == 0) {
        iVar1 = __cxa_guard_acquire((u64*)PTR_DAT_71052a2890);
        if (iVar1 != 0) {
            *(u64*)PTR_DAT_71052a2898 = 0;
            __cxa_guard_release((u64*)PTR_DAT_71052a2890);
        }
    }
    return PTR_DAT_71052a2898;
}

// 71000855a0 -- nested cxa_guard: outer 29c8/29d0, inner 2918/2920
u8* FUN_71000855a0()
{
    s32 iVar1;
    if ((*PTR_DAT_71052a29c8 & 1) == 0) {
        iVar1 = __cxa_guard_acquire((u64*)PTR_DAT_71052a29c8);
        if (iVar1 != 0) {
            if ((*PTR_DAT_71052a2918 & 1) == 0) {
                iVar1 = __cxa_guard_acquire((u64*)PTR_DAT_71052a2918);
                if (iVar1 != 0) {
                    *(u64*)PTR_DAT_71052a2920 = 0;
                    __cxa_guard_release((u64*)PTR_DAT_71052a2918);
                }
            }
            *(u8**)PTR_DAT_71052a29d0 = PTR_DAT_71052a2920;
            __cxa_guard_release((u64*)PTR_DAT_71052a29c8);
        }
    }
    return PTR_DAT_71052a29d0;
}

// 7100050840 -- triple cxa_guard: outer 26d8/26e0 → mid 24a8/24b0 → inner 24b8/24c0
u8* FUN_7100050840()
{
    s32 iVar1;
    if ((*PTR_DAT_71052a26d8 & 1) == 0) {
        iVar1 = __cxa_guard_acquire((u64*)PTR_DAT_71052a26d8);
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
            *(u8**)PTR_DAT_71052a26e0 = PTR_DAT_71052a24b0;
            __cxa_guard_release((u64*)PTR_DAT_71052a26d8);
        }
    }
    return PTR_DAT_71052a26e0;
}

// ---- NAT detection check with nn::err ------------------------------------

// 71000cb1e0 -- check if NAT port state allows new connection
bool FUN_71000cb1e0(s64 param_1)
{
    u16 uVar1 = FUN_71000c87e0();
    if ((uVar1 == 0) && (*(u32*)(param_1 + 0x18) < 3)) {
        return true;
    }
    u32 uVar2 = FUN_71000c75f0();
    if ((uVar1 < uVar2) && (*(s8*)(param_1 + 0x7f8) != '\0' && (*(u32*)(param_1 + 0x18) < 3))) {
        s32 local_30[4];
        nn::err::Result local_40[4];
        local_30[0] = 0;
        new ((void*)((u64)local_30 | 4)) nn::err::ErrorResultVariant();
        local_40[0].m_Value = 0;
        ((nn::err::ErrorResultVariant*)((u64)local_30 | 4))->operator=(local_40[0]);
        FUN_71000c81f0((u32*)local_40, param_1);
        FUN_71000bcf30(local_30, (u32*)local_40);
        return local_30[0] == 0;
    }
    nn::pia::nat::NatDetecter::SetCurrentPort((u32)uVar1);
    return false;
}
