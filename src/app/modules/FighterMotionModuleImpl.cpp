#include "app/BattleObjectModuleAccessor.h"

// FighterMotionModuleImpl -- accesses MotionModule at accessor+0x88
// Most functions are tail-call wrappers to external targets (won't byte-match).
// Complex functions include Kirby copy hash translation and damage stop logic.

struct FighterMotionModuleImpl;
#define VT(m) (*reinterpret_cast<void***>(m))
#define MOTION(a) (reinterpret_cast<u8*>((a)->motion_module))

// External tail call targets
extern "C" void FUN_71006e1b90(void*, u32);
extern "C" void FUN_71006e1e20(void*, u64, bool);
extern "C" void FUN_71006e20c0(void*, u64, bool);
extern "C" void FUN_71006e2440(void*, u64, bool);
extern "C" void FUN_71006e2200(void*, u64, bool);
extern "C" void FUN_71006e2680(void*, u64, bool, bool, bool);
extern "C" void FUN_71006e27f0(void*, u64, bool, bool);
extern "C" void FUN_71006e29f0(void*, bool);
extern "C" void FUN_710049c190(void*, u64);
extern "C" void FUN_710049e4b0(void*, u32, u64, bool, bool, bool, bool, bool, f32, f32, f32);

// Global Kirby copy hash lookup table
extern "C" u64 PTR_DAT_7104fcd388[];

// Global pause state
extern "C" u64* DAT_71052c2760;

namespace app::lua_bind {

// 71020aa000 -- mov x0,x1; mov w1,w2; b external
void FighterMotionModuleImpl__add_body_type_hash_impl(BattleObjectModuleAccessor*, void* module, u32 hash) {
    FUN_71006e1b90(module, hash);
}

// 71020aa010 -- ldr x0,[x0,#0x88]; and w2,w2,#0x1; b external
void FighterMotionModuleImpl__get_cancel_frame_impl(BattleObjectModuleAccessor* a, u64 hash, bool p2) {
    FUN_71006e1e20(a->motion_module, hash, p2 & 1);
}

// 71020aa020 -- ldr x0,[x0,#0x88]; and w2,w2,#0x1; b external
void FighterMotionModuleImpl__is_valid_cancel_frame_impl(BattleObjectModuleAccessor* a, u64 hash, bool p2) {
    FUN_71006e20c0(a->motion_module, hash, p2 & 1);
}

// 71020aa030 -- ldr x0,[x0,#0x88]; and w2,w2,#0x1; b external
void FighterMotionModuleImpl__get_hit_normal_frame_impl(BattleObjectModuleAccessor* a, u64 hash, bool p2) {
    FUN_71006e2440(a->motion_module, hash, p2 & 1);
}

// 71020aa040 -- ldr x0,[x0,#0x88]; and w2,w2,#0x1; b external
void FighterMotionModuleImpl__get_hit_xlu_frame_impl(BattleObjectModuleAccessor* a, u64 hash, bool p2) {
    FUN_71006e2200(a->motion_module, hash, p2 & 1);
}

// 71020aa0d0 -- ldr module; and w2,w3,w4 with #0x1; b change_motion_kirby_copy
void FighterMotionModuleImpl__change_motion_kirby_copy_impl(BattleObjectModuleAccessor* a, u64 hash, bool p2, bool p3, bool p4) {
    FUN_71006e2680(a->motion_module, hash, p2 & 1, p3 & 1, p4 & 1);
}

// 71020aa0f0 -- ldr module; and w2,w3 with #0x1; b external
void FighterMotionModuleImpl__change_motion_inherit_frame_kirby_copy_impl(BattleObjectModuleAccessor* a, u64 hash, bool p2, bool p3) {
    FUN_71006e27f0(a->motion_module, hash, p2 & 1, p3 & 1);
}

// 71020aa100 -- ldr module; hardcode w3=1,w2=0; b same target as above
void FighterMotionModuleImpl__change_motion_inherit_frame_keep_rate_kirby_copy_impl(BattleObjectModuleAccessor* a, u64 hash) {
    FUN_71006e27f0(a->motion_module, hash, 0, 1);
}

// 71020aa210 -- ldr x0,[x0,#0x88]; and w1,w1,#0x1; b external
void FighterMotionModuleImpl__set_frame_sync_anim_cmd_kirby_copy_impl(BattleObjectModuleAccessor* a, bool val) {
    FUN_71006e29f0(a->motion_module, val & 1);
}

// 71020aa3a0 -- set_blend_waist (4 insns: ldr module, and bool, strb to +0x2f2)
void FighterMotionModuleImpl__set_blend_waist_impl(BattleObjectModuleAccessor* a, bool val) {
    auto* module = reinterpret_cast<u8*>(a->motion_module);
    module[0x2f2] = val & 1;
}

// 71020aa490 -- set_update_finger_and_face_joint: chain through module+0x10, +0x8, vtable
void FighterMotionModuleImpl__set_update_finger_and_face_joint_impl(BattleObjectModuleAccessor* a, bool val) {
    auto* module = MOTION(a);
    auto* chain1 = *reinterpret_cast<u8**>(module + 0x10);
    auto* chain2 = *reinterpret_cast<void**>(chain1 + 0x8);
    auto* vt = *reinterpret_cast<void***>(chain2);
    auto fn = reinterpret_cast<void (*)(void*, bool)>(vt[0xa0 / 8]);
    fn(chain2, val & 1);
}
} // namespace app::lua_bind

