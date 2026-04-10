// fun_med_final_b_009.cpp — Matched functions from 0x71002c range
// Cleaned: removed 10 unmatched Ghidra paste functions, kept 2 verified (M)

#include "types.h"

extern "C" {
    void FUN_710003a0e0();
    void FUN_710003a240(void *p);
}

// 0x71002c2f70 — init slot: call setup helpers, set sentinel at +0x120 (quality=M)
void FUN_71002c2f70(long param_1) {
    FUN_710003a0e0();
    FUN_710003a240((void *)(param_1 + 0xd8));
    *(u64 *)(param_1 + 0x120) = 0xffffffffffffffffULL;
}

// 0x71002c31e0 — conditional store: if field != sentinel, reset; then copy from param_2 (quality=M)
void FUN_71002c31e0(long param_1, u64 *param_2) {
    if (*(long *)(param_1 + 0x120) != -1) {
        *(u64 *)(param_1 + 0x120) = 0xffffffffffffffffULL;
    }
    *(u64 *)(param_1 + 0x120) = *param_2;
}
