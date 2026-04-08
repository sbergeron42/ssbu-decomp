// SSBU 13.0.4 — MEDIUM-tier decompilation batch B-003
// Address range: 0x71000a3920 – 0x7100149290

#include "types.h"

// ---------------------------------------------------------------------------
// 0x71000a3920  size=48  FUN_71000a3920
// Same as FUN_710009e130: count chain at struct+0x418
// ---------------------------------------------------------------------------
int FUN_71000a3920(long param_1)
{
    if (*(char *)(*(long *)(param_1 + 0x418) + 0x10) == '\0')
        return 0;
    int count = *(int *)(param_1 + 0x2c);
    for (long node = *(long *)(*(long *)(param_1 + 0x418) + 0x18); node != 0; node = *(long *)(node + 0x68))
        count++;
    return count;
}

// ---------------------------------------------------------------------------
// 0x71000af810  size=48  FUN_71000af810
// Index into a packed 3-byte-tuple table (bytes 8,9,10 → row, col, depth)
// ---------------------------------------------------------------------------
extern void *PTR_DAT_71052a3bc0;

long FUN_71000af810(long param_1)
{
    return *(long *)PTR_DAT_71052a3bc0 +
           ((u64)*(u8 *)(param_1 + 9)
            + (u64)*(u8 *)(param_1 + 8) * 4
            + (u64)*(u8 *)(param_1 + 10) * 0x10) * 0xa8;
}

// ---------------------------------------------------------------------------
// 0x71000b1b50  size=64  FUN_71000b1b50
// Look up 8-byte entry by index (2-based, range 2..26); default +200
// ---------------------------------------------------------------------------
extern void *PTR_DAT_71052a3c18;
extern u8 DAT_7104492890;

u64 FUN_71000b1b50(int param_1)
{
    if ((u32)(param_1 - 2) < 0x19u)
        return *(u64 *)((u8 *)PTR_DAT_71052a3c18 + *(long *)(&DAT_7104492890 + (long)(param_1 - 2) * 8) * 8);
    return *(u64 *)((u8 *)PTR_DAT_71052a3c18 + 200);
}

// ---------------------------------------------------------------------------
// 0x71000b1bb0  size=64  FUN_71000b1bb0
// Write table-looked-up value to global; fallback = 0x19
// ---------------------------------------------------------------------------
extern void *PTR_DAT_71052a3c10;
extern u8 DAT_7104492960;

void FUN_71000b1bb0(int param_1)
{
    if ((u32)(param_1 - 2) < 0x19u)
        *(u32 *)PTR_DAT_71052a3c10 = *(u32 *)(&DAT_7104492960 + (long)(param_1 - 2) * 4);
    else
        *(u32 *)PTR_DAT_71052a3c10 = 0x19;
}

// ---------------------------------------------------------------------------
// 0x71000b3c70  size=48  FUN_71000b3c70
// Divide counter DAT_7104f49390 by DAT_7104f49388; return 0 if divisor == 0
// ---------------------------------------------------------------------------
extern u64 DAT_7104f49388;
extern u64 DAT_7104f49390;

u64 FUN_71000b3c70(void)
{
    if (DAT_7104f49388 != 0)
        return DAT_7104f49390 / DAT_7104f49388;
    return 0;
}

// ---------------------------------------------------------------------------
// 0x71000b3d10  size=48  FUN_71000b3d10
// Divide counter DAT_7104f49430 by DAT_7104f49428; return 0 if divisor == 0
// ---------------------------------------------------------------------------
extern u64 DAT_7104f49428;
extern u64 DAT_7104f49430;

u64 FUN_71000b3d10(void)
{
    if (DAT_7104f49428 != 0)
        return DAT_7104f49430 / DAT_7104f49428;
    return 0;
}

// ---------------------------------------------------------------------------
// 0x71000b71c0  size=~  FUN_71000b71c0
// Pop head of linked list; decrement count field; return popped node or null
// ---------------------------------------------------------------------------
long *FUN_71000b71c0(u64 *param_1)
{
    int count = *(int *)(param_1 + 2);
    if (count != 0) {
        long *node = (long *)*param_1;
        long prev_link = *(long *)(node[1]);
        *(long *)(prev_link + 8) = node[1];
        *(long *)node[1] = prev_link;  // was: *(long *)plVar3[1] = lVar1
        // actually: splice out node from circular list
        long next_link = node[1];
        *(long *)(next_link + 8) = (long)(param_1);
        *(long *)param_1 = next_link;

        // rebuild per Ghidra
        long lVar1 = *node;
        *(long *)(lVar1 + 8) = node[1];
        *(long *)node[1] = lVar1;
        *node = 0;
        node[1] = 0;
        *(int *)(param_1 + 2) = count - 1;
        return node;
    }
    return nullptr;
}

// ---------------------------------------------------------------------------
// 0x71000b9d40  size=~  FUN_71000b9d40
// Map TLS error code to nn::err error result and dispatch
// ---------------------------------------------------------------------------
void FUN_71000bce50(u64, u32 *);

// nn::err constructor/operator= stubs for ErrorResultVariant
// These forward to the real SDK symbols; pointer tag bit 2 selects the vtable slot
static void nn_err_ErVarInit(void *self) { (void)self; }
static void nn_err_ErVarAssign(void *self, void *r) { (void)self; (void)r; }

void FUN_71000b9d40(u64 param_1, u32 param_2)
{
    u32 local_38[4] = {};
    u32 local_28[2] = {};

    switch (param_2) {
    default:              local_38[0] = 0x10c08; break;
    case 4: case 0xb: case 0xc: case 0x10: case 0x69:
                          local_38[0] = 0x4c0d;  break;
    case 9: case 0x16: case 0x58: case 0x59: case 0x5a:
    case 0x5b: case 0x5f: case 0x61: case 99:
                          local_38[0] = 0x10c07; break;
    case 0x20: case 100: case 0x65: case 0x68: case 0x6b:
    case 0x6e: case 0x6f: case 0x70: case 0x71:
                          local_38[0] = 0xc406;  break;
    }
    nn_err_ErVarInit((void *)((u64)local_38 | 4));
    nn_err_ErVarAssign((void *)((u64)local_38 | 4), local_28);
    FUN_71000bce50(param_1, local_38);
}

// ---------------------------------------------------------------------------
// 0x71000b9de0  size=~  FUN_71000b9de0
// Map TLS error code (variant B) to nn::err and dispatch
// ---------------------------------------------------------------------------
void FUN_71000b9de0(u64 param_1, u32 param_2)
{
    u32 local_38[4] = {};
    u32 local_28[2] = {};

    switch (param_2) {
    case 4: case 0xb: case 0xc: case 0x10: local_38[0] = 0x2c09;  break;
    default:                               local_38[0] = 0x10c08; break;
    case 9: case 0x16: case 0x58: case 0x5a: case 0x5f: case 0x61:
                                           local_38[0] = 0x10c07; break;
    case 100: case 0x68: case 0x6b: case 0x6e:
                                           local_38[0] = 0xc406;  break;
    }
    nn_err_ErVarInit((void *)((u64)local_38 | 4));
    nn_err_ErVarAssign((void *)((u64)local_38 | 4), local_28);
    FUN_71000bce50(param_1, local_38);
}

// ---------------------------------------------------------------------------
// 0x71000b9e80  size=~  FUN_71000b9e80
// Map TLS error code (variant C) to nn::err and dispatch
// ---------------------------------------------------------------------------
void FUN_71000b9e80(u64 param_1, u32 param_2)
{
    u32 local_38[4] = {};
    u32 local_28[2] = {};

    switch (param_2) {
    default:              local_38[0] = 0x10c08; break;
    case 9: case 0x16: case 0x58: case 0x5b: case 0x5c: case 0x5d:
    case 0x5f: case 0x61: case 99:
                          local_38[0] = 0x10c07; break;
    case 0x10:            local_38[0] = 0x4c0d;  break;
    case 0x62:            local_38[0] = 0xc35;   break;
    case 100: case 0x68: case 0x6b: case 0x6e:
                          local_38[0] = 0xc406;  break;
    }
    nn_err_ErVarInit((void *)((u64)local_38 | 4));
    nn_err_ErVarAssign((void *)((u64)local_38 | 4), local_28);
    FUN_71000bce50(param_1, local_38);
}

// ---------------------------------------------------------------------------
// 0x71000bb050  size=352  FUN_71000bb050
// Count UTF-8 code points in string (up to length field at +0x14)
// ---------------------------------------------------------------------------
u32 FUN_71000bb050(long param_1)
{
    u8 *str = *(u8 **)(param_1 + 8);
    if (str == nullptr)
        return 0;

    u32 len = *(u32 *)(param_1 + 0x14);
    if (len == 0)
        return 0;

    int mode = *(int *)(param_1 + 0x18);
    if (mode == 2)
        return len >> 1;
    if (mode != 1)
        return 0;

    u32 count = 0;
    u8 *p = str;
    while (true) {
        u8 b = *p;
        if (b == 0)
            return count;
        if ((long)(u64)len <= (long)(p - str))
            break;

        u32 seq;
        if ((s8)b < 0) {
            u32 ub = (u32)(s8)b;
            if (ub + 0x3e < 0x1e)       seq = 2;
            else if ((ub & ~0xfu) == (u32)-0x20) seq = 3;
            else if ((ub & ~0x7u) == (u32)-0x10) seq = 4;
            else if ((ub & ~0x3u) == (u32)-0x8)  seq = 5;
            else if ((b & 0xfe) == 0xfc) seq = 6;
            else                         seq = 0;
        } else {
            seq = 1;
        }

        if (seq != 0) count++;
        count++;
        p += seq ? seq : 1;
        if (seq == 0)
            return count - 1;
    }
    return count;
}

// ---------------------------------------------------------------------------
// 0x71000bb9f0  size=32  FUN_71000bb9f0
// Returns true for control bytes or 0xfd
// ---------------------------------------------------------------------------
bool FUN_71000bb9f0(u8 param_1)
{
    return param_1 < 0x20 || param_1 == 0xfd;
}

// ---------------------------------------------------------------------------
// 0x71000bed20  size=~  FUN_71000bed20
// Init node with vtable from PTR_DAT_71052a3d28, clear param_1[2]
// ---------------------------------------------------------------------------
extern u8 *PTR_DAT_71052a3d28;

void FUN_71000bed20(long *param_1)
{
    param_1[2] = 0;
    *param_1 = (long)(PTR_DAT_71052a3d28 + 0x10);
}

// ---------------------------------------------------------------------------
// 0x71000bf2f0  size=~  FUN_71000bf2f0
// Check magic signature and type tag; validate state field in range
// ---------------------------------------------------------------------------
bool FUN_71000bf2f0(long param_1)
{
    if (*(int *)(param_1 + 8) == 0x32ab9864 && (*(u8 *)(param_1 + 0xc) & 0x7f) == 4)
        return (u32)(*(int *)(param_1 + 0x5e8) - 0x20) < 0x5a1u;
    return false;
}

// ---------------------------------------------------------------------------
// 0x71000c4d40  size=~  FUN_71000c4d40
// If vtable bool method at +0x28 returns true, clear +0xc0 and return 1
// ---------------------------------------------------------------------------
long *FUN_71000c4d40(long param_1)
{
    long *vtobj = *(long **)(param_1 + 0x50);
    if (vtobj != nullptr) {
        u64 ok = (*(u64 (*)(void))(*vtobj + 0x28))();
        if ((ok & 1) == 0)
            return nullptr;
        *(u64 *)(param_1 + 0xc0) = 0;
        return (long *)1;
    }
    return vtobj;
}

// ---------------------------------------------------------------------------
// 0x71000cf5c0  size=~  FUN_71000cf5c0
// Init linked-list node with vtable, clear fields
// ---------------------------------------------------------------------------
extern u8 *PTR_DAT_71052a3ee8;

void FUN_71000cf5c0(long *param_1)
{
    *(u32 *)(param_1 + 1) = 0;
    *(u8 *)((u8 *)param_1 + 0xc) = 0;
    param_1[2] = 0;
    *param_1 = (long)(PTR_DAT_71052a3ee8 + 0x10);
    *(u32 *)(param_1 + 3) = 0;
}

// ---------------------------------------------------------------------------
// 0x71000e4340  size=~  FUN_71000e4340
// Map value 0 → 1, 1 → 2, other → 0
// ---------------------------------------------------------------------------
int FUN_71000e4340(int param_1)
{
    if (param_1 == 0) return 1;
    return (int)((u32)(param_1 == 1) << 1);
}

// ---------------------------------------------------------------------------
// 0x71000eb680  size=~  FUN_71000eb680
// Map 2 → 5, 1 → 4, other → 0
// ---------------------------------------------------------------------------
int FUN_71000eb680(int param_1)
{
    if (param_1 == 2) return 5;
    return (int)((u32)(param_1 == 1) << 2);
}

// ---------------------------------------------------------------------------
// 0x71000ee650  size=~  FUN_71000ee650
// Count active entries in a ring-buffer list matching param_2 type
// ---------------------------------------------------------------------------
extern void *PTR_DAT_71052a4080;
extern u8 DAT_000012e8;
extern u8 DAT_000012f0;
extern u8 DAT_000012f8;

int FUN_71000ee650(long param_1, int param_2)
{
    long lVar2 = *(long *)(param_1 + 0x2d8);
    if (lVar2 == 0 || *(long *)PTR_DAT_71052a4080 == 0)
        return 0;

    int *head;
    int *tail;

    if (*(int *)(lVar2 + 0x10) == param_2) {
        head = (int *)(lVar2 + 0x10);
        tail = head + 2;
        int *next = *(int **)(head + 4);
        if (next == tail) return 0;
        head = tail; tail = next;
        goto count;
    }
    if (*(int *)(lVar2 + 0x658) == param_2) {
        head = (int *)(lVar2 + 0x658);
    } else if (*(int *)(lVar2 + 0xca0) == param_2) {
        head = (int *)(lVar2 + 0xca8);
        tail = *(int **)(lVar2 + 0xcb0);
        if (tail == head) return 0;
        goto count;
    } else if (*(int *)(&DAT_000012e8 + lVar2) == param_2) {
        head = (int *)(&DAT_000012f0 + lVar2);
        tail = *(int **)(&DAT_000012f8 + lVar2);
        if (tail == head) return 0;
        goto count;
    } else {
        return 0;
    }
    {
        int *list_head = head + 2;
        tail = *(int **)(head + 4);
        if (tail == list_head) return 0;
        head = list_head;
    }
count:;
    int count = 0;
    int *it = tail;
    do {
        if (*(long *)(it + 4) != 0 &&
            *(long *)(it + 4) == *(long *)(it + 6) &&
            *(s16 *)((u8 *)it + 0x22) > 0)
            count++;
        it = *(int **)(it + 2);
    } while (it != head);
    return count;
}

// ---------------------------------------------------------------------------
// 0x7100112c40  size=~  FUN_7100112c40
// Copy 8 bytes from param_2+8 into param_1+0x260
// ---------------------------------------------------------------------------
void FUN_7100112c40(long param_1, long param_2)
{
    *(u16 *)(param_1 + 0x260) = *(u16 *)(param_2 + 8);
    *(u8  *)(param_1 + 0x262) = *(u8  *)(param_2 + 10);
    *(u8  *)(param_1 + 0x263) = *(u8  *)(param_2 + 0xb);
    *(u8  *)(param_1 + 0x264) = *(u8  *)(param_2 + 0xc);
    *(u8  *)(param_1 + 0x265) = *(u8  *)(param_2 + 0xd);
    *(u8  *)(param_1 + 0x266) = *(u8  *)(param_2 + 0xe);
    *(u8  *)(param_1 + 0x267) = *(u8  *)(param_2 + 0xf);
}

// ---------------------------------------------------------------------------
// 0x71001133a0  size=~  FUN_71001133a0
// Set wildcard SSID (0xffff) + target BSSID, mark dirty bit 2
// ---------------------------------------------------------------------------
void FUN_71001133a0(long param_1, u16 param_2)
{
    *(u16 *)(param_1 + 0xa38) = 0xffff;
    *(u16 *)(param_1 + 0xa3a) = param_2;
    *(u32 *)(param_1 + 0xd30) |= 2u;
}

// ---------------------------------------------------------------------------
// 0x71001133c0  size=~  FUN_71001133c0
// Set SSID + BSSID pair, mark dirty bit 2
// ---------------------------------------------------------------------------
void FUN_71001133c0(long param_1, u16 param_2, u16 param_3)
{
    *(u16 *)(param_1 + 0xa38) = param_3;
    *(u16 *)(param_1 + 0xa3a) = param_2;
    *(u32 *)(param_1 + 0xd30) |= 2u;
}

// ---------------------------------------------------------------------------
// 0x71001133e0  size=~  FUN_71001133e0
// Set bool at +0xa3c, mark dirty bit 4
// ---------------------------------------------------------------------------
void FUN_71001133e0(long param_1, u8 param_2)
{
    *(u8 *)(param_1 + 0xa3c) = param_2 & 1u;
    *(u32 *)(param_1 + 0xd30) |= 4u;
}

// ---------------------------------------------------------------------------
// 0x7100113400  size=~  FUN_7100113400
// Set bool at +0xa3d, mark dirty bit 8
// ---------------------------------------------------------------------------
void FUN_7100113400(long param_1, u8 param_2)
{
    *(u8 *)(param_1 + 0xa3d) = param_2 & 1u;
    *(u32 *)(param_1 + 0xd30) |= 8u;
}

// ---------------------------------------------------------------------------
// 0x7100113480  size=~  FUN_7100113480
// Set bool at +0x9ca, mark dirty bit 0x1000
// ---------------------------------------------------------------------------
void FUN_7100113480(long param_1, u8 param_2)
{
    *(u8 *)(param_1 + 0x9ca) = param_2 & 1u;
    *(u32 *)(param_1 + 0xd30) |= 0x1000u;
}

// ---------------------------------------------------------------------------
// 0x71001134a0  size=~  FUN_71001134a0
// Set bool at +0x9cb, mark dirty bit 0x2000
// ---------------------------------------------------------------------------
void FUN_71001134a0(long param_1, u8 param_2)
{
    *(u8 *)(param_1 + 0x9cb) = param_2 & 1u;
    *(u32 *)(param_1 + 0xd30) |= 0x2000u;
}

// ---------------------------------------------------------------------------
// 0x71001136c0  size=~  FUN_71001136c0
// Set bool at +0xa08, mark dirty bit 0x100000
// ---------------------------------------------------------------------------
void FUN_71001136c0(long param_1, u8 param_2)
{
    *(u8 *)(param_1 + 0xa08) = param_2 & 1u;
    *(u32 *)(param_1 + 0xd30) |= 0x100000u;
}

// ---------------------------------------------------------------------------
// 0x71001158e0  size=~  FUN_71001158e0
// Set mode (0 or 1) and bool flag at +0x14/+0x10; mark dirty bit 0x2000
// ---------------------------------------------------------------------------
void FUN_71001158e0(long param_1, u32 param_2, u8 param_3)
{
    if (param_2 < 2) {
        *(u8 *)(param_1 + 0x14) = param_3 & 1u;
        *(u32 *)(param_1 + 0x10) = param_2;
        *(u32 *)(param_1 + 0x628) |= 0x2000u;
    }
}

// ---------------------------------------------------------------------------
// 0x710011be80  size=~  FUN_710011be80
// Get slot pointer for index (0 or 1) within struct; null if out of range
// ---------------------------------------------------------------------------
extern u8 DAT_000011e8;

u8 *FUN_710011be80(long param_1, u8 param_2)
{
    if (param_2 > 1)
        return nullptr;
    return &DAT_000011e8 + param_1 + (u64)param_2 * 0x268;
}

// ---------------------------------------------------------------------------
// 0x710012b490  size=~  FUN_710012b490
// Trigger async event if channel 1 or 2, not already running
// ---------------------------------------------------------------------------
void FUN_71000b40e0(long);
void FUN_71000b4160(long);

u64 FUN_710012b490(long param_1, s8 param_2)
{
    if ((u8)((u8)(param_2 - 1) - 1u) > 1u)
        return 0;
    if (*(int *)(param_1 + 0xd88) == 1)
        return 0;
    *(u8 *)(param_1 + 0xd81) = 1;
    *(s8 *)(param_1 + 0xd80) = param_2;
    FUN_71000b40e0(param_1 + 0xd88);
    FUN_71000b4160(param_1 + 0xd88);
    return 1;
}

// ---------------------------------------------------------------------------
// 0x710012eb20  size=~  FUN_710012eb20
// Set both copies of field_256/600 and mark dirty bit 1
// ---------------------------------------------------------------------------
void FUN_710012eb20(long param_1, u16 param_2)
{
    *(u16 *)(param_1 + 0x256) = param_2;
    *(u16 *)(param_1 + 600) = param_2;
    *(u32 *)(param_1 + 0x260) |= 1u;
}

// ---------------------------------------------------------------------------
// 0x710012eb40  size=~  FUN_710012eb40
// Set two consecutive fields at +0x25a/+0x25c and mark dirty bit 2
// ---------------------------------------------------------------------------
void FUN_710012eb40(long param_1, u16 param_2)
{
    *(u16 *)(param_1 + 0x25a) = param_2;
    *(u16 *)(param_1 + 0x25c) = param_2;
    *(u32 *)(param_1 + 0x260) |= 2u;
}

// ---------------------------------------------------------------------------
// 0x710012eb60  size=~  FUN_710012eb60
// Set bool at +0x25e and mark dirty bit 4
// ---------------------------------------------------------------------------
void FUN_710012eb60(long param_1, u8 param_2)
{
    *(u8 *)(param_1 + 0x25e) = param_2 & 1u;
    *(u32 *)(param_1 + 0x260) |= 4u;
}

// ---------------------------------------------------------------------------
// 0x710012eb80  size=~  FUN_710012eb80
// Set bool at +0x25f and mark dirty bit 8
// ---------------------------------------------------------------------------
void FUN_710012eb80(long param_1, u8 param_2)
{
    *(u8 *)(param_1 + 0x25f) = param_2 & 1u;
    *(u32 *)(param_1 + 0x260) |= 8u;
}

// ---------------------------------------------------------------------------
// 0x7100130aa0  size=~  FUN_7100130aa0
// Prepend node param_2 to singly-linked-like list at param_1+8
// ---------------------------------------------------------------------------
void FUN_7100130aa0(long param_1, long *param_2)
{
    u64 *old_head = *(u64 **)(param_1 + 8);
    *(long **)(param_1 + 8) = param_2;
    *param_2 = param_1;
    param_2[1] = (long)old_head;
    if (old_head != nullptr)
        *old_head = (u64)param_2;
}

// ---------------------------------------------------------------------------
// 0x7100130ac0  size=~  FUN_7100130ac0
// Insert param_2 at head of list param_1
// ---------------------------------------------------------------------------
void FUN_7100130ac0(long *param_1, long *param_2)
{
    long old = *param_1;
    *param_1 = (long)param_2;
    *param_2 = old;
    param_2[1] = (long)param_1;
    if (old != 0)
        *(long **)(old + 8) = param_2;
}

// ---------------------------------------------------------------------------
// 0x7100130b10  size=~  FUN_7100130b10
// Drain circular list: zero all nodes, reset head/tail to self
// ---------------------------------------------------------------------------
void FUN_7100130b10(u64 *param_1)
{
    u64 *it = (u64 *)param_1[1];
    while (it != param_1) {
        u64 *next = (u64 *)it[1];
        *it = 0;
        it[1] = 0;
        it = next;
    }
    *(u32 *)(param_1 + 2) = 0;
    *param_1 = (u64)param_1;
    param_1[1] = (u64)param_1;
}

// ---------------------------------------------------------------------------
// 0x71001353c0  size=~  FUN_71001353c0
// Init slice-view struct if count > 0 and ptr != 0
// ---------------------------------------------------------------------------
void FUN_71001353c0(u32 *param_1, int param_2, long param_3)
{
    if (param_2 > 0 && param_3 != 0) {
        *(long *)(param_1 + 2) = param_3;
        param_1[0] = 0;
        param_1[1] = (u32)param_2;
    }
}

// ---------------------------------------------------------------------------
// 0x71001354c0  size=~  FUN_71001354c0
// popcount32 (Hamming weight)
// ---------------------------------------------------------------------------
u32 FUN_71001354c0(u32 param_1)
{
    u32 v = param_1;
    v = v - ((v >> 1) & 0x55555555u);
    v = (v & 0x33333333u) + ((v >> 2) & 0x33333333u);
    v = (v + (v >> 4)) & 0x0f0f0f0fu;
    v += v >> 8;
    return (v + (v >> 16)) & 0x3fu;
}

// ---------------------------------------------------------------------------
// 0x7100135500  size=~  FUN_7100135500
// Find index of the (param_2)th least-significant set bit; -1 if not found
// ---------------------------------------------------------------------------
u32 FUN_7100135500(u32 param_1, int param_2)
{
    if (param_1 == 0)
        return 0xffffffff;

    int n = param_2 + 1;
    do {
        n--;
        if (n < 2) {
            // popcount of (lsb - 1)
            u32 v = (param_1 & (u32)(-(int)param_1)) - 1;
            v = v - ((v >> 1) & 0x55555555u);
            v = (v & 0x33333333u) + ((v >> 2) & 0x33333333u);
            v = (v + (v >> 4)) & 0x0f0f0f0fu;
            v += v >> 8;
            return (v + (v >> 16)) & 0x3fu;
        }
        param_1 = (param_1 - 1) & param_1;
    } while (param_1 != 0);
    return 0xffffffff;
}

// ---------------------------------------------------------------------------
// 0x710013c200  size=~  FUN_710013c200
// Start thread if not already started; set running flag
// ---------------------------------------------------------------------------
namespace nn { namespace os { struct ThreadType; void StartThread(ThreadType *); } }

u64 FUN_710013c200(long param_1)
{
    if (*(int *)(param_1 + 0xcc) != 0)
        return 0;
    nn::os::StartThread(*(nn::os::ThreadType **)(param_1 + 0xd0));
    *(int *)(param_1 + 200) = (int)*(u64 *)(param_1 + 0xd0);
    if (*(int *)(param_1 + 0xcc) != 0)
        return 1;
    *(u32 *)(param_1 + 0xcc) = 1;
    return 1;
}

// ---------------------------------------------------------------------------
// 0x710013dc90  size=~  FUN_710013dc90
// Copy 7-byte address/config blob from param_2+8 to param_1+8
// ---------------------------------------------------------------------------
void FUN_710013dc90(long param_1, long param_2)
{
    *(u16 *)(param_1 + 8)  = *(u16 *)(param_2 + 8);
    *(u8  *)(param_1 + 10) = *(u8  *)(param_2 + 10);
    *(u16 *)(param_1 + 0xc) = *(u16 *)(param_2 + 0xc);
    *(u8  *)(param_1 + 0xe) = *(u8  *)(param_2 + 0xe);
}

// ---------------------------------------------------------------------------
// 0x7100145a10 – 0x7100146a90  size=32 each
// Check role field (param_1+0x140) == N and state in range [2,4]
// ---------------------------------------------------------------------------
bool FUN_7100145a10(long param_1) { return *(int *)(param_1+0x140)==1  && (u32)(*(int *)(param_1+0x110)-2)<3; }
bool FUN_7100145ce0(long param_1) { return *(int *)(param_1+0x140)==2  && (u32)(*(int *)(param_1+0x110)-2)<3; }
bool FUN_7100145ec0(long param_1) { return *(int *)(param_1+0x140)==3  && (u32)(*(int *)(param_1+0x110)-2)<3; }
bool FUN_7100146070(long param_1) { return *(int *)(param_1+0x140)==4  && (u32)(*(int *)(param_1+0x110)-2)<3; }
bool FUN_71001462a0(long param_1) { return *(int *)(param_1+0x140)==5  && (u32)(*(int *)(param_1+0x110)-2)<3; }
bool FUN_7100146670(long param_1) { return *(int *)(param_1+0x140)==7  && (u32)(*(int *)(param_1+0x110)-2)<3; }
bool FUN_71001468b0(long param_1) { return *(int *)(param_1+0x140)==8  && (u32)(*(int *)(param_1+0x110)-2)<3; }
bool FUN_7100146a90(long param_1) { return *(int *)(param_1+0x140)==0x13 && (u32)(*(int *)(param_1+0x110)-2)<3; }
bool FUN_7100149180(long param_1) { return *(int *)(param_1+0x140)==0x1a && (u32)(*(int *)(param_1+0x110)-2)<3; }

// ---------------------------------------------------------------------------
// 0x7100149270  size=~  FUN_7100149270
// Store param_2 at dynamic slot; if non-zero, also update global
// ---------------------------------------------------------------------------
extern void *PTR_DAT_71052a3bd0;

void FUN_7100149270(long param_1, int param_2)
{
    *(int *)(param_1 + (u64)*(u8 *)(param_1 + 0x162) * 4 + 0x180) = param_2;
    if (param_2 != 0)
        *(int *)((u8 *)PTR_DAT_71052a3bd0 + 0x124) = param_2;
}

// ---------------------------------------------------------------------------
// 0x7100149290  size=~  FUN_7100149290
// Store param_2 at inverted-flag slot; if non-zero, also update other global
// ---------------------------------------------------------------------------
extern void *PTR_DAT_71052a3bd8;

void FUN_7100149290(long param_1, int param_2)
{
    *(int *)(param_1 + (u64)(*(char *)(param_1 + 0x162) == '\0') * 4 + 0x180) = param_2;
    if (param_2 != 0)
        *(int *)((u8 *)PTR_DAT_71052a3bd8 + 0x300) = param_2;
}
