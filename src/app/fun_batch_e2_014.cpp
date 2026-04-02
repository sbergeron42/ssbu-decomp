#include "types.h"

// MEDIUM-tier named functions — 0x71037340c0-0x71037ae670 range, batch e2-014
// L2CValue constructors, type-check accessors, and field helpers
// Decoded from binary via pattern analysis

// ---- L2CValue constructors -----------------------------------------------
// L2CValue layout: [+0] type:u32 (4 bytes), [+4] pad (4 bytes), [+8] value:u64
// Type tags: 1=Bool, 2=Integer, 4=Pointer, 5=Table, 6=InnerFunction, 7=Hash40

// FUN_71037340c0 — TODO: type=1 (Bool), binary has `and w2,w1,#1` dead code pattern

// 0x71037340e0 — type=2, sxtw x8,w1 then str x8 — Integer constructor (signed)
void L2CValue_71037340e0(u64 param_1, s32 param_2)
{
    *(u32 *)param_1 = 2;
    *(s64 *)(param_1 + 8) = (s64)param_2;
}

// 0x7103734100 — type=2, mov w8,w1 then str x8 — Integer constructor (unsigned/zero-extend)
void L2CValue_7103734100(u64 param_1, u32 param_2)
{
    *(u32 *)param_1 = 2;
    *(u64 *)(param_1 + 8) = (u64)param_2;
}

// 0x7103734160 — type=5 (Table), stores pointer then increments [ptr] ref count
void L2CValue_7103734160(u64 param_1, u64 param_2)
{
    *(u32 *)param_1 = 5;
    *(u64 *)(param_1 + 8) = param_2;
    (*(u32 *)param_2)++;
}

// 0x7103734180 — type=6 (InnerFunction), stores pointer then increments [ptr+8] ref count
void L2CValue_7103734180(u64 param_1, u64 param_2)
{
    *(u32 *)param_1 = 6;
    *(u64 *)(param_1 + 8) = param_2;
    (*(u32 *)(param_2 + 8))++;
}

// 0x71037341a0 — type=7 (Hash40), stores lower 40 bits of param_2
void L2CValue_71037341a0(u64 param_1, u64 param_2)
{
    *(u32 *)param_1 = 7;
    *(u64 *)(param_1 + 8) = param_2 & 0xFFFFFFFFFFULL;
}

// ---- L2CValue type-check accessors ----------------------------------------
// Pattern: ldr w8,[x0]; cmp/ccmp; b.ne; ldr x0,[x0,#8]; ret; mov x0,xzr; ret

// 0x7103735e80 — as_hash: return value if type==7 (Hash40) or type==2 (Integer)
u64 as_hash(u64 param_1)
{
    u32 type = *(u32 *)param_1;
    if (type == 7 || type == 2)
        return *(u64 *)(param_1 + 8);
    return 0;
}

// 0x7103735f90 — as_pointer: return value if type==4 (Pointer)
u64 as_pointer(u64 param_1)
{
    if (*(u32 *)param_1 != 4)
        return 0;
    return *(u64 *)(param_1 + 8);
}

// 0x7103735fb0 — as_table: return value if type==5 (Table)
u64 as_table(u64 param_1)
{
    if (*(u32 *)param_1 != 5)
        return 0;
    return *(u64 *)(param_1 + 8);
}

// 0x7103735fd0 — as_inner_function: return value if type==6 (InnerFunction)
u64 as_inner_function(u64 param_1)
{
    if (*(u32 *)param_1 != 6)
        return 0;
    return *(u64 *)(param_1 + 8);
}

// ---- Field helpers -------------------------------------------------------

// 0x71037ae670 — get_format: double-deref, return field at [*param_1 + 0x10]
u64 get_format(u64 param_1)
{
    u64 ptr = *(u64 *)param_1;
    if (!ptr)
        return 0;
    return *(u64 *)(ptr + 0x10);
}
