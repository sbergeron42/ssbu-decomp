#include "types.h"

// MEDIUM-tier FUN_* functions — mixed 0x7101 ranges, batch d4-019
// Pool-d worker: auto-generated from Ghidra decompilation
// Includes: vtable dispatch, singleton guard, abort wrappers, FNV hash switches, struct copies, nested switch

// ---- External declarations -----------------------------------------------

// Singleton guard globals (FUN_71012859f0)
extern u64 DAT_71052c1b00;
extern u64 DAT_71052c1b08;
extern u8  PTR_LAB_7105051418;

// PTR_LAB globals for struct-copy functions
extern u8 PTR_LAB_7105079ed0;
extern u8 PTR_LAB_71050806a8;

extern "C" s32 __cxa_guard_acquire(u64 *);
extern "C" void __cxa_guard_release(u64 *);
extern "C" void abort();

namespace std { namespace __1 {
    template<bool> struct __vector_base_common {
        [[noreturn]] static void __throw_out_of_range();
    };
}}

// ---- Functions ---------------------------------------------------------------

// 0x710116b7f0 — vtable dispatch: call vfunc via nested ptr at param+0x20→+0x40→vtable+0x110, return 1 if opcode in set
u64 FUN_710116b7f0(s64 param_1)
{
    s32 iVar1;

    iVar1 = (*(s32(**)(void))(**(s64**)(*(s64*)(param_1 + 0x20) + 0x40) + 0x110))();
    if (iVar1 < 0xd0) {
        switch (iVar1) {
        case 0: case 1: case 3: case 4: case 0xb: case 0xc: case 0xd: case 0xe: case 0xf:
        case 0x16: case 0x17: case 0x18: case 0x1a: case 0x7f: case 0xa7: case 0xa8: case 0xa9:
            goto switchD_710116b838_caseD_2;
        default:
            return 0;
        }
    }
    if (iVar1 < 0x11e) {
        if ((iVar1 != 0xd0) && (iVar1 != 0x11b)) {
            return 0;
        }
    } else if (((iVar1 != 0x11e) && (iVar1 != 0x2ce)) && (iVar1 != 0x1dc)) {
        return 0;
    }
switchD_710116b838_caseD_2:
    return 1;
}

// 0x710116d8a0 — vtable dispatch: same pattern as 710116b7f0 but with larger opcode set
u64 FUN_710116d8a0(s64 param_1)
{
    s32 iVar1;

    iVar1 = (*(s32(**)(void))(**(s64**)(*(s64*)(param_1 + 0x20) + 0x40) + 0x110))();
    if (iVar1 < 0x149) {
        switch (iVar1) {
        case 0: case 1: case 3: case 4: case 6: case 7: case 8: case 0xb: case 0xc: case 0xe:
        case 0xf: case 0x16: case 0x17: case 0x18: case 0x1a: case 0x47: case 0x48: case 0x49:
        case 0x4a: case 0x4b: case 0x4c: case 0x4d: case 0x4e: case 0x4f: case 0x50: case 0x53:
        case 0x57: case 0x58: case 0x59: case 0x7f:
            goto switchD_710116d8e8_caseD_2;
        default:
            return 0;
        }
    }
    if (iVar1 < 0x1dc) {
        if ((iVar1 != 0x149) && (iVar1 != 0x14c)) {
            return 0;
        }
    } else if ((iVar1 != 0x2ce) && (iVar1 != 0x1dc)) {
        return 0;
    }
switchD_710116d8e8_caseD_2:
    return 1;
}

// 0x71012859f0 — singleton guard: init vtable ptr DAT_71052c1b08, write ptr to param_2+0x318, set +0xe8=6
void FUN_71012859f0(u64 param_1, s64 param_2)
{
    s32 iVar1;

    if ((DAT_71052c1b00 & 1) == 0) {
        iVar1 = __cxa_guard_acquire(&DAT_71052c1b00);
        if (iVar1 != 0) {
            DAT_71052c1b08 = (u64)&PTR_LAB_7105051418;
            __cxa_guard_release(&DAT_71052c1b00);
        }
    }
    *(u64**)(param_2 + 0x318) = &DAT_71052c1b08;
    *(u8*)(param_2 + 0xe8) = 6;
}

// 0x71013c8300 — opcode-type map: switch on param_1 [0..0x2c], return constant code; param_2 used for cases 3 and 0x18
u32 FUN_71013c8300(u32 param_1, s32 param_2)
{
    u32 uVar1;

    uVar1 = 0x500d;
    switch (param_1) {
    case 0:
        goto switchD_71013c8324_caseD_0;
    case 1:    return 0x5001;
    case 2:    return 0x500e;
    case 3:
        uVar1 = 0x5003;
        if (param_2 == 0) { uVar1 = 0x5004; }
        return uVar1;
    case 4:    return 0x5005;
    case 5:    return 0x10304;
    case 6:    return 0x10302;
    case 7:    return 0x5011;
    case 8:    return 0x5010;
    case 9:    return 0x5013;
    case 10:   return 0x500b;
    case 0xb:  return 0x5002;
    case 0xc:
    case 0x1b: return 0x10303;
    case 0xd:  return 0x10305;
    case 0xe:  return 0x5015;
    case 0xf:  return 0x5007;
    case 0x10: return 0x22000;
    case 0x11: return 0x5009;
    case 0x12: return 0x5012;
    case 0x13: return 0x5014;
    case 0x14:
    case 0x2b:
    case 0x2c: return 0x100000;
    case 0x15: return 0x500a;
    case 0x16: return 0x5008;
    case 0x17: return 0x5006;
    case 0x18:
        uVar1 = 0x51000;
        if (param_2 != 0) { uVar1 = 0x5017; }
        return uVar1;
    case 0x19: return 0x5016;
    case 0x1a: return 0x500c;
    case 0x1c: return 0x500f;
    case 0x1d: return 0x10300;
    default:
        uVar1 = 0;
switchD_71013c8324_caseD_0:
        return uVar1;
    case 0x28:
    case 0x29:
    case 0x2a: return 0x5011;
    }
}

// 0x710135de10 — abort wrapper
void FUN_710135de10(void)
{
    abort();
}

// 0x71013ccd48 — abort wrapper
void FUN_71013ccd48(void)
{
    abort();
}

// 0x71013e4048 — abort wrapper
void FUN_71013e4048(void)
{
    abort();
}

// 0x71013fea54 — std::vector out-of-range wrapper
void FUN_71013fea54(void)
{
    std::__1::__vector_base_common<true>::__throw_out_of_range();
}

// 0x710140b190 — set queue entry 8 or 9 based on byte flags at +0x18c/+0x18d
void FUN_710140b190(s64 param_1)
{
    if (*(s8*)(param_1 + 0x18c) != 0) {
        if (*(u32*)(param_1 + 300) < 0x13) {
            *(u32*)(param_1 + (s64)(s32)*(u32*)(param_1 + 300) * 4 + 0xe0) = 8;
            *(u8*)(param_1 + 0x18c) = 0;
            return;
        }
        abort();
    }
    if (*(s8*)(param_1 + 0x18d) != 0) {
        if (0x12 < *(u32*)(param_1 + 300)) abort();
        *(u32*)(param_1 + (s64)(s32)*(u32*)(param_1 + 300) * 4 + 0xe0) = 9;
        *(u8*)(param_1 + 0x18d) = 0;
    }
}

// 0x710140b2e0 — set queue entry 8, 9, or 4 based on byte flags at +0x18c/+0x18d and int compare
void FUN_710140b2e0(s64 param_1)
{
    if (*(s8*)(param_1 + 0x18c) == 0) {
        if (*(s8*)(param_1 + 0x18d) == 0) {
            if (*(s32*)(param_1 + 0x184) != *(s32*)(param_1 + 0x188)) {
                if (0x12 < *(u32*)(param_1 + 300)) abort();
                *(u32*)(param_1 + (s64)(s32)*(u32*)(param_1 + 300) * 4 + 0xe0) = 4;
            }
            return;
        }
        if (*(u32*)(param_1 + 300) < 0x13) {
            *(u32*)(param_1 + (s64)(s32)*(u32*)(param_1 + 300) * 4 + 0xe0) = 9;
            *(u8*)(param_1 + 0x18d) = 0;
            return;
        }
    } else if (*(u32*)(param_1 + 300) < 0x13) {
        *(u32*)(param_1 + (s64)(s32)*(u32*)(param_1 + 300) * 4 + 0xe0) = 8;
        *(u8*)(param_1 + 0x18c) = 0;
        return;
    }
    abort();
}

// 0x71014150e8 — abort wrapper
void FUN_71014150e8(void)
{
    abort();
}

// 0x7101415210 — bounds-checked bit-field test: param_2 in [0..7], param_3 in [0..2]
u64 FUN_7101415210(s64 param_1, s32 param_2, u32 param_3)
{
    if (param_2 == -1) {
        return 0;
    }
    if (((u64)(s64)param_2 < 8) && (param_3 < 3)) {
        return (*(u64*)(*(s64*)(param_1 + 8) + (s64)param_2 * 8 + 800) &
               (u64)(1LL << ((s64)(s32)param_3 & 0x3f))) != 0;
    }
    abort();
}

// 0x7101657920 — struct copy: set PTR_LAB as vtable, copy 5 u64 fields from param_1+8..+0x28
void FUN_7101657920(s64 param_1, u64 *param_2)
{
    u64 uVar1;
    u64 uVar2;
    u64 uVar3;

    *param_2 = (u64)&PTR_LAB_7105079ed0;
    param_2[1] = *(u64*)(param_1 + 8);
    uVar1 = *(u64*)(param_1 + 0x10);
    uVar2 = *(u64*)(param_1 + 0x18);
    uVar3 = *(u64*)(param_1 + 0x28);
    param_2[4] = *(u64*)(param_1 + 0x20);
    param_2[5] = uVar3;
    param_2[2] = uVar1;
    param_2[3] = uVar2;
}

// 0x7101677120 — struct copy: set PTR_LAB as vtable, copy 3 u64 fields from param_1+8..+0x18
void FUN_7101677120(s64 param_1, u64 *param_2)
{
    u64 uVar1;
    u64 uVar2;

    *param_2 = (u64)&PTR_LAB_71050806a8;
    uVar1 = *(u64*)(param_1 + 8);
    uVar2 = *(u64*)(param_1 + 0x18);
    param_2[2] = *(u64*)(param_1 + 0x10);
    param_2[3] = uVar2;
    param_2[1] = uVar1;
}

// 0x7101c6ec50 — FNV hash: pack color_N name string into param_1 struct based on param_2 index (0..8)
void FUN_7101c6ec50(u32 *param_1, u8 param_2)
{
    u32 uVar1;
    u8 *pbVar2;
    u32 uVar3;

    uVar1 = 0x811c9dc5;
    *(u8*)(param_1 + 4) = 0;
    param_1[0] = 0;
    param_1[1] = 8;
    param_1[2] = 0x6f6c6f63; // "colo"
    switch (param_2) {
    case 1: param_1[3] = 0x35305f72; break; // "r_05"
    case 2: param_1[3] = 0x34305f72; break; // "r_04"
    case 3: param_1[3] = 0x33305f72; break; // "r_03"
    case 4: param_1[3] = 0x32305f72; break; // "r_02"
    case 5: param_1[3] = 0x31305f72; break; // "r_01"
    case 7: param_1[3] = 0x36305f72; break; // "r_06"
    case 8: param_1[3] = 0x31315f72; break; // "r_11"
    default: param_1[3] = 0x30305f72; break; // "r_00"
    }
    uVar3 = 99; // 'c'
    pbVar2 = (u8*)((s64)param_1 + 9);
    do {
        uVar1 = uVar1 * 0x89 ^ uVar3;
        uVar3 = (u32)*pbVar2;
        pbVar2++;
    } while (uVar3 != 0);
    *param_1 = uVar1;
}

// 0x7101c6ee80 — FNV hash: pack mnu_online_room_purpose_* string into param_1 struct (cases 0..8)
void FUN_7101c6ee80(u32 *param_1, u8 param_2)
{
    u32 uVar1;
    u8 *pbVar2;
    u32 uVar3;

    uVar1 = 0x811c9dc5;
    switch (param_2) {
    case 0:
        param_1[0] = 0;
        param_1[1] = 0x1b;
        param_1[2] = 0x5f756e6d;
        param_1[3] = 0x696c6e6f;
        *(u16*)(param_1 + 6) = 0x7570;
        param_1[4] = 0x725f656e;
        param_1[5] = 0x5f6d6f6f;
        *(u64*)((s64)param_1 + 0x1a) = 0x6c615f65736f7072;
        *(u16*)((s64)param_1 + 0x22) = 0x6c;
        break;
    case 1:
        *(u8*)((s64)param_1 + 0x26) = 0;
        param_1[0] = 0;
        param_1[1] = 0x1e;
        param_1[2] = 0x5f756e6d;
        param_1[3] = 0x696c6e6f;
        param_1[4] = 0x725f656e;
        param_1[5] = 0x5f6d6f6f;
        *(u16*)(param_1 + 6) = 0x7570;
        *(u64*)((s64)param_1 + 0x1a) = 0x6e615f65736f7072;
        *(u32*)((s64)param_1 + 0x22) = 0x656e6f79;
        break;
    case 2:
        param_1[0] = 0;
        param_1[1] = 0x1f;
        param_1[2] = 0x5f756e6d;
        param_1[3] = 0x696c6e6f;
        param_1[4] = 0x725f656e;
        param_1[5] = 0x5f6d6f6f;
        *(u16*)(param_1 + 6) = 0x7570;
        *(u64*)((s64)param_1 + 0x1a) = 0x65735f65736f7072;
        *(u32*)((s64)param_1 + 0x22) = 0x756f6972;
        *(u16*)((s64)param_1 + 0x26) = 0x73;
        break;
    case 3:
        *(u8*)(param_1 + 10) = 0;
        param_1[0] = 0;
        param_1[1] = 0x20;
        param_1[2] = 0x5f756e6d;
        param_1[3] = 0x696c6e6f;
        param_1[4] = 0x725f656e;
        param_1[5] = 0x5f6d6f6f;
        *(u16*)(param_1 + 6) = 0x7570;
        *(u64*)((s64)param_1 + 0x1a) = 0x65625f65736f7072;
        *(u32*)((s64)param_1 + 0x22) = 0x6e6e6967;
        *(u16*)((s64)param_1 + 0x26) = 0x7265;
        break;
    case 4:
        param_1[0] = 0;
        param_1[1] = 0x2b;
        param_1[2] = 0x5f756e6d;
        param_1[3] = 0x696c6e6f;
        param_1[4] = 0x725f656e;
        param_1[5] = 0x5f6d6f6f;
        *(u16*)(param_1 + 6) = 0x7570;
        *(u64*)((s64)param_1 + 0x1a) = 0x6e695f65736f7072;
        *(u32*)((s64)param_1 + 0x22) = 0x6d726574;
        *(u16*)((s64)param_1 + 0x26) = 0x6465;
        param_1[10] = 0x65746169;
        param_1[11] = 0x6e65735f;
        *(u32*)(param_1 + 12) = 0x726f69;
        break;
    case 5:
        *(u8*)(param_1 + 10) = 0;
        param_1[0] = 0;
        param_1[1] = 0x20;
        param_1[2] = 0x5f756e6d;
        param_1[3] = 0x696c6e6f;
        param_1[4] = 0x725f656e;
        param_1[5] = 0x5f6d6f6f;
        *(u16*)(param_1 + 6) = 0x7570;
        *(u64*)((s64)param_1 + 0x1a) = 0x6e615f65736f7072;
        *(u32*)((s64)param_1 + 0x22) = 0x69687479;
        *(u16*)((s64)param_1 + 0x26) = 0x676e;
        break;
    default:
        *(u8*)(param_1 + 9) = 0;
        param_1[0] = 0;
        param_1[1] = 0x1c;
        param_1[2] = 0x5f756e6d;
        param_1[3] = 0x696c6e6f;
        param_1[4] = 0x725f656e;
        param_1[5] = 0x5f6d6f6f;
        *(u16*)(param_1 + 6) = 0x7570;
        *(u64*)((s64)param_1 + 0x1a) = 0x72665f65736f7072;
        *(u16*)((s64)param_1 + 0x22) = 0x6565;
        break;
    case 7:
        *(u8*)((s64)param_1 + 0x26) = 0;
        param_1[0] = 0;
        param_1[1] = 0x1e;
        param_1[2] = 0x5f756e6d;
        param_1[3] = 0x696c6e6f;
        param_1[4] = 0x725f656e;
        param_1[5] = 0x5f6d6f6f;
        *(u16*)(param_1 + 6) = 0x7570;
        *(u64*)((s64)param_1 + 0x1a) = 0x6d615f65736f7072;
        *(u32*)((s64)param_1 + 0x22) = 0x6f626969;
        break;
    case 8:
        param_1[0] = 0;
        param_1[1] = 0x1b;
        param_1[2] = 0x5f756e6d;
        param_1[3] = 0x696c6e6f;
        *(u16*)(param_1 + 6) = 0x7570;
        param_1[4] = 0x725f656e;
        param_1[5] = 0x5f6d6f6f;
        *(u64*)((s64)param_1 + 0x1a) = 0x69765f65736f7072;
        *(u16*)((s64)param_1 + 0x22) = 0x70;
        break;
    }
    uVar3 = 0x6d; // 'm'
    pbVar2 = (u8*)((s64)param_1 + 9);
    do {
        uVar1 = uVar1 * 0x89 ^ uVar3;
        uVar3 = (u32)*pbVar2;
        pbVar2++;
    } while (uVar3 != 0);
    *param_1 = uVar1;
}

// 0x7101c70500 — string table: return mnu_online_room_inside_sysmsg_* for given message id
const char *FUN_7101c70500(u8 param_1)
{
    const char *pcVar1;

    pcVar1 = "mnu_online_room_inside_sysmsg_enter";
    switch (param_1) {
    case 1:
        goto switchD_7101c70528_caseD_1;
    case 2:
    case 3:
        return "mnu_online_room_inside_sysmsg_leave";
    case 4:
        return "mnu_online_room_inside_sysmsg_10ko";
    case 5:
        return "mnu_online_room_inside_sysmsg_30ko";
    case 6:
        return "mnu_online_room_inside_sysmsg_50ko";
    case 7:
        return "mnu_online_room_inside_sysmsg_100ko";
    default:
        pcVar1 = "";
switchD_7101c70528_caseD_1:
        return pcVar1;
    case 9:
        return "mnu_online_room_inside_sysmsg_battle_finish";
    case 10:
        return "mnu_online_room_inside_sysmsg_cannot_battle";
    case 100:
        return "mnu_online_room_inside_sysmsg_battle_start";
    case 0x65:
        return "mnu_online_room_inside_sysmsg_battle_start_c";
    case 0x66:
        return "mnu_online_room_inside_sysmsg_winning_streak";
    case 0x67:
        return "mnu_online_room_inside_chat_own";
    case 0x68:
        return "mnu_online_room_inside_chat_others";
    case 0x69:
        return "mnu_online_room_inside_sysmsg_rule_changing";
    case 0x6a:
        return "mnu_online_room_inside_sysmsg_rule_change";
    case 0x6b:
        return "mnu_online_room_inside_sysmsg_rule_0";
    case 0x6c:
    case 0x6d:
    case 0x6e:
        return "mnu_online_room_inside_sysmsg_rule_1";
    case 0x6f:
        return "mnu_online_room_inside_sysmsg_rule_2";
    case 0x70:
        return "mnu_online_room_inside_sysmsg_rule_3";
    case 0x71:
        return "mnu_online_room_inside_sysmsg_rule_no_change";
    }
}

// 0x7101d2c6b0 — mismatch check: load two char fields from param_1 indexed by (param_2, param_3), compare
u64 FUN_7101d2c6b0(s64 param_1, s32 param_2, u32 param_3)
{
    s8 cVar1;
    s8 cVar2;

    if (param_2 == 2) {
        switch (param_3) {
        case 0:  cVar1 = *(s8*)(param_1 + 0x58); cVar2 = *(s8*)(param_1 + 0xb8); break;
        case 1:  cVar1 = *(s8*)(param_1 + 0x59); cVar2 = *(s8*)(param_1 + 0xb9); break;
        case 2:  cVar1 = *(s8*)(param_1 + 0x5a); cVar2 = *(s8*)(param_1 + 0xba); break;
        case 3:  cVar1 = *(s8*)(param_1 + 0x5b); cVar2 = *(s8*)(param_1 + 0xbb); break;
        case 4:  cVar1 = *(s8*)(param_1 + 0x5c); cVar2 = *(s8*)(param_1 + 0xbc); break;
        case 5:  cVar1 = *(s8*)(param_1 + 0x5d); cVar2 = *(s8*)(param_1 + 0xbd); break;
        case 6:  cVar1 = *(s8*)(param_1 + 0x5e); cVar2 = *(s8*)(param_1 + 0xbe); break;
        case 7:  cVar1 = *(s8*)(param_1 + 0x5f); cVar2 = *(s8*)(param_1 + 0xbf); break;
        case 8:  cVar1 = *(s8*)(param_1 + 0x60); cVar2 = *(s8*)(param_1 + 0xc0); break;
        case 9:  cVar1 = *(s8*)(param_1 + 0x62); cVar2 = *(s8*)(param_1 + 0xc2); break;
        case 10: cVar1 = *(s8*)(param_1 + 0x61); cVar2 = *(s8*)(param_1 + 0xc1); break;
        default: return 0;
        }
    } else if (param_2 == 1) {
        switch (param_3) {
        case 0: cVar1 = *(s8*)(param_1 + 0x77); cVar2 = *(s8*)(param_1 + 0xd7); break;
        case 1: cVar1 = *(s8*)(param_1 + 0x78); cVar2 = *(s8*)(param_1 + 0xd8); break;
        case 2: cVar1 = *(s8*)(param_1 + 0x79); cVar2 = *(s8*)(param_1 + 0xd9); break;
        case 3: cVar1 = *(s8*)(param_1 + 0x7a); cVar2 = *(s8*)(param_1 + 0xda); break;
        case 4: cVar1 = *(s8*)(param_1 + 0x7b); cVar2 = *(s8*)(param_1 + 0xdb); break;
        case 5: cVar1 = *(s8*)(param_1 + 0x7c); cVar2 = *(s8*)(param_1 + 0xdc); break;
        case 6: cVar1 = *(s8*)(param_1 + 0x7d); cVar2 = *(s8*)(param_1 + 0xdd); break;
        case 7: cVar1 = *(s8*)(param_1 + 0x7e); cVar2 = *(s8*)(param_1 + 0xde); break;
        default: return 0;
        }
    } else {
        if (param_2 != 0) { return 0; }
        switch (param_3) {
        case 0:  cVar1 = *(s8*)(param_1 + 0x67); cVar2 = *(s8*)(param_1 + 199); break;
        case 1:  cVar1 = *(s8*)(param_1 + 0x68); cVar2 = *(s8*)(param_1 + 200); break;
        case 2:  cVar1 = *(s8*)(param_1 + 0x69); cVar2 = *(s8*)(param_1 + 0xc9); break;
        case 3:  cVar1 = *(s8*)(param_1 + 0x6a); cVar2 = *(s8*)(param_1 + 0xca); break;
        case 4:  cVar1 = *(s8*)(param_1 + 0x6b); cVar2 = *(s8*)(param_1 + 0xcb); break;
        case 5:  cVar1 = *(s8*)(param_1 + 0x6c); cVar2 = *(s8*)(param_1 + 0xcc); break;
        case 6:  cVar1 = *(s8*)(param_1 + 0x6d); cVar2 = *(s8*)(param_1 + 0xcd); break;
        case 7:  cVar1 = *(s8*)(param_1 + 0x6e); cVar2 = *(s8*)(param_1 + 0xce); break;
        case 8:  cVar1 = *(s8*)(param_1 + 0x6f); cVar2 = *(s8*)(param_1 + 0xcf); break;
        case 9:  cVar1 = *(s8*)(param_1 + 0x70); cVar2 = *(s8*)(param_1 + 0xd0); break;
        case 10: cVar1 = *(s8*)(param_1 + 0x71); cVar2 = *(s8*)(param_1 + 0xd1); break;
        case 0xb: cVar1 = *(s8*)(param_1 + 0x72); cVar2 = *(s8*)(param_1 + 0xd2); break;
        default: return 0;
        }
    }
    return (u64)(cVar1 != cVar2);
}
