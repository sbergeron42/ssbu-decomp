#include "types.h"

// MEDIUM-tier FUN_* functions — address range 0x71001d000–0x71002c000
// Pool-d worker: auto-generated from Ghidra decompilation

extern void* PTR_DAT_71052a3da8;
extern void* PTR_DAT_71052a3db8;
extern u16   DAT_71052b4278;
extern u16*  DAT_71052b4270;
extern u64   DAT_71052b4450;
extern u64   DAT_71052b4458;
extern u32   DAT_71052b4448;
extern void* PTR_DAT_71052a6540;
extern void** PTR_PTR_DAT_71052a6570;

extern "C" void* FUN_7101717b00(u64);
extern "C" void  FUN_71001f2180(u8*);
extern "C" void  FUN_71001f24a0(u8*);
extern "C" void  FUN_71001b3cb0(u8*, void*);
extern "C" void* FUN_71002c31d0(u8*);

extern void* PTR_s_personal_7104f60978[];
extern void* PTR_s_playing_inactivity_7104f609b0[];

// -- FUN_71001d05a0 ----------------------------------------------------------
// Read u64 from stream: check 8 bytes remain; advance cursor; return value
// 71001d05a0
u64 FUN_71001d05a0(u8* param_1, u64* param_2)
{
    s64 lVar1 = *(s64*)(param_1 + 0x10);
    s64 lVar2 = *(s64*)(param_1 + 0x18);
    if ((u64)(*(s64*)(lVar1 + 0x18) - lVar2) < 8) {
        param_1[8] = 1;
        return 0;
    }
    u64 uVar3 = *(u64*)(*(s64*)(lVar1 + 0x10) + *(s64*)(lVar1 + 0x28) + lVar2);
    *(s64*)(param_1 + 0x18) = lVar2 + 8;
    *param_2 = uVar3;
    return 1;
}

// -- FUN_71001d7780 ----------------------------------------------------------
// Reset stream cursors to base+size or just base
// 71001d7780
void FUN_71001d7780(u8* param_1)
{
    if (*(u64*)(param_1 + 0x30) != 0) {
        s64 lVar1 = *(s64*)(param_1 + 0x10) + *(s64*)(param_1 + 0x30);
        *(s64*)(param_1 + 0x18) = lVar1;
        *(s64*)(param_1 + 0x20) = lVar1;
        return;
    }
    *(u64*)(param_1 + 0x18) = *(u64*)(param_1 + 0x10);
    *(u64*)(param_1 + 0x20) = *(u64*)(param_1 + 0x10);
}

// -- FUN_71001df870 ----------------------------------------------------------
// Return ptr at +8; lazy-init via FUN_71001f2180 if flag at +0x68 not set
// 71001df870
u64 FUN_71001df870(u8* param_1)
{
    if (*(s8*)(param_1 + 0x68) != '\0') return *(u64*)(param_1 + 8);
    FUN_71001f2180(param_1);
    return *(u64*)(param_1 + 8);
}

// -- FUN_71001f30d0 ----------------------------------------------------------
// Return ptr at +0x60; lazy-init via FUN_71001f24a0 if flag at +0x69 not set
// 71001f30d0
u64 FUN_71001f30d0(u8* param_1)
{
    if (*(s8*)(param_1 + 0x69) != '\0') return *(u64*)(param_1 + 0x60);
    FUN_71001f24a0(param_1);
    return *(u64*)(param_1 + 0x60);
}

// -- FUN_7100228150 ----------------------------------------------------------
// Set global state: store param_1/param_2, set flag (param_1!=0)
// 7100228150
void FUN_7100228150(u64 param_1, u64 param_2)
{
    DAT_71052b4450 = param_1;
    DAT_71052b4458 = param_2;
    DAT_71052b4448 = (u32)(param_1 != 0);
}

// -- FUN_710022b090 ----------------------------------------------------------
// Init struct with vtable from PTR_DAT_71052a6540+0x10; clear byte field
// 710022b090
void FUN_710022b090(u64* param_1)
{
    *(u8*)(param_1 + 1) = 0;
    *param_1 = (u64)((u8*)PTR_DAT_71052a6540 + 0x10);
}

// -- FUN_710022bcf0 ----------------------------------------------------------
// Dispatch via double-deref vtable at PTR_PTR_DAT_71052a6570 offset +0x28
// 710022bcf0
void FUN_710022bcf0(u64 param_1, u64 param_2, u64 param_3, u64 param_4)
{
    u64* obj = *PTR_PTR_DAT_71052a6570;
    (*(void(**)(u64*, u64, u64, u64, u64))((*obj) + 0x28))(obj, param_1, param_2, param_3, param_4);
}

// -- FUN_710022f060 ----------------------------------------------------------
// Copy u8+u32+u32 fields from param_2+8 to param_1+8
// 710022f060
void FUN_710022f060(u8* param_1, u8* param_2)
{
    *(u8*)(param_1 + 8)   = *(u8*)(param_2 + 8);
    *(u32*)(param_1 + 0xc) = *(u32*)(param_2 + 0xc);
    *(u32*)(param_1 + 0x10) = *(u32*)(param_2 + 0x10);
}

// -- FUN_71002315f0 ----------------------------------------------------------
// Call cleanup fn on old value at +0x28 (vtable[1]); store new param_2
// 71002315f0
void FUN_71002315f0(u8* param_1, u64 param_2)
{
    u64* p = *(u64**)(param_1 + 0x28);
    if (p != nullptr) {
        (*(void(**)(u64*))((*p) + 8))(p);
    }
    *(u64*)(param_1 + 0x28) = param_2;
}

// -- FUN_71002611f0 ----------------------------------------------------------
// Copy u8+u32+u32 fields from param_2+8 to param_1+8 (identical to FUN_710022f060)
// 71002611f0
void FUN_71002611f0(u8* param_1, u8* param_2)
{
    *(u8*)(param_1 + 8)    = *(u8*)(param_2 + 8);
    *(u32*)(param_1 + 0xc) = *(u32*)(param_2 + 0xc);
    *(u32*)(param_1 + 0x10) = *(u32*)(param_2 + 0x10);
}

// -- FUN_710028b440 ----------------------------------------------------------
// Copy u8+u16+u8 fields from param_2+8 to param_1+8
// 710028b440
void FUN_710028b440(u8* param_1, u8* param_2)
{
    *(u8*)(param_1 + 8)   = *(u8*)(param_2 + 8);
    *(u16*)(param_1 + 10) = *(u16*)(param_2 + 10);
    *(u8*)(param_1 + 0xc) = *(u8*)(param_2 + 0xc);
}

// -- FUN_710028b540 ----------------------------------------------------------
// Copy u8+u64+u16 fields from param_2+8 to param_1+8
// 710028b540
void FUN_710028b540(u8* param_1, u8* param_2)
{
    *(u8*)(param_1 + 8)    = *(u8*)(param_2 + 8);
    *(u64*)(param_1 + 0x10) = *(u64*)(param_2 + 0x10);
    *(u16*)(param_1 + 0x18) = *(u16*)(param_2 + 0x18);
}

// -- FUN_71002aeb40 ----------------------------------------------------------
// Set string field from table PTR_s_personal if param_2 in [1..7]
// 71002aeb40
u64 FUN_71002aeb40(u8* param_1, u32 param_2)
{
    if ((param_2 < 8) && (param_2 - 1 < 7)) {
        FUN_71001b3cb0(param_1 + 0x10, PTR_s_personal_7104f60978[(s32)(param_2 - 1)]);
        return 1;
    }
    return 0;
}

// -- FUN_71002aedf0 ----------------------------------------------------------
// Set string field from table PTR_s_playing_inactivity if param_2 in [1..6]
// 71002aedf0
u64 FUN_71002aedf0(u8* param_1, u32 param_2)
{
    if ((param_2 < 7) && (param_2 - 1 < 6)) {
        FUN_71001b3cb0(param_1 + 0x10, PTR_s_playing_inactivity_7104f609b0[(s32)(param_2 - 1)]);
        return 1;
    }
    return 0;
}

// -- FUN_71002b3510 ----------------------------------------------------------
// SetDefault: init struct with packed constant fields
// 71002b3510
void FUN_71002b3510(u64* param_1)
{
    param_1[0] = 0xb0100000b01ULL;
    param_1[1] = 0x100000001ULL;
    param_1[2] = 0x20000000200ULL;
    param_1[3] = 0x900000001ULL;
    param_1[4] = 0x1003f800000ULL;
    *(u32*)(param_1 + 5) = 0x10000;
}

// -- FUN_71002b3ed0 ----------------------------------------------------------
// SetDefault: zero 0x22*4 bytes + set one field to 3
// 71002b3ed0
void FUN_71002b3ed0(u32* param_1)
{
    *param_1 = 0;
    param_1[0x18] = 0;
    *(u64*)(param_1 + 0x14) = 0;
    *(u64*)(param_1 + 0x16) = 0;
    param_1[0x22] = 3;
    *(u64*)(param_1 + 2)    = 0;
    *(u64*)(param_1 + 0x1e) = 0;
    *(u64*)(param_1 + 0x20) = 0;
    *(u64*)(param_1 + 0x1a) = 0;
    *(u64*)(param_1 + 0x1c) = 0;
    *(u64*)(param_1 + 0x10) = 0;
    *(u64*)(param_1 + 0x12) = 0;
    *(u64*)(param_1 + 0xc)  = 0;
    *(u64*)(param_1 + 0xe)  = 0;
    *(u64*)(param_1 + 8)    = 0;
    *(u64*)(param_1 + 10)   = 0;
    *(u64*)(param_1 + 4)    = 0;
    *(u64*)(param_1 + 6)    = 0;
}

// -- FUN_71002b8160 ----------------------------------------------------------
// Compute offset into a 2D array: param_1 + param_2*0x30 + param_3*0x18 + 0x480c
// 71002b8160
s64 FUN_71002b8160(s64 param_1, u32 param_2, u32 param_3)
{
    return param_1 + (u64)param_2 * 0x30 + (u64)param_3 * 0x18 + 0x480c;
}

// -- FUN_71002ba540 ----------------------------------------------------------
// If flag at param_1+0x918+(param_2+1) set, call FUN_71002c31d0 on entry
// 71002ba540
u64 FUN_71002ba540(u8* param_1, u32 param_2)
{
    if (*(s8*)(param_1 + (u64)(param_2 + 1) + 0x918) != '\0') {
        return (u64)FUN_71002c31d0(param_1 + (u64)param_2 * 0x128 + 0x5a0);
    }
    return 0;
}

// -- FUN_71002bb310 ----------------------------------------------------------
// SetDefault: zero 14 u64 + u32 in reverse-pair order
// 71002bb310
void FUN_71002bb310(u64* param_1)
{
    *(u32*)(param_1 + 0xd) = 0;
    param_1[0xb] = 0; param_1[0xc] = 0;
    param_1[0]   = 0;
    param_1[9]   = 0; param_1[10]  = 0;
    param_1[7]   = 0; param_1[8]   = 0;
    param_1[5]   = 0; param_1[6]   = 0;
    param_1[3]   = 0; param_1[4]   = 0;
    param_1[1]   = 0; param_1[2]   = 0;
}

// -- FUN_71002c1f70 ----------------------------------------------------------
// Align-up: param_1+0x10 = (param_1+0x10 + param_2 - 1) & ~(param_2-1)
// 71002c1f70
void FUN_71002c1f70(u8* param_1, s64 param_2)
{
    *(u64*)(param_1 + 0x10) = (u64)((param_2 + *(s64*)(param_1 + 0x10)) - 1) & (u64)(-param_2);
}
