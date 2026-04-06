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

// PTR_DAT used by FUN_7100041570
extern s64 *PTR_DAT_71052a34f0;
extern s64 *PTR_DAT_71052a34a8;
extern s64 *PTR_DAT_71052a34b8;
extern u8  *PTR_DAT_71052a34c0;
extern u8  *PTR_DAT_71052a34b0;
extern u8  *PTR_DAT_71052a34f8;


// 0x710003b460 — bounding box range check on a struct
// param_1 [inferred: object with enable flag + AABB bounds, ~0x80 bytes]
//   +0x68 [inferred: enable/valid flag, s64 — zero means disabled]
//   +0x70 [inferred: AABB min X, float]
//   +0x74 [inferred: AABB min Y, float]
//   +0x78 [inferred: AABB max X, float]
//   +0x7c [inferred: AABB max Y, float]
bool FUN_710003b460(s64 param_1, float *param_2)
{
  // +0x68 [inferred: enable/valid flag — if zero, range check is skipped]
  if (*(s64 *)(param_1 + 0x68) == 0) {
    return false;
  }
  // +0x70 [inferred: AABB min X bound, float]
  if (*param_2 < *(float *)(param_1 + 0x70)) {
    return false;
  }
  // +0x78 [inferred: AABB max X bound, float]
  if (*(float *)(param_1 + 0x78) < *param_2) {
    return false;
  }
  // +0x74 [inferred: AABB min Y bound, float]
  if (param_2[1] < *(float *)(param_1 + 0x74)) {
    return false;
  }
  // +0x7c [inferred: AABB max Y bound, float]
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
