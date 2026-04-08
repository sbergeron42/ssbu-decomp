#include "types.h"
#include "app/BattleObjectModuleAccessor.h"
#include "app/modules/MotionModule.h"
#include "app/modules/PostureModule.h"

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

} // namespace app::FighterUtil

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
