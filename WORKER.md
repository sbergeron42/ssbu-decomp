# Worker: pool-b

## Model: Opus

## Task: Build proper C++ struct definitions for all game types

The decomp currently uses raw pointer arithmetic (`reinterpret_cast<u8*>(obj) + 0x60`) instead of proper struct field access (`obj->cameraModule`). This makes the code unreadable. Build real C++ struct/class headers so the decomp produces human-readable code.

### Phase 1: Complete BattleObjectModuleAccessor struct
`include/app/BattleObjectModuleAccessor.h` already has partial fields. Fill in ALL module pointers using the verified offset map:

| Offset | Field | Type |
|--------|-------|------|
| +0x38 | posture_module | PostureModule* |
| +0x40 | status_module | StatusModule* |
| +0x48 | control_module | ControlModule* |
| +0x50 | work_module | WorkModule* |
| +0x58 | ground_module | GroundModule* |
| +0x60 | camera_module | CameraModule* |
| +0x68 | kinetic_module | KineticModule* |
| +0x70 | color_blend_module | ColorBlendModule* |
| +0x78 | model_module | ModelModule* |
| +0x80 | physics_module | PhysicsModule* |
| +0x88 | motion_module | MotionModule* |
| +0x90 | stop_module | StopModule* |
| +0x98 | article_module | ArticleModule* |
| +0xA0 | attack_module | AttackModule* |
| +0xA8 | damage_module | DamageModule* |
| +0xB0 | hit_module | HitModule* |
| +0xB8 | combo_module | ComboModule* |
| +0xC0 | area_module | AreaModule* |
| +0xC8 | item_module | ItemModule* |
| +0xD0 | link_module | LinkModule* |
| +0xD8 | team_module | TeamModule* |
| +0xE0 | search_module | SearchModule* |
| +0xF0 | turn_module | TurnModule* |
| +0xF8 | reflect_module | ReflectModule* |
| +0x100 | shield_module | ShieldModule* |
| +0x108 | reflector_module | ReflectorModule* |
| +0x110 | absorber_module | AbsorberModule* |
| +0x118 | jostle_module | JostleModule* |
| +0x120 | catch_module | CatchModule* |
| +0x128 | cancel_module | CancelModule* |
| +0x138 | capture_module | CaptureModule* |
| +0x140 | effect_module | EffectModule* |
| +0x148 | sound_module | SoundModule* |
| +0x150 | visibility_module | VisibilityModule* |
| +0x158 | grab_module | GrabModule* |
| +0x168 | shake_module | ShakeModule* |
| +0x170 | slow_module | SlowModule* |
| +0x180 | shadow_module | ShadowModule* |
| +0x188 | motion_animcmd_module | MotionAnimcmdModule* |
| +0x198 | ink_paint_module | InkPaintModule* |

Use forward-declared struct types (not void*) for each module.

### Phase 2: Add stub struct headers for each module type
Create `include/app/modules/CameraModule.h`, `include/app/modules/WorkModule.h`, etc. — each is just a forward declaration or empty struct for now. This lets the accessor header use real types.

### Phase 3: Add FighterManager, FighterInformation, FighterEntry structs
These operate on their own pointer (not through the accessor). Define their known field offsets from our verified decomp.

### Phase 4: Refactor ONE module file as proof of concept
Pick CameraModule.cpp and replace all `reinterpret_cast<u8*>(acc) + 0x60` with `acc->camera_module`. Verify it still compiles and matches. This proves the struct is correct.

### Rules
- ONLY edit files in `include/app/` and `include/app/modules/`
- For Phase 4, ONLY edit `src/app/modules/CameraModule.cpp`
- Do NOT edit any other source files
- Do NOT modify data/functions.csv or tools/
- Verify matching is preserved after each change: `cmd /c build.bat && python tools/verify_all.py --summary`
