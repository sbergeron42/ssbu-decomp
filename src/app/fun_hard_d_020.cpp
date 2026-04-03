#include "types.h"

// HARD-tier FUN_* functions — 0x7100/0x7101 address range, batch hard-d-020
// Pool-d worker: node list walker, field clear loop, struct ctor, bit-set helper (112B each)

#define HIDDEN __attribute__((visibility("hidden")))

extern "C" {
    void abort(void);
}

// ---- External data -------------------------------------------------------

extern u8 *PTR_DAT_71052a2d80 HIDDEN;
extern u8 *PTR_DAT_71052a5ac8 HIDDEN;
extern u8  DAT_710440f4cc     HIDDEN;

// ---- External functions --------------------------------------------------

extern void FUN_71001b3cb0(s64, u8 *);

// ---- Functions ---------------------------------------------------------------

// 0x71000399e0 — walk node list, track max slot index, compute byte size (112 bytes)
s64 FUN_71000399e0(u16 *param_1)
{
    s32 iVar4;
    u64 uVar3 = (u64)*param_1;
    if (uVar3 == 0) {
        iVar4 = -1;
    } else {
        s64 *plVar5 = (s64 *)(*(s64 *)(param_1 + 4) + 0x10);
        iVar4 = -1;
        do {
            s16 sVar2;
            while ((sVar2 = *(s16 *)((s64)plVar5 - 0xe)) < 0) {
                iVar4 = 0xf;
                plVar5 += 5;
                if (--uVar3 == 0) goto done;
            }
            s32 iVar1 = (s32)sVar2;
            if (sVar2 <= (s16)iVar4) iVar1 = iVar4;
            iVar4 = 0xf;
            if (*plVar5 == 0) iVar4 = iVar1;
            plVar5 += 5;
            uVar3--;
        } while (uVar3 != 0);
    }
done:
    return (u64)param_1[1] * 8 + (s64)(iVar4 + 1) * 4;
}

// 0x71001549d0 — clear pairs of fields in loop over count at param_1+0x300 (112 bytes)
void FUN_71001549d0(s64 param_1)
{
    s32 iVar1 = *(s32 *)(param_1 + 0x300);
    if (iVar1 > 0) {
        u64 uVar2 = (u64)(s64)iVar1 & 1;
        s64 lVar3;
        if (iVar1 == 1) {
            lVar3 = 0;
        } else {
            lVar3 = 0;
            s64 lVar4 = param_1 + 0x20;
            do {
                lVar3 += 2;
                *(u64 *)(lVar4 - 0x1c) = 0;
                *(u64 *)(lVar4 - 4) = 0;
                lVar4 += 0x30;
            } while ((s64)iVar1 - (s64)uVar2 != lVar3);
        }
        if (uVar2 != 0) {
            *(u64 *)(param_1 + lVar3 * 0x18 + 4) = 0;
        }
    }
    *(u32 *)(param_1 + 0x304) = 0;
    *(u64 *)(param_1 + 0x328) = 0;
}

// 0x710024cf70 — struct ctor: init vtable, zero fields, set capacity/self-ptrs (112 bytes)
void FUN_710024cf70(s64 *param_1)
{
    u8 *puVar1 = PTR_DAT_71052a2d80 + 0x10;
    *(u8 *)(param_1 + 1) = 0;
    param_1[7] = (s64)puVar1;
    *(u8 *)(param_1 + 8) = 0;
    u8 *puVar2 = PTR_DAT_71052a5ac8;
    *(u32 *)((s64)param_1 + 0xc) = 0;
    *(u32 *)(param_1 + 4) = 0;
    param_1[2] = 0;
    param_1[3] = 0;
    *param_1 = (s64)(puVar2 + 0x10);
    *(u64 *)((s64)param_1 + 0x24) = 1;
    *(u64 *)((s64)param_1 + 0x2c) = 0x200;
    param_1[10] = (s64)(param_1 + 8);
    param_1[0xb] = 0x10;
    FUN_71001b3cb0((s64)(param_1 + 7), &DAT_710440f4cc);
}

// 0x71014151a0 — set/clear bit in flag array, bounds-checked with abort (112 bytes)
// Ghidra entry at 0x7101415180; triage address 0x71014151a0 is interior
void FUN_7101415180(s64 param_1, s32 param_2, u32 param_3, u32 param_4)
{
    if (param_2 != -1) {
        if ((u64)(s64)param_2 > 7 || param_3 > 2) {
            abort();
        }
        u64 uVar2 = 1ULL << ((s64)param_3 & 0x3f);
        u64 *puVar1 = (u64 *)(*(s64 *)(param_1 + 8) + (s64)param_2 * 8 + 800);
        if ((param_4 & 1) == 0) {
            uVar2 = *puVar1 & (uVar2 ^ 0xffffffffffffffffULL);
        } else {
            uVar2 = *puVar1 | uVar2;
        }
        *puVar1 = uVar2;
    }
}
