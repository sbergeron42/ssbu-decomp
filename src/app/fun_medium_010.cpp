#include "types.h"

// MEDIUM-tier FUN_* functions — mixed address range, batch 11
// Pool-d worker: auto-generated from Ghidra decompilation

// ---- External declarations -----------------------------------------------

extern "C" void* memset(void*, int, u64);
extern "C" void* memcpy(void*, const void*, u64);
extern "C" [[noreturn]] void abort();

// nn::crypto
namespace nn {
namespace crypto {
    void GenerateCryptographicallyRandomBytes(void*, u64);
}
}

// External C functions
extern "C" void  FUN_7100002540(u64);
extern "C" void  FUN_710002a1f0(s64);
extern "C" void  FUN_710002bb40(s64);
extern "C" void  FUN_7100032e40(u64, u64, u32*, u64);
extern "C" void  FUN_7100039dd0(char*);
extern "C" void  FUN_7100048dd0();
extern "C" void  FUN_71000bf010(void*, s64, s64, u64);
extern "C" void  FUN_71000bae70(void*, s64);
extern "C" void  FUN_71001941b0(s64*);
extern "C" u64   FUN_71001aea80(s64);
extern "C" void  FUN_7100125af0();

// External data
extern u8   PTR_DAT_71052a3f80[];
extern u8   PTR_DAT_71052a4838[];
extern u8   PTR_DAT_71052a4f20[];
extern f32  DAT_7104470ba0;
extern f32  DAT_71044723d0;
extern u64  PTR_DAT_71052a3dc8;

// ---- Functions -----------------------------------------------------------

// 710065f908
[[noreturn]] void FUN_710065f908()
{
    abort();
}

// 710065f998
[[noreturn]] void FUN_710065f998()
{
    abort();
}

// 71002b8ce0 — dereference u32 pointer
u32 FUN_71002b8ce0(u32* param_1)
{
    return *param_1;
}

// 71002b8d10 — linear map: (float)param_1 * scale + offset
f32 FUN_71002b8d10(s32 param_1)
{
    return (f32)param_1 * DAT_7104470ba0 + DAT_71044723d0;
}

// 71001932d0 — return aea80 result, or -3/-2 for missing state
u64 FUN_71001932d0(s64 param_1)
{
    if (*(s64*)PTR_DAT_71052a3dc8 == 0)
        return (u64)-3;
    if (*(s64*)(param_1 + 0x90) != 0)
        return FUN_71001aea80(*(s64*)(param_1 + 0x90) + 0x48);
    return (u64)-2;
}

// 7100002690 — null-guarded free + zero
void FUN_7100002690(u64* param_1)
{
    if (param_1 != nullptr) {
        FUN_7100002540(*param_1);
        param_1[0] = 0;
        param_1[3] = 0;
    }
}

// 7100013480 — conditional clear with FUN_710002a1f0
void FUN_7100013480(s64* param_1)
{
    s64 lVar1 = *param_1;
    if (*(s32*)(lVar1 + 0x194) != 0) {
        FUN_710002a1f0(lVar1 + 0x198);
        *(u32*)(lVar1 + 0x194) = 0;
    }
}

// 7100032e10 — pack 4 u32s to stack, then call FUN_7100032e40
void FUN_7100032e10(u32 param_1, u32 param_2, u32 param_3, u32 param_4,
                    u64 param_5, u64 param_6, u64 param_7)
{
    u32 local_20[4];
    local_20[0] = param_1;
    local_20[1] = param_2;
    local_20[2] = param_3;
    local_20[3] = param_4;
    FUN_7100032e40(param_5, param_6, local_20, param_7);
}

// 7100044480 — conditional FUN_7100048dd0 + zero fields
void FUN_7100044480(u16* param_1)
{
    if (*(s64*)(param_1 + 4) != 0) {
        FUN_7100048dd0();
        *(u64*)(param_1 + 4) = 0;
        *param_1 = 0;
    }
}

// 710008b320 — clear 8 byte fields at +0x360 if first byte nonzero
void FUN_710008b320(char* param_1)
{
    if (*param_1 != '\0') {
        FUN_7100039dd0(param_1 + 0x370);
        param_1[0x360] = '\0';
        param_1[0x361] = '\0';
        param_1[0x362] = '\0';
        param_1[0x363] = '\0';
        param_1[0x364] = '\0';
        param_1[0x365] = '\0';
        param_1[0x366] = '\0';
        param_1[0x367] = '\0';
    }
}

// 71000b1910 — copy: *param_1 = *param_2, then memcpy 0x10 bytes
u32* FUN_71000b1910(u32* param_1, u32* param_2)
{
    *param_1 = *param_2;
    memcpy(param_1 + 1, param_2 + 1, 0x10);
    return param_1;
}

// 71000b2890 — zero 0x10 bytes at +8, then zero u16 at +0x18
void FUN_71000b2890(s64 param_1)
{
    memset((void*)(param_1 + 8), 0, 0x10);
    *(u16*)(param_1 + 0x18) = 0;
}

// 71000b28c0 — identical to FUN_71000b2890
void FUN_71000b28c0(s64 param_1)
{
    memset((void*)(param_1 + 8), 0, 0x10);
    *(u16*)(param_1 + 0x18) = 0;
}

// 71000b63d0 — generate 8 cryptographically random bytes
u64 FUN_71000b63d0()
{
    u64 local_18 = 0;
    nn::crypto::GenerateCryptographicallyRandomBytes(&local_18, 8);
    return local_18;
}

// 71000bca90 — initialize 4 fields of struct
void FUN_71000bca90(s64 param_1)
{
    FUN_710002bb40(param_1 + 0x20);
    *(u64*)(param_1 + 0x38) = 0;
    *(u32*)(param_1 + 0x40) = 0;
    *(u32*)(param_1 + 0x10) = 0;
}

// 71000befe0 — stack-alloc 16 bytes, call FUN_71000bf010
void FUN_71000befe0(s64 param_1)
{
    u8 auStack_20[16];
    FUN_71000bf010(auStack_20, param_1, param_1 + 0x28, 0x5c0);
}

// 71000c04b0 — call FUN_710002a1f0 then zero field
void FUN_71000c04b0(s64 param_1)
{
    FUN_710002a1f0(0);
    *(u32*)(param_1 + 0x80) = 0;
}

// 710012fd70 — stack-alloc 16 bytes, call FUN_71000bae70
void FUN_710012fd70(s64 param_1)
{
    u8 auStack_20[16];
    FUN_71000bae70(auStack_20, param_1 + 0x18);
}

// 7100117020 — conditional call FUN_7100125af0, then zero field
void FUN_7100117020(s64* param_1)
{
    if (*param_1 != 0)
        FUN_7100125af0();
    *param_1 = 0;
}

// 710014c900 — call FUN_71001941b0(param_1), then set vtable ptr at *param_1
__attribute__((noinline)) void FUN_710014c900(s64* param_1)
{
    FUN_71001941b0(param_1);
    *param_1 = (s64)(PTR_DAT_71052a4f20 + 0x10);
}

// 71000d39b0 — call FUN_710014c900(param_1), then overwrite vtable ptr
void FUN_71000d39b0(s64* param_1)
{
    FUN_710014c900(param_1);
    *param_1 = (s64)(PTR_DAT_71052a3f80 + 0x10);
}

// 7100117190 — call FUN_710014c900(param_1), then overwrite vtable ptr
void FUN_7100117190(s64* param_1)
{
    FUN_710014c900(param_1);
    *param_1 = (s64)(PTR_DAT_71052a4838 + 0x10);
}

// ---- Vtable dispatch patterns --------------------------------------------

// 71003cfc50 — vtable call at +0x130, return field at +8 or 0x50000000
u32 FUN_71003cfc50(s64* param_1)
{
    s64 lVar1 = (*(s64(**)(s64*))(*(s64*)param_1 + 0x130))(param_1);
    if (lVar1 != 0)
        return *(u32*)(lVar1 + 8);
    return 0x50000000;
}

// 710049d9c0 — vtable call at +0x680 with this, return byte at lVar1+0x13 != 0
bool FUN_710049d9c0(s64* param_1)
{
    s64 lVar1 = (*(s64(**)(s64*))(*(s64*)param_1 + 0x680))(param_1);
    return *(s8*)(lVar1 + 0x13) != 0;
}

// 710049e370 — vtable call at +0x680, return bit 3 of byte at +0x10
u8 FUN_710049e370(s64* param_1)
{
    s64 lVar1 = (*(s64(**)(s64*))(*(s64*)param_1 + 0x680))(param_1);
    return (*(u8*)(lVar1 + 0x10) >> 3) & 1;
}

// 7100612130 — double-deref vtable at +0x108, call with arg 0x2000002c, return ~result & 1
u32 FUN_7100612130(s64 param_1)
{
    s64* inner = *(s64**)(param_1 + 0x440);
    u32 uVar1 = (*(u32(**)(s64*, u32))(*(s64*)inner + 0x108))(inner, 0x2000002c);
    return ~uVar1 & 1;
}

// 71006c90d0 — double-deref vtable at +0x98, call with 0x10000001, return == 0x4d
bool FUN_71006c90d0(u64 /*param_1*/, s64 param_2)
{
    s64* inner = *(s64**)(param_2 + 0x50);
    s32 iVar1 = (*(s32(**)(s64*, u32))(*(s64*)inner + 0x98))(inner, 0x10000001);
    return iVar1 == 0x4d;
}
