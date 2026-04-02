#include "types.h"

// EASY-tier FUN_* functions -- address range 0x7102xxxxxx
// Pool-b worker: manually decompiled from Ghidra

// External labels (vtable pointers)
extern u64 PTR_LAB_71050bf4d0 __attribute__((visibility("hidden")));

// 71024b8a00
void FUN_71024b8a00(u64 param_1, u64 *param_2) {
    *param_2 = (u64)&PTR_LAB_71050bf4d0;
}
