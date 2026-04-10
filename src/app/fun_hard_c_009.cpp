#include "types.h"

// HARD-tier FUN_* functions — 0x7102 address range, batch hard-c-009

extern "C" {
    __attribute__((noreturn)) void abortWrapper_71039c20a0(void);
}

#define DAT_HIDDEN __attribute__((visibility("hidden")))

extern "C" DAT_HIDDEN u64 DAT_7104861960;   // Lua stack sentinel
extern "C" DAT_HIDDEN u64 DAT_71052b84f8;   // lib::Singleton<app::FighterManager>::instance_

// 0x71021afc20 — Lua binding: normalize stack to 1 arg, get FighterManager entry index
u32 FUN_71021afc20(u64 param_1)
{
#ifdef MATCHING_HACK_NX_CLANG
    asm volatile("" :: "r"(__builtin_frame_address(0)) : "memory");
#endif
    u64 *plVar4 = *(u64 **)(param_1 + 0x10);
    u64 *plVar3 = (u64 *)(**(u64 **)(param_1 + 0x20) + 0x10);
    u64 *plVar1 = plVar3;
    if (plVar4 <= plVar3) {
        plVar1 = (u64 *)&DAT_7104861960;
    }
    u64 uVar6 = (u64)((s64)plVar4 - (s64)plVar3);

    s64 lVar5;
    u32 type_bits = *(u32 *)(plVar1 + 1) & 0xf;
    if (type_bits == 2)
        lVar5 = (s64)*plVar1;
    else if (type_bits == 7)
        lVar5 = (s64)*plVar1 + 0x28;
    else
        lVar5 = 0;

    if ((s32)(uVar6 >> 4) < 0) {
        plVar3 = (u64 *)((s64)plVar3 + ((s64)(uVar6 * (u64)0x10000000 ^ (u64)0xffffffff00000000LL) >> 0x1c));
        while (plVar4 < plVar3) {
            *(u64 **)(param_1 + 0x10) = plVar4 + 2;
            *(u32 *)(plVar4 + 1) = 0;
            plVar4 = *(u64 **)(param_1 + 0x10);
        }
    } else {
        plVar3 = (u64 *)((s64)plVar4 + ((s64)(uVar6 * -(u64)0x10000000) >> 0x1c));
    }
    *(u64 **)(param_1 + 0x10) = plVar3;

    u64 fmgr = DAT_71052b84f8;
    u64 fmgr_data = *(u64 *)fmgr;
    s64 lVar8;
    if ((*(u8 *)(fmgr_data + 0xc1) == 1) || (*(u8 *)(fmgr_data + 0xc3) != 0)) {
        u64 *work = *(u64 **)(*(u64 *)(lVar5 + 0x20) + 0x50);
        u32 idx = ((u32 (*)(u64 *, u32))*(u64 *)(*(u64 *)work + 0x98))(work, 0x1000000au);
        if (idx >= 8u)
            abortWrapper_71039c20a0();
        fmgr_data = *(u64 *)fmgr;
        lVar8 = (s64)*(s32 *)(*(u64 *)(*(u64 *)(fmgr_data + (s64)(s32)idx * 8 + 0x20) + 0xf8) + 0xd8);
        plVar3 = *(u64 **)(param_1 + 0x10);
    } else {
        lVar8 = -1;
    }

    *plVar3 = (u64)lVar8;
    *(u32 *)(plVar3 + 1) = 0x13;
    *(u64 *)(param_1 + 0x10) = *(u64 *)(param_1 + 0x10) + 0x10;
    return 1;
}
