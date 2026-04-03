#include "types.h"

// MEDIUM-tier FUN_* functions -- address range 0x7100031000-0x7100050000
// Pool-d worker: auto-generated from Ghidra decompilation

// External globals (function pointer tables)
extern void* PTR_DAT_71052a22b8;
extern void* PTR_DAT_71052a2350;
extern void* PTR_DAT_71052a24e8;
extern void* PTR_DAT_71052a2ae8;
extern void* PTR_DAT_71052a2c78;
extern void* PTR_DAT_71052a3328;
extern void* PTR_DAT_71052a3390;
extern void* PTR_DAT_71052a21e0;

// External data tables
extern u32 DAT_710446f0e0[];
extern u32 DAT_710446f090[];
extern u32 DAT_71044705bc[];

// External globals for guard
extern u8  DAT_71052aa330;
extern u64 DAT_71052aa338, DAT_71052aa340, DAT_71052aa348, DAT_71052aa350;
extern u64 DAT_71052aa358, DAT_71052aa360, DAT_71052aa368, DAT_71052aa370;
extern u64 DAT_71052aa378;

// External functions
extern "C" void FUN_71000339b0();
extern "C" int  __cxa_guard_acquire(u8*);
extern "C" void __cxa_guard_release(u8*);
extern "C" void nn__detail__UnexpectedDefaultImpl(const char*, const char*, int);

// -- FUN_7100031aa0 ----------------------------------------------------------
// Call function ptr at PTR_DAT_71052a22b8 with (param_1[0], 0x14, &out); return out as s64
// 7100031aa0
s64 FUN_7100031aa0(u64* param_1)
{
    s32 local_14;
    typedef void (*FnT)(u64, u32, s32*);
    (**(FnT**)&PTR_DAT_71052a22b8)(*param_1, 0x14, &local_14);
    return (s64)local_14;
}

// -- FUN_7100031d70 ----------------------------------------------------------
// Call fn ptr at PTR_DAT_71052a2350 with *(param_1+0xb8); store result at +0xc0; set flag
// 7100031d70
void FUN_7100031d70(u8* param_1)
{
    typedef u64 (*FnT)(u64);
    u64 uVar1 = (**(FnT**)&PTR_DAT_71052a2350)(*(u64*)(param_1 + 0xb8));
    *(u64*)(param_1 + 0xc0) = uVar1;
    *param_1 = 1;
}

// -- FUN_7100033190 ----------------------------------------------------------
// If param_2 has flags 0x49c0: call fn ptr with (*(param_1+0xb8), 1)
// 7100033190
void FUN_7100033190(u8* param_1, u32 param_2)
{
    if ((param_2 & 0x49c0) != 0) {
        typedef void (*FnT)(u64, u32);
        (**(FnT**)&PTR_DAT_71052a24e8)(*(u64*)(param_1 + 0xb8), 1);
    }
}

// -- FUN_7100038210 ----------------------------------------------------------
// Call fn ptr at PTR_DAT_71052a2c78 with *(param_1+8); clear ptr; clear flag
// 7100038210
void FUN_7100038210(u8* param_1)
{
    typedef void (*FnT)(u64);
    (**(FnT**)&PTR_DAT_71052a2c78)(*(u64*)(param_1 + 8));
    *(u64*)(param_1 + 8) = 0;
    *param_1 = 0;
}

// -- FUN_710003a200 ----------------------------------------------------------
// Call fn ptr at PTR_DAT_71052a2ae8 with *(param_1+8); clear ptr; clear flag
// 710003a200
void FUN_710003a200(u8* param_1)
{
    typedef void (*FnT)(u64);
    (**(FnT**)&PTR_DAT_71052a2ae8)(*(u64*)(param_1 + 8));
    *(u64*)(param_1 + 8) = 0;
    *param_1 = 0;
}
