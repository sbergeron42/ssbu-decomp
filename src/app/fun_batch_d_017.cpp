#include "types.h"

// MEDIUM-tier FUN_* functions — 0x71037 address range, batch d-017
// Pool-d worker: auto-generated from Ghidra decompilation

// ---- External declarations -----------------------------------------------

extern "C" {
    void* malloc(long);
    void  free(void*);
}

extern void  FUN_71037aeec0(u64);
extern void  FUN_71037af2c0(u64);
extern void  FUN_71037af320(u64);
extern void  FUN_71037b0b30(u64);
extern void  FUN_71037b5780(u64, u64);

// ---- Functions ---------------------------------------------------------------

// 0x7103716afc — call function pointer param_1, return result (36 bytes)
u32 FUN_7103716afc(u32 (*param_1)()) { return param_1(); }

// 0x7103721588 — call function pointer param_1, return result (24 bytes)
u32 FUN_7103721588(u32 (*param_1)()) { return param_1(); }

// 0x71037af250 — init four sub-objects at fixed offsets (64 bytes)
void FUN_71037af250(s64 param_1)
{
    FUN_71037af2c0(param_1);
    FUN_71037af2c0(param_1 + 0x20);
    FUN_71037af320(param_1 + 0x40);
    FUN_71037af320(param_1 + 0x50);
}

// 0x71037b0080 — init three sub-objects via FUN_71037b0b30 (64 bytes)
void FUN_71037b0080(s64 param_1)
{
    FUN_71037b0b30(param_1);
    FUN_71037b0b30(param_1 + 0x24);
    FUN_71037b0b30(param_1 + 0x48);
}

// 0x71037b0420 — 2D float squared length: x*x + y*y (48 bytes)
float FUN_71037b0420(float *param_1)
{
    return *param_1 * *param_1 + param_1[1] * param_1[1];
}

// 0x71037b1ad0 — scale 2D float vector in-place by scalar (64 bytes)
void FUN_71037b1ad0(float param_1, float *param_2)
{
    *param_2 = *param_2 * param_1;
    param_2[1] = param_2[1] * param_1;
}

// 0x71037b2910 — malloc wrapper (48 bytes)
void FUN_71037b2910(s32 param_1) { malloc((long)param_1); }

// 0x71037b2940 — free wrapper (48 bytes)
void FUN_71037b2940(void *param_1) { free(param_1); }

// 0x71037b2e20 — call FUN_71037aeec0 at param_1 + 4 (48 bytes)
void FUN_71037b2e20(s64 param_1) { FUN_71037aeec0(param_1 + 4); }

// 0x71037b2e50 — vtable call through double-pointer at +0x18, three-arg dispatch (64 bytes)
void FUN_71037b2e50(u32 *param_1, u64 param_2)
{
    s64 *lVar1 = *(s64**)(param_1 + 6);
    (*(void(*)(u32, s64*, u64))(*(s64*)(*lVar1 + 0x38)))(*param_1, lVar1, param_2);
}

// 0x71037b44a0 — call FUN_71037aeec0 at +0 and +8 (48 bytes)
void FUN_71037b44a0(s64 param_1)
{
    FUN_71037aeec0(param_1);
    FUN_71037aeec0(param_1 + 8);
}

// 0x71037b5750 — wrapper: FUN_71037b5780(param_1, param_1) (48 bytes)
void FUN_71037b5750(u64 param_1) { FUN_71037b5780(param_1, param_1); }
