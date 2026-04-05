#include "types.h"

// MEDIUM-tier FUN_* functions — batch d5-050
// Pool-d worker: misc functions 0x71001*-0x71033* ranges
// FUN_71031b97bc FUN_71031bb28c FUN_71031bdeac FUN_71031bf6fc FUN_71031c267c
// FUN_710317a3e8 FUN_71033c2258 FUN_71033cbda0 FUN_7103582b00 FUN_71036e5730
// FUN_71001683a0 FUN_710065f6b0

extern "C" {
    __attribute__((noreturn)) void abort(void);
}

// ---- External declarations ----

extern void FUN_71001352b0(u64);
extern void FUN_71000b1b90(void);
extern s64  FUN_7100130810(void *, u64);
extern void FUN_7100168f10(s64, u64);
extern void FUN_7101f44910(void *, int, u64, int, u32);
extern void FUN_7103359b40(void);
extern void FUN_7103359c4c(void);
extern void FUN_71037786c0(u64);
extern void FUN_71037790a0(u64);

// ---- 0x710317 ----

// 0x710317a3e8 — abort wrapper (72B)
void FUN_710317a3e8(void) {
    abort();
}

// ---- 0x71031b-0x71031c range — inner-object vtable dispatch at +0x18 ----
// Pattern: dereference obj_ptr to get inner object, call vtable[3] on it

// 0x71031b97bc (84B)
u64 FUN_71031b97bc(s64 *obj_ptr) {
    return (*reinterpret_cast<u64(**)()>(*(s64 *)*obj_ptr + 0x18))();
}

// 0x71031bb28c (84B)
u64 FUN_71031bb28c(s64 *obj_ptr) {
    return (*reinterpret_cast<u64(**)()>(*(s64 *)*obj_ptr + 0x18))();
}

// 0x71031bdeac (84B)
u64 FUN_71031bdeac(s64 *obj_ptr) {
    return (*reinterpret_cast<u64(**)()>(*(s64 *)*obj_ptr + 0x18))();
}

// 0x71031bf6fc (84B)
u64 FUN_71031bf6fc(s64 *obj_ptr) {
    return (*reinterpret_cast<u64(**)()>(*(s64 *)*obj_ptr + 0x18))();
}

// 0x71031c267c (84B)
u64 FUN_71031c267c(s64 *obj_ptr) {
    return (*reinterpret_cast<u64(**)()>(*(s64 *)*obj_ptr + 0x18))();
}

// ---- 0x71033 range ----

// 0x71033c2258 — call FUN_7101f44910 and return 0 (64B)
u64 FUN_71033c2258(s64 obj, void *ctx) {
    FUN_7101f44910(ctx, 0, *(u64 *)(obj + 0x50), 1, 0xffffffff);
    return 0;
}

// 0x71033cbda0 — WorkModule vtable +0x108 check, return inverted low bit (96B)
// accessor_holder+0x20 → module accessor, +0x50 = work_module
u32 FUN_71033cbda0(u64 unused, s64 accessor_holder) {
    s64 *work = *(s64 **)(*(s64 *)(accessor_holder + 0x20) + 0x50);
    u32 result = (*reinterpret_cast<u32(*)(s64 *, u32)>((*reinterpret_cast<s64 **>(work))[0x108/8]))(work, 0x20000004);
    return ~result & 1;
}

// ---- 0x71035 range ----

// 0x7103582b00 — vtable +0x240 dispatch, return result > 12 (96B)
bool FUN_7103582b00(u64 unused, u64 *obj_ptr) {
    s32 kind = (*reinterpret_cast<s32(**)()>(*(s64 *)*obj_ptr + 0x240))();
    return 0xc < kind;
}

// ---- 0x71036 range ----

// 0x71036e5730 — vtable +0x108 dispatch, deref result chain → byte at +0x128 (80B)
u8 FUN_71036e5730(s64 *obj) {
    s64 sub_obj = (*reinterpret_cast<s64(*)(s64*)>((*reinterpret_cast<s64 **>(*obj))[0x108/8]))(obj);
    return *(u8 *)(*(s64 *)(sub_obj + 8) + 0x128);
}

// ---- 0x71001 range ----

// 0x71001683a0 — allocate 0x7220 bytes and init from module instance (176B)
extern u64 *PTR_DAT_71052a50b0;
s64 FUN_71001683a0(void) {
    u64 instance_id = *PTR_DAT_71052a50b0;
    FUN_71000b1b90();
    s64 obj = FUN_7100130810((void *)0x7220, 0);
    if (obj != 0) {
        FUN_7100168f10(obj, instance_id);
    }
    return obj;
}

// ---- 0x71006 range ----

// 0x710065f6b0 — conditional bit-set in a large bit array (128B)
// Tests/sets bits in a 0x1ff8-aligned slot structure
void FUN_710065f6b0(s64 base, u16 *index_ptr, u32 flags) {
    u16 index = *index_ptr;
    if ((flags & 1) != 0) {
        if (index != 0) {
            if (0x11c < index) { abort(); }
            if ((*(u64 *)(*(s64 *)(base + 8) + ((u64)(index >> 3) & 0x1ff8) + 0x968) &
                 (1ULL << ((u64)index & 0x3f))) != 0) {
                goto do_set;
            }
        }
        return;
    }
    if (index >= 0x11d) { abort(); }
do_set:
    {
        s64 slot = *(s64 *)(base + 8) + ((u64)(index >> 3) & 0x1ff8);
        *(u64 *)(slot + 0x1b0) = *(u64 *)(slot + 0x1b0) | (1ULL << ((u64)index & 0x3f));
    }
}
