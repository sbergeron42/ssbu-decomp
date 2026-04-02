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

// PTR_DAT used by FUN_7100041570
extern s64 *PTR_DAT_71052a34f0;
extern s64 *PTR_DAT_71052a34a8;
extern s64 *PTR_DAT_71052a34b8;
extern u8  *PTR_DAT_71052a34c0;
extern u8  *PTR_DAT_71052a34b0;
extern u8  *PTR_DAT_71052a34f8;


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

// FUN_710003cf90 — compiled in fun_medium_012.cpp











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





