#include "types.h"

// MEDIUM-tier FUN_* functions -- address range 0x7100b000-0x71001500000
// Pool-d worker: auto-generated from Ghidra decompilation

extern void* PTR_DAT_71052a3d28;
extern void* PTR_DAT_71052a3ee8;

// SDK thread type (opaque)
struct ThreadType;
namespace nn { namespace os { void StartThread(ThreadType**); } }

extern "C" void FUN_71000bce50(u64, u32*);

// -- FUN_71000b71c0 ----------------------------------------------------------
// Dequeue head from doubly-linked list: unlink and return node
// 71000b71c0
u64* FUN_71000b71c0(u64* param_1)
{
    s32 iVar2 = *(s32*)(param_1 + 2);
    if (iVar2 != 0) {
        u64* plVar3 = (u64*)*param_1;
        u64  lVar1  = *plVar3;
        *(u64*)(lVar1 + 8) = plVar3[1];
        *(u64*)plVar3[1]   = lVar1;
        *plVar3   = 0;
        plVar3[1] = 0;
        *(s32*)(param_1 + 2) = iVar2 - 1;
        return plVar3;
    }
    return nullptr;
}

// -- FUN_71000bed20 ----------------------------------------------------------
// Init struct: set vtable ptr from PTR_DAT_71052a3d28+0x10, clear field
// 71000bed20
void FUN_71000bed20(u64* param_1)
{
    param_1[2] = 0;
    *param_1 = (u64)((u8*)PTR_DAT_71052a3d28 + 0x10);
}

// -- FUN_71000bf2f0 ----------------------------------------------------------
// Check magic, type, and version range
// 71000bf2f0
bool FUN_71000bf2f0(u8* param_1)
{
    if ((*(s32*)(param_1 + 8) == 0x32ab9864) && ((*(u8*)(param_1 + 0xc) & 0x7f) == 4)) {
        return (u32)(*(s32*)(param_1 + 0x5e8) - 0x20) < 0x5a1;
    }
    return false;
}

// -- FUN_71000c4d40 ----------------------------------------------------------
// Check vtable fn result from +0x50 ptr; clear +0xc0 if ok
// 71000c4d40
u64* FUN_71000c4d40(u8* param_1)
{
    u64* plVar1 = *(u64**)(param_1 + 0x50);
    if (plVar1 != nullptr) {
        u64 uVar2 = (*(u64(*)(u64*))((*plVar1) + 0x28))(plVar1);
        if ((uVar2 & 1) == 0) return nullptr;
        *(u64*)(param_1 + 0xc0) = 0;
        return (u64*)1;
    }
    return plVar1;
}

// -- FUN_71000cf5c0 ----------------------------------------------------------
// Init struct: vtable from PTR_DAT_71052a3ee8+0x10, clear fields
// 71000cf5c0
void FUN_71000cf5c0(u64* param_1)
{
    *(u32*)(param_1 + 1) = 0;
    *(u8*)((u8*)param_1 + 0xc) = 0;
    param_1[2] = 0;
    *param_1 = (u64)((u8*)PTR_DAT_71052a3ee8 + 0x10);
    *(u32*)(param_1 + 3) = 0;
}

// -- FUN_71000eb680 ----------------------------------------------------------
// Map param_1 to result: 2→5, 1→4, else→0
// 71000eb680
s32 FUN_71000eb680(s32 param_1)
{
    s32 iVar1 = 5;
    if (param_1 != 2) {
        iVar1 = (u32)(param_1 == 1) << 2;
    }
    return iVar1;
}

// -- FUN_7100112c40 ----------------------------------------------------------
// Copy 8 bytes (u16+6 bytes) from param_2+8 to param_1+0x260
// 7100112c40
void FUN_7100112c40(u8* param_1, u8* param_2)
{
    *(u16*)(param_1 + 0x260) = *(u16*)(param_2 + 8);
    *(u8*)(param_1 + 0x262)  = *(u8*)(param_2 + 10);
    *(u8*)(param_1 + 0x263)  = *(u8*)(param_2 + 0xb);
    *(u8*)(param_1 + 0x264)  = *(u8*)(param_2 + 0xc);
    *(u8*)(param_1 + 0x265)  = *(u8*)(param_2 + 0xd);
    *(u8*)(param_1 + 0x266)  = *(u8*)(param_2 + 0xe);
    *(u8*)(param_1 + 0x267)  = *(u8*)(param_2 + 0xf);
}

// -- FUN_71001133a0 ----------------------------------------------------------
// Set u16 fields at +0xa38/+0xa3a; set bit 2 in flag at +0xd30
// 71001133a0
void FUN_71001133a0(u8* param_1, u16 param_2)
{
    *(u16*)(param_1 + 0xa38) = 0xffff;
    *(u16*)(param_1 + 0xa3a) = param_2;
    *(u32*)(param_1 + 0xd30) = *(u32*)(param_1 + 0xd30) | 2;
}

// -- FUN_71001133c0 ----------------------------------------------------------
// Set u16 fields at +0xa38/+0xa3a from params; set bit 2 in flag
// 71001133c0
void FUN_71001133c0(u8* param_1, u16 param_2, u16 param_3)
{
    *(u16*)(param_1 + 0xa38) = param_3;
    *(u16*)(param_1 + 0xa3a) = param_2;
    *(u32*)(param_1 + 0xd30) = *(u32*)(param_1 + 0xd30) | 2;
}

// -- FUN_71001133e0 ----------------------------------------------------------
// Set bit field at +0xa3c bit 0 from param_2; set bit 4 in flag
// 71001133e0
void FUN_71001133e0(u8* param_1, u8 param_2)
{
    *(u8*)(param_1 + 0xa3c) = param_2 & 1;
    *(u32*)(param_1 + 0xd30) = *(u32*)(param_1 + 0xd30) | 4;
}

// -- FUN_7100113400 ----------------------------------------------------------
// Set bit field at +0xa3d bit 0 from param_2; set bit 8 in flag
// 7100113400
void FUN_7100113400(u8* param_1, u8 param_2)
{
    *(u8*)(param_1 + 0xa3d) = param_2 & 1;
    *(u32*)(param_1 + 0xd30) = *(u32*)(param_1 + 0xd30) | 8;
}

// -- FUN_7100113480 ----------------------------------------------------------
// Set bit field at +0x9ca bit 0 from param_2; set bit 0x1000 in flag
// 7100113480
void FUN_7100113480(u8* param_1, u8 param_2)
{
    *(u8*)(param_1 + 0x9ca) = param_2 & 1;
    *(u32*)(param_1 + 0xd30) = *(u32*)(param_1 + 0xd30) | 0x1000;
}

// -- FUN_71001134a0 ----------------------------------------------------------
// Set bit field at +0x9cb bit 0 from param_2; set bit 0x2000 in flag
// 71001134a0
void FUN_71001134a0(u8* param_1, u8 param_2)
{
    *(u8*)(param_1 + 0x9cb) = param_2 & 1;
    *(u32*)(param_1 + 0xd30) = *(u32*)(param_1 + 0xd30) | 0x2000;
}

// -- FUN_71001136c0 ----------------------------------------------------------
// Set bit field at +0xa08 bit 0 from param_2; set bit 0x100000 in flag
// 71001136c0
void FUN_71001136c0(u8* param_1, u8 param_2)
{
    *(u8*)(param_1 + 0xa08) = param_2 & 1;
    *(u32*)(param_1 + 0xd30) = *(u32*)(param_1 + 0xd30) | 0x100000;
}

// -- FUN_71001158e0 ----------------------------------------------------------
// Conditionally set fields and set bit 0x2000; guard: param_2 < 2
// 71001158e0
void FUN_71001158e0(u8* param_1, u32 param_2, u8 param_3)
{
    if (param_2 < 2) {
        *(u8*)(param_1 + 0x14)  = param_3 & 1;
        *(u32*)(param_1 + 0x10) = param_2;
        *(u32*)(param_1 + 0x628) = *(u32*)(param_1 + 0x628) | 0x2000;
    }
}

// -- FUN_710012eb20 ----------------------------------------------------------
// Set u16 at +0x256 and +0x258; set bit 1 in flag at +0x260
// 710012eb20
void FUN_710012eb20(u8* param_1, u16 param_2)
{
    *(u16*)(param_1 + 0x256) = param_2;
    *(u16*)(param_1 + 600)   = param_2;
    *(u32*)(param_1 + 0x260) = *(u32*)(param_1 + 0x260) | 1;
}

// -- FUN_710012eb40 ----------------------------------------------------------
// Set u16 at +0x25a and +0x25c; set bit 2 in flag at +0x260
// 710012eb40
void FUN_710012eb40(u8* param_1, u16 param_2)
{
    *(u16*)(param_1 + 0x25a) = param_2;
    *(u16*)(param_1 + 0x25c) = param_2;
    *(u32*)(param_1 + 0x260) = *(u32*)(param_1 + 0x260) | 2;
}

// -- FUN_710012eb60 ----------------------------------------------------------
// Set bit at +0x25e; set bit 4 in flag at +0x260
// 710012eb60
void FUN_710012eb60(u8* param_1, u8 param_2)
{
    *(u8*)(param_1 + 0x25e) = param_2 & 1;
    *(u32*)(param_1 + 0x260) = *(u32*)(param_1 + 0x260) | 4;
}

// -- FUN_710012eb80 ----------------------------------------------------------
// Set bit at +0x25f; set bit 8 in flag at +0x260
// 710012eb80
void FUN_710012eb80(u8* param_1, u8 param_2)
{
    *(u8*)(param_1 + 0x25f) = param_2 & 1;
    *(u32*)(param_1 + 0x260) = *(u32*)(param_1 + 0x260) | 8;
}

// -- FUN_7100130aa0 ----------------------------------------------------------
// Insert node param_2 after list head param_1 (doubly-linked)
// 7100130aa0
void FUN_7100130aa0(u8* param_1, u64* param_2)
{
    u64* puVar1 = *(u64**)(param_1 + 8);
    *(u64**)(param_1 + 8) = param_2;
    *param_2 = (u64)(param_1 - 8);  // note: param_1 is the list head itself at offset 0
    param_2[1] = (u64)puVar1;
    if (puVar1 != nullptr) {
        *puVar1 = (u64)param_2;
    }
}

// -- FUN_7100130ac0 ----------------------------------------------------------
// Insert node param_2 at head of list param_1 (doubly-linked, head-only)
// 7100130ac0
void FUN_7100130ac0(u64* param_1, u64* param_2)
{
    u64 lVar1 = *param_1;
    *param_1  = (u64)param_2;
    *param_2  = lVar1;
    param_2[1] = (u64)param_1;
    if (lVar1 != 0) {
        *(u64**)(lVar1 + 8) = param_2;
    }
}

// -- FUN_7100130b10 ----------------------------------------------------------
// Clear circular doubly-linked list: null all nodes, reset head to self
// 7100130b10
void FUN_7100130b10(u64* param_1)
{
    u64* puVar1 = (u64*)param_1[1];
    while (puVar1 != param_1) {
        u64* puVar2 = (u64*)puVar1[1];
        *puVar1   = 0;
        puVar1[1] = 0;
        puVar1    = puVar2;
    }
    *(u32*)(param_1 + 2) = 0;
    *param_1   = (u64)param_1;
    param_1[1] = (u64)param_1;
}

// -- FUN_71001354c0 ----------------------------------------------------------
// Popcount: count set bits in the low 32 bits of param_1
// 71001354c0
u32 FUN_71001354c0(u64 param_1)
{
    u32 uVar1 = (u32)param_1 - ((u32)(param_1 >> 1) & 0x55555555);
    uVar1 = (uVar1 >> 2 & 0x33333333) + (uVar1 & 0x33333333);
    uVar1 = (uVar1 + (uVar1 >> 4)) & 0x0f0f0f0f;
    uVar1 = uVar1 + (uVar1 >> 8);
    return (uVar1 + (uVar1 >> 0x10)) & 0x3f;
}

// -- FUN_710013dc90 ----------------------------------------------------------
// Copy u16+u8+u16+u8 fields from param_2+8 to param_1+8
// 710013dc90
void FUN_710013dc90(u8* param_1, u8* param_2)
{
    *(u16*)(param_1 + 8)  = *(u16*)(param_2 + 8);
    *(u8*)(param_1 + 10)  = *(u8*)(param_2 + 10);
    *(u16*)(param_1 + 0xc) = *(u16*)(param_2 + 0xc);
    *(u8*)(param_1 + 0xe) = *(u8*)(param_2 + 0xe);
}

// -- FUN_7100145a10 ----------------------------------------------------------
// Return true if +0x140==1 and +0x110 in [2..4]
// 7100145a10
bool FUN_7100145a10(u8* param_1)
{
    if (*(s32*)(param_1 + 0x140) == 1) {
        return (u32)(*(s32*)(param_1 + 0x110) - 2) < 3;
    }
    return false;
}

// -- FUN_7100145ce0 ----------------------------------------------------------
// Return true if +0x140==2 and +0x110 in [2..4]
// 7100145ce0
bool FUN_7100145ce0(u8* param_1)
{
    if (*(s32*)(param_1 + 0x140) == 2) {
        return (u32)(*(s32*)(param_1 + 0x110) - 2) < 3;
    }
    return false;
}
