#include "types.h"

// MEDIUM-tier FUN_* functions -- address range 0x7100145000-0x7100165000
// Pool-d worker: auto-generated from Ghidra decompilation

extern void* PTR_DAT_71052a3bd0;
extern u8*   PTR_DAT_71052a3bd8;
extern void* PTR_DAT_71052a4f38;

extern "C" void* FUN_710015f5c0();

// -- FUN_710014f090 ----------------------------------------------------------
// Copy 3 u32 fields from param_2+8/c/10 to param_1+8/c/10
// 710014f090
void FUN_710014f090(u8* param_1, u8* param_2)
{
    *(u32*)(param_1 + 0x10) = *(u32*)(param_2 + 0x10);
    *(u32*)(param_1 + 8)    = *(u32*)(param_2 + 8);
    *(u32*)(param_1 + 0xc)  = *(u32*)(param_2 + 0xc);
}
