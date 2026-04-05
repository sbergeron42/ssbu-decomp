// Batch C - 017: MEDIUM FUN_* batch decompilation (0x7102 range)
// Functions: 2 - Hash binary tree lookup functions

#include "types.h"

// 0x71026d0af0
u64 FUN_71026d0af0(s64 param_1, u8 *param_2)
{
    u64 result;
    u32 type_tag;
    u64 hash;

    type_tag = (u32)*param_2;
    if (type_tag - 1 < 7) {
        switch(type_tag) {
        case 1:
        case 3:
            result = (u64)param_2[1];
            break;
        case 2:
            result = (u64)(char)param_2[1];
            break;
        case 4:
            result = (u64)*(s16 *)(param_2 + 1);
            break;
        case 5:
            result = (u64)*(u16 *)(param_2 + 1);
            break;
        case 6:
        case 7:
            result = (u64)*(u32 *)(param_2 + 1);
            break;
        default:
            result = 0;
        }
        result = result << 0x20;
        goto LAB_71026d0ccc;
    }
    if (type_tag != 9) {
        return 0;
    }
    hash = *(u64 *)(*(s64 *)(param_1 + 0x20) + (s64)*(s32 *)(param_2 + 1) * 8) & 0xffffffffff;
    if (hash < 0x1e3ae8c9f9) {
        result = 0;
        if (0x1abf715126 < hash) {
            if (0x1c89c9c2c4 < hash) {
                if (hash < 0x1d7808e1ba) {
                    if (0x1cf08c9a52 < hash) {
                        if (0x1d600d17e9 < hash) {
                            if (hash == 0x1d600d17ea) {
LAB_71026d1928:
                                result = 0x1700000000;
                                goto LAB_71026d0ccc;
                            }
                            if (hash != 0x1d6c35808e) {
                                if (hash != 0x1d707084a0) {
                                    return 0;
                                }
                                goto LAB_71026d1d2c;
                            }
LAB_71026d1050:
                            result = 0xd00000000;
                            goto LAB_71026d0ccc;
                        }
                        if (hash == 0x1cf08c9a53) {
                            result = 0x8000000100000000;
                            goto LAB_71026d0ccc;
                        }
                        if (hash != 0x1d0f3340a1) {
                            return 0;
                        }
LAB_71026d1784:
                        result = 0xf00000000;
                        goto LAB_71026d0ccc;
                    }
                    if (hash < 0x1cd91cdd73) {
                        if (hash == 0x1c89c9c2c5) goto LAB_71026d1c1c;
                        result = 0xc22d24d3;
                    }
                    else {
                        if (hash == 0x1cd91cdd73) {
                            result = 0x1100000000;
                            goto LAB_71026d0ccc;
                        }
                        result = 0xe0f1d8ec;
                    }
                    if (hash != (result | 0x1c00000000)) {
                        return 0;
                    }
                    goto LAB_71026d1a74;
                }
                if (0x1dcafa394b < hash) {
                    if (0x1ded09afe2 < hash) {
                        if (hash == 0x1ded09afe3) {
LAB_71026d1d1c:
                            result = 0x2000000000;
                            goto LAB_71026d0ccc;
                        }
                        if (hash != 0x1e1bc21503) {
                            if (hash != 0x1e20ed33da) {
                                return 0;
                            }
                            result = 0x2e00000000;
                            goto LAB_71026d0ccc;
                        }
LAB_71026d18f0:
                        result = 0x3d00000000;
                        goto LAB_71026d0ccc;
                    }
                    if (hash != 0x1dcafa394c) {
                        if (hash != 0x1de5509806) {
                            return 0;
                        }
                        result = 0x3c00000000;
                        goto LAB_71026d0ccc;
                    }
LAB_71026d1b44:
                    result = 0xb00000000;
                    goto LAB_71026d0ccc;
                }
                if (hash < 0x1da8d32364) {
                    if (hash == 0x1d7808e1ba) {
                        result = 0x8000000300000000;
                        goto LAB_71026d0ccc;
                    }
                    if (hash != 0x1da727dda7) {
                        return 0;
                    }
                    goto LAB_71026d1c4c;
                }
                if (hash != 0x1da8d32364) {
                    if (hash != 0x1dc7d376a5) {
                        return 0;
                    }
                    result = 0x4e00000000;
                    goto LAB_71026d0ccc;
                }
                goto LAB_71026d1c1c;
            }
            if (0x1bedba73ce < hash) {
                if (hash < 0x1c1ba64c99) {
                    if (hash < 0x1c0ae27e24) {
                        if (hash != 0x1bedba73cf) {
                            if (hash != 0x1c013682e2) {
                                return 0;
                            }
                            goto LAB_71026d1d24;
                        }
                        goto LAB_71026d1ae4;
                    }
                    if (hash == 0x1c0ae27e24) goto LAB_71026d1b44;
                    if (hash != 0x1c0eb10be3) {
                        return 0;
                    }
                }
                else {
                    if (hash < 0x1c3cd3e508) {
                        if (hash == 0x1c1ba64c99) {
                            result = 0x4c00000000;
                            goto LAB_71026d0ccc;
                        }
                        if (hash != 0x1c2f7a650c) {
                            return 0;
                        }
                        goto LAB_71026d19e4;
                    }
                    if (hash != 0x1c3cd3e508) {
                        if (hash != 0x1c4627fa8f) {
                            if (hash != 0x1c807afd3d) {
                                return 0;
                            }
                            goto LAB_71026d0ccc;
                        }
                        goto LAB_71026d18f0;
                    }
                }
LAB_71026d1c7c:
                result = 0x700000000;
                goto LAB_71026d0ccc;
            }
            if (hash < 0x1b19308703) {
                if (hash < 0x1ae13e9305) {
                    if ((hash != 0x1abf715127) && (hash != 0x1ac4d90a73)) {
                        return 0;
                    }
                    goto LAB_71026d1cac;
                }
                if (hash == 0x1ae13e9305) {
LAB_71026d1d34:
                    result = 0x1000000000;
                    goto LAB_71026d0ccc;
                }
                if (hash != 0x1afddcec06) {
                    return 0;
                }
            }
            else {
                if (0x1bde8ff303 < hash) {
                    if (hash != 0x1bde8ff304) {
                        if (hash != 0x1beac53520) {
                            return 0;
                        }
                        result = 0x2300000000;
                        goto LAB_71026d0ccc;
                    }
LAB_71026d1d3c:
                    result = 0x3f00000000;
                    goto LAB_71026d0ccc;
                }
                if (hash == 0x1b19308703) goto LAB_71026d1784;
                if (hash != 0x1b4d027a79) {
                    return 0;
                }
            }
            goto LAB_71026d1ae4;
        }
        if (0x185be87e9f < hash) {
            if (hash < 0x19d8701188) {
                if (hash < 0x1900a16150) {
                    if (hash < 0x189ef7c5e8) {
                        if (hash == 0x185be87ea0) goto LAB_71026d1be4;
                        if (hash != 0x187d583698) {
                            return 0;
                        }
                        goto LAB_71026d1ba4;
                    }
                    if (hash != 0x189ef7c5e8) {
                        if (hash != 0x18c8e98293) {
                            return 0;
                        }
                        result = 0xe00000000;
                        goto LAB_71026d0ccc;
                    }
                }
                else {
                    if (hash < 0x199e7bc742) {
                        if (hash == 0x1900a16150) goto LAB_71026d1b44;
                        if (hash != 0x1920ee5d2e) {
                            return 0;
                        }
                        goto LAB_71026d1c7c;
                    }
                    if (hash == 0x199e7bc742) goto LAB_71026d1c1c;
                    if (hash == 0x19b54ed1b7) {
                        result = 0x5000000000;
                        goto LAB_71026d0ccc;
                    }
                    if (hash != 0x19d5c78f1a) {
                        return 0;
                    }
                }
LAB_71026d1a74:
                result = 0x400000000;
            }
            else {
                if (0x1a3cd9a171 < hash) {
                    if (hash < 0x1a5612f412) {
                        if (hash != 0x1a3cd9a172) {
                            if (hash != 0x1a4035e5d8) {
                                return 0;
                            }
                            result = 0xa00000000;
                            goto LAB_71026d0ccc;
                        }
LAB_71026d1d24:
                        result = 0x600000000;
                        goto LAB_71026d0ccc;
                    }
                    if (hash != 0x1a5612f412) {
                        if (hash == 0x1a92090074) {
                            result = 0x4f00000000;
                            goto LAB_71026d0ccc;
                        }
                        if (hash != 0x1ab95511b5) {
                            return 0;
                        }
                        goto LAB_71026d1050;
                    }
                    goto LAB_71026d1c1c;
                }
                if (hash < 0x1a042cd3ef) {
                    if (hash != 0x19d8701188) {
                        if (hash != 0x19ff3e1888) {
                            return 0;
                        }
                        goto LAB_71026d0ccc;
                    }
LAB_71026d1adc:
                    result = 0x800000000;
                    goto LAB_71026d0ccc;
                }
                if (hash == 0x1a042cd3ef) goto LAB_71026d1bac;
                if (hash != 0x1a130b6ef1) {
                    return 0;
                }
LAB_71026d1ba4:
                result = 0x900000000;
            }
            goto LAB_71026d0ccc;
        }
        if (0x14d9ca6a0a < hash) {
            if (hash < 0x15f087af49) {
                if (0x15010dd11b < hash) {
                    if (hash != 0x15010dd11c) {
                        if (hash != 0x154b6b24ab) {
                            return 0;
                        }
                        goto LAB_71026d1adc;
                    }
                    goto LAB_71026d1ae4;
                }
                if (hash != 0x14d9ca6a0b) {
                    if (hash != 0x14e734bf1f) {
                        return 0;
                    }
                    goto LAB_71026d1bac;
                }
            }
            else {
                if (0x1777723c77 < hash) {
                    if (hash == 0x1777723c78) goto LAB_71026d1754;
                    if (hash != 0x1798a00332) {
                        if (hash != 0x1854e3a50a) {
                            return 0;
                        }
                        goto LAB_71026d1bac;
                    }
LAB_71026d1ae4:
                    result = 0x300000000;
                    goto LAB_71026d0ccc;
                }
                if (hash == 0x15f087af49) goto LAB_71026d1cac;
                if (hash != 0x1762df116c) {
                    return 0;
                }
            }
LAB_71026d1c1c:
            result = 0x200000000;
            goto LAB_71026d0ccc;
        }
        if (hash < 0x140b342854) {
            if (hash < 0x12464ef7c0) {
                if (hash != 0x11c8f620e5) {
                    if (hash != 0x11cf9be4fc) {
                        return 0;
                    }
                    goto LAB_71026d1a74;
                }
                goto LAB_71026d1ae4;
            }
            if (hash != 0x12464ef7c0) {
                if (hash != 0x136a7c7544) {
                    return 0;
                }
                goto LAB_71026d0ccc;
            }
            goto LAB_71026d1c1c;
        }
        if (hash < 0x14aecd5a9d) {
            if (hash != 0x140b342854) {
                if (hash != 0x1454c267fe) {
                    return 0;
                }
                goto LAB_71026d0ccc;
            }
LAB_71026d1bac:
            result = 0x500000000;
            goto LAB_71026d0ccc;
        }
        if (hash != 0x14aecd5a9d) {
            if (hash != 0x14d45c28b1) {
                return 0;
            }
            goto LAB_71026d1c7c;
        }
    }
    else {
        if (0x2216ca77c0 < hash) {
            if (hash < 0x24d6eee396) {
                if (hash < 0x23723258ad) {
                    if (hash < 0x22d66e8a25) {
                        if (hash < 0x222bb85667) {
                            if (hash == 0x2216ca77c1) {
                                result = 0x2d00000000;
                            }
                            else {
                                if (hash != 0x222a600352) {
                                    return 0;
                                }
                                result = 0x3a00000000;
                            }
                            goto LAB_71026d0ccc;
                        }
                        if (hash != 0x222bb85667) {
                            if (hash != 0x227cfc8a95) {
                                return 0;
                            }
                            result = 0x4b00000000;
                            goto LAB_71026d0ccc;
                        }
                        goto LAB_71026d19e4;
                    }
                    if (0x23415d63a3 < hash) {
                        if (hash == 0x23415d63a4) {
                            result = 0x2400000000;
                        }
                        else {
                            if (hash != 0x234f3bf32b) {
                                return 0;
                            }
                            result = 0x4500000000;
                        }
                        goto LAB_71026d0ccc;
                    }
                    if (hash != 0x22d66e8a25) {
                        if (hash != 0x230535683b) {
                            return 0;
                        }
                        result = 0x4400000000;
                        goto LAB_71026d0ccc;
                    }
                }
                else {
                    if (hash < 0x23d632a291) {
                        if (hash < 0x23a1359207) {
                            if (hash == 0x23723258ad) {
                                result = 0x4300000000;
                            }
                            else {
                                if (hash != 0x2374dfc186) {
                                    return 0;
                                }
                                result = 0x3100000000;
                            }
                        }
                        else if (hash == 0x23a1359207) {
                            result = 0x4700000000;
                        }
                        else {
                            if (hash != 0x23a208a58c) {
                                return 0;
                            }
                            result = 0x4a00000000;
                        }
                        goto LAB_71026d0ccc;
                    }
                    if (0x23eb3b0916 < hash) {
                        if (hash == 0x23eb3b0917) {
                            result = 0x4200000000;
                        }
                        else if (hash == 0x24b92f2d22) {
                            result = 0x2500000000;
                        }
                        else {
                            if (hash != 0x24c5f41f55) {
                                return 0;
                            }
                            result = 0x8000000000000000;
                        }
                        goto LAB_71026d0ccc;
                    }
                    if (hash == 0x23d632a291) {
                        result = 0x4600000000;
                        goto LAB_71026d0ccc;
                    }
                    if (hash != 0x23e1ea6f4c) {
                        return 0;
                    }
                }
                result = 0x3700000000;
            }
            else {
                if (hash < 0x262c49a549) {
                    if (hash < 0x256b10096c) {
                        if (0x25435e849f < hash) {
                            if (hash == 0x25435e84a0) {
                                result = 0x4800000000;
                            }
                            else {
                                if (hash != 0x2547e571c8) {
                                    return 0;
                                }
                                result = 0x2f00000000;
                            }
                            goto LAB_71026d0ccc;
                        }
                        if (hash != 0x24d6eee396) {
                            if (hash != 0x251f64b361) {
                                return 0;
                            }
                            result = 0x5300000000;
                            goto LAB_71026d0ccc;
                        }
                        goto LAB_71026d1aac;
                    }
                    if (0x2585a6ffec < hash) {
                        if (hash == 0x2585a6ffed) {
                            result = 0x2800000000;
                            goto LAB_71026d0ccc;
                        }
                        if (hash == 0x25da57d51a) {
                            result = 0x4900000000;
                            goto LAB_71026d0ccc;
                        }
                        if (hash != 0x25deca122a) {
                            return 0;
                        }
                        goto LAB_71026d1b44;
                    }
                    if (hash == 0x256b10096c) {
                        result = 0x3900000000;
                        goto LAB_71026d0ccc;
                    }
                    if (hash != 0x257e7b4b96) {
                        return 0;
                    }
                }
                else {
                    if (0x27a107ee26 < hash) {
                        if (hash < 0x28136c1b0e) {
                            if (hash == 0x27a107ee27) {
                                result = 0x3400000000;
                            }
                            else {
                                if (hash != 0x27f9d546cd) {
                                    return 0;
                                }
                                result = 0x3800000000;
                            }
                            goto LAB_71026d0ccc;
                        }
                        if (hash == 0x28136c1b0e) goto LAB_71026d1928;
                        if (hash == 0x2a3eef0b50) {
                            result = 0x5400000000;
                            goto LAB_71026d0ccc;
                        }
                        if (hash != 0x2ba3786d83) {
                            return 0;
                        }
LAB_71026d19e4:
                        result = 0x1c00000000;
                        goto LAB_71026d0ccc;
                    }
                    if (hash < 0x26d4d7e9ef) {
                        if (hash == 0x262c49a549) {
                            result = 0x3600000000;
                        }
                        else {
                            if (hash != 0x26540fe18d) {
                                return 0;
                            }
                            result = 0x3300000000;
                        }
                        goto LAB_71026d0ccc;
                    }
                    if (hash == 0x26d4d7e9ef) {
                        result = 0x3500000000;
                        goto LAB_71026d0ccc;
                    }
                    if (hash != 0x273be3703a) {
                        return 0;
                    }
                }
LAB_71026d1c4c:
                result = 0x2a00000000;
            }
            goto LAB_71026d0ccc;
        }
        if (0x20146ba333 < hash) {
            if (0x209bd8469d < hash) {
                if (0x20ebe35d0b < hash) {
                    if (hash < 0x212020c2cb) {
                        if (hash == 0x20ebe35d0c) {
                            result = 0x3000000000;
                        }
                        else {
                            if (hash != 0x20fe9ed417) {
                                return 0;
                            }
                            result = 0x4000000000;
                        }
                    }
                    else if (hash == 0x212020c2cb) {
                        result = 0x2c00000000;
                    }
                    else if (hash == 0x21333f7557) {
                        result = 0x1500000000;
                    }
                    else {
                        if (hash != 0x21bba1c0ca) {
                            return 0;
                        }
                        result = 0x3200000000;
                    }
                    goto LAB_71026d0ccc;
                }
                if (0x20d78fbbda < hash) {
                    if (hash == 0x20d78fbbdb) {
                        result = 0x5500000000;
                    }
                    else {
                        if (hash != 0x20dd065dc2) {
                            return 0;
                        }
                        result = 0x2900000000;
                    }
                    goto LAB_71026d0ccc;
                }
                if (hash != 0x209bd8469e) {
                    if (hash != 0x20ab1af734) {
                        return 0;
                    }
                    result = 0x5200000000;
                    goto LAB_71026d0ccc;
                }
LAB_71026d1be4:
                result = 0xc00000000;
                goto LAB_71026d0ccc;
            }
            if (hash < 0x2039a52466) {
                if (hash < 0x2028826d4b) {
                    if (hash == 0x20146ba334) {
                        result = 0x5100000000;
                    }
                    else {
                        if (hash != 0x201bbc3e12) {
                            return 0;
                        }
                        result = 0x1e00000000;
                    }
                }
                else if (hash == 0x2028826d4b) {
                    result = 0x1200000000;
                }
                else {
                    if (hash != 0x2033aee21c) {
                        return 0;
                    }
                    result = 0x2700000000;
                }
                goto LAB_71026d0ccc;
            }
            if (hash < 0x203ee4966d) {
                if (hash == 0x2039a52466) goto LAB_71026d1d1c;
                if (hash != 0x203cdb45fe) {
                    return 0;
                }
            }
            else {
                if (hash == 0x203ee4966d) goto LAB_71026d1464;
                if (hash != 0x2040e200b9) {
                    if (hash != 0x208999e481) {
                        return 0;
                    }
                    goto LAB_71026d1d3c;
                }
            }
LAB_71026d1754:
            result = 0x1f00000000;
            goto LAB_71026d0ccc;
        }
        if (hash < 0x1f4550d37f) {
            if (hash < 0x1eb513a4a5) {
                if (0x1e49c10adf < hash) {
                    if (hash == 0x1e49c10ae0) {
LAB_71026d1d2c:
                        result = 0x2200000000;
                        goto LAB_71026d0ccc;
                    }
                    if (hash != 0x1e7e74ecf4) {
                        return 0;
                    }
                    goto LAB_71026d1ae4;
                }
                if (hash != 0x1e3ae8c9f9) {
                    if (hash != 0x1e3be1c044) {
                        return 0;
                    }
                    goto LAB_71026d1d34;
                }
LAB_71026d1aac:
                result = 0x1300000000;
                goto LAB_71026d0ccc;
            }
            if (hash < 0x1f1d32e6fb) {
                if (hash == 0x1eb513a4a5) {
                    result = 0x3b00000000;
                }
                else {
                    if (hash != 0x1eefe69e67) {
                        return 0;
                    }
                    result = 0x4100000000;
                }
                goto LAB_71026d0ccc;
            }
            if (hash == 0x1f1d32e6fb) {
                result = 0x2600000000;
                goto LAB_71026d0ccc;
            }
            result = 0x2d85f02b;
        }
        else {
            if (hash < 0x1fd0532c69) {
                if (0x1f7d633a34 < hash) {
                    if (hash == 0x1f7d633a35) {
                        result = 0x1400000000;
                        goto LAB_71026d0ccc;
                    }
                    if (hash != 0x1fbb4dec79) {
                        return 0;
                    }
                    goto LAB_71026d1c1c;
                }
                if (hash != 0x1f4550d37f) {
                    if (hash != 0x1f6cd6c486) {
                        return 0;
                    }
LAB_71026d1464:
                    result = 0x2b00000000;
                    goto LAB_71026d0ccc;
                }
                goto LAB_71026d1754;
            }
            if (0x1ffc091e00 < hash) {
                if (hash == 0x1ffc091e01) {
                    result = 0x2100000000;
                }
                else if (hash == 0x2005388c3e) {
                    result = 0x1d00000000;
                }
                else {
                    if (hash != 0x201090b53b) {
                        return 0;
                    }
                    result = 0x3e00000000;
                }
                goto LAB_71026d0ccc;
            }
            if (hash == 0x1fd0532c69) goto LAB_71026d1adc;
            result = 0xf3d0c1f7;
        }
        if (hash != (result | 0x1f00000000)) {
            return 0;
        }
    }
LAB_71026d1cac:
    result = 0x100000000;
LAB_71026d0ccc:
    return result | 1;
}

// 0x71029015b0
u64 FUN_71029015b0(u8 *param_1, u8 *param_2)
{
    u64 result;
    u32 type_tag;
    u64 hash;

    type_tag = (u32)(u8)*param_2;
    if (type_tag - 1 < 7) {
        switch(type_tag) {
        case 1:
        case 3:
            result = (u64)(u8)param_2[1] << 0x20;
            break;
        case 2:
            result = (s64)(char)param_2[1] << 0x20;
            break;
        case 4:
            result = (s64)*(s16 *)(param_2 + 1) << 0x20;
            break;
        case 5:
            result = (u64)*(u16 *)(param_2 + 1) << 0x20;
            break;
        case 6:
        case 7:
            result = (u64)*(u32 *)(param_2 + 1) << 0x20;
            break;
        default:
            result = 0;
        }
        goto LAB_71029027e8;
    }
    if (type_tag != 9) {
        return 0;
    }
    hash = *(u64 *)(*(s64 *)(param_1 + 0x20) + (s64)*(s32 *)(param_2 + 1) * 8) & 0xffffffffff;
    if (0x1e1bc21502 < hash) {
        if (hash < 0x21333f7557) {
            if (0x1ffc091e00 < hash) {
                if (hash < 0x203ee4966d) {
                    if (hash < 0x2028826d4b) {
                        if (hash < 0x201090b53b) {
                            if (hash == 0x1ffc091e01) {
                                result = 0x2100000000;
                            }
                            else {
                                if (hash != 0x2005388c3e) {
                                    return 0;
                                }
                                result = 0x1d00000000;
                            }
                        }
                        else if (hash == 0x201090b53b) {
                            result = 0x3e00000000;
                        }
                        else {
                            if (hash != 0x201bbc3e12) {
                                return 0;
                            }
                            result = 0x1e00000000;
                        }
                        goto LAB_71029027e8;
                    }
                    if (hash < 0x2039a52466) {
                        if (hash == 0x2028826d4b) {
                            result = 0x1200000000;
                        }
                        else {
                            if (hash != 0x2033aee21c) {
                                return 0;
                            }
                            result = 0x2700000000;
                        }
                        goto LAB_71029027e8;
                    }
                    if (hash == 0x2039a52466) goto LAB_71029026e4;
                    result = 0x3cdb45fe;
                }
                else {
                    if (0x20dd065dc1 < hash) {
                        if (hash < 0x20fe9ed417) {
                            if (hash == 0x20dd065dc2) {
                                result = 0x2900000000;
                            }
                            else {
                                if (hash != 0x20ebe35d0c) {
                                    return 0;
                                }
                                result = 0x3000000000;
                            }
                        }
                        else if (hash == 0x20fe9ed417) {
                            result = 0x4000000000;
                        }
                        else {
                            if (hash != 0x212020c2cb) {
                                return 0;
                            }
                            result = 0x2c00000000;
                        }
                        goto LAB_71029027e8;
                    }
                    if (0x208999e480 < hash) {
                        if (hash == 0x208999e481) goto LAB_7102902494;
                        if (hash != 0x209bd8469e) {
                            return 0;
                        }
LAB_7102902398:
                        result = 0xc00000000;
                        goto LAB_71029027e8;
                    }
                    if (hash == 0x203ee4966d) goto LAB_71029022d8;
                    result = 0x40e200b9;
                }
                if (hash != (result | 0x2000000000)) {
                    return 0;
                }
LAB_71029025b4:
                result = 0x1f00000000;
                goto LAB_71029027e8;
            }
            if (0x1f1d32e6fa < hash) {
                if (hash < 0x1f7d633a35) {
                    if (0x1f4550d37e < hash) {
                        if (hash == 0x1f4550d37f) goto LAB_71029025b4;
                        if (hash != 0x1f6cd6c486) {
                            return 0;
                        }
LAB_71029022d8:
                        result = 0x2b00000000;
                        goto LAB_71029027e8;
                    }
                    if (hash == 0x1f1d32e6fb) {
                        result = 0x2600000000;
                        goto LAB_71029027e8;
                    }
                    result = 0x2d85f02b;
                }
                else {
                    if (hash < 0x1fd0532c69) {
                        if (hash == 0x1f7d633a35) {
                            result = 0x1400000000;
                            goto LAB_71029027e8;
                        }
                        if (hash != 0x1fbb4dec79) {
                            return 0;
                        }
                        goto LAB_7102902684;
                    }
                    if (hash == 0x1fd0532c69) goto LAB_71029025ec;
                    result = 0xf3d0c1f7;
                }
                if (hash != (result | 0x1f00000000)) {
                    return 0;
                }
                goto LAB_71029025e4;
            }
            if (0x1e49c10adf < hash) {
                if (0x1eb513a4a4 < hash) {
                    if (hash == 0x1eb513a4a5) {
                        result = 0x3b00000000;
                    }
                    else {
                        if (hash != 0x1eefe69e67) {
                            return 0;
                        }
                        result = 0x4100000000;
                    }
                    goto LAB_71029027e8;
                }
                if (hash == 0x1e49c10ae0) goto LAB_7102902464;
                if (hash != 0x1e7e74ecf4) {
                    return 0;
                }
                goto LAB_71029025ac;
            }
            if (hash < 0x1e3ae8c9f9) {
                if (hash != 0x1e1bc21503) {
                    if (hash != 0x1e20ed33da) {
                        return 0;
                    }
                    result = 0x2e00000000;
                    goto LAB_71029027e8;
                }
LAB_710290261c:
                result = 0x3d00000000;
                goto LAB_71029027e8;
            }
            if (hash != 0x1e3ae8c9f9) {
                if (hash != 0x1e3be1c044) {
                    return 0;
                }
                goto LAB_7102902188;
            }
LAB_71029026f4:
            result = 0x1300000000;
        }
        else {
            if (hash < 0x24c5f41f55) {
                if (hash < 0x234f3bf32b) {
                    if (hash < 0x222bb85667) {
                        if (hash < 0x2216ca77c1) {
                            if (hash == 0x21333f7557) {
                                result = 0x1500000000;
                            }
                            else {
                                if (hash != 0x21bba1c0ca) {
                                    return 0;
                                }
                                result = 0x3200000000;
                            }
                        }
                        else if (hash == 0x2216ca77c1) {
                            result = 0x2d00000000;
                        }
                        else {
                            if (hash != 0x222a600352) {
                                return 0;
                            }
                            result = 0x3a00000000;
                        }
                        goto LAB_71029027e8;
                    }
                    if (0x230535683a < hash) {
                        if (hash == 0x230535683b) {
                            result = 0x4400000000;
                        }
                        else {
                            if (hash != 0x23415d63a4) {
                                return 0;
                            }
                            result = 0x2400000000;
                        }
                        goto LAB_71029027e8;
                    }
                    if (hash == 0x222bb85667) goto LAB_7102901fc8;
                    if (hash != 0x22d66e8a25) {
                        return 0;
                    }
                }
                else {
                    if (hash < 0x23d632a291) {
                        if (hash < 0x2374dfc186) {
                            if (hash == 0x234f3bf32b) {
                                result = 0x4500000000;
                            }
                            else {
                                if (hash != 0x23723258ad) {
                                    return 0;
                                }
                                result = 0x4300000000;
                            }
                        }
                        else if (hash == 0x2374dfc186) {
                            result = 0x3100000000;
                        }
                        else {
                            if (hash != 0x23a1359207) {
                                return 0;
                            }
                            result = 0x4700000000;
                        }
                        goto LAB_71029027e8;
                    }
                    if (0x23eb3b0916 < hash) {
                        if (hash == 0x23eb3b0917) {
                            result = 0x4200000000;
                        }
                        else {
                            if (hash != 0x24b92f2d22) {
                                return 0;
                            }
                            result = 0x2500000000;
                        }
                        goto LAB_71029027e8;
                    }
                    if (hash == 0x23d632a291) {
                        result = 0x4600000000;
                        goto LAB_71029027e8;
                    }
                    if (hash != 0x23e1ea6f4c) {
                        return 0;
                    }
                }
                result = 0x3700000000;
                goto LAB_71029027e8;
            }
            if (hash < 0x25deca122a) {
                if (hash < 0x256b10096c) {
                    if (0x25435e849f < hash) {
                        if (hash == 0x25435e84a0) {
                            result = 0x4800000000;
                        }
                        else {
                            if (hash != 0x2547e571c8) {
                                return 0;
                            }
                            result = 0x2f00000000;
                        }
                        goto LAB_71029027e8;
                    }
                    if (hash == 0x24c5f41f55) {
                        result = 0x8000000000000000;
                        goto LAB_71029027e8;
                    }
                    if (hash != 0x24d6eee396) {
                        return 0;
                    }
                    goto LAB_71029026f4;
                }
                if (0x2585a6ffec < hash) {
                    if (hash == 0x2585a6ffed) {
                        result = 0x2800000000;
                    }
                    else {
                        if (hash != 0x25da57d51a) {
                            return 0;
                        }
                        result = 0x4900000000;
                    }
                    goto LAB_71029027e8;
                }
                if (hash == 0x256b10096c) {
                    result = 0x3900000000;
                    goto LAB_71029027e8;
                }
                if (hash != 0x257e7b4b96) {
                    return 0;
                }
            }
            else {
                if (hash < 0x273be3703a) {
                    if (0x26540fe18c < hash) {
                        if (hash == 0x26540fe18d) {
                            result = 0x3300000000;
                        }
                        else {
                            if (hash != 0x26d4d7e9ef) {
                                return 0;
                            }
                            result = 0x3500000000;
                        }
                        goto LAB_71029027e8;
                    }
                    if (hash != 0x25deca122a) {
                        if (hash != 0x262c49a549) {
                            return 0;
                        }
                        result = 0x3600000000;
                        goto LAB_71029027e8;
                    }
                    goto LAB_7102902308;
                }
                if (0x27f9d546cc < hash) {
                    if (hash == 0x27f9d546cd) {
                        result = 0x3800000000;
                        goto LAB_71029027e8;
                    }
                    if (hash == 0x28136c1b0e) goto LAB_710290254c;
                    if (hash != 0x2ba3786d83) {
                        return 0;
                    }
LAB_7102901fc8:
                    result = 0x1c00000000;
                    goto LAB_71029027e8;
                }
                if (hash != 0x273be3703a) {
                    if (hash != 0x27a107ee27) {
                        return 0;
                    }
                    result = 0x3400000000;
                    goto LAB_71029027e8;
                }
            }
LAB_71029023c8:
            result = 0x2a00000000;
        }
        goto LAB_71029027e8;
    }
    result = 0;
    if (hash < 0x1ab95511b5) {
        if (hash < 0x1854e3a50a) {
            if (hash < 0x14d9ca6a0b) {
                if (0x140b342853 < hash) {
                    if (0x14aecd5a9c < hash) {
                        if (hash != 0x14aecd5a9d) {
                            if (hash != 0x14d45c28b1) {
                                return 0;
                            }
                            goto LAB_7102902624;
                        }
LAB_71029025e4:
                        result = 0x100000000;
                        goto LAB_71029027e8;
                    }
                    if (hash != 0x140b342854) {
                        if (hash != 0x1454c267fe) {
                            return 0;
                        }
                        goto LAB_71029027e8;
                    }
                    goto LAB_7102902368;
                }
                if (hash < 0x12464ef7c0) {
                    if (hash != 0x11c8f620e5) {
                        if (hash != 0x11cf9be4fc) {
                            return 0;
                        }
                        goto LAB_710290224c;
                    }
                    goto LAB_71029025ac;
                }
                if (hash != 0x12464ef7c0) {
                    if (hash != 0x136a7c7544) {
                        return 0;
                    }
                    goto LAB_71029027e8;
                }
            }
            else if (hash < 0x15f087af49) {
                if (0x15010dd11b < hash) {
                    if (hash != 0x15010dd11c) {
                        if (hash != 0x154b6b24ab) {
                            return 0;
                        }
                        goto LAB_71029025ec;
                    }
LAB_71029025ac:
                    result = 0x300000000;
                    goto LAB_71029027e8;
                }
                if (hash != 0x14d9ca6a0b) {
                    if (hash != 0x14e734bf1f) {
                        return 0;
                    }
                    goto LAB_7102902368;
                }
            }
            else {
                if (0x1777723c77 < hash) {
                    if (hash == 0x1777723c78) goto LAB_71029025b4;
                    if (hash != 0x1798a00332) {
                        return 0;
                    }
                    goto LAB_71029025ac;
                }
                if (hash == 0x15f087af49) goto LAB_71029025e4;
                if (hash != 0x1762df116c) {
                    return 0;
                }
            }
        }
        else if (hash < 0x19d5c78f1a) {
            if (hash < 0x18c8e98293) {
                if (hash < 0x187d583698) {
                    if (hash != 0x1854e3a50a) {
                        if (hash != 0x185be87ea0) {
                            return 0;
                        }
                        goto LAB_7102902398;
                    }
LAB_7102902368:
                    result = 0x500000000;
                    goto LAB_71029027e8;
                }
                if (hash == 0x187d583698) goto LAB_71029026fc;
                if (hash != 0x189ef7c5e8) {
                    return 0;
                }
LAB_710290224c:
                result = 0x400000000;
                goto LAB_71029027e8;
            }
            if (hash < 0x1920ee5d2e) {
                if (hash == 0x18c8e98293) {
                    result = 0xe00000000;
                    goto LAB_71029027e8;
                }
                if (hash != 0x1900a16150) {
                    return 0;
                }
                goto LAB_7102902308;
            }
            if (hash == 0x1920ee5d2e) goto LAB_7102902624;
            if (hash != 0x199e7bc742) {
                return 0;
            }
        }
        else {
            if (hash < 0x1a130b6ef1) {
                if (0x19ff3e1887 < hash) {
                    if (hash == 0x19ff3e1888) goto LAB_71029027e8;
                    if (hash != 0x1a042cd3ef) {
                        return 0;
                    }
                    goto LAB_7102902368;
                }
                if (hash != 0x19d5c78f1a) {
                    if (hash != 0x19d8701188) {
                        return 0;
                    }
LAB_71029025ec:
                    result = 0x800000000;
                    goto LAB_71029027e8;
                }
                goto LAB_710290224c;
            }
            if (hash < 0x1a4035e5d8) {
                if (hash != 0x1a130b6ef1) {
                    if (hash != 0x1a3cd9a172) {
                        return 0;
                    }
LAB_7102902704:
                    result = 0x600000000;
                    goto LAB_71029027e8;
                }
LAB_71029026fc:
                result = 0x900000000;
                goto LAB_71029027e8;
            }
            if (hash == 0x1a4035e5d8) {
                result = 0xa00000000;
                goto LAB_71029027e8;
            }
            if (hash != 0x1a5612f412) {
                return 0;
            }
        }
    }
    else {
        if (hash < 0x1c807afd3d) {
            if (hash < 0x1beac53520) {
                if (hash < 0x1afddcec06) {
                    if (hash < 0x1ac4d90a73) {
                        if (hash == 0x1ab95511b5) goto LAB_71029023d0;
                        if (hash != 0x1abf715127) {
                            return 0;
                        }
                    }
                    else if (hash != 0x1ac4d90a73) {
                        if (hash != 0x1ae13e9305) {
                            return 0;
                        }
LAB_7102902188:
                        result = 0x1000000000;
                        goto LAB_71029027e8;
                    }
                    goto LAB_71029025e4;
                }
                if (hash < 0x1b4d027a79) {
                    if (hash != 0x1afddcec06) {
                        if (hash != 0x1b19308703) {
                            return 0;
                        }
                        goto LAB_710290270c;
                    }
                }
                else if (hash != 0x1b4d027a79) {
                    if (hash != 0x1bde8ff304) {
                        return 0;
                    }
LAB_7102902494:
                    result = 0x3f00000000;
                    goto LAB_71029027e8;
                }
            }
            else {
                if (0x1c0eb10be2 < hash) {
                    if (hash < 0x1c3cd3e508) {
                        if (hash != 0x1c0eb10be3) {
                            if (hash != 0x1c2f7a650c) {
                                return 0;
                            }
                            goto LAB_7102901fc8;
                        }
                    }
                    else if (hash != 0x1c3cd3e508) {
                        if (hash != 0x1c4627fa8f) {
                            return 0;
                        }
                        goto LAB_710290261c;
                    }
LAB_7102902624:
                    result = 0x700000000;
                    goto LAB_71029027e8;
                }
                if (0x1c013682e1 < hash) {
                    if (hash == 0x1c013682e2) goto LAB_7102902704;
                    if (hash != 0x1c0ae27e24) {
                        return 0;
                    }
LAB_7102902308:
                    result = 0xb00000000;
                    goto LAB_71029027e8;
                }
                if (hash == 0x1beac53520) {
                    result = 0x2300000000;
                    goto LAB_71029027e8;
                }
                if (hash != 0x1bedba73cf) {
                    return 0;
                }
            }
            goto LAB_71029025ac;
        }
        if (hash < 0x1d6c35808e) {
            if (hash < 0x1ce0f1d8ec) {
                if (hash < 0x1cc22d24d3) {
                    if (hash == 0x1c807afd3d) goto LAB_71029027e8;
                    if (hash != 0x1c89c9c2c5) {
                        return 0;
                    }
                    goto LAB_7102902684;
                }
                if (hash != 0x1cc22d24d3) {
                    if (hash != 0x1cd91cdd73) {
                        return 0;
                    }
                    result = 0x1100000000;
                    goto LAB_71029027e8;
                }
            }
            else {
                if (0x1d0f3340a0 < hash) {
                    if (hash != 0x1d0f3340a1) {
                        if (hash != 0x1d600d17ea) {
                            return 0;
                        }
LAB_710290254c:
                        result = 0x1700000000;
                        goto LAB_71029027e8;
                    }
LAB_710290270c:
                    result = 0xf00000000;
                    goto LAB_71029027e8;
                }
                if (hash != 0x1ce0f1d8ec) {
                    if (hash != 0x1cf08c9a53) {
                        return 0;
                    }
                    result = 0x8000000100000000;
                    goto LAB_71029027e8;
                }
            }
            goto LAB_710290224c;
        }
        if (hash < 0x1da8d32364) {
            if (0x1d7808e1b9 < hash) {
                if (hash == 0x1d7808e1ba) {
                    result = 0x8000000300000000;
                    goto LAB_71029027e8;
                }
                if (hash != 0x1da727dda7) {
                    return 0;
                }
                goto LAB_71029023c8;
            }
            if (hash != 0x1d6c35808e) {
                if (hash != 0x1d707084a0) {
                    return 0;
                }
LAB_7102902464:
                result = 0x2200000000;
                goto LAB_71029027e8;
            }
LAB_71029023d0:
            result = 0xd00000000;
            goto LAB_71029027e8;
        }
        if (0x1de5509805 < hash) {
            if (hash == 0x1de5509806) {
                result = 0x3c00000000;
                goto LAB_71029027e8;
            }
            if (hash != 0x1ded09afe3) {
                return 0;
            }
LAB_71029026e4:
            result = 0x2000000000;
            goto LAB_71029027e8;
        }
        if (hash != 0x1da8d32364) {
            if (hash != 0x1dcafa394c) {
                return 0;
            }
            goto LAB_7102902308;
        }
    }
LAB_7102902684:
    result = 0x200000000;
LAB_71029027e8:
    return result | 1;
}
