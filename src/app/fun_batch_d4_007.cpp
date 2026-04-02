#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7100 address range, batch d4-007
// Pool-d worker: auto-generated from Ghidra decompilation
// Includes: motion-type switches, bit-array ops, multi-sub-object checks, vtable dispatchers

// ---- External declarations -----------------------------------------------

[[noreturn]] extern "C" void abort();

// Forward declarations
extern "C" void FUN_710065d430(s64, s32, s32);

// ---- Functions ---------------------------------------------------------------

// 0x71004f5750 — init: set 8 sentinel pointer entries in param_1
void FUN_71004f5750(u64 *param_1)
{
    extern u8 DAT_c1ffff0000000000;
    *param_1     = (u64)&DAT_c1ffff0000000000;
    param_1[3]   = (u64)&DAT_c1ffff0000000000;
    param_1[6]   = (u64)&DAT_c1ffff0000000000;
    param_1[9]   = (u64)&DAT_c1ffff0000000000;
    param_1[0xc] = (u64)&DAT_c1ffff0000000000;
    param_1[0xf] = (u64)&DAT_c1ffff0000000000;
    param_1[0x12]= (u64)&DAT_c1ffff0000000000;
    param_1[0x15]= (u64)&DAT_c1ffff0000000000;
}

// 0x710058b1d0 — vtable dispatch: call vtable[0xc0], forward return
u32 FUN_710058b1d0(s64 *param_1)
{
    return (**(u32 (**)())(*param_1 + 0xc0))();
}

// 0x710065dca0 — motion-type remap: switch selected pairs to alternate IDs
u32 FUN_710065dca0(u32 *param_1)
{
    switch(*param_1) {
    case 0x24:
        if (param_1[1] == (u32)-1) {
            return 0x6f;
        }
        break;
    case 0x25:
        if (param_1[1] == (u32)-1) {
            return 0x70;
        }
        break;
    case 0x26:
        if (param_1[1] == (u32)-1) {
            return 0x71;
        }
        break;
    case 0x4b:
        if (param_1[1] == 0x4c) {
            return 0x6e;
        }
        break;
    case 0x5a:
        if (param_1[1] == (u32)-1) {
            return 0x73;
        }
        break;
    case 0x5b:
        if (param_1[1] == (u32)-1) {
            return 0x74;
        }
        break;
    }
    return *param_1;
}

// 0x710065dd50 — motion-type check: return 1 if motion is in the combo/special set
u64 FUN_710065dd50(u32 param_1)
{
    switch(param_1) {
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

// 0x710065f690 — bit-array set: set bit uVar2 in the bit table at param_1+8
void FUN_710065f690(s64 param_1, u16 *param_2, u32 param_3)
{
    s64 lVar1;
    u16 uVar2;

    uVar2 = *param_2;
    if ((param_3 & 1) != 0) {
        if (uVar2 != 0) {
            if (0x11c < uVar2) goto lab_abort;
            if ((*(u64 *)(*(s64 *)(param_1 + 8) + ((u64)(uVar2 >> 3) & 0x1ff8) + 0x968) &
                ((u64)1 << ((u64)uVar2 & 0x3f))) != 0) goto lab_set;
        }
        return;
    }
    if (uVar2 < 0x11d) {
lab_set:
        lVar1 = *(s64 *)(param_1 + 8) + ((u64)(uVar2 >> 3) & 0x1ff8);
        *(u64 *)(lVar1 + 0x1b0) = *(u64 *)(lVar1 + 0x1b0) | ((u64)1 << ((u64)uVar2 & 0x3f));
        return;
    }
lab_abort:
    abort();
}

// 0x710065f710 — bit-array clear: clear bit uVar2 in the bit table at param_1+8
void FUN_710065f710(s64 param_1, u16 *param_2, u32 param_3)
{
    s64 lVar1;
    u16 uVar2;

    uVar2 = *param_2;
    if ((param_3 & 1) != 0) {
        if (uVar2 != 0) {
            if (0x11c < uVar2) goto lab_abort;
            if ((*(u64 *)(*(s64 *)(param_1 + 8) + ((u64)(uVar2 >> 3) & 0x1ff8) + 0x968) &
                ((u64)1 << ((u64)uVar2 & 0x3f))) != 0) goto lab_clear;
        }
        return;
    }
    if (uVar2 < 0x11d) {
lab_clear:
        lVar1 = *(s64 *)(param_1 + 8) + ((u64)(uVar2 >> 3) & 0x1ff8);
        *(u64 *)(lVar1 + 0x1b0) = *(u64 *)(lVar1 + 0x1b0) &
            (((u64)1 << ((u64)uVar2 & 0x3f)) ^ (u64)0xffffffffffffffffULL);
        return;
    }
lab_abort:
    abort();
}

// 0x710065f7b0 — bit-array read: check if bit uVar1 is set in the bit table
u8 FUN_710065f7b0(s64 param_1, u16 *param_2, u32 param_3)
{
    u16 uVar1;

    uVar1 = *param_2;
    if ((param_3 & 1) == 0) {
        if (0x11c < uVar1) goto lab_abort;
    }
    else {
        if (uVar1 == 0) {
            return 0;
        }
        if (0x11c < uVar1) {
lab_abort:
            abort();
        }
        if ((*(u64 *)(*(s64 *)(param_1 + 8) + ((u64)(uVar1 >> 3) & 0x1ff8) + 0x968) &
            ((u64)1 << ((u64)uVar1 & 0x3f))) == 0) {
            return 0;
        }
    }
    return (*(u64 *)(*(s64 *)(param_1 + 8) + ((u64)(uVar1 >> 3) & 0x1ff8) + 0x1b0) &
           ((u64)1 << ((u64)uVar1 & 0x3f))) != 0;
}

// 0x710067a380 — multi-sub check: return true if any sub-object has specific state flags
u8 FUN_710067a380(s64 param_1, u32 param_2)
{
    s64 lVar1;

    if ((param_2 & 1) == 0) {
        return '\0' < *(s8 *)(param_1 + 0xbc);
    }
    lVar1 = *(s64 *)(param_1 + 0x20);
    if (lVar1 != 0) {
        if ((*(u8 *)(lVar1 + 0x5920) == '\x03') && (*(u8 *)(lVar1 + 0x44d2) != '\0')) {
            return 1;
        }
        if (*(u8 *)(lVar1 + 0x5921) != '\0') {
            return 1;
        }
    }
    lVar1 = *(s64 *)(param_1 + 0x28);
    if (lVar1 != 0) {
        if ((*(u8 *)(lVar1 + 0x5920) == '\x03') && (*(u8 *)(lVar1 + 0x44d2) != '\0')) {
            return 1;
        }
        if (*(u8 *)(lVar1 + 0x5921) != '\0') {
            return 1;
        }
    }
    lVar1 = *(s64 *)(param_1 + 0x30);
    if (lVar1 != 0) {
        if ((*(u8 *)(lVar1 + 0x5920) == '\x03') && (*(u8 *)(lVar1 + 0x44d2) != '\0')) {
            return 1;
        }
        if (*(u8 *)(lVar1 + 0x5921) != '\0') {
            return 1;
        }
    }
    lVar1 = *(s64 *)(param_1 + 0x38);
    if (lVar1 != 0) {
        if ((*(u8 *)(lVar1 + 0x5920) == '\x03') && (*(u8 *)(lVar1 + 0x44d2) != '\0')) {
            return 1;
        }
        if (*(u8 *)(lVar1 + 0x5921) != '\0') {
            return 1;
        }
    }
    lVar1 = *(s64 *)(param_1 + 0x40);
    if (lVar1 != 0) {
        if ((*(u8 *)(lVar1 + 0x5920) == '\x03') && (*(u8 *)(lVar1 + 0x44d2) != '\0')) {
            return 1;
        }
        if (*(u8 *)(lVar1 + 0x5921) != '\0') {
            return 1;
        }
    }
    lVar1 = *(s64 *)(param_1 + 0x48);
    if (lVar1 != 0) {
        if ((*(u8 *)(lVar1 + 0x5920) == '\x03') && (*(u8 *)(lVar1 + 0x44d2) != '\0')) {
            return 1;
        }
        if (*(u8 *)(lVar1 + 0x5921) != '\0') {
            return 1;
        }
    }
    lVar1 = *(s64 *)(param_1 + 0x50);
    if (lVar1 != 0) {
        if ((*(u8 *)(lVar1 + 0x5920) == '\x03') && (*(u8 *)(lVar1 + 0x44d2) != '\0')) {
            return 1;
        }
        if (*(u8 *)(lVar1 + 0x5921) != '\0') {
            return 1;
        }
    }
    lVar1 = *(s64 *)(param_1 + 0x58);
    if (lVar1 != 0) {
        if ((*(u8 *)(lVar1 + 0x5920) == '\x03') && (*(u8 *)(lVar1 + 0x44d2) != '\0')) {
            return 1;
        }
        if (*(u8 *)(lVar1 + 0x5921) != '\0') {
            return 1;
        }
    }
    return 0;
}

// 0x710067a5a0 — multi-sub check: return 1 if any sub-object has stopped state with extra byte > 1
u64 FUN_710067a5a0(s64 param_1)
{
    s64 lVar1;

    lVar1 = *(s64 *)(param_1 + 0x20);
    if ((lVar1 != 0) &&
       (((*(u8 *)(lVar1 + 0x5920) != '\x03' || (*(u8 *)(lVar1 + 0x44d2) == '\0')) &&
        (1 < *(u8 *)(lVar1 + 0x5921))))) {
        return 1;
    }
    lVar1 = *(s64 *)(param_1 + 0x28);
    if ((lVar1 != 0) &&
       (((*(u8 *)(lVar1 + 0x5920) != '\x03' || (*(u8 *)(lVar1 + 0x44d2) == '\0')) &&
        (1 < *(u8 *)(lVar1 + 0x5921))))) {
        return 1;
    }
    lVar1 = *(s64 *)(param_1 + 0x30);
    if (((lVar1 != 0) && ((*(u8 *)(lVar1 + 0x5920) != '\x03' || (*(u8 *)(lVar1 + 0x44d2) == '\0'))))
       && (1 < *(u8 *)(lVar1 + 0x5921))) {
        return 1;
    }
    lVar1 = *(s64 *)(param_1 + 0x38);
    if ((lVar1 != 0) &&
       (((*(u8 *)(lVar1 + 0x5920) != '\x03' || (*(u8 *)(lVar1 + 0x44d2) == '\0')) &&
        (1 < *(u8 *)(lVar1 + 0x5921))))) {
        return 1;
    }
    lVar1 = *(s64 *)(param_1 + 0x40);
    if ((lVar1 != 0) &&
       (((*(u8 *)(lVar1 + 0x5920) != '\x03' || (*(u8 *)(lVar1 + 0x44d2) == '\0')) &&
        (1 < *(u8 *)(lVar1 + 0x5921))))) {
        return 1;
    }
    lVar1 = *(s64 *)(param_1 + 0x48);
    if (((lVar1 != 0) && ((*(u8 *)(lVar1 + 0x5920) != '\x03' || (*(u8 *)(lVar1 + 0x44d2) == '\0'))))
       && (1 < *(u8 *)(lVar1 + 0x5921))) {
        return 1;
    }
    lVar1 = *(s64 *)(param_1 + 0x50);
    if ((lVar1 != 0) &&
       (((*(u8 *)(lVar1 + 0x5920) != '\x03' || (*(u8 *)(lVar1 + 0x44d2) == '\0')) &&
        (1 < *(u8 *)(lVar1 + 0x5921))))) {
        return 1;
    }
    lVar1 = *(s64 *)(param_1 + 0x58);
    if (((lVar1 != 0) && ((*(u8 *)(lVar1 + 0x5920) != '\x03' || (*(u8 *)(lVar1 + 0x44d2) == '\0'))))
       && (1 < *(u8 *)(lVar1 + 0x5921))) {
        return 1;
    }
    return 0;
}

// 0x710067e650 — multi-sub dispatch: call FUN_710065d430 on each non-null sub-object with different int field
void FUN_710067e650(s64 param_1, s32 param_2, s32 param_3)
{
    s64 paVar1;

    if (((param_3 != 6) && (3 < (u32)((u32)param_3 - 0x4d))) && (-1 < param_3)) {
        paVar1 = *(s64 *)(param_1 + 0x20);
        if ((paVar1 != 0) && (*(s32 *)(paVar1 + 0xe0) != param_2)) {
            FUN_710065d430(paVar1, param_3, param_2);
        }
        paVar1 = *(s64 *)(param_1 + 0x28);
        if ((paVar1 != 0) && (*(s32 *)(paVar1 + 0xe0) != param_2)) {
            FUN_710065d430(paVar1, param_3, param_2);
        }
        paVar1 = *(s64 *)(param_1 + 0x30);
        if ((paVar1 != 0) && (*(s32 *)(paVar1 + 0xe0) != param_2)) {
            FUN_710065d430(paVar1, param_3, param_2);
        }
        paVar1 = *(s64 *)(param_1 + 0x38);
        if ((paVar1 != 0) && (*(s32 *)(paVar1 + 0xe0) != param_2)) {
            FUN_710065d430(paVar1, param_3, param_2);
        }
        paVar1 = *(s64 *)(param_1 + 0x40);
        if ((paVar1 != 0) && (*(s32 *)(paVar1 + 0xe0) != param_2)) {
            FUN_710065d430(paVar1, param_3, param_2);
        }
        paVar1 = *(s64 *)(param_1 + 0x48);
        if ((paVar1 != 0) && (*(s32 *)(paVar1 + 0xe0) != param_2)) {
            FUN_710065d430(paVar1, param_3, param_2);
        }
        paVar1 = *(s64 *)(param_1 + 0x50);
        if ((paVar1 != 0) && (*(s32 *)(paVar1 + 0xe0) != param_2)) {
            FUN_710065d430(paVar1, param_3, param_2);
        }
        paVar1 = *(s64 *)(param_1 + 0x58);
        if ((paVar1 != 0) && (*(s32 *)(paVar1 + 0xe0) != param_2)) {
            FUN_710065d430(paVar1, param_3, param_2);
        }
    }
}
