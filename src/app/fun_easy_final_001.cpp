#include "types.h"

// EASY-tier batch 001 — pool-a worker

// External globals
extern u32 DAT_710446e378[];
extern u32 DAT_710446f000[];
extern u64 PTR_DAT_71052a12f8;

// 0x71000afc80
u64 FUN_71000afc80(s64 param_1, u32 param_2)
{
    return *(u64 *)(param_1 + (u64)param_2 * 8 + 0x50);
}

// 0x71000afca0
s64 FUN_71000afca0(s64 param_1, u32 param_2)
{
    return param_1 + (u64)param_2 * 0x10 + 0x20;
}

// 0x71000b9f30
void FUN_71000b9f30(u64 *param_1)
{
    *param_1 = 0xffffffff;
    *(u8 *)(param_1 + 1) = 0;
    *(u32 *)((s64)param_1 + 0xc) = 0xffffffff;
}

// 0x71000bb970
u64 FUN_71000bb970(u64 *param_1)
{
    u64 uVar1;
    uVar1 = (*param_1 & 0xff00ff00ff00ff00ULL) >> 8 | (*param_1 & 0x00ff00ff00ff00ffULL) << 8;
    uVar1 = (uVar1 & 0xffff0000ffff0000ULL) >> 0x10 | (uVar1 & 0x0000ffff0000ffffULL) << 0x10;
    return uVar1 >> 0x20 | uVar1 << 0x20;
}

// 0x71000bc920
void FUN_71000bc920(u64 *param_1)
{
    *param_1 = 0;
    *(u32 *)(param_1 + 1) = 0;
}

// 0x71000be900
void FUN_71000be900(s64 param_1, u64 *param_2)
{
    u64 uVar1 = *param_2;
    *(u32 *)(param_1 + 0xc) = *(u32 *)(param_2 + 1);
    *(u64 *)(param_1 + 4) = uVar1;
}

// 0x71000c7410
bool FUN_71000c7410(s64 param_1)
{
    return *(char *)(param_1 + 0x20) == '\x03';
}

// 0x71000c87f0
s64 FUN_71000c87f0(s64 param_1, u32 param_2)
{
    return param_1 + (u64)param_2 * 0x14 + 0x5c0;
}

// 0x7100031080
void FUN_7100031080(u8 *param_1)
{
    *param_1 = 0;
    *(u16 *)(param_1 + 2) = 7;
}

// 0x7100031090
void FUN_7100031090(u8 *param_1)
{
    *param_1 = 0;
    *(u32 *)(param_1 + 4) = 0;
}

// 0x71000310b0
void FUN_71000310b0(u16 *param_1)
{
    *param_1 = 7;
}

// 0x71000312e0
void FUN_71000312e0(u32 *param_1)
{
    *param_1 = 0;
    *(u64 *)(param_1 + 2) = 0;
    *(u64 *)(param_1 + 4) = 0;
}

// 0x71000312f0
void FUN_71000312f0(u64 *param_1)
{
    *param_1 = 0;
    param_1[1] = 0;
    param_1[2] = 0x3f80000000000000ULL;
}

// 0x71000319e0
void FUN_71000319e0(s64 param_1)
{
    if ((*(u8 *)(param_1 + 1) >> 1 & 1) == 0) {
        return;
    }
    ((void (*)(u64))(*(u64 *)PTR_DAT_71052a12f8))(*(u64 *)(param_1 + 8));
}

// 0x71000338a0
s32 FUN_71000338a0(s64 param_1, s32 *param_2)
{
    s32 iVar1;
    s32 iVar2;
    if (*(char *)(param_1 + 1) != '\0') {
        return *param_2;
    }
    iVar2 = *param_2 - *(s32 *)(param_1 + 0x10);
    iVar1 = iVar2 + 0xf;
    if (-1 < iVar2) {
        iVar1 = iVar2;
    }
    return iVar1 >> 4;
}

// 0x71000373b0
u32 FUN_71000373b0(u64 param_1)
{
    return *(u32 *)((s64)&DAT_710446e378 + (s64)(param_1 & 0xffffffff) * 4);
}

// 0x71000373c0
u32 FUN_71000373c0(u64 param_1)
{
    return DAT_710446f000[param_1 & 0xffffffff];
}

// 0x71000373d0
u32 FUN_71000373d0(u64 param_1)
{
    return DAT_710446f000[param_1 & 0xffffffff];
}

// 0x710002b7f0
const char *FUN_710002b7f0(void)
{
    return "1.2.11.f-NINTENDO-SDK-v1";
}

// 0x710008a240
void FUN_710008a240(s64 param_1)
{
    *(u8 *)(param_1 + 9) = 1;
}

// 0x7100112a00
void FUN_7100112a00(s64 param_1, u8 param_2)
{
    *(u8 *)(param_1 + 0x16) = param_2 & 1;
}

// 0x7100113420
void FUN_7100113420(s64 param_1, u32 param_2)
{
    *(u32 *)(param_1 + 0x14) = param_2;
    *(u32 *)(param_1 + 0xd30) = *(u32 *)(param_1 + 0xd30) | 0x10;
}

// 0x7100113440
void FUN_7100113440(s64 param_1, u32 param_2)
{
    *(u32 *)(param_1 + 0x18) = param_2;
    *(u32 *)(param_1 + 0xd30) = *(u32 *)(param_1 + 0xd30) | 0x20;
}

// 0x7100113460
void FUN_7100113460(s64 param_1, u32 param_2)
{
    *(u32 *)(param_1 + 0x9cc) = param_2;
    *(u32 *)(param_1 + 0xd30) = *(u32 *)(param_1 + 0xd30) | 0x4000;
}

// 0x7100113640
void FUN_7100113640(s64 param_1, u32 param_2)
{
    *(u32 *)(param_1 + 0x9d0) = param_2;
    *(u32 *)(param_1 + 0xd30) = *(u32 *)(param_1 + 0xd30) | 0x8000;
}

// 0x7100113660
void FUN_7100113660(s64 param_1, u32 param_2)
{
    *(u32 *)(param_1 + 0x9d4) = param_2;
    *(u32 *)(param_1 + 0xd30) = *(u32 *)(param_1 + 0xd30) | 0x10000;
}

// 0x7100113680
void FUN_7100113680(s64 param_1, u32 param_2)
{
    *(u32 *)(param_1 + 0x9d8) = param_2;
    *(u32 *)(param_1 + 0xd30) = *(u32 *)(param_1 + 0xd30) | 0x20000;
}

// 0x71001136a0
void FUN_71001136a0(s64 param_1, u32 param_2)
{
    *(u32 *)(param_1 + 0x9dc) = param_2;
    *(u32 *)(param_1 + 0xd30) = *(u32 *)(param_1 + 0xd30) | 0x40000;
}

// 0x710012cf70
void FUN_710012cf70(s64 param_1, u8 param_2)
{
    *(u8 *)(param_1 + 0x1e) = param_2 & 1;
}

// 0x710012eba0
void FUN_710012eba0(s64 param_1, u32 param_2)
{
    *(u32 *)(param_1 + 0x20) = param_2;
    *(u32 *)(param_1 + 0x260) = *(u32 *)(param_1 + 0x260) | 0x10;
}

// 0x710012ebc0
void FUN_710012ebc0(s64 param_1, u32 param_2)
{
    *(u32 *)(param_1 + 0x24) = param_2;
    *(u32 *)(param_1 + 0x260) = *(u32 *)(param_1 + 0x260) | 0x20;
}

// 0x7100135690
void FUN_7100135690(s64 param_1, s64 param_2)
{
    *(u64 *)(param_1 + 8) = *(u64 *)(param_2 + 8);
}

// 0x7100135780
void FUN_7100135780(s64 param_1)
{
    *(u8 *)(*(s64 *)(param_1 + 8) + (s64)*(s32 *)(param_1 + 0x10) + -1) = 0;
}

// 0x7100140e30
bool FUN_7100140e30(s64 param_1)
{
    return (u32)(*(s32 *)(param_1 + 0x90) - 6) < 3;
}

// 0x7100154ed0
void FUN_7100154ed0(s64 param_1)
{
    *(u64 *)(param_1 + 0x14) = 0;
    *(u32 *)(param_1 + 0x1c) = 0;
    *(u64 *)(param_1 + 0x20) = 0xffffffffffffffffULL;
}

// 0x7100154ef0
void FUN_7100154ef0(s64 param_1)
{
    *(u64 *)(param_1 + 0x14) = 0;
    *(u32 *)(param_1 + 0x1c) = 0;
    *(u64 *)(param_1 + 0x20) = 0xffffffffffffffffULL;
}

// 0x7100154f90
void FUN_7100154f90(s64 param_1)
{
    *(u32 *)(param_1 + 0x18) = *(u32 *)(param_1 + 0x14);
}

// 0x710015e530
void FUN_710015e530(s64 param_1)
{
    *(u8 *)(param_1 + 8) = 0;
    *(u64 *)(param_1 + 0x50) = 0;
}

// 0x7100160420
bool FUN_7100160420(s64 param_1)
{
    return *(char *)(param_1 + 0x7a) == '\x01';
}

// 0x71001604f0
void FUN_71001604f0(s64 param_1, u8 param_2)
{
    *(u8 *)(param_1 + 0x7a) = param_2 & 1;
}

// 0x7100160500
void FUN_7100160500(s64 param_1, u8 param_2)
{
    *(u8 *)(param_1 + 0x7b) = param_2 & 1;
}

// 0x71001645a0
void FUN_71001645a0(s64 param_1)
{
    if (*(char *)(param_1 + 0x18) != '\0') {
        *(u8 *)(param_1 + 0x18) = 0;
    }
}

// 0x710017f0f0
void FUN_710017f0f0(s64 param_1, u64 param_2, u64 param_3)
{
    *(u64 *)(param_1 + 0x520) = param_2;
    *(u64 *)(param_1 + 0x528) = param_3;
}

// 0x710017f1c0
void FUN_710017f1c0(s64 param_1, u8 param_2)
{
    *(u8 *)(param_1 + 0x1735) = param_2 & 1;
}

// 0x71001804d0
bool FUN_71001804d0(s64 param_1)
{
    return *(s32 *)(param_1 + 0x4e8) == 1;
}

// 0x7100193310
void FUN_7100193310(s64 param_1, u8 param_2)
{
    *(u8 *)(param_1 + 0xe2) = param_2 & 1;
}

// 0x7100193370
void FUN_7100193370(s64 param_1, u8 param_2)
{
    *(u8 *)(param_1 + 0x129) = param_2 & 1;
}

// 0x7100193380
void FUN_7100193380(s64 param_1, u8 param_2)
{
    *(u8 *)(param_1 + 0x128) = param_2 & 1;
}

// 0x71001a35e0
void FUN_71001a35e0(s64 param_1)
{
    *(u64 *)(param_1 + 0x78) = 0;
    *(u32 *)(param_1 + 0x80) = 0xffff00;
}

// 0x71001b04e0
void FUN_71001b04e0(u64 *param_1, u64 *param_2)
{
    *param_1 = *param_2;
}

// 0x71001b3130
void FUN_71001b3130(s64 param_1, s32 param_2)
{
    *(s32 *)(param_1 + 8) = *(s32 *)(param_1 + 8) + param_2;
}

// 0x71001bf280
void FUN_71001bf280(u32 *param_1)
{
    *param_1 = 0;
    *(u64 *)(param_1 + 2) = 0;
}

// 0x71001cbc30
s64 FUN_71001cbc30(s64 param_1)
{
    s64 lVar1 = 0;
    if (*(s64 *)(param_1 + 0x10) != *(s64 *)(param_1 + 0x18)) {
        lVar1 = *(s64 *)(param_1 + 0x10);
    }
    return lVar1;
}

// 0x71002276f0
u32 FUN_71002276f0(u32 param_1)
{
    return ((param_1 & 0xff00ff00u) >> 8 | (param_1 & 0x00ff00ffu) << 8) & 0xffff;
}
