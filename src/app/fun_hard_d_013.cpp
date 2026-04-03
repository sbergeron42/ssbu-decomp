#include "types.h"

// HARD-tier FUN_* functions — 0x7100 address range, batch hard-d-013
// Pool-d worker: struct type inits, session ctors, SignalCancel/Reset (96B each)

#define HIDDEN __attribute__((visibility("hidden")))

extern "C" {
    void *memset(void *s, int c, u64 n);
}

// ---- External data -------------------------------------------------------

// Vtable bases
extern u8 *PTR_DAT_71052a3860 HIDDEN;
extern u8 *PTR_DAT_71052a3b58 HIDDEN; // base vtable for type-stamped structs
extern u8 *PTR_DAT_71052a3b60 HIDDEN; // type 3 vtable
extern u8 *PTR_DAT_71052a3b68 HIDDEN; // type 5 vtable
extern u8 *PTR_DAT_71052a3b70 HIDDEN; // type 6 vtable
extern u8 *PTR_DAT_71052a3b78 HIDDEN; // type 7 vtable
extern u8 *PTR_DAT_71052a3ba8 HIDDEN;
extern u8 *PTR_DAT_71052a3cf8 HIDDEN;
extern u8 *PTR_DAT_71052a3dc8 HIDDEN;
extern u8 *PTR_DAT_71052a3f58 HIDDEN;
extern u8 *PTR_DAT_71052a3f88 HIDDEN;

// Pointer-to-pointer cleanup globals
extern u8 *PTR_DAT_71052a3820 HIDDEN;
extern u8 *PTR_DAT_71052a3828 HIDDEN;

// Singleton pointer
extern u64 PTR_s_pInstance_71052a3080 HIDDEN; // some singleton*

// ---- External functions --------------------------------------------------

extern void FUN_71000b1cf0(s64 *);
extern void FUN_71000b4760(s64 *);
extern void FUN_710015ff20(s64 *);
extern void FUN_71000bed20(s64 *);
extern void FUN_71000bce50(u32 *, u32 *);
extern void FUN_710013be00(s64 *, u64, u64, u32, u32, u64, u32, u32);
extern void FUN_7100147420(u64, u32, u32, u8 *);
extern void FUN_7100154130(void);
extern void FUN_7100157940(s64 *);

namespace pead {
    void getArraySize(s64);
    void freeToSeadHeap(void *);
}

namespace nn {
namespace pia {
namespace common {
    void CallContext_dtor(s64 *);
    void CallContext_Reset(void *);
    void CallContext_SignalCancel(void *);
    namespace ListBase {
        void Init(s64 *);
        void Init_default(void);
    }
}
namespace session {
    void UpdateSessionSetting_ctor(void); // UpdateSessionSetting::UpdateSessionSetting()
}
}
}

// ---- Functions ---------------------------------------------------------------

// 0x7100116ee0 — conditional: zero inner ctx + FUN_71000b1cf0, then free heap array (96 bytes)
void FUN_7100116ee0(void)
{
    u64 *puVar2 = *(u64 **)PTR_DAT_71052a3820;
    if (puVar2 != nullptr) {
        *puVar2 = 0;
        FUN_71000b1cf0((s64 *)(puVar2 + 1));
        *(u64 *)PTR_DAT_71052a3820 = 0;
    }
    s64 lVar3 = *(s64 *)PTR_DAT_71052a3828;
    if (lVar3 != 0) {
        pead::getArraySize(lVar3);
        pead::freeToSeadHeap((void *)lVar3);
        *(u64 *)PTR_DAT_71052a3828 = 0;
    }
}

// 0x7100118620 — derived vtable + self-ptr + 4x FUN_71000b1cf0 + FUN_71000bed20 (96 bytes)
// param_1 points into middle of struct; param_1[-3] = base vtable, param_1[0] = derived vtable
void FUN_7100118620(s64 *param_1)
{
    param_1[-3] = (s64)(PTR_DAT_71052a3860 + 0x10);
    *param_1 = (s64)(PTR_DAT_71052a3860 + 0x40);
    param_1[0x11] = 0;
    FUN_71000b1cf0(param_1 + 0xd);
    FUN_71000b1cf0(param_1 + 9);
    FUN_71000b1cf0(param_1 + 5);
    FUN_71000b1cf0(param_1 + 1);
    FUN_71000bed20(param_1 + -3);
}

// ---- Type-stamped struct init variants (5 variants, 96 bytes each) ------------
// All start by setting base vtable (PTR_3b58), clearing fields via memset, then
// switching to a type-specific vtable and setting a type ID in param_1[1].

// 0x7100129c40 — type 3 init (no extra param)
void FUN_7100129c40(s64 *param_1)
{
    *(u32 *)(param_1 + 1) = 0;
    *param_1 = (s64)(PTR_DAT_71052a3b58 + 0x10);
    memset((void *)((s64)param_1 + 0xc), 0, 0xb);
    *(u32 *)(param_1 + 3) = 0;
    *param_1 = (s64)(PTR_DAT_71052a3b60 + 0x10);
    *(u32 *)(param_1 + 1) = 3;
}

// 0x7100129ca0 — type 3 init with extra param stored at [3]
void FUN_7100129ca0(s64 *param_1, u32 param_2)
{
    *(u32 *)(param_1 + 1) = 0;
    *param_1 = (s64)(PTR_DAT_71052a3b58 + 0x10);
    memset((void *)((s64)param_1 + 0xc), 0, 0xb);
    *(u32 *)(param_1 + 3) = param_2;
    *param_1 = (s64)(PTR_DAT_71052a3b60 + 0x10);
    *(u32 *)(param_1 + 1) = 3;
}

// 0x710012a160 — type 5 init (no extra param)
void FUN_710012a160(s64 *param_1)
{
    *(u32 *)(param_1 + 1) = 0;
    *param_1 = (s64)(PTR_DAT_71052a3b58 + 0x10);
    memset((void *)((s64)param_1 + 0xc), 0, 0xb);
    *(u32 *)(param_1 + 3) = 0;
    *param_1 = (s64)(PTR_DAT_71052a3b68 + 0x10);
    *(u32 *)(param_1 + 1) = 5;
}

// 0x710012a1c0 — type 5 init with extra param
void FUN_710012a1c0(s64 *param_1, u32 param_2)
{
    *(u32 *)(param_1 + 1) = 0;
    *param_1 = (s64)(PTR_DAT_71052a3b58 + 0x10);
    memset((void *)((s64)param_1 + 0xc), 0, 0xb);
    *(u32 *)(param_1 + 3) = param_2;
    *param_1 = (s64)(PTR_DAT_71052a3b68 + 0x10);
    *(u32 *)(param_1 + 1) = 5;
}

// 0x710012a3c0 — type 6 init with extra fields zeroed
void FUN_710012a3c0(s64 *param_1)
{
    *(u32 *)(param_1 + 1) = 0;
    *param_1 = (s64)(PTR_DAT_71052a3b58 + 0x10);
    memset((void *)((s64)param_1 + 0xc), 0, 0xb);
    param_1[3] = 0;
    *(u32 *)(param_1 + 0x68) = 0;
    *param_1 = (s64)(PTR_DAT_71052a3b70 + 0x10);
    *(u32 *)(param_1 + 1) = 6;
}

// 0x710012a740 — type 7 init (no extra field)
void FUN_710012a740(s64 *param_1)
{
    *(u32 *)(param_1 + 1) = 0;
    *param_1 = (s64)(PTR_DAT_71052a3b58 + 0x10);
    memset((void *)((s64)param_1 + 0xc), 0, 0xb);
    *param_1 = (s64)(PTR_DAT_71052a3b78 + 0x10);
    *(u32 *)(param_1 + 1) = 7;
}

// 0x7100130550 — UpdateSessionSetting ctor + vtable + 2x memset + u64 sentinel (96 bytes)
void FUN_7100130550(s64 *param_1)
{
    nn::pia::session::UpdateSessionSetting_ctor();
    *(u64 *)((s64)param_1 + 0xc) = 0xffffffff;
    *(u32 *)((s64)param_1 + 0x1ac) = 0;
    *param_1 = (s64)(PTR_DAT_71052a3ba8 + 0x10);
    memset((void *)((s64)param_1 + 0x14), 0, 0x18);
    memset((void *)((s64)param_1 + 0x2c), 0, 0x180);
}

// 0x710013b4d0 — call FUN_710013be00 + vtable switch + store param_3 (96 bytes)
void FUN_710013b4d0(s64 *param_1, u64 param_2, s64 param_3, u64 param_4,
                    u32 param_5, u32 param_6, u64 param_7, u32 param_8, u32 param_9)
{
    FUN_710013be00(param_1, param_2, param_4, param_5, param_6, param_7, param_8, param_9);
    param_1[0x1e] = param_3;
    *param_1 = (s64)(PTR_DAT_71052a3cf8 + 0x10);
}

// 0x710013dae0 — load singleton, init error result, call helper (96 bytes)
void FUN_710013dae0(u64 param_1, u32 param_2, u32 param_3, u64 param_4)
{
    u32 local[4];
    u64 uVar1 = PTR_s_pInstance_71052a3080;
    FUN_71000bce50(local, (u32 *)param_4);
    FUN_7100147420(uVar1, param_2, param_3, (u8 *)local);
}

// 0x710013e610 — vtable + FUN_710015ff20 + CallContext dtor + FUN_71000b4760 (96 bytes)
void FUN_710013e610(s64 *param_1)
{
    *param_1 = (s64)(PTR_DAT_71052a3dc8 + 0x10);
    FUN_710015ff20(param_1 + 0x12);
    nn::pia::common::CallContext_dtor(param_1 + 0xc);
    FUN_71000b4760(param_1);
}

// ---- SignalCancel/Reset sequence (2 identical instances, 96 bytes each) --------

// 0x710014bf10
void FUN_710014bf10(s64 param_1)
{
    if (*(s32 **)(param_1 + 0x58) != nullptr) {
        if (**(s32 **)(param_1 + 0x58) == 1) {
            nn::pia::common::CallContext_SignalCancel(nullptr);
        }
        *(u64 *)(param_1 + 0x58) = 0;
    }
    void *piVar1 = (void *)(param_1 + 0x60);
    if (*(s32 *)piVar1 == 1) {
        nn::pia::common::CallContext_SignalCancel(piVar1);
    }
    nn::pia::common::CallContext_Reset(piVar1);
}

// 0x710014c8a0 — identical pattern
void FUN_710014c8a0(s64 param_1)
{
    if (*(s32 **)(param_1 + 0x58) != nullptr) {
        if (**(s32 **)(param_1 + 0x58) == 1) {
            nn::pia::common::CallContext_SignalCancel(nullptr);
        }
        *(u64 *)(param_1 + 0x58) = 0;
    }
    void *piVar1 = (void *)(param_1 + 0x60);
    if (*(s32 *)piVar1 == 1) {
        nn::pia::common::CallContext_SignalCancel(piVar1);
    }
    nn::pia::common::CallContext_Reset(piVar1);
}

// 0x710014fe30 — vtable + zero fields + ListBase::Init (96 bytes)
void FUN_710014fe30(s64 *param_1)
{
    *param_1 = (s64)(PTR_DAT_71052a3f58 + 0x10);
    param_1[1] = 0;
    param_1[2] = 0;
    nn::pia::common::ListBase::Init_default();
    param_1[4] = 0;
    param_1[5] = 0;
    nn::pia::common::ListBase::Init(param_1 + 4);
    param_1[7] = 0;
    *(u32 *)(param_1 + 8) = 0;
    *(u32 *)((s64)param_1 + 0x34) = 0;
    param_1[9] = 0;
}

// 0x7100153310 — guard init + vtable + field zero + FUN_7100157940 (96 bytes)
void FUN_7100153310(s64 *param_1)
{
    FUN_7100154130();
    *param_1 = (s64)(PTR_DAT_71052a3f88 + 0x10);
    param_1[6] = 0;
    param_1[7] = 0;
    FUN_7100157940(param_1 + 8);
    param_1[0x19] = 0;
    param_1[0x1a] = 0;
    param_1[0x1b] = 0;
    *(u32 *)(param_1 + 0x1c) = 0;
    *(u32 *)(param_1 + 0x21) = 0;
    param_1[0x1d] = (s64)param_1;
    param_1[0x1e] = 0;
    param_1[0x1f] = 0;
    param_1[0x20] = 0;
}
