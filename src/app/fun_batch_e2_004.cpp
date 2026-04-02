#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7103 address range, batch e2-004
// Pool-e worker: auto-generated from Ghidra decompilation

// ---- Forward declarations -----------------------------------------------

extern "C" void FUN_710347cff0(u64);
extern "C" void FUN_710348cc70(u64);
extern "C" u64  FUN_71037223f0(s64);
extern "C" u64  FUN_7103721ea0(s64, u8);

namespace nn {
    namespace nfp {
        struct DeviceHandle;
        struct ApplicationAreaCreateInfo;
        s64 StartDetection(DeviceHandle *);
        s64 StopDetection(DeviceHandle *);
        s64 Mount(DeviceHandle *, s32);
        s64 Unmount(DeviceHandle *);
        s64 Flush(DeviceHandle *);
        s64 Restore(DeviceHandle *);
        s64 CreateApplicationArea(DeviceHandle *, ApplicationAreaCreateInfo *);
    }
}

// ---- nn::nfp wrappers -----------------------------------------------
// Pattern: add x0,x0,#0x84; bl nn::nfp::XXX; and x0,x0,#0xffffffff; ldp; ret

// 0x71037162f0 — nn::nfp::StartDetection wrapper (28 bytes)
u32 FUN_71037162f0(s64 param_1)
{
    return (u32)nn::nfp::StartDetection((nn::nfp::DeviceHandle *)(param_1 + 0x84));
}

// 0x7103716310 — nn::nfp::StopDetection wrapper (28 bytes)
u32 FUN_7103716310(s64 param_1)
{
    return (u32)nn::nfp::StopDetection((nn::nfp::DeviceHandle *)(param_1 + 0x84));
}

// 0x7103716330 — nn::nfp::Mount wrapper (32 bytes)
u32 FUN_7103716330(s64 param_1)
{
    return (u32)nn::nfp::Mount((nn::nfp::DeviceHandle *)(param_1 + 0x84), 0);
}

// 0x7103716350 — nn::nfp::Unmount wrapper (28 bytes)
u32 FUN_7103716350(s64 param_1)
{
    return (u32)nn::nfp::Unmount((nn::nfp::DeviceHandle *)(param_1 + 0x84));
}

// 0x7103716b20 — nn::nfp::Flush wrapper (28 bytes)
u32 FUN_7103716b20(s64 param_1)
{
    return (u32)nn::nfp::Flush((nn::nfp::DeviceHandle *)(param_1 + 0x84));
}

// 0x7103716b40 — nn::nfp::Restore wrapper (28 bytes)
u32 FUN_7103716b40(s64 param_1)
{
    return (u32)nn::nfp::Restore((nn::nfp::DeviceHandle *)(param_1 + 0x84));
}

// 0x7103716b60 — nn::nfp::CreateApplicationArea wrapper (28 bytes)
u32 FUN_7103716b60(s64 param_1, nn::nfp::ApplicationAreaCreateInfo *param_2)
{
    return (u32)nn::nfp::CreateApplicationArea((nn::nfp::DeviceHandle *)(param_1 + 0x84), param_2);
}

// ---- simple forwarders -----------------------------------------------

// 0x710347d410 — pass param_2 (x1) to FUN_710347cff0, return 0 (32 bytes)
u32 FUN_710347d410(u64 param_1, u64 param_2)
{
    FUN_710347cff0(param_2);
    return 0;
}

// 0x710348cc50 — pass param_2 (x1) to FUN_710348cc70, return 1 (28 bytes)
u32 FUN_710348cc50(u64 param_1, u64 param_2)
{
    FUN_710348cc70(param_2);
    return 1;
}

// 0x7103720de0 — FUN_71037223f0(param_2 + 0xc), return u32 (28 bytes)
u32 FUN_7103720de0(u64 param_1, s64 param_2)
{
    return (u32)FUN_71037223f0(param_2 + 0x0c);
}

// 0x7103720e00 — FUN_7103721ea0(param_2+0xc, *(u8*)(param_2+0x158)), return u32 (32 bytes)
u32 FUN_7103720e00(u64 param_1, s64 param_2)
{
    return (u32)FUN_7103721ea0(param_2 + 0x0c, *(u8 *)(param_2 + 0x158));
}

// ---- struct getters (stack-spill pattern, 24-28 bytes each) -----------------------------------------------
// Note: original uses sub/str/ldr/add stack spill — compiles correctly, may not verify

// 0x71037aef40 — zero-init two u32 fields (28 bytes)
void FUN_71037aef40(u32 *param_1)
{
    param_1[0] = 0;
    param_1[1] = 0;
}

// 0x71037af510 — return *(u32 *)(param_1 + 0x8) (20 bytes)
u32 FUN_71037af510(s64 param_1)
{
    return *(u32 *)(param_1 + 0x8);
}

// 0x71037b3130 — return *(u64 *)(param_1 + 0x60) (24 bytes)
u64 FUN_71037b3130(s64 param_1)
{
    return *(u64 *)(param_1 + 0x60);
}

// 0x71037b3150 — return *(u64 *)(param_1 + 0x68) (24 bytes)
u64 FUN_71037b3150(s64 param_1)
{
    return *(u64 *)(param_1 + 0x68);
}

// 0x71037b3600 — return bit 5 of *(u16 *)(param_1 + 0x4) (28 bytes)
u16 FUN_71037b3600(s64 param_1)
{
    return (*(u16 *)(param_1 + 0x4) >> 5) & 1;
}

// 0x71037b4430 — return *(s32 *)(param_1 + 0x1c) == -1 (32 bytes)
u8 FUN_71037b4430(s64 param_1)
{
    return (u8)(*(s32 *)(param_1 + 0x1c) == -1);
}

// 0x71037b52d0 — return *(u64 *)(param_1 + 0x10) (24 bytes)
u64 FUN_71037b52d0(s64 param_1)
{
    return *(u64 *)(param_1 + 0x10);
}

// 0x71037b52f0 — return bit 1 of *(u8 *)(param_1 + 0x8) (28 bytes)
u8 FUN_71037b52f0(s64 param_1)
{
    return (*(u8 *)(param_1 + 0x8) >> 1) & 1;
}

// 0x71037b5570 — return *(u32 *)(param_1 + 0x70) (24 bytes)
u32 FUN_71037b5570(s64 param_1)
{
    return *(u32 *)(param_1 + 0x70);
}

// 0x71037b5590 — return *(u32 *)(param_1 + 0x74) (24 bytes)
u32 FUN_71037b5590(s64 param_1)
{
    return *(u32 *)(param_1 + 0x74);
}

// 0x71037b55b0 — return *(u64 *)(param_1 + 0x18) (24 bytes)
u64 FUN_71037b55b0(s64 param_1)
{
    return *(u64 *)(param_1 + 0x18);
}

// 0x71037b55d0 — return bit 1 of *(u16 *)(param_1 + 0x4) (28 bytes)
u16 FUN_71037b55d0(s64 param_1)
{
    return (*(u16 *)(param_1 + 0x4) >> 1) & 1;
}

// 0x71037b6730 — return *(u64 *)(param_1 + 0x88) (24 bytes)
u64 FUN_71037b6730(s64 param_1)
{
    return *(u64 *)(param_1 + 0x88);
}
