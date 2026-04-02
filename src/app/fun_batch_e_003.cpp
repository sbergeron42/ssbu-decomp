#include "types.h"

// Batch decompiled via Ghidra MCP — pool-e, batch 003
// Range: 0x7100000000 — 0x7100FFFFFF

// ---- External declarations --------------------------------------------------

extern "C" {
    void abort(void);
    void *memcpy(void *, const void *, u64);
    void *memset(void *, s32, u64);
}

// Called functions
extern u32  FUN_710025afd0(s64, u64, u64 *);
extern u32  FUN_710025cee0(s64, u64, u32 *);
extern u32  FUN_710026f290(s64, u64, u64 *);
extern void FUN_71002b7df0(u64);
extern void FUN_71002b5920(u64);
extern void FUN_71002ba4d0(u64);
extern void FUN_71002b9b20(u64);
extern void FUN_71002c1480(u64);
extern void FUN_71002bf040(u64);
extern s64  FUN_71000339f0(u64);
extern u64  FUN_71002c2810(u32);
extern void FUN_710003a0e0(void);
extern void FUN_710003a240(s64);
extern void FUN_71000bf820(void *);
extern u64  FUN_71000b1b90(void);
extern s64  FUN_7100130810(u64, u64);
extern void FUN_7100195180(s64);

// ---- Functions --------------------------------------------------------------

// 0x710025afa0 — wrapper: FUN_710025afd0(param_1+0x20, param_2, &local_18) & 1
u32 FUN_710025afa0(s64 param_1, u64 param_2, u64 param_3)
{
    u32 uVar1;
    u64 local_18;

    local_18 = param_3;
    uVar1 = FUN_710025afd0(param_1 + 0x20, param_2, &local_18);
    return uVar1 & 1;
}

// 0x710025ceb0 — wrapper: FUN_710025cee0(param_1+0x20, param_2, &local_14) & 1
u32 FUN_710025ceb0(s64 param_1, u64 param_2, u32 param_3)
{
    u32 uVar1;
    u32 local_14;

    local_14 = param_3;
    uVar1 = FUN_710025cee0(param_1 + 0x20, param_2, &local_14);
    return uVar1 & 1;
}

// 0x710026f260 — wrapper: FUN_710026f290(param_1+0x28, param_2, &local_18) & 1
u32 FUN_710026f260(s64 param_1, u64 param_2, u64 param_3)
{
    u32 uVar1;
    u64 local_18;

    local_18 = param_3;
    uVar1 = FUN_710026f290(param_1 + 0x28, param_2, &local_18);
    return uVar1 & 1;
}

// 0x71002b3830 — two-call destructor then null out
void FUN_71002b3830(u64 *param_1)
{
    FUN_71002b7df0(*param_1);
    FUN_71002b5920(*param_1);
    *param_1 = 0;
}

// 0x71002b41a0 — two-call destructor then null out
void FUN_71002b41a0(u64 *param_1)
{
    FUN_71002ba4d0(*param_1);
    FUN_71002b9b20(*param_1);
    *param_1 = 0;
}

// 0x71002b4ae0 — two-call destructor then null out
void FUN_71002b4ae0(u64 *param_1)
{
    FUN_71002c1480(*param_1);
    FUN_71002bf040(*param_1);
    *param_1 = 0;
}

// 0x71002c1fe0 — offset lookup + field addition
s64 FUN_71002c1fe0(u64 *param_1)
{
    s64 lVar1;

    lVar1 = FUN_71000339f0(*param_1);
    return lVar1 + param_1[2];
}

// 0x71002c2ba0 — field / FUN_71002c2810(1), guarded divide
u64 FUN_71002c2ba0(s64 param_1)
{
    u32 uVar1;
    u64 uVar2;
    u64 uVar3;

    uVar1 = *(u32 *)(param_1 + 0x2c);
    uVar3 = FUN_71002c2810(1);
    uVar2 = 0;
    if (uVar3 != 0) {
        uVar2 = uVar1 / uVar3;
    }
    return uVar2;
}

// 0x71002c2f70 — init + store 0xffffffffffffffff
void FUN_71002c2f70(s64 param_1)
{
    FUN_710003a0e0();
    FUN_710003a240(param_1 + 0xd8);
    *(u64 *)(param_1 + 0x120) = 0xffffffffffffffff;
}

// 0x7100cec330 — nested vtable call, return bool
bool FUN_7100cec330(u64 param_1, s64 param_2)
{
    u32 uVar1;

    uVar1 = (*(u32 (**)())(*(s64 *)(*(s64 *)(*(s64 *)(param_2 + 0x20) + 0x40)) + 0x110))();
    return (uVar1 & 0xfffffffe) != 0x1ea;
}

// 0x710065f938 — abort stub
void FUN_710065f938(void)
{
    abort();
}

// 0x710065faa4 — abort stub
void FUN_710065faa4(void)
{
    abort();
}

// 0x710065fae0 — abort stub
void FUN_710065fae0(void)
{
    abort();
}

// 0x710049f5b8 — vtable call at offset 0x20, return != -1
bool FUN_710049f5b8(s64 param_1, u64 param_2, u64 param_3)
{
    s64 *plVar1;
    s32 iVar1;

    plVar1 = *(s64 **)(param_1 + 8);
    iVar1 = (*(s32 (*)(s64 *, u64))(*plVar1 + 0x20))(plVar1, param_3 & 0xffffffffff);
    return iVar1 != -1;
}

// 0x7100125cc0 — store fields at param_1 + 0x134c/0x1350/0x1361
void FUN_7100125cc0(s64 param_1, u32 *param_2)
{
    *(u32 *)(param_1 + 0x134c) = *param_2;
    memcpy((void *)(param_1 + 0x1350), param_2 + 1, 0x10);
    *(u8 *)(param_1 + 0x1361) = 1;
}

// 0x7100125d00 — zero fields at param_1 + 0x134c/0x1350/0x1361
void FUN_7100125d00(s64 param_1)
{
    *(u32 *)(param_1 + 0x134c) = 1;
    memset((void *)(param_1 + 0x1350), 0, 0x10);
    *(u8 *)(param_1 + 0x1361) = 0;
}

// 0x7100129550 — call FUN_71000bf820 then set byte flag
void FUN_7100129550(s64 param_1)
{
    FUN_71000bf820((void *)(param_1 + 0x1368));
    *(u8 *)(param_1 + 0x1348) = 1;
}

// 0x7100179480 — alloc 0xab0-byte object + init
s64 FUN_7100179480(void)
{
    u64 uVar1;
    s64 lVar2;

    uVar1 = FUN_71000b1b90();
    lVar2 = FUN_7100130810(0xab0, uVar1);
    if (lVar2 != 0) {
        FUN_7100195180(lVar2);
    }
    return lVar2;
}
