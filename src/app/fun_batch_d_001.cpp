#include "types.h"

// MEDIUM-tier FUN_* functions -- 0x7103 address range, batch d-001
// Pool-d worker: auto-generated from Ghidra decompilation

// ---- External declarations -----------------------------------------------

extern "C" int  __cxa_guard_acquire(u64*);
extern "C" void __cxa_guard_release(u64*);

extern void FUN_71003a9ab0(void*, u32);
extern void FUN_71000001c0(void*, void*, void*);
extern void FUN_7101763de0();
extern void FUN_71032f5820(u64*, u64*, u64*, u64*, u64*);
extern void FUN_7103341050(u64*, u64*, u64*, u64*, u64*);
extern u64  get_battle_object_from_id(u32);

// External data symbols
extern u8 PTR_LAB_710517b8e0[] __attribute__((visibility("hidden")));
extern u8 DAT_7105182268[] __attribute__((visibility("hidden")));
extern u8 PTR_LAB_71051824c0[];
extern u8 PTR_LAB_71051825a8[];
extern u8 DAT_7105184ee8[];
extern u8 DAT_c1ffff0000000000[];
extern u8 PTR_LAB_7104f61078[];

extern u8 DAT_71052b6100[];   // __cxa_guard for static init
extern u8 DAT_71052b60f0[];   // static vtable ptr
extern u8 DAT_71052b60f8[];   // static object ptr
extern u8 DAT_71052c2420[];
extern u8 DAT_710532e8b0[];

// ---- Functions ---------------------------------------------------------------

// 0x71031758c0 -- vtable + field copy, 2 fields (32 bytes)
void FUN_71031758c0(s64 param_1, u64 *param_2)
{
    *param_2 = (u64)PTR_LAB_710517b8e0;
    param_2[1] = *(u64 *)(param_1 + 8);
}

// 0x71032ca720 -- vtable + field copy, 3 fields (80 bytes)
void FUN_71032ca720(s64 param_1, u64 *param_2)
{
    u64 uVar1;
    *param_2 = (u64)DAT_7105182268;
    uVar1 = *(u64 *)(param_1 + 0x10);
    param_2[1] = *(u64 *)(param_1 + 8);
    param_2[2] = uVar1;
}

// 0x71032db1c0 -- vtable + field copy, 4 fields (96 bytes)
void FUN_71032db1c0(s64 param_1, u64 *param_2)
{
    u64 uVar1;
    u64 uVar2;
    *param_2 = (u64)PTR_LAB_71051824c0;
    uVar1 = *(u64 *)(param_1 + 8);
    uVar2 = *(u64 *)(param_1 + 0x18);
    param_2[2] = *(u64 *)(param_1 + 0x10);
    param_2[3] = uVar2;
    param_2[1] = uVar1;
}

// 0x71032e5c20 -- vtable + field copy, 4 fields variant (96 bytes)
void FUN_71032e5c20(s64 param_1, u64 *param_2)
{
    u64 uVar1;
    u64 uVar2;
    *param_2 = (u64)PTR_LAB_71051825a8;
    uVar1 = *(u64 *)(param_1 + 8);
    uVar2 = *(u64 *)(param_1 + 0x18);
    param_2[2] = *(u64 *)(param_1 + 0x10);
    param_2[3] = uVar2;
    param_2[1] = uVar1;
}

// 0x7103378c00 -- vtable + field copy, 4 fields variant 2 (96 bytes)
void FUN_7103378c00(s64 param_1, u64 *param_2)
{
    u64 uVar1;
    u64 uVar2;
    *param_2 = (u64)DAT_7105184ee8;
    uVar1 = *(u64 *)(param_1 + 8);
    uVar2 = *(u64 *)(param_1 + 0x18);
    param_2[2] = *(u64 *)(param_1 + 0x10);
    param_2[3] = uVar2;
    param_2[1] = uVar1;
}

// 0x7103351390 -- struct zero/init with sentinel values (1728 bytes)
void FUN_7103351390(u64 *param_1)
{
    *(u8 *)((s64)param_1 + 0x7c) = 0;
    param_1[0x11] = 0;
    param_1[0x12] = (u64)DAT_c1ffff0000000000;
    *(u64 *)((s64)param_1 + 0x74) = 0;
    *param_1 = 0;
    *(u64 *)((s64)param_1 + 6) = 0;
    param_1[0x13] = 0;
    *(u32 *)(param_1 + 0x14) = 0;
    *(u32 *)(param_1 + 0x17) = 0;
    param_1[0x15] = (u64)DAT_c1ffff0000000000;
    param_1[0x16] = 0;
    param_1[0x18] = 0;
    param_1[0x19] = 1;
}

// 0x710313ed70 -- battle object lookup with static singleton fallback (240 bytes)
// Looks up a BattleObject by ID stored at param_2+0x28. If the object is invalid or
// uninitialized, falls back to a lazily-initialized static singleton.
// Then checks if the object's attack module (vtable index at +0xa0) reports a hit
// for the given attack ID (param_2+0x1c). Returns 0 if hit found, 1 otherwise.
u64 FUN_710313ed70(u64 param_1, s64 param_2)
{
    s32 guard_result;
    u64 *battle_obj;
    u64 is_dead;
    s64 attack_result;

    if (*(s32 *)(param_2 + 0x24) == 0) {
        battle_obj = (u64 *)get_battle_object_from_id(*(u32 *)(param_2 + 0x28));
        if ((battle_obj == nullptr) || (*(u8 *)((s64)battle_obj + 0x3a) < 4)) {
            // Lazily initialize static singleton if needed
            if (((*(u64 *)DAT_71052b6100 & 1) == 0) &&
                (guard_result = __cxa_guard_acquire((u64 *)DAT_71052b6100), guard_result != 0)) {
                FUN_71003a9ab0(DAT_71052b60f0, 0);
                *(u8 **)DAT_71052b60f0 = PTR_LAB_7104f61078;
                __cxa_guard_release((u64 *)DAT_71052b6100);
            }
            battle_obj = *(u64 **)DAT_71052b60f8;
            if (*(u64 **)DAT_71052b60f8 == nullptr) {
                return 1;
            }
        }
        // Check if object is alive via vtable call, then query attack module
        is_dead = (**(u64 (**)(u64 *))battle_obj)(battle_obj);
        if (((((is_dead & 1) == 0) && (3 < *(u8 *)((s64)battle_obj + 0x3a))) &&
            (attack_result = (*(s64 (**)(u64 *, u64, u64))(*(s64 *)(battle_obj[4] + 0xa0) + 0x1e8))(*(u64 **)(battle_obj[4] + 0xa0), (u64)(u32)(*(u32 *)(param_2 + 0x1c)), 0), attack_result != 0)) &&
           (*(s8 *)(attack_result + 0x67) == '\0')) {
            return 0;
        }
    }
    return 1;
}

// 0x710316a140 -- linked list traversal + conditional flag set on fighter (960 bytes)
// Walks a linked list at param_1+0x50, searching by param_2.
// If found and various game-state conditions are met (FighterManager active,
// not in specific mode), sets a flag byte at a nested offset.
void FUN_710316a140(s64 param_1, u64 param_2)
{
    s64 *plVar1;
    u64 uVar2;
    s64 lVar3;

    if ((*(u64 *)(param_1 + 0x20) == param_2) && (*(s8 *)(param_1 + 0xa8) != '\0')) {
        for (plVar1 = *(s64 **)(param_1 + 0x50); plVar1 != nullptr; plVar1 = (s64 *)*plVar1) {
            while (uVar2 = (u64)plVar1[4], param_2 > uVar2 || uVar2 == param_2) {
                if ((param_2 <= uVar2) || (plVar1 = (s64 *)plVar1[1], plVar1 == nullptr))
                    goto LAB_710316a198;
            }
        }
LAB_710316a198:
        if (((((*(u64 *)DAT_71052c2420 != 0) &&
               (lVar3 = **(s64 **)(*(u64 *)DAT_71052c2420 + 8), *(s64 *)(lVar3 + 0xbf8) != 0)) &&
              (uVar2 = (*(u64 (*)())(*(s64 *)(lVar3 + 0xbf0) + 0x10))(), (uVar2 & 1) != 0)) &&
             (((*(u64 *)DAT_710532e8b0 == 0 || (*(s32 *)(*(s64 *)(*(u64 *)DAT_710532e8b0 + 8) + 0x138) == 0)) ||
              (*(s8 *)(*(s64 *)(*(u64 *)DAT_710532e8b0 + 8) + 0x2b8) != '\v')))) &&
            (lVar3 = *(s64 *)(**(s64 **)(lVar3 + 0xbf8) + 0x738), *(s8 *)(lVar3 + 9) != '\0')) {
            *(u8 *)(*(s64 *)(lVar3 + 0x68) + 0x105) = 1;
        }
    }
}

// 0x71032f5a00 -- small-array sort by Hash40 key (low 40 bits of u64) (172 bytes)
// Handles arrays of 0-5 elements with specialized sort networks,
// then falls back to insertion sort for larger arrays (with early-exit after 8 swaps).
u8 FUN_71032f5a00(u64 *param_1, u64 *param_2)
{
    u8 bVar1;
    u64 uVar2;
    u64 *puVar3;
    u64 *puVar4;
    s32 iVar5;
    u64 uVar6;
    u64 uVar7;
    u64 uVar8;
    u64 uVar9;
    u64 uVar10;
    u64 uVar11;
    u64 *puVar12;

    switch ((s64)param_2 - (s64)param_1 >> 3) {
    case 0:
    case 1:
        return 1;
    case 2:
        uVar8 = *param_1;
        if ((uVar8 & 0xffffffffff) <= (param_2[-1] & 0xffffffffff)) {
            return 1;
        }
        *param_1 = param_2[-1];
        break;
    case 3:
        uVar8 = *param_1;
        uVar10 = param_1[1];
        uVar2 = param_2[-1];
        uVar6 = uVar10 & 0xffffffffff;
        if ((uVar8 & 0xffffffffff) <= uVar6) {
            if (uVar6 <= (uVar2 & 0xffffffffff)) {
                return 1;
            }
            param_1[1] = uVar2;
            param_2[-1] = uVar10;
            uVar8 = *param_1;
            if ((uVar8 & 0xffffffffff) <= (param_1[1] & 0xffffffffff)) {
                return 1;
            }
            *param_1 = param_1[1];
            param_1[1] = uVar8;
            return 1;
        }
        if ((uVar2 & 0xffffffffff) < uVar6) {
            *param_1 = uVar2;
        } else {
            *param_1 = uVar10;
            param_1[1] = uVar8;
            if ((uVar8 & 0xffffffffff) <= (param_2[-1] & 0xffffffffff)) {
                return 1;
            }
            param_1[1] = param_2[-1];
        }
        break;
    case 4:
        uVar8 = *param_1;
        uVar10 = param_1[1];
        uVar9 = param_1[2];
        uVar7 = uVar10 & 0xffffffffff;
        uVar11 = uVar8 & 0xffffffffff;
        uVar6 = uVar9 & 0xffffffffff;
        uVar2 = uVar9;
        if (uVar7 < uVar11) {
            if (uVar6 < uVar7) {
                *param_1 = uVar9;
            } else {
                *param_1 = uVar10;
                param_1[1] = uVar8;
                if (uVar11 <= uVar6) goto LAB_71032f5c8c;
                param_1[1] = uVar9;
            }
            param_1[2] = uVar8;
            uVar2 = uVar8;
            uVar6 = uVar11;
        } else if (uVar6 < uVar7) {
            bVar1 = uVar6 < uVar11;
            param_1[1] = uVar9;
            param_1[2] = uVar10;
            uVar2 = uVar10;
            uVar6 = uVar7;
            if (bVar1) {
                *param_1 = uVar9;
                param_1[1] = uVar8;
            }
        }
LAB_71032f5c8c:
        if (uVar6 <= (param_2[-1] & 0xffffffffff)) {
            return 1;
        }
        param_1[2] = param_2[-1];
        param_2[-1] = uVar2;
        uVar8 = param_1[1];
        uVar10 = param_1[2];
        if ((uVar8 & 0xffffffffff) <= (uVar10 & 0xffffffffff)) {
            return 1;
        }
        param_1[1] = uVar10;
        param_1[2] = uVar8;
        uVar8 = *param_1;
        if ((uVar8 & 0xffffffffff) <= (uVar10 & 0xffffffffff)) {
            return 1;
        }
        *param_1 = uVar10;
        param_1[1] = uVar8;
        return 1;
    case 5:
        FUN_71032f5820(param_1, param_1 + 1, param_1 + 2, param_1 + 3, param_2 - 1);
        return 1;
    default:
        uVar8 = *param_1;
        uVar10 = param_1[1];
        uVar6 = param_1[2];
        uVar11 = uVar10 & 0xffffffffff;
        uVar7 = uVar8 & 0xffffffffff;
        uVar9 = uVar6 & 0xffffffffff;
        uVar2 = uVar6;
        if (uVar11 < uVar7) {
            if (uVar9 < uVar11) {
                *param_1 = uVar6;
            } else {
                *param_1 = uVar10;
                param_1[1] = uVar8;
                if (uVar7 <= uVar9) goto LAB_71032f5ba8;
                param_1[1] = uVar6;
            }
            param_1[2] = uVar8;
            uVar2 = uVar8;
        } else if (uVar9 < uVar11) {
            param_1[1] = uVar6;
            param_1[2] = uVar10;
            uVar2 = uVar10;
            if (uVar9 < uVar7) {
                *param_1 = uVar6;
                param_1[1] = uVar8;
            }
        }
LAB_71032f5ba8:
        if (param_1 + 3 == param_2) {
            return 1;
        }
        iVar5 = 0;
        puVar4 = param_1 + 3;
        do {
            uVar8 = *puVar4;
            uVar10 = uVar8 & 0xffffffffff;
            puVar3 = puVar4;
            if (uVar10 < (uVar2 & 0xffffffffff)) {
                do {
                    puVar12 = puVar3;
                    *puVar12 = uVar2;
                    puVar3 = param_1;
                    if (puVar12 - 1 == param_1) goto LAB_71032f5c08;
                    uVar2 = puVar12[-2];
                    puVar3 = puVar12 - 1;
                } while (uVar10 < (uVar2 & 0xffffffffff));
                puVar3 = puVar12 - 1;
LAB_71032f5c08:
                iVar5 = iVar5 + 1;
                *puVar3 = uVar8;
                if (iVar5 == 8) {
                    return (u8)(puVar4 + 1 == param_2);
                }
            }
            if (puVar4 + 1 == param_2) {
                return 1;
            }
            uVar2 = *puVar4;
            puVar4 = puVar4 + 1;
        } while (1);
    }
    param_2[-1] = uVar8;
    return 1;
}

// 0x7103341230 -- small-array sort by Hash40 key (0xff0000ffffffffff mask of u64) (1308 bytes)
// Same algorithm as FUN_71032f5a00 but uses a different key mask that includes
// the high byte (category/type field) along with the low 40 bits.
u8 FUN_7103341230(u64 *param_1, u64 *param_2)
{
    u8 bVar1;
    u64 uVar2;
    u64 *puVar3;
    u64 *puVar4;
    s32 iVar5;
    u64 uVar6;
    u64 uVar7;
    u64 uVar8;
    u64 uVar9;
    u64 uVar10;
    u64 uVar11;
    u64 *puVar12;

    switch ((s64)param_2 - (s64)param_1 >> 3) {
    case 0:
    case 1:
        return 1;
    case 2:
        uVar8 = *param_1;
        if ((uVar8 & 0xff0000ffffffffff) <= (param_2[-1] & 0xff0000ffffffffff)) {
            return 1;
        }
        *param_1 = param_2[-1];
        break;
    case 3:
        uVar8 = *param_1;
        uVar10 = param_1[1];
        uVar2 = param_2[-1];
        uVar6 = uVar10 & 0xff0000ffffffffff;
        if ((uVar8 & 0xff0000ffffffffff) <= uVar6) {
            if (uVar6 <= (uVar2 & 0xff0000ffffffffff)) {
                return 1;
            }
            param_1[1] = uVar2;
            param_2[-1] = uVar10;
            uVar8 = *param_1;
            if ((uVar8 & 0xff0000ffffffffff) <= (param_1[1] & 0xff0000ffffffffff)) {
                return 1;
            }
            *param_1 = param_1[1];
            param_1[1] = uVar8;
            return 1;
        }
        if ((uVar2 & 0xff0000ffffffffff) < uVar6) {
            *param_1 = uVar2;
        } else {
            *param_1 = uVar10;
            param_1[1] = uVar8;
            if ((uVar8 & 0xff0000ffffffffff) <= (param_2[-1] & 0xff0000ffffffffff)) {
                return 1;
            }
            param_1[1] = param_2[-1];
        }
        break;
    case 4:
        uVar8 = *param_1;
        uVar10 = param_1[1];
        uVar9 = param_1[2];
        uVar7 = uVar10 & 0xff0000ffffffffff;
        uVar11 = uVar8 & 0xff0000ffffffffff;
        uVar6 = uVar9 & 0xff0000ffffffffff;
        uVar2 = uVar9;
        if (uVar7 < uVar11) {
            if (uVar6 < uVar7) {
                *param_1 = uVar9;
            } else {
                *param_1 = uVar10;
                param_1[1] = uVar8;
                if (uVar11 <= uVar6) goto LAB_71033414bc;
                param_1[1] = uVar9;
            }
            param_1[2] = uVar8;
            uVar2 = uVar8;
            uVar6 = uVar11;
        } else if (uVar6 < uVar7) {
            bVar1 = (u8)(uVar6 < uVar11);
            param_1[1] = uVar9;
            param_1[2] = uVar10;
            uVar2 = uVar10;
            uVar6 = uVar7;
            if (bVar1) {
                *param_1 = uVar9;
                param_1[1] = uVar8;
            }
        }
LAB_71033414bc:
        if (uVar6 <= (param_2[-1] & 0xff0000ffffffffff)) {
            return 1;
        }
        param_1[2] = param_2[-1];
        param_2[-1] = uVar2;
        uVar8 = param_1[1];
        uVar10 = param_1[2];
        if ((uVar8 & 0xff0000ffffffffff) <= (uVar10 & 0xff0000ffffffffff)) {
            return 1;
        }
        param_1[1] = uVar10;
        param_1[2] = uVar8;
        uVar8 = *param_1;
        if ((uVar8 & 0xff0000ffffffffff) <= (uVar10 & 0xff0000ffffffffff)) {
            return 1;
        }
        *param_1 = uVar10;
        param_1[1] = uVar8;
        return 1;
    case 5:
        FUN_7103341050(param_1, param_1 + 1, param_1 + 2, param_1 + 3, param_2 - 1);
        return 1;
    default:
        uVar8 = *param_1;
        uVar10 = param_1[1];
        uVar6 = param_1[2];
        uVar11 = uVar10 & 0xff0000ffffffffff;
        uVar7 = uVar8 & 0xff0000ffffffffff;
        uVar9 = uVar6 & 0xff0000ffffffffff;
        uVar2 = uVar6;
        if (uVar11 < uVar7) {
            if (uVar9 < uVar11) {
                *param_1 = uVar6;
            } else {
                *param_1 = uVar10;
                param_1[1] = uVar8;
                if (uVar7 <= uVar9) goto LAB_71033413d8;
                param_1[1] = uVar6;
            }
            param_1[2] = uVar8;
            uVar2 = uVar8;
        } else if (uVar9 < uVar11) {
            param_1[1] = uVar6;
            param_1[2] = uVar10;
            uVar2 = uVar10;
            if (uVar9 < uVar7) {
                *param_1 = uVar6;
                param_1[1] = uVar8;
            }
        }
LAB_71033413d8:
        if (param_1 + 3 == param_2) {
            return 1;
        }
        iVar5 = 0;
        puVar4 = param_1 + 3;
        do {
            uVar8 = *puVar4;
            uVar10 = uVar8 & 0xff0000ffffffffff;
            puVar3 = puVar4;
            if (uVar10 < (uVar2 & 0xff0000ffffffffff)) {
                do {
                    puVar12 = puVar3;
                    *puVar12 = uVar2;
                    puVar3 = param_1;
                    if (puVar12 - 1 == param_1) goto LAB_7103341438;
                    uVar2 = puVar12[-2];
                    puVar3 = puVar12 - 1;
                } while (uVar10 < (uVar2 & 0xff0000ffffffffff));
                puVar3 = puVar12 - 1;
LAB_7103341438:
                iVar5 = iVar5 + 1;
                *puVar3 = uVar8;
                if (iVar5 == 8) {
                    return (u8)(puVar4 + 1 == param_2);
                }
            }
            if (puVar4 + 1 == param_2) {
                return 1;
            }
            uVar2 = *puVar4;
            puVar4 = puVar4 + 1;
        } while (1);
    }
    param_2[-1] = uVar8;
    return 1;
}

// 0x71033949b0 -- Hash40 builder for "mnu_header_*" menu section names (768 bytes)
// Writes packed string into Hash40 struct {u32 hash, u32 len, char str[]},
// then computes hash = multiply-xor over the string bytes.
// Switch key: ((param_2 >> 24) & 0x7f) - 2
void FUN_71033949b0(u32 *param_1, u32 param_2)
{
    u32 hash;
    u8 *str_ptr;
    u32 ch;

    hash = 0x811c9dc5;
    switch ((s32)(((param_2 & 0x7f000000) + 0xfe000000) >> 0x18)) {
    case 0: // "mnu_header_melee"
        *(u8 *)(param_1 + 6) = 0;
        param_1[4] = 0x6d5f7265; // "er_m"
        param_1[5] = 0x65656c65; // "elee"
        param_1[0] = 0;
        param_1[1] = 0x10;       // length = 16
        param_1[2] = 0x5f756e6d; // "mnu_"
        param_1[3] = 0x64616568; // "head"
        ch = 0x6d; // 'm'
        str_ptr = (u8 *)((s64)param_1 + 9);
        do {
            hash = hash * 0x89 ^ ch;
            ch = (u32)*str_ptr;
            str_ptr = str_ptr + 1;
        } while (ch != 0);
        break;
    case 1: // "mnu_header_spirits"
        *(u8 *)((s64)param_1 + 0x1a) = 0;
        param_1[0] = 0;
        param_1[1] = 0x12;       // length = 18
        param_1[2] = 0x5f756e6d; // "mnu_"
        param_1[3] = 0x64616568; // "head"
        *(u16 *)(param_1 + 6) = 0x7374; // "ts"
        ch = 0x6d; // 'm'
        param_1[4] = 0x735f7265; // "er_s"
        param_1[5] = 0x69726970; // "piri"
        str_ptr = (u8 *)((s64)param_1 + 9);
        do {
            hash = hash * 0x89 ^ ch;
            ch = (u32)*str_ptr;
            str_ptr = str_ptr + 1;
        } while (ch != 0);
        break;
    case 2: // "mnu_header_other"
        *(u8 *)(param_1 + 6) = 0;
        param_1[4] = 0x6f5f7265; // "er_o"
        param_1[5] = 0x72656874; // "ther"
        param_1[0] = 0;
        param_1[1] = 0x10;       // length = 16
        param_1[2] = 0x5f756e6d; // "mnu_"
        param_1[3] = 0x64616568; // "head"
        ch = 0x6d; // 'm'
        str_ptr = (u8 *)((s64)param_1 + 9);
        do {
            hash = hash * 0x89 ^ ch;
            ch = (u32)*str_ptr;
            str_ptr = str_ptr + 1;
        } while (ch != 0);
        break;
    case 3: // "mnu_header_collection"
        param_1[0] = 0;
        param_1[1] = 0x15;       // length = 21
        param_1[2] = 0x5f756e6d; // "mnu_"
        param_1[3] = 0x64616568; // "head"
        param_1[4] = 0x635f7265; // "er_c"
        param_1[5] = 0x656c6c6f; // "olle"
        *(u16 *)(param_1 + 6) = 0x7463; // "ct"
        *(u32 *)((s64)param_1 + 0x1a) = 0x6e6f69; // "ion\0"
        ch = 0x6d; // 'm'
        str_ptr = (u8 *)((s64)param_1 + 9);
        do {
            hash = hash * 0x89 ^ ch;
            ch = (u32)*str_ptr;
            str_ptr = str_ptr + 1;
        } while (ch != 0);
        break;
    case 4: // "mnu_header_option"
        param_1[0] = 0;
        param_1[1] = 0x11;       // length = 17
        param_1[2] = 0x5f756e6d; // "mnu_"
        param_1[3] = 0x64616568; // "head"
        param_1[4] = 0x6f5f7265; // "er_o"
        param_1[5] = 0x6f697470; // "ptio"
        *(u16 *)(param_1 + 6) = 0x6e; // "n\0"
        ch = 0x6d; // 'm'
        str_ptr = (u8 *)((s64)param_1 + 9);
        do {
            hash = hash * 0x89 ^ ch;
            ch = (u32)*str_ptr;
            str_ptr = str_ptr + 1;
        } while (ch != 0);
        break;
    case 5: // "mnu_header_online"
        param_1[0] = 0;
        param_1[1] = 0x11;       // length = 17
        param_1[2] = 0x5f756e6d; // "mnu_"
        param_1[3] = 0x64616568; // "head"
        param_1[4] = 0x6f5f7265; // "er_o"
        param_1[5] = 0x6e696c6e; // "nlin"
        *(u16 *)(param_1 + 6) = 0x65; // "e\0"
        ch = 0x6d; // 'm'
        str_ptr = (u8 *)((s64)param_1 + 9);
        do {
            hash = hash * 0x89 ^ ch;
            ch = (u32)*str_ptr;
            str_ptr = str_ptr + 1;
        } while (ch != 0);
        break;
    case 6: // "mnu_header_help"
        param_1[0] = 0;
        param_1[1] = 0xf;        // length = 15
        param_1[2] = 0x5f756e6d; // "mnu_"
        param_1[3] = 0x64616568; // "head"
        ch = 0x6d; // 'm'
        param_1[4] = 0x685f7265; // "er_h"
        param_1[5] = 0x706c65;   // "elp\0"
        str_ptr = (u8 *)((s64)param_1 + 9);
        do {
            hash = hash * 0x89 ^ ch;
            ch = (u32)*str_ptr;
            str_ptr = str_ptr + 1;
        } while (ch != 0);
        break;
    default: // "mnu_header_melee" (fallback)
        *(u8 *)(param_1 + 6) = 0;
        param_1[4] = 0x6d5f7265; // "er_m"
        param_1[5] = 0x65656c65; // "elee"
        param_1[0] = 0;
        param_1[1] = 0x10;       // length = 16
        param_1[2] = 0x5f756e6d; // "mnu_"
        param_1[3] = 0x64616568; // "head"
        ch = 0x6d; // 'm'
        str_ptr = (u8 *)((s64)param_1 + 9);
        do {
            hash = hash * 0x89 ^ ch;
            ch = (u32)*str_ptr;
            str_ptr = str_ptr + 1;
        } while (ch != 0);
    }
    *param_1 = hash;
}
