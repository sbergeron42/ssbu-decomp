# Worker: pool-a

## Model: Opus

## Task: Refactor non-module files to use struct field access (batch/region files)

Replace raw reinterpret_cast offset patterns with proper struct member access. Module files are done — this covers the batch and region files.

### Your files (batch + region — highest cast counts)
- src/app/engine_functions.cpp (133 casts)
- src/app/fun_region_000.cpp (52)
- src/app/fun_region_001.cpp (80)
- src/app/fun_region_002.cpp (34)
- src/app/fun_batch_c2_017.cpp (98)
- src/app/fun_batch_c2_018.cpp
- src/app/fun_batch_c2_019.cpp
- All other src/app/fun_region_*.cpp and src/app/fun_batch_*.cpp files

### What to change
For functions taking BattleObjectModuleAccessor* as first param:
    #include "app/BattleObjectModuleAccessor.h"
Replace:
    auto* m = *reinterpret_cast<void**>(reinterpret_cast<u8*>(acc) + 0x60);
With:
    auto* m = acc->camera_module;

For functions taking FighterInformation*, FighterManager*, FighterEntry*:
    #include "app/FighterInformation.h"  (etc.)
Replace raw offset casts with struct field access where the header defines the field.

### Critical rule
After EACH file, rebuild and verify: cmd /c build.bat && python tools/verify_all.py --summary
If verified drops, REVERT and move on.

### Rules
- ONLY edit src/app/fun_region_*.cpp, src/app/fun_batch_*.cpp, src/app/engine_functions.cpp
- Do NOT edit modules/ (already done)
- Do NOT edit game type files (pool-b territory)
- Do NOT modify include/ headers, tools/, or data/
