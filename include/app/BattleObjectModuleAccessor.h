#pragma once

#include "types.h"

namespace app {

// Forward declarations for all module types
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
struct ReflectorModule;
struct AbsorberModule;
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

// BattleObjectModuleAccessor — first param to most lua_bind functions
// Offsets verified from Ghidra analysis of SSBU 13.0.4
struct BattleObjectModuleAccessor {
    u8 pad_0x00[0x38];
    void* posture_module;               // +0x38
    void* status_module;                // +0x40
    void* fighter_control_module;       // +0x48
    void* work_module;                  // +0x50
    void* ground_module;                // +0x58
    void* camera_module;                // +0x60
    void* item_kinetic_module;          // +0x68
    void* color_blend_module;           // +0x70
    void* model_module;                 // +0x78
    void* physics_module;              // +0x80
    void* motion_module;                // +0x88
    void* stop_module;                  // +0x90
    void* article_module;               // +0x98
    void* attack_module;                // +0xA0
    void* damage_module;                // +0xA8
    void* hit_module;                   // +0xB0
    void* combo_module;                 // +0xB8
    void* fighter_area_module;          // +0xC0
    void* item_module;                  // +0xC8
    void* link_module;                  // +0xD0
    void* team_module;                  // +0xD8
    void* search_module;                // +0xE0
    void* pad_0xE8;                     // +0xE8 (unknown)
    void* turn_module;                  // +0xF0
    void* reflect_module;              // +0xF8
    void* shield_module;                // +0x100
    void* reflector_module;             // +0x108
    void* absorber_module;              // +0x110
    void* jostle_module;                // +0x118
    void* catch_module;                 // +0x120
    void* cancel_module;                // +0x128
    void* pad_0x130;                    // +0x130 (unknown)
    void* capture_module;               // +0x138
    void* effect_module;                // +0x140
    void* sound_module;                 // +0x148
    void* visibility_module;            // +0x150
    void* grab_module;                  // +0x158
    void* pad_0x160;                    // +0x160 (unknown)
    void* shake_module;                 // +0x168
    void* slow_module;                  // +0x170
    void* pad_0x178;                    // +0x178 (unknown)
    void* shadow_module;                // +0x180
    void* motion_animcmd_module;        // +0x188
    void* pad_0x190;                    // +0x190 (unknown)
    void* ink_paint_module;             // +0x198
};

} // namespace app
