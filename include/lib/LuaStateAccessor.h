#pragma once

#include "types.h"

// Forward declarations — same types as BattleObjectModuleAccessor
namespace app {
struct PostureModule;
struct StatusModule;
struct ControlModule;
struct WorkModule;
struct GroundModule;
struct CameraModule;
struct KineticModule;
struct ColorBlendModule;
struct ModelModule;
struct PhysicsModule;
struct MotionModule;
struct StopModule;
struct ArticleModule;
struct AttackModule;
struct DamageModule;
struct HitModule;
struct ComboModule;
struct AreaModule;
struct ItemModule;
struct LinkModule;
struct TeamModule;
struct SearchModule;
struct TurnModule;
struct ReflectModule;
struct ShieldModule;
struct AbsorberModule;
struct ReflectorModule;
struct JostleModule;
struct CatchModule;
struct CancelModule;
struct CaptureModule;
struct EffectModule;
struct SoundModule;
struct VisibilityModule;
struct GrabModule;
struct ShakeModule;
struct SlowModule;
struct ShadowModule;
struct MotionAnimcmdModule;
struct InkPaintModule;
}

namespace lib {

// LuaStateAccessor — module pointer cache for Lua script execution.
// Layout derived from SetLuaStateAccessor at 0x71003ab220 (364 bytes),
// which copies module pointers from BattleObjectModuleAccessor (src+0x38..+0x198)
// into this struct (dst+0x18..+0x180).
//
// Note: layout differs from BattleObjectModuleAccessor — contiguous packing
// with different ordering for absorber/reflector (stored out-of-order at end).
struct LuaStateAccessor {
    u8 pad_0x00[0x18];                                       // +0x00 header (lua state internals)
    app::PostureModule* posture_module;                      // +0x18 [derived: from acc+0x38]
    void* pad_0x20;                                          // +0x20 (gap — not written in SetLuaStateAccessor)
    app::StatusModule* status_module;                        // +0x28 [derived: from acc+0x40]
    app::ControlModule* fighter_control_module;              // +0x30 [derived: from acc+0x48]
    app::WorkModule* work_module;                            // +0x38 [derived: from acc+0x50]
    app::GroundModule* ground_module;                        // +0x40 [derived: from acc+0x58]
    app::CameraModule* camera_module;                        // +0x48 [derived: from acc+0x60]
    app::KineticModule* item_kinetic_module;                 // +0x50 [derived: from acc+0x68]
    app::ColorBlendModule* color_blend_module;               // +0x58 [derived: from acc+0x70]
    app::ModelModule* model_module;                          // +0x60 [derived: from acc+0x78]
    app::PhysicsModule* physics_module;                      // +0x68 [derived: from acc+0x80]
    app::MotionModule* motion_module;                        // +0x70 [derived: from acc+0x88]
    app::StopModule* stop_module;                            // +0x78 [derived: from acc+0x90]
    app::ArticleModule* article_module;                      // +0x80 [derived: from acc+0x98]
    app::AttackModule* attack_module;                        // +0x88 [derived: from acc+0xA0]
    app::DamageModule* damage_module;                        // +0x90 [derived: from acc+0xA8]
    app::HitModule* hit_module;                              // +0x98 [derived: from acc+0xB0]
    app::ComboModule* combo_module;                          // +0xa0 [derived: from acc+0xB8]
    app::AreaModule* fighter_area_module;                     // +0xa8 [derived: from acc+0xC0]
    app::ItemModule* item_module;                            // +0xb0 [derived: from acc+0xC8]
    app::LinkModule* link_module;                            // +0xb8 [derived: from acc+0xD0]
    app::TeamModule* team_module;                            // +0xc0 [derived: from acc+0xD8]
    app::SearchModule* search_module;                        // +0xc8 [derived: from acc+0xE0]
    void* pad_0xD0;                                          // +0xd0 [derived: from acc+0xE8 (unknown)]
    app::TurnModule* turn_module;                            // +0xd8 [derived: from acc+0xF0]
    app::ReflectModule* reflect_module;                      // +0xe0 [derived: from acc+0xF8]
    app::ShieldModule* shield_module;                        // +0xe8 [derived: from acc+0x100]
    app::AbsorberModule* absorber_module;                    // +0xf0 [derived: from acc+0x110, stored out-of-order]
    app::ReflectorModule* reflector_module;                  // +0xf8 [derived: from acc+0x108, stored out-of-order]
    app::JostleModule* jostle_module;                        // +0x100 [derived: from acc+0x118]
    app::CatchModule* catch_module;                          // +0x108 [derived: from acc+0x120]
    app::CancelModule* cancel_module;                        // +0x110 [derived: from acc+0x128]
    void* pad_0x118;                                         // +0x118 [derived: from acc+0x130 (unknown)]
    app::CaptureModule* capture_module;                      // +0x120 [derived: from acc+0x138]
    app::EffectModule* effect_module;                        // +0x128 [derived: from acc+0x140]
    app::SoundModule* sound_module;                          // +0x130 [derived: from acc+0x148]
    app::VisibilityModule* visibility_module;                // +0x138 [derived: from acc+0x150]
    app::GrabModule* grab_module;                            // +0x140 [derived: from acc+0x158]
    void* pad_0x148;                                         // +0x148 [derived: from acc+0x160 (unknown)]
    app::ShakeModule* shake_module;                          // +0x150 [derived: from acc+0x168]
    app::SlowModule* slow_module;                            // +0x158 [derived: from acc+0x170]
    void* pad_0x160;                                         // +0x160 [derived: from acc+0x178 (unknown)]
    app::ShadowModule* shadow_module;                        // +0x168 [derived: from acc+0x180]
    app::MotionAnimcmdModule* motion_animcmd_module;         // +0x170 [derived: from acc+0x188]
    void* pad_0x178;                                         // +0x178 [derived: from acc+0x190 (unknown)]
    app::InkPaintModule* ink_paint_module;                   // +0x180 [derived: from acc+0x198]
};
static_assert(sizeof(LuaStateAccessor) == 0x188, "LuaStateAccessor size mismatch");

} // namespace lib
