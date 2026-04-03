#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7100 address range, batch d4-002
// Pool-d worker: auto-generated from Ghidra decompilation
// These are state-machine / animation-frame dispatch functions

// ---- External declarations -----------------------------------------------

// External data tables
extern u8 DAT_71045378d0;
extern u8 DAT_71044692f0;
extern u8 DAT_7104537890;
extern u8 DAT_7104538d70;
extern u8 DAT_7104467f70;
extern u8 DAT_71045497f0;

// ---- Functions ---------------------------------------------------------------

// 0x71002f0f70 — motion-type state remapper: translate param_2 motion ID by active motion type
s32 FUN_71002f0f70(s64 *param_1, s32 param_2)
{
    u32 uVar1;
    s32 iVar2;
    u8 bVar3;
    s32 iVar4;
    s32 iVar5;
    s32 iVar6;

    switch(*(u32 *)(*param_1 + 0xc04)) {
    case 0x1c:
        if ((*(u8 *)(param_1[1] + 0x68) >> 1 & 1) == 0) {
            return param_2;
        }
        break;
    default:
        switch(param_2) {
        case 0x6038:
            iVar5 = *(s32 *)(param_1[1] + 0x238);
            if (iVar5 == 0) {
                return 0x6038;
            }
            iVar6 = 0x6049;
            break;
        case 0x6039:
            iVar5 = *(s32 *)(param_1[1] + 0x23c);
            if (iVar5 == 0) {
                return 0x6039;
            }
            iVar6 = 0x604a;
            break;
        case 0x603a:
            iVar5 = *(s32 *)(param_1[1] + 0x240);
            if (iVar5 == 0) {
                return 0x603a;
            }
            iVar6 = 0x604b;
            break;
        case 0x603b:
            iVar5 = *(s32 *)(param_1[1] + 0x244);
            if (iVar5 == 0) {
                return 0x603b;
            }
            iVar6 = 0x604c;
            break;
        case 0x603c:
        case 0x603d:
        case 0x603e:
        case 0x603f:
        case 0x6040:
        case 0x6041:
        case 0x6042:
        case 0x6043:
        case 0x6044:
        case 0x6045:
            return param_2;
        case 0x6046:
            iVar5 = *(s32 *)(param_1[1] + 0x238);
            if (iVar5 == 0) {
                return 0x6046;
            }
            iVar6 = 0x604d;
            break;
        case 0x6047:
            iVar5 = *(s32 *)(param_1[1] + 0x23c);
            if (iVar5 == 0) {
                return 0x6047;
            }
            iVar6 = 0x604e;
            break;
        case 0x6048:
            iVar5 = *(s32 *)(param_1[1] + 0x240);
            if (iVar5 == 0) {
                return 0x6048;
            }
            iVar6 = 0x604f;
            break;
        case 0x6049:
            iVar5 = *(s32 *)(param_1[1] + 0x244);
            if (iVar5 == 0) {
                return 0x6049;
            }
            iVar6 = 0x6050;
            break;
        default:
            return param_2;
        }
        return iVar6 + iVar5 * 8;
    case 0x21:
        if ((*(u8 *)(param_1[1] + 0x68) >> 1 & 1) == 0) {
            return param_2;
        }
        break;
    case 0x30:
    case 0x46:
        if ((*(u8 *)(param_1[1] + 0x68) & 1) == 0) {
            return param_2;
        }
        goto LAB_71002f1040;
    case 0x34:
        if ((*(u8 *)(param_1[1] + 0x68) & 1) == 0) {
            return param_2;
        }
LAB_71002f1040:
        iVar4 = 0x6051;
        iVar5 = 0x6038;
        bVar3 = param_2 == 0x6046;
        iVar6 = 0x6055;
        goto LAB_71002f1140;
    case 0x3c:
    case 0x3d:
        iVar5 = param_2 + -0x20;
        if (3 < param_2 - 0x6071U) {
            iVar5 = param_2;
        }
        return iVar5;
    case 0x53:
        iVar5 = 0x6051;
        switch(param_2) {
        case 0x6101:
            goto switchD_71002f1000_caseD_603c;
        case 0x6102:
            return 0x6052;
        case 0x6103:
        case 0x6104:
        case 0x6105:
        case 0x6106:
        case 0x6107:
        case 0x6108:
        case 0x6109:
        case 0x610a:
        case 0x610b:
        case 0x610c:
        case 0x610d:
        case 0x610e:
        case 0x610f:
        case 0x6110:
            return param_2;
        case 0x6111:
            return 0x6053;
        case 0x6112:
            return 0x6054;
        default:
            return param_2;
        }
    case 0x55:
        uVar1 = param_2 - 0x6121;
        if (0x15 < uVar1) {
            return param_2;
        }
        iVar5 = param_2;
        if ((0x3f00ffU >> (u64)(uVar1 & 0x1f) & 1) == 0) {
switchD_71002f1000_caseD_603c:
            return iVar5;
        }
        return *(s32 *)(&DAT_71045378d0 + (s64)(s32)uVar1 * 4);
    case 0x56:
        iVar5 = 0x6141;
        iVar6 = 0x6151;
        goto LAB_71002f1138;
    case 0x57:
        iVar5 = 0x6051;
        switch(param_2) {
        case 0x6161:
            return 0x6053;
        case 0x6162:
            return 0x6054;
        case 0x6163:
        case 0x6164:
        case 0x6165:
        case 0x6166:
        case 0x6167:
        case 0x6168:
        case 0x6169:
        case 0x616a:
        case 0x616b:
        case 0x616c:
        case 0x616d:
        case 0x616e:
        case 0x616f:
        case 0x6170:
            return param_2;
        case 0x6171:
            goto switchD_71002f1000_caseD_603c;
        case 0x6172:
            return 0x6052;
        case 0x6173:
            return 0x6055;
        case 0x6174:
            return 0x6056;
        case 0x6175:
            return 0x6057;
        case 0x6176:
            return 0x6058;
        case 0x6177:
            return 0x6059;
        default:
            return param_2;
        }
    case 0x58:
        iVar5 = 0x6181;
        iVar6 = 0x6191;
LAB_71002f1138:
        iVar4 = 0x6052;
        bVar3 = param_2 == iVar6;
        iVar6 = 0x6056;
        goto LAB_71002f1140;
    case 0x5c:
        iVar5 = param_2 + -0x1b0;
        if (0xf < param_2 - 0x6201U) {
            iVar5 = param_2;
        }
        return iVar5;
    }
    iVar4 = 0x6054;
    iVar5 = 0x603b;
    bVar3 = param_2 == 0x6049;
    iVar6 = 0x6058;
LAB_71002f1140:
    iVar2 = param_2;
    if (bVar3) {
        iVar2 = iVar6;
    }
    if (param_2 != iVar5) {
        iVar4 = iVar2;
    }
    return iVar4;
}

// 0x71002f14e0 — inverse state remapper: translate param_2 base motion ID by type
s32 FUN_71002f14e0(u32 param_1, s32 param_2)
{
    s32 iVar1;
    s32 iVar2;
    s32 iVar3;

    iVar2 = param_2;
    switch(param_1) {
    case 0x3c:
    case 0x3d:
        iVar2 = param_2 + 0x20;
        if (3 < param_2 - 0x6051U) {
            iVar2 = param_2;
        }
        return iVar2;
    case 0x53:
        if (param_2 - 0x6051U < 4) {
            return *(s32 *)(&DAT_71044692f0 + (s64)(s32)(param_2 - 0x6051U) * 4);
        }
        break;
    case 0x55:
        if (param_2 - 0x6051U < 0xe) {
            return *(s32 *)(&DAT_7104537890 + (s64)(s32)(param_2 - 0x6051U) * 4);
        }
        break;
    case 0x56:
        iVar2 = 0x6141;
        iVar3 = 0x6151;
        goto LAB_71002f15d0;
    case 0x57:
        if (param_2 - 0x6051U < 9) {
            return *(s32 *)(&DAT_7104538d70 + (s64)(s32)(param_2 - 0x6051U) * 4);
        }
        break;
    case 0x58:
        iVar2 = 0x6181;
        iVar3 = 0x6191;
LAB_71002f15d0:
        iVar1 = param_2;
        if (param_2 == 0x6056) {
            iVar1 = iVar3;
        }
        if (param_2 != 0x6052) {
            iVar2 = iVar1;
        }
        return iVar2;
    case 0x5c:
        iVar2 = param_2 + 0x1b0;
        if (0xf < param_2 - 0x6051U) {
            iVar2 = param_2;
        }
    }
    return iVar2;
}

// 0x71002f2820 — inverse state remapper variant: translate param_1 by motion type param_2
s32 FUN_71002f2820(s32 param_1, u32 param_2)
{
    s32 iVar1;
    u8 *puVar2;
    u32 uVar3;

    uVar3 = param_1 - 0x6091;
    if (uVar3 < 4) {
        puVar2 = &DAT_7104467f70;
LAB_71002f2838:
        iVar1 = *(s32 *)(puVar2 + (s64)(s32)uVar3 * 4);
    }
    else {
        iVar1 = param_1;
        switch(param_2) {
        case 0x3c:
        case 0x3d:
            iVar1 = param_1 + -0x20;
            if (3 < param_1 - 0x6071U) {
                iVar1 = param_1;
            }
            return iVar1;
        case 0x3e:
        case 0x3f:
        case 0x40:
        case 0x41:
        case 0x42:
        case 0x43:
        case 0x44:
        case 0x45:
        case 0x46:
        case 0x47:
        case 0x48:
        case 0x49:
        case 0x4a:
        case 0x4b:
        case 0x4c:
        case 0x4d:
        case 0x4e:
        case 0x4f:
        case 0x50:
        case 0x51:
        case 0x52:
        case 0x54:
        case 0x59:
        case 0x5a:
        case 0x5b:
            break;
        case 0x53:
            iVar1 = 0x6051;
            switch(param_1) {
            case 0x6101:
                break;
            case 0x6102:
                return 0x6052;
            case 0x6103:
            case 0x6104:
            case 0x6105:
            case 0x6106:
            case 0x6107:
            case 0x6108:
            case 0x6109:
            case 0x610a:
            case 0x610b:
            case 0x610c:
            case 0x610d:
            case 0x610e:
            case 0x610f:
            case 0x6110:
                return param_1;
            case 0x6111:
                return 0x6053;
            case 0x6112:
                return 0x6054;
            default:
                return param_1;
            }
        case 0x55:
            uVar3 = param_1 - 0x6121;
            if (0x15 < uVar3) {
                return param_1;
            }
            if ((0x3f00ffU >> (u64)(uVar3 & 0x1f) & 1) == 0) {
                return param_1;
            }
            puVar2 = &DAT_71045378d0;
            goto LAB_71002f2838;
        case 0x56:
            if (param_1 == 0x6141) {
                return 0x6052;
            }
            if (param_1 == 0x6151) {
                return 0x6056;
            }
            break;
        case 0x57:
            iVar1 = 0x6051;
            switch(param_1) {
            case 0x6161:
                return 0x6053;
            case 0x6162:
                return 0x6054;
            case 0x6163:
            case 0x6164:
            case 0x6165:
            case 0x6166:
            case 0x6167:
            case 0x6168:
            case 0x6169:
            case 0x616a:
            case 0x616b:
            case 0x616c:
            case 0x616d:
            case 0x616e:
            case 0x616f:
            case 0x6170:
                return param_1;
            case 0x6171:
                break;
            case 0x6172:
                return 0x6052;
            case 0x6173:
                return 0x6055;
            case 0x6174:
                return 0x6056;
            case 0x6175:
                return 0x6057;
            case 0x6176:
                return 0x6058;
            case 0x6177:
                return 0x6059;
            default:
                return param_1;
            }
        case 0x58:
            if (param_1 == 0x6181) {
                return 0x6052;
            }
            if (param_1 == 0x6191) {
                return 0x6056;
            }
            break;
        case 0x5c:
            iVar1 = param_1 + -0x1b0;
            if (0xf < param_1 - 0x6201U) {
                iVar1 = param_1;
            }
            return iVar1;
        default:
            return param_1;
        }
    }
    return iVar1;
}

// 0x71002f46a0 — set motion bit: update bitmask at +0x180 based on active motion type
void FUN_71002f46a0(s64 param_1, s32 param_2)
{
    u8 bVar1;
    s32 iVar2;
    u32 uVar3;
    s32 iVar5;
    u64 uVar4;

    iVar5 = param_2;
    switch(*(u32 *)(*(s64 *)(param_1 + 8) + 0x28)) {
    case 0x3c:
    case 0x3d:
        iVar5 = param_2 + -0x20;
        bVar1 = 3 < param_2 - 0x6071U;
        goto LAB_71002f4794;
    case 0x53:
        iVar2 = 0x6051;
        switch(param_2) {
        case 0x6101:
            break;
        case 0x6102:
switchD_71002f4700_caseD_6102:
            iVar2 = 0x6052;
            break;
        default:
            goto switchD_71002f46c4_caseD_3e;
        case 0x6111:
switchD_71002f4700_caseD_6111:
            iVar2 = 0x6053;
            break;
        case 0x6112:
switchD_71002f4700_caseD_6112:
            iVar2 = 0x6054;
        }
        goto switchD_71002f4700_caseD_6101;
    case 0x55:
        uVar3 = param_2 - 0x6121;
        if ((uVar3 < 0x16) && ((0x3f00ffU >> (u64)(uVar3 & 0x1f) & 1) != 0)) {
            iVar5 = *(s32 *)(&DAT_71045378d0 + (s64)(s32)uVar3 * 4);
        }
        break;
    case 0x57:
        iVar2 = 0x6051;
        switch(param_2) {
        case 0x6161:
            goto switchD_71002f4700_caseD_6111;
        case 0x6162:
            goto switchD_71002f4700_caseD_6112;
        default:
            goto switchD_71002f46c4_caseD_3e;
        case 0x6171:
            break;
        case 0x6172:
            goto switchD_71002f4700_caseD_6102;
        case 0x6173:
            iVar2 = 0x6055;
            break;
        case 0x6174:
switchD_71002f4758_caseD_6174:
            iVar2 = 0x6056;
            break;
        case 0x6175:
            iVar2 = 0x6057;
            break;
        case 0x6176:
            iVar2 = 0x6058;
            break;
        case 0x6177:
            iVar2 = 0x6059;
        }
        goto switchD_71002f4700_caseD_6101;
    case 0x58:
        if (param_2 == 0x6181) goto switchD_71002f4700_caseD_6102;
        if (param_2 == 0x6191) goto switchD_71002f4758_caseD_6174;
        break;
    case 0x5c:
        iVar5 = param_2 + -0x1b0;
        bVar1 = 0xf < param_2 - 0x6201U;
LAB_71002f4794:
        if (bVar1) {
            iVar5 = param_2;
        }
    }
switchD_71002f46c4_caseD_3e:
    uVar3 = iVar5 - 0x6031;
    if (0xe < uVar3) {
        if (iVar5 - 0x6041U < 0xf) {
            uVar3 = iVar5 - 0x6034;
        }
        else {
            iVar2 = iVar5;
            if (0x17 < iVar5 - 0x6051U) {
                uVar4 = 0;
                goto LAB_71002f4818;
            }
switchD_71002f4700_caseD_6101:
            uVar3 = iVar2 - 0x603b;
        }
    }
    uVar4 = (u64)(s32)uVar3;
LAB_71002f4818:
    *(u64 *)(param_1 + 0x180) = *(u64 *)(param_1 + 0x180) | 1L << (uVar4 & 0x3f);
}

// 0x71002f5770 — clear motion bit: clear bitmask at +0x180 based on active motion type
void FUN_71002f5770(s64 param_1, s32 param_2)
{
    u8 bVar1;
    s32 iVar2;
    u32 uVar3;
    s32 iVar5;
    u64 uVar4;

    iVar5 = param_2;
    switch(*(u32 *)(*(s64 *)(param_1 + 8) + 0x28)) {
    case 0x3c:
    case 0x3d:
        iVar5 = param_2 + -0x20;
        bVar1 = 3 < param_2 - 0x6071U;
        goto LAB_71002f5864;
    case 0x53:
        iVar2 = 0x6051;
        switch(param_2) {
        case 0x6101:
            break;
        case 0x6102:
switchD_71002f57d0_caseD_6102:
            iVar2 = 0x6052;
            break;
        default:
            goto switchD_71002f5794_caseD_3e;
        case 0x6111:
switchD_71002f57d0_caseD_6111:
            iVar2 = 0x6053;
            break;
        case 0x6112:
switchD_71002f57d0_caseD_6112:
            iVar2 = 0x6054;
        }
        goto switchD_71002f57d0_caseD_6101;
    case 0x55:
        uVar3 = param_2 - 0x6121;
        if ((uVar3 < 0x16) && ((0x3f00ffU >> (u64)(uVar3 & 0x1f) & 1) != 0)) {
            iVar5 = *(s32 *)(&DAT_71045378d0 + (s64)(s32)uVar3 * 4);
        }
        break;
    case 0x57:
        iVar2 = 0x6051;
        switch(param_2) {
        case 0x6161:
            goto switchD_71002f57d0_caseD_6111;
        case 0x6162:
            goto switchD_71002f57d0_caseD_6112;
        default:
            goto switchD_71002f5794_caseD_3e;
        case 0x6171:
            break;
        case 0x6172:
            goto switchD_71002f57d0_caseD_6102;
        case 0x6173:
            iVar2 = 0x6055;
            break;
        case 0x6174:
switchD_71002f5828_caseD_6174:
            iVar2 = 0x6056;
            break;
        case 0x6175:
            iVar2 = 0x6057;
            break;
        case 0x6176:
            iVar2 = 0x6058;
            break;
        case 0x6177:
            iVar2 = 0x6059;
        }
        goto switchD_71002f57d0_caseD_6101;
    case 0x58:
        if (param_2 == 0x6181) goto switchD_71002f57d0_caseD_6102;
        if (param_2 == 0x6191) goto switchD_71002f5828_caseD_6174;
        break;
    case 0x5c:
        iVar5 = param_2 + -0x1b0;
        bVar1 = 0xf < param_2 - 0x6201U;
LAB_71002f5864:
        if (bVar1) {
            iVar5 = param_2;
        }
    }
switchD_71002f5794_caseD_3e:
    uVar3 = iVar5 - 0x6031;
    if (0xe < uVar3) {
        if (iVar5 - 0x6041U < 0xf) {
            uVar3 = iVar5 - 0x6034;
        }
        else {
            iVar2 = iVar5;
            if (0x17 < iVar5 - 0x6051U) {
                uVar4 = 0;
                goto LAB_71002f58e8;
            }
switchD_71002f57d0_caseD_6101:
            uVar3 = iVar2 - 0x603b;
        }
    }
    uVar4 = (u64)(s32)uVar3;
LAB_71002f58e8:
    *(u64 *)(param_1 + 0x180) =
         *(u64 *)(param_1 + 0x180) & (1L << (uVar4 & 0x3f) ^ 0xffffffffffffffffU);
}

// 0x7100314d50 — is-grounded-flag: return true if param_1 matches a known grounded motion ID
u8 FUN_7100314d50(u32 param_1)
{
    switch(param_1) {
    case 0:
    case 3:
    case 0x11:
    case 0x23:
    case 0x32:
    case 0x3e:
    case 0x53:
    case 0x56:
    case 0x59:
    case 0x5f:
    case 0x62:
    case 0x65:
    case 0x68:
    case 0x6b:
    case 0x6e:
    case 0x71:
    case 0x7d:
    case 0x89:
    case 0x8c:
    case 0x9e:
    case 0xad:
    case 0xb0:
    case 0xb6:
    case 0xce:
    case 0xd1:
    case 0x101:
    case 0x12e:
    case 0x14c:
    case 0x14f:
    case 0x155:
    case 0x158:
    case 0x15b:
    case 0x15c:
    case 0x15f:
    case 0x163:
    case 0x166:
    case 0x169:
        return true;
    }
    if (param_1 < 0x16c) {
        return (&DAT_71045497f0)[(s64)(s32)param_1 * 0x12] - 1 < 2;
    }
    return false;
}
