#pragma once

#include "types.h"

namespace app {

// GroundModule — accessed at BattleObjectModuleAccessor+0x58
// Handles ground collision, surfaces, cliffs, and raycasting.
// Vtable layout recovered from lua_bind dispatchers (offsets 0x80–0x818).
// All named method names derived from .dynsym lua_bind::GroundModule__*_impl functions.
struct GroundModule {
    // Base class entries (indices 0–15, offsets 0x00–0x78)
    virtual ~GroundModule();                                                       // 0x00, 0x08
    virtual void _vf2();                                                           // 0x10
    virtual void _vf3();                                                           // 0x18
    virtual void _vf4();                                                           // 0x20
    virtual void _vf5();                                                           // 0x28
    virtual void _vf6();                                                           // 0x30
    virtual void _vf7();                                                           // 0x38
    virtual void _vf8();                                                           // 0x40
    virtual void _vf9();                                                           // 0x48
    virtual void _vf10();                                                          // 0x50
    virtual void _vf11();                                                          // 0x58
    virtual void _vf12();                                                          // 0x60
    virtual void _vf13();                                                          // 0x68
    virtual void _vf14();                                                          // 0x70
    virtual void _vf15();                                                          // 0x78

    // Shape / Update (offsets 0x80–0xc0)
    virtual void update_force();                                                   // 0x80
    virtual void update_shape(bool p1);                                            // 0x88
    virtual void _vf18();                                                          // 0x90
    virtual void _vf19();                                                          // 0x98
    virtual void _vf20();                                                          // 0xa0
    virtual void _vf21();                                                          // 0xa8
    virtual void _vf22();                                                          // 0xb0
    virtual void* get_rhombus(bool p1);                                            // 0xb8
    virtual void modify_rhombus();                                                 // 0xc0

    // Unknown (offsets 0xc8–0xf8)
    virtual void _vf25();                                                          // 0xc8
    virtual void _vf26();                                                          // 0xd0
    virtual void _vf27();                                                          // 0xd8
    virtual void _vf28();                                                          // 0xe0
    virtual void _vf29();                                                          // 0xe8
    virtual void _vf30();                                                          // 0xf0
    virtual void _vf31();                                                          // 0xf8

    // Circle / Offset (offsets 0x100–0x158)
    virtual void set_init_circle(u64 p1);                                          // 0x100
    virtual void _vf33();                                                          // 0x108
    virtual void _vf34();                                                          // 0x110
    virtual f32 get_circle_radius();                                               // 0x118
    virtual void set_offset_x();                                                   // 0x120
    virtual void set_offset_y();                                                   // 0x128
    virtual f32 get_offset_x();                                                    // 0x130
    virtual f32 get_offset_y();                                                    // 0x138
    virtual void set_rhombus_offset(u64 p1);                                       // 0x140
    virtual void correct(u64 p1);                                                  // 0x148
    virtual void set_correct(u64 p1);                                              // 0x150
    virtual u32 get_correct();                                                     // 0x158

    // Collision settings (offsets 0x160–0x210)
    virtual void _vf44();                                                          // 0x160
    virtual void set_collidable(bool p1);                                          // 0x168
    virtual void _vf46();                                                          // 0x170
    virtual void _vf47();                                                          // 0x178
    virtual void _vf48();                                                          // 0x180
    virtual void _vf49();                                                          // 0x188
    virtual void set_passable_check(bool p1);                                      // 0x190
    virtual bool is_passable_check();                                              // 0x198
    virtual void _vf52();                                                          // 0x1a0
    virtual void set_cloud_through(bool p1);                                       // 0x1a8
    virtual void _vf54();                                                          // 0x1b0
    virtual void _vf55();                                                          // 0x1b8
    virtual void _vf56();                                                          // 0x1c0
    virtual void _vf57();                                                          // 0x1c8
    virtual void _vf58();                                                          // 0x1d0
    virtual void _vf59();                                                          // 0x1d8
    virtual void set_ignore_line_type1(bool p1);                                   // 0x1e0
    virtual void set_ignore_boss(bool p1);                                         // 0x1e8
    virtual bool is_ignore_fighter_other();                                         // 0x1f0
    virtual void set_ignore_fighter_other(bool p1);                                // 0x1f8
    virtual bool is_ignore_fighter_other_wall_l();                                 // 0x200
    virtual bool is_ignore_fighter_other_wall_r();                                 // 0x208
    virtual void set_correct_ignore_slope(bool p1);                                // 0x210

    // Cliff system (offsets 0x218–0x2b0)
    virtual void set_cliff_check(u64 p1);                                          // 0x218
    virtual u32 cliff_check();                                                     // 0x220
    virtual void select_cliff_hangdata(u64 p1);                                    // 0x228
    virtual void _vf70();                                                          // 0x230
    virtual void _vf71();                                                          // 0x238
    virtual bool is_status_cliff();                                                // 0x240
    virtual void* correct_pos();                                                   // 0x248
    virtual void entry_cliff();                                                    // 0x250
    virtual void reentry_cliff();                                                  // 0x258
    virtual bool can_entry_cliff();                                                // 0x260
    virtual bool can_entry_cliff_same(u64 p1);                                     // 0x268
    virtual bool can_entry_cliff_hang_data(u64 p1, u64 p2);                        // 0x270
    virtual void leave_cliff();                                                    // 0x278
    virtual void* hang_cliff_pos();                                                // 0x280
    virtual void* hang_cliff_pos_3f();                                             // 0x288
    virtual void* hang_can_entry_cliff_pos();                                      // 0x290
    virtual void* hang_cliff_dir();                                                // 0x298
    virtual void* hang_can_entry_cliff_dir();                                      // 0x2a0
    virtual void* get_cliff_movement_speed();                                      // 0x2a8
    virtual bool is_cliff_move_exception();                                         // 0x2b0

    // Collision stop / Ottotto (offsets 0x2b8–0x320)
    virtual void _vf87();                                                          // 0x2b8
    virtual void _vf88();                                                          // 0x2c0
    virtual void clear_cliff_point();                                              // 0x2c8
    virtual void set_test_coll_stop(bool p1);                                      // 0x2d0
    virtual void set_test_coll_stop_status(bool p1);                               // 0x2d8
    virtual void set_coll_stop_slidable_length();                                  // 0x2e0
    virtual void _vf93();                                                          // 0x2e8
    virtual void set_ignore_slide_up(bool p1);                                     // 0x2f0
    virtual void _vf95();                                                          // 0x2f8
    virtual bool is_ottotto();                                                     // 0x300
    virtual bool is_ottotto_lr();                                                  // 0x308
    virtual bool is_myground_nearcliff();                                          // 0x310
    virtual bool is_near_cliff();                                                  // 0x318
    virtual bool is_miss_foot();                                                   // 0x320

    // Shape (offsets 0x328–0x398)
    virtual void _vf101();                                                         // 0x328
    virtual void _vf102();                                                         // 0x330
    virtual void set_shape_flag(u64 p1, bool p2);                                  // 0x338
    virtual void _vf104();                                                         // 0x340
    virtual void set_shape_safe_pos(u64 p1);                                       // 0x348
    virtual void _vf106();                                                         // 0x350
    virtual void* get_shape_safe_pos();                                            // 0x358
    virtual void set_status_ground();                                              // 0x360
    virtual void set_shape_kind(u64 p1);                                           // 0x368
    virtual void set_init_shape_kind();                                            // 0x370
    virtual u32 get_shape_kind();                                                  // 0x378
    virtual void set_z();                                                          // 0x380
    virtual f32 get_z();                                                           // 0x388
    virtual void _vf114();                                                         // 0x390
    virtual void* attach_ground(bool p1);                                          // 0x398

    // Attachment (offsets 0x3a0–0x3e8)
    virtual void _vf116();                                                         // 0x3a0
    virtual void set_attach_ground(bool p1);                                       // 0x3a8
    virtual bool is_attachable(u64 p1);                                            // 0x3b0
    virtual void attach(u64 p1);                                                   // 0x3b8
    virtual void _vf120();                                                         // 0x3c0
    virtual bool is_attach();                                                      // 0x3c8
    virtual void* get_line_movement_speed(void* p1);                               // 0x3d0
    virtual void _vf123();                                                         // 0x3d8
    virtual void _vf124();                                                         // 0x3e0
    virtual void detach(u64 p1);                                                   // 0x3e8

    // Touch / Normal (offsets 0x3f0–0x480)
    virtual void _vf126();                                                         // 0x3f0
    virtual void _vf127();                                                         // 0x3f8
    virtual void* test();                                                          // 0x400
    virtual void* get_touch_normal(u64 p1);                                        // 0x408
    virtual void* get_touch_normal_x(u64 p1);                                      // 0x410
    virtual void* get_touch_normal_y(u64 p1);                                      // 0x418
    virtual void* get_touch_normal_consider_gravity(u64 p1);                       // 0x420
    virtual void _vf133();                                                         // 0x428
    virtual void* get_touch_normal_x_consider_gravity(u64 p1);                     // 0x430
    virtual void* get_touch_normal_y_consider_gravity(u64 p1);                     // 0x438
    virtual void* get_touch_normal_fixed_consider_gravity(u64 p1);                 // 0x440
    virtual void* get_touch_normal_for_touch_attack_data(u64 p1);                  // 0x448
    virtual void _vf138();                                                         // 0x450
    virtual u32 ground_touch_flag();                                               // 0x458
    virtual void* ground_touch_flag_ex(bool p1, bool p2);                          // 0x460
    virtual u32 get_touch_flag();                                                  // 0x468
    virtual u32 get_touch_moment_flag();                                           // 0x470
    virtual u32 get_touch_material_type(u64 p1);                                   // 0x478
    virtual void* get_touch_pos();                                                 // 0x480

    // Touch detection (offsets 0x488–0x518)
    virtual void _vf145();                                                         // 0x488
    virtual void _vf146();                                                         // 0x490
    virtual void _vf147();                                                         // 0x498
    virtual bool is_touch(u64 p1);                                                 // 0x4a0
    virtual void _vf149();                                                         // 0x4a8
    virtual void _vf150();                                                         // 0x4b0
    virtual void _vf151();                                                         // 0x4b8
    virtual void _vf152();                                                         // 0x4c0
    virtual void _vf153();                                                         // 0x4c8
    virtual void _vf154();                                                         // 0x4d0
    virtual void* get_touch_line_raw(u64 p1);                                      // 0x4d8
    virtual void* get_touch_wall_cliff_pos(u64 p1, u64 p2);                        // 0x4e0
    virtual bool is_floor_touch_line(u64 p1);                                      // 0x4e8
    virtual bool is_wall_touch_line(u64 p1);                                       // 0x4f0
    virtual bool is_passable_ground();                                             // 0x4f8

    // Floor / Vanishing (offsets 0x500–0x568)
    virtual void _vf160();                                                         // 0x500
    virtual void _vf161();                                                         // 0x508
    virtual void _vf162();                                                         // 0x510
    virtual bool is_floor_vanishing();                                             // 0x518
    virtual void _vf164();                                                         // 0x520
    virtual void _vf165();                                                         // 0x528
    virtual void _vf166();                                                         // 0x530
    virtual void _vf167();                                                         // 0x538
    virtual void _vf168();                                                         // 0x540
    virtual void _vf169();                                                         // 0x548
    virtual void _vf170();                                                         // 0x550
    virtual void _vf171();                                                         // 0x558
    virtual void _vf172();                                                         // 0x560
    virtual u32 get_cliff_id_uint32();                                             // 0x568

    // Positions (offsets 0x570–0x5c8)
    virtual void _vf174();                                                         // 0x570
    virtual void* get_up_pos();                                                    // 0x578
    virtual void* get_down_pos();                                                  // 0x580
    virtual void* get_left_pos();                                                  // 0x588
    virtual void* get_right_pos();                                                 // 0x590
    virtual void* get_center_pos();                                                // 0x598
    virtual void* center_pos();                                                    // 0x5a0
    virtual f32 get_width();                                                       // 0x5a8
    virtual void* get_down_movement_speed();                                       // 0x5b0
    virtual void _vf183();                                                         // 0x5b8
    virtual void* check_down_correct_pos();                                        // 0x5c0
    virtual void* get_latest_down_correct_pos();                                   // 0x5c8

    // Down / Distance (offsets 0x5d0–0x610)
    virtual void _vf186();                                                         // 0x5d0
    virtual void _vf187();                                                         // 0x5d8
    virtual void _vf188();                                                         // 0x5e0
    virtual void _vf189();                                                         // 0x5e8
    virtual void* get_down_correct_edge_pos(u64 p1, u64 p2);                       // 0x5f0
    virtual f32 get_down_friction();                                               // 0x5f8
    virtual void get_distance_to_floor(u64 p1, bool p2);                           // 0x600
    virtual void is_still_on_floor(bool p1);                                       // 0x608
    virtual void _vf194();                                                         // 0x610

    // Ray check (offsets 0x618��0x6b8)
    virtual void ray_check(u64 p1, u64 p2, bool p3);                              // 0x618
    virtual void* ray_check_hit_pos(u64 p1, u64 p2, u64 p3, bool p4);             // 0x620
    virtual void* ray_check_hit_normal(u64 p1, u64 p2, u64 p3, bool p4);          // 0x628
    virtual void* ray_check_hit_pos_normal(u64 p1, u64 p2, u64 p3, u64 p4, bool p5);       // 0x630
    virtual void* ray_check_hit_pos_normal_no_culling(u64 p1, u64 p2, u64 p3, u64 p4, bool p5); // 0x638
    virtual void* ray_check_hit_pos_target(u64 p1, u64 p2, u64 p3, u64 p4, bool p5);       // 0x640
    virtual bool ray_check_get_line(u64 p1, u64 p2, bool p3);                     // 0x648
    virtual bool ray_check_get_line_no_culling(u64 p1, u64 p2, bool p3);          // 0x650
    virtual void* ray_check_get_line_hit_pos(u64 p1, u64 p2, u64 p3, bool p4);    // 0x658
    virtual void _vf204();                                                         // 0x660
    virtual void* ray_check_get_line_hit_pos_no_culling(u64 p1, u64 p2, u64 p3, bool p4);   // 0x668
    virtual void* ray_check_get_line_target_any(u64 p1, u64 p2, u64 p3, bool p4);           // 0x670
    virtual void* ray_check_get_line_target_any_no_culling(u64 p1, u64 p2, u64 p3, bool p4);// 0x678
    virtual void* ray_check_get_line_ignore_any(u64 p1, u64 p2, u64 p3);          // 0x680
    virtual void* ray_check_get_line_ignore_any_no_culling(u64 p1, u64 p2, u64 p3);         // 0x688
    virtual void* ray_check_get_line_hit_pos_ignore_any(u64 p1, u64 p2, u64 p3, u64 p4);   // 0x690
    virtual void* ray_check_get_line_hit_pos_ignore_any_no_culling(u64 p1, u64 p2, u64 p3, u64 p4); // 0x698
    virtual void* ray_check_get_line_hit_pos_target_any(u64 p1, u64 p2, u64 p3, u64 p4, bool p5);  // 0x6a0
    virtual void* line_segment_check(u64 p1, u64 p2, u64 p3, u64 p4, bool p5);    // 0x6a8
    virtual void _vf214();                                                         // 0x6b0
    virtual void* test_ground();                                                   // 0x6b8

    // Friction / Correct pos (offsets 0x6c0–0x6e0)
    virtual void set_ignore_friction(bool p1);                                     // 0x6c0
    virtual void* get_correct_pos();                                               // 0x6c8
    virtual void set_correct_pos(u64 p1);                                          // 0x6d0
    virtual void* get_correct_pos_local();                                         // 0x6d8
    virtual void set_update_shape(bool p1);                                        // 0x6e0

    // Unknown / Cliff attachment (offsets 0x6e8–0x750)
    virtual void _vf221();                                                         // 0x6e8
    virtual void _vf222();                                                         // 0x6f0
    virtual void _vf223();                                                         // 0x6f8
    virtual void _vf224();                                                         // 0x700
    virtual void _vf225();                                                         // 0x708
    virtual bool is_attach_cliff();                                                // 0x710
    virtual void _vf227();                                                         // 0x718
    virtual void _vf228();                                                         // 0x720
    virtual void* pass_floor();                                                    // 0x728
    virtual void clear_pass_floor();                                               // 0x730
    virtual void _vf231();                                                         // 0x738
    virtual void _vf232();                                                         // 0x740
    virtual void _vf233();                                                         // 0x748
    virtual void set_auto_detach(bool p1);                                         // 0x750

    // Unknown (offsets 0x758–0x7a0)
    virtual void _vf235();                                                         // 0x758
    virtual void _vf236();                                                         // 0x760
    virtual void _vf237();                                                         // 0x768
    virtual void _vf238();                                                         // 0x770
    virtual void _vf239();                                                         // 0x778
    virtual void _vf240();                                                         // 0x780
    virtual void set_no_cliff_stop_energy(u64 p1);                                 // 0x788
    virtual void _vf242();                                                         // 0x790
    virtual void* ignore_recovery();                                               // 0x798
    virtual void enable_recovery();                                                // 0x7a0

    // Collision mode / Rhombus (offsets 0x7a8–0x818)
    virtual void set_gr_collision_mode(bool p1);                                   // 0x7a8
    virtual void* get_shape_data_rhombus_modify_node_offset(u64 p1);               // 0x7b0
    virtual void update_lr();                                                      // 0x7b8
    virtual void set_shape_data_rhombus_modify_node_offset(u64 p1, u64 p2);        // 0x7c0
    virtual void _vf249();                                                         // 0x7c8
    virtual void set_keep_distant_cliff(bool p1);                                  // 0x7d0
    virtual void set_reverse_direction(bool p1, bool p2);                          // 0x7d8
    virtual void _vf252();                                                         // 0x7e0
    virtual void _vf253();                                                         // 0x7e8
    virtual void _vf254();                                                         // 0x7f0
    virtual void set_rhombus_modify_air_lasso(bool p1);                            // 0x7f8
    virtual void set_rhombus_modify(u64 p1);                                       // 0x800
    virtual void _vf257();                                                         // 0x808
    virtual void _vf258();                                                         // 0x810
    virtual void set_is_ignore_geometry_move_power(bool p1);                       // 0x818
};

} // namespace app
