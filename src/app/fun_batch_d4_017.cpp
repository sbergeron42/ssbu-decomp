#include "types.h"

// MEDIUM-tier FUN_* functions — mixed 0x7100 ranges, batch d4-017
// Pool-d worker: auto-generated from Ghidra decompilation
// Includes: string switch, error code switch, bit-field ops, vtable dispatch loops, singleton guards

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
extern u64 PTR_LAB_7104f7fe70;

// FUN_710068d530 table + singleton globals
extern u64 PTR_PTR_710529bfd0;
extern u64 DAT_71052b8800;
extern u64 DAT_71052b8808;
extern u64 PTR_LAB_7104f83b18;

// __cxa_guard
extern "C" s32 __cxa_guard_acquire(u64 *);
extern "C" void __cxa_guard_release(u64 *);

// ---- Functions ---------------------------------------------------------------

// 0x7100156720 — protocol name string lookup: switch on bits[24..31] of param_1
const char *FUN_7100156720(u64 param_1)
{
    switch ((u32)((u64)param_1 >> 0x18) & 0xff) {
    case 8:
        return "KeepAlive";
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
    default:
        return "(KickoutReason_Unknown PROTOCOL NAME)";
    }
}

// 0x71001e1770 — map error code (param_2) to Result constant; default: copy param_3 into param_1
void FUN_71001e1770(u64 *param_1, u32 param_2, u64 *param_3)
{
    u64 uVar1;
    u64 uVar2;
    u32 local_14;

    switch (param_2) {
    case 8:
        local_14 = 0x8068000b;
        break;
    case 10:
        local_14 = 0x80680011;
        break;
    case 0xb:
        local_14 = 0x80680013;
        break;
    case 0xc:
        local_14 = 0x80680014;
        break;
    case 0xd:
        local_14 = 0x800300e2;
        break;
    case 0xe:
        local_14 = 0x8003006c;
        break;
    default:
        uVar1 = *param_3;
        uVar2 = param_3[2];
        param_1[1] = param_3[1];
        param_1[2] = uVar2;
        *param_1 = uVar1;
        return;
    }
    FUN_71001b4200(param_1, &local_14);
}

// 0x7100460760 — state machine: set param_1+0x40 = param_2, update sub-state and flags
void FUN_7100460760(s64 param_1, u32 param_2)
{
    s64 lVar1;
    s64 lVar2;
    u32 uVar3;

    *(u32 *)(param_1 + 0x40) = param_2;
    switch (param_2) {
    case 0:
        *(u32 *)(*(s64 *)(param_1 + 0x28) + 0x510) = 4;
        break;
    case 1:
        *(u32 *)(*(s64 *)(param_1 + 0x28) + 0x510) = 0;
        goto LAB_7100460830;
    case 2:
        lVar2 = *(s64 *)(param_1 + 0x28);
        uVar3 = 2;
        goto LAB_710046082c;
    case 3:
        lVar1 = (*(s64 (**)(void))(*(s64 *)(*(s64 *)(param_1 + 0x20) + 0x38) + 0x60))();
        lVar2 = (*(s64 (**)(void))(*(s64 *)(*(s64 *)(param_1 + 0x20) + 0x38) + 0x90))();
        if (*(float *)(lVar1 + 4) < *(float *)(lVar2 + 4)) {
            *(u32 *)(*(s64 *)(param_1 + 0x28) + 0x510) = 0;
        }
        break;
    case 4:
        *(u32 *)(*(s64 *)(param_1 + 0x28) + 0x510) = 2;
        break;
    case 5:
        *(u32 *)(*(s64 *)(param_1 + 0x28) + 0x510) = 1;
        break;
    case 6:
        lVar2 = *(s64 *)(param_1 + 0x28);
        uVar3 = 3;
LAB_710046082c:
        *(u32 *)(lVar2 + 0x510) = uVar3;
LAB_7100460830:
        *(u32 *)(*(s64 *)(param_1 + 0x28) + 0x5d8) =
            *(u32 *)(*(s64 *)(param_1 + 0x28) + 0x5d8) | 2;
        break;
    }
}

// 0x7100479f70 — dispatch vtable +0x10 for each non-null entry with matching mask or 0xffffffff
void FUN_7100479f70(s64 param_1, u32 param_2)
{
    s32 iVar1;
    s64 *plVar2;
    s64 lVar3;
    s64 *plVar4;

    if (*(s8 *)(param_1 + 0x1bc) == '\0') {
        iVar1 = *(s32 *)(param_1 + 0x20);
        if (param_2 == 0xffffffff) {
            if (0 < iVar1) {
                lVar3 = (s64)iVar1 + 1;
                plVar4 = (s64 *)(param_1 + (s64)iVar1 * 0x18 + 0x18);
                do {
                    plVar2 = (s64 *)*plVar4;
                    if (((s8)plVar2[6] != '\0') && (*(s8 *)((s64)plVar2 + 0x31) == '\0')) {
                        (*(void(**)(s64 *, u64))(*plVar2 + 0x10))(plVar2, *(u64 *)(param_1 + 8));
                    }
                    lVar3 = lVar3 + -1;
                    plVar4 = plVar4 + -3;
                } while (1 < lVar3);
            }
        } else if (0 < iVar1) {
            lVar3 = (s64)iVar1 + 1;
            plVar4 = (s64 *)(param_1 + (s64)iVar1 * 0x18 + 0x18);
            do {
                if ((((*(u32 *)((s64)plVar4 + 0xc) & param_2) != 0) &&
                    (plVar2 = (s64 *)*plVar4, (s8)plVar2[6] != '\0')) &&
                   (*(s8 *)((s64)plVar2 + 0x31) == '\0')) {
                    (*(void(**)(s64 *, u64))(*plVar2 + 0x10))(plVar2, *(u64 *)(param_1 + 8));
                }
                lVar3 = lVar3 + -1;
                plVar4 = plVar4 + -3;
            } while (1 < lVar3);
        }
    }
}

// 0x710047a060 — dispatch vtable +0x18 for each non-null entry with matching mask or 0xffffffff
void FUN_710047a060(s64 param_1, u32 param_2)
{
    s32 iVar1;
    s64 *plVar2;
    s64 lVar3;
    s64 *plVar4;

    if (*(s8 *)(param_1 + 0x1bc) == '\0') {
        iVar1 = *(s32 *)(param_1 + 0x20);
        if (param_2 == 0xffffffff) {
            if (0 < iVar1) {
                lVar3 = (s64)iVar1 + 1;
                plVar4 = (s64 *)(param_1 + (s64)iVar1 * 0x18 + 0x18);
                do {
                    plVar2 = (s64 *)*plVar4;
                    if (((s8)plVar2[6] != '\0') && (*(s8 *)((s64)plVar2 + 0x31) == '\0')) {
                        (*(void(**)(s64 *, u64))(*plVar2 + 0x18))(plVar2, *(u64 *)(param_1 + 8));
                    }
                    lVar3 = lVar3 + -1;
                    plVar4 = plVar4 + -3;
                } while (1 < lVar3);
            }
        } else if (0 < iVar1) {
            lVar3 = (s64)iVar1 + 1;
            plVar4 = (s64 *)(param_1 + (s64)iVar1 * 0x18 + 0x18);
            do {
                if ((((*(u32 *)((s64)plVar4 + 0xc) & param_2) != 0) &&
                    (plVar2 = (s64 *)*plVar4, (s8)plVar2[6] != '\0')) &&
                   (*(s8 *)((s64)plVar2 + 0x31) == '\0')) {
                    (*(void(**)(s64 *, u64))(*plVar2 + 0x18))(plVar2, *(u64 *)(param_1 + 8));
                }
                lVar3 = lVar3 + -1;
                plVar4 = plVar4 + -3;
            } while (1 < lVar3);
        }
    }
}

// 0x710047cda0 — find matching node by param_3, fill param_4 fields, link into lists
s64 FUN_710047cda0(s64 param_1, s64 param_2, s32 param_3, s64 param_4)
{
    u64 *puVar1;
    u32 uVar2;
    s64 lVar3;
    s64 *plVar4;
    u64 uVar5;
    u8 *local_40;
    u32 local_38;
    u64 local_30;
    u64 uStack_28;
    u64 local_20;
    u8 local_18;

    if (*(s32 *)(param_1 + 0x18) == 0) {
        return 0;
    }
    plVar4 = *(s64 **)(param_1 + 8);
    if (plVar4 != (s64 *)0x0) {
        do {
            lVar3 = plVar4[2];
            if (*(s32 *)(*(s64 *)(lVar3 + 8) + 8) == param_3) {
                if (lVar3 != 0) {
                    uVar2 = *(u32 *)(*(s64 *)(param_2 + 8) + 8);
                    *(s64 *)(param_4 + 0x30) = param_2;
                    *(s32 *)(param_4 + 0x48) = param_3;
                    *(s64 *)(param_4 + 0x58) = lVar3;
                    *(u8 *)(param_4 + 0x65) = 1;
                    *(u32 *)(param_4 + 0x20) = uVar2;
                    puVar1 = (u64 *)(param_4 + 0x38);
                    if (*(s32 *)(param_2 + 0x48) == 0) {
                        if (*(s64 *)(param_2 + 0x38) != 0) {
                            *(u64 **)(*(s64 *)(param_2 + 0x38) + 8) = puVar1;
                            *puVar1 = *(u64 *)(param_2 + 0x38);
                        }
                        *(u64 **)(param_2 + 0x38) = puVar1;
                    } else {
                        uVar5 = *(u64 *)(param_2 + 0x40);
                        *(u64 *)(param_4 + 0x38) = 0;
                        *(u64 *)(param_4 + 0x40) = uVar5;
                        **(s64 **)(param_2 + 0x40) = (s64)puVar1;
                    }
                    *(u64 **)(param_2 + 0x40) = puVar1;
                    *(s32 *)(param_2 + 0x48) = *(s32 *)(param_2 + 0x48) + 1;
                    puVar1 = (u64 *)(param_4 + 0x10);
                    if (*(s32 *)(lVar3 + 0x30) == 0) {
                        if (*(s64 *)(lVar3 + 0x20) != 0) {
                            *(u64 **)(*(s64 *)(lVar3 + 0x20) + 8) = puVar1;
                            *puVar1 = *(u64 *)(lVar3 + 0x20);
                        }
                        *(u64 **)(lVar3 + 0x20) = puVar1;
                    } else {
                        uVar5 = *(u64 *)(lVar3 + 0x28);
                        *(u64 *)(param_4 + 0x10) = 0;
                        *(u64 *)(param_4 + 0x18) = uVar5;
                        **(s64 **)(lVar3 + 0x28) = (s64)puVar1;
                    }
                    *(u64 **)(lVar3 + 0x28) = puVar1;
                    *(s32 *)(lVar3 + 0x30) = *(s32 *)(lVar3 + 0x30) + 1;
                    local_38 = 10;
                    local_30 = 0xbcd988648ULL;
                    uStack_28 = 0;
                    local_40 = &DAT_71050b33c8;
                    local_18 = 0;
                    local_20 = 0xffffffff50000000ULL;
                    FUN_7100489b00(lVar3, param_2, &local_40, *(u8 *)(param_4 + 100));
                    lVar3 = 1;
                }
                return lVar3;
            }
            plVar4 = (s64 *)*plVar4;
        } while (plVar4 != (s64 *)0x0);
        return 0;
    }
    return 0;
}

// 0x71004c16f0 — write param_3 into bit-field of *(param_4+0xc) at bit position determined by param_2
void FUN_71004c16f0(s32 param_1, u32 param_2, u32 param_3, s64 param_4)
{
    u32 uVar1;

    if ((param_4 != 0) && (param_1 != 0)) {
        switch (param_2) {
        case 0:
            uVar1 = *(u32 *)(param_4 + 0xc) & 0xffffff80 | param_3 & 0x7f;
            break;
        case 1:
            uVar1 = *(u32 *)(param_4 + 0xc) & 0xffffe000 |
                    *(u32 *)(param_4 + 0xc) & 0x7f | (param_3 & 0x3f) << 7;
            break;
        case 2:
            uVar1 = *(u32 *)(param_4 + 0xc) & 0xffff0000 |
                    *(u32 *)(param_4 + 0xc) & 0x1fff | (param_3 & 7) << 0xd;
            break;
        case 3:
            uVar1 = *(u32 *)(param_4 + 0xc) & 0xffe00000 |
                    *(u32 *)(param_4 + 0xc) & 0xffff | (param_3 & 0x1f) << 0x10;
            break;
        case 4:
            uVar1 = *(u32 *)(param_4 + 0xc) & 0xff000000 |
                    *(u32 *)(param_4 + 0xc) & 0x1fffff | (param_3 & 7) << 0x15;
            break;
        case 5:
            uVar1 = *(u32 *)(param_4 + 0xc) & 0xf8000000 |
                    *(u32 *)(param_4 + 0xc) & 0xffffff | (param_3 & 7) << 0x18;
            break;
        case 6:
            uVar1 = *(u32 *)(param_4 + 0xc) & 0xe0000000 |
                    *(u32 *)(param_4 + 0xc) & 0x7ffffff | (param_3 & 3) << 0x1b;
            break;
        case 7:
            uVar1 = *(u32 *)(param_4 + 0xc) & 0x1fffffff | param_3 << 0x1d;
            break;
        default:
            return;
        }
        *(u32 *)(param_4 + 0xc) = uVar1;
    }
}

// 0x710064c290 — write vtable label ptr + param_1+8 field into param_2[0..1]
void FUN_710064c290(s64 param_1, u64 *param_2)
{
    *param_2 = (u64)&PTR_LAB_7104f7fe70;
    param_2[1] = *(u64 *)(param_1 + 8);
}

// 0x710065dcc0 — map opcode pair: remap certain (opcode, -1) or (0x4b, 0x4c) combos
u32 FUN_710065dcc0(u32 *param_1)
{
    switch (*param_1) {
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

// 0x710065dd70 — return 1 if param_1 is one of the recognized opcode values, else 0
u64 FUN_710065dd70(u32 param_1)
{
    switch (param_1) {
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
u8 FUN_710067a3a0(s64 param_1, u32 param_2)
{
    s64 lVar1;

    if ((param_2 & 1) == 0) {
        return '\0' < *(s8 *)(param_1 + 0xbc);
    }
    lVar1 = *(s64 *)(param_1 + 0x20);
    if (lVar1 != 0) {
        if (((&DAT_00005920)[lVar1] == '\x03') && (*(s8 *)(lVar1 + 0x44d2) != '\0')) {
            return 1;
        }
        if (*(s8 *)(lVar1 + 0x5921) != '\0') {
            return 1;
        }
    }
    lVar1 = *(s64 *)(param_1 + 0x28);
    if (lVar1 != 0) {
        if (((&DAT_00005920)[lVar1] == '\x03') && (*(s8 *)(lVar1 + 0x44d2) != '\0')) {
            return 1;
        }
        if (*(s8 *)(lVar1 + 0x5921) != '\0') {
            return 1;
        }
    }
    lVar1 = *(s64 *)(param_1 + 0x30);
    if (lVar1 != 0) {
        if (((&DAT_00005920)[lVar1] == '\x03') && (*(s8 *)(lVar1 + 0x44d2) != '\0')) {
            return 1;
        }
        if (*(s8 *)(lVar1 + 0x5921) != '\0') {
            return 1;
        }
    }
    lVar1 = *(s64 *)(param_1 + 0x38);
    if (lVar1 != 0) {
        if (((&DAT_00005920)[lVar1] == '\x03') && (*(s8 *)(lVar1 + 0x44d2) != '\0')) {
            return 1;
        }
        if (*(s8 *)(lVar1 + 0x5921) != '\0') {
            return 1;
        }
    }
    lVar1 = *(s64 *)(param_1 + 0x40);
    if (lVar1 != 0) {
        if (((&DAT_00005920)[lVar1] == '\x03') && (*(s8 *)(lVar1 + 0x44d2) != '\0')) {
            return 1;
        }
        if (*(s8 *)(lVar1 + 0x5921) != '\0') {
            return 1;
        }
    }
    lVar1 = *(s64 *)(param_1 + 0x48);
    if (lVar1 != 0) {
        if (((&DAT_00005920)[lVar1] == '\x03') && (*(s8 *)(lVar1 + 0x44d2) != '\0')) {
            return 1;
        }
        if (*(s8 *)(lVar1 + 0x5921) != '\0') {
            return 1;
        }
    }
    lVar1 = *(s64 *)(param_1 + 0x50);
    if (lVar1 != 0) {
        if (((&DAT_00005920)[lVar1] == '\x03') && (*(s8 *)(lVar1 + 0x44d2) != '\0')) {
            return 1;
        }
        if (*(s8 *)(lVar1 + 0x5921) != '\0') {
            return 1;
        }
    }
    lVar1 = *(s64 *)(param_1 + 0x58);
    if (lVar1 != 0) {
        if (((&DAT_00005920)[lVar1] == '\x03') && (*(s8 *)(lVar1 + 0x44d2) != '\0')) {
            return 1;
        }
        if (*(s8 *)(lVar1 + 0x5921) != '\0') {
            return 1;
        }
    }
    return 0;
}

// 0x710067a5c0 — check if any of 8 slot ptrs has (type!=3 or no flag) and state>1; u64 return
u64 FUN_710067a5c0(s64 param_1)
{
    s64 lVar1;

    lVar1 = *(s64 *)(param_1 + 0x20);
    if ((lVar1 != 0) &&
       ((((&DAT_00005920)[lVar1] != '\x03' || (*(s8 *)(lVar1 + 0x44d2) == '\0')) &&
        (1 < *(u8 *)(lVar1 + 0x5921))))) {
        return 1;
    }
    lVar1 = *(s64 *)(param_1 + 0x28);
    if ((lVar1 != 0) &&
       ((((&DAT_00005920)[lVar1] != '\x03' || (*(s8 *)(lVar1 + 0x44d2) == '\0')) &&
        (1 < *(u8 *)(lVar1 + 0x5921))))) {
        return 1;
    }
    lVar1 = *(s64 *)(param_1 + 0x30);
    if (((lVar1 != 0) && (((&DAT_00005920)[lVar1] != '\x03' || (*(s8 *)(lVar1 + 0x44d2) == '\0'))))
       && (1 < *(u8 *)(lVar1 + 0x5921))) {
        return 1;
    }
    lVar1 = *(s64 *)(param_1 + 0x38);
    if ((lVar1 != 0) &&
       ((((&DAT_00005920)[lVar1] != '\x03' || (*(s8 *)(lVar1 + 0x44d2) == '\0')) &&
        (1 < *(u8 *)(lVar1 + 0x5921))))) {
        return 1;
    }
    lVar1 = *(s64 *)(param_1 + 0x40);
    if ((lVar1 != 0) &&
       ((((&DAT_00005920)[lVar1] != '\x03' || (*(s8 *)(lVar1 + 0x44d2) == '\0')) &&
        (1 < *(u8 *)(lVar1 + 0x5921))))) {
        return 1;
    }
    lVar1 = *(s64 *)(param_1 + 0x48);
    if (((lVar1 != 0) && (((&DAT_00005920)[lVar1] != '\x03' || (*(s8 *)(lVar1 + 0x44d2) == '\0'))))
       && (1 < *(u8 *)(lVar1 + 0x5921))) {
        return 1;
    }
    lVar1 = *(s64 *)(param_1 + 0x50);
    if ((lVar1 != 0) &&
       ((((&DAT_00005920)[lVar1] != '\x03' || (*(s8 *)(lVar1 + 0x44d2) == '\0')) &&
        (1 < *(u8 *)(lVar1 + 0x5921))))) {
        return 1;
    }
    lVar1 = *(s64 *)(param_1 + 0x58);
    if (((lVar1 != 0) && (((&DAT_00005920)[lVar1] != '\x03' || (*(s8 *)(lVar1 + 0x44d2) == '\0'))))
       && (1 < *(u8 *)(lVar1 + 0x5921))) {
        return 1;
    }
    return 0;
}

// 0x710067e670 — dispatch FUN_710065d450 to each of 8 slot ptrs if condition met
void FUN_710067e670(s64 param_1, s32 param_2, s32 param_3)
{
    s64 lVar1;

    if (((param_3 != 6) && (3 < (u32)(param_3 - 0x4d))) && (-1 < param_3)) {
        lVar1 = *(s64 *)(param_1 + 0x20);
        if ((lVar1 != 0) && (*(s32 *)(lVar1 + 0xe0) != param_2)) {
            FUN_710065d450(lVar1, param_3, param_2);
        }
        lVar1 = *(s64 *)(param_1 + 0x28);
        if ((lVar1 != 0) && (*(s32 *)(lVar1 + 0xe0) != param_2)) {
            FUN_710065d450(lVar1, param_3, param_2);
        }
        lVar1 = *(s64 *)(param_1 + 0x30);
        if ((lVar1 != 0) && (*(s32 *)(lVar1 + 0xe0) != param_2)) {
            FUN_710065d450(lVar1, param_3, param_2);
        }
        lVar1 = *(s64 *)(param_1 + 0x38);
        if ((lVar1 != 0) && (*(s32 *)(lVar1 + 0xe0) != param_2)) {
            FUN_710065d450(lVar1, param_3, param_2);
        }
        lVar1 = *(s64 *)(param_1 + 0x40);
        if ((lVar1 != 0) && (*(s32 *)(lVar1 + 0xe0) != param_2)) {
            FUN_710065d450(lVar1, param_3, param_2);
        }
        lVar1 = *(s64 *)(param_1 + 0x48);
        if ((lVar1 != 0) && (*(s32 *)(lVar1 + 0xe0) != param_2)) {
            FUN_710065d450(lVar1, param_3, param_2);
        }
        lVar1 = *(s64 *)(param_1 + 0x50);
        if ((lVar1 != 0) && (*(s32 *)(lVar1 + 0xe0) != param_2)) {
            FUN_710065d450(lVar1, param_3, param_2);
        }
        lVar1 = *(s64 *)(param_1 + 0x58);
        if ((lVar1 != 0) && (*(s32 *)(lVar1 + 0xe0) != param_2)) {
            FUN_710065d450(lVar1, param_3, param_2);
        }
    }
}

// 0x710068d530 — table lookup for param_1 < 0x5e, else singleton guard init; return u64*
u64 *FUN_710068d530(u32 param_1)
{
    s32 iVar1;

    if (param_1 < 0x5e) {
        return (u64 *)(&PTR_PTR_710529bfd0)[(s32)param_1];
    }
    if (((DAT_71052b8800 & 1) == 0) && (iVar1 = __cxa_guard_acquire(&DAT_71052b8800), iVar1 != 0)) {
        DAT_71052b8808 = (u64)&PTR_LAB_7104f83b18;
        __cxa_guard_release(&DAT_71052b8800);
    }
    return &DAT_71052b8808;
}
