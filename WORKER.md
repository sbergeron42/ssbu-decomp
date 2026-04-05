# Worker: pool-c

## Model: Opus

## Task: Types-first HARD decomp — SearchModule + ReflectModule + ReflectorModule functions

Decomp HARD-tier functions that access these modules. All structs are recovered.

### Output: src/app/fun_typed_c_004.cpp onward (continue numbering)

### Progress
- fun_typed_c_004.cpp: 13 functions (5 verified 100%, 1 near-match, 7 L2C bridges compiled)
- Verified: get_pre_explosion_search_object_id, search_range, search_range_ignore_lr, get_material_type, get_assist_respawn_position
- L2C bridge functions compile but don't verify due to NX Clang register allocation divergence

### Rules
- Use struct field access, no raw offsets, no Ghidra paste, no naked asm
- 3-attempt limit per function
- ONLY create src/app/fun_typed_c_*.cpp
