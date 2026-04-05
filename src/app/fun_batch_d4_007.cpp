#include "types.h"

// ---- External declarations -----------------------------------------------

[[noreturn]] extern "C" void abort();

extern "C" void FUN_710065d430(s64, s32, s32);

// ---- Functions ---------------------------------------------------------------

// 0x71004f5750 — Initializes 8 entries at stride-3 with a sentinel pointer (NaN-boxed null)
void FUN_71004f5750(u64 *entries)
{
    extern u8 DAT_c1ffff0000000000;
    entries[0]    = (u64)&DAT_c1ffff0000000000;
    entries[3]    = (u64)&DAT_c1ffff0000000000;
    entries[6]    = (u64)&DAT_c1ffff0000000000;
    entries[9]    = (u64)&DAT_c1ffff0000000000;
    entries[0xc]  = (u64)&DAT_c1ffff0000000000;
    entries[0xf]  = (u64)&DAT_c1ffff0000000000;
    entries[0x12] = (u64)&DAT_c1ffff0000000000;
    entries[0x15] = (u64)&DAT_c1ffff0000000000;
}

// 0x710065dca0 — Remaps specific (motion_kind, sub_kind) pairs to alternate IDs
u32 FUN_710065dca0(u32 *motion_pair)
{
    switch(motion_pair[0]) {
    case 0x24:
        if (motion_pair[1] == (u32)-1) {
            return 0x6f;
        }
        break;
    case 0x25:
        if (motion_pair[1] == (u32)-1) {
            return 0x70;
        }
        break;
    case 0x26:
        if (motion_pair[1] == (u32)-1) {
            return 0x71;
        }
        break;
    case 0x4b:
        if (motion_pair[1] == 0x4c) {
            return 0x6e;
        }
        break;
    case 0x5a:
        if (motion_pair[1] == (u32)-1) {
            return 0x73;
        }
        break;
    case 0x5b:
        if (motion_pair[1] == (u32)-1) {
            return 0x74;
        }
        break;
    }
    return motion_pair[0];
}

// 0x710065dd50 — Returns 1 if motion_kind is in the combo/special set
u64 FUN_710065dd50(u32 motion_kind)
{
    switch(motion_kind) {
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

// 0x710065f690 — Bit-array set: sets bit_index in the bit table at container+8
// Two bit planes: +0x968 = valid mask, +0x1b0 = value bits
// If check_valid (param_3 & 1), only set if the bit is marked valid
void FUN_710065f690(s64 container, u16 *bit_index_ptr, u32 flags)
{
    s64 slot_base;
    u16 bit_index;

    bit_index = *bit_index_ptr;
    if ((flags & 1) != 0) {
        if (bit_index != 0) {
            if (0x11c < bit_index) goto lab_abort;
            if ((*(u64 *)(*(s64 *)(container + 8) + ((u64)(bit_index >> 3) & 0x1ff8) + 0x968) &
                ((u64)1 << ((u64)bit_index & 0x3f))) != 0) goto lab_set;
        }
        return;
    }
    if (bit_index < 0x11d) {
lab_set:
        slot_base = *(s64 *)(container + 8) + ((u64)(bit_index >> 3) & 0x1ff8);
        *(u64 *)(slot_base + 0x1b0) = *(u64 *)(slot_base + 0x1b0) | ((u64)1 << ((u64)bit_index & 0x3f));
        return;
    }
lab_abort:
    abort();
}

// 0x710065f710 — Bit-array clear: clears bit_index in the bit table at container+8
void FUN_710065f710(s64 container, u16 *bit_index_ptr, u32 flags)
{
    s64 slot_base;
    u16 bit_index;

    bit_index = *bit_index_ptr;
    if ((flags & 1) != 0) {
        if (bit_index != 0) {
            if (0x11c < bit_index) goto lab_abort;
            if ((*(u64 *)(*(s64 *)(container + 8) + ((u64)(bit_index >> 3) & 0x1ff8) + 0x968) &
                ((u64)1 << ((u64)bit_index & 0x3f))) != 0) goto lab_clear;
        }
        return;
    }
    if (bit_index < 0x11d) {
lab_clear:
        slot_base = *(s64 *)(container + 8) + ((u64)(bit_index >> 3) & 0x1ff8);
        *(u64 *)(slot_base + 0x1b0) = *(u64 *)(slot_base + 0x1b0) &
            (((u64)1 << ((u64)bit_index & 0x3f)) ^ (u64)0xffffffffffffffffULL);
        return;
    }
lab_abort:
    abort();
}

// 0x710065f7b0 — Bit-array read: returns 1 if bit_index is set in the value plane
u8 FUN_710065f7b0(s64 container, u16 *bit_index_ptr, u32 flags)
{
    u16 bit_index;

    bit_index = *bit_index_ptr;
    if ((flags & 1) == 0) {
        if (0x11c < bit_index) goto lab_abort;
    }
    else {
        if (bit_index == 0) {
            return 0;
        }
        if (0x11c < bit_index) {
lab_abort:
            abort();
        }
        if ((*(u64 *)(*(s64 *)(container + 8) + ((u64)(bit_index >> 3) & 0x1ff8) + 0x968) &
            ((u64)1 << ((u64)bit_index & 0x3f))) == 0) {
            return 0;
        }
    }
    return (*(u64 *)(*(s64 *)(container + 8) + ((u64)(bit_index >> 3) & 0x1ff8) + 0x1b0) &
           ((u64)1 << ((u64)bit_index & 0x3f))) != 0;
}

// 0x710067a380 — Returns 1 if any of 8 sub-objects has active state flags
// Sub-objects stored at obj+0x20..+0x58 (8 pointer slots, stride 8)
// Each sub-object checked: +0x5920 state, +0x44d2 active flag, +0x5921 extra state
u8 FUN_710067a380(s64 obj, u32 param_2)
{
    s64 sub;

    if ((param_2 & 1) == 0) {
        return '\0' < *(s8 *)(obj + 0xbc);
    }
    sub = *(s64 *)(obj + 0x20);
    if (sub != 0) {
        if ((*(u8 *)(sub + 0x5920) == '\x03') && (*(u8 *)(sub + 0x44d2) != '\0')) {
            return 1;
        }
        if (*(u8 *)(sub + 0x5921) != '\0') {
            return 1;
        }
    }
    sub = *(s64 *)(obj + 0x28);
    if (sub != 0) {
        if ((*(u8 *)(sub + 0x5920) == '\x03') && (*(u8 *)(sub + 0x44d2) != '\0')) {
            return 1;
        }
        if (*(u8 *)(sub + 0x5921) != '\0') {
            return 1;
        }
    }
    sub = *(s64 *)(obj + 0x30);
    if (sub != 0) {
        if ((*(u8 *)(sub + 0x5920) == '\x03') && (*(u8 *)(sub + 0x44d2) != '\0')) {
            return 1;
        }
        if (*(u8 *)(sub + 0x5921) != '\0') {
            return 1;
        }
    }
    sub = *(s64 *)(obj + 0x38);
    if (sub != 0) {
        if ((*(u8 *)(sub + 0x5920) == '\x03') && (*(u8 *)(sub + 0x44d2) != '\0')) {
            return 1;
        }
        if (*(u8 *)(sub + 0x5921) != '\0') {
            return 1;
        }
    }
    sub = *(s64 *)(obj + 0x40);
    if (sub != 0) {
        if ((*(u8 *)(sub + 0x5920) == '\x03') && (*(u8 *)(sub + 0x44d2) != '\0')) {
            return 1;
        }
        if (*(u8 *)(sub + 0x5921) != '\0') {
            return 1;
        }
    }
    sub = *(s64 *)(obj + 0x48);
    if (sub != 0) {
        if ((*(u8 *)(sub + 0x5920) == '\x03') && (*(u8 *)(sub + 0x44d2) != '\0')) {
            return 1;
        }
        if (*(u8 *)(sub + 0x5921) != '\0') {
            return 1;
        }
    }
    sub = *(s64 *)(obj + 0x50);
    if (sub != 0) {
        if ((*(u8 *)(sub + 0x5920) == '\x03') && (*(u8 *)(sub + 0x44d2) != '\0')) {
            return 1;
        }
        if (*(u8 *)(sub + 0x5921) != '\0') {
            return 1;
        }
    }
    sub = *(s64 *)(obj + 0x58);
    if (sub != 0) {
        if ((*(u8 *)(sub + 0x5920) == '\x03') && (*(u8 *)(sub + 0x44d2) != '\0')) {
            return 1;
        }
        if (*(u8 *)(sub + 0x5921) != '\0') {
            return 1;
        }
    }
    return 0;
}

// 0x710067a5a0 — Returns 1 if any sub-object has non-stopped state with extra > 1
u64 FUN_710067a5a0(s64 obj)
{
    s64 sub;

    sub = *(s64 *)(obj + 0x20);
    if ((sub != 0) &&
       (((*(u8 *)(sub + 0x5920) != '\x03' || (*(u8 *)(sub + 0x44d2) == '\0')) &&
        (1 < *(u8 *)(sub + 0x5921))))) {
        return 1;
    }
    sub = *(s64 *)(obj + 0x28);
    if ((sub != 0) &&
       (((*(u8 *)(sub + 0x5920) != '\x03' || (*(u8 *)(sub + 0x44d2) == '\0')) &&
        (1 < *(u8 *)(sub + 0x5921))))) {
        return 1;
    }
    sub = *(s64 *)(obj + 0x30);
    if (((sub != 0) && ((*(u8 *)(sub + 0x5920) != '\x03' || (*(u8 *)(sub + 0x44d2) == '\0'))))
       && (1 < *(u8 *)(sub + 0x5921))) {
        return 1;
    }
    sub = *(s64 *)(obj + 0x38);
    if ((sub != 0) &&
       (((*(u8 *)(sub + 0x5920) != '\x03' || (*(u8 *)(sub + 0x44d2) == '\0')) &&
        (1 < *(u8 *)(sub + 0x5921))))) {
        return 1;
    }
    sub = *(s64 *)(obj + 0x40);
    if ((sub != 0) &&
       (((*(u8 *)(sub + 0x5920) != '\x03' || (*(u8 *)(sub + 0x44d2) == '\0')) &&
        (1 < *(u8 *)(sub + 0x5921))))) {
        return 1;
    }
    sub = *(s64 *)(obj + 0x48);
    if (((sub != 0) && ((*(u8 *)(sub + 0x5920) != '\x03' || (*(u8 *)(sub + 0x44d2) == '\0'))))
       && (1 < *(u8 *)(sub + 0x5921))) {
        return 1;
    }
    sub = *(s64 *)(obj + 0x50);
    if ((sub != 0) &&
       (((*(u8 *)(sub + 0x5920) != '\x03' || (*(u8 *)(sub + 0x44d2) == '\0')) &&
        (1 < *(u8 *)(sub + 0x5921))))) {
        return 1;
    }
    sub = *(s64 *)(obj + 0x58);
    if (((sub != 0) && ((*(u8 *)(sub + 0x5920) != '\x03' || (*(u8 *)(sub + 0x44d2) == '\0'))))
       && (1 < *(u8 *)(sub + 0x5921))) {
        return 1;
    }
    return 0;
}

// 0x710067e650 — Dispatches FUN_710065d430 to each non-null sub-object whose field +0xe0 differs from param_2
void FUN_710067e650(s64 obj, s32 param_2, s32 param_3)
{
    s64 sub;

    if (((param_3 != 6) && (3 < (u32)((u32)param_3 - 0x4d))) && (-1 < param_3)) {
        sub = *(s64 *)(obj + 0x20);
        if ((sub != 0) && (*(s32 *)(sub + 0xe0) != param_2)) {
            FUN_710065d430(sub, param_3, param_2);
        }
        sub = *(s64 *)(obj + 0x28);
        if ((sub != 0) && (*(s32 *)(sub + 0xe0) != param_2)) {
            FUN_710065d430(sub, param_3, param_2);
        }
        sub = *(s64 *)(obj + 0x30);
        if ((sub != 0) && (*(s32 *)(sub + 0xe0) != param_2)) {
            FUN_710065d430(sub, param_3, param_2);
        }
        sub = *(s64 *)(obj + 0x38);
        if ((sub != 0) && (*(s32 *)(sub + 0xe0) != param_2)) {
            FUN_710065d430(sub, param_3, param_2);
        }
        sub = *(s64 *)(obj + 0x40);
        if ((sub != 0) && (*(s32 *)(sub + 0xe0) != param_2)) {
            FUN_710065d430(sub, param_3, param_2);
        }
        sub = *(s64 *)(obj + 0x48);
        if ((sub != 0) && (*(s32 *)(sub + 0xe0) != param_2)) {
            FUN_710065d430(sub, param_3, param_2);
        }
        sub = *(s64 *)(obj + 0x50);
        if ((sub != 0) && (*(s32 *)(sub + 0xe0) != param_2)) {
            FUN_710065d430(sub, param_3, param_2);
        }
        sub = *(s64 *)(obj + 0x58);
        if ((sub != 0) && (*(s32 *)(sub + 0xe0) != param_2)) {
            FUN_710065d430(sub, param_3, param_2);
        }
    }
}
