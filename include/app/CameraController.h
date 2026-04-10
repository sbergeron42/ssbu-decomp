#pragma once

#include "types.h"

namespace app {

// CameraController — global camera state singleton
// Singleton at DAT_71052b7f00
// [derived: Ghidra analysis of camera_functions.cpp dispatch patterns,
//  convert_pos_dead_range_gravity (0x7102282ef0), set_dead_range (0x710164c390),
//  dead_range (0x7102282810), get_camera_range (0x71015cb960)]
struct CameraController {
    s32 unk_0x00;                       // +0x000
    s32 camera_mode;                    // +0x004 [inferred: checked == 1 in is_camera_mode_active]
    u8 unk_0x008[0x2A8];               // +0x008

    // -- Quake subsystem (0x2B0–0x827) --
    u8 quake_base[0x2C];               // +0x2B0 [derived: passed to FUN_71005162f0 for quake dispatch]
    u32 quake_array[82];               // +0x2DC [derived: indexed by kind in stop_quake/request_quake]
    u8 unk_0x424[0x400];               // +0x424
    u32 quake_bitmask;                 // +0x824 [derived: bitfield cleared in stop_quake]
    u8 unk_0x828[0x408];               // +0x828

    // -- Dead range (0xC30) --
    float dead_range_neg;              // +0xC30 [inferred: dead range negative boundary, used in gravity rotation]
    float dead_range_pos;              // +0xC34 [inferred: dead range positive boundary, used in gravity rotation]
    u8 unk_0xC38[0x64];                // +0xC38

    s32 camera_ref_count;              // +0xC9C [derived: incremented/decremented in add/remove_camera_reference]
    u8 unk_0xCA0[0x210];               // +0xCA0

    // -- Camera view parameters (0xEB0+) --
    float camera_center_pos[4];        // +0xEB0 [inferred: camera center position (x,y,z,w), vector-loaded in get_camera_range]
    u8 unk_0xEC0[0x78];                // +0xEC0

    float camera_half_height_scale;    // +0xF38 [inferred: half-height scale factor in get_camera_range]
    u8 unk_0xF3C[0x1C];                // +0xF3C

    float width_height_ratio;          // +0xF58 [inferred: width-to-height ratio in get_camera_range]
    u8 unk_0xF5C[0xC];                 // +0xF5C

    float aspect_ratio;                // +0xF68 [inferred: aspect ratio in get_camera_range]
};

} // namespace app
