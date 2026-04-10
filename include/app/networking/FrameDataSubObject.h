#pragma once

#include "types.h"

// Frame data sub-object for net frame exchange
//
// Constructed by FUN_710012fbb0. Contains multiple vtable pointers
// and inline data used by the frame data send/recv pipeline.
//
// Layout derived from FUN_710012fbb0 (constructor).

namespace app {

struct FrameDataSubObject {
    // +0x00: primary vtable (set to PTR_DAT_71052a4ba0+0x10)
    // [derived: FUN_710012fbb0 stores puVar1 = PTR_DAT_71052a4ba0+0x10 to *param_1]
    void* vtable_primary;              // +0x00

    u64 pad_08;                        // +0x08

    // +0x10: secondary vtable (set to PTR_DAT_71052a4ba0+0x50)
    // [derived: FUN_710012fbb0 stores PTR_DAT_71052a4ba0+0x50 to param_1[2]]
    void* vtable_secondary;            // +0x10

    // +0x18: tertiary vtable (set to PTR_DAT_71052a4870+0x10)
    // [derived: FUN_710012fbb0 stores puVar2 = PTR_DAT_71052a4870+0x10 to param_1[3]]
    void* vtable_tertiary;             // +0x18

    // +0x20: self-pointer to inline data at +0x34
    // [derived: param_1[4] = (long)param_1 + 0x34]
    void* inline_data_ptr;             // +0x20

    // +0x28: constant 0x28
    // [derived: param_1[5] = 0x28]
    u64 data_offset;                   // +0x28

    // +0x30..+0x33: padding
    u32 pad_30;                        // +0x30

    // +0x34..+0x3B: inline data (zeroed)
    // [derived: FUN_710012fbb0 writes 0 to *(u64*)(param_1+0x34)]
    u64 inline_data;                   // +0x34

    // +0x3C..+0x3F: zeroed
    // [derived: FUN_710012fbb0 writes 0 to *(u32*)(param_1+0x3c)]
    u32 field_3c;                      // +0x3C

    // +0x40: zeroed (param_1[8])
    // [derived: FUN_710012fbb0 writes 0 to param_1[8]]
    u64 field_40;                      // +0x40

    // +0x48..+0x49: zeroed (u16)
    // [derived: FUN_710012fbb0 writes 0 to *(u16*)(param_1+9) which is +0x48]
    u16 field_48;                      // +0x48

    // +0x4A..+0x51: zeroed (u64)
    // [derived: FUN_710012fbb0 writes 0 to *(u64*)(param_1+0x4a)]
    u8 pad_4a[8];                      // +0x4A

    // +0x52..+0x59: zeroed (u64)
    // [derived: FUN_710012fbb0 writes 0 to *(u64*)(param_1+0x52)]
    u8 pad_52[8];                      // +0x52

    // +0x5A..+0x5B: zeroed (u16)
    // [derived: FUN_710012fbb0 writes 0 to *(u16*)(param_1+0x5a)]
    u16 field_5a;                      // +0x5A

    // +0x5C: zeroed (u8)
    // [derived: FUN_710012fbb0 writes 0 to *(u8*)(param_1+0x5c)]
    u8 field_5c;                       // +0x5C

    u8 pad_5d[3];                      // +0x5D

    // +0x60: param_1[0xc] = 0 → field at offset 0x60
    // [derived: FUN_710012fbb0 writes 0 to param_1[0xc]]
    u64 field_60;                      // +0x60
};
// sizeof = 0x68

} // namespace app
