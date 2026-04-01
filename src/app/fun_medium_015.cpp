#include "types.h"

// MEDIUM-tier FUN_* functions — mixed address range, batch 16
// Pool-d worker: auto-generated from Ghidra decompilation

// ---- External declarations -----------------------------------------------

extern "C" int   __cxa_guard_acquire(u64*);
extern "C" void  __cxa_guard_release(u64*);

// nn namespaces
namespace nn {
namespace os {
    struct MutexType;
    void InitializeMutex(MutexType*, bool, int);
}
namespace mem {
    struct NumberLineAllocator;
    // Allocate(allocator, out_ptr) — returns 0 on success
    int NumberLineAllocator_Allocate(NumberLineAllocator*, u64*);
}
}

// External C functions
extern "C" void  FUN_7100078b20();
extern "C" void  FUN_7100081d20(u64, u64, u64, u64);
extern "C" void  FUN_7100082590(u64, u64*, u64, u64);
extern "C" void  FUN_7100083da0(u64, u64*, u64, u64);

// External data (cxa_guard guards / singleton storage)
extern u8  PTR_DAT_71052a28f0[];  // outer guard (FUN_710007d360)
extern u8  PTR_DAT_71052a28f8[];  // outer data  (FUN_710007d360)
extern u8  PTR_DAT_71052a2890[];  // inner guard  (FUN_710007d360)
extern u8  PTR_DAT_71052a2898[];  // inner data   (FUN_710007d360)
extern u8  PTR_DAT_71052a2900[];  // guard        (FUN_710007d410)
extern u8  PTR_DAT_71052a2908[];  // data         (FUN_710007d410)
extern u8  PTR_DAT_71052a2918[];  // guard        (FUN_710007d820)
extern u8  PTR_DAT_71052a2920[];  // data         (FUN_710007d820)
extern u8  PTR_DAT_71052a2958[];  // data ptr     (FUN_71000824a0)
extern u8  PTR_DAT_71052a2988[];  // data ptr     (FUN_7100083cb0)
extern u8  PTR_DAT_71052a2710[];  // outer guard  (FUN_7100065550)
extern u8  PTR_DAT_71052a2708[];  // outer data   (FUN_7100065550)
extern u8  PTR_DAT_71052a2718[];  // inner guard  (FUN_7100065550)
extern u8  PTR_DAT_71052a2720[];  // inner data   (FUN_7100065550)

// ---- cxa_guard singletons ------------------------------------------------

// 710007d360 — nested cxa_guard: outer 28f0/28f8 → inner 2890/2898
u8* FUN_710007d360()
{
    s32 iVar1;
    if ((*PTR_DAT_71052a28f0 & 1) == 0) {
        iVar1 = __cxa_guard_acquire((u64*)PTR_DAT_71052a28f0);
        if (iVar1 != 0) {
            if ((*PTR_DAT_71052a2890 & 1) == 0) {
                iVar1 = __cxa_guard_acquire((u64*)PTR_DAT_71052a2890);
                if (iVar1 != 0) {
                    *(u64*)PTR_DAT_71052a2898 = 0;
                    __cxa_guard_release((u64*)PTR_DAT_71052a2890);
                }
            }
            *(u8**)PTR_DAT_71052a28f8 = PTR_DAT_71052a2898 + 0x10;
            __cxa_guard_release((u64*)PTR_DAT_71052a28f0);
        }
    }
    return PTR_DAT_71052a28f8;
}

// 710007d410 — simple cxa_guard: guard 2900, data 2908
u8* FUN_710007d410()
{
    s32 iVar1;
    if ((*PTR_DAT_71052a2900 & 1) == 0) {
        iVar1 = __cxa_guard_acquire((u64*)PTR_DAT_71052a2900);
        if (iVar1 != 0) {
            *(u64*)PTR_DAT_71052a2908 = 0;
            __cxa_guard_release((u64*)PTR_DAT_71052a2900);
        }
    }
    return PTR_DAT_71052a2908;
}

// 710007d820 — simple cxa_guard: guard 2918, data 2920
u8* FUN_710007d820()
{
    s32 iVar1;
    if ((*PTR_DAT_71052a2918 & 1) == 0) {
        iVar1 = __cxa_guard_acquire((u64*)PTR_DAT_71052a2918);
        if (iVar1 != 0) {
            *(u64*)PTR_DAT_71052a2920 = 0;
            __cxa_guard_release((u64*)PTR_DAT_71052a2918);
        }
    }
    return PTR_DAT_71052a2920;
}

// 7100065550 — nested cxa_guard: outer 2710/2708 → inner 2718/2720
u8* FUN_7100065550()
{
    s32 iVar1;
    if ((*PTR_DAT_71052a2710 & 1) == 0) {
        iVar1 = __cxa_guard_acquire((u64*)PTR_DAT_71052a2710);
        if (iVar1 != 0) {
            if ((*PTR_DAT_71052a2718 & 1) == 0) {
                iVar1 = __cxa_guard_acquire((u64*)PTR_DAT_71052a2718);
                if (iVar1 != 0) {
                    *(u64*)PTR_DAT_71052a2720 = 0;
                    __cxa_guard_release((u64*)PTR_DAT_71052a2718);
                }
            }
            *(u8**)PTR_DAT_71052a2708 = PTR_DAT_71052a2720 + 0x10;
            __cxa_guard_release((u64*)PTR_DAT_71052a2710);
        }
    }
    return PTR_DAT_71052a2708;
}

// ---- Bit-packing / float helpers -----------------------------------------

// 7100081cd0 — pack param_2/3/4 into a 64-bit word, then call FUN_7100081d20
void FUN_7100081cd0(u64 param_1, u64 param_2, u64 param_3, u64 param_4)
{
    u64 packed = (param_3 << 0x30) | (param_2 & 0xffffffff) | ((u64)(param_4 & 0xffff) << 0x20);
    FUN_7100081d20(param_1, param_2, param_3, packed);
}

// 71000824a0 — call FUN_7100078b20, store constants + data ptr
void FUN_71000824a0(u64 param_1)
{
    FUN_7100078b20();
    *(u32*)(param_1 + 0)  = 0x7f7fffff;
    *(u32*)(param_1 + 4)  = 0;
    *(u32*)(param_1 + 8)  = 4;
    *(u8**)(param_1 + 16) = PTR_DAT_71052a2958 + 0x1000000;
}

// 7100083cb0 — same as 71000824a0 but with PTR_DAT_71052a2988
void FUN_7100083cb0(u64 param_1)
{
    FUN_7100078b20();
    *(u32*)(param_1 + 0)  = 0x7f7fffff;
    *(u32*)(param_1 + 4)  = 0;
    *(u32*)(param_1 + 8)  = 4;
    *(u8**)(param_1 + 16) = PTR_DAT_71052a2988 + 0x1000000;
}

// 7100082550 — zero two locals, call FUN_7100082590, return float subtraction
f32 FUN_7100082550(u64 param_1, u64 param_2, u64 param_3)
{
    u64 local_18 = 0;
    u64 local_20 = 0;
    FUN_7100082590(param_1, &local_20, param_2, param_3);
    return (f32)local_18 - (f32)local_20;
}

// 7100083d60 — same pattern as 7100082550 but calls FUN_7100083da0
f32 FUN_7100083d60(u64 param_1, u64 param_2, u64 param_3)
{
    u64 local_18 = 0;
    u64 local_20 = 0;
    FUN_7100083da0(param_1, &local_20, param_2, param_3);
    return (f32)local_18 - (f32)local_20;
}

// ---- Struct init helpers --------------------------------------------------

// 7100066660 — write param_1/param_2 as s32 into two structs at param_3/param_4
void FUN_7100066660(f32 param_1, f32 param_2, s32* param_3, s32* param_4)
{
    *param_4                    = 0;
    *(s32*)(param_4 + 1)        = (s32)param_1;
    *(s32*)((s64)param_4 + 0xc) = (s32)param_2;
    *param_3                    = 0;
    *(f32*)(param_3 + 1)        = param_1;
    *(f32*)((s64)param_3 + 0xc) = param_2;
}

// 710003a9c0 — init mutex and zero struct fields
void FUN_710003a9c0(u64* param_1)
{
    *param_1 = 0;
    nn::os::InitializeMutex((nn::os::MutexType*)(param_1 + 3), false, 0);
    *(u64*)(param_1 + 1) = 0;
    *(u64*)(param_1 + 2) = 0;
}

// 710003aa50 — NumberLineAllocator::Allocate + conditional return
u64 FUN_710003aa50(nn::mem::NumberLineAllocator* param_1)
{
    u64 local_14 = 0;
    int iVar1 = nn::mem::NumberLineAllocator_Allocate(param_1, &local_14);
    if (iVar1 != 0)
        return 0;
    return local_14;
}
