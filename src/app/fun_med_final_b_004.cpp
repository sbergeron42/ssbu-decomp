// SSBU 13.0.4 — MEDIUM-tier decompilation batch B-004
// Address range: 0x710014f090 – 0x71001aca20

#include "types.h"

// ---------------------------------------------------------------------------
// 0x710014f090  size=~  FUN_710014f090
// Copy 3×uint32 fields from param_2+8 to param_1+8
// ---------------------------------------------------------------------------
void FUN_710014f090(long param_1, long param_2)
{
    *(u32 *)(param_1 + 0x10) = *(u32 *)(param_2 + 0x10);
    *(u32 *)(param_1 + 8)    = *(u32 *)(param_2 + 8);
    *(u32 *)(param_1 + 0xc)  = *(u32 *)(param_2 + 0xc);
}

// ---------------------------------------------------------------------------
// 0x710014f150  size=~  FUN_710014f150
// Init node: set vtable from PTR_DAT_71052a4f38, clear param_1[1]
// ---------------------------------------------------------------------------
__attribute__((visibility("hidden"))) extern u8 *PTR_DAT_71052a4f38;

void FUN_710014f150(long *param_1)
{
    u8 *puVar1 = PTR_DAT_71052a4f38;
    *(u32 *)(param_1 + 1) = 0;
    *param_1 = (long)(puVar1 + 0x10);
}

// ---------------------------------------------------------------------------
// 0x710014fde0  size=~  FUN_710014fde0
// Vtable dispatch: call slot +0x20 (no args), then slot +0x10 with (self, 1)
// ---------------------------------------------------------------------------
void FUN_710014fde0(long *param_1)
{
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
    (*(void (**)(void))(*param_1 + 0x20))();
    (*(void (**)(long *, int))(*param_1 + 0x10))(param_1, 1);
}

// ---------------------------------------------------------------------------
// 0x7100150720  size=~  FUN_7100150720
// Linked-list search: find node with key at +0x20, return bool at +0x2e
// ---------------------------------------------------------------------------
bool FUN_7100150720(long param_1, long param_2)
{
    long it = *(long *)(param_1 + 0x10);
    if (it == param_1 + 8)
        return false;
    do {
        if (*(long *)(it + 0x20) == param_2)
            return *(char *)(it + 0x2e) != '\0';
        it = *(long *)(it + 8);
    } while (it != param_1 + 8);
    return false;
}

// ---------------------------------------------------------------------------
// 0x7100150900  size=~  FUN_7100150900
// Walk linked list, clear u32 at +0x14 in each node
// ---------------------------------------------------------------------------
void FUN_7100150900(long param_1)
{
    for (long it = *(long *)(param_1 + 0x10); it != param_1 + 8; it = *(long *)(it + 8))
        *(u32 *)(it + 0x14) = 0;
}

// ---------------------------------------------------------------------------
// 0x7100150de0  size=~  FUN_7100150de0
// Linked-list lookup: get byte at +0x2d by key; returns 1/0 found/not-found
// ---------------------------------------------------------------------------
u64 FUN_7100150de0(long param_1, long param_2, u8 *param_3)
{
    long it = *(long *)(param_1 + 0x10);
    if (it == param_1 + 8)
        return 0;
    do {
        if (*(long *)(it + 0x20) == param_2) {
            *param_3 = *(u8 *)(it + 0x2d);
            return 1;
        }
        it = *(long *)(it + 8);
    } while (it != param_1 + 8);
    return 0;
}

// ---------------------------------------------------------------------------
// 0x7100150e30  size=~  FUN_7100150e30
// Linked-list update: set bool at +0x2c in the node with key param_2
// ---------------------------------------------------------------------------
void FUN_7100150e30(long param_1, long param_2, u8 param_3)
{
    long it = *(long *)(param_1 + 0x10);
    if (it == param_1 + 8)
        return;
    do {
        if (*(long *)(it + 0x20) == param_2) {
            *(u8 *)(it + 0x2c) = param_3 & 1u;
            return;
        }
        it = *(long *)(it + 8);
    } while (it != param_1 + 8);
}

// ---------------------------------------------------------------------------
// 0x7100150ec0  size=~  FUN_7100150ec0
// Count nodes in linked list where field at +0x28 == param_2
// ---------------------------------------------------------------------------
int FUN_7100150ec0(long param_1, int param_2)
{
    long it = *(long *)(param_1 + 0x10);
    if (it == param_1 + 8)
        return 0;
    int count = 0;
    do {
        if (*(int *)(it + 0x28) == param_2)
            count++;
        it = *(long *)(it + 8);
    } while (it != param_1 + 8);
    return count;
}

// ---------------------------------------------------------------------------
// 0x7100151fe0  size=~  FUN_7100151fe0
// Check bitfield: both flags set and index < 6, return bit from 0x31 bitmask
// ---------------------------------------------------------------------------
u32 FUN_7100151fe0(long param_1)
{
    if (*(char *)(param_1 + 0x48) != '\0' &&
        *(char *)(param_1 + 0x50) != '\0' &&
        *(u32 *)(param_1 + 0x78) < 6u)
        return (0x31u >> (*(u32 *)(param_1 + 0x78) & 0x1f)) & 1u;
    return 0;
}

// ---------------------------------------------------------------------------
// 0x7100153200  size=~  FUN_7100153200
// Return 1 if param_2 is a valid SSBU network protocol ID, else 0
// ---------------------------------------------------------------------------
u64 FUN_7100153200(u64 param_1, u8 param_2)
{
    switch (param_2) {
    case 0x08: case 0x14: case 0x18: case 0x1c: case 0x24: case 0x28: case 0x2c:
    case 0x34: case 0x44: case 0x54: case 0x58: case 0x65: case 0x68: case 0x6c:
    case 0x73: case 0x74: case 0x76: case 0x77: case 0x78: case 0x7b: case 0x7c:
    case 0x80: case 0x81: case 0x84: case 0x94: case 0xa4: case 0xa8: case 0xac:
    case 0xb0: case 0xb4:
        return 1;
    default:
        return 0;
    }
}

// ---------------------------------------------------------------------------
// 0x7100153d50  size=~  FUN_7100153d50
// Store param_2 at slot +0x1b, call vtable +0x98, return ptr to +0x1d
// ---------------------------------------------------------------------------
long *FUN_7100153d50(long *param_1, u32 *param_2)
{
    *(u32 *)(param_1 + 0x1b) = *param_2;
    (*(void (**)(void))(*param_1 + 0x98))();
    return param_1 + 0x1d;
}

// ---------------------------------------------------------------------------
// 0x7100154c10  size=~  FUN_7100154c10
// Linear search in stride-6 int array; return index or -1
// ---------------------------------------------------------------------------
u64 FUN_7100154c10(int *param_1, int param_2)
{
    int *end = param_1 + 0xc0;
    if (*end < 1)
        return 0xffffffff;
    u64 i = 0;
    do {
        if (*param_1 == param_2)
            return i & 0xffffffff;
        i++;
        param_1 += 6;
    } while ((long)i < (long)*end);
    return 0xffffffff;
}

// ---------------------------------------------------------------------------
// 0x7100154c60  size=~  FUN_7100154c60
// Append param_2 to circular 0x20-slot array at param_1+0x300; return idx/-1
// ---------------------------------------------------------------------------
int FUN_7100154c60(long param_1, u32 param_2)
{
    if (*(int *)(param_1 + 0x300) < 0x20) {
        int idx = *(int *)(param_1 + 0x300);
        *(u32 *)(param_1 + (long)idx * 0x18) = param_2;
        *(int *)(param_1 + 0x300) = idx + 1;
        return idx;
    }
    return -1;
}

// ---------------------------------------------------------------------------
// 0x7100154f10  size=~  FUN_7100154f10
// Advance round-robin index in array; return base + old_index * 0x658
// ---------------------------------------------------------------------------
long FUN_7100154f10(long param_1)
{
    u32 cap   = *(u32 *)(param_1 + 0x10);
    u32 idx   = *(u32 *)(param_1 + 0x14);
    u32 next  = idx + 1;
    u32 wrap  = cap ? next / cap : 0;
    int rem   = (int)(next - wrap * cap);
    if (rem == *(int *)(param_1 + 0x1c))
        return 0;
    *(int *)(param_1 + 0x14) = rem;
    return *(long *)(param_1 + 8) + (u64)idx * 0x658;
}

// ---------------------------------------------------------------------------
// 0x7100154f50  size=~  FUN_7100154f50
// Peek ahead by param_2 slots; return 0 if already at that slot
// ---------------------------------------------------------------------------
long FUN_7100154f50(long param_1, int param_2)
{
    u32 cap  = *(u32 *)(param_1 + 0x10);
    u32 sum  = (u32)(*(int *)(param_1 + 0x18) + param_2);
    u32 wrap = cap ? sum / cap : 0;
    u32 rem  = sum - wrap * cap;
    if (*(u32 *)(param_1 + 0x14) == rem)
        return 0;
    return *(long *)(param_1 + 8) + (u64)rem * 0x658;
}

// ---------------------------------------------------------------------------
// 0x7100155000  size=~  FUN_7100155000
// Flush deferred index: if pending >= 0, commit to +0x1c and reset to -1
// ---------------------------------------------------------------------------
void FUN_7100155000(long param_1)
{
    if ((long)*(long *)(param_1 + 0x20) >= 0) {
        *(int *)(param_1 + 0x1c) = (int)*(long *)(param_1 + 0x20);
        *(u64 *)(param_1 + 0x20) = 0xffffffffffffffffULL;
    }
}

// ---------------------------------------------------------------------------
// 0x7100156720  size=~  FUN_7100156720
// Protocol-ID to name string lookup (SSBU LDN/network protocol names)
// ---------------------------------------------------------------------------
const char *FUN_7100156720(u64 param_1)
{
    switch ((u32)((param_1 >> 0x18) & 0xff)) {
    default:   return "(KickoutReason_Unknown PROTOCOL NAME)";
    case 0x08: return "KeepAlive";
    case 0x14: return "Station";
    case 0x18: return "Mesh";
    case 0x1c: return "SyncClock";
    case 0x24: return "Local";
    case 0x28: return "Direct";
    case 0x2c: return "Net";
    case 0x34: return "Nat";
    case 0x44: return "Lan";
    case 0x54: return "BandwidthCheck";
    case 0x58: return "Rtt";
    case 0x65: return "Sync";
    case 0x68: return "Unreliable";
    case 0x6c: return "RoundrobinUnreliable";
    case 0x73: return "Clone";
    case 0x74: return "Atomic";
    case 0x76: return "Event";
    case 0x77: return "Clock";
    case 0x78: return "InterpolationClock";
    case 0x7b: return "Voice";
    case 0x7c: return "Reliable";
    case 0x80: return "BroadcastReliable";
    case 0x81: return "StreamBroadcastReliable";
    case 0x84: return "ReliableBroadcast";
    case 0x94: return "Session";
    case 0x98: return "Lobby";
    case 0xa4: return "Feedback";
    case 0xa8: return "RelayService";
    case 0xac: return "WanNat";
    }
}

// ---------------------------------------------------------------------------
// 0x7100156d00  size=~  FUN_7100156d00
// Protocol-ID to channel bitmask
// ---------------------------------------------------------------------------
u64 FUN_7100156d00(u16 param_1)
{
    switch (param_1) {
    default:   return 0;
    case 0x14: return 2;
    case 0x18: return 4;
    case 0x1c: return 8;
    case 0x24: return 0x80000;
    case 0x28: return 0x100000;
    case 0x2c: return 0x200000;
    case 0x34: return 0x10;
    case 0x44: return 0x20000;
    case 0x54: return 0x40000;
    case 0x58: return 0x20;
    case 0x65: return 0x40;
    case 0x68: return 0x80;
    case 0x6c: return 0x1000;
    case 0x73: return 0x4000;
    case 0x74: return 0x4000000;
    case 0x76: return 0x800000;
    case 0x77: return 0x2000000;
    case 0x78: return 0x2000;
    case 0x7b: return 0x8000;
    case 0x7c: return 0x100;
    case 0x80: return 0x10000000;
    case 0x81: return 0x20000000;
    case 0x84: return 0x200;
    case 0x94: return 0x10000;
    case 0x98: return 0x400000;
    case 0xa4: return 0x400;
    case 0xac: return 0x8000000;
    case 0xb0: return 0x40000000;
    case 0xb4: return 0x80000000;
    }
}

// ---------------------------------------------------------------------------
// 0x71001578e0  size=~  FUN_71001578e0
// Check if char param_2 is NOT in byte array at param_1+0x29 of len [+0x4c]
// ---------------------------------------------------------------------------
u64 FUN_71001578e0(long param_1, char param_2)
{
    if (*(int *)(param_1 + 0x4c) < 1)
        return 1;
    long i = 0;
    do {
        if (*(char *)(param_1 + 0x29 + i) == param_2)
            return 0;
        i++;
    } while (i < *(int *)(param_1 + 0x4c));
    return 1;
}

// ---------------------------------------------------------------------------
// 0x7100158070  size=~  FUN_7100158070
// Store 6 connection config fields; clear a00 region
// ---------------------------------------------------------------------------
void FUN_7100158070(long param_1, u32 *param_2, u32 param_3, u8 param_4, u8 param_5)
{
    *(u32 *)(param_1 + 0x608) = param_3;
    u32 v = *param_2;
    *(u8  *)(param_1 + 0x61c) = param_4 & 1u;
    *(u8  *)(param_1 + 0xa04) = 0;
    *(u32 *)(param_1 + 0xa00) = 0;
    *(u32 *)(param_1 + 0x618) = v;
    *(u8  *)(param_1 + 0x61d) = param_5 & 1u;
}

// ---------------------------------------------------------------------------
// 0x71001583c0  size=~  FUN_71001583c0
// Append entry to ring-buffer array at param_1+0x620; increment count
// ---------------------------------------------------------------------------
void FUN_71001583c0(long param_1, u64 param_2, u64 param_3, u64 param_4,
                    u8 param_5, u8 param_6, u8 param_7)
{
    u32 idx  = *(u32 *)(param_1 + 0xa00);
    long slot = param_1 + (u64)idx * 0x20;
    *(u8  *)(slot + 0x638) = param_6 & 1u;
    *(u64 *)(slot + 0x620) = param_2;
    *(u64 *)(slot + 0x628) = param_3;
    *(u64 *)(slot + 0x630) = param_4;
    *(u8  *)(slot + 0x639) = param_7 & 1u;
    *(u8  *)(slot + 0x63a) = param_5 & 1u;
    *(u32 *)(param_1 + 0xa00) = idx + 1;
}

// ---------------------------------------------------------------------------
// 0x710015d240  size=~  FUN_710015d240
// Set timeout at +0x488: global_tick_rate * param_2 / 1000
// ---------------------------------------------------------------------------
__attribute__((visibility("hidden"))) extern long *PTR_DAT_71052a3cd0;

void FUN_710015d240(long param_1, u32 param_2)
{
    *(long *)(param_1 + 0x488) = (long)(*PTR_DAT_71052a3cd0 * (u64)param_2) / 1000;
}

// ---------------------------------------------------------------------------
// 0x710015e850  size=~  FUN_710015e850
// If connection active and not in state -3: get socket fd, else -1
// ---------------------------------------------------------------------------
u64 FUN_710015f5c0(long);

u64 FUN_710015e850(long param_1)
{
    long conn = *(long *)(param_1 + 0x50);
    if (conn != 0 && *(s8 *)(param_1 + 0x38) != -3)
        return FUN_710015f5c0(conn);
    return 0xffffffff;
}

// ---------------------------------------------------------------------------
// 0x710015e880  size=~  FUN_710015e880
// If connection active and not state -3: call FUN_710015f600 with socket/state
// ---------------------------------------------------------------------------
u64 FUN_710015f600(long, s8, u32);

u64 FUN_710015e880(long param_1, u32 param_2)
{
    if (*(long *)(param_1 + 0x50) != 0 && *(s8 *)(param_1 + 0x38) != -3)
        return FUN_710015f600(*(long *)(param_1 + 0x50), *(s8 *)(param_1 + 0x38), param_2);
    return 0xffffffff;
}

// ---------------------------------------------------------------------------
// 0x710015fb50  size=~  FUN_710015fb50
// Clear connection slot: invalidate MAC/keys, zero many fields
// ---------------------------------------------------------------------------
void FUN_710015fb50(char *param_1)
{
    if (*param_1 == '\0')
        return;
    param_1[4] = -1; param_1[5] = -1; param_1[6] = -1; param_1[7] = -1;
    param_1[8] = -1; param_1[9] = -1; param_1[0xa] = -1; param_1[0xb] = -1;
    *param_1 = '\0';
    param_1[0x10] = '\0'; param_1[0x11] = '\0'; param_1[0x12] = '\0';
    param_1[0x13] = '\0'; param_1[0x14] = '\0'; param_1[0x15] = '\0';
    param_1[0x16] = '\0'; param_1[0x17] = '\0'; param_1[0x18] = '\0';
    param_1[0x48] = '\0'; param_1[0x49] = '\0'; param_1[0x4a] = '\0';
    param_1[0x4b] = '\0'; param_1[0x4c] = '\0'; param_1[0x4d] = '\0';
    param_1[0x4e] = '\0'; param_1[0x4f] = '\0';
    param_1[0x1c] = '\0'; param_1[0x1d] = '\0'; param_1[0x1e] = '\0';
    param_1[0x1f] = '\0'; param_1[0x20] = '\0'; param_1[0x21] = '\0';
    param_1[0x22] = '\0'; param_1[0x23] = '\0';
    param_1[0xc] = -1; param_1[0xd] = -1; param_1[0xe] = -1; param_1[0xf] = -1;
    param_1[0x50] = '\0'; param_1[0x51] = '\0'; param_1[0x52] = '\0';
    param_1[0x53] = '\0';
}

// ---------------------------------------------------------------------------
// 0x71001604a0  size=~  FUN_71001604a0
// Pack 2-bit field (param_2 & 3) into bits [2:3] of byte at +0x78
// ---------------------------------------------------------------------------
void FUN_71001604a0(long param_1, u32 param_2)
{
    *(u8 *)(param_1 + 0x78) = (*(u8 *)(param_1 + 0x78) & 0xf3u) | (u8)((param_2 & 3u) << 2);
}

// ---------------------------------------------------------------------------
// 0x7100162ce0  size=~  FUN_7100162ce0
// Clamp field at +0xa4 to [1..254]; write to PTR_DAT_71052a3bd8[0x2b6]
// ---------------------------------------------------------------------------
__attribute__((visibility("hidden"))) extern u8 *PTR_DAT_71052a3bd8;

void FUN_7100162ce0(long param_1)
{
    int v = *(int *)(param_1 + 0xa4);
    if ((u32)(v - 1) > 0xfdu)
        v = 0xff;
    PTR_DAT_71052a3bd8[0x2b6] = (char)v;
}

// ---------------------------------------------------------------------------
// 0x7100163d40  size=~  FUN_7100163d40
// Same as FUN_7100162ce0 but writes to index [0x2b7]
// ---------------------------------------------------------------------------
void FUN_7100163d40(long param_1)
{
    int v = *(int *)(param_1 + 0xa4);
    if ((u32)(v - 1) > 0xfdu)
        v = 0xff;
    PTR_DAT_71052a3bd8[0x2b7] = (char)v;
}

// ---------------------------------------------------------------------------
// 0x7100164070  size=~  FUN_7100164070
// Zero 0x400-byte struct in 32-byte strides, then clear trailing u32
// ---------------------------------------------------------------------------
void FUN_7100164070(long param_1)
{
    long off = 0;
#pragma clang loop unroll(disable)
    do {
        u64 *p = (u64 *)(param_1 + off);
        off += 0x20;
        *p = 0;
        p[1] = 0;
        p[2] = 0;
        *(u32 *)(p + 3) = 0;
        *(u8 *)((u8 *)p + 0x1c) = 0;
    } while (off != 0x400);
    *(u32 *)(param_1 + 0x400) = 0;
}

// ---------------------------------------------------------------------------
// 0x7100174530  size=~  FUN_7100174530
// Vtable dispatch at slot +0x30; clear byte[9] to 0
// ---------------------------------------------------------------------------
void FUN_7100174530(long *param_1)
{
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
    (*(void (**)(void))(*param_1 + 0x30))();
    *(u8 *)((u8 *)param_1 + 9) = 0;
}

// ---------------------------------------------------------------------------
// 0x7100174cb0  size=~  FUN_7100174cb0
// Check active connection: bool at +0x418 of nested pointer at +0x18
// ---------------------------------------------------------------------------
bool FUN_7100174cb0(long param_1)
{
    if (*(char *)(param_1 + 8) == '\0')
        return false;
    if (*(long *)(param_1 + 0x18) != 0)
        return *(int *)(*(long *)(param_1 + 0x18) + 0x418) != 0;
    return false;
}

// ---------------------------------------------------------------------------
// 0x7100174ff0  size=~  FUN_7100174ff0
// Attach param_2 to param_1+0x18, call vtable+0x178 with a stack buffer
// ---------------------------------------------------------------------------
void FUN_7100174ff0(long param_1, long *param_2)
{
    u8 tmp[16];
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
    *(long **)(param_1 + 0x18) = param_2;
    (*(void (**)(u8 *, long *, u64))(*param_2 + 0x178))(tmp, param_2, *(u64 *)(param_1 + 0x10));
}

// ---------------------------------------------------------------------------
// 0x7100175030  size=~  FUN_7100175030
// Disconnect: call vtable+0x180 on param_1+0x18 if set; then clear it
// ---------------------------------------------------------------------------
void FUN_7100175030(long param_1)
{
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
    long *ptr = *(long **)(param_1 + 0x18);
    if (ptr != nullptr)
        (*(void (**)(void))(*ptr + 0x180))();
    *(u64 *)(param_1 + 0x18) = 0;
}

// ---------------------------------------------------------------------------
// 0x7100181270  size=~  FUN_7100181270
// Conditional: return field +0x46c; skip if connection active and state checks fail
// ---------------------------------------------------------------------------
u64 FUN_71000b2850(long);
u64 FUN_71000b2b10(long, long);

u32 FUN_7100181270(long param_1)
{
    if (*(int *)(param_1 + 0x418) == 0) {
        long a = param_1 + 0x2c0;
        u64 r1 = FUN_71000b2850(a);
        if (r1 & 1) {
            u64 r2 = FUN_71000b2850(param_1 + 0x2a0);
            if ((r2 & 1) && (FUN_71000b2b10(param_1 + 0x2a0, a) & 1))
                goto done;
        }
        if (!(FUN_71000b2850(a) & 1))         return 0;
        if (!(FUN_71000b2850(param_1 + 0x2a0) & 1)) return 0;
        if (FUN_71000b2b10(param_1 + 0x2a0, a) & 1)  return 0;
    }
done:
    return *(u32 *)(param_1 + 0x46c);
}

// ---------------------------------------------------------------------------
// 0x7100182c70  size=~  FUN_7100182c70
// Init packet node: vtable from PTR_DAT_71052a53d8, type=0x12, size=0x10
// ---------------------------------------------------------------------------
__attribute__((visibility("hidden"))) extern u8 *PTR_DAT_71052a53d8;

void FUN_7100182c70(long *param_1, long param_2, u16 param_3)
{
    *(u16 *)(param_1 + 2) = param_3;
    *(u16 *)(param_1 + 3) = 0;
    *param_1 = (long)(PTR_DAT_71052a53d8 + 0x10);
    param_1[1] = param_2;
    *(u8 *)((u8 *)param_1 + 0x12) = 0x12;
    *(u32 *)((u8 *)param_1 + 0x14) = 0x10;
}

// ---------------------------------------------------------------------------
// 0x7100182d10  size=~  FUN_7100182d10
// Init packet node: vtable from PTR_DAT_71052a53e0, type=0x13
// ---------------------------------------------------------------------------
__attribute__((visibility("hidden"))) extern u8 *PTR_DAT_71052a53e0;

void FUN_7100182d10(long *param_1, long param_2, u16 param_3)
{
    *(u16 *)(param_1 + 2) = param_3;
    *(u16 *)(param_1 + 3) = 0;
    *param_1 = (long)(PTR_DAT_71052a53e0 + 0x10);
    param_1[1] = param_2;
    *(u8 *)((u8 *)param_1 + 0x12) = 0x13;
    *(u32 *)((u8 *)param_1 + 0x14) = 0x10;
}

// ---------------------------------------------------------------------------
// 0x7100182db0  size=~  FUN_7100182db0
// Init extended packet node: vtable from PTR_DAT_71052a53e8, parameterized type
// ---------------------------------------------------------------------------
__attribute__((visibility("hidden"))) extern u8 *PTR_DAT_71052a53e8;

void FUN_7100182db0(long *param_1, long param_2, u16 param_3, u8 param_4, u32 param_5)
{
    *(u16 *)(param_1 + 2) = param_3;
    *(u16 *)(param_1 + 3) = 0;
    *(u32 *)((u8 *)param_1 + 0x1c) = param_5;
    *param_1 = (long)(PTR_DAT_71052a53e8 + 0x10);
    param_1[1] = param_2;
    *(u8 *)((u8 *)param_1 + 0x12) = param_4;
    *(u32 *)((u8 *)param_1 + 0x14) = 0x14;
}

// ---------------------------------------------------------------------------
// 0x7100185e30  size=~  FUN_7100185e30
// Clear bit param_2 in u32 bitfield at param_1+0x5c
// ---------------------------------------------------------------------------
void FUN_7100185e30(long param_1, u32 param_2)
{
    *(u32 *)(param_1 + 0x5c) &= ~(1u << (param_2 & 0x1fu));
}

// ---------------------------------------------------------------------------
// 0x7100186270  size=~  FUN_7100186270
// Init node: vtable from PTR_DAT_71052a5528, clear u32 at [1]
// ---------------------------------------------------------------------------
__attribute__((visibility("hidden"))) extern u8 *PTR_DAT_71052a5528;

void FUN_7100186270(long *param_1)
{
    u8 *puVar1 = PTR_DAT_71052a5528;
    *(u32 *)(param_1 + 1) = 0;
    *param_1 = (long)(puVar1 + 0x10);
}

// ---------------------------------------------------------------------------
// 0x7100191f90 – 0x7100192ce0
// Check role (param_1+0x118) == N and state (param_1+0xe8) in [2,4]
// ---------------------------------------------------------------------------
bool FUN_7100191f90(long p) { return *(int *)(p+0x118)==2  && (u32)(*(int *)(p+0xe8)-2)<3; }
bool FUN_7100192260(long p) { return *(int *)(p+0x118)==3  && (u32)(*(int *)(p+0xe8)-2)<3; }
bool FUN_7100192ce0(long p) { return *(int *)(p+0x118)==5  && (u32)(*(int *)(p+0xe8)-2)<3; }

// ---------------------------------------------------------------------------
// 0x7100193740  size=~  FUN_7100193740
// Returns true if nested struct at +0x38 has flag at +0x84 set
// ---------------------------------------------------------------------------
bool FUN_7100193740(long param_1)
{
    if (*(long *)(param_1 + 0x38) != 0)
        return *(char *)(*(long *)(param_1 + 0x38) + 0x84) != '\0';
    return false;
}

// ---------------------------------------------------------------------------
// 0x7100194e60  size=~  FUN_7100194e60
// Check if connection request is "sendable": vtable check or role/mask filter
// ---------------------------------------------------------------------------
u64 FUN_7100157cf0(long);

bool FUN_7100194e60(long *param_1, long param_2)
{
    u64 r = (*(u64 (**)(void))(*param_1 + 200))();
    if (r & 1)
        return true;
    if ((*(u8 *)(param_2 + 0x31) & 3u) == 1) {
        u64 v = FUN_7100157cf0(param_2);
        if (v >> 0x20 != 0) return false;
        return (int)param_1[0x22] == 0;
    }
    return false;
}

// ---------------------------------------------------------------------------
// 0x71001a8730  size=~  FUN_71001a8730
// Find slot matching char key in peer table; return base + slot * 0x80
// ---------------------------------------------------------------------------
long FUN_71001a8730(long param_1, char param_2)
{
    u16 count = *(u16 *)(param_1 + 0xd6);
    if (count == 0)
        return 0;
    u16 i = 0;
    do {
        if (*(char *)(*(long *)(param_1 + 0xb0) + (u64)i) == param_2)
            return *(long *)(param_1 + 0xa8) + (u64)i * 0x80;
        i++;
    } while (i < count);
    return 0;
}

// ---------------------------------------------------------------------------
// 0x71001a8b40  size=~  FUN_71001a8b40
// Extended sendability check: handles multicast/unicast roles and seq masks
// ---------------------------------------------------------------------------
u32 FUN_7100157cf0_u32(long);

bool FUN_71001a8b40(long *param_1, long param_2)
{
    u64 r = (*(u64 (**)(void))(*param_1 + 200))();
    if (r & 1) return true;

    u8 role = *(u8 *)(param_2 + 0x31);
    if (role >> 1 & 1) {
        if (!(role & 1)) return false;
        u64 v = FUN_7100157cf0(param_2);
        if (v >> 0x20 != 0) return false;
        if ((int)param_1[0x22] != 0) {
            u32 m = (u32)FUN_7100157cf0(param_2);
            return (m & ~*(u32 *)(param_1 + 0x22)) != 0;
        }
        return true;
    }
    if (!(role & 1)) return false;
    u64 v = FUN_7100157cf0(param_2);
    if (v >> 0x20 != 0) return false;
    return (int)param_1[0x22] == 0;
}

// ---------------------------------------------------------------------------
// 0x71001aa3d0  size=~  FUN_71001aa3d0
// Zero-init connection config block (11 slots + misc fields)
// ---------------------------------------------------------------------------
void FUN_71001aa3d0(u64 *param_1)
{
    *(u64 *)((u8 *)param_1 + 0x44) = 0;
    param_1[6] = 0x40001f4ULL;
    param_1[7] = 0;
    *(u16 *)(param_1 + 8) = 0x5fd;
    *(u8  *)((u8 *)param_1 + 0x42) = 0xff;
    *(u8  *)((u8 *)param_1 + 0x4c) = 0;
    param_1[10] = 0;
    *param_1 = 0;
    param_1[1] = 0;
    param_1[2] = 0;
    param_1[3] = 0;
    param_1[4] = 0;
    param_1[5] = 0;
}

// ---------------------------------------------------------------------------
// 0x71001aca20  size=~  FUN_71001aca20
// Compute compressed size of 2D field param_1: rows*4 + ceil_to_byte(rows*cols*bits) + 4
// ---------------------------------------------------------------------------
int FUN_71001aca20(long param_1)
{
    int rows  = *(int *)(param_1 + 0x3c);
    u32 bits  = (u32)(rows * (u32)*(u8 *)(param_1 + 0x41) * (u32)rows);
    int pad   = 0;
    if (bits & 7u)
        pad = 8 - (int)(bits & 7u);
    return rows * 4 + ((pad + bits) >> 3) + 4;
}
