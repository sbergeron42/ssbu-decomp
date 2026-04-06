#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7100 address range, batch d4-015
// Zero-fills, struct inits with vtable setup, vtable dispatch

// ---- External declarations -----------------------------------------------

// PTR_DAT globals — hold runtime pointer values
#pragma GCC visibility push(hidden)
extern u8 *PTR_DAT_71052a3328; // vtable base for FUN_710003aac0
extern u8 *PTR_DAT_71052a3390; // vtable base for FUN_710003bc80
extern s32 *PTR_DAT_71052a3648; // count limit for FUN_710004a590
#pragma GCC visibility pop

// ---- Functions ---------------------------------------------------------------

// 0x710003a4e0 — zero-fill 9 u64 fields
void FUN_710003a4e0(u64 *fields)
{
    fields[7] = 0;
    fields[8] = 0;
    *fields = 0;
    fields[5] = 0;
    fields[6] = 0;
    fields[3] = 0;
    fields[4] = 0;
    fields[1] = 0;
    fields[2] = 0;
}

// 0x710003a7d0 — zero-fill 24 u64 fields in pairs
void FUN_710003a7d0(u64 *fields)
{
    fields[0x16] = 0;
    fields[0x17] = 0;
    fields[0x14] = 0;
    fields[0x15] = 0;
    fields[0x12] = 0;
    fields[0x13] = 0;
    fields[0x10] = 0;
    fields[0x11] = 0;
    fields[0xe] = 0;
    fields[0xf] = 0;
    fields[0xc] = 0;
    fields[0xd] = 0;
    fields[10] = 0;
    fields[0xb] = 0;
    fields[8] = 0;
    fields[9] = 0;
    fields[6] = 0;
    fields[7] = 0;
    fields[4] = 0;
    fields[5] = 0;
    fields[2] = 0;
    fields[3] = 0;
    *fields = 0;
    fields[1] = 0;
}

// 0x710003aac0 — init struct: set fields, store PTR_DAT_71052a3328+0x10 as vtable
void FUN_710003aac0(s64 *self, u32 type, u32 count)
{
    u8 *vtable_base;

    self[2] = 0;
    *(u32 *)(self + 3) = type;
    *(u32 *)((s64)self + 0x1c) = 2;
    vtable_base = PTR_DAT_71052a3328;
    *(u32 *)(self + 4) = count;
    *(u64 *)((s64)self + 0x24) = 0;
    self[6] = 0;
    self[7] = 0;
    *self = (s64)(vtable_base + 0x10);
    self[1] = 0;
}

// 0x710003ac20 — set size category (1 or 2) based on threshold, store value at +0x28
void FUN_710003ac20(s64 self, s32 value)
{
    u32 size_category;

    size_category = 1;
    if (0xffff < value) {
        size_category = 2;
    }
    *(u32 *)(self + 0x1c) = size_category;
    *(s32 *)(self + 0x28) = value;
}

// 0x710003bc80 — init struct: store PTR_DAT_71052a3390+0x10 as vtable, set const at index 1
void FUN_710003bc80(s64 *self)
{
    u8 *vtable_base;

    vtable_base = PTR_DAT_71052a3390;
    self[2] = 0;
    self[3] = 0;
    *self = (s64)(vtable_base + 0x10);
    self[1] = 0x1f00000000LL;
    *(u32 *)(self + 4) = 0;
}

// 0x710003c350 — vtable dispatch: cases 0,2 call vfuncs +0xd8/+0x98; cases 4,6 return 0
u64 FUN_710003c350(s64 *self)
{
    switch ((s32)self[1]) {
    case 0:
    case 2:
        (*(void(**)(s64 *, s32))(*self + 0xd8))(self, 1);
        (*(void(**)(s64 *))(*self + 0x98))(self);
        break;
    case 1:
    case 3:
    case 5:
        break;
    case 4:
    case 6:
        return 0;
    }
    return 1;
}

// 0x710003de30 — vtable dispatch: cases 0,2,5 call vfuncs +0xd8/+0x98; cases 4,6 return 0
u64 FUN_710003de30(s64 *self)
{
    switch ((s32)self[1]) {
    case 0:
    case 2:
    case 5:
        (*(void(**)(s64 *, s32))(*self + 0xd8))(self, 1);
        (*(void(**)(s64 *))(*self + 0x98))(self);
        break;
    case 1:
    case 3:
        break;
    case 4:
    case 6:
        return 0;
    }
    return 1;
}

// 0x710003e030 — vtable dispatch: cases 0,2,5 call vfuncs +0xd8/+0x98; cases 4,6 return 0
u64 FUN_710003e030(s64 *self)
{
    switch ((s32)self[1]) {
    case 0:
    case 2:
    case 5:
        (*(void(**)(s64 *, s32))(*self + 0xd8))(self, 1);
        (*(void(**)(s64 *))(*self + 0x98))(self);
        break;
    case 1:
    case 3:
        break;
    case 4:
    case 6:
        return 0;
    }
    return 1;
}
