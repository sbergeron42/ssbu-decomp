#include "app/BattleObjectModuleAccessor.h"

// FighterMotionModuleImpl — accesses MotionModule at accessor+0x88
// Simple tail-call wrappers that load module, mask bools, and branch

struct FighterMotionModuleImpl;
#define VT(m) (*reinterpret_cast<void***>(m))
namespace app::lua_bind {

// 71020aa010 — get_cancel_frame (3 insns: ldr+and+b)
extern "C" void _get_cancel_frame_target();
// 71020aa020 — is_valid_cancel_frame (3 insns)
// 71020aa030 — get_hit_normal_frame (3 insns)
// 71020aa040 — get_hit_xlu_frame (3 insns)
// 71020aa210 — set_frame_sync_anim_cmd_kirby_copy (3 insns)

// These are tail calls to external functions — need the target addresses to link.
// For now, write the field write which is self-contained:

// 71020aa3a0 — set_blend_waist (4 insns: ldr module, and bool, strb to +0x2f2)
void FighterMotionModuleImpl__set_blend_waist_impl(BattleObjectModuleAccessor* a, bool val) {
    auto* module = reinterpret_cast<u8*>(a->motion_module);
    module[0x2f2] = val & 1;
}

void FighterMotionModuleImpl__set_update_finger_and_face_joint_impl(FighterMotionModuleImpl* obj,bool p1) { reinterpret_cast<void(*)(FighterMotionModuleImpl*,bool)>(VT(obj)[0x10/8])(obj,p1); }
} // namespace app::lua_bind
