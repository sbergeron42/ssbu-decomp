#include "types.h"

// Virtual method dispatchers and utility functions — 0x71037d-0x71038 address range, batch d-015
//
// The vtable dispatch functions (18 total, 6 class groups × 3 sub-structures) share a pattern:
//   1. Call vtable[24] (byte offset 0xc0) on the object → returns a base data block pointer
//   2. Add a fixed offset (+0x20, +0x230, or +0x338) to return a sub-structure
//
// These are identical virtual method implementations across a class hierarchy.
// DATA xrefs show these appear in vtables at 0x71052414xx, 0x7105241fxx, 0x71052420xx, etc.
// [inferred: 6 sibling classes sharing the same data block layout — no .dynsym names available]
//
// Sub-structure offsets within the data block:
//   +0x20  → sub-structure A [unknown purpose]
//   +0x230 → sub-structure B [unknown purpose]
//   +0x338 → sub-structure C [unknown purpose]

// ---- External declarations -----------------------------------------------

extern "C" int strcmp(const char*, const char*);

extern void  FUN_710356bb20(void);
extern void  FUN_710392e590(void*);
extern void  FUN_71037d7e30(void);
extern void  FUN_71037d9830(void);

namespace nu {
    extern void VirtualFreeHook(void*);
}

// External data
extern u8 PTR_VirtualFreeHook_71052a7a70[];

// ---- Vtable dispatch: class group 1 (DATA xrefs at 0x7105241420) ----------

// 0x71037d1920 — virtual: get sub-structure A (+0x20) from data block (32 bytes)
s64 FUN_71037d1920(s64 *param_1)
{
    // *param_1 → vtable; +0xc0 → vtable[24] = get_data_block virtual method
    s64 result = (*(s64(*)())(*(s64*)(*param_1 + 0xc0)))();
    return result + 0x20;
}

// 0x71037d1940 — virtual: get sub-structure B (+0x230) from data block (32 bytes)
s64 FUN_71037d1940(s64 *param_1)
{
    s64 result = (*(s64(*)())(*(s64*)(*param_1 + 0xc0)))();
    return result + 0x230;
}

// 0x71037d1960 — virtual: get sub-structure C (+0x338) from data block (32 bytes)
s64 FUN_71037d1960(s64 *param_1)
{
    s64 result = (*(s64(*)())(*(s64*)(*param_1 + 0xc0)))();
    return result + 0x338;
}

// ---- Vtable dispatch: class group 2 (DATA xrefs at 0x7105241f90) ----------

// 0x71037d3b80 — virtual: get sub-structure A (+0x20) (32 bytes)
s64 FUN_71037d3b80(s64 *param_1)
{
    s64 result = (*(s64(*)())(*(s64*)(*param_1 + 0xc0)))();
    return result + 0x20;
}

// 0x71037d3ba0 — virtual: get sub-structure B (+0x230) (32 bytes)
s64 FUN_71037d3ba0(s64 *param_1)
{
    s64 result = (*(s64(*)())(*(s64*)(*param_1 + 0xc0)))();
    return result + 0x230;
}

// 0x71037d3bc0 — virtual: get sub-structure C (+0x338) (32 bytes)
s64 FUN_71037d3bc0(s64 *param_1)
{
    s64 result = (*(s64(*)())(*(s64*)(*param_1 + 0xc0)))();
    return result + 0x338;
}

// ---- Vtable dispatch: class group 3 ----------------------------------------

// 0x71037d5430 — virtual: get sub-structure A (+0x20) (32 bytes)
s64 FUN_71037d5430(s64 *param_1)
{
    s64 result = (*(s64(*)())(*(s64*)(*param_1 + 0xc0)))();
    return result + 0x20;
}

// 0x71037d5450 — virtual: get sub-structure B (+0x230) (32 bytes)
s64 FUN_71037d5450(s64 *param_1)
{
    s64 result = (*(s64(*)())(*(s64*)(*param_1 + 0xc0)))();
    return result + 0x230;
}

// 0x71037d5470 — virtual: get sub-structure C (+0x338) (32 bytes)
s64 FUN_71037d5470(s64 *param_1)
{
    s64 result = (*(s64(*)())(*(s64*)(*param_1 + 0xc0)))();
    return result + 0x338;
}

// ---- Vtable dispatch: class group 4 ----------------------------------------

// 0x71037d6e70 — virtual: get sub-structure A (+0x20) (32 bytes)
s64 FUN_71037d6e70(s64 *param_1)
{
    s64 result = (*(s64(*)())(*(s64*)(*param_1 + 0xc0)))();
    return result + 0x20;
}

// 0x71037d6e90 — virtual: get sub-structure B (+0x230) (32 bytes)
s64 FUN_71037d6e90(s64 *param_1)
{
    s64 result = (*(s64(*)())(*(s64*)(*param_1 + 0xc0)))();
    return result + 0x230;
}

// 0x71037d6eb0 — virtual: get sub-structure C (+0x338) (32 bytes)
s64 FUN_71037d6eb0(s64 *param_1)
{
    s64 result = (*(s64(*)())(*(s64*)(*param_1 + 0xc0)))();
    return result + 0x338;
}

// ---- Vtable dispatch: class group 5 ----------------------------------------

// 0x71037d8890 — virtual: get sub-structure A (+0x20) (32 bytes)
s64 FUN_71037d8890(s64 *param_1)
{
    s64 result = (*(s64(*)())(*(s64*)(*param_1 + 0xc0)))();
    return result + 0x20;
}

// 0x71037d88b0 — virtual: get sub-structure B (+0x230) (32 bytes)
s64 FUN_71037d88b0(s64 *param_1)
{
    s64 result = (*(s64(*)())(*(s64*)(*param_1 + 0xc0)))();
    return result + 0x230;
}

// 0x71037d88d0 — virtual: get sub-structure C (+0x338) (32 bytes)
s64 FUN_71037d88d0(s64 *param_1)
{
    s64 result = (*(s64(*)())(*(s64*)(*param_1 + 0xc0)))();
    return result + 0x338;
}

// ---- Vtable dispatch: class group 6 ----------------------------------------

// 0x71037da290 — virtual: get sub-structure A (+0x20) (32 bytes)
s64 FUN_71037da290(s64 *param_1)
{
    s64 result = (*(s64(*)())(*(s64*)(*param_1 + 0xc0)))();
    return result + 0x20;
}

// 0x71037da2b0 — virtual: get sub-structure B (+0x230) (32 bytes)
s64 FUN_71037da2b0(s64 *param_1)
{
    s64 result = (*(s64(*)())(*(s64*)(*param_1 + 0xc0)))();
    return result + 0x230;
}

// 0x71037da2d0 — virtual: get sub-structure C (+0x338) (32 bytes)
s64 FUN_71037da2d0(s64 *param_1)
{
    s64 result = (*(s64(*)())(*(s64*)(*param_1 + 0xc0)))();
    return result + 0x338;
}

// ---- Destructor/free helpers ------------------------------------------------

// 0x71037dc3b0 — destructor helper: notify + conditional VirtualFreeHook + free (64 bytes)
// [inferred: destructor pattern — FUN_71037d7e30 likely decrements refcount or unregisters]
void FUN_71037dc3b0(void *param_1)
{
    FUN_71037d7e30();
    if (*(u8 **)PTR_VirtualFreeHook_71052a7a70 != nullptr) {
        nu::VirtualFreeHook(param_1);
    }
    FUN_710392e590(param_1);  // [inferred: operator delete or heap free]
}

// 0x71037dc810 — destructor helper: same pattern, different notify (64 bytes)
// [inferred: different class destructor — FUN_71037d9830 is class-specific cleanup]
void FUN_71037dc810(void *param_1)
{
    FUN_71037d9830();
    if (*(u8 **)PTR_VirtualFreeHook_71052a7a70 != nullptr) {
        nu::VirtualFreeHook(param_1);
    }
    FUN_710392e590(param_1);
}

// ---- Miscellaneous ----------------------------------------------------------

// 0x7103835760 — type-switch copy: copy 16 bytes (two u64) for cases 0/1, abort otherwise (64 bytes)
// [inferred: copy operation for a discriminated union with at least 2 valid types]
void FUN_7103835760(u32 param_1, u64 *param_2, u64 *param_3)
{
    switch (param_1) {
    case 0:
    case 1:
        param_3[1] = param_2[1];
        *param_3 = *param_2;
        return;
    default:
        FUN_710356bb20();  // [inferred: abort/unreachable — invalid type discriminant]
    }
}

// 0x7103839270 — bounds check: abort if param_1 >= 4 (64 bytes)
// [inferred: guard for 4-element array or enum range]
void FUN_7103839270(u32 param_1)
{
    if (param_1 < 4) {
        return;
    }
    FUN_710356bb20();
}

// 0x7103841cf0 — abort wrapper (16 bytes)
u32 FUN_7103841cf0(void) { FUN_710356bb20(); }

// 0x7103841d00 — abort wrapper (16 bytes)
u32 FUN_7103841d00(void) { FUN_710356bb20(); }

// 0x71038e0bec — strcmp comparator, negated result (36 bytes)
// [inferred: comparison callback for sorted container — compares string at +0x04 of entry]
s32 FUN_71038e0bec(s64 param_1, u64 param_2, const char *param_3)
{
    // +0x04 → inline null-terminated string [inferred: key field in sorted entry]
    return -strcmp((const char*)(param_1 + 4), param_3);
}

// 0x71038e150c — strcmp comparator, negated result (36 bytes)
// [inferred: same pattern as FUN_71038e0bec — different caller/registration context]
s32 FUN_71038e150c(s64 param_1, u64 param_2, const char *param_3)
{
    return -strcmp((const char*)(param_1 + 4), param_3);
}
