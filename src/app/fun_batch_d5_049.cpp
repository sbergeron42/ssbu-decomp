#include "types.h"

// MEDIUM-tier FUN_* functions — batch d5-049
// Pool-d worker: 0x71037* and 0x71038* misc functions
// FUN_71037aee70 FUN_71037b0ae0 FUN_71037b0c30 FUN_71037b0ce0 FUN_71037b12a0
// FUN_71037b1250 FUN_71037b1d20 FUN_71037b3820 FUN_71037b4a90 FUN_71037b7440
// FUN_71037bc140 FUN_71037bcc00 FUN_71037bd490 FUN_71037bf520 FUN_71037bf8c0
// FUN_71037c1600 FUN_71037c2460 FUN_71037c2630 FUN_71037c2800 FUN_71037c29d0
// FUN_71038647b0 FUN_7103815c70 FUN_71038717a0 FUN_710386ddd0 FUN_7103869bc0
// FUN_71038e0600 FUN_71038e0650 FUN_7103871190

extern "C" {
    void *memcpy(void *dst, const void *src, u64 n);
    float sinf(float x);
    float cosf(float x);
    __attribute__((noreturn)) void abort(void);
}

// ---- External declarations ----

extern void FUN_71037aeb30(float, float, void *);
extern void FUN_71037aeec0(u64);
extern void FUN_71037aeed0(float, float, void *);
extern void FUN_71037aedd0(void *, void *);
extern void FUN_71037b0c80(s64, s64);
extern void FUN_71037b0cd0(u64);
extern void FUN_71037b1bf0(u32, u64);
extern void FUN_71037b3650(s64);
extern void FUN_71037b3870(s64, u32);
extern void FUN_71037b3d50(u64, u32);
extern void FUN_71037b4ae0(u64, u32);
extern void FUN_71037b3620(u32 *);
// Forward declarations for functions defined later in this file
void FUN_71037b4a90(u64 param_1, u32 param_2);
extern void FUN_71037bc730(u64);
extern u64  FUN_71037aef60(u32, u32);
extern void FUN_710392e590(void *);
extern void FUN_71037f0c00(u64);
extern void FUN_71038711e0(int);
extern void FUN_71038e0640(int);
extern void FUN_71038e0690(int);

extern u8 *PTR_VirtualFreeHook_71052a7a70;

namespace nu {
    void VirtualFreeHook(void *p);
}

// ---- 0x71037* functions ----

// 0x71037aee70 — negate and wrap a 2D angle vector
u32 FUN_71037aee70(float *param_1) {
    u32 local_18[2];
    FUN_71037aeec0((u64)local_18);
    FUN_71037aeb30(-*param_1, -param_1[1], local_18);
    return local_18[0];
}

// 0x71037b0ae0 — rotate 2D vector 90 degrees
u32 FUN_71037b0ae0(float *param_1) {
    u32 local_18[2];
    FUN_71037aeed0(param_1[1] * 1.0f, *param_1 * -1.0f, local_18);
    return local_18[0];
}

// 0x71037b0c30 — copy two sub-objects and the trailing field
void FUN_71037b0c30(s64 param_1, s64 param_2) {
    FUN_71037b0c80(param_1, param_2);
    *(u64 *)(param_1 + 0x10) = *(u64 *)(param_2 + 0x10);
}

// 0x71037b0ce0 — wrapper
void FUN_71037b0ce0(u64 param_1) {
    FUN_71037b0cd0(param_1);
}

// 0x71037b12a0 — wrapper
void FUN_71037b12a0(u64 param_1) {
    FUN_71037b0cd0(param_1);
}

// 0x71037b1250 — copy sub-objects + 0x8c bytes
void FUN_71037b1250(s64 param_1, s64 param_2) {
    FUN_71037b0c80(param_1, param_2);
    memcpy((void *)(param_1 + 0x10), (void *)(param_2 + 0x10), 0x8c);
}

// 0x71037b1d20 — sin/cos decompose
void FUN_71037b1d20(float param_1, float *param_2) {
    *param_2 = sinf(param_1);
    param_2[1] = cosf(param_1);
}

// 0x71037b3820 — three-step op with counter decrement
void FUN_71037b3820(s64 param_1, u32 param_2) {
    FUN_71037b3870(param_1, param_2);
    *(s32 *)(param_1 + 0x28) = *(s32 *)(param_1 + 0x28) - 1;
    FUN_71037b4a90(param_1, param_2);
}

// 0x71037b4a90 — two-call wrapper
void FUN_71037b4a90(u64 param_1, u32 param_2) {
    FUN_71037b4ae0(param_1, param_2);
    FUN_71037b3d50(param_1, param_2);
}

// 0x71037b7440 — zero-init many fields
void FUN_71037b7440(u32 *param_1) {
    FUN_71037b3620(param_1 + 0xd);
    *(u64 *)(param_1 + 0x10) = 0;
    *(u64 *)(param_1 + 4)    = 0;
    *(u64 *)(param_1 + 2)    = 0;
    *(u64 *)(param_1 + 10)   = 0;
    param_1[0xc]             = 0;
    *(u64 *)(param_1 + 6)    = 0;
    *param_1                 = 0;
}

// 0x71037bc140 — return pointer offset
s64 FUN_71037bc140(s64 param_1) {
    return param_1 + 0x34;
}

// 0x71037bcc00 — wrapper
void FUN_71037bcc00(u64 param_1) {
    FUN_71037bc730(param_1);
}

// 0x71037bd490 — wrapper
void FUN_71037bd490(u64 param_1) {
    FUN_71037bc730(param_1);
}

// 0x71037bf520 — init five sub-objects at fixed offsets
void FUN_71037bf520(s64 param_1) {
    FUN_71037aeec0(param_1 + 8);
    FUN_71037aeec0(param_1 + 0x10);
    FUN_71037aeec0(param_1 + 0x18);
    FUN_71037aeec0(param_1 + 0x20);
    FUN_71037aeec0(param_1 + 0x2c);
}

// 0x71037bf8c0 — wrapper
void FUN_71037bf8c0(u64 param_1) {
    FUN_71037bc730(param_1);
}

// 0x71037c1600 — compose two calls
void FUN_71037c1600(u32 param_1, u32 param_2, u32 param_3) {
    u64 uVar1 = FUN_71037aef60(param_1, param_3);
    FUN_71037b1bf0(param_2, uVar1);
}

// 0x71037c2460 — wrapper
void FUN_71037c2460(u64 param_1) {
    FUN_71037bc730(param_1);
}

// 0x71037c2630 — wrapper
void FUN_71037c2630(u64 param_1) {
    FUN_71037bc730(param_1);
}

// 0x71037c2800 — wrapper
void FUN_71037c2800(u64 param_1) {
    FUN_71037bc730(param_1);
}

// 0x71037c29d0 — wrapper
void FUN_71037c29d0(u64 param_1) {
    FUN_71037bc730(param_1);
}

// ---- 0x71038* functions ----

// 0x71038647b0 — write "nn::GP_NULL\x0b" string literal
void FUN_71038647b0(u64 *param_1) {
    *param_1       = 0x5f5550473a3a756eULL;  // "nn::GPU_"
    *(u32 *)(param_1 + 1) = 0x4c4c41;            // "ALL"
    *(u8 *)((u8 *)param_1 + 0x81) = 0xb;
}

// 0x7103815c70 — wrapper returning 1
u64 FUN_7103815c70(s64 param_1) {
    FUN_71037f0c00(*(u64 *)(param_1 + 0x18));
    return 1;
}

// 0x7103869bc0 — recursive binary-tree free (left, right, then node)
void FUN_7103869bc0(u64 *param_1) {
    if (param_1 != (u64 *)0) {
        FUN_7103869bc0((u64 *)*param_1);
        FUN_7103869bc0((u64 *)param_1[1]);
        if (PTR_VirtualFreeHook_71052a7a70 != (u8 *)0) {
            nu::VirtualFreeHook(param_1);
        }
        FUN_710392e590(param_1);
    }
}

// 0x710386ddd0 — recursive binary-tree free (same pattern, different tree)
void FUN_710386ddd0(u64 *param_1) {
    if (param_1 != (u64 *)0) {
        FUN_710386ddd0((u64 *)*param_1);
        FUN_710386ddd0((u64 *)param_1[1]);
        if (PTR_VirtualFreeHook_71052a7a70 != (u8 *)0) {
            nu::VirtualFreeHook(param_1);
        }
        FUN_710392e590(param_1);
    }
}

// 0x71038717a0 — recursive binary-tree free (same pattern, different tree)
void FUN_71038717a0(u64 *param_1) {
    if (param_1 != (u64 *)0) {
        FUN_71038717a0((u64 *)*param_1);
        FUN_71038717a0((u64 *)param_1[1]);
        if (PTR_VirtualFreeHook_71052a7a70 != (u8 *)0) {
            nu::VirtualFreeHook(param_1);
        }
        FUN_710392e590(param_1);
    }
}

// 0x7103871190 — switch: return 0 for most, param_2 for case 3
u64 FUN_7103871190(u32 param_1, u64 param_2) {
    switch (param_1) {
    case 0: case 1: case 2: case 4:
        return 0;
    case 3:
        return param_2;
    default:
        FUN_71038711e0(0);
        abort();
    }
}

// 0x71038e0600 — switch: case 0 or 1 return param_2, else abort
u64 FUN_71038e0600(u32 param_1, u64 param_2) {
    switch (param_1) {
    case 0:
    case 1:
        return param_2;
    default:
        FUN_71038e0640(0);
        abort();
    }
}

// 0x71038e0650 — switch: case 1 returns param_2, case 0 returns 0
u64 FUN_71038e0650(u32 param_1, u64 param_2) {
    switch (param_1) {
    case 0:
        return 0;
    case 1:
        return param_2;
    default:
        FUN_71038e0690(0);
        abort();
    }
}
