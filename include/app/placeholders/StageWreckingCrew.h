#pragma once
#include "app/placeholders/StageBase.h"

// Inner container types used by StageWreckingCrew destructor

// ContainerWithBuf10 — container sub-object with buffer at +0x10/+0x18
// [derived: dtor pattern in FUN_7102fe2330, field at +0xAC0]
struct ContainerWithBuf10 {
    u8 unk_0x00[0x10];          // +0x00
    void* buffer_begin;         // +0x10 [derived: freed in dtor]
    void* buffer_end;           // +0x18 [derived: set to begin before free]
};

// ContainerWithBuf18 — container sub-object with buffer at +0x18/+0x20
// [derived: dtor pattern in FUN_7102fe2330, field at +0x970]
struct ContainerWithBuf18 {
    u8 unk_0x00[0x18];          // +0x00
    void* buffer_begin;         // +0x18 [derived: freed in dtor]
    void* buffer_end;           // +0x20 [derived: set to begin before free]
};

// StageWreckingCrew — extends StageBase directly
// Vtable: PTR_LAB_710515d6e0
// Destructor: FUN_7102fe2330
// [derived: dtor at 0x7102fe2330, frees 9 owned sub-objects + 1 owned container + embedded sub]

struct StageWreckingCrew : StageBase {
    u8 unk_0x728[0x10];                  // +0x728
    u64 embedded_sub_0x738;              // +0x738 [derived: embedded sub-object, cleanup via FUN_7102fe2250]
    u8 unk_0x740[0x230];                 // +0x740
    ContainerWithBuf18* container_0x970; // +0x970 [derived: owned container, inner buffer at +0x18/+0x20]
    u8 unk_0x978[0x138];                 // +0x978
    void* owned_0xAB0;                   // +0xAB0 [derived: cleanup via FUN_7102ff1420 + free]
    void* owned_0xAB8;                   // +0xAB8 [derived: cleanup via FUN_7102ff2b40 + free]
    ContainerWithBuf10* container_0xAC0; // +0xAC0 [derived: container, inner buffer at +0x10/+0x18]
    void* owned_0xAC8;                   // +0xAC8 [derived: cleanup via FUN_7102ff02b0 + free]
    void* owned_0xAD0;                   // +0xAD0 [derived: cleanup via FUN_7102feb430 + free]
    void* owned_0xAD8;                   // +0xAD8 [derived: cleanup via FUN_7102ff2520 + free]
    void* owned_0xAE0;                   // +0xAE0 [derived: cleanup via FUN_7102ff2e20 + free]
    void* owned_0xAE8;                   // +0xAE8 [derived: simple free]
    void* owned_0xAF0;                   // +0xAF0 [derived: cleanup via FUN_7102fed000 + free]
};
static_assert(sizeof(StageWreckingCrew) == 0xAF8, "StageWreckingCrew size mismatch");
