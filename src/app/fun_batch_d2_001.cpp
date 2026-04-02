#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7103 address range, batch d2-001
// Pool-d worker: auto-generated from Ghidra decompilation

// ---- External declarations -----------------------------------------------

extern "C" void abort();

extern void FUN_710377a930(u32, s64);
extern "C" void ui2d_apply_named_animation(u32, u64, const char *);

// External data
extern void *DAT_71052b5fd8;   // pointer to singleton with collision region list
extern float DAT_7104471398;   // float constant (default rate)
extern float DAT_7104471b54;   // float constant (alt rate)
extern u8 DAT_710532e7b0[];    // pointer-to-manager base

// ---- Functions ---------------------------------------------------------------

// 0x710317d6e0 — collision region submit: read rect from param_1, find free slot, write and tag (1424 bytes)
void FUN_710317d6e0(s64 param_1)
{
    char cVar1;
    s32 *piVar6;
    s32 iVar3;
    s64 lVar4;
    u8 uVar5;
    u8 *puVar7;
    float fVar8;
    float fVar9;
    float fVar10;
    float fVar11;
    float fVar12;

    if ((*(u8 *)(param_1 + 9) != '\0') || (*(u8 *)(param_1 + 8) == '\0'))
        goto LAB_710317dc60;

    switch (*(u32 *)(param_1 + 0x40)) {
    case 1:
        fVar9 = *(float *)(param_1 + 0x10);
        fVar11 = *(float *)(param_1 + 0x20);
        fVar10 = *(float *)(param_1 + 0x14);
        fVar8 = fVar9;
        if (fVar11 <= fVar9) { fVar8 = fVar11; fVar11 = fVar9; }
        fVar12 = *(float *)(param_1 + 0x24);
        piVar6 = *(s32 **)(*(s64 *)&DAT_71052b5fd8 + 0xc0);
        fVar9 = fVar12;
        if (fVar12 <= fVar10) { fVar9 = fVar10; fVar10 = fVar12; }
        if (*(u8 *)((s64)piVar6 + 0x464) == '\0') { lVar4 = 0; }
        else if (*(u8 *)((s64)piVar6 + 0x465) == '\0') { lVar4 = 1; }
        else if (*(u8 *)((s64)piVar6 + 0x466) == '\0') { lVar4 = 2; }
        else if (*(u8 *)((s64)piVar6 + 0x467) == '\0') { lVar4 = 3; }
        else if (*(u8 *)((s64)piVar6 + 0x468) == '\0') { lVar4 = 4; }
        else if (*(u8 *)((s64)piVar6 + 0x469) == '\0') { lVar4 = 5; }
        else if (*(u8 *)((s64)piVar6 + 0x46a) == '\0') { lVar4 = 6; }
        else {
            if (*(u8 *)((s64)piVar6 + 0x46b) != '\0') { lVar4 = 0xffffffff; break; }
            lVar4 = 7;
        }
        piVar6[lVar4 * 5 + 1] = (s32)fVar8;
        piVar6[lVar4 * 5 + 2] = (s32)fVar11;
        piVar6[lVar4 * 5 + 3] = (s32)fVar9;
        piVar6[lVar4 * 5 + 4] = (s32)fVar10;
        piVar6[lVar4 * 5 + 5] = -1;
        cVar1 = *(u8 *)((s64)piVar6 + lVar4 + 0x464);
        if (cVar1 != 'A') {
            puVar7 = (u8 *)((s64)piVar6 + lVar4 + 0x464);
            if (cVar1 == '\0') { *piVar6 = *piVar6 + 1; }
            uVar5 = 0x41;
            *puVar7 = uVar5;
        }
        break;
    case 2:
        fVar9 = *(float *)(param_1 + 0x10);
        fVar11 = *(float *)(param_1 + 0x20);
        fVar10 = *(float *)(param_1 + 0x14);
        fVar8 = fVar9;
        if (fVar11 <= fVar9) { fVar8 = fVar11; fVar11 = fVar9; }
        fVar12 = *(float *)(param_1 + 0x24);
        piVar6 = *(s32 **)(*(s64 *)&DAT_71052b5fd8 + 0xc0);
        fVar9 = fVar12;
        if (fVar12 <= fVar10) { fVar9 = fVar10; fVar10 = fVar12; }
        if (*(u8 *)((s64)piVar6 + 0x464) == '\0') { lVar4 = 0; }
        else if (*(u8 *)((s64)piVar6 + 0x465) == '\0') { lVar4 = 1; }
        else if (*(u8 *)((s64)piVar6 + 0x466) == '\0') { lVar4 = 2; }
        else if (*(u8 *)((s64)piVar6 + 0x467) == '\0') { lVar4 = 3; }
        else if (*(u8 *)((s64)piVar6 + 0x468) == '\0') { lVar4 = 4; }
        else if (*(u8 *)((s64)piVar6 + 0x469) == '\0') { lVar4 = 5; }
        else if (*(u8 *)((s64)piVar6 + 0x46a) == '\0') { lVar4 = 6; }
        else {
            if (*(u8 *)((s64)piVar6 + 0x46b) != '\0') { lVar4 = 0xffffffff; break; }
            lVar4 = 7;
        }
        piVar6[lVar4 * 5 + 1] = (s32)fVar8;
        piVar6[lVar4 * 5 + 2] = (s32)fVar11;
        piVar6[lVar4 * 5 + 3] = (s32)fVar9;
        piVar6[lVar4 * 5 + 4] = (s32)fVar10;
        piVar6[lVar4 * 5 + 5] = -1;
        cVar1 = *(u8 *)((s64)piVar6 + lVar4 + 0x464);
        if (cVar1 != '\x03') {
            puVar7 = (u8 *)((s64)piVar6 + lVar4 + 0x464);
            if (cVar1 == '\0') { *piVar6 = *piVar6 + 1; }
            uVar5 = 3;
            *puVar7 = uVar5;
        }
        break;
    case 3:
        fVar9 = *(float *)(param_1 + 0x10);
        fVar11 = *(float *)(param_1 + 0x20);
        fVar10 = *(float *)(param_1 + 0x14);
        fVar8 = fVar9;
        if (fVar11 <= fVar9) { fVar8 = fVar11; fVar11 = fVar9; }
        fVar12 = *(float *)(param_1 + 0x24);
        piVar6 = *(s32 **)(*(s64 *)&DAT_71052b5fd8 + 0xc0);
        fVar9 = fVar12;
        if (fVar12 <= fVar10) { fVar9 = fVar10; fVar10 = fVar12; }
        if (*(u8 *)((s64)piVar6 + 0x464) == '\0') { lVar4 = 0; }
        else if (*(u8 *)((s64)piVar6 + 0x465) == '\0') { lVar4 = 1; }
        else if (*(u8 *)((s64)piVar6 + 0x466) == '\0') { lVar4 = 2; }
        else if (*(u8 *)((s64)piVar6 + 0x467) == '\0') { lVar4 = 3; }
        else if (*(u8 *)((s64)piVar6 + 0x468) == '\0') { lVar4 = 4; }
        else if (*(u8 *)((s64)piVar6 + 0x469) == '\0') { lVar4 = 5; }
        else if (*(u8 *)((s64)piVar6 + 0x46a) == '\0') { lVar4 = 6; }
        else {
            if (*(u8 *)((s64)piVar6 + 0x46b) != '\0') { lVar4 = 0xffffffff; break; }
            lVar4 = 7;
        }
        piVar6[lVar4 * 5 + 1] = (s32)fVar8;
        piVar6[lVar4 * 5 + 2] = (s32)fVar11;
        piVar6[lVar4 * 5 + 3] = (s32)fVar9;
        piVar6[lVar4 * 5 + 4] = (s32)fVar10;
        piVar6[lVar4 * 5 + 5] = -1;
        cVar1 = *(u8 *)((s64)piVar6 + lVar4 + 0x464);
        if (cVar1 != '\x81') {
            puVar7 = (u8 *)((s64)piVar6 + lVar4 + 0x464);
            if (cVar1 == '\0') { *piVar6 = *piVar6 + 1; }
            uVar5 = 0x81;
            *puVar7 = uVar5;
        }
        break;
    case 4:
        fVar9 = *(float *)(param_1 + 0x10);
        fVar11 = *(float *)(param_1 + 0x20);
        fVar10 = *(float *)(param_1 + 0x14);
        fVar8 = fVar9;
        if (fVar11 <= fVar9) { fVar8 = fVar11; fVar11 = fVar9; }
        fVar12 = *(float *)(param_1 + 0x24);
        piVar6 = *(s32 **)(*(s64 *)&DAT_71052b5fd8 + 0xc0);
        fVar9 = fVar12;
        if (fVar12 <= fVar10) { fVar9 = fVar10; fVar10 = fVar12; }
        if (*(u8 *)((s64)piVar6 + 0x464) == '\0') { lVar4 = 0; }
        else if (*(u8 *)((s64)piVar6 + 0x465) == '\0') { lVar4 = 1; }
        else if (*(u8 *)((s64)piVar6 + 0x466) == '\0') { lVar4 = 2; }
        else if (*(u8 *)((s64)piVar6 + 0x467) == '\0') { lVar4 = 3; }
        else if (*(u8 *)((s64)piVar6 + 0x468) == '\0') { lVar4 = 4; }
        else if (*(u8 *)((s64)piVar6 + 0x469) == '\0') { lVar4 = 5; }
        else if (*(u8 *)((s64)piVar6 + 0x46a) == '\0') { lVar4 = 6; }
        else {
            if (*(u8 *)((s64)piVar6 + 0x46b) != '\0') { lVar4 = 0xffffffff; break; }
            lVar4 = 7;
        }
        piVar6[lVar4 * 5 + 1] = (s32)fVar8;
        piVar6[lVar4 * 5 + 2] = (s32)fVar11;
        piVar6[lVar4 * 5 + 3] = (s32)fVar9;
        piVar6[lVar4 * 5 + 4] = (s32)fVar10;
        piVar6[lVar4 * 5 + 5] = -1;
        cVar1 = *(u8 *)((s64)piVar6 + lVar4 + 0x464);
        if (cVar1 != ' ') {
            puVar7 = (u8 *)((s64)piVar6 + lVar4 + 0x464);
            if (cVar1 == '\0') { *piVar6 = *piVar6 + 1; }
            uVar5 = 0x20;
            *puVar7 = uVar5;
        }
        break;
    default:
        fVar9 = *(float *)(param_1 + 0x10);
        fVar11 = *(float *)(param_1 + 0x20);
        fVar10 = *(float *)(param_1 + 0x14);
        fVar8 = fVar9;
        if (fVar11 <= fVar9) { fVar8 = fVar11; fVar11 = fVar9; }
        fVar12 = *(float *)(param_1 + 0x24);
        piVar6 = *(s32 **)(*(s64 *)&DAT_71052b5fd8 + 0xc0);
        fVar9 = fVar12;
        if (fVar12 <= fVar10) { fVar9 = fVar10; fVar10 = fVar12; }
        if (*(u8 *)((s64)piVar6 + 0x464) == '\0') { lVar4 = 0; }
        else if (*(u8 *)((s64)piVar6 + 0x465) == '\0') { lVar4 = 1; }
        else if (*(u8 *)((s64)piVar6 + 0x466) == '\0') { lVar4 = 2; }
        else if (*(u8 *)((s64)piVar6 + 0x467) == '\0') { lVar4 = 3; }
        else if (*(u8 *)((s64)piVar6 + 0x468) == '\0') { lVar4 = 4; }
        else if (*(u8 *)((s64)piVar6 + 0x469) == '\0') { lVar4 = 5; }
        else if (*(u8 *)((s64)piVar6 + 0x46a) == '\0') { lVar4 = 6; }
        else {
            if (*(u8 *)((s64)piVar6 + 0x46b) != '\0') { lVar4 = 0xffffffff; break; }
            lVar4 = 7;
        }
        piVar6[lVar4 * 5 + 1] = (s32)fVar8;
        piVar6[lVar4 * 5 + 2] = (s32)fVar11;
        piVar6[lVar4 * 5 + 3] = (s32)fVar9;
        piVar6[lVar4 * 5 + 4] = (s32)fVar10;
        piVar6[lVar4 * 5 + 5] = -1;
        cVar1 = *(u8 *)((s64)piVar6 + lVar4 + 0x464);
        if (cVar1 != '\t') {
            puVar7 = (u8 *)((s64)piVar6 + lVar4 + 0x464);
            if (cVar1 == '\0') { *piVar6 = *piVar6 + 1; }
            uVar5 = 9;
            *puVar7 = uVar5;
        }
    }

    iVar3 = (s32)lVar4;
    *(s32 *)(param_1 + 0xc) = iVar3;
    if ((iVar3 != -1) && (*(u32 *)(param_1 + 0x40) < 5)) {
        piVar6 = *(s32 **)(*(s64 *)&DAT_71052b5fd8 + 0xc0);
        if (*(u8 *)((s64)piVar6 + iVar3 + 0x464) != '\0') {
            s64 lVar4b = *(s64 *)&DAT_71052b5fd8;
            lVar4b = *(s64 *)(lVar4b + 0xc0) + (s64)iVar3 * 0x14;
            *(float *)(lVar4b + 4) = *(float *)(lVar4b + 4) + *(float *)(param_1 + 0x30);
            *(float *)(lVar4b + 8) = *(float *)(lVar4b + 8) + *(float *)(param_1 + 0x30);
            *(float *)(lVar4b + 0xc) = *(float *)(lVar4b + 0xc) + *(float *)(param_1 + 0x34);
            *(float *)(lVar4b + 0x10) = *(float *)(lVar4b + 0x10) + *(float *)(param_1 + 0x34);
        }
    }
    *(u8 *)(param_1 + 9) = 1;

LAB_710317dc60:
    *(u8 *)(param_1 + 10) = 1;
    return;
}

// 0x71032d05a0 — tournament UI slot set: update anim state based on resource callback (688 bytes)
void FUN_71032d05a0(s64 param_1, u32 param_2, s64 param_3)
{
    s64 lVar1;
    s64 lVar2;
    float fVar3;

    if (9 < param_2) {
        abort();
    }
    *(s64 *)(param_1 + (s64)(s32)param_2 * 0x130 + 0x110) = param_3;
    if (param_3 == 0) {
        lVar2 = (s64)(s32)param_2;
        lVar1 = param_1 + lVar2 * 0x130;
        if (*(u8 *)(lVar1 + 0x11f) != '\0') {
            *(u8 *)(lVar1 + 0x11f) = 0;
            fVar3 = DAT_7104471398;
            if (((*(s32 *)(param_1 + lVar2 * 0x130 + 0x10) == 1) &&
                 (*(u8 *)(param_1 + lVar2 * 0x130 + 0x11e) != '\0')) &&
                (*(u8 *)(param_1 + lVar2 * 0x130 + 0x126) != '\0')) {
                fVar3 = DAT_7104471b54;
            }
            lVar1 = param_1 + lVar2 * 0x130;
            *(float *)(lVar1 + 0x104) = fVar3;
            *(float *)(lVar1 + 0x10c) = fVar3 * *(float *)(lVar1 + 0x100);
            if ((*(s64 *)(*(s64 *)(lVar1 + 0x88)) != 0) &&
                ((*(s64 **)(lVar1 + 0x88))[1] != 0)) {
                FUN_710377a930(0x3f800000, lVar1 + 0x80);
            }
            if (*(s32 *)(param_1 + lVar2 * 0x130 + 0x14) == 2) {
                ui2d_apply_named_animation(0x3f800000,
                    *(u64 *)(param_1 + lVar2 * 0x130 + 0x28), "tournament_off");
                return;
            }
        }
    }
    return;
}

// 0x71032e2f20 — stage mode to hash40 constant lookup (small)
u64 FUN_71032e2f20(u64 param_1)
{
    s32 iVar1;
    u64 uVar2;

    iVar1 = *(s32 *)(*(s64 *)(DAT_710532e7b0 + 8) + 0x210);
    if (iVar1 == 0x11) {
        uVar2 = 0x58ffff270aab93dcULL;
        if ((param_1 & 1) == 0) {
            uVar2 = 0x58ffff0000000000ULL;
        }
        return uVar2;
    }
    if (iVar1 != 3) {
        if (iVar1 == 2) {
            return 0x58ffff27d91566bfULL;
        }
        return 0x58ffff0000000000ULL;
    }
    return 0x58ffff202a6b270cULL;
}
