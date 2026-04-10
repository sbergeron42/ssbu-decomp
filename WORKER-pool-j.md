# Worker: pool-j

## Model: Opus

## Task: Sound and audio systems (SoundModule, audio_functions)

## Priority: NEW DECOMP

## Context
Sound and audio handle SE (sound effects), BGM, voice lines, and audio triggers. The .dynsym has `SoundModule__*_impl` names. `include/app/modules/SoundModule.h` has typed wrappers. `src/app/audio_functions.cpp` has existing work.

## Approach
1. Use `mcp__ghidra__search_functions_by_name` to find sound/audio functions
2. Focus on SoundModule methods, audio dispatch helpers, BGM control
3. Extend SoundModule.h with new vtable slot wrappers

## File Territory
- `src/app/audio_functions.cpp` (extend)
- `src/app/modules/SoundModule.cpp` (extend)
- `include/app/modules/SoundModule.h` (extend)
- `include/app/placeholders/` (new types as needed)

## Quality Rules
- NO `FUN_` names, NO Ghidra vars, NO raw vtable dispatch, NO naked asm
- Cast density under 10%
- Run `python tools/review_diff.py pool-j` before committing

## Build
```bash
python tools/build.py 2>&1 | tee build_output.txt
```
