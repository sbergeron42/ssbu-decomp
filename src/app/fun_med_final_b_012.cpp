// fun_med_final_b_012.cpp — Matched functions from 0x71003f–0x710048 range
// Cleaned: removed 32 unmatched Ghidra paste functions, kept 3 verified (M)

#include "types.h"

extern "C" void *nn_os_GetCurrentThread();

// FUN_71003f8730 — vtable +0x260; invert low bit (36 bytes, quality=M)
// Named "CheckButtonOff" in community symbols
u32 FUN_71003f8730(long *param_1) {
    u32 result = (*(u32 (**)(void))(*param_1 + 0x260))();
    return ~result & 1;
}

// FUN_7100405d60 — status kind bitmask check (68 bytes, quality=M)
// Values 7–29 mapped through bitmask 0x500003
u32 FUN_7100405d60(long *param_1) {
    int status_kind = (*(int (**)(void))(*param_1 + 0x28))();
    if ((u32)(status_kind - 7) < 0x17u) {
        return 0x500003u >> ((u64)(status_kind - 7) & 0x1f) & 1;
    }
    return 0;
}

// FUN_710043ff00 — store current OS thread handle to global (28 bytes, quality=M)
static void *s_dat_7105331f18;
void FUN_710043ff00() {
    s_dat_7105331f18 = nn_os_GetCurrentThread();
}
