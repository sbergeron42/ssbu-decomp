#include "types.h"

// HARD-tier FUN_* functions — 0x71020a-0x71021a address range, batch hard-c-008

extern "C" {
    __attribute__((noreturn)) void FUN_71039c20a0(void);
}

#define DAT_HIDDEN __attribute__((visibility("hidden")))

extern "C" DAT_HIDDEN u64 DAT_71053299d8;   // lib::Singleton<StageManager>::instance_
extern "C" DAT_HIDDEN u64 DAT_7104861960;   // Lua stack sentinel

// 0x7102145710 — StageManager singleton: query game state, push bool result
u32 FUN_7102145710(u64 param_1)
{
#ifdef MATCHING_HACK_NX_CLANG
    asm volatile("" :: "r"(__builtin_frame_address(0)) : "memory");
#endif
    u64 instance = DAT_71053299d8;
    if (instance == 0)
        return 0;
    u64 vtable = *(u64 *)instance;
    u32 uVar1 = *(u32 *)(vtable + 0x17c);
    if (uVar1 == 0xffffffffu) {
        uVar1 = 1;
    } else {
        if (uVar1 >= 3)
            FUN_71039c20a0();
        u64 sub = *(u64 *)(vtable + (u64)uVar1 * 8 + 0x110);
        u64 fn = *(u64 *)(*(u64 *)sub + 0x4a0);
        uVar1 = ((u32 (*)(u64))fn)(sub) & 1;
    }
    u64 stack_top = *(u64 *)(param_1 + 0x10);
    *(u32 *)stack_top = uVar1;
    *(u32 *)(stack_top + 8) = 1;
    *(u64 *)(param_1 + 0x10) = *(u64 *)(param_1 + 0x10) + 0x10;
    return 1;
}

// 0x71020ad890 — Lua binding: HTTP status check, push bool (is-available)
u32 FUN_71020ad890(u64 param_1)
{
#ifdef MATCHING_HACK_NX_CLANG
    asm volatile("" :: "r"(__builtin_frame_address(0)) : "memory");
#endif
    u64 closure = *(u64 *)(param_1 - 8);
    if (closure == 0)
        return 0;
    u64 *plVar8 = *(u64 **)(closure + 0x78);
    if (plVar8 == nullptr)
        return 0;

    u64 *plVar5 = *(u64 **)(param_1 + 0x10);
    u64 *plVar1 = (u64 *)(**(u64 **)(param_1 + 0x20) + 0x10);

    if (0 < (s32)((u64)((s64)plVar5 - (s64)plVar1) >> 4)) {
        plVar8 = (plVar1 < plVar5) ? plVar1 : (u64 *)&DAT_7104861960;
        s64 lVar7;
        u32 type_bits = *(u32 *)(plVar8 + 1) & 0xf;
        if (type_bits == 2)
            lVar7 = (s64)*plVar8;
        else if (type_bits == 7)
            lVar7 = (s64)*plVar8 + 0x28;
        else
            lVar7 = 0;
        plVar8 = *(u64 **)(lVar7 + 0x90);
        *(u64 *)(param_1 + 0x10) = (u64)((s64)plVar5 + (((s64)plVar5 - (s64)plVar1) * -(s64)0x10000000 >> 0x1c));
    }

    u64 inner1 = *(u64 *)(plVar8[1] + 0x40);
    s32 iVar2 = ((s32 (*)(u64))*(u64 *)(*(u64 *)inner1 + 0x110))(inner1);

    u32 uVar3;
    if (iVar2 < 200) {
        if ((4 < (u32)((u32)iVar2 - 0x47u)) ||
            (((u64 (*)(u64, u32))*(u64 *)(*(u64 *)*(u64 *)(plVar8[1] + 0x50) + 0x108))(*(u64 *)(plVar8[1] + 0x50), (u32)0x2100000f) & 1) == 0) {
            uVar3 = ((u32 (*)(u64 *))*(u64 *)(*(u64 *)plVar8 + 0xa0))(plVar8);
            goto LAB_ad9c0;
        }
    } else if ((iVar2 != 200) && (iVar2 != 0x149) && (iVar2 != 0x14c)) {
        uVar3 = ((u32 (*)(u64 *))*(u64 *)(*(u64 *)plVar8 + 0xa0))(plVar8);
        goto LAB_ad9c0;
    }

    iVar2 = ((s32 (*)(u64, u32))*(u64 *)(*(u64 *)*(u64 *)(plVar8[1] + 0x50) + 0x98))(*(u64 *)(plVar8[1] + 0x50), (u32)0x11000006);
    uVar3 = (u32)(0 < iVar2);

LAB_ad9c0:
    u32 *puVar6 = *(u32 **)(param_1 + 0x10);
    *puVar6 = uVar3 & 1;
    puVar6[2] = 1;
    *(u64 *)(param_1 + 0x10) = *(u64 *)(param_1 + 0x10) + 0x10;
    return 1;
}

// 0x71020ad9f0 — Lua binding: HTTP status check, push signed int result
u32 FUN_71020ad9f0(u64 param_1)
{
#ifdef MATCHING_HACK_NX_CLANG
    asm volatile("" :: "r"(__builtin_frame_address(0)) : "memory");
#endif
    u64 closure = *(u64 *)(param_1 - 8);
    if (closure == 0)
        return 0;
    u64 *plVar6 = *(u64 **)(closure + 0x78);
    if (plVar6 == nullptr)
        return 0;

    u64 *plVar4 = *(u64 **)(param_1 + 0x10);
    u64 *plVar1 = (u64 *)(**(u64 **)(param_1 + 0x20) + 0x10);

    if (0 < (s32)((u64)((s64)plVar4 - (s64)plVar1) >> 4)) {
        plVar6 = (plVar1 < plVar4) ? plVar1 : (u64 *)&DAT_7104861960;
        s64 lVar5;
        u32 type_bits = *(u32 *)(plVar6 + 1) & 0xf;
        if (type_bits == 2)
            lVar5 = (s64)*plVar6;
        else if (type_bits == 7)
            lVar5 = (s64)*plVar6 + 0x28;
        else
            lVar5 = 0;
        plVar6 = *(u64 **)(lVar5 + 0x90);
        *(u64 *)(param_1 + 0x10) = (u64)((s64)plVar4 + (((s64)plVar4 - (s64)plVar1) * -(s64)0x10000000 >> 0x1c));
    }

    u64 inner1 = *(u64 *)(plVar6[1] + 0x40);
    s32 iVar2 = ((s32 (*)(u64))*(u64 *)(*(u64 *)inner1 + 0x110))(inner1);

    if (iVar2 < 200) {
        if ((4 < (u32)((u32)iVar2 - 0x47u)) ||
            (((u64 (*)(u64, u32))*(u64 *)(*(u64 *)*(u64 *)(plVar6[1] + 0x50) + 0x108))(*(u64 *)(plVar6[1] + 0x50), (u32)0x2100000f) & 1) == 0) {
            iVar2 = ((s32 (*)(u64 *))*(u64 *)(*(u64 *)plVar6 + 0xc8))(plVar6);
            goto LAB_adb18;
        }
    } else if ((iVar2 != 200) && (iVar2 != 0x149) && (iVar2 != 0x14c)) {
        iVar2 = ((s32 (*)(u64 *))*(u64 *)(*(u64 *)plVar6 + 0xc8))(plVar6);
        goto LAB_adb18;
    }

    iVar2 = ((s32 (*)(u64, u32))*(u64 *)(*(u64 *)*(u64 *)(plVar6[1] + 0x50) + 0x98))(*(u64 *)(plVar6[1] + 0x50), (u32)0x11000006);

LAB_adb18:
    u64 *plVar6b = *(u64 **)(param_1 + 0x10);
    *plVar6b = (u64)(s64)iVar2;
    *(u32 *)(plVar6b + 1) = 0x13;
    *(u64 *)(param_1 + 0x10) = *(u64 *)(param_1 + 0x10) + 0x10;
    return 1;
}

// 0x71020af340 — Lua binding: read float property from actor, push float
u32 FUN_71020af340(u64 param_1)
{
#ifdef MATCHING_HACK_NX_CLANG
    asm volatile("" :: "r"(__builtin_frame_address(0)) : "memory");
#endif
    u64 closure = *(u64 *)(param_1 - 8);
    if (closure == 0)
        return 0;
    u64 lVar9 = *(u64 *)(closure + 0x30);
    if (lVar9 == 0)
        return 0;

    u64 *plVar7 = *(u64 **)(param_1 + 0x10);
    u64 *plVar1 = (u64 *)(**(u64 **)(param_1 + 0x20) + 0x10);

    if ((s32)((u64)((s64)plVar7 - (s64)plVar1) >> 4) >= 1) {
        u64 *plVar2 = (plVar1 < plVar7) ? plVar1 : (u64 *)&DAT_7104861960;
        s64 lVar9b;
        u32 type_bits = *(u32 *)(plVar2 + 1) & 0xf;
        if (type_bits == 2)
            lVar9b = (s64)*plVar2;
        else if (type_bits == 7)
            lVar9b = (s64)*plVar2 + 0x28;
        else
            lVar9b = 0;
        lVar9 = *(u64 *)(lVar9b + 0x48);
        *(u64 *)(param_1 + 0x10) = (u64)((s64)plVar7 + (((s64)plVar7 - (s64)plVar1) * -(s64)0x10000000 >> 0x1c));
    }

    u64 inner2 = *(u64 *)(lVar9 + 0x118);
    s32 raw5 = ((s32 (*)(u64))*(u64 *)(*(u64 *)inner2 + 0x98))(inner2);
    u32 cVar5 = (u32)raw5 & 0xff;

    s64 lVar3 = 0xc10;
    if (cVar5 != 2u)
        lVar3 = 0x2b8;
    s64 lVar4 = 0xc14;
    if (raw5 & 0xff)
        lVar4 = lVar3;

    s32 iVar10 = *(s32 *)(*(u64 *)(lVar9 + 0x140) + lVar4);
    u64 *pfVar8 = *(u64 **)(param_1 + 0x10);
    *(u32 *)((u64)pfVar8 + 8) = 3;
    *(float *)pfVar8 = (float)iVar10;
    *(u64 *)(param_1 + 0x10) = *(u64 *)(param_1 + 0x10) + 0x10;
    return 1;
}

// 0x7102149a50 — Lua binding: normalize stack to 1 arg, push network session id
u32 FUN_7102149a50(u64 param_1)
{
    u64 *plVar3 = *(u64 **)(param_1 + 0x10);
    u64 *plVar5 = (u64 *)(**(u64 **)(param_1 + 0x20) + 0x10);
    u64 *plVar1 = (plVar3 <= plVar5) ? (u64 *)&DAT_7104861960 : plVar5;

    u64 uVar6 = (u64)((s64)plVar3 - (s64)plVar5);

    s64 lVar4;
    u32 type_bits = *(u32 *)(plVar1 + 1) & 0xf;
    if (type_bits == 2)
        lVar4 = (s64)*plVar1;
    else if (type_bits == 7)
        lVar4 = (s64)*plVar1 + 0x28;
    else
        lVar4 = 0;

    if ((s32)((s32)(uVar6 >> 4)) < 0) {
        plVar5 = (u64 *)((s64)plVar5 + ((s64)((s64)(uVar6 * 0x10000000) ^ (s64)0xffffffff00000000LL) >> 0x1c));
        while (plVar3 < plVar5) {
            *(u64 **)(param_1 + 0x10) = plVar3 + 2;
            *(u32 *)(plVar3 + 1) = 0;
            plVar3 = *(u64 **)(param_1 + 0x10);
        }
    } else {
        plVar5 = (u64 *)((s64)plVar3 + ((s64)(uVar6 * -(u64)0x10000000) >> 0x1c));
    }
    *(u64 **)(param_1 + 0x10) = plVar5;

    u64 inner3 = *(u64 *)(lVar4 + 0x50);
    u64 has_session = ((u64 (*)(u64, u32))*(u64 *)(*(u64 *)inner3 + 0x108))(inner3, (u32)0x20000102);

    if ((has_session & 1) == 0) {
        lVar4 = -1;
    } else {
        s32 iVar2 = ((s32 (*)(u64, u32))*(u64 *)(*(u64 *)inner3 + 0x98))(inner3, (u32)0x100000fc);
        lVar4 = (s64)iVar2;
    }

    u64 *plVar5b = *(u64 **)(param_1 + 0x10);
    *plVar5b = (u64)lVar4;
    *(u32 *)(plVar5b + 1) = 0x13;
    *(u64 *)(param_1 + 0x10) = *(u64 *)(param_1 + 0x10) + 0x10;
    return 1;
}
