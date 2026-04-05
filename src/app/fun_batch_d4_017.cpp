#include "types.h"

// MEDIUM-tier FUN_* functions — mixed 0x7100 ranges, batch d4-017
// Pool-d worker: auto-generated from Ghidra decompilation
// Includes: string switch, error code switch, bit-field ops, vtable dispatch loops, singleton guards

#define HIDDEN __attribute__((visibility("hidden")))

// ---- External declarations -----------------------------------------------

// DAT small-addr globals (used as base for pointer arithmetic)
extern s8 DAT_00005920;

// FUN_71001e1770 helper
extern "C" void FUN_71001b4200(u64 *, u32 *);

// FUN_710047cda0 helper + data
extern u8 DAT_71050b33c8;
extern "C" void FUN_7100489b00(s64, s64, u8 **, u8);

// FUN_710067e670 helper
extern "C" void FUN_710065d450(s64, s32, s32);

// FUN_710064c290 vtable label
extern u64 PTR_LAB_7104f7fe70 HIDDEN;

// FUN_710068d530 table + singleton globals
extern u64 PTR_PTR_710529bfd0;
extern u64 DAT_71052b8800;
extern u64 DAT_71052b8808;
extern u64 PTR_LAB_7104f83b18;

// __cxa_guard
extern "C" s32 __cxa_guard_acquire(u64 *);
extern "C" void __cxa_guard_release(u64 *);

// ---- Functions ---------------------------------------------------------------

// 0x71001e1770 — map error code to Result constant; default: copy src into dst
void FUN_71001e1770(u64 *dst, u32 error_type, u64 *src)
{
    u64 first;
    u64 third;
    u32 result_code;

    switch (error_type) {
    case 8:
        result_code = 0x8068000b;
        break;
    case 10:
        result_code = 0x80680011;
        break;
    case 0xb:
        result_code = 0x80680013;
        break;
    case 0xc:
        result_code = 0x80680014;
        break;
    case 0xd:
        result_code = 0x800300e2;
        break;
    case 0xe:
        result_code = 0x8003006c;
        break;
    default:
        first = *src;
        third = src[2];
        dst[1] = src[1];
        dst[2] = third;
        *dst = first;
        return;
    }
    FUN_71001b4200(dst, &result_code);
}

// 0x7100460760 — state machine: set phase, update sub-state and flags
void FUN_7100460760(s64 self, u32 phase)
{
    s64 pos_a;
    s64 data;
    u32 sub_state;

    *(u32 *)(self + 0x40) = phase;
    switch (phase) {
    case 0:
        *(u32 *)(*(s64 *)(self + 0x28) + 0x510) = 4;
        break;
    case 1:
        *(u32 *)(*(s64 *)(self + 0x28) + 0x510) = 0;
        goto LAB_7100460830;
    case 2:
        data = *(s64 *)(self + 0x28);
        sub_state = 2;
        goto LAB_710046082c;
    case 3:
        pos_a = (*(s64 (**)(void))(*(s64 *)(*(s64 *)(self + 0x20) + 0x38) + 0x60))();
        data = (*(s64 (**)(void))(*(s64 *)(*(s64 *)(self + 0x20) + 0x38) + 0x90))();
        if (*(float *)(pos_a + 4) < *(float *)(data + 4)) {
            *(u32 *)(*(s64 *)(self + 0x28) + 0x510) = 0;
        }
        break;
    case 4:
        *(u32 *)(*(s64 *)(self + 0x28) + 0x510) = 2;
        break;
    case 5:
        *(u32 *)(*(s64 *)(self + 0x28) + 0x510) = 1;
        break;
    case 6:
        data = *(s64 *)(self + 0x28);
        sub_state = 3;
LAB_710046082c:
        *(u32 *)(data + 0x510) = sub_state;
LAB_7100460830:
        *(u32 *)(*(s64 *)(self + 0x28) + 0x5d8) =
            *(u32 *)(*(s64 *)(self + 0x28) + 0x5d8) | 2;
        break;
    }
}

// 0x7100479f70 — dispatch vtable +0x10 for each non-null entry with matching mask or 0xffffffff
void FUN_7100479f70(s64 self, u32 mask)
{
    s32 count;
    s64 *entry;
    s64 remaining;
    s64 *cursor;

    if (*(s8 *)(self + 0x1bc) == '\0') {
        count = *(s32 *)(self + 0x20);
        if (mask == 0xffffffff) {
            if (0 < count) {
                remaining = (s64)count + 1;
                cursor = (s64 *)(self + (s64)count * 0x18 + 0x18);
                do {
                    entry = (s64 *)*cursor;
                    if (((s8)entry[6] != '\0') && (*(s8 *)((s64)entry + 0x31) == '\0')) {
                        (*(void(**)(s64 *, u64))(*entry + 0x10))(entry, *(u64 *)(self + 8));
                    }
                    remaining = remaining + -1;
                    cursor = cursor + -3;
                } while (1 < remaining);
            }
        } else if (0 < count) {
            remaining = (s64)count + 1;
            cursor = (s64 *)(self + (s64)count * 0x18 + 0x18);
            do {
                if ((((*(u32 *)((s64)cursor + 0xc) & mask) != 0) &&
                    (entry = (s64 *)*cursor, (s8)entry[6] != '\0')) &&
                   (*(s8 *)((s64)entry + 0x31) == '\0')) {
                    (*(void(**)(s64 *, u64))(*entry + 0x10))(entry, *(u64 *)(self + 8));
                }
                remaining = remaining + -1;
                cursor = cursor + -3;
            } while (1 < remaining);
        }
    }
}

// 0x710047a060 — dispatch vtable +0x18 for each non-null entry with matching mask or 0xffffffff
void FUN_710047a060(s64 self, u32 mask)
{
    s32 count;
    s64 *entry;
    s64 remaining;
    s64 *cursor;

    if (*(s8 *)(self + 0x1bc) == '\0') {
        count = *(s32 *)(self + 0x20);
        if (mask == 0xffffffff) {
            if (0 < count) {
                remaining = (s64)count + 1;
                cursor = (s64 *)(self + (s64)count * 0x18 + 0x18);
                do {
                    entry = (s64 *)*cursor;
                    if (((s8)entry[6] != '\0') && (*(s8 *)((s64)entry + 0x31) == '\0')) {
                        (*(void(**)(s64 *, u64))(*entry + 0x18))(entry, *(u64 *)(self + 8));
                    }
                    remaining = remaining + -1;
                    cursor = cursor + -3;
                } while (1 < remaining);
            }
        } else if (0 < count) {
            remaining = (s64)count + 1;
            cursor = (s64 *)(self + (s64)count * 0x18 + 0x18);
            do {
                if ((((*(u32 *)((s64)cursor + 0xc) & mask) != 0) &&
                    (entry = (s64 *)*cursor, (s8)entry[6] != '\0')) &&
                   (*(s8 *)((s64)entry + 0x31) == '\0')) {
                    (*(void(**)(s64 *, u64))(*entry + 0x18))(entry, *(u64 *)(self + 8));
                }
                remaining = remaining + -1;
                cursor = cursor + -3;
            } while (1 < remaining);
        }
    }
}

// 0x710047cda0 — find matching node by key, fill link fields, link into lists
s64 FUN_710047cda0(s64 table, s64 owner, s32 key, s64 link)
{
    u64 *link_node;
    u32 owner_id;
    s64 match;
    s64 *iter;
    u64 tail;
    u8 *local_40;
    u32 local_38;
    u64 local_30;
    u64 uStack_28;
    u64 local_20;
    u8 local_18;

    if (*(s32 *)(table + 0x18) == 0) {
        return 0;
    }
    iter = *(s64 **)(table + 8);
    if (iter != (s64 *)0x0) {
        do {
            match = iter[2];
            if (*(s32 *)(*(s64 *)(match + 8) + 8) == key) {
                if (match != 0) {
                    owner_id = *(u32 *)(*(s64 *)(owner + 8) + 8);
                    *(s64 *)(link + 0x30) = owner;
                    *(s32 *)(link + 0x48) = key;
                    *(s64 *)(link + 0x58) = match;
                    *(u8 *)(link + 0x65) = 1;
                    *(u32 *)(link + 0x20) = owner_id;
                    link_node = (u64 *)(link + 0x38);
                    if (*(s32 *)(owner + 0x48) == 0) {
                        if (*(s64 *)(owner + 0x38) != 0) {
                            *(u64 **)(*(s64 *)(owner + 0x38) + 8) = link_node;
                            *link_node = *(u64 *)(owner + 0x38);
                        }
                        *(u64 **)(owner + 0x38) = link_node;
                    } else {
                        tail = *(u64 *)(owner + 0x40);
                        *(u64 *)(link + 0x38) = 0;
                        *(u64 *)(link + 0x40) = tail;
                        **(s64 **)(owner + 0x40) = (s64)link_node;
                    }
                    *(u64 **)(owner + 0x40) = link_node;
                    *(s32 *)(owner + 0x48) = *(s32 *)(owner + 0x48) + 1;
                    link_node = (u64 *)(link + 0x10);
                    if (*(s32 *)(match + 0x30) == 0) {
                        if (*(s64 *)(match + 0x20) != 0) {
                            *(u64 **)(*(s64 *)(match + 0x20) + 8) = link_node;
                            *link_node = *(u64 *)(match + 0x20);
                        }
                        *(u64 **)(match + 0x20) = link_node;
                    } else {
                        tail = *(u64 *)(match + 0x28);
                        *(u64 *)(link + 0x10) = 0;
                        *(u64 *)(link + 0x18) = tail;
                        **(s64 **)(match + 0x28) = (s64)link_node;
                    }
                    *(u64 **)(match + 0x28) = link_node;
                    *(s32 *)(match + 0x30) = *(s32 *)(match + 0x30) + 1;
                    local_38 = 10;
                    local_30 = 0xbcd988648ULL;
                    uStack_28 = 0;
                    local_40 = &DAT_71050b33c8;
                    local_18 = 0;
                    local_20 = 0xffffffff50000000ULL;
                    FUN_7100489b00(match, owner, &local_40, *(u8 *)(link + 100));
                    match = 1;
                }
                return match;
            }
            iter = (s64 *)*iter;
        } while (iter != (s64 *)0x0);
        return 0;
    }
    return 0;
}

// 0x71004c16f0 — write value into bit-field at bit position determined by field_index
void FUN_71004c16f0(s32 guard, u32 field_index, u32 value, s64 entry)
{
    u32 packed;

    if ((entry != 0) && (guard != 0)) {
        switch (field_index) {
        case 0:
            packed = *(u32 *)(entry + 0xc) & 0xffffff80 | value & 0x7f;
            break;
        case 1:
            packed = *(u32 *)(entry + 0xc) & 0xffffe000 |
                    *(u32 *)(entry + 0xc) & 0x7f | (value & 0x3f) << 7;
            break;
        case 2:
            packed = *(u32 *)(entry + 0xc) & 0xffff0000 |
                    *(u32 *)(entry + 0xc) & 0x1fff | (value & 7) << 0xd;
            break;
        case 3:
            packed = *(u32 *)(entry + 0xc) & 0xffe00000 |
                    *(u32 *)(entry + 0xc) & 0xffff | (value & 0x1f) << 0x10;
            break;
        case 4:
            packed = *(u32 *)(entry + 0xc) & 0xff000000 |
                    *(u32 *)(entry + 0xc) & 0x1fffff | (value & 7) << 0x15;
            break;
        case 5:
            packed = *(u32 *)(entry + 0xc) & 0xf8000000 |
                    *(u32 *)(entry + 0xc) & 0xffffff | (value & 7) << 0x18;
            break;
        case 6:
            packed = *(u32 *)(entry + 0xc) & 0xe0000000 |
                    *(u32 *)(entry + 0xc) & 0x7ffffff | (value & 3) << 0x1b;
            break;
        case 7:
            packed = *(u32 *)(entry + 0xc) & 0x1fffffff | value << 0x1d;
            break;
        default:
            return;
        }
        *(u32 *)(entry + 0xc) = packed;
    }
}

// 0x710064c290 — write vtable label ptr + self+8 field into dst[0..1]
void FUN_710064c290(s64 self, u64 *dst)
{
    *dst = (u64)&PTR_LAB_7104f7fe70;
    dst[1] = *(u64 *)(self + 8);
}

// 0x710065dcc0 — map opcode pair: remap certain (opcode, -1) or (0x4b, 0x4c) combos
u32 FUN_710065dcc0(u32 *opcodes)
{
    switch (*opcodes) {
    case 0x24:
        if (opcodes[1] == (u32)-1) {
            return 0x6f;
        }
        break;
    case 0x25:
        if (opcodes[1] == (u32)-1) {
            return 0x70;
        }
        break;
    case 0x26:
        if (opcodes[1] == (u32)-1) {
            return 0x71;
        }
        break;
    case 0x4b:
        if (opcodes[1] == 0x4c) {
            return 0x6e;
        }
        break;
    case 0x5a:
        if (opcodes[1] == (u32)-1) {
            return 0x73;
        }
        break;
    case 0x5b:
        if (opcodes[1] == (u32)-1) {
            return 0x74;
        }
        break;
    }
    return *opcodes;
}

// 0x710065dd70 — return 1 if opcode is one of the recognized values, else 0
u64 FUN_710065dd70(u32 opcode)
{
    switch (opcode) {
    case 5:
    case 7:
    case 0xb:
    case 0x14:
    case 0x21:
    case 0x2a:
    case 0x2f:
    case 0x31:
    case 0x39:
    case 0x3b:
    case 0x3f:
    case 0x40:
    case 0x42:
    case 0x43:
    case 0x44:
    case 0x45:
    case 0x47:
    case 0x52:
    case 0x53:
    case 0x54:
    case 0x55:
    case 0x56:
    case 0x57:
    case 0x58:
    case 0x59:
    case 0x5a:
    case 0x5b:
    case 0x5c:
    case 0x5d:
    case 0x75:
        return 1;
    default:
        return 0;
    }
}

// 0x710067a3a0 — check if any of 8 slot ptrs is active (type==3+flag or state>1); u8 return
u8 FUN_710067a3a0(s64 self, u32 check_slots)
{
    s64 slot;

    if ((check_slots & 1) == 0) {
        return '\0' < *(s8 *)(self + 0xbc);
    }
    slot = *(s64 *)(self + 0x20);
    if (slot != 0) {
        if (((&DAT_00005920)[slot] == '\x03') && (*(s8 *)(slot + 0x44d2) != '\0')) {
            return 1;
        }
        if (*(s8 *)(slot + 0x5921) != '\0') {
            return 1;
        }
    }
    slot = *(s64 *)(self + 0x28);
    if (slot != 0) {
        if (((&DAT_00005920)[slot] == '\x03') && (*(s8 *)(slot + 0x44d2) != '\0')) {
            return 1;
        }
        if (*(s8 *)(slot + 0x5921) != '\0') {
            return 1;
        }
    }
    slot = *(s64 *)(self + 0x30);
    if (slot != 0) {
        if (((&DAT_00005920)[slot] == '\x03') && (*(s8 *)(slot + 0x44d2) != '\0')) {
            return 1;
        }
        if (*(s8 *)(slot + 0x5921) != '\0') {
            return 1;
        }
    }
    slot = *(s64 *)(self + 0x38);
    if (slot != 0) {
        if (((&DAT_00005920)[slot] == '\x03') && (*(s8 *)(slot + 0x44d2) != '\0')) {
            return 1;
        }
        if (*(s8 *)(slot + 0x5921) != '\0') {
            return 1;
        }
    }
    slot = *(s64 *)(self + 0x40);
    if (slot != 0) {
        if (((&DAT_00005920)[slot] == '\x03') && (*(s8 *)(slot + 0x44d2) != '\0')) {
            return 1;
        }
        if (*(s8 *)(slot + 0x5921) != '\0') {
            return 1;
        }
    }
    slot = *(s64 *)(self + 0x48);
    if (slot != 0) {
        if (((&DAT_00005920)[slot] == '\x03') && (*(s8 *)(slot + 0x44d2) != '\0')) {
            return 1;
        }
        if (*(s8 *)(slot + 0x5921) != '\0') {
            return 1;
        }
    }
    slot = *(s64 *)(self + 0x50);
    if (slot != 0) {
        if (((&DAT_00005920)[slot] == '\x03') && (*(s8 *)(slot + 0x44d2) != '\0')) {
            return 1;
        }
        if (*(s8 *)(slot + 0x5921) != '\0') {
            return 1;
        }
    }
    slot = *(s64 *)(self + 0x58);
    if (slot != 0) {
        if (((&DAT_00005920)[slot] == '\x03') && (*(s8 *)(slot + 0x44d2) != '\0')) {
            return 1;
        }
        if (*(s8 *)(slot + 0x5921) != '\0') {
            return 1;
        }
    }
    return 0;
}

// 0x710067a5c0 — check if any of 8 slot ptrs has (type!=3 or no flag) and state>1; u64 return
u64 FUN_710067a5c0(s64 self)
{
    s64 slot;

    slot = *(s64 *)(self + 0x20);
    if ((slot != 0) &&
       ((((&DAT_00005920)[slot] != '\x03' || (*(s8 *)(slot + 0x44d2) == '\0')) &&
        (1 < *(u8 *)(slot + 0x5921))))) {
        return 1;
    }
    slot = *(s64 *)(self + 0x28);
    if ((slot != 0) &&
       ((((&DAT_00005920)[slot] != '\x03' || (*(s8 *)(slot + 0x44d2) == '\0')) &&
        (1 < *(u8 *)(slot + 0x5921))))) {
        return 1;
    }
    slot = *(s64 *)(self + 0x30);
    if (((slot != 0) && (((&DAT_00005920)[slot] != '\x03' || (*(s8 *)(slot + 0x44d2) == '\0'))))
       && (1 < *(u8 *)(slot + 0x5921))) {
        return 1;
    }
    slot = *(s64 *)(self + 0x38);
    if ((slot != 0) &&
       ((((&DAT_00005920)[slot] != '\x03' || (*(s8 *)(slot + 0x44d2) == '\0')) &&
        (1 < *(u8 *)(slot + 0x5921))))) {
        return 1;
    }
    slot = *(s64 *)(self + 0x40);
    if ((slot != 0) &&
       ((((&DAT_00005920)[slot] != '\x03' || (*(s8 *)(slot + 0x44d2) == '\0')) &&
        (1 < *(u8 *)(slot + 0x5921))))) {
        return 1;
    }
    slot = *(s64 *)(self + 0x48);
    if (((slot != 0) && (((&DAT_00005920)[slot] != '\x03' || (*(s8 *)(slot + 0x44d2) == '\0'))))
       && (1 < *(u8 *)(slot + 0x5921))) {
        return 1;
    }
    slot = *(s64 *)(self + 0x50);
    if ((slot != 0) &&
       ((((&DAT_00005920)[slot] != '\x03' || (*(s8 *)(slot + 0x44d2) == '\0')) &&
        (1 < *(u8 *)(slot + 0x5921))))) {
        return 1;
    }
    slot = *(s64 *)(self + 0x58);
    if (((slot != 0) && (((&DAT_00005920)[slot] != '\x03' || (*(s8 *)(slot + 0x44d2) == '\0'))))
       && (1 < *(u8 *)(slot + 0x5921))) {
        return 1;
    }
    return 0;
}

// 0x710067e670 — dispatch FUN_710065d450 to each of 8 slot ptrs if condition met
void FUN_710067e670(s64 self, s32 source_id, s32 action)
{
    s64 slot;

    if (((action != 6) && (3 < (u32)(action - 0x4d))) && (-1 < action)) {
        slot = *(s64 *)(self + 0x20);
        if ((slot != 0) && (*(s32 *)(slot + 0xe0) != source_id)) {
            FUN_710065d450(slot, action, source_id);
        }
        slot = *(s64 *)(self + 0x28);
        if ((slot != 0) && (*(s32 *)(slot + 0xe0) != source_id)) {
            FUN_710065d450(slot, action, source_id);
        }
        slot = *(s64 *)(self + 0x30);
        if ((slot != 0) && (*(s32 *)(slot + 0xe0) != source_id)) {
            FUN_710065d450(slot, action, source_id);
        }
        slot = *(s64 *)(self + 0x38);
        if ((slot != 0) && (*(s32 *)(slot + 0xe0) != source_id)) {
            FUN_710065d450(slot, action, source_id);
        }
        slot = *(s64 *)(self + 0x40);
        if ((slot != 0) && (*(s32 *)(slot + 0xe0) != source_id)) {
            FUN_710065d450(slot, action, source_id);
        }
        slot = *(s64 *)(self + 0x48);
        if ((slot != 0) && (*(s32 *)(slot + 0xe0) != source_id)) {
            FUN_710065d450(slot, action, source_id);
        }
        slot = *(s64 *)(self + 0x50);
        if ((slot != 0) && (*(s32 *)(slot + 0xe0) != source_id)) {
            FUN_710065d450(slot, action, source_id);
        }
        slot = *(s64 *)(self + 0x58);
        if ((slot != 0) && (*(s32 *)(slot + 0xe0) != source_id)) {
            FUN_710065d450(slot, action, source_id);
        }
    }
}

// 0x710068d530 — table lookup for index < 0x5e, else singleton guard init; return u64*
u64 *FUN_710068d530(u32 index)
{
    s32 acquired;

    if (index < 0x5e) {
        return (u64 *)(&PTR_PTR_710529bfd0)[(s32)index];
    }
    if (((DAT_71052b8800 & 1) == 0) && (acquired = __cxa_guard_acquire(&DAT_71052b8800), acquired != 0)) {
        DAT_71052b8808 = (u64)&PTR_LAB_7104f83b18;
        __cxa_guard_release(&DAT_71052b8800);
    }
    return &DAT_71052b8808;
}
