#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7103 address range, batch d-006
// Pool-d worker: auto-generated from Ghidra decompilation

// ---- External declarations -----------------------------------------------

extern "C" {
    int  __cxa_guard_acquire(u64*);
    void __cxa_guard_release(u64*);
}

// External data — guard symbols shared across multiple functions
extern u8 DAT_710593aa98[];
extern u8 DAT_710593aaa0[];
extern u8 DAT_710593aaa8[];
extern u8 DAT_710593aab0[];

// FUN_71037a2e00 guard data
extern u8 DAT_710593ac50[];
extern u8 DAT_710532e740[];
extern u8 DAT_710532e748[];
extern u8 DAT_710593ac58[];

// FUN_7103791420 guard data
extern u8 DAT_710593ab18[];
extern u8 DAT_710593ab20[];

// FUN_710379b910 guard data
extern u8 DAT_710593abc8[];
extern u8 DAT_710593abd0[];

// FUN_71037a02a0 guard data
extern u8 DAT_710593ac40[];
extern u8 DAT_710593ac48[];

// ---- Functions ---------------------------------------------------------------

// 0x7103789780 — two-level guard init, returns &DAT_710593aab0 (336 bytes)
u64 *FUN_7103789780(void)
{
    s32 iVar1;

    if (((*(u64*)DAT_710593aa98 & 1) == 0) &&
        (iVar1 = __cxa_guard_acquire((u64*)DAT_710593aa98), iVar1 != 0)) {
        if (((*(u64*)DAT_710593aaa0 & 1) == 0) &&
            (iVar1 = __cxa_guard_acquire((u64*)DAT_710593aaa0), iVar1 != 0)) {
            *(u64*)DAT_710593aaa8 = 0;
            __cxa_guard_release((u64*)DAT_710593aaa0);
        }
        *(u8**)DAT_710593aab0 = DAT_710593aaa8;
        __cxa_guard_release((u64*)DAT_710593aa98);
    }
    return (u64*)DAT_710593aab0;
}

// 0x71037a2e00 — two-level guard init (cross-segment inner guard), returns &DAT_710593ac58 (272 bytes)
u64 *FUN_71037a2e00(void)
{
    s32 iVar1;

    if (((*(u64*)DAT_710593ac50 & 1) == 0) &&
        (iVar1 = __cxa_guard_acquire((u64*)DAT_710593ac50), iVar1 != 0)) {
        if (((*(u64*)DAT_710532e740 & 1) == 0) &&
            (iVar1 = __cxa_guard_acquire((u64*)DAT_710532e740), iVar1 != 0)) {
            *(u64*)DAT_710532e748 = 0;
            __cxa_guard_release((u64*)DAT_710532e740);
        }
        *(u8**)DAT_710593ac58 = DAT_710532e748;
        __cxa_guard_release((u64*)DAT_710593ac50);
    }
    return (u64*)DAT_710593ac58;
}

// 0x7103791420 — triple-nested guard init, returns &DAT_710593ab20 (288 bytes)
u64 *FUN_7103791420(void)
{
    s32 iVar1;

    if (((*(u64*)DAT_710593ab18 & 1) == 0) &&
        (iVar1 = __cxa_guard_acquire((u64*)DAT_710593ab18), iVar1 != 0)) {
        if (((*(u64*)DAT_710593aa98 & 1) == 0) &&
            (iVar1 = __cxa_guard_acquire((u64*)DAT_710593aa98), iVar1 != 0)) {
            if (((*(u64*)DAT_710593aaa0 & 1) == 0) &&
                (iVar1 = __cxa_guard_acquire((u64*)DAT_710593aaa0), iVar1 != 0)) {
                *(u64*)DAT_710593aaa8 = 0;
                __cxa_guard_release((u64*)DAT_710593aaa0);
            }
            *(u8**)DAT_710593aab0 = DAT_710593aaa8;
            __cxa_guard_release((u64*)DAT_710593aa98);
        }
        *(u8**)DAT_710593ab20 = DAT_710593aab0;
        __cxa_guard_release((u64*)DAT_710593ab18);
    }
    return (u64*)DAT_710593ab20;
}

// 0x710379b910 — triple-nested guard init, returns &DAT_710593abd0 (288 bytes)
u64 *FUN_710379b910(void)
{
    s32 iVar1;

    if (((*(u64*)DAT_710593abc8 & 1) == 0) &&
        (iVar1 = __cxa_guard_acquire((u64*)DAT_710593abc8), iVar1 != 0)) {
        if (((*(u64*)DAT_710593aa98 & 1) == 0) &&
            (iVar1 = __cxa_guard_acquire((u64*)DAT_710593aa98), iVar1 != 0)) {
            if (((*(u64*)DAT_710593aaa0 & 1) == 0) &&
                (iVar1 = __cxa_guard_acquire((u64*)DAT_710593aaa0), iVar1 != 0)) {
                *(u64*)DAT_710593aaa8 = 0;
                __cxa_guard_release((u64*)DAT_710593aaa0);
            }
            *(u8**)DAT_710593aab0 = DAT_710593aaa8;
            __cxa_guard_release((u64*)DAT_710593aa98);
        }
        *(u8**)DAT_710593abd0 = DAT_710593aab0;
        __cxa_guard_release((u64*)DAT_710593abc8);
    }
    return (u64*)DAT_710593abd0;
}

// 0x71037a02a0 — triple-nested guard init, returns &DAT_710593ac48 (352 bytes)
u64 *FUN_71037a02a0(void)
{
    s32 iVar1;

    if (((*(u64*)DAT_710593ac40 & 1) == 0) &&
        (iVar1 = __cxa_guard_acquire((u64*)DAT_710593ac40), iVar1 != 0)) {
        if (((*(u64*)DAT_710593aa98 & 1) == 0) &&
            (iVar1 = __cxa_guard_acquire((u64*)DAT_710593aa98), iVar1 != 0)) {
            if (((*(u64*)DAT_710593aaa0 & 1) == 0) &&
                (iVar1 = __cxa_guard_acquire((u64*)DAT_710593aaa0), iVar1 != 0)) {
                *(u64*)DAT_710593aaa8 = 0;
                __cxa_guard_release((u64*)DAT_710593aaa0);
            }
            *(u8**)DAT_710593aab0 = DAT_710593aaa8;
            __cxa_guard_release((u64*)DAT_710593aa98);
        }
        *(u8**)DAT_710593ac48 = DAT_710593aab0;
        __cxa_guard_release((u64*)DAT_710593ac40);
    }
    return (u64*)DAT_710593ac48;
}

// 0x710335c478 — vtable call at 0x268 (no args), return 0 (300 bytes)
u64 FUN_710335c478(s64 *param_1)
{
    (*(void(*)())(*param_1 + 0x268))();
    return 0;
}

// 0x71031d04b0 — vtable call at 0x20 (no args), return 1 (320 bytes)
u64 FUN_71031d04b0(s64 *param_1)
{
    (*(void(*)())(*param_1 + 0x20))();
    return 1;
}

// 0x7103360268 — vtable call at 8 (no args), return 0 (352 bytes)
u64 FUN_7103360268(s64 *param_1)
{
    (*(void(*)())(*param_1 + 8))();
    return 0;
}

// 0x7103365d08 — vtable call at 8 (no args), return 0 (352 bytes)
u64 FUN_7103365d08(s64 *param_1)
{
    (*(void(*)())(*param_1 + 8))();
    return 0;
}

// 0x71033f1cc0 — vtable call at 0x2d0 with flag=1, set byte field (336 bytes)
void FUN_71033f1cc0(u64 param_1, s64 param_2)
{
    s64 *plVar1 = *(s64**)(*(s64*)(param_2 + 0x20) + 0x58);
    (*(void(*)(s64*, u32))(*plVar1 + 0x2d0))(plVar1, 1);
    *(u8*)(param_2 + 0x90) = 1;
}

// 0x71037f1d50 — switch on param_2: bool tests on param_1 vs param_3 (320 bytes)
u8 FUN_71037f1d50(u32 param_1, u32 param_2, s32 param_3)
{
    switch (param_2) {
    case 1: case 2: case 3: case 4:
    case 5: case 6: case 7: case 8:
        break;
    case 9: case 10: case 0xb: case 0xc:
    case 0xd: case 0xe: case 0xf: case 0x10:
        return (u8)(param_1 == 5 || (param_1 | 2) == 6);
    case 0x11: case 0x12: case 0x13: case 0x14:
    case 0x15: case 0x16: case 0x17: case 0x18:
        return (u8)(param_3 == 0x11 && (param_1 == 0xd || (param_1 | 1) == 0xf));
    default:
        return 0;
    case 0x21: case 0x22: case 0x23: case 0x24:
    case 0x25: case 0x26: case 0x27: case 0x28:
        return (u8)(param_1 - 10 < 3);
    case 0x29: case 0x2a: case 0x2b: case 0x2c:
    case 0x2d: case 0x2e: case 0x2f: case 0x30:
        return (u8)((param_1 | 1) == 0x11);
    case 0x31: case 0x32: case 0x33: case 0x34:
    case 0x35: case 0x36: case 0x37: case 0x38:
        return (u8)(param_1 - 7 < 3);
    case 0x41: case 0x42: case 0x43: case 0x44:
    case 0x45: case 0x46: case 0x47: case 0x48:
        return (u8)(param_1 == 0x14 && param_3 == 0x11);
    case 0x49: case 0x4a: case 0x4b: case 0x4c:
    case 0x4d: case 0x4e: case 0x4f: case 0x50:
        return (u8)(param_1 == 0x15 && param_3 == 0x11);
    }
    if (param_3 == 0xf) {
        return (u8)(param_1 == 2);
    }
    if (param_3 == 0x10) {
        return (u8)(param_1 == 1);
    }
    if (param_3 != 0x11) {
        return 0;
    }
    return (u8)(param_1 == 0 || param_1 == 3);
}

// 0x71037ccf40 — large switch: return component count for param type (288 bytes)
u64 FUN_71037ccf40(s32 param_1)
{
    u64 uVar1 = 0;
    if (param_1 < 0x332) {
        switch (param_1) {
        case 0x100: case 0x101: case 0x102: case 0x103:
            return 1;
        case 0x104: case 0x105: case 0x106: case 0x107:
        case 0x108: case 0x109: case 0x10a: case 0x10b:
        case 0x10c: case 0x10d: case 0x10e: case 0x10f:
        case 0x115: case 0x116: case 0x117: case 0x118:
        case 0x119: case 0x11a: case 0x11b: case 0x11c:
        case 0x11d: case 0x11e: case 0x11f:
        case 0x121: case 0x122: case 0x123: case 0x124:
        case 0x125: case 0x126: case 0x127: case 0x128:
        case 0x129: case 0x12a:
        case 299: case 300:
        case 0x12d: case 0x12e: case 0x12f: case 0x130:
        case 0x135: case 0x136: case 0x137: case 0x138:
        case 0x139: case 0x13a: case 0x13b: case 0x13c:
        case 0x13d: case 0x13e: case 0x13f: case 0x140:
        case 0x141: case 0x142: case 0x143:
        case 0x145: case 0x146: case 0x147: case 0x148:
        case 0x149: case 0x14a: case 0x14b: case 0x14c:
        case 0x14d: case 0x14e: case 0x14f: case 0x150:
        case 0x151: case 0x152: case 0x153: case 0x154:
        case 0x155: case 0x156: case 0x157: case 0x158:
        case 0x159: case 0x15a: case 0x15b: case 0x15c:
        case 0x15d: case 0x15e: case 0x15f: case 0x160:
        case 0x161: case 0x162: case 0x163: case 0x164:
        case 0x165: case 0x166: case 0x167: case 0x168:
        case 0x169: case 0x16a: case 0x16b: case 0x16c:
        case 0x16d: case 0x16e: case 0x16f: case 0x170:
        case 0x171: case 0x172: case 0x173: case 0x174:
        case 0x175: case 0x176: case 0x177: case 0x178:
        case 0x179: case 0x17a: case 0x17b: case 0x17c:
        case 0x17d: case 0x17e: case 0x17f:
            break;
        case 0x110: case 0x111: case 0x112: case 0x113: case 0x114:
        case 0x120:
        case 0x180: case 0x181:
            return 2;
        case 0x131: case 0x132: case 0x133: case 0x134:
        case 0x144:
            return 4;
        default:
            switch (param_1) {
            case 0x200: case 0x201: case 0x202: case 0x203:
                return 2;
            case 0x204: case 0x205: case 0x206: case 0x207:
            case 0x208: case 0x209: case 0x20a: case 0x20b:
            case 0x20c: case 0x20d: case 0x20e: case 0x20f:
            case 0x215: case 0x216: case 0x217: case 0x218:
            case 0x219: case 0x21a: case 0x21b: case 0x21c:
            case 0x21d: case 0x21e: case 0x21f: case 0x220:
            case 0x221: case 0x222: case 0x223: case 0x224:
            case 0x225: case 0x226: case 0x227: case 0x228:
            case 0x229: case 0x22a: case 0x22b: case 0x22c:
            case 0x22d: case 0x22e: case 0x22f: case 0x230:
            case 0x231: case 0x232: case 0x233:
            case 0x235: case 0x236: case 0x237: case 0x238:
            case 0x239: case 0x23a: case 0x23b: case 0x23c:
            case 0x23d: case 0x23e: case 0x23f: case 0x240:
            case 0x241: case 0x242: case 0x243: case 0x244:
            case 0x245:
            case 0x247: case 0x248: case 0x249: case 0x24a:
            case 0x24b: case 0x24c: case 0x24d: case 0x24e:
            case 0x24f: case 0x250: case 0x251: case 0x252:
            case 0x253: case 0x254: case 0x255: case 0x256:
            case 599: case 600:
            case 0x259: case 0x25a: case 0x25b: case 0x25c:
            case 0x25d: case 0x25e: case 0x25f: case 0x260:
            case 0x261: case 0x262: case 0x263: case 0x264:
            case 0x265: case 0x266: case 0x267: case 0x268:
            case 0x269: case 0x26a: case 0x26b: case 0x26c:
            case 0x26d: case 0x26e: case 0x26f: case 0x270:
            case 0x271: case 0x272: case 0x273: case 0x274:
            case 0x275: case 0x276: case 0x277: case 0x278:
            case 0x279: case 0x27a: case 0x27b: case 0x27c:
            case 0x27d: case 0x27e: case 0x27f:
                break;
            case 0x210: case 0x211: case 0x212: case 0x213: case 0x214:
            case 0x246:
            case 0x280: case 0x281:
                return 4;
            case 0x234:
                return 8;
            default:
                if ((u32)(param_1 - 800) < 2) {
                    return 2;
                }
            }
        }
    } else {
        switch (param_1) {
        case 0x400: case 0x401: case 0x402: case 0x403:
        case 0x405:
        case 0x440: case 0x442:
        case 0x450: case 0x455:
        case 0x490: case 0x495:
        case 0x4a0: case 0x4a5:
        case 0x4d7: case 0x4d8:
        case 0x4e0: case 0x4e5:
        case 0x4ea: case 0x4eb:
        case 0x4ee: case 0x4ef:
            return 4;
        case 0x404:
        case 0x406: case 0x407: case 0x408: case 0x409:
        case 0x40a: case 0x40b: case 0x40c: case 0x40d:
        case 0x40e: case 0x40f: case 0x410: case 0x411:
        case 0x412: case 0x413: case 0x414: case 0x415:
        case 0x416: case 0x417: case 0x418: case 0x419:
        case 0x41a: case 0x41b: case 0x41c: case 0x41d:
        case 0x41e: case 0x41f:
        case 0x421: case 0x422: case 0x423: case 0x424:
        case 0x425: case 0x426: case 0x427: case 0x428:
        case 0x429: case 0x42a: case 0x42b: case 0x42c:
        case 0x42d: case 0x42e: case 0x42f: case 0x430:
        case 0x431:
        case 0x436: case 0x437: case 0x438: case 0x439:
        case 0x43a: case 0x43b: case 0x43c: case 0x43d:
        case 0x43e: case 0x43f:
        case 0x441:
        case 0x443: case 0x444: case 0x445: case 0x446:
        case 0x447: case 0x448: case 0x449: case 0x44a:
        case 1099:
        case 0x44c: case 0x44d: case 0x44e: case 0x44f:
        case 0x451: case 0x452: case 0x453: case 0x454:
        case 0x456: case 0x457: case 0x458: case 0x459:
        case 0x45a: case 0x45b: case 0x45c: case 0x45d:
        case 0x45e: case 0x45f: case 0x460: case 0x461:
        case 0x462: case 0x463: case 0x464: case 0x465:
        case 0x466: case 0x467: case 0x468: case 0x469:
        case 0x46a: case 0x46b: case 0x46c: case 0x46d:
        case 0x46e: case 0x46f: case 0x470: case 0x471:
        case 0x472: case 0x473: case 0x474: case 0x475:
        case 0x476: case 0x477: case 0x478: case 0x479:
        case 0x47a: case 0x47b: case 0x47c: case 0x47d:
        case 0x47e: case 0x47f:
        case 0x481: case 0x482: case 0x483: case 0x484:
        case 0x486: case 0x487: case 0x488: case 0x489:
        case 0x48a: case 0x48b: case 0x48c: case 0x48d:
        case 0x48e: case 0x48f:
        case 0x491: case 0x492: case 0x493: case 0x494:
        case 0x496: case 0x497: case 0x498: case 0x499:
        case 0x49a: case 0x49b: case 0x49c: case 0x49d:
        case 0x49e: case 0x49f:
        case 0x4a1: case 0x4a2: case 0x4a3: case 0x4a4:
        case 0x4a6: case 0x4a7: case 0x4a8: case 0x4a9:
        case 0x4aa: case 0x4ab: case 0x4ac: case 0x4ad:
        case 0x4ae: case 0x4af: case 0x4b0: case 0x4b1:
        case 0x4b2: case 0x4b3: case 0x4b4: case 0x4b5:
        case 0x4b6: case 0x4b7: case 0x4b8: case 0x4b9:
        case 0x4ba: case 0x4bb: case 0x4bc: case 0x4bd:
        case 0x4be: case 0x4bf:
        case 0x4c1: case 0x4c2: case 0x4c3: case 0x4c4:
        case 0x4c5: case 0x4c6: case 0x4c7: case 0x4c8:
        case 0x4c9: case 0x4ca: case 0x4cb: case 0x4cc:
        case 0x4cd: case 0x4ce: case 0x4cf: case 0x4d0:
        case 0x4d1: case 0x4d2: case 0x4d3: case 0x4d4:
        case 0x4d5: case 0x4d6:
        case 0x4d9: case 0x4da: case 0x4db: case 0x4dc:
        case 0x4dd: case 0x4de: case 0x4df:
        case 0x4e1: case 0x4e2: case 0x4e3: case 0x4e4:
            break;
        case 0x420:
        case 0x480: case 0x485:
        case 0x4c0:
        case 0x4e6: case 0x4e7: case 0x4e8: case 0x4e9:
        case 0x4ec: case 0x4ed:
            return 2;
        case 0x432: case 0x433: case 0x434:
            uVar1 = 0x10;
            break;
        case 0x435:
            return 8;
        default:
            if ((u32)(param_1 - 0x332) < 3) {
                return 0xc;
            }
            if (param_1 == 0x344) {
                return 4;
            }
        }
    }
    return uVar1;
}
