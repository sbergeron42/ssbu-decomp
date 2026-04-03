#include "types.h"

// HARD-tier FUN_* functions — 0x7100 address range, batch hard-d-021
// Pool-d worker: bit-buffer flush (144B), curl session auth check (128B)

#define HIDDEN __attribute__((visibility("hidden")))

// ---- Functions ---------------------------------------------------------------

// 0x710002f370 — bit buffer flush: if count==0x10 write both bytes, else flush high byte (144 bytes)
void FUN_710002f370(s64 param_1)
{
    u8 uVar1;
    s32 iVar2;
    s64 lVar3;

    if (*(s32 *)(param_1 + 0x1734) == 0x10) {
        lVar3 = *(s64 *)(param_1 + 0x28);
        uVar1 = *(u8 *)(param_1 + 0x1730);
        *(s64 *)(param_1 + 0x28) = lVar3 + 1;
        *(u8 *)(*(s64 *)(param_1 + 0x10) + lVar3) = uVar1;
        lVar3 = *(s64 *)(param_1 + 0x28);
        *(s64 *)(param_1 + 0x28) = lVar3 + 1;
        iVar2 = 0;
        *(u8 *)(*(s64 *)(param_1 + 0x10) + lVar3) = *(u8 *)(param_1 + 0x1731);
        *(u16 *)(param_1 + 0x1730) = 0;
    } else {
        if (*(s32 *)(param_1 + 0x1734) < 8) {
            return;
        }
        lVar3 = *(s64 *)(param_1 + 0x28);
        uVar1 = *(u8 *)(param_1 + 0x1730);
        *(s64 *)(param_1 + 0x28) = lVar3 + 1;
        *(u8 *)(*(s64 *)(param_1 + 0x10) + lVar3) = uVar1;
        *(u16 *)(param_1 + 0x1730) = (u16)*(u8 *)(param_1 + 0x1731);
        iVar2 = *(s32 *)(param_1 + 0x1734) - 8;
    }
    *(s32 *)(param_1 + 0x1734) = iVar2;
}

// 0x7100014620 — check session head-node match and set active flag (128 bytes)
// Ghidra entry at 0x71000145e0; triage address 0x7100014620 is interior
u64 FUN_71000145e0(s64 param_1, s64 param_2)
{
    if (*(s8 *)(param_2 + 0x82d) != 0) {
        return 1;
    }
    if (*(s8 *)(param_2 + 0x8c9) != 0) {
        return 0;
    }
    if (*(s64 **)(param_2 + 0x8d0) == nullptr) {
        return 0;
    }
    if (**(s64 **)(param_2 + 0x8d0) != param_1) {
        return 0;
    }
    *(u8 *)(param_2 + 0x8c9) = 1;
    return 1;
}
