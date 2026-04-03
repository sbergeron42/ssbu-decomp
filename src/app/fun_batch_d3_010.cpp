#include "types.h"

#define HIDDEN __attribute__((visibility("hidden")))

// MEDIUM-tier FUN_* functions — 0x7100 address range, batch d3-010
// Pool-d worker: auto-generated from Ghidra decompilation

// ---- External declarations -----------------------------------------------

// External data
extern u8 DAT_710446f0e0 HIDDEN;
extern u8 DAT_710446f090 HIDDEN;
extern u8 PTR_DAT_71052a22b8[] HIDDEN;

// External FUN_* forward declarations
extern void FUN_71000272a0(u64);
extern s64  FUN_71000272b0(void);
extern void FUN_7100006870(s64 *, s64 *, u32);

// ---- Functions ---------------------------------------------------------------

// 0x71000145a0 — bool: deref ptr at +0x8f0, compare to param_1 (32 bytes)
bool FUN_71000145a0(s64 param_1, s64 param_2)
{
    if (*(s64 **)(param_2 + 0x8f0) != (s64 *)0x0) {
        return **(s64 **)(param_2 + 0x8f0) == param_1;
    }
    return false;
}

// 0x71000145c0 — bool: deref ptr at +0x8d0, compare to param_1 (32 bytes)
bool FUN_71000145c0(s64 param_1, s64 param_2)
{
    if (*(s64 **)(param_2 + 0x8d0) != (s64 *)0x0) {
        return **(s64 **)(param_2 + 0x8d0) == param_1;
    }
    return false;
}

// 0x7100014fc0 — setter: if param_2>=0 store+set bit, else clear+clear bit (64 bytes)
void FUN_7100014fc0(s64 param_1, s64 param_2)
{
    if (-1 < param_2) {
        *(s64 *)(param_1 + 0x9d8) = param_2;
        *(u32 *)(param_1 + 0xa08) = *(u32 *)(param_1 + 0xa08) | 0x40;
        return;
    }
    *(u64 *)(param_1 + 0x9d8) = 0;
    *(u32 *)(param_1 + 0xa08) = *(u32 *)(param_1 + 0xa08) & 0xffffffbf;
}

// 0x7100017450 — toUpper loop: copy param_2 to param_1, uppercasing as-you-go (80 bytes)
void FUN_7100017450(u8 *param_1, u8 *param_2, s64 param_3)
{
    u8 bVar1;
    u8 bVar2;

    if (param_3 != 0) {
        do {
            bVar2 = *param_2;
            bVar1 = bVar2 - 0x20;
            if (0x19 < bVar2 - 0x61) {
                bVar1 = bVar2;
            }
            *param_1 = bVar1;
            if (*param_2 == 0) {
                return;
            }
            param_2 = param_2 + 1;
            param_1 = param_1 + 1;
            param_3 = param_3 + -1;
        } while (param_3 != 0);
    }
}

// 0x7100017580 — guarded release: get counter, if param_2!=0 and zero, free param_1 (48 bytes)
s64 FUN_7100017580(u64 param_1, s64 param_2)
{
    s64 lVar1;

    lVar1 = FUN_71000272b0();
    if ((param_2 != 0) && (lVar1 == 0)) {
        FUN_71000272a0(param_1);
    }
    return lVar1;
}

// 0x710001ebb0 — linked-list search: find param_1 at *node, delete and return 1 (80 bytes)
u64 FUN_710001ebb0(s64 param_1, s64 *param_2)
{
    s64 *plVar1;

    if (param_2 != (s64 *)0x0) {
        for (plVar1 = (s64 *)*param_2; plVar1 != (s64 *)0x0; plVar1 = (s64 *)plVar1[2]) {
            if (*plVar1 == param_1) {
                FUN_7100006870(param_2, plVar1, 0);
                return 1;
            }
        }
    }
    return 0;
}

// 0x7100031140 — init: write version and float-pair constants (32 bytes)
void FUN_7100031140(u32 *param_1)
{
    *param_1 = 0x20202;
    *(u64 *)(param_1 + 1) = 0xc47a0000002a0100;
    *(u64 *)(param_1 + 3) = 0x447a0000;
}

// 0x71000311e0 — init: set 7 byte fields (32 bytes)
void FUN_71000311e0(u8 *param_1)
{
    param_1[1] = 1;
    param_1[2] = 0;
    param_1[3] = 0;
    param_1[4] = 1;
    *param_1 = *param_1 & 0xfe;
    param_1[5] = 0;
    param_1[6] = 0;
    param_1[7] = 0xf;
}

// 0x7100031210 — init: set float 1.0, clear fields, set flags (48 bytes)
void FUN_7100031210(u16 *param_1)
{
    *(u64 *)(param_1 + 6) = 0x3f80000000000000;
    param_1[1] = param_1[1] & 0xfff0;
    *(u64 *)(param_1 + 2) = 0;
    *(u64 *)(param_1 + 0xc) = 0;
    *param_1 = 0x500;
}

// 0x7100031250 — init: set channel/type flags across multiple fields (48 bytes)
void FUN_7100031250(u16 *param_1)
{
    *param_1 = 0xff01;
    *(u8 *)(param_1 + 1) = 0xff;
    *(u32 *)(param_1 + 4) = 0x7000000;
    *(u8 *)(param_1 + 6) = 0;
    param_1[2] = param_1[2] & 0xfff0;
    *(u32 *)(param_1 + 0xc) = 0x7000000;
    *(u8 *)(param_1 + 0xe) = 0;
}

// 0x7100031360 — init: write descriptor constants to struct (48 bytes)
void FUN_7100031360(u16 *param_1)
{
    *param_1 = 1;
    *(u64 *)(param_1 + 2) = 0x504030200000000;
    *(u32 *)(param_1 + 8) = 0x10000;
    *(u64 *)(param_1 + 0x10) = 0x100000000;
    *(u64 *)(param_1 + 0x18) = 0;
}

// 0x7100031390 — init: set type byte, clear count fields (32 bytes)
void FUN_7100031390(u8 *param_1)
{
    *param_1 = 1;
    *(u64 *)(param_1 + 4) = 0;
    *(u16 *)(param_1 + 2) = 0;
    *(u32 *)(param_1 + 0xc) = 1;
    *(u64 *)(param_1 + 0x18) = 0;
}

// 0x71000313b0 — init: set type, clear fields, set stride (32 bytes)
void FUN_71000313b0(u8 *param_1)
{
    *param_1 = 1;
    *(u16 *)(param_1 + 2) = 0;
    *(u64 *)(param_1 + 8) = 0x100000000;
    *(u64 *)(param_1 + 0x18) = 0;
}

// 0x71000314e0 — setter: set type byte, OR flags byte, store param_2 (32 bytes)
void FUN_71000314e0(u8 *param_1, u64 param_2)
{
    *param_1 = 1;
    param_1[1] = param_1[1] | 1;
    *(u64 *)(param_1 + 8) = param_2;
}

// 0x7100031510 — table lookup: return DAT_710446f0e0[(param_1-0x27)&u32] or 4 (32 bytes)
u32 FUN_7100031510(s32 param_1)
{
    if (param_1 - 0x27U < 0x14) {
        return *(u32 *)(&DAT_710446f0e0 + (s64)(s32)(param_1 - 0x27U) * 4);
    }
    return 4;
}

// 0x7100031540 — table lookup: return DAT_710446f090[(param_1-0x27)&u32] or 4 (32 bytes)
u32 FUN_7100031540(s32 param_1)
{
    if (param_1 - 0x27U < 0x14) {
        return *(u32 *)(&DAT_710446f090 + (s64)(s32)(param_1 - 0x27U) * 4);
    }
    return 4;
}

// 0x7100031850 — zero-init: clear 9 u64 fields (out of order) (48 bytes)
void FUN_7100031850(u64 *param_1)
{
    param_1[7] = 0;
    param_1[8] = 0;
    *param_1 = 0;
    param_1[5] = 0;
    param_1[6] = 0;
    param_1[3] = 0;
    param_1[4] = 0;
    param_1[1] = 0;
    param_1[2] = 0;
}

// 0x7100031a60 — vtable dispatch: call fn at *PTR_DAT_71052a22b8 with 0x13 opcode (48 bytes)
s64 FUN_7100031a60(u64 *param_1)
{
    s32 local_14;

    (**(void (**)(u64, u32, s32 *))PTR_DAT_71052a22b8)(*param_1, 0x13, &local_14);
    return (s64)local_14;
}
