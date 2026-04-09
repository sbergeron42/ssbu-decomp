#include "types.h"

// HARD-tier FUN_* functions — batch hard-d-033
// Pool-d worker: more optnone wrappers from 0x710395 cluster (resource/jemalloc)
// These are -O0 compiled (spill/reload, b .+4 patterns).
// Compiled with __attribute__((optnone)) to match debug codegen.

#define HIDDEN __attribute__((visibility("hidden")))

// ---- External functions ----

extern "C" void  FUN_710395bb10(u64);
extern "C" void  FUN_710395bb60(u64);
extern "C" void  FUN_710395bc50(u64);
extern "C" void  FUN_710395c470(u64);
extern "C" void  FUN_710395c840(u64);
extern "C" u64   FUN_710395d270(u64);
extern "C" void  FUN_710395d2c0(u64);
extern "C" void  FUN_710395d310(u64);
extern "C" void  FUN_710395d360(u64);
extern "C" u64   FUN_710395eb50(u64);
extern "C" u64   FUN_710395eba0(u64);
extern "C" u64   FUN_710395eee0(u64);
extern "C" void  FUN_710395ef30(u64);
extern "C" u32   FUN_7103952190(u64);
extern "C" u32   FUN_71039521d0(u32);
extern "C" void  FUN_710395d760(u64);
extern "C" u64   FUN_710395d7a0(void);
extern "C" void  FUN_710395faf0(u64, u64);
extern "C" void  FUN_710395a6a0(s32*, u64, s32, u32, u64);
extern "C" void  FUN_710395aa80(s32*);
extern "C" void  FUN_710395a4a0(s32*, const char*, ...);
extern "C" void  FUN_710395aad0(s32*);
extern "C" s64   FUN_710395b990(u64, u32);
extern "C" u8    FUN_710395b830(u64);
extern "C" u64   FUN_710395b850(u64);
extern "C" u64   FUN_710395c410(void);
extern "C" void  FUN_7103958840(u64);
extern "C" void  FUN_710395ea10(u64);
extern "C" void  FUN_710395c700(u32, u64);
extern "C" u8    FUN_710395e0e0(s64);
extern "C" void  FUN_710395ae10(u64, s64);
extern "C" void  FUN_710395ee90(u64);
extern "C" void  FUN_710395ee40(u64);
extern "C" u8    FUN_710395f440(u64);
extern "C" u64   FUN_710395f460(u64);
extern "C" u64   FUN_710395f480(u64);
extern "C" u8    FUN_7103950de0(u64);
extern "C" void  FUN_7103950e00(u64);
extern "C" u64   FUN_7103953330(void);
extern "C" u64   FUN_710395e8b0(u64, u64);

// ---- External data ----

extern "C" u64 DAT_7106dd40b0 HIDDEN;    // [inferred: resource manager context pointer]
extern "C" u32 DAT_7106dd3fec HIDDEN;    // [inferred: resource config/mode flag]
extern "C" u8  DAT_710425d0a2 HIDDEN;    // [inferred: format string in .rodata, likely "]"]

// ════════════════════════════════════════════════════════════════════
// Simple wrapper functions (48 bytes each, tail-call delegates)
// ════════════════════════════════════════════════════════════════════

// 0x710395bae0 — wrapper: delegates to FUN_710395bb10
__attribute__((optnone)) extern "C"
void FUN_710395bae0(u64 param_1) {
    FUN_710395bb10(param_1);
}

// 0x710395bb30 — wrapper: delegates to FUN_710395bb60
__attribute__((optnone)) extern "C"
void FUN_710395bb30(u64 param_1) {
    FUN_710395bb60(param_1);
}

// 0x710395bc20 — wrapper: delegates to FUN_710395bc50
__attribute__((optnone)) extern "C"
void FUN_710395bc20(u64 param_1) {
    FUN_710395bc50(param_1);
}

// 0x710395c440 — wrapper: delegates to FUN_710395c470
__attribute__((optnone)) extern "C"
void FUN_710395c440(u64 param_1) {
    FUN_710395c470(param_1);
}

// 0x710395d1e0 — wrapper: delegates to FUN_710395c840 (cross-module)
__attribute__((optnone)) extern "C"
void FUN_710395d1e0(u64 param_1) {
    FUN_710395c840(param_1);
}

// 0x710395d240 — wrapper: delegates to FUN_710395d270, returns pointer
__attribute__((optnone)) extern "C"
u64 FUN_710395d240(u64 param_1) {
    return FUN_710395d270(param_1);
}

// 0x710395d290 — wrapper: delegates to FUN_710395d2c0
__attribute__((optnone)) extern "C"
void FUN_710395d290(u64 param_1) {
    FUN_710395d2c0(param_1);
}

// 0x710395d2e0 — wrapper: delegates to FUN_710395d310
__attribute__((optnone)) extern "C"
void FUN_710395d2e0(u64 param_1) {
    FUN_710395d310(param_1);
}

// 0x710395d330 — wrapper: delegates to FUN_710395d360
__attribute__((optnone)) extern "C"
void FUN_710395d330(u64 param_1) {
    FUN_710395d360(param_1);
}

// 0x710395eb20 — wrapper: delegates to FUN_710395eb50, returns pointer
__attribute__((optnone)) extern "C"
u64 FUN_710395eb20(u64 param_1) {
    return FUN_710395eb50(param_1);
}

// 0x710395eb70 — wrapper: delegates to FUN_710395eba0, returns pointer
__attribute__((optnone)) extern "C"
u64 FUN_710395eb70(u64 param_1) {
    return FUN_710395eba0(param_1);
}

// 0x710395eeb0 — wrapper: delegates to FUN_710395eee0, returns pointer
__attribute__((optnone)) extern "C"
u64 FUN_710395eeb0(u64 param_1) {
    return FUN_710395eee0(param_1);
}

// 0x710395ef00 — wrapper: delegates to FUN_710395ef30
__attribute__((optnone)) extern "C"
void FUN_710395ef00(u64 param_1) {
    FUN_710395ef30(param_1);
}

// ════════════════════════════════════════════════════════════════════
// Two-call-and-return wrappers (64 bytes)
// ════════════════════════════════════════════════════════════════════

// 0x7103951e60 — call FUN_7103952190, then return FUN_71039521d0 result (64 bytes)
// [derived: Ghidra — sequential dispatch, passes result of first to second]
__attribute__((optnone)) extern "C"
u64 FUN_7103951e60(u64 param_1) {
    FUN_7103952190(param_1);
    return FUN_71039521d0(0);
}

// 0x710395d430 — call FUN_710395d760, then return FUN_710395d7a0 result (64 bytes)
// [derived: Ghidra — same pattern as FUN_7103951e60]
__attribute__((optnone)) extern "C"
u64 FUN_710395d430(u64 param_1) {
    FUN_710395d760(param_1);
    return FUN_710395d7a0();
}

// 0x710395f210 — wrapper with global context arg (48 bytes)
// [derived: Ghidra — loads DAT_7106dd40b0 as first arg]
__attribute__((optnone)) extern "C"
void FUN_710395f210(u64 param_1) {
    FUN_710395faf0(DAT_7106dd40b0, param_1);
}

// ════════════════════════════════════════════════════════════════════
// Conditional dispatch functions (80-96 bytes)
// ════════════════════════════════════════════════════════════════════

// 0x710395a890 — conditional init: if error flag clear, call with fixed param (96 bytes)
// [derived: Ghidra — checks *param_1==0 guard, inserts 0 as third arg]
__attribute__((optnone)) extern "C"
void FUN_710395a890(s32* param_1, u64 param_2, u32 param_3, u64 param_4) {
    if (*param_1 == 0) {
        FUN_710395a6a0(param_1, param_2, 0, param_3, param_4);
    }
}

// 0x710395a8f0 — JSON array open: if error flag clear, emit key+bracket (96 bytes)
// [derived: Ghidra — aa80=indent, a4a0=printf, aad0=depth push]
__attribute__((optnone)) extern "C"
void FUN_710395a8f0(s32* param_1, u64 param_2) {
    if (*param_1 == 0) {
        FUN_710395aa80(param_1);
        FUN_710395a4a0(param_1, "\"%s\": [", param_2);
        FUN_710395aad0(param_1);
    }
}

// 0x710395a950 — JSON array close: if error flag clear, emit bracket (80 bytes)
// [derived: Ghidra — same indent/printf/depth pattern]
__attribute__((optnone)) extern "C"
void FUN_710395a950(s32* param_1) {
    if (*param_1 == 0) {
        FUN_710395aa80(param_1);
        FUN_710395a4a0(param_1, (const char*)&DAT_710425d0a2);
        FUN_710395aad0(param_1);
    }
}

// 0x710395b8a0 — lookup by key, null-coalesce to 0 (96 bytes)
// [derived: Ghidra — calls FUN_710395b990, returns result or 0 if null]
__attribute__((optnone)) extern "C"
s64 FUN_710395b8a0(u64 param_1, u32 param_2) {
    s64 result = FUN_710395b990(param_1, param_2);
    if (result == 0) {
        return 0;
    }
    return result;
}

// 0x710395bba0 — check flag, branch, chain (96 bytes)
// [derived: Ghidra — checks FUN_710395b830, if false returns 0,
//  else calls FUN_710395b850 → FUN_710395bc20]
__attribute__((optnone)) extern "C"
u64 FUN_710395bba0(u64 param_1) {
    u8 flag = FUN_710395b830(param_1);
    if (flag & 1) {
        return 0;
    }
    u64 val = FUN_710395b850(param_1);
    FUN_710395bc20(val);
    return val;
}

// 0x710395bd70 — check flag, branch to two paths (96 bytes)
// [derived: Ghidra — if !b830: b850→c410; else 58840(p2)→p2]
__attribute__((optnone)) extern "C"
u64 FUN_710395bd70(u64 param_1, u64 param_2) {
    u8 flag = FUN_710395b830(param_1);
    if (flag & 1) {
        FUN_7103958840(param_2);
        return param_2;
    }
    FUN_710395b850(param_1);
    return FUN_710395c410();
}

// 0x710395c6b0 — set byte flag via FUN_710395d240 (80 bytes)
// [derived: Ghidra — gets pointer via d240, writes param_2 & 1]
__attribute__((optnone)) extern "C"
void FUN_710395c6b0(u64 param_1, u8 param_2) {
    u8* ptr = (u8*)FUN_710395d240(param_1);
    *ptr = param_2 & 1;
}

// 0x710395c650 — multi-call sequence with global flag (96 bytes)
// [derived: Ghidra — c6b0(inverted flag)+ea10+conditional c700]
__attribute__((optnone)) extern "C"
void FUN_710395c650(u64 param_1) {
    FUN_710395c6b0(param_1, ~DAT_7106dd3fec & 1);
    FUN_710395ea10(param_1);
    if (DAT_7106dd3fec - 1 != 0) {
        FUN_710395c700(DAT_7106dd3fec - 1, param_1);
    }
}

// 0x710395e090 — conditional dispatch: check flag, then call (80 bytes)
// [derived: Ghidra — calls FUN_710395e0e0(param_2+8), if true calls FUN_710395ae10]
__attribute__((optnone)) extern "C"
void FUN_710395e090(u64 param_1, s64 param_2) {
    u8 flag = FUN_710395e0e0(param_2 + 8);
    if (flag & 1) {
        FUN_710395ae10(param_1, param_2);
    }
}

// 0x710395e850 — dispatch based on handle range (96 bytes)
// [derived: Ghidra — if param <= 0x1000: FUN_710395d760; else FUN_710395e8b0(param-0x1000, param)]
__attribute__((optnone)) extern "C"
u32 FUN_710395e850(u64 param_1) {
    if (param_1 <= 0x1000) {
        FUN_710395d760(param_1);
        return FUN_710395d7a0();
    } else {
        return FUN_710395e8b0(param_1 - 0x1000, param_1);
    }
}

// 0x710395ede0 — multi-setter: init sequence on resource handle (96 bytes)
// [derived: Ghidra — ee90+58840+set 3 flags via wrapper calls+ee40]
__attribute__((optnone)) extern "C"
void FUN_710395ede0(u64 param_1) {
    FUN_710395ee90(param_1);
    FUN_7103958840(0);
    u8* p1 = (u8*)FUN_710395eeb0(param_1);
    *p1 = 1;
    u8* p2 = (u8*)FUN_710395eb70(param_1);
    *p2 = 0;
    u8* p3 = (u8*)FUN_710395eb20(param_1);
    *p3 = 1;
    FUN_710395ee40(param_1);
}

// 0x710395f3c0 — check flag, branch, chain (96 bytes)
// [derived: Ghidra — same pattern as FUN_710395bba0 but different callees]
__attribute__((optnone)) extern "C"
u64 FUN_710395f3c0(u64 param_1) {
    u8 flag = FUN_710395f440(param_1);
    if (flag & 1) {
        return 0;
    }
    u64 val = FUN_710395f460(param_1);
    return FUN_710395f480(val);
}

// 0x7103952a90 — check flag, branch to two paths (96 bytes)
// [derived: Ghidra — same pattern as FUN_710395bd70 but different callees]
__attribute__((optnone)) extern "C"
u64 FUN_7103952a90(u64 param_1, u64 param_2) {
    u8 flag = FUN_7103950de0(param_1);
    if (flag & 1) {
        FUN_7103958840(param_2);
        return param_2;
    }
    FUN_7103950e00(param_1);
    return FUN_7103953330();
}
