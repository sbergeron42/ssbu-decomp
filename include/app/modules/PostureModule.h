#pragma once

#include "types.h"

namespace app {

// PostureModule — accessed at BattleObjectModuleAccessor+0x38
// Handles position, rotation, scale, and direction of battle objects.
// Vtable layout recovered from lua_bind dispatchers (offsets 0x58–0x180).
struct PostureModule {
    // Base class entries (indices 0–10, offsets 0x00–0x50)
    virtual ~PostureModule();                              // 0x00, 0x08
    virtual void _vf2();                                   // 0x10
    virtual void _vf3();                                   // 0x18
    virtual void _vf4();                                   // 0x20
    virtual void _vf5();                                   // 0x28
    virtual void _vf6();                                   // 0x30
    virtual void _vf7();                                   // 0x38
    virtual void _vf8();                                   // 0x40
    virtual void _vf9();                                   // 0x48
    virtual void _vf10();                                  // 0x50

    // Position (offsets 0x58–0x98)
    virtual void init_pos(void* pos, bool p2, bool p3);   // 0x58
    virtual f32* pos();                                    // 0x60
    virtual void* pos_2d();                                // 0x68
    virtual void set_pos(void* pos);                       // 0x70
    virtual void set_pos_2d(void* pos);                    // 0x78
    virtual void add_pos(void* pos);                       // 0x80
    virtual void add_pos_2d(void* pos);                    // 0x88
    virtual void* prev_pos();                              // 0x90
    virtual void* prev_pos_2d();                           // 0x98

    // Unknown (offsets 0xa0–0xa8)
    virtual void _vf20();                                  // 0xa0
    virtual void _vf21();                                  // 0xa8

    // Direction (offsets 0xb0–0xc0)
    virtual f32 lr();                                      // 0xb0
    virtual void set_lr(f32 lr);                           // 0xb8
    virtual void reverse_lr();                             // 0xc0

    // Rotation (offsets 0xc8–0x108)
    virtual void* init_rot();                              // 0xc8
    virtual void init_rot_2(void* p1);                     // 0xd0
    virtual f32* rot();                                    // 0xd8
    virtual void set_rot(u64 p1, u64 p2);                 // 0xe0
    virtual void init_rot_y_lr();                          // 0xe8
    virtual bool is_rot_y_lr_different_inner_lr();         // 0xf0
    virtual f32 rot_y_lr();                                // 0xf8
    virtual void update_rot_y_lr();                        // 0x100
    virtual void reverse_rot_y_lr();                       // 0x108

    // Scale (offsets 0x110–0x150)
    virtual f32 base_scale();                              // 0x110
    virtual void* scale();                                 // 0x118
    virtual void set_scale(bool p1);                       // 0x120
    virtual void _vf37();                                  // 0x128
    virtual void set_scale_status();                       // 0x130
    virtual void* init_scale();                            // 0x138
    virtual f32 owner_scale();                             // 0x140
    virtual void set_owner_scale();                        // 0x148
    virtual void set_link_scale(bool p1);                  // 0x150

    // Unknown (offsets 0x158–0x170)
    virtual void _vf43();                                  // 0x158
    virtual void _vf44();                                  // 0x160
    virtual void _vf45();                                  // 0x168
    virtual void _vf46();                                  // 0x170

    // Misc (offsets 0x178–0x180)
    virtual void set_stick_lr();                           // 0x178
    virtual void set_sync_constraint_joint(u64 p1);        // 0x180
};

} // namespace app
