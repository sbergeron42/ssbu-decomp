#pragma once

#include "types.h"

namespace app {

// Forward declaration — KineticEnergy is returned by KineticModule::get_energy
struct KineticEnergy;

// KineticModule — accessed at BattleObjectModuleAccessor+0x68
// Handles kinetic energy systems: speed, acceleration, friction, and energy slots.
// Vtable layout recovered from 29 .dynsym lua_bind::KineticModule__*_impl dispatchers.
// All named methods confirmed by decompiling _impl functions and verifying vtable offsets.
struct KineticModule {
    // Base class entries (offsets 0x00–0x58)
    virtual ~KineticModule();                                              // 0x00, 0x08
    virtual void _vf2();                                                   // 0x10
    virtual void _vf3();                                                   // 0x18
    virtual void _vf4();                                                   // 0x20
    virtual void _vf5();                                                   // 0x28
    virtual void _vf6();                                                   // 0x30
    virtual void _vf7();                                                   // 0x38
    virtual void _vf8();                                                   // 0x40
    virtual void _vf9();                                                   // 0x48
    virtual void _vf10();                                                  // 0x50
    virtual void _vf11();                                                  // 0x58

    // Energy access (offset 0x60)
    // [derived: KineticModule__get_energy_impl at 0x7102043970 dispatches to vtable+0x60]
    virtual KineticEnergy* get_energy(int index);                          // 0x60

    // Unknown (offsets 0x68–0x88)
    virtual void _vf13();                                                  // 0x68
    virtual void _vf14();                                                  // 0x70
    virtual void _vf15();                                                  // 0x78
    virtual void _vf16();                                                  // 0x80
    virtual void _vf17();                                                  // 0x88

    // Speed control (offsets 0x90–0xA0)
    // [derived: KineticModule__clear_speed_all_impl at 0x7102043990 dispatches to vtable+0x90]
    virtual void clear_speed_all();                                        // 0x90
    // [derived: KineticModule__clear_speed_energy_id_impl at 0x71020439a0 dispatches to vtable+0x98]
    virtual void clear_speed_energy_id(int id);                            // 0x98
    // [derived: KineticModule__clear_speed_attr_impl at 0x71020439b0 dispatches to vtable+0xA0]
    virtual void clear_speed_attr(u64 attr);                               // 0xA0

    // Energy suspend/resume (offsets 0xA8–0xB8)
    // [derived: KineticModule__suspend_energy_all_impl at 0x71020439c0 dispatches to vtable+0xA8]
    virtual void suspend_energy_all();                                     // 0xA8
    // [derived: KineticModule__resume_energy_all_impl at 0x71020439d0 dispatches to vtable+0xB0]
    virtual void resume_energy_all();                                      // 0xB0
    // [derived: KineticModule__unable_energy_all_impl at 0x71020439e0 dispatches to vtable+0xB8]
    virtual void unable_energy_all();                                      // 0xB8

    // Sum speed queries (offsets 0xC0–0xE0)
    // [derived: KineticModule__get_sum_speed_impl at 0x71020439f0 dispatches to vtable+0xC0]
    virtual void* get_sum_speed(void* out);                                // 0xC0
    // [derived: KineticModule__get_sum_speed_x_impl at 0x7102043a00 dispatches to vtable+0xC8]
    virtual void* get_sum_speed_x(void* out);                              // 0xC8
    // [derived: KineticModule__get_sum_speed_y_impl at 0x7102043a10 dispatches to vtable+0xD0]
    virtual void* get_sum_speed_y(void* out);                              // 0xD0
    // [derived: KineticModule__get_sum_speed_length_impl at 0x7102043a20 dispatches to vtable+0xD8]
    virtual void* get_sum_speed_length(void* out);                         // 0xD8
    // [derived: KineticModule__get_sum_speed3f_impl at 0x7102043a30 dispatches to vtable+0xE0]
    virtual void* get_sum_speed3f(void* out);                              // 0xE0

    // Rotation / friction (offsets 0xE8–0xF0)
    // [derived: KineticModule__get_sum_rotation_impl at 0x7102043a40 dispatches to vtable+0xE8]
    virtual void get_sum_rotation(u64 p1);                                 // 0xE8
    // [derived: KineticModule__set_consider_ground_friction_impl at 0x7102043a50 dispatches to vtable+0xF0]
    virtual void set_consider_ground_friction(bool enable, int id);        // 0xF0

    // Speed/accel transforms (offsets 0xF8–0x110)
    // [derived: KineticModule__mul_speed_impl at 0x7102043a70 dispatches to vtable+0xF8]
    virtual void mul_speed(void* v, u64 p2);                               // 0xF8
    // [derived: KineticModule__mul_accel_impl at 0x7102043a80 dispatches to vtable+0x100]
    virtual void mul_accel(void* v, int id);                               // 0x100
    // [derived: KineticModule__reflect_speed_impl at 0x7102043a90 dispatches to vtable+0x108]
    virtual void reflect_speed(void* v, int id);                           // 0x108
    // [derived: KineticModule__reflect_accel_impl at 0x7102043aa0 dispatches to vtable+0x110]
    virtual void reflect_accel(void* v, int id);                           // 0x110

    // Kinetic type (offsets 0x118–0x120)
    // [derived: KineticModule__change_kinetic_impl at 0x7102043ab0 dispatches to vtable+0x118]
    virtual void change_kinetic(int kind);                                 // 0x118
    // [derived: KineticModule__get_kinetic_type_impl at 0x7102043ac0 dispatches to vtable+0x120]
    virtual int get_kinetic_type();                                        // 0x120

    // Per-energy enable/suspend (offsets 0x128–0x150)
    // [derived: KineticModule__enable_energy_impl at 0x7102043ad0 dispatches to vtable+0x128]
    virtual void enable_energy(int id);                                    // 0x128
    // [derived: KineticModule__unable_energy_impl at 0x7102043ae0 dispatches to vtable+0x130]
    virtual void unable_energy(int id);                                    // 0x130
    // [derived: KineticModule__is_enable_energy_impl at 0x7102043af0 dispatches to vtable+0x138]
    virtual bool is_enable_energy(int id);                                 // 0x138
    // [derived: KineticModule__suspend_energy_impl at 0x7102043b00 dispatches to vtable+0x140]
    virtual void suspend_energy(int id);                                   // 0x140
    // [derived: KineticModule__resume_energy_impl at 0x7102043b10 dispatches to vtable+0x148]
    virtual void resume_energy(int id);                                    // 0x148
    // [derived: KineticModule__is_suspend_energy_impl at 0x7102043b20 dispatches to vtable+0x150]
    virtual bool is_suspend_energy(int id);                                // 0x150

    // Speed addition / sleep (offsets 0x158–0x168)
    // [derived: KineticModule__add_speed_impl at 0x7102043b30 dispatches to vtable+0x158]
    virtual void add_speed(void* v);                                       // 0x158
    // [derived: KineticModule__add_speed_outside_impl at 0x7102043b40 dispatches to vtable+0x160]
    virtual void add_speed_outside(void* v, u64 p2);                       // 0x160
    // [derived: KineticModule__sleep_impl at 0x7102043b50 dispatches to vtable+0x168]
    virtual void sleep(bool enable);                                       // 0x168
};

// KineticEnergy — individual energy slot returned by KineticModule::get_energy(int)
// Polymorphic object with vtable for speed/acceleration operations.
// Vtable layout recovered from 17 .dynsym lua_bind::KineticEnergy__*_impl dispatchers.
// Data fields confirmed by enable_impl/unable_impl/is_enable_impl direct struct access.
struct KineticEnergy {
    // Vtable entries (offsets 0x00–0x80)
    virtual ~KineticEnergy();                                              // 0x00, 0x08
    virtual void _vf2();                                                   // 0x10
    virtual void _vf3();                                                   // 0x18
    // [derived: KineticEnergy__get_speed_impl at 0x71020f6430 dispatches to vtable+0x20]
    virtual void* get_speed();                                             // 0x20
    virtual void _vf5();                                                   // 0x28
    virtual void _vf6();                                                   // 0x30
    virtual void _vf7();                                                   // 0x38
    // [derived: KineticEnergy__reset_energy_impl at 0x71020f64d0 dispatches to vtable+0x40]
    virtual void reset_energy(int kind);                                   // 0x40
    // [derived: KineticEnergy__clear_speed_impl at 0x71020f64e0 dispatches to vtable+0x48]
    virtual void clear_speed();                                            // 0x48
    // [derived: KineticEnergy__clear_rot_speed_impl at 0x71020f64f0 dispatches to vtable+0x50]
    virtual void clear_rot_speed();                                        // 0x50
    // [derived: KineticEnergy__mul_speed_impl at 0x71020f6500 dispatches to vtable+0x58]
    virtual void mul_speed(void* v);                                       // 0x58
    // [derived: KineticEnergy__mul_accel_impl at 0x71020f6510 dispatches to vtable+0x60]
    virtual void mul_accel(void* v);                                       // 0x60
    // [derived: KineticEnergy__reflect_speed_impl at 0x71020f6520 dispatches to vtable+0x68]
    virtual void reflect_speed(void* v);                                   // 0x68
    // [derived: KineticEnergy__reflect_accel_impl at 0x71020f6530 dispatches to vtable+0x70]
    virtual void reflect_accel(void* v);                                   // 0x70
    // [derived: KineticEnergy__on_consider_ground_friction_impl at 0x71020f6540 dispatches to vtable+0x78]
    virtual void on_consider_ground_friction();                            // 0x78
    // [derived: KineticEnergy__off_consider_ground_friction_impl at 0x71020f6550 dispatches to vtable+0x80]
    virtual void off_consider_ground_friction();                           // 0x80

    // Data fields
    u8 _unk_0x08[0x18];       // +0x08 to +0x1F (unknown)
    u8 _rotation[0x10];       // +0x20 [derived: KineticEnergy__get_rotation_impl at 0x71020f64c0 returns &this+0x20]
    u8 enabled;               // +0x30 [derived: enable_impl writes 1, unable_impl writes 0, is_enable_impl reads]
    u8 field_0x31_u8;         // +0x31 [inferred: set/cleared alongside enabled in 40+ lua_bind functions]
    u8 _unk_0x32[0x0E];       // +0x32 to +0x3F (unknown padding)

    // Speed/physics vectors — each is an {x, y} pair of f32
    // [derived: sv_kinetic_energy lua_bind readers at 0x7102222280-0x7102222400
    //  read these fields directly from KineticEnergy* returned by get_energy()]
    f32 accel_x;              // +0x40 [derived: FUN_7102222280 (get_energy3_accel_xy) reads +0x40]
    f32 accel_y;              // +0x44 [derived: FUN_7102222280 reads +0x44]
    u8 _unk_0x48[0x08];       // +0x48 to +0x4F (unknown)
    f32 brake_x;              // +0x50 [derived: FUN_7102222300 (get_energy3_brake_xy) reads +0x50]
    f32 brake_y;              // +0x54 [derived: FUN_7102222300 reads +0x54]
    u8 _unk_0x58[0x08];       // +0x58 to +0x5F (unknown)
    f32 stable_speed_x;       // +0x60 [derived: FUN_7102222380 (get_energy3_stable_speed_xy) reads +0x60]
    f32 stable_speed_y;       // +0x64 [derived: FUN_7102222380 reads +0x64]
    u8 _unk_0x68[0x08];       // +0x68 to +0x6F (unknown)
    f32 limit_speed_x;        // +0x70 [derived: FUN_7102222400 (get_energy3_limit_speed_xy) reads +0x70]
    f32 limit_speed_y;        // +0x74 [derived: FUN_7102222400 reads +0x74]
};

} // namespace app
