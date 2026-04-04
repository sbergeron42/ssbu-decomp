#pragma once

#include "types.h"

namespace app {

// CameraModule -- accessed at BattleObjectModuleAccessor+0x60
// Handles camera control, clipping, quake effects, and zoom.
// Vtable layout recovered from lua_bind dispatchers (offsets 0x70-0x238).
struct CameraModule {
    // Base class entries (indices 0-13, offsets 0x00-0x68)
    virtual ~CameraModule();                                                        // 0x00, 0x08
    virtual void _vf2();                                                            // 0x10
    virtual void _vf3();                                                            // 0x18
    virtual void _vf4();                                                            // 0x20
    virtual void _vf5();                                                            // 0x28
    virtual void _vf6();                                                            // 0x30
    virtual void _vf7();                                                            // 0x38
    virtual void _vf8();                                                            // 0x40
    virtual void _vf9();                                                            // 0x48
    virtual void _vf10();                                                           // 0x50
    virtual void _vf11();                                                           // 0x58
    virtual void _vf12();                                                           // 0x60
    virtual void _vf13();                                                           // 0x68

    // Reset / Update (offsets 0x70-0xa0)                                           [confirmed: lua_bind API names]
    virtual void reset_all();                                                       // 0x70
    virtual void _vf15();                                                           // 0x78
    virtual void update_force(u64 p1, u64 p2, u64 p3);                             // 0x80
    virtual void set_enable_camera(bool p1, u64 p2);                                // 0x88
    virtual void set_whole(bool p1);                                                // 0x90
    virtual void set_enable_update_pos(u64 p1, u64 p2);                             // 0x98
    virtual void set_enable_interpolate_pos(bool p1, u64 p2);                       // 0xa0

    // Unknown (offsets 0xa8-0xb0)
    virtual void _vf21();                                                           // 0xa8
    virtual void _vf22();                                                           // 0xb0

    // Camera range (offsets 0xb8-0xd0)                                             [confirmed: lua_bind API names]
    virtual void reset_camera_range(u64 p1);                                        // 0xb8
    virtual void set_camera_range_offset(u64 p1, u64 p2);                           // 0xc0
    virtual void add_camera_range_offset(void* p1, u64 p2);                         // 0xc8
    virtual void add_camera_range_rect(void* p1, u64 p2);                           // 0xd0

    // Unknown (offsets 0xd8-0xe0)
    virtual void _vf27();                                                           // 0xd8
    virtual void _vf28();                                                           // 0xe0

    // Registration / Zoom (offsets 0xe8-0xf8)                                      [confirmed: lua_bind API names]
    virtual void* un_regist_camera(u64 p1);                                         // 0xe8
    virtual void* zoom_in(u64 p1, u64 p2, u64 p3, bool p4);                        // 0xf0
    virtual void* zoom_out(u64 p1);                                                 // 0xf8

    // Unknown (offsets 0x100-0x120)
    virtual void _vf32();                                                           // 0x100
    virtual void _vf33();                                                           // 0x108
    virtual void _vf34();                                                           // 0x110
    virtual void _vf35();                                                           // 0x118
    virtual void _vf36();                                                           // 0x120

    // Status / Priority / Player (offsets 0x128-0x148)                             [confirmed: lua_bind API names]
    virtual void set_status(u64 p1, u64 p2);                                        // 0x128
    virtual void set_priority(u64 p1, u64 p2);                                      // 0x130
    virtual s32 get_priority(u64 p1);                                               // 0x138
    virtual void set_player_no(u64 p1, u64 p2);                                     // 0x140
    virtual s32 get_player_no(u64 p1);                                              // 0x148

    // Unknown (offsets 0x150-0x158)
    virtual void _vf42();                                                           // 0x150
    virtual void _vf43();                                                           // 0x158

    // Damage fly / Run / Carried (offsets 0x160-0x188)                             [confirmed: lua_bind API names]
    virtual void set_damage_fly(u64 p1);                                            // 0x160
    virtual void exit_damage_fly(u64 p1);                                           // 0x168
    virtual void set_run(u64 p1);                                                   // 0x170
    virtual void exit_run(u64 p1);                                                  // 0x178
    virtual void set_being_carried(u64 p1);                                         // 0x180
    virtual void exit_being_carried(u64 p1);                                        // 0x188

    // Unknown (offset 0x190)
    virtual void _vf50();                                                           // 0x190

    // Clip detection (offsets 0x198-0x1a0)                                         [confirmed: lua_bind API names]
    virtual bool is_clip_in(bool p1);                                               // 0x198
    virtual bool is_clip_in_all(bool p1);                                           // 0x1a0

    // Unknown (offsets 0x1a8-0x1b0)
    virtual void _vf53();                                                           // 0x1a8
    virtual void _vf54();                                                           // 0x1b0

    // Global rect / Target pos (offsets 0x1b8-0x1d8)                               [confirmed: lua_bind API names]
    virtual void set_camera_range_global_rect(u64 p1, u64 p2);                      // 0x1b8
    virtual void _vf56();                                                           // 0x1c0
    virtual void* get_main_camera_target_pos();                                     // 0x1c8
    virtual void* get_main_camera_range();                                          // 0x1d0
    virtual void* get_internal_camera_target_pos();                                 // 0x1d8

    // Camera type (offsets 0x1e0-0x1f0)                                            [confirmed: lua_bind API names]
    virtual s32 get_camera_type();                                                  // 0x1e0
    virtual s32 get_camera_type_for_save();                                         // 0x1e8
    virtual void set_camera_type(u64 p1);                                           // 0x1f0

    // Unknown (offset 0x1f8)
    virtual void _vf63();                                                           // 0x1f8

    // Quake effects (offsets 0x200-0x218)                                          [confirmed: lua_bind API names]
    virtual void* req_quake(u64 p1);                                                // 0x200
    virtual void* req_quake_pos(u64 p1, u64 p2);                                   // 0x208
    virtual void* stop_quake(u64 p1);                                               // 0x210
    virtual s32 get_quakeKind();                                                    // 0x218

    // Final zoom / FOV (offsets 0x220-0x238)                                       [confirmed: lua_bind API names]
    virtual void* start_final_zoom_out(u64 p1, u64 p2, u64 p3);                    // 0x220
    virtual void end_final_zoom_out();                                              // 0x228
    virtual void* get_camera_view_volume_z0_rect();                                 // 0x230
    virtual void reset_main_camera_fov();                                           // 0x238
};

} // namespace app
