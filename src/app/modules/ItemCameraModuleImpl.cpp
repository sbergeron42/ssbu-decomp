#include "app/BattleObjectModuleAccessor.h"

// ItemCameraModuleImpl -- accesses CameraModule at accessor+0x60
// Camera slots are 0xe0 bytes apart. Slot enable at slot+0x70; pos at slot+0x90.

extern "C" void FUN_7101610890(void*);

namespace app::lua_bind {

// 71020d21f0 -- load camera_module, tail-call start function
void ItemCameraModuleImpl__start_camera_subject_impl(BattleObjectModuleAccessor* a) {
    FUN_7101610890(a->camera_module);
}

// 71020d2460 -- bounds-checked slot enable/disable
void ItemCameraModuleImpl__set_camera_subject_enable_impl(BattleObjectModuleAccessor* a, s32 slot, bool enable) {
    if (slot < 4) {
        u8* cam = reinterpret_cast<u8*>(a->camera_module);
        *reinterpret_cast<u32*>(cam + (s64)slot * 0xe0 + 0x70) = (~(u32)enable) & 1;
    }
}

// 71020d3c60 -- set_fix_rate (4 instructions: ldr ptr chain, str float)
void ItemMotionAnimcmdModuleImpl__set_fix_rate_impl(BattleObjectModuleAccessor* a, f32 rate) {
    auto* mac = *reinterpret_cast<void**>(reinterpret_cast<u8*>(a) + 0x188);
    auto* inner = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(mac) + 0x8);
    *reinterpret_cast<f32*>(inner + 0x48) = rate;
}

} // namespace app::lua_bind

