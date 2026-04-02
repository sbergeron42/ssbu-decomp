#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7103 address range, batch d-003
// Pool-d worker: auto-generated from Ghidra decompilation

// ---- External declarations -----------------------------------------------

extern "C" {
    int   __cxa_guard_acquire(u64*);
    void  __cxa_guard_release(u64*);
    void* memcpy(void*, const void*, u64);
    void* je_aligned_alloc(u64, u64);
}

extern void FUN_71037aeec0(s64);
extern void FUN_71031f4740(u64);
extern u64  FUN_7103799b10();
extern u32  FUN_71037aed30(u32, s64);
extern u32  FUN_71037aed80(void*, void*);
extern u32  FUN_71037b0850(s64, s64);
extern u32  FUN_71037aec40(s64, s64);
extern u32  FUN_71037afad0(void*, void*);
extern void FUN_71037a1cc0(u64, u64, u32, u32);

namespace nn { namespace os {
    extern void sched_getcpu();
}}

// External data
extern u8 DAT_710593ab58[];
extern u8 DAT_710593ab60[];
extern u8 DAT_710593ab68[];
extern u8 DAT_710593ab70[];
extern u8 DAT_7105339020[];
extern u8 DAT_7105339008[];
extern u8 DAT_7105338ff8[];
extern u8 DAT_7105339000[];
extern u8 PTR_FUN_7105181f40[];
extern u8 DAT_7105331f20[];
extern s64 *DAT_7105331f00;

// ---- Functions ---------------------------------------------------------------

// 0x71033dc420 — vtable call returning bool: iVar != 1 (160 bytes)
u8 FUN_71033dc420(u64 param_1, s64 param_2)
{
    s32 iVar1 = (*(s32(*)())(*(s64*)(*(s64*)(*(s64*)(param_2 + 0x20) + 0x40)) + 0x110))();
    return (u8)(iVar1 != 1);
}

// 0x7103796c20 — nested guard init with FUN_7103799b10, returns &DAT_710593ab70 (160 bytes)
u64 *FUN_7103796c20(void)
{
    s32 iVar1;

    if (((*(u64*)DAT_710593ab58 & 1) == 0) &&
        (iVar1 = __cxa_guard_acquire((u64*)DAT_710593ab58), iVar1 != 0)) {
        if (((*(u64*)DAT_710593ab60 & 1) == 0) &&
            (iVar1 = __cxa_guard_acquire((u64*)DAT_710593ab60), iVar1 != 0)) {
            *(u64*)DAT_710593ab68 = FUN_7103799b10();
            __cxa_guard_release((u64*)DAT_710593ab60);
        }
        *(u8**)DAT_710593ab70 = DAT_710593ab68;
        __cxa_guard_release((u64*)DAT_710593ab58);
    }
    return (u64*)DAT_710593ab70;
}

// 0x71037b0b30 — call FUN_71037aeec0 on three consecutive fields (160 bytes)
void FUN_71037b0b30(s64 param_1)
{
    FUN_71037aeec0(param_1);
    FUN_71037aeec0(param_1 + 8);
    FUN_71037aeec0(param_1 + 0x10);
}

// 0x71033640c0 — vtable dispatch at offset 0x18 (168 bytes)
u32 FUN_71033640c0(s64 *param_1)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (*(void(*)(s64*))(*in_x8 + 0x18))(in_x8);
    return 0;
}

// 0x7103364460 — vtable dispatch at offset 8 (168 bytes)
u32 FUN_7103364460(s64 *param_1)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (*(void(*)(s64*))(*in_x8 + 8))(in_x8);
    return 0;
}

// 0x710341aac0 — vtable call at 0x98 returning bool: 3 < iVar (176 bytes)
u8 FUN_710341aac0(u64 param_1, s64 param_2)
{
    s64 *plVar2 = *(s64**)(*(s64*)(param_2 + 0x20) + 0x50);
    s32 iVar1 = (*(s32(*)(s64*, u32))(*(s64 *)(*plVar2 + 0x98)))(plVar2, 0x10000005);
    return (u8)(3 < iVar1);
}

// 0x7103541c00 — je_aligned_alloc with OOM handler fallback (176 bytes)
s64 *FUN_7103541c00(u64 param_1, s64 param_2)
{
    s64 *plVar1;
    u64 uVar2;
    s64 local_28;
    u32 local_14;

    if (param_2 == 0) {
        param_2 = 1;
    }
    plVar1 = (s64*)je_aligned_alloc(8, (u64)param_2);
    if ((plVar1 == nullptr) && (plVar1 = DAT_7105331f00, DAT_7105331f00 != nullptr)) {
        local_14 = 0;
        local_28 = param_2;
        uVar2 = (*(u64(*)(s64*, u32*, s64*))(*DAT_7105331f00 + 0x30))(DAT_7105331f00, &local_14, &local_28);
        if ((uVar2 & 1) == 0) {
            plVar1 = nullptr;
        } else {
            plVar1 = (s64*)je_aligned_alloc(8, (u64)param_2);
        }
    }
    return plVar1;
}

// 0x710335a5fc — wrapper: FUN_71037a1cc0(p1, p2, 0xffffffff, 1) (180 bytes)
u32 FUN_710335a5fc(u64 param_1, u64 param_2)
{
    FUN_71037a1cc0(param_1, param_2, 0xffffffff, 1);
    return 0;
}

// 0x71037b0360 — switch on *(param3+0x6c): compute local_18 from sub-calls (192 bytes)
u64 FUN_71037b0360(u8 param_1[16], u32 param_2, s64 param_3)
{
    u32 local_38;
    u32 local_34;
    u32 local_30;
    u32 local_2c;
    s64 local_28;
    u32 local_18;

    switch (*(u32*)(param_3 + 0x6c)) {
    case 0:
        local_18 = 0;
        break;
    case 1:
        local_18 = (u32)*(u64*)(param_3 + 0x10);
        break;
    case 2:
        local_28 = param_3;
        local_30 = FUN_71037aed30(*(u32*)(param_3 + 0x18), param_3 + 0x10);
        local_2c = param_2;
        local_38 = FUN_71037aed30(*(u32*)(param_3 + 0x3c), param_3 + 0x34);
        local_34 = param_2;
        local_18 = FUN_71037aed80(&local_30, &local_38);
        break;
    case 3:
        local_18 = 0;
        break;
    default:
        local_18 = 0;
    }
    return local_18;
}

// 0x71037b09d0 — switch on *(param3+0x6c): compute local_24 from sub-calls variant (192 bytes)
u64 FUN_71037b09d0(u8 param_1[16], u32 param_2, s64 param_3)
{
    u32 local_40;
    u32 local_3c;
    u32 local_38;
    u32 local_34;
    s64 local_30;
    u32 local_24;

    local_30 = param_3;
    switch (*(u32*)(param_3 + 0x6c)) {
    case 0:
        local_24 = 0;
        break;
    case 1:
        local_24 = 0;
        break;
    case 2:
        local_24 = FUN_71037b0850(param_3 + 0x10, param_3 + 0x34);
        break;
    case 3:
        local_38 = FUN_71037aec40(param_3 + 0x34, param_3 + 0x10);
        local_34 = param_2;
        local_40 = FUN_71037aec40(param_3 + 0x58, param_3 + 0x10);
        local_3c = param_2;
        local_24 = FUN_71037afad0(&local_38, &local_40);
        break;
    default:
        local_24 = 0;
    }
    return local_24;
}

// 0x71039505b0 — wrapper: call nn::os::sched_getcpu() (192 bytes)
void FUN_71039505b0(void)
{
    nn::os::sched_getcpu();
}

// 0x71031cfbe0 — call FUN_71031f4740, return 1 (192 bytes)
u64 FUN_71031cfbe0(s64 param_1)
{
    FUN_71031f4740(*(u64*)(param_1 + 8));
    return 1;
}

// 0x71031cfd10 — vtable call at 0x20, return 1 (192 bytes)
u64 FUN_71031cfd10(s64 *param_1)
{
    (*(void(*)(s64*))(*(s64 *)(*param_1 + 0x20)))(param_1);
    return 1;
}

// 0x71036e5780 — vtable call + guard init, return struct ptr (160 bytes)
u64 *FUN_71036e5780(s64 *param_1)
{
    s32 iVar1;
    s64 lVar2;
    s64 *plVar3;

    lVar2 = (*(s64(*)())(*(s64*)(*param_1 + 0x108)))();
    plVar3 = *(s64**)(*(s64*)(lVar2 + 8) + 0x120);
    if (plVar3 != nullptr) {
        return (u64*)(*(s64*)(*plVar3 + 0x28) + 0x500);
    }
    if (((*(u64*)DAT_7105339020 & 1) == 0) &&
        (iVar1 = __cxa_guard_acquire((u64*)DAT_7105339020), iVar1 != 0)) {
        *(u64*)DAT_7105339008 = 0;
        *(u8**)DAT_7105338ff8 = PTR_FUN_7105181f40;
        *(u64*)DAT_7105339000 = 0xffffffffffffffff;
        __cxa_guard_release((u64*)DAT_7105339020);
    }
    *(u64*)DAT_7105339008 = 0x10001;
    *(u64*)DAT_7105339000 = 0xffffffffffffffff;
    return (u64*)DAT_7105338ff8;
}
