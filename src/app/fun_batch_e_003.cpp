#include "types.h"

// Batch decompiled via Ghidra MCP -- pool-e, batch 003
// Range: 0x7100000000 -- 0x7100FFFFFF

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

// 0x710025afa0 -- wrapper: FUN_710025afd0(param_1+0x20, param_2, &out) & 1
u32 FUN_710025afa0(s64 param_1, u64 param_2, u64 param_3)
{
    u32 result;
    u64 out = param_3;

    result = FUN_710025afd0(param_1 + 0x20, param_2, &out);
    return result & 1;
}

// 0x710025ceb0 -- wrapper: FUN_710025cee0(param_1+0x20, param_2, &out) & 1
u32 FUN_710025ceb0(s64 param_1, u64 param_2, u32 param_3)
{
    u32 result;
    u32 out = param_3;

    result = FUN_710025cee0(param_1 + 0x20, param_2, &out);
    return result & 1;
}

// 0x710026f260 -- wrapper: FUN_710026f290(param_1+0x28, param_2, &out) & 1
u32 FUN_710026f260(s64 param_1, u64 param_2, u64 param_3)
{
    u32 result;
    u64 out = param_3;

    result = FUN_710026f290(param_1 + 0x28, param_2, &out);
    return result & 1;
}

// 0x71002b3830 -- teardown + null out handle
void FUN_71002b3830(u64 *param_1)
{
    FUN_71002b7df0(*param_1);
    FUN_71002b5920(*param_1);
    *param_1 = 0;
}

// 0x71002b41a0 -- teardown + null out handle
void FUN_71002b41a0(u64 *param_1)
{
    FUN_71002ba4d0(*param_1);
    FUN_71002b9b20(*param_1);
    *param_1 = 0;
}

// 0x71002b4ae0 -- teardown + null out handle
void FUN_71002b4ae0(u64 *param_1)
{
    FUN_71002c1480(*param_1);
    FUN_71002bf040(*param_1);
    *param_1 = 0;
}

// 0x7100cec330 -- check if status kind is not 0x1ea/0x1eb
bool FUN_7100cec330(u64 param_1, s64 param_2)
{
    u32 status_kind;

    status_kind = (*(u32 (**)())(*(s64 *)(*(s64 *)(*(s64 *)(param_2 + 0x20) + 0x40)) + 0x110))();
    return (status_kind & 0xfffffffe) != 0x1ea;
}

// 0x710065f938 -- abort stub
void FUN_710065f938(void)
{
    abort();
}

// 0x710065faa4 -- abort stub
void FUN_710065faa4(void)
{
    abort();
}

// 0x710065fae0 -- abort stub
void FUN_710065fae0(void)
{
    abort();
}

// 0x710049f5b8 -- vtable call at offset 0x20, return != -1
bool FUN_710049f5b8(s64 param_1, u64 param_2, u64 param_3)
{
    s64 *obj;
    s32 result;

    obj = *(s64 **)(param_1 + 8);
    result = (*(s32 (*)(s64 *, u64))(*obj + 0x20))(obj, param_3 & 0xffffffffff);
    return result != -1;
}

// 0x7100125cc0 -- store fields at param_1 + 0x134c/0x1350/0x1361
void FUN_7100125cc0(s64 param_1, u32 *param_2)
{
    *(u32 *)(param_1 + 0x134c) = *param_2;
    memcpy((void *)(param_1 + 0x1350), param_2 + 1, 0x10);
    *(u8 *)(param_1 + 0x1361) = 1;
}

// 0x7100125d00 -- zero fields at param_1 + 0x134c/0x1350/0x1361
void FUN_7100125d00(s64 param_1)
{
    *(u32 *)(param_1 + 0x134c) = 1;
    memset((void *)(param_1 + 0x1350), 0, 0x10);
    *(u8 *)(param_1 + 0x1361) = 0;
}

// 0x7100129550 -- call FUN_71000bf820 then set byte flag
void FUN_7100129550(s64 param_1)
{
    FUN_71000bf820((void *)(param_1 + 0x1368));
    *(u8 *)(param_1 + 0x1348) = 1;
}

// 0x7100179480 -- alloc 0xab0-byte object
s64 FUN_7100179480(void)
{
    u64 heap_id;
    s64 obj;

    heap_id = FUN_71000b1b90();
    obj = FUN_7100130810(0xab0, heap_id);
    if (obj != 0) {
    }
    return obj;
}
