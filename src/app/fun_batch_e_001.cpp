#include "types.h"

// Batch decompiled via Ghidra MCP -- pool-e, batch 001
// Range: 0x7100000000 -- 0x7100FFFFFF

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

// 0x710003cf90 -- defined in fun_medium_012.cpp (duplicate removed)
// 0x710003d160 -- defined in fun_medium_012.cpp (duplicate removed)

// 0x710003d480 -- moved to fun_medium_016.cpp (duplicate)
// 0x710003d650 -- moved to fun_medium_013.cpp (duplicate)
// 0x710003d730 -- moved to fun_medium_016.cpp (duplicate)
// 0x710003d9c0 -- moved to fun_medium_016.cpp (duplicate)
// 0x710003dce0 -- moved to fun_medium_016.cpp (duplicate)
// 0x710003df20 -- moved to fun_medium_016.cpp (duplicate)
// 0x710003e120 -- moved to fun_medium_016.cpp (duplicate)

// 0x7100041420 -- moved to fun_medium_012.cpp (duplicate)
// 0x71000414c0 -- moved to fun_medium_012.cpp (duplicate)

// 0x7100041570 -- moved to fun_medium_012.cpp (duplicate)
// 0x7100043260 -- moved to fun_medium_012.cpp (duplicate)
// 0x7100044060 -- moved to fun_medium_012.cpp (duplicate)
// 0x7100044110 -- moved to fun_medium_012.cpp (duplicate)
// 0x7100044990 -- moved to fun_medium_012.cpp (duplicate)
// 0x7100044f10 -- moved to fun_medium_012.cpp (duplicate)
