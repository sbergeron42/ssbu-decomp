#include "types.h"

// MEDIUM-tier FUN_* functions — address range 0x7100031000–0x7100050000
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

// -- FUN_71000313f0 ----------------------------------------------------------
// SetDefault: init struct with pointer+constants
// 71000313f0
void FUN_71000313f0(u64* param_1)
{
    param_1[2] = 0x100000001ULL;
    param_1[0] = 0;
    param_1[1] = 0x100000000ULL;
    *(u16*)(param_1 + 3) = 0;
    *(u64*)((u8*)param_1 + 0x1c) = 0x100000000ULL;
}

// -- FUN_7100031410 ----------------------------------------------------------
// SetDefault: init struct with pointer+constants
// 7100031410
void FUN_7100031410(u64* param_1)
{
    param_1[2] = 0;
    param_1[3] = 0x100000001ULL;
    *(u32*)(param_1 + 4) = 1;
    param_1[0] = 0;
    param_1[1] = 0;
    *(u16*)((u8*)param_1 + 0x24) = 0;
    param_1[5] = 0x100000000ULL;
}

// -- FUN_71000314e0 ----------------------------------------------------------
// Set active flag and pointer field
// 71000314e0
void FUN_71000314e0(u8* param_1, u64 param_2)
{
    param_1[0] = 1;
    param_1[1] = param_1[1] | 1;
    *(u64*)(param_1 + 8) = param_2;
}

// -- FUN_7100031510 ----------------------------------------------------------
// Table lookup for type code offset; return 4 for out-of-range
// 7100031510
u32 FUN_7100031510(s32 param_1)
{
    if ((u32)(param_1 - 0x27) < 0x14) {
        return DAT_710446f0e0[(s32)(param_1 - 0x27)];
    }
    return 4;
}

// -- FUN_7100031540 ----------------------------------------------------------
// Table lookup for type code offset (second table); return 4 for out-of-range
// 7100031540
u32 FUN_7100031540(s32 param_1)
{
    if ((u32)(param_1 - 0x27) < 0x14) {
        return DAT_710446f090[(s32)(param_1 - 0x27)];
    }
    return 4;
}

// -- FUN_71000316b0 ----------------------------------------------------------
// Compute pixel format from type/flags
// 71000316b0
u32 FUN_71000316b0(s32 param_1, u64 param_2, u64 param_3)
{
    u32 uVar1, uVar2;
    if (param_1 == 3) return 2;
    if (param_1 == 2) {
        uVar2 = 6; uVar1 = 7;
        if ((param_3 & 1) == 0) { uVar2 = 1; uVar1 = 5; }
        if ((param_2 & 1) != 0) uVar2 = uVar1;
        return uVar2;
    }
    if (param_1 != 1) {
        nn__detail__UnexpectedDefaultImpl("", "", 0);
    }
    uVar1 = 4;
    if ((param_2 & 1) == 0) uVar1 = 0;
    return uVar1;
}

// -- FUN_7100031850 ----------------------------------------------------------
// SetDefault: zero 9 u64 fields in reverse-pair order
// 7100031850
void FUN_7100031850(u64* param_1)
{
    param_1[7] = 0; param_1[8] = 0;
    param_1[0] = 0;
    param_1[5] = 0; param_1[6] = 0;
    param_1[3] = 0; param_1[4] = 0;
    param_1[1] = 0; param_1[2] = 0;
}

// -- FUN_7100031a60 ----------------------------------------------------------
// Call function ptr at PTR_DAT_71052a22b8 with (param_1[0], 0x13, &out); return out as s64
// 7100031a60
s64 FUN_7100031a60(u64* param_1)
{
    s32 local_14;
    typedef void (*FnT)(u64, u32, s32*);
    (**(FnT**)&PTR_DAT_71052a22b8)(*param_1, 0x13, &local_14);
    return (s64)local_14;
}

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

// -- FUN_7100037790 ----------------------------------------------------------
// Table lookup: return u32 from DAT_71044705bc at index param_1*8
// 7100037790
u32 FUN_7100037790(u64 param_1)
{
    return DAT_71044705bc[(param_1 & 0xffffffff) * 2];
}

// -- FUN_7100037cb0 ----------------------------------------------------------
// Lazy-init singleton struct via __cxa_guard; return pointer to it
// 7100037cb0
u64* FUN_7100037cb0()
{
    if (((DAT_71052aa330 & 1) == 0) && (__cxa_guard_acquire(&DAT_71052aa330) != 0)) {
        DAT_71052aa370 = 0; DAT_71052aa378 = 0;
        DAT_71052aa360 = 0; DAT_71052aa368 = 0;
        DAT_71052aa338 = 0; DAT_71052aa350 = 0;
        DAT_71052aa358 = 0; DAT_71052aa340 = 0;
        DAT_71052aa348 = 0;
        __cxa_guard_release(&DAT_71052aa330);
    }
    return &DAT_71052aa338;
}

// -- FUN_71000380b0 ----------------------------------------------------------
// Reset field at *(param_1+0x28)+0x30 to 0; call FUN_71000339b0 if +0x30 == +0x20
// 71000380b0
void FUN_71000380b0(u8* param_1)
{
    u8* lVar1 = *(u8**)(param_1 + 0x28);
    if (*(u64*)(lVar1 + 0x30) != *(u64*)(lVar1 + 0x20)) {
        *(u64*)(lVar1 + 0x30) = 0;
        return;
    }
    FUN_71000339b0();
    *(u64*)(lVar1 + 0x30) = 0;
}

// -- FUN_7100038120 ----------------------------------------------------------
// SetDefault: zero 15 u64 fields in reverse-pair order
// 7100038120
void FUN_7100038120(u64* param_1)
{
    param_1[0xd] = 0; param_1[0xe] = 0;
    param_1[0]   = 0;
    param_1[0xb] = 0; param_1[0xc] = 0;
    param_1[9]   = 0; param_1[10]  = 0;
    param_1[7]   = 0; param_1[8]   = 0;
    param_1[5]   = 0; param_1[6]   = 0;
    param_1[3]   = 0; param_1[4]   = 0;
    param_1[1]   = 0; param_1[2]   = 0;
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

// -- FUN_7100039e30 ----------------------------------------------------------
// SetDefault: zero 9 u64 fields in reverse-pair order (identical to FUN_7100031850)
// 7100039e30
void FUN_7100039e30(u64* param_1)
{
    param_1[7] = 0; param_1[8] = 0;
    param_1[0] = 0;
    param_1[5] = 0; param_1[6] = 0;
    param_1[3] = 0; param_1[4] = 0;
    param_1[1] = 0; param_1[2] = 0;
}

// -- FUN_710003a0e0 ----------------------------------------------------------
// SetDefault: zero 27 u64 fields in reverse-pair order
// 710003a0e0
void FUN_710003a0e0(u64* param_1)
{
    param_1[0x19] = 0; param_1[0x1a] = 0;
    param_1[0]    = 0;
    param_1[0x17] = 0; param_1[0x18] = 0;
    param_1[0x15] = 0; param_1[0x16] = 0;
    param_1[0x13] = 0; param_1[0x14] = 0;
    param_1[0x11] = 0; param_1[0x12] = 0;
    param_1[0xf]  = 0; param_1[0x10] = 0;
    param_1[0xd]  = 0; param_1[0xe]  = 0;
    param_1[0xb]  = 0; param_1[0xc]  = 0;
    param_1[9]    = 0; param_1[10]   = 0;
    param_1[7]    = 0; param_1[8]    = 0;
    param_1[5]    = 0; param_1[6]    = 0;
    param_1[3]    = 0; param_1[4]    = 0;
    param_1[1]    = 0; param_1[2]    = 0;
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

// -- FUN_710003a240 ----------------------------------------------------------
// SetDefault: zero 9 u64 fields in reverse-pair order
// 710003a240
void FUN_710003a240(u64* param_1)
{
    param_1[7] = 0; param_1[8] = 0;
    param_1[0] = 0;
    param_1[5] = 0; param_1[6] = 0;
    param_1[3] = 0; param_1[4] = 0;
    param_1[1] = 0; param_1[2] = 0;
}

// -- FUN_710003a3c0 ----------------------------------------------------------
// SetDefault: zero 9 u64 fields in reverse-pair order
// 710003a3c0
void FUN_710003a3c0(u64* param_1)
{
    param_1[7] = 0; param_1[8] = 0;
    param_1[0] = 0;
    param_1[5] = 0; param_1[6] = 0;
    param_1[3] = 0; param_1[4] = 0;
    param_1[1] = 0; param_1[2] = 0;
}

// -- FUN_710003a4e0 ----------------------------------------------------------
// SetDefault: zero 9 u64 fields in reverse-pair order
// 710003a4e0
void FUN_710003a4e0(u64* param_1)
{
    param_1[7] = 0; param_1[8] = 0;
    param_1[0] = 0;
    param_1[5] = 0; param_1[6] = 0;
    param_1[3] = 0; param_1[4] = 0;
    param_1[1] = 0; param_1[2] = 0;
}

// -- FUN_710003a7d0 ----------------------------------------------------------
// SetDefault: zero 24 u64 fields in pairs (high to low)
// 710003a7d0
void FUN_710003a7d0(u64* param_1)
{
    param_1[0x16] = 0; param_1[0x17] = 0;
    param_1[0x14] = 0; param_1[0x15] = 0;
    param_1[0x12] = 0; param_1[0x13] = 0;
    param_1[0x10] = 0; param_1[0x11] = 0;
    param_1[0xe]  = 0; param_1[0xf]  = 0;
    param_1[0xc]  = 0; param_1[0xd]  = 0;
    param_1[10]   = 0; param_1[0xb]  = 0;
    param_1[8]    = 0; param_1[9]    = 0;
    param_1[6]    = 0; param_1[7]    = 0;
    param_1[4]    = 0; param_1[5]    = 0;
    param_1[2]    = 0; param_1[3]    = 0;
    param_1[0]    = 0; param_1[1]    = 0;
}

// -- FUN_710003aac0 ----------------------------------------------------------
// Init struct with vtable ptr from PTR_DAT_71052a3328+0x10, and fields
// 710003aac0
void FUN_710003aac0(u64* param_1, u32 param_2, u32 param_3)
{
    param_1[2] = 0;
    *(u32*)(param_1 + 3) = param_2;
    *(u32*)((u8*)param_1 + 0x1c) = 2;
    *(u32*)(param_1 + 4) = param_3;
    *(u64*)((u8*)param_1 + 0x24) = 0;
    param_1[6] = 0;
    param_1[7] = 0;
    *param_1 = (u64)((u8*)PTR_DAT_71052a3328 + 0x10);
    param_1[1] = 0;
}

// -- FUN_710003ac20 ----------------------------------------------------------
// Set protocol version field: 1 for <=0xffff, 2 for larger
// 710003ac20
void FUN_710003ac20(u8* param_1, s32 param_2)
{
    u32 uVar1 = 1;
    if (0xffff < param_2) uVar1 = 2;
    *(u32*)(param_1 + 0x1c) = uVar1;
    *(s32*)(param_1 + 0x28) = param_2;
}

// -- FUN_710003bc80 ----------------------------------------------------------
// Init struct with vtable ptr from PTR_DAT_71052a3390+0x10, and fields
// 710003bc80
void FUN_710003bc80(u64* param_1)
{
    param_1[2] = 0;
    param_1[3] = 0;
    *param_1 = (u64)((u8*)PTR_DAT_71052a3390 + 0x10);
    param_1[1] = 0x1f00000000ULL;
    *(u32*)(param_1 + 4) = 0;
}

// -- FUN_710003c350 ----------------------------------------------------------
// State machine step: for state 0/2 call vtable fns; for 4/6 return 0; else return 1
// 710003c350
u64 FUN_710003c350(u64* param_1)
{
    switch ((s32)param_1[1]) {
    case 0:
    case 2:
        (*(void(**)(u64*, u32))(param_1[0] + 0xd8))(param_1, 1);
        (*(void(**)(u64*))(param_1[0] + 0x98))(param_1);
        break;
    case 4:
    case 6:
        return 0;
    }
    return 1;
}

// -- FUN_710003de30 ----------------------------------------------------------
// State machine step: for state 0/2/5 call vtable fns; for 4/6 return 0; else return 1
// 710003de30
u64 FUN_710003de30(u64* param_1)
{
    switch ((s32)param_1[1]) {
    case 0:
    case 2:
    case 5:
        (*(void(**)(u64*, u32))(param_1[0] + 0xd8))(param_1, 1);
        (*(void(**)(u64*))(param_1[0] + 0x98))(param_1);
        break;
    case 4:
    case 6:
        return 0;
    }
    return 1;
}

// -- FUN_710003e030 ----------------------------------------------------------
// State machine step: identical pattern to FUN_710003de30
// 710003e030
u64 FUN_710003e030(u64* param_1)
{
    switch ((s32)param_1[1]) {
    case 0:
    case 2:
    case 5:
        (*(void(**)(u64*, u32))(param_1[0] + 0xd8))(param_1, 1);
        (*(void(**)(u64*))(param_1[0] + 0x98))(param_1);
        break;
    case 4:
    case 6:
        return 0;
    }
    return 1;
}

// -- FUN_7100044c70 ----------------------------------------------------------
// Set fields at param_1+0x18c/0x190/0x198/0xc0
// 7100044c70
void FUN_7100044c70(u8* param_1, u64 param_2)
{
    *(u8*)(param_1 + 0x18c) = 1;
    *(u64*)(param_1 + 400) = 0;
    *(u16*)(param_1 + 0x198) = 0;
    *(u64*)(param_1 + 0xc0) = param_2;
}
