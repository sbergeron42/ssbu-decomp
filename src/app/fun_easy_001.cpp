#include "types.h"

// EASY-tier FUN_* functions — address range 0x7101xxxxxx
// Pool-b worker: manually decompiled from Ghidra

// External functions
extern "C" void FUN_71015b8290(u32, u64, u64);
extern "C" void FUN_71015b8600(u32, u64, u64);

// External labels (vtable pointers)
extern u64 PTR_LAB_71050aff48;
extern u64 PTR_LAB_71050bf4d0;

// 710138a720
u64 FUN_710138a720(void) { return 1; }

// 710141a940
void FUN_710141a940(void) {}

// 710159d5d0
void FUN_710159d5d0(void) {}

// 710159d8b0
void FUN_710159d8b0(void) {}

// 71015c97f0
void FUN_71015c97f0(void) {}

// 71015c9810
void FUN_71015c9810(u64 param_1, u64 *param_2, u64 *param_3) {
    FUN_71015b8290(*(u32*)(param_1 + 8), *param_2, *param_3);
}

// 71015c9a00
void FUN_71015c9a00(void) {}

// 71015c9a20
void FUN_71015c9a20(u64 param_1, u64 *param_2, u64 *param_3) {
    FUN_71015b8600(*(u32*)(param_1 + 8), *param_2, *param_3);
}

// 71015c9c10
void FUN_71015c9c10(void) {}

// 71015c9d30
void FUN_71015c9d30(void) {}

// 7101e017e0
void FUN_7101e017e0(u64 param_1, u64 *param_2) {
    *param_2 = (u64)&PTR_LAB_71050aff48;
}

// 7101e02810
void FUN_7101e02810(void) {}
