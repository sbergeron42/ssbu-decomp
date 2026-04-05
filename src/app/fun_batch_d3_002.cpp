#include "types.h"

#define HIDDEN __attribute__((visibility("hidden")))

// ---- External declarations -----------------------------------------------

extern "C" void *ext_memset(void *, int, u64) asm("memset");

namespace nn { namespace os {
    void LockMutex(void *);
    void UnlockMutex(void *);
}}

extern u64 PTR_DAT_71052a5108 HIDDEN;
extern u64 PTR_DAT_71052a5190 HIDDEN;
extern u64 PTR_DAT_71052a5198 HIDDEN;
extern u64 PTR_DAT_71052a5200 HIDDEN;

extern void FUN_71001738e0();
extern void FUN_71001758d0();
extern void FUN_7100185e60(s64, u64);
extern void FUN_710014f090();
extern u64  FUN_71000b1b90();
extern s64  FUN_7100130810(u64, u64);
extern void FUN_710013f9b0();
extern void FUN_71000bce50(s64 *, s64);
extern void FUN_71000b41f0(u64, s64 *);
extern u64  FUN_71000b2b10(s64, u64);
extern void FUN_71000b4160(s64);
extern u64  FUN_7100157cf0(s64);

// ---- Functions ---------------------------------------------------------------

// 0x710016df20 — Constructor: parent init + vtable set (48 bytes)
void FUN_710016df20(s64 *this_ptr)
{
    FUN_71001738e0();
    *this_ptr = (s64)(PTR_DAT_71052a5108 + 0x10);
}

// 0x7100170d50 — Constructor: parent init + vtable set (48 bytes)
void FUN_7100170d50(s64 *this_ptr)
{
    FUN_71001758d0();
    *this_ptr = (s64)(PTR_DAT_71052a5190 + 0x10);
}

// 0x71001712c0 — Constructor: parent init + vtable set (48 bytes)
void FUN_71001712c0(s64 *this_ptr)
{
    FUN_7100185e60((s64)this_ptr, 0);
    *this_ptr = (s64)(PTR_DAT_71052a5198 + 0x10);
}

// 0x7100172290 — Copy constructor: parent init, copy u16/u8/u64 fields (96 bytes)
s64 FUN_7100172290(s64 dst, s64 src)
{
    u64 field_28;

    FUN_710014f090();
    *(u16 *)(dst + 0x14) = *(u16 *)(src + 0x14);
    *(u16 *)(dst + 0x16) = *(u16 *)(src + 0x16);
    *(u8  *)(dst + 0x18) = *(u8  *)(src + 0x18);
    *(u8  *)(dst + 0x19) = *(u8  *)(src + 0x19);
    field_28 = *(u64 *)(src + 0x28);
    *(u64 *)(dst + 0x20) = *(u64 *)(src + 0x20);
    *(u64 *)(dst + 0x28) = field_28;
    return dst;
}

// 0x7100174570 — Factory: alloc 0x10-byte object, set vtable + clear fields (80 bytes)
void FUN_7100174570(void)
{
    u64 heap_id;
    s64 *obj;

    heap_id = FUN_71000b1b90();
    obj = (s64 *)FUN_7100130810(0x10, heap_id);
    if (obj != (s64 *)0x0) {
        *(u32 *)(obj + 1) = 0;
        *(u16 *)((s64)obj + 0xc) = 0;
        *obj = (s64)(PTR_DAT_71052a5200 + 0x10);
    }
}

// 0x7100175030 — Calls vtable[+0x180] on child at +0x18, then nulls the child ptr (48 bytes)
void FUN_7100175030(s64 this_ptr)
{
    if (*(s64 **)(this_ptr + 0x18) != (s64 *)0x0) {
        (**(void (**)(void))(**(s64 **)(this_ptr + 0x18) + 0x180))();
    }
    *(u64 *)(this_ptr + 0x18) = 0;
}

// 0x71001772e0 — Resets fields at +0x2c..+0x54, calls FUN_710013f9b0, clears flag (80 bytes)
void FUN_71001772e0(s64 this_ptr)
{
    *(u64 *)(this_ptr + 0x34) = 0;
    *(u64 *)(this_ptr + 0x3c) = 0;
    *(u16 *)(this_ptr + 0x44) = 0;
    *(u64 *)(this_ptr + 0x46) = 0;
    *(u32 *)(this_ptr + 0x4e) = 0;
    *(u16 *)(this_ptr + 0x52) = 0;
    *(u8  *)(this_ptr + 0x54) = 0;
    *(u64 *)(this_ptr + 0x2c) = 0;
    FUN_710013f9b0();
    *(u8  *)(this_ptr + 0x16) = 0;
}

// 0x710017ac20 — Copies field +0x58, builds stack obj from +0xb0, dispatches, clears, returns 1 (80 bytes)
u64 FUN_710017ac20(s64 this_ptr)
{
    u64 saved_field;
    s64 stack_obj[2];

    saved_field = *(u64 *)(this_ptr + 0x58);
    FUN_71000bce50(stack_obj, this_ptr + 0xb0);
    FUN_71000b41f0(saved_field, stack_obj);
    *(u64 *)(this_ptr + 0x58) = 0;
    return 1;
}

// 0x710017f4a0 — Searches 8 sub-objects (stride 0x40, base +0xb0) via FUN_71000b2b10, returns slot index (96 bytes)
u32 FUN_710017f4a0(s64 this_ptr, u64 key)
{
    u64 found;

    found = FUN_71000b2b10(this_ptr + 0xb0, 0);
    if ((found & 1) != 0) return 0;
    found = FUN_71000b2b10(this_ptr + 0xf0, key);
    if ((found & 1) != 0) return 1;
    found = FUN_71000b2b10(this_ptr + 0x130, key);
    if ((found & 1) != 0) return 2;
    found = FUN_71000b2b10(this_ptr + 0x170, key);
    if ((found & 1) != 0) return 3;
    found = FUN_71000b2b10(this_ptr + 0x1b0, key);
    if ((found & 1) != 0) return 4;
    found = FUN_71000b2b10(this_ptr + 0x1f0, key);
    if ((found & 1) != 0) return 5;
    found = FUN_71000b2b10(this_ptr + 0x230, key);
    if ((found & 1) != 0) return 6;
    found = FUN_71000b2b10(this_ptr + 0x270, key);
    return ((found & 1) != 0) ? 7u : 0xffffffffu;
}

// 0x7100180260 — Factory: alloc 0x70-byte object, init with FUN_7100185e60 (80 bytes)
s64 FUN_7100180260(u64 param_1)
{
    u64 heap_id;
    s64 obj;

    heap_id = FUN_71000b1b90();
    obj = FUN_7100130810(0x70, heap_id);
    if (obj != 0) {
        FUN_7100185e60(obj, param_1);
    }
    return obj;
}

// 0x7100194050 — If ready flags (+0x8d, +0x8e) both set, store ref and bump refcount (64 bytes)
u64 FUN_7100194050(s64 this_ptr, s64 ref)
{
    if (*(u8 *)(this_ptr + 0x8d) == 0) {
        return 0;
    }
    if (*(u8 *)(this_ptr + 0x8e) != 0) {
        if (ref != 0) {
            *(s64 *)(this_ptr + 0x58) = ref;
            FUN_71000b4160(ref);
        }
        *(u8 *)(this_ptr + 0x8e) = 0;
        return 1;
    }
    return 0;
}

// 0x710019c3b0 — Lock mutex at +0x138, zero 0x100 bytes at +0x160, unlock (48 bytes)
void FUN_710019c3b0(s64 this_ptr)
{
    nn::os::LockMutex((void *)(this_ptr + 0x138));
    ext_memset((void *)(this_ptr + 0x160), 0, 0x100);
    nn::os::UnlockMutex((void *)(this_ptr + 0x138));
}

// 0x7100194e60 — Vtable check at +0xc8, then flag/field validation (64 bytes)
bool FUN_7100194e60(s64 *this_ptr, s64 param_2)
{
    u64 result;

    result = (*(u64 (**)())(*(s64 *)this_ptr + 0xc8))();
    if ((result & 1) != 0) {
        return true;
    }
    if ((*(u8 *)(param_2 + 0x31) & 3) == 1) {
        result = FUN_7100157cf0(param_2);
        if (result >> 0x20 != 0) {
            return false;
        }
        return (s32)this_ptr[0x22] == 0;
    }
    return false;
}
