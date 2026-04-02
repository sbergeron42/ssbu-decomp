#include "types.h"

// MEDIUM-tier FUN_* functions — mixed address range, batch 15
// Pool-d worker: auto-generated from Ghidra decompilation

// ---- External declarations -----------------------------------------------

extern "C" void* memcpy(void*, const void*, u64);
extern "C" s32   memcmp(const void*, const void*, u64);
extern "C" s32  __cxa_guard_acquire(u64*);
extern "C" void __cxa_guard_release(u64*);

// nn namespaces
namespace nn {
namespace os {
    struct MessageQueueType;
    struct ThreadType;
    u64  GetSystemTickFrequency();
    u64  TryReceiveMessageQueue(u64*, MessageQueueType*);
    void ReceiveMessageQueue(u64*, MessageQueueType*);
    void StartThread(ThreadType*);
}
namespace pia {
namespace common {
    namespace CallContext {
        void SignalCancel(s32*);
        void Reset(s32*);
        void InitiateCall(s32*);
    }
    namespace TimeSpan {
        s64* GetTicksPerMSec();
    }
    namespace HeapManager {
        void Cleanup(s32);
    }
}
namespace transport {
    namespace StationConnectionInfo {
        void StationConnectionInfo(s64*);  // ctor as free function
    }
}
}
}

namespace pead {
    void* allocateFromSeadHeap(u64);
    void  freeToSeadHeap(s64);
    namespace HeapMgr {
        s64 getCurrentHeap(u64);
    }
}

// External C functions
extern "C" s64   FUN_71000c9b60(s64);
extern "C" u64   FUN_71000c84e0(s64);
extern "C" void  FUN_7100140e60(s64*);
extern "C" void  FUN_71000bcda0(u8*, s32);
extern "C" void  FUN_71000bce50(u64, u32*);
extern "C" void  FUN_71000ba010(u8*, s64);
extern "C" void  FUN_710015fde0(s64*);
extern "C" void  FUN_71001259f0(u8*, u64);
extern "C" void  FUN_7100126a70(u8*, u64, u64*);
extern "C" void  FUN_7100127530(u64);
extern "C" void  FUN_71001617f0(u8*, u64, s64);
extern "C" void  FUN_71001464b0(s32*, s64, u32, u64, u64, s32);
extern "C" u32   FUN_71001936d0(u64);

// External data
extern u8  PTR_DAT_71052a2ca0[];
extern u8  PTR_DAT_71052a2ed0[];
extern u8  PTR_DAT_71052a3108[];
extern u8  PTR_DAT_71052a49d0[];
extern u8  DAT_71052aafc8;
extern u8  PTR_DAT_71052a3c18[];
extern u8  PTR_DAT_71052a3c20[];
extern u8  PTR_DAT_71052a3c30[];
extern u64 PTR_s_pInstance_71052a3bb0;
extern u64 PTR_s_pMesh_71052a2df0;
extern u8  DAT_71044919c4[];

// cxa_guard data for tick freq singletons
extern u8  DAT_71052aacc0;
extern s64 DAT_71052aacb8;
extern u8  DAT_71052aacd0;
extern s64 DAT_71052aacc8;
extern u8  DAT_71052aace0;
extern s64 DAT_71052aacd8;

// ---- nn::os tick frequency singletons -------------------------------------

// 71000bb600 — guard 71052aacc0, store freq/1M to 71052aacb8
s64* FUN_71000bb600()
{
    s32 iVar1;
    if ((DAT_71052aacc0 & 1) == 0) {
        iVar1 = __cxa_guard_acquire((u64*)&DAT_71052aacc0);
        if (iVar1 != 0) {
            s64 lVar2 = (s64)nn::os::GetSystemTickFrequency();
            DAT_71052aacb8 = lVar2 / 1000000;
            __cxa_guard_release((u64*)&DAT_71052aacc0);
            return &DAT_71052aacb8;
        }
    }
    return &DAT_71052aacb8;
}

// 71000bb700 — nested: 71052aace0 outer, 71052aacd0 inner; freq/1K then *1K
s64* FUN_71000bb700()
{
    s32 iVar1;
    if ((DAT_71052aace0 & 1) == 0) {
        iVar1 = __cxa_guard_acquire((u64*)&DAT_71052aace0);
        if (iVar1 != 0) {
            if ((DAT_71052aacd0 & 1) == 0) {
                iVar1 = __cxa_guard_acquire((u64*)&DAT_71052aacd0);
                if (iVar1 != 0) {
                    s64 lVar2 = (s64)nn::os::GetSystemTickFrequency();
                    DAT_71052aacc8 = lVar2 / 1000;
                    __cxa_guard_release((u64*)&DAT_71052aacd0);
                }
            }
            DAT_71052aacd8 = DAT_71052aacc8 * 1000;
            __cxa_guard_release((u64*)&DAT_71052aace0);
            return &DAT_71052aacd8;
        }
    }
    return &DAT_71052aacd8;
}

// ---- cxa_guard pointer-init variant ----------------------------------------

// 7100134ba0 — guard 3c18, sets *3c20 = 3c30+0x10 (no data zeroing)
u8* FUN_7100134ba0()
{
    s32 iVar1;
    if ((*PTR_DAT_71052a3c18 & 1) == 0) {
        iVar1 = __cxa_guard_acquire((u64*)PTR_DAT_71052a3c18);
        if (iVar1 != 0) {
            *(u8**)PTR_DAT_71052a3c20 = PTR_DAT_71052a3c30 + 0x10;
            __cxa_guard_release((u64*)PTR_DAT_71052a3c18);
            return PTR_DAT_71052a3c20;
        }
    }
    return PTR_DAT_71052a3c20;
}

// ---- Comparison helpers ---------------------------------------------------

// 71000b2b10 — memcmp 0x10 bytes + u16 compare, return 1 if both equal
u64 FUN_71000b2b10(s64 param_1, s64 param_2)
{
    s32 iVar1 = memcmp((void*)(param_1 + 8), (void*)(param_2 + 8), 0x10);
    if ((iVar1 == 0) && (*(u16*)(param_1 + 0x18) == *(u16*)(param_2 + 0x18)))
        return 1;
    return 0;
}

// ---- pead allocation helpers -----------------------------------------------

// 71000b7020 — allocate 0x20 bytes, init as a linked-list / cache node
void FUN_71000b7020(s64 param_1)
{
    s64 lVar1 = *(s64*)(param_1 + 8);
    s64 lVar2 = *(s64*)(param_1 + 0x10);
    s64 lVar4 = *(s64*)(param_1 + 0x18);
    s64* plVar3 = (s64*)pead::allocateFromSeadHeap(0x20);
    if (plVar3 != nullptr) {
        plVar3[2] = lVar2;
        plVar3[3] = lVar4;
        *plVar3 = (s64)(PTR_DAT_71052a2ca0 + 0x10);
        plVar3[1] = lVar1;
    }
}

// 710013b7a0 — vtable delete sub-object at +0x80, free, zero ptr
void FUN_710013b7a0(s64 param_1)
{
    u64* puVar1 = *(u64**)(param_1 + 0x80);
    if (puVar1 != nullptr) {
        (*(void(**)(u64*))*puVar1)(puVar1);
        pead::freeToSeadHeap((s64)puVar1);
        *(u64*)(param_1 + 0x80) = 0;
    }
}

// 71000ecf00 — overwrite vtable, vtable-delete field[0x5b], free, zero
void FUN_71000ecf00(s64* param_1)
{
    u64* puVar1 = (u64*)param_1[0x5b];
    *param_1 = (s64)(PTR_DAT_71052a3108 + 0x10);
    if (puVar1 != nullptr) {
        (*(void(**)(u64*))*puVar1)(puVar1);
        pead::freeToSeadHeap((s64)puVar1);
        param_1[0x5b] = 0;
    }
}

// ---- Loop / check helpers --------------------------------------------------

// 71000c7428 — call FUN_71000c9b60(+0x178), check field +0x9c != -1
u64 FUN_71000c7428(s64 param_1)
{
    s64 lVar1 = FUN_71000c9b60(param_1 + 0x178);
    if ((lVar1 != 0) && (*(s32*)(lVar1 + 0x9c) != -1))
        return 1;
    return 0;
}

// 71000c8490 — do-while: loop while FUN_71000c84e0 returns odd, exit on 0 at +0x90
u64 FUN_71000c8490(s64 param_1)
{
    u64 uVar1;
    do {
        if (*(s32*)(param_1 + 0x90) == 0)
            return 1;
        uVar1 = FUN_71000c84e0(param_1);
    } while ((uVar1 & 1) != 0);
    return 0;
}

// ---- Time span computation -------------------------------------------------

// 71000cabc0 — compute elapsed ms: (end - start) / ticksPerMSec
void FUN_71000cabc0(s64 param_1, u64* param_2, u64* param_3)
{
    u64 uVar3 = *param_3;
    u64 uVar4 = *param_2;
    if (uVar3 <= uVar4) {
        s64* plVar2 = nn::pia::common::TimeSpan::GetTicksPerMSec();
        u32 uVar1 = 0;
        if (*plVar2 != 0)
            uVar1 = (u32)((s64)(uVar4 - uVar3) / *plVar2);
        *(u32*)(param_1 + 0x9c) = uVar1;
    }
}

// ---- nn::pia vtable init helpers -------------------------------------------

// 71000cf800 — vtable init + field stores
void FUN_71000cf800(s64* param_1, u64 param_2, u8 param_3, u8 param_4, s64 param_5)
{
    *param_1 = (s64)(PTR_DAT_71052a2ed0 + 0x10);
    FUN_710015fde0(param_1 + 1);
    *(u8*)((s64)param_1 + 0x88) = param_3 & 1;
    *(u8*)((s64)param_1 + 0x89) = param_4 & 1;
    param_1[0x12] = 0;
    param_1[0x13] = param_5;
}

// 7100116780 — conditional HeapManager::Cleanup + FUN_71000bcda0
void FUN_7100116780()
{
    u8 auStack_30[16];
    if (DAT_71052aafc8 == '\x01') {
        nn::pia::common::HeapManager::Cleanup(6);
        DAT_71052aafc8 = '\0';
        FUN_71000bcda0(auStack_30, 6);
    }
}

// ---- Callback / wrapper patterns ------------------------------------------

// 7100116fd0 — store param_2, call two setup functions with stack buffers
void FUN_7100116fd0(u64* param_1, u64 param_2)
{
    u8 auStack_40[16];
    u8 auStack_30[16];
    *param_1 = param_2;
    FUN_71001259f0(auStack_30, param_2);
    FUN_7100126a70(auStack_40, *param_1, param_1 + 1);
}

// 71001170d0 — single wrapper: call FUN_7100127530 with *param_1
void FUN_71001170d0(u64* param_1)
{
    FUN_7100127530(*param_1);
}

// 710011efd0 — call FUN_7100140e60(param_1), overwrite vtable
void FUN_710011efd0(s64* param_1)
{
    FUN_7100140e60(param_1);
    *param_1 = (s64)(PTR_DAT_71052a49d0 + 0x10);
}

// ---- nn::pia::common::CallContext helpers ----------------------------------

// 710012b440 — conditional SignalCancel, then conditional sub call
void FUN_710012b440(s64 param_1)
{
    u8 auStack_30[16];
    if (*(s32*)(param_1 + 0xd88) == 1)
        nn::pia::common::CallContext::SignalCancel((s32*)(param_1 + 0xd88));
    if (0 < *(s32*)(param_1 + 100))
        FUN_71000ba010(auStack_30, param_1 + 0x60);
}

// 710012b490 — guard: skip if param_2 out of range [1,2] or already running
u64 FUN_710012b490(s64 param_1, s8 param_2)
{
    if ((u8)(param_2 - 1) > 1)
        return 0;
    if (*(s32*)(param_1 + 0xd88) == 1)
        return 0;
    *(u8*)(param_1 + 0xd81) = 1;
    *(s8*)(param_1 + 0xd80) = param_2;
    nn::pia::common::CallContext::Reset((s32*)(param_1 + 0xd88));
    nn::pia::common::CallContext::InitiateCall((s32*)(param_1 + 0xd88));
    return 1;
}

// ---- nn::os MessageQueue / Thread helpers ---------------------------------

// 710013bcb0 — conditional ReceiveMessageQueue (blocking or try)
u64 FUN_710013bcb0(nn::os::MessageQueueType* param_1, s32 param_2)
{
    u64 local_18;
    if (param_2 != 0) {
        u64 uVar1 = nn::os::TryReceiveMessageQueue(&local_18, param_1);
        if ((uVar1 & 1) == 0)
            local_18 = 0;
        return local_18;
    }
    nn::os::ReceiveMessageQueue(&local_18, param_1);
    return local_18;
}

// 710013c200 — start thread if not already running
u64 FUN_710013c200(s64 param_1)
{
    if (*(s32*)(param_1 + 0xcc) != 0)
        return 0;
    nn::os::StartThread(*(nn::os::ThreadType**)(param_1 + 0xd0));
    *(s32*)(param_1 + 0xc8) = (s32)*(u64*)(param_1 + 0xd0);
    if (*(s32*)(param_1 + 0xcc) != 0)
        return 1;
    *(u32*)(param_1 + 0xcc) = 1;
    return 1;
}

// ---- Misc helpers ----------------------------------------------------------

// 7100142430 — store fields + call FUN_71001617f0
void FUN_7100142430(s64 param_1, u32* param_2)
{
    u8 auStack_30[16];
    *(u32*)(param_1 + 0x24c) = *param_2;
    memcpy((void*)(param_1 + 0x250), param_2 + 1, 0x10);
    FUN_71001617f0(auStack_30, *(u64*)PTR_s_pInstance_71052a3bb0, param_1 + 0x24c);
}

// 7100146a30 — computed-offset dispatch, then conditional store 0x13
void FUN_7100146a30(s32* param_1, s64 param_2, u64 param_3)
{
    FUN_71001464b0(param_1, param_2,
                   *(u32*)(param_2 + (u64)*(u8*)(param_2 + 0x162) * 4 + 0x180),
                   *(u64*)(param_2 + (u64)*(u8*)(param_2 + 0x162) * 8 + 0x168),
                   param_3, 0);
    if (*param_1 != 0)
        return;
    *(u32*)(param_2 + 0x140) = 0x13;
}

// 7100146f80 — vtable dispatch at +0x58, conditional sub-lookup, return
u64 FUN_7100146f80(s64 param_1)
{
    u64 uVar2 = (*(u64(**)(void))(*(s64*)*(s64**)(param_1 + 0x30) + 0x58))();
    if ((s32)uVar2 == 4) {
        u32 uVar1 = FUN_71001936d0(*(u64*)PTR_s_pMesh_71052a2df0);
        if (3 < uVar1)
            return 9;
        uVar2 = (u64)(uVar1 + 4);
    }
    return uVar2;
}
