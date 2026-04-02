#include "types.h"

// MEDIUM-tier FUN_* functions — mixed address range, batch d-013
// Pool-d worker: auto-generated from Ghidra decompilation

// ---- External declarations -----------------------------------------------

extern "C" {
    void* memset(void*, int, u64);
    float sqrtf(float);
}

// External functions
extern void  FUN_71032e5640(s64);
extern void  FUN_71032e5560(u64);
extern void  FUN_7101af9320(u64);
extern u32   FUN_7103300dd0();
extern void  FUN_7103540560(s64);
extern void  FUN_71036b58b0(s64);
extern void  FUN_710007db90();
extern u32   FUN_71037223f0(s64);
extern u32   FUN_7103721ea0(s64, u8);
extern u32   FUN_71037228b0(s64, u64, u64, u64);
extern void  FUN_71037aeec0(s64);
extern void  FUN_71037af350(s64);

// External data
extern s64   DAT_710532e7c8;
extern s64   DAT_710532e840;
extern s64   DAT_7105331f20;

// nn::nfp opaque types and functions
namespace nn { namespace nfp {
    struct DeviceHandle;
    struct ApplicationAreaCreateInfo;
    extern u32 StartDetection(DeviceHandle*);
    extern u32 StopDetection(DeviceHandle*);
    extern u32 Mount(DeviceHandle*, int);
    extern u32 Unmount(DeviceHandle*);
    extern u32 OpenApplicationArea(DeviceHandle*, u32);
    extern u32 GetApplicationArea(void*, u64*, DeviceHandle*, u64);
    extern u32 Flush(DeviceHandle*);
    extern u32 Restore(DeviceHandle*);
    extern u32 CreateApplicationArea(DeviceHandle*, ApplicationAreaCreateInfo*);
}}

// ---- Functions ---------------------------------------------------------------

// 0x71033011cc — wrapper: FUN_7103300dd0() (36 bytes)
u32 FUN_71033011cc(void) { return FUN_7103300dd0(); }

// 0x71033646c0 — vtable call at +0x10, return 0 (48 bytes)
u64 FUN_71033646c0(s64 *param_1)
{
    (*(void(*)(s64*))(*(s64*)(*param_1 + 0x10)))(param_1);
    return 0;
}

// 0x71033669a0 — wrapper: FUN_71032e5640(global), return 0 (32 bytes)
u64 FUN_71033669a0(void) { FUN_71032e5640(DAT_710532e7c8); return 0; }

// 0x7103366b00 — wrapper: FUN_71032e5560(*(global+8)), return 0 (48 bytes)
u64 FUN_7103366b00(void) { FUN_71032e5560(*(u64*)(DAT_710532e7c8 + 8)); return 0; }

// 0x7103367c40 — store param_1 at p2+0x10, vtable call through nested globals (48 bytes)
u64 FUN_7103367c40(u64 param_1, s64 param_2)
{
    *(u64*)(param_2 + 0x10) = param_1;
    FUN_7101af9320(*(u64*)(*(s64*)(*(s64*)(DAT_710532e840 + 8) + 0xb8) + 0x80));
    return 0;
}

// 0x7103342850 — clear u16 then memset large region (48 bytes)
void FUN_7103342850(u16 *param_1)
{
    *param_1 = 0;
    memset(param_1 + 4, 0, 0x2041e8);
}

// 0x71036b3db0 — conditional: check string then update field (64 bytes)
void FUN_71036b3db0(s64 param_1, u64 param_2)
{
    s64 lVar1 = *(s64*)(param_1 + 0x158);
    if (*(char*)(*(s64*)(lVar1 + 0x18)) != '\0') {
        FUN_71036b58b0(lVar1);
        *(u64*)(lVar1 + 0xd8) = param_2;
    }
}

// 0x7103762200 — conditional copy of two u32 fields via pointer (64 bytes)
void FUN_7103762200(s64 param_1, s64 *param_2)
{
    FUN_710007db90();
    if (*(char*)(param_1 + 0x5c) == '\0') {
        s64 lVar2 = *param_2;
        u32 uVar1 = *(u32*)(param_1 + 0x54);
        *(u32*)(lVar2 + 0xc) = *(u32*)(param_1 + 0x50);
        *(u32*)(lVar2 + 0x10) = uVar1;
    }
}

// 0x7103720640 — conditional reset of 0xffffff (64 bytes)
void FUN_7103720640(s64 param_1)
{
    if (*(s32*)(param_1 + 0x10) != 0xffffff) {
        FUN_7103540560(DAT_7105331f20);
        *(u32*)(param_1 + 0x10) = 0xffffff;
    }
}

// 0x7103720de0 — wrapper: FUN_71037223f0(param_2 + 0xc) (32 bytes)
u32 FUN_7103720de0(u64 param_1, s64 param_2) { return FUN_71037223f0(param_2 + 0xc); }

// 0x7103720e00 — wrapper: FUN_7103721ea0(param_2+0xc, byte at +0x158) (48 bytes)
u32 FUN_7103720e00(u64 param_1, s64 param_2)
{
    return FUN_7103721ea0(param_2 + 0xc, *(u8*)(param_2 + 0x158));
}

// 0x7103720ee0 — wrapper: FUN_71037228b0 with three u64 fields (48 bytes)
u32 FUN_7103720ee0(u64 param_1, s64 param_2)
{
    return FUN_71037228b0(param_2 + 0xc,
                          *(u64*)(param_2 + 0x110),
                          *(u64*)(param_2 + 0x118),
                          *(u64*)(param_2 + 0x120));
}

// 0x71037153d8 — call function pointer with no args (24 bytes)
u32 FUN_71037153d8(u32 (*param_1)()) { return param_1(); }

// 0x71037162f0 — nn::nfp::StartDetection (32 bytes)
u32 FUN_71037162f0(s64 param_1) { return nn::nfp::StartDetection((nn::nfp::DeviceHandle*)(param_1 + 0x84)); }

// 0x7103716310 — nn::nfp::StopDetection (32 bytes)
u32 FUN_7103716310(s64 param_1) { return nn::nfp::StopDetection((nn::nfp::DeviceHandle*)(param_1 + 0x84)); }

// 0x7103716330 — nn::nfp::Mount with mode 0 (32 bytes)
u32 FUN_7103716330(s64 param_1) { return nn::nfp::Mount((nn::nfp::DeviceHandle*)(param_1 + 0x84), 0); }

// 0x7103716350 — nn::nfp::Unmount (32 bytes)
u32 FUN_7103716350(s64 param_1) { return nn::nfp::Unmount((nn::nfp::DeviceHandle*)(param_1 + 0x84)); }

// 0x71037164a0 — nn::nfp::OpenApplicationArea (48 bytes)
u32 FUN_71037164a0(s64 param_1, u32 param_2)
{
    return nn::nfp::OpenApplicationArea((nn::nfp::DeviceHandle*)(param_1 + 0x84), param_2);
}

// 0x7103716720 — nn::nfp::GetApplicationArea (64 bytes)
u32 FUN_7103716720(s64 param_1, void *param_2, u64 *param_3, u64 param_4)
{
    return nn::nfp::GetApplicationArea(param_2, param_3, (nn::nfp::DeviceHandle*)(param_1 + 0x84), param_4);
}

// 0x7103716b20 — nn::nfp::Flush (32 bytes)
u32 FUN_7103716b20(s64 param_1) { return nn::nfp::Flush((nn::nfp::DeviceHandle*)(param_1 + 0x84)); }

// 0x7103716b40 — nn::nfp::Restore (32 bytes)
u32 FUN_7103716b40(s64 param_1) { return nn::nfp::Restore((nn::nfp::DeviceHandle*)(param_1 + 0x84)); }

// 0x7103716b60 — nn::nfp::CreateApplicationArea (48 bytes)
u32 FUN_7103716b60(s64 param_1, nn::nfp::ApplicationAreaCreateInfo *param_2)
{
    return nn::nfp::CreateApplicationArea((nn::nfp::DeviceHandle*)(param_1 + 0x84), param_2);
}

// 0x71037aeb30 — store two u32 params to array (48 bytes)
void FUN_71037aeb30(u32 param_1, u32 param_2, u32 *param_3)
{
    *param_3 = param_1;
    param_3[1] = param_2;
}

// 0x71037aedd0 — 2D float dot product (64 bytes)
float FUN_71037aedd0(float *param_1, float *param_2)
{
    return *param_1 * *param_2 + param_1[1] * param_2[1];
}

// 0x71037aeed0 — store two u32 params to array (48 bytes)
void FUN_71037aeed0(u32 param_1, u32 param_2, u32 *param_3)
{
    *param_3 = param_1;
    param_3[1] = param_2;
}

// 0x71037aef00 — sqrtf(x^2 + y^2), result discarded (64 bytes)
void FUN_71037aef00(float *param_1) { sqrtf(*param_1 * *param_1 + param_1[1] * param_1[1]); }

// 0x71037aef40 — clear two u32 fields (32 bytes)
void FUN_71037aef40(u32 *param_1) { *param_1 = 0; param_1[1] = 0; }

// 0x71037af290 — call FUN_71037aeec0 at +0 and +8 (48 bytes)
void FUN_71037af290(s64 param_1)
{
    FUN_71037aeec0(param_1);
    FUN_71037aeec0(param_1 + 8);
}

// 0x71037af320 — call FUN_71037aeec0 then FUN_71037af350 at +8 (48 bytes)
void FUN_71037af320(s64 param_1)
{
    FUN_71037aeec0(param_1);
    FUN_71037af350(param_1 + 8);
}

// 0x71037af510 — return *(u32*)(p+8) (32 bytes)
u32 FUN_71037af510(s64 param_1) { return *(u32*)(param_1 + 8); }
