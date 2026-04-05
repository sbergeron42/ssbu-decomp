#include "types.h"

// MEDIUM-tier FUN_* functions — mixed 0x7100 ranges, batch d4-016
// Pool-d worker: auto-generated from Ghidra decompilation
// Includes: list ops, struct inits, memcpy group, UTF-8 counter, table lookups, nn::os

// ---- External declarations -----------------------------------------------

#pragma GCC visibility push(hidden)
extern s64 *PTR_DAT_71052a3bc0; // base for FUN_71000af810
extern u64 PTR_DAT_71052a3c18;  // array base for FUN_71000b1b50
extern s64 DAT_7104492890;      // index table for FUN_71000b1b50
extern u64 PTR_DAT_71052a3c10;  // u32* target for FUN_71000b1bb0
extern u8 DAT_7104492960;       // index table for FUN_71000b1bb0
extern u8 *PTR_DAT_71052a3d28;  // vtable base for FUN_71000bed20
extern u8 *PTR_DAT_71052a3ee8;  // vtable base for FUN_71000cf5c0
extern s64 *PTR_DAT_71052a4080; // global ptr for FUN_71000ee650
#pragma GCC visibility pop

extern "C" void *memcpy(void *, const void *, u64);

namespace nn { namespace os {
    struct ThreadType;
    void StartThread(ThreadType *);
}}

// ---- Functions ---------------------------------------------------------------

// 0x7100078b00 — doubly-linked list splice: insert self+0x38 node after target+0x48
void FUN_7100078b00(s64 self, s64 target)
{
    s64 *src_node;
    s64 *dst_node;
    s64 prev_head;

    dst_node = (s64 *)(target + 0x48);
    prev_head = *dst_node;
    src_node = (s64 *)(self + 0x38);
    *dst_node = *src_node;
    *(s64 **)(prev_head + 8) = src_node;
    *(s64 **)(*src_node + 8) = dst_node;
    *src_node = prev_head;
}

// 0x71000887d0 — cycling counter: advance slot index modulo 2 or 3 (based on flag)
u64 FUN_71000887d0(s64 self, s32 mode)
{
    s32 next_index;
    u32 slot_index;
    s32 quotient;
    s32 num_slots;

    if (mode == 2) {
        if ((*(s8 *)(self + 9) == '\0') && (*(s8 *)(self + 10) == '\0')) {
            return 0;
        }
    }
    else if (mode != 1) {
        return 0;
    }
    *(u16 *)(self + 9) = 0;
    next_index = *(s32 *)(self + 0x30) + 1;
    num_slots = 2;
    if (*(s8 *)(*(s64 *)(*(s64 *)(self + 0x78) + 0x20) + 0x36) != '\0') {
        num_slots = 3;
    }
    quotient = next_index / num_slots;
    slot_index = next_index - quotient * num_slots;
    *(u32 *)(self + 0x30) = slot_index;
    *(u64 *)(self + 0xc0) = self + (u64)slot_index * 0x58 + 200;
    return 1;
}

// 0x710008d670 — bulk memcpy: copy up to 11 channel buffers from source to dest_bufs array
void FUN_710008d670(u64 unused, s64 source)
{
    u64 copy_size;
    u64 *dest_bufs;

    if (*(s8 *)(*(s64 *)(source + 0xa0) + 0x752) == '\0') {
        dest_bufs = *(u64 **)(source + 0xc0);
        copy_size = (u64)((s64)*(s32 *)(source + 0x28) << 4);
        memcpy((void *)dest_bufs[0], *(void **)(source + 0x1d0), copy_size);
        memcpy((void *)dest_bufs[1], *(void **)(source + 0x1d8), copy_size);
        memcpy((void *)dest_bufs[2], *(void **)(source + 0x1e0), copy_size);
        memcpy((void *)dest_bufs[4], *(void **)(source + 0x1f0), copy_size);
        memcpy((void *)dest_bufs[3], *(void **)(source + 0x1e8), copy_size);
        memcpy((void *)dest_bufs[5], *(void **)(source + 0x1f8), copy_size);
        if ((void *)dest_bufs[6] != (void *)0x0) {
            memcpy((void *)dest_bufs[6], *(void **)(source + 0x200), copy_size);
            memcpy((void *)dest_bufs[7], *(void **)(source + 0x208), copy_size);
        }
        if ((void *)dest_bufs[8] != (void *)0x0) {
            memcpy((void *)dest_bufs[8], *(void **)(source + 0x210), copy_size);
            memcpy((void *)dest_bufs[9], *(void **)(source + 0x218), copy_size);
            memcpy((void *)dest_bufs[10], *(void **)(source + 0x220), copy_size);
        }
    }
}

// 0x71000af810 — indexed lookup: PTR_DAT_71052a3bc0 base + packed byte index * 0xa8
s64 FUN_71000af810(s64 self)
{
    return *PTR_DAT_71052a3bc0 +
           ((u64)*(u8 *)(self + 9) + (u64)*(u8 *)(self + 8) * 4 +
           (u64)*(u8 *)(self + 10) * 0x10) * 0xa8;
}

// 0x71000b1b50 — double-indexed lookup: table DAT_7104492890 → array at PTR_DAT_71052a3c18
u64 FUN_71000b1b50(s32 type_id)
{
    if ((u32)(type_id - 2) < 0x19) {
        return *(u64 *)(PTR_DAT_71052a3c18 +
               *(s64 *)(&DAT_7104492890 + (s64)(s32)((u32)type_id - 2) * 8) * 8);
    }
    return *(u64 *)(PTR_DAT_71052a3c18 + 200);
}

// 0x71000b1bb0 — write indexed u32 from DAT_7104492960 to *(u32*)PTR_DAT_71052a3c10
void FUN_71000b1bb0(s32 type_id)
{
    if ((u32)(type_id - 2) < 0x19) {
        *(u32 *)PTR_DAT_71052a3c10 =
            *(u32 *)(&DAT_7104492960 + (s64)(s32)((u32)type_id - 2) * 4);
        return;
    }
    *(u32 *)PTR_DAT_71052a3c10 = 0x19;
}

// 0x71000bb050 — count UTF-8 characters in string within bounds, handling multi-byte sequences
u32 FUN_71000bb050(s64 self)
{
    u32 final_count;
    u32 byte_length;
    u8 cur_byte;
    u32 char_count;
    u8 *str_base;
    u8 *cursor;
    u32 seq_len;
    u32 advance;

    str_base = *(u8 **)(self + 8);
    if (str_base == (u8 *)0x0) {
        return 0;
    }
    byte_length = *(u32 *)(self + 0x14);
    if (byte_length != 0) {
        if (*(s32 *)(self + 0x18) != 1) {
            char_count = 0;
            if (*(s32 *)(self + 0x18) == 2) {
                char_count = byte_length >> 1;
            }
            return char_count;
        }
        char_count = 0;
        cursor = str_base;
        while (true) {
            cur_byte = *cursor;
            if (cur_byte == 0) {
                return char_count;
            }
            if ((s64)(u64)byte_length <= (s64)cursor - (s64)str_base) break;
            if ((s8)cur_byte < '\0') {
                advance = (u32)(s8)cur_byte;
                if (advance + 0x3e < 0x1e) {
                    seq_len = 2;
                }
                else if ((advance & 0xfffffff0) == 0xffffffe0) {
                    seq_len = 3;
                }
                else if ((advance & 0xfffffff8) == 0xfffffff0) {
                    seq_len = 4;
                }
                else {
                    seq_len = 5;
                    if (((advance & 0xfffffffc) != 0xfffffff8) && (seq_len = 6, (cur_byte & 0xfe) != 0xfc)) {
                        seq_len = 0;
                    }
                }
            }
            else {
                seq_len = 1;
            }
            advance = seq_len;
            if (seq_len == 0) {
                advance = 1;
            }
            final_count = char_count;
            if (seq_len != 0) {
                final_count = char_count + 1;
            }
            char_count = char_count + 1;
            cursor = cursor + advance;
            if (seq_len == 0) {
                return final_count;
            }
        }
        return char_count;
    }
    return 0;
}

// 0x71000bed20 — init s64* struct: zero [2], store PTR_DAT_71052a3d28+0x10 as vtable
void FUN_71000bed20(s64 *self)
{
    u8 *vtable_base;

    vtable_base = PTR_DAT_71052a3d28;
    self[2] = 0;
    *self = (s64)(vtable_base + 0x10);
}

// 0x71000bf2f0 — validate: check magic+flag at +8/+0xc, then range-check field +0x5e8
u8 FUN_71000bf2f0(s64 self)
{
    if ((*(s32 *)(self + 8) == 0x32ab9864) && ((*(u8 *)(self + 0xc) & 0x7f) == 4)) {
        return (u32)(*(s32 *)(self + 0x5e8)) - 0x20U < 0x5a1;
    }
    return 0;
}

// 0x71000c4d40 — vtable call +0x28 on *(self+0x50): return null on failure, 1 on success
s64 *FUN_71000c4d40(s64 self)
{
    s64 *obj;
    u64 result;

    obj = *(s64 **)(self + 0x50);
    if (obj != (s64 *)0x0) {
        result = (*(u64(**)(void))(*obj + 0x28))();
        if ((result & 1) == 0) {
            return (s64 *)0x0;
        }
        obj = (s64 *)0x1;
        *(u64 *)(self + 0xc0) = 0;
    }
    return obj;
}

// 0x71000cf5c0 — init s64* struct: zero fields, store PTR_DAT_71052a3ee8+0x10 as vtable
void FUN_71000cf5c0(s64 *self)
{
    u8 *vtable_base;

    vtable_base = PTR_DAT_71052a3ee8;
    *(u32 *)(self + 1) = 0;
    *(u8 *)((s64)self + 0xc) = 0;
    self[2] = 0;
    *self = (s64)(vtable_base + 0x10);
    *(u32 *)(self + 3) = 0;
}

// 0x71000e4340 — map input: 0->1, 1->2, else->0
s32 FUN_71000e4340(s32 input)
{
    s32 mapped;

    mapped = (u32)(input == 1) << 1;
    if (input == 0) {
        mapped = 1;
    }
    return mapped;
}

// 0x71000ee650 — count valid linked-list entries matching category across four dispatch paths
s32 FUN_71000ee650(s64 self, s32 category)
{
    s32 count;
    s64 data;
    s32 *list_end;
    s32 *entry;

    data = *(s64 *)(self + 0x2d8);
    if (data == 0 || *PTR_DAT_71052a4080 == 0) {
        return 0;
    }
    entry = (s32 *)(data + 0x10);
    if (*entry != category) {
        if (*(s32 *)(data + 0x658) != category) {
            if (*(s32 *)(data + 0xca0) == category) {
                list_end = (s32 *)(data + 0xca8);
                entry = *(s32 **)(data + 0xcb0);
                if (entry == list_end) {
                    return 0;
                }
            }
            else {
                if (*(s32 *)(data + 0x12e8) != category) {
                    return 0;
                }
                list_end = (s32 *)(data + 0x12f0);
                entry = *(s32 **)(data + 0x12f8);
                if (entry == list_end) {
                    return 0;
                }
            }
            goto LAB_71000ee6a4;
        }
        entry = (s32 *)(data + 0x658);
    }
    list_end = entry + 2;
    entry = *(s32 **)(entry + 4);
    if (entry == list_end) {
        return 0;
    }
LAB_71000ee6a4:
    count = 0;
    do {
        if (((*(s64 *)(entry + 4) != 0) && (*(s64 *)(entry + 4) == *(s64 *)(entry + 6))) &&
           (0 < *(s16 *)((s64)entry + 0x22))) {
            count = count + 1;
        }
        entry = *(s32 **)(entry + 2);
    } while (entry != list_end);
    return count;
}
