#include "types.h"

// MEDIUM-tier FUN_* functions — 0x71001xxxxx range, batch d4-011
// Pool-d worker: auto-generated from Ghidra decompilation
// Includes: bool-check variants, DLL circular search, protocol tables, ring buf

// ---- External declarations -----------------------------------------------

// Network protocol field write targets (FUN_7100149270 / FUN_7100149290)
extern u64 PTR_DAT_71052a3bd0;
extern u64 PTR_DAT_71052a3bd8;

// Vtable init base (FUN_710014f150)
extern u64 PTR_DAT_71052a4f38;

// ---- Functions ---------------------------------------------------------------

// 0x7100145ec0 — true if field+0x140 == 3 and field+0x110 in [2..4]
u8 FUN_7100145ec0(s64 param_1)
{
    if (*(s32 *)(param_1 + 0x140) == 3) {
        return *(s32 *)(param_1 + 0x110) - 2U < 3;
    }
    return 0;
}

// 0x7100146070 — true if field+0x140 == 4 and field+0x110 in [2..4]
u8 FUN_7100146070(s64 param_1)
{
    if (*(s32 *)(param_1 + 0x140) == 4) {
        return *(s32 *)(param_1 + 0x110) - 2U < 3;
    }
    return 0;
}

// 0x71001462a0 — true if field+0x140 == 5 and field+0x110 in [2..4]
u8 FUN_71001462a0(s64 param_1)
{
    if (*(s32 *)(param_1 + 0x140) == 5) {
        return *(s32 *)(param_1 + 0x110) - 2U < 3;
    }
    return 0;
}

// 0x7100146670 — true if field+0x140 == 7 and field+0x110 in [2..4]
u8 FUN_7100146670(s64 param_1)
{
    if (*(s32 *)(param_1 + 0x140) == 7) {
        return *(s32 *)(param_1 + 0x110) - 2U < 3;
    }
    return 0;
}

// 0x71001468b0 — true if field+0x140 == 8 and field+0x110 in [2..4]
u8 FUN_71001468b0(s64 param_1)
{
    if (*(s32 *)(param_1 + 0x140) == 8) {
        return *(s32 *)(param_1 + 0x110) - 2U < 3;
    }
    return 0;
}

// 0x7100146a90 — true if field+0x140 == 0x13 and field+0x110 in [2..4]
u8 FUN_7100146a90(s64 param_1)
{
    if (*(s32 *)(param_1 + 0x140) == 0x13) {
        return *(s32 *)(param_1 + 0x110) - 2U < 3;
    }
    return 0;
}

// 0x7100149180 — true if field+0x140 == 0x1a and field+0x110 in [2..4]
u8 FUN_7100149180(s64 param_1)
{
    if (*(s32 *)(param_1 + 0x140) == 0x1a) {
        return *(s32 *)(param_1 + 0x110) - 2U < 3;
    }
    return 0;
}

// 0x7100149270 — write param_2 to indexed slot at +0x180, conditionally to PTR field
void FUN_7100149270(s64 param_1, s32 param_2)
{
    *(s32 *)(param_1 + (u64)*(u8 *)(param_1 + 0x162) * 4 + 0x180) = param_2;
    if (param_2 != 0) {
        *(s32 *)(PTR_DAT_71052a3bd0 + 0x124) = param_2;
    }
}

// 0x7100149290 — write param_2 to indexed slot at +0x180 (index by null-check), conditionally to PTR
void FUN_7100149290(s64 param_1, s32 param_2)
{
    *(s32 *)(param_1 + (u64)(*(s8 *)(param_1 + 0x162) == '\0') * 4 + 0x180) = param_2;
    if (param_2 != 0) {
        *(s32 *)(PTR_DAT_71052a3bd8 + 0x300) = param_2;
    }
}

// 0x710014f090 — copy 3 u32 fields from param_2+8..+0x10 to param_1+8..+0x10
void FUN_710014f090(s64 param_1, s64 param_2)
{
    *(u32 *)(param_1 + 0x10) = *(u32 *)(param_2 + 0x10);
    *(u32 *)(param_1 + 8) = *(u32 *)(param_2 + 8);
    *(u32 *)(param_1 + 0xc) = *(u32 *)(param_2 + 0xc);
}

// 0x710014f150 — init vtable ptr in param_1[0] to PTR_DAT+0x10, zero param_1[1] low 32b
void FUN_710014f150(s64 *param_1)
{
    *(u32 *)(param_1 + 1) = 0;
    *param_1 = (s64)(PTR_DAT_71052a4f38 + 0x10);
}

// 0x71001506d0 — circular DLL search: find node+0x20==param_2, write bit0(param_3) at +0x2e
u64 FUN_71001506d0(s64 param_1, s64 param_2, u8 param_3)
{
    s64 lVar1;

    lVar1 = *(s64 *)(param_1 + 0x10);
    if (lVar1 == param_1 + 8) {
        return 0;
    }
    do {
        if (*(s64 *)(lVar1 + 0x20) == param_2) {
            *(u8 *)(lVar1 + 0x2e) = param_3 & 1;
            return 1;
        }
        lVar1 = *(s64 *)(lVar1 + 8);
    } while (lVar1 != param_1 + 8);
    return 0;
}

// 0x7100150720 — circular DLL search: find node+0x20==param_2, return byte+0x2e != 0
u8 FUN_7100150720(s64 param_1, s64 param_2)
{
    s64 lVar1;

    lVar1 = *(s64 *)(param_1 + 0x10);
    if (lVar1 == param_1 + 8) {
        return 0;
    }
    do {
        if (*(s64 *)(lVar1 + 0x20) == param_2) {
            return *(s8 *)(lVar1 + 0x2e) != '\0';
        }
        lVar1 = *(s64 *)(lVar1 + 8);
    } while (lVar1 != param_1 + 8);
    return 0;
}

// 0x7100150900 — circular DLL: clear u32 field+0x14 in every node
void FUN_7100150900(s64 param_1)
{
    s64 lVar1;

    for (lVar1 = *(s64 *)(param_1 + 0x10); lVar1 != param_1 + 8; lVar1 = *(s64 *)(lVar1 + 8)) {
        *(u32 *)(lVar1 + 0x14) = 0;
    }
}

// 0x7100150de0 — circular DLL search: find node+0x20==param_2, copy byte+0x2d to *param_3
u64 FUN_7100150de0(s64 param_1, s64 param_2, u8 *param_3)
{
    s64 lVar1;

    lVar1 = *(s64 *)(param_1 + 0x10);
    if (lVar1 == param_1 + 8) {
        return 0;
    }
    do {
        if (*(s64 *)(lVar1 + 0x20) == param_2) {
            *param_3 = *(u8 *)(lVar1 + 0x2d);
            return 1;
        }
        lVar1 = *(s64 *)(lVar1 + 8);
    } while (lVar1 != param_1 + 8);
    return 0;
}

// 0x7100150e30 — circular DLL search: find node+0x20==param_2, write bit0(param_3) at +0x2c
void FUN_7100150e30(s64 param_1, s64 param_2, u8 param_3)
{
    s64 lVar1;

    lVar1 = *(s64 *)(param_1 + 0x10);
    if (lVar1 != param_1 + 8) {
        do {
            if (*(s64 *)(lVar1 + 0x20) == param_2) {
                *(u8 *)(lVar1 + 0x2c) = param_3 & 1;
                return;
            }
            lVar1 = *(s64 *)(lVar1 + 8);
        } while (lVar1 != param_1 + 8);
    }
}

// 0x7100150ec0 — circular DLL: count nodes where field+0x28 == param_2
s32 FUN_7100150ec0(s64 param_1, s32 param_2)
{
    s32 *piVar1;
    s32 iVar2;
    s64 lVar3;

    lVar3 = *(s64 *)(param_1 + 0x10);
    if (lVar3 != param_1 + 8) {
        iVar2 = 0;
        do {
            piVar1 = (s32 *)(lVar3 + 0x28);
            lVar3 = *(s64 *)(lVar3 + 8);
            if (*piVar1 == param_2) {
                iVar2 = iVar2 + 1;
            }
        } while (lVar3 != param_1 + 8);
        return iVar2;
    }
    return 0;
}

// 0x7100151fe0 — check two flags + bit test: return 1 if field+0x78 ∈ {0,4,5}
u32 FUN_7100151fe0(s64 param_1)
{
    if (((*(s8 *)(param_1 + 0x48) != '\0') && (*(s8 *)(param_1 + 0x50) != '\0')) &&
       (*(u32 *)(param_1 + 0x78) < 6)) {
        return 0x31U >> (u64)(*(u32 *)(param_1 + 0x78) & 0x1f) & 1;
    }
    return 0;
}

// 0x7100153200 — return 1 if param_2 is a known network protocol byte value
u64 FUN_7100153200(u64 param_1, u8 param_2)
{
    switch(param_2) {
    case 8:
    case 0x14:
    case 0x18:
    case 0x1c:
    case 0x24:
    case 0x28:
    case 0x2c:
    case 0x34:
    case 0x44:
    case 0x54:
    case 0x58:
    case 0x65:
    case 0x68:
    case 0x6c:
    case 0x73:
    case 0x74:
    case 0x76:
    case 0x77:
    case 0x78:
    case 0x7b:
    case 0x7c:
    case 0x80:
    case 0x81:
    case 0x84:
    case 0x94:
    case 0xa4:
    case 0xa8:
    case 0xac:
    case 0xb0:
    case 0xb4:
        return 1;
    default:
        return 0;
    }
}

// 0x7100153d50 — write *param_2 to array slot 0x1b, call vtable[0x98], return slot 0x1d
s64 *FUN_7100153d50(s64 *param_1, u32 *param_2)
{
    *(u32 *)(param_1 + 0x1b) = *param_2;
    (**(void(**)())(*param_1 + 0x98))();
    return param_1 + 0x1d;
}

// 0x7100154c10 — linear search: scan param_1 stride-6 array for param_2, return index
u64 FUN_7100154c10(s32 *param_1, s32 param_2)
{
    s32 *piVar1;
    u64 uVar2;

    piVar1 = param_1 + 0xc0;
    if (*piVar1 < 1) {
        return 0xffffffff;
    }
    uVar2 = 0;
    do {
        if (*param_1 == param_2) {
            return uVar2 & 0xffffffff;
        }
        uVar2 = uVar2 + 1;
        param_1 = param_1 + 6;
    } while ((s64)uVar2 < (s64)*piVar1);
    return 0xffffffff;
}

// 0x7100154c60 — ring buffer append: write param_2 at index field+0x300, return index or -1
s32 FUN_7100154c60(s64 param_1, u32 param_2)
{
    s32 iVar1;

    if (*(s32 *)(param_1 + 0x300) < 0x20) {
        *(u32 *)(param_1 + (s64)*(s32 *)(param_1 + 0x300) * 0x18) = param_2;
        iVar1 = *(s32 *)(param_1 + 0x300);
        *(s32 *)(param_1 + 0x300) = iVar1 + 1;
        return iVar1;
    }
    return -1;
}

// 0x7100154f10 — advance circular write cursor: return ptr to next slot, or 0 if wrapped
s64 FUN_7100154f10(s64 param_1)
{
    u32 uVar1;
    u32 uVar2;
    u32 uVar3;
    s32 iVar4;
    u32 uVar5;

    uVar2 = *(u32 *)(param_1 + 0x10);
    uVar3 = *(u32 *)(param_1 + 0x14);
    uVar1 = uVar3 + 1;
    uVar5 = 0;
    if (uVar2 != 0) {
        uVar5 = uVar1 / uVar2;
    }
    iVar4 = uVar1 - uVar5 * uVar2;
    if (iVar4 == *(s32 *)(param_1 + 0x1c)) {
        return 0;
    }
    *(s32 *)(param_1 + 0x14) = iVar4;
    return *(s64 *)(param_1 + 8) + (u64)uVar3 * 0x658;
}

// 0x7100154f50 — peek circular buffer at cursor+param_2 offset, return ptr or 0
s64 FUN_7100154f50(s64 param_1, s32 param_2)
{
    u32 uVar1;
    u32 uVar2;
    u32 uVar3;

    uVar2 = *(u32 *)(param_1 + 0x10);
    uVar1 = *(s32 *)(param_1 + 0x18) + param_2;
    uVar3 = 0;
    if (uVar2 != 0) {
        uVar3 = uVar1 / uVar2;
    }
    uVar1 = uVar1 - uVar3 * uVar2;
    if (*(u32 *)(param_1 + 0x14) == uVar1) {
        return 0;
    }
    return *(s64 *)(param_1 + 8) + (u64)uVar1 * 0x658;
}

// 0x7100155000 — if field+0x20 >= 0: truncate to s32 into field+0x1c and reset to -1
void FUN_7100155000(s64 param_1)
{
    if (-1 < *(s64 *)(param_1 + 0x20)) {
        *(s32 *)(param_1 + 0x1c) = (s32)*(s64 *)(param_1 + 0x20);
        *(u64 *)(param_1 + 0x20) = 0xffffffffffffffff;
    }
}

// 0x7100156720 — network protocol ID byte → string name
const char *FUN_7100156720(u64 param_1)
{
    const char *pcVar1;

    pcVar1 = "KeepAlive";
    switch((u32)((u64)param_1 >> 0x18) & 0xff) {
    case 8:
        goto switchD_7100156748_caseD_8;
    default:
        pcVar1 = "(KickoutReason_Unknown PROTOCOL NAME)";
switchD_7100156748_caseD_8:
        return pcVar1;
    case 0x14:
        return "Station";
    case 0x18:
        return "Mesh";
    case 0x1c:
        return "SyncClock";
    case 0x24:
        return "Local";
    case 0x28:
        return "Direct";
    case 0x2c:
        return "Net";
    case 0x34:
        return "Nat";
    case 0x44:
        return "Lan";
    case 0x54:
        return "BandwidthCheck";
    case 0x58:
        return "Rtt";
    case 0x65:
        return "Sync";
    case 0x68:
        return "Unreliable";
    case 0x6c:
        return "RoundrobinUnreliable";
    case 0x73:
        return "Clone";
    case 0x74:
        return "Atomic";
    case 0x76:
        return "Event";
    case 0x77:
        return "Clock";
    case 0x78:
        return "InterpolationClock";
    case 0x7b:
        return "Voice";
    case 0x7c:
        return "Reliable";
    case 0x80:
        return "BroadcastReliable";
    case 0x81:
        return "StreamBroadcastReliable";
    case 0x84:
        return "ReliableBroadcast";
    case 0x94:
        return "Session";
    case 0x98:
        return "Lobby";
    case 0xa4:
        return "Feedback";
    case 0xa8:
        return "RelayService";
    case 0xac:
        return "WanNat";
    }
}

// 0x7100156d00 — network protocol ID → capability mask (u64)
u64 FUN_7100156d00(u16 param_1)
{
    u64 uVar1;

    uVar1 = 2;
    switch(param_1) {
    case 0x14:
        goto switchD_7100156d24_caseD_14;
    default:
        uVar1 = 0;
switchD_7100156d24_caseD_14:
        return uVar1;
    case 0x18:
        return 4;
    case 0x1c:
        return 8;
    case 0x24:
        return 0x80000;
    case 0x28:
        return 0x100000;
    case 0x2c:
        return 0x200000;
    case 0x34:
        return 0x10;
    case 0x44:
        return 0x20000;
    case 0x54:
        return 0x40000;
    case 0x58:
        return 0x20;
    case 0x65:
        return 0x40;
    case 0x68:
        return 0x80;
    case 0x6c:
        return 0x1000;
    case 0x73:
        return 0x4000;
    case 0x74:
        return 0x4000000;
    case 0x76:
        return 0x800000;
    case 0x77:
        return 0x2000000;
    case 0x78:
        return 0x2000;
    case 0x7b:
        return 0x8000;
    case 0x7c:
        return 0x100;
    case 0x80:
        return 0x10000000;
    case 0x81:
        return 0x20000000;
    case 0x84:
        return 0x200;
    case 0x94:
        return 0x10000;
    case 0x98:
        return 0x400000;
    case 0xa4:
        return 0x400;
    case 0xac:
        return 0x8000000;
    case 0xb0:
        return 0x40000000;
    case 0xb4:
        return 0x80000000;
    }
}

// 0x71001578e0 — scan byte array at param_1+0x29 for char param_2, return 1 if not found
u64 FUN_71001578e0(s64 param_1, s8 param_2)
{
    s64 lVar1;

    if (*(s32 *)(param_1 + 0x4c) < 1) {
        return 1;
    }
    lVar1 = 0;
    do {
        if (*(s8 *)(param_1 + 0x29 + lVar1) == param_2) {
            return 0;
        }
        lVar1 = lVar1 + 1;
    } while (lVar1 < *(s32 *)(param_1 + 0x4c));
    return 1;
}
