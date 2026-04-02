# Worker: pool-c

## Model: Opus

## Task: Convert non-PLT naked asm functions to C++ with asm barriers (files M-Z)

~93 non-PLT naked asm functions are scattered across module files. Convert them to readable C++ using asm("") barriers.

### How to convert
For each naked asm function:
1. Read the assembly and understand the logic
2. Write equivalent C++ with the same struct field accesses and control flow
3. Insert asm("") barriers between independent operations to force correct scheduling
4. Wrap barriers in #ifdef MATCHING_HACK_NX_CLANG
5. Verify the C++ version produces identical bytes

### Your files (M through Z alphabetically, plus fun_batch_c/d/e, fun_medium, fun_nro)
Check these for __attribute__((naked)):
- OnCalcParamEvent, Rhombus2
- particle_functions, audio_functions, graphics_functions
- stWaterAreaInfo, StatusModule
- WeaponKineticEnergyGravity, WeaponSnakeMissileKineticEnergyNormal
- GimmickEventPresenter
- fun_batch_c_*, fun_batch_c2_*, fun_batch_d_*, fun_batch_d2_*, fun_batch_e_*
- fun_medium_*, fun_nro_load.cpp

### Rules
- ONLY edit files listed above
- Do NOT edit fun_region_039.cpp (pool-a territory)
- Do NOT edit files starting with A-L or fun_batch_a/b (pool-b territory)
- Do NOT modify tools/ or data/functions.csv
