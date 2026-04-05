#include "types.h"

#define HIDDEN __attribute__((visibility("hidden")))

// ---- External declarations -----------------------------------------------

extern u64 PTR_DAT_71052a50b0 HIDDEN;
extern u64 PTR_DAT_71052a4610 HIDDEN;
extern u64 PTR_DAT_71052a4630 HIDDEN;
extern u64 PTR_DAT_71052a46c8 HIDDEN;
extern u64 PTR_DAT_71052a4718 HIDDEN;
extern u64 PTR_DAT_71052a4880 HIDDEN;
extern u64 PTR_DAT_71052a4a00 HIDDEN;
extern u64 PTR_DAT_71052a4a88 HIDDEN;
extern u64 PTR_DAT_71052a4a90 HIDDEN;
extern u64 PTR_DAT_71052a4a98 HIDDEN;
extern u8  PTR_DAT_71052a4c08[] HIDDEN;
extern u8 *PTR_DAT_71052a4c10 HIDDEN;
extern u8  PTR_DAT_71052a4c28[] HIDDEN;

extern u64  FUN_71000b1b90();
extern s64  FUN_7100130810(u64, u64);
extern void FUN_7100179c70(s64, u64);
extern void FUN_710017c3d0(s64, u64);
extern void FUN_710017b8d0(s64, u64);
extern void FUN_710017a6e0(s64, u64);
extern void FUN_710017b010(s64, u64);
extern void FUN_7100179d50(s64, u64);
extern void FUN_710017a610(s64, u64);
extern void FUN_71000b4260();
extern void FUN_710013ce70();
extern void FUN_710013d130();
extern void FUN_7100151120();
extern void FUN_710013e400();
extern void FUN_71000c4cf0(u64, u64);
extern void FUN_7100118020(s64, u16);
extern void FUN_7100186580();
extern void FUN_710015fd60(s64 *);
extern void FUN_710015ffc0(s64);
extern void FUN_7100141e80();
extern void FUN_710018f180();
extern void FUN_710013dcf0();
extern "C" s32 __cxa_guard_acquire(u8 *);
extern "C" void __cxa_guard_release(u8 *);

// ---- Functions ---------------------------------------------------------------

// 0x710013ce20 — Clears shared-ptr-like field at +0x58, calling release if refcount == 1 (96 bytes)
void FUN_710013ce20(s64 this_ptr)
{
    if (*(s32 **)(this_ptr + 0x58) != (s32 *)0x0) {
        if (**(s32 **)(this_ptr + 0x58) == 1) {
            FUN_71000b4260();
        }
        *(u64 *)(this_ptr + 0x58) = 0;
    }
}

// 0x7100179730 — Factory: alloc 0x168-byte object, init with FUN_710017c3d0 (112 bytes)
s64 FUN_7100179730(void)
{
    u64 heap_id;
    s64 obj;
    u64 alloc_ctx;

    alloc_ctx = *(u64 *)PTR_DAT_71052a50b0;
    heap_id = FUN_71000b1b90();
    obj = FUN_7100130810(0x168, heap_id);
    if (obj != 0) {
        FUN_710017c3d0(obj, alloc_ctx);
    }
    return obj;
}

// 0x71001797c0 — Factory: alloc 0x98-byte object, init with FUN_710017b8d0 (112 bytes)
s64 FUN_71001797c0(void)
{
    u64 heap_id;
    s64 obj;
    u64 alloc_ctx;

    alloc_ctx = *(u64 *)PTR_DAT_71052a50b0;
    heap_id = FUN_71000b1b90();
    obj = FUN_7100130810(0x98, heap_id);
    if (obj != 0) {
        FUN_710017b8d0(obj, alloc_ctx);
    }
    return obj;
}

// 0x7100179850 — Factory: alloc 0xc0-byte object, init with FUN_710017a6e0 (112 bytes)
s64 FUN_7100179850(void)
{
    u64 heap_id;
    s64 obj;
    u64 alloc_ctx;

    alloc_ctx = *(u64 *)PTR_DAT_71052a50b0;
    heap_id = FUN_71000b1b90();
    obj = FUN_7100130810(0xc0, heap_id);
    if (obj != 0) {
        FUN_710017a6e0(obj, alloc_ctx);
    }
    return obj;
}

// 0x7100179900 — Factory: alloc 0xa0-byte object, init with FUN_710017b010 (112 bytes)
s64 FUN_7100179900(void)
{
    u64 heap_id;
    s64 obj;
    u64 alloc_ctx;

    alloc_ctx = *(u64 *)PTR_DAT_71052a50b0;
    heap_id = FUN_71000b1b90();
    obj = FUN_7100130810(0xa0, heap_id);
    if (obj != 0) {
        FUN_710017b010(obj, alloc_ctx);
    }
    return obj;
}

// 0x7100179990 — Factory: alloc 0x148-byte object, init with FUN_7100179d50 (112 bytes)
s64 FUN_7100179990(void)
{
    u64 heap_id;
    s64 obj;
    u64 alloc_ctx;

    alloc_ctx = *(u64 *)PTR_DAT_71052a50b0;
    heap_id = FUN_71000b1b90();
    obj = FUN_7100130810(0x148, heap_id);
    if (obj != 0) {
        FUN_7100179d50(obj, alloc_ctx);
    }
    return obj;
}

// 0x7100179a20 — Factory: alloc 0xb0-byte object, init with FUN_710017a610 (112 bytes)
s64 FUN_7100179a20(void)
{
    u64 heap_id;
    s64 obj;
    u64 alloc_ctx;

    alloc_ctx = *(u64 *)PTR_DAT_71052a50b0;
    heap_id = FUN_71000b1b90();
    obj = FUN_7100130810(0xb0, heap_id);
    if (obj != 0) {
        FUN_710017a610(obj, alloc_ctx);
    }
    return obj;
}

// 0x710010ab30 — Constructor: parent init, set vtable, clear field (80 bytes)
void FUN_710010ab30(s64 *this_ptr)
{
    FUN_710013ce70();
    *this_ptr = (s64)(PTR_DAT_71052a4610 + 0x10);
    this_ptr[0x13] = 0;
}

// 0x710010b0b0 — Constructor: parent init, set vtable, clear multiple fields (128 bytes)
void FUN_710010b0b0(s64 *this_ptr)
{
    FUN_710013d130();
    this_ptr[0x12] = 0;
    *this_ptr = (s64)(PTR_DAT_71052a4630 + 0x10);
    *(u32 *)(this_ptr + 0x13) = 0;
    this_ptr[0x14] = 0;
    this_ptr[0x15] = 0;
    *(u8 *)(this_ptr + 0x16) = 1;
}

// 0x710010d4f0 — Constructor: parent init, set vtable, clear fields (112 bytes)
void FUN_710010d4f0(s64 *this_ptr)
{
    FUN_7100151120();
    *this_ptr = (s64)(PTR_DAT_71052a46c8 + 0x10);
    this_ptr[0x13] = 0;
    *(u32 *)(this_ptr + 0x58) = 0;
    *(u8 *)((s64)this_ptr + 0x2c4) = 0;
}

// 0x710010ead0 — Constructor: parent init, set vtable, clear field (80 bytes)
void FUN_710010ead0(s64 *this_ptr)
{
    FUN_710013e400();
    *this_ptr = (s64)(PTR_DAT_71052a4718 + 0x10);
    this_ptr[0x13] = 0;
}

// 0x71001125a0 — Clears flag at +0x1f9, calls helper with saved ptr from +0x200, returns 1 (48 bytes)
u64 FUN_71001125a0(s64 this_ptr, u64 param_2)
{
    *(u8 *)(this_ptr + 0x1f9) = 0;
    FUN_71000c4cf0(param_2, *(u64 *)(this_ptr + 0x200));
    return 1;
}

// 0x7100117e90 — Factory: alloc 0x18-byte object, normalize port (0→1), init with FUN_7100118020 (128 bytes)
s64 FUN_7100117e90(u64 param_1, u16 port)
{
    u16 normalized_port;
    u64 heap_id;
    s64 obj;

    heap_id = FUN_71000b1b90();
    obj = FUN_7100130810(0x18, heap_id);
    if (obj != 0) {
        normalized_port = port & 0xff;
        if (port == 0) {
            normalized_port = 1;
        }
        FUN_7100118020(obj, normalized_port);
    }
    return obj;
}

// 0x710011c2f0 — Constructor: parent init, vtable, sub-struct init, set fields (112 bytes)
void FUN_710011c2f0(s64 *this_ptr)
{
    FUN_7100186580();
    *this_ptr = (s64)(PTR_DAT_71052a4880 + 0x10);
    FUN_710015fd60(this_ptr + 0x10);
    *(u64 *)((s64)this_ptr + 0x4c) = 0x40000000;
    *(u32 *)((s64)this_ptr + 0x54) = 0;
}

// 0x710011f880 — Constructor: parent init, set vtable (48 bytes)
void FUN_710011f880(s64 *this_ptr)
{
    FUN_710013dcf0();
    *this_ptr = (s64)(PTR_DAT_71052a4a00 + 0x10);
}

// 0x7100121500 — Constructor: parent init, vtable, clear fields (96 bytes)
void FUN_7100121500(s64 *this_ptr)
{
    FUN_7100141e80();
    *this_ptr = (s64)(PTR_DAT_71052a4a88 + 0x10);
    this_ptr[0x55] = 0;
    *(u32 *)(this_ptr + 0x56) = 0;
}

// 0x7100121d40 — Constructor: parent init, set vtable (48 bytes)
void FUN_7100121d40(s64 *this_ptr)
{
    FUN_710018f180();
    *this_ptr = (s64)(PTR_DAT_71052a4a90 + 0x10);
}

// 0x7100122220 — Constructor: parent init, vtable, clear fields (96 bytes)
void FUN_7100122220(s64 *this_ptr)
{
    FUN_7100151120();
    *this_ptr = (s64)(PTR_DAT_71052a4a98 + 0x10);
    this_ptr[0x13] = 0;
    *(u8 *)(this_ptr + 0x14) = 0;
}

// 0x710012d350 — Delegates to FUN_710015ffc0 on sub-object at +0x1e0 (32 bytes)
void FUN_710012d350(s64 this_ptr)
{
    FUN_710015ffc0(this_ptr + 0x1e0);
}

// 0x7100133510 — Singleton getter: guard-acquire, set vtable ptr once, return (80 bytes)
u8 *FUN_7100133510(void)
{
    s32 acquired;

    if (((PTR_DAT_71052a4c08[0] & 1) == 0) &&
        (acquired = __cxa_guard_acquire(PTR_DAT_71052a4c08), acquired != 0)) {
        PTR_DAT_71052a4c10 = PTR_DAT_71052a4c28 + 0x10;
        __cxa_guard_release(PTR_DAT_71052a4c08);
        return PTR_DAT_71052a4c10;
    }
    return PTR_DAT_71052a4c10;
}
