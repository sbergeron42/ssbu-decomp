#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7103 address range, batch d-004
// Pool-d worker: auto-generated from Ghidra decompilation

// ---- External declarations -----------------------------------------------

extern "C" {
    int  __cxa_guard_acquire(u64*);
    void __cxa_guard_release(u64*);
}

extern void FUN_710392e590(void*);
extern void FUN_71033137f0(u64, u32);

// External data
extern u8 DAT_710532e8d0[];

// FUN_710379d480 guard data
extern u8 DAT_710593abf8[];
extern u8 DAT_710593aa98[];
extern u8 DAT_710593aaa0[];
extern u8 DAT_710593aaa8[];
extern u8 DAT_710593aab0[];
extern u8 DAT_710593ac00[];

// FUN_710379dc50 / FUN_71037a1170 shared guard data
extern u8 DAT_710593aa20[];
extern u8 DAT_710593aa28[];
extern u8 DAT_710593a9e0[];
extern u8 DAT_710593a9e8[];
extern u8 DAT_710593aa30[];
extern u8 DAT_710593aa38[];

// FUN_71037a1170 guard data
extern u8 DAT_710593aa00[];
extern u8 DAT_710593aa08[];
extern u8 DAT_710593aa10[];
extern u8 DAT_710593aa18[];

// ---- Functions ---------------------------------------------------------------

// 0x710395f890 — no-op (192 bytes)
void FUN_710395f890(void)
{
    return;
}

// 0x71038f9be4 — wrapper: FUN_710392e590(param_2), return 0 (204 bytes)
u64 FUN_71038f9be4(u64 param_1, u64 param_2)
{
    FUN_710392e590((void*)param_2);
    return 0;
}

// 0x71031d0660 — vtable call at 0x20 (no args), return 1 (208 bytes)
u64 FUN_71031d0660(s64 *param_1)
{
    (*(void(*)())(*(s64 *)(*param_1 + 0x20)))();
    return 1;
}

// 0x710336e170 — call FUN_71033137f0 via DAT_710532e8d0+8, return 0 (208 bytes)
u32 FUN_710336e170(void)
{
    FUN_71033137f0(*(u64*)(DAT_710532e8d0 + 8), 0);
    return 0;
}

// 0x71034d3d70 — vtable call at 0x110 returning bool: iVar == 0 (208 bytes)
u8 FUN_71034d3d70(u64 param_1, s64 param_2)
{
    s32 iVar1 = (*(s32(*)())(*(s64*)(*(s64*)(*(s64*)(param_2 + 0x20) + 0x40)) + 0x110))();
    return (u8)(iVar1 == 0);
}

// 0x7103791bb0 — vtable call at 0x230 (no args), return 1 (208 bytes)
u64 FUN_7103791bb0(s64 *param_1)
{
    (*(void(*)())(*(s64 *)(*param_1 + 0x230)))();
    return 1;
}

// 0x710379d480 — triple-nested guard init, returns &DAT_710593ac00 (208 bytes)
u64 *FUN_710379d480(void)
{
    s32 iVar1;

    if (((*(u64*)DAT_710593abf8 & 1) == 0) &&
        (iVar1 = __cxa_guard_acquire((u64*)DAT_710593abf8), iVar1 != 0)) {
        if (((*(u64*)DAT_710593aa98 & 1) == 0) &&
            (iVar1 = __cxa_guard_acquire((u64*)DAT_710593aa98), iVar1 != 0)) {
            if (((*(u64*)DAT_710593aaa0 & 1) == 0) &&
                (iVar1 = __cxa_guard_acquire((u64*)DAT_710593aaa0), iVar1 != 0)) {
                *(u64*)DAT_710593aaa8 = 0;
                __cxa_guard_release((u64*)DAT_710593aaa0);
            }
            *(u8**)DAT_710593aab0 = DAT_710593aaa8;
            __cxa_guard_release((u64*)DAT_710593aa98);
        }
        *(u8**)DAT_710593ac00 = DAT_710593aab0;
        __cxa_guard_release((u64*)DAT_710593abf8);
    }
    return (u64*)DAT_710593ac00;
}

// 0x710379dc50 — triple-nested guard init, returns &DAT_710593aa38 (208 bytes)
u64 *FUN_710379dc50(void)
{
    s32 iVar1;

    if (((*(u64*)DAT_710593aa20 & 1) == 0) &&
        (iVar1 = __cxa_guard_acquire((u64*)DAT_710593aa20), iVar1 != 0)) {
        if (((*(u64*)DAT_710593aa28 & 1) == 0) &&
            (iVar1 = __cxa_guard_acquire((u64*)DAT_710593aa28), iVar1 != 0)) {
            if (((*(u64*)DAT_710593a9e0 & 1) == 0) &&
                (iVar1 = __cxa_guard_acquire((u64*)DAT_710593a9e0), iVar1 != 0)) {
                *(u64*)DAT_710593a9e8 = 0;
                __cxa_guard_release((u64*)DAT_710593a9e0);
            }
            *(u8**)DAT_710593aa30 = DAT_710593a9e8;
            __cxa_guard_release((u64*)DAT_710593aa28);
        }
        *(u8**)DAT_710593aa38 = DAT_710593aa30;
        __cxa_guard_release((u64*)DAT_710593aa20);
    }
    return (u64*)DAT_710593aa38;
}

// 0x71037a0060 — vtable call at 0x230 (no args), return 1 (208 bytes)
u64 FUN_71037a0060(s64 *param_1)
{
    (*(void(*)())(*(s64 *)(*param_1 + 0x230)))();
    return 1;
}

// 0x71037a1170 — triple-nested guard init (shares inner guard with dc50), returns &DAT_710593aa18 (208 bytes)
u64 *FUN_71037a1170(void)
{
    s32 iVar1;

    if (((*(u64*)DAT_710593aa00 & 1) == 0) &&
        (iVar1 = __cxa_guard_acquire((u64*)DAT_710593aa00), iVar1 != 0)) {
        if (((*(u64*)DAT_710593aa08 & 1) == 0) &&
            (iVar1 = __cxa_guard_acquire((u64*)DAT_710593aa08), iVar1 != 0)) {
            if (((*(u64*)DAT_710593a9e0 & 1) == 0) &&
                (iVar1 = __cxa_guard_acquire((u64*)DAT_710593a9e0), iVar1 != 0)) {
                *(u64*)DAT_710593a9e8 = 0;
                __cxa_guard_release((u64*)DAT_710593a9e0);
            }
            *(u8**)DAT_710593aa10 = DAT_710593a9e8;
            __cxa_guard_release((u64*)DAT_710593aa08);
        }
        *(u8**)DAT_710593aa18 = DAT_710593aa10;
        __cxa_guard_release((u64*)DAT_710593aa00);
    }
    return (u64*)DAT_710593aa18;
}

// 0x71033c86a0 — vtable call at 0x108 with flag, return ~uVar1 & 1 (224 bytes)
u64 FUN_71033c86a0(u64 param_1, s64 param_2)
{
    s64 *plVar2 = *(s64**)(*(s64*)(param_2 + 0x20) + 0x50);
    u32 uVar1 = (*(u32(*)(s64*, u32))(*(s64 *)(*plVar2 + 0x108)))(plVar2, 0x20000006);
    return ~uVar1 & 1;
}

// 0x71031cfe40 — vtable call at 0x20 (no args), return 1 (224 bytes)
u64 FUN_71031cfe40(s64 *param_1)
{
    (*(void(*)())(*(s64 *)(*param_1 + 0x20)))();
    return 1;
}
