// fun_hard_c_008.cpp — Matched Lua binding functions from 0x71020a–0x71021a range
// Cleaned: removed 3 unmatched Ghidra paste functions, kept 2 verified (M)

#include "types.h"

extern "C" {
    __attribute__((noreturn)) void abortWrapper_71039c20a0(void);
}

#define DAT_HIDDEN __attribute__((visibility("hidden")))

extern "C" DAT_HIDDEN u64 DAT_71053299d8;   // lib::Singleton<StageManager>::instance_

// 0x7102145710 — StageManager singleton: query game state, push bool result (quality=M)
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
            abortWrapper_71039c20a0();
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

extern "C" DAT_HIDDEN u64 DAT_7104861960;   // Lua stack sentinel

// 0x71020ad9f0 — Lua binding: HTTP status check, push signed int result (quality=M)
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
