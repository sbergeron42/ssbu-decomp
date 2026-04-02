#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7100 address range, batch d4-004
// Pool-d worker: auto-generated from Ghidra decompilation
// Includes: large hash dispatch, bit-flag state machine

// ---- Functions ---------------------------------------------------------------

// 0x71003a0a20 — hash dispatch: decode type byte then binary-search 40-bit hash for opcode
u64 FUN_71003a0a20(s64 param_1, u8 *param_2)
{
    u32 uVar2;
    u64 uVar1;
    u64 uVar3;
    u64 uVar4;

    uVar2 = (u32)*param_2;
    if (uVar2 - 1 < 7) {
        switch(uVar2) {
        case 1:
        case 3:
            uVar1 = (u64)param_2[1];
            break;
        case 2:
            uVar1 = (u64)(s8)param_2[1];
            break;
        case 4:
            uVar1 = (u64)*(s16 *)(param_2 + 1);
            break;
        case 5:
            uVar1 = (u64)*(u16 *)(param_2 + 1);
            break;
        case 6:
        case 7:
            uVar1 = (u64)*(u32 *)(param_2 + 1);
            break;
        default:
            uVar1 = 0;
        }
        uVar1 = uVar1 << 0x20;
        goto LAB_71003a0bd0;
    }
    if (uVar2 != 9) {
        return 0;
    }
    uVar3 = *(u64 *)(*(s64 *)(param_1 + 0x20) + (s64)*(s32 *)(param_2 + 1) * 8) & 0xffffffffff;
    if (uVar3 < 0xb7b38e86d) {
        if (0x84e1d5489 < uVar3) {
            if (uVar3 < 0x99e181983) {
                if (0x9007be1e3 < uVar3) {
                    if (uVar3 < 0x915c5de42) {
                        if (uVar3 == 0x9007be1e4) {
                            uVar1 = 0x4100000000;
                        }
                        else {
                            if (uVar3 != 0x90cf8e2c2) {
                                return 0;
                            }
                            uVar1 = 0x2b00000000;
                        }
                    }
                    else if (uVar3 == 0x915c5de42) {
                        uVar1 = 0x2f00000000;
                    }
                    else if (uVar3 == 0x976c3b29b) {
                        uVar1 = 0x3000000000;
                    }
                    else {
                        if (uVar3 != 0x9929b1aa5) {
                            return 0;
                        }
                        uVar1 = 0x2a00000000;
                    }
                    goto LAB_71003a0bd0;
                }
                if (0x8cc9b876e < uVar3) {
                    if (uVar3 == 0x8cc9b876f) {
                        uVar1 = 0x2900000000;
                    }
                    else if (uVar3 == 0x8d07eaced) {
                        uVar1 = 0x2d00000000;
                    }
                    else {
                        if (uVar3 != 0x8f98399a4) {
                            return 0;
                        }
                        uVar1 = 0x3f00000000;
                    }
                    goto LAB_71003a0bd0;
                }
                if (uVar3 == 0x84e1d548a) {
                    uVar1 = 0x2e00000000;
                    goto LAB_71003a0bd0;
                }
                if (uVar3 != 0x8ca19bc96) {
                    return 0;
                }
            }
            else {
                if (0xa4386c43d < uVar3) {
                    if (uVar3 < 0xab6928cf2) {
                        if (uVar3 == 0xa4386c43e) {
                            uVar1 = 0x4600000000;
                        }
                        else if (uVar3 == 0xa44eb0027) {
                            uVar1 = 0x4200000000;
                        }
                        else {
                            if (uVar3 != 0xaaae5610b) {
                                return 0;
                            }
                            uVar1 = 0x4400000000;
                        }
                    }
                    else if (uVar3 == 0xab6928cf2) {
                        uVar1 = 0x3200000000;
                    }
                    else if (uVar3 == 0xadde2519d) {
                        uVar1 = 0x4300000000;
                    }
                    else {
                        if (uVar3 != 0xae47033ba) {
                            return 0;
                        }
                        uVar1 = 0x3c00000000;
                    }
                    goto LAB_71003a0bd0;
                }
                if (uVar3 < 0xa28f17495) {
                    if (uVar3 == 0x99e181983) {
                        uVar1 = 0x4000000000;
                        goto LAB_71003a0bd0;
                    }
                    if (uVar3 != 0x99f3b6987) {
                        return 0;
                    }
LAB_71003a13a0:
                    uVar1 = 0x100000000;
                    goto LAB_71003a0bd0;
                }
                if (uVar3 == 0xa28f17495) {
                    uVar1 = 0x3100000000;
                    goto LAB_71003a0bd0;
                }
                if (uVar3 != 0xa30cf19b2) {
                    if (uVar3 != 0xa3481f4a8) {
                        return 0;
                    }
                    uVar1 = 0x4500000000;
                    goto LAB_71003a0bd0;
                }
            }
            uVar1 = 0x200000000;
            goto LAB_71003a0bd0;
        }
        if (0x6556ba433 < uVar3) {
            if (uVar3 < 0x7211e5e71) {
                if (uVar3 < 0x6a79e3f0f) {
                    if (uVar3 != 0x6556ba434) {
                        if (uVar3 != 0x696794351) {
                            return 0;
                        }
                        uVar1 = 0x2300000000;
                        goto LAB_71003a0bd0;
                    }
                    goto LAB_71003a149c;
                }
                if (uVar3 != 0x6a79e3f0f) {
                    if (uVar3 == 0x6b0a25677) goto LAB_71003a1340;
                    if (uVar3 != 0x6f3e15596) {
                        return 0;
                    }
                    goto LAB_71003a0ed0;
                }
            }
            else {
                if (0x78004eba4 < uVar3) {
                    if (uVar3 != 0x78004eba5) {
                        if (uVar3 == 0x791e51c56) {
                            uVar1 = 0x2600000000;
                        }
                        else {
                            if (uVar3 != 0x79bb5a346) {
                                return 0;
                            }
                            uVar1 = 0x2c00000000;
                        }
                        goto LAB_71003a0bd0;
                    }
                    goto LAB_71003a14a4;
                }
                if (uVar3 == 0x7211e5e71) {
                    uVar1 = 0xb00000000;
                    goto LAB_71003a0bd0;
                }
                if (uVar3 != 0x738b0c3a4) {
                    if (uVar3 != 0x74de8608c) {
                        return 0;
                    }
                    uVar1 = 0x2200000000;
                    goto LAB_71003a0bd0;
                }
            }
            uVar1 = 0x700000000;
            goto LAB_71003a0bd0;
        }
        if (uVar3 < 0x4f533deef) {
            uVar1 = 0;
            if (uVar3 < 0x47f9000cf) {
                if (uVar3 == 0x3dc43af6e) {
                    uVar1 = 0x4800000000;
                    goto LAB_71003a0bd0;
                }
                uVar4 = 0x764c1c11;
            }
            else {
                if (uVar3 == 0x47f9000cf) {
                    uVar1 = 0xffffffff00000000;
                    goto LAB_71003a0bd0;
                }
                if (uVar3 == 0x49b6edd00) goto LAB_71003a13fc;
                uVar4 = 0xab0788bb;
            }
            if (uVar3 != (uVar4 | 0x400000000)) {
                return 0;
            }
            goto LAB_71003a0bd0;
        }
        if (uVar3 < 0x5bf722094) {
            if (uVar3 == 0x4f533deef) {
LAB_71003a14ac:
                uVar1 = 0x300000000;
                goto LAB_71003a0bd0;
            }
            if (uVar3 != 0x4fb50df0c) {
                return 0;
            }
LAB_71003a13fc:
            uVar1 = 0x400000000;
            goto LAB_71003a0bd0;
        }
        if (uVar3 == 0x5bf722094) goto LAB_71003a13a0;
        if (uVar3 != 0x5c56b7b64) {
            if (uVar3 != 0x647c02d3b) {
                return 0;
            }
            uVar1 = 0x2800000000;
            goto LAB_71003a0bd0;
        }
    }
    else {
        if (0xdde67d934 < uVar3) {
            if (uVar3 < 0xfa4769cbf) {
                if (0xec201e3bb < uVar3) {
                    if (uVar3 < 0xedbdb91cd) {
                        if (uVar3 == 0xec201e3bc) {
                            uVar1 = 0x1600000000;
                        }
                        else {
                            if (uVar3 != 0xed8a31e01) {
                                return 0;
                            }
                            uVar1 = 0x3a00000000;
                        }
                    }
                    else if (uVar3 == 0xedbdb91cd) {
                        uVar1 = 0x2100000000;
                    }
                    else if (uVar3 == 0xf3b8af605) {
                        uVar1 = 0x1b00000000;
                    }
                    else {
                        if (uVar3 != 0xf48927f95) {
                            return 0;
                        }
                        uVar1 = 0x1100000000;
                    }
                    goto LAB_71003a0bd0;
                }
                if (0xe45ca50fd < uVar3) {
                    if (uVar3 == 0xe45ca50fe) {
                        uVar1 = 0x2500000000;
                    }
                    else if (uVar3 == 0xe46c0e666) {
                        uVar1 = 0x3b00000000;
                    }
                    else {
                        if (uVar3 != 0xe78fcc0de) {
                            return 0;
                        }
                        uVar1 = 0x1d00000000;
                    }
                    goto LAB_71003a0bd0;
                }
                if (uVar3 == 0xdde67d935) {
                    uVar1 = 0x3600000000;
                    goto LAB_71003a0bd0;
                }
                if (uVar3 != 0xdfe89581e) {
                    return 0;
                }
LAB_71003a149c:
                uVar1 = 0x600000000;
                goto LAB_71003a0bd0;
            }
            if (0x129bc90dcc < uVar3) {
                if (uVar3 < 0x13cbf15113) {
                    if (uVar3 == 0x129bc90dcd) {
                        uVar1 = 0x1400000000;
                    }
                    else if (uVar3 == 0x1302834a39) {
                        uVar1 = 0x1500000000;
                    }
                    else {
                        if (uVar3 != 0x133327aa87) {
                            return 0;
                        }
                        uVar1 = 0x1900000000;
                    }
                }
                else if (uVar3 == 0x13cbf15113) {
                    uVar1 = 0x3e00000000;
                }
                else if (uVar3 == 0x14c74f7d71) {
                    uVar1 = 0x2400000000;
                }
                else {
                    if (uVar3 != 0x14c76a6159) {
                        return 0;
                    }
                    uVar1 = 0x1700000000;
                }
                goto LAB_71003a0bd0;
            }
            if (0x1059a64ec8 < uVar3) {
                if (uVar3 == 0x1059a64ec9) {
                    uVar1 = 0x1a00000000;
                }
                else if (uVar3 == 0x11923bd1ef) {
                    uVar1 = 0x1800000000;
                }
                else {
                    if (uVar3 != 0x129b12d785) {
                        return 0;
                    }
                    uVar1 = 0x3d00000000;
                }
                goto LAB_71003a0bd0;
            }
            if (uVar3 != 0xfa4769cbf) {
                if (uVar3 != 0x104eb58716) {
                    return 0;
                }
                goto LAB_71003a14ac;
            }
LAB_71003a14a4:
            uVar1 = 0x500000000;
            goto LAB_71003a0bd0;
        }
        if (0xd1bef7309 < uVar3) {
            if (uVar3 < 0xd6014b8e2) {
                if (uVar3 < 0xd40042152) {
                    if (uVar3 == 0xd1bef730a) {
                        uVar1 = 0x1f00000000;
                    }
                    else {
                        if (uVar3 != 0xd2b3a620b) {
                            return 0;
                        }
                        uVar1 = 0x3900000000;
                    }
                }
                else if (uVar3 == 0xd40042152) {
                    uVar1 = 0x3700000000;
                }
                else if (uVar3 == 0xd483c0ed2) {
                    uVar1 = 0x3800000000;
                }
                else {
                    if (uVar3 != 0xd51a54dee) {
                        return 0;
                    }
                    uVar1 = 0xe00000000;
                }
                goto LAB_71003a0bd0;
            }
            if (0xd9de36c6c < uVar3) {
                if (uVar3 == 0xd9de36c6d) {
                    uVar1 = 0x1300000000;
                }
                else if (uVar3 == 0xdab964a4c) {
                    uVar1 = 0x1200000000;
                }
                else {
                    if (uVar3 != 0xdb8672fc7) {
                        return 0;
                    }
                    uVar1 = 0xc00000000;
                }
                goto LAB_71003a0bd0;
            }
            if (uVar3 == 0xd6014b8e2) {
LAB_71003a1340:
                uVar1 = 0xa00000000;
                goto LAB_71003a0bd0;
            }
            if (uVar3 == 0xd81c59e15) {
                uVar1 = 0x1000000000;
                goto LAB_71003a0bd0;
            }
            if (uVar3 != 0xd8823fcd2) {
                return 0;
            }
LAB_71003a0ed0:
            uVar1 = 0x900000000;
            goto LAB_71003a0bd0;
        }
        if (uVar3 < 0xc3a4e2597) {
            if (uVar3 < 0xc2248f61c) {
                if (uVar3 == 0xb7b38e86d) {
                    uVar1 = 0x2700000000;
                }
                else {
                    if (uVar3 != 0xbb4f89cce) {
                        return 0;
                    }
                    uVar1 = 0xd00000000;
                }
            }
            else if (uVar3 == 0xc2248f61c) {
                uVar1 = 0x2000000000;
            }
            else if (uVar3 == 0xc33f869bc) {
                uVar1 = 0x3500000000;
            }
            else {
                if (uVar3 != 0xc3495ada5) {
                    return 0;
                }
                uVar1 = 0x3400000000;
            }
            goto LAB_71003a0bd0;
        }
        if (0xcf5b33543 < uVar3) {
            if (uVar3 == 0xcf5b33544) {
                uVar1 = 0xf00000000;
            }
            else if (uVar3 == 0xcf954c9be) {
                uVar1 = 0x1c00000000;
            }
            else {
                if (uVar3 != 0xcff414a68) {
                    return 0;
                }
                uVar1 = 0x1e00000000;
            }
            goto LAB_71003a0bd0;
        }
        if (uVar3 == 0xc3a4e2597) {
            uVar1 = 0x3300000000;
            goto LAB_71003a0bd0;
        }
        if (uVar3 != 0xc45264430) {
            return 0;
        }
    }
    uVar1 = 0x800000000;
LAB_71003a0bd0:
    return uVar1 | 1;
}

// 0x71003abd60 — motion-flag updater: update status bytes at +0x3a/0xa2/0x10a/0x172/0x1da based on flags
void FUN_71003abd60(s64 param_1)
{
    u8 bVar1;
    s8 cVar2;
    s64 lVar3;
    u8 uVar4;

    if ((*(u8 *)(param_1 + 100) & 1) == 0) {
        if ((*(u8 *)(param_1 + 100) >> 1 & 1) != 0) goto LAB_71003abdd8;
LAB_71003abd70:
        bVar1 = *(u8 *)(param_1 + 100);
joined_r0x0071003abe1c:
        if ((bVar1 >> 2 & 1) == 0) goto LAB_71003abd78;
LAB_71003abe20:
        lVar3 = *(s64 *)(param_1 + 8);
        cVar2 = *(s8 *)(lVar3 + 0x10c);
        if (cVar2 != -1) {
            if ((*(u8 *)(param_1 + 0x65) >> 2 & 1) == 0) {
                if (cVar2 != '\x01') goto LAB_71003abe3c;
LAB_71003abe58:
                uVar4 = 2;
            }
            else {
                if (cVar2 == '\0') goto LAB_71003abe58;
LAB_71003abe3c:
                uVar4 = 0xff;
            }
            *(u8 *)(lVar3 + 0x10c) = uVar4;
            bVar1 = *(u8 *)(param_1 + 100);
            goto joined_r0x0071003abe64;
        }
        if ((*(u8 *)(param_1 + 0x65) >> 2 & 1) == 0) {
            uVar4 = 4;
        }
        else {
            uVar4 = 5;
        }
        *(u8 *)(lVar3 + 0x10a) = uVar4;
        if ((*(u8 *)(param_1 + 100) >> 3 & 1) == 0) goto LAB_71003abd80;
LAB_71003abe68:
        lVar3 = *(s64 *)(param_1 + 8);
        cVar2 = *(s8 *)(lVar3 + 0x174);
        if (cVar2 == -1) {
            if ((*(u8 *)(param_1 + 0x65) >> 3 & 1) == 0) {
                uVar4 = 4;
            }
            else {
                uVar4 = 5;
            }
            *(u8 *)(lVar3 + 0x172) = uVar4;
            bVar1 = *(u8 *)(param_1 + 100);
        }
        else {
            if ((*(u8 *)(param_1 + 0x65) >> 3 & 1) == 0) {
                if (cVar2 != '\x01') goto LAB_71003abe84;
LAB_71003abea0:
                uVar4 = 2;
            }
            else {
                if (cVar2 == '\0') goto LAB_71003abea0;
LAB_71003abe84:
                uVar4 = 0xff;
            }
            *(u8 *)(lVar3 + 0x174) = uVar4;
            bVar1 = *(u8 *)(param_1 + 100);
        }
    }
    else {
        lVar3 = *(s64 *)(param_1 + 8);
        cVar2 = *(s8 *)(lVar3 + 0x3c);
        if (cVar2 == -1) {
            if ((*(u8 *)(param_1 + 0x65) & 1) == 0) {
                uVar4 = 4;
            }
            else {
                uVar4 = 5;
            }
            *(u8 *)(lVar3 + 0x3a) = uVar4;
            bVar1 = *(u8 *)(param_1 + 100);
        }
        else {
            if ((*(u8 *)(param_1 + 0x65) & 1) == 0) {
                if (cVar2 != '\x01') goto LAB_71003abdac;
LAB_71003abdc8:
                uVar4 = 2;
            }
            else {
                if (cVar2 == '\0') goto LAB_71003abdc8;
LAB_71003abdac:
                uVar4 = 0xff;
            }
            *(u8 *)(lVar3 + 0x3c) = uVar4;
            bVar1 = *(u8 *)(param_1 + 100);
        }
        if ((bVar1 >> 1 & 1) == 0) goto LAB_71003abd70;
LAB_71003abdd8:
        lVar3 = *(s64 *)(param_1 + 8);
        cVar2 = *(s8 *)(lVar3 + 0xa4);
        if (cVar2 != -1) {
            if ((*(u8 *)(param_1 + 0x65) >> 1 & 1) == 0) {
                if (cVar2 != '\x01') goto LAB_71003abdf4;
LAB_71003abe10:
                uVar4 = 2;
            }
            else {
                if (cVar2 == '\0') goto LAB_71003abe10;
LAB_71003abdf4:
                uVar4 = 0xff;
            }
            *(u8 *)(lVar3 + 0xa4) = uVar4;
            bVar1 = *(u8 *)(param_1 + 100);
            goto joined_r0x0071003abe1c;
        }
        if ((*(u8 *)(param_1 + 0x65) >> 1 & 1) == 0) {
            uVar4 = 4;
        }
        else {
            uVar4 = 5;
        }
        *(u8 *)(lVar3 + 0xa2) = uVar4;
        if ((*(u8 *)(param_1 + 100) >> 2 & 1) != 0) goto LAB_71003abe20;
LAB_71003abd78:
        bVar1 = *(u8 *)(param_1 + 100);
joined_r0x0071003abe64:
        if ((bVar1 >> 3 & 1) != 0) goto LAB_71003abe68;
LAB_71003abd80:
        bVar1 = *(u8 *)(param_1 + 100);
    }
    if ((bVar1 >> 4 & 1) == 0) {
        *(u8 *)(param_1 + 100) = 0;
        return;
    }
    lVar3 = *(s64 *)(param_1 + 8);
    cVar2 = *(s8 *)(lVar3 + 0x1dc);
    if (cVar2 == -1) {
        if ((*(u8 *)(param_1 + 0x65) >> 4 & 1) == 0) {
            uVar4 = 4;
        }
        else {
            uVar4 = 5;
        }
        *(u8 *)(lVar3 + 0x1da) = uVar4;
        *(u8 *)(param_1 + 100) = 0;
        return;
    }
    if ((*(u8 *)(param_1 + 0x65) >> 4 & 1) == 0) {
        if (cVar2 == '\x01') goto LAB_71003abef0;
    }
    else if (cVar2 == '\0') {
LAB_71003abef0:
        *(u8 *)(lVar3 + 0x1dc) = 2;
        *(u8 *)(param_1 + 100) = 0;
        return;
    }
    *(u8 *)(lVar3 + 0x1dc) = 0xff;
    *(u8 *)(param_1 + 100) = 0;
}
