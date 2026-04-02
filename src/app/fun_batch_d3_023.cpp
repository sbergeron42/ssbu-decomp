#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7100 address range, batch d3-023
// Pool-d worker: auto-generated from Ghidra decompilation

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

// 0x71001cbc30 — cond getter: if ptr+0x10 != ptr+0x18, return ptr+0x10, else 0 (16 bytes)
s64 FUN_71001cbc30(s64 param_1)
{
    s64 lVar1;

    lVar1 = 0;
    if (*(s64 *)(param_1 + 0x10) != *(s64 *)(param_1 + 0x18)) {
        lVar1 = *(s64 *)(param_1 + 0x10);
    }
    return lVar1;
}

// 0x71001cbc40 — GetLength: return ptr+0x18 - ptr+0x10 (16 bytes)
s64 FUN_71001cbc40(s64 param_1)
{
    return *(s64 *)(param_1 + 0x18) - *(s64 *)(param_1 + 0x10);
}

// 0x71001ce080 — GetChecksumLength: return 0x10 (16 bytes)
u64 FUN_71001ce080(void)
{
    return 0x10;
}

// 0x71001cf560 — delegate: call FUN_71001cf300(p1, p2, p3*p4*8) (16 bytes)
void FUN_71001cf560(u64 param_1, u64 param_2, s64 param_3, s64 param_4)
{
    FUN_71001cf300(param_1, param_2, param_3 * param_4 * 8);
}

// 0x71001cfb70 — SetHeadShiftSize: swap field and adjust ptr (32 bytes)
void FUN_71001cfb70(s64 param_1, s64 param_2)
{
    s64 lVar1;

    lVar1 = *(s64 *)(param_1 + 0x28);
    *(s64 *)(param_1 + 0x28) = param_2;
    *(s64 *)(param_1 + 0x18) = (*(s64 *)(param_1 + 0x18) - param_2) + lVar1;
}

// 0x71001d0c80 — SetDependentConnection: write u64 to +0x70, u32 to +0x78 (16 bytes)
void FUN_71001d0c80(s64 param_1, u64 param_2, u32 param_3)
{
    *(u64 *)(param_1 + 0x70) = param_2;
    *(u32 *)(param_1 + 0x78) = param_3;
}

// 0x71001d2550 — call FUN_71001d2570 and return 1 (32 bytes)
u64 FUN_71001d2550(void)
{
    FUN_71001d2570();
    return 1;
}

// 0x71001d2810 — call FUN_71001d2830 and return 1 (32 bytes)
u64 FUN_71001d2810(void)
{
    FUN_71001d2830();
    return 1;
}

// 0x71001d6920 — GetContentPtr: if ptr+0x10 != ptr+0x18, return ptr+0x10 (16 bytes)
s64 FUN_71001d6920(s64 param_1)
{
    s64 lVar1;

    lVar1 = 0;
    if (*(s64 *)(param_1 + 0x10) != *(s64 *)(param_1 + 0x18)) {
        lVar1 = *(s64 *)(param_1 + 0x10);
    }
    return lVar1;
}

// 0x71001d6b80 — GetCurrentOperation: cond getter via ptr chain (32 bytes)
u64 FUN_71001d6b80(s64 param_1)
{
    if (*(s64 *)(param_1 + 0x30) != 0) {
        return *(u64 *)(*(s64 *)(param_1 + 0x20) + 0x10);
    }
    return 0;
}

// 0x71001d72c0 — empty stub (32 bytes)
void FUN_71001d72c0(void)
{
}

// 0x71001dc780 — constant: return 4 (16 bytes)
u64 FUN_71001dc780(void)
{
    return 4;
}

// 0x71001dc790 — constant: return 6 (16 bytes)
u64 FUN_71001dc790(void)
{
    return 6;
}

// 0x71001dc7a0 — constant: return 0xd (16 bytes)
u64 FUN_71001dc7a0(void)
{
    return 0xd;
}

// 0x71001dec00 — offset: return param_1 + 8 (16 bytes)
s64 FUN_71001dec00(s64 param_1)
{
    return param_1 + 8;
}

// 0x71001dec10 — offset: return param_1 + 0x80 (16 bytes)
s64 FUN_71001dec10(s64 param_1)
{
    return param_1 + 0x80;
}

// 0x71001dec20 — getter: return u32 at +0xa8 (32 bytes)
u32 FUN_71001dec20(s64 param_1)
{
    return *(u32 *)(param_1 + 0xa8);
}

// 0x71001e1010 — delegate: call FUN_71001efaf0(param_1 + 0x80) (16 bytes)
void FUN_71001e1010(s64 param_1)
{
    FUN_71001efaf0(param_1 + 0x80);
}

// 0x71001e6bc0 — empty stub (32 bytes)
void FUN_71001e6bc0(void)
{
}

// 0x71001ef600 — offset: return param_1 + 0x80 (16 bytes)
s64 FUN_71001ef600(s64 param_1)
{
    return param_1 + 0x80;
}

// 0x71001f30c0 — constant: return 3 (16 bytes)
u64 FUN_71001f30c0(void)
{
    return 3;
}

// 0x7100221700 — empty stub (32 bytes)
void FUN_7100221700(void)
{
}

// 0x71002275c0 — setter: write u32 param_2 to +0x70 (32 bytes)
void FUN_71002275c0(s64 param_1, u32 param_2)
{
    *(u32 *)(param_1 + 0x70) = param_2;
}

// 0x7100227660 — getter: return byte at +0x21 (32 bytes)
u8 FUN_7100227660(s64 param_1)
{
    return *(u8 *)(param_1 + 0x21);
}

// 0x71002276f0 — bswap16: byte-swap u32 and mask to 16 bits (16 bytes)
u32 FUN_71002276f0(u32 param_1)
{
    return ((param_1 & 0xff00ff00) >> 8 | (param_1 & 0xff00ff) << 8) & 0xffff;
}

// 0x71002282f0 — getter: return u64 at **param_1 (32 bytes)
u64 FUN_71002282f0(u64 *param_1)
{
    return *(u64 *)*param_1;
}

// 0x710022a510 — getter: return u64 at +0x20 (16 bytes)
u64 FUN_710022a510(s64 param_1)
{
    return *(u64 *)(param_1 + 0x20);
}

// 0x710022b0c0 — empty stub (16 bytes)
void FUN_710022b0c0(void)
{
}

// 0x710022b380 — SetProtocolID: write u16 param_2 to +0x48 (16 bytes)
void FUN_710022b380(s64 param_1, u16 param_2)
{
    *(u16 *)(param_1 + 0x48) = param_2;
}

// 0x710022b500 — FlagIsSet: (param_2 & ~*(u32*)(+0x60)) == 0 (16 bytes)
bool FUN_710022b500(s64 param_1, u32 param_2)
{
    return (param_2 & (*(u32 *)(param_1 + 0x60) ^ 0xffffffff)) == 0;
}

// 0x710022e6a0 — setter: write u64 param_2 to +0x50 (16 bytes)
void FUN_710022e6a0(s64 param_1, u64 param_2)
{
    *(u64 *)(param_1 + 0x50) = param_2;
}

// 0x710022f060 — copy: transfer u8 and two u32 fields (32 bytes)
void FUN_710022f060(s64 param_1, s64 param_2)
{
    *(u8 *)(param_1 + 8) = *(u8 *)(param_2 + 8);
    *(u32 *)(param_1 + 0xc) = *(u32 *)(param_2 + 0xc);
    *(u32 *)(param_1 + 0x10) = *(u32 *)(param_2 + 0x10);
}

// 0x7100231b40 — getter: return byte at +8 (16 bytes)
u8 FUN_7100231b40(s64 param_1)
{
    return *(u8 *)(param_1 + 8);
}

// 0x7100232ca0 — empty stub (16 bytes)
void FUN_7100232ca0(void)
{
}

// 0x710024d060 — setter: write two u32 params to +0x24 and +0x28 (16 bytes)
void FUN_710024d060(s64 param_1, u32 param_2, u32 param_3)
{
    *(u32 *)(param_1 + 0x24) = param_2;
    *(u32 *)(param_1 + 0x28) = param_3;
}

// 0x7100255b10 — SetExcludeLocked: write param_2&1 to byte at +0xc9 (16 bytes)
void FUN_7100255b10(s64 param_1, u8 param_2)
{
    *(u8 *)(param_1 + 0xc9) = param_2 & 1;
}

// 0x7100255b20 — SetVacantOnly: set byte at +0xc8, set u16 sentinel at +0xd0 (32 bytes)
void FUN_7100255b20(s64 param_1, u8 param_2)
{
    *(u8 *)(param_1 + 0xc8) = param_2 & 1;
    *(u16 *)(param_1 + 0xd0) = 1;
}

// 0x7100255b40 — SetExcludeNonHostPid: write param_2&1 to byte at +0xca (16 bytes)
void FUN_7100255b40(s64 param_1, u8 param_2)
{
    *(u8 *)(param_1 + 0xca) = param_2 & 1;
}

// 0x7100255b50 — SetExcludeUserPasswordSet: write param_2&1 to byte at +0x100 (16 bytes)
void FUN_7100255b50(s64 param_1, u8 param_2)
{
    *(u8 *)(param_1 + 0x100) = param_2 & 1;
}

// 0x7100255b60 — setter: write u32 param_2 to +0xcc (16 bytes)
void FUN_7100255b60(s64 param_1, u32 param_2)
{
    *(u32 *)(param_1 + 0xcc) = param_2;
}
