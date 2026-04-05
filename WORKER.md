# Worker: pool-c

## Model: Opus

## Task: Re-decomp non-matching module functions (Tier 1 + naked asm stubs)

Replace bad-quality non-matching code with clean struct-based C++ using the recovered module headers.

### Tier 1 Targets (15 N-quality functions with module names)
These are decomped but bytes don't match. Rewrite from scratch using Ghidra + struct headers.

| Address | Function | Size |
|---------|----------|------|
| 0x7102092c10 | ArticleModule__add_motion_partial_impl | 48B |
| 0x71031485f0 | ~GimmickAttackModule | 80B |
| 0x7101fca0b0 | BattleObjectManager__is_active_find_battle_object_impl | 76B |
| 0x7101fca200 | BattleObjectWorld__scale_z_impl | 24B |
| 0x7102000e80 | ControlModule__reset_down_stand_fb_kind_impl | 416B |
| 0x71020aebd0 | FighterControlModuleImpl__delete_command_impl | 64B |
| 0x71020d1b20 | ItemDamageModuleImpl__damage_log_value_float_impl | 160B |
| 0x71020d1bc0 | ItemDamageModuleImpl__damage_log_value_int_impl | 720B |
| 0x7102017900 | EffectModule__req_after_image_impl | 80B |
| 0x7102017950 | EffectModule__req_after_image_no_parent_impl | 80B |
| 0x71020c9d60 | FighterInformation__hit_point_impl | 64B |
| 0x71020c9e90 | FighterInformation__suicide_count_impl | 80B |
| 0x7102140490 | FighterManager__get_fighter_entry_impl | 240B |
| 0x7102140f90 | FighterManager__get_fighter_entry_impl (lua_bind) | 28B |
| 0x7102140fc0 | FighterManager__get_fighter_information_impl (lua_bind) | 32B |

### Tier 2 Targets: Naked ASM stubs to replace with real C++
Priority files (most naked stubs):
- `src/app/modules/ItemKineticModuleImpl.cpp` — 16 naked functions
- `src/app/FighterManager.cpp` — 9 naked functions
- `src/app/modules/FighterMotionModuleImpl.cpp` — 8 naked functions

For each naked function: decompile in Ghidra, write clean C++ using struct headers, remove the asm block.

### Approach
1. For Tier 1: find the existing bad code in src/, delete it, rewrite using Ghidra + struct headers
2. For Tier 2: find the naked asm block, decompile in Ghidra, replace with C++
3. Build and verify after each batch

### Output: Edit existing files listed above + src/app/fun_redecomp_c_*.cpp for new files if needed

### Rules
- Use struct field access from include/app/modules/ — all 41 module structs are recovered
- No raw offsets, no Ghidra paste, no naked asm
- 3-attempt limit per function
- CAN edit: src/app/modules/ItemKineticModuleImpl.cpp, src/app/FighterManager.cpp, src/app/modules/FighterMotionModuleImpl.cpp, and Tier 1 source files
- Save Ghidra results to /tmp/ghidra_results.txt
