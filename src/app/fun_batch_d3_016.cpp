#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7100 address range, batch d3-016
// Pool-d worker: auto-generated from Ghidra decompilation

// ---- External declarations -----------------------------------------------

// External FUN_* forward declarations
extern void FUN_71000b2b10(s64, s64);

namespace nn {
    namespace util {
        void ReferSymbol(const char *);
    }
    namespace pia { namespace common {
        struct InetAddress { static bool IsValid(s64); };
    } }
}

// ---- Functions ---------------------------------------------------------------

// 0x71000bc860 — empty stub (16 bytes)
void FUN_71000bc860(void)
{
}

// 0x71000bc920 — ResetTurnLr: clear u64 and u32 fields (16 bytes)
void FUN_71000bc920(u64 *param_1)
{
    *param_1 = 0;
    *(u32 *)(param_1 + 1) = 0;
}

// 0x71000bccc0 — SDK symbol anchor: ReferSymbol with Pia SDK version (16 bytes)
void FUN_71000bccc0(void)
{
    nn::util::ReferSymbol("SDK MW+Nintendo+Pia-5_19_1");
}

// 0x71000be900 — copy: transfer u64 and u32 from param_2 into param_1 (32 bytes)
void FUN_71000be900(s64 param_1, u64 *param_2)
{
    u64 uVar1;

    uVar1 = *param_2;
    *(u32 *)(param_1 + 0xc) = *(u32 *)(param_2 + 1);
    *(u64 *)(param_1 + 4) = uVar1;
}

// 0x71000beb20 — validate: call InetAddress::IsValid on +8 sub-field (16 bytes)
void FUN_71000beb20(s64 param_1)
{
    nn::pia::common::InetAddress::IsValid(param_1 + 8);
}

// 0x71000beb30 — delegate: forward both offsets+8 to FUN_71000b2b10 (16 bytes)
void FUN_71000beb30(s64 param_1, s64 param_2)
{
    FUN_71000b2b10(param_1 + 8, param_2 + 8);
}

// 0x71000bedc0 — clear byte: write 0 to param_1+8 (16 bytes)
void FUN_71000bedc0(s64 param_1)
{
    *(u8 *)(param_1 + 8) = 0;
}

// 0x71000bf170 — GetPayload: compute packet payload pointer (16 bytes)
s64 FUN_71000bf170(s64 param_1, s32 param_2)
{
    return param_1 + (u64)(param_2 + 0x20) + 0x28;
}

// 0x71000bf810 — empty stub (16 bytes)
void FUN_71000bf810(void)
{
}

// 0x71000bfa90 — clear: write 0 to *param_1 (16 bytes)
void FUN_71000bfa90(u64 *param_1)
{
    *param_1 = 0;
}

// 0x71000c03c0 — Finalize: clear two fields at +0x70 and +0x78 (16 bytes)
void FUN_71000c03c0(s64 param_1)
{
    *(u64 *)(param_1 + 0x70) = 0;
    *(u32 *)(param_1 + 0x78) = 0;
}

// 0x71000c36d0 — getter: return byte at +0xb2 (16 bytes)
u8 FUN_71000c36d0(s64 param_1)
{
    return *(u8 *)(param_1 + 0xb2);
}

// 0x71000c4cc0 — setter: write param_2 to +0x58 (16 bytes)
void FUN_71000c4cc0(s64 param_1, u32 param_2)
{
    *(u32 *)(param_1 + 0x58) = param_2;
}

// 0x71000c7410 — bool: return (byte at +0x20) == 3 (16 bytes)
bool FUN_71000c7410(s64 param_1)
{
    return *(s8 *)(param_1 + 0x20) == '\x03';
}

// 0x71000c74a0 — offset: return param_1 + 0x150 (16 bytes)
s64 FUN_71000c74a0(s64 param_1)
{
    return param_1 + 0x150;
}

// 0x71000c74b0 — getter: return u16 at +0x22 (16 bytes)
u16 FUN_71000c74b0(s64 param_1)
{
    return *(u16 *)(param_1 + 0x22);
}

// 0x71000c74d0 — getter: return u64 at +0x200 (16 bytes)
u64 FUN_71000c74d0(s64 param_1)
{
    return *(u64 *)(param_1 + 0x200);
}

// 0x71000c87e0 — getter: return u32 at +0x5c8 (16 bytes)
u32 FUN_71000c87e0(s64 param_1)
{
    return *(u32 *)(param_1 + 0x5c8);
}

// 0x71000c87f0 — indexed offset: param_1 + param_2*0x14 + 0x5c0 (48 bytes)
s64 FUN_71000c87f0(s64 param_1, u32 param_2)
{
    return param_1 + (u64)param_2 * 0x14 + 0x5c0;
}

// 0x71000c8800 — empty stub (16 bytes)
void FUN_71000c8800(void)
{
}

// 0x71000cb3b0 — offset: return param_1 + 0x6f8 (16 bytes)
s64 FUN_71000cb3b0(s64 param_1)
{
    return param_1 + 0x6f8;
}

// 0x71000cb3c0 — offset: return param_1 + 0x778 (16 bytes)
s64 FUN_71000cb3c0(s64 param_1)
{
    return param_1 + 0x778;
}

// 0x71000d3390 — setter: write param_2 at param_1+600 (16 bytes)
void FUN_71000d3390(s64 param_1, u64 param_2)
{
    *(u64 *)(param_1 + 600) = param_2;
}

// 0x71000eb680 — flag map: if ==2 return 5, if ==1 return 4, else 0 (48 bytes)
s32 FUN_71000eb680(s32 param_1)
{
    s32 iVar1;

    iVar1 = 5;
    if (param_1 != 2) {
        iVar1 = (u32)(param_1 == 1) << 2;
    }
    return iVar1;
}

// 0x71000eb6b0 — getter: return byte at +0x554 (16 bytes)
u8 FUN_71000eb6b0(s64 param_1)
{
    return *(u8 *)(param_1 + 0x554);
}

// 0x71000ee2c0 — GetSessionIdArraySize: if ptr non-null return 4, else 0 (32 bytes)
u32 FUN_71000ee2c0(s64 param_1)
{
    if (*(s64 *)(param_1 + 0x2d8) != 0) {
        return 4;
    }
    return 0;
}

// 0x71001127b0 — empty stub (32 bytes)
void FUN_71001127b0(void)
{
}
