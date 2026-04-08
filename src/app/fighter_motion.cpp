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
// [derived: acc->kinetic_module vtable+0x60 get_energy(2), str s8 at +0x8c]
void energy_motion_set_angle(BattleObjectModuleAccessor* acc, f32 angle) {
    KineticModule* km = static_cast<KineticModule*>(acc->item_kinetic_module);
    KineticEnergy* energy = km->get_energy(2);
    *reinterpret_cast<f32*>(reinterpret_cast<u8*>(energy) + 0x8c) = angle;
}

} // namespace app::WeaponSpecializer_EFlameEsword

namespace app::WeaponSpecializer_ElementDiver {

// 0x71033f5630 (52 bytes)
// Sets speed multiplier on motion energy (slot 2) at energy+0x90
// [derived: acc->kinetic_module vtable+0x60 get_energy(2), str s8 at +0x90]
void set_energy_motion_speed_mul(BattleObjectModuleAccessor* acc, f32 mul) {
    KineticModule* km = static_cast<KineticModule*>(acc->item_kinetic_module);
    KineticEnergy* energy = km->get_energy(2);
    *reinterpret_cast<f32*>(reinterpret_cast<u8*>(energy) + 0x90) = mul;
}

} // namespace app::WeaponSpecializer_ElementDiver
