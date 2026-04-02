#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7103 address range, batch d-005
// Pool-d worker: auto-generated from Ghidra decompilation

// ---- External declarations -----------------------------------------------

extern "C" {
    int  __cxa_guard_acquire(u64*);
    void __cxa_guard_release(u64*);
}

namespace nn { namespace nfp {
    struct DeviceHandle;
    struct TagInfo;
    struct RegisterInfo;
    struct CommonInfo;
    struct ModelInfo;
    struct ApplicationAreaCreateInfo;
    extern u32 SetApplicationArea(DeviceHandle*, void*, u64);
    extern u32 GetTagInfo(TagInfo*, DeviceHandle*);
    extern u32 GetRegisterInfo(RegisterInfo*, DeviceHandle*);
    extern u32 GetCommonInfo(CommonInfo*, DeviceHandle*);
    extern u32 GetModelInfo(ModelInfo*, DeviceHandle*);
    extern u32 RecreateApplicationArea(DeviceHandle*, ApplicationAreaCreateInfo*);
}}

// External data (guard shared with d-004: DAT_710593aa98, DAT_710593aaa0, DAT_710593aaa8, DAT_710593aab0)
extern u8 DAT_710593aa98[];
extern u8 DAT_710593aaa0[];
extern u8 DAT_710593aaa8[];
extern u8 DAT_710593aab0[];

// FUN_710378d8f0 guard data
extern u8 DAT_710593aab8[];
extern u8 DAT_710593aac0[];

// FUN_7103791100 guard data
extern u8 DAT_710593ab08[];
extern u8 DAT_710593ab10[];

// FUN_7103799b10 guard data
extern u8 DAT_710593ab78[];
extern u8 DAT_710593ab80[];
extern u8 DAT_710593ab88[];
extern u8 DAT_710593ab90[];
extern u8 DAT_710593ab98[];
extern u8 DAT_710593aba0[];
extern u8 DAT_710593aba8[];
extern u8 DAT_710593abb0[];

// ---- Functions ---------------------------------------------------------------

// 0x710357a0dc — vtable call at 0x168 (no args), void return (228 bytes)
void FUN_710357a0dc(s64 *param_1)
{
    (*(void(*)())(*param_1 + 0x168))();
}

// 0x710378d8f0 — triple-nested guard init, returns &DAT_710593aac0 (224 bytes)
u64 *FUN_710378d8f0(void)
{
    s32 iVar1;

    if (((*(u64*)DAT_710593aab8 & 1) == 0) &&
        (iVar1 = __cxa_guard_acquire((u64*)DAT_710593aab8), iVar1 != 0)) {
        if (((*(u64*)DAT_710593aa98 & 1) == 0) &&
            (iVar1 = __cxa_guard_acquire((u64*)DAT_710593aa98), iVar1 != 0)) {
            if (((*(u64*)DAT_710593aaa0 & 1) == 0) &&
                (iVar1 = __cxa_guard_acquire((u64*)DAT_710593aaa0), iVar1 != 0)) {
                *(u64*)DAT_710593aaa8 = 0;
                __cxa_guard_release((u64*)DAT_710593aaa0);
            }
            *(u8**)DAT_710593aab0 = DAT_710593aaa8;
            __cxa_guard_release((u64*)DAT_710593aa98);
        }
        *(u8**)DAT_710593aac0 = DAT_710593aab0;
        __cxa_guard_release((u64*)DAT_710593aab8);
    }
    return (u64*)DAT_710593aac0;
}

// 0x7103791100 — triple-nested guard init, returns &DAT_710593ab10 (240 bytes)
u64 *FUN_7103791100(void)
{
    s32 iVar1;

    if (((*(u64*)DAT_710593ab08 & 1) == 0) &&
        (iVar1 = __cxa_guard_acquire((u64*)DAT_710593ab08), iVar1 != 0)) {
        if (((*(u64*)DAT_710593aa98 & 1) == 0) &&
            (iVar1 = __cxa_guard_acquire((u64*)DAT_710593aa98), iVar1 != 0)) {
            if (((*(u64*)DAT_710593aaa0 & 1) == 0) &&
                (iVar1 = __cxa_guard_acquire((u64*)DAT_710593aaa0), iVar1 != 0)) {
                *(u64*)DAT_710593aaa8 = 0;
                __cxa_guard_release((u64*)DAT_710593aaa0);
            }
            *(u8**)DAT_710593aab0 = DAT_710593aaa8;
            __cxa_guard_release((u64*)DAT_710593aa98);
        }
        *(u8**)DAT_710593ab10 = DAT_710593aab0;
        __cxa_guard_release((u64*)DAT_710593ab08);
    }
    return (u64*)DAT_710593ab10;
}

// 0x7103716880 — nn::nfp::SetApplicationArea wrapper (256 bytes)
u64 FUN_7103716880(s64 param_1, void *param_2, u64 param_3)
{
    return nn::nfp::SetApplicationArea((nn::nfp::DeviceHandle*)(param_1 + 0x84), param_2, param_3);
}

// 0x7103716b80 — nn::nfp::GetTagInfo wrapper (256 bytes)
u64 FUN_7103716b80(s64 param_1, nn::nfp::TagInfo *param_2)
{
    return nn::nfp::GetTagInfo(param_2, (nn::nfp::DeviceHandle*)(param_1 + 0x84));
}

// 0x7103716cd0 — nn::nfp::GetRegisterInfo wrapper (256 bytes)
u64 FUN_7103716cd0(s64 param_1, nn::nfp::RegisterInfo *param_2)
{
    return nn::nfp::GetRegisterInfo(param_2, (nn::nfp::DeviceHandle*)(param_1 + 0x84));
}

// 0x7103716e20 — nn::nfp::GetCommonInfo wrapper (256 bytes)
u64 FUN_7103716e20(s64 param_1, nn::nfp::CommonInfo *param_2)
{
    return nn::nfp::GetCommonInfo(param_2, (nn::nfp::DeviceHandle*)(param_1 + 0x84));
}

// 0x7103716f70 — nn::nfp::GetModelInfo wrapper (256 bytes)
u64 FUN_7103716f70(s64 param_1, nn::nfp::ModelInfo *param_2)
{
    return nn::nfp::GetModelInfo(param_2, (nn::nfp::DeviceHandle*)(param_1 + 0x84));
}

// 0x71037169d0 — nn::nfp::RecreateApplicationArea wrapper (256 bytes)
u64 FUN_71037169d0(s64 param_1, nn::nfp::ApplicationAreaCreateInfo *param_2)
{
    return nn::nfp::RecreateApplicationArea((nn::nfp::DeviceHandle*)(param_1 + 0x84), param_2);
}

// 0x710397a620 — vtable call at 0x1b0, return bool: iVar != 0 (256 bytes)
u8 FUN_710397a620(s64 *param_1)
{
    s32 iVar1 = (*(s32(*)())(*param_1 + 0x1b0))();
    return (u8)(iVar1 != 0);
}

// 0x710335c924 — vtable call at 0x320 (no args), return 0 (272 bytes)
u64 FUN_710335c924(s64 *param_1)
{
    (*(void(*)())(*param_1 + 0x320))();
    return 0;
}

// 0x7103799b10 — quad-nested guard init, returns &DAT_710593abb0 (272 bytes)
u64 *FUN_7103799b10(void)
{
    s32 iVar1;

    if (((*(u64*)DAT_710593ab78 & 1) == 0) &&
        (iVar1 = __cxa_guard_acquire((u64*)DAT_710593ab78), iVar1 != 0)) {
        if (((*(u64*)DAT_710593ab80 & 1) == 0) &&
            (iVar1 = __cxa_guard_acquire((u64*)DAT_710593ab80), iVar1 != 0)) {
            if (((*(u64*)DAT_710593ab88 & 1) == 0) &&
                (iVar1 = __cxa_guard_acquire((u64*)DAT_710593ab88), iVar1 != 0)) {
                if (((*(u64*)DAT_710593ab90 & 1) == 0) &&
                    (iVar1 = __cxa_guard_acquire((u64*)DAT_710593ab90), iVar1 != 0)) {
                    *(u64*)DAT_710593ab98 = 0;
                    __cxa_guard_release((u64*)DAT_710593ab90);
                }
                *(u8**)DAT_710593aba0 = DAT_710593ab98;
                __cxa_guard_release((u64*)DAT_710593ab88);
            }
            *(u8**)DAT_710593aba8 = DAT_710593aba0;
            __cxa_guard_release((u64*)DAT_710593ab80);
        }
        *(u8**)DAT_710593abb0 = DAT_710593aba8;
        __cxa_guard_release((u64*)DAT_710593ab78);
    }
    return (u64*)DAT_710593abb0;
}
