// SSBU 13.0.4 — MEDIUM-tier decompilation batch 009
// Address range: 0x71002c2c30 – 0x7100314d50
// Worker: pool-b

#include "types.h"

namespace app {
namespace lua_bind {

// Forward declarations
extern "C" {
    [[noreturn]] void nn_detail_UnexpectedDefaultImpl(const char *, const char *, int);
    void  FUN_710003a0e0();
    void  FUN_710003a240(void *p);
    void  FUN_7100313000(long a, void *b, void *c, void *d, void *e);
    void  FUN_7100313460(long a, void *b, void *c, void *d, void *e);
}

// FUN_71002c2c30 — slot address table: param_1 + param_3*0x58 + base_offset[param_2]
// Maps 12 channel types (0–11) to their per-slot offsets
long FUN_71002c2c30(long param_1, u32 param_2, int param_3) {
    static const long offsets[12] = {
        0x6c, 0x1cc, 0x5ec, 0xa0c, 0x376c, 0x64cc,
        0x922c, 0xbf8c, 0xecec, 0x11a4c, 0x11aa4, 0x120d4
    };
    if (param_2 < 12) {
        return param_1 + (long)param_3 * 0x58 + offsets[param_2];
    }
    nn_detail_UnexpectedDefaultImpl("", "", 0);
}

// FUN_71002c2df0 — table lookup (< 11): return DAT_71044a7d50[param_1]
extern u32 DAT_71044a7d50;
u32 FUN_71002c2df0(u32 param_1) {
    if (param_1 < 0xb) {
        return *(u32 *)(&DAT_71044a7d50 + (long)(int)param_1 * 4);
    }
    nn_detail_UnexpectedDefaultImpl("", "", 0);
}

// FUN_71002c2e50 — slot pointer table (11 cases): param_1 + param_3*0x1c + base[param_2]
// Returns pointer into animation blend channel data
extern u8 DAT_0000159c;
extern u8 DAT_00002188;
extern u8 DAT_00002230;
u8 *FUN_71002c2e50(long param_1, u32 param_2, int param_3) {
    switch (param_2) {
    case  0: return (u8 *)(param_1 + (long)param_3 * 0x1c + 100);
    case  1: return (u8 *)(param_1 + (long)param_3 * 0x1c + 0xed4);
    case  2: return &DAT_0000159c + param_1 + (long)param_3 * 0x1c;
    case  3: return (u8 *)(param_1 + (long)param_3 * 0x1c + 0x183c);
    case  4: return (u8 *)(param_1 + (long)param_3 * 0x1c + 0x1874);
    case  5: return (u8 *)(param_1 + (long)param_3 * 0x1c + 0x19c4);
    case  6: return (u8 *)(param_1 + (long)param_3 * 0x1c + 0x1b14);
    case  7: return (u8 *)(param_1 + (long)param_3 * 0x1c + 0x1d44);
    case  8: return (u8 *)(param_1 + (long)param_3 * 0x1c + 0x1d7c);
    case  9: return &DAT_00002188 + param_1 + (long)param_3 * 0x1c;
    case 10: return &DAT_00002230 + param_1 + (long)param_3 * 0x1c;
    default:
        nn_detail_UnexpectedDefaultImpl("", "", 0);
    }
}

// FUN_71002c2f70 — init slot: call setup helpers, set sentinel at +0x120
void FUN_71002c2f70(long param_1) {
    FUN_710003a0e0();
    FUN_710003a240((void *)(param_1 + 0xd8));
    *(u64 *)(param_1 + 0x120) = 0xffffffffffffffffULL;
}

// FUN_71002c31e0 — conditional store: if field != sentinel, reset; then copy from param_2
void FUN_71002c31e0(long param_1, u64 *param_2) {
    if (*(long *)(param_1 + 0x120) != -1) {
        *(u64 *)(param_1 + 0x120) = 0xffffffffffffffffULL;
    }
    *(u64 *)(param_1 + 0x120) = *param_2;
}

// FUN_71002f0f70 — action code remapper: translates fighter-specific codes to canonical codes
// Used by input system to map between fighter move IDs and game-global action IDs
int FUN_71002f0f70(long *param_1, int param_2) {
    int iVar5, iVar6, iVar4;
    bool bVar3;

    switch (*(u32 *)(*param_1 + 0xc04)) {
    case 0x1c:
        if (!((*(u8 *)(param_1[1] + 0x68) >> 1) & 1)) return param_2;
        break;
    case 0x21:
        if (!((*(u8 *)(param_1[1] + 0x68) >> 1) & 1)) return param_2;
        break;
    case 0x30: case 0x46:
        if (!(*(u8 *)(param_1[1] + 0x68) & 1)) return param_2;
        iVar4 = 0x6051; iVar5 = 0x6038; bVar3 = (param_2 == 0x6046); iVar6 = 0x6055;
        goto LAB_71002f1140;
    case 0x34:
        if (!(*(u8 *)(param_1[1] + 0x68) & 1)) return param_2;
        iVar4 = 0x6051; iVar5 = 0x6038; bVar3 = (param_2 == 0x6046); iVar6 = 0x6055;
        goto LAB_71002f1140;
    case 0x3c: case 0x3d:
        iVar5 = param_2 - 0x20;
        if ((u32)(param_2 - 0x6071) > 3) iVar5 = param_2;
        return iVar5;
    case 0x53:
        iVar5 = 0x6051;
        switch (param_2) {
        case 0x6101: break;
        case 0x6102: return 0x6052;
        case 0x6103: case 0x6104: case 0x6105: case 0x6106: case 0x6107:
        case 0x6108: case 0x6109: case 0x610a: case 0x610b: case 0x610c:
        case 0x610d: case 0x610e: case 0x610f: case 0x6110: return param_2;
        case 0x6111: return 0x6053;
        case 0x6112: return 0x6054;
        default: return param_2;
        }
        goto switchD_6101;
    case 0x55: {
        u32 uVar3 = (u32)(param_2 - 0x6121);
        if (uVar3 < 0x16) {
            extern int DAT_71045378d0;
            if ((0x3f00ffU >> (uVar3 & 0x1f)) & 1) {
                return *(int *)(&DAT_71045378d0 + (long)(int)uVar3 * 4);
            }
        }
        return param_2;
    }
    case 0x56:
        iVar5 = 0x6141; iVar6 = 0x6151; goto LAB_71002f1138;
    case 0x57:
        iVar5 = 0x6051;
        switch (param_2) {
        case 0x6161: return 0x6053;
        case 0x6162: return 0x6054;
        case 0x6163: case 0x6164: case 0x6165: case 0x6166: case 0x6167:
        case 0x6168: case 0x6169: case 0x616a: case 0x616b: case 0x616c:
        case 0x616d: case 0x616e: case 0x616f: case 0x6170: return param_2;
        case 0x6171: break;
        case 0x6172: return 0x6052;
        case 0x6173: return 0x6055;
        case 0x6174: return 0x6056;
        case 0x6175: return 0x6057;
        case 0x6176: return 0x6058;
        case 0x6177: return 0x6059;
        default: return param_2;
        }
        goto switchD_6101;
    case 0x58:
        iVar5 = 0x6181; iVar6 = 0x6191;
LAB_71002f1138:
        iVar4 = 0x6052; bVar3 = (param_2 == iVar6); iVar6 = 0x6056; goto LAB_71002f1140;
    case 0x5c:
        iVar5 = param_2 - 0x1b0;
        if ((u32)(param_2 - 0x6201) > 0xf) iVar5 = param_2;
        return iVar5;
    default:
        switch (param_2) {
        case 0x6038: { int v = *(int *)(param_1[1]+0x238); return v ? 0x6049 + v*8 : 0x6038; }
        case 0x6039: { int v = *(int *)(param_1[1]+0x23c); return v ? 0x604a + v*8 : 0x6039; }
        case 0x603a: { int v = *(int *)(param_1[1]+0x240); return v ? 0x604b + v*8 : 0x603a; }
        case 0x603b: { int v = *(int *)(param_1[1]+0x244); return v ? 0x604c + v*8 : 0x603b; }
        case 0x603c: case 0x603d: case 0x603e: case 0x603f: case 0x6040:
        case 0x6041: case 0x6042: case 0x6043: case 0x6044: case 0x6045:
            return param_2;
        case 0x6046: { int v = *(int *)(param_1[1]+0x238); return v ? 0x604d + v*8 : 0x6046; }
        case 0x6047: { int v = *(int *)(param_1[1]+0x23c); return v ? 0x604e + v*8 : 0x6047; }
        case 0x6048: { int v = *(int *)(param_1[1]+0x240); return v ? 0x604f + v*8 : 0x6048; }
        case 0x6049: { int v = *(int *)(param_1[1]+0x244); return v ? 0x6050 + v*8 : 0x6049; }
        default: return param_2;
        }
    }

    iVar4 = 0x6054; iVar5 = 0x603b; bVar3 = (param_2 == 0x6049); iVar6 = 0x6058;
LAB_71002f1140: {
        int iVar2 = param_2;
        if (bVar3) iVar2 = iVar6;
        if (param_2 != iVar5) iVar4 = iVar2;
        return iVar4;
    }
switchD_6101:
    // iVar5 = 0x6051 at this point
    {
        u32 uVar3 = (u32)(iVar5 - 0x603b);
        return (int)(u64)(iVar5 - 0x603b);
    }
}

// FUN_71002f14e0 — reverse action remapper: canonical → fighter-specific
int FUN_71002f14e0(u32 param_1, int param_2) {
    int iVar2 = param_2;
    switch (param_1) {
    case 0x3c: case 0x3d:
        iVar2 = param_2 + 0x20;
        if ((u32)(param_2 - 0x6051) > 3) iVar2 = param_2;
        return iVar2;
    case 0x53:
        if ((u32)(param_2 - 0x6051) < 4) {
            extern int DAT_71044692f0;
            return *(int *)(&DAT_71044692f0 + (long)(int)(param_2 - 0x6051) * 4);
        }
        break;
    case 0x55:
        if ((u32)(param_2 - 0x6051) < 0xe) {
            extern int DAT_7104537890;
            return *(int *)(&DAT_7104537890 + (long)(int)(param_2 - 0x6051) * 4);
        }
        break;
    case 0x56: {
        int i2 = 0x6141, i3 = 0x6151;
        int i1 = param_2;
        if (param_2 == 0x6056) i1 = i3;
        if (param_2 != 0x6052) i2 = i1;
        return i2;
    }
    case 0x57:
        if ((u32)(param_2 - 0x6051) < 9) {
            extern int DAT_7104538d70;
            return *(int *)(&DAT_7104538d70 + (long)(int)(param_2 - 0x6051) * 4);
        }
        break;
    case 0x58: {
        int i2 = 0x6181, i3 = 0x6191;
        int i1 = param_2;
        if (param_2 == 0x6056) i1 = i3;
        if (param_2 != 0x6052) i2 = i1;
        return i2;
    }
    case 0x5c:
        iVar2 = param_2 + 0x1b0;
        if ((u32)(param_2 - 0x6051) > 0xf) iVar2 = param_2;
        break;
    }
    return iVar2;
}

// FUN_71002f2820 — action remapper variant 2 (maps 0x6091–0x6094 via table)
extern int DAT_7104467f70;
int FUN_71002f2820(int param_1, u32 param_2) {
    u32 uVar3 = (u32)(param_1 - 0x6091);
    if (uVar3 < 4) {
        return *(int *)(&DAT_7104467f70 + (long)(int)uVar3 * 4);
    }
    int iVar1 = param_1;
    switch (param_2) {
    case 0x3c: case 0x3d:
        iVar1 = param_1 - 0x20;
        if ((u32)(param_1 - 0x6071) > 3) iVar1 = param_1;
        return iVar1;
    case 0x53:
        iVar1 = 0x6051;
        switch (param_1) {
        case 0x6101: break;
        case 0x6102: return 0x6052;
        case 0x6103: case 0x6104: case 0x6105: case 0x6106: case 0x6107:
        case 0x6108: case 0x6109: case 0x610a: case 0x610b: case 0x610c:
        case 0x610d: case 0x610e: case 0x610f: case 0x6110: return param_1;
        case 0x6111: return 0x6053;
        case 0x6112: return 0x6054;
        default: return param_1;
        }
        break;
    case 0x55: {
        u32 u = (u32)(param_1 - 0x6121);
        if (u < 0x16 && ((0x3f00ffU >> (u & 0x1f)) & 1)) {
            extern int DAT_71045378d0_2;
            return *(int *)(&DAT_71045378d0_2 + (long)(int)u * 4);
        }
        break;
    }
    case 0x56:
        if (param_1 == 0x6141) return 0x6052;
        if (param_1 == 0x6151) return 0x6056;
        break;
    case 0x57:
        iVar1 = 0x6051;
        switch (param_1) {
        case 0x6161: return 0x6053;
        case 0x6162: return 0x6054;
        case 0x6163: case 0x6164: case 0x6165: case 0x6166: case 0x6167:
        case 0x6168: case 0x6169: case 0x616a: case 0x616b: case 0x616c:
        case 0x616d: case 0x616e: case 0x616f: case 0x6170: return param_1;
        case 0x6171: break;
        case 0x6172: return 0x6052;
        case 0x6173: return 0x6055;
        case 0x6174: return 0x6056;
        case 0x6175: return 0x6057;
        case 0x6176: return 0x6058;
        case 0x6177: return 0x6059;
        default: return param_1;
        }
        break;
    case 0x58:
        if (param_1 == 0x6181) return 0x6052;
        if (param_1 == 0x6191) return 0x6056;
        break;
    case 0x5c:
        iVar1 = param_1 - 0x1b0;
        if ((u32)(param_1 - 0x6201) > 0xf) iVar1 = param_1;
        return iVar1;
    default:
        return param_1;
    }
    return iVar1;
}

// FUN_71002f46a0 — set bit in bitmask at param_1+0x180 for given action code
// Translates action code to bit index using same remapping logic as FUN_71002f0f70
void FUN_71002f46a0(long param_1, int param_2) {
    bool bVar1;
    int iVar2, iVar5;
    u32 uVar3;
    u64 uVar4;
    extern int DAT_71045378d0_3;

    iVar5 = param_2;
    switch (*(u32 *)(*(long *)(param_1 + 8) + 0x28)) {
    case 0x3c: case 0x3d:
        iVar5 = param_2 - 0x20;
        bVar1 = (u32)(param_2 - 0x6071) > 3;
        if (bVar1) iVar5 = param_2;
        break;
    case 0x53:
        iVar2 = 0x6051;
        switch (param_2) {
        case 0x6101: break;
        case 0x6102: iVar2 = 0x6052; goto setbit;
        case 0x6111: iVar2 = 0x6053; goto setbit;
        case 0x6112: iVar2 = 0x6054; goto setbit;
        default: goto fallthrough;
        }
        goto setbit;
    case 0x55:
        uVar3 = (u32)(param_2 - 0x6121);
        if (uVar3 < 0x16 && ((0x3f00ffU >> (uVar3 & 0x1f)) & 1)) {
            iVar5 = *(int *)(&DAT_71045378d0_3 + (long)(int)uVar3 * 4);
        }
        break;
    case 0x57:
        iVar2 = 0x6051;
        switch (param_2) {
        case 0x6161: iVar2 = 0x6053; goto setbit;
        case 0x6162: iVar2 = 0x6054; goto setbit;
        case 0x6171: break;
        case 0x6172: iVar2 = 0x6052; goto setbit;
        case 0x6173: iVar2 = 0x6055; goto setbit;
        case 0x6174: iVar2 = 0x6056; goto setbit;
        case 0x6175: iVar2 = 0x6057; goto setbit;
        case 0x6176: iVar2 = 0x6058; goto setbit;
        case 0x6177: iVar2 = 0x6059; goto setbit;
        default: goto fallthrough;
        }
        goto setbit;
    case 0x58:
        iVar2 = 0x6051;
        if (param_2 == 0x6181) { iVar2 = 0x6052; goto setbit; }
        if (param_2 == 0x6191) { iVar2 = 0x6056; goto setbit; }
        break;
    case 0x5c:
        iVar5 = param_2 - 0x1b0;
        if ((u32)(param_2 - 0x6201) > 0xf) iVar5 = param_2;
        break;
    default:
        break;
    }
fallthrough:
    uVar3 = (u32)(iVar5 - 0x6031);
    if (uVar3 > 0xe) {
        if ((u32)(iVar5 - 0x6041) < 0xf) {
            uVar3 = (u32)(iVar5 - 0x6034);
        } else {
            iVar2 = iVar5;
            if ((u32)(iVar5 - 0x6051) > 0x17) { uVar4 = 0; goto setmask; }
setbit:
            uVar3 = (u32)(iVar2 - 0x603b);
        }
    }
    uVar4 = (u64)(int)uVar3;
setmask:
    *(u64 *)(param_1 + 0x180) |= 1ULL << (uVar4 & 0x3f);
}

// FUN_71002f5770 — clear bit in bitmask at param_1+0x180 for given action code
// Mirror of FUN_71002f46a0 but clears instead of sets
void FUN_71002f5770(long param_1, int param_2) {
    int iVar2, iVar5;
    u32 uVar3;
    u64 uVar4;
    extern int DAT_71045378d0_4;

    iVar5 = param_2;
    switch (*(u32 *)(*(long *)(param_1 + 8) + 0x28)) {
    case 0x3c: case 0x3d:
        iVar5 = param_2 - 0x20;
        if ((u32)(param_2 - 0x6071) > 3) iVar5 = param_2;
        break;
    case 0x53:
        iVar2 = 0x6051;
        switch (param_2) {
        case 0x6101: break;
        case 0x6102: iVar2 = 0x6052; goto clearbit;
        case 0x6111: iVar2 = 0x6053; goto clearbit;
        case 0x6112: iVar2 = 0x6054; goto clearbit;
        default: goto clear_fallthrough;
        }
        goto clearbit;
    case 0x55:
        uVar3 = (u32)(param_2 - 0x6121);
        if (uVar3 < 0x16 && ((0x3f00ffU >> (uVar3 & 0x1f)) & 1)) {
            iVar5 = *(int *)(&DAT_71045378d0_4 + (long)(int)uVar3 * 4);
        }
        break;
    case 0x57:
        iVar2 = 0x6051;
        switch (param_2) {
        case 0x6161: iVar2 = 0x6053; goto clearbit;
        case 0x6162: iVar2 = 0x6054; goto clearbit;
        case 0x6171: break;
        case 0x6172: iVar2 = 0x6052; goto clearbit;
        case 0x6173: iVar2 = 0x6055; goto clearbit;
        case 0x6174: iVar2 = 0x6056; goto clearbit;
        case 0x6175: iVar2 = 0x6057; goto clearbit;
        case 0x6176: iVar2 = 0x6058; goto clearbit;
        case 0x6177: iVar2 = 0x6059; goto clearbit;
        default: goto clear_fallthrough;
        }
        goto clearbit;
    case 0x58:
        iVar2 = 0x6051;
        if (param_2 == 0x6181) { iVar2 = 0x6052; goto clearbit; }
        if (param_2 == 0x6191) { iVar2 = 0x6056; goto clearbit; }
        break;
    case 0x5c:
        iVar5 = param_2 - 0x1b0;
        if ((u32)(param_2 - 0x6201) > 0xf) iVar5 = param_2;
        break;
    default:
        break;
    }
clear_fallthrough:
    uVar3 = (u32)(iVar5 - 0x6031);
    if (uVar3 > 0xe) {
        if ((u32)(iVar5 - 0x6041) < 0xf) {
            uVar3 = (u32)(iVar5 - 0x6034);
        } else {
            iVar2 = iVar5;
            if ((u32)(iVar5 - 0x6051) > 0x17) { uVar4 = 0; goto clearmask; }
clearbit:
            uVar3 = (u32)(iVar2 - 0x603b);
        }
    }
    uVar4 = (u64)(int)uVar3;
clearmask:
    *(u64 *)(param_1 + 0x180) &= ~(1ULL << (uVar4 & 0x3f));
}

// FUN_71002fafb0 — animation blend-tree shortest-path finder
// Searches a fixed-size (128-slot) adjacency list for the shortest weighted path
// from param_2 to param_3. Returns the first node on the optimal path.
// Returns null if: graph locked, either endpoint absent, or no path found.
extern float DAT_7104471d2c;

void *FUN_71002fafb0(u8 *param_1, void **param_2, void **param_3) {
    // Guard: graph must be enabled (param_1[0] != 0)
    if (!*param_1) return 0;
    if (!param_3 || !param_2 || param_2 == param_3) return 0;

    // Lock: prevent re-entry (param_1[0x39])
    if (param_1[0x38] || param_1[0x39]) return 0;
    param_1[0x39] = 1;

    // Walk 128-slot adjacency table at param_1+0x28 (stride 0x50)
    void **src_slot  = 0;
    void **dst_slot  = 0;
    u8   *base       = param_1 + 0x28;
    for (int i = 0; i < 0x80; i++) {
        void **slot = (void **)(base + (long)i * 0x50);
        if (!*(int *)slot) continue;
        slot[8] = 0;
        slot[9] = 0;
        if (slot[1] == param_2) {
            *(int *)(slot + 9) = 1;
            src_slot = slot;
        }
        if (slot[1] == param_3) {
            dst_slot = slot;
        }
    }
    if (!src_slot || !dst_slot) {
        param_1[0x39] = 0;
        return 0;
    }

    // BFS/Dijkstra: two alternating open lists
    void *list_a[2] = { &list_a, &list_a };
    void *list_b[2] = { &list_b, &list_b };
    int count_a = 0, count_b = 0;

    // Seed: mark all edges from src_slot as VISITED(2), enqueue
    void **edge = (void **)src_slot[3];
    while (src_slot + 2 != (void **)edge) {
        void **node = (void **)edge[2];
        if (node == dst_slot) {
            param_1[0x39] = 0;
            return node[1];
        }
        if (node[1] && *(int *)(node + 9) == 0) {
            *(int *)(node + 9) = 2;
            // push to list_b
            node[8] = node;
            node[5] = list_b[1];
            node[6] = list_b;
            ((void **)list_b[1])[1] = node + 5;
            list_b[1] = node + 5;
            count_b++;
        }
        edge = (void **)edge[1];
    }

    float best_dist = DAT_7104471d2c;
    void **best_next = 0;
    u32 iter = 0;
    void **open  = (void **)list_b;
    void **closed = (void **)list_a;

    while (count_a || count_b) {
        // Reset next open list
        void *next_open[2] = { &next_open, &next_open };
        int next_count = 0;

        // Iterate over current open list
        void **cur_open_tail = (void **)open[1];
        while (open != cur_open_tail) {
            void **cur = (void **)cur_open_tail[2];
            void **edges_head = (void **)(cur + 2);
            void **edges = (void **)cur[3];
            if (edges_head != edges) {
                float cur_dist = *(float *)((u8 *)cur_open_tail + 0x24);
                u32 edge_idx = 0;
                while (1) {
                    void **tgt = (void **)edges[2];
                    float new_dist = cur_dist + *(float *)(edges + 3);
                    if (tgt == dst_slot) {
                        if (new_dist < best_dist) {
                            best_next = (void **)cur_open_tail[3];
                            best_dist = new_dist;
                        }
                        goto next_edge;
                    }
                    if (tgt[1]) {
                        if (*(int *)(tgt + 9) == 0) {
                            *(int *)(tgt + 9) = 3;
                            *(float *)((u8 *)tgt + 0x4c) = new_dist;
                            tgt[8] = cur_open_tail[3];
                            // enqueue into next_open
                            void **tail2 = (void **)next_open[1];
                            tgt[5] = *tail2;
                            tgt[6] = next_open + 1;
                            ((void **)*tail2)[1] = tgt + 5;
                            ((void **)next_open[1])[0] = tgt + 5;
                            next_count++;
                        } else if (*(int *)(tgt + 9) == 3) {
                            float cur_best = *(float *)((u8 *)tgt + 0x4c);
                            if (new_dist < cur_best) {
                                *(float *)((u8 *)tgt + 0x4c) = new_dist;
                                tgt[8] = cur_open_tail[3];
                            }
                        }
                    }
next_edge:
                    edge_idx++;
                    if (edge_idx > 0x3f) break;
                    edges = (void **)edges[1];
                    if (edges_head == (void **)edges) break;
                }
                if (best_next) {
                    param_1[0x39] = 0;
                    return best_next[1];
                }
            }
            *(int *)(cur_open_tail + 4) = 4; // mark DONE
            if (iter > 0x3f) break;
            cur_open_tail = (void **)cur_open_tail[1];
            iter++;
        }

        // Swap lists
        bool was_next = ((void **)next_open == open);
        open   = was_next ? closed : (void **)next_open;
        closed = was_next ? (void **)next_open : closed;
        count_a = count_b;
        count_b = next_count;
        if (iter > 0x1f) break;
    }

    param_1[0x39] = 0;
    return 0;
}

// FUN_710031321c — call FUN_7100313000 with 5 args derived from param_1 fields
u64 FUN_710031321c(long param_1, long param_2) {
    FUN_7100313000(param_1,
                   (void *)(param_1 + 4),
                   (void *)(param_1 + 8),
                   (void *)(param_1 + 0xc),
                   (void *)(param_2 - 4));
    return 1;
}

// FUN_710031367c — call FUN_7100313460 with 5 args derived from param_1 fields
u64 FUN_710031367c(long param_1, long param_2) {
    FUN_7100313460(param_1,
                   (void *)(param_1 + 4),
                   (void *)(param_1 + 8),
                   (void *)(param_1 + 0xc),
                   (void *)(param_2 - 4));
    return 1;
}

// FUN_7100314d50 — check if action ID belongs to a hardcoded set of "important" actions
// Used to determine if an action requires special processing
extern u8 DAT_71045497f0;
bool FUN_7100314d50(u32 param_1) {
    switch (param_1) {
    case 0x00: case 0x03: case 0x11: case 0x23: case 0x32: case 0x3e:
    case 0x53: case 0x56: case 0x59: case 0x5f: case 0x62: case 0x65:
    case 0x68: case 0x6b: case 0x6e: case 0x71: case 0x7d: case 0x89:
    case 0x8c: case 0x9e: case 0xad: case 0xb0: case 0xb6: case 0xce:
    case 0xd1: case 0x101: case 0x12e: case 0x14c: case 0x14f:
    case 0x155: case 0x158: case 0x15b: case 0x15c: case 0x15f:
    case 0x163: case 0x166: case 0x169:
        return true;
    default:
        if (param_1 < 0x16c) {
            return (&DAT_71045497f0)[(long)(int)param_1 * 0x12] - 1 < 2;
        }
        return false;
    }
}

} // namespace lua_bind
} // namespace app
