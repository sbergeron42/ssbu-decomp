// Batch C - 015: MEDIUM FUN_* batch decompilation (mixed ranges)
// Functions: 9 - Misc compilable functions from broader 0x7102 range

#include "types.h"

typedef void (*CodePtr)();

extern "C" void FUN_710313e970();
extern "C" void FUN_710062dc20(u64, const char *, u32);
extern "C" void FUN_7102523c10();
extern "C" void FUN_7102524ce0();
extern "C" void FUN_7102524e70();
extern "C" void FUN_7102525000();
extern "C" void FUN_7102525180();
extern "C" void FUN_7102523d70(u64, u64, CodePtr *);

// 0x710261d790
u64 FUN_710261d790(u32 param_1)
{
    switch(param_1) {
    case 0x9b:
    case 0x9c:
    case 0x9d:
    case 0xda:
    case 0xdb:
    case 0xdc:
    case 0xe0:
    case 0xe1:
    case 0xe2:
    case 0x113:
    case 0x114:
    case 0x115:
    case 0x116:
    case 0x117:
    case 0x118:
    case 0x119:
    case 0x11a:
    case 0x11b:
    case 0x11f:
    case 0x120:
    case 0x121:
        return 1;
    default:
        return 0;
    }
}

// 0x7102c5ea20
u64 FUN_7102c5ea20(s64 param_1)
{
    s64 *iter;
    s64 *end;
    end = *(s64 **)(param_1 + 0x70);
    for (iter = *(s64 **)(param_1 + 0x68); iter != end; iter = iter + 1) {
        if (*iter != 0) {
            FUN_710313e970();
        }
    }
    return 1;
}

// 0x7102ef5030
u64 FUN_7102ef5030(u64 param_1, u32 param_2, u64 param_3)
{
    FUN_710062dc20(param_3, "resultstage_effect_set_%02d", param_2);
    return 1;
}

// 0x7102528a50
void FUN_7102528a50(u64 *param_1, u8 param_2)
{
    u64 uVar1;
    u64 uVar2;
    CodePtr local_18;

    switch(param_2) {
    case 0:
        uVar2 = *param_1;
        uVar1 = param_1[1];
        local_18 = FUN_7102523c10;
        break;
    case 1:
        uVar2 = *param_1;
        uVar1 = param_1[1];
        local_18 = FUN_7102524ce0;
        break;
    case 2:
        uVar2 = *param_1;
        uVar1 = param_1[1];
        local_18 = FUN_7102524e70;
        break;
    case 3:
        uVar2 = *param_1;
        uVar1 = param_1[1];
        local_18 = FUN_7102525000;
        break;
    case 4:
        uVar2 = *param_1;
        uVar1 = param_1[1];
        local_18 = FUN_7102525180;
        break;
    default:
        return;
    }
    FUN_7102523d70(uVar2, uVar1, &local_18);
}

// 0x7102a65b80
u64 FUN_7102a65b80(u64 param_1)
{
    switch((s32)param_1) {
    case 2:
        return 3;
    case 0xe:
        return 0xf;
    case 0x19:
        return 0x1a;
    case 0x1b:
        return 0x1c;
    case 0x26:
        return 0x27;
    case 0x31:
        return 0x32;
    case 0x3c:
        return 0x3d;
    case 0x45:
        return 0x46;
    case 0x47:
        param_1 = 0x48;
    }
    return param_1;
}

// 0x7102220920
u32 FUN_7102220920(s64 param_1)
{
    s64 *module;
    s64 entry;
    module = *(s64 **)(*(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0) + 0x68);
    entry = (**(s64 (**)(s64 *, s64))(*module + 0x60))(module, 2);
    *(u8 *)(entry + 0x30) = 0;
    return 0;
}

// 0x7102224040
u32 FUN_7102224040(s64 param_1)
{
    s64 *module;
    module = *(s64 **)(*(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0) + 0x68);
    module = (s64 *)(**(s64 (**)(s64 *, s64))(*module + 0x60))(module, 4);
    (**(void (**)(void))(*module + 0x48))();
    return 0;
}

// 0x7102220a40
u32 FUN_7102220a40(s64 param_1)
{
    s64 *module;
    module = *(s64 **)(*(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0) + 0x68);
    module = (s64 *)(**(s64 (**)(s64 *, s64))(*module + 0x60))(module, 2);
    (**(void (**)(void))(*module + 0x48))();
    return 0;
}

// 0x7102ff0bf0
s64 *FUN_7102ff0bf0(s64 param_1, u32 param_2, s64 *param_3, s64 *param_4)
{
    s64 lVar1;
    s64 *pentry;
    s64 *plVar3;

    pentry = (s64 *)0;
    switch(param_2) {
    case 0:
        pentry = *(s64 **)(param_1 + 0x28);
        if (pentry == (s64 *)(param_1 + 0x28)) return (s64 *)0;
        if (pentry == (s64 *)0) return (s64 *)0;
        plVar3 = *(s64 **)(param_1 + 0x30);
        lVar1 = *plVar3;
        pentry = (s64 *)plVar3[1];
        *pentry = lVar1;
        *(s64 **)(lVar1 + 8) = pentry;
        *(s64 *)(param_1 + 0x20) = *(s64 *)(param_1 + 0x20) - 1;
        break;
    case 1:
        pentry = *(s64 **)(param_1 + 0x88);
        if (pentry == (s64 *)(param_1 + 0x88)) return (s64 *)0;
        if (pentry == (s64 *)0) return (s64 *)0;
        plVar3 = *(s64 **)(param_1 + 0x90);
        lVar1 = *plVar3;
        pentry = (s64 *)plVar3[1];
        *pentry = lVar1;
        *(s64 **)(lVar1 + 8) = pentry;
        *(s64 *)(param_1 + 0x80) = *(s64 *)(param_1 + 0x80) - 1;
        break;
    case 2:
        pentry = *(s64 **)(param_1 + 0xe8);
        if (pentry == (s64 *)(param_1 + 0xe8)) return (s64 *)0;
        if (pentry == (s64 *)0) return (s64 *)0;
        plVar3 = *(s64 **)(param_1 + 0xf0);
        lVar1 = *plVar3;
        pentry = (s64 *)plVar3[1];
        *pentry = lVar1;
        *(s64 **)(lVar1 + 8) = pentry;
        *(s64 *)(param_1 + 0xe0) = *(s64 *)(param_1 + 0xe0) - 1;
        break;
    case 3:
        if (*(s64 *)(param_1 + 0x148) == param_1 + 0x148) return (s64 *)0;
        if (*(s64 *)(param_1 + 0x148) == 0) return (s64 *)0;
        plVar3 = *(s64 **)(param_1 + 0x150);
        lVar1 = *plVar3;
        pentry = (s64 *)plVar3[1];
        *pentry = lVar1;
        *(s64 **)(lVar1 + 8) = pentry;
        *(s64 *)(param_1 + 0x140) = *(s64 *)(param_1 + 0x140) - 1;
        break;
    default:
        return pentry;
    case 5:
        if (*(s64 *)(param_1 + 0x208) == param_1 + 0x208) return (s64 *)0;
        if (*(s64 *)(param_1 + 0x208) == 0) return (s64 *)0;
        plVar3 = *(s64 **)(param_1 + 0x210);
        lVar1 = *plVar3;
        pentry = (s64 *)plVar3[1];
        *pentry = lVar1;
        *(s64 **)(lVar1 + 8) = pentry;
        *(s64 *)(param_1 + 0x200) = *(s64 *)(param_1 + 0x200) - 1;
        break;
    case 6:
        if (*(s64 *)(param_1 + 0x1a8) == param_1 + 0x1a8) return (s64 *)0;
        if (*(s64 *)(param_1 + 0x1a8) == 0) return (s64 *)0;
        plVar3 = *(s64 **)(param_1 + 0x1b0);
        lVar1 = *plVar3;
        pentry = (s64 *)plVar3[1];
        *pentry = lVar1;
        *(s64 **)(lVar1 + 8) = pentry;
        *(s64 *)(param_1 + 0x1a0) = *(s64 *)(param_1 + 0x1a0) - 1;
        break;
    case 7:
        if (*(s64 *)(param_1 + 0x268) == param_1 + 0x268) return (s64 *)0;
        if (*(s64 *)(param_1 + 0x268) == 0) return (s64 *)0;
        plVar3 = *(s64 **)(param_1 + 0x270);
        lVar1 = *plVar3;
        pentry = (s64 *)plVar3[1];
        *pentry = lVar1;
        *(s64 **)(lVar1 + 8) = pentry;
        *(s64 *)(param_1 + 0x260) = *(s64 *)(param_1 + 0x260) - 1;
    }
    *plVar3 = 0;
    plVar3[1] = 0;
    plVar3[6] = param_4[1];
    lVar1 = *param_4;
    *(u8 *)((s64)plVar3 + 0x41) = 1;
    plVar3[5] = lVar1;
    plVar3[7] = *param_3;
    *(u8 *)((s64)plVar3 + 0x41) = 1;
    pentry = plVar3 - 1;
    (**(void (**)(s64 *))(*pentry + 0x40))(pentry);
    *(u8 *)((s64)plVar3 + 0x41) = 0;
    (**(void (**)(s64 *))(*pentry + 0x48))(pentry);
    *(u8 *)((s64)plVar3 + 8) = 1;
    return pentry;
}
