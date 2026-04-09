#pragma once
#include "types.h"

// Intermediate structs for effect cleanup pointer chain
// Used by FUN_7101958da0, FUN_710195f150 (src/app/fun_hard_d_030.cpp)
// Chain: EffectModuleCtx +0x58 → EffectContainerRef +0x170/0x180 → EffectListRef +0x80 → EffectSlotRef +0x50

// [inferred: Ghidra — deepest link in chain, holds pointer to effect handle]
struct EffectSlotRef {
    u8 _pad_0x00[0x50];
    u64* handle;            // +0x50 [inferred: pointer to effect handle value, dereferenced for cleanup]
};

// [inferred: Ghidra — intermediate list/array entry linking to slot]
struct EffectListRef {
    u8 _pad_0x00[0x80];
    EffectSlotRef* slot;    // +0x80 [inferred: effect slot reference]
};

// [inferred: Ghidra — container with two effect list variants at +0x170 and +0x180]
struct EffectContainerRef {
    u8 _pad_0x00[0x170];
    EffectListRef* list_alt;  // +0x170 [inferred: effect list entry (alternate path, FUN_710195f150)]
    u8 _pad_0x178[0x08];
    EffectListRef* list;      // +0x180 [inferred: effect list entry (primary path, FUN_7101958da0)]
};

// [inferred: Ghidra — top-level context object for effect cleanup functions]
struct EffectModuleCtx {
    u8 _pad_0x00[0x58];
    EffectContainerRef* container;  // +0x58 [inferred: effect data container]
};
