#include "types.h"

#define HIDDEN __attribute__((visibility("hidden")))

// MEDIUM-tier FUN_* functions — 0x7100 address range, batch d3-005
// Pool-d worker: auto-generated from Ghidra decompilation

// ---- External declarations -----------------------------------------------

extern "C" void *memcpy(void *, const void *, u64);

// External data
extern u8  PTR_DAT_71052a5058[] HIDDEN;
extern u8  PTR_DAT_71052a50c0[] HIDDEN;
extern u8  PTR_DAT_71052a50e0[] HIDDEN;
extern u8  PTR_DAT_71052a57d8[] HIDDEN;
extern u8  PTR_DAT_71052a57e0[] HIDDEN;

// External FUN_* forward declarations
extern u64  FUN_71000b1b90();
extern s64  FUN_7100130810(u64, u64);
extern void FUN_71000bed00(s64 *);
extern u64  FUN_7100157cf0(s64);
extern void FUN_7100156390();
extern u64  FUN_710015f600(s64, s8, u32);  // approx: (ptr, channel, flags)
extern void FUN_710015fb50(s64);
extern void FUN_7100165090();
extern void FUN_7100168450(s64, u32);
extern void FUN_7100170cd0(s64, u64);
extern void FUN_71001770c0();
extern void FUN_710017c1c0();
extern void FUN_7100194810();
extern void FUN_7100195180();

// ---- Functions ---------------------------------------------------------------

// 0x7100156720 — protocol-ID to name string (128 bytes)
const char *FUN_7100156720(u64 param_1)
{
    const char *pcVar1 = "KeepAlive";
    switch ((u32)((u64)param_1 >> 0x18) & 0xff) {
    default:                   return "(KickoutReason_Unknown PROTOCOL NAME)";
    case 0x08:                 return pcVar1;
    case 0x14:                 return "Station";
    case 0x18:                 return "Mesh";
    case 0x1c:                 return "SyncClock";
    case 0x24:                 return "Local";
    case 0x28:                 return "Direct";
    case 0x2c:                 return "Net";
    case 0x34:                 return "Nat";
    case 0x44:                 return "Lan";
    case 0x54:                 return "BandwidthCheck";
    case 0x58:                 return "Rtt";
    case 0x65:                 return "Sync";
    case 0x68:                 return "Unreliable";
    case 0x6c:                 return "RoundrobinUnreliable";
    case 0x73:                 return "Clone";
    case 0x74:                 return "Atomic";
    case 0x76:                 return "Event";
    case 0x77:                 return "Clock";
    case 0x78:                 return "InterpolationClock";
    case 0x7b:                 return "Voice";
    case 0x7c:                 return "Reliable";
    case 0x80:                 return "BroadcastReliable";
    case 0x81:                 return "StreamBroadcastReliable";
    case 0x84:                 return "ReliableBroadcast";
    case 0x94:                 return "Session";
    case 0x98:                 return "Lobby";
    case 0xa4:                 return "Feedback";
    case 0xa8:                 return "RelayService";
    case 0xac:                 return "WanNat";
    }
}

// 0x7100156d00 — protocol-ID to flag bitmask (128 bytes)
u64 FUN_7100156d00(u16 param_1)
{
    u64 uVar1 = 2;
    switch (param_1) {
    default:    return 0;
    case 0x14:  return uVar1;
    case 0x18:  return 4;
    case 0x1c:  return 8;
    case 0x24:  return 0x80000;
    case 0x28:  return 0x100000;
    case 0x2c:  return 0x200000;
    case 0x34:  return 0x10;
    case 0x44:  return 0x20000;
    case 0x54:  return 0x40000;
    case 0x58:  return 0x20;
    case 0x65:  return 0x40;
    case 0x68:  return 0x80;
    case 0x6c:  return 0x1000;
    case 0x73:  return 0x4000;
    case 0x74:  return 0x4000000;
    case 0x76:  return 0x800000;
    case 0x77:  return 0x2000000;
    case 0x78:  return 0x2000;
    case 0x7b:  return 0x8000;
    case 0x7c:  return 0x100;
    case 0x80:  return 0x10000000;
    case 0x81:  return 0x20000000;
    case 0x84:  return 0x200;
    case 0x94:  return 0x10000;
    case 0x98:  return 0x400000;
    case 0xa4:  return 0x400;
    case 0xac:  return 0x8000000;
    case 0xb0:  return 0x40000000;
    case 0xb4:  return 0x80000000;
    }
}

// 0x710015e880 — guarded delegate: if ptr+0x50 and channel != -3, forward (80 bytes)
u64 FUN_710015e880(s64 param_1, u32 param_2)
{
    u64 uVar1;
    if (*(s64 *)(param_1 + 0x50) != 0) {
        if (*(s8 *)(param_1 + 0x38) != -3) {
            uVar1 = (u64)FUN_710015f600(*(s64 *)(param_1 + 0x50), *(s8 *)(param_1 + 0x38), param_2);
            return uVar1;
        }
    }
    return 0xffffffff;
}

// 0x710015f240 — bounded delegate: if param_2 < byte at +0x60, call on indexed sub-object (64 bytes)
void FUN_710015f240(s64 param_1, u8 param_2)
{
    if (param_2 < *(u8 *)(param_1 + 0x60)) {
        FUN_710015fb50(*(s64 *)(param_1 + 0x58) + (u64)param_2 * 0x58);
    }
}

// 0x7100162b00 — delegate: call FUN_7100165090, zero field at +0x4d0 (32 bytes)
void FUN_7100162b00(s64 param_1)
{
    FUN_7100165090();
    *(u64 *)(param_1 + 0x4d0) = 0;
}

// 0x7100163d70 — ctor: parent init, set vtable (48 bytes)
void FUN_7100163d70(s64 *param_1)
{
    FUN_7100156390();
    *param_1 = (s64)(PTR_DAT_71052a5058 + 0x10);
}

// 0x7100166180 — vtable dispatch at +0x68, return non-zero bool (48 bytes)
bool FUN_7100166180(s64 *param_1)
{
    s64 lVar1;
    lVar1 = (*(s64 (*)(void))(*(s64 *)*param_1 + 0x68))();
    return lVar1 != 0;
}

// 0x7100168810 — ctor: parent + sub init, set vtable + sub-vtable ptr (80 bytes)
void FUN_7100168810(s64 *param_1)
{
    u8 *puVar1;
    FUN_71001770c0();
    FUN_71000bed00(param_1 + 2);
    puVar1 = PTR_DAT_71052a50c0 + 0x48;
    *param_1 = (s64)(PTR_DAT_71052a50c0 + 0x10);
    param_1[2] = (s64)puVar1;
}

// 0x710016a240 — ctor: parent + sub init, set vtable + sub-vtable ptr (80 bytes)
void FUN_710016a240(s64 *param_1)
{
    u8 *puVar1;
    FUN_710017c1c0();
    FUN_71000bed00(param_1 + 2);
    puVar1 = PTR_DAT_71052a50e0 + 0x68;
    *param_1 = (s64)(PTR_DAT_71052a50e0 + 0x10);
    param_1[2] = (s64)puVar1;
}

// 0x710016b7a0 — factory: alloc 0x68-byte object, init with FUN_7100170cd0 (144 bytes)
s64 FUN_710016b7a0(u64 param_1)
{
    u64 uVar1;
    s64 lVar2;
    uVar1 = FUN_71000b1b90();
    lVar2 = FUN_7100130810(0x68, uVar1);
    if (lVar2 != 0) {
        FUN_7100170cd0(lVar2, param_1);
    }
    return lVar2;
}

// 0x710016d800 — struct copy: store param_2, memcpy from +0x440, copy byte+u32 (80 bytes)
u64 *FUN_710016d800(s64 param_1, u64 param_2)
{
    u64 *puVar1;
    puVar1 = *(u64 **)(param_1 + 0x460);
    *puVar1 = param_2;
    memcpy((void *)((s64)puVar1 + 0xc), *(void **)(param_1 + 0x440),
           (u64)*(u8 *)(param_1 + 0x448));
    *(u8 *)((s64)puVar1 + 0x4c) = *(u8 *)(param_1 + 0x448);
    *(u32 *)(puVar1 + 1) = *(u32 *)(param_1 + 0x44c);
    return puVar1;
}

// 0x71001a8810 — ctor: parent init, set vtable (48 bytes)
void FUN_71001a8810(s64 *param_1)
{
    FUN_7100194810();
    *param_1 = (s64)(PTR_DAT_71052a57d8 + 0x10);
}

// 0x71001a8c40 — flag/channel check: match on bit pattern and mask (96 bytes)
bool FUN_71001a8c40(s64 param_1, s64 param_2)
{
    u32 uVar1;
    s64 lVar2;
    u64 uVar3;

    if ((*(u8 *)(param_2 + 0x31) & 1) == 0) {
        if ((*(u8 *)(param_2 + 0x31) >> 1 & 1) == 0) {
            lVar2 = FUN_7100157cf0(param_2);
            return lVar2 == *(s64 *)(param_1 + 8);
        }
        return false;
    }
    uVar3 = FUN_7100157cf0(param_2);
    if (uVar3 >> 0x20 != 0) {
        return false;
    }
    uVar1 = (u32)FUN_7100157cf0(param_2);
    if (uVar1 != 0) {
        if ((*(u32 *)(param_1 + 0x110) & uVar1) == 0) {
            return false;
        }
        if (((*(u8 *)(param_2 + 0x31) >> 1 & 1) != 0) &&
            ((uVar1 & (*(u32 *)(param_1 + 0x110) ^ 0xffffffff)) == 0)) {
            return false;
        }
        return true;
    }
    return (*(u8 *)(param_2 + 0x31) & 2) == 0;
}

// 0x71001a8df0 — ctor: parent init, set vtable (48 bytes)
void FUN_71001a8df0(s64 *param_1)
{
    FUN_7100195180();
    *param_1 = (s64)(PTR_DAT_71052a57e0 + 0x10);
}
