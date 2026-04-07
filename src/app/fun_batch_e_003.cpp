#include "types.h"

// Batch decompiled via Ghidra MCP -- pool-e, batch 003
// Rewritten with derivation chains + VT macro

#define VT(m) (*reinterpret_cast<void***>(m))

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

// 0x710025afa0 -- wrapper: forward to FUN_710025afd0, return bit 0
// param_1 [inferred: container struct]
//   +0x20 [inferred: embedded sub-object passed to FUN_710025afd0]
u32 FUN_710025afa0(s64 param_1, u64 param_2, u64 param_3)
{
    u32 result;
    u64 out = param_3;

    result = FUN_710025afd0(param_1 + 0x20, param_2, &out);  // +0x20 [inferred: sub-object]
    return result & 1;
}

// 0x710025ceb0 -- wrapper: forward to FUN_710025cee0, return bit 0
// param_1 [inferred: container struct]
//   +0x20 [inferred: embedded sub-object passed to FUN_710025cee0]
u32 FUN_710025ceb0(s64 param_1, u64 param_2, u32 param_3)
{
    u32 result;
    u32 out = param_3;

    result = FUN_710025cee0(param_1 + 0x20, param_2, &out);  // +0x20 [inferred: sub-object]
    return result & 1;
}

// 0x710026f260 -- wrapper: forward to FUN_710026f290, return bit 0
// param_1 [inferred: container struct]
//   +0x28 [inferred: embedded sub-object passed to FUN_710026f290]
u32 FUN_710026f260(s64 param_1, u64 param_2, u64 param_3)
{
    u32 result;
    u64 out = param_3;

    result = FUN_710026f290(param_1 + 0x28, param_2, &out);  // +0x28 [inferred: sub-object]
    return result & 1;
}

// 0x71002b3830 -- release handle: destroy resource, cleanup, null out
// param_1 [inferred: handle pointer — FUN_71002b7df0 destroys, FUN_71002b5920 cleans up]
void FUN_71002b3830(u64 *param_1)
{
    FUN_71002b7df0(*param_1);
    FUN_71002b5920(*param_1);
    *param_1 = 0;
}

// 0x71002b41a0 -- release handle: destroy resource, cleanup, null out
// param_1 [inferred: handle pointer — FUN_71002ba4d0 destroys, FUN_71002b9b20 cleans up]
void FUN_71002b41a0(u64 *param_1)
{
    FUN_71002ba4d0(*param_1);
    FUN_71002b9b20(*param_1);
    *param_1 = 0;
}

// 0x71002b4ae0 -- release handle: destroy resource, cleanup, null out
// param_1 [inferred: handle pointer — FUN_71002c1480 destroys, FUN_71002bf040 cleans up]
void FUN_71002b4ae0(u64 *param_1)
{
    FUN_71002c1480(*param_1);
    FUN_71002bf040(*param_1);
    *param_1 = 0;
}

// 0x7100cec330 -- check if status kind is not 0x1ea/0x1eb
// param_2 [inferred: BattleObject*]
//   +0x20 [inferred: BattleObjectModuleAccessor* — same pattern across 5+ call sites]
//   acc+0x40 = status_module [derived: StatusModule__*_impl (.dynsym) loads from accessor+0x40]
//   vtable+0x110 = StatusKind [derived: status_kind_impl (.dynsym) dispatches to vtable+0x110]
bool FUN_7100cec330(u64 param_1, s64 param_2)
{
    // +0x20 [inferred: module accessor from BattleObject]
    // +0x40 [derived: status_module, StatusModule__*_impl (.dynsym)]
    s64 *status_mod = *(s64 **)(*(s64 *)(param_2 + 0x20) + 0x40);
    // vtable+0x110 [derived: StatusKind, status_kind_impl (.dynsym)]
    s32 status_kind = reinterpret_cast<s32 (*)(s64 *)>(VT(status_mod)[0x110 / 8])(status_mod);
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

// 0x710049f5b8 -- vtable call at slot 0x20/8, return != -1
// param_1 [inferred: wrapper struct]
//   +0x08 [inferred: inner vtable-bearing object pointer]
//   vtable+0x20 [inferred: lookup method, returns s32 index or -1 on failure]
bool FUN_710049f5b8(s64 param_1, u64 param_2, u64 param_3)
{
    s64 *obj = *(s64 **)(param_1 + 8);  // +0x08 [inferred: inner object pointer]
    // vtable+0x20 [inferred: index lookup, -1 = not found]
    s32 result = reinterpret_cast<s32 (*)(s64 *, u64)>(VT(obj)[0x20 / 8])(obj, param_3 & 0xffffffffff);
    return result != -1;
}

// 0x7100125cc0 -- store fields at +0x134c/+0x1350/+0x1361
// param_1 [inferred: large struct, possibly FighterEntry or similar (size > 0x1368)]
//   +0x134c [inferred: u32 field, set from param_2[0]]
//   +0x1350 [inferred: 16-byte data block, copied from param_2+4]
//   +0x1361 [inferred: bool flag, set to true on write]
void FUN_7100125cc0(s64 param_1, u32 *param_2)
{
    *(u32 *)(param_1 + 0x134c) = *param_2;                    // +0x134c [inferred: u32 config/id field]
    memcpy((void *)(param_1 + 0x1350), param_2 + 1, 0x10);    // +0x1350 [inferred: 16-byte data payload]
    *(u8 *)(param_1 + 0x1361) = 1;                             // +0x1361 [inferred: dirty/valid flag]
}

// 0x7100125d00 -- clear fields at +0x134c/+0x1350/+0x1361
// Same struct as FUN_7100125cc0
void FUN_7100125d00(s64 param_1)
{
    *(u32 *)(param_1 + 0x134c) = 1;                            // +0x134c [inferred: reset to default 1]
    memset((void *)(param_1 + 0x1350), 0, 0x10);               // +0x1350 [inferred: zero data payload]
    *(u8 *)(param_1 + 0x1361) = 0;                             // +0x1361 [inferred: clear dirty/valid flag]
}

// 0x7100129550 -- init sub-object at +0x1368, set flag at +0x1348
// param_1 [inferred: same large struct as FUN_7100125cc0]
//   +0x1368 [inferred: embedded object passed to FUN_71000bf820 for initialization]
//   +0x1348 [inferred: bool flag, set after init]
void FUN_7100129550(s64 param_1)
{
    FUN_71000bf820((void *)(param_1 + 0x1368));  // +0x1368 [inferred: embedded sub-object]
    *(u8 *)(param_1 + 0x1348) = 1;               // +0x1348 [inferred: initialized flag]
}

// 0x7100179480 -- factory: allocate 0xab0-byte object
// [inferred: allocator pattern — FUN_71000b1b90 gets heap id, FUN_7100130810 allocates]
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
