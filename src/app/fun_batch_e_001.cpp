#include "types.h"

// Batch decompiled via Ghidra MCP — pool-e, batch 001
// Range: 0x7100000000 — 0x7100FFFFFF

// ---- External declarations --------------------------------------------------

extern "C" {
    s32  __cxa_guard_acquire(s64 *);
    void __cxa_guard_release(s64 *);
    void *malloc(u64);
    void *memset(void *, s32, u64);
    s32  memcmp(const void *, const void *, u64);
}

// Called functions
extern "C" void FUN_71000052d0(void *, s32, void *, void *, void *);
extern "C" s64  FUN_7100039590(u64);
extern "C" s64  FUN_71000399e0(u64);

// Forward declaration (defined later in this file)
u8 *FUN_7100041570(void);

// Misc PTR labels/data
extern void *PTR_LAB_71052a21e0;
extern void *PTR_DAT_71052a21e8;
extern u8   LAB_7100005b00;

// Guard pointer variables (s64*)
extern s64 *PTR_DAT_71052a3380;
extern s64 *PTR_DAT_71052a33d0;
extern s64 *PTR_DAT_71052a33e0;
extern s64 *PTR_DAT_71052a33f8;
extern s64 *PTR_DAT_71052a3418;
extern s64 *PTR_DAT_71052a3428;
extern s64 *PTR_DAT_71052a3438;
extern s64 *PTR_DAT_71052a3450;
extern s64 *PTR_DAT_71052a3460;
extern s64 *PTR_DAT_71052a3470;
extern s64 *PTR_DAT_71052a34d0;
extern s64 *PTR_DAT_71052a34e0;
extern s64 *PTR_DAT_71052a34f0;
extern s64 *PTR_DAT_71052a34a8;
extern s64 *PTR_DAT_71052a34b8;
extern s64 *PTR_DAT_71052a3498;
extern s64 *PTR_DAT_71052a3520;
extern s64 *PTR_DAT_71052a3548;
extern s64 *PTR_DAT_71052a3558;
extern s64 *PTR_DAT_71052a3568;
extern s64 *PTR_DAT_71052a3588;

// Data pointer variables (u8*)
extern u8 *PTR_DAT_71052a3388;
extern u8 *PTR_DAT_71052a33d8;
extern u8 *PTR_DAT_71052a33e8;
extern u8 *PTR_DAT_71052a3400;
extern u8 *PTR_DAT_71052a3420;
extern u8 *PTR_DAT_71052a3430;
extern u8 *PTR_DAT_71052a3440;
extern u8 *PTR_DAT_71052a3458;
extern u8 *PTR_DAT_71052a3468;
extern u8 *PTR_DAT_71052a3478;
extern u8 *PTR_DAT_71052a34d8;
extern u8 *PTR_DAT_71052a34e8;
extern u8 *PTR_DAT_71052a34f8;
extern u8 *PTR_DAT_71052a34b0;
extern u8 *PTR_DAT_71052a34c0;
extern u8 *PTR_DAT_71052a34a0;
extern u8 *PTR_DAT_71052a3528;
extern u8 *PTR_DAT_71052a3550;
extern u8 *PTR_DAT_71052a3560;
extern u8 *PTR_DAT_71052a3570;
extern u8 *PTR_DAT_71052a3590;

// ---- Functions --------------------------------------------------------------

// 0x7100006180
void FUN_7100006180(u64 param_1)
{
  FUN_71000052d0((void *)param_1, 7, PTR_LAB_71052a21e0, PTR_DAT_71052a21e8, &LAB_7100005b00);
  return;
}

// 0x710003a790
s64 FUN_710003a790(s64 param_1)
{
  s64 lVar1;
  s64 lVar2;

  lVar1 = FUN_7100039590(*(u64 *)(param_1 + 8));
  lVar2 = FUN_71000399e0(*(u64 *)(param_1 + 0x20));
  return lVar2 + lVar1;
}

// 0x710003b460
bool FUN_710003b460(s64 param_1, float *param_2)
{
  if (*(s64 *)(param_1 + 0x68) == 0) {
    return false;
  }
  if (*param_2 < *(float *)(param_1 + 0x70)) {
    return false;
  }
  if (*(float *)(param_1 + 0x78) < *param_2) {
    return false;
  }
  if (param_2[1] < *(float *)(param_1 + 0x74)) {
    return false;
  }
  return param_2[1] <= *(float *)(param_1 + 0x7c);
}

// 0x710003cf90 — defined in fun_medium_012.cpp (duplicate removed)
// 0x710003d160 — defined in fun_medium_012.cpp (duplicate removed)

// 0x710003d480
u8 *FUN_710003d480(void)
{
  s32 iVar1;

  if (((*PTR_DAT_71052a33f8 & 1) == 0) &&
      (iVar1 = __cxa_guard_acquire(PTR_DAT_71052a33f8), iVar1 != 0)) {
    if (((*PTR_DAT_71052a3380 & 1) == 0) &&
        (iVar1 = __cxa_guard_acquire(PTR_DAT_71052a3380), iVar1 != 0)) {
      *(u64 *)PTR_DAT_71052a3388 = 0;
      __cxa_guard_release(PTR_DAT_71052a3380);
    }
    *(u8 **)PTR_DAT_71052a3400 = PTR_DAT_71052a3388;
    __cxa_guard_release(PTR_DAT_71052a33f8);
    return PTR_DAT_71052a3400;
  }
  return PTR_DAT_71052a3400;
}

// 0x710003d650
u8 *FUN_710003d650(void)
{
  s32 iVar1;

  if (((*PTR_DAT_71052a3418 & 1) == 0) &&
      (iVar1 = __cxa_guard_acquire(PTR_DAT_71052a3418), iVar1 != 0)) {
    if (((*PTR_DAT_71052a3380 & 1) == 0) &&
        (iVar1 = __cxa_guard_acquire(PTR_DAT_71052a3380), iVar1 != 0)) {
      *(u64 *)PTR_DAT_71052a3388 = 0;
      __cxa_guard_release(PTR_DAT_71052a3380);
    }
    *(u8 **)PTR_DAT_71052a3420 = PTR_DAT_71052a3388;
    __cxa_guard_release(PTR_DAT_71052a3418);
    return PTR_DAT_71052a3420;
  }
  return PTR_DAT_71052a3420;
}

// 0x710003d730
u8 *FUN_710003d730(void)
{
  s32 iVar1;

  if (((*PTR_DAT_71052a3428 & 1) == 0) &&
      (iVar1 = __cxa_guard_acquire(PTR_DAT_71052a3428), iVar1 != 0)) {
    if (((*PTR_DAT_71052a3380 & 1) == 0) &&
        (iVar1 = __cxa_guard_acquire(PTR_DAT_71052a3380), iVar1 != 0)) {
      *(u64 *)PTR_DAT_71052a3388 = 0;
      __cxa_guard_release(PTR_DAT_71052a3380);
    }
    *(u8 **)PTR_DAT_71052a3430 = PTR_DAT_71052a3388;
    __cxa_guard_release(PTR_DAT_71052a3428);
    return PTR_DAT_71052a3430;
  }
  return PTR_DAT_71052a3430;
}

// 0x710003d9c0
u8 *FUN_710003d9c0(void)
{
  s32 iVar1;

  if (((*PTR_DAT_71052a3438 & 1) == 0) &&
      (iVar1 = __cxa_guard_acquire(PTR_DAT_71052a3438), iVar1 != 0)) {
    if (((*PTR_DAT_71052a3380 & 1) == 0) &&
        (iVar1 = __cxa_guard_acquire(PTR_DAT_71052a3380), iVar1 != 0)) {
      *(u64 *)PTR_DAT_71052a3388 = 0;
      __cxa_guard_release(PTR_DAT_71052a3380);
    }
    *(u8 **)PTR_DAT_71052a3440 = PTR_DAT_71052a3388;
    __cxa_guard_release(PTR_DAT_71052a3438);
    return PTR_DAT_71052a3440;
  }
  return PTR_DAT_71052a3440;
}

// 0x710003dce0
u8 *FUN_710003dce0(void)
{
  s32 iVar1;

  if (((*PTR_DAT_71052a3450 & 1) == 0) &&
      (iVar1 = __cxa_guard_acquire(PTR_DAT_71052a3450), iVar1 != 0)) {
    if (((*PTR_DAT_71052a33f8 & 1) == 0) &&
        (iVar1 = __cxa_guard_acquire(PTR_DAT_71052a33f8), iVar1 != 0)) {
      if (((*PTR_DAT_71052a3380 & 1) == 0) &&
          (iVar1 = __cxa_guard_acquire(PTR_DAT_71052a3380), iVar1 != 0)) {
        *(u64 *)PTR_DAT_71052a3388 = 0;
        __cxa_guard_release(PTR_DAT_71052a3380);
      }
      *(u8 **)PTR_DAT_71052a3400 = PTR_DAT_71052a3388;
      __cxa_guard_release(PTR_DAT_71052a33f8);
    }
    *(u8 **)PTR_DAT_71052a3458 = PTR_DAT_71052a3400;
    __cxa_guard_release(PTR_DAT_71052a3450);
    return PTR_DAT_71052a3458;
  }
  return PTR_DAT_71052a3458;
}

// 0x710003df20
u8 *FUN_710003df20(void)
{
  s32 iVar1;

  if (((*PTR_DAT_71052a3460 & 1) == 0) &&
      (iVar1 = __cxa_guard_acquire(PTR_DAT_71052a3460), iVar1 != 0)) {
    if (((*PTR_DAT_71052a3380 & 1) == 0) &&
        (iVar1 = __cxa_guard_acquire(PTR_DAT_71052a3380), iVar1 != 0)) {
      *(u64 *)PTR_DAT_71052a3388 = 0;
      __cxa_guard_release(PTR_DAT_71052a3380);
    }
    *(u8 **)PTR_DAT_71052a3468 = PTR_DAT_71052a3388;
    __cxa_guard_release(PTR_DAT_71052a3460);
    return PTR_DAT_71052a3468;
  }
  return PTR_DAT_71052a3468;
}

// 0x710003e120
u8 *FUN_710003e120(void)
{
  s32 iVar1;

  if (((*PTR_DAT_71052a3470 & 1) == 0) &&
      (iVar1 = __cxa_guard_acquire(PTR_DAT_71052a3470), iVar1 != 0)) {
    if (((*PTR_DAT_71052a33d0 & 1) == 0) &&
        (iVar1 = __cxa_guard_acquire(PTR_DAT_71052a33d0), iVar1 != 0)) {
      if (((*PTR_DAT_71052a3380 & 1) == 0) &&
          (iVar1 = __cxa_guard_acquire(PTR_DAT_71052a3380), iVar1 != 0)) {
        *(u64 *)PTR_DAT_71052a3388 = 0;
        __cxa_guard_release(PTR_DAT_71052a3380);
      }
      *(u8 **)PTR_DAT_71052a33d8 = PTR_DAT_71052a3388;
      __cxa_guard_release(PTR_DAT_71052a33d0);
    }
    *(u8 **)PTR_DAT_71052a3478 = PTR_DAT_71052a33d8;
    __cxa_guard_release(PTR_DAT_71052a3470);
    return PTR_DAT_71052a3478;
  }
  return PTR_DAT_71052a3478;
}

// 0x7100041420
u8 *FUN_7100041420(void)
{
  s32 iVar1;
  u8 *uVar2;

  if (((*PTR_DAT_71052a34d0 & 1) == 0) &&
      (iVar1 = __cxa_guard_acquire(PTR_DAT_71052a34d0), iVar1 != 0)) {
    uVar2 = FUN_7100041570();
    *(u8 **)PTR_DAT_71052a34d8 = uVar2;
    __cxa_guard_release(PTR_DAT_71052a34d0);
    return PTR_DAT_71052a34d8;
  }
  return PTR_DAT_71052a34d8;
}

// 0x71000414c0
u8 *FUN_71000414c0(void)
{
  s32 iVar1;
  u8 *uVar2;

  if (((*PTR_DAT_71052a34e0 & 1) == 0) &&
      (iVar1 = __cxa_guard_acquire(PTR_DAT_71052a34e0), iVar1 != 0)) {
    uVar2 = FUN_7100041570();
    *(u8 **)PTR_DAT_71052a34e8 = uVar2;
    __cxa_guard_release(PTR_DAT_71052a34e0);
    return PTR_DAT_71052a34e8;
  }
  return PTR_DAT_71052a34e8;
}

// 0x7100041570
u8 *FUN_7100041570(void)
{
  s32 iVar1;

  if (((*PTR_DAT_71052a34f0 & 1) == 0) &&
      (iVar1 = __cxa_guard_acquire(PTR_DAT_71052a34f0), iVar1 != 0)) {
    if (((*PTR_DAT_71052a34a8 & 1) == 0) &&
        (iVar1 = __cxa_guard_acquire(PTR_DAT_71052a34a8), iVar1 != 0)) {
      if (((*PTR_DAT_71052a34b8 & 1) == 0) &&
          (iVar1 = __cxa_guard_acquire(PTR_DAT_71052a34b8), iVar1 != 0)) {
        *(u64 *)PTR_DAT_71052a34c0 = 0;
        __cxa_guard_release(PTR_DAT_71052a34b8);
      }
      *(u8 **)PTR_DAT_71052a34b0 = PTR_DAT_71052a34c0;
      __cxa_guard_release(PTR_DAT_71052a34a8);
    }
    *(u8 **)PTR_DAT_71052a34f8 = PTR_DAT_71052a34b0;
    __cxa_guard_release(PTR_DAT_71052a34f0);
    return PTR_DAT_71052a34f8;
  }
  return PTR_DAT_71052a34f8;
}

// 0x7100043260
u8 *FUN_7100043260(void)
{
  s32 iVar1;

  if (((*PTR_DAT_71052a3520 & 1) == 0) &&
      (iVar1 = __cxa_guard_acquire(PTR_DAT_71052a3520), iVar1 != 0)) {
    if (((*PTR_DAT_71052a3498 & 1) == 0) &&
        (iVar1 = __cxa_guard_acquire(PTR_DAT_71052a3498), iVar1 != 0)) {
      *(u64 *)PTR_DAT_71052a34a0 = 0;
      __cxa_guard_release(PTR_DAT_71052a3498);
    }
    *(u8 **)PTR_DAT_71052a3528 = PTR_DAT_71052a34a0;
    __cxa_guard_release(PTR_DAT_71052a3520);
    return PTR_DAT_71052a3528;
  }
  return PTR_DAT_71052a3528;
}

// 0x7100044060
u8 *FUN_7100044060(void)
{
  s32 iVar1;

  if (((*PTR_DAT_71052a3548 & 1) == 0) &&
      (iVar1 = __cxa_guard_acquire(PTR_DAT_71052a3548), iVar1 != 0)) {
    if (((*PTR_DAT_71052a3498 & 1) == 0) &&
        (iVar1 = __cxa_guard_acquire(PTR_DAT_71052a3498), iVar1 != 0)) {
      *(u64 *)PTR_DAT_71052a34a0 = 0;
      __cxa_guard_release(PTR_DAT_71052a3498);
    }
    *(u8 **)PTR_DAT_71052a3550 = PTR_DAT_71052a34a0;
    __cxa_guard_release(PTR_DAT_71052a3548);
    return PTR_DAT_71052a3550;
  }
  return PTR_DAT_71052a3550;
}

// 0x7100044110
u8 *FUN_7100044110(void)
{
  s32 iVar1;

  if (((*PTR_DAT_71052a3558 & 1) == 0) &&
      (iVar1 = __cxa_guard_acquire(PTR_DAT_71052a3558), iVar1 != 0)) {
    if (((*PTR_DAT_71052a3568 & 1) == 0) &&
        (iVar1 = __cxa_guard_acquire(PTR_DAT_71052a3568), iVar1 != 0)) {
      *(u64 *)PTR_DAT_71052a3570 = 0;
      __cxa_guard_release(PTR_DAT_71052a3568);
    }
    *(u8 **)PTR_DAT_71052a3560 = PTR_DAT_71052a3570;
    __cxa_guard_release(PTR_DAT_71052a3558);
    return PTR_DAT_71052a3560;
  }
  return PTR_DAT_71052a3560;
}

// 0x7100044990
u8 *FUN_7100044990(void)
{
  s32 iVar1;

  if (((*PTR_DAT_71052a3568 & 1) == 0) &&
      (iVar1 = __cxa_guard_acquire(PTR_DAT_71052a3568), iVar1 != 0)) {
    *(u64 *)PTR_DAT_71052a3570 = 0;
    __cxa_guard_release(PTR_DAT_71052a3568);
    return PTR_DAT_71052a3570;
  }
  return PTR_DAT_71052a3570;
}

// 0x7100044f10
u8 *FUN_7100044f10(void)
{
  s32 iVar1;

  if (((*PTR_DAT_71052a3588 & 1) == 0) &&
      (iVar1 = __cxa_guard_acquire(PTR_DAT_71052a3588), iVar1 != 0)) {
    *(u64 *)PTR_DAT_71052a3590 = 0;
    __cxa_guard_release(PTR_DAT_71052a3588);
    return PTR_DAT_71052a3590;
  }
  return PTR_DAT_71052a3590;
}
