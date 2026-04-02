#include "types.h"

// placement new (not available without <new> in this toolchain; size_t = unsigned long on AArch64)
inline void* operator new(unsigned long, void* p) noexcept { return p; }
inline void  operator delete(void*, void*) noexcept {}

// MEDIUM-tier FUN_* functions — mixed address range, batch 18
// Pool-d worker: auto-generated from Ghidra decompilation

// ---- External declarations -----------------------------------------------

extern "C" int  __cxa_guard_acquire(u64*);
extern "C" void __cxa_guard_release(u64*);

// nn namespaces
namespace nn {
namespace pia {
namespace common {
    struct StepSequenceJob  { StepSequenceJob(); };
    struct InetAddress      { InetAddress(); InetAddress& operator=(const InetAddress&); };
    struct CryptoSetting    { CryptoSetting(); };
    namespace HeapManager {
        u64 GetHeap();
    }
}
namespace transport {
    struct Protocol             { Protocol(); };
    struct StationConnectionInfo{ StationConnectionInfo(); };
}
}
}

namespace pead {
    s64  allocateFromSeadHeap(u64);
    s64  allocateFromSeadHeap(u64, u64);
}

// External C functions
extern "C" u32  FUN_71001936d0(u64);
extern "C" void FUN_710015ffc0(s64);
extern "C" u32  FUN_71001602d0(u64);
extern "C" void FUN_7100164800();
extern "C" void FUN_71001641d0(s64*);
extern "C" void FUN_7100165090();
extern "C" void FUN_7100161fc0(s32*, s64, u8*, u64);
extern "C" void FUN_7100170470(s64, u64);
extern "C" u64  FUN_71000b2b10(s64, s64);
extern "C" void FUN_71000bae70(u8*, s64, s64);  // 3-arg variant (2-arg also used elsewhere)
extern "C" void FUN_7100173e80(s64*, s64);

// External data
extern u8  PTR_DAT_71052a2360[];   // outer guard (FUN_710004fd30)
extern u8  PTR_DAT_71052a2368[];   // outer data
extern u8  PTR_DAT_71052a2370[];   // inner guard
extern u8  PTR_DAT_71052a2378[];   // inner data

extern u8  PTR_DAT_71052a2ed0[];   // StationConnectionInfo vtable
extern u8  PTR_DAT_71052a3f28[];   // Protocol vtable
extern u8  PTR_DAT_71052a4f40[];   // StepSequenceJob vtable (FUN_710014f1c0)
extern u8  PTR_DAT_71052a3f90[];   // CryptoSetting-owner vtable
extern u8  PTR_DAT_71052a4048[];   // ctor vtable (FUN_7100162930)
extern u8  PTR_DAT_71052a4050[];   // ctor vtable (FUN_7100163940)
extern u8  PTR_DAT_71052a4060[];   // ctor vtable (FUN_7100164190)
extern u8  PTR_DAT_71052a4070[];   // pead-alloc vtable (FUN_7100165640)
extern u8  PTR_DAT_71052a4100[];   // InetAddress-owner vtable
extern u8  PTR_DAT_71052a4188[];   // StepSequenceJob vtable (FUN_7100170cd0)
extern u8  PTR_DAT_71052a51e0[];   // StepSequenceJob vtable (FUN_7100173e80)
extern u8  PTR_DAT_71052a5210[];   // StepSequenceJob vtable (FUN_71001758d0)

extern u8  PTR_s_pMesh_71052a2df0[];
extern u8  PTR_g_SessionBeginMonitoringContent_71052a2bd0[];
extern u8  PTR_s_pInstance_71052a2dc8[];
extern u8  PTR_sInstancePtr_71052a3bb0[];

// ---- cxa_guard singleton -------------------------------------------------

// 710004fd30 — nested: outer 2360/2368, inner 2370/2378
u8* FUN_710004fd30()
{
    s32 iVar1;
    if ((*PTR_DAT_71052a2360 & 1) == 0) {
        iVar1 = __cxa_guard_acquire((u64*)PTR_DAT_71052a2360);
        if (iVar1 != 0) {
            if ((*PTR_DAT_71052a2370 & 1) == 0) {
                iVar1 = __cxa_guard_acquire((u64*)PTR_DAT_71052a2370);
                if (iVar1 != 0) {
                    *(u64*)PTR_DAT_71052a2378 = 0;
                    __cxa_guard_release((u64*)PTR_DAT_71052a2370);
                }
            }
            *(u8**)PTR_DAT_71052a2368 = PTR_DAT_71052a2378;
            __cxa_guard_release((u64*)PTR_DAT_71052a2360);
        }
    }
    return PTR_DAT_71052a2368;
}

// ---- Constructor helpers -------------------------------------------------

// 71000cf8b0 — set vtable, construct StationConnectionInfo sub-object, zero fields
void FUN_71000cf8b0(s64* param_1)
{
    *param_1 = (s64)(PTR_DAT_71052a2ed0 + 0x10);
    new (param_1 + 1) nn::pia::transport::StationConnectionInfo();
    *(u16*)(param_1 + 0x11) = 0;
    param_1[0x12] = 0;
    param_1[0x13] = 0;
}

// 710014c9f0 — construct Protocol base, set vtable, zero fields
void FUN_710014c9f0(s64* param_1)
{
    new (param_1) nn::pia::transport::Protocol();
    *(u16*)(param_1 + 9)  = 0;
    param_1[10]            = 0;
    *(u16*)(param_1 + 0xb) = 0;
    *param_1               = (s64)(PTR_DAT_71052a3f28 + 0x10);
    param_1[6]             = 0;
}

// 710014f1c0 — construct StepSequenceJob base, override vtable
void FUN_710014f1c0(s64* param_1)
{
    new (param_1) nn::pia::common::StepSequenceJob();
    *param_1 = (s64)(PTR_DAT_71052a4f40 + 0x10);
}

// 7100154130 — set vtable, zero fields, construct CryptoSetting sub-object
void FUN_7100154130(s64* param_1)
{
    param_1[2] = 0;
    param_1[1] = 0;
    *param_1   = (s64)(PTR_DAT_71052a3f90 + 0x10);
    new (param_1 + 3) nn::pia::common::CryptoSetting();
    *(u16*)((s64)param_1 + 0x2c) = 0;
}

// 7100162930 — call FUN_7100164800, zero fields, set vtable 4048
void FUN_7100162930(s64* param_1)
{
    FUN_7100164800();
    param_1[0x9a] = 0;
    *(u32*)(param_1 + 0x9b) = 0;
    param_1[0x9c] = 0;
    *param_1 = (s64)(PTR_DAT_71052a4048 + 0x10);
}

// 7100163940 — same as 7100162930 but vtable 4050
void FUN_7100163940(s64* param_1)
{
    FUN_7100164800();
    param_1[0x9a] = 0;
    *(u32*)(param_1 + 0x9b) = 0;
    param_1[0x9c] = 0;
    *param_1 = (s64)(PTR_DAT_71052a4050 + 0x10);
}

// 7100163b10 — call FUN_7100165090, zero field at +0x4d0
void FUN_7100163b10(s64 param_1)
{
    FUN_7100165090();
    *(u64*)(param_1 + 0x4d0) = 0;
}

// 7100164190 — set vtable 4060, zero fields, call FUN_71001641d0
void FUN_7100164190(s64* param_1)
{
    param_1[2] = 0;
    *(u8*)(param_1 + 3) = 0;
    *param_1   = (s64)(PTR_DAT_71052a4060 + 0x10);
    param_1[1] = 0;
    FUN_71001641d0(param_1 + 4);
    param_1[0x225] = 0;
}

// 7100165640 — pead alloc 0x20 bytes, set vtable + fields
void FUN_7100165640(s64 param_1)
{
    s64 lVar1 = *(s64*)(param_1 + 8);
    s64 lVar2 = *(s64*)(param_1 + 0x10);
    s64 lVar4 = *(s64*)(param_1 + 0x18);
    s64* plVar3 = (s64*)pead::allocateFromSeadHeap(0x20);
    if (plVar3 != nullptr) {
        plVar3[2] = lVar2;
        plVar3[3] = lVar4;
        *plVar3   = (s64)(PTR_DAT_71052a4070 + 0x10);
        plVar3[1] = lVar1;
    }
}

// 7100170cd0 — call FUN_7100173e80 then override vtable 4188
void FUN_7100170cd0(s64* param_1, s64 param_2)
{
    FUN_7100173e80(param_1, param_2);
    *param_1 = (s64)(PTR_DAT_71052a4188 + 0x10);
}

// 7100172660 — set vtable 4100, construct InetAddress, zero u16 field
void FUN_7100172660(s64* param_1)
{
    *param_1 = (s64)(PTR_DAT_71052a4100 + 0x10);
    new (param_1 + 1) nn::pia::common::InetAddress();
    *(u16*)(param_1 + 5) = 0;
}

// 7100173e80 — construct StepSequenceJob, zero/store fields, set vtable 41e0
void FUN_7100173e80(s64* param_1, s64 param_2)
{
    new (param_1) nn::pia::common::StepSequenceJob();
    param_1[0xb] = 0;
    param_1[0xc] = param_2;
    *param_1     = (s64)(PTR_DAT_71052a51e0 + 0x10);
}

// 71001758d0 — same as 7100173e80 but vtable 4210
void FUN_71001758d0(s64* param_1, s64 param_2)
{
    new (param_1) nn::pia::common::StepSequenceJob();
    param_1[0xb] = 0;
    param_1[0xc] = param_2;
    *param_1     = (s64)(PTR_DAT_71052a5210 + 0x10);
}

// ---- Comparison / copy helpers -------------------------------------------

// 71001728a0 — compare InetAddress sub-fields + u16
u64 FUN_71001728a0(s64 param_1, s64 param_2)
{
    u64 uVar1 = FUN_71000b2b10(param_1 + 8, param_2 + 8);
    if (((uVar1 & 1) != 0) && (*(s16*)(param_1 + 0x28) == *(s16*)(param_2 + 0x28)))
        return 1;
    return 0;
}

// 7100172900 — InetAddress assignment: copy InetAddress sub-object + u16 field
s64 FUN_7100172900(s64 param_1, s64 param_2)
{
    if (param_1 != param_2) {
        *(nn::pia::common::InetAddress*)(param_1 + 8) =
            *(const nn::pia::common::InetAddress*)(param_2 + 8);
        *(u16*)(param_1 + 0x28) = *(u16*)(param_2 + 0x28);
    }
    return param_1;
}

// 7100177cd0 — FUN_71000bae70 + copy 3 fields
void FUN_7100177cd0(s64 param_1, s64 param_2)
{
    u8 auStack_30[16];
    FUN_71000bae70(auStack_30, param_2, param_1 + 8);
    *(u8*)(param_2 + 0x70)  = *(u8*)(param_1 + 0x78);
    u64 uVar1               = *(u64*)(param_1 + 0x88);
    *(u64*)(param_2 + 0x78) = *(u64*)(param_1 + 0x80);
    *(u64*)(param_2 + 0x80) = uVar1;
}

// ---- Misc ----------------------------------------------------------------

// 7100146fe0 — vtable dispatch at [+0x20][+0x38], return 9 or uVar1+4 or uVar2
u64 FUN_7100146fe0(s64 param_1)
{
    u64 uVar2 = (*(u64(**)(void))(*(s64*)*(s64**)(param_1 + 0x20) + 0x38))();
    if ((s32)uVar2 == 4) {
        u32 uVar1 = FUN_71001936d0(*(u64*)PTR_s_pMesh_71052a2df0);
        if (3 < uVar1)
            return 9;
        uVar2 = (u64)(uVar1 + 4);
    }
    return uVar2;
}

// 710015fb50 — clear struct fields if first byte non-zero
void FUN_710015fb50(char* param_1)
{
    if (*param_1 == '\0')
        return;
    param_1[4]  = -1;  param_1[5]  = -1;  param_1[6]  = -1;  param_1[7]  = -1;
    param_1[8]  = -1;  param_1[9]  = -1;  param_1[10] = -1;  param_1[0xb] = -1;
    param_1[0xc]= -1;  param_1[0xd]= -1;  param_1[0xe]= -1;  param_1[0xf]= -1;
    *param_1    = '\0';
    param_1[0x10] = '\0'; param_1[0x11] = '\0'; param_1[0x12] = '\0';
    param_1[0x13] = '\0'; param_1[0x14] = '\0'; param_1[0x15] = '\0';
    param_1[0x16] = '\0'; param_1[0x17] = '\0'; param_1[0x18] = '\0';
    param_1[0x48] = '\0'; param_1[0x49] = '\0'; param_1[0x4a] = '\0';
    param_1[0x4b] = '\0'; param_1[0x4c] = '\0'; param_1[0x4d] = '\0';
    param_1[0x4e] = '\0'; param_1[0x4f] = '\0';
    param_1[0x1c] = '\0'; param_1[0x1d] = '\0'; param_1[0x1e] = '\0';
    param_1[0x1f] = '\0'; param_1[0x20] = '\0'; param_1[0x21] = '\0';
    param_1[0x22] = '\0'; param_1[0x23] = '\0';
    param_1[0x50] = '\0'; param_1[0x51] = '\0'; param_1[0x52] = '\0';
    param_1[0x53] = '\0';
}

// 7100160ae0 — call two helpers, write global monitoring content field
void FUN_7100160ae0(s64 param_1, u64 param_2)
{
    FUN_710015ffc0(param_1 + 8);
    u32 uVar1 = FUN_71001602d0(param_2);
    *(u32*)(PTR_g_SessionBeginMonitoringContent_71052a2bd0 + 0xd4) = uVar1;
}

// 7100167260 — pInstance check + call FUN_7100161fc0, return result or 0xfd
u32 FUN_7100167260(u64 param_1)
{
    if (*(s64*)PTR_s_pInstance_71052a2dc8 != 0) {
        s32  local_28[5];
        u8   local_14[4];
        FUN_7100161fc0(local_28, *(s64*)PTR_s_pInstance_71052a2dc8, local_14, param_1);
        u32 uVar1 = (u32)local_14[0];
        if (local_28[0] != 0)
            uVar1 = 0xfffffffd;
        return uVar1;
    }
    return 0xfd;
}

// 710016bb30 — GetHeap + alloc 0xa8 bytes + call init
s64 FUN_710016bb30(u64 param_1)
{
    u64 uVar1 = nn::pia::common::HeapManager::GetHeap();
    s64 lVar2 = pead::allocateFromSeadHeap(0xa8, uVar1);
    if (lVar2 != 0) {
        FUN_7100170470(lVar2, param_1);
    }
    return lVar2;
}
