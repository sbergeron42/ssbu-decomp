#include "types.h"
// FighterManager.h — struct layout used for derivation chains in slot functions below
// Struct access not used directly due to void*-to-s64 cast breaking matching
// #include "app/FighterManager.h"

// MEDIUM-tier FUN_* functions — mixed 0x7100 ranges, batch d4-017
// Includes: string switch, error code switch, bit-field ops, vtable dispatch loops, singleton guards
// FighterManager slot functions derived from Ghidra xref to is_final_status_or_standby (.dynsym)

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

// 0x71001e1770 — map nn::Result error_type to SDK error code; default: copy src into dst
// Error codes: 0x8068000b (type 8), 0x80680011 (10), 0x80680013 (0xb), 0x80680014 (0xc),
//              0x800300e2 (0xd), 0x8003006c (0xe)
// [inferred: nn::nifm or nn::socket error translation — 0x806800xx = network module errors]
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
// self [unknown: AI/camera controller struct — vtable DATA refs at 7104f6cac8, 7104f86778, etc.]
// +0x20 [unknown: sub-object with vtable at *(+0x38)]
//   vtable+0x60 [inferred: get_position — returns ptr with float y at +4]
//   vtable+0x90 [inferred: get_target_position — returns ptr with float y at +4]
// +0x28 [unknown: data/state pointer]
//   +0x510 [unknown: phase sub-state field, set to 0..4 per phase]
//   +0x5D8 [unknown: flags field, bit 1 set on phase transitions 1/2/6]
// +0x40 [unknown: current phase, written directly from param]
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
        // Compare y-positions from two vtable calls on sub-object at +0x20
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
        // Set bit 1 in flags at +0x5D8 (marks state transition)
        *(u32 *)(*(s64 *)(self + 0x28) + 0x5d8) =
            *(u32 *)(*(s64 *)(self + 0x28) + 0x5d8) | 2;
        break;
    }
}

// 0x7100479f70 — dispatch vtable+0x10 for each entry with matching mask (event broadcast)
// self [unknown: event dispatch table struct]
//   +0x08 [unknown: context/owner value passed as arg to dispatched callbacks]
//   +0x20 [unknown: entry count (s32)]
//   +0x1BC [unknown: disabled flag — if nonzero, skip all dispatch]
//   +0x30 [unknown: start of entry array, stride 0x18 per slot]
//     slot+0x00 [unknown: entry pointer]
//     slot+0x0C [unknown: mask field (u32), AND'd with param mask for filtering]
// entry struct (pointed to by slot+0x00):
//   +0x00 [unknown: vtable pointer]
//   +0x30 [unknown: enabled flag (s8), must be nonzero]
//   +0x31 [unknown: suppress flag (s8), must be zero for dispatch]
//   vtable+0x10 [unknown: callback — called with (entry, context)]
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

// 0x710047a060 — dispatch vtable+0x18 for each entry with matching mask (event broadcast)
// Same dispatch table struct as FUN_7100479f70 but calls vtable+0x18 instead of +0x10
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

// 0x710047cda0 — find matching node by key, fill link fields, link into owner+match lists
// table [unknown: linked list container]
//   +0x08 [unknown: head pointer of node list]
//   +0x18 [unknown: node count; returns 0 if empty]
// node (iterated via +0x00 = next pointer):
//   +0x10 [unknown: data pointer to match candidate]
//     match+0x08 → key container [unknown: match->*(+8)+8 compared with key param]
// owner [unknown: object that "owns" the link]
//   +0x08 [unknown: pointer to ID container; *(+8)+8 = owner_id]
//   +0x38/+0x40/+0x48 [unknown: doubly-linked list (head/tail/count) of owned links]
// match [unknown: matched node data]
//   +0x20/+0x28/+0x30 [unknown: doubly-linked list (head/tail/count) of match's links]
// link [unknown: link object being inserted]
//   +0x10/+0x18 [unknown: match-side list pointers]
//   +0x20 [unknown: owner_id copy]
//   +0x30 [unknown: back-pointer to owner]
//   +0x38/+0x40 [unknown: owner-side list pointers]
//   +0x48 [unknown: key copy]
//   +0x58 [unknown: back-pointer to match]
//   +0x64 [unknown: flags byte; bit at +0x65 set to 1 on insert]
//   +0x65 [unknown: inserted flag]
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
// Packs multiple sub-fields into a single u32 at entry+0x0C [unknown: packed flags word]
// Field layout (LSB to MSB): [6:0]=f0, [12:7]=f1, [15:13]=f2, [20:16]=f3, [23:21]=f4, [26:24]=f5, [28:27]=f6, [31:29]=f7
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

// 0x710064c290 — initialize vtable + data for a sub-object
// Writes vtable label from PTR_LAB_7104f7fe70 and copies data pointer from self+0x08
// self+0x08 [unknown: data pointer, copied to dst[1]]
void FUN_710064c290(s64 self, u64 *dst)
{
    *dst = (u64)&PTR_LAB_7104f7fe70;
    dst[1] = *(u64 *)(self + 8);
}

// 0x710065dcc0 — map opcode pair: remap certain (opcode, -1) or (0x4b, 0x4c) combos
// [inferred: input command remapping — combines two sequential inputs into a single action code]
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

// 0x710065dd70 — return 1 if opcode is a "complex" action (requires special handling), else 0
// [inferred: action classification — 30 recognized opcodes return 1, likely multi-frame or stateful actions]
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

// 0x710067a3a0 — check if any of 8 fighter entries is active (type==3+flag or state>1)
// self = FighterManagerData* [derived: called with *FighterManager::instance_ in is_final_status_or_standby (.dynsym)]
u8 FUN_710067a3a0(s64 self, u32 check_slots)
{
    s64 slot;

    if ((check_slots & 1) == 0) {
        // +0xBC [unknown: manager-level active flag, returned as bool when check_slots bit 0 clear]
        return '\0' < *(s8 *)(self + 0xbc);
    }
    // Check all 8 fighter entries (entries[0..7] at +0x20..+0x58)
    // [derived: FighterManagerData.entries[8] from get_fighter_entry_impl (.dynsym), indexes +0x20 with entry_id*8]
    // Per-entry checks:
    //   (&DAT_00005920)[slot] → FighterEntry.entry_type at +0x5920 [derived: FighterEntry struct]
    //   type 3 = fighter [inferred: checked alongside fighter-specific fields across 12+ functions]
    //   +0x44D2 [unknown: flag byte within FighterEntry, always paired with type==3 check]
    //   +0x5921 [inferred: active/alive state, byte after entry_type; nonzero = active]
    slot = *(s64 *)(self + 0x20);                       // entries[0]
    if (slot != 0) {
        if (((&DAT_00005920)[slot] == '\x03') && (*(s8 *)(slot + 0x44d2) != '\0')) {
            return 1;
        }
        if (*(s8 *)(slot + 0x5921) != '\0') {
            return 1;
        }
    }
    slot = *(s64 *)(self + 0x28);                       // entries[1]
    if (slot != 0) {
        if (((&DAT_00005920)[slot] == '\x03') && (*(s8 *)(slot + 0x44d2) != '\0')) {
            return 1;
        }
        if (*(s8 *)(slot + 0x5921) != '\0') {
            return 1;
        }
    }
    slot = *(s64 *)(self + 0x30);                       // entries[2]
    if (slot != 0) {
        if (((&DAT_00005920)[slot] == '\x03') && (*(s8 *)(slot + 0x44d2) != '\0')) {
            return 1;
        }
        if (*(s8 *)(slot + 0x5921) != '\0') {
            return 1;
        }
    }
    slot = *(s64 *)(self + 0x38);                       // entries[3]
    if (slot != 0) {
        if (((&DAT_00005920)[slot] == '\x03') && (*(s8 *)(slot + 0x44d2) != '\0')) {
            return 1;
        }
        if (*(s8 *)(slot + 0x5921) != '\0') {
            return 1;
        }
    }
    slot = *(s64 *)(self + 0x40);                       // entries[4]
    if (slot != 0) {
        if (((&DAT_00005920)[slot] == '\x03') && (*(s8 *)(slot + 0x44d2) != '\0')) {
            return 1;
        }
        if (*(s8 *)(slot + 0x5921) != '\0') {
            return 1;
        }
    }
    slot = *(s64 *)(self + 0x48);                       // entries[5]
    if (slot != 0) {
        if (((&DAT_00005920)[slot] == '\x03') && (*(s8 *)(slot + 0x44d2) != '\0')) {
            return 1;
        }
        if (*(s8 *)(slot + 0x5921) != '\0') {
            return 1;
        }
    }
    slot = *(s64 *)(self + 0x50);                       // entries[6]
    if (slot != 0) {
        if (((&DAT_00005920)[slot] == '\x03') && (*(s8 *)(slot + 0x44d2) != '\0')) {
            return 1;
        }
        if (*(s8 *)(slot + 0x5921) != '\0') {
            return 1;
        }
    }
    slot = *(s64 *)(self + 0x58);                       // entries[7]
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

// 0x710067a5c0 — check if any fighter entry has non-fighter-type (or no flag) with state>1
// self = FighterManagerData* [derived: same pattern as FUN_710067a3a0, shares entries[] access]
u64 FUN_710067a5c0(s64 self)
{
    s64 slot;

    // Check entries[0..7]: return 1 if (type!=3 || !flag_0x44d2) && state_0x5921 > 1
    // Inverse of FUN_710067a3a0's type==3 check — finds non-fighter entries in active state
    slot = *(s64 *)(self + 0x20);                       // entries[0]
    if ((slot != 0) &&
       ((((&DAT_00005920)[slot] != '\x03' || (*(s8 *)(slot + 0x44d2) == '\0')) &&
        (1 < *(u8 *)(slot + 0x5921))))) {
        return 1;
    }
    slot = *(s64 *)(self + 0x28);                       // entries[1]
    if ((slot != 0) &&
       ((((&DAT_00005920)[slot] != '\x03' || (*(s8 *)(slot + 0x44d2) == '\0')) &&
        (1 < *(u8 *)(slot + 0x5921))))) {
        return 1;
    }
    slot = *(s64 *)(self + 0x30);                       // entries[2]
    if (((slot != 0) && (((&DAT_00005920)[slot] != '\x03' || (*(s8 *)(slot + 0x44d2) == '\0'))))
       && (1 < *(u8 *)(slot + 0x5921))) {
        return 1;
    }
    slot = *(s64 *)(self + 0x38);                       // entries[3]
    if ((slot != 0) &&
       ((((&DAT_00005920)[slot] != '\x03' || (*(s8 *)(slot + 0x44d2) == '\0')) &&
        (1 < *(u8 *)(slot + 0x5921))))) {
        return 1;
    }
    slot = *(s64 *)(self + 0x40);                       // entries[4]
    if ((slot != 0) &&
       ((((&DAT_00005920)[slot] != '\x03' || (*(s8 *)(slot + 0x44d2) == '\0')) &&
        (1 < *(u8 *)(slot + 0x5921))))) {
        return 1;
    }
    slot = *(s64 *)(self + 0x48);                       // entries[5]
    if (((slot != 0) && (((&DAT_00005920)[slot] != '\x03' || (*(s8 *)(slot + 0x44d2) == '\0'))))
       && (1 < *(u8 *)(slot + 0x5921))) {
        return 1;
    }
    slot = *(s64 *)(self + 0x50);                       // entries[6]
    if ((slot != 0) &&
       ((((&DAT_00005920)[slot] != '\x03' || (*(s8 *)(slot + 0x44d2) == '\0')) &&
        (1 < *(u8 *)(slot + 0x5921))))) {
        return 1;
    }
    slot = *(s64 *)(self + 0x58);                       // entries[7]
    if (((slot != 0) && (((&DAT_00005920)[slot] != '\x03' || (*(s8 *)(slot + 0x44d2) == '\0'))))
       && (1 < *(u8 *)(slot + 0x5921))) {
        return 1;
    }
    return 0;
}

// 0x710067e670 — dispatch FUN_710065d450 to each fighter entry, skipping source
// self = FighterManagerData* [derived: called with *FighterManager::instance_ in FUN_7100653490]
// Filters: action != 6, action not in [0x4d..0x50], action >= 0
// Per entry: skips if entry's object_id == source_id (avoids self-dispatch)
void FUN_710067e670(s64 self, s32 source_id, s32 action)
{
    s64 slot;

    if (((action != 6) && (3 < (u32)(action - 0x4d))) && (-1 < action)) {
        // entries[0..7] [derived: FighterManagerData.entries[8]]
        // +0xE0 on each entry [inferred: object_id — compared with source_id to skip self-dispatch]
        //   [evidence: caller FUN_7100653490 passes *(s32*)(param_1+0xe0) as source_id]
        slot = *(s64 *)(self + 0x20);                   // entries[0]
        if ((slot != 0) && (*(s32 *)(slot + 0xe0) != source_id)) {
            FUN_710065d450(slot, action, source_id);
        }
        slot = *(s64 *)(self + 0x28);                   // entries[1]
        if ((slot != 0) && (*(s32 *)(slot + 0xe0) != source_id)) {
            FUN_710065d450(slot, action, source_id);
        }
        slot = *(s64 *)(self + 0x30);                   // entries[2]
        if ((slot != 0) && (*(s32 *)(slot + 0xe0) != source_id)) {
            FUN_710065d450(slot, action, source_id);
        }
        slot = *(s64 *)(self + 0x38);                   // entries[3]
        if ((slot != 0) && (*(s32 *)(slot + 0xe0) != source_id)) {
            FUN_710065d450(slot, action, source_id);
        }
        slot = *(s64 *)(self + 0x40);                   // entries[4]
        if ((slot != 0) && (*(s32 *)(slot + 0xe0) != source_id)) {
            FUN_710065d450(slot, action, source_id);
        }
        slot = *(s64 *)(self + 0x48);                   // entries[5]
        if ((slot != 0) && (*(s32 *)(slot + 0xe0) != source_id)) {
            FUN_710065d450(slot, action, source_id);
        }
        slot = *(s64 *)(self + 0x50);                   // entries[6]
        if ((slot != 0) && (*(s32 *)(slot + 0xe0) != source_id)) {
            FUN_710065d450(slot, action, source_id);
        }
        slot = *(s64 *)(self + 0x58);                   // entries[7]
        if ((slot != 0) && (*(s32 *)(slot + 0xe0) != source_id)) {
            FUN_710065d450(slot, action, source_id);
        }
    }
}

// 0x710068d530 — table lookup for index < 0x5E (94 entries), else singleton fallback
// PTR_PTR_710529bfd0 [unknown: global array of 94 u64* entries, indexed by param]
// DAT_71052b8800 [unknown: __cxa_guard for singleton init of fallback entry]
// DAT_71052b8808 [unknown: singleton fallback value, initialized to PTR_LAB_7104f83b18]
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
