#include "types.h"
#include "app/BattleObjectModuleAccessor.h"
#include "app/modules/KineticModule.h"
#include "app/modules/MotionModule.h"
#include "app/modules/PostureModule.h"
#include "app/modules/WorkModule.h"

using namespace app;

// Helper: get MotionModule* from item lua context
// Pattern: *(L-8) -> battle_object -> +0x1a0 -> accessor -> motion_module
// [derived: all app::item:: functions load battle object from lua_State-8,
//  then accessor at +0x1a0, then motion_module at accessor+0x88]
static inline MotionModule* item_motion(u8* L) {
    u8* obj = *reinterpret_cast<u8**>(L - 8);
    BattleObjectModuleAccessor* acc = *reinterpret_cast<BattleObjectModuleAccessor**>(obj + 0x1a0);
    return static_cast<MotionModule*>(acc->motion_module);
}

namespace app::FighterUtil {

// 0x710068e170 (72 bytes)
// Returns true if motion hash matches one of three hammer animations
// Hash values are Hash40 constants [derived: literal comparisons in binary]
bool is_hammer_motion(u64 hash) {
    u64 h = hash & 0xFFFFFFFFFF;
    return h == 0x101acf6ce8 || h == 0x1052425d86 || h == 0x10c092e91b;
}

// 0x71006946c0 (44 bytes)
// Returns true if fighter has a valid entry_id (WorkModule::get_int(0x10000000) != -1)
// [derived: work_module vtable[19] called with hash 0x10000000, compared to -1]
bool is_valid_entry_id(BattleObjectModuleAccessor* acc) {
    WorkModule* wm = static_cast<WorkModule*>(acc->work_module);
    return wm->get_int(0x10000000) != -1;
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
}

// 0x710068e160 (16 bytes)
// Returns true if status kind is in the hammer range (0xd9..0xdf)
// [derived: literal SUB #0xd9, CMP #7 in binary]
bool is_hammer_status(int kind) {
    return static_cast<u32>(kind - 0xd9) < 7;
}

} // namespace app::FighterUtil

namespace app::FighterSpecializer_Pickel {

// 0x7100f0a980 (48 bytes)
// Returns true if fighter has a tool equipped (WorkModule::get_int(0x100000cf) != -1)
// [derived: work_module vtable[19] called with hash 0x100000cf, compared to -1]
bool is_have_tool(BattleObjectModuleAccessor* acc) {
    WorkModule* wm = static_cast<WorkModule*>(acc->work_module);
    return wm->get_int(0x100000cf) != -1;
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
}

} // namespace app::FighterSpecializer_Pickel

namespace app::sv_fighter_util {

// 0x7102281bf0 (120 bytes)
// Returns Hash40 motion kind for attack_hi3 based on fighter kind and facing
// +0x198 on battle object is fighter_kind [derived: compared against 0x3c-0x3d range and 0x1c]
// Uses PostureModule::lr() to check facing direction
u64 get_attack_hi3_motion(u8* L) {
    u8* obj = *reinterpret_cast<u8**>(L - 8);
    int kind = *reinterpret_cast<int*>(obj + 0x198);
    u32 diff = static_cast<u32>(kind) - 0x3c;
    if (diff < 2) {
        return 0xc2500ccc8;  // [derived: literal Hash40 in binary]
    }
    if (kind == 0x1c) {
        BattleObjectModuleAccessor* acc = *reinterpret_cast<BattleObjectModuleAccessor**>(obj + 0x1a0);
        PostureModule* pm = static_cast<PostureModule*>(acc->posture_module);
        if (pm->lr() == -1.0f) {
            return 0xca808c13d;  // [derived: literal Hash40 in binary]
        }
    }
    return 0xacbfc42e6;  // [derived: literal Hash40 in binary — default attack_hi3 motion]
}

} // namespace app::sv_fighter_util

namespace app::item {

// 0x71015c44e0 (72 bytes)
// Adds a partial motion to an item
// Calls vtable[100] (add_motion_partial) — raw dispatch needed because actual
// vtable takes 3 floats (start_frame, rate, unk) but header exposes only 1
void change_partial_motion(u8* L, u64 slot, u64 hash) {
    MotionModule* m = item_motion(L);
    reinterpret_cast<void(*)(MotionModule*, u64, u64, f32, f32, f32, bool, bool, bool, bool, bool)>
        (m->_vt[100])(m, slot, hash, 0.0f, 1.0f, 0.0f, false, false, true, false, false);
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
}

// 0x71015c4530 (72 bytes)
// Same as change_partial_motion with skeletal blending flag set (p9=true)
void change_partial_motion_as_skeletal(u8* L, u64 slot, u64 hash) {
    MotionModule* m = item_motion(L);
    reinterpret_cast<void(*)(MotionModule*, u64, u64, f32, f32, f32, bool, bool, bool, bool, bool)>
        (m->_vt[100])(m, slot, hash, 0.0f, 1.0f, 0.0f, false, false, true, true, false);
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
}

// 0x71015c45e0 (44 bytes)
// Removes a partial motion from an item
// Calls MotionModule::remove_motion_partial (vtable[101]) with p2=false
void remove_partial_motion(u8* L, u64 slot) {
    MotionModule* m = item_motion(L);
    m->remove_motion_partial(slot, false);
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
}

// 0x71015c4580 (40 bytes)
// Sets the playback rate of an item's partial motion
// Calls MotionModule vtable[107] — float rate passes through s0 register implicitly
void set_partial_motion_rate(u8* L, u64 slot, f32 rate) {
    MotionModule* m = item_motion(L);
    m->set_rate_partial(slot);
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
}

// 0x71015c45b0 (44 bytes)
// Sets the current frame of an item's partial motion
// Calls MotionModule::set_frame_partial (vtable[111]) with sync=true
void set_partial_motion_frame(u8* L, u64 slot, f32 frame) {
    MotionModule* m = item_motion(L);
    m->set_frame_partial(slot, true);
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
}

} // namespace app::item

// Helper: get KineticModule* from lua context (item/boss pattern)
// [derived: all boss_private/item kinetic functions load battle object from lua_State-8,
//  then accessor at +0x1a0, then kinetic_module at accessor+0x68]
static inline KineticModule* item_kinetic(u8* L) {
    u8* obj = *reinterpret_cast<u8**>(L - 8);
    BattleObjectModuleAccessor* acc = *reinterpret_cast<BattleObjectModuleAccessor**>(obj + 0x1a0);
    return static_cast<KineticModule*>(acc->item_kinetic_module);
}

namespace app::boss_private {

// 0x71015c8390 (48 bytes)
// Disables main kinetic energy (slot 0xc) by clearing enabled flag
// [derived: get_energy vtable+0x60 with index 0xc, strb wzr at energy+0x30]
void unable_main_energy(u8* L) {
    KineticModule* km = item_kinetic(L);
    KineticEnergy* energy = km->get_energy(0xc);
    energy->enabled = 0;
}

// 0x71015c83c0 (48 bytes)
// Disables sub1 kinetic energy (slot 0xd) by clearing enabled flag
// [derived: get_energy vtable+0x60 with index 0xd, strb wzr at energy+0x30]
void unable_sub1_energy(u8* L) {
    KineticModule* km = item_kinetic(L);
    KineticEnergy* energy = km->get_energy(0xd);
    energy->enabled = 0;
}

// 0x71015c8280 (60 bytes)
// Sets angle on sub1 kinetic energy (slot 0xd) at energy+0xa4
// [derived: get_energy(0xd), str s8 at +0xa4 — callee-saved float across virtual call]
void set_sub1_energy_angle(u8* L, f32 angle) {
    KineticModule* km = item_kinetic(L);
    KineticEnergy* energy = km->get_energy(0xd);
    *reinterpret_cast<f32*>(reinterpret_cast<u8*>(energy) + 0xa4) = angle;
}

// 0x71015c82c0 (72 bytes)
// Clears sub1 kinetic energy (slot 0xd) — calls clear_speed then zeroes field at +0xa0
// [derived: get_energy(0xd) → vtable+0x48 (clear_speed), then str wzr at energy+0xa0]
void clear_sub1_energy(u8* L) {
    KineticModule* km = item_kinetic(L);
    KineticEnergy* energy = km->get_energy(0xd);
    energy->clear_speed();
    *reinterpret_cast<u32*>(reinterpret_cast<u8*>(energy) + 0xa0) = 0;
}

// 0x71015c8310 (116 bytes)
// Clears speed on both main (slot 0xc) and sub1 (slot 0xd) kinetic energies
// [derived: km saved in x19, get_energy(0xc) → x20, get_energy(0xd) → x19,
//  then clear_speed vtable+0x48 called on both]
void clear_energy_all(u8* L) {
    KineticModule* km = item_kinetic(L);
    KineticEnergy* e1 = km->get_energy(0xc);
    KineticEnergy* e2 = km->get_energy(0xd);
    e1->clear_speed();
    e2->clear_speed();
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
}

} // namespace app::boss_private

namespace app::kinetic_energy_damage {

// 0x71015d1ca0 (56 bytes)
// Returns true if damage energy (slot 8) has ground type == 0
// [derived: get_energy(8), ldr w8 at +0x88, cmp #0, cset eq]
bool is_ground_type_energy(u8* L) {
    KineticModule* km = item_kinetic(L);
    KineticEnergy* energy = km->get_energy(8);
    return *reinterpret_cast<int*>(reinterpret_cast<u8*>(energy) + 0x88) == 0;
}

} // namespace app::kinetic_energy_damage

namespace app::WeaponSpecializer_EFlameEsword {

// 0x71033f3630 (52 bytes)
// Sets angle on motion energy (slot 2) at energy+0x8c
// [derived: acc->item_kinetic_module vtable+0x60 get_energy(2), str s8 at +0x8c]
void energy_motion_set_angle(BattleObjectModuleAccessor* acc, f32 angle) {
    KineticModule* km = static_cast<KineticModule*>(acc->item_kinetic_module);
    KineticEnergy* energy = km->get_energy(2);
    *reinterpret_cast<f32*>(reinterpret_cast<u8*>(energy) + 0x8c) = angle;
}

} // namespace app::WeaponSpecializer_EFlameEsword

namespace app::WeaponSpecializer_ElementDiver {

// 0x71033f5630 (52 bytes)
// Sets speed multiplier on motion energy (slot 2) at energy+0x90
// [derived: acc->item_kinetic_module vtable+0x60 get_energy(2), str s8 at +0x90]
void set_energy_motion_speed_mul(BattleObjectModuleAccessor* acc, f32 mul) {
    KineticModule* km = static_cast<KineticModule*>(acc->item_kinetic_module);
    KineticEnergy* energy = km->get_energy(2);
    *reinterpret_cast<f32*>(reinterpret_cast<u8*>(energy) + 0x90) = mul;
}

} // namespace app::WeaponSpecializer_ElementDiver

namespace app::boss_private {

// 0x71015c83f0 (88 bytes)
// Disables both main (slot 0xc) and sub1 (slot 0xd) kinetic energies
// [derived: get_energy called twice on same KineticModule, km saved in x19,
//  first result in x20; both energy->enabled (at +0x30) set to 0]
void unable_energy_all(u8* L) {
    KineticModule* km = item_kinetic(L);
    KineticEnergy* e1 = km->get_energy(0xc);
    KineticEnergy* e2 = km->get_energy(0xd);
    e1->enabled = 0;
    e2->enabled = 0;
}

} // namespace app::boss_private

namespace app::kinetic_energy_outer {

// 0x71015d00f0 (60 bytes)
// Returns x speed from outer energy (slot 1)
// [derived: get_energy(1) → energy->get_speed() vtable+0x20, return *(f32*)speed]
f32 get_speed_x(u8* L) {
    KineticModule* km = item_kinetic(L);
    KineticEnergy* energy = km->get_energy(1);
    void* speed = energy->get_speed();
    return *reinterpret_cast<f32*>(speed);
}

// 0x71015d0130 (60 bytes)
// Returns y speed from outer energy (slot 1)
// [derived: get_energy(1) → energy->get_speed() vtable+0x20, return *(f32*)(speed+4)]
f32 get_speed_y(u8* L) {
    KineticModule* km = item_kinetic(L);
    KineticEnergy* energy = km->get_energy(1);
    void* speed = energy->get_speed();
    return *reinterpret_cast<f32*>(reinterpret_cast<u8*>(speed) + 4);
}

} // namespace app::kinetic_energy_outer

namespace app::kinetic_energy_gravity {

// 0x71015d0280 (60 bytes)
// Returns y speed from gravity energy (slot 2)
// [derived: get_energy(2) → get_speed(), return *(f32*)(speed+4)]
f32 get_speed_y(u8* L) {
    KineticModule* km = item_kinetic(L);
    KineticEnergy* energy = km->get_energy(2);
    void* speed = energy->get_speed();
    return *reinterpret_cast<f32*>(reinterpret_cast<u8*>(speed) + 4);
}

} // namespace app::kinetic_energy_gravity

namespace app::kinetic_energy_ground {

// 0x71015d03b0 (60 bytes)
// Returns y speed from ground energy (slot 3)
// [derived: get_energy(3) → get_speed(), return *(f32*)(speed+4)]
f32 get_speed_y(u8* L) {
    KineticModule* km = item_kinetic(L);
    KineticEnergy* energy = km->get_energy(3);
    void* speed = energy->get_speed();
    return *reinterpret_cast<f32*>(reinterpret_cast<u8*>(speed) + 4);
}

} // namespace app::kinetic_energy_ground

namespace app::kinetic_energy_control {

// 0x71015d0470 (60 bytes)
// Returns x speed from control energy (slot 4)
// [derived: get_energy(4) → get_speed(), return *(f32*)speed]
f32 get_speed_x(u8* L) {
    KineticModule* km = item_kinetic(L);
    KineticEnergy* energy = km->get_energy(4);
    void* speed = energy->get_speed();
    return *reinterpret_cast<f32*>(speed);
}

// 0x71015d04b0 (60 bytes)
// Returns y speed from control energy (slot 4)
// [derived: get_energy(4) → get_speed(), return *(f32*)(speed+4)]
f32 get_speed_y(u8* L) {
    KineticModule* km = item_kinetic(L);
    KineticEnergy* energy = km->get_energy(4);
    void* speed = energy->get_speed();
    return *reinterpret_cast<f32*>(reinterpret_cast<u8*>(speed) + 4);
}

} // namespace app::kinetic_energy_control

namespace app::kinetic_energy_motion {

// 0x71015d07f0 (60 bytes)
// Returns x speed from motion energy (slot 6)
// [derived: get_energy(6) → get_speed(), return *(f32*)speed]
f32 get_speed_x(u8* L) {
    KineticModule* km = item_kinetic(L);
    KineticEnergy* energy = km->get_energy(6);
    void* speed = energy->get_speed();
    return *reinterpret_cast<f32*>(speed);
}

// 0x71015d0830 (60 bytes)
// Returns y speed from motion energy (slot 6)
// [derived: get_energy(6) → get_speed(), return *(f32*)(speed+4)]
f32 get_speed_y(u8* L) {
    KineticModule* km = item_kinetic(L);
    KineticEnergy* energy = km->get_energy(6);
    void* speed = energy->get_speed();
    return *reinterpret_cast<f32*>(reinterpret_cast<u8*>(speed) + 4);
}

} // namespace app::kinetic_energy_motion

namespace app::kinetic_energy_stop {

// 0x71015d0900 (60 bytes)
// Returns x speed from stop energy (slot 7)
// [derived: get_energy(7) → get_speed(), return *(f32*)speed]
f32 get_speed_x(u8* L) {
    KineticModule* km = item_kinetic(L);
    KineticEnergy* energy = km->get_energy(7);
    void* speed = energy->get_speed();
    return *reinterpret_cast<f32*>(speed);
}

} // namespace app::kinetic_energy_stop

namespace app::kinetic_energy_damage {

// 0x71015d0be0 (60 bytes)
// Returns x speed from damage energy (slot 8)
// [derived: get_energy(8) → get_speed(), return *(f32*)speed]
f32 get_speed_x(u8* L) {
    KineticModule* km = item_kinetic(L);
    KineticEnergy* energy = km->get_energy(8);
    void* speed = energy->get_speed();
    return *reinterpret_cast<f32*>(speed);
}

} // namespace app::kinetic_energy_damage

namespace app::kinetic_energy_jostle {

// 0x71015d0a30 (60 bytes)
// Returns x speed from jostle energy (slot 9)
// [derived: get_energy(9) → get_speed(), return *(f32*)speed]
f32 get_speed_x(u8* L) {
    KineticModule* km = item_kinetic(L);
    KineticEnergy* energy = km->get_energy(9);
    void* speed = energy->get_speed();
    return *reinterpret_cast<f32*>(speed);
}

} // namespace app::kinetic_energy_jostle

namespace app::kinetic_energy_ground_movement {

// 0x71015d0b30 (60 bytes)
// Returns x speed from ground movement energy (slot 10)
// [derived: get_energy(0xa) → get_speed(), return *(f32*)speed]
f32 get_speed_x(u8* L) {
    KineticModule* km = item_kinetic(L);
    KineticEnergy* energy = km->get_energy(10);
    void* speed = energy->get_speed();
    return *reinterpret_cast<f32*>(speed);
}

} // namespace app::kinetic_energy_ground_movement

namespace app::kinetic_energy_motion_linked_main {

// 0x71015d0cc0 (60 bytes)
// Returns x speed from motion-linked main energy (slot 0xc)
// [derived: get_energy(0xc) → get_speed(), return *(f32*)speed]
f32 get_speed_x(u8* L) {
    KineticModule* km = item_kinetic(L);
    KineticEnergy* energy = km->get_energy(0xc);
    void* speed = energy->get_speed();
    return *reinterpret_cast<f32*>(speed);
}

// 0x71015d0d00 (60 bytes)
// Returns y speed from motion-linked main energy (slot 0xc)
// [derived: get_energy(0xc) → get_speed(), return *(f32*)(speed+4)]
f32 get_speed_y(u8* L) {
    KineticModule* km = item_kinetic(L);
    KineticEnergy* energy = km->get_energy(0xc);
    void* speed = energy->get_speed();
    return *reinterpret_cast<f32*>(reinterpret_cast<u8*>(speed) + 4);
}

} // namespace app::kinetic_energy_motion_linked_main

namespace app::kinetic_energy_motion_linked_sub1 {

// 0x71015d0e00 (60 bytes)
// Returns x speed from motion-linked sub1 energy (slot 0xd)
// [derived: get_energy(0xd) → get_speed(), return *(f32*)speed]
f32 get_speed_x(u8* L) {
    KineticModule* km = item_kinetic(L);
    KineticEnergy* energy = km->get_energy(0xd);
    void* speed = energy->get_speed();
    return *reinterpret_cast<f32*>(speed);
}

// 0x71015d0e40 (60 bytes)
// Returns y speed from motion-linked sub1 energy (slot 0xd)
// [derived: get_energy(0xd) → get_speed(), return *(f32*)(speed+4)]
f32 get_speed_y(u8* L) {
    KineticModule* km = item_kinetic(L);
    KineticEnergy* energy = km->get_energy(0xd);
    void* speed = energy->get_speed();
    return *reinterpret_cast<f32*>(reinterpret_cast<u8*>(speed) + 4);
}

} // namespace app::kinetic_energy_motion_linked_sub1

namespace app::kinetic_energy_stop {

// 0x71015d0a00 (48 bytes)
// Returns whether stop energy (slot 7) is enabled
// [derived: get_energy(7), return *(u8*)(energy+0x30) — the enabled field]
u8 is_enable(u8* L) {
    KineticModule* km = item_kinetic(L);
    KineticEnergy* energy = km->get_energy(7);
    return energy->enabled;
}

} // namespace app::kinetic_energy_stop

namespace app::kinetic_energy_motion_linked_sub1 {

// 0x71015d0ef0 (48 bytes)
// Returns whether motion-linked sub1 energy (slot 0xd) is enabled
// [derived: get_energy(0xd), return *(u8*)(energy+0x30)]
u8 is_enable(u8* L) {
    KineticModule* km = item_kinetic(L);
    KineticEnergy* energy = km->get_energy(0xd);
    return energy->enabled;
}

} // namespace app::kinetic_energy_motion_linked_sub1

namespace app::kinetic_energy_control_rot {

// 0x71015d0730 (52 bytes)
// Suspends control rot energy (slot 5) by setting field_0x31 to 1
// [derived: get_energy(5), strb #1 at energy+0x31]
void suspend(u8* L) {
    KineticModule* km = item_kinetic(L);
    KineticEnergy* energy = km->get_energy(5);
    energy->field_0x31_u8 = 1;
}

// 0x71015d0770 (48 bytes)
// Resumes control rot energy (slot 5) by clearing field_0x31
// [derived: get_energy(5), strb #0 at energy+0x31]
void resume(u8* L) {
    KineticModule* km = item_kinetic(L);
    KineticEnergy* energy = km->get_energy(5);
    energy->field_0x31_u8 = 0;
}

// 0x71015d1140 (48 bytes)
// Returns pointer to rotation data of control rot energy (slot 5)
// [derived: get_energy(5), return energy+0x20 — the _rotation field]
void* get_rotation(u8* L) {
    KineticModule* km = item_kinetic(L);
    KineticEnergy* energy = km->get_energy(5);
    return energy->_rotation;
}

} // namespace app::kinetic_energy_control_rot

namespace app::kinetic_energy_outer {

// 0x71015d16f0 (48 bytes)
// Returns pointer to accel data of outer energy (slot 1) at energy+0x40
// [derived: get_energy(1), return energy+0x40]
void* get_accel(u8* L) {
    KineticModule* km = item_kinetic(L);
    KineticEnergy* energy = km->get_energy(1);
    return reinterpret_cast<u8*>(energy) + 0x40;
}

// 0x71015d1720 (48 bytes)
// Returns pointer to limit speed data of outer energy (slot 1) at energy+0x70
// [derived: get_energy(1), return energy+0x70]
void* get_limit_speed(u8* L) {
    KineticModule* km = item_kinetic(L);
    KineticEnergy* energy = km->get_energy(1);
    return reinterpret_cast<u8*>(energy) + 0x70;
}

} // namespace app::kinetic_energy_outer

namespace app::kinetic_energy_control_rot {

// 0x71015d1170 (56 bytes)
// Clears rotation speed on control rot energy (slot 5)
// [derived: get_energy(5) → energy->clear_rot_speed() vtable+0x50]
void clear_rot_speed(u8* L) {
    KineticModule* km = item_kinetic(L);
    KineticEnergy* energy = km->get_energy(5);
    energy->clear_rot_speed();
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
}

} // namespace app::kinetic_energy_control_rot

namespace app::kinetic_energy_gravity {

// 0x71015d1af0 (48 bytes)
// Returns accel value from gravity energy (slot 2) at energy+0x34
// [derived: get_energy(2), return *(f32*)(energy+0x34)]
f32 get_accel(u8* L) {
    KineticModule* km = item_kinetic(L);
    KineticEnergy* energy = km->get_energy(2);
    return *reinterpret_cast<f32*>(reinterpret_cast<u8*>(energy) + 0x34);
}

// 0x71015d1b20 (48 bytes)
// Returns limit speed from gravity energy (slot 2) at energy+0x40
// [derived: get_energy(2), return *(f32*)(energy+0x40)]
f32 get_limit_speed(u8* L) {
    KineticModule* km = item_kinetic(L);
    KineticEnergy* energy = km->get_energy(2);
    return *reinterpret_cast<f32*>(reinterpret_cast<u8*>(energy) + 0x40);
}

// 0x71015d1ba0 (60 bytes)
// Sets accel on gravity energy (slot 2) at energy+0x34
// [derived: get_energy(2), str s8 at energy+0x34]
void set_accel(u8* L, f32 val) {
    KineticModule* km = item_kinetic(L);
    KineticEnergy* energy = km->get_energy(2);
    *reinterpret_cast<f32*>(reinterpret_cast<u8*>(energy) + 0x34) = val;
}

// 0x71015d1be0 (60 bytes)
// Sets stable speed on gravity energy (slot 2) at energy+0x38
// [derived: get_energy(2), str s8 at energy+0x38]
void set_stable_speed(u8* L, f32 val) {
    KineticModule* km = item_kinetic(L);
    KineticEnergy* energy = km->get_energy(2);
    *reinterpret_cast<f32*>(reinterpret_cast<u8*>(energy) + 0x38) = val;
}

// 0x71015d1c20 (60 bytes)
// Sets brake on gravity energy (slot 2) at energy+0x3c
// [derived: get_energy(2), str s8 at energy+0x3c]
void set_brake(u8* L, f32 val) {
    KineticModule* km = item_kinetic(L);
    KineticEnergy* energy = km->get_energy(2);
    *reinterpret_cast<f32*>(reinterpret_cast<u8*>(energy) + 0x3c) = val;
}

// 0x71015d1c60 (60 bytes)
// Sets limit speed on gravity energy (slot 2) at energy+0x40
// [derived: get_energy(2), str s8 at energy+0x40]
void set_limit_speed(u8* L, f32 val) {
    KineticModule* km = item_kinetic(L);
    KineticEnergy* energy = km->get_energy(2);
    *reinterpret_cast<f32*>(reinterpret_cast<u8*>(energy) + 0x40) = val;
}

} // namespace app::kinetic_energy_gravity

namespace app::kinetic_energy_rot {

// 0x71015d0030 (52 bytes)
// Enables rot energy (slot 0) by setting enabled flag to 1
// [derived: get_energy(0), strb #1 at energy+0x30]
void enable(u8* L) {
    KineticModule* km = item_kinetic(L);
    KineticEnergy* energy = km->get_energy(0);
    energy->enabled = 1;
}

// 0x71015d0070 (48 bytes)
// Disables rot energy (slot 0) by clearing enabled flag
// [derived: get_energy(0), strb wzr at energy+0x30]
void unable(u8* L) {
    KineticModule* km = item_kinetic(L);
    KineticEnergy* energy = km->get_energy(0);
    energy->enabled = 0;
}

// 0x71015d10d0 (48 bytes)
// Returns pointer to rotation data of rot energy (slot 0)
// [derived: get_energy(0), return energy+0x20 — the _rotation field]
void* get_rotation(u8* L) {
    KineticModule* km = item_kinetic(L);
    KineticEnergy* energy = km->get_energy(0);
    return energy->_rotation;
}

// 0x71015d1100 (56 bytes)
// Clears rotation speed on rot energy (slot 0)
// [derived: get_energy(0) → energy->clear_rot_speed() vtable+0x50]
void clear_rot_speed(u8* L) {
    KineticModule* km = item_kinetic(L);
    KineticEnergy* energy = km->get_energy(0);
    energy->clear_rot_speed();
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
}

} // namespace app::kinetic_energy_rot

namespace app::kinetic_energy_outer {

// 0x71015d0f20 (56 bytes)
// Clears speed on outer energy (slot 1)
// [derived: get_energy(1) → energy->clear_speed() vtable+0x48]
void clear_speed(u8* L) {
    KineticModule* km = item_kinetic(L);
    KineticEnergy* energy = km->get_energy(1);
    energy->clear_speed();
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
}

} // namespace app::kinetic_energy_outer

namespace app::kinetic_energy_gravity {

// 0x71015d0380 (48 bytes)
// Returns whether gravity energy (slot 2) is enabled
// [derived: get_energy(2), return *(u8*)(energy+0x30)]
u8 is_enable(u8* L) {
    KineticModule* km = item_kinetic(L);
    KineticEnergy* energy = km->get_energy(2);
    return energy->enabled;
}

} // namespace app::kinetic_energy_gravity

namespace app::kinetic_energy_outer {

// 0x71015d0170 (72 bytes)
// Multiplies speed on outer energy (slot 1) by vector
// [derived: get_energy(1) → energy->mul_speed(vec) vtable+0x58]
void mul_speed(u8* L, void* vec) {
    KineticModule* km = item_kinetic(L);
    KineticEnergy* energy = km->get_energy(1);
    energy->mul_speed(vec);
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
}

// 0x71015d01c0 (52 bytes)
// Enables outer energy (slot 1) by setting enabled flag to 1
// [derived: get_energy(1), strb #1 at energy+0x30]
void enable(u8* L) {
    KineticModule* km = item_kinetic(L);
    KineticEnergy* energy = km->get_energy(1);
    energy->enabled = 1;
}

// 0x71015d0200 (48 bytes)
// Disables outer energy (slot 1) by clearing enabled flag
// [derived: get_energy(1), strb wzr at energy+0x30]
void unable(u8* L) {
    KineticModule* km = item_kinetic(L);
    KineticEnergy* energy = km->get_energy(1);
    energy->enabled = 0;
}

} // namespace app::kinetic_energy_outer

namespace app::kinetic_energy_gravity {

// 0x71015d02c0 (72 bytes)
// Multiplies speed on gravity energy (slot 2) by vector
// [derived: get_energy(2) → energy->mul_speed(vec) vtable+0x58]
void mul_speed(u8* L, void* vec) {
    KineticModule* km = item_kinetic(L);
    KineticEnergy* energy = km->get_energy(2);
    energy->mul_speed(vec);
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
}

// 0x71015d0310 (52 bytes)
// Enables gravity energy (slot 2) by setting enabled flag to 1
// [derived: get_energy(2), strb #1 at energy+0x30]
void enable(u8* L) {
    KineticModule* km = item_kinetic(L);
    KineticEnergy* energy = km->get_energy(2);
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
    energy->enabled = 1;
}

// 0x71015d0350 (48 bytes)
// Disables gravity energy (slot 2) by clearing enabled flag
// [derived: get_energy(2), strb wzr at energy+0x30]
void unable(u8* L) {
    KineticModule* km = item_kinetic(L);
    KineticEnergy* energy = km->get_energy(2);
    energy->enabled = 0;
}

// 0x71015d0f60 (56 bytes)
// Clears speed on gravity energy (slot 2)
// [derived: get_energy(2) → energy->clear_speed() vtable+0x48]
void clear_speed(u8* L) {
    KineticModule* km = item_kinetic(L);
    KineticEnergy* energy = km->get_energy(2);
    energy->clear_speed();
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
}

} // namespace app::kinetic_energy_gravity

namespace app::kinetic_energy_ground {

// 0x71015d03f0 (48 bytes)
// Disables ground energy (slot 3) by clearing enabled flag
// [derived: get_energy(3), strb wzr at energy+0x30]
void unable(u8* L) {
    KineticModule* km = item_kinetic(L);
    KineticEnergy* energy = km->get_energy(3);
    energy->enabled = 0;
}

} // namespace app::kinetic_energy_ground

namespace app::kinetic_energy_control {

// 0x71015d04f0 (72 bytes)
// Multiplies speed on control energy (slot 4) by vector
// [derived: get_energy(4) → energy->mul_speed(vec) vtable+0x58]
void mul_speed(u8* L, void* vec) {
    KineticModule* km = item_kinetic(L);
    KineticEnergy* energy = km->get_energy(4);
    energy->mul_speed(vec);
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
}

// 0x71015d0590 (52 bytes)
// Enables control energy (slot 4) by setting enabled flag to 1
// [derived: get_energy(4), strb #1 at energy+0x30]
void enable(u8* L) {
    KineticModule* km = item_kinetic(L);
    KineticEnergy* energy = km->get_energy(4);
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
    energy->enabled = 1;
}

// 0x71015d05d0 (48 bytes)
// Disables control energy (slot 4) by clearing enabled flag
// [derived: get_energy(4), strb wzr at energy+0x30]
void unable(u8* L) {
    KineticModule* km = item_kinetic(L);
    KineticEnergy* energy = km->get_energy(4);
    energy->enabled = 0;
}

// 0x71015d0fa0 (56 bytes)
// Clears speed on control energy (slot 4)
// [derived: get_energy(4) → energy->clear_speed() vtable+0x48]
void clear_speed(u8* L) {
    KineticModule* km = item_kinetic(L);
    KineticEnergy* energy = km->get_energy(4);
    energy->clear_speed();
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
}

// 0x71015d0600 (52 bytes)
// Suspends control energy (slot 4) by setting field_0x31 to 1
// [derived: get_energy(4), strb #1 at energy+0x31]
void suspend(u8* L) {
    KineticModule* km = item_kinetic(L);
    KineticEnergy* energy = km->get_energy(4);
    energy->field_0x31_u8 = 1;
}

// 0x71015d0640 (48 bytes)
// Resumes control energy (slot 4) by clearing field_0x31
// [derived: get_energy(4), strb #0 at energy+0x31]
void resume(u8* L) {
    KineticModule* km = item_kinetic(L);
    KineticEnergy* energy = km->get_energy(4);
    energy->field_0x31_u8 = 0;
}

// 0x71015d1200 (48 bytes)
// Returns pointer to accel data of control energy (slot 4) at energy+0x40
// [derived: get_energy(4), return energy+0x40]
void* get_accel(u8* L) {
    KineticModule* km = item_kinetic(L);
    KineticEnergy* energy = km->get_energy(4);
    return reinterpret_cast<u8*>(energy) + 0x40;
}

// 0x71015d1260 (48 bytes)
// Returns pointer to limit speed data of control energy (slot 4) at energy+0x70
// [derived: get_energy(4), return energy+0x70]
void* get_limit_speed(u8* L) {
    KineticModule* km = item_kinetic(L);
    KineticEnergy* energy = km->get_energy(4);
    return reinterpret_cast<u8*>(energy) + 0x70;
}

// 0x71015d1290 (64 bytes)
// Sets accel on control energy (slot 4) — copies 16 bytes from vec to energy+0x40
// [derived: get_energy(4), ldp/stp 16 bytes from x1 to energy+0x40]
void set_accel(u8* L, void* vec) {
    KineticModule* km = item_kinetic(L);
    KineticEnergy* energy = km->get_energy(4);
    __builtin_memcpy(reinterpret_cast<u8*>(energy) + 0x40, vec, 16);
}

// 0x71015d12d0 (64 bytes)
// Sets stable speed on control energy (slot 4) — copies 16 bytes from vec to energy+0x50
// [derived: get_energy(4), ldp/stp 16 bytes from x1 to energy+0x50]
void set_stable_speed(u8* L, void* vec) {
    KineticModule* km = item_kinetic(L);
    KineticEnergy* energy = km->get_energy(4);
    __builtin_memcpy(reinterpret_cast<u8*>(energy) + 0x50, vec, 16);
}

// 0x71015d1310 (64 bytes)
// Sets brake on control energy (slot 4) — copies 16 bytes from vec to energy+0x60
// [derived: get_energy(4), ldp/stp 16 bytes from x1 to energy+0x60]
void set_brake(u8* L, void* vec) {
    KineticModule* km = item_kinetic(L);
    KineticEnergy* energy = km->get_energy(4);
    __builtin_memcpy(reinterpret_cast<u8*>(energy) + 0x60, vec, 16);
}

// 0x71015d1350 (64 bytes)
// Sets limit speed on control energy (slot 4) — copies 16 bytes from vec to energy+0x70
// [derived: get_energy(4), ldp/stp 16 bytes from x1 to energy+0x70]
void set_limit_speed(u8* L, void* vec) {
    KineticModule* km = item_kinetic(L);
    KineticEnergy* energy = km->get_energy(4);
    __builtin_memcpy(reinterpret_cast<u8*>(energy) + 0x70, vec, 16);
}

} // namespace app::kinetic_energy_control

namespace app::kinetic_energy_control_rot {

// 0x71015d0670 (72 bytes)
// Multiplies speed on control rot energy (slot 5) by vector
// [derived: get_energy(5) → energy->mul_speed(vec) vtable+0x58]
void mul_speed(u8* L, void* vec) {
    KineticModule* km = item_kinetic(L);
    KineticEnergy* energy = km->get_energy(5);
    energy->mul_speed(vec);
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
}

// 0x71015d06c0 (52 bytes)
// Enables control rot energy (slot 5) by setting enabled flag to 1
// [derived: get_energy(5), strb #1 at energy+0x30]
void enable(u8* L) {
    KineticModule* km = item_kinetic(L);
    KineticEnergy* energy = km->get_energy(5);
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
    energy->enabled = 1;
}

// 0x71015d0700 (48 bytes)
// Disables control rot energy (slot 5) by clearing enabled flag
// [derived: get_energy(5), strb wzr at energy+0x30]
void unable(u8* L) {
    KineticModule* km = item_kinetic(L);
    KineticEnergy* energy = km->get_energy(5);
    energy->enabled = 0;
}

} // namespace app::kinetic_energy_control_rot

namespace app::kinetic_energy_motion {

// 0x71015d0870 (52 bytes)
// Enables motion energy (slot 6) by setting enabled flag to 1
// [derived: get_energy(6), strb #1 at energy+0x30]
void enable(u8* L) {
    KineticModule* km = item_kinetic(L);
    KineticEnergy* energy = km->get_energy(6);
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
    energy->enabled = 1;
}

// 0x71015d0fe0 (56 bytes)
// Clears speed on motion energy (slot 6)
// [derived: get_energy(6) → energy->clear_speed() vtable+0x48]
void clear_speed(u8* L) {
    KineticModule* km = item_kinetic(L);
    KineticEnergy* energy = km->get_energy(6);
    energy->clear_speed();
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
}

} // namespace app::kinetic_energy_motion

namespace app::kinetic_energy_stop {

// 0x71015d0990 (52 bytes)
// Enables stop energy (slot 7) by setting enabled flag to 1
// [derived: get_energy(7), strb #1 at energy+0x30]
void enable(u8* L) {
    KineticModule* km = item_kinetic(L);
    KineticEnergy* energy = km->get_energy(7);
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
    energy->enabled = 1;
}

// 0x71015d09d0 (48 bytes)
// Disables stop energy (slot 7) by clearing enabled flag
// [derived: get_energy(7), strb wzr at energy+0x30]
void unable(u8* L) {
    KineticModule* km = item_kinetic(L);
    KineticEnergy* energy = km->get_energy(7);
    energy->enabled = 0;
}

// 0x71015d1020 (56 bytes)
// Clears speed on stop energy (slot 7)
// [derived: get_energy(7) → energy->clear_speed() vtable+0x48]
void clear_speed(u8* L) {
    KineticModule* km = item_kinetic(L);
    KineticEnergy* energy = km->get_energy(7);
    energy->clear_speed();
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
}

// 0x71015d0940 (72 bytes)
// Multiplies speed on stop energy (slot 7) by vector
// [derived: get_energy(7) → energy->mul_speed(vec) vtable+0x58]
void mul_speed(u8* L, void* vec) {
    KineticModule* km = item_kinetic(L);
    KineticEnergy* energy = km->get_energy(7);
    energy->mul_speed(vec);
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
}

} // namespace app::kinetic_energy_stop

namespace app::kinetic_energy_jostle {

// 0x71015d0a70 (52 bytes)
// Enables jostle energy (slot 9) by setting enabled flag to 1
// [derived: get_energy(9), strb #1 at energy+0x30]
void enable(u8* L) {
    KineticModule* km = item_kinetic(L);
    KineticEnergy* energy = km->get_energy(9);
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
    energy->enabled = 1;
}

// 0x71015d0ab0 (48 bytes)
// Disables jostle energy (slot 9) by clearing enabled flag
// [derived: get_energy(9), strb wzr at energy+0x30]
void unable(u8* L) {
    KineticModule* km = item_kinetic(L);
    KineticEnergy* energy = km->get_energy(9);
    energy->enabled = 0;
}

} // namespace app::kinetic_energy_jostle

namespace app::kinetic_energy_ground_movement {

// 0x71015d0b70 (52 bytes)
// Enables ground movement energy (slot 10) by setting enabled flag to 1
// [derived: get_energy(0xa), strb #1 at energy+0x30]
void enable(u8* L) {
    KineticModule* km = item_kinetic(L);
    KineticEnergy* energy = km->get_energy(10);
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
    energy->enabled = 1;
}

// 0x71015d0bb0 (48 bytes)
// Disables ground movement energy (slot 10) by clearing enabled flag
// [derived: get_energy(0xa), strb wzr at energy+0x30]
void unable(u8* L) {
    KineticModule* km = item_kinetic(L);
    KineticEnergy* energy = km->get_energy(10);
    energy->enabled = 0;
}

} // namespace app::kinetic_energy_ground_movement

namespace app::kinetic_energy_motion_linked_main {

// 0x71015d0d40 (52 bytes)
// Enables motion-linked main energy (slot 0xc) by setting enabled flag to 1
// [derived: get_energy(0xc), strb #1 at energy+0x30]
void enable(u8* L) {
    KineticModule* km = item_kinetic(L);
    KineticEnergy* energy = km->get_energy(0xc);
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
    energy->enabled = 1;
}

// 0x71015d0d80 (48 bytes)
// Disables motion-linked main energy (slot 0xc) by clearing enabled flag
// [derived: get_energy(0xc), strb wzr at energy+0x30]
void unable(u8* L) {
    KineticModule* km = item_kinetic(L);
    KineticEnergy* energy = km->get_energy(0xc);
    energy->enabled = 0;
}

} // namespace app::kinetic_energy_motion_linked_main

namespace app::kinetic_energy_motion_linked_sub1 {

// 0x71015d0e80 (52 bytes)
// Enables motion-linked sub1 energy (slot 0xd) by setting enabled flag to 1
// [derived: get_energy(0xd), strb #1 at energy+0x30]
void enable(u8* L) {
    KineticModule* km = item_kinetic(L);
    KineticEnergy* energy = km->get_energy(0xd);
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
    energy->enabled = 1;
}

// 0x71015d0ec0 (48 bytes)
// Disables motion-linked sub1 energy (slot 0xd) by clearing enabled flag
// [derived: get_energy(0xd), strb wzr at energy+0x30]
void unable(u8* L) {
    KineticModule* km = item_kinetic(L);
    KineticEnergy* energy = km->get_energy(0xd);
    energy->enabled = 0;
}

// 0x71015d1060 (56 bytes)
// Clears speed on motion-linked sub1 energy (slot 0xd)
// [derived: get_energy(0xd) → energy->clear_speed() vtable+0x48]
void clear_speed(u8* L) {
    KineticModule* km = item_kinetic(L);
    KineticEnergy* energy = km->get_energy(0xd);
    energy->clear_speed();
#ifdef MATCHING_HACK_NX_CLANG
    asm("");
#endif
}

} // namespace app::kinetic_energy_motion_linked_sub1

namespace app::ai_param {

// 0x710036ba00 (16 bytes)
// Returns fall_speed_y_max from AI param block
// [derived: *(obj-8)->0x168 is AI param ptr, +0x228 is fall_speed_y_max field]
f32 fall_speed_y_max(u8* L) {
    u8* obj = *reinterpret_cast<u8**>(L - 8);
    u8* p = *reinterpret_cast<u8**>(obj + 0x168);
    return *reinterpret_cast<f32*>(p + 0x228);
}

// 0x710036ba10 (16 bytes)
// Returns dive_speed_y_max from AI param block
// [derived: same base as fall_speed_y_max, offset +0x22c]
f32 dive_speed_y_max(u8* L) {
    u8* obj = *reinterpret_cast<u8**>(L - 8);
    u8* p = *reinterpret_cast<u8**>(obj + 0x168);
    return *reinterpret_cast<f32*>(p + 0x22c);
}

// 0x710036b9d0 (12 bytes)
// Returns catch attack cancel frame from AI object
// [derived: *(obj + 0xbaa) direct byte access, no indirection]
u8 catch_attack_cancel_frame(u8* L) {
    u8* obj = *reinterpret_cast<u8**>(L - 8);
    return *reinterpret_cast<u8*>(obj + 0xbaa);
}

// 0x710036ba80 (12 bytes)
// Returns number of attack 123 combo hits from AI object
// [derived: *(obj + 0xb14) direct u32 access]
u32 num_of_attack_123(u8* L) {
    u8* obj = *reinterpret_cast<u8**>(L - 8);
    return *reinterpret_cast<u32*>(obj + 0xb14);
}

// 0x710036ba90 (12 bytes)
// Returns whether fighter has attack 100 (rapid jab) from AI object
// [derived: *(obj + 0xb18) direct byte access]
u8 has_attack_100(u8* L) {
    u8* obj = *reinterpret_cast<u8**>(L - 8);
    return *reinterpret_cast<u8*>(obj + 0xb18);
}

} // namespace app::ai_param

namespace app::ai_weapon {

// 0x710036b020 (16 bytes)
// Returns item kind from AI weapon param block
// [derived: *(*(obj+0x168)+0x108) — AI param at +0x168, weapon item kind at +0x108]
u32 have_item_kind(u8* L) {
    u8* obj = *reinterpret_cast<u8**>(L - 8);
    u8* p = *reinterpret_cast<u8**>(obj + 0x168);
    return *reinterpret_cast<u32*>(p + 0x108);
}

// 0x710036b0b0 (20 bytes)
// Returns weapon kind from FighterAIWeapon, or -1 if null
// [derived: null check on param_2, then *(param_2+4) or 0xFFFFFFFF]
u32 kind(u8* L, u8* weapon) {
    if (weapon) {
        return *reinterpret_cast<u32*>(weapon + 4);
    }
    return 0xFFFFFFFF;
}

// 0x710036b0d0 (20 bytes)
// Returns weapon flags from FighterAIWeapon, or 0 if null
// [derived: null check on param_2, then *(u16*)(param_2+8) or 0]
u16 flag(u8* L, u8* weapon) {
    if (weapon) {
        return *reinterpret_cast<u16*>(weapon + 8);
    }
    return 0;
}

} // namespace app::ai_weapon

// ════════════════════════════════════════════════════════════════════════════
// AI attack info / target resolution functions
// External helpers:
//   FUN_710033ba50(u32 fighter_kind) — returns attack info table pointer
//   FUN_71002f2820(u32 cmd_id, u32 fighter_kind) — remaps CmdId to motion status
//   FUN_7100314030(void* world_ptr, void* target_slot) — resolves target entry
//   FUN_710033c360(void* cmd_table, u32 cmd_id) — looks up attack entry by CmdId
//   FUN_710033c510(u32 fighter_kind, u64 motion_hash) — looks up attack entry by motion hash
//   FUN_710033e5c0(void* cmd_table, u64 motion_hash) — motion hash to CmdId
// ════════════════════════════════════════════════════════════════════════════

extern "C" void* FUN_710033ba50(u32);
extern "C" s32 FUN_71002f2820(u32, u32);
extern "C" void* FUN_7100314030(void*, void*);
extern "C" void* FUN_710033c360(void*, u32);
extern "C" void* FUN_710033c510(u32, u64);
extern "C" u32 FUN_710033e5c0(void*, u64);
extern "C" __attribute__((visibility("hidden"))) void* DAT_71052b5fd8;

namespace app::ai {

// ── Helper: compute attack table index from status code ──────────────
// The AI attack info table uses a 3-tier range mapping on the motion status:
//   [0x6031, 0x603f] → index = status - 0x6031 (ground normals, 0..14)
//   [0x6041, 0x604f] → index = status - 0x6034 (aerials, 13..27)
//   [0x6051, 0x6068] → index = status - 0x603b (specials, 22..45)
// [derived: identical pattern in attack_info_needs_turn/reaction/no_shield/meteor/
//  reflectable/as_weapon/distance — all 7 functions use same index logic with stride 0xb8]
static inline s64 attack_info_index(s32 status) {
    s64 idx_a = (s64)(s32)(status - 0x603b);
    s64 idx_b = (s64)(s32)(status - 0x6034);
    s64 idx_c = (s64)(s32)((u32)status - 0x6031u);
#ifdef MATCHING_HACK_NX_CLANG
    // Force compiler to keep 64-bit intermediates in x registers
    // (NX Clang generates sxtw + x-register csel; upstream defers sxtw)
    asm("" : "+r"(idx_a), "+r"(idx_b), "+r"(idx_c));
#endif
    s64 index = 0;
    if ((u32)(status - 0x6051) < 0x18u)
        index = idx_a;
    if ((u32)(status - 0x6041) < 0xfu)
        index = idx_b;
    if ((u32)(status - 0x6031) < 0xfu)
        index = idx_c;
    return index;
}

// ---------------------------------------------------------------------------
// 0x7100367020  40B  target_motion_kind
// Returns Hash40 motion kind of current AI target.
// [derived: resolves target via FUN_7100314030(*DAT_71052b5fd8, ctx+0xc50),
//  reads u64 at target+0x38 — motion kind field in target info struct]
// ---------------------------------------------------------------------------
u64 target_motion_kind(void* L) {
    u8* ctx = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(L) - 8);
    u8* target = reinterpret_cast<u8*>(FUN_7100314030(DAT_71052b5fd8, ctx + 0xc50));
    return *reinterpret_cast<u64*>(target + 0x38);
}

// ---------------------------------------------------------------------------
// 0x7100367050  40B  target_motion_frame
// Returns current motion frame of AI target.
// [derived: same target resolution as target_motion_kind, reads u32 at +0x48]
// ---------------------------------------------------------------------------
u32 target_motion_frame(void* L) {
    u8* ctx = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(L) - 8);
    u8* target = reinterpret_cast<u8*>(FUN_7100314030(DAT_71052b5fd8, ctx + 0xc50));
    return *reinterpret_cast<u32*>(target + 0x48);
}

// ---------------------------------------------------------------------------
// 0x7100369cd0  160B  attack_info_needs_turn
// AI: returns needs_turn flag (u8) from attack info table at +0x1d.
// [derived: attack_info table at FUN_710033ba50(fighter_kind)->+8, stride 0xb8,
//  +0x1d is needs_turn — compared with attack_info_no_shield (+0x24) pattern]
// ---------------------------------------------------------------------------
u8 attack_info_needs_turn(void* L, u32 cmd_id) {
    u8* ctx = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(L) - 8);
    u32 obj_id = *reinterpret_cast<u32*>(ctx + 0x988);
    u8* attack_data = reinterpret_cast<u8*>(FUN_710033ba50(obj_id));
    s32 status = FUN_71002f2820(cmd_id, obj_id);

    s64 index = attack_info_index(status);
    u8* base = *reinterpret_cast<u8**>(attack_data + 8);
    return base[index * 0xb8 + 0x1d];
}

// ---------------------------------------------------------------------------
// 0x7100369d70  160B  attack_info_reaction
// AI: returns reaction value (u32) from attack info table at +0x20.
// [derived: same pattern as attack_info_needs_turn, offset +0x20 is reaction —
//  u32 return type matches Ghidra undefined4 at that offset]
// ---------------------------------------------------------------------------
u32 attack_info_reaction(void* L, u32 cmd_id) {
    u8* ctx = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(L) - 8);
    u32 obj_id = *reinterpret_cast<u32*>(ctx + 0x988);
    u8* attack_data = reinterpret_cast<u8*>(FUN_710033ba50(obj_id));
    s32 status = FUN_71002f2820(cmd_id, obj_id);

    s64 index = attack_info_index(status);
    u8* base = *reinterpret_cast<u8**>(attack_data + 8);
    return *reinterpret_cast<u32*>(base + index * 0xb8 + 0x20);
}

// ---------------------------------------------------------------------------
// 0x7100369eb0  160B  attack_info_meteor
// AI: returns meteor flag (u8) from attack info table at +0x25.
// [derived: same pattern, +0x25 immediately after no_shield (+0x24)]
// ---------------------------------------------------------------------------
u8 attack_info_meteor(void* L, u32 cmd_id) {
    u8* ctx = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(L) - 8);
    u32 obj_id = *reinterpret_cast<u32*>(ctx + 0x988);
    u8* attack_data = reinterpret_cast<u8*>(FUN_710033ba50(obj_id));
    s32 status = FUN_71002f2820(cmd_id, obj_id);

    s64 index = attack_info_index(status);
    u8* base = *reinterpret_cast<u8**>(attack_data + 8);
    return base[index * 0xb8 + 0x25];
}

// ---------------------------------------------------------------------------
// 0x7100369f50  160B  attack_info_reflectable
// AI: returns reflectable flag (u8) from attack info table at +0x5.
// [derived: same pattern, +0x5 — note lower offset than others, near start of entry]
// ---------------------------------------------------------------------------
u8 attack_info_reflectable(void* L, u32 cmd_id) {
    u8* ctx = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(L) - 8);
    u32 obj_id = *reinterpret_cast<u32*>(ctx + 0x988);
    u8* attack_data = reinterpret_cast<u8*>(FUN_710033ba50(obj_id));
    s32 status = FUN_71002f2820(cmd_id, obj_id);

    s64 index = attack_info_index(status);
    u8* base = *reinterpret_cast<u8**>(attack_data + 8);
    return base[index * 0xb8 + 5];
}

// ---------------------------------------------------------------------------
// 0x7100369ff0  160B  attack_is_as_weapon
// AI: returns as_weapon flag (u8) from attack info table at +0x6.
// [derived: same pattern, +0x6 — adjacent to reflectable at +0x5]
// ---------------------------------------------------------------------------
u8 attack_is_as_weapon(void* L, u32 cmd_id) {
    u8* ctx = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(L) - 8);
    u32 obj_id = *reinterpret_cast<u32*>(ctx + 0x988);
    u8* attack_data = reinterpret_cast<u8*>(FUN_710033ba50(obj_id));
    s32 status = FUN_71002f2820(cmd_id, obj_id);

    s64 index = attack_info_index(status);
    u8* base = *reinterpret_cast<u8**>(attack_data + 8);
    return base[index * 0xb8 + 6];
}

// ---------------------------------------------------------------------------
// 0x710036a090  160B  attack_info_distance
// AI: returns distance value (u32/f32) from attack info table at +0x18.
// [derived: same pattern, +0x18 — 4-byte read, likely f32 distance threshold]
// ---------------------------------------------------------------------------
u32 attack_info_distance(void* L, u32 cmd_id) {
    u8* ctx = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(L) - 8);
    u32 obj_id = *reinterpret_cast<u32*>(ctx + 0x988);
    u8* attack_data = reinterpret_cast<u8*>(FUN_710033ba50(obj_id));
    s32 status = FUN_71002f2820(cmd_id, obj_id);

    s64 index = attack_info_index(status);
    u8* base = *reinterpret_cast<u8**>(attack_data + 8);
    return *reinterpret_cast<u32*>(base + index * 0xb8 + 0x18);
}

// ---------------------------------------------------------------------------
// 0x7100369b00  108B  target_attack_start_frame
// AI: resolves target, looks up attack entry by CmdId, returns start frame.
// [derived: FUN_7100314030 for target, validates target_id < 16 and not self,
//  FUN_710033c360 for attack lookup on target, reads u32 at entry+8]
// ---------------------------------------------------------------------------
u32 target_attack_start_frame(void* L, u32 cmd_id) {
    u8* ctx = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(L) - 8);
    u8* target = reinterpret_cast<u8*>(FUN_7100314030(DAT_71052b5fd8, ctx + 0xc50));
    u32 target_id = *reinterpret_cast<u32*>(ctx + 0xc50);

    if ((s32)target_id < 0 || target_id == *reinterpret_cast<u32*>(ctx + 0x160) || target_id > 0xf)
        return 0;

    u8* target_obj = *reinterpret_cast<u8**>(target + 0x20);
    if (!target_obj)
        return 0;

    u8* entry = reinterpret_cast<u8*>(FUN_710033c360(target_obj + 0x988, cmd_id));
    if (!entry)
        return 0;

    return *reinterpret_cast<u32*>(entry + 8);
}

// ---------------------------------------------------------------------------
// 0x7100369ba0  108B  attack_cancel_frame
// AI: looks up attack entry by CmdId, returns cancel frame; if -1, computes
// from MotionModule end frame via vtable call.
// [derived: FUN_710033c360 for attack entry, +0x14 is cancel_frame,
//  -1 sentinel triggers fallback to motion module end_frame (vtable slot 0x188/8)]
// ---------------------------------------------------------------------------
s32 attack_cancel_frame(void* L, u32 cmd_id) {
    u8* ctx = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(L) - 8);
    u8* entry = reinterpret_cast<u8*>(FUN_710033c360(ctx + 0x988, cmd_id));

    if (!entry)
        return 0;

    s32 frame = *reinterpret_cast<s32*>(entry + 0x14);
    if (frame == -1) {
        // Fallback: get end frame from MotionModule
        // [derived: ctx+0x168 is AI fighter obj, +0x10 is battle object,
        //  +0x20 is accessor, +0x88 is motion_module, vtable slot 0x188/8 = end_frame]
        u8* ai_obj = *reinterpret_cast<u8**>(ctx + 0x168);
        u8* battle_obj = *reinterpret_cast<u8**>(ai_obj + 0x10);
        u8* acc = *reinterpret_cast<u8**>(battle_obj + 0x20);
        void** motion_mod = *reinterpret_cast<void***>(acc + 0x88);
        u64 motion_hash = *reinterpret_cast<u64*>(entry);
        void** vt = reinterpret_cast<void**>(*motion_mod);
        u32 end_frame_raw = reinterpret_cast<u32(*)(void**, u64)>(
            vt[0x188 / 8])(motion_mod, motion_hash);
        frame = (s32)(f32)end_frame_raw;
    }
    return frame;
}

// ---------------------------------------------------------------------------
// 0x710036a300  92B  target_motion_to_cmd_id
// AI: resolves target, calls motion_to_cmd_id on target's cmd table.
// [derived: validates target_id < 16, resolves target via FUN_7100314030,
//  tail-calls FUN_710033e5c0(target_obj+0x988, motion_hash)]
// ---------------------------------------------------------------------------
u64 target_motion_to_cmd_id(void* L, u64 motion_hash) {
    u8* ctx = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(L) - 8);
    u8* target = reinterpret_cast<u8*>(FUN_7100314030(DAT_71052b5fd8, ctx + 0xc50));

    if (*reinterpret_cast<u32*>(ctx + 0xc50) >= 0x10u)
        return 0;

    u8* target_obj = *reinterpret_cast<u8**>(target + 0x20);
    if (!target_obj)
        return 0;

    return FUN_710033e5c0(target_obj + 0x988, motion_hash);
}

// ---------------------------------------------------------------------------
// 0x710036a360  172B  current_attack_combo_next_motion
// AI: returns the next motion in a jab combo chain based on current motion hash.
// [derived: reads motion_hash at *(ctx+0x168)+0x38, masks to 40 bits,
//  hardcoded Hash40 switch for attack_11/12/13 chain, fallback via FUN_710033c510]
// Hash40 constants:
//   0xea274b695 = attack_11 → returns 0xb78983dd2 = attack_12
//   0xfee188235 = attack_12 → returns 0xa86d04046 = attack_13
//   0xf5db36b5c = attack_13 → returns 0xa5598d745 = attack_100
//   fallback: FUN_710033c510 entry+0x28 or 0x7fb997a80 = invalid
// ---------------------------------------------------------------------------
u64 current_attack_combo_next_motion(void* L) {
    u8* ctx = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(L) - 8);
    u8* ai_obj = *reinterpret_cast<u8**>(ctx + 0x168);
    u64 motion_raw = *reinterpret_cast<u64*>(ai_obj + 0x38);
    u64 motion = motion_raw & 0xFFFFFFFFFFULL;

    if (motion == 0xea274b695ULL)   // attack_11
        return 0xb78983dd2ULL;       // attack_12
    if (motion == 0xfee188235ULL)   // attack_12
        return 0xa86d04046ULL;       // attack_13
    if (motion == 0xf5db36b5cULL)   // attack_13
        return 0xa5598d745ULL;       // attack_100

    u8* entry = reinterpret_cast<u8*>(
        FUN_710033c510(*reinterpret_cast<u32*>(ctx + 0x988), motion_raw));
    if (entry)
        return *reinterpret_cast<u64*>(entry + 0x28);

    return 0x7fb997a80ULL;          // invalid/none motion hash
}

// ---------------------------------------------------------------------------
// 0x710036a140  212B  target_attack_info_needs_turn
// AI: like attack_info_needs_turn but resolves target first.
// [derived: validates target_id < 16, resolves via FUN_7100314030,
//  then same attack_info_index + table read at +0x1d]
// ---------------------------------------------------------------------------
bool target_attack_info_needs_turn(void* L, u32 cmd_id) {
    u8* ctx = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(L) - 8);
    u8* target = reinterpret_cast<u8*>(FUN_7100314030(DAT_71052b5fd8, ctx + 0xc50));

    if (*reinterpret_cast<u32*>(ctx + 0xc50) >= 0x10u)
        return false;

    u8* target_obj = *reinterpret_cast<u8**>(target + 0x20);
    if (!target_obj)
        return false;

    u32 obj_id = *reinterpret_cast<u32*>(target_obj + 0x988);
    u8* attack_data = reinterpret_cast<u8*>(FUN_710033ba50(obj_id));
    s32 status = FUN_71002f2820(cmd_id, obj_id);

    s64 index = attack_info_index(status);
    u8* base = *reinterpret_cast<u8**>(attack_data + 8);
    return base[index * 0xb8 + 0x1d] != 0;
}

// ---------------------------------------------------------------------------
// 0x710036a410  228B  target_current_attack_combo_next_motion
// AI: like current_attack_combo_next_motion but resolves target first.
// [derived: validates target_id < 16 and not self and >= 0,
//  reads target motion hash at target+0x38, same Hash40 switch,
//  fallback via FUN_710033c510 on target's cmd table]
// ---------------------------------------------------------------------------
u64 target_current_attack_combo_next_motion(void* L) {
    u8* ctx = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(L) - 8);
    u64 result = 0x7fb997a80ULL;  // invalid/none

    u8* target = reinterpret_cast<u8*>(FUN_7100314030(DAT_71052b5fd8, ctx + 0xc50));
    u32 target_id = *reinterpret_cast<u32*>(ctx + 0xc50);

    if ((s32)target_id >= 0 && target_id != *reinterpret_cast<u32*>(ctx + 0x160) && target_id < 0x10) {
        u64 motion_raw = *reinterpret_cast<u64*>(target + 0x38);
        u64 motion = motion_raw & 0xFFFFFFFFFFULL;

        if (motion == 0xea274b695ULL) {         // attack_11
            result = 0xb78983dd2ULL;             // attack_12
        } else if (motion == 0xfee188235ULL) {  // attack_12
            result = 0xa86d04046ULL;             // attack_13
        } else if (motion == 0xf5db36b5cULL) {  // attack_13
            result = 0xa5598d745ULL;             // attack_100
        } else {
            u8* target_obj = *reinterpret_cast<u8**>(target + 0x20);
            if (target_obj) {
                u8* entry = reinterpret_cast<u8*>(
                    FUN_710033c510(*reinterpret_cast<u32*>(target_obj + 0x988), motion_raw));
                if (entry)
                    result = *reinterpret_cast<u64*>(entry + 0x28);
            }
        }
    }
    return result;
}

// ---------------------------------------------------------------------------
// 0x710036a500  108B  target_attack_start_frame_from_motion
// AI: like target_attack_start_frame but looks up by motion Hash40.
// [derived: same target validation, FUN_710033c510 for motion-based lookup,
//  reads u32 at entry+8 for start frame]
// ---------------------------------------------------------------------------
u32 target_attack_start_frame_from_motion(void* L, u64 motion_hash) {
    u8* ctx = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(L) - 8);
    u8* target = reinterpret_cast<u8*>(FUN_7100314030(DAT_71052b5fd8, ctx + 0xc50));
    u32 target_id = *reinterpret_cast<u32*>(ctx + 0xc50);

    if ((s32)target_id < 0 || target_id == *reinterpret_cast<u32*>(ctx + 0x160) || target_id > 0xf)
        return 0;

    u8* target_obj = *reinterpret_cast<u8**>(target + 0x20);
    if (!target_obj)
        return 0;

    u8* entry = reinterpret_cast<u8*>(
        FUN_710033c510(*reinterpret_cast<u32*>(target_obj + 0x988), motion_hash));
    if (!entry)
        return 0;

    return *reinterpret_cast<u32*>(entry + 8);
}

} // namespace app::ai

// ════════════════════════════════════════════════════════════════════════════
// KineticUtility — energy management helpers
// ════════════════════════════════════════════════════════════════════════════

namespace app::KineticUtility {

// ---------------------------------------------------------------------------
// 0x710047b830  68B  clear_unable_energy
// Clears speed on a kinetic energy slot and disables it.
// [derived: KineticModule::get_energy(index) vtable+0x60, then
//  KineticEnergy::clear_speed() vtable+0x48, then sets enabled byte +0x30 to 0]
// ---------------------------------------------------------------------------
void clear_unable_energy(int index, BattleObjectModuleAccessor* acc) {
    KineticModule* km = static_cast<KineticModule*>(acc->item_kinetic_module);
    KineticEnergy* energy = km->get_energy(index);
    energy->clear_speed();
    energy->enabled = 0;
}

// ---------------------------------------------------------------------------
// 0x710047b7b0  116B  reset_enable_energy
// Resets a kinetic energy slot with parameters and enables it.
// [derived: KineticModule::get_energy(index) vtable+0x60, then
//  KineticEnergy vtable+0x40 = reset_energy(kind, vec2, vec3, acc),
//  then sets enabled byte +0x30 to 1]
// ---------------------------------------------------------------------------
void reset_enable_energy(int index, BattleObjectModuleAccessor* acc, int kind,
                         void* vec2, void* vec3) {
    KineticModule* km = static_cast<KineticModule*>(acc->item_kinetic_module);
    KineticEnergy* energy = km->get_energy(index);
    // reset_energy takes (kind, vec2, vec3, acc) via vtable+0x40
    void** vt_e = *reinterpret_cast<void***>(energy);
    reinterpret_cast<void(*)(KineticEnergy*, int, void*, void*, BattleObjectModuleAccessor*)>(
        vt_e[0x40 / 8])(energy, kind, vec2, vec3, acc);
    energy->enabled = 1;
}

} // namespace app::KineticUtility

// ════════════════════════════════════════════════════════════════════════════
// Item kinetic energy helpers
// ════════════════════════════════════════════════════════════════════════════

namespace app::item {

// ---------------------------------------------------------------------------
// 0x71015c3e60  52B  unable_control_energy
// Disables control energy (slot 4) on an item's kinetic module.
// [derived: *(L-8)->+0x1a0 is accessor, +0x190 (=400) is item_module offset,
//  then +0x220 is kinetic sub-module ptr, +0x100 is kinetic module,
//  calls unable_energy(4) via vtable+0x130]
// ---------------------------------------------------------------------------
void unable_control_energy(u8* L) {
    u8* obj = *reinterpret_cast<u8**>(L - 8);
    u8* acc = *reinterpret_cast<u8**>(obj + 0x1a0);
    u8* item_mod = *reinterpret_cast<u8**>(acc + 400);
    u8* kinetic_sub = *reinterpret_cast<u8**>(item_mod + 0x220);
    void** km = *reinterpret_cast<void***>(kinetic_sub + 0x100);
    void** vt = reinterpret_cast<void**>(*km);
    reinterpret_cast<void(*)(void**, int)>(vt[0x130 / 8])(km, 4);
#ifdef MATCHING_HACK_NX_CLANG
    asm volatile("" ::: "memory");  // prevent tail-call optimization
#endif
}

} // namespace app::item

// ════════════════════════════════════════════════════════════════════════════
// Rocketbelt energy accessor
// ════════════════════════════════════════════════════════════════════════════

// FighterParamAccessor2 singleton
// [derived: lib::Singleton<app::FighterParamAccessor2>::instance_]
extern "C" __attribute__((visibility("hidden"))) void* DAT_71052bb3b0;

namespace app::rocketbelt {

// ---------------------------------------------------------------------------
// 0x710166fc60  20B  get_energy_max_frame
// Returns max frame for rocketbelt energy from FighterParamAccessor2 singleton.
// [derived: *(*(FPA2_instance + 0x50) + 0xefc) — FPA2 at DAT_71052bb3b0,
//  +0x50 is param table ptr, +0xefc is rocketbelt max frame field]
// ---------------------------------------------------------------------------
u32 get_energy_max_frame() {
    u8* pa = reinterpret_cast<u8*>(DAT_71052bb3b0);
    u8* table = *reinterpret_cast<u8**>(pa + 0x50);
    return *reinterpret_cast<u32*>(table + 0xefc);
}

} // namespace app::rocketbelt
