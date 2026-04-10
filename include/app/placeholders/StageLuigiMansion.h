#pragma once
#include "app/placeholders/StageBase.h"

// StageLuigiMansion — extends StageBase directly
// Vtable: PTR_LAB_710510dcf0
// Destructor: FUN_7102ada090
// [derived: dtor at 0x7102ada090, releases 2 shared_ptrs, 2 owned containers, zeros 4 fields]

struct StageLuigiMansion : StageBase {
    u8 unk_0x728[0x98];         // +0x728
    void* data_0x7C0;           // +0x7C0 [derived: zeroed in ~StageLuigiMansion]
    void* data_0x7C8;           // +0x7C8 [derived: zeroed in ~StageLuigiMansion]
    void* data_0x7D0;           // +0x7D0 [derived: zeroed in ~StageLuigiMansion]
    void* data_0x7D8;           // +0x7D8 [derived: zeroed in ~StageLuigiMansion]
    u8 unk_0x7E0[0x38];         // +0x7E0
    void* container_0x818;      // +0x818 [derived: owned container, inner ptr has vtable dtor at +0x68]
    void* container_0x820;      // +0x820 [derived: owned container with inner ptr]
    u8 unk_0x828[0x8];          // +0x828
    void* shared_ctrl_0x830;    // +0x830 [derived: shared_ptr control block, RELEASE_SHARED_PTR]
    u8 unk_0x838[0x8];          // +0x838
    u64 data_0x840;             // +0x840 [derived: zeroed before shared_ptr release at +0x830]
    u64 data_0x848;             // +0x848 [derived: zeroed before shared_ptr release at +0x830]
    u8 unk_0x850[0x8];          // +0x850
    void* shared_ctrl_0x858;    // +0x858 [derived: shared_ptr control block, RELEASE_SHARED_PTR]
};
static_assert(sizeof(StageLuigiMansion) == 0x860, "StageLuigiMansion size mismatch");
