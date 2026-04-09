#include "types.h"

// HARD-tier FUN_* functions — batch hard-d-031
// Pool-d worker: optnone wrappers from 0x71039500 cluster
// These are -O0 compiled (spill/reload, b .+4 patterns).
// Compiled with __attribute__((optnone)) to match debug codegen.

#define HIDDEN __attribute__((visibility("hidden")))

// ---- External functions ----

extern "C" void  FUN_71039506a0(u64);
extern "C" void  FUN_7103950b30(u64, u64, u64, u32, u8);
extern "C" u8    FUN_71039574a0(void*, void*, u32, u32);
extern "C" u32   FUN_7103951140(u64);
extern "C" s64   FUN_7103951260(u64, u32);
extern "C" void  FUN_71039513e0(u64);
extern "C" void  FUN_7103951430(u64);
extern "C" void  FUN_7103951520(u64);
extern "C" void  FUN_7103951c00(u64);
extern "C" void  FUN_7103951c80(u64);
extern "C" void  FUN_7103951cd0(u64);
extern "C" void  FUN_7103951d20(u64);
extern "C" void  FUN_7103951de0(u64);
extern "C" void  FUN_7103953390(u64);
extern "C" u64   FUN_71039521d0(u32);
extern "C" u32   FUN_7103953450(u64);
extern "C" void  FUN_71037c90e0(u64, u64);
extern "C" void  FUN_7103958740(u64);
extern "C" u32   FUN_7103952190(u64);
extern "C" u64   FUN_7103951e60(u64);
extern "C" u64   FUN_7103951ea0(u64, u64);
extern "C" u32   FUN_71039528f0(u64, u64);
extern "C" u8    FUN_7103950de0(u64);
extern "C" void  FUN_7103950e00(u64);
extern "C" u64   FUN_7103953330(void);
extern "C" void  FUN_7103958840(u64);
extern "C" void  FUN_71037c9130(u64, u64, u64, u64, u64);
extern "C" u8    FUN_71037c91c0(u64, u64, u8);
extern "C" u8    FUN_7103957c80(u64, u64);
extern "C" u8    FUN_71039586d0(u64);
extern "C" u64   FUN_71039586f0(u64);
extern "C" void  FUN_7103951d40(void*, s32);
extern "C" u8    FUN_7103953f00(s64);
extern "C" void  FUN_710395ae10(u64, s64);
extern "C" void  FUN_710395bd00(void*, s32);

// ---- External data ----

extern "C" u8  DAT_7106dd3f20 HIDDEN;    // [inferred: jemalloc config struct]
extern "C" u8  DAT_71043590fa HIDDEN;    // [derived: config key string in .rodata]
extern "C" u8  DAT_7106dd3f1f HIDDEN;    // [inferred: jemalloc flag, cleared on parse failure]
extern "C" u32 DAT_7106d424a4 HIDDEN;    // [inferred: max resource handle threshold]
extern "C" u8  DAT_7106d42580[] HIDDEN;  // [inferred: resource handle table base]

// ---- Simple wrapper functions (tail-calls) ----

// 0x7103950670 — wrapper: delegates to FUN_71039506a0 (48 bytes)
__attribute__((optnone)) extern "C"
void FUN_7103950670(u64 param_1) {
    FUN_71039506a0(param_1);
}

// 0x7103950ae0 — wrapper: delegates with fixed param w3=0x40 (80 bytes)
// [derived: Ghidra — passes param_3 as-is, inserts 0x40 as 4th arg, masks param_4]
__attribute__((optnone)) extern "C"
void FUN_7103950ae0(u64 param_1, u64 param_2, u64 param_3, u8 param_4) {
    FUN_7103950b30(param_1, param_2, param_3, 0x40, param_4 & 1);
}

// 0x71039513b0 — wrapper: delegates to FUN_71039513e0 (48 bytes)
__attribute__((optnone)) extern "C"
void FUN_71039513b0(u64 param_1) {
    FUN_71039513e0(param_1);
}

// 0x7103951400 — wrapper: delegates to FUN_7103951430 (48 bytes)
__attribute__((optnone)) extern "C"
void FUN_7103951400(u64 param_1) {
    FUN_7103951430(param_1);
}

// 0x71039514f0 — wrapper: delegates to FUN_7103951520 (48 bytes)
__attribute__((optnone)) extern "C"
void FUN_71039514f0(u64 param_1) {
    FUN_7103951520(param_1);
}

// 0x7103951bd0 — wrapper: delegates to FUN_7103951c00 (48 bytes)
__attribute__((optnone)) extern "C"
void FUN_7103951bd0(u64 param_1) {
    FUN_7103951c00(param_1);
}

// 0x7103951c50 — wrapper: delegates to FUN_7103951c80 (48 bytes)
__attribute__((optnone)) extern "C"
void FUN_7103951c50(u64 param_1) {
    FUN_7103951c80(param_1);
}

// 0x7103951ca0 — wrapper: delegates to FUN_7103951cd0 (48 bytes)
__attribute__((optnone)) extern "C"
void FUN_7103951ca0(u64 param_1) {
    FUN_7103951cd0(param_1);
}

// 0x7103951cf0 — wrapper: delegates to FUN_7103951d20 (48 bytes)
__attribute__((optnone)) extern "C"
void FUN_7103951cf0(u64 param_1) {
    FUN_7103951d20(param_1);
}

// 0x7103951db0 — wrapper: delegates to FUN_7103951de0 (48 bytes)
__attribute__((optnone)) extern "C"
void FUN_7103951db0(u64 param_1) {
    FUN_7103951de0(param_1);
}

// 0x7103953360 — wrapper: delegates to FUN_7103953390 (48 bytes)
__attribute__((optnone)) extern "C"
void FUN_7103953360(u64 param_1) {
    FUN_7103953390(param_1);
}

// 0x7103953420 — wrapper: delegates to FUN_71039521d0 (48 bytes)
__attribute__((optnone)) extern "C"
void FUN_7103953420(u32 param_1) {
    FUN_71039521d0(param_1);
}

// 0x7103957aa0 — wrapper: cross-module call to FUN_71037c90e0 (64 bytes)
__attribute__((optnone)) extern "C"
void FUN_7103957aa0(u64 param_1, u64 param_2) {
    FUN_71037c90e0(param_1, param_2);
}

// 0x7103957c40 — double wrapper: calls FUN_7103957aa0 (64 bytes)
__attribute__((optnone)) extern "C"
void FUN_7103957c40(u64 param_1, u64 param_2) {
    FUN_7103957aa0(param_1, param_2);
}

// 0x7103958710 — wrapper: delegates to FUN_7103958740 (48 bytes)
__attribute__((optnone)) extern "C"
void FUN_7103958710(u64 param_1) {
    FUN_7103958740(param_1);
}

// ---- Logic functions (return values, conditionals) ----

// 0x7103950a80 — parse config option, return success flag (96 bytes)
// [derived: Ghidra — calls FUN_71039574a0 to parse &DAT_71043590fa,
//  clears DAT_7106dd3f1f on failure, returns bool]
__attribute__((optnone)) extern "C"
bool FUN_7103950a80(void) {
    u8 result = FUN_71039574a0(&DAT_7106dd3f20, &DAT_71043590fa, 1, 0);
    bool success = (result & 1) != 0;
    if (!success) {
        DAT_7106dd3f1f = 0;
    }
    return success;
}

// 0x7103950e50 — check handle against max threshold (64 bytes)
// [derived: Ghidra — calls FUN_7103951140, compares result < DAT_7106d424a4]
__attribute__((optnone)) extern "C"
bool FUN_7103950e50(u64 param_1) {
    u32 val = FUN_7103951140(param_1);
    return val < DAT_7106d424a4;
}

// 0x7103951170 — lookup by key, null-coalesce to 0 (96 bytes)
// [derived: Ghidra — calls FUN_7103951260, returns result or 0 if null]
__attribute__((optnone)) extern "C"
s64 FUN_7103951170(u64 param_1, u32 param_2) {
    s64 result = FUN_7103951260(param_1, param_2);
    if (result == 0) {
        return 0;
    }
    return result;
}

// 0x7103951e00 — dispatch based on handle range (96 bytes)
// [derived: Ghidra — if param < 0x1000+1, call FUN_7103951e60; else subtract 0x1000 and call FUN_7103951ea0]
__attribute__((optnone)) extern "C"
u64 FUN_7103951e00(u64 param_1) {
    if (param_1 <= 0x1000) {
        return FUN_7103951e60(param_1);
    } else {
        return FUN_7103951ea0(param_1 - 0x1000, param_1);
    }
}

// 0x71039526e0 — dispatch by masked index into table (80 bytes)
// [derived: Ghidra — masks *param_1 & 0xFFF, indexes into DAT_7106d42580 table at stride 8,
//  calls FUN_7103951d40 with 2]
__attribute__((optnone)) extern "C"
void FUN_71039526e0(u32* param_1) {
    FUN_7103951d40(&DAT_7106d42580[(*param_1 & 0xFFF) * 8], 2);
}

// 0x7103952890 — dispatch based on handle range (96 bytes)
// [derived: Ghidra — same pattern as FUN_7103951e00 but calls FUN_7103952190/FUN_71039528f0]
__attribute__((optnone)) extern "C"
u32 FUN_7103952890(u64 param_1) {
    if (param_1 <= 0x1000) {
        return FUN_7103952190(param_1);
    } else {
        return FUN_71039528f0(param_1 - 0x1000, param_1);
    }
}

// 0x71039533e0 — wrapper with u32 return (64 bytes)
__attribute__((optnone)) extern "C"
u32 FUN_71039533e0(u64 param_1) {
    return FUN_7103953450(param_1);
}

// 0x7103953eb0 — conditional dispatch: check flag, then call (80 bytes)
// [derived: Ghidra — calls FUN_7103953f00(param_2+8), if true calls FUN_710395ae10]
__attribute__((optnone)) extern "C"
void FUN_7103953eb0(u64 param_1, s64 param_2) {
    u8 flag = FUN_7103953f00(param_2 + 8);
    if (flag & 1) {
        FUN_710395ae10(param_1, param_2);
    }
}

// 0x7103957bf0 — param reorder wrapper (80 bytes)
// [derived: Ghidra — reorders params: passes param_5 as first arg to FUN_71037c9130]
__attribute__((optnone)) extern "C"
void FUN_7103957bf0(u64 param_1, u64 param_2, u64 param_3, u64 param_4, u64 param_5) {
    FUN_71037c9130(param_5, param_1, param_2, param_3, param_4);
}

// 0x7103957cc0 — call with bool mask on input and output (96 bytes)
// [derived: Ghidra — masks param_3 & 1 before call, masks result & 1]
__attribute__((optnone)) extern "C"
u8 FUN_7103957cc0(u64 param_1, u64 param_2, u8 param_3) {
    u8 result = FUN_71037c91c0(param_1, param_2, param_3 & 1);
    return result & 1;
}

// 0x7103957d90 — call + mask result (64 bytes)
__attribute__((optnone)) extern "C"
u32 FUN_7103957d90(u64 param_1, u64 param_2) {
    u8 result = FUN_7103957c80(param_1, param_2);
    return result & 1;
}

// 0x7103958650 — check flag, branch, chain (96 bytes)
// [derived: Ghidra — checks FUN_71039586d0, if true returns 0,
//  else calls FUN_71039586f0 → FUN_7103958710]
__attribute__((optnone)) extern "C"
u64 FUN_7103958650(u64 param_1) {
    u8 flag = FUN_71039586d0(param_1);
    if (flag & 1) {
        return 0;
    }
    u64 val = FUN_71039586f0(param_1);
    FUN_7103958710(val);
    return val;
}

// 0x710395b690 — dispatch by masked index into table (80 bytes)
// [derived: Ghidra — same as FUN_71039526e0 but calls FUN_710395bd00]
__attribute__((optnone)) extern "C"
void FUN_710395b690(u32* param_1) {
    FUN_710395bd00(&DAT_7106d42580[(*param_1 & 0xFFF) * 8], 2);
}
