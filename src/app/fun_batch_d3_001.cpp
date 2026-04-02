#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7100 address range, batch d3-001
// Pool-d worker: auto-generated from Ghidra decompilation

// ---- External declarations -----------------------------------------------

// External data — hidden visibility for direct ADRP access (no GOT indirection)
#define HIDDEN __attribute__((visibility("hidden")))
extern u64 PTR_DAT_71052a50b0 HIDDEN;   // allocator factory context ptr
extern u8  PTR_DAT_71052a4610[] HIDDEN;
extern u8  PTR_DAT_71052a4630[] HIDDEN;
extern u8  PTR_DAT_71052a46c8[] HIDDEN;
extern u8  PTR_DAT_71052a4718[] HIDDEN;
extern u8  PTR_DAT_71052a4880[] HIDDEN;
extern u8  PTR_DAT_71052a4a00[] HIDDEN;
extern u8  PTR_DAT_71052a4a88[] HIDDEN;
extern u8  PTR_DAT_71052a4a90[] HIDDEN;
extern u8  PTR_DAT_71052a4a98[] HIDDEN;
extern u8  PTR_DAT_71052a4c08[] HIDDEN;
extern u8 *PTR_DAT_71052a4c10 HIDDEN;
extern u8  PTR_DAT_71052a4c28[] HIDDEN;

// External FUN_* forward declarations
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

// 0x710013ce20 — clear shared_ptr-like field at +0x58 if refcount is 1 (96 bytes)
void FUN_710013ce20(s64 param_1)
{
    if (*(s32 **)(param_1 + 0x58) != (s32 *)0x0) {
        if (**(s32 **)(param_1 + 0x58) == 1) {
            FUN_71000b4260();
        }
        *(u64 *)(param_1 + 0x58) = 0;
    }
}

// 0x7100179730 — factory: alloc 0x168-byte object, init with FUN_710017c3d0 (112 bytes)
s64 FUN_7100179730(void)
{
    u64 uVar1;
    s64 lVar2;
    u64 uVar3;

    uVar3 = *(u64 *)PTR_DAT_71052a50b0;
    uVar1 = FUN_71000b1b90();
    lVar2 = FUN_7100130810(0x168, uVar1);
    if (lVar2 != 0) {
        FUN_710017c3d0(lVar2, uVar3);
    }
    return lVar2;
}

// 0x71001797c0 — factory: alloc 0x98-byte object, init with FUN_710017b8d0 (112 bytes)
s64 FUN_71001797c0(void)
{
    u64 uVar1;
    s64 lVar2;
    u64 uVar3;

    uVar3 = *(u64 *)PTR_DAT_71052a50b0;
    uVar1 = FUN_71000b1b90();
    lVar2 = FUN_7100130810(0x98, uVar1);
    if (lVar2 != 0) {
        FUN_710017b8d0(lVar2, uVar3);
    }
    return lVar2;
}

// 0x7100179850 — factory: alloc 0xc0-byte object, init with FUN_710017a6e0 (112 bytes)
s64 FUN_7100179850(void)
{
    u64 uVar1;
    s64 lVar2;
    u64 uVar3;

    uVar3 = *(u64 *)PTR_DAT_71052a50b0;
    uVar1 = FUN_71000b1b90();
    lVar2 = FUN_7100130810(0xc0, uVar1);
    if (lVar2 != 0) {
        FUN_710017a6e0(lVar2, uVar3);
    }
    return lVar2;
}

// 0x7100179900 — factory: alloc 0xa0-byte object, init with FUN_710017b010 (112 bytes)
s64 FUN_7100179900(void)
{
    u64 uVar1;
    s64 lVar2;
    u64 uVar3;

    uVar3 = *(u64 *)PTR_DAT_71052a50b0;
    uVar1 = FUN_71000b1b90();
    lVar2 = FUN_7100130810(0xa0, uVar1);
    if (lVar2 != 0) {
        FUN_710017b010(lVar2, uVar3);
    }
    return lVar2;
}

// 0x7100179990 — factory: alloc 0x148-byte object, init with FUN_7100179d50 (112 bytes)
s64 FUN_7100179990(void)
{
    u64 uVar1;
    s64 lVar2;
    u64 uVar3;

    uVar3 = *(u64 *)PTR_DAT_71052a50b0;
    uVar1 = FUN_71000b1b90();
    lVar2 = FUN_7100130810(0x148, uVar1);
    if (lVar2 != 0) {
        FUN_7100179d50(lVar2, uVar3);
    }
    return lVar2;
}

// 0x7100179a20 — factory: alloc 0xb0-byte object, init with FUN_710017a610 (112 bytes)
s64 FUN_7100179a20(void)
{
    u64 uVar1;
    s64 lVar2;
    u64 uVar3;

    uVar3 = *(u64 *)PTR_DAT_71052a50b0;
    uVar1 = FUN_71000b1b90();
    lVar2 = FUN_7100130810(0xb0, uVar1);
    if (lVar2 != 0) {
        FUN_710017a610(lVar2, uVar3);
    }
    return lVar2;
}

// 0x710010ab30 — ctor: call parent init, set vtable ptr (80 bytes)
void FUN_710010ab30(s64 *param_1)
{
    FUN_710013ce70();
    param_1[0x13] = 0;
    *param_1 = (s64)(PTR_DAT_71052a4610 + 0x10);
}

// 0x710010b0b0 — ctor: call parent init, set vtable ptr + clear fields (128 bytes)
void FUN_710010b0b0(s64 *param_1)
{
    FUN_710013d130();
    param_1[0x12] = 0;
    *(u32 *)(param_1 + 0x13) = 0;
    param_1[0x14] = 0;
    param_1[0x15] = 0;
    *param_1 = (s64)(PTR_DAT_71052a4630 + 0x10);
    *(u8 *)(param_1 + 0x16) = 1;
}

// 0x710010d4f0 — ctor: call parent init, set vtable ptr + clear fields (112 bytes)
void FUN_710010d4f0(s64 *param_1)
{
    FUN_7100151120();
    param_1[0x13] = 0;
    *(u32 *)(param_1 + 0x58) = 0;
    *(u8 *)((s64)param_1 + 0x2c4) = 0;
    *param_1 = (s64)(PTR_DAT_71052a46c8 + 0x10);
}

// 0x710010ead0 — ctor: call parent init, set vtable ptr (80 bytes)
void FUN_710010ead0(s64 *param_1)
{
    FUN_710013e400();
    param_1[0x13] = 0;
    *param_1 = (s64)(PTR_DAT_71052a4718 + 0x10);
}

// 0x71001125a0 — clear flag field, call FUN with saved ptr (48 bytes)
u64 FUN_71001125a0(s64 param_1, u64 param_2)
{
    *(u8 *)(param_1 + 0x1f9) = 0;
    FUN_71000c4cf0(param_2, *(u64 *)(param_1 + 0x200));
    return 1;
}

// 0x7100117e90 — factory: alloc 0x18-byte, normalize port, init with FUN_7100118020 (128 bytes)
s64 FUN_7100117e90(u64 param_1, u16 param_2)
{
    u16 uVar1;
    u64 uVar2;
    s64 lVar3;

    uVar2 = FUN_71000b1b90();
    lVar3 = FUN_7100130810(0x18, uVar2);
    if (lVar3 != 0) {
        uVar1 = param_2 & 0xff;
        if (param_2 == 0) {
            uVar1 = 1;
        }
        FUN_7100118020(lVar3, uVar1);
    }
    return lVar3;
}

// 0x710011c2f0 — ctor: parent init, set vtable, init sub-struct, set fields (112 bytes)
void FUN_710011c2f0(s64 *param_1)
{
    FUN_7100186580();
    *param_1 = (s64)(PTR_DAT_71052a4880 + 0x10);
    FUN_710015fd60(param_1 + 0x10);
    *(u64 *)((s64)param_1 + 0x4c) = 0x40000000;
    *(u32 *)((s64)param_1 + 0x54) = 0;
}

// 0x710011f880 — ctor: call parent init, set vtable ptr (48 bytes)
void FUN_710011f880(s64 *param_1)
{
    FUN_710013dcf0();
    *param_1 = (s64)(PTR_DAT_71052a4a00 + 0x10);
}

// 0x7100121500 — ctor: call parent init, set vtable ptr + clear fields (96 bytes)
void FUN_7100121500(s64 *param_1)
{
    FUN_7100141e80();
    param_1[0x55] = 0;
    *(u32 *)(param_1 + 0x56) = 0;
    *param_1 = (s64)(PTR_DAT_71052a4a88 + 0x10);
}

// 0x7100121d40 — ctor: call parent init, set vtable ptr (48 bytes)
void FUN_7100121d40(s64 *param_1)
{
    FUN_710018f180();
    *param_1 = (s64)(PTR_DAT_71052a4a90 + 0x10);
}

// 0x7100122220 — ctor: call parent init, set vtable ptr + clear fields (96 bytes)
void FUN_7100122220(s64 *param_1)
{
    FUN_7100151120();
    param_1[0x13] = 0;
    *(u8 *)(param_1 + 0x14) = 0;
    *param_1 = (s64)(PTR_DAT_71052a4a98 + 0x10);
}

// 0x710012d350 — delegate to sub-object at +0x1e0 (32 bytes)
void FUN_710012d350(s64 param_1)
{
    FUN_710015ffc0(param_1 + 0x1e0);
}

// 0x7100133510 — singleton init guard: set vtable ptr once (80 bytes)
u8 *FUN_7100133510(void)
{
    s32 iVar1;

    if (((PTR_DAT_71052a4c08[0] & 1) == 0) &&
        (iVar1 = __cxa_guard_acquire(PTR_DAT_71052a4c08), iVar1 != 0)) {
        PTR_DAT_71052a4c10 = PTR_DAT_71052a4c28 + 0x10;
        __cxa_guard_release(PTR_DAT_71052a4c08);
        return PTR_DAT_71052a4c10;
    }
    return PTR_DAT_71052a4c10;
}
