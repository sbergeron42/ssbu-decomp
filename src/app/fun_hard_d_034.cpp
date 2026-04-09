#include "types.h"

// HARD-tier FUN_* functions — batch hard-d-034
// Pool-d worker: resource handle lookup tables, bitfield accessors, utility functions
// Mixed -O0 (optnone) and -O2

#define HIDDEN __attribute__((visibility("hidden")))

// ---- External functions ----

extern "C" void  FUN_710395f4b0(u64);
extern "C" void  FUN_710392e590(void*);   // je_free

// ---- External data ----

extern "C" u8  DAT_7104863900[] HIDDEN;  // [inferred: resource handle table — u64 entries indexed by type byte]
extern "C" u8  DAT_7104864040[] HIDDEN;  // [inferred: resource handle type lookup — byte per 8-handle block]

// ════════════════════════════════════════════════════════════════════
// Resource handle lookup tables
// Pattern: handle → byte index (type), then type → table entry (u64)
// DAT_7104864040[]: byte lookup indexed by (handle - 1) >> 3
// DAT_7104863900[]: u64 table indexed by type byte
// ════════════════════════════════════════════════════════════════════

// 0x7103952190 — resource handle type lookup (64 bytes)
// [derived: Ghidra — returns byte from DAT_7104864040 table at (param_1-1)>>3]
__attribute__((optnone)) extern "C"
u32 FUN_7103952190(u64 param_1) {
    return DAT_7104864040[(u32)(param_1 - 1) >> 3];
}

// 0x71039521d0 — resource type to table entry (48 bytes)
// [derived: Ghidra — returns u64 from DAT_7104863900 at param_1*8]
__attribute__((optnone)) extern "C"
u64 FUN_71039521d0(u32 param_1) {
    return *(u64*)(&DAT_7104863900[(u64)param_1 * 8]);
}

// 0x710395d760 — resource handle type lookup (same as FUN_7103952190) (64 bytes)
// [derived: Ghidra — identical logic, different compilation unit]
__attribute__((optnone)) extern "C"
u32 FUN_710395d760(u64 param_1) {
    return DAT_7104864040[(u32)(param_1 - 1) >> 3];
}

// 0x710395d7a0 — resource type to table entry (same as FUN_71039521d0) (48 bytes)
// [derived: Ghidra — identical logic, different compilation unit]
__attribute__((optnone)) extern "C"
u64 FUN_710395d7a0(u32 param_1) {
    return *(u64*)(&DAT_7104863900[(u64)param_1 * 8]);
}

// ════════════════════════════════════════════════════════════════════
// Bitfield accessors for resource handle metadata
// ════════════════════════════════════════════════════════════════════

// 0x7103953450 — get 8-bit field at bits 18-25 (48 bytes)
// [derived: Ghidra — extracts (*param_1 >> 18) & 0xFF]
__attribute__((optnone)) extern "C"
u32 FUN_7103953450(u64* param_1) {
    return (u32)(*param_1 >> 18) & 0xFF;
}

// 0x7103952af0 — set 8-bit field at bits 18-25 (64 bytes)
// [derived: Ghidra — clears bits 18-25, ORs in param_2 << 18]
__attribute__((optnone)) extern "C"
void FUN_7103952af0(u64* param_1, u32 param_2) {
    *param_1 = (*param_1 & 0xFFFFFFFFFC03FFFFULL) | ((u64)param_2 << 18);
}

// ════════════════════════════════════════════════════════════════════
// Array element address calculators
// ════════════════════════════════════════════════════════════════════

// 0x7103953f30 — array element address: base + index * 0x18 + 0x10 (48 bytes)
// [derived: Ghidra — offset calculation for stride-0x18 array with 0x10 header]
__attribute__((optnone)) extern "C"
s64 FUN_7103953f30(s64 param_1, u32 param_2) {
    return param_1 + (u64)param_2 * 0x18 + 0x10;
}

// 0x710395aff0 — array element address: same as FUN_7103953f30 (48 bytes)
// [derived: Ghidra — identical logic, different compilation unit]
__attribute__((optnone)) extern "C"
s64 FUN_710395aff0(s64 param_1, u32 param_2) {
    return param_1 + (u64)param_2 * 0x18 + 0x10;
}

// 0x7103953e70 — array element address with base offset (64 bytes)
// [derived: Ghidra — index adjusted by -0x34, offset 0x560, stride 0x18]
__attribute__((optnone)) extern "C"
s64 FUN_7103953e70(s64 param_1, s32 param_2) {
    return param_1 + (u64)(u32)(param_2 - 0x34) * 0x18 + 0x560;
}

// 0x710395b020 — array element address with base offset (same as FUN_7103953e70) (64 bytes)
// [derived: Ghidra — identical logic, different compilation unit]
__attribute__((optnone)) extern "C"
s64 FUN_710395b020(s64 param_1, s32 param_2) {
    return param_1 + (u64)(u32)(param_2 - 0x34) * 0x18 + 0x560;
}

// ════════════════════════════════════════════════════════════════════
// Simple utility functions
// ════════════════════════════════════════════════════════════════════

// 0x71039577e0 — in-place multiply (48 bytes)
// [derived: Ghidra — *param_1 *= param_2]
__attribute__((optnone)) extern "C"
void FUN_71039577e0(s64* param_1, s64 param_2) {
    *param_1 = *param_1 * param_2;
}

// 0x7103957850 — safe divide: returns 0 if divisor is 0 (48 bytes)
// [derived: Ghidra — if *param_2 != 0: *param_1 / *param_2; else 0]
__attribute__((optnone)) extern "C"
u64 FUN_7103957850(u64* param_1, u64* param_2) {
    u64 result = 0;
    if (*param_2 != 0) {
        result = *param_1 / *param_2;
    }
    return result;
}

// 0x710395fc00 — null check: returns true if non-null (64 bytes)
// [derived: Ghidra — return param_1 != 0]
__attribute__((optnone)) extern "C"
bool FUN_710395fc00(s64 param_1) {
    return param_1 != 0;
}

// 0x710395c5b0 — field setter: write u64 at param_2+0x520 (48 bytes)
// [derived: Ghidra — stores param_3 at offset 0x520 of param_2]
__attribute__((optnone)) extern "C"
void FUN_710395c5b0(u64 param_1, s64 param_2, u64 param_3) {
    *(u64*)(param_2 + 0x520) = param_3;
}

// 0x710395c620 — field clearer: zero u64 at param_2+0x520 (48 bytes)
// [derived: Ghidra — clears the field set by FUN_710395c5b0]
__attribute__((optnone)) extern "C"
void FUN_710395c620(u64 param_1, s64 param_2) {
    *(u64*)(param_2 + 0x520) = 0;
}

// 0x710395f480 — wrapper: delegates to FUN_710395f4b0 (48 bytes)
__attribute__((optnone)) extern "C"
void FUN_710395f480(u64 param_1) {
    FUN_710395f4b0(param_1);
}

// ════════════════════════════════════════════════════════════════════
// Arithmetic operators (in-place)
// ════════════════════════════════════════════════════════════════════

// 0x7103957760 — in-place add (64 bytes)
// [derived: Ghidra — *param_1 += *param_2]
__attribute__((optnone)) extern "C"
void FUN_7103957760(s64* param_1, s64* param_2) {
    *param_1 = *param_1 + *param_2;
}

// 0x71039577a0 — in-place subtract (64 bytes)
// [derived: Ghidra — *param_1 -= *param_2]
__attribute__((optnone)) extern "C"
void FUN_71039577a0(s64* param_1, s64* param_2) {
    *param_1 = *param_1 - *param_2;
}

// 0x7103957810 — in-place divide by 200 (64 bytes)
// [derived: Ghidra — *param_1 /= 200]
__attribute__((optnone)) extern "C"
void FUN_7103957810(u64* param_1) {
    *param_1 = *param_1 / 200;
}

// ════════════════════════════════════════════════════════════════════
// Bitfield extractors and mask operations
// ════════════════════════════════════════════════════════════════════

// 0x7103953210 — extract 4-bit field at bits 32-35 (64 bytes)
// [derived: Ghidra — (param_1 >> 32) & 0xF]
__attribute__((optnone)) extern "C"
u64 FUN_7103953210(u64 param_1) {
    return (param_1 >> 32) & 0xF;
}

// 0x7103953250 — clear lower 32 bits (96 bytes)
// [derived: Ghidra — param_1 & 0xFFFFFFFF00000000]
__attribute__((optnone)) extern "C"
u64 FUN_7103953250(u64 param_1) {
    return param_1 & 0xFFFFFFFF00000000ULL;
}

// 0x710395c2f0 — extract 4-bit field at bits 32-35 (same as FUN_7103953210) (64 bytes)
// [derived: Ghidra — identical logic, different compilation unit]
__attribute__((optnone)) extern "C"
u64 FUN_710395c2f0(u64 param_1) {
    return (param_1 >> 32) & 0xF;
}

// 0x710395c330 — clear lower 32 bits (same as FUN_7103953250) (96 bytes)
// [derived: Ghidra — identical logic, different compilation unit]
__attribute__((optnone)) extern "C"
u64 FUN_710395c330(u64 param_1) {
    return param_1 & 0xFFFFFFFF00000000ULL;
}

// 0x7103958370 — extract 4-bit field at bits 32-35 (third instance) (64 bytes)
// [derived: Ghidra — identical logic, third compilation unit]
__attribute__((optnone)) extern "C"
u64 FUN_7103958370(u64 param_1) {
    return (param_1 >> 32) & 0xF;
}

// ════════════════════════════════════════════════════════════════════
// No-op / empty functions
// ════════════════════════════════════════════════════════════════════

// 0x7103957e00 — empty function (64 bytes)
__attribute__((optnone)) extern "C"
void FUN_7103957e00(void) {
}

// 0x7103957e70 — empty function (64 bytes)
__attribute__((optnone)) extern "C"
void FUN_7103957e70(void) {
}

// 0x710395ee40 — empty function (80 bytes)
// [derived: Ghidra — no-op, called during resource handle init sequences]
__attribute__((optnone)) extern "C"
void FUN_710395ee40(u64 param_1) {
}

// ════════════════════════════════════════════════════════════════════
// Conditional dispatch (resource init)
// ════════════════════════════════════════════════════════════════════

extern "C" u64   FUN_710395f730(void);
extern "C" u64   FUN_710395eeb0(u64);
extern "C" s32   FUN_710395fa30(void);
extern "C" void  FUN_710395f210(u64);
extern "C" u8    DAT_7105296238 HIDDEN;
extern "C" u32   DAT_7106dd40b4 HIDDEN;

// 0x710395f6d0 — check if resource system initialized, init if needed (96 bytes)
// [derived: Ghidra — if fa30==0: call f210 to init, set flag; return was-already-init]
__attribute__((optnone)) extern "C"
bool FUN_710395f6d0(void) {
    s32 result = FUN_710395fa30();
    if (result == 0) {
        FUN_710395f210((u64)&DAT_7105296238);
        DAT_7106dd40b4 = 1;
    }
    return result != 0;
}

// 0x710395f670 — allocate resource handle with init guard (96 bytes)
// [derived: Ghidra — if !f6d0: allocate via f730, set flag via eeb0; else 0]
__attribute__((optnone)) extern "C"
u64 FUN_710395f670(void) {
    u8 flag = FUN_710395f6d0();
    if (flag & 1) {
        return 0;
    }
    u64 handle = FUN_710395f730();
    u8* p = (u8*)FUN_710395eeb0(handle);
    *p = 1;
    return handle;
}
