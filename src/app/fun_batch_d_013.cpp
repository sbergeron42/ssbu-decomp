#include "types.h"

// MEDIUM-tier FUN_* functions -- mixed address range, batch d-013
// Rewritten from Ghidra paste with meaningful names

// ---- External declarations -----------------------------------------------

extern "C" {
    void* memset(void*, int, u64);
    float sqrtf(float);
}

// External functions
extern void  FUN_71032e5640(s64);
extern void  FUN_71032e5560(u64);
extern void  FUN_7101af9320(u64);
extern u64   FUN_7103300dd0();
extern void  FUN_7103540560(s64);
extern void  FUN_71036b58b0(s64);
extern void  FUN_710007db90();
extern u64   FUN_71037223f0(s64);
extern u64   FUN_7103721ea0(s64, u8);
extern u64   FUN_71037228b0(s64, u64, u64, u64);
extern void  noop_71037aeec0(s64);
extern void  FUN_71037af350(s64);

// External data
extern s64   DAT_710532e7c8;
extern s64   DAT_710532e840;
extern s64   DAT_7105331f20;

// nn::nfp opaque types and functions
namespace nn { namespace nfp {
    struct DeviceHandle;
    struct ApplicationAreaCreateInfo;
    extern u64 StartDetection(DeviceHandle*);
    extern u64 StopDetection(DeviceHandle*);
    extern u64 Mount(DeviceHandle*, int);
    extern u64 Unmount(DeviceHandle*);
    extern u64 OpenApplicationArea(DeviceHandle*, u32);
    extern u64 GetApplicationArea(void*, u64*, DeviceHandle*, u64);
    extern u64 Flush(DeviceHandle*);
    extern u64 Restore(DeviceHandle*);
    extern u64 CreateApplicationArea(DeviceHandle*, ApplicationAreaCreateInfo*);
}}

// ---- Functions ---------------------------------------------------------------

// 0x71033011cc -- wrapper: FUN_7103300dd0()
u64 FUN_71033011cc(void) { return FUN_7103300dd0(); }

// 0x71033646c0 -- vtable dispatch via x8 at +0x10, return 0
u32 FUN_71033646c0(s64 *obj)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (*(void(*)(s64*))(*(s64*)(*in_x8 + 0x10)))(in_x8);
    return 0;
}

// 0x71033669a0 -- wrapper: FUN_71032e5640(global), return 0
u64 FUN_71033669a0(void) { FUN_71032e5640(DAT_710532e7c8); return 0; }

// 0x7103366b00 -- wrapper: FUN_71032e5560(*(global+8)), return 0
u64 FUN_7103366b00(void) { FUN_71032e5560(*(u64*)(DAT_710532e7c8 + 8)); return 0; }

// 0x7103367c40 -- store value at ctx+0x10, call through nested globals
u64 FUN_7103367c40(u64 value, s64 ctx)
{
    *(u64*)(ctx + 0x10) = value;
    FUN_7101af9320(*(u64*)(*(s64*)(*(s64*)(DAT_710532e840 + 8) + 0xb8) + 0x80));
    return 0;
}

// 0x7103342850 -- clear u16 then memset 0x2041e8-byte region
void FUN_7103342850(u16 *data)
{
    *data = 0;
    memset(data + 4, 0, 0x2041e8);
}

// 0x71036b3db0 -- check string field, update entry if non-empty
void FUN_71036b3db0(s64 param_1, u64 param_2)
{
    s64 entry = *(s64*)(param_1 + 0x158);
    if (*(char*)(*(s64*)(entry + 0x18)) != '\0') {
        FUN_71036b58b0(entry);
        *(u64*)(entry + 0xd8) = param_2;
    }
}

// 0x7103762200 -- conditional copy of two u32 fields to dest
void FUN_7103762200(s64 param_1, s64 *param_2)
{
    FUN_710007db90();
    if (*(char*)(param_1 + 0x5c) == '\0') {
        s64 dest = *param_2;
        u32 field_54 = *(u32*)(param_1 + 0x54);
        *(u32*)(dest + 0xc) = *(u32*)(param_1 + 0x50);
        *(u32*)(dest + 0x10) = field_54;
    }
}

// 0x7103720640 -- reset color to 0xffffff if changed
void FUN_7103720640(s64 param_1)
{
    if (*(s32*)(param_1 + 0x10) != 0xffffff) {
        FUN_7103540560(DAT_7105331f20);
        *(u32*)(param_1 + 0x10) = 0xffffff;
    }
}

// 0x7103720de0 -- wrapper: FUN_71037223f0(param_2 + 0xc)
u64 FUN_7103720de0(u64 param_1, s64 param_2) { return FUN_71037223f0(param_2 + 0xc); }

// 0x7103720e00 -- wrapper: FUN_7103721ea0(param_2+0xc, byte at +0x158)
u64 FUN_7103720e00(u64 param_1, s64 param_2)
{
    return FUN_7103721ea0(param_2 + 0xc, *(u8*)(param_2 + 0x158)) & 0xFFFFFFFF;
}

// 0x7103720ee0 -- wrapper: FUN_71037228b0 with three u64 fields
u64 FUN_7103720ee0(u64 param_1, s64 param_2)
{
    return FUN_71037228b0(param_2 + 0xc,
                          *(u64*)(param_2 + 0x110),
                          *(u64*)(param_2 + 0x118),
                          *(u64*)(param_2 + 0x120)) & 0xFFFFFFFF;
}

// 0x71037153d8 -- call function pointer, return result
u64 FUN_71037153d8(u32 (*func)()) { return func(); }

// 0x71037162f0 -- nn::nfp::StartDetection wrapper
u64 FUN_71037162f0(s64 self) { return nn::nfp::StartDetection((nn::nfp::DeviceHandle*)(self + 0x84)); }

// 0x7103716310 -- nn::nfp::StopDetection wrapper
u64 FUN_7103716310(s64 self) { return nn::nfp::StopDetection((nn::nfp::DeviceHandle*)(self + 0x84)); }

// 0x7103716330 -- nn::nfp::Mount with mode 0
u64 FUN_7103716330(s64 self) { return nn::nfp::Mount((nn::nfp::DeviceHandle*)(self + 0x84), 0); }

// 0x7103716350 -- nn::nfp::Unmount wrapper
u64 FUN_7103716350(s64 self) { return nn::nfp::Unmount((nn::nfp::DeviceHandle*)(self + 0x84)); }

// 0x71037164a0 -- nn::nfp::OpenApplicationArea wrapper
u64 FUN_71037164a0(s64 self, u32 area_id)
{
    return nn::nfp::OpenApplicationArea((nn::nfp::DeviceHandle*)(self + 0x84), area_id) & 0xFFFFFFFF;
}

// 0x7103716720 -- nn::nfp::GetApplicationArea wrapper
u64 FUN_7103716720(s64 self, void *buf, u64 *out_size, u64 buf_size)
{
    return nn::nfp::GetApplicationArea(buf, out_size, (nn::nfp::DeviceHandle*)(self + 0x84), buf_size) & 0xFFFFFFFF;
}

// 0x7103716b20 -- nn::nfp::Flush wrapper
u64 FUN_7103716b20(s64 self) { return nn::nfp::Flush((nn::nfp::DeviceHandle*)(self + 0x84)); }

// 0x7103716b40 -- nn::nfp::Restore wrapper
u64 FUN_7103716b40(s64 self) { return nn::nfp::Restore((nn::nfp::DeviceHandle*)(self + 0x84)); }

// 0x7103716b60 -- nn::nfp::CreateApplicationArea wrapper
u64 FUN_7103716b60(s64 self, nn::nfp::ApplicationAreaCreateInfo *info)
{
    return nn::nfp::CreateApplicationArea((nn::nfp::DeviceHandle*)(self + 0x84), info) & 0xFFFFFFFF;
}

// 0x71037aeb30 -- store two u32 values to output array
void FUN_71037aeb30(u32 x, u32 y, u32 *out)
{
    *out = x;
    out[1] = y;
}

// 0x71037aedd0 -- 2D float dot product
float FUN_71037aedd0(float *a, float *b)
{
    return a[0] * b[0] + a[1] * b[1];
}

// 0x71037aeed0 -- store two u32 values to output array
void FUN_71037aeed0(u32 x, u32 y, u32 *out)
{
    *out = x;
    out[1] = y;
}

// 0x71037aef00 -- compute 2D vector magnitude (result unused)
void FUN_71037aef00(float *vec) { sqrtf(vec[0] * vec[0] + vec[1] * vec[1]); }

// 0x71037aef40 -- zero two u32 fields
void FUN_71037aef40(u32 *out) { *out = 0; out[1] = 0; }

// 0x71037af290 -- call noop_71037aeec0 on two consecutive 8-byte fields
void FUN_71037af290(s64 param_1)
{
    noop_71037aeec0(param_1);
    noop_71037aeec0(param_1 + 8);
}

// 0x71037af320 -- call noop_71037aeec0 at +0, FUN_71037af350 at +8
void FUN_71037af320(s64 param_1)
{
    noop_71037aeec0(param_1);
    FUN_71037af350(param_1 + 8);
}

// 0x71037af510 -- return u32 at +8
u64 FUN_71037af510(s64 param_1) { return *(u32*)(param_1 + 8); }
