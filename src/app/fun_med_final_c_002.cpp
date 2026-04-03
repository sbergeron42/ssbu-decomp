#include "types.h"

// MEDIUM-tier FUN_* decompilation -- pool-c range 0x7102000000-0x7103FFFFFF
// Batch 002: hash dispatch tables, sort functions, animation state machines

// ─── External globals ────────────────────────────────────────────────────
extern u64 DAT_7105328fa0;
extern u64 DAT_7104550c40[];
extern f32 DAT_7104471598;
extern f32 DAT_71044723dc;
extern f32 DAT_7104471aa4;
extern f32 DAT_7104471008;
extern f32 DAT_7104472454;
extern u8  DAT_200000001;
extern u8  DAT_100000001;
extern void* LAB_7102681a70;

// ─── External functions ──────────────────────────────────────────────────
extern "C" void FUN_71025e9900(u8*);
extern "C" void FUN_71025ee000(s32, u64, s32);
extern "C" void FUN_710260fdd0(u64, u64);
extern "C" u64* get_battle_object_from_id(u32);
extern "C" void FUN_7103736740(void*, void*);
extern "C" void FUN_71025a3c50(u16*, u16*, u16*, u16*, u16*);
extern "C" void FUN_71025a4d10(s64*, s64*, s64*, s64*, s64*);
extern "C" void FUN_71025a52a0(s64*, s64*, s64*, s64*, s64*);

// ─────────────────────────────────────────────────────────────────────────
// FUN_7102573030  size=928
// Lua param decode: integer types 1-7 pass value through,
// type 9 looks up hash in table and maps to a typed constant.
// ─────────────────────────────────────────────────────────────────────────
u8* FUN_7102573030(s64 param_1, u8* param_2)
{
    u32 uVar2 = (u32)*param_2;

    if (uVar2 - 1u < 7u) {
        u64 uVar1;
        switch (uVar2) {
        case 1: case 3: uVar1 = (u64)param_2[1]; break;
        case 2:  uVar1 = (u64)(s8)param_2[1]; break;
        case 4:  uVar1 = (u64)*(s16*)(param_2 + 1); break;
        case 5:  uVar1 = (u64)*(u16*)(param_2 + 1); break;
        case 6: case 7: uVar1 = (u64)*(u32*)(param_2 + 1); break;
        default: uVar1 = 0; break;
        }
        return (u8*)(uVar1 << 0x20 | 1);
    }

    if (uVar2 == 9) {
        u64 uVar1 = *(u64*)(*(s64*)(param_1 + 0x20) + (s64)*(s32*)(param_2 + 1) * 8) & 0xffffffffffULL;
        if (uVar1 < 0xda2f68442ULL) {
            if (uVar1 < 0xd454ea945ULL) {
                if (uVar1 < 0xd324999d3ULL) {
                    if (uVar1 == 0xd22e4e4b9ULL) return (u8*)0x1000000001ULL;
                    if (uVar1 == 0xd258920a0ULL) return (u8*)0xc00000001ULL;
                } else {
                    if (uVar1 == 0xd324999d3ULL) return (u8*)0xa00000001ULL;
                    if (uVar1 == 0xd3bffd5f8ULL) return (u8*)0x600000001ULL;
                }
            } else if (uVar1 < 0xd4cf8e56eULL) {
                if (uVar1 == 0xd454ea945ULL) return (u8*)0xb00000001ULL;
                if (uVar1 == 0xd4b952177ULL) return (u8*)0x300000001ULL;
            } else {
                if (uVar1 == 0xd4cf8e56eULL) return (u8*)0x700000001ULL;
                if (uVar1 == 0xd528e1036ULL) return (u8*)0xd00000001ULL;
                if (uVar1 == 0xd55e3d42fULL) return (u8*)0x1100000001ULL;
            }
        } else if (uVar1 < 0xdd29c70cdULL) {
            if (uVar1 < 0xdbc80711aULL) {
                if (uVar1 == 0xda2f68442ULL) return (u8*)0x900000001ULL;
                if (uVar1 == 0xda59b405bULL) return (u8*)0x500000001ULL;
            } else {
                if (uVar1 == 0xdbc80711aULL) return (u8*)0xf00000001ULL;
                if (uVar1 == 0xdcb87418cULL) return (u8*)0xe00000001ULL;
            }
        } else if (uVar1 < 0xfc8c475b8ULL) {
            if (uVar1 == 0xdd29c70cdULL) return (u8*)0x400000001ULL;
            if (uVar1 == 0xdd5f1b4d4ULL) return (u8*)0x800000001ULL;
        } else {
            if (uVar1 == 0x19271dc7dfULL) return &DAT_200000001;
            if (uVar1 == 0x10841cf415ULL) return (u8*)0x1ULL;
            if (uVar1 == 0xfc8c475b8ULL)  return &DAT_100000001;
        }
    }
    return (u8*)0x0;
}

// ─────────────────────────────────────────────────────────────────────────
// FUN_71025733d0  size=1136
// Lua param decode: same pattern with different hash constants.
// ─────────────────────────────────────────────────────────────────────────
u8* FUN_71025733d0(s64 param_1, u8* param_2)
{
    u32 uVar2 = (u32)*param_2;

    if (uVar2 - 1u < 7u) {
        u64 uVar1;
        switch (uVar2) {
        case 1: case 3: uVar1 = (u64)param_2[1]; break;
        case 2:  uVar1 = (u64)(s8)param_2[1]; break;
        case 4:  uVar1 = (u64)*(s16*)(param_2 + 1); break;
        case 5:  uVar1 = (u64)*(u16*)(param_2 + 1); break;
        case 6: case 7: uVar1 = (u64)*(u32*)(param_2 + 1); break;
        default: uVar1 = 0; break;
        }
        return (u8*)(uVar1 << 0x20 | 1);
    }

    if (uVar2 == 9) {
        u64 uVar1 = *(u64*)(*(s64*)(param_1 + 0x20) + (s64)*(s32*)(param_2 + 1) * 8) & 0xffffffffffULL;
        if (uVar1 < 0x106c6c4e34ULL) {
            if (uVar1 < 0xd4c48917dULL) {
                if (uVar1 < 0xbc174cf51ULL) {
                    if (uVar1 == 0xa9184291aULL) return (u8*)0x300000001ULL;
                    if (uVar1 == 0xb1b294aa2ULL) return &DAT_100000001;
                    if (uVar1 == 0xb430c3508ULL) return (u8*)0x1ULL;
                } else {
                    if (uVar1 == 0xbc174cf51ULL) return (u8*)0x700000001ULL;
                    if (uVar1 == 0xbeb56b312ULL) return &DAT_200000001;
                    if (uVar1 == 0xd1a40e82aULL) return (u8*)0x500000001ULL;
                }
            } else if (uVar1 < 0x100c3191bfULL) {
                if (uVar1 == 0xd4c48917dULL) return (u8*)0xa00000001ULL;
                if (uVar1 == 0xe85d76e22ULL) return (u8*)0x900000001ULL;
                if (uVar1 == 0xf59e997ddULL) return (u8*)0x1600000001ULL;
            } else {
                if (uVar1 == 0x100c3191bfULL) return (u8*)0x800000001ULL;
                if (uVar1 == 0x101d57376fULL) return (u8*)0x600000001ULL;
                if (uVar1 == 0x101f1b8f98ULL) return (u8*)0x1400000001ULL;
            }
        } else if (uVar1 < 0x12808ed1d9ULL) {
            if (uVar1 < 0x11d0d139a9ULL) {
                if (uVar1 == 0x106c6c4e34ULL) return (u8*)0x400000001ULL;
                if (uVar1 == 0x112e8f817aULL) return (u8*)0x1700000001ULL;
                if (uVar1 == 0x11c7c893dcULL) return (u8*)0x1300000001ULL;
            } else {
                if (uVar1 == 0x11d0d139a9ULL) return (u8*)0x1200000001ULL;
                if (uVar1 == 0x120d34e9a4ULL) return (u8*)0xd00000001ULL;
                if (uVar1 == 0x12440726bbULL) return (u8*)0x1000000001ULL;
            }
        } else if (uVar1 < 0x12dddd3f96ULL) {
            if (uVar1 == 0x12808ed1d9ULL) return (u8*)0xb00000001ULL;
            if (uVar1 == 0x12b0ede49eULL) return (u8*)0x1500000001ULL;
            if (uVar1 == 0x12d5246adeULL) return (u8*)0xf00000001ULL;
        } else {
            if (uVar1 == 0x12dddd3f96ULL) return (u8*)0x1100000001ULL;
            if (uVar1 == 0x13c8bfe3fcULL) return (u8*)0xc00000001ULL;
            if (uVar1 == 0x13f567b79cULL) return (u8*)0xe00000001ULL;
        }
    }
    return (u8*)0x0;
}

// ─────────────────────────────────────────────────────────────────────────
// FUN_71025994c0  size=1264
// Lua param decode: same pattern, different hash constants.
// ─────────────────────────────────────────────────────────────────────────
u8* FUN_71025994c0(s64 param_1, u8* param_2)
{
    u32 uVar1 = (u32)*param_2;

    if (uVar1 - 1u < 7u) {
        switch (uVar1) {
        case 1: case 3: return (u8*)(((u64)param_2[1] << 0x20) | 1);
        case 2:  return (u8*)(((u64)(s8)param_2[1] << 0x20) | 1);
        case 4:  return (u8*)(((u64)*(s16*)(param_2+1) << 0x20) | 1);
        case 5:  return (u8*)(((u64)*(u16*)(param_2+1) << 0x20) | 1);
        case 6: case 7: return (u8*)(((u64)*(u32*)(param_2+1) << 0x20) | 1);
        default: return (u8*)0x1ULL;
        }
    }
    if (uVar1 != 9) return (u8*)0x0;

    u64 uVar2 = *(u64*)(*(s64*)(param_1 + 0x20) + (s64)*(s32*)(param_2 + 1) * 8) & 0xffffffffffULL;
    u64 uVar3;

    if (uVar2 < 0xde2b76daaULL) {
        if (0x7d8a05626ULL < uVar2) {
            if (uVar2 < 0xb8041e117ULL) {
                if (0x9e5c6a198ULL < uVar2) {
                    if (uVar2 != 0x9e5c6a199ULL) {
                        if (uVar2 != 0x9f5a79980ULL) return (u8*)0x0;
                        return (u8*)0x300000001ULL;
                    }
                    goto LAB_1;
                }
                if (uVar2 != 0x7d8a05627ULL) {
                    if (uVar2 != 0x93cf01919ULL) return (u8*)0x0;
                    return (u8*)0x500000001ULL;
                }
            } else {
                if (uVar2 < 0xcd5fe267eULL) {
                    if (uVar2 == 0xb8041e117ULL) return (u8*)0x1ULL;
                    uVar3 = 0xc780fce3bULL;
                    goto LAB_check;
                }
                if (uVar2 != 0xcd5fe267eULL) {
                    if (uVar2 != 0xceb2353a4ULL) return (u8*)0x0;
                    return (u8*)0x400000001ULL;
                }
            }
            goto LAB_2;
        }
        if (uVar2 < 0x5b4ca7514ULL) {
            if (uVar2 < 0x47a67e768ULL) {
                if ((uVar2 != 0x359fa4760ULL) && (uVar2 != 0x3c55cd5b6ULL)) return (u8*)0x0;
                goto LAB_2;
            }
            if (uVar2 == 0x47a67e768ULL) return (u8*)0x1ULL;
            if (uVar2 != 0x48eba60ccULL) return (u8*)0x0;
        } else if (uVar2 < 0x6c66ab3a6ULL) {
            if (uVar2 != 0x5b4ca7514ULL) {
                uVar3 = 0x6218568e4ULL;
                goto LAB_check;
            }
        } else {
            if (uVar2 == 0x6c66ab3a6ULL) return (u8*)0x300000001ULL;
            if (uVar2 != 0x7ac20ca5bULL) return (u8*)0x0;
        }
    } else {
        if (uVar2 < 0x10d8d36782ULL) {
            if (uVar2 < 0xeb1284b4cULL) {
                if (uVar2 < 0xe6d99bbc2ULL) {
                    if (uVar2 == 0xde2b76daaULL) return (u8*)0x300000001ULL;
                    if (uVar2 != 0xe1df34f4dULL) return (u8*)0x0;
                    return (u8*)0x300000001ULL;
                }
                if (uVar2 == 0xe6d99bbc2ULL) return (u8*)0x1ULL;
                if (uVar2 != 0xe8397daeeULL) return (u8*)0x0;
                goto LAB_2;
            }
            if (uVar2 < 0x10abc66096ULL) {
                if (uVar2 == 0xeb1284b4cULL) return (u8*)0x1ULL;
                if (uVar2 != 0xef490ea78ULL) return (u8*)0x0;
                goto LAB_1;
            }
            if (uVar2 == 0x10abc66096ULL) goto LAB_2;
            uVar3 = 0xd025f5ccULL;
        } else {
            if (0x1303a3731aULL < uVar2) {
                if (0x1441228069ULL < uVar2) {
                    if (uVar2 == 0x144122806aULL) return (u8*)0x300000001ULL;
                    if (uVar2 != 0x14bb2ea833ULL) return (u8*)0x0;
                    goto LAB_1;
                }
                if (uVar2 == 0x1303a3731bULL) return (u8*)0x1ULL;
                if (uVar2 != 0x13696afdf6ULL) return (u8*)0x0;
LAB_2:
                return &DAT_200000001;
            }
            if (0x114647a48aULL < uVar2) {
                if (uVar2 == 0x114647a48bULL) return (u8*)0x1ULL;
                if (uVar2 != 0x12ccf6a22eULL) return (u8*)0x0;
                goto LAB_2;
            }
            if (uVar2 == 0x10d8d36782ULL) return (u8*)0x300000001ULL;
            uVar3 = 0xf370fac4ULL;
        }
        if (uVar2 != (uVar3 | 0x1000000000ULL)) return (u8*)0x0;
    }
LAB_1:
    return &DAT_100000001;
LAB_check:
    if (uVar2 != uVar3) return (u8*)0x0;
    return (u8*)0x1ULL;
}

// ─────────────────────────────────────────────────────────────────────────
// FUN_71025a3de0  size=144
// Insertion sort for ushort array [param_1, param_2).
// ─────────────────────────────────────────────────────────────────────────
bool FUN_71025a3de0(u16* param_1, u16* param_2)
{
    u16 uVar1, uVar2, uVar4, uVar6;
    s64 lVar8, lVar10;
    int iVar9;
    u16* puVar5;
    u16* puVar7;

    switch (((s64)param_2 - (s64)param_1) >> 1) {
    case 0: case 1:
        return true;
    case 2:
        uVar6 = *param_1;
        if (uVar6 <= param_2[-1]) return true;
        *param_1 = param_2[-1];
        goto LAB_put_last;
    case 3:
        uVar1 = param_1[1]; uVar6 = *param_1; uVar2 = param_2[-1];
        if (uVar1 < uVar6) {
            if (uVar2 < uVar1) { *param_1 = uVar2; }
            else { *param_1 = uVar1; param_1[1] = uVar6;
                   if (uVar6 <= param_2[-1]) return true;
                   param_1[1] = param_2[-1]; }
            goto LAB_put_last;
        }
        if (uVar1 <= uVar2) return true;
        param_1[1] = uVar2; param_2[-1] = uVar1;
        uVar1 = param_1[1]; uVar6 = *param_1;
        if (uVar6 <= uVar1) return true;
        goto LAB_swap01;
    case 4:
        break;
    case 5:
        FUN_71025a3c50(param_1, param_1+1, param_1+2, param_1+3, param_2-1);
        return true;
    default:
        uVar1 = param_1[1]; uVar6 = *param_1; uVar2 = param_1[2]; uVar4 = uVar2;
        if (uVar1 < uVar6) {
            if (uVar2 < uVar1) { *param_1 = uVar2; }
            else { *param_1 = uVar1; param_1[1] = uVar6;
                   if (uVar6 <= uVar2) goto LAB_default_after3;
                   param_1[1] = uVar2; }
            param_1[2] = uVar6; uVar4 = uVar6;
        } else if (uVar2 < uVar1) {
            param_1[1] = uVar2; param_1[2] = uVar1; uVar4 = uVar1;
            if (uVar2 < uVar6) { *param_1 = uVar2; param_1[1] = uVar6; }
        }
LAB_default_after3:
        if (param_1 + 3 == param_2) return true;
        lVar8 = 0; iVar9 = 0; puVar7 = param_1 + 3;
        do {
            uVar1 = *puVar7; lVar10 = lVar8;
            if (uVar1 < uVar4) {
                for (;;) {
                    *(u16*)((u8*)param_1 + lVar10 + 6) = uVar4;
                    puVar5 = param_1;
                    if (lVar10 == -4) goto LAB_ins_place;
                    uVar4 = *(u16*)((u8*)param_1 + lVar10 + 2);
                    lVar10 -= 2;
                    if (!(uVar1 < uVar4)) break;
                }
                puVar5 = (u16*)((u8*)param_1 + lVar10 + 4);
LAB_ins_place:
                iVar9++; *puVar5 = uVar1;
                if (iVar9 == 8) return puVar7 + 1 == param_2;
            }
            if (puVar7 + 1 == param_2) return true;
            uVar4 = *puVar7; lVar8 += 2; puVar7++;
        } while (true);
    }
    // case 4
    uVar1 = param_1[1]; uVar6 = *param_1; uVar2 = param_1[2]; uVar4 = uVar2;
    if (uVar1 < uVar6) {
        if (uVar2 < uVar1) { *param_1 = uVar2; }
        else { *param_1 = uVar1; param_1[1] = uVar6;
               if (uVar6 <= uVar2) goto LAB_after4_3sort;
               param_1[1] = uVar2; }
        param_1[2] = uVar6; uVar4 = uVar6;
    } else if (uVar2 < uVar1) {
        param_1[1] = uVar2; param_1[2] = uVar1; uVar4 = uVar1;
        if (uVar2 < uVar6) { *param_1 = uVar2; param_1[1] = uVar6; }
    }
LAB_after4_3sort:
    if (uVar4 <= param_2[-1]) return true;
    param_1[2] = param_2[-1]; param_2[-1] = uVar4;
    uVar1 = param_1[2];
    if (param_1[1] <= uVar1) return true;
    param_1[2] = param_1[1]; uVar6 = *param_1; param_1[1] = uVar1;
    if (uVar6 <= uVar1) return true;
LAB_swap01:
    *param_1 = uVar1; param_1[1] = uVar6;
    return true;
LAB_put_last:
    param_2[-1] = uVar6;
    return true;
}

// ─────────────────────────────────────────────────────────────────────────
// FUN_71025a4f10  size=172
// Sort long* array [param_1, param_2) by ascending *(int*)(elem+0x48).
// ─────────────────────────────────────────────────────────────────────────
bool FUN_71025a4f10(s64* param_1, s64* param_2)
{
    s64 lVar1, lVar3, lVar5, lVar7;
    s64* plVar2; s64* plVar4;
    int iVar8;
    int *piVar6, *piVar9, *piVar10;
    s64 lVar_off, lOff2;

    switch (((s64)param_2 - (s64)param_1) >> 3) {
    case 0: case 1: return true;
    case 2:
        lVar7 = *param_1;
        if (*(s32*)(param_2[-1] + 0x48) <= *(s32*)(lVar7 + 0x48)) return true;
        *param_1 = param_2[-1];
        break;
    case 3:
        lVar7 = *param_1; lVar1 = param_1[1]; lVar3 = param_2[-1];
        iVar8 = *(s32*)(lVar1 + 0x48);
        if (iVar8 <= *(s32*)(lVar7 + 0x48)) {
            if (*(s32*)(lVar3 + 0x48) <= iVar8) return true;
            param_1[1] = lVar3; param_2[-1] = lVar1;
            lVar7 = *param_1;
            if (*(s32*)(param_1[1] + 0x48) <= *(s32*)(lVar7 + 0x48)) return true;
            *param_1 = param_1[1]; param_1[1] = lVar7; return true;
        }
        if (iVar8 < *(s32*)(lVar3 + 0x48)) { *param_1 = lVar3; }
        else { *param_1 = lVar1; param_1[1] = lVar7;
               if (*(s32*)(param_2[-1] + 0x48) <= *(s32*)(lVar7 + 0x48)) return true;
               param_1[1] = param_2[-1]; }
        break;
    case 4:
        lVar7 = *param_1; lVar1 = param_1[1]; piVar10 = (int*)(lVar1 + 0x48);
        iVar8 = *piVar10; piVar6 = (int*)(lVar7 + 0x48);
        lVar5 = param_1[2]; piVar9 = (int*)(lVar5 + 0x48); lVar3 = lVar5;
        if (*piVar6 < iVar8) {
            if (iVar8 < *piVar9) { *param_1 = lVar5; param_1[2] = lVar7; lVar3 = lVar7; piVar9 = piVar6; }
            else { *param_1 = lVar1; param_1[1] = lVar7;
                   if (*(s32*)(lVar7+0x48) < *(s32*)(lVar5+0x48)) { param_1[1]=lVar5; param_1[2]=lVar7; lVar3=lVar7; piVar9=piVar6; } }
        } else if (iVar8 < *piVar9) {
            param_1[1] = lVar5; param_1[2] = lVar1; lVar3 = lVar1; piVar9 = piVar10;
            if (*piVar6 < *(s32*)(lVar5+0x48)) { *param_1=lVar5; param_1[1]=lVar7; }
        }
        if (*(s32*)(param_2[-1] + 0x48) <= *piVar9) return true;
        param_1[2] = param_2[-1]; param_2[-1] = lVar3;
        lVar7 = param_1[1]; lVar1 = param_1[2];
        if (*(s32*)(lVar1+0x48) <= *(s32*)(lVar7+0x48)) return true;
        lVar3 = *param_1; param_1[1] = lVar1; param_1[2] = lVar7;
        if (*(s32*)(lVar1+0x48) <= *(s32*)(lVar3+0x48)) return true;
        *param_1 = lVar1; param_1[1] = lVar3; return true;
    case 5:
        FUN_71025a4d10(param_1, param_1+1, param_1+2, param_1+3, param_2-1);
        return true;
    default:
        lVar7 = *param_1; lVar1 = param_1[1]; lVar5 = param_1[2];
        iVar8 = *(s32*)(lVar1 + 0x48); lVar3 = lVar5;
        if (*(s32*)(lVar7+0x48) < iVar8) {
            if (iVar8 < *(s32*)(lVar5+0x48)) { *param_1 = lVar5; }
            else { *param_1 = lVar1; param_1[1] = lVar7;
                   if (*(s32*)(lVar5+0x48) <= *(s32*)(lVar7+0x48)) goto LAB_4f_ins;
                   param_1[1] = lVar5; }
            param_1[2] = lVar7; lVar3 = lVar7;
        } else if (iVar8 < *(s32*)(lVar5+0x48)) {
            param_1[1] = lVar5; param_1[2] = lVar1; lVar3 = lVar1;
            if (*(s32*)(lVar7+0x48) < *(s32*)(lVar5+0x48)) { *param_1=lVar5; param_1[1]=lVar7; }
        }
LAB_4f_ins:
        if (param_1 + 3 == param_2) return true;
        lVar_off = 0; iVar8 = 0; plVar2 = param_1 + 3;
        do {
            lVar5 = *plVar2; lOff2 = lVar_off;
            if (*(s32*)(lVar3+0x48) < *(s32*)(lVar5+0x48)) {
                for (;;) {
                    *(u64*)((u8*)param_1 + lOff2 + 0x18) = *(u64*)((u8*)param_1 + lOff2 + 0x10);
                    plVar4 = param_1;
                    if (lOff2 == -0x10) goto LAB_4f_place;
                    lOff2 -= 8;
                    if (!(*(s32*)(*(s64*)((u8*)param_1 + lOff2 + 8) + 0x48) < *(s32*)(lVar5+0x48))) break;
                }
                plVar4 = (s64*)((u8*)param_1 + lOff2 + 0x10);
LAB_4f_place:
                iVar8++; *plVar4 = lVar5;
                if (iVar8 == 8) return plVar2 + 1 == param_2;
            }
            if (plVar2 + 1 == param_2) return true;
            lVar3 = *plVar2; lVar_off += 8; plVar2++;
        } while (true);
    }
    param_2[-1] = lVar7;
    return true;
}

// ─────────────────────────────────────────────────────────────────────────
// FUN_71025a54a0  size=172
// Sort long* array [param_1, param_2) by DESCENDING *(int*)(elem+0x48).
// ─────────────────────────────────────────────────────────────────────────
bool FUN_71025a54a0(s64* param_1, s64* param_2)
{
    s64 lVar1, lVar3, lVar5, lVar7;
    s64* plVar2; s64* plVar4;
    int iVar8;
    int *piVar6, *piVar9, *piVar10;
    s64 lVar_off, lOff2;

    switch (((s64)param_2 - (s64)param_1) >> 3) {
    case 0: case 1: return true;
    case 2:
        lVar7 = *param_1;
        if (*(s32*)(lVar7 + 0x48) <= *(s32*)(param_2[-1] + 0x48)) return true;
        *param_1 = param_2[-1];
        break;
    case 3:
        lVar7 = *param_1; lVar1 = param_1[1]; lVar3 = param_2[-1];
        iVar8 = *(s32*)(lVar1 + 0x48);
        if (*(s32*)(lVar7+0x48) <= iVar8) {
            if (iVar8 <= *(s32*)(lVar3+0x48)) return true;
            param_1[1] = lVar3; param_2[-1] = lVar1;
            lVar7 = *param_1;
            if (*(s32*)(lVar7+0x48) <= *(s32*)(param_1[1]+0x48)) return true;
            *param_1 = param_1[1]; param_1[1] = lVar7; return true;
        }
        if (*(s32*)(lVar3+0x48) < iVar8) { *param_1 = lVar3; }
        else { *param_1 = lVar1; param_1[1] = lVar7;
               if (*(s32*)(lVar7+0x48) <= *(s32*)(param_2[-1]+0x48)) return true;
               param_1[1] = param_2[-1]; }
        break;
    case 4:
        lVar7 = *param_1; lVar1 = param_1[1]; piVar10 = (int*)(lVar1 + 0x48);
        iVar8 = *piVar10; piVar6 = (int*)(lVar7 + 0x48);
        lVar5 = param_1[2]; piVar9 = (int*)(lVar5 + 0x48); lVar3 = lVar5;
        if (iVar8 < *piVar6) {
            if (*piVar9 < iVar8) { *param_1=lVar5; param_1[2]=lVar7; lVar3=lVar7; piVar9=piVar6; }
            else { *param_1=lVar1; param_1[1]=lVar7;
                   if (*(s32*)(lVar5+0x48) < *(s32*)(lVar7+0x48)) { param_1[1]=lVar5; param_1[2]=lVar7; lVar3=lVar7; piVar9=piVar6; } }
        } else if (*piVar9 < iVar8) {
            param_1[1]=lVar5; param_1[2]=lVar1; lVar3=lVar1; piVar9=piVar10;
            if (*(s32*)(lVar5+0x48) < *piVar6) { *param_1=lVar5; param_1[1]=lVar7; }
        }
        if (*piVar9 <= *(s32*)(param_2[-1]+0x48)) return true;
        param_1[2] = param_2[-1]; param_2[-1] = lVar3;
        lVar7 = param_1[1]; lVar1 = param_1[2];
        if (*(s32*)(lVar7+0x48) <= *(s32*)(lVar1+0x48)) return true;
        lVar3 = *param_1; param_1[1]=lVar1; param_1[2]=lVar7;
        if (*(s32*)(lVar3+0x48) <= *(s32*)(lVar1+0x48)) return true;
        *param_1=lVar1; param_1[1]=lVar3; return true;
    case 5:
        FUN_71025a52a0(param_1, param_1+1, param_1+2, param_1+3, param_2-1);
        return true;
    default:
        lVar7 = *param_1; lVar1 = param_1[1]; lVar5 = param_1[2];
        iVar8 = *(s32*)(lVar1 + 0x48); lVar3 = lVar5;
        if (iVar8 < *(s32*)(lVar7+0x48)) {
            if (*(s32*)(lVar5+0x48) < iVar8) { *param_1=lVar5; }
            else { *param_1=lVar1; param_1[1]=lVar7;
                   if (*(s32*)(lVar7+0x48) <= *(s32*)(lVar5+0x48)) goto LAB_54_ins;
                   param_1[1]=lVar5; }
            param_1[2]=lVar7; lVar3=lVar7;
        } else if (*(s32*)(lVar5+0x48) < iVar8) {
            param_1[1]=lVar5; param_1[2]=lVar1; lVar3=lVar1;
            if (*(s32*)(lVar5+0x48) < *(s32*)(lVar7+0x48)) { *param_1=lVar5; param_1[1]=lVar7; }
        }
LAB_54_ins:
        if (param_1 + 3 == param_2) return true;
        lVar_off = 0; iVar8 = 0; plVar2 = param_1 + 3;
        do {
            lVar5 = *plVar2; lOff2 = lVar_off;
            if (*(s32*)(lVar5+0x48) < *(s32*)(lVar3+0x48)) {
                for (;;) {
                    *(u64*)((u8*)param_1 + lOff2 + 0x18) = *(u64*)((u8*)param_1 + lOff2 + 0x10);
                    plVar4 = param_1;
                    if (lOff2 == -0x10) goto LAB_54_place;
                    lOff2 -= 8;
                    if (!(*(s32*)(lVar5+0x48) < *(s32*)(*(s64*)((u8*)param_1 + lOff2 + 8) + 0x48))) break;
                }
                plVar4 = (s64*)((u8*)param_1 + lOff2 + 0x10);
LAB_54_place:
                iVar8++; *plVar4 = lVar5;
                if (iVar8 == 8) return plVar2 + 1 == param_2;
            }
            if (plVar2 + 1 == param_2) return true;
            lVar3 = *plVar2; lVar_off += 8; plVar2++;
        } while (true);
    }
    param_2[-1] = lVar7;
    return true;
}

// ─────────────────────────────────────────────────────────────────────────
// FUN_710266cd40  size=588
// Animation timer state machine: advances state, calling vtable slot 0x58.
// ─────────────────────────────────────────────────────────────────────────
void FUN_710266cd40(f32 param_1, s64* param_2)
{
    if (param_2 == nullptr) return;

    u32 state = *(u32*)((u8*)param_2 + 0x14);
    u32 uVar2;

    switch (state) {
    case 0:
        if (*(s8*)((u8*)param_2 + 0x10) != '\0') {
            *(u32*)((u8*)param_2 + 0x14) = 1;
            *(u8*)((u8*)param_2 + 0x10) = 0;
            return;
        }
        if (DAT_7104471598 <= param_1) return;
        uVar2 = 1;
        break;
    case 1:
        if (param_1 == DAT_71044723dc || param_1 < DAT_71044723dc) return;
        {
            s64* plVar1 = *(s64**)(*(s64*)(*param_2 + 0x338) + 8);
            if (plVar1 != nullptr)
                (*(void(**)(s64*, s32, s32))(*plVar1 + 0x58))(plVar1, 7, (s32)0xffffffff);
        }
        uVar2 = 3;
        break;
    default:
        return;
    case 3:
        if (param_1 == DAT_7104471aa4 || param_1 < DAT_7104471aa4) return;
        {
            s64* plVar1 = *(s64**)(*(s64*)(*param_2 + 0x338) + 8);
            if (plVar1 != nullptr)
                (*(void(**)(s64*, s32, s32))(*plVar1 + 0x58))(plVar1, 8, (s32)0xffffffff);
        }
        uVar2 = 4;
        break;
    case 4:
        if (param_1 == DAT_7104471008 || param_1 < DAT_7104471008) return;
        {
            s64* plVar1 = *(s64**)(*(s64*)(*param_2 + 0x338) + 8);
            if (plVar1 != nullptr)
                (*(void(**)(s64*, s32, s32))(*plVar1 + 0x58))(plVar1, 9, (s32)0xffffffff);
        }
        uVar2 = 6;
        break;
    case 6:
        if (param_1 != DAT_7104472454 && !(param_1 < DAT_7104472454)) {
            s64* plVar1 = *(s64**)(*(s64*)(*param_2 + 0x338) + 8);
            if (plVar1 != nullptr)
                (*(void(**)(s64*, s32, s32))(*plVar1 + 0x58))(plVar1, 10, (s32)0xffffffff);
            *(u32*)((u8*)param_2 + 0x14) = 0;
        }
        return;
    }
    *(u32*)((u8*)param_2 + 0x14) = uVar2;
}

// ─────────────────────────────────────────────────────────────────────────
// FUN_710279eb00  size=416
// Deactivate scene object: clear animation, set flags, trigger effect.
// ─────────────────────────────────────────────────────────────────────────
void FUN_710279eb00(u8* param_1)
{
    if (*(s32*)(param_1 + 0x14) != 0) return;

    s64 lVar3 = *(s64*)(param_1 + 0x40);
    if (lVar3 == 0) return;

    *(u8*)(lVar3 + 0x110) = 1;
    FUN_71025e9900((u8*)lVar3 + 0x108);

    u64 uVar1 = 0;
    if (*(s64*)(param_1 + 0x40) != 0) {
        FUN_71025ee000(0, *(u64*)(*(s64*)(param_1 + 0x40) + 0xd8), 1);
        lVar3 = *(s64*)(param_1 + 0x40);
        if (lVar3 != 0) {
            if ((*(s8*)(lVar3 + 0xe0) != '\0') && (*(s64*)(lVar3 + 200) != 0))
                *(u16*)(*(s64*)(lVar3 + 200) + 0x30) = 0;
            if (*(s64*)(lVar3 + 0xd8) != 0)
                *(u8*)(*(s64*)(lVar3 + 0xd8) + 0x21) = 0;
            if (*(s8*)(lVar3 + 0xe0) != '\0')
                *(u8*)(*(s64*)(lVar3 + 0xb0) + 0x10) = 1;
            lVar3 = *(s64*)(param_1 + 0x40);
            if (lVar3 != 0) {
                *(u8*)(lVar3 + 0x118) = *(u8*)(lVar3 + 0x118) & 0xfe;
                uVar1 = *(u64*)(param_1 + 0x40);
                goto LAB_continue;
            }
        }
    }
LAB_continue:
    {
        u32 uVar2 = (u32)(*(s32*)(param_1 + 0x54) != 0);
        *(u32*)(param_1 + 0x80) = uVar2;
        FUN_710260fdd0(uVar1, DAT_7104550c40[uVar2]);
        *(u32*)(param_1 + 0x14) = 1;
        *(u8*)(param_1 + 0x68) = 1;
        s32* piVar5 = *(s32**)(*(s64*)(param_1 + 8) + 0x2d0);
        s32* piVar6 = *(s32**)(*(s64*)(param_1 + 8) + 0x2d8);
        if (piVar5 != piVar6) {
            do {
                if ((*piVar5 == 0) || (*(s32*)(param_1 + 0x54) == *piVar5)) {
                    u64 local_40 = *(u64*)(piVar5 + 8);
                    s64 lVar4;
                    if ((*(u8*)((u8*)piVar5 + 8) & 1) == 0)
                        lVar4 = (s64)piVar5 + 9;
                    else
                        lVar4 = *(s64*)(piVar5 + 6);
                    s64 lVar3b = *(s64*)(param_1 + 0x40);
                    if ((lVar3b != 0) && (*(s8*)(lVar3b + 0xe0) != '\0')) {
                        (*(void(**)(u64, u64, s64*, s64, s32, void*))
                            (**(s64**)(lVar3b + 0x90) + 0x268))
                            (local_40, 0, *(s64**)(lVar3b + 0x90), lVar4, 0xd, &local_40);
                    }
                }
                piVar5 += 0xc;
            } while (piVar6 != piVar5);
        }
    }
}
