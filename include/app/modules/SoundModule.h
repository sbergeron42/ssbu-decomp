#pragma once

#include "types.h"

namespace app {

// SoundModule -- accessed at BattleObjectModuleAccessor+0x148
// Handles sound effects, BGM, voice playback, and audio parameters.
// Vtable layout recovered from lua_bind dispatchers (offsets 0xa0-0x2d8).
struct SoundModule {
    // Base class entries (indices 0-19, offsets 0x00-0x98)
    virtual ~SoundModule();                                                         // 0x00, 0x08
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
    virtual void _vf14();                                                           // 0x70
    virtual void _vf15();                                                           // 0x78
    virtual void _vf16();                                                           // 0x80
    virtual void _vf17();                                                           // 0x88
    virtual void _vf18();                                                           // 0x90
    virtual void _vf19();                                                           // 0x98

    // Sound playback (offsets 0xa0-0x110)                                          [confirmed: lua_bind API names]
    virtual void set_position_sub(u64 p1);                                          // 0xa0
    virtual void play_se(u64 hash, bool p2, bool p3, bool p4, bool p5, u64 p6);    // 0xa8
    virtual void play_se_no3d(u64 p1, bool p2, bool p3);                           // 0xb0
    virtual void play_se_pos(u64 p1, u64 p2, bool p3, bool p4);                    // 0xb8
    virtual void play_status_se(u64 p1, bool p2, bool p3, bool p4);                // 0xc0
    virtual void stop_status_se();                                                  // 0xc8
    virtual void play_sequence(u64 p1, bool p2, bool p3);                           // 0xd0
    virtual void set_play_hit_se_flag(bool p1);                                     // 0xd8
    virtual u32 get_play_hit_se_flag();                                             // 0xe0
    virtual void set_no_hit_se(bool p1);                                            // 0xe8
    virtual u64 get_no_hit_se();                                                    // 0xf0
    virtual void* play_hit_se(u64 p1, u64 p2);                                     // 0xf8
    virtual void* play_damage_se(u64 p1, u64 p2, u64 p3, u64 p4);                  // 0x100
    virtual void play_step(u64 p1);                                                 // 0x108
    virtual void* play_step_flippable(u64 p1, u64 p2);                             // 0x110

    // Landing / Down / Voice (offsets 0x118-0x130)
    virtual void _vf35();                                                           // 0x118
    virtual void play_landing_se(u64 p1);                                           // 0x120  [confirmed: lua_bind]
    virtual void play_down_se(u64 p1);                                              // 0x128  [confirmed: lua_bind]
    virtual void* play_fly_voice(u64 p1, u64 p2);                                  // 0x130  [confirmed: lua_bind]

    // Volume / Pitch control (offsets 0x138-0x188)                                 [confirmed: lua_bind API names]
    virtual void set_se_vol(u64 p1, u64 p2);                                       // 0x138
    virtual void* get_se_vol(u64 p1);                                               // 0x140
    virtual void set_se_vol_db(u64 p1, u64 p2);                                    // 0x148
    virtual void* get_se_vol_db(u64 p1);                                            // 0x150
    virtual void set_auto_se_pitch();                                               // 0x158
    virtual f32 get_auto_se_pitch();                                                // 0x160
    virtual void set_se_pitch_cent(u64 p1);                                         // 0x168
    virtual void set_se_pitch_ratio(u64 p1);                                        // 0x170
    virtual void set_se_pitch_status();                                             // 0x178
    virtual void set_se_pitch_status_handle(u64 p1);                                // 0x180
    virtual void set_continue_se_at_game_finish(u64 p1, bool p2);                   // 0x188

    // Stop / Pause (offsets 0x190-0x1b8)                                           [confirmed: lua_bind API names]
    virtual void stop_se(u64 p1, u64 p2);                                           // 0x190
    virtual void stop_se_all(u64 p1, bool p2, bool p3);                             // 0x198
    virtual void stop_loop_se_all(u64 p1);                                          // 0x1a0
    virtual void stop_se_handle(u64 p1, u64 p2);                                    // 0x1a8
    virtual void stop_all_sound();                                                   // 0x1b0
    virtual void pause_se_all(bool p1);                                              // 0x1b8

    // Speed / Landing SE (offsets 0x1c0-0x1d8)                                     [confirmed: lua_bind API names]
    virtual void set_se_speed(u64 p1);                                              // 0x1c0
    virtual void set_landing_se(u64 p1);                                            // 0x1c8
    virtual u64 get_landing_se();                                                    // 0x1d0
    virtual void play_landing_se_registered();                                       // 0x1d8

    // Unknown (offsets 0x1e0-0x218)
    virtual void _vf60();                                                           // 0x1e0
    virtual void _vf61();                                                           // 0x1e8
    virtual void _vf62();                                                           // 0x1f0
    virtual void _vf63();                                                           // 0x1f8
    virtual void _vf64();                                                           // 0x200
    virtual void _vf65();                                                           // 0x208
    virtual void _vf66();                                                           // 0x210
    virtual void _vf67();                                                           // 0x218

    // Takeout SE (offsets 0x220-0x258)                                             [confirmed: lua_bind API names]
    virtual void set_takeout_se(u64 p1);                                            // 0x220
    virtual void set_takeout_se_status(u64 p1);                                     // 0x228
    virtual void _vf70();                                                           // 0x230
    virtual void reset_takeout_se();                                                // 0x238
    virtual void play_takeout_se();                                                 // 0x240
    virtual u64 get_takeout_se();                                                   // 0x248
    virtual u32 get_takeout_se_status_flag();                                       // 0x250
    virtual void set_play_inhivit(u64 p1, u64 p2);                                 // 0x258

    // Playing state / Labels (offsets 0x260-0x280)                                 [confirmed: lua_bind API names]
    virtual bool is_playing(u64 p1);                                                // 0x260
    virtual bool is_playing_status(u64 p1);                                         // 0x268
    virtual bool is_playing_voice();                                                // 0x270
    virtual void* get_common_sound_label(u64 p1);                                   // 0x278
    virtual void play_status_bgm(u64 p1);                                           // 0x280

    // Unknown (offsets 0x288-0x2b8)
    virtual void _vf81();                                                           // 0x288
    virtual void _vf82();                                                           // 0x290
    virtual void _vf83();                                                           // 0x298
    virtual void _vf84();                                                           // 0x2a0
    virtual void _vf85();                                                           // 0x2a8
    virtual void _vf86();                                                           // 0x2b0
    virtual void _vf87();                                                           // 0x2b8

    // Calibration / Remain (offsets 0x2c0-0x2d8)
    virtual void set_gamespeed_se_calibration(bool p1);                             // 0x2c0  [confirmed: lua_bind]
    virtual void _vf89();                                                           // 0x2c8
    virtual void _vf90();                                                           // 0x2d0
    virtual void set_remain_se(bool p1);                                            // 0x2d8  [confirmed: lua_bind]
};

} // namespace app
