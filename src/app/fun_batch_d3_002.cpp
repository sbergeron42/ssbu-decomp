#include "types.h"

#define HIDDEN __attribute__((visibility("hidden")))

// MEDIUM-tier FUN_* functions — 0x7100 address range, batch d3-002
// Pool-d worker: auto-generated from Ghidra decompilation

// ---- External declarations -----------------------------------------------

// Declare with asm label to prevent builtin inlining
extern "C" void *ext_memset(void *, int, u64) asm("memset");

// nn forward declarations
namespace nn { namespace os {
    void LockMutex(void *);
    void UnlockMutex(void *);
}}

// External data
extern u64 PTR_DAT_71052a5108 HIDDEN;
extern u64 PTR_DAT_71052a5190 HIDDEN;
extern u64 PTR_DAT_71052a5198 HIDDEN;
extern u64 PTR_DAT_71052a5200 HIDDEN;

// External FUN_* forward declarations
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

// 0x710016df20 — ctor: call parent init, set vtable ptr (48 bytes)
void FUN_710016df20(s64 *param_1)
{
    FUN_71001738e0();
    *param_1 = (s64)(PTR_DAT_71052a5108 + 0x10);
}

// 0x7100170d50 — ctor: call parent init, set vtable ptr (48 bytes)
void FUN_7100170d50(s64 *param_1)
{
    FUN_71001758d0();
    *param_1 = (s64)(PTR_DAT_71052a5190 + 0x10);
}

// 0x71001712c0 — ctor: call parent init, set vtable ptr (48 bytes)
void FUN_71001712c0(s64 *param_1)
{
    FUN_7100185e60((s64)param_1, 0);
    *param_1 = (s64)(PTR_DAT_71052a5198 + 0x10);
}

// 0x7100172290 — copy ctor: parent init, copy u16/u8/u64 fields (96 bytes)
s64 FUN_7100172290(s64 param_1, s64 param_2)
{
    u64 uVar1;

    FUN_710014f090();
    *(u16 *)(param_1 + 0x14) = *(u16 *)(param_2 + 0x14);
    *(u16 *)(param_1 + 0x16) = *(u16 *)(param_2 + 0x16);
    *(u8  *)(param_1 + 0x18) = *(u8  *)(param_2 + 0x18);
    *(u8  *)(param_1 + 0x19) = *(u8  *)(param_2 + 0x19);
    uVar1 = *(u64 *)(param_2 + 0x28);
    *(u64 *)(param_1 + 0x20) = *(u64 *)(param_2 + 0x20);
    *(u64 *)(param_1 + 0x28) = uVar1;
    return param_1;
}

// 0x7100174570 — factory: alloc 0x10-byte object, set vtable + clear fields (80 bytes)
void FUN_7100174570(void)
{
    u64 uVar2;
    s64 *plVar3;

    uVar2 = FUN_71000b1b90();
    plVar3 = (s64 *)FUN_7100130810(0x10, uVar2);
    if (plVar3 != (s64 *)0x0) {
        *(u32 *)(plVar3 + 1) = 0;
        *(u16 *)((s64)plVar3 + 0xc) = 0;
        *plVar3 = (s64)(PTR_DAT_71052a5200 + 0x10);
    }
}

// 0x7100175030 — vtable dispatch at +0x180, then clear ptr field (48 bytes)
void FUN_7100175030(s64 param_1)
{
    if (*(s64 **)(param_1 + 0x18) != (s64 *)0x0) {
        (**(void (**)(void))(**(s64 **)(param_1 + 0x18) + 0x180))();
    }
    *(u64 *)(param_1 + 0x18) = 0;
}

// 0x71001772e0 — clear multiple fields, call FUN_710013f9b0 (80 bytes)
void FUN_71001772e0(s64 param_1)
{
    *(u64 *)(param_1 + 0x34) = 0;
    *(u64 *)(param_1 + 0x3c) = 0;
    *(u16 *)(param_1 + 0x44) = 0;
    *(u64 *)(param_1 + 0x46) = 0;
    *(u32 *)(param_1 + 0x4e) = 0;
    *(u16 *)(param_1 + 0x52) = 0;
    *(u8  *)(param_1 + 0x54) = 0;
    *(u64 *)(param_1 + 0x2c) = 0;
    FUN_710013f9b0();
    *(u8  *)(param_1 + 0x16) = 0;
}

// 0x710017ac20 — copy field to stack, call pair of helpers, clear ptr, return 1 (80 bytes)
u64 FUN_710017ac20(s64 param_1)
{
    u64 uVar1;
    s64 auStack_30[2];

    uVar1 = *(u64 *)(param_1 + 0x58);
    FUN_71000bce50(auStack_30, param_1 + 0xb0);
    FUN_71000b41f0(uVar1, auStack_30);
    *(u64 *)(param_1 + 0x58) = 0;
    return 1;
}

// 0x710017f4a0 — indexed search: check FUN_71000b2b10 on 8 sub-objects, return slot (96 bytes)
u32 FUN_710017f4a0(s64 param_1, u64 param_2)
{
    u64 uVar1;

    uVar1 = FUN_71000b2b10(param_1 + 0xb0, 0);
    if ((uVar1 & 1) != 0) return 0;
    uVar1 = FUN_71000b2b10(param_1 + 0xf0, param_2);
    if ((uVar1 & 1) != 0) return 1;
    uVar1 = FUN_71000b2b10(param_1 + 0x130, param_2);
    if ((uVar1 & 1) != 0) return 2;
    uVar1 = FUN_71000b2b10(param_1 + 0x170, param_2);
    if ((uVar1 & 1) != 0) return 3;
    uVar1 = FUN_71000b2b10(param_1 + 0x1b0, param_2);
    if ((uVar1 & 1) != 0) return 4;
    uVar1 = FUN_71000b2b10(param_1 + 0x1f0, param_2);
    if ((uVar1 & 1) != 0) return 5;
    uVar1 = FUN_71000b2b10(param_1 + 0x230, param_2);
    if ((uVar1 & 1) != 0) return 6;
    uVar1 = FUN_71000b2b10(param_1 + 0x270, param_2);
    return ((uVar1 & 1) != 0) ? 7u : 0xffffffffu;
}

// 0x7100180260 — factory: alloc 0x70-byte object, init with FUN_7100185e60 (80 bytes)
s64 FUN_7100180260(u64 param_1)
{
    u64 uVar1;
    s64 lVar2;

    uVar1 = FUN_71000b1b90();
    lVar2 = FUN_7100130810(0x70, uVar1);
    if (lVar2 != 0) {
        FUN_7100185e60(lVar2, param_1);
    }
    return lVar2;
}

// 0x7100194050 — check flag at +0x8d/+0x8e, set ptr + refcount if both set (64 bytes)
u64 FUN_7100194050(s64 param_1, s64 param_2)
{
    if (*(u8 *)(param_1 + 0x8d) == 0) {
        return 0;
    }
    if (*(u8 *)(param_1 + 0x8e) != 0) {
        if (param_2 != 0) {
            *(s64 *)(param_1 + 0x58) = param_2;
            FUN_71000b4160(param_2);
        }
        *(u8 *)(param_1 + 0x8e) = 0;
        return 1;
    }
    return 0;
}

// 0x710019c3b0 — mutex lock, zero 0x100-byte region at +0x160, mutex unlock (48 bytes)
void FUN_710019c3b0(s64 param_1)
{
    nn::os::LockMutex((void *)(param_1 + 0x138));
    ext_memset((void *)(param_1 + 0x160), 0, 0x100);
    nn::os::UnlockMutex((void *)(param_1 + 0x138));
}

// 0x7100194e60 — vtable dispatch at +0xc8, check flags and field +0x22 (64 bytes)
bool FUN_7100194e60(s64 *param_1, s64 param_2)
{
    u64 uVar1;

    uVar1 = (*(u64 (**)())(*(s64 *)param_1 + 0xc8))();
    if ((uVar1 & 1) != 0) {
        return true;
    }
    if ((*(u8 *)(param_2 + 0x31) & 3) == 1) {
        uVar1 = FUN_7100157cf0(param_2);
        if (uVar1 >> 0x20 != 0) {
            return false;
        }
        return (s32)param_1[0x22] == 0;
    }
    return false;
}
