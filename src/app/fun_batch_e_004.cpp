#include "types.h"

// Batch decompiled via Ghidra MCP — pool-e, batch 004
// Range: 0x7100000000 — 0x7100FFFFFF

// ---- External declarations --------------------------------------------------

extern "C" {
    void abort(void);
    void *memcpy(void *, const void *, u64);
}

// Allocator helpers
extern u64  FUN_71000b1b90(void);
extern s64  FUN_7100130810(u64, u64);

// Init functions called by allocator pattern
extern void FUN_71001875f0(s64);
extern void FUN_7100189a10(s64);
extern void FUN_7100194810(s64);
extern void FUN_710017ada0(s64);
extern void FUN_710018ea30(s64);
extern void FUN_710018daa0(s64);
extern void FUN_71001a4310(s64);
extern void FUN_7100186580(s64);
extern void FUN_7100187f50(s64);
extern void FUN_710019c400(s64);
extern void FUN_710019b910(s64);
extern void FUN_710019f980(s64);
extern void FUN_710017bb40(s64);

// Other called functions
extern u64  FUN_7100193a30(u64);
extern void FUN_71001acd50(u64, u32);
extern void FUN_71001b47e0(s64, u64, s64);
extern void FUN_71001cb870(u64, s64, u64, s64);
extern void FUN_71001b6bc0(u64, void *);

// Data pointer variables
extern u8  *PTR_DAT_71052a3da8;   // char* — checked against '\0'
extern u64 *PTR_DAT_71052a3db8;   // u64*  — used as handle
extern u8  *PTR_DAT_71052a3df0;   // u64*  — dereferenced as u64

// ---- Allocator-pattern functions -------------------------------------------

// 0x7100194310 — alloc 0x60, init FUN_71001875f0
s64 FUN_7100194310(void)
{
    u64 uVar1;
    s64 lVar2;

    uVar1 = FUN_71000b1b90();
    lVar2 = FUN_7100130810(0x60, uVar1);
    if (lVar2 != 0) {
        FUN_71001875f0(lVar2);
    }
    return lVar2;
}

// 0x7100194390 — alloc 0xf0, init FUN_7100189a10
s64 FUN_7100194390(void)
{
    u64 uVar1;
    s64 lVar2;

    uVar1 = FUN_71000b1b90();
    lVar2 = FUN_7100130810(0xf0, uVar1);
    if (lVar2 != 0) {
        FUN_7100189a10(lVar2);
    }
    return lVar2;
}

// 0x7100179500 — alloc 0x118, init FUN_7100194810
s64 FUN_7100179500(void)
{
    u64 uVar1;
    s64 lVar2;

    uVar1 = FUN_71000b1b90();
    lVar2 = FUN_7100130810(0x118, uVar1);
    if (lVar2 != 0) {
        FUN_7100194810(lVar2);
    }
    return lVar2;
}

// 0x7100179ab0 — alloc 0xa0, init FUN_710017ada0
s64 FUN_7100179ab0(void)
{
    u64 uVar1;
    s64 lVar2;

    uVar1 = FUN_71000b1b90();
    lVar2 = FUN_7100130810(0xa0, uVar1);
    if (lVar2 != 0) {
        FUN_710017ada0(lVar2);
    }
    return lVar2;
}

// 0x7100194410 — alloc 0x80, init FUN_710018ea30
s64 FUN_7100194410(void)
{
    u64 uVar1;
    s64 lVar2;

    uVar1 = FUN_71000b1b90();
    lVar2 = FUN_7100130810(0x80, uVar1);
    if (lVar2 != 0) {
        FUN_710018ea30(lVar2);
    }
    return lVar2;
}

// 0x7100194490 — alloc 0x1b0, init FUN_710018daa0
s64 FUN_7100194490(void)
{
    u64 uVar1;
    s64 lVar2;

    uVar1 = FUN_71000b1b90();
    lVar2 = FUN_7100130810(0x1b0, uVar1);
    if (lVar2 != 0) {
        FUN_710018daa0(lVar2);
    }
    return lVar2;
}

// 0x7100194510 — alloc 0x130, init FUN_71001a4310
s64 FUN_7100194510(void)
{
    u64 uVar1;
    s64 lVar2;

    uVar1 = FUN_71000b1b90();
    lVar2 = FUN_7100130810(0x130, uVar1);
    if (lVar2 != 0) {
        FUN_71001a4310(lVar2);
    }
    return lVar2;
}

// 0x7100194590 — alloc 0x80, init FUN_7100186580
s64 FUN_7100194590(void)
{
    u64 uVar1;
    s64 lVar2;

    uVar1 = FUN_71000b1b90();
    lVar2 = FUN_7100130810(0x80, uVar1);
    if (lVar2 != 0) {
        FUN_7100186580(lVar2);
    }
    return lVar2;
}

// 0x7100194610 — alloc 0x80, init FUN_7100187f50
s64 FUN_7100194610(void)
{
    u64 uVar1;
    s64 lVar2;

    uVar1 = FUN_71000b1b90();
    lVar2 = FUN_7100130810(0x80, uVar1);
    if (lVar2 != 0) {
        FUN_7100187f50(lVar2);
    }
    return lVar2;
}

// 0x7100194690 — alloc 0xf8, init FUN_710019c400
s64 FUN_7100194690(void)
{
    u64 uVar1;
    s64 lVar2;

    uVar1 = FUN_71000b1b90();
    lVar2 = FUN_7100130810(0xf8, uVar1);
    if (lVar2 != 0) {
        FUN_710019c400(lVar2);
    }
    return lVar2;
}

// 0x7100194710 — alloc 0x260, init FUN_710019b910
s64 FUN_7100194710(void)
{
    u64 uVar1;
    s64 lVar2;

    uVar1 = FUN_71000b1b90();
    lVar2 = FUN_7100130810(0x260, uVar1);
    if (lVar2 != 0) {
        FUN_710019b910(lVar2);
    }
    return lVar2;
}

// 0x7100194790 — alloc 0x1130, init FUN_710019f980
s64 FUN_7100194790(void)
{
    u64 uVar1;
    s64 lVar2;

    uVar1 = FUN_71000b1b90();
    lVar2 = FUN_7100130810(0x1130, uVar1);
    if (lVar2 != 0) {
        FUN_710019f980(lVar2);
    }
    return lVar2;
}

// 0x7100179b30 — alloc 0xb8, init FUN_710017bb40
s64 FUN_7100179b30(void)
{
    u64 uVar1;
    s64 lVar2;

    uVar1 = FUN_71000b1b90();
    lVar2 = FUN_7100130810(0xb8, uVar1);
    if (lVar2 != 0) {
        FUN_710017bb40(lVar2);
    }
    return lVar2;
}

// ---- Other small functions --------------------------------------------------

// 0x710065fa64 — abort stub
void FUN_710065fa64(void)
{
    abort();
}

// 0x710017c180 — memcpy then conditional byte fixup
void FUN_710017c180(void *param_1, void *param_2, u64 param_3)
{
    memcpy(param_1, param_2, param_3 & 0xffffffff);
    if (*(char *)((s64)param_1 + 9) != '\0') {
        return;
    }
    *(u8 *)((s64)param_1 + 9) = 0x14;
}

// 0x71001aa330 — get handle, dispatch, clear field
void FUN_71001aa330(s64 param_1)
{
    u64 uVar1;

    uVar1 = FUN_7100193a30(*(u64 *)PTR_DAT_71052a3df0);
    FUN_71001acd50(uVar1, *(u32 *)(param_1 + 0x78));
    *(u32 *)(param_1 + 0x78) = 0;
}

// 0x71001b3cb0 — conditional update via FUN_71001b47e0
s64 FUN_71001b3cb0(s64 param_1, s64 param_2)
{
    if (*(s64 *)(param_1 + 0x18) != param_2) {
        FUN_71001b47e0(param_1, param_2, 0xffffffffffffffff);
    }
    return param_1;
}

// 0x71001cfce0 — passthrough to FUN_71001cb870
u64 FUN_71001cfce0(u64 param_1, s64 param_2)
{
    FUN_71001cb870(param_1,
                   *(s64 *)(param_2 + 0x10) + *(s64 *)(param_2 + 0x28),
                   *(u64 *)(param_2 + 0x18), 0xffffffffffffffff);
    return param_1;
}

// 0x71001d05f0 — passthrough variant using field dereference
s64 FUN_71001d05f0(s64 param_1, s64 param_2)
{
    FUN_71001cb870(*(u64 *)(param_1 + 0x10),
                   *(s64 *)(param_2 + 0x10) + *(s64 *)(param_2 + 0x28),
                   *(u64 *)(param_2 + 0x18), 0xffffffffffffffff);
    return param_1;
}

// 0x71001d7470 — conditional dispatch via PTR
void FUN_71001d7470(u32 param_1)
{
    u32 local_14;

    if (*PTR_DAT_71052a3da8 != '\0') {
        local_14 = param_1;
        FUN_71001b6bc0(*(u64 *)PTR_DAT_71052a3db8, &local_14);
    }
}
