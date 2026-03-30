# First Matching Targets

Simple leaf functions to validate the toolchain. All are named by the modding community.

## Tier 1: Trivial getters (2-3 instructions)

| Function | Address | Instructions | Pattern |
|----------|---------|-------------|---------|
| FighterControlModuleImpl__get_attack_s3_turn_impl | 71020aec30 | 3 | load chain → ret |
| FighterControlModuleImpl__get_attack_s4_turn_impl | 71020aec10 | 3 | load chain → ret |
| ItemKineticModuleImpl__get_kinetic_flags_impl | 71020cc900 | 3 | load chain → ret |

## Tier 2: Simple setters (4-6 instructions)

| Function | Address | Instructions | Pattern |
|----------|---------|-------------|---------|
| FighterAreaModuleImpl__enable_fix_jostle_area_impl | 71020ae240 | 6 | load ptr, set flag+floats, ret |
| ItemKineticModuleImpl__set_slope_type_impl | 71020cc8d0 | 5 | bounds check, store, ret |
| FighterControlModuleImpl__set_command_life_count_impl | 71020aed80 | 6 | indexed store, ret |

## Tier 3: Zeroing/disable functions (7-8 instructions)

| Function | Address | Instructions | Pattern |
|----------|---------|-------------|---------|
| FighterAreaModuleImpl__disable_fix_jostle_area_impl | 71020ae280 | 7 | zero-fill struct fields |
| FighterAreaModuleImpl__enable_fix_jostle_area_xy_impl | 71020ae260 | 8 | set flag+4 floats |

## Key struct offsets discovered

- `BattleObjectModuleAccessor + 0x48` → FighterControlModule ptr
- `BattleObjectModuleAccessor + 0x68` → ItemKineticModule ptr
- `BattleObjectModuleAccessor + 0xc0` → FighterAreaModule ptr
- `FighterControlModule + 0x614` → attack_s3_turn (u32)
- `FighterAreaModule + 0x2a0` → jostle_area flags (u16)
- `FighterAreaModule + 0x2a4..0x2b0` → jostle_area floats (4x f32)
- `ItemKineticModule + 0x9d8` → kinetic_flags (u32)
- `ItemKineticModule + 0x9e8` → slope_type (u32, max=7)
