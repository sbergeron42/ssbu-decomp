# Worker: pool-c

## Model: Opus

## Task: Resource service — file loading pipeline and ARC archive operations

## Priority: NEW DECOMP (ARCropolis community value)

## Context
The resource loading pipeline is what ARCropolis hooks into for mod loading. Existing typed headers in `include/resource/` cover `ResServiceNX`, `LoadedArc`, `PathResolver`, `PipelineTypes`, `TaskInfra`, and container types. Phase 2 already rewrote `res_pipeline_medium.cpp` and `res_remaining_medium.cpp` with typed access.

## Approach
1. Use `mcp__ghidra__search_functions_by_name` to find resource-related functions (search for "ResService", "LoadedArc", "FileSystem")
2. Focus on the loading pipeline: file open, read, decompress, callback
3. Extend `include/resource/` headers as you discover new fields
4. Cross-reference with ARCropolis source for community-validated field names

## File Territory
- `src/resource/res_loading_pipeline.cpp` (extend)
- `src/resource/res_load_helpers.cpp` (extend)
- `src/resource/res_pipeline_large.cpp` (extend)
- `src/resource/res_*.cpp` (any resource file)
- `include/resource/` (extend headers)
- `include/app/placeholders/` (new types as needed)

## Quality Rules
- Use ARCropolis names where available, tag `[derived: ARCropolis]`
- NO `FUN_` names, NO Ghidra vars, NO raw vtable dispatch, NO naked asm
- Cast density under 10%
- Run `python tools/review_diff.py pool-c` before committing

## Build
```bash
python tools/build.py 2>&1 | tee build_output.txt
```
