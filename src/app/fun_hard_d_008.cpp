#include "types.h"

// HARD-tier FUN_* functions — 0x7100 address range, batch hard-d-008
// Pool-d worker: tree traversal variants, PTR_DAT inits, misc helpers

#define HIDDEN __attribute__((visibility("hidden")))

// ---- External data -------------------------------------------------------

extern u8 *PTR_DAT_71052a6978 HIDDEN;

// ---- External functions --------------------------------------------------

// Tree free helpers
extern void FUN_71001b1870(u64 *);
extern void jeFree_710392e590(u64 *);

// Misc
extern void FUN_71002b84e0(u64);
extern void FUN_7100229f10(void);
extern void FUN_7100232cb0(s64 *);
extern void FUN_7100235160(s64 *);
extern void FUN_710024c570(u64, s64);
extern void FUN_7100228de0(u64, s64);
extern void FUN_71004e3920(u64 *);

// ---- Binary tree post-order traversals (FUN_71001b1870 free) --------

// 0x71002333f0
void FUN_71002333f0(u64 param_1, u64 *param_2)
{
    if (param_2 != nullptr) {
        FUN_71002333f0(param_1, (u64 *)*param_2);
        FUN_71002333f0(param_1, (u64 *)param_2[1]);
        FUN_71001b1870(param_2);
    }
}

// 0x7100246ae0
void FUN_7100246ae0(u64 param_1, u64 *param_2)
{
    if (param_2 != nullptr) {
        FUN_7100246ae0(param_1, (u64 *)*param_2);
        FUN_7100246ae0(param_1, (u64 *)param_2[1]);
        FUN_71001b1870(param_2);
    }
}

// 0x7100293800
void FUN_7100293800(u64 param_1, u64 *param_2)
{
    if (param_2 != nullptr) {
        FUN_7100293800(param_1, (u64 *)*param_2);
        FUN_7100293800(param_1, (u64 *)param_2[1]);
        FUN_71001b1870(param_2);
    }
}

// ---- Binary tree post-order traversals (jeFree_710392e590 free) --------

// 0x71004b06a0
void FUN_71004b06a0(u64 *param_1)
{
    if (param_1 != nullptr) {
        FUN_71004b06a0((u64 *)*param_1);
        FUN_71004b06a0((u64 *)param_1[1]);
        jeFree_710392e590(param_1);
    }
}

// 0x71004e38a0
void FUN_71004e38a0(u64 *param_1)
{
    if (param_1 != nullptr) {
        FUN_71004e38a0((u64 *)*param_1);
        FUN_71004e38a0((u64 *)param_1[1]);
        jeFree_710392e590(param_1);
    }
}

// 0x71004e38e0 — post-order + free extra field at [7] before freeing node
void FUN_71004e38e0(u64 *param_1)
{
    if (param_1 != nullptr) {
        FUN_71004e38e0((u64 *)*param_1);
        FUN_71004e38e0((u64 *)param_1[1]);
        FUN_71004e3920((u64 *)param_1[7]);
        jeFree_710392e590(param_1);
    }
}

// 0x71004e3920
void FUN_71004e3920(u64 *param_1)
{
    if (param_1 != nullptr) {
        FUN_71004e3920((u64 *)*param_1);
        FUN_71004e3920((u64 *)param_1[1]);
        jeFree_710392e590(param_1);
    }
}

// 0x71004f98d0
void FUN_71004f98d0(u64 *param_1)
{
    if (param_1 != nullptr) {
        FUN_71004f98d0((u64 *)*param_1);
        FUN_71004f98d0((u64 *)param_1[1]);
        jeFree_710392e590(param_1);
    }
}

// 0x71004f9910
void FUN_71004f9910(u64 *param_1)
{
    if (param_1 != nullptr) {
        FUN_71004f9910((u64 *)*param_1);
        FUN_71004f9910((u64 *)param_1[1]);
        jeFree_710392e590(param_1);
    }
}

// 0x7100508c30
void FUN_7100508c30(u64 *param_1)
{
    if (param_1 != nullptr) {
        FUN_7100508c30((u64 *)*param_1);
        FUN_7100508c30((u64 *)param_1[1]);
        jeFree_710392e590(param_1);
    }
}

// 0x7100510cf0
void FUN_7100510cf0(u64 *param_1)
{
    if (param_1 != nullptr) {
        FUN_7100510cf0((u64 *)*param_1);
        FUN_7100510cf0((u64 *)param_1[1]);
        jeFree_710392e590(param_1);
    }
}

// 0x7100556950
void FUN_7100556950(u64 *param_1)
{
    if (param_1 != nullptr) {
        FUN_7100556950((u64 *)*param_1);
        FUN_7100556950((u64 *)param_1[1]);
        jeFree_710392e590(param_1);
    }
}

// 0x7100556990
void FUN_7100556990(u64 *param_1)
{
    if (param_1 != nullptr) {
        FUN_7100556990((u64 *)*param_1);
        FUN_7100556990((u64 *)param_1[1]);
        jeFree_710392e590(param_1);
    }
}

// 0x71005569d0
void FUN_71005569d0(u64 *param_1)
{
    if (param_1 != nullptr) {
        FUN_71005569d0((u64 *)*param_1);
        FUN_71005569d0((u64 *)param_1[1]);
        jeFree_710392e590(param_1);
    }
}

// 0x7100556a10
void FUN_7100556a10(u64 *param_1)
{
    if (param_1 != nullptr) {
        FUN_7100556a10((u64 *)*param_1);
        FUN_7100556a10((u64 *)param_1[1]);
        jeFree_710392e590(param_1);
    }
}

// 0x7100556a50
void FUN_7100556a50(u64 *param_1)
{
    if (param_1 != nullptr) {
        FUN_7100556a50((u64 *)*param_1);
        FUN_7100556a50((u64 *)param_1[1]);
        jeFree_710392e590(param_1);
    }
}

// 0x7100556a90
void FUN_7100556a90(u64 *param_1)
{
    if (param_1 != nullptr) {
        FUN_7100556a90((u64 *)*param_1);
        FUN_7100556a90((u64 *)param_1[1]);
        jeFree_710392e590(param_1);
    }
}

// 0x710057d630
void FUN_710057d630(u64 *param_1)
{
    if (param_1 != nullptr) {
        FUN_710057d630((u64 *)*param_1);
        FUN_710057d630((u64 *)param_1[1]);
        jeFree_710392e590(param_1);
    }
}

// ---- Other functions -------------------------------------------------------

// 0x7100242db0 — set vtable + 3 calls (64 bytes)
void FUN_7100242db0(s64 *param_1)
{
    *param_1 = (s64)(PTR_DAT_71052a6978 + 0x10);
    FUN_7100229f10();
    FUN_7100232cb0(param_1 + 4);
    FUN_7100235160(param_1);
}

// 0x710024cc30 — forward to two helpers with swapped args (64 bytes)
void FUN_710024cc30(s64 param_1, u64 param_2)
{
    FUN_710024c570(param_2, param_1);
    FUN_7100228de0(param_2, param_1 + 0x68);
}

// 0x71002b3900 — load-and-forward: deref then call (48 bytes)
void FUN_71002b3900(u64 *param_1)
{
    FUN_71002b84e0(*param_1);
}
