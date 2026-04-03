#include "types.h"

// HARD-tier FUN_* functions — 0x7100 address range, batch hard-d-009
// Pool-d worker: nn::pia init/dtor patterns, PRNG seed, misc helpers (80B each)

#define HIDDEN __attribute__((visibility("hidden")))

extern "C" {
    void *memset(void *s, int c, u64 n);
    void *memcpy(void *dst, const void *src, u64 n);
}

// ---- External data -------------------------------------------------------

extern u8 *PTR_DAT_71052a2c48 HIDDEN;
extern u8 *PTR_DAT_71052a3808 HIDDEN;
extern u8 *PTR_DAT_71052a3b80 HIDDEN;
extern u8 *PTR_DAT_71052a3c38 HIDDEN;
extern u8 *PTR_DAT_71052a3d00 HIDDEN;
extern u8 *PTR_DAT_71052a3d10 HIDDEN;
extern u8 *PTR_DAT_71052a3d70 HIDDEN;
extern u8 *PTR_DAT_71052a3d98 HIDDEN;
extern u8 *PTR_DAT_71052a3e08 HIDDEN;
extern u8 *PTR_DAT_71052a3f68 HIDDEN;
extern u8 *PTR_DAT_71052a4018 HIDDEN;
extern u8 *PTR_DAT_71052a4020 HIDDEN;
extern u8 *PTR_DAT_71052a41c0 HIDDEN;
extern u8 *PTR_DAT_71052a41c8 HIDDEN;
extern u8 *PTR_DAT_71052a4228 HIDDEN;
extern u8 *PTR_DAT_71052a4418 HIDDEN;

// Named globals
extern u8  *PTR_g_SessionStateMonitoringContent_71052a2bd8 HIDDEN;
extern u64  PTR_s_pMesh_71052a2df0 HIDDEN; // string pointer

// ---- External functions --------------------------------------------------

extern void FUN_71000b1cf0(s64 *);
extern void FUN_71000b4760(s64 *); // free / base-class dtor thunk
extern void FUN_71000b4c30(s64 *, u32);
extern void FUN_71000b5a90(s32 *);
extern void FUN_710013b930(s64 *);
extern void FUN_710013b9b0(s64 *);
extern void FUN_71000bf7b0(s64 *);
extern void FUN_71000bf810(s64 *);
extern void FUN_710014f070(s64 *);
extern void FUN_7100162ce0(void);
extern u64  FUN_7100193a50(u64);
extern void FUN_71001ae560(u64, u64, u32);

// nn::pia SDK forward declarations (free functions in namespace form)
namespace nn {
namespace pia {
namespace common {
    void StepSequenceJob_ctor();                // StepSequenceJob::StepSequenceJob()
    void CallContext_ctor(s64 *);               // CallContext::CallContext()
    void CallContext_Reset(s64 *);              // CallContext::Reset()
    void CallContext_dtor(s64 *);               // CallContext::~CallContext()
    void Socket_dtor(s64 *);                    // Socket::~Socket()
    void StationAddress_ctor(s64 *);            // StationAddress::StationAddress()
    void CriticalSection_dtor(void *);          // CriticalSection::~CriticalSection()
}
namespace session {
    void SessionSearchCriteria_ctor();          // SessionSearchCriteria::SessionSearchCriteria()
}
namespace transport {
    void StationConnectionInfo_ctor(s64 *);     // StationConnectionInfo::StationConnectionInfo()
}
}
namespace os {
    void SdkAllocateTlsSlot(void *, void *);
    void InitializeEvent(void *, bool, bool);
}
}

namespace pead {
    void IDisposer_ctor();                      // IDisposer::IDisposer()
    void IDisposer_dtor(s64 *);                 // IDisposer::~IDisposer()
    void freeToSeadHeap(void *);
    void getArraySize(s64);
}

// ---- Functions ---------------------------------------------------------------

// 0x71000b3d50 — nn::pia StepSequenceJob init + CallContext init (80 bytes)
void FUN_71000b3d50(s64 *param_1)
{
    nn::pia::common::StepSequenceJob_ctor();
    *param_1 = (s64)(PTR_DAT_71052a2c48 + 0x10);
    nn::pia::common::CallContext_ctor(param_1 + 0xb);
    param_1[0x11] = 0;
    nn::pia::common::CallContext_Reset(param_1 + 0xb);
}

// 0x71000b5a40 — state check + memcpy (80 bytes)
void FUN_71000b5a40(s32 *param_1, void *param_2)
{
    if (*param_1 != 5) {
        FUN_71000b5a90(param_1);
        *param_1 = 5;
    }
    memcpy(param_2, param_1 + 6, 0x10);
}

// 0x7100114e50 — SessionSearchCriteria init + vtable + memset (80 bytes)
void FUN_7100114e50(s64 *param_1)
{
    nn::pia::session::SessionSearchCriteria_ctor();
    *(u32 *)(param_1 + 2) = 3;
    *(u32 *)((s64)param_1 + 0x1a4) = 0;
    *param_1 = (s64)(PTR_DAT_71052a3808 + 0x10);
    param_1[1] = 0x64ffffffff;
    memset((void *)((s64)param_1 + 0x14), 0, 400);
}

// 0x710012a9f0 — vtable + 3-level dtor chain (80 bytes)
void FUN_710012a9f0(s64 *param_1)
{
    *param_1 = (s64)(PTR_DAT_71052a3b80 + 0x10);
    nn::pia::common::CallContext_dtor(param_1 + 0x1b1);
    FUN_710014f070(param_1 + 0x163);
    nn::pia::common::Socket_dtor(param_1 + 0xc);
    FUN_71000b4760(param_1);
}

// 0x7100133990 — vtable + sub-dtor + IDisposer dtor (80 bytes)
void FUN_7100133990(s64 *param_1)
{
    *param_1 = (s64)(PTR_DAT_71052a3c38 + 0x10);
    FUN_710013b9b0(param_1 + 0x12);
    pead::IDisposer_dtor(param_1);
}

// 0x710013b740 — list init + mutex + TLS slot alloc (80 bytes)
void FUN_710013b740(s64 *param_1)
{
    param_1[5] = (s64)(param_1 + 5);
    param_1[6] = (s64)(param_1 + 5);
    *(u32 *)(param_1 + 7) = 0;
    *param_1 = (s64)(PTR_DAT_71052a3d00 + 0x10);
    FUN_710013b930(param_1 + 8);
    param_1[0x10] = 0;
    nn::os::SdkAllocateTlsSlot((void *)(param_1 + 0x11), nullptr);
}

// 0x710013ba50 — IDisposer ctor + vtable + InitializeEvent (80 bytes)
void FUN_710013ba50(s64 *param_1, u32 param_2)
{
    pead::IDisposer_ctor();
    *param_1 = (s64)(PTR_DAT_71052a3d10 + 0x10);
    nn::os::InitializeEvent((void *)(param_1 + 4), false, (~param_2 & 1) != 0);
}

// ---- vtable + CallContext dtor + free pattern (4 variants, 80 bytes each) ----

// 0x710013d170
void FUN_710013d170(s64 *param_1)
{
    *param_1 = (s64)(PTR_DAT_71052a3d70 + 0x10);
    nn::pia::common::CallContext_dtor(param_1 + 0xc);
    FUN_71000b4760(param_1);
}

// 0x710013dd40
void FUN_710013dd40(s64 *param_1)
{
    *param_1 = (s64)(PTR_DAT_71052a3d98 + 0x10);
    nn::pia::common::CallContext_dtor(param_1 + 0xc);
    FUN_71000b4760(param_1);
}

// 0x7100140eb0
void FUN_7100140eb0(s64 *param_1)
{
    *param_1 = (s64)(PTR_DAT_71052a3e08 + 0x10);
    nn::pia::common::CallContext_dtor(param_1 + 0xc);
    FUN_71000b4760(param_1);
}

// 0x7100151160
void FUN_7100151160(s64 *param_1)
{
    *param_1 = (s64)(PTR_DAT_71052a3f68 + 0x10);
    nn::pia::common::CallContext_dtor(param_1 + 0xc);
    FUN_71000b4760(param_1);
}

// 0x7100147200 — vtable fn-ptr call + FUN_7100193a50 dispatch (80 bytes)
void FUN_7100147200(s64 param_1, u64 param_2)
{
    if (*(void **)(param_1 + 0xa0) != nullptr) {
        (*(void (**)(u64, u64, u64))(param_1 + 0xa0))(0, param_2, *(u64 *)(param_1 + 0xa8));
    }
    u64 uVar1 = FUN_7100193a50(*(u64 *)PTR_s_pMesh_71052a2df0);
    FUN_71001ae560(uVar1, param_2, 1);
}

// 0x710015ff20 — vtable + 3x FUN_71000b1cf0 (80 bytes)
void FUN_710015ff20(s64 *param_1)
{
    *param_1 = (s64)(PTR_DAT_71052a4018 + 0x10);
    FUN_71000b1cf0(param_1 + 9);
    FUN_71000b1cf0(param_1 + 5);
    FUN_71000b1cf0(param_1 + 1);
}

// 0x71001609a0 — vtable + 3x StationConnectionInfo + StationAddress init (80 bytes)
void FUN_71001609a0(s64 *param_1)
{
    *param_1 = (s64)(PTR_DAT_71052a4020 + 0x10);
    nn::pia::transport::StationConnectionInfo_ctor(param_1 + 1);
    nn::pia::transport::StationConnectionInfo_ctor(param_1 + 0x11);
    nn::pia::common::StationAddress_ctor(param_1 + 0x21);
    *(u32 *)(param_1 + 0x26) = 0;
    FUN_71000b4c30(param_1 + 0x27, 0xffffffff);
}

// 0x71001628e0 — check ptrs + clamp + write monitoring byte (80 bytes)
void FUN_71001628e0(s64 param_1)
{
    if (*(s64 *)(param_1 + 0x20) != 0) {
        FUN_7100162ce0();
    }
    if (*(s64 *)(param_1 + 0x18) != 0) {
        s32 iVar1 = *(s32 *)(*(s64 *)(param_1 + 0x18) + 0xa4);
        if (0xfd < (u32)(iVar1 - 1)) {
            iVar1 = 0xff;
        }
        PTR_g_SessionStateMonitoringContent_71052a2bd8[0x2b7] = (u8)iVar1;
    }
}

// 0x7100138580 — Mersenne Twister seed expansion (80 bytes)
// Knuth's multiplicative LCG: f(x) = x * 0x6c078965 + i
void FUN_7100138580(u32 *param_1, u32 param_2)
{
    u32 uVar1 = (param_2 ^ (param_2 >> 0x1e)) * 0x6c078965 + 1;
    u32 uVar2 = (uVar1 ^ (uVar1 >> 0x1e)) * 0x6c078965 + 2;
    u32 uVar3 = (uVar2 ^ (uVar2 >> 0x1e)) * 0x6c078965 + 3;
    *param_1 = uVar1;
    param_1[1] = uVar2;
    param_1[2] = uVar3;
    param_1[3] = (uVar3 ^ (uVar3 >> 0x1e)) * 0x6c078965 + 4;
}

// 0x71001385d0 — PRNG state init (Xorshift/WELL seed with defaults) (80 bytes)
void FUN_71001385d0(s32 *param_1, s32 param_2, s32 param_3, s32 param_4, s32 param_5)
{
    bool bVar5 = (param_3 != 0);
    bool bVar6 = (param_2 != 0);
    bool bVar4 = (param_4 != 0);
    bool bVar3 = (param_5 != 0);
    if ((!bVar5 && !bVar6) && !bVar4 && !bVar3) {
        param_2 = 1;
    }
    bool any = ((bVar5 || bVar6) || bVar4) || bVar3;
    s32 iVar2 = any ? param_3 : 0x6c078967;
    s32 iVar1 = any ? param_4 : 0x714acb41;
    *param_1 = param_2;
    param_1[1] = iVar2;
    iVar2 = any ? param_5 : 0x48077044;
    param_1[2] = iVar1;
    param_1[3] = iVar2;
}

// 0x7100172a70 — StepSequenceJob + field init + vtable (80 bytes)
void FUN_7100172a70(s64 *param_1, s64 param_2)
{
    nn::pia::common::StepSequenceJob_ctor();
    param_1[0xb] = 0;
    param_1[0xd] = 0;
    param_1[0xe] = param_2;
    *(u32 *)(param_1 + 0xc) = 10;
    *(u16 *)((s64)param_1 + 100) = 0;
    *(u8 *)(param_1 + 0xf) = 0;
    *param_1 = (s64)(PTR_DAT_71052a41c0 + 0x10);
    FUN_71000bf7b0(param_1 + 0x10);
}

// 0x7100172ac0 — vtable + FUN_71000bf810 + free (80 bytes)
void FUN_7100172ac0(s64 *param_1)
{
    param_1[0xe] = 0;
    *param_1 = (s64)(PTR_DAT_71052a41c0 + 0x10);
    FUN_71000bf810(param_1 + 0x10);
    FUN_71000b4760(param_1);
}

// ---- vtable + conditional CallContext dtor + heap free + self-free (3 variants) ----

// 0x7100173940
void FUN_7100173940(s64 *param_1)
{
    s64 lVar1 = param_1[0xc];
    *param_1 = (s64)(PTR_DAT_71052a41c8 + 0x10);
    if (lVar1 != 0) {
        nn::pia::common::CallContext_dtor((s64 *)lVar1);
        pead::freeToSeadHeap((void *)lVar1);
    }
    param_1[0xd] = 0;
    FUN_71000b4760(param_1);
}

// 0x7100175cb0
void FUN_7100175cb0(s64 *param_1)
{
    s64 lVar1 = param_1[0xc];
    *param_1 = (s64)(PTR_DAT_71052a4228 + 0x10);
    if (lVar1 != 0) {
        nn::pia::common::CallContext_dtor((s64 *)lVar1);
        pead::freeToSeadHeap((void *)lVar1);
    }
    param_1[0xf] = 0;
    FUN_71000b4760(param_1);
}

// 0x7100183340
void FUN_7100183340(s64 *param_1)
{
    s64 lVar1 = param_1[0xc];
    *param_1 = (s64)(PTR_DAT_71052a4418 + 0x10);
    if (lVar1 != 0) {
        nn::pia::common::CallContext_dtor((s64 *)lVar1);
        pead::freeToSeadHeap((void *)lVar1);
    }
    param_1[0xd] = 0;
    FUN_71000b4760(param_1);
}

// 0x7100163120 — free array + FUN_71000bf2b0 + CriticalSection dtor (80 bytes)
extern void FUN_71000bf2b0(s64);
void FUN_7100163120(s64 param_1)
{
    s64 lVar1 = *(s64 *)(param_1 + 0x40);
    if (lVar1 != 0) {
        pead::getArraySize(lVar1);
        pead::freeToSeadHeap((void *)lVar1);
        *(u64 *)(param_1 + 0x40) = 0;
    }
    FUN_71000bf2b0(param_1 + 0x88);
    nn::pia::common::CriticalSection_dtor((void *)(param_1 + 0x58));
}

// 0x7100182c20 — copy 8 fields from nested struct ptr, return 1 (80 bytes)
u64 FUN_7100182c20(s64 param_1)
{
    s64 lVar1 = *(s64 *)(param_1 + 8);
    *(u8 *)(param_1 + 0x12)  = *(u8 *)(lVar1 + 1);
    *(u16 *)(param_1 + 0x16) = *(u16 *)(lVar1 + 2);
    *(u32 *)(param_1 + 0x1c) = *(u32 *)(lVar1 + 0xc);
    *(u32 *)(param_1 + 0x20) = *(u32 *)(lVar1 + 0x10);
    *(u32 *)(param_1 + 0x24) = *(u32 *)(lVar1 + 0x14);
    *(u32 *)(param_1 + 0x28) = *(u32 *)(lVar1 + 0x18);
    *(u64 *)(param_1 + 0x30) = *(u64 *)(lVar1 + 0x20);
    *(u8 *)(param_1 + 0x38)  = *(u8 *)(lVar1 + 0x28);
    return 1;
}
