#include "types.h"

// MEDIUM-tier FUN_* functions — 0x71001xxxxx range, batch d4-011
// Pool-d worker: auto-generated from Ghidra decompilation
// Includes: DLL circular search, protocol tables, ring buf

// ---- External declarations -----------------------------------------------

// Network protocol field write targets (FUN_7100149270 / FUN_7100149290 removed — dup)
#pragma GCC visibility push(hidden)
extern u64 PTR_DAT_71052a3bd0;
extern u64 PTR_DAT_71052a3bd8;

// Vtable init base (FUN_710014f150)
extern u64 PTR_DAT_71052a4f38;
#pragma GCC visibility pop

// ---- Functions ---------------------------------------------------------------

// 0x7100149270 — write value to indexed slot at +0x180, conditionally to PTR field
void FUN_7100149270(s64 self, s32 value)
{
    *(s32 *)(self + (u64)*(u8 *)(self + 0x162) * 4 + 0x180) = value;
    if (value != 0) {
        *(s32 *)(PTR_DAT_71052a3bd0 + 0x124) = value;
    }
}

// 0x710014f150 — init vtable ptr in self[0] to PTR_DAT+0x10, zero self[1] low 32b
void FUN_710014f150(s64 *self)
{
    *(u32 *)(self + 1) = 0;
    *self = (s64)(PTR_DAT_71052a4f38 + 0x10);
}

// 0x71001506d0 — circular DLL search: find node+0x20==target, write bit0(flag) at +0x2e
u64 FUN_71001506d0(s64 list, s64 target, u8 flag)
{
    s64 node;
    u8 masked = flag & 1;

    node = *(s64 *)(list + 0x10);
    if (node == list + 8) {
        return 0;
    }
    do {
        if (*(s64 *)(node + 0x20) == target) {
            *(u8 *)(node + 0x2e) = masked;
            return 1;
        }
        node = *(s64 *)(node + 8);
    } while (node != list + 8);
    return 0;
}

// 0x7100150900 — circular DLL: clear u32 field+0x14 in every node
void FUN_7100150900(s64 list)
{
    s64 node;

    for (node = *(s64 *)(list + 0x10); node != list + 8; node = *(s64 *)(node + 8)) {
        *(u32 *)(node + 0x14) = 0;
    }
}

// 0x7100150de0 — circular DLL search: find node+0x20==target, copy byte+0x2d to *out
u64 FUN_7100150de0(s64 list, s64 target, u8 *out)
{
    s64 node;

    node = *(s64 *)(list + 0x10);
    if (node == list + 8) {
        return 0;
    }
    do {
        if (*(s64 *)(node + 0x20) == target) {
            *out = *(u8 *)(node + 0x2d);
            return 1;
        }
        node = *(s64 *)(node + 8);
    } while (node != list + 8);
    return 0;
}

// 0x7100150e30 — circular DLL search: find node+0x20==target, write bit0(flag) at +0x2c
void FUN_7100150e30(s64 list, s64 target, u8 flag)
{
    s64 node;

    node = *(s64 *)(list + 0x10);
    if (node != list + 8) {
        do {
            if (*(s64 *)(node + 0x20) == target) {
                *(u8 *)(node + 0x2c) = flag & 1;
                return;
            }
            node = *(s64 *)(node + 8);
        } while (node != list + 8);
    }
}

// 0x7100150ec0 — circular DLL: count nodes where field+0x28 == target
s32 FUN_7100150ec0(s64 list, s32 target)
{
    s32 *field_ptr;
    s32 count;
    s64 node;

    node = *(s64 *)(list + 0x10);
    if (node != list + 8) {
        count = 0;
        do {
            field_ptr = (s32 *)(node + 0x28);
            node = *(s64 *)(node + 8);
            if (*field_ptr == target) {
                count = count + 1;
            }
        } while (node != list + 8);
        return count;
    }
    return 0;
}

// 0x7100151fe0 — check two flags + bit test: return 1 if field+0x78 ∈ {0,4,5}
u32 FUN_7100151fe0(s64 self)
{
    if (((*(s8 *)(self + 0x48) != '\0') && (*(s8 *)(self + 0x50) != '\0')) &&
       (*(u32 *)(self + 0x78) < 6)) {
        return 0x31U >> (u64)(*(u32 *)(self + 0x78) & 0x1f) & 1;
    }
    return 0;
}

// 0x7100153d50 — write *key to array slot 0x1b, call vtable[0x98], return slot 0x1d
s64 *FUN_7100153d50(s64 *self, u32 *key)
{
    *(u32 *)(self + 0x1b) = *key;
    (**(void(**)())(*self + 0x98))();
    return self + 0x1d;
}

// 0x7100154c10 — linear search: scan stride-6 array for target, return index
u64 FUN_7100154c10(s32 *entries, s32 target)
{
    s32 *count_ptr;
    u64 index;

    count_ptr = entries + 0xc0;
    if (*count_ptr < 1) {
        return 0xffffffff;
    }
    index = 0;
    do {
        if (*entries == target) {
            return index & 0xffffffff;
        }
        index = index + 1;
        entries = entries + 6;
    } while ((s64)index < (s64)*count_ptr);
    return 0xffffffff;
}

// 0x7100154c60 — ring buffer append: write value at index field+0x300, return index or -1
s32 FUN_7100154c60(s64 self, u32 value)
{
    s32 write_index;

    if (*(s32 *)(self + 0x300) < 0x20) {
        *(u32 *)(self + (s64)*(s32 *)(self + 0x300) * 0x18) = value;
        write_index = *(s32 *)(self + 0x300);
        *(s32 *)(self + 0x300) = write_index + 1;
        return write_index;
    }
    return -1;
}

// 0x7100154f10 — advance circular write cursor: return ptr to next slot, or 0 if wrapped
s64 FUN_7100154f10(s64 ring)
{
    u32 next_raw;
    u32 capacity;
    u32 write_pos;
    s32 next_pos;
    u32 quotient;

    capacity = *(u32 *)(ring + 0x10);
    write_pos = *(u32 *)(ring + 0x14);
    next_raw = write_pos + 1;
    quotient = 0;
    if (capacity != 0) {
        quotient = next_raw / capacity;
    }
    next_pos = next_raw - quotient * capacity;
    if (next_pos == *(s32 *)(ring + 0x1c)) {
        return 0;
    }
    *(s32 *)(ring + 0x14) = next_pos;
    return *(s64 *)(ring + 8) + (u64)write_pos * 0x658;
}

// 0x7100154f50 — peek circular buffer at cursor+offset, return ptr or 0
s64 FUN_7100154f50(s64 ring, s32 offset)
{
    u32 raw_pos;
    u32 capacity;
    u32 quotient;

    capacity = *(u32 *)(ring + 0x10);
    raw_pos = *(s32 *)(ring + 0x18) + offset;
    quotient = 0;
    if (capacity != 0) {
        quotient = raw_pos / capacity;
    }
    raw_pos = raw_pos - quotient * capacity;
    if (*(u32 *)(ring + 0x14) == raw_pos) {
        return 0;
    }
    return *(s64 *)(ring + 8) + (u64)raw_pos * 0x658;
}

// 0x7100155000 — if field+0x20 >= 0: truncate to s32 into field+0x1c and reset to -1
void FUN_7100155000(s64 ring)
{
    if (-1 < *(s64 *)(ring + 0x20)) {
        *(s32 *)(ring + 0x1c) = (s32)*(s64 *)(ring + 0x20);
        *(u64 *)(ring + 0x20) = 0xffffffffffffffff;
    }
}

// 0x71001578e0 — scan byte array at self+0x29 for needle char, return 1 if not found
u64 FUN_71001578e0(s64 self, s8 needle)
{
    s64 i;

    if (*(s32 *)(self + 0x4c) < 1) {
        return 1;
    }
    i = 0;
    do {
        if (*(s8 *)(self + 0x29 + i) == needle) {
            return 0;
        }
        i = i + 1;
    } while (i < *(s32 *)(self + 0x4c));
    return 1;
}
