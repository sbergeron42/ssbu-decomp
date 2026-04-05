#include "types.h"

// 0x71003a0a20 — Script VM operand decoder
// Reads a type tag from stream[0], decodes the operand value based on type:
//   Types 1-7: read immediate of varying size/signedness from stream[1..]
//   Type 9:    resolve a 40-bit hash from indirect table at ctx+0x20 to an opcode index
// Returns: (opcode_index << 32) | 1 on success, 0 on unknown type/hash
u64 FUN_71003a0a20(s64 ctx, u8 *stream)
{
    u32 type_byte;
    u64 result;
    u64 hash;
    u64 temp;

    type_byte = (u32)*stream;
    if (type_byte - 1 < 7) {
        switch(type_byte) {
        case 1:
        case 3:
            result = (u64)stream[1];
            break;
        case 2:
            result = (u64)(s8)stream[1];
            break;
        case 4:
            result = (u64)*(s16 *)(stream + 1);
            break;
        case 5:
            result = (u64)*(u16 *)(stream + 1);
            break;
        case 6:
        case 7:
            result = (u64)*(u32 *)(stream + 1);
            break;
        default:
            result = 0;
        }
        result = result << 0x20;
        goto LAB_71003a0bd0;
    }
    if (type_byte != 9) {
        return 0;
    }
    hash = *(u64 *)(*(s64 *)(ctx + 0x20) + (s64)*(s32 *)(stream + 1) * 8) & 0xffffffffff;
    if (hash < 0xb7b38e86d) {
        if (0x84e1d5489 < hash) {
            if (hash < 0x99e181983) {
                if (0x9007be1e3 < hash) {
                    if (hash < 0x915c5de42) {
                        if (hash == 0x9007be1e4) {
                            result = 0x4100000000;
                        }
                        else {
                            if (hash != 0x90cf8e2c2) {
                                return 0;
                            }
                            result = 0x2b00000000;
                        }
                    }
                    else if (hash == 0x915c5de42) {
                        result = 0x2f00000000;
                    }
                    else if (hash == 0x976c3b29b) {
                        result = 0x3000000000;
                    }
                    else {
                        if (hash != 0x9929b1aa5) {
                            return 0;
                        }
                        result = 0x2a00000000;
                    }
                    goto LAB_71003a0bd0;
                }
                if (0x8cc9b876e < hash) {
                    if (hash == 0x8cc9b876f) {
                        result = 0x2900000000;
                    }
                    else if (hash == 0x8d07eaced) {
                        result = 0x2d00000000;
                    }
                    else {
                        if (hash != 0x8f98399a4) {
                            return 0;
                        }
                        result = 0x3f00000000;
                    }
                    goto LAB_71003a0bd0;
                }
                if (hash == 0x84e1d548a) {
                    result = 0x2e00000000;
                    goto LAB_71003a0bd0;
                }
                if (hash != 0x8ca19bc96) {
                    return 0;
                }
            }
            else {
                if (0xa4386c43d < hash) {
                    if (hash < 0xab6928cf2) {
                        if (hash == 0xa4386c43e) {
                            result = 0x4600000000;
                        }
                        else if (hash == 0xa44eb0027) {
                            result = 0x4200000000;
                        }
                        else {
                            if (hash != 0xaaae5610b) {
                                return 0;
                            }
                            result = 0x4400000000;
                        }
                    }
                    else if (hash == 0xab6928cf2) {
                        result = 0x3200000000;
                    }
                    else if (hash == 0xadde2519d) {
                        result = 0x4300000000;
                    }
                    else {
                        if (hash != 0xae47033ba) {
                            return 0;
                        }
                        result = 0x3c00000000;
                    }
                    goto LAB_71003a0bd0;
                }
                if (hash < 0xa28f17495) {
                    if (hash == 0x99e181983) {
                        result = 0x4000000000;
                        goto LAB_71003a0bd0;
                    }
                    if (hash != 0x99f3b6987) {
                        return 0;
                    }
LAB_71003a13a0:
                    result = 0x100000000;
                    goto LAB_71003a0bd0;
                }
                if (hash == 0xa28f17495) {
                    result = 0x3100000000;
                    goto LAB_71003a0bd0;
                }
                if (hash != 0xa30cf19b2) {
                    if (hash != 0xa3481f4a8) {
                        return 0;
                    }
                    result = 0x4500000000;
                    goto LAB_71003a0bd0;
                }
            }
            result = 0x200000000;
            goto LAB_71003a0bd0;
        }
        if (0x6556ba433 < hash) {
            if (hash < 0x7211e5e71) {
                if (hash < 0x6a79e3f0f) {
                    if (hash != 0x6556ba434) {
                        if (hash != 0x696794351) {
                            return 0;
                        }
                        result = 0x2300000000;
                        goto LAB_71003a0bd0;
                    }
                    goto LAB_71003a149c;
                }
                if (hash != 0x6a79e3f0f) {
                    if (hash == 0x6b0a25677) goto LAB_71003a1340;
                    if (hash != 0x6f3e15596) {
                        return 0;
                    }
                    goto LAB_71003a0ed0;
                }
            }
            else {
                if (0x78004eba4 < hash) {
                    if (hash != 0x78004eba5) {
                        if (hash == 0x791e51c56) {
                            result = 0x2600000000;
                        }
                        else {
                            if (hash != 0x79bb5a346) {
                                return 0;
                            }
                            result = 0x2c00000000;
                        }
                        goto LAB_71003a0bd0;
                    }
                    goto LAB_71003a14a4;
                }
                if (hash == 0x7211e5e71) {
                    result = 0xb00000000;
                    goto LAB_71003a0bd0;
                }
                if (hash != 0x738b0c3a4) {
                    if (hash != 0x74de8608c) {
                        return 0;
                    }
                    result = 0x2200000000;
                    goto LAB_71003a0bd0;
                }
            }
            result = 0x700000000;
            goto LAB_71003a0bd0;
        }
        if (hash < 0x4f533deef) {
            result = 0;
            if (hash < 0x47f9000cf) {
                if (hash == 0x3dc43af6e) {
                    result = 0x4800000000;
                    goto LAB_71003a0bd0;
                }
                temp = 0x764c1c11;
            }
            else {
                if (hash == 0x47f9000cf) {
                    result = 0xffffffff00000000;
                    goto LAB_71003a0bd0;
                }
                if (hash == 0x49b6edd00) goto LAB_71003a13fc;
                temp = 0xab0788bb;
            }
            if (hash != (temp | 0x400000000)) {
                return 0;
            }
            goto LAB_71003a0bd0;
        }
        if (hash < 0x5bf722094) {
            if (hash == 0x4f533deef) {
LAB_71003a14ac:
                result = 0x300000000;
                goto LAB_71003a0bd0;
            }
            if (hash != 0x4fb50df0c) {
                return 0;
            }
LAB_71003a13fc:
            result = 0x400000000;
            goto LAB_71003a0bd0;
        }
        if (hash == 0x5bf722094) goto LAB_71003a13a0;
        if (hash != 0x5c56b7b64) {
            if (hash != 0x647c02d3b) {
                return 0;
            }
            result = 0x2800000000;
            goto LAB_71003a0bd0;
        }
    }
    else {
        if (0xdde67d934 < hash) {
            if (hash < 0xfa4769cbf) {
                if (0xec201e3bb < hash) {
                    if (hash < 0xedbdb91cd) {
                        if (hash == 0xec201e3bc) {
                            result = 0x1600000000;
                        }
                        else {
                            if (hash != 0xed8a31e01) {
                                return 0;
                            }
                            result = 0x3a00000000;
                        }
                    }
                    else if (hash == 0xedbdb91cd) {
                        result = 0x2100000000;
                    }
                    else if (hash == 0xf3b8af605) {
                        result = 0x1b00000000;
                    }
                    else {
                        if (hash != 0xf48927f95) {
                            return 0;
                        }
                        result = 0x1100000000;
                    }
                    goto LAB_71003a0bd0;
                }
                if (0xe45ca50fd < hash) {
                    if (hash == 0xe45ca50fe) {
                        result = 0x2500000000;
                    }
                    else if (hash == 0xe46c0e666) {
                        result = 0x3b00000000;
                    }
                    else {
                        if (hash != 0xe78fcc0de) {
                            return 0;
                        }
                        result = 0x1d00000000;
                    }
                    goto LAB_71003a0bd0;
                }
                if (hash == 0xdde67d935) {
                    result = 0x3600000000;
                    goto LAB_71003a0bd0;
                }
                if (hash != 0xdfe89581e) {
                    return 0;
                }
LAB_71003a149c:
                result = 0x600000000;
                goto LAB_71003a0bd0;
            }
            if (0x129bc90dcc < hash) {
                if (hash < 0x13cbf15113) {
                    if (hash == 0x129bc90dcd) {
                        result = 0x1400000000;
                    }
                    else if (hash == 0x1302834a39) {
                        result = 0x1500000000;
                    }
                    else {
                        if (hash != 0x133327aa87) {
                            return 0;
                        }
                        result = 0x1900000000;
                    }
                }
                else if (hash == 0x13cbf15113) {
                    result = 0x3e00000000;
                }
                else if (hash == 0x14c74f7d71) {
                    result = 0x2400000000;
                }
                else {
                    if (hash != 0x14c76a6159) {
                        return 0;
                    }
                    result = 0x1700000000;
                }
                goto LAB_71003a0bd0;
            }
            if (0x1059a64ec8 < hash) {
                if (hash == 0x1059a64ec9) {
                    result = 0x1a00000000;
                }
                else if (hash == 0x11923bd1ef) {
                    result = 0x1800000000;
                }
                else {
                    if (hash != 0x129b12d785) {
                        return 0;
                    }
                    result = 0x3d00000000;
                }
                goto LAB_71003a0bd0;
            }
            if (hash != 0xfa4769cbf) {
                if (hash != 0x104eb58716) {
                    return 0;
                }
                goto LAB_71003a14ac;
            }
LAB_71003a14a4:
            result = 0x500000000;
            goto LAB_71003a0bd0;
        }
        if (0xd1bef7309 < hash) {
            if (hash < 0xd6014b8e2) {
                if (hash < 0xd40042152) {
                    if (hash == 0xd1bef730a) {
                        result = 0x1f00000000;
                    }
                    else {
                        if (hash != 0xd2b3a620b) {
                            return 0;
                        }
                        result = 0x3900000000;
                    }
                }
                else if (hash == 0xd40042152) {
                    result = 0x3700000000;
                }
                else if (hash == 0xd483c0ed2) {
                    result = 0x3800000000;
                }
                else {
                    if (hash != 0xd51a54dee) {
                        return 0;
                    }
                    result = 0xe00000000;
                }
                goto LAB_71003a0bd0;
            }
            if (0xd9de36c6c < hash) {
                if (hash == 0xd9de36c6d) {
                    result = 0x1300000000;
                }
                else if (hash == 0xdab964a4c) {
                    result = 0x1200000000;
                }
                else {
                    if (hash != 0xdb8672fc7) {
                        return 0;
                    }
                    result = 0xc00000000;
                }
                goto LAB_71003a0bd0;
            }
            if (hash == 0xd6014b8e2) {
LAB_71003a1340:
                result = 0xa00000000;
                goto LAB_71003a0bd0;
            }
            if (hash == 0xd81c59e15) {
                result = 0x1000000000;
                goto LAB_71003a0bd0;
            }
            if (hash != 0xd8823fcd2) {
                return 0;
            }
LAB_71003a0ed0:
            result = 0x900000000;
            goto LAB_71003a0bd0;
        }
        if (hash < 0xc3a4e2597) {
            if (hash < 0xc2248f61c) {
                if (hash == 0xb7b38e86d) {
                    result = 0x2700000000;
                }
                else {
                    if (hash != 0xbb4f89cce) {
                        return 0;
                    }
                    result = 0xd00000000;
                }
            }
            else if (hash == 0xc2248f61c) {
                result = 0x2000000000;
            }
            else if (hash == 0xc33f869bc) {
                result = 0x3500000000;
            }
            else {
                if (hash != 0xc3495ada5) {
                    return 0;
                }
                result = 0x3400000000;
            }
            goto LAB_71003a0bd0;
        }
        if (0xcf5b33543 < hash) {
            if (hash == 0xcf5b33544) {
                result = 0xf00000000;
            }
            else if (hash == 0xcf954c9be) {
                result = 0x1c00000000;
            }
            else {
                if (hash != 0xcff414a68) {
                    return 0;
                }
                result = 0x1e00000000;
            }
            goto LAB_71003a0bd0;
        }
        if (hash == 0xc3a4e2597) {
            result = 0x3300000000;
            goto LAB_71003a0bd0;
        }
        if (hash != 0xc45264430) {
            return 0;
        }
    }
    result = 0x800000000;
LAB_71003a0bd0:
    return result | 1;
}

// FUN_71003abd60 — defined in fun_med_final_b_010.cpp (cleaner rewrite already exists there)
