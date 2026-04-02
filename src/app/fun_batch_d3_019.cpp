#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7100 address range, batch d3-019
// Pool-d worker: auto-generated from Ghidra decompilation

// ---- External declarations -----------------------------------------------

namespace nn {
    namespace util {
        void ReferSymbol(const char *);
    }
}

// ---- Functions ---------------------------------------------------------------

// 0x710013dc90 — copy: transfer 4 fields (2+1+2+1 bytes) between structs (48 bytes)
void FUN_710013dc90(s64 param_1, s64 param_2)
{
    *(u16 *)(param_1 + 8) = *(u16 *)(param_2 + 8);
    *(u8 *)(param_1 + 10) = *(u8 *)(param_2 + 10);
    *(u16 *)(param_1 + 0xc) = *(u16 *)(param_2 + 0xc);
    *(u8 *)(param_1 + 0xe) = *(u8 *)(param_2 + 0xe);
}

// 0x710013dcc0 — Reset: zero 4 fields (2+1+2+1 bytes) (48 bytes)
void FUN_710013dcc0(s64 param_1)
{
    *(u16 *)(param_1 + 8) = 0;
    *(u8 *)(param_1 + 10) = 0;
    *(u16 *)(param_1 + 0xc) = 0;
    *(u8 *)(param_1 + 0xe) = 0;
}

// 0x710013e3f0 — SDK symbol anchor: ReferSymbol with PiaSession version (16 bytes)
void FUN_710013e3f0(void)
{
    nn::util::ReferSymbol("SDK MW+Nintendo+PiaSession-5_19_1");
}

// 0x710013f9b0 — Reset: zero 3 fields (16 bytes)
void FUN_710013f9b0(s64 param_1)
{
    *(u32 *)(param_1 + 0x10) = 0;
    *(u16 *)(param_1 + 0x14) = 0;
    *(u64 *)(param_1 + 8) = 0;
}

// 0x7100140e30 — bool: (field+0x90 - 6) < 3 (48 bytes)
bool FUN_7100140e30(s64 param_1)
{
    return *(s32 *)(param_1 + 0x90) - 6U < 3;
}

// 0x7100145a10 — bool: field==1 && (field2 - 2) < 3 (48 bytes)
bool FUN_7100145a10(s64 param_1)
{
    if (*(s32 *)(param_1 + 0x140) == 1) {
        return *(s32 *)(param_1 + 0x110) - 2U < 3;
    }
    return false;
}

// 0x7100145ce0 — bool: field==2 && (field2 - 2) < 3 (48 bytes)
bool FUN_7100145ce0(s64 param_1)
{
    if (*(s32 *)(param_1 + 0x140) == 2) {
        return *(s32 *)(param_1 + 0x110) - 2U < 3;
    }
    return false;
}

// 0x7100145ec0 — bool: field==3 && (field2 - 2) < 3 (48 bytes)
bool FUN_7100145ec0(s64 param_1)
{
    if (*(s32 *)(param_1 + 0x140) == 3) {
        return *(s32 *)(param_1 + 0x110) - 2U < 3;
    }
    return false;
}

// 0x7100146070 — bool: field==4 && (field2 - 2) < 3 (48 bytes)
bool FUN_7100146070(s64 param_1)
{
    if (*(s32 *)(param_1 + 0x140) == 4) {
        return *(s32 *)(param_1 + 0x110) - 2U < 3;
    }
    return false;
}

// 0x71001462a0 — bool: field==5 && (field2 - 2) < 3 (48 bytes)
bool FUN_71001462a0(s64 param_1)
{
    if (*(s32 *)(param_1 + 0x140) == 5) {
        return *(s32 *)(param_1 + 0x110) - 2U < 3;
    }
    return false;
}

// 0x7100146670 — bool: field==7 && (field2 - 2) < 3 (48 bytes)
bool FUN_7100146670(s64 param_1)
{
    if (*(s32 *)(param_1 + 0x140) == 7) {
        return *(s32 *)(param_1 + 0x110) - 2U < 3;
    }
    return false;
}

// 0x71001468b0 — bool: field==8 && (field2 - 2) < 3 (48 bytes)
bool FUN_71001468b0(s64 param_1)
{
    if (*(s32 *)(param_1 + 0x140) == 8) {
        return *(s32 *)(param_1 + 0x110) - 2U < 3;
    }
    return false;
}

// 0x7100146a90 — bool: field==0x13 && (field2 - 2) < 3 (48 bytes)
bool FUN_7100146a90(s64 param_1)
{
    if (*(s32 *)(param_1 + 0x140) == 0x13) {
        return *(s32 *)(param_1 + 0x110) - 2U < 3;
    }
    return false;
}

// 0x7100146be0 — GetStationNum: return u32 at +0x1a8 (16 bytes)
u32 FUN_7100146be0(s64 param_1)
{
    return *(u32 *)(param_1 + 0x1a8);
}

// 0x7100146bf0 — getter: return u32 at +0x1a8 (16 bytes)
u32 FUN_7100146bf0(s64 param_1)
{
    return *(u32 *)(param_1 + 0x1a8);
}

// 0x7100146c00 — getter: return u16 at +0x208 (16 bytes)
u16 FUN_7100146c00(s64 param_1)
{
    return *(u16 *)(param_1 + 0x208);
}

// 0x7100147350 — clear: zero two u64 fields at +0xa0, +0xa8 (16 bytes)
void FUN_7100147350(s64 param_1)
{
    *(u64 *)(param_1 + 0xa0) = 0;
    *(u64 *)(param_1 + 0xa8) = 0;
}

// 0x7100147820 — clear: zero u64 field at +0xb0 (16 bytes)
void FUN_7100147820(s64 param_1)
{
    *(u64 *)(param_1 + 0xb0) = 0;
}

// 0x7100149180 — bool: field==0x1a && (field2 - 2) < 3 (48 bytes)
bool FUN_7100149180(s64 param_1)
{
    if (*(s32 *)(param_1 + 0x140) == 0x1a) {
        return *(s32 *)(param_1 + 0x110) - 2U < 3;
    }
    return false;
}

// 0x7100149240 — SetCurrentSessionOpenStatus: indexed write to open-status array (16 bytes)
void FUN_7100149240(s64 param_1, u32 param_2)
{
    *(u32 *)(param_1 + (u64)*(u8 *)(param_1 + 0x162) * 4 + 400) = param_2;
}

// 0x7100149250 — SetBufferSessionOpenStatus: indexed write to other slot (32 bytes)
void FUN_7100149250(s64 param_1, u32 param_2)
{
    *(u32 *)(param_1 + (u64)(*(s8 *)(param_1 + 0x162) == '\0') * 4 + 400) = param_2;
}

// 0x710014f0b0 — Reset: clear u32 and set u64 sentinel (16 bytes)
void FUN_710014f0b0(s64 param_1)
{
    *(u32 *)(param_1 + 0x10) = 0;
    *(u64 *)(param_1 + 8) = 0x1400000000;
}

// 0x710014f120 — getter: return u32 at +0x10 (16 bytes)
u32 FUN_710014f120(s64 param_1)
{
    return *(u32 *)(param_1 + 0x10);
}

// 0x710014f130 — getter: return u32 at +8 (16 bytes)
u32 FUN_710014f130(s64 param_1)
{
    return *(u32 *)(param_1 + 8);
}

// 0x710014f140 — getter: return u32 at +0xc (16 bytes)
u32 FUN_710014f140(s64 param_1)
{
    return *(u32 *)(param_1 + 0xc);
}

// 0x710014f170 — empty stub (32 bytes)
void FUN_710014f170(void)
{
}

// 0x710014f190 — clear: zero u32 at +8 (16 bytes)
void FUN_710014f190(s64 param_1)
{
    *(u32 *)(param_1 + 8) = 0;
}

// 0x710014f1a0 — setter: write u32 to +8 (16 bytes)
void FUN_710014f1a0(s64 param_1, u32 param_2)
{
    *(u32 *)(param_1 + 8) = param_2;
}

// 0x710014f1b0 — getter: return u32 at +8 (16 bytes)
u32 FUN_710014f1b0(s64 param_1)
{
    return *(u32 *)(param_1 + 8);
}

// 0x7100151070 — empty stub (16 bytes)
void FUN_7100151070(void)
{
}

// 0x71001531b0 — SDK symbol anchor: ReferSymbol with PiaTransport version (16 bytes)
void FUN_71001531b0(void)
{
    nn::util::ReferSymbol("SDK MW+Nintendo+PiaTransport-5_19_1");
}

// 0x71001531e0 — empty stub (32 bytes)
void FUN_71001531e0(void)
{
}
