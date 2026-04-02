#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7103 address range, batch d2-006
// Pool-d worker: auto-generated from Ghidra decompilation

// ---- External declarations -----------------------------------------------

extern void FUN_710356ba40(u32, u64 *);
extern void FUN_710356bb20(void);
extern void FUN_710392e590(void *);
extern void FUN_71035993e0(u32, u32 *);
extern void FUN_71035e8fc0(u32, u32 *);

namespace nu {
    extern void VirtualFreeHook(void *);
}

// External data
extern u8 PTR_VirtualFreeHook_71052a7a70[];
extern u8 PTR_LAB_71052306d0[];
extern u8 PTR_LAB_710522f2c0[];
extern u8 PTR_LAB_7105230990[];
extern u8 PTR_LAB_71052309b0[];
extern u8 PTR_LAB_71052306f0[];
extern u8 PTR_LAB_7105230650[];
extern u8 PTR_LAB_7105230710[];
extern u8 PTR_LAB_7105230730[];
extern u8 PTR_LAB_7105230770[];
extern u8 PTR_LAB_7104f61038[];
extern u8 PTR_LAB_7105231e40[];
extern u8 PTR_LAB_7105231e00[];
extern u8 PTR_LAB_7105231e60[];
extern u8 PTR_LAB_7105230b10[];
extern u8 PTR_LAB_7105230ad0[];
extern u8 PTR_LAB_7105230af0[];

// ---- Functions ---------------------------------------------------------------

// 0x71035da3d0 — type-dispatch: read/copy typed value from source ptr (592 bytes)
void FUN_71035da3d0(u32 param_1, s64 *param_2, u64 *param_3)
{
    s64 lVar1;
    u64 *puVar2;
    s64 lVar3;
    u64 uVar4;
    u64 uVar5;
    u64 uVar6;
    void *pvVar7;
    u64 *puVar8;
    u64 *puVar9;
    u64 *puVar10;

    switch (param_1) {
    case 0: case 1: case 0x12:
        *(u32 *)param_3 = *(u32 *)*param_2;
        break;
    case 2:
        *(u8 *)param_3 = *(u8 *)*param_2;
        break;
    case 3:
        *param_3 = *(u64 *)*param_2;
        break;
    case 4:
    case 10:
        uVar4 = *(u64 *)*param_2;
        *(u32 *)(param_3 + 1) = *(u32 *)((u64 *)*param_2 + 1);
        *param_3 = uVar4;
        break;
    case 5: case 6: case 7:
        uVar4 = ((u64 *)*param_2)[1];
        *param_3 = *(u64 *)*param_2;
        param_3[1] = uVar4;
        break;
    case 8:
        puVar2 = (u64 *)*param_2;
        uVar4 = *puVar2;
        uVar5 = puVar2[1];
        uVar6 = puVar2[3];
        param_3[2] = puVar2[2];
        param_3[3] = uVar6;
        *param_3 = uVar4;
        param_3[1] = uVar5;
        uVar4 = puVar2[4];
        uVar5 = puVar2[5];
        uVar6 = puVar2[7];
        param_3[6] = puVar2[6];
        param_3[7] = uVar6;
        param_3[4] = uVar4;
        param_3[5] = uVar5;
        break;
    case 9:
        puVar2 = (u64 *)*param_2;
        pvVar7 = (void *)*param_3;
        if (pvVar7 != nullptr) {
            param_3[1] = (u64)pvVar7;
            if (*(u8 **)PTR_VirtualFreeHook_71052a7a70 != nullptr) {
                nu::VirtualFreeHook(pvVar7);
            }
            FUN_710392e590(pvVar7);
            param_3[1] = 0;
            param_3[2] = 0;
            *param_3 = 0;
        }
        *param_3 = *puVar2;
        param_3[1] = puVar2[1];
        goto LAB_71035da5f8;
    case 0xb: case 0xd: case 0x10: case 0x11:
        lVar1 = *param_2;
        if ((*(s64 **)(lVar1 + 0x10) == nullptr) ||
            (**(s64 **)(lVar1 + 0x10) != *(s64 *)(lVar1 + 0x18))) goto LAB_71035da524;
        lVar1 = *(s64 *)(lVar1 + 8);
        param_3[1] = (u64)lVar1;
        if (lVar1 != 0) {
            puVar2 = *(u64 **)(lVar1 + 8);
            goto LAB_71035da5ac;
        }
        goto LAB_71035da528;
    case 0xc:
        puVar2 = (u64 *)*param_2;
        puVar10 = (u64 *)*param_3;
        if (puVar10 != nullptr) {
            puVar8 = (u64 *)param_3[1];
            puVar9 = puVar10;
            if (puVar8 != puVar10) {
                do {
                    puVar8 = puVar8 - 4;
                    (*(void (*)(u64 *))(*(u64 *)*puVar8))(puVar8);
                } while (puVar10 != puVar8);
                puVar9 = (u64 *)*param_3;
            }
            param_3[1] = (u64)puVar10;
            if (*(u8 **)PTR_VirtualFreeHook_71052a7a70 != nullptr) {
                nu::VirtualFreeHook(puVar9);
            }
            FUN_710392e590(puVar9);
            param_3[1] = 0;
            param_3[2] = 0;
            *param_3 = 0;
        }
        *param_3 = *puVar2;
        param_3[1] = puVar2[1];
LAB_71035da5f8:
        param_3[2] = puVar2[2];
        *puVar2 = 0;
        puVar2[1] = 0;
        puVar2[2] = 0;
        break;
    case 0xe:
        lVar1 = *param_2;
        if ((*(s64 **)(lVar1 + 0x10) != nullptr) &&
            (lVar3 = *(s64 *)(lVar1 + 8),
             **(s64 **)(lVar1 + 0x10) == *(s64 *)(lVar1 + 0x18) && lVar3 != 0)) {
            param_3[1] = (u64)lVar3;
            puVar2 = *(u64 **)(lVar3 + 0x60);
LAB_71035da5ac:
            param_3[2] = (u64)puVar2;
            param_3[3] = *puVar2;
            return;
        }
LAB_71035da524:
        param_3[1] = 0;
LAB_71035da528:
        param_3[2] = 0;
        param_3[3] = 0;
        break;
    case 0xf:
        puVar2 = (u64 *)*param_2;
        uVar4 = *puVar2;
        uVar5 = puVar2[2];
        param_3[1] = puVar2[1];
        param_3[2] = uVar5;
        *param_3 = uVar4;
        uVar4 = puVar2[3];
        uVar5 = puVar2[4];
        uVar6 = puVar2[5];
        *(u32 *)(param_3 + 6) = *(u32 *)(puVar2 + 6);
        param_3[4] = uVar5;
        param_3[5] = uVar6;
        param_3[3] = uVar4;
        break;
    default:
        FUN_710356bb20();
    }
    return;
}

// 0x71035da620 — type-dispatch: write typed value into dest via FUN_710356ba40 (800 bytes)
void FUN_71035da620(u32 param_1, s64 *param_2, u64 *param_3)
{
    u32 uVar1;
    s64 lVar2;
    u64 uVar3;
    u64 uVar4;
    u64 uVar5;

    switch (param_1) {
    case 0: case 1: case 0x12:
        uVar1 = *(u32 *)*param_2;
        FUN_710356ba40(uVar1 ^ (s32)uVar1 >> 0x1f, (u64 *)(*param_2 + 8));
        *(u32 *)(*param_2 + 8) = *(u32 *)param_3;
        break;
    case 2:
        uVar1 = *(u32 *)*param_2;
        FUN_710356ba40(uVar1 ^ (s32)uVar1 >> 0x1f, (u64 *)(*param_2 + 8));
        *(u8 *)(*param_2 + 8) = *(u8 *)param_3;
        break;
    case 3:
        uVar1 = *(u32 *)*param_2;
        FUN_710356ba40(uVar1 ^ (s32)uVar1 >> 0x1f, (u64 *)(*param_2 + 8));
        *(u64 *)(*param_2 + 8) = *param_3;
        break;
    case 4:
        uVar1 = *(u32 *)*param_2;
        FUN_710356ba40(uVar1 ^ (s32)uVar1 >> 0x1f, (u64 *)(*param_2 + 8));
        lVar2 = *param_2;
        uVar3 = *param_3;
        *(u32 *)(lVar2 + 0x10) = *(u32 *)(param_3 + 1);
        *(u64 *)(lVar2 + 8) = uVar3;
        break;
    case 5: case 6: case 7: case 10:
        uVar1 = *(u32 *)*param_2;
        FUN_710356ba40(uVar1 ^ (s32)uVar1 >> 0x1f, (u64 *)(*param_2 + 8));
        lVar2 = *param_2;
        uVar3 = param_3[1];
        *(u64 *)(lVar2 + 8) = *param_3;
        *(u64 *)(lVar2 + 0x10) = uVar3;
        break;
    case 8:
        uVar1 = *(u32 *)*param_2;
        FUN_710356ba40(uVar1 ^ (s32)uVar1 >> 0x1f, (u64 *)(*param_2 + 8));
        lVar2 = *param_2;
        uVar3 = *param_3;
        uVar4 = param_3[1];
        uVar5 = param_3[3];
        *(u64 *)(lVar2 + 0x18) = param_3[2];
        *(u64 *)(lVar2 + 0x20) = uVar5;
        *(u64 *)(lVar2 + 8) = uVar3;
        *(u64 *)(lVar2 + 0x10) = uVar4;
        uVar3 = param_3[4];
        uVar4 = param_3[5];
        uVar5 = param_3[7];
        *(u64 *)(lVar2 + 0x38) = param_3[6];
        *(u64 *)(lVar2 + 0x40) = uVar5;
        *(u64 *)(lVar2 + 0x28) = uVar3;
        *(u64 *)(lVar2 + 0x30) = uVar4;
        break;
    case 9: case 0xc:
        uVar1 = *(u32 *)*param_2;
        FUN_710356ba40(uVar1 ^ (s32)uVar1 >> 0x1f, (u64 *)(*param_2 + 8));
        lVar2 = *param_2;
        *(u64 *)(lVar2 + 0x10) = 0;
        *(u64 *)(lVar2 + 0x18) = 0;
        *(u64 *)(lVar2 + 8) = 0;
        *(u64 *)(lVar2 + 8) = *param_3;
        *(u64 *)(lVar2 + 0x10) = param_3[1];
        *(u64 *)(lVar2 + 0x18) = param_3[2];
        param_3[1] = 0;
        param_3[2] = 0;
        *param_3 = 0;
        break;
    case 0xb:
        uVar1 = *(u32 *)*param_2;
        FUN_710356ba40(uVar1 ^ (s32)uVar1 >> 0x1f, (u64 *)(*param_2 + 8));
        lVar2 = *param_2;
        *(u8 **)(lVar2 + 8) = PTR_LAB_71052306d0;
        *(u64 *)(lVar2 + 0x10) = param_3[1];
        *(u64 *)(lVar2 + 0x18) = param_3[2];
        *(u64 *)(lVar2 + 0x20) = param_3[3];
        *(u8 **)(lVar2 + 8) = PTR_LAB_710522f2c0;
        break;
    case 0xd:
        uVar1 = *(u32 *)*param_2;
        FUN_710356ba40(uVar1 ^ (s32)uVar1 >> 0x1f, (u64 *)(*param_2 + 8));
        lVar2 = *param_2;
        *(u8 **)(lVar2 + 8) = PTR_LAB_7105230990;
        *(u64 *)(lVar2 + 0x10) = param_3[1];
        *(u64 *)(lVar2 + 0x18) = param_3[2];
        *(u64 *)(lVar2 + 0x20) = param_3[3];
        *(u8 **)(lVar2 + 8) = PTR_LAB_71052309b0;
        break;
    case 0xe:
        uVar1 = *(u32 *)*param_2;
        FUN_710356ba40(uVar1 ^ (s32)uVar1 >> 0x1f, (u64 *)(*param_2 + 8));
        lVar2 = *param_2;
        *(u8 **)(lVar2 + 8) = PTR_LAB_71052306f0;
        *(u64 *)(lVar2 + 0x10) = param_3[1];
        *(u64 *)(lVar2 + 0x18) = param_3[2];
        *(u64 *)(lVar2 + 0x20) = param_3[3];
        *(u8 **)(lVar2 + 8) = PTR_LAB_7105230650;
        break;
    case 0xf:
        uVar1 = *(u32 *)*param_2;
        FUN_710356ba40(uVar1 ^ (s32)uVar1 >> 0x1f, (u64 *)(*param_2 + 8));
        lVar2 = *param_2;
        uVar3 = *param_3;
        uVar4 = param_3[2];
        *(u64 *)(lVar2 + 0x10) = param_3[1];
        *(u64 *)(lVar2 + 0x18) = uVar4;
        *(u64 *)(lVar2 + 8) = uVar3;
        uVar3 = param_3[3];
        uVar4 = param_3[4];
        uVar5 = param_3[5];
        *(u32 *)(lVar2 + 0x38) = *(u32 *)(param_3 + 6);
        *(u64 *)(lVar2 + 0x28) = uVar4;
        *(u64 *)(lVar2 + 0x30) = uVar5;
        *(u64 *)(lVar2 + 0x20) = uVar3;
        break;
    case 0x10:
        uVar1 = *(u32 *)*param_2;
        FUN_710356ba40(uVar1 ^ (s32)uVar1 >> 0x1f, (u64 *)(*param_2 + 8));
        lVar2 = *param_2;
        *(u8 **)(lVar2 + 8) = PTR_LAB_7105230710;
        *(u64 *)(lVar2 + 0x10) = param_3[1];
        *(u64 *)(lVar2 + 0x18) = param_3[2];
        *(u64 *)(lVar2 + 0x20) = param_3[3];
        *(u8 **)(lVar2 + 8) = PTR_LAB_7105230730;
        break;
    case 0x11:
        uVar1 = *(u32 *)*param_2;
        FUN_710356ba40(uVar1 ^ (s32)uVar1 >> 0x1f, (u64 *)(*param_2 + 8));
        lVar2 = *param_2;
        *(u8 **)(lVar2 + 8) = PTR_LAB_7105230770;
        *(u64 *)(lVar2 + 0x10) = param_3[1];
        *(u64 *)(lVar2 + 0x18) = param_3[2];
        *(u64 *)(lVar2 + 0x20) = param_3[3];
        *(u8 **)(lVar2 + 8) = PTR_LAB_7104f61038;
        break;
    default:
        FUN_710356bb20();
    }
    *(s32 *)*param_2 = (s32)param_2[1];
    return;
}

// 0x71035e7a50 — type-dispatch: assign observable typed value (272 bytes)
void FUN_71035e7a50(u32 param_1, s64 *param_2, s64 param_3)
{
    u32 uVar1;
    s64 lVar2;
    u64 *puVar3;
    s64 lVar4;

    switch (param_1) {
    case 0:
        uVar1 = *(u32 *)*param_2;
        FUN_71035e8fc0(uVar1 ^ (s32)uVar1 >> 0x1f, (u32 *)(*param_2 + 2));
        lVar2 = *param_2;
        *(u8 **)(lVar2 + 8) = PTR_LAB_7105231e40;
        *(u64 *)(lVar2 + 0x10) = *(u64 *)(param_3 + 8);
        *(u64 *)(lVar2 + 0x18) = *(u64 *)(param_3 + 0x10);
        *(u64 *)(lVar2 + 0x20) = *(u64 *)(param_3 + 0x18);
        *(u8 **)(lVar2 + 8) = PTR_LAB_7105231e00;
        break;
    case 1:
        uVar1 = *(u32 *)*param_2;
        FUN_71035e8fc0(uVar1 ^ (s32)uVar1 >> 0x1f, (u32 *)(*param_2 + 2));
        lVar2 = *param_2;
        *(s64 *)(lVar2 + 0x10) = 0;
        *(u64 *)(lVar2 + 0x18) = 0;
        *(u64 *)(lVar2 + 0x20) = 0;
        *(u8 **)(lVar2 + 8) = PTR_LAB_7105231e60;
        if ((*(s64 **)(param_3 + 0x10) != nullptr) &&
            (**(s64 **)(param_3 + 0x10) == *(s64 *)(param_3 + 0x18))) {
            lVar4 = *(s64 *)(param_3 + 8);
            *(u64 *)(param_3 + 0x10) = 0;
            *(u64 *)(param_3 + 0x18) = 0;
            *(u64 *)(param_3 + 8) = 0;
            *(s64 *)(lVar2 + 0x10) = lVar4;
            if (lVar4 == 0) {
                *(u64 *)(lVar2 + 0x18) = 0;
                *(u64 *)(lVar2 + 0x20) = 0;
            } else {
                puVar3 = *(u64 **)(lVar4 + 8);
                *(u64 **)(lVar2 + 0x18) = puVar3;
                *(u64 *)(lVar2 + 0x20) = *puVar3;
            }
        }
        break;
    default:
        FUN_710356bb20();
    }
    *(s32 *)*param_2 = (s32)param_2[1];
    return;
}

// 0x71035e99f0 — type-dispatch: assign observable typed value variant B (1472 bytes)
void FUN_71035e99f0(u32 param_1, s64 *param_2, s64 param_3)
{
    u32 uVar1;
    s64 lVar2;
    u64 *puVar3;
    s64 lVar4;

    switch (param_1) {
    case 0:
        uVar1 = *(u32 *)*param_2;
        FUN_71035993e0(uVar1 ^ (s32)uVar1 >> 0x1f, (u32 *)(*param_2 + 2));
        lVar2 = *param_2;
        *(u8 **)(lVar2 + 8) = PTR_LAB_7105230b10;
        *(u64 *)(lVar2 + 0x10) = *(u64 *)(param_3 + 8);
        *(u64 *)(lVar2 + 0x18) = *(u64 *)(param_3 + 0x10);
        *(u64 *)(lVar2 + 0x20) = *(u64 *)(param_3 + 0x18);
        *(u8 **)(lVar2 + 8) = PTR_LAB_7105230ad0;
        break;
    case 1:
        uVar1 = *(u32 *)*param_2;
        FUN_71035993e0(uVar1 ^ (s32)uVar1 >> 0x1f, (u32 *)(*param_2 + 2));
        lVar2 = *param_2;
        *(s64 *)(lVar2 + 0x10) = 0;
        *(u64 *)(lVar2 + 0x18) = 0;
        *(u64 *)(lVar2 + 0x20) = 0;
        *(u8 **)(lVar2 + 8) = PTR_LAB_7105230af0;
        if ((*(s64 **)(param_3 + 0x10) != nullptr) &&
            (**(s64 **)(param_3 + 0x10) == *(s64 *)(param_3 + 0x18))) {
            lVar4 = *(s64 *)(param_3 + 8);
            *(u64 *)(param_3 + 0x10) = 0;
            *(u64 *)(param_3 + 0x18) = 0;
            *(u64 *)(param_3 + 8) = 0;
            *(s64 *)(lVar2 + 0x10) = lVar4;
            if (lVar4 == 0) {
                *(u64 *)(lVar2 + 0x18) = 0;
                *(u64 *)(lVar2 + 0x20) = 0;
            } else {
                puVar3 = *(u64 **)(lVar4 + 8);
                *(u64 **)(lVar2 + 0x18) = puVar3;
                *(u64 *)(lVar2 + 0x20) = *puVar3;
            }
        }
        break;
    default:
        FUN_710356bb20();
    }
    *(s32 *)*param_2 = (s32)param_2[1];
    return;
}
