#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7100 address range, batch d3-012
// Pool-d worker: auto-generated from Ghidra decompilation

// ---- External declarations -----------------------------------------------

extern "C" void *memset(void *, int, u64);

// Forward declaration (defined later in this file)
void FUN_7100060e80(u16 *param_1);

// ---- Functions ---------------------------------------------------------------

// 0x7100022bf0 — flag-to-canonical-alignment mapper: large if-else over power-of-two flags (256 bytes)
u64 FUN_7100022bf0(u64 param_1)
{
    s32 iVar1;
    iVar1 = (s32)param_1;
    if (iVar1 < 0x4000) {
        if (iVar1 < 0x80) {
            switch (iVar1) {
            case 1:
            case 2:
                return 1;
            case 4:
            case 8:
                return 4;
            case 0x10:
            case 0x20:
            case 0x40:
                return param_1;
            }
        } else if (iVar1 < 0x400) {
            if ((iVar1 == 0x80) || (iVar1 == 0x100)) {
                return 0x80;
            }
            if (iVar1 == 0x200) {
                return param_1 & 0xffffffff;
            }
        } else if (iVar1 < 0x1000) {
            if (iVar1 == 0x400) {
                return param_1;
            }
            if (iVar1 == 0x800) {
                return param_1 & 0xffffffff;
            }
        } else if ((iVar1 == 0x1000) || (iVar1 == 0x2000)) {
            return 0x1000;
        }
    } else if (iVar1 < 0x200000) {
        if (iVar1 < 0x20000) {
            if ((iVar1 == 0x4000) || (iVar1 == 0x8000)) {
                return 0x4000;
            }
            if (iVar1 == 0x10000) {
                return 0x10000;
            }
        } else if (iVar1 < 0x80000) {
            if (iVar1 == 0x20000) {
                return 0x10000;
            }
            if (iVar1 == 0x40000) {
                return param_1 & 0xffffffff;
            }
        } else {
            if (iVar1 == 0x80000) {
                return 0x80000;
            }
            if (iVar1 == 0x100000) {
                return 0x100000;
            }
        }
    } else if (iVar1 < 0x1000000) {
        if (iVar1 == 0x200000) {
            return param_1;
        }
        if (iVar1 == 0x400000) {
            return param_1;
        }
        if (iVar1 == 0x800000) {
            return 0x80000;
        }
    } else if (iVar1 < 0x4000000) {
        if (iVar1 == 0x1000000) {
            return 0x100000;
        }
        if (iVar1 == 0x2000000) {
            return param_1 & 0xffffffff;
        }
    } else if ((iVar1 == 0x4000000) || (iVar1 == 0x8000000)) {
        return 0x4000000;
    }
    return 0;
}

// 0x7100055470 — conditional offset: deref chain +200+0x38, add field if non-zero (32 bytes)
s64 FUN_7100055470(s64 param_1, s64 param_2)
{
    s64 lVar1;

    lVar1 = *(s64 *)(*(s64 *)(param_2 + 200) + 0x38);
    if (lVar1 != 0) {
        return lVar1 + (u64)*(u32 *)(param_1 + 0x34);
    }
    return 0;
}

// 0x7100059860 — int: read u16 count from sub-object, subtract bool (32 bytes)
s32 FUN_7100059860(s64 param_1)
{
    if (*(s64 *)(param_1 + 0xa8) != 0) {
        return (u32)*(u16 *)(*(s64 *)(param_1 + 0xa8) + 8) - (u32)(*(s32 *)(param_1 + 0x60) != 0);
    }
    return 0;
}

// 0x7100059890 — pointer arithmetic: return offset into sub-object based on conditions (48 bytes)
s64 FUN_7100059890(s64 param_1)
{
    s64 lVar1;

    lVar1 = *(s64 *)(param_1 + 0xa8);
    if (lVar1 == 0) {
        return 0;
    }
    if (*(s32 *)(param_1 + 0x60) != 0) {
        if (*(s16 *)(lVar1 + 8) == 1) {
            return 0;
        }
        return lVar1 + 0x18;
    }
    return lVar1 + 0xc;
}

// 0x710005e9f0 — vtable dispatch at +0x50, return 0 or field[0x1b] (32 bytes)
s64 FUN_710005e9f0(s64 *param_1, s32 param_2)
{
    (*(void (**)(void))(*param_1 + 0x50))();
    if (param_2 != 0) {
        return 0;
    }
    return param_1[0x1b];
}

// 0x7100060e80 — init: clear four u16 fields, set low bits of first (32 bytes)
void FUN_7100060e80(u16 *param_1)
{
    param_1[4] = 0;
    param_1[5] = 0;
    param_1[6] = 0;
    param_1[7] = 0;
    *param_1 = *param_1 & 0xe000 | 0x90;
}

// 0x7100060ea0 — conditional: clear 4 u16 fields, if param_2 store ptr+set flags, else clear bits (48 bytes)
void FUN_7100060ea0(u16 *param_1, s64 param_2)
{
    u16 uVar1;

    param_1[4] = 0;
    param_1[5] = 0;
    param_1[6] = 0;
    param_1[7] = 0;
    if (param_2 != 0) {
        uVar1 = *param_1;
        *(s64 *)(param_1 + 4) = param_2;
        *param_1 = uVar1 & 0xff00 | 0x90;
        *param_1 = uVar1 & 0xe000 | 0x90;
        return;
    }
    *param_1 = *param_1 & 0xe0ff;
}

// 0x7100060f20 — bit field pack: merge low 2 bits of param_2/param_3 into low nibble (16 bytes)
void FUN_7100060f20(u16 *param_1, u16 param_2, u32 param_3)
{
    *param_1 = param_2 & 3 | (u16)((param_3 & 3) << 2) | *param_1 & 0xfff0;
}

// 0x7100060f40 — bit field pack: merge bits 4-7 from param_2&7, bit 7 from param_3 (16 bytes)
void FUN_7100060f40(u16 *param_1, u32 param_2, u32 param_3)
{
    *param_1 = (u16)((param_2 & 7) << 4) | (u16)((param_3 & 1) << 7) | *param_1 & 0xff0f;
}

// 0x710005a5e0 — init: zero first field, reset 3 sub-objects, memset remainder (48 bytes)
void FUN_710005a5e0(u64 *param_1)
{
    *param_1 = 0;
    FUN_7100060e80((u16 *)(param_1 + 2));
    FUN_7100060e80((u16 *)(param_1 + 4));
    FUN_7100060e80((u16 *)(param_1 + 0xc));
    memset(param_1 + 1, 0, 0x1a1);
}
