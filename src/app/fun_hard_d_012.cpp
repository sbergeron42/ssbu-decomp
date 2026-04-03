#include "types.h"

// HARD-tier FUN_* functions — 0x7100 address range, batch hard-d-012
// Pool-d worker: nn::pia/pead cleanup, float blend, random init, ctxt reset (96B each)

#define HIDDEN __attribute__((visibility("hidden")))

extern "C" {
    void  operator_delete(void *);  // C++ delete via thunk
}

// ---- External data -------------------------------------------------------

extern u8 *PTR_DAT_71052a2388 HIDDEN;  // guard byte (singleton init flag)

// Vtable bases
extern u8 *PTR_DAT_71052a2d98 HIDDEN;
extern u8 *PTR_DAT_71052a2ed0 HIDDEN;
extern u8 *PTR_DAT_71052a3108 HIDDEN;

// Pointer-to-pointer cleanup globals (store pointer/size)
extern u8 *PTR_DAT_71052a2c38 HIDDEN;  // ptr-to-ptr for cleanup
extern u8 *PTR_DAT_71052a2c40 HIDDEN;  // ptr-to-ptr for heap array
extern u8 *PTR_DAT_71052a2cf0 HIDDEN;  // same pattern
extern u8 *PTR_DAT_71052a2cf8 HIDDEN;

// Singleton init globals (flag + data + fn-ptr + loop-label)
extern u8  *PTR_DAT_71052a2958 HIDDEN; // data ptr
extern u8  *PTR_DAT_71052a2960 HIDDEN; // init-guard byte
extern u64  PTR_FUN_71052a2968 HIDDEN; // function pointer
extern u64  PTR_DAT_71052a2988 HIDDEN; // TagProcessor data ptr
extern u8  *PTR_DAT_71052a2990 HIDDEN; // init-guard byte (TagProcessor)
extern u64  PTR_FUN_71052a2998 HIDDEN; // function pointer (TagProcessor)
extern u64  PTR_LOOP_7104f15000 HIDDEN; // code-address (loop label)

// Vtable-base for FUN_71000cad00
extern u8 *PTR_DAT_71052a2d20 HIDDEN;

// Global array to reset (FUN_71000b3cb0), using DAT_ names at 0x7104f484xx
extern u64 DAT_7104f48428 HIDDEN;
extern u64 DAT_7104f48430 HIDDEN;
extern u64 DAT_7104f48438 HIDDEN;
extern u64 DAT_7104f48440 HIDDEN;
extern u32 DAT_7104f48448 HIDDEN;
extern u32 DAT_7104f48450 HIDDEN;
extern u32 DAT_7104f48458 HIDDEN;
extern u32 DAT_7104f48460 HIDDEN;
extern u32 DAT_7104f48468 HIDDEN;
extern u32 DAT_7104f48470 HIDDEN;
extern u32 DAT_7104f48478 HIDDEN;
extern u32 DAT_7104f48480 HIDDEN;
extern u32 DAT_7104f48488 HIDDEN;
extern u32 DAT_7104f48490 HIDDEN;
extern u32 DAT_7104f48498 HIDDEN;
extern u32 DAT_7104f484a0 HIDDEN;
extern u32 DAT_7104f484a8 HIDDEN;
extern u32 DAT_7104f484b0 HIDDEN;
extern u32 DAT_7104f484b8 HIDDEN;
extern u32 DAT_7104f484c0 HIDDEN;

// ---- External functions --------------------------------------------------

extern void FUN_710007d470(u8 *);
extern void FUN_71000001c0(u64, u8 *, u64 *);
extern u64  FUN_71000af810(u64 *);
extern void FUN_710015ff20(s64 *);
extern void FUN_710015fde0(s64 *);
extern void FUN_71000b1cf0(s64 *);
extern void FUN_71000b2ea0(void);
extern void FUN_71000bc690(void);
extern void FUN_71000bce50(u64, u32 *);
extern void FUN_71000c8350(s64, u8 *, u32);
extern void FUN_7100160230(u8 **, s64);
extern void FUN_7100160380(u64);
extern void FUN_71000d8f90(void);

// SDK namespace declarations
namespace nn {
namespace pia {
namespace common {
    void CallContext_dtor(s64 *);     // CallContext::~CallContext
    void CallContext_Reset(void *);    // CallContext::Reset
    void CallContext_SignalCancel(void *); // CallContext::SignalCancel
    bool InetAddress_IsValid();        // InetAddress::IsValid (static)
    void InetAddress_ctor(u8 *, s64); // InetAddress::InetAddress(src)
    void InetAddress_ctor_copy(u8 *, u8 *); // copy ctor
    void InetAddress_assign(s64);      // InetAddress::operator=(src)
}
}
namespace nex {
    void CallContext_Cancel(s64);    // CallContext::Cancel
    void CallContext_Reset(s64);     // CallContext::Reset
}
namespace font {
    void TagProcessorBaseIc_ctor(u64); // TagProcessorBaseIc::TagProcessorBaseIc
}
}

namespace pead {
    void getArraySize(s64);
    void freeToSeadHeap(void *);
    namespace Random {
        void init(u8 *);
        u64  getU64(u8 *);
    }
}

// ---- Functions ---------------------------------------------------------------

// 0x7100070890 — vtable[0xc] color-mode query + conditional float swap (96 bytes)
void FUN_7100070890(float param_1, float param_2, s64 *param_3)
{
    s32 iVar1 = (*(s32(*)(void))((*param_3) + 0x60))();
    if (iVar1 == 1) {
        float fVar2 = 1.0f - param_2;
        param_2 = 1.0f - param_1;
        *(float *)(param_3 + 1) = fVar2;
    } else {
        if (iVar1 != 0) {
            return;
        }
        *(float *)(param_3 + 1) = param_1;
    }
    *(float *)((s64)param_3 + 0xc) = param_2;
}

// 0x7100083be0 — singleton init guard: check flag byte, init data, register loop (96 bytes)
void FUN_7100083be0(void)
{
    if ((*PTR_DAT_71052a2960 & 1) == 0) {
        FUN_710007d470(PTR_DAT_71052a2958);
        FUN_71000001c0(PTR_FUN_71052a2968, PTR_DAT_71052a2958, &PTR_LOOP_7104f15000);
        *(u64 *)PTR_DAT_71052a2960 = 1;
    }
}

// 0x71000853d0 — singleton init guard: check flag byte, nn::font ctor, register loop (96 bytes)
void FUN_71000853d0(void)
{
    if ((*PTR_DAT_71052a2990 & 1) == 0) {
        nn::font::TagProcessorBaseIc_ctor(PTR_DAT_71052a2988);
        FUN_71000001c0(PTR_FUN_71052a2998, (u8 *)PTR_DAT_71052a2988, &PTR_LOOP_7104f15000);
        *(u64 *)PTR_DAT_71052a2990 = 1;
    }
}

// 0x710008d030 — struct field init: set type bytes + call FUN_71000af810 twice (96 bytes)
void FUN_710008d030(u64 *param_1, u64 param_2)
{
    *param_1 = param_2;
    *(u32 *)(param_1 + 4) = 0x101;
    *(u64 *)((s64)param_1 + 0x24) = 0x417fd70a;
    u64 uVar1 = (u64)FUN_71000af810(param_1 + 3);
    param_1[1] = uVar1;
    *(u32 *)(param_1 + 8) = 0x202;
    *(u64 *)((s64)param_1 + 0x44) = 0x417fd70a;
    uVar1 = (u64)FUN_71000af810(param_1 + 7);
    param_1[2] = uVar1;
}

// 0x71000b3050 — conditional cleanup: drain singleton, free heap array (96 bytes)
void FUN_71000b3050(void)
{
    if (*(s64 *)PTR_DAT_71052a2c38 != 0) {
        FUN_71000b2ea0();
        *(u64 *)PTR_DAT_71052a2c38 = 0;
    }
    s64 lVar2 = *(s64 *)PTR_DAT_71052a2c40;
    if (lVar2 != 0) {
        pead::getArraySize(lVar2);
        pead::freeToSeadHeap((void *)lVar2);
        *(u64 *)PTR_DAT_71052a2c40 = 0;
    }
}

// 0x71000b3cb0 — reset global slot array: alternating 0/0xffff sentinel init (96 bytes)
void FUN_71000b3cb0(void)
{
    DAT_7104f48440 = 0xffffffffffffffff;
    DAT_7104f48428 = 0;
    DAT_7104f48430 = 0;
    DAT_7104f48438 = 0;
    DAT_7104f48448 = 0xffffffff;
    DAT_7104f48450 = 0;
    DAT_7104f48458 = 0xffffffff;
    DAT_7104f48460 = 0;
    DAT_7104f48468 = 0xffffffff;
    DAT_7104f48470 = 0;
    DAT_7104f48478 = 0xffffffff;
    DAT_7104f48480 = 0;
    DAT_7104f48488 = 0xffffffff;
    DAT_7104f48490 = 0;
    DAT_7104f48498 = 0xffffffff;
    DAT_7104f484a0 = 0;
    DAT_7104f484a8 = 0xffffffff;
    DAT_7104f484b0 = 0;
    DAT_7104f484b8 = 0xffffffff;
    DAT_7104f484c0 = 0;
}

// 0x71000bc630 — same pattern as FUN_71000b3050 with different globals (96 bytes)
void FUN_71000bc630(void)
{
    if (*(s64 *)PTR_DAT_71052a2cf0 != 0) {
        FUN_71000bc690();
        *(u64 *)PTR_DAT_71052a2cf0 = 0;
    }
    s64 lVar2 = *(s64 *)PTR_DAT_71052a2cf8;
    if (lVar2 != 0) {
        pead::getArraySize(lVar2);
        pead::freeToSeadHeap((void *)lVar2);
        *(u64 *)PTR_DAT_71052a2cf8 = 0;
    }
}

// 0x71000bf7b0 — fill pead::Random u64 seeds from stack RNG (96 bytes)
void FUN_71000bf7b0(u64 *param_1)
{
    u8 local[16];
    *param_1 = 0;
    pead::Random::init(local);
    u64 uVar1 = pead::Random::getU64(local);
    param_1[4] = uVar1;
    uVar1 = pead::Random::getU64(local);
    param_1[5] = uVar1;
    uVar1 = pead::Random::getU64(local);
    param_1[3] = uVar1;
    *param_1 = 0;
}

// 0x71000c3380 — vtable + FUN_710015ff20 + 3x CallContext dtor + delete (96 bytes)
void FUN_71000c3380(s64 *param_1)
{
    *param_1 = (s64)(PTR_DAT_71052a2d98 + 0x10);
    FUN_710015ff20(param_1 + 0x32);
    nn::pia::common::CallContext_dtor(param_1 + 0x27);
    nn::pia::common::CallContext_dtor(param_1 + 0x21);
    nn::pia::common::CallContext_dtor(param_1 + 0x1b);
    operator_delete(param_1);
}

// 0x71000c82f0 — InetAddress copy + FUN_71000c8350 + 2x CallContext dtor (96 bytes)
void FUN_71000c82f0(s64 param_1)
{
    u8 local_70[32];
    u8 local_50[32];
    u64 local_30 = 0;
    u64 local_28 = 0;
    nn::pia::common::InetAddress_ctor(local_70, param_1 + 0x40);
    nn::pia::common::InetAddress_ctor_copy(local_50, local_70);
    FUN_71000c8350(param_1, local_50, 5);
    FUN_71000b1cf0((s64 *)local_50);
    FUN_71000b1cf0((s64 *)local_70);
}

// 0x71000cad00 — FUN_7100160230 + set vtable + CallContext dtor + return u16 diff (96 bytes)
s32 FUN_71000cad00(s64 param_1)
{
    u8 *local_48;
    u8 local_40[24];
    u16 local_28;
    FUN_7100160230(&local_48, param_1 + 8);
    u16 uVar1 = *(u16 *)(param_1 + 0xac);
    local_48 = PTR_DAT_71052a2d20 + 0x10;
    FUN_71000b1cf0((s64 *)local_40);
    return (s32)(u32)local_28 - (s32)(u32)uVar1;
}

// 0x71000cf850 — vtable + FUN_710015fde0 + clear fields + InetAddress::IsValid check (96 bytes)
void FUN_71000cf850(s64 *param_1, u64 param_2)
{
    *param_1 = (s64)(PTR_DAT_71052a2ed0 + 0x10);
    FUN_710015fde0(param_1 + 1);
    *(u8 *)(param_1 + 0x11) = 0;
    param_1[0x12] = 0;
    param_1[0x13] = 0;
    FUN_7100160380(param_2);
    bool bVar1 = nn::pia::common::InetAddress_IsValid();
    *(u8 *)((s64)param_1 + 0x89) = (u8)(bVar1 & 1);
}

// 0x71000ecf50 — vtable + conditional vtable[0] call + pead::free + delete (96 bytes)
void FUN_71000ecf50(s64 *param_1)
{
    u64 *puVar1 = (u64 *)param_1[0x5b];
    *param_1 = (s64)(PTR_DAT_71052a3108 + 0x10);
    if (puVar1 != nullptr) {
        (*(void (**)(u64 *))(*puVar1))(puVar1);
        pead::freeToSeadHeap(puVar1);
        param_1[0x5b] = 0;
    }
    operator_delete(param_1);
}

// 0x71001077a0 — SignalCancel if active + Reset + conditional outer-ctx clear (96 bytes)
void FUN_71001077a0(s64 param_1)
{
    s32 *piVar1 = (s32 *)(param_1 + 0x60);
    if (*piVar1 == 1) {
        nn::pia::common::CallContext_SignalCancel(piVar1);
    }
    nn::pia::common::CallContext_Reset(piVar1);
    if (*(s64 *)(param_1 + 0x90) != 0) {
        FUN_71000d8f90();
        *(u64 *)(param_1 + 0x90) = 0;
    }
    if (*(s32 **)(param_1 + 0x58) != nullptr) {
        if (**(s32 **)(param_1 + 0x58) == 1) {
            nn::pia::common::CallContext_SignalCancel(nullptr);
        }
        *(u64 *)(param_1 + 0x58) = 0;
    }
}

// 0x710010f110 — nex::CallContext::Cancel/Reset + pia::SignalCancel + clear (96 bytes)
void FUN_710010f110(s64 param_1)
{
    if (*(s32 *)(param_1 + 0x74) == 1) {
        nn::nex::CallContext_Cancel(param_1 + 0x60);
    }
    nn::nex::CallContext_Reset(param_1 + 0x60);
    if (*(s32 **)(param_1 + 0x58) != nullptr && **(s32 **)(param_1 + 0x58) == 1) {
        nn::pia::common::CallContext_SignalCancel(nullptr);
        *(u64 *)(param_1 + 0x58) = 0;
    }
}
