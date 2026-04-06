#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7100 address range, batch d3-023
// Network protocol: checksum, stream, protocol ID, flags, matchmaking filters

// ---- External declarations -----------------------------------------------

// External FUN_* forward declarations
extern void FUN_71001cf300(u64, u64, s64);
extern void FUN_71001d2570(void);
extern void FUN_71001d2830(void);
extern void FUN_71001efaf0(s64);

// ---- Functions ---------------------------------------------------------------

// 0x71001cb860 — empty dtor: ~ChecksumAlgorithm (16 bytes)
void FUN_71001cb860(void)
{
}

// 0x71001cbc40 — GetLength: return end - begin (16 bytes)
s64 FUN_71001cbc40(s64 self)
{
    return *(s64 *)(self + 0x18) - *(s64 *)(self + 0x10);
}

// 0x71001ce080 — GetChecksumLength: return 0x10 (16 bytes)
u64 FUN_71001ce080(void)
{
    return 0x10;
}

// 0x71001cfb70 — SetHeadShiftSize: swap shift and adjust pointer (32 bytes)
void FUN_71001cfb70(s64 self, s64 new_shift)
{
    s64 old_shift;

    old_shift = *(s64 *)(self + 0x28);
    *(s64 *)(self + 0x28) = new_shift;
    *(s64 *)(self + 0x18) = (*(s64 *)(self + 0x18) - new_shift) + old_shift;
}

// 0x71001d0c80 — SetDependentConnection: write u64 to +0x70, u32 to +0x78 (16 bytes)
void FUN_71001d0c80(s64 self, u64 connection, u32 port)
{
    *(u64 *)(self + 0x70) = connection;
    *(u32 *)(self + 0x78) = port;
}

// 0x71001d6920 — GetContentPtr: if begin != end, return begin (16 bytes)
s64 FUN_71001d6920(s64 self)
{
    s64 result;

    result = 0;
    if (*(s64 *)(self + 0x10) != *(s64 *)(self + 0x18)) {
        result = *(s64 *)(self + 0x10);
    }
    return result;
}

// 0x71001d6b80 — GetCurrentOperation: cond getter via ptr chain (32 bytes)
u64 FUN_71001d6b80(s64 self)
{
    if (*(s64 *)(self + 0x30) != 0) {
        return *(u64 *)(*(s64 *)(self + 0x20) + 0x10);
    }
    return 0;
}

// 0x710022b380 — SetProtocolID: write u16 to +0x48 (16 bytes)
void FUN_710022b380(s64 self, u16 protocol_id)
{
    *(u16 *)(self + 0x48) = protocol_id;
}

// 0x710022b500 — FlagIsSet: check all bits of mask are set in +0x60 (16 bytes)
bool FUN_710022b500(s64 self, u32 mask)
{
    return (mask & (*(u32 *)(self + 0x60) ^ 0xffffffff)) == 0;
}

// 0x7100255b10 — SetExcludeLocked: write bit to +0xc9 (16 bytes)
void FUN_7100255b10(s64 self, u8 enabled)
{
    *(u8 *)(self + 0xc9) = enabled & 1;
}

// 0x7100255b20 — SetVacantOnly: set flag at +0xc8, set sentinel at +0xd0 (32 bytes)
void FUN_7100255b20(s64 self, u8 enabled)
{
    *(u8 *)(self + 0xc8) = enabled & 1;
    *(u16 *)(self + 0xd0) = 1;
}

// 0x7100255b40 — SetExcludeNonHostPid: write bit to +0xca (16 bytes)
void FUN_7100255b40(s64 self, u8 enabled)
{
    *(u8 *)(self + 0xca) = enabled & 1;
}

// 0x7100255b50 — SetExcludeUserPasswordSet: write bit to +0x100 (16 bytes)
void FUN_7100255b50(s64 self, u8 enabled)
{
    *(u8 *)(self + 0x100) = enabled & 1;
}
