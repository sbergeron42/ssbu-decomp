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
// Each module pointer is proven by the corresponding lua_bind::MODULE__*_impl (.dynsym)
// functions, which load the module pointer from accessor+OFFSET before vtable dispatch.
struct BattleObjectModuleAccessor {
    u8 pad_0x00[0x38];
    PostureModule* posture_module;               // +0x38 [derived: PostureModule__*_impl (.dynsym) loads from accessor+0x38]
    StatusModule* status_module;                 // +0x40 [derived: StatusModule__*_impl (.dynsym) loads from accessor+0x40]
    ControlModule* fighter_control_module;       // +0x48 [derived: ControlModule__*_impl (.dynsym) loads from accessor+0x48]
    WorkModule* work_module;                     // +0x50 [derived: WorkModule__*_impl (.dynsym) loads from accessor+0x50]
    GroundModule* ground_module;                 // +0x58 [derived: GroundModule__*_impl (.dynsym) loads from accessor+0x58]
    CameraModule* camera_module;                 // +0x60 [derived: CameraModule__*_impl (.dynsym) loads from accessor+0x60]
    KineticModule* item_kinetic_module;          // +0x68 [derived: KineticModule__*_impl (.dynsym) loads from accessor+0x68]
    ColorBlendModule* color_blend_module;        // +0x70 [derived: ColorBlendModule__*_impl (.dynsym) loads from accessor+0x70]
    ModelModule* model_module;                   // +0x78 [derived: ModelModule__*_impl (.dynsym) loads from accessor+0x78]
    PhysicsModule* physics_module;               // +0x80 [derived: PhysicsModule__*_impl (.dynsym) loads from accessor+0x80]
    MotionModule* motion_module;                 // +0x88 [derived: MotionModule__*_impl (.dynsym) loads from accessor+0x88]
    StopModule* stop_module;                     // +0x90 [derived: StopModule__*_impl (.dynsym) loads from accessor+0x90]
    ArticleModule* article_module;               // +0x98 [derived: ArticleModule__*_impl (.dynsym) loads from accessor+0x98]
    AttackModule* attack_module;                 // +0xA0 [derived: AttackModule__*_impl (.dynsym) loads from accessor+0xA0]
    DamageModule* damage_module;                 // +0xA8 [derived: DamageModule__*_impl (.dynsym) loads from accessor+0xA8]
    HitModule* hit_module;                       // +0xB0 [derived: HitModule__*_impl (.dynsym) loads from accessor+0xB0]
    ComboModule* combo_module;                   // +0xB8 [derived: ComboModule__*_impl (.dynsym) loads from accessor+0xB8]
    AreaModule* fighter_area_module;              // +0xC0 [derived: AreaModule__*_impl (.dynsym) loads from accessor+0xC0]
    ItemModule* item_module;                     // +0xC8 [derived: ItemModule__*_impl (.dynsym) loads from accessor+0xC8]
    LinkModule* link_module;                     // +0xD0 [derived: LinkModule__*_impl (.dynsym) loads from accessor+0xD0]
    TeamModule* team_module;                     // +0xD8 [derived: TeamModule__*_impl (.dynsym) loads from accessor+0xD8]
    SearchModule* search_module;                 // +0xE0 [derived: SearchModule__*_impl (.dynsym) loads from accessor+0xE0]
    void* pad_0xE8;                              // +0xE8 (unknown — no .dynsym function loads from this offset)
    TurnModule* turn_module;                     // +0xF0 [derived: TurnModule__*_impl (.dynsym) loads from accessor+0xF0]
    ReflectModule* reflect_module;               // +0xF8 [derived: ReflectModule__*_impl (.dynsym) loads from accessor+0xF8]
    ShieldModule* shield_module;                 // +0x100 [derived: ShieldModule__*_impl (.dynsym) loads from accessor+0x100]
    ReflectorModule* reflector_module;           // +0x108 [derived: ReflectorModule__*_impl (.dynsym) loads from accessor+0x108]
    AbsorberModule* absorber_module;             // +0x110 [derived: AbsorberModule__*_impl (.dynsym) loads from accessor+0x110]
    JostleModule* jostle_module;                 // +0x118 [derived: JostleModule__*_impl (.dynsym) loads from accessor+0x118]
    CatchModule* catch_module;                   // +0x120 [derived: CatchModule__*_impl (.dynsym) loads from accessor+0x120]
    CancelModule* cancel_module;                 // +0x128 [derived: CancelModule__*_impl (.dynsym) loads from accessor+0x128]
    void* pad_0x130;                             // +0x130 (unknown — no .dynsym function loads from this offset)
    CaptureModule* capture_module;               // +0x138 [derived: CaptureModule__*_impl (.dynsym) loads from accessor+0x138]
    EffectModule* effect_module;                 // +0x140 [derived: EffectModule__*_impl (.dynsym) loads from accessor+0x140]
    SoundModule* sound_module;                   // +0x148 [derived: SoundModule__*_impl (.dynsym) loads from accessor+0x148]
    VisibilityModule* visibility_module;         // +0x150 [derived: VisibilityModule__*_impl (.dynsym) loads from accessor+0x150]
    GrabModule* grab_module;                     // +0x158 [derived: GrabModule__*_impl (.dynsym) loads from accessor+0x158]
    void* pad_0x160;                             // +0x160 (unknown — no .dynsym function loads from this offset)
    ShakeModule* shake_module;                   // +0x168 [derived: ShakeModule__*_impl (.dynsym) loads from accessor+0x168]
    SlowModule* slow_module;                     // +0x170 [derived: SlowModule__*_impl (.dynsym) loads from accessor+0x170]
    void* pad_0x178;                             // +0x178 (unknown — no .dynsym function loads from this offset)
    ShadowModule* shadow_module;                 // +0x180 [derived: ShadowModule__*_impl (.dynsym) loads from accessor+0x180]
    MotionAnimcmdModule* motion_animcmd_module;  // +0x188 [derived: MotionAnimcmdModule__*_impl (.dynsym) loads from accessor+0x188]
    void* pad_0x190;                             // +0x190 (unknown — no .dynsym function loads from this offset)
    InkPaintModule* ink_paint_module;             // +0x198 [derived: InkPaintModule__*_impl (.dynsym) loads from accessor+0x198]
};

} // namespace app
