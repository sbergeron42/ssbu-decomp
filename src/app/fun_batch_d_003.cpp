#include "types.h"
#include "app/BattleObjectModuleAccessor.h"

// MEDIUM-tier FUN_* functions -- 0x7103 address range, batch d-003
// Rewritten from Ghidra paste with meaningful names and struct field access

using app::BattleObjectModuleAccessor;

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

// ---- Helper: extract accessor from lua context ----------------------------
#define ACC(p) reinterpret_cast<BattleObjectModuleAccessor*>(*(s64*)((p) + 0x20))

// ---- Functions ---------------------------------------------------------------

// 0x71033dc420 -- status_module vtable[0x110/8]() != 1
u8 FUN_71033dc420(u64 param_1, s64 param_2)
{
    auto* acc = ACC(param_2);
    s64* status_mod = static_cast<s64*>(acc->status_module);
    s32 status_kind = (*(s32(*)())(*(s64*)(*status_mod + 0x110)))();
    return (u8)(status_kind != 1);
}

// 0x7103796c20 -- static init: nested guard with FUN_7103799b10, returns &DAT_710593ab70
u64 *FUN_7103796c20(void)
{
    s32 acquired;

    if (((*(u64*)DAT_710593ab58 & 1) == 0) &&
        (acquired = __cxa_guard_acquire((u64*)DAT_710593ab58), acquired != 0)) {
        if (((*(u64*)DAT_710593ab60 & 1) == 0) &&
            (acquired = __cxa_guard_acquire((u64*)DAT_710593ab60), acquired != 0)) {
            *(u64*)DAT_710593ab68 = FUN_7103799b10();
            __cxa_guard_release((u64*)DAT_710593ab60);
        }
        *(u8**)DAT_710593ab70 = DAT_710593ab68;
        __cxa_guard_release((u64*)DAT_710593ab58);
    }
    return (u64*)DAT_710593ab70;
}

// 0x71037b0b30 -- call FUN_71037aeec0 on three consecutive 8-byte fields
void FUN_71037b0b30(s64 param_1)
{
    FUN_71037aeec0(param_1);
    FUN_71037aeec0(param_1 + 8);
    FUN_71037aeec0(param_1 + 0x10);
}

// 0x71033640c0 -- vtable dispatch via x8 at offset 0x18, return 0
u32 FUN_71033640c0(s64 *obj)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (*(void(*)(s64*))(*in_x8 + 0x18))(in_x8);
    return 0;
}

// 0x7103364460 -- vtable dispatch via x8 at offset 8, return 0
u32 FUN_7103364460(s64 *obj)
{
    register s64 *in_x8 asm("x8");
    asm volatile("" : "+r"(in_x8));
    (*(void(*)(s64*))(*in_x8 + 8))(in_x8);
    return 0;
}

// 0x710341aac0 -- work_module vtable[0x98/8](mod, 0x10000005) > 3
u8 FUN_710341aac0(u64 param_1, s64 param_2)
{
    auto* acc = ACC(param_2);
    s64* work_mod = static_cast<s64*>(acc->work_module);
    s32 work_val = (*(s32(*)(s64*, u32))(*(s64 *)(*work_mod + 0x98)))(work_mod, 0x10000005);
    return (u8)(3 < work_val);
}

// 0x7103541c00 -- je_aligned_alloc(8, size) with OOM handler fallback
s64 *FUN_7103541c00(u64 param_1, s64 size)
{
    s64 *result;
    u64 retry_result;
    s64 requested_size;
    u32 flags;

    if (size == 0) {
        size = 1;
    }
    result = (s64*)je_aligned_alloc(8, (u64)size);
    if ((result == nullptr) && (result = DAT_7105331f00, DAT_7105331f00 != nullptr)) {
        flags = 0;
        requested_size = size;
        retry_result = (*(u64(*)(s64*, u32*, s64*))(*DAT_7105331f00 + 0x30))(DAT_7105331f00, &flags, &requested_size);
        if ((retry_result & 1) == 0) {
            result = nullptr;
        } else {
            result = (s64*)je_aligned_alloc(8, (u64)size);
        }
    }
    return result;
}

// 0x710335a5fc -- wrapper: FUN_71037a1cc0(p1, p2, 0xffffffff, 1)
u32 FUN_710335a5fc(u64 param_1, u64 param_2)
{
    FUN_71037a1cc0(param_1, param_2, 0xffffffff, 1);
    return 0;
}

// 0x71037b0360 -- switch on *(param3+0x6c): compute result from sub-calls
u64 FUN_71037b0360(u8 param_1[16], u32 param_2, s64 param_3)
{
    u32 val_a;
    u32 tag_a;
    u32 val_b;
    u32 tag_b;
    s64 ctx;
    u32 result;

    switch (*(u32*)(param_3 + 0x6c)) {
    case 0:
        result = 0;
        break;
    case 1:
        result = (u32)*(u64*)(param_3 + 0x10);
        break;
    case 2:
        ctx = param_3;
        val_a = FUN_71037aed30(*(u32*)(param_3 + 0x18), param_3 + 0x10);
        tag_a = param_2;
        val_b = FUN_71037aed30(*(u32*)(param_3 + 0x3c), param_3 + 0x34);
        tag_b = param_2;
        result = FUN_71037aed80(&val_a, &val_b);
        break;
    case 3:
        result = 0;
        break;
    default:
        result = 0;
    }
    return result;
}

// 0x71037b09d0 -- switch on *(param3+0x6c): compute result from sub-calls (variant)
u64 FUN_71037b09d0(u8 param_1[16], u32 param_2, s64 param_3)
{
    u32 val_a;
    u32 tag_a;
    u32 val_b;
    u32 tag_b;
    s64 ctx;
    u32 result;

    ctx = param_3;
    switch (*(u32*)(param_3 + 0x6c)) {
    case 0:
        result = 0;
        break;
    case 1:
        result = 0;
        break;
    case 2:
        result = FUN_71037b0850(param_3 + 0x10, param_3 + 0x34);
        break;
    case 3:
        val_a = FUN_71037aec40(param_3 + 0x34, param_3 + 0x10);
        tag_a = param_2;
        val_b = FUN_71037aec40(param_3 + 0x58, param_3 + 0x10);
        tag_b = param_2;
        result = FUN_71037afad0(&val_a, &val_b);
        break;
    default:
        result = 0;
    }
    return result;
}

// 0x71039505b0 -- wrapper: nn::os::sched_getcpu()
void FUN_71039505b0(void)
{
    nn::os::sched_getcpu();
}

// 0x71031cfbe0 -- call FUN_71031f4740 on field at +8, return 1
u64 FUN_71031cfbe0(s64 param_1)
{
    FUN_71031f4740(*(u64*)(param_1 + 8));
    return 1;
}

// 0x71031cfd10 -- vtable dispatch at 0x20, return 1
u64 FUN_71031cfd10(s64 *obj)
{
    (*(void(*)(s64*))(*(s64 *)(*obj + 0x20)))(obj);
    return 1;
}

// 0x71036e5780 -- vtable call + guard init, return struct ptr
u64 *FUN_71036e5780(s64 *obj)
{
    s32 acquired;
    s64 vtable_result;
    s64 *inner_obj;

    vtable_result = (*(s64(*)())(*(s64*)(*obj + 0x108)))();
    inner_obj = *(s64**)(*(s64*)(vtable_result + 8) + 0x120);
    if (inner_obj != nullptr) {
        return (u64*)(*(s64*)(*inner_obj + 0x28) + 0x500);
    }
    if (((*(u64*)DAT_7105339020 & 1) == 0) &&
        (acquired = __cxa_guard_acquire((u64*)DAT_7105339020), acquired != 0)) {
        *(u64*)DAT_7105339008 = 0;
        *(u8**)DAT_7105338ff8 = PTR_FUN_7105181f40;
        *(u64*)DAT_7105339000 = 0xffffffffffffffff;
        __cxa_guard_release((u64*)DAT_7105339020);
    }
    *(u64*)DAT_7105339008 = 0x10001;
    *(u64*)DAT_7105339000 = 0xffffffffffffffff;
    return (u64*)DAT_7105338ff8;
}
