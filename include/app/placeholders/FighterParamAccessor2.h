#pragma once

#include "types.h"

namespace app {

// FighterParamAccessor2PhysicsParams — sub-struct at FighterParamAccessor2+0x12d0.
// Contains common physics/kinetic parameters used by many fighter param getters.
// Fields mapped from: fighter_core.cpp FPA2 param getter batch (0x71016593a0+).
// All field names are community names from the modding community, validated
// against Ghidra decompilation showing consistent offset patterns.
struct FighterParamAccessor2PhysicsParams {
    u8   unk_0x00[0x230];
    u32  init_bound_frame;             // +0x230 [derived: FUN_71016593a0 reads as u32]
    f32  special_lw_gravity;           // +0x234 [derived: FUN_71016593c0 reads as f32]
    u8   unk_0x238[0x8];
    f32  length_gravity;               // +0x240 [derived: FUN_7101659400]
    f32  length_speed_y_max;           // +0x244 [derived: FUN_7101659420]
    u8   unk_0x248[0x18];
    f32  length_angle_x_velocity;      // +0x260 [derived: FUN_7101659440]
    f32  length_angle_y_velocity;      // +0x264 [derived: FUN_7101659460]
    f32  length_angle_z_velocity;      // +0x268 [derived: FUN_7101659480]
    f32  side_gravity;                 // +0x26C [derived: FUN_71016594a0]
    f32  side_speed_y_max;             // +0x270 [derived: FUN_71016594c0]
    u8   unk_0x274[0x18];
    f32  side_angle_x_velocity;        // +0x28C [derived: FUN_71016594e0]
    f32  side_angle_y_velocity;        // +0x290 [derived: FUN_7101659500]
    f32  side_angle_z_velocity;        // +0x294 [derived: FUN_7101659520]
    u8   unk_0x298[0xC];
    u32  flashing_frame_before_life_over; // +0x2A4 [derived: FUN_7101659560 reads as u32]
    f32  rebound_speed_x_add;          // +0x2A8 [derived: FUN_7101659580]
    f32  rebound_speed_y_add;          // +0x2AC [derived: FUN_71016595a0]
};

// FighterParamAccessor2 — singleton accessed via lib::Singleton<app::FighterParamAccessor2>::instance_.
// Name confirmed from .dynsym: _ZN3lib9SingletonIN3app22FighterParamAccessor2EE9instance_E
// Large struct with multiple sub-struct pointers. Only the physics params sub-struct
// at +0x12d0 has been mapped so far.
struct FighterParamAccessor2 {
    u8   unk_0x00[0x12D0];
    FighterParamAccessor2PhysicsParams* physics_params; // +0x12D0 [derived: 15+ param getters deref this]
};

} // namespace app
