#include "types.h"

// MEDIUM-tier FUN_* functions — mixed 0x7100-0x7101 range, batch d5-008
// Pool-d worker: auto-generated from Ghidra decompilation
// Includes: abort() thunks, strcmp comparator, call wrappers, in_x10 vtable wrappers,
//           vtable dispatchers, bounds-checked dispatch, deref-chain vtable dispatchers

// NOTE: FUN_7101fe09a4 and FUN_7101fe6684 carry a value in AArch64 register X10 that
// cannot be represented in standard C++. Initialized to 0 here; will not verify.

// ---- External declarations -----------------------------------------------

[[noreturn]] extern "C" void abort();
extern "C" int strcmp(const char *, const char *);

extern "C" void FUN_710337a860(u64, u64, u64);
extern "C" void FUN_7103778500(u64, s64);

// ---- abort() thunks -------------------------------------------------------

// 0x7101482cf0
[[noreturn]] void FUN_7101482cf0(void) { abort(); }

// 0x710148e970
[[noreturn]] void FUN_710148e970(void) { abort(); }

// 0x7101a0124c
[[noreturn]] void FUN_7101a0124c(void) { abort(); }

// 0x7101b3388c
[[noreturn]] void FUN_7101b3388c(void) { abort(); }

// 0x7101bfe104
[[noreturn]] void FUN_7101bfe104(void) { abort(); }

// ---- Utility wrappers ----------------------------------------------------

// 0x7101e309f8 — strcmp comparator: return 1 if (param_1+0x18) < (param_2+0x18)
u64 FUN_7101e309f8(s64 param_1, s64 param_2)
{
    s32 iVar1 = strcmp((char *)(param_1 + 0x18), (char *)(param_2 + 0x18));
    return iVar1 < 0 ? 1 : 0;
}

// 0x7101ea5158 — call FUN_710337a860 with hash constant
void FUN_7101ea5158(void)
{
    FUN_710337a860(0x4dffff1fb607f69fULL, 0, 0);
}

// ---- in_x10 wrappers -----------------------------------------------------

// 0x7101fe09a4 — store in_x10 at param_2+0x10, vtable call +0x448
u64 FUN_7101fe09a4(s64 *param_1, s64 param_2)
{
    u64 in_x10 = 0;
    *(u64 *)(param_2 + 0x10) = in_x10;
    (*(void(**)(s64 *))(*param_1 + 0x448))(param_1);
    return 0;
}

// 0x7101fe6684 — store in_x10 at param_2+0x10, vtable call +0x660
u64 FUN_7101fe6684(s64 *param_1, s64 param_2)
{
    u64 in_x10 = 0;
    *(u64 *)(param_2 + 0x10) = in_x10;
    (*(void(**)(s64 *))(*param_1 + 0x660))(param_1);
    return 0;
}

// ---- Vtable dispatchers --------------------------------------------------

// 0x7100065800 — vtable call at *param_1+0x58 (no arg), then *param_1+0x20 (param_1, param_3&1)
void FUN_7100065800(s64 *param_1, u64 param_2, u32 param_3)
{
    (*(void (**)())(*param_1 + 0x58))();
    (*(void(**)(s64 *, u32))(*param_1 + 0x20))(param_1, param_3 & 1);
}

// 0x71016a5890 — deref *(param_1+8)[0](), then *(param_1+0x70)[0](param_1+0x70, param_2)
void FUN_71016a5890(s64 param_1, u64 param_2)
{
    (*(void (**)())(*(s64 *)(param_1 + 8)))();
    (*(void(**)(s64 *, u64))(*(s64 *)(param_1 + 0x70)))((s64 *)(param_1 + 0x70), param_2);
}

// ---- Bounds-checked dispatch ---------------------------------------------

// 0x7101b79d30 — guard param_3<8, param_4<0x15, then dispatch into 2D array stride 0xd90/0x10
void FUN_7101b79d30(u64 param_1, s64 param_2, u32 param_3, u32 param_4)
{
    if ((param_3 < 8) && (param_4 < 0x15)) {
        FUN_7103778500(param_1, param_2 + (s64)(s32)param_3 * 0xd90 + (s64)(s32)param_4 * 0x10 + 0x818);
        return;
    }
    abort();
}

// ---- Deref-chain vtable dispatchers ---------------------------------------

// 0x7101f956d0 — triple deref to module ptr, vtable +0xc0 with hash 0xcb22cf505
u64 FUN_7101f956d0(s64 param_1)
{
    s64 *plVar1 = *(s64 **)(*(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0) + 0x190);
    (*(void(**)(s64 *, s64, u64))(*plVar1 + 0xc0))(plVar1, param_1, 0xcb22cf505ULL);
    return 1;
}

// 0x7101f95710 — same pattern, hash 0x143e92c88b
u64 FUN_7101f95710(s64 param_1)
{
    s64 *plVar1 = *(s64 **)(*(s64 *)(*(s64 *)(param_1 - 8) + 0x1a0) + 0x190);
    (*(void(**)(s64 *, s64, u64))(*plVar1 + 0xc0))(plVar1, param_1, 0x143e92c88bULL);
    return 1;
}
