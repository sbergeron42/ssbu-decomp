#include "types.h"

// ---- External declarations -----------------------------------------------

extern "C" void FUN_71000b40e0(s64);
extern "C" void FUN_71000b4160(s64);

#pragma GCC visibility push(hidden)
extern u64 DAT_7104f49388;
extern u64 DAT_7104f49390;
extern u64 DAT_7104f49428;
extern u64 DAT_7104f49430;
#pragma GCC visibility pop

// ---- Functions ---------------------------------------------------------------

// 0x710007c310 — Scans variable-stride entries for matching key, returns data ptr (+8 from match)
// Entry layout: [0]=key (s32), [4]=stride (s32), [8..]=data
s32 *FUN_710007c310(s64 header, s32 key)
{
    u32 i;
    s32 *entry;

    if (*(u16 *)(header + 0x10) != 0) {
        i = 0;
        entry = (s32 *)(header + (u64)*(u16 *)(header + 6));
        do {
            if (*entry == key) {
                return entry + 2;
            }
            i = i + 1;
            entry = (s32 *)((s64)entry + (u64)(u32)entry[1]);
        } while (i < *(u16 *)(header + 0x10));
    }
    return (s32 *)0x0;
}

// 0x710008a130 — Unlinks a node from its doubly-linked list
// Two list types: type 0 uses container+0x150/0x158 as head/tail
// Type != 0 uses an indexed bucket at node+0x548 base, stride 8 by node+0x20 field
// Each node has: prev at +0x80, next at +0x88, type byte at [0]
void FUN_710008a130(s64 container, s8 *node)
{
    s64 next;
    s64 bucket_base;

    if (*node == '\0') {
        next = *(s64 *)(node + 0x88);
        if ((next != 0) && (*(s64 *)(node + 0x80) != 0)) {
            *(s64 *)(next + 0x80) = *(s64 *)(node + 0x80);
            *(u64 *)(*(s64 *)(node + 0x80) + 0x88) = *(u64 *)(node + 0x88);
            return;
        }
        if (*(s8 **)(container + 0x150) == node) {
            *(u64 *)(container + 0x150) = *(u64 *)(node + 0x80);
            next = *(s64 *)(node + 0x80);
            if (next == 0) {
                *(u64 *)(container + 0x158) = 0;
                return;
            }
            goto LAB_710008a204;
        }
        if (*(s8 **)(container + 0x158) != node) {
            return;
        }
        *(s64 *)(container + 0x158) = next;
        next = *(s64 *)(node + 0x88);
        if (next == 0) {
            *(u64 *)(container + 0x150) = 0;
            return;
        }
    }
    else {
        next = *(s64 *)(node + 0x88);
        if ((next != 0) && (*(s64 *)(node + 0x80) != 0)) {
            *(s64 *)(next + 0x80) = *(s64 *)(node + 0x80);
            *(u64 *)(*(s64 *)(node + 0x80) + 0x88) = *(u64 *)(node + 0x88);
            return;
        }
        bucket_base = *(s64 *)(node + 0x548) + (s64)*(s32 *)(node + 0x20) * 8;
        if (*(s8 **)(bucket_base + 0x440) == node) {
            *(u64 *)(bucket_base + 0x440) = *(u64 *)(node + 0x80);
            next = *(s64 *)(node + 0x80);
            if (next == 0) {
                *(u64 *)(bucket_base + 0x4c0) = 0;
                return;
            }
LAB_710008a204:
            *(u64 *)(next + 0x88) = *(u64 *)(node + 0x88);
            return;
        }
        if (*(s8 **)(bucket_base + 0x4c0) != node) {
            return;
        }
        *(s64 *)(bucket_base + 0x4c0) = next;
        next = *(s64 *)(node + 0x88);
        if (next == 0) {
            *(u64 *)(bucket_base + 0x440) = 0;
            return;
        }
    }
    *(u64 *)(next + 0x80) = *(u64 *)(node + 0x80);
}

// 0x710008a3b0 — Walks linked list at +0x150, advances skip_count entries via +0x80 links
void FUN_710008a3b0(s64 container, s32 skip_count)
{
    s64 cursor;

    cursor = *(volatile s64 *)(container + 0x150);
    if ((skip_count != 0) && (cursor != 0)) {
        skip_count = skip_count + -1;
        do {
            cursor = *(volatile s64 *)(cursor + 0x80);
            if (skip_count == 0) {
                return;
            }
            skip_count = skip_count + -1;
        } while (cursor != 0);
    }
}

// 0x7100112c40 — Copies 7 bytes from src+8..+0xf into dst+0x260..+0x267
void FUN_7100112c40(s64 dst, s64 src)
{
    *(u16 *)(dst + 0x260) = *(u16 *)(src + 8);
    *(u8 *)(dst + 0x262) = *(u8 *)(src + 10);
    *(u8 *)(dst + 0x263) = *(u8 *)(src + 0xb);
    *(u8 *)(dst + 0x264) = *(u8 *)(src + 0xc);
    *(u8 *)(dst + 0x265) = *(u8 *)(src + 0xd);
    *(u8 *)(dst + 0x266) = *(u8 *)(src + 0xe);
    *(u8 *)(dst + 0x267) = *(u8 *)(src + 0xf);
}

// 0x71001158e0 — If mode < 2: writes enable flag (bit0 of param_3), mode, and sets dirty bit 0x2000
void FUN_71001158e0(s64 this_ptr, u32 mode, u8 enable)
{
    if (mode < 2) {
        *(u8 *)(this_ptr + 0x14) = enable & 1;
        *(u32 *)(this_ptr + 0x10) = mode;
        *(u32 *)(this_ptr + 0x628) = *(u32 *)(this_ptr + 0x628) | 0x2000;
    }
}

// 0x710011be80 — Returns pointer to array entry (stride 0x268), or null if index > 1
u8 *FUN_710011be80(s64 this_ptr, u8 index)
{
    u8 *entry;

    entry = (u8 *)(this_ptr + 0x11e8) + (u64)index * 0x268;
    if (1 < index) {
        entry = (u8 *)0x0;
    }
    return entry;
}

// 0x710012b490 — Validates param_2 in {1,2}, checks lock, writes state, triggers callback pair
u64 FUN_710012b490(s64 this_ptr, s8 value)
{
    if (1 < (u8)(value - 1U)) {
        return 0;
    }
    if (*(s32 *)(this_ptr + 0xd88) == 1) {
        return 0;
    }
    *(u8 *)(this_ptr + 0xd81) = 1;
    *(s8 *)(this_ptr + 0xd80) = value;
    FUN_71000b40e0(this_ptr + 0xd88);
    FUN_71000b4160(this_ptr + 0xd88);
    return 1;
}

// 0x7100130aa0 — Inserts new_node before the current head of doubly-linked list at container+8
void FUN_7100130aa0(s64 container, s64 *new_node)
{
    u64 *old_head;

    old_head = *(u64 **)(container + 8);
    *(s64 **)(container + 8) = new_node;
    *new_node = container;
    new_node[1] = (s64)old_head;
    if (old_head != (u64 *)0x0) {
        *old_head = (u64)new_node;
    }
}

// 0x71001354c0 — Popcount (Hamming weight) of lower 32 bits via bit-parallel sum
u32 FUN_71001354c0(u64 val)
{
    u32 x;

    x = (s32)val - ((u32)(val >> 1) & 0x55555555);
    x = (x >> 2 & 0x33333333) + (x & 0x33333333);
    x = x + (x >> 4) & 0xf0f0f0f;
    x = x + (x >> 8);
    return x + (x >> 0x10) & 0x3f;
}

// 0x71000b3c70 — Returns DAT_7104f49390 / DAT_7104f49388, or 0 if denominator is zero
u64 FUN_71000b3c70(void)
{
    u64 result;

    if (DAT_7104f49388 != 0) {
        result = 0;
        if ((u64)DAT_7104f49388 != 0) {
            result = DAT_7104f49390 / DAT_7104f49388;
        }
        return result;
    }
    return 0;
}

// 0x71000b3d10 — Returns DAT_7104f49430 / DAT_7104f49428, or 0 if denominator is zero
u64 FUN_71000b3d10(void)
{
    u64 result;

    if (DAT_7104f49428 != 0) {
        result = 0;
        if ((u64)DAT_7104f49428 != 0) {
            result = DAT_7104f49430 / DAT_7104f49428;
        }
        return result;
    }
    return 0;
}
