#include "types.h"

// EASY-tier batch 004 — pool-a worker

// External globals
extern u32 DAT_7104545610[];
extern u64 DAT_7105328fa0;
extern u64 PTR_DAT_71052a5818;
extern u64 PTR_DAT_71052a5820;
extern u64 PTR_DAT_71052a3df0;

// External function declarations
extern void FUN_71039c1490(s64);   // std::__1::recursive_mutex::lock
extern void FUN_71039c14a0(s64);   // std::__1::recursive_mutex::unlock
extern void FUN_71039c1410(s64);   // std::__1::mutex::lock
extern void FUN_71039c1420(s64);   // std::__1::mutex::unlock
extern void FUN_7102413ed0(s64, s64);
extern void FUN_7102416c00(void);
extern void FUN_7103559220(s64);
extern void FUN_71000b40e0(s64);
extern void FUN_71000b4160(s64);
extern u64  FUN_7100192590(u64);
extern void FUN_7100127af0(s64);
extern s64 *FUN_71000bb680(void);
extern void FUN_71000bb5d0(s64 *);
extern void FUN_71025e9900(s64);
extern void FUN_710260f980(s64, u64, s64);
extern void FUN_710313e970(u64);
extern "C" void *malloc(unsigned long);

// ── 128-byte functions ───────────────────────────────────────────────────────

// 0x71001ae5e0
void FUN_71001ae5e0(s64 param_1, s8 param_2, u8 param_3)
{
    s64 lVar1 = *(s64 *)(param_1 + 8);
    while (true) {
        if (lVar1 == param_1) {
            return;
        }
        if (*(s8 *)(lVar1 + 0x18) == param_2) break;
        lVar1 = *(s64 *)(lVar1 + 8);
    }
    *(u8 *)(lVar1 + 0x28) = param_3 & 1;
}

// ── 160-byte functions ───────────────────────────────────────────────────────

// 0x7100127a50
u64 FUN_7100127a50(s64 param_1)
{
    s64 local_28;
    if (*(s32 *)(param_1 + 0x12a0) == 1) {
        return 0;
    }
    FUN_71000b40e0(param_1 + 0x12a0);
    FUN_71000b4160(param_1 + 0x12a0);
    u64 uVar1 = FUN_7100192590(*(u64 *)PTR_DAT_71052a3df0);
    if ((uVar1 & 1) == 0) {
        FUN_7100127af0(param_1);
    }
    s64 *plVar2 = FUN_71000bb680();
    s64 lVar3 = *plVar2;
    local_28 = 0;
    FUN_71000bb5d0(&local_28);
    *(s64 *)(param_1 + 0x12d0) = local_28 + lVar3 * 2000;
    return 1;
}

// ── 176-byte functions ───────────────────────────────────────────────────────

// 0x71023ee4b0
void FUN_71023ee4b0(f32 param_1, s64 param_2)
{
    if (*(u8 *)(param_2 + 0x20) != 0) {
        return;
    }
    FUN_71039c1490(param_2);
    s64 lVar1 = *(s64 *)(param_2 + 0x28);
    *(f32 *)(lVar1 + 200) = param_1;
    if ((*(s32 *)(lVar1 + 0x18) == 6) && (*(s64 *)(lVar1 + 0x28) != 0)) {
        s64 *plVar3 = *(s64 **)(lVar1 + 0x20);
        s64 lVar2 = *(s64 *)(lVar1 + 0x28) << 5;
        do {
            s64 lVar4 = *plVar3;
            if (lVar4 != 0) {
                FUN_71039c1410(lVar4 + 0x48);
                *(f32 *)(lVar4 + 0x6c) = param_1;
                *(u8 *)(lVar4 + 0x68) = 1;
                FUN_7102413ed0(lVar4, 0);
                FUN_71039c1420(lVar4 + 0x48);
            }
            plVar3 = plVar3 + 4;
            lVar2 = lVar2 - 0x20;
        } while (lVar2 != 0);
    }
    FUN_71039c14a0(param_2);
}

// 0x71023ee560
void FUN_71023ee560(f32 param_1, s64 param_2)
{
    if (*(u8 *)(param_2 + 0x20) != 0) {
        return;
    }
    FUN_71039c1490(param_2);
    s64 lVar1 = *(s64 *)(param_2 + 0x28);
    *(f32 *)(lVar1 + 0xcc) = param_1;
    if ((*(s32 *)(lVar1 + 0x18) == 6) && (*(s64 *)(lVar1 + 0x28) != 0)) {
        s64 *plVar3 = *(s64 **)(lVar1 + 0x20);
        s64 lVar2 = *(s64 *)(lVar1 + 0x28) << 5;
        do {
            s64 lVar4 = *plVar3;
            if (lVar4 != 0) {
                FUN_71039c1410(lVar4 + 0x48);
                *(f32 *)(lVar4 + 0x74) = param_1;
                *(u8 *)(lVar4 + 0x70) = 1;
                FUN_7102413ed0(lVar4, 0);
                FUN_71039c1420(lVar4 + 0x48);
            }
            plVar3 = plVar3 + 4;
            lVar2 = lVar2 - 0x20;
        } while (lVar2 != 0);
    }
    FUN_71039c14a0(param_2);
}

// ── 192-byte functions ───────────────────────────────────────────────────────

// 0x71025ed7f0
void FUN_71025ed7f0(s64 param_1)
{
    s64 lVar1;
    u64 *puVar2;
    s64 lVar3;
    u8 *pcVar4;

    if (*(u8 *)(param_1 + 0x81) != 0) {
        return;
    }
    FUN_7103559220(param_1 + 0x30);
    lVar1 = *(s64 *)(param_1 + 0x58);
    if (*(u8 *)(lVar1 + 0x31) == 0) {
        *(u8 *)(lVar1 + 0x31) = 1;
        if (*(s64 *)(lVar1 + 0x40) != 0) {
            puVar2 = *(u64 **)(lVar1 + 0x38);
            lVar3 = *(s64 *)(lVar1 + 0x40) << 4;
            do {
                if ((*(u8 *)(lVar1 + 0x30) == 0) || (*(u8 *)(lVar1 + 0x31) == 0) ||
                    (*(u8 *)(lVar1 + 0x32) != 0)) {
                    if (((u64 *)*puVar2 != nullptr) &&
                        (pcVar4 = *(u8 **)*puVar2, *pcVar4 != 0)) {
                        *pcVar4 = 0;
                    }
                } else if (((u64 *)*puVar2 != nullptr) &&
                           (pcVar4 = *(u8 **)*puVar2, *pcVar4 == 0)) {
                    *pcVar4 = 1;
                }
                puVar2 = puVar2 + 2;
                lVar3 = lVar3 - 0x10;
            } while (lVar3 != 0);
        }
    }
    *(u8 *)(param_1 + 0x81) = 1;
}

// ── 224-byte functions ───────────────────────────────────────────────────────

// 0x71001b2280
u64 *FUN_71001b2280(s64 param_1, s64 param_2)
{
    u64 *puVar1;
    if (*(u64 *)(param_1 + 0x20) != 0) {
        puVar1 = (u64 *)((u64 (*)(s64))(*(u64 *)(param_1 + 0x20)))(param_2);
        return puVar1;
    }
    if (*(u64 *)PTR_DAT_71052a5818 == 0) {
        puVar1 = (u64 *)malloc(((u64)param_2 + 0x17U) & ~7ULL);
    } else {
        puVar1 = (u64 *)((u64 (*)())(*(u64 *)PTR_DAT_71052a5818))();
    }
    *puVar1 = *(u64 *)PTR_DAT_71052a5820;
    return puVar1 + 2;
}

// 0x71023ed810
void FUN_71023ed810(s64 param_1)
{
    u32 uVar1;
    u8 cVar2;
    s64 lVar3;

    if (*(u8 *)(param_1 + 0x20) != 0) {
        return;
    }
    FUN_71039c1490(param_1);
    lVar3 = *(s64 *)(param_1 + 0x28);
    uVar1 = *(u32 *)(lVar3 + 0x10);
    if (uVar1 - 8 < 4) {
        if ((0xbU >> (u64)(uVar1 - 8 & 0xf) & 1) != 0) goto LAB_71023ed8e0;
LAB_71023ed868:
        if (((0x18bU >> (u64)(uVar1 - 3 & 0x1f) & 1) == 0) && ((uVar1 | 2) != 7)) goto LAB_71023ed8e0;
LAB_71023ed884:
        if ((0x307U >> (u64)(uVar1 - 3 & 0x1f) & 1) == 0) goto LAB_71023ed8c4;
        *(u32 *)(lVar3 + 0x10) = DAT_7104545610[(s32)(uVar1 - 3)];
        cVar2 = *(u8 *)(lVar3 + 0x100);
    } else {
        if (uVar1 - 3 < 9) goto LAB_71023ed868;
        if ((uVar1 | 2) != 7) goto LAB_71023ed8e0;
        if (uVar1 - 3 < 10) goto LAB_71023ed884;
LAB_71023ed8c4:
        cVar2 = *(u8 *)(lVar3 + 0x100);
    }
    if (cVar2 != 0) {
        *(u8 *)(lVar3 + 0x100) = 0;
    }
    if (*(u8 *)(lVar3 + 0x198) != 0) {
        *(u8 *)(lVar3 + 0x198) = 0;
    }
    FUN_7102416c00();
LAB_71023ed8e0:
    FUN_71039c14a0(param_1);
}

// 0x710251abb0
s32 FUN_710251abb0(s64 param_1, u8 param_2)
{
    u64 uVar1, uVar2, uVar3;
    s32 iVar4, iVar5;
    s64 lVar6;
    f32 fVar7;

    if (param_2 > 2) {
        return 0;
    }
    s64 lVar6_obj = *(s64 *)(param_1 + (u64)param_2 * 8 + 0x78);
    if (lVar6_obj == 0 || *(u8 *)(param_1 + 0x388) == 0) {
        return 0;
    }
    uVar2 = *(u64 *)(lVar6_obj + 8);
    uVar3 = *(u64 *)(lVar6_obj + 0x10);
    uVar1 = ((s64)uVar3 >> 0x20) * 0x68fd3d1dULL +
            (((uVar3 & 0xffffffff) * 0x68fd3d1dULL) >> 0x20);
    lVar6 = (s64)*(s32 *)(*(s64 *)DAT_7105328fa0 + 0x848);
    iVar4 = 0;
    if (lVar6 != 0) {
        iVar4 = (s32)(((s64)((((s64)uVar3 >> 0x20) * 0x12533feLL + ((s64)uVar1 >> 0x20) +
                               ((uVar3 & 0xffffffff) * 0x12533feLL +
                                (uVar1 & 0xffffffff)) >> 0x20) >> 0x1c)
                        - ((s64)uVar3 >> 0x3f)) / lVar6);
    }
    uVar1 = ((s64)uVar2 >> 0x20) * 0x68fd3d1dULL +
            (((uVar2 & 0xffffffff) * 0x68fd3d1dULL) >> 0x20);
    iVar5 = 0;
    if (lVar6 != 0) {
        iVar5 = (s32)(((s64)((((s64)uVar2 >> 0x20) * 0x12533feLL + ((s64)uVar1 >> 0x20) +
                               ((uVar2 & 0xffffffff) * 0x12533feLL +
                                (uVar1 & 0xffffffff)) >> 0x20) >> 0x1c)
                        - ((s64)uVar2 >> 0x3f)) / lVar6);
    }
    fVar7 = *(f32 *)(lVar6_obj + 0x228);
    return (s32)(((f32)iVar4 / (f32)iVar5) * fVar7);
}

// ── 240-byte functions ───────────────────────────────────────────────────────

// 0x71027fe830
void FUN_71027fe830(s64 param_1)
{
    s64 lVar1;
    s64 lVar2;

    if (*(u8 *)(param_1 + 0x50) != 0) {
        return;
    }
    lVar2 = *(s64 *)(param_1 + 0x10);
    if (lVar2 != 0) {
        *(u8 *)(lVar2 + 0x110) = 1;
        FUN_71025e9900(lVar2 + 0x108);
        FUN_710260f980(0, *(u64 *)(param_1 + 0x10), 1);
        lVar2 = *(s64 *)(param_1 + 0x10);
        if (lVar2 != 0) {
            if ((*(u8 *)(lVar2 + 0xe0) != 0) && (*(s64 *)(lVar2 + 200) != 0)) {
                *(u16 *)(*(s64 *)(lVar2 + 200) + 0x30) = 0;
            }
            if (*(s64 *)(lVar2 + 0xd8) != 0) {
                *(u8 *)(*(s64 *)(lVar2 + 0xd8) + 0x21) = 0;
            }
            if (*(u8 *)(lVar2 + 0xe0) != 0) {
                *(u8 *)(*(s64 *)(lVar2 + 0xb0) + 0x10) = 1;
            }
            lVar2 = *(s64 *)(param_1 + 0x10);
            if (lVar2 != 0) {
                if ((*(u8 *)(lVar2 + 0xe0) != 0) && (*(s64 *)(lVar2 + 200) != 0)) {
                    *(u16 *)(*(s64 *)(lVar2 + 200) + 0x32) = 0;
                }
                if (*(s64 *)(lVar2 + 0xd8) != 0) {
                    *(u8 *)(*(s64 *)(lVar2 + 0xd8) + 0x22) = 0;
                }
            }
        }
    }
    lVar2 = *(s64 *)(param_1 + 0x80);
    lVar1 = *(s64 *)(param_1 + 0x88);
    *(u8 *)(param_1 + 0x58) = 0;
    *(u64 *)(param_1 + 0x60) = 0;
    for (; lVar2 != lVar1; lVar2 = lVar2 + 0x70) {
        if (*(u8 *)(lVar2 + 0x20) != 0) {
            *(u8 *)(lVar2 + 0x20) = 0;
        }
    }
    FUN_710313e970(*(u64 *)(param_1 + 0x20));
    *(u8 *)(param_1 + 0x50) = 1;
}

// ── 256-byte functions ───────────────────────────────────────────────────────

// 0x71015357e0
void FUN_71015357e0(s64 param_1)
{
    s64 *obj = *(s64 **)(param_1 + 8);
    (*(void (**)())(*obj + 0x10))();
}

// 0x71002fa670
s64 FUN_71002fa670(s64 param_1, u32 param_2)
{
    if (param_2 < 10) {
        if (*(s16 *)(param_1 + 0xc) != 0) {
            if (param_2 == 0) return param_1;
            param_2 = param_2 - 1;
        }
        if (*(s16 *)(param_1 + 0x5c) != 0) {
            if (param_2 == 0) return param_1 + 0x50;
            param_2 = param_2 - 1;
        }
        if (*(s16 *)(param_1 + 0xac) != 0) {
            if (param_2 == 0) return param_1 + 0xa0;
            param_2 = param_2 - 1;
        }
        if (*(s16 *)(param_1 + 0xfc) != 0) {
            if (param_2 == 0) return param_1 + 0xf0;
            param_2 = param_2 - 1;
        }
        if (*(s16 *)(param_1 + 0x14c) != 0) {
            if (param_2 == 0) return param_1 + 0x140;
            param_2 = param_2 - 1;
        }
        if (*(s16 *)(param_1 + 0x19c) != 0) {
            if (param_2 == 0) return param_1 + 400;
            param_2 = param_2 - 1;
        }
        if (*(s16 *)(param_1 + 0x1ec) != 0) {
            if (param_2 == 0) return param_1 + 0x1e0;
            param_2 = param_2 - 1;
        }
        if (*(s16 *)(param_1 + 0x23c) != 0) {
            if (param_2 == 0) return param_1 + 0x230;
            param_2 = param_2 - 1;
        }
        if (*(s16 *)(param_1 + 0x28c) != 0) {
            if (param_2 == 0) return param_1 + 0x280;
            param_2 = param_2 - 1;
        }
        if ((*(s16 *)(param_1 + 0x2dc) != 0) && (param_2 == 0)) {
            return param_1 + 0x2d0;
        }
    }
    return 0;
}

// ── 288-byte functions ───────────────────────────────────────────────────────

// 0x7100145da0
void FUN_7100145da0(s64 param_1)
{
    u8 idx = *(u8 *)(param_1 + 0x162);
    s64 *obj = *(s64 **)(param_1 + (u64)idx * 8 + 0x168);
    (*(void (**)())(*obj + 0x38))();
}
