#include "types.h"

// MEDIUM-tier FUN_* functions -- address range 0x7100000000-0x7100040000
// Pool-d worker: auto-generated from Ghidra decompilation

// External globals
extern u64 DAT_71052a90e8;
extern u32 DAT_71052a90f0;
extern u8  DAT_71052a90f8;
extern u8  DAT_71052a9100[];
extern void* PTR_LAB_71052a21e0;
extern void* PTR_DAT_71052a21e8;

// External functions
extern "C" void FUN_7100027f90();
extern "C" void FUN_7100005b40();
extern "C" void FUN_7100026140();
extern "C" void FUN_7100004780();
extern "C" int  FUN_71000052d0(void*, int, void*, void*, void*);
extern "C" void FUN_7100006870(void*, void*, void*);
extern "C" u64  FUN_71000272d0(u64, int);

// -- FUN_7100005a70 ----------------------------------------------------------
// Lazy-init singleton: init DAT_71052a9100 once via FUN_71000052d0
// 7100005a70
u8* FUN_7100005a70()
{
    if ((DAT_71052a90f8 & 1) != 0) return DAT_71052a9100;
    int r = FUN_71000052d0(DAT_71052a9100, 7, PTR_LAB_71052a21e0, PTR_DAT_71052a21e8, nullptr);
    if (r != 0) return nullptr;
    DAT_71052a90f8 = 1;
    return DAT_71052a9100;
}

// -- FUN_710000bba0 ----------------------------------------------------------
// Remove node from intrusive list at param_1+0x4d58, matched by int key at vtable[0]+0x28
// 710000bba0
void FUN_710000bba0(u8* param_1, s32 param_2)
{
    u8* node = *(u8**)(param_1 + 0x4d58);
    if (node == nullptr) return;
    do {
        if (*(s32*)((*(u64*)node) + 0x28) == param_2) {
            FUN_7100006870(param_1 + 0x4d58, node, nullptr);
            return;
        }
        node = *(u8**)(node + 0x10);
    } while (node != nullptr);
}

// -- FUN_710001ef80 ----------------------------------------------------------
// Call vtable slot at +0x858+0x30 if non-null; set *param_2 = 0 on call, 1 if not callable
// 710001ef80
u64 FUN_710001ef80(u8* param_1, u8* param_2)
{
    if ((param_1 != nullptr) && (*(u64*)(*(u8**)(param_1 + 0x858) + 0x30) != 0)) {
        *param_2 = 0;
        u64 (*fn)() = *(u64(**)())(*(u8**)(param_1 + 0x858) + 0x30);
        return fn();
    }
    *param_2 = 1;
    return 0;
}

// -- FUN_710001efb0 ----------------------------------------------------------
// Call vtable slot at +0x858+0x38 if non-null; set *param_2 = 0 on call, 1 if not callable
// 710001efb0
u64 FUN_710001efb0(u8* param_1, u8* param_2)
{
    if ((param_1 != nullptr) && (*(u64*)(*(u8**)(param_1 + 0x858) + 0x38) != 0)) {
        *param_2 = 0;
        u64 (*fn)() = *(u64(**)())(*(u8**)(param_1 + 0x858) + 0x38);
        return fn();
    }
    *param_2 = 1;
    return 0;
}

// -- FUN_71000263c0 ----------------------------------------------------------
// Register entry: check param_1+0x4bc8, alloc 0xb8 via FUN_71000272d0, store back
// 71000263c0
u64 FUN_71000263c0(u8* param_1, u64 param_2)
{
    if (*(u64*)(param_1 + 0x4bc8) != 0) return 0;
    u64 alloc = FUN_71000272d0(param_2, 0xb8);
    if (alloc == 0) return 0x1b;
    *(u64*)(param_1 + 0x4bc8) = alloc;
    *(u64*)(param_1 + 0x658) = param_2;
    *(u64*)(param_1 + 0x4bd0) = 1;
    return 0;
}
