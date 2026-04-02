#include "types.h"

// Batch decompiled via Ghidra MCP — pool-e, batch 006
// Range: 0x7100000000 — 0x7100FFFFFF

// ---- SDK declarations -------------------------------------------------------

namespace nn { namespace os {
    struct MutexType;
    extern void LockMutex(MutexType *);
    extern void UnlockMutex(MutexType *);
}}

namespace nn { namespace detail {
    [[noreturn]] extern void UnexpectedDefaultImpl(const char *, const char *, s32);
}}

// ---- External declarations --------------------------------------------------

extern "C" {
    void  abort(void);
    void *malloc(u64);
    u64   strlen(const char *);
    char *strcpy(char *, const char *);
    s32  __cxa_guard_acquire(s64 *);
    void __cxa_guard_release(s64 *);
}

// Called functions
extern void FUN_71000b1900(void *);
extern void FUN_71000b1910(s64, void *);
extern s32  FUN_71001c4c40(u32, s64, s64, u64 *, u64, s32);
extern u64  FUN_71001b4200(u64, void *);
extern u64  FUN_71000b1b90(void);
extern s64  FUN_7100130810(u64, u64);
extern u64  FUN_7101717b00(u64);
extern s64  FUN_71001dacc0(s64);
extern void FUN_71001f2180(s64);
extern void FUN_71001bec20(u64, u64);
extern void FUN_71001e1770(u64, u32, void *);
extern void FUN_71000baa20(void);
extern void FUN_71001b47e0(s64, s64, s64);
extern void FUN_71000bb5d0(s64 *);
extern s64 *FUN_71000bb680(void);
extern void FUN_7100179c70(s64, u64);

// Data
extern u8  *PTR_DAT_71052a3db8;
extern u8   DAT_71052b4270[];
extern u16  DAT_71052b4278;
extern u8  *PTR_DAT_71052a5538;
extern void *PTR_DAT_71052a5818;
extern u8  *PTR_DAT_71052a5820;
extern u8  *PTR_DAT_71052a50b0;
extern u8   DAT_71052b82e0;
extern u8   DAT_71052b82f0;
extern u8   DAT_71044a7c80[];
extern u32  DAT_71044718a4;
extern u32  DAT_71044723d8;

// ---- Functions --------------------------------------------------------------

// FUN_7100154200 — TODO: decompile

// 0x71001ce780 — strcpy "Encryption Error" if buffer large enough
u64 FUN_71001ce780(u64 param_1, u64 param_2, char *param_3, u64 param_4)
{
    u64 sVar1;

    sVar1 = strlen("Encryption Error");
    if (sVar1 < param_4) {
        strcpy(param_3, "Encryption Error");
        return 1;
    }
    return 0;
}

// 0x71001e0910 — language table lookup via handle
u16 FUN_71001e0910(void)
{
    u32 *puVar1;

    return DAT_71052b4278;
}

// FUN_71001e1710 — TODO: decompile (nn::nex::qResult constructor)

// 0x7100325e50 — switch returning float constants
u32 FUN_7100325e50(s64 param_1, u32 param_2)
{
    switch (param_2) {
    case 0x23:
        return 0;
    case 0x24: case 0x25: case 0x26: case 0x27:
        return 0x41c80000;
    case 0x3f: case 0x40: case 0x41:
        return DAT_71044718a4;
    case 0x42: case 0x43: case 0x44: case 0x45: case 0x46:
        if (*(s32 *)(param_1 + 0x120) == 0x39) {
            return 0x41a00000;
        }
        if (*(s32 *)(param_1 + 0x120) == 0x47) {
            return 0x41a00000;
        }
        break;
    }
    return DAT_71044723d8;
}

// 0x71004f6590 — empty CXA guard, return byte
u8 FUN_71004f6590(void)
{
    s32 iVar1;

    if (((DAT_71052b82e0 & 1) == 0) &&
        (iVar1 = __cxa_guard_acquire((s64 *)&DAT_71052b82e0), iVar1 != 0)) {
        __cxa_guard_release((s64 *)&DAT_71052b82e0);
    }
    return DAT_71052b82f0;
}

// 0x710065f8a8 — abort stub
void FUN_710065f8a8(void)
{
    abort();
}

// 0x7100405d60 — vtable call + bit test
u32 FUN_7100405d60(s64 *param_1)
{
    s32 iVar1;

    iVar1 = (*(s32 (**)())(*param_1 + 0x28))();
    if ((u32)(iVar1 - 7) < 0x17) {
        return 0x500003u >> ((u64)(u32)((iVar1 - 7) & 0x1f)) & 1;
    }
    return 0;
}

// 0x710065f65c — abort stub
void FUN_710065f65c(void)
{
    abort();
}

// 0x710049f570 — double vtable dereference chain
u32 FUN_710049f570(s64 param_1)
{
    s64 *plVar2;
    u32 uVar1;

    plVar2 = *(s64 **)(*(s64 *)(param_1 + 0x10) + 0x38);
    plVar2 = (s64 *)(*(s64 (*)(s64 *, s32))(*plVar2 + 0x10))(plVar2, 0);
    uVar1 = (*(u32 (**)())(*plVar2 + 0x78))();
    return ~uVar1 & 1;
}

// 0x710065fa1c — abort stub
void FUN_710065fa1c(void)
{
    abort();
}

// 0x710065f610 — abort stub
void FUN_710065f610(void)
{
    abort();
}

// 0x7100f574d0 — nested vtable call + bit test
u32 FUN_7100f574d0(u64 param_1, s64 param_2)
{
    u32 uVar1;

    uVar1 = (*(u32 (**)())(*(s64 *)(*(s64 *)(*(s64 *)(param_2 + 0x20) + 0x40)) + 0x110))();
    if ((u32)(uVar1 - 0x3c) < 5) {
        return 0xcU >> ((u64)(u32)((uVar1 - 0x3c) & 0x1f)) & 1;
    }
    return 1;
}

// 0x71001daf50 — conditional field dereference returning u32
u32 FUN_71001daf50(s64 param_1)
{
    s64 lVar1;

    lVar1 = FUN_71001dacc0(param_1 + 8);
    if (*(s64 *)(lVar1 + 0x10) != 0) {
        lVar1 = FUN_71001dacc0(param_1 + 8);
        return *(u32 *)(*(s64 *)(lVar1 + 8) + 0x24);
    }
    return 0;
}

// 0x71001dafa0 — conditional field dereference returning u16
u16 FUN_71001dafa0(s64 param_1)
{
    s64 lVar1;

    lVar1 = FUN_71001dacc0(param_1 + 8);
    if (*(s64 *)(lVar1 + 0x10) != 0) {
        lVar1 = FUN_71001dacc0(param_1 + 8);
        return *(u16 *)(*(s64 *)(lVar1 + 8) + 0x28);
    }
    return 0;
}

// FUN_71001e0070 — TODO: decompile (nn::nex::StationURL/InetAddress)


// 0x7100179620 — allocator with extra init param
s64 FUN_7100179620(void)
{
    u64 uVar1;
    s64 lVar2;
    u64 uVar3;

    uVar3 = *(u64 *)PTR_DAT_71052a50b0;
    uVar1 = FUN_71000b1b90();
    lVar2 = FUN_7100130810(0x1b8, uVar1);
    if (lVar2 != 0) {
        FUN_7100179c70(lVar2, uVar3);
    }
    return lVar2;
}
