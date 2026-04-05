# Worker: pool-d

## Model: Opus

## Task: Re-decomp non-matching module functions (Tier 1 + naked asm stubs)

Replace bad-quality non-matching code with clean struct-based C++ using the recovered module headers.

### Tier 1 Targets (16 N-quality functions with module names)
These are decomped but bytes don't match. Rewrite from scratch using Ghidra + struct headers.

| Address | Function | Size |
|---------|----------|------|
| 0x7102141200 | FighterManager__set_cursor_whole_impl | 16B |
| 0x7102141450 | FighterManager__set_final_fear_face_impl | 128B |
| 0x71021414d0 | FighterManager__start_finalbg_impl | 144B |
| 0x7102141560 | FighterManager__exit_finalbg_impl | 64B |
| 0x7102029270 | GroundModule__set_shape_safe_pos_impl | 368B |
| 0x71020293e0 | GroundModule__get_touch_normal_x_consider_gravity_impl | 736B |
| 0x71020296c0 | GroundModule__ray_check_hit_pos_target_impl | 48B |
| 0x71020296f0 | GroundModule__ray_check_hit_pos_normal_no_culling_impl | 528B |
| 0x710202a6e0 | GroundModule__ray_check_hit_normal_impl | 560B |
| 0x7102043ea0 | KineticModule__is_suspend_energy_impl | 432B |
| 0x7102044050 | KineticModule__enable_energy_impl | 176B |
| 0x7102044100 | KineticModule__suspend_energy_impl | 176B |
| 0x7102048a60 | LinkModule__get_parent_have_item_visibility_impl | 48B |
| 0x7102048a90 | LinkModule__get_parent_attach_item_visibility_impl | 432B |
| 0x71020ad720 | FighterStopModuleImpl__is_damage_stop_impl | 192B |
| 0x71020ad7e0 | FighterStopModuleImpl__get_damage_stop_frame_impl | 176B |

### Tier 2 Targets: Naked ASM stubs to replace with real C++
Priority files (most naked stubs):
- `src/app/modules/ItemCameraModuleImpl.cpp` — 8 naked functions
- `src/app/modules/StatusModule.cpp` — 2 naked functions
- `src/app/modules/AttackModule.cpp` — 2 naked functions
- `src/app/modules/ItemDamageModuleImpl.cpp` — 1 naked function
- `src/app/modules/FighterWorkModuleImpl.cpp` — 1 naked function

For each naked function: decompile in Ghidra, write clean C++ using struct headers, remove the asm block.

### Approach
1. For Tier 1: find the existing bad code in src/, delete it, rewrite using Ghidra + struct headers
2. For Tier 2: find the naked asm block, decompile in Ghidra, replace with C++
3. Build and verify after each batch

### Output: Edit existing files listed above + src/app/fun_redecomp_d_*.cpp for new files if needed

### Rules
- Use struct field access from include/app/modules/ — all 41 module structs are recovered
- No raw offsets, no Ghidra paste, no naked asm
- 3-attempt limit per function
- CAN edit: src/app/modules/ItemCameraModuleImpl.cpp, src/app/modules/StatusModule.cpp, src/app/modules/AttackModule.cpp, src/app/modules/ItemDamageModuleImpl.cpp, src/app/modules/FighterWorkModuleImpl.cpp, and Tier 1 source files
- Save Ghidra results to /tmp/ghidra_results.txt
