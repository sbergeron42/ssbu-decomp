#include "types.h"

// MEDIUM-tier FUN_* functions -- 0x7103 address range, batch d-002
// Pool-d worker: auto-generated from Ghidra decompilation

// ---- External declarations -----------------------------------------------

extern "C" {
    int  __cxa_guard_acquire(u64*);
    void __cxa_guard_release(u64*);
    void* memcpy(void*, const void*, u64);
}

extern void FUN_7103778ed0(u64);
extern void FUN_71037b0cd0(u64);
extern void FUN_7103945810(u64);
extern void FUN_710395cc80(u64, u32, u32);
extern void FUN_7103540560(u64);
extern void FUN_7103818550(u32, u64, u8, u8, u32);
extern void FUN_710392e590(void*);
extern u16  FUN_710003e210();

namespace nu {
    extern void VirtualFreeHook(void*);
}

namespace nn { namespace fs {
    typedef u64 FileHandle;
    extern s32  ReadFile(FileHandle handle, s64 offset, void* buf, u64 size);
    extern void GetFileSize(s64* out, FileHandle handle);
}}

// External data
extern u8 DAT_00007d80[];
extern u8 DAT_7105331f20[];
extern u8 PTR_VirtualFreeHook_71052a7a70[];
extern u8 DAT_710593aac8[];
extern u8 DAT_710593aad0[];
extern u8 DAT_710593aad8[];
extern u8 DAT_710593aae0[];

// ---- Functions ---------------------------------------------------------------

// 0x710335d314 -- vtable dispatch at offset 0x280 (104 bytes)
u64 FUN_710335d314(s64 *param_1)
{
    (*(void (*)(s64 *))(*(s64 *)(*param_1 + 0x280)))(param_1);
    return 0;
}

// 0x7103366688 -- vtable dispatch at offset 8 (104 bytes)
u64 FUN_7103366688(s64 *param_1)
{
    (*(void (*)(s64 *))(*(s64 *)(*param_1 + 8)))(param_1);
    return 0;
}

// 0x7103715068 -- indirect call through code pointer (104 bytes)
u64 FUN_7103715068(void (*param_1)())
{
    u32 uVar1 = ((u32 (*)())param_1)();
    return uVar1;
}

// 0x7103359be0 -- wrapper: call FUN_7103778ed0 (108 bytes)
u64 FUN_7103359be0(u64 param_1)
{
    FUN_7103778ed0(param_1);
    return 0;
}

// 0x7103579b10 -- vtable call at 0x68 with byte param (112 bytes)
void FUN_7103579b10(s64 param_1, u8 param_2)
{
    s64 lVar2 = *(s64 *)(param_1 + 8);
    s64 *plVar1 = *(s64 **)(lVar2 + 0xb0);
    if (plVar1 != nullptr) {
        (*(void (*)(s64 *, u32))(*plVar1 + 0x68))(plVar1, (u32)(param_2 & 1));
    }
    *(u8 *)(lVar2 + 0x62) = param_2 & 1;
}

// 0x7103444090 -- vtable call at 0x108 with flag, return negated (112 bytes)
u64 FUN_7103444090(u64 param_1, s64 param_2)
{
    s64 *plVar2 = *(s64 **)(*(s64 *)(param_2 + 0x20) + 0x50);
    u32 uVar1 = (*(u32 (*)(s64 *, u32))(*(s64 *)(*plVar2 + 0x108)))(plVar2, 0x20000006);
    return ~uVar1 & 1;
}

// 0x71037bd590 -- wrapper: call FUN_71037b0cd0 (112 bytes)
void FUN_71037bd590(u64 param_1)
{
    FUN_71037b0cd0(param_1);
}

// 0x7103938a80 -- table lookup by param, call FUN_7103945810 (112 bytes)
void FUN_7103938a80(s64 param_1)
{
    FUN_7103945810(*(u64 *)(DAT_00007d80 + param_1));
}

// 0x710395d8d0 -- wrapper: call FUN_710395cc80(p, 0, 1) (112 bytes)
void FUN_710395d8d0(u64 param_1)
{
    FUN_710395cc80(param_1, 0, 1);
}

// 0x7103979cbc -- field call at param1+0x38 with param1+0x60 (120 bytes)
u64 FUN_7103979cbc(s64 param_1)
{
    (*(void (*)(s64))(*(s64 *)(param_1 + 0x38)))(param_1 + 0x60);
    return 0;
}

// 0x71034d9c70 -- vtable call returning bool: iVar != 2 (128 bytes)
u8 FUN_71034d9c70(u64 param_1, s64 param_2)
{
    s32 iVar1 = (*(s32 (*)())(*(s64 *)(*(s64 *)(*(s64 *)(*(s64 *)(param_2 + 0x20) + 0x40)) + 0x110)))();
    return (u8)(iVar1 != 2);
}

// 0x7103999620 -- memcpy 0x1b4 bytes from *param_4 to param_2 (128 bytes)
u32 FUN_7103999620(u64 param_1, void *param_2, u64 param_3, u64 *param_4)
{
    memcpy(param_2, (void *)*param_4, 0x1b4);
    return 0;
}

// 0x7103655f40 -- conditional free of two pointers with VirtualFreeHook (128 bytes)
void FUN_7103655f40(u8 *param_1)
{
    void *pvVar1;

    if ((param_1[0x18] & 1) != 0) {
        pvVar1 = *(void **)(param_1 + 0x28);
        if (*(u8 **)PTR_VirtualFreeHook_71052a7a70 != nullptr) {
            nu::VirtualFreeHook(pvVar1);
        }
        FUN_710392e590(pvVar1);
    }
    if ((*param_1 & 1) == 0) {
        return;
    }
    pvVar1 = *(void **)(param_1 + 0x10);
    if (*(u8 **)PTR_VirtualFreeHook_71052a7a70 != nullptr) {
        nu::VirtualFreeHook(pvVar1);
    }
    FUN_710392e590(pvVar1);
}

// 0x71037c6940 -- nn::fs::ReadFile wrapper, returns bytes read or 0 (128 bytes)
u64 FUN_71037c6940(s64 param_1, void *param_2, u64 param_3)
{
    s64 local_28;
    s32 iVar2;
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif

    if ((*(s32 *)(param_1 + 0x14) == 0) ||
        (iVar2 = nn::fs::ReadFile((nn::fs::FileHandle)*(u64 *)(param_1 + 0x18),
                                  *(s64 *)(param_1 + 0x20), param_2, param_3), iVar2 != 0)) {
        param_3 = 0;
    } else if ((*(s32 *)(param_1 + 0x14) != 0) &&
               (*(s64 *)(param_1 + 0x20) = *(s64 *)(param_1 + 0x20) + (s64)param_3,
                -1 < *(s64 *)(param_1 + 0x20))) {
        local_28 = 0;
        nn::fs::GetFileSize(&local_28, (nn::fs::FileHandle)*(u64 *)(param_1 + 0x18));
    }
    return param_3;
}

// 0x7103979c34 -- field call at param1+0x30 with param1+0x60 (136 bytes)
u64 FUN_7103979c34(s64 param_1)
{
    (*(void (*)(s64))(*(s64 *)(param_1 + 0x30)))(param_1 + 0x60);
    return 0;
}

// 0x71037f1cc0 -- multi-case lookup table switch (144 bytes)
s32 FUN_71037f1cc0(u32 param_1, s32 param_2)
{
    s32 iVar1 = 5;
    switch (param_1) {
    case 1: case 2: case 3: case 4:
    case 5: case 6: case 7: case 8:
        if (2 < (u32)(param_2 - 0xf)) {
            return 0x18;
        }
        iVar1 = 0x11 - param_2;
        // fall through
    case 9: case 10: case 0xb: case 0xc:
    case 0xd: case 0xe: case 0xf: case 0x10:
        return iVar1;
    case 0x11: case 0x12: case 0x13: case 0x14:
    case 0x15: case 0x16: case 0x17: case 0x18:
        if (param_2 == 0x11) {
            return 0xf;
        }
        break;
    case 0x21: case 0x22: case 0x23: case 0x24:
    case 0x25: case 0x26: case 0x27: case 0x28:
        return 0xb;
    case 0x29: case 0x2a: case 0x2b: case 0x2c:
    case 0x2d: case 0x2e: case 0x2f: case 0x30:
        return 0x11;
    case 0x31: case 0x32: case 0x33: case 0x34:
    case 0x35: case 0x36: case 0x37: case 0x38:
        return 8;
    case 0x41: case 0x42: case 0x43: case 0x44:
    case 0x45: case 0x46: case 0x47: case 0x48:
        if (param_2 == 0x11) {
            return 0x14;
        }
        break;
    case 0x49: case 0x4a: case 0x4b: case 0x4c:
    case 0x4d: case 0x4e: case 0x4f: case 0x50:
        if (param_2 == 0x11) {
            return 0x15;
        }
        break;
    }
    return 0x18;
}

// 0x710340fbf0 -- vtable call returning bool: iVar != 2 (144 bytes)
u8 FUN_710340fbf0(u64 param_1, s64 param_2)
{
    s32 iVar1 = (*(s32 (*)())(*(s64 *)(*(s64 *)(*(s64 *)(*(s64 *)(param_2 + 0x20) + 0x40)) + 0x110)))();
    return (u8)(iVar1 != 2);
}

// 0x71034f2790 -- vtable call returning bool: iVar == 1 (144 bytes)
u8 FUN_71034f2790(u64 param_1, s64 param_2)
{
    s32 iVar1 = (*(s32 (*)())(*(s64 *)(*(s64 *)(*(s64 *)(*(s64 *)(param_2 + 0x20) + 0x40)) + 0x110)))();
    return (u8)(iVar1 == 1);
}

// 0x71035033a0 -- vtable call returning bool: iVar != 2 variant (144 bytes)
u8 FUN_71035033a0(u64 param_1, s64 param_2)
{
    s32 iVar1 = (*(s32 (*)())(*(s64 *)(*(s64 *)(*(s64 *)(*(s64 *)(param_2 + 0x20) + 0x40)) + 0x110)))();
    return (u8)(iVar1 != 2);
}

// 0x710378e960 -- nested guard init, returns pointer to DAT_710593aae0 (144 bytes)
u64 *FUN_710378e960(void)
{
    s32 iVar1;

    if (((*(u64 *)DAT_710593aac8 & 1) == 0) &&
        (iVar1 = __cxa_guard_acquire((u64 *)DAT_710593aac8), iVar1 != 0)) {
        if (((*(u64 *)DAT_710593aad0 & 1) == 0) &&
            (iVar1 = __cxa_guard_acquire((u64 *)DAT_710593aad0), iVar1 != 0)) {
            *(u64 *)DAT_710593aad8 = 0;
            __cxa_guard_release((u64 *)DAT_710593aad0);
        }
        *(u8 **)DAT_710593aae0 = DAT_710593aad8;
        __cxa_guard_release((u64 *)DAT_710593aac8);
    }
    return (u64 *)DAT_710593aae0;
}

// 0x71037a0990 -- call FUN_710003e210 and return as float (144 bytes)
float FUN_71037a0990(void)
{
    u16 uVar1 = FUN_710003e210();
    return (float)uVar1;
}

// 0x710386a130 -- marshal fields to FUN_7103818550 (144 bytes)
void FUN_710386a130(s64 param_1, s64 param_2)
{
    FUN_7103818550(*(u32 *)(param_1 + 0x9c), *(u64 *)(param_2 + 8),
                   *(u8 *)(param_1 + 0x98), *(u8 *)(param_1 + 0x99),
                   *(u32 *)(param_1 + 0xa0));
}

// 0x71032a3590 -- set 0xffffff if not already set, call FUN_7103540560 (144 bytes)
void FUN_71032a3590(s64 param_1)
{
    s64 lVar1 = *(s64 *)(param_1 + 8);
    if (*(s32 *)(lVar1 + 0x10) != 0xffffff) {
        FUN_7103540560(*(u64 *)DAT_7105331f20);
        *(u32 *)(lVar1 + 0x10) = 0xffffff;
    }
}
