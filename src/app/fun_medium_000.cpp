#include "types.h"

// MEDIUM-tier FUN_* functions — address range 0x7100000000–0x7100040000
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
extern "C" void FUN_7100006870(void*, void*, int);
extern "C" u64  FUN_71000272d0(u64, int);

// -- FUN_7100000250 ----------------------------------------------------------
// Compare n bytes; returns 1 if equal, 0 if different (like memcmp returning bool)
// 7100000250
u64 FUN_7100000250(u8* param_1, u8* param_2, s32 param_3)
{
    if (param_3 < 1) return 1;
    s64 i = 0;
    do {
        if (*(s8*)(param_1 + i) != *(s8*)(param_2 + i)) return 0;
        i++;
    } while (i < param_3);
    return 1;
}

// -- FUN_71000007c0 ----------------------------------------------------------
// String hash % modulo: iterates bytes accumulating uVar3*0x492+byte, returns uVar3 % param_2
// 71000007c0
u32 FUN_71000007c0(u8* param_1, u32 param_2)
{
    u8  bVar1;
    u32 uVar2 = 0;
    u32 uVar3;
    do {
        uVar3 = uVar2;
        bVar1 = *param_1++;
        uVar2 = (u32)bVar1 + uVar3 * 0x492;
    } while (bVar1 != 0);
    uVar2 = 0;
    if (param_2 != 0) {
        uVar2 = uVar3 / param_2;
    }
    return uVar3 - uVar2 * param_2;
}

// -- FUN_7100000900 ----------------------------------------------------------
// Reference-counted finalization: decrement DAT_71052a90e8; if hits 0, run teardown
// 7100000900
void FUN_7100000900()
{
    if ((DAT_71052a90e8 != 0) && (DAT_71052a90e8 = DAT_71052a90e8 - 1, DAT_71052a90e8 == 0)) {
        FUN_7100027f90();
        FUN_7100005b40();
        if ((DAT_71052a90f0 & 1) != 0) {
            FUN_7100026140();
        }
        FUN_7100004780();
        DAT_71052a90f0 = 0;
    }
}

// -- FUN_7100002ac0 ----------------------------------------------------------
// Reverse scan: find last occurrence of param_2 in param_1[0..param_3-1]
// 7100002ac0
s8* FUN_7100002ac0(s8* param_1, s8 param_2, s64 param_3)
{
    if (param_3 - 1 >= 0) {
        s8* p = param_1 + param_3 - 1;
        do {
            if (*p == param_2) return p;
            p--;
        } while (param_1 <= p);
    }
    return nullptr;
}

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

// -- FUN_71000093f0 ----------------------------------------------------------
// Test bit flag param_2 in *(u64*)(param_1 + 0xe8)
// 71000093f0
u64 FUN_71000093f0(u64 param_1, s32 param_2)
{
    if (param_1 != 0) {
        param_1 = (u64)((*(u64*)(param_1 + 0xe8) & (u64)(s64)param_2) != 0);
    }
    return param_1;
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
            FUN_7100006870(param_1 + 0x4d58, node, 0);
            return;
        }
        node = *(u8**)(node + 0x10);
    } while (node != nullptr);
}

// -- FUN_710000c8f0 ----------------------------------------------------------
// Returns true if *(*(param_1+0xb70)+0x4024) == 2
// 710000c8f0
bool FUN_710000c8f0(u8* param_1)
{
    u8* p = *(u8**)(param_1 + 0xb70);
    if (p != nullptr) {
        return *(s32*)(p + 0x4024) == 2;
    }
    return false;
}

// -- FUN_710000c920 ----------------------------------------------------------
// Returns true if *(*(param_1+0xb70)+0x4024) != 2
// 710000c920
bool FUN_710000c920(u8* param_1)
{
    u8* p = *(u8**)(param_1 + 0xb70);
    if (p != nullptr) {
        return *(s32*)(p + 0x4024) != 2;
    }
    return false;
}

// -- FUN_71000145a0 ----------------------------------------------------------
// Returns true if *(*(param_2+0x8f0)) == param_1
// 71000145a0
bool FUN_71000145a0(u64 param_1, u8* param_2)
{
    u64* ptr = *(u64**)(param_2 + 0x8f0);
    if (ptr != nullptr) {
        return *ptr == param_1;
    }
    return false;
}

// -- FUN_71000145c0 ----------------------------------------------------------
// Returns true if *(*(param_2+0x8d0)) == param_1
// 71000145c0
bool FUN_71000145c0(u64 param_1, u8* param_2)
{
    u64* ptr = *(u64**)(param_2 + 0x8d0);
    if (ptr != nullptr) {
        return *ptr == param_1;
    }
    return false;
}

// -- FUN_7100014fc0 ----------------------------------------------------------
// Set signed value at +0x9d8; set/clear bit 0x40 in flag at +0xa08
// 7100014fc0
void FUN_7100014fc0(u8* param_1, s64 param_2)
{
    if (param_2 >= 0) {
        *(s64*)(param_1 + 0x9d8) = param_2;
        *(u32*)(param_1 + 0xa08) = *(u32*)(param_1 + 0xa08) | 0x40;
    } else {
        *(u64*)(param_1 + 0x9d8) = 0;
        *(u32*)(param_1 + 0xa08) = *(u32*)(param_1 + 0xa08) & 0xffffffbf;
    }
}

// -- FUN_7100017450 ----------------------------------------------------------
// Copy src to dst with toupper, stop at null or when n==0
// 7100017450
void FUN_7100017450(u8* param_1, u8* param_2, s64 param_3)
{
    if (param_3 == 0) return;
    do {
        u8 bVar2 = *param_2;
        u8 bVar1 = bVar2 - 0x20;
        if ((u8)(bVar2 - 0x61) > 0x19) {
            bVar1 = bVar2;
        }
        *param_1 = bVar1;
        if (*param_2 == 0) return;
        param_2++;
        param_1++;
        param_3--;
    } while (param_3 != 0);
}

// -- FUN_710001ebb0 ----------------------------------------------------------
// Remove node from singly-linked list (head at *param_2); returns 1 if found
// 710001ebb0
u64 FUN_710001ebb0(u64 param_1, u64* param_2)
{
    if (param_2 != nullptr) {
        for (u64* node = (u64*)*param_2; node != nullptr; node = (u64*)node[2]) {
            if (*node == param_1) {
                FUN_7100006870(param_2, node, 0);
                return 1;
            }
        }
    }
    return 0;
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

// -- FUN_7100022bf0 ----------------------------------------------------------
// Get alignment requirement for a type-flag bitmask value
// 7100022bf0
u64 FUN_7100022bf0(u64 param_1)
{
    s32 v = (s32)param_1;
    if (v < 0x4000) {
        if (v < 0x80) {
            switch (v) {
            case 1:
            case 2:
                return 1;
            case 4:
            case 8:
                return 4;
            case 0x10:
            case 0x20:
            case 0x40:
                return param_1;
            }
        } else if (v < 0x400) {
            if (v == 0x80 || v == 0x100) return 0x80;
            if (v == 0x200) return param_1 & 0xffffffff;
        } else if (v < 0x1000) {
            if (v == 0x400) return param_1;
            if (v == 0x800) return param_1 & 0xffffffff;
        } else {
            if (v == 0x1000 || v == 0x2000) return 0x1000;
        }
    } else if (v < 0x200000) {
        if (v < 0x20000) {
            if (v == 0x4000 || v == 0x8000) return 0x4000;
            if (v == 0x10000) return 0x10000;
        } else if (v < 0x80000) {
            if (v == 0x20000) return 0x10000;
            if (v == 0x40000) return param_1 & 0xffffffff;
        } else {
            if (v == 0x80000)  return 0x80000;
            if (v == 0x100000) return 0x100000;
        }
    } else if (v < 0x1000000) {
        if (v == 0x200000) return param_1;
        if (v == 0x400000) return param_1;
        if (v == 0x800000) return 0x80000;
    } else if (v < 0x4000000) {
        if (v == 0x1000000) return 0x100000;
        if (v == 0x2000000) return param_1 & 0xffffffff;
    } else {
        if (v == 0x4000000 || v == 0x8000000) return 0x4000000;
    }
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

// -- FUN_7100031140 ----------------------------------------------------------
// SetDefault: write fixed constants to struct fields
// 7100031140
void FUN_7100031140(u32* param_1)
{
    *param_1 = 0x20202;
    *(u64*)(param_1 + 1) = 0xc47a0000002a0100ULL;
    *(u64*)(param_1 + 3) = 0x447a0000ULL;
}

// -- FUN_71000311e0 ----------------------------------------------------------
// SetDefault: initialize byte fields of a struct
// 71000311e0
void FUN_71000311e0(u8* param_1)
{
    param_1[1] = 1;
    param_1[2] = 0;
    param_1[3] = 0;
    param_1[4] = 1;
    param_1[0] = param_1[0] & 0xfe;
    param_1[5] = 0;
    param_1[6] = 0;
    param_1[7] = 0xf;
}

// -- FUN_7100031210 ----------------------------------------------------------
// SetDefault: init struct with float-pattern constants
// 7100031210
void FUN_7100031210(u16* param_1)
{
    *(u64*)(param_1 + 6) = 0x3f80000000000000ULL;
    param_1[1] = param_1[1] & 0xfff0;
    *(u64*)(param_1 + 2) = 0;
    *(u64*)(param_1 + 0xc) = 0;
    *param_1 = 0x500;
}

// -- FUN_7100031250 ----------------------------------------------------------
// SetDefault: init struct with flag constants
// 7100031250
void FUN_7100031250(u16* param_1)
{
    *param_1 = 0xff01;
    *(u8*)(param_1 + 1) = 0xff;
    *(u32*)(param_1 + 4) = 0x7000000;
    *(u8*)(param_1 + 6) = 0;
    param_1[2] = param_1[2] & 0xfff0;
    *(u32*)(param_1 + 0xc) = 0x7000000;
    *(u8*)(param_1 + 0xe) = 0;
}

// -- FUN_7100031330 ----------------------------------------------------------
// SetDefault: init struct with mixed constants and pointer
// 7100031330
void FUN_7100031330(u8* param_1)
{
    param_1[1] = 2;
    *(u64*)(param_1 + 2) = 0x1000100000000ULL;
    *(u8**)(param_1 + 0x14) = (u8*)0x100000001ULL;
    *(u64*)(param_1 + 0xc) = 0;
    *(u64*)(param_1 + 0x1c) = 1;
}

// -- FUN_7100031360 ----------------------------------------------------------
// SetDefault: init struct with byte/word constants
// 7100031360
void FUN_7100031360(u16* param_1)
{
    *param_1 = 1;
    *(u64*)(param_1 + 2) = 0x504030200000000ULL;
    *(u32*)(param_1 + 8) = 0x10000;
    *(u64*)(param_1 + 0x10) = 0x100000000ULL;
    *(u64*)(param_1 + 0x18) = 0;
}

// -- FUN_7100031390 ----------------------------------------------------------
// SetDefault: init small struct
// 7100031390
void FUN_7100031390(u8* param_1)
{
    *param_1 = 1;
    *(u64*)(param_1 + 4) = 0;
    *(u16*)(param_1 + 2) = 0;
    *(u32*)(param_1 + 0xc) = 1;
    *(u64*)(param_1 + 0x18) = 0;
}

// -- FUN_71000313b0 ----------------------------------------------------------
// SetDefault: init small struct
// 71000313b0
void FUN_71000313b0(u8* param_1)
{
    *param_1 = 1;
    *(u16*)(param_1 + 2) = 0;
    *(u64*)(param_1 + 8) = 0x100000000ULL;
    *(u64*)(param_1 + 0x18) = 0;
}
