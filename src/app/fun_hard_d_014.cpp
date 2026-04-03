#include "types.h"

// HARD-tier FUN_* functions — 0x7100 address range, batch hard-d-014
// Pool-d worker: shared_ptr dtor, StationAddress, ListBase drain, dtor patterns, hex encode (96B each)

#define HIDDEN __attribute__((visibility("hidden")))

extern "C" {
    int sprintf(char *buf, const char *fmt, ...);
}

// ---- External data -------------------------------------------------------

// Vtable bases
extern u8 *PTR_DAT_71052a2618 HIDDEN;
extern u8 *PTR_DAT_71052a2d80 HIDDEN;
extern u8 *PTR_DAT_71052a41e0 HIDDEN;
extern u8 *PTR_DAT_71052a4210 HIDDEN;
extern u8 *PTR_DAT_71052a4228 HIDDEN;
extern u8 *PTR_DAT_71052a4418 HIDDEN;
extern u8 *PTR_DAT_71052a4438 HIDDEN;
extern u8 *PTR_DAT_71052a4478 HIDDEN;

// Function-pointer vtable base (stored directly as address, not pointer+offset)
extern u64 PTR_FUN_710523f540 HIDDEN;

// ---- External functions --------------------------------------------------

extern void FUN_7100056c40(void);
extern void FUN_71000b4760(s64 *);
extern void FUN_71000b1cf0(s64 *);
extern void FUN_71000beb80(u8 *, void *, s64);
extern u64  FUN_71000b2b10(s64, s64);
extern void FUN_71001b52b0(s64 *, s64);
extern void FUN_71001d7920(s64, s64, s64);
extern void FUN_shared_weak_release(s64 *); // std::__1::__shared_weak_count::__release_weak

extern "C" {
    void operator_delete(void *);
}

namespace nn {
namespace pia {
namespace common {
    void CallContext_dtor(s64 *);
    void StationAddress_ctor(void *);
    bool InetAddress_IsValid(s64);
    namespace ListBase {
        void Init(u64 *);
        void InsertAfterNode(u64 *, u64 *, s64);
    }
}
}
}

namespace pead {
    void freeToSeadHeap(void *);
}

// ---- Functions ---------------------------------------------------------------

// 0x7100068190 — shared_ptr atomic release dtor: vtable swap + 2x shared_weak release (96 bytes)
void FUN_7100068190(s64 *param_1)
{
    *param_1 = (s64)&PTR_FUN_710523f540;
    if (*(u8 *)((s64)param_1 + 0x235) != 0) {
        if (param_1[0x26] != 0) {
            s64 lVar4 = param_1[0x23];
            if (lVar4 != 0 && (*(u8 *)(lVar4 + 0x14) & 3) != 0) {
                *(s64 *)(*(s64 *)(lVar4 + 0x18) + 8) = param_1[0x26];
            }
        }
        *(u8 *)((s64)param_1 + 0x235) = 0;
    }
    s64 *p_Var5 = (s64 *)param_1[0x28];
    param_1[0x27] = 0;
    param_1[0x28] = 0;
    if (p_Var5 == nullptr) {
        *(u8 *)((s64)param_1 + 0x236) = 0;
    } else {
        s64 lVar4 = __sync_fetch_and_add(p_Var5 + 1, -1LL);
        if (lVar4 == 0) {
            (*(void(**)(s64 *))(*p_Var5 + 0x10))(p_Var5);
            FUN_shared_weak_release(p_Var5);
        }
        p_Var5 = (s64 *)param_1[0x28];
        *(u8 *)((s64)param_1 + 0x236) = 0;
        if (p_Var5 != nullptr) {
            lVar4 = __sync_fetch_and_add(p_Var5 + 1, -1LL);
            if (lVar4 == 0) {
                (*(void(**)(s64 *))(*p_Var5 + 0x10))(p_Var5);
                FUN_shared_weak_release(p_Var5);
            }
        }
    }
    *param_1 = (s64)(PTR_DAT_71052a2618 + 0x10);
    FUN_7100056c40();
}

// 0x7100160230 — StationAddress ctor + conditional offset + FUN_71000beb80 (96 bytes)
void FUN_7100160230(void *param_1, s64 param_2)
{
    u8 auStack_30[16];
    nn::pia::common::StationAddress_ctor(param_1);
    if (*(s8 *)(param_2 + 0x7b) == 1) {
        param_2 += 0x28;
    } else {
        param_2 += 8;
    }
    FUN_71000beb80(auStack_30, param_1, param_2);
}

// 0x7100163190 — drain linked list into offset sub-list, then ListBase::Init (96 bytes)
void FUN_7100163190(u64 *param_1)
{
    if ((u64 *)param_1[1] != param_1) {
        u64 *puVar1 = (u64 *)param_1[1];
        u64 *puVar2;
        do {
            puVar2 = (u64 *)puVar1[1];
            *puVar1 = 0;
            puVar1[1] = 0;
            nn::pia::common::ListBase::InsertAfterNode(
                param_1 + 3, param_1 + 3,
                (s64)*(s32 *)((s64)param_1 + 0x2c) + (s64)puVar1);
            puVar1 = puVar2;
        } while (puVar2 != param_1);
    }
    nn::pia::common::ListBase::Init(param_1);
}

// ---- Simple dtor: zero [0xc], set vtable, FUN_71000b4760 (2 variants, 96 bytes each) ----

// 0x7100173ec0
void FUN_7100173ec0(s64 *param_1)
{
    param_1[0xc] = 0;
    *param_1 = (s64)(PTR_DAT_71052a41e0 + 0x10);
    FUN_71000b4760(param_1);
}

// 0x7100175910
void FUN_7100175910(s64 *param_1)
{
    param_1[0xc] = 0;
    *param_1 = (s64)(PTR_DAT_71052a4210 + 0x10);
    FUN_71000b4760(param_1);
}

// 0x7100175d00 — vtable + conditional CallContext dtor + free + zero [0xf] + delete (96 bytes)
void FUN_7100175d00(s64 *param_1)
{
    s64 lVar1 = param_1[0xc];
    *param_1 = (s64)(PTR_DAT_71052a4228 + 0x10);
    if (lVar1 != 0) {
        nn::pia::common::CallContext_dtor((s64 *)lVar1);
        pead::freeToSeadHeap((void *)lVar1);
    }
    param_1[0xf] = 0;
    FUN_71000b4760(param_1);
    operator_delete(param_1);
}

// 0x71001800a0 — check two InetAddresses valid, then call FUN_71000b2b10 (96 bytes)
u64 FUN_71001800a0(s64 param_1)
{
    if ((nn::pia::common::InetAddress_IsValid(param_1 + 0x2c0) & 1) != 0) {
        if ((nn::pia::common::InetAddress_IsValid(param_1 + 0x2a0) & 1) != 0) {
            return FUN_71000b2b10(param_1 + 0x2a0, param_1 + 0x2c0);
        }
    }
    return 0;
}

// ---- CallContext dtor + freeToSeadHeap + zero field + FUN_71000b4760 + delete (3 variants, 96 bytes each) ----

// 0x7100183390 — zero [0xd]
void FUN_7100183390(s64 *param_1)
{
    s64 lVar1 = param_1[0xc];
    *param_1 = (s64)(PTR_DAT_71052a4418 + 0x10);
    if (lVar1 != 0) {
        nn::pia::common::CallContext_dtor((s64 *)lVar1);
        pead::freeToSeadHeap((void *)lVar1);
    }
    param_1[0xd] = 0;
    FUN_71000b4760(param_1);
    operator_delete(param_1);
}

// 0x71001838c0 — zero [0x11]
void FUN_71001838c0(s64 *param_1)
{
    s64 lVar1 = param_1[0xc];
    *param_1 = (s64)(PTR_DAT_71052a4438 + 0x10);
    if (lVar1 != 0) {
        nn::pia::common::CallContext_dtor((s64 *)lVar1);
        pead::freeToSeadHeap((void *)lVar1);
    }
    param_1[0x11] = 0;
    FUN_71000b4760(param_1);
    operator_delete(param_1);
}

// 0x7100184160 — zero [0xd] (different vtable)
void FUN_7100184160(s64 *param_1)
{
    s64 lVar1 = param_1[0xc];
    *param_1 = (s64)(PTR_DAT_71052a4478 + 0x10);
    if (lVar1 != 0) {
        nn::pia::common::CallContext_dtor((s64 *)lVar1);
        pead::freeToSeadHeap((void *)lVar1);
    }
    param_1[0xd] = 0;
    FUN_71000b4760(param_1);
    operator_delete(param_1);
}

// 0x71001d00c0 — vtable + buffer init + sprintf "%02X" hex-encode loop (96 bytes)
u32 FUN_71001d00c0(s64 *param_1, s64 param_2)
{
    *param_1 = (s64)(PTR_DAT_71052a2d80 + 0x10);
    *(u8 *)(param_1 + 1) = 0;
    param_1[3] = (s64)(param_1 + 1);
    param_1[4] = 0x10;
    FUN_71001b52b0(param_1, *(s64 *)(param_2 + 0x18) << 1);
    s64 lVar3 = *(s64 *)(param_2 + 0x18);
    s64 lVar2 = param_1[3];
    if (lVar3 == 0) {
        return 0;
    }
    u32 uVar4 = 0;
    u8 *pbVar5 = (u8 *)(*(s64 *)(param_2 + 0x10) + *(s64 *)(param_2 + 0x28));
    do {
        s32 iVar1 = sprintf((char *)(lVar2 + (u64)uVar4), "%02X", (u32)*pbVar5);
        uVar4 = iVar1 + uVar4;
        lVar3 -= 1;
        pbVar5 += 1;
    } while (lVar3 != 0);
    return uVar4;
}

// 0x71001d7680 — buffer assignment: skip self, compute end ptr, call FUN_71001d7920 (96 bytes)
s64 FUN_71001d7680(s64 param_1, s64 param_2)
{
    if (param_2 != param_1) {
        s64 lVar1;
        if (*(s64 *)(param_1 + 0x30) == 0) {
            lVar1 = *(s64 *)(param_1 + 0x10);
        } else {
            lVar1 = *(s64 *)(param_1 + 0x10) + *(s64 *)(param_1 + 0x30);
        }
        *(s64 *)(param_1 + 0x18) = lVar1;
        *(s64 *)(param_1 + 0x20) = lVar1;
        FUN_71001d7920(param_1, param_2 + 0x18, param_2 + 0x20);
    }
    return param_1;
}
