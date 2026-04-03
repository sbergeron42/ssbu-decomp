#include "types.h"

// MEDIUM-tier FUN_* functions — 0x7100 address range, batch d3-020
// Pool-d worker: auto-generated from Ghidra decompilation

// ---- Functions ---------------------------------------------------------------
// 0x710015e200 — GetNextSendSequenceId: increment u16, skip 0 (32 bytes)
s32 FUN_710015e200(s64 param_1)
{
    s32 iVar1;
    u16 uVar2;

    uVar2 = *(u16 *)(param_1 + 8);
    iVar1 = uVar2 + 2;
    if ((uVar2 + 1 & 0xffff) != 0) {
        iVar1 = uVar2 + 1;
    }
    *(s16 *)(param_1 + 8) = (s16)iVar1;
    return iVar1;
}
