# Worker: pool-e

## Model: Opus

## Task: Phase 5 — Decomp remaining module functions

## Priority: DECOMP matchable functions in owned files

## Context
Phase 4 (naked asm audit) is COMPLETE — 113 naked functions removed across 32 files.
Phase 5 adds new decomp for functions in pool-e territory files.

## Completed Work
- **Phase 4**: Removed all `__attribute__((naked))` from pool-e territory (G-Z files, fun_hard_*, modules/)
- **Batch 2**: 11 functions (ItemKineticModuleImpl: 5 angle/throw/speed, Item: 2 param lookups, ItemDamageModuleImpl: 1 smash check, throw wrappers: 3)
- **Batch 3**: 4 functions (ItemKineticModuleImpl: 2 more, ItemCameraModuleImpl: 2)
- **Batch 4**: 2 functions (ItemParamAccessor: get_self_param_float/int)
- **Total new decomp**: 17 functions

## Remaining Targets (known unmatchable — skip these)
All remaining small functions (<=40B) in pool-e territory are either:
1. **NEON ext+mov divergence**: KineticEnergyRotNormal set_*, KineticEnergyNormal set_speed_3d, WeaponSnakeMissileKineticEnergyNormal set_direction, ItemKineticModuleImpl set_motion_trans_rate/rate_2nd/it_base_rot/clear_speed
2. **x8 register (not ABI param)**: All store_l2c_table_impl functions, GimmickEventPresenter dispatch
3. **Already compiled** (CSV stale): SlowModule rate_impl2, WorkModule enable_transition_term_group_impl_2

## Potential Next Targets (larger, need investigation)
- FighterMotionModuleImpl: 5 funcs 88-144B (kirby_copy patterns, damage_stop_interpolation)
- ItemCameraModuleImpl: 3 funcs 64-104B (get/set camera_subject_pos, set_camera_subject_range)
- ItemInkPaintModuleImpl: apply_link_ink_paint_impl 128B
- ItemKineticModuleImpl: it_ai_dir_factor (48B, float clamp), set_rot_along_speed_x (complex)
- stWaterAreaInfo/Rhombus2/lib::Rect store_l2c_table 196B variants

## File Territory
Same as Phase 4: all non-jemalloc files G-Z, fun_hard_*, fun_medium_*, fun_nro_*, modules/

## Build
```bash
python tools/build.py 2>&1 | tee build_output.txt
```
