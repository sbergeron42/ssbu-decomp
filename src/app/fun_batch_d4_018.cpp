#include "types.h"

// MEDIUM-tier FUN_* functions — mixed 0x7100 ranges, batch d4-018
// Pool-d worker: auto-generated from Ghidra decompilation
// Includes: vtable-ptr lookup switch, singleton guards (+0x318 store), opcode membership test

// ---- External declarations -----------------------------------------------

// FUN_710064b730 — vtable pointer lookup table (95 unique targets)
extern u8 DAT_7104fe35d0; // case 0
extern u8 DAT_7104fa9110; // case 1
extern u8 DAT_7104fd71c8; // case 2
extern u8 DAT_71050354c0; // case 3
extern u8 DAT_7105037740; // case 4
extern u8 DAT_7105058238; // case 5
extern u8 DAT_7104fcc698; // case 6
extern u8 DAT_7104fb6b98; // case 7
extern u8 DAT_7105012ad8; // case 8
extern u8 DAT_7104fe15c8; // case 9
extern u8 DAT_7104ffd300; // case 0xa
extern u8 DAT_7104f98ab0; // case 0xb
extern u8 DAT_710501f7b8; // case 0xc
extern u8 DAT_7105008ea8; // case 0xd
extern u8 DAT_7104f9db40; // case 0xe
extern u8 DAT_7104fcf8a8; // case 0xf
extern u8 DAT_7105039690; // case 0x10
extern u8 DAT_710505ca00; // case 0x11
extern u8 DAT_7104fe5410; // case 0x12
extern u8 DAT_710500ca00; // case 0x13
extern u8 DAT_7104fb45e8; // case 0x14
extern u8 DAT_7104fe7430; // case 0x15
extern u8 DAT_7104fdf970; // case 0x16
extern u8 DAT_710505a528; // case 0x17
extern u8 DAT_7104fbb778; // case 0x18
extern u8 DAT_7104fed590; // case 0x19
extern u8 DAT_71050313e8; // case 0x1a
extern u8 DAT_7104f9a120; // case 0x1b
extern u8 DAT_7104fb9390; // case 0x1c
extern u8 DAT_7104feb710; // case 0x1d
extern u8 DAT_7105017030; // case 0x1e
extern u8 DAT_7105018c80; // case 0x1f
extern u8 DAT_7105048168; // case 0x20
extern u8 DAT_7105050e20; // case 0x21
extern u8 DAT_7105043718; // case 0x22
extern u8 DAT_7104fc1dd0; // case 0x23
extern u8 DAT_71050212e8; // case 0x24
extern u8 DAT_710500b158; // case 0x25
extern u8 DAT_710501a938; // case 0x26
extern u8 DAT_7104fa4588; // case 0x27
extern u8 DAT_7104fdd6f0; // case 0x28
extern u8 DAT_71050459e0; // case 0x29
extern u8 DAT_7104f9fad8; // case 0x2a
extern u8 DAT_7105014e78; // case 0x2b
extern u8 DAT_7104fdb558; // case 0x2c
extern u8 DAT_71050294a0; // case 0x2d
extern u8 DAT_710504cbc8; // case 0x2e
extern u8 DAT_7105055cf0; // case 0x2f
extern u8 DAT_7104ffa0b8; // case 0x30
extern u8 DAT_710502c3e8; // case 0x31
extern u8 DAT_7105053ed8; // case 0x32
extern u8 DAT_710502f718; // case 0x33
extern u8 DAT_7104fd9620; // case 0x34
extern u8 DAT_7104fbf748; // case 0x35
extern u8 DAT_71050050f0; // case 0x36
extern u8 DAT_71050014c0; // case 0x37
extern u8 DAT_7105023418; // case 0x38
extern u8 DAT_710503e390; // case 0x39
extern u8 DAT_7104fd29d8; // case 0x3a
extern u8 DAT_7104faa9e0; // case 0x3b
extern u8 DAT_7105032dd8; // case 0x3c
extern u8 DAT_7104fcac58; // case 0x3d
extern u8 DAT_7104f9bd78; // case 0x3e
extern u8 DAT_7104fc8fe0; // case 0x3f
extern u8 DAT_7104f91020; // case 0x40
extern u8 DAT_7104fc3b78; // case 0x41
extern u8 DAT_7105026f38; // case 0x42
extern u8 DAT_7105040b20; // case 0x43
extern u8 DAT_71050253a0; // case 0x44
extern u8 DAT_7104fd4e28; // case 0x45
extern u8 DAT_710503c308; // case 0x46
extern u8 DAT_7104fbd790; // case 0x47
extern u8 DAT_7104ff33c0; // case 0x48
extern u8 DAT_7104ff7c70; // case 0x49
extern u8 DAT_7104ff4f68; // case 0x4a
extern u8 DAT_710501d110; // cases 0x4b, 0x4c
extern u8 DAT_7104fd0e40; // case 0x4d
extern u8 DAT_7104fef610; // case 0x4e
extern u8 DAT_7104ff2058; // case 0x4f
extern u8 DAT_7104ff0978; // case 0x50
extern u8 DAT_7104fff6b8; // case 0x51
extern u8 DAT_7104fc6528; // case 0x52
extern u8 DAT_7104f93668; // case 0x53
extern u8 DAT_7104f965e0; // case 0x54
extern u8 DAT_7104fa6d98; // case 0x55
extern u8 DAT_7104fe9060; // case 0x56
extern u8 DAT_710504a728; // case 0x57
extern u8 DAT_7105010490; // case 0x58
extern u8 DAT_7104fad340; // case 0x59
extern u8 DAT_7104fafe58; // case 0x5a
extern u8 DAT_7104fb2430; // case 0x5b
extern u8 DAT_7104fa2530; // case 0x5c
extern u8 DAT_710504ee80; // case 0x5d
extern u8 DAT_7104fb0298; // case 0x73
extern u8 DAT_7104fb28d8; // case 0x74
extern "C" void abort();

// Singleton guard globals (18 functions × guard/data/ptrlabel)
extern u64 DAT_71052bb470; extern u64 DAT_71052bb478; extern u64 PTR_LAB_7104f98f40;
extern u64 DAT_71052bb4d0; extern u64 DAT_71052bb4d8; extern u64 PTR_LAB_7104fa0118;
extern u64 DAT_71052c1b80; extern u64 DAT_71052c1b88; extern u64 PTR_LAB_7105056140;
extern u64 DAT_71052bb660; extern u64 DAT_71052bb668; extern u64 PTR_LAB_7104fbbb68;
extern u64 DAT_71052bb698; extern u64 DAT_71052bb6a0; extern u64 PTR_LAB_7104fc40b0;
extern u64 DAT_71052c0d50; extern u64 DAT_71052c0d58; extern u64 PTR_LAB_7104fd2e98;
extern u64 DAT_71052c0d80; extern u64 DAT_71052c0d88; extern u64 PTR_LAB_7104fd7690;
extern u64 DAT_71052c0d90; extern u64 DAT_71052c0d98; extern u64 PTR_LAB_7104fddbe0;
extern u64 DAT_71052c0da0; extern u64 DAT_71052c0da8; extern u64 PTR_LAB_7104fe19f8;
extern u64 DAT_71052c0dd0; extern u64 DAT_71052c0dd8; extern u64 PTR_LAB_7104fe5858;
extern u64 DAT_71052c0df8; extern u64 DAT_71052c0e00; extern u64 PTR_LAB_7104febb20;
extern u64 DAT_71052c0e58; extern u64 DAT_71052c0e60; extern u64 PTR_LAB_7104ffa720;
extern u64 DAT_71052c0f28; extern u64 DAT_71052c0f30; extern u64 PTR_LAB_71050055c0;
extern u64 DAT_71052c0f38; extern u64 DAT_71052c0f40; extern u64 PTR_LAB_71050092d8;
extern u64 DAT_71052c0f58; extern u64 DAT_71052c0f60; extern u64 PTR_LAB_7105012f38;
extern u64 DAT_71052c0f68; extern u64 DAT_71052c0f70; extern u64 PTR_LAB_71050152c0;
extern u64 DAT_71052c0fc0; extern u64 DAT_71052c0fc8; extern u64 PTR_LAB_710501d5c0;
extern u64 DAT_71052c1918; extern u64 DAT_71052c1920; extern u64 PTR_LAB_710502ca60;

extern "C" s32 __cxa_guard_acquire(u64 *);
extern "C" void __cxa_guard_release(u64 *);

// ---- Functions ---------------------------------------------------------------

// 0x710064b730 — vtable-ptr lookup: switch on param_1, return pointer to vtable data
u8 *FUN_710064b730(u32 param_1)
{
    switch (param_1) {
    default:
        abort();
    case 0: return &DAT_7104fe35d0;
    case 1: return &DAT_7104fa9110;
    case 2: return &DAT_7104fd71c8;
    case 3: return &DAT_71050354c0;
    case 4: return &DAT_7105037740;
    case 5: return &DAT_7105058238;
    case 6: return &DAT_7104fcc698;
    case 7: return &DAT_7104fb6b98;
    case 8: return &DAT_7105012ad8;
    case 9: return &DAT_7104fe15c8;
    case 0xa: return &DAT_7104ffd300;
    case 0xb: return &DAT_7104f98ab0;
    case 0xc: return &DAT_710501f7b8;
    case 0xd: return &DAT_7105008ea8;
    case 0xe: return &DAT_7104f9db40;
    case 0xf: return &DAT_7104fcf8a8;
    case 0x10: return &DAT_7105039690;
    case 0x11: return &DAT_710505ca00;
    case 0x12: return &DAT_7104fe5410;
    case 0x13: return &DAT_710500ca00;
    case 0x14: return &DAT_7104fb45e8;
    case 0x15: return &DAT_7104fe7430;
    case 0x16: return &DAT_7104fdf970;
    case 0x17: return &DAT_710505a528;
    case 0x18: return &DAT_7104fbb778;
    case 0x19: return &DAT_7104fed590;
    case 0x1a: return &DAT_71050313e8;
    case 0x1b: return &DAT_7104f9a120;
    case 0x1c: return &DAT_7104fb9390;
    case 0x1d: return &DAT_7104feb710;
    case 0x1e: return &DAT_7105017030;
    case 0x1f: return &DAT_7105018c80;
    case 0x20: return &DAT_7105048168;
    case 0x21: return &DAT_7105050e20;
    case 0x22: return &DAT_7105043718;
    case 0x23: return &DAT_7104fc1dd0;
    case 0x24: return &DAT_71050212e8;
    case 0x25: return &DAT_710500b158;
    case 0x26: return &DAT_710501a938;
    case 0x27: return &DAT_7104fa4588;
    case 0x28: return &DAT_7104fdd6f0;
    case 0x29: return &DAT_71050459e0;
    case 0x2a: return &DAT_7104f9fad8;
    case 0x2b: return &DAT_7105014e78;
    case 0x2c: return &DAT_7104fdb558;
    case 0x2d: return &DAT_71050294a0;
    case 0x2e: return &DAT_710504cbc8;
    case 0x2f: return &DAT_7105055cf0;
    case 0x30: return &DAT_7104ffa0b8;
    case 0x31: return &DAT_710502c3e8;
    case 0x32: return &DAT_7105053ed8;
    case 0x33: return &DAT_710502f718;
    case 0x34: return &DAT_7104fd9620;
    case 0x35: return &DAT_7104fbf748;
    case 0x36: return &DAT_71050050f0;
    case 0x37: return &DAT_71050014c0;
    case 0x38: return &DAT_7105023418;
    case 0x39: return &DAT_710503e390;
    case 0x3a: return &DAT_7104fd29d8;
    case 0x3b: return &DAT_7104faa9e0;
    case 0x3c: return &DAT_7105032dd8;
    case 0x3d: return &DAT_7104fcac58;
    case 0x3e: return &DAT_7104f9bd78;
    case 0x3f: return &DAT_7104fc8fe0;
    case 0x40: return &DAT_7104f91020;
    case 0x41: return &DAT_7104fc3b78;
    case 0x42: return &DAT_7105026f38;
    case 0x43: return &DAT_7105040b20;
    case 0x44: return &DAT_71050253a0;
    case 0x45: return &DAT_7104fd4e28;
    case 0x46: return &DAT_710503c308;
    case 0x47: return &DAT_7104fbd790;
    case 0x48: return &DAT_7104ff33c0;
    case 0x49: return &DAT_7104ff7c70;
    case 0x4a: return &DAT_7104ff4f68;
    case 0x4b:
    case 0x4c: return &DAT_710501d110;
    case 0x4d: return &DAT_7104fd0e40;
    case 0x4e: return &DAT_7104fef610;
    case 0x4f: return &DAT_7104ff2058;
    case 0x50: return &DAT_7104ff0978;
    case 0x51: return &DAT_7104fff6b8;
    case 0x52: return &DAT_7104fc6528;
    case 0x53: return &DAT_7104f93668;
    case 0x54: return &DAT_7104f965e0;
    case 0x55: return &DAT_7104fa6d98;
    case 0x56: return &DAT_7104fe9060;
    case 0x57: return &DAT_710504a728;
    case 0x58: return &DAT_7105010490;
    case 0x59: return &DAT_7104fad340;
    case 0x5a: return &DAT_7104fafe58;
    case 0x5b: return &DAT_7104fb2430;
    case 0x5c: return &DAT_7104fa2530;
    case 0x5d: return &DAT_710504ee80;
    case 0x73: return &DAT_7104fb0298;
    case 0x74: return &DAT_7104fb28d8;
    }
}

// 0x71006d5560 — conditional offset: return param_1+0x60 or param_1+0x10
s64 FUN_71006d5560(s64 param_1)
{
    s64 result;

    result = param_1 + 0x60;
    if (*(s32 *)(param_1 + 0x70) < 1) {
        result = param_1 + 0x10;
    }
    return result;
}

// 0x71008b75a0 — singleton guard: init vtable ptr, store &DAT at param_2+0x318
void FUN_71008b75a0(u64 param_1, s64 param_2)
{
    s32 acquired;

    if ((DAT_71052bb470 & 1) == 0) {
        acquired = __cxa_guard_acquire(&DAT_71052bb470);
        if (acquired != 0) {
            DAT_71052bb478 = (u64)&PTR_LAB_7104f98f40;
            __cxa_guard_release(&DAT_71052bb470);
        }
    }
    *(u64 **)(param_2 + 0x318) = &DAT_71052bb478;
}

// 0x7100903c10 — singleton guard: init vtable ptr, store &DAT at param_2+0x318
void FUN_7100903c10(u64 param_1, s64 param_2)
{
    s32 acquired;

    if ((DAT_71052bb4d0 & 1) == 0) {
        acquired = __cxa_guard_acquire(&DAT_71052bb4d0);
        if (acquired != 0) {
            DAT_71052bb4d8 = (u64)&PTR_LAB_7104fa0118;
            __cxa_guard_release(&DAT_71052bb4d0);
        }
    }
    *(u64 **)(param_2 + 0x318) = &DAT_71052bb4d8;
}

// 0x7100a615e0 — singleton guard: init vtable ptr, store &DAT at param_2+0x318
void FUN_7100a615e0(u64 param_1, s64 param_2)
{
    s32 acquired;

    if ((DAT_71052c1b80 & 1) == 0) {
        acquired = __cxa_guard_acquire(&DAT_71052c1b80);
        if (acquired != 0) {
            DAT_71052c1b88 = (u64)&PTR_LAB_7105056140;
            __cxa_guard_release(&DAT_71052c1b80);
        }
    }
    *(u64 **)(param_2 + 0x318) = &DAT_71052c1b88;
}

// 0x7100aa64a0 — singleton guard: init vtable ptr, store &DAT at param_2+0x318
void FUN_7100aa64a0(u64 param_1, s64 param_2)
{
    s32 acquired;

    if ((DAT_71052bb660 & 1) == 0) {
        acquired = __cxa_guard_acquire(&DAT_71052bb660);
        if (acquired != 0) {
            DAT_71052bb668 = (u64)&PTR_LAB_7104fbbb68;
            __cxa_guard_release(&DAT_71052bb660);
        }
    }
    *(u64 **)(param_2 + 0x318) = &DAT_71052bb668;
}

// 0x7100b0abf0 — singleton guard: init vtable ptr, store &DAT at param_2+0x318, set +0xe8=6
void FUN_7100b0abf0(u64 param_1, s64 param_2)
{
    s32 acquired;

    if ((DAT_71052bb698 & 1) == 0) {
        acquired = __cxa_guard_acquire(&DAT_71052bb698);
        if (acquired != 0) {
            DAT_71052bb6a0 = (u64)&PTR_LAB_7104fc40b0;
            __cxa_guard_release(&DAT_71052bb698);
        }
    }
    *(u64 **)(param_2 + 0x318) = &DAT_71052bb6a0;
    *(u8 *)(param_2 + 0xe8) = 6;
}

// 0x7100be3740 — singleton guard: init vtable ptr, store &DAT at param_2+0x318
void FUN_7100be3740(u64 param_1, s64 param_2)
{
    s32 acquired;

    if ((DAT_71052c0d50 & 1) == 0) {
        acquired = __cxa_guard_acquire(&DAT_71052c0d50);
        if (acquired != 0) {
            DAT_71052c0d58 = (u64)&PTR_LAB_7104fd2e98;
            __cxa_guard_release(&DAT_71052c0d50);
        }
    }
    *(u64 **)(param_2 + 0x318) = &DAT_71052c0d58;
}

// 0x7100c28080 — singleton guard: init vtable ptr, store &DAT at param_2+0x318
void FUN_7100c28080(u64 param_1, s64 param_2)
{
    s32 acquired;

    if ((DAT_71052c0d80 & 1) == 0) {
        acquired = __cxa_guard_acquire(&DAT_71052c0d80);
        if (acquired != 0) {
            DAT_71052c0d88 = (u64)&PTR_LAB_7104fd7690;
            __cxa_guard_release(&DAT_71052c0d80);
        }
    }
    *(u64 **)(param_2 + 0x318) = &DAT_71052c0d88;
}

// 0x7100c72fd0 — singleton guard: init vtable ptr, store &DAT at param_2+0x318
void FUN_7100c72fd0(u64 param_1, s64 param_2)
{
    s32 acquired;

    if ((DAT_71052c0d90 & 1) == 0) {
        acquired = __cxa_guard_acquire(&DAT_71052c0d90);
        if (acquired != 0) {
            DAT_71052c0d98 = (u64)&PTR_LAB_7104fddbe0;
            __cxa_guard_release(&DAT_71052c0d90);
        }
    }
    *(u64 **)(param_2 + 0x318) = &DAT_71052c0d98;
}

// 0x7100ca0c70 — singleton guard: init vtable ptr, store &DAT at param_2+0x318
void FUN_7100ca0c70(u64 param_1, s64 param_2)
{
    s32 acquired;

    if ((DAT_71052c0da0 & 1) == 0) {
        acquired = __cxa_guard_acquire(&DAT_71052c0da0);
        if (acquired != 0) {
            DAT_71052c0da8 = (u64)&PTR_LAB_7104fe19f8;
            __cxa_guard_release(&DAT_71052c0da0);
        }
    }
    *(u64 **)(param_2 + 0x318) = &DAT_71052c0da8;
}

// 0x7100cc8da0 — singleton guard: init vtable ptr, store &DAT at param_2+0x318
void FUN_7100cc8da0(u64 param_1, s64 param_2)
{
    s32 acquired;

    if ((DAT_71052c0dd0 & 1) == 0) {
        acquired = __cxa_guard_acquire(&DAT_71052c0dd0);
        if (acquired != 0) {
            DAT_71052c0dd8 = (u64)&PTR_LAB_7104fe5858;
            __cxa_guard_release(&DAT_71052c0dd0);
        }
    }
    *(u64 **)(param_2 + 0x318) = &DAT_71052c0dd8;
}

// 0x7100d12b10 — singleton guard: init vtable ptr, store &DAT at param_2+0x318, set +0xe8=6
void FUN_7100d12b10(u64 param_1, s64 param_2)
{
    s32 acquired;

    if ((DAT_71052c0df8 & 1) == 0) {
        acquired = __cxa_guard_acquire(&DAT_71052c0df8);
        if (acquired != 0) {
            DAT_71052c0e00 = (u64)&PTR_LAB_7104febb20;
            __cxa_guard_release(&DAT_71052c0df8);
        }
    }
    *(u64 **)(param_2 + 0x318) = &DAT_71052c0e00;
    *(u8 *)(param_2 + 0xe8) = 6;
}

// 0x7100dba7a0 — singleton guard: init vtable ptr, store &DAT at param_2+0x318
void FUN_7100dba7a0(u64 param_1, s64 param_2)
{
    s32 acquired;

    if ((DAT_71052c0e58 & 1) == 0) {
        acquired = __cxa_guard_acquire(&DAT_71052c0e58);
        if (acquired != 0) {
            DAT_71052c0e60 = (u64)&PTR_LAB_7104ffa720;
            __cxa_guard_release(&DAT_71052c0e58);
        }
    }
    *(u64 **)(param_2 + 0x318) = &DAT_71052c0e60;
}

// 0x7100e5e630 — singleton guard: init vtable ptr, store &DAT at param_2+0x318
void FUN_7100e5e630(u64 param_1, s64 param_2)
{
    s32 acquired;

    if ((DAT_71052c0f28 & 1) == 0) {
        acquired = __cxa_guard_acquire(&DAT_71052c0f28);
        if (acquired != 0) {
            DAT_71052c0f30 = (u64)&PTR_LAB_71050055c0;
            __cxa_guard_release(&DAT_71052c0f28);
        }
    }
    *(u64 **)(param_2 + 0x318) = &DAT_71052c0f30;
}

// 0x7100e88c30 — singleton guard: init vtable ptr, store &DAT at param_2+0x318
void FUN_7100e88c30(u64 param_1, s64 param_2)
{
    s32 acquired;

    if ((DAT_71052c0f38 & 1) == 0) {
        acquired = __cxa_guard_acquire(&DAT_71052c0f38);
        if (acquired != 0) {
            DAT_71052c0f40 = (u64)&PTR_LAB_71050092d8;
            __cxa_guard_release(&DAT_71052c0f38);
        }
    }
    *(u64 **)(param_2 + 0x318) = &DAT_71052c0f40;
}

// 0x7100f2a4b0 — singleton guard: init vtable ptr, store &DAT at param_2+0x318
void FUN_7100f2a4b0(u64 param_1, s64 param_2)
{
    s32 acquired;

    if ((DAT_71052c0f58 & 1) == 0) {
        acquired = __cxa_guard_acquire(&DAT_71052c0f58);
        if (acquired != 0) {
            DAT_71052c0f60 = (u64)&PTR_LAB_7105012f38;
            __cxa_guard_release(&DAT_71052c0f58);
        }
    }
    *(u64 **)(param_2 + 0x318) = &DAT_71052c0f60;
}

// 0x7100f51310 — singleton guard: init vtable ptr, store &DAT at param_2+0x318
void FUN_7100f51310(u64 param_1, s64 param_2)
{
    s32 acquired;

    if ((DAT_71052c0f68 & 1) == 0) {
        acquired = __cxa_guard_acquire(&DAT_71052c0f68);
        if (acquired != 0) {
            DAT_71052c0f70 = (u64)&PTR_LAB_71050152c0;
            __cxa_guard_release(&DAT_71052c0f68);
        }
    }
    *(u64 **)(param_2 + 0x318) = &DAT_71052c0f70;
}

// 0x7100fb59a0 — singleton guard: init vtable ptr, store &DAT at param_2+0x318
void FUN_7100fb59a0(u64 param_1, s64 param_2)
{
    s32 acquired;

    if ((DAT_71052c0fc0 & 1) == 0) {
        acquired = __cxa_guard_acquire(&DAT_71052c0fc0);
        if (acquired != 0) {
            DAT_71052c0fc8 = (u64)&PTR_LAB_710501d5c0;
            __cxa_guard_release(&DAT_71052c0fc0);
        }
    }
    *(u64 **)(param_2 + 0x318) = &DAT_71052c0fc8;
}

// 0x7100fb6710 — opcode membership test: return 1 for select opcodes, 0 otherwise
u64 FUN_7100fb6710(s32 param_1)
{
    switch (param_1) {
    case 0xc0: case 0xc1: case 0xc4: case 0xc5: case 0xc6:
    case 0xe6: case 0xe9: case 0xea: case 0xed: case 0xee:
    case 0xef: case 0xf0: case 0xf1: case 0xf3: case 0xf4:
    case 0xf5: case 0xf6: case 0xf7: case 0xfe: case 0x146:
    case 0x176: case 0x178: case 0x179: case 0x17a: case 0x17b:
    case 0x17c: case 0x1be:
        return 1;
    case 0xc2: case 0xc3: case 199: case 200: case 0xc9:
    case 0xca: case 0xcb: case 0xcc: case 0xcd: case 0xce:
    case 0xcf: case 0xd0: case 0xd1: case 0xd2: case 0xd3:
    case 0xd4: case 0xd5: case 0xd6: case 0xd7: case 0xd8:
    case 0xd9: case 0xda: case 0xdb: case 0xdc: case 0xdd:
    case 0xde: case 0xdf: case 0xe0: case 0xe1: case 0xe2:
    case 0xe3: case 0xe4: case 0xe5: case 0xe7: case 0xe8:
    case 0xeb: case 0xec: case 0xf2: case 0xf8: case 0xf9:
    case 0xfa: case 0xfb: case 0xfc: case 0xfd: case 0xff:
    case 0x100: case 0x101: case 0x102: case 0x103: case 0x104:
    case 0x105: case 0x106: case 0x107: case 0x108: case 0x109:
    case 0x10a: case 0x10b: case 0x10c: case 0x10d: case 0x10e:
    case 0x10f: case 0x110: case 0x111: case 0x112: case 0x113:
    case 0x114: case 0x115: case 0x116: case 0x117: case 0x118:
    case 0x119: case 0x11a: case 0x11b: case 0x11c: case 0x11d:
    case 0x11e: case 0x11f: case 0x120: case 0x121: case 0x122:
    case 0x123: case 0x124: case 0x125: case 0x126: case 0x127:
    case 0x128: case 0x129: case 0x12a: case 299: case 300:
    case 0x12d: case 0x12e: case 0x12f: case 0x130: case 0x131:
    case 0x132: case 0x133: case 0x134: case 0x135: case 0x136:
    case 0x137: case 0x138: case 0x139: case 0x13a: case 0x13b:
    case 0x13c: case 0x13d: case 0x13e: case 0x13f: case 0x140:
    case 0x141: case 0x142: case 0x143: case 0x144: case 0x145:
    case 0x147: case 0x148: case 0x149: case 0x14a: case 0x14b:
    case 0x14c: case 0x14d: case 0x14e: case 0x14f: case 0x150:
    case 0x151: case 0x152: case 0x153: case 0x154: case 0x155:
    case 0x156: case 0x157: case 0x158: case 0x159: case 0x15a:
    case 0x15b: case 0x15c: case 0x15d: case 0x15e: case 0x15f:
    case 0x160: case 0x161: case 0x162: case 0x163: case 0x164:
    case 0x165: case 0x166: case 0x167: case 0x168: case 0x169:
    case 0x16a: case 0x16b: case 0x16c: case 0x16d: case 0x16e:
    case 0x16f: case 0x170: case 0x171: case 0x172: case 0x173:
    case 0x174: case 0x175: case 0x177: case 0x17d: case 0x17e:
    case 0x17f: case 0x180: case 0x181: case 0x182: case 0x183:
    case 0x184: case 0x185: case 0x186: case 0x187: case 0x188:
    case 0x189: case 0x18a: case 0x18b: case 0x18c: case 0x18d:
    case 0x18e: case 399: case 400: case 0x191: case 0x192:
    case 0x193: case 0x194: case 0x195: case 0x196: case 0x197:
    case 0x198: case 0x199: case 0x19a: case 0x19b: case 0x19c:
    case 0x19d: case 0x19e: case 0x19f: case 0x1a0: case 0x1a1:
    case 0x1a2: case 0x1a3: case 0x1a4: case 0x1a5: case 0x1a6:
    case 0x1a7: case 0x1a8: case 0x1a9: case 0x1aa: case 0x1ab:
    case 0x1ac: case 0x1ad: case 0x1ae: case 0x1af: case 0x1b0:
    case 0x1b1: case 0x1b2: case 0x1b3: case 0x1b4: case 0x1b5:
    case 0x1b6: case 0x1b7: case 0x1b8: case 0x1b9: case 0x1ba:
    case 0x1bb: case 0x1bc: case 0x1bd:
        return 0;
    default:
        if ((u32)(param_1 - 0x41) > 3) {
            return 0;
        }
        return 1;
    }
}

// 0x710107dae0 — singleton guard: init vtable ptr, store &DAT at param_2+0x318, set +0xe8=7
void FUN_710107dae0(u64 param_1, s64 param_2)
{
    s32 acquired;

    if ((DAT_71052c1918 & 1) == 0) {
        acquired = __cxa_guard_acquire(&DAT_71052c1918);
        if (acquired != 0) {
            DAT_71052c1920 = (u64)&PTR_LAB_710502ca60;
            __cxa_guard_release(&DAT_71052c1918);
        }
    }
    *(u64 **)(param_2 + 0x318) = &DAT_71052c1920;
    *(u8 *)(param_2 + 0xe8) = 7;
}
