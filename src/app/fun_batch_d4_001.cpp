#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7100 address range, batch d4-001
// Table lookups, switch dispatchers, struct inits

// ---- External declarations -----------------------------------------------

[[noreturn]] extern "C" void nn__detail__UnexpectedDefaultImpl(const char*, const char*, s32);

// External FUN_* forward declarations
extern "C" char *FUN_71002c31d0(s64);
extern "C" void  FUN_71002c3200(void *);
extern "C" s64   FUN_71000339f0(u64);
extern "C" u32   FUN_71002c2f60(u32, u32);
extern "C" u32   FUN_71002c2d60(u32, u32);
extern "C" void  FUN_710003a0e0();
extern "C" void  FUN_710003a240(s64);
extern "C" void  FUN_7100313000(s64, s64, s64, s64, s64);
extern "C" void  FUN_7100313460(s64, s64, s64, s64, s64);

// External data
#pragma GCC visibility push(hidden)
extern u8 DAT_71044a7c80;
extern u8 DAT_71044a7cd0;
extern u8 DAT_71044a7d50;
#pragma GCC visibility pop

// ---- Functions ---------------------------------------------------------------

// 0x71002c2810 — table lookup by index (<3): return u64 entry from DAT table
u64 FUN_71002c2810(u32 index)
{
    if (index < 3) {
        return *(u64 *)(&DAT_71044a7c80 + (s64)(s32)index * 8);
    }
    /* WARNING: Subroutine does not return */
    nn__detail__UnexpectedDefaultImpl("", "", 0);
}

// 0x71002c2bf0 — table lookup by index (<12): return u32 entry from DAT table
u32 FUN_71002c2bf0(u32 index)
{
    if (index < 0xc) {
        return *(u32 *)(&DAT_71044a7cd0 + (s64)(s32)index * 4);
    }
    /* WARNING: Subroutine does not return */
    nn__detail__UnexpectedDefaultImpl("", "", 0);
}

// 0x71002c2c30 — switch returning pointer offset into self by category (12 cases)
s64 FUN_71002c2c30(s64 self, u32 category, s32 slot)
{
    switch(category) {
    case 0:
        return self + (s64)slot * 0x58 + 0x6c;
    case 1:
        return self + (s64)slot * 0x58 + 0x1cc;
    case 2:
        return self + (s64)slot * 0x58 + 0x5ec;
    case 3:
        return self + (s64)slot * 0x58 + 0xa0c;
    case 4:
        return self + (s64)slot * 0x58 + 0x376c;
    case 5:
        return self + (s64)slot * 0x58 + 0x64cc;
    case 6:
        return self + (s64)slot * 0x58 + 0x922c;
    case 7:
        return self + (s64)slot * 0x58 + 0xbf8c;
    case 8:
        return self + (s64)slot * 0x58 + 0xecec;
    case 9:
        return self + (s64)slot * 0x58 + 0x11a4c;
    case 10:
        return self + (s64)slot * 0x58 + 0x11aa4;
    case 0xb:
        return self + (s64)slot * 0x58 + 0x120d4;
    default:
        /* WARNING: Subroutine does not return */
        nn__detail__UnexpectedDefaultImpl("", "", 0);
    }
}

// 0x71002c2df0 — table lookup by index (<11): return u32 entry from DAT table
u32 FUN_71002c2df0(u32 index)
{
    if (index < 0xb) {
        return *(u32 *)(&DAT_71044a7d50 + (s64)(s32)index * 4);
    }
    /* WARNING: Subroutine does not return */
    nn__detail__UnexpectedDefaultImpl("", "", 0);
}

// 0x71002c2e50 — switch returning pointer offset into self by category (11 cases)
u8 *FUN_71002c2e50(s64 self, u32 category, s32 slot)
{
    switch(category) {
    case 0:
        return (u8 *)(self + (s64)slot * 0x1c + 100);
    case 1:
        return (u8 *)(self + (s64)slot * 0x1c + 0xed4);
    case 2:
        return (u8 *)(self + (s64)slot * 0x1c + 0x159c);
    case 3:
        return (u8 *)(self + (s64)slot * 0x1c + 0x183c);
    case 4:
        return (u8 *)(self + (s64)slot * 0x1c + 0x1874);
    case 5:
        return (u8 *)(self + (s64)slot * 0x1c + 0x19c4);
    case 6:
        return (u8 *)(self + (s64)slot * 0x1c + 0x1b14);
    case 7:
        return (u8 *)(self + (s64)slot * 0x1c + 0x1d44);
    case 8:
        return (u8 *)(self + (s64)slot * 0x1c + 0x1d7c);
    case 9:
        return (u8 *)(self + (s64)slot * 0x1c + 0x2188);
    case 10:
        return (u8 *)(self + (s64)slot * 0x1c + 0x2230);
    default:
        /* WARNING: Subroutine does not return */
        nn__detail__UnexpectedDefaultImpl("", "", 0);
    }
}

// 0x71002c1790 — get non-empty string: return ptr if not '\0', else null
char *FUN_71002c1790(s64 self, u32 entry_index)
{
    char *str;
    char *result;

    str = (char *)FUN_71002c31d0(self + (u64)entry_index * 0x128 + 8);
    result = (char *)0x0;
    if (*str != '\0') {
        result = str;
    }
    return result;
}

// 0x71002c1d20 — delegate: call FUN_71002c3200 with computed array offset
void FUN_71002c1d20(s64 self, u32 entry_index)
{
    FUN_71002c3200((void *)(self + (u64)entry_index * 0x128 + 8));
}

// 0x71002c1fe0 — delegate+offset: return FUN_71000339f0(*p) + p[2]
s64 FUN_71002c1fe0(u64 *entry)
{
    s64 base;

    base = FUN_71000339f0(*entry);
    return base + entry[2];
}

// 0x71002c2ba0 — divide field +0x2c by table[1] entry
u64 FUN_71002c2ba0(s64 self)
{
    u32 field_value;
    u64 divisor;
    u64 result;

    field_value = *(u32 *)(self + 0x2c);
    divisor = FUN_71002c2810(1);
    result = 0;
    if (divisor != 0) {
        result = field_value / divisor;
    }
    return result;
}

// 0x71002c2910 — dispatch: lookup type+size, then index into +0x10 region
void FUN_71002c2910(s64 self, u32 category, u32 size)
{
    u32 index;

    index = FUN_71002c2f60(category, size);
    FUN_71002c2df0(category);
    FUN_71002c2e50(*(u64 *)(self + 0x10), category, index);
}

// 0x71002c2960 — dispatch: lookup type+size, then index into +0x18 region
void FUN_71002c2960(s64 self, u32 category, u32 size)
{
    u32 index;

    index = FUN_71002c2d60(category, size);
    FUN_71002c2bf0(category);
    FUN_71002c2c30(*(u64 *)(self + 0x18), category, index);
}

// 0x71002c2f70 — init: call setup fns and set -1 sentinel at +0x120
void FUN_71002c2f70(s64 self)
{
    FUN_710003a0e0();
    FUN_710003a240(self + 0xd8);
    *(u64 *)(self + 0x120) = 0xffffffffffffffff;
}

// 0x710031321c — delegate: call FUN_7100313000 with 4 sub-offsets
u64 FUN_710031321c(s64 data, s64 stream)
{
    FUN_7100313000(data, data + 4, data + 8, data + 0xc, stream + -4);
    return 1;
}

// 0x710031367c — delegate: call FUN_7100313460 with 4 sub-offsets
u64 FUN_710031367c(s64 data, s64 stream)
{
    FUN_7100313460(data, data + 4, data + 8, data + 0xc, stream + -4);
    return 1;
}
