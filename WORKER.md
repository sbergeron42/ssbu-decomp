# Worker: pool-a

## Model: Opus

## Task: Refactor module files A-G to use struct field access

Replace raw pointer arithmetic with proper struct member access across module source files. The struct headers now exist in include/app/.

### What to change
Replace patterns like:
    auto* m = *reinterpret_cast<void**>(reinterpret_cast<u8*>(acc) + 0x60);
With:
    auto* m = acc->camera_module;

And replace vtable casts like:
    reinterpret_cast<void(*)(void*)>(VT(m)[0x48/8])(m);
With:
    reinterpret_cast<void(*)(void*)>((*reinterpret_cast<void***>(m))[0x48/8])(m);
(keep vtable calls as-is for now, just fix the module access pattern)

### Your files
Refactor these source files (alphabetically A through G):
- src/app/modules/AbsorberModule.cpp
- src/app/modules/AreaModule.cpp
- src/app/modules/ArticleModule.cpp
- src/app/modules/AttackModule.cpp
- src/app/modules/CancelModule.cpp
- src/app/modules/CaptureModule.cpp
- src/app/modules/CatchModule.cpp
- src/app/modules/ColorBlendModule.cpp
- src/app/modules/ComboModule.cpp
- src/app/modules/ControlModule.cpp
- src/app/modules/DamageModule.cpp
- src/app/modules/EffectModule.cpp
- src/app/modules/FighterAreaModuleImpl.cpp
- src/app/modules/FighterControlModuleImpl.cpp
- src/app/modules/GrabModule.cpp
- src/app/modules/GroundModule.cpp

### Critical rule
After EACH file change, rebuild and verify matching is preserved:
    cmd /c build.bat && python tools/verify_all.py --summary
If verified count drops, REVERT that file and move on.

### Include the header
Add #include "app/BattleObjectModuleAccessor.h" at top of each file.

### Rules
- ONLY edit files listed above
- Do NOT edit include/ headers
- Do NOT modify data/functions.csv or tools/
- NEVER reduce verified count
