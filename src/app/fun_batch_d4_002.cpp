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
    u32 offset;
    s32 mapped_id;
    u8 is_alternate;
    s32 default_id;
    s32 motion_id;
    s32 remap_base;

    switch(*(u32 *)(*param_1 + 0xc04)) {
    case 0x1c:
        if ((*(u8 *)(param_1[1] + 0x68) >> 1 & 1) == 0) {
            return param_2;
        }
        break;
    default:
        switch(param_2) {
        case 0x6038:
            motion_id = *(s32 *)(param_1[1] + 0x238);
            if (motion_id == 0) {
                return 0x6038;
            }
            remap_base = 0x6049;
            break;
        case 0x6039:
            motion_id = *(s32 *)(param_1[1] + 0x23c);
            if (motion_id == 0) {
                return 0x6039;
            }
            remap_base = 0x604a;
            break;
        case 0x603a:
            motion_id = *(s32 *)(param_1[1] + 0x240);
            if (motion_id == 0) {
                return 0x603a;
            }
            remap_base = 0x604b;
            break;
        case 0x603b:
            motion_id = *(s32 *)(param_1[1] + 0x244);
            if (motion_id == 0) {
                return 0x603b;
            }
            remap_base = 0x604c;
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
            motion_id = *(s32 *)(param_1[1] + 0x238);
            if (motion_id == 0) {
                return 0x6046;
            }
            remap_base = 0x604d;
            break;
        case 0x6047:
            motion_id = *(s32 *)(param_1[1] + 0x23c);
            if (motion_id == 0) {
                return 0x6047;
            }
            remap_base = 0x604e;
            break;
        case 0x6048:
            motion_id = *(s32 *)(param_1[1] + 0x240);
            if (motion_id == 0) {
                return 0x6048;
            }
            remap_base = 0x604f;
            break;
        case 0x6049:
            motion_id = *(s32 *)(param_1[1] + 0x244);
            if (motion_id == 0) {
                return 0x6049;
            }
            remap_base = 0x6050;
            break;
        default:
            return param_2;
        }
        return remap_base + motion_id * 8;
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
        goto remap_alternate;
    case 0x34:
        if ((*(u8 *)(param_1[1] + 0x68) & 1) == 0) {
            return param_2;
        }
remap_alternate:
        default_id = 0x6051;
        motion_id = 0x6038;
        is_alternate = param_2 == 0x6046;
        remap_base = 0x6055;
        goto select_result;
    case 0x3c:
    case 0x3d:
        motion_id = param_2 + -0x20;
        if (3 < param_2 - 0x6071U) {
            motion_id = param_2;
        }
        return motion_id;
    case 0x53:
        motion_id = 0x6051;
        switch(param_2) {
        case 0x6101:
            goto passthrough;
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
        offset = param_2 - 0x6121;
        if (0x15 < offset) {
            return param_2;
        }
        motion_id = param_2;
        if ((0x3f00ffU >> (u64)(offset & 0x1f) & 1) == 0) {
passthrough:
            return motion_id;
        }
        return *(s32 *)(&DAT_71045378d0 + (s64)(s32)offset * 4);
    case 0x56:
        motion_id = 0x6141;
        remap_base = 0x6151;
        goto setup_alternate;
    case 0x57:
        motion_id = 0x6051;
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
            goto passthrough;
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
        motion_id = 0x6181;
        remap_base = 0x6191;
setup_alternate:
        default_id = 0x6052;
        is_alternate = param_2 == remap_base;
        remap_base = 0x6056;
        goto select_result;
    case 0x5c:
        motion_id = param_2 + -0x1b0;
        if (0xf < param_2 - 0x6201U) {
            motion_id = param_2;
        }
        return motion_id;
    }
    default_id = 0x6054;
    motion_id = 0x603b;
    is_alternate = param_2 == 0x6049;
    remap_base = 0x6058;
select_result:
    mapped_id = param_2;
    if (is_alternate) {
        mapped_id = remap_base;
    }
    if (param_2 != motion_id) {
        default_id = mapped_id;
    }
    return default_id;
}

// 0x71002f14e0 — inverse state remapper: translate param_2 base motion ID by type
s32 FUN_71002f14e0(u32 param_1, s32 param_2)
{
    s32 result;
    s32 mapped_id;
    s32 alternate_id;

    mapped_id = param_2;
    switch(param_1) {
    case 0x3c:
    case 0x3d:
        mapped_id = param_2 + 0x20;
        if (3 < param_2 - 0x6051U) {
            mapped_id = param_2;
        }
        return mapped_id;
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
        mapped_id = 0x6141;
        alternate_id = 0x6151;
        goto select_inverse;
    case 0x57:
        if (param_2 - 0x6051U < 9) {
            return *(s32 *)(&DAT_7104538d70 + (s64)(s32)(param_2 - 0x6051U) * 4);
        }
        break;
    case 0x58:
        mapped_id = 0x6181;
        alternate_id = 0x6191;
select_inverse:
        result = param_2;
        if (param_2 == 0x6056) {
            result = alternate_id;
        }
        if (param_2 != 0x6052) {
            mapped_id = result;
        }
        return mapped_id;
    case 0x5c:
        mapped_id = param_2 + 0x1b0;
        if (0xf < param_2 - 0x6051U) {
            mapped_id = param_2;
        }
    }
    return mapped_id;
}

// 0x71002f2820 — inverse state remapper variant: translate param_1 by motion type param_2
s32 FUN_71002f2820(s32 param_1, u32 param_2)
{
    s32 result;
    u8 *table;
    u32 index;

    index = param_1 - 0x6091;
    if (index < 4) {
        table = &DAT_7104467f70;
lookup_table:
        result = *(s32 *)(table + (s64)(s32)index * 4);
    }
    else {
        result = param_1;
        switch(param_2) {
        case 0x3c:
        case 0x3d:
            result = param_1 + -0x20;
            if (3 < param_1 - 0x6071U) {
                result = param_1;
            }
            return result;
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
            result = 0x6051;
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
            index = param_1 - 0x6121;
            if (0x15 < index) {
                return param_1;
            }
            if ((0x3f00ffU >> (u64)(index & 0x1f) & 1) == 0) {
                return param_1;
            }
            table = &DAT_71045378d0;
            goto lookup_table;
        case 0x56:
            if (param_1 == 0x6141) {
                return 0x6052;
            }
            if (param_1 == 0x6151) {
                return 0x6056;
            }
            break;
        case 0x57:
            result = 0x6051;
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
            result = param_1 + -0x1b0;
            if (0xf < param_1 - 0x6201U) {
                result = param_1;
            }
            return result;
        default:
            return param_1;
        }
    }
    return result;
}

// 0x71002f46a0 — set motion bit: update bitmask at +0x180 based on active motion type
void FUN_71002f46a0(s64 param_1, s32 param_2)
{
    u8 out_of_range;
    s32 mapped_id;
    u32 index;
    s32 motion_id;
    u64 shift;

    motion_id = param_2;
    switch(*(u32 *)(*(s64 *)(param_1 + 8) + 0x28)) {
    case 0x3c:
    case 0x3d:
        motion_id = param_2 + -0x20;
        out_of_range = 3 < param_2 - 0x6071U;
        goto set_check_range;
    case 0x53:
        mapped_id = 0x6051;
        switch(param_2) {
        case 0x6101:
            break;
        case 0x6102:
set_map_6052:
            mapped_id = 0x6052;
            break;
        default:
            goto set_compute_index;
        case 0x6111:
set_map_6053:
            mapped_id = 0x6053;
            break;
        case 0x6112:
set_map_6054:
            mapped_id = 0x6054;
        }
        goto set_compute_shift;
    case 0x55:
        index = param_2 - 0x6121;
        if ((index < 0x16) && ((0x3f00ffU >> (u64)(index & 0x1f) & 1) != 0)) {
            motion_id = *(s32 *)(&DAT_71045378d0 + (s64)(s32)index * 4);
        }
        break;
    case 0x57:
        mapped_id = 0x6051;
        switch(param_2) {
        case 0x6161:
            goto set_map_6053;
        case 0x6162:
            goto set_map_6054;
        default:
            goto set_compute_index;
        case 0x6171:
            break;
        case 0x6172:
            goto set_map_6052;
        case 0x6173:
            mapped_id = 0x6055;
            break;
        case 0x6174:
set_map_6056:
            mapped_id = 0x6056;
            break;
        case 0x6175:
            mapped_id = 0x6057;
            break;
        case 0x6176:
            mapped_id = 0x6058;
            break;
        case 0x6177:
            mapped_id = 0x6059;
        }
        goto set_compute_shift;
    case 0x58:
        if (param_2 == 0x6181) goto set_map_6052;
        if (param_2 == 0x6191) goto set_map_6056;
        break;
    case 0x5c:
        motion_id = param_2 + -0x1b0;
        out_of_range = 0xf < param_2 - 0x6201U;
set_check_range:
        if (out_of_range) {
            motion_id = param_2;
        }
    }
set_compute_index:
    index = motion_id - 0x6031;
    if (0xe < index) {
        if (motion_id - 0x6041U < 0xf) {
            index = motion_id - 0x6034;
        }
        else {
            mapped_id = motion_id;
            if (0x17 < motion_id - 0x6051U) {
                shift = 0;
                goto set_apply_mask;
            }
set_compute_shift:
            index = mapped_id - 0x603b;
        }
    }
    shift = (u64)(s32)index;
set_apply_mask:
    *(u64 *)(param_1 + 0x180) = *(u64 *)(param_1 + 0x180) | 1L << (shift & 0x3f);
}

// 0x71002f5770 — clear motion bit: clear bitmask at +0x180 based on active motion type
void FUN_71002f5770(s64 param_1, s32 param_2)
{
    u8 out_of_range;
    s32 mapped_id;
    u32 index;
    s32 motion_id;
    u64 shift;

    motion_id = param_2;
    switch(*(u32 *)(*(s64 *)(param_1 + 8) + 0x28)) {
    case 0x3c:
    case 0x3d:
        motion_id = param_2 + -0x20;
        out_of_range = 3 < param_2 - 0x6071U;
        goto clr_check_range;
    case 0x53:
        mapped_id = 0x6051;
        switch(param_2) {
        case 0x6101:
            break;
        case 0x6102:
clr_map_6052:
            mapped_id = 0x6052;
            break;
        default:
            goto clr_compute_index;
        case 0x6111:
clr_map_6053:
            mapped_id = 0x6053;
            break;
        case 0x6112:
clr_map_6054:
            mapped_id = 0x6054;
        }
        goto clr_compute_shift;
    case 0x55:
        index = param_2 - 0x6121;
        if ((index < 0x16) && ((0x3f00ffU >> (u64)(index & 0x1f) & 1) != 0)) {
            motion_id = *(s32 *)(&DAT_71045378d0 + (s64)(s32)index * 4);
        }
        break;
    case 0x57:
        mapped_id = 0x6051;
        switch(param_2) {
        case 0x6161:
            goto clr_map_6053;
        case 0x6162:
            goto clr_map_6054;
        default:
            goto clr_compute_index;
        case 0x6171:
            break;
        case 0x6172:
            goto clr_map_6052;
        case 0x6173:
            mapped_id = 0x6055;
            break;
        case 0x6174:
clr_map_6056:
            mapped_id = 0x6056;
            break;
        case 0x6175:
            mapped_id = 0x6057;
            break;
        case 0x6176:
            mapped_id = 0x6058;
            break;
        case 0x6177:
            mapped_id = 0x6059;
        }
        goto clr_compute_shift;
    case 0x58:
        if (param_2 == 0x6181) goto clr_map_6052;
        if (param_2 == 0x6191) goto clr_map_6056;
        break;
    case 0x5c:
        motion_id = param_2 + -0x1b0;
        out_of_range = 0xf < param_2 - 0x6201U;
clr_check_range:
        if (out_of_range) {
            motion_id = param_2;
        }
    }
clr_compute_index:
    index = motion_id - 0x6031;
    if (0xe < index) {
        if (motion_id - 0x6041U < 0xf) {
            index = motion_id - 0x6034;
        }
        else {
            mapped_id = motion_id;
            if (0x17 < motion_id - 0x6051U) {
                shift = 0;
                goto clr_apply_mask;
            }
clr_compute_shift:
            index = mapped_id - 0x603b;
        }
    }
    shift = (u64)(s32)index;
clr_apply_mask:
    *(u64 *)(param_1 + 0x180) =
         *(u64 *)(param_1 + 0x180) & (1L << (shift & 0x3f) ^ 0xffffffffffffffffU);
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
