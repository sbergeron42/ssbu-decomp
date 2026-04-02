#include "types.h"

// placement new
inline void* operator new(unsigned long, void* p) noexcept { return p; }
inline void  operator delete(void*, void*) noexcept {}

// MEDIUM-tier FUN_* functions -- mixed address range, batch 19
// Pool-d worker: auto-generated from Ghidra decompilation

// ---- External declarations -----------------------------------------------

extern "C" void* memset(void*, int, u64);

// nn namespaces
namespace nn {
namespace pia {
namespace common {
    struct StepSequenceJob { StepSequenceJob(); };
    struct Job             { u32 IsRunning(); };
    namespace InetAddress {
        u64 IsValid(s64);
    }
    namespace HeapManager {
        u64 GetHeap();
    }
}
namespace transport {
    namespace StationManager {
        s64 GetStation(u64);
    }
    namespace Station {
        void CleanupJobs(u64);
    }
}
}
}

namespace pead {
    s64 allocateFromSeadHeap(u64, u64);
}

// External C functions
extern "C" u64  FUN_71001800a0(s64);
extern "C" u32  FUN_71000b2b10(s64, s64);
extern "C" void FUN_7100172660(s64*);
extern "C" void FUN_71000b28c0(s64);
extern "C" s32  FUN_71001726a0(s64);
extern "C" void FUN_71000bae70(u8*, s64, s64);
extern "C" void FUN_7100155060();
extern "C" void FUN_71001609a0();
extern "C" void FUN_7100164190(s64*);
extern "C" void FUN_7100155060();
extern "C" void FUN_71001510a0();
extern "C" void FUN_710013e590();
extern "C" void FUN_7100170470(s64, u64);
extern "C" void FUN_7100138e0(s64, u64);
extern "C" void FUN_71001738e0(s64, u64);

// External data
extern u8  PTR_s_pInstance_71052a2dc8[];
extern u8  PTR_DAT_71052a52a0[];   // StepSequenceJob vtable (FUN_7100179d50)
extern u8  PTR_DAT_71052a4500[];   // outer vtable (FUN_71001857c0)
extern u8  PTR_DAT_71052a4538[];   // vtable (FUN_7100186580)
extern u8  PTR_DAT_71052a5560[];   // vtable (FUN_71001875f0)
extern u8  PTR_DAT_71052a46d8[];   // vtable (FUN_7100195180)
extern u8  PTR_DAT_71052a56f0[];   // vtable (FUN_710019b910)
extern u8  PTR_DAT_71052a5708[];   // vtable (FUN_710019f980)

// ---- Condition + passthrough call ----------------------------------------

// 7100174f00 -- guard: byte+ptr nonzero, then call FUN_71001800a0
u64 FUN_7100174f00(s64 param_1)
{
    if (*(s8*)(param_1 + 8) != '\0' && *(s64*)(param_1 + 0x18) != 0) {
        return FUN_71001800a0(param_1);
    }
    return 0;
}

// 7100174ff0 -- vtable call at +0x178 with 16-byte stack buf
void FUN_7100174ff0(s64 param_1, s64* param_2)
{
    u8 auStack_20[16];
    *(s64**)(param_1 + 0x18) = param_2;
    (*(void(**)(u8*, s64*, u64))(*(s64*)param_2 + 0x178))(auStack_20, param_2, *(u64*)(param_1 + 0x10));
}

// ---- InetAddress helpers -------------------------------------------------

// 71001800a0 -- double IsValid check, return compare result
u64 FUN_71001800a0(s64 param_1)
{
    u64 uVar1 = nn::pia::common::InetAddress::IsValid(param_1 + 0x2c0);
    if ((uVar1 & 1) != 0) {
        uVar1 = nn::pia::common::InetAddress::IsValid(param_1 + 0x2a0);
        if ((uVar1 & 1) != 0) {
            u64 uVar2 = FUN_71000b2b10(param_1 + 0x2a0, param_1 + 0x2c0);
            return uVar2;
        }
    }
    return 0;
}

// 710017ebf0 -- similar to 71001800a0 but returns negated compare
u32 FUN_710017ebf0(s64 param_1)
{
    u64 uVar2 = nn::pia::common::InetAddress::IsValid(param_1 + 0x2c0);
    if ((uVar2 & 1) == 0) return 0;
    uVar2 = nn::pia::common::InetAddress::IsValid(param_1 + 0x2a0);
    if ((uVar2 & 1) != 0) {
        u32 uVar1 = FUN_71000b2b10(param_1 + 0x2a0, param_1 + 0x2c0);
        return (uVar1 ^ 1) & 1;
    }
    return 0;
}

// ---- memset copy helpers -------------------------------------------------

// 7100182ca0 -- copy fields from param_1 into *(u8**)(param_1+8) buffer
void FUN_7100182ca0(s64 param_1)
{
    u8* puVar1 = *(u8**)(param_1 + 8);
    *puVar1        = 1;
    puVar1[1]      = *(u8*)(param_1 + 0x12);
    *(u16*)(puVar1 + 2) = *(u16*)(param_1 + 0x16);
    memset(puVar1 + 4, 0, 6);
    *(u32*)(*(s64*)(param_1 + 8) + 0xc) = 0;
}

// 7100182d40 -- identical to FUN_7100182ca0
void FUN_7100182d40(s64 param_1)
{
    u8* puVar1 = *(u8**)(param_1 + 8);
    *puVar1        = 1;
    puVar1[1]      = *(u8*)(param_1 + 0x12);
    *(u16*)(puVar1 + 2) = *(u16*)(param_1 + 0x16);
    memset(puVar1 + 4, 0, 6);
    *(u32*)(*(s64*)(param_1 + 8) + 0xc) = 0;
}

// ---- Constructor helpers -------------------------------------------------

// 71001857c0 -- set vtable 4500, call FUN_7100172660 for sub-object, zero fields
void FUN_71001857c0(s64* param_1)
{
    *param_1 = (s64)(PTR_DAT_71052a4500 + 0x10);
    FUN_7100172660(param_1 + 1);
    *(u32*)(param_1 + 7)        = 0;
    *(u16*)((s64)param_1 + 0x3c) = 0xff00;
    FUN_71000b28c0((s64)(param_1 + 2));
    *(u16*)(param_1 + 6) = 0;
}

// 71001875f0 -- StepSequenceJob base + vtable 4560 + one zero
void FUN_71001875f0(s64* param_1)
{
    new (param_1) nn::pia::common::StepSequenceJob();
    param_1[0xb] = 0;
    *param_1     = (s64)(PTR_DAT_71052a5560 + 0x10);
}

// 7100179d50 -- StepSequenceJob base + vtable 42a0 + store param_2
void FUN_7100179d50(s64* param_1, s64 param_2)
{
    FUN_710013e590();
    param_1[0x27] = 0;
    param_1[0x28] = param_2;
    *param_1      = (s64)(PTR_DAT_71052a52a0 + 0x10);
}

// 7100185a90 -- return FUN_71001726a0(param_1+8) + 1
s32 FUN_7100185a90(s64 param_1)
{
    return FUN_71001726a0(param_1 + 8) + 1;
}

// 7100186540 -- FUN_71001510a0 + zero field at +0xc
void FUN_7100186540(s64 param_1)
{
    FUN_71001510a0();
    *(u32*)(param_1 + 0xc) = 0;
}

// 7100195180 -- FUN_7100155060 + set vtable 46d8, zero fields
void FUN_7100195180(s64* param_1)
{
    FUN_7100155060();
    *(u8*)(param_1 + 0x153)     = 0xfd;
    *param_1                     = (s64)(PTR_DAT_71052a46d8 + 0x10);
    *(u64*)((s64)param_1 + 0xa9c) = 0;
    param_1[0x155]               = 0;
}

// 710019b910 -- FUN_71001609a0 + zero field + set vtable 46f0
void FUN_710019b910(s64* param_1)
{
    FUN_71001609a0();
    param_1[0x2b] = 0;
    *param_1      = (s64)(PTR_DAT_71052a56f0 + 0x10);
}

// 710019f980 -- FUN_7100164190(x0 passthrough) + override vtable 4708
void FUN_710019f980(s64* param_1)
{
    FUN_7100164190(param_1);
    *param_1 = (s64)(PTR_DAT_71052a5708 + 0x10);
}

// 7100180210 -- GetHeap + alloc 0x70 + init
s64 FUN_7100180210(u64 param_1)
{
    u64 uVar1 = nn::pia::common::HeapManager::GetHeap();
    s64 lVar2 = pead::allocateFromSeadHeap(0x70, uVar1);
    if (lVar2 != 0) {
        FUN_71001738e0(lVar2, param_1);
    }
    return lVar2;
}

// ---- Linked list traversal -----------------------------------------------

// 7100190ff0 -- iterate StationManager list, call CleanupJobs on each
void FUN_7100190ff0()
{
    s64 lVar1 = nn::pia::transport::StationManager::GetStation(*(u64*)PTR_s_pInstance_71052a2dc8);
    for (s64 lVar2 = *(s64*)(lVar1 + 0x20); lVar2 != lVar1 + 0x18; lVar2 = *(s64*)(lVar2 + 8)) {
        nn::pia::transport::Station::CleanupJobs(*(u64*)(lVar2 + 0x10));
    }
}

// ---- Job::IsRunning checks -----------------------------------------------

// 7100192590 -- OR IsRunning() from 3 job fields, return &1
u32 FUN_7100192590(s64 param_1)
{
    u32 uVar1;
    s64 lVar3;
    if (*(s64*)(param_1 + 0x10) == 0) {
        uVar1 = 0;
        lVar3 = *(s64*)(param_1 + 0x40);
    } else {
        uVar1 = ((nn::pia::common::Job*)*(s64*)(param_1 + 0x10))->IsRunning();
        lVar3 = *(s64*)(param_1 + 0x40);
    }
    if (lVar3 != 0) {
        u32 uVar2 = ((nn::pia::common::Job*)lVar3)->IsRunning();
        uVar1 = uVar1 | uVar2;
    }
    if (*(s64*)(param_1 + 0x28) != 0) {
        u32 uVar2 = ((nn::pia::common::Job*)*(s64*)(param_1 + 0x28))->IsRunning();
        uVar1 = uVar1 | uVar2;
    }
    return uVar1 & 1;
}

// ---- Char search in array ------------------------------------------------

// 71001a8730 -- linear search for char in array, return base + index*0x80
s64 FUN_71001a8730(s64 param_1, char param_2)
{
    u16 uVar1;
    if (*(u16*)(param_1 + 0xd6) == 0)
        return 0;
    uVar1 = 0;
    do {
        if (*(char*)(*(s64*)(param_1 + 0xb0) + (u64)uVar1) == param_2) {
            return *(s64*)(param_1 + 0xa8) + (u64)uVar1 * 0x80;
        }
        uVar1 = uVar1 + 1;
    } while (uVar1 < *(u16*)(param_1 + 0xd6));
    return 0;
}
